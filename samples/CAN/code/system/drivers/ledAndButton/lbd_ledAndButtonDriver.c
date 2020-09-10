/**
 * @file lbd_ledAndButtonDriver.c
 * 
 *
 * Copyright (C) 2019-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/* Module interface
 *   lbd_osInitLEDAndButtonDriver
 *   lbd_scSmplHdlr_setLED
 *   lbd_scSmplHdlr_getButton_core0
 *   lbd_scSmplHdlr_getButton_core1
 *   lbd_scSmplHdlr_getButton_core2
 *   lbd_osGetButtonSw1
 *   lbd_osGetButtonSw2
 *   lbd_osTask1ms
 * Local functions
 *   osGetButton
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "typ_types.h"
#include "rtos.config.h"
#include "rtos_ivorHandler.h"
#include "lbd_ledAndButtonDriver_defSysCalls.h"
#include "lbd_ledAndButtonDriver.h"


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
/** The state information needed to debounce a single button. */
typedef struct stateButton_t
{
    /** The GPIO index of the digital input the button is connected to. */ 
    lbd_button_t button;

    /** The counter value of the debouncer. */
    int8_t cntDebounce;
    
    /** The current debounced state of the button. \a true means pressed. */
    bool buttonState;

} stateButton_t;


/** The state information of the driver. It can be run on different cores and the cores
    must influence one another. Therefore we have the state information core dependent. */
typedef struct stateDriver_t
{
    /** The debounce counter for button SW1. */
    stateButton_t stateSW1;
    
    /** The debounce counter for button SW2. */
    stateButton_t stateSW2;
    
    /** The last recent value of the vector of all button states. Used in the driver's main
        function to detect button change events. */
    uint8_t lastStateButtons;
    
    /** The specification of a notification callback in case the button state changes. */
    rtos_taskDesc_t onButtonChangeCallback;

} stateDriver_t;


/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */

/** The state information to debounce the buttons on the different cores.
      @remark We make the definition for all cores independent from the configuration
    macros #RTOS_RUN_SAFE_RTOS_ON_CORE_0 (1, 2): The driver's OS API is not RTOS dependent
    and may be used from a core not running the RTOS, too.
      @remark We can put the data object into a normal cached area. Each core solely uses
    its own array element and the only data exchange across core boundaries is the
    initialization of the elements, which is done on the boot core and before any other
    core may make use of the driver API. Therefore this is uncritical with respect to
    cache consistency. */
static stateDriver_t DATA_OS(_coreInstanceDataAry)[RTOS_NO_CORES] =
    {
        [0 ... (RTOS_NO_CORES-1)] =
            { .stateSW1 =
                { .button = lbd_bt_button_SW1
                , .cntDebounce = 0
                , .buttonState = false
                }
            , .stateSW2 =
                { .button = lbd_bt_button_SW2
                , .cntDebounce = 0
                , .buttonState = false
                }
            , .lastStateButtons = 0
            , .onButtonChangeCallback =
                { .addrTaskFct = 0
                , .PID = 0
                , .tiTaskMax = RTOS_TI_US2TICKS(1000)
                }
            }       
    };


/*
 * Function implementation
 */

/**
 * Get the current status of button SW1. This is the switch, which is labeled both on the
 * PCB, "SW1_PA3" and "SW4". This makes it potentially dangerous to mix up the switch with
 * the reset button on the board, which is labeled "RESET" and "SW1".
 *   @return
 * \a true if button SW1 is currently pressed, \a false otherwise. This is the debounced
 * read value from the GPIO.
 *   @param pCoreInstanceData
 * Each participating core has its own debouncing. We need some core related state
 * information, which is provided by reference by this argument.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception. User task code can consider using
 * lbd_getButton() instead.
 */
static bool osGetButton(stateButton_t * const pCoreInstanceData)
{
    _Static_assert( LBD_DEBOUNCE_TIME_BUTTONS >= 2  &&  LBD_DEBOUNCE_TIME_BUTTONS <= 100
                  , "Debounce time configuration out of range"
                  );

    /* The debounce time of the read process of the button states is determined by this
       counter maximum. */  
    #define MAX_CNT_BTN_DEBOUNCE    ((LBD_DEBOUNCE_TIME_BUTTONS)/2)

    /* The contribution to the debouncing depends on the current 0/1 reading of the GPIO
       input buffer. */
    const signed int actState =
        *(((__IO uint8_t*)&SIUL2->GPDI[0])+((unsigned)pCoreInstanceData->button)) != 0? 1: -1;

    pCoreInstanceData->cntDebounce += actState;
    if(pCoreInstanceData->cntDebounce >= MAX_CNT_BTN_DEBOUNCE)
    {
        pCoreInstanceData->cntDebounce = MAX_CNT_BTN_DEBOUNCE;
        pCoreInstanceData->buttonState = true;
    }
    else if(pCoreInstanceData->cntDebounce <= -MAX_CNT_BTN_DEBOUNCE)
    {
        pCoreInstanceData->cntDebounce = -MAX_CNT_BTN_DEBOUNCE;
        pCoreInstanceData->buttonState = false;
    }
    #undef MAX_CNT_BTN_DEBOUNCE

    return pCoreInstanceData->buttonState;

} /* End of osGetButton */




/**
 * Initialization of LED driver. The GPIO ports are defined to become outputs and the
 * output values are set such that the LEDs are shut off.
 *   @param onButtonChangeCallback_core0
 * The I/O driver offers the service to regularly poll the current button input status and
 * to inform the application code about any change. The notification is done per callback.
 * Pass NULL if no notification is desired on core 0, Z4A.
 *   @param PID_core0
 * The ID of the process to run the callback in. The value doesn't care if \a
 * onButtonChangeCallback_core0 is NULL. The range is 1 ... #RTOS_NO_PROCESSES. It is
 * checked by assertion.
 *   @param onButtonChangeCallback_core1
 * The I/O driver offers the service to regularly poll the current button input status and
 * to inform the application code about any change. The notification is done per callback.
 * Pass NULL if no notification is desired on core 1, Z4B.
 *   @param PID_core1
 * The ID of the process to run the callback in. The value doesn't care if \a
 * onButtonChangeCallback_core1 is NULL. The range is 1 ... #RTOS_NO_PROCESSES. It is
 * checked by assertion.
 *   @param onButtonChangeCallback_core2
 * The I/O driver offers the service to regularly poll the current button input status and
 * to inform the application code about any change. The notification is done per callback.
 * Pass NULL if no notification is desired on core 2, Z2.
 *   @param PID_core2
 * The ID of the process to run the callback in. The value doesn't care if \a
 * onButtonChangeCallback_core2 is NULL. The range is 1 ... #RTOS_NO_PROCESSES. It is
 * checked by assertion.
 *   @param tiMaxTimeInUs
 * Deadline monitoring is enabled for the callbacks. This argument specifies the world time
 * budget for completion of the callbacks \a onButtonChangeCallback_coreN in Microseconds.
 * A value of 0 disables the deadline monitoring for the callback execution. The maximum
 * permited value is #RTOS_TI_DEADLINE_MAX_IN_US.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user 
 * code will lead to a privileged exception.
 *   @remark
 * In a multi-core implementation, this function is called only once from the boot core and
 * before any other core may make use of the other driver API.
 *   @remark
 * In a multi-core environment, if a core doesn't run safe-RTOS, it may still use this
 * driver in restricted way:\n
 *   - Only the OS functions can be used (lbd_os<FctName>())\n
 *   - Callbacks must not be used (onButtonChangeCallback_coreN == NULL)\n
 *   - The regular call of lbd_osTask1ms() should be avoided. It is simply useless without
 * a callback
 */
void lbd_osInitLEDAndButtonDriver( lbd_onButtonChangeCallback_t onButtonChangeCallback_core0
                                 , unsigned int PID_core0
                                 , lbd_onButtonChangeCallback_t onButtonChangeCallback_core1
                                 , unsigned int PID_core1
                                 , lbd_onButtonChangeCallback_t onButtonChangeCallback_core2
                                 , unsigned int PID_core2
                                 , unsigned int tiMaxTimeInUs
                                 )
{
    /* Reset driver's state information. */
    _Static_assert( sizeOfAry(_coreInstanceDataAry) == 3
                  , "Code needs adaptation after change of HW configuration"
                  );
    _coreInstanceDataAry[0] =
    _coreInstanceDataAry[1] =
    _coreInstanceDataAry[2] =
        (stateDriver_t){ .stateSW1 =
                            { .button = lbd_bt_button_SW1
                            , .cntDebounce = 0
                            , .buttonState = false
                            }
                        , .stateSW2 =
                            { .button = lbd_bt_button_SW2
                            , .cntDebounce = 0
                            , .buttonState = false
                            }
                       , .lastStateButtons = 0
                       , .onButtonChangeCallback =
                            { .addrTaskFct = 0
                            , .PID = 0
                            , .tiTaskMax = RTOS_TI_US2TICKS(1000)
                            }
                       };
        
    /* LEDs are initially off. */
    lbd_osSetLED(lbd_led_0_DS11, /* isOn */ false);
    lbd_osSetLED(lbd_led_1_DS10, /* isOn */ false);
    lbd_osSetLED(lbd_led_2_DS9, /* isOn */ false);
    lbd_osSetLED(lbd_led_3_DS8, /* isOn */ false);
    lbd_osSetLED(lbd_led_4_DS7, /* isOn */ false);
    lbd_osSetLED(lbd_led_5_DS6, /* isOn */ false);
    lbd_osSetLED(lbd_led_6_DS5, /* isOn */ false);
    lbd_osSetLED(lbd_led_7_DS4, /* isOn */ false);
    
    /* Enable access to a user LED on the evalution board (see
       DEVKIT-MPC5748G-Schematics.pdf). The reference from a port designation like PA4 to
       the related pin configuration register MSCR is found in the attachment
       IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx of the MCU reference
       manual. In this file, go to tab "IO Signal Table", row 36, for PA4. Column C gives
       us the index of the MSCR. Column D gives us 0 as "Source Signal Select" for function
       GPIO. */
#define INIT_LED(led)                                                                        \
    SIUL2->MSCR[led] =                                                                       \
            SIUL2_MSCR_SSS(0 /* GPIO */)                                                     \
            | SIUL2_MSCR_SRC(0) /* Slew rate: slowest possible */                            \
            | SIUL2_MSCR_OBE(1) /* Enable output buffer */                                   \
            | SIUL2_MSCR_ODE(1) /* Enable open drain: LED connected to +3.3V */              \
            | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */                               \
            | SIUL2_MSCR_APC(0) /* No analog I/O */                                          \
            | SIUL2_MSCR_IBE(0) /* Disable input buffer */                                   \
            | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */                              \
            | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */                               \
            | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */                 \
            ;

    /* Enable all LEDs accordingly. */
    INIT_LED(lbd_led_0_DS11)
    INIT_LED(lbd_led_1_DS10)
    INIT_LED(lbd_led_2_DS9)
    INIT_LED(lbd_led_3_DS8)
    INIT_LED(lbd_led_4_DS7)
    INIT_LED(lbd_led_5_DS6)
    INIT_LED(lbd_led_6_DS5)
    INIT_LED(lbd_led_7_DS4)

#undef INIT_LED
   
    /// @todo Check if the buttons are connected to ports, which are interrupt enabled. If
    // we are likely better off not to use polling but use an interrupt service.
#define INIT_SW(sw)                                                                          \
    SIUL2->MSCR[sw] =                                                                        \
            SIUL2_MSCR_SSS(0 /* GPIO */)                                                     \
            | SIUL2_MSCR_SRC(0) /* Slew rate: slowest possible */                            \
            | SIUL2_MSCR_OBE(0) /* Disable output buffer */                                  \
            | SIUL2_MSCR_ODE(0) /* Irrelevant: Enable open drain: LED connected to +3.3V */  \
            | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */                               \
            | SIUL2_MSCR_APC(0) /* No analog I/O */                                          \
            | SIUL2_MSCR_IBE(1) /* Enable input buffer */                                    \
            | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */                              \
            | SIUL2_MSCR_PUE(0) /* Pull up/down: Off, we have a pulldown on the PCB */       \
            | SIUL2_MSCR_PUS(0) /* If enabled, we would need 0=pull down */                  \
            ;

    /* Enable all buttons accordingly. */
    INIT_SW(lbd_bt_button_SW1)
    INIT_SW(lbd_bt_button_SW2)

    /* Save optional callbacks in global driver data. */
    if(onButtonChangeCallback_core0 != NULL)
    {
        /* Here we are in trusted code. The passed arguments are static configuration data
           and cannot produce an occasional failure. Checking by assertion is appropriate. */
        assert(PID_core0 > 0  &&  PID_core0 < RTOS_NO_PROCESSES
               &&  tiMaxTimeInUs < RTOS_TI_DEADLINE_MAX_IN_US
              );
        
        _coreInstanceDataAry[0].onButtonChangeCallback.PID = PID_core0;
        _coreInstanceDataAry[0].onButtonChangeCallback.addrTaskFct =
                                                    (uintptr_t)onButtonChangeCallback_core0;
        _coreInstanceDataAry[0].onButtonChangeCallback.tiTaskMax =
                                                    RTOS_TI_US2TICKS(tiMaxTimeInUs);
    }
    if(onButtonChangeCallback_core1 != NULL)
    {
        /* Here we are in trusted code. The passed arguments are static configuration data
           and cannot produce an occasional failure. Checking by assertion is appropriate. */
        assert(PID_core1 > 0  &&  PID_core1 < RTOS_NO_PROCESSES
               &&  tiMaxTimeInUs < RTOS_TI_DEADLINE_MAX_IN_US
              );
        
        _coreInstanceDataAry[1].onButtonChangeCallback.PID = PID_core1;
        _coreInstanceDataAry[1].onButtonChangeCallback.addrTaskFct =
                                                    (uintptr_t)onButtonChangeCallback_core1;
        _coreInstanceDataAry[1].onButtonChangeCallback.tiTaskMax =
                                                    RTOS_TI_US2TICKS(tiMaxTimeInUs);
    }
    if(onButtonChangeCallback_core2 != NULL)
    {
        /* Here we are in trusted code. The passed arguments are static configuration data
           and cannot produce an occasional failure. Checking by assertion is appropriate. */
        assert(PID_core2 > 0  &&  PID_core2 < RTOS_NO_PROCESSES
               &&  tiMaxTimeInUs < RTOS_TI_DEADLINE_MAX_IN_US
              );
        
        _coreInstanceDataAry[2].onButtonChangeCallback.PID = PID_core2;
        _coreInstanceDataAry[2].onButtonChangeCallback.addrTaskFct =
                                                    (uintptr_t)onButtonChangeCallback_core2;
        _coreInstanceDataAry[2].onButtonChangeCallback.tiTaskMax =
                                                    RTOS_TI_US2TICKS(tiMaxTimeInUs);
    }
} /* End of lbd_osInitLEDAndButtonDriver */



/**
 * Sample implementation of a system call of conformance class "simple". Such a
 * system call can already be implemented in C but it needs to be run with all interrupts
 * suspended. It cannot be preempted. Suitable for short running services only.\n
 *   Here we use the concept to implement an I/O driver for the four LEDs on the eval board
 * TRK-USB-MPC5643L.
 *   @return
 * The value of the argument \a isOn is returned.
 *   @param pidOfCallingTask
 * Process ID of calling user task.
 *   @param led
 * The LED to address to.
 *   @param isOn
 * Switch the selected LED either on or off.
 */
uint32_t lbd_scSmplHdlr_setLED( uint32_t pidOfCallingTask ATTRIB_UNUSED
                              , lbd_led_t led
                              , bool isOn
                              )
{
    /* A safe, "trusted" implementation needs to double check the selected LED in order to
       avoid undesired access to I/O ports other than the true LED ports.
         We apply a hard-coded binary search. */
    const unsigned int iLed = (unsigned)led;
    bool isOk;
    if(iLed < 36)
    {
        if(iLed < 7)
        {
            if(iLed < 4)
                isOk = iLed == 0;
            else
                isOk = iLed == 4;
        }
        else
        {
            if(iLed < 10)
                isOk = iLed == 7;
            else
                isOk = iLed == 10;
        }
    }
    else
    {
        if(iLed < 125)
        {
            if(iLed < 117)
                isOk = iLed == 36;
            else
                isOk = iLed == 117;
        }
        else
        {
            if(iLed < 148)
                isOk = iLed == 125;
            else
                isOk = iLed == 148;
        }
    }

    if(!isOk)
    {
        /* Abort this system call and the calling user task and count this event as an
           error in the process the failing task belongs to. */
        rtos_osSystemCallBadArgument();
        
        /* rtos_osSystemCallBadArgument() doesn't return. We never get here. */
    }

    lbd_osSetLED(led, isOn);
    return isOn;
    
} /* End of lbd_scSmplHdlr_setLED */




#if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 1
/**
 * Sample implementation of a system call of conformance class "simple". Such a system call
 * can already be implemented in C but it needs to be run with all interrupts suspended. It
 * cannot be preempted. Suitable for short running services only.\n
 *   Here we use the concept to implement an input function for the two buttons on core 0
 * on the eval board DEVKIT-MPC5748G.
 *   @return
 * The value of the argument \a isOn is returned.
 *   @param pidOfCallingTask
 * Process ID of calling user task.
 *   @param led
 * The LED to address to.
 *   @param isOn
 * Switch the selected LED either on or off.
 */
uint32_t lbd_scSmplHdlr_getButton_core0( uint32_t pidOfCallingTask ATTRIB_UNUSED
                                       , lbd_button_t button
                                       )
{
    /* A safe, "trusted" implementation needs to double check the selected button in order to
       avoid undesired access to I/O ports other than the two true button ports on the eval
       board. */
    assert(rtos_osGetIdxCore() == 0);
    if(button == lbd_bt_button_SW1)
        return (uint32_t)osGetButton(&_coreInstanceDataAry[/* idxCore */ 0].stateSW1);
    else if(button == lbd_bt_button_SW2)
        return (uint32_t)osGetButton(&_coreInstanceDataAry[/* idxCore */ 0].stateSW2);
    else
    {
        /* Abort this system call and the calling user task and count this event as an
           error in the process the failing task belongs to. */
        rtos_osSystemCallBadArgument();
    }
} /* End of lbd_scSmplHdlr_getButton_core0 */
#endif




#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
/**
 * Sample implementation of a system call of conformance class "simple". Such a system call
 * can already be implemented in C but it needs to be run with all interrupts suspended. It
 * cannot be preempted. Suitable for short running services only.\n
 *   Here we use the concept to implement an input function for the two buttons on core 1
 * on the eval board DEVKIT-MPC5748G.
 *   @return
 * The value of the argument \a isOn is returned.
 *   @param pidOfCallingTask
 * Process ID of calling user task.
 *   @param led
 * The LED to address to.
 *   @param isOn
 * Switch the selected LED either on or off.
 */
uint32_t lbd_scSmplHdlr_getButton_core1( uint32_t pidOfCallingTask ATTRIB_UNUSED
                                       , lbd_button_t button
                                       )
{
    /* A safe, "trusted" implementation needs to double check the selected button in order to
       avoid undesired access to I/O ports other than the two true button ports on the eval
       board. */
    assert(rtos_osGetIdxCore() == 1);
    if(button == lbd_bt_button_SW1)
        return (uint32_t)osGetButton(&_coreInstanceDataAry[/* idxCore */ 1].stateSW1);
    else if(button == lbd_bt_button_SW2)
        return (uint32_t)osGetButton(&_coreInstanceDataAry[/* idxCore */ 1].stateSW2);
    else
    {
        /* Abort this system call and the calling user task and count this event as an
           error in the process the failing task belongs to. */
        rtos_osSystemCallBadArgument();
    }
} /* End of lbd_scSmplHdlr_getButton_core1 */
#endif




#if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
/**
 * Sample implementation of a system call of conformance class "simple". Such a system call
 * can already be implemented in C but it needs to be run with all interrupts suspended. It
 * cannot be preempted. Suitable for short running services only.\n
 *   Here we use the concept to implement an input function for the two buttons on core 2
 * on the eval board DEVKIT-MPC5748G.
 *   @return
 * The value of the argument \a isOn is returned.
 *   @param pidOfCallingTask
 * Process ID of calling user task.
 *   @param led
 * The LED to address to.
 *   @param isOn
 * Switch the selected LED either on or off.
 */
uint32_t lbd_scSmplHdlr_getButton_core2( uint32_t pidOfCallingTask ATTRIB_UNUSED
                                       , lbd_button_t button
                                       )
{
    /* A safe, "trusted" implementation needs to double check the selected button in order to
       avoid undesired access to I/O ports other than the two true button ports on the eval
       board. */
    assert(rtos_osGetIdxCore() == 2);
    if(button == lbd_bt_button_SW1)
        return (uint32_t)osGetButton(&_coreInstanceDataAry[/* idxCore */ 2].stateSW1);
    else if(button == lbd_bt_button_SW2)
        return (uint32_t)osGetButton(&_coreInstanceDataAry[/* idxCore */ 2].stateSW2);
    else
    {
        /* Abort this system call and the calling user task and count this event as an
           error in the process the failing task belongs to. */
        rtos_osSystemCallBadArgument();
    }
} /* End of lbd_scSmplHdlr_getButton_core2 */
#endif




/**
 * Get the current status of button SW1. This is the switch, which is labeled both on the
 * PCB, "SW1_PA3" and "SW4". This makes it potentially dangerous to mix up the switch with
 * the reset button on the board, which is labeled "RESET" and "SW1".
 *   @return
 * \a true if button SW1 is currently pressed, \a false otherwise. This is the debounced
 * read value from the GPIO.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception. User task code can consider using
 * lbd_getButton() instead.
 */
bool lbd_osGetButtonSw1(void)
{
    assert(rtos_osGetIdxCore() < sizeOfAry(_coreInstanceDataAry));
    return osGetButton(&_coreInstanceDataAry[rtos_osGetIdxCore()].stateSW1);
    
} /* End of lbd_osGetButtonSw1 */




/**
 * Get the current status of button SW2.
 *   @return
 * \a true if button SW2 is currently pressed, \a false otherwise. This is the debounced
 * read value from the GPIO.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception. User task code can consider using
 * lbd_getButton() instead.
 */
bool lbd_osGetButtonSw2(void)
{
    assert(rtos_osGetIdxCore() < sizeOfAry(_coreInstanceDataAry));
    return osGetButton(&_coreInstanceDataAry[rtos_osGetIdxCore()].stateSW2);

} /* End of lbd_osGetButtonSw2 */




/**
 * Regularly called step function of the I/O driver. This function needs to be called from
 * a regular 1ms operating system task. The button states are read and a callback is
 * invoked in case of a state change.
 *   @remark
 * On a multi-core implementation, this function needs to be called from all cores, which
 * want to make use of the on-button-change callback.
 */
void lbd_osTask1ms(void)
{
    /* The state infomation is core dependent. This way, each core can get its own
        notifications. */
    assert(rtos_osGetIdxCore() < sizeOfAry(_coreInstanceDataAry));
    stateDriver_t * const pCoreInstanceData = &_coreInstanceDataAry[rtos_osGetIdxCore()];
    
    const uint8_t lastStateButtons = pCoreInstanceData->lastStateButtons;

    /* Polling the buttons is useless if we have no notification callback. */
    if(pCoreInstanceData->onButtonChangeCallback.addrTaskFct != 0)
    {
        /* Read the current button status. */
        const uint8_t stateButtons = (lbd_osGetButtonSw1()? 0x01: 0x0)
                                     | (lbd_osGetButtonSw2()? 0x10: 0x0)
                                     ;

        if(stateButtons != lastStateButtons)
        {
            const uint8_t comp = stateButtons
                                 | ((stateButtons ^ lastStateButtons) << 1)  /* changed  */
                                 | ((stateButtons & ~lastStateButtons) << 2) /* went on  */
                                 | ((~stateButtons & lastStateButtons) << 3) /* went off */
                                 ;
            rtos_osRunTask(&pCoreInstanceData->onButtonChangeCallback, /* taskParam */ comp);
            pCoreInstanceData->lastStateButtons = stateButtons;
        }
    } /* End if(Callback demanded by system configuration?) */    
} /* End of lbd_osTask1ms */

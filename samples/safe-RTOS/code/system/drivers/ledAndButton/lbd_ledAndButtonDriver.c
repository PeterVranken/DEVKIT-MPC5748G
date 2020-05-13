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
 *   lbd_scSmplHdlr_getButton
 *   lbd_osGetButtonSw1
 *   lbd_osGetButtonSw2
 *   lbd_osTask1ms
 * Local functions
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
#include "rtos_ivorHandler.h"
#include "lbd_ledAndButtonDriver_defSysCalls.h"
#include "lbd_ledAndButtonDriver.h"


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */

/** The descriptor of a user task, which is run as notification in case of a button state
    change. */
static rtos_taskDesc_t SDATA_OS(_onButtonChangeCallback) =
            { .addrTaskFct = 0
            , .PID = 0
            , .tiTaskMax = RTOS_TI_US2TICKS(1000)
            };

/*
 * Function implementation
 */

/**
 * Initialization of LED driver. The GPIO ports are defined to become outputs and the
 * output values are set such that the LEDs are shut off.
 *   @param onButtonChangeCallback
 * The I/O driver offers the service to poll the current button input status and to inform
 * the application code about any change. The notification is done per callback. Pass NULL
 * if no notification is desired.
 *   @param PID
 * The ID of the process to run the callback in. The value doesn't care if \a
 * onButtonChangeCallback is NULL. The range is 1 ... #RTOS_NO_PROCESSES. It is checked by
 * assertion.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user 
 * code will lead to a privileged exception.
 */
void lbd_osInitLEDAndButtonDriver( lbd_onButtonChangeCallback_t onButtonChangeCallback
                                 , unsigned int PID
                                 )
{
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

    /* Save optional callback in global variable. */
    if(onButtonChangeCallback != NULL)
    {
        /* Here we are in trusted code. The passed PID is static configuration data and
           cannot produce an occasional failure. Checking by assertion is appropriate. */
        assert(PID > 0  &&  PID < RTOS_NO_PROCESSES);
        _onButtonChangeCallback.PID = PID;

        _onButtonChangeCallback.addrTaskFct = (uintptr_t)onButtonChangeCallback;
        
        /* A difficult descision: Shall we generally set a time budget for all user code?
           This may rarely produce an exception, which can leave the user code in an
           inconsistent state, such that subsequent failures result. Even in a safe system, a
           potentially not returning user function may be not critical: There will be a
           higher prioritized supervisory task to recognize this situation and to bring the
           system in a safe state. */
        assert(_onButtonChangeCallback.tiTaskMax > 0);
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




/**
 * Sample implementation of a system call of conformance class "simple". Such a system call
 * can already be implemented in C but it needs to be run with all interrupts suspended. It
 * cannot be preempted. Suitable for short running services only.\n
 *   Here we use the concept to implement an input function for the two buttons on the eval
 * board TRK-USB-MPC5643L.
 *   @return
 * The value of the argument \a isOn is returned.
 *   @param pidOfCallingTask
 * Process ID of calling user task.
 *   @param led
 * The LED to address to.
 *   @param isOn
 * Switch the selected LED either on or off.
 */
uint32_t lbd_scSmplHdlr_getButton( uint32_t pidOfCallingTask ATTRIB_UNUSED
                                 , lbd_button_t button
                                 )
{
    /* A safe, "trusted" implementation needs to double check the selected button in order to
       avoid undesired access to I/O ports other than the two true button ports on the eval
       board. */
    if(button == lbd_bt_button_SW1  ||  button == lbd_bt_button_SW2)
        return (uint32_t)lbd_osGetButton(button);
    else
    {
        /* Abort this system call and the calling user task and count this event as an
           error in the process the failing task belongs to. */
        rtos_osSystemCallBadArgument();
    }
} /* End of lbd_scSmplHdlr_getButton */



/**
 * Get the current status of button SW1. This is the switch, which is labeled both on the
 * PCB, "SW1_PA3" and "SW4". This makes it potentially dangeraous to mix up the switch with
 * the reset button on the board, which is labeled "RESET" and "SW1".
 *   @return
 * \a true if button SW1 is currently pressed, \a false otherwise. This is the debounced
 * read value from the GPIO.
 *   @param button
 * The enumeration value to identify a button.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception. User task code can consider using
 * lbd_getButton() instead.
 */
bool lbd_osGetButtonSw1(void)
{
    _Static_assert( LBD_MAX_CNT_BTN_DEBOUNCE >= 1  && LBD_MAX_CNT_BTN_DEBOUNCE <= 50
                  , "Debounce time configuration out of range"
                  );

    /* The contribution to the debouncing depends on th current 0/1 reading of the GPIO
       input buffer. */
    const signed int actState =
                *(((__IO uint8_t*)&SIUL2->GPDI[0])+((unsigned)lbd_bt_button_SW1)) != 0? 1: -1;

    static signed int SBSS_OS(cntDebounce_) = 0;
    static bool SBSS_OS(buttonState_) = false;
    cntDebounce_ += actState;
    if(cntDebounce_ >= LBD_MAX_CNT_BTN_DEBOUNCE)
    {
        cntDebounce_ = LBD_MAX_CNT_BTN_DEBOUNCE;
        buttonState_ = true;
    }
    else if(cntDebounce_ <= -LBD_MAX_CNT_BTN_DEBOUNCE)
    {
        cntDebounce_ = -LBD_MAX_CNT_BTN_DEBOUNCE;
        buttonState_ = false;
    }
    return buttonState_;

} /* End of lbd_osGetButtonSw1 */




/**
 * Get the current status of button SW2.
 *   @return
 * \a true if button SW2 is currently pressed, \a false otherwise. This is the debounced
 * read value from the GPIO.
 *   @param button
 * The enumeration value to identify a button.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception. User task code can consider using
 * lbd_getButton() instead.
 */
bool lbd_osGetButtonSw2(void)
{
    _Static_assert( LBD_MAX_CNT_BTN_DEBOUNCE >= 1  && LBD_MAX_CNT_BTN_DEBOUNCE <= 50
                  , "Debounce time configuration out of range"
                  );

    /* The contribution to the debouncing depends on th current 0/1 reading of the GPIO
       input buffer. */
    const signed int actState =
                *(((__IO uint8_t*)&SIUL2->GPDI[0])+((unsigned)lbd_bt_button_SW2)) != 0? 1: -1;

    static signed int SBSS_OS(cntDebounce_) = 0;
    static bool SBSS_OS(buttonState_) = false;
    cntDebounce_ += actState;
    if(cntDebounce_ >= LBD_MAX_CNT_BTN_DEBOUNCE)
    {
        cntDebounce_ = LBD_MAX_CNT_BTN_DEBOUNCE;
        buttonState_ = true;
    }
    else if(cntDebounce_ <= -LBD_MAX_CNT_BTN_DEBOUNCE)
    {
        cntDebounce_ = -LBD_MAX_CNT_BTN_DEBOUNCE;
        buttonState_ = false;
    }
    return buttonState_;

} /* End of lbd_osGetButtonSw2 */




/**
 * Regularly called step function of the I/O driver. This function needs to be called from
 * a regular 1ms operating system task. The button states are read and a callback is
 * invoked in case of a state change.
 */
void lbd_osTask1ms(void)
{
    /* Polling the buttons is useless if we have no notification callback. */
    if(_onButtonChangeCallback.addrTaskFct != 0)
    {
        /* Read the current button status. */
        const uint8_t stateButtons = (lbd_osGetButtonSw1()? 0x01: 0x0)
                                     | (lbd_osGetButtonSw2()? 0x10: 0x0)
                                     ;

        /* Compare with last state and invoke callback on any difference. */
        static uint8_t SBSS_OS(lastStateButtons_) = 0;
        
        if(stateButtons != lastStateButtons_)
        {
            const uint8_t comp = stateButtons
                                 | ((stateButtons ^ lastStateButtons_) << 1)  /* changed  */
                                 | ((stateButtons & ~lastStateButtons_) << 2) /* went on  */
                                 | ((~stateButtons & lastStateButtons_) << 3) /* went off */
                                 ;
            rtos_osRunTask(&_onButtonChangeCallback, /* taskParam */ comp);
            lastStateButtons_ = stateButtons;
        }
    } /* End if(Callback demanded by system configuration?) */    
} /* End of lbd_osTask1ms */

#ifndef LBD_LEDANDBUTTONDRIVER_INCLUDED
#define LBD_LEDANDBUTTONDRIVER_INCLUDED
/**
 * @file lbd_ledAndButtonDriver.h
 * Definition of global interface of module lbd_ledAndButtonDriver.\n
 *   Simple hardware driver for the LEDs and buttons on the eval board DEVKIT-MPC5748G.
 *
 * Copyright (C) 2017-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   lbd_setLED
 *   lbd_osSetLED
 *   lbd_getButton
 *   lbd_osGetButton
 */
/*
 * Include files
 */

#include "MPC5748G.h"
#include "typ_types.h"
#include "rtos.h"


/*
 * Defines
 */

/** The debounce time of the read process of the button states in ticks, where one tick is
    the time between two invokations of interface function lbd_osGetButton.
      The range is 2 .. 100. */
#define LBD_DEBOUNCE_TIME_BUTTONS   4

/** Index of implemented system call for switching an LED on or off. */
#define LBD_SYSCALL_SET_LED         25

/** Index of system call for getting the button state, lbd_scSmplHdlr_getButton(). */
#define LBD_SYSCALL_GET_BUTTON      26

/*
 * Global type definitions
 */

/** The list of available LEDs. */
typedef enum lbd_led_t
    { lbd_led_0_DS11 = 4    /// The value is the SIUL2 index of the bottom most LED, DS11, PA4
    , lbd_led_1_DS10 = 0    /// The value is the SIUL2 index of the second LED, DS10, PA0
    , lbd_led_2_DS9  = 148  /// The value is the SIUL2 index of DS9 at PJ4
    , lbd_led_3_DS8  = 117  /// The value is the SIUL2 index of DS8 at PH5
    , lbd_led_4_DS7  = 36   /// The value is the SIUL2 index of DS at PC4
    , lbd_led_5_DS6  = 125  /// The value is the SIUL2 index of DS at PH13
    , lbd_led_6_DS5  = 7    /// The value is the SIUL2 index of DS at PA7
    , lbd_led_7_DS4  = 10   /// The value is the SIUL2 index of DS at PA10
    } lbd_led_t;

/** The list of available buttons. */
typedef enum lbd_button_t
    { lbd_bt_button_SW1 = 3 	/// The value is the SIUL2 index of button SW1, port PA3
    , lbd_bt_button_SW2 = 76  	/// The value is the SIUL2 index of button SW2, port PE12
    } lbd_button_t;


/** The masks to filter the separate bits in argument \a buttonState of a function of type
    \a lbd_onButtonChangeCallback_t. */
typedef enum lbd_buttonStateMask_t
{
    lbd_btStMask_btnSw1_isOn = 0x01         /** Current state of button SW1. */
    , lbd_btStMask_btnSw1_changed = 0x02    /** Button SW1 went either on or off. */
    , lbd_btStMask_btnSw1_down = 0x04       /** Button SW1 went on. */
    , lbd_btStMask_btnSw1_released = 0x08   /** Button SW1 went off. */

    , lbd_btStMask_btnSw2_isOn = 0x10       /** Current state of button SW2. */
    , lbd_btStMask_btnSw2_changed = 0x20    /** Button SW2 went either on or off. */
    , lbd_btStMask_btnSw2_down = 0x40       /** Button SW2 went on. */
    , lbd_btStMask_btnSw2_released = 0x80   /** Button SW2 went off. */

} lbd_buttonStateMask_t;


/** Type of function pointer to an optional callback, invoked whenever the button status
    changes. See lbd_osInitLEDAndButtonDriver().\n
      The callback is invoked in the context of the specified process and at the same
    priority level as this I/O driver, i.e. the level at which lbd_osTask1ms() is regularly
    invoked.
      @return
    The implementation can return a neagtive value if an error occurs. This would be
    counted as failure event in process PID. Any value greater or equal to zero doesn't
    have any effect.
      @param PID
    ID of process, which the callback is invoked in. Will be redundant information in most
    cases.
      @param buttonState
    The two LSBits 0 and 4 indicate the current state of the buttons lbd_bt_button_SW1 and
    lbd_bt_button_SW2, respectively: A set bit for button pressed, a zero bit otherwise.
    The remaining bits indictae the changes compared to the previous callback invocation;
    see type \a lbd_buttonStateMask_t for details. */
typedef int32_t (*lbd_onButtonChangeCallback_t)( uint32_t PID
                                               , uint8_t buttonState
                                               );

/*
 * Global data declarations
 */

/*
 * Global inline functions
 */

/**
 * Switch a single LED on or off.
 *   @param led
 * The enumeration value to identify an LED.
 *   @param isOn
 * \a true to switch it on \a false to switch it off.
 *   @remark
 * There are no race-conditions between different LEDs. You need to consider using a
 * critical section only, if one and the same LED is served from different interrupt
 * contexts. This is not handled by this driver.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception. See lbd_setLED() for the user mode variant of
 * the function.
 */
static inline void lbd_osSetLED(lbd_led_t led, bool isOn)
{
    /* Toggle the LED state.
       Unfortunately the MCU header only models the 32 Bit access, which involves four
       port bits at once. We need to recompute the register address so that we can
       apply a single Byte access. */
    *(((__IO uint8_t*)&SIUL2->GPDO[0])+((unsigned)led)) = isOn? 0: 1;
    
} /* End of lbd_osSetLED */



/**
 * Switch a single LED on or off. This is a system call to make the LED I/O driver
 * accessible from a user task. It has the same functionality as lbd_osSetLED().
 *   @param led
 * The enumeration value to identify an LED.
 *   @param isOn
 * \a true to switch it on \a false to switch it off.
 *   @remark
 * There are no race-conditions between different LEDs. You need to consider using a
 * critical section only, if one and the same LED is served from different interrupt
 * contexts. This is not handled by this driver.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from
 * OS code will lead to undefined behavior.
 */
static inline void lbd_setLED(lbd_led_t led, bool isOn)
{
    rtos_systemCall(LBD_SYSCALL_SET_LED, led, isOn);

} /* End of lbd_setLED */



/**
 * Get the current status of a button.
 *   @return
 * \a true if button is currently pressed, \a false otherwise. This is the debounced read
 * value from the GPIO.
 *   @param button
 * The enumeration value to identify a button.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception. User task code can consider using
 * lbd_getButton() instead.
 */
static inline bool lbd_osGetButton(lbd_button_t button)
{
    if(button == lbd_bt_button_SW1)
    {
        extern bool lbd_osGetButtonSw1(void);
        return lbd_osGetButtonSw1();
    }
    else
    {
        assert(button == lbd_bt_button_SW2);
        extern bool lbd_osGetButtonSw2(void);
        return lbd_osGetButtonSw2();
    }
} /* End of lbd_osGetButton */



/**
 * Get the current status of a button.
 *   @return
 * \a true if button is currently pressed, \a false otherwise. This is the debounced read
 * value from the GPIO.
 *   @param button
 * The enumeration value to identify a button.
 *   @remark
 * The function is implemented as static inline. This implies that any using code location
 * will get its own, irrelated debounce counter. One logical client of a button should not
 * have more than one code location to read its current value, otherwise its debouncing
 * won't function as intended.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from
 * OS code will lead to undefined behavior.
 */
static inline bool lbd_getButton(lbd_button_t button)
{
    return (bool)rtos_systemCall(LBD_SYSCALL_GET_BUTTON, button);

} /* End of lbd_getButton */



/*
 * Global prototypes
 */

/** Initialization of LED driver. */
void lbd_osInitLEDAndButtonDriver( lbd_onButtonChangeCallback_t onButtonChangeCallback_core0
                                 , unsigned int PID_core0
                                 , lbd_onButtonChangeCallback_t onButtonChangeCallback_core1
                                 , unsigned int PID_core1
                                 , lbd_onButtonChangeCallback_t onButtonChangeCallback_core2
                                 , unsigned int PID_core2
                                 , unsigned int tiMaxTimeInUs
                                 );

/** Regularly called step function of the I/O driver. */
void lbd_osTask1ms(void);

/** Get the status of button SW1_PA3. */
bool lbd_osGetButtonSw1(void);

/** Get the status of button SW2_PE12. */
bool lbd_osGetButtonSw2(void);

#endif  /* LBD_LEDANDBUTTONDRIVER_INCLUDED */

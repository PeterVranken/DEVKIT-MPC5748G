#ifndef LBD_LEDANDBUTTONDRIVER_INCLUDED
#define LBD_LEDANDBUTTONDRIVER_INCLUDED
/**
 * @file lbd_ledAndButtonDriver.h
 * Definition of global interface of module lbd_ledAndButtonDriver.\n
 *   Simple hardware driver for the LEDs and buttons on the eval board DEVKIT-MPC5748G.
 *
 * Copyright (C) 2017-2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "siu_siuPortDriver.h"


/*
 * Defines
 */

/** The debounce time of the read process of the button states in ticks, where one tick is
    the time between two invokations of interface function lbd_osGetButton.
      The range is 2 .. 100. Note, the value is a signed despite of the positive range. */
#define LBD_DEBOUNCE_TIME_BUTTONS   4

/** Index of implemented system call for switching an LED on or off. */
#define LBD_SYSCALL_SET_LED         25u

/** Index of system call for getting the button state, lbd_scSmplHdlr_getButton(). */
#define LBD_SYSCALL_GET_BUTTON      26u

/** These defines allow to enable the compilation of the LED API for any of the LEDs on the
    PCB. If the according port clashes with the application software running on the board
    then the LED should be disabled by setting the macro to 0 and the LED won't be
    accessible through this driver. Here for LED 0. */
#define LBD_ENABLE_LED_0_DS11       1
#define LBD_ENABLE_LED_1_DS10       1   /** Enable the use of LED 1. */
#define LBD_ENABLE_LED_2_DS9        1   /** Enable the use of LED 2. */
#define LBD_ENABLE_LED_3_DS8        1   /** Enable the use of LED 3. */
#define LBD_ENABLE_LED_4_DS7        1   /** Enable the use of LED 4. */
#define LBD_ENABLE_LED_5_DS6        1   /** Enable the use of LED 5. */
#define LBD_ENABLE_LED_6_DS5        1   /** Enable the use of LED 6. */
#define LBD_ENABLE_LED_7_DS4        1   /** Enable the use of LED 7. */

/** These defines allow to enable the compilation of the button API for any of the user
    buttons on the PCB. If the according port clashes with the application software running
    on the board then the button should be disabled by setting the macro to 0 and it won't
    be accessible through this driver. Here for button SW1. */
#define LBD_ENABLE_BUTTON_SW1       1
#define LBD_ENABLE_BUTTON_SW2       1   /** Here for button SW2. */


/** The number of LEDs, which have been enabled at compile-time for SW use. */
#define LBD_NO_ENABLED_LEDS                                                         \
            (LBD_ENABLE_LED_0_DS11 + LBD_ENABLE_LED_1_DS10 + LBD_ENABLE_LED_2_DS9   \
             + LBD_ENABLE_LED_3_DS8 + LBD_ENABLE_LED_4_DS7 + LBD_ENABLE_LED_5_DS6   \
             + LBD_ENABLE_LED_6_DS5 + LBD_ENABLE_LED_7_DS4)

/** The number of user buttons, which have been enabled at compile-time for SW use. */
#define LBD_NO_ENABLED_BUTTONS      (LBD_ENABLE_BUTTON_SW1 + LBD_ENABLE_BUTTON_SW2)


/*
 * Global type definitions
 */

#if LBD_NO_ENABLED_LEDS > 0

/** The list of available LEDs. */
typedef enum lbd_led_t
    {
#if LBD_ENABLE_LED_0_DS11 == 1
        lbd_led_0_DS11 = 4,  /// The value is the SIUL2 index of the bottom most LED, DS11, PA4
#endif
#if LBD_ENABLE_LED_1_DS10 == 1
        lbd_led_1_DS10 = 0,  /// The value is the SIUL2 index of the second LED, DS10, PA0
#endif
#if LBD_ENABLE_LED_2_DS9 == 1
        lbd_led_2_DS9  = 148,/// The value is the SIUL2 index of DS9 at PJ4
#endif
#if LBD_ENABLE_LED_3_DS8 == 1
        lbd_led_3_DS8  = 117,/// The value is the SIUL2 index of DS8 at PH5
#endif
#if LBD_ENABLE_LED_4_DS7 == 1
        lbd_led_4_DS7  = 36, /// The value is the SIUL2 index of DS at PC4
#endif
#if LBD_ENABLE_LED_5_DS6 == 1
        lbd_led_5_DS6  = 125,/// The value is the SIUL2 index of DS at PH13
#endif
#if LBD_ENABLE_LED_6_DS5 == 1
        lbd_led_6_DS5  = 7,  /// The value is the SIUL2 index of DS at PA7
#endif
#if LBD_ENABLE_LED_7_DS4 == 1
        lbd_led_7_DS4  = 10, /// The value is the SIUL2 index of DS at PA10
#endif
    } lbd_led_t;

#endif /* #if At least one LED is in use */


#if LBD_NO_ENABLED_BUTTONS > 0

/** The list of available buttons. */
typedef enum lbd_button_t
    {
#if LBD_ENABLE_BUTTON_SW1 == 1
        lbd_bt_button_SW1 = 3,  /// The value is the SIUL2 index of button SW1, port PA3
#endif
#if LBD_ENABLE_BUTTON_SW2 == 1
        lbd_bt_button_SW2 = 76, /// The value is the SIUL2 index of button SW2, port PE12
#endif
    } lbd_button_t;


/** The masks to filter the separate bits in argument \a buttonState of a function of type
    \a lbd_onButtonChangeCallback_t. */
typedef enum lbd_buttonStateMask_t
{
#if LBD_ENABLE_BUTTON_SW1 == 1
    lbd_btStMask_btnSw1_isOn = 0x01u,       /** Current state of button SW1. */
    lbd_btStMask_btnSw1_changed = 0x02u,    /** Button SW1 went either on or off. */
    lbd_btStMask_btnSw1_down = 0x04u,       /** Button SW1 went on. */
    lbd_btStMask_btnSw1_released = 0x08u,   /** Button SW1 went off. */
#endif
#if LBD_ENABLE_BUTTON_SW2 == 1
    lbd_btStMask_btnSw2_isOn = 0x10u,       /** Current state of button SW2. */
    lbd_btStMask_btnSw2_changed = 0x20u,    /** Button SW2 went either on or off. */
    lbd_btStMask_btnSw2_down = 0x40u,       /** Button SW2 went on. */
    lbd_btStMask_btnSw2_released = 0x80u,   /** Button SW2 went off. */
#endif
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

#endif /* #if At least one button is in use */


/*
 * Global data declarations
 */

/*
 * Global inline functions
 */

#if LBD_NO_ENABLED_LEDS > 0

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
    /* Set the LED state. The GPIO pin requires inversion, the LED is connected from port
       to Vcc. */
    siu_osSetGPIO(/* idxPort */ (unsigned)led, isOn? false: true);

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

#endif /* #if At least one LED is in use */


#if LBD_NO_ENABLED_BUTTONS > 0

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
    bool isPressed = false;
#if LBD_ENABLE_BUTTON_SW1 == 1
    if(button == lbd_bt_button_SW1)
    {
        extern bool lbd_osGetButtonSw1(void);
        isPressed = lbd_osGetButtonSw1();
    }
#endif
#if LBD_ENABLE_BUTTON_SW2 == 1
    if(button == lbd_bt_button_SW2)
    {
        extern bool lbd_osGetButtonSw2(void);
        isPressed = lbd_osGetButtonSw2();
    }
#endif

    return isPressed;
    
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

#endif /* #if At least one button is in use */


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

#if LBD_NO_ENABLED_BUTTONS > 0
/** Regularly called step function of the I/O driver. */
void lbd_osTask1ms(void);
#endif /* #if At least one button is in use */

#if LBD_ENABLE_BUTTON_SW1 == 1
/** Get the status of button SW1_PA3. */
bool lbd_osGetButtonSw1(void);
#endif

#if LBD_ENABLE_BUTTON_SW2 == 1
/** Get the status of button SW2_PE12. */
bool lbd_osGetButtonSw2(void);
#endif

#endif  /* LBD_LEDANDBUTTONDRIVER_INCLUDED */

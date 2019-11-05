#ifndef LBD_LEDANDBUTTONDRIVER_INCLUDED
#define LBD_LEDANDBUTTONDRIVER_INCLUDED
/**
 * @file lbd_ledAndButtonDriver.h
 * Definition of global interface of module lbd_ledAndButtonDriver.
 * Simple hardware driver for the LEDs and buttons on the eval board DEVKIT-MPC5748G.
 *
 * Copyright (C) 2017-2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   lbd_initLEDAndButtonDriver
 *   lbd_setLED
 */
/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>

#include "MPC5748G.h"


/*
 * Defines
 */

/** The debounce time of the read process of the button states in ticks, where one tick is
    the time between two invokations of interface function lbd_getButton.
      The range is 2 .. 100. */
#define LBD_DEBOUNCE_TIME_BUTTONS   4

/* The debounce time of the read process of the button states is determined by this
   counter maximum. */
#define LBD_MAX_CNT_BTN_DEBOUNCE    ((LBD_DEBOUNCE_TIME_BUTTONS)/2)


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
    { lbd_bt_button_SW2 = 76 /// The value is the SIUL2 index of button SW2, port PE12
    , lbd_bt_button_SW4 = 3  /// The value is the SIUL2 index of button SW4, port PA3
    } lbd_button_t;
    

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
 */
static inline void lbd_setLED(lbd_led_t led, bool isOn)
{
    /* Toggle the LED state.
       Unfortunately the MCU header only models the 32 Bit access, which involves four
       port bits at once. We need to recompute the register address so that we can
       apply a single Byte access. */
    *(((__IO uint8_t*)&SIUL2->GPDO[(unsigned)led/4])+((unsigned)led%4)) = isOn? 0: 1;
    
} /* End of lbd_setLED */


/**
 * Initialization of LED driver. The GPIO ports are defined to become outputs and the
 * output values are set such that the LEDs are shut off.
 */
static inline void lbd_initLEDAndButtonDriver(void)
{
    /* LEDs are initially off. */
    lbd_setLED(lbd_led_0_DS11, /* isOn */ false);
    lbd_setLED(lbd_led_1_DS10, /* isOn */ false);
    lbd_setLED(lbd_led_2_DS9, /* isOn */ false);
    lbd_setLED(lbd_led_3_DS8, /* isOn */ false);
    lbd_setLED(lbd_led_4_DS7, /* isOn */ false);
    lbd_setLED(lbd_led_5_DS6, /* isOn */ false);
    lbd_setLED(lbd_led_6_DS5, /* isOn */ false);
    lbd_setLED(lbd_led_7_DS4, /* isOn */ false);
    
    /* Enable access to a user LED on the evlaution board (see
       DEVKIT-MPC5748G-Schematics.pdf). The reference from a port designation like PA4 to
       the related pin configuration register MSCR is found in the attachment
       IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx of the MCU reference
       manual. In this file, go to tab "IO Signal Table", row 36, for PA4. Column C gives
       us the index of the MSCR. Column D gives us 0 as "Source Signal Select" for function
       GPIO. */
#define INIT_LED(led)                                                                        \
    SIUL2->MSCR[led] =                                                                       \
            SIUL2_MSCR_SSS(0 /* GPIO */)                                                     \
                          | SIUL2_MSCR_SRC(0) /* Slew rate: slowest possible */              \
                          | SIUL2_MSCR_OBE(1) /* Enable output buffer */                     \
                          | SIUL2_MSCR_ODE(1) /* Enable open drain: LED connected to +3.3V */\
                          | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */                 \
                          | SIUL2_MSCR_APC(0) /* No analog I/O */                            \
                          | SIUL2_MSCR_IBE(0) /* Disable input buffer */                     \
                          | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */                \
                          | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */                 \
                          | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */   \
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

//    /* Unfortunately, the buttons are connected to inputs, that are not interrupt enabled.
//       We will have to poll the current input values.
//       0x100: Input buffer enable. */
//    SIU.PCR[lbd_bt_button_SW2].R = 0x0100;
//    SIU.PCR[lbd_bt_button_SW3].R = 0x0100;
    
} /* End of lbd_initLEDAndButtonDriver */


///**
// * Get the current status of button SW2.
// *   @return
// * \a true if button SW2 is currently pressed, \a false otherwise. This is the debounced
// * read value from the GPIO.
// *   @param button
// * The enumeration value to identify a button.
// *   @remark
// * The function is implemented as static inline. This implies that any using code location
// * will get its own, irrelated debounce counter. One logical client of a button should not
// * have more than one code location to read its current value, otherwise its debouncing
// * won't function as intended.
// */
//static inline bool lbd_getButtonSw2(void)
//{
//    _Static_assert( LBD_MAX_CNT_BTN_DEBOUNCE >= 1  && LBD_MAX_CNT_BTN_DEBOUNCE <= 50
//                  , "Debounce time configuration out of range"
//                  );
//
//    static int cntDebounce_ = 0;
//    static bool buttonState_ = false;
//    cntDebounce_ += SIU.GPDI[lbd_bt_button_SW2].B.PDI? -1: 1;
//    if(cntDebounce_ >= LBD_MAX_CNT_BTN_DEBOUNCE)
//    {
//        cntDebounce_ = LBD_MAX_CNT_BTN_DEBOUNCE;
//        buttonState_ = true;
//    }
//    else if(cntDebounce_ <= -LBD_MAX_CNT_BTN_DEBOUNCE)
//    {
//        cntDebounce_ = -LBD_MAX_CNT_BTN_DEBOUNCE;
//        buttonState_ = false;
//    }
//    return buttonState_;
//    
//} /* End of lbd_getButtonSw2 */
//
//
//
//
///**
// * Get the current status of button SW3.
// *   @return
// * \a true if button SW3 is currently pressed, \a false otherwise. This is the debounced
// * read value from the GPIO.
// *   @param button
// * The enumeration value to identify a button.
// *   @remark
// * The function is implemented as static inline. This implies that any using code location
// * will get its own, irrelated debounce counter. One logical client of a button should not
// * have more than one code location to read its current value, otherwise its debouncing
// * won't function as intended.
// */
//static inline bool lbd_getButtonSw3(void)
//{
//    static int cntDebounce_ = 0;
//    static bool buttonState_ = false;
//    cntDebounce_ += SIU.GPDI[lbd_bt_button_SW3].B.PDI? -1: 1;
//    if(cntDebounce_ >= LBD_MAX_CNT_BTN_DEBOUNCE)
//    {
//        cntDebounce_ = LBD_MAX_CNT_BTN_DEBOUNCE;
//        buttonState_ = true;
//    }
//    else if(cntDebounce_ <= -LBD_MAX_CNT_BTN_DEBOUNCE)
//    {
//        cntDebounce_ = -LBD_MAX_CNT_BTN_DEBOUNCE;
//        buttonState_ = false;
//    }
//    return buttonState_;
//    
//} /* End of lbd_getButtonSw3 */
//
//
//
//
///**
// * Get the current status of a button.
// *   @return
// * \a true if button is currently pressed, \a false otherwise. This is the debounced read
// * value from the GPIO.
// *   @param button
// * The enumeration value to identify a button.
// *   @remark
// * The function is implemented as static inline. This implies that any using code location
// * will get its own, irrelated debounce counter. One logical client of a button should not
// * have more than one code location to read its current value, otherwise its debouncing
// * won't function as intended.
// */
//static inline bool lbd_getButton(lbd_button_t button)
//{
//    if(button == lbd_bt_button_SW2)
//        return lbd_getButtonSw2();
//    else
//    {
//        assert(button == lbd_bt_button_SW3);
//        return lbd_getButtonSw3();
//    }
//} /* End of lbd_getButton */


/*
 * Global prototypes
 */



#endif  /* LBD_LEDANDBUTTONDRIVER_INCLUDED */

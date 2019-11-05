#ifndef MZB_MAIN_Z4B_INCLUDED
#define MZB_MAIN_Z4B_INCLUDED
/**
 * @file mzb_main_Z4B.h
 * Definition of global interface of module mzb_main_Z4B.c
 *
 * Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */


/*
 * Global type definitions
 */

/** The LEDs are used to indicate the activity of the main execution thread of the three
    cores. Here for core 0. */
enum { mzb_ledCore0Main = lbd_led_0_DS11 /** Core 0, activity in main */
     , mzb_ledCore1Main = lbd_led_1_DS10 /** Core 1, activity in main */
     , mzb_ledCore2Main = lbd_led_2_DS9  /** Core 2, activity in main */
     , mzb_ledCore0IrqPit1 = lbd_led_4_DS7 /** Core 0, 1ms IRQ */
     , mzb_ledCore0IrqPit2 = lbd_led_5_DS6 /** Core 0, 100us IRQ */
     , mzb_ledCore1IrqPit3 = lbd_led_6_DS5 /** Core 1, 10ms IRQ */
     , mzb_ledCore2IrqPit4 = lbd_led_7_DS4 /** Core 2, 10ms IRQ */
     };
     

/*
 * Global data declarations
 */

/** Counter, which is incremented in forever spinning main function running on core Z4B. */
extern volatile uint32_t mzb_cntMainLoopsCore1;

/** Counter of calls of PIT 3 interrupts. */
extern volatile unsigned long mzb_cntIntPIT3;


/*
 * Global prototypes
 */

/** Main entry point of code execution for core Z4B. */
void mzb_main_Z4B(int noArgs, const char *argAry[]);

#endif  /* MZB_MAIN_Z4B_INCLUDED */

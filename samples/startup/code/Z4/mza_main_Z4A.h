#ifndef MZA_MAIN_Z4B_INCLUDED
#define MZA_MAIN_Z4B_INCLUDED
/**
 * @file mza_main_Z4A.h
 * Definition of global interface of module mza_main_Z4A.c
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
enum { mza_ledCore0Main = lbd_led_0_DS11 /** Core 0, activity in main */
     , mza_ledCore1Main = lbd_led_1_DS10 /** Core 1, activity in main */
     , mza_ledCore2Main = lbd_led_2_DS9  /** Core 2, activity in main */
     , mza_ledCore0IrqPit1 = lbd_led_4_DS7 /** Core 0, 1ms IRQ */
     , mza_ledCore0IrqPit2 = lbd_led_5_DS6 /** Core 0, 100us IRQ */
     , mza_ledCore1IrqPit3 = lbd_led_6_DS5 /** Core 1, 10ms IRQ */
     , mza_ledCore2IrqPit4 = lbd_led_7_DS4 /** Core 2, 10ms IRQ */
     };
     

/** A data object shared between core Z4A and Z4B for communication purpose. */
typedef struct mza_msgZ4AToZ4B_t
{
    /** Two values, which should always sum up to zero, so that receiver can validate the
        data. */
    signed int msgAry[2];
    
    /** A flag to indicate new data to the receiver. The flag is written by the sender and
        read-only to the receiver. A value change signals new data. */
    uint8_t newDataAvailable;
    
    /** A flag to acknowledge new data to the sender. The flag is written by the receiver and
        read-only to the sender. A value change signals "ready for new data". */
    uint8_t dataAcknowledge;

} mza_msgZ4AToZ4B_t;
    

/*
 * Global data declarations
 */

/** A data object shared between core Z4A and Z4B for communication purpose. */
extern mza_msgZ4AToZ4B_t TYP_SECTION(.uncached.data) mza_msgZ4AToZ4B;

/** Test of intercore critical section: The critical section object. */
extern mtx_intercoreCriticalSection_t mza_csTestOfCriticalSection;

/** Test of intercore critical section: Some protected data. */
extern TYP_SECTION(.uncached.data) volatile unsigned int mza_csTestData1;

/** Test of intercore critical section: Some protected data. */
extern TYP_SECTION(.uncached.data) volatile unsigned int mza_csTestData2;


/*
 * Global prototypes
 */

/** Some floating point operations in order to test the compiler configuration. */
void mza_testZ4FloatingPointConfiguration(void);

/** Main entry point of code execution for core Z4A. */
int main(int noArgs, const char *argAry[]);

#endif  /* MZA_MAIN_Z4B_INCLUDED */

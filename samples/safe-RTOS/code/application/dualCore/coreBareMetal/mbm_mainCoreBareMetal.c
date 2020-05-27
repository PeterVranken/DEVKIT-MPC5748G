/**
 * @file mbm_mainCoreBareMetal.c
 * C entry function for the remaining core, which doesn't run safe-RTOS. It registers some
 * ISRs and has a main loop for processing. It drives the last available user LED on the
 * evaluation board.\n
 *
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   mbm_mainCoreBareMetal
 * Local functions
 *   taskInitProcess
 *   task1ms
 *   taskOs1ms
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "ccl_configureClocks.h"
#include "xbs_crossbarSwitch.h"

#include "rtos.h"
#include "gsl_systemLoad.h"
#include "lbd_ledAndButtonDriver.h"
#include "sio_serialIO.h"
#include "del_delay.h"
#include "stm_systemTimer.h"
#include "mbm_mainCoreBareMetal.h"


/*
 * Defines
 */
 
/** The demo can be compiled with a ground load. Most tasks produce some CPU load if this
    switch is set to 1. */
#define ISRs_PRODUCE_GROUND_LOAD   1

/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** Counter of cycles of infinite main loop. */
volatile unsigned long SECTION(.uncached.OS.mbm_cntIsrIdle) mbm_cntMain = 0;

#if 0
/** Counter of cyclic 1ms user isr. */
volatile unsigned long SECTION(.uncached.OS.mbm_cntIsr1ms) mbm_cntIsr1ms = 0;  
#endif

/** The average CPU load produced by all ISRs in tens of percent. */ 
volatile unsigned int SECTION(.uncached.OS.mbm_cpuLoad) mbm_cpuLoadCoreBareMetal = 1000;


/*
 * Function implementation
 */

/**
 * C entry function main. Is used for the remaining core, which doesn't run safe-RTOS in
 * this sample. It depends on configuration macros #RTOS_RUN_SAFE_RTOS_ON_CORE_1 and
 * #RTOS_RUN_SAFE_RTOS_ON_CORE_2, which one that is. A core not running safe-RTOS, it can
 * still be used without an RTOS.
 *   @param noArgs
 * Number of arguments in \a argAry. Is actually always equal to one.
 *   @param argAry
 * Array of string arguments to the function. Actually, always a single string which equals
 * the name of the core, which is started.
 *   @remark
 * Actually, the function is a _Noreturn. We don't declare it as such in order to avoid a
 * compiler warning. 
 */
void /* _Noreturn */ mbm_mainCoreBareMetal(int noArgs ATTRIB_DBG_ONLY, const char *argAry[])
{
    assert( noArgs == 1
#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
            &&  strcmp(argAry[0], "Z2") == 0
#elif RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
            &&  strcmp(argAry[0], "Z4B") == 0
#endif
          );

    /* The "main" function of a bare metal application on a core not running sfae-RTOS is
       placed in infinte loop; C's main must never return. */
    while(true)
    {
        /* Compute the average CPU load. Note, this operation lasts about 1.5s and has a
           significant impact on the cycling speed of this infinite loop. Furthermore, it
           measures only the load produced by the interrupts but not that of the rest of
           the code in the idle loop. */
        mbm_cpuLoadCoreBareMetal = gsl_osGetSystemLoad();

        static bool SBSS_OS(isOn_) = false;
        lbd_osSetLED(lbd_led_4_DS7, isOn_ = !isOn_);

        /* Make spinning of the idle task observable in the debugger. */
        ++ mbm_cntMain;

    } /* End of inifinite idle loop of bare metal application. */

} /* End of mbm_mainCoreBareMetal */

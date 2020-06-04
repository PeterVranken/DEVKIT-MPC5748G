/**
 * @file mbm_mainCoreBareMetal.c
 * C entry function for the remaining core, which doesn't run safe-RTOS. It registers some
 * ISRs and has a main loop for processing. It drives the last available user LED on the
 * evaluation board.
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
 *   isrPit4
 *   isrPit5
 *   isrPit6
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

/** Counter of regular 1ms user isr. */
volatile unsigned long SECTION(.uncached.OS.mbm_cntIsr1ms) mbm_cntIsr1ms = 0;  

/** Counter of regular 100us user isr. */
volatile unsigned long SECTION(.uncached.OS.mbm_cntIsr100us) mbm_cntIsr100us = 0;  

/** Counter of regular 33us user isr. */
volatile unsigned long SECTION(.uncached.OS.mbm_cntIsr33us) mbm_cntIsr33us = 0;  

/** Stack reserve on the bare metal core. */
volatile unsigned int SECTION(.uncached.OS.mbm_stackReserve) mbm_stackReserve = 0;

/** The average CPU load produced by all ISRs in tens of percent. */ 
volatile unsigned int SECTION(.uncached.OS.mbm_cpuLoad) mbm_cpuLoadCoreBareMetal = 1000;


/*
 * Function implementation
 */

/**
 * A regularly triggered interrupt handler for the timer PIT4. The interrupt does nothing
 * but counting a variable. It is triggered at high frequency and asynchronously to the
 * other ISRs and clocks on the other cores.
 */
static void isrPit4(void)
{
    ++ mbm_cntIsr1ms;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
    PIT->TIMER[4].TFLG = PIT_RTI_TFLG_TIF(1);

} /* End of isrPit4 */



/**
 * A regularly triggered interrupt handler for the timer PIT5. The interrupt does nothing
 * but counting a variable. It is triggered at high frequency and asynchronously to the
 * other ISRs and clocks on the other cores.
 */
static void isrPit5(void)
{
    ++ mbm_cntIsr100us;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
     PIT->TIMER[5].TFLG = PIT_RTI_TFLG_TIF(1);

} /* End of isrPit5 */



/**
 * A regularly triggered interrupt handler for the timer PIT6. The interrupt does nothing
 * but counting a variable. It is triggered at high frequency and asynchronously to the
 * other ISRs and clocks on the other cores.
 */
static void isrPit6(void)
{
    ++ mbm_cntIsr33us;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
    PIT->TIMER[6].TFLG = PIT_RTI_TFLG_TIF(1);

} /* End of isrPit6 */



/**
 * This demonstration software uses a number of fast interrupts to produce system load and
 * prove stability. The interrupts are timer controlled (for simplicity) but the
 * activations are chosen as asynchronous to the operating system clock as possible to
 * provoke a most variable preemption pattern.
 */
static void osInstallInterruptServiceRoutines(void)
{
    /* Disable timers during configuration. RM, 51.4.1, p. 2731.
         Disable all PIT timers during configuration. Note, this is a global setting for
       all sixteen timers. Accessing the bits makes this rountine have race conditions with
       the RTOS initialization that uses timer #RTOS_CORE_0_IDX_OF_PID_TIMER. Both routines
       must not be called in concurrency. */
    PIT->MCR = PIT_MCR_MDIS(1) | PIT_MCR_FRZ(1);

    /* Install the ISRs now that all timers are stopped.
         Vector numbers: See MCU reference manual, section 28.7, table 28-4. */
    const unsigned int processorID = rtos_osGetIdxCore();
    rtos_osRegisterInterruptHandler( &isrPit4
                                   , processorID
                                   , /* vectorNum */ PIT_Ch4_IRQn
                                   , /* psrPriority */ 1
                                   , /* isPreemptable */ true
                                   );
    rtos_osRegisterInterruptHandler( &isrPit5
                                   , processorID
                                   , /* vectorNum */ PIT_Ch5_IRQn
                                   , /* psrPriority */ 2
                                   , /* isPreemptable */ true
                                   );
    rtos_osRegisterInterruptHandler( &isrPit6
                                   , processorID
                                   , /* vectorNum */ PIT_Ch6_IRQn
                                   , /* psrPriority */ 3
                                   , /* isPreemptable */ true
                                   );

    /* Peripheral clock has been initialized to 40 MHz. The timers count at this rate. To
       get a 1ms interrupt tick we need to count till 40000.
         The RTOS on the other cores operates in ticks of 1ms. We use prime numbers to get
       good asynchronity with that activity.
         -1: See RM, 51.6 */
    PIT->TIMER[4].LDVAL = 39979-1;/* Interrupt rate approx. 1kHz */
    PIT->TIMER[5].LDVAL = 3989-1; /* Interrupt rate approx. 10kHz */
    PIT->TIMER[6].LDVAL = 1321-1; /* Interrupt rate approx. 30kHz */

    /* Enable timer operation. This operation affects all timer channels.
         PIT_MCR_FRZ: For this multi-core MCU it is not so easy to decide whether or not to
       let the timers be stopped on debugger entry: Any stopped core will halt the timers,
       regardless whether that core is related to the timer or not (and how should the
       debugger know...). Both possibilities can be annoying or advantageous, depending on
       the situation. */
    PIT->MCR = PIT_MCR_MDIS(0) | PIT_MCR_FRZ(1);

    /* Clear possibly pending interrupt flags. */
    PIT->TIMER[4].TFLG = PIT_TFLG_TIF(1);
    PIT->TIMER[5].TFLG = PIT_TFLG_TIF(1);
    PIT->TIMER[6].TFLG = PIT_TFLG_TIF(1);

    /* Enable interrupts by the timers and start them. See RM 51.4.10. */
    PIT->TIMER[4].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    PIT->TIMER[5].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    PIT->TIMER[6].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);

} /* End of osInstallInterruptServiceRoutines */



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

    /* A bare metal application may use the RTOS servivces
       rtos_osRegisterInterruptHandler() and
       rtos_osSuspendAllInterrupts()/rtos_osResumeAllInterrupts() to install and control
       interrupt handlers. The next function defines 3 PIT interrupts. */
    osInstallInterruptServiceRoutines();
    rtos_osResumeAllInterrupts();
    
    /* The "main" function of a bare metal application on a core not running sfae-RTOS is
       placed in infinite loop; C's main must never return. */
    while(true)
    {
        /* Compute the average CPU load. Note, this operation lasts about 1.5s and has a
           significant impact on the cycling speed of this infinite loop. Furthermore, it
           measures only the load produced by the interrupts but not that of the rest of
           the code in the idle loop. */
        mbm_cpuLoadCoreBareMetal = gsl_osGetSystemLoad();

        /* We have only one LED left for this core. We let it blink as usually but since it
           should be a failure indication, we enable the activity only if everything looks
           alright. Particularly, the interrupts should work properly.
             We assume, that the idle loop takes between 1 and 2s. */
        bool isSystemAlive = mbm_cpuLoadCoreBareMetal < 1000
                             &&  mbm_cpuLoadCoreBareMetal > 0;
                             
        static unsigned long SDATA_OS(cntIsr1ms_) = 0;
        unsigned long tmpCntIsr = mbm_cntIsr1ms;
        if(tmpCntIsr < cntIsr1ms_+1000u  ||  tmpCntIsr > cntIsr1ms_+2000u)
            isSystemAlive = false;
        cntIsr1ms_ = tmpCntIsr; 
        
        static unsigned long SDATA_OS(cntIsr100us_) = 0;
        tmpCntIsr = mbm_cntIsr100us;
        if(tmpCntIsr < cntIsr100us_+10000u  ||  tmpCntIsr > cntIsr100us_+20000u)
            isSystemAlive = false;
        cntIsr100us_ = tmpCntIsr; 
            
        static unsigned long SDATA_OS(cntIsr33us_) = 0;
        tmpCntIsr = mbm_cntIsr33us;
        if(tmpCntIsr < cntIsr33us_+30000u  ||  tmpCntIsr > cntIsr33us_+60000u)
            isSystemAlive = false;
        cntIsr33us_ = tmpCntIsr; 
        
        static bool SBSS_OS(isOn_) = false;
        isOn_ = isSystemAlive && !isOn_;
        lbd_osSetLED(lbd_led_4_DS7, isOn_);

        /* Communicate some status information to the reporting task running on the boot
           core. */
        mbm_stackReserve = rtos_getStackReserve(/* PID */ 0);
        
        /* Make spinning of the idle task observable in the debugger. */
        ++ mbm_cntMain;

    } /* End of inifinite idle loop of bare metal application. */

} /* End of mbm_mainCoreBareMetal */

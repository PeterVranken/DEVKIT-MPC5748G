/**
 * @file mzt_main_Z2.c
 * Main function for core Z2. This file needs to be compiled with other settings than the
 * Z4 sources.
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
/* Module interface
 *   mzt_main_Z2
 * Local functions
 *   testFloatingPointConfiguration
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "lbd_ledAndButtonDriver.h"
#include "std_decoratedStorage.h"
#include "inc_INTCInterruptController.h"
#include "sio_serialIO.h"
#include "mtx_mutex.h"
#include "mza_main_Z4A.h"
#include "mzt_main_Z2.h"


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
 
/** Counter, which is incremented in forever spinning main function. */
/*_Atomic*/ uint32_t mzt_cntMainLoopsCore2 = 0;
 
/** Counter of calls of PIT 4 interrupts */
volatile unsigned long mzt_cntIntPIT4 = 0;

/** A mutex to share some test data container between all cores. */
mtx_nestedMutex_t mzt_mtxDataMutexTest = MTX_NESTED_MUTEX_INITIALLY_RELEASED;

/** Test data container for mutex test. */
volatile mzt_dataMutexTest_t mzt_dataMutexTest TYP_SECTION(.uncached.data) =
{
    /** Cycle counters for successful access to the shared object, per core. */
    .cntCore0Success = 0,
    .cntCore1Success = 0,
    .cntCore2Success = 0,
    
    /** Total access count, needs to be same as sum of core related counts. */
    .totalCntSuccess = 0,
};


/*
 * Function implementation
 */

#if defined(USE_Z2_CLIB) || defined(USE_FP_EMULATION_CLIB) 
/**
 * Some floating point operations in order to test the compiler configuration.
 */
static void testFloatingPointConfiguration(void)
{
    volatile float x, y = 99.0f, z;
    x = y / 3;
    x = y / 3.0f;
    x = y / 3.0;
    
    z = y / x;
    z = y * x;
    z = y + x;
    z = y - x;
    z = y + 56ul;
    
    x = 3.1415f / 4.0f;
    y = sin(x);
    y = sinf(x);
    y = cos(x);
    y = cosf(x);
    
    x = 1.0f;
    y = exp(x);
    y = expf(x);
    y = log(x);
    y = logf(x);
#ifdef USE_EWL2
    y = pow(10.0f, x);
    y = powf(10.0f, x);
#else
    y = pow10(x);
    y = pow10f(x);
#endif

    x = 0.0f;
    y = z / x;
    y = log(x);
    y = logf(x);
    x = -1.0;
    y = sqrt(x);
    y = sqrtf(x);
    
    volatile double a, b = 99.0f, c;
    a = x + z;
    a = b / 3;
    a = b / 3.0f;
    a = b / 3.0;
    
    c = b / a;
    c = b * a;
    c = b + a;
    c = b - a;
    c = b + 56ul;
    
    a = 3.1415f / 4.0f;
    b = sin(a);
    b = sinf(a);
    b = cos(a);
    b = cosf(a);
    
    a = 1.0;
    b = exp(a);
    b = expf(a);
    b = log(a);
    b = logf(a);
#ifdef USE_EWL2
    b = pow(10.0, a);
    b = powf(10.0f, a);
#else
    b = pow10(a);
    b = pow10f(a);
#endif    

    a = 0.0f;
    b = c / a;
    b = log(a);
    b = logf(a);
    a = -1.0;
    b = sqrt(a);
    b = sqrtf(a);
    
    /* Give us a chance to see the last result in the debugger prior to leaving scope. */
    b = 0.0;

} /* testFloatingPointConfiguration */
#endif



/**
 * Interrupt handler that serves the interrupt of Programmable Interrupt Timer 4.\n
 *   TBC: Note, the function has been declared global in order to let the interuppt
 * registration be done at one centralized code location. We still need to decide whether
 * this is useful, likely not: The interrupt flag may be set before the core has started up
 * - however, this must not be critical.
 */
void mzt_interruptPIT4Handler(void)
{
    ++ mzt_cntIntPIT4;

    /* Acknowledge the interrupt in the causing HW device. */
    PIT->TIMER[4].TFLG = PIT_TFLG_TIF(1);
    
    unsigned int u;
    for(u=0; u<25; ++u)
    {

        /* Test of nested mutex. This is the ISR of highest priority among those that
           compete for the mutex. We don't need to suspend interrupt handling. */
        mtx_acquireNestedMutex(&mzt_mtxDataMutexTest);
        assert(mzt_dataMutexTest.cntCore0Success
               + mzt_dataMutexTest.cntCore1Success
               + mzt_dataMutexTest.cntCore2Success
               == mzt_dataMutexTest.totalCntSuccess
              );
        ++ mzt_dataMutexTest.cntCore2Success;
        ++ mzt_dataMutexTest.totalCntSuccess;
        mtx_releaseNestedMutex(&mzt_mtxDataMutexTest);

    } /* End for(All cycles of mutex test) */
    
    /* Access to LED doesn't require a critical section since this interrupt has the
       highest priority. */
    static int cntIsOn = 0;
    if(++cntIsOn >= 500)
        cntIsOn = -500;
    lbd_setLED(mza_ledCore2IrqPit4, /* isOn */ cntIsOn >= 0);
    
} /* End of mzt_interruptPIT4Handler */



/**
 * Initialize the Periodic Interrupt Timers (PIT), which we use as interrupt source on this
 * core. We let timer 4 generate a 1ms clock tick on this core.
 */
static void initPIT(void)
{
    /* Note, time PIT0 must not be used. It is occupied by the DMA channel as trigger for
       serial output. */

    /* Disable timers during configuration. RM, 51.4.1, p. 2731. */
    PIT->MCR = PIT_MCR_MDIS(1) | PIT_MCR_FRZ(1);

    /* Install the interrupt handlers for cyclic timer PIT 4. The interrupts go to
       core 2, Z2. */
    inc_installINTCInterruptHandler( mzt_interruptPIT4Handler
                                   , /* processor ID */ 2
                                   , /* vectorNum */ 230
                                   , /* psrPriority */ 2
                                   , /* isPreemptable */ true
                                   );

    /* Peripheral clock has been initialized to 40 MHz. To get a 1ms interrupt tick we
       need to count till 40000. -1: See RM, 51.6 */
    PIT->TIMER[4].LDVAL = 40009-1; /* Interrupt rate chosen a bit different from and mutual
                                      prime to other cores. */

    /* Enable timer operation.
         PIT_MCR_FRZ: For this multi-core MCU it is not so easy to decide whether or not to
       let the timers be stopped on debugger entry: Any stopped core will halt the timers,
       regardless whether that core is related to the timer or not (and how should the
       debugger know...). Both possibilities can be annoying or advantageous, depending on
       the situation. */
    PIT->MCR = PIT_MCR_MDIS(0) | PIT_MCR_FRZ(0);
    
    /* Clear a possibly pending interrupt flag. */
    PIT->TIMER[4].TFLG = PIT_TFLG_TIF(1);
    
    /* Enable interrupts by the timer and start it. See RM 51.4.10. */
    PIT->TIMER[4].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);

} /* End of initPIT */


 

/** C entry function for Z2 core. */
void _Noreturn mzt_main_Z2(signed int noArgs TYP_DBG_ONLY, const char *argAry[] TYP_DBG_ONLY)
{
    assert(noArgs == 1  && strcmp(argAry[0], "Z2") == 0);

    /* The Z2 core may execute floating point operations but
       - they are implemented by the compiler as emulation code. The source file must be
         compiled with -mcpu=e200z2
       - the linked clib must have been built for Z2 not for Z4. The development
         environment contains both builds and the linker command line need to select the Z2
         variant
       - since the linker needs to select the Z2 variant of the clib all Z4 code will be
         degraded with respect to floating point performance - it'll use the Z2 emulation
         libaries, too, for all computations, which cannot be implement by raw floating
         point instructions directly by the compiler. This holds e.g. for all calls from
         the math lib, like sinf, etc.
       All in all, the best decision for a project is not at all to use floating point on
       the Z2 so that the project can link the Z4 libraries. This gurantees full floating
       point power on the two Z4 cores but will lead to an exception if the Z2 tries
       floating point computations. */
#if defined(USE_Z2_CLIB) || defined(USE_FP_EMULATION_CLIB) 
    testFloatingPointConfiguration();
#endif

    /* Configure interrupt source and start interrupt servicing by core 2. */
    initPIT();
    inc_resumeAllInterrupts();
    
    bool isOn = false;
    while(true)
    {
        unsigned int u;
        for(u=0; u<100000; ++u)
        {
            /* ++mzt_cntMainLoopsCore2 implemented with atomic read and write. Actually
               useless, there's no other core looking at the variable. */
            const uint32_t newVal = std_loadWordAtomic(/* address */ &mzt_cntMainLoopsCore2)+1;
            std_storeWordAtomic(/* word */  newVal, /* address */ &mzt_cntMainLoopsCore2);
            
            /* Test of mutex. */
            mtx_acquireNestedMutex(&mzt_mtxDataMutexTest);
            inc_suspendAllInterrupts();
            
            assert(mzt_dataMutexTest.cntCore0Success
                   + mzt_dataMutexTest.cntCore1Success
                   + mzt_dataMutexTest.cntCore2Success
                   == mzt_dataMutexTest.totalCntSuccess
                  );
            ++ mzt_dataMutexTest.cntCore2Success;
            ++ mzt_dataMutexTest.totalCntSuccess;

            inc_resumeAllInterrupts();
            mtx_releaseNestedMutex(&mzt_mtxDataMutexTest);
        }

        /* Toggle third LED. */
        lbd_setLED(mza_ledCore2Main, isOn=!isOn);
        
        /* Print a message to the console. */
        #define GREETING "core Z2, main: Cycle completed\r\n"
        sio_writeSerial(/* msg */ GREETING, /* noBytes */ sizeof(GREETING)-1);
        #undef GREETING
    }
} /* End of mzt_main_Z2 */




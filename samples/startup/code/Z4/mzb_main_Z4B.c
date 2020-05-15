/**
 * @file mzb_main_Z4B.c
 * C entry function for the Z4 B core.
 *   The operation of the main program is a loop, which is used to test and demonstrate the
 * offered, very basic inter-core communication methods.
 *   Core Z4A uses two nested interrupts. Cores Z4B and Z2 have one interrupt each. All
 * interrupts and the three core's main functions take part in the communication and test
 * the consistency of the read data. Each of these seven execution contexts control one of
 * the eight user LEDs. Any deteced failure is reported by assertion - implemented as an
 * infinitely spinning loop - and the according LED will stop blinking. Other contexts will
 * likely by affected because of blocking states and their LED will stop blinking, too.
 * Only if all sever LEDs are blinking everything is alright.
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
 *   mzb_main_Z4B
 * Local functions
 *   interruptPIT3Handler
 *   initPIT
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lbd_ledAndButtonDriver.h"
#include "inc_INTCInterruptController.h"
#include "mtx_mutex.h"
#include "std_decoratedStorage.h"
#include "sio_serialIO.h"
#include "mzt_main_Z2.h"
#include "mza_main_Z4A.h"
#include "mzb_main_Z4B.h"


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

/** Counter, which is incremented in forever spinning main function running on core Z4B. */
volatile uint32_t mzb_cntMainLoopsCore1 = 0;

/** Counter of calls of PIT 3 interrupts. */
volatile unsigned long mzb_cntIntPIT3 = 0;


/*
 * Function implementation
 */


/**
 * Interrupt handler that serves the interrupt of Programmable Interrupt Timer 3. This
 * interrupt is handled by core 1 at low priority. The interrupt occurs about once a
 * Millisecond.
 */
static void interruptPIT3Handler()
{
    ++ mzb_cntIntPIT3;

    unsigned int u;
    for(u=0; u<25; ++u)
    {

        /* Test of nested mutex. This is the ISR of highest priority among those on this
           core that compete for the mutex. We don't need to suspend interrupt handling. */
        mtx_acquireNestedMutex(&mzt_mtxDataMutexTest);
        assert(mzt_dataMutexTest.cntCore0Success
               + mzt_dataMutexTest.cntCore1Success
               + mzt_dataMutexTest.cntCore2Success
               == mzt_dataMutexTest.totalCntSuccess
              );
        ++ mzt_dataMutexTest.cntCore1Success;
        ++ mzt_dataMutexTest.totalCntSuccess;
        mtx_releaseNestedMutex(&mzt_mtxDataMutexTest);

    } /* End for(All cycles of mutex test) */
    
    /* Test of intercore critical section. This code is running on core 1. */
    unsigned int u1 TYP_DBG_ONLY, u2 TYP_DBG_ONLY;
    mtx_enterIntercoreCriticalSection(&mza_csTestOfCriticalSection);
    u1 = mza_csTestData1++;
    u2 = mza_csTestData2++;
    mtx_leaveIntercoreCriticalSection(&mza_csTestOfCriticalSection);
    assert(u1 == u2);

    /* Here, a lock free inter-core communication pattern is demonstrated. It works only
       with a peer-to-peer communication; exactely one execution context on either of two
       of cores is involved. We receive a value from core Z4A and acknowledge the
       reception. The received values are incremented by one in each cycle, this is
       additional redundancy, which can be used for test result evaluation. */
    static uint8_t newDataAvailable_lastVal = 0;
    static signed int expectedData = 0;
    if(mza_msgZ4AToZ4B.newDataAvailable != newDataAvailable_lastVal)
    {
        /* Consume the data. Here: Test for expected values. */
        assert(mza_msgZ4AToZ4B.msgAry[0] == expectedData
               &&  mza_msgZ4AToZ4B.msgAry[0] + mza_msgZ4AToZ4B.msgAry[1] == 0
              );
        
        /* Test only: We can double-check that the flag always changes by one. */
        assert(mza_msgZ4AToZ4B.newDataAvailable == (uint8_t)(newDataAvailable_lastVal + 1));
        
        std_fullMemoryBarrier();    /* Ensure completion of data evaluation. */
        ++ mza_msgZ4AToZ4B.dataAcknowledge; /* Signal the data consumption */
        
        /* Be prepared for next cycle. This can be done already in parallel with the
           producer. */
        ++ newDataAvailable_lastVal;
        ++ expectedData;
    }
    
    static int cntIsOn = 0;
    if(++cntIsOn >= 500)
        cntIsOn = -500;
    lbd_setLED(mza_ledCore1IrqPit3, /* isOn */ cntIsOn >= 0);
    
    /* Acknowledge the interrupt in the causing HW device. */
    PIT->TIMER[3].TFLG = PIT_TFLG_TIF(1);
    
} /* End of interruptPIT3Handler */



/**
 * Initialize the Periodic Interrupt Timers (PIT), which we use as interrupt source in this
 * simple sample. We let timers 1, 2, 3 generate a 1ms clock tick on all cores. The times
 * differ a bit on all cores and they are chosen mutual prime to get a more meaningful
 * test of the mutex operations.
 */
static void initPIT(void)
{
    /* Note, time PIT0 must not be used. It is occupied by the DMA channel as trigger for
       serial output. */

    /* Disable timers during configuration. RM, 51.4.1, p. 2731. */
    PIT->MCR = PIT_MCR_MDIS(1) | PIT_MCR_FRZ(0);

    /* Install the interrupt handlers for cyclic timer PIT 3. The interrupt goes to
       core 1, Z4B. */
    inc_installINTCInterruptHandler( interruptPIT3Handler
                                   , /* processor ID */ 1
                                   , /* vectorNum */ 229
                                   , /* psrPriority */ 2
                                   , /* isPreemptable */ true
                                   );

    /* Peripheral clock has been initialized to 40 MHz. To get a 1ms interrupt tick we
       need to count till 40000. -1: See RM, 51.6 */
    PIT->TIMER[3].LDVAL = 39989-1; /* Interrupt rate chosen a bit different from and mutual
                                      prime to other cores. */

    /* Enable timer operation.
         PIT_MCR_FRZ: For this multi-core MCU it is not so easy to decide whether or not to
       let the timers be stopped on debugger entry: Any stopped core will halt the timers,
       regardless whether that core is related to the timer or not (and how should the
       debugger know...). Both possibilities can be annoying or advantageous, depending on
       the situation. */
    PIT->MCR = PIT_MCR_MDIS(0) | PIT_MCR_FRZ(0);
    
    /* Clear a possibly pending interrupt flag. */
    PIT->TIMER[3].TFLG = PIT_TFLG_TIF(1);
    
    /* Enable interrupts by the timer and start it. See RM 51.4.10. */
    PIT->TIMER[3].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);

} /* End of initPIT */


 

/**
 * C entry function for Z4B core.
 *   @param noArgs
 * Number of arguments in \a argAry. Is actually always equal to one.
 *   @param argAry
 * Array of string arguments to the function. Actually, always a single string which equals
 * the name of the core, which is started. Evaluating the string enables having the same
 * main function for all secondary cores.
 */
void _Noreturn mzb_main_Z4B( signed int noArgs TYP_DBG_ONLY
                           , const char *argAry[] TYP_DBG_ONLY
                           )
{
    /* The arguments of the main function are quite useless. Only use case would be a main
       function shared between core 1 and core 2. */
    assert(noArgs == 1  && strcmp(argAry[0], "Z4B") == 0);
    
    /* Floating point operation is always possible on this core. However, it depends on a
       makefile setting, whether the non basic operations like sinf, powf use pure
       emulation code or if their implementation builds on floating point machine
       instructions: If core 2 is configured to do floating point operations, too, then we
       need to select the emulation library - all cores share the C run time libaries. */
    mza_testZ4FloatingPointConfiguration();
    
    /* Start interrupt servicing by core 1. */
    initPIT();
    inc_resumeAllInterrupts();
    
    bool isOn = false;
    while(true)
    {
        unsigned int u;
        for(u=0; u<750000; ++u)
        {
            /* ++mzb_cntMainLoopsCore1 implemented with atomic read and write. Actually
               useless, there's no other core looking at the variable. */
            const uint32_t newVal = std_loadWordAtomic
                                        (/* address */ (uint32_t*)&mzb_cntMainLoopsCore1)
                                    + 1;
            std_storeWordAtomic( /* word */  newVal
                               , /* address */ (uint32_t*)&mzb_cntMainLoopsCore1
                               );

            /* Test of mutual exclusion of cores. */
            mtx_acquireNestedMutex(&mzt_mtxDataMutexTest);
            inc_suspendAllInterrupts();
            
            assert(mzt_dataMutexTest.cntCore0Success
                   + mzt_dataMutexTest.cntCore1Success
                   + mzt_dataMutexTest.cntCore2Success
                   == mzt_dataMutexTest.totalCntSuccess
                  );
            ++ mzt_dataMutexTest.cntCore1Success;
            ++ mzt_dataMutexTest.totalCntSuccess;
                
            inc_resumeAllInterrupts();
            mtx_releaseNestedMutex(&mzt_mtxDataMutexTest);
        }

        /* Toggle second LED. */
        lbd_setLED(mza_ledCore1Main, isOn=!isOn);
        
        /* Print a message to the console. */
        #define GREETING "core Z4B, main: Cycle completed\r\n"
        sio_writeSerial(/* msg */ GREETING, /* noBytes */ sizeof(GREETING)-1);
        #undef GREETING
    }
} /* End of mzb_main_Z4B */

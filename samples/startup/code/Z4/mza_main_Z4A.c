/**
 * @file mza_main_Z4A.c
 * C entry function for the Z4 A core. The core completes the HW initialization (clocks run
 * at full speed, peripheral bridge is widely opened, SMPU permitts full access of all
 * cores to all address space and it shapes cache-inhibitted memory section for inter-core
 * communication) and initializes a few I/O drivers, e.g. LED drivers and serial I/O with
 * the host. Then it starts the other cores.
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
 *   mza_testZ4FloatingPointConfiguration
 *   main
 * Local functions
 *   interruptPIT1Handler
 *   interruptPIT2Handler
 *   initPIT
 *   startSecondaryCore
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
#include "mpu_systemMemoryProtectionUnit.h"

#include "lbd_ledAndButtonDriver.h"
#include "inc_INTCInterruptController.h"
#include "sio_serialIO.h"
#include "std_decoratedStorage.h"
#include "stm_systemTimer.h"
#include "f2d_float2Double.h"
#include "mzt_main_Z2.h"
#include "mzb_main_Z4B.h"
#include "mza_main_Z4A.h"


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

/** Counter, which is incremented in forever spinning main function running on core Z4A. It
    is not declared static in order to have it located in the small data area. */
uint32_t mza_cntMainLoopsCore0 = 0;

volatile unsigned long mza_cntIntPIT1 = 0 /** Counter of calls of PIT 1 interrupts */
                     , mza_cntIntPIT2 = 0;/** Counter of calls of PIT 3 interrupts */

/** Test of intercore critical section: The critical section object. */
mtx_intercoreCriticalSection_t mza_csTestOfCriticalSection = MTX_INTERCORE_CRITICAL_SECTION;

/** Test of intercore critical section: Some protected data. */
volatile unsigned TYP_SECTION(.uncached.data) int mza_csTestData1 = 0;

/** Test of intercore critical section: Some protected data. */
volatile unsigned TYP_SECTION(.uncached.data) int mza_csTestData2 = 0;

/** A data object shared between core Z4A and Z4B for communication purpose. */
mza_msgZ4AToZ4B_t TYP_SECTION(.uncached.data) mza_msgZ4AToZ4B =
{
    .msgAry = {[0] = 0, [1] = 0},
    .newDataAvailable = 0,
    .dataAcknowledge = 0
};

/** Interface with assembly code: Here's a variable in the assembly startup code, which
    takes the addresses of the C main function to be invoked on core Z4B. It needs to be
    initialized prior to starting the core. Z4B and Z2 may use the same function.
      @todo Why can't we place the declaration locally into the function where it is used?
    The compiler rejects it due to the section attribute. */
extern void (*volatile TYP_SECTION(.bss.startup) sup_main_Z4B)(signed int, const char **);

/** Interface with assembly code: Here's a variable in the assembly startup code, which
    takes the addresses of the C main function to be invoked on core Z2. It needs to be
    initialized prior to starting the core. Z4B and Z2 may use the same function. */
extern void (*volatile TYP_SECTION(.bss.startup) sup_main_Z2)(signed int, const char **);


/*
 * Function implementation
 */


/**
 * Some floating point operations in order to test the compiler configuration. The
 * implementation is shared between the Z4 cores.
 *   @remark
 * This is meant an "interactive" test. The results can be evaluated in the debugger only.
 * However, even without debugger it can at least prove that no exception is thrown because
 * of bad floating point configuration.
 *   @remark
 * We know that not all of the operations are computed well. The double operations like y =
 * sin(x) do fail. This is because we don't have a C math library, which had been compiled with
 * our project settings. We use the "double implemented as float" setting (i.e.
 * short-double on the compiler command line) but our available libraries still use double
 * (and they need to use very slow emulation code for this). This is not too bad as the
 * newer C standards offers the according float functions and one should anyway only use
 * these in an embedded 32 Bit project. y = sinf(x) is expected to work well.
 */
void mza_testZ4FloatingPointConfiguration(void)
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

} /* mza_testZ4FloatingPointConfiguration */




/**
 * Interrupt handler that serves the interrupt of Programmable Interrupt Timer 1. This
 * interrupt is handled by core 0 at low priority. The interrupt occurs about once a
 * Millisecond.
 */
static void interruptPIT1Handler()
{
    ++ mza_cntIntPIT1;

    /* Acknowledge the interrupt in the causing HW device. */
    PIT->TIMER[1].TFLG = PIT_TFLG_TIF(1);
    
    const uint32_t tiStart = stm_getTimerValue(/* idxTimer */ 0);
    
    unsigned int u;
    //for(u=0; u<25; ++u)
    do
    {
        /* The nested mutex only handles the competition of different cores. We need
           to apply a second means (suspension of interrupt handling) to protect our
           resource against interference from another execution context on the same core.
             Note, the order of statements matters significantly. If we first acquire the
           mutex and then inhibit local context switches then the mutex-lock time seen by
           the competing core can be prolonged by the execution time of whatever
           preempting contexts. If this is a normal application task in an RTOS environment
           then this can be catastrophic. */
        mtx_acquireNestedMutex(&mzt_mtxDataMutexTest);
        inc_suspendAllInterrupts();
        
        assert(mzt_dataMutexTest.cntCore0Success
               + mzt_dataMutexTest.cntCore1Success
               + mzt_dataMutexTest.cntCore2Success
               == mzt_dataMutexTest.totalCntSuccess
              );
        ++ mzt_dataMutexTest.cntCore0Success;
        ++ mzt_dataMutexTest.totalCntSuccess;

        inc_resumeAllInterrupts();
        mtx_releaseNestedMutex(&mzt_mtxDataMutexTest);
        
    } /* End for(All cycles of mutex test) */
/// @todo Cleanup code, no literals. Consider: The times of all cores can sum up
    while(stm_getTimerValue(/* idxTimer */ 0) - tiStart < 16000u);
    
    /* Test of intercore critical section. This code is running on core 0. */
    unsigned int u1 TYP_DBG_ONLY, u2 TYP_DBG_ONLY;
    mtx_enterIntercoreCriticalSection(&mza_csTestOfCriticalSection);
    /// @todo Call a recursive sub-routine, which tests the nested entry into the section
    u1 = mza_csTestData1++;
    u2 = mza_csTestData2++;
    mtx_leaveIntercoreCriticalSection(&mza_csTestOfCriticalSection);
    assert(u1 == u2);

    /* Here, a lock free inter-core communication pattern is demonstrated. It works only
       with a peer-to-peer communication; exactely one execution context on either of two
       of cores is involved. We send a value to core Z4B and let it respond. The received
       values are incremented by one in each cycle, this is additional redundancy, which
       can be used for test result evaluation. */
    static uint8_t dataAcknowledge_lastVal = (uint8_t)-1; /* Not 0: Have an initial trigger */
    static signed int dataToBeSent = 0;
    if(mza_msgZ4AToZ4B.dataAcknowledge != dataAcknowledge_lastVal)
    {
        mza_msgZ4AToZ4B.msgAry[0] = dataToBeSent; /* Reading now, the receiver would see
                                                     inconsistent data. */
        mza_msgZ4AToZ4B.msgAry[1] = -dataToBeSent;/* Now, the receiver would see consistent
                                                     data again. */
                                                     
        /* Test only: We can double-check that the flag always changes by one. */
        assert(mza_msgZ4AToZ4B.dataAcknowledge == (uint8_t)(dataAcknowledge_lastVal + 1));
        
        std_fullMemoryBarrier();    /* Ensure completion of write message payload data. */
        ++ mza_msgZ4AToZ4B.newDataAvailable; /* Signal the data update */
        
        /* Be prepared for next cycle. This can be done already in parallel with the
           consumer. */
        ++ dataAcknowledge_lastVal;
        ++ dataToBeSent;
    }
    
    static int cntIsOn = 0;
    if(++cntIsOn >= 500)
        cntIsOn = -500;
    lbd_setLED(mza_ledCore0IrqPit1, /* isOn */ cntIsOn >= 0);

} /* End of interruptPIT1Handler */



/**
 * Interrupt handler that serves the interrupt of Programmable Interrupt Timer 2. This
 * interrupt is handled by core 0. It occurs at high rate (once about every 100us) and is
 * intended to preempt the PIT1 handler on the same core in order to get a meaningful test
 * of the nested mutex.
 */
static void interruptPIT2Handler()
{
    ++ mza_cntIntPIT2;

    /* Acknowledge the interrupt in the causing HW device. */
    PIT->TIMER[2].TFLG = PIT_TFLG_TIF(1);
    
    const uint32_t tiStart = stm_getTimerValue(/* idxTimer */ 0);
    unsigned int u;
//    for(u=0; u<5; ++u)
    {

        /* Test of nested mutex. This is the ISR of highest priority among those that
           compete for the mutex. We don't need to suspend interrupt handling. */
        mtx_acquireNestedMutex(&mzt_mtxDataMutexTest);
        assert(mzt_dataMutexTest.cntCore0Success
               + mzt_dataMutexTest.cntCore1Success
               + mzt_dataMutexTest.cntCore2Success
               == mzt_dataMutexTest.totalCntSuccess
              );
        ++ mzt_dataMutexTest.cntCore0Success;
        ++ mzt_dataMutexTest.totalCntSuccess;
        mtx_releaseNestedMutex(&mzt_mtxDataMutexTest);

    } /* End for(All cycles of mutex test) */
/// @todo Cleanup code, no literals
    while(stm_getTimerValue(/* idxTimer */ 0) - tiStart < 4000u);
  
    /* Test of intercore critical section. This code is running on core 0. */
    unsigned int u1 TYP_DBG_ONLY, u2 TYP_DBG_ONLY;
    mtx_enterIntercoreCriticalSection(&mza_csTestOfCriticalSection);
    u1 = mza_csTestData1++;
    u2 = mza_csTestData2++;
    mtx_leaveIntercoreCriticalSection(&mza_csTestOfCriticalSection);
    assert(u1 == u2);

    static int cntIsOn = 0;
    if(++cntIsOn >= 5000)
        cntIsOn = -5000;
    lbd_setLED(mza_ledCore0IrqPit2, /* isOn */ cntIsOn >= 0);
    
} /* End of interruptPIT2Handler */




/**
 * Initialize the Periodic Interrupt Timers (PIT), which we use as interrupt source on this
 * core. We let timers 1, 2, 3 generate a 1ms clock tick on all cores. The times
 * differ a bit on all cores and they are chosen mutual prime to get a more meaningful
 * test of the mutex operations.
 */
static void initPIT(void)
{
    /* Note, time PIT0 must not be used. It is occupied by the DMA channel as trigger for
       serial output. */

    /* Disable timers during configuration. RM, 51.4.1, p. 2731. */
    PIT->MCR = PIT_MCR_MDIS(1) | PIT_MCR_FRZ(1);

    /* Install the interrupt handlers for cyclic timer PIT 1 and 2. The interrupts go to
       core 0, Z4A. */
    inc_installINTCInterruptHandler( interruptPIT1Handler
                                   , /* processor ID */ 0
                                   , /* vectorNum */ 227
                                   , /* psrPriority */ 2
                                   , /* isPreemptable */ true
                                   );
    inc_installINTCInterruptHandler( interruptPIT2Handler
                                   , /* processor ID */ 0
                                   , /* vectorNum */ 228
                                   , /* psrPriority */ 3
                                   , /* isPreemptable */ true
                                   );

    /* Peripheral clock has been initialized to 40 MHz. To get a 1ms interrupt tick we
       need to count till 40000. -1: See RM, 51.6 */
    PIT->TIMER[1].LDVAL = 40000-1; /* Interrupt rate 1ms. */
    PIT->TIMER[2].LDVAL = 4001-1;  /* Interrupt rate chosen higher and mutually prime with
                                      the other timer on the same core and the timers on
                                      the other cores. This makes the tests more
                                      meaningful. */ 

    /* Enable timer operation.
         PIT_MCR_FRZ: For this multi-core MCU it is not so easy to decide whether or not to
       let the timers be stopped on debugger entry: Any stopped core will halt the timers,
       regardless whether that core is related to the timer or not (and how should the
       debugger know...). Both possibilities can be annoying or advantageous, depending on
       the situation. */
    PIT->MCR = PIT_MCR_MDIS(0) | PIT_MCR_FRZ(0);
    
    /* Clear possibly pending interrupt flags. */
    PIT->TIMER[1].TFLG = PIT_TFLG_TIF(1);
    PIT->TIMER[2].TFLG = PIT_TFLG_TIF(1);
    
    /* Enable interrupts by the timers and start them. See RM 51.4.10. */
    PIT->TIMER[1].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    PIT->TIMER[2].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);

} /* End of initPIT */


 

/**
 * Start a secondary core. The initial core is already started and it is the one, which will
 * execute this function. Never call the function from another core than Z4A.
 *   @param idxCore
 * Which core to start? Permitted indexes are 1 for the Z4B core and 2 for the Z2 core.
 *   @param main
 * The main function to be used for the secondary core. Although it might be tempting to
 * have one and the same main function for all cores, the normal function main must not be
 * passed: The compiler generates special code on entry into C's main() to initialize the C
 * runtime. If C's main() is called for more than a single core then this initializtaion
 * happens repeatedly and maybe even coincidentally; either of this can make the runtime
 * fail.
 */
static void startSecondaryCore( unsigned int idxCore
                              , void (*main)(signed int, const char *[])
                              )
{
    /* The entry point into the C code cannot be the normal main function for the other
       cores. The C compiler unconditionally generates the call of the C run time
       initialization as part of the machine code that implements the entry into main. We
       must of course not execute this initialization three times. Instead, we pass the
       main function for the other cores explicitly to the startup code. Although this
       effectively is cross-core communication we don't have any issues with it; the other
       core is not yet running, has not filled any data into its cache and the output write
       buffers of the Z4A core, which executes this code here will be written through its
       cache into external memory long before the other core actually reaches the location
       in the startup code where the function pointer is read. */

    /* Interface with assembly startup code. (There's no header file for the assembly
       startup code.): The entry point into code execution after reset. Common for all
       three cores. */
    extern void _Noreturn sup_startUp(void);
    
    /* Prepare core start: Enter code start address and set allowed run modes. */
    switch(idxCore)
    {
    case 1 /* Z4B */:
        /* Pass the pointer to the C code entry to the assembly startup code being executed
           on the other core. Note, all core use the same startup code. This code is
           conditionally in that it reads a core dependent address of the C main function
           to use. */
        sup_main_Z4B = main;
        std_fullMemoryBarrier();

        /* RM 38.3.91, p. 1209: The core is enabled in all run modes. Caution, the RM names
           the three cores 1, 2 and 3, while in SW (as the argument of this function does)
           we normally count from zero. */
        MC_ME->CCTL2 = 0x00fc;

        /* RM, 38.3.94, p. 1214: Reset vector for core 1. Why do we need to set this
           vector? It had already been entered in the boot sector, the BAF. */
        MC_ME->CADDR2 = (uint32_t)sup_startUp | MC_ME_CADDR2_RMC(1);

        break;

    case 2 /* Z2 */:
        /* Pass the pointer to the C code entry to the assembly startup code being executed
           on the other core. See case Z4B for details. */ 
        sup_main_Z2 = main;
        std_fullMemoryBarrier();

        /* RM 38.3.92, p. 1211: The core is enabled in all run modes. */
        MC_ME->CCTL3 = 0x00fc;

        /* RM, 38.3.95, p. 1215: Reset vector for core 2. */
        MC_ME->CADDR3 = (uint32_t)sup_startUp | MC_ME_CADDR3_RMC(1);

        break;

    default:
        /* Core 0 is always running and there are no other cores on this hardware. */
        assert(false);
    }

    /* RM 38.3.94: Another core is started on the next run mode change. We trigger a
       transition from DRUN to DRUN. On return from this function call, the other core is
       running in parallel. */
    ccl_triggerTransitionToModeDRUN();

} /* End of startSecondaryCore */



/**
 * C entry function main. Is used for and only for Z4A core.
 *   @param noArgs
 * Number of arguments in \a argAry. Is actually always equal to one.
 *   @param argAry
 * Array of string arguments to the function. Actually, always a single string which equals
 * the name of the core, which is started.
 */
int _Noreturn main(int noArgs TYP_DBG_ONLY, const char *argAry[] TYP_DBG_ONLY)
{
    assert(noArgs == 1  && strcmp(argAry[0], "Z4A") == 0);

    /* Complete the core HW initialization - as far as not yet done by the assembly startup
       code. */
    
    /* All clocks run at full speed, including all peripheral clocks. */
    ccl_configureClocks();          
    
    /* Interrupts become usable and configurable by SW. */
    inc_initINTCInterruptController();
    
    /* Configuration of cross bars: All three cores need efficient access to ROM and RAM.
       By default, the cores generally have strictly prioritized access to all memory slave
       ports in order Z4A, I-Bus, Z4A, D-Bus, Z4B, I-Bus, Z4B, D-Bus, Z2, I-Bus, Z2, D-Bus.
       While not optimal it is at least acceptable for most ports - with the exception of
       slave port 3 of cross bar 0: This port is the only path for the D buses of Z4B and
       Z2 (see RM, 16.1.1, table 16-1, p. 409) and Z2 suffers from starvation if Z4B is
       heavily transferring data. This can happen in our example, where all cores are
       spinning in a tiny loop to increment some counters in RAM. The minimum action to
       take is setting this port to round robin arbitration. */
    xbs_configCrossbarSwitch(/* isZ2IOCore */ true);

    /* Memory access definition to give access to all cores to all memory (no memory
       protection in this simple sample). One memory region is defined
       cache-inhibited for cross-core communication. */
    mpu_initSMPU();

    /* The core is now running in the desired state. I/O driver initialization follows to
       the extend required by this simple sample. */
    
    /* Shape access to the eight user LEDs. */
    lbd_initLEDAndButtonDriver();
    
    /* Route the CLOCKOUTs 0 and 1 from the clock generation module to the external pins
       PG7 and PG6, respectively. They are available at connector J3-16 and J3-14. The
       devided core clocks should be visible as a 10 and a 1 MHz signal. */
    SIUL2->MSCR[103 /* PG7 */] =
                SIUL2_MSCR_SSS(3)   /* CLOCKOUT0 */
                | SIUL2_MSCR_SRC(3) /* Slew rate: Full drive without SR control */
                | SIUL2_MSCR_OBE(1) /* Enable output buffer */
                | SIUL2_MSCR_ODE(0) /* Disable open drain, drive both edges */
                | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */
                | SIUL2_MSCR_APC(0) /* No analog I/O */
                | SIUL2_MSCR_IBE(0) /* Disable input buffer */
                | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */
                | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */
                | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */
                ;
    SIUL2->MSCR[102 /* PG6 */] =
                SIUL2_MSCR_SSS(3)   /* CLOCKOUT1 */
                | SIUL2_MSCR_SRC(3) /* Slew rate: Full drive without SR control */
                | SIUL2_MSCR_OBE(1) /* Enable output buffer */
                | SIUL2_MSCR_ODE(0) /* Disable open drain, drive both edges */
                | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */
                | SIUL2_MSCR_APC(0) /* No analog I/O */
                | SIUL2_MSCR_IBE(0) /* Disable input buffer */
                | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */
                | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */
                | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */
                ;

    /* Start the system timers for execution time measurement. */
    stm_initSystemTimers();
    
    /* Initialize the serial interface. */
    sio_initSerialInterface(/* baudRate */ 115200);

    /* After HW initialization, we can start the other cores. Note, there's no guarantee in
       which time order they will arrive in their main. */
    startSecondaryCore(/* idxCore */ 1 /* Z4B */, mzb_main_Z4B);
    startSecondaryCore(/* idxCore */ 2 /* Z2 */, mzt_main_Z2);

    /* Demonstrate the use of the serial interface. Note, the function is never blocking
       and we have left it for a long time before the character are visible in the console
       window. Never blocking: If the buffer has not enough space then an according number
       of characters is dropped rather than the function waiting for the buffer becoming
       empty. */
    #define GREETING "Hello World\r\n"
    sio_writeSerial(GREETING, /* noBytes */ sizeof(GREETING)-1);
    puts("puts saying " GREETING);
    printf("printf saying %s", GREETING);
    #undef GREETING
    
    /* Configure interrupt source and start interrupt servicing on core 0. */
    initPIT();
    inc_resumeAllInterrupts();
    
    /* Floating point operation is always possible on this core. However, it depends on a
       makefile setting, whether the non basic operations like sinf, powf use pure
       emulation code or if their implementation builds on floating point machine
       instructions: If core 2 is configured to do floating point operations, too, then we
       need to select the emulation library - all cores share the C run time libaries. */
    mza_testZ4FloatingPointConfiguration();

    bool isOn = false;
    while(true)
    {
        /* Demonstrate the use of the serial input: Print all complete lines of input text,
           which have been received since the previous loop. */
        while(true)
        {
            char input[128];
            if(sio_getLine(input, sizeof(input)) == input)
                printf("You entered: %s\r\n", input);
            else
                break;
        }
        
        unsigned long u;
        
        /* A fast loop, accessing some data, which is shared between different cores and
           different execution contexts on the cores. Redundant data makes this a test of
           the synchronization: As soon as some inconsistencies are recognized the code
           execution is halted in an assertion and one or more LEDs stop blinking. */
        for(u=0; u<2000000; ++u)
        {
            ++ mza_cntMainLoopsCore0;
            
            /* The nested mutex only handles the competition of different cores. We need to
               apply a second means (suspension of interrupt handling, see below) to
               protect our resource against interference from another execution context on
               the same core.
                 Note, the order of statements matters significantly. If we first acquire
               the mutex and then inhibit local context switches then the mutex-lock time
               seen by the competing core can be prolonged by the execution time of
               what-ever preempting contexts. If this is a normal application task in an
               RTOS environment then this can be catastrophic. On the other hand, when
               doing it vice versa, the non arbitrated busy-wait for a spin-lock always
               involves the risk of starvation. The unpredictable, theoretically unbounded
               wait time prolongs the suspension time of the local interrupts. */
            mtx_acquireNestedMutex(&mzt_mtxDataMutexTest);
            
            inc_suspendAllInterrupts();
            assert(mzt_dataMutexTest.cntCore0Success
                   + mzt_dataMutexTest.cntCore1Success
                   + mzt_dataMutexTest.cntCore2Success
                   == mzt_dataMutexTest.totalCntSuccess
                  );
            inc_resumeAllInterrupts();

            /* Note, the interrupt suspension time doesn't necessarily need to be identical
               to the mutex hold time. However, the same considerations as above hold for
               the possible impact on the wait time of other cores. This is a demo but not
               meant good design. */

            inc_suspendAllInterrupts();
            ++ mzt_dataMutexTest.cntCore0Success;
            ++ mzt_dataMutexTest.totalCntSuccess;
            inc_resumeAllInterrupts();
            
            mtx_releaseNestedMutex(&mzt_mtxDataMutexTest);
        }
        
        /* The variables counted by the other core reside in cached memory and the value
           changes are not easily visible by this core. We use a function from our tiny
           decorated store library to read them. */
        const uint32_t cntMainLoopsCore1 = std_loadWordAtomic(&mzb_cntMainLoopsCore1)
                     , cntMainLoopsCore2 = std_loadWordAtomic(&mzt_cntMainLoopsCore2);
        
        /* Display progress. */
        printf( "Core 0: %u, Core 1: %u, Core 2: %u\r\n"
              , mza_cntMainLoopsCore0
              , cntMainLoopsCore1
              , cntMainLoopsCore2
              );

        inc_suspendAllInterrupts();
        mtx_acquireNestedMutex(&mzt_mtxDataMutexTest);
        
        /* Copy all data to not block test during very slow printf. */
        mzt_dataMutexTest_t testDataMutex = mzt_dataMutexTest;
        
        mtx_releaseNestedMutex(&mzt_mtxDataMutexTest);
        inc_resumeAllInterrupts();

        assert(testDataMutex.cntCore0Success
               + testDataMutex.cntCore1Success
               + testDataMutex.cntCore2Success
               == testDataMutex.totalCntSuccess
              );

const uint32_t tiStart = stm_getTimerValue(/* idxTimer */ 0);

        printf( "Mutex test:\r\n"
                "  %lu successful cycles, (%.1f%%, %.1f%%, %.1f%%)\r\n"
              , testDataMutex.totalCntSuccess
              , f2d(100.0f*(float)testDataMutex.cntCore0Success/testDataMutex.totalCntSuccess)
              , f2d(100.0f*(float)testDataMutex.cntCore1Success/testDataMutex.totalCntSuccess)
              , f2d(100.0f*(float)testDataMutex.cntCore2Success/testDataMutex.totalCntSuccess)
              );

const uint32_t tiPrintf = stm_getTimerValue(/* idxTimer */ 0) - tiStart;
printf("Times for printf: %u\r\n", tiPrintf);

        /* Test of intercore critical section. This code is running on core 0. */
        unsigned int u1 TYP_DBG_ONLY, u2 TYP_DBG_ONLY;
        mtx_enterIntercoreCriticalSection(&mza_csTestOfCriticalSection);
        u1 = mza_csTestData1++;
        u2 = mza_csTestData2++;
        mtx_leaveIntercoreCriticalSection(&mza_csTestOfCriticalSection);
        assert(u1 == u2);

        /* Toggle the bottom most LED. */
        lbd_setLED(mza_ledCore0Main, isOn=!isOn);
    }
} /* End of main */

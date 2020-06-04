/**
 * @file syc_systemConfiguration.c
 * System configuration: Here we have the C entry function for the Z4A core. It completes
 * the HW initialization (clocks run at full speed, peripheral bridge is widely opened,
 * SMPU is configured) and initializes a few I/O drivers, e.g. LED drivers and serial I/O
 * with the host. Then it configures tasks and I/O drivers as required for the application.
 * It starts the safe-RTOS kernel on the core Z4A and starts the other core Z4B.\n
 *   Most of the code in this file is executed in supervisor mode and belongs to the sphere
 * of trusted code.
 *
 * Copyright (C) 2019-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   syc_startSecondaryCore
 *   main
 * Local functions
 *   taskInitProcess
 *   isrPit1
 *   isrPit2
 *   isrPit3
 *   osInstallInterruptServiceRoutines
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "ccl_configureClocks.h"
#include "xbs_crossbarSwitch.h"
#include "stm_systemTimer.h"
#include "lbd_ledAndButtonDriver.h"
#include "sio_serialIO.h"
#include "rtos.h"
#include "gsl_systemLoad.h"
#include "tcx_testContext.h"
#include "prr_processReporting.h"
#include "prf_processFailureInjection.h"
#include "prs_processSupervisor.h"
#include "syc_systemConfiguration.h"
#include "std_decoratedStorage.h"
#include "msc_mainSecondCore.h"


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

/** The current, averaged CPU load in tens of percent. */
volatile unsigned int SDATA_OS(syc_cpuLoad) = 1000;

/** A counter of the invocations of the otherwise useless PIT3 ISR. */
volatile unsigned long long SBSS_OS(syc_cntISRPit3) = 0;

/** Interface with assembly code: Here's a variable in the assembly startup code, which
    takes the addresses of the C main function to be invoked on core Z4B. It needs to be
    initialized prior to starting the core. Z4B and Z2 may use the same function.
      @todo Why can't we place the declaration locally into the function where it is used?
    The compiler rejects it due to the section attribute. */
/// @todo Bad section. Don't we require cache inhibitted? And surely not in P1!
extern void (*volatile SECTION(.bss.startup) sup_main_Z4B)(signed int, const char **);

/** Interface with assembly code: Here's a variable in the assembly startup code, which
    takes the addresses of the C main function to be invoked on core Z2. It needs to be
    initialized prior to starting the core. Z4B and Z2 may use the same function. */
extern void (*volatile SECTION(.bss.startup) sup_main_Z2)(signed int, const char **);


/*
 * Function implementation
 */

/**
 * Initialization task of process \a PID.
 *   @return
 * The function returns the Boolean descision, whether the initialization was alright and
 * the system can start up. "Not alright" is expressed by a negative number, which hinders
 * the RTOS to startup.
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @remark
 * In this sample, we demonstrate that different processes' tasks can share the same task
 * function implementation. This is meant a demonstration of the technical feasibility but
 * not of good practice; the implementation needs to use shared memory, which may break a
 * safety constraint, and it needs to consider the different privileges of the processes.
 */
static int32_t taskInitProcess(uint32_t PID)
{
    static unsigned int SHARED(cnt_) = 0;
    ++ cnt_;

    /* Only process 1 has access to the C lib (more precise: to those functions of the C
       lib, which write to lib owned data objects) and can write a status message. */
    if(PID == 1)
        iprintf("taskInitPID%lu(): %u\r\n", PID, cnt_);

    return cnt_ == PID? 0: -1;

} /* End of taskInitProcess */



/**
 * A regularly triggered interrupt handler for the timer PIT1. The handler starts a user
 * task, which belongs to the failing process. In this process it has the highest priority.
 * The ISR must not be affected by the failures occurring in that process.
 *   @remark
 * This is a normal interrupt running in the kernel context (supervisor mode, no MPU
 * restrictions).
 */
static void isrPit1(void)
{
    static unsigned int SDATA_OS(cnt_) = 0;

    /* Directly start a user task. It is executed synchronously with this ISR and on the
       same priority level. */
    static const rtos_taskDesc_t taskConfig = { .addrTaskFct = (uintptr_t)prf_task1ms
                                              , .PID = syc_pidFailingTasks
                                              , .tiTaskMax = 0 //RTOS_TI_MS2TICKS(5)
                                              };
    rtos_osRunTask(&taskConfig, /* taskParam */ cnt_);
    ++ cnt_;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
    PIT->TIMER[1].TFLG = PIT_RTI_TFLG_TIF(1);

} /* End of isrPit1 */



/**
 * A regularly triggered interrupt handler for the timer PIT2. It triggers an RTOS event
 * such that the watchdog task in the supervisor process is started. As long as we don't
 * see any activation losses the watchdog task will execute synchronous with this ISR. The
 * difference to the task directly started by isrPIT1 is that the watchdog task has a lower
 * priority than the triggering ISR.
 *   @remark
 * This is a normal interrupt running in the kernel context (supervisor mode, no MPU
 * restrictions).
 */
static void isrPit2(void)
{
    /* Indirectly start a user task. It is executed asynchronously to this ISR and has its
       own, irrelated task priority level. */
    static long unsigned int cnt_ = 0;
    rtos_osTriggerEvent(syc_idEvPIT2, cnt_++);

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
     PIT->TIMER[2].TFLG = PIT_RTI_TFLG_TIF(1);

} /* End of isrPit2 */



/**
 * A regularly triggered interrupt handler for the timer PIT3. The interrupt does nothing
 * but counting a variable. It is triggered at high frequency and asynchronously to the
 * kernel's clock tick to prove the system stability and properness of the context switches.
 *   @remark
 * This is a normal interrupt running in the kernel context (supervisor mode, no MPU
 * restrictions).
 */
static void isrPit3(void)
{
    ++ syc_cntISRPit3;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
    PIT->TIMER[3].TFLG = PIT_RTI_TFLG_TIF(1);

} /* End of isrPit3 */



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
    rtos_osRegisterInterruptHandler( &isrPit1
                                   , processorID
                                   , /* vectorNum */ PIT_Ch1_IRQn
                                   , /* psrPriority */ syc_prioIrqPit1
                                   , /* isPreemptable */ true
                                   );
    rtos_osRegisterInterruptHandler( &isrPit2
                                   , processorID
                                   , /* vectorNum */ PIT_Ch2_IRQn
                                   , /* psrPriority */ syc_prioIrqPit2
                                   , /* isPreemptable */ true
                                   );
    rtos_osRegisterInterruptHandler( &isrPit3
                                   , processorID
                                   , /* vectorNum */ PIT_Ch3_IRQn
                                   , /* psrPriority */ syc_prioIrqPit3
                                   , /* isPreemptable */ true
                                   );

    /* Peripheral clock has been initialized to 40 MHz. The timers count at this rate. To
       get a 1ms interrupt tick we need to count till 40000.
         The RTOS operates in ticks of 1ms. We use prime numbers to get good asynchronity
       with the RTOS clock.
         -1: See RM, 51.6 */
    PIT->TIMER[1].LDVAL = 39989-1;/* Interrupt rate approx. 1kHz */
    PIT->TIMER[2].LDVAL = 40009-1;/* Interrupt rate approx. 1kHz for watchdog */
    PIT->TIMER[3].LDVAL = 1327-1; /* Interrupt rate approx. 30kHz */

    /* Enable timer operation. This operation affects all timer channels.
         PIT_MCR_FRZ: For this multi-core MCU it is not so easy to decide whether or not to
       let the timers be stopped on debugger entry: Any stopped core will halt the timers,
       regardless whether that core is related to the timer or not (and how should the
       debugger know...). Both possibilities can be annoying or advantageous, depending on
       the situation. */
    PIT->MCR = PIT_MCR_MDIS(0) | PIT_MCR_FRZ(1);

    /* Clear possibly pending interrupt flags. */
    PIT->TIMER[1].TFLG = PIT_TFLG_TIF(1);
    PIT->TIMER[2].TFLG = PIT_TFLG_TIF(1);
    PIT->TIMER[3].TFLG = PIT_TFLG_TIF(1);

    /* Enable interrupts by the timers and start them. See RM 51.4.10. */
    PIT->TIMER[1].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    PIT->TIMER[2].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    PIT->TIMER[3].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);

} /* End of osInstallInterruptServiceRoutines */



/**
 * Start a secondary core. The initial core is already started and it is the one, which will
 * typically execute this function.
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
void syc_startSecondaryCore( unsigned int idxCore
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

        /* Ensure that the value has been written into main memory before we do the mode
           change below. */
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

        /* Ensure that the value has been written into main memory before we do the mode
           change below. */
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

} /* End of syc_startSecondaryCore */



/**
 * Entry point into C code. The C main function is entered without arguments and despite
 * of its usual return code definition it must never be left in this environment.
 * (Returning from main would enter an infinite loop in the calling assembler startup
 * code.)
 */
int /* _Noreturn */ main(int noArgs ATTRIB_DBG_ONLY, const char *argAry[] ATTRIB_DBG_ONLY)
{
    assert(noArgs == 1  && strcmp(argAry[0], "Z4A") == 0);

    /* Complete the core HW initialization - as far as not yet done by the assembly startup
       code. */

    /* All clocks run at full speed, including all peripheral clocks. */
    ccl_configureClocks();

    /* Interrupts become usable and configurable by SW. */
    rtos_osInitINTCInterruptController();

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

    /* The core is now running in the desired state. I/O driver initialization follows to
       the extend required by this simple sample. */

    /* Start the system timers for execution time measurement.
         Caution: On the MPC5748G, this is not an opton but an essential prerequisite for
       running safe-RTOS. The MPC5748G has a simplified z4 core without the timebase
       feature. The system timer is used as substitute. The driver needs to be started and
       it must be neither changed nor re-configured without carefully double-checking the
       side-effects on the kernel! */
    stm_osInitSystemTimers();

    /* Initialize the button and LED driver for the eval board. */
    lbd_osInitLEDAndButtonDriver( /* onButtonChangeCallback_core0 */ NULL
                                , /* PID_core0 */                    0
#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
                                , /* onButtonChangeCallback_core1 */ msc_onButtonChangeCallback
                                , /* PID_core1 */                    1
                                , /* onButtonChangeCallback_core2 */ NULL
                                , /* PID_core2 */                    0
#elif RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
                                , /* onButtonChangeCallback_core1 */ NULL
                                , /* PID_core1 */                    0
                                , /* onButtonChangeCallback_core2 */ msc_onButtonChangeCallback
                                , /* PID_core2 */                    1
#endif
                                , /* tiMaxTimeInUs */                1000
                                );

    /* Initialize the serial output channel as prerequisite of using printf. */
    sio_osInitSerialInterface(/* baudRate */ 115200);

    /* Register the process initialization tasks. Here, we used always the same function. */
    bool initOk = true;
    unsigned int u;
    for(u=1; u<=3; ++u)
    {
        if(rtos_osRegisterInitTask(taskInitProcess, /* PID */ u, /* tiTaskMaxInUs */ 1000)
           != rtos_err_noError
          )
        {
            initOk = false;
        }
    }

    /* Create the events that trigger application tasks at the RTOS. Note, we do not really
       respect the ID, which is assigned to the event by the RTOS API rtos_osCreateEvent().
       The returned value is redundant. This technique requires that we create the events
       in the right order and this requires in practice a double-check by assertion - later
       maintenance errors are unavoidable otherwise. */
    unsigned int idEvent;
    if(rtos_osCreateEvent
                    ( &idEvent
                    , /* tiCycleInMs */              997 /* about 1s but prime to others */
                    , /* tiFirstActivationInMs */    19
                    , /* priority */                 syc_prioEvReporting
                    , /* minPIDToTriggerThisEvent */ RTOS_EVENT_NOT_USER_TRIGGERABLE
                    , /* taskParam */                0
                    )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    else
        assert(idEvent == syc_idEvReporting);

    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              10
                         , /* tiFirstActivationInMs */    0
                         , /* priority */                 syc_prioEvTest
                         , /* minPIDToTriggerThisEvent */ RTOS_EVENT_NOT_USER_TRIGGERABLE
                         , /* taskParam */                0
                         )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    else
        assert(idEvent == syc_idEvTest);

    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              11
                         , /* tiFirstActivationInMs */    0
                         , /* priority */                 syc_prioEvTestCtxSw
                         , /* minPIDToTriggerThisEvent */ RTOS_EVENT_NOT_USER_TRIGGERABLE
                         , /* taskParam */                0
                         )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    else
        assert(idEvent == syc_idEvTestCtxSw);

    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              0
                         , /* tiFirstActivationInMs */    0
                         , /* priority */                 syc_prioEvPIT2
                         , /* minPIDToTriggerThisEvent */ RTOS_EVENT_NOT_USER_TRIGGERABLE
                         , /* taskParam */                0
                         )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    else
        assert(idEvent == syc_idEvPIT2);

    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              17
                         , /* tiFirstActivationInMs */    0
                         , /* priority */                 syc_prioEv17ms
                         , /* minPIDToTriggerThisEvent */ RTOS_EVENT_NOT_USER_TRIGGERABLE
                         , /* taskParam */                0
                         )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    else
        assert(idEvent == syc_idEv17ms);

    /* The tasks are associated with the events. We have two tasks, which are not triggered
       by the RTOS scheduler but by independent interrupts. One is triggered through an
       event from an asynchronous interrupt service routine (i.e. it may run on a lower
       priority as the ISR) and the other one is directly started from the ISR and
       necessarily shares the priority with the ISR. This one is the only task, which is
       not found here in the list of registrations. */
    if(rtos_osRegisterUserTask( syc_idEvReporting
                              , prr_taskReporting
                              , syc_pidReporting
                              , /* tiTaskMaxInUs */ 1500000
                              )
       != rtos_err_noError
      )
    {
        initOk = false;
    }

    /* The next three tasks share the same event for triggering. The order of registration
       matters: When the event becomes due the tasks will activated in the order of
       registration. We need to first see the task, which commands the (failing) action to
       take, then the task which executes the action and finally the task, which
       double-checks the system behavior. */
    if(rtos_osRegisterUserTask( syc_idEvTest
                              , prs_taskCommandError
                              , syc_pidSupervisor
                              , /* tiTaskMaxInUs */ 1500
                              )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    if(rtos_osRegisterUserTask( syc_idEvTest
                              , prf_taskInjectError
                              , syc_pidFailingTasks
                              , /* tiTaskMaxInUs */ 2500
                              )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    if(rtos_osRegisterUserTask( syc_idEvTest
                              , prs_taskEvaluateError
                              , syc_pidSupervisor
                              , /* tiTaskMaxInUs */ 1500
                              )
       != rtos_err_noError
      )
    {
        initOk = false;
    }

    if(rtos_osRegisterUserTask( syc_idEvTestCtxSw
                              , prr_taskTestContextSwitches
                              , syc_pidReporting
                              , /* tiTaskMaxInUs */ 0
                              )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    if(rtos_osRegisterUserTask( syc_idEvPIT2
                              , prs_taskWatchdog
                              , syc_pidSupervisor
                              , /* tiTaskMaxInUs */ 0
                              )
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    if(rtos_osRegisterUserTask( syc_idEv17ms
                              , prf_task17ms
                              , syc_pidFailingTasks
                              , /* tiTaskMaxInUs */ 0
                              )
       != rtos_err_noError
      )
    {
        initOk = false;
    }

    /* The watchdog uses the reporting process, which owns the C library and can do a
       printf, to regularly print a progress message. We need to grant the required
       permissions. */
    rtos_osGrantPermissionRunTask( /* pidOfCallingTask */ syc_pidSupervisor
                                 , /* targetPID */ syc_pidReporting
                                 );

    /* The watchdog uses service rtos_suspendProcess() if it recognizes an error. We need
       to grant the required permissions. */
    rtos_osGrantPermissionSuspendProcess( /* pidOfCallingTask */ syc_pidSupervisor
                                        , /* targetPID */ syc_pidFailingTasks
                                        );

    /* Initialize the RTOS kernel. The global interrupt processing is resumed if it
       succeeds. The step involves a configuration check. We must not startup the SW if the
       check fails. */
    if(!initOk ||  rtos_osInitKernel() != rtos_err_noError)
        while(true)
            ;

    /* Installing more interrupts should be possible while the system is already running. */
    osInstallInterruptServiceRoutines();

    /* Only after initialization of the RTOS, we start the next core. This is because the
       function to register the interrupt handlers at the global, shared interrupt
       controller is not cross-core safe under all circumstances. This was we simply avoid
       any race condition. For the same reason, the next core will start the third one
       after it reached the same point. */
    const unsigned int idxSecondRTOSCore =
#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
        1; /* Z4B */
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
        2; /* Z2 */
#endif
    syc_startSecondaryCore(idxSecondRTOSCore, msc_mainSecondCore);

    /* The code down here becomes our idle task. It is executed when and only when no
       application task or ISR is running. */

    while(true)
    {
        /* Compute the average CPU load. Note, this operation lasts about 1.5s and has a
           significant impact on the cycling speed of this infinite loop. Furthermore, it
           measures only the load produced by the tasks and system interrupts but not that
           of the rest of the code in the idle loop. */
        syc_cpuLoad = gsl_osGetSystemLoad();
    }
} /* End of main */

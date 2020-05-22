/**
 * @file mai_main.c
 *   C entry function. The core completes the HW initialization (clocks run at full speed,
 * drivers for MPU and devices are initialized).\n
 *   The safe-RTOS is configured to run a few tasks, both OS and user mode tasks, which
 * drive the user LEDs. The user tasks injects a very few failures in order to demonstrate
 * the error catching capabilities of the RTOS.\n
 *   Only if all the LEDs are blinking everything is alright.\n
 *   Progress information is permanently written into the serial output channel. A terminal
 * on the development host needs to use these settings: 115000 Bd, 8 Bit data word, no
 * parity, 1 stop bit.
 *
 * Copyright (C) 2017-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   main
 * Local functions
 *   taskInitProcess
 *   isrPit1
 *   isrPit2
 *   isrPit3
 *   taskUserPit2
 *   taskUser1ms
 *   taskUser10ms
 *   taskUser100ms
 *   taskUser1000ms
 *   taskOSIdle
 *   taskOS1ms
 *   taskOS5ms
 *   taskOS10ms
 *   taskSafety1ms
 *   osInstallInterruptServiceRoutines
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
#include "stm_systemTimer.h"
#include "lbd_ledAndButtonDriver.h"
#include "sio_serialIO.h"
#include "rtos.h"
#include "del_delay.h"
#include "gsl_systemLoad.h"
//#include "mai_main.h"


/*
 * Defines
 */

/* The demo simulates a typical true RTOS application. These macros specify how much load
   each  task produces. The values mean CPU load in percent. */
#define LOAD_TASK_SAFETY_1MS    2
#define LOAD_TASK_PIT2          5
#define LOAD_TASK_1MS           5
#define LOAD_TASK_10MS          35
#define LOAD_TASK_100MS         7
#define LOAD_TASK_1000MS        5
#define LOAD_TASK_OS_1MS        3
#define LOAD_TASK_OS_5MS        5
#define LOAD_TASK_OS_10MS       5

/** Configuration of simulation: The fraction of the computation time a task typically
    spends in its pro- or epilogue, which means copying of in- and output data inside a
    critical section. */
#define REL_LOAD_TASK_INTERFACE     0.05f

/** Configuration of simulation: The fraction of the computation time a task typically
    spends in its true activities - outside of critical sections. */
#define REL_LOAD_TASK_COMPUTATION   (1.0f - 2.0f*(REL_LOAD_TASK_INTERFACE))


/** A wrapper around the API for the priority ceiling protocol (PCP), which lets the API
    for mutual exclusion of a task set look similar to the API calls from the OSEK/VDX
    standard.
      Here, for getting the resource, i.e. for entering a critical section of code. */
#define getResource(maxPrioOfCompetingTasks) \
            rtos_suspendAllTasksByPriority(maxPrioOfCompetingTasks)

/** A wrapper around the API for the priority ceiling protocol (PCP), which lets the API
    for mutual exclusion of a task set look like the API calls from the OSEK/VDX standard.
      Here, for returning the resource, i.e. for leaving a critical section of code. */
#define releaseResource(prioOfTask) rtos_resumeAllTasksByPriority(prioOfTask)

/** A wrapper around the API for the priority ceiling protocol (PCP), which lets the API
    for mutual exclusion of a task set look like the API calls from the OSEK/VDX standard.
      Here, for getting the resource, i.e. for entering a critical section of code.\n
      Here for OS tasks (including idle task). */
#define osGetResource(maxPrioOfCompetingTasks) \
            rtos_osSuspendAllTasksByPriority(maxPrioOfCompetingTasks)

/** A wrapper around the API for the priority ceiling protocol (PCP), which lets the API
    for mutual exclusion of a task set look like the API calls from the OSEK/VDX standard.\n
      Here, for returning the resource, i.e. for leaving a critical section of code.\n
      Here for OS tasks (including idle task). */
#define osReleaseResource(prioOfTask) rtos_osResumeAllTasksByPriority(prioOfTask)

/** Helper macro to produce the wanted CPU load in the simulation of a typical task. It
    simply consumes a given amount of computation time by busy wait. The time is meant in
    true CPU instructions, not as world time. Preemptions of the calling task will
    accordingly prolong the time till return from busyWait.
      @param cpuLoad The average CPU load produced by this macro given it is called in
    every activation of a cyclic task with cycle time \a tiCycleInMs.
      @param tiCycleInMs The cycle time of the simulated, cyclic task, which makes use of
    the macro. */
#define busyWait(cpuLoad, tiCycleInMs) \
            del_delayMicroseconds \
                (/* tiCpuInUs */ (uint32_t)((cpuLoad)/100.0f * tiCycleInMs * 1000.0f + 0.5))


/*
 * Local type definitions
 */

/** The enumeration of all events, tasks and priorities, to have them as symbols in the
    source code. Most relevant are the event IDs. Actually, these IDs are provided by the
    RTOS at runtime, when creating the event. However, it is guaranteed that the IDs, which
    are dealt out by rtos_osCreateEvent() form the series 0, 1, 2, .... So we don't need
    to have a dynamic storage of the IDs; we define them as constants and double-check by
    assertion that we got the correct, expected IDs from rtos_osCreateEvent(). Note, this
    requires that the order of creating the events follows the order here in the
    enumeration.\n
      Here we have the IDs of the created events. They occupy the index range starting from
    zero. */
enum idEvent_t
{
    idEv1msSafety = 0,  /// Event for safety task
    idEvPit2,           /// Event for task following the PIT2 interrupt
    idEv1ms,            /// Event for cyclic tasks of 1 ms
    idEv5ms,            /// Event for cyclic tasks of 5 ms
    idEv10ms,           /// Event for cyclic tasks of 10 ms
    idEv100ms,          /// Event for cyclic tasks of 100 ms
    idEv1000ms,         /// Event for cyclic tasks of 1000 ms

    /** The number of events. */
    noRegisteredEvents
};


/** The RTOS uses constant priorities for its events, which are defined here.\n
      Note, the priority is a property of an event rather than of a task. A task implicitly
    inherits the priority of the event it is associated with. */
enum prioEvent_t
{
    prioTaskIdle = 0,   /// Prio 0 of idle task is implicit, cannot be chosen explicitly
    prioEv1000ms,       /// Prio of event for cyclic tasks of 1000 ms
    prioEv100ms,        /// Prio of event for cyclic tasks of 100 ms
    prioEv10ms,         /// Prio of event for cyclic tasks of 10 ms
    prioEv5ms,          /// Prio of event for cyclic tasks of 5 ms
    prioEv1ms,          /// Prio of event for cyclic tasks of 1 ms
    prioEvPit2,         /// Prio of event triggered from the ISR for the PIT2 interrupt
    prioEv1msSafety = RTOS_MAX_LOCKABLE_TASK_PRIORITY+1,  /// Event for safety task
};


/** The INTC priorities of the interrupts in use. These priorities constitute another space
    as the task priorities. */
enum prioIRQ_t
{
    prioIrqPit1 = RTOS_KERNEL_IRQ_PRIORITY_CORE_0-2,   /** INTC priority of timer IRQ PIT1 */
    prioIrqPit2 = RTOS_KERNEL_IRQ_PRIORITY_CORE_0,     /** INTC priority of timer IRQ PIT2 */
    prioIrqPit3 = RTOS_KERNEL_IRQ_PRIORITY_CORE_0+3,   /** INTC priority of timer IRQ PIT3 */
};


/** In safe-RTOS a task belongs to a process, characterized by the PID, 1..4. The
    relationship is defined here.\n
      Note, a process needs to be configured in the linker script (actually: assignment of
    stack space) before it can be used. */
enum pidOfTask_t
{
    pidOs = 0,         /* Kernel always and implicitly has PID 0 */
    pidTaskIdle = 0,   /* Prio 0 of idle task is implicit, cannot be chosen explicitly */
    pidTask1000ms = 1, /* PID of cyclic 1000 ms user task */
    pidTask100ms = 1,  /* PID of cyclic 100 ms user task */
    pidTask10ms = 1,   /* PID of cyclic 10 ms user task */
    pidTask1ms = 1,    /* PID of cyclic 1 ms user task */
    pidTaskPit2 = 1,   /* PID of user task that is triggered by asynchronous interrupt */
    pidOsTask10ms,     /* PID of cyclic 10 ms OS task */
    pidOsTask5ms,      /* PID of cyclic 5 ms OS task */
    pidOsTask1ms,      /* PID of cyclic 1 ms OS task */
    pidTask1msSafety = 2,  /* PID for safety task */
};




/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** Counter of calls of ISR for PIT1 interrupt. */
volatile unsigned long SBSS_OS(mai_cntISRPit1) = 0;

/** Counter of calls of ISR for PIT2 interrupt. */
volatile unsigned long SBSS_OS(mai_cntISRPit2) = 0;

/** Counter of calls of ISR for PIT3 interrupt. */
volatile unsigned long SBSS_OS(mai_cntISRPit3) = 0;

/** Counter of asynchronous event task, triggered from PIT2 interrupt. */
volatile unsigned long SBSS_P1(mai_cntTaskUserPit2) = 0;

/** Counter of cyclic safety task. */
volatile unsigned long SBSS_P2(mai_cntTaskSafety1ms) = 0;

/** Counter of cycles of infinite main loop. */
volatile unsigned long SBSS_OS(mai_cntTaskIdle) = 0;

/** The average CPU load produced by all tasks and interrupts in tens of percent. */
unsigned int SDATA_OS(mai_cpuLoad) = 1000;


/*
 * Function implementation
 */

/**
 * Initialization task of process \a PID.
 *   @return
 * The function returns the Boolean decision, whether the initialization was alright and
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
    _Static_assert(prioTaskIdle == 0
                   &&  prioEv1000ms > prioTaskIdle
                   &&  prioEv100ms > prioEv1000ms
                   &&  prioEv10ms > prioEv100ms
                   &&  prioEv5ms > prioEv10ms
                   &&  prioEv1ms > prioEv5ms
                   &&  prioEvPit2 > prioEv1ms
                   &&  prioEvPit2 <= RTOS_MAX_LOCKABLE_TASK_PRIORITY
                   &&  prioEv1msSafety > RTOS_MAX_LOCKABLE_TASK_PRIORITY
                  , "Bad task priority configuration"
                  );

    static unsigned int SHARED(cnt_) = 0;
    ++ cnt_;

    /* Scheduler test: Check order of initialization calls. */
    assert(cnt_ == PID);
    return cnt_ == PID? 0: -1;

} /* End of taskInitProcess */



/**
 * A regularly triggered interrupt handler for the timer PIT1. The interrupt does nothing
 * but counting a variable. It is triggered at medium frequency and asynchronously to the
 * kernel's clock tick to prove the system stability and properness of the context
 * switches.
 *   @remark
 * This is a normal interrupt running in the kernel context (supervisor mode, no MPU
 * restrictions).
 */
static void isrPit1(void)
{
    ++ mai_cntISRPit1;

    /* RM 51.4.11, p. 2738f: Acknowledge the interrupt in the causing HW device. Can be
       done as this is "trusted code" that is running in supervisor mode. */
    PIT->TIMER[1].TFLG = PIT_RTI_TFLG_TIF(1);

} /* End of isrPit1 */



/**
 * A regularly triggered interrupt handler for the timer PIT2. The interrupt does nothing
 * but counting a variable. It is triggered at high frequency and asynchronously to the
 * kernel's clock tick to prove the system stability and properness of the context switches.
 *   @remark
 * This is a normal interrupt running in the kernel context (supervisor mode, no MPU
 * restrictions).
 */
static void isrPit2(void)
{
    ++ mai_cntISRPit2;

    /* This ISR delegates some computation to a user task. It triggers the task. */
    const unsigned long tmpCntTaskUserPit2 ATTRIB_DBG_ONLY = mai_cntTaskUserPit2;
    const bool evCouldBeTriggered ATTRIB_DBG_ONLY =
                        rtos_osTriggerEvent(idEvPit2, /* taskParam */ mai_cntTaskUserPit2);
    assert(evCouldBeTriggered);

    /* There must be no immediate counter change of the task. It will be started after
       return from the ISR and depending on the task priorities. */
    assert(tmpCntTaskUserPit2 == mai_cntTaskUserPit2);

    /* RM 51.4.11, p. 2738f: Acknowledge the interrupt in the causing HW device. Can be
       done as this is "trusted code" that is running in supervisor mode. */
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
    ++ mai_cntISRPit3;

    /* RM 51.4.11, p. 2738f: Acknowledge the interrupt in the causing HW device. Can be
       done as this is "trusted code" that is running in supervisor mode. */
    PIT->TIMER[3].TFLG = PIT_RTI_TFLG_TIF(1);

} /* End of isrPit3 */



/**
 * Simulated user task. It is characterized mainly by the CPU load in percent is requires
 * to complete.
 *   A small, fixed fraction of the load is spent for the in- and output of the task. We
 * simulate the concept that at the beginning of the task some data is copied into local
 * task storage, before the actual task computations start and that - after computation -
 * another small fraction of the computation time is required to store the data for use by
 * other tasks.
 *   For our intention, getting a measure for the cost of the kernel, the actual
 * operations, copying data, doing some computations, copying data, doesn't matter at all.
 * However, it matters that copying data has to be done inside critical sections. This has
 * an impact on scheduling timing and it is a relative expensive operation for a safe
 * kernel, which must not offer the cheap suspension of all interrupts.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process. This mechanism is used to report a problem in PRODUCTION
 * compilation, when we have no assertions available.
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @param taskParam
 * A variable task parameter. Here just used for testing.
 */
static int32_t taskUserPit2(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_DBG_ONLY)
{
    bool success = true;

    assert(taskParam == mai_cntTaskUserPit2);

    /* Simulate the task prologue: All input data is copied to local storage. A critical
       section is granted implicitly since this task has the highest priority. According
       code is omitted and we can combine all busy waits to a single one. */

    /* Simulate the task activity: Computation of results. Note, this task is triggered by
       an asynchronous interrupt but we still use a regular one (5 kHz) so that we can use
       our normal macro to produce defined CPU load. */
    busyWait(LOAD_TASK_PIT2, /* tiCycleInMs */ 0.2f);

    /* Increment the alive counter of the task. */
    ++ mai_cntTaskUserPit2;

    return success? 0: -1;

} /* End of taskUserPit2 */




/**
 * Simulated user task. It is characterized mainly by the CPU load in percent is requires
 * to complete.
 *   A small, fixed fraction of the load is spent for the in- and output of the task. We
 * simluate the concept that at the beginning of the task some data is copied into local
 * task storage, before the actual task computations start and that - after computation -
 * another small fraction of the computation time is required to store the data for use by
 * other tasks.
 *   For our intention, getting a measure for the cost of the kernel, the actual
 * operations, copying data, doing some computations, copying data, doesn't matter at all.
 * However, it matters that copying data has to be done inside critical sections. This has
 * an impact on scheduling timing and it is a relative expensive operation for a safe
 * kernel, which must not offer the cheap suspension of all interrupts.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process. This mechanism is used to report a problem in PRODUCTION
 * compilation, when we have no assertions available.
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
#define USER_TASK(tiCycleInMs, cpuLoad, prioCritSec)                                        \
                                                                                            \
/** Counter of cycles of infinite main loop. */                                             \
volatile unsigned long SBSS_P1(mai_cntTaskUser##tiCycleInMs##ms) = 0;                       \
                                                                                            \
static int32_t taskUser##tiCycleInMs##ms( uint32_t PID ATTRIB_UNUSED                        \
                                        , uintptr_t taskParam ATTRIB_UNUSED                 \
                                        )                                                   \
{                                                                                           \
    bool success = true;                                                                    \
                                                                                            \
    /* Simulate the task prologue: All input data is copied to local storage. This is done  \
       in a critical section, which includes all competing tasks. */                        \
    if(prioEv##tiCycleInMs##ms < prioCritSec){ getResource(prioCritSec); }                  \
    busyWait(REL_LOAD_TASK_INTERFACE*cpuLoad, tiCycleInMs);                                 \
    if(prioEv##tiCycleInMs##ms < prioCritSec){ releaseResource(prioEv##tiCycleInMs##ms); }  \
                                                                                            \
    /* Simulate the task activity: Computation of results. */                               \
    busyWait(REL_LOAD_TASK_COMPUTATION*cpuLoad, tiCycleInMs);                               \
    /* Increment the alive counter of the task. */                                          \
    ++ mai_cntTaskUser##tiCycleInMs##ms;                                                    \
                                                                                            \
    /* Simulate the task epilogue: All computed data is copied to shared, global storage.   \
       This is done in a critical section, which includes all competing tasks. */           \
    if(prioEv##tiCycleInMs##ms < prioCritSec){ getResource(prioCritSec); }                  \
    busyWait(REL_LOAD_TASK_INTERFACE*cpuLoad, tiCycleInMs);                                 \
    if(prioEv##tiCycleInMs##ms < prioCritSec){ releaseResource(prioEv##tiCycleInMs##ms); }  \
                                                                                            \
    return success? 0: -1;                                                                  \
                                                                                            \
} /* End of taskUser##tiCycleInMs##ms */                                                    \
                                                                                            \
/* End of macro USER_TASK */

USER_TASK(/* tiCycleInMs */ 1,    /* cpuLoad */ LOAD_TASK_1MS,    /* prioCritSec */ prioEv1ms)
USER_TASK(/* tiCycleInMs */ 10,   /* cpuLoad */ LOAD_TASK_10MS,   /* prioCritSec */ prioEv5ms)
USER_TASK(/* tiCycleInMs */ 100,  /* cpuLoad */ LOAD_TASK_100MS,  /* prioCritSec */ prioEv10ms)
USER_TASK(/* tiCycleInMs */ 1000, /* cpuLoad */ LOAD_TASK_1000MS, /* prioCritSec */ prioEv10ms)

#undef USER_TASK




/**
 * Simulated OS task. It is characterized mainly by the CPU load in percent is requires
 * to complete.
 *   A small, fixed fraction of the load is spent for the in- and output of the task. We
 * simulate the concept that at the beginning of the task some data is copied into local
 * task storage, before the actual task computations start and that - after computation -
 * another small fraction of the computation time is required to store the data for use by
 * other tasks.
 *   For our intention, getting a measure for the cost of the kernel, the actual
 * operations, copying data, doing some computations, copying data, don't matter at all.
 * However, it matters that copying data has to be done inside critical sections. This has
 * an impact on scheduling timing and it is a relative expensive operation for a safe
 * kernel, which must not offer the cheap suspension of all interrupts.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
#define OS_TASK(tiCycleInMs, cpuLoad, prioCritSec)                                          \
                                                                                            \
/** Counter of cycles of infinite main loop. */                                             \
volatile unsigned long SBSS_OS(mai_cntTaskOS##tiCycleInMs##ms) = 0;                         \
                                                                                            \
static void taskOS##tiCycleInMs##ms(uintptr_t taskParam ATTRIB_UNUSED)                      \
{                                                                                           \
    /* Simulate the task prologue: All input data is copied to local storage. This is done  \
       in a critical section, which includes all competing tasks. */                        \
    if(prioEv##tiCycleInMs##ms < prioCritSec){ osGetResource(prioCritSec); }                \
    busyWait(REL_LOAD_TASK_INTERFACE*cpuLoad, tiCycleInMs);                                 \
    if(prioEv##tiCycleInMs##ms < prioCritSec){ osReleaseResource(prioEv##tiCycleInMs##ms); }\
                                                                                            \
    /* Simulate the task activity: Computation of results. */                               \
    busyWait(REL_LOAD_TASK_COMPUTATION*cpuLoad, tiCycleInMs);                               \
    /* Increment the alive counter of the task. */                                          \
    ++ mai_cntTaskOS##tiCycleInMs##ms;                                                      \
                                                                                            \
    /* Simulate the task epilogue: All computed data is copied to shared, global storage.   \
       This is done in a critical section, which includes all competing tasks. */           \
    if(prioEv##tiCycleInMs##ms < prioCritSec){ osGetResource(prioCritSec); }                \
    busyWait(REL_LOAD_TASK_INTERFACE*cpuLoad, tiCycleInMs);                                 \
    if(prioEv##tiCycleInMs##ms < prioCritSec){ osReleaseResource(prioEv##tiCycleInMs##ms); }\
                                                                                            \
} /* End of taskOS##tiCycleInMs##ms */                                                      \
                                                                                            \
/* End of macro OS_TASK */

OS_TASK(/* tiCycleInMs */ 1,  /* cpuLoad */ LOAD_TASK_OS_1MS,  /* prioCritSec */ prioEvPit2)
OS_TASK(/* tiCycleInMs */ 5,  /* cpuLoad */ LOAD_TASK_OS_5MS,  /* prioCritSec */ prioEv1ms)
OS_TASK(/* tiCycleInMs */ 10, /* cpuLoad */ LOAD_TASK_OS_10MS, /* prioCritSec */ prioEv10ms)

#undef OS_TASK


/**
 * Simulated safety task. It is characterized mainly by the CPU load in percent is requires
 * to complete.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t taskSafety1ms(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    busyWait(LOAD_TASK_SAFETY_1MS, /* tiCycleInMs */ 1);

    /* Increment the alive counter of the task. */
    ++ mai_cntTaskSafety1ms;

    return 0;

} /* End of taskSafety1ms */



/**
 * Idle task implementation.
 */
static void taskOSIdle(void)
{
    /* Compute the average CPU load. Note, this operation lasts about 1.5s and has a
       significant impact on the cycling speed of the idle task. Furthermore, it
       measures only the load produced by the tasks and system interrupts but not that
       of the rest of the code in this function. Therefore, we can do some supervision and
       reporting without biasing the measurement results. */
    mai_cpuLoad = gsl_osGetSystemLoad();
    const unsigned int simulatedCpuLoad = (LOAD_TASK_SAFETY_1MS
                                           + LOAD_TASK_PIT2
                                           + LOAD_TASK_1MS
                                           + LOAD_TASK_10MS
                                           + LOAD_TASK_100MS
                                           + LOAD_TASK_1000MS
                                           + LOAD_TASK_OS_1MS
                                           + LOAD_TASK_OS_5MS
                                           + LOAD_TASK_OS_10MS
                                          ) * 10;
    unsigned int cpuLoadKernel = simulatedCpuLoad;
    if(mai_cpuLoad > cpuLoadKernel)
        cpuLoadKernel = mai_cpuLoad - cpuLoadKernel;
    else
        cpuLoadKernel = 0;

    /* Make spinning of the idle task observable in the debugger. */
    ++ mai_cntTaskIdle;

    const unsigned int stackReserveOs = rtos_getStackReserve(/* idxCore */ 0, pidOs)
                     , stackReserveP1 = rtos_getStackReserve(/* idxCore */ 0, /* PID */ 1)
                     , stackReserveP2 = rtos_getStackReserve(/* idxCore */ 0, /* PID */ 2);

    const bool success = rtos_getNoTotalTaskFailure(/* PID */ 1) == 0
                         &&  rtos_getNoTotalTaskFailure(/* PID */ 2) == 0
                         &&  stackReserveOs >= 3072
                         &&  stackReserveP1 >= 1024
                         &&  stackReserveP2 >= 1024
                         ;
    char msg[256];
    signed int noChar;
    if(success)
    {
        /* Normal operation: Let the first LED blink slowly. */
        lbd_osSetLED(lbd_led_0_DS11, /* isOn */ (mai_cntTaskIdle & 1) != 0);
        /* Print some results. */

        noChar = sniprintf( msg, sizeof(msg)
                          , "CPU load: %u%% (Simulated: %u%%, kernel: %u ppmille)\r\n"
                          , (mai_cpuLoad+5)/10
                          , (simulatedCpuLoad+5)/10
                          , cpuLoadKernel
                          );
        assert((unsigned)noChar < sizeOfAry(msg));
        sio_osWriteSerial(msg, (unsigned)noChar);

        noChar = sniprintf( msg, sizeof(msg)
                          , "Cycles user tasks (Pit2, 1, 10, 100, 1000 ms): %lu, %lu, %lu,"
                            " %lu, %lu\r\n"
                          , mai_cntTaskUserPit2
                          , mai_cntTaskUser1ms
                          , mai_cntTaskUser10ms
                          , mai_cntTaskUser100ms
                          , mai_cntTaskUser1000ms
                          );
        assert((unsigned)noChar < sizeOfAry(msg));
        sio_osWriteSerial(msg, (unsigned)noChar);

        noChar = sniprintf( msg, sizeof(msg)
                          , "Cycles OS tasks (1, 5, 10 ms): %lu, %lu, %lu\r\n"
                          , mai_cntTaskOS1ms
                          , mai_cntTaskOS5ms
                          , mai_cntTaskOS10ms
                          );
        assert((unsigned)noChar < sizeOfAry(msg));
        sio_osWriteSerial(msg, (unsigned)noChar);

        noChar = sniprintf( msg, sizeof(msg)
                          , "Cycles safety task: %lu\r\n"
                          , mai_cntTaskSafety1ms
                          );
        assert((unsigned)noChar < sizeOfAry(msg));
        sio_osWriteSerial(msg, (unsigned)noChar);

        noChar = sniprintf( msg, sizeof(msg)
                          , "Cycles of ISRs: %lu, %lu, %lu\r\n"
                          , mai_cntISRPit1
                          , mai_cntISRPit2
                          , mai_cntISRPit3
                          );
        assert((unsigned)noChar < sizeOfAry(msg));
        sio_osWriteSerial(msg, (unsigned)noChar);
    }
    else if(!rtos_isProcessSuspended(/* PID */ 1))
    {
        /* Transition to suspend state for process 1: Turn first LED off. */
        lbd_osSetLED(lbd_led_0_DS11, /* isOn */ false);
        rtos_osSuspendProcess(/* PID */ 1);

        noChar = sniprintf( msg, sizeof(msg)
                          , "Fatal error detected. Process 1 is suspended!\r\n"
                          );
        assert((unsigned)noChar < sizeOfAry(msg));
        sio_osWriteSerial(msg, (unsigned)noChar);
    }
    else
    {
        /* Failure: Let another LED blink. */
        lbd_osSetLED(lbd_led_7_DS4, /* isOn */ (mai_cntTaskIdle & 1) != 0);
    }
} /* End of taskOSIdle */



/**
 * This demonstration software uses a number of fast interrupts to produce system load and
 * prove stability. The interrupts are timer controlled (for simplicity) but the
 * activations are chosen as asynchronous to the operating system clock as possible to
 * provoke a most variable preemption pattern.
 */
static void osInstallInterruptServiceRoutines(void)
{
    _Static_assert(prioIrqPit1 >= 1  &&  prioIrqPit1 <= 15
                   &&  prioIrqPit2 >= 1  &&  prioIrqPit2 <= 15
                   &&  prioIrqPit3 >= 1  &&  prioIrqPit3 <= 15
                  , "Interrupt priority out of range"
                  );
    _Static_assert(prioIrqPit1 > RTOS_KERNEL_IRQ_PRIORITY_CORE_0
                   ||  prioIrqPit2 > RTOS_KERNEL_IRQ_PRIORITY_CORE_0
                   ||  prioIrqPit3 > RTOS_KERNEL_IRQ_PRIORITY_CORE_0
                  , "By intention, at least one interrupt should have a priority above the"
                    " scheduler of the RTOS"
                  );
    _Static_assert(prioIrqPit1 < RTOS_KERNEL_IRQ_PRIORITY_CORE_0
                   ||  prioIrqPit2 < RTOS_KERNEL_IRQ_PRIORITY_CORE_0
                   ||  prioIrqPit3 < RTOS_KERNEL_IRQ_PRIORITY_CORE_0
                  , "By intention, at least one interrupt should have a priority below the"
                    " scheduler of the RTOS"
                  );
    _Static_assert(prioIrqPit1 == RTOS_KERNEL_IRQ_PRIORITY_CORE_0
                   ||  prioIrqPit2 == RTOS_KERNEL_IRQ_PRIORITY_CORE_0
                   ||  prioIrqPit3 == RTOS_KERNEL_IRQ_PRIORITY_CORE_0
                  , "By intention, at least one interrupt should have the priority of the"
                    " scheduler of the RTOS"
                  );

    /* Disable timers during configuration. RM, 51.4.1, p. 2731.
         Disable all PIT timers during configuration. Note, this is a global setting for
       all sixteen timers. Accessing the bits makes this routine have race conditions with
       the RTOS initialization that uses timer #RTOS_CORE_0_IDX_OF_PID_TIMER. Both routines
       must not be called in concurrency. */
    PIT->MCR = PIT_MCR_MDIS(1) | PIT_MCR_FRZ(1);

    /* Install the ISRs now that all timers are stopped.
         Vector numbers: See MCU reference manual, section 28.7, table 28-4. */
    const unsigned int processorID = rtos_osGetIdxCore();
    rtos_osRegisterInterruptHandler( &isrPit1
                                   , processorID
                                   , /* vectorNum */ PIT_Ch1_IRQn
                                   , /* psrPriority */ prioIrqPit1
                                   , /* isPreemptable */ true
                                   );
    rtos_osRegisterInterruptHandler( &isrPit2
                                   , processorID
                                   , /* vectorNum */ PIT_Ch2_IRQn
                                   , /* psrPriority */ prioIrqPit2
                                   , /* isPreemptable */ true
                                   );
    rtos_osRegisterInterruptHandler( &isrPit3
                                   , processorID
                                   , /* vectorNum */ PIT_Ch3_IRQn
                                   , /* psrPriority */ prioIrqPit3
                                   , /* isPreemptable */ true
                                   );

    /* Peripheral clock has been initialized to 40 MHz. The timers count at this rate. To
       get a 1ms interrupt tick we need to count till 40000.
         The RTOS operates in ticks of 1ms. We use prime numbers to get good asynchronity
       with the RTOS clock.
         Note, one interrupt is much slower than the two others. The reason is it does much
       more, it takes part at the test of safely accessing data shared with the application
       tasks.
         -1: See RM, 51.6 */
    PIT->TIMER[1].LDVAL = 39989-1; /* Interrupt rate approx. 1 kHz */
    PIT->TIMER[2].LDVAL = 8009-1; /* Interrupt rate approx. 5 kHz */
    PIT->TIMER[3].LDVAL = 3989-1; /* Interrupt rate approx. 10 kHz */
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
 * C entry function main. Is used for and only for the Z7_0 core.
 *   @param noArgs
 * Number of arguments in \a argAry. Is actually always equal to one.
 *   @param argAry
 * Array of string arguments to the function. Actually, always a single string which equals
 * the name of the core, which is started.
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
         Caution: On the MPC5748G, this is not an option but an essential prerequisite for
       running safe-RTOS. The MPC5748G has a simplified z4 core without the timebase
       feature. The system timer is used as substitute. The driver needs to be started and
       it must be neither changed nor re-configured without carefully double-checking the
       side-effects on the kernel! */
    stm_osInitSystemTimers();
    
    /* Initialize the button and LED driver for the eval board. */
    lbd_osInitLEDAndButtonDriver( /* onButtonChangeCallback_core0 */ NULL
                                , /* PID_core0 */                    0
                                , /* onButtonChangeCallback_core1 */ NULL
                                , /* PID_core1 */                    0
                                , /* onButtonChangeCallback_core2 */ NULL
                                , /* PID_core2 */                    0   
                                , /* tiMaxTimeInUs */                1000
                                );

    /* Initialize the serial output channel as prerequisite of using printf. */
    sio_osInitSerialInterface(/* baudRate */ 115200);

    /* Register the process initialization tasks. */
    bool initOk = true;
    if(rtos_osRegisterInitTask(taskInitProcess, /* PID */ 1, /* tiTaskMaxInUS */ 1000)
       != rtos_err_noError
       ||  rtos_osRegisterInitTask(taskInitProcess, /* PID */ 2, /* tiTaskMaxInUS */ 1000)
           != rtos_err_noError
      )
    {
        initOk = false;
    }


#define CREATE_EVENT(name, tiCycleInMs)                                                     \
    if(initOk                                                                               \
       &&  rtos_osCreateEvent( &idEvent                                                     \
                             , /* tiCycleInMs */              tiCycleInMs                   \
                             , tiCycleInMs>0? tiFirstActivationInMs: 0                      \
                             , /* priority */                 prioEv##name                  \
                             , /* minPIDToTriggerThisEvent */                               \
                                                         RTOS_EVENT_NOT_USER_TRIGGERABLE    \
                             , /* taskParam */                0                             \
                             )                                                              \
           != rtos_err_noError                                                              \
      )                                                                                     \
    {                                                                                       \
        initOk = false;                                                                     \
    }                                                                                       \
    assert(idEvent == idEv##name);                                                          \
    if(tiCycleInMs > 0)                                                                     \
        ++ tiFirstActivationInMs;                                                           \
                                                                                            \
/* End of macro CREATE_EVENT */

    unsigned int tiFirstActivationInMs = 0
               , idEvent = 0;
    CREATE_EVENT(/* name */ 1msSafety, /* tiCycleInMs */ 1)
    CREATE_EVENT(/* name */ Pit2,      /* tiCycleInMs */ 0)
    CREATE_EVENT(/* name */ 1ms,       /* tiCycleInMs */ 1)
    CREATE_EVENT(/* name */ 5ms,       /* tiCycleInMs */ 5)
    CREATE_EVENT(/* name */ 10ms,      /* tiCycleInMs */ 10)
    CREATE_EVENT(/* name */ 100ms,     /* tiCycleInMs */ 100)
    CREATE_EVENT(/* name */ 1000ms,    /* tiCycleInMs */ 1000)

#undef CREATE_EVENT

#define CREATE_USER_TASK(name)                                                              \
    if( initOk                                                                              \
        &&  rtos_osRegisterUserTask( idEv##name                                             \
                                   , taskUser##name                                         \
                                   , pidTask##name                                          \
                                   , /* tiTaskMaxInUs */ 0                                  \
                                   )                                                        \
            != rtos_err_noError                                                             \
      )                                                                                     \
    {                                                                                       \
        initOk = false;                                                                     \
    }                                                                                       \
/* End of macro CREATE_USER_TASK */

    CREATE_USER_TASK(/* name */ Pit2)
    CREATE_USER_TASK(/* name */ 1ms)
    CREATE_USER_TASK(/* name */ 10ms)
    CREATE_USER_TASK(/* name */ 100ms)
    CREATE_USER_TASK(/* name */ 1000ms)

#undef CREATE_USER_TASK

#define CREATE_OS_TASK(name)                                                                \
    if( initOk                                                                              \
        &&  rtos_osRegisterOSTask(idEv##name, taskOS##name)                                 \
            != rtos_err_noError                                                             \
      )                                                                                     \
    {                                                                                       \
        initOk = false;                                                                     \
    }                                                                                       \
/* End of macro CREATE_OS_TASK */

    CREATE_OS_TASK(/* name */ 1ms)
    CREATE_OS_TASK(/* name */ 5ms)
    CREATE_OS_TASK(/* name */ 10ms)

#undef CREATE_OS_TASK

    /* Create the safety task. */
    if( initOk
        &&  rtos_osRegisterUserTask( idEv1msSafety
                                   , taskSafety1ms
                                   , pidTask1msSafety
                                   , /* tiTaskMaxInUs */ 0
                                   )
            != rtos_err_noError
      )
    {
        initOk = false;
    }

    /* The last check ensures that we didn't forget to register an event. */
    assert(initOk &&  idEvent == noRegisteredEvents-1);

    rtos_osGrantPermissionSuspendProcess( /* pidOfCallingTask */ 2 /* Supervisor */
                                        , /* targetPID */ 1        /* All user tasks */
                                        );

    /* Installing irrelated interrupts should be possible before the system is running.
       We place the PIT timer initialization here to prove this statement. Interrupt
       handling is generally disabled until the RTOS kernel starts up so there should be no
       activation losses or other harm. */
    osInstallInterruptServiceRoutines();
    del_delayMicroseconds(500000);

    /* Here we have an old unrecognized bug: If we put an arbitrary delay between interrupt
       source configuation and enabling of interrupt handling then we have am arbitrary
       phase delay of the source: We can be sure that the first interrupt is already
       pending and will be served immediately but we have no idea of how long it'll take
       until the source will raise the next interrupt - which matters in this sample: The
       interrupt handler isrPit2 triggers a user tasks and - by assertion - it demands
       success of the action. If the second interrupt follows the immediate first one soon
       then the second task activation will fail as the first triggered task has not
       completed yet.
         In this particular sample, we saw this happen depending on the compilation mode.
       The slower DEBUG failed, while the a bit faster PRODUCTION ran fine. 
         We can force correct startup by waiting for the next begin of counter cycle of the
       timer PIT2. Note, a cycle of the test loop must not execute longer than
       cntStillFarFromIrq, which is 20us in our case. */
    const uint32_t cntStillFarFromIrq = 9 * PIT->TIMER[2].LDVAL / 10;
    while(PIT->TIMER[2].CVAL < cntStillFarFromIrq)
        ;

    /* Initialize the RTOS kernel. The global interrupt processing is resumed if it
       succeeds. The step involves a configuration check. We must not startup the SW if the
       check fails. */
    if(!initOk ||  rtos_osInitKernel() != rtos_err_noError)
        while(true)
            ;

    /* Here we are in the idle task. */
    while(true)
        taskOSIdle();

} /* End of main */

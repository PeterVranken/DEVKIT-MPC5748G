/**
 * @file mai_main.c
 * The main entry point of the C code, which implements sample application "default" of the
 * RTOS. The code found here configures and runs the RTOS. Some tasks are registered that
 * implement blinking LEDs and more.\n
 *   A cyclic 1ms task controls one LED such that it blinks at 1 Hz. The task reads the
 * state of the buttons on the evaluation board. On button press an according event task,
 * taskOnButtonDown, is activated.\n
 *   The event task taskOnButtonDown reports each button event by printing a message to the
 * serial COM channel. At the same time it increments the amount of CPU load by 10% load,
 * which is (artificially) produced by task taskCpuLoad. This is a cyclic task with a busy
 * wait loop.\n
 *   A cyclic 1000ms task toggles the second LED at a rate of 0.5 Hz.\n
 *   An event task taskNonCyclic is activated by several other tasks under different
 * conditions. It can be observed that the activation sometime succeeds and sometime fails.
 * Below it's explained why.\n
 *   The regular 1s task is used to report the system state, CPU load, stack usage and task
 * overrun events (more precise: failed activations).\n
 *   The idle task measures the CPU load. Some artificial load is produced by taskCpuLoad;
 * this is about 26% plus n times 10%, where n is the number of button down events at
 * user button SW2.\n
 *   Three timer interrupts fire at high speed and on a time grid, which is asynchronous to
 * the normal application tasks. This leads to most variable preemption patterns. The
 * interrupts do nothing but producing system load and one of them participates the
 * software self-test (consistency check of shared data).
 *
 * The application should be run with a connected terminal. The terminal should be
 * configured for 115200 Bd, 8 Bits, no parity, 1 start and 1 stop bit.
 *
 * Some observations:\n
 *   Blinking LEDs: Note the slight phase shift due to the differing task start times.\n
 *   Reported CPU load: At nominal 100% artificial load the actual load drops to about 50%.
 * The execution time of the cyclic task that produces the load exceeds the nominal cycle
 * time of the task and every second activation is lost. The activation loss counter in the
 * RTOS' task array constantly increases.\n
 *   Occasional activation losses can be reported for task taskNonCyclic. It can be
 * preempted by task task17ms and this task activates task taskNonCyclic. If it tries to
 * do, while it has preempted task taskNonCyclic, the activation is not possible.\n
 *   The code runs a permanent test of the offered mechanism for mutual exclusion of tasks
 * that access some shared data objects. A recognized failure is reported by assertion,
 * which will halt the code execution (in DEBUG compilation only). Everything is fine as
 * long as the LEDs continue blinking.
 *
 * CAUTION: This safe-RTOS application only is a migration of the demo software from the
 * ancestor implementation of the RTOS, which didn't have the safety mechanisms. The
 * migrated application doesn't aim at demonstrating the design of a true safe application.
 * The major issue is that there's no clear visual separation of code belonging in the
 * spheres of a) an operating system, b) the functional application code and c) some
 * supervisory safety code.
 *
 * Copyright (C) 2017-2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   checkAndIncrementTaskCnts
 *   testPCP_checkDataConsistency
 *   testPCP
 *   isrPit1
 *   isrPit2
 *   isrPit3
 *   taskOs1ms
 *   onButtonChangeCallback
 *   task1ms
 *   task3ms
 *   task1s
 *   taskNonCyclic
 *   task17ms
 *   taskOnButtonDown
 *   taskCpuLoad
 *   osInstallInterruptServiceRoutines
 *   taskInitProcess
 *   taskIdlePID2
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
#include <float.h>
#include <limits.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "ccl_configureClocks.h"
#include "xbs_crossbarSwitch.h"

#include "lbd_ledAndButtonDriver.h"
#include "dma_dmaDriver.h"
#include "sio_serialIO.h"
#include "rtos.h"
#include "del_delay.h"
#include "gsl_systemLoad.h"
#include "stm_systemTimer.h"
#include "tcx_testContext.h"
#include "mai_main.h"


/*
 * Defines
 */

/** The demo can be compiled with a ground load. Most tasks produce some CPU load if this
    switch is set to 1. */
#define TASKS_PRODUCE_GROUND_LOAD   0

/** A wrapper around the API for the priority ceiling protocal (PCP), which lets the API
    for mutual exclusion of a task set look like the API calls from the OSEK/VDX standard.
      Here, for getting the resource, i.e. for entering a critical section of code. */
#define GetResource(idTask, resource)                                                       \
            {   uint32_t priorityLevelSoFar;                                                \
                if((idTask) <= lastUserTaskId)                                              \
                {                                                                           \
                    priorityLevelSoFar = rtos_suspendAllTasksByPriority                     \
                                                (/* suspendUpToThisPriority */ (resource)); \
                }                                                                           \
                else                                                                        \
                {                                                                           \
                    assert((idTask) < noRegisteredTasks ||  (idTask) == idTaskIdle);        \
                    priorityLevelSoFar = rtos_osSuspendAllTasksByPriority              \
                                                (/* suspendUpToThisPriority */ (resource)); \
                }

/** A wrapper around the API for the priority ceiling protocal (PCP), which lets the API
    for mutual exclusion of a task set look like the API calls from the OSEK/VDX standard.
      Here, for returning the resource, i.e. for leaving a critical section of code. */
#define ReleaseResource(idTask)                                                             \
                if((idTask) <= lastUserTaskId)                                              \
                    rtos_resumeAllTasksByPriority(priorityLevelSoFar);                      \
                else                                                                        \
                {                                                                           \
                    assert((idTask) < noRegisteredTasks ||  (idTask) == idTaskIdle);        \
                    rtos_osResumeAllTasksByPriority(priorityLevelSoFar);               \
                }                                                                           \
            }

/** The task counter array is accessed by all tasks. Here it is modelled as an OSEK/VDX
    like resource to be used with #GetResource and #ReleaseResource. */
#define RESOURCE_CNT_TASK_ARY   (RESOURCE_ALL_TASKS)

/** The priority level to set if all tasks should be mutually excluded from accessing a
    shared resource. The macro is named such that the code resembles the resource API from
    the OSEK/VDX standard. */
#define RESOURCE_ALL_TASKS  (MAXP(prioTask1ms,MAXP(prioTask3ms, \
                             MAXP(prioTask1s,MAXP(prioTaskNonCyclic, \
                             MAXP(prioTask17ms,MAXP(prioTaskOnButtonDown, \
                             prioTaskCpuLoad)))))))

/** The priority level to set for the atomic operations done in function testPCP(). The
    macro is named such that the code resembles the resource API from the OSEK/VDX
    standard. */
#define RESOURCE_TEST_PCP  (MAXP(prioTask1ms,MAXP(prioTaskCpuLoad,prioTaskIdle)))

/** Some helper code to get the maximum task priority as a constant for the priority ceiling
    protocol. */
#define MAXP(p1,p2)  ((p2)>(p1)?(p2):(p1))


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
      Here, we have the IDs of the created events. They occupy the index range starting
    from zero. */
enum
{
    /** The ID of the created events. They occupy the index range starting from zero. */
    idEv1ms = 0
    , idEv3ms
    , idEv1s
    , idEvNonCyclic
    , idEv17ms
    , idEvOnButtonDown
    , idEvCpuLoad

    /** In this sample, we have a one by one relation between events and tasks for most
        tasks. We duplicate the event IDs to have task IDs, too. This is a remnant from the
        elder RTOS, where we had a strict one-by-one relation between events and tasks. */
    , idTask1ms          = idEv1ms
    , idTask3ms          = idEv3ms
    , idTask1s           = idEv1s
    , idTaskNonCyclic    = idEvNonCyclic
    , idTask17ms         = idEv17ms
    , idTaskOnButtonDown = idEvOnButtonDown
    , idTaskCpuLoad      = idEvCpuLoad

    /** Some derived enumeration values permit making the distinction between user and OS
        tasks by ID. */
    , tmpIdTask1
    , lastUserTaskId = tmpIdTask1 - 1
    , firstOsTaskId
    , tmpIdTask2 = firstOsTaskId - 1

    , idTaskOs1ms

    /** The number of tasks to register. */
    , noRegisteredTasks

    /** The idle task is not a task under control of the RTOS and it doesn't have an ID.
        We assign it a pseudo task ID that is used to store some task related data in the
        same array here in this sample application as we do by true task ID for all true
        tasks. */
    , idTaskIdle = noRegisteredTasks
};


/** The RTOS uses constant priorities for its events, which are defined here.\n
      Note, the priority is a property of an event rather than of a task. A task implicitly
    inherits the priority of the event it is associated with. */
enum
{
    prioTask1ms = 2
    , prioTask3ms = 2
    , prioTask1s = 1
    , prioTaskNonCyclic = 3
    , prioTask17ms = 4
    , prioTaskOnButtonDown = 1
    , prioTaskCpuLoad = 1

    , prioTaskOs1ms = prioTask1ms /* same event, cannot have other prio */
    , prioTaskIdle = 0      /** Prio 0 is implicit for idle, cannot be chosen explicitly */

    , prioIrqPit1 = 5       /** INTC priority of timer IRQ PIT1 */
    , prioIrqPit2 = 6       /** INTC priority of timer IRQ PIT2 */
    , prioIrqPit3 = 15      /** INTC priority of timer IRQ PIT3 */
};


/** In safe-RTOS a task belongs to a process, characterized by the PID, 1..4. The
    relationship is defined here.\n
      Note, a process needs to be configured in the linker script (actually: assignment of
    stack space) before it can be used. */
enum
{
    pidTask1ms = 1
    , pidTask3ms = 1
    , pidTask1s = 1
    , pidTaskNonCyclic = 1
    , pidTask17ms = 1
    , pidTaskOnButtonDown = 1
    , pidTaskCpuLoad = 1
    , pidTaskOs1ms = 0  /* A kernel or operating system task, e.g. to implement a polling
                           I/O driver. */
    , pidOnButtonChangeCallback = 1
    , pidTaskIdle = 0   /* PID 0 is implicit, idle belongs to kernel, kernel always is PID 0 */
};


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** A task invokation counter, which is incremented by all application tasks. */
volatile unsigned long long SHARED(_cntAllTasks) = 0;

/** A cycle counter for each task. The last entry is meant for the idle task. */
volatile unsigned long long SHARED(_cntTaskAry)[noRegisteredTasks+1] =
                                                        {[0 ... noRegisteredTasks] = 0};

volatile unsigned long mai_cntTaskIdle SECTION(.bss.OS) = 0  /** Counter of cycles of
                                                                 infinite main loop. */ 
                     , mai_cntTask1ms SECTION(.bss.P1) = 0   /** Counter of cyclic task. */
                     , mai_cntTask3ms SECTION(.bss.P1) = 0   /** Counter of cyclic task. */
                     , mai_cntTask1s SECTION(.bss.P1) = 0    /** Counter of cyclic task. */
                     , mai_cntTaskNonCyclic SECTION(.bss.P1) = 0 /** Counter of calls of
                                                                     software triggered task */
                     , mai_cntTask17ms SECTION(.bss.P1) = 0  /** Counter of cyclic task. */
                     , mai_cntTaskOnButtonDown SECTION(.bss.P1) = 0 /** Counter of button
                                                                        event task. */
                     , mai_cntTaskCpuLoad SECTION(.bss.P1) = 0   /** Counter of cyclic task. */
                     , mai_cntActivationLossTaskNonCyclic SECTION(.bss.P1) = 0 /** Lost 
                                                                                   activations
                                                                                   of non
                                                                                   cyclic
                                                                                   task. */
                     , mai_cntISRPit1 SECTION(.bss.OS) = 0
                     , mai_cntISRPit2 SECTION(.bss.OS) = 0
                     , mai_cntISRPit3 SECTION(.bss.OS) = 0;

/** We have an idle task in process 2. */
volatile unsigned int mai_cntTaskIdlePID2 SECTION(.sdata.P2) = 0;

/** The color currently used by the interrupt handlers are controlled through selection of
    a pin. The selection is made by global variable. Here for D5. */
static volatile lbd_led_t _ledTask1s SECTION(.sdata.P1) = lbd_led_0_DS11;

/** The color currently used by the interrupt handlers are controlled through selection of
    a pin. The selection is made by global variable. Here for D4. */
static volatile lbd_led_t _ledTask1ms SECTION(.sdata.P1) = lbd_led_7_DS4;

/** The average CPU load produced by all tasks and interrupts in tens of percent. */
unsigned int mai_cpuLoad SECTION(.data.OS) = 1000;

/** Test of CPU load estimation: This variable controls the production of some artificial
    CPU load. This is done in a task of low priority so that all higher prioritized task
    should not or barely be affected. (One LED is, the other isn't affected.) */
static unsigned int _cpuLoadInPercent SECTION(.sdata.P1) = 0;

/** Test of priority ceiling protocol. A sub-set of tasks, whereof non of highest priority
    in use, share this data object. It has redundant fields so that a sharing conflict can
    be recognized. Try compiling the code with bad resource definition and see if the
    problem is reported (in DEBUG compilation by assertion, too). */
static volatile struct sharedDataTasksIdleAnd1msAndCpuLoad_t
{
    /** Counter incremented on execution of task task1ms. */
    unsigned int cntTask1ms;

    /** Counter incremented on execution of task taskCpuLoad. */
    unsigned int cntTaskCpuLoad;

    /** Counter incremented on execution of the idle task. */
    unsigned int cntTaskIdle;

    /** Total count, sum of all others. */
    unsigned int cntTotal;

    /** The number of recognized data consistency errors. */
    unsigned int noErrors;

} _sharedDataTasksIdleAnd1msAndCpuLoad SECTION(.shared._sharedDataTasksIdleAnd1msAndCpuLoad) =
    { .cntTask1ms = 0
    , .cntTaskCpuLoad = 0
    , .cntTaskIdle = 0
    , .cntTotal = 0
    , .noErrors = 0
    };


/*
 * Function implementation
 */

/**
 * Test function, to be called from any of the tasks: A task related counter is incremented
 * and in the same atomic operation is a task-shared counter incremented. The function then
 * validates that the sum of all task related counters is identical to the value of the
 * shared counter. The test result is validated by assertion, i.e. the application is
 * halted in case of an error.
 *   The test is aimed to prove the correct implementation of the offered mutual exclusion
 * mechanisms.
 *   @param idTask
 * The ID (or index) of the calling task. Needed to identify the task related counter.
 */
static void checkAndIncrementTaskCnts(unsigned int idTask)
{
    /* Increment task related counter and shared counter in an atomic operation. */
    GetResource(idTask, RESOURCE_CNT_TASK_ARY);
    {
        assert(idTask < sizeOfAry(_cntTaskAry));
        ++ _cntTaskAry[idTask];
        ++ _cntAllTasks;
    }
    ReleaseResource(idTask);

    /* Get all task counters and the common counter in an atomic operation. */
    unsigned long long cntTaskAryCpy[noRegisteredTasks+1]
                     , cntAllTasksCpy;
    _Static_assert(sizeof(_cntTaskAry) == sizeof(cntTaskAryCpy), "Bad data definition");
    GetResource(idTask, RESOURCE_CNT_TASK_ARY);
    {
        memcpy(&cntTaskAryCpy[0], (void*)&_cntTaskAry[0], sizeof(cntTaskAryCpy));
        cntAllTasksCpy = _cntAllTasks;
    }
    ReleaseResource(idTask);

    /* Check consistency of got data. */
    unsigned int u;
    for(u=0; u<sizeOfAry(cntTaskAryCpy); ++u)
        cntAllTasksCpy -= cntTaskAryCpy[u];
    if(cntAllTasksCpy != 0)
    {
#ifdef DEBUG
        assert(false);
#else
        /* PRODUCTION compilation: Code execution can be halted only by the OS process. We
           leave this to the idle task.
             Note, incrementing the error count to make the idle task recognize the problem
           is not safe, we don't have a critical section for this object and the given
           task. */
        ++ _sharedDataTasksIdleAnd1msAndCpuLoad.noErrors;
#endif
    }
} /* End of checkAndIncrementTaskCnts. */



/**
 * Helper function of PCP test: The shared data is checked for consistency and a global
 * error counter is incremented in case.
 *   @return
 * Get \a true as long as everything is alright.
 */
static bool testPCP_checkDataConsistency()
{
    const unsigned int sum = _sharedDataTasksIdleAnd1msAndCpuLoad.cntTaskIdle
                             + _sharedDataTasksIdleAnd1msAndCpuLoad.cntTaskCpuLoad
                             + _sharedDataTasksIdleAnd1msAndCpuLoad.cntTask1ms;
    if(sum != _sharedDataTasksIdleAnd1msAndCpuLoad.cntTotal)
    {
        /* Resynchronize to enable further error recognition. */
        _sharedDataTasksIdleAnd1msAndCpuLoad.cntTotal = sum;

        const unsigned int noErr = _sharedDataTasksIdleAnd1msAndCpuLoad.noErrors+1;
        if(noErr > 0)
            _sharedDataTasksIdleAnd1msAndCpuLoad.noErrors = noErr;

        return false;
    }
    else
        return true;

} /* End of testPCP_checkDataConsistency */



/**
 * Test function for priority ceiling portocol. To be called from a sub-set of tasks, idle
 * task, task1ms and taskCpuLoad.
 *   The test is aimed to prove the correct implementation of the offered mutual exclusion
 * mechanism for this sub-set of tasks.
 *   @param idTask
 * The ID (or index) of the calling task. Needed to identify the task related counter.
 */
static void testPCP(unsigned int idTask)
{
    /* Increment task related counter and shared counter in an atomic operation. */
    if(idTask == idTaskIdle)
    {
        GetResource(idTaskIdle, RESOURCE_TEST_PCP);
        {
            ++ _sharedDataTasksIdleAnd1msAndCpuLoad.cntTaskIdle;
            ++ _sharedDataTasksIdleAnd1msAndCpuLoad.cntTotal;
        }
        ReleaseResource(idTaskIdle);
    }
    else if(idTask == idTaskCpuLoad)
    {
        GetResource(idTaskCpuLoad, RESOURCE_TEST_PCP);
        {
            ++ _sharedDataTasksIdleAnd1msAndCpuLoad.cntTaskCpuLoad;
            ++ _sharedDataTasksIdleAnd1msAndCpuLoad.cntTotal;
        }
        ReleaseResource(idTaskCpuLoad);
    }
    else if(idTask == idTask1ms)
    {
        /* Here, we want to prove that the resource doesn't need to be acquired by a task,
           which has the highest priority in the sub-set.
             Omitting the critical section code invalidates the code if the task priorities
           are redefined in the heading part of the file and we need to put an assertion to
           double check this. */
        _Static_assert( prioTask1ms >= prioTaskIdle  &&  prioTask1ms >= prioTaskCpuLoad
                      , "Task priorities do not meet the requirements of function testPCP"
                      );
        ++ _sharedDataTasksIdleAnd1msAndCpuLoad.cntTask1ms;
        ++ _sharedDataTasksIdleAnd1msAndCpuLoad.cntTotal;
    }
    else
    {
        /* This function is intended only for a sub-set of tasks. */
#ifdef DEBUG
        assert(false);
# else
        /* PRODUCTION compilation: Code execution can be halted only by the OS process. We
           leave this to the idle task.
             Note, incrementing the error count to make the idle task recognize the problem
           is not safe, we don't have a critical section for the given task. */
        ++ _sharedDataTasksIdleAnd1msAndCpuLoad.noErrors;
#endif
    }

    /* Validate the consistency of the redundant data in an atomic operation. */
    bool bOkay;
    GetResource(idTask, RESOURCE_TEST_PCP);
    {
        bOkay = testPCP_checkDataConsistency();
    }
    ReleaseResource(idTask);

#ifdef DEBUG
    assert(bOkay);
#else
    /* PRODUCTION compilation: Code execution can be halted only by the OS process. Not
       all of the errors will become visible by LED. */
    if(idTask >= firstOsTaskId  &&  !bOkay)
        rtos_osSuspendProcess(/* PID */ 1);
#endif
} /* End of testPCP. */



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
#if 0
    /* The ancestor revision of the RTOS, which was based on the hardware scheduler in the
       INTC, had been able to offer critical sections between ISRs and user tasks. The
       software scheduler introduced in this branch strictly separates ISRs from tasks and
       doesn't offer an API to user mode code to shape a critical section. We can't
       integrate this ISR into the consistency check any more. */
    checkAndIncrementTaskCnts(idISRPit1);
#endif
       
    ++ mai_cntISRPit1;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. */
    PIT->TIMER[1].TFLG = PIT_TFLG_TIF(1);

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

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. */
    PIT->TIMER[2].TFLG = PIT_TFLG_TIF(1);

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

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. */
    PIT->TIMER[3].TFLG = PIT_TFLG_TIF(1);

} /* End of isrPit3 */



/**
 * OS task function, cyclically activated every Millisecond. Used to clock the step
 * functions of our I/O drivers.\n
 *   This task is run in supervisor mode and it has no protection. The implementation
 * belongs into the sphere of trusted code.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static void taskOs1ms(uintptr_t taskParam ATTRIB_UNUSED)
{
    /* The I/O driver for the buttons is run from the OS task with priority
       prioTaskOs1ms = 2. The driver code and the callback onButtonChangeCallback it may
       invoke inherit this priority. */
    lbd_osTask1ms();

} /* End of taskOs1ms */


/**
 * Notification callback from the button and LED I/O driver (lbd) in case of a button state
 * change.\n
 *   Note, the button driver is run in the context of task taskOs1ms. Driver and this
 * callback inherit the priority of that task, which is prioTaskOs1ms = 2.
 *   @param PID
 * A user task or callback gets the process ID as first argument.
 *   @param buttonState
 * The new, changed button state. See lbd_onButtonChangeCallback_t for details.
 */
static int32_t onButtonChangeCallback(uint32_t PID ATTRIB_UNUSED, uint8_t buttonState)
{
    /* Toggle the LED colors on button SW3 down. */
    if((buttonState & lbd_btStMask_btnSw2_down) != 0)
    {
        static unsigned int cntButtonPress_ SECTION(.sbss.P1) = 0;

        lbd_setLED(_ledTask1s, /* isOn */ false);
        lbd_setLED(_ledTask1ms, /* isOn */ false);
        _ledTask1s  = (cntButtonPress_ & 0x1) != 0? lbd_led_3_DS8: lbd_led_0_DS11;
        _ledTask1ms = (cntButtonPress_ & 0x2) != 0? lbd_led_7_DS4: lbd_led_4_DS7;

        /* Activate the non cyclic task a second time. The priority of the activated
           task (3) is higher than of this activating callback (2) so any earlier
           activation should have been processed meanwhile and this one should be accepted,
           too. */ 
#ifdef DEBUG
        bool bActivationAccepted =
#endif
        rtos_triggerEvent(idEvNonCyclic, /* taskParam */ 0);
        assert(bActivationAccepted);

        /* Activate our button down event task. The activation will normally succeed
           but at high load and very fast button press events it is theoretically
           possible that not. We don't place an assertion. */
#ifdef DEBUG
        bActivationAccepted =
#endif
        rtos_triggerEvent(idEvOnButtonDown, /* taskParam */ 0);
        //assert(bActivationAccepted);

        ++ cntButtonPress_;
    }

    return 0;

} /* End of onButtonChangeCallback */



/**
 * Task function, cyclically activated every Millisecond. The LED D4 is switched on and off
 * and the button SW3 is read and evaluated.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t task1ms(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    checkAndIncrementTaskCnts(idTask1ms);
    testPCP(idTask1ms);

    ++ mai_cntTask1ms;

    /* Activate the non cyclic task.
         Note, the non cyclic task is of higher priority than this task and it'll be
       executed immediately, preempting this task. The second activation below, on button
       down must not lead to an activation loss. */
    rtos_triggerEvent(idEvNonCyclic, /* taskParam */ 0);

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 50 /* approx. 5% load */);
#endif

    static int cntIsOn_ SECTION(.sbss.P1) = 0;
    if(++cntIsOn_ >= 500)
        cntIsOn_ = -500;
    lbd_setLED(_ledTask1ms, /* isOn */ cntIsOn_ >= 0);

    return 0;

} /* End of task1ms */




/**
 * Task function, cyclically activated every 3ms.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t task3ms(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    checkAndIncrementTaskCnts(idTask3ms);
    ++ mai_cntTask3ms;

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 150 /* approx. 5% load */);
#endif

    return 0;

} /* End of task3ms */



/**
 * Task function, cyclically activated every second.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t task1s(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    checkAndIncrementTaskCnts(idTask1s);

    ++ mai_cntTask1s;

    static int cntIsOn_ SECTION(.sbss.P1) = 0;
    if(++cntIsOn_ >= 1)
        cntIsOn_ = -1;
    lbd_setLED(_ledTask1s, /* isOn */ cntIsOn_ >= 0);

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software.
         Note, the cyclic task taskCpuLoad has a period time of 23 ms and it has the same
       priority as this task. Because of the busy loop here and because the faster task
       itself has a non negligible execution time, there's a significant chance of loosing
       an activation of the faster task once a second. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 20000 /* approx. 2% load */);
#endif

    /* Simple code: First calculation of time to print is wrong. */
    static unsigned long tiPrintf_ SECTION(.sbss.P1) = 0;
    unsigned long tiFrom = stm_getSystemTime(/* idxTimer */ 0);
    iprintf( "CPU load is %u.%u%%. Stack reserve:\r\n"
             "  OS: %u Byte\r\n"
             "  PID 1: %u Byte\r\n"
             "  PID 2: %u Byte\r\n"
             "  PID 3: %u Byte\r\n"
             "  PID 4: %u Byte\r\n"
             "Task activations (lost):\r\n"
             "  task1ms: %lu (%u)\r\n"
             "  task3ms: %lu (%u)\r\n"
             "  task1s: %lu (%u)\r\n"
             "  taskNonCyclic: %lu (%u)\r\n"
             "  task17ms: %lu (%u)\r\n"
             "  taskOnButtonDown: %lu (%u)\r\n"
             "  taskCpuLoad: %lu (%u)\r\n"
             "  taskIdle: %lu\r\n"
             "  taskIdle PID 2: %u\r\n"
             "Process errors:\r\n"
             "  Total PID 1: %u\r\n"
             "  thereof Deadline missed: %u\r\n"
             "  Total PID 2: %u\r\n"
             "  thereof Deadline missed: %u\r\n"
             "tiPrintf = %luus\r\n"
           , mai_cpuLoad/10, mai_cpuLoad%10
           , rtos_getStackReserve(/* PID */ 0)
           , rtos_getStackReserve(/* PID */ 1)
           , rtos_getStackReserve(/* PID */ 2)
           , rtos_getStackReserve(/* PID */ 3)
           , rtos_getStackReserve(/* PID */ 4)
           , mai_cntTask1ms, rtos_getNoActivationLoss(idEv1ms)
           , mai_cntTask3ms, rtos_getNoActivationLoss(idEv3ms)
           , mai_cntTask1s, rtos_getNoActivationLoss(idEv1s)
           , mai_cntTaskNonCyclic, rtos_getNoActivationLoss(idEvNonCyclic)
           , mai_cntTask17ms, rtos_getNoActivationLoss(idEv17ms)
           , mai_cntTaskOnButtonDown, rtos_getNoActivationLoss(idEvOnButtonDown)
           , mai_cntTaskCpuLoad, rtos_getNoActivationLoss(idEvCpuLoad)
           , mai_cntTaskIdle
           , mai_cntTaskIdlePID2
           , rtos_getNoTotalTaskFailure(/* PID */ 1)
           , rtos_getNoTaskFailure(/* PID */ 1, RTOS_ERR_PRC_DEADLINE)
           , rtos_getNoTotalTaskFailure(/* PID */ 2)
           , rtos_getNoTaskFailure(/* PID */ 2, RTOS_ERR_PRC_DEADLINE)
           , tiPrintf_
           );
#if STM_TIMER_0_CLK % 1000000u != 0
# error Implementation not suitable for given timer configuration
#endif
    tiPrintf_ = (stm_getSystemTime(/* idxTimer */ 0) - tiFrom
                 + (STM_TIMER_0_CLK/1000000u/2u)
                ) / (STM_TIMER_0_CLK/1000000u);

    return 0;

} /* End of task1s */



/**
 * A non cyclic task, which is solely activated by software triggers from other tasks.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t taskNonCyclic(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    checkAndIncrementTaskCnts(idTaskNonCyclic);
    ++ mai_cntTaskNonCyclic;

    return 0;

} /* End of taskNonCyclic */



/**
 * Task function, cyclically activated every 17ms.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t task17ms(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    checkAndIncrementTaskCnts(idTask17ms);
    ++ mai_cntTask17ms;

    /* This task has a higher priority than the software triggered, non cyclic task. Since
       the latter one is often active we have a significant likelihood of a failing
       activation from here -- always if we preempted the non cyclic task. */
    if(!rtos_triggerEvent(idEvNonCyclic, /* taskParam */ 0))
        ++ mai_cntActivationLossTaskNonCyclic;

#if TASKS_PRODUCE_GROUND_LOAD == 1
    /* Produce a bit of CPU load. This call simulates some true application software. */
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ 17*40 /* approx. 4% load */);
#endif

    /* A task can't activate itself, we do not queue activations and it's obviously active
       at the moment. Test it. */
#ifdef DEBUG
    bool bActivationAccepted =
#endif
    rtos_triggerEvent(idEv17ms, /* taskParam */ 0);
    assert(!bActivationAccepted);

    return 0;

} /* End of task17ms */



/**
 * A non cyclic task, which is activated by software trigger every time the button on the
 * evaluation board is pressed.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t taskOnButtonDown(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    checkAndIncrementTaskCnts(idTaskOnButtonDown);
    ++ mai_cntTaskOnButtonDown;
    iprintf("You pressed the button the %lu. time\r\n", mai_cntTaskOnButtonDown);

    /* Change the value of artificial CPU load on every click by 10%. */
    if(_cpuLoadInPercent < 100)
        _cpuLoadInPercent += 10;
    else
        _cpuLoadInPercent = 0;

    iprintf("The additional, artificial CPU load has been set to %u%%\r\n", _cpuLoadInPercent);
#ifdef __VLE__
    /* This code is a work around for a bug in MinGW-powerpc-eabivle-4.9.4. If the code is
       compiled with optimization and for VLE instructions and if the iprintf (likely the
       same for all kinds of printf) is the very last operation of the C function, then the
       compiler emits a Book E instruction instead of the VLE equivalent. The execution goes
       into a trap. See https://community.nxp.com/message/966809 for details.
         Note, this is likely due to a specific optimizer decision, which is really related
       to the conditions "printf" and "last statement" but not a common error, which could
       unpredictedly appear anywhere else. */
    asm volatile ("se_nop\n\t");
#endif

    return 0;

} /* End of taskOnButtonDown */


/**
 * A cyclic task of low priority, which is used to produce some artificial CPU load.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 *   @remark
 * We need to consider that in this sample, the measurement is inaccurate because the
 * idle loop is not empty (besides measuring the load) and so the observation window is
 * discontinuous. The task has a cycle time of much less than the CPU measurement
 * observation window, which compensates for the effect of the discontinuous observation
 * window.
 */
static int32_t taskCpuLoad(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    checkAndIncrementTaskCnts(idTaskCpuLoad);
    testPCP(idTaskCpuLoad);

    /* The next call produces 100 * noCycles*(waitTimePerCycleInUS/1000) / 23 percent of
       CPU load. */
    tcx_testContext(/* noCycles */ 3, /* waitTimePerCycleInUS */ 2000);

    ++ mai_cntTaskCpuLoad;

    /* Producing load is implemented as producing full load for a given span of world time.
       This is not the same as producing an additional load of according percentage to the
       system since the task may be preempted and time elapses while this task is not
       loading the CPU. The percent value is only approximately. */
    const unsigned int tiDelayInUs = 23 /* ms = cycle time of this task */
                                     * 1000 /* ms to us to improve resolution */
                                     * _cpuLoadInPercent
                                     / 100;
    del_delayMicroseconds(/* fullLoadThisNoMicroseconds */ tiDelayInUs);

    return 0;

} /* End of taskCpuLoad */



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
         -1: See RM, 51.6 */
    PIT->TIMER[1].LDVAL = 4001-1; /* Interrupt rate approx. 10kHz */
    PIT->TIMER[2].LDVAL = 1361-1; /* Interrupt rate approx. 30kHz */
    PIT->TIMER[3].LDVAL = 1327-1; /* Interrupt rate approx. 30kHz */

    /* Clear possibly pending interrupt flags. */
    PIT->TIMER[1].TFLG = PIT_TFLG_TIF(1);
    PIT->TIMER[2].TFLG = PIT_TFLG_TIF(1);
    PIT->TIMER[3].TFLG = PIT_TFLG_TIF(1);
    
    /* Enable interrupts by the timers and start them. See RM 51.4.10. */
    PIT->TIMER[1].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    PIT->TIMER[2].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    PIT->TIMER[3].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);

    /* Enable timer operation. This operation affects all timer channels.
         PIT_MCR_FRZ: For this multi-core MCU it is not so easy to decide whether or not to
       let the timers be stopped on debugger entry: Any stopped core will halt the timers,
       regardless whether that core is related to the timer or not (and how should the
       debugger know...). Both possibilities can be annoying or advantageous, depending on
       the situation. */
    PIT->MCR = PIT_MCR_MDIS(0) | PIT_MCR_FRZ(1);
    
} /* End of osInstallInterruptServiceRoutines */



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
 * function implementation. This is meant a demonstration of the technical feasibility
 * but not of good practice; the implementation needs to use shared memory, which may break
 * a safety constraint, and it needs to consider the different privileges of the processes.
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
 * A short function, which is regularly called from the idle OS process but whic is run in
 * user process context 2.
 *   @return
 * The function returns 3 times \a taskParam (a meaningless test only).
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @param taskParam
 * Task parameter.
 */
static int32_t taskIdlePID2(uint32_t PID, uint32_t taskParam)
{
    static unsigned int cnt_ SECTION(.sdata.P2) = 0;
    ++ cnt_;
    mai_cntTaskIdlePID2 = cnt_;

    volatile static unsigned int u_ SECTION(.data.P2) = 0;
    for(u_=0; u_<1000; ++u_)
        ;

    return (signed int)(taskParam*PID + taskParam);

} /* taskIdlePID2 */


/**
 * Entry point into C code. The C main function is entered without arguments and despite of
 * its return code definition it must never be left. (Returning from main would enter an
 * infinite loop in the calling assembler startup code.)
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
    
    /* The interrupt controller is configured. This is the first driver initialization
       call: Many of the others will register their individual ISRs and this must not be
       done prior to initialization of the interrupt controller. */
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

    /* Start the system timers STM for execution time measurement.
         Caution: On the MPC5748G, this is not an option but an essential prerequisite for
       running safe-RTOS. The MPC5748G has a simplified z4 core without the timebase
       feature. The system timer is used as substitute. The driver needs to be started and
       it must be neither changed nor re-configured without carefully double-checking the
       side-effects on the kernel! */
    stm_osInitSystemTimers();
    
    /* Initialize the DMA driver. This driver needs to be initialized prior to any other
       I/O driver, which makes use of a DMA channel. */
    dma_osInitDMADriver();
    
    /* Initialize the button and LED driver for the eval board. */
    lbd_osInitLEDAndButtonDriver( /* onButtonChangeCallback_core0 */ onButtonChangeCallback
                                , /* PID_core0 */                    pidOnButtonChangeCallback
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
      )
    {
        initOk = false;
    }
    if(rtos_osRegisterInitTask(taskInitProcess, /* PID */ 2, /* tiTaskMaxInUS */ 1000)
       != rtos_err_noError
      )
    {
        initOk = false;
    }
    
    /* Create the events that trigger application tasks at the RTOS. Note, we do not really
       respect the ID, which is assigned to the event by the RTOS API rtos_osCreateEvent().
       The returned value is redundant. This technique requires that we create the events
       in the right order and this requires in practice a double-check by assertion - later
       maintenance errors are unavoidable otherwise. */
    unsigned int idEvent;
    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              1
                         , /* tiFirstActivationInMs */    10
                         , /* priority */                 prioTask1ms
                         , /* minPIDToTriggerThisEvent */ 1
                         , /* taskParam */                0
                         )
       == rtos_err_noError
      )
    {
        assert(idEvent == idEv1ms);

        if(rtos_osRegisterOSTask(idEv1ms, taskOs1ms) != rtos_err_noError)
            initOk = false;

        if(rtos_osRegisterUserTask( idEv1ms
                                  , task1ms
                                  , pidTask1ms
                                  , /* tiTaskMaxInUs */ 0
                                  )
           != rtos_err_noError
          )
        {
            initOk = false;
        }
    }
    else
        initOk = false;
        
    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              3
                         , /* tiFirstActivationInMs */    17
                         , /* priority */                 prioTask3ms
                         , /* minPIDToTriggerThisEvent */ 1
                         , /* taskParam */                0
                         )
       == rtos_err_noError
      )
    {
        assert(idEvent == idEv3ms);
        if(rtos_osRegisterUserTask( idEv3ms
                                  , task3ms
                                  , pidTask3ms
                                  , /* tiTaskMaxInUs */ 0
                                  )
           != rtos_err_noError
          )
        {
            initOk = false;
        }
    }
    else
        initOk = false;
    
    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              1000
                         , /* tiFirstActivationInMs */    100
                         , /* priority */                 prioTask1s
                         , /* minPIDToTriggerThisEvent */ 1
                         , /* taskParam */                0
                         )
       == rtos_err_noError
      )
    {
        assert(idEvent == idEv1s);
        if(rtos_osRegisterUserTask( idEv1s
                                  , task1s
                                  , pidTask1s
                                  , /* tiTaskMaxInUs */ 0
                                  )
           != rtos_err_noError
          )
        {
            initOk = false;
        }
    }
    else
        initOk = false;
    
    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              0 /* non-cyclic */
                         , /* tiFirstActivationInMs */    0
                         , /* priority */                 prioTaskNonCyclic
                         , /* minPIDToTriggerThisEvent */ 1
                         , /* taskParam */                0
                         )
       == rtos_err_noError
      )
    {
        assert(idEvent == idEvNonCyclic);
        if(rtos_osRegisterUserTask( idEvNonCyclic
                                  , taskNonCyclic
                                  , pidTaskNonCyclic
                                  , /* tiTaskMaxInUs */ 0
                                  )
           != rtos_err_noError
          )
        {
            initOk = false;
        }
    }
    else
        initOk = false;

    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              17
                         , /* tiFirstActivationInMs */    0
                         , /* priority */                 prioTask17ms
                         , /* minPIDToTriggerThisEvent */ 1
                         , /* taskParam */                0
                         )
       == rtos_err_noError
      )
    {
        assert(idEvent == idEv17ms);
        if(rtos_osRegisterUserTask( idEv17ms
                                  , task17ms
                                  , pidTask17ms
                                  , /* tiTaskMaxInUs */ 0
                                  )
           != rtos_err_noError
          )
        {
            initOk = false;
        }
    }
    else
        initOk = false;
        
    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              0 /* Event task, no cycle time */
                         , /* tiFirstActivationInMs */    0
                         , /* priority */                 prioTaskOnButtonDown
                         , /* minPIDToTriggerThisEvent */ 1
                         , /* taskParam */                0
                         )
       == rtos_err_noError
      )
    {
        assert(idEvent == idEvOnButtonDown);
        if(rtos_osRegisterUserTask( idEvOnButtonDown
                                  , taskOnButtonDown
                                  , pidTaskOnButtonDown
                                  , /* tiTaskMaxInUs */ 0 
                                  )
           != rtos_err_noError
          )
        {
            initOk = false;
        }
    }
    else
        initOk = false;

    if(rtos_osCreateEvent( &idEvent
                         , /* tiCycleInMs */              23 /* ms */
                         , /* tiFirstActivationInMs */    3
                         , /* priority */                 prioTaskCpuLoad
                         , /* minPIDToTriggerThisEvent */ 1
                         , /* taskParam */                0
                         )
       == rtos_err_noError
      )
    {
        assert(idEvent == idEvCpuLoad);
        if(rtos_osRegisterUserTask( idEvCpuLoad
                                  , taskCpuLoad
                                  , pidTaskCpuLoad
                                  , /* tiTaskMaxInUs */ 0
                                  )
           != rtos_err_noError
          )
        {
            initOk = false;
        }
    }
    else
        initOk = false;

    /* The last check ensures that we didn't forget to register a task. */
    assert(idEvent == noRegisteredTasks-2);

    /* Initialize the RTOS kernel. The global interrupt processing is resumed if it
       succeeds. The step involves a configuration check. We must not startup the SW if the
       check fails. */
    if(!initOk ||  rtos_osInitKernel() != rtos_err_noError)
        while(true)
            ;

    /* Installing more interrupts should be possible while the system is already running.
       We place the PIT timer initialization here to prove this statement. */
    del_delayMicroseconds(500000);
    osInstallInterruptServiceRoutines();

    /* The code down here becomes our idle task. It is executed when and only when no
       application task is running. */

    /* Prepare the run of the idle task of process 2. */
    static const rtos_taskDesc_t taskIdlePID2Config = { .addrTaskFct = (uintptr_t)taskIdlePID2
                                                      , .PID = 2
                                                      , .tiTaskMax = 0
                                                      };
    while(true)
    {
        checkAndIncrementTaskCnts(idTaskIdle);
        testPCP(idTaskIdle);
        ++ mai_cntTaskIdle;

        /* Activate the non cyclic task. Note, the execution time of this task activation
           will by principle not be considered by the CPU load measurement started from the
           same task (the idle task). */
#ifdef DEBUG
        bool bActivationAccepted =
#endif
        rtos_osTriggerEvent(idEvNonCyclic, /* taskParam */ 0);
        assert(bActivationAccepted);

        /* Run a kind of idle task in process 2. */
        signed int resultIdle ATTRIB_DBG_ONLY = rtos_osRunTask( &taskIdlePID2Config
                                                              , /* taskParam */ mai_cntTaskIdle
                                                              );
        assert(resultIdle == 3*(int)mai_cntTaskIdle);

        /* Compute the average CPU load. Note, this operation lasts about 1s and has a
           significant impact on the cycling speed of this infinite loop. Furthermore, it
           measures only the load produced by the tasks and system interrupts but not that
           of the rest of the code in the idle loop. */
        mai_cpuLoad = gsl_osGetSystemLoad();

        /* In PRODUCTION compilation we halt the software execution if errors where found
           in the data consistency tests. */
        if(_sharedDataTasksIdleAnd1msAndCpuLoad.noErrors != 0)
            rtos_osSuspendProcess(/* PID */ 1);
    }
    
    /* We never get here. Just to avoid a compiler warning. */
    return -1;

} /* End of main */

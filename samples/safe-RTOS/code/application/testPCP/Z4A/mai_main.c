/**
 * @file mai_main.c
 *   C entry function. The core completes the HW initialization (clocks run at full speed,
 * drivers for MPU and devices are initialized).\n
 *   The safe-RTOS is configured to run a few tasks to double-check some aspects of the
 * scheduler, particular of the priority ceiling protocol.\n
 *   Only if all the LEDs are blinking everything is alright.\n
 *   Progress information is permanently written into the serial output channel. A terminal
 * on the development host needs to use these settings: 115000 Bd, 8 Bit data word, no
 * parity, 1 stop bit.\n
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
 *   checkTotalCount
 *   taskA
 *   taskB
 *   taskH
 *   taskO
 *   taskT
 *   taskS
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
//#include "mai_main.h"


/*
 * Defines
 */

/** A wrapper around the API for the priority ceiling protocal (PCP), which lets the API
    for mutual exclusion of a task set look like the API calls from the OSEK/VDX standard.
      Here, for getting the resource, i.e. for entering a critical section of code. */
#define GetResource(resource)                                                               \
            {   uint32_t priorityLevelSoFar;                                                \
                priorityLevelSoFar = rtos_suspendAllTasksByPriority                         \
                                                (/* suspendUpToThisPriority */ (resource));

/** A wrapper around the API for the priority ceiling protocal (PCP), which lets the API
    for mutual exclusion of a task set look like the API calls from the OSEK/VDX standard.
      Here, for returning the resource, i.e. for leaving a critical section of code. */
#define ReleaseResource() rtos_resumeAllTasksByPriority(priorityLevelSoFar); }

/** A wrapper around the API for the priority ceiling protocal (PCP), which lets the API
    for mutual exclusion of a task set look like the API calls from the OSEK/VDX standard.
      Here, for getting the resource, i.e. for entering a critical section of code.\n
      Here for OS tasks (including idle task). */
#define osGetResource(resource)                                                             \
            {   uint32_t priorityLevelSoFar;                                                \
                priorityLevelSoFar = rtos_osSuspendAllTasksByPriority                       \
                                                (/* suspendUpToThisPriority */ (resource));

/** A wrapper around the API for the priority ceiling protocal (PCP), which lets the API
    for mutual exclusion of a task set look like the API calls from the OSEK/VDX standard.\n
      Here, for returning the resource, i.e. for leaving a critical section of code.\n
      Here for OS tasks (including idle task). */
#define osReleaseResource() rtos_osResumeAllTasksByPriority(priorityLevelSoFar); }

/** Some helper code to get the maximum task priority as a constant for the priority ceiling
    protocol. */
#define MAXP(p1,p2)  ((p2)>(p1)?(p2):(p1))

/** The priority level to set for the atomic operations done on the task cycle counts. The
    macro is named such that the code resembles the resource API from the OSEK/VDX
    standard.\n
      Here for mutual exclusion of all particpating tasks. */
#define RESOURCE_ALL    (MAXP(prioEvT,MAXP(prioEvH,MAXP(prioEvA,prioEvB))))

/** The priority level to set for the atomic operations done on the task cycle counts.\n
      Here for mutual exclusion of tasks A, B and H. (Note, this implicitly includes T, if
    H has a higher priority than T.) */
#define RESOURCE_A_B_H  (MAXP(prioEvH,MAXP(prioEvA,prioEvB)))

/** The priority level to set for the atomic operations done on the task cycle counts.\n
      Here for mutual exclusion of tasks A, B and T. */
#define RESOURCE_A_B_T  (MAXP(prioEvT,MAXP(prioEvA,prioEvB)))

/** Error catching for DEBUG and PRODUCTION compilation. */
#define ASSERT(cond)  ({if(!(cond)){success = false; assert(false);}})


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
enum idEvent_t
{
    idEvTaskA = 0,  /// Event for low priority task, which raise prio with PCP
    idEvTaskB,      /// Event for successor task of same priority
    idEvTaskH,      /// Event for task of higer priority, which can preempt A, B
    idEvTaskT,      /// Event for cyclic task
    idEvTaskS,      /// Event for cyclic supervisor task in other process
    
    /** The number of tasks to register. */
    noRegisteredEvents
};


/** The RTOS uses constant priorities for its events, which are defined here.\n
      Note, the priority is a property of an event rather than of a task. A task implicitly
    inherits the priority of the event it is associated with. */
enum prioTask_t
{
    prioTaskIdle = 0,            /* Prio 0 is implicit, cannot be chosen explicitly */
    prioEvA = 3,
    prioEvB = prioEvA,
    prioEvT = prioEvA+2,
    prioEvH = prioEvT+4,
    prioEvS = 11,
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
    pidOs = 0,              /* Kernel always and implicitly has PID 0 */
    pidTaskA = 1,
    pidTaskB = pidTaskA,
    pidTaskO = pidOs,
    pidTaskH = pidTaskA,
    pidTaskT = 1,           /// @todo Try third process and use shared memory
    pidTaskS = 2,
};




/*
 * Local prototypes
 */

/** We preferrably use 64 Bit types for the counter to have a higher risk of harmful race
    conditions. */
typedef unsigned long long counter64_t;


/*
 * Data definitions
 */

/** Counter of calls of ISR for PIT1 interrupt. */
volatile counter64_t SBSS_OS(mai_cntISRPit1) = 0;

/** Counter of calls of ISR for PIT2 interrupt. */
volatile counter64_t SBSS_OS(mai_cntISRPit2) = 0;

/** Counter of calls of ISR for PIT3 interrupt. */
volatile counter64_t SBSS_OS(mai_cntISRPit3) = 0;

/** Counter of cycles of infinite main loop. */
volatile counter64_t SBSS_OS(mai_cntTaskIdle) = 0;

/** Counter of event task A. */
volatile counter64_t SBSS_P1(mai_cntTaskA) = 0;  

/** Counter of event task B. */
volatile counter64_t SBSS_P1(mai_cntTaskB) = 0;  

/** Counter of task O. */
volatile counter64_t SBSS_OS(mai_cntTaskO) = 0;  

/** Counter of event task H. */
volatile counter64_t SBSS_P1(mai_cntTaskH) = 0;

/** Copy of counter of event task H. */
volatile counter64_t SBSS_P1(mai_copyOfCntTaskH) = 0;

/** Counter of timer task T. */
volatile counter64_t SBSS_P1(mai_cntTaskT) = 0;

/** Sum of counters of tasks A, B, O, H and T. Used for test of coherent data access. */
volatile counter64_t SHARED(mai_cntTotalOfAllTasks) = 0;

/** Counter of cyclic task S. */
volatile counter64_t SBSS_P2(mai_cntTaskS) = 0;


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
    _Static_assert(prioEvA <= RTOS_MAX_LOCKABLE_TASK_PRIORITY
                   &&  prioEvB <= RTOS_MAX_LOCKABLE_TASK_PRIORITY
                   &&  prioEvH <= RTOS_MAX_LOCKABLE_TASK_PRIORITY
                   &&  prioEvT <= RTOS_MAX_LOCKABLE_TASK_PRIORITY
                   &&  prioEvS >= RTOS_MAX_LOCKABLE_TASK_PRIORITY
                   &&  prioEvS <= RTOS_MAX_TASK_PRIORITY
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

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
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
    ++ mai_cntISRPit3;

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. Can
       be done as this is "trusted code" that is running in supervisor mode. */
    PIT->TIMER[3].TFLG = PIT_RTI_TFLG_TIF(1);

} /* End of isrPit3 */


/**
 * Check the consistency of the global data to detect harmful and unexpected race
 * conditions.
 *   @return
 * \a true if everything is still alright, \a false otherwise.
 */
static bool checkTotalCount(void)
{
    /* Supervisory task S can't have mutual exclusion with the normal worker tasks. It must
       not participate the consistency check. */
    return mai_cntTaskIdle + mai_cntTaskA + mai_cntTaskB + mai_cntTaskH + mai_cntTaskT
           + mai_cntTaskO 
           == mai_cntTotalOfAllTasks;

} /* End of checkTotalCount */



/**
 * Task A. Accesses data in a critical section shaped with PCP.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process. This mechanism is used to report a problem in PRODUCTION
 * compilation, when we have no assertions available.
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @param taskParam
 * A variable task parameter. Here just used for testing.
 */
static int32_t taskA(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam)
{
    bool success = true;

    ASSERT(taskParam == (uintptr_t)mai_cntTaskA);
    
    /* Concept: Tasks B and H are event triggered by A and have no race conditions with
       each other. H has higher priority as A and B, which have the same priority. Task T
       can preempt.
         A triggers H and double checks immediate increase of its counter.
         A raises the current priority level and repeats the same. H's counter must not
       increase.
         A lowers the priority again and checks for immediate increase of H's counter.
         Same with priority raised to a level, which doesn't include H. A needs to see an
      immediate increase of H's counter, i.e. before lowering the priority again.
         A raises the priority to a level which includes T and blocks for a while, which is
       longer than the cycle time of T. It checks for an increase of the activation loss
       counter of T.
         A lowers the priority to a level which doesn't include T any longer and blocks for
       a while, which is longer than the cycle time of T. It checks for no further
       activation losses of T, i.e. T is now running and preempting A.
         A raises the priority level so that H is included. It stores the counter value of
       H (for task B) and terminates gracefully. H needs to be immediately called due to
       the implicit lowering of the priority at the end of task A. Task B will check for an
       increase of H's counter. */

    /* A triggers H and double checks immediate increase of its counter. */
    counter64_t tmpCntH = mai_cntTaskH;
    bool evCouldBeTriggered = rtos_triggerEvent(idEvTaskH, /* taskParam */ 0);
    ASSERT(tmpCntH+1 == mai_cntTaskH);
    tmpCntH = mai_cntTaskH;
    ASSERT(evCouldBeTriggered);
    
    /* Use PCP to hinder the triggered task from immediate activation. */
    GetResource(RESOURCE_ALL);
    evCouldBeTriggered = rtos_triggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be no counter change now. */
    ASSERT(tmpCntH == mai_cntTaskH); 
    ASSERT(evCouldBeTriggered);
    
    /* Use PCP the release tasks of higher priority. */
    ReleaseResource();
    /* Task H must execute immediately and before we have the chance to do anything else. */
    ASSERT(tmpCntH+1 == mai_cntTaskH); 
    tmpCntH = mai_cntTaskH;

    /* Use PCP to raise priority but not to the extend that is observable but doesn't
       hinder the triggered task from immediate activation yet. */
    GetResource(RESOURCE_A_B_T);
    const counter64_t tmpCntT = mai_cntTaskT;
    evCouldBeTriggered = rtos_triggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be an immediate counter change. */
    ASSERT(tmpCntH+1 == mai_cntTaskH);
    tmpCntH = mai_cntTaskH;
    ASSERT(evCouldBeTriggered);
    /* Task T must be blocked. We check this by busy wait such long that T needs to undergo
       at least one activation loss. */
    uint32_t noActivationLoss = rtos_getNoActivationLoss(idEvTaskT);
    del_delayMicroseconds(/* tiCpuInUs */ 4100);
    ASSERT(noActivationLoss < rtos_getNoActivationLoss(idEvTaskT)
           || noActivationLoss == UINT_MAX
          );
    ASSERT(tmpCntT == mai_cntTaskT);
    evCouldBeTriggered = rtos_triggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be an immediate counter change. */
    ASSERT(tmpCntH+1 == mai_cntTaskH);
    tmpCntH = mai_cntTaskH;
    ASSERT(evCouldBeTriggered);
    
    /* A lowers the priority such that T will be served again. No more activation losses
       should be observed. Moreover, as we saw at least one loss, we know that the event
       must be triggered now. We need to see at least one immediate cycle from T. */
    ASSERT(tmpCntT == mai_cntTaskT);
    _Static_assert(prioEvT > prioEvA+1, "Undesired priority configuration");
    rtos_resumeAllTasksByPriority(prioEvT-1);
    ASSERT(tmpCntT+1 <= mai_cntTaskT);
    noActivationLoss = rtos_getNoActivationLoss(idEvTaskT);
    del_delayMicroseconds(/* tiCpuInUs */ 4100);
    ASSERT(noActivationLoss == rtos_getNoActivationLoss(idEvTaskT));
    evCouldBeTriggered = rtos_triggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be an immediate counter change. */
    ASSERT(tmpCntH+1 == mai_cntTaskH);
    tmpCntH = mai_cntTaskH;
    ASSERT(evCouldBeTriggered);
    ReleaseResource();
    
    GetResource(RESOURCE_ALL);
    ++ mai_cntTaskA;
    ++ mai_cntTotalOfAllTasks;
    ASSERT(checkTotalCount());
    ReleaseResource();

    /* A triggers B. There must be no immediate counter change because of the same
       priority. */
    const counter64_t tmpCntB = mai_cntTaskB;
    evCouldBeTriggered = rtos_triggerEvent(idEvTaskB, /* taskParam */ (uintptr_t)mai_cntTaskB);
    ASSERT(tmpCntB == mai_cntTaskB);
    ASSERT(evCouldBeTriggered);

    /* A blocks and triggers H and leaves without releasing the lock. The scheduler needs
       to take care. */
    GetResource(RESOURCE_ALL); 
    evCouldBeTriggered = rtos_triggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be no immediate counter change because of the lock. */
    ASSERT(tmpCntH == mai_cntTaskH);
    mai_copyOfCntTaskH = tmpCntH;
    ASSERT(evCouldBeTriggered);
    /* Instead of ReleaseResource: */ ASSERT(priorityLevelSoFar == prioEvA);}

    return success? 0: -1;

} /* End of taskA */



/**
 * Task B, the successor of task A. B is explicitly triggered by A.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process. This mechanism is used to report a problem in PRODUCTION
 * compilation, when we have no assertions available.
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @param taskParam
 * A variable task parameter. Here just used for testing.
 */
static int32_t taskB(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam)
{
    bool success = true;

    ASSERT(taskParam == (uintptr_t)mai_cntTaskB);
    
    /* Task H needs to have executed after leaving A but before entering B. */
    ASSERT(mai_copyOfCntTaskH+1 == mai_cntTaskH);

    GetResource(RESOURCE_ALL);
    ++ mai_cntTaskB;
    ++ mai_cntTotalOfAllTasks;
    ASSERT(checkTotalCount());
    ReleaseResource();
    
    /* A, B and O need to be always in sync. There are no race conditions. */
    ASSERT(mai_cntTaskA == mai_cntTaskB  &&  mai_cntTaskB == mai_cntTaskO+1);

    /* B blocks and triggers H and leaves without releasing the lock. The scheduler needs
       to take care. */
    GetResource(RESOURCE_ALL);
    const counter64_t tmpCntH = mai_cntTaskH;
    const bool evCouldBeTriggered = rtos_triggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be no immediate counter change because of the lock. */
    ASSERT(tmpCntH == mai_cntTaskH);
    mai_copyOfCntTaskH = tmpCntH;
    ASSERT(evCouldBeTriggered);
    /* Instead of ReleaseResource: */ ASSERT(priorityLevelSoFar == prioEvB);}

    return success? 0: -1;

} /* End of taskB */




/**
 * Task O, the successor of task B. O is associated with the same event as triggers B.
 *   @param taskParam
 * A variable task parameter. Here not used.
 *   @param taskParam
 * A variable task parameter. Here just used for testing.
 */
static void taskO(uintptr_t taskParam)
{
    bool success = true;

    ASSERT(taskParam+1 == (uintptr_t)mai_cntTaskB);
    
    /* Task H needs to have executed after leaving B but before entering O. */
    ASSERT(mai_copyOfCntTaskH+1 == mai_cntTaskH);

    /* In task O, we repeat most of the tests from task A to see if the OS API works the
       same as the user mode API. */

    /* O triggers H and double checks immediate increase of its counter. */
    counter64_t tmpCntH = mai_cntTaskH;
    bool evCouldBeTriggered = rtos_osTriggerEvent(idEvTaskH, /* taskParam */ 0);
    ASSERT(tmpCntH+1 == mai_cntTaskH);
    tmpCntH = mai_cntTaskH;
    ASSERT(evCouldBeTriggered);
    
    /* Use PCP to hinder the triggered task from immediate activation. */
    osGetResource(RESOURCE_ALL);
    evCouldBeTriggered = rtos_osTriggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be no counter change now. */
    ASSERT(tmpCntH == mai_cntTaskH); 
    ASSERT(evCouldBeTriggered);
    
    /* Use PCP the release tasks of higher priority. */
    osReleaseResource();
    /* Task H must execute immediately and before we have the chance to do anything else. */
    ASSERT(tmpCntH+1 == mai_cntTaskH); 
    tmpCntH = mai_cntTaskH;

    /* Use PCP to raise priority but not to the extend that is observable but doesn't
       hinder the triggered task from immediate activation yet. */
    osGetResource(RESOURCE_A_B_T);
    const counter64_t tmpCntT = mai_cntTaskT;
    evCouldBeTriggered = rtos_osTriggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be an immediate counter change. */
    ASSERT(tmpCntH+1 == mai_cntTaskH);
    tmpCntH = mai_cntTaskH;
    ASSERT(evCouldBeTriggered);
    /* Task T must be blocked. We check this by busy wait such long that T needs to undergo
       at least one activation loss. */
    uint32_t noActivationLoss = rtos_getNoActivationLoss(idEvTaskT);
    del_delayMicroseconds(/* tiCpuInUs */ 4100);
    ASSERT(noActivationLoss < rtos_getNoActivationLoss(idEvTaskT)
           || noActivationLoss == UINT_MAX
          );
    ASSERT(tmpCntT == mai_cntTaskT);
    evCouldBeTriggered = rtos_osTriggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be an immediate counter change. */
    ASSERT(tmpCntH+1 == mai_cntTaskH);
    tmpCntH = mai_cntTaskH;
    ASSERT(evCouldBeTriggered);
    
    /* O lowers the priority such that T will be served again. No more activation losses
       should be observed. Moreover, as we saw at least one loss, we know that the event
       must be triggered now. We need to see at least one immediate cycle from T. */
    ASSERT(tmpCntT == mai_cntTaskT);
    _Static_assert(prioEvT > prioEvB+1, "Undesired priority configuration");
    rtos_osResumeAllTasksByPriority(prioEvT-1);
    ASSERT(tmpCntT+1 <= mai_cntTaskT);
    noActivationLoss = rtos_getNoActivationLoss(idEvTaskT);
    del_delayMicroseconds(/* tiCpuInUs */ 4100);
    ASSERT(noActivationLoss == rtos_getNoActivationLoss(idEvTaskT));
    evCouldBeTriggered = rtos_osTriggerEvent(idEvTaskH, /* taskParam */ 0);
    /* There must be an immediate counter change. */
    ASSERT(tmpCntH+1 == mai_cntTaskH);
    tmpCntH = mai_cntTaskH;
    ASSERT(evCouldBeTriggered);
    osReleaseResource();
    
    osGetResource(RESOURCE_ALL);
    ++ mai_cntTaskO;
    ++ mai_cntTotalOfAllTasks;
    ASSERT(checkTotalCount());
    osReleaseResource();
    
    /* A, B and O need to be always in sync. There are no race conditions. */
    ASSERT(mai_cntTaskA == mai_cntTaskB  &&  mai_cntTaskB == mai_cntTaskO);

    /* Implementation problem: No error reporting is offered by the RTOS for OS tasks. For
       PRODUCTION compilation and if we detected a problem then we have to report it
       somehow differently. We inject another error, which will be handled at latest in the
       next user mode task. */
    if(!success)       
    {
        osGetResource(RESOURCE_ALL);
        -- mai_cntTaskO;
        osReleaseResource();
    }
} /* End of taskO */




/**
 * Event task H, which is of higher priority as A and B. It must not have
 * any race conditions with these as it is triggered only (and synchronously) by A.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process. This mechanism is used to report a problem in PRODUCTION
 * compilation, when we have no assertions available.
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t taskH(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    bool success = true;

    /* This should be the task of highest priority, which allows us to omit the code for
       entering and leaving the critical section. */
    _Static_assert(prioEvH == RESOURCE_ALL, "Bad priority configuration");
    //GetResource(RESOURCE_ALL_TASKS);
    ++ mai_cntTaskH;
    ++ mai_cntTotalOfAllTasks;
    ASSERT(checkTotalCount());
    //ReleaseResource();

    return success? 0: -1;

} /* End of taskH */




/**
 * Timer triggered task T, which is of higher priority as tasks A and B.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process. This mechanism is used to report a problem in PRODUCTION
 * compilation, when we have no assertions available.
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t taskT(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    bool success = true;

    GetResource(RESOURCE_ALL);
    ++ mai_cntTaskT;
    ++ mai_cntTotalOfAllTasks;
    ASSERT(checkTotalCount());
    ReleaseResource();

    if((mai_cntTaskT & (1024-1)) == 0)
    {
        const unsigned int noLostActivations = rtos_getNoActivationLoss(idEvTaskT);
        unsigned long long total = (mai_cntTaskT+noLostActivations) / 500;
        const unsigned int h = (unsigned int)(total / 3600ull);
        total -= 3600ull*h;
        const unsigned int min = (unsigned int)(total / 60ull);
        total -= 60ull*min;
        const unsigned int sec = (unsigned int)total;
        
        iprintf( "%3u:%02u:%02u, cycles: Task S: %llu, tasks A, B, O: %llu"
                 ", task H: %llu, task T: %llu (%u lost activations),"
                 "isrPit1: %llu, isrPit2: %llu, isrPit3: %llu\r\n"
               , h, min, sec
               , mai_cntTaskS
               , mai_cntTaskA
               , mai_cntTaskH
               , mai_cntTaskT
               , noLostActivations
               , mai_cntISRPit1
               , mai_cntISRPit2
               , mai_cntISRPit3
               );
    }

    return success? 0: -1;

} /* End of taskT */




/**
 * Timer triggered supervisor task S. It looks for failures and flashes the LED as long as
 * no failure is recognized.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process. This mechanism is used to report a problem in PRODUCTION
 * compilation, when we have no assertions available.
 *   @param PID
 * The ID of the process, the task function is executed in.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
static int32_t taskS(uint32_t PID ATTRIB_DBG_ONLY, uintptr_t taskParam ATTRIB_UNUSED)
{
    /* This task runs in another process as the supervised tasks. */
    assert(PID == 2);
    
    ++ mai_cntTaskS;
    
    const unsigned int stackReserveOs = rtos_getStackReserve(/* PID */ pidOs)
                     , stackReserveP1 = rtos_getStackReserve(/* PID */ 1)
                     , stackReserveP2 = rtos_getStackReserve(/* PID */ 2);
                     
    const bool success = rtos_getNoTotalTaskFailure(/* PID */ 1) == 0
                         &&  rtos_getNoTotalTaskFailure(/* PID */ 2) == 0
                         &&  stackReserveOs >= 3072
                         &&  stackReserveP1 >= 1024
                         &&  stackReserveP2 >= 1024
                         &&  rtos_getNoActivationLoss(idEvTaskA) == 0
                         &&  rtos_getNoActivationLoss(idEvTaskB) == 0
                         &&  rtos_getNoActivationLoss(idEvTaskH) == 0
                         &&  rtos_getNoActivationLoss(idEvTaskS) == 0
                         ;
    if(success)
    {
        /* Normal operation: Let first LED blink at about 1 Hz. */
        lbd_setLED(lbd_led_0_DS11, /* isOn */ (mai_cntTaskS & 32) != 0);
    }
    else if(!rtos_isProcessSuspended(/* PID */ 1))
    {
        lbd_setLED(lbd_led_0_DS11, /* isOn */ false);
        rtos_suspendProcess(/* PID */ 1);
    }
    else
    {
        /* Failure: Let another LED blink at higher rate. */
        lbd_setLED(lbd_led_7_DS4, /* isOn */ (mai_cntTaskS & 16) != 0);
    }

    return success? 0: -1;

} /* End of taskS */




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
         Caution: On the MPC5748G, this is not an opton but an essential prerequisite for
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
      )
    {
        initOk = false;
    }


#define CREATE_TASK(name, tiCycleInMs)                                                      \
    if(rtos_osCreateEvent( &idEvent                                                         \
                         , /* tiCycleInMs */              tiCycleInMs                       \
                         , /* tiFirstActivationInMs */    0                                 \
                         , /* priority */                 prioEv##name                      \
                         , /* minPIDToTriggerThisEvent */ tiCycleInMs == 0                  \
                                                          ? 1                               \
                                                          : RTOS_EVENT_NOT_USER_TRIGGERABLE \
                         , /* taskParam */                0                                 \
                         )                                                                  \
       == rtos_err_noError                                                                  \
      )                                                                                     \
    {                                                                                       \
        assert(idEvent == idEvTask##name);                                                  \
        if(rtos_osRegisterUserTask( idEvTask##name                                          \
                                  , task##name                                              \
                                  , pidTask##name                                           \
                                  , /* tiTaskMaxInUs */ 100000                              \
                                  )                                                         \
           != rtos_err_noError                                                              \
          )                                                                                 \
        {                                                                                   \
            initOk = false;                                                                 \
        }                                                                                   \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        initOk = false;                                                                     \
    }
/* End of macro CREATE_TASK */

    /* Create the events that trigger application tasks at the RTOS. Note, we do not really
       respect the ID, which is assigned to the event by the RTOS API rtos_osCreateEvent().
       The returned value is redundant. This technique requires that we create the events
       in the right order and this requires in practice a double-check by assertion - later
       maintenance errors are unavoidable otherwise. */
    unsigned int idEvent;
    CREATE_TASK(/* name */ A, /* tiCycleInMs */ 0)
    CREATE_TASK(/* name */ B, /* tiCycleInMs */ 0)
    CREATE_TASK(/* name */ H, /* tiCycleInMs */ 0)
    CREATE_TASK(/* name */ T, /* tiCycleInMs */ 2)
    CREATE_TASK(/* name */ S, /* tiCycleInMs */ 13)

    /* Create OS task for same event as triggers task B. O becomes a successor of B. */
    if(rtos_osRegisterOSTask(idEvTaskB, taskO) != rtos_err_noError)
        initOk = false;                                                               

    /* The last check ensures that we didn't forget to register a task. */
    assert(initOk &&  idEvent == noRegisteredEvents-1);

    rtos_osGrantPermissionSuspendProcess( /* pidOfCallingTask */ 2 /* Supervisor */
                                        , /* targetPID */ 1        /* Tasks A, B, T, H */
                                        );

    /* Installing irrelated interrupts should be possible before the system is running.
       We place the PIT timer initialization here to prove this statement. */
    osInstallInterruptServiceRoutines();
    del_delayMicroseconds(500000);

    /* Initialize the RTOS kernel. The global interrupt processing is resumed if it
       succeeds. The step involves a configuration check. We must not startup the SW if the
       check fails. */
    if(!initOk ||  rtos_osInitKernel() != rtos_err_noError)
        while(true)
            ;

    /* Here we are in the idle task. */

    bool success ATTRIB_UNUSED = true;
    while(true)    
    {
/// @todo Add: osGetResource with level higher than idle but lower than A. Should work with and without osReleaseResource

        /* Trigger the first of the chained test tasks.
             Since we are here in idle, the trigger needs to be always possible. */
        bool evCouldBeTriggered ATTRIB_DBG_ONLY =
                                rtos_osTriggerEvent( idEvTaskA
                                                   , /* taskParam */ (uintptr_t)mai_cntTaskA
                                                   );
        ASSERT(2*mai_cntTaskIdle+1 == mai_cntTaskA);
        assert(evCouldBeTriggered);

        osGetResource(RESOURCE_ALL);
        ASSERT(2*mai_cntTaskIdle+1 == mai_cntTaskA);
        evCouldBeTriggered = rtos_osTriggerEvent( idEvTaskA
                                                , /* taskParam */ (uintptr_t)mai_cntTaskA
                                                );
        ASSERT(2*mai_cntTaskIdle+1 == mai_cntTaskA);
        osReleaseResource();
        ASSERT(2*mai_cntTaskIdle+2 == mai_cntTaskA);
        assert(evCouldBeTriggered);
        
        /* Make spinning of the idle task observable in the debugger. */
        osGetResource(RESOURCE_ALL);
        ++ mai_cntTaskIdle;
        ++ mai_cntTotalOfAllTasks;
        osReleaseResource();
    }
} /* End of main */

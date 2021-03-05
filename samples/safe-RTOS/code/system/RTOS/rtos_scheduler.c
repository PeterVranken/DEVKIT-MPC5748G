/**
 * @file rtos_scheduler.c
 * This file implements a simple yet "safe" Real Time Operating System (RTOS) for the
 * MPC5748G.\n
 *   The RTOS offers a strictly priority controlled scheduler. The user code is organized
 * in processes and tasks. Any task belongs to one of the processes. Different processes
 * have different privileges. The concept is to use the process with highest privileges for
 * the safety tasks.\n
 *   A task is activated by an event; an application will repeatedly use the API
 * rtos_osCreateEvent() to define the conditions or points in time, when the tasks have to
 * become due.\n
 *   Prior to the start of the scheduler (and thus prior to the beginning of the
 * pseudo-parallel, concurrent execution of the tasks) all later used tasks are registered
 * at the scheduler; an application will repeatedly use the APIs rtos_osRegisterUserTask()
 * and rtos_osRegisterOSTask().\n
 *   After all needed tasks are registered the application will start the RTOS' kernel
 * by calling the API rtos_osInitKernel() and task scheduling begins.\n
 *   A task is mainly characterized by the owning process, the task function and a
 * priority; the C code function is invoked in the context of the process and at given
 * priority level when the task is activated. The function is executed either until the
 * task function is left or the task function or one of its sub-routines requests task
 * termination by means of a system call or the task function is aborted by an exception.\n
 *   "Context of a process" mainly relates to the memory management concept. Any process
 * has its private memory. This memory is either write-accessible only for the owning
 * process or for the owning process and all other processes with higher privileges. The
 * "or" in this statement is a matter of project configuration. A few more elements are
 * process dependent; many system calls are restricted to processes of sufficient
 * privileges.\n
 *   "Activated" does still not necessarily mean executing for a task; the more precise
 * wording is that the activation makes a task immediately and unconditionally "ready"
 * (i.e. ready for execution). If more than a single task are ready at a time then the
 * function of the task with higher priority is executed first and the function of the
 * other task will be served only after completion of the first. Several tasks can be
 * simultaneously ready and one of them will be executed, this is the one and only
 * "running" task.\n
 *   "Are ready at a time" does not necessarily mean that both tasks have been activated at
 * the same point in time. If task A of priority Pa is activated first and as only task
 * then it'll be executed regardless of its priority. If task B of priority Pb is activated
 * later, but still before A has completed then we have two tasks which have been activated
 * "at a time". The priority relation decides what happens:\n
 *   If Pa >= Pb then A is completed and B will be started and executed only after A has
 * completed.\n
 *   If Pb > Pa then task A turns from state running back to state ready and B becomes the
 * running task until it completes. Now A as remaining ready, yet uncompleted task
 * becomes the running task again and it can complete.\n
 *   With other words, if a task is activated and it has a higher priority than the running
 * task then it'll preempt the running task and it'll become the running task itself.\n
 *   If no task is ready at all then the scheduler continues the original code thread,
 * which is the code thread starting in function main() and which first registers the tasks
 * and then starts the kernel. (Everything in this code thread, which is placed behind
 * the call of API rtos_osInitKernel() is called the "idle task".)\n
 *   The implemented scheduling scheme leads to a strictly hierarchical execution order of
 * tasks. This scheme is sometimes referred to as scheduling of tasks of Basic Conformance
 * Class (BCC). It's simple, less than what most RTOSs offer, but still powerful enough for
 * the majority of industrial use cases.\n
 * Basic conformance class means that a task cannot suspend intentionally and ahead of
 * its normal termination. Once started, it needs to be entirely executed. Due to the
 * strict priority scheme it'll temporarily suspend only for sake of tasks of higher
 * priority (but not voluntarily or on own desire). Another aspect of the same is that the
 * RTOS doesn't know task to task events -- such events are usually the way intentional
 * suspension and later resume of tasks is implemented.\n
 *   The activation of a task can be done by software, using API function
 * rtos_osTriggerEvent() or rtos_triggerEvent() or it can be done by the scheduler on a
 * regular time base. In the former case the task is called an event task, the latter is a
 * cyclic task with fixed period time.\n
 *   The RTOS implementation is tightly connected to the implementation of interrupt
 * services. Interrupt services, e.g. to implement I/O operations for the tasks, are
 * registered with rtos_osRegisterInterruptHandler(). There are a few services, which are
 * available to ISRs:
 *   - An ISR may use rtos_osEnterCriticalSection()/rtos_osLeaveCriticalSection(),
 * rtos_osSuspendAllInterrupts()/rtos_osResumeAllInterrupts() or
 * rtos_osSuspendAllInterruptsByPriority()/rtos_osResumeAllInterruptsByPriority() to shape
 * critical sections with other ISRs or with OS tasks, which are based on interrupt locks
 * and which are highly efficient. (Note, safety concerns forbid having an API to shape a
 * critical section between ISRs and user tasks)
 *   - An ISR may use rtos_osTriggerEvent() to trigger an event. The associated tasks will
 * be scheduled after returning from the interrupt (and from any other interrupt it has
 * possibly preempted)
 *   - An ISR may use rtos_osRunTask to implement a callback into another process. The
 * callback is run under the constraints of the target process and can therefore be
 * implemented as part of the application(s) in that process and still without breaking the
 * safety concept
 *
 * Safety:\n
 *   The RTOS is based on its "unsafe" counterpart published at
 * https://github.com/PeterVranken/TRK-USB-MPC5643L/tree/master/LSM/RTOS-VLE. Most
 * explanations given there still hold. There are two major differences:\n
 *   In this project, we have replaced the hardware scheduler with a scheduler implemented
 * in software. The behavior is nearly identical and the performance penalty is little in
 * comparison to the advantage of now having an unlimited number of events, priorities and
 * tasks.\n
 *   The second modification is the added safety concept. Such a concept starts with a
 * specification of what we expect from a "safe" RTOS:\n
 *   "If the implementation of a task, which is meant the supervisory or safety task, is
 * itself free of faults then the RTOS shall guarantee that this task is correctly and
 * timely executed regardless of whatever imaginable failures are made by any other
 * process."\n
 *   This requirement serves at the same time as the definition of the term "safe", when
 * used in the context of this RTOS. safe-RTOS promises no more than this requirement says.
 * As a consequence, a software made with this RTOS is not necessarily safe and even if it
 * is then the system using that software is still not necessarily safe.\n
 *   The implementation uses the CPU's "problem state" in conjunction with exception
 * handlers and memory protection to meet the requirement.
 *   More details can be found at
 * https://github.com/PeterVranken/TRK-USB-MPC5643L/tree/master/LSM/safe-RTOS-VLE#3-the-safety-concept.
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
 *   rtos_osCreateEvent
 *   rtos_osRegisterInitTask
 *   rtos_osRegisterUserTask
 *   rtos_osRegisterOSTask
 *   rtos_osInitKernel
 *   rtos_osTriggerEvent
 *   rtos_scFlHdlr_triggerEvent
 *   rtos_osProcessTriggeredEvents
 *   rtos_osSuspendAllTasksByPriority
 *   rtos_osResumeAllTasksByPriority
 *   rtos_getNoActivationLoss
 *   rtos_osGetTaskBasePriority
 *   rtos_getCurrentTaskPriority
 * Module inline interface
 * Local functions
 *   getEventByID
 *   getEventByIdx
 *   registerTask
 *   osTriggerEvent
 *   checkEventDue
 *   onOsTimerTick
 *   launchAllTasksOfEvent
 *   initRTOSClockTick
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "rtos_process.h"
#include "rtos_externalInterrupt.h"
#include "rtos_priorityCeilingProtocol.h"
#include "rtos_ivorHandler.h"
#include "rtos_systemMemoryProtectionUnit.h"
#include "rtos_scheduler_defSysCalls.h"
#include "rtos_scheduler.h"
#include "rtos_kernelInstanceData.h"
#include "rtos_runTask.h"
#include "rtos.h"


/*
 * Defines
 */

/* The assembler code doesn't have access to all defines found in the sphere of C code.
   This makes it essential to have a cross check here, were we can access the definitions
   from both spheres. */
#if RTOS_NO_ERR_PRC != RTOS_NO_CAUSES_TASK_ABORTION                                     \
    ||  RTOS_ERR_PRC_PROCESS_ABORT != RTOS_CAUSE_TASK_ABBORTION_PROCESS_ABORT           \
    ||  RTOS_ERR_PRC_MACHINE_CHECK != RTOS_CAUSE_TASK_ABBORTION_MACHINE_CHECK           \
    ||  RTOS_ERR_PRC_DEADLINE != RTOS_CAUSE_TASK_ABBORTION_DEADLINE                     \
    ||  RTOS_ERR_PRC_DI_STORAGE != RTOS_CAUSE_TASK_ABBORTION_DI_STORAGE                 \
    ||  RTOS_ERR_PRC_SYS_CALL_BAD_ARG  != RTOS_CAUSE_TASK_ABBORTION_SYS_CALL_BAD_ARG    \
    ||  RTOS_ERR_PRC_ALIGNMENT != RTOS_CAUSE_TASK_ABBORTION_ALIGNMENT                   \
    ||  RTOS_ERR_PRC_PROGRAM_INTERRUPT  != RTOS_CAUSE_TASK_ABBORTION_PROGRAM_INTERRUPT  \
    ||  RTOS_ERR_PRC_FPU_UNAVAIL != RTOS_CAUSE_TASK_ABBORTION_FPU_UNAVAIL               \
    ||  RTOS_ERR_PRC_TBL_DATA != RTOS_CAUSE_TASK_ABBORTION_TBL_DATA                     \
    ||  RTOS_ERR_PRC_TBL_INSTRUCTION != RTOS_CAUSE_TASK_ABBORTION_TBL_INSTRUCTION       \
    ||  RTOS_ERR_PRC_SPE_INSTRUCTION != RTOS_CAUSE_TASK_ABBORTION_SPE_INSTRUCTION       \
    ||  RTOS_ERR_PRC_USER_ABORT != RTOS_CAUSE_TASK_ABBORTION_USER_ABORT                 \
    ||  RTOS_ERR_PRC_RESERVED != RTOS_CAUSE_TASK_ABBORTION_RESERVED                     \
    ||  RTOS_SPR_PIR != SPR_PIR
# error Inconsistencies found between definitions made in C and assembler code
#endif

/* The user API header file rtos.h doesn't recursively include all headers of all
   implementing files. Therefore it needs to make some assumptions about basically variable
   but normally never changed constants. These assumptions need of course to be double
   checked. We do this here at compile time of the RTOS. */
#if RTOS_IDX_SC_TRIGGER_EVENT != RTOS_SYSCALL_TRIGGER_EVENT
# error Inconsistent definitions made in C modules and RTOS API header file rtos.h
#endif

#if RTOS_MAX_LOCKABLE_TASK_PRIORITY >= RTOS_MAX_TASK_PRIORITY
# error Suspicious task priority configuration
#endif

/** A pseudo event ID. Used to register a process initialization task using registerTask(). */
#define EVENT_ID_INIT_TASK     (UINT_MAX)

/** Select the static configuration, which applies to the calling core. It's a simple
    selection from one out of three statically defined macros. Selection is done by
    name pattern. */
#define GET_CORE_VALUE(macro, idxCore)                                          \
            ((idxCore)==0? (macro##_CORE_0)                                     \
                         : ((idxCore)==1? (macro##_CORE_1): (macro##_CORE_2))   \
            )
            

/*
 * Local type definitions
 */


/*
 * Local prototypes
 */

/** Hook function for ISRs and system calls: Some tasks of triggered events are possibly to
    be executed (depending on priority rules).\n
      Note, this function is not publically declared although it is global. It is called
    externally only from the assembly code, which can't read public declarations in header
    files.
      @param pEvent
    The first event in global list, which is to be considered for scheduling. */
void rtos_osProcessTriggeredEvents(rtos_eventDesc_t *pEvent);


/*
 * Data definitions
 */

/** A constant array holding the index of a PIT timer for each core on the chip. This is
    just the configuration data and it leaves it open, whether the core runs the RTOS and
    whether the index is used at all. */
static const unsigned int rtos_idxRtosTimerAry[RTOS_NO_CORES] =
    { [0] = GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 0)
    , [1] = GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 1)
    , [2] = GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 2)
    };


/*
 * Function implementation
 */

/**
 * Helper: Resolve the linear event index used at the API into the actual object. The
 * mapping is not trivial since the events are internally ordered by priority.
 *   @return
 * Get the event object by reference.
 *   @param idEvent
 * The linear index of the event as used at the API.
 *   @remark
 * The mapping is not essential for the kernel. It implies avoidable run-time effort. The
 * only reason for having the mapping is a user friendly configuration API. If we had a
 * configuration tool (similar to OSEK OIL tool) or if we would put some documented
 * restrictions on the configuration API then we could have a implicit one-by-one mapping
 * without any loss of functionality.
 *   @remark
 * This function must be called from a supervisor context only. It makes use of priviledged
 * instructions.
 */
static ALWAYS_INLINE rtos_eventDesc_t *getEventByID(unsigned int idEvent)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    assert(idEvent < pIData->noEvents);
    return pIData->mapEventIDToPtr[idEvent];

} /* End of getEventByID */



/**
 * Helper: Resolve the linear, zeror based, internally used array index into the actual
 * event object. This function is trivial and intended more for completeness: it
 * complements the other function getEventByID().
 *   @return
 * Get the event object by reference.
 *   @param idxEvent
 * Index of event object in the array rtos_getInstancePtr()->eventAry.
 *   @remark
 * This function must be called from a supervisor context only. It makes use of priviledged
 * instructions.
 */
static ALWAYS_INLINE rtos_eventDesc_t *getEventByIdx(unsigned int idxEvent)
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    return &pIData->eventAry[idxEvent];

} /* End of getEventByIdx */




/**
 * Registration of a task. Normal, event activated tasks and process initialization tasks
 * can be registered for later execution. This can be both, user mode tasks and operating
 * system tasks. This function is repeatedly called by the application code as often as
 * tasks are required.\n
 *   All calls of this function need to be done prior to the start of the kernel using
 * rtos_osInitKernel().
 *   @return
 * \a rtos_err_noError (zero) if the task could be registered. The maximum number of normal
 * tasks is limited to #RTOS_MAX_NO_TASKS (regardless, how they are distributed among
 * processes). The maximum number of initialization tasks is one per process or for the OS.
 * If the limit is exceeded or if the task specification is invalid then the function
 * returns a non zero value from enumeration \a rtos_errorCode_t.\n
 *   An assertion in the calling code is considered appropriate to handle the error because
 * it'll always be a static configuration error.
 *   @param idEvent
 * Any (normal) task is activated by an event and a task without related event is useless.
 * This call associates the registered task with an already created event. See
 * rtos_osCreateEvent().\n
 *   If a process or OS initialization task is registered, then \a idEvent is set to
 * #EVENT_ID_INIT_TASK. It is allowed not to register an init task for a process or
 * for the OS but it is not possible to register more than one (or to re-register an) init
 * task for a given process or the OS.\n
 *   The order of registration of several tasks with one and the same event matters. The
 * tasks will be acivated in order of registration whenever the event becomes due or is
 * triggered by software.\n
 *   The order of registration doesn't matter for initialization tasks! The OS
 * initialization task is served first. Processes are always initialized in order of rising
 * process ID. The most privileged process is served last and can thus override descisions
 * of its less privileged predecessors.
 *   @param addrTaskFct
 * The task function, which is run in process \a PID every time, the event \a idEvent
 * triggers.
 *   @param PID
 *   The process the task belongs to by identifier. We have a fixed, limited number of four
 * processes (#RTOS_NO_PROCESSES) plus the kernel process, which has ID 0. The range of
 * process IDs to be used here is 0 .. #RTOS_NO_PROCESSES.\n
 *   @param tiTaskMaxInUs
 * Time budget for the user task in Microseconds. This budget is granted for each
 * activation of the task, i.e. each run of \a addrTaskFct(). The budget relates to
 * deadline monitoring, i.e. it is a world time budget, not an execution time budget.\n
 *   Deadline monitoring is supported up to a maximum execution time of
 * #RTOS_TI_DEADLINE_MAX_IN_US Microseconds.\n
 *   A value of zero means that deadline monitoring is disabled for the task.\n
 *   There's no deadline monitoring for OS tasks. If \a PID is zero then \a
 * tiTaskMaxInUS needs to be zero, too.
 *   @remark
 * Never call this function after the call of rtos_osInitKernel()!
 *   @remark
 * This function must be called by trusted code in supervisor mode only.
 */
static rtos_errorCode_t registerTask( unsigned int idEvent
                                    , uintptr_t addrTaskFct
                                    , unsigned int PID
                                    , unsigned int tiTaskMaxInUs
                                    )
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    /* The scheduler should be in halted state. */
    if(pIData->tiOsStep != 0)
        return rtos_err_configurationOfRunningKernel;

    /* The event need to be created before the task can be registered. */
    if(idEvent >= pIData->noEvents  &&  idEvent != EVENT_ID_INIT_TASK)
        return rtos_err_badEventId;

    /* The process ID needs to be in the fixed and limited range. */
    if(PID > RTOS_NO_PROCESSES)
        return rtos_err_badProcessId;

    /* The number of runtime tasks is constraint by compile time configuration. */
    if(pIData->noTasks >= RTOS_MAX_NO_TASKS  &&  idEvent != EVENT_ID_INIT_TASK)
        return rtos_err_tooManyTasksRegistered;

    /* The event's field noTasks is of smaller size. */
    if(idEvent != EVENT_ID_INIT_TASK
       &&  getEventByIdx(idEvent)->noTasks >= UINT_T_MAX(((rtos_eventDesc_t*)NULL)->noTasks)
      )
    {
        return rtos_err_tooManyTasksRegistered;
    }

    /* Task function not set. */
    if(addrTaskFct == 0)
        return rtos_err_badTaskFunction;

    /* Check execution budget: There's an upper boundary for user tasks and OS task cannot
       have deadline monitoring at all. */
    if(tiTaskMaxInUs > RTOS_TI_DEADLINE_MAX_IN_US  ||  PID == 0  &&  tiTaskMaxInUs > 0)
        return rtos_err_taskBudgetTooBig;

    /* We make the distinction between normal runtime tasks and initialization tasks. */
    /// @todo Afterwards, it looks like a strange design decision to make this distinction.
    // Why not having a block of consecutive tasks in the array of all tasks? The required
    // sorting algorithms are anyway in place. We would reuse same code and could easily
    // offer an unbounded number of initialization tasks per process. They were associated
    // with a virtual event, meaning the system initialization.
    /// @todo See other TODO, which proposes more or less the same for process related idle
    // tasks
    if(idEvent == EVENT_ID_INIT_TASK)
    {
        /* An initialization task must not be configured repeatedly for one and the same
           process. */
        const unsigned int idxP = PID;
        assert(idxP < sizeOfAry(pIData->initTaskCfgAry));
        if(pIData->initTaskCfgAry[idxP].addrTaskFct != 0)
            return rtos_err_initTaskRedefined;

        pIData->initTaskCfgAry[idxP].addrTaskFct = addrTaskFct;
        pIData->initTaskCfgAry[idxP].tiTaskMax = RTOS_TI_US2TICKS(tiTaskMaxInUs);
        pIData->initTaskCfgAry[idxP].PID = PID;
    }
    else
    {
        /* Add the new runtime task to the array. All tasks associated with an event need
           to form a consecutive list. We need to find the right location to insert the
           task and we need to consider an update of all events with refer to tasks with
           higher index. */
        rtos_eventDesc_t * const pEvent = getEventByID(idEvent);
        rtos_taskDesc_t *pNewTaskDesc;
        if(pEvent->taskAry == NULL)
        {
            /* First task of given event, we append a new sequence of tasks to the end of
               the task list so far. Done. */
            pEvent->taskAry = pNewTaskDesc = &pIData->taskCfgAry[pIData->noTasks];

            /* Associate the task with the specified event. */
            pEvent->noTasks = 1;
        }
        else
        {
            /* This is a further task for the event. We will have to shift the tasks in the
               task list to still have a consecutive sequence of tasks for the event. */
            pNewTaskDesc = (rtos_taskDesc_t*)pEvent->taskAry + pEvent->noTasks;

            /* The event's task sequence can be in the middle of the task list. So need to
               check if we have to move some rightmost list entries. */
            rtos_taskDesc_t *pTaskCfg = &pIData->taskCfgAry[pIData->noTasks];
            assert(pIData->noTasks >= 2  ||  pTaskCfg <= pNewTaskDesc);
            for(; pTaskCfg>pNewTaskDesc; --pTaskCfg)
                *pTaskCfg = *(pTaskCfg-1);

            /* Update the reference to the task sequence for all events, which still point
               to the shifted area of the task list. Note, that the events don't have a
               particular order with respect to the user specified index. (Instead, they
               are sorted by priority.) */
            unsigned int idxEv;
            for(idxEv=0; idxEv<pIData->noEvents; ++idxEv)
            {
                rtos_eventDesc_t * const pCheckedEvent = getEventByIdx(idxEv);
                if(pCheckedEvent != pEvent  &&  pCheckedEvent->taskAry >= pNewTaskDesc)
                    ++ pCheckedEvent->taskAry;
            }

            /* Associate the task with the specified event. */
            ++ pEvent->noTasks;
            assert(pEvent->noTasks > 0);
        }

        /* Fill the new task descriptor. */
        pNewTaskDesc->addrTaskFct = addrTaskFct;
        pNewTaskDesc->tiTaskMax = RTOS_TI_US2TICKS(tiTaskMaxInUs);
        pNewTaskDesc->PID = PID;
        ++ pIData->noTasks;
        assert(pIData->noTasks > 0);
    }

    return rtos_err_noError;

} /* End of registerTask */




/**
 * Trigger an event to activate all associated tasks.\n
 *   This function implements the operation. It is called from two API functions, one for
 * OS code and one for user code. See rtos_osTriggerEvent() and rtos_triggerEvent() for
 * more details.
 *   @return
 * Get \a true if event could be triggered, \a false otherwise.
 *   @param pEvent
 * The event to trigger by reference.
 *   @param hasTaskParam
 * Individual task parameter value for each activation of the tasks of thes event are not
 * always used. They are not used for regular, timer triggered events. However the code in
 * this function is shared between timer events and others. Specify \a true if \a taskParam
 * should be adopted by the event and \a false if it should be ignored.\n
 *   Only use Boolean literals but no Boolean expression, when calling this function: It is
 * an inline implementation. The entire code for supporting \a taskParam will be discarded
 * at compile time if the Boolean literal \a false is passed in and at least the decision
 * logic is discarded if it is a \a true.
 *   @param taskParam
 * This is the value of the variable argument for all the associated task function, when
 * they will be called later.
 *   @param isInterrupt
 * This function submits an immediate call of the scheduler if an event of accordingly high
 * priority is triggered. However, this call is postponed if we are currently still inside
 * an interrupt. This flag tells about.\n
 *   Note, this is an inline function. The complete is-interrupt decision code will be
 * discarded if a Boolean literal can be passed in - as it is for the call from the timer
 * ISR and the user task API. Only the OS API, which is shared between ISRs and OS tasks
 * will really contain the run-time decision code.
 */
static ALWAYS_INLINE bool osTriggerEvent( rtos_eventDesc_t * const pEvent
                                        , const bool hasTaskParam
                                        , uintptr_t taskParam
                                        , const bool isInterrupt
                                        )
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    bool success;

    /* If the function is called from an ISR then we need to use enter/leaveCriticalSection
       to create the critical section. This makes the function available to preemptable and
       non-preemptable ISRs. When called from a task it would be sufficient to
       unconditionally suspend and resume interrupt processing. (If a task has suspended
       the interrupts and then calls this function, which temporarily enables all
       interrupts then it'll surely be a design error in the logic of the calling task.)\n
         Generally using enter/leaveCriticalSection is never wrong but means useless
       overhead for calls from preemptable ISRs or tasks. The current construct of using
       one and the same inline implementation at all the different calling situations
       cannot avoid the useless overhead. We have a trade-off between avoidance of
       undesired code duplication and of useless overhead in all calling situations. */
    const uint32_t stateIrqAtEntry = rtos_osEnterCriticalSection();
    if(pEvent->state == evState_idle)
    {
        /* Operation successful. Event can be triggered. */
        pEvent->state = evState_triggered;
        success = true;
        
        /* Set the task function argument for this activation. (And for all future
           activations of a regular, time triggered event if such an event should be
           addressed from service rtos_triggerEvent().) */
        if(hasTaskParam)
            pEvent->taskParam = taskParam;
        
        /* Setting an event means a possible context switch to another task. It depends on
           priority and interrupt state. If so, we need to run the scheduler.
             It is not necessary to run the scheduler if the triggered event has a priority
           equal to or lower than the priority of the currently processed event. In this
           case the scheduler would anyway not change the current task right now.
             The scheduler must not be called if this function is called from inside an
           ISR. ISRs will call the function a bit later, when the interrupt context is
           cleared and only if they serve the root level interrupt (i.e. not from a nested
           interrupt). In this case calling rtos_osProcessTriggeredEvents() is postponed and
           done from the assembly code (IVOR #4 handler) but not yet here. The global flag
           pIData->pNextEventToSchedule is set to command this. */
        if(pEvent->priority > pIData->currentPrio)
        {
            if(isInterrupt)
            {
                /* Postpone the scheduler invocation till the end of the interrupt
                   handler. This is indicated by a global pointer, which has an initial
                   value that means "no pending event".
                     The next scheduler invocation will start with serving this event. We
                   must not move it towards less prior events - ISRs could trigger several
                   events and the scheduler needs to start with the one of highest
                   priority. The array of events is sorted in order of decreasing priority,
                   therefore a simple comparison is sufficient. */
                if(pEvent < pIData->pNextEventToSchedule)
                    pIData->pNextEventToSchedule = pEvent;
            }
            else
            {
                /* We will get here only if the function is called from a task (OS or user
                   through system call) */
                
                /* The recursive call of the scheduler is immediately done. We return here
                   only after a couple of other task executions.
                     Note, the critical section, we are currently in, will be left by the
                   recursively invoked scheduler as soon as it finds a task to be launched.
                   However, it'll return in a new critical section - which is the one we
                   leave at the end of this function. */
                rtos_osProcessTriggeredEvents(pEvent);
            }
        }
        else
        {
            /* Two possibilities to get here:
                 - The event's priority is in the scope of the currently operating scheduler.
               No need to immediately start a recursive scheduler or to postpone this start.
                 - The event has a priority, which is lower than the current one but still
               higher than the base priority of the currently processed event. This situation
               occurs if the current priority had been raised by means of the PCP API.
               Scheduling of the triggered event is postponed till the PCP API lowers the
               priority again. There's no simple way to store the information whether/which
               event to serve when PCP will later lower the priority:
                 "Whether" depends on the not yet known information how far PCP will be asked
               to lower the priority.
                 "Which" would require a recursive data storage. A normal, preempting
               scheduler could launch tasks, which in turn raise their priority by PCP.
                 Therefore, we need to dynamically find out later as part of the PCP
               priority lowering operation. Nothing to store here. */
        }
    }
    else
    {
        /* Processing of event has not completed yet, associated tasks have not
           all terminated yet. */

        /* Counting the loss events requires a critical section. The loss counter can be
           written concurrently from another task invoking rtos_osTriggerEvent() or by the
           timer controlled scheduler. */
        const unsigned int noActivationLoss = pEvent->noActivationLoss + 1;
        if(noActivationLoss > 0)
            pEvent->noActivationLoss = noActivationLoss;

        success = false;
    }
    rtos_osLeaveCriticalSection(stateIrqAtEntry);
    
    return success;

} /* End of osTriggerEvent */




/**
 * Process the conditions that trigger events. The events are checked for becoming
 * meanwhile due and the associated tasks are made ready in case by setting the according
 * state in the event object. However, no tasks are already started in this function.
 */
static inline void checkEventDue(void)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    
    rtos_eventDesc_t *pEvent = getEventByIdx(0);

    /* We iterate the events in order for decreasing priority. */
    const rtos_eventDesc_t * const pEndEvent = pIData->pEndEvent;
    while(pEvent < pEndEvent)
    {
        if(pEvent->tiCycleInMs > 0)
        {
            if((signed int)(pEvent->tiDue - pIData->tiOs) <= 0)
            {
                /* Trigger the event or count an activation loss error. */
                osTriggerEvent(pEvent
                              , /* hasTaskParam */ false
                              , /* taskParam */ 0 /* value doesn't care */
                              , /* isInterrupt */ true
                              );

                /* Adjust the due time.
                     Note, we could queue task activations for cyclic tasks by not adjusting
                   the due time. Some limitation code would be required to make this safe. */
                pEvent->tiDue += pEvent->tiCycleInMs;

            } /* End if(Event is due?) */
        }
        else
        {
            /* Non regular events: nothing to be done. These events are triggered only by
               explicit software call of rtos_triggerEvent(). */

        } /* End if(Timer or application software activated task?) */

        /* Proceed with next event. */
        ++ pEvent;

    } /* End While(All configured events) */

} /* End of checkEventDue */



/**
 * The OS default timer handler. In function rtos_osInitKernel(), it is associated with the
 * PIT0 interrupt. You must not call this function yourself. The routine is invoked once
 * every #RTOS_CLOCK_TICK_IN_MS_CORE_0 (_1, _2) Milliseconds and triggers most of the
 * scheduler decisions. The application code is expected to run mainly in regular tasks and
 * these are activated by this routine when they become due. All the rest is done by the
 * interrupt controller INTC.
 *   @remark
 * The INTC priority at which this function is executed is configured as
 * #RTOS_KERNEL_IRQ_PRIORITY_CORE_0 (or as #RTOS_KERNEL_IRQ_PRIORITY_CORE_1, or as
 * #RTOS_KERNEL_IRQ_PRIORITY_CORE_2, if the RTOS is running on core 1 or 2, respectively).
 */
static void onOsTimerTick(void)
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    
    /* Update the system time. */
    pIData->tiOs += pIData->tiOsStep;

    /* The scheduler is most simple; the only condition to make a task ready is the next
       periodic due time. The task activation is left to the pseudo-software-interrupt,
       which is raised either by true interrupts (if they use setEvent) or by system calls,
       which may cause a task switch. */
    checkEventDue();

    /* RM 51.4.11, p. 2738f: Acknowledge the timer interrupt in the causing HW device. */
    const unsigned int idxTimer = rtos_idxRtosTimerAry[rtos_osGetIdxCore()];
    PIT->TIMER[idxTimer].TFLG = PIT_TFLG_TIF(1);

} /* End of onOsTimerTick */



/**
 * Processing a triggered event means to execute all associated tasks. If the scheduler
 * finds an event to be processed as next one, then it'll call this function to run the
 * tasks.
 *   @param pEvent
 * The event by reference, whose tasks are to be executed one after another.
 */
static inline void launchAllTasksOfEvent(const rtos_eventDesc_t * const pEvent)
{
    const rtos_taskDesc_t *pTaskConfig = &pEvent->taskAry[0];
    unsigned int u = (unsigned int)pEvent->noTasks;
    const uintptr_t taskParam = pEvent->taskParam;
    while(u-- > 0)
    {
        if(pTaskConfig->PID > 0)
            rtos_osRunTask(pTaskConfig, taskParam);
        else
            ((void (*)(uintptr_t))pTaskConfig->addrTaskFct)(taskParam);

        ++ pTaskConfig;

    } /* End while(Run all tasks associated with the event) */

} /* End of launchAllTasksOfEvent */



/**
 * Initialize a timer and associate its wrap-around interrupt with the main clock tick
 * function of the RTOS, onOsTimerTick(). The wrap-around cycle frequency of the timer
 * determines the time resolution of the RTOS operations.\n
 *   The wrap-around cycle time is a compile-time configuration item, see
 * #RTOS_CLOCK_TICK_IN_MS_CORE_0 (_1, _2) for more details.
 */
static void initRTOSClockTick(void)
{
    _Static_assert( RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 0
                    ||  GET_CORE_VALUE(RTOS_CLOCK_TICK_IN_MS, 0) >= 1 
                        &&  GET_CORE_VALUE(RTOS_CLOCK_TICK_IN_MS, 0) <= 35791
                  , "RTOS clock tick configuration on core Z4A is out of range"
                  );
    _Static_assert( RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 0
                    ||  GET_CORE_VALUE(RTOS_CLOCK_TICK_IN_MS, 1) >= 1 
                        &&  GET_CORE_VALUE(RTOS_CLOCK_TICK_IN_MS, 1) <= 35791
                  , "RTOS clock tick configuration on core Z4B is out of range"
                  );
    _Static_assert( RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 0
                    ||  GET_CORE_VALUE(RTOS_CLOCK_TICK_IN_MS, 2) >= 1 
                        &&  GET_CORE_VALUE(RTOS_CLOCK_TICK_IN_MS, 2) <= 35791
                  , "RTOS clock tick configuration on core Z2 is out of range"
                  );
    _Static_assert( RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 0
                    ||  GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 0) >= 1
                        && GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 0) <= 15
                  , "Bad configuration of PIT timers as clock source for safe-RTOS"
                  );
    _Static_assert( RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 0
                    ||  GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 1) >= 1
                        && GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 1) <= 15
                  , "Bad configuration of PIT timers as clock source for safe-RTOS"
                  );
    _Static_assert( RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 0 
                    ||  GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 2) >= 1
                        && GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 2) <= 15
                  , "Bad configuration of PIT timers as clock source for safe-RTOS"
                  );
    _Static_assert( RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 0  ||  RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 0
                    ||  GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 0) 
                        != GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 1)
                  , "If safe-RTOS runs on different cores then they need to have different"
                    " clock sources"
                  );
    _Static_assert( RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 0  ||  RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 0
                    ||  GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 0) 
                        != GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 2)
                  , "If safe-RTOS runs on different cores then they need to have different"
                    " clock sources"
                  );
    _Static_assert( RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 0  ||  RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 0
                    ||  GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 1)
                        != GET_CORE_VALUE(RTOS_IDX_OF_PID_TIMER, 2)
                  , "If safe-RTOS runs on different cores then they need to have different"
                    " clock sources"
                  );

    /* Note, time PIT0 must not be used. It is occupied by the DMA channel as trigger for
       serial output. */

    /* Disable timers during configuration. RM, 51.4.1, p. 2731. */
    PIT->MCR = PIT_MCR_MDIS(1) | PIT_MCR_FRZ(1);

    /* Install the interrupt service routine for the configured cyclic timer PITn
       (depending on calling core). The interrupt goes to the calling core. It drives the OS
       scheduler for cyclic task activation. */
    const unsigned int processorID = rtos_osGetIdxCore()
                     , idxTimerChn = rtos_idxRtosTimerAry[processorID]
                     , vectorNum = PIT_Ch0_IRQn + idxTimerChn;
    assert(vectorNum >= PIT_Ch1_IRQn  &&  vectorNum <= PIT_Ch15_IRQn);
    rtos_osRegisterInterruptHandler( &onOsTimerTick
                                   , processorID
                                   , vectorNum
                                   , GET_CORE_VALUE(RTOS_KERNEL_IRQ_PRIORITY, processorID)
                                   , /* isPremptable */ true
                                   );

    /* Peripheral clock has been initialized to 40 MHz. To get a 1ms interrupt tick we
       need to count till 40000. We configure an interrupt rate of
       RTOS_CLOCK_TICK_IN_MS_CORE_0 (_1, _2) Milliseconds.
         -1: See RM, 51.6 */
/// @todo Here, we need to have a double-check with CCL
    PIT->TIMER[idxTimerChn].LDVAL = (unsigned int)
                                    (40000u * GET_CORE_VALUE( RTOS_CLOCK_TICK_IN_MS
                                                            , processorID
                                                            )
                                    ) - 1u;

    /* Enable timer operation. Note, this doesn't release the scheduler yet; the step size
       is still zero and the system time doesn't advance despite of the starting timer
       interrupt.
         PIT_MCR_FRZ: For this multi-core MCU it is not so easy to decide whether or not to
       let the timers be stopped on debugger entry: Any stopped core will halt the timers,
       regardless whether that core is related to the timer or not (and how should the
       debugger know...). Both possibilities can be annoying or advantageous, depending on
       the situation. */
    PIT->MCR = PIT_MCR_MDIS(0) | PIT_MCR_FRZ(1);
    
    /* Clear possibly pending interrupt flags. */
    PIT->TIMER[idxTimerChn].TFLG = PIT_TFLG_TIF(1);
    
    /* Enable interrupts by the timers and start them. See RM 51.4.10. */
    PIT->TIMER[idxTimerChn].TCTRL = PIT_TCTRL_CHN(0) | PIT_TCTRL_TIE(1) | PIT_TCTRL_TEN(1);
    
} /* End of initRTOSClockTick */




/**
 * Creation of an event. The event can be cyclically triggering or software triggered.
 * An event is needed to activate a user task. Therefore, any reasonable application will
 * create at least one event.\n
 *   This function is repeatedly called by the application code for each required event.
 * All calls of this function need to be done prior to the start of the kernel using
 * rtos_osInitKernel().\n
 *   @return
 * \a rtos_err_noError (zero) if the event could be created. The maximum number of events
 * is limited to #RTOS_MAX_NO_EVENTS by hardware constraints. If the event cannot be
 * created due to this constraint or if the event descriptor contains invalid data then
 * then the function returns a non zero value from enumeration \a rtos_errorCode_t.\n
 *   An assertion in the calling code is considered appropriate to handle the error because
 * it'll always be a static configuration error.
 *   @param pEventId
 * All events are identified by a positive integer. Normally this ID is returned by
 * reference in * \a pEventId. If the event cannot be created then #RTOS_INVALID_EVENT_ID
 * is returned in * \a pEventId.\n
 *   Note, it is guaranteed to the caller that the returned ID is not an arbitrary,
 * meaningless number. Instead, the ID is counted from zero in order of creating events.
 * The first call of this function will return 0, the second 1, and so on. This simplifies
 * ID handling in the application code, constants can mostly be applied as the IDs are
 * effectively known at compile time.
 *   @param tiCycleInMs
 * The period time for regularly triggering events in ms.\n
 *   The permitted range is 0..2^30-1. 0 means no regular, timer controlled trigger and the
 * event is only enabled for software trigger using rtos_triggerEvent() (permitted for
 * interrupts or other tasks).
 *   @param tiFirstActivationInMs
 * The first trigger of the event in ms after start of kernel. The permitted range is
 * 0..2^30-1.\n
 *   Note, this setting is useless if a cycle time zero in \a tiCycleInMs specifies a non
 * regular event. \a tiFirstActivationInMs needs to be zero in this case, too.
 *   @param priority
 * The priority of the event in the range 1..UINT_MAX. Different events can share the same
 * priority. The priority of an event is the priority of all associated tasks at the same
 * time. The execution of tasks, which share the priority will be serialized when they are
 * activated at same time or with overlap.\n
 *   Note the safety constraint that task priorities above #RTOS_MAX_LOCKABLE_TASK_PRIORITY
 * are available only to events, which solely have tasks associated that belong to the
 * process with highest process ID in use.\n
 *   Note, the order in which events are created can affect the priority in a certain
 * sense. If two events are created with same priority and when they at runtime become due
 * at the same OS time tick then the earlier created event will trigger its associated user
 * tasks before the later ceated event.
 *   @param minPIDToTriggerThisEvent
 * An event can be triggered by user code, using rtos_triggerEvent(). However, tasks
 * belonging to less privileged processes must not generally have permission to trigger
 * events that may activate tasks of higher privileged processes. Since an event is not
 * process related, we make the minimum process ID, which is required to trigger this
 * event, an explicitly configured property of the event.\n
 *   Only tasks belonging to a process with PID >= \a minPIDToTriggerThisEvent are
 * permitted to trigger this event.\n
 *   The range of \a minPIDToTriggerThisEvent is 0 ... (#RTOS_NO_PROCESSES+1). 0 and 1 both
 * mean, all processes may trigger the event, (#RTOS_NO_PROCESSES+1) means only OS code can
 * trigger the event. (#RTOS_NO_PROCESSES+1) is available as
 * #RTOS_EVENT_NOT_USER_TRIGGERABLE, too.
 *   @param taskParam
 * The event is used to trigger its associated tasks. An argument can be passed to the task
 * functions, when they are called later. The initial value of this argument is set now.\n
 *   Actually, the relevance of this initial value is little. It'll be used mainly for
 * regular, time triggered tasks, but for these tasks, the task parameter will mostly (not
 * always) be meaningless and event tasks will receive a specific argument, which is
 * defined when triggering the event they are associated with. See rtos_triggerEvent() for
 * more details.
 *   @remark
 * Never call this function after the call of rtos_osInitKernel()!
 *   @remark
 * This function must be called by trusted code in supervisor mode only.
 */
rtos_errorCode_t rtos_osCreateEvent( unsigned int *pEventId
                                   , unsigned int tiCycleInMs
                                   , unsigned int tiFirstActivationInMs
                                   , unsigned int priority
                                   , unsigned int minPIDToTriggerThisEvent
                                   , uintptr_t taskParam
                                   )
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    *pEventId = RTOS_INVALID_EVENT_ID;

    /* The number of events is constraint in order to let our mapping tables not grow more
       thatreasonable */
    if(pIData->noEvents >= RTOS_MAX_NO_EVENTS)
        return rtos_err_tooManyEventsCreated;

    if(priority == 0  ||  priority > RTOS_MAX_TASK_PRIORITY)
        return rtos_err_invalidEventPrio;

    /* Check settings for non regularly activated tasks. */
    if(tiCycleInMs == 0)
    {
        /* Avoid a useless and misleading setting. */
        if(tiFirstActivationInMs != 0)
            return rtos_err_badEventTiming;
    }

    /* The full 32 Bit range is avoided for time designations in order to have safe and
       unambiguous before and after decisions in a cyclic time model.
         Furthermore, no task must have the initial due time of 0xffffffff in order to not
       invalidate the startup logic of the scheduler (see rtos_osInitKernel()). */
    else if(((tiCycleInMs | tiFirstActivationInMs) & 0xc0000000) != 0)
        return rtos_err_badEventTiming;

    /* Is the PID constraint plausible? */
    _Static_assert( RTOS_NO_PROCESSES >= 0  &&  RTOS_NO_PROCESSES <= 254
                  , "Possible overflow of uint8_t pNewEvent->minPIDForTrigger"
                  );
    if(minPIDToTriggerThisEvent > RTOS_NO_PROCESSES+1)
        return rtos_err_eventNotTriggerable;

    /* Insert the new event into the array and initialize the data structure. The position
       to insert is such that the events appear in order of decreasing priority. */
    unsigned int idxNewEv, v;
    for(idxNewEv=0; idxNewEv<pIData->noEvents; ++idxNewEv)
    {
        if(getEventByIdx(idxNewEv)->priority < priority)
            break;
    }

    for(v=pIData->noEvents; v>idxNewEv; --v)
        *getEventByIdx(v) = *getEventByIdx(v-1);

    rtos_eventDesc_t *pNewEvent = getEventByIdx(idxNewEv);
    pNewEvent->tiCycleInMs = tiCycleInMs;
    pNewEvent->tiDue = tiFirstActivationInMs;
    pNewEvent->priority = priority;
    pNewEvent->minPIDForTrigger = minPIDToTriggerThisEvent;
    pNewEvent->noActivationLoss = 0;
    pNewEvent->taskAry = NULL;
    pNewEvent->noTasks = 0;
    pNewEvent->taskParam = taskParam;
    pNewEvent->pNextScheduledEvent = NULL;

    const unsigned int idNewEv = pIData->noEvents++;
    assert(pIData->noEvents > 0);

    /* Update the mapping of (already issued, publically known) event IDs onto the (now
       modified) internal arry index. */
    pIData->mapEventIDToPtr[idNewEv] = getEventByIdx(idxNewEv);
    for(v=0; v<idNewEv; ++v)
        if(pIData->mapEventIDToPtr[v] >= getEventByIdx(idxNewEv))
            ++ pIData->mapEventIDToPtr[v];

    /* Install the guard element at the end of the list. Essential is a priority value of
       zero, i.e. below any true, scheduled task. */
    /// @todo Effectively, this object can be considered the descriptor of the idle task.
    // At other location we wonder, whether we should offer idle tasks which are owned by
    // the different processes. It would be straightforward to use this object, and
    // particularly its field taskAry to implement this. Instead of returning from the
    // initKernel we would start a first scheduler instance. An ugly detail: Without
    // modification, the normal scheduling would clear the state "triggered" after
    // execution of all associated tasks. Is it worth to let the normal scheduling suffer
    // from an additional run-time condition just to make the idle concept work in the
    // sketched way?
    _Static_assert( RTOS_EVENT_NOT_USER_TRIGGERABLE <= UINT_T_MAX(pNewEvent->minPIDForTrigger)
                  , "Integer overflow"
                  );
    *getEventByIdx(pIData->noEvents) = 
                (rtos_eventDesc_t){ .tiCycleInMs = 0
                                    , .tiDue = 0
                                    , .priority = 0
                                    , .minPIDForTrigger = RTOS_EVENT_NOT_USER_TRIGGERABLE
                                    , .noActivationLoss = 0
                                    , .taskAry = NULL
                                    , .noTasks = 0
                                    , .taskParam = 0
                                    , .pNextScheduledEvent = NULL
                                  };
  
#ifdef DEBUG
    for(v=1; v<=pIData->noEvents; ++v)
        if(getEventByIdx(v)->priority > getEventByIdx(v-1)->priority)
            return rtos_err_invalidEventPrio; /* Actually an internal implementation error */
#endif
    /* Assign the next available array index as publically known event ID. */
    *pEventId = idNewEv;

    return rtos_err_noError;

} /* End of rtos_osCreateEvent */



/**
 * Registration of a process initialization task. This function is typically repeatedly
 * called by the operating system initialization code as often as there are processes,
 * which need initialization.\n
 *   Initialization functions are particularly useful for the user processes. They allow
 * having user provided code, that is run prior to the start of the scheduler, in a still
 * race condition free environment but already with full protection against runtime
 * failures.\n
 *   All calls of this function need to be done prior to the start of the kernel using
 * rtos_osInitKernel().
 *   @return
 * \a rtos_err_noError (zero) if the task could be registered. The maximum number of
 * initialization tasks is one per process and one for the OS. If the limit is exceeded or
 * if the task specification is invalid then the function returns a non zero value from
 * enumeration \a rtos_errorCode_t.\n
 *   An assertion in the calling code is considered appropriate to handle the error because
 * it'll always be a static configuration error.
 *   @param initTaskFct
 * The initialization function, which is run once in process \a PID.\n
 *   The function gets the ID of the process it belongs to as argument.\n
 *   The function returns a signed value. If the value is negative then it is considered an
 * error, which is counted as error #RTOS_ERR_PRC_USER_ABORT in the owning
 * process and the scheduler will not start up.
 *   @param PID
 *   The process the task belongs to by identifier. We have a fixed, limited number of four
 * processes (#RTOS_NO_PROCESSES) plus the kernel process, which has ID 0. The range of
 * process IDs to be used here is 0 .. #RTOS_NO_PROCESSES.\n
 *   At kernel initialization time, the registered user process initialization functions
 * will be called in the order of rising PID, followed by the registered kernel process
 * initialization function.
 *   @param tiTaskMaxInUs
 * Time budget for the function execution in Microseconds. The budget relates to
 * deadline monitoring, i.e. it is a world time budget, not an execution time budget.\n
 *   Deadline monitoring is supported up to a maximum execution time of
 * #RTOS_TI_DEADLINE_MAX_IN_US Microseconds.\n
 *   A value of zero means that deadline monitoring is disabled for the run of the
 * initialization function.\n
 *   There's no deadline monitoring for OS tasks. If \a PID is zero then \a
 * tiTaskMaxInUS meeds to be zero, too.
 *   @remark
 * Never call this function after the call of rtos_osInitKernel()!
 *   @remark
 * This function must be called by trusted code in supervisor mode only.
 */
rtos_errorCode_t rtos_osRegisterInitTask( int32_t (*initTaskFct)(uint32_t PID)
                                        , unsigned int PID
                                        , unsigned int tiTaskMaxInUs
                                        )
{
    return registerTask(EVENT_ID_INIT_TASK, (uintptr_t)initTaskFct, PID, tiTaskMaxInUs);

} /* End of rtos_osRegisterInitTask */




/**
 * Registration of an event triggered user mode task. Normal, event activated tasks can be
 * registered for later execution. This function is repeatedly called by the application
 * code as often as user mode tasks are required.\n
 *   All calls of this function need to be done prior to the start of the kernel using
 * rtos_osInitKernel().
 *   @return
 * \a rtos_err_noError (zero) if the task could be registered. The maximum number of
 * tasks is limited to #RTOS_MAX_NO_TASKS (regardless, how they are distributed among
 * processes). If the limit is exceeded or if the task specification is invalid then the
 * function returns a non zero value from enumeration \a rtos_errorCode_t.\n
 *   An assertion in the calling code is considered appropriate to handle the error because
 * it'll always be a static configuration error.
 *   @param idEvent
 * The task is activated by an event. This call associates the registered task with an
 * already created event. See rtos_osCreateEvent().\n
 *   The order of registration of several tasks (both, OS and user mode) with one and the
 * same event matters. The tasks will be acivated in order of registration whenever the
 * event becomes due or is triggered by software.
 *   @param userModeTaskFct
 * The task function, which is run in process \a PID every time, the event \a idEvent
 * triggers.\n
 *   The function gets the ID of the process it belongs to as argument.\n
 *   The function returns a signed value. If the value is negative then it is considered an
 * error, which is counted as error #RTOS_ERR_PRC_USER_ABORT in the owning
 * process. (And after a number of errors a supervisory task could force a shutdown of the
 * process).
 *   @param PID
 *   The process the task belongs to by identifier. We have a fixed, limited number of four
 * processes (#RTOS_NO_PROCESSES). The range of process IDs to be used here is 1 ..
 * #RTOS_NO_PROCESSES.\n
 *   @param tiTaskMaxInUs
 * Time budget for the task in Microseconds. This budget is granted for each activation of
 * the task, i.e. each run of \a userModeTaskFct(). The budget relates to deadline
 * monitoring, i.e. it is a world time budget, not an execution time budget.\n
 *   Deadline monitoring is supported up to a maximum execution time of
 * #RTOS_TI_DEADLINE_MAX_IN_US Microseconds.\n
 *   A value of zero means that deadline monitoring is disabled for the task.\n
 *   @remark
 * Never call this function after the call of rtos_osInitKernel()!
 *   @remark
 * This function must be called by trusted code in supervisor mode only.
 */
rtos_errorCode_t rtos_osRegisterUserTask( unsigned int idEvent
                                        , int32_t (*userModeTaskFct)( uint32_t PID
                                                                    , uintptr_t taskParam
                                                                    )
                                        , unsigned int PID
                                        , unsigned int tiTaskMaxInUs
                                        )
{
    /* OS task functions have another signature and should be registered with the other
       function rtos_osRegisterOSTask(). */
    if(PID == 0)
        return rtos_err_badProcessId;

    return registerTask(idEvent, (uintptr_t)userModeTaskFct, PID, tiTaskMaxInUs);

} /* End of rtos_osRegisterUserTask */



/**
 * Registration of an event triggered operating system task. Event activated tasks can be
 * registered for later execution. This function is repeatedly called by the application
 * code as often as operating system tasks are required.\n
 *   All calls of this function need to be done prior to the start of the kernel using
 * rtos_osInitKernel().
 *   @return
 * \a rtos_err_noError (zero) if the task could be registered. The maximum number of
 * tasks is limited to #RTOS_MAX_NO_TASKS (regardless, how they are distributed among
 * processes). If the limit is exceeded or if the task specification is invalid then the
 * function returns a non zero value from enumeration \a rtos_errorCode_t.\n
 *   An assertion in the calling code is considered appropriate to handle the error because
 * it'll always be a static configuration error.
 *   @param idEvent
 * The task is activated by an event. This call associates the registered task with an
 * already created event. See rtos_osCreateEvent().\n
 *   The order of registration of several tasks (both, OS and user mode) with one and the
 * same event matters. The tasks will be acivated in order of registration whenever the
 * event becomes due or is triggered by software.
 *   @param osTaskFct
 * The task function, which is run in the OS context every time, the event \a idEvent
 * triggers.
 *   @remark
 * Never call this function after the call of rtos_osInitKernel()!
 *   @remark
 * This function must be called by trusted code in supervisor mode only.
 */
rtos_errorCode_t rtos_osRegisterOSTask( unsigned int idEvent
                                      , void (*osTaskFct)(uintptr_t taskParam)
                                      )
{
    return registerTask(idEvent, (uintptr_t)osTaskFct, /* PID */ 0, /* tiTaskMaxInUs */ 0);

} /* End of rtos_osRegisterOSTask */



/**
 * Initialization and start of the RTOS kernel.\n
 *   The function initializes a hardware device to produce a regular clock tick and
 * connects the OS schedule function onOsTimerTick() with the interrupt raised by this
 * timer device. After return, the RTOS is running with a regular clock tick for scheduling
 * the tasks. Period time is #RTOS_CLOCK_TICK_IN_MS_CORE_0 (_1, _2) Milliseconds.\n
 *   The function can be called before or after the External Interrupts are enabled at the
 * CPU (see rtos_osResumeAllInterrupts()). Normal behavior is however, no to resume the
 * interrupt processing before and let this be done by rtos_osInitKernel().
 *   @return
 * \a rtos_err_noError (zero) if the scheduler could be started. The function returns a non
 * zero value from enumeration \a rtos_errorCode_t if a configuration error is detected.
 * The software must not start up in this case. Since it is only about static
 * configuration, the returned error may be appropriately handled by an assertion.
 *   @remark
 * The RTOS kernel applies the Periodic Interrupt Timer 0 (PIT0) as clock source. This
 * timer is reserved to the RTOS and must not be used at all by some other code.
 *   @remark
 * All application tasks need to be registered before invoking this function, see
 * rtos_osRegisterInitTask(), rtos_osRegisterUserTask() and rtos_osRegisterOSTask().
 *   @remark
 * This function must be called from the OS context only. The call of this function will
 * end the operating system initialization phase.
 */
rtos_errorCode_t rtos_osInitKernel(void)
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    /* If this assertion fires then you
       - should double-check if you can redefine your task priorities such that they use
         consecutive numbers, 1, 2, 3 ...
       - can decide to change the condition of the assertion if you really need so many
         different task priorities
       - should decide if you change the implementation of the mapping from task priority
         to events having that priority. So far we chose the most time efficient technique,
         a direct lookup table, but any other technique would be fine, too. */
    _Static_assert( RTOS_MAX_TASK_PRIORITY <= 64
                  , "The used range of task priorities has been chosen such large that the"
                    " implementation becomes quite inefficient in terms of memory usage"
                  );
                  
    /* The C code has an interface with the assembler code. It is used to exchange process
       and task related information. The interface is modeled twice, once as structs for C
       code and once as set of preprocessor macros, which hold size of data structures and
       offsets of fields. Here, we have macros, which support double-checking the
       equivalence of both definitions. The compiler will abort the compilation if there is
       a static inconsistency. A few more conditions require run-time checking. */
    assert(RTOS_CONSTRAINTS_INTERFACE_C_AS_PCP);
    _Static_assert( RTOS_STATIC_CONSTRAINTS_INTERFACE_C_AS_PCP
                  , "Interface check C to assembly failed for module"
                    " rtos_priorityCeilingProtocol.S"
                  );

    /* Initialization of system all module: For now it's just used to place some unit
       self-test code. */
    rtos_osInitSystemCalls();

    rtos_errorCode_t errCode = rtos_err_noError;

    /* The pointer pIData->pNextEventToSchedule is either unset or it points to the event of
       highest priority which has been triggered but which cannot be scheduled yet because
       we are still in an ISR. The value "unset" need to maintain the ordering of pointers,
       the higher the value the lesser the priority of an event it points to. NULL would
       not fulfill both condition and therefore require additional runtime code. We choose
       UINT_MAX as indication of "unset". */
    pIData->pNextEventToSchedule = (rtos_eventDesc_t*)(uintptr_t)-1;

    pIData->pEndEvent     =
    pIData->pCurrentEvent = getEventByIdx(pIData->noEvents);
    pIData->currentPrio = 0;

    /* The user must have registered at minimum one task and must have associated it with a
       event. */
    if(pIData->tiOsStep != 0)
        errCode = rtos_err_configurationOfRunningKernel;
    else if(pIData->noEvents == 0  ||  pIData->noTasks == 0)
        errCode = rtos_err_noEvOrTaskRegistered;

    /* Fill all process stacks with the empty-pattern, which is applied for computing the
       stack usage. */
    bool isProcessConfiguredAry[1+RTOS_NO_PROCESSES] = {[0 ... RTOS_NO_PROCESSES] = false};
    if(errCode == rtos_err_noError)
        errCode = rtos_osInitProcesses(isProcessConfiguredAry);

    unsigned int idxTask
               , maxPIDInUse = 0;
    /* Find the highest PID in use. */
    for(idxTask=0; idxTask<pIData->noTasks; ++idxTask)
        if(pIData->taskCfgAry[idxTask].PID > maxPIDInUse)
            maxPIDInUse = pIData->taskCfgAry[idxTask].PID;

    /* A task must not belong to an invalid configured process. This holds for init and for
       run time tasks. */
    if(errCode == rtos_err_noError)
    {
        unsigned int idxP;
        for(idxTask=0; idxTask<pIData->noTasks; ++idxTask)
        {
            assert(pIData->taskCfgAry[idxTask].PID < sizeOfAry(isProcessConfiguredAry));
            if(!isProcessConfiguredAry[pIData->taskCfgAry[idxTask].PID])
                errCode = rtos_err_taskBelongsToInvalidPrc;

        } /* For(All registered runtime tasks) */

        for(idxP=0; idxP<1+RTOS_NO_PROCESSES; ++idxP)
        {
            /* Note, the init task array is - different to the runtime task array
               pIData->taskCfgAry - ordered by PID. The field PID in the array entries are
               redundant. A runtime check is not appropriate as this had happened at
               registration time. We can place a simple assertion here. */
            if(pIData->initTaskCfgAry[idxP].addrTaskFct != 0)
            {
                assert(pIData->initTaskCfgAry[idxP].PID == idxP);
                if(!isProcessConfiguredAry[idxP])
                    errCode = rtos_err_taskBelongsToInvalidPrc;
            }
        } /* for(All possibly used processes) */
    }

    /* Now knowing, which is the process with highest privileges we can double-check the
       permissions granted for using the service rtos_runTask(). It must not be possible to
       run a task in the process with highest privileges. */
    if(errCode == rtos_err_noError)
    {
        unsigned int callingPID;
        for(callingPID=1; callingPID<=maxPIDInUse; ++callingPID)
            if(rtos_osCheckPermissionRunTask(callingPID, /* targetPID */ maxPIDInUse))
                errCode = rtos_err_runTaskBadPermission;
    }

    /* We could check if a process, an init task is registered for, has a least one runtime
       task. However, it is not harmful if not and there might be pathologic applications,
       which solely consist of I/O driver callbacks. */

    if(errCode == rtos_err_noError)
    {
        unsigned int idxEv;
        for(idxEv=0; idxEv<pIData->noEvents; ++idxEv)
        {
            const rtos_eventDesc_t * const pEvent = getEventByIdx(idxEv);
            const unsigned int noAssociatedTasks = (unsigned int)pEvent->noTasks;

            /* Check task configuration: Events without an associated task are useless and
               point to a configuration error. */
            if(noAssociatedTasks == 0)
                errCode = rtos_err_eventWithoutTask;

            /* If an event has a priority above #RTOS_MAX_LOCKABLE_TASK_PRIORITY then only
               those tasks can be associated, which belong to the process with highest PID
               in use or OS tasks. This is a safety constraint. */
            if(pEvent->priority > RTOS_MAX_LOCKABLE_TASK_PRIORITY)
            {
                for(idxTask=0; idxTask<noAssociatedTasks; ++idxTask)
                {
                    const unsigned int PID = pEvent->taskAry[idxTask].PID;
                    if(PID > 0  &&  PID != maxPIDInUse)
                        errCode = rtos_err_highPrioTaskInLowPrivPrc;
                }
            } /* End if(Unblockable priority is in use by event) */
        } /* for(All registered events) */
    }

    /* The scheduling of events of potentially same priority is supported by a link
       pointer, which points the scheduler to the next event to check after the event had
       been processed. This next event is either the first one in a group of events of same
       priority or the linear successor if this would be the event itself. */
    if(errCode == rtos_err_noError)
    {
        unsigned int idxEv, idxEvNextPrio;
        unsigned int lastPrio = sizeOfAry(pIData->mapPrioToEvent);
        for(idxEv=0; idxEv<=pIData->noEvents; ++idxEv)
        {
            rtos_eventDesc_t * const pEvent = getEventByIdx(idxEv);

            /* Is this event the first one of the group of next lower priority? */
            if(idxEv == 0  ||  pEvent->priority < lastPrio)
            {
                const uint32_t priority = pEvent->priority;
                idxEvNextPrio = idxEv;
                
                /* The first event in such a group is linked to the next one in order of
                   the list. */
                if(idxEv < pIData->noEvents)
                {
                    pEvent->pNextScheduledEvent = getEventByIdx(idxEv+1);
                    assert(priority > 0);
                }
                else
                {
                    pEvent->pNextScheduledEvent = NULL;
                    assert(priority == 0);
                }
                    
                /* Add an entry to the map from priority to event. Assertions are fine to
                   make the code safe - the according object properties have already been
                   validated when creating the event objects. */
                unsigned int idxMapEntry = lastPrio-1;
                do
                {
                    assert(idxMapEntry < sizeOfAry(pIData->mapPrioToEvent));
                    pIData->mapPrioToEvent[idxMapEntry] = pEvent;
                }
                while(idxMapEntry-- > priority);

                lastPrio = priority;
            }
            else
            {
                /* All further events in such a group are linked to the first event of the
                   group. */
                pEvent->pNextScheduledEvent = getEventByIdx(idxEvNextPrio);
            }
        } /* End for(All events) */
    } /* End if(No initialization error yet) */

    /* After checking the static configuration, we can enable the dynamic processes.
       Outline:
       - Disable all processes (which is their initial state). Once we enable the
         interrupts, the I/O drivers start working and they may invoke callbacks into the
         processes. The execution of these callbacks will be inhibited
       - Initialize the memory protection. This needs to be done before the very first user
         mode task function has the chance to become started. (The very first user mode task
         functions need to be the process initialization tasks.)
       - Disable the scheduler to trigger any events (which is its initial state).
         Triggering events would not cause any user tasks to execute (processes still
         disabled) but their due counters would already run and the configured startup
         conditions would not be met later when enabling the processes
       - Globally enable interrupt processing. I/O drivers and OS clock tick are running.
         This is a prerequisite for the deadline monitoring, which we want to have in place
         already for the init tasks
       - Sequentially execute all configured process initialization tasks. There are no
         crosswise race condition and nor with user tasks or I/O driver callbacks. Note,
         interrupts are already running and cause race conditions. Moreover, they could
         make use of rtos_osTriggerEvent() and if an OS task is associated with the
         triggered event then there would be race conditions with this OS task, too
       - Enable the processes and release the scheduler; scheduler, user tasks and I/O
         driver's callbacks start running */

    /* Arm the memory protection unit. The processes are shared between the cores and, as a
       consequence, one static MPU configuration is used to control the behavior of all
       three cores. The MPU initialization is called only for core 0. */
    if(errCode == rtos_err_noError  &&  rtos_osGetIdxCore() == RTOS_CORE_Z4A)
        rtos_osInitMPU();

    /* Stop the scheduler. It won't run although the RTOS clock starts spinning. We don't
       want to see a running user task during execution of the init tasks. */
    pIData->tiOs     = (unsigned long)-1;
    pIData->tiOsStep = 0;

    /* We can register the interrupt service routine for the scheduler timer tick. */
    if(errCode == rtos_err_noError)
        initRTOSClockTick();

    /* All processes are initialized by rtos_initProcesses() in stopped state: We don't want
       to see a callback from an I/O driver after resuming interrupt processing and while
       an init task is executed. Note, it doesn't really matter if interrupt processing was
       resumed already before. */
    if(errCode == rtos_err_noError)
        rtos_osResumeAllInterrupts();

    /* When we get here (and if we didn't see a configuration error) then all kernel
       interrupts are configured, interrupts occur and are processed, but no user tasks are
       activated nor will an I/O driver run a callback. We can safely start our process
       initialization tasks. */

    /* Run all process initialization in order of increasing PID. A process with higher
       privileges is initialized after another with less privileges. The higher privileged
       could override settings made by its predecessor.
         In this consideration and despite of its PID zero, the operating system process
       has the highest privileges. This requires a loop counter like 1, 2, ..., N, 0. */
    if(errCode == rtos_err_noError)
    {
        unsigned int idxP = 0;
        do
        {
#if RTOS_NO_PROCESSES > 0
            if(idxP < RTOS_NO_PROCESSES)
                ++ idxP;
            else
                idxP = 0;
#else
            /* No processes, just initialize the OS. idxP=0 is only loop cycle. */
#endif

            /* The specification of an initialization task is an option only. Check for
               NULL pointer. */
            if(pIData->initTaskCfgAry[idxP].addrTaskFct != 0)
            {
                if(isProcessConfiguredAry[idxP])
                {
                    /* Everything is alright. Run the initialization task. A negative
                       return value is defined to be an error. (This needs to be considered
                       by the implementation of the task.) */
                    int32_t resultInit;
                    if(pIData->initTaskCfgAry[idxP].PID == 0)
                    {
                        /* OS initialization function: It is a normal sub-function call; we
                           are here in the OS context. */
                        resultInit =
                            ((int32_t (*)(void))pIData->initTaskCfgAry[idxP].addrTaskFct)();
                    }
                    else
                    {
                        /* The initialization function of a process is run as a task in
                           that process, which involves full exception handling and
                           possible abort causes. */
                        resultInit = rtos_osRunInitTask(&pIData->initTaskCfgAry[idxP]);
                    }
                    if(resultInit < 0)
                        errCode = rtos_err_initTaskFailed;
                }
                else
                {
                    /* An initialization task must not be registered for a process, which
                       is not configured. This had been checked above and we can never get
                       here. */
                    assert(false);
                }
            } /* End if(Init task configured for process?) */
        }
        while(idxP != 0);  /* End for(All possible processes, OS as last one) */
        
    } /* End if(No error so far?) */
    
    /* After successfully completing all the initialization tasks, we can release the
       scheduler and the processes. We do this in a critical section in order to not
       endanger the specified relationship of initial task activations (specified in terms
       of task priority, period time and initial due time). */
    if(errCode == rtos_err_noError)
    {
        rtos_osSuspendAllInterrupts();

        /* Process state: Set to running (not zero) only if configuration generally okay. */
        unsigned int idxP;
        for(idxP=1; idxP<1+RTOS_NO_PROCESSES; ++idxP)
            if(isProcessConfiguredAry[idxP])
                rtos_osReleaseProcess(/* PID */ idxP);

        /* Release scheduler. */
        pIData->tiOsStep = (unsigned long)GET_CORE_VALUE( RTOS_CLOCK_TICK_IN_MS
                                                        , rtos_osGetIdxCore()
                                                        );
        rtos_osResumeAllInterrupts();
    }

    /* @todo Shall we offer idle tasks per process? If so, we cannot leave the routine but
       would need to enter an infinite loop - and had to offer such a function for OS, too.
       For consistency reasons this would require an init function for OS, too. */

    return errCode;

} /* End of rtos_osInitKernel */




/**
 * Trigger an event to activate all associated tasks. A event, which had been registered
 * with cycle time zero is normally not executed. It needs to be triggered with this
 * function in order to make its associated tasks run once, i.e. to make its task functions
 * executed once as result of this call.\n
 *   This function can be called from any OS task or ISR. However, if the calling task
 * belongs to the set of tasks associated with \a idEvent, then it'll have no effect but an
 * accounted activation loss; an event can be re-triggered only after all associated
 * activations have been completed. There is no activation queueing. The function returns
 * \a false in this case.\n
 *   Note, the system respects the priorities of the activated tasks. If a task of priority
 * higher than the activating task is activated by the triggered event then the activating
 * task is immediately preempted to the advantage of the activated task. Otherwise the
 * activated task is chained and executed after the activating task.
 *   @return
 * There is no activation queuing. Consequently, triggering the event can fail if at least
 * one of the associated tasks has not yet completed after the previous trigger of the
 * event. The function returns \a false and the activation loss counter of the event is
 * incremented. (See rtos_getNoActivationLoss().) In this situation, the new trigger is
 * entirely lost, i.e. none of the associated tasks will be activated by the new trigger.
 *   @param idEvent
 * The ID of the event to activate as it had been got by the creation call for that event.
 * (See rtos_osCreateEvent().)
 *   @param taskParam
 * All associated tasks will receive this value, when they are called because of this
 * trigger.\n
 *   The value is ignored if the function returns \a false.
 *   @remark
 * The function is indented to start a non cyclic task by application software trigger but
 * can be applied to cyclic tasks, too. In which case the task function of the cyclic task
 * would be invoked once additionally. Note, that an event activation loss is not unlikely in
 * this case; the cyclic task may currently be busy.
 *   @remark
 * It may look like an inconsistent API design if all associated tasks receive the same
 * value \a taskParam from the triggering event. The service could easily offer an API,
 * which provides an individual value to each associated task. The only reason not to do
 * so is the additional overhead in combination with the very few imaginable use cases.
 * In most cases an explicitly triggered event will have just one associated task; events
 * with more than one task will mostly be regular timer tasks, which make rarely use of the
 * task parameter.
 *   @remark
 * If \a idEvent addresses a regular, time triggered event and if triggering succeeds, then
 * the regular tasks will receive the passed value from now on. (Instead of the initial
 * value specified at event creation time, see rtos_osCreateEvent().) Note, there's likely
 * no use case for this, it's just a side effect of the implementation. However, it should
 * not do any harm, because mostly regular tasks don't make use of the task parameter and
 * mostly this service is not permitted for such events. If it could be harmful, e.g. if a
 * timer event exceptionally makes use of the task parameter, then explicit triggering of
 * the event using this service needs to be inhibitted.
 *   @remark
 * It is not forbidden but useless to let a task activate itself by triggering the event it
 * is associated with. This will have no effect besides incrementing the activation loss
 * counter for that event.
 *   @remark
 * This function must be called from the OS context only. It may be called from an ISR to
 * implement delegation to a user task.
 */
bool rtos_osTriggerEvent(unsigned int idEvent, uintptr_t taskParam)
{
    /* This function behaves differently depending on whether it is called from an ISR
       (task activation is deferred) or from an OS task (task activation immediately
       possible depending on priorities). If we don't want to offer different APIs for
       tasks and ISRs then we need to have run-time code to decide. This is a little
       performance degradation for sake of ease of use and transparency of the API. */
    const bool isInterrupt = rtos_osIsInterrupt();
    
    /* Although it is not generally forbidden to call this function from a task while under
       lock of External Interrupt processing it's at least very suspicious; the function
       will unconditionally remove the lock, which is likely not what a calling context
       expects if it set the lock. We catch this situation by assertion.
         If this assertion fires then there's likely a misunderstanding of the semantics of
       rtos_osTriggerEvent() in the calling code. */
    assert(isInterrupt || !rtos_osGetAllInterruptsSuspended());
    
    /* This function is shared between ISRs and OS tasks. We need to know because the
       behavior depends (2nd function argument). */
    return osTriggerEvent( getEventByID(idEvent)
                         , /* hasTaskParam */ true
                         , taskParam
                         , isInterrupt
                         );
} /* End of rtos_osTriggerEvent */



/**
 * System call handler implementation to trigger an event (and to activate the associated
 * tasks). Find all details in rtos_osTriggerEvent().
 *   @return
 * \a true if activation was possible, \a false otherwise.
 *   @param pidOfCallingTask
 * Process ID of calling user task. The operation is permitted only for tasks belonging to
 * those processes, which
 * have an ID that is greater of equal to the minimum specified for the event in question.
 * Otherwise an exception is raised, which aborts the calling task.
 *   @param idEvent
 * The ID of the event to trigger. This is the ID got from rtos_osCreateEvent().
 *   @param taskParam
 * All associated tasks will receive this value, when they are called because of this
 * trigger.\n
 *   The value is ignored if the function returns \a false.
 *   @remark
 * It may look like an inconsistent API design if all associated tasks receive the same
 * value \a taskParam from the triggering event. The service could easily offer an API,
 * which provides an individual value to each associated task. The only reason not to do
 * so is the additional overhead in combination with the very few imaginable use cases.
 * In most cases an explicitly triggered event will have just one associated task; events
 * with more than one task will mostly be regular timer tasks, which make rarely use of the
 * task parameter.
 *   @remark
 * If \a idEvent addresses a regular, time triggered event and if triggering succeeds, then
 * the regular tasks will receive the passed value from now on. (Instead of the initial
 * value specified at event creation time, see rtos_osCreateEvent().) Note, there's likely
 * no use case for this, it's just a side effect of the implementation. However, it should
 * not do any harm, because mostly regular tasks don't make use of the task parameter and
 * mostly this service is not permitted for such events. If it could be harmful, e.g. if a
 * timer event exceptionally makes use of the task parameter, then explicit triggering of
 * the event using service rtos_triggerEvent() needs to be inhibitted.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
uint32_t rtos_scFlHdlr_triggerEvent( unsigned int pidOfCallingTask
                                   , unsigned int idEvent
                                   , uintptr_t taskParam
                                   )
{
    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    if(idEvent < pIData->noEvents)
    {
        rtos_eventDesc_t * const pEvent = getEventByID(idEvent);
        if(pidOfCallingTask >= (unsigned int)pEvent->minPIDForTrigger)
            return (uint32_t)osTriggerEvent( pEvent
                                           , /* hasTaskParam */ true
                                           , taskParam
                                           , /* isInterrupt */ false
                                           );
    }

    /* The user specified event ID is not in range or the calling process doesn't have the
       required privileges. Either is a severe user code error, which is handled with an
       exception, task abort and counted error.
         Note, this function does not return. */
    rtos_osSystemCallBadArgument();

} /* End of rtos_scFlHdlr_triggerEvent */



/**
 * This function implements the main part of the scheduler, which actually runs tasks. It
 * inspects all events, whether they have been triggered in an ISR or system call handler
 * and execute the associated tasks if furthermore the priority conditions are fullfilled.
 *   The function is called from the common part of the assembly implementation of the ISRs
 * and from all system call handlers, which could potentially lead to the start of tasks.\n
 *   This function is entered with all interrupt processing disabled (MSR[ee]=0).
 *   @param
 * The caller (likely osTriggerEvent(), immediately or postponed) usually knows, which is
 * the recently triggered event, which has to be handled by the scheduler. This event is
 * provided by reference as a hint so that the scheduler doesn't need to look for the
 * event.
 */
SECTION(.text.ivor.rtos_osProcessTriggeredEvents) void rtos_osProcessTriggeredEvents
                                                               (rtos_eventDesc_t *pEvent)
{
    /* This function and particularly this loop is the essence of the task scheduler. There
       are some tricky details to be understood.
         This function is called as a kind of "on-exit-hook" of any interrupt, which makes
       use of the rtos_osTriggerEvent() service. (Actually, this includes user tasks, which
       run the software interrupt rtos_triggerEvent().) It looks for the triggered event
       and runs the associated tasks if it has a priority higher then the priority of the
       currently running task.
         The operation looks uncomplicated for an event of higher priority. We acknowledge
       the event and run the tasks. Looking for and acknowleding means a read-modify-write
       operation and since the events can at any time be accessed by interrupts of higher
       priority we need a critical section for this.
         First complexity is an interrupt, which sets another event while we are processing
       the tasks of the first one. If this has in turn a higher priority then it's no new
       consideration but just a matter of recursive invocation of this same function.
       However, if it has a priority lower than that of the currently processed event and
       tasks, then we (and not the preempting context, which triggers the event) are
       obliged to run the tasks of this event, too, but - because of the lower priority -
       only later, after the current set of tasks. (Note, "later", there is no
       HW/SW-interrupt any more to get the new event be processed - so we need a loop here
       to not forget that event.) The tricky thing is how to span the critical sections:
         If we find the first event (searching from highest towards lower priorities) then
       we apply the CS just to acknowledge the event. (I.e. no potential later, recursive
       invocation of this function will compete in handling it.) When done with all the
       tasks of the event we release the event. We change the status from "in progress" to
       "idle" - of course again in a CS. However, this CS must now be merged with the CS at
       the beginning of the next cycle, the CS to acknowledge the next found event. The
       reason why:
         As soon as we release an event, it can be set again and in particular before we
       have left this function and killed its stack frame (a stack frame of significant
       size as this function still is element of an ISR). The newly set event would mean a
       recursive call of this function, so another stack frame for the same event. The same
       could then happen to the recursice function invocation and so forth - effectively
       there were no bounds anymore for the stack consumption, which is a fatal risk.
       Merging the CSs for releasing event A and acknowledging event B (of lower priority)
       means that the stack frame of this invokation is inherited by the next processed
       event B before a recursive call can process the next occurance of A. Which is
       alright; this leads to the pattern that there can be outermost one stack frame per
       event priority and this is the possible minimum.
         The same consideration requires that the CS for the final event release must not
       be left before return from the function. Return from the function still means
       several instructions until the stack frame is killed and event setting in this phase
       is just the same as outlined for the loop cycle-to-cycle situation. Actually, the
       final CS must not be ended before the stack frame has been killed, effectively at
       the very end of the ISR, with the rfi instruction.
         Another consideration makes it useful that we are already inside the first
       acknowledge-CS when entering the function. This CS includes the decision (in
       triggerEvenet), whether or not a recursive scheduler call is required. Being here,
       and because of the CS, this information is still coherent with the events' state. We
       can place some assertions, the behavior is more transparent and the implementation
       more reliable. Without an CS we could see this: Event A is set and makes this
       scheduler invoked. Event B can be triggered before tbhe scheduler finds the due
       event. It is preempted by a recursive scheduler invocation. The preempting scheduler
       would handle both events, B first then A. After the preemption the event A is no
       longer due and the scheduler would have to return without doing anything. Which is
       neither a problem nor an advantage (same overall effort and timing), but there are
       less invariants for checking. Note, this is still an option if minimizing the CS
       is rated higher than transparency of behavior. */

    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    /* Here, we are inside a critical section. External Interrupt handling is disabled. */
    assert(rtos_osGetAllInterruptsSuspended());

    /* If we were called because of pending, postponed events, which are indicated by
       pIData->pNextEventToSchedule then the caller must have acknowledged the request by
       setting the pointer back to "unset". */
    assert((uintptr_t)pIData->pNextEventToSchedule == (uintptr_t)-1);

    /* Safe the current state: It'll be updated with each of the events, we find to be
       served, but finally we will have to restore these values here. */
    const rtos_eventDesc_t * const pCurrentEvent = pIData->pCurrentEvent;
    const unsigned int prioAtEntry = pIData->currentPrio;

    /* We iterate the events in order of decreasing priority. */
    assert(pEvent < pIData->pEndEvent &&  pEvent->priority >= prioAtEntry);
    while(true)
    {
        if(pEvent->priority <= prioAtEntry)
        {
            /* Launching tasks must not be considered for events at or below the priority
               at start of this scheduler recursion. This priority level will mostly be
               because another, earlier call of this function, preempted and currently
               suspended somewhere deeper on the OS stack, which already handles the event
               but it can also happen if the PCP has been used to temporarily raise the
               current priority. This would hinder us to serve a triggered event already
               now.
                 We leave the function still (or again) being in a critical section. */
            break;
        }
        else if(pEvent->state == evState_triggered)
        {
            /* Associated tasks are due and they have a priority higher than all other
               currently activated ones. Before we execute them we need to acknowledge the
               event - only then we my leave the critical section. */
            pEvent->state = evState_inProgress;

            /* The current priority is changed synchronously with the acknowledge of the
               event. We need to do this still inside the same critical section. */
            pIData->pCurrentEvent = pEvent;
            pIData->currentPrio = pEvent->priority;

            /* Now handle the event, i.e. launch and execute all associated tasks. This is
               of course not done inside the critical section. We leave it now. */
            rtos_osResumeAllInterrupts();
            launchAllTasksOfEvent(pEvent);

            /* The executed tasks can have temporarily changed the current priority, but
               here it needs to be the event's priority again.
                 The assertion can fire if an OS task raised the priority using the PCP API
               but didn't restore it again. */
            assert(pIData->currentPrio == pEvent->priority);

            /* The event is entirely processed, we can release it. This must not be done
               before we are again in the next critical section. */
            rtos_osSuspendAllInterrupts();
            pEvent->state = evState_idle;

            /* The next event to check is not necessarily the next in order. Since we allow
               events to have the same priority we need to ensure that we have checked all
               other events of same priority before we advance to one of lower priority.
               (If we wouldn't allow same priorities then this condition was implicitly
               fulfilled and we could always advance with the next event in order, which is
               surely of lower priority.)
                 Note, this consideration leads to the repeated check of the same events.
               Example: A and B were events of same priority and appear in the list in this
               order. Event A can be triggered while event B is being proceessed. We must
               check A before we check the successor of B, e.g. C, which has lower
               priority. While running the tasks of A, event B can have been triggered
               again, and so on. In an extreme situation, we would infinitly loop and
               alternatingly process A and B, but C would never been visited and suffer
               from starvation. (Easy to get: A task of A triggers event B and a task of B
               triggers event A.)
                 After we have served an event of priority n, we check the first event of
               this priority n as next one. All event specifications, inlcuding priorities,
               are staical and we have prepared a link from each event to the first in list
               order, which has the same priority but which is not the event itself.
               Examples:
               - A, B, C have prio n, D is the successor of C with prio n-1:
                 - A is linked to B
                 - B and C are linked to A
                 - D is linked to its successor
               - A has prio n, B has prio n-1, C has prio n-2:
                 - A is linked to B
                 - B is linked to C
                 - C is linked to its successor
                 Note, this scheme doesn't lead to a fair round robin for groups of events
               with same priority but this is not a contradiction with the meaning of
               priorities or priority based scheduling. */

            /* Proceed with preceding events of same priority (if any). */
            pEvent = pEvent->pNextScheduledEvent;
        }
        else
        {
            /* Ignore events, which have not been set (yet). */

            /* There must be no events in state inProgress, which have a priority above the
               current one. */
            assert(pEvent->state == evState_idle);

            /* Proceed with next event. No need to start over at first event of same
               priority as we had not left the critical section so that no such event can
               have been triggered meanwhile. */
            ++ pEvent;

        } /* End if(Which event state?) */
    } /* End while(All events of prio, which is to be handled by this scheduler invocation) */

    /* Here we are surely still or again inside a critical section. */

    /* Restored the initial state. */
    pIData->pCurrentEvent = pCurrentEvent;
    pIData->currentPrio = prioAtEntry;

} /* End of rtos_osProcessTriggeredEvents */



/**
 * Priority ceiling protocol (PCP), partial scheduler lock: All tasks up to the specified
 * task priority level won't be handled by the CPU any more. This function is intended for
 * implementing mutual exclusion of sub-sets of tasks.\n
 *   Note, the use of the other function pairs\n
 *   - rtos_osEnterCriticalSection() and\n
 *   - rtos_osLeaveCriticalSection()\n
 * or\n
 *   - rtos_osSuspendAllInterrupts() and\n
 *   - rtos_osResumeAllInterrupts()\n
 * locks all interrupt processing and no other task (or interrupt handler) can become
 * active while the task is inside the critical section code. With respect to behavior,
 * using the PCP API is much better: Call this function with the highest priority of all
 * tasks, which should be locked, i.e. which compete for the resource or critical section
 * to protect. This may still lock other, non competing tasks, but at least all interrupts
 * and all non competing tasks of higher priority will be served.\n
 *   The major drawback of using the PCP instead of the interrupt lock API is the
 * significantly higher expense; particularly at the end of the critical section, when
 * resuming the scheduling again: A recursive call of the scheduler is required to see if
 * some tasks of higher priority had become ready during the lock time. Therefore, locking
 * the interrupts is likely the better choice for very short critical sections.\n
 *   To release the protected resource or to leave the critical section, call the
 * counterpart function rtos_osResumeAllTasksByPriority(), which restores the original
 * task priority level.
 *   @return
 * The task priority level at entry into this function (and into the critical section) is
 * returned. This level needs to be restored on exit from the critical section using
 * rtos_osResumeAllTasksByPriority().
 *   @param suspendUpToThisTaskPriority
 * All tasks up to and including this priority will be locked, i.e. they won't be executed
 * even if they'd become ready. The CPU will not handle them until the priority level is
 * lowered again.
 *   @remark
 * The critical section shaped with this API from an OS task guarantees mutual exclusion
 * with critical section code shaped with the other API rtos_suspendAllTasksByPriority()
 * from a user code task.
 *   @remark
 * To support the use case of nested calls of OSEK/VDX like GetResource/ReleaseResource
 * functions, this function compares the stated value to the current priority level. If \a
 * suspendUpToThisTaskPriority is less than the current value then the current value is not
 * altered. The function still returns the current value and the calling code doesn't need
 * to take care: It can unconditionally end a critical section with
 * rtos_osResumeAllTasksByPriority() stating the returned priority level value. (The
 * resume function will have no effect in this case.) This makes the OSEK like functions
 * usable without deep inside or full transparency of the priority levels behind the scene;
 * just use the pairs of Get-/ResumeResource, be they nested or not.
 *   @remark
 * The use of this function to implement critical sections is usually quite static. For any
 * protected entity (usually a data object or I/O device) the set of competing tasks
 * normally is a compile time known. The priority level to set for entry into the critical
 * section is the maximum of the priorities of all tasks in the set. The priority level to
 * restore on exit from the critical section is the priority of the calling task. All of
 * this static knowledge would typically be put into encapsulating macros that actually
 * invoke this function. (OSEK/VDX like environments would use this function pair to
 * implement the GetResource/ReleaseResource concept.)
 *   @remark
 * Any change of the current priority level made with this function needs to be undone
 * using rtos_osResumeAllTasksByPriority() and still inside the same task. It is not
 * possible to consider this function a mutex, which can be acquired in one task activation
 * and which can be released in an arbitrary later task activation or from another task.\n
 *   Moreover, different to the user mode variant of the PCP function pair, there is no
 * restoration of the current priority level at task termination time.\n
 *   An assertion in the scheduler will likely fire if the two PCP APIs are not properly
 * used in pairs.
 *   @remark
 * This function must be called from OS tasks only. Any attempt to use it from either an
 * ISR or in user mode code will lead to either a failure or privileged exception,
 * respectively.
 *   @remark
 * This function requires that msr[EE]=1 on entry.
 */
uint32_t rtos_osSuspendAllTasksByPriority(uint32_t suspendUpToThisTaskPriority)
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    const uint32_t prioBeforeChange = pIData->currentPrio;
    if(suspendUpToThisTaskPriority > prioBeforeChange)
        pIData->currentPrio = suspendUpToThisTaskPriority;

    return prioBeforeChange;

} /* rtos_osSuspendAllTasksByPriority */




/**
 * This function is called to end a critical section of code, which requires mutual
 * exclusion of two or more tasks. It is the counterpart of function
 * rtos_osSuspendAllInterruptsByPriority(), refer to that function for more details.\n
 *   @param resumeDownToThisTaskPriority
 * All tasks/interrupts above this priority level are resumed again. All tasks/interrupts
 * up to and including this priority remain locked.\n
 *   You will normally pass in the value got from the related call of
 * rtos_osSuspendAllInterruptsByPriority().
 *   @remark
 * Caution, this function lowers the current task priority level to the stated value
 * regardless of the initial value for the task. Accidentally lowering the task priority
 * level below the configured task priority (i.e. the priority inherited from the triggering
 * event) will have unpredictable consequences.
 *   @remark
 * Different to the user mode variant of the function, rtos_resumeAllTasksByPriority(),
 * there is no restoration of the current priority level at task termination time. For OS
 * tasks, there's no option to omit the resume operation if a critical section should last
 * till the end of the task - and there's no need to attempt this neither: The OS variant
 * of the function doesn't involve the overhead of a system call and no execution time
 * would be saved as for the user variant.
 *   @remark
 * This function must be called from OS tasks only. Any attempt to use it from either an
 * ISR or in user mode code will lead to either a failure or privileged exception,
 * respectively.
 *   @remark
 * This function requires that msr[EE]=1 on entry.
 */
void rtos_osResumeAllTasksByPriority(uint32_t resumeDownToThisTaskPriority)
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    if(resumeDownToThisTaskPriority < pIData->currentPrio)
    {
        /* Identify the events, which could possibly require the recursive call of the
           scheduler.
             Note, there is a significant difference in the implementation here for the OS
           tasks and the system call that implements the same concept for the user tasks.
           The OS code just identifies the events that may have been triggered meanwhile
           and calls the scheduler to let it decide whether there's really something to do.
           Often, this won't be the case. (Which is possible for the other reason, too,
           that the check code is not inside the critical section).
             The system call implementation really figures out whether there is at least
           one event that requires scheduling. It looks at the state of all possible
           candidates. Effectively, it re-implements part of the scheduler itself. The
           reason is the significant overhead, which results from calling a C function from
           a system call. In the majority of cases, the system call will find that calling
           the scheduler is not needed so that this effectively is a significant
           optimization. The OS code here would not benefit from the same strategy. */
        rtos_eventDesc_t * const pEvToSchedulePossibly = 
                                                rtos_osGetEventByPriority(pIData->currentPrio);
        pIData->currentPrio = resumeDownToThisTaskPriority;

        rtos_osSuspendAllInterrupts();
        /* Note, because check and change of the current prio are not inside the critical
           section it can easily be that the call of the scheduler is already obsolete.
           This doesn't matter, not even with respect to overhead and the number of
           function invocations. Not taking check and change into the CS just means to have
           a smaller CS. */
        rtos_osProcessTriggeredEvents(pEvToSchedulePossibly);
        rtos_osResumeAllInterrupts();
    }
} /* rtos_osResumeAllTasksByPriority */



/**
 * An event, which becomes due may not be able to activate all its associated tasks because
 * they didn't terminate yet after their previous activation. It doesn't matter if this
 * happens because a cyclic task becomes due or because an event task has been triggered by
 * software (using rtos_triggerEvent()). The scheduler counts the failing activations on a
 * per event base. The current value can be queried with this function.
 *   @return
 * Get the current number of triggers of the given event, which have failed since start of
 * the RTOS scheduler. The counter is saturated and will not wrap around.\n
 *   The returned count can be understood as number of task overrun events for all
 * associated tasks.
 *   @param idEvent
 * Each event has its own counter. The value is returned for the given event. The range is 0
 * .. number of registered events minus one (double-checked by assertion).
 *   @remark
 * This function can be called from both, the OS context and a user task.
 */
unsigned int rtos_getNoActivationLoss(unsigned int idEvent)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_getInstancePtr();
    if(idEvent < pIData->noEvents)
    {
        const rtos_kernelInstanceData_t * const pIData = rtos_getInstancePtr();
        assert(idEvent < pIData->noEvents);
        const rtos_eventDesc_t *pEvent = pIData->mapEventIDToPtr[idEvent];
        return pEvent->noActivationLoss;
    }
    else
    {
        assert(false);
        return UINT_MAX;
    }
} /* End of rtos_getNoActivationLoss */



/**
 * A cyclic or event task can query its base priority.
 *   @return
 * Get the base priority of the task, which calls this function. It's the priority of the
 * event it is associated with.
 *   @remark
 * The function is quite similar to rtos_getCurrentBasePriority() but this function
 * considers temporary changes of the priority of a task because of the use of the PCP API.
 * For one and the same task, it is rtos_getCurrentPriority() >
 * rtos_getCurrentBasePriority().
 *   @remark
 * This function can be called from an OS task only. Any attempt to call it from a user
 * task will cause a privileged exception.
 *   @remark
 * The function must not be called from an ISR. The result would be undefined as there is
 * no event, which such a handler function would be associated with. However, with respect
 * to safety or stability, there's no problem in doing this.
 */
unsigned int rtos_osGetTaskBasePriority(void)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    return pIData->pCurrentEvent->priority;

} /* End of rtos_osGetTaskBasePriority */


#if 0
/**
 * A task can query the current task scheduling priority.
 *   @return
 * Get the current priority of the task, which calls this function.
 *   @remark
 * The function is quite similar to rtos_osGetTaskBasePriority() but this function
 * considers temporary changes of the priority of a task because of the use of the PCP API.
 * For one and the same task, it is rtos_getCurrentTaskPriority() >
 * rtos_osGetTaskBasePriority().
 *   @remark
 * This function can be called from both, an OS or a user task.
 *   @remark
 * The function must not be called from an ISR or from a callback, which is started by an
 * ISR and using the service rtos_osRunTask(). The result would be undefined as there is no
 * event, which such a function would be associated with. However, with respect to safety
 * or stability, there's no problem in doing this and therefore no privileges have been
 * connected to this service.
 */
unsigned int rtos_getCurrentTaskPriority(void)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_getInstancePtr();
    return (unsigned int)pIData->currentPrio;

} /* End of rtos_getCurrentTaskPriority */
#endif
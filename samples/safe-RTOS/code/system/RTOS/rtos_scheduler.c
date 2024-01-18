/**
 * @file rtos_scheduler.c
 * This file implements a simple yet "safe" Real Time Operating System (RTOS) for the
 * MPC5748G.\n
 *   The RTOS offers a strictly priority controlled scheduler. The user code is organized
 * in processes and tasks. Any task belongs to one of the processes. Different processes
 * have different privileges. The concept is to use the process with highest privileges for
 * the safety tasks.\n
 *   A task is activated by events. Events are either produced on timer base by event
 * processors or software notified to the processor; an application will repeatedly use the
 * API rtos_osCreateEventProcessor() to define the conditions or points in time, when the
 * tasks have to become due.\n
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
 * (i.e., ready for execution). If more than a single task are ready at a time then the
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
 * Basic conformance class means that a task cannot suspend intentionally and ahead of its
 * normal termination, e.g., entering a system call to wait for an event. Once started, it
 * needs to be entirely executed. Due to the strict priority scheme it'll temporarily
 * suspend only for sake of tasks of higher priority (but not voluntarily or on own
 * desire).\n
 *   The activation of a task can be done by software, using API function
 * rtos_osSendEvent() or rtos_sendEvent() or it can be done by the scheduler on a
 * regular time base. In the former case the task is called an event task, the latter is a
 * cyclic task with fixed period time.\n
 *   The RTOS implementation is tightly connected to the implementation of interrupt
 * services. Interrupt services, e.g., to implement I/O operations for the tasks, are
 * registered with rtos_osRegisterInterruptHandler(). There are a few services, which are
 * available to ISRs:
 *   - An ISR may use rtos_osEnterCriticalSection()/rtos_osLeaveCriticalSection(),
 * rtos_osSuspendAllInterrupts()/rtos_osResumeAllInterrupts() or
 * rtos_osSuspendAllInterruptsByPriority()/rtos_osResumeAllInterruptsByPriority() to shape
 * critical sections with other ISRs or with OS tasks, which are based on interrupt locks
 * and which are highly efficient. (Note, safety concerns forbid having an API to shape a
 * critical section between ISRs and user tasks.)
 *   - An ISR may use rtos_osSendEvent() to trigger an event processor. The associated
 * tasks will be scheduled after returning from the interrupt (and from any other interrupt
 * it has possibly preempted)
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
 * comparison to the advantage of now having an unlimited number of event processors,
 * priorities and tasks.\n
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
 * Copyright (C) 2017-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   rtos_osCreateEventProcessor
 *   rtos_osCreateSwTriggeredEventProcessor
 *   rtos_osRegisterInitTask
 *   rtos_osRegisterUserTask
 *   rtos_osRegisterOSTask
 *   rtos_osInitKernel
 *   rtos_osSendEvent
 *   rtos_osSendEventCountable
 *   rtos_osSendEventMultiple
 *   rtos_scFlHdlr_sendEvent
 *   rtos_osProcessTriggeredEvProcs
 *   rtos_osSuspendAllTasksByPriority
 *   rtos_osResumeAllTasksByPriority
 *   rtos_getNoActivationLoss
 *   rtos_osGetTaskBasePriority
 *   rtos_getCurrentTaskPriority
 * Module inline interface
 *   rtos_osGetCurrentInterruptPriority
 *   rtos_osIsInterrupt
 * Local functions
 *   getEventProcByID
 *   getEventProcByIdx
 *   registerTask
 *   incMaskedCounter
 *   osSendEvent
 *   checkEventDue
 *   onOsTimerTick
 *   launchAllTasksOfEvProc
 *   advanceEvProcToSuccesorSamePrio
 *   advanceEvProcToSuccesorLowerPrio
 *   initRTOSClockTick
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "ccl_configureClocks.h"
#include "stm_systemTimer.h"
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
#if RTOS_IDX_SC_SEND_EVENT != RTOS_SYSCALL_SEND_EVENT
# error Inconsistent definitions made in C modules and RTOS API header file rtos.h
#endif

#if RTOS_MAX_LOCKABLE_TASK_PRIORITY >= RTOS_MAX_TASK_PRIORITY
# error Suspicious task priority configuration
#endif

/** A pseudo event ID. Used to register a process initialization task using registerTask(). */
#define EVENT_PROC_ID_INIT_TASK     (UINT_MAX)

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

/** Hook function for ISRs and system calls: Some tasks of triggered event processors are
    possibly to be executed (depending on priority rules).\n
      Note, this function is not publically declared although it is global. It is called
    externally only from the assembly code, which can't read public declarations in header
    files.
      @param pEvProc
    The first event processor in global list, which is to be considered for scheduling. */
void rtos_osProcessTriggeredEvProcs(rtos_eventProcDesc_t *pEvProc);


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
 * Helper: Resolve the linear event processor index used at the API into the actual object.
 * The mapping is not trivial since the event processors are internally ordered by
 * priority.
 *   @return
 * Get the event processor object by reference.
 *   @param idEventProc
 * The linear index of the event processor as used at the API.
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
static ALWAYS_INLINE rtos_eventProcDesc_t *getEventProcByID(unsigned int idEventProc)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    assert(idEventProc < pIData->noEventProcs);
    return pIData->mapEvProcIDToPtr[idEventProc];

} /* End of getEventProcByID */



/**
 * Helper: Resolve the linear, zero based, internally used array index into the actual
 * event processor object. This function is trivial and intended more for completeness: it
 * complements the other function getEventProcByID().
 *   @return
 * Get the event processor object by reference.
 *   @param idxEventProc
 * Index of event processor object in the array rtos_getInstancePtr()->eventProcAry.
 *   @remark
 * This function must be called from a supervisor context only. It makes use of priviledged
 * instructions.
 */
static ALWAYS_INLINE rtos_eventProcDesc_t *getEventProcByIdx(unsigned int idxEventProc)
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    return &pIData->eventProcAry[idxEventProc];

} /* End of getEventProcByIdx */




/**
 * Helper: Advance the pointer to an event processor to its successor in the chain of all.
 *   Here, for processors of same priority and in a cyclic manner. If ** \a ppEvProc is the
 * only one of given priority then the function result is the unmodified, same pointer.
 *   @param ppEvProc
 * The pointer to the event processor by reference. * \a ppEvProc is function argument and
 * result.
 */
static ALWAYS_INLINE void advanceEvProcToSuccesorSamePrio
                                                    (rtos_eventProcDesc_t ** const ppEvProc)
{
    const const rtos_eventProcDesc_t * const pEvProc = *ppEvProc;
    *ppEvProc = (rtos_eventProcDesc_t*)((intptr_t)pEvProc
                                         + pEvProc->offsNextEvProcSamePrio
                                       );
} /* advanceEvProcToSuccesorSamePrio */


/**
 * Helper: Advance the pointer to an event processor to its first follower in the chain of
 * all, which has a lower priority. The operation is always defined due to the guard
 * element at the end of the list, which has a priority lower than any true list element can
 * have.
 *   @param ppEvProc
 * The pointer to the event processor by reference. * \a ppEvProc is function argument and
 * result.
 */
static ALWAYS_INLINE void advanceEvProcToSuccesorLowerPrio
                                                    (rtos_eventProcDesc_t ** const ppEvProc)
{
    const const rtos_eventProcDesc_t * const pEvProc = *ppEvProc;
    *ppEvProc = (rtos_eventProcDesc_t*)((intptr_t)pEvProc
                                        + pEvProc->offsNextEvProcLowerPrio
                                       );
} /* advanceEvProcToSuccesorLowerPrio */


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
 *   @param idEventProc
 * Any (normal) task is activated by an event and a task without related event processor is
 * useless. This call associates the registered task with an already created event
 * processor. See rtos_osCreateEventProcessor().\n
 *   If a process or OS initialization task is registered, then \a idEventProc is set to
 * #EVENT_PROC_ID_INIT_TASK. It is allowed not to register an init task for a process or
 * for the OS but it is not possible to register more than one (or to re-register an) init
 * task for a given process or the OS.\n
 *   The order of registration of several tasks with one and the same event processor
 * matters. The tasks will be acivated in order of registration whenever the event
 * processor becomes due or is triggered by software.\n
 *   The order of registration doesn't matter for initialization tasks! The OS
 * initialization task is served first. Processes are always initialized in order of rising
 * process ID. The most privileged process is served last and can thus override descisions
 * of its less privileged predecessors.
 *   @param addrTaskFct
 * The task function, which is run in process \a PID every time, the event processor \a
 * idEventProc becomes due or is triggered by software.
 *   @param PID
 *   The process the task belongs to by identifier. We have a fixed, limited number of four
 * processes (#RTOS_NO_PROCESSES) plus the kernel process, which has ID 0. The range of
 * process IDs to be used here is 0 .. #RTOS_NO_PROCESSES.\n
 *   @param tiTaskMaxInUs
 * Time budget for the user task in Microseconds. This budget is granted for each
 * activation of the task, i.e., each run of \a addrTaskFct(). The budget relates to
 * deadline monitoring, i.e., it is a world time budget, not an execution time budget.\n
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
static rtos_errorCode_t registerTask( unsigned int idEventProc
                                    , uintptr_t addrTaskFct
                                    , unsigned int PID
                                    , unsigned int tiTaskMaxInUs
                                    )
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    /* The scheduler should be in halted state. */
    if(pIData->tiOsStep != 0)
        return rtos_err_configurationOfRunningKernel;

    /* The event processor need to be created before the task can be registered. */
    if(idEventProc >= pIData->noEventProcs  &&  idEventProc != EVENT_PROC_ID_INIT_TASK)
        return rtos_err_badEventProcId;

    /* The process ID needs to be in the fixed and limited range. */
    if(PID > RTOS_NO_PROCESSES)
        return rtos_err_badProcessId;

    /* The number of runtime tasks is constraint by compile time configuration. */
    if(pIData->noTasks >= RTOS_MAX_NO_TASKS  &&  idEventProc != EVENT_PROC_ID_INIT_TASK)
        return rtos_err_tooManyTasksRegistered;

    /* The event processor's field noTasks is of smaller size. */
    if(idEventProc != EVENT_PROC_ID_INIT_TASK
       &&  getEventProcByIdx(idEventProc)->noTasks
           >= UINT_T_MAX(((rtos_eventProcDesc_t*)NULL)->noTasks)
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
    if(idEventProc == EVENT_PROC_ID_INIT_TASK)
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
        /* Add the new runtime task to the array. All tasks associated with an event
           processor need to form a consecutive list. We need to find the right location to
           insert the task and we need to consider an update of all event processors with
           refer to tasks with higher index. */
        rtos_eventProcDesc_t * const pEvProc = getEventProcByID(idEventProc);
        rtos_taskDesc_t *pNewTaskDesc;
        if(pEvProc->taskAry == NULL)
        {
            /* First task of given event processor, we append a new sequence of tasks to
               the end of the task list so far. Done. */
            pEvProc->taskAry = pNewTaskDesc = &pIData->taskCfgAry[pIData->noTasks];

            /* Associate the task with the specified event processor. */
            pEvProc->noTasks = 1;
        }
        else
        {
            /* This is a further task for the event processor. We will have to shift the
               tasks in the task list to still have a consecutive sequence of tasks for the
               event processor. */
            pNewTaskDesc = (rtos_taskDesc_t*)pEvProc->taskAry + pEvProc->noTasks;

            /* The event processor's task sequence can be in the middle of the task list.
               So need to check if we have to move some rightmost list entries. */
            rtos_taskDesc_t *pTaskCfg = &pIData->taskCfgAry[pIData->noTasks];
            assert(pIData->noTasks >= 2  ||  pTaskCfg <= pNewTaskDesc);
            for(; pTaskCfg>pNewTaskDesc; --pTaskCfg)
                *pTaskCfg = *(pTaskCfg-1);

            /* Update the reference to the task sequence for all event processors, which
               still point to the shifted area of the task list. Note, that the event
               processors don't have a particular order with respect to the user specified
               index. (Instead, they are sorted by priority.) */
            unsigned int idxEvProc;
            for(idxEvProc=0; idxEvProc<pIData->noEventProcs; ++idxEvProc)
            {
                rtos_eventProcDesc_t * const pCheckedEvProc = getEventProcByIdx(idxEvProc);
                if(pCheckedEvProc != pEvProc  &&  pCheckedEvProc->taskAry >= pNewTaskDesc)
                    ++ pCheckedEvProc->taskAry;
            }

            /* Associate the task with the specified event processor. */
            ++ pEvProc->noTasks;
            assert(pEvProc->noTasks > 0);
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
 * This function implements the increment of a counter, which consists of an arbitrary
 * number of bits scattered over a 32 Bit word. Where the counter bits sit in the word is
 * expressed by a mask. The significance of counter bits has the same ordering as for the
 * bits in the word.\n
 *   All bits in the word, i.e., * \a pWord, which do not correspond to a bit set in the
 * mask are not affected by the operation.\n
 *   The current value of the counter, denoted by the mask bits, is incremented by a small
 * integral number \a inc if this is possible without overflow to zero. If the increment
 * would overflow then the counter is not modified as far as possible, i.e., the counter in
 * the word is saturated at its implementation maximum.\n
 *   Note, for single-bit masks, the operation is identical to:\n
 *   *pWord = *pWord | mask;
 *   @return
 * Get zero if the operation succeeds, if the counter can be incremented by \a inc. A
 * value greater than zero means the number of increments, which could not be executed
 * because the counter reached its implementation limit before.\n
 *   If the function doesn't return zero then the counter is at its implementation limit
 * but still to little by the returned value.
 *   @param pWord
 * The word, i.e., the container of the counter, by reference.
 *   @param mask
 * The bits in the mask denote the bits of the counter inside the word.
 *   @param inc
 * A small integral number, which should be added to the counter. The operation is
 * iterative, meaning O(inc). To avoid long blocking times, the operation is implicitly
 * limited to inc <= 255 by choosing an according data type.
 */
static inline unsigned int incMaskedCounter(uint32_t * const pWord, uint32_t mask, uint8_t inc)
{
    /* If we set beforehand all non-counter bits, then the normal increment of the word
       will ripple either into the counter or, if it has already all bits set, beyond it. */
    do
    {
        const uint32_t newMaskedVal = ((*pWord | ~mask) + 1u) & mask;
        if(newMaskedVal != 0u)
        {
            *pWord = (*pWord & ~mask) | newMaskedVal;
        }
        else
            break;

        -- inc;
    }
    while(inc > 0u);

    return inc;

} /* incMaskedCounter */



/**
 * Trigger an event processor to let it activate all associated tasks.\n
 *   This function implements the operation. It is called from different API functions,
 * those for OS code and those for user code (the latter via system call). See, e.g.,
 * rtos_osSendEvent() and rtos_sendEvent() for more details.
 *   @return
 * Get \a true if event could be delivered, \a false otherwise.\n
 *   Note, for countable events, \a true means that all multiplicities of the event could
 * be delivered but it does not necessarily mean that the event processor has already been
 * triggered on exit from the function. The associated tasks may still be busy executing.
 * However, the event has been recorded and will re-trigger the event processor immediately
 * after returning to idle.
 *   @param pEvProc
 * The event processor to trigger by reference.
 *   @param noCountableTriggers
 * The distinction between countable and ordinary events is made using this parameter.
 * Zero means using the ordinary event. It triggers the event processor, but only if it is
 * currently idle. It passes an argument of arbitrary value as task parameter to the next
 * activation of the associated task functions.\n
 *   Values greater than zero mean to notify the event with according multiplicity. The
 * associated task functions will receive the multiplicity of the event as task parameter.
 * If the event processor is not idle then the multiplicity of the event is accumulated. As
 * soon as the event processor becomes idle it'll be triggered and the associated task
 * functions will get all the event counts accumulated meanwhile as task parameter (from
 * this and maybe from later calls of this function).\n
 *   The accumulating variable has an implementation limit. As long as this limit is not
 * exceeded it is guaranteed that the task functions will eventually get all multiplicities
 * of the event. The function returns \a false if at least one multiplicity of the event is
 * lost.\n
 *   For regular, timer triggered event processors, the value, which has been configured at
 * event creation time, is re-used every time they become due. This way, a timer triggered
 * event can use ordinary events or countable events.
 *   @param evMaskOrTaskParam
 * In case of countable events, \a evMaskOrTaskParam is the mask that specifies the
 * variable for accumulating the multiplicities of the event, which are still to be
 * delivered to the associated task functions. The variable consists of all bits, which are
 * set in \a evMaskOrTaskParam. (Normally, but this is not a must, this will be all
 * neighbored bits.) If less than 32 bits are set then the implementation maximum of the
 * counter drops but the unset bits become available to notifying other countable events to
 * the same event processor and to the associated task functions.\n
 *   For example, using the masks 0xFF, 0xFF00, 0xFF0000 and 0xFF000000 one could trigger
 * the event processor with four different countable events, each capable of temporarily
 * storing a multiplicity of up to 255. The associated task functions receive the countable
 * events in their task parameter and using the same bit masks for decoding the counts.\n
 *   For regular, timer triggered event processors and if the processor is currently idle,
 * this is the task parameter for the next activation of the associated task functions.
 *   @param isInterrupt
 * This function submits an immediate call of the scheduler if an event of accordingly high
 * priority is triggered. However, this call is postponed if we are currently still inside
 * an interrupt. This flag tells about.\n
 *   Note, this is an inline function. The complete is-interrupt decision code will be
 * discarded if a Boolean literal can be passed in - as it is for the call from the timer
 * ISR and the user task API. Only the OS API, which is shared between ISRs and OS tasks
 * will really contain the run-time decision code.
 */
static ALWAYS_INLINE bool osSendEvent( rtos_eventProcDesc_t * const pEvProc
                                     , uint8_t noCountableTriggers
                                     , uint32_t evMaskOrTaskParam
                                     , const bool isInterrupt
                                     )
{
    /* Countable events require the native 32 Bit word, task parameter requires a pointer
       type. */
    _Static_assert(sizeof(uintptr_t) <= sizeof(uint32_t), "Bad combination of argument types");

    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    bool success = true;

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

    uint32_t taskParam = 0u;
    if(noCountableTriggers == 0u)
    {
        /* The old way of posting events: The event is not countable and the argument is
           the desired task parameter, meaningless to the scheduler, just forwarded as
           is. */
        taskParam = evMaskOrTaskParam;
    }
    else
    {
        /* Increment the countable event, which is specified by the event mask, in the
           accumulator of events as often as demanded.
             Caution, the implementation of incMaskedCounter() is of complexity O(n) and we
           must not block if someone demands, e.g., UINT_MAX. The only way out is limiting
           and documenting this as a constraint.
             Note, an implementation with O(1) is possible but ugly and it performs much
           worse for the by far most important use case (n=1). A mixed implementation
           depending on n is of course imaginable if use cases become visible. */
        const unsigned int failInc = incMaskedCounter( &pEvProc->eventCounterMask
                                                     , evMaskOrTaskParam
                                                     , noCountableTriggers
                                                     );
        if(failInc < (unsigned)noCountableTriggers)
            taskParam = pEvProc->eventCounterMask;
        else
        {
            /* The invalid counter mask zero will always make counting fail. This is a
               client code error. */
            assert(evMaskOrTaskParam != 0u);
            success = false;
        }

        /* The number of provided events can exceed the implementation maximum of the
           counter and some events would be lost. We record this in the task overflow
           counter.
             Note, we increment for each failing multiplicity of the event, but the task
           can still be triggered and activated with a remaining number of events. */
        pEvProc->noActivationLoss += failInc;

    } /* if(Macro is used in mode "collecting events" or old style?) */

    if(pEvProc->state == evState_idle)
    {
        /* Counting events above must never fail entirely if the task is idle; all elder
           events should have been delivered and the accumulator should be zero, i.e., able
           to accept at least a single multiplicity of the new event. */
        assert(success);

        /* Operation successful. Event can be triggered. */
        pEvProc->state = evState_triggered;

        /* Set the task function argument for this activation.
             For countable events: In an atomic operation, make the collected events the
           argument of the upcoming execution of the task functions and clear the
           collection so far - this way it is guaranteed that each posted event is
           delivered once and only once. */
        pEvProc->taskParam = taskParam;

        /* Acknowledge delivered countable events. */
        if(noCountableTriggers > 0u)
            pEvProc->eventCounterMask = 0u;

        /* Setting an event means a possible context switch to another task. It depends on
           priority and interrupt state. If so, we need to run the scheduler.
             It is not necessary to run the scheduler if the triggered event has a priority
           equal to or lower than the priority of the currently processed event. In this
           case the scheduler would anyway not change the current task right now.
             The scheduler must not be called if this function is called from inside an
           ISR. ISRs will call the function a bit later, when the interrupt context is
           cleared and only if they serve the root level interrupt (i.e., not from a nested
           interrupt). In this case calling rtos_osProcessTriggeredEvProcs() is postponed
           and done from the assembly code (IVOR #4 handler) but not yet here. The global
           flag pIData->pNextEvProcToSchedule is set to command this. */
        if(pEvProc->priority > pIData->currentPrio)
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
                if(pEvProc < pIData->pNextEvProcToSchedule)
                    pIData->pNextEvProcToSchedule = pEvProc;
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
                rtos_osProcessTriggeredEvProcs(pEvProc);
            }
        }
        else
        {
            /* Two possibilities to get here:
                 - The event's priority is in the scope of the currently operating
               scheduler. No need to immediately start a recursive scheduler or to postpone
               this start.
                 - The event has a priority, which is lower than the current one but still
               higher than the base priority of the currently processed event. This
               situation occurs if the current priority had been raised by means of the PCP
               API. Scheduling of the triggered event is postponed till the PCP API lowers
               the priority again. There's no simple way to store the information
               whether/which event to serve when PCP will later lower the priority:
                 "Whether" depends on the not yet known information how far PCP will be
               asked to lower the priority.
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
           written concurrently from another task invoking rtos_osSendEvent() or by the
           timer controlled scheduler. */
        if(noCountableTriggers == 0u)
        {
            success = false;
            ++ pEvProc->noActivationLoss;
        }
    }
    rtos_osLeaveCriticalSection(stateIrqAtEntry);

    return success;

} /* End of osSendEvent */




/**
 * Process the conditions that trigger event processors. The event processors are checked
 * for becoming meanwhile due and the associated tasks are made ready in case by setting
 * the according state in the event processor object. However, no tasks are already started
 * in this function.
 */
static inline void checkEventDue(void)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    rtos_eventProcDesc_t *pEvProc = getEventProcByIdx(0);

    /* We iterate the event processors in order for decreasing priority. */
    const rtos_eventProcDesc_t * const pEndEvProc = pIData->pEndEvProc;
    while(pEvProc < pEndEvProc)
    {
        if(pEvProc->tiCycleInMs > 0)
        {
            if((signed int)(pEvProc->tiDue - pIData->tiOs) <= 0)
            {
                /* Trigger the event processor or count an activation loss error. */
                osSendEvent( pEvProc
                           , /* noCountableTriggers */ pEvProc->timerUsesCountableEvs? 1u: 0u
                           , pEvProc->timerTaskTriggerParam
                           , /* isInterrupt */ true
                           );

                /* Adjust the due time.
                     Note, we could queue task activations for cyclic tasks by not adjusting
                   the due time. Some limitation code would be required to make this safe. */
                pEvProc->tiDue += pEvProc->tiCycleInMs;

            } /* End if(Event Processor is due?) */
        }
        else
        {
            /* Non regular events: nothing to be done. These event processors are triggered
               only by explicit software call of rtos_sendEvent(). */

        } /* End if(Timer or application software activated task?) */

        /* Proceed with next event processor. */
        ++ pEvProc;

    } /* End While(All configured event processors) */

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
 * Processing a triggered event processor means to execute all associated tasks. If the
 * scheduler finds an event processor to be processed as next one, then it'll call this
 * function to run the tasks.
 *   @param pEvProc
 * The event processor by reference, whose tasks are to be executed one after another.
 */
static inline void launchAllTasksOfEvProc(const rtos_eventProcDesc_t * const pEvProc)
{
    const rtos_taskDesc_t *pTaskConfig = &pEvProc->taskAry[0];
    unsigned int u = (unsigned int)pEvProc->noTasks;
    const uint32_t taskParam = pEvProc->taskParam;
    while(u-- > 0)
    {
        if(pTaskConfig->PID > 0)
            rtos_osRunTask(pTaskConfig, taskParam);
        else
            ((void (*)(uintptr_t))pTaskConfig->addrTaskFct)(taskParam);

        ++ pTaskConfig;

    } /* End while(Run all tasks associated with the event processor) */

} /* End of launchAllTasksOfEvProc */


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
                  
    /* On the MPC5748G, which doesn't have a free running counter itself, we use device
       STM0 for measuring time spans (e.g., deadline monitoring. Public convenience macros
       for scaling Milliseconds to ticks of this counter need to be double-checked for
       consistency with the configuration of the STM. */
    _Static_assert( RTOS_TI_MS2TICKS(1000u) == STM_TIMER_0_CLK
                    &&  RTOS_TI_US2TICKS(1000u) == RTOS_TI_MS2TICKS(1u)
                  , "Inconsistency between public API and configuration of STM found"
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

    /* The PIT is clocked by F40 (RM, 9.4.4.2, p.213). This peripheral clock has been
       initialized to 40 MHz. To get a 1ms interrupt tick we need to count till 40000. We
       configure an interrupt rate of RTOS_CLOCK_TICK_IN_MS_CORE_0 (_1, _2) Milliseconds.
         -1: See RM, 51.6 */
    _Static_assert(CCL_PER_CLK_F40 == 40000000u, "Unexpected clock rate");
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
 * Creation of an event processor. The event processor can produce a periodic timer event
 * or it can be software triggered. An event processor is needed to activate a user task.
 * Therefore, any reasonable application will create at least one event processor.\n
 *   This function is repeatedly called by the application code for each required event
 * processor. All calls of this function need to be done prior to the start of the kernel
 * using rtos_osInitKernel().\n
 *   @return
 * \a rtos_err_noError (zero) if the event processor could be created. The maximum number
 * of event processors is limited to #RTOS_MAX_NO_EVENT_PROCESSORS. If the event processor
 * cannot be created due to this constraint or if the function arguments are invalid or
 * inconsistent then the function returns a non zero value from enumeration \a
 * rtos_errorCode_t.\n
 *   An assertion in the calling code is considered appropriate to handle the error because
 * it'll always be a static configuration error.
 *   @param pEvProcId
 * All event processors are identified by a positive integer. Normally this ID is returned
 * by reference in * \a pEvProcId. If the event processor cannot be created then
 * #RTOS_INVALID_EVENT_PROC_ID is returned in * \a pEvProcId.\n
 *   Note, it is guaranteed to the caller that the returned ID is not an arbitrary,
 * meaningless number. Instead, the ID is counted from zero in order of creating event
 * processors. The first call of this function will return 0, the second 1, and so on. This
 * simplifies ID handling in the application code, constants can mostly be applied as the
 * IDs are effectively known at compile time.
 *   @param tiCycleInMs
 * The period time for regularly triggering events in ms.\n
 *   The permitted range is 0..2^30-1. 0 means no regular, timer controlled trigger and the
 * event processor is enabled only for software trigger using rtos_osSendEvent() (permitted
 * for interrupts or other tasks).
 *   @param tiFirstActivationInMs
 * The first trigger by timer event in ms after start of kernel. The permitted range is
 * 0..2^30-1.\n
 *   Note, this setting is useless if a cycle time zero in \a tiCycleInMs specifies a non
 * regular event. \a tiFirstActivationInMs needs to be zero in this case, too.
 *   @param priority
 * The priority of the event processor in the range 1..UINT_MAX. Different event processors
 * can share the same priority. The priority of an event processor is the priority of all
 * associated tasks at the same time. The execution of tasks, which share the priority will
 * be serialized when they are activated at same time or with overlap.\n
 *   Note the safety constraint that task priorities above #RTOS_MAX_LOCKABLE_TASK_PRIORITY
 * are available only to event processors, which solely have associated tasks that belong
 * to the process with highest process ID in use. (Which is assumed to be the safety
 * process.)\n
 *   Note, the order in which event processors are created can affect the priority in a
 * certain sense. If two event processors are created with same priority and when they at
 * runtime become due at the same OS time tick then the earlier created processor will
 * activate its associated tasks before the later created.
 *   @param minPIDToTriggerThisEvProc
 * Events can be notified by user code, e.g., using rtos_sendEvent(). However, tasks
 * belonging to less privileged processes must not generally have permission to trigger
 * event processors that may activate tasks of higher privileged processes. Since an event
 * processor is not process related, we make the minimum process ID, which is required to
 * notify the event to the processor, an explicitly configured property of the processor.\n
 *   Only tasks belonging to a process with PID >= \a minPIDToTriggerThisEvProc are
 * permitted to trigger this event processor.\n
 *   The range of \a minPIDToTriggerThisEvProc is 0 ... (#RTOS_NO_PROCESSES+1). 0 and 1
 * both mean, all processes may trigger the event processor, (#RTOS_NO_PROCESSES+1) means
 * only OS code can trigger it. (#RTOS_NO_PROCESSES+1) is available as
 * #RTOS_EVENT_PROC_NOT_USER_TRIGGERABLE, too.
 *   @param timerUsesCountableEvents
 * When the OS timer triggers a due event processor then it needs to decide whether to use
 * it as countable or ordinary event. This decision is configured per event but once
 * for ever.\n
 *   \a timerUsesCountableEvents doesn't care for solely SW notified events, i.e., if \a
 * tiCycleInMs is zero.
 *   @param timerTaskTriggerParam
 * For timer triggered event processors, this is the argument of the trigger operation. For
 * countable events, this is the mask specifying the variable storing the multiplicity of
 * the notified event. Timer triggers always use multiplicity 1 per trigger, i.e., per due
 * time. The number of bits set determine, how many triggers can be stored until a task
 * overflow is reported. For example, with \a timerTaskTriggerParam=3, a task overflow
 * would be recorded only, when the event has been found non-idle at four consecutive due
 * times. For countable events, \a timerTaskTriggerParam must not be zero.\n
 *   If \a timerUsesCountableEvents=false then \a timerTaskTriggerParam will be used as
 * task parameter that is delivered to all associated task functions on every successful
 * trigger.
 *   \a timerTaskTriggerParam doesn't care for solely SW triggered event processors, i.e.,
 * if \a tiCycleInMs is zero.
 *   @remark
 * Never call this function after the call of rtos_osInitKernel()!
 *   @remark
 * This function must be called by trusted code in supervisor mode only.
 */
rtos_errorCode_t rtos_osCreateEventProcessor( unsigned int *pEvProcId
                                            , unsigned int tiCycleInMs
                                            , unsigned int tiFirstActivationInMs
                                            , unsigned int priority
                                            , unsigned int minPIDToTriggerThisEvProc
                                            , bool timerUsesCountableEvents
                                            , uint32_t timerTaskTriggerParam
                                            )
{
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    *pEvProcId = RTOS_INVALID_EVENT_PROC_ID;

    /* The number of events is constraint in order to let our mapping tables not grow more
       thatreasonable */
    if(pIData->noEventProcs >= RTOS_MAX_NO_EVENT_PROCESSORS)
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
    if(minPIDToTriggerThisEvProc > RTOS_NO_PROCESSES+1)
        return rtos_err_eventNotTriggerable;

    /* For countable events, the task trigger parameter has the meaning of the counter bit
       mask and must not be zero. */
    if(timerUsesCountableEvents &&  timerTaskTriggerParam == 0u)
        return rtos_err_badCountableTimerEventMask;

    /* Insert the new event into the array and initialize the data structure. The position
       to insert is such that the events appear in order of decreasing priority. */
    unsigned int idxNewEv, v;
    for(idxNewEv=0; idxNewEv<pIData->noEventProcs; ++idxNewEv)
    {
        if(getEventProcByIdx(idxNewEv)->priority < priority)
            break;
    }

    for(v=pIData->noEventProcs; v>idxNewEv; --v)
        *getEventProcByIdx(v) = *getEventProcByIdx(v-1);

    rtos_eventProcDesc_t *pNewEvent = getEventProcByIdx(idxNewEv);
    pNewEvent->tiCycleInMs = tiCycleInMs;
    pNewEvent->tiDue = tiFirstActivationInMs;
    pNewEvent->priority = priority;
    pNewEvent->minPIDForTrigger = minPIDToTriggerThisEvProc;
    pNewEvent->noActivationLoss = 0u;
    pNewEvent->taskAry = NULL;
    pNewEvent->noTasks = 0u;
    pNewEvent->taskParam = 0u;
    pNewEvent->timerUsesCountableEvs = timerUsesCountableEvents;
    pNewEvent->timerTaskTriggerParam = timerTaskTriggerParam;
    pNewEvent->eventCounterMask = 0u;
    pNewEvent->offsNextEvProcSamePrio = 0;
    pNewEvent->offsNextEvProcLowerPrio = 0;

    const unsigned int idNewEv = pIData->noEventProcs++;
    assert(pIData->noEventProcs > 0);

    /* Update the mapping of (already issued, publically known) event IDs onto the (now
       modified) internal arry index. */
    pIData->mapEvProcIDToPtr[idNewEv] = getEventProcByIdx(idxNewEv);
    for(v=0; v<idNewEv; ++v)
        if(pIData->mapEvProcIDToPtr[v] >= getEventProcByIdx(idxNewEv))
            ++ pIData->mapEvProcIDToPtr[v];

    /* Install the guard element at the end of the list. Essential is a priority value of
       zero, i.e., below any true, scheduled task. */
    /// @todo Effectively, this object can be considered the descriptor of the idle task.
    // At other location we wonder, whether we should offer idle tasks which are owned by
    // the different processes. It would be straightforward to use this object, and
    // particularly its field taskAry to implement this. Instead of returning from the
    // initKernel we would start a first scheduler instance. An ugly detail: Without
    // modification, the normal scheduling would clear the state "triggered" after
    // execution of all associated tasks. Is it worth to let the normal scheduling suffer
    // from an additional run-time condition just to make the idle concept work in the
    // sketched way?
    _Static_assert( RTOS_EVENT_PROC_NOT_USER_TRIGGERABLE
                    <= UINT_T_MAX(pNewEvent->minPIDForTrigger)
                  , "Integer overflow"
                  );
    *getEventProcByIdx(pIData->noEventProcs) =
            (rtos_eventProcDesc_t){ .tiCycleInMs = 0u
                                  , .tiDue = 0u
                                  , .priority = 0u
                                  , .minPIDForTrigger = RTOS_EVENT_PROC_NOT_USER_TRIGGERABLE
                                  , .taskAry = NULL
                                  , .noTasks = 0u
                                  , .timerUsesCountableEvs = false
                                  , .timerTaskTriggerParam = 0u
                                  , .eventCounterMask = 0u
                                  , .taskParam = 0u
                                  , .noActivationLoss = 0u
                                  , pNewEvent->offsNextEvProcSamePrio = 0
                                  , pNewEvent->offsNextEvProcLowerPrio = 0
                                  };

#ifdef DEBUG
    for(v=1; v<=pIData->noEventProcs; ++v)
        if(getEventProcByIdx(v)->priority > getEventProcByIdx(v-1)->priority)
            return rtos_err_invalidEventPrio; /* Actually an internal implementation error */
#endif
    /* Assign the next available array index as publically known event ID. */
    *pEvProcId = idNewEv;

    return rtos_err_noError;

} /* End of rtos_osCreateEventProcessor */


/**
 * A simplified call of rtos_osCreateEventProcessor() to create an event processor, which
 * won't be triggered by timer events. (The function internally calls
 * rtos_osCreateEventProcessor() with \a tiCycleInMs=0.) Most of the function arguments of
 * rtos_osCreateEventProcessor() are meaningless for event processors triggered by software
 * only, which makes the use of this API more appropriate.
 *   @param pEvProcId
 * The event processor ID is returned by reference. See rtos_osCreateEventProcessor() for
 * details. 
 *   @param priority
 * The priority of the event processor. See rtos_osCreateEventProcessor() for details.
 *   @param minPIDToTriggerThisEvProc
 * Privileges management for this event processor. See rtos_osCreateEventProcessor() for
 * details.
 */
rtos_errorCode_t rtos_osCreateSwTriggeredEventProcessor( unsigned int *pEvProcId
                                                       , unsigned int priority
                                                       , unsigned int minPIDToTriggerThisEvProc
                                                       )
{
    return rtos_osCreateEventProcessor( pEvProcId
                                      , /* tiCycleInMs */ 0u
                                      , /* tiFirstActivationInMs */ 0u
                                      , priority
                                      , minPIDToTriggerThisEvProc
                                      , /* timerUsesCountableEvents */ false
                                      , /* timerTaskTriggerParam */ 0u
                                      );
} /* rtos_osCreateSwTriggeredEventProcessor */



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
 * deadline monitoring, i.e., it is a world time budget, not an execution time budget.\n
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
    return registerTask(EVENT_PROC_ID_INIT_TASK, (uintptr_t)initTaskFct, PID, tiTaskMaxInUs);

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
 *   @param idEventProc
 * The task is activated by an event. This call associates the registered task with an
 * already created event processor. See rtos_osCreateEventProcessor().\n
 *   The order of registration of several tasks (both, OS and user mode) with one and the
 * same event processor matters. The tasks will be acivated in order of registration
 * whenever the event processor becomes due or is triggered by software.
 *   @param userModeTaskFct
 * The task function, which is run in process \a PID every time the event processor \a
 * idEventProc becomes due of is triggered by software.\n
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
 * the task, i.e., each run of \a userModeTaskFct(). The budget relates to deadline
 * monitoring, i.e., it is a world time budget, not an execution time budget.\n
 *   Deadline monitoring is supported up to a maximum execution time of
 * #RTOS_TI_DEADLINE_MAX_IN_US Microseconds.\n
 *   A value of zero means that deadline monitoring is disabled for the task.\n
 *   @remark
 * Never call this function after the call of rtos_osInitKernel()!
 *   @remark
 * This function must be called by trusted code in supervisor mode only.
 */
rtos_errorCode_t rtos_osRegisterUserTask( unsigned int idEventProc
                                        , int32_t (*userModeTaskFct)( uint32_t PID
                                                                    , uint32_t taskParam
                                                                    )
                                        , unsigned int PID
                                        , unsigned int tiTaskMaxInUs
                                        )
{
    /* OS task functions have another signature and should be registered with the other
       function rtos_osRegisterOSTask(). */
    if(PID == 0)
        return rtos_err_badProcessId;

    return registerTask(idEventProc, (uintptr_t)userModeTaskFct, PID, tiTaskMaxInUs);

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
 *   @param idEventProc
 * The task is activated by an event. This call associates the registered task with an
 * already created event processor. See rtos_osCreateEventProcessor().\n
 *   The order of registration of several tasks (both, OS and user mode) with one and the
 * same event processor matters. The tasks will be acivated in order of registration
 * whenever the event processor becomes due or is triggered by software.
 *   @param osTaskFct
 * The task function, which is run in the OS context every time the event processor \a
 * idEventProc becomes due or is triggered by software.
 *   @remark
 * Never call this function after the call of rtos_osInitKernel()!
 *   @remark
 * This function must be called by trusted code in supervisor mode only.
 */
rtos_errorCode_t rtos_osRegisterOSTask( unsigned int idEventProc
                                      , void (*osTaskFct)(uint32_t taskParam)
                                      )
{
    return registerTask(idEventProc, (uintptr_t)osTaskFct, /* PID */ 0, /* tiTaskMaxInUs */ 0);

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
         to event processors having that priority. So far we chose the most time efficient
         technique, a direct lookup table, but any other technique would be fine, too. */
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

    /* The pointer pIData->pNextEvProcToSchedule is either unset or it points to the event
       processor of highest priority which has been triggered but which cannot be scheduled
       yet because we are still in an ISR. The value "unset" need to maintain the ordering
       of pointers, the higher the value the lesser the priority of an event processor it
       points to. NULL would not fulfill both condition and therefore require additional
       runtime code. We choose UINT_MAX as indication of "unset". */
    pIData->pNextEvProcToSchedule = (rtos_eventProcDesc_t*)(uintptr_t)-1;

    pIData->pEndEvProc     =
    pIData->pCurrentEvProc = getEventProcByIdx(pIData->noEventProcs);
    pIData->currentPrio    = 0;

    /* The user must have registered at minimum one task and must have associated it with an
       event processor. */
    if(pIData->tiOsStep != 0)
        errCode = rtos_err_configurationOfRunningKernel;
    else if(pIData->noEventProcs == 0  ||  pIData->noTasks == 0)
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
        unsigned int idxEvProc;
        for(idxEvProc=0; idxEvProc<pIData->noEventProcs; ++idxEvProc)
        {
            const rtos_eventProcDesc_t * const pEvProc = getEventProcByIdx(idxEvProc);
            const unsigned int noAssociatedTasks = (unsigned int)pEvProc->noTasks;

            /* Check task configuration: Event Processors without an associated task are
               useless and point to a configuration error. */
            if(noAssociatedTasks == 0)
                errCode = rtos_err_evProcWithoutTask;

            /* If an event processor has a priority above #RTOS_MAX_LOCKABLE_TASK_PRIORITY
               then only those tasks can be associated, which belong to the process with
               highest PID in use or OS tasks. This is a safety constraint. */
            if(pEvProc->priority > RTOS_MAX_LOCKABLE_TASK_PRIORITY)
            {
                for(idxTask=0; idxTask<noAssociatedTasks; ++idxTask)
                {
                    const unsigned int PID = pEvProc->taskAry[idxTask].PID;
                    if(PID > 0  &&  PID != maxPIDInUse)
                        errCode = rtos_err_highPrioTaskInLowPrivPrc;
                }
            } /* End if(Unblockable priority is in use by event processor) */
        } /* for(All registered event processors) */
    }

    /* The scheduling of events is supported by a link pointer, which points the scheduler
       to the next event processor to check after the event processor had been processed.
       This next event processor is either the (cyclically) next one in a group of event
       processors of same priority or the first successor with lower priority. */
    if(errCode == rtos_err_noError)
    {
        unsigned int lastPrioMap = sizeOfAry(pIData->mapPrioToEvProc) - 1u;
        assert(pIData->noEventProcs >= 1u);
        unsigned int idxEvProcFirstInPrio = 0u;
        unsigned int priority = getEventProcByIdx(idxEvProcFirstInPrio)->priority;
        for(unsigned int idxEvProc=1u; idxEvProc<=pIData->noEventProcs; ++idxEvProc)
        {
            const unsigned int nextPriority = getEventProcByIdx(idxEvProc)->priority;
            
            /* Is this event processor the first one of the group of next lower priority? */
            if(nextPriority < priority)
            {
                /* We have identified a group of event processors of same priority prio. */
            
                /* The cyclic pointers are installed for all members of the group.
                     Note, we check for potential overflow of the links in a static compile
                   time assertion, which requires a too weak condition. If this condition
                   fails, then the precise condition for a runtime assertion would liekly
                   not fail. However, the static assertion is sufficient to avoid overflows
                   and it'll not fail in any reasonable configuration. */
                _Static_assert( (RTOS_MAX_NO_EVENT_PROCESSORS) * sizeof(rtos_eventProcDesc_t)
                                < INT_T_MAX(int16_t)
                              , "Overflow of offset"
                              );
                assert(idxEvProc > idxEvProcFirstInPrio);
                unsigned int idxInGrp;
                for(idxInGrp=idxEvProcFirstInPrio; idxInGrp<idxEvProc-1u; ++idxInGrp)
                {
                    getEventProcByIdx(idxInGrp)->offsNextEvProcSamePrio =
                                                        (int16_t)sizeof(rtos_eventProcDesc_t);
                    getEventProcByIdx(idxInGrp)->offsNextEvProcLowerPrio =
                            (int16_t)((idxEvProc - idxInGrp) * sizeof(rtos_eventProcDesc_t));
                }
                getEventProcByIdx(idxInGrp)->offsNextEvProcSamePrio = 
                                        (int16_t)-(int)((idxEvProc - idxEvProcFirstInPrio - 1)
                                                        * sizeof(rtos_eventProcDesc_t)
                                                       );
                getEventProcByIdx(idxInGrp)->offsNextEvProcLowerPrio = 
                                                        (int16_t)sizeof(rtos_eventProcDesc_t);

                /* Add some entries to the map from priority to event processor. Assertions
                   are fine to make the code safe - the according object properties have
                   already been validated when creating the event processor objects. */
                do
                {
                    assert(lastPrioMap < sizeOfAry(pIData->mapPrioToEvProc));
                    pIData->mapPrioToEvProc[lastPrioMap]
                                                    = getEventProcByIdx(idxEvProcFirstInPrio);
                }
                while(lastPrioMap-- > priority);
                
                priority = nextPriority;
                idxEvProcFirstInPrio = idxEvProc;
            }
            else
                assert(nextPriority == priority);

        } /* End for(All event processors) */
        
        assert(priority == 0u);

        /* The remaining entries of the map priority-to-evProc are initialized to point to
           the guard object. However, referencing these entries is an implementation
           error. */
        rtos_eventProcDesc_t * const pEvProcGuard = getEventProcByIdx(pIData->noEventProcs);
        do
        {
            assert(lastPrioMap < sizeOfAry(pIData->mapPrioToEvProc));
            pIData->mapPrioToEvProc[lastPrioMap] = pEvProcGuard;
        }
        while(lastPrioMap-- > 0u);

    } /* End if(No initialization error yet) */

    /* After checking the static configuration, we can enable the dynamic processes.
       Outline:
       - Disable all processes (which is their initial state). Once we enable the
         interrupts, the I/O drivers start working and they may invoke callbacks into the
         processes. The execution of these callbacks will be inhibited
       - Initialize the memory protection. This needs to be done before the very first user
         mode task function has the chance to become started. (The very first user mode task
         functions need to be the process initialization tasks.)
       - Disable the scheduler to trigger any event processors (which is its initial
         state). Triggering event processors would not cause any user tasks to execute
         (processes still disabled) but their due counters would already run and the
         configured startup conditions would not be met later when enabling the processes
       - Globally enable interrupt processing. I/O drivers and OS clock tick are running.
         This is a prerequisite for the deadline monitoring, which we want to have in place
         already for the init tasks
       - Sequentially execute all configured process initialization tasks. There are no
         crosswise race condition and nor with user tasks or I/O driver callbacks. Note,
         interrupts are already running and cause race conditions. Moreover, they could
         make use of rtos_osSendEvent() and if an OS task is associated with the triggered
         event processor then there would be race conditions with this OS task, too
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
       interrupts are configured but global interrupt processing is not enabled yet, but it
       could: The processes are still in state disabled and no user tasks can be activated,
       neither by the scheduler's timer task nor by an I/O driver using rtos_osRunTask(). */

    /* Run all process initialization tasks in order of increasing PID. A process with
       higher privileges is initialized after another with less privileges. The higher
       privileged could override settings made by its predecessor.
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
            const rtos_taskDesc_t * const pInitTaskCfg = &pIData->initTaskCfgAry[idxP];
            if(pInitTaskCfg->addrTaskFct != 0)
            {
                if(isProcessConfiguredAry[idxP])
                {
                    /* Everything is alright. Run the initialization task. A negative
                       return value is defined to be an error. (This needs to be considered
                       by the implementation of the task.) */
                    int32_t resultInit;
                    if(pInitTaskCfg->PID == 0)
                    {
                        /* OS initialization function: It is a normal sub-function call; we
                           are here in the OS context. */
                        resultInit = ((int32_t (*)(void))pInitTaskCfg->addrTaskFct)();
                    }
                    else
                    {
                        /* The initialization function of a process is run as a task in
                           that process, which involves full exception handling and
                           possible abort causes. */
                        rtos_osReleaseProcess(/* PID */ idxP, /* isInitOnly */ true);
                        if(pInitTaskCfg->tiTaskMax > 0u)
                            rtos_osResumeAllInterrupts();

                        resultInit = rtos_osRunInitTask(pInitTaskCfg);

                        rtos_osSuspendAllInterrupts();
                        rtos_osSuspendProcess(/* PID */ idxP);
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
        /* Process state: Set to running (not zero) only if configuration generally okay. */
        unsigned int idxP;
        for(idxP=1; idxP<1+RTOS_NO_PROCESSES; ++idxP)
            if(isProcessConfiguredAry[idxP])
                rtos_osReleaseProcess(/* PID */ idxP, /* isInitOnly */ false);

        /* Release scheduler. */
        pIData->tiOsStep = (unsigned long)GET_CORE_VALUE( RTOS_CLOCK_TICK_IN_MS
                                                        , rtos_osGetIdxCore()
                                                        );
        rtos_osResumeAllInterrupts();
    }

    /* @todo Shall we offer idle tasks per process? If so, we cannot leave the routine but
       would need to enter an infinite loop - and had to offer such a function for OS, too. */

    return errCode;

} /* End of rtos_osInitKernel */




/**
 * Notify an event to an event processor to let it activate all associated tasks.\n
 *   This function can be called from any OS task or ISR. However, if the calling task
 * belongs to the set of tasks associated with \a idEventProc, then it'll have no effect
 * but a recorded activation loss; using this API, an event can be re-triggered only after
 * all associated tasks have been completed. There is no activation queueing. The function
 * returns \a false in this case.\n
 *   Note, the system respects the priorities of the activated tasks. If a task of priority
 * higher than the activating task is activated by the triggered event processor then the
 * activating task is immediately preempted to the advantage of the activated task.
 * Otherwise the activated task is chained and executed after the activating task.
 *   @return
 * There is no activation queuing. Consequently, notifying the event can fail if at least
 * one of the associated tasks has not yet completed after the previous trigger of the
 * event. The function returns \a false and the activation loss counter of the event
 * processor is incremented. (See rtos_getNoActivationLoss().) In this situation, the new
 * trigger is entirely lost, i.e., none of the associated tasks will be activated by the
 * event and \a the value of taskParam won't be seen by the task functions.
 *   @param idEventProc
 * The ID of the event processor to activate as it had been got by the creation call for
 * that processor. (See rtos_osCreateEventProcessor() and
 * rtos_osCreateSwTriggeredEventProcessor().)
 *   @param taskParam
 * All associated tasks will receive this value, when they are called because of this
 * trigger.\n
 *   The value is ignored if the function returns \a false.
 *   @remark
 * The function is indented to start a non periodic task by application software trigger
 * but can be applied to periodic timer tasks, too. In which case the task function of the
 * cyclic task would be invoked once additionally. Note, that an event activation loss is
 * not unlikely in this case; the cyclic task may currently be busy. For this purpose, the
 * use of countable events is probably the better choice. See rtos_osSendEventCountable().
 *   @remark
 * Events notified with this API are called "ordinary". In most situations, the use of
 * countable events will perform better, see rtos_osSendEventCountable(). An important
 * exception from this are timer events for ordinary periodic tasks.
 *   @remark
 * It may look like an inconsistent API design if all associated tasks receive the same
 * value \a taskParam. The service could easily offer an API, which provides an individual
 * value to each associated task. The only reason not to do so is the additional overhead
 * in combination with the very few imaginable use cases. In most cases an explicitly
 * triggered event will have just one associated task; events with more than one task will
 * mostly be regular timer tasks, which make rarely use of the task parameter.
 *   @remark
 * It is not forbidden but useless to let a task activate itself by triggering the event
 * processor it is associated with with this API. This will have no effect besides
 * incrementing the activation loss counter for that event processor.
 *   @remark
 * This function must be called from the OS context only. It may be called from an ISR to
 * implement delegation to a user task.
 */
bool rtos_osSendEvent(unsigned int idEventProc, uint32_t taskParam)
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
       expects if it sets the lock. We catch this situation by assertion.
         If this assertion fires then there's likely a misunderstanding of the semantics of
       rtos_osSendEvent() in the calling code. */
    assert(isInterrupt || !rtos_osGetAllInterruptsSuspended());

    return osSendEvent( getEventProcByID(idEventProc)
                      , /* noCountableTriggers */ 0u
                      , taskParam
                      , isInterrupt
                      );
} /* End of rtos_osSendEvent */



/**
 * Notify a countable event to activate all associated tasks. Event processors can be used
 * with countable or ordinary events. Please note, the event processor as such is neither
 * countable nor ordinary, but it can be triggered in either way. (For ordinary, see
 * rtos_osSendEvent().)\n
 *   For countable events, the multiplicity of notification is recorded and forwarded to
 * the associated task functions by means of their task parameter. Effectively, this is a
 * kind of activation queing, even if it doesn't mean that an associated task is guaranteed
 * to become activated as often as this function is called.\n
 *   Up to a certain maximum, the number of invocations of this function is counted and
 * stored. The stored number is handed over as task parameter to all associated tasks, when
 * they are activated the next time. If the event processor is idle, when this function is
 * called, then the count is one and this is what the task functions will get. If it is not
 * idle then it depends. If the next call(s) of this function happen before the event
 * processor becomes idle again then the stored multiplicity is 2, 3, 4, ... As soon as the
 * event processor becomes idle, its tasks are activated and their task parameter will
 * carry the 2, 3, 4, ..., respectively. In this example, if the event processor becomes
 * idle after 4 calls, then the tasks will be activated not 4 times but just once with a
 * reported multiplicity of 4 triggers. No activation loss is recorded for the event
 * processor, as long as the counter for storing the multiplicity of the triggers doesn't
 * overflow.\n
 *   Using this API for triggering an event, the associated tasks will strictly know, how
 * many notifications of the event occurred - even if the number of task activations may be
 * lesser.\n
 *   Note, the system respects the priorities of the activated tasks. If a task of priority
 * higher than the activating task is activated by the notified event then the activating
 * task is immediately preempted to the advantage of the activated task. Otherwise the
 * activated task is chained and executed after the activating task.
 *   @return
 * Notifying the countable event fails if the counter for the multiplicity of the event
 * overflows. The implementation limit of this counter is determined by the mask \a evMask.
 * If n bits are set in \a evMask then the function may be called up to 2^n-1 times while
 * the event processor is not idle. The 2^n-th call will be first one returning \a false
 * and only now, an activation loss will be recorded for the event processor.\n
 *   As long as the caller gets \a true, he can be sure that the multiplicity of all
 * notifications so far will be properly delivered to the associated task functions.
 *   @param idEventProc
 * The ID of the event processor to activate as it had been got by the creation call for
 * that processor. (See rtos_osCreateEventProcessor() and
 * rtos_osCreateSwTriggeredEventProcessor().)
 *   @param evMask
 * Definition of the bit mask designating the notified event. See above for details.
 *   @remark
 * The function is indented to start a non periodic task by application software trigger
 * but can be applied to periodic timer tasks, too. In which case the task function of the
 * cyclic task would be invoked once additionally. Note, that a non-idle event processor is
 * not unlikely in this case; \a evMask should spent a sufficient number of bits to
 * temporarily store the multiplicity of notifications-while-non-idle.
 *   @remark
 * This function must be called from the OS context only. It may be called from an ISR to
 * implement delegation to a user task.
 */
bool rtos_osSendEventCountable(unsigned int idEventProc, uint32_t evMask)
{
    /* IRQ handling: See comments in rtos_osSendEvent(). */
    const bool isInterrupt = rtos_osIsInterrupt();
    assert(isInterrupt || !rtos_osGetAllInterruptsSuspended());

    return osSendEvent( getEventProcByID(idEventProc)
                      , /* noCountableTriggers */ 1u
                      , evMask
                      , isInterrupt
                      );
} /* rtos_osSendEventCountable */


/**
 * A countable event can be notified with multiplicity greater than one. If the event
 * processor is idle then the associated tasks are activated and they will receive the
 * multiplicity \a count in their task parameter. If the event processor is not idle then
 * the accumulator for the event will be incremented either by \a count or up to its
 * implementation maximum, whatever comes first. The resulting, accumulated count will be
 * forwarded to the task functions as soon as the processor becomes idle again.
 *   @return
 * Get \a false if the accumulator for the event overflows (and saturates at its maximum).
 * Get \a true otherwise.
 *   @param idEventProc
 * The ID of the event processor to activate as it had been got by the creation call for
 * that processor. (See rtos_osCreateEventProcessor() and
 * rtos_osCreateSwTriggeredEventProcessor().)
 *   @param evMask
 * Definition of the bit mask designating the notified event. See
 * rtos_osSendEventCountable() for details.
 *   @param count
 * The notified multiplicity of the event.\n
 *   The complexity of the operation is O(count), which means that it is intended for
 * rather small multiplicities. To avoid undesired blocking of the function due to
 * excessive high multiplicities, the implementation type for the argument has been chosen
 * 8 Bit, which strictly limits the range of \a count to 1..255.\n
 *   \a count = 0 is not allowed and caught by assertion.
 *   @remark
 * The behavior of this function is similar to calling rtos_osSendEventCountable() for \a
 * count times. The result of rtos_osSendEventMultiple() would then be the result of the
 * very last call of rtos_osSendEventCountable().
 *   @remark
 * This function must be called from the OS context only. It may be called from an ISR to
 * implement delegation to a user task.
 */ 
bool rtos_osSendEventMultiple(unsigned int idEventProc, uint32_t evMask, uint8_t count)
{
    /* IRQ handling: See comments in rtos_osSendEvent(). */
    const bool isInterrupt = rtos_osIsInterrupt();
    assert(isInterrupt || !rtos_osGetAllInterruptsSuspended());

    /* This function must not be used with an increment of zero counts: This is useless and
       therefore used as flag to say "old style" trigger, i.e., other behavior and
       deviating interpretation of evMask. */
    assert(count > 0u);

    return osSendEvent( getEventProcByID(idEventProc)
                      , /* noCountableTriggers */ count
                      , evMask
                      , isInterrupt
                      );
} /* rtos_osSendEventMultiple */


/**
 * System call handler implementation to notify an event (and to activate the associated
 * tasks). Find more details in rtos_osSendEvent(), rtos_osSendEventCountable() and
 * rtos_osSendEventMultiple().
 *   @return
 * \a true if notification was possible, \a false otherwise.
 *   @param pidOfCallingTask
 * Process ID of calling user task. The operation is permitted only for tasks belonging to
 * those processes, which have an ID that is greater of equal to the minimum specified for
 * the event processor in question. Otherwise an exception is raised, which aborts the
 * calling task.
 *   @param idEventProc
 * The ID of the event processor to trigger. This is the ID got from
 * rtos_osCreateEventProcessor(). 
 *   @param evMaskOrTaskParam
 * If \a noCountableTriggers is zero then the system call branches into rtos_osSendEvent()
 * and \a evMaskOrTaskParam is argument \a taskParam. All associated tasks will receive
 * this value, when they are called because of this trigger but the value is lost if the
 * function returns \a false.\n
 *   If \a noCountableTriggers is greater than zero \a evMaskOrTaskParam is argument \a
 * evMask of the other functions. The value specifies the variable used for accumulating
 * the countable event and must not be zero.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
uint32_t rtos_scFlHdlr_sendEvent( unsigned int pidOfCallingTask
                                , unsigned int idEventProc
                                , uint8_t noCountableTriggers
                                , uint32_t evMaskOrTaskParam
                                )
{
    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    if(idEventProc < pIData->noEventProcs
       &&  (evMaskOrTaskParam != 0u  ||  noCountableTriggers == 0u)
      )
    {
        rtos_eventProcDesc_t * const pEvProc = getEventProcByID(idEventProc);
        if(pidOfCallingTask >= (unsigned int)pEvProc->minPIDForTrigger)
        {
            return (uint32_t)osSendEvent( pEvProc
                                        , noCountableTriggers
                                        , evMaskOrTaskParam
                                        , /* isInterrupt */ false
                                        );
        }
    }

    /* The user specified event ID is not in range or the calling process doesn't have the
       required privileges. Either is a severe user code error, which is handled with an
       exception, task abort and counted error.
         Note, this function does not return. */
    rtos_osSystemCallBadArgument();

} /* End of rtos_scFlHdlr_sendEvent */



/**
 * This function implements the main part of the scheduler, which actually runs tasks. It
 * inspects all event processors, whether they have been triggered in an ISR or system call
 * handler and execute the associated tasks if furthermore the priority conditions are
 * fullfilled.
 *   The function is called from the common part of the assembly implementation of the ISRs
 * and from all system call handlers, which could potentially lead to the start of tasks.\n
 *   This function is entered with all interrupt processing disabled (MSR[ee]=0).
 *   @param
 * The caller (likely osSendEvent(), immediately or postponed) usually knows, which is the
 * recently triggered event processor, which has to be handled by the scheduler. This event
 * processor is provided by reference as a hint so that the scheduler doesn't need to look
 * for the event processor.
 */
SECTION(.text.ivor.rtos_osProcessTriggeredEvProcs) void rtos_osProcessTriggeredEvProcs
                                                               (rtos_eventProcDesc_t *pEvProc)
{
    /* This function and particularly this loop is the essence of the task scheduler. There
       are some tricky details to be understood.
         This function is called as a kind of "on-exit-hook" of any interrupt, which makes
       use of the rtos_osSendEvent() service. (Actually, this includes user tasks, which
       run the software interrupt rtos_sendEvent().) It looks for the triggered event
       processor and runs the associated tasks if it has a priority higher then the
       priority of the currently running task.
         The operation looks uncomplicated for an event processor of higher priority. We
       acknowledge the event and run the tasks. Looking for and acknowleding means a
       read-modify-write operation and since the event processors can at any time be
       accessed by interrupts of higher priority we need a critical section for this.
         First complexity is an interrupt, which triggers another event processor while we
       are processing the tasks of the first one. If this has in turn a higher priority
       then it's no new consideration but just a matter of recursive invocation of this
       same function. However, if it has a priority lower than that of the event processor
       in progress (and its tasks), then we (and not the preempting context, which triggers
       the event processor) are obliged to run the tasks of this event processor, too, but
       - because of the lower priority - only later, after the current set of tasks. (Note,
       "later", there is no HW/SW-interrupt any more to get the new event(s) be processed -
       so we need a loop here to not forget those events.) The tricky thing is how to span
       the critical sections:
         If we find the first event processor (searching from highest towards lower
       priorities) then we apply the CS just to acknowledge the event but bringing the
       event processor from idle into "in progress". When done with all the tasks of the
       event processor we normally release the event processor; we change the status from
       "in progress" to "idle" - of course again in a CS. The exception from the "normally"
       are countable events. While being in progress, the processor can be re-triggered by
       new multiplicities of the same event. In this case, the processor returns only to
       state "triggered". This CS for this state change must be merged with the CS at the
       beginning of the next cycle, the CS to acknowledge the next found event. The reason
       why:
         As soon as we release an event processor, it can be triggered again and in
       particular before we have left this function and killed its stack frame (a stack
       frame of significant size as this function still is element of an ISR). The newly
       triggered event processor would mean a recursive call of this function, so another
       stack frame for the same event. The same could then happen to the recursive function
       invocation and so forth - effectively there were no bounds anymore for the stack
       consumption, which is a fatal risk. Merging the CSs for releasing event processor A
       and acknowledging event B (of lower priority) means that the stack frame of this
       invokation is inherited by the next processed event processor B before a recursive
       call can process the next occurance of A. Which is alright; this leads to the
       pattern that there can be outermost one stack frame per event processor priority and
       this is the possible minimum.
         The same consideration requires that the CS for the final release of the event
       processor must not be left before return from the function. Return from the function
       still means several instructions until the stack frame is killed and event setting
       in this phase is just the same as outlined for the loop cycle-to-cycle situation.
       Actually, the final CS must not be ended before the stack frame has been killed,
       effectively at the very end of the ISR, with the rfi instruction.
         Another consideration makes it useful that we are already inside the first
       acknowledge-CS when entering the function. This CS includes the decision (in
       sendEvent), whether or not a recursive scheduler call is required. Being here, and
       because of the CS, this information is still coherent with the event processors'
       state. We can place some assertions, the behavior is more transparent and the
       implementation more reliable. Without an CS we could see this: Event Processor A is
       set and makes this scheduler invoked. Event Processor B can be triggered before the
       scheduler finds the due event processor. It is preempted by a recursive scheduler
       invocation. The preempting scheduler would handle both event processors, B first
       then A. After the preemption the event processor A is no longer due and the
       scheduler would have to return without doing anything. Which is neither a problem
       nor an advantage (same overall effort and timing), but there are less invariants for
       checking. Note, this is still an option if minimizing the CS is rated higher than
       transparency of behavior. */

    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();

    assert(pEvProc != NULL  &&  pEvProc != getEventProcByIdx(pIData->noEventProcs));
    
    /* Here, we are inside a critical section. External Interrupt handling is disabled. */
    assert(rtos_osGetAllInterruptsSuspended());

    /* If we were called because of pending, postponed events, which are indicated by
       pIData->pNextEvProcToSchedule then the caller must have acknowledged the request by
       setting the pointer back to "unset". */
    assert((uintptr_t)pIData->pNextEvProcToSchedule == (uintptr_t)-1);

    /* Safe the current state: It'll be updated with each of the event processors, we find
       to be served, but finally we will have to restore these values here. */
    const rtos_eventProcDesc_t * const pCurrentEvProc = pIData->pCurrentEvProc;
    const unsigned int prioAtEntry = pIData->currentPrio;

    /* Basically, we iterate the event processors in order of decreasing priority. To handle
       re-triggering of event processors of same priority in a fair manner, we cyclically
       visit all of them until none of them is still triggered. pDone denotes the beginning
       of a check cycle. The check cycle starts over when we have to shortly leave the CS -
       this can mean newly triggered event processors.
         The entry condition of the loop ensures that launching tasks must not be
       considered for event processors at or below the priority at start of this scheduler
       recursion. This priority level will mostly be because another, earlier call of this
       function, being preempted and currently suspended somewhere deeper on the OS stack,
       which already handles the event processor. It can also happen if the PCP has been
       used to temporarily raise the current priority. This disallows us to serve a
       triggered event processor already now. If we find the priority condition hurt then
       we leave the function still (or again) being in a critical section. */
    rtos_eventProcDesc_t *pDone = NULL;
    assert(pEvProc < pIData->pEndEvProc &&  pEvProc->priority >= prioAtEntry);
    while(pEvProc->priority > prioAtEntry)
    {
        if(pEvProc->state == evState_triggered)
        {
            /* Associated tasks are due and they have a priority higher than all other
               currently activated ones. Before we execute them we need to acknowledge the
               event - only then we may leave the critical section. */
            pEvProc->state = evState_inProgress;

            /* The current priority is changed synchronously with the acknowledge of the
               event. We need to do this still inside the same critical section. */
            pIData->pCurrentEvProc = pEvProc;
            pIData->currentPrio = pEvProc->priority;

            /* Now handle the event processor, i.e., launch and execute all associated
               tasks. This is of course not done inside the critical section. We leave it
               now. */
            rtos_osResumeAllInterrupts();
            launchAllTasksOfEvProc(pEvProc);

            /* The executed tasks can have temporarily changed the current priority, but
               here it needs to be the event processor's priority again.
                 The assertion can fire if an OS task raised the priority using the PCP API
               but didn't restore it again. */
            assert(pIData->currentPrio == pEvProc->priority);

            /* The event processor is entirely processed, we can release it. This must not
               be done before we are again in the next critical section. */
            rtos_osSuspendAllInterrupts();

            if(pEvProc->eventCounterMask != 0u)
            {
                /* The event processor has received more countable events while its
                   associated tasks were executing (or were being preempted by tasks of
                   higher priority). The event processor remains triggered and the new
                   events will be forwarded to the tasks as task parameter. */
                pEvProc->state = evState_triggered;
                pEvProc->taskParam = pEvProc->eventCounterMask;
                pEvProc->eventCounterMask = 0u;
                
                /* The event processor is (still) triggered. So we surely didn't see the
                   first one in the required series of all either not or not any longer
                   triggered ones. */
                pDone = NULL; 
            }
            else
            {
                /* When not re-triggered, the active state is always followed by state
                   idle. */
                pEvProc->state = evState_idle;

                /* The event processor is not triggered any longer and becomes the (new)
                   first one in the required series of all either not or not any longer
                   triggered ones. A potentially elder candidate is dropped as we can have
                   received new events during processing this one. */
                pDone = pEvProc; 
            }
        }
        else 
        {
            /* The event processor is not triggered and we advance to the next one without
               having the CS left. The just checked one is the first one in the required
               series of all either not or not any longer triggered ones. */
            assert(pEvProc->state == evState_idle);
            if(pDone == NULL)
                pDone = pEvProc;
        }        
        
        /* Proceed with successor event processor of same priority. Successor is defined in
           a cyclic manner and will be the same processor again if it is the only one of
           given priority. */
        advanceEvProcToSuccesorSamePrio(&pEvProc);

        if(pEvProc == pDone)
        {
            /* Without leaving the CS, we have visited all event processors and found them
               not triggered. We can proceed with the first processor from the next lower
               priority. */
            advanceEvProcToSuccesorLowerPrio(&pEvProc);

            /* A deeper priority level requires a new check cycle of all event processors
               on this new level. */
            pDone = NULL;
        }
    } /* while(All event procs of prio, which is to be handled by this scheduler invocation) */

    /* Here we are surely still or again inside a critical section. */

    /* Restore the initial state. */
    pIData->pCurrentEvProc = pCurrentEvProc;
    pIData->currentPrio = prioAtEntry;

} /* End of rtos_osProcessTriggeredEvProcs */


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
 * tasks, which should be locked, i.e., which compete for the resource or critical section
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
 * All tasks up to and including this priority will be locked, i.e., they won't be executed
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
 * level below the configured task priority (i.e., the priority inherited from the triggering
 * event processor) will have unpredictable consequences.
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
        /* Identify the event processors, which could possibly require the recursive call
           of the scheduler.
             Note, there is a significant difference in the implementation here for the OS
           tasks and the system call that implements the same concept for the user tasks.
           The OS code just identifies the event processors that may have been triggered
           meanwhile and calls the scheduler to let it decide whether there's really
           something to do. Often, this won't be the case. (Which is possible for the other
           reason, too, that the check code is not inside the critical section).
             The system call implementation really figures out whether there is at least
           one event processor that requires scheduling. It looks at the state of all
           possible candidates. Effectively, it re-implements part of the scheduler itself.
           The reason is the significant overhead, which results from calling a C function
           from a system call. In the majority of cases, the system call will find that
           calling the scheduler is not needed so that this effectively is a significant
           optimization. The OS code here would not benefit from the same strategy. */
        rtos_eventProcDesc_t * const pEvProcToSchedulePossibly =
                                            rtos_osGetEvProcByPriority(pIData->currentPrio);
        pIData->currentPrio = resumeDownToThisTaskPriority;

        rtos_osSuspendAllInterrupts();
        /* Note, because check and change of the current prio are not inside the critical
           section it can easily be that the call of the scheduler is already obsolete.
           This doesn't matter, not even with respect to overhead and the number of
           function invocations. Not taking check and change into the CS just means to have
           a smaller CS. */
        rtos_osProcessTriggeredEvProcs(pEvProcToSchedulePossibly);
        rtos_osResumeAllInterrupts();
    }
} /* rtos_osResumeAllTasksByPriority */



/**
 * An event processor, which becomes due may not be able to activate all its associated
 * tasks because they didn't terminate yet after their previous activation. It doesn't
 * matter if this happens because a cyclic task becomes due or because the event processor
 * has been triggered by software (e.g., using rtos_sendEvent()). The scheduler counts the
 * failing activations on a per event processor base. The current value can be queried with
 * this function.
 *   @return
 * Get the current number of triggers of the given event processor, which have failed since
 * start of the RTOS scheduler. The counter is saturated and will not wrap around.\n
 *   The returned count can be understood as number of task overrun events for all
 * associated tasks.
 *   @param idEventProc
 * Each event processor has its own counter. The value is returned for the given processor.
 * The range is 0 .. number of registered event processors minus one (double-checked by
 * assertion).
 *   @remark
 * This function can be called from both, the OS context and a user task.
 */
unsigned int rtos_getNoActivationLoss(unsigned int idEventProc)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_getInstancePtr();
    if(idEventProc < pIData->noEventProcs)
    {
        const rtos_kernelInstanceData_t * const pIData = rtos_getInstancePtr();
        assert(idEventProc < pIData->noEventProcs);
        const rtos_eventProcDesc_t *pEvProc = pIData->mapEvProcIDToPtr[idEventProc];
        return pEvProc->noActivationLoss;
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
 * event processor it is associated with.
 *   @remark
 * This function can be called from an OS task only. Any attempt to call it from a user
 * task will cause a privileged exception.
 *   @remark
 * The function must not be called from an ISR. The result would be undefined as there is
 * no event processor, which such a handler function would be associated with. However,
 * with respect to safety or stability, there's no problem in doing this.
 */
unsigned int rtos_osGetTaskBasePriority(void)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    return pIData->pCurrentEvProc->priority;

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
 * event processor, which such a function would be associated with. However, with respect
 * to safety or stability, there's no problem in doing this and therefore no privileges
 * have been connected to this service.
 */
unsigned int rtos_getCurrentTaskPriority(void)
{
    const rtos_kernelInstanceData_t * const pIData = rtos_getInstancePtr();
    return (unsigned int)pIData->currentPrio;

} /* End of rtos_getCurrentTaskPriority */
#endif
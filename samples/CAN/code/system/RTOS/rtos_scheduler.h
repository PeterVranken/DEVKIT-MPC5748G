#ifndef RTOS_SCHEDULER_INCLUDED
#define RTOS_SCHEDULER_INCLUDED
/**
 * @file rtos_scheduler.h
 * Definition of global interface of module rtos_scheduler.c
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
/* Module inline interface
 *   rtos_osGetCurrentInterruptPriority
 *   rtos_osIsInterrupt
 */
 
/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>

#include "MPC5748G.h"
#include "rtos.h"


/*
 * Defines
 */

/** System call index of function rtos_triggerEvent(), offered by this module. */
#define RTOS_SYSCALL_TRIGGER_EVENT                      3


/*
 * Global type definitions
 */


/** The runtime information for a task triggering event.
      Note, we use a statically allocated array of fixed size for all possible events. A
    resource optimized implementation could use an application defined macro to tailor the
    size of the array and it could put the event and task configuration data into ROM.
    (Instead of offering the run-time configuration by APIs.) */
typedef struct rtos_eventDesc_t
{
    /** The current state of the event.\n
          This field is shared with the assembly code. The PCP implementation reads it. */
    enum eventState_t { evState_idle, evState_triggered, evState_inProgress } state;

    /** An event can be triggered by user code, using rtos_triggerEvent(). However, tasks
        belonging to less privileged processes must not generally granted permission to
        trigger events that may activate tasks of higher privileged processes. Since an
        event is not process related, we make the minimum process ID an explicitly
        configured, which is required to trigger this event.\n
          Only tasks belonging to a process with PID >= \a minPIDToTriggerThisEvent are
        permitted to trigger this event.\n
          The range of \a minPIDToTriggerThisEvent is 0 ... (#RTOS_NO_PROCESSES+1). 0 and 1
        both mean, all processes may trigger the event, #RTOS_NO_PROCESSES+1 means only OS
        code can trigger the event. */
    uint8_t minPIDForTrigger;

    /** The set of associated tasks, which are activated by the event, is implemented by an
        array and the number of entries. Here we have the number of entries. */
    uint16_t noTasks;

    /** The set of associated tasks, which are activated by the event, is implemented by an
        array and the number of entries. Here we have the array. */
    const rtos_taskDesc_t * taskAry;

    /** The next due time. At this time, the event will activate the associated task set.*/
    unsigned int tiDue;

    /** The period time of the (cyclic) event in ms. The permitted range is 0..2^30-1.\n
          0 means no regular, timer controlled activation. The event is only enabled for
        software trigger using rtos_triggerEvent() (by interrupts or other tasks). */
    unsigned int tiCycleInMs;

    /** The priority of the event (and thus of all associated user tasks, which inherit the
        prioritry) in the range 1..UINT_MAX. Different events can share the same priority.
        If they do then the execution of their associated tasks will be sequenced when they
        become due at same time or with overlap.\n
          Note, if the event has a priority above #RTOS_MAX_LOCKABLE_TASK_PRIORITY then
        only those tasks can be associated, which belong to the process with highest PID in
        use. This is a safety constraint. */
    unsigned int priority;

    /** The tasks associated with the event can receive an argument. It is send with the
        triggerEvent operation and advanced to the task functions, when they are called
        later. */
    uintptr_t taskParam;

    /** We can't queue events. If at least one task is still busy, which had been activated
        by the event at its previous due time then an event (and the activation of the
        associated tasks) is lost. This situation is considered an overrun and it is
        counted for diagnostic purpose. The counter is saturated and will halt at the
        implementation maximum.
          @remark This field is shared with the external client code of the module. There,
        it is read only. Only the scheduler code must update the field. */
    unsigned int noActivationLoss;

    /** Support the scheduler: If this event has been processed then check event * \a
        this->pNextScheduledEvent as next one. */
    struct rtos_eventDesc_t *pNextScheduledEvent;

} rtos_eventDesc_t;



/*
 * Global data declarations
 */


/*
 * Global inline functions
 */

/**
 * Query the current interrupt priority level.
 *   @return
 * Get the interrupt level in the range 0..15. 1..15 are returned to ISRs running on that
 * level and 0 ist returned if the function is called from an OS task.
 *   @remark
 * This function must be called from the OS context only. User tasks don't have the
 * privileges to call this function.
 */
static ALWAYS_INLINE unsigned int rtos_osGetCurrentInterruptPriority(void)
{
    /* We query the INTC to find out on which interrupt level we are busy. */
    return (unsigned int)*(&INTC->CPR0 + rtos_osGetIdxCore());

} /* End of rtos_osGetCurrentInterruptPriority */



/**
 * Query if we are running code inside an ISR.
 *   @return
 * Get \a true if we are in an External Interrupt and \a false otherwise (i.e. including
 * system calls, which are often considered software interrupts). 
 *   @remark
 * This function must be called from the OS context only. User tasks don't have the
 * privileges to call this function.
 */
static ALWAYS_INLINE bool rtos_osIsInterrupt(void)
{
    /* We query the INTC to find out on which interrupt level we are busy. */
    return rtos_osGetCurrentInterruptPriority() > 0;

} /* End of rtos_osIsInterrupt */




/*
 * Global prototypes
 */

/** Creation of an event. The event can be cyclically triggering or software triggerd. */
rtos_errorCode_t rtos_osCreateEvent( unsigned int *pEventId
                                   , unsigned int tiCycleInMs
                                   , unsigned int tiFirstActivationInMs
                                   , unsigned int priority
                                   , unsigned int minPIDToTriggerThisEvent
                                   , uintptr_t taskParam
                                   );

/** Task registration for user mode or operating system initialization task. */
rtos_errorCode_t rtos_osRegisterInitTask( int32_t (*initTaskFct)(uint32_t PID)
                                        , unsigned int PID
                                        , unsigned int tiMaxInUs
                                        );

/** Task registration for scheduled user mode tasks. */
rtos_errorCode_t rtos_osRegisterUserTask( unsigned int idEvent
                                        , int32_t (*userModeTaskFct)( uint32_t PID
                                                                    , uintptr_t taskParam
                                                                    )
                                        , unsigned int PID
                                        , unsigned int tiMaxInUs
                                        );

/** Task registration for scheduled operating system tasks. */
rtos_errorCode_t rtos_osRegisterOSTask( unsigned int idEvent
                                      , void (*osTaskFct)(uintptr_t taskParam)
                                      );

/** Kernel initialization. */
rtos_errorCode_t rtos_osInitKernel(void);

/** Enter critcal section; partially suspend task scheduling. */
uint32_t rtos_osSuspendAllTasksByPriority(uint32_t suspendUpToThisTaskPriority);
 
/** Leave critical section; resume scheduling of tasks. */
void rtos_osResumeAllTasksByPriority(uint32_t resumeDownToThisTaskPriority);

/** Get the current number of failed task activations since start of the RTOS scheduler. */
unsigned int rtos_getNoActivationLoss(unsigned int idTask);

/** A cyclic or event task can query its base priority. For OS tasks only. */
unsigned int rtos_osGetTaskBasePriority(void);

#if 0
/** A task can query the current task scheduling priority. */
unsigned int rtos_getCurrentTaskPriority(void);
#endif

#endif  /* RTOS_SCHEDULER_INCLUDED */

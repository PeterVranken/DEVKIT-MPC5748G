/**
 * @file rtos_runTask.c
 * Service runtask of the RTOS: A task of process A can run a single-shot task in process
 * B, if it has the privileges to do so.
 *
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   rtos_osGrantPermissionRunTask
 *   rtos_osCheckPermissionRunTask
 *   rtos_scFlHdlr_runTask
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "rtos_runTask_defSysCalls.h"
#include "rtos_runTask.h"
#include "rtos_kernelInstanceData.h"
#include "rtos.h"


/*
 * Defines
 */

/* The user API header file rtos.h doesn't recursively include all headers of all
   implementing files. Therefore it needs to make some assumptions about basically variable
   but normally never changed constants. These assumptions need of course to be double
   checked. We do this here at compile time of the RTOS. */
#if RTOS_IDX_SC_RUN_TASK != RTOS_SYSCALL_RUN_TASK
# error Inconsistent definitions made in C modules and RTOS API header file rtos.h
#endif


/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 

/*
 * Function implementation
 */

/**
 * Operating system initialization function: Grant permissions for using the service
 * rtos_runTask to particular processes. By default, the use of that service is not
 * allowed.\n
 *   By principle, offering service rtos_runTask makes all processes vulnerable, which are
 * allowed as target for the service. A failing, straying process can always hit some ROM
 * code executing the system call with arbitrary register contents, which can then lead to
 * errors in an otherwise correct process.\n
 *   This does not generally break the safety concept, the potentially harmed process can
 * for example be anyway supervised by another, unaccessible supervisory process.
 * Consequently, we can offer the service at least on demand. A call of this function
 * enables the service for a particular pair of calling process and targeted process.
 *   @param pidOfCallingTask
 * The tasks belonging to process with PID \a pidOfCallingTask are granted permission to
 * run a task in another process. The range is 1 .. #RTOS_NO_PROCESSES, which is
 * double-checked by assertion.
 *   @param targetPID
 * The tasks started with service rtos_runTask() may be run in process with PID \a
 * targetPID. The range is 1 .. maxPIDInUse-1, which is double-checked later at kernel
 * initialization time.\n
 *   \a pidOfCallingTask and \a targetPID must not be identical, which is double-checked by
 * assertion.
 *   @remark
 * It would break the safety concept if we permitted the process with highest privileges to
 * become the target of the service. This is double-checked not here (when it is not yet
 * defined, which particular process that will be) but as part of the RTOS startup
 * procedure; a bad configuration can therefore lead to a later reported run-time error.
 *   @remark
 * This function must be called from the OS context only. It is intended for use in the
 * operating system initialization phase. It is not reentrant. The function needs to be
 * called prior to rtos_osInitKernel().
 */
void rtos_osGrantPermissionRunTask(unsigned int pidOfCallingTask, unsigned int targetPID)
{
    /* targetPID <= 3: Necessary but not sufficient to double-check
       "targetPID <= maxPIDInUse-1". */
    assert(pidOfCallingTask >= 1  &&  pidOfCallingTask <= 4
           &&  targetPID >= 1  &&  targetPID <= 3
          );

    /* It may be useful to grant process A the right to run a task in process A. This
       effectively implements a try/catch mechanism. The run task function has the option
       to abort its action at however deeply nested function invocation and using
       rtos_terminateTask(). Control returns to the call of rtos_runTask and the caller
       gets a negative response code as indication (otherwise a positive value computed by
       the called function). The called function belongs to the same process and its
       potential failures can of course harm the calling task, too. This does not break
       our safety concept, but nonetheless, offering a kind of try/catch could easily be
       misunderstood as a kind of full-flavored run-time protection, similar to what we
       have between processes. This potential misunderstanding makes the use of such a
       try/catch untransparent and therefore unsafe. Hence, we do not allow it here. */
    assert(targetPID != pidOfCallingTask);

    /* Caution, the code here depends on macro RTOS_NO_PROCESSES being four and needs to be
       consistent with the implementation of rtos_scFlHdlr_runTask(). */
#if RTOS_NO_PROCESSES != 4
# error Implementation requires the number of processes to be four
#endif
    const unsigned int idxCalledPrc = targetPID - 1u;
    const uint16_t mask = 0x1 << (4u*(pidOfCallingTask-1u) + idxCalledPrc);
    rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    pIData->runTask_permissions |= mask;

} /* End of rtos_osGrantPermissionRunTask */



/**
 * Operating system initialization function: Grant permissions for using the service
 * rtos_runTask to particular processes. By default, the use of that service is not
 * allowed.\n
 *   By principle, offering service rtos_runTask makes all processes vulnerable, which are
 * allowed as target for the service. A failing, straying process can always hit some ROM
 * code executing the system call with arbitrary register contents, which can then lead to
 * errors in an otherwise correct process.\n
 *   This does not generally break the safety concept, the potentially harmed process can
 * for example be anyway supervised by another, unaccessible supervisory process.
 * Consequently, we can offer the service at least on demand. A call of this function
 * enables the service for a particular pair of calling process and targeted process.
 *   @return
 * Get \a true if a task from process \a pidOfCallingTask may run a task in the context of
 * process \a targetPID or \a false if not.
 *   @param pidOfCallingTask
 * The tasks belonging to process with PID \a pidOfCallingTask are granted permission to
 * run a task in another process. The range is 1 .. #RTOS_NO_PROCESSES, which is
 * double-checked by assertion.
 *   @param targetPID
 * The tasks started with service rtos_runTask() may be run in process with PID \a
 * targetPID. The range is 1 .. maxPIDInUse-1, which is double-checked later at kernel
 * initialization time.\n
 *   \a pidOfCallingTask and \a targetPID must not be identical, which is double-checked by
 * assertion.
 *   @remark
 * It would break the safety concept if we permitted the process with highest privileges to
 * become the target of the service. This is double-checked not here (when it is not yet
 * defined, which particular process that will be) but as part of the RTOS startup
 * procedure; a bad configuration can therefore lead to a later reported run-time error.
 *   @remark
 * This function must be called from the OS context only. It is intended for use in the
 * operating system initialization phase. It is not reentrant. The function needs to be
 * called prior to rtos_osInitKernel().
 */
bool rtos_osCheckPermissionRunTask(unsigned int pidOfCallingTask, unsigned int targetPID)
{
    /* This code depends on a specific number of processes, we need a check. The
       implementation requires consistent maintenance with other function
       rtos_osGrantPermissionRunTask() */
#if RTOS_NO_PROCESSES != 4
# error Implementation requires the number of processes to be four
#endif

    /* Now we can check the index of the target process. */
    const unsigned int idxCalledPrc = targetPID - 1u;
    if(idxCalledPrc > 3)
        return false;

    /* No range check is required for pidOfCallingTask. We implicitly get the wanted result
       false if it would be out of range 1..4. */

    const rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
    const uint16_t mask = 0x1 << (4u*(pidOfCallingTask-1u) + idxCalledPrc);
    return (pIData->runTask_permissions & mask) != 0;

} /* End of rtos_osCheckPermissionRunTask */



/**
 * System call handler implementation to create and run a task in another process. Find
 * more details in rtos_osRunTask().\n
 *   Start a user task. A user task is a C function, which is executed in user mode and in
 * a given process context. The call is synchronous; the calling user context is
 * immediately preempted and superseded by the started task. The calling user context is
 * resumed when the task function ends - be it gracefully or by exception/abortion.\n
 *   The started task inherits the priority of the calling user task. It can be preempted
 * only by contexts of higher priority.\n
 *   The function requires sufficient privileges. By default the use of this function is
 * forbidden. The operating system startup code can however use
 * rtos_osGrantPermissionRunTask() to enable particular pairs of calling and target
 * process for this service. The task can generally not be started in the OS context.\n
 *   The function cannot be used recursively. The created task cannot in turn make use of
 * rtos_runTask().
 *   @return
 * The executed task function can return a value, which is propagated to the calling user
 * context if it is positive. A returned negative task function result is interpreted as
 * failing task and rtos_runTask() returns #RTOS_ERR_PRC_USER_ABORT instead.
 * Furthermore, this event is counted as process error in the target process.
 *   @param pidOfCallingTask
 * The ID of the process the task belongs to, which invoked the system call.
 *   @param pUserTaskConfig
 * The read-only configuration data for the task. In particular the task function pointer
 * and the ID of the target process.
 *   @param taskParam
 * This argument is meaningless to the function. The value is just passed on to the started
 * task function. The size is large enough to convey a pointer.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
uint32_t rtos_scFlHdlr_runTask( unsigned int pidOfCallingTask
                              , const rtos_taskDesc_t *pUserTaskConfig
                              , uintptr_t taskParam
                              )
{
    if(!rtos_checkUserCodeReadPtr(pUserTaskConfig, sizeof(rtos_taskDesc_t)))
    {
        /* User code passed in an invalid pointer. We must not even touch the contents.
             Note, the next function won't return. */
        rtos_osSystemCallBadArgument();
    }

    if(rtos_osCheckPermissionRunTask(pidOfCallingTask, /* targetPID */ pUserTaskConfig->PID))
    {
        rtos_kernelInstanceData_t * const pIData = rtos_osGetInstancePtr();
        
        /* We forbid recursive use of this system call not because it would be technically
           not possible but to avoid an overflow of the supervisor stack. Each creation of
           a user task puts a stack frame on the SV stack. We cannot detect a recursion but
           we can hinder the SV stack overflow by making the current context's base
           priority a gate for further use of this function: The next invocation needs to
           appear at higher level. This will limit the number of stack frames similar as
           this is generally the case for interrupts.
             The number of available task base priority levels is strictly limited and so
           is then the number of possible recursions. The SV stack is protected. */
        unsigned int currentLevel = rtos_osGetTaskBasePriority()
                   , minPriorityLevelOnEntry;

        rtos_osSuspendAllInterrupts();
        const bool isEnabled = currentLevel >= pIData->runTask_minPriorityLevel;
        if(isEnabled)
        {
            minPriorityLevelOnEntry = pIData->runTask_minPriorityLevel;
            pIData->runTask_minPriorityLevel = currentLevel+1;
        }
        rtos_osResumeAllInterrupts();

        if(isEnabled)
        {
            /* All preconditions fulfilled, lock is set, run the task. */
            const int32_t taskResult = rtos_osRunUserTask(pUserTaskConfig, taskParam);

            /* Restore the pre-requisite for future use of this system call. */
            rtos_osSuspendAllInterrupts();

            /* The warning "'minPriorityLevelOnEntry' may be used uninitialized" is locally
               switched off. Justification: Variable is only used if(isEnabled) and then it
               is initialized, too. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            pIData->runTask_minPriorityLevel = minPriorityLevelOnEntry;
#pragma GCC diagnostic pop

            rtos_osResumeAllInterrupts();

            return (uint32_t)taskResult;
        }
        else
        {
            /* Bad use of function, penalty is task abortion.
                 Note, this function does not return. */
            rtos_osSystemCallBadArgument();
        }
    }
    else
    {
        /* The user doesn't have the privileges to run the aimed task. This is a severe
           user code error, which is handled with an exception, task abort and counted
           error.
             Note, this function does not return. */
        rtos_osSystemCallBadArgument();
    }
} /* End of rtos_scFlHdlr_runTask */





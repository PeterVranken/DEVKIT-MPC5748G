#ifndef RTOS_PROCESS_INCLUDED
#define RTOS_PROCESS_INCLUDED
/**
 * @file rtos_process.h
 * Definition of global interface of module rtos_process.c
 *
 * Copyright (C) 2019 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/*
 * Include files
 */

#include "typ_types.h"
#include "rtos_ivorHandler.h"
#include "rtos.h"


/*
 * Defines
 */

/** Index of implemented system call for aborting running tasks belonging to a given
    process and stopping that process forever (i.e. no further task or I/O driver callback
    execution). */
#define RTOS_SYSCALL_SUSPEND_PROCESS     5


/*
 * Global type definitions
 */

/** Run-time data describing a process. An object of this type must be allocated in RAM,
    which is not write-permitted for user code. */
typedef struct rtos_processDesc_t
{
    /** When preempting a task that belongs to this process then the IVOR #4 handler will
        store the current user mode stack pointer value in \a userSP. The stored value may
        be used later as initial stack pointer value of a newly started task from the same
        process.\n
          In the assembler code addressed to by offset #O_PDESC_USP. */
    uint32_t userSP;

    /** The state of the process. This field is e.g. checked at the end of a preemption of
        a task of this process to see if the task may be continued or if the process has
        been stopped meanwhile.\n
          A non zero value means process is running, zero means process stopped.\n
          In the assembler code addressed to by offset #O_PDESC_ST. */
    uint8_t state;

    /** The total count of errors for the process since the start of the kernel. Or the sum
        of all element in array \a cntTaskFailureAry. Or total number of abnormal abortions
        of tasks belonging to the process. */
    uint32_t cntTotalTaskFailure;

    /** This is an array of counters for task termination. The tasks of a process are not
        separated in these counters. Each array entry means another cause, where a cause
        normally is a specific CPU exception.\n
          See file rtos_ivorHandler.h, #RTOS_CAUSE_TASK_ABBORTION_MACHINE_CHECK and
        following, for the enumerated causes. */
    uint32_t cntTaskFailureAry[RTOS_NO_CAUSES_TASK_ABORTION];

} rtos_processDesc_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialize the data structure with all process descriptors. */
rtos_errorCode_t rtos_osInitProcesses(bool isProcessConfiguredAry[1+RTOS_NO_PROCESSES]);

/** Grant permission to particular processes for using the service rtos_suspendProcess(). */
void rtos_osGrantPermissionSuspendProcess( unsigned int pidOfCallingTask
                                         , unsigned int targetPID
                                         );

/** Kernel function to initially release a process. */
void rtos_osReleaseProcess(uint32_t PID);

/** Kernel function to suspend a process. */
void rtos_osSuspendProcess(uint32_t PID);

/** Kernel function to read the suspend status of a process. */
bool rtos_isProcessSuspended(uint32_t PID);

/** Get the number of task failures counted for the given process since start of the kernel. */
unsigned int rtos_getNoTotalTaskFailure(unsigned int PID);

/** Get the number of task failures of given category for the given process. */
unsigned int rtos_getNoTaskFailure(unsigned int PID, unsigned int kindOfErr);

/** Compute how many bytes of the stack area are still unused. */
unsigned int rtos_getStackReserve(unsigned int PID);


/*
 * Inline functions
 */

#endif  /* RTOS_PROCESS_INCLUDED */

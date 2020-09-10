#ifndef RTOS_KERNELINSTANCEDATA_INCLUDED
#define RTOS_KERNELINSTANCEDATA_INCLUDED
/**
 * @file rtos_kernelInstanceData.h
 * Data types and declaration of global data of one instance of the RTOS on a multi-core
 * MCU.
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
/* Module inline interface
 *   rtos_osGetInstancePtr
 */

/*
 * Include files
 */

#include "typ_types.h"
#include "rtos_process.h"
#include "rtos_scheduler.h"
#include "rtos_systemCall.h"


/*
 * Defines
 */

/** \cond Two nested macros are used to convert a constant expression to a string which can be
    used e.g. as part of some inline assembler code.\n
      If for example PI is defined to be (355/113) you could use STR(PI) instead of
    "(355/113)" in the source code. ARG2STR is not called directly. */
#define ARG2STR(x) #x
#define STR(x) ARG2STR(x)
/** \endcond */



/*
 * Global type definitions
 */

/** Definition of global data of one instance of the RTOS on a multi-core MCU. */
typedef struct rtos_kernelInstanceData_t
{
    /** Array holding run-time data for all processes. Note the process IDs have a one based
        index (as 0 is reserved for the kernel process) but this is a normal array with zero
        based index. Use PID-1 as index into the array. */
    rtos_processDesc_t processAry[RTOS_NO_PROCESSES];

    /** The list of all tasks. */
    rtos_taskDesc_t taskCfgAry[RTOS_MAX_NO_TASKS];

    /** The list of all process initialization tasks. */
    rtos_taskDesc_t initTaskCfgAry[1+RTOS_NO_PROCESSES];

    /** The number of registered tasks. The range is 0..#RTOS_MAX_NO_TASKS. */
    unsigned int noTasks;

    /** The list of task activating events. Plus a zero element as end-of-list guard.\n
          Note, this variable is an interface with the assembly code. It may need to pick
        an element from the list if lowering the current priority in the implementation of
        the PCP requires the recursive call of the scheduler. */
    rtos_eventDesc_t eventAry[RTOS_MAX_NO_EVENTS+1];

    /** For performance reasons, all events are internally ordered by priority. At user
        API, they are identified by an ID, which can have an ordering. We need a mapping
        for the implementation of APIs that refer to an event. */
    rtos_eventDesc_t *mapEventIDToPtr[RTOS_MAX_NO_EVENTS];

    /** The PCP, which changes the current priority needs the mapping from priority to the
        first event in the list that has this priority. The map is implemented as direct
        lookup table.\n
          Note the map object is shared with the assembly code. */
    rtos_eventDesc_t *mapPrioToEvent[RTOS_MAX_TASK_PRIORITY+1];

    /** The number of created events. The range is 0..#RTOS_MAX_NO_EVENTS. */
    unsigned int noEvents;

    /** A pointer to event, which has to be served next by the scheduler. Points to an
        element of array rtos_osGetInstancePtr()->eventAry if an event requires the call of
        the scheduler or behind the end of the array otherwise.\n
          This variable is an interface with the assembly code. It may call the scheduler
        with this variable as argument after an ISR (postponed task activation). */
    rtos_eventDesc_t *pNextEventToSchedule;

    /** Pointer to guard element at the end of the list of events.\n
          Since the guard itself is used as list termination this explicit pointer is just
        used for self-tests in DEBUG compilation. */
    const rtos_eventDesc_t *pEndEvent;

    /** Pointer to currently active event. This event is the one, whose associated tasks
        are currently executed. Using this pointer, some informative services can be
        implemented for the tasks. */
    const rtos_eventDesc_t *pCurrentEvent;

    /** The different instances of the RTOS will offer different sets of system calls. Here
        we have the pointer to the system call table to be used. */
    const rtos_systemCallDesc_t *systemCallDescAry;

    /** The priority of the currently executed task.\n
          This variable is an interface with the assembly code. The implementation of the
        PCP requires access to the variable to terminate a critical section if a user task
        should end without doing so.\n
          Note the use of qualifier volatile: This data object is shared between different
        nesting levels of the scheduler but it is not - and this makes the difference to
        nearly all other shared objects - accessed solely from inside of critical sections,
        which have a synchronizing side effect. */
    volatile uint32_t currentPrio;
    
    /** Time increment of one tick of the RTOS system clock. It is set at kernel
        initialization time to the configured period time of the system clock in
        Milliseconds (#RTOS_CLOCK_TICK_IN_MS). This way the unit of all time designations
        in the RTOS API always stays Milliseconds despite of the actually chosen clock
        rate. (An application of the RTOS can reduce the clock rate to the lowest possible
        value in order to save overhead.) The normal settings are a clock rate of 1 kHz and
        #RTOS_CLOCK_TICK_IN_MS=1.\n
          The variable is initially set to zero to hold the scheduler during RTOS
        initialization. */
    unsigned long tiOsStep;

    /** RTOS sytem time in Milliseconds since start of kernel. */
    unsigned long tiOs;

    /** The option to let a task of process A suspend process B (system call
        rtos_suspendProcess()) is potentially harmful, as a safety relevant supervisory task
        could be hindered from running. This is of course not generally permittable. An
        all-embracing privilege rule cannot be defined because of the different use cases of
        the mechanism. Therefore, we have an explicit table of granted permissions, which can
        be configured at startup time as an element of the operating system initialization
        code.\n
          The bits of the word correspond to the 16 possible combinations of four possible
        caller processes in four possible target processes.
          By default, no permission is granted. */
#if RTOS_NO_PROCESSES == 4
    uint16_t suspendProcess_permissions;
#else
# error Implementation depends on four being the number of processes
#endif
    
    /** The option for inter-process communication to let a task of process A run a task in
        process B (system call rtos_runTask()) is potentially harmful, as the started task
        can destroy on behalf of process A all data structures of the other process B. It's
        of course not generally permittable. An all-embracing privilege rule cannot be
        defined because of the different use cases of the mechanism. Therefore, we have an
        explicit table of granted permissions, which can be configured at startup time as
        an element of the operating system initialization code.\n
          The bits of the word correspond to the 16 possible combinations of four possible
        caller processes in four possible target processes.
          By default, no permission is granted. */
#if RTOS_NO_PROCESSES == 4
    uint16_t runTask_permissions;
#else
# error Implementation depends on four being the number of processes
#endif

    /** Local data of service rtos_runTask(). The current priority value, at which the
        service is still permitted. Used to avoid unbounded recursive use of this service,
        which would crash the system. */
    uint32_t runTask_minPriorityLevel;

} rtos_kernelInstanceData_t;


/*
 * Global data declarations
 */


/*
 * Global inline functions
 */

/**
 * All data in use by the kernel is bundled in a large struct. If the RTOS is run on an MCU
 * with several cores then each core uses its own dedicated instance of this struct. This
 * function returns the struct to use by reference.
 *   @return
 * Get the instance pointer to the RTOS data set.
 *   @remark
 * This function my be called from OS contexts only. Any attempt to call it from a user
 * task will cause a privileged exception. Use rtos_getInstancePtr() instead.
 */
static inline rtos_kernelInstanceData_t *rtos_osGetInstancePtr(void)
{
    rtos_kernelInstanceData_t *pInstanceData;
    _Static_assert( sizeof(rtos_kernelInstanceData_t*) == 4
                  , "Interface check C to assembly failed for module rtos_kernelInstanceData.c"
                  );
    asm volatile ( /* AssemblerTemplate */
                   "mfspr   %0, " STR(SPR_G3_CDATA) "\n\t"
                 : /* OutputOperands */ "=r" (pInstanceData)
                 : /* InputOperands */
                 : /* Clobbers */
                 );
    return pInstanceData;

} /* End of rtos_osGetInstancePtr */


/*
 * Global prototypes
 */


/** Get kernel instance data by reference. Here for user tasks. */
const rtos_kernelInstanceData_t *rtos_getInstancePtr(void);


#endif  /* RTOS_KERNELINSTANCEDATA_INCLUDED */

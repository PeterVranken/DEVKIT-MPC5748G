/**
 * @file rtos_kernelInstanceData.c
 * Definition of global data of one instance of the RTOS on a multi-core MCU.
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

#include "rtos_ivorHandler.h"
#include "rtos.h"
#include "rtos_kernelInstanceData.h"


/*
 * Defines
 */

/** The initializer expression for a single kernel instance data object. All fields have
    zero or "invalid" initial values, so they are not core specific. We can use the same
    initializer expression for all CPU cores and therefore we define them once here. */
#define KERNEL_INSTANCE_DATA_INITIAL_DATA                                                   \
{                                                                                           \
    /* Array holding run-time data for all processes. Note the process IDs have a one       \
       based index (as 0 is reserved for the kernel process) but this is a normal array     \
       with zero based index. Use PID-1 as index into the array. */                         \
    .processAry =                                                                           \
    {                                                                                       \
        /** Process 1. */                                                                   \
        [0] = { .userSP = 0                                                                 \
                , .state = 0                                                                \
                , .cntTotalTaskFailure = 0                                                  \
                , .cntTaskFailureAry = {[0 ... (RTOS_NO_CAUSES_TASK_ABORTION-1)] = 0}       \
              },                                                                            \
                                                                                            \
        /** Process 2. */                                                                   \
        [1] = { .userSP = 0                                                                 \
                , .state = 0                                                                \
                , .cntTotalTaskFailure = 0                                                  \
                , .cntTaskFailureAry = {[0 ... (RTOS_NO_CAUSES_TASK_ABORTION-1)] = 0}       \
              },                                                                            \
                                                                                            \
        /** Process 3. */                                                                   \
        [2] = { .userSP = 0                                                                 \
                , .state = 0                                                                \
                , .cntTotalTaskFailure = 0                                                  \
                , .cntTaskFailureAry = {[0 ... (RTOS_NO_CAUSES_TASK_ABORTION-1)] = 0}       \
              },                                                                            \
                                                                                            \
        /** Process 4. */                                                                   \
        [3] = { .userSP = 0                                                                 \
                , .state = 0                                                                \
                , .cntTotalTaskFailure = 0                                                  \
                , .cntTaskFailureAry = {[0 ... (RTOS_NO_CAUSES_TASK_ABORTION-1)] = 0}       \
              },                                                                            \
    },                                                                                      \
                                                                                            \
    /* The list of all tasks. */                                                            \
    .taskCfgAry =                                                                           \
        { [0 ... (RTOS_MAX_NO_TASKS-1)] = { .addrTaskFct = 0                                \
                                            , .PID = 0                                      \
                                            , .tiTaskMax = 0                                \
                                          },                                                \
        },                                                                                  \
                                                                                            \
    /* The list of all process initialization tasks. */                                     \
    .initTaskCfgAry =                                                                       \
        { [0 ... RTOS_NO_PROCESSES] = { .addrTaskFct = 0                                    \
                                        , .PID = 0                                          \
                                        , .tiTaskMax = 0                                    \
                                      },                                                    \
        },                                                                                  \
                                                                                            \
    /* The number of registered tasks. The range is 0..#RTOS_MAX_NO_TASKS. */               \
    .noTasks = 0,                                                                           \
                                                                                            \
    /* The list of task activating events. Plus a zero element as end-of-list guard.\n      \
         Note, this variable is an interface with the assembly code. It may need to pick    \
       an element from the list if lowering the current priority in the implementation of   \
       the PCP requires the recursive call of the scheduler. */                             \
    .eventAry =                                                                             \
        { [0 ... RTOS_MAX_NO_EVENTS] =                                                      \
            { .state = evState_idle                                                         \
              , .minPIDForTrigger = RTOS_EVENT_NOT_USER_TRIGGERABLE                         \
              , .noTasks = 0                                                                \
              , .taskAry = NULL                                                             \
              , .tiDue = 0                                                                  \
              , .tiCycleInMs = 0                                                            \
              , .priority = 0                                                               \
              , .taskParam = 0                                                              \
              , .noActivationLoss = 0                                                       \
              , .pNextScheduledEvent = NULL                                                 \
            },                                                                              \
        },                                                                                  \
                                                                                            \
    /* For performance reasons, all events are internally ordered by priority. At user      \
       API, they are identified by an ID, which can have an ordering. We need a mapping     \
       for the implementation of APIs that refer to an event. */                            \
    .mapEventIDToPtr = {[0 ... (RTOS_MAX_NO_EVENTS-1)] = NULL},                             \
                                                                                            \
    /* The PCP, which changes the current priority needs the mapping from priority to       \
       the first event in the list that has this priority. The map is implemented as        \
       direct lookup table.\n                                                               \
         Note the map object is shared with the assembly code. */                           \
    .mapPrioToEvent = {[0 ... RTOS_MAX_TASK_PRIORITY] = NULL},                              \
                                                                                            \
    /* The number of created events. The range is 0..#RTOS_MAX_NO_EVENTS. */                \
    .noEvents = 0,                                                                          \
                                                                                            \
    /* A pointer to the event, which has to be served next by the scheduler. Points to      \
       an element of array rtos_osGetInstancePtr()->eventAry if an event requires the       \
       call of the scheduler or behind the end of the array otherwise.\n                    \
         This variable is an interface with the assembly code. It may call the              \
       scheduler with this variable as argument after an ISR (postponed task                \
       activation). */                                                                      \
    .pNextEventToSchedule = (rtos_eventDesc_t*)(uintptr_t)-1,                               \
                                                                                            \
    /* Pointer to guard element at the end of the list of events.\n                         \
         Since the guard itself is used as list termination this explicit pointer is        \
       just used for self-tests in DEBUG compilation. */                                    \
    .pEndEvent = NULL,                                                                      \
                                                                                            \
    /* Pointer to currently active event. This event is the one, whose associated tasks     \
       are currently executed. Using this pointer, some informative services can be         \
       implemented for the tasks. */                                                        \
    .pCurrentEvent = NULL,                                                                  \
                                                                                            \
    /* The different instances of the RTOS will offer different sets of system calls.       \
       Here we have the pointer to the system call table to be used. */                     \
    .systemCallDescAry = NULL,                                                              \
                                                                                            \
    /* The priority of the currently executed task.\n                                       \
         This variable is an interface with the assembly code. The implementation of        \
       the PCP requires access to the variable to terminate a critical section if a         \
       user task should end without doing so.\n                                             \
         Note the use of qualifier volatile: This data object is shared between             \
       different nesting levels of the scheduler but it is not - and this makes the         \
       difference to nearly all other shared objects - accessed solely from inside of       \
       critical sections, which have a synchronizing side effect. */                        \
    .currentPrio = 0,                                                                       \
                                                                                            \
    /* Time increment of one tick of the RTOS system clock. It is set at kernel             \
       initialization time to the configured period time of the system clock in             \
       Milliseconds (#RTOS_CLOCK_TICK_IN_MS). This way the unit of all time                 \
       designations in the RTOS API always stays Milliseconds despite of the actually       \
       chosen clock rate. (An application of the RTOS can reduce the clock rate to the      \
       lowest possible value in order to save overhead.) The normal settings are a          \
       clock rate of 1 kHz and #RTOS_CLOCK_TICK_IN_MS=1.\n                                  \
         The variable is initially set to zero to hold the scheduler during RTOS            \
       initialization. */                                                                   \
    .tiOsStep = 0,                                                                          \
                                                                                            \
    /* RTOS sytem time in Milliseconds since start of kernel. */                            \
    .tiOs = (unsigned long)-1,                                                              \
                                                                                            \
    /* By default, no permission is granted to suspend another process. */                  \
    .suspendProcess_permissions = 0,                                                        \
                                                                                            \
    /* By default, no permission is granted to run a task in another process. */            \
    .runTask_permissions = 0,                                                               \
                                                                                            \
    /* Local data of service rtos_runTask(). The current priority value, at which the       \
       service is still permitted. */                                                       \
    .runTask_minPriorityLevel = 0,                                                          \
}



/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

#if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 1
/** Global data of one instance of the RTOS on a multi-core MCU. Here for core 0, Z4A. */
rtos_kernelInstanceData_t DATA_OS(rtos_kernelInstanceData_core0) =
                                                    KERNEL_INSTANCE_DATA_INITIAL_DATA;
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
/** Global data of one instance of the RTOS on a multi-core MCU. Here for core 1, Z4B. */
rtos_kernelInstanceData_t DATA_OS(rtos_kernelInstanceData_core1) =
                                                    KERNEL_INSTANCE_DATA_INITIAL_DATA;
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
/** Global data of one instance of the RTOS on a multi-core MCU. Here for core 2, Z2. */
rtos_kernelInstanceData_t DATA_OS(rtos_kernelInstanceData_core2) =
                                                    KERNEL_INSTANCE_DATA_INITIAL_DATA;
#endif


/*
 * Function implementation
 */


/**
 * The C code has an interface with the assembler code. It is used to exchange process
 * and task related information. The interface is modeled twice, once as structs for C
 * code and once as set of preprocessor macros, which hold size of data structures and
 * offsets of fields. Here, we have macros, which support double-checking the
 * equivalence of both definitions. The compiler will abort the compilation if there is
 * a static inconsistency.
 *   @remark
 * This function neds to be compiled but doesn't need to be called. Nonelthelees, to avoid
 * a compiler warning like "static but never used" we define it public.
 *   @todo
 * As soon as runtime checks are defined (see
 * #RTOS_CONSTRAINTS_INTERFACE_C_AS_INSTANCE_DATA) we need to call this function. This
 * requires a documentation change of the function, too.
 */
void dummyFctToCheckStaticAssertions(void);
void dummyFctToCheckStaticAssertions(void)
{
    ///* A few more conditions even require run-time checking. */
    //assert(RTOS_CONSTRAINTS_INTERFACE_C_AS_INSTANCE_DATA);
    _Static_assert( RTOS_STATIC_CONSTRAINTS_INTERFACE_C_AS_INSTANCE_DATA
                  , "Interface check C to assembly failed for module rtos_kernelInstanceData.c"
                  );
} /* dummyFctToCheckStaticAssertions */

#ifndef RTOS_CONFIG_INCLUDED
#define RTOS_CONFIG_INCLUDED
/**
 * @file rtos.config.h
 * This file contains the application depended compile-time configuration of the RTOS.
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

/*
 * Include files
 */


/*
 * Defines
 */

/** @remark Note, this file is shared with the assembly code. You must not use any
    constructs in the definition of the macros, which were not compatible with the GNU
    assembly language, e.g. number literals like 10u instead of 10. */


/** Specify whether core 0, Z4A, should run safe-RTOS. Permitted values are 1 or 0. */
#define RTOS_RUN_SAFE_RTOS_ON_CORE_0        1

/** Specify whether core 1, Z4B, should run safe-RTOS. Permitted values are 1 or 0. */
#define RTOS_RUN_SAFE_RTOS_ON_CORE_1        1

/** Specify whether core 2, Z2, should run safe-RTOS. Permitted values are 1 or 0. */
#define RTOS_RUN_SAFE_RTOS_ON_CORE_2        1

/** The period time of the RTOS system timer. Unit is 1ms. Configurable range is 1..35791.
    If either this range or the timing accuracy of 1ms is not sufficient then you need to
    change the implementation of the main RTOS clock in rtos_scheduler.c, function
    initRTOSClockTick().
      @remark In this test we use a floating point value for the clock period of the RTOS
    on the second core. Basically, the RTOS expects a non-zero integer. A floating point
    number leads to the correct, according timer configuration but the logical clock of the
    scheduler increments by the downwards rounded value. We have in our example a period
    time of 1.0002375ms on core 1 but the RTOS thinks for all scheduling decisions it were
    1ms.\n
      The reason for doing so is testing. The small deviation has been chosen such that the
    RTOS timers on the different cores have integer cycle times, which are prime to one
    another. This leads to most random concurrency patterns. */
#define RTOS_CLOCK_TICK_IN_MS_CORE_0            1 /* ms */
#define RTOS_CLOCK_TICK_IN_MS_CORE_1            1.0002375 /* ms */
#define RTOS_CLOCK_TICK_IN_MS_CORE_2            1.0003375 /* ms */

/** ISR priority of the scheduler for cyclic, time triggered events. The priority of the
    scheduler should be balanced with other ISRs that interact with user tasks. Interrupts
    of same or higher priority may exist but they cannot have a secured callback into user
    code (no deadline monitoring). This makes them somewhat critical in use with respect to
    the safety concept. */
#define RTOS_KERNEL_IRQ_PRIORITY_CORE_0         12
#define RTOS_KERNEL_IRQ_PRIORITY_CORE_1         2
#define RTOS_KERNEL_IRQ_PRIORITY_CORE_2         2

/** This is the highest task priority in use. Basically, a priority is just a number and it
    doesn't matter which one. However, for some operations, the kernel needs lookup operations
    from priority to other objects. These can be implemented most simple and efficient by
    direct lookup tables if the maximum priority in use is not too large. Therefore, you
    should preferrably use the priority values 1, 2, 3, ..., max and specify the maximum
    here.\n
      @remark The maximum task priority is not core specific. It impacts the build-up of
    the kernel instance data set, which needs to be identical on all cores. You will need
    to specify the maximum of what is required on all cores. */
#define RTOS_MAX_TASK_PRIORITY                  11

/** This the highest priority that user tasks can have, which user code can shape a
    critical section with. If a task has a higher priority then user code can't hinder it
    from being scheduled at any time and race conditions with these tasks can't be
    avoided. Lockfree coding pattern need to be applied for communication with such
    tasks.\n
      Note, in order to not break the safety concept, there should be at least one safety
    supervisory task having a priority above #RTOS_MAX_LOCKABLE_TASK_PRIORITY.\n
      @remark The maximum lockable task priority is not core specific. Usually, it'll be
    one less than #RTOS_MAX_TASK_PRIORITY. */
#define RTOS_MAX_LOCKABLE_TASK_PRIORITY         ((RTOS_MAX_TASK_PRIORITY)-1)

/** Any user task is activated by an event. Several tasks can be associated with one and
    the same event but each event needs to have at least one associated task. Therefore, it
    is useless to configure this macro less than #RTOS_MAX_NO_TASKS.\n
      The chosen number is a compile time configuration setting and there are no
    constraints in changing it besides the amount of reserved RAM space for the resulting
    table size.\n
      @remark The maximum number of events is not core specific. It impacts the build-up of
    the kernel instance data set, which needs to be identical on all cores. You will need
    to specify the maximum of what is required on all cores. */
#define RTOS_MAX_NO_EVENTS                      8

/** The maximum, total number of user tasks, which can be activated by the events. The
    chosen number is a compile time configuration setting and there are no constraints in
    changing it besides the amount of reserved RAM space for the resulting table size.\n
      The configured limit applies to the tasks registered with rtos_osRegisterUserTask()
    and rtos_osRegisterOSTask() only; process initialization tasks and callbacks from I/O
    drivers, which are much of a user task, too, are not counted here.\n
      @remark The maximum number of tasks is not core specific. It impacts the build-up of
    the kernel instance data set, which needs to be identical on all cores. You will need
    to specify the maximum of what is required on all cores. */
#define RTOS_MAX_NO_TASKS                       20

/** The MPC5748G has 16 PIT timer channels, which can be used to clock the RTOS. The choice
    is made a configuration item because the PIT timers may be used for particular I/O
    purposes and not each timer can drive each I/O device. Each core uses its own timer.\n
      Specify here, which PIT channel is used for core 0, Z4A.\n
      Range is 0..15. (But be aware that the serial I/O driver requires channel 0.)\n
      The value doesn't care if the core dosn't run safe-RTOS, see
    #RTOS_RUN_SAFE_RTOS_ON_CORE_0.*/
#define RTOS_IDX_OF_PID_TIMER_CORE_0            13
#define RTOS_IDX_OF_PID_TIMER_CORE_1            12
#define RTOS_IDX_OF_PID_TIMER_CORE_2            11
    

/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



#endif  /* RTOS_CONFIG_INCLUDED */

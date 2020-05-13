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

/** The number of cores in the MCU running the RTOS.\n
      @remark Although this macro is application dependent, we decided to not put it into
    the user configuration file rtos.config.h. The reason is that the configuration of
    another number of cores requires more changes than just this macro. Mainly the linker
    script is additionally affected and it can't reasonably be made dependent on this macro.
    Putting the macro here effectively expresses that the RTOS needs migration and not just
    re-configuration if run on another MCU derivative with another number of cores. */
/// @todo Wrong. We need to allow an application dependent number of RTOS instanciations.
// the remaining cores can run the normal IVOR #4 handler and all code in SV mode, as
// sample startup. Actually, we would have a set opreration, any core can decide, but an
// allowed limitation for this sample would be to say the n first cores need to run the
// RTOS, n>=1. This should be doable by preprocessor switches.
#define RTOS_NO_CORES               1

/** @remark Note, this file is shared with the assembly code. You must not use any
    constructs in the definition of the macros, which were not compatible with the GNU
    assembly language, e.g. number literals like 10u instead of 10. */

/** The period time of the RTOS system timer. Unit is 1ms. Configurable range is 1..35791.
    If either this range or the timing accuracy of 1ms is not sufficient then you need to
    change the implementation of the main RTOS clock in rtos_scheduler.c, function
    initRTOSClockTick(). */
#define RTOS_CLOCK_TICK_IN_MS                   1 /* ms */

/** ISR priority of the scheduler for cyclic, time triggered events. The priority of the
    scheduler should be balanced with other ISRs that interact with user tasks. Interrupts
    of same or higher priority may exist but they cannot have a secured callback into user
    code (no deadline monitoring). This makes them somewhat critical in use with respect to
    the safety concept. */
#define RTOS_KERNEL_IRQ_PRIORITY                1

/** This is the highest task priority in use. Basically, a priority is just a number and it
    doesn't matter which one. However, for some operations, the kernel needs lookup operations
    from priority to other objects. These can be implemented most simple and efficient by
    direct lookup tables if the maximum priority in use is not too large. Therefore, one
    should use the priority values 1, 2, 3, ..., max and specify the maximum here. */
#define RTOS_MAX_TASK_PRIORITY                  (RTOS_MAX_NO_EVENTS)

/** This the highest priority that user tasks can have, which user code can shape a
    critical section with. If a task has a higher priority then user code can't hinder it
    from being scheduled at any time and race conditions with these tasks can't be
    avoided. Lockfree coding pattern need to be applied for communication with such
    tasks.\n
      Note, in order to not break the safety concept, there should be at least one safety
    supervisory task having a priority above #RTOS_MAX_LOCKABLE_TASK_PRIORITY. */
#define RTOS_MAX_LOCKABLE_TASK_PRIORITY         (RTOS_MAX_TASK_PRIORITY-1)

/** Any user task is activated by an event. Several tasks can be associated with one and
    the same event but each event needs to have at least one associated task. Therefore, it
    is useless to configure this macro less than #RTOS_MAX_NO_TASKS.\n
      The chosen number is a compile time configuration setting and there are no
    constraints in changing it besides the amount of reserved RAM space for the resulting
    table size. */
#define RTOS_MAX_NO_EVENTS                      8

/** The maximum, total number of user tasks, which can be activated by the events. The
    chosen number is a compile time configuration setting and there are no constraints in
    changing it besides the amount of reserved RAM space for the resulting table size.\n
      The configured limit applies to the tasks registered with rtos_osRegisterUserTask()
    and rtos_osRegisterOSTask() only; process initialization tasks and callbacks from I/O
    drivers, which are much of a user task, too, are not counted here. */
#define RTOS_MAX_NO_TASKS                       20


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

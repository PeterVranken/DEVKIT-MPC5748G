#ifndef RTOS_RUNTASK_INCLUDED
#define RTOS_RUNTASK_INCLUDED
/**
 * @file rtos_runTask.h
 * Definition of global interface of module rtos_runTask.c
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

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */

/** System call index of function rtos_runTask(), offered by this module. */
#define RTOS_SYSCALL_RUN_TASK                           4


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Grant permission to particular processes for using the service rtos_runTask(). */
void rtos_osGrantPermissionRunTask(unsigned int pidOfCallingTask, unsigned int targetPID);

/** Check if rtos_osGrantPermissionRunTask() had been used to grant access for a given
    process to start a task in another given process. */
bool rtos_osCheckPermissionRunTask(unsigned int pidOfCallingTask, unsigned int targetPID);


#endif  /* RTOS_RUNTASK_INCLUDED */

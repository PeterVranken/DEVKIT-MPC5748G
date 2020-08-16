#ifndef PRS_PROCESSSUPERVISOR_INCLUDED
#define PRS_PROCESSSUPERVISOR_INCLUDED
/**
 * @file prs_processSupervisor.h
 * Definition of global interface of module prs_applicationTasks.c
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

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** Counter for test cycles. */
extern volatile long unsigned int prs_cntTestCycles;


/*
 * Global prototypes
 */

/** User task to select and command the error to inject by the failing task. */
int32_t prs_taskCommandError(uint32_t PID, uintptr_t taskParam);

/** User task to double-check if failure has been produced and was reported on process
    level. */
int32_t prs_taskEvaluateError(uint32_t PID, uintptr_t taskParam);

/** Watchdog task to check if supervisor task is still alive. */
int32_t prs_taskWatchdog(uint32_t PID, uintptr_t taskParam);

#endif  /* PRS_PROCESSSUPERVISOR_INCLUDED */

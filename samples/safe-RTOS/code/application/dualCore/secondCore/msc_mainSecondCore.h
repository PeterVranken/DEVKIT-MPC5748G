#ifndef MSC_MAINSECONDCORE_INCLUDED
#define MSC_MAINSECONDCORE_INCLUDED
/**
 * @file msc_mainSecondCore.h
 * Definition of global interface of module msc_mainSecondCore.c
 *
 * Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/** Counter of cycles of infinite main loop. */
extern volatile unsigned long msc_cntTaskIdle;

/** Counter of cyclic 1ms user task. */
extern volatile unsigned long msc_cntTask1ms;  

/** Counter of cyclic 1ms OS task. */
extern volatile unsigned long msc_cntTaskOs1ms;

/** Total counter of task failures in P1 on second core. */
extern volatile unsigned int msc_cntTaskFailuresP1;

/** Activation loss counter for process 1 on the second core. */
extern volatile unsigned int msc_cntActivationLossFailures;

/** Stack reserve of process p1 on the second core. */
extern volatile unsigned int msc_stackReserveP1;

/** Stack reserve of kernel process on the second core. */
extern volatile unsigned int msc_stackReserveOS;

/** The average CPU load produced by all tasks and interrupts on core Z4B in tens of
    percent. */ 
extern volatile unsigned int msc_cpuLoadSecondCore;


/*
 * Global prototypes
 */

/** Main entry point of code execution for core Z4B. */
void /* _Noreturn */ msc_mainSecondCore(int noArgs, const char *argAry[]);

/** Callback for LED and button I/O driver. */
int32_t msc_onButtonChangeCallback(uint32_t PID ATTRIB_UNUSED, uint8_t buttonState);

#endif  /* MSC_MAINSECONDCORE_INCLUDED */

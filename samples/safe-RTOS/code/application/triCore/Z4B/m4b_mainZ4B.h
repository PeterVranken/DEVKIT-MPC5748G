#ifndef M4B_MAINZ4B_INCLUDED
#define M4B_MAINZ4B_INCLUDED
/**
 * @file m4b_mainZ4B.h
 * Definition of global interface of module m4b_mainZ4B.c
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

/** This is the RTOS event on core Z4B that is triggered from the other core Z2 using the
    inter-core notification driver. The notification task on the Z4B, which is associated
    with the event is activated by the Z2 core. */
#define M4B_ID_EVENT_NOTIFICATION_FROM_Z2   1


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** Counter of cyclic 1ms user task. */
extern volatile unsigned long m4b_cntTask1ms;  

/** Counter of cyclic 1ms OS task. */
extern volatile unsigned long m4b_cntTaskOs1ms;

/** Counter of cycles of infinite main loop. */
extern volatile unsigned long m4b_cntTaskIdle;

/** Total counter of task failures in P1 on second core. */
extern volatile unsigned int m4b_cntTaskFailuresP1;

/** Activation loss counter for process 1 on the second core. */
extern volatile unsigned int m4b_cntActivationLossFailures;

/** Stack reserve of process p1 on the second core. */
extern volatile unsigned int m4b_stackReserveP1;

/** Stack reserve of kernel process on the second core. */
extern volatile unsigned int m4b_stackReserveOS;

/** The average CPU load produced by all tasks and interrupts on core Z4B in tens of
    percent. */ 
extern volatile unsigned int m4b_cpuLoadZ4B;


/*
 * Global prototypes
 */

/** Test function: error injection. */
void mb4_injectError(unsigned int * const pIdxErr);

/** Callback for LED and button I/O driver. */
int32_t m4b_onButtonChangeCallback(uint32_t PID ATTRIB_UNUSED, uint8_t buttonState);

/** Main entry point of code execution for core Z4B. */
void /* _Noreturn */ m4b_mainZ4B(int noArgs, const char *argAry[]);

#endif  /* M4B_MAINZ4B_INCLUDED */

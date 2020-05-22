#ifndef MZB_MAIN_Z4B_INCLUDED
#define MZB_MAIN_Z4B_INCLUDED
/**
 * @file mzb_main_Z4B.h
 * Definition of global interface of module mzb_main_Z4B.c
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
extern volatile unsigned long mzb_cntTaskIdle;

/** Counter of cyclic 1ms user task. */
extern volatile unsigned long mzb_cntTask1ms;  

/** Counter of cyclic 1ms OS task. */
extern volatile unsigned long mzb_cntTaskOs1ms;

/** The average CPU load produced by all tasks and interrupts on core Z4B in tens of
    percent. */ 
extern volatile unsigned int mzb_cpuLoad;


/*
 * Global prototypes
 */

/** Main entry point of code execution for core Z4B. */
void /* _Noreturn */ mzb_main_Z4B(int noArgs, const char *argAry[]);

/** Callback for LED and button I/O driver. */
int32_t mzb_onButtonChangeCallback(uint32_t PID ATTRIB_UNUSED, uint8_t buttonState);

#endif  /* MZB_MAIN_Z4B_INCLUDED */

#ifndef MZ2_MAIN_Z2_INCLUDED
#define MZ2_MAIN_Z2_INCLUDED
/**
 * @file mz2_main_Z2.h
 * Definition of global interface of module mz2_main_Z2.c
 *
 * Copyright (C) 2018-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
extern volatile unsigned long mbm_cntMain;

#if 0
/** Counter of cyclic 1ms user isr. */
extern volatile unsigned long mbm_cntIsr1ms;  
#endif

/** The average CPU load produced by all isrs and interrupts in tens of percent. */ 
extern volatile unsigned int mbm_cpuLoadCoreBareMetal;


/*
 * Global prototypes
 */

/** Main entry point of code execution for core Z2. */
void /* _Noreturn */ mbm_mainCoreBareMetal(int noArgs, const char *argAry[]);

#endif  /* MZ2_MAIN_Z2_INCLUDED */

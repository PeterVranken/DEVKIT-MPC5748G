#ifndef TCX_TESTCONTEXT_INCLUDED
#define TCX_TESTCONTEXT_INCLUDED
/**
 * @file tcx_testContext.h
 * Definition of global interface of module tcx_testContext.c
 *
 * Copyright (C) 2018-2019 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

volatile extern uint32_t tcx_cntTestLoops;


/*
 * Global prototypes
 */

/**
 * This function writes specific values to most accessible registers of the CPU, does busy
 * wait for a while - to let the scheduler make a context switch - and checks the register
 * contents. This is done the given number of times, the function returns after \a noCycles
 * times \a waitTimePerCycleInUS Microseconds consumption of CPU. (It produces full CPU
 * load during operation.) The time till return depends on the time it is preempted by
 * other tasks.
 *   @return
 * The function returns the total number of test cycles since its very first use after
 * system startup.
 *   @param noCycles
 * The number of test cycles to run.
 *   @param waitTimePerCycleInUS
 * The busy wait time applied in each of the cycles in Microseconds.
 *   @remark
 * The function is not reentrant. It must not be called again before the preceeding
 * invocation has returned.
 */
uint32_t tcx_testContext(uint32_t noCycles, uint32_t waitTimePerCycleInUS);

#endif  /* TCX_TESTCONTEXT_INCLUDED */

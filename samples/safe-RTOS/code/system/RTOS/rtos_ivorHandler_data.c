/**
 * @file rtos_ivorHandler_data.c
 * Data object of the assembly code, which should appear in the debug information, are
 * placed here. (It's not so clear how to declare it directly in the assembly code.)
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

#include "typ_types.h"


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
/** @todo MPC5748G, Z4A, seems to not load MCSRR0/1 as expected. Test code counts
    occurances. */
volatile uint32_t DATA_OS(rtos_cntIvor1AtFFFFC000) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted the
    handler of an IVOR #2 CPU exception. The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor2) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted the
    handler of an IVOR #3 CPU exception. The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor3) = 0;

/** The IVOR #1 counts the number of occurances of the rare situation, when it preempts a
    coincidentally starting IVOR #4 handler. The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor4) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted the
    handler of an IVOR #5 CPU exception. The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor5) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted the
    handler of an IVOR #6 CPU exception. The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor6) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted the
    handler of an IVOR #7 CPU exception. The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor7) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted the
    handler of an IVOR #8 system call.The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor8) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted the
    handler of an IVOR #13 CPU exception. The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor13) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted the
    handler of an IVOR #14 CPU exception. The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor14) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted the
    handler of an IVOR #32 CPU exception. The counter is saturated at its implementation
    maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor32) = 0;

/** Reporting of double exceptions: A counter for MC exceptions, which preempted one of the
    CPU FPU exception handlers, IVOR #33 or IVOR #34. The counter is saturated at its
    implementation maximum. */
volatile uint16_t DATA_OS(rtos_cntIvor1PreemptsIvor33Or34) = 0;


/*
 * Function implementation
 */


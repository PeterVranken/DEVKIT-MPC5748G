#ifndef RTOS_EXTERNALINTERRUPT_INCLUDED
#define RTOS_EXTERNALINTERRUPT_INCLUDED
/**
 * @file rtos_externalInterrupt.h
 * Definition of global interface of module rtos_externalInterrupt.c
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

#include "typ_types.h"

#include "rtos.h"


/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global inline functions
 */


/*
 * Global prototypes
 */

/** Initialize the interrupt controller INTC. */
void rtos_osInitINTCInterruptController(void);

/** Install an interrupt service for a given I/O device. */
/// @todo Make function disappear and have a ROM table as for system calls
void rtos_osRegisterInterruptHandler( rtos_interruptServiceRoutine_t interruptServiceRoutine
                                    , unsigned int processorID
                                    , unsigned int vectorNum
                                    , unsigned int psrPriority
                                    , bool isPreemptable
                                    );

#endif  /* RTOS_EXTERNALINTERRUPT_INCLUDED */

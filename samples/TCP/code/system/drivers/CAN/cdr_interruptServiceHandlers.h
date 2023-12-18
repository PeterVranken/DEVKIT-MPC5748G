#ifndef CDR_INTERRUPTSERVICEHANDLERS_INCLUDED
#define CDR_INTERRUPTSERVICEHANDLERS_INCLUDED
/**
 * @file cdr_interruptServiceHandlers.h
 * Definition of global interface of module cdr_interruptServiceHandlers.c
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


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** The interrupt handlers of a single CAN device are registered at the operating system. */
void cdr_osRegisterInterrupts(unsigned int idxCanDevice);


/*
 * Global inline functions
 */


#endif  /* CDR_INTERRUPTSERVICEHANDLERS_INCLUDED */

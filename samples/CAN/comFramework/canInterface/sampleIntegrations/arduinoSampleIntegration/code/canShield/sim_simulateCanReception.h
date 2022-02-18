#ifndef SIM_SIMULATECANRECEPTION_INCLUDED
#define SIM_SIMULATECANRECEPTION_INCLUDED
/**
 * @file sim_simulateCanReception.h
 * Definition of global interface of module sim_simulateCanReception.c
 *
 * Copyright (C) 2015 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <stdlib.h>

#include "types.h"


/*
 * Defines
 */

/** Global switch to enable error simulation for all frames and buses. Set it to either 1
    or 0. */
#define SIM_DO_ERROR_SIMULATION     1


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Clock the CAN reception simulation. */
void sim_simulateCanReception();

#endif  /* SIM_SIMULATECANRECEPTION_INCLUDED */

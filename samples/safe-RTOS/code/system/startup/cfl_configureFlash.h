#ifndef CFL_CONFIGUREFLASH_INCLUDED
#define CFL_CONFIGUREFLASH_INCLUDED
/**
 * @file cfl_configureFlash.h
 * Definition of global interface of module cfl_configureFlash.S
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
#include "MPC5748G.h"


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

/** Configure the flash controller. */
void cfl_configureFlash(uint32_t RWSC_waitStates, uint32_t APC_pipelining);

#endif  /* CFL_CONFIGUREFLASH_INCLUDED */

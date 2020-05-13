#ifndef MAI_MAIN_INCLUDED
#define MAI_MAIN_INCLUDED
/**
 * @file mai_main.h
 * Definition of global interface of module mai_main.c
 *
 * Copyright (C) 2017 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "lbd_ledAndButtonDriver.h"

/*
 * Defines
 */

/** Index of implemented (preemptable, preliminary test) system call for accessing an LED. */
#define MAI_SYSCALL_SET_LED_AND_WAIT    2


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

#endif  /* MAI_MAIN_INCLUDED */

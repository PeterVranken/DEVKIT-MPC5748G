#ifndef MAIN_INCLUDED
#define MAIN_INCLUDED
/**
 * @file main.h
 * Definition of global interface of module main.c
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

#include "types.h"


/*
 * Defines
 */

/** The printable long name of the application. */
#define MAIN_APP_GREETING   "comFramework - Event dispatcher timer demo" " " MAIN_SW_REV

/** The revision. */
#define MAIN_SW_REV         "0.1.1"

/** The time unit, the time span between two calls of the dispatcher with index 0. */
#define MAIN_TI_TICK_DISPATCHER_0   13


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** The simulation time. */
extern unsigned long main_tiSim;


/*
 * Global prototypes
 */

/** Main function of application. */
signed int main(signed int argc, char *argv[]);


#endif  /* MAIN_INCLUDED */

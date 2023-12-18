#ifndef GSL_SYSTEMLOAD_INCLUDED
#define GSL_SYSTEMLOAD_INCLUDED
/**
 * @file gsl_systemLoad.h
 * Definition of global interface of module gsl_systemLoad.c
 *
 * This file has been downloaded from
 * https://svn.code.sf.net/p/rtuinos/code/trunk/code/RTOS/gsl_systemLoad.c on May 19, 2017.
 *
 * Copyright (C) 2012-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 * Global inline functions
 */


/*
 * Global prototypes
 */

/** Estimate the current system load. Must be used from the idle task only and takes above
    1.5s to execute. */
unsigned int gsl_osGetSystemLoad(void);


#endif  /* GSL_SYSTEMLOAD_INCLUDED */

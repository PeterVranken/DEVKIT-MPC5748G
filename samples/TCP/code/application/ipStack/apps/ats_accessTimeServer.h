#ifndef ATS_ACCESSTIMESERVER_INCLUDED
#define ATS_ACCESSTIMESERVER_INCLUDED
/**
 * @file ats_accessTimeServer.h
 * Definition of global interface of module ats_accessTimeServer.c
 *
 * Copyright (C) 2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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


/** The initialization function of the time service. */
void ats_initAccessTimeService(void);

/** The step function of the IP application for fetching time information. */
void ats_mainFunction(void);

/*
 * Global inline functions
 */


#endif  /* ATS_ACCESSTIMESERVER_INCLUDED */

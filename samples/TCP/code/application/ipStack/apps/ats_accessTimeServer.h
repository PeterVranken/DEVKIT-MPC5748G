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

#include "typ_types.h"

/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** Number of fully successful synchronization events with time server. A positive HTTP
    response was received and could be evaluated. */
extern unsigned int DATA_P1(ats_noSyncWithTimeServer);

/** Number of time synchronization events with time information picked from the HTTP header
    of the time server response. A negative HTTP response was received and only the header
    could be evaluated. */
extern unsigned int DATA_P1(ats_noSyncWithHTTPHeader);


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

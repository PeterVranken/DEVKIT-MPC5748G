#ifndef CLG_CANLOGGERONTCP_INCLUDED
#define CLG_CANLOGGERONTCP_INCLUDED
/**
 * @file clg_canLoggerOnTCP.h
 * Definition of global interface of module clg_canLoggerOnTCP.c
 *
 * Copyright (C) 2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/*
 * Defines
 */

/** The CAN logger service is listening on this TCP port for a connection request from
    telnet. */
#define CLG_TCP_PORT_CAN_LOGGER     1234u

/** The maximum number of TCP/IP connections, which can be established with this service in
    parallel. */
#define CLG_MAX_NO_TCP_CONNECTIONS  3u


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** The initialization function of the CAN logger application. */
bool clg_initCanLoggerTcp(void);

/** Get the number of currently established connections with the TCP CAN logger. */
unsigned int clg_getNoConnections(void);

/** The step function of the CAN logger application. */
void clg_mainFunction(void);


/*
 * Global inline functions
 */


#endif  /* CLG_CANLOGGERONTCP_INCLUDED */

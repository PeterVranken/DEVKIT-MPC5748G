#ifndef LWIP_MAIN_FUNCTION_INCLUDED
#define LWIP_MAIN_FUNCTION_INCLUDED
/**
 * @file lwip_lwIPMainFunction.h
 * Definition of global interface of module test_lwipFromGit.c
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


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialization of lwIP and applications using IP. */
void lwip_initIPStack(void);

/** Poll Ethernet driver for meanwhile received Rx frames. */
unsigned int lwip_ethIfPollAllInterfaces(void);

/** Acknowledge the completed transmissin of a Tx frame to lwIP. */
void lwip_onEthBufferTxComplete(void);

/** LwIP clock tick, mainly for check of timeouts. */
void lwip_onTimerTick(void);

/*
 * Global inline functions
 */


#endif  /* LWIP_MAIN_FUNCTION_INCLUDED */

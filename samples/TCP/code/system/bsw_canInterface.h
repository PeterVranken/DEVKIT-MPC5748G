#ifndef BSW_CANINTERFACE_INCLUDED
#define BSW_CANINTERFACE_INCLUDED
/**
 * @file bsw_canInterface.h
 * Definition of global interface of module bsw_canInterface.c
 *
 * Copyright (C) 2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "ede_externalInterfaces.h"

/*
 * Defines
 */


/*
 * Global type definitions
 */

/* Forward reference required by prototype below. */
struct bsw_rxCanMessage_t;



/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** This is the notification callback for received messages. */
void bsw_osOnRxCan(const struct bsw_rxCanMessage_t *pRxCanMsg);

/** Initialize the CAN interface at system startup time. */
bool bsw_osInitCanInterface(void);

/** Get the receiver port of the CAN interface, which can be connected to a dispatcher
    engine in the ASPW. */
ede_eventReceiverPort_t bsw_getCanRxPort(void);

/*
 * Global inline functions
 */


#endif  /* BSW_CANINTERFACE_INCLUDED */

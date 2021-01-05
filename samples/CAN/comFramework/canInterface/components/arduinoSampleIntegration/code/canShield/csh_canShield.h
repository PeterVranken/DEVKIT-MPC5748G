#ifndef CSH_CANSHIELD_INCLUDED
#define CSH_CANSHIELD_INCLUDED
/**
 * @file csh_canShield.h
 * Definition of the user API of a hypothetic CAN shield for Arduino. See readMe.txt in the
 * same directory for design details.
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

/** The fixed number of available message transfer objects. This number limits the range of
    all function parameter and return values dealing with MTO indexes. */
#define CSH_NBR_OF_AVAILABLE_MESSAGE_TRANSFER_OBJECTS   32

/*
 * Global type definitions
 */

/** Network management: The status of the CAN bus. Not all of these are supported by our
    simulation. */
typedef enum csh_stateCanBus_t
{
    csh_stsBusInvalid
    , csh_stsBusShutdown
    , csh_stsBusOff
    , csh_stsBusListening
    , csh_stsBusActive

} csh_stateCanBus_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialization of this compilation unit. Needs to be called first. */
void csh_initModule();

/** Notification of APSW of bus state change: User provided callback. */
extern void csh_callbackOnBusStateChange(csh_stateCanBus_t newState);

/** Register a CAN frame with standard CAN ID. */
void csh_registerStdCanFrame( uint8_t idxMto
                            , boolean isReception
                            , uint16_t canStdIdFilter
                            , uint16_t canIdMask
                            );

/** Register a CAN frame with extended CAN ID. */
void csh_registerExtCanFrame( uint8_t idxMto
                            , boolean isReception
                            , uint32_t canExtIdFilter
                            , uint32_t canIdMask
                            );

/** Send a CAN frame with standard ID. */
boolean csh_sendStdCanFrame(uint16_t canStdId, const uint8_t *pData, uint8_t DLC);

/** Send a CAN frame with extended ID. */
boolean csh_sendExtCanFrame(uint32_t canExtId, const uint8_t *pData, uint8_t DLC);

/** Notification of APSW of frame reception: User provided callback. */
extern void csh_callbackOnReceiveCanFrame(uint8_t idxMto);

/** The APSW can use this function to try to recover from a bus-off. */
void csh_restartCanBus();

/** Query function from reception callback: Does the received frame have a standard CAN ID? */
boolean csh_getHasCanStdId(uint8_t idxMto);

/** Query function from reception callback: Get the standard CAN ID of the received frame. */
uint16_t csh_getCanStdId(uint8_t idxMto);

/** Query function from reception callback: Get the extended CAN ID of the received frame. */
uint32_t csh_getCanExtId(uint8_t idxMto);

/** Query function from reception callback: Get the DLC of the received frame. */
uint8_t csh_getCanDLC(uint8_t idxMto);

/** Query function from reception callback: Get the frame contents. */
void csh_getFrameData(uint8_t idxMto, uint8_t sizeOfBuffer, uint8_t *buffer);

/** Simulation API: A status change of the bus is simulated. */
void csh_hwBusStateChange(csh_stateCanBus_t newState);

/** Simulation API: Query if the APSW has requested an attempt for bus recovery. */
boolean csh_hwGetRestartBus();

/** Simulation API: A frame is received. Not intended for use by APSW. */
void csh_hwFrameReceived(uint16_t canId, uint8_t DLC, const uint8_t *pData);

#endif  /* CSH_CANSHIELD_INCLUDED */

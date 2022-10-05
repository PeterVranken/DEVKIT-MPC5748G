#ifndef CBK_CALLBACKS_DEFINED
#define CBK_CALLBACKS_DEFINED
/**
 * @file cbk_callbacks.h
 * Declaration of callbacks for the CAN interface engine for cluster arduinoSampleIntegration.
 *
 * This file has been created with comFramework - codeGenerator version 1.11.2,
 * see http://sourceforge.net/projects/comframe/
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

#include "types.h"
#include "ede_eventDispatcherEngine.h"


/*
 * Defines
 */

 

/*
 * Type definitions
 */

/** The different status bits of the CAN transmission status word. */
typedef enum cbk_enumStsTransmission_t
{
    /** No bit is set, no error or problem or else is reported. */
    cbk_stsTransm_okay = 0,

    /** The frame has never been received since startup of the interface. Only for inbound
        frames. */
    cbk_stsTransm_neverReceived = 1,

    /** The frame could not be sent, send buffer full. Only for outbound frames. */
    cbk_stsTransm_errSendBufferFull = 1,

    /** The frame has not been received timely. */
    cbk_stsTransm_errTimeout = 2,

    /** The received frame has a data error; the checksum doesn't match. No signals will be
        extracted. */ 
    cbk_stsTransm_errChecksum = 4,

    /** The sequence counter of the received frame indicates a lost frame. */
    cbk_stsTransm_errSequence = 8,

    /** The received frame doesn't have the expected size. No signals can be extracted. */
    cbk_stsTransm_errDLC = 16

} cbk_enumStsTransmission_t;


/** The type of the transmission status. The encoding of the information is done bit-wise,
    see enumeration \a cbk_enumStsTransmission_t. The status variable is neither defined as an
    enumeration nor as a bit field in order to permit the use of binary operations to
    filter and combine status bits. */
typedef uint8_t cbk_stsTransmission_t;

 

/*
 * Data declarations
 */

 

/*
 * Function declarations
 */

/** Initialization of the interface: Register all affected frames. */
void cbk_initInterface();

#endif // !defined(CBK_CALLBACKS_DEFINED)
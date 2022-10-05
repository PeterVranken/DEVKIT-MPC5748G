#ifndef CDT_CANDATATABLES_DEFINED
#define CDT_CANDATATABLES_DEFINED
/**
 * @file cdt_canDataTables.h
 * 
 * This module contains data tables, which contain all relevant information from the CAN
 * network database files about messages and signals. Mainly the callback functions of the
 * event dispatchers will access the tables to implement the message-indvidual behavior like
 * different timing patterns, different checksum protections, different size, etc.
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

#include "typ_types.h"
#include "cap_canApi.h"
#include "cst_canStatistics.h"


/*
 * Defines
 */


/*
 * Type definitions
 */

/** The decription of a CAN message as required for implementation of its send/receive
    behavior in the callbacks of the event dispatchers. */
typedef struct cdt_canMessage_t
{
    /** Name of message. */
    const char *name;

    /** The CAN bus, which the reception event is simulated for. */
    unsigned int idxCanBus;

    /** Boolean information, whether \a canId designates an extended 29 Bit ID. */
    unsigned long isExtId;

    /** The CAN ID. */
    unsigned long canId;

    /** The size of the message contents in Byte. */
    unsigned int size;

    /** An external function, which is called to unpack a received CAN message into the
        global CAN API. */
    void (*fctUnpackApiMsg)(const uint8_t msgContentAry[]);

    /** An external function, which is called to pack the message. */
    void (*fctPackApiMsg)(uint8_t msgContentAry[]);

    /** The transmission timing pattern to be applied to the message. */
    cap_enumSendMode_t sendMode;

    /** The index of the message in its particular group. A group are all messages, which are
        implemented by the same (hand-coded) handler in the CAN interface. The index
        supports easy and efficient implementation of handler owned, message related context
        data. */
    unsigned int idxHandlerCtxData;

    /** The pointer to the transmission info of the given message in the global CAN API. */
    cap_infoTransmission_t *pInfoTransmission;

    /** The nominal cycle time in ms if the message is not purely event triggered. */
    unsigned int tiCycle;

    /** The minimum distance of reception events if the message is event triggered. */
    unsigned int tiMinDistance;

} cdt_canMessage_t;


/** The description of a CAN signal as required for the specific functionality of this
    applicatin: The user can select signals rather than messages for reception and sending. */
typedef struct cdt_canSignal_t
{
    /** Name of signal. */
    const char *name;

    /** Reference to containg CAN message: Index into table of all messages, either
        cdt_canRxMsgAry or cdt_canTxMsgAry. */
    unsigned int idxMsg;

    /** Reference to containg CAN message: Table of Rx or Tx messages? */
    boolean_t isReceived;

    /** Getter for signal: Has a signal independent, generic prototype and allows to read
        the signal value from the global API as uniform type \a float. */
    float (*getter)(void);

    /** Setter for signal: Has a signal independent, generic prototype and allows to set
        the signal value in the global API. */
    void (*setter)(float newValue);

    /** The minimum physical value of the signal. */
    float min;

    /** The maximum physical value of the signal. */
    float max;

    /** The unit of the signal value. */
    const char *unit;

} cdt_canSignal_t;



/*
 * Data declarations
 */

/** A global table with the description of all CAN messages which are received by the device.
    The description of the messages is as detailed as required for implementation of their
    send/receive behavior in the callbacks of the event dispatchers. */
extern const cdt_canMessage_t cdt_canRxMsgAry[CST_NO_CAN_MSGS_RECEIVED];

/** A global table with the description of all CAN messages which are sent by the device.
    The description of the messages is as detailed as required for implementation of their
    send/receive behavior in the callbacks of the event dispatchers. */
extern const cdt_canMessage_t cdt_canTxMsgAry[CST_NO_CAN_MSGS_SENT];

/** A global table with the description of all CAN signals as required for the specific
    functionality of this application: The user can select signals rather than messages for
    reception and sending. */
extern const cdt_canSignal_t cdt_canSignalAry[CST_NO_SENT_AND_RECEIVED_CAN_SIGNALS];


/*
 * Function declarations
 */


/*
 * Inline function definitions
 */

#endif // !defined(CDT_CANDATATABLES_DEFINED)
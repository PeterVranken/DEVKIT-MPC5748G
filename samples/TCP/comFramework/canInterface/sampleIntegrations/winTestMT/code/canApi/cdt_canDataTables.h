#ifndef CDT_CANDATATABLES_DEFINED
#define CDT_CANDATATABLES_DEFINED
/**
 * @file cdt_canDataTables.h
 * 
 * This module contains data tables, which contain all relevant information from the CAN
 * network database files about frames and signals. Mainly the callback functions of the
 * event dispatchers will access the tables to implement the frame-indvidual behavior like
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

#include "types.h"
#include "ede_eventDispatcherEngine.h"
#include "cst_canStatistics.h"
#include "cap_canApi.h"


/*
 * Defines
 */

/** Helper to get CAN IDs: Get a 11 Bit standard CAN ID object from the raw number. */
#define CDT_STD_CAN_ID(id11Bit)         ((cdt_canId_t){.isExtId=0, .id=(id11Bit)})

/** Helper to get CAN IDs: Get a 29 Bit standard CAN ID object from the raw number. */
#define CDT_EXT_CAN_ID(id29Bit)         ((cdt_canId_t){.isExtId=1, .id=(id29Bit)})

/** Helper to get CAN IDs: Get CAN ID object from raw number and Boolean \a isExt. */
#define CDT_CAN_ID(ID, isExt)           ((cdt_canId_t){.isExtId=(isExt), .id=(ID)})


/*
 * Type definitions
 */

/** CAN ID: The number and the Boolean distinction between 11 and 29 Bit ID. */
typedef union cdt_canId_t
{
    /** An anonymous struct provides the normally used access to the fields. */
    struct
    {
        /** The CAN ID.\n
              Note, this field is intentionally not modelled as 29 Bit integer in order to
            avoid undefined values for unused bit: This supports efficient binary
            comparison of CAN IDs. */
        unsigned long id:31;

        /** The Boolean distinction, whether we have an 11 or a 29 Bit CAN ID. */
        unsigned long isExtId:1;
    };

    /** An alternative 32 Bit integer access supports efficient CAN ID comparisons (equal
        or not). */
    unsigned long uniqueCanId:32;

} cdt_canId_t;

_Static_assert(sizeof(cdt_canId_t) == sizeof(uint32_t), "Unexpected size of data object");

/** The description of a CAN frame as required for implementation of its send/receive
    behavior in the callbacks of the event dispatchers. */
typedef struct cdt_canFrame_t
{
    /** The CAN bus, which the reception event is simulated for. */
    unsigned int idxCanBus;

    /** The CAN ID. */
    cdt_canId_t canId;

    /** The send direction. Only transmitted, affected frames are listed; if it is not
        received then it is sent. */
    boolean_t isReceived;

    /** The size of the frame contents in Byte. */
    unsigned int size;

    /** An external function, which is called to unpack a received CAN frame into the
        global CAN API and to run the E2E validation on the received contents. */
    boolean_t (*fctUnpackApiFrameAndValidate)(const uint8_t frameContentAry[]);

    /** An external function, which randomly fills all signal values in the global CAN API
        for the frame. */
    void (*fctRandomFillApiFrame)();

    /** An external function, which is called to E2E protect the frame. */
    void (*fctProtectApiFrame)();

    /** An external function, which is called to pack the frame. */
    void (*fctPackApiFrame)(uint8_t frameContentAry[]);

    /** The transmission timing pattern to be applied to the frame. */
    cap_enumSendMode_t sendMode;

    /** The index of the frame in its particular group. A group are all frames, which are
        implemented by the same (hand-coded) handler in the CAN interface. The index
        supports easy and efficient implementation of handler owned, frame related context
        data. */
    unsigned int idxHandlerCtxData;

    /** The pointer to the transmission info of the given frame in the global CAN API. */
    cap_infoTransmission_t *pInfoTransmission;

    /** The nominal cycle time in ms if the frame is not purely event triggered. */
    unsigned int tiCycle;

    /** The minimum distance of reception events if the frame is event triggered. */
    unsigned int tiMinDistance;

} cdt_canFrame_t;


/*
 * Data declarations
 */

/** A global table with the description of all affected CAN frames as required for
    implementation of their send/receive behavior in the callbacks of the event
    dispatchers. */
extern const cdt_canFrame_t cdt_canFrameAry[CST_NO_CAN_FRAMES];


/*
 * Function declarations
 */


/*
 * Inline function definitions
 */

#endif // !defined(CDT_CANDATATABLES_DEFINED)
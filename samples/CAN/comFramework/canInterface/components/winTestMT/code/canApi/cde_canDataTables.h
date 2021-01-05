#ifndef CDE_CANDATATABLES_DEFINED
#define CDE_CANDATATABLES_DEFINED
/**
 * @file cde_canDataTables.h
 * 
 * This module contains data tables, which contain all relevant information from the CAN
 * network database files about frames and signals. Mainly the callback functions of the
 * event dispatchers will access the tables to implement the frame-indvidual behavior like
 * different timing patterns, different checksum protections, different DLC, etc.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.0,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "cde_canStatistics.h"


/*
 * Defines
 */

/** Both, operating system and CAN interface use tables to store frame properties and use
    the index into these tables as handle to the frame in progress. The operating system
    uses separate tables for in- and outbound, while the CAN interface implementation in
    this sample prefers a single table. This requires a mapping of the OS handle to the CAN
    interface handle.\n
      Here is the mapping for the inbound frames. */
#ifdef __GNUC__
#define CDE_MAP_HANDLE_RECEIVED_FRAME_OS_TO_CAN_IF(hOS) \
                                            ({assert((hOS) < CDE_NO_CAN_FRAMES); (hOS);})
#else
#define CDE_MAP_HANDLE_RECEIVED_FRAME_OS_TO_CAN_IF(hOS)  (hOS)
#endif

/** Both, operating system and CAN interface use tables to store frame properties and use
    the index into these tables as handle to the frame in progress. The operating system
    uses separate tables for in- and outbound, while the CAN interface implementation in
    this sample prefers a single table. This requires a mapping of the CAN interface handle
    to the OS handle.\n
      Here is the mapping for the outbound frames. */
#ifdef __GNUC__
#define CDE_MAP_HANDLE_SENT_FRAME_CAN_IF_TO_OS(hIF)                                         \
            ({assert((hIF)>=(CDE_NO_CAN_FRAMES_RECEIVED)                                    \
                     &&  (hIF) < ose_noSentCanFrames + (CDE_NO_CAN_FRAMES_RECEIVED)         \
                    );                                                                      \
              (hIF)-(CDE_NO_CAN_FRAMES_RECEIVED);                                           \
            })
#else
#define CDE_MAP_HANDLE_SENT_FRAME_CAN_IF_TO_OS(hIF)     ((hIF)-(CDE_NO_CAN_FRAMES_RECEIVED))
#endif
 

/*
 * Type definitions
 */

/** The decription of a CAN frame as required for implementation of its send/receive
    behavior in the callbacks of the event dispatchers. */
typedef struct cde_canFrame_t
{
    /** The CAN bus, which the reception event is simulated for. */
    unsigned int idxCanBus;

    /** The CAN ID. */
    unsigned long canId;

    /** The send direction. Only transmitted, affected frames are listed; if it is not
        received then it is sent. */
    boolean_t isReceived;

    /** The size of the frame contents in Byte. */
    unsigned int DLC;

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

} cde_canFrame_t;
 

/*
 * Data declarations
 */

/** A global table with the description of all affected CAN frames as required for
    implementation of their send/receive behavior in the callbacks of the event
    dispatchers. */
extern const cde_canFrame_t cde_canFrameAry[CDE_NO_CAN_FRAMES];
 

/*
 * Function declarations
 */

#endif // !defined(CDE_CANDATATABLES_DEFINED)
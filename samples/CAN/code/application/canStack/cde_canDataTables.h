#ifndef CDE_CANDATATABLES_DEFINED
#define CDE_CANDATATABLES_DEFINED
/**
 * @file cde_canDataTables.h
 * 
 * This module contains data tables, which contain all relevant information from the CAN
 * network database files about frames and signals. Mainly the callback functions of the
 * event dispatchers will access the tables to implement the frame-indvidual behavior like
 * different timing patterns, different checksum protections, different size, etc.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.4,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "cde_canStatistics.h"


/*
 * Defines
 */

/** Both, operating system and CAN interface use their handles for identification of a
    frame. The operating system uses separate handles for in- and outbound, while the CAN
    interface enginge has one solid handle space for all frames. This requires a mapping of
    the OS handle to the CAN interface handle.\n
      Here is the mapping for the inbound frames. */
#define CDE_MAP_HANDLE_RX_FRAME_OS_TO_CAN_IF(hOS)                                           \
            (assert((hOS) < (CDE_NO_CAN_FRAMES_RECEIVED)+(BSW_IDX_FIRST_RX_MAILBOX)),       \
             (hOS)-(BSW_IDX_FIRST_RX_MAILBOX)                                               \
            )

/** Both, operating system and CAN interface use their handles for identification of a
    frame. The operating system uses separate handles for in- and outbound, while the CAN
    interface enginge has one solid handle space for all frames. This requires a mapping of
    CAN interface handle to OS handle.\n
      Here is the mapping for the inbound frames. */
#define CDE_MAP_HANDLE_RX_FRAME_CAN_IF_TO_OS(hIF)                                           \
            (assert((hIF)+(BSW_IDX_FIRST_RX_MAILBOX) <= (BSW_IDX_LAST_RX_MAILBOX)),         \
             (hIF)+(BSW_IDX_FIRST_RX_MAILBOX)                                               \
            )

/** Our data tables with frame decriptions are separated in Rx and Tx frames. The interface
    engine has one solid handle space for all frames. This macro computes the array index of
    a sent frame from the handle used by the engine. The index relates to array \a
    cde_canTxFrameAry. */
#define CDE_MAP_HANDLE_RX_FRAME_CAN_IF_TO_IDX_RX(idxFrCde)                                  \
            (assert((idxFrCde) < sizeOfAry(cde_canRxFrameAry)),(idxFrCde))

/** Both, operating system and CAN interface use their handles for identification of a
    frame. The operating system uses separate handles for in- and outbound, while the CAN
    interface enginge has one solid handle space for all frames. This requires a mapping of
    the OS handle to the CAN interface handle.\n
      Here is the mapping for the outbound frames. */
#define CDE_MAP_HANDLE_TX_FRAME_OS_TO_CAN_IF(hOS)                                           \
            (assert((hOS) >= (BSW_IDX_FIRST_TX_MAILBOX)                                     \
                    &&  (hOS)-(BSW_IDX_FIRST_TX_MAILBOX)+(CDE_NO_CAN_FRAMES_RECEIVED)       \
                        < (CDE_NO_CAN_FRAMES)                                               \
                   ),                                                                       \
             (hOS)-(BSW_IDX_FIRST_TX_MAILBOX)+(CDE_NO_CAN_FRAMES_RECEIVED)                  \
            )

/** Both, operating system and CAN interface use their handles for identification of a
    frame. The operating system uses separate handles for in- and outbound, while the CAN
    interface enginge has one solid handle space for all frames. This requires a mapping of
    CAN interface handle to OS handle.\n
      Here is the mapping for the outbound frames. */
#define CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_OS(hIF)                                           \
            (assert((hIF) >= (CDE_NO_CAN_FRAMES_RECEIVED)                                   \
                    &&  (hIF)+(BSW_IDX_FIRST_TX_MAILBOX)                                    \
                        <= (BSW_IDX_LAST_TX_MAILBOX)+(CDE_NO_CAN_FRAMES_RECEIVED)           \
                   ),                                                                       \
             (hIF)-(CDE_NO_CAN_FRAMES_RECEIVED)+(BSW_IDX_FIRST_TX_MAILBOX)                  \
            )

/** Our data tables with frame decriptions are separated in Rx and Tx frames. The interface
    engine has one solid handle space for all frames. This macro computes the array index of
    a received frame from the handle used by the engine. The index relates to array \a
    cde_canRxFrameAry. */
#define CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_IDX_TX(idxFrCde)                                  \
            (assert((idxFrCde)-(CDE_NO_CAN_FRAMES_RECEIVED) < sizeOfAry(cde_canTxFrameAry)),\
             (idxFrCde)-(CDE_NO_CAN_FRAMES_RECEIVED)                                        \
            )


/*
 * Type definitions
 */

/** The decription of a CAN frame as required for implementation of its send/receive
    behavior in the callbacks of the event dispatchers. */
typedef struct cde_canFrame_t
{
    /** The CAN bus, which the reception event is simulated for. */
    unsigned int idxCanBus;

    /** Boolean information, whether \a canId designates an extended 29 Bit ID. */
    unsigned long isExtId;

    /** The CAN ID. */
    unsigned long canId;

    /** The send direction. Only transmitted, affected frames are listed; if it is not
        received then it is sent. */
    /// @todo Remove: Became obsolete due to separate tables for Rx and Tx
    boolean_t isReceived;

    /** The size of the frame contents in Byte. */
    unsigned int size;

    /** An external function, which is called to unpack a received CAN frame into the
        global CAN API. */
    void (*fctUnpackApiFrame)(const uint8_t frameContentAry[]);

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

/** A global table with the description of all CAN frames which are received by the device.
    The description of the frames is as detailed as required for implementation of their
    send/receive behavior in the callbacks of the event dispatchers. */
extern const cde_canFrame_t cde_canRxFrameAry[CDE_NO_CAN_FRAMES_RECEIVED];

/** A global table with the description of all CAN frames which are sent by the device.
    The description of the frames is as detailed as required for implementation of their
    send/receive behavior in the callbacks of the event dispatchers. */
extern const cde_canFrame_t cde_canTxFrameAry[CDE_NO_CAN_FRAMES_SENT];


/*
 * Function declarations
 */


/*
 * Inline function definitions
 */

#endif // !defined(CDE_CANDATATABLES_DEFINED)
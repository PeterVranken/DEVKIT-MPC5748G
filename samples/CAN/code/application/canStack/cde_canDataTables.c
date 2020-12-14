/**
 * @file cde_canDataTables.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "typ_types.h"
#include "cap_canApi.h"
#include "cde_canStatistics.h"
#include "cde_canDataTables.h"


/*
 * Defines
 */


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** A global table with the description of all CAN frames which are received by the device.
    The description of the frames is as detailed as required for implementation of their
    send/receive behavior in the callbacks of the event dispatchers. */
const cde_canFrame_t cde_canRxFrameAry[CDE_NO_CAN_FRAMES_RECEIVED] =
{
    [0] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1024
        , .isReceived = true
        , .size = 4
        , .fctUnpackApiFrame = cap_unpackApi_PT_StateEcu01
        , .fctPackApiFrame = cap_packApi_PT_StateEcu01
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_StateEcu01_1024().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 20
        },
    [1] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1040
        , .isReceived = true
        , .size = 4
        , .fctUnpackApiFrame = cap_unpackApi_PT_StateEcu02
        , .fctPackApiFrame = cap_packApi_PT_StateEcu02
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 1
        , .pInfoTransmission = &cap_getFrameSts_PT_StateEcu02_1040().infoTransmission
        , .tiCycle = 25
        , .tiMinDistance = 20
        },
    [2] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 2032
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_UserLimits
        , .fctPackApiFrame = cap_packApi_PT_UserLimits
        , .sendMode = cap_enumSendMode_event
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_UserLimits_2032().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 65
        },
}; /* cde_canRxFrameAry */

/** A global table with the description of all CAN frames which are sent by the device.
    The description of the frames is as detailed as required for implementation of their
    send/receive behavior in the callbacks of the event dispatchers. */
const cde_canFrame_t cde_canTxFrameAry[CDE_NO_CAN_FRAMES_SENT] =
{
    [0] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1536
        , .isReceived = false
        , .size = 6
        , .fctUnpackApiFrame = cap_unpackApi_PT_InfoPowerDisplay
        , .fctPackApiFrame = cap_packApi_PT_InfoPowerDisplay
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_InfoPowerDisplay_1536().infoTransmission
        , .tiCycle = 30
        , .tiMinDistance = 20
        },
    [1] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1537
        , .isReceived = false
        , .size = 6
        , .fctUnpackApiFrame = cap_unpackApi_PT_StatusPowerDisplay
        , .fctPackApiFrame = cap_packApi_PT_StatusPowerDisplay
        , .sendMode = cap_enumSendMode_mixed
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_StatusPowerDisplay_1537().infoTransmission
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [2] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1538
        , .isReceived = false
        , .size = 1
        , .fctUnpackApiFrame = cap_unpackApi_PT_LimitsPowerDisplay
        , .fctPackApiFrame = cap_packApi_PT_LimitsPowerDisplay
        , .sendMode = cap_enumSendMode_event
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_LimitsPowerDisplay_1538().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 20
        },
}; /* cde_canTxFrameAry */

#if (2) != CDE_NO_CAN_FRAMES_RECEIVED_REGULAR \
    ||  (1) != CDE_NO_CAN_FRAMES_RECEIVED_EVENT \
    ||  (0) != CDE_NO_CAN_FRAMES_RECEIVED_MIXED \
    ||  (1) != CDE_NO_CAN_FRAMES_SENT_REGULAR \
    ||  (1) != CDE_NO_CAN_FRAMES_SENT_EVENT \
    ||  (1) != CDE_NO_CAN_FRAMES_SENT_MIXED
# error Invalid index ranges detected. Looks like an inconsistency in your code generation templates
#endif



/*
 * Function implementation
 */


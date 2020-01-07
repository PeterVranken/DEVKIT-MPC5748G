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
 * Copyright (C) 2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
        { .name = "StateEcu01"
        , .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1024
        , .isReceived = true
        , .size = 4
        , .fctUnpackApiFrame = cap_unpackApi_PT_StateEcu01
        , .fctPackApiFrame = cap_packApi_PT_StateEcu01
        , .sendMode = cap_enumSendMode_0_cyclic
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_StateEcu01_1024().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 20
        },
    [1] =
        { .name = "StateEcu02"
        , .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1040
        , .isReceived = true
        , .size = 4
        , .fctUnpackApiFrame = cap_unpackApi_PT_StateEcu02
        , .fctPackApiFrame = cap_packApi_PT_StateEcu02
        , .sendMode = cap_enumSendMode_0_cyclic
        , .idxHandlerCtxData = 1
        , .pInfoTransmission = &cap_getFrameSts_PT_StateEcu02_1040().infoTransmission
        , .tiCycle = 25
        , .tiMinDistance = 20
        },
    [2] =
        { .name = "UserLimits"
        , .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 2032
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_UserLimits
        , .fctPackApiFrame = cap_packApi_PT_UserLimits
        , .sendMode = cap_enumSendMode_1_event
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
        { .name = "InfoPowerDisplay"
        , .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1536
        , .isReceived = false
        , .size = 6
        , .fctUnpackApiFrame = cap_unpackApi_PT_InfoPowerDisplay
        , .fctPackApiFrame = cap_packApi_PT_InfoPowerDisplay
        , .sendMode = cap_enumSendMode_0_cyclic
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_InfoPowerDisplay_1536().infoTransmission
        , .tiCycle = 30
        , .tiMinDistance = 20
        },
    [1] =
        { .name = "StatusPowerDisplay"
        , .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1537
        , .isReceived = false
        , .size = 6
        , .fctUnpackApiFrame = cap_unpackApi_PT_StatusPowerDisplay
        , .fctPackApiFrame = cap_packApi_PT_StatusPowerDisplay
        , .sendMode = cap_enumSendMode_2_cyclicOrEvent
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_StatusPowerDisplay_1537().infoTransmission
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [2] =
        { .name = "LimitsPowerDisplay"
        , .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1538
        , .isReceived = false
        , .size = 1
        , .fctUnpackApiFrame = cap_unpackApi_PT_LimitsPowerDisplay
        , .fctPackApiFrame = cap_packApi_PT_LimitsPowerDisplay
        , .sendMode = cap_enumSendMode_1_event
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



/** A global table with the description of all CAN signals as required for the specific
    functionality of this application: The user can select signals rather than frames for
    reception and sending. */
const cde_canSignal_t cde_canSignalAry[CDE_NO_SENT_AND_RECEIVED_CAN_SIGNALS] =
{
    [0] =
        { .name = "checksum"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PT_1024_checksum
        , .setter = set_PT_1024_checksum
        , .min = 0.0
        , .max = 255.0
        , .unit = ""
        },
    [1] =
        { .name = "speedOfRotation"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PT_1024_speedOfRotation
        , .setter = set_PT_1024_speedOfRotation
        , .min = 0.0
        , .max = 6500.0
        , .unit = "rpm"
        },
    [2] =
        { .name = "sequenceCounter"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PT_1024_sequenceCounter
        , .setter = set_PT_1024_sequenceCounter
        , .min = 0.0
        , .max = 14.0
        , .unit = ""
        },
    [3] =
        { .name = "checksum"
        , .idxFrame = 1
        , .isReceived = true
        , .getter = get_PT_1040_checksum
        , .setter = set_PT_1040_checksum
        , .min = 0.0
        , .max = 255.0
        , .unit = ""
        },
    [4] =
        { .name = "sequenceCounter"
        , .idxFrame = 1
        , .isReceived = true
        , .getter = get_PT_1040_sequenceCounter
        , .setter = set_PT_1040_sequenceCounter
        , .min = 15.0
        , .max = 1.0
        , .unit = ""
        },
    [5] =
        { .name = "torque"
        , .idxFrame = 1
        , .isReceived = true
        , .getter = get_PT_1040_torque
        , .setter = set_PT_1040_torque
        , .min = -500.0
        , .max = 500.0
        , .unit = "Nm"
        },
    [6] =
        { .name = "sequenceCounter"
        , .idxFrame = 2
        , .isReceived = true
        , .getter = get_PT_2032_sequenceCounter
        , .setter = set_PT_2032_sequenceCounter
        , .min = 1.0
        , .max = 14.0
        , .unit = ""
        },
    [7] =
        { .name = "minSpeedOfRotation"
        , .idxFrame = 2
        , .isReceived = true
        , .getter = get_PT_2032_minSpeedOfRotation
        , .setter = set_PT_2032_minSpeedOfRotation
        , .min = 0.0
        , .max = 6500.0
        , .unit = "rpm"
        },
    [8] =
        { .name = "maxSpeedOfRotation"
        , .idxFrame = 2
        , .isReceived = true
        , .getter = get_PT_2032_maxSpeedOfRotation
        , .setter = set_PT_2032_maxSpeedOfRotation
        , .min = 0.0
        , .max = 6500.0
        , .unit = "rpm"
        },
    [9] =
        { .name = "checksum"
        , .idxFrame = 2
        , .isReceived = true
        , .getter = get_PT_2032_checksum
        , .setter = set_PT_2032_checksum
        , .min = 0.0
        , .max = 255.0
        , .unit = ""
        },
    [10] =
        { .name = "minPower"
        , .idxFrame = 2
        , .isReceived = true
        , .getter = get_PT_2032_minPower
        , .setter = set_PT_2032_minPower
        , .min = -10.0
        , .max = 240.0
        , .unit = "KW"
        },
    [11] =
        { .name = "maxPower"
        , .idxFrame = 2
        , .isReceived = true
        , .getter = get_PT_2032_maxPower
        , .setter = set_PT_2032_maxPower
        , .min = -10.0
        , .max = 240.0
        , .unit = "KW"
        },

    [12] =
        { .name = "checksum"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PT_1536_checksum
        , .setter = set_PT_1536_checksum
        , .min = 0.0
        , .max = 255.0
        , .unit = ""
        },
    [13] =
        { .name = "sequenceCounter"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PT_1536_sequenceCounter
        , .setter = set_PT_1536_sequenceCounter
        , .min = 0.0
        , .max = 14.0
        , .unit = ""
        },
    [14] =
        { .name = "power"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PT_1536_power
        , .setter = set_PT_1536_power
        , .min = -500000.0
        , .max = 500000.0
        , .unit = "W"
        },
    [15] =
        { .name = "state"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PT_1536_state
        , .setter = set_PT_1536_state
        , .min = 0.0
        , .max = 2.0
        , .unit = ""
        },
    [16] =
        { .name = "noDlcErrors"
        , .idxFrame = 1
        , .isReceived = false
        , .getter = get_PT_1537_noDlcErrors
        , .setter = set_PT_1537_noDlcErrors
        , .min = 0.0
        , .max = 2047.0
        , .unit = ""
        },
    [17] =
        { .name = "noCheckSumErrors"
        , .idxFrame = 1
        , .isReceived = false
        , .getter = get_PT_1537_noCheckSumErrors
        , .setter = set_PT_1537_noCheckSumErrors
        , .min = 0.0
        , .max = 2047.0
        , .unit = ""
        },
    [18] =
        { .name = "noSqcErrors"
        , .idxFrame = 1
        , .isReceived = false
        , .getter = get_PT_1537_noSqcErrors
        , .setter = set_PT_1537_noSqcErrors
        , .min = 0.0
        , .max = 2047.0
        , .unit = ""
        },
    [19] =
        { .name = "sequenceCounter"
        , .idxFrame = 1
        , .isReceived = false
        , .getter = get_PT_1537_sequenceCounter
        , .setter = set_PT_1537_sequenceCounter
        , .min = 1.0
        , .max = 126.0
        , .unit = ""
        },
    [20] =
        { .name = "checksum"
        , .idxFrame = 1
        , .isReceived = false
        , .getter = get_PT_1537_checksum
        , .setter = set_PT_1537_checksum
        , .min = 0.0
        , .max = 255.0
        , .unit = ""
        },
    [21] =
        { .name = "sequenceCounter"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1538_sequenceCounter
        , .setter = set_PT_1538_sequenceCounter
        , .min = 1.0
        , .max = 6.0
        , .unit = ""
        },
    [22] =
        { .name = "belowMinSpeedOfRotation"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1538_belowMinSpeedOfRotation
        , .setter = set_PT_1538_belowMinSpeedOfRotation
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [23] =
        { .name = "aboveMaxSpeedOfRotation"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1538_aboveMaxSpeedOfRotation
        , .setter = set_PT_1538_aboveMaxSpeedOfRotation
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [24] =
        { .name = "belowMinPower"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1538_belowMinPower
        , .setter = set_PT_1538_belowMinPower
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [25] =
        { .name = "aboveMaxPower"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1538_aboveMaxPower
        , .setter = set_PT_1538_aboveMaxPower
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
}; /* cde_canSignalAry */


/*
 * Function implementation
 */


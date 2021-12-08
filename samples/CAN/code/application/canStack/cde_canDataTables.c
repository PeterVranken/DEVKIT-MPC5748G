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
#include "can_canRuntime.h"
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
        { .name = "PWM_out"
        , .idxCanBus = CAN_BUS_PWM
        , .isExtId = false
        , .canId = 1001
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PWM_PWM_out
        , .fctPackApiFrame = cap_packApi_PWM_PWM_out
        , .sendMode = cap_enumSendMode_1_event
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PWM_PWM_out_1001().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 20
        },
    [1] =
        { .name = "StateEcu01"
        , .idxCanBus = CAN_BUS_PT
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
    [2] =
        { .name = "StateEcu02"
        , .idxCanBus = CAN_BUS_PT
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
    [3] =
        { .name = "UserLimits"
        , .idxCanBus = CAN_BUS_PT
        , .isExtId = false
        , .canId = 2032
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_UserLimits
        , .fctPackApiFrame = cap_packApi_PT_UserLimits
        , .sendMode = cap_enumSendMode_1_event
        , .idxHandlerCtxData = 1
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
        { .name = "PWM_in"
        , .idxCanBus = CAN_BUS_PWM
        , .isExtId = false
        , .canId = 1000
        , .isReceived = false
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PWM_PWM_in
        , .fctPackApiFrame = cap_packApi_PWM_PWM_in
        , .sendMode = cap_enumSendMode_0_cyclic
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PWM_PWM_in_1000().infoTransmission
        , .tiCycle = 100
        , .tiMinDistance = 20
        },
    [1] =
        { .name = "InfoPowerDisplay"
        , .idxCanBus = CAN_BUS_PT
        , .isExtId = false
        , .canId = 1536
        , .isReceived = false
        , .size = 6
        , .fctUnpackApiFrame = cap_unpackApi_PT_InfoPowerDisplay
        , .fctPackApiFrame = cap_packApi_PT_InfoPowerDisplay
        , .sendMode = cap_enumSendMode_0_cyclic
        , .idxHandlerCtxData = 1
        , .pInfoTransmission = &cap_getFrameSts_PT_InfoPowerDisplay_1536().infoTransmission
        , .tiCycle = 30
        , .tiMinDistance = 20
        },
    [2] =
        { .name = "StatusPowerDisplay"
        , .idxCanBus = CAN_BUS_PT
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
    [3] =
        { .name = "LimitsPowerDisplay"
        , .idxCanBus = CAN_BUS_PT
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
    ||  (2) != CDE_NO_CAN_FRAMES_RECEIVED_EVENT \
    ||  (0) != CDE_NO_CAN_FRAMES_RECEIVED_MIXED \
    ||  (2) != CDE_NO_CAN_FRAMES_SENT_REGULAR \
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
        { .name = "LED_2_DS10_inhibit"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_LED_2_DS10_inhibit
        , .setter = set_PWM_1001_LED_2_DS10_inhibit
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [1] =
        { .name = "LED_4_DS11_inhibit"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_LED_4_DS11_inhibit
        , .setter = set_PWM_1001_LED_4_DS11_inhibit
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [2] =
        { .name = "LED_5_DS5_inhibit"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_LED_5_DS5_inhibit
        , .setter = set_PWM_1001_LED_5_DS5_inhibit
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [3] =
        { .name = "PA1_J3_pin1_inhibit"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_PA1_J3_pin1_inhibit
        , .setter = set_PWM_1001_PA1_J3_pin1_inhibit
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [4] =
        { .name = "LED_2_DS10_frequency"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_LED_2_DS10_frequency
        , .setter = set_PWM_1001_LED_2_DS10_frequency
        , .min = 2.0
        , .max = 1000.0
        , .unit = "Hz"
        },
    [5] =
        { .name = "LED_4_DS11_frequency"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_LED_4_DS11_frequency
        , .setter = set_PWM_1001_LED_4_DS11_frequency
        , .min = 2.0
        , .max = 1000.0
        , .unit = "Hz"
        },
    [6] =
        { .name = "LED_5_DS5_frequency"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_LED_5_DS5_frequency
        , .setter = set_PWM_1001_LED_5_DS5_frequency
        , .min = 2.0
        , .max = 1000.0
        , .unit = "Hz"
        },
    [7] =
        { .name = "PA1_J3_pin1_frequency"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_PA1_J3_pin1_frequency
        , .setter = set_PWM_1001_PA1_J3_pin1_frequency
        , .min = 2.0
        , .max = 10000.0
        , .unit = "Hz"
        },
    [8] =
        { .name = "LED_2_DS10_dutyCycle"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_LED_2_DS10_dutyCycle
        , .setter = set_PWM_1001_LED_2_DS10_dutyCycle
        , .min = 0.0
        , .max = 0.0
        , .unit = "%"
        },
    [9] =
        { .name = "LED_4_DS11_dutyCycle"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_LED_4_DS11_dutyCycle
        , .setter = set_PWM_1001_LED_4_DS11_dutyCycle
        , .min = 0.0
        , .max = 0.0
        , .unit = "%"
        },
    [10] =
        { .name = "LED_5_DS5_dutyCycle"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_LED_5_DS5_dutyCycle
        , .setter = set_PWM_1001_LED_5_DS5_dutyCycle
        , .min = 0.0
        , .max = 0.0
        , .unit = "%"
        },
    [11] =
        { .name = "PA1_J3_pin1_dutyCycle"
        , .idxFrame = 0
        , .isReceived = true
        , .getter = get_PWM_1001_PA1_J3_pin1_dutyCycle
        , .setter = set_PWM_1001_PA1_J3_pin1_dutyCycle
        , .min = 0.0
        , .max = 0.0
        , .unit = "%"
        },
    [12] =
        { .name = "checksum"
        , .idxFrame = 1
        , .isReceived = true
        , .getter = get_PT_1024_checksum
        , .setter = set_PT_1024_checksum
        , .min = 0.0
        , .max = 255.0
        , .unit = ""
        },
    [13] =
        { .name = "speedOfRotation"
        , .idxFrame = 1
        , .isReceived = true
        , .getter = get_PT_1024_speedOfRotation
        , .setter = set_PT_1024_speedOfRotation
        , .min = 0.0
        , .max = 6500.0
        , .unit = "rpm"
        },
    [14] =
        { .name = "sequenceCounter"
        , .idxFrame = 1
        , .isReceived = true
        , .getter = get_PT_1024_sequenceCounter
        , .setter = set_PT_1024_sequenceCounter
        , .min = 0.0
        , .max = 14.0
        , .unit = ""
        },
    [15] =
        { .name = "sequenceCounter"
        , .idxFrame = 2
        , .isReceived = true
        , .getter = get_PT_1040_sequenceCounter
        , .setter = set_PT_1040_sequenceCounter
        , .min = 1.0
        , .max = 15.0
        , .unit = ""
        },
    [16] =
        { .name = "torque"
        , .idxFrame = 2
        , .isReceived = true
        , .getter = get_PT_1040_torque
        , .setter = set_PT_1040_torque
        , .min = -500.0
        , .max = 500.0
        , .unit = "Nm"
        },
    [17] =
        { .name = "sequenceCounter"
        , .idxFrame = 3
        , .isReceived = true
        , .getter = get_PT_2032_sequenceCounter
        , .setter = set_PT_2032_sequenceCounter
        , .min = 1.0
        , .max = 14.0
        , .unit = ""
        },
    [18] =
        { .name = "minSpeedOfRotation"
        , .idxFrame = 3
        , .isReceived = true
        , .getter = get_PT_2032_minSpeedOfRotation
        , .setter = set_PT_2032_minSpeedOfRotation
        , .min = 0.0
        , .max = 6500.0
        , .unit = "rpm"
        },
    [19] =
        { .name = "maxSpeedOfRotation"
        , .idxFrame = 3
        , .isReceived = true
        , .getter = get_PT_2032_maxSpeedOfRotation
        , .setter = set_PT_2032_maxSpeedOfRotation
        , .min = 0.0
        , .max = 6500.0
        , .unit = "rpm"
        },
    [20] =
        { .name = "checksum"
        , .idxFrame = 3
        , .isReceived = true
        , .getter = get_PT_2032_checksum
        , .setter = set_PT_2032_checksum
        , .min = 0.0
        , .max = 255.0
        , .unit = ""
        },
    [21] =
        { .name = "minPower"
        , .idxFrame = 3
        , .isReceived = true
        , .getter = get_PT_2032_minPower
        , .setter = set_PT_2032_minPower
        , .min = -10.0
        , .max = 240.0
        , .unit = "KW"
        },
    [22] =
        { .name = "maxPower"
        , .idxFrame = 3
        , .isReceived = true
        , .getter = get_PT_2032_maxPower
        , .setter = set_PT_2032_maxPower
        , .min = -10.0
        , .max = 240.0
        , .unit = "KW"
        },

    [23] =
        { .name = "PA2_J3_pin3_periodTime"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PWM_1000_PA2_J3_pin3_periodTime
        , .setter = set_PWM_1000_PA2_J3_pin3_periodTime
        , .min = 0.0
        , .max = 511.98437551
        , .unit = "ms"
        },
    [24] =
        { .name = "PA2_J3_pin3_isNew"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PWM_1000_PA2_J3_pin3_isNew
        , .setter = set_PWM_1000_PA2_J3_pin3_isNew
        , .min = 0.0
        , .max = 0.0
        , .unit = ""
        },
    [25] =
        { .name = "PA6_J2_pin1_isNew"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PWM_1000_PA6_J2_pin1_isNew
        , .setter = set_PWM_1000_PA6_J2_pin1_isNew
        , .min = 0.0
        , .max = 0.0
        , .unit = ""
        },
    [26] =
        { .name = "PA6_J2_pin1_dutyTime"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PWM_1000_PA6_J2_pin1_dutyTime
        , .setter = set_PWM_1000_PA6_J2_pin1_dutyTime
        , .min = 0.0
        , .max = 511.984375
        , .unit = "ms"
        },
    [27] =
        { .name = "PA2_PA6_dutyCycle"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PWM_1000_PA2_PA6_dutyCycle
        , .setter = set_PWM_1000_PA2_PA6_dutyCycle
        , .min = 0.0
        , .max = 100.0
        , .unit = "%"
        },
    [28] =
        { .name = "PA2_J3_pin3_frequency"
        , .idxFrame = 0
        , .isReceived = false
        , .getter = get_PWM_1000_PA2_J3_pin3_frequency
        , .setter = set_PWM_1000_PA2_J3_pin3_frequency
        , .min = 0.0
        , .max = 8191.75
        , .unit = "Hz"
        },
    [29] =
        { .name = "checksum"
        , .idxFrame = 1
        , .isReceived = false
        , .getter = get_PT_1536_checksum
        , .setter = set_PT_1536_checksum
        , .min = 0.0
        , .max = 255.0
        , .unit = ""
        },
    [30] =
        { .name = "sequenceCounter"
        , .idxFrame = 1
        , .isReceived = false
        , .getter = get_PT_1536_sequenceCounter
        , .setter = set_PT_1536_sequenceCounter
        , .min = 0.0
        , .max = 14.0
        , .unit = ""
        },
    [31] =
        { .name = "power"
        , .idxFrame = 1
        , .isReceived = false
        , .getter = get_PT_1536_power
        , .setter = set_PT_1536_power
        , .min = -500000.0
        , .max = 500000.0
        , .unit = "W"
        },
    [32] =
        { .name = "state"
        , .idxFrame = 1
        , .isReceived = false
        , .getter = get_PT_1536_state
        , .setter = set_PT_1536_state
        , .min = 0.0
        , .max = 2.0
        , .unit = ""
        },
    [33] =
        { .name = "noDlcErrors"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1537_noDlcErrors
        , .setter = set_PT_1537_noDlcErrors
        , .min = 0.0
        , .max = 2047.0
        , .unit = ""
        },
    [34] =
        { .name = "noCheckSumErrors"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1537_noCheckSumErrors
        , .setter = set_PT_1537_noCheckSumErrors
        , .min = 0.0
        , .max = 2047.0
        , .unit = ""
        },
    [35] =
        { .name = "noSqcErrors"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1537_noSqcErrors
        , .setter = set_PT_1537_noSqcErrors
        , .min = 0.0
        , .max = 2047.0
        , .unit = ""
        },
    [36] =
        { .name = "sequenceCounter"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1537_sequenceCounter
        , .setter = set_PT_1537_sequenceCounter
        , .min = 1.0
        , .max = 126.0
        , .unit = ""
        },
    [37] =
        { .name = "checksum"
        , .idxFrame = 2
        , .isReceived = false
        , .getter = get_PT_1537_checksum
        , .setter = set_PT_1537_checksum
        , .min = 0.0
        , .max = 255.0
        , .unit = ""
        },
    [38] =
        { .name = "sequenceCounter"
        , .idxFrame = 3
        , .isReceived = false
        , .getter = get_PT_1538_sequenceCounter
        , .setter = set_PT_1538_sequenceCounter
        , .min = 1.0
        , .max = 6.0
        , .unit = ""
        },
    [39] =
        { .name = "belowMinSpeedOfRotation"
        , .idxFrame = 3
        , .isReceived = false
        , .getter = get_PT_1538_belowMinSpeedOfRotation
        , .setter = set_PT_1538_belowMinSpeedOfRotation
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [40] =
        { .name = "aboveMaxSpeedOfRotation"
        , .idxFrame = 3
        , .isReceived = false
        , .getter = get_PT_1538_aboveMaxSpeedOfRotation
        , .setter = set_PT_1538_aboveMaxSpeedOfRotation
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [41] =
        { .name = "belowMinPower"
        , .idxFrame = 3
        , .isReceived = false
        , .getter = get_PT_1538_belowMinPower
        , .setter = set_PT_1538_belowMinPower
        , .min = 0.0
        , .max = 1.0
        , .unit = ""
        },
    [42] =
        { .name = "aboveMaxPower"
        , .idxFrame = 3
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


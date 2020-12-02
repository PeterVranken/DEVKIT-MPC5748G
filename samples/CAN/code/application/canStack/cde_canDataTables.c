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
        , .canId = 215
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_INS_Vel_Body_Axes
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_INS_Vel_Body_Axes
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_INS_Vel_Body_Axes_215().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [1] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8392740
        , .isReceived = true
        , .size = 7
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Speed
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Speed
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 1
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Speed_8392740().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [2] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9175332
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_GPS_Time
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_GPS_Time
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 2
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_GPS_Time_9175332().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [3] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9175844
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_GPS_Pos_LLH_2
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_GPS_Pos_LLH_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 3
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [4] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9175588
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_GPS_Pos_LLH_1
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_GPS_Pos_LLH_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 4
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [5] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1234
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_GPS_Speed
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_GPS_Speed
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 5
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_GPS_Speed_1234().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [6] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9962021
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IRTemp_Temp_FL_2
        , .fctPackApiFrame = cap_packApi_PT_RT_IRTemp_Temp_FL_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 6
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IRTemp_Temp_FL_2_9962021().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [7] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9962789
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IRTemp_Temp_RL_1
        , .fctPackApiFrame = cap_packApi_PT_RT_IRTemp_Temp_RL_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 7
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IRTemp_Temp_RL_1_9962789().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [8] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9962277
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IRTemp_Temp_FR_1
        , .fctPackApiFrame = cap_packApi_PT_RT_IRTemp_Temp_FR_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 8
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IRTemp_Temp_FR_1_9962277().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [9] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9961765
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IRTemp_Temp_FL_1
        , .fctPackApiFrame = cap_packApi_PT_RT_IRTemp_Temp_FL_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 9
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IRTemp_Temp_FL_1_9961765().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [10] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9503013
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IRTemp_Temp_1
        , .fctPackApiFrame = cap_packApi_PT_RT_IRTemp_Temp_1
        , .sendMode = cap_enumSendMode_mixed
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IRTemp_Temp_1_9503013().infoTransmission
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [11] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9242402
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Trig_Final_Condition
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Trig_Final_Condition
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 10
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Trig_Final_Condition_9242402().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [12] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 794
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Trig_Initial_Condition
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Trig_Initial_Condition
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 11
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Trig_Initial_Condition_794().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [13] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9241890
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Trig_Direct_Dist
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Trig_Direct_Dist
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 12
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Trig_Direct_Dist_9241890().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [14] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9241378
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Trig_Path_Dist
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Trig_Path_Dist
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 13
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Trig_Path_Dist_9241378().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [15] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9833252
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_11
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_11
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 14
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_11_9833252().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [16] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9832996
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_10
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_10
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 15
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_10_9832996().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [17] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9832740
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_9
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_9
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 16
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_9_9832740().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [18] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9832484
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_8
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_8
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 17
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_8_9832484().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [19] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9832228
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_7
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_7
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 18
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_7_9832228().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [20] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9831972
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_6
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_6
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 19
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_6_9831972().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [21] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9831716
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_5
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_5
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 20
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_5_9831716().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [22] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9831460
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_4
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_4
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 21
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_4_9831460().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [23] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9831204
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_3
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_3
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 22
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_3_9831204().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [24] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9830948
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_2
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 23
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_2_9830948().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [25] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9830692
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Measure_Time_1
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Measure_Time_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 24
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_1_9830692().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [26] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9767972
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_RPM
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_RPM
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 25
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_RPM_9767972().infoTransmission
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [27] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9767716
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Freq_4
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Freq_4
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 26
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Freq_4_9767716().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [28] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9896740
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Misc_3
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Misc_3
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 27
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Misc_3_9896740().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [29] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9896484
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Misc_2
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Misc_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 28
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Misc_2_9896484().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [30] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9896228
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Misc_1
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Misc_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 29
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Misc_1_9896228().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [31] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9699876
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Aux_2
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Aux_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 30
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Aux_2_9699876().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [32] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9699620
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Aux_1
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Aux_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 31
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Aux_1_9699620().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [33] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9438500
        , .isReceived = true
        , .size = 3
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Pressure_5
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Pressure_5
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 32
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Pressure_5_9438500().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [34] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9569060
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Angle_3
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Angle_3
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 33
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Angle_3_9569060().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [35] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9503012
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Temp_1
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Temp_1
        , .sendMode = cap_enumSendMode_event
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Temp_1_9503012().infoTransmission
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [36] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8520228
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Analog_3
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Analog_3
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 34
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Analog_3_8520228().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [37] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8519972
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Analog_2
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Analog_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 35
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Analog_2_8519972().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [38] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8519716
        , .isReceived = true
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Analog_1
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Analog_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 36
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Analog_1_8519716().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [39] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8388644
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_DL1MK3_Accel
        , .fctPackApiFrame = cap_packApi_PT_RT_DL1MK3_Accel
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 37
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_DL1MK3_Accel_8388644().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [40] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9306146
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_INS_Status
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_INS_Status
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 38
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_INS_Status_9306146().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [41] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9306402
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_INS_Attitude
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_INS_Attitude
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 39
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_INS_Attitude_9306402().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [42] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9240866
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Output_Status
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Output_Status
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 40
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Output_Status_9240866().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [43] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9180706
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Heading_Gradient_2
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Heading_Gradient_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 41
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Heading_Gradient_2_9180706().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [44] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8397090
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Cumulative_Distance_2
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Cumulative_Distance_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 42
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Cumulative_Distance_2_8397090().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [45] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8396834
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Cumulative_Distance_1
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Cumulative_Distance_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 43
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Cumulative_Distance_1_8396834().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [46] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9240610
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Trigger_Timestamp
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Trigger_Timestamp
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 44
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Trigger_Timestamp_9240610().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [47] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8388897
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IMU06_Gyro_Rates
        , .fctPackApiFrame = cap_packApi_PT_RT_IMU06_Gyro_Rates
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 45
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IMU06_Gyro_Rates_8388897().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [48] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8388641
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IMU06_Accel
        , .fctPackApiFrame = cap_packApi_PT_RT_IMU06_Accel
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 46
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IMU06_Accel_8388641().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [49] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8392738
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Speed
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Speed
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 47
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Speed_8392738().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [50] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9183522
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_RTK_Slip
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_RTK_Slip
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 48
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_RTK_Slip_9183522().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [51] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9183266
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_RTK_Attitude
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_RTK_Attitude
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 49
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_RTK_Attitude_9183266().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [52] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9187362
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Mcycle_Lean
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Mcycle_Lean
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 50
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Mcycle_Lean_9187362().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [53] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9175074
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Status
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Status
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 51
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Status_9175074().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [54] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9176354
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Pos_ECEF_2
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Pos_ECEF_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 52
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Pos_ECEF_2_9176354().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [55] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9176098
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Pos_ECEF_1
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Pos_ECEF_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 53
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Pos_ECEF_1_9176098().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [56] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9175842
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Pos_LLH_2
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Pos_LLH_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 54
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Pos_LLH_2_9175842().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [57] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9175586
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Pos_LLH_1
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Pos_LLH_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 55
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Pos_LLH_1_9175586().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [58] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9180450
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Heading_Gradient
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Heading_Gradient
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 56
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Heading_Gradient_9180450().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [59] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9180194
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Vel_ECEF_2
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Vel_ECEF_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 57
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Vel_ECEF_2_9180194().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [60] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9179938
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Vel_ECEF_1
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Vel_ECEF_1
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 58
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Vel_ECEF_1_9179938().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [61] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 0
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Vel_NED_2
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Vel_NED_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 59
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Vel_NED_2_0().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [62] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 1818
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Speed
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Speed
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 60
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Speed_1818().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [63] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 2047
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_GPS_Time
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_GPS_Time
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 61
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_GPS_Time_2047().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [64] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = false
        , .canId = 290
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Accel
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Accel
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 62
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Accel_290().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [65] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 8388898
        , .isReceived = true
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Gyro_Rates
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Gyro_Rates
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 63
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Gyro_Rates_8388898().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
}; /* cde_canRxFrameAry */

/** A global table with the description of all CAN frames which are sent by the device.
    The description of the frames is as detailed as required for implementation of their
    send/receive behavior in the callbacks of the event dispatchers. */
const cde_canFrame_t cde_canTxFrameAry[CDE_NO_CAN_FRAMES_SENT] =
{
    [0] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9963045
        , .isReceived = false
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IRTemp_Temp_RL_2
        , .fctPackApiFrame = cap_packApi_PT_RT_IRTemp_Temp_RL_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 0
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IRTemp_Temp_RL_2_9963045().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [1] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9962533
        , .isReceived = false
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IRTemp_Temp_FR_2
        , .fctPackApiFrame = cap_packApi_PT_RT_IRTemp_Temp_FR_2
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 1
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IRTemp_Temp_FR_2_9962533().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [2] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9510437
        , .isReceived = false
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IRTemp_Temp_30
        , .fctPackApiFrame = cap_packApi_PT_RT_IRTemp_Temp_30
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 2
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IRTemp_Temp_30_9510437().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [3] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9509413
        , .isReceived = false
        , .size = 2
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_IRTemp_Temp_26
        , .fctPackApiFrame = cap_packApi_PT_RT_IRTemp_Temp_26
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 3
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_IRTemp_Temp_26_9509413().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [4] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9241634
        , .isReceived = false
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Trig_Forward_Dist
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Trig_Forward_Dist
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 4
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Trig_Forward_Dist_9241634().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [5] =
        { .idxCanBus = OSE_CAN_BUS_PT
        , .isExtId = true
        , .canId = 9241122
        , .isReceived = false
        , .size = 8
        , .fctUnpackApiFrame = cap_unpackApi_PT_RT_SB_Trig_Accel
        , .fctPackApiFrame = cap_packApi_PT_RT_SB_Trig_Accel
        , .sendMode = cap_enumSendMode_regular
        , .idxHandlerCtxData = 5
        , .pInfoTransmission = &cap_getFrameSts_PT_RT_SB_Trig_Accel_9241122().infoTransmission
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
}; /* cde_canTxFrameAry */

#if (64) != CDE_NO_CAN_FRAMES_RECEIVED_REGULAR \
    ||  (1) != CDE_NO_CAN_FRAMES_RECEIVED_EVENT \
    ||  (1) != CDE_NO_CAN_FRAMES_RECEIVED_MIXED \
    ||  (6) != CDE_NO_CAN_FRAMES_SENT_REGULAR \
    ||  (0) != CDE_NO_CAN_FRAMES_SENT_EVENT \
    ||  (0) != CDE_NO_CAN_FRAMES_SENT_MIXED
# error Invalid index ranges detected. Looks like an inconsistency in your code generation templates
#endif



/*
 * Function implementation
 */


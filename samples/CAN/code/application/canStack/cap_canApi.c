/**
 * @file cap_canApi.c
 * 
 * This file implements the data oriented CAN API between the APSW code and the upper
 * layers of the CAN stack. The global data structure is initialized with the initial
 * signal values from the CAN network database.\n
 *   The integration of the API with the CAN stack is supported by a set of pack and unpack
 * functions; one such pair of functions is available for each CAN frame. The pack function
 * composes the binary frame contents from the set of signal values found in the API and
 * the counterpart function (unpack) decomposes received binary frame content data into
 * distinct signal values, which are placed into the API.\n
 *   The functions are globally accessible; their names are composed such that name clashes
 * across different buses won't appear even if frames of same name and ID are
 * transmitted.\n
 *   Note, concurrency is not handled here. Particularly for CAN input, data reception and
 * decomposition of the frame contents into signals might be an asynchronous event. If so,
 * the caller of the unpack function would have to add appropriate code to implement mutual
 * exclusion with the Embedded Coder generated APSW code, which also accesses the API data.
 * Although less likely may the same hold for CAN output.
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

#include <string.h>
#include <assert.h>

#include "typ_types.h"
#include "cap_canApi.h"


/*
 * Defines
 */

/* Check the values of the frame and special signal related #define's. Compilation errors
   can occur due to incompatibilites between the code generation templates and the actual
   network databases. */
#define CAP_INCLUDES_PRECO_CHECKS
#include "cap_precoCheck.h"


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** Signals and transmission status of the CAN frames on bus PT. This global
    variable is used as API between the platform's CAN interface and the APSW. */
cap_canBus_PT_t cap_canBus_PT =
{
    /** Signals and transmission status of inbound CAN frame RT_SB_INS_Vel_Body_Axes
        (215, 0x0d7) on bus PT. */
    .PT_RT_SB_INS_Vel_Body_Axes_215_sts =
    {
        .signals =
        {
            .Validity_INS_Vel_Forwards = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_INS_Vel_Sideways = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Bit4 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Bit7 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Byte2_Bit0 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .INS_Vel_Sideways_2D = CAP_PT_215_INS_VEL_SIDEWAYS_2D_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Byte4_Bits67 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_INS_Vel_Body_org_m1 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .INS_Vel_Forwards_2D_org_m1 = CAP_PT_215_INS_VEL_FORWARDS_2D_ORG_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accuracy_INS_Vel_Body_no2_m2 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .INS_Vel_Forwards_2D_no2_m2 = CAP_PT_215_INS_VEL_FORWARDS_2D_NO2_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accuracy_INS_Vel_Body_no3_m3 = CAP_PT_215_ACCURACY_INS_VEL_BODY_NO3_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .INS_Vel_Forwards_2D_no3_m3 = CAP_PT_215_INS_VEL_FORWARDS_2D_NO3_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Speed
        (8392740, 0x801024) on bus PT. */
    .PT_RT_DL1MK3_Speed_8392740_sts =
    {
        .signals =
        {
            .Validity_Speed = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_Speed = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Direction = CAP_PT_8392740_DIRECTION_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Speed = CAP_PT_8392740_SPEED_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Time
        (9175332, 0x8c0124) on bus PT. */
    .PT_RT_DL1MK3_GPS_Time_9175332_sts =
    {
        .signals =
        {
            .Validity_GPS_Time = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Week = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Time = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Time = CAP_PT_9175332_GPS_TIME_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .GPS_Week = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Pos_LLH_2
        (9175844, 0x8c0324) on bus PT. */
    .PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts =
    {
        .signals =
        {
            .GPS_Pos_LLH_Longitude = CAP_PT_9175844_GPS_POS_LLH_LONGITUDE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .GPS_Pos_LLH_Altitude = CAP_PT_9175844_GPS_POS_LLH_ALTITUDE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Pos_LLH_1
        (9175588, 0x8c0224) on bus PT. */
    .PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts =
    {
        .signals =
        {
            .Validity_GPS_Pos_LLH_Latitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Pos_LLH_Longitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Pos_LLH_Altitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Pos_LLH_Latitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Pos_LLH_Longitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Pos_LLH_Altitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Pos_LLH_Latitude = CAP_PT_9175588_GPS_POS_LLH_LATITUDE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Speed
        (1234, 0x4d2) on bus PT. */
    .PT_RT_DL1MK3_GPS_Speed_1234_sts =
    {
        .signals =
        {
            .Validity_GPS_Speed_2D = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Speed_3D = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Speed = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Speed_2D = CAP_PT_1234_GPS_SPEED_2D_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .GPS_Speed_3D = CAP_PT_1234_GPS_SPEED_3D_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_RL_2
        (9963045, 0x980625) on bus PT. */
    .PT_RT_IRTemp_Temp_RL_2_9963045_sts =
    {
        .signals =
        {
            .IR_Temperature_21 = CAP_PT_9963045_IR_TEMPERATURE_21_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_22 = CAP_PT_9963045_IR_TEMPERATURE_22_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_23 = CAP_PT_9963045_IR_TEMPERATURE_23_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_24 = CAP_PT_9963045_IR_TEMPERATURE_24_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_FR_2
        (9962533, 0x980425) on bus PT. */
    .PT_RT_IRTemp_Temp_FR_2_9962533_sts =
    {
        .signals =
        {
            .IR_Temperature_13 = CAP_PT_9962533_IR_TEMPERATURE_13_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_14 = CAP_PT_9962533_IR_TEMPERATURE_14_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_15 = CAP_PT_9962533_IR_TEMPERATURE_15_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_16 = CAP_PT_9962533_IR_TEMPERATURE_16_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_FL_2
        (9962021, 0x980225) on bus PT. */
    .PT_RT_IRTemp_Temp_FL_2_9962021_sts =
    {
        .signals =
        {
            .IR_Temperature_5 = CAP_PT_9962021_IR_TEMPERATURE_5_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_6 = CAP_PT_9962021_IR_TEMPERATURE_6_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_7 = CAP_PT_9962021_IR_TEMPERATURE_7_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_8 = CAP_PT_9962021_IR_TEMPERATURE_8_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_RL_1
        (9962789, 0x980525) on bus PT. */
    .PT_RT_IRTemp_Temp_RL_1_9962789_sts =
    {
        .signals =
        {
            .IR_Temperature_17 = CAP_PT_9962789_IR_TEMPERATURE_17_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_18 = CAP_PT_9962789_IR_TEMPERATURE_18_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_19 = CAP_PT_9962789_IR_TEMPERATURE_19_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_20 = CAP_PT_9962789_IR_TEMPERATURE_20_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_FR_1
        (9962277, 0x980325) on bus PT. */
    .PT_RT_IRTemp_Temp_FR_1_9962277_sts =
    {
        .signals =
        {
            .IR_Temperature_9 = CAP_PT_9962277_IR_TEMPERATURE_9_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_10 = CAP_PT_9962277_IR_TEMPERATURE_10_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_11 = CAP_PT_9962277_IR_TEMPERATURE_11_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_12 = CAP_PT_9962277_IR_TEMPERATURE_12_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_FL_1
        (9961765, 0x980125) on bus PT. */
    .PT_RT_IRTemp_Temp_FL_1_9961765_sts =
    {
        .signals =
        {
            .IR_Temperature_1 = CAP_PT_9961765_IR_TEMPERATURE_1_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_2 = CAP_PT_9961765_IR_TEMPERATURE_2_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_3 = CAP_PT_9961765_IR_TEMPERATURE_3_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .IR_Temperature_4 = CAP_PT_9961765_IR_TEMPERATURE_4_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_30
        (9510437, 0x911e25) on bus PT. */
    .PT_RT_IRTemp_Temp_30_9510437_sts =
    {
        .signals =
        {
            .IR_Temperature_30 = CAP_PT_9510437_IR_TEMPERATURE_30_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_26
        (9509413, 0x911a25) on bus PT. */
    .PT_RT_IRTemp_Temp_26_9509413_sts =
    {
        .signals =
        {
            .IR_Temperature_26 = CAP_PT_9509413_IR_TEMPERATURE_26_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_1
        (9503013, 0x910125) on bus PT. */
    .PT_RT_IRTemp_Temp_1_9503013_sts =
    {
        .signals =
        {
            .IR_Temperature_1 = CAP_PT_9503013_IR_TEMPERATURE_1_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .CRC = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Trig_Final_Condition
        (9242402, 0x8d0722) on bus PT. */
    .PT_RT_SB_Trig_Final_Condition_9242402_sts =
    {
        .signals =
        {
            .Validity_Final_Speed = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Final_Speed = CAP_PT_9242402_FINAL_SPEED_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Trig_Initial_Condition
        (794, 0x31a) on bus PT. */
    .PT_RT_SB_Trig_Initial_Condition_794_sts =
    {
        .signals =
        {
            .Validity_Initial_Speed = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Initial_Heading = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Initial_Speed = CAP_PT_794_INITIAL_SPEED_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Initial_Heading = CAP_PT_794_INITIAL_HEADING_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .MFDD_Start_Threshold = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .MFDD_End_Threshold = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Trig_Direct_Dist
        (9241890, 0x8d0522) on bus PT. */
    .PT_RT_SB_Trig_Direct_Dist_9241890_sts =
    {
        .signals =
        {
            .Direct_Distance = CAP_PT_9241890_DIRECT_DISTANCE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Path_Distance_2D = CAP_PT_9241890_PATH_DISTANCE_2D_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of outbound CAN frame RT_SB_Trig_Forward_Dist
        (9241634, 0x8d0422) on bus PT. */
    .PT_RT_SB_Trig_Forward_Dist_9241634_sts =
    {
        .signals =
        {
            .Forward_Distance = CAP_PT_9241634_FORWARD_DISTANCE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Deviation_Distance = CAP_PT_9241634_DEVIATION_DISTANCE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Trig_Path_Dist
        (9241378, 0x8d0322) on bus PT. */
    .PT_RT_SB_Trig_Path_Dist_9241378_sts =
    {
        .signals =
        {
            .Path_Distance_3D = CAP_PT_9241378_PATH_DISTANCE_3D_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of outbound CAN frame RT_SB_Trig_Accel
        (9241122, 0x8d0222) on bus PT. */
    .PT_RT_SB_Trig_Accel_9241122_sts =
    {
        .signals =
        {
            .Validity_MFDD = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Average_Accel = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Triggered_Time = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .MFDD = CAP_PT_9241122_MFDD_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Average_Accel = CAP_PT_9241122_AVERAGE_ACCEL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Triggered_Time = CAP_PT_9241122_TRIGGERED_TIME_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_okay,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_11
        (9833252, 0x960b24) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_11_9833252_sts =
    {
        .signals =
        {
            .Measured_Time_11 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_10
        (9832996, 0x960a24) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_10_9832996_sts =
    {
        .signals =
        {
            .Measured_Time_10 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_9
        (9832740, 0x960924) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_9_9832740_sts =
    {
        .signals =
        {
            .Measured_Time_9 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_8
        (9832484, 0x960824) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_8_9832484_sts =
    {
        .signals =
        {
            .Measured_Time_8 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_7
        (9832228, 0x960724) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_7_9832228_sts =
    {
        .signals =
        {
            .Measured_Time_7 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_6
        (9831972, 0x960624) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_6_9831972_sts =
    {
        .signals =
        {
            .Measured_Time_6 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_5
        (9831716, 0x960524) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_5_9831716_sts =
    {
        .signals =
        {
            .Measured_Time_5 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_4
        (9831460, 0x960424) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_4_9831460_sts =
    {
        .signals =
        {
            .Measured_Time_4 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_3
        (9831204, 0x960324) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_3_9831204_sts =
    {
        .signals =
        {
            .Measured_Time_3 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_2
        (9830948, 0x960224) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_2_9830948_sts =
    {
        .signals =
        {
            .Measured_Time_2 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_1
        (9830692, 0x960124) on bus PT. */
    .PT_RT_DL1MK3_Measure_Time_1_9830692_sts =
    {
        .signals =
        {
            .Measured_Time_1 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_RPM
        (9767972, 0x950c24) on bus PT. */
    .PT_RT_DL1MK3_RPM_9767972_sts =
    {
        .signals =
        {
            .RPM = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Freq_4
        (9767716, 0x950b24) on bus PT. */
    .PT_RT_DL1MK3_Freq_4_9767716_sts =
    {
        .signals =
        {
            .Frequency_4 = CAP_PT_9767716_FREQUENCY_4_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Misc_3
        (9896740, 0x970324) on bus PT. */
    .PT_RT_DL1MK3_Misc_3_9896740_sts =
    {
        .signals =
        {
            .Misc_3 = CAP_PT_9896740_MISC_3_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Misc_2
        (9896484, 0x970224) on bus PT. */
    .PT_RT_DL1MK3_Misc_2_9896484_sts =
    {
        .signals =
        {
            .Misc_2 = CAP_PT_9896484_MISC_2_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Misc_1
        (9896228, 0x970124) on bus PT. */
    .PT_RT_DL1MK3_Misc_1_9896228_sts =
    {
        .signals =
        {
            .Misc_1 = CAP_PT_9896228_MISC_1_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Aux_2
        (9699876, 0x940224) on bus PT. */
    .PT_RT_DL1MK3_Aux_2_9699876_sts =
    {
        .signals =
        {
            .AUX_2 = CAP_PT_9699876_AUX_2_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Aux_1
        (9699620, 0x940124) on bus PT. */
    .PT_RT_DL1MK3_Aux_1_9699620_sts =
    {
        .signals =
        {
            .AUX_1 = CAP_PT_9699620_AUX_1_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Pressure_5
        (9438500, 0x900524) on bus PT. */
    .PT_RT_DL1MK3_Pressure_5_9438500_sts =
    {
        .signals =
        {
            .Pressure_5 = CAP_PT_9438500_PRESSURE_5_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Angle_3
        (9569060, 0x920324) on bus PT. */
    .PT_RT_DL1MK3_Angle_3_9569060_sts =
    {
        .signals =
        {
            .Angle_3 = CAP_PT_9569060_ANGLE_3_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Temp_1
        (9503012, 0x910124) on bus PT. */
    .PT_RT_DL1MK3_Temp_1_9503012_sts =
    {
        .signals =
        {
            .Temperature_1 = CAP_PT_9503012_TEMPERATURE_1_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Analog_3
        (8520228, 0x820224) on bus PT. */
    .PT_RT_DL1MK3_Analog_3_8520228_sts =
    {
        .signals =
        {
            .Analog_3 = CAP_PT_8520228_ANALOG_3_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Analog_2
        (8519972, 0x820124) on bus PT. */
    .PT_RT_DL1MK3_Analog_2_8519972_sts =
    {
        .signals =
        {
            .Analog_2 = CAP_PT_8519972_ANALOG_2_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Analog_1
        (8519716, 0x820024) on bus PT. */
    .PT_RT_DL1MK3_Analog_1_8519716_sts =
    {
        .signals =
        {
            .Analog_1 = CAP_PT_8519716_ANALOG_1_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Accel
        (8388644, 0x800024) on bus PT. */
    .PT_RT_DL1MK3_Accel_8388644_sts =
    {
        .signals =
        {
            .Validity_Accel_Longitudinal = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Accel_Lateral = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Accel_Vertical = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .SQC = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_Accel = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accel_Longitudinal = CAP_PT_8388644_ACCEL_LONGITUDINAL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accel_Lateral = CAP_PT_8388644_ACCEL_LATERAL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accel_Vertical = CAP_PT_8388644_ACCEL_VERTICAL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_INS_Status
        (9306146, 0x8e0022) on bus PT. */
    .PT_RT_SB_INS_Status_9306146_sts =
    {
        .signals =
        {
            .INS_Status = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_INS_Attitude
        (9306402, 0x8e0122) on bus PT. */
    .PT_RT_SB_INS_Attitude_9306402_sts =
    {
        .signals =
        {
            .Validity_Yaw = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Pitch = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Roll = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_Attitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Attitude_Yaw = CAP_PT_9306402_ATTITUDE_YAW_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Attitude_Pitch = CAP_PT_9306402_ATTITUDE_PITCH_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Attitude_Roll = CAP_PT_9306402_ATTITUDE_ROLL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Output_Status
        (9240866, 0x8d0122) on bus PT. */
    .PT_RT_SB_Output_Status_9240866_sts =
    {
        .signals =
        {
            .Validity_Status_Timestamp = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Status_Analogue_1 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Status_Analogue_2 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Status_Analogue_3 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Status_Analogue_4 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Status_Pulse_Output = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Status_Serial_Output_1 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Status_Serial_Output_2 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Status_Trigger = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Time = CAP_PT_9240866_GPS_TIME_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Heading_Gradient_2
        (9180706, 0x8c1622) on bus PT. */
    .PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts =
    {
        .signals =
        {
            .Validity_GPS_Heading = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Gradient = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Heading = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Heading_2 = CAP_PT_9180706_GPS_HEADING_2_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accuracy_GPS_Gradient = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Gradient = CAP_PT_9180706_GPS_GRADIENT_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Cumulative_Distance_2
        (8397090, 0x802122) on bus PT. */
    .PT_RT_SB_Cumulative_Distance_2_8397090_sts =
    {
        .signals =
        {
            .Validity_Cumulative_Time = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Cumulative_Distance = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Cumulative_Time = CAP_PT_8397090_CUMULATIVE_TIME_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Cumulative_Distance = CAP_PT_8397090_CUMULATIVE_DISTANCE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Cumulative_Distance_1
        (8396834, 0x802022) on bus PT. */
    .PT_RT_SB_Cumulative_Distance_1_8396834_sts =
    {
        .signals =
        {
            .Validity_Cumulative_Time = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Cumulative_Distance = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Cumulative_Time = CAP_PT_8396834_CUMULATIVE_TIME_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Cumulative_Distance = CAP_PT_8396834_CUMULATIVE_DISTANCE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Trigger_Timestamp
        (9240610, 0x8d0022) on bus PT. */
    .PT_RT_SB_Trigger_Timestamp_9240610_sts =
    {
        .signals =
        {
            .Validity_Trigger_Timestamp = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_Trigger_Timestamp = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Trigger_Number = CAP_PT_9240610_TRIGGER_NUMBER_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Trigger_Timestamp_Type = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_High_Resolution_Time = CAP_PT_9240610_GPS_HIGH_RESOLUTION_TIME_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_IMU06_Gyro_Rates
        (8388897, 0x800121) on bus PT. */
    .PT_RT_IMU06_Gyro_Rates_8388897_sts =
    {
        .signals =
        {
            .Validity_Gyro_Rate_Yaw = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Gyro_Rate_Pitch = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Gyro_Rate_Roll = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_Gyro_Rates = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Gyro_Rate_Yaw = CAP_PT_8388897_GYRO_RATE_YAW_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Gyro_Rate_Pitch = CAP_PT_8388897_GYRO_RATE_PITCH_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Gyro_Rate_Roll = CAP_PT_8388897_GYRO_RATE_ROLL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_IMU06_Accel
        (8388641, 0x800021) on bus PT. */
    .PT_RT_IMU06_Accel_8388641_sts =
    {
        .signals =
        {
            .Validity_Accel_Longitudinal = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Accel_Lateral = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Accel_Vertical = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_Accel = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accel_Longitudinal = CAP_PT_8388641_ACCEL_LONGITUDINAL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accel_Lateral = CAP_PT_8388641_ACCEL_LATERAL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accel_Vertical = CAP_PT_8388641_ACCEL_VERTICAL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Speed
        (8392738, 0x801022) on bus PT. */
    .PT_RT_SB_Speed_8392738_sts =
    {
        .signals =
        {
            .Validity_Speed = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_Speed = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Speed = CAP_PT_8392738_SPEED_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_RTK_Slip
        (9183522, 0x8c2122) on bus PT. */
    .PT_RT_SB_RTK_Slip_9183522_sts =
    {
        .signals =
        {
            .Validity_RTK_Slip = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_RTK_Squat = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_RTK_Baseline = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_RTK_Baseline = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .RTK_Slip = CAP_PT_9183522_RTK_SLIP_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .RTK_Squat = CAP_PT_9183522_RTK_SQUAT_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .RTK_Baseline = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_RTK_Attitude
        (9183266, 0x8c2022) on bus PT. */
    .PT_RT_SB_RTK_Attitude_9183266_sts =
    {
        .signals =
        {
            .Validity_RTK_Yaw = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_RTK_Pitch = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_RTK_Roll = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_RTK_Attitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .RTK_Attitude_Yaw = CAP_PT_9183266_RTK_ATTITUDE_YAW_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .RTK_Attitude_Pitch = CAP_PT_9183266_RTK_ATTITUDE_PITCH_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .RTK_Attitude_Roll = CAP_PT_9183266_RTK_ATTITUDE_ROLL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Mcycle_Lean
        (9187362, 0x8c3022) on bus PT. */
    .PT_RT_SB_GPS_Mcycle_Lean_9187362_sts =
    {
        .signals =
        {
            .Validity_GPS_Lateral_Accel = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Mcycle_Lean = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Lateral_Accel = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Lateral_Accel = CAP_PT_9187362_GPS_LATERAL_ACCEL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .GPS_Mcycle_Lean_Angle = CAP_PT_9187362_GPS_MCYCLE_LEAN_ANGLE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Status
        (9175074, 0x8c0022) on bus PT. */
    .PT_RT_SB_GPS_Status_9175074_sts =
    {
        .signals =
        {
            .GPS_Status = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Firmware_Version_Major = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Firmware_Version_Intermediate = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Firmware_Version_Minor = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_nSv = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_nSv_2 = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_nSv_RTK = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .RTK_Status = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_ECEF_2
        (9176354, 0x8c0522) on bus PT. */
    .PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts =
    {
        .signals =
        {
            .GPS_Pos_ECEF_Y = CAP_PT_9176354_GPS_POS_ECEF_Y_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .GPS_Pos_ECEF_Z = CAP_PT_9176354_GPS_POS_ECEF_Z_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_ECEF_1
        (9176098, 0x8c0422) on bus PT. */
    .PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts =
    {
        .signals =
        {
            .Validity_GPS_Pos_ECEF_X = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Pos_ECEF_Y = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Pos_ECEF_Z = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Pos_ECEF_X = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Pos_ECEF_Y = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Pos_ECEF_Z = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Pos_ECEF_X = CAP_PT_9176098_GPS_POS_ECEF_X_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_LLH_2
        (9175842, 0x8c0322) on bus PT. */
    .PT_RT_SB_GPS_Pos_LLH_2_9175842_sts =
    {
        .signals =
        {
            .GPS_Pos_LLH_Longitude = CAP_PT_9175842_GPS_POS_LLH_LONGITUDE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .GPS_Pos_LLH_Altitude = CAP_PT_9175842_GPS_POS_LLH_ALTITUDE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_LLH_1
        (9175586, 0x8c0222) on bus PT. */
    .PT_RT_SB_GPS_Pos_LLH_1_9175586_sts =
    {
        .signals =
        {
            .Validity_GPS_Pos_LLH_Latitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Pos_LLH_Longitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Pos_LLH_Altitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Pos_LLH_Latitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Pos_LLH_Longitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Pos_LLH_Altitude = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Pos_LLH_Latitude = CAP_PT_9175586_GPS_POS_LLH_LATITUDE_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Heading_Gradient
        (9180450, 0x8c1522) on bus PT. */
    .PT_RT_SB_GPS_Heading_Gradient_9180450_sts =
    {
        .signals =
        {
            .Validity_GPS_Heading = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Gradient = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Heading = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Heading = CAP_PT_9180450_GPS_HEADING_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accuracy_GPS_Gradient = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Gradient = CAP_PT_9180450_GPS_GRADIENT_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Vel_ECEF_2
        (9180194, 0x8c1422) on bus PT. */
    .PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts =
    {
        .signals =
        {
            .Validity_GPS_Vel_ECEF_Y = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Vel_ECEF_Z = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Vel_ECEF_Y = CAP_PT_9180194_GPS_VEL_ECEF_Y_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .GPS_Vel_ECEF_Z = CAP_PT_9180194_GPS_VEL_ECEF_Z_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Vel_ECEF_1
        (9179938, 0x8c1322) on bus PT. */
    .PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts =
    {
        .signals =
        {
            .Validity_GPS_Vel_ECEF_X = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Vel_ECEF_X = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Vel_ECEF_Y = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Vel_ECEF_Z = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Vel_ECEF_X = CAP_PT_9179938_GPS_VEL_ECEF_X_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Vel_NED_2
        (0, 0x000) on bus PT. */
    .PT_RT_SB_GPS_Vel_NED_2_0_sts =
    {
        .signals =
        {
            .Validity_GPS_Vel_NED_D = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Vel_D = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Vel_NED_D = CAP_PT_0_GPS_VEL_NED_D_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Speed
        (1818, 0x71a) on bus PT. */
    .PT_RT_SB_GPS_Speed_1818_sts =
    {
        .signals =
        {
            .Validity_GPS_Speed_2D = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Speed_3D = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Speed = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Speed_2D = CAP_PT_1818_GPS_SPEED_2D_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .GPS_Speed_3D = CAP_PT_1818_GPS_SPEED_3D_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Time
        (2047, 0x7ff) on bus PT. */
    .PT_RT_SB_GPS_Time_2047_sts =
    {
        .signals =
        {
            .Validity_GPS_Time = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_GPS_Week = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_GPS_Time = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .GPS_Time = CAP_PT_2047_GPS_TIME_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .GPS_Week = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Accel
        (290, 0x122) on bus PT. */
    .PT_RT_SB_Accel_290_sts =
    {
        .signals =
        {
            .Validity_Accel_Longitudinal = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Accel_Lateral = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Accel_Vertical = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_Accel = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accel_Longitudinal = CAP_PT_290_ACCEL_LONGITUDINAL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accel_Lateral = CAP_PT_290_ACCEL_LATERAL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Accel_Vertical = CAP_PT_290_ACCEL_VERTICAL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },

    /** Signals and transmission status of inbound CAN frame RT_SB_Gyro_Rates
        (8388898, 0x800122) on bus PT. */
    .PT_RT_SB_Gyro_Rates_8388898_sts =
    {
        .signals =
        {
            .Validity_Gyro_Rate_Yaw = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Gyro_Rate_Pitch = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Validity_Gyro_Rate_Roll = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Accuracy_Gyro_Rates = 0 /* Initial value not found in database; check signal attribute "initialValue" */,
            .Gyro_Rate_Yaw = CAP_PT_8388898_GYRO_RATE_YAW_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Gyro_Rate_Pitch = CAP_PT_8388898_GYRO_RATE_PITCH_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
            .Gyro_Rate_Roll = CAP_PT_8388898_GYRO_RATE_ROLL_DBL_TO_BIN(0 /* Initial value not found in database; check signal attribute "initialValue" */),
        },

        .infoTransmission =
        {
            .stsTransmission = cap_stsTransm_neverReceived,
            .noTransmittedFrames = 0,
            .isEvent = false,
        },
    },


}; /* End of cap_canBus_PT_t cap_canBus_PT */




/*
 * Function implementation
 */

#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_INS_Vel_Body_Axes_215_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_INS_Vel_Body_Axes(uint8_t m[])
{
    cap_pack_PT_RT_SB_INS_Vel_Body_Axes
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_INS_Vel_Body_Axes_215()
            );
} /* End of cap_packApi_PT_RT_SB_INS_Vel_Body_Axes */




/**
 * Pack the signals of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_INS_Vel_Body_Axes.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_INS_Vel_Body_Axes
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_INS_Vel_Body_Axes_215_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Validity_INS_Vel_Forwards. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_INS_Vel_Forwards;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_INS_Vel_Sideways. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_INS_Vel_Sideways << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Bit4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Bit4 << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x10;
        m[0] |= (uint8_t)(s & 0x10);
    }

    /* Pack signal Bit7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Bit7 << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x80;
        m[0] |= (uint8_t)(s & 0x80);
    }

    /* Pack signal Byte2_Bit0. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Byte2_Bit0;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (uint8_t)~0x01;
        m[2] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal INS_Vel_Sideways_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->INS_Vel_Sideways_2D << (9-9);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] &= (uint8_t)~0x7f;
        m[7] |= (uint8_t)(s & 0x7f);
    }

    /* Pack signal Byte4_Bits67. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Byte4_Bits67 << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] &= (uint8_t)~0xc0;
        m[4] |= (uint8_t)(s & 0xc0);
    }

    /* Pack the selected set of multiplexed signals. */
    switch(pFrameStruct->Byte4_Bits67)
    {
    case 1:
        /* Pack signal Accuracy_INS_Vel_Body_org. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            uint8_t s = (uint8_t)pFrameStruct->Accuracy_INS_Vel_Body_org_m1;

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[1] = (uint8_t)s;
        }

        /* Pack signal INS_Vel_Forwards_2D_org. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            uint32_t s = (uint32_t)pFrameStruct->INS_Vel_Forwards_2D_org_m1 << (11-10);

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[2] &= (uint8_t)~0xfe;
            m[2] |= (uint8_t)(s & 0xfe);
            s >>= 8;
            m[3] = (uint8_t)s;
            s >>= 8;
            m[4] &= (uint8_t)~0x3f;
            m[4] |= (uint8_t)(s & 0x3f);
        }

        break;
    case 2:
        /* Pack signal Accuracy_INS_Vel_Body_no2. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            uint8_t s = (uint8_t)pFrameStruct->Accuracy_INS_Vel_Body_no2_m2;

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[1] = (uint8_t)s;
        }

        /* Pack signal INS_Vel_Forwards_2D_no2. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            uint32_t s = (uint32_t)pFrameStruct->INS_Vel_Forwards_2D_no2_m2 << (11-10);

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[2] &= (uint8_t)~0xfe;
            m[2] |= (uint8_t)(s & 0xfe);
            s >>= 8;
            m[3] = (uint8_t)s;
            s >>= 8;
            m[4] &= (uint8_t)~0x3f;
            m[4] |= (uint8_t)(s & 0x3f);
        }

        break;
    case 3:
        /* Pack signal Accuracy_INS_Vel_Body_no3. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            uint16_t s = (uint16_t)pFrameStruct->Accuracy_INS_Vel_Body_no3_m3 << 1;

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[2] &= (uint8_t)~0xfe;
            m[2] |= (uint8_t)(s & 0xfe);
            s >>= 8;
            m[1] = (uint8_t)s;
        }

        /* Pack signal INS_Vel_Forwards_2D_no3. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            uint16_t s = (uint16_t)pFrameStruct->INS_Vel_Forwards_2D_no3_m3 << (2-2);

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[3] = (uint8_t)s;
            s >>= 8;
            m[4] &= (uint8_t)~0x3f;
            m[4] |= (uint8_t)(s & 0x3f);
        }

        break;

    default: assert(1==0); // Undefined mux selector value encountered
    }
} /* End of cap_pack_PT_RT_SB_INS_Vel_Body_Axes */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_INS_Vel_Body_Axes_215_sts, which models frame RT_SB_INS_Vel_Body_Axes.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_INS_Vel_Body_Axes(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_INS_Vel_Body_Axes
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_INS_Vel_Body_Axes_215()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_INS_Vel_Body_Axes */



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_INS_Vel_Body_Axes.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_INS_Vel_Body_Axes
                    ( cap_PT_RT_SB_INS_Vel_Body_Axes_215_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_INS_Vel_Forwards =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_INS_Vel_Sideways =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Bit4 =
        (boolean_t)(((uint8_t)(m[0] & 0x10)) >> 4);
    pFrameStruct->Bit7 =
        (boolean_t)(((uint8_t)(m[0] & 0x80)) >> 7);
    pFrameStruct->Byte2_Bit0 =
        (boolean_t)((uint8_t)(m[2] & 0x01));
    pFrameStruct->INS_Vel_Sideways_2D =
        (int32_t)((int32_t)(((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 9) >> 9);

    /* Decode the multiplex selector signal. */
    pFrameStruct->Byte4_Bits67 =
        (uint8_t)(((uint8_t)(m[4] & 0xc0)) >> 6);

    /* Decode the selected set of multiplexed signals. */
    switch(pFrameStruct->Byte4_Bits67)
    {
    case 1:
        pFrameStruct->Accuracy_INS_Vel_Body_org_m1 =
            (uint8_t)((uint8_t)m[1]);
        pFrameStruct->INS_Vel_Forwards_2D_org_m1 =
            (int32_t)((int32_t)(((((((uint32_t)m[4]) << 8) | m[3]) << 8) | m[2]) << 10) >> 11);

        break;
    case 2:
        pFrameStruct->Accuracy_INS_Vel_Body_no2_m2 =
            (uint8_t)((uint8_t)m[1]);
        pFrameStruct->INS_Vel_Forwards_2D_no2_m2 =
            (int32_t)((int32_t)(((((((uint32_t)m[4]) << 8) | m[3]) << 8) | m[2]) << 10) >> 11);

        break;
    case 3:
        pFrameStruct->Accuracy_INS_Vel_Body_no3_m3 =
            (uint16_t)(((((uint16_t)m[1]) << 8) | m[2]) >> 1);
        pFrameStruct->INS_Vel_Forwards_2D_no3_m3 =
            (int16_t)((int16_t)(((((uint16_t)m[4]) << 8) | m[3]) << 2) >> 2);

        break;

    default: assert(1==0); // Undefined mux selector value encountered
    }
} /* End of cap_unpack_PT_RT_SB_INS_Vel_Body_Axes */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024) on bus PT
 * into a byte array of 7 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Speed_8392740_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Speed(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Speed
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Speed_8392740()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Speed */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024) on bus PT
 * into a byte array of 7 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Speed.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Speed
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Speed_8392740_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[2] = 0xff;
    m[6] = 0xff;

    /* Pack signal Validity_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Accuracy_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Direction. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Direction;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (uint8_t)~0x03;
        m[2] |= (uint8_t)(s & 0x03);
    }

    /* Pack signal Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint64_t s = (uint64_t)pFrameStruct->Speed << (32-30);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (uint8_t)~0xfc;
        m[2] |= (uint8_t)(s & 0xfc);
        s >>= 8;
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] &= (uint8_t)~0x03;
        m[6] |= (uint8_t)(s & 0x03);
    }
} /* End of cap_pack_PT_RT_DL1MK3_Speed */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024) on bus PT
 * from a byte array of 7 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Speed_8392740_sts, which models frame RT_DL1MK3_Speed.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Speed(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Speed
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Speed_8392740()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Speed */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024) on bus PT
 * from a byte array of 7 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Speed.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Speed
                    ( cap_PT_RT_DL1MK3_Speed_8392740_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Speed =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Accuracy_Speed =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Direction =
        (uint8_t)((uint8_t)(m[2] & 0x03));
    pFrameStruct->Speed =
        (int32_t)((int64_t)(((((((((((uint64_t)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) | m[3]) << 8) | m[2]) << 30) >> 32);

} /* End of cap_unpack_PT_RT_DL1MK3_Speed */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_GPS_Time_9175332_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_GPS_Time(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_GPS_Time
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_GPS_Time_9175332()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_GPS_Time */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_GPS_Time.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_GPS_Time
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_GPS_Time_9175332_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Week. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Week << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal GPS_Week. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->GPS_Week;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_GPS_Time */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_GPS_Time_9175332_sts, which models frame RT_DL1MK3_GPS_Time.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_GPS_Time(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_GPS_Time
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_GPS_Time_9175332()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_GPS_Time */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_GPS_Time.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_GPS_Time
                    ( cap_PT_RT_DL1MK3_GPS_Time_9175332_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Time =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Week =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Accuracy_GPS_Time =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->GPS_Time =
        (uint32_t)((((((((uint32_t)m[5]) << 8) | m[4]) << 8) | m[3]) << 8) | m[2]);
    pFrameStruct->GPS_Week =
        (uint16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_DL1MK3_GPS_Time */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_GPS_Pos_LLH_2(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_GPS_Pos_LLH_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_GPS_Pos_LLH_2 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_GPS_Pos_LLH_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_GPS_Pos_LLH_2
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_t *pFrameStruct
                    )
{

    /* Pack signal GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_GPS_Pos_LLH_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts, which models frame RT_DL1MK3_GPS_Pos_LLH_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_GPS_Pos_LLH_2(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_GPS_Pos_LLH_2 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_GPS_Pos_LLH_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_2
                    ( cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->GPS_Pos_LLH_Longitude =
        (int32_t)((((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    pFrameStruct->GPS_Pos_LLH_Altitude =
        (int32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_GPS_Pos_LLH_1(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_GPS_Pos_LLH_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_GPS_Pos_LLH_1 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_GPS_Pos_LLH_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_GPS_Pos_LLH_1
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Pos_LLH_Longitude << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Pos_LLH_Altitude << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_GPS_Pos_LLH_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts, which models frame RT_DL1MK3_GPS_Pos_LLH_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_GPS_Pos_LLH_1(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_GPS_Pos_LLH_1 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_GPS_Pos_LLH_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_1
                    ( cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Pos_LLH_Latitude =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Pos_LLH_Longitude =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_GPS_Pos_LLH_Altitude =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_GPS_Pos_LLH_Latitude =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Accuracy_GPS_Pos_LLH_Longitude =
        (uint8_t)((uint8_t)m[2]);
    pFrameStruct->Accuracy_GPS_Pos_LLH_Altitude =
        (uint8_t)((uint8_t)m[3]);
    pFrameStruct->GPS_Pos_LLH_Latitude =
        (int32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_GPS_Speed_1234_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_GPS_Speed(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_GPS_Speed
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_GPS_Speed_1234()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_GPS_Speed */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_GPS_Speed.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_GPS_Speed
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_GPS_Speed_1234_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Speed_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Speed_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Speed_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Speed_3D << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal GPS_Speed_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Speed_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] = (uint8_t)s;
    }

    /* Pack signal GPS_Speed_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Speed_3D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_GPS_Speed */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_GPS_Speed_1234_sts, which models frame RT_DL1MK3_GPS_Speed.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_GPS_Speed(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_GPS_Speed
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_GPS_Speed_1234()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_GPS_Speed */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_GPS_Speed.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_GPS_Speed
                    ( cap_PT_RT_DL1MK3_GPS_Speed_1234_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Speed_2D =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Speed_3D =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Accuracy_GPS_Speed =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->GPS_Speed_2D =
        (uint32_t)((((((uint32_t)m[4]) << 8) | m[3]) << 8) | m[2]);
    pFrameStruct->GPS_Speed_3D =
        (uint32_t)((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]);

} /* End of cap_unpack_PT_RT_DL1MK3_GPS_Speed */


/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_RL_2_9963045_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IRTemp_Temp_RL_2(uint8_t m[])
{
    cap_pack_PT_RT_IRTemp_Temp_RL_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_RL_2_9963045()
            );
} /* End of cap_packApi_PT_RT_IRTemp_Temp_RL_2 */




/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IRTemp_Temp_RL_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IRTemp_Temp_RL_2
                    ( uint8_t m[]
                    , const cap_PT_RT_IRTemp_Temp_RL_2_9963045_t *pFrameStruct
                    )
{

    /* Pack signal IR_Temperature_21. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_21;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_22. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_22;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_23. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_23;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_24. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_24;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IRTemp_Temp_RL_2 */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_RL_2_9963045_sts, which models frame RT_IRTemp_Temp_RL_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IRTemp_Temp_RL_2(const uint8_t m[])
{
    cap_unpack_PT_RT_IRTemp_Temp_RL_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_RL_2_9963045()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IRTemp_Temp_RL_2 */



/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IRTemp_Temp_RL_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IRTemp_Temp_RL_2
                    ( cap_PT_RT_IRTemp_Temp_RL_2_9963045_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->IR_Temperature_21 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);
    pFrameStruct->IR_Temperature_22 =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->IR_Temperature_23 =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->IR_Temperature_24 =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_IRTemp_Temp_RL_2 */
#endif



/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_FR_2_9962533_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IRTemp_Temp_FR_2(uint8_t m[])
{
    cap_pack_PT_RT_IRTemp_Temp_FR_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_FR_2_9962533()
            );
} /* End of cap_packApi_PT_RT_IRTemp_Temp_FR_2 */




/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IRTemp_Temp_FR_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IRTemp_Temp_FR_2
                    ( uint8_t m[]
                    , const cap_PT_RT_IRTemp_Temp_FR_2_9962533_t *pFrameStruct
                    )
{

    /* Pack signal IR_Temperature_13. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_13;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_14. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_14;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_15. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_15;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_16. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_16;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IRTemp_Temp_FR_2 */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_FR_2_9962533_sts, which models frame RT_IRTemp_Temp_FR_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IRTemp_Temp_FR_2(const uint8_t m[])
{
    cap_unpack_PT_RT_IRTemp_Temp_FR_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_FR_2_9962533()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IRTemp_Temp_FR_2 */



/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IRTemp_Temp_FR_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IRTemp_Temp_FR_2
                    ( cap_PT_RT_IRTemp_Temp_FR_2_9962533_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->IR_Temperature_13 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);
    pFrameStruct->IR_Temperature_14 =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->IR_Temperature_15 =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->IR_Temperature_16 =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_IRTemp_Temp_FR_2 */
#endif




#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_FL_2_9962021_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IRTemp_Temp_FL_2(uint8_t m[])
{
    cap_pack_PT_RT_IRTemp_Temp_FL_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_FL_2_9962021()
            );
} /* End of cap_packApi_PT_RT_IRTemp_Temp_FL_2 */




/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IRTemp_Temp_FL_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IRTemp_Temp_FL_2
                    ( uint8_t m[]
                    , const cap_PT_RT_IRTemp_Temp_FL_2_9962021_t *pFrameStruct
                    )
{

    /* Pack signal IR_Temperature_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_6. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_8. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_8;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IRTemp_Temp_FL_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_FL_2_9962021_sts, which models frame RT_IRTemp_Temp_FL_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IRTemp_Temp_FL_2(const uint8_t m[])
{
    cap_unpack_PT_RT_IRTemp_Temp_FL_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_FL_2_9962021()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IRTemp_Temp_FL_2 */



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IRTemp_Temp_FL_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IRTemp_Temp_FL_2
                    ( cap_PT_RT_IRTemp_Temp_FL_2_9962021_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->IR_Temperature_5 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);
    pFrameStruct->IR_Temperature_6 =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->IR_Temperature_7 =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->IR_Temperature_8 =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_IRTemp_Temp_FL_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_RL_1_9962789_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IRTemp_Temp_RL_1(uint8_t m[])
{
    cap_pack_PT_RT_IRTemp_Temp_RL_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_RL_1_9962789()
            );
} /* End of cap_packApi_PT_RT_IRTemp_Temp_RL_1 */




/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IRTemp_Temp_RL_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IRTemp_Temp_RL_1
                    ( uint8_t m[]
                    , const cap_PT_RT_IRTemp_Temp_RL_1_9962789_t *pFrameStruct
                    )
{

    /* Pack signal IR_Temperature_17. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_17;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_18. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_18;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_19. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_19;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_20. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_20;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IRTemp_Temp_RL_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_RL_1_9962789_sts, which models frame RT_IRTemp_Temp_RL_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IRTemp_Temp_RL_1(const uint8_t m[])
{
    cap_unpack_PT_RT_IRTemp_Temp_RL_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_RL_1_9962789()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IRTemp_Temp_RL_1 */



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IRTemp_Temp_RL_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IRTemp_Temp_RL_1
                    ( cap_PT_RT_IRTemp_Temp_RL_1_9962789_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->IR_Temperature_17 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);
    pFrameStruct->IR_Temperature_18 =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->IR_Temperature_19 =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->IR_Temperature_20 =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_IRTemp_Temp_RL_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_FR_1_9962277_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IRTemp_Temp_FR_1(uint8_t m[])
{
    cap_pack_PT_RT_IRTemp_Temp_FR_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_FR_1_9962277()
            );
} /* End of cap_packApi_PT_RT_IRTemp_Temp_FR_1 */




/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IRTemp_Temp_FR_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IRTemp_Temp_FR_1
                    ( uint8_t m[]
                    , const cap_PT_RT_IRTemp_Temp_FR_1_9962277_t *pFrameStruct
                    )
{

    /* Pack signal IR_Temperature_9. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_9;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_10. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_10;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_11. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_11;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_12. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_12;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IRTemp_Temp_FR_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_FR_1_9962277_sts, which models frame RT_IRTemp_Temp_FR_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IRTemp_Temp_FR_1(const uint8_t m[])
{
    cap_unpack_PT_RT_IRTemp_Temp_FR_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_FR_1_9962277()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IRTemp_Temp_FR_1 */



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IRTemp_Temp_FR_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IRTemp_Temp_FR_1
                    ( cap_PT_RT_IRTemp_Temp_FR_1_9962277_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->IR_Temperature_9 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);
    pFrameStruct->IR_Temperature_10 =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->IR_Temperature_11 =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->IR_Temperature_12 =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_IRTemp_Temp_FR_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_FL_1_9961765_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IRTemp_Temp_FL_1(uint8_t m[])
{
    cap_pack_PT_RT_IRTemp_Temp_FL_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_FL_1_9961765()
            );
} /* End of cap_packApi_PT_RT_IRTemp_Temp_FL_1 */




/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IRTemp_Temp_FL_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IRTemp_Temp_FL_1
                    ( uint8_t m[]
                    , const cap_PT_RT_IRTemp_Temp_FL_1_9961765_t *pFrameStruct
                    )
{

    /* Pack signal IR_Temperature_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal IR_Temperature_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IRTemp_Temp_FL_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_FL_1_9961765_sts, which models frame RT_IRTemp_Temp_FL_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IRTemp_Temp_FL_1(const uint8_t m[])
{
    cap_unpack_PT_RT_IRTemp_Temp_FL_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_FL_1_9961765()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IRTemp_Temp_FL_1 */



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IRTemp_Temp_FL_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IRTemp_Temp_FL_1
                    ( cap_PT_RT_IRTemp_Temp_FL_1_9961765_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->IR_Temperature_1 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);
    pFrameStruct->IR_Temperature_2 =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->IR_Temperature_3 =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->IR_Temperature_4 =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_IRTemp_Temp_FL_1 */


/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_30_9510437_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IRTemp_Temp_30(uint8_t m[])
{
    cap_pack_PT_RT_IRTemp_Temp_30
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_30_9510437()
            );
} /* End of cap_packApi_PT_RT_IRTemp_Temp_30 */




/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IRTemp_Temp_30.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IRTemp_Temp_30
                    ( uint8_t m[]
                    , const cap_PT_RT_IRTemp_Temp_30_9510437_t *pFrameStruct
                    )
{

    /* Pack signal IR_Temperature_30. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_30;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IRTemp_Temp_30 */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_30_9510437_sts, which models frame RT_IRTemp_Temp_30.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IRTemp_Temp_30(const uint8_t m[])
{
    cap_unpack_PT_RT_IRTemp_Temp_30
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_30_9510437()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IRTemp_Temp_30 */



/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IRTemp_Temp_30.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IRTemp_Temp_30
                    ( cap_PT_RT_IRTemp_Temp_30_9510437_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->IR_Temperature_30 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_IRTemp_Temp_30 */
#endif



/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_26_9509413_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IRTemp_Temp_26(uint8_t m[])
{
    cap_pack_PT_RT_IRTemp_Temp_26
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_26_9509413()
            );
} /* End of cap_packApi_PT_RT_IRTemp_Temp_26 */




/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IRTemp_Temp_26.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IRTemp_Temp_26
                    ( uint8_t m[]
                    , const cap_PT_RT_IRTemp_Temp_26_9509413_t *pFrameStruct
                    )
{

    /* Pack signal IR_Temperature_26. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_26;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IRTemp_Temp_26 */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_26_9509413_sts, which models frame RT_IRTemp_Temp_26.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IRTemp_Temp_26(const uint8_t m[])
{
    cap_unpack_PT_RT_IRTemp_Temp_26
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_26_9509413()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IRTemp_Temp_26 */



/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IRTemp_Temp_26.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IRTemp_Temp_26
                    ( cap_PT_RT_IRTemp_Temp_26_9509413_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->IR_Temperature_26 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_IRTemp_Temp_26 */
#endif




#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_1_9503013_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IRTemp_Temp_1(uint8_t m[])
{
    cap_pack_PT_RT_IRTemp_Temp_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_1_9503013()
            );
} /* End of cap_packApi_PT_RT_IRTemp_Temp_1 */




/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IRTemp_Temp_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IRTemp_Temp_1
                    ( uint8_t m[]
                    , const cap_PT_RT_IRTemp_Temp_1_9503013_t *pFrameStruct
                    )
{

    /* Pack signal IR_Temperature_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->IR_Temperature_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }

    /* Pack signal CRC. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->CRC;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IRTemp_Temp_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IRTemp_Temp_1_9503013_sts, which models frame RT_IRTemp_Temp_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IRTemp_Temp_1(const uint8_t m[])
{
    cap_unpack_PT_RT_IRTemp_Temp_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IRTemp_Temp_1_9503013()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IRTemp_Temp_1 */



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IRTemp_Temp_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IRTemp_Temp_1
                    ( cap_PT_RT_IRTemp_Temp_1_9503013_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->IR_Temperature_1 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_IRTemp_Temp_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Final_Condition_9242402_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Trig_Final_Condition(uint8_t m[])
{
    cap_pack_PT_RT_SB_Trig_Final_Condition
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Final_Condition_9242402()
            );
} /* End of cap_packApi_PT_RT_SB_Trig_Final_Condition */




/**
 * Pack the signals of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Trig_Final_Condition.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Trig_Final_Condition
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Trig_Final_Condition_9242402_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Validity_Final_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Final_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Final_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Final_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Trig_Final_Condition */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Final_Condition_9242402_sts, which models frame RT_SB_Trig_Final_Condition.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Trig_Final_Condition(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Trig_Final_Condition
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Final_Condition_9242402()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Trig_Final_Condition */



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Trig_Final_Condition.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Trig_Final_Condition
                    ( cap_PT_RT_SB_Trig_Final_Condition_9242402_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Final_Speed =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Final_Speed =
        (uint32_t)((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]);

} /* End of cap_unpack_PT_RT_SB_Trig_Final_Condition */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Initial_Condition_794_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Trig_Initial_Condition(uint8_t m[])
{
    cap_pack_PT_RT_SB_Trig_Initial_Condition
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Initial_Condition_794()
            );
} /* End of cap_packApi_PT_RT_SB_Trig_Initial_Condition */




/**
 * Pack the signals of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Trig_Initial_Condition.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Trig_Initial_Condition
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Trig_Initial_Condition_794_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Initial_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Initial_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Initial_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Initial_Heading << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Initial_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Initial_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Initial_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Initial_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal MFDD_Start_Threshold. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->MFDD_Start_Threshold;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
    }

    /* Pack signal MFDD_End_Threshold. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->MFDD_End_Threshold;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Trig_Initial_Condition */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Initial_Condition_794_sts, which models frame RT_SB_Trig_Initial_Condition.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Trig_Initial_Condition(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Trig_Initial_Condition
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Initial_Condition_794()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Trig_Initial_Condition */



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Trig_Initial_Condition.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Trig_Initial_Condition
                    ( cap_PT_RT_SB_Trig_Initial_Condition_794_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Initial_Speed =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Initial_Heading =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Initial_Speed =
        (uint32_t)((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]);
    pFrameStruct->Initial_Heading =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->MFDD_Start_Threshold =
        (uint8_t)((uint8_t)m[6]);
    pFrameStruct->MFDD_End_Threshold =
        (uint8_t)((uint8_t)m[7]);

} /* End of cap_unpack_PT_RT_SB_Trig_Initial_Condition */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Direct_Dist_9241890_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Trig_Direct_Dist(uint8_t m[])
{
    cap_pack_PT_RT_SB_Trig_Direct_Dist
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Direct_Dist_9241890()
            );
} /* End of cap_packApi_PT_RT_SB_Trig_Direct_Dist */




/**
 * Pack the signals of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Trig_Direct_Dist.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Trig_Direct_Dist
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Trig_Direct_Dist_9241890_t *pFrameStruct
                    )
{

    /* Pack signal Direct_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Direct_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Path_Distance_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Path_Distance_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Trig_Direct_Dist */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Direct_Dist_9241890_sts, which models frame RT_SB_Trig_Direct_Dist.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Trig_Direct_Dist(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Trig_Direct_Dist
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Direct_Dist_9241890()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Trig_Direct_Dist */



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Trig_Direct_Dist.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Trig_Direct_Dist
                    ( cap_PT_RT_SB_Trig_Direct_Dist_9241890_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Direct_Distance =
        (uint32_t)((((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    pFrameStruct->Path_Distance_2D =
        (uint32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_Trig_Direct_Dist */


/**
 * Pack the signals of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Forward_Dist_9241634_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Trig_Forward_Dist(uint8_t m[])
{
    cap_pack_PT_RT_SB_Trig_Forward_Dist
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Forward_Dist_9241634()
            );
} /* End of cap_packApi_PT_RT_SB_Trig_Forward_Dist */




/**
 * Pack the signals of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Trig_Forward_Dist.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Trig_Forward_Dist
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Trig_Forward_Dist_9241634_t *pFrameStruct
                    )
{

    /* Pack signal Forward_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Forward_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Deviation_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Deviation_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Trig_Forward_Dist */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Forward_Dist_9241634_sts, which models frame RT_SB_Trig_Forward_Dist.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Trig_Forward_Dist(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Trig_Forward_Dist
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Forward_Dist_9241634()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Trig_Forward_Dist */



/**
 * Unpack the signals of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Trig_Forward_Dist.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Trig_Forward_Dist
                    ( cap_PT_RT_SB_Trig_Forward_Dist_9241634_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Forward_Distance =
        (int32_t)((((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    pFrameStruct->Deviation_Distance =
        (int32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_Trig_Forward_Dist */
#endif




#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Path_Dist_9241378_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Trig_Path_Dist(uint8_t m[])
{
    cap_pack_PT_RT_SB_Trig_Path_Dist
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Path_Dist_9241378()
            );
} /* End of cap_packApi_PT_RT_SB_Trig_Path_Dist */




/**
 * Pack the signals of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Trig_Path_Dist.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Trig_Path_Dist
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Trig_Path_Dist_9241378_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Path_Distance_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Path_Distance_3D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Trig_Path_Dist */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Path_Dist_9241378_sts, which models frame RT_SB_Trig_Path_Dist.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Trig_Path_Dist(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Trig_Path_Dist
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Path_Dist_9241378()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Trig_Path_Dist */



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Trig_Path_Dist.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Trig_Path_Dist
                    ( cap_PT_RT_SB_Trig_Path_Dist_9241378_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Path_Distance_3D =
        (uint32_t)((((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_SB_Trig_Path_Dist */


/**
 * Pack the signals of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Accel_9241122_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Trig_Accel(uint8_t m[])
{
    cap_pack_PT_RT_SB_Trig_Accel
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Accel_9241122()
            );
} /* End of cap_packApi_PT_RT_SB_Trig_Accel */




/**
 * Pack the signals of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Trig_Accel.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Trig_Accel
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Trig_Accel_9241122_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_MFDD. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_MFDD;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Average_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Average_Accel << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_Triggered_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Triggered_Time << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal MFDD. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->MFDD;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }

    /* Pack signal Average_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Average_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] = (uint8_t)s;
    }

    /* Pack signal Triggered_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Triggered_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Trig_Accel */


#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trig_Accel_9241122_sts, which models frame RT_SB_Trig_Accel.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Trig_Accel(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Trig_Accel
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trig_Accel_9241122()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Trig_Accel */



/**
 * Unpack the signals of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Trig_Accel.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Trig_Accel
                    ( cap_PT_RT_SB_Trig_Accel_9241122_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_MFDD =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Average_Accel =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_Triggered_Time =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->MFDD =
        (int16_t)((((uint16_t)m[2]) << 8) | m[1]);
    pFrameStruct->Average_Accel =
        (int16_t)((((uint16_t)m[4]) << 8) | m[3]);
    pFrameStruct->Triggered_Time =
        (uint32_t)((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]);

} /* End of cap_unpack_PT_RT_SB_Trig_Accel */
#endif




#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_11_9833252_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_11(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_11
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_11_9833252()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_11 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_11.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_11
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_11_9833252_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_11. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_11;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_11 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_11_9833252_sts, which models frame RT_DL1MK3_Measure_Time_11.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_11(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_11
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_11_9833252()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_11 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_11.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_11
                    ( cap_PT_RT_DL1MK3_Measure_Time_11_9833252_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_11 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_11 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_10_9832996_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_10(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_10
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_10_9832996()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_10 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_10.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_10
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_10_9832996_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_10. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_10;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_10 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_10_9832996_sts, which models frame RT_DL1MK3_Measure_Time_10.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_10(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_10
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_10_9832996()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_10 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_10.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_10
                    ( cap_PT_RT_DL1MK3_Measure_Time_10_9832996_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_10 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_10 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_9_9832740_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_9(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_9
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_9_9832740()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_9 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_9.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_9
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_9_9832740_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_9. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_9;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_9 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_9_9832740_sts, which models frame RT_DL1MK3_Measure_Time_9.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_9(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_9
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_9_9832740()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_9 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_9.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_9
                    ( cap_PT_RT_DL1MK3_Measure_Time_9_9832740_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_9 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_9 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_8_9832484_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_8(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_8
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_8_9832484()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_8 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_8.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_8
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_8_9832484_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_8. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_8;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_8 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_8_9832484_sts, which models frame RT_DL1MK3_Measure_Time_8.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_8(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_8
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_8_9832484()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_8 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_8.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_8
                    ( cap_PT_RT_DL1MK3_Measure_Time_8_9832484_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_8 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_8 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_7_9832228_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_7(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_7
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_7_9832228()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_7 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_7.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_7
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_7_9832228_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_7 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_7_9832228_sts, which models frame RT_DL1MK3_Measure_Time_7.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_7(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_7
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_7_9832228()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_7 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_7.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_7
                    ( cap_PT_RT_DL1MK3_Measure_Time_7_9832228_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_7 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_7 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_6_9831972_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_6(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_6
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_6_9831972()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_6 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_6.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_6
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_6_9831972_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_6. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_6 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_6_9831972_sts, which models frame RT_DL1MK3_Measure_Time_6.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_6(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_6
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_6_9831972()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_6 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_6.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_6
                    ( cap_PT_RT_DL1MK3_Measure_Time_6_9831972_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_6 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_6 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_5_9831716_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_5(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_5
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_5_9831716()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_5 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_5.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_5
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_5_9831716_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_5 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_5_9831716_sts, which models frame RT_DL1MK3_Measure_Time_5.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_5(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_5
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_5_9831716()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_5 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_5.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_5
                    ( cap_PT_RT_DL1MK3_Measure_Time_5_9831716_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_5 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_5 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_4_9831460_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_4(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_4
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_4_9831460()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_4 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_4.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_4
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_4_9831460_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_4 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_4_9831460_sts, which models frame RT_DL1MK3_Measure_Time_4.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_4(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_4
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_4_9831460()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_4 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_4.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_4
                    ( cap_PT_RT_DL1MK3_Measure_Time_4_9831460_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_4 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_4 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_3_9831204_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_3(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_3
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_3_9831204()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_3 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_3.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_3
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_3_9831204_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_3 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_3_9831204_sts, which models frame RT_DL1MK3_Measure_Time_3.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_3(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_3
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_3_9831204()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_3 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_3.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_3
                    ( cap_PT_RT_DL1MK3_Measure_Time_3_9831204_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_3 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_3 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_2_9830948_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_2(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_2_9830948()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_2 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_2
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_2_9830948_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_2_9830948_sts, which models frame RT_DL1MK3_Measure_Time_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_2(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_2_9830948()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_2 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_2
                    ( cap_PT_RT_DL1MK3_Measure_Time_2_9830948_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_2 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_1_9830692_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Measure_Time_1(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Measure_Time_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_1_9830692()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Measure_Time_1 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Measure_Time_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Measure_Time_1
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Measure_Time_1_9830692_t *pFrameStruct
                    )
{

    /* Pack signal Measured_Time_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Measured_Time_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Measure_Time_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_1_9830692_sts, which models frame RT_DL1MK3_Measure_Time_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_1(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Measure_Time_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Measure_Time_1_9830692()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Measure_Time_1 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Measure_Time_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Measure_Time_1
                    ( cap_PT_RT_DL1MK3_Measure_Time_1_9830692_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Measured_Time_1 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Measure_Time_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_RPM_9767972_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_RPM(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_RPM
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_RPM_9767972()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_RPM */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_RPM.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_RPM
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_RPM_9767972_t *pFrameStruct
                    )
{

    /* Pack signal RPM. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->RPM;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_RPM */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_RPM_9767972_sts, which models frame RT_DL1MK3_RPM.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_RPM(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_RPM
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_RPM_9767972()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_RPM */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_RPM.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_RPM
                    ( cap_PT_RT_DL1MK3_RPM_9767972_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->RPM =
        (uint16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_RPM */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Freq_4_9767716_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Freq_4(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Freq_4
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Freq_4_9767716()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Freq_4 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Freq_4.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Freq_4
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Freq_4_9767716_t *pFrameStruct
                    )
{

    /* Pack signal Frequency_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Frequency_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Freq_4 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Freq_4_9767716_sts, which models frame RT_DL1MK3_Freq_4.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Freq_4(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Freq_4
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Freq_4_9767716()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Freq_4 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Freq_4.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Freq_4
                    ( cap_PT_RT_DL1MK3_Freq_4_9767716_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Frequency_4 =
        (uint16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Freq_4 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Misc_3_9896740_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Misc_3(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Misc_3
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Misc_3_9896740()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Misc_3 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Misc_3.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Misc_3
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Misc_3_9896740_t *pFrameStruct
                    )
{

    /* Pack signal Misc_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Misc_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Misc_3 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Misc_3_9896740_sts, which models frame RT_DL1MK3_Misc_3.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Misc_3(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Misc_3
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Misc_3_9896740()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Misc_3 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Misc_3.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Misc_3
                    ( cap_PT_RT_DL1MK3_Misc_3_9896740_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Misc_3 =
        (uint16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Misc_3 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Misc_2_9896484_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Misc_2(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Misc_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Misc_2_9896484()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Misc_2 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Misc_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Misc_2
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Misc_2_9896484_t *pFrameStruct
                    )
{

    /* Pack signal Misc_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Misc_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Misc_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Misc_2_9896484_sts, which models frame RT_DL1MK3_Misc_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Misc_2(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Misc_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Misc_2_9896484()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Misc_2 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Misc_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Misc_2
                    ( cap_PT_RT_DL1MK3_Misc_2_9896484_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Misc_2 =
        (uint16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Misc_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Misc_1_9896228_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Misc_1(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Misc_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Misc_1_9896228()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Misc_1 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Misc_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Misc_1
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Misc_1_9896228_t *pFrameStruct
                    )
{

    /* Pack signal Misc_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Misc_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Misc_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Misc_1_9896228_sts, which models frame RT_DL1MK3_Misc_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Misc_1(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Misc_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Misc_1_9896228()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Misc_1 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Misc_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Misc_1
                    ( cap_PT_RT_DL1MK3_Misc_1_9896228_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Misc_1 =
        (uint16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Misc_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Aux_2_9699876_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Aux_2(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Aux_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Aux_2_9699876()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Aux_2 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Aux_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Aux_2
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Aux_2_9699876_t *pFrameStruct
                    )
{

    /* Pack signal AUX_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->AUX_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Aux_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Aux_2_9699876_sts, which models frame RT_DL1MK3_Aux_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Aux_2(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Aux_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Aux_2_9699876()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Aux_2 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Aux_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Aux_2
                    ( cap_PT_RT_DL1MK3_Aux_2_9699876_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->AUX_2 =
        (uint16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Aux_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Aux_1_9699620_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Aux_1(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Aux_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Aux_1_9699620()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Aux_1 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Aux_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Aux_1
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Aux_1_9699620_t *pFrameStruct
                    )
{

    /* Pack signal AUX_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->AUX_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Aux_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Aux_1_9699620_sts, which models frame RT_DL1MK3_Aux_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Aux_1(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Aux_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Aux_1_9699620()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Aux_1 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Aux_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Aux_1
                    ( cap_PT_RT_DL1MK3_Aux_1_9699620_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->AUX_1 =
        (uint16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Aux_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Pressure_5_9438500_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Pressure_5(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Pressure_5
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Pressure_5_9438500()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Pressure_5 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT
 * into a byte array of 3 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Pressure_5.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Pressure_5
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Pressure_5_9438500_t *pFrameStruct
                    )
{

    /* Pack signal Pressure_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Pressure_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Pressure_5 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT
 * from a byte array of 3 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Pressure_5_9438500_sts, which models frame RT_DL1MK3_Pressure_5.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Pressure_5(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Pressure_5
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Pressure_5_9438500()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Pressure_5 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT
 * from a byte array of 3 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Pressure_5.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Pressure_5
                    ( cap_PT_RT_DL1MK3_Pressure_5_9438500_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Pressure_5 =
        (uint32_t)((((((uint32_t)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Pressure_5 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Angle_3_9569060_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Angle_3(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Angle_3
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Angle_3_9569060()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Angle_3 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Angle_3.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Angle_3
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Angle_3_9569060_t *pFrameStruct
                    )
{

    /* Pack signal Angle_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Angle_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Angle_3 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Angle_3_9569060_sts, which models frame RT_DL1MK3_Angle_3.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Angle_3(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Angle_3
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Angle_3_9569060()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Angle_3 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Angle_3.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Angle_3
                    ( cap_PT_RT_DL1MK3_Angle_3_9569060_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Angle_3 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Angle_3 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Temp_1_9503012_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Temp_1(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Temp_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Temp_1_9503012()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Temp_1 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Temp_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Temp_1
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Temp_1_9503012_t *pFrameStruct
                    )
{

    /* Pack signal Temperature_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Temperature_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Temp_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Temp_1_9503012_sts, which models frame RT_DL1MK3_Temp_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Temp_1(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Temp_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Temp_1_9503012()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Temp_1 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Temp_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Temp_1
                    ( cap_PT_RT_DL1MK3_Temp_1_9503012_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Temperature_1 =
        (int16_t)((((uint16_t)m[1]) << 8) | m[0]);

} /* End of cap_unpack_PT_RT_DL1MK3_Temp_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Analog_3_8520228_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Analog_3(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Analog_3
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Analog_3_8520228()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Analog_3 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Analog_3.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Analog_3
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Analog_3_8520228_t *pFrameStruct
                    )
{

    /* Pack signal Analog_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Analog_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[0] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Analog_3 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Analog_3_8520228_sts, which models frame RT_DL1MK3_Analog_3.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Analog_3(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Analog_3
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Analog_3_8520228()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Analog_3 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Analog_3.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Analog_3
                    ( cap_PT_RT_DL1MK3_Analog_3_8520228_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Analog_3 =
        (uint16_t)((((uint16_t)m[0]) << 8) | m[1]);

} /* End of cap_unpack_PT_RT_DL1MK3_Analog_3 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Analog_2_8519972_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Analog_2(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Analog_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Analog_2_8519972()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Analog_2 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Analog_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Analog_2
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Analog_2_8519972_t *pFrameStruct
                    )
{

    /* Pack signal Analog_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Analog_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[0] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Analog_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Analog_2_8519972_sts, which models frame RT_DL1MK3_Analog_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Analog_2(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Analog_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Analog_2_8519972()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Analog_2 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Analog_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Analog_2
                    ( cap_PT_RT_DL1MK3_Analog_2_8519972_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Analog_2 =
        (uint16_t)((((uint16_t)m[0]) << 8) | m[1]);

} /* End of cap_unpack_PT_RT_DL1MK3_Analog_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Analog_1_8519716_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Analog_1(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Analog_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Analog_1_8519716()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Analog_1 */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT
 * into a byte array of 2 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Analog_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Analog_1
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Analog_1_8519716_t *pFrameStruct
                    )
{

    /* Pack signal Analog_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Analog_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[0] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Analog_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT
 * from a byte array of 2 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Analog_1_8519716_sts, which models frame RT_DL1MK3_Analog_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Analog_1(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Analog_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Analog_1_8519716()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Analog_1 */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT
 * from a byte array of 2 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Analog_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Analog_1
                    ( cap_PT_RT_DL1MK3_Analog_1_8519716_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Analog_1 =
        (uint16_t)((((uint16_t)m[0]) << 8) | m[1]);

} /* End of cap_unpack_PT_RT_DL1MK3_Analog_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Accel_8388644_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_DL1MK3_Accel(uint8_t m[])
{
    cap_pack_PT_RT_DL1MK3_Accel
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Accel_8388644()
            );
} /* End of cap_packApi_PT_RT_DL1MK3_Accel */




/**
 * Pack the signals of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_DL1MK3_Accel.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_DL1MK3_Accel
                    ( uint8_t m[]
                    , const cap_PT_RT_DL1MK3_Accel_8388644_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Accel_Lateral << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Accel_Vertical << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal SQC. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->SQC << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0xf0;
        m[0] |= (uint8_t)(s & 0xf0);
    }

    /* Pack signal Accuracy_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Accel_Lateral;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Accel_Vertical;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_DL1MK3_Accel */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_DL1MK3_Accel_8388644_sts, which models frame RT_DL1MK3_Accel.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_DL1MK3_Accel(const uint8_t m[])
{
    cap_unpack_PT_RT_DL1MK3_Accel
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_DL1MK3_Accel_8388644()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_DL1MK3_Accel */



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_DL1MK3_Accel.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_DL1MK3_Accel
                    ( cap_PT_RT_DL1MK3_Accel_8388644_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Accel_Longitudinal =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Accel_Lateral =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_Accel_Vertical =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_Accel =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Accel_Longitudinal =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->Accel_Lateral =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->Accel_Vertical =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_DL1MK3_Accel */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_INS_Status_9306146_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_INS_Status(uint8_t m[])
{
    cap_pack_PT_RT_SB_INS_Status
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_INS_Status_9306146()
            );
} /* End of cap_packApi_PT_RT_SB_INS_Status */




/**
 * Pack the signals of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_INS_Status.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_INS_Status
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_INS_Status_9306146_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal INS_Status. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->INS_Status;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_INS_Status */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_INS_Status_9306146_sts, which models frame RT_SB_INS_Status.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_INS_Status(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_INS_Status
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_INS_Status_9306146()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_INS_Status */



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_INS_Status.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_INS_Status
                    ( cap_PT_RT_SB_INS_Status_9306146_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->INS_Status =
        (uint8_t)((uint8_t)m[0]);

} /* End of cap_unpack_PT_RT_SB_INS_Status */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_INS_Attitude_9306402_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_INS_Attitude(uint8_t m[])
{
    cap_pack_PT_RT_SB_INS_Attitude
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_INS_Attitude_9306402()
            );
} /* End of cap_packApi_PT_RT_SB_INS_Attitude */




/**
 * Pack the signals of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_INS_Attitude.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_INS_Attitude
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_INS_Attitude_9306402_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Pitch << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Roll << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_Attitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_Attitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Attitude_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Attitude_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Attitude_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Attitude_Pitch;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal Attitude_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Attitude_Roll;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_INS_Attitude */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_INS_Attitude_9306402_sts, which models frame RT_SB_INS_Attitude.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_INS_Attitude(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_INS_Attitude
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_INS_Attitude_9306402()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_INS_Attitude */



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_INS_Attitude.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_INS_Attitude
                    ( cap_PT_RT_SB_INS_Attitude_9306402_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Yaw =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Pitch =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_Roll =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_Attitude =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Attitude_Yaw =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->Attitude_Pitch =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->Attitude_Roll =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_SB_INS_Attitude */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Output_Status_9240866_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Output_Status(uint8_t m[])
{
    cap_pack_PT_RT_SB_Output_Status
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Output_Status_9240866()
            );
} /* End of cap_packApi_PT_RT_SB_Output_Status */




/**
 * Pack the signals of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Output_Status.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Output_Status
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Output_Status_9240866_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Validity_Status_Timestamp. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Status_Timestamp;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Status_Analogue_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Status_Analogue_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x01;
        m[1] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Status_Analogue_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Status_Analogue_2 << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x02;
        m[1] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Status_Analogue_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Status_Analogue_3 << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x04;
        m[1] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Status_Analogue_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Status_Analogue_4 << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x08;
        m[1] |= (uint8_t)(s & 0x08);
    }

    /* Pack signal Status_Pulse_Output. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Status_Pulse_Output << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x10;
        m[1] |= (uint8_t)(s & 0x10);
    }

    /* Pack signal Status_Serial_Output_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Status_Serial_Output_1 << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x20;
        m[1] |= (uint8_t)(s & 0x20);
    }

    /* Pack signal Status_Serial_Output_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Status_Serial_Output_2 << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x40;
        m[1] |= (uint8_t)(s & 0x40);
    }

    /* Pack signal Status_Trigger. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Status_Trigger << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (uint8_t)~0x80;
        m[1] |= (uint8_t)(s & 0x80);
    }

    /* Pack signal GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Output_Status */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Output_Status_9240866_sts, which models frame RT_SB_Output_Status.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Output_Status(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Output_Status
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Output_Status_9240866()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Output_Status */



/**
 * Unpack the signals of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Output_Status.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Output_Status
                    ( cap_PT_RT_SB_Output_Status_9240866_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Status_Timestamp =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Status_Analogue_1 =
        (boolean_t)((uint8_t)(m[1] & 0x01));
    pFrameStruct->Status_Analogue_2 =
        (boolean_t)(((uint8_t)(m[1] & 0x02)) >> 1);
    pFrameStruct->Status_Analogue_3 =
        (boolean_t)(((uint8_t)(m[1] & 0x04)) >> 2);
    pFrameStruct->Status_Analogue_4 =
        (boolean_t)(((uint8_t)(m[1] & 0x08)) >> 3);
    pFrameStruct->Status_Pulse_Output =
        (boolean_t)(((uint8_t)(m[1] & 0x10)) >> 4);
    pFrameStruct->Status_Serial_Output_1 =
        (boolean_t)(((uint8_t)(m[1] & 0x20)) >> 5);
    pFrameStruct->Status_Serial_Output_2 =
        (boolean_t)(((uint8_t)(m[1] & 0x40)) >> 6);
    pFrameStruct->Status_Trigger =
        (boolean_t)(((uint8_t)(m[1] & 0x80)) >> 7);
    pFrameStruct->GPS_Time =
        (uint32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_Output_Status */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Heading_Gradient_2(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Heading_Gradient_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Heading_Gradient_2_9180706()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Heading_Gradient_2 */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Heading_Gradient_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Heading_Gradient_2
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_GPS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Gradient << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal GPS_Heading_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->GPS_Heading_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
    }

    /* Pack signal GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->GPS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Heading_Gradient_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts, which models frame RT_SB_GPS_Heading_Gradient_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Heading_Gradient_2(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Heading_Gradient_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Heading_Gradient_2_9180706()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Heading_Gradient_2 */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Heading_Gradient_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Heading_Gradient_2
                    ( cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Heading =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Gradient =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Accuracy_GPS_Heading =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->GPS_Heading_2 =
        (uint16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->Accuracy_GPS_Gradient =
        (uint8_t)((uint8_t)m[4]);
    pFrameStruct->GPS_Gradient =
        (int16_t)((((uint16_t)m[6]) << 8) | m[5]);

} /* End of cap_unpack_PT_RT_SB_GPS_Heading_Gradient_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Cumulative_Distance_2_8397090_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Cumulative_Distance_2(uint8_t m[])
{
    cap_pack_PT_RT_SB_Cumulative_Distance_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Cumulative_Distance_2_8397090()
            );
} /* End of cap_packApi_PT_RT_SB_Cumulative_Distance_2 */




/**
 * Pack the signals of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Cumulative_Distance_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Cumulative_Distance_2
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Cumulative_Distance_2_8397090_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Cumulative_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Cumulative_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Cumulative_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Cumulative_Distance << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Cumulative_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Cumulative_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Cumulative_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Cumulative_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Cumulative_Distance_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Cumulative_Distance_2_8397090_sts, which models frame RT_SB_Cumulative_Distance_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Cumulative_Distance_2(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Cumulative_Distance_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Cumulative_Distance_2_8397090()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Cumulative_Distance_2 */



/**
 * Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Cumulative_Distance_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Cumulative_Distance_2
                    ( cap_PT_RT_SB_Cumulative_Distance_2_8397090_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Cumulative_Time =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Cumulative_Distance =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Cumulative_Time =
        (uint32_t)((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]);
    pFrameStruct->Cumulative_Distance =
        (uint32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_Cumulative_Distance_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Cumulative_Distance_1_8396834_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Cumulative_Distance_1(uint8_t m[])
{
    cap_pack_PT_RT_SB_Cumulative_Distance_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Cumulative_Distance_1_8396834()
            );
} /* End of cap_packApi_PT_RT_SB_Cumulative_Distance_1 */




/**
 * Pack the signals of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Cumulative_Distance_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Cumulative_Distance_1
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Cumulative_Distance_1_8396834_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Cumulative_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Cumulative_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Cumulative_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Cumulative_Distance << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Cumulative_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Cumulative_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Cumulative_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Cumulative_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Cumulative_Distance_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Cumulative_Distance_1_8396834_sts, which models frame RT_SB_Cumulative_Distance_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Cumulative_Distance_1(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Cumulative_Distance_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Cumulative_Distance_1_8396834()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Cumulative_Distance_1 */



/**
 * Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Cumulative_Distance_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Cumulative_Distance_1
                    ( cap_PT_RT_SB_Cumulative_Distance_1_8396834_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Cumulative_Time =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Cumulative_Distance =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Cumulative_Time =
        (uint32_t)((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]);
    pFrameStruct->Cumulative_Distance =
        (uint32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_Cumulative_Distance_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trigger_Timestamp_9240610_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Trigger_Timestamp(uint8_t m[])
{
    cap_pack_PT_RT_SB_Trigger_Timestamp
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trigger_Timestamp_9240610()
            );
} /* End of cap_packApi_PT_RT_SB_Trigger_Timestamp */




/**
 * Pack the signals of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Trigger_Timestamp.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Trigger_Timestamp
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Trigger_Timestamp_9240610_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[2] = 0xff;

    /* Pack signal Validity_Trigger_Timestamp. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Trigger_Timestamp;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Accuracy_Trigger_Timestamp. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_Trigger_Timestamp;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Trigger_Number. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Trigger_Number;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (uint8_t)~0x7f;
        m[2] |= (uint8_t)(s & 0x7f);
    }

    /* Pack signal Trigger_Timestamp_Type. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Trigger_Timestamp_Type << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (uint8_t)~0x80;
        m[2] |= (uint8_t)(s & 0x80);
    }

    /* Pack signal GPS_High_Resolution_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint64_t s = (uint64_t)pFrameStruct->GPS_High_Resolution_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Trigger_Timestamp */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Trigger_Timestamp_9240610_sts, which models frame RT_SB_Trigger_Timestamp.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Trigger_Timestamp(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Trigger_Timestamp
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Trigger_Timestamp_9240610()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Trigger_Timestamp */



/**
 * Unpack the signals of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Trigger_Timestamp.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Trigger_Timestamp
                    ( cap_PT_RT_SB_Trigger_Timestamp_9240610_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Trigger_Timestamp =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Accuracy_Trigger_Timestamp =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Trigger_Number =
        (uint8_t)((uint8_t)(m[2] & 0x7f));
    pFrameStruct->Trigger_Timestamp_Type =
        (boolean_t)(((uint8_t)(m[2] & 0x80)) >> 7);
    pFrameStruct->GPS_High_Resolution_Time =
        (uint64_t)((((((((((uint64_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]) << 8) | m[3]);

} /* End of cap_unpack_PT_RT_SB_Trigger_Timestamp */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IMU06_Gyro_Rates_8388897_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IMU06_Gyro_Rates(uint8_t m[])
{
    cap_pack_PT_RT_IMU06_Gyro_Rates
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IMU06_Gyro_Rates_8388897()
            );
} /* End of cap_packApi_PT_RT_IMU06_Gyro_Rates */




/**
 * Pack the signals of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IMU06_Gyro_Rates.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IMU06_Gyro_Rates
                    ( uint8_t m[]
                    , const cap_PT_RT_IMU06_Gyro_Rates_8388897_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Gyro_Rate_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Gyro_Rate_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Gyro_Rate_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Gyro_Rate_Pitch << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_Gyro_Rate_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Gyro_Rate_Roll << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_Gyro_Rates. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_Gyro_Rates;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Gyro_Rate_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Gyro_Rate_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Gyro_Rate_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Gyro_Rate_Pitch;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal Gyro_Rate_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Gyro_Rate_Roll;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IMU06_Gyro_Rates */
#endif



/**
 * Unpack the signals of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IMU06_Gyro_Rates_8388897_sts, which models frame RT_IMU06_Gyro_Rates.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IMU06_Gyro_Rates(const uint8_t m[])
{
    cap_unpack_PT_RT_IMU06_Gyro_Rates
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IMU06_Gyro_Rates_8388897()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IMU06_Gyro_Rates */



/**
 * Unpack the signals of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IMU06_Gyro_Rates.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IMU06_Gyro_Rates
                    ( cap_PT_RT_IMU06_Gyro_Rates_8388897_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Gyro_Rate_Yaw =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Gyro_Rate_Pitch =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_Gyro_Rate_Roll =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_Gyro_Rates =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Gyro_Rate_Yaw =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->Gyro_Rate_Pitch =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->Gyro_Rate_Roll =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_IMU06_Gyro_Rates */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IMU06_Accel (8388641, 0x800021) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_IMU06_Accel_8388641_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_IMU06_Accel(uint8_t m[])
{
    cap_pack_PT_RT_IMU06_Accel
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_IMU06_Accel_8388641()
            );
} /* End of cap_packApi_PT_RT_IMU06_Accel */




/**
 * Pack the signals of inbound PDU RT_IMU06_Accel (8388641, 0x800021) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_IMU06_Accel.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_IMU06_Accel
                    ( uint8_t m[]
                    , const cap_PT_RT_IMU06_Accel_8388641_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Accel_Lateral << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Accel_Vertical << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Accel_Lateral;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Accel_Vertical;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_IMU06_Accel */
#endif



/**
 * Unpack the signals of inbound PDU RT_IMU06_Accel (8388641, 0x800021) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_IMU06_Accel_8388641_sts, which models frame RT_IMU06_Accel.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_IMU06_Accel(const uint8_t m[])
{
    cap_unpack_PT_RT_IMU06_Accel
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_IMU06_Accel_8388641()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_IMU06_Accel */



/**
 * Unpack the signals of inbound PDU RT_IMU06_Accel (8388641, 0x800021) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_IMU06_Accel.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_IMU06_Accel
                    ( cap_PT_RT_IMU06_Accel_8388641_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Accel_Longitudinal =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Accel_Lateral =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_Accel_Vertical =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_Accel =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Accel_Longitudinal =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->Accel_Lateral =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->Accel_Vertical =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_IMU06_Accel */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Speed (8392738, 0x801022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Speed_8392738_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Speed(uint8_t m[])
{
    cap_pack_PT_RT_SB_Speed
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Speed_8392738()
            );
} /* End of cap_packApi_PT_RT_SB_Speed */




/**
 * Pack the signals of inbound PDU RT_SB_Speed (8392738, 0x801022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Speed.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Speed
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Speed_8392738_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[6] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Accuracy_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Speed */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Speed (8392738, 0x801022) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Speed_8392738_sts, which models frame RT_SB_Speed.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Speed(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Speed
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Speed_8392738()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Speed */



/**
 * Unpack the signals of inbound PDU RT_SB_Speed (8392738, 0x801022) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Speed.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Speed
                    ( cap_PT_RT_SB_Speed_8392738_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Speed =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Accuracy_Speed =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Speed =
        (int32_t)((((((((uint32_t)m[5]) << 8) | m[4]) << 8) | m[3]) << 8) | m[2]);

} /* End of cap_unpack_PT_RT_SB_Speed */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_RTK_Slip_9183522_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_RTK_Slip(uint8_t m[])
{
    cap_pack_PT_RT_SB_RTK_Slip
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_RTK_Slip_9183522()
            );
} /* End of cap_packApi_PT_RT_SB_RTK_Slip */




/**
 * Pack the signals of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_RTK_Slip.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_RTK_Slip
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_RTK_Slip_9183522_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_RTK_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_RTK_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_RTK_Squat. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_RTK_Squat << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_RTK_Baseline. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_RTK_Baseline << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_RTK_Baseline. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_RTK_Baseline;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal RTK_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->RTK_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal RTK_Squat. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->RTK_Squat;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal RTK_Baseline. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->RTK_Baseline;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_RTK_Slip */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_RTK_Slip_9183522_sts, which models frame RT_SB_RTK_Slip.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_RTK_Slip(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_RTK_Slip
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_RTK_Slip_9183522()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_RTK_Slip */



/**
 * Unpack the signals of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_RTK_Slip.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_RTK_Slip
                    ( cap_PT_RT_SB_RTK_Slip_9183522_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_RTK_Slip =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_RTK_Squat =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_RTK_Baseline =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_RTK_Baseline =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->RTK_Slip =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->RTK_Squat =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->RTK_Baseline =
        (uint16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_SB_RTK_Slip */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_RTK_Attitude_9183266_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_RTK_Attitude(uint8_t m[])
{
    cap_pack_PT_RT_SB_RTK_Attitude
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_RTK_Attitude_9183266()
            );
} /* End of cap_packApi_PT_RT_SB_RTK_Attitude */




/**
 * Pack the signals of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_RTK_Attitude.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_RTK_Attitude
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_RTK_Attitude_9183266_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_RTK_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_RTK_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_RTK_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_RTK_Pitch << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_RTK_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_RTK_Roll << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_RTK_Attitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_RTK_Attitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal RTK_Attitude_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->RTK_Attitude_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal RTK_Attitude_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->RTK_Attitude_Pitch;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal RTK_Attitude_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->RTK_Attitude_Roll;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_RTK_Attitude */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_RTK_Attitude_9183266_sts, which models frame RT_SB_RTK_Attitude.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_RTK_Attitude(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_RTK_Attitude
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_RTK_Attitude_9183266()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_RTK_Attitude */



/**
 * Unpack the signals of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_RTK_Attitude.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_RTK_Attitude
                    ( cap_PT_RT_SB_RTK_Attitude_9183266_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_RTK_Yaw =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_RTK_Pitch =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_RTK_Roll =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_RTK_Attitude =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->RTK_Attitude_Yaw =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->RTK_Attitude_Pitch =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->RTK_Attitude_Roll =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_SB_RTK_Attitude */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Mcycle_Lean_9187362_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Mcycle_Lean(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Mcycle_Lean
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Mcycle_Lean_9187362()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Mcycle_Lean */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Mcycle_Lean.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Mcycle_Lean
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[6] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_GPS_Lateral_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Lateral_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Mcycle_Lean. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Mcycle_Lean << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Lateral_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Lateral_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal GPS_Lateral_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->GPS_Lateral_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_Mcycle_Lean_Angle. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->GPS_Mcycle_Lean_Angle;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Mcycle_Lean */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Mcycle_Lean_9187362_sts, which models frame RT_SB_GPS_Mcycle_Lean.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Mcycle_Lean(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Mcycle_Lean
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Mcycle_Lean_9187362()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Mcycle_Lean */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Mcycle_Lean.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Mcycle_Lean
                    ( cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Lateral_Accel =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Mcycle_Lean =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Accuracy_GPS_Lateral_Accel =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->GPS_Lateral_Accel =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->GPS_Mcycle_Lean_Angle =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_GPS_Mcycle_Lean */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Status_9175074_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Status(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Status
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Status_9175074()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Status */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Status.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Status
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Status_9175074_t *pFrameStruct
                    )
{

    /* Pack signal GPS_Status. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->GPS_Status;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
    }

    /* Pack signal Firmware_Version_Major. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Firmware_Version_Major;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Firmware_Version_Intermediate. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Firmware_Version_Intermediate;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
    }

    /* Pack signal Firmware_Version_Minor. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Firmware_Version_Minor;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_nSv. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->GPS_nSv;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
    }

    /* Pack signal GPS_nSv_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->GPS_nSv_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_t)s;
    }

    /* Pack signal GPS_nSv_RTK. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->GPS_nSv_RTK;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
    }

    /* Pack signal RTK_Status. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->RTK_Status;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Status */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Status_9175074_sts, which models frame RT_SB_GPS_Status.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Status(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Status
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Status_9175074()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Status */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Status.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Status
                    ( cap_PT_RT_SB_GPS_Status_9175074_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->GPS_Status =
        (uint8_t)((uint8_t)m[0]);
    pFrameStruct->Firmware_Version_Major =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Firmware_Version_Intermediate =
        (uint8_t)((uint8_t)m[2]);
    pFrameStruct->Firmware_Version_Minor =
        (uint8_t)((uint8_t)m[3]);
    pFrameStruct->GPS_nSv =
        (uint8_t)((uint8_t)m[4]);
    pFrameStruct->GPS_nSv_2 =
        (uint8_t)((uint8_t)m[5]);
    pFrameStruct->GPS_nSv_RTK =
        (uint8_t)((uint8_t)m[6]);
    pFrameStruct->RTK_Status =
        (uint8_t)((uint8_t)m[7]);

} /* End of cap_unpack_PT_RT_SB_GPS_Status */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Pos_ECEF_2(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Pos_ECEF_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Pos_ECEF_2_9176354()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Pos_ECEF_2 */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Pos_ECEF_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Pos_ECEF_2
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_t *pFrameStruct
                    )
{

    /* Pack signal GPS_Pos_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Pos_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_Pos_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Pos_ECEF_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Pos_ECEF_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts, which models frame RT_SB_GPS_Pos_ECEF_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Pos_ECEF_2(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Pos_ECEF_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Pos_ECEF_2_9176354()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Pos_ECEF_2 */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Pos_ECEF_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Pos_ECEF_2
                    ( cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->GPS_Pos_ECEF_Y =
        (int32_t)((((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    pFrameStruct->GPS_Pos_ECEF_Z =
        (int32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_GPS_Pos_ECEF_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Pos_ECEF_1(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Pos_ECEF_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Pos_ECEF_1_9176098()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Pos_ECEF_1 */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Pos_ECEF_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Pos_ECEF_1
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Pos_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Pos_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Pos_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Pos_ECEF_Y << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_GPS_Pos_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Pos_ECEF_Z << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_GPS_Pos_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Pos_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Pos_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Pos_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Pos_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Pos_ECEF_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_Pos_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Pos_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Pos_ECEF_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts, which models frame RT_SB_GPS_Pos_ECEF_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Pos_ECEF_1(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Pos_ECEF_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Pos_ECEF_1_9176098()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Pos_ECEF_1 */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Pos_ECEF_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Pos_ECEF_1
                    ( cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Pos_ECEF_X =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Pos_ECEF_Y =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_GPS_Pos_ECEF_Z =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_GPS_Pos_ECEF_X =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Accuracy_GPS_Pos_ECEF_Y =
        (uint8_t)((uint8_t)m[2]);
    pFrameStruct->Accuracy_GPS_Pos_ECEF_Z =
        (uint8_t)((uint8_t)m[3]);
    pFrameStruct->GPS_Pos_ECEF_X =
        (int32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_GPS_Pos_ECEF_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_2_9175842_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Pos_LLH_2(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Pos_LLH_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Pos_LLH_2_9175842()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Pos_LLH_2 */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Pos_LLH_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Pos_LLH_2
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_t *pFrameStruct
                    )
{

    /* Pack signal GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (uint8_t)s;
        s >>= 8;
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Pos_LLH_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_2_9175842_sts, which models frame RT_SB_GPS_Pos_LLH_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Pos_LLH_2(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Pos_LLH_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Pos_LLH_2_9175842()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Pos_LLH_2 */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Pos_LLH_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Pos_LLH_2
                    ( cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->GPS_Pos_LLH_Longitude =
        (int32_t)((((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    pFrameStruct->GPS_Pos_LLH_Altitude =
        (int32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_GPS_Pos_LLH_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_1_9175586_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Pos_LLH_1(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Pos_LLH_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Pos_LLH_1_9175586()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Pos_LLH_1 */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Pos_LLH_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Pos_LLH_1
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Pos_LLH_Longitude << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Pos_LLH_Altitude << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Pos_LLH_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_1_9175586_sts, which models frame RT_SB_GPS_Pos_LLH_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Pos_LLH_1(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Pos_LLH_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Pos_LLH_1_9175586()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Pos_LLH_1 */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Pos_LLH_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Pos_LLH_1
                    ( cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Pos_LLH_Latitude =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Pos_LLH_Longitude =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_GPS_Pos_LLH_Altitude =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_GPS_Pos_LLH_Latitude =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Accuracy_GPS_Pos_LLH_Longitude =
        (uint8_t)((uint8_t)m[2]);
    pFrameStruct->Accuracy_GPS_Pos_LLH_Altitude =
        (uint8_t)((uint8_t)m[3]);
    pFrameStruct->GPS_Pos_LLH_Latitude =
        (int32_t)((((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of cap_unpack_PT_RT_SB_GPS_Pos_LLH_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_9180450_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Heading_Gradient(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Heading_Gradient
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Heading_Gradient_9180450()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Heading_Gradient */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Heading_Gradient.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Heading_Gradient
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Heading_Gradient_9180450_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_GPS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Gradient << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal GPS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
    }

    /* Pack signal GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->GPS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Heading_Gradient */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_9180450_sts, which models frame RT_SB_GPS_Heading_Gradient.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Heading_Gradient(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Heading_Gradient
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Heading_Gradient_9180450()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Heading_Gradient */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Heading_Gradient.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Heading_Gradient
                    ( cap_PT_RT_SB_GPS_Heading_Gradient_9180450_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Heading =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Gradient =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Accuracy_GPS_Heading =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->GPS_Heading =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->Accuracy_GPS_Gradient =
        (uint8_t)((uint8_t)m[4]);
    pFrameStruct->GPS_Gradient =
        (int16_t)((((uint16_t)m[6]) << 8) | m[5]);

} /* End of cap_unpack_PT_RT_SB_GPS_Heading_Gradient */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Vel_ECEF_2(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Vel_ECEF_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Vel_ECEF_2_9180194()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Vel_ECEF_2 */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Vel_ECEF_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Vel_ECEF_2
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_GPS_Vel_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Vel_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Vel_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Vel_ECEF_Z << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal GPS_Vel_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Vel_ECEF_Y << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
        s >>= 8;
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_Vel_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Vel_ECEF_Z << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Vel_ECEF_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts, which models frame RT_SB_GPS_Vel_ECEF_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Vel_ECEF_2(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Vel_ECEF_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Vel_ECEF_2_9180194()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Vel_ECEF_2 */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Vel_ECEF_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Vel_ECEF_2
                    ( cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Vel_ECEF_Y =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Vel_ECEF_Z =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->GPS_Vel_ECEF_Y =
        (int32_t)((int32_t)(((((((uint32_t)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) >> 8);
    pFrameStruct->GPS_Vel_ECEF_Z =
        (int32_t)((int32_t)(((((((uint32_t)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of cap_unpack_PT_RT_SB_GPS_Vel_ECEF_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Vel_ECEF_1(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Vel_ECEF_1
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Vel_ECEF_1_9179938()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Vel_ECEF_1 */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Vel_ECEF_1.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Vel_ECEF_1
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_GPS_Vel_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Vel_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Accuracy_GPS_Vel_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Vel_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Vel_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Vel_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
    }

    /* Pack signal Accuracy_GPS_Vel_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Vel_ECEF_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (uint8_t)s;
    }

    /* Pack signal GPS_Vel_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Vel_ECEF_X << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Vel_ECEF_1 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts, which models frame RT_SB_GPS_Vel_ECEF_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Vel_ECEF_1(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Vel_ECEF_1
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Vel_ECEF_1_9179938()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Vel_ECEF_1 */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Vel_ECEF_1.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Vel_ECEF_1
                    ( cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Vel_ECEF_X =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Accuracy_GPS_Vel_ECEF_X =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Accuracy_GPS_Vel_ECEF_Y =
        (uint8_t)((uint8_t)m[2]);
    pFrameStruct->Accuracy_GPS_Vel_ECEF_Z =
        (uint8_t)((uint8_t)m[3]);
    pFrameStruct->GPS_Vel_ECEF_X =
        (int32_t)((int32_t)(((((((uint32_t)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of cap_unpack_PT_RT_SB_GPS_Vel_ECEF_1 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Vel_NED_2_0_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Vel_NED_2(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Vel_NED_2
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Vel_NED_2_0()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Vel_NED_2 */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Vel_NED_2.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Vel_NED_2
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Vel_NED_2_0_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Validity_GPS_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Vel_NED_D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Accuracy_GPS_Vel_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Vel_D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal GPS_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Vel_NED_D << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Vel_NED_2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Vel_NED_2_0_sts, which models frame RT_SB_GPS_Vel_NED_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Vel_NED_2(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Vel_NED_2
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Vel_NED_2_0()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Vel_NED_2 */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Vel_NED_2.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Vel_NED_2
                    ( cap_PT_RT_SB_GPS_Vel_NED_2_0_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Vel_NED_D =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Accuracy_GPS_Vel_D =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->GPS_Vel_NED_D =
        (int32_t)((int32_t)(((((((uint32_t)m[4]) << 8) | m[3]) << 8) | m[2]) << 8) >> 8);

} /* End of cap_unpack_PT_RT_SB_GPS_Vel_NED_2 */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Speed (1818, 0x71a) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Speed_1818_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Speed(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Speed
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Speed_1818()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Speed */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Speed (1818, 0x71a) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Speed.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Speed
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Speed_1818_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Speed_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Speed_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Speed_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Speed_3D << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal GPS_Speed_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Speed_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] = (uint8_t)s;
    }

    /* Pack signal GPS_Speed_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Speed_3D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (uint8_t)s;
        s >>= 8;
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Speed */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Speed (1818, 0x71a) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Speed_1818_sts, which models frame RT_SB_GPS_Speed.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Speed(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Speed
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Speed_1818()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Speed */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Speed (1818, 0x71a) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Speed.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Speed
                    ( cap_PT_RT_SB_GPS_Speed_1818_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Speed_2D =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Speed_3D =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Accuracy_GPS_Speed =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->GPS_Speed_2D =
        (uint32_t)((((((uint32_t)m[4]) << 8) | m[3]) << 8) | m[2]);
    pFrameStruct->GPS_Speed_3D =
        (uint32_t)((((((uint32_t)m[7]) << 8) | m[6]) << 8) | m[5]);

} /* End of cap_unpack_PT_RT_SB_GPS_Speed */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Time (2047, 0x7ff) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Time_2047_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_GPS_Time(uint8_t m[])
{
    cap_pack_PT_RT_SB_GPS_Time
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Time_2047()
            );
} /* End of cap_packApi_PT_RT_SB_GPS_Time */




/**
 * Pack the signals of inbound PDU RT_SB_GPS_Time (2047, 0x7ff) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_GPS_Time.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_GPS_Time
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_GPS_Time_2047_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Week. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_GPS_Week << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint32_t s = (uint32_t)pFrameStruct->GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
        s >>= 8;
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal GPS_Week. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->GPS_Week;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_GPS_Time */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Time (2047, 0x7ff) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_GPS_Time_2047_sts, which models frame RT_SB_GPS_Time.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_GPS_Time(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_GPS_Time
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_GPS_Time_2047()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_GPS_Time */



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Time (2047, 0x7ff) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_GPS_Time.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_GPS_Time
                    ( cap_PT_RT_SB_GPS_Time_2047_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_GPS_Time =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_GPS_Week =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Accuracy_GPS_Time =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->GPS_Time =
        (uint32_t)((((((((uint32_t)m[5]) << 8) | m[4]) << 8) | m[3]) << 8) | m[2]);
    pFrameStruct->GPS_Week =
        (uint16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_SB_GPS_Time */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Accel (290, 0x122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Accel_290_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Accel(uint8_t m[])
{
    cap_pack_PT_RT_SB_Accel
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Accel_290()
            );
} /* End of cap_packApi_PT_RT_SB_Accel */




/**
 * Pack the signals of inbound PDU RT_SB_Accel (290, 0x122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Accel.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Accel
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Accel_290_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Accel_Lateral << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Accel_Vertical << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Accel_Lateral;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Accel_Vertical;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Accel */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Accel (290, 0x122) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Accel_290_sts, which models frame RT_SB_Accel.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Accel(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Accel
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Accel_290()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Accel */



/**
 * Unpack the signals of inbound PDU RT_SB_Accel (290, 0x122) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Accel.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Accel
                    ( cap_PT_RT_SB_Accel_290_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Accel_Longitudinal =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Accel_Lateral =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_Accel_Vertical =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_Accel =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Accel_Longitudinal =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->Accel_Lateral =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->Accel_Vertical =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_SB_Accel */



#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from the global interface struct
 * cap_canBus_PT.PT_RT_SB_Gyro_Rates_8388898_sts.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_packApi_PT_RT_SB_Gyro_Rates(uint8_t m[])
{
    cap_pack_PT_RT_SB_Gyro_Rates
            ( &m[0]
            , /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Gyro_Rates_8388898()
            );
} /* End of cap_packApi_PT_RT_SB_Gyro_Rates */




/**
 * Pack the signals of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT
 * into a byte array of 8 Byte.\n
 *   The signal values are read from a frame struct by reference.
 *   @param pFrameStruct
 * The signal values to pack are read from the interface struct * \a pFrameStruct, which
 * models frame RT_SB_Gyro_Rates.
 *   @param m
 * The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void cap_pack_PT_RT_SB_Gyro_Rates
                    ( uint8_t m[]
                    , const cap_PT_RT_SB_Gyro_Rates_8388898_t *pFrameStruct
                    )
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Gyro_Rate_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Gyro_Rate_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x01;
        m[0] |= (uint8_t)(s & 0x01);
    }

    /* Pack signal Validity_Gyro_Rate_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Gyro_Rate_Pitch << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x02;
        m[0] |= (uint8_t)(s & 0x02);
    }

    /* Pack signal Validity_Gyro_Rate_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Validity_Gyro_Rate_Roll << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (uint8_t)~0x04;
        m[0] |= (uint8_t)(s & 0x04);
    }

    /* Pack signal Accuracy_Gyro_Rates. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint8_t s = (uint8_t)pFrameStruct->Accuracy_Gyro_Rates;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (uint8_t)s;
    }

    /* Pack signal Gyro_Rate_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Gyro_Rate_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (uint8_t)s;
        s >>= 8;
        m[3] = (uint8_t)s;
    }

    /* Pack signal Gyro_Rate_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Gyro_Rate_Pitch;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (uint8_t)s;
        s >>= 8;
        m[5] = (uint8_t)s;
    }

    /* Pack signal Gyro_Rate_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        uint16_t s = (uint16_t)pFrameStruct->Gyro_Rate_Roll;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (uint8_t)s;
        s >>= 8;
        m[7] = (uint8_t)s;
    }
} /* End of cap_pack_PT_RT_SB_Gyro_Rates */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT
 * from a byte array of 8 Byte.\n
 *   The unpacked signal values are written into the global interface struct
 * cap_canBus_PT.PT_RT_SB_Gyro_Rates_8388898_sts, which models frame RT_SB_Gyro_Rates.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpackApi_PT_RT_SB_Gyro_Rates(const uint8_t m[])
{
    cap_unpack_PT_RT_SB_Gyro_Rates
            ( /* pFrameStruct */ &cap_getFrame_PT_RT_SB_Gyro_Rates_8388898()
            , &m[0]
            );
} /* End of cap_unpackApi_PT_RT_SB_Gyro_Rates */



/**
 * Unpack the signals of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT
 * from a byte array of 8 Byte.\n
 *   @param pFrameStruct
 * The unpacked signal values are written into the interface struct * \a pFrameStruct,
 * which models frame RT_SB_Gyro_Rates.
 *   @param m
 * The byte array. The signal values are extracted from this array.
 */

void cap_unpack_PT_RT_SB_Gyro_Rates
                    ( cap_PT_RT_SB_Gyro_Rates_8388898_t *pFrameStruct
                    , const uint8_t m[]
                    )
{
    /* Decode all normal, not multiplexed signals. */
    pFrameStruct->Validity_Gyro_Rate_Yaw =
        (boolean_t)((uint8_t)(m[0] & 0x01));
    pFrameStruct->Validity_Gyro_Rate_Pitch =
        (boolean_t)(((uint8_t)(m[0] & 0x02)) >> 1);
    pFrameStruct->Validity_Gyro_Rate_Roll =
        (boolean_t)(((uint8_t)(m[0] & 0x04)) >> 2);
    pFrameStruct->Accuracy_Gyro_Rates =
        (uint8_t)((uint8_t)m[1]);
    pFrameStruct->Gyro_Rate_Yaw =
        (int16_t)((((uint16_t)m[3]) << 8) | m[2]);
    pFrameStruct->Gyro_Rate_Pitch =
        (int16_t)((((uint16_t)m[5]) << 8) | m[4]);
    pFrameStruct->Gyro_Rate_Roll =
        (int16_t)((((uint16_t)m[7]) << 8) | m[6]);

} /* End of cap_unpack_PT_RT_SB_Gyro_Rates */



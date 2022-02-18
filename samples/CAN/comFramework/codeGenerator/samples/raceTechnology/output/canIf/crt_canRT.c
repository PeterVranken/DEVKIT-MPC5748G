/**
 * @file crt_canRT.c
 * Implementation of CAN interface for cluster raceCar.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.6,
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

#include <string.h>
#include <assert.h>

#include "types.h"
#include "crt_canRT.h"


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

/* The global signal variables. These variables form the interface towards the application
   software. They are filled by the unpack functions and the pack functions encode the
   values found in these variables in the PDUs. */
Bool crt_PT_0d7_Validity_INS_Vel_Forwards = 0;
Bool crt_PT_0d7_Validity_INS_Vel_Sideways = 0;
Bool crt_PT_0d7_Bit4 = 0;
Bool crt_PT_0d7_Bit7 = 0;
Bool crt_PT_0d7_Byte2_Bit0 = 0;
Int32 crt_PT_0d7_INS_Vel_Sideways_2D = 0;
UInt8 crt_PT_0d7_Byte4_Bits67 = 0;
UInt8 crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1 = 0;
Int32 crt_PT_0d7_INS_Vel_Forwards_2D_org_m1 = 0;
UInt8 crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2 = 0;
Int32 crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2 = 0;
UInt16 crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3 = 0;
Int16 crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3 = 0;
Bool crt_PT_801024_Validity_Speed = 0;
UInt8 crt_PT_801024_Accuracy_Speed = 0;
UInt8 crt_PT_801024_Direction = 0;
Int32 crt_PT_801024_Speed = 0;
Bool crt_PT_8c0124_Validity_GPS_Time = 0;
Bool crt_PT_8c0124_Validity_GPS_Week = 0;
UInt8 crt_PT_8c0124_Accuracy_GPS_Time = 0;
UInt32 crt_PT_8c0124_GPS_Time = 0;
UInt16 crt_PT_8c0124_GPS_Week = 0;
Int32 crt_PT_8c0324_GPS_Pos_LLH_Longitude = 0;
Int32 crt_PT_8c0324_GPS_Pos_LLH_Altitude = 0;
Bool crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude = 0;
Bool crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude = 0;
Bool crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude = 0;
UInt8 crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude = 0;
UInt8 crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude = 0;
UInt8 crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude = 0;
Int32 crt_PT_8c0224_GPS_Pos_LLH_Latitude = 0;
Bool crt_PT_4d2_Validity_GPS_Speed_2D = 0;
Bool crt_PT_4d2_Validity_GPS_Speed_3D = 0;
UInt8 crt_PT_4d2_Accuracy_GPS_Speed = 0;
UInt32 crt_PT_4d2_GPS_Speed_2D = 0;
UInt32 crt_PT_4d2_GPS_Speed_3D = 0;
Int16 crt_PT_910725_IR_Temperature_7 = 0; /* Signal is not used. */
Int16 crt_PT_980825_IR_Temperature_29 = 0;
Int16 crt_PT_980825_IR_Temperature_30 = 0;
Int16 crt_PT_980825_IR_Temperature_31 = 0;
Int16 crt_PT_980825_IR_Temperature_32 = 0;
Int16 crt_PT_980625_IR_Temperature_21 = 0;
Int16 crt_PT_980625_IR_Temperature_22 = 0;
Int16 crt_PT_980625_IR_Temperature_23 = 0;
Int16 crt_PT_980625_IR_Temperature_24 = 0;
Int16 crt_PT_980425_IR_Temperature_13 = 0;
Int16 crt_PT_980425_IR_Temperature_14 = 0;
Int16 crt_PT_980425_IR_Temperature_15 = 0;
Int16 crt_PT_980425_IR_Temperature_16 = 0;
Int16 crt_PT_980225_IR_Temperature_5 = 0;
Int16 crt_PT_980225_IR_Temperature_6 = 0;
Int16 crt_PT_980225_IR_Temperature_7 = 0;
Int16 crt_PT_980225_IR_Temperature_8 = 0;
Int16 crt_PT_980725_IR_Temperature_25 = 0;
Int16 crt_PT_980725_IR_Temperature_26 = 0;
Int16 crt_PT_980725_IR_Temperature_27 = 0;
Int16 crt_PT_980725_IR_Temperature_28 = 0;
Int16 crt_PT_980525_IR_Temperature_17 = 0;
Int16 crt_PT_980525_IR_Temperature_18 = 0;
Int16 crt_PT_980525_IR_Temperature_19 = 0;
Int16 crt_PT_980525_IR_Temperature_20 = 0;
Int16 crt_PT_980325_IR_Temperature_9 = 0;
Int16 crt_PT_980325_IR_Temperature_10 = 0;
Int16 crt_PT_980325_IR_Temperature_11 = 0;
Int16 crt_PT_980325_IR_Temperature_12 = 0;
Int16 crt_PT_980125_IR_Temperature_1 = 0;
Int16 crt_PT_980125_IR_Temperature_2 = 0;
Int16 crt_PT_980125_IR_Temperature_3 = 0;
Int16 crt_PT_980125_IR_Temperature_4 = 0;
Int16 crt_PT_912025_IR_Temperature_32 = 0;
Int16 crt_PT_911f25_IR_Temperature_31 = 0;
Int16 crt_PT_911e25_IR_Temperature_30 = 0;
Int16 crt_PT_911d25_IR_Temperature_29 = 0;
Int16 crt_PT_911c25_IR_Temperature_28 = 0;
Int16 crt_PT_911b25_IR_Temperature_27 = 0;
Int16 crt_PT_911a25_IR_Temperature_26 = 0;
Int16 crt_PT_911925_IR_Temperature_25 = 0;
Int16 crt_PT_911825_IR_Temperature_24 = 0;
Int16 crt_PT_911625_IR_Temperature_22 = 0;
Int16 crt_PT_911725_IR_Temperature_23 = 0;
Int16 crt_PT_911525_IR_Temperature_21 = 0;
Int16 crt_PT_911425_IR_Temperature_20 = 0;
Int16 crt_PT_911325_IR_Temperature_19 = 0;
Int16 crt_PT_911225_IR_Temperature_18 = 0;
Int16 crt_PT_911025_IR_Temperature_16 = 0;
Int16 crt_PT_910f25_IR_Temperature_15 = 0;
Int16 crt_PT_910e25_IR_Temperature_14 = 0;
Int16 crt_PT_910d25_IR_Temperature_13 = 0;
Int16 crt_PT_910c25_IR_Temperature_12 = 0;
Int16 crt_PT_910b25_IR_Temperature_11 = 0;
Int16 crt_PT_910a25_IR_Temperature_10 = 0;
Int16 crt_PT_910825_IR_Temperature_8 = 0;
Int16 crt_PT_910925_IR_Temperature_9 = 0;
Int16 crt_PT_911125_IR_Temperature_17 = 0;
Int16 crt_PT_910625_IR_Temperature_6 = 0;
Int16 crt_PT_910525_IR_Temperature_5 = 0;
Int16 crt_PT_910425_IR_Temperature_4 = 0;
Int16 crt_PT_910325_IR_Temperature_3 = 0;
Int16 crt_PT_910225_IR_Temperature_2 = 0;
Int16 crt_PT_910125_IR_Temperature_1 = 0;
UInt8 crt_PT_910125_CRC = 0; /* Signal is not used. */
Bool crt_PT_8d0722_Validity_Final_Speed = 0;
UInt32 crt_PT_8d0722_Final_Speed = 0;
Bool crt_PT_31a_Validity_Initial_Speed = 0;
Bool crt_PT_31a_Validity_Initial_Heading = 0;
UInt32 crt_PT_31a_Initial_Speed = 0;
Int16 crt_PT_31a_Initial_Heading = 0;
UInt8 crt_PT_31a_MFDD_Start_Threshold = 0;
UInt8 crt_PT_31a_MFDD_End_Threshold = 0;
UInt32 crt_PT_8d0522_Direct_Distance = 0;
UInt32 crt_PT_8d0522_Path_Distance_2D = 0;
Int32 crt_PT_8d0422_Forward_Distance = 0;
Int32 crt_PT_8d0422_Deviation_Distance = 0;
UInt32 crt_PT_8d0322_Path_Distance_3D = 0;
Bool crt_PT_8d0222_Validity_MFDD = 0;
Bool crt_PT_8d0222_Validity_Average_Accel = 0;
Bool crt_PT_8d0222_Validity_Triggered_Time = 0;
Int16 crt_PT_8d0222_MFDD = 0;
Int16 crt_PT_8d0222_Average_Accel = 0;
UInt32 crt_PT_8d0222_Triggered_Time = 0;
UInt32 crt_PT_960c24_Measured_Time_12 = 0; /* Signal is not used. */
UInt32 crt_PT_960b24_Measured_Time_11 = 0;
UInt32 crt_PT_960a24_Measured_Time_10 = 0;
UInt32 crt_PT_960924_Measured_Time_9 = 0;
UInt32 crt_PT_960824_Measured_Time_8 = 0;
UInt32 crt_PT_960724_Measured_Time_7 = 0;
UInt32 crt_PT_960624_Measured_Time_6 = 0;
UInt32 crt_PT_960524_Measured_Time_5 = 0;
UInt32 crt_PT_960424_Measured_Time_4 = 0;
UInt32 crt_PT_960324_Measured_Time_3 = 0;
UInt32 crt_PT_960224_Measured_Time_2 = 0;
UInt32 crt_PT_960124_Measured_Time_1 = 0;
UInt16 crt_PT_950c24_RPM = 0;
UInt16 crt_PT_950b24_Frequency_4 = 0;
UInt16 crt_PT_950a24_Frequency_3 = 0;
UInt16 crt_PT_950924_Frequency_2 = 0;
UInt16 crt_PT_970324_Misc_3 = 0;
UInt16 crt_PT_970224_Misc_2 = 0;
UInt16 crt_PT_970124_Misc_1 = 0;
UInt16 crt_PT_941f24_AUX_31 = 0;
UInt16 crt_PT_941e24_AUX_30 = 0;
UInt16 crt_PT_941d24_AUX_29 = 0;
UInt16 crt_PT_941c24_AUX_28 = 0;
UInt16 crt_PT_941b24_AUX_27 = 0;
UInt16 crt_PT_941a24_AUX_26 = 0;
UInt16 crt_PT_941924_AUX_25 = 0;
UInt16 crt_PT_941824_AUX_24 = 0;
UInt16 crt_PT_941724_AUX_23 = 0;
UInt16 crt_PT_941624_AUX_22 = 0;
UInt16 crt_PT_941524_AUX_21 = 0;
UInt16 crt_PT_941424_AUX_20 = 0;
UInt16 crt_PT_941324_AUX_19 = 0;
UInt16 crt_PT_941224_AUX_18 = 0;
UInt16 crt_PT_941124_AUX_17 = 0;
UInt16 crt_PT_941024_AUX_16 = 0;
UInt16 crt_PT_940f24_AUX_15 = 0;
UInt16 crt_PT_940e24_AUX_14 = 0;
UInt16 crt_PT_940d24_AUX_13 = 0;
UInt16 crt_PT_940c24_AUX_12 = 0;
UInt16 crt_PT_940b24_AUX_11 = 0;
UInt16 crt_PT_940924_AUX_9 = 0;
UInt16 crt_PT_940a24_AUX_10 = 0;
UInt16 crt_PT_940824_AUX_8 = 0;
UInt16 crt_PT_940724_AUX_7 = 0;
UInt16 crt_PT_940624_AUX_6 = 0;
UInt16 crt_PT_940524_AUX_5 = 0;
UInt16 crt_PT_940424_AUX_4 = 0;
UInt16 crt_PT_940324_AUX_3 = 0;
UInt16 crt_PT_940224_AUX_2 = 0;
UInt16 crt_PT_940124_AUX_1 = 0;
UInt32 crt_PT_900524_Pressure_5 = 0;
UInt32 crt_PT_900424_Pressure_4 = 0;
UInt32 crt_PT_900324_Pressure_3 = 0;
UInt32 crt_PT_900224_Pressure_2 = 0;
UInt32 crt_PT_900124_Pressure_1 = 0;
Int16 crt_PT_920324_Angle_3 = 0;
Int16 crt_PT_920224_Angle_2 = 0;
Int16 crt_PT_920124_Angle_1 = 0;
Int16 crt_PT_911924_Temperature_25 = 0;
Int16 crt_PT_911824_Temperature_24 = 0;
Int16 crt_PT_911724_Temperature_23 = 0;
Int16 crt_PT_911624_Temperature_22 = 0;
Int16 crt_PT_911524_Temperature_21 = 0;
Int16 crt_PT_911424_Temperature_20 = 0;
Int16 crt_PT_911324_Temperature_19 = 0;
Int16 crt_PT_911224_Temperature_18 = 0;
Int16 crt_PT_911124_Temperature_17 = 0;
Int16 crt_PT_911024_Temperature_16 = 0;
Int16 crt_PT_910f24_Temperature_15 = 0;
Int16 crt_PT_910e24_Temperature_14 = 0;
Int16 crt_PT_910d24_Temperature_13 = 0;
Int16 crt_PT_910c24_Temperature_12 = 0;
Int16 crt_PT_910b24_Temperature_11 = 0;
Int16 crt_PT_910a24_Temperature_10 = 0;
Int16 crt_PT_910924_Temperature_9 = 0;
Int16 crt_PT_910824_Temperature_8 = 0;
Int16 crt_PT_910724_Temperature_7 = 0;
Int16 crt_PT_910624_Temperature_6 = 0;
Int16 crt_PT_910524_Temperature_5 = 0;
Int16 crt_PT_910424_Temperature_4 = 0;
Int16 crt_PT_910324_Temperature_3 = 0;
Int16 crt_PT_910224_Temperature_2 = 0;
Int16 crt_PT_910124_Temperature_1 = 0;
UInt16 crt_PT_821f24_Analog_32 = 0;
UInt16 crt_PT_821e24_Analog_31 = 0;
UInt16 crt_PT_821d24_Analog_30 = 0;
UInt16 crt_PT_821c24_Analog_29 = 0;
UInt16 crt_PT_821b24_Analog_28 = 0;
UInt16 crt_PT_821a24_Analog_27 = 0;
UInt16 crt_PT_821924_Analog_26 = 0;
UInt16 crt_PT_821824_Analog_25 = 0;
UInt16 crt_PT_820e24_Analog_15 = 0;
UInt16 crt_PT_820d24_Analog_14 = 0;
UInt16 crt_PT_821024_Analog_17 = 0;
UInt16 crt_PT_821724_Analog_24 = 0;
UInt16 crt_PT_821624_Analog_23 = 0;
UInt16 crt_PT_821524_Analog_22 = 0;
UInt16 crt_PT_821424_Analog_21 = 0;
UInt16 crt_PT_821324_Analog_20 = 0;
UInt16 crt_PT_821224_Analog_19 = 0;
UInt16 crt_PT_820f24_Analog_16 = 0;
UInt16 crt_PT_821124_Analog_18 = 0;
UInt16 crt_PT_820b24_Analog_12 = 0;
UInt16 crt_PT_820a24_Analog_11 = 0;
UInt16 crt_PT_820924_Analog_10 = 0;
UInt16 crt_PT_820824_Analog_9 = 0;
UInt16 crt_PT_820724_Analog_8 = 0;
UInt16 crt_PT_820624_Analog_7 = 0;
UInt16 crt_PT_820524_Analog_6 = 0;
UInt16 crt_PT_820424_Analog_5 = 0;
UInt16 crt_PT_820324_Analog_4 = 0;
UInt16 crt_PT_820224_Analog_3 = 0;
UInt16 crt_PT_820124_Analog_2 = 0;
UInt16 crt_PT_820024_Analog_1 = 0;
Bool crt_PT_800024_Validity_Accel_Longitudinal = 0;
Bool crt_PT_800024_Validity_Accel_Lateral = 0;
Bool crt_PT_800024_Validity_Accel_Vertical = 0;
UInt8 crt_PT_800024_SQC = 0; /* Signal is not used. */
UInt8 crt_PT_800024_Accuracy_Accel = 0;
Int16 crt_PT_800024_Accel_Longitudinal = 0;
Int16 crt_PT_800024_Accel_Lateral = 0;
Int16 crt_PT_800024_Accel_Vertical = 0;
Int32 crt_PT_8f3222_Virtual_4_Vel_NED_D = 0;
Int16 crt_PT_8f3222_Virtual_4_Heading = 0;
Int16 crt_PT_8f3222_Virtual_4_Slip = 0;
Int32 crt_PT_8f3122_Virtual_4_Vel_NED_N = 0;
Int32 crt_PT_8f3122_Virtual_4_Vel_NED_E = 0;
Int16 crt_PT_8f3022_Virtual_4_Offset_X = 0;
Int16 crt_PT_8f3022_Virtual_4_Offset_Y = 0;
Int16 crt_PT_8f3022_Virtual_4_Offset_Z = 0;
Int32 crt_PT_8f2222_Virtual_3_Vel_NED_D = 0;
Int16 crt_PT_8f2222_Virtual_3_Heading = 0;
Int16 crt_PT_8f2222_Virtual_3_Slip = 0;
Int32 crt_PT_8f2122_Virtual_3_Vel_NED_N = 0;
Int32 crt_PT_8f2122_Virtual_3_Vel_NED_E = 0;
Int16 crt_PT_8f2022_Virtual_3_Offset_X = 0;
Int16 crt_PT_8f2022_Virtual_3_Offset_Y = 0;
Int16 crt_PT_8f2022_Virtual_3_Offset_Z = 0;
Int32 crt_PT_8f1222_Virtual_2_Vel_NED_D = 0;
Int16 crt_PT_8f1222_Virtual_2_Heading = 0;
Int16 crt_PT_8f1222_Virtual_2_Slip = 0;
Int32 crt_PT_8f1122_Virtual_2_Vel_NED_N = 0;
Int32 crt_PT_8f1122_Virtual_2_Vel_NED_E = 0;
Int16 crt_PT_8f1022_Virtual_2_Offset_X = 0;
Int16 crt_PT_8f1022_Virtual_2_Offset_Y = 0;
Int16 crt_PT_8f1022_Virtual_2_Offset_Z = 0;
Int32 crt_PT_8f0222_Virtual_1_Vel_NED_D = 0;
Int16 crt_PT_8f0222_Virtual_1_Heading = 0;
Int16 crt_PT_8f0222_Virtual_1_Slip = 0;
Int32 crt_PT_8f0122_Virtual_1_Vel_NED_N = 0;
Int32 crt_PT_8f0122_Virtual_1_Vel_NED_E = 0;
Int16 crt_PT_8f0022_Virtual_1_Offset_X = 0;
Int16 crt_PT_8f0022_Virtual_1_Offset_Y = 0;
Int16 crt_PT_8f0022_Virtual_1_Offset_Z = 0;
Bool crt_PT_8e1622_Validity_INS_Slip = 0;
Bool crt_PT_8e1622_Validity_INS_Squat = 0;
UInt8 crt_PT_8e1622_Accuracy_INS_Slip = 0;
Int16 crt_PT_8e1622_INS_Slip = 0;
UInt8 crt_PT_8e1622_Accuracy_INS_Squat = 0;
Int16 crt_PT_8e1622_INS_Squat = 0;
Bool crt_PT_8e1322_Validity_INS_Vel_ECEF_Y = 0;
Bool crt_PT_8e1322_Validity_INS_Vel_ECEF_Z = 0;
Int32 crt_PT_8e1322_INS_Vel_ECEF_Y = 0;
Int32 crt_PT_8e1322_INS_Vel_ECEF_Z = 0;
Bool crt_PT_8e1222_Validity_INS_Vel_ECEF_X = 0;
UInt8 crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X = 0;
UInt8 crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y = 0;
UInt8 crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z = 0;
Int32 crt_PT_8e1222_INS_Vel_ECEF_X = 0;
Bool crt_PT_8e1122_Validity_INS_Vel_NED_D = 0;
UInt8 crt_PT_8e1122_Accuracy_INS_Vel_D = 0;
Int32 crt_PT_8e1122_INS_Vel_NED_D = 0;
Bool crt_PT_8e1022_Validity_INS_Vel_NED_N = 0;
Bool crt_PT_8e1022_Validity_INS_Vel_NED_E = 0;
UInt8 crt_PT_8e1022_Accuracy_INS_Vel_NE = 0;
Int32 crt_PT_8e1022_INS_Vel_NED_N = 0;
Int32 crt_PT_8e1022_INS_Vel_NED_E = 0;
Int32 crt_PT_8e0522_INS_Pos_ECEF_Y = 0;
Int32 crt_PT_8e0522_INS_Pos_ECEF_Z = 0;
Bool crt_PT_8e0422_Validity_INS_Pos_ECEF_X = 0;
Bool crt_PT_8e0422_Validity_INS_Pos_ECEF_Y = 0;
Bool crt_PT_8e0422_Validity_INS_Pos_ECEF_Z = 0;
UInt8 crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X = 0;
UInt8 crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y = 0;
UInt8 crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z = 0;
Int32 crt_PT_8e0422_INS_Pos_ECEF_X = 0;
Int32 crt_PT_8e0322_INS_Pos_LLH_Longitude = 0;
Int32 crt_PT_8e0322_INS_Pos_LLH_Altitude = 0;
Bool crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude = 0;
Bool crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude = 0;
Bool crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude = 0;
UInt8 crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude = 0;
UInt8 crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude = 0;
UInt8 crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude = 0;
Int32 crt_PT_8e0222_INS_Pos_LLH_Latitude = 0;
Bool crt_PT_8e1522_Validity_INS_Heading = 0;
Bool crt_PT_8e1522_Validity_INS_Gradient = 0;
UInt8 crt_PT_8e1522_Accuracy_INS_Heading = 0;
UInt16 crt_PT_8e1522_INS_Heading_2 = 0;
UInt8 crt_PT_8e1522_Accuracy_INS_Gradient = 0;
Int16 crt_PT_8e1522_INS_Gradient = 0;
Bool crt_PT_8e1422_Validity_INS_Heading = 0;
Bool crt_PT_8e1422_Validity_INS_Gradient = 0;
UInt8 crt_PT_8e1422_Accuracy_INS_Heading = 0;
Int16 crt_PT_8e1422_INS_Heading = 0;
UInt8 crt_PT_8e1422_Accuracy_INS_Gradient = 0;
Int16 crt_PT_8e1422_INS_Gradient = 0;
UInt8 crt_PT_8e0022_INS_Status = 0;
Bool crt_PT_8e0122_Validity_Yaw = 0;
Bool crt_PT_8e0122_Validity_Pitch = 0;
Bool crt_PT_8e0122_Validity_Roll = 0;
UInt8 crt_PT_8e0122_Accuracy_Attitude = 0;
Int16 crt_PT_8e0122_Attitude_Yaw = 0;
Int16 crt_PT_8e0122_Attitude_Pitch = 0;
Int16 crt_PT_8e0122_Attitude_Roll = 0;
Bool crt_PT_8d0122_Validity_Status_Timestamp = 0;
Bool crt_PT_8d0122_Status_Analogue_1 = 0;
Bool crt_PT_8d0122_Status_Analogue_2 = 0;
Bool crt_PT_8d0122_Status_Analogue_3 = 0;
Bool crt_PT_8d0122_Status_Analogue_4 = 0;
Bool crt_PT_8d0122_Status_Pulse_Output = 0;
Bool crt_PT_8d0122_Status_Serial_Output_1 = 0;
Bool crt_PT_8d0122_Status_Serial_Output_2 = 0;
Bool crt_PT_8d0122_Status_Trigger = 0;
UInt32 crt_PT_8d0122_GPS_Time = 0;
Bool crt_PT_8c1622_Validity_GPS_Heading = 0;
Bool crt_PT_8c1622_Validity_GPS_Gradient = 0;
UInt8 crt_PT_8c1622_Accuracy_GPS_Heading = 0;
UInt16 crt_PT_8c1622_GPS_Heading_2 = 0;
UInt8 crt_PT_8c1622_Accuracy_GPS_Gradient = 0;
Int16 crt_PT_8c1622_GPS_Gradient = 0;
Bool crt_PT_802122_Validity_Cumulative_Time = 0;
Bool crt_PT_802122_Validity_Cumulative_Distance = 0;
UInt32 crt_PT_802122_Cumulative_Time = 0;
UInt32 crt_PT_802122_Cumulative_Distance = 0;
Bool crt_PT_802022_Validity_Cumulative_Time = 0;
Bool crt_PT_802022_Validity_Cumulative_Distance = 0;
UInt32 crt_PT_802022_Cumulative_Time = 0;
UInt32 crt_PT_802022_Cumulative_Distance = 0;
Bool crt_PT_8d0022_Validity_Trigger_Timestamp = 0;
UInt8 crt_PT_8d0022_Accuracy_Trigger_Timestamp = 0;
UInt8 crt_PT_8d0022_Trigger_Number = 0;
Bool crt_PT_8d0022_Trigger_Timestamp_Type = 0;
UInt64 crt_PT_8d0022_GPS_High_Resolution_Time = 0;
Bool crt_PT_800121_Validity_Gyro_Rate_Yaw = 0;
Bool crt_PT_800121_Validity_Gyro_Rate_Pitch = 0;
Bool crt_PT_800121_Validity_Gyro_Rate_Roll = 0;
UInt8 crt_PT_800121_Accuracy_Gyro_Rates = 0;
Int16 crt_PT_800121_Gyro_Rate_Yaw = 0;
Int16 crt_PT_800121_Gyro_Rate_Pitch = 0;
Int16 crt_PT_800121_Gyro_Rate_Roll = 0;
Bool crt_PT_800021_Validity_Accel_Longitudinal = 0;
Bool crt_PT_800021_Validity_Accel_Lateral = 0;
Bool crt_PT_800021_Validity_Accel_Vertical = 0;
UInt8 crt_PT_800021_Accuracy_Accel = 0;
Int16 crt_PT_800021_Accel_Longitudinal = 0;
Int16 crt_PT_800021_Accel_Lateral = 0;
Int16 crt_PT_800021_Accel_Vertical = 0;
Bool crt_PT_801022_Validity_Speed = 0;
UInt8 crt_PT_801022_Accuracy_Speed = 0;
Int32 crt_PT_801022_Speed = 0;
Bool crt_PT_8c2122_Validity_RTK_Slip = 0;
Bool crt_PT_8c2122_Validity_RTK_Squat = 0;
Bool crt_PT_8c2122_Validity_RTK_Baseline = 0;
UInt8 crt_PT_8c2122_Accuracy_RTK_Baseline = 0;
Int16 crt_PT_8c2122_RTK_Slip = 0;
Int16 crt_PT_8c2122_RTK_Squat = 0;
UInt16 crt_PT_8c2122_RTK_Baseline = 0;
Bool crt_PT_8c2022_Validity_RTK_Yaw = 0;
Bool crt_PT_8c2022_Validity_RTK_Pitch = 0;
Bool crt_PT_8c2022_Validity_RTK_Roll = 0;
UInt8 crt_PT_8c2022_Accuracy_RTK_Attitude = 0;
Int16 crt_PT_8c2022_RTK_Attitude_Yaw = 0;
Int16 crt_PT_8c2022_RTK_Attitude_Pitch = 0;
Int16 crt_PT_8c2022_RTK_Attitude_Roll = 0;
Bool crt_PT_8c3022_Validity_GPS_Lateral_Accel = 0;
Bool crt_PT_8c3022_Validity_GPS_Mcycle_Lean = 0;
UInt8 crt_PT_8c3022_Accuracy_GPS_Lateral_Accel = 0;
Int16 crt_PT_8c3022_GPS_Lateral_Accel = 0;
Int16 crt_PT_8c3022_GPS_Mcycle_Lean_Angle = 0;
UInt8 crt_PT_8c0022_GPS_Status = 0;
UInt8 crt_PT_8c0022_Firmware_Version_Major = 0;
UInt8 crt_PT_8c0022_Firmware_Version_Intermediate = 0;
UInt8 crt_PT_8c0022_Firmware_Version_Minor = 0;
UInt8 crt_PT_8c0022_GPS_nSv = 0;
UInt8 crt_PT_8c0022_GPS_nSv_2 = 0;
UInt8 crt_PT_8c0022_GPS_nSv_RTK = 0;
UInt8 crt_PT_8c0022_RTK_Status = 0;
Int32 crt_PT_8c0522_GPS_Pos_ECEF_Y = 0;
Int32 crt_PT_8c0522_GPS_Pos_ECEF_Z = 0;
Bool crt_PT_8c0422_Validity_GPS_Pos_ECEF_X = 0;
Bool crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y = 0;
Bool crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z = 0;
UInt8 crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X = 0;
UInt8 crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y = 0;
UInt8 crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z = 0;
Int32 crt_PT_8c0422_GPS_Pos_ECEF_X = 0;
Int32 crt_PT_8c0322_GPS_Pos_LLH_Longitude = 0;
Int32 crt_PT_8c0322_GPS_Pos_LLH_Altitude = 0;
Bool crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude = 0;
Bool crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude = 0;
Bool crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude = 0;
UInt8 crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude = 0;
UInt8 crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude = 0;
UInt8 crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude = 0;
Int32 crt_PT_8c0222_GPS_Pos_LLH_Latitude = 0;
Bool crt_PT_8c1522_Validity_GPS_Heading = 0;
Bool crt_PT_8c1522_Validity_GPS_Gradient = 0;
UInt8 crt_PT_8c1522_Accuracy_GPS_Heading = 0;
Int16 crt_PT_8c1522_GPS_Heading = 0;
UInt8 crt_PT_8c1522_Accuracy_GPS_Gradient = 0;
Int16 crt_PT_8c1522_GPS_Gradient = 0;
Bool crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y = 0;
Bool crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z = 0;
Int32 crt_PT_8c1422_GPS_Vel_ECEF_Y = 0;
Int32 crt_PT_8c1422_GPS_Vel_ECEF_Z = 0;
Bool crt_PT_8c1322_Validity_GPS_Vel_ECEF_X = 0;
UInt8 crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X = 0;
UInt8 crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y = 0;
UInt8 crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z = 0;
Int32 crt_PT_8c1322_GPS_Vel_ECEF_X = 0;
Bool crt_PT_000_Validity_GPS_Vel_NED_D = 0;
UInt8 crt_PT_000_Accuracy_GPS_Vel_D = 0;
Int32 crt_PT_000_GPS_Vel_NED_D = 0;
Bool crt_PT_1fffffff_Validity_GPS_Vel_NED_N = 0;
Bool crt_PT_1fffffff_Validity_GPS_Vel_NED_E = 0;
UInt8 crt_PT_1fffffff_Accuracy_GPS_Vel_NE = 0;
Int32 crt_PT_1fffffff_GPS_Vel_NED_N = 0;
Int32 crt_PT_1fffffff_GPS_Vel_NED_E = 0;
Bool crt_PT_71a_Validity_GPS_Speed_2D = 0;
Bool crt_PT_71a_Validity_GPS_Speed_3D = 0;
UInt8 crt_PT_71a_Accuracy_GPS_Speed = 0;
UInt32 crt_PT_71a_GPS_Speed_2D = 0;
UInt32 crt_PT_71a_GPS_Speed_3D = 0;
Bool crt_PT_7ff_Validity_GPS_Time = 0;
Bool crt_PT_7ff_Validity_GPS_Week = 0;
UInt8 crt_PT_7ff_Accuracy_GPS_Time = 0;
UInt32 crt_PT_7ff_GPS_Time = 0;
UInt16 crt_PT_7ff_GPS_Week = 0;
Bool crt_PT_122_Validity_Accel_Longitudinal = 0;
Bool crt_PT_122_Validity_Accel_Lateral = 0;
Bool crt_PT_122_Validity_Accel_Vertical = 0;
UInt8 crt_PT_122_Accuracy_Accel = 0;
Int16 crt_PT_122_Accel_Longitudinal = 0;
Int16 crt_PT_122_Accel_Lateral = 0;
Int16 crt_PT_122_Accel_Vertical = 0;
Bool crt_PT_800122_Validity_Gyro_Rate_Yaw = 0;
Bool crt_PT_800122_Validity_Gyro_Rate_Pitch = 0;
Bool crt_PT_800122_Validity_Gyro_Rate_Roll = 0;
UInt8 crt_PT_800122_Accuracy_Gyro_Rates = 0;
Int16 crt_PT_800122_Gyro_Rate_Yaw = 0;
Int16 crt_PT_800122_Gyro_Rate_Pitch = 0;
Int16 crt_PT_800122_Gyro_Rate_Roll = 0;
 

/*
 * Function implementation
 */




#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vel_Body_Axes (bus PT, frame ID 215) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vel_Body_Axes_0d7(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Validity_INS_Vel_Forwards. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_0d7_Validity_INS_Vel_Forwards;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_INS_Vel_Sideways. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_0d7_Validity_INS_Vel_Sideways << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Bit4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_0d7_Bit4 << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x10;
        m[0] |= (UInt8)(s & 0x10);
    }

    /* Pack signal Bit7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_0d7_Bit7 << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x80;
        m[0] |= (UInt8)(s & 0x80);
    }

    /* Pack signal Byte2_Bit0. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_0d7_Byte2_Bit0;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (UInt8)~0x01;
        m[2] |= (UInt8)(s & 0x01);
    }

    /* Pack signal INS_Vel_Sideways_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_0d7_INS_Vel_Sideways_2D << (9-9);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] &= (UInt8)~0x7f;
        m[7] |= (UInt8)(s & 0x7f);
    }

    /* Pack signal Byte4_Bits67. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_0d7_Byte4_Bits67 << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] &= (UInt8)~0xc0;
        m[4] |= (UInt8)(s & 0xc0);
    }

    /* Pack the selected set of multiplexed signals. */
    switch(crt_PT_0d7_Byte4_Bits67)
    {
    case 1:
        /* Pack signal Accuracy_INS_Vel_Body_org. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            UInt8 s = (UInt8)crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1;

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[1] = (UInt8)s;
        }

        /* Pack signal INS_Vel_Forwards_2D_org. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            UInt32 s = (UInt32)crt_PT_0d7_INS_Vel_Forwards_2D_org_m1 << (11-10);

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[2] &= (UInt8)~0xfe;
            m[2] |= (UInt8)(s & 0xfe);
            s >>= 8;
            m[3] = (UInt8)s;
            s >>= 8;
            m[4] &= (UInt8)~0x3f;
            m[4] |= (UInt8)(s & 0x3f);
        }

        break;
    case 2:
        /* Pack signal Accuracy_INS_Vel_Body_no2. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            UInt8 s = (UInt8)crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2;

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[1] = (UInt8)s;
        }

        /* Pack signal INS_Vel_Forwards_2D_no2. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            UInt32 s = (UInt32)crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2 << (11-10);

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[2] &= (UInt8)~0xfe;
            m[2] |= (UInt8)(s & 0xfe);
            s >>= 8;
            m[3] = (UInt8)s;
            s >>= 8;
            m[4] &= (UInt8)~0x3f;
            m[4] |= (UInt8)(s & 0x3f);
        }

        break;
    case 3:
        /* Pack signal Accuracy_INS_Vel_Body_no3. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            UInt16 s = (UInt16)crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3 << 1;

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[2] &= (UInt8)~0xfe;
            m[2] |= (UInt8)(s & 0xfe);
            s >>= 8;
            m[1] = (UInt8)s;
        }

        /* Pack signal INS_Vel_Forwards_2D_no3. */
        {
            /* Assign the signal value to a temporary variable, where the signal value's bits
               have the same byte-relative position as in the final, packed PDU. */
            UInt16 s = (UInt16)crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3 << (2-2);

            /* Transfer all bytes of the temporary variable into the PDU. */
            m[3] = (UInt8)s;
            s >>= 8;
            m[4] &= (UInt8)~0x3f;
            m[4] |= (UInt8)(s & 0x3f);
        }

        break;

    default: assert(1==0); // Undefined mux selector value encountered
    }
} /* End of crt_pack_PT_RT_SB_INS_Vel_Body_Axes_0d7 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vel_Body_Axes (bus PT, frame ID 215) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vel_Body_Axes_0d7(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_0d7_Validity_INS_Vel_Forwards = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_0d7_Validity_INS_Vel_Sideways = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_0d7_Bit4 = (Bool)(((UInt8)(m[0] & 0x10)) >> 4);
    crt_PT_0d7_Bit7 = (Bool)(((UInt8)(m[0] & 0x80)) >> 7);
    crt_PT_0d7_Byte2_Bit0 = (Bool)((UInt8)(m[2] & 0x01));
    crt_PT_0d7_INS_Vel_Sideways_2D = (Int32)((Int32)(((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 9) >> 9);

    /* Decode the multiplex selector signal. */
    crt_PT_0d7_Byte4_Bits67 = (UInt8)(((UInt8)(m[4] & 0xc0)) >> 6);

    /* Decode the selected set of multiplexed signals. */
    switch(crt_PT_0d7_Byte4_Bits67)
    {
    case 1:
        crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1 = (UInt8)((UInt8)m[1]);
        crt_PT_0d7_INS_Vel_Forwards_2D_org_m1 = (Int32)((Int32)(((((((UInt32)m[4]) << 8) | m[3]) << 8) | m[2]) << 10) >> 11);

        break;
    case 2:
        crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2 = (UInt8)((UInt8)m[1]);
        crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2 = (Int32)((Int32)(((((((UInt32)m[4]) << 8) | m[3]) << 8) | m[2]) << 10) >> 11);

        break;
    case 3:
        crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3 = (UInt16)(((((UInt16)m[1]) << 8) | m[2]) >> 1);
        crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3 = (Int16)((Int16)(((((UInt16)m[4]) << 8) | m[3]) << 2) >> 2);

        break;

    default: assert(1==0); // Undefined mux selector value encountered
    }
} /* End of crt_unpack_PT_RT_SB_INS_Vel_Body_Axes_0d7 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Speed (bus PT, frame ID 8392740) into a
 * byte array of 7 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Speed_801024(UInt8 m[])
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
        UInt8 s = (UInt8)crt_PT_801024_Validity_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Accuracy_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_801024_Accuracy_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Direction. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_801024_Direction;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (UInt8)~0x03;
        m[2] |= (UInt8)(s & 0x03);
    }

    /* Pack signal Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt64 s = (UInt64)crt_PT_801024_Speed << (32-30);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (UInt8)~0xfc;
        m[2] |= (UInt8)(s & 0xfc);
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] &= (UInt8)~0x03;
        m[6] |= (UInt8)(s & 0x03);
    }
} /* End of crt_pack_PT_RT_DL1MK3_Speed_801024 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Speed (bus PT, frame ID 8392740) from
 * a byte array of 7 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Speed_801024(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_801024_Validity_Speed = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_801024_Accuracy_Speed = (UInt8)((UInt8)m[1]);
    crt_PT_801024_Direction = (UInt8)((UInt8)(m[2] & 0x03));
    crt_PT_801024_Speed = (Int32)((Int64)(((((((((((UInt64)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) | m[3]) << 8) | m[2]) << 30) >> 32);

} /* End of crt_unpack_PT_RT_DL1MK3_Speed_801024 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Time (bus PT, frame ID 9175332) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_GPS_Time_8c0124(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0124_Validity_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Week. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0124_Validity_GPS_Week << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0124_Accuracy_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0124_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal GPS_Week. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c0124_GPS_Week;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_GPS_Time_8c0124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Time (bus PT, frame ID 9175332) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_GPS_Time_8c0124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c0124_Validity_GPS_Time = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c0124_Validity_GPS_Week = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c0124_Accuracy_GPS_Time = (UInt8)((UInt8)m[1]);
    crt_PT_8c0124_GPS_Time = (UInt32)((((((((UInt32)m[5]) << 8) | m[4]) << 8) | m[3]) << 8) | m[2]);
    crt_PT_8c0124_GPS_Week = (UInt16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_DL1MK3_GPS_Time_8c0124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (bus PT, frame ID 9175844) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_GPS_Pos_LLH_2_8c0324(UInt8 m[])
{

    /* Pack signal GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0324_GPS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0324_GPS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_GPS_Pos_LLH_2_8c0324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (bus PT, frame ID 9175844) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_2_8c0324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c0324_GPS_Pos_LLH_Longitude = (Int32)((((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    crt_PT_8c0324_GPS_Pos_LLH_Altitude = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_2_8c0324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (bus PT, frame ID 9175588) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_GPS_Pos_LLH_1_8c0224(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0224_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_GPS_Pos_LLH_1_8c0224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (bus PT, frame ID 9175588) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_1_8c0224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude = (UInt8)((UInt8)m[1]);
    crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude = (UInt8)((UInt8)m[2]);
    crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude = (UInt8)((UInt8)m[3]);
    crt_PT_8c0224_GPS_Pos_LLH_Latitude = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_1_8c0224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_GPS_Speed (bus PT, frame ID 1234) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_GPS_Speed_4d2(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Speed_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_4d2_Validity_GPS_Speed_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Speed_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_4d2_Validity_GPS_Speed_3D << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_4d2_Accuracy_GPS_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal GPS_Speed_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_4d2_GPS_Speed_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
    }

    /* Pack signal GPS_Speed_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_4d2_GPS_Speed_3D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_GPS_Speed_4d2 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_GPS_Speed (bus PT, frame ID 1234) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_GPS_Speed_4d2(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_4d2_Validity_GPS_Speed_2D = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_4d2_Validity_GPS_Speed_3D = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_4d2_Accuracy_GPS_Speed = (UInt8)((UInt8)m[1]);
    crt_PT_4d2_GPS_Speed_2D = (UInt32)((((((UInt32)m[4]) << 8) | m[3]) << 8) | m[2]);
    crt_PT_4d2_GPS_Speed_3D = (UInt32)((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]);

} /* End of crt_unpack_PT_RT_DL1MK3_GPS_Speed_4d2 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of unused PDU RT_IRTemp_Temp_7 (bus PT, frame ID 9504549) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_7_910725(UInt8 m[])
{

    /* Pack signal IR_Temperature_7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910725_IR_Temperature_7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_7_910725 */
#endif



#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of unused PDU RT_IRTemp_Temp_7 (bus PT, frame ID 9504549) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_7_910725(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
} /* End of crt_unpack_PT_RT_IRTemp_Temp_7_910725 */
#endif



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_RR_2 (bus PT, frame ID 9963557) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_RR_2_980825(UInt8 m[])
{

    /* Pack signal IR_Temperature_29. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980825_IR_Temperature_29;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_30. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980825_IR_Temperature_30;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_31. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980825_IR_Temperature_31;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_32. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980825_IR_Temperature_32;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_RR_2_980825 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_RR_2 (bus PT, frame ID 9963557) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_RR_2_980825(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_980825_IR_Temperature_29 = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_980825_IR_Temperature_30 = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_980825_IR_Temperature_31 = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_980825_IR_Temperature_32 = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_RR_2_980825 */


/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_RL_2 (bus PT, frame ID 9963045) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_RL_2_980625(UInt8 m[])
{

    /* Pack signal IR_Temperature_21. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980625_IR_Temperature_21;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_22. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980625_IR_Temperature_22;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_23. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980625_IR_Temperature_23;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_24. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980625_IR_Temperature_24;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_RL_2_980625 */


#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_RL_2 (bus PT, frame ID 9963045) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_RL_2_980625(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_980625_IR_Temperature_21 = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_980625_IR_Temperature_22 = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_980625_IR_Temperature_23 = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_980625_IR_Temperature_24 = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_RL_2_980625 */
#endif


/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_FR_2 (bus PT, frame ID 9962533) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_FR_2_980425(UInt8 m[])
{

    /* Pack signal IR_Temperature_13. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980425_IR_Temperature_13;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_14. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980425_IR_Temperature_14;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_15. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980425_IR_Temperature_15;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_16. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980425_IR_Temperature_16;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_FR_2_980425 */


#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_FR_2 (bus PT, frame ID 9962533) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_FR_2_980425(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_980425_IR_Temperature_13 = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_980425_IR_Temperature_14 = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_980425_IR_Temperature_15 = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_980425_IR_Temperature_16 = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_FR_2_980425 */
#endif



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_FL_2 (bus PT, frame ID 9962021) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_FL_2_980225(UInt8 m[])
{

    /* Pack signal IR_Temperature_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980225_IR_Temperature_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_6. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980225_IR_Temperature_6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980225_IR_Temperature_7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_8. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980225_IR_Temperature_8;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_FL_2_980225 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_2 (bus PT, frame ID 9962021) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_FL_2_980225(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_980225_IR_Temperature_5 = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_980225_IR_Temperature_6 = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_980225_IR_Temperature_7 = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_980225_IR_Temperature_8 = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_FL_2_980225 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_RR_1 (bus PT, frame ID 9963301) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_RR_1_980725(UInt8 m[])
{

    /* Pack signal IR_Temperature_25. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980725_IR_Temperature_25;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_26. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980725_IR_Temperature_26;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_27. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980725_IR_Temperature_27;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_28. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980725_IR_Temperature_28;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_RR_1_980725 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_RR_1 (bus PT, frame ID 9963301) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_RR_1_980725(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_980725_IR_Temperature_25 = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_980725_IR_Temperature_26 = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_980725_IR_Temperature_27 = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_980725_IR_Temperature_28 = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_RR_1_980725 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_RL_1 (bus PT, frame ID 9962789) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_RL_1_980525(UInt8 m[])
{

    /* Pack signal IR_Temperature_17. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980525_IR_Temperature_17;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_18. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980525_IR_Temperature_18;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_19. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980525_IR_Temperature_19;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_20. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980525_IR_Temperature_20;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_RL_1_980525 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_RL_1 (bus PT, frame ID 9962789) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_RL_1_980525(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_980525_IR_Temperature_17 = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_980525_IR_Temperature_18 = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_980525_IR_Temperature_19 = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_980525_IR_Temperature_20 = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_RL_1_980525 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_FR_1 (bus PT, frame ID 9962277) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_FR_1_980325(UInt8 m[])
{

    /* Pack signal IR_Temperature_9. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980325_IR_Temperature_9;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_10. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980325_IR_Temperature_10;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_11. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980325_IR_Temperature_11;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_12. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980325_IR_Temperature_12;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_FR_1_980325 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_FR_1 (bus PT, frame ID 9962277) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_FR_1_980325(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_980325_IR_Temperature_9 = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_980325_IR_Temperature_10 = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_980325_IR_Temperature_11 = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_980325_IR_Temperature_12 = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_FR_1_980325 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_FL_1 (bus PT, frame ID 9961765) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_FL_1_980125(UInt8 m[])
{

    /* Pack signal IR_Temperature_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980125_IR_Temperature_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980125_IR_Temperature_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980125_IR_Temperature_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal IR_Temperature_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_980125_IR_Temperature_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_FL_1_980125 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_1 (bus PT, frame ID 9961765) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_FL_1_980125(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_980125_IR_Temperature_1 = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_980125_IR_Temperature_2 = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_980125_IR_Temperature_3 = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_980125_IR_Temperature_4 = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_FL_1_980125 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_32 (bus PT, frame ID 9510949) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_32_912025(UInt8 m[])
{

    /* Pack signal IR_Temperature_32. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_912025_IR_Temperature_32;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_32_912025 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_32 (bus PT, frame ID 9510949) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_32_912025(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_912025_IR_Temperature_32 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_32_912025 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_31 (bus PT, frame ID 9510693) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_31_911f25(UInt8 m[])
{

    /* Pack signal IR_Temperature_31. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911f25_IR_Temperature_31;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_31_911f25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_31 (bus PT, frame ID 9510693) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_31_911f25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911f25_IR_Temperature_31 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_31_911f25 */


/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_30 (bus PT, frame ID 9510437) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_30_911e25(UInt8 m[])
{

    /* Pack signal IR_Temperature_30. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911e25_IR_Temperature_30;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_30_911e25 */


#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_30 (bus PT, frame ID 9510437) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_30_911e25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911e25_IR_Temperature_30 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_30_911e25 */
#endif



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_29 (bus PT, frame ID 9510181) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_29_911d25(UInt8 m[])
{

    /* Pack signal IR_Temperature_29. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911d25_IR_Temperature_29;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_29_911d25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_29 (bus PT, frame ID 9510181) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_29_911d25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911d25_IR_Temperature_29 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_29_911d25 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_28 (bus PT, frame ID 9509925) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_28_911c25(UInt8 m[])
{

    /* Pack signal IR_Temperature_28. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911c25_IR_Temperature_28;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_28_911c25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_28 (bus PT, frame ID 9509925) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_28_911c25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911c25_IR_Temperature_28 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_28_911c25 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_27 (bus PT, frame ID 9509669) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_27_911b25(UInt8 m[])
{

    /* Pack signal IR_Temperature_27. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911b25_IR_Temperature_27;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_27_911b25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_27 (bus PT, frame ID 9509669) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_27_911b25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911b25_IR_Temperature_27 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_27_911b25 */


/**
 * Pack the signals of outbound PDU RT_IRTemp_Temp_26 (bus PT, frame ID 9509413) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_26_911a25(UInt8 m[])
{

    /* Pack signal IR_Temperature_26. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911a25_IR_Temperature_26;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_26_911a25 */


#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_IRTemp_Temp_26 (bus PT, frame ID 9509413) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_26_911a25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911a25_IR_Temperature_26 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_26_911a25 */
#endif



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_25 (bus PT, frame ID 9509157) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_25_911925(UInt8 m[])
{

    /* Pack signal IR_Temperature_25. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911925_IR_Temperature_25;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_25_911925 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_25 (bus PT, frame ID 9509157) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_25_911925(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911925_IR_Temperature_25 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_25_911925 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_24 (bus PT, frame ID 9508901) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_24_911825(UInt8 m[])
{

    /* Pack signal IR_Temperature_24. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911825_IR_Temperature_24;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_24_911825 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_24 (bus PT, frame ID 9508901) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_24_911825(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911825_IR_Temperature_24 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_24_911825 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_22 (bus PT, frame ID 9508389) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_22_911625(UInt8 m[])
{

    /* Pack signal IR_Temperature_22. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911625_IR_Temperature_22;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_22_911625 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_22 (bus PT, frame ID 9508389) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_22_911625(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911625_IR_Temperature_22 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_22_911625 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_23 (bus PT, frame ID 9508645) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_23_911725(UInt8 m[])
{

    /* Pack signal IR_Temperature_23. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911725_IR_Temperature_23;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_23_911725 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_23 (bus PT, frame ID 9508645) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_23_911725(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911725_IR_Temperature_23 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_23_911725 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_21 (bus PT, frame ID 9508133) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_21_911525(UInt8 m[])
{

    /* Pack signal IR_Temperature_21. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911525_IR_Temperature_21;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_21_911525 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_21 (bus PT, frame ID 9508133) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_21_911525(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911525_IR_Temperature_21 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_21_911525 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_20 (bus PT, frame ID 9507877) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_20_911425(UInt8 m[])
{

    /* Pack signal IR_Temperature_20. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911425_IR_Temperature_20;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_20_911425 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_20 (bus PT, frame ID 9507877) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_20_911425(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911425_IR_Temperature_20 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_20_911425 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_19 (bus PT, frame ID 9507621) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_19_911325(UInt8 m[])
{

    /* Pack signal IR_Temperature_19. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911325_IR_Temperature_19;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_19_911325 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_19 (bus PT, frame ID 9507621) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_19_911325(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911325_IR_Temperature_19 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_19_911325 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_18 (bus PT, frame ID 9507365) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_18_911225(UInt8 m[])
{

    /* Pack signal IR_Temperature_18. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911225_IR_Temperature_18;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_18_911225 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_18 (bus PT, frame ID 9507365) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_18_911225(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911225_IR_Temperature_18 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_18_911225 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_16 (bus PT, frame ID 9506853) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_16_911025(UInt8 m[])
{

    /* Pack signal IR_Temperature_16. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911025_IR_Temperature_16;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_16_911025 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_16 (bus PT, frame ID 9506853) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_16_911025(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911025_IR_Temperature_16 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_16_911025 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_15 (bus PT, frame ID 9506597) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_15_910f25(UInt8 m[])
{

    /* Pack signal IR_Temperature_15. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910f25_IR_Temperature_15;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_15_910f25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_15 (bus PT, frame ID 9506597) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_15_910f25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910f25_IR_Temperature_15 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_15_910f25 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_14 (bus PT, frame ID 9506341) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_14_910e25(UInt8 m[])
{

    /* Pack signal IR_Temperature_14. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910e25_IR_Temperature_14;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_14_910e25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_14 (bus PT, frame ID 9506341) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_14_910e25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910e25_IR_Temperature_14 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_14_910e25 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_13 (bus PT, frame ID 9506085) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_13_910d25(UInt8 m[])
{

    /* Pack signal IR_Temperature_13. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910d25_IR_Temperature_13;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_13_910d25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_13 (bus PT, frame ID 9506085) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_13_910d25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910d25_IR_Temperature_13 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_13_910d25 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_12 (bus PT, frame ID 9505829) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_12_910c25(UInt8 m[])
{

    /* Pack signal IR_Temperature_12. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910c25_IR_Temperature_12;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_12_910c25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_12 (bus PT, frame ID 9505829) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_12_910c25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910c25_IR_Temperature_12 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_12_910c25 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_11 (bus PT, frame ID 9505573) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_11_910b25(UInt8 m[])
{

    /* Pack signal IR_Temperature_11. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910b25_IR_Temperature_11;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_11_910b25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_11 (bus PT, frame ID 9505573) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_11_910b25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910b25_IR_Temperature_11 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_11_910b25 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_10 (bus PT, frame ID 9505317) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_10_910a25(UInt8 m[])
{

    /* Pack signal IR_Temperature_10. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910a25_IR_Temperature_10;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_10_910a25 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_10 (bus PT, frame ID 9505317) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_10_910a25(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910a25_IR_Temperature_10 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_10_910a25 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_8 (bus PT, frame ID 9504805) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_8_910825(UInt8 m[])
{

    /* Pack signal IR_Temperature_8. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910825_IR_Temperature_8;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_8_910825 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_8 (bus PT, frame ID 9504805) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_8_910825(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910825_IR_Temperature_8 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_8_910825 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_9 (bus PT, frame ID 9505061) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_9_910925(UInt8 m[])
{

    /* Pack signal IR_Temperature_9. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910925_IR_Temperature_9;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_9_910925 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_9 (bus PT, frame ID 9505061) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_9_910925(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910925_IR_Temperature_9 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_9_910925 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_17 (bus PT, frame ID 9507109) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_17_911125(UInt8 m[])
{

    /* Pack signal IR_Temperature_17. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911125_IR_Temperature_17;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_17_911125 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_17 (bus PT, frame ID 9507109) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_17_911125(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911125_IR_Temperature_17 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_17_911125 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_6 (bus PT, frame ID 9504293) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_6_910625(UInt8 m[])
{

    /* Pack signal IR_Temperature_6. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910625_IR_Temperature_6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_6_910625 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_6 (bus PT, frame ID 9504293) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_6_910625(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910625_IR_Temperature_6 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_6_910625 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_5 (bus PT, frame ID 9504037) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_5_910525(UInt8 m[])
{

    /* Pack signal IR_Temperature_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910525_IR_Temperature_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_5_910525 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_5 (bus PT, frame ID 9504037) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_5_910525(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910525_IR_Temperature_5 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_5_910525 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_4 (bus PT, frame ID 9503781) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_4_910425(UInt8 m[])
{

    /* Pack signal IR_Temperature_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910425_IR_Temperature_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_4_910425 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_4 (bus PT, frame ID 9503781) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_4_910425(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910425_IR_Temperature_4 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_4_910425 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_3 (bus PT, frame ID 9503525) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_3_910325(UInt8 m[])
{

    /* Pack signal IR_Temperature_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910325_IR_Temperature_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_3_910325 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_3 (bus PT, frame ID 9503525) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_3_910325(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910325_IR_Temperature_3 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_3_910325 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_2 (bus PT, frame ID 9503269) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_2_910225(UInt8 m[])
{

    /* Pack signal IR_Temperature_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910225_IR_Temperature_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_2_910225 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_2 (bus PT, frame ID 9503269) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_2_910225(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910225_IR_Temperature_2 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_2_910225 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IRTemp_Temp_1 (bus PT, frame ID 9503013) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IRTemp_Temp_1_910125(UInt8 m[])
{

    /* Pack signal IR_Temperature_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910125_IR_Temperature_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal CRC. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_910125_CRC;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IRTemp_Temp_1_910125 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IRTemp_Temp_1 (bus PT, frame ID 9503013) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IRTemp_Temp_1_910125(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910125_IR_Temperature_1 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_IRTemp_Temp_1_910125 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trig_Final_Condition (bus PT, frame ID 9242402) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Trig_Final_Condition_8d0722(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Validity_Final_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0722_Validity_Final_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Final_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8d0722_Final_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Trig_Final_Condition_8d0722 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Final_Condition (bus PT, frame ID 9242402) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Trig_Final_Condition_8d0722(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8d0722_Validity_Final_Speed = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8d0722_Final_Speed = (UInt32)((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_SB_Trig_Final_Condition_8d0722 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trig_Initial_Condition (bus PT, frame ID 794) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Trig_Initial_Condition_31a(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Initial_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_31a_Validity_Initial_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Initial_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_31a_Validity_Initial_Heading << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Initial_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_31a_Initial_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Initial_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_31a_Initial_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal MFDD_Start_Threshold. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_31a_MFDD_Start_Threshold;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
    }

    /* Pack signal MFDD_End_Threshold. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_31a_MFDD_End_Threshold;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Trig_Initial_Condition_31a */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Initial_Condition (bus PT, frame ID 794) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Trig_Initial_Condition_31a(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_31a_Validity_Initial_Speed = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_31a_Validity_Initial_Heading = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_31a_Initial_Speed = (UInt32)((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]);
    crt_PT_31a_Initial_Heading = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_31a_MFDD_Start_Threshold = (UInt8)((UInt8)m[6]);
    crt_PT_31a_MFDD_End_Threshold = (UInt8)((UInt8)m[7]);

} /* End of crt_unpack_PT_RT_SB_Trig_Initial_Condition_31a */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trig_Direct_Dist (bus PT, frame ID 9241890) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Trig_Direct_Dist_8d0522(UInt8 m[])
{

    /* Pack signal Direct_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8d0522_Direct_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Path_Distance_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8d0522_Path_Distance_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Trig_Direct_Dist_8d0522 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Direct_Dist (bus PT, frame ID 9241890) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Trig_Direct_Dist_8d0522(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8d0522_Direct_Distance = (UInt32)((((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    crt_PT_8d0522_Path_Distance_2D = (UInt32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_Trig_Direct_Dist_8d0522 */


/**
 * Pack the signals of outbound PDU RT_SB_Trig_Forward_Dist (bus PT, frame ID 9241634) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Trig_Forward_Dist_8d0422(UInt8 m[])
{

    /* Pack signal Forward_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8d0422_Forward_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Deviation_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8d0422_Deviation_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Trig_Forward_Dist_8d0422 */


#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_SB_Trig_Forward_Dist (bus PT, frame ID 9241634) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Trig_Forward_Dist_8d0422(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8d0422_Forward_Distance = (Int32)((((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    crt_PT_8d0422_Deviation_Distance = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_Trig_Forward_Dist_8d0422 */
#endif



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trig_Path_Dist (bus PT, frame ID 9241378) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Trig_Path_Dist_8d0322(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Path_Distance_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8d0322_Path_Distance_3D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Trig_Path_Dist_8d0322 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trig_Path_Dist (bus PT, frame ID 9241378) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Trig_Path_Dist_8d0322(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8d0322_Path_Distance_3D = (UInt32)((((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_SB_Trig_Path_Dist_8d0322 */


/**
 * Pack the signals of outbound PDU RT_SB_Trig_Accel (bus PT, frame ID 9241122) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Trig_Accel_8d0222(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_MFDD. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0222_Validity_MFDD;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Average_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0222_Validity_Average_Accel << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_Triggered_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0222_Validity_Triggered_Time << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal MFDD. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8d0222_MFDD;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }

    /* Pack signal Average_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8d0222_Average_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
    }

    /* Pack signal Triggered_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8d0222_Triggered_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Trig_Accel_8d0222 */


#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of outbound PDU RT_SB_Trig_Accel (bus PT, frame ID 9241122) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Trig_Accel_8d0222(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8d0222_Validity_MFDD = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8d0222_Validity_Average_Accel = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8d0222_Validity_Triggered_Time = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_8d0222_MFDD = (Int16)((((UInt16)m[2]) << 8) | m[1]);
    crt_PT_8d0222_Average_Accel = (Int16)((((UInt16)m[4]) << 8) | m[3]);
    crt_PT_8d0222_Triggered_Time = (UInt32)((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]);

} /* End of crt_unpack_PT_RT_SB_Trig_Accel_8d0222 */
#endif



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of unused PDU RT_DL1MK3_Measure_Time_12 (bus PT, frame ID 9833508) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_12_960c24(UInt8 m[])
{

    /* Pack signal Measured_Time_12. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960c24_Measured_Time_12;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_12_960c24 */
#endif



#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/**
 * Unpack the signals of unused PDU RT_DL1MK3_Measure_Time_12 (bus PT, frame ID 9833508) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_12_960c24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_12_960c24 */
#endif



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_11 (bus PT, frame ID 9833252) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_11_960b24(UInt8 m[])
{

    /* Pack signal Measured_Time_11. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960b24_Measured_Time_11;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_11_960b24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_11 (bus PT, frame ID 9833252) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_11_960b24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960b24_Measured_Time_11 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_11_960b24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_10 (bus PT, frame ID 9832996) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_10_960a24(UInt8 m[])
{

    /* Pack signal Measured_Time_10. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960a24_Measured_Time_10;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_10_960a24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_10 (bus PT, frame ID 9832996) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_10_960a24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960a24_Measured_Time_10 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_10_960a24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_9 (bus PT, frame ID 9832740) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_9_960924(UInt8 m[])
{

    /* Pack signal Measured_Time_9. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960924_Measured_Time_9;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_9_960924 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_9 (bus PT, frame ID 9832740) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_9_960924(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960924_Measured_Time_9 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_9_960924 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_8 (bus PT, frame ID 9832484) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_8_960824(UInt8 m[])
{

    /* Pack signal Measured_Time_8. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960824_Measured_Time_8;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_8_960824 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_8 (bus PT, frame ID 9832484) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_8_960824(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960824_Measured_Time_8 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_8_960824 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_7 (bus PT, frame ID 9832228) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_7_960724(UInt8 m[])
{

    /* Pack signal Measured_Time_7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960724_Measured_Time_7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_7_960724 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_7 (bus PT, frame ID 9832228) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_7_960724(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960724_Measured_Time_7 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_7_960724 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_6 (bus PT, frame ID 9831972) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_6_960624(UInt8 m[])
{

    /* Pack signal Measured_Time_6. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960624_Measured_Time_6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_6_960624 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_6 (bus PT, frame ID 9831972) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_6_960624(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960624_Measured_Time_6 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_6_960624 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_5 (bus PT, frame ID 9831716) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_5_960524(UInt8 m[])
{

    /* Pack signal Measured_Time_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960524_Measured_Time_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_5_960524 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_5 (bus PT, frame ID 9831716) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_5_960524(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960524_Measured_Time_5 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_5_960524 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_4 (bus PT, frame ID 9831460) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_4_960424(UInt8 m[])
{

    /* Pack signal Measured_Time_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960424_Measured_Time_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_4_960424 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_4 (bus PT, frame ID 9831460) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_4_960424(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960424_Measured_Time_4 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_4_960424 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_3 (bus PT, frame ID 9831204) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_3_960324(UInt8 m[])
{

    /* Pack signal Measured_Time_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960324_Measured_Time_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_3_960324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_3 (bus PT, frame ID 9831204) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_3_960324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960324_Measured_Time_3 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_3_960324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_2 (bus PT, frame ID 9830948) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_2_960224(UInt8 m[])
{

    /* Pack signal Measured_Time_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960224_Measured_Time_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_2_960224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_2 (bus PT, frame ID 9830948) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_2_960224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960224_Measured_Time_2 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_2_960224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Measure_Time_1 (bus PT, frame ID 9830692) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Measure_Time_1_960124(UInt8 m[])
{

    /* Pack signal Measured_Time_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_960124_Measured_Time_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Measure_Time_1_960124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_1 (bus PT, frame ID 9830692) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Measure_Time_1_960124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_960124_Measured_Time_1 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Measure_Time_1_960124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_RPM (bus PT, frame ID 9767972) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_RPM_950c24(UInt8 m[])
{

    /* Pack signal RPM. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_950c24_RPM;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_RPM_950c24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_RPM (bus PT, frame ID 9767972) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_RPM_950c24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_950c24_RPM = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_RPM_950c24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Freq_4 (bus PT, frame ID 9767716) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Freq_4_950b24(UInt8 m[])
{

    /* Pack signal Frequency_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_950b24_Frequency_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Freq_4_950b24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Freq_4 (bus PT, frame ID 9767716) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Freq_4_950b24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_950b24_Frequency_4 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Freq_4_950b24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Freq_3 (bus PT, frame ID 9767460) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Freq_3_950a24(UInt8 m[])
{

    /* Pack signal Frequency_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_950a24_Frequency_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Freq_3_950a24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Freq_3 (bus PT, frame ID 9767460) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Freq_3_950a24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_950a24_Frequency_3 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Freq_3_950a24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Freq_2 (bus PT, frame ID 9767204) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Freq_2_950924(UInt8 m[])
{

    /* Pack signal Frequency_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_950924_Frequency_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Freq_2_950924 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Freq_2 (bus PT, frame ID 9767204) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Freq_2_950924(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_950924_Frequency_2 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Freq_2_950924 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Misc_3 (bus PT, frame ID 9896740) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Misc_3_970324(UInt8 m[])
{

    /* Pack signal Misc_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_970324_Misc_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Misc_3_970324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Misc_3 (bus PT, frame ID 9896740) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Misc_3_970324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_970324_Misc_3 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Misc_3_970324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Misc_2 (bus PT, frame ID 9896484) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Misc_2_970224(UInt8 m[])
{

    /* Pack signal Misc_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_970224_Misc_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Misc_2_970224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Misc_2 (bus PT, frame ID 9896484) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Misc_2_970224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_970224_Misc_2 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Misc_2_970224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Misc_1 (bus PT, frame ID 9896228) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Misc_1_970124(UInt8 m[])
{

    /* Pack signal Misc_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_970124_Misc_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Misc_1_970124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Misc_1 (bus PT, frame ID 9896228) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Misc_1_970124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_970124_Misc_1 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Misc_1_970124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_31 (bus PT, frame ID 9707300) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_31_941f24(UInt8 m[])
{

    /* Pack signal AUX_31. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941f24_AUX_31;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_31_941f24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_31 (bus PT, frame ID 9707300) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_31_941f24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941f24_AUX_31 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_31_941f24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_30 (bus PT, frame ID 9707044) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_30_941e24(UInt8 m[])
{

    /* Pack signal AUX_30. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941e24_AUX_30;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_30_941e24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_30 (bus PT, frame ID 9707044) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_30_941e24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941e24_AUX_30 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_30_941e24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_29 (bus PT, frame ID 9706788) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_29_941d24(UInt8 m[])
{

    /* Pack signal AUX_29. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941d24_AUX_29;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_29_941d24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_29 (bus PT, frame ID 9706788) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_29_941d24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941d24_AUX_29 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_29_941d24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_28 (bus PT, frame ID 9706532) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_28_941c24(UInt8 m[])
{

    /* Pack signal AUX_28. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941c24_AUX_28;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_28_941c24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_28 (bus PT, frame ID 9706532) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_28_941c24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941c24_AUX_28 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_28_941c24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_27 (bus PT, frame ID 9706276) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_27_941b24(UInt8 m[])
{

    /* Pack signal AUX_27. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941b24_AUX_27;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_27_941b24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_27 (bus PT, frame ID 9706276) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_27_941b24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941b24_AUX_27 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_27_941b24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_26 (bus PT, frame ID 9706020) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_26_941a24(UInt8 m[])
{

    /* Pack signal AUX_26. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941a24_AUX_26;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_26_941a24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_26 (bus PT, frame ID 9706020) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_26_941a24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941a24_AUX_26 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_26_941a24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_25 (bus PT, frame ID 9705764) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_25_941924(UInt8 m[])
{

    /* Pack signal AUX_25. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941924_AUX_25;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_25_941924 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_25 (bus PT, frame ID 9705764) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_25_941924(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941924_AUX_25 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_25_941924 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_24 (bus PT, frame ID 9705508) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_24_941824(UInt8 m[])
{

    /* Pack signal AUX_24. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941824_AUX_24;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_24_941824 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_24 (bus PT, frame ID 9705508) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_24_941824(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941824_AUX_24 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_24_941824 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_23 (bus PT, frame ID 9705252) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_23_941724(UInt8 m[])
{

    /* Pack signal AUX_23. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941724_AUX_23;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_23_941724 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_23 (bus PT, frame ID 9705252) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_23_941724(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941724_AUX_23 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_23_941724 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_22 (bus PT, frame ID 9704996) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_22_941624(UInt8 m[])
{

    /* Pack signal AUX_22. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941624_AUX_22;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_22_941624 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_22 (bus PT, frame ID 9704996) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_22_941624(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941624_AUX_22 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_22_941624 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_21 (bus PT, frame ID 9704740) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_21_941524(UInt8 m[])
{

    /* Pack signal AUX_21. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941524_AUX_21;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_21_941524 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_21 (bus PT, frame ID 9704740) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_21_941524(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941524_AUX_21 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_21_941524 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_20 (bus PT, frame ID 9704484) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_20_941424(UInt8 m[])
{

    /* Pack signal AUX_20. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941424_AUX_20;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_20_941424 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_20 (bus PT, frame ID 9704484) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_20_941424(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941424_AUX_20 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_20_941424 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_19 (bus PT, frame ID 9704228) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_19_941324(UInt8 m[])
{

    /* Pack signal AUX_19. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941324_AUX_19;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_19_941324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_19 (bus PT, frame ID 9704228) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_19_941324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941324_AUX_19 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_19_941324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_18 (bus PT, frame ID 9703972) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_18_941224(UInt8 m[])
{

    /* Pack signal AUX_18. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941224_AUX_18;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_18_941224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_18 (bus PT, frame ID 9703972) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_18_941224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941224_AUX_18 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_18_941224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_17 (bus PT, frame ID 9703716) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_17_941124(UInt8 m[])
{

    /* Pack signal AUX_17. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941124_AUX_17;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_17_941124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_17 (bus PT, frame ID 9703716) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_17_941124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941124_AUX_17 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_17_941124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_16 (bus PT, frame ID 9703460) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_16_941024(UInt8 m[])
{

    /* Pack signal AUX_16. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_941024_AUX_16;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_16_941024 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_16 (bus PT, frame ID 9703460) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_16_941024(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_941024_AUX_16 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_16_941024 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_15 (bus PT, frame ID 9703204) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_15_940f24(UInt8 m[])
{

    /* Pack signal AUX_15. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940f24_AUX_15;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_15_940f24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_15 (bus PT, frame ID 9703204) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_15_940f24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940f24_AUX_15 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_15_940f24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_14 (bus PT, frame ID 9702948) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_14_940e24(UInt8 m[])
{

    /* Pack signal AUX_14. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940e24_AUX_14;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_14_940e24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_14 (bus PT, frame ID 9702948) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_14_940e24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940e24_AUX_14 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_14_940e24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_13 (bus PT, frame ID 9702692) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_13_940d24(UInt8 m[])
{

    /* Pack signal AUX_13. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940d24_AUX_13;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_13_940d24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_13 (bus PT, frame ID 9702692) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_13_940d24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940d24_AUX_13 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_13_940d24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_12 (bus PT, frame ID 9702436) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_12_940c24(UInt8 m[])
{

    /* Pack signal AUX_12. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940c24_AUX_12;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_12_940c24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_12 (bus PT, frame ID 9702436) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_12_940c24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940c24_AUX_12 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_12_940c24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_11 (bus PT, frame ID 9702180) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_11_940b24(UInt8 m[])
{

    /* Pack signal AUX_11. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940b24_AUX_11;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_11_940b24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_11 (bus PT, frame ID 9702180) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_11_940b24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940b24_AUX_11 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_11_940b24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_9 (bus PT, frame ID 9701668) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_9_940924(UInt8 m[])
{

    /* Pack signal AUX_9. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940924_AUX_9;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_9_940924 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_9 (bus PT, frame ID 9701668) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_9_940924(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940924_AUX_9 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_9_940924 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_10 (bus PT, frame ID 9701924) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_10_940a24(UInt8 m[])
{

    /* Pack signal AUX_10. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940a24_AUX_10;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_10_940a24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_10 (bus PT, frame ID 9701924) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_10_940a24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940a24_AUX_10 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_10_940a24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_8 (bus PT, frame ID 9701412) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_8_940824(UInt8 m[])
{

    /* Pack signal AUX_8. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940824_AUX_8;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_8_940824 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_8 (bus PT, frame ID 9701412) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_8_940824(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940824_AUX_8 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_8_940824 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_7 (bus PT, frame ID 9701156) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_7_940724(UInt8 m[])
{

    /* Pack signal AUX_7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940724_AUX_7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_7_940724 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_7 (bus PT, frame ID 9701156) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_7_940724(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940724_AUX_7 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_7_940724 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_6 (bus PT, frame ID 9700900) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_6_940624(UInt8 m[])
{

    /* Pack signal AUX_6. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940624_AUX_6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_6_940624 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_6 (bus PT, frame ID 9700900) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_6_940624(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940624_AUX_6 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_6_940624 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_5 (bus PT, frame ID 9700644) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_5_940524(UInt8 m[])
{

    /* Pack signal AUX_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940524_AUX_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_5_940524 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_5 (bus PT, frame ID 9700644) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_5_940524(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940524_AUX_5 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_5_940524 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_4 (bus PT, frame ID 9700388) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_4_940424(UInt8 m[])
{

    /* Pack signal AUX_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940424_AUX_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_4_940424 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_4 (bus PT, frame ID 9700388) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_4_940424(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940424_AUX_4 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_4_940424 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_3 (bus PT, frame ID 9700132) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_3_940324(UInt8 m[])
{

    /* Pack signal AUX_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940324_AUX_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_3_940324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_3 (bus PT, frame ID 9700132) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_3_940324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940324_AUX_3 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_3_940324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_2 (bus PT, frame ID 9699876) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_2_940224(UInt8 m[])
{

    /* Pack signal AUX_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940224_AUX_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_2_940224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_2 (bus PT, frame ID 9699876) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_2_940224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940224_AUX_2 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_2_940224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Aux_1 (bus PT, frame ID 9699620) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Aux_1_940124(UInt8 m[])
{

    /* Pack signal AUX_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_940124_AUX_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Aux_1_940124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Aux_1 (bus PT, frame ID 9699620) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Aux_1_940124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_940124_AUX_1 = (UInt16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Aux_1_940124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Pressure_5 (bus PT, frame ID 9438500) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Pressure_5_900524(UInt8 m[])
{

    /* Pack signal Pressure_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_900524_Pressure_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Pressure_5_900524 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Pressure_5 (bus PT, frame ID 9438500) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Pressure_5_900524(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_900524_Pressure_5 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Pressure_5_900524 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Pressure_4 (bus PT, frame ID 9438244) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Pressure_4_900424(UInt8 m[])
{

    /* Pack signal Pressure_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_900424_Pressure_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Pressure_4_900424 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Pressure_4 (bus PT, frame ID 9438244) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Pressure_4_900424(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_900424_Pressure_4 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Pressure_4_900424 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Pressure_3 (bus PT, frame ID 9437988) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Pressure_3_900324(UInt8 m[])
{

    /* Pack signal Pressure_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_900324_Pressure_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Pressure_3_900324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Pressure_3 (bus PT, frame ID 9437988) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Pressure_3_900324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_900324_Pressure_3 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Pressure_3_900324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Pressure_2 (bus PT, frame ID 9437732) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Pressure_2_900224(UInt8 m[])
{

    /* Pack signal Pressure_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_900224_Pressure_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Pressure_2_900224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Pressure_2 (bus PT, frame ID 9437732) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Pressure_2_900224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_900224_Pressure_2 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Pressure_2_900224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Pressure_1 (bus PT, frame ID 9437476) into a
 * byte array of 3 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Pressure_1_900124(UInt8 m[])
{

    /* Pack signal Pressure_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_900124_Pressure_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Pressure_1_900124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Pressure_1 (bus PT, frame ID 9437476) from
 * a byte array of 3 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Pressure_1_900124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_900124_Pressure_1 = (UInt32)((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Pressure_1_900124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Angle_3 (bus PT, frame ID 9569060) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Angle_3_920324(UInt8 m[])
{

    /* Pack signal Angle_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_920324_Angle_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Angle_3_920324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Angle_3 (bus PT, frame ID 9569060) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Angle_3_920324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_920324_Angle_3 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Angle_3_920324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Angle_2 (bus PT, frame ID 9568804) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Angle_2_920224(UInt8 m[])
{

    /* Pack signal Angle_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_920224_Angle_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Angle_2_920224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Angle_2 (bus PT, frame ID 9568804) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Angle_2_920224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_920224_Angle_2 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Angle_2_920224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Angle_1 (bus PT, frame ID 9568548) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Angle_1_920124(UInt8 m[])
{

    /* Pack signal Angle_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_920124_Angle_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Angle_1_920124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Angle_1 (bus PT, frame ID 9568548) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Angle_1_920124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_920124_Angle_1 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Angle_1_920124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_25 (bus PT, frame ID 9509156) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_25_911924(UInt8 m[])
{

    /* Pack signal Temperature_25. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911924_Temperature_25;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_25_911924 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_25 (bus PT, frame ID 9509156) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_25_911924(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911924_Temperature_25 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_25_911924 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_24 (bus PT, frame ID 9508900) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_24_911824(UInt8 m[])
{

    /* Pack signal Temperature_24. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911824_Temperature_24;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_24_911824 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_24 (bus PT, frame ID 9508900) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_24_911824(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911824_Temperature_24 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_24_911824 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_23 (bus PT, frame ID 9508644) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_23_911724(UInt8 m[])
{

    /* Pack signal Temperature_23. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911724_Temperature_23;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_23_911724 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_23 (bus PT, frame ID 9508644) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_23_911724(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911724_Temperature_23 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_23_911724 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_22 (bus PT, frame ID 9508388) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_22_911624(UInt8 m[])
{

    /* Pack signal Temperature_22. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911624_Temperature_22;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_22_911624 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_22 (bus PT, frame ID 9508388) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_22_911624(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911624_Temperature_22 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_22_911624 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_21 (bus PT, frame ID 9508132) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_21_911524(UInt8 m[])
{

    /* Pack signal Temperature_21. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911524_Temperature_21;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_21_911524 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_21 (bus PT, frame ID 9508132) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_21_911524(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911524_Temperature_21 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_21_911524 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_20 (bus PT, frame ID 9507876) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_20_911424(UInt8 m[])
{

    /* Pack signal Temperature_20. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911424_Temperature_20;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_20_911424 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_20 (bus PT, frame ID 9507876) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_20_911424(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911424_Temperature_20 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_20_911424 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_19 (bus PT, frame ID 9507620) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_19_911324(UInt8 m[])
{

    /* Pack signal Temperature_19. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911324_Temperature_19;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_19_911324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_19 (bus PT, frame ID 9507620) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_19_911324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911324_Temperature_19 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_19_911324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_18 (bus PT, frame ID 9507364) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_18_911224(UInt8 m[])
{

    /* Pack signal Temperature_18. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911224_Temperature_18;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_18_911224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_18 (bus PT, frame ID 9507364) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_18_911224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911224_Temperature_18 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_18_911224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_17 (bus PT, frame ID 9507108) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_17_911124(UInt8 m[])
{

    /* Pack signal Temperature_17. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911124_Temperature_17;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_17_911124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_17 (bus PT, frame ID 9507108) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_17_911124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911124_Temperature_17 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_17_911124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_16 (bus PT, frame ID 9506852) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_16_911024(UInt8 m[])
{

    /* Pack signal Temperature_16. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_911024_Temperature_16;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_16_911024 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_16 (bus PT, frame ID 9506852) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_16_911024(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_911024_Temperature_16 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_16_911024 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_15 (bus PT, frame ID 9506596) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_15_910f24(UInt8 m[])
{

    /* Pack signal Temperature_15. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910f24_Temperature_15;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_15_910f24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_15 (bus PT, frame ID 9506596) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_15_910f24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910f24_Temperature_15 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_15_910f24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_14 (bus PT, frame ID 9506340) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_14_910e24(UInt8 m[])
{

    /* Pack signal Temperature_14. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910e24_Temperature_14;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_14_910e24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_14 (bus PT, frame ID 9506340) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_14_910e24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910e24_Temperature_14 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_14_910e24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_13 (bus PT, frame ID 9506084) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_13_910d24(UInt8 m[])
{

    /* Pack signal Temperature_13. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910d24_Temperature_13;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_13_910d24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_13 (bus PT, frame ID 9506084) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_13_910d24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910d24_Temperature_13 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_13_910d24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_12 (bus PT, frame ID 9505828) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_12_910c24(UInt8 m[])
{

    /* Pack signal Temperature_12. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910c24_Temperature_12;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_12_910c24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_12 (bus PT, frame ID 9505828) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_12_910c24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910c24_Temperature_12 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_12_910c24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_11 (bus PT, frame ID 9505572) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_11_910b24(UInt8 m[])
{

    /* Pack signal Temperature_11. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910b24_Temperature_11;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_11_910b24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_11 (bus PT, frame ID 9505572) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_11_910b24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910b24_Temperature_11 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_11_910b24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_10 (bus PT, frame ID 9505316) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_10_910a24(UInt8 m[])
{

    /* Pack signal Temperature_10. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910a24_Temperature_10;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_10_910a24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_10 (bus PT, frame ID 9505316) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_10_910a24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910a24_Temperature_10 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_10_910a24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_9 (bus PT, frame ID 9505060) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_9_910924(UInt8 m[])
{

    /* Pack signal Temperature_9. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910924_Temperature_9;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_9_910924 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_9 (bus PT, frame ID 9505060) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_9_910924(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910924_Temperature_9 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_9_910924 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_8 (bus PT, frame ID 9504804) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_8_910824(UInt8 m[])
{

    /* Pack signal Temperature_8. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910824_Temperature_8;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_8_910824 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_8 (bus PT, frame ID 9504804) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_8_910824(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910824_Temperature_8 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_8_910824 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_7 (bus PT, frame ID 9504548) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_7_910724(UInt8 m[])
{

    /* Pack signal Temperature_7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910724_Temperature_7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_7_910724 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_7 (bus PT, frame ID 9504548) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_7_910724(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910724_Temperature_7 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_7_910724 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_6 (bus PT, frame ID 9504292) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_6_910624(UInt8 m[])
{

    /* Pack signal Temperature_6. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910624_Temperature_6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_6_910624 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_6 (bus PT, frame ID 9504292) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_6_910624(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910624_Temperature_6 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_6_910624 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_5 (bus PT, frame ID 9504036) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_5_910524(UInt8 m[])
{

    /* Pack signal Temperature_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910524_Temperature_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_5_910524 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_5 (bus PT, frame ID 9504036) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_5_910524(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910524_Temperature_5 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_5_910524 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_4 (bus PT, frame ID 9503780) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_4_910424(UInt8 m[])
{

    /* Pack signal Temperature_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910424_Temperature_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_4_910424 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_4 (bus PT, frame ID 9503780) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_4_910424(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910424_Temperature_4 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_4_910424 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_3 (bus PT, frame ID 9503524) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_3_910324(UInt8 m[])
{

    /* Pack signal Temperature_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910324_Temperature_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_3_910324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_3 (bus PT, frame ID 9503524) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_3_910324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910324_Temperature_3 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_3_910324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_2 (bus PT, frame ID 9503268) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_2_910224(UInt8 m[])
{

    /* Pack signal Temperature_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910224_Temperature_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_2_910224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_2 (bus PT, frame ID 9503268) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_2_910224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910224_Temperature_2 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_2_910224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Temp_1 (bus PT, frame ID 9503012) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Temp_1_910124(UInt8 m[])
{

    /* Pack signal Temperature_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_910124_Temperature_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Temp_1_910124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Temp_1 (bus PT, frame ID 9503012) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Temp_1_910124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_910124_Temperature_1 = (Int16)((((UInt16)m[1]) << 8) | m[0]);

} /* End of crt_unpack_PT_RT_DL1MK3_Temp_1_910124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_32 (bus PT, frame ID 8527652) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_32_821f24(UInt8 m[])
{

    /* Pack signal Analog_32. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821f24_Analog_32;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_32_821f24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_32 (bus PT, frame ID 8527652) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_32_821f24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821f24_Analog_32 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_32_821f24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_31 (bus PT, frame ID 8527396) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_31_821e24(UInt8 m[])
{

    /* Pack signal Analog_31. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821e24_Analog_31;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_31_821e24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_31 (bus PT, frame ID 8527396) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_31_821e24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821e24_Analog_31 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_31_821e24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_30 (bus PT, frame ID 8527140) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_30_821d24(UInt8 m[])
{

    /* Pack signal Analog_30. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821d24_Analog_30;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_30_821d24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_30 (bus PT, frame ID 8527140) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_30_821d24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821d24_Analog_30 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_30_821d24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_29 (bus PT, frame ID 8526884) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_29_821c24(UInt8 m[])
{

    /* Pack signal Analog_29. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821c24_Analog_29;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_29_821c24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_29 (bus PT, frame ID 8526884) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_29_821c24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821c24_Analog_29 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_29_821c24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_28 (bus PT, frame ID 8526628) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_28_821b24(UInt8 m[])
{

    /* Pack signal Analog_28. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821b24_Analog_28;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_28_821b24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_28 (bus PT, frame ID 8526628) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_28_821b24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821b24_Analog_28 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_28_821b24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_27 (bus PT, frame ID 8526372) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_27_821a24(UInt8 m[])
{

    /* Pack signal Analog_27. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821a24_Analog_27;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_27_821a24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_27 (bus PT, frame ID 8526372) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_27_821a24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821a24_Analog_27 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_27_821a24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_26 (bus PT, frame ID 8526116) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_26_821924(UInt8 m[])
{

    /* Pack signal Analog_26. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821924_Analog_26;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_26_821924 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_26 (bus PT, frame ID 8526116) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_26_821924(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821924_Analog_26 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_26_821924 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_25 (bus PT, frame ID 8525860) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_25_821824(UInt8 m[])
{

    /* Pack signal Analog_25. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821824_Analog_25;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_25_821824 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_25 (bus PT, frame ID 8525860) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_25_821824(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821824_Analog_25 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_25_821824 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_15 (bus PT, frame ID 8523300) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_15_820e24(UInt8 m[])
{

    /* Pack signal Analog_15. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820e24_Analog_15;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_15_820e24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_15 (bus PT, frame ID 8523300) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_15_820e24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820e24_Analog_15 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_15_820e24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_14 (bus PT, frame ID 8523044) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_14_820d24(UInt8 m[])
{

    /* Pack signal Analog_14. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820d24_Analog_14;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_14_820d24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_14 (bus PT, frame ID 8523044) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_14_820d24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820d24_Analog_14 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_14_820d24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_17 (bus PT, frame ID 8523812) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_17_821024(UInt8 m[])
{

    /* Pack signal Analog_17. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821024_Analog_17;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_17_821024 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_17 (bus PT, frame ID 8523812) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_17_821024(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821024_Analog_17 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_17_821024 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_24 (bus PT, frame ID 8525604) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_24_821724(UInt8 m[])
{

    /* Pack signal Analog_24. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821724_Analog_24;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_24_821724 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_24 (bus PT, frame ID 8525604) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_24_821724(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821724_Analog_24 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_24_821724 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_23 (bus PT, frame ID 8525348) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_23_821624(UInt8 m[])
{

    /* Pack signal Analog_23. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821624_Analog_23;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_23_821624 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_23 (bus PT, frame ID 8525348) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_23_821624(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821624_Analog_23 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_23_821624 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_22 (bus PT, frame ID 8525092) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_22_821524(UInt8 m[])
{

    /* Pack signal Analog_22. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821524_Analog_22;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_22_821524 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_22 (bus PT, frame ID 8525092) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_22_821524(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821524_Analog_22 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_22_821524 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_21 (bus PT, frame ID 8524836) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_21_821424(UInt8 m[])
{

    /* Pack signal Analog_21. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821424_Analog_21;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_21_821424 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_21 (bus PT, frame ID 8524836) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_21_821424(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821424_Analog_21 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_21_821424 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_20 (bus PT, frame ID 8524580) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_20_821324(UInt8 m[])
{

    /* Pack signal Analog_20. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821324_Analog_20;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_20_821324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_20 (bus PT, frame ID 8524580) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_20_821324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821324_Analog_20 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_20_821324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_19 (bus PT, frame ID 8524324) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_19_821224(UInt8 m[])
{

    /* Pack signal Analog_19. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821224_Analog_19;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_19_821224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_19 (bus PT, frame ID 8524324) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_19_821224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821224_Analog_19 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_19_821224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_16 (bus PT, frame ID 8523556) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_16_820f24(UInt8 m[])
{

    /* Pack signal Analog_16. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820f24_Analog_16;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_16_820f24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_16 (bus PT, frame ID 8523556) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_16_820f24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820f24_Analog_16 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_16_820f24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_18 (bus PT, frame ID 8524068) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_18_821124(UInt8 m[])
{

    /* Pack signal Analog_18. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_821124_Analog_18;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_18_821124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_18 (bus PT, frame ID 8524068) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_18_821124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_821124_Analog_18 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_18_821124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_12 (bus PT, frame ID 8522532) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_12_820b24(UInt8 m[])
{

    /* Pack signal Analog_12. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820b24_Analog_12;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_12_820b24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_12 (bus PT, frame ID 8522532) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_12_820b24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820b24_Analog_12 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_12_820b24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_11 (bus PT, frame ID 8522276) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_11_820a24(UInt8 m[])
{

    /* Pack signal Analog_11. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820a24_Analog_11;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_11_820a24 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_11 (bus PT, frame ID 8522276) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_11_820a24(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820a24_Analog_11 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_11_820a24 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_10 (bus PT, frame ID 8522020) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_10_820924(UInt8 m[])
{

    /* Pack signal Analog_10. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820924_Analog_10;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_10_820924 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_10 (bus PT, frame ID 8522020) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_10_820924(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820924_Analog_10 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_10_820924 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_9 (bus PT, frame ID 8521764) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_9_820824(UInt8 m[])
{

    /* Pack signal Analog_9. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820824_Analog_9;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_9_820824 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_9 (bus PT, frame ID 8521764) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_9_820824(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820824_Analog_9 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_9_820824 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_8 (bus PT, frame ID 8521508) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_8_820724(UInt8 m[])
{

    /* Pack signal Analog_8. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820724_Analog_8;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_8_820724 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_8 (bus PT, frame ID 8521508) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_8_820724(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820724_Analog_8 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_8_820724 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_7 (bus PT, frame ID 8521252) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_7_820624(UInt8 m[])
{

    /* Pack signal Analog_7. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820624_Analog_7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_7_820624 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_7 (bus PT, frame ID 8521252) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_7_820624(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820624_Analog_7 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_7_820624 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_6 (bus PT, frame ID 8520996) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_6_820524(UInt8 m[])
{

    /* Pack signal Analog_6. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820524_Analog_6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_6_820524 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_6 (bus PT, frame ID 8520996) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_6_820524(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820524_Analog_6 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_6_820524 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_5 (bus PT, frame ID 8520740) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_5_820424(UInt8 m[])
{

    /* Pack signal Analog_5. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820424_Analog_5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_5_820424 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_5 (bus PT, frame ID 8520740) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_5_820424(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820424_Analog_5 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_5_820424 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_4 (bus PT, frame ID 8520484) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_4_820324(UInt8 m[])
{

    /* Pack signal Analog_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820324_Analog_4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_4_820324 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_4 (bus PT, frame ID 8520484) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_4_820324(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820324_Analog_4 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_4_820324 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_3 (bus PT, frame ID 8520228) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_3_820224(UInt8 m[])
{

    /* Pack signal Analog_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820224_Analog_3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_3_820224 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_3 (bus PT, frame ID 8520228) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_3_820224(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820224_Analog_3 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_3_820224 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_2 (bus PT, frame ID 8519972) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_2_820124(UInt8 m[])
{

    /* Pack signal Analog_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820124_Analog_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_2_820124 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_2 (bus PT, frame ID 8519972) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_2_820124(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820124_Analog_2 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_2_820124 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Analog_1 (bus PT, frame ID 8519716) into a
 * byte array of 2 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Analog_1_820024(UInt8 m[])
{

    /* Pack signal Analog_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_820024_Analog_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Analog_1_820024 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Analog_1 (bus PT, frame ID 8519716) from
 * a byte array of 2 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Analog_1_820024(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_820024_Analog_1 = (UInt16)((((UInt16)m[0]) << 8) | m[1]);

} /* End of crt_unpack_PT_RT_DL1MK3_Analog_1_820024 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_DL1MK3_Accel (bus PT, frame ID 8388644) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_DL1MK3_Accel_800024(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800024_Validity_Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800024_Validity_Accel_Lateral << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800024_Validity_Accel_Vertical << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal SQC. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800024_SQC << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0xf0;
        m[0] |= (UInt8)(s & 0xf0);
    }

    /* Pack signal Accuracy_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800024_Accuracy_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800024_Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800024_Accel_Lateral;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800024_Accel_Vertical;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_DL1MK3_Accel_800024 */
#endif



/**
 * Unpack the signals of inbound PDU RT_DL1MK3_Accel (bus PT, frame ID 8388644) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_DL1MK3_Accel_800024(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_800024_Validity_Accel_Longitudinal = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_800024_Validity_Accel_Lateral = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_800024_Validity_Accel_Vertical = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_800024_Accuracy_Accel = (UInt8)((UInt8)m[1]);
    crt_PT_800024_Accel_Longitudinal = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_800024_Accel_Lateral = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_800024_Accel_Vertical = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_DL1MK3_Accel_800024 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_4_Vel_NED_2 (bus PT, frame ID 9384482) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_4_Vel_NED_2_8f3222(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[3] = 0xff;

    /* Pack signal Virtual_4_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f3222_Virtual_4_Vel_NED_D << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }

    /* Pack signal Virtual_4_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f3222_Virtual_4_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Virtual_4_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f3222_Virtual_4_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_4_Vel_NED_2_8f3222 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_4_Vel_NED_2 (bus PT, frame ID 9384482) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_4_Vel_NED_2_8f3222(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f3222_Virtual_4_Vel_NED_D = (Int32)((Int32)(((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]) << 8) >> 8);
    crt_PT_8f3222_Virtual_4_Heading = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_8f3222_Virtual_4_Slip = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_4_Vel_NED_2_8f3222 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_4_Vel_NED_1 (bus PT, frame ID 9384226) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_4_Vel_NED_1_8f3122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[3] = 0xff;
    m[7] = 0xff;

    /* Pack signal Virtual_4_Vel_NED_N. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f3122_Virtual_4_Vel_NED_N << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }

    /* Pack signal Virtual_4_Vel_NED_E. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f3122_Virtual_4_Vel_NED_E << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_4_Vel_NED_1_8f3122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_4_Vel_NED_1 (bus PT, frame ID 9384226) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_4_Vel_NED_1_8f3122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f3122_Virtual_4_Vel_NED_N = (Int32)((Int32)(((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]) << 8) >> 8);
    crt_PT_8f3122_Virtual_4_Vel_NED_E = (Int32)((Int32)(((((((UInt32)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_4_Vel_NED_1_8f3122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_4_Offset (bus PT, frame ID 9383970) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_4_Offset_8f3022(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[6] = 0xff;
    m[7] = 0xff;

    /* Pack signal Virtual_4_Offset_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f3022_Virtual_4_Offset_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal Virtual_4_Offset_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f3022_Virtual_4_Offset_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Virtual_4_Offset_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f3022_Virtual_4_Offset_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_4_Offset_8f3022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_4_Offset (bus PT, frame ID 9383970) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_4_Offset_8f3022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f3022_Virtual_4_Offset_X = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_8f3022_Virtual_4_Offset_Y = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8f3022_Virtual_4_Offset_Z = (Int16)((((UInt16)m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_4_Offset_8f3022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_3_Vel_NED_2 (bus PT, frame ID 9380386) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_3_Vel_NED_2_8f2222(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[3] = 0xff;

    /* Pack signal Virtual_3_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f2222_Virtual_3_Vel_NED_D << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }

    /* Pack signal Virtual_3_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f2222_Virtual_3_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Virtual_3_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f2222_Virtual_3_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_3_Vel_NED_2_8f2222 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_3_Vel_NED_2 (bus PT, frame ID 9380386) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_3_Vel_NED_2_8f2222(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f2222_Virtual_3_Vel_NED_D = (Int32)((Int32)(((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]) << 8) >> 8);
    crt_PT_8f2222_Virtual_3_Heading = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_8f2222_Virtual_3_Slip = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_3_Vel_NED_2_8f2222 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_3_Vel_NED_1 (bus PT, frame ID 9380130) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_3_Vel_NED_1_8f2122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[3] = 0xff;
    m[7] = 0xff;

    /* Pack signal Virtual_3_Vel_NED_N. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f2122_Virtual_3_Vel_NED_N << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }

    /* Pack signal Virtual_3_Vel_NED_E. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f2122_Virtual_3_Vel_NED_E << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_3_Vel_NED_1_8f2122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_3_Vel_NED_1 (bus PT, frame ID 9380130) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_3_Vel_NED_1_8f2122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f2122_Virtual_3_Vel_NED_N = (Int32)((Int32)(((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]) << 8) >> 8);
    crt_PT_8f2122_Virtual_3_Vel_NED_E = (Int32)((Int32)(((((((UInt32)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_3_Vel_NED_1_8f2122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_3_Offset (bus PT, frame ID 9379874) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_3_Offset_8f2022(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[6] = 0xff;
    m[7] = 0xff;

    /* Pack signal Virtual_3_Offset_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f2022_Virtual_3_Offset_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal Virtual_3_Offset_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f2022_Virtual_3_Offset_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Virtual_3_Offset_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f2022_Virtual_3_Offset_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_3_Offset_8f2022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_3_Offset (bus PT, frame ID 9379874) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_3_Offset_8f2022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f2022_Virtual_3_Offset_X = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_8f2022_Virtual_3_Offset_Y = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8f2022_Virtual_3_Offset_Z = (Int16)((((UInt16)m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_3_Offset_8f2022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_2_Vel_NED_2 (bus PT, frame ID 9376290) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_2_Vel_NED_2_8f1222(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[3] = 0xff;

    /* Pack signal Virtual_2_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f1222_Virtual_2_Vel_NED_D << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }

    /* Pack signal Virtual_2_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f1222_Virtual_2_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Virtual_2_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f1222_Virtual_2_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_2_Vel_NED_2_8f1222 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_2_Vel_NED_2 (bus PT, frame ID 9376290) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_2_Vel_NED_2_8f1222(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f1222_Virtual_2_Vel_NED_D = (Int32)((Int32)(((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]) << 8) >> 8);
    crt_PT_8f1222_Virtual_2_Heading = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_8f1222_Virtual_2_Slip = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_2_Vel_NED_2_8f1222 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_2_Vel_NED_1 (bus PT, frame ID 9376034) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_2_Vel_NED_1_8f1122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[3] = 0xff;
    m[7] = 0xff;

    /* Pack signal Virtual_2_Vel_NED_N. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f1122_Virtual_2_Vel_NED_N << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }

    /* Pack signal Virtual_2_Vel_NED_E. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f1122_Virtual_2_Vel_NED_E << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_2_Vel_NED_1_8f1122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_2_Vel_NED_1 (bus PT, frame ID 9376034) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_2_Vel_NED_1_8f1122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f1122_Virtual_2_Vel_NED_N = (Int32)((Int32)(((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]) << 8) >> 8);
    crt_PT_8f1122_Virtual_2_Vel_NED_E = (Int32)((Int32)(((((((UInt32)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_2_Vel_NED_1_8f1122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_2_Offset (bus PT, frame ID 9375778) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_2_Offset_8f1022(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[6] = 0xff;
    m[7] = 0xff;

    /* Pack signal Virtual_2_Offset_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f1022_Virtual_2_Offset_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal Virtual_2_Offset_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f1022_Virtual_2_Offset_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Virtual_2_Offset_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f1022_Virtual_2_Offset_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_2_Offset_8f1022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_2_Offset (bus PT, frame ID 9375778) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_2_Offset_8f1022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f1022_Virtual_2_Offset_X = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_8f1022_Virtual_2_Offset_Y = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8f1022_Virtual_2_Offset_Z = (Int16)((((UInt16)m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_2_Offset_8f1022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_1_Vel_NED_2 (bus PT, frame ID 9372194) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_1_Vel_NED_2_8f0222(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[3] = 0xff;

    /* Pack signal Virtual_1_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f0222_Virtual_1_Vel_NED_D << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }

    /* Pack signal Virtual_1_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f0222_Virtual_1_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Virtual_1_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f0222_Virtual_1_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_1_Vel_NED_2_8f0222 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_1_Vel_NED_2 (bus PT, frame ID 9372194) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_1_Vel_NED_2_8f0222(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f0222_Virtual_1_Vel_NED_D = (Int32)((Int32)(((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]) << 8) >> 8);
    crt_PT_8f0222_Virtual_1_Heading = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_8f0222_Virtual_1_Slip = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_1_Vel_NED_2_8f0222 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_1_Vel_NED_1 (bus PT, frame ID 9371938) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_1_Vel_NED_1_8f0122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[3] = 0xff;
    m[7] = 0xff;

    /* Pack signal Virtual_1_Vel_NED_N. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f0122_Virtual_1_Vel_NED_N << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
    }

    /* Pack signal Virtual_1_Vel_NED_E. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8f0122_Virtual_1_Vel_NED_E << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_1_Vel_NED_1_8f0122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_1_Vel_NED_1 (bus PT, frame ID 9371938) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_1_Vel_NED_1_8f0122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f0122_Virtual_1_Vel_NED_N = (Int32)((Int32)(((((((UInt32)m[2]) << 8) | m[1]) << 8) | m[0]) << 8) >> 8);
    crt_PT_8f0122_Virtual_1_Vel_NED_E = (Int32)((Int32)(((((((UInt32)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_1_Vel_NED_1_8f0122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vpt_1_Offset (bus PT, frame ID 9371682) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vpt_1_Offset_8f0022(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[6] = 0xff;
    m[7] = 0xff;

    /* Pack signal Virtual_1_Offset_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f0022_Virtual_1_Offset_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
    }

    /* Pack signal Virtual_1_Offset_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f0022_Virtual_1_Offset_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Virtual_1_Offset_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8f0022_Virtual_1_Offset_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vpt_1_Offset_8f0022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vpt_1_Offset (bus PT, frame ID 9371682) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vpt_1_Offset_8f0022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8f0022_Virtual_1_Offset_X = (Int16)((((UInt16)m[1]) << 8) | m[0]);
    crt_PT_8f0022_Virtual_1_Offset_Y = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8f0022_Virtual_1_Offset_Z = (Int16)((((UInt16)m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_INS_Vpt_1_Offset_8f0022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Slip (bus PT, frame ID 9311778) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Slip_8e1622(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_INS_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1622_Validity_INS_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_INS_Squat. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1622_Validity_INS_Squat << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_INS_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1622_Accuracy_INS_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal INS_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8e1622_INS_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Accuracy_INS_Squat. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1622_Accuracy_INS_Squat;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
    }

    /* Pack signal INS_Squat. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8e1622_INS_Squat;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Slip_8e1622 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Slip (bus PT, frame ID 9311778) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Slip_8e1622(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e1622_Validity_INS_Slip = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e1622_Validity_INS_Squat = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8e1622_Accuracy_INS_Slip = (UInt8)((UInt8)m[1]);
    crt_PT_8e1622_INS_Slip = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8e1622_Accuracy_INS_Squat = (UInt8)((UInt8)m[4]);
    crt_PT_8e1622_INS_Squat = (Int16)((((UInt16)m[6]) << 8) | m[5]);

} /* End of crt_unpack_PT_RT_SB_INS_Slip_8e1622 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vel_ECEF_2 (bus PT, frame ID 9311010) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vel_ECEF_2_8e1322(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_INS_Vel_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1322_Validity_INS_Vel_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_INS_Vel_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1322_Validity_INS_Vel_ECEF_Z << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal INS_Vel_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e1322_INS_Vel_ECEF_Y << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal INS_Vel_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e1322_INS_Vel_ECEF_Z << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vel_ECEF_2_8e1322 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vel_ECEF_2 (bus PT, frame ID 9311010) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vel_ECEF_2_8e1322(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e1322_Validity_INS_Vel_ECEF_Y = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e1322_Validity_INS_Vel_ECEF_Z = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8e1322_INS_Vel_ECEF_Y = (Int32)((Int32)(((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) >> 8);
    crt_PT_8e1322_INS_Vel_ECEF_Z = (Int32)((Int32)(((((((UInt32)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_INS_Vel_ECEF_2_8e1322 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vel_ECEF_1 (bus PT, frame ID 9310754) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vel_ECEF_1_8e1222(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_INS_Vel_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1222_Validity_INS_Vel_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Accuracy_INS_Vel_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accuracy_INS_Vel_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
    }

    /* Pack signal Accuracy_INS_Vel_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
    }

    /* Pack signal INS_Vel_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e1222_INS_Vel_ECEF_X << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vel_ECEF_1_8e1222 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vel_ECEF_1 (bus PT, frame ID 9310754) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vel_ECEF_1_8e1222(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e1222_Validity_INS_Vel_ECEF_X = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X = (UInt8)((UInt8)m[1]);
    crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y = (UInt8)((UInt8)m[2]);
    crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z = (UInt8)((UInt8)m[3]);
    crt_PT_8e1222_INS_Vel_ECEF_X = (Int32)((Int32)(((((((UInt32)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_INS_Vel_ECEF_1_8e1222 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vel_NED_2 (bus PT, frame ID 9310498) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vel_NED_2_8e1122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Validity_INS_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1122_Validity_INS_Vel_NED_D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Accuracy_INS_Vel_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1122_Accuracy_INS_Vel_D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal INS_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e1122_INS_Vel_NED_D << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vel_NED_2_8e1122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vel_NED_2 (bus PT, frame ID 9310498) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vel_NED_2_8e1122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e1122_Validity_INS_Vel_NED_D = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e1122_Accuracy_INS_Vel_D = (UInt8)((UInt8)m[1]);
    crt_PT_8e1122_INS_Vel_NED_D = (Int32)((Int32)(((((((UInt32)m[4]) << 8) | m[3]) << 8) | m[2]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_INS_Vel_NED_2_8e1122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Vel_NED_1 (bus PT, frame ID 9310242) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Vel_NED_1_8e1022(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_INS_Vel_NED_N. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1022_Validity_INS_Vel_NED_N;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_INS_Vel_NED_E. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1022_Validity_INS_Vel_NED_E << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_INS_Vel_NE. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1022_Accuracy_INS_Vel_NE;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal INS_Vel_NED_N. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e1022_INS_Vel_NED_N << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
    }

    /* Pack signal INS_Vel_NED_E. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e1022_INS_Vel_NED_E << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Vel_NED_1_8e1022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Vel_NED_1 (bus PT, frame ID 9310242) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Vel_NED_1_8e1022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e1022_Validity_INS_Vel_NED_N = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e1022_Validity_INS_Vel_NED_E = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8e1022_Accuracy_INS_Vel_NE = (UInt8)((UInt8)m[1]);
    crt_PT_8e1022_INS_Vel_NED_N = (Int32)((Int32)(((((((UInt32)m[4]) << 8) | m[3]) << 8) | m[2]) << 8) >> 8);
    crt_PT_8e1022_INS_Vel_NED_E = (Int32)((Int32)(((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_INS_Vel_NED_1_8e1022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Pos_ECEF_2 (bus PT, frame ID 9307426) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Pos_ECEF_2_8e0522(UInt8 m[])
{

    /* Pack signal INS_Pos_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e0522_INS_Pos_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal INS_Pos_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e0522_INS_Pos_ECEF_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Pos_ECEF_2_8e0522 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Pos_ECEF_2 (bus PT, frame ID 9307426) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Pos_ECEF_2_8e0522(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e0522_INS_Pos_ECEF_Y = (Int32)((((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    crt_PT_8e0522_INS_Pos_ECEF_Z = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_INS_Pos_ECEF_2_8e0522 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Pos_ECEF_1 (bus PT, frame ID 9307170) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Pos_ECEF_1_8e0422(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_INS_Pos_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0422_Validity_INS_Pos_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_INS_Pos_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0422_Validity_INS_Pos_ECEF_Y << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_INS_Pos_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0422_Validity_INS_Pos_ECEF_Z << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_INS_Pos_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accuracy_INS_Pos_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
    }

    /* Pack signal Accuracy_INS_Pos_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
    }

    /* Pack signal INS_Pos_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e0422_INS_Pos_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Pos_ECEF_1_8e0422 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Pos_ECEF_1 (bus PT, frame ID 9307170) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Pos_ECEF_1_8e0422(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e0422_Validity_INS_Pos_ECEF_X = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e0422_Validity_INS_Pos_ECEF_Y = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8e0422_Validity_INS_Pos_ECEF_Z = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X = (UInt8)((UInt8)m[1]);
    crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y = (UInt8)((UInt8)m[2]);
    crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z = (UInt8)((UInt8)m[3]);
    crt_PT_8e0422_INS_Pos_ECEF_X = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_INS_Pos_ECEF_1_8e0422 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Pos_LLH_2 (bus PT, frame ID 9306914) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Pos_LLH_2_8e0322(UInt8 m[])
{

    /* Pack signal INS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e0322_INS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal INS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e0322_INS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Pos_LLH_2_8e0322 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Pos_LLH_2 (bus PT, frame ID 9306914) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Pos_LLH_2_8e0322(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e0322_INS_Pos_LLH_Longitude = (Int32)((((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    crt_PT_8e0322_INS_Pos_LLH_Altitude = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_INS_Pos_LLH_2_8e0322 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Pos_LLH_1 (bus PT, frame ID 9306658) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Pos_LLH_1_8e0222(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_INS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_INS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_INS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_INS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accuracy_INS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
    }

    /* Pack signal Accuracy_INS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
    }

    /* Pack signal INS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8e0222_INS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Pos_LLH_1_8e0222 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Pos_LLH_1 (bus PT, frame ID 9306658) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Pos_LLH_1_8e0222(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude = (UInt8)((UInt8)m[1]);
    crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude = (UInt8)((UInt8)m[2]);
    crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude = (UInt8)((UInt8)m[3]);
    crt_PT_8e0222_INS_Pos_LLH_Latitude = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_INS_Pos_LLH_1_8e0222 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Heading_Gradient_2 (bus PT, frame ID 9311522) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Heading_Gradient_2_8e1522(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_INS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1522_Validity_INS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_INS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1522_Validity_INS_Gradient << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_INS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1522_Accuracy_INS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal INS_Heading_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8e1522_INS_Heading_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Accuracy_INS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1522_Accuracy_INS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
    }

    /* Pack signal INS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8e1522_INS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Heading_Gradient_2_8e1522 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Heading_Gradient_2 (bus PT, frame ID 9311522) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Heading_Gradient_2_8e1522(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e1522_Validity_INS_Heading = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e1522_Validity_INS_Gradient = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8e1522_Accuracy_INS_Heading = (UInt8)((UInt8)m[1]);
    crt_PT_8e1522_INS_Heading_2 = (UInt16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8e1522_Accuracy_INS_Gradient = (UInt8)((UInt8)m[4]);
    crt_PT_8e1522_INS_Gradient = (Int16)((((UInt16)m[6]) << 8) | m[5]);

} /* End of crt_unpack_PT_RT_SB_INS_Heading_Gradient_2_8e1522 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Heading_Gradient (bus PT, frame ID 9311266) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Heading_Gradient_8e1422(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;
    m[7] = 0xff;

    /* Pack signal Validity_INS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1422_Validity_INS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_INS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1422_Validity_INS_Gradient << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_INS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1422_Accuracy_INS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal INS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8e1422_INS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Accuracy_INS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e1422_Accuracy_INS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
    }

    /* Pack signal INS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8e1422_INS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Heading_Gradient_8e1422 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Heading_Gradient (bus PT, frame ID 9311266) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Heading_Gradient_8e1422(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e1422_Validity_INS_Heading = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e1422_Validity_INS_Gradient = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8e1422_Accuracy_INS_Heading = (UInt8)((UInt8)m[1]);
    crt_PT_8e1422_INS_Heading = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8e1422_Accuracy_INS_Gradient = (UInt8)((UInt8)m[4]);
    crt_PT_8e1422_INS_Gradient = (Int16)((((UInt16)m[6]) << 8) | m[5]);

} /* End of crt_unpack_PT_RT_SB_INS_Heading_Gradient_8e1422 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Status (bus PT, frame ID 9306146) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Status_8e0022(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal INS_Status. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0022_INS_Status;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Status_8e0022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Status (bus PT, frame ID 9306146) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Status_8e0022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e0022_INS_Status = (UInt8)((UInt8)m[0]);

} /* End of crt_unpack_PT_RT_SB_INS_Status_8e0022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_INS_Attitude (bus PT, frame ID 9306402) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_INS_Attitude_8e0122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0122_Validity_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0122_Validity_Pitch << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0122_Validity_Roll << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_Attitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8e0122_Accuracy_Attitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Attitude_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8e0122_Attitude_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Attitude_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8e0122_Attitude_Pitch;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Attitude_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8e0122_Attitude_Roll;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_INS_Attitude_8e0122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_INS_Attitude (bus PT, frame ID 9306402) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_INS_Attitude_8e0122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8e0122_Validity_Yaw = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8e0122_Validity_Pitch = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8e0122_Validity_Roll = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_8e0122_Accuracy_Attitude = (UInt8)((UInt8)m[1]);
    crt_PT_8e0122_Attitude_Yaw = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8e0122_Attitude_Pitch = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_8e0122_Attitude_Roll = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_INS_Attitude_8e0122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Output_Status (bus PT, frame ID 9240866) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Output_Status_8d0122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Validity_Status_Timestamp. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0122_Validity_Status_Timestamp;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Status_Analogue_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0122_Status_Analogue_1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (UInt8)~0x01;
        m[1] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Status_Analogue_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0122_Status_Analogue_2 << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (UInt8)~0x02;
        m[1] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Status_Analogue_3. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0122_Status_Analogue_3 << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (UInt8)~0x04;
        m[1] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Status_Analogue_4. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0122_Status_Analogue_4 << 3;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (UInt8)~0x08;
        m[1] |= (UInt8)(s & 0x08);
    }

    /* Pack signal Status_Pulse_Output. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0122_Status_Pulse_Output << 4;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (UInt8)~0x10;
        m[1] |= (UInt8)(s & 0x10);
    }

    /* Pack signal Status_Serial_Output_1. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0122_Status_Serial_Output_1 << 5;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (UInt8)~0x20;
        m[1] |= (UInt8)(s & 0x20);
    }

    /* Pack signal Status_Serial_Output_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0122_Status_Serial_Output_2 << 6;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (UInt8)~0x40;
        m[1] |= (UInt8)(s & 0x40);
    }

    /* Pack signal Status_Trigger. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0122_Status_Trigger << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] &= (UInt8)~0x80;
        m[1] |= (UInt8)(s & 0x80);
    }

    /* Pack signal GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8d0122_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Output_Status_8d0122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Output_Status (bus PT, frame ID 9240866) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Output_Status_8d0122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8d0122_Validity_Status_Timestamp = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8d0122_Status_Analogue_1 = (Bool)((UInt8)(m[1] & 0x01));
    crt_PT_8d0122_Status_Analogue_2 = (Bool)(((UInt8)(m[1] & 0x02)) >> 1);
    crt_PT_8d0122_Status_Analogue_3 = (Bool)(((UInt8)(m[1] & 0x04)) >> 2);
    crt_PT_8d0122_Status_Analogue_4 = (Bool)(((UInt8)(m[1] & 0x08)) >> 3);
    crt_PT_8d0122_Status_Pulse_Output = (Bool)(((UInt8)(m[1] & 0x10)) >> 4);
    crt_PT_8d0122_Status_Serial_Output_1 = (Bool)(((UInt8)(m[1] & 0x20)) >> 5);
    crt_PT_8d0122_Status_Serial_Output_2 = (Bool)(((UInt8)(m[1] & 0x40)) >> 6);
    crt_PT_8d0122_Status_Trigger = (Bool)(((UInt8)(m[1] & 0x80)) >> 7);
    crt_PT_8d0122_GPS_Time = (UInt32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_Output_Status_8d0122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Heading_Gradient_2 (bus PT, frame ID 9180706) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Heading_Gradient_2_8c1622(UInt8 m[])
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
        UInt8 s = (UInt8)crt_PT_8c1622_Validity_GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1622_Validity_GPS_Gradient << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1622_Accuracy_GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal GPS_Heading_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c1622_GPS_Heading_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1622_Accuracy_GPS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
    }

    /* Pack signal GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c1622_GPS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Heading_Gradient_2_8c1622 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient_2 (bus PT, frame ID 9180706) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Heading_Gradient_2_8c1622(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c1622_Validity_GPS_Heading = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c1622_Validity_GPS_Gradient = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c1622_Accuracy_GPS_Heading = (UInt8)((UInt8)m[1]);
    crt_PT_8c1622_GPS_Heading_2 = (UInt16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8c1622_Accuracy_GPS_Gradient = (UInt8)((UInt8)m[4]);
    crt_PT_8c1622_GPS_Gradient = (Int16)((((UInt16)m[6]) << 8) | m[5]);

} /* End of crt_unpack_PT_RT_SB_GPS_Heading_Gradient_2_8c1622 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Cumulative_Distance_2 (bus PT, frame ID 8397090) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Cumulative_Distance_2_802122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Cumulative_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_802122_Validity_Cumulative_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Cumulative_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_802122_Validity_Cumulative_Distance << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Cumulative_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_802122_Cumulative_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Cumulative_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_802122_Cumulative_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Cumulative_Distance_2_802122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_2 (bus PT, frame ID 8397090) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Cumulative_Distance_2_802122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_802122_Validity_Cumulative_Time = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_802122_Validity_Cumulative_Distance = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_802122_Cumulative_Time = (UInt32)((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]);
    crt_PT_802122_Cumulative_Distance = (UInt32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_Cumulative_Distance_2_802122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Cumulative_Distance_1 (bus PT, frame ID 8396834) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Cumulative_Distance_1_802022(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Cumulative_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_802022_Validity_Cumulative_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Cumulative_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_802022_Validity_Cumulative_Distance << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Cumulative_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_802022_Cumulative_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Cumulative_Distance. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_802022_Cumulative_Distance;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Cumulative_Distance_1_802022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_1 (bus PT, frame ID 8396834) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Cumulative_Distance_1_802022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_802022_Validity_Cumulative_Time = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_802022_Validity_Cumulative_Distance = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_802022_Cumulative_Time = (UInt32)((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]);
    crt_PT_802022_Cumulative_Distance = (UInt32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_Cumulative_Distance_1_802022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Trigger_Timestamp (bus PT, frame ID 9240610) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Trigger_Timestamp_8d0022(UInt8 m[])
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
        UInt8 s = (UInt8)crt_PT_8d0022_Validity_Trigger_Timestamp;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Accuracy_Trigger_Timestamp. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0022_Accuracy_Trigger_Timestamp;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Trigger_Number. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0022_Trigger_Number;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (UInt8)~0x7f;
        m[2] |= (UInt8)(s & 0x7f);
    }

    /* Pack signal Trigger_Timestamp_Type. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8d0022_Trigger_Timestamp_Type << 7;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] &= (UInt8)~0x80;
        m[2] |= (UInt8)(s & 0x80);
    }

    /* Pack signal GPS_High_Resolution_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt64 s = (UInt64)crt_PT_8d0022_GPS_High_Resolution_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Trigger_Timestamp_8d0022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Trigger_Timestamp (bus PT, frame ID 9240610) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Trigger_Timestamp_8d0022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8d0022_Validity_Trigger_Timestamp = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8d0022_Accuracy_Trigger_Timestamp = (UInt8)((UInt8)m[1]);
    crt_PT_8d0022_Trigger_Number = (UInt8)((UInt8)(m[2] & 0x7f));
    crt_PT_8d0022_Trigger_Timestamp_Type = (Bool)(((UInt8)(m[2] & 0x80)) >> 7);
    crt_PT_8d0022_GPS_High_Resolution_Time = (UInt64)((((((((((UInt64)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]) << 8) | m[3]);

} /* End of crt_unpack_PT_RT_SB_Trigger_Timestamp_8d0022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IMU06_Gyro_Rates (bus PT, frame ID 8388897) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IMU06_Gyro_Rates_800121(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Gyro_Rate_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800121_Validity_Gyro_Rate_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Gyro_Rate_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800121_Validity_Gyro_Rate_Pitch << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_Gyro_Rate_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800121_Validity_Gyro_Rate_Roll << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_Gyro_Rates. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800121_Accuracy_Gyro_Rates;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Gyro_Rate_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800121_Gyro_Rate_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Gyro_Rate_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800121_Gyro_Rate_Pitch;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Gyro_Rate_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800121_Gyro_Rate_Roll;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IMU06_Gyro_Rates_800121 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IMU06_Gyro_Rates (bus PT, frame ID 8388897) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IMU06_Gyro_Rates_800121(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_800121_Validity_Gyro_Rate_Yaw = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_800121_Validity_Gyro_Rate_Pitch = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_800121_Validity_Gyro_Rate_Roll = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_800121_Accuracy_Gyro_Rates = (UInt8)((UInt8)m[1]);
    crt_PT_800121_Gyro_Rate_Yaw = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_800121_Gyro_Rate_Pitch = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_800121_Gyro_Rate_Roll = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IMU06_Gyro_Rates_800121 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_IMU06_Accel (bus PT, frame ID 8388641) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_IMU06_Accel_800021(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800021_Validity_Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800021_Validity_Accel_Lateral << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800021_Validity_Accel_Vertical << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800021_Accuracy_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800021_Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800021_Accel_Lateral;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800021_Accel_Vertical;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_IMU06_Accel_800021 */
#endif



/**
 * Unpack the signals of inbound PDU RT_IMU06_Accel (bus PT, frame ID 8388641) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_IMU06_Accel_800021(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_800021_Validity_Accel_Longitudinal = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_800021_Validity_Accel_Lateral = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_800021_Validity_Accel_Vertical = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_800021_Accuracy_Accel = (UInt8)((UInt8)m[1]);
    crt_PT_800021_Accel_Longitudinal = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_800021_Accel_Lateral = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_800021_Accel_Vertical = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_IMU06_Accel_800021 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Speed (bus PT, frame ID 8392738) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Speed_801022(UInt8 m[])
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
        UInt8 s = (UInt8)crt_PT_801022_Validity_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Accuracy_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_801022_Accuracy_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_801022_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Speed_801022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Speed (bus PT, frame ID 8392738) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Speed_801022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_801022_Validity_Speed = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_801022_Accuracy_Speed = (UInt8)((UInt8)m[1]);
    crt_PT_801022_Speed = (Int32)((((((((UInt32)m[5]) << 8) | m[4]) << 8) | m[3]) << 8) | m[2]);

} /* End of crt_unpack_PT_RT_SB_Speed_801022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_RTK_Slip (bus PT, frame ID 9183522) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_RTK_Slip_8c2122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_RTK_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c2122_Validity_RTK_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_RTK_Squat. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c2122_Validity_RTK_Squat << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_RTK_Baseline. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c2122_Validity_RTK_Baseline << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_RTK_Baseline. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c2122_Accuracy_RTK_Baseline;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal RTK_Slip. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c2122_RTK_Slip;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal RTK_Squat. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c2122_RTK_Squat;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal RTK_Baseline. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c2122_RTK_Baseline;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_RTK_Slip_8c2122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_RTK_Slip (bus PT, frame ID 9183522) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_RTK_Slip_8c2122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c2122_Validity_RTK_Slip = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c2122_Validity_RTK_Squat = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c2122_Validity_RTK_Baseline = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_8c2122_Accuracy_RTK_Baseline = (UInt8)((UInt8)m[1]);
    crt_PT_8c2122_RTK_Slip = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8c2122_RTK_Squat = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_8c2122_RTK_Baseline = (UInt16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_RTK_Slip_8c2122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_RTK_Attitude (bus PT, frame ID 9183266) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_RTK_Attitude_8c2022(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_RTK_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c2022_Validity_RTK_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_RTK_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c2022_Validity_RTK_Pitch << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_RTK_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c2022_Validity_RTK_Roll << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_RTK_Attitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c2022_Accuracy_RTK_Attitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal RTK_Attitude_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c2022_RTK_Attitude_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal RTK_Attitude_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c2022_RTK_Attitude_Pitch;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal RTK_Attitude_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c2022_RTK_Attitude_Roll;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_RTK_Attitude_8c2022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_RTK_Attitude (bus PT, frame ID 9183266) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_RTK_Attitude_8c2022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c2022_Validity_RTK_Yaw = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c2022_Validity_RTK_Pitch = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c2022_Validity_RTK_Roll = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_8c2022_Accuracy_RTK_Attitude = (UInt8)((UInt8)m[1]);
    crt_PT_8c2022_RTK_Attitude_Yaw = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8c2022_RTK_Attitude_Pitch = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_8c2022_RTK_Attitude_Roll = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_RTK_Attitude_8c2022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Mcycle_Lean (bus PT, frame ID 9187362) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Mcycle_Lean_8c3022(UInt8 m[])
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
        UInt8 s = (UInt8)crt_PT_8c3022_Validity_GPS_Lateral_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Mcycle_Lean. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c3022_Validity_GPS_Mcycle_Lean << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Lateral_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c3022_Accuracy_GPS_Lateral_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal GPS_Lateral_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c3022_GPS_Lateral_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_Mcycle_Lean_Angle. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c3022_GPS_Mcycle_Lean_Angle;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Mcycle_Lean_8c3022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Mcycle_Lean (bus PT, frame ID 9187362) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Mcycle_Lean_8c3022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c3022_Validity_GPS_Lateral_Accel = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c3022_Validity_GPS_Mcycle_Lean = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c3022_Accuracy_GPS_Lateral_Accel = (UInt8)((UInt8)m[1]);
    crt_PT_8c3022_GPS_Lateral_Accel = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8c3022_GPS_Mcycle_Lean_Angle = (Int16)((((UInt16)m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_GPS_Mcycle_Lean_8c3022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Status (bus PT, frame ID 9175074) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Status_8c0022(UInt8 m[])
{

    /* Pack signal GPS_Status. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0022_GPS_Status;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
    }

    /* Pack signal Firmware_Version_Major. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0022_Firmware_Version_Major;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Firmware_Version_Intermediate. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0022_Firmware_Version_Intermediate;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
    }

    /* Pack signal Firmware_Version_Minor. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0022_Firmware_Version_Minor;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_nSv. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0022_GPS_nSv;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
    }

    /* Pack signal GPS_nSv_2. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0022_GPS_nSv_2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
    }

    /* Pack signal GPS_nSv_RTK. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0022_GPS_nSv_RTK;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
    }

    /* Pack signal RTK_Status. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0022_RTK_Status;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Status_8c0022 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Status (bus PT, frame ID 9175074) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Status_8c0022(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c0022_GPS_Status = (UInt8)((UInt8)m[0]);
    crt_PT_8c0022_Firmware_Version_Major = (UInt8)((UInt8)m[1]);
    crt_PT_8c0022_Firmware_Version_Intermediate = (UInt8)((UInt8)m[2]);
    crt_PT_8c0022_Firmware_Version_Minor = (UInt8)((UInt8)m[3]);
    crt_PT_8c0022_GPS_nSv = (UInt8)((UInt8)m[4]);
    crt_PT_8c0022_GPS_nSv_2 = (UInt8)((UInt8)m[5]);
    crt_PT_8c0022_GPS_nSv_RTK = (UInt8)((UInt8)m[6]);
    crt_PT_8c0022_RTK_Status = (UInt8)((UInt8)m[7]);

} /* End of crt_unpack_PT_RT_SB_GPS_Status_8c0022 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_2 (bus PT, frame ID 9176354) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Pos_ECEF_2_8c0522(UInt8 m[])
{

    /* Pack signal GPS_Pos_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0522_GPS_Pos_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_Pos_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0522_GPS_Pos_ECEF_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Pos_ECEF_2_8c0522 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_2 (bus PT, frame ID 9176354) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Pos_ECEF_2_8c0522(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c0522_GPS_Pos_ECEF_Y = (Int32)((((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    crt_PT_8c0522_GPS_Pos_ECEF_Z = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_GPS_Pos_ECEF_2_8c0522 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_1 (bus PT, frame ID 9176098) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Pos_ECEF_1_8c0422(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Pos_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0422_Validity_GPS_Pos_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Pos_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_GPS_Pos_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_GPS_Pos_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Pos_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Pos_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_Pos_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0422_GPS_Pos_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Pos_ECEF_1_8c0422 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_1 (bus PT, frame ID 9176098) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Pos_ECEF_1_8c0422(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c0422_Validity_GPS_Pos_ECEF_X = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X = (UInt8)((UInt8)m[1]);
    crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y = (UInt8)((UInt8)m[2]);
    crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z = (UInt8)((UInt8)m[3]);
    crt_PT_8c0422_GPS_Pos_ECEF_X = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_GPS_Pos_ECEF_1_8c0422 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_LLH_2 (bus PT, frame ID 9175842) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Pos_LLH_2_8c0322(UInt8 m[])
{

    /* Pack signal GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0322_GPS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] = (UInt8)s;
        s >>= 8;
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0322_GPS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Pos_LLH_2_8c0322 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_2 (bus PT, frame ID 9175842) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Pos_LLH_2_8c0322(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c0322_GPS_Pos_LLH_Longitude = (Int32)((((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) | m[0]);
    crt_PT_8c0322_GPS_Pos_LLH_Altitude = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_GPS_Pos_LLH_2_8c0322 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Pos_LLH_1 (bus PT, frame ID 9175586) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Pos_LLH_1_8c0222(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Longitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Pos_LLH_Altitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_Pos_LLH_Latitude. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c0222_GPS_Pos_LLH_Latitude;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Pos_LLH_1_8c0222 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_1 (bus PT, frame ID 9175586) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Pos_LLH_1_8c0222(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude = (UInt8)((UInt8)m[1]);
    crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude = (UInt8)((UInt8)m[2]);
    crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude = (UInt8)((UInt8)m[3]);
    crt_PT_8c0222_GPS_Pos_LLH_Latitude = (Int32)((((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) | m[4]);

} /* End of crt_unpack_PT_RT_SB_GPS_Pos_LLH_1_8c0222 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Heading_Gradient (bus PT, frame ID 9180450) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Heading_Gradient_8c1522(UInt8 m[])
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
        UInt8 s = (UInt8)crt_PT_8c1522_Validity_GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1522_Validity_GPS_Gradient << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1522_Accuracy_GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal GPS_Heading. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c1522_GPS_Heading;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1522_Accuracy_GPS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
    }

    /* Pack signal GPS_Gradient. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_8c1522_GPS_Gradient;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Heading_Gradient_8c1522 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient (bus PT, frame ID 9180450) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Heading_Gradient_8c1522(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c1522_Validity_GPS_Heading = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c1522_Validity_GPS_Gradient = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c1522_Accuracy_GPS_Heading = (UInt8)((UInt8)m[1]);
    crt_PT_8c1522_GPS_Heading = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_8c1522_Accuracy_GPS_Gradient = (UInt8)((UInt8)m[4]);
    crt_PT_8c1522_GPS_Gradient = (Int16)((((UInt16)m[6]) << 8) | m[5]);

} /* End of crt_unpack_PT_RT_SB_GPS_Heading_Gradient_8c1522 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_2 (bus PT, frame ID 9180194) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Vel_ECEF_2_8c1422(UInt8 m[])
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
        UInt8 s = (UInt8)crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Vel_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal GPS_Vel_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c1422_GPS_Vel_ECEF_Y << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
        s >>= 8;
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_Vel_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c1422_GPS_Vel_ECEF_Z << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Vel_ECEF_2_8c1422 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_2 (bus PT, frame ID 9180194) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Vel_ECEF_2_8c1422(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_8c1422_GPS_Vel_ECEF_Y = (Int32)((Int32)(((((((UInt32)m[3]) << 8) | m[2]) << 8) | m[1]) << 8) >> 8);
    crt_PT_8c1422_GPS_Vel_ECEF_Z = (Int32)((Int32)(((((((UInt32)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_GPS_Vel_ECEF_2_8c1422 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_1 (bus PT, frame ID 9179938) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Vel_ECEF_1_8c1322(UInt8 m[])
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
        UInt8 s = (UInt8)crt_PT_8c1322_Validity_GPS_Vel_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Accuracy_GPS_Vel_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Vel_ECEF_Y. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
    }

    /* Pack signal Accuracy_GPS_Vel_ECEF_Z. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[3] = (UInt8)s;
    }

    /* Pack signal GPS_Vel_ECEF_X. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_8c1322_GPS_Vel_ECEF_X << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Vel_ECEF_1_8c1322 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_1 (bus PT, frame ID 9179938) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Vel_ECEF_1_8c1322(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_8c1322_Validity_GPS_Vel_ECEF_X = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X = (UInt8)((UInt8)m[1]);
    crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y = (UInt8)((UInt8)m[2]);
    crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z = (UInt8)((UInt8)m[3]);
    crt_PT_8c1322_GPS_Vel_ECEF_X = (Int32)((Int32)(((((((UInt32)m[6]) << 8) | m[5]) << 8) | m[4]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_GPS_Vel_ECEF_1_8c1322 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_NED_2 (bus PT, frame ID 0) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Vel_NED_2_000(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    memset(m, /* value */ 0xff, /* noBytes */ 8);

    /* Pack signal Validity_GPS_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_000_Validity_GPS_Vel_NED_D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Accuracy_GPS_Vel_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_000_Accuracy_GPS_Vel_D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal GPS_Vel_NED_D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_000_GPS_Vel_NED_D << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Vel_NED_2_000 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_NED_2 (bus PT, frame ID 0) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Vel_NED_2_000(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_000_Validity_GPS_Vel_NED_D = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_000_Accuracy_GPS_Vel_D = (UInt8)((UInt8)m[1]);
    crt_PT_000_GPS_Vel_NED_D = (Int32)((Int32)(((((((UInt32)m[4]) << 8) | m[3]) << 8) | m[2]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_GPS_Vel_NED_2_000 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Vel_NED_1 (bus PT, frame ID 536870911) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Vel_NED_1_1fffffff(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Vel_NED_N. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_1fffffff_Validity_GPS_Vel_NED_N;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Vel_NED_E. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_1fffffff_Validity_GPS_Vel_NED_E << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Vel_NE. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_1fffffff_Accuracy_GPS_Vel_NE;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal GPS_Vel_NED_N. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_1fffffff_GPS_Vel_NED_N << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
    }

    /* Pack signal GPS_Vel_NED_E. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_1fffffff_GPS_Vel_NED_E << (8-8);

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Vel_NED_1_1fffffff */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Vel_NED_1 (bus PT, frame ID 536870911) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Vel_NED_1_1fffffff(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_1fffffff_Validity_GPS_Vel_NED_N = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_1fffffff_Validity_GPS_Vel_NED_E = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_1fffffff_Accuracy_GPS_Vel_NE = (UInt8)((UInt8)m[1]);
    crt_PT_1fffffff_GPS_Vel_NED_N = (Int32)((Int32)(((((((UInt32)m[4]) << 8) | m[3]) << 8) | m[2]) << 8) >> 8);
    crt_PT_1fffffff_GPS_Vel_NED_E = (Int32)((Int32)(((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]) << 8) >> 8);

} /* End of crt_unpack_PT_RT_SB_GPS_Vel_NED_1_1fffffff */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Speed (bus PT, frame ID 1818) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Speed_71a(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Speed_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_71a_Validity_GPS_Speed_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Speed_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_71a_Validity_GPS_Speed_3D << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Speed. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_71a_Accuracy_GPS_Speed;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal GPS_Speed_2D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_71a_GPS_Speed_2D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
    }

    /* Pack signal GPS_Speed_3D. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_71a_GPS_Speed_3D;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[5] = (UInt8)s;
        s >>= 8;
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Speed_71a */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Speed (bus PT, frame ID 1818) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Speed_71a(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_71a_Validity_GPS_Speed_2D = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_71a_Validity_GPS_Speed_3D = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_71a_Accuracy_GPS_Speed = (UInt8)((UInt8)m[1]);
    crt_PT_71a_GPS_Speed_2D = (UInt32)((((((UInt32)m[4]) << 8) | m[3]) << 8) | m[2]);
    crt_PT_71a_GPS_Speed_3D = (UInt32)((((((UInt32)m[7]) << 8) | m[6]) << 8) | m[5]);

} /* End of crt_unpack_PT_RT_SB_GPS_Speed_71a */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_GPS_Time (bus PT, frame ID 2047) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_GPS_Time_7ff(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_7ff_Validity_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_GPS_Week. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_7ff_Validity_GPS_Week << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Accuracy_GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_7ff_Accuracy_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal GPS_Time. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt32 s = (UInt32)crt_PT_7ff_GPS_Time;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
        s >>= 8;
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal GPS_Week. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_7ff_GPS_Week;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_GPS_Time_7ff */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_GPS_Time (bus PT, frame ID 2047) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_GPS_Time_7ff(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_7ff_Validity_GPS_Time = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_7ff_Validity_GPS_Week = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_7ff_Accuracy_GPS_Time = (UInt8)((UInt8)m[1]);
    crt_PT_7ff_GPS_Time = (UInt32)((((((((UInt32)m[5]) << 8) | m[4]) << 8) | m[3]) << 8) | m[2]);
    crt_PT_7ff_GPS_Week = (UInt16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_GPS_Time_7ff */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Accel (bus PT, frame ID 290) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Accel_122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_122_Validity_Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_122_Validity_Accel_Lateral << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_122_Validity_Accel_Vertical << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_Accel. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_122_Accuracy_Accel;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Accel_Longitudinal. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_122_Accel_Longitudinal;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Accel_Lateral. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_122_Accel_Lateral;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Accel_Vertical. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_122_Accel_Vertical;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Accel_122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Accel (bus PT, frame ID 290) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Accel_122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_122_Validity_Accel_Longitudinal = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_122_Validity_Accel_Lateral = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_122_Validity_Accel_Vertical = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_122_Accuracy_Accel = (UInt8)((UInt8)m[1]);
    crt_PT_122_Accel_Longitudinal = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_122_Accel_Lateral = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_122_Accel_Vertical = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_Accel_122 */



#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/**
 * Pack the signals of inbound PDU RT_SB_Gyro_Rates (bus PT, frame ID 8388898) into a
 * byte array of 8 Byte.\n
 *   The signal values are read from the global signal interface.
 * @param m
 *   The byte array. The packed signal values will be found in this array after return.
 * Unused bits will be set to zero.
 */

void crt_pack_PT_RT_SB_Gyro_Rates_800122(UInt8 m[])
{
    /* The further commands will partly use bit clear and set commands to write the signal
       values. Those bytes, which are not entirely occupied by the signals are initialized
       as 0xff in order to finally have ones in all unused payload bit positions. */
    m[0] = 0xff;

    /* Pack signal Validity_Gyro_Rate_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800122_Validity_Gyro_Rate_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x01;
        m[0] |= (UInt8)(s & 0x01);
    }

    /* Pack signal Validity_Gyro_Rate_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800122_Validity_Gyro_Rate_Pitch << 1;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x02;
        m[0] |= (UInt8)(s & 0x02);
    }

    /* Pack signal Validity_Gyro_Rate_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800122_Validity_Gyro_Rate_Roll << 2;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[0] &= (UInt8)~0x04;
        m[0] |= (UInt8)(s & 0x04);
    }

    /* Pack signal Accuracy_Gyro_Rates. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt8 s = (UInt8)crt_PT_800122_Accuracy_Gyro_Rates;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[1] = (UInt8)s;
    }

    /* Pack signal Gyro_Rate_Yaw. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800122_Gyro_Rate_Yaw;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[2] = (UInt8)s;
        s >>= 8;
        m[3] = (UInt8)s;
    }

    /* Pack signal Gyro_Rate_Pitch. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800122_Gyro_Rate_Pitch;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[4] = (UInt8)s;
        s >>= 8;
        m[5] = (UInt8)s;
    }

    /* Pack signal Gyro_Rate_Roll. */
    {
        /* Assign the signal value to a temporary variable, where the signal value's bits
           have the same byte-relative position as in the final, packed PDU. */
        UInt16 s = (UInt16)crt_PT_800122_Gyro_Rate_Roll;

        /* Transfer all bytes of the temporary variable into the PDU. */
        m[6] = (UInt8)s;
        s >>= 8;
        m[7] = (UInt8)s;
    }
} /* End of crt_pack_PT_RT_SB_Gyro_Rates_800122 */
#endif



/**
 * Unpack the signals of inbound PDU RT_SB_Gyro_Rates (bus PT, frame ID 8388898) from
 * a byte array of 8 Byte.\n
 *   The signal values are written into the global signal interface.
 * @param m
 *   The byte array. The signal values are extracted from this array.
 */

void crt_unpack_PT_RT_SB_Gyro_Rates_800122(const UInt8 m[])
{
    /* Decode all normal, not multiplexed signals. */
    crt_PT_800122_Validity_Gyro_Rate_Yaw = (Bool)((UInt8)(m[0] & 0x01));
    crt_PT_800122_Validity_Gyro_Rate_Pitch = (Bool)(((UInt8)(m[0] & 0x02)) >> 1);
    crt_PT_800122_Validity_Gyro_Rate_Roll = (Bool)(((UInt8)(m[0] & 0x04)) >> 2);
    crt_PT_800122_Accuracy_Gyro_Rates = (UInt8)((UInt8)m[1]);
    crt_PT_800122_Gyro_Rate_Yaw = (Int16)((((UInt16)m[3]) << 8) | m[2]);
    crt_PT_800122_Gyro_Rate_Pitch = (Int16)((((UInt16)m[5]) << 8) | m[4]);
    crt_PT_800122_Gyro_Rate_Roll = (Int16)((((UInt16)m[7]) << 8) | m[6]);

} /* End of crt_unpack_PT_RT_SB_Gyro_Rates_800122 */

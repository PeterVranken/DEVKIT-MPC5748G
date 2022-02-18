#ifndef CRT_CANRT_DEFINED
#define CRT_CANRT_DEFINED
/**
 * @file crt_canRT.h
 * Global interface of CAN pack/unpack functions for cluster raceCar.
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

#include "types.h"


/*
 * Defines
 */

#ifndef CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS
/** Normally, a pack function is generated for sent PDUs only. If this define is set to a
    value other than 0 then a pack function is generated for received PDUs, too. */
# define CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS 0
#endif

#ifndef CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS
/** Normally, an unpack function is generated for received PDUs only. If this define is set
    to a value other than 0 then an unpack function is generated for sent PDUs, too. */
# define CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS 0
#endif
 

/*
 * Type definitions
 */

 

/*
 * Data declarations
 */

/* The global signal variables. These variables form the interface towards the application
   software. They are filled by the unpack functions and the pack functions encode the
   values found in these variables in the PDUs. */
extern Bool crt_PT_0d7_Validity_INS_Vel_Forwards;
extern Bool crt_PT_0d7_Validity_INS_Vel_Sideways;
extern Bool crt_PT_0d7_Bit4;
extern Bool crt_PT_0d7_Bit7;
extern Bool crt_PT_0d7_Byte2_Bit0;
extern Int32 crt_PT_0d7_INS_Vel_Sideways_2D;
extern UInt8 crt_PT_0d7_Byte4_Bits67;
extern UInt8 crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1;
extern Int32 crt_PT_0d7_INS_Vel_Forwards_2D_org_m1;
extern UInt8 crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2;
extern Int32 crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2;
extern UInt16 crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3;
extern Int16 crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3;
extern Bool crt_PT_801024_Validity_Speed;
extern UInt8 crt_PT_801024_Accuracy_Speed;
extern UInt8 crt_PT_801024_Direction;
extern Int32 crt_PT_801024_Speed;
extern Bool crt_PT_8c0124_Validity_GPS_Time;
extern Bool crt_PT_8c0124_Validity_GPS_Week;
extern UInt8 crt_PT_8c0124_Accuracy_GPS_Time;
extern UInt32 crt_PT_8c0124_GPS_Time;
extern UInt16 crt_PT_8c0124_GPS_Week;
extern Int32 crt_PT_8c0324_GPS_Pos_LLH_Longitude;
extern Int32 crt_PT_8c0324_GPS_Pos_LLH_Altitude;
extern Bool crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude;
extern Bool crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude;
extern Bool crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude;
extern UInt8 crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude;
extern UInt8 crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude;
extern UInt8 crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude;
extern Int32 crt_PT_8c0224_GPS_Pos_LLH_Latitude;
extern Bool crt_PT_4d2_Validity_GPS_Speed_2D;
extern Bool crt_PT_4d2_Validity_GPS_Speed_3D;
extern UInt8 crt_PT_4d2_Accuracy_GPS_Speed;
extern UInt32 crt_PT_4d2_GPS_Speed_2D;
extern UInt32 crt_PT_4d2_GPS_Speed_3D;
extern Int16 crt_PT_910725_IR_Temperature_7; /* Signal is not used. */
extern Int16 crt_PT_980825_IR_Temperature_29;
extern Int16 crt_PT_980825_IR_Temperature_30;
extern Int16 crt_PT_980825_IR_Temperature_31;
extern Int16 crt_PT_980825_IR_Temperature_32;
extern Int16 crt_PT_980625_IR_Temperature_21;
extern Int16 crt_PT_980625_IR_Temperature_22;
extern Int16 crt_PT_980625_IR_Temperature_23;
extern Int16 crt_PT_980625_IR_Temperature_24;
extern Int16 crt_PT_980425_IR_Temperature_13;
extern Int16 crt_PT_980425_IR_Temperature_14;
extern Int16 crt_PT_980425_IR_Temperature_15;
extern Int16 crt_PT_980425_IR_Temperature_16;
extern Int16 crt_PT_980225_IR_Temperature_5;
extern Int16 crt_PT_980225_IR_Temperature_6;
extern Int16 crt_PT_980225_IR_Temperature_7;
extern Int16 crt_PT_980225_IR_Temperature_8;
extern Int16 crt_PT_980725_IR_Temperature_25;
extern Int16 crt_PT_980725_IR_Temperature_26;
extern Int16 crt_PT_980725_IR_Temperature_27;
extern Int16 crt_PT_980725_IR_Temperature_28;
extern Int16 crt_PT_980525_IR_Temperature_17;
extern Int16 crt_PT_980525_IR_Temperature_18;
extern Int16 crt_PT_980525_IR_Temperature_19;
extern Int16 crt_PT_980525_IR_Temperature_20;
extern Int16 crt_PT_980325_IR_Temperature_9;
extern Int16 crt_PT_980325_IR_Temperature_10;
extern Int16 crt_PT_980325_IR_Temperature_11;
extern Int16 crt_PT_980325_IR_Temperature_12;
extern Int16 crt_PT_980125_IR_Temperature_1;
extern Int16 crt_PT_980125_IR_Temperature_2;
extern Int16 crt_PT_980125_IR_Temperature_3;
extern Int16 crt_PT_980125_IR_Temperature_4;
extern Int16 crt_PT_912025_IR_Temperature_32;
extern Int16 crt_PT_911f25_IR_Temperature_31;
extern Int16 crt_PT_911e25_IR_Temperature_30;
extern Int16 crt_PT_911d25_IR_Temperature_29;
extern Int16 crt_PT_911c25_IR_Temperature_28;
extern Int16 crt_PT_911b25_IR_Temperature_27;
extern Int16 crt_PT_911a25_IR_Temperature_26;
extern Int16 crt_PT_911925_IR_Temperature_25;
extern Int16 crt_PT_911825_IR_Temperature_24;
extern Int16 crt_PT_911625_IR_Temperature_22;
extern Int16 crt_PT_911725_IR_Temperature_23;
extern Int16 crt_PT_911525_IR_Temperature_21;
extern Int16 crt_PT_911425_IR_Temperature_20;
extern Int16 crt_PT_911325_IR_Temperature_19;
extern Int16 crt_PT_911225_IR_Temperature_18;
extern Int16 crt_PT_911025_IR_Temperature_16;
extern Int16 crt_PT_910f25_IR_Temperature_15;
extern Int16 crt_PT_910e25_IR_Temperature_14;
extern Int16 crt_PT_910d25_IR_Temperature_13;
extern Int16 crt_PT_910c25_IR_Temperature_12;
extern Int16 crt_PT_910b25_IR_Temperature_11;
extern Int16 crt_PT_910a25_IR_Temperature_10;
extern Int16 crt_PT_910825_IR_Temperature_8;
extern Int16 crt_PT_910925_IR_Temperature_9;
extern Int16 crt_PT_911125_IR_Temperature_17;
extern Int16 crt_PT_910625_IR_Temperature_6;
extern Int16 crt_PT_910525_IR_Temperature_5;
extern Int16 crt_PT_910425_IR_Temperature_4;
extern Int16 crt_PT_910325_IR_Temperature_3;
extern Int16 crt_PT_910225_IR_Temperature_2;
extern Int16 crt_PT_910125_IR_Temperature_1;
extern UInt8 crt_PT_910125_CRC; /* Signal is not used. */
extern Bool crt_PT_8d0722_Validity_Final_Speed;
extern UInt32 crt_PT_8d0722_Final_Speed;
extern Bool crt_PT_31a_Validity_Initial_Speed;
extern Bool crt_PT_31a_Validity_Initial_Heading;
extern UInt32 crt_PT_31a_Initial_Speed;
extern Int16 crt_PT_31a_Initial_Heading;
extern UInt8 crt_PT_31a_MFDD_Start_Threshold;
extern UInt8 crt_PT_31a_MFDD_End_Threshold;
extern UInt32 crt_PT_8d0522_Direct_Distance;
extern UInt32 crt_PT_8d0522_Path_Distance_2D;
extern Int32 crt_PT_8d0422_Forward_Distance;
extern Int32 crt_PT_8d0422_Deviation_Distance;
extern UInt32 crt_PT_8d0322_Path_Distance_3D;
extern Bool crt_PT_8d0222_Validity_MFDD;
extern Bool crt_PT_8d0222_Validity_Average_Accel;
extern Bool crt_PT_8d0222_Validity_Triggered_Time;
extern Int16 crt_PT_8d0222_MFDD;
extern Int16 crt_PT_8d0222_Average_Accel;
extern UInt32 crt_PT_8d0222_Triggered_Time;
extern UInt32 crt_PT_960c24_Measured_Time_12; /* Signal is not used. */
extern UInt32 crt_PT_960b24_Measured_Time_11;
extern UInt32 crt_PT_960a24_Measured_Time_10;
extern UInt32 crt_PT_960924_Measured_Time_9;
extern UInt32 crt_PT_960824_Measured_Time_8;
extern UInt32 crt_PT_960724_Measured_Time_7;
extern UInt32 crt_PT_960624_Measured_Time_6;
extern UInt32 crt_PT_960524_Measured_Time_5;
extern UInt32 crt_PT_960424_Measured_Time_4;
extern UInt32 crt_PT_960324_Measured_Time_3;
extern UInt32 crt_PT_960224_Measured_Time_2;
extern UInt32 crt_PT_960124_Measured_Time_1;
extern UInt16 crt_PT_950c24_RPM;
extern UInt16 crt_PT_950b24_Frequency_4;
extern UInt16 crt_PT_950a24_Frequency_3;
extern UInt16 crt_PT_950924_Frequency_2;
extern UInt16 crt_PT_970324_Misc_3;
extern UInt16 crt_PT_970224_Misc_2;
extern UInt16 crt_PT_970124_Misc_1;
extern UInt16 crt_PT_941f24_AUX_31;
extern UInt16 crt_PT_941e24_AUX_30;
extern UInt16 crt_PT_941d24_AUX_29;
extern UInt16 crt_PT_941c24_AUX_28;
extern UInt16 crt_PT_941b24_AUX_27;
extern UInt16 crt_PT_941a24_AUX_26;
extern UInt16 crt_PT_941924_AUX_25;
extern UInt16 crt_PT_941824_AUX_24;
extern UInt16 crt_PT_941724_AUX_23;
extern UInt16 crt_PT_941624_AUX_22;
extern UInt16 crt_PT_941524_AUX_21;
extern UInt16 crt_PT_941424_AUX_20;
extern UInt16 crt_PT_941324_AUX_19;
extern UInt16 crt_PT_941224_AUX_18;
extern UInt16 crt_PT_941124_AUX_17;
extern UInt16 crt_PT_941024_AUX_16;
extern UInt16 crt_PT_940f24_AUX_15;
extern UInt16 crt_PT_940e24_AUX_14;
extern UInt16 crt_PT_940d24_AUX_13;
extern UInt16 crt_PT_940c24_AUX_12;
extern UInt16 crt_PT_940b24_AUX_11;
extern UInt16 crt_PT_940924_AUX_9;
extern UInt16 crt_PT_940a24_AUX_10;
extern UInt16 crt_PT_940824_AUX_8;
extern UInt16 crt_PT_940724_AUX_7;
extern UInt16 crt_PT_940624_AUX_6;
extern UInt16 crt_PT_940524_AUX_5;
extern UInt16 crt_PT_940424_AUX_4;
extern UInt16 crt_PT_940324_AUX_3;
extern UInt16 crt_PT_940224_AUX_2;
extern UInt16 crt_PT_940124_AUX_1;
extern UInt32 crt_PT_900524_Pressure_5;
extern UInt32 crt_PT_900424_Pressure_4;
extern UInt32 crt_PT_900324_Pressure_3;
extern UInt32 crt_PT_900224_Pressure_2;
extern UInt32 crt_PT_900124_Pressure_1;
extern Int16 crt_PT_920324_Angle_3;
extern Int16 crt_PT_920224_Angle_2;
extern Int16 crt_PT_920124_Angle_1;
extern Int16 crt_PT_911924_Temperature_25;
extern Int16 crt_PT_911824_Temperature_24;
extern Int16 crt_PT_911724_Temperature_23;
extern Int16 crt_PT_911624_Temperature_22;
extern Int16 crt_PT_911524_Temperature_21;
extern Int16 crt_PT_911424_Temperature_20;
extern Int16 crt_PT_911324_Temperature_19;
extern Int16 crt_PT_911224_Temperature_18;
extern Int16 crt_PT_911124_Temperature_17;
extern Int16 crt_PT_911024_Temperature_16;
extern Int16 crt_PT_910f24_Temperature_15;
extern Int16 crt_PT_910e24_Temperature_14;
extern Int16 crt_PT_910d24_Temperature_13;
extern Int16 crt_PT_910c24_Temperature_12;
extern Int16 crt_PT_910b24_Temperature_11;
extern Int16 crt_PT_910a24_Temperature_10;
extern Int16 crt_PT_910924_Temperature_9;
extern Int16 crt_PT_910824_Temperature_8;
extern Int16 crt_PT_910724_Temperature_7;
extern Int16 crt_PT_910624_Temperature_6;
extern Int16 crt_PT_910524_Temperature_5;
extern Int16 crt_PT_910424_Temperature_4;
extern Int16 crt_PT_910324_Temperature_3;
extern Int16 crt_PT_910224_Temperature_2;
extern Int16 crt_PT_910124_Temperature_1;
extern UInt16 crt_PT_821f24_Analog_32;
extern UInt16 crt_PT_821e24_Analog_31;
extern UInt16 crt_PT_821d24_Analog_30;
extern UInt16 crt_PT_821c24_Analog_29;
extern UInt16 crt_PT_821b24_Analog_28;
extern UInt16 crt_PT_821a24_Analog_27;
extern UInt16 crt_PT_821924_Analog_26;
extern UInt16 crt_PT_821824_Analog_25;
extern UInt16 crt_PT_820e24_Analog_15;
extern UInt16 crt_PT_820d24_Analog_14;
extern UInt16 crt_PT_821024_Analog_17;
extern UInt16 crt_PT_821724_Analog_24;
extern UInt16 crt_PT_821624_Analog_23;
extern UInt16 crt_PT_821524_Analog_22;
extern UInt16 crt_PT_821424_Analog_21;
extern UInt16 crt_PT_821324_Analog_20;
extern UInt16 crt_PT_821224_Analog_19;
extern UInt16 crt_PT_820f24_Analog_16;
extern UInt16 crt_PT_821124_Analog_18;
extern UInt16 crt_PT_820b24_Analog_12;
extern UInt16 crt_PT_820a24_Analog_11;
extern UInt16 crt_PT_820924_Analog_10;
extern UInt16 crt_PT_820824_Analog_9;
extern UInt16 crt_PT_820724_Analog_8;
extern UInt16 crt_PT_820624_Analog_7;
extern UInt16 crt_PT_820524_Analog_6;
extern UInt16 crt_PT_820424_Analog_5;
extern UInt16 crt_PT_820324_Analog_4;
extern UInt16 crt_PT_820224_Analog_3;
extern UInt16 crt_PT_820124_Analog_2;
extern UInt16 crt_PT_820024_Analog_1;
extern Bool crt_PT_800024_Validity_Accel_Longitudinal;
extern Bool crt_PT_800024_Validity_Accel_Lateral;
extern Bool crt_PT_800024_Validity_Accel_Vertical;
extern UInt8 crt_PT_800024_SQC; /* Signal is not used. */
extern UInt8 crt_PT_800024_Accuracy_Accel;
extern Int16 crt_PT_800024_Accel_Longitudinal;
extern Int16 crt_PT_800024_Accel_Lateral;
extern Int16 crt_PT_800024_Accel_Vertical;
extern Int32 crt_PT_8f3222_Virtual_4_Vel_NED_D;
extern Int16 crt_PT_8f3222_Virtual_4_Heading;
extern Int16 crt_PT_8f3222_Virtual_4_Slip;
extern Int32 crt_PT_8f3122_Virtual_4_Vel_NED_N;
extern Int32 crt_PT_8f3122_Virtual_4_Vel_NED_E;
extern Int16 crt_PT_8f3022_Virtual_4_Offset_X;
extern Int16 crt_PT_8f3022_Virtual_4_Offset_Y;
extern Int16 crt_PT_8f3022_Virtual_4_Offset_Z;
extern Int32 crt_PT_8f2222_Virtual_3_Vel_NED_D;
extern Int16 crt_PT_8f2222_Virtual_3_Heading;
extern Int16 crt_PT_8f2222_Virtual_3_Slip;
extern Int32 crt_PT_8f2122_Virtual_3_Vel_NED_N;
extern Int32 crt_PT_8f2122_Virtual_3_Vel_NED_E;
extern Int16 crt_PT_8f2022_Virtual_3_Offset_X;
extern Int16 crt_PT_8f2022_Virtual_3_Offset_Y;
extern Int16 crt_PT_8f2022_Virtual_3_Offset_Z;
extern Int32 crt_PT_8f1222_Virtual_2_Vel_NED_D;
extern Int16 crt_PT_8f1222_Virtual_2_Heading;
extern Int16 crt_PT_8f1222_Virtual_2_Slip;
extern Int32 crt_PT_8f1122_Virtual_2_Vel_NED_N;
extern Int32 crt_PT_8f1122_Virtual_2_Vel_NED_E;
extern Int16 crt_PT_8f1022_Virtual_2_Offset_X;
extern Int16 crt_PT_8f1022_Virtual_2_Offset_Y;
extern Int16 crt_PT_8f1022_Virtual_2_Offset_Z;
extern Int32 crt_PT_8f0222_Virtual_1_Vel_NED_D;
extern Int16 crt_PT_8f0222_Virtual_1_Heading;
extern Int16 crt_PT_8f0222_Virtual_1_Slip;
extern Int32 crt_PT_8f0122_Virtual_1_Vel_NED_N;
extern Int32 crt_PT_8f0122_Virtual_1_Vel_NED_E;
extern Int16 crt_PT_8f0022_Virtual_1_Offset_X;
extern Int16 crt_PT_8f0022_Virtual_1_Offset_Y;
extern Int16 crt_PT_8f0022_Virtual_1_Offset_Z;
extern Bool crt_PT_8e1622_Validity_INS_Slip;
extern Bool crt_PT_8e1622_Validity_INS_Squat;
extern UInt8 crt_PT_8e1622_Accuracy_INS_Slip;
extern Int16 crt_PT_8e1622_INS_Slip;
extern UInt8 crt_PT_8e1622_Accuracy_INS_Squat;
extern Int16 crt_PT_8e1622_INS_Squat;
extern Bool crt_PT_8e1322_Validity_INS_Vel_ECEF_Y;
extern Bool crt_PT_8e1322_Validity_INS_Vel_ECEF_Z;
extern Int32 crt_PT_8e1322_INS_Vel_ECEF_Y;
extern Int32 crt_PT_8e1322_INS_Vel_ECEF_Z;
extern Bool crt_PT_8e1222_Validity_INS_Vel_ECEF_X;
extern UInt8 crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X;
extern UInt8 crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y;
extern UInt8 crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z;
extern Int32 crt_PT_8e1222_INS_Vel_ECEF_X;
extern Bool crt_PT_8e1122_Validity_INS_Vel_NED_D;
extern UInt8 crt_PT_8e1122_Accuracy_INS_Vel_D;
extern Int32 crt_PT_8e1122_INS_Vel_NED_D;
extern Bool crt_PT_8e1022_Validity_INS_Vel_NED_N;
extern Bool crt_PT_8e1022_Validity_INS_Vel_NED_E;
extern UInt8 crt_PT_8e1022_Accuracy_INS_Vel_NE;
extern Int32 crt_PT_8e1022_INS_Vel_NED_N;
extern Int32 crt_PT_8e1022_INS_Vel_NED_E;
extern Int32 crt_PT_8e0522_INS_Pos_ECEF_Y;
extern Int32 crt_PT_8e0522_INS_Pos_ECEF_Z;
extern Bool crt_PT_8e0422_Validity_INS_Pos_ECEF_X;
extern Bool crt_PT_8e0422_Validity_INS_Pos_ECEF_Y;
extern Bool crt_PT_8e0422_Validity_INS_Pos_ECEF_Z;
extern UInt8 crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X;
extern UInt8 crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y;
extern UInt8 crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z;
extern Int32 crt_PT_8e0422_INS_Pos_ECEF_X;
extern Int32 crt_PT_8e0322_INS_Pos_LLH_Longitude;
extern Int32 crt_PT_8e0322_INS_Pos_LLH_Altitude;
extern Bool crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude;
extern Bool crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude;
extern Bool crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude;
extern UInt8 crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude;
extern UInt8 crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude;
extern UInt8 crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude;
extern Int32 crt_PT_8e0222_INS_Pos_LLH_Latitude;
extern Bool crt_PT_8e1522_Validity_INS_Heading;
extern Bool crt_PT_8e1522_Validity_INS_Gradient;
extern UInt8 crt_PT_8e1522_Accuracy_INS_Heading;
extern UInt16 crt_PT_8e1522_INS_Heading_2;
extern UInt8 crt_PT_8e1522_Accuracy_INS_Gradient;
extern Int16 crt_PT_8e1522_INS_Gradient;
extern Bool crt_PT_8e1422_Validity_INS_Heading;
extern Bool crt_PT_8e1422_Validity_INS_Gradient;
extern UInt8 crt_PT_8e1422_Accuracy_INS_Heading;
extern Int16 crt_PT_8e1422_INS_Heading;
extern UInt8 crt_PT_8e1422_Accuracy_INS_Gradient;
extern Int16 crt_PT_8e1422_INS_Gradient;
extern UInt8 crt_PT_8e0022_INS_Status;
extern Bool crt_PT_8e0122_Validity_Yaw;
extern Bool crt_PT_8e0122_Validity_Pitch;
extern Bool crt_PT_8e0122_Validity_Roll;
extern UInt8 crt_PT_8e0122_Accuracy_Attitude;
extern Int16 crt_PT_8e0122_Attitude_Yaw;
extern Int16 crt_PT_8e0122_Attitude_Pitch;
extern Int16 crt_PT_8e0122_Attitude_Roll;
extern Bool crt_PT_8d0122_Validity_Status_Timestamp;
extern Bool crt_PT_8d0122_Status_Analogue_1;
extern Bool crt_PT_8d0122_Status_Analogue_2;
extern Bool crt_PT_8d0122_Status_Analogue_3;
extern Bool crt_PT_8d0122_Status_Analogue_4;
extern Bool crt_PT_8d0122_Status_Pulse_Output;
extern Bool crt_PT_8d0122_Status_Serial_Output_1;
extern Bool crt_PT_8d0122_Status_Serial_Output_2;
extern Bool crt_PT_8d0122_Status_Trigger;
extern UInt32 crt_PT_8d0122_GPS_Time;
extern Bool crt_PT_8c1622_Validity_GPS_Heading;
extern Bool crt_PT_8c1622_Validity_GPS_Gradient;
extern UInt8 crt_PT_8c1622_Accuracy_GPS_Heading;
extern UInt16 crt_PT_8c1622_GPS_Heading_2;
extern UInt8 crt_PT_8c1622_Accuracy_GPS_Gradient;
extern Int16 crt_PT_8c1622_GPS_Gradient;
extern Bool crt_PT_802122_Validity_Cumulative_Time;
extern Bool crt_PT_802122_Validity_Cumulative_Distance;
extern UInt32 crt_PT_802122_Cumulative_Time;
extern UInt32 crt_PT_802122_Cumulative_Distance;
extern Bool crt_PT_802022_Validity_Cumulative_Time;
extern Bool crt_PT_802022_Validity_Cumulative_Distance;
extern UInt32 crt_PT_802022_Cumulative_Time;
extern UInt32 crt_PT_802022_Cumulative_Distance;
extern Bool crt_PT_8d0022_Validity_Trigger_Timestamp;
extern UInt8 crt_PT_8d0022_Accuracy_Trigger_Timestamp;
extern UInt8 crt_PT_8d0022_Trigger_Number;
extern Bool crt_PT_8d0022_Trigger_Timestamp_Type;
extern UInt64 crt_PT_8d0022_GPS_High_Resolution_Time;
extern Bool crt_PT_800121_Validity_Gyro_Rate_Yaw;
extern Bool crt_PT_800121_Validity_Gyro_Rate_Pitch;
extern Bool crt_PT_800121_Validity_Gyro_Rate_Roll;
extern UInt8 crt_PT_800121_Accuracy_Gyro_Rates;
extern Int16 crt_PT_800121_Gyro_Rate_Yaw;
extern Int16 crt_PT_800121_Gyro_Rate_Pitch;
extern Int16 crt_PT_800121_Gyro_Rate_Roll;
extern Bool crt_PT_800021_Validity_Accel_Longitudinal;
extern Bool crt_PT_800021_Validity_Accel_Lateral;
extern Bool crt_PT_800021_Validity_Accel_Vertical;
extern UInt8 crt_PT_800021_Accuracy_Accel;
extern Int16 crt_PT_800021_Accel_Longitudinal;
extern Int16 crt_PT_800021_Accel_Lateral;
extern Int16 crt_PT_800021_Accel_Vertical;
extern Bool crt_PT_801022_Validity_Speed;
extern UInt8 crt_PT_801022_Accuracy_Speed;
extern Int32 crt_PT_801022_Speed;
extern Bool crt_PT_8c2122_Validity_RTK_Slip;
extern Bool crt_PT_8c2122_Validity_RTK_Squat;
extern Bool crt_PT_8c2122_Validity_RTK_Baseline;
extern UInt8 crt_PT_8c2122_Accuracy_RTK_Baseline;
extern Int16 crt_PT_8c2122_RTK_Slip;
extern Int16 crt_PT_8c2122_RTK_Squat;
extern UInt16 crt_PT_8c2122_RTK_Baseline;
extern Bool crt_PT_8c2022_Validity_RTK_Yaw;
extern Bool crt_PT_8c2022_Validity_RTK_Pitch;
extern Bool crt_PT_8c2022_Validity_RTK_Roll;
extern UInt8 crt_PT_8c2022_Accuracy_RTK_Attitude;
extern Int16 crt_PT_8c2022_RTK_Attitude_Yaw;
extern Int16 crt_PT_8c2022_RTK_Attitude_Pitch;
extern Int16 crt_PT_8c2022_RTK_Attitude_Roll;
extern Bool crt_PT_8c3022_Validity_GPS_Lateral_Accel;
extern Bool crt_PT_8c3022_Validity_GPS_Mcycle_Lean;
extern UInt8 crt_PT_8c3022_Accuracy_GPS_Lateral_Accel;
extern Int16 crt_PT_8c3022_GPS_Lateral_Accel;
extern Int16 crt_PT_8c3022_GPS_Mcycle_Lean_Angle;
extern UInt8 crt_PT_8c0022_GPS_Status;
extern UInt8 crt_PT_8c0022_Firmware_Version_Major;
extern UInt8 crt_PT_8c0022_Firmware_Version_Intermediate;
extern UInt8 crt_PT_8c0022_Firmware_Version_Minor;
extern UInt8 crt_PT_8c0022_GPS_nSv;
extern UInt8 crt_PT_8c0022_GPS_nSv_2;
extern UInt8 crt_PT_8c0022_GPS_nSv_RTK;
extern UInt8 crt_PT_8c0022_RTK_Status;
extern Int32 crt_PT_8c0522_GPS_Pos_ECEF_Y;
extern Int32 crt_PT_8c0522_GPS_Pos_ECEF_Z;
extern Bool crt_PT_8c0422_Validity_GPS_Pos_ECEF_X;
extern Bool crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y;
extern Bool crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z;
extern UInt8 crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X;
extern UInt8 crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y;
extern UInt8 crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z;
extern Int32 crt_PT_8c0422_GPS_Pos_ECEF_X;
extern Int32 crt_PT_8c0322_GPS_Pos_LLH_Longitude;
extern Int32 crt_PT_8c0322_GPS_Pos_LLH_Altitude;
extern Bool crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude;
extern Bool crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude;
extern Bool crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude;
extern UInt8 crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude;
extern UInt8 crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude;
extern UInt8 crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude;
extern Int32 crt_PT_8c0222_GPS_Pos_LLH_Latitude;
extern Bool crt_PT_8c1522_Validity_GPS_Heading;
extern Bool crt_PT_8c1522_Validity_GPS_Gradient;
extern UInt8 crt_PT_8c1522_Accuracy_GPS_Heading;
extern Int16 crt_PT_8c1522_GPS_Heading;
extern UInt8 crt_PT_8c1522_Accuracy_GPS_Gradient;
extern Int16 crt_PT_8c1522_GPS_Gradient;
extern Bool crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y;
extern Bool crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z;
extern Int32 crt_PT_8c1422_GPS_Vel_ECEF_Y;
extern Int32 crt_PT_8c1422_GPS_Vel_ECEF_Z;
extern Bool crt_PT_8c1322_Validity_GPS_Vel_ECEF_X;
extern UInt8 crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X;
extern UInt8 crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y;
extern UInt8 crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z;
extern Int32 crt_PT_8c1322_GPS_Vel_ECEF_X;
extern Bool crt_PT_000_Validity_GPS_Vel_NED_D;
extern UInt8 crt_PT_000_Accuracy_GPS_Vel_D;
extern Int32 crt_PT_000_GPS_Vel_NED_D;
extern Bool crt_PT_1fffffff_Validity_GPS_Vel_NED_N;
extern Bool crt_PT_1fffffff_Validity_GPS_Vel_NED_E;
extern UInt8 crt_PT_1fffffff_Accuracy_GPS_Vel_NE;
extern Int32 crt_PT_1fffffff_GPS_Vel_NED_N;
extern Int32 crt_PT_1fffffff_GPS_Vel_NED_E;
extern Bool crt_PT_71a_Validity_GPS_Speed_2D;
extern Bool crt_PT_71a_Validity_GPS_Speed_3D;
extern UInt8 crt_PT_71a_Accuracy_GPS_Speed;
extern UInt32 crt_PT_71a_GPS_Speed_2D;
extern UInt32 crt_PT_71a_GPS_Speed_3D;
extern Bool crt_PT_7ff_Validity_GPS_Time;
extern Bool crt_PT_7ff_Validity_GPS_Week;
extern UInt8 crt_PT_7ff_Accuracy_GPS_Time;
extern UInt32 crt_PT_7ff_GPS_Time;
extern UInt16 crt_PT_7ff_GPS_Week;
extern Bool crt_PT_122_Validity_Accel_Longitudinal;
extern Bool crt_PT_122_Validity_Accel_Lateral;
extern Bool crt_PT_122_Validity_Accel_Vertical;
extern UInt8 crt_PT_122_Accuracy_Accel;
extern Int16 crt_PT_122_Accel_Longitudinal;
extern Int16 crt_PT_122_Accel_Lateral;
extern Int16 crt_PT_122_Accel_Vertical;
extern Bool crt_PT_800122_Validity_Gyro_Rate_Yaw;
extern Bool crt_PT_800122_Validity_Gyro_Rate_Pitch;
extern Bool crt_PT_800122_Validity_Gyro_Rate_Roll;
extern UInt8 crt_PT_800122_Accuracy_Gyro_Rates;
extern Int16 crt_PT_800122_Gyro_Rate_Yaw;
extern Int16 crt_PT_800122_Gyro_Rate_Pitch;
extern Int16 crt_PT_800122_Gyro_Rate_Roll;
 

/*
 * Function declarations
 */

/* The global pack and unpack functions. These functions form the interface towards the basic
   software. */

/** Pack the signal values of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vel_Body_Axes_0d7(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vel_Body_Axes_0d7(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024)
    in the global signal interface into a byte array of 7 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Speed_801024(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024) from
    a byte array of 7 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Speed_801024(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_GPS_Time_8c0124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_GPS_Time_8c0124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_GPS_Pos_LLH_2_8c0324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_2_8c0324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_GPS_Pos_LLH_1_8c0224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_1_8c0224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_GPS_Speed_4d2(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_GPS_Speed_4d2(const UInt8 m[]);

/** Pack the signal values of unused PDU RT_IRTemp_Temp_7 (9504549, 0x910725)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_7_910725(UInt8 m[]);
#endif

/** Unpack the signals of unused PDU RT_IRTemp_Temp_7 (9504549, 0x910725) from
    a byte array of 2 Byte into the global signal interface. */
#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
void crt_unpack_PT_RT_IRTemp_Temp_7_910725(const UInt8 m[]);
#endif

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_RR_2 (9963557, 0x980825)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_RR_2_980825(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_RR_2 (9963557, 0x980825) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_RR_2_980825(const UInt8 m[]);

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625)
    in the global signal interface into a byte array of 8 Byte. */
void crt_pack_PT_RT_IRTemp_Temp_RL_2_980625(UInt8 m[]);

/** Unpack the signals of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625) from
    a byte array of 8 Byte into the global signal interface. */
#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
void crt_unpack_PT_RT_IRTemp_Temp_RL_2_980625(const UInt8 m[]);
#endif

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425)
    in the global signal interface into a byte array of 8 Byte. */
void crt_pack_PT_RT_IRTemp_Temp_FR_2_980425(UInt8 m[]);

/** Unpack the signals of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425) from
    a byte array of 8 Byte into the global signal interface. */
#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
void crt_unpack_PT_RT_IRTemp_Temp_FR_2_980425(const UInt8 m[]);
#endif

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_FL_2_980225(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_FL_2_980225(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_RR_1 (9963301, 0x980725)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_RR_1_980725(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_RR_1 (9963301, 0x980725) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_RR_1_980725(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_RL_1_980525(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_RL_1_980525(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_FR_1_980325(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_FR_1_980325(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_FL_1_980125(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_FL_1_980125(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_32 (9510949, 0x912025)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_32_912025(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_32 (9510949, 0x912025) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_32_912025(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_31 (9510693, 0x911f25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_31_911f25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_31 (9510693, 0x911f25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_31_911f25(const UInt8 m[]);

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25)
    in the global signal interface into a byte array of 2 Byte. */
void crt_pack_PT_RT_IRTemp_Temp_30_911e25(UInt8 m[]);

/** Unpack the signals of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25) from
    a byte array of 2 Byte into the global signal interface. */
#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
void crt_unpack_PT_RT_IRTemp_Temp_30_911e25(const UInt8 m[]);
#endif

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_29 (9510181, 0x911d25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_29_911d25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_29 (9510181, 0x911d25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_29_911d25(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_28 (9509925, 0x911c25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_28_911c25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_28 (9509925, 0x911c25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_28_911c25(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_27 (9509669, 0x911b25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_27_911b25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_27 (9509669, 0x911b25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_27_911b25(const UInt8 m[]);

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25)
    in the global signal interface into a byte array of 2 Byte. */
void crt_pack_PT_RT_IRTemp_Temp_26_911a25(UInt8 m[]);

/** Unpack the signals of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25) from
    a byte array of 2 Byte into the global signal interface. */
#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
void crt_unpack_PT_RT_IRTemp_Temp_26_911a25(const UInt8 m[]);
#endif

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_25 (9509157, 0x911925)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_25_911925(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_25 (9509157, 0x911925) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_25_911925(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_24 (9508901, 0x911825)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_24_911825(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_24 (9508901, 0x911825) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_24_911825(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_22 (9508389, 0x911625)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_22_911625(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_22 (9508389, 0x911625) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_22_911625(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_23 (9508645, 0x911725)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_23_911725(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_23 (9508645, 0x911725) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_23_911725(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_21 (9508133, 0x911525)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_21_911525(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_21 (9508133, 0x911525) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_21_911525(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_20 (9507877, 0x911425)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_20_911425(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_20 (9507877, 0x911425) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_20_911425(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_19 (9507621, 0x911325)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_19_911325(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_19 (9507621, 0x911325) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_19_911325(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_18 (9507365, 0x911225)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_18_911225(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_18 (9507365, 0x911225) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_18_911225(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_16 (9506853, 0x911025)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_16_911025(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_16 (9506853, 0x911025) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_16_911025(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_15 (9506597, 0x910f25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_15_910f25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_15 (9506597, 0x910f25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_15_910f25(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_14 (9506341, 0x910e25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_14_910e25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_14 (9506341, 0x910e25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_14_910e25(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_13 (9506085, 0x910d25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_13_910d25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_13 (9506085, 0x910d25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_13_910d25(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_12 (9505829, 0x910c25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_12_910c25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_12 (9505829, 0x910c25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_12_910c25(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_11 (9505573, 0x910b25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_11_910b25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_11 (9505573, 0x910b25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_11_910b25(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_10 (9505317, 0x910a25)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_10_910a25(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_10 (9505317, 0x910a25) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_10_910a25(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_8 (9504805, 0x910825)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_8_910825(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_8 (9504805, 0x910825) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_8_910825(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_9 (9505061, 0x910925)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_9_910925(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_9 (9505061, 0x910925) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_9_910925(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_17 (9507109, 0x911125)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_17_911125(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_17 (9507109, 0x911125) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_17_911125(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_6 (9504293, 0x910625)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_6_910625(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_6 (9504293, 0x910625) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_6_910625(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_5 (9504037, 0x910525)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_5_910525(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_5 (9504037, 0x910525) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_5_910525(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_4 (9503781, 0x910425)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_4_910425(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_4 (9503781, 0x910425) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_4_910425(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_3 (9503525, 0x910325)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_3_910325(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_3 (9503525, 0x910325) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_3_910325(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_2 (9503269, 0x910225)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_2_910225(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_2 (9503269, 0x910225) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_2_910225(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IRTemp_Temp_1_910125(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_IRTemp_Temp_1_910125(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Trig_Final_Condition_8d0722(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Trig_Final_Condition_8d0722(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Trig_Initial_Condition_31a(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Trig_Initial_Condition_31a(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Trig_Direct_Dist_8d0522(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Trig_Direct_Dist_8d0522(const UInt8 m[]);

/** Pack the signal values of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422)
    in the global signal interface into a byte array of 8 Byte. */
void crt_pack_PT_RT_SB_Trig_Forward_Dist_8d0422(UInt8 m[]);

/** Unpack the signals of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) from
    a byte array of 8 Byte into the global signal interface. */
#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
void crt_unpack_PT_RT_SB_Trig_Forward_Dist_8d0422(const UInt8 m[]);
#endif

/** Pack the signal values of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Trig_Path_Dist_8d0322(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Trig_Path_Dist_8d0322(const UInt8 m[]);

/** Pack the signal values of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222)
    in the global signal interface into a byte array of 8 Byte. */
void crt_pack_PT_RT_SB_Trig_Accel_8d0222(UInt8 m[]);

/** Unpack the signals of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222) from
    a byte array of 8 Byte into the global signal interface. */
#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
void crt_unpack_PT_RT_SB_Trig_Accel_8d0222(const UInt8 m[]);
#endif

/** Pack the signal values of unused PDU RT_DL1MK3_Measure_Time_12 (9833508, 0x960c24)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_12_960c24(UInt8 m[]);
#endif

/** Unpack the signals of unused PDU RT_DL1MK3_Measure_Time_12 (9833508, 0x960c24) from
    a byte array of 3 Byte into the global signal interface. */
#if CRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
void crt_unpack_PT_RT_DL1MK3_Measure_Time_12_960c24(const UInt8 m[]);
#endif

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_11_960b24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_11_960b24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_10_960a24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_10_960a24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_9_960924(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_9_960924(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_8_960824(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_8_960824(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_7_960724(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_7_960724(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_6_960624(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_6_960624(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_5_960524(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_5_960524(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_4_960424(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_4_960424(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_3_960324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_3_960324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_2_960224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_2_960224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Measure_Time_1_960124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Measure_Time_1_960124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_RPM_950c24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_RPM_950c24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Freq_4_950b24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Freq_4_950b24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Freq_3 (9767460, 0x950a24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Freq_3_950a24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Freq_3 (9767460, 0x950a24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Freq_3_950a24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Freq_2 (9767204, 0x950924)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Freq_2_950924(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Freq_2 (9767204, 0x950924) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Freq_2_950924(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Misc_3_970324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Misc_3_970324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Misc_2_970224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Misc_2_970224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Misc_1_970124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Misc_1_970124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_31 (9707300, 0x941f24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_31_941f24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_31 (9707300, 0x941f24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_31_941f24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_30 (9707044, 0x941e24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_30_941e24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_30 (9707044, 0x941e24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_30_941e24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_29 (9706788, 0x941d24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_29_941d24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_29 (9706788, 0x941d24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_29_941d24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_28 (9706532, 0x941c24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_28_941c24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_28 (9706532, 0x941c24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_28_941c24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_27 (9706276, 0x941b24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_27_941b24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_27 (9706276, 0x941b24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_27_941b24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_26 (9706020, 0x941a24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_26_941a24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_26 (9706020, 0x941a24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_26_941a24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_25 (9705764, 0x941924)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_25_941924(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_25 (9705764, 0x941924) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_25_941924(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_24 (9705508, 0x941824)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_24_941824(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_24 (9705508, 0x941824) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_24_941824(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_23 (9705252, 0x941724)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_23_941724(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_23 (9705252, 0x941724) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_23_941724(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_22 (9704996, 0x941624)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_22_941624(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_22 (9704996, 0x941624) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_22_941624(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_21 (9704740, 0x941524)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_21_941524(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_21 (9704740, 0x941524) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_21_941524(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_20 (9704484, 0x941424)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_20_941424(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_20 (9704484, 0x941424) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_20_941424(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_19 (9704228, 0x941324)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_19_941324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_19 (9704228, 0x941324) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_19_941324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_18 (9703972, 0x941224)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_18_941224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_18 (9703972, 0x941224) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_18_941224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_17 (9703716, 0x941124)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_17_941124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_17 (9703716, 0x941124) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_17_941124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_16 (9703460, 0x941024)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_16_941024(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_16 (9703460, 0x941024) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_16_941024(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_15 (9703204, 0x940f24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_15_940f24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_15 (9703204, 0x940f24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_15_940f24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_14 (9702948, 0x940e24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_14_940e24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_14 (9702948, 0x940e24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_14_940e24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_13 (9702692, 0x940d24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_13_940d24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_13 (9702692, 0x940d24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_13_940d24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_12 (9702436, 0x940c24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_12_940c24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_12 (9702436, 0x940c24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_12_940c24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_11 (9702180, 0x940b24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_11_940b24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_11 (9702180, 0x940b24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_11_940b24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_9 (9701668, 0x940924)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_9_940924(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_9 (9701668, 0x940924) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_9_940924(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_10 (9701924, 0x940a24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_10_940a24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_10 (9701924, 0x940a24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_10_940a24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_8 (9701412, 0x940824)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_8_940824(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_8 (9701412, 0x940824) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_8_940824(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_7 (9701156, 0x940724)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_7_940724(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_7 (9701156, 0x940724) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_7_940724(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_6 (9700900, 0x940624)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_6_940624(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_6 (9700900, 0x940624) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_6_940624(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_5 (9700644, 0x940524)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_5_940524(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_5 (9700644, 0x940524) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_5_940524(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_4 (9700388, 0x940424)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_4_940424(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_4 (9700388, 0x940424) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_4_940424(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_3 (9700132, 0x940324)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_3_940324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_3 (9700132, 0x940324) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_3_940324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_2_940224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_2_940224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Aux_1_940124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Aux_1_940124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Pressure_5_900524(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Pressure_5_900524(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Pressure_4 (9438244, 0x900424)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Pressure_4_900424(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Pressure_4 (9438244, 0x900424) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Pressure_4_900424(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Pressure_3 (9437988, 0x900324)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Pressure_3_900324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Pressure_3 (9437988, 0x900324) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Pressure_3_900324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Pressure_2 (9437732, 0x900224)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Pressure_2_900224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Pressure_2 (9437732, 0x900224) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Pressure_2_900224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Pressure_1 (9437476, 0x900124)
    in the global signal interface into a byte array of 3 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Pressure_1_900124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Pressure_1 (9437476, 0x900124) from
    a byte array of 3 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Pressure_1_900124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Angle_3_920324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Angle_3_920324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Angle_2 (9568804, 0x920224)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Angle_2_920224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Angle_2 (9568804, 0x920224) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Angle_2_920224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Angle_1 (9568548, 0x920124)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Angle_1_920124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Angle_1 (9568548, 0x920124) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Angle_1_920124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_25 (9509156, 0x911924)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_25_911924(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_25 (9509156, 0x911924) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_25_911924(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_24 (9508900, 0x911824)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_24_911824(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_24 (9508900, 0x911824) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_24_911824(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_23 (9508644, 0x911724)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_23_911724(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_23 (9508644, 0x911724) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_23_911724(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_22 (9508388, 0x911624)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_22_911624(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_22 (9508388, 0x911624) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_22_911624(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_21 (9508132, 0x911524)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_21_911524(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_21 (9508132, 0x911524) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_21_911524(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_20 (9507876, 0x911424)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_20_911424(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_20 (9507876, 0x911424) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_20_911424(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_19 (9507620, 0x911324)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_19_911324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_19 (9507620, 0x911324) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_19_911324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_18 (9507364, 0x911224)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_18_911224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_18 (9507364, 0x911224) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_18_911224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_17 (9507108, 0x911124)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_17_911124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_17 (9507108, 0x911124) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_17_911124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_16 (9506852, 0x911024)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_16_911024(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_16 (9506852, 0x911024) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_16_911024(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_15 (9506596, 0x910f24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_15_910f24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_15 (9506596, 0x910f24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_15_910f24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_14 (9506340, 0x910e24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_14_910e24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_14 (9506340, 0x910e24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_14_910e24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_13 (9506084, 0x910d24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_13_910d24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_13 (9506084, 0x910d24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_13_910d24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_12 (9505828, 0x910c24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_12_910c24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_12 (9505828, 0x910c24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_12_910c24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_11 (9505572, 0x910b24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_11_910b24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_11 (9505572, 0x910b24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_11_910b24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_10 (9505316, 0x910a24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_10_910a24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_10 (9505316, 0x910a24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_10_910a24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_9 (9505060, 0x910924)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_9_910924(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_9 (9505060, 0x910924) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_9_910924(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_8 (9504804, 0x910824)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_8_910824(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_8 (9504804, 0x910824) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_8_910824(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_7 (9504548, 0x910724)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_7_910724(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_7 (9504548, 0x910724) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_7_910724(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_6 (9504292, 0x910624)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_6_910624(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_6 (9504292, 0x910624) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_6_910624(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_5 (9504036, 0x910524)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_5_910524(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_5 (9504036, 0x910524) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_5_910524(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_4 (9503780, 0x910424)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_4_910424(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_4 (9503780, 0x910424) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_4_910424(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_3 (9503524, 0x910324)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_3_910324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_3 (9503524, 0x910324) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_3_910324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_2 (9503268, 0x910224)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_2_910224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_2 (9503268, 0x910224) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_2_910224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Temp_1_910124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Temp_1_910124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_32 (8527652, 0x821f24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_32_821f24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_32 (8527652, 0x821f24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_32_821f24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_31 (8527396, 0x821e24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_31_821e24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_31 (8527396, 0x821e24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_31_821e24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_30 (8527140, 0x821d24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_30_821d24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_30 (8527140, 0x821d24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_30_821d24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_29 (8526884, 0x821c24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_29_821c24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_29 (8526884, 0x821c24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_29_821c24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_28 (8526628, 0x821b24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_28_821b24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_28 (8526628, 0x821b24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_28_821b24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_27 (8526372, 0x821a24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_27_821a24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_27 (8526372, 0x821a24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_27_821a24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_26 (8526116, 0x821924)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_26_821924(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_26 (8526116, 0x821924) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_26_821924(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_25 (8525860, 0x821824)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_25_821824(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_25 (8525860, 0x821824) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_25_821824(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_15 (8523300, 0x820e24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_15_820e24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_15 (8523300, 0x820e24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_15_820e24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_14 (8523044, 0x820d24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_14_820d24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_14 (8523044, 0x820d24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_14_820d24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_17 (8523812, 0x821024)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_17_821024(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_17 (8523812, 0x821024) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_17_821024(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_24 (8525604, 0x821724)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_24_821724(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_24 (8525604, 0x821724) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_24_821724(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_23 (8525348, 0x821624)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_23_821624(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_23 (8525348, 0x821624) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_23_821624(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_22 (8525092, 0x821524)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_22_821524(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_22 (8525092, 0x821524) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_22_821524(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_21 (8524836, 0x821424)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_21_821424(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_21 (8524836, 0x821424) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_21_821424(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_20 (8524580, 0x821324)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_20_821324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_20 (8524580, 0x821324) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_20_821324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_19 (8524324, 0x821224)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_19_821224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_19 (8524324, 0x821224) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_19_821224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_16 (8523556, 0x820f24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_16_820f24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_16 (8523556, 0x820f24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_16_820f24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_18 (8524068, 0x821124)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_18_821124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_18 (8524068, 0x821124) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_18_821124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_12 (8522532, 0x820b24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_12_820b24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_12 (8522532, 0x820b24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_12_820b24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_11 (8522276, 0x820a24)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_11_820a24(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_11 (8522276, 0x820a24) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_11_820a24(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_10 (8522020, 0x820924)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_10_820924(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_10 (8522020, 0x820924) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_10_820924(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_9 (8521764, 0x820824)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_9_820824(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_9 (8521764, 0x820824) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_9_820824(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_8 (8521508, 0x820724)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_8_820724(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_8 (8521508, 0x820724) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_8_820724(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_7 (8521252, 0x820624)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_7_820624(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_7 (8521252, 0x820624) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_7_820624(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_6 (8520996, 0x820524)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_6_820524(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_6 (8520996, 0x820524) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_6_820524(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_5 (8520740, 0x820424)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_5_820424(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_5 (8520740, 0x820424) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_5_820424(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_4 (8520484, 0x820324)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_4_820324(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_4 (8520484, 0x820324) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_4_820324(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_3_820224(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_3_820224(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_2_820124(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_2_820124(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024)
    in the global signal interface into a byte array of 2 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Analog_1_820024(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024) from
    a byte array of 2 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Analog_1_820024(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_DL1MK3_Accel_800024(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_DL1MK3_Accel_800024(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_4_Vel_NED_2 (9384482, 0x8f3222)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_4_Vel_NED_2_8f3222(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_4_Vel_NED_2 (9384482, 0x8f3222) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_4_Vel_NED_2_8f3222(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_4_Vel_NED_1 (9384226, 0x8f3122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_4_Vel_NED_1_8f3122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_4_Vel_NED_1 (9384226, 0x8f3122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_4_Vel_NED_1_8f3122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_4_Offset (9383970, 0x8f3022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_4_Offset_8f3022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_4_Offset (9383970, 0x8f3022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_4_Offset_8f3022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_3_Vel_NED_2 (9380386, 0x8f2222)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_3_Vel_NED_2_8f2222(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_3_Vel_NED_2 (9380386, 0x8f2222) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_3_Vel_NED_2_8f2222(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_3_Vel_NED_1 (9380130, 0x8f2122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_3_Vel_NED_1_8f2122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_3_Vel_NED_1 (9380130, 0x8f2122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_3_Vel_NED_1_8f2122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_3_Offset (9379874, 0x8f2022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_3_Offset_8f2022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_3_Offset (9379874, 0x8f2022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_3_Offset_8f2022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_2_Vel_NED_2 (9376290, 0x8f1222)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_2_Vel_NED_2_8f1222(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_2_Vel_NED_2 (9376290, 0x8f1222) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_2_Vel_NED_2_8f1222(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_2_Vel_NED_1 (9376034, 0x8f1122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_2_Vel_NED_1_8f1122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_2_Vel_NED_1 (9376034, 0x8f1122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_2_Vel_NED_1_8f1122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_2_Offset (9375778, 0x8f1022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_2_Offset_8f1022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_2_Offset (9375778, 0x8f1022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_2_Offset_8f1022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_1_Vel_NED_2 (9372194, 0x8f0222)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_1_Vel_NED_2_8f0222(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_1_Vel_NED_2 (9372194, 0x8f0222) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_1_Vel_NED_2_8f0222(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_1_Vel_NED_1 (9371938, 0x8f0122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_1_Vel_NED_1_8f0122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_1_Vel_NED_1 (9371938, 0x8f0122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_1_Vel_NED_1_8f0122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vpt_1_Offset (9371682, 0x8f0022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vpt_1_Offset_8f0022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vpt_1_Offset (9371682, 0x8f0022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vpt_1_Offset_8f0022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Slip (9311778, 0x8e1622)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Slip_8e1622(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Slip (9311778, 0x8e1622) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Slip_8e1622(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vel_ECEF_2 (9311010, 0x8e1322)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vel_ECEF_2_8e1322(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vel_ECEF_2 (9311010, 0x8e1322) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vel_ECEF_2_8e1322(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vel_ECEF_1 (9310754, 0x8e1222)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vel_ECEF_1_8e1222(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vel_ECEF_1 (9310754, 0x8e1222) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vel_ECEF_1_8e1222(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vel_NED_2 (9310498, 0x8e1122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vel_NED_2_8e1122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vel_NED_2 (9310498, 0x8e1122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vel_NED_2_8e1122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vel_NED_1 (9310242, 0x8e1022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Vel_NED_1_8e1022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vel_NED_1 (9310242, 0x8e1022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Vel_NED_1_8e1022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Pos_ECEF_2 (9307426, 0x8e0522)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Pos_ECEF_2_8e0522(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Pos_ECEF_2 (9307426, 0x8e0522) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Pos_ECEF_2_8e0522(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Pos_ECEF_1 (9307170, 0x8e0422)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Pos_ECEF_1_8e0422(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Pos_ECEF_1 (9307170, 0x8e0422) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Pos_ECEF_1_8e0422(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Pos_LLH_2 (9306914, 0x8e0322)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Pos_LLH_2_8e0322(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Pos_LLH_2 (9306914, 0x8e0322) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Pos_LLH_2_8e0322(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Pos_LLH_1 (9306658, 0x8e0222)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Pos_LLH_1_8e0222(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Pos_LLH_1 (9306658, 0x8e0222) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Pos_LLH_1_8e0222(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Heading_Gradient_2 (9311522, 0x8e1522)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Heading_Gradient_2_8e1522(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Heading_Gradient_2 (9311522, 0x8e1522) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Heading_Gradient_2_8e1522(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Heading_Gradient (9311266, 0x8e1422)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Heading_Gradient_8e1422(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Heading_Gradient (9311266, 0x8e1422) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Heading_Gradient_8e1422(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Status_8e0022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Status_8e0022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_INS_Attitude_8e0122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_INS_Attitude_8e0122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Output_Status_8d0122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Output_Status_8d0122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Heading_Gradient_2_8c1622(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Heading_Gradient_2_8c1622(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Cumulative_Distance_2_802122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Cumulative_Distance_2_802122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Cumulative_Distance_1_802022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Cumulative_Distance_1_802022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Trigger_Timestamp_8d0022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Trigger_Timestamp_8d0022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IMU06_Gyro_Rates_800121(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_IMU06_Gyro_Rates_800121(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_IMU06_Accel (8388641, 0x800021)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_IMU06_Accel_800021(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_IMU06_Accel (8388641, 0x800021) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_IMU06_Accel_800021(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Speed (8392738, 0x801022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Speed_801022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Speed (8392738, 0x801022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Speed_801022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_RTK_Slip_8c2122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_RTK_Slip_8c2122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_RTK_Attitude_8c2022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_RTK_Attitude_8c2022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Mcycle_Lean_8c3022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Mcycle_Lean_8c3022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Status_8c0022(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Status_8c0022(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Pos_ECEF_2_8c0522(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Pos_ECEF_2_8c0522(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Pos_ECEF_1_8c0422(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Pos_ECEF_1_8c0422(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Pos_LLH_2_8c0322(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Pos_LLH_2_8c0322(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Pos_LLH_1_8c0222(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Pos_LLH_1_8c0222(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Heading_Gradient_8c1522(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Heading_Gradient_8c1522(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Vel_ECEF_2_8c1422(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Vel_ECEF_2_8c1422(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Vel_ECEF_1_8c1322(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Vel_ECEF_1_8c1322(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Vel_NED_2_000(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Vel_NED_2_000(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_NED_1 (536870911, 0x1fffffff)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Vel_NED_1_1fffffff(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_NED_1 (536870911, 0x1fffffff) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Vel_NED_1_1fffffff(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Speed (1818, 0x71a)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Speed_71a(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Speed (1818, 0x71a) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Speed_71a(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Time (2047, 0x7ff)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_GPS_Time_7ff(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Time (2047, 0x7ff) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_GPS_Time_7ff(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Accel (290, 0x122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Accel_122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Accel (290, 0x122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Accel_122(const UInt8 m[]);

/** Pack the signal values of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122)
    in the global signal interface into a byte array of 8 Byte. */
#if CRT_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
void crt_pack_PT_RT_SB_Gyro_Rates_800122(UInt8 m[]);
#endif

/** Unpack the signals of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122) from
    a byte array of 8 Byte into the global signal interface. */
void crt_unpack_PT_RT_SB_Gyro_Rates_800122(const UInt8 m[]);



/*
 * Inline function definitions
 */

#endif // !defined(CRT_CANRT_DEFINED)
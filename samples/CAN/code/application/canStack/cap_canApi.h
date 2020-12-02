#ifndef CAP_CANAPI_DEFINED
#define CAP_CANAPI_DEFINED
/**
 * @file cap_canApi.h
 * Declaration of API and pack/unpack functions for the CAN frames of cluster
 * DEVKIT-MPC5775G.
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


/*
 * Defines
 */

#ifndef CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS
/** Normally, a pack function is generated for sent frames only. If this define is set to a
    value other than 0 then a pack function is generated for received Frames, too. */
# define CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS 0
#endif

#ifndef CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS
/** Normally, an unpack function is generated for received Frames only. If this define is set
    to a value other than 0 then an unpack function is generated for sent Frames, too. */
# define CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS 0
#endif


/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_INS_Vel_Body_Axes_215() \
            (cap_canBus_PT.PT_RT_SB_INS_Vel_Body_Axes_215_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_INS_Vel_Body_Axes_215() \
            (cap_canBus_PT.PT_RT_SB_INS_Vel_Body_Axes_215_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_INS_Vel_Body_Axes_215(signalName) \
            (cap_canBus_PT.PT_RT_SB_INS_Vel_Body_Axes_215_sts.signals.signalName)

/** The size in Byte of frame RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_RT_SB_INS_VEL_BODY_AXES_215_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Speed (8392740, 0x801024) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Speed_8392740() \
            (cap_canBus_PT.PT_RT_DL1MK3_Speed_8392740_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Speed_8392740() \
            (cap_canBus_PT.PT_RT_DL1MK3_Speed_8392740_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Speed_8392740(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Speed_8392740_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_RT_DL1MK3_SPEED_8392740_DLC	7

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_GPS_Time_9175332() \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Time_9175332_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_GPS_Time_9175332() \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Time_9175332_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_GPS_Time_9175332(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Time_9175332_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_RT_DL1MK3_GPS_TIME_9175332_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844() \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844() \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. */
#define CAP_PT_RT_DL1MK3_GPS_POS_LLH_2_9175844_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588() \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588() \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_RT_DL1MK3_GPS_POS_LLH_1_9175588_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_GPS_Speed_1234() \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Speed_1234_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_GPS_Speed_1234() \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Speed_1234_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_GPS_Speed_1234(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_GPS_Speed_1234_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_RT_DL1MK3_GPS_SPEED_1234_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IRTemp_Temp_RL_2_9963045() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_RL_2_9963045_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IRTemp_Temp_RL_2_9963045() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_RL_2_9963045_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IRTemp_Temp_RL_2_9963045(signalName) \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_RL_2_9963045_sts.signals.signalName)

/** The size in Byte of frame RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_RL_2_9963045_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IRTemp_Temp_FR_2_9962533() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FR_2_9962533_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IRTemp_Temp_FR_2_9962533() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FR_2_9962533_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IRTemp_Temp_FR_2_9962533(signalName) \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FR_2_9962533_sts.signals.signalName)

/** The size in Byte of frame RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_FR_2_9962533_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IRTemp_Temp_FL_2_9962021() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FL_2_9962021_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IRTemp_Temp_FL_2_9962021() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FL_2_9962021_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IRTemp_Temp_FL_2_9962021(signalName) \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FL_2_9962021_sts.signals.signalName)

/** The size in Byte of frame RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_FL_2_9962021_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IRTemp_Temp_RL_1_9962789() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_RL_1_9962789_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IRTemp_Temp_RL_1_9962789() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_RL_1_9962789_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IRTemp_Temp_RL_1_9962789(signalName) \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_RL_1_9962789_sts.signals.signalName)

/** The size in Byte of frame RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_RL_1_9962789_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IRTemp_Temp_FR_1_9962277() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FR_1_9962277_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IRTemp_Temp_FR_1_9962277() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FR_1_9962277_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IRTemp_Temp_FR_1_9962277(signalName) \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FR_1_9962277_sts.signals.signalName)

/** The size in Byte of frame RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_FR_1_9962277_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IRTemp_Temp_FL_1_9961765() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FL_1_9961765_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IRTemp_Temp_FL_1_9961765() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FL_1_9961765_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IRTemp_Temp_FL_1_9961765(signalName) \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_FL_1_9961765_sts.signals.signalName)

/** The size in Byte of frame RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_FL_1_9961765_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IRTemp_Temp_30_9510437() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_30_9510437_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IRTemp_Temp_30_9510437() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_30_9510437_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IRTemp_Temp_30_9510437(signalName) \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_30_9510437_sts.signals.signalName)

/** The size in Byte of frame RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_30_9510437_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IRTemp_Temp_26_9509413() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_26_9509413_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IRTemp_Temp_26_9509413() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_26_9509413_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IRTemp_Temp_26_9509413(signalName) \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_26_9509413_sts.signals.signalName)

/** The size in Byte of frame RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_26_9509413_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IRTemp_Temp_1_9503013() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_1_9503013_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IRTemp_Temp_1_9503013() \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_1_9503013_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IRTemp_Temp_1_9503013(signalName) \
            (cap_canBus_PT.PT_RT_IRTemp_Temp_1_9503013_sts.signals.signalName)

/** The size in Byte of frame RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_1_9503013_DLC	3

/** The size in Bit of checksum signal of frame RT_IRTemp_Temp_1 (9503013, 0x910125)
    on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_1_9503013_CHECKSUM_LENGTH	8

/** The start bit of checksum signal of frame RT_IRTemp_Temp_1 (9503013, 0x910125)
    on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_1_9503013_CHECKSUM_STARTBIT	23

/** The endianness of checksum signal of frame RT_IRTemp_Temp_1 (9503013, 0x910125)
    on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_1_9503013_CHECKSUM_IS_BIG_ENDIAN	true

/** The data ID of checksum signal of frame RT_IRTemp_Temp_1 (9503013, 0x910125)
    on bus PT. */
#define CAP_PT_RT_IRTEMP_TEMP_1_9503013_CHECKSUM_START_VALUE	23

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Trig_Final_Condition_9242402() \
            (cap_canBus_PT.PT_RT_SB_Trig_Final_Condition_9242402_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Trig_Final_Condition_9242402() \
            (cap_canBus_PT.PT_RT_SB_Trig_Final_Condition_9242402_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Trig_Final_Condition_9242402(signalName) \
            (cap_canBus_PT.PT_RT_SB_Trig_Final_Condition_9242402_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT. */
#define CAP_PT_RT_SB_TRIG_FINAL_CONDITION_9242402_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Trig_Initial_Condition_794() \
            (cap_canBus_PT.PT_RT_SB_Trig_Initial_Condition_794_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Trig_Initial_Condition_794() \
            (cap_canBus_PT.PT_RT_SB_Trig_Initial_Condition_794_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Trig_Initial_Condition_794(signalName) \
            (cap_canBus_PT.PT_RT_SB_Trig_Initial_Condition_794_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_RT_SB_TRIG_INITIAL_CONDITION_794_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Trig_Direct_Dist_9241890() \
            (cap_canBus_PT.PT_RT_SB_Trig_Direct_Dist_9241890_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Trig_Direct_Dist_9241890() \
            (cap_canBus_PT.PT_RT_SB_Trig_Direct_Dist_9241890_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Trig_Direct_Dist_9241890(signalName) \
            (cap_canBus_PT.PT_RT_SB_Trig_Direct_Dist_9241890_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. */
#define CAP_PT_RT_SB_TRIG_DIRECT_DIST_9241890_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Trig_Forward_Dist_9241634() \
            (cap_canBus_PT.PT_RT_SB_Trig_Forward_Dist_9241634_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Trig_Forward_Dist_9241634() \
            (cap_canBus_PT.PT_RT_SB_Trig_Forward_Dist_9241634_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Trig_Forward_Dist_9241634(signalName) \
            (cap_canBus_PT.PT_RT_SB_Trig_Forward_Dist_9241634_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. */
#define CAP_PT_RT_SB_TRIG_FORWARD_DIST_9241634_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Trig_Path_Dist_9241378() \
            (cap_canBus_PT.PT_RT_SB_Trig_Path_Dist_9241378_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Trig_Path_Dist_9241378() \
            (cap_canBus_PT.PT_RT_SB_Trig_Path_Dist_9241378_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Trig_Path_Dist_9241378(signalName) \
            (cap_canBus_PT.PT_RT_SB_Trig_Path_Dist_9241378_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT. */
#define CAP_PT_RT_SB_TRIG_PATH_DIST_9241378_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Trig_Accel_9241122() \
            (cap_canBus_PT.PT_RT_SB_Trig_Accel_9241122_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Trig_Accel_9241122() \
            (cap_canBus_PT.PT_RT_SB_Trig_Accel_9241122_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Trig_Accel_9241122(signalName) \
            (cap_canBus_PT.PT_RT_SB_Trig_Accel_9241122_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_RT_SB_TRIG_ACCEL_9241122_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_11_9833252() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_11_9833252_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_11_9833252() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_11_9833252_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_11_9833252(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_11_9833252_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_11_9833252_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_10_9832996() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_10_9832996_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_10_9832996() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_10_9832996_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_10_9832996(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_10_9832996_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_10_9832996_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_9_9832740() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_9_9832740_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_9_9832740() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_9_9832740_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_9_9832740(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_9_9832740_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_9_9832740_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_8_9832484() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_8_9832484_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_8_9832484() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_8_9832484_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_8_9832484(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_8_9832484_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_8_9832484_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_7_9832228() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_7_9832228_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_7_9832228() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_7_9832228_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_7_9832228(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_7_9832228_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_7_9832228_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_6_9831972() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_6_9831972_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_6_9831972() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_6_9831972_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_6_9831972(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_6_9831972_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_6_9831972_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_5_9831716() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_5_9831716_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_5_9831716() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_5_9831716_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_5_9831716(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_5_9831716_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_5_9831716_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_4_9831460() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_4_9831460_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_4_9831460() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_4_9831460_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_4_9831460(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_4_9831460_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_4_9831460_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_3_9831204() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_3_9831204_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_3_9831204() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_3_9831204_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_3_9831204(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_3_9831204_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_3_9831204_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_2_9830948() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_2_9830948_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_2_9830948() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_2_9830948_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_2_9830948(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_2_9830948_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_2_9830948_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Measure_Time_1_9830692() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_1_9830692_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Measure_Time_1_9830692() \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_1_9830692_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Measure_Time_1_9830692(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_1_9830692_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT. */
#define CAP_PT_RT_DL1MK3_MEASURE_TIME_1_9830692_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_RPM_9767972() \
            (cap_canBus_PT.PT_RT_DL1MK3_RPM_9767972_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_RPM_9767972() \
            (cap_canBus_PT.PT_RT_DL1MK3_RPM_9767972_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_RPM_9767972(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_RPM_9767972_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT. */
#define CAP_PT_RT_DL1MK3_RPM_9767972_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Freq_4_9767716() \
            (cap_canBus_PT.PT_RT_DL1MK3_Freq_4_9767716_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Freq_4_9767716() \
            (cap_canBus_PT.PT_RT_DL1MK3_Freq_4_9767716_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Freq_4_9767716(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Freq_4_9767716_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT. */
#define CAP_PT_RT_DL1MK3_FREQ_4_9767716_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Misc_3_9896740() \
            (cap_canBus_PT.PT_RT_DL1MK3_Misc_3_9896740_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Misc_3_9896740() \
            (cap_canBus_PT.PT_RT_DL1MK3_Misc_3_9896740_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Misc_3_9896740(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Misc_3_9896740_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT. */
#define CAP_PT_RT_DL1MK3_MISC_3_9896740_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Misc_2_9896484() \
            (cap_canBus_PT.PT_RT_DL1MK3_Misc_2_9896484_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Misc_2_9896484() \
            (cap_canBus_PT.PT_RT_DL1MK3_Misc_2_9896484_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Misc_2_9896484(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Misc_2_9896484_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT. */
#define CAP_PT_RT_DL1MK3_MISC_2_9896484_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Misc_1_9896228() \
            (cap_canBus_PT.PT_RT_DL1MK3_Misc_1_9896228_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Misc_1_9896228() \
            (cap_canBus_PT.PT_RT_DL1MK3_Misc_1_9896228_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Misc_1_9896228(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Misc_1_9896228_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT. */
#define CAP_PT_RT_DL1MK3_MISC_1_9896228_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Aux_2_9699876() \
            (cap_canBus_PT.PT_RT_DL1MK3_Aux_2_9699876_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Aux_2_9699876() \
            (cap_canBus_PT.PT_RT_DL1MK3_Aux_2_9699876_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Aux_2_9699876(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Aux_2_9699876_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT. */
#define CAP_PT_RT_DL1MK3_AUX_2_9699876_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Aux_1_9699620() \
            (cap_canBus_PT.PT_RT_DL1MK3_Aux_1_9699620_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Aux_1_9699620() \
            (cap_canBus_PT.PT_RT_DL1MK3_Aux_1_9699620_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Aux_1_9699620(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Aux_1_9699620_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT. */
#define CAP_PT_RT_DL1MK3_AUX_1_9699620_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Pressure_5_9438500() \
            (cap_canBus_PT.PT_RT_DL1MK3_Pressure_5_9438500_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Pressure_5_9438500() \
            (cap_canBus_PT.PT_RT_DL1MK3_Pressure_5_9438500_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Pressure_5_9438500(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Pressure_5_9438500_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT. */
#define CAP_PT_RT_DL1MK3_PRESSURE_5_9438500_DLC	3

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Angle_3_9569060() \
            (cap_canBus_PT.PT_RT_DL1MK3_Angle_3_9569060_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Angle_3_9569060() \
            (cap_canBus_PT.PT_RT_DL1MK3_Angle_3_9569060_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Angle_3_9569060(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Angle_3_9569060_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT. */
#define CAP_PT_RT_DL1MK3_ANGLE_3_9569060_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Temp_1_9503012() \
            (cap_canBus_PT.PT_RT_DL1MK3_Temp_1_9503012_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Temp_1_9503012() \
            (cap_canBus_PT.PT_RT_DL1MK3_Temp_1_9503012_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Temp_1_9503012(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Temp_1_9503012_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT. */
#define CAP_PT_RT_DL1MK3_TEMP_1_9503012_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Analog_3_8520228() \
            (cap_canBus_PT.PT_RT_DL1MK3_Analog_3_8520228_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Analog_3_8520228() \
            (cap_canBus_PT.PT_RT_DL1MK3_Analog_3_8520228_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Analog_3_8520228(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Analog_3_8520228_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT. */
#define CAP_PT_RT_DL1MK3_ANALOG_3_8520228_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Analog_2_8519972() \
            (cap_canBus_PT.PT_RT_DL1MK3_Analog_2_8519972_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Analog_2_8519972() \
            (cap_canBus_PT.PT_RT_DL1MK3_Analog_2_8519972_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Analog_2_8519972(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Analog_2_8519972_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT. */
#define CAP_PT_RT_DL1MK3_ANALOG_2_8519972_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Analog_1_8519716() \
            (cap_canBus_PT.PT_RT_DL1MK3_Analog_1_8519716_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Analog_1_8519716() \
            (cap_canBus_PT.PT_RT_DL1MK3_Analog_1_8519716_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Analog_1_8519716(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Analog_1_8519716_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT. */
#define CAP_PT_RT_DL1MK3_ANALOG_1_8519716_DLC	2

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_DL1MK3_Accel (8388644, 0x800024) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_DL1MK3_Accel_8388644() \
            (cap_canBus_PT.PT_RT_DL1MK3_Accel_8388644_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_DL1MK3_Accel_8388644() \
            (cap_canBus_PT.PT_RT_DL1MK3_Accel_8388644_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_DL1MK3_Accel_8388644(signalName) \
            (cap_canBus_PT.PT_RT_DL1MK3_Accel_8388644_sts.signals.signalName)

/** The size in Byte of frame RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_RT_DL1MK3_ACCEL_8388644_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_INS_Status (9306146, 0x8e0022) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_INS_Status_9306146() \
            (cap_canBus_PT.PT_RT_SB_INS_Status_9306146_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_INS_Status (9306146, 0x8e0022) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_INS_Status_9306146() \
            (cap_canBus_PT.PT_RT_SB_INS_Status_9306146_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_INS_Status (9306146, 0x8e0022) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_INS_Status_9306146(signalName) \
            (cap_canBus_PT.PT_RT_SB_INS_Status_9306146_sts.signals.signalName)

/** The size in Byte of frame RT_SB_INS_Status (9306146, 0x8e0022) on bus PT. */
#define CAP_PT_RT_SB_INS_STATUS_9306146_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_INS_Attitude_9306402() \
            (cap_canBus_PT.PT_RT_SB_INS_Attitude_9306402_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_INS_Attitude_9306402() \
            (cap_canBus_PT.PT_RT_SB_INS_Attitude_9306402_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_INS_Attitude_9306402(signalName) \
            (cap_canBus_PT.PT_RT_SB_INS_Attitude_9306402_sts.signals.signalName)

/** The size in Byte of frame RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_RT_SB_INS_ATTITUDE_9306402_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Output_Status (9240866, 0x8d0122) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Output_Status_9240866() \
            (cap_canBus_PT.PT_RT_SB_Output_Status_9240866_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Output_Status_9240866() \
            (cap_canBus_PT.PT_RT_SB_Output_Status_9240866_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Output_Status_9240866(signalName) \
            (cap_canBus_PT.PT_RT_SB_Output_Status_9240866_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_RT_SB_OUTPUT_STATUS_9240866_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Heading_Gradient_2_9180706() \
            (cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Heading_Gradient_2_9180706() \
            (cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Heading_Gradient_2_9180706(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_RT_SB_GPS_HEADING_GRADIENT_2_9180706_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Cumulative_Distance_2_8397090() \
            (cap_canBus_PT.PT_RT_SB_Cumulative_Distance_2_8397090_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Cumulative_Distance_2_8397090() \
            (cap_canBus_PT.PT_RT_SB_Cumulative_Distance_2_8397090_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Cumulative_Distance_2_8397090(signalName) \
            (cap_canBus_PT.PT_RT_SB_Cumulative_Distance_2_8397090_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_RT_SB_CUMULATIVE_DISTANCE_2_8397090_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Cumulative_Distance_1_8396834() \
            (cap_canBus_PT.PT_RT_SB_Cumulative_Distance_1_8396834_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Cumulative_Distance_1_8396834() \
            (cap_canBus_PT.PT_RT_SB_Cumulative_Distance_1_8396834_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Cumulative_Distance_1_8396834(signalName) \
            (cap_canBus_PT.PT_RT_SB_Cumulative_Distance_1_8396834_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_RT_SB_CUMULATIVE_DISTANCE_1_8396834_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Trigger_Timestamp_9240610() \
            (cap_canBus_PT.PT_RT_SB_Trigger_Timestamp_9240610_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Trigger_Timestamp_9240610() \
            (cap_canBus_PT.PT_RT_SB_Trigger_Timestamp_9240610_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Trigger_Timestamp_9240610(signalName) \
            (cap_canBus_PT.PT_RT_SB_Trigger_Timestamp_9240610_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_RT_SB_TRIGGER_TIMESTAMP_9240610_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IMU06_Gyro_Rates_8388897() \
            (cap_canBus_PT.PT_RT_IMU06_Gyro_Rates_8388897_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IMU06_Gyro_Rates_8388897() \
            (cap_canBus_PT.PT_RT_IMU06_Gyro_Rates_8388897_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IMU06_Gyro_Rates_8388897(signalName) \
            (cap_canBus_PT.PT_RT_IMU06_Gyro_Rates_8388897_sts.signals.signalName)

/** The size in Byte of frame RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_RT_IMU06_GYRO_RATES_8388897_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_IMU06_Accel (8388641, 0x800021) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_IMU06_Accel_8388641() \
            (cap_canBus_PT.PT_RT_IMU06_Accel_8388641_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_IMU06_Accel_8388641() \
            (cap_canBus_PT.PT_RT_IMU06_Accel_8388641_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_IMU06_Accel_8388641(signalName) \
            (cap_canBus_PT.PT_RT_IMU06_Accel_8388641_sts.signals.signalName)

/** The size in Byte of frame RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_RT_IMU06_ACCEL_8388641_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Speed (8392738, 0x801022) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Speed_8392738() \
            (cap_canBus_PT.PT_RT_SB_Speed_8392738_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Speed_8392738() \
            (cap_canBus_PT.PT_RT_SB_Speed_8392738_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Speed_8392738(signalName) \
            (cap_canBus_PT.PT_RT_SB_Speed_8392738_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Speed (8392738, 0x801022) on bus PT. */
#define CAP_PT_RT_SB_SPEED_8392738_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_RTK_Slip_9183522() \
            (cap_canBus_PT.PT_RT_SB_RTK_Slip_9183522_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_RTK_Slip_9183522() \
            (cap_canBus_PT.PT_RT_SB_RTK_Slip_9183522_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_RTK_Slip_9183522(signalName) \
            (cap_canBus_PT.PT_RT_SB_RTK_Slip_9183522_sts.signals.signalName)

/** The size in Byte of frame RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_RT_SB_RTK_SLIP_9183522_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_RTK_Attitude_9183266() \
            (cap_canBus_PT.PT_RT_SB_RTK_Attitude_9183266_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_RTK_Attitude_9183266() \
            (cap_canBus_PT.PT_RT_SB_RTK_Attitude_9183266_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_RTK_Attitude_9183266(signalName) \
            (cap_canBus_PT.PT_RT_SB_RTK_Attitude_9183266_sts.signals.signalName)

/** The size in Byte of frame RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_RT_SB_RTK_ATTITUDE_9183266_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Mcycle_Lean_9187362() \
            (cap_canBus_PT.PT_RT_SB_GPS_Mcycle_Lean_9187362_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Mcycle_Lean_9187362() \
            (cap_canBus_PT.PT_RT_SB_GPS_Mcycle_Lean_9187362_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Mcycle_Lean_9187362(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Mcycle_Lean_9187362_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_RT_SB_GPS_MCYCLE_LEAN_9187362_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Status_9175074() \
            (cap_canBus_PT.PT_RT_SB_GPS_Status_9175074_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Status_9175074() \
            (cap_canBus_PT.PT_RT_SB_GPS_Status_9175074_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Status_9175074(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Status_9175074_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_RT_SB_GPS_STATUS_9175074_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Pos_ECEF_2_9176354() \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Pos_ECEF_2_9176354() \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Pos_ECEF_2_9176354(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. */
#define CAP_PT_RT_SB_GPS_POS_ECEF_2_9176354_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Pos_ECEF_1_9176098() \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Pos_ECEF_1_9176098() \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Pos_ECEF_1_9176098(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_RT_SB_GPS_POS_ECEF_1_9176098_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Pos_LLH_2_9175842() \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_2_9175842_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Pos_LLH_2_9175842() \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_2_9175842_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Pos_LLH_2_9175842(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_2_9175842_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. */
#define CAP_PT_RT_SB_GPS_POS_LLH_2_9175842_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Pos_LLH_1_9175586() \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_1_9175586_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Pos_LLH_1_9175586() \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_1_9175586_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Pos_LLH_1_9175586(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_1_9175586_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_RT_SB_GPS_POS_LLH_1_9175586_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Heading_Gradient_9180450() \
            (cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_9180450_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Heading_Gradient_9180450() \
            (cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_9180450_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Heading_Gradient_9180450(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_9180450_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_RT_SB_GPS_HEADING_GRADIENT_9180450_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Vel_ECEF_2_9180194() \
            (cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Vel_ECEF_2_9180194() \
            (cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Vel_ECEF_2_9180194(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_RT_SB_GPS_VEL_ECEF_2_9180194_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Vel_ECEF_1_9179938() \
            (cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Vel_ECEF_1_9179938() \
            (cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Vel_ECEF_1_9179938(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_RT_SB_GPS_VEL_ECEF_1_9179938_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Vel_NED_2_0() \
            (cap_canBus_PT.PT_RT_SB_GPS_Vel_NED_2_0_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Vel_NED_2_0() \
            (cap_canBus_PT.PT_RT_SB_GPS_Vel_NED_2_0_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Vel_NED_2_0(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Vel_NED_2_0_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. */
#define CAP_PT_RT_SB_GPS_VEL_NED_2_0_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Speed (1818, 0x71a) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Speed_1818() \
            (cap_canBus_PT.PT_RT_SB_GPS_Speed_1818_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Speed_1818() \
            (cap_canBus_PT.PT_RT_SB_GPS_Speed_1818_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Speed_1818(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Speed_1818_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_RT_SB_GPS_SPEED_1818_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_GPS_Time (2047, 0x7ff) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_GPS_Time_2047() \
            (cap_canBus_PT.PT_RT_SB_GPS_Time_2047_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_GPS_Time_2047() \
            (cap_canBus_PT.PT_RT_SB_GPS_Time_2047_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_GPS_Time_2047(signalName) \
            (cap_canBus_PT.PT_RT_SB_GPS_Time_2047_sts.signals.signalName)

/** The size in Byte of frame RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_RT_SB_GPS_TIME_2047_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Accel (290, 0x122) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Accel_290() \
            (cap_canBus_PT.PT_RT_SB_Accel_290_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Accel (290, 0x122) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Accel_290() \
            (cap_canBus_PT.PT_RT_SB_Accel_290_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Accel (290, 0x122) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Accel_290(signalName) \
            (cap_canBus_PT.PT_RT_SB_Accel_290_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_RT_SB_ACCEL_290_DLC	8

/** Provide read/write access to the frame API struct, which bundles the set of signals of
    frame RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT with the
    transmission status information. The referenced struct is a nested sub-element of the
    large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrameSts_PT_RT_SB_Gyro_Rates_8388898() \
            (cap_canBus_PT.PT_RT_SB_Gyro_Rates_8388898_sts)

/** Provide read/write access to the frame API struct, which bundles the signals of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. The referenced struct is
    a nested sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getFrame_PT_RT_SB_Gyro_Rates_8388898() \
            (cap_canBus_PT.PT_RT_SB_Gyro_Rates_8388898_sts.signals)

/** Provide read/write access to a field of the struct, which bundles the signals of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. This struct is a nested
    sub-element of the large the CAN bus describing struct cap_canBus_PT. */
#define cap_getSignal_PT_RT_SB_Gyro_Rates_8388898(signalName) \
            (cap_canBus_PT.PT_RT_SB_Gyro_Rates_8388898_sts.signals.signalName)

/** The size in Byte of frame RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_RT_SB_GYRO_RATES_8388898_DLC	8


/** The minimum of the world value of signal Validity_INS_Vel_Forwards of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_VALIDITY_INS_VEL_FORWARDS_MIN	(0)

/** The maximum of the world value of signal Validity_INS_Vel_Forwards of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_VALIDITY_INS_VEL_FORWARDS_MAX	(1)

/** The minimum of the world value of signal Validity_INS_Vel_Sideways of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_VALIDITY_INS_VEL_SIDEWAYS_MIN	(0)

/** The maximum of the world value of signal Validity_INS_Vel_Sideways of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_VALIDITY_INS_VEL_SIDEWAYS_MAX	(1)

/** The minimum of the world value of signal Bit4 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_BIT4_MIN	(0)

/** The maximum of the world value of signal Bit4 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_BIT4_MAX	(1)

/** The minimum of the world value of signal Bit7 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_BIT7_MIN	(0)

/** The maximum of the world value of signal Bit7 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_BIT7_MAX	(1)

/** The minimum of the world value of signal Byte2_Bit0 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_BYTE2_BIT0_MIN	(0)

/** The maximum of the world value of signal Byte2_Bit0 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_BYTE2_BIT0_MAX	(1)


/** Convert the binary value of signal INS_Vel_Sideways_2D of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the world value. */
#define CAP_PT_215_INS_VEL_SIDEWAYS_2D_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_215_INS_VEL_SIDEWAYS_2D_FACTOR)

/** Convert the world value of signal INS_Vel_Sideways_2D of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_215_INS_VEL_SIDEWAYS_2D_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_215_INS_VEL_SIDEWAYS_2D_FACTOR))

/** The gain factor of the scaling of signal INS_Vel_Sideways_2D of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_SIDEWAYS_2D_FACTOR	(1.0E-4)

/** The offset of the scaling of signal INS_Vel_Sideways_2D of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_SIDEWAYS_2D_OFFSET	(0.0)

/** The minimum of the world value of signal INS_Vel_Sideways_2D of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_SIDEWAYS_2D_MIN	(-838.0)

/** The maximum of the world value of signal INS_Vel_Sideways_2D of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_SIDEWAYS_2D_MAX	(838.0)

/** The minimum of the world value of signal Byte4_Bits67 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_BYTE4_BITS67_MIN	(1)

/** The maximum of the world value of signal Byte4_Bits67 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_BYTE4_BITS67_MAX	(3)

/** The minimum of the world value of signal Accuracy_INS_Vel_Body_org of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_ORG_MIN	(0)

/** The maximum of the world value of signal Accuracy_INS_Vel_Body_org of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_ORG_MAX	(255)


/** Convert the binary value of signal INS_Vel_Forwards_2D_org of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the world value. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_ORG_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_215_INS_VEL_FORWARDS_2D_ORG_FACTOR)

/** Convert the world value of signal INS_Vel_Forwards_2D_org of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_ORG_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_215_INS_VEL_FORWARDS_2D_ORG_FACTOR))

/** The gain factor of the scaling of signal INS_Vel_Forwards_2D_org of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_ORG_FACTOR	(1.0E-4)

/** The offset of the scaling of signal INS_Vel_Forwards_2D_org of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_ORG_OFFSET	(0.0)

/** The minimum of the world value of signal INS_Vel_Forwards_2D_org of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_ORG_MIN	(-838.0)

/** The maximum of the world value of signal INS_Vel_Forwards_2D_org of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_ORG_MAX	(838.0)

/** The minimum of the world value of signal Accuracy_INS_Vel_Body_no2 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_NO2_MIN	(0)

/** The maximum of the world value of signal Accuracy_INS_Vel_Body_no2 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_NO2_MAX	(255)


/** Convert the binary value of signal INS_Vel_Forwards_2D_no2 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the world value. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO2_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_215_INS_VEL_FORWARDS_2D_NO2_FACTOR)

/** Convert the world value of signal INS_Vel_Forwards_2D_no2 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO2_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_215_INS_VEL_FORWARDS_2D_NO2_FACTOR))

/** The gain factor of the scaling of signal INS_Vel_Forwards_2D_no2 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO2_FACTOR	(1.0E-4)

/** The offset of the scaling of signal INS_Vel_Forwards_2D_no2 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO2_OFFSET	(0.0)

/** The minimum of the world value of signal INS_Vel_Forwards_2D_no2 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO2_MIN	(-104.0)

/** The maximum of the world value of signal INS_Vel_Forwards_2D_no2 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO2_MAX	(104.0)


/** Convert the binary value of signal Accuracy_INS_Vel_Body_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the world value. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_NO3_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_215_ACCURACY_INS_VEL_BODY_NO3_FACTOR)

/** Convert the world value of signal Accuracy_INS_Vel_Body_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_NO3_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_215_ACCURACY_INS_VEL_BODY_NO3_FACTOR))

/** The gain factor of the scaling of signal Accuracy_INS_Vel_Body_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_NO3_FACTOR	(0.001)

/** The offset of the scaling of signal Accuracy_INS_Vel_Body_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_NO3_OFFSET	(0.0)

/** The minimum of the world value of signal Accuracy_INS_Vel_Body_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_NO3_MIN	(0.0)

/** The maximum of the world value of signal Accuracy_INS_Vel_Body_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_ACCURACY_INS_VEL_BODY_NO3_MAX	(32.768)


/** Convert the binary value of signal INS_Vel_Forwards_2D_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the world value. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO3_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_215_INS_VEL_FORWARDS_2D_NO3_FACTOR)

/** Convert the world value of signal INS_Vel_Forwards_2D_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO3_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_215_INS_VEL_FORWARDS_2D_NO3_FACTOR))

/** The gain factor of the scaling of signal INS_Vel_Forwards_2D_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO3_FACTOR	(0.01)

/** The offset of the scaling of signal INS_Vel_Forwards_2D_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO3_OFFSET	(0.0)

/** The minimum of the world value of signal INS_Vel_Forwards_2D_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO3_MIN	(-81.92)

/** The maximum of the world value of signal INS_Vel_Forwards_2D_no3 of frame
    RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on bus PT. */
#define CAP_PT_215_INS_VEL_FORWARDS_2D_NO3_MAX	(81.91)

/** The minimum of the world value of signal Validity_Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_VALIDITY_SPEED_MIN	(0)

/** The maximum of the world value of signal Validity_Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_VALIDITY_SPEED_MAX	(1)

/** The minimum of the world value of signal Accuracy_Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_ACCURACY_SPEED_MIN	(0)

/** The maximum of the world value of signal Accuracy_Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_ACCURACY_SPEED_MAX	(255)


/** Convert the binary value of signal Direction of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT into the world value. */
#define CAP_PT_8392740_DIRECTION_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8392740_DIRECTION_FACTOR+CAP_PT_8392740_DIRECTION_OFFSET)

/** Convert the world value of signal Direction of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8392740_DIRECTION_DBL_TO_BIN(dbl) \
            ((uint8_t)(((dbl)-CAP_PT_8392740_DIRECTION_OFFSET)/CAP_PT_8392740_DIRECTION_FACTOR))

/** The gain factor of the scaling of signal Direction of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_DIRECTION_FACTOR	(2.0)

/** The offset of the scaling of signal Direction of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_DIRECTION_OFFSET	(-1.0)

/** The minimum of the world value of signal Direction of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_DIRECTION_MIN	(-1.0)

/** The maximum of the world value of signal Direction of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_DIRECTION_MAX	(1.0)


/** Convert the binary value of signal Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT into the world value. */
#define CAP_PT_8392740_SPEED_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8392740_SPEED_FACTOR)

/** Convert the world value of signal Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8392740_SPEED_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_8392740_SPEED_FACTOR))

/** The gain factor of the scaling of signal Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_SPEED_FACTOR	(1.0E-5)

/** The offset of the scaling of signal Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_SPEED_OFFSET	(0.0)

/** The minimum of the world value of signal Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_SPEED_MIN	(-20000.0)

/** The maximum of the world value of signal Speed of frame
    RT_DL1MK3_Speed (8392740, 0x801024) on bus PT. */
#define CAP_PT_8392740_SPEED_MAX	(20000.0)

/** The minimum of the world value of signal Validity_GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_VALIDITY_GPS_TIME_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_VALIDITY_GPS_TIME_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Week of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_VALIDITY_GPS_WEEK_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Week of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_VALIDITY_GPS_WEEK_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_ACCURACY_GPS_TIME_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_ACCURACY_GPS_TIME_MAX	(255)


/** Convert the binary value of signal GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT into the world value. */
#define CAP_PT_9175332_GPS_TIME_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9175332_GPS_TIME_FACTOR)

/** Convert the world value of signal GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9175332_GPS_TIME_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_9175332_GPS_TIME_FACTOR))

/** The gain factor of the scaling of signal GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_GPS_TIME_FACTOR	(0.001)

/** The offset of the scaling of signal GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_GPS_TIME_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_GPS_TIME_MIN	(0.0)

/** The maximum of the world value of signal GPS_Time of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_GPS_TIME_MAX	(604800.0)

/** The minimum of the world value of signal GPS_Week of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_GPS_WEEK_MIN	(0)

/** The maximum of the world value of signal GPS_Week of frame
    RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on bus PT. */
#define CAP_PT_9175332_GPS_WEEK_MAX	(65535)


/** Convert the binary value of signal GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT into the world value. */
#define CAP_PT_9175844_GPS_POS_LLH_LONGITUDE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9175844_GPS_POS_LLH_LONGITUDE_FACTOR)

/** Convert the world value of signal GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9175844_GPS_POS_LLH_LONGITUDE_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9175844_GPS_POS_LLH_LONGITUDE_FACTOR))

/** The gain factor of the scaling of signal GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. */
#define CAP_PT_9175844_GPS_POS_LLH_LONGITUDE_FACTOR	(1.0E-7)

/** The offset of the scaling of signal GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. */
#define CAP_PT_9175844_GPS_POS_LLH_LONGITUDE_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. */
#define CAP_PT_9175844_GPS_POS_LLH_LONGITUDE_MIN	(-180.0)

/** The maximum of the world value of signal GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. */
#define CAP_PT_9175844_GPS_POS_LLH_LONGITUDE_MAX	(180.0)


/** Convert the binary value of signal GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT into the world value. */
#define CAP_PT_9175844_GPS_POS_LLH_ALTITUDE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9175844_GPS_POS_LLH_ALTITUDE_FACTOR)

/** Convert the world value of signal GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9175844_GPS_POS_LLH_ALTITUDE_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9175844_GPS_POS_LLH_ALTITUDE_FACTOR))

/** The gain factor of the scaling of signal GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. */
#define CAP_PT_9175844_GPS_POS_LLH_ALTITUDE_FACTOR	(0.001)

/** The offset of the scaling of signal GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. */
#define CAP_PT_9175844_GPS_POS_LLH_ALTITUDE_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. */
#define CAP_PT_9175844_GPS_POS_LLH_ALTITUDE_MIN	(-1000.0)

/** The maximum of the world value of signal GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on bus PT. */
#define CAP_PT_9175844_GPS_POS_LLH_ALTITUDE_MAX	(100000.0)

/** The minimum of the world value of signal Validity_GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_VALIDITY_GPS_POS_LLH_LATITUDE_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_VALIDITY_GPS_POS_LLH_LATITUDE_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_VALIDITY_GPS_POS_LLH_LONGITUDE_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_VALIDITY_GPS_POS_LLH_LONGITUDE_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_VALIDITY_GPS_POS_LLH_ALTITUDE_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_VALIDITY_GPS_POS_LLH_ALTITUDE_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_ACCURACY_GPS_POS_LLH_LATITUDE_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_ACCURACY_GPS_POS_LLH_LATITUDE_MAX	(255)

/** The minimum of the world value of signal Accuracy_GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_ACCURACY_GPS_POS_LLH_LONGITUDE_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Pos_LLH_Longitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_ACCURACY_GPS_POS_LLH_LONGITUDE_MAX	(255)

/** The minimum of the world value of signal Accuracy_GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_ACCURACY_GPS_POS_LLH_ALTITUDE_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Pos_LLH_Altitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_ACCURACY_GPS_POS_LLH_ALTITUDE_MAX	(255)


/** Convert the binary value of signal GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT into the world value. */
#define CAP_PT_9175588_GPS_POS_LLH_LATITUDE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9175588_GPS_POS_LLH_LATITUDE_FACTOR)

/** Convert the world value of signal GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9175588_GPS_POS_LLH_LATITUDE_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9175588_GPS_POS_LLH_LATITUDE_FACTOR))

/** The gain factor of the scaling of signal GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_GPS_POS_LLH_LATITUDE_FACTOR	(1.0E-7)

/** The offset of the scaling of signal GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_GPS_POS_LLH_LATITUDE_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_GPS_POS_LLH_LATITUDE_MIN	(-90.0)

/** The maximum of the world value of signal GPS_Pos_LLH_Latitude of frame
    RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on bus PT. */
#define CAP_PT_9175588_GPS_POS_LLH_LATITUDE_MAX	(90.0)

/** The minimum of the world value of signal Validity_GPS_Speed_2D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_VALIDITY_GPS_SPEED_2D_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Speed_2D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_VALIDITY_GPS_SPEED_2D_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Speed_3D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_VALIDITY_GPS_SPEED_3D_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Speed_3D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_VALIDITY_GPS_SPEED_3D_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Speed of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_ACCURACY_GPS_SPEED_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Speed of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_ACCURACY_GPS_SPEED_MAX	(255)


/** Convert the binary value of signal GPS_Speed_2D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT into the world value. */
#define CAP_PT_1234_GPS_SPEED_2D_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1234_GPS_SPEED_2D_FACTOR)

/** Convert the world value of signal GPS_Speed_2D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1234_GPS_SPEED_2D_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_1234_GPS_SPEED_2D_FACTOR))

/** The gain factor of the scaling of signal GPS_Speed_2D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_GPS_SPEED_2D_FACTOR	(1.0E-4)

/** The offset of the scaling of signal GPS_Speed_2D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_GPS_SPEED_2D_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Speed_2D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_GPS_SPEED_2D_MIN	(0.0)

/** The maximum of the world value of signal GPS_Speed_2D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_GPS_SPEED_2D_MAX	(1675.0)


/** Convert the binary value of signal GPS_Speed_3D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT into the world value. */
#define CAP_PT_1234_GPS_SPEED_3D_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1234_GPS_SPEED_3D_FACTOR)

/** Convert the world value of signal GPS_Speed_3D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1234_GPS_SPEED_3D_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_1234_GPS_SPEED_3D_FACTOR))

/** The gain factor of the scaling of signal GPS_Speed_3D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_GPS_SPEED_3D_FACTOR	(1.0E-4)

/** The offset of the scaling of signal GPS_Speed_3D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_GPS_SPEED_3D_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Speed_3D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_GPS_SPEED_3D_MIN	(0.0)

/** The maximum of the world value of signal GPS_Speed_3D of frame
    RT_DL1MK3_GPS_Speed (1234, 0x4d2) on bus PT. */
#define CAP_PT_1234_GPS_SPEED_3D_MAX	(1675.0)


/** Convert the binary value of signal IR_Temperature_21 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT into the world value. */
#define CAP_PT_9963045_IR_TEMPERATURE_21_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9963045_IR_TEMPERATURE_21_FACTOR)

/** Convert the world value of signal IR_Temperature_21 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9963045_IR_TEMPERATURE_21_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9963045_IR_TEMPERATURE_21_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_21 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_21_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_21 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_21_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_21 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_21_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_21 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_21_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_22 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT into the world value. */
#define CAP_PT_9963045_IR_TEMPERATURE_22_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9963045_IR_TEMPERATURE_22_FACTOR)

/** Convert the world value of signal IR_Temperature_22 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9963045_IR_TEMPERATURE_22_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9963045_IR_TEMPERATURE_22_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_22 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_22_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_22 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_22_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_22 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_22_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_22 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_22_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_23 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT into the world value. */
#define CAP_PT_9963045_IR_TEMPERATURE_23_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9963045_IR_TEMPERATURE_23_FACTOR)

/** Convert the world value of signal IR_Temperature_23 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9963045_IR_TEMPERATURE_23_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9963045_IR_TEMPERATURE_23_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_23 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_23_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_23 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_23_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_23 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_23_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_23 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_23_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_24 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT into the world value. */
#define CAP_PT_9963045_IR_TEMPERATURE_24_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9963045_IR_TEMPERATURE_24_FACTOR)

/** Convert the world value of signal IR_Temperature_24 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9963045_IR_TEMPERATURE_24_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9963045_IR_TEMPERATURE_24_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_24 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_24_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_24 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_24_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_24 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_24_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_24 of frame
    RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on bus PT. */
#define CAP_PT_9963045_IR_TEMPERATURE_24_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_13 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT into the world value. */
#define CAP_PT_9962533_IR_TEMPERATURE_13_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962533_IR_TEMPERATURE_13_FACTOR)

/** Convert the world value of signal IR_Temperature_13 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962533_IR_TEMPERATURE_13_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962533_IR_TEMPERATURE_13_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_13 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_13_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_13 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_13_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_13 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_13_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_13 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_13_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_14 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT into the world value. */
#define CAP_PT_9962533_IR_TEMPERATURE_14_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962533_IR_TEMPERATURE_14_FACTOR)

/** Convert the world value of signal IR_Temperature_14 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962533_IR_TEMPERATURE_14_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962533_IR_TEMPERATURE_14_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_14 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_14_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_14 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_14_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_14 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_14_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_14 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_14_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_15 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT into the world value. */
#define CAP_PT_9962533_IR_TEMPERATURE_15_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962533_IR_TEMPERATURE_15_FACTOR)

/** Convert the world value of signal IR_Temperature_15 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962533_IR_TEMPERATURE_15_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962533_IR_TEMPERATURE_15_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_15 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_15_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_15 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_15_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_15 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_15_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_15 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_15_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_16 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT into the world value. */
#define CAP_PT_9962533_IR_TEMPERATURE_16_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962533_IR_TEMPERATURE_16_FACTOR)

/** Convert the world value of signal IR_Temperature_16 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962533_IR_TEMPERATURE_16_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962533_IR_TEMPERATURE_16_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_16 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_16_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_16 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_16_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_16 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_16_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_16 of frame
    RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on bus PT. */
#define CAP_PT_9962533_IR_TEMPERATURE_16_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_5 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT into the world value. */
#define CAP_PT_9962021_IR_TEMPERATURE_5_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962021_IR_TEMPERATURE_5_FACTOR)

/** Convert the world value of signal IR_Temperature_5 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962021_IR_TEMPERATURE_5_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962021_IR_TEMPERATURE_5_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_5 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_5_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_5 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_5_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_5 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_5_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_5 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_5_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_6 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT into the world value. */
#define CAP_PT_9962021_IR_TEMPERATURE_6_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962021_IR_TEMPERATURE_6_FACTOR)

/** Convert the world value of signal IR_Temperature_6 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962021_IR_TEMPERATURE_6_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962021_IR_TEMPERATURE_6_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_6 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_6_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_6 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_6_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_6 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_6_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_6 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_6_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_7 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT into the world value. */
#define CAP_PT_9962021_IR_TEMPERATURE_7_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962021_IR_TEMPERATURE_7_FACTOR)

/** Convert the world value of signal IR_Temperature_7 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962021_IR_TEMPERATURE_7_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962021_IR_TEMPERATURE_7_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_7 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_7_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_7 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_7_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_7 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_7_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_7 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_7_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_8 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT into the world value. */
#define CAP_PT_9962021_IR_TEMPERATURE_8_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962021_IR_TEMPERATURE_8_FACTOR)

/** Convert the world value of signal IR_Temperature_8 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962021_IR_TEMPERATURE_8_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962021_IR_TEMPERATURE_8_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_8 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_8_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_8 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_8_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_8 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_8_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_8 of frame
    RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on bus PT. */
#define CAP_PT_9962021_IR_TEMPERATURE_8_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_17 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT into the world value. */
#define CAP_PT_9962789_IR_TEMPERATURE_17_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962789_IR_TEMPERATURE_17_FACTOR)

/** Convert the world value of signal IR_Temperature_17 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962789_IR_TEMPERATURE_17_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962789_IR_TEMPERATURE_17_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_17 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_17_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_17 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_17_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_17 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_17_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_17 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_17_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_18 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT into the world value. */
#define CAP_PT_9962789_IR_TEMPERATURE_18_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962789_IR_TEMPERATURE_18_FACTOR)

/** Convert the world value of signal IR_Temperature_18 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962789_IR_TEMPERATURE_18_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962789_IR_TEMPERATURE_18_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_18 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_18_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_18 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_18_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_18 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_18_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_18 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_18_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_19 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT into the world value. */
#define CAP_PT_9962789_IR_TEMPERATURE_19_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962789_IR_TEMPERATURE_19_FACTOR)

/** Convert the world value of signal IR_Temperature_19 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962789_IR_TEMPERATURE_19_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962789_IR_TEMPERATURE_19_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_19 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_19_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_19 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_19_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_19 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_19_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_19 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_19_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_20 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT into the world value. */
#define CAP_PT_9962789_IR_TEMPERATURE_20_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962789_IR_TEMPERATURE_20_FACTOR)

/** Convert the world value of signal IR_Temperature_20 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962789_IR_TEMPERATURE_20_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962789_IR_TEMPERATURE_20_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_20 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_20_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_20 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_20_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_20 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_20_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_20 of frame
    RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on bus PT. */
#define CAP_PT_9962789_IR_TEMPERATURE_20_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_9 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT into the world value. */
#define CAP_PT_9962277_IR_TEMPERATURE_9_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962277_IR_TEMPERATURE_9_FACTOR)

/** Convert the world value of signal IR_Temperature_9 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962277_IR_TEMPERATURE_9_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962277_IR_TEMPERATURE_9_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_9 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_9_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_9 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_9_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_9 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_9_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_9 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_9_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_10 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT into the world value. */
#define CAP_PT_9962277_IR_TEMPERATURE_10_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962277_IR_TEMPERATURE_10_FACTOR)

/** Convert the world value of signal IR_Temperature_10 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962277_IR_TEMPERATURE_10_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962277_IR_TEMPERATURE_10_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_10 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_10_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_10 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_10_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_10 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_10_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_10 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_10_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_11 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT into the world value. */
#define CAP_PT_9962277_IR_TEMPERATURE_11_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962277_IR_TEMPERATURE_11_FACTOR)

/** Convert the world value of signal IR_Temperature_11 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962277_IR_TEMPERATURE_11_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962277_IR_TEMPERATURE_11_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_11 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_11_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_11 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_11_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_11 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_11_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_11 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_11_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_12 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT into the world value. */
#define CAP_PT_9962277_IR_TEMPERATURE_12_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9962277_IR_TEMPERATURE_12_FACTOR)

/** Convert the world value of signal IR_Temperature_12 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9962277_IR_TEMPERATURE_12_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9962277_IR_TEMPERATURE_12_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_12 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_12_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_12 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_12_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_12 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_12_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_12 of frame
    RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on bus PT. */
#define CAP_PT_9962277_IR_TEMPERATURE_12_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT into the world value. */
#define CAP_PT_9961765_IR_TEMPERATURE_1_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9961765_IR_TEMPERATURE_1_FACTOR)

/** Convert the world value of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9961765_IR_TEMPERATURE_1_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9961765_IR_TEMPERATURE_1_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_1_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_1_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_1_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_1_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_2 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT into the world value. */
#define CAP_PT_9961765_IR_TEMPERATURE_2_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9961765_IR_TEMPERATURE_2_FACTOR)

/** Convert the world value of signal IR_Temperature_2 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9961765_IR_TEMPERATURE_2_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9961765_IR_TEMPERATURE_2_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_2 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_2_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_2 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_2_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_2 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_2_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_2 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_2_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_3 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT into the world value. */
#define CAP_PT_9961765_IR_TEMPERATURE_3_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9961765_IR_TEMPERATURE_3_FACTOR)

/** Convert the world value of signal IR_Temperature_3 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9961765_IR_TEMPERATURE_3_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9961765_IR_TEMPERATURE_3_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_3 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_3_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_3 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_3_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_3 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_3_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_3 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_3_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_4 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT into the world value. */
#define CAP_PT_9961765_IR_TEMPERATURE_4_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9961765_IR_TEMPERATURE_4_FACTOR)

/** Convert the world value of signal IR_Temperature_4 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9961765_IR_TEMPERATURE_4_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9961765_IR_TEMPERATURE_4_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_4 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_4_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_4 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_4_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_4 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_4_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_4 of frame
    RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on bus PT. */
#define CAP_PT_9961765_IR_TEMPERATURE_4_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_30 of frame
    RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT into the world value. */
#define CAP_PT_9510437_IR_TEMPERATURE_30_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9510437_IR_TEMPERATURE_30_FACTOR)

/** Convert the world value of signal IR_Temperature_30 of frame
    RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9510437_IR_TEMPERATURE_30_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9510437_IR_TEMPERATURE_30_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_30 of frame
    RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT. */
#define CAP_PT_9510437_IR_TEMPERATURE_30_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_30 of frame
    RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT. */
#define CAP_PT_9510437_IR_TEMPERATURE_30_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_30 of frame
    RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT. */
#define CAP_PT_9510437_IR_TEMPERATURE_30_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_30 of frame
    RT_IRTemp_Temp_30 (9510437, 0x911e25) on bus PT. */
#define CAP_PT_9510437_IR_TEMPERATURE_30_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_26 of frame
    RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT into the world value. */
#define CAP_PT_9509413_IR_TEMPERATURE_26_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9509413_IR_TEMPERATURE_26_FACTOR)

/** Convert the world value of signal IR_Temperature_26 of frame
    RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9509413_IR_TEMPERATURE_26_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9509413_IR_TEMPERATURE_26_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_26 of frame
    RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT. */
#define CAP_PT_9509413_IR_TEMPERATURE_26_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_26 of frame
    RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT. */
#define CAP_PT_9509413_IR_TEMPERATURE_26_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_26 of frame
    RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT. */
#define CAP_PT_9509413_IR_TEMPERATURE_26_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_26 of frame
    RT_IRTemp_Temp_26 (9509413, 0x911a25) on bus PT. */
#define CAP_PT_9509413_IR_TEMPERATURE_26_MAX	(0.0)


/** Convert the binary value of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT into the world value. */
#define CAP_PT_9503013_IR_TEMPERATURE_1_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9503013_IR_TEMPERATURE_1_FACTOR)

/** Convert the world value of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9503013_IR_TEMPERATURE_1_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9503013_IR_TEMPERATURE_1_FACTOR))

/** The gain factor of the scaling of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT. */
#define CAP_PT_9503013_IR_TEMPERATURE_1_FACTOR	(0.1)

/** The offset of the scaling of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT. */
#define CAP_PT_9503013_IR_TEMPERATURE_1_OFFSET	(0.0)

/** The minimum of the world value of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT. */
#define CAP_PT_9503013_IR_TEMPERATURE_1_MIN	(0.0)

/** The maximum of the world value of signal IR_Temperature_1 of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT. */
#define CAP_PT_9503013_IR_TEMPERATURE_1_MAX	(0.0)

/** The minimum of the world value of signal CRC of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT. */
#define CAP_PT_9503013_CRC_MIN	(1)

/** The maximum of the world value of signal CRC of frame
    RT_IRTemp_Temp_1 (9503013, 0x910125) on bus PT. */
#define CAP_PT_9503013_CRC_MAX	(255)

/** The minimum of the world value of signal Validity_Final_Speed of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT. */
#define CAP_PT_9242402_VALIDITY_FINAL_SPEED_MIN	(0)

/** The maximum of the world value of signal Validity_Final_Speed of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT. */
#define CAP_PT_9242402_VALIDITY_FINAL_SPEED_MAX	(1)


/** Convert the binary value of signal Final_Speed of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT into the world value. */
#define CAP_PT_9242402_FINAL_SPEED_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9242402_FINAL_SPEED_FACTOR)

/** Convert the world value of signal Final_Speed of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9242402_FINAL_SPEED_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_9242402_FINAL_SPEED_FACTOR))

/** The gain factor of the scaling of signal Final_Speed of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT. */
#define CAP_PT_9242402_FINAL_SPEED_FACTOR	(1.0E-4)

/** The offset of the scaling of signal Final_Speed of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT. */
#define CAP_PT_9242402_FINAL_SPEED_OFFSET	(0.0)

/** The minimum of the world value of signal Final_Speed of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT. */
#define CAP_PT_9242402_FINAL_SPEED_MIN	(0.0)

/** The maximum of the world value of signal Final_Speed of frame
    RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on bus PT. */
#define CAP_PT_9242402_FINAL_SPEED_MAX	(1675.0)

/** The minimum of the world value of signal Validity_Initial_Speed of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_VALIDITY_INITIAL_SPEED_MIN	(0)

/** The maximum of the world value of signal Validity_Initial_Speed of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_VALIDITY_INITIAL_SPEED_MAX	(1)

/** The minimum of the world value of signal Validity_Initial_Heading of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_VALIDITY_INITIAL_HEADING_MIN	(0)

/** The maximum of the world value of signal Validity_Initial_Heading of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_VALIDITY_INITIAL_HEADING_MAX	(1)


/** Convert the binary value of signal Initial_Speed of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT into the world value. */
#define CAP_PT_794_INITIAL_SPEED_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_794_INITIAL_SPEED_FACTOR)

/** Convert the world value of signal Initial_Speed of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_794_INITIAL_SPEED_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_794_INITIAL_SPEED_FACTOR))

/** The gain factor of the scaling of signal Initial_Speed of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_INITIAL_SPEED_FACTOR	(1.0E-4)

/** The offset of the scaling of signal Initial_Speed of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_INITIAL_SPEED_OFFSET	(0.0)

/** The minimum of the world value of signal Initial_Speed of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_INITIAL_SPEED_MIN	(0.0)

/** The maximum of the world value of signal Initial_Speed of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_INITIAL_SPEED_MAX	(1675.0)


/** Convert the binary value of signal Initial_Heading of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT into the world value. */
#define CAP_PT_794_INITIAL_HEADING_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_794_INITIAL_HEADING_FACTOR)

/** Convert the world value of signal Initial_Heading of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_794_INITIAL_HEADING_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_794_INITIAL_HEADING_FACTOR))

/** The gain factor of the scaling of signal Initial_Heading of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_INITIAL_HEADING_FACTOR	(0.01)

/** The offset of the scaling of signal Initial_Heading of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_INITIAL_HEADING_OFFSET	(0.0)

/** The minimum of the world value of signal Initial_Heading of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_INITIAL_HEADING_MIN	(-180.0)

/** The maximum of the world value of signal Initial_Heading of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_INITIAL_HEADING_MAX	(180.0)

/** The minimum of the world value of signal MFDD_Start_Threshold of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_MFDD_START_THRESHOLD_MIN	(0)

/** The maximum of the world value of signal MFDD_Start_Threshold of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_MFDD_START_THRESHOLD_MAX	(100)

/** The minimum of the world value of signal MFDD_End_Threshold of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_MFDD_END_THRESHOLD_MIN	(0)

/** The maximum of the world value of signal MFDD_End_Threshold of frame
    RT_SB_Trig_Initial_Condition (794, 0x31a) on bus PT. */
#define CAP_PT_794_MFDD_END_THRESHOLD_MAX	(100)


/** Convert the binary value of signal Direct_Distance of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT into the world value. */
#define CAP_PT_9241890_DIRECT_DISTANCE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9241890_DIRECT_DISTANCE_FACTOR)

/** Convert the world value of signal Direct_Distance of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9241890_DIRECT_DISTANCE_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_9241890_DIRECT_DISTANCE_FACTOR))

/** The gain factor of the scaling of signal Direct_Distance of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. */
#define CAP_PT_9241890_DIRECT_DISTANCE_FACTOR	(0.001)

/** The offset of the scaling of signal Direct_Distance of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. */
#define CAP_PT_9241890_DIRECT_DISTANCE_OFFSET	(0.0)

/** The minimum of the world value of signal Direct_Distance of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. */
#define CAP_PT_9241890_DIRECT_DISTANCE_MIN	(0.0)

/** The maximum of the world value of signal Direct_Distance of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. */
#define CAP_PT_9241890_DIRECT_DISTANCE_MAX	(4294970.0)


/** Convert the binary value of signal Path_Distance_2D of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT into the world value. */
#define CAP_PT_9241890_PATH_DISTANCE_2D_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9241890_PATH_DISTANCE_2D_FACTOR)

/** Convert the world value of signal Path_Distance_2D of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9241890_PATH_DISTANCE_2D_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_9241890_PATH_DISTANCE_2D_FACTOR))

/** The gain factor of the scaling of signal Path_Distance_2D of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. */
#define CAP_PT_9241890_PATH_DISTANCE_2D_FACTOR	(0.001)

/** The offset of the scaling of signal Path_Distance_2D of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. */
#define CAP_PT_9241890_PATH_DISTANCE_2D_OFFSET	(0.0)

/** The minimum of the world value of signal Path_Distance_2D of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. */
#define CAP_PT_9241890_PATH_DISTANCE_2D_MIN	(0.0)

/** The maximum of the world value of signal Path_Distance_2D of frame
    RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on bus PT. */
#define CAP_PT_9241890_PATH_DISTANCE_2D_MAX	(4294970.0)


/** Convert the binary value of signal Forward_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT into the world value. */
#define CAP_PT_9241634_FORWARD_DISTANCE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9241634_FORWARD_DISTANCE_FACTOR)

/** Convert the world value of signal Forward_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9241634_FORWARD_DISTANCE_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9241634_FORWARD_DISTANCE_FACTOR))

/** The gain factor of the scaling of signal Forward_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. */
#define CAP_PT_9241634_FORWARD_DISTANCE_FACTOR	(0.001)

/** The offset of the scaling of signal Forward_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. */
#define CAP_PT_9241634_FORWARD_DISTANCE_OFFSET	(0.0)

/** The minimum of the world value of signal Forward_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. */
#define CAP_PT_9241634_FORWARD_DISTANCE_MIN	(-2147480.0)

/** The maximum of the world value of signal Forward_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. */
#define CAP_PT_9241634_FORWARD_DISTANCE_MAX	(2147480.0)


/** Convert the binary value of signal Deviation_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT into the world value. */
#define CAP_PT_9241634_DEVIATION_DISTANCE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9241634_DEVIATION_DISTANCE_FACTOR)

/** Convert the world value of signal Deviation_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9241634_DEVIATION_DISTANCE_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9241634_DEVIATION_DISTANCE_FACTOR))

/** The gain factor of the scaling of signal Deviation_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. */
#define CAP_PT_9241634_DEVIATION_DISTANCE_FACTOR	(0.001)

/** The offset of the scaling of signal Deviation_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. */
#define CAP_PT_9241634_DEVIATION_DISTANCE_OFFSET	(0.0)

/** The minimum of the world value of signal Deviation_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. */
#define CAP_PT_9241634_DEVIATION_DISTANCE_MIN	(-2147480.0)

/** The maximum of the world value of signal Deviation_Distance of frame
    RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on bus PT. */
#define CAP_PT_9241634_DEVIATION_DISTANCE_MAX	(2147480.0)


/** Convert the binary value of signal Path_Distance_3D of frame
    RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT into the world value. */
#define CAP_PT_9241378_PATH_DISTANCE_3D_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9241378_PATH_DISTANCE_3D_FACTOR)

/** Convert the world value of signal Path_Distance_3D of frame
    RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9241378_PATH_DISTANCE_3D_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_9241378_PATH_DISTANCE_3D_FACTOR))

/** The gain factor of the scaling of signal Path_Distance_3D of frame
    RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT. */
#define CAP_PT_9241378_PATH_DISTANCE_3D_FACTOR	(0.001)

/** The offset of the scaling of signal Path_Distance_3D of frame
    RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT. */
#define CAP_PT_9241378_PATH_DISTANCE_3D_OFFSET	(0.0)

/** The minimum of the world value of signal Path_Distance_3D of frame
    RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT. */
#define CAP_PT_9241378_PATH_DISTANCE_3D_MIN	(0.0)

/** The maximum of the world value of signal Path_Distance_3D of frame
    RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on bus PT. */
#define CAP_PT_9241378_PATH_DISTANCE_3D_MAX	(4294970.0)

/** The minimum of the world value of signal Validity_MFDD of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_VALIDITY_MFDD_MIN	(0)

/** The maximum of the world value of signal Validity_MFDD of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_VALIDITY_MFDD_MAX	(1)

/** The minimum of the world value of signal Validity_Average_Accel of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_VALIDITY_AVERAGE_ACCEL_MIN	(0)

/** The maximum of the world value of signal Validity_Average_Accel of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_VALIDITY_AVERAGE_ACCEL_MAX	(1)

/** The minimum of the world value of signal Validity_Triggered_Time of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_VALIDITY_TRIGGERED_TIME_MIN	(0)

/** The maximum of the world value of signal Validity_Triggered_Time of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_VALIDITY_TRIGGERED_TIME_MAX	(1)


/** Convert the binary value of signal MFDD of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT into the world value. */
#define CAP_PT_9241122_MFDD_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9241122_MFDD_FACTOR)

/** Convert the world value of signal MFDD of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9241122_MFDD_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9241122_MFDD_FACTOR))

/** The gain factor of the scaling of signal MFDD of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_MFDD_FACTOR	(0.001)

/** The offset of the scaling of signal MFDD of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_MFDD_OFFSET	(0.0)

/** The minimum of the world value of signal MFDD of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_MFDD_MIN	(-65.0)

/** The maximum of the world value of signal MFDD of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_MFDD_MAX	(65.0)


/** Convert the binary value of signal Average_Accel of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT into the world value. */
#define CAP_PT_9241122_AVERAGE_ACCEL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9241122_AVERAGE_ACCEL_FACTOR)

/** Convert the world value of signal Average_Accel of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9241122_AVERAGE_ACCEL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9241122_AVERAGE_ACCEL_FACTOR))

/** The gain factor of the scaling of signal Average_Accel of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_AVERAGE_ACCEL_FACTOR	(0.001)

/** The offset of the scaling of signal Average_Accel of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_AVERAGE_ACCEL_OFFSET	(0.0)

/** The minimum of the world value of signal Average_Accel of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_AVERAGE_ACCEL_MIN	(-65.0)

/** The maximum of the world value of signal Average_Accel of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_AVERAGE_ACCEL_MAX	(65.0)


/** Convert the binary value of signal Triggered_Time of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT into the world value. */
#define CAP_PT_9241122_TRIGGERED_TIME_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9241122_TRIGGERED_TIME_FACTOR)

/** Convert the world value of signal Triggered_Time of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9241122_TRIGGERED_TIME_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_9241122_TRIGGERED_TIME_FACTOR))

/** The gain factor of the scaling of signal Triggered_Time of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_TRIGGERED_TIME_FACTOR	(0.01)

/** The offset of the scaling of signal Triggered_Time of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_TRIGGERED_TIME_OFFSET	(0.0)

/** The minimum of the world value of signal Triggered_Time of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_TRIGGERED_TIME_MIN	(0.0)

/** The maximum of the world value of signal Triggered_Time of frame
    RT_SB_Trig_Accel (9241122, 0x8d0222) on bus PT. */
#define CAP_PT_9241122_TRIGGERED_TIME_MAX	(167772.0)

/** The minimum of the world value of signal Measured_Time_12 of frame
    RT_DL1MK3_Measure_Time_12 (9833508, 0x960c24) on bus PT. */
#define CAP_PT_9833508_MEASURED_TIME_12_MIN	(0)

/** The maximum of the world value of signal Measured_Time_12 of frame
    RT_DL1MK3_Measure_Time_12 (9833508, 0x960c24) on bus PT. */
#define CAP_PT_9833508_MEASURED_TIME_12_MAX	(0)

/** The minimum of the world value of signal Measured_Time_11 of frame
    RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT. */
#define CAP_PT_9833252_MEASURED_TIME_11_MIN	(0)

/** The maximum of the world value of signal Measured_Time_11 of frame
    RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on bus PT. */
#define CAP_PT_9833252_MEASURED_TIME_11_MAX	(0)

/** The minimum of the world value of signal Measured_Time_10 of frame
    RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT. */
#define CAP_PT_9832996_MEASURED_TIME_10_MIN	(0)

/** The maximum of the world value of signal Measured_Time_10 of frame
    RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on bus PT. */
#define CAP_PT_9832996_MEASURED_TIME_10_MAX	(0)

/** The minimum of the world value of signal Measured_Time_9 of frame
    RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT. */
#define CAP_PT_9832740_MEASURED_TIME_9_MIN	(0)

/** The maximum of the world value of signal Measured_Time_9 of frame
    RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on bus PT. */
#define CAP_PT_9832740_MEASURED_TIME_9_MAX	(0)

/** The minimum of the world value of signal Measured_Time_8 of frame
    RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT. */
#define CAP_PT_9832484_MEASURED_TIME_8_MIN	(0)

/** The maximum of the world value of signal Measured_Time_8 of frame
    RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on bus PT. */
#define CAP_PT_9832484_MEASURED_TIME_8_MAX	(0)

/** The minimum of the world value of signal Measured_Time_7 of frame
    RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT. */
#define CAP_PT_9832228_MEASURED_TIME_7_MIN	(0)

/** The maximum of the world value of signal Measured_Time_7 of frame
    RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on bus PT. */
#define CAP_PT_9832228_MEASURED_TIME_7_MAX	(0)

/** The minimum of the world value of signal Measured_Time_6 of frame
    RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT. */
#define CAP_PT_9831972_MEASURED_TIME_6_MIN	(0)

/** The maximum of the world value of signal Measured_Time_6 of frame
    RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on bus PT. */
#define CAP_PT_9831972_MEASURED_TIME_6_MAX	(0)

/** The minimum of the world value of signal Measured_Time_5 of frame
    RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT. */
#define CAP_PT_9831716_MEASURED_TIME_5_MIN	(0)

/** The maximum of the world value of signal Measured_Time_5 of frame
    RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on bus PT. */
#define CAP_PT_9831716_MEASURED_TIME_5_MAX	(0)

/** The minimum of the world value of signal Measured_Time_4 of frame
    RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT. */
#define CAP_PT_9831460_MEASURED_TIME_4_MIN	(0)

/** The maximum of the world value of signal Measured_Time_4 of frame
    RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on bus PT. */
#define CAP_PT_9831460_MEASURED_TIME_4_MAX	(0)

/** The minimum of the world value of signal Measured_Time_3 of frame
    RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT. */
#define CAP_PT_9831204_MEASURED_TIME_3_MIN	(0)

/** The maximum of the world value of signal Measured_Time_3 of frame
    RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on bus PT. */
#define CAP_PT_9831204_MEASURED_TIME_3_MAX	(0)

/** The minimum of the world value of signal Measured_Time_2 of frame
    RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT. */
#define CAP_PT_9830948_MEASURED_TIME_2_MIN	(0)

/** The maximum of the world value of signal Measured_Time_2 of frame
    RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on bus PT. */
#define CAP_PT_9830948_MEASURED_TIME_2_MAX	(0)

/** The minimum of the world value of signal Measured_Time_1 of frame
    RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT. */
#define CAP_PT_9830692_MEASURED_TIME_1_MIN	(0)

/** The maximum of the world value of signal Measured_Time_1 of frame
    RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on bus PT. */
#define CAP_PT_9830692_MEASURED_TIME_1_MAX	(0)

/** The minimum of the world value of signal RPM of frame
    RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT. */
#define CAP_PT_9767972_RPM_MIN	(0)

/** The maximum of the world value of signal RPM of frame
    RT_DL1MK3_RPM (9767972, 0x950c24) on bus PT. */
#define CAP_PT_9767972_RPM_MAX	(0)


/** Convert the binary value of signal Frequency_4 of frame
    RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT into the world value. */
#define CAP_PT_9767716_FREQUENCY_4_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9767716_FREQUENCY_4_FACTOR)

/** Convert the world value of signal Frequency_4 of frame
    RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9767716_FREQUENCY_4_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_9767716_FREQUENCY_4_FACTOR))

/** The gain factor of the scaling of signal Frequency_4 of frame
    RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT. */
#define CAP_PT_9767716_FREQUENCY_4_FACTOR	(0.1)

/** The offset of the scaling of signal Frequency_4 of frame
    RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT. */
#define CAP_PT_9767716_FREQUENCY_4_OFFSET	(0.0)

/** The minimum of the world value of signal Frequency_4 of frame
    RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT. */
#define CAP_PT_9767716_FREQUENCY_4_MIN	(0.0)

/** The maximum of the world value of signal Frequency_4 of frame
    RT_DL1MK3_Freq_4 (9767716, 0x950b24) on bus PT. */
#define CAP_PT_9767716_FREQUENCY_4_MAX	(0.0)


/** Convert the binary value of signal Misc_3 of frame
    RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT into the world value. */
#define CAP_PT_9896740_MISC_3_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9896740_MISC_3_FACTOR)

/** Convert the world value of signal Misc_3 of frame
    RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9896740_MISC_3_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_9896740_MISC_3_FACTOR))

/** The gain factor of the scaling of signal Misc_3 of frame
    RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT. */
#define CAP_PT_9896740_MISC_3_FACTOR	(0.001)

/** The offset of the scaling of signal Misc_3 of frame
    RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT. */
#define CAP_PT_9896740_MISC_3_OFFSET	(0.0)

/** The minimum of the world value of signal Misc_3 of frame
    RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT. */
#define CAP_PT_9896740_MISC_3_MIN	(0.0)

/** The maximum of the world value of signal Misc_3 of frame
    RT_DL1MK3_Misc_3 (9896740, 0x970324) on bus PT. */
#define CAP_PT_9896740_MISC_3_MAX	(0.0)


/** Convert the binary value of signal Misc_2 of frame
    RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT into the world value. */
#define CAP_PT_9896484_MISC_2_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9896484_MISC_2_FACTOR)

/** Convert the world value of signal Misc_2 of frame
    RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9896484_MISC_2_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_9896484_MISC_2_FACTOR))

/** The gain factor of the scaling of signal Misc_2 of frame
    RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT. */
#define CAP_PT_9896484_MISC_2_FACTOR	(0.001)

/** The offset of the scaling of signal Misc_2 of frame
    RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT. */
#define CAP_PT_9896484_MISC_2_OFFSET	(0.0)

/** The minimum of the world value of signal Misc_2 of frame
    RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT. */
#define CAP_PT_9896484_MISC_2_MIN	(0.0)

/** The maximum of the world value of signal Misc_2 of frame
    RT_DL1MK3_Misc_2 (9896484, 0x970224) on bus PT. */
#define CAP_PT_9896484_MISC_2_MAX	(0.0)


/** Convert the binary value of signal Misc_1 of frame
    RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT into the world value. */
#define CAP_PT_9896228_MISC_1_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9896228_MISC_1_FACTOR)

/** Convert the world value of signal Misc_1 of frame
    RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9896228_MISC_1_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_9896228_MISC_1_FACTOR))

/** The gain factor of the scaling of signal Misc_1 of frame
    RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT. */
#define CAP_PT_9896228_MISC_1_FACTOR	(0.001)

/** The offset of the scaling of signal Misc_1 of frame
    RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT. */
#define CAP_PT_9896228_MISC_1_OFFSET	(0.0)

/** The minimum of the world value of signal Misc_1 of frame
    RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT. */
#define CAP_PT_9896228_MISC_1_MIN	(0.0)

/** The maximum of the world value of signal Misc_1 of frame
    RT_DL1MK3_Misc_1 (9896228, 0x970124) on bus PT. */
#define CAP_PT_9896228_MISC_1_MAX	(0.0)


/** Convert the binary value of signal AUX_2 of frame
    RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT into the world value. */
#define CAP_PT_9699876_AUX_2_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9699876_AUX_2_FACTOR)

/** Convert the world value of signal AUX_2 of frame
    RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9699876_AUX_2_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_9699876_AUX_2_FACTOR))

/** The gain factor of the scaling of signal AUX_2 of frame
    RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT. */
#define CAP_PT_9699876_AUX_2_FACTOR	(0.1)

/** The offset of the scaling of signal AUX_2 of frame
    RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT. */
#define CAP_PT_9699876_AUX_2_OFFSET	(0.0)

/** The minimum of the world value of signal AUX_2 of frame
    RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT. */
#define CAP_PT_9699876_AUX_2_MIN	(0.0)

/** The maximum of the world value of signal AUX_2 of frame
    RT_DL1MK3_Aux_2 (9699876, 0x940224) on bus PT. */
#define CAP_PT_9699876_AUX_2_MAX	(0.0)


/** Convert the binary value of signal AUX_1 of frame
    RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT into the world value. */
#define CAP_PT_9699620_AUX_1_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9699620_AUX_1_FACTOR)

/** Convert the world value of signal AUX_1 of frame
    RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9699620_AUX_1_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_9699620_AUX_1_FACTOR))

/** The gain factor of the scaling of signal AUX_1 of frame
    RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT. */
#define CAP_PT_9699620_AUX_1_FACTOR	(0.1)

/** The offset of the scaling of signal AUX_1 of frame
    RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT. */
#define CAP_PT_9699620_AUX_1_OFFSET	(0.0)

/** The minimum of the world value of signal AUX_1 of frame
    RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT. */
#define CAP_PT_9699620_AUX_1_MIN	(0.0)

/** The maximum of the world value of signal AUX_1 of frame
    RT_DL1MK3_Aux_1 (9699620, 0x940124) on bus PT. */
#define CAP_PT_9699620_AUX_1_MAX	(0.0)


/** Convert the binary value of signal Pressure_5 of frame
    RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT into the world value. */
#define CAP_PT_9438500_PRESSURE_5_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9438500_PRESSURE_5_FACTOR)

/** Convert the world value of signal Pressure_5 of frame
    RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9438500_PRESSURE_5_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_9438500_PRESSURE_5_FACTOR))

/** The gain factor of the scaling of signal Pressure_5 of frame
    RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT. */
#define CAP_PT_9438500_PRESSURE_5_FACTOR	(0.1)

/** The offset of the scaling of signal Pressure_5 of frame
    RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT. */
#define CAP_PT_9438500_PRESSURE_5_OFFSET	(0.0)

/** The minimum of the world value of signal Pressure_5 of frame
    RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT. */
#define CAP_PT_9438500_PRESSURE_5_MIN	(0.0)

/** The maximum of the world value of signal Pressure_5 of frame
    RT_DL1MK3_Pressure_5 (9438500, 0x900524) on bus PT. */
#define CAP_PT_9438500_PRESSURE_5_MAX	(0.0)


/** Convert the binary value of signal Angle_3 of frame
    RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT into the world value. */
#define CAP_PT_9569060_ANGLE_3_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9569060_ANGLE_3_FACTOR)

/** Convert the world value of signal Angle_3 of frame
    RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9569060_ANGLE_3_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9569060_ANGLE_3_FACTOR))

/** The gain factor of the scaling of signal Angle_3 of frame
    RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT. */
#define CAP_PT_9569060_ANGLE_3_FACTOR	(0.1)

/** The offset of the scaling of signal Angle_3 of frame
    RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT. */
#define CAP_PT_9569060_ANGLE_3_OFFSET	(0.0)

/** The minimum of the world value of signal Angle_3 of frame
    RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT. */
#define CAP_PT_9569060_ANGLE_3_MIN	(0.0)

/** The maximum of the world value of signal Angle_3 of frame
    RT_DL1MK3_Angle_3 (9569060, 0x920324) on bus PT. */
#define CAP_PT_9569060_ANGLE_3_MAX	(0.0)


/** Convert the binary value of signal Temperature_1 of frame
    RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT into the world value. */
#define CAP_PT_9503012_TEMPERATURE_1_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9503012_TEMPERATURE_1_FACTOR)

/** Convert the world value of signal Temperature_1 of frame
    RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9503012_TEMPERATURE_1_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9503012_TEMPERATURE_1_FACTOR))

/** The gain factor of the scaling of signal Temperature_1 of frame
    RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT. */
#define CAP_PT_9503012_TEMPERATURE_1_FACTOR	(0.1)

/** The offset of the scaling of signal Temperature_1 of frame
    RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT. */
#define CAP_PT_9503012_TEMPERATURE_1_OFFSET	(0.0)

/** The minimum of the world value of signal Temperature_1 of frame
    RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT. */
#define CAP_PT_9503012_TEMPERATURE_1_MIN	(0.0)

/** The maximum of the world value of signal Temperature_1 of frame
    RT_DL1MK3_Temp_1 (9503012, 0x910124) on bus PT. */
#define CAP_PT_9503012_TEMPERATURE_1_MAX	(0.0)


/** Convert the binary value of signal Analog_3 of frame
    RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT into the world value. */
#define CAP_PT_8520228_ANALOG_3_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8520228_ANALOG_3_FACTOR)

/** Convert the world value of signal Analog_3 of frame
    RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8520228_ANALOG_3_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_8520228_ANALOG_3_FACTOR))

/** The gain factor of the scaling of signal Analog_3 of frame
    RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT. */
#define CAP_PT_8520228_ANALOG_3_FACTOR	(0.001)

/** The offset of the scaling of signal Analog_3 of frame
    RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT. */
#define CAP_PT_8520228_ANALOG_3_OFFSET	(0.0)

/** The minimum of the world value of signal Analog_3 of frame
    RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT. */
#define CAP_PT_8520228_ANALOG_3_MIN	(0.0)

/** The maximum of the world value of signal Analog_3 of frame
    RT_DL1MK3_Analog_3 (8520228, 0x820224) on bus PT. */
#define CAP_PT_8520228_ANALOG_3_MAX	(0.0)


/** Convert the binary value of signal Analog_2 of frame
    RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT into the world value. */
#define CAP_PT_8519972_ANALOG_2_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8519972_ANALOG_2_FACTOR)

/** Convert the world value of signal Analog_2 of frame
    RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8519972_ANALOG_2_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_8519972_ANALOG_2_FACTOR))

/** The gain factor of the scaling of signal Analog_2 of frame
    RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT. */
#define CAP_PT_8519972_ANALOG_2_FACTOR	(0.001)

/** The offset of the scaling of signal Analog_2 of frame
    RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT. */
#define CAP_PT_8519972_ANALOG_2_OFFSET	(0.0)

/** The minimum of the world value of signal Analog_2 of frame
    RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT. */
#define CAP_PT_8519972_ANALOG_2_MIN	(0.0)

/** The maximum of the world value of signal Analog_2 of frame
    RT_DL1MK3_Analog_2 (8519972, 0x820124) on bus PT. */
#define CAP_PT_8519972_ANALOG_2_MAX	(0.0)


/** Convert the binary value of signal Analog_1 of frame
    RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT into the world value. */
#define CAP_PT_8519716_ANALOG_1_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8519716_ANALOG_1_FACTOR)

/** Convert the world value of signal Analog_1 of frame
    RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8519716_ANALOG_1_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_8519716_ANALOG_1_FACTOR))

/** The gain factor of the scaling of signal Analog_1 of frame
    RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT. */
#define CAP_PT_8519716_ANALOG_1_FACTOR	(0.001)

/** The offset of the scaling of signal Analog_1 of frame
    RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT. */
#define CAP_PT_8519716_ANALOG_1_OFFSET	(0.0)

/** The minimum of the world value of signal Analog_1 of frame
    RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT. */
#define CAP_PT_8519716_ANALOG_1_MIN	(0.0)

/** The maximum of the world value of signal Analog_1 of frame
    RT_DL1MK3_Analog_1 (8519716, 0x820024) on bus PT. */
#define CAP_PT_8519716_ANALOG_1_MAX	(0.0)

/** The minimum of the world value of signal Validity_Accel_Longitudinal of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_VALIDITY_ACCEL_LONGITUDINAL_MIN	(0)

/** The maximum of the world value of signal Validity_Accel_Longitudinal of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_VALIDITY_ACCEL_LONGITUDINAL_MAX	(1)

/** The minimum of the world value of signal Validity_Accel_Lateral of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_VALIDITY_ACCEL_LATERAL_MIN	(0)

/** The maximum of the world value of signal Validity_Accel_Lateral of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_VALIDITY_ACCEL_LATERAL_MAX	(1)

/** The minimum of the world value of signal Validity_Accel_Vertical of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_VALIDITY_ACCEL_VERTICAL_MIN	(0)

/** The maximum of the world value of signal Validity_Accel_Vertical of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_VALIDITY_ACCEL_VERTICAL_MAX	(1)

/** The minimum of the world value of signal SQC of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_SQC_MIN	(0)

/** The maximum of the world value of signal SQC of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_SQC_MAX	(14)

/** The minimum of the world value of signal Accuracy_Accel of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCURACY_ACCEL_MIN	(0)

/** The maximum of the world value of signal Accuracy_Accel of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCURACY_ACCEL_MAX	(255)


/** Convert the binary value of signal Accel_Longitudinal of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT into the world value. */
#define CAP_PT_8388644_ACCEL_LONGITUDINAL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388644_ACCEL_LONGITUDINAL_FACTOR)

/** Convert the world value of signal Accel_Longitudinal of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388644_ACCEL_LONGITUDINAL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388644_ACCEL_LONGITUDINAL_FACTOR))

/** The gain factor of the scaling of signal Accel_Longitudinal of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_LONGITUDINAL_FACTOR	(0.001)

/** The offset of the scaling of signal Accel_Longitudinal of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_LONGITUDINAL_OFFSET	(0.0)

/** The minimum of the world value of signal Accel_Longitudinal of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_LONGITUDINAL_MIN	(-65.0)

/** The maximum of the world value of signal Accel_Longitudinal of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_LONGITUDINAL_MAX	(65.0)


/** Convert the binary value of signal Accel_Lateral of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT into the world value. */
#define CAP_PT_8388644_ACCEL_LATERAL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388644_ACCEL_LATERAL_FACTOR)

/** Convert the world value of signal Accel_Lateral of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388644_ACCEL_LATERAL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388644_ACCEL_LATERAL_FACTOR))

/** The gain factor of the scaling of signal Accel_Lateral of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_LATERAL_FACTOR	(0.001)

/** The offset of the scaling of signal Accel_Lateral of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_LATERAL_OFFSET	(0.0)

/** The minimum of the world value of signal Accel_Lateral of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_LATERAL_MIN	(-65.0)

/** The maximum of the world value of signal Accel_Lateral of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_LATERAL_MAX	(65.0)


/** Convert the binary value of signal Accel_Vertical of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT into the world value. */
#define CAP_PT_8388644_ACCEL_VERTICAL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388644_ACCEL_VERTICAL_FACTOR)

/** Convert the world value of signal Accel_Vertical of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388644_ACCEL_VERTICAL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388644_ACCEL_VERTICAL_FACTOR))

/** The gain factor of the scaling of signal Accel_Vertical of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_VERTICAL_FACTOR	(0.001)

/** The offset of the scaling of signal Accel_Vertical of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_VERTICAL_OFFSET	(0.0)

/** The minimum of the world value of signal Accel_Vertical of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_VERTICAL_MIN	(-65.0)

/** The maximum of the world value of signal Accel_Vertical of frame
    RT_DL1MK3_Accel (8388644, 0x800024) on bus PT. */
#define CAP_PT_8388644_ACCEL_VERTICAL_MAX	(65.0)

/** The minimum of the world value of signal INS_Status of frame
    RT_SB_INS_Status (9306146, 0x8e0022) on bus PT. */
#define CAP_PT_9306146_INS_STATUS_MIN	(0)

/** The maximum of the world value of signal INS_Status of frame
    RT_SB_INS_Status (9306146, 0x8e0022) on bus PT. */
#define CAP_PT_9306146_INS_STATUS_MAX	(255)

/** The minimum of the world value of signal Validity_Yaw of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_VALIDITY_YAW_MIN	(0)

/** The maximum of the world value of signal Validity_Yaw of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_VALIDITY_YAW_MAX	(1)

/** The minimum of the world value of signal Validity_Pitch of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_VALIDITY_PITCH_MIN	(0)

/** The maximum of the world value of signal Validity_Pitch of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_VALIDITY_PITCH_MAX	(1)

/** The minimum of the world value of signal Validity_Roll of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_VALIDITY_ROLL_MIN	(0)

/** The maximum of the world value of signal Validity_Roll of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_VALIDITY_ROLL_MAX	(1)

/** The minimum of the world value of signal Accuracy_Attitude of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ACCURACY_ATTITUDE_MIN	(0)

/** The maximum of the world value of signal Accuracy_Attitude of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ACCURACY_ATTITUDE_MAX	(255)


/** Convert the binary value of signal Attitude_Yaw of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT into the world value. */
#define CAP_PT_9306402_ATTITUDE_YAW_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9306402_ATTITUDE_YAW_FACTOR)

/** Convert the world value of signal Attitude_Yaw of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9306402_ATTITUDE_YAW_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9306402_ATTITUDE_YAW_FACTOR))

/** The gain factor of the scaling of signal Attitude_Yaw of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_YAW_FACTOR	(0.01)

/** The offset of the scaling of signal Attitude_Yaw of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_YAW_OFFSET	(0.0)

/** The minimum of the world value of signal Attitude_Yaw of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_YAW_MIN	(-360.0)

/** The maximum of the world value of signal Attitude_Yaw of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_YAW_MAX	(360.0)


/** Convert the binary value of signal Attitude_Pitch of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT into the world value. */
#define CAP_PT_9306402_ATTITUDE_PITCH_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9306402_ATTITUDE_PITCH_FACTOR)

/** Convert the world value of signal Attitude_Pitch of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9306402_ATTITUDE_PITCH_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9306402_ATTITUDE_PITCH_FACTOR))

/** The gain factor of the scaling of signal Attitude_Pitch of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_PITCH_FACTOR	(0.01)

/** The offset of the scaling of signal Attitude_Pitch of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_PITCH_OFFSET	(0.0)

/** The minimum of the world value of signal Attitude_Pitch of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_PITCH_MIN	(-360.0)

/** The maximum of the world value of signal Attitude_Pitch of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_PITCH_MAX	(360.0)


/** Convert the binary value of signal Attitude_Roll of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT into the world value. */
#define CAP_PT_9306402_ATTITUDE_ROLL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9306402_ATTITUDE_ROLL_FACTOR)

/** Convert the world value of signal Attitude_Roll of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9306402_ATTITUDE_ROLL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9306402_ATTITUDE_ROLL_FACTOR))

/** The gain factor of the scaling of signal Attitude_Roll of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_ROLL_FACTOR	(0.01)

/** The offset of the scaling of signal Attitude_Roll of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_ROLL_OFFSET	(0.0)

/** The minimum of the world value of signal Attitude_Roll of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_ROLL_MIN	(-360.0)

/** The maximum of the world value of signal Attitude_Roll of frame
    RT_SB_INS_Attitude (9306402, 0x8e0122) on bus PT. */
#define CAP_PT_9306402_ATTITUDE_ROLL_MAX	(360.0)

/** The minimum of the world value of signal Validity_Status_Timestamp of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_VALIDITY_STATUS_TIMESTAMP_MIN	(0)

/** The maximum of the world value of signal Validity_Status_Timestamp of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_VALIDITY_STATUS_TIMESTAMP_MAX	(1)

/** The minimum of the world value of signal Status_Analogue_1 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_ANALOGUE_1_MIN	(0)

/** The maximum of the world value of signal Status_Analogue_1 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_ANALOGUE_1_MAX	(1)

/** The minimum of the world value of signal Status_Analogue_2 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_ANALOGUE_2_MIN	(0)

/** The maximum of the world value of signal Status_Analogue_2 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_ANALOGUE_2_MAX	(1)

/** The minimum of the world value of signal Status_Analogue_3 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_ANALOGUE_3_MIN	(0)

/** The maximum of the world value of signal Status_Analogue_3 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_ANALOGUE_3_MAX	(1)

/** The minimum of the world value of signal Status_Analogue_4 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_ANALOGUE_4_MIN	(0)

/** The maximum of the world value of signal Status_Analogue_4 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_ANALOGUE_4_MAX	(1)

/** The minimum of the world value of signal Status_Pulse_Output of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_PULSE_OUTPUT_MIN	(0)

/** The maximum of the world value of signal Status_Pulse_Output of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_PULSE_OUTPUT_MAX	(1)

/** The minimum of the world value of signal Status_Serial_Output_1 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_SERIAL_OUTPUT_1_MIN	(0)

/** The maximum of the world value of signal Status_Serial_Output_1 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_SERIAL_OUTPUT_1_MAX	(1)

/** The minimum of the world value of signal Status_Serial_Output_2 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_SERIAL_OUTPUT_2_MIN	(0)

/** The maximum of the world value of signal Status_Serial_Output_2 of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_SERIAL_OUTPUT_2_MAX	(1)

/** The minimum of the world value of signal Status_Trigger of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_TRIGGER_MIN	(0)

/** The maximum of the world value of signal Status_Trigger of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_STATUS_TRIGGER_MAX	(1)


/** Convert the binary value of signal GPS_Time of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT into the world value. */
#define CAP_PT_9240866_GPS_TIME_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9240866_GPS_TIME_FACTOR)

/** Convert the world value of signal GPS_Time of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9240866_GPS_TIME_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_9240866_GPS_TIME_FACTOR))

/** The gain factor of the scaling of signal GPS_Time of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_GPS_TIME_FACTOR	(0.001)

/** The offset of the scaling of signal GPS_Time of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_GPS_TIME_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Time of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_GPS_TIME_MIN	(0.0)

/** The maximum of the world value of signal GPS_Time of frame
    RT_SB_Output_Status (9240866, 0x8d0122) on bus PT. */
#define CAP_PT_9240866_GPS_TIME_MAX	(604800.0)

/** The minimum of the world value of signal Validity_GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_VALIDITY_GPS_HEADING_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_VALIDITY_GPS_HEADING_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_VALIDITY_GPS_GRADIENT_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_VALIDITY_GPS_GRADIENT_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_ACCURACY_GPS_HEADING_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_ACCURACY_GPS_HEADING_MAX	(255)


/** Convert the binary value of signal GPS_Heading_2 of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT into the world value. */
#define CAP_PT_9180706_GPS_HEADING_2_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9180706_GPS_HEADING_2_FACTOR)

/** Convert the world value of signal GPS_Heading_2 of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9180706_GPS_HEADING_2_DBL_TO_BIN(dbl) \
            ((uint16_t)((dbl)/CAP_PT_9180706_GPS_HEADING_2_FACTOR))

/** The gain factor of the scaling of signal GPS_Heading_2 of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_GPS_HEADING_2_FACTOR	(0.01)

/** The offset of the scaling of signal GPS_Heading_2 of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_GPS_HEADING_2_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Heading_2 of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_GPS_HEADING_2_MIN	(0.0)

/** The maximum of the world value of signal GPS_Heading_2 of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_GPS_HEADING_2_MAX	(360.0)

/** The minimum of the world value of signal Accuracy_GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_ACCURACY_GPS_GRADIENT_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_ACCURACY_GPS_GRADIENT_MAX	(255)


/** Convert the binary value of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT into the world value. */
#define CAP_PT_9180706_GPS_GRADIENT_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9180706_GPS_GRADIENT_FACTOR)

/** Convert the world value of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9180706_GPS_GRADIENT_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9180706_GPS_GRADIENT_FACTOR))

/** The gain factor of the scaling of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_GPS_GRADIENT_FACTOR	(0.01)

/** The offset of the scaling of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_GPS_GRADIENT_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_GPS_GRADIENT_MIN	(-90.0)

/** The maximum of the world value of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on bus PT. */
#define CAP_PT_9180706_GPS_GRADIENT_MAX	(90.0)

/** The minimum of the world value of signal Validity_Cumulative_Time of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_VALIDITY_CUMULATIVE_TIME_MIN	(0)

/** The maximum of the world value of signal Validity_Cumulative_Time of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_VALIDITY_CUMULATIVE_TIME_MAX	(1)

/** The minimum of the world value of signal Validity_Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_VALIDITY_CUMULATIVE_DISTANCE_MIN	(0)

/** The maximum of the world value of signal Validity_Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_VALIDITY_CUMULATIVE_DISTANCE_MAX	(1)


/** Convert the binary value of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT into the world value. */
#define CAP_PT_8397090_CUMULATIVE_TIME_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8397090_CUMULATIVE_TIME_FACTOR)

/** Convert the world value of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8397090_CUMULATIVE_TIME_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_8397090_CUMULATIVE_TIME_FACTOR))

/** The gain factor of the scaling of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_CUMULATIVE_TIME_FACTOR	(0.01)

/** The offset of the scaling of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_CUMULATIVE_TIME_OFFSET	(0.0)

/** The minimum of the world value of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_CUMULATIVE_TIME_MIN	(0.0)

/** The maximum of the world value of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_CUMULATIVE_TIME_MAX	(167772.0)


/** Convert the binary value of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT into the world value. */
#define CAP_PT_8397090_CUMULATIVE_DISTANCE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8397090_CUMULATIVE_DISTANCE_FACTOR)

/** Convert the world value of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8397090_CUMULATIVE_DISTANCE_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_8397090_CUMULATIVE_DISTANCE_FACTOR))

/** The gain factor of the scaling of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_CUMULATIVE_DISTANCE_FACTOR	(0.001)

/** The offset of the scaling of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_CUMULATIVE_DISTANCE_OFFSET	(0.0)

/** The minimum of the world value of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_CUMULATIVE_DISTANCE_MIN	(0.0)

/** The maximum of the world value of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on bus PT. */
#define CAP_PT_8397090_CUMULATIVE_DISTANCE_MAX	(4294970.0)

/** The minimum of the world value of signal Validity_Cumulative_Time of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_VALIDITY_CUMULATIVE_TIME_MIN	(0)

/** The maximum of the world value of signal Validity_Cumulative_Time of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_VALIDITY_CUMULATIVE_TIME_MAX	(1)

/** The minimum of the world value of signal Validity_Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_VALIDITY_CUMULATIVE_DISTANCE_MIN	(0)

/** The maximum of the world value of signal Validity_Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_VALIDITY_CUMULATIVE_DISTANCE_MAX	(1)


/** Convert the binary value of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT into the world value. */
#define CAP_PT_8396834_CUMULATIVE_TIME_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8396834_CUMULATIVE_TIME_FACTOR)

/** Convert the world value of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8396834_CUMULATIVE_TIME_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_8396834_CUMULATIVE_TIME_FACTOR))

/** The gain factor of the scaling of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_CUMULATIVE_TIME_FACTOR	(0.01)

/** The offset of the scaling of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_CUMULATIVE_TIME_OFFSET	(0.0)

/** The minimum of the world value of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_CUMULATIVE_TIME_MIN	(0.0)

/** The maximum of the world value of signal Cumulative_Time of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_CUMULATIVE_TIME_MAX	(167772.0)


/** Convert the binary value of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT into the world value. */
#define CAP_PT_8396834_CUMULATIVE_DISTANCE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8396834_CUMULATIVE_DISTANCE_FACTOR)

/** Convert the world value of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8396834_CUMULATIVE_DISTANCE_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_8396834_CUMULATIVE_DISTANCE_FACTOR))

/** The gain factor of the scaling of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_CUMULATIVE_DISTANCE_FACTOR	(0.001)

/** The offset of the scaling of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_CUMULATIVE_DISTANCE_OFFSET	(0.0)

/** The minimum of the world value of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_CUMULATIVE_DISTANCE_MIN	(0.0)

/** The maximum of the world value of signal Cumulative_Distance of frame
    RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on bus PT. */
#define CAP_PT_8396834_CUMULATIVE_DISTANCE_MAX	(4294970.0)

/** The minimum of the world value of signal Validity_Trigger_Timestamp of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_VALIDITY_TRIGGER_TIMESTAMP_MIN	(0)

/** The maximum of the world value of signal Validity_Trigger_Timestamp of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_VALIDITY_TRIGGER_TIMESTAMP_MAX	(1)

/** The minimum of the world value of signal Accuracy_Trigger_Timestamp of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_ACCURACY_TRIGGER_TIMESTAMP_MIN	(0)

/** The maximum of the world value of signal Accuracy_Trigger_Timestamp of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_ACCURACY_TRIGGER_TIMESTAMP_MAX	(255)


/** Convert the binary value of signal Trigger_Number of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT into the world value. */
#define CAP_PT_9240610_TRIGGER_NUMBER_BIN_TO_DBL(bin) \
            ((double)(bin)+CAP_PT_9240610_TRIGGER_NUMBER_OFFSET)

/** Convert the world value of signal Trigger_Number of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9240610_TRIGGER_NUMBER_DBL_TO_BIN(dbl) \
            ((uint8_t)((dbl)-CAP_PT_9240610_TRIGGER_NUMBER_OFFSET))

/** The gain factor of the scaling of signal Trigger_Number of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_TRIGGER_NUMBER_FACTOR	(1.0)

/** The offset of the scaling of signal Trigger_Number of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_TRIGGER_NUMBER_OFFSET	(1.0)

/** The minimum of the world value of signal Trigger_Number of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_TRIGGER_NUMBER_MIN	(0.0)

/** The maximum of the world value of signal Trigger_Number of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_TRIGGER_NUMBER_MAX	(128.0)

/** The minimum of the world value of signal Trigger_Timestamp_Type of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_TRIGGER_TIMESTAMP_TYPE_MIN	(0)

/** The maximum of the world value of signal Trigger_Timestamp_Type of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_TRIGGER_TIMESTAMP_TYPE_MAX	(1)


/** Convert the binary value of signal GPS_High_Resolution_Time of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT into the world value. */
#define CAP_PT_9240610_GPS_HIGH_RESOLUTION_TIME_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9240610_GPS_HIGH_RESOLUTION_TIME_FACTOR)

/** Convert the world value of signal GPS_High_Resolution_Time of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9240610_GPS_HIGH_RESOLUTION_TIME_DBL_TO_BIN(dbl) \
            ((uint64_t)((dbl)/CAP_PT_9240610_GPS_HIGH_RESOLUTION_TIME_FACTOR))

/** The gain factor of the scaling of signal GPS_High_Resolution_Time of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_GPS_HIGH_RESOLUTION_TIME_FACTOR	(1.0E-6)

/** The offset of the scaling of signal GPS_High_Resolution_Time of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_GPS_HIGH_RESOLUTION_TIME_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_High_Resolution_Time of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_GPS_HIGH_RESOLUTION_TIME_MIN	(0.0)

/** The maximum of the world value of signal GPS_High_Resolution_Time of frame
    RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on bus PT. */
#define CAP_PT_9240610_GPS_HIGH_RESOLUTION_TIME_MAX	(604800.0)

/** The minimum of the world value of signal Validity_Gyro_Rate_Yaw of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_VALIDITY_GYRO_RATE_YAW_MIN	(0)

/** The maximum of the world value of signal Validity_Gyro_Rate_Yaw of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_VALIDITY_GYRO_RATE_YAW_MAX	(1)

/** The minimum of the world value of signal Validity_Gyro_Rate_Pitch of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_VALIDITY_GYRO_RATE_PITCH_MIN	(0)

/** The maximum of the world value of signal Validity_Gyro_Rate_Pitch of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_VALIDITY_GYRO_RATE_PITCH_MAX	(1)

/** The minimum of the world value of signal Validity_Gyro_Rate_Roll of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_VALIDITY_GYRO_RATE_ROLL_MIN	(0)

/** The maximum of the world value of signal Validity_Gyro_Rate_Roll of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_VALIDITY_GYRO_RATE_ROLL_MAX	(1)

/** The minimum of the world value of signal Accuracy_Gyro_Rates of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_ACCURACY_GYRO_RATES_MIN	(0)

/** The maximum of the world value of signal Accuracy_Gyro_Rates of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_ACCURACY_GYRO_RATES_MAX	(0)


/** Convert the binary value of signal Gyro_Rate_Yaw of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT into the world value. */
#define CAP_PT_8388897_GYRO_RATE_YAW_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388897_GYRO_RATE_YAW_FACTOR)

/** Convert the world value of signal Gyro_Rate_Yaw of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388897_GYRO_RATE_YAW_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388897_GYRO_RATE_YAW_FACTOR))

/** The gain factor of the scaling of signal Gyro_Rate_Yaw of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_YAW_FACTOR	(0.01)

/** The offset of the scaling of signal Gyro_Rate_Yaw of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_YAW_OFFSET	(0.0)

/** The minimum of the world value of signal Gyro_Rate_Yaw of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_YAW_MIN	(-327.0)

/** The maximum of the world value of signal Gyro_Rate_Yaw of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_YAW_MAX	(327.0)


/** Convert the binary value of signal Gyro_Rate_Pitch of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT into the world value. */
#define CAP_PT_8388897_GYRO_RATE_PITCH_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388897_GYRO_RATE_PITCH_FACTOR)

/** Convert the world value of signal Gyro_Rate_Pitch of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388897_GYRO_RATE_PITCH_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388897_GYRO_RATE_PITCH_FACTOR))

/** The gain factor of the scaling of signal Gyro_Rate_Pitch of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_PITCH_FACTOR	(0.01)

/** The offset of the scaling of signal Gyro_Rate_Pitch of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_PITCH_OFFSET	(0.0)

/** The minimum of the world value of signal Gyro_Rate_Pitch of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_PITCH_MIN	(-327.0)

/** The maximum of the world value of signal Gyro_Rate_Pitch of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_PITCH_MAX	(327.0)


/** Convert the binary value of signal Gyro_Rate_Roll of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT into the world value. */
#define CAP_PT_8388897_GYRO_RATE_ROLL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388897_GYRO_RATE_ROLL_FACTOR)

/** Convert the world value of signal Gyro_Rate_Roll of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388897_GYRO_RATE_ROLL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388897_GYRO_RATE_ROLL_FACTOR))

/** The gain factor of the scaling of signal Gyro_Rate_Roll of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_ROLL_FACTOR	(0.01)

/** The offset of the scaling of signal Gyro_Rate_Roll of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_ROLL_OFFSET	(0.0)

/** The minimum of the world value of signal Gyro_Rate_Roll of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_ROLL_MIN	(-327.0)

/** The maximum of the world value of signal Gyro_Rate_Roll of frame
    RT_IMU06_Gyro_Rates (8388897, 0x800121) on bus PT. */
#define CAP_PT_8388897_GYRO_RATE_ROLL_MAX	(327.0)

/** The minimum of the world value of signal Validity_Accel_Longitudinal of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_VALIDITY_ACCEL_LONGITUDINAL_MIN	(0)

/** The maximum of the world value of signal Validity_Accel_Longitudinal of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_VALIDITY_ACCEL_LONGITUDINAL_MAX	(1)

/** The minimum of the world value of signal Validity_Accel_Lateral of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_VALIDITY_ACCEL_LATERAL_MIN	(0)

/** The maximum of the world value of signal Validity_Accel_Lateral of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_VALIDITY_ACCEL_LATERAL_MAX	(1)

/** The minimum of the world value of signal Validity_Accel_Vertical of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_VALIDITY_ACCEL_VERTICAL_MIN	(0)

/** The maximum of the world value of signal Validity_Accel_Vertical of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_VALIDITY_ACCEL_VERTICAL_MAX	(1)

/** The minimum of the world value of signal Accuracy_Accel of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCURACY_ACCEL_MIN	(0)

/** The maximum of the world value of signal Accuracy_Accel of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCURACY_ACCEL_MAX	(255)


/** Convert the binary value of signal Accel_Longitudinal of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT into the world value. */
#define CAP_PT_8388641_ACCEL_LONGITUDINAL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388641_ACCEL_LONGITUDINAL_FACTOR)

/** Convert the world value of signal Accel_Longitudinal of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388641_ACCEL_LONGITUDINAL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388641_ACCEL_LONGITUDINAL_FACTOR))

/** The gain factor of the scaling of signal Accel_Longitudinal of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_LONGITUDINAL_FACTOR	(0.001)

/** The offset of the scaling of signal Accel_Longitudinal of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_LONGITUDINAL_OFFSET	(0.0)

/** The minimum of the world value of signal Accel_Longitudinal of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_LONGITUDINAL_MIN	(-65.0)

/** The maximum of the world value of signal Accel_Longitudinal of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_LONGITUDINAL_MAX	(65.0)


/** Convert the binary value of signal Accel_Lateral of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT into the world value. */
#define CAP_PT_8388641_ACCEL_LATERAL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388641_ACCEL_LATERAL_FACTOR)

/** Convert the world value of signal Accel_Lateral of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388641_ACCEL_LATERAL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388641_ACCEL_LATERAL_FACTOR))

/** The gain factor of the scaling of signal Accel_Lateral of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_LATERAL_FACTOR	(0.001)

/** The offset of the scaling of signal Accel_Lateral of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_LATERAL_OFFSET	(0.0)

/** The minimum of the world value of signal Accel_Lateral of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_LATERAL_MIN	(-65.0)

/** The maximum of the world value of signal Accel_Lateral of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_LATERAL_MAX	(65.0)


/** Convert the binary value of signal Accel_Vertical of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT into the world value. */
#define CAP_PT_8388641_ACCEL_VERTICAL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388641_ACCEL_VERTICAL_FACTOR)

/** Convert the world value of signal Accel_Vertical of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388641_ACCEL_VERTICAL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388641_ACCEL_VERTICAL_FACTOR))

/** The gain factor of the scaling of signal Accel_Vertical of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_VERTICAL_FACTOR	(0.001)

/** The offset of the scaling of signal Accel_Vertical of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_VERTICAL_OFFSET	(0.0)

/** The minimum of the world value of signal Accel_Vertical of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_VERTICAL_MIN	(-65.0)

/** The maximum of the world value of signal Accel_Vertical of frame
    RT_IMU06_Accel (8388641, 0x800021) on bus PT. */
#define CAP_PT_8388641_ACCEL_VERTICAL_MAX	(65.0)

/** The minimum of the world value of signal Validity_Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. */
#define CAP_PT_8392738_VALIDITY_SPEED_MIN	(0)

/** The maximum of the world value of signal Validity_Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. */
#define CAP_PT_8392738_VALIDITY_SPEED_MAX	(1)

/** The minimum of the world value of signal Accuracy_Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. */
#define CAP_PT_8392738_ACCURACY_SPEED_MIN	(0)

/** The maximum of the world value of signal Accuracy_Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. */
#define CAP_PT_8392738_ACCURACY_SPEED_MAX	(255)


/** Convert the binary value of signal Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT into the world value. */
#define CAP_PT_8392738_SPEED_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8392738_SPEED_FACTOR)

/** Convert the world value of signal Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8392738_SPEED_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_8392738_SPEED_FACTOR))

/** The gain factor of the scaling of signal Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. */
#define CAP_PT_8392738_SPEED_FACTOR	(1.0E-5)

/** The offset of the scaling of signal Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. */
#define CAP_PT_8392738_SPEED_OFFSET	(0.0)

/** The minimum of the world value of signal Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. */
#define CAP_PT_8392738_SPEED_MIN	(-20000.0)

/** The maximum of the world value of signal Speed of frame
    RT_SB_Speed (8392738, 0x801022) on bus PT. */
#define CAP_PT_8392738_SPEED_MAX	(20000.0)

/** The minimum of the world value of signal Validity_RTK_Slip of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_VALIDITY_RTK_SLIP_MIN	(0)

/** The maximum of the world value of signal Validity_RTK_Slip of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_VALIDITY_RTK_SLIP_MAX	(1)

/** The minimum of the world value of signal Validity_RTK_Squat of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_VALIDITY_RTK_SQUAT_MIN	(0)

/** The maximum of the world value of signal Validity_RTK_Squat of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_VALIDITY_RTK_SQUAT_MAX	(1)

/** The minimum of the world value of signal Validity_RTK_Baseline of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_VALIDITY_RTK_BASELINE_MIN	(0)

/** The maximum of the world value of signal Validity_RTK_Baseline of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_VALIDITY_RTK_BASELINE_MAX	(1)

/** The minimum of the world value of signal Accuracy_RTK_Baseline of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_ACCURACY_RTK_BASELINE_MIN	(0)

/** The maximum of the world value of signal Accuracy_RTK_Baseline of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_ACCURACY_RTK_BASELINE_MAX	(255)


/** Convert the binary value of signal RTK_Slip of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT into the world value. */
#define CAP_PT_9183522_RTK_SLIP_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9183522_RTK_SLIP_FACTOR)

/** Convert the world value of signal RTK_Slip of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9183522_RTK_SLIP_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9183522_RTK_SLIP_FACTOR))

/** The gain factor of the scaling of signal RTK_Slip of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_SLIP_FACTOR	(0.01)

/** The offset of the scaling of signal RTK_Slip of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_SLIP_OFFSET	(0.0)

/** The minimum of the world value of signal RTK_Slip of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_SLIP_MIN	(-360.0)

/** The maximum of the world value of signal RTK_Slip of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_SLIP_MAX	(360.0)


/** Convert the binary value of signal RTK_Squat of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT into the world value. */
#define CAP_PT_9183522_RTK_SQUAT_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9183522_RTK_SQUAT_FACTOR)

/** Convert the world value of signal RTK_Squat of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9183522_RTK_SQUAT_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9183522_RTK_SQUAT_FACTOR))

/** The gain factor of the scaling of signal RTK_Squat of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_SQUAT_FACTOR	(0.01)

/** The offset of the scaling of signal RTK_Squat of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_SQUAT_OFFSET	(0.0)

/** The minimum of the world value of signal RTK_Squat of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_SQUAT_MIN	(-360.0)

/** The maximum of the world value of signal RTK_Squat of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_SQUAT_MAX	(360.0)

/** The minimum of the world value of signal RTK_Baseline of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_BASELINE_MIN	(0)

/** The maximum of the world value of signal RTK_Baseline of frame
    RT_SB_RTK_Slip (9183522, 0x8c2122) on bus PT. */
#define CAP_PT_9183522_RTK_BASELINE_MAX	(65535)

/** The minimum of the world value of signal Validity_RTK_Yaw of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_VALIDITY_RTK_YAW_MIN	(0)

/** The maximum of the world value of signal Validity_RTK_Yaw of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_VALIDITY_RTK_YAW_MAX	(1)

/** The minimum of the world value of signal Validity_RTK_Pitch of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_VALIDITY_RTK_PITCH_MIN	(0)

/** The maximum of the world value of signal Validity_RTK_Pitch of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_VALIDITY_RTK_PITCH_MAX	(1)

/** The minimum of the world value of signal Validity_RTK_Roll of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_VALIDITY_RTK_ROLL_MIN	(0)

/** The maximum of the world value of signal Validity_RTK_Roll of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_VALIDITY_RTK_ROLL_MAX	(1)

/** The minimum of the world value of signal Accuracy_RTK_Attitude of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_ACCURACY_RTK_ATTITUDE_MIN	(0)

/** The maximum of the world value of signal Accuracy_RTK_Attitude of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_ACCURACY_RTK_ATTITUDE_MAX	(255)


/** Convert the binary value of signal RTK_Attitude_Yaw of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT into the world value. */
#define CAP_PT_9183266_RTK_ATTITUDE_YAW_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9183266_RTK_ATTITUDE_YAW_FACTOR)

/** Convert the world value of signal RTK_Attitude_Yaw of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9183266_RTK_ATTITUDE_YAW_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9183266_RTK_ATTITUDE_YAW_FACTOR))

/** The gain factor of the scaling of signal RTK_Attitude_Yaw of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_YAW_FACTOR	(0.01)

/** The offset of the scaling of signal RTK_Attitude_Yaw of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_YAW_OFFSET	(0.0)

/** The minimum of the world value of signal RTK_Attitude_Yaw of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_YAW_MIN	(-360.0)

/** The maximum of the world value of signal RTK_Attitude_Yaw of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_YAW_MAX	(360.0)


/** Convert the binary value of signal RTK_Attitude_Pitch of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT into the world value. */
#define CAP_PT_9183266_RTK_ATTITUDE_PITCH_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9183266_RTK_ATTITUDE_PITCH_FACTOR)

/** Convert the world value of signal RTK_Attitude_Pitch of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9183266_RTK_ATTITUDE_PITCH_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9183266_RTK_ATTITUDE_PITCH_FACTOR))

/** The gain factor of the scaling of signal RTK_Attitude_Pitch of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_PITCH_FACTOR	(0.01)

/** The offset of the scaling of signal RTK_Attitude_Pitch of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_PITCH_OFFSET	(0.0)

/** The minimum of the world value of signal RTK_Attitude_Pitch of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_PITCH_MIN	(-90.0)

/** The maximum of the world value of signal RTK_Attitude_Pitch of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_PITCH_MAX	(90.0)


/** Convert the binary value of signal RTK_Attitude_Roll of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT into the world value. */
#define CAP_PT_9183266_RTK_ATTITUDE_ROLL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9183266_RTK_ATTITUDE_ROLL_FACTOR)

/** Convert the world value of signal RTK_Attitude_Roll of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9183266_RTK_ATTITUDE_ROLL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9183266_RTK_ATTITUDE_ROLL_FACTOR))

/** The gain factor of the scaling of signal RTK_Attitude_Roll of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_ROLL_FACTOR	(0.01)

/** The offset of the scaling of signal RTK_Attitude_Roll of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_ROLL_OFFSET	(0.0)

/** The minimum of the world value of signal RTK_Attitude_Roll of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_ROLL_MIN	(-90.0)

/** The maximum of the world value of signal RTK_Attitude_Roll of frame
    RT_SB_RTK_Attitude (9183266, 0x8c2022) on bus PT. */
#define CAP_PT_9183266_RTK_ATTITUDE_ROLL_MAX	(90.0)

/** The minimum of the world value of signal Validity_GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_VALIDITY_GPS_LATERAL_ACCEL_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_VALIDITY_GPS_LATERAL_ACCEL_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Mcycle_Lean of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_VALIDITY_GPS_MCYCLE_LEAN_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Mcycle_Lean of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_VALIDITY_GPS_MCYCLE_LEAN_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_ACCURACY_GPS_LATERAL_ACCEL_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_ACCURACY_GPS_LATERAL_ACCEL_MAX	(255)


/** Convert the binary value of signal GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT into the world value. */
#define CAP_PT_9187362_GPS_LATERAL_ACCEL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9187362_GPS_LATERAL_ACCEL_FACTOR)

/** Convert the world value of signal GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9187362_GPS_LATERAL_ACCEL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9187362_GPS_LATERAL_ACCEL_FACTOR))

/** The gain factor of the scaling of signal GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_GPS_LATERAL_ACCEL_FACTOR	(0.001)

/** The offset of the scaling of signal GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_GPS_LATERAL_ACCEL_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_GPS_LATERAL_ACCEL_MIN	(-65.0)

/** The maximum of the world value of signal GPS_Lateral_Accel of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_GPS_LATERAL_ACCEL_MAX	(65.0)


/** Convert the binary value of signal GPS_Mcycle_Lean_Angle of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT into the world value. */
#define CAP_PT_9187362_GPS_MCYCLE_LEAN_ANGLE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9187362_GPS_MCYCLE_LEAN_ANGLE_FACTOR)

/** Convert the world value of signal GPS_Mcycle_Lean_Angle of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9187362_GPS_MCYCLE_LEAN_ANGLE_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9187362_GPS_MCYCLE_LEAN_ANGLE_FACTOR))

/** The gain factor of the scaling of signal GPS_Mcycle_Lean_Angle of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_GPS_MCYCLE_LEAN_ANGLE_FACTOR	(0.01)

/** The offset of the scaling of signal GPS_Mcycle_Lean_Angle of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_GPS_MCYCLE_LEAN_ANGLE_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Mcycle_Lean_Angle of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_GPS_MCYCLE_LEAN_ANGLE_MIN	(-90.0)

/** The maximum of the world value of signal GPS_Mcycle_Lean_Angle of frame
    RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on bus PT. */
#define CAP_PT_9187362_GPS_MCYCLE_LEAN_ANGLE_MAX	(90.0)

/** The minimum of the world value of signal GPS_Status of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_GPS_STATUS_MIN	(0)

/** The maximum of the world value of signal GPS_Status of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_GPS_STATUS_MAX	(255)

/** The minimum of the world value of signal Firmware_Version_Major of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_FIRMWARE_VERSION_MAJOR_MIN	(0)

/** The maximum of the world value of signal Firmware_Version_Major of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_FIRMWARE_VERSION_MAJOR_MAX	(255)

/** The minimum of the world value of signal Firmware_Version_Intermediate of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_FIRMWARE_VERSION_INTERMEDIATE_MIN	(0)

/** The maximum of the world value of signal Firmware_Version_Intermediate of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_FIRMWARE_VERSION_INTERMEDIATE_MAX	(255)

/** The minimum of the world value of signal Firmware_Version_Minor of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_FIRMWARE_VERSION_MINOR_MIN	(0)

/** The maximum of the world value of signal Firmware_Version_Minor of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_FIRMWARE_VERSION_MINOR_MAX	(255)

/** The minimum of the world value of signal GPS_nSv of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_GPS_NSV_MIN	(0)

/** The maximum of the world value of signal GPS_nSv of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_GPS_NSV_MAX	(16)

/** The minimum of the world value of signal GPS_nSv_2 of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_GPS_NSV_2_MIN	(0)

/** The maximum of the world value of signal GPS_nSv_2 of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_GPS_NSV_2_MAX	(16)

/** The minimum of the world value of signal GPS_nSv_RTK of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_GPS_NSV_RTK_MIN	(0)

/** The maximum of the world value of signal GPS_nSv_RTK of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_GPS_NSV_RTK_MAX	(16)

/** The minimum of the world value of signal RTK_Status of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_RTK_STATUS_MIN	(0)

/** The maximum of the world value of signal RTK_Status of frame
    RT_SB_GPS_Status (9175074, 0x8c0022) on bus PT. */
#define CAP_PT_9175074_RTK_STATUS_MAX	(255)


/** Convert the binary value of signal GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT into the world value. */
#define CAP_PT_9176354_GPS_POS_ECEF_Y_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9176354_GPS_POS_ECEF_Y_FACTOR)

/** Convert the world value of signal GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9176354_GPS_POS_ECEF_Y_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9176354_GPS_POS_ECEF_Y_FACTOR))

/** The gain factor of the scaling of signal GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. */
#define CAP_PT_9176354_GPS_POS_ECEF_Y_FACTOR	(0.01)

/** The offset of the scaling of signal GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. */
#define CAP_PT_9176354_GPS_POS_ECEF_Y_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. */
#define CAP_PT_9176354_GPS_POS_ECEF_Y_MIN	(-1.0E7)

/** The maximum of the world value of signal GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. */
#define CAP_PT_9176354_GPS_POS_ECEF_Y_MAX	(1.0E7)


/** Convert the binary value of signal GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT into the world value. */
#define CAP_PT_9176354_GPS_POS_ECEF_Z_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9176354_GPS_POS_ECEF_Z_FACTOR)

/** Convert the world value of signal GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9176354_GPS_POS_ECEF_Z_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9176354_GPS_POS_ECEF_Z_FACTOR))

/** The gain factor of the scaling of signal GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. */
#define CAP_PT_9176354_GPS_POS_ECEF_Z_FACTOR	(0.01)

/** The offset of the scaling of signal GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. */
#define CAP_PT_9176354_GPS_POS_ECEF_Z_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. */
#define CAP_PT_9176354_GPS_POS_ECEF_Z_MIN	(-1.0E7)

/** The maximum of the world value of signal GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on bus PT. */
#define CAP_PT_9176354_GPS_POS_ECEF_Z_MAX	(1.0E7)

/** The minimum of the world value of signal Validity_GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_VALIDITY_GPS_POS_ECEF_X_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_VALIDITY_GPS_POS_ECEF_X_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_VALIDITY_GPS_POS_ECEF_Y_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_VALIDITY_GPS_POS_ECEF_Y_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_VALIDITY_GPS_POS_ECEF_Z_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_VALIDITY_GPS_POS_ECEF_Z_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_ACCURACY_GPS_POS_ECEF_X_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_ACCURACY_GPS_POS_ECEF_X_MAX	(255)

/** The minimum of the world value of signal Accuracy_GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_ACCURACY_GPS_POS_ECEF_Y_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Pos_ECEF_Y of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_ACCURACY_GPS_POS_ECEF_Y_MAX	(255)

/** The minimum of the world value of signal Accuracy_GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_ACCURACY_GPS_POS_ECEF_Z_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Pos_ECEF_Z of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_ACCURACY_GPS_POS_ECEF_Z_MAX	(255)


/** Convert the binary value of signal GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT into the world value. */
#define CAP_PT_9176098_GPS_POS_ECEF_X_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9176098_GPS_POS_ECEF_X_FACTOR)

/** Convert the world value of signal GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9176098_GPS_POS_ECEF_X_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9176098_GPS_POS_ECEF_X_FACTOR))

/** The gain factor of the scaling of signal GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_GPS_POS_ECEF_X_FACTOR	(0.01)

/** The offset of the scaling of signal GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_GPS_POS_ECEF_X_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_GPS_POS_ECEF_X_MIN	(-1.0E7)

/** The maximum of the world value of signal GPS_Pos_ECEF_X of frame
    RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on bus PT. */
#define CAP_PT_9176098_GPS_POS_ECEF_X_MAX	(1.0E7)


/** Convert the binary value of signal GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT into the world value. */
#define CAP_PT_9175842_GPS_POS_LLH_LONGITUDE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9175842_GPS_POS_LLH_LONGITUDE_FACTOR)

/** Convert the world value of signal GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9175842_GPS_POS_LLH_LONGITUDE_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9175842_GPS_POS_LLH_LONGITUDE_FACTOR))

/** The gain factor of the scaling of signal GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. */
#define CAP_PT_9175842_GPS_POS_LLH_LONGITUDE_FACTOR	(1.0E-7)

/** The offset of the scaling of signal GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. */
#define CAP_PT_9175842_GPS_POS_LLH_LONGITUDE_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. */
#define CAP_PT_9175842_GPS_POS_LLH_LONGITUDE_MIN	(-180.0)

/** The maximum of the world value of signal GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. */
#define CAP_PT_9175842_GPS_POS_LLH_LONGITUDE_MAX	(180.0)


/** Convert the binary value of signal GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT into the world value. */
#define CAP_PT_9175842_GPS_POS_LLH_ALTITUDE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9175842_GPS_POS_LLH_ALTITUDE_FACTOR)

/** Convert the world value of signal GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9175842_GPS_POS_LLH_ALTITUDE_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9175842_GPS_POS_LLH_ALTITUDE_FACTOR))

/** The gain factor of the scaling of signal GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. */
#define CAP_PT_9175842_GPS_POS_LLH_ALTITUDE_FACTOR	(0.001)

/** The offset of the scaling of signal GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. */
#define CAP_PT_9175842_GPS_POS_LLH_ALTITUDE_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. */
#define CAP_PT_9175842_GPS_POS_LLH_ALTITUDE_MIN	(-1000.0)

/** The maximum of the world value of signal GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on bus PT. */
#define CAP_PT_9175842_GPS_POS_LLH_ALTITUDE_MAX	(100000.0)

/** The minimum of the world value of signal Validity_GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_VALIDITY_GPS_POS_LLH_LATITUDE_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_VALIDITY_GPS_POS_LLH_LATITUDE_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_VALIDITY_GPS_POS_LLH_LONGITUDE_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_VALIDITY_GPS_POS_LLH_LONGITUDE_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_VALIDITY_GPS_POS_LLH_ALTITUDE_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_VALIDITY_GPS_POS_LLH_ALTITUDE_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_ACCURACY_GPS_POS_LLH_LATITUDE_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_ACCURACY_GPS_POS_LLH_LATITUDE_MAX	(255)

/** The minimum of the world value of signal Accuracy_GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_ACCURACY_GPS_POS_LLH_LONGITUDE_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Pos_LLH_Longitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_ACCURACY_GPS_POS_LLH_LONGITUDE_MAX	(255)

/** The minimum of the world value of signal Accuracy_GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_ACCURACY_GPS_POS_LLH_ALTITUDE_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Pos_LLH_Altitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_ACCURACY_GPS_POS_LLH_ALTITUDE_MAX	(255)


/** Convert the binary value of signal GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT into the world value. */
#define CAP_PT_9175586_GPS_POS_LLH_LATITUDE_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9175586_GPS_POS_LLH_LATITUDE_FACTOR)

/** Convert the world value of signal GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9175586_GPS_POS_LLH_LATITUDE_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9175586_GPS_POS_LLH_LATITUDE_FACTOR))

/** The gain factor of the scaling of signal GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_GPS_POS_LLH_LATITUDE_FACTOR	(1.0E-7)

/** The offset of the scaling of signal GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_GPS_POS_LLH_LATITUDE_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_GPS_POS_LLH_LATITUDE_MIN	(-90.0)

/** The maximum of the world value of signal GPS_Pos_LLH_Latitude of frame
    RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on bus PT. */
#define CAP_PT_9175586_GPS_POS_LLH_LATITUDE_MAX	(90.0)

/** The minimum of the world value of signal Validity_GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_VALIDITY_GPS_HEADING_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_VALIDITY_GPS_HEADING_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_VALIDITY_GPS_GRADIENT_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_VALIDITY_GPS_GRADIENT_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_ACCURACY_GPS_HEADING_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_ACCURACY_GPS_HEADING_MAX	(255)


/** Convert the binary value of signal GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT into the world value. */
#define CAP_PT_9180450_GPS_HEADING_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9180450_GPS_HEADING_FACTOR)

/** Convert the world value of signal GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9180450_GPS_HEADING_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9180450_GPS_HEADING_FACTOR))

/** The gain factor of the scaling of signal GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_GPS_HEADING_FACTOR	(0.01)

/** The offset of the scaling of signal GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_GPS_HEADING_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_GPS_HEADING_MIN	(-180.0)

/** The maximum of the world value of signal GPS_Heading of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_GPS_HEADING_MAX	(180.0)

/** The minimum of the world value of signal Accuracy_GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_ACCURACY_GPS_GRADIENT_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_ACCURACY_GPS_GRADIENT_MAX	(255)


/** Convert the binary value of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT into the world value. */
#define CAP_PT_9180450_GPS_GRADIENT_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9180450_GPS_GRADIENT_FACTOR)

/** Convert the world value of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9180450_GPS_GRADIENT_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_9180450_GPS_GRADIENT_FACTOR))

/** The gain factor of the scaling of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_GPS_GRADIENT_FACTOR	(0.01)

/** The offset of the scaling of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_GPS_GRADIENT_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_GPS_GRADIENT_MIN	(-90.0)

/** The maximum of the world value of signal GPS_Gradient of frame
    RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on bus PT. */
#define CAP_PT_9180450_GPS_GRADIENT_MAX	(90.0)

/** The minimum of the world value of signal Validity_GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_VALIDITY_GPS_VEL_ECEF_Y_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_VALIDITY_GPS_VEL_ECEF_Y_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_VALIDITY_GPS_VEL_ECEF_Z_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_VALIDITY_GPS_VEL_ECEF_Z_MAX	(1)


/** Convert the binary value of signal GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT into the world value. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Y_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9180194_GPS_VEL_ECEF_Y_FACTOR)

/** Convert the world value of signal GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Y_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9180194_GPS_VEL_ECEF_Y_FACTOR))

/** The gain factor of the scaling of signal GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Y_FACTOR	(1.0E-4)

/** The offset of the scaling of signal GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Y_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Y_MIN	(-838.0)

/** The maximum of the world value of signal GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Y_MAX	(838.0)


/** Convert the binary value of signal GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT into the world value. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Z_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9180194_GPS_VEL_ECEF_Z_FACTOR)

/** Convert the world value of signal GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Z_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9180194_GPS_VEL_ECEF_Z_FACTOR))

/** The gain factor of the scaling of signal GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Z_FACTOR	(1.0E-4)

/** The offset of the scaling of signal GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Z_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Z_MIN	(-838.0)

/** The maximum of the world value of signal GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on bus PT. */
#define CAP_PT_9180194_GPS_VEL_ECEF_Z_MAX	(838.0)

/** The minimum of the world value of signal Validity_GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_VALIDITY_GPS_VEL_ECEF_X_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_VALIDITY_GPS_VEL_ECEF_X_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_ACCURACY_GPS_VEL_ECEF_X_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_ACCURACY_GPS_VEL_ECEF_X_MAX	(255)

/** The minimum of the world value of signal Accuracy_GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_ACCURACY_GPS_VEL_ECEF_Y_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Vel_ECEF_Y of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_ACCURACY_GPS_VEL_ECEF_Y_MAX	(255)

/** The minimum of the world value of signal Accuracy_GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_ACCURACY_GPS_VEL_ECEF_Z_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Vel_ECEF_Z of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_ACCURACY_GPS_VEL_ECEF_Z_MAX	(255)


/** Convert the binary value of signal GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT into the world value. */
#define CAP_PT_9179938_GPS_VEL_ECEF_X_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_9179938_GPS_VEL_ECEF_X_FACTOR)

/** Convert the world value of signal GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_9179938_GPS_VEL_ECEF_X_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_9179938_GPS_VEL_ECEF_X_FACTOR))

/** The gain factor of the scaling of signal GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_GPS_VEL_ECEF_X_FACTOR	(1.0E-4)

/** The offset of the scaling of signal GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_GPS_VEL_ECEF_X_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_GPS_VEL_ECEF_X_MIN	(-838.0)

/** The maximum of the world value of signal GPS_Vel_ECEF_X of frame
    RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on bus PT. */
#define CAP_PT_9179938_GPS_VEL_ECEF_X_MAX	(838.0)

/** The minimum of the world value of signal Validity_GPS_Vel_NED_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. */
#define CAP_PT_0_VALIDITY_GPS_VEL_NED_D_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Vel_NED_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. */
#define CAP_PT_0_VALIDITY_GPS_VEL_NED_D_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Vel_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. */
#define CAP_PT_0_ACCURACY_GPS_VEL_D_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Vel_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. */
#define CAP_PT_0_ACCURACY_GPS_VEL_D_MAX	(255)


/** Convert the binary value of signal GPS_Vel_NED_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT into the world value. */
#define CAP_PT_0_GPS_VEL_NED_D_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_0_GPS_VEL_NED_D_FACTOR)

/** Convert the world value of signal GPS_Vel_NED_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_0_GPS_VEL_NED_D_DBL_TO_BIN(dbl) \
            ((int32_t)((dbl)/CAP_PT_0_GPS_VEL_NED_D_FACTOR))

/** The gain factor of the scaling of signal GPS_Vel_NED_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. */
#define CAP_PT_0_GPS_VEL_NED_D_FACTOR	(1.0E-4)

/** The offset of the scaling of signal GPS_Vel_NED_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. */
#define CAP_PT_0_GPS_VEL_NED_D_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Vel_NED_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. */
#define CAP_PT_0_GPS_VEL_NED_D_MIN	(-838.0)

/** The maximum of the world value of signal GPS_Vel_NED_D of frame
    RT_SB_GPS_Vel_NED_2 (0, 0x000) on bus PT. */
#define CAP_PT_0_GPS_VEL_NED_D_MAX	(838.0)

/** The minimum of the world value of signal Validity_GPS_Speed_2D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_VALIDITY_GPS_SPEED_2D_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Speed_2D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_VALIDITY_GPS_SPEED_2D_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Speed_3D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_VALIDITY_GPS_SPEED_3D_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Speed_3D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_VALIDITY_GPS_SPEED_3D_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Speed of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_ACCURACY_GPS_SPEED_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Speed of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_ACCURACY_GPS_SPEED_MAX	(255)


/** Convert the binary value of signal GPS_Speed_2D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT into the world value. */
#define CAP_PT_1818_GPS_SPEED_2D_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1818_GPS_SPEED_2D_FACTOR)

/** Convert the world value of signal GPS_Speed_2D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1818_GPS_SPEED_2D_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_1818_GPS_SPEED_2D_FACTOR))

/** The gain factor of the scaling of signal GPS_Speed_2D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_GPS_SPEED_2D_FACTOR	(1.0E-4)

/** The offset of the scaling of signal GPS_Speed_2D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_GPS_SPEED_2D_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Speed_2D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_GPS_SPEED_2D_MIN	(0.0)

/** The maximum of the world value of signal GPS_Speed_2D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_GPS_SPEED_2D_MAX	(1675.0)


/** Convert the binary value of signal GPS_Speed_3D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT into the world value. */
#define CAP_PT_1818_GPS_SPEED_3D_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_1818_GPS_SPEED_3D_FACTOR)

/** Convert the world value of signal GPS_Speed_3D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_1818_GPS_SPEED_3D_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_1818_GPS_SPEED_3D_FACTOR))

/** The gain factor of the scaling of signal GPS_Speed_3D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_GPS_SPEED_3D_FACTOR	(1.0E-4)

/** The offset of the scaling of signal GPS_Speed_3D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_GPS_SPEED_3D_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Speed_3D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_GPS_SPEED_3D_MIN	(0.0)

/** The maximum of the world value of signal GPS_Speed_3D of frame
    RT_SB_GPS_Speed (1818, 0x71a) on bus PT. */
#define CAP_PT_1818_GPS_SPEED_3D_MAX	(1675.0)

/** The minimum of the world value of signal Validity_GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_VALIDITY_GPS_TIME_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_VALIDITY_GPS_TIME_MAX	(1)

/** The minimum of the world value of signal Validity_GPS_Week of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_VALIDITY_GPS_WEEK_MIN	(0)

/** The maximum of the world value of signal Validity_GPS_Week of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_VALIDITY_GPS_WEEK_MAX	(1)

/** The minimum of the world value of signal Accuracy_GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_ACCURACY_GPS_TIME_MIN	(0)

/** The maximum of the world value of signal Accuracy_GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_ACCURACY_GPS_TIME_MAX	(255)


/** Convert the binary value of signal GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT into the world value. */
#define CAP_PT_2047_GPS_TIME_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_2047_GPS_TIME_FACTOR)

/** Convert the world value of signal GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_2047_GPS_TIME_DBL_TO_BIN(dbl) \
            ((uint32_t)((dbl)/CAP_PT_2047_GPS_TIME_FACTOR))

/** The gain factor of the scaling of signal GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_GPS_TIME_FACTOR	(0.001)

/** The offset of the scaling of signal GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_GPS_TIME_OFFSET	(0.0)

/** The minimum of the world value of signal GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_GPS_TIME_MIN	(0.0)

/** The maximum of the world value of signal GPS_Time of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_GPS_TIME_MAX	(604800.0)

/** The minimum of the world value of signal GPS_Week of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_GPS_WEEK_MIN	(0)

/** The maximum of the world value of signal GPS_Week of frame
    RT_SB_GPS_Time (2047, 0x7ff) on bus PT. */
#define CAP_PT_2047_GPS_WEEK_MAX	(65535)

/** The minimum of the world value of signal Validity_Accel_Longitudinal of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_VALIDITY_ACCEL_LONGITUDINAL_MIN	(0)

/** The maximum of the world value of signal Validity_Accel_Longitudinal of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_VALIDITY_ACCEL_LONGITUDINAL_MAX	(1)

/** The minimum of the world value of signal Validity_Accel_Lateral of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_VALIDITY_ACCEL_LATERAL_MIN	(0)

/** The maximum of the world value of signal Validity_Accel_Lateral of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_VALIDITY_ACCEL_LATERAL_MAX	(1)

/** The minimum of the world value of signal Validity_Accel_Vertical of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_VALIDITY_ACCEL_VERTICAL_MIN	(0)

/** The maximum of the world value of signal Validity_Accel_Vertical of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_VALIDITY_ACCEL_VERTICAL_MAX	(1)

/** The minimum of the world value of signal Accuracy_Accel of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCURACY_ACCEL_MIN	(0)

/** The maximum of the world value of signal Accuracy_Accel of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCURACY_ACCEL_MAX	(255)


/** Convert the binary value of signal Accel_Longitudinal of frame
    RT_SB_Accel (290, 0x122) on bus PT into the world value. */
#define CAP_PT_290_ACCEL_LONGITUDINAL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_290_ACCEL_LONGITUDINAL_FACTOR)

/** Convert the world value of signal Accel_Longitudinal of frame
    RT_SB_Accel (290, 0x122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_290_ACCEL_LONGITUDINAL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_290_ACCEL_LONGITUDINAL_FACTOR))

/** The gain factor of the scaling of signal Accel_Longitudinal of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_LONGITUDINAL_FACTOR	(0.001)

/** The offset of the scaling of signal Accel_Longitudinal of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_LONGITUDINAL_OFFSET	(0.0)

/** The minimum of the world value of signal Accel_Longitudinal of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_LONGITUDINAL_MIN	(-65.0)

/** The maximum of the world value of signal Accel_Longitudinal of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_LONGITUDINAL_MAX	(65.0)


/** Convert the binary value of signal Accel_Lateral of frame
    RT_SB_Accel (290, 0x122) on bus PT into the world value. */
#define CAP_PT_290_ACCEL_LATERAL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_290_ACCEL_LATERAL_FACTOR)

/** Convert the world value of signal Accel_Lateral of frame
    RT_SB_Accel (290, 0x122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_290_ACCEL_LATERAL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_290_ACCEL_LATERAL_FACTOR))

/** The gain factor of the scaling of signal Accel_Lateral of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_LATERAL_FACTOR	(0.001)

/** The offset of the scaling of signal Accel_Lateral of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_LATERAL_OFFSET	(0.0)

/** The minimum of the world value of signal Accel_Lateral of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_LATERAL_MIN	(-65.0)

/** The maximum of the world value of signal Accel_Lateral of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_LATERAL_MAX	(65.0)


/** Convert the binary value of signal Accel_Vertical of frame
    RT_SB_Accel (290, 0x122) on bus PT into the world value. */
#define CAP_PT_290_ACCEL_VERTICAL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_290_ACCEL_VERTICAL_FACTOR)

/** Convert the world value of signal Accel_Vertical of frame
    RT_SB_Accel (290, 0x122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_290_ACCEL_VERTICAL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_290_ACCEL_VERTICAL_FACTOR))

/** The gain factor of the scaling of signal Accel_Vertical of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_VERTICAL_FACTOR	(0.001)

/** The offset of the scaling of signal Accel_Vertical of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_VERTICAL_OFFSET	(0.0)

/** The minimum of the world value of signal Accel_Vertical of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_VERTICAL_MIN	(-65.0)

/** The maximum of the world value of signal Accel_Vertical of frame
    RT_SB_Accel (290, 0x122) on bus PT. */
#define CAP_PT_290_ACCEL_VERTICAL_MAX	(65.0)

/** The minimum of the world value of signal Validity_Gyro_Rate_Yaw of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_VALIDITY_GYRO_RATE_YAW_MIN	(0)

/** The maximum of the world value of signal Validity_Gyro_Rate_Yaw of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_VALIDITY_GYRO_RATE_YAW_MAX	(1)

/** The minimum of the world value of signal Validity_Gyro_Rate_Pitch of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_VALIDITY_GYRO_RATE_PITCH_MIN	(0)

/** The maximum of the world value of signal Validity_Gyro_Rate_Pitch of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_VALIDITY_GYRO_RATE_PITCH_MAX	(1)

/** The minimum of the world value of signal Validity_Gyro_Rate_Roll of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_VALIDITY_GYRO_RATE_ROLL_MIN	(0)

/** The maximum of the world value of signal Validity_Gyro_Rate_Roll of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_VALIDITY_GYRO_RATE_ROLL_MAX	(1)

/** The minimum of the world value of signal Accuracy_Gyro_Rates of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_ACCURACY_GYRO_RATES_MIN	(0)

/** The maximum of the world value of signal Accuracy_Gyro_Rates of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_ACCURACY_GYRO_RATES_MAX	(0)


/** Convert the binary value of signal Gyro_Rate_Yaw of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT into the world value. */
#define CAP_PT_8388898_GYRO_RATE_YAW_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388898_GYRO_RATE_YAW_FACTOR)

/** Convert the world value of signal Gyro_Rate_Yaw of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388898_GYRO_RATE_YAW_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388898_GYRO_RATE_YAW_FACTOR))

/** The gain factor of the scaling of signal Gyro_Rate_Yaw of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_YAW_FACTOR	(0.01)

/** The offset of the scaling of signal Gyro_Rate_Yaw of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_YAW_OFFSET	(0.0)

/** The minimum of the world value of signal Gyro_Rate_Yaw of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_YAW_MIN	(-327.0)

/** The maximum of the world value of signal Gyro_Rate_Yaw of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_YAW_MAX	(327.0)


/** Convert the binary value of signal Gyro_Rate_Pitch of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT into the world value. */
#define CAP_PT_8388898_GYRO_RATE_PITCH_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388898_GYRO_RATE_PITCH_FACTOR)

/** Convert the world value of signal Gyro_Rate_Pitch of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388898_GYRO_RATE_PITCH_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388898_GYRO_RATE_PITCH_FACTOR))

/** The gain factor of the scaling of signal Gyro_Rate_Pitch of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_PITCH_FACTOR	(0.01)

/** The offset of the scaling of signal Gyro_Rate_Pitch of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_PITCH_OFFSET	(0.0)

/** The minimum of the world value of signal Gyro_Rate_Pitch of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_PITCH_MIN	(-327.0)

/** The maximum of the world value of signal Gyro_Rate_Pitch of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_PITCH_MAX	(327.0)


/** Convert the binary value of signal Gyro_Rate_Roll of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT into the world value. */
#define CAP_PT_8388898_GYRO_RATE_ROLL_BIN_TO_DBL(bin) \
            ((double)(bin)*CAP_PT_8388898_GYRO_RATE_ROLL_FACTOR)

/** Convert the world value of signal Gyro_Rate_Roll of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT into the binary value as
    transmitted via the CAN interface. */
#define CAP_PT_8388898_GYRO_RATE_ROLL_DBL_TO_BIN(dbl) \
            ((int16_t)((dbl)/CAP_PT_8388898_GYRO_RATE_ROLL_FACTOR))

/** The gain factor of the scaling of signal Gyro_Rate_Roll of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_ROLL_FACTOR	(0.01)

/** The offset of the scaling of signal Gyro_Rate_Roll of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_ROLL_OFFSET	(0.0)

/** The minimum of the world value of signal Gyro_Rate_Roll of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_ROLL_MIN	(-327.0)

/** The maximum of the world value of signal Gyro_Rate_Roll of frame
    RT_SB_Gyro_Rates (8388898, 0x800122) on bus PT. */
#define CAP_PT_8388898_GYRO_RATE_ROLL_MAX	(327.0)




/*
 * Type definitions
 */

/** The enumeration of supported message send patterns. */
typedef enum cap_enumSendMode_t
    { cap_enumSendMode_regular = 0, cap_enumSendMode_event = 1, cap_enumSendMode_mixed = 2
    } cap_enumSendMode_t;

/** The different status bits of the CAN transmission status word. */
typedef enum cap_enumStsTransmission_t
{
    /** No bit is set, no error or problem or else is reported. */
    cap_stsTransm_okay = 0,

    /** The frame has never been received since startup of the interface. Only for inbound
        frames. */
    cap_stsTransm_neverReceived = 1,

    /** The frame could not be sent, send buffer full. Only for outbound frames. */
    cap_stsTransm_errSendBufferFull = 1,

    /** The frame has not been received timely. */
    cap_stsTransm_errTimeout = 2,

    /** The received frame has a data error; the checksum doesn't match. No signals will be
        extracted. */ 
    cap_stsTransm_errChecksum = 4,

    /** The sequence counter of the received frame indicates a lost frame. */
    cap_stsTransm_errSequence = 8,

    /** The received frame doesn't have the expected size. No signals can be extracted. */
    cap_stsTransm_errDLC = 16

} cap_enumStsTransmission_t;


/** The type of the transmission status. The encoding of the information is done bit-wise,
    see enumeration \a cap_enumStsTransmission_t. The status variable is neither defined as an
    enumeration nor as a bit field in order to permit the use of binary operations to
    filter and combine status bits. Furthermore, having a defined word width means safer
    interfacing with the Embedded Coder. */
typedef uint8_t cap_stsTransmission_t;

/** This struct bundles the transmission related information for a single frame. */
typedef struct cap_infoTransmission_t
{
    /** The transmission status. */
    cap_stsTransmission_t stsTransmission;

    /** The number of receive or sent events of the frame. The APSW, who is regularly
        checking the global CAN API, can look at changes of this variable to find out if
        there were newly received frames or whether the outbound frame became due
        meanwhile. Since the CAN API is race-condition free it may even reset the value to
        zero after each check - and and will then always have a simple and straight forward
        indication of the frames received and sent meanwhile.
          @remark The counter cycles around if it is not regularly reset by the APSW, no
        boundaries are implemented. */
    unsigned int noTransmittedFrames;

    /** For outbound frames and by setting this flag to \a true, the APSW can signal that
        the frame contents have been updated and that the frame requires sending. The APSW
        should never reset the flag, the frame sending logic will do as soon as it submits
        the frame at the operating system for sending.\n
          For regular, outbound frames it is useless to set the flag. These frames are
        anyway due at each check cycle.\n
          For outbound frames with timing pattern "mixed", it is not required or useful to
        regularly set this flag when there's no real data change event; the sending logic
        implements the regular sending if no APSW send command happens.\n
          For inbound frames this flag is a bit redundant with \a
        noTransmittedFrames; it is set on reception by the interface engine but not
        reset. If the APSW resets it after check it behaves like a Boolean statement
        whether new information arrived. */
    boolean_t isEvent;

} cap_infoTransmission_t;



/** The signals of inbound CAN frame RT_SB_INS_Vel_Body_Axes (215, 0x0d7) on
    bus PT. */
typedef struct cap_PT_RT_SB_INS_Vel_Body_Axes_215_t
{
    /** Signal Validity_INS_Vel_Forwards. */
    boolean_t Validity_INS_Vel_Forwards;

    /** Signal Validity_INS_Vel_Sideways. */
    boolean_t Validity_INS_Vel_Sideways;

    /** Signal Bit4. */
    boolean_t Bit4;

    /** Signal Bit7. */
    boolean_t Bit7;

    /** Signal Byte2_Bit0. */
    boolean_t Byte2_Bit0;

    /** Signal INS_Vel_Sideways_2D. */
    int32_t INS_Vel_Sideways_2D;

    /** Signal Byte4_Bits67 (mux selector). */
    uint8_t Byte4_Bits67;

    /** Signal Accuracy_INS_Vel_Body_org (muxed). */
    uint8_t Accuracy_INS_Vel_Body_org_m1;

    /** Signal INS_Vel_Forwards_2D_org (muxed). */
    int32_t INS_Vel_Forwards_2D_org_m1;

    /** Signal Accuracy_INS_Vel_Body_no2 (muxed). */
    uint8_t Accuracy_INS_Vel_Body_no2_m2;

    /** Signal INS_Vel_Forwards_2D_no2 (muxed). */
    int32_t INS_Vel_Forwards_2D_no2_m2;

    /** Signal Accuracy_INS_Vel_Body_no3 (muxed). */
    uint16_t Accuracy_INS_Vel_Body_no3_m3;

    /** Signal INS_Vel_Forwards_2D_no3 (muxed). */
    int16_t INS_Vel_Forwards_2D_no3_m3;

} cap_PT_RT_SB_INS_Vel_Body_Axes_215_t;


/** The signals of inbound CAN frame RT_DL1MK3_Speed (8392740, 0x801024) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Speed_8392740_t
{
    /** Signal Validity_Speed. */
    boolean_t Validity_Speed;

    /** Signal Accuracy_Speed. */
    uint8_t Accuracy_Speed;

    /** Signal Direction. */
    uint8_t Direction;

    /** Signal Speed. */
    int32_t Speed;

} cap_PT_RT_DL1MK3_Speed_8392740_t;


/** The signals of inbound CAN frame RT_DL1MK3_GPS_Time (9175332, 0x8c0124) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_GPS_Time_9175332_t
{
    /** Signal Validity_GPS_Time. */
    boolean_t Validity_GPS_Time;

    /** Signal Validity_GPS_Week. */
    boolean_t Validity_GPS_Week;

    /** Signal Accuracy_GPS_Time. */
    uint8_t Accuracy_GPS_Time;

    /** Signal GPS_Time. */
    uint32_t GPS_Time;

    /** Signal GPS_Week. */
    uint16_t GPS_Week;

} cap_PT_RT_DL1MK3_GPS_Time_9175332_t;


/** The signals of inbound CAN frame RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_t
{
    /** Signal GPS_Pos_LLH_Longitude. */
    int32_t GPS_Pos_LLH_Longitude;

    /** Signal GPS_Pos_LLH_Altitude. */
    int32_t GPS_Pos_LLH_Altitude;

} cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_t;


/** The signals of inbound CAN frame RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_t
{
    /** Signal Validity_GPS_Pos_LLH_Latitude. */
    boolean_t Validity_GPS_Pos_LLH_Latitude;

    /** Signal Validity_GPS_Pos_LLH_Longitude. */
    boolean_t Validity_GPS_Pos_LLH_Longitude;

    /** Signal Validity_GPS_Pos_LLH_Altitude. */
    boolean_t Validity_GPS_Pos_LLH_Altitude;

    /** Signal Accuracy_GPS_Pos_LLH_Latitude. */
    uint8_t Accuracy_GPS_Pos_LLH_Latitude;

    /** Signal Accuracy_GPS_Pos_LLH_Longitude. */
    uint8_t Accuracy_GPS_Pos_LLH_Longitude;

    /** Signal Accuracy_GPS_Pos_LLH_Altitude. */
    uint8_t Accuracy_GPS_Pos_LLH_Altitude;

    /** Signal GPS_Pos_LLH_Latitude. */
    int32_t GPS_Pos_LLH_Latitude;

} cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_t;


/** The signals of inbound CAN frame RT_DL1MK3_GPS_Speed (1234, 0x4d2) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_GPS_Speed_1234_t
{
    /** Signal Validity_GPS_Speed_2D. */
    boolean_t Validity_GPS_Speed_2D;

    /** Signal Validity_GPS_Speed_3D. */
    boolean_t Validity_GPS_Speed_3D;

    /** Signal Accuracy_GPS_Speed. */
    uint8_t Accuracy_GPS_Speed;

    /** Signal GPS_Speed_2D. */
    uint32_t GPS_Speed_2D;

    /** Signal GPS_Speed_3D. */
    uint32_t GPS_Speed_3D;

} cap_PT_RT_DL1MK3_GPS_Speed_1234_t;


/** The signals of outbound CAN frame RT_IRTemp_Temp_RL_2 (9963045, 0x980625) on
    bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_RL_2_9963045_t
{
    /** Signal IR_Temperature_21. */
    int16_t IR_Temperature_21;

    /** Signal IR_Temperature_22. */
    int16_t IR_Temperature_22;

    /** Signal IR_Temperature_23. */
    int16_t IR_Temperature_23;

    /** Signal IR_Temperature_24. */
    int16_t IR_Temperature_24;

} cap_PT_RT_IRTemp_Temp_RL_2_9963045_t;


/** The signals of outbound CAN frame RT_IRTemp_Temp_FR_2 (9962533, 0x980425) on
    bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_FR_2_9962533_t
{
    /** Signal IR_Temperature_13. */
    int16_t IR_Temperature_13;

    /** Signal IR_Temperature_14. */
    int16_t IR_Temperature_14;

    /** Signal IR_Temperature_15. */
    int16_t IR_Temperature_15;

    /** Signal IR_Temperature_16. */
    int16_t IR_Temperature_16;

} cap_PT_RT_IRTemp_Temp_FR_2_9962533_t;


/** The signals of inbound CAN frame RT_IRTemp_Temp_FL_2 (9962021, 0x980225) on
    bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_FL_2_9962021_t
{
    /** Signal IR_Temperature_5. */
    int16_t IR_Temperature_5;

    /** Signal IR_Temperature_6. */
    int16_t IR_Temperature_6;

    /** Signal IR_Temperature_7. */
    int16_t IR_Temperature_7;

    /** Signal IR_Temperature_8. */
    int16_t IR_Temperature_8;

} cap_PT_RT_IRTemp_Temp_FL_2_9962021_t;


/** The signals of inbound CAN frame RT_IRTemp_Temp_RL_1 (9962789, 0x980525) on
    bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_RL_1_9962789_t
{
    /** Signal IR_Temperature_17. */
    int16_t IR_Temperature_17;

    /** Signal IR_Temperature_18. */
    int16_t IR_Temperature_18;

    /** Signal IR_Temperature_19. */
    int16_t IR_Temperature_19;

    /** Signal IR_Temperature_20. */
    int16_t IR_Temperature_20;

} cap_PT_RT_IRTemp_Temp_RL_1_9962789_t;


/** The signals of inbound CAN frame RT_IRTemp_Temp_FR_1 (9962277, 0x980325) on
    bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_FR_1_9962277_t
{
    /** Signal IR_Temperature_9. */
    int16_t IR_Temperature_9;

    /** Signal IR_Temperature_10. */
    int16_t IR_Temperature_10;

    /** Signal IR_Temperature_11. */
    int16_t IR_Temperature_11;

    /** Signal IR_Temperature_12. */
    int16_t IR_Temperature_12;

} cap_PT_RT_IRTemp_Temp_FR_1_9962277_t;


/** The signals of inbound CAN frame RT_IRTemp_Temp_FL_1 (9961765, 0x980125) on
    bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_FL_1_9961765_t
{
    /** Signal IR_Temperature_1. */
    int16_t IR_Temperature_1;

    /** Signal IR_Temperature_2. */
    int16_t IR_Temperature_2;

    /** Signal IR_Temperature_3. */
    int16_t IR_Temperature_3;

    /** Signal IR_Temperature_4. */
    int16_t IR_Temperature_4;

} cap_PT_RT_IRTemp_Temp_FL_1_9961765_t;


/** The signals of outbound CAN frame RT_IRTemp_Temp_30 (9510437, 0x911e25) on
    bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_30_9510437_t
{
    /** Signal IR_Temperature_30. */
    int16_t IR_Temperature_30;

} cap_PT_RT_IRTemp_Temp_30_9510437_t;


/** The signals of outbound CAN frame RT_IRTemp_Temp_26 (9509413, 0x911a25) on
    bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_26_9509413_t
{
    /** Signal IR_Temperature_26. */
    int16_t IR_Temperature_26;

} cap_PT_RT_IRTemp_Temp_26_9509413_t;


/** The signals of inbound CAN frame RT_IRTemp_Temp_1 (9503013, 0x910125) on
    bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_1_9503013_t
{
    /** Signal IR_Temperature_1. */
    int16_t IR_Temperature_1;

    /** Signal CRC. */
    uint8_t CRC; /* Signal is not used by node ECU. */

} cap_PT_RT_IRTemp_Temp_1_9503013_t;


/** The signals of inbound CAN frame RT_SB_Trig_Final_Condition (9242402, 0x8d0722) on
    bus PT. */
typedef struct cap_PT_RT_SB_Trig_Final_Condition_9242402_t
{
    /** Signal Validity_Final_Speed. */
    boolean_t Validity_Final_Speed;

    /** Signal Final_Speed. */
    uint32_t Final_Speed;

} cap_PT_RT_SB_Trig_Final_Condition_9242402_t;


/** The signals of inbound CAN frame RT_SB_Trig_Initial_Condition (794, 0x31a) on
    bus PT. */
typedef struct cap_PT_RT_SB_Trig_Initial_Condition_794_t
{
    /** Signal Validity_Initial_Speed. */
    boolean_t Validity_Initial_Speed;

    /** Signal Validity_Initial_Heading. */
    boolean_t Validity_Initial_Heading;

    /** Signal Initial_Speed. */
    uint32_t Initial_Speed;

    /** Signal Initial_Heading. */
    int16_t Initial_Heading;

    /** Signal MFDD_Start_Threshold. */
    uint8_t MFDD_Start_Threshold;

    /** Signal MFDD_End_Threshold. */
    uint8_t MFDD_End_Threshold;

} cap_PT_RT_SB_Trig_Initial_Condition_794_t;


/** The signals of inbound CAN frame RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) on
    bus PT. */
typedef struct cap_PT_RT_SB_Trig_Direct_Dist_9241890_t
{
    /** Signal Direct_Distance. */
    uint32_t Direct_Distance;

    /** Signal Path_Distance_2D. */
    uint32_t Path_Distance_2D;

} cap_PT_RT_SB_Trig_Direct_Dist_9241890_t;


/** The signals of outbound CAN frame RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) on
    bus PT. */
typedef struct cap_PT_RT_SB_Trig_Forward_Dist_9241634_t
{
    /** Signal Forward_Distance. */
    int32_t Forward_Distance;

    /** Signal Deviation_Distance. */
    int32_t Deviation_Distance;

} cap_PT_RT_SB_Trig_Forward_Dist_9241634_t;


/** The signals of inbound CAN frame RT_SB_Trig_Path_Dist (9241378, 0x8d0322) on
    bus PT. */
typedef struct cap_PT_RT_SB_Trig_Path_Dist_9241378_t
{
    /** Signal Path_Distance_3D. */
    uint32_t Path_Distance_3D;

} cap_PT_RT_SB_Trig_Path_Dist_9241378_t;


/** The signals of outbound CAN frame RT_SB_Trig_Accel (9241122, 0x8d0222) on
    bus PT. */
typedef struct cap_PT_RT_SB_Trig_Accel_9241122_t
{
    /** Signal Validity_MFDD. */
    boolean_t Validity_MFDD;

    /** Signal Validity_Average_Accel. */
    boolean_t Validity_Average_Accel;

    /** Signal Validity_Triggered_Time. */
    boolean_t Validity_Triggered_Time;

    /** Signal MFDD. */
    int16_t MFDD;

    /** Signal Average_Accel. */
    int16_t Average_Accel;

    /** Signal Triggered_Time. */
    uint32_t Triggered_Time;

} cap_PT_RT_SB_Trig_Accel_9241122_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_11_9833252_t
{
    /** Signal Measured_Time_11. */
    uint32_t Measured_Time_11;

} cap_PT_RT_DL1MK3_Measure_Time_11_9833252_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_10_9832996_t
{
    /** Signal Measured_Time_10. */
    uint32_t Measured_Time_10;

} cap_PT_RT_DL1MK3_Measure_Time_10_9832996_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_9_9832740_t
{
    /** Signal Measured_Time_9. */
    uint32_t Measured_Time_9;

} cap_PT_RT_DL1MK3_Measure_Time_9_9832740_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_8_9832484_t
{
    /** Signal Measured_Time_8. */
    uint32_t Measured_Time_8;

} cap_PT_RT_DL1MK3_Measure_Time_8_9832484_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_7_9832228_t
{
    /** Signal Measured_Time_7. */
    uint32_t Measured_Time_7;

} cap_PT_RT_DL1MK3_Measure_Time_7_9832228_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_6_9831972_t
{
    /** Signal Measured_Time_6. */
    uint32_t Measured_Time_6;

} cap_PT_RT_DL1MK3_Measure_Time_6_9831972_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_5_9831716_t
{
    /** Signal Measured_Time_5. */
    uint32_t Measured_Time_5;

} cap_PT_RT_DL1MK3_Measure_Time_5_9831716_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_4_9831460_t
{
    /** Signal Measured_Time_4. */
    uint32_t Measured_Time_4;

} cap_PT_RT_DL1MK3_Measure_Time_4_9831460_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_3_9831204_t
{
    /** Signal Measured_Time_3. */
    uint32_t Measured_Time_3;

} cap_PT_RT_DL1MK3_Measure_Time_3_9831204_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_2_9830948_t
{
    /** Signal Measured_Time_2. */
    uint32_t Measured_Time_2;

} cap_PT_RT_DL1MK3_Measure_Time_2_9830948_t;


/** The signals of inbound CAN frame RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_1_9830692_t
{
    /** Signal Measured_Time_1. */
    uint32_t Measured_Time_1;

} cap_PT_RT_DL1MK3_Measure_Time_1_9830692_t;


/** The signals of inbound CAN frame RT_DL1MK3_RPM (9767972, 0x950c24) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_RPM_9767972_t
{
    /** Signal RPM. */
    uint16_t RPM;

} cap_PT_RT_DL1MK3_RPM_9767972_t;


/** The signals of inbound CAN frame RT_DL1MK3_Freq_4 (9767716, 0x950b24) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Freq_4_9767716_t
{
    /** Signal Frequency_4. */
    uint16_t Frequency_4;

} cap_PT_RT_DL1MK3_Freq_4_9767716_t;


/** The signals of inbound CAN frame RT_DL1MK3_Misc_3 (9896740, 0x970324) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Misc_3_9896740_t
{
    /** Signal Misc_3. */
    uint16_t Misc_3;

} cap_PT_RT_DL1MK3_Misc_3_9896740_t;


/** The signals of inbound CAN frame RT_DL1MK3_Misc_2 (9896484, 0x970224) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Misc_2_9896484_t
{
    /** Signal Misc_2. */
    uint16_t Misc_2;

} cap_PT_RT_DL1MK3_Misc_2_9896484_t;


/** The signals of inbound CAN frame RT_DL1MK3_Misc_1 (9896228, 0x970124) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Misc_1_9896228_t
{
    /** Signal Misc_1. */
    uint16_t Misc_1;

} cap_PT_RT_DL1MK3_Misc_1_9896228_t;


/** The signals of inbound CAN frame RT_DL1MK3_Aux_2 (9699876, 0x940224) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Aux_2_9699876_t
{
    /** Signal AUX_2. */
    uint16_t AUX_2;

} cap_PT_RT_DL1MK3_Aux_2_9699876_t;


/** The signals of inbound CAN frame RT_DL1MK3_Aux_1 (9699620, 0x940124) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Aux_1_9699620_t
{
    /** Signal AUX_1. */
    uint16_t AUX_1;

} cap_PT_RT_DL1MK3_Aux_1_9699620_t;


/** The signals of inbound CAN frame RT_DL1MK3_Pressure_5 (9438500, 0x900524) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Pressure_5_9438500_t
{
    /** Signal Pressure_5. */
    uint32_t Pressure_5;

} cap_PT_RT_DL1MK3_Pressure_5_9438500_t;


/** The signals of inbound CAN frame RT_DL1MK3_Angle_3 (9569060, 0x920324) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Angle_3_9569060_t
{
    /** Signal Angle_3. */
    int16_t Angle_3;

} cap_PT_RT_DL1MK3_Angle_3_9569060_t;


/** The signals of inbound CAN frame RT_DL1MK3_Temp_1 (9503012, 0x910124) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Temp_1_9503012_t
{
    /** Signal Temperature_1. */
    int16_t Temperature_1;

} cap_PT_RT_DL1MK3_Temp_1_9503012_t;


/** The signals of inbound CAN frame RT_DL1MK3_Analog_3 (8520228, 0x820224) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Analog_3_8520228_t
{
    /** Signal Analog_3. */
    uint16_t Analog_3;

} cap_PT_RT_DL1MK3_Analog_3_8520228_t;


/** The signals of inbound CAN frame RT_DL1MK3_Analog_2 (8519972, 0x820124) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Analog_2_8519972_t
{
    /** Signal Analog_2. */
    uint16_t Analog_2;

} cap_PT_RT_DL1MK3_Analog_2_8519972_t;


/** The signals of inbound CAN frame RT_DL1MK3_Analog_1 (8519716, 0x820024) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Analog_1_8519716_t
{
    /** Signal Analog_1. */
    uint16_t Analog_1;

} cap_PT_RT_DL1MK3_Analog_1_8519716_t;


/** The signals of inbound CAN frame RT_DL1MK3_Accel (8388644, 0x800024) on
    bus PT. */
typedef struct cap_PT_RT_DL1MK3_Accel_8388644_t
{
    /** Signal Validity_Accel_Longitudinal. */
    boolean_t Validity_Accel_Longitudinal;

    /** Signal Validity_Accel_Lateral. */
    boolean_t Validity_Accel_Lateral;

    /** Signal Validity_Accel_Vertical. */
    boolean_t Validity_Accel_Vertical;

    /** Signal SQC. */
    uint8_t SQC; /* Signal is not used by node ECU. */

    /** Signal Accuracy_Accel. */
    uint8_t Accuracy_Accel;

    /** Signal Accel_Longitudinal. */
    int16_t Accel_Longitudinal;

    /** Signal Accel_Lateral. */
    int16_t Accel_Lateral;

    /** Signal Accel_Vertical. */
    int16_t Accel_Vertical;

} cap_PT_RT_DL1MK3_Accel_8388644_t;


/** The signals of inbound CAN frame RT_SB_INS_Status (9306146, 0x8e0022) on
    bus PT. */
typedef struct cap_PT_RT_SB_INS_Status_9306146_t
{
    /** Signal INS_Status. */
    uint8_t INS_Status;

} cap_PT_RT_SB_INS_Status_9306146_t;


/** The signals of inbound CAN frame RT_SB_INS_Attitude (9306402, 0x8e0122) on
    bus PT. */
typedef struct cap_PT_RT_SB_INS_Attitude_9306402_t
{
    /** Signal Validity_Yaw. */
    boolean_t Validity_Yaw;

    /** Signal Validity_Pitch. */
    boolean_t Validity_Pitch;

    /** Signal Validity_Roll. */
    boolean_t Validity_Roll;

    /** Signal Accuracy_Attitude. */
    uint8_t Accuracy_Attitude;

    /** Signal Attitude_Yaw. */
    int16_t Attitude_Yaw;

    /** Signal Attitude_Pitch. */
    int16_t Attitude_Pitch;

    /** Signal Attitude_Roll. */
    int16_t Attitude_Roll;

} cap_PT_RT_SB_INS_Attitude_9306402_t;


/** The signals of inbound CAN frame RT_SB_Output_Status (9240866, 0x8d0122) on
    bus PT. */
typedef struct cap_PT_RT_SB_Output_Status_9240866_t
{
    /** Signal Validity_Status_Timestamp. */
    boolean_t Validity_Status_Timestamp;

    /** Signal Status_Analogue_1. */
    boolean_t Status_Analogue_1;

    /** Signal Status_Analogue_2. */
    boolean_t Status_Analogue_2;

    /** Signal Status_Analogue_3. */
    boolean_t Status_Analogue_3;

    /** Signal Status_Analogue_4. */
    boolean_t Status_Analogue_4;

    /** Signal Status_Pulse_Output. */
    boolean_t Status_Pulse_Output;

    /** Signal Status_Serial_Output_1. */
    boolean_t Status_Serial_Output_1;

    /** Signal Status_Serial_Output_2. */
    boolean_t Status_Serial_Output_2;

    /** Signal Status_Trigger. */
    boolean_t Status_Trigger;

    /** Signal GPS_Time. */
    uint32_t GPS_Time;

} cap_PT_RT_SB_Output_Status_9240866_t;


/** The signals of inbound CAN frame RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_t
{
    /** Signal Validity_GPS_Heading. */
    boolean_t Validity_GPS_Heading;

    /** Signal Validity_GPS_Gradient. */
    boolean_t Validity_GPS_Gradient;

    /** Signal Accuracy_GPS_Heading. */
    uint8_t Accuracy_GPS_Heading;

    /** Signal GPS_Heading_2. */
    uint16_t GPS_Heading_2;

    /** Signal Accuracy_GPS_Gradient. */
    uint8_t Accuracy_GPS_Gradient;

    /** Signal GPS_Gradient. */
    int16_t GPS_Gradient;

} cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_t;


/** The signals of inbound CAN frame RT_SB_Cumulative_Distance_2 (8397090, 0x802122) on
    bus PT. */
typedef struct cap_PT_RT_SB_Cumulative_Distance_2_8397090_t
{
    /** Signal Validity_Cumulative_Time. */
    boolean_t Validity_Cumulative_Time;

    /** Signal Validity_Cumulative_Distance. */
    boolean_t Validity_Cumulative_Distance;

    /** Signal Cumulative_Time. */
    uint32_t Cumulative_Time;

    /** Signal Cumulative_Distance. */
    uint32_t Cumulative_Distance;

} cap_PT_RT_SB_Cumulative_Distance_2_8397090_t;


/** The signals of inbound CAN frame RT_SB_Cumulative_Distance_1 (8396834, 0x802022) on
    bus PT. */
typedef struct cap_PT_RT_SB_Cumulative_Distance_1_8396834_t
{
    /** Signal Validity_Cumulative_Time. */
    boolean_t Validity_Cumulative_Time;

    /** Signal Validity_Cumulative_Distance. */
    boolean_t Validity_Cumulative_Distance;

    /** Signal Cumulative_Time. */
    uint32_t Cumulative_Time;

    /** Signal Cumulative_Distance. */
    uint32_t Cumulative_Distance;

} cap_PT_RT_SB_Cumulative_Distance_1_8396834_t;


/** The signals of inbound CAN frame RT_SB_Trigger_Timestamp (9240610, 0x8d0022) on
    bus PT. */
typedef struct cap_PT_RT_SB_Trigger_Timestamp_9240610_t
{
    /** Signal Validity_Trigger_Timestamp. */
    boolean_t Validity_Trigger_Timestamp;

    /** Signal Accuracy_Trigger_Timestamp. */
    uint8_t Accuracy_Trigger_Timestamp;

    /** Signal Trigger_Number. */
    uint8_t Trigger_Number;

    /** Signal Trigger_Timestamp_Type. */
    boolean_t Trigger_Timestamp_Type;

    /** Signal GPS_High_Resolution_Time. */
    uint64_t GPS_High_Resolution_Time;

} cap_PT_RT_SB_Trigger_Timestamp_9240610_t;


/** The signals of inbound CAN frame RT_IMU06_Gyro_Rates (8388897, 0x800121) on
    bus PT. */
typedef struct cap_PT_RT_IMU06_Gyro_Rates_8388897_t
{
    /** Signal Validity_Gyro_Rate_Yaw. */
    boolean_t Validity_Gyro_Rate_Yaw;

    /** Signal Validity_Gyro_Rate_Pitch. */
    boolean_t Validity_Gyro_Rate_Pitch;

    /** Signal Validity_Gyro_Rate_Roll. */
    boolean_t Validity_Gyro_Rate_Roll;

    /** Signal Accuracy_Gyro_Rates. */
    uint8_t Accuracy_Gyro_Rates;

    /** Signal Gyro_Rate_Yaw. */
    int16_t Gyro_Rate_Yaw;

    /** Signal Gyro_Rate_Pitch. */
    int16_t Gyro_Rate_Pitch;

    /** Signal Gyro_Rate_Roll. */
    int16_t Gyro_Rate_Roll;

} cap_PT_RT_IMU06_Gyro_Rates_8388897_t;


/** The signals of inbound CAN frame RT_IMU06_Accel (8388641, 0x800021) on
    bus PT. */
typedef struct cap_PT_RT_IMU06_Accel_8388641_t
{
    /** Signal Validity_Accel_Longitudinal. */
    boolean_t Validity_Accel_Longitudinal;

    /** Signal Validity_Accel_Lateral. */
    boolean_t Validity_Accel_Lateral;

    /** Signal Validity_Accel_Vertical. */
    boolean_t Validity_Accel_Vertical;

    /** Signal Accuracy_Accel. */
    uint8_t Accuracy_Accel;

    /** Signal Accel_Longitudinal. */
    int16_t Accel_Longitudinal;

    /** Signal Accel_Lateral. */
    int16_t Accel_Lateral;

    /** Signal Accel_Vertical. */
    int16_t Accel_Vertical;

} cap_PT_RT_IMU06_Accel_8388641_t;


/** The signals of inbound CAN frame RT_SB_Speed (8392738, 0x801022) on
    bus PT. */
typedef struct cap_PT_RT_SB_Speed_8392738_t
{
    /** Signal Validity_Speed. */
    boolean_t Validity_Speed;

    /** Signal Accuracy_Speed. */
    uint8_t Accuracy_Speed;

    /** Signal Speed. */
    int32_t Speed;

} cap_PT_RT_SB_Speed_8392738_t;


/** The signals of inbound CAN frame RT_SB_RTK_Slip (9183522, 0x8c2122) on
    bus PT. */
typedef struct cap_PT_RT_SB_RTK_Slip_9183522_t
{
    /** Signal Validity_RTK_Slip. */
    boolean_t Validity_RTK_Slip;

    /** Signal Validity_RTK_Squat. */
    boolean_t Validity_RTK_Squat;

    /** Signal Validity_RTK_Baseline. */
    boolean_t Validity_RTK_Baseline;

    /** Signal Accuracy_RTK_Baseline. */
    uint8_t Accuracy_RTK_Baseline;

    /** Signal RTK_Slip. */
    int16_t RTK_Slip;

    /** Signal RTK_Squat. */
    int16_t RTK_Squat;

    /** Signal RTK_Baseline. */
    uint16_t RTK_Baseline;

} cap_PT_RT_SB_RTK_Slip_9183522_t;


/** The signals of inbound CAN frame RT_SB_RTK_Attitude (9183266, 0x8c2022) on
    bus PT. */
typedef struct cap_PT_RT_SB_RTK_Attitude_9183266_t
{
    /** Signal Validity_RTK_Yaw. */
    boolean_t Validity_RTK_Yaw;

    /** Signal Validity_RTK_Pitch. */
    boolean_t Validity_RTK_Pitch;

    /** Signal Validity_RTK_Roll. */
    boolean_t Validity_RTK_Roll;

    /** Signal Accuracy_RTK_Attitude. */
    uint8_t Accuracy_RTK_Attitude;

    /** Signal RTK_Attitude_Yaw. */
    int16_t RTK_Attitude_Yaw;

    /** Signal RTK_Attitude_Pitch. */
    int16_t RTK_Attitude_Pitch;

    /** Signal RTK_Attitude_Roll. */
    int16_t RTK_Attitude_Roll;

} cap_PT_RT_SB_RTK_Attitude_9183266_t;


/** The signals of inbound CAN frame RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_t
{
    /** Signal Validity_GPS_Lateral_Accel. */
    boolean_t Validity_GPS_Lateral_Accel;

    /** Signal Validity_GPS_Mcycle_Lean. */
    boolean_t Validity_GPS_Mcycle_Lean;

    /** Signal Accuracy_GPS_Lateral_Accel. */
    uint8_t Accuracy_GPS_Lateral_Accel;

    /** Signal GPS_Lateral_Accel. */
    int16_t GPS_Lateral_Accel;

    /** Signal GPS_Mcycle_Lean_Angle. */
    int16_t GPS_Mcycle_Lean_Angle;

} cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_t;


/** The signals of inbound CAN frame RT_SB_GPS_Status (9175074, 0x8c0022) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Status_9175074_t
{
    /** Signal GPS_Status. */
    uint8_t GPS_Status;

    /** Signal Firmware_Version_Major. */
    uint8_t Firmware_Version_Major;

    /** Signal Firmware_Version_Intermediate. */
    uint8_t Firmware_Version_Intermediate;

    /** Signal Firmware_Version_Minor. */
    uint8_t Firmware_Version_Minor;

    /** Signal GPS_nSv. */
    uint8_t GPS_nSv;

    /** Signal GPS_nSv_2. */
    uint8_t GPS_nSv_2;

    /** Signal GPS_nSv_RTK. */
    uint8_t GPS_nSv_RTK;

    /** Signal RTK_Status. */
    uint8_t RTK_Status;

} cap_PT_RT_SB_GPS_Status_9175074_t;


/** The signals of inbound CAN frame RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_t
{
    /** Signal GPS_Pos_ECEF_Y. */
    int32_t GPS_Pos_ECEF_Y;

    /** Signal GPS_Pos_ECEF_Z. */
    int32_t GPS_Pos_ECEF_Z;

} cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_t;


/** The signals of inbound CAN frame RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_t
{
    /** Signal Validity_GPS_Pos_ECEF_X. */
    boolean_t Validity_GPS_Pos_ECEF_X;

    /** Signal Validity_GPS_Pos_ECEF_Y. */
    boolean_t Validity_GPS_Pos_ECEF_Y;

    /** Signal Validity_GPS_Pos_ECEF_Z. */
    boolean_t Validity_GPS_Pos_ECEF_Z;

    /** Signal Accuracy_GPS_Pos_ECEF_X. */
    uint8_t Accuracy_GPS_Pos_ECEF_X;

    /** Signal Accuracy_GPS_Pos_ECEF_Y. */
    uint8_t Accuracy_GPS_Pos_ECEF_Y;

    /** Signal Accuracy_GPS_Pos_ECEF_Z. */
    uint8_t Accuracy_GPS_Pos_ECEF_Z;

    /** Signal GPS_Pos_ECEF_X. */
    int32_t GPS_Pos_ECEF_X;

} cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_t;


/** The signals of inbound CAN frame RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_t
{
    /** Signal GPS_Pos_LLH_Longitude. */
    int32_t GPS_Pos_LLH_Longitude;

    /** Signal GPS_Pos_LLH_Altitude. */
    int32_t GPS_Pos_LLH_Altitude;

} cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_t;


/** The signals of inbound CAN frame RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_t
{
    /** Signal Validity_GPS_Pos_LLH_Latitude. */
    boolean_t Validity_GPS_Pos_LLH_Latitude;

    /** Signal Validity_GPS_Pos_LLH_Longitude. */
    boolean_t Validity_GPS_Pos_LLH_Longitude;

    /** Signal Validity_GPS_Pos_LLH_Altitude. */
    boolean_t Validity_GPS_Pos_LLH_Altitude;

    /** Signal Accuracy_GPS_Pos_LLH_Latitude. */
    uint8_t Accuracy_GPS_Pos_LLH_Latitude;

    /** Signal Accuracy_GPS_Pos_LLH_Longitude. */
    uint8_t Accuracy_GPS_Pos_LLH_Longitude;

    /** Signal Accuracy_GPS_Pos_LLH_Altitude. */
    uint8_t Accuracy_GPS_Pos_LLH_Altitude;

    /** Signal GPS_Pos_LLH_Latitude. */
    int32_t GPS_Pos_LLH_Latitude;

} cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_t;


/** The signals of inbound CAN frame RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Heading_Gradient_9180450_t
{
    /** Signal Validity_GPS_Heading. */
    boolean_t Validity_GPS_Heading;

    /** Signal Validity_GPS_Gradient. */
    boolean_t Validity_GPS_Gradient;

    /** Signal Accuracy_GPS_Heading. */
    uint8_t Accuracy_GPS_Heading;

    /** Signal GPS_Heading. */
    int16_t GPS_Heading;

    /** Signal Accuracy_GPS_Gradient. */
    uint8_t Accuracy_GPS_Gradient;

    /** Signal GPS_Gradient. */
    int16_t GPS_Gradient;

} cap_PT_RT_SB_GPS_Heading_Gradient_9180450_t;


/** The signals of inbound CAN frame RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_t
{
    /** Signal Validity_GPS_Vel_ECEF_Y. */
    boolean_t Validity_GPS_Vel_ECEF_Y;

    /** Signal Validity_GPS_Vel_ECEF_Z. */
    boolean_t Validity_GPS_Vel_ECEF_Z;

    /** Signal GPS_Vel_ECEF_Y. */
    int32_t GPS_Vel_ECEF_Y;

    /** Signal GPS_Vel_ECEF_Z. */
    int32_t GPS_Vel_ECEF_Z;

} cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_t;


/** The signals of inbound CAN frame RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_t
{
    /** Signal Validity_GPS_Vel_ECEF_X. */
    boolean_t Validity_GPS_Vel_ECEF_X;

    /** Signal Accuracy_GPS_Vel_ECEF_X. */
    uint8_t Accuracy_GPS_Vel_ECEF_X;

    /** Signal Accuracy_GPS_Vel_ECEF_Y. */
    uint8_t Accuracy_GPS_Vel_ECEF_Y;

    /** Signal Accuracy_GPS_Vel_ECEF_Z. */
    uint8_t Accuracy_GPS_Vel_ECEF_Z;

    /** Signal GPS_Vel_ECEF_X. */
    int32_t GPS_Vel_ECEF_X;

} cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_t;


/** The signals of inbound CAN frame RT_SB_GPS_Vel_NED_2 (0, 0x000) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Vel_NED_2_0_t
{
    /** Signal Validity_GPS_Vel_NED_D. */
    boolean_t Validity_GPS_Vel_NED_D;

    /** Signal Accuracy_GPS_Vel_D. */
    uint8_t Accuracy_GPS_Vel_D;

    /** Signal GPS_Vel_NED_D. */
    int32_t GPS_Vel_NED_D;

} cap_PT_RT_SB_GPS_Vel_NED_2_0_t;


/** The signals of inbound CAN frame RT_SB_GPS_Speed (1818, 0x71a) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Speed_1818_t
{
    /** Signal Validity_GPS_Speed_2D. */
    boolean_t Validity_GPS_Speed_2D;

    /** Signal Validity_GPS_Speed_3D. */
    boolean_t Validity_GPS_Speed_3D;

    /** Signal Accuracy_GPS_Speed. */
    uint8_t Accuracy_GPS_Speed;

    /** Signal GPS_Speed_2D. */
    uint32_t GPS_Speed_2D;

    /** Signal GPS_Speed_3D. */
    uint32_t GPS_Speed_3D;

} cap_PT_RT_SB_GPS_Speed_1818_t;


/** The signals of inbound CAN frame RT_SB_GPS_Time (2047, 0x7ff) on
    bus PT. */
typedef struct cap_PT_RT_SB_GPS_Time_2047_t
{
    /** Signal Validity_GPS_Time. */
    boolean_t Validity_GPS_Time;

    /** Signal Validity_GPS_Week. */
    boolean_t Validity_GPS_Week;

    /** Signal Accuracy_GPS_Time. */
    uint8_t Accuracy_GPS_Time;

    /** Signal GPS_Time. */
    uint32_t GPS_Time;

    /** Signal GPS_Week. */
    uint16_t GPS_Week;

} cap_PT_RT_SB_GPS_Time_2047_t;


/** The signals of inbound CAN frame RT_SB_Accel (290, 0x122) on
    bus PT. */
typedef struct cap_PT_RT_SB_Accel_290_t
{
    /** Signal Validity_Accel_Longitudinal. */
    boolean_t Validity_Accel_Longitudinal;

    /** Signal Validity_Accel_Lateral. */
    boolean_t Validity_Accel_Lateral;

    /** Signal Validity_Accel_Vertical. */
    boolean_t Validity_Accel_Vertical;

    /** Signal Accuracy_Accel. */
    uint8_t Accuracy_Accel;

    /** Signal Accel_Longitudinal. */
    int16_t Accel_Longitudinal;

    /** Signal Accel_Lateral. */
    int16_t Accel_Lateral;

    /** Signal Accel_Vertical. */
    int16_t Accel_Vertical;

} cap_PT_RT_SB_Accel_290_t;


/** The signals of inbound CAN frame RT_SB_Gyro_Rates (8388898, 0x800122) on
    bus PT. */
typedef struct cap_PT_RT_SB_Gyro_Rates_8388898_t
{
    /** Signal Validity_Gyro_Rate_Yaw. */
    boolean_t Validity_Gyro_Rate_Yaw;

    /** Signal Validity_Gyro_Rate_Pitch. */
    boolean_t Validity_Gyro_Rate_Pitch;

    /** Signal Validity_Gyro_Rate_Roll. */
    boolean_t Validity_Gyro_Rate_Roll;

    /** Signal Accuracy_Gyro_Rates. */
    uint8_t Accuracy_Gyro_Rates;

    /** Signal Gyro_Rate_Yaw. */
    int16_t Gyro_Rate_Yaw;

    /** Signal Gyro_Rate_Pitch. */
    int16_t Gyro_Rate_Pitch;

    /** Signal Gyro_Rate_Roll. */
    int16_t Gyro_Rate_Roll;

} cap_PT_RT_SB_Gyro_Rates_8388898_t;


/** Signals and transmission status of inbound CAN frame RT_SB_INS_Vel_Body_Axes
    (215, 0x0d7) on bus PT. */
typedef struct cap_PT_RT_SB_INS_Vel_Body_Axes_215_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_INS_Vel_Body_Axes_215_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_INS_Vel_Body_Axes_215_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Speed
    (8392740, 0x801024) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Speed_8392740_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Speed_8392740_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Speed_8392740_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Time
    (9175332, 0x8c0124) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_GPS_Time_9175332_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_GPS_Time_9175332_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_GPS_Time_9175332_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Pos_LLH_2
    (9175844, 0x8c0324) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Pos_LLH_1
    (9175588, 0x8c0224) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Speed
    (1234, 0x4d2) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_GPS_Speed_1234_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_GPS_Speed_1234_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_GPS_Speed_1234_sts_t;


/** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_RL_2
    (9963045, 0x980625) on bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_RL_2_9963045_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IRTemp_Temp_RL_2_9963045_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IRTemp_Temp_RL_2_9963045_sts_t;


/** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_FR_2
    (9962533, 0x980425) on bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_FR_2_9962533_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IRTemp_Temp_FR_2_9962533_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IRTemp_Temp_FR_2_9962533_sts_t;


/** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_FL_2
    (9962021, 0x980225) on bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_FL_2_9962021_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IRTemp_Temp_FL_2_9962021_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IRTemp_Temp_FL_2_9962021_sts_t;


/** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_RL_1
    (9962789, 0x980525) on bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_RL_1_9962789_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IRTemp_Temp_RL_1_9962789_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IRTemp_Temp_RL_1_9962789_sts_t;


/** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_FR_1
    (9962277, 0x980325) on bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_FR_1_9962277_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IRTemp_Temp_FR_1_9962277_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IRTemp_Temp_FR_1_9962277_sts_t;


/** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_FL_1
    (9961765, 0x980125) on bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_FL_1_9961765_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IRTemp_Temp_FL_1_9961765_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IRTemp_Temp_FL_1_9961765_sts_t;


/** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_30
    (9510437, 0x911e25) on bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_30_9510437_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IRTemp_Temp_30_9510437_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IRTemp_Temp_30_9510437_sts_t;


/** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_26
    (9509413, 0x911a25) on bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_26_9509413_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IRTemp_Temp_26_9509413_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IRTemp_Temp_26_9509413_sts_t;


/** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_1
    (9503013, 0x910125) on bus PT. */
typedef struct cap_PT_RT_IRTemp_Temp_1_9503013_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IRTemp_Temp_1_9503013_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IRTemp_Temp_1_9503013_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Trig_Final_Condition
    (9242402, 0x8d0722) on bus PT. */
typedef struct cap_PT_RT_SB_Trig_Final_Condition_9242402_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Trig_Final_Condition_9242402_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Trig_Final_Condition_9242402_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Trig_Initial_Condition
    (794, 0x31a) on bus PT. */
typedef struct cap_PT_RT_SB_Trig_Initial_Condition_794_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Trig_Initial_Condition_794_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Trig_Initial_Condition_794_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Trig_Direct_Dist
    (9241890, 0x8d0522) on bus PT. */
typedef struct cap_PT_RT_SB_Trig_Direct_Dist_9241890_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Trig_Direct_Dist_9241890_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Trig_Direct_Dist_9241890_sts_t;


/** Signals and transmission status of outbound CAN frame RT_SB_Trig_Forward_Dist
    (9241634, 0x8d0422) on bus PT. */
typedef struct cap_PT_RT_SB_Trig_Forward_Dist_9241634_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Trig_Forward_Dist_9241634_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Trig_Forward_Dist_9241634_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Trig_Path_Dist
    (9241378, 0x8d0322) on bus PT. */
typedef struct cap_PT_RT_SB_Trig_Path_Dist_9241378_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Trig_Path_Dist_9241378_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Trig_Path_Dist_9241378_sts_t;


/** Signals and transmission status of outbound CAN frame RT_SB_Trig_Accel
    (9241122, 0x8d0222) on bus PT. */
typedef struct cap_PT_RT_SB_Trig_Accel_9241122_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Trig_Accel_9241122_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Trig_Accel_9241122_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_11
    (9833252, 0x960b24) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_11_9833252_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_11_9833252_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_11_9833252_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_10
    (9832996, 0x960a24) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_10_9832996_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_10_9832996_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_10_9832996_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_9
    (9832740, 0x960924) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_9_9832740_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_9_9832740_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_9_9832740_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_8
    (9832484, 0x960824) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_8_9832484_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_8_9832484_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_8_9832484_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_7
    (9832228, 0x960724) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_7_9832228_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_7_9832228_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_7_9832228_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_6
    (9831972, 0x960624) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_6_9831972_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_6_9831972_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_6_9831972_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_5
    (9831716, 0x960524) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_5_9831716_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_5_9831716_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_5_9831716_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_4
    (9831460, 0x960424) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_4_9831460_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_4_9831460_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_4_9831460_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_3
    (9831204, 0x960324) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_3_9831204_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_3_9831204_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_3_9831204_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_2
    (9830948, 0x960224) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_2_9830948_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_2_9830948_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_2_9830948_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_1
    (9830692, 0x960124) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Measure_Time_1_9830692_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Measure_Time_1_9830692_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Measure_Time_1_9830692_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_RPM
    (9767972, 0x950c24) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_RPM_9767972_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_RPM_9767972_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_RPM_9767972_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Freq_4
    (9767716, 0x950b24) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Freq_4_9767716_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Freq_4_9767716_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Freq_4_9767716_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Misc_3
    (9896740, 0x970324) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Misc_3_9896740_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Misc_3_9896740_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Misc_3_9896740_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Misc_2
    (9896484, 0x970224) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Misc_2_9896484_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Misc_2_9896484_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Misc_2_9896484_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Misc_1
    (9896228, 0x970124) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Misc_1_9896228_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Misc_1_9896228_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Misc_1_9896228_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Aux_2
    (9699876, 0x940224) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Aux_2_9699876_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Aux_2_9699876_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Aux_2_9699876_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Aux_1
    (9699620, 0x940124) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Aux_1_9699620_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Aux_1_9699620_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Aux_1_9699620_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Pressure_5
    (9438500, 0x900524) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Pressure_5_9438500_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Pressure_5_9438500_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Pressure_5_9438500_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Angle_3
    (9569060, 0x920324) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Angle_3_9569060_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Angle_3_9569060_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Angle_3_9569060_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Temp_1
    (9503012, 0x910124) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Temp_1_9503012_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Temp_1_9503012_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Temp_1_9503012_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Analog_3
    (8520228, 0x820224) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Analog_3_8520228_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Analog_3_8520228_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Analog_3_8520228_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Analog_2
    (8519972, 0x820124) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Analog_2_8519972_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Analog_2_8519972_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Analog_2_8519972_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Analog_1
    (8519716, 0x820024) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Analog_1_8519716_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Analog_1_8519716_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Analog_1_8519716_sts_t;


/** Signals and transmission status of inbound CAN frame RT_DL1MK3_Accel
    (8388644, 0x800024) on bus PT. */
typedef struct cap_PT_RT_DL1MK3_Accel_8388644_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_DL1MK3_Accel_8388644_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_DL1MK3_Accel_8388644_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_INS_Status
    (9306146, 0x8e0022) on bus PT. */
typedef struct cap_PT_RT_SB_INS_Status_9306146_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_INS_Status_9306146_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_INS_Status_9306146_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_INS_Attitude
    (9306402, 0x8e0122) on bus PT. */
typedef struct cap_PT_RT_SB_INS_Attitude_9306402_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_INS_Attitude_9306402_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_INS_Attitude_9306402_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Output_Status
    (9240866, 0x8d0122) on bus PT. */
typedef struct cap_PT_RT_SB_Output_Status_9240866_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Output_Status_9240866_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Output_Status_9240866_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Heading_Gradient_2
    (9180706, 0x8c1622) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Cumulative_Distance_2
    (8397090, 0x802122) on bus PT. */
typedef struct cap_PT_RT_SB_Cumulative_Distance_2_8397090_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Cumulative_Distance_2_8397090_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Cumulative_Distance_2_8397090_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Cumulative_Distance_1
    (8396834, 0x802022) on bus PT. */
typedef struct cap_PT_RT_SB_Cumulative_Distance_1_8396834_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Cumulative_Distance_1_8396834_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Cumulative_Distance_1_8396834_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Trigger_Timestamp
    (9240610, 0x8d0022) on bus PT. */
typedef struct cap_PT_RT_SB_Trigger_Timestamp_9240610_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Trigger_Timestamp_9240610_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Trigger_Timestamp_9240610_sts_t;


/** Signals and transmission status of inbound CAN frame RT_IMU06_Gyro_Rates
    (8388897, 0x800121) on bus PT. */
typedef struct cap_PT_RT_IMU06_Gyro_Rates_8388897_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IMU06_Gyro_Rates_8388897_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IMU06_Gyro_Rates_8388897_sts_t;


/** Signals and transmission status of inbound CAN frame RT_IMU06_Accel
    (8388641, 0x800021) on bus PT. */
typedef struct cap_PT_RT_IMU06_Accel_8388641_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_IMU06_Accel_8388641_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_IMU06_Accel_8388641_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Speed
    (8392738, 0x801022) on bus PT. */
typedef struct cap_PT_RT_SB_Speed_8392738_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Speed_8392738_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Speed_8392738_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_RTK_Slip
    (9183522, 0x8c2122) on bus PT. */
typedef struct cap_PT_RT_SB_RTK_Slip_9183522_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_RTK_Slip_9183522_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_RTK_Slip_9183522_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_RTK_Attitude
    (9183266, 0x8c2022) on bus PT. */
typedef struct cap_PT_RT_SB_RTK_Attitude_9183266_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_RTK_Attitude_9183266_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_RTK_Attitude_9183266_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Mcycle_Lean
    (9187362, 0x8c3022) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Status
    (9175074, 0x8c0022) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Status_9175074_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Status_9175074_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Status_9175074_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_ECEF_2
    (9176354, 0x8c0522) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_ECEF_1
    (9176098, 0x8c0422) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_LLH_2
    (9175842, 0x8c0322) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_LLH_1
    (9175586, 0x8c0222) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Heading_Gradient
    (9180450, 0x8c1522) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Heading_Gradient_9180450_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Heading_Gradient_9180450_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Heading_Gradient_9180450_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Vel_ECEF_2
    (9180194, 0x8c1422) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Vel_ECEF_1
    (9179938, 0x8c1322) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Vel_NED_2
    (0, 0x000) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Vel_NED_2_0_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Vel_NED_2_0_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Vel_NED_2_0_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Speed
    (1818, 0x71a) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Speed_1818_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Speed_1818_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Speed_1818_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_GPS_Time
    (2047, 0x7ff) on bus PT. */
typedef struct cap_PT_RT_SB_GPS_Time_2047_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_GPS_Time_2047_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_GPS_Time_2047_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Accel
    (290, 0x122) on bus PT. */
typedef struct cap_PT_RT_SB_Accel_290_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Accel_290_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Accel_290_sts_t;


/** Signals and transmission status of inbound CAN frame RT_SB_Gyro_Rates
    (8388898, 0x800122) on bus PT. */
typedef struct cap_PT_RT_SB_Gyro_Rates_8388898_sts_t
{
    /** The collection of signals of the frame. */
    cap_PT_RT_SB_Gyro_Rates_8388898_t signals;

    /** Some transmission related information for this frame. */
    cap_infoTransmission_t infoTransmission;

} cap_PT_RT_SB_Gyro_Rates_8388898_sts_t;



/** The frames and signals of CAN bus PT. A global variable of this type is used
    as API between the lower layers of the CAN stack and the APSW. */
typedef struct cap_canBus_PT_t
{
    /** Signals and transmission status of inbound CAN frame RT_SB_INS_Vel_Body_Axes
        (215, 0x0d7) */
    cap_PT_RT_SB_INS_Vel_Body_Axes_215_sts_t PT_RT_SB_INS_Vel_Body_Axes_215_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Speed
        (8392740, 0x801024) */
    cap_PT_RT_DL1MK3_Speed_8392740_sts_t PT_RT_DL1MK3_Speed_8392740_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Time
        (9175332, 0x8c0124) */
    cap_PT_RT_DL1MK3_GPS_Time_9175332_sts_t PT_RT_DL1MK3_GPS_Time_9175332_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Pos_LLH_2
        (9175844, 0x8c0324) */
    cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts_t PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Pos_LLH_1
        (9175588, 0x8c0224) */
    cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts_t PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_GPS_Speed
        (1234, 0x4d2) */
    cap_PT_RT_DL1MK3_GPS_Speed_1234_sts_t PT_RT_DL1MK3_GPS_Speed_1234_sts;

    /** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_RL_2
        (9963045, 0x980625) */
    cap_PT_RT_IRTemp_Temp_RL_2_9963045_sts_t PT_RT_IRTemp_Temp_RL_2_9963045_sts;

    /** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_FR_2
        (9962533, 0x980425) */
    cap_PT_RT_IRTemp_Temp_FR_2_9962533_sts_t PT_RT_IRTemp_Temp_FR_2_9962533_sts;

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_FL_2
        (9962021, 0x980225) */
    cap_PT_RT_IRTemp_Temp_FL_2_9962021_sts_t PT_RT_IRTemp_Temp_FL_2_9962021_sts;

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_RL_1
        (9962789, 0x980525) */
    cap_PT_RT_IRTemp_Temp_RL_1_9962789_sts_t PT_RT_IRTemp_Temp_RL_1_9962789_sts;

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_FR_1
        (9962277, 0x980325) */
    cap_PT_RT_IRTemp_Temp_FR_1_9962277_sts_t PT_RT_IRTemp_Temp_FR_1_9962277_sts;

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_FL_1
        (9961765, 0x980125) */
    cap_PT_RT_IRTemp_Temp_FL_1_9961765_sts_t PT_RT_IRTemp_Temp_FL_1_9961765_sts;

    /** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_30
        (9510437, 0x911e25) */
    cap_PT_RT_IRTemp_Temp_30_9510437_sts_t PT_RT_IRTemp_Temp_30_9510437_sts;

    /** Signals and transmission status of outbound CAN frame RT_IRTemp_Temp_26
        (9509413, 0x911a25) */
    cap_PT_RT_IRTemp_Temp_26_9509413_sts_t PT_RT_IRTemp_Temp_26_9509413_sts;

    /** Signals and transmission status of inbound CAN frame RT_IRTemp_Temp_1
        (9503013, 0x910125) */
    cap_PT_RT_IRTemp_Temp_1_9503013_sts_t PT_RT_IRTemp_Temp_1_9503013_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Trig_Final_Condition
        (9242402, 0x8d0722) */
    cap_PT_RT_SB_Trig_Final_Condition_9242402_sts_t PT_RT_SB_Trig_Final_Condition_9242402_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Trig_Initial_Condition
        (794, 0x31a) */
    cap_PT_RT_SB_Trig_Initial_Condition_794_sts_t PT_RT_SB_Trig_Initial_Condition_794_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Trig_Direct_Dist
        (9241890, 0x8d0522) */
    cap_PT_RT_SB_Trig_Direct_Dist_9241890_sts_t PT_RT_SB_Trig_Direct_Dist_9241890_sts;

    /** Signals and transmission status of outbound CAN frame RT_SB_Trig_Forward_Dist
        (9241634, 0x8d0422) */
    cap_PT_RT_SB_Trig_Forward_Dist_9241634_sts_t PT_RT_SB_Trig_Forward_Dist_9241634_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Trig_Path_Dist
        (9241378, 0x8d0322) */
    cap_PT_RT_SB_Trig_Path_Dist_9241378_sts_t PT_RT_SB_Trig_Path_Dist_9241378_sts;

    /** Signals and transmission status of outbound CAN frame RT_SB_Trig_Accel
        (9241122, 0x8d0222) */
    cap_PT_RT_SB_Trig_Accel_9241122_sts_t PT_RT_SB_Trig_Accel_9241122_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_11
        (9833252, 0x960b24) */
    cap_PT_RT_DL1MK3_Measure_Time_11_9833252_sts_t PT_RT_DL1MK3_Measure_Time_11_9833252_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_10
        (9832996, 0x960a24) */
    cap_PT_RT_DL1MK3_Measure_Time_10_9832996_sts_t PT_RT_DL1MK3_Measure_Time_10_9832996_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_9
        (9832740, 0x960924) */
    cap_PT_RT_DL1MK3_Measure_Time_9_9832740_sts_t PT_RT_DL1MK3_Measure_Time_9_9832740_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_8
        (9832484, 0x960824) */
    cap_PT_RT_DL1MK3_Measure_Time_8_9832484_sts_t PT_RT_DL1MK3_Measure_Time_8_9832484_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_7
        (9832228, 0x960724) */
    cap_PT_RT_DL1MK3_Measure_Time_7_9832228_sts_t PT_RT_DL1MK3_Measure_Time_7_9832228_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_6
        (9831972, 0x960624) */
    cap_PT_RT_DL1MK3_Measure_Time_6_9831972_sts_t PT_RT_DL1MK3_Measure_Time_6_9831972_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_5
        (9831716, 0x960524) */
    cap_PT_RT_DL1MK3_Measure_Time_5_9831716_sts_t PT_RT_DL1MK3_Measure_Time_5_9831716_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_4
        (9831460, 0x960424) */
    cap_PT_RT_DL1MK3_Measure_Time_4_9831460_sts_t PT_RT_DL1MK3_Measure_Time_4_9831460_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_3
        (9831204, 0x960324) */
    cap_PT_RT_DL1MK3_Measure_Time_3_9831204_sts_t PT_RT_DL1MK3_Measure_Time_3_9831204_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_2
        (9830948, 0x960224) */
    cap_PT_RT_DL1MK3_Measure_Time_2_9830948_sts_t PT_RT_DL1MK3_Measure_Time_2_9830948_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Measure_Time_1
        (9830692, 0x960124) */
    cap_PT_RT_DL1MK3_Measure_Time_1_9830692_sts_t PT_RT_DL1MK3_Measure_Time_1_9830692_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_RPM
        (9767972, 0x950c24) */
    cap_PT_RT_DL1MK3_RPM_9767972_sts_t PT_RT_DL1MK3_RPM_9767972_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Freq_4
        (9767716, 0x950b24) */
    cap_PT_RT_DL1MK3_Freq_4_9767716_sts_t PT_RT_DL1MK3_Freq_4_9767716_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Misc_3
        (9896740, 0x970324) */
    cap_PT_RT_DL1MK3_Misc_3_9896740_sts_t PT_RT_DL1MK3_Misc_3_9896740_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Misc_2
        (9896484, 0x970224) */
    cap_PT_RT_DL1MK3_Misc_2_9896484_sts_t PT_RT_DL1MK3_Misc_2_9896484_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Misc_1
        (9896228, 0x970124) */
    cap_PT_RT_DL1MK3_Misc_1_9896228_sts_t PT_RT_DL1MK3_Misc_1_9896228_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Aux_2
        (9699876, 0x940224) */
    cap_PT_RT_DL1MK3_Aux_2_9699876_sts_t PT_RT_DL1MK3_Aux_2_9699876_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Aux_1
        (9699620, 0x940124) */
    cap_PT_RT_DL1MK3_Aux_1_9699620_sts_t PT_RT_DL1MK3_Aux_1_9699620_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Pressure_5
        (9438500, 0x900524) */
    cap_PT_RT_DL1MK3_Pressure_5_9438500_sts_t PT_RT_DL1MK3_Pressure_5_9438500_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Angle_3
        (9569060, 0x920324) */
    cap_PT_RT_DL1MK3_Angle_3_9569060_sts_t PT_RT_DL1MK3_Angle_3_9569060_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Temp_1
        (9503012, 0x910124) */
    cap_PT_RT_DL1MK3_Temp_1_9503012_sts_t PT_RT_DL1MK3_Temp_1_9503012_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Analog_3
        (8520228, 0x820224) */
    cap_PT_RT_DL1MK3_Analog_3_8520228_sts_t PT_RT_DL1MK3_Analog_3_8520228_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Analog_2
        (8519972, 0x820124) */
    cap_PT_RT_DL1MK3_Analog_2_8519972_sts_t PT_RT_DL1MK3_Analog_2_8519972_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Analog_1
        (8519716, 0x820024) */
    cap_PT_RT_DL1MK3_Analog_1_8519716_sts_t PT_RT_DL1MK3_Analog_1_8519716_sts;

    /** Signals and transmission status of inbound CAN frame RT_DL1MK3_Accel
        (8388644, 0x800024) */
    cap_PT_RT_DL1MK3_Accel_8388644_sts_t PT_RT_DL1MK3_Accel_8388644_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_INS_Status
        (9306146, 0x8e0022) */
    cap_PT_RT_SB_INS_Status_9306146_sts_t PT_RT_SB_INS_Status_9306146_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_INS_Attitude
        (9306402, 0x8e0122) */
    cap_PT_RT_SB_INS_Attitude_9306402_sts_t PT_RT_SB_INS_Attitude_9306402_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Output_Status
        (9240866, 0x8d0122) */
    cap_PT_RT_SB_Output_Status_9240866_sts_t PT_RT_SB_Output_Status_9240866_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Heading_Gradient_2
        (9180706, 0x8c1622) */
    cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts_t PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Cumulative_Distance_2
        (8397090, 0x802122) */
    cap_PT_RT_SB_Cumulative_Distance_2_8397090_sts_t PT_RT_SB_Cumulative_Distance_2_8397090_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Cumulative_Distance_1
        (8396834, 0x802022) */
    cap_PT_RT_SB_Cumulative_Distance_1_8396834_sts_t PT_RT_SB_Cumulative_Distance_1_8396834_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Trigger_Timestamp
        (9240610, 0x8d0022) */
    cap_PT_RT_SB_Trigger_Timestamp_9240610_sts_t PT_RT_SB_Trigger_Timestamp_9240610_sts;

    /** Signals and transmission status of inbound CAN frame RT_IMU06_Gyro_Rates
        (8388897, 0x800121) */
    cap_PT_RT_IMU06_Gyro_Rates_8388897_sts_t PT_RT_IMU06_Gyro_Rates_8388897_sts;

    /** Signals and transmission status of inbound CAN frame RT_IMU06_Accel
        (8388641, 0x800021) */
    cap_PT_RT_IMU06_Accel_8388641_sts_t PT_RT_IMU06_Accel_8388641_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Speed
        (8392738, 0x801022) */
    cap_PT_RT_SB_Speed_8392738_sts_t PT_RT_SB_Speed_8392738_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_RTK_Slip
        (9183522, 0x8c2122) */
    cap_PT_RT_SB_RTK_Slip_9183522_sts_t PT_RT_SB_RTK_Slip_9183522_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_RTK_Attitude
        (9183266, 0x8c2022) */
    cap_PT_RT_SB_RTK_Attitude_9183266_sts_t PT_RT_SB_RTK_Attitude_9183266_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Mcycle_Lean
        (9187362, 0x8c3022) */
    cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_sts_t PT_RT_SB_GPS_Mcycle_Lean_9187362_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Status
        (9175074, 0x8c0022) */
    cap_PT_RT_SB_GPS_Status_9175074_sts_t PT_RT_SB_GPS_Status_9175074_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_ECEF_2
        (9176354, 0x8c0522) */
    cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts_t PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_ECEF_1
        (9176098, 0x8c0422) */
    cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts_t PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_LLH_2
        (9175842, 0x8c0322) */
    cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_sts_t PT_RT_SB_GPS_Pos_LLH_2_9175842_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Pos_LLH_1
        (9175586, 0x8c0222) */
    cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_sts_t PT_RT_SB_GPS_Pos_LLH_1_9175586_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Heading_Gradient
        (9180450, 0x8c1522) */
    cap_PT_RT_SB_GPS_Heading_Gradient_9180450_sts_t PT_RT_SB_GPS_Heading_Gradient_9180450_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Vel_ECEF_2
        (9180194, 0x8c1422) */
    cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts_t PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Vel_ECEF_1
        (9179938, 0x8c1322) */
    cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts_t PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Vel_NED_2
        (0, 0x000) */
    cap_PT_RT_SB_GPS_Vel_NED_2_0_sts_t PT_RT_SB_GPS_Vel_NED_2_0_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Speed
        (1818, 0x71a) */
    cap_PT_RT_SB_GPS_Speed_1818_sts_t PT_RT_SB_GPS_Speed_1818_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_GPS_Time
        (2047, 0x7ff) */
    cap_PT_RT_SB_GPS_Time_2047_sts_t PT_RT_SB_GPS_Time_2047_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Accel
        (290, 0x122) */
    cap_PT_RT_SB_Accel_290_sts_t PT_RT_SB_Accel_290_sts;

    /** Signals and transmission status of inbound CAN frame RT_SB_Gyro_Rates
        (8388898, 0x800122) */
    cap_PT_RT_SB_Gyro_Rates_8388898_sts_t PT_RT_SB_Gyro_Rates_8388898_sts;


} cap_canBus_PT_t;




/*
 * Data declarations
 */

/** Signals and transmission status of CAN frames on bus PT. This global variable
    is used as API between the lower layers of the CAN stack and the APSW. */
extern cap_canBus_PT_t cap_canBus_PT;



/*
 * Function declarations
 */

#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_INS_Vel_Body_Axes_215_sts. */
void cap_packApi_PT_RT_SB_INS_Vel_Body_Axes(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_INS_Vel_Body_Axes
                ( uint8_t m[]
                , const cap_PT_RT_SB_INS_Vel_Body_Axes_215_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_INS_Vel_Body_Axes_215_sts. */
void cap_unpackApi_PT_RT_SB_INS_Vel_Body_Axes(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_INS_Vel_Body_Axes (215, 0x0d7) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_INS_Vel_Body_Axes
                ( cap_PT_RT_SB_INS_Vel_Body_Axes_215_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024)
    into a byte array of 7 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Speed_8392740_sts. */
void cap_packApi_PT_RT_DL1MK3_Speed(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024)
    into a byte array of 7 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Speed
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Speed_8392740_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024) from
    a byte array of 7 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Speed_8392740_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Speed(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Speed (8392740, 0x801024) from
    a byte array of 7 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Speed
                ( cap_PT_RT_DL1MK3_Speed_8392740_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_GPS_Time_9175332_sts. */
void cap_packApi_PT_RT_DL1MK3_GPS_Time(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_GPS_Time
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_GPS_Time_9175332_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_GPS_Time_9175332_sts. */
void cap_unpackApi_PT_RT_DL1MK3_GPS_Time(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Time (9175332, 0x8c0124) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_GPS_Time
                ( cap_PT_RT_DL1MK3_GPS_Time_9175332_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts. */
void cap_packApi_PT_RT_DL1MK3_GPS_Pos_LLH_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_GPS_Pos_LLH_2
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_sts. */
void cap_unpackApi_PT_RT_DL1MK3_GPS_Pos_LLH_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_2 (9175844, 0x8c0324) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_2
                ( cap_PT_RT_DL1MK3_GPS_Pos_LLH_2_9175844_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts. */
void cap_packApi_PT_RT_DL1MK3_GPS_Pos_LLH_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_GPS_Pos_LLH_1
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_sts. */
void cap_unpackApi_PT_RT_DL1MK3_GPS_Pos_LLH_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Pos_LLH_1 (9175588, 0x8c0224) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_GPS_Pos_LLH_1
                ( cap_PT_RT_DL1MK3_GPS_Pos_LLH_1_9175588_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_GPS_Speed_1234_sts. */
void cap_packApi_PT_RT_DL1MK3_GPS_Speed(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_GPS_Speed
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_GPS_Speed_1234_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_GPS_Speed_1234_sts. */
void cap_unpackApi_PT_RT_DL1MK3_GPS_Speed(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_GPS_Speed (1234, 0x4d2) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_GPS_Speed
                ( cap_PT_RT_DL1MK3_GPS_Speed_1234_t *pFrameStruct
                , const uint8_t m[]
                );

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IRTemp_Temp_RL_2_9963045_sts. */
void cap_packApi_PT_RT_IRTemp_Temp_RL_2(uint8_t m[]);

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IRTemp_Temp_RL_2
                ( uint8_t m[]
                , const cap_PT_RT_IRTemp_Temp_RL_2_9963045_t *pFrameStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_IRTemp_Temp_RL_2_9963045_sts. */
void cap_unpackApi_PT_RT_IRTemp_Temp_RL_2(const uint8_t m[]);

/** Unpack the signals of outbound PDU RT_IRTemp_Temp_RL_2 (9963045, 0x980625) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IRTemp_Temp_RL_2
                ( cap_PT_RT_IRTemp_Temp_RL_2_9963045_t *pFrameStruct
                , const uint8_t m[]
                );
#endif

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IRTemp_Temp_FR_2_9962533_sts. */
void cap_packApi_PT_RT_IRTemp_Temp_FR_2(uint8_t m[]);

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IRTemp_Temp_FR_2
                ( uint8_t m[]
                , const cap_PT_RT_IRTemp_Temp_FR_2_9962533_t *pFrameStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_IRTemp_Temp_FR_2_9962533_sts. */
void cap_unpackApi_PT_RT_IRTemp_Temp_FR_2(const uint8_t m[]);

/** Unpack the signals of outbound PDU RT_IRTemp_Temp_FR_2 (9962533, 0x980425) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IRTemp_Temp_FR_2
                ( cap_PT_RT_IRTemp_Temp_FR_2_9962533_t *pFrameStruct
                , const uint8_t m[]
                );
#endif


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IRTemp_Temp_FL_2_9962021_sts. */
void cap_packApi_PT_RT_IRTemp_Temp_FL_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IRTemp_Temp_FL_2
                ( uint8_t m[]
                , const cap_PT_RT_IRTemp_Temp_FL_2_9962021_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_IRTemp_Temp_FL_2_9962021_sts. */
void cap_unpackApi_PT_RT_IRTemp_Temp_FL_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_2 (9962021, 0x980225) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IRTemp_Temp_FL_2
                ( cap_PT_RT_IRTemp_Temp_FL_2_9962021_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IRTemp_Temp_RL_1_9962789_sts. */
void cap_packApi_PT_RT_IRTemp_Temp_RL_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IRTemp_Temp_RL_1
                ( uint8_t m[]
                , const cap_PT_RT_IRTemp_Temp_RL_1_9962789_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_IRTemp_Temp_RL_1_9962789_sts. */
void cap_unpackApi_PT_RT_IRTemp_Temp_RL_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_RL_1 (9962789, 0x980525) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IRTemp_Temp_RL_1
                ( cap_PT_RT_IRTemp_Temp_RL_1_9962789_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IRTemp_Temp_FR_1_9962277_sts. */
void cap_packApi_PT_RT_IRTemp_Temp_FR_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IRTemp_Temp_FR_1
                ( uint8_t m[]
                , const cap_PT_RT_IRTemp_Temp_FR_1_9962277_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_IRTemp_Temp_FR_1_9962277_sts. */
void cap_unpackApi_PT_RT_IRTemp_Temp_FR_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_FR_1 (9962277, 0x980325) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IRTemp_Temp_FR_1
                ( cap_PT_RT_IRTemp_Temp_FR_1_9962277_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IRTemp_Temp_FL_1_9961765_sts. */
void cap_packApi_PT_RT_IRTemp_Temp_FL_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IRTemp_Temp_FL_1
                ( uint8_t m[]
                , const cap_PT_RT_IRTemp_Temp_FL_1_9961765_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_IRTemp_Temp_FL_1_9961765_sts. */
void cap_unpackApi_PT_RT_IRTemp_Temp_FL_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_FL_1 (9961765, 0x980125) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IRTemp_Temp_FL_1
                ( cap_PT_RT_IRTemp_Temp_FL_1_9961765_t *pFrameStruct
                , const uint8_t m[]
                );

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IRTemp_Temp_30_9510437_sts. */
void cap_packApi_PT_RT_IRTemp_Temp_30(uint8_t m[]);

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IRTemp_Temp_30
                ( uint8_t m[]
                , const cap_PT_RT_IRTemp_Temp_30_9510437_t *pFrameStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_IRTemp_Temp_30_9510437_sts. */
void cap_unpackApi_PT_RT_IRTemp_Temp_30(const uint8_t m[]);

/** Unpack the signals of outbound PDU RT_IRTemp_Temp_30 (9510437, 0x911e25) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IRTemp_Temp_30
                ( cap_PT_RT_IRTemp_Temp_30_9510437_t *pFrameStruct
                , const uint8_t m[]
                );
#endif

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IRTemp_Temp_26_9509413_sts. */
void cap_packApi_PT_RT_IRTemp_Temp_26(uint8_t m[]);

/** Pack the signal values of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IRTemp_Temp_26
                ( uint8_t m[]
                , const cap_PT_RT_IRTemp_Temp_26_9509413_t *pFrameStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_IRTemp_Temp_26_9509413_sts. */
void cap_unpackApi_PT_RT_IRTemp_Temp_26(const uint8_t m[]);

/** Unpack the signals of outbound PDU RT_IRTemp_Temp_26 (9509413, 0x911a25) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IRTemp_Temp_26
                ( cap_PT_RT_IRTemp_Temp_26_9509413_t *pFrameStruct
                , const uint8_t m[]
                );
#endif


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IRTemp_Temp_1_9503013_sts. */
void cap_packApi_PT_RT_IRTemp_Temp_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IRTemp_Temp_1
                ( uint8_t m[]
                , const cap_PT_RT_IRTemp_Temp_1_9503013_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_IRTemp_Temp_1_9503013_sts. */
void cap_unpackApi_PT_RT_IRTemp_Temp_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_IRTemp_Temp_1 (9503013, 0x910125) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IRTemp_Temp_1
                ( cap_PT_RT_IRTemp_Temp_1_9503013_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Trig_Final_Condition_9242402_sts. */
void cap_packApi_PT_RT_SB_Trig_Final_Condition(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Trig_Final_Condition
                ( uint8_t m[]
                , const cap_PT_RT_SB_Trig_Final_Condition_9242402_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Trig_Final_Condition_9242402_sts. */
void cap_unpackApi_PT_RT_SB_Trig_Final_Condition(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Trig_Final_Condition (9242402, 0x8d0722) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Trig_Final_Condition
                ( cap_PT_RT_SB_Trig_Final_Condition_9242402_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Trig_Initial_Condition_794_sts. */
void cap_packApi_PT_RT_SB_Trig_Initial_Condition(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Trig_Initial_Condition
                ( uint8_t m[]
                , const cap_PT_RT_SB_Trig_Initial_Condition_794_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Trig_Initial_Condition_794_sts. */
void cap_unpackApi_PT_RT_SB_Trig_Initial_Condition(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Trig_Initial_Condition (794, 0x31a) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Trig_Initial_Condition
                ( cap_PT_RT_SB_Trig_Initial_Condition_794_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Trig_Direct_Dist_9241890_sts. */
void cap_packApi_PT_RT_SB_Trig_Direct_Dist(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Trig_Direct_Dist
                ( uint8_t m[]
                , const cap_PT_RT_SB_Trig_Direct_Dist_9241890_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Trig_Direct_Dist_9241890_sts. */
void cap_unpackApi_PT_RT_SB_Trig_Direct_Dist(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Trig_Direct_Dist (9241890, 0x8d0522) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Trig_Direct_Dist
                ( cap_PT_RT_SB_Trig_Direct_Dist_9241890_t *pFrameStruct
                , const uint8_t m[]
                );

/** Pack the signal values of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Trig_Forward_Dist_9241634_sts. */
void cap_packApi_PT_RT_SB_Trig_Forward_Dist(uint8_t m[]);

/** Pack the signal values of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Trig_Forward_Dist
                ( uint8_t m[]
                , const cap_PT_RT_SB_Trig_Forward_Dist_9241634_t *pFrameStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Trig_Forward_Dist_9241634_sts. */
void cap_unpackApi_PT_RT_SB_Trig_Forward_Dist(const uint8_t m[]);

/** Unpack the signals of outbound PDU RT_SB_Trig_Forward_Dist (9241634, 0x8d0422) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Trig_Forward_Dist
                ( cap_PT_RT_SB_Trig_Forward_Dist_9241634_t *pFrameStruct
                , const uint8_t m[]
                );
#endif


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Trig_Path_Dist_9241378_sts. */
void cap_packApi_PT_RT_SB_Trig_Path_Dist(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Trig_Path_Dist
                ( uint8_t m[]
                , const cap_PT_RT_SB_Trig_Path_Dist_9241378_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Trig_Path_Dist_9241378_sts. */
void cap_unpackApi_PT_RT_SB_Trig_Path_Dist(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Trig_Path_Dist (9241378, 0x8d0322) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Trig_Path_Dist
                ( cap_PT_RT_SB_Trig_Path_Dist_9241378_t *pFrameStruct
                , const uint8_t m[]
                );

/** Pack the signal values of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Trig_Accel_9241122_sts. */
void cap_packApi_PT_RT_SB_Trig_Accel(uint8_t m[]);

/** Pack the signal values of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Trig_Accel
                ( uint8_t m[]
                , const cap_PT_RT_SB_Trig_Accel_9241122_t *pFrameStruct
                );

#if CAP_UNCONDITIONALLY_GENERATE_UNPACK_FCTS != 0
/** Unpack the signals of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Trig_Accel_9241122_sts. */
void cap_unpackApi_PT_RT_SB_Trig_Accel(const uint8_t m[]);

/** Unpack the signals of outbound PDU RT_SB_Trig_Accel (9241122, 0x8d0222) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Trig_Accel
                ( cap_PT_RT_SB_Trig_Accel_9241122_t *pFrameStruct
                , const uint8_t m[]
                );
#endif


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_11_9833252_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_11(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_11
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_11_9833252_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_11_9833252_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_11(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_11 (9833252, 0x960b24) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_11
                ( cap_PT_RT_DL1MK3_Measure_Time_11_9833252_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_10_9832996_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_10(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_10
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_10_9832996_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_10_9832996_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_10(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_10 (9832996, 0x960a24) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_10
                ( cap_PT_RT_DL1MK3_Measure_Time_10_9832996_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_9_9832740_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_9(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_9
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_9_9832740_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_9_9832740_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_9(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_9 (9832740, 0x960924) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_9
                ( cap_PT_RT_DL1MK3_Measure_Time_9_9832740_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_8_9832484_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_8(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_8
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_8_9832484_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_8_9832484_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_8(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_8 (9832484, 0x960824) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_8
                ( cap_PT_RT_DL1MK3_Measure_Time_8_9832484_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_7_9832228_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_7(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_7
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_7_9832228_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_7_9832228_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_7(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_7 (9832228, 0x960724) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_7
                ( cap_PT_RT_DL1MK3_Measure_Time_7_9832228_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_6_9831972_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_6(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_6
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_6_9831972_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_6_9831972_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_6(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_6 (9831972, 0x960624) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_6
                ( cap_PT_RT_DL1MK3_Measure_Time_6_9831972_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_5_9831716_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_5(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_5
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_5_9831716_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_5_9831716_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_5(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_5 (9831716, 0x960524) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_5
                ( cap_PT_RT_DL1MK3_Measure_Time_5_9831716_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_4_9831460_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_4(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_4
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_4_9831460_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_4_9831460_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_4(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_4 (9831460, 0x960424) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_4
                ( cap_PT_RT_DL1MK3_Measure_Time_4_9831460_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_3_9831204_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_3(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_3
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_3_9831204_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_3_9831204_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_3(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_3 (9831204, 0x960324) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_3
                ( cap_PT_RT_DL1MK3_Measure_Time_3_9831204_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_2_9830948_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_2
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_2_9830948_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_2_9830948_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_2 (9830948, 0x960224) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_2
                ( cap_PT_RT_DL1MK3_Measure_Time_2_9830948_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Measure_Time_1_9830692_sts. */
void cap_packApi_PT_RT_DL1MK3_Measure_Time_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Measure_Time_1
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Measure_Time_1_9830692_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Measure_Time_1_9830692_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Measure_Time_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Measure_Time_1 (9830692, 0x960124) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Measure_Time_1
                ( cap_PT_RT_DL1MK3_Measure_Time_1_9830692_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_RPM_9767972_sts. */
void cap_packApi_PT_RT_DL1MK3_RPM(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_RPM
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_RPM_9767972_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_RPM_9767972_sts. */
void cap_unpackApi_PT_RT_DL1MK3_RPM(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_RPM (9767972, 0x950c24) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_RPM
                ( cap_PT_RT_DL1MK3_RPM_9767972_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Freq_4_9767716_sts. */
void cap_packApi_PT_RT_DL1MK3_Freq_4(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Freq_4
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Freq_4_9767716_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Freq_4_9767716_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Freq_4(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Freq_4 (9767716, 0x950b24) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Freq_4
                ( cap_PT_RT_DL1MK3_Freq_4_9767716_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Misc_3_9896740_sts. */
void cap_packApi_PT_RT_DL1MK3_Misc_3(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Misc_3
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Misc_3_9896740_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Misc_3_9896740_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Misc_3(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Misc_3 (9896740, 0x970324) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Misc_3
                ( cap_PT_RT_DL1MK3_Misc_3_9896740_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Misc_2_9896484_sts. */
void cap_packApi_PT_RT_DL1MK3_Misc_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Misc_2
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Misc_2_9896484_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Misc_2_9896484_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Misc_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Misc_2 (9896484, 0x970224) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Misc_2
                ( cap_PT_RT_DL1MK3_Misc_2_9896484_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Misc_1_9896228_sts. */
void cap_packApi_PT_RT_DL1MK3_Misc_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Misc_1
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Misc_1_9896228_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Misc_1_9896228_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Misc_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Misc_1 (9896228, 0x970124) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Misc_1
                ( cap_PT_RT_DL1MK3_Misc_1_9896228_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Aux_2_9699876_sts. */
void cap_packApi_PT_RT_DL1MK3_Aux_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Aux_2
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Aux_2_9699876_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Aux_2_9699876_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Aux_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_2 (9699876, 0x940224) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Aux_2
                ( cap_PT_RT_DL1MK3_Aux_2_9699876_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Aux_1_9699620_sts. */
void cap_packApi_PT_RT_DL1MK3_Aux_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Aux_1
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Aux_1_9699620_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Aux_1_9699620_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Aux_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Aux_1 (9699620, 0x940124) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Aux_1
                ( cap_PT_RT_DL1MK3_Aux_1_9699620_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524)
    into a byte array of 3 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Pressure_5_9438500_sts. */
void cap_packApi_PT_RT_DL1MK3_Pressure_5(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524)
    into a byte array of 3 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Pressure_5
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Pressure_5_9438500_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524) from
    a byte array of 3 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Pressure_5_9438500_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Pressure_5(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Pressure_5 (9438500, 0x900524) from
    a byte array of 3 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Pressure_5
                ( cap_PT_RT_DL1MK3_Pressure_5_9438500_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Angle_3_9569060_sts. */
void cap_packApi_PT_RT_DL1MK3_Angle_3(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Angle_3
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Angle_3_9569060_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Angle_3_9569060_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Angle_3(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Angle_3 (9569060, 0x920324) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Angle_3
                ( cap_PT_RT_DL1MK3_Angle_3_9569060_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Temp_1_9503012_sts. */
void cap_packApi_PT_RT_DL1MK3_Temp_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Temp_1
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Temp_1_9503012_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Temp_1_9503012_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Temp_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Temp_1 (9503012, 0x910124) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Temp_1
                ( cap_PT_RT_DL1MK3_Temp_1_9503012_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Analog_3_8520228_sts. */
void cap_packApi_PT_RT_DL1MK3_Analog_3(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Analog_3
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Analog_3_8520228_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Analog_3_8520228_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Analog_3(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_3 (8520228, 0x820224) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Analog_3
                ( cap_PT_RT_DL1MK3_Analog_3_8520228_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Analog_2_8519972_sts. */
void cap_packApi_PT_RT_DL1MK3_Analog_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Analog_2
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Analog_2_8519972_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Analog_2_8519972_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Analog_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_2 (8519972, 0x820124) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Analog_2
                ( cap_PT_RT_DL1MK3_Analog_2_8519972_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024)
    into a byte array of 2 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Analog_1_8519716_sts. */
void cap_packApi_PT_RT_DL1MK3_Analog_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024)
    into a byte array of 2 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Analog_1
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Analog_1_8519716_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024) from
    a byte array of 2 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Analog_1_8519716_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Analog_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Analog_1 (8519716, 0x820024) from
    a byte array of 2 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Analog_1
                ( cap_PT_RT_DL1MK3_Analog_1_8519716_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_DL1MK3_Accel_8388644_sts. */
void cap_packApi_PT_RT_DL1MK3_Accel(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_DL1MK3_Accel
                ( uint8_t m[]
                , const cap_PT_RT_DL1MK3_Accel_8388644_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_DL1MK3_Accel_8388644_sts. */
void cap_unpackApi_PT_RT_DL1MK3_Accel(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_DL1MK3_Accel (8388644, 0x800024) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_DL1MK3_Accel
                ( cap_PT_RT_DL1MK3_Accel_8388644_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_INS_Status_9306146_sts. */
void cap_packApi_PT_RT_SB_INS_Status(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_INS_Status
                ( uint8_t m[]
                , const cap_PT_RT_SB_INS_Status_9306146_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_INS_Status_9306146_sts. */
void cap_unpackApi_PT_RT_SB_INS_Status(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_INS_Status (9306146, 0x8e0022) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_INS_Status
                ( cap_PT_RT_SB_INS_Status_9306146_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_INS_Attitude_9306402_sts. */
void cap_packApi_PT_RT_SB_INS_Attitude(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_INS_Attitude
                ( uint8_t m[]
                , const cap_PT_RT_SB_INS_Attitude_9306402_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_INS_Attitude_9306402_sts. */
void cap_unpackApi_PT_RT_SB_INS_Attitude(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_INS_Attitude (9306402, 0x8e0122) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_INS_Attitude
                ( cap_PT_RT_SB_INS_Attitude_9306402_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Output_Status_9240866_sts. */
void cap_packApi_PT_RT_SB_Output_Status(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Output_Status
                ( uint8_t m[]
                , const cap_PT_RT_SB_Output_Status_9240866_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Output_Status_9240866_sts. */
void cap_unpackApi_PT_RT_SB_Output_Status(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Output_Status (9240866, 0x8d0122) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Output_Status
                ( cap_PT_RT_SB_Output_Status_9240866_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts. */
void cap_packApi_PT_RT_SB_GPS_Heading_Gradient_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Heading_Gradient_2
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Heading_Gradient_2_9180706_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Heading_Gradient_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient_2 (9180706, 0x8c1622) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Heading_Gradient_2
                ( cap_PT_RT_SB_GPS_Heading_Gradient_2_9180706_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Cumulative_Distance_2_8397090_sts. */
void cap_packApi_PT_RT_SB_Cumulative_Distance_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Cumulative_Distance_2
                ( uint8_t m[]
                , const cap_PT_RT_SB_Cumulative_Distance_2_8397090_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Cumulative_Distance_2_8397090_sts. */
void cap_unpackApi_PT_RT_SB_Cumulative_Distance_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_2 (8397090, 0x802122) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Cumulative_Distance_2
                ( cap_PT_RT_SB_Cumulative_Distance_2_8397090_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Cumulative_Distance_1_8396834_sts. */
void cap_packApi_PT_RT_SB_Cumulative_Distance_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Cumulative_Distance_1
                ( uint8_t m[]
                , const cap_PT_RT_SB_Cumulative_Distance_1_8396834_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Cumulative_Distance_1_8396834_sts. */
void cap_unpackApi_PT_RT_SB_Cumulative_Distance_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Cumulative_Distance_1 (8396834, 0x802022) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Cumulative_Distance_1
                ( cap_PT_RT_SB_Cumulative_Distance_1_8396834_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Trigger_Timestamp_9240610_sts. */
void cap_packApi_PT_RT_SB_Trigger_Timestamp(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Trigger_Timestamp
                ( uint8_t m[]
                , const cap_PT_RT_SB_Trigger_Timestamp_9240610_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Trigger_Timestamp_9240610_sts. */
void cap_unpackApi_PT_RT_SB_Trigger_Timestamp(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Trigger_Timestamp (9240610, 0x8d0022) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Trigger_Timestamp
                ( cap_PT_RT_SB_Trigger_Timestamp_9240610_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IMU06_Gyro_Rates_8388897_sts. */
void cap_packApi_PT_RT_IMU06_Gyro_Rates(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IMU06_Gyro_Rates
                ( uint8_t m[]
                , const cap_PT_RT_IMU06_Gyro_Rates_8388897_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_IMU06_Gyro_Rates_8388897_sts. */
void cap_unpackApi_PT_RT_IMU06_Gyro_Rates(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_IMU06_Gyro_Rates (8388897, 0x800121) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IMU06_Gyro_Rates
                ( cap_PT_RT_IMU06_Gyro_Rates_8388897_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_IMU06_Accel (8388641, 0x800021)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_IMU06_Accel_8388641_sts. */
void cap_packApi_PT_RT_IMU06_Accel(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_IMU06_Accel (8388641, 0x800021)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_IMU06_Accel
                ( uint8_t m[]
                , const cap_PT_RT_IMU06_Accel_8388641_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_IMU06_Accel (8388641, 0x800021) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_IMU06_Accel_8388641_sts. */
void cap_unpackApi_PT_RT_IMU06_Accel(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_IMU06_Accel (8388641, 0x800021) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_IMU06_Accel
                ( cap_PT_RT_IMU06_Accel_8388641_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Speed (8392738, 0x801022)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Speed_8392738_sts. */
void cap_packApi_PT_RT_SB_Speed(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Speed (8392738, 0x801022)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Speed
                ( uint8_t m[]
                , const cap_PT_RT_SB_Speed_8392738_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Speed (8392738, 0x801022) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Speed_8392738_sts. */
void cap_unpackApi_PT_RT_SB_Speed(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Speed (8392738, 0x801022) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Speed
                ( cap_PT_RT_SB_Speed_8392738_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_RTK_Slip_9183522_sts. */
void cap_packApi_PT_RT_SB_RTK_Slip(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_RTK_Slip
                ( uint8_t m[]
                , const cap_PT_RT_SB_RTK_Slip_9183522_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_RTK_Slip_9183522_sts. */
void cap_unpackApi_PT_RT_SB_RTK_Slip(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_RTK_Slip (9183522, 0x8c2122) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_RTK_Slip
                ( cap_PT_RT_SB_RTK_Slip_9183522_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_RTK_Attitude_9183266_sts. */
void cap_packApi_PT_RT_SB_RTK_Attitude(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_RTK_Attitude
                ( uint8_t m[]
                , const cap_PT_RT_SB_RTK_Attitude_9183266_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_RTK_Attitude_9183266_sts. */
void cap_unpackApi_PT_RT_SB_RTK_Attitude(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_RTK_Attitude (9183266, 0x8c2022) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_RTK_Attitude
                ( cap_PT_RT_SB_RTK_Attitude_9183266_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Mcycle_Lean_9187362_sts. */
void cap_packApi_PT_RT_SB_GPS_Mcycle_Lean(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Mcycle_Lean
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Mcycle_Lean_9187362_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Mcycle_Lean(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Mcycle_Lean (9187362, 0x8c3022) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Mcycle_Lean
                ( cap_PT_RT_SB_GPS_Mcycle_Lean_9187362_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Status_9175074_sts. */
void cap_packApi_PT_RT_SB_GPS_Status(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Status
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Status_9175074_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Status_9175074_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Status(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Status (9175074, 0x8c0022) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Status
                ( cap_PT_RT_SB_GPS_Status_9175074_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts. */
void cap_packApi_PT_RT_SB_GPS_Pos_ECEF_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Pos_ECEF_2
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Pos_ECEF_2_9176354_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Pos_ECEF_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_2 (9176354, 0x8c0522) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Pos_ECEF_2
                ( cap_PT_RT_SB_GPS_Pos_ECEF_2_9176354_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts. */
void cap_packApi_PT_RT_SB_GPS_Pos_ECEF_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Pos_ECEF_1
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Pos_ECEF_1_9176098_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Pos_ECEF_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_ECEF_1 (9176098, 0x8c0422) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Pos_ECEF_1
                ( cap_PT_RT_SB_GPS_Pos_ECEF_1_9176098_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_2_9175842_sts. */
void cap_packApi_PT_RT_SB_GPS_Pos_LLH_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Pos_LLH_2
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Pos_LLH_2_9175842_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Pos_LLH_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_2 (9175842, 0x8c0322) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Pos_LLH_2
                ( cap_PT_RT_SB_GPS_Pos_LLH_2_9175842_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Pos_LLH_1_9175586_sts. */
void cap_packApi_PT_RT_SB_GPS_Pos_LLH_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Pos_LLH_1
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Pos_LLH_1_9175586_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Pos_LLH_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Pos_LLH_1 (9175586, 0x8c0222) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Pos_LLH_1
                ( cap_PT_RT_SB_GPS_Pos_LLH_1_9175586_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Heading_Gradient_9180450_sts. */
void cap_packApi_PT_RT_SB_GPS_Heading_Gradient(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Heading_Gradient
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Heading_Gradient_9180450_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Heading_Gradient_9180450_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Heading_Gradient(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Heading_Gradient (9180450, 0x8c1522) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Heading_Gradient
                ( cap_PT_RT_SB_GPS_Heading_Gradient_9180450_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts. */
void cap_packApi_PT_RT_SB_GPS_Vel_ECEF_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Vel_ECEF_2
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Vel_ECEF_2_9180194_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Vel_ECEF_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_2 (9180194, 0x8c1422) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Vel_ECEF_2
                ( cap_PT_RT_SB_GPS_Vel_ECEF_2_9180194_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts. */
void cap_packApi_PT_RT_SB_GPS_Vel_ECEF_1(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Vel_ECEF_1
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Vel_ECEF_1_9179938_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Vel_ECEF_1(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_ECEF_1 (9179938, 0x8c1322) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Vel_ECEF_1
                ( cap_PT_RT_SB_GPS_Vel_ECEF_1_9179938_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Vel_NED_2_0_sts. */
void cap_packApi_PT_RT_SB_GPS_Vel_NED_2(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Vel_NED_2
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Vel_NED_2_0_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Vel_NED_2_0_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Vel_NED_2(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Vel_NED_2 (0, 0x000) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Vel_NED_2
                ( cap_PT_RT_SB_GPS_Vel_NED_2_0_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Speed (1818, 0x71a)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Speed_1818_sts. */
void cap_packApi_PT_RT_SB_GPS_Speed(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Speed (1818, 0x71a)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Speed
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Speed_1818_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Speed (1818, 0x71a) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Speed_1818_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Speed(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Speed (1818, 0x71a) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Speed
                ( cap_PT_RT_SB_GPS_Speed_1818_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_GPS_Time (2047, 0x7ff)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_GPS_Time_2047_sts. */
void cap_packApi_PT_RT_SB_GPS_Time(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_GPS_Time (2047, 0x7ff)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_GPS_Time
                ( uint8_t m[]
                , const cap_PT_RT_SB_GPS_Time_2047_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_GPS_Time (2047, 0x7ff) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_GPS_Time_2047_sts. */
void cap_unpackApi_PT_RT_SB_GPS_Time(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_GPS_Time (2047, 0x7ff) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_GPS_Time
                ( cap_PT_RT_SB_GPS_Time_2047_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Accel (290, 0x122)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Accel_290_sts. */
void cap_packApi_PT_RT_SB_Accel(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Accel (290, 0x122)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Accel
                ( uint8_t m[]
                , const cap_PT_RT_SB_Accel_290_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Accel (290, 0x122) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Accel_290_sts. */
void cap_unpackApi_PT_RT_SB_Accel(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Accel (290, 0x122) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Accel
                ( cap_PT_RT_SB_Accel_290_t *pFrameStruct
                , const uint8_t m[]
                );


#if CAP_UNCONDITIONALLY_GENERATE_PACK_FCTS != 0
/** Pack the signal values of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122)
    into a byte array of 8 Byte. The signal values are read from the global interface
    struct cap_canBus_PT.PT_RT_SB_Gyro_Rates_8388898_sts. */
void cap_packApi_PT_RT_SB_Gyro_Rates(uint8_t m[]);

/** Pack the signal values of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122)
    into a byte array of 8 Byte. The signal values are read from a frame by reference. */
void cap_pack_PT_RT_SB_Gyro_Rates
                ( uint8_t m[]
                , const cap_PT_RT_SB_Gyro_Rates_8388898_t *pFrameStruct
                );
#endif

/** Unpack the signals of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122) from
    a byte array of 8 Byte. The signal values are written into the global interface struct
    PT_RT_SB_Gyro_Rates_8388898_sts. */
void cap_unpackApi_PT_RT_SB_Gyro_Rates(const uint8_t m[]);

/** Unpack the signals of inbound PDU RT_SB_Gyro_Rates (8388898, 0x800122) from
    a byte array of 8 Byte. The signal values are written into a frame struct by
    reference. */
void cap_unpack_PT_RT_SB_Gyro_Rates
                ( cap_PT_RT_SB_Gyro_Rates_8388898_t *pFrameStruct
                , const uint8_t m[]
                );



/*
 * Inline function definitions
 */

#endif // !defined(CAP_CANAPI_DEFINED)
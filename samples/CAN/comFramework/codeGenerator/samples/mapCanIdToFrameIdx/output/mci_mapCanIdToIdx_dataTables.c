/**
 * @file mci_mapCanIdToIdx_dataTables.c
 * 
 * A standard use case of sorted frame iteration is the implementation of a mapping table
 * to map the pair CAN bus index plus CAN frame ID (as occasionally used as frame
 * identification in the CAN callback in some platforms) to the zero based linear frame
 * index as used by the CAN interface engine. If we sort the tables in raising order of CAN
 * IDs and separated by buses then an efficient binary search can be applied.\n
 *   As an optimization for (typical) platform, which offer a lot of ROM space but limited
 * CPU power and very limited RAM space, we can further optimize the mapping by separating
 * standard CAN IDs, which are mostly used, from the rarely used extended CAN identifiers.
 * The former span a numeric range of 2048 values, which permits to have a direct lookup
 * table with complexity O(1). Only the few N extended identifiers need a binary search
 * with a complexity O(log(N)).\n
 *   The simplest way to relate the table entries to registered frames is to use the
 * position in the table as index of the frame in the interface engine. This requires that
 * frame registration in our CAN interface is done in the same iteration of frames. It's
 * also possible to have an enumeration of frames and to generate the enumeration in the
 * same iteration as the registration process. This is less ROM efficient but much more
 * transparent. This is what we demonstrate here.\n
 *   Please note, the usual way of doing is to let the code generator produce only the data
 * dependent code (i.e., dependent on the network databases). Consequently, you will not
 * find the algorithms to use the generated tables, particularly the binary search. This is
 * one-time made code and such code should not be developed and maintained through a
 * template. Write this code directly as plain C file.
 *
 * This file has been created with comFramework - codeGenerator version 1.11.2,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "mci_mapCanIdToIdx_dataTables.h"

#include <assert.h>

#include "types.h"

/*
 * Defines
 */

/** Initializer expression for  CAN IDs: Get CAN ID object from raw number and Boolean \a
    isExt. */
#if MCI_SUPPORT_EXTENDED_CAN_IDS == 1
# define MCI_CAN_ID_INIT_EXPR(ID, isExt)    {.u.isExtId=(isExt), .u.id=(ID),}
#else
# define MCI_CAN_ID_INIT_EXPR(ID, isExt)    {.u.id=(ID),}
#endif 
 

/*
 * Local type definitions
 */

/** An enumeration gives meaningful names to the values of the linear, zero based frame
    index.
      @remark Normally, in a full scale integration of the CAN interface such an
    enumeration would probably be globally available, located and generated in the header
    file of another module, see the generation of callback code in the sample integrations
    of the CAN interface. In this sample we place it here as a local definition to make the
    sample code self-contained. From outside the index is only seen as integer number.\n
      Support of an integration of this module into a true environment is given by a
    preprocessor switch to turn off this local definition. */
#if MCI_ENUM_FRAMES_IS_DEFINED == 0
enum idxFrameInCanInterfaceEngine_t
{
    /* Received frames. */
    mci_idxFr_RT_simplified_rt_SB_INS_Vel_Body_Axes_mux_215,
    mci_idxFr_RT_simplified_RT_SB_INS_Vel_Body_Axes_9312034x,
    mci_idxFr_RT_simplified_RT_DL1MK3_Speed_8392740x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_Body_Axes_215,
    mci_idxFr_CAN_RT_attributed_RT_DL1MK3_GPS_Speed_1234,
    mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Final_Condition_9242402x,
    mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Initial_Condition_794,
    mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Direct_Dist_9241890x,
    mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Path_Dist_9241378x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Vel_NED_2_9384482x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Vel_NED_1_9384226x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Offset_9383970x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Vel_NED_2_9380386x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Vel_NED_1_9380130x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Offset_9379874x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Vel_NED_2_9376290x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Vel_NED_1_9376034x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Offset_9375778x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Vel_NED_2_9372194x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Vel_NED_1_9371938x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Offset_9371682x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Slip_9311778x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_ECEF_2_9311010x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_ECEF_1_9310754x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_NED_2_9310498x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_NED_1_9310242x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Pos_ECEF_2_9307426x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Pos_ECEF_1_9307170x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Pos_LLH_2_9306914x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Pos_LLH_1_9306658x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Heading_Gradient_2_9311522x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Heading_Gradient_9311266x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Status_9306146x,
    mci_idxFr_CAN_RT_attributed_RT_SB_INS_Attitude_9306402x,
    mci_idxFr_CAN_RT_attributed_RT_SB_Output_Status_9240866x,
    mci_idxFr_CAN_RT_attributed_RT_SB_Trigger_Timestamp_9240610x,
    mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_2_0,
    mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_1_536870911x,
    mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Speed_1818,
    mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Time_2047,
    mci_idxFr_CAN_RT_attributed_RT_SB_Accel_290,
    mci_idxFr_DUP_DRIVER_HEARTBEAT_100,
    mci_idxFr_DUP_IO_DEBUG_500,
    mci_idxFr_DUP_MOTOR_CMD_101,
    mci_idxFr_DUP_MOTOR_STATUS_400,
    mci_idxFr_DUP_SENSOR_SONARS_200,
    mci_idxFr_DUP_SENSOR_SONARS_1_200x,
    mci_idxFr_DUP_MOTOR_STATUS_1_0x,
    mci_idxFr_DUP_MOTOR_STATUS_2_0,

    /* Sent frames. */
    mci_idxFr_RT_simplified_RT_DL1MK3_GPS_Time_9175332x,
    mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Forward_Dist_9241634x,
    mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Accel_9241122x,
    mci_idxFr_DUP_ECU_STATUS_1_2047,
    mci_idxFr_DUP_ECU_STATUS_2_2047x,

    /* The number of frames indexes is used to recognize overflow of the 8 bit integers,
       which are partly used to reduce the table sizes. */
    mci_idxEdeFr_maxIdxFrame
};

/* An assertion double-checks that there aren't to many frames for the 8 Bit integer
   type, which is used for the direct lookup table in order to don't make it
   unnecessarily large and in the API. */
_Static_assert( (unsigned)mci_idxEdeFr_maxIdxFrame <= 254u
              , "Modelling of lookup tables as 8 Bit type failed due to the excessive"
                " number of CAN messages found in the DBC files"
              );
#endif 

/*
 * Local prototypes
 */

 

/*
 * Data definitions
 */

#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID != 0
/** The direct lookup table for 11 Bit standard CAN IDs. This table uses a byte as value in
    order to save ROM space. The lookup algorithm will use this table for all CAN IDs less
    or equal to 2047.\n
      The code generator fills those elements of the table, which belong to known
    associations. All other elements are implicitly initialized to 0. Since 0 is a valid
    frame index the unset elements cannot be distinguished from avlid fields. A lookup
    could not decide on an unknown CAN ID. Therefore, we do not store the aimed frame index
    but the index plus 1. Now 0 is a valid indication of a bad query. The successful lookup
    will subtract one from the found value in order to yield the true frame index. This is
    why we hide the table and only make the lookup function global.
      @remark The compiler will generate a message if there should be frames with index
    greater 254 and a standard CAN ID but this is a warning only. Bad code with table
    overflow can be compiler but will fail to work properly. */
const UInt8 mci_lookupTableFrameIdxByBusAndStdId[4][0x800] =
{
    [mci_idxBus_RT_simplified][0x0d7] = mci_idxFr_RT_simplified_rt_SB_INS_Vel_Body_Axes_mux_215+1,
    [mci_idxBus_CAN_RT_attributed][0x0d7] = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_Body_Axes_215+1,
    [mci_idxBus_CAN_RT_attributed][0x4d2] = mci_idxFr_CAN_RT_attributed_RT_DL1MK3_GPS_Speed_1234+1,
    [mci_idxBus_CAN_RT_attributed][0x31a] = mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Initial_Condition_794+1,
    [mci_idxBus_CAN_RT_attributed][0x000] = mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_2_0+1,
    [mci_idxBus_CAN_RT_attributed][0x71a] = mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Speed_1818+1,
    [mci_idxBus_CAN_RT_attributed][0x7ff] = mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Time_2047+1,
    [mci_idxBus_CAN_RT_attributed][0x122] = mci_idxFr_CAN_RT_attributed_RT_SB_Accel_290+1,
    [mci_idxBus_DUP][0x064] = mci_idxFr_DUP_DRIVER_HEARTBEAT_100+1,
    [mci_idxBus_DUP][0x1f4] = mci_idxFr_DUP_IO_DEBUG_500+1,
    [mci_idxBus_DUP][0x065] = mci_idxFr_DUP_MOTOR_CMD_101+1,
    [mci_idxBus_DUP][0x190] = mci_idxFr_DUP_MOTOR_STATUS_400+1,
    [mci_idxBus_DUP][0x0c8] = mci_idxFr_DUP_SENSOR_SONARS_200+1,
    [mci_idxBus_DUP][0x7ff] = mci_idxFr_DUP_ECU_STATUS_1_2047+1,
    [mci_idxBus_DUP][0x000] = mci_idxFr_DUP_MOTOR_STATUS_2_0+1,
};
#endif

#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0  ||  MCI_SUPPORT_EXTENDED_CAN_IDS != 0
/** One row of the two dimensional lookup table: The CAN ID to frame index associations for
    bus RT_simplified. */
static const mci_pairCanIdAndIdx_t _mapFrameIdxById_RT_simplified[] =
{
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0xd7, false), .idx = mci_idxFr_RT_simplified_rt_SB_INS_Vel_Body_Axes_mux_215},
    #endif
    {.canId = MCI_CAN_ID_INIT_EXPR(0x801024, true), .idx = mci_idxFr_RT_simplified_RT_DL1MK3_Speed_8392740x},
    #if MCI_USE_MAP_FOR_SENT_FRAMES != 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8c0124, true), .idx = mci_idxFr_RT_simplified_RT_DL1MK3_GPS_Time_9175332x},
    #endif
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e1722, true), .idx = mci_idxFr_RT_simplified_RT_SB_INS_Vel_Body_Axes_9312034x},
};

/** One row of the two dimensional lookup table: The CAN ID to frame index associations for
    bus CAN_RT_attributed. */
static const mci_pairCanIdAndIdx_t _mapFrameIdxById_CAN_RT_attributed[] =
{
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x0, false), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_2_0},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0xd7, false), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_Body_Axes_215},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x122, false), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_Accel_290},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x31a, false), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Initial_Condition_794},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x4d2, false), .idx = mci_idxFr_CAN_RT_attributed_RT_DL1MK3_GPS_Speed_1234},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x71a, false), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Speed_1818},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x7ff, false), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Time_2047},
    #endif
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8d0022, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_Trigger_Timestamp_9240610x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8d0122, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_Output_Status_9240866x},
    #if MCI_USE_MAP_FOR_SENT_FRAMES != 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8d0222, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Accel_9241122x},
    #endif
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8d0322, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Path_Dist_9241378x},
    #if MCI_USE_MAP_FOR_SENT_FRAMES != 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8d0422, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Forward_Dist_9241634x},
    #endif
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8d0522, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Direct_Dist_9241890x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8d0722, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_Trig_Final_Condition_9242402x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e0022, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Status_9306146x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e0122, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Attitude_9306402x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e0222, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Pos_LLH_1_9306658x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e0322, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Pos_LLH_2_9306914x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e0422, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Pos_ECEF_1_9307170x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e0522, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Pos_ECEF_2_9307426x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e1022, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_NED_1_9310242x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e1122, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_NED_2_9310498x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e1222, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_ECEF_1_9310754x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e1322, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vel_ECEF_2_9311010x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e1422, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Heading_Gradient_9311266x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e1522, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Heading_Gradient_2_9311522x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8e1622, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Slip_9311778x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f0022, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Offset_9371682x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f0122, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Vel_NED_1_9371938x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f0222, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Vel_NED_2_9372194x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f1022, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Offset_9375778x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f1122, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Vel_NED_1_9376034x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f1222, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Vel_NED_2_9376290x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f2022, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Offset_9379874x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f2122, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Vel_NED_1_9380130x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f2222, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Vel_NED_2_9380386x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f3022, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Offset_9383970x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f3122, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Vel_NED_1_9384226x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x8f3222, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Vel_NED_2_9384482x},
    {.canId = MCI_CAN_ID_INIT_EXPR(0x1fffffff, true), .idx = mci_idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_1_536870911x},
};

/** One row of the two dimensional lookup table: The CAN ID to frame index associations for
    bus DUP. */
static const mci_pairCanIdAndIdx_t _mapFrameIdxById_DUP[] =
{
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x0, false), .idx = mci_idxFr_DUP_MOTOR_STATUS_2_0},
    #endif
    {.canId = MCI_CAN_ID_INIT_EXPR(0x0, true), .idx = mci_idxFr_DUP_MOTOR_STATUS_1_0x},
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x64, false), .idx = mci_idxFr_DUP_DRIVER_HEARTBEAT_100},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x65, false), .idx = mci_idxFr_DUP_MOTOR_CMD_101},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0xc8, false), .idx = mci_idxFr_DUP_SENSOR_SONARS_200},
    #endif
    {.canId = MCI_CAN_ID_INIT_EXPR(0xc8, true), .idx = mci_idxFr_DUP_SENSOR_SONARS_1_200x},
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x190, false), .idx = mci_idxFr_DUP_MOTOR_STATUS_400},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x1f4, false), .idx = mci_idxFr_DUP_IO_DEBUG_500},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    #if MCI_USE_MAP_FOR_SENT_FRAMES != 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x7ff, false), .idx = mci_idxFr_DUP_ECU_STATUS_1_2047},
    #endif
    #endif
    #if MCI_USE_MAP_FOR_SENT_FRAMES != 0
    {.canId = MCI_CAN_ID_INIT_EXPR(0x7ff, true), .idx = mci_idxFr_DUP_ECU_STATUS_2_2047x},
    #endif
};

/** One row of the two dimensional lookup table: The CAN ID to frame index associations for
    bus CAN_RT. */
static const mci_pairCanIdAndIdx_t _mapFrameIdxById_CAN_RT[] =
{
};


/** A two dimensional lookup table to get the frame index from the pair (bus, CAN ID).
    First, the right row is selected by the bus index. Then a binary search can be
    applied to the row data as it is sorted in order of raising CAN IDs. */
const mci_pairCanIdAndIdx_t * const mci_mapFrameIdxByBusAndId[4] =
{
    &_mapFrameIdxById_RT_simplified[0],
    &_mapFrameIdxById_CAN_RT_attributed[0],
    &_mapFrameIdxById_DUP[0],
    &_mapFrameIdxById_CAN_RT[0],
};

/** The number of entries of the rows of the two dimensional map mci_mapFrameIdxByBusAndId.
    The bus index is used as index. The number of row elements is required to initialize
    the binary search for the CAN ID in the bus related row of the map. */
const unsigned int mci_mapFrameIdxByBusAndId_rowLengthAry[4] =
{
    sizeof(_mapFrameIdxById_RT_simplified)/sizeof(_mapFrameIdxById_RT_simplified[0]),
    sizeof(_mapFrameIdxById_CAN_RT_attributed)/sizeof(_mapFrameIdxById_CAN_RT_attributed[0]),
    sizeof(_mapFrameIdxById_DUP)/sizeof(_mapFrameIdxById_DUP[0]),
    sizeof(_mapFrameIdxById_CAN_RT)/sizeof(_mapFrameIdxById_CAN_RT[0]),
};
#endif /* Two dimensional lookup table required? */
 

/*
 * Function implementation
 */


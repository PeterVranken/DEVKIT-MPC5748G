/**
 * @file mci_mapCanIdToFrameIdx.c
 * 
 * A standard use case of sorted frame iteration is the implementation of a mapping table
 * to map the pair CAN bus index plus CAN frame ID (as occasionally used as frame
 * identification in the CAN callback in some platforms) to the null based linear frame
 * index as used by the CAN interface engine. If we sort the tables in raising order of CAN
 * IDs and separated by buses then an efficient binary search can be applied.\n
 *   As an optimization for (typical) platform, which offer a lot of ROM space but limited
 * CPU power and very limited RAM space, we can further optimize the mapping by separating
 * standard CAN IDs, which are mostly used, for the rarely used extended CAN identifiers.
 * The former span a numeric range of 2048 values, which permits to have a direct lookup
 * table with complexity O(1). Only the few N extended identifiers need a binary search with
 * a complexity O(log(N)).\n
 *   The simplest way to relate the table entries to registered frames is to use the position
 * in the table as index of the frame in the interface engine. This requires that frame
 * registration in our CAN interface is done in the same iteration of frames. It's also
 * possible to have an enumeration of frames and to generate the enumeration in the same
 * iteration as the registration process. This is less ROM efficient but much more
 * transparent. This is what we demonstrate here.\n
 *   Please note, the usual way of doing is to let the code generator produce only the data
 * dependent code (i.e. dependent on the network databases). Consequently, you will not
 * find the algorithms to use the generated tables, particularly the binary search. This is
 * one-time code and such code should not be developed and maintained through a template.
 * Write this code directly as plain C file.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "mci_mapCanIdToFrameIdx.h"


/*
 * Defines
 */

 

/*
 * Local type definitions
 */

/** An enumeration gives meaningful names to the values of the linear, null based frame
    index.
      @remark Normally, in a full scale integration of the CAN interface such an
    enumeration would probably be globally available, located and generated in the header
    file of another module, see the generation of callback code in the sample integrations
    of the CAN interface. In this sample we place it here as a local definition to make the
    sample code self-contained. From outside the index is only seen as integer number.
      @remark This enumeration is needed for technical reasons not only to improve the
    readability of the code: A StringTemplate V4 template can't do numerical operations and
    particularly it can't generate number sequences like 0, 1, 2, 3 ... By generating an
    enumeration we do exactly this but on text not on number basis. */
typedef enum idxFrameInCanInterfaceEngine_t
{
    idxFr_RT_simplified_Rt_SB_INS_Vel_Body_Axes_mux_0d7,
    idxFr_RT_simplified_RT_SB_INS_Vel_Body_Axes_8e1722,
    idxFr_RT_simplified_RT_DL1MK3_Speed_801024,
    idxFr_RT_simplified_RT_DL1MK3_GPS_Time_8c0124,
    idxFr_RT_simplified_RT_DL1MK3_Measure_Time_10_960a24,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vel_Body_Axes_0d7,
    idxFr_CAN_RT_attributed_RT_DL1MK3_GPS_Speed_4d2,
    idxFr_CAN_RT_attributed_RT_SB_Trig_Final_Condition_8d0722,
    idxFr_CAN_RT_attributed_RT_SB_Trig_Initial_Condition_31a,
    idxFr_CAN_RT_attributed_RT_SB_Trig_Direct_Dist_8d0522,
    idxFr_CAN_RT_attributed_RT_SB_Trig_Forward_Dist_8d0422,
    idxFr_CAN_RT_attributed_RT_SB_Trig_Path_Dist_8d0322,
    idxFr_CAN_RT_attributed_RT_SB_Trig_Accel_8d0222,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Vel_NED_2_8f3222,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Vel_NED_1_8f3122,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Offset_8f3022,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Vel_NED_2_8f2222,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Vel_NED_1_8f2122,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Offset_8f2022,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Vel_NED_2_8f1222,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Vel_NED_1_8f1122,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Offset_8f1022,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Vel_NED_2_8f0222,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Vel_NED_1_8f0122,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Offset_8f0022,
    idxFr_CAN_RT_attributed_RT_SB_INS_Slip_8e1622,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vel_ECEF_2_8e1322,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vel_ECEF_1_8e1222,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vel_NED_2_8e1122,
    idxFr_CAN_RT_attributed_RT_SB_INS_Vel_NED_1_8e1022,
    idxFr_CAN_RT_attributed_RT_SB_INS_Pos_ECEF_2_8e0522,
    idxFr_CAN_RT_attributed_RT_SB_INS_Pos_ECEF_1_8e0422,
    idxFr_CAN_RT_attributed_RT_SB_INS_Pos_LLH_2_8e0322,
    idxFr_CAN_RT_attributed_RT_SB_INS_Pos_LLH_1_8e0222,
    idxFr_CAN_RT_attributed_RT_SB_INS_Heading_Gradient_2_8e1522,
    idxFr_CAN_RT_attributed_RT_SB_INS_Heading_Gradient_8e1422,
    idxFr_CAN_RT_attributed_RT_SB_INS_Status_8e0022,
    idxFr_CAN_RT_attributed_RT_SB_INS_Attitude_8e0122,
    idxFr_CAN_RT_attributed_RT_SB_Output_Status_8d0122,
    idxFr_CAN_RT_attributed_RT_SB_Trigger_Timestamp_8d0022,
    idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_2_000,
    idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_1_1fffffff,
    idxFr_CAN_RT_attributed_RT_SB_GPS_Speed_71a,
    idxFr_CAN_RT_attributed_RT_SB_GPS_Time_7ff,
    idxFr_CAN_RT_attributed_RT_SB_Accel_122,

    /* The number of frames indexes is used to recognize overflow of the 8 bit integers,
       which are partly used to reduce the table sizes. */
    idxFr_maxIdxFrame

} idxFrameInCanInterfaceEngine_t; 

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
static const UInt8 _lookupTableFrameIdxByBusAndStdId[3][0x800] =
{
    [mci_idxBus_RT_simplified][0x0d7] = idxFr_RT_simplified_Rt_SB_INS_Vel_Body_Axes_mux_0d7+1,
    [mci_idxBus_CAN_RT_attributed][0x0d7] = idxFr_CAN_RT_attributed_RT_SB_INS_Vel_Body_Axes_0d7+1,
    [mci_idxBus_CAN_RT_attributed][0x4d2] = idxFr_CAN_RT_attributed_RT_DL1MK3_GPS_Speed_4d2+1,
    [mci_idxBus_CAN_RT_attributed][0x31a] = idxFr_CAN_RT_attributed_RT_SB_Trig_Initial_Condition_31a+1,
    [mci_idxBus_CAN_RT_attributed][0x000] = idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_2_000+1,
    [mci_idxBus_CAN_RT_attributed][0x71a] = idxFr_CAN_RT_attributed_RT_SB_GPS_Speed_71a+1,
    [mci_idxBus_CAN_RT_attributed][0x7ff] = idxFr_CAN_RT_attributed_RT_SB_GPS_Time_7ff+1,
    [mci_idxBus_CAN_RT_attributed][0x122] = idxFr_CAN_RT_attributed_RT_SB_Accel_122+1,
};
#endif

#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0  ||  MCI_SUPPORT_EXTENDED_CAN_IDS != 0
/** One row of the two dimensional lookup table: The CAN ID to frame index associations for
    bus RT_simplified. */
const mci_pairIdAndIdx_t mapFrameIdxById_RT_simplified[] =
{
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.id = 0xd7, .idx = idxFr_RT_simplified_Rt_SB_INS_Vel_Body_Axes_mux_0d7},
    #endif
    {.id = 0x801024, .idx = idxFr_RT_simplified_RT_DL1MK3_Speed_801024},
    {.id = 0x8c0124, .idx = idxFr_RT_simplified_RT_DL1MK3_GPS_Time_8c0124},
    {.id = 0x8e1722, .idx = idxFr_RT_simplified_RT_SB_INS_Vel_Body_Axes_8e1722},
    {.id = 0x960a24, .idx = idxFr_RT_simplified_RT_DL1MK3_Measure_Time_10_960a24},
};

/** One row of the two dimensional lookup table: The CAN ID to frame index associations for
    bus CAN_RT_attributed. */
const mci_pairIdAndIdx_t mapFrameIdxById_CAN_RT_attributed[] =
{
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.id = 0x0, .idx = idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_2_000},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.id = 0xd7, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vel_Body_Axes_0d7},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.id = 0x122, .idx = idxFr_CAN_RT_attributed_RT_SB_Accel_122},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.id = 0x31a, .idx = idxFr_CAN_RT_attributed_RT_SB_Trig_Initial_Condition_31a},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.id = 0x4d2, .idx = idxFr_CAN_RT_attributed_RT_DL1MK3_GPS_Speed_4d2},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.id = 0x71a, .idx = idxFr_CAN_RT_attributed_RT_SB_GPS_Speed_71a},
    #endif
    #if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0
    {.id = 0x7ff, .idx = idxFr_CAN_RT_attributed_RT_SB_GPS_Time_7ff},
    #endif
    {.id = 0x8d0022, .idx = idxFr_CAN_RT_attributed_RT_SB_Trigger_Timestamp_8d0022},
    {.id = 0x8d0122, .idx = idxFr_CAN_RT_attributed_RT_SB_Output_Status_8d0122},
    {.id = 0x8d0222, .idx = idxFr_CAN_RT_attributed_RT_SB_Trig_Accel_8d0222},
    {.id = 0x8d0322, .idx = idxFr_CAN_RT_attributed_RT_SB_Trig_Path_Dist_8d0322},
    {.id = 0x8d0422, .idx = idxFr_CAN_RT_attributed_RT_SB_Trig_Forward_Dist_8d0422},
    {.id = 0x8d0522, .idx = idxFr_CAN_RT_attributed_RT_SB_Trig_Direct_Dist_8d0522},
    {.id = 0x8d0722, .idx = idxFr_CAN_RT_attributed_RT_SB_Trig_Final_Condition_8d0722},
    {.id = 0x8e0022, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Status_8e0022},
    {.id = 0x8e0122, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Attitude_8e0122},
    {.id = 0x8e0222, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Pos_LLH_1_8e0222},
    {.id = 0x8e0322, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Pos_LLH_2_8e0322},
    {.id = 0x8e0422, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Pos_ECEF_1_8e0422},
    {.id = 0x8e0522, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Pos_ECEF_2_8e0522},
    {.id = 0x8e1022, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vel_NED_1_8e1022},
    {.id = 0x8e1122, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vel_NED_2_8e1122},
    {.id = 0x8e1222, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vel_ECEF_1_8e1222},
    {.id = 0x8e1322, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vel_ECEF_2_8e1322},
    {.id = 0x8e1422, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Heading_Gradient_8e1422},
    {.id = 0x8e1522, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Heading_Gradient_2_8e1522},
    {.id = 0x8e1622, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Slip_8e1622},
    {.id = 0x8f0022, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Offset_8f0022},
    {.id = 0x8f0122, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Vel_NED_1_8f0122},
    {.id = 0x8f0222, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_1_Vel_NED_2_8f0222},
    {.id = 0x8f1022, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Offset_8f1022},
    {.id = 0x8f1122, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Vel_NED_1_8f1122},
    {.id = 0x8f1222, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_2_Vel_NED_2_8f1222},
    {.id = 0x8f2022, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Offset_8f2022},
    {.id = 0x8f2122, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Vel_NED_1_8f2122},
    {.id = 0x8f2222, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_3_Vel_NED_2_8f2222},
    {.id = 0x8f3022, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Offset_8f3022},
    {.id = 0x8f3122, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Vel_NED_1_8f3122},
    {.id = 0x8f3222, .idx = idxFr_CAN_RT_attributed_RT_SB_INS_Vpt_4_Vel_NED_2_8f3222},
    {.id = 0x1fffffff, .idx = idxFr_CAN_RT_attributed_RT_SB_GPS_Vel_NED_1_1fffffff},
};

/** One row of the two dimensional lookup table: The CAN ID to frame index associations for
    bus CAN_RT. */
const mci_pairIdAndIdx_t mapFrameIdxById_CAN_RT[] =
{
};


/** A two dimensional lookup table to get the frame index from the pair (bus, CAN ID).
    First, the right row is selected by the bus index. Then a binary search can be
    applied to the row data as it is sorted in order of raising CAN IDs. */
const mci_pairIdAndIdx_t * const mci_mapFrameIdxByBusAndId[3] =
{
    &mapFrameIdxById_RT_simplified[0],
    &mapFrameIdxById_CAN_RT_attributed[0],
    &mapFrameIdxById_CAN_RT[0],
};

/** The number of entries of the rows of the two dimensional map mci_mapFrameIdxByBusAndId.
    The bus index is used as index. The number of row elements is required to initialize
    the binary search for the CAN ID in the bus related row of the map. */
const size_t mci_mapFrameIdxByBusAndId_rowLengthAry[3] =
{
    sizeof(mapFrameIdxById_RT_simplified)/sizeof(mapFrameIdxById_RT_simplified[0]),
    sizeof(mapFrameIdxById_CAN_RT_attributed)/sizeof(mapFrameIdxById_CAN_RT_attributed[0]),
    sizeof(mapFrameIdxById_CAN_RT)/sizeof(mapFrameIdxById_CAN_RT[0]),
};
#endif /* Two dimensional lookup table required? */
 

/*
 * Function implementation
 */

#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID != 0
/**
 * Get the frame index as used by the CAN interface engine from the pair of CAN bus and
 * CAN standard ID. This function is restricted\n
 *   @return
 * The frame index is returned. If the pair of bus and CAN id does not designate a frame,
 * which had been registered in the CAN interface engine, thus a frame, which can't be
 * processed by the engine, then (UInt8)-1 or 255 is returned instead of a valid index.
 *   @param idxBus
 * The index of the bus. Please see enum mci_idxCanBus_t for details.
 *   @param canId
 * The CAN ID, which needs to be an 11 Bit standard ID. Extended IDs can't be handled by
 * this function. This is double-checked by assertion.
 *   @remark
 * The frame index is returned as UInt8. If more than 254 CAN frames should be in use
 * then the implemented table will not fit and the lookup function would fail. In this case
 * the code generation needs (simple) reconfiguration and the ROM consumption of the table
 * will be doubled.
 */
UInt8 mci_getFrameIdxByCanBusAndStdId(UInt8 idxBus, UInt16 canId)
{
    assert(idxBus < 3  &&  canId < 0x800);

    /* An assertion double-checks that there aren't to many frame for the 8 Bit integer
       type, which is used for the direct lookup table in order to don't make it
       unnecessarily large. This is not fully satisfactory: Firstly, the test should be
       made only once and not in every call of this function. If we had a piece of once
       executed module initialization code then we would place the check there. Secondary,
       the condition is too strict. The true condition is that there must be no frame with
       standard CAN ID and index larger than 254. There may however be frames with larger
       index if they only have an extended IDs.
         The best way out would be to let the code-generator make a #define with the number
       of frames and a preprocessor compile time check. This has been demonstrated in
       another sample, see raceTechnology, cst_canStatistics.h.stg. */
    assert(idxFr_maxIdxFrame <= 254);

    /* The fields of the table hold 0 for unset pairs and the CAN ID plus one otherwise. We
       just have to subtract one to handled registered and unregistered pairs of bus index
       and CAN ID. */
    return (UInt8)(_lookupTableFrameIdxByBusAndStdId[idxBus][canId] - 1);

} /* End of mci_getFrameIdxByCanBusAndStdId */
#endif

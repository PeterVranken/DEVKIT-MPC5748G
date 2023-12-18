#ifndef MCI_MAPCANIDTOIDX_DATATABLES_DEFINED
#define MCI_MAPCANIDTOIDX_DATATABLES_DEFINED
/**
 * @file mci_mapCanIdToIdx_dataTables.h
 * 
 * Public data interface of the mapping table, which associates the pair CAN bus index plus
 * CAN message ID (as occasionally used as message identification in the CAN callback in some
 * platforms) to the zero based linear message index as used by the CAN interface engine.\n
 *   This interface does not contain the lookup algorithm; this is data independent program
 * code, which doesn't belong into an auto-generated module. It's however straightforward
 * to implement the function that operates on the generated data tables.
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

#include "types.h"


/*
 * Defines
 */

/** The code can either use the map for all CAN IDs or a mixture of a direct lookup table
    for the limited range of standard CAN IDs and a map for the extended CAN IDs. If the
    direct lookup table is used then the lookup is much faster for standard IDs on cost of
    higher ROM consumption: Now a table of the fixed size 2048*<numberOfCanBuses> Byte is
    placed in ROM.\n
      The macro can be set to either 0 or 1. */
#ifndef MCI_USE_DIRECT_LOOKUP_FOR_STD_ID
# define MCI_USE_DIRECT_LOOKUP_FOR_STD_ID   1
#endif

/** Most true environments will require the map for received CAN messages only. However, if
    a platform provides a send acknowledge with CAN ID as message handle then this macro
    can be set to 1 and the sent messages are considered in the map, too.\n
      The macro can be set to either 0 or 1. */
#ifndef MCI_USE_MAP_FOR_SENT_FRAMES
# define MCI_USE_MAP_FOR_SENT_FRAMES        0
#endif

/** If the map is integrated into a true project then the enumeration of CAN messages is
    likely defined externally and we won't use the definition made locally in this file.
    Set the value to 0 in this case.
      The macro can be set to either 0 or 1. */
#ifndef MCI_ENUM_FRAMES_IS_DEFINED
# define MCI_ENUM_FRAMES_IS_DEFINED         0
#endif

/** This define controls whether code for the support of extended CAN identifiers is
    required or not. The value of this define depends on the actual data found in the
    network databases and must not be changed. */
#ifndef MCI_SUPPORT_EXTENDED_CAN_IDS
# define MCI_SUPPORT_EXTENDED_CAN_IDS       1
#endif

/* The next include requires the defintion of #MCI_SUPPORT_EXTENDED_CAN_IDS and can be made
   only now. */
#include "mci_ifMapBinarySearchCanId.h"
 

/*
 * Type definitions
 */

/** An enumeration gives meaningful names to the different CAN buses, which are addressed
    by a linear, zero based index. The named values defined here can be used as index into
    the generated tables (or as argument of a generated function) anywhere, where a bus
    index is expected.
      @remark Normally, in a full scale integration of the CAN interface such an
    enumeration would probably be not generated here as already defined by the Basic
    Software provider (be it as enum or as series of \#define's. In which case it has to be
    ensured that the indexes are compatible. From code generation side this is controlled
    by the parsing order of network database files, i.e., by the command line of the code
    generator. Additionally, one should generate some preprocessor or assert statements,
    which actively double-check the identity of indexes. */
typedef enum mci_idxCanBus_t
{
    mci_idxBus_RT_simplified,
    mci_idxBus_CAN_RT_attributed,
    mci_idxBus_DUP,
    mci_idxBus_CAN_RT,

    mci_noBuses

} mci_idxCanBus_t;

 

/*
 * Data declarations
 */

#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID != 0
/** A two dimensional lookup table only for standard CAN IDs to get the message index from
    the pair (bus, 11 Bit CAN ID). The first array index selects the bus by zero based bus
    index. The 11 Bit CAN ID is then used as second array index to get the wanted message
    index. */
extern const uint8_t mci_lookupTableFrameIdxByBusAndStdId[4][0x800];
#endif

#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0  ||  MCI_SUPPORT_EXTENDED_CAN_IDS != 0
/** A two dimensional map to get the message index from the pair (bus, CAN ID). First, the
    right row is selected by the bus index. Then a binary search can be applied to the row
    data as it is sorted in order of raising CAN IDs. */
extern const mci_pairCanIdAndIdx_t * const mci_mapFrameIdxByBusAndId[4];


/** The number of entries of the rows of the two dimensional map mci_mapFrameIdxByBusAndId.
    The bus index is used as index. The number of row elements is required to initialize
    the binary search for the CAN ID in the bus related row of the map. */
extern const unsigned int mci_mapFrameIdxByBusAndId_rowLengthAry[4];
#endif
 

/*
 * Function declarations
 */

#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID != 0
/** Get the message index as used by the CAN interface engine from the pair of CAN bus and
    CAN standard ID. */
uint8_t mci_getFrameIdxByCanBusAndStdId(uint8_t idxBus, uint16_t canId);
#endif


/*
 * Inline function definitions
 */

#endif // !defined(MCI_MAPCANIDTOIDX_DATATABLES_DEFINED)

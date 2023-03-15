#ifndef MCI_IF_MAP_BINARY_SEARCH_CAN_ID_DEFINED
#define MCI_IF_MAP_BINARY_SEARCH_CAN_ID_DEFINED
/**
 * @file mci_ifMapBinarySearchCanId.h
 * 
 * Interface definition of the data tables, which are used by the map. This interface
 * definition is required by the auto-generated data tables and by the hand-coded lookup
 * algorithms. This file is hand-coded.
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

#include <stdint.h>


/*
 * Defines
 */

/** The definitions below depend on whether or not extended CAN IDs are in use. This needs
    to be decided before this header is included. Set #MCI_SUPPORT_EXTENDED_CAN_IDS to 0 or
    1 prior to including this file. */
#ifndef MCI_SUPPORT_EXTENDED_CAN_IDS
# error MCI_SUPPORT_EXTENDED_CAN_IDS needs to be defined when including this file
#endif

#if MCI_SUPPORT_EXTENDED_CAN_IDS == 1

/** Helper to get CAN IDs: Get a 11 Bit standard CAN ID object from the raw number. */
# define MCI_STD_CAN_ID(id11Bit)        ((mci_canId_t)(((unsigned)(id11Bit)&0x7FFu)<<1u))

/** Helper to get CAN IDs: Get a 29 Bit standard CAN ID object from the raw number. */
# define MCI_EXT_CAN_ID(id29Bit) \
                            ((mci_canId_t)((((unsigned)(id29Bit)&0x1FFFFFFFu)<<1u)|1u))

/** Helper to get CAN IDs: Get CAN ID object from raw number and Boolean \a isExt. */
# define MCI_CAN_ID(ID, isExt) \
                        ((mci_canId_t)((((unsigned)(ID)&0x1FFFFFFFu)<<1u)|((isExt)?1u:0u)))

/** Helper to get the CAN ID as a number from a CAN ID object. */
# define MCI_GET_CAN_ID(mci_canId)      ((mci_canId) >> 1u)

/** Helper to get the Boolean distinction between standard and extended CAN ID from a CAN
    ID object. */
# define MCI_GET_IS_EXT_ID(mci_canId)   (((mci_canId) & 1u) == 1u)

#else

/** Helper to get CAN IDs: Get a 11 Bit standard CAN ID object from the raw number. */
# define MCI_STD_CAN_ID(id11Bit)        ((mci_canId_t)((unsigned)(id11Bit)&0x7FFu))

/** Helper to get CAN IDs: Get CAN ID object from raw number and Boolean \a isExt. */
# define MCI_CAN_ID(ID, isExt)          (assert(!isExt),((mci_canId_t)((unsigned)(id11Bit)&0x7FFu)))

/** Helper to get the CAN ID as a number from a CAN ID object. */
# define MCI_GET_CAN_ID(mci_canId)      (mci_canId)

/** Helper to get the Boolean distinction between standard and extended CAN ID from a CAN
    ID object. */
# define MCI_GET_IS_EXT_ID(mci_canId)   false

#endif 


/*
 * Type definitions
 */

/** The map value type. Normally, an 8 Bit unsigned will be appropriate but if more than
    254 CAN messages are defined in at least one involved event dispatcher system then this
    type would overflow and a uint16_t becomes the better choice. */
typedef uint8_t mci_uintMapValue_t;

#if MCI_SUPPORT_EXTENDED_CAN_IDS == 1
/** CAN ID: The number and the Boolean distinction between standard 11 and extended 29 Bit
    IDs.\n
      The Boolean "isExtendedID" is encoded as bit 0.\n
      The ID as number is encoded as bits 1..31. Unused bits need to be set to zero; for
    standard IDs all bits 12..31 are always zero and for extended IDs the bits 30 and 31 are
    always zero. */
typedef uint32_t mci_canId_t;
#else
/** CAN ID: A standard 11 Bit represented as a 16 Bit unsigned integer. The bits 11..15 are
    always zero. */
typedef uint16_t mci_canId_t;
#endif

/** Map entry: Makes the association from CAN ID to frame index. We just need to find the
    CAN ID by binary search to have the frame index. */
typedef struct mci_pairCanIdAndIdx_t
{
    /** The CAN ID. */
    mci_canId_t canId;

    /** The frame index in the CAN interface engine. */
    mci_uintMapValue_t idx;

} mci_pairCanIdAndIdx_t;

 

/*
 * Data declarations
 */


/*
 * Function declarations
 */


/*
 * Inline function definitions
 */

#endif // !defined(MCI_IF_MAP_BINARY_SEARCH_CAN_ID_DEFINED)

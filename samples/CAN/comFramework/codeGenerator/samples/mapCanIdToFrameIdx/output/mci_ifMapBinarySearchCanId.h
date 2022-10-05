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

/* The software is written as portable as reasonably possible. This requires the awareness
   of the C language standard it is compiled with.
     With respect to the language feature C11 and C17 are identical. We combine the in one
   switch. */
#if defined(__STDC_VERSION__)
# if (__STDC_VERSION__)/100 == 2017
#  define _STDC_VERSION_C17
#  define _STDC_VERSION_C17_C11
# elif (__STDC_VERSION__)/100 == 2011
#  define _STDC_VERSION_C11
#  define _STDC_VERSION_C17_C11
# elif (__STDC_VERSION__)/100 == 1999
#  define _STDC_VERSION_C99
# endif
#endif

/** The definitions below depend on whether or not extended CAN IDs are in use. This needs
    to be decided before this header is included. Set #MCI_SUPPORT_EXTENDED_CAN_IDS to 0 or
    1 prior to including this file. */
#ifndef MCI_SUPPORT_EXTENDED_CAN_IDS
# error MCI_SUPPORT_EXTENDED_CAN_IDS needs to be defined when including this file
#endif

/*
 * Type definitions
 */

/** The map value type. Normally, a uint8 will be appropriate but if more than 254 CAN
    messages are defined in at least one involved event dispatcher system then this type
    would overflow and a unit16_t becomes the better choice. */
typedef uint8_t mci_uintMapValue_t;

/** CAN ID: The number and the Boolean distinction between standard 11 and extended 29 Bit
    IDs. */
typedef union mci_canId_t
{
#if MCI_SUPPORT_EXTENDED_CAN_IDS == 1
    /** A struct provides the normally used access to the fields. */
    struct
    {
        /** The Boolean distinction, whether we have an 11 or a 29 Bit CAN ID. */
        uint32_t isExtId:1;

        /** The CAN ID.\n
              Note, this field is intentionally not modelled as 29 Bit integer in order to
            avoid undefined values for unused bit: This supports efficient binary
            comparison of CAN IDs. */
        uint32_t id:31;
        
    } u;

    /** An alternative 32 Bit integer access supports efficient CAN ID comparisons (equal
        or not). */
    uint32_t uniqueCanId;
#else
    uint16_t id;
    uint16_t uniqueCanId;
#endif

} mci_canId_t;

#if defined(_STDC_VERSION_C17_C11) || defined(_Static_assert)
# if MCI_SUPPORT_EXTENDED_CAN_IDS == 1
_Static_assert(sizeof(union mci_canId_t) == sizeof(uint32_t), "Unexpected size of data object");
# else
_Static_assert(sizeof(mci_canId_t) == sizeof(uint16_t), "Unexpected size of data object");
# endif
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

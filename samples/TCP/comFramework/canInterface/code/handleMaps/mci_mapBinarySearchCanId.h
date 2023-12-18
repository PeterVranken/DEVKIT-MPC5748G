#ifndef MCI_MAPBINARYSEARCHCANID_INCLUDED
#define MCI_MAPBINARYSEARCHCANID_INCLUDED
/**
 * @file mci_mapBinarySearchCanId.h
 * Definition of global interface of module mci_mapBinarySearchCanId.c
 *
 * Copyright (C) 2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <stdbool.h>

#include "ede_externalInterfaces.h"

#define MCI_SUPPORT_EXTENDED_CAN_IDS 1
#include "mci_ifMapBinarySearchCanId.h"


/*
 * Defines
 */


/*
 * Global type definitions
 */

/** Specification of one kind-of-event instance of the binary search handle map. Used
    (only) for creation of the map object using mci_createMapBinarySearchCanId(). */
typedef struct mci_specMapInstance_t
{   
    /** Does the given kind-of-event require binary search of a CAN ID or is simple mapping
        sufficient? If \a doBinarySearchMapping is \a false then all other fields are
        meaningless and should be set to NULL or 0. */
    bool doBinarySearchMapping;
   
    /** The lookup table for standard CAN IDs by reference or NULL if all CAN IDs are
        handled via binary search. Index into the table is the 11 Bit CAN ID, so it has
        2048 entries. Array entry is the associated zero based index of the message in the
        event dispatcher system. */
    const mci_uintMapValue_t *mapStdCanIdToEdeIdxAry;

    /** The lookup table for extended CAN IDs by reference (and for standard IDs, too, if
        \a mapStdCanIdToEdeIdxAry is NULL), or NULL if the map instance is of kind "simple
        mapping". */
    const mci_pairCanIdAndIdx_t *mapExtCanIdToEdeIdxAry;

    /** For non-simple mapping: The number of entries in lookup table \a
        mapExtCanIdToEdeIdxAry. */
    unsigned int noExtCanIds;

} mci_specMapInstance_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Create a new map object for binary search of CAN IDs. */
bool mci_createMapBinarySearchCanId( ede_mapSenderEvHandleToIdx_t * const pNewMap
                                   , unsigned int noKindsOfEv
                                   , const mci_specMapInstance_t specInstanceAry[]
                                   , ede_memoryPool_t * const pMemPool
                                   );


/*
 * Global inline functions
 */


#endif  /* MCI_MAPBINARYSEARCHCANID_INCLUDED */

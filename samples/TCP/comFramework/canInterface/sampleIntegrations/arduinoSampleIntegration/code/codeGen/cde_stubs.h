#ifndef CDE_STUBS_INCLUDED
#define CDE_STUBS_INCLUDED
/**
 * @file cde_stubs.h
 * Definition of global interface of module cde_stubs.c
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

#include <stdint.h>
//#include <stdbool.h>
#include "ede_eventDispatcherEngine.h"

/*
 * Defines
 */

/** Helper to get CAN IDs: Get a 11 Bit standard CAN ID object from the raw number. */
#define CDE_STD_CAN_ID(id11Bit)         ((cde_canId_t){.isExtId=0, .id=(id11Bit)})

/** Helper to get CAN IDs: Get a 29 Bit standard CAN ID object from the raw number. */
#define CDE_EXT_CAN_ID(id29Bit)         ((cde_canId_t){.isExtId=1, .id=(id29Bit)})

/** Helper to get CAN IDs: Get CAN ID object from raw number and Boolean \a isExt. */
#define CDE_CAN_ID(ID, isExt)           ((cde_canId_t){.isExtId=(isExt), .id=(ID)})


/*
 * Global type definitions
 */

/** CAN ID: The number and the Boolean distinction between 11 and 29 Bit ID. */
typedef union cde_canId_t
{
    /** An anonymous struct provides the normally used access to the fields. */
    struct
    {
        /** The CAN ID.\n
              Note, this field is intentionally not modelled as 29 Bit integer in order to
            avoid undefined values for unused bit: This supports efficient binary
            comparison of CAN IDs. */
        unsigned long id:31;

        /** The Boolean distinction, whether we have an 11 or a 29 Bit CAN ID. */
        unsigned long isExtId:1;
    };
    
    /** An alternative 32 Bit integer access supports efficient CAN ID comparisons (equal
        or not). */
    unsigned long uniqueCanId:32;

} cde_canId_t;

_Static_assert(sizeof(cde_canId_t) == sizeof(uint32_t), "Unexpected size of data object");


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Get the CAN ID of the related frame from a callback */
cde_canId_t cde_getCanId(const ede_callbackContext_t *pContext);

/*
 * Global inline functions
 */


#endif  /* CDE_STUBS_INCLUDED */

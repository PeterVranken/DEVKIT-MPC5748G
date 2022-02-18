#ifndef CEV_CANEVENTS_INCLUDED
#define CEV_CANEVENTS_INCLUDED
/**
 * @file cev_canEvents.h
 * Definition of global interface of module cev_canEvents.c
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

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */

/** Helper to get CAN IDs: Get a 11 Bit standard CAN ID object from the raw number. */
#define CEV_STD_CAN_ID(id11Bit)         ((cev_canId_t){.isExtId=0, .id=(id11Bit)})

/** Helper to get CAN IDs: Get a 29 Bit standard CAN ID object from the raw number. */
#define CEV_EXT_CAN_ID(id29Bit)         ((cev_canId_t){.isExtId=1, .id=(id29Bit)})

/** Helper to get CAN IDs: Get CAN ID object from raw number and Boolean \a isExt. */
#define CEV_CAN_ID(ID, isExt)           ((cev_canId_t){.isExtId=(isExt), .id=(ID)})


/*
 * Global type definitions
 */

/* Elder versions of GCC (unclear which one exactly) may not yet support anonymous structs,
   which exist as GNU extension of C99 and generally since C11. If this happens to your
   compiler then some of the CAN interface samples won't compile. */
#if defined(__GNUC__) && (1000*__GNUC__ + __GNUC_MINOR__ <= 4003 /* Version 4.3 */)

typedef struct cev_canId_t
{
    /** The CAN ID.\n
          Note, this field is intentionally not modelled as 29 Bit integer in order to
        avoid undefined values for unused bit: This supports efficient binary
        comparison of CAN IDs. */
    unsigned long id:31;

    /** The Boolean distinction, whether we have an 11 or a 29 Bit CAN ID. */
    unsigned long isExtId:1;

} cev_canId_t;

#else /* Down here, we have the fully operatinal, normally used code. */

/** CAN ID: The number and the Boolean distinction between 11 and 29 Bit ID. */
typedef union cev_canId_t
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

} cev_canId_t;

_Static_assert(sizeof(cev_canId_t) == sizeof(uint32_t), "Unexpected size of data object");

#endif



/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


#endif  /* CEV_CANEVENTS_INCLUDED */

#ifndef MU8_MAPDIRECTLOOKUPU8_INCLUDED
#define MU8_MAPDIRECTLOOKUPU8_INCLUDED
/**
 * @file mu8_mapDirectLookupU8.h
 * Definition of global interface of module mu8_mapDirectLookupU8.c
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

#include "ede_basicDefinitions.h"
#include "ede_externalInterfaces.h"


/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Create a new handle map with arbitrary mapping but with limited value range. */
bool mu8_createMapDirectLookupU8( ede_mapSenderEvHandleToIdx_t * const pNewMap
                                , unsigned int noKindsOfEv
                                , const signed int rangeSenderHandleEvAry[][2u]
                                , ede_memoryPool_t * pMemPool
                                );

/*
 * Global inline functions
 */


#endif  /* MU8_MAPDIRECTLOOKUPU8_INCLUDED */

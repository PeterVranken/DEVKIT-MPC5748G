#ifndef MPO_MAP_OFFSET_ONLY_INCLUDED
#define MPO_MAP_OFFSET_ONLY_INCLUDED
/**
 * @file mpo_mapOffsetOnly.h
 * Definition of global interface of module mpo_mapOffsetOnly.c
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

/** Create a new handle map with simple offset mapping. */
bool mpo_createMapOffsetOnly( ede_mapSenderEvHandleToIdx_t * const pNewMap
                            , unsigned int noKindsOfEv
                            , const bool isSenderHandleInUseAry[]
                            , ede_memoryPool_t * pMemPool
                            );

/*
 * Global inline functions
 */


#endif  /* MPO_MAP_OFFSET_ONLY_INCLUDED */

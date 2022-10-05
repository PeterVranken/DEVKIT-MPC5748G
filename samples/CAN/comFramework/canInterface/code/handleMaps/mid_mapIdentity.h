#ifndef MID_MAPIDENTITY_INCLUDED
#define MID_MAPIDENTITY_INCLUDED
/**
 * @file mid_mapIdentity.h
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

/** Create a new handle map with identity mapping. */
void mid_createMapIdentity(ede_mapSenderEvHandleToIdx_t *pNewMap);

/*
 * Global inline functions
 */


#endif  /* MID_MAPIDENTITY_INCLUDED */

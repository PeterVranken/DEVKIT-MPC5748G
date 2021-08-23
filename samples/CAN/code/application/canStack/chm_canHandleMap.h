#ifndef CHM_CANHANDLEMAP_INCLUDED
#define CHM_CANHANDLEMAP_INCLUDED
/**
 * @file chm_canHandleMap.h
 * Definition of global interface of module chm_canHandleMap.c
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

#include <typ_types.h>
#include "cde_canDispatcherEngine.config.h"


/*
 * Defines
 */

/** The number of supported CAN buses. */
#define CHM_MAX_NO_CAN_BUSES    4u


/*
 * Global type definitions
 */

/** Work dataset of the map build-up function chm_makeMapEntryOsHandleFrameToCdeIndex(),
    which is used during CAN frame registration process. Although it is meaningless to the
    client code, the data structure has been made public: The client code needs to provide
    the memory space for the dataset and this is easiest possible having the type
    declaration. */
typedef struct chm_handleRanges_t
{
    unsigned int minHOsRx  /** Minimum of all ever seen OS Rx handles. */
               , maxHOsRx  /** Maximum of all ever seen OS Rx handles. */
               , minHOsTx  /** Minimum of all ever seen OS Tx handles. */
               , maxHOsTx; /** Maximum of all ever seen OS Tx handles. */

} chm_workDataset_t[CHM_MAX_NO_CAN_BUSES];



/*
 * Global data declarations
 */


/*
 * Global prototypes
 */
 
/** Provide workspace memory for the map-buildup. */
void chm_allocateWorkspaceForMapBuildup(struct chm_handleRanges_t *pProvidedMemory);

/** Add a handle pair (OS, CAN-IF) to the map. */
boolean_t chm_makeMapEntryOsHandleFrameToCdeIndex( unsigned long canId
                                                 , unsigned int idxBus
                                                 , cde_osHandleFrame_t osHandleFrame
                                                 , unsigned int cdeIdxFrame
                                                 , boolean_t isInbound
                                                 );

/** Map an OS CAN frame handle onto the handle (i.e. index) used in the interface engine. */
boolean_t chm_mapOsHandleFrameToCdeIndex( unsigned int *pIdxFrame
                                        , unsigned int idxBus
                                        , cde_osHandleFrame_t osHandleFrame
                                        );


/*
 * Global inline functions
 */


#endif  /* CHM_CANHANDLEMAP_INCLUDED */

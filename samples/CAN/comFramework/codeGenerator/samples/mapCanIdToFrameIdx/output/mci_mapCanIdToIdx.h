#ifndef MCI_MAP_CAN_ID_TO_IDX_INCLUDED
#define MCI_MAP_CAN_ID_TO_IDX_INCLUDED
/**
 * @file mci_mapCanIdToIdx.h
 * Definition of global interface of module mci_mapCanIdToIdx.c
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
#include "mci_mapCanIdToIdx_dataTables.h"


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

#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID != 0
/** Get the frame index as used by the CAN interface engine from the pair of CAN bus and
    CAN standard ID. */
uint8_t mci_getFrameIdxByCanBusAndStdId(uint8_t idxBus, uint16_t canId);
#endif

#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0  ||  MCI_SUPPORT_EXTENDED_CAN_IDS != 0
/** Get the frame index as used by the CAN interface engine of the very frame, which is
    transmitted on the given bus and which has the given CAN ID. */
uint8_t mci_getIdxFrameByCanId( uint8_t idxBus
#if MCI_SUPPORT_EXTENDED_CAN_IDS == 0
                              , uint16_t id
#else
                              , uint32_t id
                              , bool isExtId
#endif
                              );
#endif

#endif  /* MCI_MAP_CAN_ID_TO_IDX_INCLUDED */

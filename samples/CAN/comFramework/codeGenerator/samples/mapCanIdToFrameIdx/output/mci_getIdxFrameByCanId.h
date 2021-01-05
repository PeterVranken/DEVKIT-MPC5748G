#ifndef MCI_GETIDXFRAMEBYCANID_INCLUDED
#define MCI_GETIDXFRAMEBYCANID_INCLUDED
/**
 * @file mci_getIdxFrameByCanId.h
 * Definition of global interface of module mci_getIdxFrameByCanId.c
 *
 * Copyright (C) 2015 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "mci_mapCanIdToFrameIdx.h"


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

/** Get the frame index as used by the CAN interface engine of the very frame, which is
    transmitted on the given bus and which has the given CAN ID. */
UInt8 mci_getIdxFrameByCanId( UInt8 idxBus
#if MCI_SUPPORT_EXTENDED_CAN_IDS == 0
                            , UInt16 id
#else
                            , UInt32 id
#endif
                            );

#endif  /* MCI_GETIDXFRAMEBYCANID_INCLUDED */

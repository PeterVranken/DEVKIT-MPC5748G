/**
 * @file ose_dataTables.c
 * 
 * This module contains the data tables, which are required by the CAN transmission
 * simulation in the emulated operating system. The hand-coded module \a
 * ose_operatingSystemEmulation declares the data tables as extern and the code generator
 * generates then from the CAN databases. This way the simulation knowns, which CAN frames
 * to simulate and how to.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.0,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "cap_canApi.h"
#include "e2e_frameProtection.h"
#include "cde_canDispatcherEngine.h"
#include "ose_unpackAndCheckFrame.h"
#include "ose_operatingSystemEmulation.h"
#include "ose_dataTables.h"


/*
 * Defines
 */

 

/*
 * Local type definitions
 */

 

/*
 * Local prototypes
 */

 

/*
 * Data definitions
 */

/** This is the external instatiation of the data table of module \a
    ose_operatingSystemEmulation, which is required by that module to do the
    implementation of the simulation of CAN reception. */
const ose_receivedCanFrame_t ose_receivedCanFrameAry[] =
{
    [0] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1706
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1706
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [1] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1242
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1242
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [2] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 774
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_774
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [3] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1907
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1907
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [4] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 594
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_594
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [5] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1207
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1207
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [6] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 902
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_902
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [7] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 609
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_609
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [8] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1367
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1367
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [9] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1114
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1114
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [10] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 667
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_667
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [11] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1294
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1294
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [12] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1051
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1051
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [13] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1352
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1352
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [14] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1140
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1140
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [15] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 652
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_652
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [16] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1091
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1091
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [17] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1715
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1715
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [18] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 131
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_131
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [19] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 833
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_833
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [20] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 514
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_514
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [21] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 417
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_417
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [22] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1246
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1246
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [23] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1423
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1423
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [24] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 846
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_846
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [25] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1764
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1764
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [26] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1412
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1412
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 500
        },
    [27] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1445
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1445
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [28] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 442
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_442
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [29] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 672
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_672
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [30] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 718
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_718
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [31] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1042
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1042
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [32] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 2013
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_2013
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [33] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1473
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1473
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [34] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 779
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_779
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [35] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 877
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_877
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [36] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 489
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_489
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [37] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1758
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1758
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [38] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1324
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1324
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [39] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1252
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1252
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [40] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 947
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_947
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [41] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1334
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1334
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [42] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 458
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_458
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [43] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [44] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 435
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_435
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [45] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 982
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_982
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [46] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 263
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_263
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [47] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 90
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_90
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [48] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1675
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1675
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [49] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 261
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_261
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [50] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 660
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_660
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [51] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1074
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1074
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [52] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1747
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1747
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [53] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 786
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_786
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [54] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 341
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_341
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [55] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1400
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1400
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [56] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1545
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1545
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [57] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 328
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_328
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [58] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 844
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_844
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [59] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 196
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_196
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [60] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 870
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_870
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [61] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1492
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1492
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [62] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1413
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1413
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [63] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1185
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1185
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [64] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 322
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_322
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [65] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1188
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1188
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [66] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 2012
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_2012
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [67] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1041
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1041
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [68] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 287
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_287
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [69] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 138
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_138
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [70] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 937
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_937
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [71] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 490
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_490
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [72] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1827
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1827
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [73] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1819
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1819
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [74] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1255
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1255
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [75] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1036
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1036
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [76] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 922
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_922
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [77] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 759
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_759
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [78] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 88
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_88
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [79] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 162
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_162
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [80] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 495
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_495
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [81] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 563
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_563
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [82] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1888
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1888
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [83] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1382
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1382
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [84] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1345
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1345
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [85] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 497
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_497
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [86] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1514
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1514
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [87] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 92
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_92
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [88] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1350
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1350
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [89] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1347
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1347
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [90] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 31
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_31
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [91] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1694
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1694
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [92] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 725
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_725
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [93] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 429
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_429
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [94] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 633
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_633
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [95] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1005
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1005
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [96] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1794
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1794
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [97] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1010
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1010
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [98] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 260
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_260
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [99] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1337
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1337
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [100] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1519
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1519
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [101] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 888
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_888
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [102] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1320
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1320
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [103] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1162
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1162
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [104] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 187
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_187
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [105] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 428
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_428
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [106] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1217
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1217
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [107] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 456
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_456
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [108] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1627
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1627
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [109] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 804
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_804
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [110] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 259
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_259
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [111] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1433
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1433
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [112] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1820
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1820
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [113] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1909
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1909
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [114] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1318
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1318
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [115] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1068
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1068
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [116] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1670
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1670
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [117] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1300
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1300
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [118] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1446
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1446
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [119] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 144
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_144
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [120] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1029
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1029
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [121] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 23
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_23
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [122] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1262
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1262
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [123] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1512
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1512
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 500
        },
    [124] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 912
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_912
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [125] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1979
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1979
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [126] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1856
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1856
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [127] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 74
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_74
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 1000
        },
    [128] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1779
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1779
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [129] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 425
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_425
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [130] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1697
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1697
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [131] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 378
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_378
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [132] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 814
        , .DLC = 1
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_814
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [133] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 929
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_929
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [134] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1661
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1661
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [135] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1115
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1115
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [136] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1540
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1540
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [137] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1831
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1831
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [138] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1978
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1978
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [139] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1968
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1968
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [140] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1795
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1795
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [141] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 545
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_545
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [142] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1873
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1873
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [143] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1612
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1612
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [144] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 214
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_214
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [145] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 577
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_577
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [146] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 517
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_517
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [147] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1470
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1470
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [148] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1189
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1189
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [149] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 480
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_480
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [150] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 865
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_865
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [151] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1940
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1940
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [152] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 764
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_764
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [153] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 907
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_907
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [154] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 366
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_366
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [155] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 2039
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_2039
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [156] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 411
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_411
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [157] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 376
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_376
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [158] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1985
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1985
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [159] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1572
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1572
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [160] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 253
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_253
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [161] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 866
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_866
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [162] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1270
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1270
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [163] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1631
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1631
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [164] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 823
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_823
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [165] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 83
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_83
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [166] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 481
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_481
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [167] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 65
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_65
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [168] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1776
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1776
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [169] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 11
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_11
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [170] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 732
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_732
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [171] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 682
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_682
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [172] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1840
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1840
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [173] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 2036
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_2036
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [174] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 963
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_963
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [175] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 510
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_510
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [176] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 105
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_105
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [177] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1756
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1756
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [178] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 988
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_988
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [179] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 200
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_200
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [180] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 2
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_2
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [181] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1660
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1660
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [182] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1875
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1875
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [183] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1932
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1932
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [184] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 639
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_639
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [185] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 541
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_541
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [186] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1911
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1911
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [187] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 2032
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_2032
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [188] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1837
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1837
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [189] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 2011
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_2011
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [190] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1672
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1672
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [191] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 126
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_126
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [192] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1848
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1848
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [193] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1989
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1989
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [194] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 248
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_248
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [195] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 424
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_424
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [196] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 325
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_325
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [197] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 506
        , .DLC = 1
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_506
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [198] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1244
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1244
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [199] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1218
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1218
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [200] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 329
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_329
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [201] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1030
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1030
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [202] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 70
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_70
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [203] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 906
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_906
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [204] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1507
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1507
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [205] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1253
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1253
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [206] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 362
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_362
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [207] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 800
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_800
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [208] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 283
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_283
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [209] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1562
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1562
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [210] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 464
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_464
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [211] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1853
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1853
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 100
        },
    [212] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1319
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1319
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [213] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 564
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_564
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [214] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1642
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1642
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [215] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1024
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1024
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [216] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 2004
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_2004
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [217] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 14
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_14
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [218] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 477
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_477
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [219] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1781
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1781
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [220] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 572
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_572
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [221] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1990
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1990
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [222] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1811
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1811
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [223] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 27
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_27
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [224] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1576
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1576
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [225] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1454
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1454
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [226] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 794
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_794
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [227] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1714
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1714
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [228] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 2010
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_2010
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [229] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 300
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_300
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [230] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1561
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1561
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [231] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 992
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_992
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [232] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 157
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_157
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [233] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1981
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1981
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [234] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1169
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1169
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [235] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1941
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1941
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [236] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 978
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_978
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [237] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1155
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1155
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [238] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1971
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1971
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [239] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1838
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1838
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [240] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1770
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1770
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [241] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1701
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1701
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [242] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1727
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1727
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [243] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1329
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1329
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [244] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1493
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1493
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [245] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 997
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_997
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 1000
        },
    [246] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1269
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1269
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [247] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1962
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1962
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [248] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1116
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1116
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [249] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 32
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_32
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [250] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1479
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1479
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 1000
        },
    [251] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 557
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_557
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [252] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1857
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1857
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [253] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1395
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1395
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [254] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 457
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_457
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [255] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1424
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1424
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [256] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1859
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1859
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [257] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 985
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_985
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [258] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 454
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_454
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [259] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 753
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_753
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [260] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 13
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_13
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [261] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1408
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1408
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [262] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 999
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_999
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [263] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 132
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_132
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [264] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 553
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_553
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [265] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 321
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_321
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [266] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1552
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1552
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [267] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1487
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1487
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [268] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1225
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1225
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [269] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1183
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1183
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [270] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 679
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_679
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [271] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 257
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_257
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [272] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1032
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1032
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [273] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 58
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_58
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [274] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 313
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_313
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [275] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 115
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_115
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [276] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1574
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1574
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [277] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1757
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1757
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [278] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 505
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_505
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [279] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1310
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1310
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [280] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 567
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_567
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [281] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1632
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1632
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [282] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 345
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_345
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [283] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1918
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1918
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [284] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 858
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_858
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [285] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 467
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_467
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [286] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1754
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1754
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [287] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 923
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_923
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [288] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 44
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_44
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [289] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 315
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_315
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [290] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1125
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1125
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [291] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1842
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1842
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [292] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1429
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1429
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [293] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 191
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_191
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [294] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 967
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_967
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [295] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1948
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1948
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [296] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 462
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_462
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [297] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 673
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_673
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [298] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 422
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_422
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [299] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1821
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1821
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [300] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1380
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1380
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [301] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1788
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1788
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [302] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 255
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_255
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [303] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 586
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_586
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [304] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 914
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_914
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [305] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 565
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_565
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [306] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 53
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_53
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [307] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 752
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_752
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [308] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1312
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1312
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [309] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 863
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_863
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [310] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1535
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1535
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [311] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 262
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_262
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [312] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1208
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1208
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [313] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1542
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1542
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [314] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1341
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1341
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [315] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1119
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1119
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [316] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 869
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_869
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [317] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1381
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1381
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [318] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 152
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_152
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [319] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1496
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1496
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [320] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1237
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1237
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [321] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 927
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_927
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [322] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1601
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1601
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [323] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 405
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_405
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [324] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1219
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1219
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [325] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 788
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_788
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [326] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1689
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1689
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [327] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 42
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_42
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [328] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1671
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1671
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [329] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1890
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1890
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [330] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 434
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_434
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [331] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1389
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1389
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [332] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 141
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_141
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [333] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 412
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_412
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [334] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 592
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_592
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [335] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1813
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1813
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [336] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1323
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1323
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [337] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 334
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_334
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [338] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 18
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_18
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [339] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1302
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1302
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [340] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1622
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1622
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [341] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1997
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1997
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [342] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 82
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_82
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [343] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1816
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1816
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [344] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 159
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_159
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [345] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1449
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1449
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [346] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1177
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1177
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [347] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1356
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1356
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [348] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 875
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_875
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [349] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1592
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1592
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [350] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1870
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1870
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [351] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 440
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_440
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [352] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1080
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1080
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [353] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 2000
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_2000
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [354] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1055
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1055
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [355] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 234
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_234
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [356] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1075
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1075
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [357] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 845
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_845
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [358] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 605
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_605
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [359] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1330
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1330
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [360] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1249
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1249
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 500
        },
    [361] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 579
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_579
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [362] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 891
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_891
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [363] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1082
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1082
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [364] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 878
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_878
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [365] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 299
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_299
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [366] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1921
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1921
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [367] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 754
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_754
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [368] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 838
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_838
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [369] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 16
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_16
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [370] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1578
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1578
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [371] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1550
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1550
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [372] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1636
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1636
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [373] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 575
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_575
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [374] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 931
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_931
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [375] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 525
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_525
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [376] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1645
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1645
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [377] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1832
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1832
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [378] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1598
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1598
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [379] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1933
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1933
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [380] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1959
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1959
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [381] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 748
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_748
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [382] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1566
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1566
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [383] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 722
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_722
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [384] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1817
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1817
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [385] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1910
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1910
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [386] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 75
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_75
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 100
        },
    [387] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1946
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1946
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [388] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1193
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1193
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [389] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 95
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_95
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [390] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1678
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1678
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [391] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1812
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1812
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [392] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1131
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1131
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [393] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 625
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_625
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [394] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 204
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_204
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [395] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1700
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1700
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [396] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1600
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1600
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [397] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1307
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1307
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [398] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1414
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1414
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [399] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1085
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1085
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [400] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 39
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_39
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [401] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1453
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1453
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [402] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1039
        , .DLC = 1
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1039
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [403] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1668
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1668
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [404] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1724
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1724
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [405] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1296
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1296
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [406] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 461
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_461
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [407] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1804
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1804
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [408] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 496
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_496
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [409] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 777
        , .DLC = 1
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_777
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [410] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1844
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1844
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [411] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 511
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_511
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [412] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 616
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_616
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [413] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 934
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_934
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [414] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1012
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1012
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [415] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 499
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_499
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [416] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 993
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_993
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [417] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1210
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1210
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [418] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 566
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_566
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [419] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 810
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_810
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [420] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1001
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1001
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [421] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1238
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1238
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [422] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1602
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1602
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [423] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 113
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_113
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [424] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1629
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1629
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [425] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1928
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1928
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [426] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1256
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1256
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [427] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1852
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1852
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [428] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 29
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_29
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [429] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 726
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_726
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [430] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 245
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_245
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [431] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1965
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1965
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [432] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1393
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1393
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [433] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1338
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1338
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [434] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1478
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1478
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [435] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1500
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1500
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [436] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 2033
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_2033
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [437] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1058
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1058
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [438] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 223
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_223
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [439] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 971
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_971
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [440] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1815
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1815
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [441] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 824
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_824
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [442] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 445
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_445
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [443] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 583
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_583
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [444] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 551
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_551
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [445] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 8
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_8
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [446] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 840
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_840
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [447] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 899
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_899
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [448] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 148
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_148
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [449] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1474
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1474
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [450] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1762
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1762
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [451] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1121
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1121
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [452] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1648
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1648
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [453] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1120
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1120
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [454] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 897
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_897
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [455] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 324
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_324
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [456] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1232
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1232
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [457] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 161
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_161
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [458] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1037
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1037
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [459] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1129
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1129
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [460] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1231
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1231
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [461] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 892
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_892
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [462] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1982
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1982
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [463] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 225
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_225
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [464] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 232
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_232
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [465] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 591
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_591
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [466] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 91
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_91
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [467] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 316
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_316
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [468] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1841
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1841
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [469] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1103
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1103
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [470] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 109
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_109
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [471] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1999
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1999
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [472] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 956
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_956
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [473] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1847
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1847
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [474] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 267
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_267
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [475] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1407
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1407
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [476] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1915
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1915
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [477] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 2007
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_2007
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [478] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1194
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1194
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [479] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 446
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_446
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [480] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1060
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1060
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [481] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1702
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1702
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [482] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 964
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_964
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [483] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 400
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_400
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [484] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 264
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_264
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [485] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 479
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_479
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [486] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 502
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_502
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [487] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 419
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_419
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [488] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1325
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1325
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [489] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 393
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_393
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [490] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 703
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_703
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [491] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 48
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_48
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [492] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1570
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1570
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [493] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1791
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1791
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [494] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1364
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1364
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
};

/** The number of entries in the external data table \a ose_receivedCanFrameAry. */
const unsigned int ose_noReceivedCanFrames = sizeof(ose_receivedCanFrameAry)
                                             / sizeof(ose_receivedCanFrameAry[0]);

/** This is the external instatiation of the data table of module \a
    ose_operatingSystemEmulation, which is required by that module to do the
    implementation of CAN output. Particularly some information is required to do the E2E
    validation for these frames. */
const ose_sentCanFrame_t ose_sentCanFrameAry[] =
{
    [0] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 2044
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_2044
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [1] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1049
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1049
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [2] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1834
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1834
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [3] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1053
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1053
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [4] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 693
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_693
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [5] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1143
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1143
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [6] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 453
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_453
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [7] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 403
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_403
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [8] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 766
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_766
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [9] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1271
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1271
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [10] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 332
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_332
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [11] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 602
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_602
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [12] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1605
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1605
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [13] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1731
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1731
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [14] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1529
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1529
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [15] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 808
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_808
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [16] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1181
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1181
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [17] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1725
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1725
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [18] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 208
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_208
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [19] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 2018
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_2018
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [20] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 590
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_590
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [21] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1419
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1419
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [22] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1937
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1937
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [23] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1630
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1630
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [24] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1033
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1033
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [25] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 803
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_803
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [26] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 106
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_106
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [27] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 905
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_905
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [28] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1998
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1998
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [29] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1885
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1885
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [30] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1415
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1415
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [31] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 915
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_915
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [32] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 349
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_349
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [33] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 25
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_25
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [34] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1641
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1641
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [35] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 669
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_669
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [36] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1401
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1401
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [37] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1340
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1340
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [38] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1151
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1151
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [39] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1730
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1730
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [40] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 46
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_46
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [41] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1939
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1939
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [42] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 659
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_659
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [43] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 981
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_981
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [44] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 708
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_708
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [45] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1618
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1618
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [46] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1956
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1956
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [47] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 463
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_463
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [48] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 954
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_954
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [49] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1126
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1126
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [50] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 729
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_729
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [51] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 2045
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_2045
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [52] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1901
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1901
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [53] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 381
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_381
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [54] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 796
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_796
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [55] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1652
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1652
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [56] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1442
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1442
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [57] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 661
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_661
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [58] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1084
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1084
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [59] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1170
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1170
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [60] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1696
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1696
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [61] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1398
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1398
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [62] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1425
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1425
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [63] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1154
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1154
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [64] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1404
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1404
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [65] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1374
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1374
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [66] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 820
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_820
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [67] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1713
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1713
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [68] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1485
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1485
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [69] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1385
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1385
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [70] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 2017
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_2017
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [71] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 523
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_523
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [72] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 807
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_807
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [73] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1637
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1637
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [74] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1784
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1784
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [75] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 649
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_649
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [76] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1801
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1801
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [77] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1926
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1926
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [78] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 986
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_986
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [79] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 998
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_998
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [80] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 743
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_743
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [81] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 655
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_655
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [82] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1332
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1332
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [83] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 86
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_86
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [84] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1002
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1002
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [85] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1957
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1957
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [86] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 969
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_969
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [87] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 739
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_739
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [88] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 484
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_484
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [89] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1970
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1970
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [90] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 163
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_163
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [91] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 948
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_948
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [92] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 853
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_853
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [93] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1444
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1444
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [94] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 570
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_570
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [95] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1406
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1406
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [96] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 201
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_201
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [97] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1951
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1951
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [98] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 154
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_154
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [99] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1043
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1043
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [100] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 306
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_306
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [101] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 37
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_37
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [102] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1351
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1351
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [103] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1458
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1458
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [104] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 809
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_809
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [105] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1752
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1752
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [106] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 170
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_170
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [107] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1732
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1732
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [108] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 550
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_550
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [109] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 168
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_168
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [110] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 66
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_66
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [111] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1387
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1387
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [112] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 441
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_441
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [113] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1716
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1716
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [114] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 941
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_941
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [115] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1640
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1640
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [116] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1575
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1575
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [117] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1272
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1272
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [118] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 913
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_913
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [119] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1165
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1165
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [120] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 895
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_895
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [121] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 666
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_666
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [122] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1495
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1495
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [123] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1175
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1175
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [124] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1277
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1277
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [125] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1593
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1593
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [126] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1980
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1980
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [127] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1287
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1287
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [128] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 189
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_189
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [129] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 494
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_494
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [130] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1045
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1045
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [131] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1469
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1469
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [132] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1684
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1684
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [133] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1614
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1614
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [134] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 747
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_747
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [135] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1013
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1013
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [136] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 582
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_582
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [137] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 291
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_291
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [138] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 137
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_137
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [139] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 782
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_782
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [140] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1867
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1867
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [141] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 61
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_61
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [142] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1403
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1403
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [143] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 158
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_158
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [144] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1052
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1052
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [145] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1297
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1297
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [146] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1829
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1829
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [147] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1281
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1281
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [148] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 678
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_678
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [149] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1157
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1157
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [150] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 111
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_111
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [151] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 509
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_509
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [152] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 199
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_199
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [153] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1931
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1931
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [154] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1524
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1524
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [155] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 924
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_924
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [156] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1022
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1022
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [157] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 793
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_793
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [158] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 465
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_465
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [159] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 294
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_294
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [160] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 593
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_593
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [161] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1475
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1475
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [162] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 192
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_192
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [163] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1954
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1954
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [164] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1993
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1993
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [165] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 392
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_392
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [166] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 33
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_33
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [167] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1076
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1076
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [168] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 24
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_24
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [169] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 880
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_880
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [170] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 646
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_646
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [171] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 85
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_85
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [172] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 696
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_696
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [173] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 991
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_991
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [174] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 632
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_632
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [175] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1388
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1388
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [176] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 755
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_755
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [177] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 966
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_966
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [178] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1961
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1961
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [179] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1687
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1687
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [180] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1663
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1663
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [181] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1510
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1510
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 1000
        },
    [182] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1460
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1460
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [183] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 653
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_653
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [184] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 699
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_699
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [185] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 970
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_970
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [186] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 305
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_305
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [187] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 309
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_309
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [188] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 231
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_231
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [189] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1530
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1530
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [190] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1676
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1676
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [191] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1491
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1491
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [192] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1536
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1536
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [193] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 621
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_621
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [194] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 538
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_538
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [195] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1384
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1384
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [196] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 21
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_21
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [197] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 409
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_409
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [198] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1148
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1148
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [199] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1934
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1934
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [200] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1538
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1538
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [201] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1146
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1146
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [202] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1025
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1025
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [203] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1610
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1610
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [204] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1315
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1315
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [205] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 900
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_900
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [206] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 171
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_171
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [207] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 240
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_240
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [208] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 178
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_178
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [209] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 2031
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_2031
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [210] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1935
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1935
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [211] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1416
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1416
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [212] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 950
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_950
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [213] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 734
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_734
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [214] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1565
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1565
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [215] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1699
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1699
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [216] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1698
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1698
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [217] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1854
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1854
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [218] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1142
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1142
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [219] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1007
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1007
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [220] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1613
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1613
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [221] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 627
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_627
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [222] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 973
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_973
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [223] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1362
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1362
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [224] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 612
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_612
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [225] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 5
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_5
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [226] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1477
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1477
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [227] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1604
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1604
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [228] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 36
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_36
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [229] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 2001
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_2001
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [230] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 80
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_80
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [231] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 0
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_0
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [232] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1494
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1494
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [233] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 537
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_537
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [234] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 741
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_741
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [235] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1396
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1396
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [236] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 207
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_207
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [237] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1996
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1996
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [238] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1505
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1505
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [239] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 26
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_26
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [240] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 515
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_515
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [241] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 677
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_677
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
};

/** The number of entries in the external data table \a ose_sentCanFrameAry. */
const unsigned int ose_noSentCanFrames = sizeof(ose_sentCanFrameAry)
                                         / sizeof(ose_sentCanFrameAry[0]);
 

/*
 * Function implementation
 */


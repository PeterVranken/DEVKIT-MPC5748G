/**
 * @file ose_dataTables.c
 * 
 * This module contains the data tables, which are required by the CAN transmission
 * simulation in the emulated operating system. The hand-coded module \a
 * ose_operatingSystemEmulation declares the data tables as extern and the code generator
 * generates then from the CAN databases. This way the simulation knowns, which CAN frames
 * to simulate and how to.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.6,
 * see http://sourceforge.net/projects/comframe/
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "cap_canApi.h"
#include "e2e_frameProtection.h"
#include "ede_eventDispatcherEngine.h"
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
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1706_1706
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [1] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1242
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1242_1242
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [2] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 774
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_774_774
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [3] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1907
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1907_1907
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [4] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 594
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_594_594
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [5] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1207
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1207_1207
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [6] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 902
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_902_902
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [7] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 609
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_609_609
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [8] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1367
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1367_1367
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [9] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1114
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1114_1114
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [10] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 667
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_667_667
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [11] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1294
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1294_1294
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [12] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1051
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1051_1051
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [13] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1352
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1352_1352
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [14] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1140
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1140_1140
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [15] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 652
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_652_652
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [16] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1091
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1091_1091
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [17] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1715
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1715_1715
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [18] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 131
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_131_131
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [19] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 833
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_833_833
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [20] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 514
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_514_514
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [21] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 417
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_417_417
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [22] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1246
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1246_1246
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [23] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1423
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1423_1423
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [24] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 846
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_846_846
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [25] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1764
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1764_1764
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [26] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1412
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1412_1412
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 500
        },
    [27] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1445
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1445_1445
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [28] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 442
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_442_442
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [29] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 672
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_672_672
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [30] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 718
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_718_718
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [31] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1042
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1042_1042
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [32] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 2047
        , .isExtId = true
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_x2047_x2047
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [33] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1473
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1473_1473
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [34] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 779
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_779_779
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [35] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 877
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_877_877
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [36] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 489
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_489_489
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [37] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1758
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1758_1758
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [38] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1324
        , .isExtId = false
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1324_1324
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [39] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1252
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1252_1252
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [40] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 947
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_947_947
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [41] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1334
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1334_1334
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [42] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 458
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_458_458
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [43] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_1_1
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [44] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 435
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_435_435
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [45] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 982
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_982_982
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [46] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 263
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B1_frame_263_263
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [47] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 90
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_90_90
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [48] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1675
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1675_1675
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [49] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 261
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_261_261
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [50] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 660
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_660_660
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [51] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1074
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1074_1074
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [52] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1747
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1747_1747
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [53] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 786
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_786_786
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [54] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 341
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_341_341
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [55] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1400
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1400_1400
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [56] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1545
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1545_1545
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [57] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 328
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_328_328
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [58] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 844
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_844_844
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [59] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 196
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_196_196
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [60] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 870
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_870_870
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [61] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1492
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1492_1492
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [62] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1413
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1413_1413
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [63] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1185
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1185_1185
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [64] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 322
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_322_322
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [65] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1188
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1188_1188
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [66] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 2012
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_2012_2012
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [67] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1041
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1041_1041
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [68] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 287
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_287_287
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [69] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 138
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_138_138
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [70] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 937
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_937_937
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [71] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 490
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_490_490
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [72] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1827
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1827_1827
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [73] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1819
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1819_1819
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [74] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1255
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1255_1255
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [75] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1036
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1036_1036
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [76] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 922
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_922_922
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [77] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 759
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_759_759
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [78] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 88
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_88_88
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [79] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 162
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_162_162
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [80] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 495
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_495_495
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [81] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 563
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_563_563
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [82] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1888
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1888_1888
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [83] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1382
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1382_1382
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [84] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1345
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1345_1345
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [85] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 497
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_497_497
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [86] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1514
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1514_1514
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [87] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 92
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_92_92
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [88] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1350
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1350_1350
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [89] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1347
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1347_1347
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [90] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 31
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_31_31
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [91] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1694
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1694_1694
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [92] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 725
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_725_725
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [93] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 429
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_429_429
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [94] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 633
        , .isExtId = false
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_633_633
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [95] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1005
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1005_1005
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [96] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1794
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1794_1794
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [97] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1010
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1010_1010
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [98] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 260
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_260_260
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [99] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1337
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B2_frame_1337_1337
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [100] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1519
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1519_1519
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [101] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 888
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_888_888
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [102] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1320
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1320_1320
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [103] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1162
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1162_1162
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [104] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 187
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_187_187
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [105] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 428
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_428_428
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [106] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1217
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1217_1217
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [107] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 456
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_456_456
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [108] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1627
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1627_1627
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [109] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 804
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_804_804
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [110] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 259
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_259_259
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [111] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1433
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1433_1433
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [112] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1820
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1820_1820
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [113] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1909
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1909_1909
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [114] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1318
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1318_1318
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [115] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1068
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1068_1068
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [116] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1670
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1670_1670
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [117] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1300
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1300_1300
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [118] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1446
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1446_1446
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [119] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 144
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_144_144
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [120] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1029
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1029_1029
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [121] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 23
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_23_23
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [122] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1262
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1262_1262
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [123] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1512
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1512_1512
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 500
        },
    [124] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 912
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_912_912
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [125] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1979
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1979_1979
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [126] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1856
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1856_1856
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [127] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 74
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_74_74
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 1000
        },
    [128] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1779
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1779_1779
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [129] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 425
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_425_425
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [130] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1697
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1697_1697
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [131] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 378
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_378_378
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [132] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 814
        , .isExtId = false
        , .DLC = 1
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_814_814
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [133] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 929
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_929_929
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [134] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1661
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1661_1661
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [135] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1115
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1115_1115
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [136] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1540
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1540_1540
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [137] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1831
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1831_1831
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [138] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1978
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1978_1978
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [139] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1968
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1968_1968
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [140] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1795
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1795_1795
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [141] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 545
        , .isExtId = false
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_545_545
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [142] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1873
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1873_1873
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [143] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1612
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_1612_1612
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [144] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 214
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B3_frame_214_214
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [145] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 577
        , .isExtId = false
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_577_577
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [146] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 517
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_517_517
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [147] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1470
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1470_1470
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [148] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1189
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1189_1189
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [149] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 480
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_480_480
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [150] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 865
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_865_865
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [151] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1940
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1940_1940
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [152] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 764
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_764_764
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [153] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 907
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_907_907
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [154] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 366
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_366_366
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [155] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 2039
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_2039_2039
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [156] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 411
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_411_411
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [157] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 376
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_376_376
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [158] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1985
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1985_1985
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [159] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1572
        , .isExtId = false
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1572_1572
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [160] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 253
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_253_253
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [161] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 866
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_866_866
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [162] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1270
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1270_1270
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [163] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1631
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1631_1631
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [164] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 823
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_823_823
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [165] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 83
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_83_83
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [166] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 481
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_481_481
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [167] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 65
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_65_65
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [168] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1776
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1776_1776
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [169] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 11
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_11_11
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [170] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 732
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_732_732
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [171] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 682
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_682_682
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [172] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1840
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1840_1840
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [173] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 2036
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_2036_2036
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [174] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 963
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_963_963
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [175] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 510
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_510_510
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [176] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 105
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_105_105
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [177] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1756
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1756_1756
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [178] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 988
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_988_988
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [179] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 200
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_200_200
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [180] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 2
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_2_2
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [181] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1660
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1660_1660
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [182] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1875
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B4_frame_1875_1875
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [183] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1932
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1932_1932
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [184] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 639
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_639_639
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [185] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 541
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_541_541
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [186] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1911
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1911_1911
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [187] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 2032
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_2032_2032
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [188] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1837
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1837_1837
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [189] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 2011
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_2011_2011
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [190] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1672
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1672_1672
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [191] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 126
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_126_126
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [192] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1848
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1848_1848
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [193] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1989
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1989_1989
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [194] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 248
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_248_248
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [195] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 424
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_424_424
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [196] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 325
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_325_325
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [197] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 506
        , .isExtId = false
        , .DLC = 1
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_506_506
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [198] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1244
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1244_1244
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [199] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1218
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1218_1218
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [200] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 329
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_329_329
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [201] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1030
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1030_1030
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [202] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 70
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_70_70
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [203] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 906
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_906_906
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [204] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1507
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1507_1507
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [205] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1253
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1253_1253
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [206] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 362
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_362_362
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [207] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 800
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_800_800
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [208] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 283
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_283_283
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [209] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1562
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1562_1562
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [210] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 464
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_464_464
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [211] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1853
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1853_1853
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 100
        },
    [212] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1319
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1319_1319
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [213] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 564
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_564_564
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [214] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1642
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1642_1642
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [215] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1024
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1024_1024
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [216] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 2004
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_2004_2004
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [217] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 14
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_14_14
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [218] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 477
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_477_477
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [219] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1781
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1781_1781
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [220] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 572
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_572_572
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [221] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1990
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1990_1990
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [222] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1811
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1811_1811
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [223] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 27
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_27_27
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [224] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1576
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1576_1576
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [225] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1454
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B5_frame_1454_1454
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [226] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 794
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_794_794
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [227] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1714
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1714_1714
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [228] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 2010
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_2010_2010
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [229] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 300
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_300_300
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [230] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1561
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1561_1561
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [231] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 992
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_992_992
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [232] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 157
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_157_157
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [233] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1981
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1981_1981
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [234] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1169
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1169_1169
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [235] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1941
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1941_1941
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [236] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 978
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_978_978
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [237] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1155
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1155_1155
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [238] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1971
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1971_1971
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [239] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1838
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1838_1838
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [240] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1770
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1770_1770
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [241] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1701
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1701_1701
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [242] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1727
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1727_1727
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [243] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1329
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1329_1329
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [244] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1493
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1493_1493
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [245] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 997
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_997_997
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 1000
        },
    [246] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1269
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1269_1269
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [247] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1962
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1962_1962
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [248] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1116
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1116_1116
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [249] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 32
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_32_32
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [250] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1479
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1479_1479
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 1000
        },
    [251] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 557
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_557_557
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [252] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1857
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1857_1857
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [253] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1395
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1395_1395
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [254] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 457
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_457_457
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [255] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1424
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1424_1424
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [256] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1859
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1859_1859
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [257] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 985
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_985_985
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [258] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 454
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_454_454
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [259] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 753
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_753_753
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [260] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 13
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_13_13
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [261] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1408
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1408_1408
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [262] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 999
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_999_999
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [263] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 132
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_132_132
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [264] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 553
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_553_553
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [265] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 321
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_321_321
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [266] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1552
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1552_1552
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [267] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1487
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1487_1487
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [268] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1225
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1225_1225
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [269] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1183
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1183_1183
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [270] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 679
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_679_679
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [271] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 257
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_257_257
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [272] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1032
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1032_1032
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [273] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 58
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_58_58
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [274] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 313
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_313_313
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [275] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 115
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_115_115
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [276] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1574
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1574_1574
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [277] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1757
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1757_1757
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [278] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 505
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_505_505
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [279] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1310
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1310_1310
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [280] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 567
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_567_567
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [281] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1632
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1632_1632
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [282] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 345
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_345_345
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [283] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1918
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1918_1918
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [284] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 858
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_858_858
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [285] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 467
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_467_467
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [286] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1754
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_1754_1754
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [287] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 923
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_923_923
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [288] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 44
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_44_44
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [289] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 315
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B6_frame_315_315
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [290] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1125
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1125_1125
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [291] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1842
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1842_1842
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [292] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1429
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1429_1429
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [293] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 191
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_191_191
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [294] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 967
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_967_967
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [295] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1948
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1948_1948
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [296] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 462
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_462_462
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [297] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 673
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_673_673
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [298] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 422
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_422_422
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [299] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1821
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1821_1821
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [300] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1380
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1380_1380
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [301] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1788
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1788_1788
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [302] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 255
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_255_255
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [303] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 586
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_586_586
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [304] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 914
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_914_914
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [305] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 565
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_565_565
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [306] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 53
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_53_53
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [307] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 752
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_752_752
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [308] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1312
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1312_1312
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [309] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 863
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_863_863
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [310] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1535
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1535_1535
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [311] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 262
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_262_262
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [312] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1208
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1208_1208
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [313] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1542
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1542_1542
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [314] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1341
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1341_1341
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [315] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1119
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1119_1119
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [316] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 869
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_869_869
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [317] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1381
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1381_1381
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [318] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 152
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_152_152
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [319] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1496
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1496_1496
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [320] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1237
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1237_1237
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [321] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 927
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_927_927
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [322] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1601
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1601_1601
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [323] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 405
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_405_405
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [324] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1219
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1219_1219
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [325] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 788
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_788_788
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [326] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1689
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1689_1689
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [327] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 42
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_42_42
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [328] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1671
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1671_1671
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [329] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1890
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1890_1890
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [330] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 434
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_434_434
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [331] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1389
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1389_1389
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [332] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 141
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_141_141
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [333] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 412
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_412_412
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [334] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 592
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_592_592
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [335] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1813
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1813_1813
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [336] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1323
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1323_1323
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [337] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 334
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_334_334
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [338] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 18
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_18_18
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [339] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1302
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1302_1302
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [340] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1622
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1622_1622
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [341] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1997
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1997_1997
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [342] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 82
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_82_82
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [343] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1816
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1816_1816
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [344] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 159
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_159_159
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [345] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1449
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1449_1449
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [346] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1177
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1177_1177
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [347] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1356
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1356_1356
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [348] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 875
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_875_875
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [349] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1592
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1592_1592
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [350] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1870
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1870_1870
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [351] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 440
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_440_440
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [352] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1080
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1080_1080
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [353] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 2000
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_2000_2000
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [354] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1055
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1055_1055
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [355] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 234
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_234_234
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [356] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1075
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1075_1075
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [357] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 845
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_845_845
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [358] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 605
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_605_605
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [359] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1330
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B7_frame_1330_1330
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [360] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1249
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1249_1249
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 500
        },
    [361] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 579
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_579_579
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [362] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 891
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_891_891
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [363] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1082
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1082_1082
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [364] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 878
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_878_878
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [365] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 299
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_299_299
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [366] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1921
        , .isExtId = false
        , .DLC = 2
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1921_1921
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [367] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 754
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_754_754
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [368] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 838
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_838_838
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [369] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 16
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_16_16
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [370] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1578
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1578_1578
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [371] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1550
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1550_1550
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [372] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1636
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1636_1636
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [373] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 575
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_575_575
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [374] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 931
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_931_931
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [375] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 525
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_525_525
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [376] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1645
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1645_1645
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [377] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1832
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1832_1832
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [378] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1598
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1598_1598
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [379] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1933
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1933_1933
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [380] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1959
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1959_1959
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [381] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 748
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_748_748
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [382] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1566
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1566_1566
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [383] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 722
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_722_722
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [384] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1817
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1817_1817
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [385] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1910
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1910_1910
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [386] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 75
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_75_75
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 100
        },
    [387] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1946
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1946_1946
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [388] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1193
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1193_1193
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [389] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 95
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_95_95
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [390] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1678
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1678_1678
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [391] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1812
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1812_1812
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [392] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1131
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1131_1131
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [393] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 625
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_625_625
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [394] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 204
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_204_204
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [395] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1700
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1700_1700
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [396] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1600
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1600_1600
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [397] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1307
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1307_1307
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [398] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1414
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1414_1414
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [399] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1085
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1085_1085
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [400] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 39
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_39_39
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [401] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1453
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1453_1453
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [402] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1039
        , .isExtId = false
        , .DLC = 1
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1039_1039
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [403] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1668
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1668_1668
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [404] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1724
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1724_1724
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [405] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1296
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1296_1296
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [406] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 461
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_461_461
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [407] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1804
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1804_1804
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [408] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 496
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_496_496
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [409] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 777
        , .isExtId = false
        , .DLC = 1
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_777_777
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [410] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1844
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_1844_1844
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [411] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 511
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_511_511
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [412] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 616
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_616_616
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [413] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 934
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B8_frame_934_934
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [414] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1012
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1012_1012
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [415] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 499
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_499_499
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [416] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 993
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_993_993
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [417] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1210
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1210_1210
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [418] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 566
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_566_566
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [419] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 810
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_810_810
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [420] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1001
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1001_1001
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [421] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1238
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1238_1238
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [422] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1602
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1602_1602
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [423] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 113
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_113_113
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [424] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1629
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1629_1629
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [425] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1928
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1928_1928
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [426] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1256
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1256_1256
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [427] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1852
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1852_1852
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [428] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 29
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_29_29
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [429] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 726
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_726_726
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [430] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 245
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_245_245
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [431] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1965
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1965_1965
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [432] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1393
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1393_1393
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [433] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1338
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1338_1338
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [434] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1478
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1478_1478
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [435] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1500
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1500_1500
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [436] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 2033
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_2033_2033
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [437] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1058
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1058_1058
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [438] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 223
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_223_223
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [439] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 971
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_971_971
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [440] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1815
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1815_1815
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [441] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 824
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_824_824
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [442] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 445
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_445_445
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [443] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 583
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_583_583
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [444] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 551
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_551_551
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [445] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 8
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_8_8
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [446] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 840
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_840_840
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [447] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 899
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_899_899
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [448] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 148
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_148_148
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [449] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1474
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1474_1474
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [450] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1762
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1762_1762
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [451] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1121
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1121_1121
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [452] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1648
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1648_1648
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [453] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1120
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_1120_1120
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [454] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 897
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B9_frame_897_897
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [455] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 324
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_324_324
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [456] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1232
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1232_1232
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [457] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 161
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_161_161
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [458] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1037
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1037_1037
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [459] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1129
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1129_1129
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [460] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1231
        , .isExtId = false
        , .DLC = 5
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1231_1231
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [461] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 892
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_892_892
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [462] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1982
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1982_1982
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [463] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 225
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_225_225
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [464] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 232
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_232_232
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [465] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 591
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_591_591
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [466] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 91
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_91_91
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [467] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 316
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_316_316
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [468] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1841
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1841_1841
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [469] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1103
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1103_1103
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [470] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 109
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_109_109
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [471] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1999
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1999_1999
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [472] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 956
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_956_956
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [473] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1847
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1847_1847
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [474] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 267
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_267_267
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [475] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1407
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1407_1407
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [476] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1915
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1915_1915
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [477] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 2007
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_2007_2007
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [478] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1194
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1194_1194
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [479] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 446
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_446_446
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [480] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1060
        , .isExtId = false
        , .DLC = 3
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1060_1060
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [481] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1702
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1702_1702
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [482] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 964
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_964_964
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [483] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 400
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_400_400
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [484] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 264
        , .isExtId = false
        , .DLC = 4
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_264_264
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [485] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 479
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_479_479
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [486] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 502
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_502_502
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [487] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 419
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_419_419
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [488] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1325
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1325_1325
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [489] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 393
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_393_393
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [490] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 703
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_703_703
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [491] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 48
        , .isExtId = false
        , .DLC = 8
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_48_48
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [492] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1570
        , .isExtId = false
        , .DLC = 7
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1570_1570
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [493] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1791
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1791_1791
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [494] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1364
        , .isExtId = false
        , .DLC = 6
        , .fctGetFrameContents = e2e_randomFillProtectAndPack_B10_frame_1364_1364
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
        , .isExtId = true
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_x2044_x2044
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [1] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1049
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1049_1049
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [2] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1834
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1834_1834
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [3] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1053
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1053_1053
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [4] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 693
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_693_693
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [5] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1143
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1143_1143
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [6] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 453
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_453_453
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [7] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 403
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_403_403
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [8] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 766
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_766_766
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [9] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1271
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1271_1271
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [10] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 332
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_332_332
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [11] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 602
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_602_602
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [12] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1605
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1605_1605
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [13] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1731
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1731_1731
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [14] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1529
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1529_1529
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [15] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 808
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_808_808
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [16] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1181
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1181_1181
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [17] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1725
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1725_1725
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [18] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 208
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_208_208
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [19] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 2047
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_2047_2047
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [20] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 590
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_590_590
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [21] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1419
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1419_1419
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [22] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 0
        , .isExtId = true
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_x0_x0
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [23] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1630
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1630_1630
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [24] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1033
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1033_1033
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [25] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 803
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_803_803
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [26] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 106
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_106_106
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [27] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 905
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_905_905
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [28] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 0
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_0_0
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [29] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1885
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1885_1885
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [30] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 1415
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_1415_1415
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [31] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 915
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_915_915
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [32] =
        { .idxCanBus = OSE_CAN_BUS_B1
        , .canId = 349
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B1_frame_349_349
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [33] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 25
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_25_25
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [34] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1641
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1641_1641
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [35] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 669
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_669_669
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [36] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1401
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1401_1401
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [37] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1340
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1340_1340
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [38] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1151
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1151_1151
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [39] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1730
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1730_1730
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [40] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 46
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_46_46
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [41] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1939
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1939_1939
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [42] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 659
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_659_659
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [43] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 981
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_981_981
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [44] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 708
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_708_708
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [45] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1618
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1618_1618
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [46] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1956
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1956_1956
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [47] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 463
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_463_463
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [48] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 954
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_954_954
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [49] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1126
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1126_1126
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [50] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 729
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_729_729
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [51] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 2045
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_2045_2045
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [52] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1901
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1901_1901
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [53] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 381
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_381_381
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [54] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 796
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_796_796
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [55] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1652
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1652_1652
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [56] =
        { .idxCanBus = OSE_CAN_BUS_B2
        , .canId = 1442
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B2_frame_1442_1442
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [57] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 661
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_661_661
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [58] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1084
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1084_1084
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [59] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1170
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1170_1170
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [60] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1696
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1696_1696
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [61] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1398
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1398_1398
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [62] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1425
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1425_1425
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [63] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1154
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1154_1154
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [64] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1404
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1404_1404
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [65] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1374
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1374_1374
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [66] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 820
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_820_820
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [67] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1713
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1713_1713
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [68] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1485
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1485_1485
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [69] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1385
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1385_1385
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [70] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 2017
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_2017_2017
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [71] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 523
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_523_523
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [72] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 807
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_807_807
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [73] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1637
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1637_1637
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [74] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 1784
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_1784_1784
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [75] =
        { .idxCanBus = OSE_CAN_BUS_B3
        , .canId = 649
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B3_frame_649_649
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [76] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1801
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1801_1801
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [77] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1926
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1926_1926
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [78] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 986
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_986_986
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [79] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 998
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_998_998
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [80] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 743
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_743_743
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [81] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 655
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_655_655
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [82] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1332
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1332_1332
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [83] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 86
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_86_86
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [84] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1002
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1002_1002
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [85] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1957
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1957_1957
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [86] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 969
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_969_969
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [87] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 739
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_739_739
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [88] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 484
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_484_484
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [89] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1970
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1970_1970
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [90] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 163
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_163_163
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [91] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 948
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_948_948
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [92] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 853
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_853_853
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [93] =
        { .idxCanBus = OSE_CAN_BUS_B4
        , .canId = 1444
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B4_frame_1444_1444
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [94] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 570
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_570_570
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [95] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1406
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1406_1406
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [96] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 201
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_201_201
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [97] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1951
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1951_1951
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [98] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 154
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_154_154
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [99] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1043
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1043_1043
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [100] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 306
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_306_306
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [101] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 37
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_37_37
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [102] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1351
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1351_1351
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 50
        },
    [103] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1458
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1458_1458
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [104] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 809
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_809_809
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [105] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1752
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1752_1752
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [106] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 170
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_170_170
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [107] =
        { .idxCanBus = OSE_CAN_BUS_B5
        , .canId = 1732
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B5_frame_1732_1732
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [108] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 550
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_550_550
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [109] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 168
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_168_168
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [110] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 66
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_66_66
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [111] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1387
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1387_1387
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [112] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 441
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_441_441
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [113] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1716
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1716_1716
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [114] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 941
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_941_941
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [115] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1640
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1640_1640
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [116] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1575
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1575_1575
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [117] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1272
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1272_1272
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [118] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 913
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_913_913
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [119] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1165
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1165_1165
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [120] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 895
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_895_895
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [121] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 666
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_666_666
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [122] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1495
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1495_1495
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [123] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1175
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1175_1175
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [124] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1277
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1277_1277
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [125] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1593
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1593_1593
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [126] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1980
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1980_1980
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [127] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1287
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1287_1287
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [128] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 189
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_189_189
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [129] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 494
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_494_494
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [130] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1045
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1045_1045
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [131] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1469
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1469_1469
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [132] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1684
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1684_1684
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [133] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1614
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1614_1614
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [134] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 747
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_747_747
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [135] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 1013
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_1013_1013
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [136] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 582
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_582_582
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [137] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 291
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_291_291
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [138] =
        { .idxCanBus = OSE_CAN_BUS_B6
        , .canId = 137
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B6_frame_137_137
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [139] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 782
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_782_782
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [140] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1867
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1867_1867
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [141] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 61
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_61_61
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [142] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1403
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1403_1403
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [143] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 158
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_158_158
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 100
        },
    [144] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1052
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1052_1052
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [145] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1297
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1297_1297
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 100
        },
    [146] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1829
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1829_1829
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [147] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1281
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1281_1281
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [148] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 678
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_678_678
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [149] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1157
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1157_1157
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [150] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 111
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_111_111
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [151] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 509
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_509_509
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [152] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 199
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_199_199
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [153] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1931
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1931_1931
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [154] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1524
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1524_1524
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [155] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 924
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_924_924
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [156] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1022
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1022_1022
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [157] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 793
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_793_793
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [158] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 465
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_465_465
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [159] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 294
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_294_294
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [160] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 593
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_593_593
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [161] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1475
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1475_1475
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [162] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 192
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_192_192
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [163] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1954
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1954_1954
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [164] =
        { .idxCanBus = OSE_CAN_BUS_B7
        , .canId = 1993
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B7_frame_1993_1993
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [165] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 392
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_392_392
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [166] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 33
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_33_33
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [167] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1076
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1076_1076
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [168] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 24
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_24_24
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [169] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 880
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_880_880
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [170] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 646
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_646_646
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [171] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 85
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_85_85
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 50
        },
    [172] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 696
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_696_696
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [173] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 991
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_991_991
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [174] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 632
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_632_632
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [175] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1388
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1388_1388
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [176] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 755
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_755_755
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [177] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 966
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_966_966
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [178] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1961
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1961_1961
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [179] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1687
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1687_1687
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [180] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1663
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1663_1663
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [181] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1510
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1510_1510
        , .sendMode = cap_enumSendMode_event
        , .tiCycle = 10
        , .tiMinDistance = 1000
        },
    [182] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1460
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1460_1460
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [183] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 653
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_653_653
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [184] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 699
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_699_699
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [185] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 970
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_970_970
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 500
        },
    [186] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 305
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_305_305
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [187] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 309
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_309_309
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [188] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 231
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_231_231
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [189] =
        { .idxCanBus = OSE_CAN_BUS_B8
        , .canId = 1530
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B8_frame_1530_1530
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [190] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1676
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1676_1676
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [191] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1491
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1491_1491
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [192] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1536
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1536_1536
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [193] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 621
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_621_621
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 10000
        , .tiMinDistance = 1000
        },
    [194] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 538
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_538_538
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [195] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1384
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1384_1384
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [196] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 21
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_21_21
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 50
        },
    [197] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 409
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_409_409
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 500
        },
    [198] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1148
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1148_1148
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [199] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1934
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1934_1934
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [200] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1538
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1538_1538
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [201] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1146
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1146_1146
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [202] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1025
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1025_1025
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [203] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1610
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1610_1610
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [204] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1315
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1315_1315
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [205] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 900
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_900_900
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [206] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 171
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_171_171
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 500
        },
    [207] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 240
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_240_240
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [208] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 178
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_178_178
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 100
        , .tiMinDistance = 10
        },
    [209] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 2031
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_2031_2031
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [210] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1935
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1935_1935
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [211] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1416
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1416_1416
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [212] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 950
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_950_950
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [213] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 734
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_734_734
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 100
        },
    [214] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1565
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1565_1565
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 50
        , .tiMinDistance = 10
        },
    [215] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1699
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1699_1699
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [216] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1698
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1698_1698
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 1000
        },
    [217] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1854
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1854_1854
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 500
        , .tiMinDistance = 50
        },
    [218] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1142
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1142_1142
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [219] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1007
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1007_1007
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [220] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1613
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1613_1613
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [221] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 627
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_627_627
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [222] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 973
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_973_973
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 50
        , .tiMinDistance = 50
        },
    [223] =
        { .idxCanBus = OSE_CAN_BUS_B9
        , .canId = 1362
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B9_frame_1362_1362
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 100
        , .tiMinDistance = 50
        },
    [224] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 612
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_612_612
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [225] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 5
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_5_5
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [226] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1477
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1477_1477
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 500
        , .tiMinDistance = 10
        },
    [227] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1604
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1604_1604
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [228] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 36
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_36_36
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [229] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 2001
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_2001_2001
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 20
        , .tiMinDistance = 10
        },
    [230] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 80
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_80_80
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [231] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 0
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_0_0
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [232] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1494
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1494_1494
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [233] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 537
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_537_537
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [234] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 741
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_741_741
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 5
        , .tiMinDistance = 10
        },
    [235] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1396
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1396_1396
        , .sendMode = cap_enumSendMode_mixed
        , .tiCycle = 1000
        , .tiMinDistance = 100
        },
    [236] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 207
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_207_207
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10000
        , .tiMinDistance = 10
        },
    [237] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1996
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1996_1996
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [238] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 1505
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_1505_1505
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 10
        , .tiMinDistance = 10
        },
    [239] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 26
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_26_26
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 1000
        , .tiMinDistance = 10
        },
    [240] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 515
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_515_515
        , .sendMode = cap_enumSendMode_regular
        , .tiCycle = 25
        , .tiMinDistance = 10
        },
    [241] =
        { .idxCanBus = OSE_CAN_BUS_B10
        , .canId = 677
        , .isExtId = false
        , .fctDoE2eValidation = ose_unpackAndCheck_B10_frame_677_677
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


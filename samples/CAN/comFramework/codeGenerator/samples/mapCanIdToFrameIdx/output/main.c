/**
 * @file main.c
 * The simple hnd-coded main function, which runs the other code in a few simple tests.
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
/* Module interface
 * Local functions
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "types.h"
#include "mci_mapCanIdToIdx.h"


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
 
 
/*
 * Function implementation
 */

signed int main(signed int noArgs, const char *pargAry[])
{
#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID != 0
    printf("This test function uses direct lookup for 11 Bit standard CAN IDs\n");
#else
    printf("This test function uses binary search in the map for all CAN IDs\n");
#endif
    
    unsigned int u;
    for(u=0; u<mci_noBuses; ++u)
    {
        printf( "Number of CAN frames transmitted on bus %u: %u\n"
              , u 
              , mci_mapFrameIdxByBusAndId_rowLengthAry[u]
              );
    }

    /* We "abuse" the pair of CAN ID and frame index for our test cases: The frame index is
       used as bus index. */
    const struct testCase_t
    {
        mci_pairCanIdAndIdx_t pairCanIdAndBusIdx;
        unsigned int expectedIdxFrame;
    } testCaseAry[] =
        {
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 0x000, .canId.u.isExtId = false},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 0x000, .canId.u.isExtId = false},
             .expectedIdxFrame = 36
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 0x000, .canId.u.isExtId = false},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 0xD7, .canId.u.isExtId = false},
             .expectedIdxFrame = 0
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 0xD7, .canId.u.isExtId = false},
             .expectedIdxFrame = 3
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 0xD7, .canId.u.isExtId = false},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 0x8e1722, .canId.u.isExtId = true},
             .expectedIdxFrame = 1
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 0x8e1722, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 0x8e1722, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 0x8e1522, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 0x8e1522, .canId.u.isExtId = true},
             .expectedIdxFrame = 30
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 0x8e1522, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 0x8d0022, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 0x8d0022, .canId.u.isExtId = true},
             .expectedIdxFrame = 35
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 0x8d0022, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 0x8f3222, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 0x8f3222, .canId.u.isExtId = true},
             .expectedIdxFrame = 9
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 0x8f3222, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 0x960a24, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 0x960a24, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 0x960a24, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 0x8c0124, .canId.u.isExtId = true},
             .expectedIdxFrame = 49
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 0x8c0124, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 0x8c0124, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 2047, .canId.u.isExtId = false},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 2047, .canId.u.isExtId = false},
             .expectedIdxFrame = 39
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 2047, .canId.u.isExtId = false},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 2048, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 2048, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 2048, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },

            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = 0x1fffffff, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = 0x1fffffff, .canId.u.isExtId = true},
             .expectedIdxFrame = 37
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = 0x1fffffff, .canId.u.isExtId = true},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_DUP, .canId.u.id = 100, .canId.u.isExtId = false},
             .expectedIdxFrame = 41
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_DUP, .canId.u.id = 500, .canId.u.isExtId = false},
             .expectedIdxFrame = 42
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_DUP, .canId.u.id = 101, .canId.u.isExtId = false},
             .expectedIdxFrame = 43
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_DUP, .canId.u.id = 400, .canId.u.isExtId = false},
             .expectedIdxFrame = 44
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_DUP, .canId.u.id = 200, .canId.u.isExtId = false},
             .expectedIdxFrame = 45
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_DUP, .canId.u.id = 200, .canId.u.isExtId = true},
             .expectedIdxFrame = 46
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_DUP, .canId.u.id = 0, .canId.u.isExtId = true},
             .expectedIdxFrame = 47
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_DUP, .canId.u.id = 0, .canId.u.isExtId = false},
             .expectedIdxFrame = 48
            },

#if 0            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .canId.u.id = , .canId.u.isExtId = },
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .canId.u.id = , .canId.u.isExtId = },
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .canId.u.id = , .canId.u.isExtId = },
             .expectedIdxFrame = 0xff
            },
#endif
        };
    
    const unsigned int noTestCases = sizeof(testCaseAry)/sizeof(testCaseAry[0]);
    for(u=0; u<noTestCases; ++u)
    {
        const struct testCase_t *pTestCase = &testCaseAry[u];
        const unsigned int idxFrame = mci_getIdxFrameByCanId
                                            ( /* idxBus */ pTestCase->pairCanIdAndBusIdx.idx
                                            , pTestCase->pairCanIdAndBusIdx.canId.u.id
                                            , pTestCase->pairCanIdAndBusIdx.canId.u.isExtId
                                            );
        if(idxFrame == pTestCase->expectedIdxFrame)
        {
            printf( "%03u) Test case succeeded", u+1);
            if(idxFrame < 0xff)
            {
                printf( ". CAN frame with ID %s%#x on bus %u has frame index %u\n"
                      , pTestCase->pairCanIdAndBusIdx.canId.u.isExtId? "x": ""
                      , (unsigned)pTestCase->pairCanIdAndBusIdx.canId.u.id
                      , (unsigned)pTestCase->pairCanIdAndBusIdx.idx
                      , idxFrame
                      );
            }
            else
            {
                printf( ". A CAN frame with ID %s%#x is not transmitted on bus %u\n"
                      , pTestCase->pairCanIdAndBusIdx.canId.u.isExtId? "x": ""
                      , (unsigned)pTestCase->pairCanIdAndBusIdx.canId.u.id
                      , (unsigned)pTestCase->pairCanIdAndBusIdx.idx
                      );
            }            
        }
        else
        {
            printf( "%03u) Test case failed"
                    ". We got frame index %u instead of %u for CAN frame with ID %s%#x on"
                    " bus %u\n"
                  , u+1
                  , idxFrame
                  , pTestCase->expectedIdxFrame
                  , pTestCase->pairCanIdAndBusIdx.canId.u.isExtId? "x": ""
                  , (unsigned)pTestCase->pairCanIdAndBusIdx.canId.u.id
                  , (unsigned)pTestCase->pairCanIdAndBusIdx.idx
                  );
        }            
    } /* End for(All test cases) */

    return 0;
    
} /* End of main */
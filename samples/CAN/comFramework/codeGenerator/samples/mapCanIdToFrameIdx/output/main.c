/**
 * @file main.c
 * The simple hnd-coded main function, which runs the other code in a few simple tests.
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
#include "mci_mapCanIdToFrameIdx.h"
#include "mci_getIdxFrameByCanId.h"


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
        mci_pairIdAndIdx_t pairCanIdAndBusIdx;
        unsigned int expectedIdxFrame;
    } testCaseAry[] =
        {
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 0x000},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 0x000},
             .expectedIdxFrame = 40
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 0x000},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 0xD7},
             .expectedIdxFrame = 0
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 0xD7},
             .expectedIdxFrame = 5
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 0xD7},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 0x8e1722},
             .expectedIdxFrame = 1
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 0x8e1722},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 0x8e1722},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 0x8e1522},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 0x8e1522},
             .expectedIdxFrame = 34
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 0x8e1522},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 0x8d0022},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 0x8d0022},
             .expectedIdxFrame = 39
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 0x8d0022},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 0x8f3222},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 0x8f3222},
             .expectedIdxFrame = 13
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 0x8f3222},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 0x960a24},
             .expectedIdxFrame = 4
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 0x960a24},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 0x960a24},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 0x8c0124},
             .expectedIdxFrame = 3
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 0x8c0124},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 0x8c0124},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 2047},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 2047},
             .expectedIdxFrame = 43
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 2047},
             .expectedIdxFrame = 0xff
            },
            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 2048},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 2048},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 2048},
             .expectedIdxFrame = 0xff
            },

            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = 0x1fffffff},
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = 0x1fffffff},
             .expectedIdxFrame = 41
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = 0x1fffffff},
             .expectedIdxFrame = 0xff
            },
#if 0            
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_RT_simplified, .id = },
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT_attributed, .id = },
             .expectedIdxFrame = 0xff
            },
            {.pairCanIdAndBusIdx = {.idx = mci_idxBus_CAN_RT, .id = },
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
                                            , /* id */     pTestCase->pairCanIdAndBusIdx.id
                                            );
        if(idxFrame == pTestCase->expectedIdxFrame)
        {
            printf( "%03u) Test case succeeded", u+1);
            if(idxFrame < 0xff)
            {
                printf( ". CAN frame with ID %#x on bus %u has frame index %u\n"
                      , (unsigned)pTestCase->pairCanIdAndBusIdx.id
                      , (unsigned)pTestCase->pairCanIdAndBusIdx.idx
                      , idxFrame
                      );
            }
            else
            {
                printf( ". A CAN frame with ID %#x is not transmitted on bus %u\n"
                      , (unsigned)pTestCase->pairCanIdAndBusIdx.id
                      , (unsigned)pTestCase->pairCanIdAndBusIdx.idx
                      );
            }            
        }
        else
        {
            printf( "%03u) Test case failed"
                    ". We got frame index %u instead of %u for CAN frame with ID %#x on"
                    " bus %u\n"
                  , u+1
                  , idxFrame
                  , pTestCase->expectedIdxFrame
                  , (unsigned)pTestCase->pairCanIdAndBusIdx.id
                  , (unsigned)pTestCase->pairCanIdAndBusIdx.idx
                  );
        }            
    } /* End for(All test cases) */

    return 0;
    
} /* End of main */
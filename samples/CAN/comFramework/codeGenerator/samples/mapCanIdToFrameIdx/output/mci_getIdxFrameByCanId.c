/**
 * @file mci_getIdxFrameByCanId.c
 * This is a hand-coded C file, which completes the auto-generated lookup table with the
 * functional code. The function offered in this implementation file actually is the only
 * global entry point we need.
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
 *   mci_getIdxFrameByCanId
 * Local functions
 *   comparePairsIdAndIdxById
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

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

/**
 * Comparison of two elements of the sorted lookup table. Used by bsearch to find the entry
 * with the matching CAN ID.\n
 *   See bsearch from the C standard library for more details.
 *   @return
 * The difference of the CAN ID in the first element and the CAN ID in the second element
 * is returned as a signed quantity. Overflow is impossible due to the restriction of CAN
 * IDs to a maximum of 29 Bit. (This is however double-checked by assertion.)
 *   @param pFirstElement
 * The typeless pointer to the first element of the comparsion. This is a pair of CAN ID
 * and associated frame index.
 *   @param pSecondElement
 * The typeless pointer to the second element of the comparsion. This is a pair of CAN ID
 * and associated frame index.
 */

static signed int comparePairsIdAndIdxById( const void *pFirstElement
                                          , const void *pSecondElement
                                          )
{
    /* Both (unsigned) operands should be lower or equal than INT_MAX, so the maximum
       difference would be absolute INT_MAX; which a safe negative representation exits
       for. The assertion is sufficient to exclude an overflow. */
    assert(((const mci_pairIdAndIdx_t*)pFirstElement)->id <= INT_MAX
           &&  ((const mci_pairIdAndIdx_t*)pSecondElement)->id <= INT_MAX
          );

    return (signed int)((const mci_pairIdAndIdx_t*)pFirstElement)->id
           - (signed int)((const mci_pairIdAndIdx_t*)pSecondElement)->id;
    
} /* End of comparePairsIdAndIdxById */




/**
 * Get the frame index as used by the CAN interface engine of the very frame, which is
 * transmitted on the given bus and which has the given CAN ID.
 *   @return
 * The function returns the frame index or (UInt8)-1 = 255 if no frame with given bus index
 * and CAN ID has been registered in the CAN interface engine.
 *   @param idxBus
 * The index of the bus. Please see enum mci_idxCanBus_t for details.
 *   @param canId
 * The CAN ID, which needs to be an 11 Bit standard ID. Extended IDs can't be handled by
 * this function. This is double-checked by assertion.
 *   @remark
 * The function builds on the data tables, which the code generator has generated from the
 * network database files.
 */

UInt8 mci_getIdxFrameByCanId( UInt8 idxBus
#if MCI_SUPPORT_EXTENDED_CAN_IDS == 0
                            , UInt16 canId
#else
                            , UInt32 canId
#endif
                            )
{
#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID != 0
    /* A direct lookup table for 11 Bit IDs is available. We have to apply it if possible. */
    if(canId < 0x800)
        return mci_getFrameIdxByCanBusAndStdId(idxBus, canId);
#endif
    /* Here we either have an extended CAN ID or there's no direct lookup table for
       standard IDs. We use the sorted map by applying a binary search on the row, which
       relates to our bus. */
    size_t noElements = mci_mapFrameIdxByBusAndId_rowLengthAry[idxBus];
    const mci_pairIdAndIdx_t keyElement = {.id = canId}
                           , *pFoundElement = bsearch( &keyElement
                                                     , mci_mapFrameIdxByBusAndId[idxBus]
                                                     , noElements
                                                     , sizeof(const mci_pairIdAndIdx_t)
                                                     , comparePairsIdAndIdxById
                                                     );
    if(pFoundElement != NULL)
    {
        assert(pFoundElement->id == canId);
        assert(pFoundElement->idx < (UInt8)-1);
        return (UInt8)pFoundElement->idx;
    }
    else
    {
        /* The CAN ID has not been found for the given bus index. */
        return (UInt8)-1;
    }
} /* End of mci_getIdxFrameByCanId */





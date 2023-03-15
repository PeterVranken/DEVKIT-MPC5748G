/**
 * @file mci_mapCanIdToIdx.c
 * This is a hand-coded C file, which completes the auto-generated lookup table with the
 * functional code. The function offered in this implementation file actually is the only
 * global entry point we need.
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
 *   mci_getFrameIdxByCanBusAndStdId
 *   mci_getIdxFrameByCanId
 * Local functions
 *   comparePairsIdAndIdxById
 */

/*
 * Include files
 */

#include "mci_mapCanIdToIdx.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "types.h"
#include "mci_mapCanIdToIdx_dataTables.h"


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
    assert(((const mci_pairCanIdAndIdx_t*)pFirstElement)->canId <= INT_MAX
           &&  ((const mci_pairCanIdAndIdx_t*)pSecondElement)->canId <= INT_MAX
          );

    return (signed int)((const mci_pairCanIdAndIdx_t*)pFirstElement)->canId
           - (signed int)((const mci_pairCanIdAndIdx_t*)pSecondElement)->canId;
    
} /* End of comparePairsIdAndIdxById */



#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID != 0
/**
 * Get the frame index as used by the CAN interface engine from the pair of CAN bus and
 * CAN standard ID. This function is restricted to 11 Bit CAN IDs.
 *   @return
 * The frame index is returned. If the pair of bus and CAN id does not designate a frame,
 * which had been registered in the CAN interface engine, thus a frame, which can't be
 * processed by the engine, then (uint8_t)-1 or 255 is returned instead of a valid index.
 *   @param idxBus
 * The index of the bus. Please see enum mci_idxCanBus_t for details.
 *   @param canId
 * The CAN ID, which needs to be an 11 Bit standard ID. Extended IDs can't be handled by
 * this function. This is double-checked by assertion.
 *   @remark
 * The frame index is returned as uint8_t. If more than 254 CAN frames should be in use
 * then the implemented table will not fit and the lookup function would fail. In this case
 * the code generation needs (simple) reconfiguration and the ROM consumption of the table
 * will be doubled.
 */
uint8_t mci_getFrameIdxByCanBusAndStdId(uint8_t idxBus, uint16_t canId)
{
    assert(idxBus < mci_noBuses  &&  canId < 0x800u);

    /* The fields of the table hold 0 for unset pairs and the CAN ID plus one otherwise. We
       just have to subtract one to handled registered and unregistered pairs of bus index
       and CAN ID. */
    return (uint8_t)(mci_lookupTableFrameIdxByBusAndStdId[idxBus][canId] - 1u);

} /* mci_getFrameIdxByCanBusAndStdId */
#endif



#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID == 0  ||  MCI_SUPPORT_EXTENDED_CAN_IDS != 0
/**
 * Get the frame index as used by the CAN interface engine of the very frame, which is
 * transmitted on the given bus and which has the given CAN ID.
 *   @return
 * The function returns the frame index or (uint8_t)-1 = 255 if no frame with given bus index
 * and CAN ID has been registered in the CAN interface engine.
 *   @param idxBus
 * The index of the bus. Please see enum mci_idxCanBus_t for details.
 *   @param canId
 * The CAN ID, which needs to be an 11 Bit standard ID. Extended IDs can't be handled by
 * this function. This is double-checked by assertion.
 *   @param isExtId
 * \a true if \a canId designates a 29 Bit extended CAN ID.
 *   @remark
 * The function builds on the data tables, which the code generator has generated from the
 * network database files.
 */
uint8_t mci_getIdxFrameByCanId( uint8_t idxBus
#if MCI_SUPPORT_EXTENDED_CAN_IDS == 0
                              , uint16_t canId
#else
                              , uint32_t canId
                              , bool isExtId
#endif
                              )
{
#if MCI_USE_DIRECT_LOOKUP_FOR_STD_ID != 0
    /* A direct lookup table for 11 Bit IDs is available. We have to apply it if possible. */
    if(canId < 0x800u
# if MCI_SUPPORT_EXTENDED_CAN_IDS != 0
       && !isExtId
# endif
      )
    {
        return mci_getFrameIdxByCanBusAndStdId(idxBus, canId);
    }
#endif

    /* Here we either have an extended CAN ID or there's no direct lookup table for
       standard IDs. We use the sorted map by applying a binary search on the row, which
       relates to our bus. */
    size_t noElements = mci_mapFrameIdxByBusAndId_rowLengthAry[idxBus];
    const mci_pairCanIdAndIdx_t keyElement = { .canId = MCI_CAN_ID( canId
#if MCI_SUPPORT_EXTENDED_CAN_IDS != 0
                                                                  , isExtId
#else
                                                                  , false
#endif
                                                                  ),
                                               .idx = 0u,
                                             };
    const mci_pairCanIdAndIdx_t * const pFoundElement = 
                                            bsearch( &keyElement
                                                   , mci_mapFrameIdxByBusAndId[idxBus]
                                                   , noElements
                                                   , sizeof(const mci_pairCanIdAndIdx_t)
                                                   , comparePairsIdAndIdxById
                                                   );
    if(pFoundElement != NULL)
    {
#if MCI_SUPPORT_EXTENDED_CAN_IDS != 0
        assert((pFoundElement->canId >> 1u) == canId
               &&  ((pFoundElement->canId & 1u) == 1u) == isExtId
              );
#else
        assert(pFoundElement->canId == canId);
#endif
        assert(pFoundElement->idx < (uint8_t)-1);
        return (uint8_t)pFoundElement->idx;
    }
    else
    {
        /* The CAN ID has not been found for the given bus index. */
        return (uint8_t)-1;
    }
} /* mci_getIdxFrameByCanId */
#endif




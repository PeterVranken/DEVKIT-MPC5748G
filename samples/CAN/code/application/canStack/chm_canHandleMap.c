/**
 * @file chm_canHandleMap.c
 * A map to retrieve the frame index of the CAN interface from the whatever handle of the
 * frame in the operating system. See cde_installMapOsHandleFrameToCdeIndex() and type \a
 * cde_mapOsHandleFrameToCdeIndex_t for details.\n
 *   This file implements a map for piecewise linear mapping. It can be applied, if it
 * holds for each CAN bus, that all Rx messages and all Tx messages both use handle pairs
 * (hOS, hIf) with hOS=hIf+k, where k is a signed integral constant, which may have an
 * individual value for each bus and between Rx and Tx.\n
 *   A second working assumption is that Rx and Tx messages of the same bus have disjunct
 * handle ranges, i.e. each Rx handle is lower than any Tx handle or vice versa, where this
 * ordering of ranges is decided with interpreting the operating system handles as unsigned
 * integral numbers.
 *   During frame registration, the module determines all required values k and it
 * double-checks if the made working assumptions about piecewise linear mappings are
 * fulfilled for all registered frames. 
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
/* Module interface
 * Local functions
 *   getIdxOffset
 *   updateHandleRanges
 */

/*
 * Include files
 */

#include "chm_canHandleMap.h"

#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include <typ_types.h>
#include "cde_canDispatcherEngine.h"


/*
 * Defines
 */

/** The number of required offsets. */
#define NO_OFFSETS      ((CHM_MAX_NO_CAN_BUSES) * 2u /* Rx+Tx */)

/** The undefined, still undetermined offset. */
#define INVALID_OFFSET  (INT_MAX)


/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
/** The array of all required offsets. A value of #INVALID_OFFSET indicates that the offset
    has not been determined yet. */
static signed int DATA_P1(_offsetAry)[NO_OFFSETS] =
{
    [0 ... (NO_OFFSETS-1u)] = INVALID_OFFSET,
};

/** The boundary between Rx and Tx handles for each bus. */
static struct rxTxBoundary_t
{
    /** A value in the range between Rx and Tx handles. */
    unsigned int boundary;
    
    /** \a true if OS handle values lesser or equal to \a boundary belong to Rx messages. */
    boolean_t isLEQInbound;
    
} _rxTxBoundaryAry[CHM_MAX_NO_CAN_BUSES] SECTION(.data.P1._rxTxBoundaryAry) =
    {
        [1 ... (CHM_MAX_NO_CAN_BUSES-1)] =
            {
               .boundary = 0u,
               .isLEQInbound = false,
            },
    };

/** Work dataset of the map build-up function chm_makeMapEntryOsHandleFrameToCdeIndex().
    The memory space is provided by the client code for temporary use. */
static struct chm_handleRanges_t * SBSS_P1(_rxTxRangesAry) = NULL;


/*
 * Function implementation
 */

/**
 * The offset lookup is a two-dimensional array lookup (bus and direction). We implement it
 * as a one-dimensional array in order to have optimized index computation for the typical
 * power-of-two values. Here's an inline implementation for getting the index to the right
 * offset.
 *   @return
 * Get the index of the related offset in \a _offsetAry.
 *   @param idxBus
 * The zero based index of the CAN bus as enumerated in the OS.
 *   @param isInbound
 * Transmission direction of the affected frame.
 */
static inline unsigned int getIdxOffset(unsigned int idxBus, boolean_t isInbound)
{
    unsigned int idxOffset;
    if(isInbound)
        idxOffset = idxBus;
    else
        idxOffset = idxBus + CHM_MAX_NO_CAN_BUSES;

    assert(idxOffset < sizeOfAry(_offsetAry));
    return idxOffset;

} /* getIdxOffset */



/**
 * Record the ranges of Rx and Tx handles by inspecting each registered frame. This
 * function is called for each registered frame to do so.
 *   @return
 * Get \a true if the handle of this frame still fits into the working model of piecewise
 * linear handle mapping without overlap between Tx and Rx.\n
 *   If only a single frame returns \a false during CAN stack initialization then it is
 * proven that the implemented mapping is insufficient for the given use case and not all of
 * the frames will later be properly delivered.
 *   @param idxBus
 * The zero based index of the bus the frame in question is transmitted on.\n
 *   @param osHandleFrame
 * The handle as it has got from the frame registration or initialization at the
 * operating system. With respect to ranges and possible range overlap, it is treated as an
 * unsigned integral number.
 *   @param isInbound
 * The transmission direction of the frame in question. 
 */
static boolean_t updateHandleRanges( unsigned int idxBus
                                   , unsigned int osHandleFrame
                                   , boolean_t isInbound
                                   )
{
    if(_rxTxRangesAry == NULL)
    {
        assert(false);
        return false;
    }

    /* Minimum and maximum of all ever seen OS Rx/Tx handles. */
    unsigned int minHOsRx = _rxTxRangesAry[idxBus].minHOsRx
               , maxHOsRx = _rxTxRangesAry[idxBus].maxHOsRx
               , minHOsTx = _rxTxRangesAry[idxBus].minHOsTx
               , maxHOsTx = _rxTxRangesAry[idxBus].maxHOsTx;

    if(isInbound)
    {
        /* This is an Rx frame. If we have already seen an Rx frame before then we
           enlarge the recorded Rx handle range and check if this doesn't lead to a
           violation of our assumptions. */
        if(minHOsRx <= maxHOsRx)
        {
            /* Update the Rx range. */
            if(osHandleFrame < minHOsRx)
                minHOsRx = osHandleFrame;
            else if(osHandleFrame > maxHOsRx)
                maxHOsRx = osHandleFrame;
        }
        else
        {
            /* This is the very first reported Rx frame. Set the range initially. */
            minHOsRx = osHandleFrame;
            maxHOsRx = osHandleFrame;
        }
    }
    else
    {
        /* This is an Tx frame. If we have already seen an Tx frame before then we
           enlarge the recorded Tx handle range and check if this doesn't lead to a
           violation of our assumptions. */
        if(minHOsTx <= maxHOsTx)
        {
            /* Update the Tx range. */
            if(osHandleFrame < minHOsTx)
                minHOsTx = osHandleFrame;
            else if(osHandleFrame > maxHOsTx)
                maxHOsTx = osHandleFrame;
        }
        else
        {
            /* This is the very first reported Tx frame. Set the range initially. */
            minHOsTx = osHandleFrame;
            maxHOsTx = osHandleFrame;
        }
    }

    /* After updating the ranges, we can check the assumptions and update the range
       boundary if found alright. */
    const boolean_t isRxRangeKnown = minHOsRx <= maxHOsRx
                  , isTxRangeKnown = minHOsTx <= maxHOsTx;
    boolean_t isLEQInbound
            , success = true;
    if(isRxRangeKnown && isTxRangeKnown)
    {
        isLEQInbound = maxHOsRx < minHOsTx;
        success = isLEQInbound ||  maxHOsTx < minHOsRx;
    }
    else if(isRxRangeKnown)
    {
        isLEQInbound = true;
    }
    else
    {
        assert(isTxRangeKnown);
        isLEQInbound = false;
    }

    unsigned int boundary;
    if(success)
    {
        if(isLEQInbound)
        {
            assert(isRxRangeKnown);
            boundary = maxHOsRx;
        }
        else
        {
            assert(isTxRangeKnown);
            boundary = maxHOsTx;
        }
    
        /* The new frame still fits into our pattern. We can update the internal recording
           and the global data structure. */
        _rxTxRangesAry[idxBus].minHOsRx = minHOsRx;
        _rxTxRangesAry[idxBus].maxHOsRx = maxHOsRx;
        _rxTxRangesAry[idxBus].minHOsTx = minHOsTx;
        _rxTxRangesAry[idxBus].maxHOsTx = maxHOsTx;
        
        _rxTxBoundaryAry[idxBus].boundary = boundary;
        _rxTxBoundaryAry[idxBus].isLEQInbound = isLEQInbound;
    }

    return success;
    
} /* updateHandleRanges */





/**
 * The call of this function is a prerequiste of using the map preparation
 * chm_makeMapEntryOsHandleFrameToCdeIndex() and thus of calling cde_registerFrame(): It
 * provides the work space to the registration process. After completion of the
 * registration process, this work space is no longer used.\n
 *   Letting the caller provide the work space, which is needed by this module, has been
 * decided for sake of saving expensive RAM. The memory is required only during
 * registration and the caller can easily provide some stack space for this temporary use
 * of the memory. If the module's implementation would provide the memory then it would
 * mean static allocation and useless memory consumption at runtime. (A reasonable
 * assumption is that no dynamic memory allocation and freeing is available in the embedded
 * environments, which are targetted by the CAN stack.)
 */
void chm_allocateWorkspaceForMapBuildup(struct chm_handleRanges_t *pProvidedMemory)
{
    _rxTxRangesAry = pProvidedMemory;

    unsigned int u;
    for(u=0; u<CHM_MAX_NO_CAN_BUSES; ++u)
    {
        _rxTxRangesAry[u] = (struct chm_handleRanges_t){ .minHOsRx = 1u,
                                                         .maxHOsRx = 0u,
                                                         .minHOsTx = 1u,
                                                         .maxHOsTx = 0u,
                                                       };
    }
} /* chm_allocateWorkspaceForMapBuildup */



/**
 * This function helps to prepare, fill, buildup the map. It is a callback from the frame
 * registration process and used to report a single association between operating system
 * handles for CAN bus and frame and the index, which is used as frame handle in the CAN
 * interface engine. This function is called once per registered frame as sub-routine of
 * cde_registerFrame().
 *   Return value:\n
 * The function will return \a true, if it succeeds. The implementation of
 * the map may be size or otherwise limited. If the map entry could not be made the
 * external function may return \a false. The CAN interface engine will assume that
 * the frame in question won't be processed later, it'll in turn discard its related
 * entries. If later at run-time an event relates to this frame then it'll be
 * ignored.\n
 *   For this implementation of a map, \a true is returned if the handle of this frame
 * still fits into the working model of piecewise linear handle mapping without overlap
 * between Tx and Rx.
 *   @param canId
 * The CAN ID of the frame in question. It is the value of the same parameter in the
 * call of the parent function cde_registerFrame().
 *   @param idxBus
 * The zero based index of the bus the frame in question is transmitted on. It is the
 * value of the same parameter in the call of the parent function cde_registerFrame().\n
 *   @param osHandleFrame
 * The handle as it has got from the frame registration or initialization at the
 * operating system. It is the value of the same parameter in the call of the parent
 * function cde_registerFrame().
 *   @param cdeIdxFrame
 * The zero based index of the frame as used inside the CAN interface implementation.
 * This value needs to be associated with the operating system's frame identification
 * (idxBus,osHandleFrame).
 *   @param isInbound
 * The transmission direction of the frame in question. This parameter is useless for
 * the pure lookup operation. The frame identification (idxBus,osHandleFrame) should
 * be unique without it and the lookup function \a fctMapOsHandleFrameToCdeIndex won't
 * make a statement about the transmission direction. The use case is a typical
 * optimization. In many integrations the only frame events will relate to frame
 * reception. If so, the map could silently ignore all outbound frames and save a
 * significant amount of space.\n
 *    It is the value of the same parameter in the call of the parent function
 * cde_registerFrame().
 *   @remark
 * This function is called in the system initialization phase, i.e. in a single
 * threaded, race condition free context.
 */
boolean_t chm_makeMapEntryOsHandleFrameToCdeIndex( unsigned long canId
                                                 , unsigned int idxBus
                                                 , cde_osHandleFrame_t osHandleFrame
                                                 , unsigned int cdeIdxFrame
                                                 , boolean_t isInbound
                                                 )
{
    boolean_t success = true; 
    
    /* Check if the OS handle fits into our working model. Reject the frame otherwise. */
    if(idxBus >= CHM_MAX_NO_CAN_BUSES)
        success = false;
    
    if(success)
    {
        /* We see another RX or Tx frame, which broadens the related known handle
           range; we need to record this information. */
        success = updateHandleRanges(idxBus, (unsigned)osHandleFrame, isInbound);
        assert(_rxTxBoundaryAry[idxBus].isLEQInbound == isInbound
               &&  (unsigned)osHandleFrame <= _rxTxBoundaryAry[idxBus].boundary
               ||  _rxTxBoundaryAry[idxBus].isLEQInbound != isInbound
                   &&  (unsigned)osHandleFrame > _rxTxBoundaryAry[idxBus].boundary
              );

        const unsigned int idxOffs = getIdxOffset(idxBus, isInbound);
        if(_offsetAry[idxOffs] == INVALID_OFFSET)
        {
            /* This is the first registration of a frame, which uses this offset. We
               calculate and store the offset. */
            _offsetAry[idxOffs] = (int)cdeIdxFrame - (int)osHandleFrame;

            /* The particular value INVALID_OFFSET is used as a flag and can't become a
               valid offset. */
            if(_offsetAry[idxOffs] == INVALID_OFFSET)
            {
                assert(false);
                success = false;
            }
        }
        else
        {
            /* We had already calculated the offset for this group from an earlier mapping
               pair. Now, we check if the same offset fits here, i.e. whether the basic
               working assumption of having a piecewise linear mapping is fulfilled for
               this system. */
            unsigned int idxFrameCalc;
            success = chm_mapOsHandleFrameToCdeIndex(&idxFrameCalc, idxBus, osHandleFrame);
            assert(!success ||  idxFrameCalc == cdeIdxFrame);
        }
    }
    
    return success;

} /* chm_makeMapEntryOsHandleFrameToCdeIndex */




/**
 * The actual map function. The map is queried for a frame index as internally used by
 * the dispatcher engine. The map query function is called as sub-routine of the frame
 * event notification cde_postFrameEvent().
 *   Return value
 * Normally, the frame index is returned by reference (see below) and the function
 * result is \a true. If the function doesn't find a suitable association it will
 * return \a false and the related frame event is lost.
 *   @param pIdxFrame
 * The result of the lookup operation is returned by reference. If the function
 * returns \a false then it may ignore this parameter.
 *   @param idxBus
 * The zero based index of the bus the frame in question is transmitted on.
 *   @param osHandleFrame
 * The operating system handle of the frame. It is assumed that this is the handle,
 * which is used in the (platform specific) frame reception interrupt or callback to
 * identify the frame.
 *   @remark
 * The external implementation of the map function needs to be fully reentrant. It can be
 * called concurrently by all CPU contexts, which can invoke cde_postFrameEvent() to report
 * a frame related event. Full re-entrance is considered a weak constraint for the
 * implementation insofar the mapping is a pure lookup operation in static, unchangeable
 * data. All possible handle associations have been defined in the race-condition free
 * initialization phase.
 *   @remark
 * The function is called as sub-routine of cde_postFrameEvent(), see there for more
 * details about re-entrance and CPU contexts.
 */
boolean_t chm_mapOsHandleFrameToCdeIndex( unsigned int *pIdxFrame
                                        , unsigned int idxBus
                                        , cde_osHandleFrame_t osHandleFrame
                                        )
{
    /* Check if the bus index fits.
         Note, this can become an assertion if your system setup is such that it rejects to
       startup in case at least one frame registration was rejected. (Which will usually be
       the case.) */
    if(idxBus >= CHM_MAX_NO_CAN_BUSES)
        return false;
    
    boolean_t const isInbound = (unsigned)osHandleFrame > _rxTxBoundaryAry[idxBus].boundary
                                !=  _rxTxBoundaryAry[idxBus].isLEQInbound;
    
    *pIdxFrame = (unsigned)((int)osHandleFrame + _offsetAry[getIdxOffset(idxBus, isInbound)]);
    return true;

} /* chm_mapOsHandleFrameToCdeIndex */
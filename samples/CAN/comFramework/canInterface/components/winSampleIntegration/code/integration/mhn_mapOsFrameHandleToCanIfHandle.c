/**
 * @file mhn_mapOsFrameHandleToCanIfHandle.c
 * This file implements a map, which associates the operating system handles of frames to
 * those of the CAN interface engine. The map is required for the use of the engine and
 * during initialization time the engine provides the map entries.
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
 *   mhn_assignFrameToDispatcher
 *   mhn_addOsToCdeHandlePair
 *   mhn_mapOsFrameHandleToCanIfHandle
 * Local functions
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "log_logger.h"
#include "main.h"
#include "oss_operatingSystemSimulation.h"
#include "cde_canDispatcherEngine.h"
#include "apt_applicationTask.h"
#include "mhn_mapOsFrameHandleToCanIfHandle.h"


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
 * Select the appropriate dispatcher for handling the events of a given frame. The decision
 * is mainly taken because of the latency time which needs to be achieved for the given
 * frame. Frames, which don't need a high reponsiveness can be handled by the dispatcher
 * with the lower regular clock tick, which saves CPU load.
 *   @param canId
 * The frame in question is identified by its CAN ID, ...
 *   @param osHandleBus
 * ... the (operating system) handle of the bus it is transmited on and ...
 *   @param osHandleFrame
 * ... its (operating system) handle.
 *   @param isInbound
 * The most relevant properties of the frame are passed to the function to support the
 * decision. This Boolean flag indicates the transmission direction.
 *   @param latencyTime
 * The most relevant properties of the frame are passed to the function to support the
 * decision. This time designation gives an idea of the required latency time in handling
 * the frame. Unit and particular meaning of the time designation depend on the (usually)
 * auto-coded frame registration code, but normally it's a time in ms taken from the frame
 * attributes in the network database.
 */

unsigned int mhn_assignFrameToDispatcher( uint32_t canId
                                        , uint16_t osHandleBus
                                        , cde_osHandleFrame_t osHandleFrame
                                        , boolean_t isInbound
                                        , signed int latencyTime
                                        )
{
    unsigned int idxDispatcher;
    if(latencyTime < 50)
        idxDispatcher = APT_IDX_DISPATCHER_10MS;
    else
        idxDispatcher = APT_IDX_DISPATCHER_100MS;
        
    LOG_INFO( main_hGlobalLogger    
            , "%.1f ms: "
              "mhn_assignFrameToDispatcher: "
              "Frame %lu, platform handle %lu, %s, bus %lu with latency time %i ms is"
              " assigned to dispatcher %u"
            , oss_tiSim / 1000.0
            , canId
            , (unsigned long)osHandleFrame
            , isInbound? "inbound": "outbound"
            , (unsigned long)osHandleBus
            , latencyTime
            , idxDispatcher
            );

    return idxDispatcher;
    
} /* End of mhn_assignFrameToDispatcher */



/**
 * Add a new entry to the map of handle mappings. The map is capable to return the frame
 * handles as used in the CAN interface if the operating system handle of the frame and the
 * bus it is transmitted on is given.
 *   @return
 * This map implementation will never fail to add a new entry and it always returns \a true.
 *   @param canId
 * The CAN ID of the registered frame.
 *   @param idxBus
 * The identification of the bus the frame is tranmitted on as a null based index.
 *   @param osHandleFrame
 * The identification of the frame as operating system handle.
 *   @param cdeIdxFrame
 * The handle of the registered frame as used in the CAN interface.\n
 *   This handle kind has some simple characteristics, which can help to find the easiest
 * possible implementation of the needed mapping table:\n
 *   - The handle is a linear null based index
 *   - The handles are assigned in the order of registration calls, i.e. this function will
 * always see the handles values starting with null in its first invokation, followed by
 * one, two and so forth
 *   @param isInbound
 * The transmission direction of the registered frame.\n
 *   In many real environments the mapping can be limited to received frames. Only if frame
 * related events for sent frames have to be processed then a full mapping for all frames
 * is required.
 *   @remark
 * This function is called during initialization of the CAN interface, which is done in a
 * race condition free, single threaded context. This function is called repeatedly for
 * each known frame but the calls will be strictly sequential.
 */
boolean_t mhn_addOsToCdeHandlePair( unsigned long canId ATTRIB_UNUSED
                                  , unsigned int idxBus ATTRIB_UNUSED
                                  , cde_osHandleFrame_t osHandleFrame ATTRIB_DBG_ONLY
                                  , unsigned int cdeIdxFrame ATTRIB_DBG_ONLY
                                  , boolean_t isInbound ATTRIB_UNUSED
                                  )
{
    /* In our simple example the simulated OS and the engine both use null based linear
       indexes in the order of registration, or identical handles with other words. We just
       check this but don't store the handle.
         In a real environment it often is as simple but not necessarily. If true mapping
       is required one can let the code generation support the implementation of the map.
       Dynamically allocated data structures are generally undesired in embedded
       programming but the code generator can at least tell at compile time how many
       entries the mapping table will have. This supports simple implementations of lookup
       tables or binary search tables with static arrays. In our sample integration the
       code generator produces among more the defines CST_NO_CAN_FRAMES,
       CST_NO_CAN_FRAMES_SENT, CST_NO_CAN_FRAMES_RECEIVED.
         In many real environments the mapping can be limited to the received frames. Only
       if frame related events for sent frames have to be processed then a full mapping for
       all frames is required.
         Which mapping algorithm is best can't be answered in general but depends on the
       range and distribution of the numeric values of the handles. */
    assert((unsigned int)osHandleFrame == cdeIdxFrame);
    
    /* The implementation of a mapping table in a real environment can be further supported
       by the simple pattern of the frame handles in the CAN engine: They will always begin
       with zero and then grow by one in each call of this function. */
#ifdef DEBUG
    static unsigned int assertIncOfIfHandles_ = 0;
    assert(assertIncOfIfHandles_ == cdeIdxFrame);
    ++ assertIncOfIfHandles_;
#endif

    return true;
    
} /* End of mhn_addOsToCdeHandlePair */




/**
 * This function implements a map, which associates the operating system handles of frames
 * to those of the CAN interface engine (which span a linear, null based index). The map is
 * required for the use of the engine and during initialization time the engine provides
 * the map entries.
 *   @return
 * \a true, if a mapping could be found, else \a false.
 *   @param pCdeIdxFrame
 * The index of the frame as required by the API of the CAN interface engine is returned by
 * reference.
 *   @param osHandle
 * The handle as used by the operating system.
 */

boolean_t mhn_mapOsFrameHandleToCdeIdx( unsigned int *pCdeIdxFrame
                                      , unsigned int idxBus ATTRIB_DBG_ONLY
                                      , cde_osHandleFrame_t osHandle
                                      )
{
    /* In our simple example the simulated OS and the engine both use null based linear
       indexes in the order of registration, or identical handles with other words. We had
       double-checked this during the registration process and can now simply return a copy
       of the OS handle as CAN interface handle. */
    assert(idxBus == OSS_CAN_BUS_PT);
    *pCdeIdxFrame = (unsigned int)osHandle;
    return true;

} /* End of mhn_mapOsFrameHandleToCanIfHandle */





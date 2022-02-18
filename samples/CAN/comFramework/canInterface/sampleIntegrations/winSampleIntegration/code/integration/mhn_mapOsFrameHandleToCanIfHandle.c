/**
 * @file mhn_mapOsFrameHandleToCanIfHandle.c
 * This file implements a map, which associates the operating system handles of frames to
 * those of the CAN interface engine. The map is required for the use of the engine and
 * during initialization time the engine provides the map entries.
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
 *   mhn_initModule
 *   mhn_assignFrameToDispatcher
 *   mhn_addOsToEdeHandlePair
 *   mhn_mapOsFrameHandleToEdeIdx
 * Local functions
 *   add
 *   get
 */

/*
 * Include files
 */

#include "mhn_mapOsFrameHandleToCanIfHandle.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "log_logger.h"
#include "main.h"
#include "oss_operatingSystemSimulation.h"
#include "apt_applicationTask.h"
#include "cst_canStatistics.h"


/*
 * Defines
 */

/** The number of implemented map objects. Each dispatcher object has its own handle space
    and requires its own map object. */
#define NO_MAP_INSTANCES        (APT_NO_DISPATCHER_SYSTEMS)

/** The representation of an invalid, uninitialized event handle. */
#define UNDEFINED_EV_HANDLE     (INT_MAX)

/*
 * Local type definitions
 */

/** A map object. */
typedef struct handleMap_t
{
    /** Our mapping is a one-by-one with offset. The only instance specific element is the
        offset. It is edeIdxEv = osFrameHandle + offset. */
    signed int offset;

} handleMap_t;


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** All our maps. */
static handleMap_t _mapAry[NO_MAP_INSTANCES] =
{
    [0 ... NO_MAP_INSTANCES-1] = {.offset = UNDEFINED_EV_HANDLE},
};

/** The only, global sender map, which direct the frames Rx notifications to the
    appropriate dispatcher. For sake of most simple mapping, we have an array element for
    all CAN frames, including Tx. */
static unsigned int _idxSenderPortAry[CST_NO_CAN_FRAMES];

/*
 * Function implementation
 */

/**
 * Add a key, value pair to the map.
 *   @param idxMap
 * The affected map instance as zero based index into an array of all instances.
 *   @param key_osHandle
 * The key of the lookup operation: The abstract handle of an event.
 *   @param value_edeIdx
 * The desired result of the lookup operation: The event source object inside the
 * dispatcher engine as zero based index into an array of all objects.
 */
static bool add( unsigned int idxMap
               , ede_senderHandleEvent_t key_osHandle
               , unsigned int value_edeIdx
               )
{
    assert(idxMap < NO_MAP_INSTANCES);
    handleMap_t * const pMap = &_mapAry[idxMap];

    /* Either this is the first call and we have to remind the apparent offset... */
    if(pMap->offset == UNDEFINED_EV_HANDLE)
    {
        pMap->offset = (signed int)value_edeIdx - (signed int)key_osHandle;
        assert(pMap->offset != UNDEFINED_EV_HANDLE);
        LOG_INFO( main_hGlobalLogger
                , "%.1f ms: "
                  "mhn::add: "
                  "Build-up handle map: hInstance %u has handle offset: %d\n"
                , oss_tiSim / 1000.0
                , idxMap
                , pMap->offset
                );
        return true;
    }
    /* ... or we just have to double-check if our implicit mapping really fits. */
    else if(pMap->offset == (signed int)value_edeIdx - (signed int)key_osHandle)
    {
        return true;
    }
    else
    {
        assert(false);
        return false;
    }
} /* add */



/**
 * Get the value for a key, i.e. the internally used index from an OS event handle.
 *   @return
 * The result of the lookup operation: The event source object inside the dispatcher engine
 * as zero based index into an array of all objects.
 *   @param idxMap
 * The map instance to use for the lookup operation as zero based index into an array of
 * all instances.
 *   @param key_osHandle
 * The key of the lookup operation: The abstract handle of an event.
 */
static unsigned int get(unsigned int idxMap, ede_senderHandleEvent_t key_osHandle)
{
    assert(idxMap < NO_MAP_INSTANCES);
    return (unsigned int)((signed int)key_osHandle + _mapAry[idxMap].offset);
}


/**
 * Initialze the module. All map instances are created initially empty.
 */
void mhn_initModule(void)
{
    for(unsigned int u=0u; u<NO_MAP_INSTANCES; ++u)
        _mapAry[u].offset = UNDEFINED_EV_HANDLE;

    for(unsigned int u=0u; u<CST_NO_CAN_FRAMES; ++u)
        _idxSenderPortAry[u] = UINT_MAX;

} /* mhn_initModule */


/**
 * Select the appropriate dispatcher for handling the events of a given frame. The decision
 * is mainly taken because of the latency time which needs to be achieved for the given
 * frame. Frames, which don't need a high reponsiveness can be handled by the dispatcher
 * with the lower regular clock tick, which saves CPU load.
 *   @return
 * Get either #APT_IDX_DISPATCHER_SYSTEM_10MS or #APT_IDX_DISPATCHER_SYSTEM_100MS, the
 * dispatcher to use for the given message.
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
unsigned int mhn_assignFrameToDispatcher( cev_canId_t canId
                                        , uint16_t osHandleBus
                                        , ede_senderHandleEvent_t osHandleFrame
                                        , bool isInbound
                                        , signed int latencyTime
                                        )
{
    unsigned int idxDispatcher;
    if(latencyTime < 50)
        idxDispatcher = APT_IDX_DISPATCHER_SYSTEM_10MS;
    else
        idxDispatcher = APT_IDX_DISPATCHER_SYSTEM_100MS;

    LOG_INFO( main_hGlobalLogger
            , "%.1f ms: "
              "mhn_assignFrameToDispatcher: "
              "Frame %lu (%s), platform handle %lu, %s, bus %lu with latency time %i ms is"
              " assigned to dispatcher %u"
            , oss_tiSim / 1000.0
            , canId.id
            , canId.isExtId? "ext": "std"
            , (unsigned long)osHandleFrame
            , isInbound? "inbound": "outbound"
            , (unsigned long)osHandleBus
            , latencyTime
            , idxDispatcher
            );

    return idxDispatcher;

} /* mhn_assignFrameToDispatcher */



/**
 * Add a new entry to the map of handle mappings. The map is capable to return the frame
 * handles as used in the CAN interface if the operating system handle of the frame and the
 * bus it is transmitted on is given.
 *   @return
 * This map implementation will never fail to add a new entry and it always returns \a true.
 *   @param hInstance
 * The handle of the map to use. (Each dispatcher has its own index space and uses a
 * dedicated map instance.)
 *   @param kindOfEvent
 * Kind of external event. In this sample, it can be either #APT_EV_RX_CAN_MSG,
 * #APT_EV_BUS_OFF or #APT_EV_RECOVERED_FROM_BUS_OFF.
 *   @param senderHandleEvent
 * The identification of an external event of given kind, as known and used by the
 * (external) event source. In this sample, only events of kind #APT_EV_RX_CAN_MSG are
 * distinguished by a handle. For all other kinds of events the handle is ignored.
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
bool mhn_addOsToEdeHandlePair( uintptr_t hInstance
                             , ede_kindOfEvent_t kindOfEvent
                             , ede_senderHandleEvent_t senderHandleEvent
                             , unsigned int idxEdeEventSrc
                             )
{
    /* In this example, and similar to many real environments, only CAN message related
       events use a handle space. All other events stand for themselves, they are fully
       characterized by the kind of event. Mapping becomes most simple if we register these
       events first - then we get a priori known, fixed internal indexes for those and the
       mapping is a simple one-by-one. */
    if((unsigned int)kindOfEvent < APT_EV_RX_CAN_MSG)
    {
        assert((unsigned int)kindOfEvent == idxEdeEventSrc);
        return true;
    }

    /* All remaining events are CAN message related events, which require a true handle
       mapping. We delegate the call to our simple map implementation. */
    return add(hInstance, senderHandleEvent, idxEdeEventSrc);

} /* mhn_addOsToEdeHandlePair */




/**
 * This function implements a map, which associates the externally defined handles of
 * external events to the indexes of the event source as used by the event dispatcher
 * engine (which span a linear, null based index). The map is required for the use of the
 * engine and during initialization time the engine provides the map entries.
 *   @return
 * \a true, if a mapping could be found, else \a false.
 *   @param hInstance
 * The handle of the map to use. (Each dispatcher has its own index space and uses a
 * dedicated map instance.)
 *   @param pIdxEdeEventSrc
 * The index of the event source as required by the event dispatcher engine is returned by
 * reference if the function returns \a true.
 *   @param kindOfEvent
 * Kind of external event. In this sample, it can be either #APT_EV_RX_CAN_MSG,
 * #APT_EV_BUS_OFF or #APT_EV_RECOVERED_FROM_BUS_OFF.
 *   @param senderHandleEvent
 * The handle of the event. In this sample, event handles are used only to distinguish
 * events of kind #APT_EV_RX_CAN_MSG, so it's either a don't care or the handle of the CAN
 * message, as used by the operating system.
 *   @param hDispatcher
 * The dispatcher engine using the given map instance.
 */
bool mhn_mapOsFrameHandleToEdeIdx( uintptr_t hInstance
                                 , unsigned int * pIdxEdeEventSrc
                                 , ede_kindOfEvent_t kindOfEvent
                                 , ede_senderHandleEvent_t senderHandleEvent
                                 )
{
    /* In this example, and similar to many real environments, only CAN message related
       events use a handle space. All other events stand for themselves, they are fully
       characterized by the kind of event. Mapping becomes most simple if we register these
       events first - then we get a priori known, fixed internal indexes for those and the
       mapping is a simple one-by-one. */
    if((unsigned int)kindOfEvent < APT_EV_RX_CAN_MSG)
        *pIdxEdeEventSrc = (unsigned int)kindOfEvent;
    else
    {
        /* All remaining events are CAN message related events, which require a true handle
           mapping. We delegate the call to our simple map implementation. */
        *pIdxEdeEventSrc = get(hInstance, senderHandleEvent);
    }

    return true;

} /* mhn_mapOsFrameHandleToEdeIdx */


/**
 * Add a key, value pair to the sender-side map, which directs CAN events to the right
 * dispatcher.
 *   @return
 * \a true if the pair could be added to the map, \a false otherwise.
 *   @param hInstance
 * The handle of the map to use. Is ignored, we have only a single sender and accordingly
 * only a single map instance.
 *   @param kindOfEvent
 * Kind of event and handle of event characterize the event or notification to send. Here
 * is the kind of event.
 *   @param senderHandleEvent
 * Kind of event and handle of event characterize the event or notification to send. Here
 * is the sender's handle of the event.
 *   @param idxPort
 * The zero based index of the port to use. Relates to the ports of the very sender object,
 * which uses this particular map instance.
 */
bool mhn_addMapEntrySenderEvHandleToSenderPortIndex
                                        ( uintptr_t hInstance ATTRIB_DBG_ONLY
                                        , unsigned int kindOfEvent
                                        , ede_senderHandleEvent_t senderHandleEvent
                                        , unsigned int idxPort
                                        )
{
    assert(hInstance == 0u  &&  idxPort < APT_NO_DISPATCHER_SYSTEMS);
    if(kindOfEvent == APT_EV_RX_CAN_MSG)
    {
        if((unsigned int)senderHandleEvent < CST_NO_CAN_FRAMES)
        {
            assert(_idxSenderPortAry[(unsigned int)senderHandleEvent] == UINT_MAX);
            _idxSenderPortAry[(unsigned int)senderHandleEvent] = idxPort;
            return true;
        }
    }
    return false;    

} /* mhn_addMapEntrySenderEvHandleToSenderPortIndex */



/**
 * Query for a CAN Rx event, which sender's port to use for.
 *   @return
 * Get \a true if the event is found in the map and a valid port index could be returned in
 * * \a pIdxPort. If \a false is returned then the queriying sender must not post the event
 * into any port.
 *   @param hInstance
 * The handle of the map to use. Is ignored, we have only a single sender and accordingly
 * only a single map instance.
 *   @param pIdxPort
 * If the function returned \a true then the zero based index of the port to use has been
 * placed in * \a pIdxPort. The index relates to the ports of the very sender object, which
 * uses this particular map instance.
 *   @param kindOfEvent
 * Kind of event and handle of event characterize the event or notification to send. Here
 * is the kind of event.
 *   @param senderHandleEvent
 * Kind of event and handle of event characterize the event or notification to send. Here
 * is the sender's handle of the event.
 */
bool mhn_mapSenderEvHandleToSenderPortIndex( uintptr_t hInstance ATTRIB_DBG_ONLY
                                           , unsigned int * const pIdxPort
                                           , unsigned int kindOfEvent
                                           , ede_senderHandleEvent_t senderHandleEvent
                                           )
{
    assert(hInstance == 0u);
    if(kindOfEvent == APT_EV_RX_CAN_MSG)
    {
        /* For CAN Rx events, we actively decide, which dispatcher to address to. The map
           implementation is a simple table lookup in this example, where we have a simple
           handle structure - a zero based index. */
        if((unsigned int)senderHandleEvent < CST_NO_CAN_FRAMES)
        {
            *pIdxPort = _idxSenderPortAry[(unsigned int)senderHandleEvent];
            assert(*pIdxPort < APT_NO_DISPATCHER_SYSTEMS);
            return true;
        }
        else
        {
            /* In this application a non-match surely is an implementation error. */
            assert(false);

            return false;
        }
    }
    else
    {
        /* All non CAN Rx events go to the 100ms dispatcher. These are the bus-off events. */
        assert(kindOfEvent == APT_EV_BUS_OFF  || kindOfEvent == APT_EV_RECOVERED_FROM_BUS_OFF);
        *pIdxPort = APT_IDX_DISPATCHER_SYSTEM_100MS;
        return true;
    }
} /* mhn_mapSenderEvHandleToSenderPortIndex */
/**
 * @file mci_mapBinarySearchCanId.c
 * This module provides a handle map, which relates the pair of kind-of-event and the 32
 * Bit integer representation of a CAN ID to the zero based index as used in the event
 * dispatcher engine.\n
 *   Use case are some rare platforms that report CAN events (typically reception event or
 * transmission complete event) by saying, which CAN ID was affected, rather than using a
 * (zero based) message handle or index. This is the right map implementation to use on
 * such systems: Kind of event will likely be the CAN bus index and the CAN ID is used as
 * the 32 Bit integer map key.\n
 *   The implementation supports the interfaces defined by the event sender and dispatcher
 * engine and the map is therefore most easy to use in this context. Just create a map
 * object and pass it to the constructor of sender or dispatcher object.\n
 *   The implementation of this map uses a binary search for the (huge) range of 32 Bit
 * integers. The complexity is O(log(n)), where n is the number of messages on a given bus.
 * For standard CAN IDs, it is an option to apply a direct lookup table instead, which
 * improves complexity to O(1), at the cost of a ROM table with 2048 entries per CAN bus.
 * Which technique to apply to standard CAN IDs is a compile time decision.\n
 *   The binary search requires a sorted data table per CAN bus with all CAN IDs, which are
 * in use on that bus. The straigh-forward decision is to use map API to build-up this
 * table during the frame registration. While easy, it is not desirable, as it would cost a
 * lot of expensive RAM. Instead, the concept is to let the comFramework code generator
 * make the required tables in ROM. Therefore, this map implementation is no longer
 * self-contained, it'll compile and work only, if the data tables are in place. This will
 * normally mean that you are going to integrate the code generation templates from sample
 * "mapCanIdToFrameIdx" of the code generator into your project.\n
 *   Most use cases will have a few kinds of event, which know an event handle for further
 * distinction of events of the kind. (CAN: Message Rx and Tx events.) Many other events
 * won't use a handle but stand for themselves. (CAN: Bus-off, bus on) To support these
 * without wasting useless lookup RAM, the implementation offers an alternative, "simple"
 * mapping: A single map value is stored for each of these kinds of events.
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
/* Module interface
 *   mci_createMapBinarySearchCanId
 * Local functions
 *   comparePairsIdAndIdxById
 *   mci_getIdxByCanId
 *   addKeyValuePair
 *   getValue
 */

/*
 * Include files
 */

#include "mci_mapBinarySearchCanId.h"

#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "ede_basicDefinitions.h"
#include "ede_externalInterfaces.h"
#include "mem_malloc.h"

#define MCI_SUPPORT_EXTENDED_CAN_IDS 1
#include "mci_ifMapBinarySearchCanId.h"

/*
 * Defines
 */

/* The software is written as portable as reasonably possible. This requires the awareness
   of the C language standard it is compiled with.
     With respect to the language feature C11 and C17 are identical. We combine the in one
   switch. */
#if defined(__STDC_VERSION__)
# if (__STDC_VERSION__)/100 == 2017
#  define _STDC_VERSION_C17
#  define _STDC_VERSION_C17_C11
# elif (__STDC_VERSION__)/100 == 2011
#  define _STDC_VERSION_C11
#  define _STDC_VERSION_C17_C11
# elif (__STDC_VERSION__)/100 == 1999
#  define _STDC_VERSION_C99
# endif
#endif

/** The reserved value "uninitialized" for those kinds of events, which don't make use of
    of a sender handle. */
#define INVALID_MAP_VALUE   ((unsigned)(1ull<<(sizeof(mci_uintMapValue_t)*8u) - 1ull))

/*
 * Local type definitions
 */

/** One instance of the map. */
typedef struct mapInstance_t
{   
    /** To get smaller objects, a union merges the data space for simple mapping and true
        binary serach mapping of CAN IDs. */
    union
    {
        /** The map value in case of simple mapping. */
        mci_uintMapValue_t simpleMapValue;
        
        /** For non-simple mapping: The number of entries in lookup table \a
            mapExtCanIdToEdeIdxAry. */
        unsigned int noExtCanIds;

    } u;

    /** The lookup table for standard CAN IDs or NULL if all CAN IDs are handled via binary
        search. Index into the table is the 11 Bit CAN ID, array entry is the wanted zero
        based index of the message in the event dispatcher system. */
    const mci_uintMapValue_t *mapStdCanIdToEdeIdxAry;

    /** The lookup table for extended CAN IDs (for standard IDs, too, if \a
        mapStdCanIdToEdeIdxAry is NULL), or NULL if the map instance is of kind "simple
        mapping". */
    const mci_pairCanIdAndIdx_t *mapExtCanIdToEdeIdxAry;

} mapInstance_t;

/** The map object. */
typedef struct map_t
{
    /** The number of supported kinds of events. */
    unsigned int noInstances;
    
    /** For each kind of event: The related map instance.\n
          The array is implemented as flexible array member. */
    mapInstance_t mapInstanceAry[];
    
} map_t;


/*
 * Local prototypes
 */

static bool getValue( uintptr_t hMap
                    , unsigned int * pValue
                    , ede_kindOfEvent_t kindOfEvent
                    , ede_senderHandleEvent_t senderHandleEvent
                    );

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
    
} /* comparePairsIdAndIdxById */




/**
 * Search the given sorted table of all CAN IDs for a particular ID.
 *   @return
 * The function returns \a true if the key (CAN ID) could be found in the table and \a
 * false otherwise.
 *   @param[out] pValue
 * If the function returns \a true then the index associated with the CAN ID \a canId is
 * returned by reference.
 *   @param mapExtCanIdToEdeIdxAry
 * The given lookup table, which contains all CAN IDs is rising order.
 *   @param sizeOfMap
 * The number of entries in table \a mapExtCanIdToEdeIdxAry.
 *   @param canId
 * The CAN ID to search for.
 */
static bool getIdxByCanId( unsigned int * const pValue
                         , const mci_pairCanIdAndIdx_t mapExtCanIdToEdeIdxAry[]
                         , unsigned int sizeOfMap
                         , mci_canId_t canId
                         )
{
    /* We apply the binary search from the C standard lib on the given, sorted array. */
    const size_t noElements = sizeOfMap;
    const mci_pairCanIdAndIdx_t key = {.canId = canId, .idx = 0,};
    const mci_pairCanIdAndIdx_t *pFoundElement = bsearch( &key
                                                        , /* table */ mapExtCanIdToEdeIdxAry
                                                        , noElements
                                                        , sizeof(const mci_pairCanIdAndIdx_t)
                                                        , comparePairsIdAndIdxById
                                                        );
    if(pFoundElement != NULL)
    {
        assert(pFoundElement->canId == canId);
        *pValue = (unsigned)pFoundElement->idx;
        return true;
    }
    else
    {
        /* The CAN ID has not been found for the given bus index. */
        return false;
    }
} /* getIdxByCanId */




/**
 * This function helps to prepare the map.\n
 *   1. Use case mapping external events to registered event sources:\n
 *   A single association as appears in each event registration is added to the map.
 * This function is called once per registered event source as sub-routine of
 * ede_registerEventSource().\n
 *   May be NULL. In many environments, the required map is trivial (e.g. the
 * identity) or known (and generated as ROM table) and no code is required to built-up
 * the map.\n
 *   2. Use case mapping external events to a sender's port:\n
 *   The function is currently not called by the dispatcher engine or sender
 * implementation. The integration code is in charge of providing the map contents and
 * it may or may not make use of this function to buildup the map.\n
 *   May be NULL to indicate that operation is not required.\n
 *   @return
 * The function will return \a true, if the new key, value pair could be considered.
 * The implementation of the map may be limited by size or otherwise. If the map entry
 * could not be made the external function may return \a false and, later at run-time,
 * the sender or dispatcher engine will ignore all events, which origin from the
 * related event source.
 *   @param hMap
 * This is the identification of the map object to use.
 *   @param kindOfEvent
 * An event is characterized by its kind and by the sender's handle. The meaning of both
 * values is widely transparent to sender and dispatcher engine. They will be defined by
 * the integrating environment. For the intended use case of this map type, the principal
 * kind of event would be "CAN Rx event on bus X" and sender handle would be the CAN ID,
 * represented as an object of type mci_canId_t.
 *   @param senderHandleEvent
 * See \a kindOfEvent.
 *   @param mapValue
 * The value of the pair to add to the map. This value needs to be returned by 
 * getValue() if the same event characterization is provided.\n
 *   Use cases: It's either the zero based index of a registered event source or the
 * zero based index of a sender's port.
 *   @remark
 * This function is called in the system initialization phase, i.e. in a single
 * threaded, still race condition free context.
 *   @note
 * For map instance, which are not "simple", the map implementation makes use of externally
 * defined ROM data tables. It's therefore not possible to influence the map contents by
 * calling this method. The method is offered nonetheless: It is used to double-check the
 * ROM data tables. Each "added" pair is compared against these tables and the function
 * returns \a false if it is not properly represented in these tables.
 */
static bool addKeyValuePair( uintptr_t hMap
                           , ede_kindOfEvent_t kindOfEvent
                           , ede_senderHandleEvent_t senderHandleEvent
                           , unsigned int mapValue
                           )
{
    map_t * const pMap = (map_t*)hMap;
    if(kindOfEvent >= pMap->noInstances)
    {
        EDE_ASSERT(false);
        return false;
    }

    /** Each kind of event has its own map instance. */
    mapInstance_t * const pMapInstance = &pMap->mapInstanceAry[kindOfEvent];
    
    /* Do we need to apply the actual binary search mapping or the simple mapping? */
    const bool isSimpleMapping = pMapInstance->mapExtCanIdToEdeIdxAry == NULL;
    
    if(isSimpleMapping)
    {
        /* Events of given kind don't use a handle. Their "kind of event" stands for
           itself. This map implementation supports those events by simply storing the
           associated map value. */
           
        /* Reject the key-value pair if the map value doesn't fit into our representation. */
        if(mapValue >= INVALID_MAP_VALUE)
            return false;

        if(pMapInstance->u.simpleMapValue == INVALID_MAP_VALUE)
        {
            /* Map value had not been defined yet for the given key. Set it now. */
            pMapInstance->u.simpleMapValue = mapValue;
        }    
        else
        {
            /* The mapping result had already been determined and this is a (somewhat
               unexpected) re-definition. We need to check if identical and reject the pair
               if not. */
            if(pMapInstance->u.simpleMapValue != mapValue)
            {
                EDE_ASSERT(false);
                return false;
            }
        }
        EDE_ASSERT(pMapInstance->u.simpleMapValue != INVALID_MAP_VALUE);
    }
    else
    {
        /* We can't add something to the const external data tables, but we can prove that
           their contents meet the expectations. We can run our own getValue method as it
           is guaranteed that the complete data tables do exist from the beginning. */
        unsigned int value;
        const bool keyFound = getValue(hMap, &value, kindOfEvent, senderHandleEvent);
        if(!keyFound ||  value != mapValue)
        {
            EDE_ASSERT(false);
            return false;
        }

    } /* if(Simple mapping or normal binary search mapping?) */

    return true;   

} /* addKeyValuePair */



/**
 * The map lookup operation. The index associated with an external event is queried.\n
 *   1. Use case mapping external events to registered event sources:\n
 *   The requested index is that of an event source as internally used in the
 * dispatcher system. The map query function is called as sub-routine of the
 * dispatching operation, ede_dispatcherMain().\n
 *   2. Use case mapping external events to a sender's port:\n
 *   The requested index is that of a port of the querying sender. The map query
 * function is called as sub-routine of sending an event, ede_postEvent().\n
 *   Must not be NULL.
 *   @return
 * Normally, the requested index is returned by reference (see below) and the function
 * result is \a true. If the function doesn't find a suitable association it will
 * return \a false and the related event is lost.
 *   @param hMap
 * This is the identification of the map instance to use. The data type
 * uintptr_t is such that the implementation of the map can hide an index into an
 * array of objects or a pointer to an object behind this value. See field \a
 * hInstance, too.\n
 *   1. Use case mapping external events to registered event sources:\n
 *   Each dispatcher system has its own index space for event sources and will apply a
 * dedicated map.\n
 *   2. Use case mapping external events to a sender's port:\n
 *   Each sender has its own index space for its individual ports and it'll use a
 * dedicated, related map instance.
 *   @param pValue
 * The result of the lookup operation is returned by reference. If the function
 * returns \a false then it may ignore this parameter.
 *   @param kindOfEvent
 * First element of characterizing the event source under progress. See argument of
 * same name of addKeyValuePair() for more details.
 *   @param senderHandleEvent
 * Second element of characterizing the event source under progress. See argument of
 * same name of addKeyValuePair() for more details.
 *   @remark
 * The external implementation of the map function needs to be reentrant only with
 * respect to different map instances. There won't be concurrent calls for one and the
 * same instance.
 */
static bool getValue( uintptr_t hMap
                    , unsigned int * pValue
                    , ede_kindOfEvent_t kindOfEvent
                    , ede_senderHandleEvent_t senderHandleEvent
                    )
{
    map_t * const pMap = (map_t*)hMap;
    if(kindOfEvent >= pMap->noInstances)
    {
        EDE_ASSERT(false);
        return false;
    }

    /** Each kind of event has its own map instance. */
    const mapInstance_t * const pMapInstance = &pMap->mapInstanceAry[kindOfEvent];
    
    /* Do we need to apply the actual binary search mapping or the simple mapping? */
    const bool isSimpleMapping = pMapInstance->mapExtCanIdToEdeIdxAry == NULL;
    
    if(isSimpleMapping)
    {
        /* Events of given kind don't use a handle. Their "kind of event" stands for
           itself. This map implementation supports those events by simply returning the
           stored associated value. */

        if(pMapInstance->u.simpleMapValue != INVALID_MAP_VALUE)
            *pValue = (unsigned)pMapInstance->u.simpleMapValue;
        else
        {
            /* The largest unsigned value is unused and has the meaning of "mapping not yet
               set". */
            EDE_ASSERT(false);
            return false;
        }
    }
    else
    {
        /* Events of given kind require handle mapping. */
        
        /* For this particular map, the sender event handle has a pre-defined structure:
           The 32 Bit integer is an agglomeration of CAN ID and Boolean isExtended. Decode
           it. */
        const mci_canId_t canId = (mci_canId_t)senderHandleEvent;

        if(!MCI_GET_IS_EXT_ID(canId) && pMapInstance->mapStdCanIdToEdeIdxAry != NULL)
        {
            /* The map defines a direct lookup table for the limited range of standard CAN
               IDs. This leads to very fast lookup. */
            EDE_ASSERT(MCI_GET_CAN_ID(canId) < 0x800u);
            const unsigned int idxInAry = MCI_GET_CAN_ID(canId) & 0x7FFu;
            *pValue = (unsigned)pMapInstance->mapStdCanIdToEdeIdxAry[idxInAry];
        }
        else
        {
            /* We apply a binary search on the given, external, constant data tables, which
               have a pre-defined, known structure. (By means of an interface, which is
               shared between map implementation of table generation process.) */
            const bool canIdFound = getIdxByCanId( pValue
                                                 , pMapInstance->mapExtCanIdToEdeIdxAry
                                                 , pMapInstance->u.noExtCanIds
                                                 , canId
                                                 );
            if(!canIdFound)
                return false;
        }
    } /* if(Simple mapping or normal binary search mapping?) */

    return true;
    
} /* getValue */


/**
 * Create new map object. It has \a noKindsOfEv independently operating instances, which
 * relate to the same number of supported kinds of events. The map is capable of key-value
 * pairs, where key is a CAN ID of the form \a mci_pairCanIdAndIdx_t.
 *   @return
 * The function returns \a true in case of success, \a false otherwise. The map is not
 * usable in the latter case.
 *   @param pNewMap
 * If the function returns \a true, then the new map object is returned by reference as * \a
 * pNewMap.
 *   @param noKindsOfEv
 * The map will have this number of independent instances.\n
 *   Caution, later at runtime, the argument \a kindOfEvent will be used as zero based
 * index into the array of instances. Consequently, this map implementation must not be
 * used, if the applied enumeration of event kinds is not zero based!
 *   @param specInstanceAry
 * Each kind of event has its own map instance, internal to the created map object. Each of
 * these instance will have individual properrties, in particular its own data tables.
 * Therefore, the function requires the specification of \a noKindsOfEv map instance. They
 * are bundled inside this array. The size of the array is \a noKindsOfEv and the entries
 * relate in a one-by-one relations to the numeric values of the different kinds of
 * event.\n
 *   Such a map instance is characterized mainly by the data tables and their number of
 * entries. However, an instance may alternatively make use of the simple mapping only.
 * Find the details of a map instance specification in the description of data type \a
 * mci_specMapInstance_t.\n
 *   The passed array needs to exist only during run-time of this function.
 *   @param pMemPool
 * This memory pool (by reference) provides the memory for the new object. The map is used
 * from the dispatcher system, so this memory pool should have the same access rights or
 * restrictions as the one applied for creation of the related dispatcher objects. Usually,
 * it'll even be the same one.
 */
bool mci_createMapBinarySearchCanId( ede_mapSenderEvHandleToIdx_t * const pNewMap
                                   , unsigned int noKindsOfEv
                                   , const mci_specMapInstance_t specInstanceAry[]
                                   , ede_memoryPool_t * const pMemPool
                                   )
{
    EDE_ASSERT(noKindsOfEv > 0u);
    const unsigned int sizeOfMap = sizeof(map_t) + noKindsOfEv * sizeof(mapInstance_t);

    /* Check capacity of pool. The operation is optional for a memory pool. */
    bool success = pMemPool->getNbrOfAvailableBytes == NULL
                   ||  sizeOfMap <= pMemPool->getNbrOfAvailableBytes(pMemPool->hInstance);

    map_t *pMap = NULL;
    if(success)
    {
        /* Try to allocate memory for the map, including the array with all its instances. */
        pMap = pMemPool->malloc(pMemPool->hInstance, sizeOfMap);
        success = pMap != NULL;
    }
    
    if(success)
    {
        pMap->noInstances = noKindsOfEv;
        
        /* Initialize all instances of the map. Each kind of event has an unrelated handle
           space and requires its own mapping. */
        for(unsigned int idxInstance=0u; idxInstance<noKindsOfEv; ++idxInstance)
        {
            const mci_specMapInstance_t * const pSpec = &specInstanceAry[idxInstance];
            mapInstance_t * const pMapInstance = &pMap->mapInstanceAry[idxInstance];
            if(pSpec->doBinarySearchMapping)
            {   
                pMapInstance->u.noExtCanIds = pSpec->noExtCanIds;
                pMapInstance->mapStdCanIdToEdeIdxAry = pSpec->mapStdCanIdToEdeIdxAry;
                pMapInstance->mapExtCanIdToEdeIdxAry = pSpec->mapExtCanIdToEdeIdxAry;
            }
            else
            {
                pMapInstance->u.simpleMapValue = INVALID_MAP_VALUE;
                pMapInstance->mapStdCanIdToEdeIdxAry = NULL;
                pMapInstance->mapExtCanIdToEdeIdxAry = NULL;
            }
        }

        /* Return the new map in the form as it is expected by the dispatcher engine. */
        pNewMap->addKeyValuePair = addKeyValuePair;
        pNewMap->getValue        = getValue;
        pNewMap->hInstance       = (uintptr_t)pMap;
        return true;
    }
    else
        return false;

} /* mci_createMapBinarySearchCanId */


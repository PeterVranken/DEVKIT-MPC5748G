/**
 * @file m16_mapDirectLookupU16.c
 * This module provides a simple handle map, suitable for many applications of the event
 * dispatcher mechanism. It can be used as mapping from some OS event handles (e.g. Rx CAN
 * frame handles) to the zero based index space of a dispatcher object.\n
 *   The implementation supports the interfaces defined by the event sender and dispatcher
 * engine and the map is therefore most easy to use in this context. Just create a map
 * object and pass it to the constructor of sender or dispatcher object.\n
 *   The implementation of this map uses a direct lookup table, i.e. the map is highly
 * execution time efficient, O(1), and can be applied for arbitrary mappings as long as the
 * convered OS handle and index spaces suffice. These spaces are limited, they spawn an
 * 16 Bit range, in order to not waste too much expensive RAM.\n
 *   Most use cases will have a few kinds of events, which know an event handle for further
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
 *   m16_createMapDirectLookupU16
 * Local functions
 *   addKeyValuePair
 *   getValue
 */

/*
 * Include files
 */

#include "m16_mapDirectLookupU16.h"

#include <limits.h>
#include <assert.h>

#include "ede_basicDefinitions.h"
#include "ede_externalInterfaces.h"
#include "mem_malloc.h"

/*
 * Defines
 */

/** The maximum size of the lookup table area of a single map instance. This value is used
    only to recognize errors in the calling code, e.g. overflows due to confused from and
    to values. The actual value of the define is rather irrelevant; the expectation is that
    all ever used maps will be much smaller than the defined size. If a map of an
    accordingly wide spread handle space would really be needed then the implementation as
    direct table lookup should be doubted. */
#define MAX_BYTE_PER_TABLE_INSTANCE     0x10000u

/** The maximum total size of the entire lookup area. We use a 16 Bit value to index this
    range and we need to store the first unused index in the 16 Bit variable. Therefore,
    the maximum size specified here need to be less than 2^16. */
#define MAX_BYTE_TABLE_AREA             UINT16_MAX

/** Empty map entry. Used for recognition of ambiguous mappings. Note, this fault
    recognition effectively reduces the range of supported dispatcher event source indexes
    by one. */
#define INVALID_MAP_VALUE               UINT_MAX


/*
 * Local type definitions
 */

/** The map value type. */
typedef uint16_t uintMapVal_t;

/** One instance of the map, i.e., the structure needed for one kind of event. */
typedef struct mapInstance_t
{
    /** The offset to apply to the map input, before doing the table lookup by zero based
        index. */
    signed int offsetInp;

#ifdef DEBUG
    /** Index range check for access into table area. Lower boundary. */
    unsigned int minTableIdx;
#endif

    /** Index range check for access into table area. Upper boundary (excluding). A value
        of zero has a special meaning: Many kinds of events stands for themselves and do
        not need or use an additional handle. Zero indicates this situation and no lookup
        is done. */
    uint16_t maxTableIdx;

    /** The map value in case of simple mapping. */
    uintMapVal_t valueSimpleMapping;
    
} mapInstance_t;


typedef struct map_t
{
    /** The instances of the map. One instance for each kind of event. Each kind of event
        has its own, independent sender event and dispatcher index space. */
    mapInstance_t *mapInstanceAry;

    /** Number of instances. Used only for index boundary check. */
    unsigned int noInstances;

    /** The lookup table area as flexible array member. This member needs to be the last
        member. */
    uintMapVal_t tableArea[];

} map_t;


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
 * An event is characterized by its kind and by the sender's handle. The meaning of
 * both values is transparent to sender and dispatcher engine. They will be defined by
 * the integrating environment. A common use case would for example be: Kind is "CAN Rx
 * event" and sender handle is CAN message ID.
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
 */
static bool addKeyValuePair( uintptr_t hMap
                           , ede_kindOfEvent_t kindOfEvent
                           , ede_senderHandleEvent_t senderHandleEvent
                           , unsigned int mapValue
                           )
{
    map_t * const pMap = (map_t*)hMap;
    if(mapValue >= INVALID_MAP_VALUE  ||  kindOfEvent >= pMap->noInstances)
    {
        EDE_ASSERT(false);
        return false;
    }

    mapInstance_t * const pMapInst = &pMap->mapInstanceAry[kindOfEvent];
    if((unsigned)pMapInst->maxTableIdx > 0u)
    {
        const unsigned int idxLookup = (unsigned)senderHandleEvent
                                       + (unsigned)pMapInst->offsetInp;

        /* Check if the sender handle is in the range, which had been specified at map
           creation time. The lower boundary is only checked in DEBUG, as it is much
           less critical in fault consequence; if it is hurt then we still do a valid
           access inside the map's table area. (But we violate another instance and
           there is a good chance to detect this as doubly defined entry.) A run-time
           check is done for accessing out of bounds of allocated memory. */
        EDE_ASSERT(idxLookup >= pMapInst->minTableIdx);
        if(idxLookup > (unsigned)pMapInst->maxTableIdx)
        {
            EDE_ASSERT(false);
            return false;
        }

        /* The second condition checks that one and the same mapping is not redefined
           ambiguously. */
        const uintMapVal_t valueLookup = pMap->tableArea[idxLookup];
        if(valueLookup != (uintMapVal_t)INVALID_MAP_VALUE  &&  valueLookup != mapValue)
        {
            EDE_ASSERT(false);
            return false;
        }

        /* Add the validated new mapping to the table. */
        pMap->tableArea[idxLookup] = (uintMapVal_t)mapValue;
        return true;
    }
    else
    {
        /* Events with zero size lookup table area are those, which don't use a handle.
           Their "kind of event" stands for itself. This map implementation supports
           those events by simply storing the related dispatcher index. */
        if(pMapInst->valueSimpleMapping == (uintMapVal_t)INVALID_MAP_VALUE)
        {
            pMapInst->valueSimpleMapping = (uintMapVal_t)mapValue;
            return true;
        }
        else if((unsigned)pMapInst->valueSimpleMapping != mapValue)
        {
            /* Ambiguous mapping for given key. */
            EDE_ASSERT(false);
            return false;
        }
        else
        {
            /* The earlier defined mapping matches this new key value pair. */
            return true;
        }
    } /* if(Normal direct lookup mapping or simple mapping?) */
} /* addKeyValuePair */



/**
 * The map lookup operation. The index associated with an external event is queried.\n
 *   1. Use case mapping external events to registered event sources:\n
 *   The requested index is that of an event source as internally used by the
 * dispatcher engine. The map query function is called as sub-routine of the
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
 * This is the identification of the map object to use.
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

    const mapInstance_t * const pMapInst = &pMap->mapInstanceAry[kindOfEvent];
    if(pMapInst->maxTableIdx > 0)
    {
        const unsigned int idxLookup = (unsigned)senderHandleEvent
                                       + (unsigned)pMapInst->offsetInp;

        /* Check if the sender handle is in the range, which had been specified at map
           creation time. The lower boundary is only checked in DEBUG, as it is much less
           critical in fault consequence; if it is hurt then we still do a valid read
           inside the map's table area. A run-time check is done for reading out of bounds
           of allocated memory. */
        EDE_ASSERT(idxLookup >= pMapInst->minTableIdx);
        if(idxLookup > pMapInst->maxTableIdx)
        {
            EDE_ASSERT(false);
            return false;
        }
        const unsigned int mapVal = (unsigned)pMap->tableArea[idxLookup];
        if(mapVal < INVALID_MAP_VALUE)
        {   
            /* Return the mapping found at validated position in the table. */
            *pValue = mapVal;
            return true;
        }
        else
            return false;
    }
    else
    {
        /* Events with zero size lookup table area are those, which don't use a handle.
           Their "kind of event" stands for itself. Just return the map value, which had
           been stored for the given kind of event. */
        *pValue = (unsigned)pMapInst->valueSimpleMapping;
        return true;
    }
} /* getValue */


/**
 * Create new map object. It has \a noKindsOfEv independently operating instances, which
 * relate to the same number of supported kinds of events.
 *   @return
 * The function returns \a true in case of success, \a false otherwise. The map is not
 * usable in the latter case.
 *   @param pNewMap
 * If the function returns \a true, then the new map object is returned by reference as * \a
 * pNewMap.
 *   @param noKindsOfEv
 * The map will have this number of independent lookup tables.\n
 *   Caution, later at runtime, the argument kindOfEvent will be used as zero based index
 * into the array of lookup tables. Consequently, this map implementation must not be used,
 * if the applied enumeration of event kinds is not zero based!
 *   @param rangeSenderHandleEvAry
 * An array of ranges of sender handle values. Each range relates to one kind of event, so
 * the array size is \a noKindsOfEv entries. Each entry, a handle value range, consists of
 * two intergers. The first one is the lowest possible sender handle value and the seconds
 * one is the largest possible sender handle value plus one.\n
 *   A range of zero length is allowed. If rangeSenderHandleEvAry[][0] ==
 * rangeSenderHandleEvAry[][1], then no lookup table is stored for the given kind of event.
 * Instead, that kind of event will be mapped onto a fixed value, regardless of a sender
 * event handle. (It is assumed a standard use case, that kinds of event stands for
 * themselves but don't require an additional handle space.)
 *   @param pMemPool
 * This memory pool (by reference) provides the memory for the new object. The map is used
 * from the dispatcher engine, so this memory pool should have the same access rights or
 * restrictions as the one applied for creation of the related dispatcher object. Usually,
 * it'll even be the same one.
 */
bool m16_createMapDirectLookupU16( ede_mapSenderEvHandleToIdx_t * const pNewMap
                                 , unsigned int noKindsOfEv
                                 , const signed int rangeSenderHandleEvAry[][2u]
                                 , ede_memoryPool_t * const pMemPool
                                 )
{
    EDE_ASSERT(noKindsOfEv > 0u);
    unsigned int sizeOfTableArea = 0u
               , idxInstance;
    bool success = true;
    for(idxInstance=0u; idxInstance<noKindsOfEv; ++idxInstance)
    {
        const unsigned int sizeOfInstTableArea = sizeof(uintMapVal_t)
                                                 * (unsigned)
                                                   (rangeSenderHandleEvAry[idxInstance][1u]
                                                    - rangeSenderHandleEvAry[idxInstance][0u]
                                                   );
        if(sizeOfInstTableArea >= MAX_BYTE_PER_TABLE_INSTANCE)
        {
            EDE_ASSERT(false);
            success = false;
        }
        sizeOfTableArea += sizeOfInstTableArea;
    }
    if(sizeOfTableArea >= MAX_BYTE_TABLE_AREA)
    {
        EDE_ASSERT(false);
        success = false;
    }
    
    const unsigned int sizeOfMap = sizeof(map_t)
                                   + noKindsOfEv * sizeof(mapInstance_t)
                                   + sizeOfTableArea;

    if(success)
    {
        /* Check capacity of pool. The operation is optional for a memory pool. */
        success = pMemPool->getNbrOfAvailableBytes == NULL
                  ||  sizeOfMap <= pMemPool->getNbrOfAvailableBytes(pMemPool->hInstance);
    }
    
    mapInstance_t * pInstance = NULL;
    if(success)
    {
        /* Try to allocate memory for the map and including the table area for all its
           instances. 
             Note, we put the instances before the map in order to have the table area at
           the very end. This makes the use of the flexible array member easier. */
        pInstance = pMemPool->malloc(pMemPool->hInstance, sizeOfMap);
        success = pInstance != NULL;
    }
    
    if(success)
    {
        /* Initialize all instances of the map. Each kind of event has an unrelated handle
           space and requires its own mapping. */
        unsigned int idxZero = 0u;
        for(idxInstance=0u; idxInstance<noKindsOfEv; ++idxInstance, ++pInstance)
        {
#ifdef DEBUG
            /* Hurting the beginning of the instance's table area is a rather weak fault
               and it is not tested in production build. */
            pInstance->minTableIdx = idxZero;
#endif
            /* Offset: It is added to the map input (the sender handle) such that the sum
               is the ready to use table area index. */
            pInstance->offsetInp = (int)idxZero - rangeSenderHandleEvAry[idxInstance][0u];

            /* The map input is checked against the uppermost index of the table area,
               which still belongs to the given index. Note, a lookup table with zero
               entries means don't do a lookup and is indicated by maxTableIdx=0. */
            const unsigned int sizeOfInstTableArea = 
                                sizeof(uintMapVal_t)
                                * (unsigned)(rangeSenderHandleEvAry[idxInstance][1u]
                                             - rangeSenderHandleEvAry[idxInstance][0u]
                                            );
            if(sizeOfInstTableArea > 0)
            {
                EDE_ASSERT((unsigned long)idxZero + sizeOfInstTableArea <= UINT16_MAX);
                pInstance->maxTableIdx = (uint16_t)((unsigned)idxZero + sizeOfInstTableArea);
                idxZero += sizeOfInstTableArea;
            }
            else
                pInstance->maxTableIdx = 0u;
            
            pInstance->valueSimpleMapping = (uintMapVal_t)INVALID_MAP_VALUE;
        }
        EDE_ASSERT(idxZero == sizeOfTableArea);

        /* The map object itself, which collects all instances, follows behind the last
           instance. */
        map_t * const pMap = (map_t*)pInstance;
        pInstance -= noKindsOfEv;
        pMap->mapInstanceAry = pInstance;
        pMap->noInstances = noKindsOfEv;

        /* Pre-fill all map instances such that ambiguous mappings can be safely recognized
           when the dispatcher engine builds up the map. */
        for(unsigned int u=0u; u<sizeOfTableArea; ++u)
            pMap->tableArea[u] = (uintMapVal_t)INVALID_MAP_VALUE;

        /* Return the new map in the form as it is expected by the dispatcher engine. */
        pNewMap->addKeyValuePair = addKeyValuePair;
        pNewMap->getValue        = getValue;
        pNewMap->hInstance       = (uintptr_t)pMap;
        return true;
    }
    else
        return false;

} /* m16_createMapDirectLookupU16 */


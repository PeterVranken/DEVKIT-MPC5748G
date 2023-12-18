/**
 * @file mpo_mapOffsetOnly.c
 * This module provides a simple handle map, suitable for many applications of the event
 * dispatcher mechanism. It can be used as mapping from some OS event handles (e.g. Rx CAN
 * frame handles) to the zero based index space of a dispatcher object.\n
 *   The implementation supports the interfaces defined by the event sender and dispatcher
 * engine and the map is therefore most easy to use in this context. Just create a map
 * object and pass it to the constructor of sender or dispatcher object.\n
 *   The implementation of this map uses a direct lookup table, i.e. the map is highly
 * execution time efficient, O(1), and can be applied for arbitrary mappings as long as the
 * convered OS handle and index spaces suffice. These spaces are kept little, they spawn an
 * 8 Bit range only, in order to not waste much expensive RAM.\n
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
 *   mpo_createMapOffsetOnly
 * Local functions
 *   addKeyValuePair
 *   getValue
 */

/*
 * Include files
 */

#include "mpo_mapOffsetOnly.h"

#include <limits.h>
#include <assert.h>

#include "ede_basicDefinitions.h"
#include "ede_externalInterfaces.h"
#include "mem_malloc.h"

/*
 * Defines
 */

/* The software is written as portable as reasonably possible. This requires the awareness
   of the C language standard it is compiled with.
     With respect to the language feature C11 and C17 are identical. We combine them in one
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

/** The map value type. One bit is required to distinguish handle offset mapping from
    simple mapping. The representable range of map values is accordingly smaller. */
typedef uint16_t uintMapConstant_t;

/** All range calculations are done in the native integer size of the platform. This limits
    the configurable types for the map constant. */
_Static_assert( sizeof(uintMapConstant_t) <= sizeof(unsigned int)
              , "The type of the map constant needs to fit into type (un)signed int"
              );
              
#ifdef _STDC_VERSION_C17_C11

/** Empty map entry. Used for recognition of ambiguous mapping definitions. */
#define INVALID_OFFSET_VALUE    (_Generic( (uintMapConstant_t)0                         \
                                         , uint8_t:  0x80u                              \
                                         , uint16_t: 0x8000u                            \
                                         , uint32_t: 0x80000000u                        \
                                         )                                              \
                                )

/** The reserved value "uninitialized" for those kinds of events, which don't make use of
    of a sender handle. */
#define INVALID_MAP_VALUE       (_Generic( (uintMapConstant_t)0                         \
                                         , uint8_t:  0xFFu                              \
                                         , uint16_t: 0xFFFFu                            \
                                         , uint32_t: 0xFFFFFFFFu                        \
                                         )                                              \
                                )

#else

/* Not having the _Generic keyword means independent definition of the mask values - which
   has to be made consistently with the configured data type though. Consistency is
   double-checked by assertion. */
_Static_assert( sizeof(uintMapConstant_t) == 2u
              , "Inconsistent definition of map value type and related masks"
              );

/** Empty map entry. Used for recognition of ambiguous mapping definitions. */
#define INVALID_OFFSET_VALUE    (0x8000u)

/** The reserved value "uninitialized" for those kinds of events, which don't make use of
    of a sender handle. */
#define INVALID_MAP_VALUE       (0xFFFFu)

#endif

/** Sign extension operation from map value type to signed int. */
#define INT(x) (sizeof(x)==1u? (int)(int8_t)x                                           \
                             : (sizeof(x)==2u? (int)(int16_t)x: (int)x)                 \
               )

_Static_assert( sizeof(uint16_t) == sizeof(unsigned short)
              , "Assumption failed, which has been made for the definition of "
                " INVALID_OFFSET_VALUE and INVALID_MAP_VALUE"
              );

/** Mask for bit "is simple mapping". */
#define BIT_MASK_MAP_CONSTANT_IS_SIMPLE_MAPPING     1u


/*
 * Local type definitions
 */

/** The map object. */
typedef struct map_t
{
    /** The number of supported kinds of events. */
    unsigned int noInstances;
    
    /** For each kind of event: The offset to apply to the map input if handle offset
        mapping is applicable. Or the map value in case of simple mapping - in which case the
        value is considered unsigned.\n
          Bit 0 has the meaning of "is simple mapping".
          The array is implemented as flexible array member. */
    uintMapConstant_t mappingConstantAry[];
    
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
    if(kindOfEvent >= pMap->noInstances)
    {
        EDE_ASSERT(false);
        return false;
    }

    /** Each map instance, its implementation for a given kind of event, just consists of a
        single unsigned word. */
    const uintMapConstant_t mapConstant = pMap->mappingConstantAry[kindOfEvent];
    
    /* The LSB tells us, whether we need to apply the actual offset mapping or the simple
       mapping. */
    const bool isSimpleMapping = (mapConstant & BIT_MASK_MAP_CONSTANT_IS_SIMPLE_MAPPING) != 0u
                                 ? true
                                 : false;
    if(isSimpleMapping)
    {
        /* Events of given kind don't use a handle. Their "kind of event" stands for
           itself. This map implementation supports those events by simply storing the
           related index in bits 1..n of the constant. */
           
        /* -1: The largest representable value is unused as offset but has the meaning of
           "mapping not yet set". */
        const uintMapConstant_t maxMapValue = (INVALID_MAP_VALUE >> 1u) - 1u;
        
        /* Reject the key-value pair if the map value doesn't fit into our representation. */
        if(mapValue > maxMapValue)
            return false;

        const uintMapConstant_t newMapConstant = (mapValue << 1u) + 1u;
        if(mapConstant == INVALID_MAP_VALUE)
        {
            /* Map value had not yet been defined for the given key. Set it now. */
            pMap->mappingConstantAry[kindOfEvent] = newMapConstant;
        }    
        else
        {
            /* The mapping result had already been determined and this is a (somewhat
               unexpected) re-definition. We need to check if identical and reject the pair
               if not. */
            if(mapConstant != newMapConstant)
            {
                EDE_ASSERT(false);
                return false;
            }
        }
        EDE_ASSERT(pMap->mappingConstantAry[kindOfEvent] != INVALID_MAP_VALUE);
    }
    else
    {
        /* Events of given kind require handle mapping. This map implementation only
           supports a constant offset between key and value, by storing the offset in bits
           1..n of the constant. */
           
        /* The offset required to represent the given key-value pair. */
        const signed int offset = (int)mapValue - INT(senderHandleEvent);
        
        /* The range of representable mappings. */
        const signed int minOffset =
                    ((int)((UINT_MAX & ~INVALID_MAP_VALUE) | INVALID_OFFSET_VALUE) >> 1u) + 1;
        const signed int maxOffset = -minOffset;

        /* Reject the key-value pair if the map value doesn't fit into our representation. */
        if(offset < minOffset  ||  offset > maxOffset)
            return false;

        /* The new value of the constant can be safely calculated. */
        const uintMapConstant_t newMapConstant = ((unsigned)offset << 1u) + 0u;
        
        /* The largest negative value is unused and has the meaning of "offset not yet
           set". */
        if(mapConstant == INVALID_OFFSET_VALUE)
        {
            /* Map value had not yet been defined for the given key. Set it now. */
            pMap->mappingConstantAry[kindOfEvent] = newMapConstant;
        }    
        else
        {
            /* The mapping result had already been determined and this is a (somewhat
               unexpected) re-definition. We need to check whether it identical and reject
               the pair if not. */
            if(mapConstant != newMapConstant)
            {
                EDE_ASSERT(false);
                return false;
            }
        }
        EDE_ASSERT(pMap->mappingConstantAry[kindOfEvent] != INVALID_OFFSET_VALUE);

    } /* if(Simple mapping or normal offset mapping?) */

    EDE_ASSERT((pMap->mappingConstantAry[kindOfEvent]
                & BIT_MASK_MAP_CONSTANT_IS_SIMPLE_MAPPING
               )
               == (isSimpleMapping? 1u: 0u)
              );
    return true;   

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
 * This is the identification of the map instance to use. The data type
 * uintptr_t is such that the implementation of the map can hide an index into an
 * array of objects or a pointer to an object behind this value. See field \a
 * hInstance, too.\n
 *   1. Use case mapping external events to registered event sources:\n
 *   Each dispatcher has its own index space for event sources and will apply a
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

    /** Each map instance, its implementation for a given kind of event, just consists of a
        single unsigned word. */
    const uintMapConstant_t mapConstant = pMap->mappingConstantAry[kindOfEvent];
    
    /* The LSB tells us, whether we need to apply the actual offset mapping or the simple
       mapping. */
    const bool isSimpleMapping = (mapConstant & BIT_MASK_MAP_CONSTANT_IS_SIMPLE_MAPPING) != 0u
                                 ? true
                                 : false;
    
    if(isSimpleMapping)
    {
        /* Events of given kind don't use a handle. Their "kind of event" stands for
           itself. This map implementation supports those events by simply storing the
           related index in bits 1..n of the constant. */
           
        if(mapConstant != INVALID_MAP_VALUE)
            *pValue = (unsigned)mapConstant >> 1u;
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
        /* Events of given kind require handle mapping. This map implementation only
           supports a constant offset between key and value, by storing the offset in bits
           1..n of the constant. */

        if(mapConstant != INVALID_OFFSET_VALUE)
        {
            /* We don't need signed/unsigned overflow checks here. They may occur,
               depending on the added key-value pairs. */
            const signed int offset = INT(mapConstant) >> 1u;
            *pValue = (unsigned)((int)senderHandleEvent + offset);
        }
        else
        {
            /* The largest negative value is unused and has the meaning of "offset not yet
               set". */
            EDE_ASSERT(false);
            return false;
        }            
    } /* if(Simple mapping or normal offset mapping?) */

    return true;
    
} /* getValue */


/**
 * Create new map object. It has \a noKindsOfEv independently operating instances, which
 * relate to the same number of supported kinds of events. The map is capable of key-value
 * pairs, which all have the simple relation value = key + const, where "const" is a fixed,
 * known offset value, which may be individual per map instance.\n
 *   Despite of its simplicity, this map is most useful. It can be applied in a majority of
 * typical CAN interface use cases. It's always applicable if the mapped sender (or OS)
 * handles are dealt out incrementally and if they are registered in this order at one and
 * the same dispatcher system.
 *   @return
 * The function returns \a true in case of success, \a false otherwise. The map is not
 * usable in the latter case.
 *   @param pNewMap
 * If the function returns \a true, then the new map object is returned by reference as * \a
 * pNewMap.
 *   @param noKindsOfEv
 * The map will have this number of independent instances.\n
 *   Caution, later at runtime, the argument kindOfEvent will be used as zero based index
 * into the array of instances. Consequently, this map implementation must not be used, if
 * the applied enumeration of event kinds is not zero based!
 *   @param isSenderHandleInUseAry
 * A Boolean property of the map instance, which states, whether a given kind of event
 * makes use of the sender handle. (Many events stands for themselves and don't require an
 * additional handle for further differentiation.) Each entry in the array relates to one
 * kind of event, so the array size is \a noKindsOfEv entries.\n
 *   If \a isSenderHandleInUseAry[\a i] is \a true, then normal offset mapping is performed
 * and the map lookup result is the sender handle value plus the fixed offset value, which
 * has been stored for the \a kindOfEvent \a i.\n
 *   If \a isSenderHandleInUseAry[\a i] is \a false, then no offset mapping is performed
 * and the map lookup result is the fixed value, which has been stored for the \a
 * kindOfEvent \a i. 
 *   @param pMemPool
 * This memory pool (by reference) provides the memory for the new object. The map is used
 * from the dispatcher engine, so this memory pool should have the same access rights or
 * restrictions as the one applied for creation of the related dispatcher object. Usually,
 * it'll even be the same one.
 */
bool mpo_createMapOffsetOnly( ede_mapSenderEvHandleToIdx_t * const pNewMap
                            , unsigned int noKindsOfEv
                            , const bool isSenderHandleInUseAry[]
                            , ede_memoryPool_t * const pMemPool
                            )
{
    EDE_ASSERT(noKindsOfEv > 0u);
    const unsigned int sizeOfMap = sizeof(map_t) + noKindsOfEv * sizeof(uintMapConstant_t);

    /* Check capacity of pool. The operation is optional for a memory pool. */
    bool success = pMemPool->getNbrOfAvailableBytes == NULL
                   ||  sizeOfMap <= pMemPool->getNbrOfAvailableBytes(pMemPool->hInstance);

    map_t *pMap = NULL;
    if(success)
    {
        /* Try to allocate memory for the map and including the table with all its
           instances. */
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
            if(isSenderHandleInUseAry[idxInstance])
            {
                /* Initialize the instance for normal offset mapping. */
                pMap->mappingConstantAry[idxInstance] = INVALID_OFFSET_VALUE;
            }
            else
            {
                /* Initialize the instance for simple mapping. */
                pMap->mappingConstantAry[idxInstance] = INVALID_MAP_VALUE;
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

} /* mpo_createMapOffsetOnly */


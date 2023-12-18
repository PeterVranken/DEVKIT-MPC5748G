/**
 * @file mid_mapIdentity.c
 * This module provides a simple handle map, suitable for many applications of the event
 * dispatcher mechanism. It can be used as mapping from some OS event handles (e.g. Rx CAN
 * frame handles) to the zero based index space of a dispatcher object.\n
 *   The implementation supports the interfaces defined by the event sender and dispatcher
 * engine and the map is therefore most easy to use in this context. Just create a map
 * object and pass it to the constructor of sender or dispatcher object.\n
 *   The implementation of this map is the identity. Quite frequently in simple platforms,
 * the OS uses a simple zero based mailbox index as handle space for CAN transmission. In
 * such systems, it's mostly possible to organize the enumeration of messages in the
 * dispatcher engine identical to the use of OS owned mailboxes and dispathcer index and
 * mailbox become equal. If so, this map can be applied. It doesn't do any storage or
 * lookup operation but just returns the dispatcher index as OS handle.
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
 *   mid_createMapIdentity
 * Local functions
 *   getValue
 */

/*
 * Include files
 */

#include "mid_mapIdentity.h"

#include <limits.h>
#include <assert.h>

#include "ede_basicDefinitions.h"
#include "ede_externalInterfaces.h"

/*
 * Defines
 */

/* The software is written as portable as reasonably possible. This requires the awareness
   of the C language standard it is compiled with. */
#if defined(__STDC_VERSION__)
# if (__STDC_VERSION__)/100 == 2011
#  define _STDC_VERSION_C11
# elif (__STDC_VERSION__)/100 == 1999
#  define _STDC_VERSION_C99
# endif
#endif


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
 * The map lookup operation. The index associated with an external event is queried.\n
 *   1. Use case mapping external events to registered event sources:\n
 *   The requested index is that of an event source as internally used by the
 * dispatcher engine. The map query function is called as sub-routine of the
 * dispatching operation, ede_dispatcherMain().\n
 *   2. Use case mapping external events to a sender's port:\n
 *   The requested index is that of a port of the querying sender. The map query
 * function is called as sub-routine of sending an event, ede_postEvent().
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
static bool getValue( uintptr_t hMap EDE_UNUSED
                    , unsigned int * pValue
                    , ede_kindOfEvent_t kindOfEvent EDE_UNUSED
                    , ede_senderHandleEvent_t senderHandleEvent
                    )
{
    *pValue = (unsigned int)senderHandleEvent;
    return true;
    
} /* getValue */


/**
 * Create new map object.
 *   @param pNewMap
 * The new map object is returned by reference as * \a * pNewMap.
 */
void mid_createMapIdentity(ede_mapSenderEvHandleToIdx_t * const pNewMap)
{
    pNewMap->addKeyValuePair = NULL;
    pNewMap->getValue        = getValue;
    pNewMap->hInstance       = 0u;

} /* mid_createMapIdentity */


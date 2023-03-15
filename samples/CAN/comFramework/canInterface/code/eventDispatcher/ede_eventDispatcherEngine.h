#ifndef EDE_EVENTDISPATCHERENGINE_INCLUDED
#define EDE_EVENTDISPATCHERENGINE_INCLUDED
/**
 * @file ede_eventDispatcherEngine.h
 * Definition of global interface of module ede_eventDispatcherEngine.c
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

/*
 * Include files
 */

#include <limits.h>

#include "ede_basicDefinitions.h"
#include "ede_eventDispatcherEngine.config.h"
#include "ede_externalInterfaces.h"


/*
 * Defines
 */

/** A predefined value of the enumeration \ref ede_kindOfEvent_t meaning initialization of
    an external event source. */
#define EDE_EV_EVENT_SOURCE_EXT_INIT    ((EDE_EV_KIND_LAST)+1u)

/** A predefined value of the enumeration \ref ede_kindOfEvent_t meaning initialization of
    an internal event source. */
#define EDE_EV_EVENT_SOURCE_INT_INIT    ((EDE_EV_KIND_LAST)+2u)

/** A predefined value of the enumeration \ref ede_kindOfEvent_t meaning Timer event. */
#define EDE_EV_TIMER_ELAPSED            ((EDE_EV_KIND_LAST)+3u)

/** The integration code can use all values from the implementation range of \ref
    ede_kindOfEvent_t as kind of event, except for the few values (#EDE_EV_KIND_LAST+1)
    till (#EDE_EV_KIND_LAST+3). If an unsigned type is configured then this is equivalent
    to a usable range of 0..#EDE_EV_KIND_LAST, both including, plus 0xff..f. */
#define EDE_EV_KIND_LAST                ((ede_kindOfEvent_t)((ede_kindOfEvent_t)-(2+3)))

/** The first permitted client code's custom value for enumeration \ref ede_kindOfEvent_t.
    Define the enumeration values for your specific external events starting with this
    value. */
#define EDE_EV_FIRST_CUSTOM_EVENT       100

/** The invalid event dispatcher system handle. */
#define EDE_INVALID_DISPATCHER_SYSTEM_HANDLE    NULL

/** The invalid timer handle. */
#define EDE_INVALID_TIMER_HANDLE        NULL

/** The invalid index value for event sources. */
#define EDE_INVALID_EVENT_SOURCE_INDEX  UINT_MAX


/*
 * Global type definitions
 */

/** The handle or identification of an event dispatcher system object. */
typedef struct ede_dispatcherSystem_t *ede_handleDispatcherSystem_t;
typedef const struct ede_dispatcherSystem_t *ede_handleConstDispatcherSystem_t;

/** The client implemented callback functions can interact with the engine via a bunch of
    API functions. Since any number of concurrent dispatcher engines can be run in different
    tasks it is necessary to have a context for the implementation of the API. This context
    has an opaque type but it has to be passed to all API functions.
      @remark Unfortunately, the wording \a context is misleading since this term is mostly
    used for "CPU context" in order to distinguish the different concurrent execution
    threads in a multi-threading or -core environment. Here, \a context refers to the
    context of using the API, effectively a reference to the dispatcher engine in use. */
typedef struct event_t ede_callbackContext_t;

/** The type of a callback for external events. */
typedef void (*ede_callback_t)(const ede_callbackContext_t *pContext);

/** The handle or identification of a timer object. */
typedef struct ede_timer_t *ede_handleTimer_t;

/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Create a dispatcher system object. */
bool ede_createDispatcherSystem( ede_handleDispatcherSystem_t * const pHandleDispSystem
                               , unsigned int noEventDispatcherEngines
                               , unsigned int maxNoEventSourcesExt
                               , unsigned int maxNoEventSourcesInt
                               , ede_memoryPool_t * const pMemPoolDispatchingProcess
                               );

/** Create a dispatcher object. */
bool ede_createDispatcher( ede_handleDispatcherSystem_t hDispatcherSystem
                         , unsigned int idxDispatcher
                         , signed int tiTick
                         , const ede_eventReceiverPort_t portAry[]
                         , unsigned int noPorts
                         , ede_mapSenderEvHandleToIdx_t mapSdrEvHdlToEdeEvSrcIdx
                         );

/** Register an event source for processing of external events by the engine. */
unsigned int ede_registerExternalEventSource( ede_handleDispatcherSystem_t hDispatcherSystem
                                            , unsigned int idxDispatcher
                                            , ede_kindOfEvent_t kindOfEvent
                                            , ede_senderHandleEvent_t senderHandleEvent
                                            , ede_callback_t callback
                                            , uintptr_t refEventSourceData
                                            );

/** Register an internal event source. */
unsigned int ede_registerInternalEventSource( ede_handleDispatcherSystem_t hDispatcherSystem
                                            , unsigned int idxDispatcher
                                            , ede_callback_t callback
                                            , uintptr_t refEventSourceData
                                            );

/** The regular tick function of a dispatcher. */
void ede_dispatcherMain(ede_handleConstDispatcherSystem_t hSystem, unsigned int idxDispatcher);

/** Create a periodic timer object. */
ede_handleTimer_t ede_createPeriodicTimer( const ede_callbackContext_t *pContext
                                         , signed int tiPeriod
                                         , ede_callback_t callback
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                         , uintptr_t refUserContextData
#endif
                                         );

/** Create a periodic timer object with shifted first due time. */
ede_handleTimer_t ede_createPeriodicTimerShifted( const ede_callbackContext_t *pContext
                                                , signed int tiPeriod
                                                , signed int tiPhase
                                                , ede_callback_t callback
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1          
                                                , uintptr_t refUserContextData
#endif                                          
                                                );

/** Create a single shot timer. */
ede_handleTimer_t ede_createSingleShotTimer( const ede_callbackContext_t *pContext
                                           , signed int tiFromNow
                                           , ede_callback_t callback
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                           , uintptr_t refUserContextData
#endif
                                           , bool killAtDueTime
                                           );

/** Kill a periodic or single shot timer object. */
void ede_killTimer(const ede_callbackContext_t *pContext, ede_handleTimer_t hTimer);

/** Stop a running timer but keep the handle alive for later reuse. */
void ede_suspendSingleShotTimer( const ede_callbackContext_t *pContext
                               , ede_handleTimer_t hTimer
                               );

/** Re-trigger a single shot timer before it has elapsed. */
void ede_retriggerSingleShotTimer( const ede_callbackContext_t *pContext
                                 , ede_handleTimer_t hTimer
                                 , signed int tiNewFromNow
                                 );

/** Redefine the callback function for a given dispatcher/event context from within a
    callback. */
ede_callback_t ede_installCallback( const ede_callbackContext_t *pContext
                                  , ede_callback_t newCallback
                                  );

/** Get the index of the event source, which caused this callback. */
unsigned int ede_getIdxEventSource( const ede_callbackContext_t *pContext
                                  , bool * const pIsExternalEventSrc
                                  );

/** Get the index of the external event source, which caused this callback. */
unsigned int ede_getIdxExternalEventSource(const ede_callbackContext_t * const pContext);

/** Get the index of the internal event source, which caused this callback. */
unsigned int ede_getIdxInternalEventSource(const ede_callbackContext_t * const pContext);

/** Get the data object belonging to and registered with the custom event source. */
uintptr_t ede_getEventSourceData(const ede_callbackContext_t *pContext);

/** Get the index of the port, which had received the event. */
ede_kindOfEvent_t ede_getIdxPort(const ede_callbackContext_t *pContext);

/** Get the handle of the timer causing a EDE_EV_TIMER_ELAPSED event. */
ede_handleTimer_t ede_getHandleTimer(const ede_callbackContext_t *pContext);

/** Query the kind of callback (or event) from within a callback. */
ede_kindOfEvent_t ede_getKindOfEvent(const ede_callbackContext_t *pContext);

/** Get the data contents of an event from within a callback. */
const void *ede_getEventData( const ede_callbackContext_t *pContext
                            , unsigned int *pSizeOfEvData
                            );

/** Get the user provided context data of a timer from within its timer-elapsed callback. */
uintptr_t ede_getTimerContextData(const ede_callbackContext_t * const pContext);

#endif  /* EDE_EVENTDISPATCHERENGINE_INCLUDED */

/**
 * @file ede_eventDispatcherEngine.c
 * The dispatcher engine for events. Events are either external events, which are sent with
 * a connected sender object, or internal timer events.\n
 *   Both ends of the communication, sender and dispatcher can execute in different CPU
 * contexts. This is the principal reason for the chosen design: Events, normally generated
 * asynchonously in one or more interrupts can be processed in some application task
 * context on the same or another core and without fearing difficult to handle race
 * conditions.
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
 *   ede_createDispatcherSystem
 *   ede_createDispatcher
 *   ede_registerExternalEventSource
 *   ede_registerInternalEventSource
 *   ede_dispatcherMain
 *   ede_createPeriodicTimer
 *   ede_createSingleShotTimer
 *   ede_killTimer
 *   ede_suspendSingleShotTimer
 *   ede_retriggerSingleShotTimer
 *   ede_installCallback
 *   ede_getIdxEventSource
 *   ede_getIdxExternalEventSource
 *   ede_getIdxInternalEventSource
 *   ede_getEventSourceData
 *   ede_getIdxPort
 *   ede_getHandleTimer
 *   ede_getKindOfEvent
 *   ede_getEventData
 *   ede_getTimerContextData
 * Local functions
 *   createTimer
 *   invokeCallback
 *   getEventSourceFromContext
 *   getTimerObject
 */


/*
 * Include files
 */

#include "ede_eventDispatcherEngine.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "vsq_threadSafeQueueVariableSize.h"
#include "ede_externalInterfaces.h"

/*
 * Defines
 */

/* Some specific numeric values for the timer reload property, which have a special meaning
   other than the normal time designation. */
#define TIMER_STATE_SINGLE_SHOT             (0)
#define TIMER_STATE_SINGLE_SHOT_AUTO_KILL   (-1)
#define TIMER_STATE_SINGLE_SHOT_SUSPENDED   (-2)
#define TIMER_STATE_KILLED                  (-3)

#ifndef sizeoffield
# define sizeoffield(c,m) sizeof(((const c*)NULL)->m)
#endif

/** The invalid event dispatcher handle. */
#define INVALID_DISPATCHER_HANDLE   NULL


/*
 * Local type definitions
 */

/* Forward references for recursive data type definition. See below for actual types. */
struct eventSrc_t;
struct ede_timer_t;
struct ede_eventDispatcher_t;
typedef struct ede_dispatcherSystem_t ede_dispatcherSystem_t;
typedef struct ede_eventDispatcher_t ede_eventDispatcher_t;



/** The internal representation of a registered event source.\n
      Note, this typedef relates to the internal events; see \ref eventSrcExt_t for
    external events. The concept is, that the external source event class extends the
    internal source event class. This requires careful identical maintenance of both
    types, but correctness is double-checked by compile time assertions. */
typedef struct eventSrc_t
{
    /** A context pointer: The event source is meaningless to the dispatcher but by means
        of this reference, the callback code can still access methods or data specific to
        the given event source. The reference can be either an index or a pointer. */
    uintptr_t refEventSrcData;
    
} eventSrc_t;


/** The internal representation of a registered event source.\n
      Note, this typedef relates to the external events; see \ref eventSrc_t for
    internal events. The concept is, that the external source event class extends the
    internal source event class. This requires careful identical maintenance of both
    types, but correctness is double-checked by compile time assertions. */
typedef struct eventSrcExt_t
{
    /** A context pointer: The event source is meaningless to the dispatcher but by means
        of this reference, the callback code can still access methods or data specific to
        the given event source. The reference can be either an index or a pointer. */
    uintptr_t refEventSrcData;

    /** The currently registered callback for external events. */
    ede_callback_t callback;

#if EDE_CHECK_FOR_EVENT_DELIVERY_TO_ASSOCIATED_DISPATCHER == 1u
    /** The dispatcher by reference, which had registered the external event source. Only
        used for internal consistency checks. */
    const ede_eventDispatcher_t *pDispatcher;
#endif
} eventSrcExt_t;


/* A compile-time assertion ensures that the class extension works well, i.e., that the
   extended class has identical fields as the base class such that a pointer to any kind
   of event source class can be used to safely access these common fields. */
_Static_assert(offsetof(eventSrcExt_t, refEventSrcData)
               == offsetof(struct eventSrc_t, refEventSrcData)
               &&  sizeoffield(eventSrcExt_t, refEventSrcData)
               == sizeoffield(struct eventSrc_t, refEventSrcData)
               &&  sizeof(eventSrc_t) == offsetof(eventSrcExt_t, callback)
              , "Construction of extended class definition is bad"
              );

/** A reference to an event source, which can be used to type-safely assign a pointer value
    and to read it type-safely if the kind of event source is known. For any kind of event
    source, the base class pointer can be used to safely access the common fields. */
typedef union ptrToEvtSrc_t
{
    /** This field is used to address to the referenced object if it is an external event
        source. */
    eventSrcExt_t *ext;

    /* This field is used if the common fields of the event source class are read or if the
       the reference to an internal event source is assigned to the reference object. */
    const eventSrc_t *base;
    
} ptrToEvtSrc_t;

/* A compile-time assertion ensures that the class extension works well, i.e., that the
   extended class has identical fields as the base class such that a pointer to any kind
   of event source class can be used to safely access these common fields. */
_Static_assert(offsetof(ptrToEvtSrc_t, ext) == offsetof(ptrToEvtSrc_t, base)
               &&  sizeoffield(ptrToEvtSrc_t, ext) == sizeoffield(ptrToEvtSrc_t, base)
               &&  sizeof(ptrToEvtSrc_t) == sizeof(void*)
              , "Construction of extended class definition is bad"
              );

/** A timer object. */
typedef struct ede_timer_t
{
    /** Any timer is created by an event source - directly or via other timers. This
        event source is the (grand) parent of the timer and this is the reference to
        that event source. */
    ptrToEvtSrc_t pRootEventSrc;
    
    /** A timer can be periodic or a single shot type. For regular, periodic timers this
        value means the timer period in ms.\n
          For killed or single shot timers this value will be less or equal to 0:\n
          #TIMER_STATE_SINGLE_SHOT means an active, running single shot timer without
        automatic kill.\n
          #TIMER_STATE_SINGLE_SHOT_AUTO_KILL means an active, running single shot timer with
        enabled automatic kill property; it'll disappear after firing the event.\n
          #TIMER_STATE_SINGLE_SHOT_SUSPENDED means an already elapsed but not yet killed
        timer.\n
          #TIMER_STATE_KILLED indicates the temporary state, in which a timer has been
        killed by the client callback code but not yet been removed from memory.\n
          Other negative values are invalid. */
    signed int tiReload;

    /** The time at which the timer elapses. Unit is ms. For performance reasons we use the
        native int size of the platform, which may limit the maximum time span
        significantly on small 8 or 16 Bit platforms. */
    signed int tiDue;

    /** The callback to be invoked when the timer becomes due. */
    ede_callback_t callback;

#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
    /** The timer can have some user provided data, which it brings back into the callback,
        when it becomes due. This data can be useful to convey some information from the
        callback creating the timer object to the on-elapsed callback of the timer itself.
        Or if several timer objects share the same callback. The reference to the user data
        can be either an index or a pointer. */
    uintptr_t refUserContextData;
#endif

    /** The timers are organized in linked lists. Here we have the reference to the next
        timer in the list or NULL at the end of the list.
          @remark So far, the kill operation is barely used. So far this is the only
        operation, which would significantly benefit from a doubly linked list. Now it is
        of complexity O(n), where n is the number of objects but using a DLL we would
        achieve O(1) for a single kill operation. Change implementation once kill becomes
        essential in typical use cases. */
    struct ede_timer_t *pNext;

} timer_t;


/** An event for the client code, i.e. the callback into the client code, is based on or
    controlled by this kind of object. */
typedef struct event_t
{
    /** The kind of event. This value is set by the producer of the data element.\n
          In case of external events this is the integration code. Now the value is out of
        scope of the dispatcher engine. The integration code will decide, which kinds of
        event exist. It just needs to avoid the internally used values, see
        #EDE_EV_KIND_LAST for details. */
    ede_kindOfEvent_t kindOfEvent;

    /** Any event is raised by an event source, either received from some external code
        via the dispatcher queue or directly by a timer, which has that source as (grand)
        parent. This is the reference to that event source. */
    ptrToEvtSrc_t pEventSrc;
    

    /** An event is either received from some external code via a sender object and the
        interconnection object or raised by a timer object. In the latter case, we have
        here the reference to the timer object. In the former case this field is NULL. */
    timer_t *pTimer;

    /** A reference to the dispatcher, which delivered this event to the addressed
        callback. */
    ede_eventDispatcher_t *pDispatcher;

    /** The index of the dispatcher's port, which delivered this event to the addressed
        callback. */
    unsigned int idxPort;

    /** The number of actual data bytes in \a pData. */
    unsigned int sizeOfData;

    /** The data contents of the event.\n
          The alignment of the memory chunk is the alignment of a (void) pointer and an
        integer, whatever is the stronger constraint. This should be fine on all existing
        platforms to avoid misalignments of event data. Even a double or long long will
        normally be alright; these data types would likely cause problems only on a system
        with 32 Bit address bus and 64 data bus width, which can be considered a rather
        extraordinary architecture. */
    const void *pData;

} event_t;


/** The dispatcher object. */
struct ede_eventDispatcher_t
{
    /** The owning/containing dispatcher system by reference. */
    const ede_dispatcherSystem_t *pSystem;
    
    /** Pointer to the list of timers or to the first timer object in the list. NULL if and
        only if the list is empty. */
    timer_t *listOfTimerObjects;

    /** Pointer to a list of newly created timers, which have to be appended to the list of
        normally scheduled timers as soon as possible. NULL if and only if the list is
        empty. */
    timer_t *listOfNewTimerObjects;

    /** Pointer to the end of the list of new timers, i.e., to the last new timer object
        in the list. NULL if and only if the list is empty. */
    timer_t *pLastNewTimerObject;

    /** Memory reuse despite of a one-way heap: Killed timer objects are collected in a
        free list for reuse. NULL if and only if the list is empty. */
    timer_t *freeListOfTimerObjects;

    /** The processing of the queue needs to be done on a regular time base using function
        \a ede_dispatcherMain. The time distance between two calls of the clock function
        ede_dispatcherMain() is held in \a tiTick.\n
          The unit is arbitrary but the chosen unit defines the unit of all other timer
        operations at the same time. Usually it'll be a Millisecond.\n
          A signed type is used in order to permit a simple implementation of a cyclically
        running (i.e. never overrunning) counter.\n
          The possible range of timing operations is limited to the positive range of the
        integer time; although this means a significant limitation for small 8 or 16 Bit
        platforms we use the native int type rather than a long type - this is because of
        the better performance. */
    signed int tiTick;

    /** The current time in this dispatcher. The unit is the same as chosen for \a tiTick. */
    signed int tiNow;

    /** The (externally implemented) map, which associates the abstract handle of an external
        event with the internally used event source index. */
    ede_mapSenderEvHandleToIdx_t mapSdrEvHdlToEdeEvSrcIdx;

    /** The number of event input ports in \a portAry. */
    unsigned int noPorts;

    /** The list of event input ports, which provide external events from different
        senders. The port will usually be the back end of a queue. The list is implemented
        as flexible array member; therefore, it needs to be the very last field. */
    ede_eventReceiverPort_t portAry[];
};


/** The event dispatcher system: A set of dispatcher engines, which share the memory space
    and the index spaces of event sources. Different dispatchers use the same memory with
    same access constraints and they may be operated in different tasks as long as this is
    not a contradiction with the memory access constarints. */
struct ede_dispatcherSystem_t
{
    /** The memory pool for allocation of dispatcher owned objects, like event sources and
        timers. */
    ede_memoryPool_t memPool;

    /** The list of registered external event sources. */
    eventSrcExt_t *eventSrcExtAry;

    /** The maximum number of external event sources, which can be registered with the
        dispatchers of the system. */
    unsigned int maxNoEventSrcsExt;

    /** The number of external event sources, which are currently registered with the
        dispatchers of the system. */
    unsigned int noEventSrcsExt;

    /** The list of registered internal event sources. */
    struct eventSrc_t *eventSrcIntAry;

    /** The maximum number of internal event sources, which can be registered with the
        dispatchers of the system. */
    unsigned int maxNoEventSrcsInt;

    /** The number of internal event sources, which are currently registered with the
        dispatchers of the system. */
    unsigned int noEventSrcsInt;

    /** The number of dispatcher objects owned by this system. At the same time the number
        of entries in \a pDispatcherAry. */
    unsigned int noDispatchers;
    
    /* The set of dispatcher engines, which belong to the system. The array is implemented
       as flexible array member; therefore, it needs to be the very last field. */
    ede_eventDispatcher_t * pDispatcherAry[];
    
};

_Static_assert( EDE_COMMON_MACHINE_ALIGNMENT >= _Alignof(uintptr_t)
                ||  EDE_COMMON_MACHINE_ALIGNMENT == 1u
                ||  EDE_COMMON_MACHINE_ALIGNMENT == 2u
                ||  EDE_COMMON_MACHINE_ALIGNMENT == 4u
                ||  EDE_COMMON_MACHINE_ALIGNMENT == 8u
                ||  EDE_COMMON_MACHINE_ALIGNMENT == 16u
              , "Bad configuration of alignment"
              );

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
 * Create a timer object.
 *   @return
 * The timer handle is returned.\n
 *   If no timer can be created due to a lack of memory then #EDE_INVALID_TIMER_HANDLE is
 * returned instead.
 *   @param pContext
 * The dispatcher context.
 *   @param isPeriodic
 * A periodic or a single shot timer can be created.
 *   @param ti
 * The period of a periodic timer or the time span of a single shot timer. A positive
 * number is expected.\n
 *   For single-shot timers without auto-kill 0 is permitted, too; is means to create the
 * timer in suspended state. Doing so can give better control of memory allocation.
 *   @param callback
 * The callback, which is invoked at due time.
 *   @param refUserContextData
 * The user specified context information, which is stored with the timer and which will be
 * brought back into its callback at due time.\n
 *   This argument is available only if #EDE_ENABLE_TIMER_CONTEXT_DATA is set to 1.
 *   @param killAtDueTime
 * Single shot timers can be killed at due time (and after callback processing) or they can
 * stay alive for later reprogramming of a new single-shot time.
 */
static ede_handleTimer_t createTimer( const ede_callbackContext_t * const pContext
                                    , bool isPeriodic
                                    , signed int ti
                                    , ede_callback_t callback
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                    , uintptr_t refUserContextData
#endif
                                    , bool killAtDueTime
                                    )
{
    ede_eventDispatcher_t * const pDisp = pContext->pDispatcher;

    /* A timer is allocated once and simply put into the linked list of all timers, the
       order in the list doesn't actually matter. However, since the timers are tested in
       list order and to get more natural behavior at run time, we place new objects at the
       end.
         Killed timer objects are collected in the free list (as we don't want a dynamic
       memory allocation concept). Conseqeuntly, the first source of object allocation is
       this list. */
    timer_t *pTimer = NULL;
    if(pDisp->freeListOfTimerObjects != NULL)
    {
        /* Object reuse: Take a timer from the free list of returned (killed) objects. */
        pTimer = pDisp->freeListOfTimerObjects;
        pDisp->freeListOfTimerObjects = pTimer->pNext;
    }
    else
    {
        /* Allocate a new object on the (one-way) heap. Consider that at run time we have
           race conditions between different dispatchers, which might (and typically do)
           run in different task contexts. */
        const ede_memoryPool_t * const pMPool = &pDisp->pSystem->memPool;
        pTimer = pMPool->malloc(pMPool->hInstance, sizeof(timer_t));
        
        if(pTimer == NULL)
            return EDE_INVALID_TIMER_HANDLE;
    }

    /* Fill the new timer object. */

    /* The parent of the new timer is set. */
    pTimer->pRootEventSrc = pContext->pEventSrc;

    /* For single shot timers without auto-kill we permit the time 0 to express that the
       timer is created in suspended state. This gives better control on memory
       allocation. */
    EDE_ASSERT((!isPeriodic || !killAtDueTime)
               &&  (ti > 0  ||  (ti == 0 && !isPeriodic && !killAtDueTime))
              );
    pTimer->tiReload = isPeriodic
                       ? (ti >= pDisp->tiTick? ti: pDisp->tiTick)
                       : (killAtDueTime
                          ? TIMER_STATE_SINGLE_SHOT_AUTO_KILL
                          : (ti == 0
                             ? TIMER_STATE_SINGLE_SHOT_SUSPENDED
                             : TIMER_STATE_SINGLE_SHOT
                            )
                         );
    pTimer->tiDue = pDisp->tiNow + ti;
    pTimer->callback = callback;
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
    pTimer->refUserContextData = refUserContextData;
#endif
    pTimer->pNext = NULL;

    /* Add the timer to the end of newly created timers. This order is preferred in order
       to later see the same order in the callback invokation if two timers should have the
       same due time. */
    if(pDisp->listOfNewTimerObjects == NULL)
    {
        /* The list is still empty, this is the first object. */
        EDE_ASSERT(pDisp->pLastNewTimerObject == NULL);
        pDisp->listOfNewTimerObjects =
        pDisp->pLastNewTimerObject   = pTimer;
    }
    else
    {
        /* Add the new object to the end of the list. */
        EDE_ASSERT(pDisp->pLastNewTimerObject->pNext == NULL  &&  pTimer->pNext == NULL);
        pDisp->pLastNewTimerObject->pNext = pTimer;

        /* Update pLastNewTimerObject, the new object is the new last element of the list. */
        pDisp->pLastNewTimerObject = pTimer;
    }

    return pTimer;

} /* End of createTimer */





/**
 * Invoke the callback, which is associated with the given event.
 *   @param pEvent
 * The processed event.
 */
static void invokeCallback(const event_t *pEvent)
{
    /* Caution, the run-time code doesn't support a "dynamic cast", i.e., we can't double
        check, whether the event source is of base class or extended class - and only the
        latter has member callback. Never invoke this function for internal events! */
    ede_callback_t const callback = pEvent->pTimer != NULL? pEvent->pTimer->callback
                                                          : pEvent->pEventSrc.ext->callback;
    EDE_ASSERT(callback != NULL);
    callback(pEvent);

} /* End of invokeCallback */



/**
 * Support of "dynamic cast" between base and extended class of event sources: A reference
 * to such an object is checked by run-time value to which of the two it belongs.
 *   @return
 * Get \a true if the event source is an external one, \a false otherwise.
 *   @param pSystem
 * The identification requires access to the dispatcher system, which owns the references
 * event source.
 *   @param pEventSrc
 * The reference to an event source, which could be either internalor external.
 */
static inline bool isExtEventSrc( const ede_dispatcherSystem_t * const pSystem
                                , const ptrToEvtSrc_t pEventSrc
                                )
{
    const eventSrcExt_t * const pFrom = &pSystem->eventSrcExtAry[0];
    const eventSrcExt_t * const pTo   = pFrom + pSystem->noEventSrcsExt;;
    if(pEventSrc.ext >= pFrom  &&  pEventSrc.ext < pTo)
        return true;
    else
    {
#ifdef DEBUG
        const eventSrc_t * const pFrom = &pSystem->eventSrcIntAry[0];
        const eventSrc_t * const pTo   = pFrom + pSystem->noEventSrcsInt;;
        EDE_ASSERT(pEventSrc.base >= pFrom  &&  pEventSrc.base < pTo);
#endif
        return false;
    }
} /* isExtEventSrc */




/**
 * Helper function for the implementation of the API for the callbacks: The pointer to the
 * event source object is retrieved, which relates to the callback context. This can be the
 * direct source of the event or in case of timer callbacks the (grand) parent of the
 * timer, which then needs to be an event source.
 *   @return
 * The pointer to the event source.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static inline const eventSrc_t *getEventSourceFromContext
                                                (const ede_callbackContext_t * const pContext)
{
    EDE_ASSERT(pContext->pEventSrc.base != NULL);
    return pContext->pEventSrc.base;

} /* End of getEventSourceFromContext */




/**
 * From a callback, retrieve the handle of a time object. The function supports two cases:
 * Either the timer is explicitly named or \a hTimer is Null. In the former case just the
 * named timer is returned. In the latter case it is validated that the call is made from a
 * timer callback and the handle of the causing timer is returned.
 *   @return
 * Get the addressed timer object's handle.
 *   @param pContext
 * The callback context, can be a received external event or a timer event.
 *   @param hTimer
 * A valid timer handle or NULL if the the event causing timer is meant.
 */
static inline ede_handleTimer_t getTimerObject( const ede_callbackContext_t * const pContext
                                              , ede_handleTimer_t hTimer
                                              )
{
    if(hTimer == NULL)
    {
        EDE_ASSERT(pContext->kindOfEvent == EDE_EV_TIMER_ELAPSED);
        hTimer = pContext->pTimer;
    }
    EDE_ASSERT(hTimer != NULL);

    return hTimer;

} /* End of getTimerObject */



/**
 * Create a dispatcher.\n
 *   The dispatcher delivers events to the client code, which is completely organized as
 * set of callbacks, which implement the reaction on the events. The root of all is the
 * initialization call(back), which is made for each registered event source.\n
 *   Events can be external events (their meaning is fully determined by the integration
 * code) or internal timer events.\n
 *   A dispatcher is single-threaded. There are no race conditions between callbacks, which
 * makes the design of the event handling code easy and safe. If events are logically
 * connected to several application tasks then one would create an according number of
 * dispatchers and each events goes to the dispatcher in the appropriate, associated
 * application task. For use case CAN communication, this could mean to process fast
 * regular messages with one dispatcher in a fast application task and all other messages
 * in a slower task.\n
 *   Events can carry data of variable size. For use case CAN communication, this could be
 * the message payload in case of message reception events or some fault status information
 * for message send acknowledge events.\n
 *   In general, the data elements are opaque to the dispatcher engine. Filling the
 * contents is done as part of the integration code and evaluating the data elements, too.
 * The engine will just ensure proper delivery of the event together with the data it
 * carries.
 *   @return
 * Get \a true if the new system could be created and \a false otherwise.\n
 *   The function will fail only in case of lack of memory. Since all memory allocation is
 * static and deterministic an appropriate and recommended failure handling concept is to
 * check the return value by assertion only. If the assertion doesn't fire throughout the
 * development and test phase then it won't in the production code. Anyhow, the dispatcher
 * system must never be used if this function returns \a false.
 *   @param pHandleDispSystem
 * Get the handle of the newly created dispatcher object by reference. This handle is later
 * needed to use the dispatcher. If the function returns \a false then it'll return the
 * special handle #EDE_INVALID_DISPATCHER_SYSTEM_HANDLE in * \a pHandleDispSystem.\n
 *   @param tiTick
 * The processing of the queue needs to be done on a regular time base using function \a
 * ede_dispatcherMain(). The time distance between two calls of this function
 * needs to be known for the timer operations and is passed in as \a
 * tiTick.\n
 *   The value needs to be a positive integer and should not be too large: No timing
 * operation shorter or faster than the value passed in here will become possible. This
 * relates to raising events and checking timeouts of operations.\n
 *   The unit is arbitrary but the chosen unit defines the unit of all other timer
 * operations at the same time. Usually it'll be a Millisecond.
 *   @param maxNoEventSourcesExt
 * The maximum number of different sources of external events, that will be received through
 * the ports. This number of event sources can be registered for the new dispatcher and
 * using ede_registerExternalEventSource().
 *   @param maxNoEventSourcesExt
 * The maximum number of different sources of external events, that will be received through
 * the ports. This number of event sources can be registered fot the new dispatcher and
 * using ede_registerExternalEventSource().
 *   @param mapSdrEvHdlToEdeEvSrcIdx
 * The (externally implemented) map, which associates the abstract handle of an external
 * event with the internally used event source index. See data type \a
 * ede_mapSenderEvHandleToIdx_t for more details.
 *   @param pMemPoolDispatchingProcess
 * A memory pool by reference, which provides the memory needed for construction of the
 * dispatcher object.\n
 *   The memory dealt out by this pool needs to grant write-access to the context that runs
 * the dispatching process, i.e. which is going to regularly call ede_dispatcherMain() for
 * the here created dispatcher object. All other contexts don't need access to the memory.
 *   @remark
 * The call of this function is assumed to be done in a race condition free environment,
 * prior to entering the multi-tasking phase of the application. Most platforms will offer
 * an initialization task for this purpose.\n
 *   See ede_createDispatcher() for more details on race conditions and use in concurrent
 * environments.
 */
bool ede_createDispatcherSystem( ede_handleDispatcherSystem_t * const pHandleDispSystem
                               , unsigned int noEventDispatcherEngines
                               , unsigned int maxNoEventSourcesExt
                               , unsigned int maxNoEventSourcesInt
                               , ede_memoryPool_t * const pMemPoolDispatchingProcess
                               )
{
    *pHandleDispSystem = EDE_INVALID_DISPATCHER_SYSTEM_HANDLE;

    if(noEventDispatcherEngines < 1u
       ||  (maxNoEventSourcesExt < 1u  &&  maxNoEventSourcesInt < 1u)
      )
    {
        /* Invalid configuration of dispatcher system. */
        EDE_ASSERT(false);
        return false;
    }

    /* Flexible array member: The size of the dispatcher system object depends on the
       number of dispatcher engines. */
    const unsigned int sizeOfSystemObj = sizeof(ede_dispatcherSystem_t)
                                         + noEventDispatcherEngines
                                           * sizeof(ede_eventDispatcher_t*);

    /* The dispatcher system object is created in the memory pool of the dispatching
       process. */
    ede_dispatcherSystem_t * const pSys = pMemPoolDispatchingProcess->malloc
                                                ( pMemPoolDispatchingProcess->hInstance
                                                , sizeOfSystemObj
                                                );
    if(pSys == NULL)
        return false;

    /* Initialize the event source arrays. */
    if(maxNoEventSourcesExt > 0u)
    {
        pSys->eventSrcExtAry = pMemPoolDispatchingProcess->malloc
                                                ( pMemPoolDispatchingProcess->hInstance
                                                , sizeof(eventSrcExt_t) * maxNoEventSourcesExt
                                                );
        if(pSys->eventSrcExtAry == NULL)
            return false;
    }
    else
        pSys->eventSrcExtAry = NULL;

    if(maxNoEventSourcesInt > 0u)
    {
        pSys->eventSrcIntAry = pMemPoolDispatchingProcess->malloc
                                                ( pMemPoolDispatchingProcess->hInstance
                                                , sizeof(eventSrcExt_t) * maxNoEventSourcesInt
                                                );
        if(pSys->eventSrcIntAry == NULL)
            return false;
    }
    else
        pSys->eventSrcIntAry = NULL;
        
    pSys->noDispatchers = noEventDispatcherEngines;
    pSys->maxNoEventSrcsExt = maxNoEventSourcesExt;
    pSys->maxNoEventSrcsInt = maxNoEventSourcesInt;
    pSys->noEventSrcsExt = 0u;
    pSys->noEventSrcsInt = 0u;
    pSys->memPool = *pMemPoolDispatchingProcess;
    for(unsigned int idxDisp=0u; idxDisp<noEventDispatcherEngines; ++idxDisp)
        pSys->pDispatcherAry[idxDisp] = INVALID_DISPATCHER_HANDLE;

    *pHandleDispSystem = pSys;
    return pSys;

} /* End of ede_createDispatcherSystem */



/**
 * Create a dispatcher.\n
 *   The dispatcher delivers events to the client code, which is completely organized as
 * set of callbacks, which implement the reaction on the events. The root of all is the
 * initialization call(back), which is made for each registered event source.\n
 *   Events can be external events (their meaning is fully determined by the integration
 * code) or internal events. An internal event actually means the initialization callback
 * and later timer events, triggered from there.\n
 *   A dispatcher is single-threaded. There are no race conditions between callbacks, which
 * makes the design of the event handling code easy and safe. If events are logically
 * connected to several application tasks then one would create an according number of
 * dispatchers and each events goes to the dispatcher in the appropriate, associated
 * application task. For use case CAN communication, this could mean to process fast
 * regular messages with one dispatcher in a fast application task and all other messages
 * in a slower task.\n
 *   Events can carry data of variable size. For use case CAN communication, this could be
 * the message payload in case of message reception events or some fault status information
 * for message send acknowledge events.\n
 *   In general, the data elements are opaque to the dispatcher engine. Filling the
 * contents is done as part of the integration code and evaluating the data elements, too,
 * inside the external callback implementation. The engine will just ensure proper delivery
 * of the event together with the data it carries.
 *   @return
 * Get \a true if dispatcher creation succeeded. \a false would be returned in case of
 * bad function arguments or if an already created dispatcher instance is re-created (both
 * caught by assertion, too) or if the dispatcher system's memory pool is exhausted.\n
 *   Beside obvious programming errors in the calling code, the function will fail only in
 * case of lack of memory. Since all memory allocation is static and deterministic an
 * appropriate and recommended failure handling concept is to check the return value by
 * assertion only. If the assertion doesn't fire throughout the development and test phase
 * then it won't in the production code. Anyhow, the dispatcher must never be used if this
 * function returns \a false.
 *   @param pSys
 * The dispatcher system by reference, which owns the dispatcher. At creation time of a
 * system, the number of contained dispatchers is specified and one out of these is now
 * initialized. All of these dispatchers share the same memory space and access rights and
 * they share the index spaces of external and internal event sources. (Although not the
 * event sources themselves.)
 *   @param tiTick
 * The processing of the received and timer events needs to be done on a regular time base
 * using function \a ede_dispatcherMain(). The time distance between two calls of this
 * function needs to be known for the timer operations and is passed in as \a tiTick.\n
 *   The value needs to be a positive integer and should not be too large: No timing
 * operation shorter or faster than the value passed in here will become possible. This
 * relates to raising events and checking timeouts of operations.\n
 *   The unit is arbitrary but the chosen unit defines the unit of all other timer
 * operations at the same time. Usually it'll be a Millisecond and this is what the
 * function documentation normally assumes.
 *   @param portAry
 * The input port instances. They are passed in and copied as an array and the index order
 * in \a portAry is the same as later used at run-time, it is e.g. visible as origin of an
 * event in the callback.
 *   @param noPorts
 * The number of input ports of this dispatcher.
 *   @param mapSdrEvHdlToEdeEvSrcIdx
 * The (externally implemented) map, which associates the abstract handle of an external
 * event with the internally used event source index. See data type \a
 * ede_mapSenderEvHandleToIdx_t for more details.
 *   @remark
 * The call of this function is assumed to be done in a still race condition free
 * environment, prior to entering the multi-tasking phase of the application. Most
 * platforms will offer an initialization task for this purpose.\n
 *   Race conditions occur inside one dispatcher system between creation of different
 * dispatchers and registering of events. All of these functions need to be called strictly
 * sequentially for one and the same system.\n
 *   Race conditions between different dispatcher systems do only occur through their
 * memory pool. If both use the same one (and if it doesn't do the mutual exclusion
 * internally), then the statement before holds for the union of both systems.
 */
bool ede_createDispatcher( ede_dispatcherSystem_t * const pSys
                         , unsigned int idxDispatcher
                         , signed int tiTick
                         , ede_eventReceiverPort_t portAry[]
                         , unsigned int noPorts
                         , ede_mapSenderEvHandleToIdx_t mapSdrEvHdlToEdeEvSrcIdx
                         )
{
    if(noPorts < 1u  ||  tiTick <= 0  ||  idxDispatcher >= pSys->noDispatchers)
    {
        /* Invalid configuration of dispatcher. */
        EDE_ASSERT(false);
        return false;
    }

    /* A dispatcher must not be created twice. */
    ede_eventDispatcher_t *pDisp = pSys->pDispatcherAry[idxDispatcher];
    if(pDisp != NULL)
    {
        EDE_ASSERT(false);
        return false;
    }
    
    /* Flexible array member: The size of the dispatcher object depends on the number of
       ports. */
    const unsigned int sizeOfDispObj = sizeof(ede_eventDispatcher_t)
                                       + noPorts * sizeof(portAry[0]);

    /* The dispatcher object is created in the memory pool of the dispatching process. */
    pDisp = pSys->memPool.malloc( pSys->memPool.hInstance
                                , sizeOfDispObj
                                );
    if(pDisp == NULL)
        return false;

    pDisp->pSystem = pSys;
    pDisp->listOfTimerObjects = NULL;
    pDisp->listOfNewTimerObjects = NULL;
    pDisp->pLastNewTimerObject = NULL;
    pDisp->freeListOfTimerObjects = NULL;
    pDisp->tiTick = tiTick;
    pDisp->tiNow = 0;
    pDisp->mapSdrEvHdlToEdeEvSrcIdx = mapSdrEvHdlToEdeEvSrcIdx;
    pDisp->noPorts = noPorts;
    for(unsigned int idxPort=0u; idxPort<noPorts; ++idxPort)
        pDisp->portAry[idxPort] = portAry[idxPort];

    /* Put the ready dispatcher object into the owning system object. */
    pSys->pDispatcherAry[idxDispatcher] = pDisp;

    return true;

} /* End of ede_createDispatcher */



/**
 * Registration of an external event source: A newly created event source object shapes the
 * association between the abstract handle of the event as used by its producer/origin, a
 * given dispatcher and an event callback. Having this association for all possible events,
 * the dispatcher engine can receive events, decode their handle and delegate the
 * processing of the event to the dedicated (external) callback. This event processing can
 * be done safely and free of race conditions in the context, which owns the dispatcher.
 * This context can be another application task as the event producing context, on the same
 * or on another core.
 *   @return
 * Internally, the dispatcher organizes all registered external event sources in an array.
 * The linear, zero based index into this array is returned in case of success.\n
 *   Please note, the returned index is basically redundant information since the indexes
 * will be dealt out in strictly incremental order in each invocation of this method.
 * Knowing this, the design of the client code can make use of pre-determined constants
 * rather than dealing with run time stored IDs.\n
 *   Note that internal events (see ede_registerInternalEventSource()) spawn their own,
 * zero based index. An index on its own can't identify an event source.\n
 *   #EDE_INVALID_EVENT_SOURCE_INDEX is returned if more external event sources are
 * registered as had been declared in ede_createDispatcher().
 *   @param hDispatcherSystem
 * The event dispatcher system, which owns the dispatcher engine to use with the registered
 * event source.
 *   @param idxDispatcher
 * The dispatcher object that is associated with the registered event source and which is
 * going process its events. The dispatcher is identified by the index in the owning
 * system, the index which had been specified in ede_createDispatcher(), too.\n
 *   All existing dispatchers are functionally identical but the integration code can
 * configure them differently and assign them to different use cases, and most often to
 * different application task contexts. The appropriate dispatcher for the registered event
 * source is passed in.
 *   @param kindOfEvent
 * The kind of event. It is passed together with \a senderHandleEvent to the handle map
 * owned by the dispatcher.\n
 *   The enumeration \a kindOfEvent is meaningless to the sender and dispatcher object.
 * Which values are passed is entirely in the scope of the integration code, which defines
 * both, the event reporting interrupts and the client code, which eventually evaluates the
 * transmitted events. In the case of CAN communication, this will e.g. be the CAN message
 * reception event.
 *   @param senderHandleEvent
 * The event's handle as used (and issued) by the external integration code. In the case of
 * CAN communication, this will e.g. be the operating system's handle of a registered CAN
 * message.
 *   @param callback
 * The callback related to the registered event source. The evaluation of all events
 * associated with the registered source will be delegated to this (external) function. The
 * callback is invoked the first time immediately after registration of the event source
 * (and still from within this method), which permits to do further initialization there.\n
 *   Note, for the first, initializing callback, the kind of event will be set to
 * #EDE_EV_EVENT_SOURCE_EXT_INIT; all later events received events from the registered
 * source will have \a kindOfEvent as kind of event.
 *   @param refEventSourceData
 * Some context data associated with the event source can be specified by reference. The
 * reference can be an index or a pointer. The same reference is available to the callback,
 * which is invoked later whenever an event from this source is processed.\n
 *   Reference and referenced data are entirely meaningless to the dispatcher. The only
 * thing it does is providing the service to store and deliver the reference. (And,
 * particularly, not the data behind the reference!)
 *   @remark
 * The call of this function is assumed to be done in a still race condition free
 * environment, prior to entering the multi-tasking phase of the application when actual
 * event dispatching takes place. Most platforms will offer an initialization task for this
 * purpose.\n
 *   See ede_createDispatcher() for more details on race conditions and use in concurrent
 * environments.
 */
unsigned int ede_registerExternalEventSource
                            ( ede_handleDispatcherSystem_t const hDispatcherSystem
                            , unsigned int idxDispatcher
                            , ede_kindOfEvent_t kindOfEvent
                            , ede_senderHandleEvent_t senderHandleEvent
                            , ede_callback_t callback
                            , uintptr_t refEventSourceData
                            )
{
    ede_dispatcherSystem_t * const pSystem = hDispatcherSystem;
    if(pSystem == EDE_INVALID_DISPATCHER_SYSTEM_HANDLE  ||  callback == NULL
       ||  idxDispatcher >= pSystem->noDispatchers
      )
    {
        EDE_ASSERT(false);
        return EDE_INVALID_EVENT_SOURCE_INDEX;
    }
    ede_eventDispatcher_t * const pDispatcher = pSystem->pDispatcherAry[idxDispatcher];

    /* Find the new entry in the internal table of all registered event sources. Nothing
       else to be done if the table is full. */
    if(pSystem->noEventSrcsExt >= pSystem->maxNoEventSrcsExt)
        return EDE_INVALID_EVENT_SOURCE_INDEX;
    const unsigned int idxEvSrc = pSystem->noEventSrcsExt++;
    eventSrcExt_t * const pEventSrc = &pSystem->eventSrcExtAry[idxEvSrc];

    pEventSrc->callback = callback;
    pEventSrc->refEventSrcData = refEventSourceData;
#if EDE_CHECK_FOR_EVENT_DELIVERY_TO_ASSOCIATED_DISPATCHER == 1u
    pEventSrc->pDispatcher = pDispatcher;
#endif

    /* Normally, the external, integrator provided code has a map, which associates the
       abstract handle of the sender with the engine's event source index. This mapping is
       likely required at runtime to relate an external event, identified by the sender
       handle to the information held in the event source, which is owned by the
       dispatcher. The next call gives the external code the opportunity to add the next
       key value pair to its map.
         In simple environments the mapping might be not used, e.g. if the operating system
       (sender) uses the same zero based index as handle as the dispatcher engine does, or
       the mapping is known beforehand and without run time information. In these cases the
       function pointer will be configured to be NULL. */
    const ede_mapSenderEvHandleToIdx_t * const pMap = &pDispatcher->mapSdrEvHdlToEdeEvSrcIdx;
    if(pMap->addKeyValuePair != NULL && !pMap->addKeyValuePair( pMap->hInstance
                                                              , kindOfEvent
                                                              , senderHandleEvent
                                                              , idxEvSrc
                                                              )
      )
    {
        /* Error in external code: No space left in its map. The event source can't be
           registered. */
        -- pSystem->noEventSrcsExt;
        return EDE_INVALID_EVENT_SOURCE_INDEX;
    }

    /* In case of success, invoke the registered callback, which has the meaning of an
       initialization callback this time. */
    event_t evInit = { .kindOfEvent = EDE_EV_EVENT_SOURCE_EXT_INIT
                     , .pEventSrc.ext = pEventSrc
                     , .pTimer = NULL
                     , .pDispatcher = pDispatcher
                     , .idxPort = UINT_MAX
                     , .sizeOfData = 0
                     , .pData = NULL
                     };
    invokeCallback(&evInit);

    return idxEvSrc;

} /* End of ede_registerExternalEventSource */




/**
 * Registration of an internal event source. An internal event source is transient in a
 * certain way: It emits just one event, its initialization event. The use case is having
 * the initialization of some timing logic in the initialization call back, i.e., the
 * creation of some timers, which control some later activities.\n
 *   Use case CAN communication: We could implement outbound messages in this way. The
 * initialization callback from the registration of a Tx message would install a periodic
 * timer, and the on-elapse callback of this timer would implement the send message
 * operation.\n
 *   Note, the registered event source is persistent, although it produces just one event:
 * It remains the parent of all created timers and these timers have therefore access to
 * the context data associated with the event source (see below).
 *   @return
 * Internally, the dispatcher organizes all registered internal event sources in an array.
 * The linear, zero based index into this array is returned in case of success.\n
 *   Please note, the returned index is basically redundant information since the indexes
 * will be dealt out in strictly incremental order in each invocation of this method.
 * Knowing this, the design of the client code can make use of pre-determined constants
 * rather than dealing with run time stored IDs.\n
 *   Note that external events (see ede_registerExternalEventSource()) spawn their own,
 * zero based index. An index on its own can't identify an event source.\n
 *   #EDE_INVALID_EVENT_SOURCE_INDEX is returned if more internal event sources are
 * registered as had been declared in ede_createDispatcher().
 *   @param hDispatcherSystem
 * The event dispatcher system, which owns the dispatcher engine to use with the registered
 * event source.
 *   @param idxDispatcher
 * The dispatcher object that is associated with the registered event source and which is
 * going process its events. The dispatcher is identified by the index in the owning
 * system, the index which had been specified in ede_createDispatcher(), too.\n
 *   All existing dispatchers are functionally identical but the integration code can
 * configure them differently and assign them to different use cases, and most often to
 * different application task contexts. The appropriate dispatcher for the registered event
 * source is passed in.
 *   @param hDispatcher
 * The handle of the dispatcher object that is associated with the registered event source
 * and which is going process its event. The dispatcher is identified by the index in the
 * owning system, the index which had been specified in ede_createDispatcher(), too.\n
 *   All existing dispatchers are functionally identical but the integration code can
 * configure them differently and assign them to different use cases, and most often to
 * different application task contexts. The appropriate dispatcher for the registered event
 * source is passed in.
 *   @param callback
 * The callback related to the registered event source. The callback is invoked immediately
 * after registration of the event source (and still from within this method), which
 * permits to do further initialization there. The initializing callback receives
 * #EDE_EV_EVENT_SOURCE_INT_INIT as kind of event.
 *   @param refEventSourceData
 * Some context data associated with the event source can be specified by reference. The
 * reference can be an index or a pointer. The same reference is available to the
 * initialization callback and the callbacks of all timers, which are created in the
 * initialization callback.\n
 *   Reference and referenced data are entirely meaningless to the dispatcher. The only
 * thing it does is providing the service to store and deliver the reference. (And,
 * particularly, not the data behind the reference!)
 *   @remark
 * The call of this function is assumed to be done in a still race condition free
 * environment, prior to entering the multi-tasking phase of the application when actual
 * event dispatching takes place. Most platforms will offer an initialization task for this
 * purpose.\n
 *   See ede_createDispatcher() for more details on race conditions and use in concurrent
 * environments.
 */
unsigned int ede_registerInternalEventSource( ede_dispatcherSystem_t * const pSystem
                                            , unsigned int idxDispatcher
                                            , ede_callback_t callback
                                            , uintptr_t refEventSourceData
                                            )
{
    if(pSystem == EDE_INVALID_DISPATCHER_SYSTEM_HANDLE  ||  callback == NULL
       ||  idxDispatcher >= pSystem->noDispatchers
      )
    {
        EDE_ASSERT(false);
        return EDE_INVALID_EVENT_SOURCE_INDEX;
    }

    /* Find the new entry in the internal table of all registered event sources. Nothing
       else to be done if the table is full. */
    if(pSystem->noEventSrcsInt >= pSystem->maxNoEventSrcsInt)
        return EDE_INVALID_EVENT_SOURCE_INDEX;
    const unsigned int idxEvSrc = pSystem->noEventSrcsInt++;
    eventSrc_t * const pEventSrc = &pSystem->eventSrcIntAry[idxEvSrc];

    pEventSrc->refEventSrcData = refEventSourceData;

    /* In case of success, invoke the registered callback, which has the meaning of an
       initialization callback this time. */
    event_t evInit = { .kindOfEvent = EDE_EV_EVENT_SOURCE_INT_INIT
                     , .pEventSrc.base = pEventSrc
                     , .pTimer = NULL
                     , .pDispatcher = pSystem->pDispatcherAry[idxDispatcher]
                     , .idxPort = UINT_MAX
                     , .sizeOfData = 0
                     , .pData = NULL
                     };
    callback(&evInit);

    return idxEvSrc;

} /* End of ede_registerInternalEventSource */



/**
 * The regular tick function of a dispatcher. This function is invoked from the (periodic)
 * task, which processes the dispatched events. Example CAN communication: This is normally
 * the APSW task, which receives and sends the CAN frames, which are associated with the
 * given dispatcher.\n
 *   All notifications and timer operations and thus all event related actions are done
 * in the context of this function call (actually as sub-routines of this invokation) and
 * they are therefore completely race conidtion free with the rest of the same task's
 * code.
 *   @param hDispatcherSystem
 * The event dispatcher system, which owns the dispatcher engine to be clocked.
 *   @param idxDispatcher
 * The dispatcher object, which is clocked. The dispatcher is identified by the index in
 * the owning system, the index which had been specified in ede_createDispatcher(), too.
 *   @remark
 * The call of this function is race condition free with respect to other dispatchers,
 * regardless whether they belong to the same or another dispatcher system.
 */
void ede_dispatcherMain( ede_handleConstDispatcherSystem_t const hDispatcherSystem
                       , unsigned int idxDispatcher
                       )
{
    const ede_dispatcherSystem_t * const pSystem = hDispatcherSystem;
    EDE_ASSERT(pSystem != EDE_INVALID_DISPATCHER_SYSTEM_HANDLE
               &&  idxDispatcher < pSystem->noDispatchers
              );
    ede_eventDispatcher_t * const pDisp = pSystem->pDispatcherAry[idxDispatcher];
    EDE_ASSERT(pDisp != INVALID_DISPATCHER_HANDLE);
    
    event_t event = {.pDispatcher = pDisp, .pTimer = NULL,};

    /* Process all meanwhile received external events. The ports are iterated in order of
       appearance - this is the prioritization scheme for ports. */
    for(event.idxPort=0u; event.idxPort<pDisp->noPorts; ++event.idxPort)
    {
        ede_eventReceiverPort_t * const pPort = &pDisp->portAry[event.idxPort];
        while(true)
        {
            /* Check the dispatcher port for a received event. If any, return it by
               reference. We own this element until we explicitly release it (see below).
               We get NULL if there's no newly received event. */
            const ede_externalEvent_t *pExternalEvent = pPort->readBuffer( pPort->hInstance
                                                                         , &event.sizeOfData
                                                                         );
            if(pExternalEvent == NULL)
                break;

            event.kindOfEvent = pExternalEvent->kindOfEvent;
            event.pData = (const void*)&pExternalEvent->dataAry[0];

            /* The sender's event handle is mapped to the internally used index of the
               related event source. */
            unsigned int idxEvSrc;
            const ede_mapSenderEvHandleToIdx_t * const pMap = &pDisp->mapSdrEvHdlToEdeEvSrcIdx;
            if(pMap->getValue( pMap->hInstance
                             , &idxEvSrc
                             , event.kindOfEvent
                             , pExternalEvent->senderHandleEvent
                             )
              )
            {
                EDE_ASSERT(idxEvSrc < pSystem->noEventSrcsExt);
                event.pEventSrc.ext = &pSystem->eventSrcExtAry[idxEvSrc];
                
#if EDE_CHECK_FOR_EVENT_DELIVERY_TO_ASSOCIATED_DISPATCHER == 1u
                if(event.pEventSrc.ext->pDispatcher == pDisp)
#endif
                {
                    /* Process the event and the contained data by forwarding it to the
                       client code (outside the dispatcher engine). This code is normally
                       auto-coded from the network database file and is aware of the
                       meaning of the received events. */
                    invokeCallback(&event);
                }
#if EDE_CHECK_FOR_EVENT_DELIVERY_TO_ASSOCIATED_DISPATCHER == 1u
                else
                {
                    /* The next assertion will fire, if a sender has posted its event to
                       the wrong dispatcher. */
                    EDE_ASSERT(false);
                }
#endif
            }
            else
            {
                /* The handle map doesn't know the event. This is normally an implementation
                   error in the external code and we could even have an assertion here.
                   However, the mapping has been specified tolerant, only the event is lost. */
                /// @todo Should this be counted like a lost event due to queue full?
                //EDE_ASSERT(false);
            }
            
            /* All reading on port's data is done. Release it. */
            pPort->freeBuffer(pPort->hInstance);
            
        } /* while(All meanwhile received events) */
    } /* for(All event input ports) */

    /* Visit all timers and process all due internal (timer) events. */
    timer_t *pTimer = pDisp->listOfTimerObjects
          , **pLinkPtr = &pDisp->listOfTimerObjects;
    while(pTimer != NULL)
    {
        if(pTimer->tiReload == TIMER_STATE_KILLED)
        {
            /* The timer was scheduled for deletion. This operation is not done immediately
               but only now, synchronously with processing the timers in order to avoid
               undefined intermediate states from the perspective of the callbacks. */

            /* A single shot timer with automatic kill. It is removed from the list. */
            *pLinkPtr = pTimer->pNext;

            /* We have a one-way memory allocation concept. The removed object is not
               freed but put into the freelist for reuse. */
            pTimer->pNext = pDisp->freeListOfTimerObjects;
            pDisp->freeListOfTimerObjects = pTimer;

            /* Continue the main loop along active timers. */
            pTimer = *pLinkPtr;
        }
        else
        {
            /* Check if timers became due. We use a signed comparison as simplest
               implementation of a cyclically defined less or equal operation. The second
               condition considers elapsed but not killed single shot timers, which must
               not fire again. */
            if((signed)((unsigned)pDisp->tiNow - (unsigned)pTimer->tiDue) >= 0
               &&  pTimer->tiReload != TIMER_STATE_SINGLE_SHOT_SUSPENDED
              )
            {
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                const unsigned int sizeOfPayload = sizeof(pTimer->refUserContextData);
                const void * const payload = &pTimer->refUserContextData;
#else
                const unsigned int sizeOfPayload = 0;
                const void * const payload = NULL;
#endif
                event.kindOfEvent = EDE_EV_TIMER_ELAPSED;
                event.pEventSrc = pTimer->pRootEventSrc;
                event.pTimer = pTimer;
                /* .pDispatcher is still set correctly. */
                event.idxPort = UINT_MAX;
                event.sizeOfData = sizeOfPayload;
                event.pData = payload;

                invokeCallback(&event);

                /* Update the due time of the timer. */
                if(pTimer->tiReload > 0)
                {
                    /* A periodic timer, the next due time is programmed. */
                    pTimer->tiDue += pTimer->tiReload;
                }
                else if(pTimer->tiReload == TIMER_STATE_SINGLE_SHOT)
                {
                    /* A single shot timer, which is not automatically killed after
                       elapsing. */

                    /* The is-elapsed condition is now tested a second time in order to
                       find out if the timer has been reprogrammed in its callback. */
                    if((signed)((unsigned)pDisp->tiNow - (unsigned)pTimer->tiDue) >= 0)
                    {
                        /* The timer stays elapsed. It remains in the list as an inactive
                           timer. This is indicated by a special predefined reload value. */
                        pTimer->tiReload = TIMER_STATE_SINGLE_SHOT_SUSPENDED;
                    }
                    else
                    {
                        /* The timer got a new due time and keeps on running. */
                    }
                }
                else if(pTimer->tiReload == TIMER_STATE_SINGLE_SHOT_AUTO_KILL)
                {
                    /* The timer object is scheduled for deletion. */
                    pTimer->tiReload = TIMER_STATE_KILLED;
                }
                else
                {
                    /* The timer can be in state killed or suspended if the according API
                       function has been called from within the callback of the timer.
                       (See ede_killTimer and ede_suspendSingleShotTimer.) */
                }
            } /* if(Is tested timer due?) */

            /* Advance to next timer object. */
            pLinkPtr = &pTimer->pNext;
            pTimer = pTimer->pNext;

        } /* if(Timer object scheduled for deletion or still operational?) */

    } /* while(All existing timer objects) */

    /* Add the list of timers newly created in the callbacks of the visit-all-timers loop
       to the list of active timers. They will be checked for due time the first time in
       the next time tic. */
    if(pDisp->listOfNewTimerObjects != NULL)
    {
        /* *pLinkPtr is either the link pointer of the last element of the non-empty timer
           list or the list pointer of the dispatcher. Append the newly-created list by
           overwriting this pointer. */
        EDE_ASSERT(*pLinkPtr == NULL);
        *pLinkPtr = pDisp->listOfNewTimerObjects;

        /* Clear the list of new timers, needed only to temporarily collect new objects. */
        pDisp->listOfNewTimerObjects =
        pDisp->pLastNewTimerObject   = NULL;

    } /* if(Have new timer objects been created in this tic?) */

    /* (Cyclically) increment the time. */
    pDisp->tiNow += pDisp->tiTick;

} /* ede_dispatcherMain */




/**
 * Create a periodic timer event from a callback.\n
 *   Typical use case in the context of CAN communication is a timer, which triggers
 * sending of regular frames.
 *   @return
 * The timer handle is returned; this handle is used to identify a timer (if several timers
 * should share the same callback function) or to perform other operations on this timer.\n
 *   If no timer can be created due to a lack of memory then #EDE_INVALID_TIMER_HANDLE is
 * returned instead. Due to the static, deterministic error allocation concept this error
 * should preferrably be handled by a simple assertion only; if this assertion doesn't fire
 * in the DEBUG compilation then there won't be an error in the production code neither.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param tiPeriod
 * The timer will invoke the specified callback \a callback every \a tiPeriod time units.
 * The unit is the same as that of argument \a tiTick in the call of
 * ede_createDispatcher().\n
 *   The value needs to be positive. If it is less than the tick time of the dispatcher than
 * it is rounded upwards to this tick time; the timer will fire in every tick of the
 * dispatcher.\n
 *   The cycle time is not rounded to a multiple of the dispatcher's clock tick. If \a
 * tiPeriod is not a multiple of the clock tick then the timer will always fire at the
 * first tick at or after the next nominal due time. The timer events are no longer
 * equidistant but the nominal cycle time is kept in average.
 *   @param callback
 * Please refer to \a tiPeriod.
 *   @param refUserContextData
 * The user specified context information, which is stored with the timer and which will be
 * brought back into its callback at due time. In the timer's callback, use \a
 * ede_getEventData() to retrieve the value passed in here. The data type of the user
 * specified context data is \a uintptr_t; if you pass in a pointer to some data then
 * ede_getEventData() will only return the pointer - not the data it points to.\n
 *   This argument is available only if #EDE_ENABLE_TIMER_CONTEXT_DATA is set to 1.
 *   @remark
 * This method and ede_createSingleShotTimer() are the only pieces of code in the
 * dispatcher implementation, which could suffer from race conditions. The timer objects
 * are created from the memory pool specified in ede_createDispatcherSystem(). Race conditions
 * would occur if another task calls ede_dispatcherMain() for another dispatcher object and
 * that dispatcher coincidently creates a timer and both dispatchers use the same memory
 * pool. (Two dispatchers will always use the same memory pool if they belong to the same
 * system!)\n 
 *   In such a scenario, you'd need to use an implementation of the memory pool interface
 * with appropriate mutual exclusion mechanism. The default implementation of the CAN
 * interface, mem_malloc.c, allows using a guard function provided by the
 * integration code, see argument \a mutualExclusionGuard of its constructor
 * mem_createMemoryPool().\n
 *   Even better is either having separated memory pools for concurrently executed
 * dispatchers (not possible for same system) or not using the timer creation API at
 * dispatcher run time. Instead, create your timers preferably at system initialization
 * time.
 */
ede_handleTimer_t ede_createPeriodicTimer( const ede_callbackContext_t * const pContext
                                         , signed int tiPeriod
                                         , ede_callback_t callback
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                         , uintptr_t refUserContextData
#endif
                                         )
{
    return createTimer( pContext
                      , /* isPeriodic */ true
                      , tiPeriod
                      , callback
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                      , refUserContextData
#endif
                      , /* killAtDueTime */ false
                      );
} /* End of ede_createPeriodicTimer */





/**
 * Create a single shot timer event from a callback.\n
 *   Typical use case is a timer, which triggers once after a while to notify a timeout.
 * This timer can be re-triggered before it elapses and it can be reused after having
 * elapsed.
 *   @return
 * The timer handle is returned; this handle is used to identify a timer (if several timers
 * should share the same callback function) or to perform other operations on this timer.\n
 *   If no timer can be created due to a lack of memory then #EDE_INVALID_TIMER_HANDLE is
 * returned instead. Due to the static, deterministic error allocation concept this error
 * should preferrably be handled by a simple assertion only; if this assertion doesn't fire
 * in the DEBUG compilation then there won't be an error in the production code neither.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param tiFromNow
 * The timer will invoke the specified callback \a tiFromNow time units later.\n
 *   The unit is the same as that of argument \a tiTick in the call of
 * ede_createDispatcher().\n
 *   The value needs to be positive. If it is less than the tick time of the dispatcher
 * than it is rounded upwards to this tick time and the timer fires in the next tick of the
 * dispatcher.\n
 *   For single-shot timers with \a killAtDueTime == \a false the value 0 is permitted,
 * too; is means to create the timer in suspended state. Doing so can give better control
 * of memory allocation; all ever required timers can be created in the initialization
 * callback for later use at runtime and dynamic object creation at runtime is entirely
 * avoided.
 *   @param callback
 * Please refer to \a tiFromNow.
 *   @param refUserContextData
 * The user specified context information, which is stored with the timer and which will be
 * brought back into its callback at due time. In the timer's callback, use \a
 * ede_getEventData() to retrieve the value passed in here. The data type of the user
 * specified context data is \a uintptr_t; if you pass in a pointer to some data then
 * ede_getEventData() will only return the pointer - not the data it points to.\n
 *   This argument is available only if #EDE_ENABLE_TIMER_CONTEXT_DATA is set to 1.
 *   @param killAtDueTime
 * Single shot timers can be killed at due time (and after callback processing) or they can
 * stay alive in suspended state for later reprogramming of a new single-shot time.
 *   @remark
 * This method and ede_createPeriodicTimer() are the only pieces of code in the CAN
 * interface implementation, which potentially suffer from race conditions with other
 * threads, that concurrenly run another dispatcher object. These race conditions are
 * easily to avoid, see ede_createPeriodicTimer() for details.
 *   @see ede_retriggerSingleShotTimer
 */
ede_handleTimer_t ede_createSingleShotTimer( const ede_callbackContext_t * const pContext
                                           , signed int tiFromNow
                                           , ede_callback_t callback
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                           , uintptr_t refUserContextData
#endif
                                           , bool killAtDueTime
                                           )
{
    return createTimer( pContext
                      , /* isPeriodic */ false
                      , tiFromNow
                      , callback
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                      , refUserContextData
#endif
                      , killAtDueTime
                      );
} /* End of ede_createSingleShotTimer */





/**
 * A timer is killed. No later callbacks will appear for periodic and single shot timers
 * and nor will it be possible to reset the due time of a killed timer. Killing of a timer
 * can be done at any reasonable time. Exceptions are: The operation must neither be
 * applied twice or more often to the same timer and nor after leaving the callback of a
 * single-shot timer with auto kill property.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param hTimer
 * The handle of the killed timer as got from the timer create function. The handle becomes
 * invalid with return from this function!\n
 *   The handle may be \a NULL if the function is used from the on-elapse callback of a
 * timer. In which case the operation affects this timer. This operation is permitted but
 * useless for a single-shot timer with auto-kill property.
 *   @see ede_createSingleShotTimer
 */
void ede_killTimer( const ede_callbackContext_t * const pContext
                  , ede_handleTimer_t hTimer
                  )
{
    /* The timer object is scheduled for deletion. */
    getTimerObject(pContext, hTimer)->tiReload = TIMER_STATE_KILLED;

} /* End of ede_killTimer */


/**
 * Stop a running timer. The difference to kill is that the timer object is not marked for
 * reuse (which is the substitute for object destroying in our static, deterministic memory
 * allocation concept). The handle stays valid and the timer can later be reused by
 * reprogramming its due time with ede_retriggerSingleShotTimer().\n
 *   The concept of suspending and later reusing timers only holds for single shot timers
 * without the auto-kill property set. Calling this function for an auto-kill single shot
 * timer is still permitted but the operation is effectively a kill. These timers can't be
 * reprogrammed after suspend. Calling this function for a periodic timer is forbidden; this
 * is caught by assertion.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param hTimer
 * The handle of the suspended timer as got from the timer create function. It needs to be a
 * single-shot timer. Otherwise an assertion fires.\n
 *   The handle may be \a NULL if the function is used from the on-elapse callback of a
 * single-shot timer. In which case the operation affects this timer.\n
 *   If the function is called from the on-elapse callback of a single-shot timer with
 * auto-kill property set then the operation is without effect since the timer would be
 * killed anyway.
 */
void ede_suspendSingleShotTimer( const ede_callbackContext_t * const pContext
                               , ede_handleTimer_t hTimer
                               )
{
    /* Find the timer object if not explicitly passed in. */
    hTimer = getTimerObject(pContext, hTimer);

    /* So far there's no concept of suspending and reusing periodic timers or single-shot
       timers with auto-kill (and this would mean a redesign of the complete timer model).
       For periodic timers the operation is forbidden (assertion) and for auto-kill timers
       it's interpreted like a kill. It's a bit unclear what to do with the suspend of a
       suspended timer: We interpret it as a no operation, but an assertion would be a
       valid option, too. */
    if(hTimer->tiReload == TIMER_STATE_SINGLE_SHOT)
        hTimer->tiReload = TIMER_STATE_SINGLE_SHOT_SUSPENDED;
    else if(hTimer->tiReload == TIMER_STATE_SINGLE_SHOT_AUTO_KILL)
        hTimer->tiReload = TIMER_STATE_KILLED;
    else
        EDE_ASSERT(hTimer->tiReload == TIMER_STATE_SINGLE_SHOT_SUSPENDED);

} /* End of ede_suspendSingleShotTimer */




/**
 * A single shot timer can be reprogrammed during elapsing or - but only if it doesn't have
 * the auto-kill property set - even after firing or explicit suspend command. Use this
 * function to redefine the due time.\n
 *   For running single shot timers with or without auto-kill property this operation means
 * to postpone the timer event by a new time span counting from now.\n
 *   For suspended timers it means the reactivation of an inactive timer object.
 * Reactivation after suspend is functionally identical to killing a timer (explicit or by
 * auto-kill) and creating a new one. The only difference is the different memory
 * management impact, kill and create can mean to allocate a new object on the heap,
 * whereas suspend/resume guarantees not to do any heap operation.\n
 *   Please note: Single shot timers with auto-kill can't have a suspended state. They are
 * either running or killed, i.e. no longer existant and not accessible.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param hTimer
 * The handle of the reprogrammed timer as got from the create function. It needs to be a
 * single-shot timer. Otherwise an assertion fires.\n
 *   The handle may be \a NULL if the function is used from the on-elapse callback of a
 * single-shot timer. In which case the operation affects this timer.\n
 *   If the function is called from the on-elapse callback of a single-shot timer with
 * auto-kill property set then the operation is without effect: These timers won't fire
 * again but are definitly killed after firing their event.
 *   @param tiNewFromNow
 * The new due time is defined to be \a tiNewFromNow time units in the future.
 *   The unit is the same as that of argument \a tiTick in the call of
 * ede_createDispatcher().\n
 *   The value needs to be positive. If it is less than the tick time of the dispatcher than
 * it is rounded upwards to this tick time and the timer fires in the next tick of the
 * dispatcher.
 */
void ede_retriggerSingleShotTimer( const ede_callbackContext_t * const pContext
                                 , ede_handleTimer_t hTimer
                                 , signed int tiNewFromNow
                                 )
{
    ede_eventDispatcher_t * const pDisp = pContext->pDispatcher;

    /* Find the timer object if not explicitly passed in. */
    hTimer = getTimerObject(pContext, hTimer);

    /* If this assertion fires then it either because of an invalid time designation or
       because the method has been called for a periodic timer, which must not be
       retriggrered. */
    EDE_ASSERT(tiNewFromNow > 0  &&  hTimer != NULL
               && (hTimer->tiReload == TIMER_STATE_SINGLE_SHOT
                   ||  hTimer->tiReload == TIMER_STATE_SINGLE_SHOT_AUTO_KILL
                   ||  hTimer->tiReload == TIMER_STATE_SINGLE_SHOT_SUSPENDED
                  )
              );

    hTimer->tiDue = pDisp->tiNow + tiNewFromNow;

    /* Reactivate a single shot timer without auto kill, which had elapsed meanwhile. */
    if(hTimer->tiReload == TIMER_STATE_SINGLE_SHOT_SUSPENDED)
        hTimer->tiReload = TIMER_STATE_SINGLE_SHOT;

} /* End of ede_retriggerSingleShotTimer */



/**
 * All events related to a registered event source or a timer are reported through
 * the registered callback. In general this callback can have a switch/case to handle
 * different kinds of events. Sometime it might be better to (temporarily) redefine the
 * callback function to handle anticipated, specific events. From within a callback the
 * client code may use this function to re-register the callback function for all future
 * events from the same source.
 *   @return
 * The callback function registered so far is returned.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param newCallback
 * The new callback function.
 *   @remark
 * This function may be called from only from timer callbacks or from callbacks of external
 * events. (But never from the initialization callback of an internal event, where it is
 * anway useless as there won't ever be another callback.)\n
 *   For external events, received via the dispatcher queue, it relates to the callback of
 * the the event causing registered event source. For timer events it relates to the timer
 * object, i.e., to future #EDE_EV_TIMER_ELAPSED events of the same timer object.
 */
ede_callback_t ede_installCallback( const ede_callbackContext_t * const pContext
                                  , ede_callback_t newCallback
                                  )
{
    EDE_ASSERT(pContext->kindOfEvent != EDE_EV_EVENT_SOURCE_INT_INIT);
    ede_callback_t *pCallback;
    if(pContext->pTimer != NULL)
    {
        /* This is a timer callback and the timer's callback function will be exchanged. */
        EDE_ASSERT(pContext->kindOfEvent == EDE_EV_TIMER_ELAPSED);
        pCallback = &pContext->pTimer->callback;
    }
    else
    {
        /* This is a received external event and the event source's callback function will
           be exchanged. (The operation is not defined for internal event sources.) */
        EDE_ASSERT(pContext->kindOfEvent != EDE_EV_TIMER_ELAPSED
                   &&  isExtEventSrc(pContext->pDispatcher->pSystem, pContext->pEventSrc)
                  );
        pCallback = &pContext->pEventSrc.ext->callback;
    }

    ede_callback_t const oldCallback = *pCallback;
    *pCallback = newCallback;
    return oldCallback;

} /* End of ede_installCallback */



/**
 * Get the index of the event source, which has posted the event. The index is the same,
 * which had been returned by the registration of that event source (see
 * ede_registerExternalEventSource()). If this method is called from a timer callback then the
 * operation relates to the parent event source of the timer.
 *   @return
 * Get the zero based, linear event source index.\n
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param pIsExternalEventSrc
 * Registered event sources has separate index spaces for internal and external sources. It
 * is returned by reference, whether the returned index relates to an external source (\a
 * true) or an internal one (\a false).
 */
unsigned int ede_getIdxEventSource( const ede_callbackContext_t * const pContext
                                  , bool * const pIsExternalEventSrc
                                  )
{
    const ede_dispatcherSystem_t * const pSystem = pContext->pDispatcher->pSystem;
    const ptrToEvtSrc_t pEventSrc = pContext->pEventSrc;
    unsigned int idxEvSrc;
    if(isExtEventSrc(pSystem, pEventSrc))
    {
        *pIsExternalEventSrc = true;
        idxEvSrc = (unsigned int)(pEventSrc.ext - &pSystem->eventSrcExtAry[0]);
        EDE_ASSERT(idxEvSrc < pSystem->noEventSrcsExt);
    }
    else
    {
        *pIsExternalEventSrc = false;
        idxEvSrc = (unsigned int)(pEventSrc.base - &pSystem->eventSrcIntAry[0]);
        EDE_ASSERT(idxEvSrc < pSystem->noEventSrcsInt);
    }
    
    return idxEvSrc;

} /* End of ede_getIdxEventSource */




/**
 * Get the index of the external event source, which has posted the event, which had raised
 * the callback, which invokes this method. The index is the same, which had been returned
 * by the registration of that external event source (see
 * ede_registerExternalEventSource()). If this method is called from a timer callback then
 * the operation relates to the parent external event source of the timer.
 *   @return
 * Get the zero based, linear index of the external event source.\n
 *   The method must be used only from callbacks caused by an external event source.
 * Function result and behavior are undefined if it is invoked from a callback initiated by
 * an external event source. This is caught by assertion only.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * Registered event sources have separate index spaces for internal and external sources.
 * Never call this method from a callback initiated by an internal event source! (This
 * includes callback from timers, which had been created in earlier callbacks from internal
 * sources.) Use ede_getIdxEventSource() in case of doubts.
 */
unsigned int ede_getIdxExternalEventSource(const ede_callbackContext_t * const pContext)
{
    const ede_dispatcherSystem_t * const pSystem = pContext->pDispatcher->pSystem;
    const ptrToEvtSrc_t pEventSrc = pContext->pEventSrc;

    const unsigned int idxEvSrc = (unsigned int)(pEventSrc.ext - &pSystem->eventSrcExtAry[0]);
    
    /* The in-bounds assertion also catches calling this method from the callback of an
       internal event source. */
    EDE_ASSERT(idxEvSrc < pSystem->noEventSrcsExt);

    return idxEvSrc;

} /* End of ede_getIdxExternalEventSource */




/**
 * Get the index of the internal event source, which has posted the event, which had raised
 * the callback, which invokes this method. The index is the same, which had been returned
 * by the registration of that internal event source (see
 * ede_registerInternalEventSource()). If this method is called from a timer callback then
 * the operation relates to the parent internal event source of the timer.
 *   @return
 * Get the zero based, linear index of the internal event source.\n
 *   The method must be used only from callbacks caused by an internal event source.
 * Function result and behavior are undefined if it is invoked from a callback initiated by
 * an external event source. This is caught by assertion only.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * Registered event sources have separate index spaces for internal and external sources.
 * Never call this method from a callback initiated by an external event source! (This
 * includes callback from timers, which had been created in earlier callbacks from external
 * sources.) Use ede_getIdxEventSource() in case of doubts.
 */
unsigned int ede_getIdxInternalEventSource(const ede_callbackContext_t * const pContext)
{
    const ede_dispatcherSystem_t * const pSystem = pContext->pDispatcher->pSystem;
    const ptrToEvtSrc_t pEventSrc = pContext->pEventSrc;

    const unsigned int idxEvSrc = (unsigned int)(pEventSrc.base - &pSystem->eventSrcIntAry[0]);
    
    /* The in-bounds assertion also catches calling this method from the callback of an
       external event source. */
    EDE_ASSERT(idxEvSrc < pSystem->noEventSrcsInt);

    return idxEvSrc;

} /* End of ede_getIdxInternalEventSource */




/**
 * Event sources are registered with a reference to some data object, which characterizes
 * the event source. Accessing this data may be useful for processing the received event.\n
 *   Note, reference and referenced data object are meaningless to the dispatcher engine.
 * See ede_registerExternalEventSource().
 *   @return
 * Get the data reference, which had been registered with the causing custom event source;
 * see argument \a refEventSourceData of ede_registerExternalEventSource(). The reference
 * can be an index or a pointer.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * The other API ede_getIdxEventSource(), which identifies the causing event source
 * by index, is an alternative to using the event source's referenced data object.
 */
uintptr_t ede_getEventSourceData(const ede_callbackContext_t * const pContext)
{
    const eventSrc_t * const pEventSrc = getEventSourceFromContext(pContext);
    return pEventSrc->refEventSrcData;

} /* End of ede_getEventSourceData */



/**
 * Get the index of the port, which had received the event that caused the callback. This
 * method is useless when called from a timer callback.
 *   @return
 * The zero based index of the receiving dispatcher port or UINT_MAX for a timer callback.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
ede_kindOfEvent_t ede_getIdxPort(const ede_callbackContext_t * const pContext)
{
    return pContext->idxPort;

} /* End of ede_getIdxPort */




/**
 * Get the handle of the timer causing the callback, which this method is called from. The
 * method can be useful to identify the due timer if several timer objects share the same
 * callback.
 *   @return
 * The handle of the timer object as initially got from either ede_createPeriodicTimer() or
 * ede_createSingleShotTimer().\n
 *   The function returns NULL if not called from a timer elapsed callback. However, this
 * situation is considered a fault in the (external) code and reported by assertion in
 * DEBUG compilation.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
ede_handleTimer_t ede_getHandleTimer(const ede_callbackContext_t * const pContext)
{
    EDE_ASSERT(pContext->kindOfEvent == EDE_EV_TIMER_ELAPSED  ||  pContext->pTimer == NULL);
    return pContext->pTimer;

} /* End of ede_getHandleTimer */



/**
 * Get the "kind of event", i.e., the reason for invokation of the callback, this method is
 * called from.
 *   @return
 * The reason for invokation or the causing event.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
ede_kindOfEvent_t ede_getKindOfEvent(const ede_callbackContext_t * const pContext)
{
    return pContext->kindOfEvent;

} /* End of ede_getKindOfEvent */




/**
 * Get the data contents of an event from within a callback.\n
 *   For use case CAN communication, this normally relates to the content bytes of a
 * received message but it may have any other meaning, which is aggreed on between data
 * producer and consumer and which are both defined in the integration code.\n
 *   For timer events and if user specified timer context data is supported (see
 * #EDE_ENABLE_TIMER_CONTEXT_DATA) then the data contents of the event is the user
 * specified context data. This method will return the value, which had been specified as
 * parameter \a refUserContextData in the timer creation methods, either
 * ede_createPeriodicTimer() or ede_createSingleShotTimer(). Note, for timer callbacks,
 * it'll normally be more to the point to use the alternative method
 * ede_getTimerContextData().
 *   @return
 * Get the pointer to the content data of the event. The calling client code has read-only
 * access to the data and the data the returned pointer points to is valid only during the
 * execution of the callback, which this method is called from. The data needs to be copied
 * by the callback code if this doesn't suffice.\n
 *   The data has the alignment of a pointer to \a void or an (\a unsigned) \a int,
 * whatever is the stronger constraint. If you e.g. know that it actually is an \a int then
 * you may on most platforms cast the returned pointer to an \a int pointer and read the
 * integer as a whole. (As opposed to reading all the integer's bytes as \a uint8_t and
 * composing the number from these.)
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param pSizeOfEvData
 * The number of bytes the returned pointer points to.
 *   @remark
 * Event data is not defined for timer events if the code is not compiled with support of
 * user specified timer context data. The function will return NULL and set * \a
 * pSizeOfEvData to zero in this case. See #EDE_ENABLE_TIMER_CONTEXT_DATA for more.
 *   @remark
 * The alignment of the pointer is not ensured by the implementation of the dispatcher. At
 * least for external events, the dispatcher just passes through the data pointer from the
 * connection element, which is connected to the dispatcher's input port. Nevertheless, the
 * alignment promise is still kept, though by requirement only; any implementation of a
 * connection element must regard this alignment constraint.
 */
const void *ede_getEventData( const ede_callbackContext_t * const pContext
                            , unsigned int *pSizeOfEvData
                            )
{
    *pSizeOfEvData = pContext->sizeOfData;
    EDE_ASSERT(((uintptr_t)pContext->pData & (EDE_COMMON_MACHINE_ALIGNMENT-1u)) == 0u);
    return pContext->pData;

} /* End of ede_getEventData */



#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
/**
 * Get the user provided context data of a timer from within its timer-elapsed callback.\n
 *   The method must not be called from callbacks of an external event. This is checked by
 * assertion.\n
 *   The timer context data is transported as event data. Therefore, this function is just
 * an alternative to using ede_getEventData(). It's just a bit more convenient in use as
 * no pointer dereferencing is involved for the caller.
 *   @return
 * The method returns the value, which had been specified as parameter \a
 * refUserContextData in the timer creation methods, either ede_createPeriodicTimer() or
 * ede_createSingleShotTimer().
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
uintptr_t ede_getTimerContextData(const ede_callbackContext_t * const pContext)
{
    EDE_ASSERT(pContext->pTimer != NULL  &&  pContext->sizeOfData == sizeof(uintptr_t)
               &&  ((uintptr_t)pContext->pData & (sizeof(uintptr_t)-1u)) == 0u
              );
    return *(const uintptr_t*)pContext->pData;

} /* End of ede_getTimerContextData */
#endif
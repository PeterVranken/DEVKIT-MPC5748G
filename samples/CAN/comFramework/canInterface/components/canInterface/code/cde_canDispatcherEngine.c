/**
 * @file cde_canDispatcherEngine.c
 * The dispatcher engine for CAN frames. This engine serves the CAN API implemented by the
 * package.\n
 *   The input of the engine is connected to the native API of the underlying system.
 * Specific target platform integration is required. Normally, there will be an interrupt
 * or interrupt triggered callback, which notifies CAN related events. Frame reception in
 * the first place, but there may be more events like send acknowledge or error events.\n
 *   The output of the engine is connected to the CAN API. For example if a CAN reception
 * event is received than the received frame contents can be decoded and written into that
 * API. This process is called dispatching because the API usually has a parallel design,
 * with a distinct, dedicated connection point (by global data or functional) for each
 * frame ID.\n
 *   Both ends of the engine can be used from different CPU contexts, a thread-safe queue
 * safely decouples both ends.
 *
 * Copyright (C) 2015-2017 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   cde_initModule
 *   cde_installMapOsHandleFrameToCdeIndex
 *   cde_createDispatcher
 *   cde_registerBus
 *   cde_registerFrame
 *   cde_postBusEvent
 *   cde_postFrameEvent
 *   cde_getNoDispatcherQueueFullEvents
 *   cde_dispatcherMain
 *   cde_getNoQueueFullEvents
 *   cde_createPeriodicTimer
 *   cde_createSingleShotTimer
 *   cde_killTimer
 *   cde_suspendSingleShotTimer
 *   cde_retriggerSingleShotTimer
 *   cde_installCallback
 *   cde_getCanId
 *   cde_getIdxFrame
 *   cde_getIdxBus
 *   cde_getOsHandleFrame
 *   cde_getHandleTimer
 *   cde_isInboundTransmission
 *   cde_getKindOfEvent
 *   cde_getEventData
 * Local functions
 *   createTimer
 *   invokeCallback
 *   getBusFromContext
 *   getFrameFromContext
 *   getNoQueueFullEvents
 *   postEvent
 */


/*
 * Include files
 */

#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "mem_malloc.h"
#include "tsq_threadSafeQueue.h"
#include "cde_canDispatcherEngine.h"

#ifdef _STDC_VERSION_C11
# include <stdatomic.h>
#endif


/*
 * Defines
 */

/* Some specific numeric values for the timer reload property, which have a special meaning
   other than the normal time designation. */
#define TIMER_STATE_SINGLE_SHOT             (0)
#define TIMER_STATE_SINGLE_SHOT_AUTO_KILL   (-1)
#define TIMER_STATE_SINGLE_SHOT_SUSPENDED   (-2)
#define TIMER_STATE_KILLED                  (-3)


/*
 * Local type definitions
 */

/* Forward references for recursive data type definition. See below for actual types. */
struct frame_t;
struct bus_t;
struct cde_timer_t;
struct dispatcher_t;


/** The reference to a frame, bus or timer object. Used as parent of timers or as source of
    events. */
typedef struct objRef_t
{
    /** The kind of the object: Is it a frame, bus or timer object? */
    enum { objTypeFrame, objTypeBus, objTypeTimer } type;

    /** The handle to the object. Maybe a pointer or an index. */
    union
    {
        /** The pointer to a frame object if \a type == \a objTypeFrame. */
        struct frame_t *pFrame;

        /** The pointer to a bus object if \a type == \a objTypeBus. */
        struct bus_t *pBus;

        /** The pointer to a timer object if \a type == \a objTypeTimer. */
        struct cde_timer_t *pTimer;

    } objRef;

} objRef_t;


/** The internal representation of a registered bus. */
typedef struct bus_t
{
    /** The currently registered callback for external events. */
    cde_callback_t callback;

    /** The reference to the dispatcher the bus' events are processed in. */
    struct dispatcher_t *pDispatcher;

} bus_t;



/** The internal representation of a registered frame. */
typedef struct frame_t
{
    /** The CAN ID. */
    unsigned long canId;

#if CDE_ENABLE_API_GET_INDEX_BUS == 1
    /** The handle of the bus, implemented as linear zero based index. */
    unsigned int idxBus;
#endif

#if CDE_ENABLE_API_GET_OS_HANDLE_FRAME == 1
    /** The OS handle of the frame. */
    cde_osHandleFrame_t osHandleFrame;
#endif

    /** The currently registered callback for external events. */
    cde_callback_t callback;

#if CDE_ENABLE_API_IS_INBOUND_TRANSMISSION == 1
    /** The transmission direction. */
    boolean_t isInbound;
#endif

    /** The reference to the dispatcher the frame's events are processed in. */
    struct dispatcher_t *pDispatcher;

} frame_t;



/** A timer object.
      @remark The type designation "struct cde_timer_t" of this class is publically visible
    although the class as such is local to this module. */
typedef struct cde_timer_t
{
    /** A timer is owned by a parent. Having this reference to its parent enables the
        timer's callback function to query not only the timer's own properties but also
        those of its parent. Mostly, the parent is a frame object. */
    objRef_t parentRef;

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
    cde_callback_t callback;

#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
    /** The timer can have some user provided data, which it brings back into the callback,
        when it becomes due. This data can be useful to convey some information from the
        callback creating the timer object to the on-elapsed callback of the timer itself.
        Or if several timer objects share the same callback. */
    void *pUserContextData;
#endif

    /** The timers are organized in linked lists. Here we have the reference to the next
        timer in the list or NULL at the end of the list.
          @remark So far, the kill operation is barely used. So far this is the only
        operation, which would significantly benefit from a doubly linked list. Now it is
        of complexity O(n), where n is the number of objects but using a DLL we would
        achieve O(1) for a single kill operation. Change implementation once kill becomes
        essential in typical use cases. */
    struct cde_timer_t *pNext;

} timer_t;



/* Forward reference for recursive data type definition. See below for actual type. */
typedef struct dispatcher_t dispatcher_t;


/* TODO Does it make sense to have \a pDispatcher in the event? For bus and frame
   source we can have a cheap method \a getDispatcher; for timer it would be more
   expensive. Unfortunately, it is mainly used for timer related callbacks. It could be an
   idea, too, to have a compile switch in the sense of optimize for speed or for RAM
   size. */

/** An event for the client code, i.e. the callback into the client code. For external
    events this is an element of the dispatcher's queue at the same time. */
typedef struct event_t
{
    /** The kind of event. This value is set by the producer of the data element.\n In case
        of external events this is the integration code. Now the value is out of scope of
        the dispatcher engine. The integration code will decide, which kinds of event
        exist. It should however use the values of the enumeration \ref cde_kindOfEvent_t
        as far as applicable and it must not redefine the already used values. */
    unsigned int kind;

    /** A reference to the object (frame, bus or timer) this event is related to. It is set
        by the producer of the data element. */
    objRef_t source;

    /** A reference to the dispatcher, which delivered this event to the addressed
        callback. */
    dispatcher_t *pDispatcher;

    /** The number of actual data bytes in \a dataAry. */
    unsigned int sizeOfData;

    /** The data contents of the event. This is a flexible array member. Although it
        formally holds values of type void* is it effectively a memory chunk of fixed,
        user-specified length, that can vary between 0 and any number of bytes. (The actual
        length is specified at dispatcher creation time.)\n
          The alignment of the memory chunk is the alignment of a (void) pointer. This
        should be fine on all existing platforms to avoid misalignments of event data. Even
        a double or long long will normally be alright; these data types would likely cause
        problems only on a system with 32 Bit address bus and 64 data bus width, which can
        be considered a rather extraordinary architecture.\n
          For C11 targets the alignment is as explicitly configured by setting
        #CDE_COMMON_MACHINE_ALIGNMENT.\n
          The flexible array member must not be touched if the user specified a length of
        zero. */
#if defined(_STDC_VERSION_C11)
    _Alignas(CDE_COMMON_MACHINE_ALIGNMENT) void *dataAry[];
#elif defined(_STDC_VERSION_C99)
    void *dataAry[];
#elif defined(__GNUC__)
    void *dataAry[0];
#else
# error Flexible array members are not supported by your compiler
#endif

} event_t;


/** The single dispatcher. */
struct dispatcher_t
{
    /** The queue of external events. This will usually be reception events, error events
        or transmission acknowledge events. */
    tsq_queue_t *pEventQueue;

    /** Counter of attempts to write to a full queue.\n
          This member is updated by the event source (mostly a CAN interrupt) and read-only
        to the data consumer (APSW). It is essential that this member can be read or
        written in a single atomic operation; this explains the type, which has to be
        configured platform dependent.\n
          In case of C11 compilation this is a true _Atomic entity. Read-modify-write
       operations are possible from producer and consumer context and the race conditions
       documented for the APIs cde_getNoQueueFullEvents() and
       cde_getNoDispatcherQueueFullEvents() disappear. */
#ifdef _STDC_VERSION_C11
    _Atomic
#endif
    volatile cde_atomicUnsignedInt_t noErrorsQueueOverrun;

#ifndef _STDC_VERSION_C11
    /** Flag to indicate to the data producer that the counter of overrun errors should be
        reset during the next write operation.\n
          This member is write-only to the data consumer (APSW). The data producer will
        read and modify it. It's assumed that writing to a Boolean is atomic on all
        existing platforms. The use of this flag in relathionship with the other member \a
        noErrorsQueueOverrun is not race condition free. Please see method
        cde_getNoQueueFullEvents() for more information.
          @remark This member is not apparent in C11 compilation. */
    boolean_t doResetCntErrorQueueOverrun;
#endif

    /* Pointer to the list of timers or to the first timer object in the list. NULL if and
       only if the list is empty. */
    timer_t *listOfTimerObjects;

    /* Pointer to a list of newly created timers, which have to be appended to the list of
       normally scheduled timers as sson as possible. NULL if and only if the list is
       empty. */
    timer_t *listOfNewTimerObjects;

    /* Pointer to the end of the list of new timers, meaning to the last new timer object
       in the list. NULL if and only if the list is empty. */
    timer_t *pLastNewTimerObject;

    /** Memory reuse despite of a one-way heap: Killed timer objects are collected in a
        free list for reuse. NULL if and only if the list is empty. */
    timer_t *freeListOfTimerObjects;

    /** The processing of the queue needs to be done on a regular time base using function
        \a cde_dispatcherMain. The time distance between two calls of the clock function
        cde_dispatcherMain() is held in \a tiTick.\n
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
};



/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** The dispatcher objects. */
static dispatcher_t *_dispatcherAry = NULL;

/** The number of dispatchers held in \ref _dispatcherAry. */
static unsigned int _noDispatchers = 0;

/** The internal list of registered buses. */
static bus_t *_busAry = NULL;

/** The length (and maximum length at the same time) of the bus list \ref _busAry. */
static unsigned int _noBuses = 0;

/** The internal list of registered frames. */
static frame_t *_frameAry = NULL;

/** The maximum length of the frame list \ref _frameAry. */
static unsigned int _maxNoFrames = 0;

/** The length of the frame list \ref _frameAry. */
static unsigned int _noFrames = 0;

/** The (externally implemented) map, which associates bus index and OS frame handle with
    the internally used frame index. */
static cde_mapOsHandleFrameToCdeIndex_t _mapOsHandleFrameToCdeIndex =
{
    /** Add an association to the map. Or NULL if the default mapping should be applied. */
    .fctMakeMapEntryOsHandleFrameToCdeIndex = NULL,

    /** Query the map. Or NULL if the default mapping should be applied. */
    .fctMapOsHandleFrameToCdeIndex = NULL
};



/*
 * Function implementation
 */



/**
 * Create a timer object.
 *   @return
 * The timer handle is returned.\n
 *   If no timer can be created due to a lack of memory then #CDE_INVALID_TIMER_HANDLE is
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
 *   @param pUserContextData
 * The user specified context information, which is stored with the timer and which will be
 * brought back into its callback at due time.\n
 *   This argument is available only if #CDE_ENABLE_TIMER_CONTEXT_DATA is set to 1.
 *   @param killAtDueTime
 * Single shot timers can be killed at due time (and after callback processing) or they can
 * stay alive for later reprogramming of a new single-shot time.
 */

static cde_handleTimer_t createTimer( const cde_callbackContext_t *pContext
                                    , boolean_t isPeriodic
                                    , signed int ti
                                    , cde_callback_t callback
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                    , void *pUserContextData
#endif
                                    , boolean_t killAtDueTime
                                    )
{
    dispatcher_t * const pDisp = pContext->pDispatcher;

    /* A timer is allocated once and simply put into the linked list of all timers, the
       order in the list doesn't actually matter. However, since the timers are tested in
       list order and to get more natural behavior at run-time, we place new objects at the
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
        /* Allocate a new object on the (one-way) heap. Consider that at run-time we have
           race conditions between different dispatchers, which might (and typically do)
           run in different task contexts. */
        pTimer = mem_malloc(sizeof(timer_t), /* mutualExclusionOfClients */ true);
        if(pTimer == NULL)
            return CDE_INVALID_TIMER_HANDLE;
    }

    /* Determine the parent of the new timer. If the callback is frame or bus related then
       the frame or bus object is the parent. If the callback is a timer callback then we
       inherit the parent of this timer as parent for the new timer. */
    const objRef_t *pParentRef;
    if(pContext->source.type == objTypeTimer)
        pParentRef = &pContext->source.objRef.pTimer->parentRef;
    else
        pParentRef = &pContext->source;
    CDE_ASSERT((pParentRef->type == objTypeFrame  &&  pParentRef->objRef.pFrame != NULL)
               || (pParentRef->type == objTypeBus  &&  pParentRef->objRef.pBus != NULL)
              );

    /* Fill the new timer object. */
    pTimer->parentRef = *pParentRef;

    /* For single shot timers without auto-kill we permit the time 0 to express that the
       timer is created in suspended state. This gives better control on memory
       allocation. */
    CDE_ASSERT((!isPeriodic || !killAtDueTime)
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
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
    pTimer->pUserContextData = pUserContextData;
#endif
    pTimer->pNext = NULL;

    /* Add the timer to the end of newly created timers. This order is preferred in order
       to later see the same order in the callback invokation if two timers should have the
       same due time. */
    if(pDisp->listOfNewTimerObjects == NULL)
    {
        /* The list is still empty, this is the first object. */
        CDE_ASSERT(pDisp->pLastNewTimerObject == NULL);
        pDisp->listOfNewTimerObjects =
        pDisp->pLastNewTimerObject   = pTimer;
    }
    else
    {
        /* Add the new object to the end of the list. */
        CDE_ASSERT(pDisp->pLastNewTimerObject->pNext == NULL  &&  pTimer->pNext == NULL);
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
    /* The source of the event determines how to get the callback. */
    cde_callback_t callback;
    switch(pEvent->source.type)
    {
    case objTypeFrame:
        callback = pEvent->source.objRef.pFrame->callback;
        CDE_ASSERT(pEvent->pDispatcher == pEvent->source.objRef.pFrame->pDispatcher);
        break;
    case objTypeBus:
        callback = pEvent->source.objRef.pBus->callback;
        CDE_ASSERT(pEvent->pDispatcher == pEvent->source.objRef.pBus->pDispatcher);
        break;
    case objTypeTimer:
        callback = pEvent->source.objRef.pTimer->callback;
        break;
    default:
        callback = NULL;
        CDE_ASSERT(false);
    }

    /* Run the callback. */
    if(callback != NULL)
        callback(pEvent);

} /* End of invokeCallback */




/**
 * Helper function for the implementation of the API for the callbacks: The pointer to the
 * bus object is retrieved, which relates to the callback context. For bus related
 * callbacks this is the causing bus itself, for timer callbacks this is the parent
 * bus.
 *   @return
 * The pointer to the bus or NULL if called from a frame related ballback or a timer
 * callback of a timer, which has a frame as parent.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */

static inline bus_t *getBusFromContext(const cde_callbackContext_t *pContext)
{
    if(pContext->source.type == objTypeBus)
        return pContext->source.objRef.pBus;
    else if(pContext->source.type == objTypeTimer)
    {
        timer_t *pTimer = pContext->source.objRef.pTimer;
        if(pTimer->parentRef.type == objTypeBus)
            return pTimer->parentRef.objRef.pBus;
        else
            return NULL;
    }
    else
        return NULL;

} /* End of getBusFromContext */




/**
 * Helper function for the implementation of the API for the callbacks: The pointer to the
 * frame object is retrieved, which relates to the callback context. For frame related
 * callbacks this is the causing frame itself, for timer callbacks this is the parent
 * frame.
 *   @return
 * The pointer to the frame or NULL if called from a bus related ballback or a timer
 * callback of a timer, which has a bus as parent.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */

static inline frame_t *getFrameFromContext(const cde_callbackContext_t *pContext)
{
    if(pContext->source.type == objTypeFrame)
        return pContext->source.objRef.pFrame;
    else if(pContext->source.type == objTypeTimer)
    {
        timer_t *pTimer = pContext->source.objRef.pTimer;
        if(pTimer->parentRef.type == objTypeFrame)
            return pTimer->parentRef.objRef.pFrame;
        else
            return NULL;
    }
    else
        return NULL;

} /* End of getFrameFromContext */




/**
 * Get the number of recorded queue full events, i.e. the number of lost events due to an
 * overfull queue.\n
 *   This inline function implements the common parts of the two available API methods.
 *   @return
 * Get the number, which should normally be zero in case of a well designed queue size.
 *   @param pDisp
 * The dispatcher by reference, whose queue is meant.
 *   @param reset
 * If \a true then the event counter is reset to zero at the next occasion. Due to the fact
 * that the reset command is handled by the event producing task or interrupt no statement
 * can be made when the reset will actually appear. Due to race conditions it may even
 * slightly increment until the reset command is executed. In particular, the client code
 * must not assume that it can accurately compute the total number of queue full events by
 * regularly calling this method with parameter \a reset set to \a true and summing up the
 * function result values.\n
 *   If \a reset is not used and if the event counter reaches its limit then it'll be held
 * at this limit.\n
 *   In C11 compilation all delays and race conditions disappear and the function return
 * value is the real, accumulatable number of events since the previous call of this method
 * with \a reset == \a true.
 */

static inline cde_atomicUnsignedInt_t getNoQueueFullEvents( dispatcher_t * const pDisp
                                                          , boolean_t reset
                                                          )
{
#ifdef _STDC_VERSION_C11
    if(reset)
        return atomic_exchange(&pDisp->noErrorsQueueOverrun, /* desired */ 0);
    else
        return pDisp->noErrorsQueueOverrun;
#else
    const cde_atomicUnsignedInt_t noErrorsQueueOverrun = pDisp->noErrorsQueueOverrun;
    if(reset)
        pDisp->doResetCntErrorQueueOverrun = true;
    return noErrorsQueueOverrun;
#endif
} /* End of getNoQueueFullEvents */




/**
 * An event is posted to a dispatcher queue.\n
 *   The implementation is thread-safe with respect to an asynchronous call of
 * cde_dispatcherMain(), which processes the posted events in another CPU context. There are
 * no constraints to the preemption patter of the two involved contexts. This can be a
 * one-way preemption (an interrupt posts, a normal task dispatches) or a mutual preemption
 * (two ordinary threads in a general purpose operating system) or true parallelism as in a
 * multi-core environment with shared memory.\n
 *   The implementation is not reentrant. No two event sources must post an event at the
 * same time. Consequently, mutual exclusion must be implemented for all competing CPU
 * contexts posting events to the same dispatcher.
 *   @return
 * \a true, if function succeeded, else \a false. The dispatcher's queue has a maximum
 * length and the function will return false if it is full. In this case, the event is
 * entirely ignored (besides the reporting of the queue-full event).
 *   @param eventSrc
 * An event has its origin as property. This relates the event to a specific frame, bus or
 * timer.
 *   @param kind
 * The kind of event, which is passed to the client code, which reads the posted events
 * from the other end of the queue. It is an enumeration, which is meaningless to the
 * dispatcher engine or queue.
 *   @param pData
 * A pointer to some event data, which is meaningless to the dispatcher engine. Normally
 * used to convey CAN frame content bytes in case of a reception event, but can be anything
 * else. The data is copied into the queue and the pointer only needs to be valid during
 * the call of this method.\n
 *   May be NULL if \a sizeOfData is zero.
 *   @param sizeOfData
 * The number of data bytes. The elements of the dispatcher queue have a fixed limit for
 * the conveyed data. This limit must not be exceeded; this is checked by assertion and the
 * function will return false and further ignore the event in case.
 */

static boolean_t postEvent( dispatcher_t *pDisp
                          , objRef_t eventSrc
                          , unsigned int kind
                          , const void *pData
                          , unsigned int sizeOfData
                          )
{
    /* This assertion can fire if an unregistered bus object is used. */
    CDE_ASSERT(pDisp != NULL);

    tsq_queue_t * const pQueue = pDisp->pEventQueue;

#ifndef _STDC_VERSION_C11
    /* Prior to C11: Check for intermediate error reset demand. The data consumer can't
       reset the counter himself as this would require an unavailable atomic
       read-modify-write operation. */
    if(pDisp->doResetCntErrorQueueOverrun)
    {
        pDisp->doResetCntErrorQueueOverrun = false;
        pDisp->noErrorsQueueOverrun = 0;
    }
#endif

    /* Check data size. */
    if(tsq_getMaxSizeOfElement(pQueue) < sizeof(event_t) + sizeOfData)
    {
        CDE_ASSERT(false);
        return false;
    }

    /* Check if there's still room in the queue. */
    event_t * const pElem = tsq_allocTailElement(pQueue);
    if(pElem != NULL)
    {
        /* Enter the event by coying the data. */
        pElem->kind = kind;
        pElem->source = eventSrc;
        pElem->pDispatcher = pDisp;
        memcpy(&pElem->dataAry[0], pData, sizeOfData);
        pElem->sizeOfData = sizeOfData;
        
        /* Signal the new event to the receiver. pElem is invalid from now on. */
        tsq_postTailElement(pQueue);

        return true;
    }
    else
    {
        /* Queue is full this time. Count this error event but avoid counter overflow. */
#ifdef _STDC_VERSION_C11
        /* Note that atomic_compare_exchange_strong updates oldValue with the unexpected
           value if the operation fails. This means that we do not persist on writing our
           initially desired value but continue until we incremented the value - be it the
           initial one or from an concurrent write access (i.e. the reset operation in
           cde_getNoQueueFullEvents. */
        cde_atomicUnsignedInt_t oldValue = pDisp->noErrorsQueueOverrun;
        while(oldValue < (cde_atomicUnsignedInt_t)-1
              && !atomic_compare_exchange_strong( &pDisp->noErrorsQueueOverrun
                                                , /* pExpected */ &oldValue
                                                , /* desired */ oldValue+1
                                                )
             )
        {}
#else
        const unsigned int newVal = pDisp->noErrorsQueueOverrun+1;
        if(newVal > 0)
            pDisp->noErrorsQueueOverrun = newVal;
#endif
        return false;
    }
} /* End of postEvent */




/**
 * Initialize the module at application startup. The internal data structures are set up.\n
 *   This function must be called once and only once. Re-initialization is forbidden due to
 * the static, deterministic memory allocation concept.
 *   @return
 * \a true, if function succeeded, else \a false.\n
 *   The function will fail only in case of lack of memory. Since all memory allocation is
 * static and deterministic an appropriate and recommended failure handling concept is to
 * check the return value by assertion only. Anyhow, the system is not operational if this
 * function returns \a false.
 *   @param noBuses
 * The number of buses, which will be registered. In many integrations of the CAN
 * interface this will be zero: Buses need to be registered only if bus related events have
 * to be processed (e.g. bus off errors).\n
 *   Please note the difference to frames: For frames a maximum number is specified and any
 * actual number up to this maximum can be registered. For buses the actual number is
 * specified here and all of these buses need to be registered subsequently using
 * cde_registerBus().
 *   @param maxNoFrames
 * The maximum number of frames, which can be registered. The number of frames to be
 * registered is deterministic but depends on the network database files. The
 * recommendation is to pass a value, which is taken from the auto coded parts of the
 * interface code.
 *   @param noDispatchers
 * The intended number of dispatchers; minimum is one. How many dispatchers are used
 * depends on the concept of the APSW.
 *   @remark
 * Using this function is not an option but a must. You need to call it prior to any other
 * call of this module and prior to accessing any of its global data objects.
 *   @remark
 * The call of this function has to be done in a race condition free environment, prior to
 * entering the multi-tasking phase of the application. Most platform will offer an
 * initialization task for this purpose.
 */

boolean_t cde_initModule( unsigned int noBuses
                        , unsigned int maxNoFrames
                        , unsigned int noDispatchers
                        )
{
    unsigned int u;

    if(maxNoFrames == 0  ||  noDispatchers == 0)
    {
        CDE_ASSERT(false);
        return false;
    }

    /* Initialize the bus array. Re-initialization is forbidden due to the deterministic
       memory allocation concept. */
    if(_busAry != NULL)
    {
        CDE_ASSERT(false);
        return false;
    }
    _busAry = mem_malloc(sizeof(bus_t) * noBuses, /* mutualExclusionOfClients */ false);
    if(_busAry == NULL)
        return false;
    _noBuses = noBuses;
    for(u=0; u<_noBuses; ++u)
    {
        /* Validation of applied pointer arthmetics, which is undesired by paranoiacs. */
        CDE_ASSERT(&_busAry[u] - &_busAry[0] == (int)u);

        _busAry[u].callback = NULL;
        _busAry[u].pDispatcher = NULL;
    }

    /* Initialize the frame array. Re-initialization is forbidden due to the deterministic
       memory allocation concept. */
    if(_frameAry != NULL)
    {
        CDE_ASSERT(false);
        return false;
    }
    _frameAry = mem_malloc(sizeof(frame_t)*maxNoFrames, /* mutualExclusionOfClients */ false);
    if(_frameAry == NULL)
        return false;
    _maxNoFrames = maxNoFrames;
    _noFrames = 0;

    /* Initialize the dispatcher array. Re-initialization is forbidden due to the
       deterministic memory allocation concept. */
    if(_dispatcherAry != NULL)
    {
        CDE_ASSERT(false);
        return false;
    }
    _dispatcherAry = mem_malloc( sizeof(dispatcher_t) * noDispatchers
                               , /* mutualExclusionOfClients */ false
                               );
    if(_dispatcherAry == NULL)
        return false;
    _noDispatchers = noDispatchers;

    /* Initialize the dispatchers to become empty objects: They all have to be created
       explicitly by a later constructor call. */
    for(u=0; u<noDispatchers; ++u)
    {
        dispatcher_t * const pDisp = &_dispatcherAry[u];
        pDisp->pEventQueue = NULL;
        pDisp->noErrorsQueueOverrun = 0;
#ifndef _STDC_VERSION_C11
        pDisp->doResetCntErrorQueueOverrun = false;
#endif
        pDisp->listOfTimerObjects = NULL;
        pDisp->listOfNewTimerObjects = NULL;
        pDisp->pLastNewTimerObject = NULL;
        pDisp->freeListOfTimerObjects = NULL;
        pDisp->tiTick = 1;
        pDisp->tiNow = 0;
    }

    return true;

} /* End of cde_initModule */




/**
 * Set the reference to the required external, integrator provided map, which associates
 * the operating system's bus index and frame handle with the CAN interface engine's frame
 * index.
 *   @param mapOsHandleFrameToCdeIndex
 * The reference to the external map. Both entries of the struct may be NULL if no mapping
 * is required. See type defintion \ref cde_mapOsHandleFrameToCdeIndex_t for details.
 */

void cde_installMapOsHandleFrameToCdeIndex( cde_mapOsHandleFrameToCdeIndex_t
                                                                    mapOsHandleFrameToCdeIndex
                                          )
{
    CDE_ASSERT(mapOsHandleFrameToCdeIndex.fctMakeMapEntryOsHandleFrameToCdeIndex != NULL
               ||  mapOsHandleFrameToCdeIndex.fctMapOsHandleFrameToCdeIndex == NULL
              );
    _mapOsHandleFrameToCdeIndex = mapOsHandleFrameToCdeIndex;

} /* End of cde_installMapOsHandleFrameToCdeIndex */



/**
 * Create a dispatcher.\n
 *   The dispatcher delivers events to the client code, which is completely organized as
 * set of callbacks, which implement the reaction on the events. The root of all is the
 * initialization call, which is made for each registered bus or frame.\n
 *   Events can be external events (their meaning is fully determined by the integration
 * code) or internal timer events.\n
 *   A dispatcher is single-threaded. There are no race conditions between callbacks, which
 * makes the design of the event handling code easy and safe. If CAN events (reception
 * mostly) are logically connected to several application tasks (e.g. fast frames are
 * handled in a fast task, low frequent frames in a slower task) then one would create two
 * dispatchers; one delegates the fast frames race condition free to one task and the other
 * one the remainig frames also race condition free to the slower task.\n
 *   The decoupling of the platform dependent CAN interface (typically interrupt driven)
 * and the APSW (run in some regular periodic task context) is done with dispatcher queues,
 * which have a threadsafe implementation. There is a one by one relation between
 * dispatcher objects and their queues.\n
 *   The OS' CAN interrupts can pass arbitrary information through these queues to the
 * client code in the APSW. This can be CAN message contents and/or transmission status
 * information. Therefore the size of the data elements in the queue is configurable. Each
 * frame is associated with one particular dispatcher. The association is made during frame
 * registration.\n
 *   A typical use case would be a system with two queues. One has elements of 8 Byte and
 * is associated with all inbound frames - it conveys the received CAN information - and
 * the other one is associated with all outbound frames and has data elements of size 0. A
 * contentless event signaled through this queue would just mean an acknowledge of having
 * the frame sent.\n
 *   However, if the platform would provide status information together with the CAN
 * content bytes then the queue for inbound frames could decide to have e.g. 9 Byte
 * elements: 8 content bytes plus a status byte. All memory allocation in the CAN interface
 * is static and deterministic, which means for the queues that they allocate the maximum
 * element size times the number of elements regardless of the later actual use of the
 * queue.\n
 *   In general, the data elements are opaque to the dispatcher engine. Filling the
 * contents is done as part of the integration code and evaluating the data elements, too.
 * (The former in the implementation of the OS' CAN interrupt handlers and the latter by
 * appropriate configuration of the auto-coding of the callbacks.) The engine will just
 * ensure proper delivery of the data element in the right frame or bus context.
 *   @return
 * \a true, if function succeeded, else \a false.\n
 *   The function will fail only in case of lack of memory. Since all memory allocation is
 * static and deterministic an appropriate and recommended failure handling concept is to
 * check the return value by assertion only. If the assertion doesn't fire throughout the
 * development and test phase then it won't in the production code. Anyhow, the dispatcher
 * must never be used if this function returns \a false.
 *   @param idxDispatcher
 * The dispatcher object is identified by a linear, zero based index. The integration code
 * determines the number of dispatchers, thus the index range and it knows which queue to
 * be applied for which purpose, so it is aware of the meaning of the index. The
 * implementation doesn't make any difference between the dispatcher objects.
 *   @param maxQueueLength
 * The implemented algorithms superimpose a fixed maximum queue length, which has to be
 * specified at creation time. The maximum queue is greater or equal to one.\n
 *   The length will be chosen by the integrator as little as possible. The basic
 * consideration will be the worst case ratio of the rate of conveyed events and the
 * frequency, which the engine is ticked with. The selection of the appropriate queue
 * length in the development phase is supported by an overflow detection and reporting
 * mechanism.
 *   @param maxSizeOfDataElement
 * The maximum size of the content data of any later event in Byte.
 *   @param tiTick
 * The processing of the queue needs to be done on a regular time base using function \a
 * cde_dispatcherMain. The time distance between two calls of the clock function
 * cde_dispatcherMain() needs to be known for the timer operations and is passed in as \a
 * tiTick.\n
 *   The value needs to be a positive integer and should not be too large: No timing
 * operation shorter or faster than the value passed in here will become possible. This
 * relates to sending frames and checking timeouts of operations.\n
 *   The unit is arbitrary but the chosen unit defines the unit of all other timer
 * operations at the same time. Usually it'll be a Millisecond.
 *   @remark
 * The static, deterministic memory allocation concept inhibits re-creation of a
 * dispatcher. If one and the same dispatcher is created twice then the code fails by
 * assertion and returns \a false.
 *   @remark
 * The call of this function has to be done in a race condition free environment, prior to
 * entering the multi-tasking phase of the application. Most platforms will offer an
 * initialization task for this purpose.
 */

boolean_t cde_createDispatcher( unsigned int idxDispatcher
                              , unsigned int maxQueueLength
                              , unsigned int maxSizeOfDataElement
                              , signed int tiTick
                              )
{
    if(idxDispatcher >= _noDispatchers)
    {
        /* Invalid dispatcher index. */
        CDE_ASSERT(false);
        return false;
    }
    dispatcher_t * const pDisp = &_dispatcherAry[idxDispatcher];

    if(tiTick <= 0)
    {
        /* Invalid tick time. */
        CDE_ASSERT(false);
        return false;
    }
    pDisp->tiTick = tiTick;
    pDisp->tiNow = 0;

    if(pDisp->pEventQueue == NULL)
    {
        /* The event objects in the queue are defined using the "flexible array member" of
           C99. The size of such element needs to be figured out. */
        const unsigned int elementSize = sizeof(event_t) + maxSizeOfDataElement;

        /* The queue implementation makes use of untyped objects. Safe implementation
           requires information about the alignment of the stored elements. This is
           platform dependent. Some common cases are supported here but it can easily be
           that other target platforms/compilers need an extension of the definition. */
        #ifdef _STDC_VERSION_C11
        # define ALIGN_OF_EVENT_T _Alignof(event_t)
        #elif defined(__GNUC__) && defined(__WIN64__)
        # define ALIGN_OF_EVENT_T 8
        #elif defined(__GNUC__) && defined(__WIN32__)
        # define ALIGN_OF_EVENT_T 4
        #elif defined(__AVR__)
        # define ALIGN_OF_EVENT_T 1
        #else
        # error Define the alignment of struct event_t for your compiler/target
        #endif

        /* The queue implementation module doesn't do any memory allocation. We need to
           first reserve a chunk of required size and then let the constructor fill it. */
        const unsigned int sizeOfEvQueue = tsq_getSizeOfQueue
                                                ( maxQueueLength
                                                , /* maxElementSize */ elementSize
                                                , /* alignOfElement */ ALIGN_OF_EVENT_T
                                                );

        pDisp->pEventQueue = mem_malloc( sizeOfEvQueue
                                       , /* mutualExclusionOfClients */ false
                                       );
        if(pDisp->pEventQueue == NULL)
            return false;

        /* Create a new queue object. */
        tsq_createQueue( /* pMemoryChunk */ pDisp->pEventQueue
                       ,  maxQueueLength
                       , /* maxElementSize */ elementSize
                       , /* alignOfElement */ ALIGN_OF_EVENT_T
                       );
        #undef ALIGN_OF_EVENT_T
    }
    else
    {
        /* Forbidden re-creation of same dispatcher queue? */
        CDE_ASSERT(false);
        return false;
    }

    return true;

} /* End of cde_createDispatcher */




/**
 * Registration of a bus: A bus is associated with a dispatcher and an event callback. The
 * engine can be bound to some bus related notifications (e.g. bus-off interrupt) and the
 * dispatcher will delegate the event to the callback. The added value of doing so is the
 * change of CPU context. While the notification typically origins from an interrupt can
 * the event handling be safely done in the race condition free application task context.\n
 *   Bus registration is - different to frame registration - an option only and in many
 * integrations it won't be applied. However, all buses specified in the module
 * initialization cde_initModule() need to be registered using this function.
 *   @param idxBus
 * The zero based index of the bus. This index relates to the identification of buses, when
 * later notifing an event at run-time with cde_postBusEvent().
 *   @param idxDispatcher
 * The bus related events will be processed by one of the available dispatchers. All
 * dispatchers are functionally identical but the integration code can configure them
 * differently and assign them to different use case, most often to different application
 * task contexts. The appropriate dispatcher for the registered bus is passed in by index.
 * The index is the same as used in call cde_createDispatcher(), when the dispatchers
 * were created and configured.\n
 *   The dispatcher, which is associated with the bus needs to be configured and
 * initialized prior to this call of the bus registration. Please refer to
 * cde_createDispatcher().
 *   @param callback
 * The bus related callback. This callback is invoked the first time immediately after
 * registration of the bus (and still from within this method), which permits to do further
 * initialization there.
 *   @remark
 * The call of this function has to be done in a race condition free environment, prior to
 * entering the multi-tasking phase of the application. Most platform will offer an
 * initialization task for this purpose.
 */

void cde_registerBus( unsigned int idxBus
                    , unsigned int idxDispatcher
                    , cde_callback_t callback
                    )
{
    CDE_ASSERT(idxBus < _noBuses  &&  idxDispatcher < _noDispatchers);
    bus_t * const pBus = &_busAry[idxBus];

    /* A bus can't be registered more than once. Initially, the dispatcher reference had
       been invalidated and this is taken to recognize double registering. */
    CDE_ASSERT(pBus->pDispatcher == NULL);

    /* Save basic bus properties. */
    pBus->pDispatcher = &_dispatcherAry[idxDispatcher];
    pBus->callback = callback;

    /* Now invoke the registered callback, which has the meaning of an initialization
       callback this time. */
    event_t evInit = { .kind = CDE_EV_BUS_INIT
                     , .source = {.type = objTypeBus, .objRef = {.pBus = pBus}}
                     , .pDispatcher = pBus->pDispatcher
                     , .sizeOfData = 0
                     };
    invokeCallback(&evInit);

} /* End of cde_registerBus */




/**
 * A CAN frame is registered at the engine for processing. The client code will call this
 * function repeatedly in the initialization phase. Frame registration has the following
 * aspects:\n
 *   Primarily we need an association between the frame identifier as used by the platform
 * (operating system) when signaling the reception or transmission of a frame and the frame
 * index as used by the dispatcher engine. Most platforms have some kind of handle, which
 * is an argument to the reception or transmission callback. This handle can be a linear,
 * zero based index, a pointer or whatever. Normally this handle is returned from a
 * register function in the operating system or it is known from the (static) configuration
 * of the operating system. The dispatcher engine takes this handle as an anonymous 32 Bit
 * value and maintains a mapping onto its internal frame object. The implementation of the
 * mapping is an external function, which has to be provided by the integrator: The
 * implementation strongly depends on the characteristics of the operating system's handle.
 * It can be a null operation (if the handle is a zero based linear index), a simple lookup
 * table (if the handles span a small range of numbers) or a true hash map (if nothing is
 * known about the operating system handles). This registration function supports the
 * external build-up of the map by invoking a previously agreed external function, see
 * interface \ref cde_mapOsHandleFrameToCdeIndex_t and function
 * cde_installMapOsHandleFrameToCdeIndex() for details.\n
 *   Secondary, the appropriate dispatcher for the registered frame is selected. The
 * decision needs to be done prior to the frame registration by some external code, which
 * is provided by the integrator. This code will typically decide based on the period time
 * or permitted latency time of a frame or it'll select a specific dispatcher for specific
 * frames (e.g. grouping those which implement a self-contained protocol like XCP). In
 * simple systems there might be only a single dispatcher (and thus a single event queue)
 * and the decision is trivial. This function is informed about the dispatcher to apply by
 * means of an index.\n
 *   The last element of the registration process is the call of the frame's callback. This
 * callback is meant for initialization and will typically be used to do all further
 * initialization. The advantage is that this further initialization can then already been
 * done in the frame context; the receive callback can be installed, which has knowledge
 * about the specific contents of this frame, a timeout counter can be armed with respect
 * to the specific frame timing conditions, interface signal values can be initialized etc.
 * The implementation of the callback is typically auto-coded and based on the information
 * in the network database.
 *   @return
 * Internally, the engine organizes all registered frames in an array. The linear, zero
 * based index into this array is returned in case of success. Getting this index is
 * basically redundant information since the indexes will be returned in strictly
 * incremental order in each invocation of this method. Having the index may be useful if
 * the client code of the interface is structured as hand-written code (the callbacks),
 * which operates on auto-coded data tables. These tables are likely organized in arrays
 * using the identical index space in order to avoid mapping or hashing strategies.
 * Furthermore, the engine's index is not fully opaque as it appears in the mapping from
 * engine to operating system handles when posting a frame related event.\n
 *   #CDE_INVALID_FRAME_INDEX is returned in case of failures. Now the client code should
 * assume that later transmission of the frame is not possible. Registering can mainly fail
 * due to the static memory allocation. The preallocated memory can be exhausted.
 * Therefore, the return value should be validated by assertion and the configuration of
 * the heap would be updated if the assertion fires during the software test phase.
 *   @param canId
 * The frame's CAN ID.
 *   @param isInbound
 * The transmission direction as a Boolean.
 *   @param idxBus
 * The index of the bus the frame is transmitted on. On principle, buses are identified by
 * a linear, zero based index. \a idxBus needs to be less than the number of buses
 * specified at initialization time in cde_initModule().\n
 *   The bus index has relevance for the handle mapping only. The model is that - later at
 * run-time - the CAN notification from the operating system identifies the affected frame
 * by bus index and frame handle. Here, in the registration call, the pair of bus index and
 * frame handle is passed to the agreed mapping setup function but not used beyond this.
 * The value passed in for \a idxBus wouldn't care if the operating system's frame handle
 * is unambiguous across all buses.\n
 *   In particular, the bus index specified here doesn't necessarily need to correlate with
 * a bus registration using cde_registerBus. In many environments there won't be the need
 * for a bus registration at all (which enables dispatching events other than frame
 * related).
 *   @param osHandleFrame
 * The frame's handle as used (and issued) by the operating system. (The registration or
 * configuration of the frame at the system precedes this registration call.)
 *   @param idxDispatcher
 * The frame will be processed by one of the available dispatchers. All dispatchers are
 * functionally identical but the integration code can configure them differently and
 * assign them to different use case, most often to different application task contexts or
 * different event sources. The appropriate dispatcher for the registered frame is passed
 * in by index. The index is the same as used in call cde_createDispatcher(), when the
 * dispatchers were created and configured.\n
 *   The dispatcher, which is associated with the frame needs to be configured and
 * initialized prior to this call of the frame registration. Please refer to
 * cde_createDispatcher().
 *   @param callback
 * The frame related callback. This callback is invoked the first time immediately after
 * registration of the frame, which permits to do further initialization there; in
 * particular the function will consider to renew the callback registration with a more
 * appropriate, regularly called runtime callback.
 *   @remark
 * The call of this function must be preceded by the call of
 * cde_installMapOsHandleFrameToCdeIndex(); this function depends on the
 * external function specified in the former call.
 *   @remark
 * The call of this function has to be done in a race condition free environment, prior to
 * entering the multi-tasking phase of the application. Most platform will offer an
 * initialization task for this purpose.
 */

unsigned int cde_registerFrame( unsigned long canId
                              , boolean_t isInbound
                              , unsigned int idxBus
                              , cde_osHandleFrame_t osHandleFrame
                              , unsigned int idxDispatcher
                              , cde_callback_t callback
                              )
{
    if(idxDispatcher >= _noDispatchers)
    {
        CDE_ASSERT(false);
        return CDE_INVALID_FRAME_INDEX;
    }

    /* Find the new entry in the internal table of all registered frames. Nothing else to
       be done if the table is full. */
    if(_noFrames >= _maxNoFrames)
        return CDE_INVALID_FRAME_INDEX;
    unsigned int idxFrame = _noFrames++;
    frame_t * const pFrame = &_frameAry[idxFrame];

    /* Save basic frame properties. */
    pFrame->canId = canId;
#if CDE_ENABLE_API_IS_INBOUND_TRANSMISSION == 1
    pFrame->isInbound = isInbound;
#endif
#if CDE_ENABLE_API_GET_INDEX_BUS == 1
    pFrame->idxBus = idxBus;
#endif
#if CDE_ENABLE_API_GET_OS_HANDLE_FRAME == 1
    pFrame->osHandleFrame = osHandleFrame;
#endif
    pFrame->callback = callback;
    pFrame->pDispatcher = &_dispatcherAry[idxDispatcher];
    
    /* The dispatcher needs to be created before frame registration. */
    CDE_ASSERT(pFrame->pDispatcher->pEventQueue != NULL);

    /* Normally, the external, integrator provided code has a map, which associates the OS
       handle with the engine's frame index. This mapping is likely required at runtime by
       the CAN interrupts (usually one for reception, sometimes a second one for send
       acknowledge) to translate their information about affected frames back into the
       context of the dispatcher engine. The next call gives the external code the
       opportunity to add the next key value pair to its map.
         In simple environments the mapping might be not used, if the operating system uses
       the same zero based index as handle as the dispatcher engine does or if it permits
       to have a private context for all registered frames, which is passed to the
       interrupts. In these cases the function pointer will be configured to be NULL. */
    if(_mapOsHandleFrameToCdeIndex.fctMakeMapEntryOsHandleFrameToCdeIndex != NULL
       && !_mapOsHandleFrameToCdeIndex.fctMakeMapEntryOsHandleFrameToCdeIndex
                                       ( canId
                                       , idxBus
                                       , osHandleFrame
                                       , idxFrame
                                       , isInbound
                                       )
      )
    {
        /* Error in external code: No space left in its map. This frame can't be
           registered. */
        -- _noFrames;
        return CDE_INVALID_FRAME_INDEX;
    }

    /* Now invoke the registered callback, which has the meaning of initialization callback
       this time. */
    event_t evInit = { .kind = CDE_EV_FRAME_INIT
                     , .source = {.type = objTypeFrame, .objRef = {.pFrame = pFrame}}
                     , .pDispatcher = pFrame->pDispatcher
                     , .sizeOfData = 0
                     };
    invokeCallback(&evInit);

    return idxFrame;

} /* End of cde_registerFrame */




/**
 * A CAN bus related event is posted. It is put into the associated dispatcher's queue.\n
 *   This function is invoked by the integration code. The call is typically used from
 * within a CAN interrupt handler. The posted event normally is a bus state change or a bus
 * error. The kind of postable events depends on the platform and the integration.
 *   @return
 * \a true, if function succeeded, else \a false. The dispatcher's queue has a maximum
 * length and the function will return false if it is full. In this case, the event is
 * entirely ignored (besides the reporting of the queue-full event).
 *   @param idxBus
 * The index of the bus the event is related to. When registering the bus it had been
 * associated with a particular dispatcher and the event will be put into this dispatcher's
 * queue.
 *   @param kind
 * The kind of event is passed to the client code, which reads the posted events from the
 * other end of the queue. It is an enumeration, which is meaningless to the dispatcher
 * engine or queue. Which values are passed is entirely in the scope of the integration
 * code, which defines both, the event reporting interrupts and the client code, which
 * evaluates the queued elements.\n
 *   As a recommendation, the values of the enumeration \ref cde_kindOfEvent_t can be used
 * as far as applicable. If other values are used then they should have no overlap with the
 * values of \ref cde_kindOfEvent_t. Please refer to #CDE_EV_FIRST_CUSTOM_EVENT, too.
 *   @param pData
 * A pointer to some event data, which is meaningless to the dispatcher engine. Normally
 * used to convey CAN frame content bytes in case of a reception event, but can be anything
 * else. May be NULL if \a sizeOfData is zero, too.
 *   @param sizeOfData
 * The number of data bytes. The elements of the dispatcher queue have a fixed limit for
 * the conveyed data. This limit must not be exceeded; this is checked by assertion and the
 * function will return false and further ignore the event.
 *   @remark
 * Posting an event to a particular dispatcher queue is not reentrant. If event sources
 * running in different CPU contexts are posting to one and the same dispatcher then the
 * integration code needs to implement mutual exclusion. All of these event sources
 * need to be serialized with respect to event posting.\n
 *   Note, "event posting" does not only relate to this method but includes the other method
 * \a cde_postFrameEvent if the posted frame event is configured to be processed by the same
 * dispatcher.\n
 *   Please see cde_postFrameEvent() for more details.
 */

boolean_t cde_postBusEvent( unsigned int idxBus
                          , unsigned int kind
                          , const void *pData
                          , unsigned int sizeOfData
                          )
{
    /* Find the reference to the dispatcher to be applied for the event and assemble the
       event source object reference. */
    dispatcher_t *pDisp;
    objRef_t evSrc;
    evSrc.type = objTypeBus;
    if(idxBus >= _noBuses)
    {
        CDE_ASSERT(false);
        return false;
    }
    evSrc.objRef.pBus = &_busAry[idxBus];
    pDisp = evSrc.objRef.pBus->pDispatcher;

    return postEvent(pDisp, evSrc, kind, pData, sizeOfData);

} /* End of cde_postBusEvent */




/**
 * A CAN frame related event is posted. It is put into the associated dispatcher's queue.\n
 *   This function is invoked by the integration code. The call is typically used from
 * within a CAN interrupt handler. The posted event normally is a frame reception event or
 * a frame send acknowledge event, but it's also imaginable that a platform has error or
 * status events, which are related to frames. The kind of postable events depends on the
 * platform and the integration.
 *   @return
 * \a true, if function succeeded, else \a false. The dispatcher's queue has a maximum
 * length and the function will return false if it is full. In this case, the event is
 * entirely ignored (besides the reporting of the queue-full event).
 *   @param idxBus
 * The index of the bus the frame is transmitted on. Please refer to the description of
 * parameter \a osHandleFrame, too.
 *   @param osHandleFrame
 * The frame's handle as used (and issued) by the operating system. The pair of bus index
 * and frame handle is translated into the internally used frame index by means of the
 * mapping table, which has been built up during frame registration and which is
 * implemented as external integration code.\n
 *   If no specific mapping has been built up then the default mapping "osHandleFrame
 * is engine frame index" is applied.
 *   @param kind
 * The kind of event is passed to the client code, which reads the posted events from the
 * other end of the queue. It is an enumeration, which is meaningless to the dispatcher
 * engine or queue. Which values are passed is entirely in the scope of the integration
 * code, which defines both, the event reporting interrupts and the client code, which
 * evaluates the queued elements.\n
 *   As a recommendation, the values of the enumeration \ref cde_kindOfEvent_t can be used
 * as far as applicable. If other values are used then they should have no overlap with the
 * values of \ref cde_kindOfEvent_t. Please refer to #CDE_EV_FIRST_CUSTOM_EVENT, too.
 *   @param pData
 * A pointer to some event data, which is meaningless to the dispatcher engine. Normally
 * used to convey CAN frame content bytes in case of a reception event, but can be anything
 * else. May be NULL if \a sizeOfData is zero, too.
 *   @param sizeOfData
 * The number of data bytes. The elements of the dispatcher queue have a fixed limit for
 * the conveyed data. This limit must not be exceeded; this is checked by assertion and the
 * function will return false and further ignore the event.
 *   @remark
 * Posting an event to a particular dispatcher queue is not reentrant. If event sources
 * running in different CPU contexts are posting to one and the same dispatcher then the
 * integration code needs to implement mutual exclusion. All of these event sources
 * need to be serialized with respect to event posting.\n
 *   Note, "event posting" does not only relate to this method but includes the other method
 * cde_postBusEvent() if the posted bus event is configured to be processed by the same
 * dispatcher.\n
 *   In practice, concurrent event sources that require mutual exclusion will likely occur
 * if the events are reported by different interrupts; different interrupts have different
 * priorities on most existing systems and interrupts of higher priority are normally
 * allowed to preempt those of lower priority. In this situation, a reasonable alternative
 * to explicit mutual exclusion code is an architecture using another dispatcher for each
 * interrupt and running all the dispatcher's main functions one after another in the event
 * receiving APSW task.
 */

boolean_t cde_postFrameEvent( unsigned int idxBus
                            , cde_osHandleFrame_t osHandleFrame
                            , unsigned int kind
                            , const void *pData
                            , unsigned int sizeOfData
                            )
{
    /* Apply the (external) mapping in order to find the frame the event is related to. */
    unsigned int idxFrame;
    if(_mapOsHandleFrameToCdeIndex.fctMapOsHandleFrameToCdeIndex != NULL)
    {
        if(!_mapOsHandleFrameToCdeIndex.fctMapOsHandleFrameToCdeIndex( &idxFrame
                                                                     , idxBus
                                                                     , osHandleFrame
                                                                     )
          )
        {
            /* The external map doesn't know the frame. This is normally an implementation
               error in the external code and we could even have an assertion here.
               However, the mapping has been specified tolerant, only the event is lost. */
            // TODO Should this be counted like a lost event due to queue full?
            return false;
        }
    }
    else
    {
        /* Default handle mapping: OS and dispatcher use the same simple zero based index. */
        idxFrame = (unsigned int)osHandleFrame;
    }

    /* Find the reference to the dispatcher to be applied for the event and assemble the
       event source object reference. */
    if(idxFrame >= _noFrames)
    {
        /* If this should fire then we see an error in the external implementation of the
           handle mapping. */
        CDE_ASSERT(false);
        return false;
    }
    dispatcher_t *pDisp;
    objRef_t evSrc;
    evSrc.type = objTypeFrame;
    evSrc.objRef.pFrame = &_frameAry[idxFrame];
    pDisp = evSrc.objRef.pFrame->pDispatcher;

    return postEvent(pDisp, evSrc, kind, pData, sizeOfData);
    
} /* End of cde_postFrameEvent */




/**
 * Get the number of recorded queue full events, i.e. the number of lost events due to an
 * overfull queue.
 *   @return
 * Get the number, which should normally be zero in case of a well designed queue size.
 *   @param idxDispatcher
 * The index of the dispatcher, whose queue is meant.
 *   @param reset
 * If \a true then the event counter is reset to zero at the next occasion. Due to the fact
 * that the reset command is handled by the event producing task or interrupt no statement
 * can be made when the reset will actually appear. Due to race conditions it may even
 * slightly increment until the reset command is executed. In particular, the client code
 * must not assume that it can accurately compute the total number of queue full events by
 * regularly calling this method with parameter \a reset set to \a true and summing up the
 * function result values.\n
 *   If \a reset is not used and if the event counter reaches its limit then it'll be held
 * at this limit.\n
 *   In C11 compilation all delays and race conditions disappear and the function return
 * value is the real, accumulatable number of events since the previous call of this method
 * or cde_getNoQueueFullEvents() with \a reset == \a true.
 *   @remark
 * This function is designed for call from any application context. It might be the task,
 * which clocks the referenced dispatcher or another task. The function may be called from
 * a callback in the dispatcher's context, too, but a dedicated function with same
 * functionality is provided for this particular purpose, please refer to \a
 * cde_getNoQueueFullEvents.
 *   @remark
 * The intended use case of this method is to have a diagnostic API, which gives some
 * feedback about the appropriateness of the chosen queue length. Unless the code is
 * compiled in C11 mode and due to race conditions between event source and APSW is the
 * result not fully consistent (see above) and must not be used for essential program flow
 * decisions.
 */

cde_atomicUnsignedInt_t cde_getNoDispatcherQueueFullEvents( unsigned int idxDispatcher
                                                          , boolean_t reset
                                                          )
{
    CDE_ASSERT(idxDispatcher < _noDispatchers);
    return getNoQueueFullEvents(&_dispatcherAry[idxDispatcher], reset);

} /* End of cde_getNoDispatcherQueueFullEvents */




/**
 * The regular tick function of a dispatcher. This function is invoked from the (periodic)
 * APSW task, which processes the dispatched events. Normally the task, which receives and
 * sends the CAN frames, which are associated with the given dispatcher.\n
 *   All notifications and timer operations and thus all can frame related actions are done
 * in the context of this function call (actually as sub-routines of this invokation) and
 * they are therefore completely race conidtion free with the rest of the same APSW task
 * code.
 *   @param idxDispatcher
 * The index of the dispatcher, which is clocked.
 */

void cde_dispatcherMain(unsigned int idxDispatcher)
{
    if(idxDispatcher >= _noDispatchers)
    {
        /* Invalid dispatcher index. */
        CDE_ASSERT(false);
        return;
    }
    dispatcher_t * const pDisp = &_dispatcherAry[idxDispatcher];

    /* Process all meanwhile received external events. */
    while(true)
    {
        /* Check the dispatcher's queue for a received event. If any, return the eldest one
           by reference. We own this element until we get the next one - be it immediately
           in the next loop or later in the next call of the dispatcher main method.
             We get NULL if there's no newly received event. */
        const event_t *pEvent = tsq_readFromHead(pDisp->pEventQueue);
        if(pEvent == NULL)
            break;

        /* Process the event and the contained data by forwarding it to the client code
           (outside the dispatcher engine). This code is normally auto-coded from the
           network database file and is aware of the meaning of the received events. */
        invokeCallback(pEvent);

    } /* End while(All meanwhile received events) */

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
                /* We need an event object. Since we use the flexible aray member we can't
                   simply instantiate such an object, no space for the flexible part would
                   be allocated. */
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                const unsigned int sizeOfEvent = sizeof(event_t) + sizeof(void*);
# if defined(_STDC_VERSION_C11)
                _Alignas(event_t) unsigned char memChunk[sizeOfEvent];
                #define pEvTimer ((event_t*)&memChunk[0])
# else
                struct { event_t evBody;
                         void *flexibleArrayContents;
                       } memChunk;
                CDE_ASSERT(sizeof(memChunk) >= sizeOfEvent);
                #define pEvTimer ((event_t*)&memChunk)
# endif
#else
                event_t evTimer;
                #define pEvTimer (&evTimer)
#endif
                /* Timer is due, create a timer event and invoke the callback. */
                *pEvTimer = (event_t){ .kind = CDE_TIMER_ELAPSED
                                     , .source = { .type = objTypeTimer
                                                 , .objRef = {.pTimer = pTimer}
                                                 }
                                     , .pDispatcher = pDisp
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                     , .sizeOfData = sizeof(pEvTimer->dataAry[0])
#else
                                     , .sizeOfData = 0
#endif                               
                                     };
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                pEvTimer->dataAry[0] = pTimer->pUserContextData;
#endif
                invokeCallback(pEvTimer);
                #undef pEvTimer

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
                    /* TODO Consider if an auto-kill timer may be retriggered in its own
                       on-elapsed callback: This could be seen here by tiDue>tiNow. If so,
                       we could decide not to remove the timer. However, is this a
                       transparent behavior? Remains the differentiation to non auto-kill
                       still clear to the user? What is the advantage in contrast to the
                       auto-kill single shot timer so far? */

                    /* The timer object is scheduled for deletion. */
                    pTimer->tiReload = TIMER_STATE_KILLED;
                }
                else
                {
                    /* The timer can be in state killed or suspended if the according API
                       function has been called from the within the callback of the timer.
                       (See cde_killTimer and cde_suspendSingleShotTimer.) */
                }
            } /* End if(Is tested timer due?) */

            /* Advance to next timer object. */
            pLinkPtr = &pTimer->pNext;
            pTimer = pTimer->pNext;

        } /* End if(Timer object scheduled for deletion or still operational?) */

    } /* End while(All existing timer objects) */

    /* Add the list of timers newly created in the callbacks of the visit-all-timers loop
       to the list of active timers. They will be checked for due time the first time in
       the next time tic. */
    if(pDisp->listOfNewTimerObjects != NULL)
    {
        /* *pLinkPtr is either the link pointer of the last element of the non-empty timer
           list or the list pointer of the dispatcher. Append the newly-created list by
           overwriting this pointer. */
        CDE_ASSERT(*pLinkPtr == NULL);
        *pLinkPtr = pDisp->listOfNewTimerObjects;

        /* Clear the list of new timers, needed only to temporarily collect new objects. */
        pDisp->listOfNewTimerObjects =
        pDisp->pLastNewTimerObject   = NULL;

    } /* End if(Have new timer objects been created in this tic?) */

    /* (Cyclically) increment the time. */
    pDisp->tiNow += pDisp->tiTick;

} /* End of cde_dispatcherMain */




/**
 * Get the number of recorded queue full events, i.e. the number of lost events due to an
 * overfull queue.
 *   @return
 * Get the number, which should normally be zero in case of a well designed queue size.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param reset
 * If \a true then the event counter is reset to zero at the next occasion. Due to the fact
 * that the reset command is handled by the event producing task or interrupt no statement
 * can be made when the reset will actually appear. Due to race conditions it may even
 * slightly increment until the reset command is executed. In particular, the client code
 * must not assume that it can accurately compute the total number of queue full events by
 * regularly calling this method with parameter \a reset set to \a true and summing up the
 * function result values.\n
 *   If \a reset is not used and if the event counter reaches its limit then it'll be held
 * at this limit.\n
 *   In C11 compilation all delays and race conditions disappear and the function return
 * value is the real, accumulatable number of events since the previous call of this method
 * or cde_getNoDispatcherQueueFullEvents() with \a reset == \a true.
 *   @remark
 * This function is designed for call from a callback. The addressed dispatcher is
 * retrieved from the callback's context. There's the other function \a
 * cde_getNoDispatcherQueueFullEvents, which provides the same functionality for the
 * normal application context.
 *   @remark
 * The intended use case of this method is to have a diagnostic API, which gives some
 * feedback about the appropriateness of the chosen queue length. Unless the code is
 * compiled in C11 mode and due to race conditions between event source and APSW is the
 * result not fully consistent (see above) and must not be used for essential program flow
 * decisions.
 */

cde_atomicUnsignedInt_t cde_getNoQueueFullEvents( const cde_callbackContext_t *pContext
                                                , boolean_t reset
                                                )
{
    return getNoQueueFullEvents(pContext->pDispatcher, reset);

} /* End of cde_getNoQueueFullEvents */




/**
 * Create a periodic timer event from a callback.\n
 *   Typical use case is a timer, which triggers sending of regular frames.
 *   @return
 * The timer handle is returned; this handle is used to identify a timer (if several timers
 * should share the same callback function) or to perform other operations on this timer.\n
 *   If no timer can be created due to a lack of memory then #CDE_INVALID_TIMER_HANDLE is
 * returned instead. Due to the static, deterministic error allocation concept this error
 * should preferrably be handled by a simple assertion only; if this assertion doesn't fire
 * in the DEBUG compilation then there won't be an error in the production code neither.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param tiPeriod
 * The timer will invoke the specified callback \a callback every \a tiPeriod time units.
 * The unit is the same as that of argument \a tiTick in the call of
 * cde_createDispatcher().\n
 *   The value needs to be positive. If it is less than the tick time of the dispatcher than
 * it is rounded upwards to this tick time; the timer will fire in every tick of the
 * dispatcher.\n
 *   The cycle time is not rounded to a multiple of the dispatcher's clock tick. If \a
 * tiPeriod is not a multiple of the clock tick then the timer will always fire at the
 * first tick at or after the next nominal due time. The timer events are no longer
 * equidistant but the nominal cycle time is kept in average.
 *   @param callback
 * Please refer to \a tiPeriod.
 *   @param pUserContextData
 * The user specified context information, which is stored with the timer and which will be
 * brought back into its callback at due time. In the timer's callback, use \a
 * cde_getEventData to retrieve the value passed in here. The data type of the user context
 * data is hidden behind \a void*; if you really pass in a pointer to some data then
 * cde_getEventData() will return the pointer - not the data it points to.\n
 *   This argument is available only if #CDE_ENABLE_TIMER_CONTEXT_DATA is set to 1.
 *   @remark
 * This method and cde_createSingleShotTimer() are the only pieces of code in the CAN
 * interface implementation, which suffer from race conditions with other threads that call
 * cde_dispatcherMain(), too, and that could coincidently create a timer. The macros
 * #cde_enterCriticalSection and #cde_leaveCriticalSection need to be defined in this
 * case.\n
 *   It's a strong recommendation to not use the timer creation API at run-time and to not
 * set the critical section defines. Create your timers preferably at system initialization
 * time. If periodic timers with varying cycle times are needed, this will likely require
 * using single shot timers as a substitute; these can be re-triggered and re-used while
 * period timers can only be killed and re-created.
 *   @see cde_createDispatcher
 */

cde_handleTimer_t cde_createPeriodicTimer( const cde_callbackContext_t *pContext
                                         , signed int tiPeriod
                                         , cde_callback_t callback
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                         , void *pUserContextData
#endif
                                         )
{
    return createTimer( pContext
                      , /* isPeriodic */ true
                      , tiPeriod
                      , callback
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                      , pUserContextData
#endif
                      , /* killAtDueTime */ false
                      );
} /* End of cde_createPeriodicTimer */





/**
 * Create a single shot timer event from a callback.\n
 *   Typical use case is a timer, which triggers once after a while to notify a timeout.
 * This timer can be re-triggered before it elapses and it can be reused after having
 * elapsed.
 *   @return
 * The timer handle is returned; this handle is used to identify a timer (if several timers
 * should share the same callback function) or to perform other operations on this timer.\n
 *   If no timer can be created due to a lack of memory then #CDE_INVALID_TIMER_HANDLE is
 * returned instead. Due to the static, deterministic error allocation concept this error
 * should preferrably be handled by a simple assertion only; if this assertion doesn't fire
 * in the DEBUG compilation then there won't be an error in the production code neither.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param tiFromNow
 * The timer will invoke the specified callback \a tiFromNow time units later.\n
 *   The unit is the same as that of argument \a tiTick in the call of
 * cde_createDispatcher().\n
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
 *   @param pUserContextData
 * The user specified context information, which is stored with the timer and which will be
 * brought back into its callback at due time. In the timer's callback, use \a
 * cde_getEventData to retrieve the value passed in here. The data type of the user context
 * data is hidden behind \a void*; if you really pass in a pointer to some data then
 * cde_getEventData() will return the pointer - not the data it points to.
 *   This argument is available only if #CDE_ENABLE_TIMER_CONTEXT_DATA is set to 1.
 *   @param killAtDueTime
 * Single shot timers can be killed at due time (and after callback processing) or they can
 * stay alive for later reprogramming of a new single-shot time.
 *   @remark
 * This method and cde_createPeriodicTimer() are the only pieces of code in the CAN
 * interface implementation, which suffer from race conditions with other threads that call
 * cde_dispatcherMain(), too, and that could coincidently create a timer. The macros
 * #cde_enterCriticalSection and #cde_leaveCriticalSection need to be defined in this
 * case.\n
 *   It's a strong recommendation to not use the timer creation API at run-time and to not
 * set the critical section defines. Create your timers preferably at system initialization
 * time but at runtime just re-trigger the always same instead of killing them and creating
 * new ones.
 *   @see cde_createDispatcher
 *   @see cde_retriggerSingleShotTimer
 */

cde_handleTimer_t cde_createSingleShotTimer( const cde_callbackContext_t *pContext
                                           , signed int tiFromNow
                                           , cde_callback_t callback
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                           , void *pUserContextData
#endif
                                           , boolean_t killAtDueTime
                                           )
{
    return createTimer( pContext
                      , /* isPeriodic */ false
                      , tiFromNow
                      , callback
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                      , pUserContextData
#endif
                      , killAtDueTime
                      );
} /* End of cde_createSingleShotTimer */





/**
 * A timer is killed. No later callbacks will appear for periodic and single shot timers
 * and nor will it be possible to reset the due time of a killed timer. Killing of a timer
 * can be done at any reasonable time. Exceptions are: The operation must neither be
 * applied twice or more often to the same timer and nor after leaving the callback of a
 * single-shot timer with auto kill property.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param hTimer
 * The handle of the killed timer as got from the create function. The handle becomes
 * invalid with return from this function!\n
 *   The handle may be \a NULL if the function is used from the on-elapse callback of a
 * timer. In which case the operation affects this timer. This operation is permitted but
 * useless for a single-shot timer with auto-kill property.
 *   @see cde_createSingleShotTimer
 *   @see cde_createDispatcher
 *   @remark
 * This function may be called from frame, bus and timer callbacks. It relates to the
 * explicitly mentioned timer object. (For \a hTimer == \a NULL see above)
 */

void cde_killTimer( const cde_callbackContext_t *pContext
                  , cde_handleTimer_t hTimer
                  )
{
    /* Find the timer object if not explicitly passed in. */
    if(hTimer == NULL)
    {
        CDE_ASSERT(pContext->source.type == objTypeTimer);
        hTimer = pContext->source.objRef.pTimer;
    }
    CDE_ASSERT(hTimer != NULL);

    /* The timer object is scheduled for deletion. */
    hTimer->tiReload = TIMER_STATE_KILLED;

} /* End of cde_killTimer */



/**
 * Stop a running timer. The difference to kill is that the timer object is not marked for
 * reuse (which is the substitute for object destroying in our static, deterministic memory
 * allocation concept). The handle stays valid and the timer can later be reused by
 * reprogramming its due time with cde_retriggerSingleShotTimer().\n
 *   The concept of suspending and later reusing timers only holds for single shot timers
 * without the auto-kill property set. Calling this function for an auto-kill single shot
 * timer is still permitted but the operation is effectively a kill. These timers can't be
 * reprogrammed after suspend. Calling this function for a periodic timer is forbidden; this
 * is caught by assertion.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param hTimer
 * The handle of the suspended timer as got from the create function. It needs to be a
 * single-shot timer. Otherwise an assertion fires.\n
 *   The handle may be \a NULL if the function is used from the on-elapse callback of a
 * single-shot timer. In which case the operation affects this timer.\n
 *   If the function is called from the on-elapse callback of a single-shot timer with
 * auto-kill property set then the operation is without effect since the timer would be
 * killed anyway.
 */
void cde_suspendSingleShotTimer( const cde_callbackContext_t *pContext
                               , cde_handleTimer_t hTimer
                               )
{
    /* Find the timer object if not explicitly passed in. */
    if(hTimer == NULL)
    {
        CDE_ASSERT(pContext->source.type == objTypeTimer);
        hTimer = pContext->source.objRef.pTimer;
    }
    CDE_ASSERT(hTimer != NULL);

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
        CDE_ASSERT(hTimer->tiReload == TIMER_STATE_SINGLE_SHOT_SUSPENDED);

} /* End of cde_suspendSingleShotTimer */




/**
 * A single shot timer can be reprogrammed during elapsing or - but only if it
 * doesn't have the auto-kill property set - even after firing or explicit suspend command.
 * Use this function to redefine the due time.\n
 *   For running single shot timers with or without auto-kill property this operation means
 * to postpone the timer event by a new time span counting from now.\n
 *   For suspended timers it means the reactivation of an inactive timer object.
 * Reactivation after suspend it functionally identical to killing a timer (explicit or by
 * auto-kill) and creating a new one. The only difference is the different memory management
 * impact, kill and create can mean to allocate a new object on the heap, whereas
 * suspend/resume guarantees not to do any heap operation.\n
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
 * cde_createDispatcher().\n
 *   The value needs to be positive. If it is less than the tick time of the dispatcher than
 * it is rounded upwards to this tick time and the timer fires in the next tick of the
 * dispatcher.
 *   @remark
 * This function may be called from frame, bus and timer callbacks. It relates to the
 * explicitly mentioned timer object. (For \a hTimer == \a NULL see above.)
 *   @see cde_createSingleShotTimer
 *   @see cde_createDispatcher
 */

void cde_retriggerSingleShotTimer( const cde_callbackContext_t *pContext
                                 , cde_handleTimer_t hTimer
                                 , signed int tiNewFromNow
                                 )
{
    dispatcher_t * const pDisp = pContext->pDispatcher;

    /* Find the timer object if not explicitly passed in. */
    if(hTimer == NULL)
    {
        CDE_ASSERT(pContext->source.type == objTypeTimer);
        hTimer = pContext->source.objRef.pTimer;
    }

    /* If this assertion fires then it either because of an invalid time designation or
       because the method has been called for a periodic timer, which must not be
       retriggrered. */
    CDE_ASSERT(tiNewFromNow > 0  &&  hTimer != NULL
               && (hTimer->tiReload == TIMER_STATE_SINGLE_SHOT
                   ||  hTimer->tiReload == TIMER_STATE_SINGLE_SHOT_AUTO_KILL
                   ||  hTimer->tiReload == TIMER_STATE_SINGLE_SHOT_SUSPENDED
                  )
              );

    hTimer->tiDue = pDisp->tiNow + tiNewFromNow;

    /* Reactivate a single shot timer without auto kill, which had elapsed meanwhile. */
    if(hTimer->tiReload == TIMER_STATE_SINGLE_SHOT_SUSPENDED)
        hTimer->tiReload = TIMER_STATE_SINGLE_SHOT;

} /* End of cde_retriggerSingleShotTimer */




/**
 * All events related to a bus, frame or timer are reported through the registered
 * callback. In general this callback can have a switch/case to handle different kinds of
 * events. Sometime it might be better to (temporarily) redefine the callback function to
 * handle anticipated, specific events. From within a callback the client code may use this
 * function to re-register the callback function for all future events.
 *   @return
 * The callback function registered so far is returned.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param newCallback
 * The new callback function.
 *   @remark
 * This function may be called from frame, bus and timer callbacks. It relates to the
 * callback of the the event causing bus, frame or timer object.
 */

cde_callback_t cde_installCallback( const cde_callbackContext_t *pContext
                                  , cde_callback_t newCallback
                                  )
{
    cde_callback_t *pCallback;
    switch(pContext->source.type)
    {
    case objTypeBus:
        pCallback = &pContext->source.objRef.pBus->callback;
        break;
    case objTypeFrame:
        pCallback = &pContext->source.objRef.pFrame->callback;
        break;
    case objTypeTimer:
        pCallback = &pContext->source.objRef.pTimer->callback;
        break;
    default:
        CDE_ASSERT(false);
        return NULL;
    }

    cde_callback_t oldCallback = *pCallback;
    *pCallback = newCallback;
    return oldCallback;

} /* End of cde_installCallback */




/**
 * Get the CAN ID of a frame from a callback invoked by frame or timer event. If it is a
 * timer event then the operation relates to the parent frame of the timer.
 *   @return
 * The CAN ID.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from frame or timer callback. An assertion fires if this
 * function is invoked from a bus event's callback or from a timer's callback and the
 * timer's parent is a bus.
 */

unsigned long cde_getCanId(const cde_callbackContext_t *pContext)
{
    frame_t * const pFrame = getFrameFromContext(pContext);
    CDE_ASSERT(pFrame != NULL);
    return pFrame->canId;

} /* End of cde_getCanId */




/**
 * Get the index of the frame. The index is the same, which had been returned by the
 * registration of this frame (see cde_registerFrame()). The affected frame is the one,
 * which caused the invocation of the callback. If it is a timer callback then the
 * operation relates to the parent frame of the timer.
 *   @return
 * Get the zero based, linear frame index.\n
 *   No frame index can be determined if the callback, which uses this method is not frame
 * related. This situation is caught by assertion and the production compilation will
 * return #CDE_INVALID_FRAME_INDEX.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */

unsigned int cde_getIdxFrame(const cde_callbackContext_t *pContext)
{
    const frame_t *pFrame = getFrameFromContext(pContext);
    if(pFrame != NULL)
    {
        unsigned int idxFrame = (unsigned int)(pFrame - _frameAry);
        CDE_ASSERT(idxFrame < _noFrames);
        return idxFrame;
    }
    else
    {
        CDE_ASSERT(false);
        return CDE_INVALID_FRAME_INDEX;
    }
} /* End of cde_getIdxFrame */




#if CDE_ENABLE_API_GET_INDEX_BUS == 1
/**
 * A callback may invoke this method to get the operating system handle of the related bus.
 * For bus related events, this is the causing bus. For timer callbacks, this is either its
 * parent bus or the bus its parent frame is transmitted on. For frame related callbacks
 * this is the bus the frame is transmitted on.
 *   @return
 * The OS handle of the CAN bus.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from all callbacks.
 *   @remark
 * This API function is available only if #CDE_ENABLE_API_GET_INDEX_BUS is set to 1.
 */

unsigned int cde_getIdxBus(const cde_callbackContext_t *pContext)
{
    frame_t * const pFrame = getFrameFromContext(pContext);
    if(pFrame != NULL)
        return pFrame->idxBus;
    else
    {
        bus_t * const pBus = getBusFromContext(pContext);
        CDE_ASSERT(pBus != NULL // Implementation error in this module if this ever fires.
                   &&  pBus - &_busAry[0] < (intptr_t)_noBuses
                  );
        return (unsigned int)(pBus - &_busAry[0]);
    }
} /* End of cde_getIdxBus */
#endif



#if CDE_ENABLE_API_GET_OS_HANDLE_FRAME == 1
/**
 * Get the operating system handle of the frame related to the callback, which calls this
 * method. The affected frame is the one, which caused the invocation of the callback. If
 * it is a timer callback then the operation relates to the parent frame of the timer.
 *   @return
 * The OS handle of the CAN frame.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from frame or timer callback. An assertion fires if this
 * function is invoked from a bus event's callback or from a timer's callback and the
 * timer's parent is not a frame.
 *   @remark
 * This API function is available only if #CDE_ENABLE_API_GET_OS_HANDLE_FRAME is set to 1.
 */

cde_osHandleFrame_t cde_getOsHandleFrame(const cde_callbackContext_t *pContext)
{
    frame_t * const pFrame = getFrameFromContext(pContext);
    CDE_ASSERT(pFrame != NULL);
    return pFrame->osHandleFrame;

} /* End of cde_getOsHandleFrame */
#endif



/**
 * Get the handle of the timer causing the callback of a #CDE_TIMER_ELAPSED event, which
 * calls this method. The method can be useful to identify the due timer if several timer
 * objects share the same callback.
 *   @return
 * The handle of the timer object as initially got from either cde_createPeriodicTimer() or
 * cde_createSingleShotTimer().
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from a timer callback only. An assertion fires if this
 * function is invoked from a bus or frame event's callback.
 */

cde_handleTimer_t cde_getHandleTimer(const cde_callbackContext_t *pContext)
{
    CDE_ASSERT(pContext->kind == CDE_TIMER_ELAPSED  &&  pContext->source.type == objTypeTimer);
    return pContext->source.objRef.pTimer;

} /* End of cde_getHandleTimer */



#if CDE_ENABLE_API_IS_INBOUND_TRANSMISSION == 1
/**
 * Get the transmission direction of the frame related to the callback, which calls this
 * method. The affected frame is the one, which caused the invocation of the callback. If
 * it is a timer callback then the operation relates to the parent frame of the timer.
 *   @return
 * \a true for a received frame, \b false otherwise.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from frame or timer callback. An assertion fires if this
 * function is invoked from a bus event's callback or from a timer's callback and the
 * timer's parent is not a frame.
 *   @remark
 * This API function is available only if #CDE_ENABLE_API_IS_INBOUND_TRANSMISSION is set to
 * 1.
 */

boolean_t cde_isInboundTransmission(const cde_callbackContext_t *pContext)
{
    frame_t * const pFrame = getFrameFromContext(pContext);
    CDE_ASSERT(pFrame != NULL);
    return pFrame->isInbound;

} /* End of cde_isInboundTransmission */
#endif




/**
 * Get the reason for invokation of a callback.
 *   @return
 * The reason for invokation or the causing event.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */

cde_kindOfEvent_t cde_getKindOfEvent(const cde_callbackContext_t *pContext)
{
    return pContext->kind;

} /* End of cde_getKindOfEvent */




/**
 * Get the data contents of an event from within a callback.\n
 *   Normally, this relates to the content bytes of a received frame but for external
 * events other than #CDE_EV_FRAME_RECEPTION it may have any other meaning, which is
 * aggreed on between data producer and consumer, which are both defined in the integration
 * code.\n
 *   For timer events and if user specified timer context data is supported (see
 * #CDE_ENABLE_TIMER_CONTEXT_DATA) then the data contents of the event is the user
 * specified context data. This method will return the pointer value, which had been
 * specified as parameter \a pUserContextData in the timer creation methods, either
 * cde_createPeriodicTimer() or cde_createSingleShotTimer().
 *   @return
 * \a true, if function succeeded, else \a false.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param pSizeOfEvContentByteAry
 * The number of bytes returned by reference through \a pEvContentByteAry.
 *   @param pEvContentByteAry
 * A pointer to a pointer variable in the client code, which is set such that it points to
 * the content data of the event. The pointer in the client code has read-only access to
 * the data and the data it points to is valid only during the execution of the callback,
 * which this method is called from. The data needs to be copied by the callback code if
 * this doesn't suffice.\n
 *   The data has the alignment of a pointer to \a void. If you e.g. know that it actually
 * is an \a int then you may on most platforms cast the got \a void pointer to an \a int
 * pointer and read the integer as a whole. (As opposed to reading all the integer's bytes
 * as unsigned char and composing the number from these.)\n
 *   "On most platforms" refers to the fact that pointers normally have the same or a
 * stricter alignment constraint than type \a int. However, this is not guaranteed and no
 * general statement can be made if the data is of type \a long, \a long \a long, \a float
 * or \a double. Platform specific defines and assertions should make the client code safe
 * and portable if such data is in use.
 *   @remark
 * Event data is not defined for timer events if the code is not compiled with support of
 * user specified timer context data. It must not be used in this case, an assertion would
 * fire and the return value is undefined. See #CDE_ENABLE_TIMER_CONTEXT_DATA for more.
 */

void cde_getEventData( const cde_callbackContext_t *pContext
                     , unsigned int *pSizeOfEvContentByteAry
                     , const void **pEvContentByteAry
                     )
{
    *pSizeOfEvContentByteAry = pContext->sizeOfData;

    /* Timer events don't have contents data besides the user specified context
       information. Using this context information requires however according compile
       configuration. */
    CDE_ASSERT(CDE_ENABLE_TIMER_CONTEXT_DATA == 1  ||  pContext->source.type != objTypeTimer);

#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
    if(pContext->source.type == objTypeTimer)
    {
        /* Timer objects use the event content area to store the user provided pointer to
           the user context data. We get the pointer by reading the first word of the
           flexible array member. */
        assert(pContext->sizeOfData == sizeof(void*));
        *pEvContentByteAry = pContext->dataAry[0];
    }
    else
#endif
    
    /* The data is meaningless to us, it'll particularly not fit to the formal type void*
       of the event content area. We simply return the address of the flexible array member
       as the pointer to the opaque data. */
    *pEvContentByteAry = &pContext->dataAry[0];

} /* End of cde_getEventData */





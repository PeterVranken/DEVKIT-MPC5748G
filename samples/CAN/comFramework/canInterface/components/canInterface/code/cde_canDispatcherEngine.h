#ifndef CDE_CANDISPATCHERENGINE_INCLUDED
#define CDE_CANDISPATCHERENGINE_INCLUDED
/**
 * @file cde_canDispatcherEngine.h
 * Definition of global interface of module cde_canDispatcherEngine.c
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

/*
 * Include files
 */

#include <limits.h>

#include "cde_canDispatcherEngine.config.h"


/*
 * Defines
 */

/** A predefined value of the enumeration \ref cde_kindOfEvent_t meaning Invalid. */
#define CDE_EV_INVALID                  1
/** A predefined value of the enumeration \ref cde_kindOfEvent_t meaning Bus
    initialization. */
#define CDE_EV_BUS_INIT                 2
/** A predefined value of the enumeration \ref cde_kindOfEvent_t meaning Frame
    initialization. */
#define CDE_EV_FRAME_INIT               3
/** A predefined value of the enumeration \ref cde_kindOfEvent_t meaning Timer event. */
#define CDE_TIMER_ELAPSED               4
/** A predefined value of the enumeration \ref cde_kindOfEvent_t meaning CAN frame
    received. */
#define CDE_EV_FRAME_RECEPTION          5
/** A predefined value of the enumeration \ref cde_kindOfEvent_t meaning CAN frame sent. */
#define CDE_EV_FRAME_SEND_ACKNOWLEDGE   6
/** A predefined value of the enumeration \ref cde_kindOfEvent_t meaning CAN frame related
    error. */
#define CDE_EV_FRAME_ERROR              7
/** The end of the range of predefined values for enumeration \ref cde_kindOfEvent_t. */
#define CDE_EV_LAST_PREDEFINED_VALUE    99
/** The first permitted client code's custom value for enumeration \ref cde_kindOfEvent_t.
    Define the enumeration values for your specific external events starting with this
    value. */
#define CDE_EV_FIRST_CUSTOM_EVENT       100

/** The invalid timer handle. */
#define CDE_INVALID_TIMER_HANDLE    NULL

/** The invalid frame index. */
#define CDE_INVALID_FRAME_INDEX     UINT_MAX


/*
 * Global type definitions
 */

/** The interface of a a map, which associates bus index and OS frame handle with the
    internally used frame index. The implementation of the map is done externally as part
    of the integration, here we just specify the interface of the required map. */
typedef struct cde_mapOsHandleFrameToCdeIndex_t
{
    /** This (external) function helps to prepare the map. A single association as appears
        in each frame registration is reported to the map initialization code. This
        function is called once per registered frame as sub-routine of
        cde_registerFrame().\n
          May be NULL. Now a default mapping is applied: The engine assumes that the OS
        uses the same zero based linear index as frame handle as itself does. If it is NULL
        the the other function pointer \a fctMapOsHandleFrameToCdeIndex needs to be NULL,
        too.\n
          Return value:\n
        The external function will return \a true, if it succeeds. The implementation of
        the map may be size or otherwise limited. If the map entry could not be made the
        external function may return \a false. The CAN interface engine will assume that
        the frame in question won't be processed later, it'll in turn discard its related
        entries. If later at run-time an event relates to this frame then it'll be
        ignored.\n
          Parameter \a canId :\n
        The CAN ID of the frame in question. It is the value of the same parameter in the
        call of the parent function \a cde_registerFrame.\n
          Parameter \a idxBus :\n
        The zero based index of the bus the frame in question is transmitted on. It is the
        value of the same parameter in the call of the parent function \a
        cde_registerFrame.\n
          Parameter \a osHandleFrame :\n
        The handle as it has got from the frame registration or initialization at the
        operating system. It is the value of the same parameter in the call of the parent
        function \a cde_registerFrame.\n
          Parameter \a cdeIdxFrame :\n
        The zero based index of the frame as used inside the CAN interface implementation.
        This value needs to be associated with the operating system's frame identification
        (idxBus,osHandleFrame)\n
          Parameter \a isInbound :\n
        The transmission direction of the frame in question. This parameter is useless for
        the pure lookup operation. The frame identification (idxBus,osHandleFrame) should
        be unique without it and the lookup function \a fctMapOsHandleFrameToCdeIndex won't
        make a statement about the transmission direction. The use case is a typical
        optimization. In many integrations the only frame events will relate to frame
        reception. If so, the map could silently ignore all outbound frames and save a
        significant amount of space.\n
           It is the value of the same parameter in the call of the parent function
        cde_registerFrame().
          @remark
        This function is called in the system initialization phase, i.e. in a single
        threaded, race condition free context. */
    boolean_t (*fctMakeMapEntryOsHandleFrameToCdeIndex)( unsigned long canId
                                                       , unsigned int idxBus
                                                       , cde_osHandleFrame_t osHandleFrame
                                                       , unsigned int cdeIdxFrame
                                                       , boolean_t isInbound
                                                       );

    /** The actual map function. The map is queried for a frame index as internally used by
        the dispatcher engine. The map query function is called as sub-routine of the frame
        event notification cde_postFrameEvent().\n
          May be NULL. Now a default mapping is applied: The engine assumes that the OS
        uses the same zero based linear index as frame handle as itself does. If it is NULL
        it may still happen to have a non NULL function pointer for \a
        fctMakeMapEntryOsHandleFrameToCdeIndex. It is for example good practice to
        double-check in DEBUG configuration if the presumptions of the default mapping are
        really fulfilled.\n
          Return value:\n
        Normally, the frame index is returned by reference (see below) and the function
        result is \a true. If the function doesn't find a suitable association it will
        return \a false and the related frame event is lost.\n
          Parameter \a pIdxFrame :\n
        The result of the lookup operation is returned by reference. If the function
        returns \a false then it may ignore this parameter.\n
          Parameter \a idxBus :\n
        The zero based index of the bus the frame in question is transmitted on.\n
          Parameter \a osHandleFrame :\n
        The operating system handle of the frame. It is assumed that this is the handle,
        which is used in the (platform specific) frame reception interrupt or callback to
        identify the frame.
          @remark
        The external implementation of the map function needs to be fully reentrant. It can
        be called concurrently by all CPU contexts, which can invoke \a cde_postFrameEvent
        to report a frame related event. Full re-entrance is considered a weak constraint
        for the implementation insofar the mapping is a pure lookup operation in static,
        unchangeable data. All possible handle associations have been defined in the
        race-condition free initialization phase.
          @remark
        The function is called as sub-routine of cde_postFrameEvent(), see there for more
        details about re-entrance and CPU contexts. */
    boolean_t (*fctMapOsHandleFrameToCdeIndex)
                        ( unsigned int *pIdxFrame
                        , unsigned int idxBus
                        , cde_osHandleFrame_t osHandleFrame
                        );

} cde_mapOsHandleFrameToCdeIndex_t;



/** The kind of a frame-related callback. The enumeration is not defined as such but as a
    series of \#define's in order to enable the integration code to extend the value set of
    the enumeration as required for whatever external events. Please refer to
    #CDE_EV_FIRST_CUSTOM_EVENT. */
typedef unsigned int cde_kindOfEvent_t;

/** The client implemented callback functions can interact with the engine via a bunch of
    API functions. Since any number of concurrent dispatcher engines can be run in different
    tasks it is necessary to have a context for the implementation of the API. This context
    has an opaque type but it has to be passed to all API functions.
      @remark Unfortunately, the wording \a context is misleading since this term is mostly
    used for "CPU context" in order to distinguish the different concurrent execution
    threads in a multi-threading or -core environment. Here, \a context refers to the
    context of using the API, effectively a reference to the dispatcher engine in use. */
typedef struct event_t cde_callbackContext_t;

/** The type of a frame-related callback for external events. */
typedef void (*cde_callback_t)(const cde_callbackContext_t *pContext);

/** The handle or identification of a timer object. */
typedef struct cde_timer_t *cde_handleTimer_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialize the module at application startup. The internal data structures are set up. */
boolean_t cde_initModule( unsigned int maxNoBuses
                        , unsigned int maxNoFrames
                        , unsigned int noDispatchers
                        );

/** Set the references to the required external, integrator provided map, which associates
    the operating system's frame handle with the frame index as used by the interface
    engine. */
void cde_installMapOsHandleFrameToCdeIndex( cde_mapOsHandleFrameToCdeIndex_t
                                                                    mapOsHandleFrameToCdeIndex
                                          );

/** Create a dispatcher object. */
boolean_t cde_createDispatcher( unsigned int idxDispatcher
                              , unsigned int maxQueueLength
                              , unsigned int maxSizeOfElement
                              , signed int tiTick
                              );

/** Register a bus for processing of bus related events by the engine. */
void cde_registerBus( unsigned int idxBus
                    , unsigned int idxDispatcher
                    , cde_callback_t callback
                    );

/** Register a frame for processing by the engine. */
unsigned int cde_registerFrame( unsigned long canId
                              , boolean_t isInbound
                              , unsigned int idxBus
                              , cde_osHandleFrame_t osHandleFrame
                              , unsigned int idxDispatcher
                              , cde_callback_t callback
                              );

/** A CAN bus related event is posted. It is put into the associated dispatcher's event
    queue. */
boolean_t cde_postBusEvent( unsigned int idxBus
                          , unsigned int kind
                          , const void *pData
                          , unsigned int sizeOfData
                          );

/** A CAN frame related event is posted. It is put into the associated dispatcher's event
    queue. */
boolean_t cde_postFrameEvent( unsigned int idxBus
                            , cde_osHandleFrame_t osHandleFrame
                            , unsigned int kind
                            , const void *pData
                            , unsigned int sizeOfData
                            );

/** Get the number of recorded queue full events. For use from any task context. */
cde_atomicUnsignedInt_t cde_getNoDispatcherQueueFullEvents( unsigned int idxDispatcher
                                                          , boolean_t reset
                                                          );

/** The regular tic function of a dispatcher. */
void cde_dispatcherMain(unsigned int idxDispatcher);

/** Get the number of recorded queue full events. For use from callbacks. */
cde_atomicUnsignedInt_t cde_getNoQueueFullEvents( const cde_callbackContext_t *pContext
                                                , boolean_t reset
                                                );

/** Create a periodic timer object. */
cde_handleTimer_t cde_createPeriodicTimer( const cde_callbackContext_t *pContext
                                         , signed int tiPeriod
                                         , cde_callback_t callback
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                         , void *pUserContextData
#endif
                                         );

/** Create a single shot timer. */
cde_handleTimer_t cde_createSingleShotTimer( const cde_callbackContext_t *pContext
                                           , signed int tiFromNow
                                           , cde_callback_t callback
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                           , void *pUserContextData
#endif
                                           , boolean_t killAtDueTime
                                           );

/** Kill a periodic or single shot timer object. */
void cde_killTimer(const cde_callbackContext_t *pContext, cde_handleTimer_t hTimer);

/** Stop a running timer but keep the handle alive for later reuse. */
void cde_suspendSingleShotTimer( const cde_callbackContext_t *pContext
                               , cde_handleTimer_t hTimer
                               );

/** Re-trigger a single shot timer before it has elapsed. */
void cde_retriggerSingleShotTimer( const cde_callbackContext_t *pContext
                                 , cde_handleTimer_t hTimer
                                 , signed int tiNewFromNow
                                 );

/** Redefine the callback function for a given dispatcher/frame context from within a
    callback. */
cde_callback_t cde_installCallback( const cde_callbackContext_t *pContext
                                  , cde_callback_t newCallback
                                  );

/** Get the CAN ID of the related frame from a callback */
unsigned long cde_getCanId(const cde_callbackContext_t *pContext);

/** Get the engine's index of the frame. */
unsigned int cde_getIdxFrame(const cde_callbackContext_t *pContext);

#if CDE_ENABLE_API_GET_INDEX_BUS == 1
/** Get the OS handle of the related bus from a callback */
unsigned int cde_getIdxBus(const cde_callbackContext_t *pContext);
#endif

#if CDE_ENABLE_API_GET_OS_HANDLE_FRAME == 1
/** Get the OS handle of the related frame from a callback */
cde_osHandleFrame_t cde_getOsHandleFrame(const cde_callbackContext_t *pContext);
#endif

/** Get the handle of the timer causing a CDE_TIMER_ELAPSED event. */
cde_handleTimer_t cde_getHandleTimer(const cde_callbackContext_t *pContext);

#if CDE_ENABLE_API_IS_INBOUND_TRANSMISSION == 1
/** Get the transmission direction of the related frame from a callback */
boolean_t cde_isInboundTransmission(const cde_callbackContext_t *pContext);
#endif

/** Query the kind of callback (or event) from within a callback. */
cde_kindOfEvent_t cde_getKindOfEvent(const cde_callbackContext_t *pContext);

/** Get the data contents of an event from within a callback. */
void cde_getEventData( const cde_callbackContext_t *pContext
                     , unsigned int *pSizeOfEvData
                     , const void **ppEvData
                     );

#endif  /* CDE_CANDISPATCHERENGINE_INCLUDED */

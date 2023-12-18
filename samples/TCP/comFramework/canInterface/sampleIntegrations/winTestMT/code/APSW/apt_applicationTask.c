/**
 * @file apt_applicationTask.c
 * This file links the dummy APSW to the operating system (emulation). It contains the
 * entry points into all the application tasks.\n
 *   The init task is for example used to initialize all data structures of the CAN
 * interface.\n
 *   The regularly executed run-time tasks run the CAN interface engine and call the APSW.
 * The CAN interface engine updates all signal values and status in the global CAN API and
 * sends due messages, filled with information read from this API.\n
 *   The APSW could run its operations on the data found in the global CAN API, but it is
 * just a dummy and it doesn't do anything with the input. At least, it produces new random
 * output data, which will then be sent out by the CAN interface engine at next due time.\n
 *   The shutdown task is used to double-check some required conditions.\n
 * This is meant a test of the CAN interface engine only. No real function is found in the
 * implementation. It is all about filling CAN signals with random data, transmitting them
 * through the interface and double-checking the correctness of the data at the other end.
 * Any error is reported by assertion; there's nothing special to observe as long as the
 * application is still running.
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
 *   apt_irqHandlerRxCan
 *   apt_taskInit
 *   apt_task10ms
 *   apt_task100ms
 *   apt_taskShutdown
 * Local functions
 *   getMsgDescription
 *   getCanId
 *   isInboundTransmission
 *   getIdxMessage
 *   getIdxBus
 *   mapSenderEvHandleToSenderPortIndex
 *   onMessageReception
 *   onMessageInTimeout
 *   onInitReceivedMessages
 *   protectAndSendMessage
 *   onSendRegularMessage
 *   onDueCheckEventMessage
 *   onDueCheckMixedMessage
 *   onInitSentMessages
 */


/*
 * Include files
 */

#include "apt_applicationTask.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "sup_startup.h"
#include "ose_operatingSystemEmulation.h"
#include "mem_malloc.h"
#include "ede_eventDispatcherEngine.h"
#include "cst_canStatistics.h"
#include "cap_canApi.h"
#include "e2e_frameProtection.h"
#include "ede_eventSender.h"
#include "cdt_canDataTables.h"
#include "asw_APSW.h"
#include "vsq_dispatcherPortInterface.h"
#include "mpo_mapOffsetOnly.h"


/*
 * Defines
 */

/** Floating point random number with more than 15 Bit resolution; taken fron
    http://www.azillionmonkeys.com/qed/random.html on Jan 23, 2017.
      @remark Caution, the definition make use of a GNU extension and is not portable. */
#define DRAND() ({                                                                  \
    double d;                                                                       \
    do {                                                                            \
       d = (((rand() * RS_SCALE) + rand()) * RS_SCALE + rand()) * RS_SCALE;         \
    } while(d >= 1); /* Round off */                                                \
    d;                                                                              \
})

/** Helper for #DRAND. */
#define RS_SCALE (1.0 / (1.0 + RAND_MAX))

/** A scaled floating point random number in the range [a, b). */
#define RAND(a,b) ((double)((b)-(a))*DRAND()+(double)(a))

/** A Boolean random number with given probability p of getting a true. */
#define BOOL_RAND(p) ((DRAND()<(p))? true: false)

/** The size of an array object in number of elements. The index into the array needs to be
    lower than the returned value. */
#define sizeOfAry(a) (sizeof(a)/sizeof(a[0]))

/** This macro is a primitive way to define the timeout span for received messages. It maps
    the nominal maximum time span between two reception events onto the time span after
    which the CAN interface should decide on timeout. The latter time span needs to be
    greater than the former: CAN bus timing always requires a tolerance and the time
    measurement is done only with the resolution of the tick of the CAN interface engine. */
#define TIMEOUT(tiCycle) (3*(tiCycle)+1)

/** The index of the dispatcher event queue that serves the 10ms APSW task with CAN related
    events. */
#define IDX_EVENT_QUEUE_RX_10MS     0u

/** The index of the dispatcher event queue that serves the 100ms APSW task with CAN
    related events. */
#define IDX_EVENT_QUEUE_RX_100MS    1u


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */

/* Root entry point into APSW. */
static rtos_taskFctResult_t apt_taskInit();

/* Task functions of APSW. Registered at the operating system in apt_taskInit. */
static rtos_taskFctResult_t apt_task10ms();
static rtos_taskFctResult_t apt_task100ms();
static rtos_taskFctResult_t apt_taskShutdown();


/*
 * Data definitions
 */

/** The fundamental entry point into the APSW is defined by this function pointer. It is
    external to the operating system emulation and needs to be instantiated in the APSW
    code. The designated function will be executed as part of the system startup. The
    invokation happens in a race-condition free, single-threaded context. The
    implementation of the executed function gives the APSW the chance to do all further
    initialization, which is all data initialization and - with respect to the operating
    system - the definition of the required threads and task functions. No APSW code is
    executed prior to the function specified here. */
rtos_taskFctResult_t (* const sup_initAPSW)() = apt_taskInit;


/** The handler for inbound messages requires local context data for regular and mixed mode
    messages. Here's an array of context data objects, one for each such message; the entries
    for regular messages precede those for mixed mode messages. */
static ede_handleTimer_t _hTimerInTimeoutAry[CST_NO_CAN_FRAMES_RECEIVED_REGULAR
                                             + CST_NO_CAN_FRAMES_RECEIVED_MIXED
                                            ];

/** The handler for outbound mixed mode messages requires local context data. Here's an array
    of context data objects, one for each such message. */
static struct hdlCtxDataOutMixed_t
{
    /** The handle of the due check timer. */
    ede_handleTimer_t hTimerDueCheck;

    /** The handle of the timeout timer. */
    ede_handleTimer_t hTimerTimeout;

} _hdlCtxDataOutMixedAry[CST_NO_CAN_FRAMES_SENT_MIXED];


/** A memory pool for OS related CAN stack objects, i.e. objects in use by the OS
    notification process. */
static ede_memoryPool_t apt_memoryPoolOS = EDE_INVALID_MEMORY_POOL;

/** A memory pool for APSW related CAN stack objects, i.e. objects in use by the CAN
    notification/event dispatching process. */
static ede_memoryPool_t apt_memoryPoolAPSW = EDE_INVALID_MEMORY_POOL;

/** The sender of CAN events. It is connected to both dispatchers. */
static ede_handleSender_t _hOsEventSender = EDE_INVALID_SENDER_HANDLE;

/** The system, which owns the dispatcher engines processing the CAN events in the 10ms and
    in the 100ms APSW tasks. */
static ede_handleDispatcherSystem_t _hDispatcherSystem = EDE_INVALID_DISPATCHER_SYSTEM_HANDLE;

/** The total count of all ever received messages, including the lost one because of queue
    full events. */
_Atomic unsigned long long apt_noRxMessages = 0;

/** The total number of sent messages, including the lost one because of send buffer full
    events. */
_Atomic unsigned long long apt_noTxMessages = 0;

/** The total number of Rx timeout events. */
_Atomic unsigned long long apt_noEvRxTimeout = 0;

/** The total number of lost Rx messages because of queue full. */
_Atomic unsigned long long apt_noEvRxQueueFull = 0;

/** The total number of recognized E2E validation errors for Rx messages. */
_Atomic unsigned long long apt_noEvRxE2eFailure = 0;

/** The total number of lost Tx messages because of send buffer full events. */
_Atomic unsigned long long apt_noEvTxSendBufFull = 0;


/*
 * Function implementation
 */

/**
 * Get the description of a message from a callback invoked by message or timer event. If
 * it is a timer event then the operation relates to the parent message of the timer.
 *   @return
 * Get the message description by reference. It is the pointer to the message's entry in
 * the APSW's data table \a cdt_canFrameAry.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from an external event or a timer callback.
 */
static inline const cdt_canFrame_t *getMsgDescription(const ede_callbackContext_t *pContext)
{
    const uintptr_t refEventSourceData = ede_getEventSourceData(pContext);
    return (const cdt_canFrame_t *)refEventSourceData;

} /* getMsgDescription */




/**
 * Get the CAN ID of a message from a callback invoked by message or timer event. If it is a
 * timer event then the operation relates to the parent message of the timer.
 *   @return
 * The CAN ID.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from an external event or a timer callback.
 *   @remark
 * This is a helper function for smooth migration of client code made for elder revisions
 * of the event dispatcher: It emulates the CAN specific API cde_getCanId from
 * the dispatcher engine in revision <= 1.5.
 */
static cdt_canId_t getCanId(const ede_callbackContext_t *pContext)
{
    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);
    return pMsgDescCde->canId;

} /* getCanId */




/**
 * Get the transmission direction of the message related to the callback, which calls this
 * method. The affected message is the one, which caused the invocation of the callback. If
 * it is a timer callback then the operation relates to the parent message of the timer.
 *   @return
 * \a true for a received message, \b false otherwise.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from an external event or a timer callback.
 *   @remark
 * This is a helper function for smooth migration of client code made for elder revisions
 * of the event dispatcher: It emulates the CAN specific API cde_isInboundTransmission from
 * the dispatcher engine in revision <= 1.5.
 */
static bool isInboundTransmission(const ede_callbackContext_t *pContext)
{
    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);
    return pMsgDescCde->isReceived;

} /* isInboundTransmission */




/**
 * A callback may invoke this method to get the operating system handle of the related bus.
 * For timer callbacks, this is the bus of the message, which is the parent event of the
 * timer.
 *   @return
 * The index of the CAN bus the related message is transmitted on. Typically, this index
 * will at the same time be the OS handle of the bus.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from all callbacks.
 *   @remark
 * This function may be called from an external event or a timer callback.
 *   @remark
 * This is a helper function for smooth migration of client code made for elder revisions
 * of the event dispatcher: It emulates the CAN specific API cde_getIdxBus from
 * the dispatcher engine in revision <= 1.5.
 */
static unsigned int getIdxBus(const ede_callbackContext_t *pContext)
{
    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);
    return pMsgDescCde->idxCanBus;
    
} /* getIdxBus */



/**
 * The lookup operation of the map, which associates an event queue with the sender's
 * handle of an external event. The map query function is called as sub-routine of
 * sending an event, ede_postEvent().
 *   @return
 * Normally, the port index is returned by reference (see below) and the function
 * result is \a true. If the function doesn't find a suitable association it will
 * return \a false and the related event is lost.
 *   @param hInstance
 * Each sender has its own index space for ports and will require a dedicated map. This
 * is the identification of the map instance to use.
 *   @param pIdxPort
 * The result of the lookup operation is returned by reference. If the function
 * returns \a false then it may ignore this parameter.
 *   @param kindOfEvent
 * First element of characterizing the event source under progress. See argument of
 * same name of addKeyValuePair() for more details.
 *   @param senderHandleEvent
 * Second element of characterizing the event source under progress. See argument of
 * same name of addKeyValuePair() for more details.\n
 *   In this application, the sender handle is the index into the table
 * ose_receivedCanFrameAry of all Rx messages.
 *   @remark
 * The required reentrance of the external implementation depends on the integration.
 * The function can be called concurrently by all CPU contexts, which can invoke \a
 * ede_postEvent() for one and the same sender instance. Different senders will invoke
 * the function with different values of \a hInstance.
 */
static bool mapSenderEvHandleToSenderPortIndex( uintptr_t hInstance ATTRIB_DBG_ONLY
                                              , unsigned int * pIdxPort
                                              , unsigned int kindOfEvent ATTRIB_DBG_ONLY
                                              , ede_senderHandleEvent_t senderHandleEvent
                                              )
{
    assert(hInstance == 0u  &&  kindOfEvent == apt_evt_newRxMsg);
    
    /* The sender (OS) handle of the message is specified to be the index into the
       configuration table. This gives us access to the message properties. */
    assert(senderHandleEvent < sizeOfAry(cdt_canFrameAry));
    const cdt_canFrame_t *const pMsgDescCde = &cdt_canFrameAry[senderHandleEvent];
    *pIdxPort = asw_getAssociatedTaskOfMessage(pMsgDescCde) == 10? IDX_EVENT_QUEUE_RX_10MS
                                                                 : IDX_EVENT_QUEUE_RX_100MS;
    return true;

} /* mapSenderEvHandleToSenderPortIndex */



/**
 * Temporary solution for reception callback: No timing supervision, just E2E validation.
 */
static void onMessageReception(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(isInboundTransmission(pContext)
           &&  ede_getKindOfEvent(pContext) == apt_evt_newRxMsg
          );

    /* Get the CDE index of the message, which is the index into the CDE data tables at the
       same time. This has been ensured by the message registration process. */
    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);

    /* Test: Do some consistency tests. */
    assert(getCanId(pContext).uniqueCanId == pMsgDescCde->canId.uniqueCanId
           &&  getIdxBus(pContext) == pMsgDescCde->idxCanBus
           &&  pMsgDescCde->isReceived
           &&  pMsgDescCde->pInfoTransmission != NULL
          );

    /* Reset the never received bit in the transmission status. */
    pMsgDescCde->pInfoTransmission->stsTransmission &= ~cap_stsTransm_neverReceived;

    /* Some transmission pattern have a timeout supervision. Retrigger the timer and clear
       a possibly set timeout error bit. */
    if(pMsgDescCde->sendMode != cap_enumSendMode_event)
    {
        unsigned int idxHandlerCtxData;
        if(pMsgDescCde->sendMode == cap_enumSendMode_regular)
            idxHandlerCtxData = pMsgDescCde->idxHandlerCtxData;
        else
        {
            assert(pMsgDescCde->sendMode == cap_enumSendMode_mixed);

            /* Both transmission patterns share the same handler context data. The entries
               for mode mixed are placed behind those of mode regular. */
            idxHandlerCtxData = pMsgDescCde->idxHandlerCtxData
                                + CST_NO_CAN_FRAMES_RECEIVED_REGULAR;
        }

        assert(idxHandlerCtxData < sizeOfAry(_hTimerInTimeoutAry)
               &&  _hTimerInTimeoutAry[idxHandlerCtxData] != EDE_INVALID_TIMER_HANDLE
              );
        ede_retriggerSingleShotTimer( pContext
                                    , _hTimerInTimeoutAry[idxHandlerCtxData]
                                    , /* tiNewFromNow */ TIMEOUT(pMsgDescCde->tiCycle)
                                    );

        /* Reset the timeout error in the message related status word. */
        pMsgDescCde->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errTimeout;

    } /* if(Do we have a timeout timer for the given transmission pattern?) */

    /* For event kind apt_evt_newRxMsg the event's data is the message contents. */
    unsigned int sizeOfEvData;
    const uint8_t * const messageContents = ede_getEventData(pContext, &sizeOfEvData);
    assert(sizeOfEvData <= 8);

    /* Run the message specific E2E protection method. By side effect, and only on success,
       the data is written into the global API at the same time. (Where nobody will ever
       look for it in this test.) */
    const boolean_t e2eOkay = pMsgDescCde->fctUnpackApiFrameAndValidate(messageContents);

    /* Indicate the E2E validation result to the APSW. */
    if(e2eOkay)
    {
        pMsgDescCde->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errChecksum;

        /* The reception event is only counted in case of valid data. Otherwise the global
           CAN API has not been updated with new signal values and no reception event must
           be notified. */
        ++ pMsgDescCde->pInfoTransmission->noTransmittedFrames;
        pMsgDescCde->pInfoTransmission->isEvent;
    }
    else
    {
        /* Globally count the recognized failures. */
        ++ apt_noEvRxE2eFailure;

        /* Report the failure. */
        pMsgDescCde->pInfoTransmission->stsTransmission |= cap_stsTransm_errChecksum;
        LOG_FATAL( sup_hGlobalLogger
                 , "%lu ms: "
                   "%s: E2E validation error in inbound message %u%s on bus %u"
                 , ose_tiSim, __func__
                 , pMsgDescCde->canId.id
                 , pMsgDescCde->canId.isExtId? "x": ""
                 , pMsgDescCde->idxCanBus
                 );
    }

    /* In this test, there must never be a data error and there's no APSW, which would
       handle the problem. We report all errors by assertion. */
    assert(e2eOkay);

} /* End of onMessageReception */



/**
 * Timer callback for all inbound messages, which a timeout is defined for. The timer is
 * retriggered on each message reception event and if it eventually fires then it is a
 * timeout event for the related message.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onMessageInTimeout(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(isInboundTransmission(pContext)
           &&  ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED
          );

    /* Get the CDE index of the message, which is the index into the CDE data tables at the
       same time. This has been ensured by the message registration process. */
    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);

    /* Test: Do some consistency tests. */
    assert(getCanId(pContext).uniqueCanId == pMsgDescCde->canId.uniqueCanId
           &&  getIdxBus(pContext) == pMsgDescCde->idxCanBus
           &&  pMsgDescCde->isReceived
           &&  pMsgDescCde->sendMode != cap_enumSendMode_event
           &&  pMsgDescCde->pInfoTransmission != NULL
          );

    /* Globally count all timeout events. */
    ++ apt_noEvRxTimeout;

    /* Set timeout error in message related status word. */
    pMsgDescCde->pInfoTransmission->stsTransmission |= cap_stsTransm_errTimeout;

} /* End of onMessageInTimeout */



/**
 * The initialization callback for all received messages. Timers are created that implement
 * the timming supervision.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onInitReceivedMessages(const ede_callbackContext_t *pContext)
{
    /* Double-check the intended use case of this callback. This callback must be used only
       for the initialization of inbound messages. It is shared between all dispatchers. */
    assert(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_EXT_INIT
           &&  isInboundTransmission(pContext)
          );

    /* No particular timing supervision is implemented yet. We just redirect to the later
       implementation. */
#ifdef DEBUG
    ede_callback_t callbackSoFar =
#endif
    ede_installCallback(pContext, onMessageReception);
    assert(callbackSoFar == onInitReceivedMessages);

    /* Get the CDE index of the message, which is the index into the CDE data tables at the
       same time. This has been ensured by the message registration process. */
    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);
    assert(pMsgDescCde->pInfoTransmission->stsTransmission == cap_stsTransm_neverReceived);

    /* All but pure event messages get a timeout counter. The handle needs to be accessible
       since the timer requires retriggering on reception. We use handler context data,
       which can be implemented by direct array lookup using the information in the
       auto-coded CDE data tables. */
    if(pMsgDescCde->sendMode != cap_enumSendMode_event)
    {
        unsigned int idxHandlerCtxData;
        if(pMsgDescCde->sendMode == cap_enumSendMode_regular)
            idxHandlerCtxData = pMsgDescCde->idxHandlerCtxData;
        else
        {
            assert(pMsgDescCde->sendMode == cap_enumSendMode_mixed);

            /* Both transmission patterns share the same handler context data. The entries
               for mode mixed are placed behind those of mode regular. */
            idxHandlerCtxData = pMsgDescCde->idxHandlerCtxData
                                + CST_NO_CAN_FRAMES_RECEIVED_REGULAR;
        }

        assert(idxHandlerCtxData < sizeOfAry(_hTimerInTimeoutAry)
               &&  _hTimerInTimeoutAry[idxHandlerCtxData] == EDE_INVALID_TIMER_HANDLE
              );
        _hTimerInTimeoutAry[idxHandlerCtxData] =
            ede_createSingleShotTimer( pContext
                                     , /* tiFromNow */ TIMEOUT(pMsgDescCde->tiCycle)
                                     , /* callback */ onMessageInTimeout
                                     , /* refUserContextData */ 0
                                     , /* killAtDueTime */ false
                                     );
        assert(_hTimerInTimeoutAry[idxHandlerCtxData] != EDE_INVALID_TIMER_HANDLE);

    } /* if(Do we require a timeout timer for the given transmission pattern?) */

} /* End of onInitReceivedMessages */



/**
 * Common code for sending messages of different transmission modes: E2E protect the data
 * found in the global CAN API of a given message and submit this message at the operating
 * system for sending.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in, which in turn calls this
 * function.
 *   @remark
 * The implementation of this callback needs to be reentrant. It can be called coincidently
 * from different dispatchers clocked in different threads.
 */
static void protectAndSendMessage(const ede_callbackContext_t * const pContext)
{
    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);
    assert(!pMsgDescCde->isReceived);

    /* Do the E2E protection of the APSW computed values in the global CAN interface:
       Compute the checksum - if there is any. */
    if(pMsgDescCde->fctProtectApiFrame != NULL)
        pMsgDescCde->fctProtectApiFrame();

    /* Pack the message. */
    uint8_t messageContent[pMsgDescCde->size];
    pMsgDescCde->fctPackApiFrame(&messageContent[0]);

#if 0
    /* Self test of test application: This should lead to a reported E2E validation error
       after a while. */
    if(BOOL_RAND(1e-3 / CST_NO_CAN_FRAMES_SENT))
    {
        LOG_ERROR( sup_hGlobalLogger
                 , "%lu ms: "
                   "%s: Inject error in message %u%s on bus %u"
                 , ose_tiSim, __func__
                 , pMsgDescCde->canId.id
                 , pMsgDescCde->canId.isExtId? "x": ""
                 , pMsgDescCde->idxCanBus
                 );
        assert(pMsgDescCde->DLC > 0);
        ++ messageContent[pMsgDescCde->DLC-1];
    }
#endif

    const unsigned int idxConnectionPoint = asw_getAssociatedTaskOfMessage(pMsgDescCde) == 10
                                            ? APT_IDX_DISPATCHER_10MS
                                            : APT_IDX_DISPATCHER_100MS;

    /* Invoke the operating system API to submit the message for sending.
         The OS handle of the message is the index in the OSE owned configuration table. The
       mapping from module cdt's data table index to OS handle is a simple offset
       operation. This is a simple and efficient descision, which has been taken in the
       call of the registration method. */
    const unsigned int hOsMessage = pMsgDescCde-&cdt_canFrameAry[CST_NO_CAN_FRAMES_RECEIVED];
    assert(pMsgDescCde->pInfoTransmission != NULL);
    if(ose_sendCanMessage( idxConnectionPoint
                         , hOsMessage
                         , &messageContent[0]
                         , pMsgDescCde->size
                         )
      )
    {
        /* Reset the error status if we were able to put the message into the send queue. */
        pMsgDescCde->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errSendBufferFull;

        /* The transmission event is only counted in case of success. This can be decided
           differently but it is consistent with the counting of received messages */
        ++ pMsgDescCde->pInfoTransmission->noTransmittedFrames;
    }
    else
    {
        /* Count the messages, which are lost due to queue full. */
        ++ apt_noEvTxSendBufFull;

        pMsgDescCde->pInfoTransmission->stsTransmission |= cap_stsTransm_errSendBufferFull;
        LOG_DEBUG( sup_hGlobalLogger
                 , "%lu ms: "
                   "%s: Failed to send message %u%s on bus %u"
                 , ose_tiSim, __func__
                 , pMsgDescCde->canId.id
                 , pMsgDescCde->canId.isExtId? "x": ""
                 , pMsgDescCde->idxCanBus
                 );
    }

    /* Count all messages, which should have been sent. */
    ++ apt_noTxMessages;

} /* End of protectAndSendMessage */



/**
 * Shared callback for the timers of all regular outbound messages. When the timer elapses
 * the message is due and needs to be submitted for sending.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 *   @remark
 * The implementation of this callback needs to be reentrant. It can be called coincidently
 * from different dispatchers clocked in different threads.
 */
static void onSendRegularMessage(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(!isInboundTransmission(pContext)
           &&  ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED
          );

    /* Sending a regular message is an unconditional, straight forward operation each time
       the callback fires. */
    protectAndSendMessage(pContext);

} /* End of onSendRegularMessage */



/**
 * Shared callback for the timers of all outbound event messages. When the timer elapses
 * the due conditions of the message need to be checked and the message needs to be submitted
 * for sending if it became \a true in the meantime.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onDueCheckEventMessage(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(!isInboundTransmission(pContext)
           &&  ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED
          );

    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);

    signed int tiNewFromNow;
    assert(pMsgDescCde->pInfoTransmission != NULL);
    if(pMsgDescCde->pInfoTransmission->isEvent)
    {
        /* APSW has signaled an event, acknowledge by resetting the flag and send the
           message. */
        pMsgDescCde->pInfoTransmission->isEvent = false;
        protectAndSendMessage(pContext);

        /* The time when the timer should fire the next time depends. We had an event in
           this tick, so we need to regard the minimum distance. */
        tiNewFromNow = (int)pMsgDescCde->tiMinDistance;
        assert(tiNewFromNow > 0);
    }
    else
    {
        /* The time when the timer should fire the next time depends. We had no event this
           time and will test the Boolean decision immediately again in the next tick. */
        tiNewFromNow = 1;
    }

    /* The time when the timer should fire the next time depends. Adjust now, when again to
       test the send condition. */
    ede_retriggerSingleShotTimer( pContext
                                , /* hTimer */ NULL /* this timer */
                                , tiNewFromNow
                                );
} /* End of onDueCheckEventMessage */



/**
 * Shared callback for the timers of all outbound messages of transmission timing pattern
 * "mixed". When the timer elapses the due conditions of the message need to be checked and
 * the message needs to be submitted for sending if it became \a true in the meantime.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onDueCheckMixedMessage(const ede_callbackContext_t *pContext)
{
    /* The OS handle of the message is the index in the OSE owned configuration table. This
       is a simple and efficient decision, which has been taken in the call of the
       registration method. */
    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);

    /* Double-check that this callback is called from an expected context. */
    assert(!isInboundTransmission(pContext)
           &&  ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED
           &&  pMsgDescCde->sendMode == cap_enumSendMode_mixed
          );

    /* Get access to the handler's context data related to the message under progress. */
    assert(pMsgDescCde->idxHandlerCtxData < sizeOfAry(_hdlCtxDataOutMixedAry));
    const ede_handleTimer_t
        hTimerDueCheck = _hdlCtxDataOutMixedAry[pMsgDescCde->idxHandlerCtxData].hTimerDueCheck,
        hTimerTimeout = _hdlCtxDataOutMixedAry[pMsgDescCde->idxHandlerCtxData].hTimerTimeout,
        hThis = ede_getHandleTimer(pContext);

    /* The message needs to be sent if there is a data change event from the APSW or if the
       timeout timer fired. */
    signed int tiNewFromNowDueCheck;
    assert(pMsgDescCde->pInfoTransmission != NULL);
    if(pMsgDescCde->pInfoTransmission->isEvent  ||  hThis == hTimerTimeout)
    {
        /* If APSW has signaled an event, acknowledge by resetting the flag and send the
           message. If it is a timeout, we can still reset the flag, there are no race
           conditions. */
        pMsgDescCde->pInfoTransmission->isEvent = false;
        protectAndSendMessage(pContext);

        /* The time when the due check should be done again depends. We had a sent event in
           this tick, so we need to regard the minimum distance.
             The timeout timer is retriggered. */
        tiNewFromNowDueCheck = (int)pMsgDescCde->tiMinDistance;
        assert(tiNewFromNowDueCheck > 0  &&  (int)pMsgDescCde->tiCycle > 0);
        ede_retriggerSingleShotTimer( pContext
                                    , hTimerTimeout
                                    , /* tiNewFromNow */ (int)pMsgDescCde->tiCycle
                                    );
    }
    else
    {
        /* The time when the due check should be done again depends. We had no event this
           time and will test the Boolean decision immediately again in the next tick.
             The timeout timer must continue to run without retrigger. */
        tiNewFromNowDueCheck = 1;
    }

    /* The time when the timer should fire the next time depends. Adjust now, when again to
       test the send condition. */
    ede_retriggerSingleShotTimer(pContext, hTimerDueCheck, tiNewFromNowDueCheck);

} /* End of onDueCheckMixedMessage */



/**
 * The initialization callback for registered messages. An appropriate set of timers is
 * created, which will later trigger all messages at their individual due times.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onInitSentMessages(const ede_callbackContext_t *pContext)
{
    /* Double-check the intended use case of this callback. This callback must be used only
       for the initialization of outbound messages. It is shared between all dispatchers. */
    assert(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_INT_INIT
           &&  !isInboundTransmission(pContext)
          );

    /* This callback is shared between all outbound messages. Get access to the
       specification entry of the currently processed message. */
    const cdt_canFrame_t * const pMsgDescCde = getMsgDescription(pContext);

    switch(pMsgDescCde->sendMode)
    {
        case cap_enumSendMode_regular:
        {
            /* Regular messages are most simple. We apply a regular timer. */
            assert((int)pMsgDescCde->tiCycle > 0);
#ifdef DEBUG
            ede_handleTimer_t hTimer =
#endif
            ede_createPeriodicTimer( pContext
                                   , /* tiPeriod */ (int)pMsgDescCde->tiCycle
                                   , /* callback */ onSendRegularMessage
                                   , /* refUserContextData */ 0
                                   );
            assert(hTimer != EDE_INVALID_TIMER_HANDLE);
            break;
        }
        case cap_enumSendMode_event:
        {
            /* Event messages can become due in every tic. We set a timer of minimum elapse
               time and will check the send condition in the callback. The repetition of
               the timer depends; if it comes to sending then the next check is not
               immediately but after the minimum distance time. Therefore we don't use a
               regular timer to trigger the due check regularly but take a single shot timer,
               which can be reprogrammed at every callback. */
#ifdef DEBUG
            ede_handleTimer_t hTimer =
#endif
            ede_createSingleShotTimer( pContext
                                     , /* tiFromNow */ 1
                                     , /* callback */ onDueCheckEventMessage
                                     , /* refUserContextData */ 0
                                     , /* killAtDueTime */ false
                                     );
            assert(hTimer != EDE_INVALID_TIMER_HANDLE);
            break;
        }
        case cap_enumSendMode_mixed:
        {
            /* Event messages with fallback can become due in every tic. We set a timer of
               minimum elapse time and will check the send condition in the callback. The
               repetition of the timer depends; if it comes to sending then the next check
               is not immediately but after the minimum distance time. Therefore we don't
               use a regular timer to trigger the due check regularly but take a single
               shot timer, which can be reprogrammed at every callback.
                 A second timer is required to guarantee the fallback trigger if no event
               occurs. */
            const unsigned int idxCtxData = pMsgDescCde->idxHandlerCtxData;
            assert(idxCtxData < sizeOfAry(_hdlCtxDataOutMixedAry)
                   &&  _hdlCtxDataOutMixedAry[idxCtxData].hTimerDueCheck
                       == EDE_INVALID_TIMER_HANDLE
                   &&  _hdlCtxDataOutMixedAry[idxCtxData].hTimerTimeout
                       == EDE_INVALID_TIMER_HANDLE
                  );

            _hdlCtxDataOutMixedAry[idxCtxData].hTimerDueCheck =
            ede_createSingleShotTimer( pContext
                                     , /* tiPeriod */ 1
                                     , /* callback */ onDueCheckMixedMessage
                                     , /* refUserContextData */ 0
                                     , /* killAtDueTime */ false
                                     );
            assert(_hdlCtxDataOutMixedAry[idxCtxData].hTimerDueCheck
                   != EDE_INVALID_TIMER_HANDLE
                  );

            assert((int)pMsgDescCde->tiCycle > 0);
            _hdlCtxDataOutMixedAry[idxCtxData].hTimerTimeout =
            ede_createSingleShotTimer( pContext
                                     , /* tiPeriod */ (int)pMsgDescCde->tiCycle
                                     , /* callback */ onDueCheckMixedMessage
                                     , /* refUserContextData */ 0
                                     , /* killAtDueTime */ false
                                     );
            assert(_hdlCtxDataOutMixedAry[idxCtxData].hTimerTimeout
                   != EDE_INVALID_TIMER_HANDLE
                  );

            break;
        }
        default:
            assert(false);

    } /* switch(Transmission pattern of message) */

} /* End of onInitSentMessages */




/**
 * The application owned part of the CAN reception interrupt, or the CAN reception
 * callback. In each integration, this callback will be used to feed received CAN messages
 * into the input queue of the appropriate dispatcher for (later) processing.\n
 *   This callback will always be executed in the interrupt CPU context. The later
 * processing of the message is done by the dispatcher in the context it has been started in
 * (i.e. the calling context of ede_dispatcherMain()). This is a normal application task
 * context, ideally the only task, which requires access to the message's contents. If so, no
 * further attention has to be drawn to inter-task communication and data exchange.\n
 *   In our operating system emulation this callback is invoked in the context of a
 * different thread, which makes no particular difference to the interrupt context on a
 * typical embedded platform.
 *   @param idxMessageOs
 * A typical callback will pass some handle of the received CAN message. This handle has
 * mostly been agreed on between APSW and BSW during the system initialization. In our
 * emulated operation system the received messages are specified by the APSW in form of an
 * initialized, constant data table. The index into this configuration table naturally is
 * the handle, which the operating system responds with when it comes to a reception event.
 *   @param pMsgContent
 * The received bytes are typically passed in as a pointer to a byte array.
 *   @param DLC
 * Any real existing platform will report the number of actually received bytes.
 */

void apt_irqHandlerRxCan( unsigned int idxMessageOs
                        , const unsigned char *pMsgContent
                        , unsigned int DLC
                        )
{
    /* Note, this is a callback from the operating system and not a dispatcher callback.
       The EDE API is not available here to access message properties. */

    /* The OS handle of the message is specified to be the index into the configuration
       table. This gives us access to the message properties. */
    assert(idxMessageOs < ose_noReceivedCanFrames);
    const ose_receivedCanFrame_t * const pMsgDesc = &ose_receivedCanFrameAry[idxMessageOs];

    LOG_DEBUG( sup_hGlobalLogger
             , "%lu ms: "
               "apt_irqHandlerRxCan: Message %lu received (ID: %lu%s, %u Byte)"
             , ose_tiSim
             , idxMessageOs
             , pMsgDesc->canId
             , pMsgDesc->isExtId? "x": ""
             , (unsigned)DLC
             );

    /* Having the CAN interface handle of the received message, we can post a message received
       event to the dispatcher. If no internal mapping is configured then the bus index
       specified here doesn't care and the parameter osHandle is taken as CDE index. */
    const boolean_t success = ede_postEvent( _hOsEventSender
                                           , /* kindOfEvent */ apt_evt_newRxMsg
                                           , /* senderHandleEvent */ idxMessageOs
                                           , /* pData */ pMsgContent
                                           , /* sizeOfData */ DLC
                                           );
    if(!success)
    {
        /* Count all received messages, which are lost because of queue full. */
        ++ apt_noEvRxQueueFull;

        LOG_DEBUG( sup_hGlobalLogger
                 , "%lu ms: "
                   "apt_irqHandlerRxCan: "
                   "Dispatcher queue full, can't post received event for message"
                   " with handle %lu (OS) (ID: %lu%s, %u Byte)"
                 , ose_tiSim
                 , idxMessageOs
                 , pMsgDesc->canId
                 , pMsgDesc->isExtId? "x": ""
                 , (unsigned)DLC
                 );
    }

    /* Count all received messages. */
    ++ apt_noRxMessages;

} /* End of apt_irqHandlerRxCan */



/**
 * The initialization task. Such a task is found in any RTOS environment. Usually it is
 * called at a time when no parallel thread execution is done yet, so no race conditions
 * exist with other parts of the code and safe build-up of all required data structure can
 * be done prior to the start of the real task scheduling.\n
 *   We use this function to initialize the CAN interface.
 */

static rtos_taskFctResult_t apt_taskInit()
{
    bool initOk ATTRIB_DBG_ONLY;

    /* Initialize the global data of this module. */
    unsigned int u;
    for(u=0; u<sizeOfAry(_hTimerInTimeoutAry); ++u)
        _hTimerInTimeoutAry[u] = EDE_INVALID_TIMER_HANDLE;
    for(u=0; u<sizeOfAry(_hdlCtxDataOutMixedAry); ++u)
    {
        _hdlCtxDataOutMixedAry[u].hTimerDueCheck = EDE_INVALID_TIMER_HANDLE;
        _hdlCtxDataOutMixedAry[u].hTimerTimeout = EDE_INVALID_TIMER_HANDLE;
    }

    /* Even if it is entirely useless in the given Windows environment: We demonstrate the
       use of distinct memory pools for sending events (by simulated OS) and for receiving
       events (by APSW). */
    static char heapMemoryOS[APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    static char heapMemoryAPSW[APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    initOk = mem_createMemoryPool( &apt_memoryPoolOS
                                 , /* pPoolMemory */ heapMemoryOS
                                 , /* sizeOfPoolMemory */ sizeof(heapMemoryOS)
                                 , MEM_VOID_CRITICAL_SECTION_OBJECT
                                 );
    assert(initOk);
    initOk = mem_createMemoryPool( &apt_memoryPoolAPSW
                                 , /* pPoolMemory */ heapMemoryAPSW
                                 , /* sizeOfPoolMemory */ sizeof(heapMemoryAPSW)
                                 , MEM_VOID_CRITICAL_SECTION_OBJECT
                                 );
    assert(initOk);

    /* Create the required dispatcher systems. */
    initOk = ede_createDispatcherSystem
                        ( &_hDispatcherSystem
                        , APT_NO_DISPATCHERS
                        , /* maxNoEventSourcesExt */ CST_NO_CAN_FRAMES_RECEIVED
                        , /* maxNoEventSourcesInt */ CST_NO_CAN_FRAMES_SENT
                        , &apt_memoryPoolAPSW
                        );
    assert(initOk &&  _hDispatcherSystem != EDE_INVALID_DISPATCHER_SYSTEM_HANDLE);

    /* Create the required dispatcher queues. */
    ede_eventSenderPort_t portSender10ms;
    ede_eventReceiverPort_t portDispatcher10ms;
    initOk = vsq_createEventQueue
                        ( &portDispatcher10ms
                        , &portSender10ms
                        , /* maxQueueLength */ APT_DISPATCHER_10MS_QUEUE_LEN /* no msgs */
                        , /* sizeOfPayload */ 8u /* max DLC */
                        , /* pMemPoolDispatchingProcess */ &apt_memoryPoolAPSW
                        , /* pMemPoolSenderOfEvents */     &apt_memoryPoolOS
                        );
    assert(initOk);
    ede_eventSenderPort_t portSender100ms;
    ede_eventReceiverPort_t portDispatcher100ms;
    initOk = vsq_createEventQueue
                        ( &portDispatcher100ms
                        , &portSender100ms
                        , /* maxQueueLength */ APT_DISPATCHER_100MS_QUEUE_LEN /* no msgs */
                        , /* sizeOfPayload */ 8u /* max DLC */
                        , /* pMemPoolDispatchingProcess */ &apt_memoryPoolAPSW
                        , /* pMemPoolSenderOfEvents */     &apt_memoryPoolOS
                        );
    assert(initOk);

    /* Create the required dispatchers with their associated handle maps.
         Suitable handle maps: In this application, we see a nearly trivial handle mapping:
       The sender handles of CAN Rx events are the index into the global data tables with
       all message definitions. We register the messages in the order of these tables at a
       single dispatcher system - this will produce the basically same sequence of indexes,
       maybe with an offset due to other events previously registered (our bus events). We
       apply the pre-defined offset mapping, which comes along with the CAN interface.
         Our map knows the kinds of events:
         Rx: Sender handle is the index into cdt_canFrameAry[], but only the first
       CST_NO_CAN_FRAMES_RECEIVED entries are used, Rx messages are specified before Tx
       messages. */
    const bool isSenderHandleInUseAry[apt_evt_noKindsOfExternalEvents] =
    {
        [/* Kind of event */ apt_evt_newRxMsg] = true,
    };
    ede_mapSenderEvHandleToIdx_t handleMap;
    initOk = mpo_createMapOffsetOnly( &handleMap
                                    , apt_evt_noKindsOfExternalEvents
                                    , isSenderHandleInUseAry
                                    , &apt_memoryPoolAPSW
                                    );
    assert(initOk);
    initOk = ede_createDispatcher( _hDispatcherSystem
                                 , /* idxDispatcher */ APT_IDX_DISPATCHER_10MS
                                 , /* tiTick */ 10 /* ms */
                                 , /* portAry */ &portDispatcher10ms
                                 , /* noPorts */ 1u
                                 , /* mapSdrEvHdlToEdeEvSrcIdx */ handleMap
                                 );
    assert(initOk);
    initOk = ede_createDispatcher( _hDispatcherSystem
                                 , /* idxDispatcher */ APT_IDX_DISPATCHER_100MS
                                 , /* tiTick */ 100 /* ms */
                                 , /* portAry */ &portDispatcher100ms
                                 , /* noPorts */ 1u
                                 , /* mapSdrEvHdlToEdeEvSrcIdx */ handleMap
                                 );
    assert(initOk);

    /* Create the senders. We have one instance with two ports to serve the two
       dispatchers. */
    ede_eventSenderPort_t portAry[2u] =
    {
        [IDX_EVENT_QUEUE_RX_10MS]  = portSender10ms,
        [IDX_EVENT_QUEUE_RX_100MS] = portSender100ms,
    };
    ede_mapSenderEvHandleToIdx_t mapSdrEvHdlToEdePortIdx =
    {
        .addKeyValuePair = NULL,
        .getValue = mapSenderEvHandleToSenderPortIndex,
        .hInstance = 0u, /* doesn't care, we only have one implicit instance */
    };
    initOk = ede_createSender( &_hOsEventSender
                             , portAry
                             , /* noPorts */ 2u
                             , &mapSdrEvHdlToEdePortIdx
                             , &apt_memoryPoolOS
                             );
    assert(!initOk ||  _hOsEventSender != EDE_INVALID_SENDER_HANDLE);

    /* Register all messages at the dispatcher engines. */
    unsigned int hOsMessage, idxCdt;
    for(hOsMessage=0, idxCdt=0; idxCdt<CST_NO_CAN_FRAMES_RECEIVED; ++hOsMessage, ++idxCdt)
    {
        assert(idxCdt < sizeOfAry(cdt_canFrameAry)  && hOsMessage < ose_noReceivedCanFrames);
        const cdt_canFrame_t * const pMsgDescCde = &cdt_canFrameAry[idxCdt];

        /* The never received bit is initially set in the transmission status. All other
           status bits are cleared. */
        pMsgDescCde->pInfoTransmission->stsTransmission = cap_stsTransm_neverReceived;

        /* We have some redundancy since the OS CAN registration tables partly hold the
           same information about messages as our APSW owned data tables. We can put an
           assertion to double-check the strict synchronicity of both tables. */
        assert(pMsgDescCde->isReceived
               &&  ose_receivedCanFrameAry[hOsMessage].idxCanBus == pMsgDescCde->idxCanBus
               &&  CDT_CAN_ID( ose_receivedCanFrameAry[hOsMessage].canId
                             , ose_receivedCanFrameAry[hOsMessage].isExtId
                             ).uniqueCanId
                   == pMsgDescCde->canId.uniqueCanId
              );

        /* Choice of appropriate dispatcher: The slowest clocked reasonably possible
           dispatcher should be used to minimize computation overhead. We have a 10ms and a
           100ms clocked dispatcher. The messages are separated by their timing. Regular
           messages are rated by cycle time. Event triggered messages are rated by their
           minimum distance time, which is a measure for the expected latency of
           processing. */
        const unsigned int idxDispatcher =
                                    asw_getAssociatedTaskOfMessage(pMsgDescCde) == 10u
                                    ? APT_IDX_DISPATCHER_10MS
                                    : APT_IDX_DISPATCHER_100MS;
        assert(idxDispatcher == APT_IDX_DISPATCHER_10MS
               ||  asw_getAssociatedTaskOfMessage(pMsgDescCde) == /* tiTaskCycle */ 100u
              );
        ede_registerExternalEventSource( _hDispatcherSystem
                                       , idxDispatcher
                                       , /* kindOfEvent */ apt_evt_newRxMsg
                                       , /* senderHandleEvent */ hOsMessage
                                       , /* callback */ onInitReceivedMessages
                                       , /* refEventSourceData */ (uintptr_t)pMsgDescCde
                                       );
    } /* for(All inbound messages) */

    assert(idxCdt == CST_NO_CAN_FRAMES_RECEIVED);
    for(hOsMessage=0; idxCdt<CST_NO_CAN_FRAMES; ++hOsMessage, ++idxCdt)
    {
        assert(idxCdt < sizeOfAry(cdt_canFrameAry)  &&  hOsMessage < ose_noSentCanFrames);
        const cdt_canFrame_t * const pMsgDescCde = &cdt_canFrameAry[idxCdt];

        /* We have some redundancy since the OS CAN registration tables partly hold the
           same information about messages as our APSW owned data tables. We can put an
           assertion to double-check the strict synchronicity of both tables. */
        assert(!pMsgDescCde->isReceived
               &&  ose_sentCanFrameAry[hOsMessage].idxCanBus == pMsgDescCde->idxCanBus
               &&  CDT_CAN_ID( ose_sentCanFrameAry[hOsMessage].canId
                             , ose_sentCanFrameAry[hOsMessage].isExtId
                             ).uniqueCanId
                   == pMsgDescCde->canId.uniqueCanId
              );

        /* Choice of appropriate dispatcher: The slowest clocked reasonably possible
           dispatcher should be used to minimize computation overhead. We have a 10ms and a
           100ms clocked dispatcher. The messages are separated by their timing. Regular
           messages are rated by cycle time. Event triggered messages are rated by their
           minimum distance time, which is a measure for the expected latency of
           processing. */
        const unsigned int idxDispatcher =
                                    asw_getAssociatedTaskOfMessage(pMsgDescCde) == 10u
                                    ? APT_IDX_DISPATCHER_10MS
                                    : APT_IDX_DISPATCHER_100MS;
        assert(idxDispatcher == APT_IDX_DISPATCHER_10MS
               ||  asw_getAssociatedTaskOfMessage(pMsgDescCde) == /* tiTaskCycle */ 100u
              );
        ede_registerInternalEventSource( _hDispatcherSystem
                                       , idxDispatcher
                                       , /* callback */ onInitSentMessages
                                       , /* refEventSourceData */ (uintptr_t)pMsgDescCde
                                       );

        /* Double-check the condition, which is later applied to retrieve the OS message
           handle from the event source data. */
        assert(pMsgDescCde - &cdt_canFrameAry[CST_NO_CAN_FRAMES_RECEIVED] == hOsMessage);
        
    } /* for(All outbound messages) */

    /* Install the task functions and interrupt handlers. This step connects the generic
       operating system with this particular APSW.
         Note, this function apt_taskInit must not be connected, it had already been
       connected to the operating system through the global function pointer sup_initAPSW. */
    ose_installIrqHandlerCanRx(apt_irqHandlerRxCan);
    ose_installTask(ose_taskType_regular10ms, apt_task10ms);
    ose_installTask(ose_taskType_regular100ms, apt_task100ms);
    ose_installTask(ose_taskType_shutdown, apt_taskShutdown);

    return rtos_taskFctResult_continueScheduling;

} /* End of apt_taskInit */




/**
 * Demo code of the regularly executed 10ms task of the APSW. The engine of the CAN
 * interface is clocked and the decoded and pre-processed CAN information can be consumed
 * by the APSW. Vice versa, the APSW provided functional results are encoded and timely
 * sent by the engine. All data access can be done easy and directly since no race
 * conditions occur.
 */

static rtos_taskFctResult_t apt_task10ms()
{
    LOG_DEBUG( sup_hGlobalLogger
             , "%lu ms: "
               "apt_task10ms: Invoked by OS"
             , ose_tiSim
             );

    /* Call the step function of the CAN interface engine for this task. */
    ede_dispatcherMain(_hDispatcherSystem, APT_IDX_DISPATCHER_10MS);

    /* Call the step function of the APSW, which computes new CAN output values. */
    asw_taskApsw_10ms();

    return rtos_taskFctResult_continueScheduling;

} /* End of apt_task10ms */




/**
 * Demo code of the regularly executed 100ms task of the APSW. The engine of the CAN
 * interface is clocked and the decoded and pre-processed CAN information can be consumed
 * by the APSW. Vice versa, the APSW provided functional results are encoded and timely
 * sent by the engine. All data access can be done easy and directly since no race
 * conditions occur.
 */

static rtos_taskFctResult_t apt_task100ms()
{
    LOG_DEBUG( sup_hGlobalLogger
             , "%lu ms: "
               "apt_task100ms: Invoked by OS"
             , ose_tiSim
             );

    /* Call the step function of the CAN interface engine for this task. */
    ede_dispatcherMain(_hDispatcherSystem, APT_IDX_DISPATCHER_100MS);

    /* Call the step function of the APSW, which computes new CAN output values. */
    asw_taskApsw_100ms();

    return rtos_taskFctResult_continueScheduling;

} /* End of apt_task100ms */




/**
 * The shutdown task of this simulation environment. It is used for diagnostic purpose only.
 */

static rtos_taskFctResult_t apt_taskShutdown()
{
#ifdef DEBUG
    /* Double-check corect use of handler context data array. */
    unsigned int u;
    for(u=0; u<sizeOfAry(_hTimerInTimeoutAry); ++u)
        assert(_hTimerInTimeoutAry[u] != EDE_INVALID_TIMER_HANDLE);
    for(u=0; u<sizeOfAry(_hdlCtxDataOutMixedAry); ++u)
    {
        assert(_hdlCtxDataOutMixedAry[u].hTimerDueCheck != EDE_INVALID_TIMER_HANDLE
               &&  _hdlCtxDataOutMixedAry[u].hTimerTimeout != EDE_INVALID_TIMER_HANDLE
              );
    }
#endif

    unsigned int noEvQFull10ms = ede_getNoSenderPortBlockedEvents( _hOsEventSender
                                                                 , IDX_EVENT_QUEUE_RX_10MS
                                                                 )
               , noEvQFull100ms = ede_getNoSenderPortBlockedEvents( _hOsEventSender
                                                                  , IDX_EVENT_QUEUE_RX_100MS
                                                                  );
    LOG_LOG( sup_hGlobalLogger
           , noEvQFull10ms>0 || noEvQFull100ms>0? log_warn: log_info
           , "%lu ms: "
             "apt_taskShutdown: "
             "Number of queue full events: %u (10ms task),  %u (100ms task)"
           , ose_tiSim
           , noEvQFull10ms, noEvQFull100ms
           );
#if MEM_DIAGNOSTIC_INTERFACE == 1
    LOG_INFO( sup_hGlobalLogger
            , "%lu ms: "
              "apt_taskShutdown: "
              "Consumed memory of CAN heap OS: %u Byte, remaining heap memory:"
              " %u Byte"
            , ose_tiSim
            , apt_memoryPoolOS.getNbrOfAllocatedBytes(apt_memoryPoolOS.hInstance)
            , apt_memoryPoolOS.getNbrOfAvailableBytes(apt_memoryPoolOS.hInstance)
            );
    if(apt_memoryPoolOS.getNbrOfAllocatedBytes(apt_memoryPoolOS.hInstance)
       < APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE
      )
    {
        LOG_WARN( sup_hGlobalLogger
                , "%lu ms: "
                  "apt_taskShutdown: "
                  "Size of CAN heap OS could be decreased by %u Byte"
                , ose_tiSim
                , APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE
                  - apt_memoryPoolOS.getNbrOfAllocatedBytes(apt_memoryPoolOS.hInstance)
                );
    }
    LOG_INFO( sup_hGlobalLogger
            , "%lu ms: "
              "apt_taskShutdown: "
              "Consumed memory of CAN heap APSW: %u Byte, remaining heap memory:"
              " %u Byte"
            , ose_tiSim
            , apt_memoryPoolAPSW.getNbrOfAllocatedBytes(apt_memoryPoolAPSW.hInstance)
            , apt_memoryPoolAPSW.getNbrOfAvailableBytes(apt_memoryPoolAPSW.hInstance)
            );
    if(apt_memoryPoolAPSW.getNbrOfAllocatedBytes(apt_memoryPoolAPSW.hInstance)
       < APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE
      )
    {
        LOG_WARN( sup_hGlobalLogger
                , "%lu ms: "
                  "apt_taskShutdown: "
                  "Size of CAN heap APSW could be decreased by %u Byte"
                , ose_tiSim
                , APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE
                  - apt_memoryPoolAPSW.getNbrOfAllocatedBytes(apt_memoryPoolAPSW.hInstance)
                );
    }
#else
    LOG_INFO( sup_hGlobalLogger
            , "%lu ms: "
              "apt_taskShutdown: "
              "No diagnostic API for module mem_malloc available. No information about"
              " heap size and usage can be given"
            , ose_tiSim
            );
#endif /* MEM_DIAGNOSTIC_INTERFACE == 1 */

    return rtos_taskFctResult_continueScheduling;

} /* End of apt_taskShutdown */




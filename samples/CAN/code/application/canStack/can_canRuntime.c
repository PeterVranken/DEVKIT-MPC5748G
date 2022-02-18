/**
 * @file can_canRuntime.c
 * The hand-made, not generated source file contains the implementation of the callbacks
 * from the CAN interface engine. These callbacks don't depend on the CAN database (*.dbc)
 * and don't need to be generated from the database. It is set up once for the project. The
 * implementation is widely based on sample
 * https://vranken@svn.code.sf.net/p/comframe/code/canInterface/branches/devR16/sampleIntegrations/winTestMT/,
 * revision 414.\n
 *   Note, in a certain sense, the implementation of this file does well depend on the CAN
 * database. The implementation of the callbacks determines, which send and receive
 * patterns are supported. For example, regular transmission versus event-based
 * transmission. Or simply the definition, what event-based transmission actually means. Or
 * the way how to protect or encrypt the message payloads. All of the imaginable options
 * may by selected under control of attributes in the CAN database and this file would need
 * to implement all options, which are available for a given database. The provided
 * implementation only supports a few, basic patterns in order to be compatible with most
 * database files.\n
 *   Using the callbacks implemented here, the CAN interface engine updates all signal
 * values and message status in the global CAN API and sends due messages, filled with
 * information read from this API.
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
 *   bsw_onRxCan
 *   can_initCanStack
 * Local functions
 *   onMsgReception
 *   onMsgInTimeout
 *   onInitReceivedMsgs
 *   protectAndSendMsg
 *   onSendRegularMsg
 *   onDueCheckEventMsg
 *   onDueCheckMixedMsg
 *   onInitSendMsgs
 */


/*
 * Include files
 */

#include "can_canRuntime.h"

#include <assert.h>

#include "typ_types.h"
#include "cap_canApi.h"
#include "cdr_canDriverAPI.h"
#include "mem_malloc.h"
#include "vsq_dispatcherPortInterface.h"
#include "ede_eventSender.h"
#include "mpo_mapOffsetOnly.h"
#include "ede_eventDispatcherEngine.h"
#include "cst_canStatistics.h"
#include "cdt_canDataTables.h"
#include "cmd_canCommand.h"


/*
 * Defines
 */

/** This macro is a primitive way to define the timeout span for received messages. It maps
    the nominal maximum time span between two reception events onto the time span after
    which the CAN interface should decide on timeout. The latter time span needs to be
    greater than the former: CAN bus timing always requires a tolerance and the time
    measurement is done only with the resolution of the tick of the CAN interface engine. */
#define TIMEOUT(tiCycle) (assert((int)(3*(tiCycle)+1)>0),((signed int)(3*(tiCycle)+1)))

/** Our data tables with message decriptions are separated in Rx and Tx messages. The interface
    engine has one solid handle space for all messages. This macro computes the array index of
    a received message from the handle used by the engine. The returned index relates to array
    \a cdt_canRxMsgAry. */
#define MAP_HANDLE_RX_MSG_CAN_IF_TO_IDX_RX(idxFrCde)                                      \
            (assert((idxFrCde) < sizeOfAry(cdt_canRxMsgAry)),(idxFrCde))

/** Our data tables with message decriptions are separated in Rx and Tx messages. The interface
    engine has one solid handle space for all messages. This macro computes the array index of
    a sent message from the handle used by the engine. The returned index relates to array \a
    cdt_canTxMsgAry. */
#define MAP_HANDLE_TX_MSG_CAN_IF_TO_IDX_TX(idxFrCde)                                      \
            (assert((idxFrCde)-(CST_NO_CAN_MSGS_RECEIVED) < sizeOfAry(cdt_canTxMsgAry)),\
             (idxFrCde)-(CST_NO_CAN_MSGS_RECEIVED)                                        \
            )


/* Check the number of processed messages against the HW constraints. Note, the condition
   is necessary but not sufficient; a bad distrubution of messages between user and safety
   process cann still foil successful initialization of the CAN stack. */
_Static_assert( CST_NO_CAN_MSGS_RECEIVED_PT
                <= (BSW_IDX_LAST_RX_MAILBOX-BSW_IDX_FIRST_RX_MAILBOX+1)
                   + (BSW_IDX_LAST_RX_MAILBOX_SAFETY-BSW_IDX_FIRST_RX_MAILBOX_SAFETY+1u)
                &&  CST_NO_CAN_MSGS_SENT_PT
                    <= (BSW_IDX_LAST_TX_MAILBOX-BSW_IDX_FIRST_TX_MAILBOX+1)
                       + (BSW_IDX_LAST_TX_MAILBOX_SAFETY-BSW_IDX_FIRST_TX_MAILBOX_SAFETY+1u)
              , "The number of processed messages exceeds the given hardware capabilities"
              );

/*
 * Local type definitions
 */

/** Type of context data for the handler for outbound mixed mode messages. */
typedef struct hdlCtxDataOutMixed_t
{
    /** The handle of the due check timer. */
    ede_handleTimer_t hTimerDueCheck;

    /** The handle of the timeout timer. */
    ede_handleTimer_t hTimerTimeout;

} hdlCtxDataOutMixed_t;

/** The known kinds of event. The use of the pre-defined handle maps require a gapless,
    zero based sequence of enumeration values. Here for Rx event queues. */
typedef enum can_kindOfExtEvents_t
{
    /*
     * External events should come first such that they get the zero based index space;
     * this facilitates the implementation of the required handle maps.
     */
     
    /** The kind-of-event for a CAN message reception event on bus 0. */
    can_evt_newRxMsg_bus0,

    /** The kind-of-event for a CAN message reception event on bus 1. */
    can_evt_newRxMsg_bus1,

    /** The kind-of-event for a CAN message reception event on bus 2. */
    can_evt_newRxMsg_bus2,

    /** The kind-of-event for a CAN message reception event on bus 3. */
    can_evt_newRxMsg_bus3,

    /** The total number of different kinds of external events, i.e.,events, which come
        from a sender object and via a queue object to the dispatcher. */
    can_evt_noKindsOfExternalEvents,
    
    /** The total number of different kinds of external events. */
    can_evt_noKindsOfExtEvents,
    
} can_kindOfExtEvents_t;

_Static_assert( can_evt_newRxMsg_bus1 == can_evt_newRxMsg_bus0 + 1
                &&  can_evt_newRxMsg_bus2 == can_evt_newRxMsg_bus0 + 2
                &&  can_evt_newRxMsg_bus3 == can_evt_newRxMsg_bus0 + 3
              , "All bus related Rx events are expected to form a gapless sequence"
              );

/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** The system, which owns the dispatcher engines processing the CAN events in the 10ms and
    in the 100ms APSW tasks. */
ede_handleDispatcherSystem_t SDATA_P1(can_hDispatcherSystem) = EDE_INVALID_DISPATCHER_SYSTEM_HANDLE;

/** The sender of CAN events. It is connected to both dispatchers. */
static ede_handleSender_t SDATA_P1(_hEventSender) = EDE_INVALID_SENDER_HANDLE;

/** The handler for inbound messages requires local context data for regular and mixed mode
    messages. Here's an array of context data objects, one for each such message; the entries
    for regular messages precede those for mixed mode messages. */
static ede_handleTimer_t BSS_P1(_hTimerInTimeoutAry)[CST_NO_CAN_MSGS_RECEIVED_REGULAR
                                                     + CST_NO_CAN_MSGS_RECEIVED_MIXED
                                                    ];

/** The handler for outbound mixed mode messages requires local context data. Here's an array
    of context data objects, one for each such message. */
static hdlCtxDataOutMixed_t BSS_P1(_hdlCtxDataOutMixedAry)[CST_NO_CAN_MSGS_SENT_MIXED];


/** The total count of all ever received messages, including the lost one because of queue
    full events. The counter is not saturated and will wrap at the implementation limit.
    This public interface can be read by any context on any core at any time. */
volatile unsigned long UNCACHED_P1(can_noRxMsgs) = 0;

/** The total number of sent messages, including the lost one because of send buffer full
    events. The counter is not saturated and will wrap at the implementation limit. This
    public interface can be read by any context on any core at any time.*/
volatile unsigned long UNCACHED_P1(can_noTxMsgs) = 0;

/** The total number of Rx timeout events. This public interface can be read by any context
    on any core at any time. */
volatile unsigned long UNCACHED_P1(can_noEvRxTimeout) = 0;

/** The total number of lost Rx messages because of queue full. This public interface can be
    read by any context on any core at any time. */
volatile unsigned long UNCACHED_P1(can_noEvRxQueueFull) = 0;

/** The total number of lost Tx messages because of send buffer full events. This public
    interface can be read by any context on any core at any time. */
volatile unsigned long UNCACHED_P1(can_noEvTxSendBufFull) = 0;


/*
 * Function implementation
 */

/**
 * Temporary solution for reception callback: No timing supervision, just E2E validation.
 */
static void onMsgReception(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(ede_getKindOfEvent(pContext) >= (unsigned)can_evt_newRxMsg_bus0
           &&  ede_getKindOfEvent(pContext) <= (unsigned)can_evt_newRxMsg_bus3
          );

    /* Get the CDE index of the message, which is the index into the CDE data tables at the
       same time. This has been ensured by the message registration process. */
    const unsigned int idxRxFr = ede_getIdxExternalEventSource(pContext);
    const cdt_canMessage_t *const pRxFrDesc = &cdt_canRxMsgAry[idxRxFr];

    /* Test: Do some consistency tests. */
    assert(pRxFrDesc->pInfoTransmission != NULL);

    /* Reset the never received bit in the transmission status. */
    pRxFrDesc->pInfoTransmission->stsTransmission &= ~cap_stsTransm_neverReceived;

    /* Some transmission pattern have a timeout supervision. Retrigger the timer and clear
       a possibly set timeout error bit. */
    if(pRxFrDesc->sendMode != CAN_ENUM_SEND_MODE_EVENT)
    {
        unsigned int idxHandlerCtxData;
        if(pRxFrDesc->sendMode == CAN_ENUM_SEND_MODE_REGULAR)
            idxHandlerCtxData = pRxFrDesc->idxHandlerCtxData;
        else
        {
            assert(pRxFrDesc->sendMode == CAN_ENUM_SEND_MODE_MIXED);

            /* Both transmission patterns share the same handler context data. The entries
               for mode mixed are placed behind those of mode regular. */
            idxHandlerCtxData = pRxFrDesc->idxHandlerCtxData
                                + CST_NO_CAN_MSGS_RECEIVED_REGULAR;
        }

        assert(idxHandlerCtxData < sizeOfAry(_hTimerInTimeoutAry)
               &&  _hTimerInTimeoutAry[idxHandlerCtxData] != EDE_INVALID_TIMER_HANDLE
              );
        ede_retriggerSingleShotTimer( pContext
                                    , _hTimerInTimeoutAry[idxHandlerCtxData]
                                    , /* tiNewFromNow */ TIMEOUT(pRxFrDesc->tiCycle)
                                    );

        /* Reset the timeout error in the message related status word. */
        pRxFrDesc->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errTimeout;

    } /* if(Do we have a timeout timer for the given transmission pattern?) */

    /* For event kind CST_EV_MSG_RECEPTION the event's data is the message contents. */
    unsigned int sizeOfEvData;
    const uint8_t *msgContents = ede_getEventData(pContext, &sizeOfEvData);
    assert(sizeOfEvData <= 8);

/// @todo E2E has not been adopted from the original sample code
//    /* Run the message specific E2E protection method. By side effect, and only on success,
//       the data is written into the global API at the same time. (Where nobody will ever
//       look for it in this test.) */
//    const boolean_t e2eOkay = pRxFrDesc->fctUnpackApiMsgAndValidate(msgContents);
    const bool e2eOkay = true;

    /* Run the message decomposition. The signal data is written into the global API. */
    pRxFrDesc->fctUnpackApiMsg(msgContents);

    /* Indicate the E2E validation result to the APSW. */
    if(e2eOkay)
    {
        pRxFrDesc->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errChecksum;

        /* The reception event is only counted in case of valid data. Otherwise the global
           CAN API has not been updated with new signal values and no reception event must
           be notified. */
        ++ pRxFrDesc->pInfoTransmission->noTransmittedMsgs;

        /* This application makes use of a callback in order to be notified about any
           successful reception event. */
        cmd_onReceiveMessage(idxRxFr);
    }
    else
    {
        /* Globally count the recognized failures. */
        /// @todo see above ++ can_noEvRxE2eFailure;

        /* Report the failure. */
        pRxFrDesc->pInfoTransmission->stsTransmission |= cap_stsTransm_errChecksum;
    }

} /* End of onMsgReception */



/**
 * Timer callback for all inbound messages, which a timeout is defined for. The timer is
 * retriggered on each message reception event and if it eventually fires then it is a
 * timeout event for the related message.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onMsgInTimeout(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* Get the CDE index of the message, which is the index into the CDE data tables at the
       same time. This has been ensured by the message registration process. */
    const unsigned int idxRxFr = ede_getIdxExternalEventSource(pContext);
    const cdt_canMessage_t *const pRxFrDesc = &cdt_canRxMsgAry[idxRxFr];

    /* Test: Do some consistency tests. */
    assert(pRxFrDesc->sendMode != CAN_ENUM_SEND_MODE_EVENT 
           &&  pRxFrDesc->pInfoTransmission != NULL
          );

    /* Globally count all timeout events. */
    const unsigned long newVal = can_noEvRxTimeout + 1;
    if(newVal != 0)
        can_noEvRxTimeout = newVal;

    /* Set timeout error in message related status word. */
    pRxFrDesc->pInfoTransmission->stsTransmission |= cap_stsTransm_errTimeout;

} /* End of onMsgInTimeout */



/**
 * The initialization callback for all received messages. Timers are created that implement
 * the timming supervision.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onInitReceivedMsgs(const ede_callbackContext_t *pContext)
{
    /* No particular timing supervision is implemented yet. We just redirect to the later
       implementation. */
#ifdef DEBUG
    ede_callback_t callbackSoFar =
#endif
    ede_installCallback(pContext, onMsgReception);
    assert(callbackSoFar == onInitReceivedMsgs);

    /* Get the CDE index of the message, which is the index into the CDE data tables at the
       same time. This has been ensured by the message registration process. */
    const unsigned int idxRxFr = ede_getIdxExternalEventSource(pContext);
    const cdt_canMessage_t *const pRxFrDesc = &cdt_canRxMsgAry[idxRxFr];
    assert(pRxFrDesc->pInfoTransmission->stsTransmission == cap_stsTransm_neverReceived);

    /* All but pure event messages get a timeout counter. The handle needs to be accessible
       since the timer requires retriggering on reception. We use handler context data,
       which can be implemented by direct array lookup using the information in the
       auto-coded CDE data tables. */
    if(pRxFrDesc->sendMode != CAN_ENUM_SEND_MODE_EVENT)
    {
        unsigned int idxHandlerCtxData;
        if(pRxFrDesc->sendMode == CAN_ENUM_SEND_MODE_REGULAR)
            idxHandlerCtxData = pRxFrDesc->idxHandlerCtxData;
        else
        {
            assert(pRxFrDesc->sendMode == CAN_ENUM_SEND_MODE_MIXED);

            /* Both transmission patterns share the same handler context data. The entries
               for mode mixed are placed behind those of mode regular. */
            idxHandlerCtxData = pRxFrDesc->idxHandlerCtxData
                                + CST_NO_CAN_MSGS_RECEIVED_REGULAR;
        }

        assert(idxHandlerCtxData < sizeOfAry(_hTimerInTimeoutAry)
               &&  _hTimerInTimeoutAry[idxHandlerCtxData] == EDE_INVALID_TIMER_HANDLE
              );
        _hTimerInTimeoutAry[idxHandlerCtxData] =
            ede_createSingleShotTimer( pContext
                                     , /* tiFromNow */ TIMEOUT(pRxFrDesc->tiCycle)
                                     , /* callback */ onMsgInTimeout
                                     , /* killAtDueTime */ false
                                     );
        assert(_hTimerInTimeoutAry[idxHandlerCtxData] != EDE_INVALID_TIMER_HANDLE);

    } /* if(Do we require a timeout timer for the given transmission pattern?) */

} /* End of onInitReceivedMsgs */



/**
 * Common code for sending messages of different transmission modes: E2E protect the data
 * found in the global CAN API of a given message and submit this message at the operating
 * system for sending.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in, which makes use of this
 * function.
 */
static void protectAndSendMsg(const ede_callbackContext_t * const pContext)
{
    const unsigned int idxTxFr = ede_getIdxInternalEventSource(pContext);
    const cdt_canMessage_t *pTxFrDesc = &cdt_canTxMsgAry[idxTxFr];

/// @todo E2E has not been adopted from the original sample code
//    /* Do the E2E protection of the APSW computed values in the global CAN interface:
//       Compute the checksum - if there is any. */
//    if(pTxFrDesc->fctProtectApiMsg != NULL)
//        pTxFrDesc->fctProtectApiMsg();

    /* Pack the message. */
    uint8_t msgContent[pTxFrDesc->size];
    pTxFrDesc->fctPackApiMsg(&msgContent[0]);

    /* The handle in the CAN driver of the message to send has been stored in the event
       source object at registration time. */
    const unsigned int hMsgBox = (unsigned)ede_getEventSourceData(pContext);
    assert(hMsgBox >= BSW_IDX_FIRST_TX_MAILBOX  &&  hMsgBox <= BSW_IDX_LAST_TX_MAILBOX);

    /* Invoke the operating system API to submit the message for sending. */
    assert(pTxFrDesc->pInfoTransmission != NULL);
    if(cdr_sendMessage(pTxFrDesc->idxCanBus, hMsgBox, &msgContent[0]) == cdr_errApi_noError)
    {
        /* Reset the error status if we were able to put the message into the mailbox. */
        pTxFrDesc->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errSendBufferFull;

        /* The transmission event is only counted in case of success. This can be decided
           differently but it is consistent with the counting of received messages */
        ++ pTxFrDesc->pInfoTransmission->noTransmittedMsgs;
    }
    else
    {
        /* Count the messages, which are lost due to queue full. */
        const unsigned long newVal = can_noEvTxSendBufFull+1;
        if(newVal != 0)
            can_noEvTxSendBufFull = newVal;

        pTxFrDesc->pInfoTransmission->stsTransmission |= cap_stsTransm_errSendBufferFull;
    }

    /* Count all messages, which should have been sent. This counter is not saturated. */
    ++ can_noTxMsgs;

} /* End of protectAndSendMsg */



/**
 * Shared callback for the timers of all regular outbound messages. When the timer elapses
 * the message is due and needs to be submitted for sending.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 *   @remark
 * The implementation of this callback needs to be reentrant. It can be called coincidently
 * from different dispatchers clocked in different threads.
 */
static void onSendRegularMsg(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* Sending a regular message is an unconditional, straight forward operation each time
       the callback fires. */
    protectAndSendMsg(pContext);

} /* End of onSendRegularMsg */



/**
 * Shared callback for the timers of all outbound event messages. When the timer elapses
 * the due conditions of the message need to be checked and the message needs to be submitted
 * for sending if it became \a true in the meantime.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onDueCheckEventMsg(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED);

    /* The OS handle of the message is the index in the OSE owned configuration table. This
       is a simple and efficient decision, which has been taken in the call of the
       registration method. */
    const unsigned int idxTxFr = ede_getIdxInternalEventSource(pContext);
    const cdt_canMessage_t * const pTxFrDesc = &cdt_canTxMsgAry[idxTxFr];

    signed int tiNewFromNow;
    assert(pTxFrDesc->pInfoTransmission != NULL);
    if(pTxFrDesc->pInfoTransmission->isEvent)
    {
        /* APSW has signaled an event, acknowledge by resetting the flag and send the
           message. */
        pTxFrDesc->pInfoTransmission->isEvent = false;
        protectAndSendMsg(pContext);

        /* The time when the timer should fire the next time depends. We had an event in
           this tick, so we need to regard the minimum distance. */
        tiNewFromNow = (int)pTxFrDesc->tiMinDistance;
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
} /* End of onDueCheckEventMsg */



/**
 * Shared callback for the timers of all outbound messages of transmission timing pattern
 * "mixed". When the timer elapses the due conditions of the message need to be checked and
 * the message needs to be submitted for sending if it became \a true in the meantime.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onDueCheckMixedMsg(const ede_callbackContext_t *pContext)
{
    /* The OS handle of the message is the index in the OSE owned configuration table. This
       is a simple and efficient decision, which has been taken in the call of the
       registration method. */
    const unsigned int idxTxFr = ede_getIdxInternalEventSource(pContext);
    const cdt_canMessage_t * const pTxFrDesc = &cdt_canTxMsgAry[idxTxFr];

    /* Double-check that this callback is called from an expected context. */
    assert(ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED
           &&  pTxFrDesc->sendMode == CAN_ENUM_SEND_MODE_MIXED
          );

    /* Get access to the handler's context data related to the message under progress. */
    assert(pTxFrDesc->idxHandlerCtxData < sizeOfAry(_hdlCtxDataOutMixedAry));
    const ede_handleTimer_t
        hTimerDueCheck = _hdlCtxDataOutMixedAry[pTxFrDesc->idxHandlerCtxData].hTimerDueCheck,
        hTimerTimeout = _hdlCtxDataOutMixedAry[pTxFrDesc->idxHandlerCtxData].hTimerTimeout,
        hThis = ede_getHandleTimer(pContext);

    /* The message needs to be sent if there is a data change event from the APSW or if the
       timeout timer fired. */
    signed int tiNewFromNowDueCheck;
    assert(pTxFrDesc->pInfoTransmission != NULL);
    if(pTxFrDesc->pInfoTransmission->isEvent  ||  hThis == hTimerTimeout)
    {
        /* If APSW has signaled an event, acknowledge by resetting the flag and send the
           message. If it is a timeout, we can still reset the flag, there are no race
           conditions. */
        pTxFrDesc->pInfoTransmission->isEvent = false;
        protectAndSendMsg(pContext);

        /* The time when the due check should be done again depends. We had a sent event in
           this tick, so we need to regard the minimum distance.
             The timeout timer is retriggered. */
        tiNewFromNowDueCheck = (int)pTxFrDesc->tiMinDistance;
        assert(tiNewFromNowDueCheck > 0  &&  (int)pTxFrDesc->tiCycle > 0);
        ede_retriggerSingleShotTimer( pContext
                                    , hTimerTimeout
                                    , /* tiNewFromNow */ (int)pTxFrDesc->tiCycle
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

} /* End of onDueCheckMixedMsg */



/**
 * The initialization callback for registered messages. An appropriate set of timers is
 * created, which will later trigger all messages at their individual due times.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onInitSendMsgs(const ede_callbackContext_t *pContext)
{
    /* Double-check the intended use case of this callback. This callback must be used only
       for the initialization of outbound messages. It is shared between all dispatchers. */
    assert(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_INT_INIT);

    /* This callback is shared between all outbound messages. Get access to the specification
       entry of the currently processed message. */
    const unsigned int idxTxFr = ede_getIdxInternalEventSource(pContext);
    const cdt_canMessage_t * const pTxFrDesc = &cdt_canTxMsgAry[idxTxFr];

    switch(pTxFrDesc->sendMode)
    {
        case CAN_ENUM_SEND_MODE_REGULAR:
        {
            /* Regular messages are most simple. We apply a regular timer. */
            assert((int)pTxFrDesc->tiCycle > 0);
#ifdef DEBUG
            const ede_handleTimer_t hTimer =
#endif
            ede_createPeriodicTimer( pContext
                                   , /* tiPeriod */ (int)pTxFrDesc->tiCycle
                                   , /* callback */ onSendRegularMsg
                                   );
            assert(hTimer != EDE_INVALID_TIMER_HANDLE);
            break;
        }
        case CAN_ENUM_SEND_MODE_EVENT:
        {
            /* Event messages can become due in every tic. We set a timer of minimum elapse
               time and will check the send condition in the callback. The repetition of
               the timer depends; if it comes to sending then the next check is not
               immediately but after the minimum distance time. Therefore we don't use a
               regular timer to trigger the due check regularly but take a single shot timer,
               which can be reprogrammed at every callback. */
#ifdef DEBUG
            const ede_handleTimer_t hTimer =
#endif
            ede_createSingleShotTimer( pContext
                                     , /* tiFromNow */ 1
                                     , /* callback */ onDueCheckEventMsg
                                     , /* killAtDueTime */ false
                                     );
            assert(hTimer != EDE_INVALID_TIMER_HANDLE);
            break;
        }
        case CAN_ENUM_SEND_MODE_MIXED:
        {
            /* Event messages with fallback can become due in every tic. We set a timer of
               minimum elapse time and will check the send condition in the callback. The
               repetition of the timer depends; if it comes to sending then the next check
               is not immediately but after the minimum distance time. Therefore we don't
               use a regular timer to trigger the due check regularly but take a single
               shot timer, which can be reprogrammed at every callback.
                 A second timer is required to guarantee the fallback trigger if no event
               occurs. */
            const unsigned int idxCtxData = pTxFrDesc->idxHandlerCtxData;
            assert(idxCtxData < sizeOfAry(_hdlCtxDataOutMixedAry)
                   &&  _hdlCtxDataOutMixedAry[idxCtxData].hTimerDueCheck
                       == EDE_INVALID_TIMER_HANDLE
                   &&  _hdlCtxDataOutMixedAry[idxCtxData].hTimerTimeout
                       == EDE_INVALID_TIMER_HANDLE
                  );

            _hdlCtxDataOutMixedAry[idxCtxData].hTimerDueCheck =
            ede_createSingleShotTimer( pContext
                                     , /* tiPeriod */ 1
                                     , /* callback */ onDueCheckMixedMsg
                                     , /* killAtDueTime */ false
                                     );
            assert(_hdlCtxDataOutMixedAry[idxCtxData].hTimerDueCheck
                   != EDE_INVALID_TIMER_HANDLE
                  );

            assert((int)pTxFrDesc->tiCycle > 0);
            _hdlCtxDataOutMixedAry[idxCtxData].hTimerTimeout =
            ede_createSingleShotTimer( pContext
                                     , /* tiPeriod */ (int)pTxFrDesc->tiCycle
                                     , /* callback */ onDueCheckMixedMsg
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

} /* End of onInitSendMsgs */




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
 *   @param PID
 * The mechanism to run task in a user process, which is applied for the implementation of
 * this callback has the target PID as first argument. So this will always be bsw_pidUser.
 *   @param pRxCanMsg
 * A typical callback will pass some information about the received CAN message. Here, in
 * this sample, it is a struct containing message handle from the OS, CAN ID and, payload.
 * The information is passed in by reference.
 */
int32_t bsw_onRxCan( uint32_t PID ATTRIB_DBG_ONLY
                   , const bsw_rxCanMessage_t *pRxCanMsg
                   )
{
    assert(PID == bsw_pidUser);

    /* Note, this is a callback from the operating system and not a dispatcher callback.
       The EDE API is not available here to access message properties. */

    /* Having the CAN interface handle of the received message, we can post a message-received
       event to the dispatcher. In this sample, we apply the internal mapping, which maps
       bus and mailbox index onto the message index used in the CAN engine. */
    const ede_kindOfEvent_t kindOfEvent = pRxCanMsg->idxCanBus + can_evt_newRxMsg_bus0;
    assert(kindOfEvent <= can_evt_newRxMsg_bus3);
    const boolean_t success = ede_postEvent( _hEventSender
                                           , kindOfEvent
                                           , /* senderHandleEvent */ pRxCanMsg->idxMailbox
                                           , /* pData */ pRxCanMsg->payload
                                           , /* sizeOfData */ pRxCanMsg->sizeOfPayload
                                           );
    if(!success)
    {
        /* Count all received messages, which are lost because of queue full. */
        const unsigned long newVal = can_noEvRxQueueFull + 1;
        if(newVal != 0)
            can_noEvRxQueueFull = newVal;
    }

    /* Count all received messages. This counter is not saturated. */
    ++ can_noRxMsgs;

    /* This function can produce errors (queue full). This is however not that server that
       we would report it as a (safety relevant) process error. */
    return 0;

} /* End of bsw_onRxCan */



/**
 * Initialization of the CAN interface.
 *   @return
 * Get \a true if everythimg is alright, or \a false otherwise. \a false will mostly point
 * to a lack of memory for the given number of messages and signals. Memory is allocated in
 * a static way and in this case the code needs recompilation with more memory; see
 * #CAN_SIZE_OF_HEAP_FOR_CAN_INTERFACE for details.\n
 *   Dynamic run-time descisions for error handling are not required. All decisions made in
 * the function, which decide the return value, are static and not runtime data dependent.
 * Once a given configuration (i.e. a given CAN database, the configured amount of memory)
 * has been found alright it'll never fail in future runs of the SW. Consequently, an
 * assertion will normally be the adequate means to check the function result.
 */
bool can_initCanStack(void)
{

    /* Initialize the global data of this module. */
    unsigned int u;
    for(u=0; u<sizeOfAry(_hTimerInTimeoutAry); ++u)
        _hTimerInTimeoutAry[u] = EDE_INVALID_TIMER_HANDLE;
    for(u=0; u<sizeOfAry(_hdlCtxDataOutMixedAry); ++u)
    {
        _hdlCtxDataOutMixedAry[u].hTimerDueCheck = EDE_INVALID_TIMER_HANDLE;
        _hdlCtxDataOutMixedAry[u].hTimerTimeout = EDE_INVALID_TIMER_HANDLE;
    }

    /* Reset some global event counters, which form a public API. */
    can_noRxMsgs        =
    can_noTxMsgs        =
    can_noEvRxTimeout     =
    can_noEvTxSendBufFull =
    can_noEvRxQueueFull   = 0;

    /* Create the memory pool we use for all CAN stack objects. This memory needs to be
       accessible during the entire remaining runtime of the software. */
    static char DATA_P1(heapMemoryForCanInterface)[CAN_SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    ede_memoryPool_t memoryPool = EDE_INVALID_MEMORY_POOL;
    mem_fctCriticalSection_t const mutualExclusionGuard = NULL;
    boolean_t success = mem_createMemoryPool
                                    ( &memoryPool
                                    , /* pPoolMemory */ heapMemoryForCanInterface
                                    , /* sizeOfPoolMemory */ sizeof(heapMemoryForCanInterface)
                                    , mutualExclusionGuard
                                    );
    
    /* Create the required dispatcher queues. */
    ede_eventSenderPort_t portSender;
    ede_eventReceiverPort_t portDispatcher;
    if(success)
    {
        success = vsq_createEventQueue( &portDispatcher
                                      , &portSender
                                      , /* maxQueueLength */ CAN_DISPATCHER_10MS_QUEUE_LEN
                                      , /* sizeOfElement */ 8u /* max DLC */
                                      , /* pMemPoolDispatchingProcess */ &memoryPool
                                      , /* pMemPoolSenderOfEvents */     &memoryPool
                                      );
    }
    
    /* Create the required dispatcher systems. */
    if(success)
    {
        success = ede_createDispatcherSystem
                                ( &can_hDispatcherSystem
                                , /* noEventDispatcherEngines */ CAN_IDX_DISPATCHER_10MS + 1u
                                , /* maxNoEventSourcesExt */ CST_NO_CAN_MSGS_RECEIVED
                                , /* maxNoEventSourcesInt */ CST_NO_CAN_MSGS_SENT
                                , &memoryPool
                                );
        assert(!success ||  can_hDispatcherSystem != EDE_INVALID_DISPATCHER_SYSTEM_HANDLE);
    }

    /* Create the required dispatchers with their associated handle maps.
         Suitable handle maps: In this application, we see a simple handle mapping.
       The sender handles of CAN Rx events are determined by the message registration
       process (see below) in a way that we can apply the offset map. A condition to use
       this map is that messages from different buses have their own dedicated instance of
       the map. We achieve this by defining a different kind of event for each supported
       bus. */
    const bool isSenderHandleInUseAry[can_evt_noKindsOfExternalEvents] =
    {
        [/* Kind of event */ can_evt_newRxMsg_bus0] = true,
        [/* Kind of event */ can_evt_newRxMsg_bus1] = true,
        [/* Kind of event */ can_evt_newRxMsg_bus2] = true,
        [/* Kind of event */ can_evt_newRxMsg_bus3] = true,
    };
    ede_mapSenderEvHandleToIdx_t handleMap;
    if(success)
    {
        success = mpo_createMapOffsetOnly( &handleMap
                                         , can_evt_noKindsOfExternalEvents
                                         , isSenderHandleInUseAry
                                         , &memoryPool
                                         );
    }
    if(success)
    {
        success = ede_createDispatcher( can_hDispatcherSystem
                                      , /* idxDispatcher */ CAN_IDX_DISPATCHER_10MS
                                      , /* tiTick */ 10 /* ms */
                                      , /* portAry */ &portDispatcher
                                      , /* noPorts */ 1u
                                      , /* mapSdrEvHdlToEdeEvSrcIdx */ handleMap
                                      );
    }

    /* Create the senders. We have one instance with one port. */
    if(success)
    {
        success = ede_createSender( &_hEventSender
                                  , &portSender
                                  , /* noPorts */ 1u
                                  , /* pMapSenderEvHandleToPortIndex */ NULL
                                  , &memoryPool
                                  );
        assert(!success ||  _hEventSender != EDE_INVALID_SENDER_HANDLE);
    }

    /* Handle mapping: The CAN interface engines deals out its handles as sequence 0, 1, 2,
       ..., regardless which bus the registered message belongs to or whether it is Rx or Tx.
       The CAN driver for the MPC5748G uses mailboxes with index and the user may
       register a message with any mailbox in the range in any order. Rx and Tx have two
       disjunct index ranges.
         We get a simple piecewise linear handle mapping with desired complexity of O(1) if
       we register the messages Rx before Tx and both groups with increasing mailbox index
       at the CAN driver. Moreover, all CAN buses use the same index ranges for their
       individual mailboxes, so we need to do this repeatedly for all buses one after
       another.
         Note, if we do not stick to this (or an equivalent) order then the implementation
       of the map will report an error and CAN communication won't be able to process all
       messages. */
    unsigned int idxBusLast, hOsMsg, idxRxFr;
    
    idxBusLast = UINT_MAX;
    hOsMsg = UINT_MAX;
    for(idxRxFr=0; success && idxRxFr<CST_NO_CAN_MSGS_RECEIVED; ++idxRxFr)
    {
        const cdt_canMessage_t *const pRxFrDesc = &cdt_canRxMsgAry[idxRxFr];

        /* Processing bus after bus is simplified by the fact that the CAN datatables are
           generally ordered in this way. We just look for the change of bus index in the
           sequence. */
/// @todo We need to have a safe and transparent identity between pRxFrDesc->idxCanBus and the Rx event enumeration
        if(pRxFrDesc->idxCanBus == idxBusLast)
        {
            /* Same CAN bus as before, address to next available mailbox. */
            ++ hOsMsg;
        }
        else
        {
            /* The messages from the next bus begin. We switch to the next instance of the
               CAN driver and need to count the mailboxes again from the beginning. */
            hOsMsg = BSW_IDX_FIRST_RX_MAILBOX;
        }
        idxBusLast = pRxFrDesc->idxCanBus;

        /// @todo The BSW should wrap this API from the CAN driver: The argument doNotify is in now way relevant to the APSW but handled internally to the BSW. Maybe, the wrapping API in the BSW could also hide some aspects from the handle mapping and/or it could offer polled safety mailbox vs. queued QM mailboxes. However, the safety concept should not be touched by seeing the argument doNotify here
        assert(hOsMsg >= BSW_IDX_FIRST_RX_MAILBOX  &&  hOsMsg <= BSW_IDX_LAST_RX_MAILBOX);
        success = cdr_makeMailboxReservation( pRxFrDesc->idxCanBus
                                            , /* hMB */ hOsMsg
                                            , pRxFrDesc->isExtId
                                            , pRxFrDesc->canId
                                            , /* isReceived */ true
                                            , /* TxDLC, doesn't care */ 0
                                            , /* doNotify */ true
                                            )
                  == cdr_errApi_noError;

        /* The never received bit is initially set in the transmission status. All other
           status bits are cleared. */
        pRxFrDesc->pInfoTransmission->stsTransmission = cap_stsTransm_neverReceived;

        if(success)
        {
            unsigned int idxEde ATTRIB_DBG_ONLY;
            const ede_kindOfEvent_t kindOfEvent = pRxFrDesc->idxCanBus+can_evt_newRxMsg_bus0;
            idxEde = ede_registerExternalEventSource
                                ( can_hDispatcherSystem
                                , CAN_IDX_DISPATCHER_10MS
                                , kindOfEvent
                                , /* senderHandleEvent */ hOsMsg
                                , /* callback */ onInitReceivedMsgs
                                , /* refEventSourceData */ (uintptr_t)pRxFrDesc
                                );
            assert(idxEde == idxRxFr);
            assert(handleMap.getValue(handleMap.hInstance, &idxEde, kindOfEvent, hOsMsg));
            assert(idxEde == idxRxFr);
        }
    } /* for(All inbound messages) */

    idxBusLast = UINT_MAX;
    hOsMsg = UINT_MAX;
    unsigned int idxTxFr;
    for(idxTxFr=0; success && idxTxFr<CST_NO_CAN_MSGS_SENT; ++idxTxFr)
    {
        const cdt_canMessage_t *const pTxFrDesc = &cdt_canTxMsgAry[idxTxFr];

        /* Processing bus after bus is simplified by the fact that the CAN datatables are
           generally ordered in this way. We just look for the change of bus index in the
           sequence. */
        if(pTxFrDesc->idxCanBus == idxBusLast)
        {
            /* Same CAN bus as before, address to next available mailbox. */
            ++ hOsMsg;
        }
        else
        {
            /* The messages from the next bus begin. We switch to the next instance of the
               CAN driver and need to count the mailboxes again from the beginning. */
            hOsMsg = BSW_IDX_FIRST_TX_MAILBOX;
        }
        idxBusLast = pTxFrDesc->idxCanBus;

        assert(hOsMsg >= BSW_IDX_FIRST_TX_MAILBOX  &&  hOsMsg <= BSW_IDX_LAST_TX_MAILBOX);
        success = cdr_makeMailboxReservation( pTxFrDesc->idxCanBus
                                            , /* hMB */ hOsMsg
                                            , pTxFrDesc->isExtId
                                            , pTxFrDesc->canId
                                            , /* isReceived */ false
                                            , /* DLC */ pTxFrDesc->size
                                            , /* doNotify */ false
                                            )
                  == cdr_errApi_noError;
        if(success)
        {
            unsigned int idxEde ATTRIB_DBG_ONLY;
            idxEde = ede_registerInternalEventSource
                                ( can_hDispatcherSystem
                                , CAN_IDX_DISPATCHER_10MS
                                , /* callback */ onInitSendMsgs
                                , /* refEventSourceData */ (uintptr_t)hOsMsg
                                );
            assert(idxEde == idxTxFr);
        }
    } /* for(All outbound messages) */

    return success;

} /* End of can_initCanStack */

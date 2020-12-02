/**
 * @file apt_applicationTask.c
 * This file links the dummy APSW to the operating system (emulation). It contains the
 * entry points into all the application tasks.\n
 *   The init task is for example used to initialize all data structures of the CAN
 * interface.\n
 *   The regularly executed run-time tasks run the CAN interface engine and call the APSW.
 * The CAN interface engine updates all signal values and status in the global CAN API and
 * sends due frames, filled with information read from this API.\n
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
 * Copyright (C) 2015-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   bsw_taskUserInit
 *   bsw_taskUser1ms
 *   bsw_taskUser10ms
 *   bsw_taskUser100ms
 *   bsw_taskUser1000ms
 * Local functions
 *   onFrameReception
 *   onFrameInTimeout
 *   onInitReceivedFrames
 *   protectAndSendFrame
 *   onSendRegularFrame
 *   onDueCheckEventFrame
 *   onDueCheckMixedFrame
 *   onInitSendFrames
 */


/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "cap_canApi.h"
#include "bsw_basicSoftware.h"
#include "cdr_canDriverAPI.h"
#include "mem_malloc.h"
#include "cde_canDispatcherEngine.h"
#include "cde_canStatistics.h"
#include "cde_canDataTables.h"
#include "asw_APSW.h"
#include "apt_applicationTask.h"


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

/** This macro is a primitive way to define the timeout span for received frames. It maps
    the nominal maximum time span between two reception events onto the time span after
    which the CAN interface should decide on timeout. The latter time span needs to be
    greater than the former: CAN bus timing always requires a tolerance and the time
    measurement is done only with the resolution of the tick of the CAN interface engine. */
#define TIMEOUT(tiCycle) (3*(tiCycle)+1)

/* Check the number of processed messages against the HW constraints. Note, the condition
   is necessary but not sufficient; a bad distrubution of messages between user and safety
   process cann still foil successful initialization of the CAN stack. */
_Static_assert( CDE_NO_CAN_FRAMES_RECEIVED
                <= (BSW_IDX_LAST_RX_MAILBOX-BSW_IDX_FIRST_RX_MAILBOX+1)
                   + (BSW_IDX_LAST_RX_MAILBOX_SAFETY-BSW_IDX_FIRST_RX_MAILBOX_SAFETY+1u)
                &&  CDE_NO_CAN_FRAMES_SENT
                    <= (BSW_IDX_LAST_TX_MAILBOX-BSW_IDX_FIRST_TX_MAILBOX+1)
                       + (BSW_IDX_LAST_TX_MAILBOX_SAFETY-BSW_IDX_FIRST_TX_MAILBOX_SAFETY+1u)
              , "The number of processed messages exceeds the given hardware capabilities"
              );

/*
 * Local type definitions
 */

/** Type of context data for the handler for outbound mixed mode frames. */
typedef struct hdlCtxDataOutMixed_t
{
    /** The handle of the due check timer. */
    cde_handleTimer_t hTimerDueCheck;

    /** The handle of the timeout timer. */
    cde_handleTimer_t hTimerTimeout;

} hdlCtxDataOutMixed_t;


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** The handler for inbound frames requires local context data for regular and mixed mode
    frames. Here's an array of context data objects, one for each such frame; the entries
    for regular frames precede those for mixed mode frames. */
static cde_handleTimer_t BSS_P1(_hTimerInTimeoutAry)[CDE_NO_CAN_FRAMES_RECEIVED_REGULAR
                                                     + CDE_NO_CAN_FRAMES_RECEIVED_MIXED
                                                    ];

/** The handler for outbound mixed mode frames requires local context data. Here's an array
    of context data objects, one for each such frame. */
static hdlCtxDataOutMixed_t BSS_P1(_hdlCtxDataOutMixedAry)[CDE_NO_CAN_FRAMES_SENT_MIXED];


/** The total count of all ever received frames, including the lost one because of queue
    full events. The counter is not saturated and will wrap at the implementation limit.
    This public interface can be read by any context on any core at any time. */
volatile unsigned long UNCACHED_P1(apt_noRxFrames) = 0;

/** The total number of sent frames, including the lost one because of send buffer full
    events. The counter is not saturated and will wrap at the implementation limit. This
    public interface can be read by any context on any core at any time.*/
volatile unsigned long UNCACHED_P1(apt_noTxFrames) = 0;

/** The total number of Rx timeout events. This public interface can be read by any context
    on any core at any time. */
volatile unsigned long UNCACHED_P1(apt_noEvRxTimeout) = 0;

/** The total number of lost Rx frames because of queue full. This public interface can be
    read by any context on any core at any time. */
volatile unsigned long UNCACHED_P1(apt_noEvRxQueueFull) = 0;

/** The total number of lost Tx frames because of send buffer full events. This public
    interface can be read by any context on any core at any time. */
volatile unsigned long UNCACHED_P1(apt_noEvTxSendBufFull) = 0;


/*
 * Function implementation
 */

/**
 * Temporary solution for reception callback: No timing supervision, just E2E validation.
 */
static void onFrameReception(const cde_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(cde_isInboundTransmission(pContext)
           &&  cde_getKindOfEvent(pContext) == CDE_EV_FRAME_RECEPTION //CDE_TIMER_ELAPSED
          );

    /* Get the CDE index of the frame, which is the index into the CDE data tables at the
       same time. This has been ensured by the frame registration process. */
    const unsigned int idxFrCde = cde_getIdxFrame(pContext)
                     , idxRxFr = CDE_MAP_HANDLE_RX_FRAME_CAN_IF_TO_IDX_RX(idxFrCde);
    const cde_canFrame_t *const pFrDescCde = &cde_canRxFrameAry[idxRxFr];

    /* Test: Do some consistency tests. */
    assert(cde_getCanId(pContext) == pFrDescCde->canId
           &&  cde_getIdxBus(pContext) == pFrDescCde->idxCanBus
           &&  pFrDescCde->isReceived
           &&  pFrDescCde->pInfoTransmission != NULL
          );

    /* Reset the never received bit in the transmission status. */
    pFrDescCde->pInfoTransmission->stsTransmission &= ~cap_stsTransm_neverReceived;

    /* Some transmission pattern have a timeout supervision. Retrigger the timer and clear
       a possibly set timeout error bit. */
    if(pFrDescCde->sendMode != cap_enumSendMode_event)
    {
        unsigned int idxHandlerCtxData;
        if(pFrDescCde->sendMode == cap_enumSendMode_regular)
            idxHandlerCtxData = pFrDescCde->idxHandlerCtxData;
        else
        {
            assert(pFrDescCde->sendMode == cap_enumSendMode_mixed);

            /* Both transmission patterns share the same handler context data. The entries
               for mode mixed are placed behind those of mode regular. */
            idxHandlerCtxData = pFrDescCde->idxHandlerCtxData
                                + CDE_NO_CAN_FRAMES_RECEIVED_REGULAR;
        }

        assert(idxHandlerCtxData < sizeOfAry(_hTimerInTimeoutAry)
               &&  _hTimerInTimeoutAry[idxHandlerCtxData] != CDE_INVALID_TIMER_HANDLE
              );
        cde_retriggerSingleShotTimer( pContext
                                    , _hTimerInTimeoutAry[idxHandlerCtxData]
                                    , /* tiNewFromNow */ TIMEOUT(pFrDescCde->tiCycle)
                                    );

        /* Reset the timeout error in the frame related status word. */
        pFrDescCde->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errTimeout;

    } /* if(Do we have a timeout timer for the given transmission pattern?) */

    /* For event kind CDE_EV_FRAME_RECEPTION the event's data is the frame contents. */
    unsigned int sizeOfEvData;
    const uint8_t *frameContents;
    cde_getEventData(pContext, &sizeOfEvData, (const void**)&frameContents);
    assert(sizeOfEvData <= 8);

/// @todo E2E has not been adopted from the original sample code
//    /* Run the frame specific E2E protection method. By side effect, and only on success,
//       the data is written into the global API at the same time. (Where nobody will ever
//       look for it in this test.) */
//    const boolean_t e2eOkay = pFrDescCde->fctUnpackApiFrameAndValidate(frameContents);
    const bool e2eOkay = true;

    /* Run the message decomposition. The signal data is written into the global API. */
    pFrDescCde->fctUnpackApiFrame(frameContents);

    /* Indicate the E2E validation result to the APSW. */
    if(e2eOkay)
    {
        pFrDescCde->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errChecksum;

        /* The reception event is only counted in case of valid data. Otherwise the global
           CAN API has not been updated with new signal values and no reception event must
           be notified. */
        ++ pFrDescCde->pInfoTransmission->noTransmittedFrames;
        pFrDescCde->pInfoTransmission->isEvent;
    }
    else
    {
        /* Globally count the recognized failures. */
        /// @todo see above ++ apt_noEvRxE2eFailure;

        /* Report the failure. */
        pFrDescCde->pInfoTransmission->stsTransmission |= cap_stsTransm_errChecksum;
    }
} /* End of onFrameReception */



/**
 * Timer callback for all inbound frames, which a timeout is defined for. The timer is
 * retriggered on each frame reception event and if it eventually fires then it is a
 * timeout event for the related frame.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onFrameInTimeout(const cde_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(cde_isInboundTransmission(pContext)
           &&  cde_getKindOfEvent(pContext) == CDE_TIMER_ELAPSED
          );

    /* Get the CDE index of the frame, which is the index into the CDE data tables at the
       same time. This has been ensured by the frame registration process. */
    const unsigned int idxFrCde = cde_getIdxFrame(pContext)
                     , idxRxFr = CDE_MAP_HANDLE_RX_FRAME_CAN_IF_TO_IDX_RX(idxFrCde);
    const cde_canFrame_t *const pFrDescCde = &cde_canRxFrameAry[idxRxFr];

    /* Test: Do some consistency tests. */
    assert(cde_getCanId(pContext) == pFrDescCde->canId
           &&  cde_getIdxBus(pContext) == pFrDescCde->idxCanBus
           &&  pFrDescCde->isReceived
           &&  pFrDescCde->sendMode != cap_enumSendMode_event
           &&  pFrDescCde->pInfoTransmission != NULL
          );

    /* Globally count all timeout events. */
    const unsigned long newVal = apt_noEvRxTimeout + 1;
    if(newVal != 0)
        apt_noEvRxTimeout = newVal;

    /* Set timeout error in frame related status word. */
    pFrDescCde->pInfoTransmission->stsTransmission |= cap_stsTransm_errTimeout;

} /* End of onFrameInTimeout */



/**
 * The initialization callback for all received frames. Timers are created that implement
 * the timming supervision.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onInitReceivedFrames(const cde_callbackContext_t *pContext)
{
    /* No particular timing supervision is implemented yet. We just redirect to the later
       implementation. */
#ifdef DEBUG
    cde_callback_t callbackSoFar =
#endif
    cde_installCallback(pContext, onFrameReception);
    assert(callbackSoFar == onInitReceivedFrames);

    /* Get the CDE index of the frame, which is the index into the CDE data tables at the
       same time. This has been ensured by the frame registration process. */
    const unsigned int idxFrCde = cde_getIdxFrame(pContext)
                     , idxRxFr = CDE_MAP_HANDLE_RX_FRAME_CAN_IF_TO_IDX_RX(idxFrCde);
    const cde_canFrame_t *const pFrDescCde = &cde_canRxFrameAry[idxRxFr];
    assert(pFrDescCde->pInfoTransmission->stsTransmission == cap_stsTransm_neverReceived);

    /* All but pure event frames get a timeout counter. The handle needs to be accessible
       since the timer requires retriggering on reception. We use handler context data,
       which can be implemented by direct array lookup using the information in the
       auto-coded CDE data tables. */
    if(pFrDescCde->sendMode != cap_enumSendMode_event)
    {
        unsigned int idxHandlerCtxData;
        if(pFrDescCde->sendMode == cap_enumSendMode_regular)
            idxHandlerCtxData = pFrDescCde->idxHandlerCtxData;
        else
        {
            assert(pFrDescCde->sendMode == cap_enumSendMode_mixed);

            /* Both transmission patterns share the same handler context data. The entries
               for mode mixed are placed behind those of mode regular. */
            idxHandlerCtxData = pFrDescCde->idxHandlerCtxData
                                + CDE_NO_CAN_FRAMES_RECEIVED_REGULAR;
        }

        assert(idxHandlerCtxData < sizeOfAry(_hTimerInTimeoutAry)
               &&  _hTimerInTimeoutAry[idxHandlerCtxData] == CDE_INVALID_TIMER_HANDLE
              );
        _hTimerInTimeoutAry[idxHandlerCtxData] =
            cde_createSingleShotTimer( pContext
                                     , /* tiFromNow */ TIMEOUT(pFrDescCde->tiCycle)
                                     , /* callback */ onFrameInTimeout
                                     , /* pUserContextData */ NULL
                                     , /* killAtDueTime */ false
                                     );
        assert(_hTimerInTimeoutAry[idxHandlerCtxData] != CDE_INVALID_TIMER_HANDLE);

    } /* if(Do we require a timeout timer for the given transmission pattern?) */

} /* End of onInitReceivedFrames */



/**
 * Common code for sending frames of different transmission modes: E2E protect the data
 * found in the global CAN API of a given frame and submit this frame at the operating
 * system for sending.
 *   @param idxFrCde
 * The frame to process is identified by its index in the CAN interface engine.
 */
static void protectAndSendFrame(const unsigned int idxFrCde)
{
    const unsigned int idxTxFr = CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_IDX_TX(idxFrCde);
    const cde_canFrame_t *pFrDescCde = &cde_canTxFrameAry[idxTxFr];
    assert(!pFrDescCde->isReceived);

/// @todo E2E has not been adopted from the original sample code
//    /* Do the E2E protection of the APSW computed values in the global CAN interface:
//       Compute the checksum - if there is any. */
//    if(pFrDescCde->fctProtectApiFrame != NULL)
//        pFrDescCde->fctProtectApiFrame();

    /* Pack the frame. */
    uint8_t frameContent[pFrDescCde->size];
    pFrDescCde->fctPackApiFrame(&frameContent[0]);

    /* Invoke the operating system API to submit the frame for sending.
         The OS handle of the frame is the index in the OSE owned configuration table. The
       mapping from CAN interface index to OS handle is a simple offset operation. This
       is a simple and efficient descision, which has been taken in the call of the
       registration method. */
    assert(pFrDescCde->pInfoTransmission != NULL);
    if(cdr_sendMessage( /* idxCanDevice */ OSE_CAN_BUS_PT
                      , CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_OS(idxFrCde)
                      , &frameContent[0]
                      )
       == cdr_errApi_noError
      )
    {
        /* Reset the error status if we were able to put the frame into the mailbox. */
        pFrDescCde->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errSendBufferFull;

        /* The transmission event is only counted in case of success. This can be decided
           differently but it is consistent with the counting of received frames */
        ++ pFrDescCde->pInfoTransmission->noTransmittedFrames;
    }
    else
    {
        /* Count the frames, which are lost due to queue full. */
        const unsigned long newVal = apt_noEvTxSendBufFull+1;
        if(newVal != 0)
            apt_noEvTxSendBufFull = newVal;

        pFrDescCde->pInfoTransmission->stsTransmission |= cap_stsTransm_errSendBufferFull;
    }

    /* Count all frames, which should have been sent. This counter is not saturated. */
    ++ apt_noTxFrames;

} /* End of protectAndSendFrame */



/**
 * Shared callback for the timers of all regular outbound frames. When the timer elapses
 * the frame is due and needs to be submitted for sending.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 *   @remark
 * The implementation of this callback needs to be reentrant. It can be called coincidently
 * from different dispatchers clocked in different threads.
 */
static void onSendRegularFrame(const cde_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(!cde_isInboundTransmission(pContext)
           &&  cde_getKindOfEvent(pContext) == CDE_TIMER_ELAPSED
          );

    /* Sending a regular frame is an unconditional, straight forward operation each time
       the callback fires. */
    protectAndSendFrame(cde_getIdxFrame(pContext));

} /* End of onSendRegularFrame */



/**
 * Shared callback for the timers of all outbound event frames. When the timer elapses
 * the due conditions of the frame need to be checked and the frame needs to be submitted
 * for sending if it became \a true in the meantime.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onDueCheckEventFrame(const cde_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(!cde_isInboundTransmission(pContext)
           &&  cde_getKindOfEvent(pContext) == CDE_TIMER_ELAPSED
          );

    /* The OS handle of the frame is the index in the OSE owned configuration table. This
       is a simple and efficient descision, which has been taken in the call of the
       registration method. */
    const unsigned int idxFrCde = cde_getIdxFrame(pContext)
                     , idxTxFr = CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_IDX_TX(idxFrCde);
    const cde_canFrame_t * const pFrDescCde = &cde_canTxFrameAry[idxTxFr];

    signed int tiNewFromNow;
    assert(pFrDescCde->pInfoTransmission != NULL);
    if(pFrDescCde->pInfoTransmission->isEvent)
    {
        /* APSW has signaled an event, acknowledge by resetting the flag and send the
           frame. */
        pFrDescCde->pInfoTransmission->isEvent = false;
        protectAndSendFrame(idxFrCde);

        /* The time when the timer should fire the next time depends. We had an event in
           this tick, so we need to regard the minimum distance. */
        tiNewFromNow = pFrDescCde->tiMinDistance;
    }
    else
    {
        /* The time when the timer should fire the next time depends. We had no event this
           time and will test the Boolean decision immediately again in the next tick. */
        tiNewFromNow = 1;
    }

    /* The time when the timer should fire the next time depends. Adjust now, when again to
       test the send condition. */
    cde_retriggerSingleShotTimer( pContext
                                , /* hTimer */ NULL /* this timer */
                                , tiNewFromNow
                                );
} /* End of onDueCheckEventFrame */



/**
 * Shared callback for the timers of all outbound frames of transmission timing pattern
 * "mixed". When the timer elapses the due conditions of the frame need to be checked and
 * the frame needs to be submitted for sending if it became \a true in the meantime.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onDueCheckMixedFrame(const cde_callbackContext_t *pContext)
{
    /* The OS handle of the frame is the index in the OSE owned configuration table. This
       is a simple and efficient decision, which has been taken in the call of the
       registration method. */
    const unsigned int idxFrCde = cde_getIdxFrame(pContext)
                     , idxTxFr = CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_IDX_TX(idxFrCde);
    const cde_canFrame_t * const pFrDescCde = &cde_canTxFrameAry[idxTxFr];

    /* Double-check that this callback is called from an expected context. */
    assert(!cde_isInboundTransmission(pContext)
           &&  cde_getKindOfEvent(pContext) == CDE_TIMER_ELAPSED
           &&  pFrDescCde->sendMode == cap_enumSendMode_mixed
          );

    /* Get access to the handler's context data related to the frame under progress. */
    assert(pFrDescCde->idxHandlerCtxData < sizeOfAry(_hdlCtxDataOutMixedAry));
    const cde_handleTimer_t
        hTimerDueCheck = _hdlCtxDataOutMixedAry[pFrDescCde->idxHandlerCtxData].hTimerDueCheck,
        hTimerTimeout = _hdlCtxDataOutMixedAry[pFrDescCde->idxHandlerCtxData].hTimerTimeout,
        hThis = cde_getHandleTimer(pContext);

    /* The frame needs to be sent if there is a data change event from the APSW or if the
       timeout timer fired. */
    signed int tiNewFromNowDueCheck;
    assert(pFrDescCde->pInfoTransmission != NULL);
    if(pFrDescCde->pInfoTransmission->isEvent  ||  hThis == hTimerTimeout)
    {
        /* If APSW has signaled an event, acknowledge by resetting the flag and send the
           frame. If it is a timeout, we can still reset the flag, there are no race
           conditions. */
        pFrDescCde->pInfoTransmission->isEvent = false;
        protectAndSendFrame(idxFrCde);

        /* The time when the due check should be done again depends. We had a sent event in
           this tick, so we need to regard the minimum distance.
             The timeout timer is retriggered. */
        tiNewFromNowDueCheck = pFrDescCde->tiMinDistance;
        cde_retriggerSingleShotTimer( pContext
                                    , hTimerTimeout
                                    , /* tiNewFromNow */ pFrDescCde->tiCycle
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
    cde_retriggerSingleShotTimer(pContext, hTimerDueCheck, tiNewFromNowDueCheck);

} /* End of onDueCheckMixedFrame */



/**
 * The initialization callback for registered frames. An appropriate set of timers is
 * created, which will later trigger all frames at their individual due times.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */

static void onInitSendFrames(const cde_callbackContext_t *pContext)
{
    /* Double-check the intended use case of this callback. This callback must be used only
       for the initialization of outbound frames. It is shared between all dispatchers. */
    assert(cde_getKindOfEvent(pContext) == CDE_EV_FRAME_INIT
           &&  !cde_isInboundTransmission(pContext)
          );

    /* This callback is shared between all outbound frames. Get access to the specification
       entry of the currently processed frame. */
    const unsigned int idxFrCde = cde_getIdxFrame(pContext)
                     , idxTxFr = CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_IDX_TX(idxFrCde);
    const cde_canFrame_t * const pFrDescCde = &cde_canTxFrameAry[idxTxFr];

    switch(pFrDescCde->sendMode)
    {
        case cap_enumSendMode_regular:
        {
            /* Regular frames are most simple. We apply a regular timer. */
#ifdef DEBUG
            cde_handleTimer_t hTimer =
#endif
            cde_createPeriodicTimer( pContext
                                   , /* tiPeriod */ pFrDescCde->tiCycle
                                   , /* callback */ onSendRegularFrame
                                   , /* pUserContextData */ NULL
                                   );
            assert(hTimer != CDE_INVALID_TIMER_HANDLE);
            break;
        }
        case cap_enumSendMode_event:
        {
            /* Event frames can become due in every tic. We set a timer of minimum elapse
               time and will check the send condition in the callback. The repetition of
               the timer depends; if it comes to sending then the next check is not
               immediately but after the minimum distance time. Therefore we don't use a
               regular timer to trigger the due check regularly but take a single shot timer,
               which can be reprogrammed at every callback. */
#ifdef DEBUG
            cde_handleTimer_t hTimer =
#endif
            cde_createSingleShotTimer( pContext
                                     , /* tiFromNow */ 1
                                     , /* callback */ onDueCheckEventFrame
                                     , /* pUserContextData */ NULL
                                     , /* killAtDueTime */ false
                                     );
            assert(hTimer != CDE_INVALID_TIMER_HANDLE);
            break;
        }
        case cap_enumSendMode_mixed:
        {
            /* Event frames with fallback can become due in every tic. We set a timer of
               minimum elapse time and will check the send condition in the callback. The
               repetition of the timer depends; if it comes to sending then the next check
               is not immediately but after the minimum distance time. Therefore we don't
               use a regular timer to trigger the due check regularly but take a single
               shot timer, which can be reprogrammed at every callback.
                 A second timer is required to guarantee the fallback trigger if no event
               occurs. */
            const unsigned int idxCtxData = pFrDescCde->idxHandlerCtxData;
            assert(idxCtxData < sizeOfAry(_hdlCtxDataOutMixedAry)
                   &&  _hdlCtxDataOutMixedAry[idxCtxData].hTimerDueCheck
                       == CDE_INVALID_TIMER_HANDLE
                   &&  _hdlCtxDataOutMixedAry[idxCtxData].hTimerTimeout
                       == CDE_INVALID_TIMER_HANDLE
                  );

            _hdlCtxDataOutMixedAry[idxCtxData].hTimerDueCheck =
            cde_createSingleShotTimer( pContext
                                     , /* tiPeriod */ 1
                                     , /* callback */ onDueCheckMixedFrame
                                     , /* pUserContextData */ NULL
                                     , /* killAtDueTime */ false
                                     );
            assert(_hdlCtxDataOutMixedAry[idxCtxData].hTimerDueCheck
                   != CDE_INVALID_TIMER_HANDLE
                  );

            _hdlCtxDataOutMixedAry[idxCtxData].hTimerTimeout =
            cde_createSingleShotTimer( pContext
                                     , /* tiPeriod */ pFrDescCde->tiCycle
                                     , /* callback */ onDueCheckMixedFrame
                                     , /* pUserContextData */ NULL
                                     , /* killAtDueTime */ false
                                     );
            assert(_hdlCtxDataOutMixedAry[idxCtxData].hTimerTimeout
                   != CDE_INVALID_TIMER_HANDLE
                  );

            break;
        }
        default:
            assert(false);

    } /* switch(Transmission pattern of frame) */

} /* End of onInitSendFrames */




/**
 * The application owned part of the CAN reception interrupt, or the CAN reception
 * callback. In each integration, this callback will be used to feed received CAN frames
 * into the input queue of the appropriate dispatcher for (later) processing.\n
 *   This callback will always be executed in the interrupt CPU context. The later
 * processing of the frame is done by the dispatcher in the context it has been started in
 * (i.e. the calling context of cde_dispatcherMain()). This is a normal application task
 * context, ideally the only task, which requires access to the frame's contents. If so, no
 * further attention has to be drawn to inter-task communication and data exchange.\n
 *   In our operating system emulation this callback is invoked in the context of a
 * different thread, which makes no particular difference to the interrupt context on a
 * typical embedded platform.
 *   @param idxFrameOs
 * A typical callback will pass some handle of the received CAN frame. This handle has
 * mostly been agreed on between APSW and BSW during the system initialization. In our
 * emulated operation system the received frames are specified by the APSW in form of an
 * initialized, constant data table. The index into this configuration table naturally is
 * the handle, which the operating system responds with when it comes to a reception event.
 *   @param pMsgContent
 * The received bytes are typically passed in as a pointer to a byte array.
 *   @param DLC
 * Any real existing platform will report the number of actually received bytes.
 */
int32_t bsw_onRxCan( uint32_t PID ATTRIB_DBG_ONLY
                   , const bsw_rxCanMessage_t *pRxCanMsg
                   )
{
    assert(PID == bsw_pidUser);

    /* Note, this is a callback from the operating system and not a dispatcher callback.
       The CDE API is not available here to access frame properties. */

    /* The OS reports the received frame with its own handle. The postEvent method can do
       the mapping from this handle (and maybe the CAN bus selection) to the frame index of
       the the dispatcher engine implementation. In this sample is the mapping of the
       handles made explicitly visible outside the CAN interface methods. */
    const unsigned int idxFrameCde =
                        CDE_MAP_HANDLE_RX_FRAME_OS_TO_CAN_IF(pRxCanMsg->idxMailbox);

    /* Having the CAN interface handle of the received frame, we can post a frame-received
       event to the dispatcher. If no internal mapping is configured then the bus index
       specified here doesn't care and the parameter osHandle is taken as CDE index. */
    boolean_t success = cde_postFrameEvent( /* idxBus */ UINT_MAX
                                          , /* osHandle */ idxFrameCde
                                          , /* kindOfEvent */ CDE_EV_FRAME_RECEPTION
                                          , /* pData */ pRxCanMsg->payload
                                          , /* sizeOfData */ pRxCanMsg->sizeOfPayload
                                          );
    if(!success)
    {
        /* Count all received frames, which are lost because of queue full. */
        const unsigned long newVal = apt_noEvRxQueueFull + 1;
        if(newVal != 0)
            apt_noEvRxQueueFull = newVal;
    }

    /* Count all received frames. This counter is not saturated. */
    ++ apt_noRxFrames;

    /* This function can produce errors (queue full). This is however not taht server taht
       we would report it as a (safety relevant) process error. */
    return 0;

} /* End of bsw_onRxCan */



/**
 * The initialization task of process bsw_pidUser, the QM aaplication code process. The task is
 * called at a time when no parallel thread execution is done yet, so no race conditions
 * exist with other parts of the code and safe build-up of all required data structure can
 * be done prior to the start of the real task scheduling.\n
 *   The initialization function of QM process bsw_pidUser is invoked prior to the
 * according initialization function of the safety process.\n
 *   We use this function to initialize the CAN interface.
 *   @return
 * The function may return a negative value to indicate a severe problem. The system won't
 * start up in this case. Normally, we will return zero.
 *   @param PID
 * The process ID of the initialized process, always bsw_pidUser in our case.
 */
unsigned idx = 999;
int32_t bsw_taskUserInit(uint32_t PID ATTRIB_DBG_ONLY)
{
    assert(PID == bsw_pidUser);

    boolean_t success;

    /* Initialize the modules. */
    /// @todo We need an extended concept in order to have CAN interface objects in
    // different memeory areas, e.g. a malloc per process
    static char heapMemoryForCanInterface[APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    mem_initModule( /* pAppMemory */ heapMemoryForCanInterface
                  , /* sizeOfAppMemory */ sizeof(heapMemoryForCanInterface)
                  );

    success = cde_initModule( /* maxNoBuses */  1
                            , /* maxNoFrames */ CDE_NO_CAN_FRAMES
                            , /* noDispatchers */ 1
                            );

    /* Initialize the global data of this module. */
    unsigned int u;
    for(u=0; u<sizeOfAry(_hTimerInTimeoutAry); ++u)
        _hTimerInTimeoutAry[u] = CDE_INVALID_TIMER_HANDLE;
    for(u=0; u<sizeOfAry(_hdlCtxDataOutMixedAry); ++u)
    {
        _hdlCtxDataOutMixedAry[u].hTimerDueCheck = CDE_INVALID_TIMER_HANDLE;
        _hdlCtxDataOutMixedAry[u].hTimerTimeout = CDE_INVALID_TIMER_HANDLE;
    }

    /* Reset some global event counters, which form a public API. */
    apt_noRxFrames        =
    apt_noTxFrames        =
    apt_noEvRxTimeout     =
    apt_noEvTxSendBufFull =
    apt_noEvRxQueueFull   = 0;

    /* Create the required dispatcher queues. */
    if(success)
    {
        success = cde_createDispatcher( /* idxQueue */ APT_IDX_DISPATCHER_10MS
                                      , /* maxQueueLength */ APT_DISPATCHER_10MS_QUEUE_LEN
                                      , /* sizeOfElement */ 8
                                      , /* tiTick */ 10 /* ms */
                                      );
    }

    /* Register all frames at the dispatcher engine. The CAN for the MPC5748G uses
       different ranges in the index space of its mailboxes for Rx and Tx. Therefore it
       offers two linear index spaces for Rx and Tx with a fixed offset in between. The
       mapping between the index spaces of CAN driver and CAN interface engine is most easy
       if we register our Rx and Tx messages in two blocks. */
       

    unsigned int idxFrCde;
    for(idxFrCde=0; success && idxFrCde<CDE_NO_CAN_FRAMES_RECEIVED; ++idxFrCde)
    {
        const unsigned int hOsFrame = CDE_MAP_HANDLE_RX_FRAME_CAN_IF_TO_OS(idxFrCde)
                         , idxRxFr = CDE_MAP_HANDLE_RX_FRAME_CAN_IF_TO_IDX_RX(idxFrCde);
        const cde_canFrame_t *const pFrDescCde = &cde_canRxFrameAry[idxRxFr];

        /// @todo The BSW should wrap this API from the CAN driver: The argument doNotify is in now way relevant to the APSW but handled internally to the BSW. Maybe, the wrapping API in the BSW could also hide some aspects from the handle mapping and/or it could offer polled safety mailbox vs. queued QM mailboxes. However, the safety concept should not be touched by seeing the argument doNotify here
        assert(hOsFrame <= BSW_IDX_LAST_RX_MAILBOX);
        success = cdr_makeMailboxReservation( /* idxCanDevice */ OSE_CAN_BUS_PT
                                            , /* hMB */ hOsFrame
                                            , pFrDescCde->isExtId
                                            , pFrDescCde->canId
                                            , /* isReceived */ true
                                            , /* TxDLC, doesn't care */ 0
                                            , /* doNotify */ true
                                            )
                  == cdr_errApi_noError;

        /* The never received bit is initially set in the transmission status. All other
           status bits are cleared. */
        pFrDescCde->pInfoTransmission->stsTransmission = cap_stsTransm_neverReceived;

        if(success)
        {
#ifdef DEBUG
            const unsigned int idxCde =
#endif
            cde_registerFrame( pFrDescCde->canId
                             , /* isInbound */ true
                             , pFrDescCde->idxCanBus
                             , /* osHandleFrame */ hOsFrame
                             , APT_IDX_DISPATCHER_10MS
                             , /* callback */ onInitReceivedFrames
                             );
            assert(idxCde == idxFrCde
                   &&  idxCde == CDE_MAP_HANDLE_RX_FRAME_OS_TO_CAN_IF(hOsFrame)
                  );
        }
else
{
    idx = idxFrCde;
}
    } /* for(All inbound frames) */

    assert(idxFrCde == CDE_NO_CAN_FRAMES_RECEIVED);
    for(; success && idxFrCde<CDE_NO_CAN_FRAMES; ++idxFrCde)
    {
        const unsigned int hOsFrame = CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_OS(idxFrCde) 
                         , idxTxFr = CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_IDX_TX(idxFrCde);
        const cde_canFrame_t *const pFrDescCde = &cde_canTxFrameAry[idxTxFr];
        

        assert(hOsFrame <= BSW_IDX_LAST_TX_MAILBOX);
        success = cdr_makeMailboxReservation( /* idxCanDevice */ OSE_CAN_BUS_PT
                                            , /* hMB */ hOsFrame
                                            , pFrDescCde->isExtId
                                            , pFrDescCde->canId
                                            , /* isReceived */ false
                                            , /* DLC */ pFrDescCde->size
                                            , /* doNotify */ false
                                            )
                  == cdr_errApi_noError;
        if(success)
        {
#ifdef DEBUG
            const unsigned int idxCde =
#endif
            cde_registerFrame( pFrDescCde->canId
                             , /* isInbound */ false
                             , pFrDescCde->idxCanBus
                             , /* osHandleFrame */ hOsFrame
                             , APT_IDX_DISPATCHER_10MS
                             , /* callback */ onInitSendFrames
                             );
            assert(idxCde == idxFrCde
                   &&  CDE_MAP_HANDLE_TX_FRAME_CAN_IF_TO_OS(idxCde) == hOsFrame
                  );
        }
else
{
    idx = idxFrCde;
}
    } /* for(All outbound frames) */

    return success? 0: -1;

} /* End of bsw_taskUserInit */




/**
 * Demo code of the regularly executed 1ms task of the APSW.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervior task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser1ms(uint32_t PID ATTRIB_DBG_ONLY, uintptr_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the 1ms step function of the APSW. */
    //asw_taskApsw_1ms();

    return 0;

} /* End of bsw_taskUser1ms */




/**
 * Demo code of the regularly executed 10ms task of the APSW. The engine of the CAN
 * interface is clocked and the decoded and pre-processed CAN information can be consumed
 * by the APSW. Vice versa, the APSW provided functional results are encoded and timely
 * sent by the engine. All data access can be done easy and directly since no race
 * conditions occur.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervior task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser10ms(uint32_t PID ATTRIB_DBG_ONLY, uintptr_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the step function of the CAN interface engine for this task. */
    cde_dispatcherMain(APT_IDX_DISPATCHER_10MS);

    /* Call the step function of the APSW, which computes new CAN output values. */
    asw_taskApsw_10ms();

    return 0;

} /* End of bsw_taskUser10ms */




/**
 * Demo code of the regularly executed 100ms task of the APSW.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervior task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser100ms(uint32_t PID ATTRIB_DBG_ONLY, uintptr_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the 100ms step function of the APSW. */
    //asw_taskApsw_100ms();

    return 0;

} /* End of bsw_taskUser100ms */




/**
 * Demo code of the regularly executed 1s task of the APSW.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervior task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser1000ms(uint32_t PID ATTRIB_DBG_ONLY, uintptr_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the 1s step function of the APSW. */
    //asw_taskApsw_1000ms();

    return 0;

} /* End of bsw_taskUser1000ms */





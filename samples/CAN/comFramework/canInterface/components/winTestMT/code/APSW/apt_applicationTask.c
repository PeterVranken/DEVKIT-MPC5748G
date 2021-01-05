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
 *   apt_irqHandlerRxCan
 *   apt_taskInit
 *   apt_task10ms
 *   apt_task100ms
 *   apt_taskShutdown
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

#include "sup_startup.h"
#include "ose_operatingSystemEmulation.h"
#include "mem_malloc.h"
#include "cde_canDispatcherEngine.h"
#include "cde_canStatistics.h"
#include "cap_canApi.h"
#include "e2e_frameProtection.h"
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


/** The handler for inbound frames requires local context data for regular and mixed mode
    frames. Here's an array of context data objects, one for each such frame; the entries
    for regular frames precede those for mixed mode frames. */
static cde_handleTimer_t _hTimerInTimeoutAry[CDE_NO_CAN_FRAMES_RECEIVED_REGULAR
                                             + CDE_NO_CAN_FRAMES_RECEIVED_MIXED
                                            ];

/** The handler for outbound mixed mode frames requires local context data. Here's an array
    of context data objects, one for each such frame. */
static struct hdlCtxDataOutMixed_t
{
    /** The handle of the due check timer. */
    cde_handleTimer_t hTimerDueCheck;
    
    /** The handle of the timeout timer. */
    cde_handleTimer_t hTimerTimeout;
    
} _hdlCtxDataOutMixedAry[CDE_NO_CAN_FRAMES_SENT_MIXED];


/** The total count of all ever received frames, including the lost one because of queue
    full events. */
_Atomic unsigned long long apt_noRxFrames = 0;

/** The total number of sent frames, including the lost one because of send buffer full
    events. */
_Atomic unsigned long long apt_noTxFrames = 0;

/** The total number of Rx timeout events. */
_Atomic unsigned long long apt_noEvRxTimeout = 0;

/** The total number of lost Rx frames because of queue full. */
_Atomic unsigned long long apt_noEvRxQueueFull = 0;

/** The total number of recognized E2E validation errors for Rx frames. */
_Atomic unsigned long long apt_noEvRxE2eFailure = 0;

/** The total number of lost Tx frames because of send buffer full events. */
_Atomic unsigned long long apt_noEvTxSendBufFull = 0;


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
    const unsigned int idxFrCde = cde_getIdxFrame(pContext);
    assert(idxFrCde < sizeOfAry(cde_canFrameAry));
    const cde_canFrame_t *const pFrDescCde = &cde_canFrameAry[idxFrCde];

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

    /* Run the frame specific E2E protection method. By side effect, and only on success,
       the data is written into the global API at the same time. (Where nobody will ever
       look for it in this test.) */
    const boolean_t e2eOkay = pFrDescCde->fctUnpackApiFrameAndValidate(frameContents);
    
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
        ++ apt_noEvRxE2eFailure;
        
        /* Report the failure. */
        pFrDescCde->pInfoTransmission->stsTransmission |= cap_stsTransm_errChecksum;
        LOG_FATAL( sup_hGlobalLogger    
                 , "%lu ms: "
                   "%s: E2E validation error in inbound frame %lu on bus %u"
                 , ose_tiSim, __func__
                 , pFrDescCde->canId
                 , pFrDescCde->idxCanBus
                 );
    }
    
    /* In this test, there must never be a data error and there's no APSW, which would
       handle the problem. We report all errors by assertion. */
    assert(e2eOkay);
    
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
    const unsigned int idxFrCde = cde_getIdxFrame(pContext);
    assert(idxFrCde < sizeOfAry(cde_canFrameAry));
    const cde_canFrame_t *const pFrDescCde = &cde_canFrameAry[idxFrCde];

    /* Test: Do some consistency tests. */
    assert(cde_getCanId(pContext) == pFrDescCde->canId
           &&  cde_getIdxBus(pContext) == pFrDescCde->idxCanBus
           &&  pFrDescCde->isReceived
           &&  pFrDescCde->sendMode != cap_enumSendMode_event
           &&  pFrDescCde->pInfoTransmission != NULL
          );
    
    /* Globally count all timeout events. */
    ++ apt_noEvRxTimeout;

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
    const unsigned int idxFrCde = cde_getIdxFrame(pContext);
    assert(idxFrCde < sizeOfAry(cde_canFrameAry)  &&  idxFrCde < CDE_NO_CAN_FRAMES_RECEIVED);
    const cde_canFrame_t *const pFrDescCde = &cde_canFrameAry[idxFrCde];
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
 * The frame to process is identified by its index in the CAN interface engine. At the same
 * time the index into the global table of frame descriptors, cde_canFrameAry.
 */
static void protectAndSendFrame(const unsigned int idxFrCde)
{
    assert(idxFrCde < sizeOfAry(cde_canFrameAry));
    const cde_canFrame_t *pFrDescCde = &cde_canFrameAry[idxFrCde];
    assert(!pFrDescCde->isReceived);

    /* Do the E2E protection of the APSW computed values in the global CAN interface:
       Compute the checksum - if there is any. */
    if(pFrDescCde->fctProtectApiFrame != NULL)
        pFrDescCde->fctProtectApiFrame();
    
    /* Pack the frame. */
    uint8_t frameContent[pFrDescCde->DLC];
    pFrDescCde->fctPackApiFrame(&frameContent[0]);

#if 0
    /* Self test of test application: This should lead to a reported E2E validation error
       after a while. */
    if(BOOL_RAND(1e-3 / CDE_NO_CAN_FRAMES_SENT))
    {
        LOG_ERROR( sup_hGlobalLogger    
                 , "%lu ms: "
                   "%s: Inject error in frame %lu on bus %u"
                 , ose_tiSim, __func__
                 , pFrDescCde->canId
                 , pFrDescCde->idxCanBus
                 );
        assert(pFrDescCde->DLC > 0);
        ++ frameContent[pFrDescCde->DLC-1];
    }
#endif

    /* Invoke the operating system API to submit the frame for sending.
         The OS handle of the frame is the index in the OSE owned configuration table. The
       mapping from CAN interface index to OS handle is a simple offset operation. This
       is a simple and efficient descision, which has been taken in the call of the
       registration method. */
    assert(pFrDescCde->pInfoTransmission != NULL);
    if(ose_sendCanFrame( /* idxFrameOs */ CDE_MAP_HANDLE_SENT_FRAME_CAN_IF_TO_OS(idxFrCde)
                       , &frameContent[0]
                       , pFrDescCde->DLC
                       )
      )
    {
        /* Reset the error status if we were able to put the frame into the send queue. */
        pFrDescCde->pInfoTransmission->stsTransmission &= ~cap_stsTransm_errSendBufferFull;
    
        /* The transmission event is only counted in case of success. This can be decided
           differently but it is consistent with the counting of received frames */
        ++ pFrDescCde->pInfoTransmission->noTransmittedFrames;
    }
    else
    {
        /* Count the frames, which are lost due to queue full. */
        ++ apt_noEvTxSendBufFull;

        pFrDescCde->pInfoTransmission->stsTransmission |= cap_stsTransm_errSendBufferFull;
        LOG_DEBUG( sup_hGlobalLogger    
                 , "%lu ms: "
                   "%s: Failed to send frame %lu on bus %u"
                 , ose_tiSim, __func__
                 , pFrDescCde->canId
                 , pFrDescCde->idxCanBus
                 );
    }
    
    /* Count all frames, which should have been sent. */
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
    const unsigned int idxFrCde = cde_getIdxFrame(pContext);
    assert(idxFrCde >= CDE_NO_CAN_FRAMES_RECEIVED  &&  idxFrCde < CDE_NO_CAN_FRAMES);
    const cde_canFrame_t * const pFrDescCde = &cde_canFrameAry[idxFrCde];

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
    const unsigned int idxFrCde = cde_getIdxFrame(pContext);
    assert(idxFrCde >= CDE_NO_CAN_FRAMES_RECEIVED  &&  idxFrCde < CDE_NO_CAN_FRAMES);
    const cde_canFrame_t * const pFrDescCde = &cde_canFrameAry[idxFrCde];

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
    assert(cde_getIdxFrame(pContext) < sizeOfAry(cde_canFrameAry));
    const cde_canFrame_t *pFrDescCde = &cde_canFrameAry[cde_getIdxFrame(pContext)];

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

void apt_irqHandlerRxCan( unsigned int idxFrameOs
                        , const unsigned char *pMsgContent
                        , unsigned int DLC
                        )
{
    /* Note, this is a callback from the operating system and not a dispatcher callback.
       The CDE API is not available here to access frame properties. */

    /* The OS reports the received frame with its own handle. The postEvent method can do
       the mapping from this handle (and maybe the CAN bus selection) to the frame index of
       the the dispatcher engine implementation. In this sample is the mapping of the
       handles made explicitly visible outside the CAN interface methods. */
    const unsigned int idxFrameCde = CDE_MAP_HANDLE_RECEIVED_FRAME_OS_TO_CAN_IF(idxFrameOs);

    /* The OS handle of the frame is specified to be the index into the configuration
       table. This gives us access to the frame properties. */
    assert(idxFrameOs < ose_noReceivedCanFrames);
    const ose_receivedCanFrame_t * const pFrDesc = &ose_receivedCanFrameAry[idxFrameOs];
    
    LOG_DEBUG( sup_hGlobalLogger    
             , "%lu ms: "
               "apt_irqHandlerRxCan: Frame %lu received (ID: %lu, %u Byte)"
             , ose_tiSim
             , idxFrameOs
             , pFrDesc->canId
             , (unsigned)DLC    
             );
             
    /* Having the CAN interface handle of the received frame, we can post a frame received
       event to the dispatcher. If no internal mapping is configured then the bus index
       specified here doesn't care and the parameter osHandle is taken as CDE index. */
    boolean_t success = cde_postFrameEvent( /* idxBus */ UINT_MAX
                                          , /* osHandle */ idxFrameCde
                                          , /* kindOfEvent */ CDE_EV_FRAME_RECEPTION
                                          , /* pData */ pMsgContent
                                          , /* sizeOfData */ DLC
                                          );
    if(!success)
    {
        /* Count all received frames, which are lost because of queue full. */
        ++ apt_noEvRxQueueFull;
        
        LOG_DEBUG( sup_hGlobalLogger    
                 , "%lu ms: "
                   "apt_irqHandlerRxCan: "
                   "Dispatcher queue full, can't post received event for frame"
                   " with handle %lu (OS) (ID: %lu, %u Byte)"
                 , ose_tiSim
                 , idxFrameOs
                 , pFrDesc->canId
                 , (unsigned)DLC    
                 );
    }
    
    /* Count all received frames. */
    ++ apt_noRxFrames;
    
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
#ifdef DEBUG
    boolean_t initOk;
#endif

    /* Initialize the modules. */
    static char heapMemoryForCanInterface[APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    mem_initModule( /* pAppMemory */ heapMemoryForCanInterface
                  , /* sizeOfAppMemory */ sizeof(heapMemoryForCanInterface)
                  );

    /* In any real project, the initialization of the CAN interface belongs completely in
       the APSW or - even more likely - the integration code. In this test application,
       however, the implementation of the operating system emulation makes use of the CAN
       interface objects, too. Therefore we have to consider the demands of the module OSE,
       when creating the interface. */
#ifdef DEBUG
    initOk =
#endif
    cde_initModule( /* maxNoBuses */  0 + OSE_NO_BUS_OBJS_IN_CAN_INTERFACE
                  , /* maxNoFrames */ CDE_NO_CAN_FRAMES + OSE_NO_FRAME_OBJS_IN_CAN_INTERFACE
                  , /* noDispachers */ 2 + OSE_NO_DISPATCHER_OBJS_IN_CAN_INTERFACE
                  );
    assert(initOk);

    /* Initialize the global data of this module. */
    unsigned int u;
    for(u=0; u<sizeOfAry(_hTimerInTimeoutAry); ++u)
        _hTimerInTimeoutAry[u] = CDE_INVALID_TIMER_HANDLE;
    for(u=0; u<sizeOfAry(_hdlCtxDataOutMixedAry); ++u)
    {
        _hdlCtxDataOutMixedAry[u].hTimerDueCheck = CDE_INVALID_TIMER_HANDLE;
        _hdlCtxDataOutMixedAry[u].hTimerTimeout = CDE_INVALID_TIMER_HANDLE;
    }
    
    /* Create the required dispatcher queues. */
#ifdef DEBUG
    initOk =
#endif
    cde_createDispatcher( /* idxQueue */ APT_IDX_DISPATCHER_10MS
                        , /* maxQueueLength */ APT_DISPATCHER_10MS_QUEUE_LEN
                        , /* sizeOfElement */ 8
                        , /* tiTick */ 10 /* ms */
                        );
    assert(initOk);
#ifdef DEBUG
    initOk =
#endif
    cde_createDispatcher( /* idxQueue */ APT_IDX_DISPATCHER_100MS
                        , /* maxQueueLength */ APT_DISPATCHER_100MS_QUEUE_LEN
                        , /* sizeOfElement */ 8
                        , /* tiTick*/ 100 /* ms */
                        );
    assert(initOk);

    /* Register all frames at the dispatcher engine. The inbound frames are registered
       first: The operating system uses the indexes into the external, auto-coded frame
       specification tables as handles. These tables are separate for in- and outbound
       frames. If we register the frames in the same order then we get for inbound frames
       an identity between OS and CDE handles and a simple offset based relationship for
       the outbound frames. */
    unsigned int hOsFrame, idxFrCde;
    for( hOsFrame = 0, idxFrCde = 0
       ; idxFrCde < CDE_NO_CAN_FRAMES_RECEIVED
       ; ++ hOsFrame, ++ idxFrCde
       )
    {
        assert(idxFrCde < sizeOfAry(cde_canFrameAry)  &&  hOsFrame < ose_noReceivedCanFrames);
        const cde_canFrame_t *const pFrDescCde = &cde_canFrameAry[idxFrCde];

        /* The never received bit is initially set in the transmission status. All other
           status bits are cleared. */
        pFrDescCde->pInfoTransmission->stsTransmission = cap_stsTransm_neverReceived;
    
        /* We have some redundancy since the OS CAN registration tables partly hold the
           same information about frames as our APSW owned data tables. We can put an
           assertion to double-check the strict synchronicity of both tables. */
        assert(ose_receivedCanFrameAry[hOsFrame].idxCanBus == pFrDescCde->idxCanBus
               &&  ose_receivedCanFrameAry[hOsFrame].canId == pFrDescCde->canId
              );

        /* Choice of appropriate dispatcher: The slowest clocked reasonably possible
           dispatcher should be used to minimize computation overhead. We have a 10ms and a
           100ms clocked dispatcher. The frames are separated by their timing. Regular
           frames are rated by cycle time. Event triggered frames are rated by their
           minimum distance time, which is a measure for the expected latency of
           processing. */
        const unsigned int idxDispatcher = asw_getAssociatedTaskOfFrame(pFrDescCde) == 10
                                           ? APT_IDX_DISPATCHER_10MS
                                           : APT_IDX_DISPATCHER_100MS;
        assert(idxDispatcher == APT_IDX_DISPATCHER_10MS
               ||  asw_getAssociatedTaskOfFrame(pFrDescCde) == /* tiTaskCycle */ 100
              );

#ifdef DEBUG
        unsigned int idxCde =
#endif
        cde_registerFrame( pFrDescCde->canId
                         , /* isInbound */ true
                         , pFrDescCde->idxCanBus
                         , /* osHandleFrame */ hOsFrame
                         , idxDispatcher
                         , /* callback */ onInitReceivedFrames
                         );
        assert(idxCde == idxFrCde
               &&  idxCde == CDE_MAP_HANDLE_RECEIVED_FRAME_OS_TO_CAN_IF(hOsFrame)
              );
    } /* for(All inbound frames) */
    
    assert(idxFrCde == CDE_NO_CAN_FRAMES_RECEIVED);
    for( hOsFrame = 0
       ; idxFrCde < CDE_NO_CAN_FRAMES
       ; ++ hOsFrame, ++ idxFrCde
       )
    {       
        assert(idxFrCde < sizeOfAry(cde_canFrameAry)  &&  hOsFrame < ose_noSentCanFrames);
        const cde_canFrame_t *const pFrDescCde = &cde_canFrameAry[idxFrCde];

        /* We have some redundancy since the OS CAN registration tables partly hold the
           same information about frames as our APSW owned data tables. We can put an
           assertion to double-check the strict synchronicity of both tables. */
        assert(ose_sentCanFrameAry[hOsFrame].idxCanBus == pFrDescCde->idxCanBus
               &&  ose_sentCanFrameAry[hOsFrame].canId == pFrDescCde->canId
              );

        /* Choice of appropriate dispatcher: The slowest clocked reasonably possible
           dispatcher should be used to minimize computation overhead. We have a 10ms and a
           100ms clocked dispatcher. The frames are separated by their timing. Regular
           frames are rated by cycle time. Event triggered frames are rated by their
           minimum distance time, which is a measure for the expected latency of
           processing. */
        const unsigned int idxDispatcher = asw_getAssociatedTaskOfFrame(pFrDescCde) == 10
                                           ? APT_IDX_DISPATCHER_10MS
                                           : APT_IDX_DISPATCHER_100MS;
        assert(idxDispatcher == APT_IDX_DISPATCHER_10MS
               ||  asw_getAssociatedTaskOfFrame(pFrDescCde) == /* tiTaskCycle */ 100
              );
              
#ifdef DEBUG
        unsigned int idxCde =
#endif
        cde_registerFrame( pFrDescCde->canId
                         , /* isInbound */ false
                         , pFrDescCde->idxCanBus
                         , /* osHandleFrame */ hOsFrame
                         , idxDispatcher
                         , /* callback */ onInitSendFrames
                         );
        assert(idxCde == idxFrCde
               &&  CDE_MAP_HANDLE_SENT_FRAME_CAN_IF_TO_OS(idxCde) == hOsFrame
              );
    } /* for(All outbound frames) */

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
    cde_dispatcherMain(APT_IDX_DISPATCHER_10MS);

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
    cde_dispatcherMain(APT_IDX_DISPATCHER_100MS);

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
        assert(_hTimerInTimeoutAry[u] != CDE_INVALID_TIMER_HANDLE);
    for(u=0; u<sizeOfAry(_hdlCtxDataOutMixedAry); ++u)
    {
        assert(_hdlCtxDataOutMixedAry[u].hTimerDueCheck != CDE_INVALID_TIMER_HANDLE
               &&  _hdlCtxDataOutMixedAry[u].hTimerTimeout != CDE_INVALID_TIMER_HANDLE
              );
    }
#endif    

    unsigned int noEvQFull10ms = cde_getNoDispatcherQueueFullEvents( APT_IDX_DISPATCHER_10MS
                                                                   , /* reset */ true
                                                                   )
               , noEvQFull100ms = cde_getNoDispatcherQueueFullEvents( APT_IDX_DISPATCHER_100MS
                                                                    , /* reset */ true
                                                                    );
#ifdef _STDC_VERSION_C11
    assert(cde_getNoDispatcherQueueFullEvents(APT_IDX_DISPATCHER_10MS, false) == 0
           &&  cde_getNoDispatcherQueueFullEvents(APT_IDX_DISPATCHER_10MS, false) == 0
          );
#endif
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
              "Consumed memory of CAN heap: %u Byte in %u chunks, remaining heap memory:"
              " %u Byte"
            , ose_tiSim
            , mem_getNbrOfAllocatedBytes() 
            , mem_getNbrOfAllocatedChunks() 
            , mem_getNbrOfAvailableBytes() 
            );
    if(mem_getNbrOfAllocatedBytes() < APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE)
    {
        LOG_WARN( sup_hGlobalLogger    
                , "%lu ms: "
                  "apt_taskShutdown: "
                  "Size of CAN heap could be decreased by %u Byte"
                , ose_tiSim
                , APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE - mem_getNbrOfAllocatedBytes()
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





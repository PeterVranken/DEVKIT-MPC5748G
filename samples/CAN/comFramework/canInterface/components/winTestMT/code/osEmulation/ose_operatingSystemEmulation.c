/**
 * @file ose_operatingSystemEmulation.c
 * Simulation of those parts of an operating system, which are required in the context of
 * the CAN interface. The simulation is simple but it's sufficient to connect to all API
 * functions and to run through all the code and to demonstrate the way the CAN interface
 * works and how it has to be integrated in a real system.
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
 *   ose_kernel
 *   ose_installTask
 *   ose_installIrqHandlerCanRx
 *   ose_sendCanFrame
 * Local functions
 *   logCanFrame
 *   onSimulateReceptionOfRegularFrame
 *   onSimulateReceptionOfEventFrame
 *   onSimulateReceptionOfMixedFrame
 *   onInitSimulationReceiveFrame
 *   onEventSendDispatcher
 *   initCANBusSimulation
 *   shutdownCANBusSimulation
 *   runSingleThreadedScheduler
 *   taskOSInternal
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <assert.h>
#ifdef __WINNT__
# include <conio.h>
#endif

#include "smalloc.h"
#include "log_logger.h"
#include "opt_getOpt.h"
#include "fil_file.h"
#include "sup_startup.h"
#include "rtos_rtosEmulation.h"
#include "cde_canDispatcherEngine.h"
#include "cde_canStatistics.h"
#include "cap_canApi.h"
#include "e2e_frameProtection.h"
#include "cde_canDispatcherEngine.h"
#include "ose_operatingSystemEmulation.h"


/*
 * Defines
 */

/** For development support is possible to replace the normal scheduler from the RTOS
    emulation by some simple, sequential task invokation. If the single thraeded scheduler
    is enabled then the software is basically doing the same but without any danger of race
    conditions and without synchronization with the world time. It'll thus consume 100% of
    the computation time of one CPU core. */
#define USE_SINGLE_THREADED_SCHEDULER   0

/** A signed integer in the range [i, j]. */
#define IRAND(i,j) (rand()%((j)-(i)+1)+(i))

/** A scaled floating point random number in the range [a, b). */
#define RAND(a,b) ((double)((b)-(a))*RND()+(double)(a))

/** A Boolean random number with given probability p of getting a true. */
#define BOOL_RAND(p) (RND()<(p)? true: false)

/** A floating point random number in the range [0;1). */
#define RND() ((double)rand()/(double)RAND_MAX)

/** The index of the dispatcher that serves the outbound frames send from the 10ms APSW
    task. The timer events of this dispatcher are used at the same time to control the
    CAN recepetion simulation.\n
      This index is used at the same time as bus index in the bus related event API of the
    CAN interface. (Which effectively is rather event-source related than bus related. A
    bus is just one possible event source.) */
#define IDX_DISPATCHER_SEND_10MS_AND_RECEIVE    0

/** The index of the dispatcher that serves the outbound frames send from the 100ms APSW
    task.\n
      This index is used at the same time as bus index in the bus related event API of the
    CAN interface. (Which effectively is rather event-source related than bus related. A
    bus is just one possible event source.) */
#define IDX_DISPATCHER_SEND_100MS               1

/** The length of the queue of the dispatcher that serves the Tx frames send from the
    10ms APSW task. The timer events of this dispatcher are used at the same time to
    control the CAN recepetion simulation. */
#define DISPATCHER_SEND_10MS_AND_RECEIVE_QUEUE_LEN  CDE_NO_CAN_FRAMES_SENT

/** The length of the queue of the dispatcher that serves the Tx frames send from the
    100ms APSW task. */
#define DISPATCHER_SEND_100MS_QUEUE_LEN             CDE_NO_CAN_FRAMES_SENT

/** The CAN send interface uses a self-defined event to notify each frame for sending. */
#define EV_FRAME_SUBMITTED_FOR_SENDING      ((CDE_EV_FIRST_CUSTOM_EVENT)+0)

/** The name of the CAN log file with simulated CAN traffic. Without extension, different
    formats are offered and the right extension will be appended. */
#define CAN_LOG_FILE_NAME SUP_APP_NAME "_CAN" ".m"

/** The CAN log can either be a human readable ASCII file or an executable Ocatve script
    with slightly degarded readability. Comment the define out to get the ASCII format. */
#define USE_OCTAVE_CAN_LOG_FORMAT

/** The maximum number of entries in the CAN log (to avoid exploding file sizes). */
#define CAN_LOG_MAX_NO_ENTRIES 250000ul

/** If Octave log is chosen: The name of an Octave matrix holding all logged data. */
#define OCATVE_NAME_OF_MTX  "canLog"

/** The size of an array object in number of elements. The index into the array needs to be
    lower than the returned value. */
#define sizeOfAry(a) (sizeof(a)/sizeof(a[0]))


/*
 * Local type definitions
 */

/** A CAN frame send event. A dispatcher queue is used to propagate this event thread-safe
    from the sending APSW funtion to the simulation of CAN sending in this OS emulation.\n
      The event contains all required frame data like bus index, ID and data contents. */
typedef struct eventSendFrame_t
{
    /** The CAN bus to send the frame on. */
    unsigned int idxCanBus;

    /** The CAN ID. */
    uint32_t canId;

    /** The number of bytes to send. */
    unsigned int noBytes;

    /** The data contents. */
    uint8_t frameContents[8];

} eventSendFrame_t;



/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** The simulation time in ms. */
_Atomic volatile unsigned long ose_tiSim = 0;

/** The CAN reception IRQ handler. */
static ose_irqHandlerCanRx_t _irqHandlerCanRx = NULL;

/** Array of task function pointers or NULL if task is not installed. */
static ose_task_t _taskAry[ose_noTaskTypes] = {[ose_noTaskTypes-1] = NULL};

/** The CAN log file. */
static FILE *_logCanData = NULL;

/** Termination condition by simulated time: At this time in ms since application start
    should the real time simulation end. A value of zero means infinite. */
static unsigned long _tiSimEnd = 0;

/** The dispatcher queues used internally by the OS emulation don't make use of the handle
    mapping table support of the CAN interface. Instead, they exploit the knowledge, that
    the different handle sets are by principle indetical besides a constant, known offset.
    Instead of a complex mapping function only this index offset is added or subtracted.\n
      Here, we have the offset for the handles of the emulated inbound frames. */
static unsigned int _offsetIdxCdeToTableOfReceivedFrames = 0;

/** The dispatcher queues used internally by the OS emulation don't make use of the handle
    mapping table support of the CAN interface. Instead, they exploit the knowledge, that
    the different handle sets are by principle indetical besides a constant, known offset.
    Instead of a complex mapping function only this index offset is added or subtracted.\n
      Here, we have the offset for the handles of the emulated outbound frames. */
static unsigned int _offsetIdxCdeToTableOfSentFrames = 0;

/** The handlers for frames with timing pattern mixed requires some local, frame related
    data. It is kept in this array. */
static struct hdlCtxDataRxMixed_t
{
    /** The handle of the due check timer. */
    cde_handleTimer_t hTimerDueCheck;
    
    /** The handle of the timeout timer. */
    cde_handleTimer_t hTimerTimeout;
    
} _hdlCtxDataRxMixedAry[CDE_NO_CAN_FRAMES_RECEIVED_MIXED];


/*
 * Function implementation
 */


/**
 * Open the CAN log file.
 *   @return Get the Boolean success message, get \a false if open failed.
 */
static boolean_t openCanLog()
{
    assert(_logCanData == NULL);
    _logCanData = fopen(CAN_LOG_FILE_NAME, "wt");
    if(_logCanData != NULL)
    {
#ifdef USE_OCTAVE_CAN_LOG_FORMAT
# define OCTAVE_HEADER                                                                  \
"% CAN log of application " SUP_APP_NAME ", version " SUP_SW_REV "\n"                   \
"\n"                                                                                    \
"% Meaning of columns:\n"                                                               \
"colTiWorld = 1; % Index of the column holding the world time in s since start of"      \
                                                                      " application.\n" \
"colTiSim = 2; % Simulation time in ms, counts of invokations of 1 ms task.\n"          \
"colBus = 3; % The index of the CAN bus.\n"                                             \
"colDir = 4; % Transmission direction. Boolean, true means a frame reception event.\n"  \
"colID = 5; % The CAN ID of the frame.\n"                                               \
"colDLC = 6; % Number of frame content bytes, the data length code.\n"                  \
"colByte0 = 7; % The first content byte or NaN if there is no content byte.\n"          \
"colContent = 7:14; % Use this to column index all frame content bytes of the frame.\n" \
"\n"

        fputs(OCTAVE_HEADER, _logCanData);
# undef OCTAVE_HEADER

        /* Ocatve script: Statement to begin a matrix definition. */
        fputs(OCATVE_NAME_OF_MTX " = [\n", _logCanData);
#endif
        return true;
    }
    else
    {
        LOG_ERROR( sup_hGlobalLogger
                 , "%s: Can't open CAN log file " CAN_LOG_FILE_NAME " for writing. No"
                   " CAN log will be available"
                 , __func__
                 );
        return false;
    }


} /* End of closeCanLog */


/**
 * Close the CAN log file.
 */
static void closeCanLog()
{
    assert(_logCanData != NULL);

#ifdef USE_OCTAVE_CAN_LOG_FORMAT
    /* Ocatve script: Close the matrix and append some useful convenience code. */
# define OCTAVE_APPENDIX                                                                \
"setOfCanBuses = unique(canLog(:,colBus));\n"                                           \
"setOfCanIDs = unique(canLog(:,colID));\n"                                              \
"for canBus = setOfCanBuses(:)'\n"                                                      \
"    for canId = setOfCanIDs(:)'\n"                                                     \
"        idxRow = find(canLog(:,colBus) == canBus  &  canLog(:,colID) == canId);\n"     \
"        if isempty(idxRow)\n"                                                          \
"            continue\n"                                                                \
"        end\n"                                                                         \
"        canLogOfId = canLog(idxRow,:);\n"                                              \
"        if canLog(idxRow(1),colDir)\n"                                                 \
"            idName = 'R';\n"                                                           \
"        else\n"                                                                        \
"            idName = 'T';\n"                                                           \
"        end\n"                                                                         \
"        idName = sprintf('_%s%i_%04i', idName, canBus, canId);\n"                      \
"        eval(sprintf('canLog%s = canLogOfId;', idName));\n"                            \
"        eval(sprintf('tiWorld%s = canLogOfId(:,colTiWorld);', idName));\n"             \
"        eval(sprintf('tiSim%s = canLogOfId(:,colTiSim);', idName));\n"                 \
"    end\n"                                                                             \
"end\n"                                                                                 \
"clear canId idxRow idName canLogOfId\n"                                                \
"disp(['Find the complete log data as canLog and access the fields of an entry' ...\n"  \
"      ' using the column indexes col*:']\n"                                            \
"    )\n"                                                                               \
"whos canLog col*\n"

    fputs("];\n\n" OCTAVE_APPENDIX, _logCanData);
# undef OCTAVE_APPENDIX
#endif

    fclose(_logCanData);
    _logCanData = NULL;

} /* End of closeCanLog */



/**
 * Log a transmitted CAN frame.
 *   @param isReceived
 * The transmission direction.
 *   @param idxCanBus
 * The CAN bus (by index) the frame is transmitted on.
 *   @param canId
 * The CAN ID of the frame.
 *   @param pData
 * The frame contents, already byte encoded.
 *   @param DLC
 * The number of bytes to send out.
 */

static void logCanFrame( boolean_t isReceived
                       , unsigned int idxCanBus
                       , uint32_t canId
                       , const uint8_t *pData
                       , unsigned int DLC
                       )
{
    if(_logCanData != NULL)
    {
        static unsigned long noLines_ = 0;
#ifdef USE_OCTAVE_CAN_LOG_FORMAT
        fprintf( _logCanData
               , "  %15.6f %10lu %1u % 5s %4lu %u"
               , rtos_getTime()
               , ose_tiSim
               , idxCanBus
               , isReceived? "true": "false"
               , canId
               , DLC
               );
#else
        fprintf( _logCanData
               , "%15.6f s - %10lu ms - %1u - %cx - ID %4lu - DLC %u -"
               , rtos_getTime()
               , ose_tiSim
               , idxCanBus
               , isReceived? 'R': 'T'
               , canId
               , DLC
               );
#endif
        unsigned int idxByte;
        for(idxByte=0; idxByte<DLC; ++idxByte)
        {
#ifdef USE_OCTAVE_CAN_LOG_FORMAT
            /* Here, MATLAB would require either a decimal number or an enclosing pair
               hex2dec(' and '). The latter makes reading the file however really slow. */
            fprintf(_logCanData, " 0x%02X", (unsigned)pData[idxByte]);
#else
            fprintf(_logCanData, " %02X", (unsigned)pData[idxByte]);
#endif
        }
#ifdef USE_OCTAVE_CAN_LOG_FORMAT
        /* Octave requires always same number of elements in each line. We fill missing
           matrix elements with a NaN. */
        assert(DLC <= 8);
        for(; idxByte<8; ++idxByte)
            fprintf(_logCanData, "  NaN");
#endif
        fprintf(_logCanData, "\n");
        fflush(_logCanData);

        /* Limit the size of the file - this application is intented an inifinitly running
           test. */
        if(++noLines_ >= CAN_LOG_MAX_NO_ENTRIES)
        {
            closeCanLog();
            LOG_WARN( sup_hGlobalLogger
                    , "%s: CAN log " CAN_LOG_FILE_NAME " is closed after %lu entries"
                      " to avoid a too large file size. Further CAN traffic won't be"
                      " recorded any more"
                    , __func__
                    , CAN_LOG_MAX_NO_ENTRIES
                    );
        }
    }
    /* For simplicity: File is closed by end of application run. */

} /* End of logCanFrame. */



/**
 * Simluate a frame reception event for a single frame.
 *   @param idxFrOs
 * The OS handle or index into the configuration table for inbound frames. This handle
 * determines the frame, which the reception event is simulated for.
 */
static void simulateFrameReception(unsigned int idxFrOs)
{
    assert(idxFrOs < ose_noReceivedCanFrames);
    const ose_receivedCanFrame_t * const pFrDescOs = &ose_receivedCanFrameAry[idxFrOs];

    /* This is a test: There's no CAN bus and no far communication peer, who produces the
       frame contents. Instead, we call here a test helper function that fills the signal
       values randomly and does the E2E protection at the same time. */
    uint8_t frameContent[pFrDescOs->DLC];
    pFrDescOs->fctGetFrameContents(&frameContent[0]);

#if 0
    /* Self test of test application: This should lead to a reported E2E validation error
       after a while. */
    if(BOOL_RAND(1e-3 / CDE_NO_CAN_FRAMES_RECEIVED))
    {
        LOG_ERROR( sup_hGlobalLogger    
                 , "%lu ms: "
                   "%s: Inject error in frame %lu on bus %u"
                 , ose_tiSim, __func__
                 , pFrDescOs->canId
                 , pFrDescOs->idxCanBus
                 );
        assert(pFrDescOs->DLC > 0);
        ++ frameContent[pFrDescOs->DLC-1];
    }
#endif

    /* A reception event is simulated. Invoke the CAN reception callback, which would
       be the CAN interrupt in a true system. The integration code has installed its
       own handler code. Here we just see the function pointer. */
    if(_irqHandlerCanRx != NULL)
    {
        logCanFrame( /* isReceived */ true
                   , pFrDescOs->idxCanBus
                   , pFrDescOs->canId
                   , &frameContent[0]
                   , pFrDescOs->DLC
                   );
        _irqHandlerCanRx(idxFrOs, &frameContent[0], pFrDescOs->DLC);
    }
    else
    {
        /* The application is useless otherwise, assertion as warning. */
        assert(false);
    }
} /* End of simulateFrameReception */




/**
 * Shared callback for the timer of all simulated inbound regular frames.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onSimulateReceptionOfRegularFrame(const cde_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(cde_isInboundTransmission(pContext)
           &&  cde_getKindOfEvent(pContext) == CDE_TIMER_ELAPSED
          );

    /* Simulation of frame reception using some random data.
         cde_getOsHandleFrame: The OS handle of the frame is the index in the OSE owned
       configuration table. This is a simple and efficient descision, which has been taken
       in the call of the registration method. */
    simulateFrameReception(cde_getOsHandleFrame(pContext));

} /* End of onSimulateReceptionOfRegularFrame */



/**
 * Shared callback for the timer of all simulated inbound event frames.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onSimulateReceptionOfEventFrame(const cde_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(cde_isInboundTransmission(pContext)
           &&  cde_getKindOfEvent(pContext) == CDE_TIMER_ELAPSED
          );

    /* The event character of this frame is simulated by a simple Boolean random decision
       every time we get in this callback. */
    const boolean_t isEvent = BOOL_RAND(2e-3);

    signed int tiNewFromNow;
    if(isEvent)
    {
        /* Simulation says: Event happened - simulate reception. */

        /* Simulation of frame reception using some random data. */
        const unsigned int idxFrOs = cde_getOsHandleFrame(pContext);
        simulateFrameReception(idxFrOs);
        
        /* The OS handle of the frame is the index in the OSE owned configuration table.
           This is a simple and efficient descision, which has been taken in the call of
           the registration method. */
        assert(idxFrOs < ose_noReceivedCanFrames);
        const ose_receivedCanFrame_t * const pFrDescOs = &ose_receivedCanFrameAry[idxFrOs];

        /* The timer when the timer should fire the next time depends. We had an event in
           this tick, so we need to regard the minimum distance. */
        tiNewFromNow = pFrDescOs->tiMinDistance;
    }
    else
    {
        /* The time when the timer should fire the next time depends. We had no event this
           time and will test the Boolean decision immediately again in the next tick. */
        tiNewFromNow = 1;
    }

    /* The time when the timer should fire the next time depends. If we had an event in
       this tick then we need to regard the minimum distance. Otherwise we test the Boolean
       decision immediately again in the next tick. */
    cde_retriggerSingleShotTimer( pContext
                                , /* hTimer */ NULL /* this timer */
                                , tiNewFromNow
                                );
} /* End of onSimulateReceptionOfEventFrame */



/**
 * Shared callback for the normal timer of all simulated inbound frames of transmission
 * pattern "mixed".
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onSimulateReceptionOfMixedFrame(const cde_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(cde_isInboundTransmission(pContext)
           &&  cde_getKindOfEvent(pContext) == CDE_TIMER_ELAPSED
          );

    /* The handler for mixed mode Rx frames requires some frame-related, local data. Itis
       held in a global table and the index into this table is stored in the timers'
       context data.
         Note, the code to access the data is platform dependent yet safe since it will
       yield a compile time error on machines where it wouldn't work. You would have to
       adjust the data type on such a machine. */
    unsigned int idxCtxData = 0;
    _Static_assert(sizeof(idxCtxData) == sizeof(void*), "Adjust platform dependent data type");
    unsigned int sizeOfCtxData;
    cde_getEventData(pContext, &sizeOfCtxData, (const void**)&idxCtxData);
    assert(sizeOfCtxData == sizeof(idxCtxData)
           &&  idxCtxData < sizeOfAry(_hdlCtxDataRxMixedAry)
          );
    const struct hdlCtxDataRxMixed_t * const pHdlCtxData = &_hdlCtxDataRxMixedAry[idxCtxData];

    /* This callback is shared between both timers involved in the control of a mixed mode
       frame. We need to know, which event it was and do a comparison on the timer handle
       to find out. */
    assert(pHdlCtxData->hTimerDueCheck != CDE_INVALID_TIMER_HANDLE
           &&  pHdlCtxData->hTimerTimeout != CDE_INVALID_TIMER_HANDLE
          );
    const boolean_t isTimerCheckForEv = cde_getHandleTimer(pContext) 
                                        == pHdlCtxData->hTimerDueCheck;
    assert(isTimerCheckForEv ||  cde_getHandleTimer(pContext) == pHdlCtxData->hTimerTimeout);

    /* The event character of this frame is simulated by a simple Boolean random decision
       every time we get in this callback. We have a sure reception event if this callback
       was triggered by the timeout. */
    const boolean_t isEvent = !isTimerCheckForEv || BOOL_RAND(2e-3);

    signed int tiNewCheckFromNow;
    if(isEvent)
    {
        /* Simulation say: Event happened - simulate reception. */

        /* Simulation of frame reception using some random data. */
        const unsigned int idxFrOs = cde_getOsHandleFrame(pContext);
        simulateFrameReception(idxFrOs);
        
        /* The OS handle of the frame is the index in the OSE owned configuration table.
           This is a simple and efficient descision, which has been taken in the call of
           the registration method. */
        assert(idxFrOs < ose_noReceivedCanFrames);
        const ose_receivedCanFrame_t * const pFrDescOs = &ose_receivedCanFrameAry[idxFrOs];

        /* The time when the timer should fire the next time depends. We had an event in
           this tick, so we need to regard the minimum distance. */
        tiNewCheckFromNow = pFrDescOs->tiMinDistance + IRAND(-1,2);

        /* We have an reception event in this tick so the timeout counts entirely from
           new. */
        cde_retriggerSingleShotTimer( pContext
                                    , /* hTimer */ pHdlCtxData->hTimerTimeout
                                    , pFrDescOs->tiCycle
                                    );
    }
    else
    {
        /* The time when the timer should fire the next time depends. We had no event this
           time and will test the Boolean decision immediately again in the next tick. */
        tiNewCheckFromNow = 1;
    }

    /* The timer when the timer should fire the next time depends. If we had an event in
       this tick then we need to regard the minimum distance. Otherwise we test the Boolean
       decision immediately again in the next tick. */
    cde_retriggerSingleShotTimer( pContext
                                , /* hTimer */ pHdlCtxData->hTimerDueCheck
                                , tiNewCheckFromNow
                                );
} /* End of onSimulateReceptionOfMixedFrame */



/**
 * The initialization callback for a registered inbound frame. We use the initialization
 * callback to initiate the simulation timing. One or more timers are created, which will
 * then trigger all required actions for the given frame.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in. It is the context of the
 * frame being registered.
 */

static void onInitSimulationReceiveFrame(const cde_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(cde_isInboundTransmission(pContext)
           &&  cde_getKindOfEvent(pContext) == CDE_EV_FRAME_INIT
          );

    /* The OS handle of the frames is the index in the OSE owned configuration table. This
       is a simple and efficient descision, which has been taken in the call of the
       registration method.
         Note, here we use another, equivalent way to get the OS handle of the frame as in
       the send simulation path. */
    const unsigned int idxFrOs = cde_getOsHandleFrame(pContext);
    assert(idxFrOs < ose_noReceivedCanFrames);
    const ose_receivedCanFrame_t * const pFrDescOs = &ose_receivedCanFrameAry[idxFrOs];

    LOG_DEBUG( sup_hGlobalLogger
             , "%s: Initialization of frame %u on bus %u"
             , __func__
             , cde_getCanId(pContext)
             , cde_getIdxBus(pContext)
             );

    switch(pFrDescOs->sendMode)
    {
        case cap_enumSendMode_regular:
        {
            /* Regular frames are most simple. We apply a regular timer. */
#ifdef DEBUG
            cde_handleTimer_t hTimer =
#endif
            cde_createPeriodicTimer( pContext
                                   , /* tiPeriod */ pFrDescOs->tiCycle + IRAND(-1,1)
                                   , /* callback */ onSimulateReceptionOfRegularFrame
                                   , /* pUserContextData */ NULL
                                   );
            assert(hTimer != CDE_INVALID_TIMER_HANDLE);
            break;
        }
        case cap_enumSendMode_event:
        {
            /* Event frames can become due in every tick but need to regard a minimum
               distance. We use a timer, which fires in every tick. A random Boolean
               descision is take each time in the callback. If it is true and the reception
               event is simulated then the timer is retriggered with the minimum
               distance. */
#ifdef DEBUG
            cde_handleTimer_t hTimer =
#endif
            cde_createSingleShotTimer( pContext
                                     , /* tiFromNow */ 1 /* next tick */
                                     , /* callback */ onSimulateReceptionOfEventFrame
                                     , /* pUserContextData */ NULL
                                     , /* killAtDueTime */ false
                                     );
            assert(hTimer != CDE_INVALID_TIMER_HANDLE);
            break;
        }
        case cap_enumSendMode_mixed:
        {
            /* Event frames with timeout are like event frames but need to be sent at a
               minimum rate even if there's no event. This requires a second timer, the
               timeout timer.
                 The order of creation matters: If both fire in the same tick then the
               callbacks are invoked in creation order. */
            static unsigned int idxNextMixedFrame_ = 0;
            assert(idxNextMixedFrame_ < sizeOfAry(_hdlCtxDataRxMixedAry)
                   &&  _hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerDueCheck
                       == CDE_INVALID_TIMER_HANDLE
                   &&  _hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerTimeout
                       == CDE_INVALID_TIMER_HANDLE
                  );
            _hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerDueCheck =
                            cde_createSingleShotTimer
                                    ( pContext
                                    , /* tiFromNow */ 1 /* next tick */
                                    , /* callback */ onSimulateReceptionOfMixedFrame
                                    , /* pUserContextData */ (void*)idxNextMixedFrame_
                                    , /* killAtDueTime */ false
                                   );
            assert(_hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerDueCheck
                   != CDE_INVALID_TIMER_HANDLE
                  );

            _hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerTimeout =
                            cde_createSingleShotTimer
                                    ( pContext
                                    , /* tiFromNow */ pFrDescOs->tiCycle
                                    , /* callback */ onSimulateReceptionOfMixedFrame
                                    , /* pUserContextData */ (void*)idxNextMixedFrame_
                                    , /* killAtDueTime */ false
                                   );
            assert(_hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerTimeout
                   != CDE_INVALID_TIMER_HANDLE
                  );

            ++ idxNextMixedFrame_;
            break;
        }
        default:
            assert(false);

    } /* switch(Transmission pattern of frame) */
} /* End of onInitSimulationReceiveFrame */




/**
 * Initialize the dispatching process of sent frames. Here, dispatching simply means to
 * take the submitted frames from the queue and to write the CAN ID and the received data
 * into the log file.
 *   @param pContext
 * The callback context, which provides access to event related information.
 *   @remark
 * The implementation of this callback is race-condition free. It is well shared between
 * both dispatchers, but both of them are clocked one after another in the same thread, the
 * internal 1ms task of this OS emulation.
 */

static void onEventSendDispatcher(const cde_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(!cde_isInboundTransmission(pContext));

    switch(cde_getKindOfEvent(pContext))
    {
    case CDE_EV_FRAME_INIT:
        /* Initialization: Nothing to be done since we intend to use the same callback for
           future events, too. An insignificant optimization would be to now install another
           callback, this would remove the need for conditional code that checks the kind
           of event.
             This event is handled in the context of the main thread at system
           initialization time, prior to the beginning of multi-threading. No
           race-conditions must be anticipated. */
        LOG_DEBUG( sup_hGlobalLogger
                 , "%s: Initialization of frame %u on bus %u"
                 , __func__
                 , cde_getCanId(pContext)
                 , cde_getIdxBus(pContext)
                 );
        break;

    case CDE_EV_FRAME_RECEPTION:
      {
        /* The only event at run-time: The APSW has submitted a frame for sending. It has
           submitted the frame using method ose_sendCanFrame.
             This event is handled in the context of the OSE internal CAN simulation
           thread. No race-conditions with other code from this thread must be
           anticipated. */

        /* Retrieve the OS handle, which is the index into the send frame configuration
           table and provide access to the frame descriptor in this table. */
        const unsigned int idxFrCde = cde_getIdxFrame(pContext)
                                      - _offsetIdxCdeToTableOfSentFrames;
        assert(idxFrCde < ose_noSentCanFrames);
        const ose_sentCanFrame_t *pFrDescOs = &ose_sentCanFrameAry[idxFrCde];

        /* Some consistency checks. */
        assert(pFrDescOs->idxCanBus == cde_getIdxBus(pContext)
               &&  pFrDescOs->canId == cde_getCanId(pContext)
              );

        /* For event kind CDE_EV_FRAME_RECEPTION the event's data is the frame contents. */
        unsigned int sizeOfEvData;
        const uint8_t *frameContents;
        cde_getEventData(pContext, &sizeOfEvData, (const void**)&frameContents);
        assert(sizeOfEvData <= 8);

        LOG_DEBUG( sup_hGlobalLogger
                 , "%s: Bus %u, frame %lu (%u Byte): Simulation of sending in OS emulation"
                 , __func__
                 , pFrDescOs->idxCanBus
                 , pFrDescOs->canId
                 , sizeOfEvData
                 );
        logCanFrame( /* isReceived */ false
                   , /* idxCanBus */ pFrDescOs->idxCanBus
                   , /* canId */ pFrDescOs->canId
                   , /* pData */ &frameContents[0]
                   , /* DLC */ sizeOfEvData
                   );

        /* Last action in send simulation: Do the E2E validation: did we receive non
           corrupted data through our queue based inter-thread interface? */
#ifdef DEBUG
        boolean_t e2eOkay =
#endif
        pFrDescOs->fctDoE2eValidation(&frameContents[0]);
        assert(e2eOkay);

        break;
      }
    default:
        /* No other events must ever occur. */
        assert(false);

    } /* End switch(Kind of received event) */
} /* End of onEventSendDispatcher */




/**
 * Initialize the simulation of the CAN transmission.
 *   @return
 * \a true if operation succeeded, \a false in case of out of memory, but \a true is enforced
 * by assertion. (See concept of deterministic, error-free, static memory allocation.)
 *   @remark
 * This method is called in a still race-condition free, single-threaded environment.
 */

static boolean_t initCANBusSimulation()
{
    /* Initialize the global data of this module. */
    unsigned int u;
    for(u=0; u<sizeOfAry(_hdlCtxDataRxMixedAry); ++u)
    {
        _hdlCtxDataRxMixedAry[u].hTimerDueCheck = CDE_INVALID_TIMER_HANDLE;
        _hdlCtxDataRxMixedAry[u].hTimerTimeout = CDE_INVALID_TIMER_HANDLE;
    }
    
    /* Create the required dispatcher engines. */
    boolean_t success = true;
    if(!cde_createDispatcher( /* idxQueue */ IDX_DISPATCHER_SEND_10MS_AND_RECEIVE
                            , /* maxQueueLength */ DISPATCHER_SEND_10MS_AND_RECEIVE_QUEUE_LEN
                            , /* sizeOfElement */ sizeof(eventSendFrame_t)
                            , /* tiTic */ 1 /* ms */
                            )
      )
    {
        success = false;
    }
    if(!cde_createDispatcher( /* idxQueue */ IDX_DISPATCHER_SEND_100MS
                            , /* maxQueueLength */ DISPATCHER_SEND_100MS_QUEUE_LEN
                            , /* sizeOfElement */ sizeof(eventSendFrame_t)
                            , /* tiTic */ 1 /* ms */
                            )
      )
    {
        success = false;
    }

    /* All frames, which have been specified to the operating system in its
       configuration tables are registered at the two dispatchers. This enables easy
       implementation of the simulation timing on the timer API of the dispatcher
       engine.
         For the simulated Rx frames it doesn't really matter, to register at which
       dispatcher. Both are clocked at the same rate and from the same thread. Now
       overhead or concurrency considerations apply. We register all at one dispatcher.
         For the simulated Tx frames is matters. The "real" code, the APSW, uses the
       API ose_sendCanFrame of the OS emulation from different execution threads (10ms
       and 100ms APSW tasks). We need to ensure that the frames of each thread go into
       a dedicated dispatcher - the postEvent method of the dispatcher is thread-safe
       only in a point to point connection, a m:1 connection cannot be implemented
       without serialization code around the call of postEvent.
         Separating the frames according to the submitting threads cannnot be
       implemented properly. The code in the OS emulation depends on the code in the
       APSW and the requirement of having a self-contained OS emulation and a
       self-contained, prototypical APSW implementation is hurt. The improper solution
       is to let both APSW and OS emulation use the identical decision code of
       distributing the frames, distributing between the threads for the APSW and
       distributing between the dispatchers in the OS emulation.
         A proper solution is not aimed. The problem arises only because we use the
       dispatcher engine for a simple implementation of this test (and to raise the
       test depth at the same time). In any real application of the CAN interface, the
       dispatcher wouldn't be applied for both, APSW and OS. */

    /* Handling of handles: There's only one dispatcher engine with a contiguous handle
       space for all registered frames. APSW and OS emulation share this space. The
       dispatcher engine specifies to use a linear, zero based index as handles for the
       frames. The indexes are provided in the order of frame registration. This
       definition of a handle makes handle mapping between dispatcher and OS in most of
       the cases a trivial operation, either an identity or just adding an offset. This
       holds for our OS emulation, too. The OS emulation has two
       configuration tables for processed frames, separate for in- and outbound frames.
       The tables are user-filled (implemented by auto-coding), therefore it is under
       control of the APSW to register the frames in the same order as it fills the
       configuration tables. If the OS emulation registers the frames in the order of
       its configuration tables, than we have anywhere same index/handle orders. The
       offsets can be different for each block of registration, in- and outbound, but
       not inside such a block. (Reason: The complete registration phase is
       single-threaded, race-condition free, thus strictly sequentially executed.) We
       just have to store for each of the registration blocks. */

    const ose_receivedCanFrame_t *pFrDescOsRx;
    unsigned int hOsFrame;
    for( hOsFrame = 0, pFrDescOsRx = &ose_receivedCanFrameAry[hOsFrame]
       ; success &&  hOsFrame < ose_noReceivedCanFrames
       ; ++hOsFrame, ++pFrDescOsRx
       )
    {
        unsigned int idxCde = cde_registerFrame( pFrDescOsRx->canId
                                               , /* isInbound */ true
                                               , pFrDescOsRx->idxCanBus
                                               , /* osHandleFrame */ hOsFrame
                                               , IDX_DISPATCHER_SEND_10MS_AND_RECEIVE
                                               , /* callback */ onInitSimulationReceiveFrame
                                               );
        success = idxCde != CDE_INVALID_FRAME_INDEX;
        if(success)
        {
            if(hOsFrame == 0)
            {
                /* First registration: Store the offset between OS handle (zero-based
                   linear index) and CDE index (linear index with start value depending
                   on preceeding frame registrations). */
                _offsetIdxCdeToTableOfReceivedFrames = idxCde;

                /* In this test environment we know, which frames the APSW has
                   previously registered and can double-check. */
                assert(_offsetIdxCdeToTableOfReceivedFrames == CDE_NO_CAN_FRAMES);
            }
            else
            {
                /* Subsequent registrations: Check statement about contiguous
                   indes/handle spaces. */
                assert(_offsetIdxCdeToTableOfReceivedFrames + hOsFrame == idxCde);
            }
        }
    } /* for(All inbound frames) */

    const ose_sentCanFrame_t *pFrDescOsTx;
    for( hOsFrame = 0, pFrDescOsTx = &ose_sentCanFrameAry[hOsFrame]
       ; success &&  hOsFrame < ose_noSentCanFrames
       ; ++hOsFrame, ++pFrDescOsTx
       )
    {
        /* Choice of appropriate dispatcher: Needs to be identical as decision in APSW;
           each dispatcher needs to be used by exactly one execution thread, i.e. APSW
           task. */
        const unsigned int idxDispatcher =
                            pFrDescOsTx->sendMode == cap_enumSendMode_regular
                            &&  pFrDescOsTx->tiCycle < 100
                            ||  pFrDescOsTx->sendMode != cap_enumSendMode_regular
                                &&  pFrDescOsTx->tiMinDistance < 100
                            ? IDX_DISPATCHER_SEND_10MS_AND_RECEIVE
                            : IDX_DISPATCHER_SEND_100MS;
        unsigned int idxCde = cde_registerFrame( pFrDescOsTx->canId
                                               , /* isInbound */ false
                                               , pFrDescOsTx->idxCanBus
                                               , /* osHandleFrame */ hOsFrame
                                               , idxDispatcher
                                               , /* callback */ onEventSendDispatcher
                                               );
        success = idxCde != CDE_INVALID_FRAME_INDEX;
        if(success)
        {
            if(hOsFrame == 0)
            {
                /* First registration: Store the offset between OS handle (zero-based
                   linear index) and CDE index (linear index with start value depending
                   on preceeding frame registrations). */
                _offsetIdxCdeToTableOfSentFrames = idxCde;

                /* In this test environment we know, which frames the APSW has
                   previously registered and can double-check. */
                assert(_offsetIdxCdeToTableOfSentFrames
                       == CDE_NO_CAN_FRAMES + CDE_NO_CAN_FRAMES_RECEIVED
                      );
            }
            else
            {
                /* Subsequent registrations: Check statement about contiguous
                   indes/handle spaces. */
                assert(_offsetIdxCdeToTableOfSentFrames + hOsFrame == idxCde);
            }
        }
    } /* for(All outbound frames) */

    if(success)
    {
        assert(_logCanData == NULL);
        openCanLog();
    }

    assert(success);
    return success;

} /* End of initCANBusSimulation */




/**
 * Finalize the simulation of the CAN transmission, do approriate clean up.
 *   @return
 * \a true if operation succeeded, \a false in case of errors.
 *   @remark
 * This method is called in an again race-condition free, single-threaded environment.
 */

static boolean_t shutdownCANBusSimulation()
{
    if(_logCanData != NULL)
        closeCanLog();

#ifdef DEBUG
    /* Double-check corect use of handler context data array. */
    unsigned int u;
    for(u=0; u<sizeOfAry(_hdlCtxDataRxMixedAry); ++u)
    {
        assert(_hdlCtxDataRxMixedAry[u].hTimerDueCheck != CDE_INVALID_TIMER_HANDLE
               &&  _hdlCtxDataRxMixedAry[u].hTimerTimeout != CDE_INVALID_TIMER_HANDLE
              );
    }
#endif    

    unsigned int noEvQFull10ms = cde_getNoDispatcherQueueFullEvents
                                               ( IDX_DISPATCHER_SEND_10MS_AND_RECEIVE
                                               , /* reset */ true
                                               )
               , noEvQFull100ms = cde_getNoDispatcherQueueFullEvents
                                               ( IDX_DISPATCHER_SEND_100MS
                                               , /* reset */ true
                                               );
#ifdef _STDC_VERSION_C11
    assert(cde_getNoDispatcherQueueFullEvents(IDX_DISPATCHER_SEND_10MS_AND_RECEIVE, false)
           == 0
           &&  cde_getNoDispatcherQueueFullEvents(IDX_DISPATCHER_SEND_100MS, false) == 0
          );
#endif
    LOG_LOG( sup_hGlobalLogger
           , noEvQFull10ms>0 || noEvQFull100ms>0? log_warn: log_info
           , "%lu ms: %s: "
             "Number of queue full events: %u (10ms task),  %u (100ms task)"
           , ose_tiSim, __func__
           , noEvQFull10ms, noEvQFull100ms
           );

    return true;

} /* End of shutdownCANBusSimulation */



/**
 * Simulation of CAN reception and sending uses a regular task of 1ms cycle time.
 *   @return
 * Normally rtos_taskFctResult_continueScheduling. If a termination condition of the
 * simulation is reached then the function returns rtos_taskFctResult_endOfScheduling. This
 * and all other threads will terminate.
 */

static rtos_taskFctResult_t taskOSInternal()
{
    /* Trigger the dispatchers for CAN send and receive simulation. */
    cde_dispatcherMain(IDX_DISPATCHER_SEND_10MS_AND_RECEIVE);
    cde_dispatcherMain(IDX_DISPATCHER_SEND_100MS);

    ++ ose_tiSim;

    /* Check the user specified termination condition. */
    return (_tiSimEnd > 0  &&  ose_tiSim >= _tiSimEnd)
#ifdef __WINNT__
           ||  _kbhit() != 0
#endif
           ? rtos_taskFctResult_endOfScheduling
           : rtos_taskFctResult_continueScheduling;

} /* End of taskOSInternal */




#if USE_SINGLE_THREADED_SCHEDULER != 0
/**
 * Test function: Run threads from a race-condition free single-threaded scheduler, will
 * invokes the tasks strictly sequentially.
 */
static void runSingleThreadedScheduler()
{
    unsigned int cntMs = 0;
    while(taskOSInternal() == rtos_taskFctResult_continueScheduling)
    {
        if(_taskAry[ose_taskType_regular1ms] != NULL)
            _taskAry[ose_taskType_regular1ms]();

        if(cntMs % 10 == 0  &&  _taskAry[ose_taskType_regular10ms] != NULL)
            _taskAry[ose_taskType_regular10ms]();

        if(cntMs % 100 == 0  &&  _taskAry[ose_taskType_regular100ms] != NULL)
            _taskAry[ose_taskType_regular100ms]();

        if(cntMs % 1000 == 0  &&  _taskAry[ose_taskType_regular1s] != NULL)
            _taskAry[ose_taskType_regular1s]();

        if(++cntMs == 1000)
            cntMs = 0;
    }
} /* End of runSingleThreadedScheduler */
#endif



/**
 * The simulation of the operating system kernel. Since we have a single threaded
 * simulation this is barely more than a simple loop with some function calls at regularly
 * reached multiples of the task base periods.
 *   @return
 * \a true, if function succeeded, else \a false.
 *   @param tiSimEndInMs
 * The duration of the simulated time. Unit is milli second. Simulation always starts at
 * time null. A value of zero the application will run infinitely.
 */

void ose_kernel(unsigned long tiSimEndInMs)
{
    /// @todo Consider making this a user-option
    //srand((unsigned)time(0));

    /* Initialize the system in a still race condition free, single-threaded environment. */
    bool success;
    if(_taskAry[ose_taskType_init] != NULL)
        success = _taskAry[ose_taskType_init]() == rtos_taskFctResult_continueScheduling;
    else
        success = true;

    /* Run the software only if initialization didn't report a problem. */
    if(success)
    {
        /* The implementation of the CAN simulation requires some objects from the CAN
           interface engine. The CAN interface has been basically initialized in the call
           of the register init function above and only now we can configure the details of
           the objects required by the CAN simulation. */
#ifdef DEBUG
        boolean_t success =
#endif
        initCANBusSimulation();
        assert(success);

        /* Prepare the threads specification. Specify the the APSW installed threads and
           those internally needed for the asynchronous simulation of CAN handling. */
        rtos_threadSpecification_t userThreadAry[4+1];
        unsigned int idxThread = 0;
        userThreadAry[idxThread] =
                (rtos_threadSpecification_t){ .name = "ose_task_internal"
                                            , .fctTask = taskOSInternal
                                            , .tiCycleMs = 1
                                            };
        ++ idxThread;
        if(_taskAry[ose_taskType_regular1ms] != NULL)
        {
            userThreadAry[idxThread] =
                (rtos_threadSpecification_t){ .name = "ose_task_regular1ms"
                                            , .fctTask = _taskAry[ose_taskType_regular1ms]
                                            , .tiCycleMs = 1
                                            };
            ++ idxThread;
        }
        if(_taskAry[ose_taskType_regular10ms] != NULL)
        {
            userThreadAry[idxThread] =
                (rtos_threadSpecification_t){ .name = "ose_task_regular10ms"
                                            , .fctTask = _taskAry[ose_taskType_regular10ms]
                                            , .tiCycleMs = 10
                                            };
            ++ idxThread;
        }
        if(_taskAry[ose_taskType_regular100ms] != NULL)
        {
            userThreadAry[idxThread] =
                (rtos_threadSpecification_t){ .name = "ose_task_regular100ms"
                                            , .fctTask = _taskAry[ose_taskType_regular100ms]
                                            , .tiCycleMs = 100
                                            };
            ++ idxThread;
        }
        if(_taskAry[ose_taskType_regular1s] != NULL)
        {
            userThreadAry[idxThread] =
                (rtos_threadSpecification_t){ .name = "ose_task_regular1s"
                                            , .fctTask = _taskAry[ose_taskType_regular1s]
                                            , .tiCycleMs = 1000
                                            };
            ++ idxThread;
        }
        const unsigned int noThreads = idxThread;
        assert(noThreads >= 2  &&  noThreads < sizeof(userThreadAry)/sizeof(userThreadAry[0]));

        if(tiSimEndInMs > 0)
        {
            LOG_INFO( sup_hGlobalLogger
                    , "%s: Simulate %.3f s"
                    , __func__
                    , (double)tiSimEndInMs / 1000.0
                    );
        }
        else
        {
            LOG_INFO( sup_hGlobalLogger
                    , "%s: Simulation is running infinitely"
                    , __func__
                    );
        }

        /* Offer a way to terminate the possibly infinitely spinning application. */
        if(tiSimEndInMs == 0  ||  tiSimEndInMs > 5000)
        {
            #ifdef __WINNT__
            # define MSG "Hit any key to terminate ..."
            #else
            # define MSG "Type Ctrl-C to abort the infinite run of the application ..."
            #endif
            LOG_INFO(sup_hGlobalLogger, "%s: " MSG, __func__);
            #undef MSG
        }

        /* Run the scheduler. The next call returns only when all started threads have
           terminated again. This will last until one of the task functions demands the end
           of scheduling. */
        _tiSimEnd = tiSimEndInMs;
#if USE_SINGLE_THREADED_SCHEDULER == 0
        rtos_runScheduler(noThreads, userThreadAry, /* threadAry */ NULL);
#else
        runSingleThreadedScheduler();
#endif
    }
    else
    {
        LOG_ERROR( sup_hGlobalLogger
                 , "%s: Realtime simulation is not started since system initialization"
                   " reported an error"
                 , __func__
                 );
    }

    /* Give a chance to release resources in the shutdown sequence even in case of
       initialization errors. */
    shutdownCANBusSimulation();
    if(_taskAry[ose_taskType_shutdown] != NULL)
    {
        if(_taskAry[ose_taskType_shutdown]() != rtos_taskFctResult_continueScheduling)
        {
            success = false;
            LOG_ERROR( sup_hGlobalLogger
                     , "%s: System shutdown reported an error"
                     , __func__
                     );
        }
    }
} /* End of ose_kernel */




/**
 * Install a function as task function in the operating system.\n
 *   @return
 * The task function so far is returned; this will normally be NULL.
 *   @param kindOfTask
 * Different tasks, mostly regularly triggered ones, can be installed.
 *   @param function
 * The function, which is from now on called as a task.
 *   @remark
 * This function must be used at system initialization time before multi-threading starts.
 */

ose_task_t ose_installTask(ose_taskType_t type, ose_task_t function)
{
    ose_task_t oldTask = NULL;
    if((unsigned)type < ose_noTaskTypes)
    {
        oldTask = _taskAry[(unsigned)type];
        _taskAry[(unsigned)type] = function;
    }
    else
        assert(false);

    return oldTask;

} /* End of ose_installTask */




/**
 * Install the IRQ handler for CAN reception in the operating system.\n
 *   @return
 * The IRQ handler so far is returned; this will normally be NULL.
 *   @param irqHandler
 * The handler, which is from now on called on every CAN frame reception.
 *   @remark
 * This function must be used at system initialization time before multi-threading starts.
 */

ose_irqHandlerCanRx_t ose_installIrqHandlerCanRx(ose_irqHandlerCanRx_t irqHandler)
{
    ose_irqHandlerCanRx_t oldHandler = _irqHandlerCanRx;
    _irqHandlerCanRx = irqHandler;
    return oldHandler;

} /* End of ose_installIrqHandlerCanRx */



/**
 * The platform's simulated CAN send function. The frame is identified by the index of the
 * sent frame in the specification table of outbound frames, ose_sentCanFrameAry.
 *   @return
 * The function returns a success message. A \a false will typically appear if the queue
 * down to the HW driver (emulated in another thread) is full.
 *   @param idxFrameOs
 * The index of the frame in table ose_sentCanFrameAry. Only specified frames can be
 * processed.
 *   @param pData
 * The frame contents, already byte encoded.
 *   @param DLC
 * The number of bytes to send out.
 */

boolean_t ose_sendCanFrame( unsigned int idxFrameOs
                          , uint8_t *pData
                          , unsigned int DLC
                          )
{
    assert(DLC <= 8  &&  idxFrameOs < ose_noSentCanFrames);
    const ose_sentCanFrame_t *pFrDescOs = &ose_sentCanFrameAry[idxFrameOs];
    return cde_postFrameEvent( pFrDescOs->idxCanBus
                             , /* osHandleFrame */ idxFrameOs
                                                   + _offsetIdxCdeToTableOfSentFrames
                             , /* kind */ CDE_EV_FRAME_RECEPTION
                             , pData
                             , DLC
                             );
} /* End of ose_sendCanFrame */



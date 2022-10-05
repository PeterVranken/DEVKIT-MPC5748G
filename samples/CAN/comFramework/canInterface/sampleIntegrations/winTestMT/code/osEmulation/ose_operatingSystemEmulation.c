/// @todo
/// - enum to be defined for OS events and kinds
///   - All set to zero, doesn't matter but is not nice
/**
 * @file ose_operatingSystemEmulation.c
 * Simulation of those parts of an operating system, which are required in the context of
 * the CAN interface. The simulation is simple but it's sufficient to connect to all API
 * functions and to run through all the code and to demonstrate the way the CAN interface
 * works and how it has to be integrated in a real system.
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
 *   ose_kernel
 *   ose_installTask
 *   ose_installIrqHandlerCanRx
 *   ose_sendCanMessage
 * Local functions
 *   openCanLog
 *   closeCanLog
 *   logCanFrame
 *   mapHandleOneToOne
 *   getIsInboundAndIdx
 *   getCanId
 *   isInboundTransmission
 *   getIdxBus
 *   onSimulateReceptionOfRegularFrame
 *   onSimulateReceptionOfEventFrame
 *   onSimulateReceptionOfMixedFrame
 *   onInitSimulationRxMsg
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
#include "mem_malloc.h"
#include "log_logger.h"
#include "opt_getOpt.h"
#include "fil_file.h"
#include "sup_startup.h"
#include "rtos_rtosEmulation.h"
#include "ede_eventDispatcherEngine.h"
#include "cst_canStatistics.h"
#include "cap_canApi.h"
#include "e2e_frameProtection.h"
#include "ede_eventSender.h"
#include "ose_operatingSystemEmulation.h"
#include "cdt_canDataTables.h"
#include "vsq_dispatcherPortInterface.h"


/*
 * Defines
 */

/** For development support is possible to replace the normal scheduler from the RTOS
    emulation by some simple, sequential task invokation. If the single thraeded scheduler
    is enabled then the software is basically doing the same but without any danger of race
    conditions and without synchronization with the world time. It'll thus consume 100% of
    the computation time of one CPU core. */
#define USE_SINGLE_THREADED_SCHEDULER   0

/** The size of the heap memory, which is statically allocated for the OS part of the
    implementation of the CAN interface.\n
      @remark Compilation for win64 requires significantly more memory than for win32: All
    the pointers and int variables in the data structures have double the size. */
#define SIZE_OF_HEAP_FOR_CAN_INTERFACE 100000 /* Byte */

/** A signed integer in the range [i, j]. */
#define IRAND(i,j) (rand()%((j)-(i)+1)+(i))

/** A scaled floating point random number in the range [a, b). */
#define RAND(a,b) ((double)((b)-(a))*RND()+(double)(a))

/** A Boolean random number with given probability p of getting a true. */
#define BOOL_RAND(p) (RND()<(p)? true: false)

/** A floating point random number in the range [0;1). */
#define RND() ((double)rand()/(double)RAND_MAX)

/** The common length of all queues of the dispatcher that serves the Tx frames send by the
    APSW. All queues corresponds to: all connection points. */
#define DISPATCHER_TX_QUEUE_LEN                 CST_NO_CAN_FRAMES_SENT

/** The name of the CAN log file with simulated CAN traffic. Without extension, different
    formats are offered and the right extension will be appended. */
#define CAN_LOG_FILE_NAME SUP_APP_NAME "_CAN" ".m"

/** The CAN log can either be a human readable ASCII file or an executable Ocatve script
    with slightly degraded readability. Comment the define out to get the ASCII format. */
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

/** The handlers for frames with timing pattern mixed requires some local, frame related
    data. It is kept in this array. */
static struct hdlCtxDataRxMixed_t
{
    /** The handle of the due check timer. */
    ede_handleTimer_t hTimerDueCheck;

    /** The handle of the timeout timer. */
    ede_handleTimer_t hTimerTimeout;

} _hdlCtxDataRxMixedAry[CST_NO_CAN_FRAMES_RECEIVED_MIXED];


/** A memory pool for OS related CAN stack objects, i.e. objects in use by the OS
    notification process. */
static ede_memoryPool_t _memoryPoolOS = EDE_INVALID_MEMORY_POOL;

/** A memory pool for APSW related CAN stack objects, i.e. objects in use by the CAN
    notification/event dispatching process. */
static ede_memoryPool_t _memoryPoolAPSW = EDE_INVALID_MEMORY_POOL;

/** The senders of CAN events. They are all connected to the single dispatcher, which is in
    charge of buffering outbound messages. */
static ede_handleSender_t _hEventSenderAry[OSE_CAN_TX_NO_CONNECTION_POINTS] =
                {[0 ... (OSE_CAN_TX_NO_CONNECTION_POINTS-1u)] = EDE_INVALID_SENDER_HANDLE,};

/** The dispatcher engine, which is used for processing Tx messages and to produce the
    timing of Rx simulation. */
static ede_handleDispatcherSystem_t _hDispatcherSystem = EDE_INVALID_DISPATCHER_SYSTEM_HANDLE;

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
"colIsExt = 6; % 11 or 29 Bit ID. Boolean, true means an extended 29 Bit ID.\n"         \
"colDLC = 7; % Number of frame content bytes, the data length code.\n"                  \
"colByte0 = 8; % The first content byte or NaN if there is no content byte.\n"          \
"colContent = 8:15; % Use this range to index all frame content bytes of the frame.\n"  \
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


} /* End of openCanLog */


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
 *   @param isExtId
 * \a true if \a canId is an extended 29 Bit ID.
 *   @param pData
 * The frame contents, already byte encoded.
 *   @param DLC
 * The number of bytes to send out.
 */
static void logCanFrame( boolean_t isReceived
                       , unsigned int idxCanBus
                       , unsigned int canId
                       , bool isExtId
                       , const uint8_t *pData
                       , unsigned int DLC
                       )
{
    _Static_assert(sizeof(canId) >= sizeof(uint32_t), "Insufficient data type used");
    if(_logCanData != NULL)
    {
        static unsigned long noLines_ = 0;
#ifdef USE_OCTAVE_CAN_LOG_FORMAT
        fprintf( _logCanData
               , "  %15.6f %10lu %1u %5s %4u %5s %u"
               , rtos_getTime()
               , ose_tiSim
               , idxCanBus
               , isReceived? "true": "false"
               , canId
               , isExtId? "true": "false"
               , DLC
               );
#else
        fprintf( _logCanData
               , "%15.6f s - %10lu ms - %1u - %cx - ID %4u (%s) - DLC %u -"
               , rtos_getTime()
               , ose_tiSim
               , idxCanBus
               , isReceived? 'R': 'T'
               , canId
               , isExtId? "ext": "std"
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
 * The map lookup operation. The map is queried for an event source index as internally
 * used by the dispatcher engine. The map query function is called as sub-routine of
 * the dispatching operation, ede_dispatcherMain().\n
 *   Must not be NULL.
 *   @return
 * Normally, the event source index is returned by reference (see below) and the
 * function result is \a true. If the function doesn't find a suitable association it
 * will return \a false and the related event is lost.
 *   @param hInstance
 * Each dispatcher has its own index space for event sources and will require a
 * dedicated map. This is the identification of the map instance to use.
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
static bool mapHandleOneToOne( uintptr_t hInstance ATTRIB_DBG_ONLY
                             , unsigned int * pValue
                             , ede_kindOfEvent_t kindOfEvent ATTRIB_DBG_ONLY
                             , ede_senderHandleEvent_t senderHandleEvent
                             )
{
    assert(hInstance == 0u  &&  kindOfEvent == 0u);
    assert(senderHandleEvent < ose_noSentCanFrames);
    *pValue = senderHandleEvent;
    return true;

} /* mapHandleOneToOne */



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
    if(BOOL_RAND(1e-3 / CST_NO_CAN_FRAMES_RECEIVED))
    {
        LOG_ERROR( sup_hGlobalLogger
                 , "%lu ms: "
                   "%s: Inject error in frame %lu%s on bus %u"
                 , ose_tiSim, __func__
                 , pFrDescOs->canId
                 , pFrDescOs->isExtId? "x": ""
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
                   , pFrDescOs->isExtId
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
 * Determine the direction of transmission of the message, which caused an event and
 * retrieve its index in the OSE data tables of all message definitions.
 *   @return
 * Get \a true if the message in inbound and \a false if it is outbound.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @param pIdxMsgInOseAry
 * On return, and if the function returns \a true, then * \a pIdxMsgInOseAry is the index
 * of the message in array \a ose_receivedCanFrameAry, otherwise it is its index in \a
 * ose_sentCanFrameAry.
 *   @remark
 * This function may be called from an external event or a timer callback.
 */
static bool getIsInboundAndIdx( const ede_callbackContext_t * const pContext
                              , unsigned int * const pIdxMsgInOseAry
                              )
{
    bool isExtEventSrc;
    *pIdxMsgInOseAry = ede_getIdxEventSource(pContext, &isExtEventSrc);
    assert(isExtEventSrc &&  *pIdxMsgInOseAry < ose_noSentCanFrames
           ||  !isExtEventSrc &&  *pIdxMsgInOseAry < ose_noReceivedCanFrames
          );
    return !isExtEventSrc;

} /* getIsInboundAndIdx */


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
 * of the event dispatcher: It emulates the CAN specific API cde_getCanId() from
 * the dispatcher engine in revision <= 1.5.
 */
static cdt_canId_t getCanId(const ede_callbackContext_t *pContext)
{
    unsigned int idxMsg;
    if(getIsInboundAndIdx(pContext, &idxMsg))
    {
        assert(idxMsg < ose_noReceivedCanFrames);
        return CDT_CAN_ID( ose_receivedCanFrameAry[idxMsg].canId
                         , ose_receivedCanFrameAry[idxMsg].isExtId
                         );
    }
    else
    {
        assert(idxMsg < ose_noSentCanFrames);
        return CDT_CAN_ID( ose_sentCanFrameAry[idxMsg].canId
                         , ose_sentCanFrameAry[idxMsg].isExtId
                         );
    }
} /* getCanId */




#ifdef DEBUG
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
 * of the event dispatcher: It emulates the CAN specific API cde_isInboundTransmission() from
 * the dispatcher engine in revision <= 1.5.
 */
static bool isInboundTransmission(const ede_callbackContext_t *pContext)
{
    unsigned int dummy;
    return getIsInboundAndIdx(pContext, &dummy);

} /* isInboundTransmission */
#endif



/**
 * A callback may invoke this method to get the operating system handle of the related bus.
 * For bus related events, this is the causing bus. For timer callbacks, this is either its
 * parent bus or the bus its parent message is transmitted on. For message related callbacks
 * this is the bus the message is transmitted on.
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
 * of the event dispatcher: It emulates the CAN specific API cde_isInboundTransmission from
 * the dispatcher engine in revision <= 1.5.
 */
static unsigned int getIdxBus(const ede_callbackContext_t *pContext)
{
    unsigned int idxMsg;
    if(getIsInboundAndIdx(pContext, &idxMsg))
    {
        assert(idxMsg < ose_noReceivedCanFrames);
        return ose_receivedCanFrameAry[idxMsg].idxCanBus;
    }
    else
    {
        assert(idxMsg < ose_noSentCanFrames);
        return ose_sentCanFrameAry[idxMsg].idxCanBus;
    }
} /* getIdxBus */



/**
 * Shared callback for the timer of all simulated inbound regular frames.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onSimulateReceptionOfRegularFrame(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(isInboundTransmission(pContext)
           &&  ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED
          );

    unsigned int idxMsgInOseAry;
    const bool isInbound ATTRIB_DBG_ONLY = getIsInboundAndIdx(pContext, &idxMsgInOseAry);
    assert(isInbound);

    /* Simulation of frame reception using some random data.
         ede_getOsHandleFrame: The OS handle of the frame is the index in the OSE owned
       configuration table. This is a simple and efficient descision, which has been taken
       in the call of the registration method. */
    simulateFrameReception(idxMsgInOseAry);

} /* End of onSimulateReceptionOfRegularFrame */



/**
 * Shared callback for the timer of all simulated inbound event frames.
 *   @param pContext
 * The dispatcher context, which the callback is invoked in.
 */
static void onSimulateReceptionOfEventFrame(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(isInboundTransmission(pContext)
           &&  ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED
          );

    /* The event character of this frame is simulated by a simple Boolean random decision
       every time we get in this callback. */
    const boolean_t isEvent = BOOL_RAND(2e-3);

    signed int tiNewFromNow;
    if(isEvent)
    {
        /* Simulation says: Event happened - simulate reception. */

        unsigned int idxMsgOse;
        const bool isInbound ATTRIB_DBG_ONLY = getIsInboundAndIdx(pContext, &idxMsgOse);
        assert(isInbound);

        /* Simulation of frame reception using some random data. */
        simulateFrameReception(idxMsgOse);

        /* The OS handle of the frame is the index in the OSE owned configuration table.
           This is a simple and efficient descision, which has been taken in the call of
           the registration method. */
        assert(idxMsgOse < ose_noReceivedCanFrames);
        const ose_receivedCanFrame_t * const pFrDescOs = &ose_receivedCanFrameAry[idxMsgOse];

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
    ede_retriggerSingleShotTimer( pContext
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
static void onSimulateReceptionOfMixedFrame(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(isInboundTransmission(pContext)
           &&  ede_getKindOfEvent(pContext) == EDE_EV_TIMER_ELAPSED
          );

    /* The handler for mixed mode Rx frames requires some frame-related, local data. It is
       held in a global table and the index into this table is stored in the timers'
       context data. */
    const uintptr_t idxCtxData = ede_getTimerContextData(pContext);

    assert(idxCtxData < sizeOfAry(_hdlCtxDataRxMixedAry));
    const struct hdlCtxDataRxMixed_t * const pHdlCtxData = &_hdlCtxDataRxMixedAry[idxCtxData];

    /* This callback is shared between both timers involved in the control of a mixed mode
       frame. We need to know, which event it was and do a comparison on the timer handle
       to find out. */
    assert(pHdlCtxData->hTimerDueCheck != EDE_INVALID_TIMER_HANDLE
           &&  pHdlCtxData->hTimerTimeout != EDE_INVALID_TIMER_HANDLE
          );
    const boolean_t isTimerCheckForEv = ede_getHandleTimer(pContext)
                                        == pHdlCtxData->hTimerDueCheck;
    assert(isTimerCheckForEv ||  ede_getHandleTimer(pContext) == pHdlCtxData->hTimerTimeout);

    /* The event character of this frame is simulated by a simple Boolean random decision
       every time we get in this callback. We have a sure reception event if this callback
       was triggered by the timeout. */
    const boolean_t isEvent = !isTimerCheckForEv || BOOL_RAND(2e-3);

    signed int tiNewCheckFromNow;
    if(isEvent)
    {
        /* Simulation say: Event happened - simulate reception. */

        unsigned int idxMsgOse;
        const bool isInbound ATTRIB_DBG_ONLY = getIsInboundAndIdx(pContext, &idxMsgOse);
        assert(isInbound);

        /* Simulation of frame reception using some random data. */
        simulateFrameReception(idxMsgOse);

        /* The OS handle of the frame is the index in the OSE owned configuration table.
           This is a simple and efficient descision, which has been taken in the call of
           the registration method. */
        assert(idxMsgOse < ose_noReceivedCanFrames);
        const ose_receivedCanFrame_t * const pFrDescOs = &ose_receivedCanFrameAry[idxMsgOse];

        /* The time when the timer should fire the next time depends. We had an event in
           this tick, so we need to regard the minimum distance. */
        tiNewCheckFromNow = pFrDescOs->tiMinDistance + IRAND(-1,2);

        /* We have an reception event in this tick so the timeout counts entirely from
           new. */
        ede_retriggerSingleShotTimer( pContext
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
    ede_retriggerSingleShotTimer( pContext
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
static void onInitSimulationRxMsg(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(isInboundTransmission(pContext)
           &&  ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_INT_INIT
          );

    unsigned int idxMsgOse;
    const bool isInbound ATTRIB_DBG_ONLY = getIsInboundAndIdx(pContext, &idxMsgOse);
    assert(isInbound &&  idxMsgOse < ose_noReceivedCanFrames);
    const ose_receivedCanFrame_t * const pFrDescOs = &ose_receivedCanFrameAry[idxMsgOse];

    LOG_DEBUG( sup_hGlobalLogger
             , "%s: Initialization of message %u%s on bus %u"
             , __func__
             , getCanId(pContext).id, getCanId(pContext).isExtId? "x": ""
             , getIdxBus(pContext)
             );

    switch(pFrDescOs->sendMode)
    {
        case cap_enumSendMode_regular:
        {
            /* Regular frames are most simple. We apply a regular timer. */
#ifdef DEBUG
            ede_handleTimer_t hTimer =
#endif
            ede_createPeriodicTimer( pContext
                                   , /* tiPeriod */ pFrDescOs->tiCycle + IRAND(-1,1)
                                   , /* callback */ onSimulateReceptionOfRegularFrame
                                   , /* refUserContextData */ 0u
                                   );
            assert(hTimer != EDE_INVALID_TIMER_HANDLE);
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
            ede_handleTimer_t hTimer =
#endif
            ede_createSingleShotTimer( pContext
                                     , /* tiFromNow */ 1 /* next tick */
                                     , /* callback */ onSimulateReceptionOfEventFrame
                                     , /* refUserContextData */ 0u
                                     , /* killAtDueTime */ false
                                     );
            assert(hTimer != EDE_INVALID_TIMER_HANDLE);
            break;
        }
        case cap_enumSendMode_mixed:
        {
            /* Event frames with timeout are like event frames but need to be sent at a
               minimum rate even if there's no event. This requires a second timer, the
               timeout timer.
                 The order of creation matters: If both fire in the same tick then the
               callbacks are invoked in creation order. */
            static uintptr_t idxNextMixedFrame_ = 0;
            assert(idxNextMixedFrame_ < sizeOfAry(_hdlCtxDataRxMixedAry)
                   &&  _hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerDueCheck
                       == EDE_INVALID_TIMER_HANDLE
                   &&  _hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerTimeout
                       == EDE_INVALID_TIMER_HANDLE
                  );
            _hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerDueCheck =
                            ede_createSingleShotTimer
                                    ( pContext
                                    , /* tiFromNow */ 1 /* next tick */
                                    , /* callback */ onSimulateReceptionOfMixedFrame
                                    , /* refUserContextData */ idxNextMixedFrame_
                                    , /* killAtDueTime */ false
                                   );
            assert(_hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerDueCheck
                   != EDE_INVALID_TIMER_HANDLE
                  );

            _hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerTimeout =
                            ede_createSingleShotTimer
                                    ( pContext
                                    , /* tiFromNow */ pFrDescOs->tiCycle
                                    , /* callback */ onSimulateReceptionOfMixedFrame
                                    , /* refUserContextData */ idxNextMixedFrame_
                                    , /* killAtDueTime */ false
                                   );
            assert(_hdlCtxDataRxMixedAry[idxNextMixedFrame_].hTimerTimeout
                   != EDE_INVALID_TIMER_HANDLE
                  );

            ++ idxNextMixedFrame_;
            break;
        }
        default:
            assert(false);

    } /* switch(Transmission pattern of frame) */
} /* End of onInitSimulationRxMsg */




/**
 * Initialize the dispatching process of sent frames. Here, dispatching simply means to
 * take the submitted frames from the queue and to write the CAN ID and the received data
 * into the log file.
 *   @param pContext
 * The callback context, which provides access to event related information.
 *   @remark
 * The implementation of this callback is race-condition free. It is well shared between
 * both dispatcher queues, but both of them are processed one after another in the same
 * thread, the internal 1ms task of this OS emulation.
 */
static void onEventSendDispatcher(const ede_callbackContext_t *pContext)
{
    /* Double-check that this callback is called from an expected context. */
    assert(!isInboundTransmission(pContext));

    switch(ede_getKindOfEvent(pContext))
    {
    case EDE_EV_EVENT_SOURCE_EXT_INIT:
        /* Initialization: Nothing to be done since we intend to use the same callback for
           future events, too. An insignificant optimization would be to now install another
           callback, this would remove the need for conditional code that checks the kind
           of event.
             This event is handled in the context of the main thread at system
           initialization time, prior to the beginning of multi-threading. No
           race-conditions must be anticipated. */
        LOG_DEBUG( sup_hGlobalLogger
                 , "%s: Initialization of message %u%s on bus %u"
                 , __func__
                 , getCanId(pContext).id, getCanId(pContext).isExtId? "x": ""
                 , getIdxBus(pContext)
                 );
        break;

    case 0u: /// @todo Use symbol instead of literal
      {
        /* The only event at run-time: The APSW has submitted a frame for sending. It has
           submitted the frame using method ose_sendCanMessage.
             This event is handled in the context of the OSE internal CAN simulation
           thread. No race-conditions with other code from this thread must be
           anticipated. */

        /* Retrieve the OS handle, which is the index into the send frame configuration
           table and provide access to the frame descriptor in this table. */
        unsigned int idxMsgOse;
        const bool isInbound ATTRIB_DBG_ONLY = getIsInboundAndIdx(pContext, &idxMsgOse);
        assert(!isInbound &&  idxMsgOse < ose_noSentCanFrames);
        const ose_sentCanFrame_t *pFrDescOs = &ose_sentCanFrameAry[idxMsgOse];

        /* Some consistency checks. */
        assert(pFrDescOs->idxCanBus == getIdxBus(pContext)
               &&  CDT_CAN_ID(pFrDescOs->canId, pFrDescOs->isExtId).uniqueCanId
                   == getCanId(pContext).uniqueCanId
              );

        /* The event's data is the frame contents. */
        unsigned int sizeOfEvData;
        const uint8_t * const frameContents = ede_getEventData(pContext, &sizeOfEvData);
        assert(sizeOfEvData <= 8);

        LOG_DEBUG( sup_hGlobalLogger
                 , "%s: Bus %u, message %lu%s (%u Byte): Simulation of sending in OS emulation"
                 , __func__
                 , pFrDescOs->idxCanBus
                 , pFrDescOs->canId
                 , pFrDescOs->isExtId? "x": ""
                 , sizeOfEvData
                 );
        logCanFrame( /* isReceived */ false
                   , pFrDescOs->idxCanBus
                   , pFrDescOs->canId
                   , pFrDescOs->isExtId
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
        _hdlCtxDataRxMixedAry[u].hTimerDueCheck = EDE_INVALID_TIMER_HANDLE;
        _hdlCtxDataRxMixedAry[u].hTimerTimeout = EDE_INVALID_TIMER_HANDLE;
    }

    /* Even if it is entirely useless in the given Windows environment: We demonstrate the
       use of distinct memory pools for sending events (by simulated OS) and for receiving
       events (by APSW). */
    static char heapMemoryOS[SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    static char heapMemoryAPSW[SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    bool success ATTRIB_DBG_ONLY = mem_createMemoryPool
                                            ( &_memoryPoolOS
                                            , /* pPoolMemory */ heapMemoryOS
                                            , /* sizeOfPoolMemory */ sizeof(heapMemoryOS)
                                            , MEM_VOID_CRITICAL_SECTION_OBJECT
                                            );
    assert(success);
    success = mem_createMemoryPool( &_memoryPoolAPSW
                                  , /* pPoolMemory */ heapMemoryAPSW
                                  , /* sizeOfPoolMemory */ sizeof(heapMemoryAPSW)
                                  , MEM_VOID_CRITICAL_SECTION_OBJECT
                                  );
    assert(success);

    /* Create the required dispatcher queues. */
    ede_eventSenderPort_t portSenderAry[sizeOfAry(_hEventSenderAry)];
    ede_eventReceiverPort_t portDispatcherAry[sizeOfAry(_hEventSenderAry)];
    for(unsigned int idxCnctPt=0u; idxCnctPt<sizeOfAry(_hEventSenderAry); ++idxCnctPt)
    {
        success = vsq_createEventQueue
                                 ( &portDispatcherAry[idxCnctPt]
                                 , &portSenderAry[idxCnctPt]
                                 , /* maxQueueLength */ DISPATCHER_TX_QUEUE_LEN /* no msgs */
                                 , /* sizeOfPayload */ 8u /* max DLC */
                                 , /* memPoolDispatchingProcess */ &_memoryPoolOS
                                 , /* memPoolSenderOfEvents */     &_memoryPoolAPSW
                                 );
        assert(success);
    }

    /* Create the required dispatcher system. */
    success = ede_createDispatcherSystem( &_hDispatcherSystem
                                        , /* noEventDispatcherEngines */ 1u
                                        , /* maxNoEventSourcesExt */ CST_NO_CAN_FRAMES_SENT
                                        , /* maxNoEventSourcesInt */ CST_NO_CAN_FRAMES_RECEIVED
                                        , &_memoryPoolOS
                                        );
    assert(!success ||  _hDispatcherSystem != EDE_INVALID_DISPATCHER_SYSTEM_HANDLE);

    /* Create the required dispatchers with their associated handle maps.
         Suitable handle maps: Here, we see a trivial handle mapping. We have a single
       dispatcher and all Tx messages are registered in the order of appearance in array
       ose_sentCanFrameAry. The index into this array is the handle, which the sender
       (APSW) has to serve. The APSW's data table has the same order but an index shift as
       it contains the Tx messages after the Rx messages. The APSW just has to consider
       this shift. */
    const ede_mapSenderEvHandleToIdx_t handleMap =
    {
        .addKeyValuePair = NULL,
        .getValue = mapHandleOneToOne,
        .hInstance = 0u,
    };
    success = ede_createDispatcher( _hDispatcherSystem
                                  , /* idxDispatcher */ 0u
                                  , /* tiTick */ 1 /* ms */
                                  , portDispatcherAry
                                  , /* noPorts */ sizeOfAry(portDispatcherAry)
                                  , /* mapSdrEvHdlToEdeEvSrcIdx */ handleMap
                                  );
    assert(success);

    /* Create the senders. Here, we demonstrate the use of one sender per queue (instead of
       a single sender with n ports), which saves us the map that associates a message
       handle with a port index. */
    for(unsigned int idxCnctPt=0u; success && idxCnctPt<sizeOfAry(_hEventSenderAry); ++idxCnctPt)
    {
        /* _memoryPoolAPSW: The sender object is run in the context of the ASPW, in an OSE
           offered API, which is invoked by the APSW. */
        success = ede_createSender( &_hEventSenderAry[idxCnctPt]
                                  , &portSenderAry[idxCnctPt]
                                  , /* noPorts */ 1u
                                  , /* pMapSenderEvHandleToPortIndex */ NULL
                                  , &_memoryPoolAPSW
                                  );
        assert(success &&  _hEventSenderAry[idxCnctPt] != EDE_INVALID_SENDER_HANDLE);
    }

    /* All frames, which have been specified to the operating system in its configuration
       tables are registered at the dispatcher. Registering the Rx messages enables easy
       implementation of the simulation timing on the timer API of the dispatcher engine.
         Handling of handles: There's only one dispatcher engine with a contiguous handle
       space for all registered frames. APSW and OS emulation share this space. The
       dispatcher engine specifies to use a linear, zero based index as handles for the
       frames. The indexes are provided in the order of frame registration. This definition
       of a handle makes handle mapping between dispatcher and OS in most of the cases a
       trivial operation, either an identity or just adding an offset. This holds for our
       OS emulation, too.
         The OS emulation has two configuration tables for processed frames, separate for
       in- and outbound frames. The tables are user-filled (implemented by code
       generation), therefore it is safely under control of the APSW to register the frames
       in the same order as it fills the configuration tables. If the OS emulation
       registers the frames in the order of its configuration tables, than we have anywhere
       same index/handle orders. The offsets can be different for each block of
       registration, in- and outbound, but not inside such a block. (Reason: The complete
       registration phase is single-threaded, race-condition free, thus strictly
       sequentially executed.) */
    unsigned int hOsMsg;
    for(hOsMsg=0; success && hOsMsg<ose_noSentCanFrames; ++hOsMsg)
    {
        /* Kind of event: It doesn't really matter for Tx messages in this application as
           this is the only kind of external event and since our simple one-to-one map
           doesn't evaluate it. */
        const unsigned int idxEvSrcEde ATTRIB_DBG_ONLY =
                    ede_registerExternalEventSource( _hDispatcherSystem
                                                   , /* idxDispatcher */ 0u
                                                   , /* kindOfEvent */ 0 /* doesn't matter */
                                                   , /* senderHandleEvent */ hOsMsg
                                                   , /* callback */ onEventSendDispatcher
                                                   , /* refEventSourceData */ 0u /* not used */
                                                   );
        success = idxEvSrcEde != EDE_INVALID_EVENT_SOURCE_INDEX;
        assert(!success ||  idxEvSrcEde == hOsMsg);

    } /* for(All outbound frames) */

    for(hOsMsg=0; success && hOsMsg<ose_noReceivedCanFrames; ++hOsMsg)
    {
        /* The event registeration of internal events, as used here, just makes the
           initialization callback happen, which is applied to install all further (timer)
           events for the simulation timing. */
        const unsigned int idxEvSrcEde ATTRIB_DBG_ONLY =
                ede_registerInternalEventSource( _hDispatcherSystem
                                               , /* idxDispatcher */ 0u
                                               , /* callback */ onInitSimulationRxMsg
                                               , /* refEventSourceData */ 0u /* not used */
                                               );
        success = idxEvSrcEde != EDE_INVALID_EVENT_SOURCE_INDEX;
        assert(!success ||  idxEvSrcEde == hOsMsg);

    } /* for(All inbound frames) */

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
        assert(_hdlCtxDataRxMixedAry[u].hTimerDueCheck != EDE_INVALID_TIMER_HANDLE
               &&  _hdlCtxDataRxMixedAry[u].hTimerTimeout != EDE_INVALID_TIMER_HANDLE
              );
    }
#endif

    for(unsigned int idxCnctPt=0u; idxCnctPt<sizeOfAry(_hEventSenderAry); ++idxCnctPt)
    {
        const unsigned int noEvQFull = ede_getNoSenderPortBlockedEvents
                                                ( _hEventSenderAry[idxCnctPt]
                                                , /* idxPort */ 0u
                                                );
        LOG_LOG( sup_hGlobalLogger
               , noEvQFull > 0? log_warn: log_info
               , "%lu ms: %s: "
                 "Number of queue full events: %u (Connection point %u)"
               , ose_tiSim, __func__
               , noEvQFull, idxCnctPt
               );
    }

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
    /* Trigger the dispatcher for CAN send and receive simulation. */
    ede_dispatcherMain(_hDispatcherSystem, /* idxDispatcher */ 0u);

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
 * The simulation of the operating system kernel. The thread descriptors are compiled in an
 * array and the RTOS emulation (built on the pthread environment) is called to create and
 * schedule these tasks.
 *   @return
 * \a true, if function succeeded, else \a false.
 *   @param tiSimEndInMs
 * The duration of the simulated time. Unit is Millisecond. Simulation always starts at
 * time zero. Given a value of zero, the application will run infinitely.
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
 *   @param idxConnectionPoint
 * A message is send via a "connection point". The OS offers
 * #OSE_CAN_TX_NO_CONNECTION_POINTS connection points. Each APSW context (task, ISR), which
 * wants to send a message needs to use its own, dedicated connection point.
 *   @param idxMessageOs
 * The index of the frame in table ose_sentCanFrameAry. Only specified frames can be
 * processed.
 *   @param pData
 * The frame contents, already byte encoded.
 *   @param sizeOfData
 * The number of bytes to send out.
 */
bool ose_sendCanMessage( unsigned int idxConnectionPoint
                       , unsigned int idxMessageOs
                       , uint8_t *pData
                       , unsigned int sizeOfData
                       )
{
    assert(sizeOfData <= 8  &&  idxMessageOs < ose_noSentCanFrames);
    if(idxConnectionPoint < sizeOfAry(_hEventSenderAry))
    {
        return ede_postEvent( _hEventSenderAry[idxConnectionPoint]
                            , /* kindOfEvent */ 0u
                            , /* senderHandleEvent */ idxMessageOs
                            , pData
                            , sizeOfData
                            );
    }
    else
    {
        assert(false);
        return false;
    }
} /* End of ose_sendCanMessage */

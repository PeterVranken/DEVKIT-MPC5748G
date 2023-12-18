/**
 * @file apt_applicationTask.c
 * This file contains the application tasks.
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
 *   apt_irqHandlerBusOff
 *   apt_taskInit
 *   apt_task10ms
 *   apt_task100ms
 *   apt_taskShutdown
 * Local functions
 *   createQueue
 */

/*
 * Include files
 */

#include "apt_applicationTask.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "main.h"
#include "oss_operatingSystemSimulation.h"
#include "mhn_mapOsFrameHandleToCanIfHandle.h"
#include "mem_malloc.h"
#include "cbk_callbacks.h"
#include "pwr_computeEnginePower.h"
#include "cst_canStatistics.h"
#include "ede_eventDispatcherEngine.config.h"
#include "ede_eventSender.h"
#include "ede_eventDispatcherEngine.h"
#include "vsq_dispatcherPortInterface.h"
#include "mu8_mapDirectLookupU8.h"

/*
 * Defines
 */


/*
 * Local type definitions
 */

/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** Simulated API with the APSW: The global bus-off state of the (only) CAN bus. The update
    of this global variable is implemented with the event notification mechanism of the CAN
    interface engine. */
bool apt_canBusOff = false;

/** A memory pool for OS related CAN stack objects, i.e. objects in use by the OS
    notification process. */
static ede_memoryPool_t apt_memoryPoolOS = EDE_INVALID_MEMORY_POOL;

/** A memory pool for APSW related CAN stack objects, i.e. objects in use by the CAN
    notification/event dispatching process. */
static ede_memoryPool_t apt_memoryPoolAPSW = EDE_INVALID_MEMORY_POOL;

/** The sender of CAN events. It is connected to both dispatchers. */
static ede_handleSender_t _hOsEventSender = EDE_INVALID_SENDER_HANDLE;

/** The array of dispatcher systems processing CAN events in the 10 and 100 ms APSW tasks. */
ede_handleDispatcherSystem_t apt_hDispatcherSystemAry[APT_NO_DISPATCHER_SYSTEMS] =
{
    [APT_IDX_DISPATCHER_SYSTEM_10MS] = EDE_INVALID_DISPATCHER_SYSTEM_HANDLE,
    [APT_IDX_DISPATCHER_SYSTEM_100MS] = EDE_INVALID_DISPATCHER_SYSTEM_HANDLE,
};


/*
 * Function implementation
 */

/**
 * The application owned part of the CAN reception interrupt, or the CAN reception
 * callback. In each integration, this callback will be used to feed received CAN frames
 * into the input queue of the appropriate engine for (later) processing.\n
 *   This callback will always be executed in the interrupt CPU context. The later
 * processing of the frame is done by the engine in the context it has been started in.
 * This is a normal application task context, ideally the only task, which requires access
 * to the frame's contents. If so, no further attention has to be drawn to inter-task
 * communication and data exchange.
 *   @param hFrame
 * A typical callback will pass the handle of the received CAN frame. This handle has
 * mostly been agreed on between APSW and BSW during the system initialization. If such a
 * handle mechanism is not applicable then this sample code will need according changes.
 * Real systems might use CAN and bus ID to identify a received message or have distinct
 * callbacks for different buses.
 *   @param pMsgContent
 * The received bytes are typically passed in as a pointer to a byte array.
 *   @param DLC
 * Any real existing platform will report the number of actually received bytes.
 */
void apt_irqHandlerRxCan( oss_handleCanFrame_t hFrame
                        , const unsigned char *pMsgContent
                        , unsigned int DLC
                        )
{
    LOG_DEBUG( main_hGlobalLogger
             , "%.1f ms: "
               "apt_irqHandlerRxCan: Frame %lu received (%u Byte)"
             , oss_tiSim / 1000.0
             , hFrame
             , (unsigned)DLC
             );

    /* Having the CAN interface handle of the received frame, we can post a frame received
       event to the dispatcher. */
    bool success = ede_postEvent( _hOsEventSender
                                , /* kindOfEvent */ APT_EV_RX_CAN_MSG
                                , /* senderHandleEvent */ hFrame
                                , /* pData */ pMsgContent
                                , /* sizeOfData */ DLC
                                );
    if(!success)
    {
        LOG_WARN( main_hGlobalLogger
                , "%.1f ms: "
                  "apt_irqHandlerRxCan: "
                  "Dispatcher queue full, can't post received event for frame"
                  " with handle %lu (OS)"
                , oss_tiSim / 1000.0
                , hFrame
                );
    }
} /* End of apt_irqHandlerRxCan */



/**
 * Our simulated platform has an interrupt to notify bus-off state and successful restart.
 *   @param isOff
 * \a true in case of a bus-off event, \a false if the bus has been (re-)started.
 */
void apt_irqHandlerBusOff(bool isOff)
{
    LOG_DEBUG( main_hGlobalLogger
             , "%.1f ms: "
               "apt_irqHandlerBusOff: Bus turns %s"
             , oss_tiSim / 1000.0
             , isOff? "off": "on"
             );

    /* We post a bus related event to the dispatcher. Handle mapping as for frames is not
       an issue as we only have one bus and even for real platforms with two or more buses
       it won't become an issue as the buses are known, predetermined and the callback
       probably has a reference to its handle/index as argument. */
    bool success = ede_postEvent( _hOsEventSender
                                , /* kindOfEvent */ isOff
                                                    ? APT_EV_BUS_OFF
                                                    : APT_EV_RECOVERED_FROM_BUS_OFF
                                , /* senderHandleEvent */ 0u /* doesn't care */
                                , /* pData */ NULL
                                , /* sizeOfData */ 0u
                                );
    if(!success)
    {
        LOG_WARN( main_hGlobalLogger
                , "%.1f ms: "
                  "apt_irqHandlerBusOff: "
                  "Dispatcher queue full, can't post bus%s event"
                , oss_tiSim / 1000.0
                , isOff? "-off": " recovery"
                );
    }
} /* End of apt_irqHandlerBusOff */




/**
 * The callback for the bus related events.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onBusOnOff(const ede_callbackContext_t *pContext)
{
/* This dispatcher is run in a 100ms period. All times will be rounded to this grid. */
#define DELAY_TILL_RESTART_ATTEMPT_IN_MS 250

    static ede_handleTimer_t timerRecovery_ = EDE_INVALID_TIMER_HANDLE;

    /* Here we demonstrate the "traditional" event handler structure with a large switch
       statement. An alternative could be a separate callback for the timer events. The
       external events (bus-off and recovery in this example) cannot be delegated to
       different callbacks. */
    switch(ede_getKindOfEvent(pContext))
    {
    case APT_EV_BUS_OFF:
        LOG_WARN( main_hGlobalLogger
                , "%.1f ms: "
                  "onBusOnOff: "
                  "A bus-off error has been notified. A restart will be tried after"
                  " %u ms"
                , oss_tiSim / 1000.0
                , DELAY_TILL_RESTART_ATTEMPT_IN_MS
                );
        /* The information is made public in the context of this APSW task. */
        apt_canBusOff = true;

        /* We create a timer in order to try a recovery after a while. There's no guarantee
           that the notifications off and recovered will always appear alternatingly. If
           the bus-off arrives twice, then we might already have a timer created. We try to
           retrigger an existing timer first. */
        if(timerRecovery_ != EDE_INVALID_TIMER_HANDLE)
        {
            ede_retriggerSingleShotTimer( pContext
                                        , timerRecovery_
                                        , DELAY_TILL_RESTART_ATTEMPT_IN_MS
                                        );
        }
        else
        {
            timerRecovery_ = ede_createSingleShotTimer( pContext
                                                      , DELAY_TILL_RESTART_ATTEMPT_IN_MS
                                                      , onBusOnOff
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                                      , /* refUserContextData */ 0u
#endif
                                                      , /* killAtDueTime */ true
                                                      );
            assert(timerRecovery_ != EDE_INVALID_TIMER_HANDLE);
        }
        break;

    case APT_EV_RECOVERED_FROM_BUS_OFF:
        LOG_INFO( main_hGlobalLogger
                , "%.1f ms: "
                  "onBusOnOff: "
                  "Recovery from bus-off has been notified"
                , oss_tiSim / 1000.0
                );
        /* The information is made public in the context of this APSW task. */
        apt_canBusOff = false;

        /* We stop the running timer; triggering of recovery is no longer required. A
           weakness of this "application code" is that we will continue making attempts to
           recover if we missed this event - which can happen due to a queue full
           situation. */
        if(timerRecovery_ != EDE_INVALID_TIMER_HANDLE)
        {
            ede_killTimer(pContext, timerRecovery_);
            timerRecovery_ = EDE_INVALID_TIMER_HANDLE;
        }
        break;

    case EDE_EV_TIMER_ELAPSED:
        LOG_INFO( main_hGlobalLogger
                , "%.1f ms: "
                  "onBusOnOff: "
                  "Timer after bus-off notification has elapsed. Bus restart is tried. New"
                  " timeout is %u ms"
                , oss_tiSim / 1000.0
                , 2*DELAY_TILL_RESTART_ATTEMPT_IN_MS
                );

        /* We make an attempt to restart the bus. This requires an according API function
           in the operating system. */
        oss_restartCanBus(OSS_CAN_BUS_PT);

        /* We don't know if the restart will succeed. Better to repeat the attempt after a
           (longer) while. As we applied a single shot timer with auto-kill, we can't
           simply reuse the same timer. We create a new one. True code would probably
           better use a single shot timer without auto-kill but this choice lets us test
           more features. */
        timerRecovery_ = ede_createSingleShotTimer( pContext
                                                  , 2*DELAY_TILL_RESTART_ATTEMPT_IN_MS
                                                  , onBusOnOff
#if EDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                                  , /* refUserContextData */ 0u
#endif
                                                  , /* killAtDueTime */ true
                                                  );
        assert(timerRecovery_ != EDE_INVALID_TIMER_HANDLE);
        break;

    default:
        assert(false);
    }

#undef DELAY_TILL_RESTART_ATTEMPT_IN_MS
} /* End of onBusOnOff */



/**
 * The initialization callback for the bus related events.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onInitBus(const ede_callbackContext_t *pContext)
{
    assert(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_EXT_INIT);
    LOG_DEBUG( main_hGlobalLogger
             , "%.1f ms: "
               "onInitBus: Invoked by dispatcher"
             , oss_tiSim / 1000.0
             );

    /* The only action is to implement the final event handler for the bus off events. We
       could also use this callback all the time and would then end up with the
       "traditional" look of an event handler having a switch case for all supported kinds
       of events. */
    ede_installCallback(pContext, onBusOnOff);

} /* End of onInitBus */



/**
 * The initialization task. Such a task is found in any RTOS environment. Usually it is
 * called at a time when no parallel thread execution is done yet, so no race conditions
 * exist with other parts of the code and safe build-up of all required data structure can
 * be done prior to the start of the real task scheduling.\n
 *   We use this function to initialize the CAN interface.
 */
void apt_taskInit()
{
    bool initOk ATTRIB_DBG_ONLY;

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

    mhn_initModule();

    /* Create the required dispatcher queues. */
    ede_eventSenderPort_t portSender10ms;
    ede_eventReceiverPort_t portDispatcher10ms;
    initOk = vsq_createEventQueue( &portDispatcher10ms
                                 , &portSender10ms
                                 , /* maxQueueLength */ 4u /* no messages */
                                 , /* sizeOfPayload */ 8u /* max DLC */
                                 , /* pMemPoolDispatchingProcess */ &apt_memoryPoolAPSW
                                 , /* pMemPoolSenderOfEvents */     &apt_memoryPoolOS
                                 );
    assert(initOk);

    ede_eventSenderPort_t portSender100ms;
    ede_eventReceiverPort_t portDispatcher100ms;
    initOk = vsq_createEventQueue( &portDispatcher100ms
                                 , &portSender100ms
                                 , /* maxQueueLength */ 4u /* no messages */
                                 , /* sizeOfPayload */ 8u /* max DLC */
                                 , /* pMemPoolDispatchingProcess */ &apt_memoryPoolAPSW
                                 , /* pMemPoolSenderOfEvents */     &apt_memoryPoolOS
                                 );
    assert(initOk);

    /* Create the required dispatcher systems. */
    
    initOk = ede_createDispatcherSystem
                                ( &apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_10MS]
                                , /* noEventDispatcherEngines */ 1u
                                , APT_NO_EXT_EV_DISPATCHER_10MS
                                , APT_NO_INT_EV_DISPATCHER_10MS
                                , &apt_memoryPoolAPSW
                                );
    assert(!initOk
           ||  apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_10MS]
               != EDE_INVALID_DISPATCHER_SYSTEM_HANDLE
          );
    initOk = ede_createDispatcherSystem
                                ( &apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_100MS]
                                , /* noEventDispatcherEngines */ 1u
                                , APT_NO_EXT_EV_DISPATCHER_100MS
                                , APT_NO_INT_EV_DISPATCHER_100MS
                                , &apt_memoryPoolAPSW
                                );
    assert(!initOk
           ||  apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_100MS]
               != EDE_INVALID_DISPATCHER_SYSTEM_HANDLE
          );
    
    /* Create a handle map. A true lookup map is required as we use two distinct dispatcher
       systems in this sample, which have each its own index space, while the sender (OS)
       handle is the contiguous zero based indes space along all CAN messages. The unique
       OS handles go either or in one of the two systems; so we can use a single map object
       for both systems as they will never try to add a mapping for one and the same OS
       handle. */
    ede_mapSenderEvHandleToIdx_t handleMap;
    const signed int rangeSenderHandleEvAry[APT_NO_KINDS_OF_EVENTS][2u] =
    {
        [APT_EV_BUS_OFF] = {[0u] = 0, [1u] = 0,}, /* Empty range: handle doesn't matter. */
        [APT_EV_RECOVERED_FROM_BUS_OFF] = {[0u] = 0, [1u] = 0,}, /* Empty range. */
        [APT_EV_RX_CAN_MSG] = {[0u] = 0, [1u] = CST_NO_CAN_FRAMES_RECEIVED,}, /* All Rx OS handles. */
    };
    initOk = mu8_createMapDirectLookupU8( &handleMap
                                        , APT_NO_KINDS_OF_EVENTS
                                        , rangeSenderHandleEvAry
                                        , &apt_memoryPoolAPSW
                                        );
    assert(initOk);
    
    /* Create the required dispatchers. */
    initOk = ede_createDispatcher( apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_10MS]
                                 , /* idxDispatcher */ 0u
                                 , /* tiTick */ 10 /* ms */
                                 , /* portAry */ &portDispatcher10ms
                                 , /* noPorts */ 1u
                                 , /* mapSdrEvHdlToEdeEvSrcIdx */ handleMap
                                 );
    assert(initOk);
    initOk = ede_createDispatcher( apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_100MS]
                                 , /* idxDispatcher */ 0u
                                 , /* tiTick */ 100 /* ms */
                                 , /* portAry */ &portDispatcher100ms
                                 , /* noPorts */ 1u
                                 , /* mapSdrEvHdlToEdeEvSrcIdx */ handleMap
                                 );
    assert(initOk);

    /* The bus-off events from the single CAN bus in this sample integration are registered
       first. This is done to demonstrate the possibility of notifying occasional bus
       (not message) related events to dedicated callbacks. The implementation of the
       callbacks, which handle the notifications are purposely not auto-coded by the code
       generator. It could easily do as the network databases list the buses, too, but the
       added value would be quite low; the set of buses is very small and predetermined and
       fixed. Providing the code in templates is inefficient under these circumstances.
         Note, we have a dependency with our simple implementation of the handle map. It
       requires that we register the bus-off events prior to the (variable number of) CAN
       message events. This leads to the assumed identity mapping. */
    unsigned int idxEdeEv ATTRIB_DBG_ONLY;
    idxEdeEv = ede_registerExternalEventSource
                            ( apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_100MS]
                            , /* idxDispatcher */ 0u
                            , /* kindOfEvent */ APT_EV_BUS_OFF
                            , /* senderHandleEvent */ 0u /* doesn't care */
                            , /* callback */ onInitBus
                            , /* refEventSourceData */ 0u
                            );
    assert(idxEdeEv == APT_EV_BUS_OFF);

    idxEdeEv = ede_registerExternalEventSource
                            ( apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_100MS]
                            , /* idxDispatcher */ 0u
                            , /* kindOfEvent */ APT_EV_RECOVERED_FROM_BUS_OFF
                            , /* senderHandleEvent */ 0u /* doesn't care */
                            , /* callback */ onInitBus
                            , /* refEventSourceData */ 0u
                            );
    assert(idxEdeEv == APT_EV_RECOVERED_FROM_BUS_OFF);

    /* Now register all transmitted CAN frames at the dispatcher engines. This is generated
       code. */
    LOG_INFO( main_hGlobalLogger
            , "%.1f ms: "
              "apt_taskInit: Calling the auto-code initialization of the CAN interface engine"
            , oss_tiSim / 1000.0
            );
    cbk_initInterface();
    
    /* Create the senders. We have one instance with two ports to serve the two
       dispatchers. */
    ede_eventSenderPort_t portAry[APT_NO_DISPATCHER_SYSTEMS] =
    {
        [APT_IDX_DISPATCHER_SYSTEM_10MS]  = portSender10ms,
        [APT_IDX_DISPATCHER_SYSTEM_100MS] = portSender100ms,
    };
    ede_mapSenderEvHandleToIdx_t mapSdrEvHdlToEdePortIdx =
    {
        .addKeyValuePair = mhn_addMapEntrySenderEvHandleToSenderPortIndex,
        .getValue = mhn_mapSenderEvHandleToSenderPortIndex,
        .hInstance = 0u, /* doesn't care, we only have one implicit instance */
    };
    initOk = ede_createSender( &_hOsEventSender
                             , portAry
                             , /* noPorts */ 2u
                             , &mapSdrEvHdlToEdePortIdx
                             , &apt_memoryPoolOS
                             );
    assert(!initOk ||  _hOsEventSender != EDE_INVALID_SENDER_HANDLE);

} /* End of apt_taskInit */




/**
 * Demo code of the regularly executed 10ms task of the APSW. The engine of the CAN
 * interface is clocked and the decoded and pre-processed CAN information can be consumed
 * by the APSW. Vice versa, the APSW provided functional results are encoded and timely
 * sent by the engine. All data access can be done easy and directly since no race
 * conditions occur.
 */
void apt_task10ms()
{
    LOG_DEBUG( main_hGlobalLogger
             , "%.1f ms: "
               "apt_task10ms: Invoked by OS"
             , oss_tiSim / 1000.0
             );

    /* Call the step function of the CAN interface engine for this task. */
    ede_dispatcherMain( apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_10MS]
                      , /* idxDispatcher */ 0u
                      );

    /* Call the step function of the functional application code. This would usually be an
       external module or component (APSW). */
    pwr_computeEnginePwr();

} /* End of apt_task10ms */




/**
 * Demo code of the regularly executed 100ms task of the APSW. The engine of the CAN
 * interface is clocked and the decoded and pre-processed CAN information can be consumed
 * by the APSW. Vice versa, the APSW provided functional results are encoded and timely
 * sent by the engine. All data access can be done easy and directly since no race
 * conditions occur.
 */

void apt_task100ms()
{
    LOG_DEBUG( main_hGlobalLogger
             , "%.1f ms: "
               "apt_task100ms: Invoked by OS"
             , oss_tiSim / 1000.0
             );

    /* Call the step function of the CAN interface engine for this task. */
    ede_dispatcherMain( apt_hDispatcherSystemAry[APT_IDX_DISPATCHER_SYSTEM_100MS]
                      , /* idxDispatcher */ 0u
                      );

    /* Call the step function of the functional application code. This would usually be an
       external module or component (APSW). */
    pwr_checkUserLimits();

} /* End of apt_task100ms */




/**
 * The shutdown task of this simulation environment. It is used for diagnostic purpose only.
 */

void apt_taskShutdown()
{
    const unsigned int noEvQFull10ms = ede_getNoSenderPortBlockedEvents
                                                ( _hOsEventSender
                                                , /* idxPort */ APT_IDX_DISPATCHER_SYSTEM_10MS
                                                )
                     , noEvQFull100ms = ede_getNoSenderPortBlockedEvents
                                                ( _hOsEventSender
                                                , /* idxPort */ APT_IDX_DISPATCHER_SYSTEM_100MS
                                                );
    LOG_LOG( main_hGlobalLogger
           , noEvQFull10ms>0u || noEvQFull100ms>0u? log_warn: log_info
           , "%.1f ms: "
             "apt_taskShutdown: "
             "Number of queue full events: %u (10ms task),  %u (100ms task)"
           , oss_tiSim / 1000.0
           , noEvQFull10ms, noEvQFull100ms
           );

#if MEM_DIAGNOSTIC_INTERFACE == 1
    LOG_INFO( main_hGlobalLogger
            , "%.1f ms: "
              "apt_taskShutdown: "
              "Consumed memory of CAN heap OS: %u Byte, remaining heap memory: %u Byte"
            , oss_tiSim / 1000.0
            , apt_memoryPoolOS.getNbrOfAllocatedBytes(apt_memoryPoolOS.hInstance)
            , apt_memoryPoolOS.getNbrOfAvailableBytes(apt_memoryPoolOS.hInstance)
            );
    if(apt_memoryPoolOS.getNbrOfAllocatedBytes(apt_memoryPoolOS.hInstance)
       < APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE
      )
    {
        LOG_WARN( main_hGlobalLogger
                , "%.1f ms: "
                  "apt_taskShutdown: "
                  "Size of CAN heap OS could be decreased by %u Byte"
                , oss_tiSim / 1000.0
                , APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE
                  - apt_memoryPoolOS.getNbrOfAllocatedBytes(apt_memoryPoolOS.hInstance)
                );
    }
    LOG_INFO( main_hGlobalLogger
            , "%.1f ms: "
              "apt_taskShutdown: "
              "Consumed memory of CAN heap APSW: %u Byte, remaining heap memory:"
              " %u Byte"
            , oss_tiSim / 1000.0
            , apt_memoryPoolAPSW.getNbrOfAllocatedBytes(apt_memoryPoolAPSW.hInstance)
            , apt_memoryPoolAPSW.getNbrOfAvailableBytes(apt_memoryPoolAPSW.hInstance)
            );
    if(apt_memoryPoolAPSW.getNbrOfAllocatedBytes(apt_memoryPoolAPSW.hInstance)
       < APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE
      )
    {
        LOG_WARN( main_hGlobalLogger
                , "%.1f ms: "
                  "apt_taskShutdown: "
                  "Size of CAN heap APSW could be decreased by %u Byte"
                , oss_tiSim / 1000.0
                , APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE
                  - apt_memoryPoolAPSW.getNbrOfAllocatedBytes(apt_memoryPoolAPSW.hInstance)
                );
    }
#else
    LOG_INFO( main_hGlobalLogger
            , "%.1f ms: "
              "apt_taskShutdown: "
              "No diagnostic API for module mem_malloc available. No information about"
              " heap size and usage can be given"
            , oss_tiSim / 1000.0
            );
#endif /* MEM_DIAGNOSTIC_INTERFACE == 1 */
} /* End of apt_taskShutdown */





/**
 * @file apt_applicationTask.c
 * This file contains the application tasks.
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
/* Module interface
 *   apt_irqHandlerRxCan
 *   apt_irqHandlerBusOff
 *   apt_taskInit
 *   apt_task10ms
 *   apt_task100ms
 *   apt_taskShutdown
 * Local functions
 */

/// @todo Test creation of suspended timers, single shot, no autokill

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "main.h"
#include "oss_operatingSystemSimulation.h"
#include "mhn_mapOsFrameHandleToCanIfHandle.h"
#include "mem_malloc.h"
#include "cde_canDispatcherEngine.h"
#include "cbk_callbacks.h"
#include "pwr_computeEnginePower.h"
#include "cst_canStatistics.h"
#include "apt_applicationTask.h"


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
boolean_t apt_canBusOff = false;
 

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
    boolean_t success = cde_postFrameEvent( /* idxBus */ OSS_CAN_BUS_PT
                                          , /* osHandle */ hFrame
                                          , /* kindOfEvent */ CDE_EV_FRAME_RECEPTION
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

void apt_irqHandlerBusOff(boolean_t isOff)
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
    boolean_t success = cde_postBusEvent( /* idxBus */ OSS_CAN_BUS_PT
                                        , /* kindOfEvent */ isOff 
                                                            ? APT_EV_BUS_OFF
                                                            : APT_EV_RECOVERED_FROM_BUS_OFF
                                        , /* pData */ NULL
                                        , /* sizeOfData */ 0
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

static void onBusOnOff(const cde_callbackContext_t *pContext)
{
/* This dispatcher is run in a 100ms period. All times will be rounded to this grid. */
#define DELAY_TILL_RESTART_ATTEMPT_IN_MS 250

    static cde_handleTimer_t timerRecovery_ = CDE_INVALID_TIMER_HANDLE;
    
    /* Here we demonstrate the "traditional" event handler structure with a large switch
       statement. An alternative could be a separate callback for the timer events. The
       external events (bus-off and recovery in this example) cannot be delegated to
       different callbacks. */
    switch(cde_getKindOfEvent(pContext))
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
        if(timerRecovery_ != CDE_INVALID_TIMER_HANDLE)
        {
            cde_retriggerSingleShotTimer( pContext
                                        , timerRecovery_
                                        , DELAY_TILL_RESTART_ATTEMPT_IN_MS
                                        );
        }
        else
        {
            timerRecovery_ = cde_createSingleShotTimer( pContext
                                                      , DELAY_TILL_RESTART_ATTEMPT_IN_MS
                                                      , onBusOnOff
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                                      , /* pUserContextData */ NULL
#endif
                                                      , /* killAtDueTime */ true
                                                      );
            assert(timerRecovery_ != CDE_INVALID_TIMER_HANDLE);
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
        if(timerRecovery_ != CDE_INVALID_TIMER_HANDLE)
        {
            cde_killTimer(pContext, timerRecovery_);
            timerRecovery_ = CDE_INVALID_TIMER_HANDLE;
        }
        break;
        
    case CDE_TIMER_ELAPSED:
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
#if CDE_ENABLE_API_GET_INDEX_BUS == 1
        assert(cde_getIdxBus(pContext) == OSS_CAN_BUS_PT);
#endif    
        oss_restartCanBus(OSS_CAN_BUS_PT);
        
        /* We don't know if the restart will succeed. Better to repeat the attempt after a
           (longer) while. As we applied a single shot timer with auto-kill, we can't
           simply reuse the same timer. We create a new one. True code would probably
           better use a single shot timer without auto-kill but this choice lets us test
           more features. */        
        timerRecovery_ = cde_createSingleShotTimer( pContext
                                                  , 2*DELAY_TILL_RESTART_ATTEMPT_IN_MS
                                                  , onBusOnOff
#if CDE_ENABLE_TIMER_CONTEXT_DATA == 1
                                                  , /* pUserContextData */ NULL
#endif
                                                  , /* killAtDueTime */ true
                                                  );
        assert(timerRecovery_ != CDE_INVALID_TIMER_HANDLE);
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
 
static void onInitBus(const cde_callbackContext_t *pContext)
{
    assert(cde_getKindOfEvent(pContext) == CDE_EV_BUS_INIT);
    LOG_DEBUG( main_hGlobalLogger    
             , "%.1f ms: "
               "onInitBus: Invoked by dispatcher"
             , oss_tiSim / 1000.0
             );
#if CDE_ENABLE_API_GET_INDEX_BUS == 1
    assert(cde_getIdxBus(pContext) == OSS_CAN_BUS_PT);
#endif    
    
    /* The only action is to implement the final event handler for the bus off events. We
       could also use this callback all the time and would then end up with the
       "traditional" look of an event handler having a switch case for all supported kinds
       of events. */
    cde_installCallback(pContext, onBusOnOff);
    
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
#ifdef DEBUG
    boolean_t initOk;
#endif

    /* Initialize the modules. */
    static char heapMemoryForCanInterface[APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    mem_initModule( /* pAppMemory */ heapMemoryForCanInterface
                  , /* sizeOfAppMemory */ sizeof(heapMemoryForCanInterface)
                  );

#ifdef DEBUG
    initOk =
#endif
    cde_initModule( /* maxNoBuses */ 1
                  , /* maxNoFrames */ CST_NO_CAN_FRAMES
                  , /* noDispacherQueues */ 2
                  );
    assert(initOk);
    
    /* Create the required dispatcher queues. */
#ifdef DEBUG
    initOk =
#endif
    cde_createDispatcher( /* idxQueue */ APT_IDX_DISPATCHER_10MS
                        , /* maxQueueLength */ 4
                        , /* sizeOfElement */ 8
                        , /* tiTic */ 10 /* ms */
                        );
    assert(initOk);
#ifdef DEBUG
    initOk =
#endif
    cde_createDispatcher( /* idxQueue */ APT_IDX_DISPATCHER_100MS
                        , /* maxQueueLength */ 4
                        , /* sizeOfElement */ 8
                        , /* tiTic */ 100 /* ms */
                        );
    assert(initOk);

    /* The CAN interface engine depends on some external code. A map needs to be
       implemented by the integrator and now it is registered for use in the engine. The
       registration of the externally implemented function needs to be done prior to the
       frame registration. */
    cde_installMapOsHandleFrameToCdeIndex
            ((cde_mapOsHandleFrameToCdeIndex_t)
             { .fctMakeMapEntryOsHandleFrameToCdeIndex = mhn_addOsToCdeHandlePair
             , .fctMapOsHandleFrameToCdeIndex = mhn_mapOsFrameHandleToCdeIdx
             }
            );

    LOG_INFO( main_hGlobalLogger    
            , "%.1f ms: "
              "apt_taskInit: Calling the auto-code initialization of the CAN interface engine"
            , oss_tiSim / 1000.0
            );
    cbk_initInterface();

    /* The single CAN bus in this sample integration is registered as well. This is done to
       demonstrate the possibility of notifying occasional bus (not frame) related events
       to dedicated callbacks. The implementation of the callbacks, which handle the
       notifications are purposely not auto-coded by the code generator. It could easily do
       as the network databases listen the buses, too, but the added value would be quite
       low; the set of buses is very small and predetermined and fixed. Providing the code
       in templates is inefficient under these circumstances. */
    cde_registerBus( /* idxBus */ 0
                   , /* idxDispatcher */ APT_IDX_DISPATCHER_100MS
                   , /* callback */ onInitBus
                   );

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
    cde_dispatcherMain(APT_IDX_DISPATCHER_10MS);

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
    cde_dispatcherMain(APT_IDX_DISPATCHER_100MS);

    /* Call the step function of the functional application code. This would usually be an
       external module or component (APSW). */
    pwr_checkUserLimits();

} /* End of apt_task100ms */




/**
 * The shutdown task of this simulation environment. It is used for diagnostic purpose only.
 */

void apt_taskShutdown()
{
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
    LOG_LOG( main_hGlobalLogger
           , noEvQFull10ms>0 || noEvQFull100ms>0? log_warn: log_info
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
              "Consumed memory of CAN heap: %u Byte in %u chunks, remaining heap memory:"
              " %u Byte"
            , oss_tiSim / 1000.0
            , mem_getNbrOfAllocatedBytes() 
            , mem_getNbrOfAllocatedChunks() 
            , mem_getNbrOfAvailableBytes() 
            );
    if(mem_getNbrOfAllocatedBytes() < APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE)
    {
        LOG_WARN( main_hGlobalLogger    
                , "%.1f ms: "
                  "apt_taskShutdown: "
                  "Size of CAN heap could be decreased by %u Byte"
                , oss_tiSim / 1000.0
                , APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE - mem_getNbrOfAllocatedBytes()
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





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
 *   csh_callbackOnBusStateChange
 *   csh_callbackOnReceiveCanFrame
 *   apt_taskInit
 *   apt_task10ms
 *   apt_task100ms
 * Local functions
 *   checkFrameHandles
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>

#include "rtos_assert.h"
#include "mem_malloc.h"
#include "cde_canDispatcherEngine.h"
#include "cbk_callbacks.h"
#include "cst_canStatistics.h"
#include "csh_canShield.h"
#include "upd_updateDisplay.h"
#include "pwr_computeEnginePower.h"
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
 
/** A counter of queue overrun events for bus events. */
uint16_t apt_noLostBusStateEvents = 0;

/** A counter of queue overrun events for frame events. */
uint16_t apt_noLostFrameEvents = 0;

/** A timer object to implement the bus-off recovery strategy. */
static cde_handleTimer_t _hTimerBusRecovery = CDE_INVALID_TIMER_HANDLE;


/*
 * Function implementation
 */

#ifdef DEBUG
/**
 * This is the dispatcher engine's hook function, which it calls to add a new entry to the
 * map of handle mappings. The map should be capable to return the frame handles as used in
 * the CAN interface if the operating system handle of the frame and the bus it is
 * transmitted on is given.\n
 *   In the Arduino integration operating system handle and dispatcher engine handle are
 * identical as null based indexes are used for both. We don't build a mapping table and
 * don't really need this function but we apply it yet for checking the identity of
 * handles. An assertion fires if they would not.
 *   @return
 * This map implementation will never fail to add a new entry and it always returns \a true.
 *   @param canId
 * The CAN ID of the registered frame.
 *   @param idxBus
 * The identification of the bus the frame is tranmitted on as a null based index.
 *   @param osHandleFrame
 * The identification of the frame as operating system handle.
 *   @param cdeIdxFrame
 * The handle of the registered frame as used in the CAN interface.\n
 *   This handle kind has some simple characteristics, which can help to find the easiest
 * possible implementation of the needed mapping table:\n
 *   - The handle is a linear null based index
 *   - The handles are assigned in the order of registration calls, i.e. this function will
 * always see the handles values starting with null in its first invokation, followed by
 * one, two and so forth
 *   @param isInbound
 * The transmission direction of the registered frame.\n
 *   In many real environments the mapping can be limited to received frames. Only if frame
 * related events for sent frames have to be processed then a full mapping for all frames
 * is required.
 *   @remark
 * This function is called during initialization of the CAN interface, which is done in a
 * race condition free, single threaded context. This function is called repeatedly for
 * each known frame but the calls will be strictly sequential.
 */

static boolean_t checkFrameHandles( unsigned long canId ATTRIB_UNUSED
                                  , unsigned int idxBus ATTRIB_UNUSED
                                  , cde_osHandleFrame_t osHandleFrame ATTRIB_DBG_ONLY
                                  , unsigned int cdeIdxFrame ATTRIB_DBG_ONLY
                                  , boolean_t isInbound ATTRIB_UNUSED
                                  )
{
    /* In our simple example the simulated OS and the engine both use null based linear
       indexes in the order of registration, or identical handles with other words. We just
       check this but don't store the handle. */
    ASSERT((unsigned int)osHandleFrame == cdeIdxFrame);
    
    return true;
    
} /* End of checkFrameHandles */
#endif




/**
 * Our simulated platform has an interrupt to notify changes of the bus state, particularly
 * bus-off and successful restart.
 *   @param newState
 * The new bus state.
 */

void csh_callbackOnBusStateChange(csh_stateCanBus_t newState)
{
    /* Our simple application just handles bus-off and recovery. */
    unsigned int kindOfEvent;
    if(newState == csh_stsBusOff)
        kindOfEvent = APT_EV_BUS_OFF;
    else if(newState == csh_stsBusActive)
        kindOfEvent = APT_EV_RECOVERED_FROM_BUS_OFF;
    else
    {
        ASSERT(false);
        kindOfEvent = CDE_EV_INVALID;
    }
    
    /* The bus index here relates to the index as used in the initialization call
       cde_registerBus in apt_taskInit. The Arduino CAN shield only supports a single bus
       and there's no concept of an enumeration or handle in the CAN API. */
    boolean_t success = cde_postBusEvent( /* idxBus */ 0
                                        ,  kindOfEvent
                                        , /* pData */ NULL
                                        , /* sizeOfData */ 0
                                        );
    if(!success)
    {
        /* A global counter is used as simple error reporting. This code is executed by the
           task of highest priority. No access control needs to be implemented here. */
        if(++apt_noLostBusStateEvents == 0)
            -- apt_noLostBusStateEvents;
    }
} /* End of csh_callbackOnBusStateChange */




/**
 * The application owned part of the CAN reception interrupt or the CAN reception
 * callback. In each integration, this callback will be used to feed received CAN frames
 * into the input queue of the appropriate dispatcher engine for (later) processing.\n
 *   This callback will always be executed in the interrupt CPU context. The later
 * processing of the frame is done by the engine in the context it has been started in.
 * This is a normal application task context, ideally the only task, which requires access
 * to the frame's contents. If so, no further attention has to be drawn to inter-task
 * communication and data exchange.
 *   @param idxMto
 * Our Arduino CAN shield reports the received CAN frame by index to the message transfer
 * object, which emitted the interrupt. Through this handle the API of the CAN shield
 * provides access to the received data.
 */

void csh_callbackOnReceiveCanFrame(uint8_t idxMto)
{
    /* Retrieve the data contents of the received frame. */
    uint8_t DLC = csh_getCanDLC(idxMto)
          , frameContents[DLC];
    csh_getFrameData(idxMto, sizeof(frameContents), &frameContents[0]);

    /* Having the CAN interface handle of the received frame, we can post a frame received
       event to the dispatcher.
         idxBus: The Arduino CAN shield only supports a single bus and doesn't know about a
       bus index or handle. In this integration, the applied mapping
       (idxBus,idxMto)->idxFrame must not make use of the bus index. */
    boolean_t success = cde_postFrameEvent( /* idxBus */ 0
                                          , /* osHandleFrame */ idxMto
                                          , /* kindOfEvent */ CDE_EV_FRAME_RECEPTION
                                          , /* pData */ &frameContents[0]
                                          , /* sizeOfData */ DLC
                                          );
    if(!success)
    {
        /* A global counter is used as simple error reporting. This code is executed by the
           task of highest priority. No access control needs to be implemented here. */
        if(++apt_noLostFrameEvents == 0)
            -- apt_noLostFrameEvents;
    }
} /* End of csh_callbackOnReceiveCanFrame */




/**
 * The callback for the bus related events.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onBusOnOff(const cde_callbackContext_t *pContext)
{
/* This dispatcher is run in a 100ms period. All times will be rounded to this grid. */
#define DELAY_TILL_RESTART_ATTEMPT_IN_MS 3000

    ASSERT(_hTimerBusRecovery != CDE_INVALID_TIMER_HANDLE)
    
    /* Here we demonstrate the "traditional" event handler structure with a large switch
       statement. An alternative could be a separate callback for the timer events. The
       external events (bus-off and recovery in this example) cannot be delegated to
       different callbacks. */
    switch(cde_getKindOfEvent(pContext))
    {
    case APT_EV_BUS_OFF:
        /* The information is made public in the context of this APSW task. */
        apt_canBusOff = true;
        
        /* We create a timer in order to try a recovery after a while. There's no guarantee
           that the notifications off and recovered will always appear alternatingly. If
           the bus-off arrives twice, then we might already have a timer created. We try to
           retrigger an existing timer first. */
        cde_retriggerSingleShotTimer( pContext
                                    , _hTimerBusRecovery
                                    , DELAY_TILL_RESTART_ATTEMPT_IN_MS
                                    );
        break;
  
    case APT_EV_RECOVERED_FROM_BUS_OFF:
        /* The information is made public in the context of this APSW task. */
        apt_canBusOff = false;
        
        /* We stop the running timer; triggering of recovery is no longer required. A
           weakness of this "application code" is that we will continue making attempts to
           recover if we missed this event - which can happen due to a queue full
           situation. */
        cde_suspendSingleShotTimer(pContext, _hTimerBusRecovery);
        break;
        
    case CDE_TIMER_ELAPSED:
        /* We make an attempt to restart the bus. This requires an according API function
           in the operating system. */    
        csh_restartCanBus();

        /* We don't know if the restart will succeed. Better to repeat the attempt after a
           (longer) while. */        
        cde_retriggerSingleShotTimer( pContext
                                    , _hTimerBusRecovery
                                    , 2*DELAY_TILL_RESTART_ATTEMPT_IN_MS
                                    );
        break;
        
    default:
        ASSERT(false);
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
    ASSERT(cde_getKindOfEvent(pContext) == CDE_EV_BUS_INIT);

    /* The first action is to implement the final event handler for the bus off events. We
       could also use this callback all the time and would then end up with the
       "traditional" look of an event handler having a switch case for all supported kinds
       of events. */
    cde_installCallback(pContext, onBusOnOff);
    
    /* The timers required to implement the error recovery strategy are created here at
       initialization time. These timers are infinitly reused. No further memory allocation
       will take place at run-time. This has two advantages:
         The debug compilation can determine the exact memory consumption of the CAN
       interface engine and report it after return from the initialization. The heap size
       can be tailored on Byte granularity to the amount needed - and without any risk of
       later memory allocation errors.
         The heap is shared between the different dispatchers of the CAN interface engine.
       If there's more than one dispatcher then they are typically run in different tasks,
       which makes mutual exclusion a must for all heap operations. (The initialization
       code here runs still in the race-condition free environment.) We don't need to
       define critical section code if we don't create timer objects at run-time. See macro
       cde_enterCriticalSection() in cde_canDispatcherEngine.config.h, too. */
    ASSERT(_hTimerBusRecovery == CDE_INVALID_TIMER_HANDLE);
    _hTimerBusRecovery = cde_createSingleShotTimer( pContext
                                                  , 0 /* create timer in suspended state */
                                                  , onBusOnOff
                                                  , /* killAtDueTime */ false
                                                  );
    ASSERT(_hTimerBusRecovery != CDE_INVALID_TIMER_HANDLE);

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
    /* Reset global error counter. */
    apt_noLostFrameEvents = 0;
    
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
    ASSERT(initOk);
    
    /* Create the required dispatcher queues. */
#ifdef DEBUG
    initOk =
#endif
    cde_createDispatcher( APT_IDX_DISPATCHER_BUS_EVENTS
                        , /* maxQueueLength */ 2
                        , /* sizeOfElement */ 0
                        , /* tiTick */ 100 /* ms */
                        );
    ASSERT(initOk);
#ifdef DEBUG
    initOk =
#endif
    cde_createDispatcher( APT_IDX_DISPATCHER_FRAME_EVENTS
                        , /* maxQueueLength */ 5
                        , /* sizeOfElement */ 8
                        , /* tiTick */ 10 /* ms */
                        );
    ASSERT(initOk);

#ifdef DEBUG
    /* The CAN CAN shield addresses the MTOs by linear, null based index. We get the same
       index values as handle for the frames, when registering them in the dispatcher
       engine. Therefore, the dispatcher engine's handle and platform's handle when
       receiving that frame will always be identical and a mapping is not required.
       Nonetheless, we install an add-to-map function; solely to have a code location for
       double-checking the identity of the two handle sets at runtime. */
    cde_mapOsHandleFrameToCdeIndex_t mapOsHandleFrameToCdeIndex =
    {
        .fctMakeMapEntryOsHandleFrameToCdeIndex = checkFrameHandles,
        .fctMapOsHandleFrameToCdeIndex = NULL
    };
    cde_installMapOsHandleFrameToCdeIndex(mapOsHandleFrameToCdeIndex);
#endif

    /* The single CAN bus in this sample integration is registered as well. This is done to
       demonstrate the possibility of notifying occasional bus (not frame) related events
       to dedicated callbacks. The implementation of the callbacks, which handle the
       notifications are purposely not auto-coded by the code generator. It could easily do
       as the network databases listen the buses, too, but the added value would be quite
       low; the set of buses is very small and predetermined and fixed. Providing the code
       in templates is inefficient under these circumstances. */
    cde_registerBus( /* idxBus */ 0
                   , /* idxDispatcher */ APT_IDX_DISPATCHER_BUS_EVENTS
                   , /* callback */ onInitBus
                   );

    /* Register all transmitted CAN frames at the engine. This is generated code. */
    cbk_initInterface();

    /* If all callback regard the recommendation not to use dynamic creation of timer
       objects (but they allocate all timers in their init callback and reuse them all time
       long), then we can now print how many Bytes are left on the stack: The heap can
       safely be reduced by this amount of memory. */
#ifdef DEBUG
    printf( "There are %u Bytes left on the heap"
# if MEM_DIAGNOSTIC_INTERFACE == 1
            ". %u Byte have been allocated in %u chunks"
# endif
            "\n"
          , mem_getNbrOfAvailableBytes()
# if MEM_DIAGNOSTIC_INTERFACE == 1
          , mem_getNbrOfAllocatedBytes()
          , mem_getNbrOfAllocatedChunks()
# endif
          );
#endif

    /* Call the init routines of the Embedded Coder generated APSW. */
    pwr_computeEnginePower_initialize();

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
    /* Call the step function of the CAN interface engine for this task. */
    cde_dispatcherMain(APT_IDX_DISPATCHER_FRAME_EVENTS);

    /* Call the 10ms step function of the functional application code. This would usually
       be an external module or component (APSW). */
    pwr_computeEnginePower_step();

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
    /* Call the step function of the CAN interface engine for this task. */
    cde_dispatcherMain(APT_IDX_DISPATCHER_BUS_EVENTS);

    /* Call the 100ms step function of the functional application code; update the
       LCDisplay with the most relevant, current information. */
    upd_updateDisplay();
    
} /* End of apt_task100ms */





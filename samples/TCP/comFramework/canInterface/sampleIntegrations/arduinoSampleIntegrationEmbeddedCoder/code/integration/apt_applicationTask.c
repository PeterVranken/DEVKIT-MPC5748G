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
 *   csh_callbackOnBusStateChange
 *   csh_callbackOnReceiveCanFrame
 *   apt_taskInit
 *   apt_task10ms
 *   apt_task100ms
 * Local functions
 *   checkFrameHandles
 *   getMapValue
 *   onBusOnOff
 *   onInitEvBusOff
 *   onInitEvRecovBusOff
 */

/*
 * Include files
 */

#include "apt_applicationTask.h"

#include <stdlib.h>
#include <stdio.h>

#include "rtos_assert.h"
#include "mem_malloc.h"
#include "cbk_callbacks.h"
#include "pwr_computeEnginePower.h"
#include "cst_canStatistics.h"
#include "csh_canShield.h"
#include "upd_updateDisplay.h"
#include "ede_eventDispatcherEngine.config.h"
#include "ede_eventSender.h"
#include "ede_eventDispatcherEngine.h"
#include "cde_stubs.h"
#include "vsq_dispatcherPortInterface.h"


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
 
/** A memory pool for CAN stack objects, i.e. objects in use by the CAN
    notification/event dispatching process. */
static ede_memoryPool_t apt_memoryPool = EDE_INVALID_MEMORY_POOL;

/** The sender of CAN events. It is connected to both dispatchers. */
static ede_handleSender_t _hOsEventSender = EDE_INVALID_SENDER_HANDLE;

/** The dispatcher system owning the two dispatchers processing CAN events and bus events. */
ede_handleDispatcherSystem_t apt_hDispatcherSystem = EDE_INVALID_DISPATCHER_SYSTEM_HANDLE;

/** A counter of queue overrun events for bus events. */
uint16_t apt_noLostBusStateEvents = 0;

/** A counter of queue overrun events for frame events. */
uint16_t apt_noLostFrameEvents = 0;

/** A timer object to implement the bus-off recovery strategy. */
static ede_handleTimer_t _hTimerBusRecovery = EDE_INVALID_TIMER_HANDLE;


/*
 * Function implementation
 */

/**
 * This is the dispatcher engine's hook function, which it calls to add a new entry to the
 * map of handle mappings. The map should be capable to return the event source index as
 * used in the event dispatchers if the operating system handle of a received message is
 * given.\n
 *   In the Arduino integration operating system handle and dispatcher engine handle are
 * except for a known offset identical as zero based indexes are used for both. We don't
 * build a mapping table and don't really need this function but we apply it yet for
 * checking the expected relation between the handles. An assertion fires if they would
 * not.
 *   @return
 * This map implementation will never fail to add a new entry and it always returns \a
 * true.
 *   @param hInstance
 * The map instance. We make the distinction between CAN Rx events and bus events. Pass
 * #APT_IDX_DISPATCHER_FRAME_EVENTS or #APT_IDX_DISPATCHER_BUS_EVENTS, respectively.
 *   @param kindOfEvent
 * A bus event or #APT_EV_RX_CAN_MSG.
 *   @param osHandleFrame
 * The identification of the frame as operating system handle. Ignored for bus events.
 *   @param edeIdxFrame
 * The handle of the registered event source as used in the dispatcher engine.\n
 *   This handle kind has some simple characteristics, which can help to find the easiest
 * possible implementation of the needed mapping table:\n
 *   - The handle is a linear zero based index
 *   - The handles are assigned in the order of registration calls, i.e. this function will
 * always see the handle values starting with zero in its first invokation, followed by
 * one, two and so forth
 *   @remark
 * This function is called during initialization of the CAN interface, which is done in a
 * race condition free, single threaded context. This function is called repeatedly for
 * each known frame and bus event but the calls will be strictly sequential.
 */
static bool checkFrameHandles( uintptr_t hInstance ATTRIB_DBG_ONLY
                             , ede_kindOfEvent_t kindOfEvent ATTRIB_DBG_ONLY
                             , ede_senderHandleEvent_t osHandleFrame ATTRIB_DBG_ONLY
                             , unsigned int edeIdxFrame ATTRIB_DBG_ONLY
                             )
{
    /* We have a fixed, known mapping. We just check it but don't store the key-value
       pairs. */
#ifdef DEBUG
    if(hInstance == APT_IDX_DISPATCHER_FRAME_EVENTS)
    {    
        /* In our simple example the simulated OS uses zero based linear indexes in the
           order of message registration and the dispather engine uses zero based linear
           indexes in the order of event registration. We register the bus events prior to
           the CAN message events, so this makes a known offset between both indexes. */
        ASSERT((unsigned int)kindOfEvent == APT_EV_RX_CAN_MSG
               &&  (unsigned int)osHandleFrame + APT_EV_RX_CAN_MSG == edeIdxFrame
              );
    }
    else
    {
        /* All events but frame events don't make use of an additional handle space. They
           stands for themselves, the enumeration value kind-of-event is the index of the
           registered event source. (Which requires registering these events first.) */
        ASSERT(hInstance == APT_IDX_DISPATCHER_BUS_EVENTS 
               &&  (unsigned int)kindOfEvent < APT_EV_RX_CAN_MSG
               &&  (unsigned int)kindOfEvent == edeIdxFrame
               &&  (unsigned int)osHandleFrame == 0u
              );
    }
#endif

    return true;
    
} /* End of checkFrameHandles */


/**
 * The map lookup operation of the map. The index of the event source associated with an
 * external event handle is queried.
 *   @return
 * \a true is returned.
 *   @param hInstance
 * This is the identification of the map instance to use. The data type uintptr_t is
 * such that the implementation of the map can hide an index into an array of objects
 * or a pointer to an object behind this value. See field \a hInstance, too.\n
 *   1. Use case mapping external events to registered event sources:\n
 *   Each dispatcher has its own index space for event sources and will apply a
 * dedicated map.\n
 *   2. Use case mapping external events to a sender's port:\n
 *   Each sender has its own index space for its individual ports and it'll use a
 * dedicated, related map instance.
 *   @param pValue
 * The result of the lookup operation is returned by reference.
 *   @param kindOfEvent
 * First element of characterizing the event source under progress. See argument of
 * same name of checkFrameHandles() for more details.
 *   @param osHandleEvent
 * Second element of characterizing the event source under progress. See argument of
 * same name of checkFrameHandles() for more details.
 *   @remark
 * The external implementation of the map function needs to be reentrant only with
 * respect to different map instances. There won't be concurrent calls for one and the
 * same instance.
 */
static bool getMapValue( uintptr_t hInstance ATTRIB_UNUSED
                       , unsigned int * pValue
                       , ede_kindOfEvent_t kindOfEvent ATTRIB_UNUSED
                       , ede_senderHandleEvent_t osHandleEvent
                       )
{
    if(hInstance == APT_IDX_DISPATCHER_FRAME_EVENTS)
    {    
        ASSERT((unsigned int)kindOfEvent == APT_EV_RX_CAN_MSG);
        *pValue = (unsigned int)osHandleEvent + APT_EV_RX_CAN_MSG;
    }
    else
    {
        /* All events but frame events don't make use of an additional handle space. They
           stands for themselves, the enumeration value kind-of-event is the index of the
           registered event source. (Which requires registering these events first.) */
        ASSERT(hInstance == APT_IDX_DISPATCHER_BUS_EVENTS
               &&  (unsigned int)kindOfEvent < APT_EV_RX_CAN_MSG
              );
        *pValue = (unsigned int)kindOfEvent;
    }
    return true;

} /* getMapValue */



/**
 * Our simulated platform has an interrupt to notify changes of the bus state, particularly
 * bus-off and successful restart.
 *   @param newState
 * The new bus state.
 */

void csh_callbackOnBusStateChange(csh_stateCanBus_t newState)
{
    /* Our simple application just handles bus-off and recovery. */
    ede_kindOfEvent_t kindOfEvent;
    if(newState == csh_stsBusOff)
        kindOfEvent = APT_EV_BUS_OFF;
    else if(newState == csh_stsBusActive)
        kindOfEvent = APT_EV_RECOVERED_FROM_BUS_OFF;
    else
    {
        ASSERT(false);
        kindOfEvent = (ede_kindOfEvent_t)(-1);
    }
    
    /* The bus index here relates to the index as used in the initialization call
       cde_registerBus in apt_taskInit. The Arduino CAN shield only supports a single bus
       and there's no concept of an enumeration or handle in the CAN API. */
    const bool success = ede_postEventToPort
                             ( _hOsEventSender
                             , /* idxPort */ APT_IDX_DISPATCHER_BUS_EVENTS
                             , kindOfEvent
                             , /* ede_senderHandleEvent_t */ 0u /* Not used */
                             , /* pData */ NULL
                             , /* sizeOfData */ 0
                             );
    if(!success)
    {
        /* A global counter is used as simple error reporting. This code is executed by the
           task of highest priority. No access control needs to be implemented here. */
        if(++apt_noLostBusStateEvents == 0u)
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
    const uint8_t DLC = csh_getCanDLC(idxMto);
    uint8_t frameContents[DLC];
    csh_getFrameData(idxMto, sizeof(frameContents), &frameContents[0]);

    /* Having the CAN interface handle of the received frame, we can post a frame received
       event to the dispatcher. */
    const bool success = ede_postEventToPort
                             ( _hOsEventSender
                             , /* idxPort */ APT_IDX_DISPATCHER_FRAME_EVENTS
                             , /* kindOfEvent */ APT_EV_RX_CAN_MSG
                             , (ede_senderHandleEvent_t)idxMto
                             , /* pData */ &frameContents[0]
                             , /* sizeOfData */ DLC
                             );
    if(!success)
    {
        /* A global counter is used as simple error reporting. This code is executed by the
           task of highest priority. No access control needs to be implemented here. */
        if(++apt_noLostFrameEvents == 0u)
            -- apt_noLostFrameEvents;
    }
} /* End of csh_callbackOnReceiveCanFrame */




/**
 * The callback for the bus related events.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onBusOnOff(const ede_callbackContext_t *pContext)
{
/* This dispatcher is run in a 100ms period. All times will be rounded to this grid. */
#define DELAY_TILL_RESTART_ATTEMPT_IN_MS 3000

    ASSERT(_hTimerBusRecovery != EDE_INVALID_TIMER_HANDLE)
    
    /* Here we demonstrate the "traditional" event handler structure with a large switch
       statement. An alternative could be a separate callback for the timer events. The
       external events (bus-off and recovery in this example) cannot be delegated to
       different callbacks. */
    switch(ede_getKindOfEvent(pContext))
    {
    case APT_EV_BUS_OFF:
        /* The information is made public in the context of this APSW task. */
        apt_canBusOff = true;
        
        /* We create a timer in order to try a recovery after a while. There's no guarantee
           that the notifications off and recovered will always appear alternatingly. If
           the bus-off arrives twice, then we might already have a timer created. We try to
           retrigger an existing timer first. */
        ede_retriggerSingleShotTimer( pContext
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
        ede_suspendSingleShotTimer(pContext, _hTimerBusRecovery);
        break;
        
    case EDE_EV_TIMER_ELAPSED:
        /* We make an attempt to restart the bus. This requires an according API function
           in the operating system. */    
        csh_restartCanBus();

        /* We don't know if the restart will succeed. Better to repeat the attempt after a
           (longer) while. */        
        ede_retriggerSingleShotTimer( pContext
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
 * The initialization callback for the bus related event APT_EV_BUS_OFF.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onInitEvBusOff(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_EXT_INIT);

    /* The first action is to implement the final event handler for the bus off events. We
       use a common handler for all bus off related events, which leads to the
       "traditional" look of an event handler having a switch case for all supported kinds
       of events. */
    ede_installCallback(pContext, onBusOnOff);
    
    /* The timers required to implement the error recovery strategy are created here at
       initialization time. These timers are infinitly reused. No further memory allocation
       will take place at run-time. This has two advantages:
         The debug compilation can determine the exact memory consumption of the CAN
       interface engine and report it after return from the initialization. The heap size
       can be tailored on Byte granularity to the amount needed - and without any risk of
       later memory allocation errors.
         The memory pool is shared between the different dispatchers of the CAN interface.
       If there's more than one dispatcher then they are typically run in different tasks,
       which makes mutual exclusion a must for all memory pool operations. (The
       initialization code here runs still in the race-condition free environment and
       doesn't require this.) We don't need to define critical section code for the memory
       pool if we don't create timer objects at run-time. */
    ASSERT(_hTimerBusRecovery == EDE_INVALID_TIMER_HANDLE);
    _hTimerBusRecovery = ede_createSingleShotTimer( pContext
                                                  , 0 /* create timer in suspended state */
                                                  , onBusOnOff
                                                  , /* killAtDueTime */ false
                                                  );
    ASSERT(_hTimerBusRecovery != EDE_INVALID_TIMER_HANDLE);

} /* End of onInitEvBusOff */



/**
 * The initialization callback for the bus related event APT_EV_RECOVERED_FROM_BUS_OFF.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 */
static void onInitEvRecovBusOff(const ede_callbackContext_t *pContext)
{
    ASSERT(ede_getKindOfEvent(pContext) == EDE_EV_EVENT_SOURCE_EXT_INIT);

    /* The first action is to implement the final event handler for the recover from bus
       off events. We use a common handler for all bus off related events. */
    ede_installCallback(pContext, onBusOnOff);
    
} /* End of onInitEvRecovBusOff */



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
    
    bool initOk ATTRIB_DBG_ONLY;
    
    /* Initialize the memory pool. Since we create all objects, and particularly timer
       objects at single-threaded initialization time, we don't need a pool with mutual
       exclusion. */
    static char heapMemoryForCanInterface[APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    initOk = mem_createMemoryPool( &apt_memoryPool
                                 , /* pPoolMemory */ heapMemoryForCanInterface
                                 , /* sizeOfPoolMemory */ sizeof(heapMemoryForCanInterface)
                                 , MEM_VOID_CRITICAL_SECTION_OBJECT
                                 );
    ASSERT(initOk);

    /* Create the required dispatcher queues. */
    ede_eventSenderPort_t portSenderMsgRxEvents;
    ede_eventReceiverPort_t portDispatcherMsgRxEvents;
    initOk = vsq_createEventQueue( &portDispatcherMsgRxEvents
                                 , &portSenderMsgRxEvents
                                 , /* maxQueueLength */ 5u /* no messages */
                                 , /* sizeOfPayload */ 8u /* max DLC */
                                 , /* pMemPoolDispatchingProcess */ &apt_memoryPool
                                 , /* pMemPoolSenderOfEvents */     &apt_memoryPool
                                 );
    ASSERT(initOk);
    ede_eventSenderPort_t portSenderBusEvents;
    ede_eventReceiverPort_t portDispatcherBusEvents;
    initOk = vsq_createEventQueue( &portDispatcherBusEvents
                                 , &portSenderBusEvents
                                 , /* maxQueueLength */ 2u /* no bus events */
                                 , /* sizeOfPayload */ 0u /* no payload */
                                 , /* pMemPoolDispatchingProcess */ &apt_memoryPool
                                 , /* pMemPoolSenderOfEvents */     &apt_memoryPool
                                 );
    ASSERT(initOk);

    /* Create the required dispatcher systems.
         +2: The two bus related events. */
    initOk = ede_createDispatcherSystem
                                ( &apt_hDispatcherSystem
                                , /* noEventDispatcherEngines */ APT_NO_DISPATCHERS
                                , /* maxNoEventSourcesExt */ CST_NO_CAN_FRAMES_RECEIVED + 2u
                                , /* maxNoEventSourcesInt */ CST_NO_CAN_FRAMES_SENT
                                , &apt_memoryPool
                                );
    ASSERT(!initOk ||  apt_hDispatcherSystem != EDE_INVALID_DISPATCHER_SYSTEM_HANDLE);

    /* The CAN CAN shield addresses the MTOs by linear, zero based index. We get the
       similar index values as handle for the messages, when registering them in the
       dispatcher engine. The dispatcher engine's handle and platform's handle when
       receiving that message will just differ by a known offset and only a most simple
       mapping is required.
         This sample application purposely makes no use of the map sample implementations,
       which come along with the CAN interface. The application demonstrates that it is
       possible to implement a specific map on-the-fly, which fits optimally to the given
       integration scenario. There's a good chance that this specific implementation is
       more efficient in terms of RAM and CPU consumption. */
    ede_mapSenderEvHandleToIdx_t mapOsHandleEventToEdeIndex =
    {
        .addKeyValuePair = checkFrameHandles,
        .getValue = getMapValue,
        .hInstance = APT_IDX_DISPATCHER_FRAME_EVENTS,
    };
    initOk = ede_createDispatcher( apt_hDispatcherSystem
                                 , APT_IDX_DISPATCHER_FRAME_EVENTS
                                 , /* tiTick */ 10 /* ms */
                                 , /* portAry */ &portDispatcherMsgRxEvents
                                 , /* noPorts */ 1u
                                 , mapOsHandleEventToEdeIndex
                                 );
    ASSERT(initOk);
    mapOsHandleEventToEdeIndex.hInstance = APT_IDX_DISPATCHER_BUS_EVENTS;
    initOk = ede_createDispatcher( apt_hDispatcherSystem
                                 , APT_IDX_DISPATCHER_BUS_EVENTS
                                 , /* tiTick */ 100 /* ms */
                                 , /* portAry */ &portDispatcherBusEvents
                                 , /* noPorts */ 1u
                                 , mapOsHandleEventToEdeIndex
                                 );
    ASSERT(initOk);

    /* The bus-off events from the single CAN bus in this sample integration are registered
       at the dedicated dispatcher. This is done to demonstrate the possibility of
       notifying occasional bus (not message) related events to dedicated callbacks. The
       implementation of the callbacks, which handle the notifications are purposely not
       auto-coded by the code generator. It could easily do as the network databases list
       the buses, too, but the added value would be quite low; the set of buses is very
       small and predetermined and fixed. Providing the code in templates is inefficient
       under these circumstances.
         Note, we have a dependency with our simple implementation of the handle map. It
       requires that we register the bus-off events prior to the (variable number of) CAN
       message events. This leads to the assumed identity mapping for bus events. */
    unsigned int idxEdeEv ATTRIB_DBG_ONLY;
    idxEdeEv = ede_registerExternalEventSource( apt_hDispatcherSystem
                                              , APT_IDX_DISPATCHER_BUS_EVENTS
                                              , /* kindOfEvent */ APT_EV_BUS_OFF
                                              , /* senderHandleEvent */ 0u /* doesn't care */
                                              , /* callback */ onInitEvBusOff
                                              , /* refEventSourceData */ 0u
                                              );
    ASSERT(idxEdeEv == APT_EV_BUS_OFF);
    idxEdeEv = ede_registerExternalEventSource( apt_hDispatcherSystem
                                              , APT_IDX_DISPATCHER_BUS_EVENTS
                                              , /* kindOfEvent */ APT_EV_RECOVERED_FROM_BUS_OFF
                                              , /* senderHandleEvent */ 0u /* doesn't care */
                                              , /* callback */ onInitEvRecovBusOff
                                              , /* refEventSourceData */ 0u
                                              );
    ASSERT(idxEdeEv == APT_EV_RECOVERED_FROM_BUS_OFF);

    /* Now register all transmitted CAN frames at the other dispatcher engine. This is
       generated code. */
    cbk_initInterface();

    /* Create the senders. We have one instance with two ports to serve the two
       dispatchers. We address to the ports directly by index and don't need a map. */
    ede_eventSenderPort_t portAry[APT_NO_DISPATCHERS] =
    {
        [APT_IDX_DISPATCHER_FRAME_EVENTS]  = portSenderMsgRxEvents,
        [APT_IDX_DISPATCHER_BUS_EVENTS] = portSenderBusEvents,
    };
    initOk = ede_createSender( &_hOsEventSender
                             , portAry
                             , /* noPorts */ 2u
                             , /* &mapSdrEvHdlToEdePortIdx */ NULL
                             , &apt_memoryPool
                             );
    ASSERT(!initOk ||  _hOsEventSender != EDE_INVALID_SENDER_HANDLE);

    /* If all callbacks regard the recommendation not to use dynamic creation of timer
       objects (but they allocate all timers in their init callback and reuse them all time
       long), then we can now print how many Bytes are left on the stack: The heap can
       safely be reduced by this amount of memory.
         Note, method getNbrOfAvailableBytes() of a memory pool object is specified as
       optional. */
    if(apt_memoryPool.getNbrOfAvailableBytes != NULL)
    {
        printf( "There are %u Bytes left in the memory pool"
# if MEM_DIAGNOSTIC_INTERFACE == 1
                ". %u Byte have been allocated"
# endif
                "\n"
              , apt_memoryPool.getNbrOfAvailableBytes(apt_memoryPool.hInstance)
# if MEM_DIAGNOSTIC_INTERFACE == 1
              , apt_memoryPool.getNbrOfAllocatedBytes(apt_memoryPool.hInstance)
# endif
              );
    }
    
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
    ede_dispatcherMain(apt_hDispatcherSystem, APT_IDX_DISPATCHER_FRAME_EVENTS);

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
    ede_dispatcherMain(apt_hDispatcherSystem, APT_IDX_DISPATCHER_BUS_EVENTS);

    /* Call the 100ms step function of the functional application code; update the
       LCDisplay with the most relevant, current information. */
    upd_updateDisplay();
    
} /* End of apt_task100ms */





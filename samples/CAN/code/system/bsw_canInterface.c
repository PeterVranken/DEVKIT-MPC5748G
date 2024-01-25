/**
 * @file bsw_canInterface.c
 * Interface for CAN communication, using the technology from the comFramework project
 * (http://sourceforge.net/p/comframe/wiki/).
 *
 * Copyright (C) 2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   bsw_osOnRxCan
 *   bsw_osInitCanInterface
 *   bsw_getCanRxPort
 * Local functions
 */

/*
 * Include files
 */

#include "bsw_canInterface.h"

#include <assert.h>

#include "typ_types.h"
#include "mem_malloc.h"
#include "cdr_canDriverApi.h"
#include "ede_externalInterfaces.h"
#include "vsq_dispatcherPortInterface.h"
#include "ede_eventSender.h"
#include "bsw_basicSoftware.h"

/*
 * Defines
 */

/** The size of the heap memory, which is statically allocated for the CAN interface. The
    value should be set as little as possible; if set too little then the OS initialzation
    will fail and the system won't start up. If it is too large then the remaining memory
    is unaccessible by any other part of the SW and wasted.
      @remark Consider to begin with a large value and then use the function \a
    ede_memoryPool_t.getNbrOfAvailableBytes() in DEBUG compilation in order to get the
    optimal setting for this define. */
#define SIZE_OF_HEAP_OS_FOR_CAN_INTERFACE  8192 /* Byte */


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** The sender of CAN events. It is connected to both dispatchers. */
static ede_handleSender_t SDATA_OS(_hEventSender) = EDE_INVALID_SENDER_HANDLE;

/** The port of the tail of the dispatcher queue. */
static ede_eventSenderPort_t SDATA_OS(_portSender) = EDE_INVALID_EVENT_SENDER_PORT;

/** The port of the head of the dispatcher queue; to be used by the QM application code. */
static ede_eventReceiverPort_t SDATA_P1(_portDispatcher)= EDE_INVALID_EVENT_RECEIVER_PORT;

/** The total count of all ever received messages, including the lost one because of queue
    full events. The counter is not saturated and will wrap at the implementation limit.
    This public interface can be read at any time by any context on the core, which serves
    the CAN ISRs. */
volatile unsigned long SDATA_OS(bsw_noCanRxMsgs) = 0;

/** The total number of lost Rx messages because of queue full. This public interface can be
    read at any time by any context on the core, which serves the CAN ISRs. */
volatile unsigned long DATA_OS(bsw_noEvCanRxQueueFull) = 0;


#ifdef DEBUG
/** Heap configuration: This is the number of never used bytes of OS heap memory. Just
    meant for diagnosis at develepoment time: The CAN Rx queue is configured such that it
    should consume nearly all bytes from the memory pool so that this variable should
    indicate only a few remaining Byte. See #SIZE_OF_HEAP_OS_FOR_CAN_INTERFACE also. */
static unsigned int DATA_OS(bsw_canIf_noUnusedBytesInOSHeap) = UINT_MAX;

/** Heap configuration: This is the number of never used bytes of P1 heap memory. Just
    meant for diagnosis at develepoment time: This variable should indicate only a few
    remaining Byte. See usage of memory pool in bsw_osInitCanInterface() also. */
static unsigned int DATA_OS(bsw_canIf_noUnusedBytesInP1Heap) = UINT_MAX;
#endif

/* Double-check consistency of public and internally known enumerations for buses and CAN
   events. */
_Static_assert( BSW_CAN_BUS_0 + 1u == cdr_canDev_noCANDevicesEnabled
              , "All bus related Rx events are expected to form a gapless, zero based sequence"
              );

/*
 * Function implementation
 */

/**
 * The reception callback from the CAN driver. The callback will be used to feed received
 * CAN messages into the CAN event queue owned by the CAN interface. An APSW can connect to
 * that queue.
 *   @param pRxCanMsg
 * A typical CAN driver callback will pass some information about the received CAN message.
 * Here, in this sample, it is a struct containing message handle from the OS, CAN ID and,
 * payload. The information is passed in by reference.
 */
void bsw_osOnRxCan(const bsw_rxCanMessage_t *pRxCanMsg)
{
    /* Having the CAN interface handle of the received message, we can post a message-received
       event to the interfacing event queue. */
    const ede_kindOfEvent_t kindOfEvent = pRxCanMsg->idxCanBus;
    assert(kindOfEvent <= BSW_CAN_BUS_0);
    const bool success = ede_postEvent( _hEventSender
                                      , kindOfEvent
                                      , /* senderHandleEvent */ pRxCanMsg->idxMailbox
                                      , /* pData */ pRxCanMsg->payload
                                      , /* sizeOfData */ pRxCanMsg->sizeOfPayload
                                      );
    if(!success)
    {
        /* Count all received messages, which are lost because of queue full. */
        const unsigned long newVal = bsw_noEvCanRxQueueFull + 1;
        if(newVal != 0)
            bsw_noEvCanRxQueueFull = newVal;
    }

    /* Count all received messages. This counter is not saturated. */
    ++ bsw_noCanRxMsgs;

} /* End of bsw_osOnRxCan */



/**
 * Initialize the CAN interface.\n
 *   Main part of the BSW's CAN interface is an event queue, which is filled with Rx
 * messages and which can be read out by a QM process via a public port.
 *   @return
 * Normally, the function will return \a true. \a false is returned in case of a lack of
 * memory. Due to the static memory allocation concept, \a false can be considered and
 * handled as a development (not a runtime error) error; an assertion will be appropriate
 * in most situations.
 */
bool bsw_osInitCanInterface(void)
{
    /* Create the memory pool we use for all CAN stack objects inside the OS. These are the
       sender objects and the queue tails. This memory needs to be accessible during the
       entire remaining runtime of the software. */
    static char DATA_OS(heapMemoryOSForCanInterface)[SIZE_OF_HEAP_OS_FOR_CAN_INTERFACE];
    ede_memoryPool_t memoryPoolOS = EDE_INVALID_MEMORY_POOL;
    const mem_criticalSection_t mutualExclusionGuard = MEM_VOID_CRITICAL_SECTION_OBJECT;
    bool success = mem_createMemoryPool
                                    ( &memoryPoolOS
                                    , /* pPoolMemory */ heapMemoryOSForCanInterface
                                    , /* sizeOfPoolMemory */ sizeof(heapMemoryOSForCanInterface)
                                    , mutualExclusionGuard
                                    );

    ede_memoryPool_t memoryPoolP1 = EDE_INVALID_MEMORY_POOL;
    if(success)
    {
        /* Create a minimalist memory pool for the QM process, which allows to create just the
           queue head object. */
        #define SIZE_OF_HEAP_P1_FOR_CAN_INTERFACE   (36u)
        static char DATA_P1(heapMemoryP1ForCanInterface)[SIZE_OF_HEAP_P1_FOR_CAN_INTERFACE];
        const mem_criticalSection_t mutualExclusionGuard = MEM_VOID_CRITICAL_SECTION_OBJECT;
        success = mem_createMemoryPool
                                ( &memoryPoolP1
                                , /* pPoolMemory */ heapMemoryP1ForCanInterface
                                , /* sizeOfPoolMemory */ sizeof(heapMemoryP1ForCanInterface)
                                , mutualExclusionGuard
                                );
        #undef SIZE_OF_HEAP_P1_FOR_CAN_INTERFACE
    }

    /* Create the head object of the required dispatcher queue. */
    if(success)
        success = vsq_createEventQueueHead(&_portDispatcher, &memoryPoolP1);

    /* Create the tail object of the required dispatcher queue. */
    if(success)
    {
        /* The length of the queue is estimated such that the given memory pool is widely
           consumed. */
        #define MAX_DLC                     8u
        #define INTERNAL_OVERHEAD_VSQ_ELEM  4u
        #define INTERNAL_OVERHEAD_VSQ_QUEUE 48u
        #define INTERNAL_OVERHEAD_MEM_POOL  28u
        #define MARGIN                      40u /* Uncertainty alignment and sender object */
        #define SIZE_OF_QUEUED_ELEMENT      (sizeof(ede_externalEvent_t)+MAX_DLC    \
                                             +INTERNAL_OVERHEAD_VSQ_ELEM            \
                                            )
        #define LENGTH_OF_QUEUE             ((sizeof(heapMemoryOSForCanInterface)   \
                                              - INTERNAL_OVERHEAD_VSQ_QUEUE         \
                                              - INTERNAL_OVERHEAD_MEM_POOL          \
                                              - MARGIN                              \
                                             ) / SIZE_OF_QUEUED_ELEMENT             \
                                            )
        success = vsq_createEventQueueTail( &_portSender
                                          , /* maxQueueLength */ LENGTH_OF_QUEUE
                                          , /* sizeOfElement */  MAX_DLC
                                          , /* pMemPoolSenderOfEvents */ &memoryPoolOS
                                          );
        #undef MAX_DLC
        #undef INTERNAL_OVERHEAD_VSQ_ELEM
        #undef INTERNAL_OVERHEAD_VSQ_QUEUE
        #undef INTERNAL_OVERHEAD_MEM_POOL
        #undef MARGIN
        #undef SIZE_OF_QUEUED_ELEMENT
        #undef LENGTH_OF_QUEUE
    }

    /* Link head and tail of the queue. */
    if(success)
    {
        vsq_linkEventQueueTailWithHead(_portSender, _portDispatcher);
        vsq_linkEventQueueHeadWithTail(_portDispatcher, _portSender);
    }

    /* Create the only sender. */
    if(success)
    {
        success = ede_createSender( &_hEventSender
                                  , &_portSender
                                  , /* noPorts */ 1u
                                  , /* pMapSenderEvHandleToPortIndex */ NULL
                                  , &memoryPoolOS
                                  );
        assert(!success ||  _hEventSender != EDE_INVALID_SENDER_HANDLE);
    }

#ifdef DEBUG
    if(success)
    {
        bsw_canIf_noUnusedBytesInOSHeap = MEM_GET_NBR_OF_AVAILABLE_BYTES(memoryPoolOS);
        bsw_canIf_noUnusedBytesInP1Heap = MEM_GET_NBR_OF_AVAILABLE_BYTES(memoryPoolP1);
    }
#endif

    return success;

} /* bsw_osInitCanInterface */



/**
 * The APSW process P1 (bsw_pidUser) can dock into the CAN interface of the BSW by getting
 * a receiver port, which can be used to connect a dispatcher engine. This API provides the
 * port to the ASPW.\n
 *   The events, which can be received via the port use the bus index from the CAN driver
 * as kind of event and the index of the message mailbox as sender handle. The index of the
 * message mailbox is the same as agreed on, when registering the message.
 *   @return
 * Get the port.
 *   @remark
 * The simple implementation of this sample doesn't check for correct use of the API. The
 * port must be got just once and cannot be shared between different contexts. Moreover,
 * the port is prepare for use by process P1. If any of these conditions disare not obeyed
 * then the SW will have an unpredicted behavior up to a possible instability of P1. Safety
 * should not be affected as only the CAN communication with QM SW is affected.
 */
ede_eventReceiverPort_t bsw_getCanRxPort(void)
{
    return _portDispatcher;
}




#ifndef APT_APPLICATIONTASK_INCLUDED
#define APT_APPLICATIONTASK_INCLUDED
/**
 * @file apt_applicationTask.h
 * Definition of global interface of module apt_applicationTask.c
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

/*
 * Include files
 */

#include <stdatomic.h>

#include "types.h"
#include "cst_canStatistics.h"
#include "rtos_rtosEmulation.h"


/*
 * Defines
 */

/** The size of the heap memory, which is statically allocated for the CAN interface. The
    value should be set as little as possible; if set too little then the application will
    abort with an assertion. This is safe due to the static, deterministic memory
    allocation concept: If no assertion fires in DEBUG compilation during development then
    it is for sure that the production code compilation won't see a lack of memory
    neither.
      @remark Consider to begin with a large value and then use the function \a
    mem_getNbrOfAllocatedChunks in DEBUG compilation in order to get the optimal setting
    for this define.
      @remark Compilation for win64 requires significantly more memory than for win32: All
    the pointers and int variables in the data structures have double the size. */
#define APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE 250000 /* Byte */

/** The length of the queue of the dispatcher that serves the 10ms APSW task with CAN
    related events. */
#define APT_DISPATCHER_10MS_QUEUE_LEN  CST_NO_CAN_FRAMES_RECEIVED

/** The length of the queue of the dispatcher that serves the 100ms APSW task with CAN
    related events. */
#define APT_DISPATCHER_100MS_QUEUE_LEN CST_NO_CAN_FRAMES_RECEIVED

/** The index of the dispatcher that serves the 10ms APSW task with CAN related events. */
#define APT_IDX_DISPATCHER_10MS     0u

/** The index of the dispatcher that serves the 100ms APSW task with CAN related events. */
#define APT_IDX_DISPATCHER_100MS    1u

/** The number of dispatchers in use. */
#define APT_NO_DISPATCHERS          2u


/*
 * Global type definitions
 */

/** The known kinds of event. The use of the pre-defined handle maps require a gapless,
    zero based sequence of enumeration values. Here for Rx event queues. */
typedef enum apt_kindOfEventsRx_t
{
    /*
     * External events should come first such that they get the zero based index space;
     * this facilitates the implementation of the required handle maps.
     */
     
    /** The kind-of-event for a CAN message reception event. Note, our simple map
        implementation requires that this is the last enumerated kind of event. */
    apt_evt_newRxMsg,

    /** The total number of different kinds of external events, i.e.,events, which come
        from a sender object and via a queue object to the dispatcher. */
    apt_evt_noKindsOfExternalEvents,
    
/// @todo Technically spoken, we don't need the internals in the enumeration. Does it make  sense with respect to readability/design of the code? Or better to kick them out here?
    /*
     * Purely internal events follow down here.
     */
     
    /** The kind-of-event for a CAN message sent event. In this application, we don't have
        external events related to Tx messages (like a transmission complete notification)
        and it is used only for initialization of a message's send timing. */
    apt_evt_initTxMsg = apt_evt_noKindsOfExternalEvents,

    /** The total number of different kinds of events. */
    apt_evt_noKindsOfEvents,
    
} apt_kindOfEventsRx_t;


/*
 * Global data declarations
 */

/** The total count of all ever received messages, including the lost one because of queue
    full events. */
extern _Atomic unsigned long long apt_noRxMessages;

/** The total number of sent messages, including the lost one because of send buffer full
    events. */
extern _Atomic unsigned long long apt_noTxMessages;

/** The total number of lost Rx messages because of queue full. */
extern _Atomic unsigned long long apt_noEvRxQueueFull;

/** The total number of Rx timeout events. */
extern _Atomic unsigned long long apt_noEvRxTimeout;

/** The total number of recognized E2E validation errors for Rx messages. */
extern _Atomic unsigned long long apt_noEvRxE2eFailure;

/** The total number of lost Tx messages because of send buffer full events. */
extern _Atomic unsigned long long apt_noEvTxSendBufFull;


/*
 * Global prototypes
 */

/** Demo code of a typical CAN receive callback implementation. Binds the platform CAN
    input to the universal CAN interface for further processing of the received messages. */
void apt_irqHandlerRxCan( unsigned int idxMessage
                        , const unsigned char *pMsgContent
                        , unsigned int DLC
                        );

#endif  /* APT_APPLICATIONTASK_INCLUDED */

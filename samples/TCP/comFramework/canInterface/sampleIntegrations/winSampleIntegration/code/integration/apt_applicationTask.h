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

#include "types.h"
#include "oss_operatingSystemSimulation.h"
#include "ede_eventDispatcherEngine.h"

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
    for this define. */
#define APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE  10000u /* Byte */

/** The index of the dispatcher system that owns the dispatcher, which serves the 10ms APSW
    task with CAN related events. */
#define APT_IDX_DISPATCHER_SYSTEM_10MS  0u

/** The index of the dispatcher system that owns the dispatcher, which serves the 100ms
    APSW task with CAN related events. */
#define APT_IDX_DISPATCHER_SYSTEM_100MS 1u

/** The number of dispatchers in use. */
#define APT_NO_DISPATCHER_SYSTEMS       2u

/** The kind-of-event for a bus-off. In this simple example, it is at the same time the
    event source index as internally used by the processing dispatcher engine (which needs
    to be ensured at initialization time by order of registration. */
#define APT_EV_BUS_OFF                  0u

/** The kind-of-event for an end of bus-off. In this simple example, it is at the same time
    the event source index as internally used by the processing dispatcher engine (which
    needs to be ensured at initialization time by order of registration. */
#define APT_EV_RECOVERED_FROM_BUS_OFF   1u

/** The kind-of-event for a CAN message reception event. Note, our simple map
    implementation requires that this is the last enumerated kind of event. */
#define APT_EV_RX_CAN_MSG               2u

/** The number of different kinds of events. */
#define APT_NO_KINDS_OF_EVENTS          3u

/** The number of external events in dispatcher 10ms. These are only the CAN Rx events. */
#define APT_NO_EXT_EV_DISPATCHER_10MS   (CST_NO_CAN_FRAMES_RECEIVED)

/** The number of internal events in dispatcher 10ms. These are only the CAN Tx events. */
#define APT_NO_INT_EV_DISPATCHER_10MS   (CST_NO_CAN_FRAMES_SENT)

/** The number of external events in dispatcher 100ms. These are the CAN Rx events plus the
    two bus-off events. */
#define APT_NO_EXT_EV_DISPATCHER_100MS  (CST_NO_CAN_FRAMES_RECEIVED + 2u)

/** The number of internal events in dispatcher 100ms. These are only the CAN Tx events. */
#define APT_NO_INT_EV_DISPATCHER_100MS  (CST_NO_CAN_FRAMES_SENT)


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** Simulated API with the APSW: The global bus-off state of the (only) CAN bus. The update
    of this global variable is implemented with the event notification mechanism of the CAN
    interface engine. */
extern bool apt_canBusOff;

/** The array of dispatcher systems processing CAN events in the 10 and 100 ms APSW tasks. */
extern ede_handleDispatcherSystem_t apt_hDispatcherSystemAry[APT_NO_DISPATCHER_SYSTEMS];


/*
 * Global prototypes
 */

/** Demo code of a typical CAN receive callback implementation. Binds the platform CAN
    input to the universal CAN interface for further processing of the received frames. */
void apt_irqHandlerRxCan( oss_handleCanFrame_t hFrame
                        , const unsigned char *pMsgContent
                        , unsigned int DLC
                        );

/** The handler of a hypothetic bus state change interrupt, which notifies bus-off events. */
void apt_irqHandlerBusOff(bool isOff);

/** The initialization task. */
void apt_taskInit();

/** Demo code of a typical application task, which runs the universal CAN interface and
    which consumes the received CAN information. */
void apt_task10ms();

/** Demo code of a typical application task, which runs the universal CAN interface and
    which consumes the received CAN information. */
void apt_task100ms();

/** The shutdown task of this simulation environment. */
void apt_taskShutdown();

#endif  /* APT_APPLICATIONTASK_INCLUDED */

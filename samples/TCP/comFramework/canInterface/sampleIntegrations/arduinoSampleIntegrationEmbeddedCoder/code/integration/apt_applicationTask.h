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
#define APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE  1000u /* Byte */

/** The index of the dispatcher that serves the APSW task with CAN frame related events. */
#define APT_IDX_DISPATCHER_FRAME_EVENTS 0u

/** The index of the dispatcher that serves the APSW task with CAN bus related events. */
#define APT_IDX_DISPATCHER_BUS_EVENTS   1u

/** The number of dispatchers in use. */
#define APT_NO_DISPATCHERS              2u

/** The kind-of-event for a bus-off. In this simple example, it is at the same time the
    event source index as internally used by the processing dispatcher engine (which needs
    to be ensured at initialization time by order of registration. */
#define APT_EV_BUS_OFF                  0u

/** The kind-of-event for an end of bus-off. In this simple example, it is at the same time
    the event source index as internally used by the processing dispatcher engine (which needs to
    be ensured at initialization time by order of registration. */
#define APT_EV_RECOVERED_FROM_BUS_OFF   1u

/** The kind-of-event for a CAN message reception event. Note, our simple map
    implementation requires that this is the last enumerated kind of event. */
#define APT_EV_RX_CAN_MSG               2u


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

/** The system with the dispatcher engines processing CAN events and bus events. */
extern ede_handleDispatcherSystem_t apt_hDispatcherSystem;

/** A counter of queue overrun events for bus events. The counter is saturated and won't
    wrap around. Reading tasks need to access it under interrupt lock. */
extern uint16_t apt_noLostBusStateEvents;

/** A counter of queue overrun events. This is the number of lost events. The counter is
    saturated and won't wrap around. Reading tasks need to access it under interrupt lock. */
extern uint16_t apt_noLostFrameEvents;


/*
 * Global prototypes
 */

/** The initialization task. */
void apt_taskInit();

/** Demo code of a typical application task, which runs the universal CAN interface and
    which consumes the received CAN information. */
void apt_task10ms();

/** Demo code of a typical application task, which runs the universal CAN interface and
    which consumes the received CAN information. */
void apt_task100ms();

#endif  /* APT_APPLICATIONTASK_INCLUDED */

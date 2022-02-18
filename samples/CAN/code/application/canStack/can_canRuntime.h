#ifndef CAN_CANRUNTIME_INCLUDED
#define CAN_CANRUNTIME_INCLUDED
/**
 * @file can_canRuntime.h
 * Definition of global interface of module can_canRuntime.c
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

#include "typ_types.h"
#include "cst_canStatistics.h"
#include "bsw_basicSoftware.h"
#include "ede_eventDispatcherEngine.h"


/*
 * Defines
 */

/** Map the CAN buses of the given board to the meaning they have in the application
    code. */
#define CAN_BUS_PT                  (BSW_CAN_BUS_0)
#define CAN_BUS_PWM                 (BSW_CAN_BUS_0)
#define CAN_BUS_1_STILL_UNUSED      (BSW_CAN_BUS_1)
#define CAN_BUS_2_STILL_UNUSED      (BSW_CAN_BUS_2)
#define CAN_BUS_3_STILL_UNUSED      (BSW_CAN_BUS_3)

/** The configuration of the supported transmission modes for CAN messages is highly
    dependent on the definition of attributes in the particular CAN database (*.dbc file).
    This requires some adaptations of CAN code generation templates and C source code. You
    need to specify the name of the enumeration values, which distinguish the transmission
    modes. The names in use depend in turn on the configuration of the CAN code generator
    (compare with attributes.stg).\n
      Here is how the transmission mode of ordinary, regular messages is named. */
#define CAN_ENUM_SEND_MODE_REGULAR cap_enumSendMode_0_cyclic
#define CAN_ENUM_SEND_MODE_EVENT cap_enumSendMode_1_event /// Send mode event triggered
#define CAN_ENUM_SEND_MODE_MIXED cap_enumSendMode_2_cyclicOrEvent /// Send mode event plus cyclic

/** The size of the heap memory, which is statically allocated for the CAN interface. The
    value should be set as little as possible; if set too little then the application will
    abort with an assertion. This is safe due to the static, deterministic memory
    allocation concept: If no assertion fires in DEBUG compilation during development then
    it is for sure that the production code compilation won't see a lack of memory
    neither.
      @remark Consider to begin with a large value and then use the function \a
    mem_getNbrOfAllocatedChunks in DEBUG compilation in order to get the optimal setting
    for this define. */
#define CAN_SIZE_OF_HEAP_FOR_CAN_INTERFACE  8192 /* Byte */

/** The index of the dispatcher that serves the 10ms APSW task with CAN related events. */
#define CAN_IDX_DISPATCHER_10MS             0

/** The length of the queue of the dispatcher that serves the 10ms APSW task with CAN
    related events. */
#define CAN_DISPATCHER_10MS_QUEUE_LEN       10u

/** This value extends the enumeration of CAN related events. It means a bus-off
    notification. */ 
#define CAN_EV_BUS_OFF                      (CDE_EV_FIRST_CUSTOM_EVENT+1)

/** This value extends the enumeration of CAN related events. It signals recovery from a
    bus-off error. */ 
#define CAN_EV_RECOVERED_FROM_BUS_OFF       (CDE_EV_FIRST_CUSTOM_EVENT+2)


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** The system, which owns the dispatcher engines processing the CAN events in the 10ms and
    in the 100ms APSW tasks. */
extern ede_handleDispatcherSystem_t can_hDispatcherSystem;

/** The total count of all ever received messages, including the lost one because of queue
    full events. */
extern volatile unsigned long can_noRxMsgs;

/** The total number of sent messages, including the lost one because of send buffer full
    events. */
extern volatile unsigned long can_noTxMsgs;

/** The total number of lost Rx messages because of queue full. */
extern volatile unsigned long can_noEvRxQueueFull;

/** The total number of Rx timeout events. */
extern volatile unsigned long can_noEvRxTimeout;

/** The total number of lost Tx messages because of send buffer full events. */
extern volatile unsigned long can_noEvTxSendBufFull;


/*
 * Global prototypes
 */

/* Initialization of the CAN stack. */
bool can_initCanStack(void);

#endif  /* CAN_CANRUNTIME_INCLUDED */

#ifndef CAN_CANRUNTIME_INCLUDED
#define CAN_CANRUNTIME_INCLUDED
/**
 * @file can_canRuntime.h
 * Definition of global interface of module can_canRuntime.c
 *
 * Copyright (C) 2015-2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "typ_types.h"
#include "cde_canStatistics.h"


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

/** The total count of all ever received frames, including the lost one because of queue
    full events. */
extern volatile unsigned long can_noRxFrames;

/** The total number of sent frames, including the lost one because of send buffer full
    events. */
extern volatile unsigned long can_noTxFrames;

/** The total number of lost Rx frames because of queue full. */
extern volatile unsigned long can_noEvRxQueueFull;

/** The total number of Rx timeout events. */
extern volatile unsigned long can_noEvRxTimeout;

/** The total number of lost Tx frames because of send buffer full events. */
extern volatile unsigned long can_noEvTxSendBufFull;


/*
 * Global prototypes
 */

/* Initialization of the CAN stack. */
bool can_initCanStack(void);

#endif  /* CAN_CANRUNTIME_INCLUDED */
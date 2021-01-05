#ifndef APT_APPLICATIONTASK_INCLUDED
#define APT_APPLICATIONTASK_INCLUDED
/**
 * @file apt_applicationTask.h
 * Definition of global interface of module apt_applicationTask.c
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

/*
 * Include files
 */

#include "types.h"


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
#define APP_SIZE_OF_HEAP_FOR_CAN_INTERFACE 10000 /* Byte */

/** The index of the dispatcher that serves the 10ms APSW task with CAN related events. */
#define APT_IDX_DISPATCHER_10MS 0

/** The index of the dispatcher that serves the 100ms APSW task with CAN related events. */
#define APT_IDX_DISPATCHER_100MS 1


/** This value extends the enumeration of CAN related events. It means a bus-off
    notification. */ 
#define APT_EV_BUS_OFF  (CDE_EV_FIRST_CUSTOM_EVENT+1)

/** This value extends the enumeration of CAN related events. It signalls recovery from a
    bus-off error. */ 
#define APT_EV_RECOVERED_FROM_BUS_OFF  (CDE_EV_FIRST_CUSTOM_EVENT+2)


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** Simulated API with the APSW: The global bus-off state of the (only) CAN bus. The update
    of this global variable is implemented with the event notification mechanism of the CAN
    interface engine. */
extern boolean_t apt_canBusOff;


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
void apt_irqHandlerBusOff(boolean_t isOff);

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

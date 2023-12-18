#ifndef OSS_OPERATINGSYSTEMSIMULATION_INCLUDED
#define OSS_OPERATINGSYSTEMSIMULATION_INCLUDED
/**
 * @file oss_operatingSystemSimulation.h
 * Definition of global interface of module oss_operatingSystemSimulation.c
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

/** The CAN bus handle is an enumeration, implemented by #define's. Here we have the one and
    only bus ID. */
#define OSS_CAN_BUS_PT  0

/** The definition of an invalid CAN frame ID. */
#define OSS_INVALID_CAN_FRAME_HANDLE    0xfffffffful

/*
 * Global type definitions
 */

/** The type of a CAN bus handle. The bus handle is a static enumeration, implemented by
    #define's. */
typedef unsigned short oss_handleCanBus_t;

/** The type of a CAN frame handle. The simulated platform uses a frame handle as a system
    wide unique identification of a CAN frame. */
typedef unsigned int oss_handleCanFrame_t;

/** The type of a (application) task function. */
typedef void (*oss_task_t)(void);

/** The type of a CAN reception interrupt on the (simulated) system. */
typedef void (*oss_irqHandlerCanRx_t)( oss_handleCanFrame_t hFrame
                                     , const unsigned char data[]
                                     , unsigned int noBytes
                                     );

/** The type of a CAN bus off interrupt on the (simulated) system. */
typedef void (*oss_irqHandlerCanBusOff_t)(bool isOff);

/** The kind of application task, which can be installed for execution. */
typedef enum { oss_taskType_init = 0
             , oss_taskType_regular1ms
             , oss_taskType_regular10ms
             , oss_taskType_regular100ms
             , oss_taskType_regular1s
             , oss_taskType_shutdown
             , oss_noTaskTypes
             } oss_taskType_t;


/*
 * Global data declarations
 */

/** The time unit of the simulated OS kernel in micro seconds. */
extern unsigned int oss_tiTick;

/** The simulation time in us. */
extern unsigned long long oss_tiSim;


/*
 * Global prototypes
 */

/** Register a CAN frame for reception. The simulated platform will only receive registered
    frames. */
oss_handleCanFrame_t oss_registerFrameForReception( oss_handleCanBus_t osHandleBus
                                                  , unsigned long canId
                                                  , bool isExtId
                                                  );

/** Register a CAN frame for sending. The simulated platform will only accept registered
    frames for transmission. */
oss_handleCanFrame_t oss_registerFrameForSending( oss_handleCanBus_t osHandleBus
                                                , unsigned long canId
                                                , bool isExtId
                                                );

/** Install the CAN receive interrupt handler. */
oss_irqHandlerCanRx_t oss_installIrqHandlerCanRx(oss_irqHandlerCanRx_t irqHandler);

/** Install the CAN bus error interrupt handler. */
oss_irqHandlerCanBusOff_t oss_installIrqHandlerCanBusOff(oss_irqHandlerCanBusOff_t irqHandler);

/** Install an application task function. */
oss_task_t oss_installTask(oss_taskType_t type, oss_task_t function);

/** Simulated operating system kernel. This call corresponds to the typical startOS of a
    real RTOS. The major difference is that it returns after a while. */
void oss_kernel(unsigned int tickInUs, unsigned long long tiSimEndInUs);

/** Simulated CAN bus management. The bus can be restarted after a bus-off notification. It
    can't however be guaranteed that this will succeed. */
void oss_restartCanBus(oss_handleCanBus_t osHandleBus);

/** The platform's simulated CAN send function. */
bool oss_sendCanFrame( oss_handleCanFrame_t osHandleFrame
                     , uint8_t *pData
                     , unsigned int DLC
                     );

#endif  /* OSS_OPERATINGSYSTEMSIMULATION_INCLUDED */

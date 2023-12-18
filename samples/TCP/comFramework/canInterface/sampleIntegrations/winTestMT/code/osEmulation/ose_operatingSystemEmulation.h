#ifndef OSE_OPERATINGSYSTEMSIMULATION_INCLUDED
#define OSE_OPERATINGSYSTEMSIMULATION_INCLUDED
/**
 * @file ose_operatingSystemEmulation.h
 * Definition of global interface of module ose_operatingSystemEmulation.c
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
#include "cap_canApi.h"
#include "ede_eventDispatcherEngine.h"
#include "rtos_rtosEmulation.h"


/*
 * Defines
 */

/** The CAN bus handle is an enumeration, implemented by #define's. Here we have the one and
    only bus ID. */
#define OSE_CAN_BUS_B1  0
#define OSE_CAN_BUS_B2  1
#define OSE_CAN_BUS_B3  2
#define OSE_CAN_BUS_B4  3
#define OSE_CAN_BUS_B5  4
#define OSE_CAN_BUS_B6  5
#define OSE_CAN_BUS_B7  6
#define OSE_CAN_BUS_B8  7
#define OSE_CAN_BUS_B9  8
#define OSE_CAN_BUS_B10 9 


/** The OS offers a fixed but configurable number of connection points for sending a CAN
    message. A connection point is a buffered input, which is available to just one context
    in the APSW. If the APSW wants to send messages from different competing contexts, e.g.
    from two or more tasks or from some tasks and some interrupts, then each context needs
    to use its own connection point. */
#define OSE_CAN_TX_NO_CONNECTION_POINTS     2u


/*
 * Global type definitions
 */

/** The decription of a received CAN frame. This is not an element we would expect in a
    real OS, since it describes how to simulate the timing and the received contents of the
    frame. A real OS might have a much simpler data structure for registering received CAN
    frames. Such a data structure would mainly state the bus and the CAN ID.\n
      Since it is anyway not a real existing element we use it at the same time as run-time
    element, to keep the state of the simulation. */
typedef struct ose_receivedCanFrame_t
{
    /** The CAN bus, which the reception event is simulated for. */
    unsigned int idxCanBus;

    /** The CAN ID. */
    unsigned long canId;
    
    /** Boolean flag, whether \a canId is an extended 29 Bit ID. */
    bool isExtId;
    
    /** The size of the frame contents in Byte. */
    unsigned int DLC;
    
    /** An external simulation function, which is called to fill the receive buffer with
        the binary frame contents. This function will be a random byte generator or
        frame-specific, auto-coded from the network database. */
    void (*fctGetFrameContents)(uint8_t frameContentAry[]);
    
    /** The transmission timing pattern to be applied to the frame. */
    cap_enumSendMode_t sendMode;

    /** The nominal cycle time in ms if the frame is not purely event triggered. */
    unsigned int tiCycle;
    
    /** The minimum distance of reception events if the frame is event triggered. */
    unsigned int tiMinDistance;
    
} ose_receivedCanFrame_t;



/** The decription of a sent CAN frame. This is not an element we would expect in a
    real OS, since it only describes how to do the E2E validation of these frames. */
typedef struct ose_sentCanFrame_t
{
    /** The CAN bus, which the send simulation should be made for. */
    unsigned int idxCanBus;

    /** The CAN ID. */
    unsigned long canId;
    
    /** Boolean flag, whether \a canId is an extended 29 Bit ID. */
    bool isExtId;
    
    /** An external simulation function, which is called to do the E2E validation of the
        frame. */
    boolean_t (*fctDoE2eValidation)(const uint8_t frameContentAry[]);
    
    /** The transmission timing pattern to be applied to the frame. */
    cap_enumSendMode_t sendMode;

    /** The nominal cycle time in ms if the frame is not purely event triggered. */
    unsigned int tiCycle;
    
    /** The minimum distance of send events if the frame is event triggered. */
    unsigned int tiMinDistance;
    
} ose_sentCanFrame_t;



/** The type of a CAN bus handle. The bus handle is a static enumeration, implemented by
    #define's. */
typedef unsigned short ose_handleCanBus_t;

/** The type of a (application) task function. */
typedef rtos_taskFctResult_t (*ose_task_t)(void);

/** The type of a CAN reception interrupt on the (simulated) system. */
typedef void (*ose_irqHandlerCanRx_t)( unsigned int idxFrame
                                     , const unsigned char data[]
                                     , unsigned int noBytes
                                     );

/** The type of a CAN bus off interrupt on the (simulated) system. */
typedef void (*ose_irqHandlerCanBusOff_t)(boolean_t isOff);

/** The kind of application task, which can be installed for execution. */
typedef enum { ose_taskType_init = 0
             , ose_taskType_regular1ms
             , ose_taskType_regular10ms
             , ose_taskType_regular100ms
             , ose_taskType_regular1s
             , ose_taskType_shutdown
             , ose_noTaskTypes
             } ose_taskType_t;


/*
 * Global data declarations
 */

/** The simulation time in ms. */
extern _Atomic volatile unsigned long ose_tiSim;

/** The data describing the received CAN frames. The data table is used to implement the
    simulation of the CAN input. The table is extern and auto-coded from the network
    database. */
extern const ose_receivedCanFrame_t ose_receivedCanFrameAry[];

/** The number of entries in the external data table \a ose_receivedCanFrameAry. The value
    has to be set by the provider of the table. */
extern const unsigned int ose_noReceivedCanFrames;

/** The data describing the sent CAN frames. The data table is used to implement the
    E2E validation of the sent frames. */
extern const ose_sentCanFrame_t ose_sentCanFrameAry[];

/** The number of entries in the external data table \a ose_sentCanFrameAry. The value
    has to be set by the provider of the table. */
extern const unsigned int ose_noSentCanFrames;


/*
 * Global prototypes
 */

/** Install the CAN receive interrupt handler. */
ose_irqHandlerCanRx_t ose_installIrqHandlerCanRx(ose_irqHandlerCanRx_t irqHandler);

/** Install the CAN bus error interrupt handler. */
ose_irqHandlerCanBusOff_t ose_installIrqHandlerCanBusOff(ose_irqHandlerCanBusOff_t irqHandler);

/** Install an application task function. */
ose_task_t ose_installTask(ose_taskType_t type, ose_task_t function);

/** Simulated operating system kernel. This call corresponds to the typical startOS of a
    real RTOS. The major difference is that it can return after a while. */
void ose_kernel(unsigned long tiSimEndInMs);

/** Simulated CAN bus management. The bus can be restarted after a bus-off notification. It
    can't however be guaranteed that this will succeed. */
void ose_restartCanBus(ose_handleCanBus_t osHandleBus);

/** The platform's simulated CAN send function. */
bool ose_sendCanMessage( unsigned int idxConnectionPoint
                       , unsigned int idxFrameOs
                       , uint8_t *pData
                       , unsigned int sizeOfData
                       );

#endif  /* OSE_OPERATINGSYSTEMSIMULATION_INCLUDED */

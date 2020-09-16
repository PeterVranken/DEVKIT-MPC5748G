#ifndef CDR_CANDRIVER_API_INCLUDED
#define CDR_CANDRIVER_API_INCLUDED
/**
 * @file cdr_canDriver.h
 * Definition of global interface of module cdr_canDriver.c
 *
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <stdint.h>
#include <stdbool.h>

#include "MPC5748G.h"
#include "cdr_canDriver.h"


/*
 * Defines
 */


/*
 * Global type definitions
 */

/** This is the enumeration of enabled CAN devices. The naming of the enumeration values is
    chosen similar to the naming of the devices in MPC5748G.h.\n
      The enumeration values form a zero based index of all devices that are enabled in the
    configuration file #CDR_CONFIG_HEADER_FILE_NAME. */
typedef enum cdr_canDevice_t
{
#if CDR_ENABLE_USE_OF_CAN_0 == 1
    cdr_canDev_CAN_0,
#endif
#if CDR_ENABLE_USE_OF_CAN_1 == 1
    cdr_canDev_CAN_1,
#endif
#if CDR_ENABLE_USE_OF_CAN_2 == 1
    cdr_canDev_CAN_2,
#endif
#if CDR_ENABLE_USE_OF_CAN_3 == 1
    cdr_canDev_CAN_3,
#endif
#if CDR_ENABLE_USE_OF_CAN_4 == 1
    cdr_canDev_CAN_4,
#endif
#if CDR_ENABLE_USE_OF_CAN_5 == 1
    cdr_canDev_CAN_5,
#endif
#if CDR_ENABLE_USE_OF_CAN_6 == 1
    cdr_canDev_CAN_6,
#endif
#if CDR_ENABLE_USE_OF_CAN_7 == 1
    cdr_canDev_CAN_7,
#endif
    cdr_canDev_noCANDevicesEnabled,
    
} cdr_canDevice_t;


/*
 * Global data declarations
 */

/** Global counter for Rx FIFO overflow events. Each count means a lost Rx message. */
extern unsigned int cdr_noRxFIFOOverflowEvents;

/** Global counter of successfully received messages since software startup.
      @remark The counter wrapps around when the implementation maximum is reached. */
extern unsigned int cdr_noRxMsgsFIFO;

/*
 * Global prototypes
 */



/*
 * Global inline functions
 */

/** Initialize the CAN driver after reset. */
void cdr_osInitCanDriver(void);

/** Test routine. Send a message on every invocation. */
void cdr_osTestSend_task10ms(cdr_canDevice_t canDevice);

#endif  /* CDR_CANDRIVER_API_INCLUDED */

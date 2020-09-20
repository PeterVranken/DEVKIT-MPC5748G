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
/// @todo Document the list of APIs intended for the client code of the driver

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>

#include "MPC5748G.h"
#include "cdr_canDriver.config.h"
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
    configuration file cdr_canDriver.config.inc. */
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


/** An enumeration of error code, which can be returned by the API functions. */
typedef enum cdr_errorAPI_t
{ cdr_errApi_noError,
  cdr_errApi_warningRxOverflow,
  cdr_errApi_rxMailboxEmpty,
  cdr_errApi_deviceHandleOutOfRange,
  cdr_errApi_fifoMailboxUsedForTx,
  cdr_errApi_fifoMailboxRequiresNotification,
  cdr_errApi_mailboxReconfigured,
  cdr_errApi_badCanId,
  cdr_errApi_notificationWithoutIRQ,
  cdr_errApi_idxMailboxOutOfRange,
  cdr_errApi_dlcOutOfRange,
  
} cdr_errorAPI_t;



/*
 * Global data declarations
 */



/*
 * Global prototypes
 */

/** Initialize the CAN driver after reset. */
void cdr_osInitCanDriver(void);

/** After driver initialization, associate all CAN messages for Rx or Tx with mailboxes. */
cdr_errorAPI_t cdr_osMakeMailboxReservation( unsigned int idxCanDevice
                                           , unsigned int hMB
                                           , bool isExtId
                                           , unsigned int canId
                                           , bool isReceived
                                           , unsigned int TxDLC
                                           , bool doNotify
                                           );

/* Rx polling API. Check if a message has been received and get it. */
cdr_errorAPI_t cdr_osReadMessage( unsigned int idxCanDevice
                                , unsigned int hMB
                                , unsigned int * const pDLC
                                , uint8_t payload[]
                                , unsigned int * const pTimeStamp
                                );
                                
/* Send a single Tx message from a reserved mailbox with pre-configured ID and DLC. */
bool cdr_osSendMessage( unsigned int idxCanDevice
                      , unsigned int hMB
                      , const uint8_t payload[]
                      );

/* Send a single Tx message from a reserved mailbox with variable ID and DLC. */
bool cdr_osSendMessageEx( unsigned int idxCanDevice
                        , unsigned int hMB
                        , bool isExtId
                        , unsigned int canId
                        , unsigned int DLC
                        , const uint8_t payload[]
                        );

/** Temporarily used test routine. Configure driver for test purpose. */
void cdr_osTestRxTx_init(cdr_canDevice_t canDevice);

/** Temporarily used test routine. Send a message on every invocation. */
void cdr_osTestRxTx_task10ms(cdr_canDevice_t canDevice);



/*
 * Global inline functions
 */

/**
 * Get the maximum number of CAN messages (i.e. with different CAN IDs) that can be
 * processed. Basically, this number depends on the hardware, in particular the number of
 * mailboxes in the CAN device. However, the result is also dependent on the chosen
 * (constant) driver configuration: The use of the FIFO can significantly enlarge the
 * number.
 *   @return
 * Get the number in the range 0..186. The count is the total number, including Rx and Tx
 * messages.
 *   @param pCanDevConfig
 * The result depends on the device configuration. It is passed in by reference.
 */
static inline unsigned int cdr_maxNoCanIds(cdr_canDevice_t idxCanDevice)
{
    assert(idxCanDevice < sizeOfAry(cdr_canDriverConfig));
    const cdr_canDeviceConfig_t * const pDeviceConfig = &cdr_canDriverConfig[idxCanDevice];
    
    return cdr_getNoFIFOFilterEntries(pDeviceConfig)
           + (pDeviceConfig->noMailboxes - cdr_getIdxOfFirstMailbox(pDeviceConfig));

} /* End of cdr_maxNoCanIds */





#endif  /* CDR_CANDRIVER_API_INCLUDED */

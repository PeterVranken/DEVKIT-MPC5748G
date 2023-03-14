#ifndef CDR_CANDRIVER_API_INCLUDED
#define CDR_CANDRIVER_API_INCLUDED
/**
 * @file cdr_canDriverAPI.h
 * Definition of global interface of the CAN driver. Client code of the driver should
 * normally not need definitions from other header files - with the big exception of the
 * definitions for the compile-time configuration of the driver.\n
 *   This header contains the data types and function prototypes to directly use. Client
 * code of the driver will solely include this header. Nonetheless, this doesn't mean that
 * this header file is self-contained. It's not the encapsulation of an obscured driver
 * implementation but includes other nested headers, which still need to be available for
 * compilation of the client code.\n
 *   The other relevant header file is cdr_canDriver.config.h. Client code won't directly
 * include it but you may need to open it for understanding the configuration of the driver
 * appropriately for your specific application. The driver configuration is a large, nested
 * constant data set and this file documents all required fields.\n
 *   The actual configuration is made in file cdr_canDriver.config.inc. This is a hybrid
 * from header and implementation file, that contains both, declaration and definition of
 * the configuration data object. The driver implementation offers a template for this
 * file, named cdr_canDriver.config.inc.template.\n
 *   The work flow is to make a copy of the template in the code repository of the aimed
 * application, using the original name cdr_canDriver.config.inc. Then open the file and do
 * all configuration according to the guiding documentation and based on the sample
 * configuration in the template. (And based on the documentation in file
 * cdr_canDriver.config.h.)\n
 *   Actually, you specify the CAN driver configuration as a large initializer expression
 * of the one and only huge constant configuration data object. This task is strongly
 * facilitated by source code comments on the different fields and by using C99's
 * designated initializer expressions.\n
 *   The principal element in configuration file cdr_canDriver.config.inc is the list of
 * #defines to enable one or more of the physically available CAN devices; see e.g.,
 * #CDR_ENABLE_USE_OF_CAN_0. (Most applications won't use all of them.) By means of
 * preprocessor switches, the driver configuration is produced only for the enabled set of
 * devices (and alike for some runtime data objects). Disabled CAN devices are not touched
 * at all by the driver and remain in reset state and nor do they consume ROM space for
 * configuration data.\n
 *   Your application won't directly use the configuration file cdr_canDriver.config.inc.
 * Don't include it, don't compile it. Indirectly, your application will read its header
 * file contents (#define's) through this header, cdr_canDriverAPI.h. Those parts of
 * cdr_canDriver.config.inc, which are actually C source code -- concretely, the definition
 * of the constant configuration data object --, will be compiled from the CAN driver's
 * main implementation file, namely cdr_canDriver.c, by way of including it.
 *   @remark
 * The CAN driver is compilable with the renamed but not altered template configuration
 * file. However, no CAN device will then be enabled and the compiler will issue several
 * warnings because of zero-sized arrays and data structures.
 *
 * Copyright (C) 2020-2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "rtos.h"
#include "cde_canDriver.config.MCUDerivative.h"
#include "cdr_canDriver.config.inc"
#include "cdr_canDriver.h"
#include "cdr_queuedSending.h"

/*
 * Defines
 */

/** Index of system call for making an association between a mailbox and a CAN ID. */
#define CDR_SYSCALL_MAKE_MB_RESERVATION 40

/** Index of system call for sending a CAN message. */
#define CDR_SYSCALL_SEND_MSG            41

/** Index of system call for reading a CAN message from a mailbox. */
#define CDR_SYSCALL_READ_MSG            42


/*
 * Global type definitions
 */

/** This is the enumeration of enabled CAN devices. The naming of the enumeration values is
    chosen similar to the naming of the devices in MPC5748G.h.\n
      The enumeration values form a zero based index of all devices that are enabled in the
    configuration file cdr_canDriver.config.inc.\n
      The enumeration values are intended for use as first argument, \a idxCanDevice, in
    the public API of the CAN driver. */
typedef enum cdr_enumCanDevice_t
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
    
} cdr_enumCanDevice_t;


/** An enumeration of error codes, which can be returned by the API functions. */
typedef enum cdr_errorAPI_t
{ cdr_errApi_noError,                   /** Operation succeeded. */
  cdr_errApi_warningRxOverflow,         /** Rx polling has skipped at least one message. */
  cdr_errApi_rxMailboxEmpty,            /** Rx polling fails, no new data available. */
  cdr_errApi_txMailboxBusy,             /** Can't send, Tx mailbox not flushed yet or is Rx. */
  cdr_errApi_handleOutOfRange,          /** API called with either bad CAN device
                                            enumeration value or invalid mailbox handle. */
  cdr_errApi_fifoMailboxUsedForTx,
  cdr_errApi_fifoMailboxRequiresNotification,
  cdr_errApi_mailboxReconfigured,       /** A MB reservation can't be changed once done. */
  cdr_errApi_badCanId,                  /** A CAN ID exceeds the 11 or 29 Bit. */
  cdr_errApi_notificationWithoutIRQ,    /** Notification demanded for MB but IRW is not
                                            enabled for the related MB group. */
  cdr_errApi_pollingOfMailboxWithIRQ,
  cdr_errApi_apiBufferIdxInvalid,       /** Configuration error: An API buffer has been
                                            specified for a Tx mailbox. Or a bad index has
                                            been specified for an Rx mailbox. */
  cdr_errApi_dlcOutOfRange,
  
} cdr_errorAPI_t;


/** An API buffer for Rx mailbox polling. The user accessible API to poll particular Rx
    messages for newly received data places its result in such a buffer. See
    cdr_readMessage(). */
typedef struct cdr_apiBufferRxPolling_t
{
    /* The number of received bytes. */
    uint8_t DLC;
    
    /* The time stamp of HW reception event. Unit is the CAN bit time, i.e., the reciprocal
       of the Baud rate. The time counts cyclically and the absolute value has no meaning. */
    uint16_t timeStamp;
    
    /* The received bytes, accessible in different word sizes. The alignment is such that
       efficient 32 or 64 Bit copy operations can be applied. */
    union
    {
        uint8_t  payload_u8[8];
        uint16_t payload_u16[4];
        uint32_t payload_u32[2];
        uint64_t payload_u64;
    };
} cdr_apiBufferRxPolling_t;


/** Used as argument for function cdr_getNoRxFifoEvents(): The total counts of occurances
    of different events can be queried. All events are related to the Rx FIFO reception
    process. */
typedef enum cdr_kindOfRxFifoEvent_t
{
    /** FIFO event: Warning because of a nearly full queue. There's a risk of loosing a
        message. */
    cdr_rxEv_warningNearlyFull,
    
    /** FIFO event: Lost message due to overfull queue. */
    cdr_rxEv_errorOverflow,
    
    /** FIFO event: Messages received via the Rx FIFO (as opposed to reception in normal
        mailbox). */
    cdr_rxEv_reception,
    
} cdr_kindOfRxFifoEvent_t;


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

/** Send a single Tx message from a reserved mailbox with pre-configured ID and DLC. */
cdr_errorAPI_t cdr_osSendMessage( unsigned int idxCanDevice
                                , unsigned int hMB
                                , const uint8_t payload[]
                                );

/** Send a single Tx message from a reserved mailbox with variable ID and DLC. */
cdr_errorAPI_t cdr_osSendMessageEx( unsigned int idxCanDevice
                                  , unsigned int hMB
                                  , bool isExtId
                                  , unsigned int canId
                                  , unsigned int DLC
                                  , const uint8_t payload[]
                                  );

/** Rx polling API. Check if a message has been received and get it. */
cdr_errorAPI_t cdr_osReadMessage( unsigned int idxCanDevice
                                , unsigned int hMB
                                , uint8_t * const pDLC
                                , uint8_t payload[]
                                , uint16_t * const pTimeStamp
                                );
                                
/** Get the API buffer for a particular Rx mailbox, which is used by polling. */
const cdr_apiBufferRxPolling_t *cdr_getRxPollingAPIBuffer( unsigned int idxCanDevice
                                                         , unsigned int hMB
                                                         );

#ifdef MCU_MPC5748G
/** Get the current bus off state for the given CAN device. */
bool cdr_getIsBusOff(unsigned int idxCanDevice);
#endif

/** Get the number of recorded bus off events for the given CAN device. */
unsigned int cdr_getNoBusOffEvents(unsigned int idxCanDevice);

/** Get the number of Rx FIFO events recorded for the given CAN device. */
unsigned int cdr_getNoRxFifoEvents( unsigned int idxCanDevice
                                  , cdr_kindOfRxFifoEvent_t kindOfEvent
                                  );

/** Get the number of recorded transmission errors for the given CAN device. */
unsigned int cdr_getNoErrorEvents(unsigned int idxCanDevice);

#if defined(MCU_MPC5775B) || defined(MCU_MPC5775E)
/** Get the number of recorded RAM ECC errors for the given CAN device. */
unsigned int cdr_getNoEccErrorEvents(unsigned int idxCanDevice);
#endif

/** Get the last recently reported CAN transmission error. */
uint16_t cdr_getLastTransmissionError(unsigned int idxCanDevice);


/*
 * Global inline functions
 */

/**
 * Get the maximum number of CAN messages (i.e., with different CAN IDs) that can be
 * processed. Basically, this number depends on the hardware, in particular the number of
 * mailboxes in the CAN device. However, the result is also dependent on the chosen
 * (constant) driver configuration: The use of the FIFO can significantly enlarge the
 * number.\n
 *   The result of this function denotes the upper boundary for mailbox handles in the
 * public interface of the CAN driver, e.g., cdr_osMakeMailboxReservation().
 *   @return
 * Get the number in the range 0..186. The count is the total number, including Rx and Tx
 * messages.
 *   @param pCanDevConfig
 * The result depends on the device configuration. It is passed in by reference.
 */
static inline unsigned int cdr_maxNoCanIds(cdr_enumCanDevice_t idxCanDevice)
{
    assert(idxCanDevice < sizeOfAry(cdr_canDriverConfig));
    const cdr_canDeviceConfig_t * const pDeviceConfig = &cdr_canDriverConfig[idxCanDevice];
    
    return pDeviceConfig->noMailboxes + cdr_getAdditionalCapacityDueToFIFO(pDeviceConfig);

} /* End of cdr_maxNoCanIds */




/**
 * Application dependent initialization of CAN communication: By calling this function, the
 * application requests one particular CAN mailbox in the hardware for a particular
 * message, for either reception or transmission.\n
 *   Note, this is just a brief function description. Many more details can be found in the
 * description of the supervisor variant of the API, cdr_osMakeMailboxReservation().
 *   @return
 * The function returns \a cdr_errApi_noError in case of success. In all other cases it
 * has not effect.\n
 *   All possible errors are static configuration errors in the client code. There's no
 * need to have a dynamic error check at run-time.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.
 *   @param hMB
 * The driver has a fixed structure of mailboxes. Some aspects of this structure, e.g., the
 * number of mailboxes depend on the configuration. All mailboxes can be used for Rx.
 * Depending on the driver configuration, all or only a subset of them can be used for
 * Tx. All required details on available mailboxes and their characteristics can be found
 * in the description of the other API cdr_osMakeMailboxReservation().\n
 *   Note, each CAN device has its own, individual space of handle values.
 *   @param isExtId
 * Standard and extended CAN IDs partly share the same space of numbers. Hence, we need the
 * additional Boolean information, which of the two the ID \a canId belongs to.
 *   @param canId
 * The standard or extended ID of the CAN message, which the mailbox reservation is made
 * for.
 *   @param isReceived
 * The Boolean information, whether the mailbox is prepared for reception (\a true) of
 * transmission (\a false).
 *   @param TxDLC
 * The number of bytes of a Tx message in the range 0..8.
 *   @param doNotify
 * The Boolean choice whether or not the completion of the mailbox activity will trigger an
 * interrupt. (The notification callback is element of the driver's compile-time
 * configuration.)
 */
static inline cdr_errorAPI_t cdr_makeMailboxReservation( unsigned int idxCanDevice
                                                       , unsigned int hMB
                                                       , bool isExtId
                                                       , unsigned int canId
                                                       , bool isReceived
                                                       , unsigned int TxDLC
                                                       , bool doNotify
                                                       )
{
    return (cdr_errorAPI_t)rtos_systemCall( CDR_SYSCALL_MAKE_MB_RESERVATION
                                          , idxCanDevice
                                          , hMB
                                          , isExtId
                                          , canId
                                          , isReceived
                                          , TxDLC
                                          , doNotify
                                          );
} /* End of cdr_makeMailboxReservation */



/** 
 * User code send API for Tx messages. User tasks can send messages but not reconfigure
 * them; it can't alter the DLC or the CAN ID to send. The only thing it is allowed to do
 * is resending a message from a pre-configured mailbox with different payloads and at
 * arbitrary points in time. The function call will succeed only, if:\n
 *   - The mailbox is configured for Tx with particular CAN ID and particular DLC
 *     (typically done by operating system startup code)\n
 *   - The user process, the caller belongs to, needs to have the privileges to access the
 *     mailbox (CAN driver compile-time configuration)\n
 *   @return
 * \a cdr_errApi_noError, if function succeeded, or \a cdr_errApi_txMailboxBusy, if the
 * buffer in the hardware is still occupied by the preceeding message, which is not
 * serialized on the CAN bus yet.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices. An out of range situation raises an exception.
 *   @param hMB
 * The message to send is identified by the handle of the mailbox it is associated with. A
 * message can be sent only if it had been associated with a mailbox in the hardware,
 * i.e., a successful call of cdr_osMakeMailboxReservation() or cdr_makeMailboxReservation()
 * is prerequisite of using this function. The handle to use here is the same as used when
 * having done the related call of cdr_(os)MakeMailboxReservation(). An out of range
 * situation raises an exception.
 *   @param payload
 * The up to eight payload bytes. The first DLC bytes are sent, where DLC is the data
 * length code, which had been defined at mailbox reservation time (see
 * cdr_osMakeMailboxReservation()). User code is not enabled to ever change the
 * configuration of a mailbox, it can't alter the DLC or the CAN ID to send.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from 
 * OS code will lead to undefined behavior.
 *   @remark
 * This function is reentrant with respect to different addressed mailboxes. It can be
 * called from different cores. The behavior is undefined if called coincidentally from
 * different contexts but for the same mailbox. 
 */
static inline cdr_errorAPI_t cdr_sendMessage( unsigned int idxCanDevice
                                            , unsigned int hMB
                                            , const uint8_t payload[8]
                                            )
{
    return (cdr_errorAPI_t)rtos_systemCall(CDR_SYSCALL_SEND_MSG, idxCanDevice, hMB, payload);

} /* End of cdr_sendMessage */



/** 
 * Use code polling API for Rx messages. User tasks can check mailboxes for newly received
 * input. The function call will succeed only, if:\n
 *   - The mailbox is configured for Rx (typically done by operating system startup code)\n
 *   - The mailbox is configured for polling (typically done by operating system startup
 *     code)\n
 *   - The user process, the caller belongs to, needs to have the privileges to access the
 *     mailbox (CAN driver compile-time configuration)\n
 *   Note, the function doesn't directly return the received data. In order to ensure
 * memory integrity under all circumstances, the caller needs the fetch the data from the
 * API buffer, which is dedicated to the mailbox. See cdr_getRxPollingAPIBuffer() for
 * details.
 *   @return
 * If the function returns either \a cdr_errApi_noError or \a cdr_errApi_warningRxOverflow
 * then a new message had been arrived and the mailbox contents are returned to the
 * caller.\n
 *   \a cdr_errApi_noError should be the normal case, while \a cdr_errApi_warningRxOverflow
 * indicates that the call of the function came too late to read all incoming messages; at
 * least one preceeding message had been lost and overwritten by it successor.\n
 *   If no new message had been received since the previous call of this function for the
 * same mailbox then the function returns \a cdr_errApi_rxMailboxEmpty.\n
 *   \a cdr_errApi_rxMailboxEmpty is returned, too, if one tries to read from a mailbox,
 * which had been configured for Tx.\n
 *   The API buffer associated with the addressed mailbox is not altered if the return code
 * is other than \a cdr_errApi_noError or \a cdr_errApi_warningRxOverflow.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices. An out of range situation raises an exception.
 *   @param hMB
 * The message to check is identified by the handle of the mailbox it is associated with. A
 * message can be received only if it had been associated with a mailbox in the hardware,
 * i.e., a successful call of cdr_osMakeMailboxReservation() or cdr_makeMailboxReservation()
 * is prerequisite of using this function. The handle to use here is the same as used when
 * having done the related call of cdr_(os)MakeMailboxReservation(). An out of range
 * situation raises an exception.
 *   @remark
 * This function must be called from the user task context only. Any attempt to use it from 
 * OS code will lead to undefined behavior.
 *   @remark
 * This function is reentrant with respect to different addressed mailboxes. It can be
 * called from different cores. The behavior is undefined if called coincidentally from
 * different contexts but for the same mailbox.\n
 *   These considerations include fetching the data from the API buffer asiciated with the
 * addressed mailbox. The API buffer is static memory, which is updated by this function.
 * Competing contexts using this function for the same mailbox will surely mess up the API
 * buffer contents.\n 
 */
static inline cdr_errorAPI_t cdr_readMessage(unsigned int idxCanDevice, unsigned int hMB)
{
    return (cdr_errorAPI_t)rtos_systemCall(CDR_SYSCALL_READ_MSG, idxCanDevice, hMB);

} /* End of cdr_readMessage */


/**
 * User code send API for Tx messages via the extended driver service "queued sending".
 * User tasks can send messages, which have not been registered with a dedicated mailbox
 * before, instead, an internal mailbox is used for this service. This mailbox is
 * associated with a software queue. The user API will either directly transmit the message
 * - if the mailbox is currently idle - or it'll queue the message for later
 * transmission.\n
 *   The queue is flushed to the CAN bus in order of queuing, not considering the CAN
 * message priorities, i.e., not looking at the CAN ID of the queued messages.\n
 *   @return
 * Get \a cdr_errApi_noError if the message could be submitted or \a
 * cdr_errApi_txMailboxBusy if the SW queue is currently full. A bad CAN device index
 * \a idxCanDevice, in particular the specification of a device, which the queued
 * sending service is not enabled for, will lead to \a cdr_errApi_handleOutOfRange.
 *   @param idxCanDevice
 * The CAN device/bus, which the message should be transmitted on. It is chosen by zero
 * based index in the list of all enabled CAN devices. Range is 0..(\a
 * cdr_canDev_noCANDevicesEnabled-1).\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices. An out of range situation is caught by assertion.
 *   @param isExtId
 * Standard and extended CAN IDs partly share the same space of numbers. Hence, we need the
 * additional Boolean information, which of the two the ID \a canId belongs to.
 *   @param canId
 * The standard or extended ID of the CAN message to send. See \a isExtId, too.
 *   @param sizeOfPayload
 * The number of bytes in \a payload[]. This number of bytes is sent. Range is 0..8. An
 * exception would be raised otherwise.
 *   @param payload
 * The \a DLC message content bytes, which are sent.
 *   @remark
 * This function can be called at any time from a user task context on the core, which is
 * configured to run the CAN driver and which services the mailbox group IRQs of the
 * mailbox that is configured for service "queued sending". Any attempt to use it from
 * another context and in particular from OS code will lead to undefined behavior.
 */
static inline enum cdr_errorAPI_t cdr_sendMessageQueued( unsigned int idxCanDevice
                                                       , bool isExtId
                                                       , unsigned int canId
                                                       , unsigned int sizeOfPayload
                                                       , const uint8_t payload[]
                                                       )
{
    return (enum cdr_errorAPI_t)rtos_systemCall( CDR_SYSCALL_SEND_MESSAGE_QUEUED
                                               , idxCanDevice
                                               , isExtId
                                               , canId
                                               , sizeOfPayload
                                               , payload
                                               );
} /* End of cdr_sendMessageQueued */

#endif  /* CDR_CANDRIVER_API_INCLUDED */

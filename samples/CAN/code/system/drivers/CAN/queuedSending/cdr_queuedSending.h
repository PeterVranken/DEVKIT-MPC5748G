#ifndef CDR_QUEUEDSENDING_INCLUDED
#define CDR_QUEUEDSENDING_INCLUDED
/**
 * @file cdr_queuedSending.h
 * Definition of global interface of module cdr_queuedSending.c
 *
 * Copyright (C) 2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/*
 * Defines
 */

/** The driver offers a special service, which can be enabled on demand: A particular
    mailbox can be configured for queued sending. The user API for this MB doesn't require
    the initial registration of a particular CAN message for later transmission but allows
    addressing at run-time to any enabled CAN bus, any CAN ID and any DLC.\n
      This macro enables or disables the service and configures the size of the queue at
    the same time. If zero then the service is disabled. Otherwise it is the queue's
    capacity, i.e., the  maximum number of queueable messages.\n
      Caution: Only powers of two in the range 1..256 are allowed as capacity.\n
      The queued sending service is configured individually per CAN device. Here for CAN
    device CAN_0. */
#define CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0  0u

/** The number of queued messages for CAN device 1. 0 means service is off. */
#define CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1  0u

/** The number of queued messages for CAN device 2. 0 means service is off. */
#define CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2  0u

/** The number of queued messages for CAN device 3. 0 means service is off. */
#define CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3  0u

/** The number of queued messages for CAN device 4. 0 means service is off. */
#define CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4  0u

/** The number of queued messages for CAN device 5. 0 means service is off. */
#define CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5  0u

/** The number of queued messages for CAN device 6. 0 means service is off. */
#define CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6  0u

/** The number of queued messages for CAN device 7. 0 means service is off. */
#define CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7  0u

/** Index of system call for sending an unregistered, arbitrary CAN message via a queue. */
#define CDR_SYSCALL_SEND_MESSAGE_QUEUED         44u

/** Global indication, whether at least one CAN channel is configured to support the
    extended CAN driver service "queued sending". */
#define CDR_IS_ENABLED_QUEUED_SENDING   ((CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0) > 0       \
                                         ||  (CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1) > 0   \
                                         ||  (CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2) > 0   \
                                         ||  (CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3) > 0   \
                                         ||  (CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4) > 0   \
                                         ||  (CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5) > 0   \
                                         ||  (CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6) > 0   \
                                         ||  (CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7) > 0   \
                                        )

/** If queued sending is configured then one of the mailboxes of the CAN device is reserved
    for this purpose. It needs to be configured as Tx and its access privileges control,
    which user processes can access the service "queued sending" on the given CAN device.\n
      Note, for sake of simplicity, all CAN devices, which enable the service use the same
    mailbox.\n
      Most typical, and in order to retain a simple contiguous handle space for the user
    code, one will preferably use the first or last physically available mailbox for this
    purpose (and inhibit it for service "make reservation"). Caution, the first mailbox
    can't be used if the use of the Rx FIFO is configured.\n
      This macro #CANIF_hMB_MAILBOX_QUEUED_TX needs to be set to the user visible handle of
    mailbox, while the other macro #CANIF_idxMB_MAILBOX_QUEUED_TX needs to be set
    consistently to the zero based physical index of the mailbox in the HW array of
    those. The two values differ if the use of the Rx FIFO is configured.\n
      The settings don't matter if the service is not enabled on any CAN device.\n
      Caution, because of the dependency on the configuration of the Rx FIFO, in particular
    field \a CTRL2_RFFN, it is not possible to provide here a reasonable default value.
    Each application of the service needs to double-check this setting. */
#define CANIF_hMB_MAILBOX_QUEUED_TX     ((CANIF_idxMB_MAILBOX_QUEUED_TX)+48u)

/** See #CANIF_hMB_MAILBOX_QUEUED_TX. */
#define CANIF_idxMB_MAILBOX_QUEUED_TX   ((CDR_NO_HW_MAILBOXES_PER_CAN_DEVICE)-1u)


/*
 * Global type definitions
 */

enum cdr_errorAPI_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialization of the queued sending service. */
bool cdr_osInitQueuedSending(void);

/** Send a message with potential queueing. */
enum cdr_errorAPI_t cdr_osSendMessageQueued( unsigned int idxCanDevice
                                           , bool isExtId
                                           , unsigned int canId
                                           , unsigned int DLC
                                           , const uint8_t payload[]
                                           );

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0 > 0
/** ISR of CAN device 0 for send acknowldge of queued QM Tx messages. */
void cdr_osCbOnCANTx_CAN_0_queuedSending( unsigned int hMB
                                        , bool isExtId
                                        , unsigned int canId
                                        , unsigned int DLC
                                        , bool isAborted
                                        , unsigned int timeStamp
                                        );
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1 > 0
/** ISR of CAN device 1 for send acknowldge of queued QM Tx messages. */
void cdr_osCbOnCANTx_CAN_1_queuedSending( unsigned int hMB
                                        , bool isExtId
                                        , unsigned int canId
                                        , unsigned int DLC
                                        , bool isAborted
                                        , unsigned int timeStamp
                                        );
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2 > 0
/** ISR of CAN device 2 for send acknowldge of queued QM Tx messages. */
void cdr_osCbOnCANTx_CAN_2_queuedSending( unsigned int hMB
                                        , bool isExtId
                                        , unsigned int canId
                                        , unsigned int DLC
                                        , bool isAborted
                                        , unsigned int timeStamp
                                        );
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3 > 0
/** ISR of CAN device 3 for send acknowldge of queued QM Tx messages. */
void cdr_osCbOnCANTx_CAN_3_queuedSending( unsigned int hMB
                                        , bool isExtId
                                        , unsigned int canId
                                        , unsigned int DLC
                                        , bool isAborted
                                        , unsigned int timeStamp
                                        );
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4 > 0
/** ISR of CAN device 4 for send acknowldge of queued QM Tx messages. */
void cdr_osCbOnCANTx_CAN_4_queuedSending( unsigned int hMB
                                        , bool isExtId
                                        , unsigned int canId
                                        , unsigned int DLC
                                        , bool isAborted
                                        , unsigned int timeStamp
                                        );
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5 > 0
/** ISR of CAN device 5 for send acknowldge of queued QM Tx messages. */
void cdr_osCbOnCANTx_CAN_5_queuedSending( unsigned int hMB
                                        , bool isExtId
                                        , unsigned int canId
                                        , unsigned int DLC
                                        , bool isAborted
                                        , unsigned int timeStamp
                                        );
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6 > 0
/** ISR of CAN device 6 for send acknowldge of queued QM Tx messages. */
void cdr_osCbOnCANTx_CAN_6_queuedSending( unsigned int hMB
                                        , bool isExtId
                                        , unsigned int canId
                                        , unsigned int DLC
                                        , bool isAborted
                                        , unsigned int timeStamp
                                        );
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7 > 0
/** ISR of CAN device 7 for send acknowldge of queued QM Tx messages. */
void cdr_osCbOnCANTx_CAN_7_queuedSending( unsigned int hMB
                                        , bool isExtId
                                        , unsigned int canId
                                        , unsigned int DLC
                                        , bool isAborted
                                        , unsigned int timeStamp
                                        );
#endif

/*
 * Global inline functions
 */

#if 0
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
#endif



#endif  /* CDR_QUEUEDSENDING_INCLUDED */

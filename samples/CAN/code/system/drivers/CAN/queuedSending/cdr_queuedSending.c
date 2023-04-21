/**
 * @file cdr_queuedSending.c
 * Extended service of the CAN driver: A particular mailbox can be used for queued sending,
 * i.e., a queue sits between user API and CAN driver API cdr_osSendMessageEx(). The user
 * code can submit messges for sending as fast as it desires or requires and the queued
 * messages are transmitted one after another via the particular mailbox and as fast as bus
 * arbitration allows to.\n
 *   The user API of this service differs from the normal CAN API in that it doesn't
 * require the registration of particular CAN messages before they may be sent. This
 * service can be used just like that with varying CAN buses, varying arbitrary CAN IDs and
 * with varying DLCs.\n
 *   Use cases for this service are either CAN based protocols, which necessarily need a
 * queued transmission in order not loose any message and the extension of the set of
 * transmittable CAN IDs: The normal CAN interface registers CAN IDs for later sending but
 * the number of registerable Tx messages is limited. (The actual limit depends on an
 * application's configuration of the CAN driver.)\n
 *   The use of a single Tx mailbox and a simple FIFO queue for this purpose implies that
 * CAN messages transmitted via this service are not prioritized among each other. They are
 * transmitted on the CAN bus in strict order of calling the user API. Of course, the
 * particular chosen mailbox is still prioritized against all other mailboxes. In turn,
 * this implies that the throughput of this service depends on the CAN IDs of the
 * transmitted messages. Transmitting a message of low priority can stall the transmission
 * all other later queued messages for a significant amount of time.\n
 *   The service is not self-contained and it doesn't work out of the box. If an
 * application of the CAN driver wants to make use of it then it needs to:\n
 *   - enable the service for one or more buses. See #CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0,
 *     #CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1, etc.\n
 *   - reserve a particular mailbox for the service. For simplicity, all enabled buses will
 *     usually use the same mailbox, but this is not a must.\n
 *   - strictly avoid calling the CAN driver's mailbox registration for the chosen mailbox;
 *     the MB is registered for the queued sending service by its initialization function\n
 *   - strictly avoid any access to the chosen MB by user processes; the access rights need
 *     to be configured accordingly, i.e., field userAccessMailboxAry[idxMB].minPIDToAccess
 *     needs to be zero. And also the privileges checks in the system calls need to consider
 *     this.\n
 *   - configure the ISR cdr_osCbOnCANTx_CAN_n_queuedSending(), which is
 *     implemented in this module, as CAN Tx ISR for the group, which the chosen mailbox
 *     belongs to. See field \a .osCallbackOnTx in cdr_canDriverConfig, for the buses the
 *     service is enabled for.\n
 *   - consider that the configured ISR serves an entire group of mailboxes. If the chosen
 *     mailbox is not the only one in its groups, which requires a Tx acknowledge IRQ, then
 *     a new ISR needs to be implemented and configured, which branches into this service'
 *     ISR cdr_osCbOnCANTx_CAN_n_queuedSending() only after it has checked that the IRQ was
 *     triggered by the chosen mailbox.\n
 *   - include the system call definitions, file cdr_queuedSending_defSysCalls.h, from file
 *     rtos_config_defSysCalls.h
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
/* Module interface
 *   cdr_osCbOnCANTx_CAN_0_queuedSending
 *   cdr_osCbOnCANTx_CAN_1_queuedSending
 *   cdr_osCbOnCANTx_CAN_2_queuedSending
 *   cdr_osCbOnCANTx_CAN_3_queuedSending
 *   cdr_osCbOnCANTx_CAN_4_queuedSending
 *   cdr_osCbOnCANTx_CAN_5_queuedSending
 *   cdr_osCbOnCANTx_CAN_6_queuedSending
 *   cdr_osCbOnCANTx_CAN_7_queuedSending
 *   cdr_scSmplHdlr_sendMessageQueued
 *   cdr_osInitQueuedSending
 *   cdr_osSendMessageQueued
 * Local functions
 *   osSendMessageQueued
 *   osCbOnCANTx_queuedSending
 */

/*
 * Include files
 */

#include "cdr_queuedSending.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "cdr_canDriverAPI.h"
#include "cdr_queuedSending_defSysCalls.h"

/*
 * Defines
 */


/*
 * Local type definitions
 */

/** The queue for a single CAN bus.\n
      All elements of the object are subject to race-conditions. We have competing
    read-modify-write accesses from the user task, which sends messages and from the CAN
    acknowledge IRQ. A simple global interrupt lock is used by the user task as
    synchronization mechanism, therefore any cross-core operation is excluded by principal.
    Since this holds for all elements of the queue, we don't mention access conditions for
    the distinct fields.\n
      Note, the data storage area of the queue is not contained. We want to have individual
    queue sizes for the buses. It wouldn't make sense to merge them into an iteratable
    array with a row accessed by reference: We anyway have distinct ISRs for all CAN buses
    and can therefore directly pick the objects to use by name. */
typedef struct msgQueue_t
{
    /** The number of submitted, pending CAN messages. One of these is in the CAN HW, the
        others are currently in the queue. */
    uint8_t noSubmittedMsgs;

    /** The write index for storing the next submitted message. */
    uint8_t idxWr;

    /** The read index for fetching the next message for transmission by the underlaying HW. */
    uint8_t idxRd;

    /** The capacity of the queue in number of messages. */
    uint8_t sizeOfQueue;

} msgQueue_t;


/** The queued data element. We use a most efficient fixed size object as the CAN driver
    anyway doesn't support CAN FD and most messages have the maximum size of 8 Byte.
    Moreover, we tolerate the loss of three gap bytes per message for sake of direct,
    well-aligned access to the queue memory. Optimally packing the data would require
    additional data copy operations. This is a trade-off, which can be easily changed in
    case of memory shortage. */
typedef struct queuedMsg_t
{
    /** The CAN ID: The number and the Boolean distinction between standard 11 and extended
        29 Bit IDs. */
    union canId_t
    {
        /** A struct provides the normally used access to the fields. */
        struct
        {
            /** The CAN ID.\n
                  Note, this field is intentionally not modelled as 29 Bit integer in order
                to avoid undefined values for unused bit: This supports efficient binary
                comparison of CAN IDs. */
            uint32_t id:31;

            /** The Boolean distinction, whether we have an 11 or a 29 Bit CAN ID. */
            uint32_t isExtId:1;
        };

        /** An alternative 32 Bit integer access supports efficient CAN ID comparisons (equal
            or not). */
        uint32_t uniqueCanId;

    } canId;

    /** The length of the message payload in Byte. */
    uint8_t sizeOfPayload;

    /** The payload bytes. */
    uint8_t payload[8];

} queuedMsg_t;



/*
 * Local prototypes
 */


/*
 * Data definitions
 */

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0 > 0
/** The queue object for CAN device 0. */
static msgQueue_t SBSS_OS(_can0MsgQueue);

/** The queue data area for CAN device 0. */
static queuedMsg_t DATA_OS(_can0MsgAry)[CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0];
#endif

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1 > 0
/** The queue object for CAN device 1. */
static msgQueue_t SBSS_OS(_can1MsgQueue);

/** The queue data area for CAN device 1. */
static queuedMsg_t DATA_OS(_can1MsgAry)[CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1];
#endif

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2 > 0
/** The queue object for CAN device 2. */
static msgQueue_t SBSS_OS(_can2MsgQueue);

/** The queue data area for CAN device 2. */
static queuedMsg_t DATA_OS(_can2MsgAry)[CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2];
#endif

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3 > 0
/** The queue object for CAN device 3. */
static msgQueue_t SBSS_OS(_can3MsgQueue);

/** The queue data area for CAN device 3. */
static queuedMsg_t DATA_OS(_can3MsgAry)[CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3];
#endif

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4 > 0
/** The queue object for CAN device 4. */
static msgQueue_t SBSS_OS(_can4MsgQueue);

/** The queue data area for CAN device 4. */
static queuedMsg_t DATA_OS(_can4MsgAry)[CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4];
#endif

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5 > 0
/** The queue object for CAN device 5. */
static msgQueue_t SBSS_OS(_can5MsgQueue);

/** The queue data area for CAN device 5. */
static queuedMsg_t DATA_OS(_can5MsgAry)[CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5];
#endif

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6 > 0
/** The queue object for CAN device 6. */
static msgQueue_t SBSS_OS(_can6MsgQueue);

/** The queue data area for CAN device 6. */
static queuedMsg_t DATA_OS(_can6MsgAry)[CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6];
#endif

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7 > 0
/** The queue object for CAN device 7. */
static msgQueue_t SBSS_OS(_can7MsgQueue);

/** The queue data area for CAN device 7. */
static queuedMsg_t DATA_OS(_can7MsgAry)[CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7];
#endif


/* Queued sending must not be enabled for a CAN device, which is disabled. */
_Static_assert
    ( (CDR_ENABLE_USE_OF_CAN_0 == 1  ||  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0 == 0)
      && (CDR_ENABLE_USE_OF_CAN_1 == 1  ||  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1 == 0)
      && (CDR_ENABLE_USE_OF_CAN_2 == 1  ||  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2 == 0)
      && (CDR_ENABLE_USE_OF_CAN_3 == 1  ||  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3 == 0)
      && (CDR_ENABLE_USE_OF_CAN_4 == 1  ||  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4 == 0)
      && (CDR_ENABLE_USE_OF_CAN_5 == 1  ||  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5 == 0)
      && (CDR_ENABLE_USE_OF_CAN_6 == 1  ||  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6 == 0)
      && (CDR_ENABLE_USE_OF_CAN_7 == 1  ||  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7 == 0)
    , "Queued sending must not be enabled for a disabled CAN device"
    );

/* The supported MCU derivatives have differing numbers of CAN devices. Check correct
   configuration. */
#if !defined(MCU_MPC5748G)
_Static_assert( CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4 == 0u
                &&  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5 == 0u
                &&  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6 == 0u
                &&  CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7 == 0u
              , "CAN devices 4..7 must not be used on the given MCU derivative"
              );
#endif

/* The queue uses efficient index calculation, which is restricted to queue capacities,
   which are a power of two. */
#define IS_PWR_OF_TWO(n) (((n) & ((n) - 1u)) == 0u  &&  (unsigned)(n) <= 256u)
_Static_assert( IS_PWR_OF_TWO(CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0)
                &&  IS_PWR_OF_TWO(CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1)
                &&  IS_PWR_OF_TWO(CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2)
                &&  IS_PWR_OF_TWO(CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3)
                &&  IS_PWR_OF_TWO(CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4)
                &&  IS_PWR_OF_TWO(CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5)
                &&  IS_PWR_OF_TWO(CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6)
                &&  IS_PWR_OF_TWO(CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7)
              , "The queue size needs to be either zero (off) or a power of two in the"
                " range 1..256"
              );
#undef IS_PWR_OF_TWO



/*
 * Function implementation
 */

/**
 * Main API for queued sending: Submit a message for transmission.\n
 *   The message is put into the underlaying HW if the associated mailbox is currently idle
 * or it is put into the SW queue for later transmission otherwise.
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
 *   @param DLC
 * The number of bytes to send in the range 0..8. An out of range situation is caught by
 * assertion.
 *   @param payload
 * The \a DLC message content bytes, which are sent.
 *   @remark
 * The function may be called at any time from any OS task context on the core, which
 * services the interrupts of the chosen CAN device. This function must not be used from an
 * ISR context, which has a priority higher than the CAN IRQ of the chosen device and for
 * the configured mailbox.
 *   @remark
 * This function needs to be called solely, while all interrupt processing is disabled.
 */
static cdr_errorAPI_t osSendMessageQueued( unsigned int idxCanDevice
                                         , bool isExtId
                                         , unsigned int canId
                                         , unsigned int DLC
                                         , const uint8_t payload[]
                                         )
{
    /* Note, the queue implementation uses the most simple way of handling race conditions
       with the data consumer (IRQ lock), which is the CAN IRQ of the given mailbox.
       This restrits the use of this API to the core, which services the IRQ. The IRQ
       doesn't lock interrupt processing, which further restricts the use of this API
       to contexts, which don't have a higher priority than the IRQ. */

    static const struct
    {
        msgQueue_t *pCanMsgQueue;
        queuedMsg_t *canMsgAry;

    } pQueueAry_[cdr_canDev_noCANDevicesEnabled] SECTION(.rodata.pQueueAry_) =
        {
#if CDR_ENABLE_USE_OF_CAN_0 == 1  
# if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0 > 0
            [cdr_canDev_CAN_0] = {.pCanMsgQueue = &_can0MsgQueue, .canMsgAry = _can0MsgAry},
# else
            [cdr_canDev_CAN_0] = {.pCanMsgQueue = NULL, .canMsgAry = NULL},
# endif
#endif
#if CDR_ENABLE_USE_OF_CAN_1 == 1  
# if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1 > 0
            [cdr_canDev_CAN_1] = {.pCanMsgQueue = &_can1MsgQueue, .canMsgAry = _can1MsgAry},
# else
            [cdr_canDev_CAN_1] = {.pCanMsgQueue = NULL, .canMsgAry = NULL},
# endif
#endif
#if CDR_ENABLE_USE_OF_CAN_2 == 1  
# if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2 > 0
            [cdr_canDev_CAN_2] = {.pCanMsgQueue = &_can2MsgQueue, .canMsgAry = _can2MsgAry},
# else
            [cdr_canDev_CAN_2] = {.pCanMsgQueue = NULL, .canMsgAry = NULL},
# endif
#endif
#if CDR_ENABLE_USE_OF_CAN_3 == 1  
# if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3 > 0
            [cdr_canDev_CAN_3] = {.pCanMsgQueue = &_can3MsgQueue, .canMsgAry = _can3MsgAry},
# else
            [cdr_canDev_CAN_3] = {.pCanMsgQueue = NULL, .canMsgAry = NULL},
# endif
#endif
#if CDR_ENABLE_USE_OF_CAN_4 == 1  
# if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4 > 0
            [cdr_canDev_CAN_4] = {.pCanMsgQueue = &_can4MsgQueue, .canMsgAry = _can4MsgAry},
# else
            [cdr_canDev_CAN_4] = {.pCanMsgQueue = NULL, .canMsgAry = NULL},
# endif
#endif
#if CDR_ENABLE_USE_OF_CAN_5 == 1  
# if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5 > 0
            [cdr_canDev_CAN_5] = {.pCanMsgQueue = &_can5MsgQueue, .canMsgAry = _can5MsgAry},
# else
            [cdr_canDev_CAN_5] = {.pCanMsgQueue = NULL, .canMsgAry = NULL},
# endif
#endif
#if CDR_ENABLE_USE_OF_CAN_6 == 1  
# if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6 > 0
            [cdr_canDev_CAN_6] = {.pCanMsgQueue = &_can6MsgQueue, .canMsgAry = _can6MsgAry},
# else
            [cdr_canDev_CAN_6] = {.pCanMsgQueue = NULL, .canMsgAry = NULL},
# endif
#endif
#if CDR_ENABLE_USE_OF_CAN_7 == 1  
# if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7 > 0
            [cdr_canDev_CAN_7] = {.pCanMsgQueue = &_can7MsgQueue, .canMsgAry = _can7MsgAry},
# else
            [cdr_canDev_CAN_7] = {.pCanMsgQueue = NULL, .canMsgAry = NULL},
# endif
#endif
        };

    if(idxCanDevice >= sizeOfAry(pQueueAry_))
        return cdr_errApi_handleOutOfRange;

    msgQueue_t * const pCanMsgQueue = pQueueAry_[idxCanDevice].pCanMsgQueue;
    if(pCanMsgQueue == NULL)
        return cdr_errApi_handleOutOfRange;
    
    /* If the queue is still empty: Immediately advance the message to the HW layer for
       transmission on the bus. */
    if(pCanMsgQueue->noSubmittedMsgs == 0u)
    {
        cdr_errorAPI_t errCode = cdr_osSendMessageEx( idxCanDevice
                                                    , CANIF_hMB_MAILBOX_QUEUED_TX
                                                    , isExtId
                                                    , canId
                                                    , DLC
                                                    , payload
                                                    );
        if(errCode == cdr_errApi_noError)
        {
            /* Update the balance of pending messages. */
            ++ pCanMsgQueue->noSubmittedMsgs;
        }
        else
        {
            /* Send errors must not happen at all. After checking the balance we expect
               the mailbox to be not busy and all other errors were anyway static
               compile-time errors. */
            assert(false);
            return cdr_errApi_txMailboxBusy;
        }
    }
    else
    {
        const unsigned int sizeOfQueue = pCanMsgQueue->sizeOfQueue;
        if(pCanMsgQueue->noSubmittedMsgs <= sizeOfQueue)
        {
            /* The HW mailbox is busy transmitting an earlier message and we have to queue
               the new one. */
            assert(pCanMsgQueue->idxWr < sizeOfQueue);
            queuedMsg_t * const pCanMsg = &pQueueAry_[idxCanDevice]
                                           .canMsgAry[pCanMsgQueue->idxWr];
            pCanMsg->canId = (union canId_t){.isExtId = isExtId, .id = canId,};
            pCanMsg->sizeOfPayload = DLC;
            assert(DLC <= sizeof(pCanMsg->payload));
            memcpy(&pCanMsg->payload[0], payload, DLC);

            /* Cyclic increment of write index can be done by masking as the array size is a
               power-of-two. */
            pCanMsgQueue->idxWr = (pCanMsgQueue->idxWr+1u) & (sizeOfQueue-1u);

            /* Update the balance of pending messages. */
            ++ pCanMsgQueue->noSubmittedMsgs;
        }
        else
        {
            /* The HW mailbox is busy transmitting and the queue is full. */
            return cdr_errApi_txMailboxBusy;
        }
    }

    return cdr_errApi_noError;

} /* osSendMessageQueued */


#if CDR_IS_ENABLED_QUEUED_SENDING
/**
 * The common code of the device specific CAN send acknowledge interrupts for the QM Tx
 * messages, which had been sent using the queued sending service.
 *   @param pCanDevice
 * The CAN device by reference, which has sent and acknowledged the message.
 *   @param pCanMsgQueue
 * The queue object for the affected CAN device.
 *   @param canMsgAry
 * The queue data area for the affected CAN device.
 *   @param maxIndex
 * The number of elements minus one of array \a canMsgAry.
 *   @remark
 * The callback is executed in supervisor mode and in the context of matching
 * mailbox-group ISR of the sending CAN device. It depends on the CAN driver
 * configuration if several invokations of this function can pre-empt one another and
 * what to do to ensure data coherency. Only in the simplest configuration case, if all
 * devices use the same priority for their mailbox-group IRQ and if the same core is
 * configured to serve the IRQs then no such preemption will occur.
 *   @remark
 * The function is reentrant only with respect to different CAN devices. Reentrance
 * by an ISR from the same CAN device would have unpredictable behavior.\n
 *   Differing IRQ priorities for the mailbox-group IRQ of different CAN devices is
 * supported.\n
 *   Different cores serving different CAN devices would be supported by this function
 * but is impossible due to the implementation of other functions in this compilation unit.
 */
static void osCbOnCANTx_queuedSending( CAN_Type * const pCanDevice
                                     , msgQueue_t * const pCanMsgQueue
                                     , const queuedMsg_t canMsgAry[]
                                     , unsigned int maxIndex
                                     )
{
    /* Note, the queue implementation uses the most simple way of handling race conditions
       with the data provider: IRQ lock. Access to the message submission API is intended
       for tasks only, so we don't do anything here; here we are in an IRQ context, which
       cannot be preempted by any task. */

    /* If there are still some messages left in the queue: Advance the next one to the HW
       layer for transmission on the bus. */
    if(pCanMsgQueue->noSubmittedMsgs > 1u)
    {
        const cdr_idMailbox_t idMB = { .pDevice = pCanDevice
                                     , .pDeviceConfig = NULL /* doesn't care */
                                     , .idxMailbox = CANIF_idxMB_MAILBOX_QUEUED_TX
                                     };
        assert(pCanMsgQueue->idxRd <= maxIndex);
        const queuedMsg_t * const pMsg = &canMsgAry[pCanMsgQueue->idxRd];
        cdr_errorAPI_t errCode = cdr_osSendMessageEx_idMB
                                            ( &idMB
                                            , pMsg->canId.isExtId
                                            , pMsg->canId.id
                                            , pMsg->sizeOfPayload
                                            , &pMsg->payload[0]
                                            );
        if(errCode == cdr_errApi_noError)
        {
            /* Cyclic increment of read index can be done by masking as the array size is a
               power-of-two. */
            pCanMsgQueue->idxRd = (pCanMsgQueue->idxRd+1u) & maxIndex;

            /* Update the balance of pending messages. */
            -- pCanMsgQueue->noSubmittedMsgs;
            assert(pCanMsgQueue->noSubmittedMsgs <= maxIndex+1u);
        }
        else
        {
            /* Send errors must not happen at all. After receiving an acknowledge we expect
               the mailbox to be not busy and all other errors were anyway static
               compile-time errors. */
            assert(false);
        }
    }
    else
    {
        /* All queued message have been transmitted. We are done for now. */
        assert(pCanMsgQueue->noSubmittedMsgs == 1u);
        pCanMsgQueue->noSubmittedMsgs = 0u;
    }
} /* osCbOnCANTx_queuedSending */
#endif



/**
 * The device specific CAN send acknowledge interrupts for the QM Tx messages, which had
 * been sent using the queued sending service.
 *   @param hMB
 * The handle of the notifying mailbox as agreed on at message registration time is returned
 * to support a simple association of the Rx event with the data content.
 *   @param isExtId
 * Standard and extended CAN IDs partly share the same space of numbers. Hence, we need the
 * additional Boolean information, which of the two the ID \a canId belongs to.
 *   @param canId
 * The standard or extended ID of the received CAN message.
 *   @param DLC
 * Data length code, the number of transmitted content bytes.
 *   @param isAborted
 * A Tx mailbox can be re-filled by the client code before the predesessor had been
 * serialized on the bus. This is called an abort. An abort still yields an acknowledging
 * IRQ and this Boolean flag is set to \a true.
 *   @param timeStamp
 * The time of completing the transmission of the message is recorded by hardware and the
 * value is forwarded to the callback. The absolute value has not meaning, time-base is a
 * free running 16 Bit counter. The frequency of the timer is the CAN bit rate; having a
 * bus with 500 kBd the unit of the timer would be 2µs. The timer wraps around at 2^16-1.
 *   @remark
 * The callback is executed in supervisor mode and in the context of the matching
 * mailbox-group ISR of the sending CAN device.
 */
#define CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING(idxDev)                                          \
void cdr_osCbOnCANTx_CAN_##idxDev##_queuedSending( unsigned int hMB ATTRIB_DBG_ONLY         \
                                                 , bool isExtId ATTRIB_UNUSED               \
                                                 , unsigned int canId ATTRIB_UNUSED         \
                                                 , unsigned int DLC ATTRIB_UNUSED           \
                                                 , bool isAborted ATTRIB_UNUSED             \
                                                 , unsigned int timeStamp ATTRIB_UNUSED     \
                                                 )                                          \
{                                                                                           \
    /* Queued Tx messages are processed with one particular mailbox. All other          */  \
    /* mailboxes belonging to the same ISR group don't use Tx notifications. So we know */  \
    /* a priori who/where we are and can apply an assertion for double-checking.        */  \
    /*   Note, modifications of the CAN driver configuration and particularly the       */  \
    /* mailbox partitioning can invalidate this condition!                              */  \
    assert(hMB == CANIF_hMB_MAILBOX_QUEUED_TX);                                             \
    osCbOnCANTx_queuedSending( CAN_##idxDev                                                 \
                             , &_can##idxDev##MsgQueue                                      \
                             , &_can##idxDev##MsgAry[0]                                     \
                             , (CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_##idxDev)-1u           \
                             );                                                             \
} /* osCbOnCANTx_CAN_n_queuedSending */



#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0 > 0
    CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING(/* idxDev */ 0)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1 > 0
    CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING(/* idxDev */ 1)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2 > 0
    CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING(/* idxDev */ 2)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3 > 0
    CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING(/* idxDev */ 3)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4 > 0
    CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING(/* idxDev */ 4)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5 > 0
    CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING(/* idxDev */ 5)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6 > 0
    CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING(/* idxDev */ 6)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7 > 0
    CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING(/* idxDev */ 7)
#endif

#undef CDR_OS_CB_ON_CAN_TX_QUEUED_SENDING


/** 
 * System call handler for sending an unregistered, arbitrary CAN message via service
 * "queued sending".\n
 *   The message is put into the underlaying HW if the single, associated mailbox is
 * currently idle or it is put into the software queue for later transmission
 * otherwise. See #CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0,
 * #CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1, etc. for the queue sizes, which are
 * configured for the different CAN devices.
 *   @return
 * Get \a cdr_errApi_noError if the message could be submitted or \a
 * cdr_errApi_txMailboxBusy if the SW queue is currently full. A bad CAN device index
 * \a idxCanDevice, in particular the specification of a device, which the queued
 * sending service is not enabled for, will lead to \a cdr_errApi_handleOutOfRange.
 *   @param PID
 * Privileges management: The process ID of the calling task. All user processes are
 * allowed to use this service.
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
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
uint32_t cdr_scSmplHdlr_sendMessageQueued( uint32_t PID
                                         , unsigned int idxCanDevice
                                         , bool isExtId
                                         , unsigned int canId
                                         , unsigned int sizeOfPayload
                                         , const uint8_t payload[]
                                         )
{
    /* As for any system call, all preconditions need to be tested to the extend that
       failures of the underlying OS code can be excluded. In particular, no arguments
       may pass the check, which would make an assertion fire in the OS code. This would
       in case halt the SW in DEBUG compilation and lead to undefined, potentially unsafe
       behavior in the PRODUCTION code. */

    if(sizeOfPayload <= 8u  &&  rtos_checkUserCodeReadPtr(payload, sizeOfPayload))
    {
        /// @todo The next condition implements the privileges for "queued sending". In
        /// this sample, we keep it simple and allow the service user process P1 with all
        /// CAN devices it is enabled on. However, it would be easily possible to do this
        /// depending on the CAN device or differently for different user processes, etc.
        if(PID == 1u)
        {
            /* After checking the potentially bad user input we may delegate to the "normal"
               function implementation.
                 Please note, we didn't do a range check of idxCanDevice. This is caught
               inside the OS API and would be reported by normal function result code. */
            return (uint32_t)osSendMessageQueued( idxCanDevice
                                                , isExtId
                                                , canId
                                                , /* DLC */ sizeOfPayload
                                                , payload
                                                );
        }
    }
    
    /* If we get here then we couldn't call the OS function to submit the message for
       transmission. We have a bad system call argument, raise exception. This function
       doesn't return. */
    rtos_osSystemCallBadArgument();

} /* cdr_scSmplHdlr_sendMessageQueued */





/**
 * Initialization of the queued sending service. Needs to be called after initialization of
 * CAN interface.
 *   @return
 * If the function returns \a false (error) then the service could not be initialized and
 * the system should not start up. Normally, it'll return \a true: CAN configuration is
 * found consistent and all needed CAN resource could be allocated and initializes.
 */
bool cdr_osInitQueuedSending(void)
{
    bool success = true;

    /* Most relevant configuration checks. Note, the checks are necessary but not
       sufficient. */
#if CDR_IS_ENABLED_QUEUED_SENDING
    cdr_idMailbox_t idMB;
#endif
    #define CHECK_CONFIG(idxCanDevice)                                                      \
    if(cdr_mapMailboxHandleToId(&idMB, idxCanDevice, CANIF_hMB_MAILBOX_QUEUED_TX)           \
       &&  idMB.idxMailbox == CANIF_idxMB_MAILBOX_QUEUED_TX                                 \
      )                                                                                     \
    {                                                                                       \
        const cdr_mailboxAccessConfig_t configMB =                                          \
                idMB.pDeviceConfig->userAccessMailboxAry[CANIF_idxMB_MAILBOX_QUEUED_TX];    \
        if(!(configMB.minPIDToAccess == 0                                                   \
             &&  configMB.idxAPIBuffer == 0                                                 \
             &&  !configMB.useAsRxMailbox                                                   \
            )                                                                               \
          )                                                                                 \
        {                                                                                   \
            success = false;                                                                \
        }                                                                                   \
    }                                                                                       \
    else                                                                                    \
        success = false;

    /* The queues are initialized. */
    #define INIT_QUEUE(idxHwDev)                                                            \
        _can##idxHwDev##MsgQueue =                                                          \
            (msgQueue_t){ .noSubmittedMsgs = 0u                                             \
                        , .idxWr = 0u                                                       \
                        , .idxRd = 0u                                                       \
                        , .sizeOfQueue = CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_##idxHwDev    \
                        };

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0 > 0
    CHECK_CONFIG(/* idxCanDevice */ cdr_canDev_CAN_0)
    INIT_QUEUE(/* idxHwDev */ 0)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1 > 0
    CHECK_CONFIG(/* idxCanDevice */ cdr_canDev_CAN_1)
    INIT_QUEUE(/* idxHwDev */ 1)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2 > 0
    CHECK_CONFIG(/* idxCanDevice */ cdr_canDev_CAN_2)
    INIT_QUEUE(/* idxHwDev */ 2)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3 > 0
    CHECK_CONFIG(/* idxCanDevice */ cdr_canDev_CAN_3)
    INIT_QUEUE(/* idxHwDev */ 3)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4 > 0
    CHECK_CONFIG(/* idxCanDevice */ cdr_canDev_CAN_4)
    INIT_QUEUE(/* idxHwDev */ 4)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5 > 0
    CHECK_CONFIG(/* idxCanDevice */ cdr_canDev_CAN_5)
    INIT_QUEUE(/* idxHwDev */ 5)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6 > 0
    CHECK_CONFIG(/* idxCanDevice */ cdr_canDev_CAN_6)
    INIT_QUEUE(/* idxHwDev */ 6)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7 > 0
    CHECK_CONFIG(/* idxCanDevice */ cdr_canDev_CAN_7)
    INIT_QUEUE(/* idxHwDev */ 7)
#endif

    #undef CHECK_CONFIG
    #undef INIT_QUEUE

    /* Register a CAN mailbox for the queued Tx messages. Note, this registration is
       closely connected to the configuration of the CAN driver and the CAN API;
       particularly to the chosen partitioning of the mailboxes. The code here must not be
       modified without deep inside into the CAN configuration. */
    #define MAKE_MAILBOX_RESERVATION(idxCanBus)                                             \
        if(cdr_osMakeMailboxReservation( idxCanBus                                          \
                                       , CANIF_hMB_MAILBOX_QUEUED_TX                        \
                                       , /* isExtId */ false /* doesn't care */             \
                                       , /* canId */ 0 /* doesn't care */                   \
                                       , /* isReceived */ false                             \
                                       , /* TxDLC */ 0u /* doesn't care */                  \
                                       , /* doNotify */ true                                \
                                       )                                                    \
           != cdr_errApi_noError                                                            \
          )                                                                                 \
        {                                                                                   \
            success = false;                                                                \
        }

#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_0 > 0
    MAKE_MAILBOX_RESERVATION(cdr_canDev_CAN_0)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_1 > 0
    MAKE_MAILBOX_RESERVATION(cdr_canDev_CAN_1)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_2 > 0
    MAKE_MAILBOX_RESERVATION(cdr_canDev_CAN_2)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_3 > 0
    MAKE_MAILBOX_RESERVATION(cdr_canDev_CAN_3)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_4 > 0
    MAKE_MAILBOX_RESERVATION(cdr_canDev_CAN_4)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_5 > 0
    MAKE_MAILBOX_RESERVATION(cdr_canDev_CAN_5)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_6 > 0
    MAKE_MAILBOX_RESERVATION(cdr_canDev_CAN_6)
#endif
#if CDR_QUEUED_SENDING_SIZE_OF_QUEUE_CAN_7 > 0
    MAKE_MAILBOX_RESERVATION(cdr_canDev_CAN_7)
#endif

    #undef MAKE_MAILBOX_RESERVATION

    return success;

} /* cdr_osInitQueuedSending */


/**
 * Main API for queued sending: Submit a message for transmission.\n
 *   The message is put into the underlaying HW if the associated mailbox is currently idle
 * or it is put into the SW queue for later transmission otherwise.
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
 *   @param DLC
 * The number of bytes to send in the range 0..8. An out of range situation is caught by
 * assertion.
 *   @param payload
 * The \a DLC message content bytes, which are sent.
 *   @remark
 * The function may be called at any time from any OS task context on the core, which
 * services the interrupts of the chosen CAN device. This function must not be used from an
 * ISR context, which has a priority higher than the CAN IRQ of the chosen device and for
 * the configured mailbox.
 */
cdr_errorAPI_t cdr_osSendMessageQueued( unsigned int idxCanDevice
                                      , bool isExtId
                                      , unsigned int canId
                                      , unsigned int DLC
                                      , const uint8_t payload[]
                                      )
{
    const uint32_t state = rtos_osEnterCriticalSection();
    const cdr_errorAPI_t errCode = osSendMessageQueued( idxCanDevice
                                                      , isExtId
                                                      , canId
                                                      , DLC
                                                      , payload
                                                      );
    rtos_osLeaveCriticalSection(state);

    return errCode;

} /* cdr_osSendMessageQueued */

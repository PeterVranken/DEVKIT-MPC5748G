/**
 * @file cdr_userCodeAPI.c
 * This file implements the CAN driver API intended for application code running in user
 * mode. Most of the time, this means a duplication of the existing normal OS API as system
 * calls. Additionally, some buffer management is required in order to not break the safety
 * concept (memory protection).
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
/* Module interface
 *   cdr_getRxPollingAPIBuffer
 *   cdr_scSmplHdlr_readMessage
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "rtos.h"
#include "cdr_canDriver.h"
#include "cdr_canDriver.config.inc"
#include "cdr_canDriverAPI.h"
#include "cdr_canDriver_defSysCalls.h"


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
/** The API buffers for Rx mailbox polling. The system call implementation of the polling
    function, cdr_scSmplHdlr_readMessage, can safely access this memory and the user code
    can still read the results from here. */
static cdr_apiBufferRxPolling_t _apiBufferRxPolling[CDR_NO_RX_USER_CODE_POLLING_MAILBOXES] = 
    { 
        [1 ... CDR_NO_RX_USER_CODE_POLLING_MAILBOXES-1] =
        {
          .DLC = 0,
          .payload_u64 = 0llu,
        },
    };


/*
 * Function implementation
 */


/**
 * System call handler for making an assocation of a particluar mailbox with a specific CAN
 * ID.\n
 *   Application dependent initialization of CAN communication: The driver will react only
 * on CAN message, it has agreed on with the application SW. This API is intended for
 * making such an agreement. By calling this function, the application requests one
 * particular CAN mailbox in the hardware for a particular message, for either reception or
 * transmission.
 *   @return
 * Mailbox reservation can fail. Mainly, because the number of outermost processable
 * messages is limited. The total number of all messages is limited by hardware and the
 * driver has no implementation of virtualization; if the Rx FIFO is enabled then numbers
 * of Rx and Tx messages even have different, indivdual limits.\n
 *   The function returns \a cdr_errApi_noError in case of success. In all other cases it
 * has not effect.\n
 *   All possible errors are static configuration errors in the client code. There's no
 * need to have a dynamic error check at run-time. The appropriate way to handle the return
 * code of this function is an assertion in DEBUG compilation. If it proves once that the
 * function returns \a cdr_errApi_noError then there's no risk to ever see another return
 * code in PRODUCTION compilation.
 *   @param PID
 * Privileges management: The process ID of the calling task. This ID is compared to the
 * driver configuration. There, it is configured, which particular process may use this
 * function. An exception is raised if another process invokes this function.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices.\n
 *   @param hMB
 * The driver has a fixed structure of mailboxes. (A structure, which is modifiable by
 * configuration only to little extend: FIFO on/off, size of FIFO filter table).
 * Consequently, all mailboxes have a fixed index and we use this index as a handle to
 * refer to a particular mailbox. Usually, a driver will deal out a handle. Our driver
 * doesn't do but lets the client code choose the appropriate handle. The reason is that
 * the mailboxes have differing properties, which are known to the client code. By letting
 * it chosse the handle, hence the mailbox, it can decide, which mailbox suits best.
 * Relevant differences between mailboxes are:\n
 *   - The first n mailboxes belong to the Rx FIFO. They can't by used for transmission. n
 * depends on the configuration of the FIFO. The remaining, normal mailboxes are available
 * to Rx or Tx\n
 *   - The normal mailboxes are organized in groups of 4, 16 or 32. Each of these groups
 * can have a different interrupts, depending on the driver configuration. Different
 * interrupts means different priority, processed on different cores and/or using
 * different notification callbacks.\n
 *   The range of hMB is 0..N, where N depends on the chosen configuration.\n
 *   Details on how n and N relate to the made configuration can be found below.\n
 *   An out of range handle or using a handle, which had already been used in an earlier
 * call of this function, is considered an error.\n
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
 * The number of bytes of a Tx message in the range 0..8.\n
 *   The value doesn't care for Rx messages and it doesn't even care for Tx messages if
 * the send API cdr_osSendMessageEx() is exclusively used. The simple send API
 * cdr_osSendMessage(), however, will send the messages with this TxDLC. The range is 0..8.
 *   @param doNotify
 * The Boolean choice whether or not the completion of the mailbox activity will trigger an
 * interrupt. If set to \a true then an Rx mailbox will raise an interrupt if the reception
 * buffer has just been filled with a message from the bus and an Tx mailbox will raise the
 * interrupt when it has entirely serialized a message on the bus. By callback invokation,
 * the interrupt handler notifies the client code about the event and provides it the
 * required information (e.g. message payload for Rx mailboxes).\n
 *   The choice of the notification callback is made in the driver configuration. All
 * mailboxes of one group share the same callback.\n
 *   It is considered an error if a notification is requested for a mailbox that belongs to
 * a group, which is no interrupt configured for.
 *   @remark
 * The number n of FIFO mailboxes is 8*(CTRL2_RFFN+1) if the FIFO is enabled
 * (isFIFOEnabled=true) and 0 otherwise. CTRL2_RFFN and isFIFOEnabled are compile-time
 * constants in the driver configuration. Handle values 0..(n-1) make a CAN message
 * received via FIFO.\n
 *   The number m of normal mailboxes is (noMailboxes-8-2*CTRL2_RFFN) if the FIFO is
 * enabled (isFIFOEnabled=true) and noMailboxes otherwise. noMailboxes, CTRL2_RFFN and
 * isFIFOEnabled are compile-time constants in the driver configuration. Handle values
 * n..(n+m-1) place a CAN message in a normal mailbox. The massage can be either Rx or
 * Tx.\n
 *   The total number N=n+m of processable CAN messages is noMailboxes+6*CTRL2_RFFN if the
 * FIFO is enabled (isFIFOEnabled=true) and noMailboxes otherwise. noMailboxes, CTRL2_RFFN
 * and isFIFOEnabled are compile-time constants in the driver configuration. This number is
 * available as cdr_maxNoCanIds(), too.
 *   @remark
 * The hardware provides plenty of mailboxes. Therefore, we decided not to make the
 * acceptance mask available to the client code. This mask would allow sharing a mailbox
 * between a set of CAN messages with similar CAN IDs. This mechanism has some deficiencies
 * in terms of ease of use and wouldn't be available to all mailboxes in a homogenous way.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
uint32_t cdr_scFullHdlr_makeMailboxReservation( uint32_t PID
                                              , unsigned int idxCanDevice
                                              , unsigned int hMB
                                              , bool isExtId
                                              , unsigned int canId
                                              , bool isReceived
                                              , unsigned int TxDLC
                                              , bool doNotify
                                              )
{
    if(idxCanDevice < sizeOfAry(cdr_canDriverConfig)
       &&  PID == (uint32_t)cdr_canDriverConfig[idxCanDevice].pidMakeMailboxReservation
      )
    {
        return (uint32_t)cdr_osMakeMailboxReservation( idxCanDevice
                                                     , hMB
                                                     , isExtId
                                                     , canId
                                                     , isReceived
                                                     , TxDLC
                                                     , doNotify
                                                     );
    }
    
    /* If we get here then we couldn't call the related OS function. We have a bad system
       call argument and raise an exception. The next function call doesn't return. */
    rtos_osSystemCallBadArgument();

} /* End of cdr_osMakeMailboxReservation */




/** 
 * System call handler for sending a preconfigured message. A particular CAN
 * mailbox is used for sending a message with given, unchangeable CAN ID and DLC but with
 * new payload.
 *   @return
 * \a cdr_errApi_noError, if function succeeded, or \a cdr_errApi_txMailboxBusy, if the
 * buffer in the hardware is still occupied by the preceeding message, which is not
 * serialized on the CAN bus yet.\n
 *   An exception is raised, if one tries to send from a mailbox, which had been configured
 * for Rx.\n
 *   @param PID
 * Privileges management: The process ID of the calling task. This ID is compared to the
 * configuration of the mailbox (group). Access to the data needs to be granted to the
 * calling process, otherwise an exception is raised.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices. An out of range situation raises an exception.
 *   @param hMB
 * The message to send is identified by the handle of the mailbox it is associated with. A
 * message can be sent only if it had been associated with a mailbox in the hardware,
 * i.e. a successful call of cdr_osMakeMailboxReservation() or cdr_makeMailboxReservation()
 * is prerequisite of using this function. The handle to use here is the same as used when
 * having done the related call of cdr_(os)MakeMailboxReservation(). An out of range
 * situation raises an exception.
 *   @param payload
 * The message content bytes to send this time. The number f bytes has been agrred on at
 * mailbox registration time and can't be altered. It may be 0..8 Byte. Regardless of the
 * actual number, the passed memory address needs to allow read access to 8 Byte for the
 * user process. An exception would be raised otherwise.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
uint32_t cdr_scSmplHdlr_sendMessage( uint32_t PID
                                   , unsigned int idxCanDevice
                                   , unsigned int hMB
                                   , uint8_t payload[8]
                                   )
{
    /* As for any system call, all preconditions need to be tested to the extend that
       failures of the underlying OS code can be excluded. In particular, no arguments
       may pass the check, which would make an assertion fire in the OS code. This would
       in case halt the SW in DEBUG compilation and lead to undefined, potentially unsafe
       behavior in the PRODUCTION code. */
    cdr_idMailbox_t idMB;
    if(rtos_checkUserCodeReadPtr(payload, 8)
       &&  cdr_mapMailboxHandleToId(&idMB, idxCanDevice, hMB)
      )
    {
        const struct cdr_mailboxAccessConfig_t configMB =
                                    idMB.pDeviceConfig->userAccessMailboxAry[idMB.idxMailbox];
        const unsigned int minPID = configMB.minPIDToAccess;
        if(minPID > 0  &&  PID >= minPID  &&  !configMB.useAsRxMailbox)
        {
            /* After checking the potentially bad user input we may delegate to the "normal"
               function implementation. */
            return (uint32_t)cdr_osSendMessage_idMB(&idMB, &payload[0]);
        }
    }
    
    /* If we get here then we couldn't call the OS function to fetch the message data. We
       have a bad system call argument, raise exception. This function doesn't return. */
    rtos_osSystemCallBadArgument();

} /* End of cdr_scSmplHdlr_sendMessage */



/**
 * Get a reference to the API buffer for a particular Rx mailbox, which is used by polling
 * from a user task.\n
 *   The memory protection concept of the driver is having internal buffers for read
 * mailboxes, which are write-inhibitted to all user code. The driver can place the Rx data
 * into buffer, the user code can fetch it from there but a memory protection fault caused
 * by the driver is impossible. Moreover, if more tahn one process should read the same CAN
 * message than data corruption by one process and on cost of the other one is
 * hindered, too.\n
 *   API buffers are dedicated to Rx mailboxes, which are configured for polling. The
 * reference stays always valid and typical client code will call this function only once
 * and save an reuse the got reference.\n
 *   The flow to poll an Rx message will look like this:\n
 *   - The caller's initialization code will invoke cdr_makeMailboxReservation() to
 *     associate a CAN message (by CAN ID) with a particular mailbox. The chosen mailbox
 *     needs to have the required privileges for the given user process. This is a matter
 *     of driver configuration and can of course not be affected by the caller\n
 *   - The caller's initialization code will call this function and store the received
 *     pointer to the API buffer\n
 *   - Cyclically, the caller will invoke cdr_readMessage() to check if new data has been
 *     received. cdr_readMessage() is invoked with the same device index and mailbox handle
 *     as this function\n
 *   - Any time the reponse from cdr_readMessage() is other than cdr_errApi_rxMailboxEmpty
 *     the caller will fetch DLC, payload and Rx time stamp via the stored pointer
 *   @return
 * Get the address of the API buffer to use for the given mailbox. If the arguments are in
 * range and if the addressed mailbox is not obviously unusable for the purpose, the
 * function returns the buffer to use by reference.\n
 *   In all other cases it returns NULL and -- since this is considered an implementation
 * error in all reasonable use case -- an assertion fires in DEBUG compilation.\n
 *   Note, not getting NULL is no guarantee that a later access to the mailbox will succeed.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices. An out of range situation is caught by assertion.
 *   @param hMB
 * The handle of the mailbox, which the caller is about to use for polling. The API buffer
 * dedicated to this mailbox is returned by reference. The handle to use is the result of a
 * successful call of either cdr_osMakeMailboxReservation() or
 * cdr_makeMailboxReservation(). An out of range situation is caught by assertion.
 */
const cdr_apiBufferRxPolling_t *cdr_getRxPollingAPIBuffer( unsigned int idxCanDevice
                                                         , unsigned int hMB
                                                         )
{
    const cdr_apiBufferRxPolling_t *pAPIBuffer = NULL;
    
    cdr_idMailbox_t idMB;
    if(cdr_mapMailboxHandleToId(&idMB, idxCanDevice, hMB))
    {
        const struct cdr_mailboxAccessConfig_t configMB =
                                    idMB.pDeviceConfig->userAccessMailboxAry[idMB.idxMailbox];
                                    
        /* Plausibility, not a hard prove: Check, if the addressed mailbox is at all
           configured for user code Rx access. */
        if(configMB.minPIDToAccess > 0  &&  configMB.minPIDToAccess <= RTOS_NO_PROCESSES
           &&  configMB.useAsRxMailbox
          )
        {
            assert(configMB.idxAPIBuffer < sizeOfAry(_apiBufferRxPolling));
            pAPIBuffer = &_apiBufferRxPolling[configMB.idxAPIBuffer];
        }
    }
    
    assert(pAPIBuffer != NULL);
    return pAPIBuffer;

} /* End of cdr_getRxPollingAPIBuffer. */




/** 
 * System call handler for reading from the message API of the CAN driver. A particular CAN
 * mailbox is checked for newly received input and the received data is copied into the
 * API buffer in case. The caller can then fetch the message payload from the API buffer,
 * see cdr_getRxPollingAPIBuffer().
 *   @return
 * If the function returns either \a cdr_errApi_noError or \a cdr_errApi_warningRxOverflow
 * then a new message had been arrived and the mailbox contents are placed into the
 * associated Rx API buffer. The contents so far, from a preceeding call of this function,
 * are overwritten.\n
 *   \a cdr_errApi_noError should be the normal case, while \a cdr_errApi_warningRxOverflow
 * indicates that the call of the function came too late to read all incoming messages; at
 * least one preceeding message had been lost and overwritten by it successor.\n
 *   If no new message had been received since the previous call of this function for the
 * same mailbox then the function returns \a cdr_errApi_rxMailboxEmpty.\n
 *   The API buffer associated with the addressed mailbox is not altered if the return code
 * is other than \a cdr_errApi_noError or \a cdr_errApi_warningRxOverflow.\n
 *   An exception is raised, if one tries to read from a mailbox, which had been configured
 * for Tx.\n
 *   @param PID
 * Privileges management: The process ID of the calling task. This ID is compared to the
 * configuration of the mailbox (group). Access to the data needs to be granted to the
 * calling process, otherwise an exception is raised.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices. An out of range situation raises an exception.
 *   @param hMB
 * The message to check is identified by the handle of the mailbox it is associated with. A
 * message can be received only if it had been associated with a mailbox in the hardware,
 * i.e. a successful call of cdr_osMakeMailboxReservation() or cdr_makeMailboxReservation()
 * is prerequisite of using this function. The handle to use here is the same as used when
 * having done the related call of cdr_(os)MakeMailboxReservation(). An out of range
 * situation raises an exception.
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
uint32_t cdr_scSmplHdlr_readMessage( uint32_t PID
                                   , unsigned int idxCanDevice
                                   , unsigned int hMB
                                   )
{
    /* As for any system call, all preconditions need to be tested to the extend that
       failures of the underlying OS code can be excluded. In particular, no arguments
       may pass the check, which would make an assertion fire in the OS code. This would
       in case halt the SW in DEBUG compilation and lead to undefined, potentially unsafe
       behavior in the PRODUCTION code. */
    cdr_idMailbox_t idMB;
    if(cdr_mapMailboxHandleToId(&idMB, idxCanDevice, hMB))
    {
        const struct cdr_mailboxAccessConfig_t configMB =
                                    idMB.pDeviceConfig->userAccessMailboxAry[idMB.idxMailbox];
        const unsigned int minPID = configMB.minPIDToAccess;
        if(minPID > 0  &&  PID >= minPID  &&  configMB.useAsRxMailbox)
        {
            /* After checking the potentially bad user input we may delegate to the "normal"
               function implementation. */
            assert(configMB.idxAPIBuffer < sizeOfAry(_apiBufferRxPolling));
            struct cdr_apiBufferRxPolling_t * const pAPIBuffer =
                                                  &_apiBufferRxPolling[configMB.idxAPIBuffer];
            cdr_errorAPI_t errCode = cdr_osReadMessage_idMB( &idMB
                                                           , &pAPIBuffer->DLC
                                                           , &pAPIBuffer->payload_u8[0]
                                                           , &pAPIBuffer->timeStamp
                                                           );
            return (uint32_t)errCode;
        }
    }
    
    /* If we get here then we couldn't call the OS function to fetch the message data. We
       have a bad system call argument, raise exception. This function doesn't return. */
    rtos_osSystemCallBadArgument();

} /* End of cdr_scSmplHdlr_readMessage */
        
        

        

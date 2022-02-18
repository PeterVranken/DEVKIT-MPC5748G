#ifndef CDR_CANDRIVER_INCLUDED
#define CDR_CANDRIVER_INCLUDED
/**
 * @file cdr_canDriver.h
 * Definition of interface of module cdr_canDriver.c, which is globally accessible from all
 * compilation units of the CAN driver, but which are not exposed to a client of the
 * driver. The functions and data objects declared in this file must not be accessed by
 * driver client code.
 *
 * Copyright (C) 2020-2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include <limits.h>

#include "cde_canDriver.config.MCUDerivative.h"
#include "cdr_canDriver.config.inc"


/*
 * Defines
 */


/*
 * Global type definitions
 */

/** Identification of a particular CAN device. The driver code normally uses a zero based
    index of devices in use, which requires a mapping from this index to the particular,
    configured device behind. The mapping yields this device ID. */
typedef struct cdr_idCanDevice_t
{
    /** The index of the CAN I/O device in the array of devices implemented in the MCU.
        Index zero relates to FlexCAN_A, one to FlexCAN_B, etc. */
    unsigned int idxFlexCAN_x;
    
    /** The register file of the CAN I/O device in the MCU by reference. */
    CAN_Type *pCanDevice;
    
} cdr_idCanDevice_t;


/** Identification of a particular HW mailbox in terms of CAN device and index of the
    mailbox in the HW array. This way to address to a mailbox is used only internally. The
    driver's public API uses a mailbox handle instaed. Both are not equivalent because of
    the additionally receivable message by FIFO. */
typedef struct cdr_idMailbox_t
{
    /** The enumerated CAN device has been resolved to the HW CAN device by reference. */
    CAN_Type *pDevice;
    
    /** The configuration information of the CAN device by reference. */
    const cdr_canDeviceConfig_t *pDeviceConfig;
    
    /** The index of the addressed mailbox in the HW array of those inside the device. */
    unsigned int idxMailbox;

} cdr_idMailbox_t;



/** The structure of a mailbox. For now, we don't support CAN FD and therefore we have a
    fixed size. With FD, we could consider using a variable size struct.\n
      This struct definition needs to match the mailbox build-up as shown in RM 43.4.40,
       Table 43-7, p. 1771. */
typedef struct cdr_mailbox_t
{
    /** The control and status word (C/S word) of the mailbox. See macros CS_WORD_* for the
        fields inside the word. */
    uint32_t csWord;

    /** The second word holds the CAN ID, extended by the "local priority", which are three
        pseudo CAN ID bits that use otherwise unused ID bits bits 0-2. */
    uint32_t canId;

    /** The payload as 8 bytes with uint32_t alignment. */
    union
    {
        uint8_t payload[8];
        uint16_t payload_u16[4];
        uint32_t payload_u32[2];
    };
} cdr_mailbox_t;


/** An instance of this type collects all runtime-data, which is required to drive one of
    the CAN devices.
      @remark This objects collects data fom different interrupts and is potentially
    subject to heavy race conditions. New fields ned to be added with care and with details
    documentation, who is writing and who is reading the data. Some considerations:\n
      For debugging, it is useful to have counters for the total number of Rx and Tx events
    and how many of these failed. However, the mailbox interrupts may all be registered on
    different interrupt priorities and can preempt one another. A critical section would
    likely be needed for writing the counters. Which will likely be too expensive for a
    pure debugging tool. And the next consideration applies, too.\n
      Maintaining status flags for bus off/on and the other errors/warning may be deemed
    useful and seem to be easy implemented by writing to the according fields from the ISR.
    No race conditions would be expected as all of these interrupts belong to the same
    group and can't preempt eachother. However, by configuration, the interrupt group could
    be served by another core. Even if it maintains the data race-condition free, any other
    core will see the correct data only by chance, depending on the status and use of its
    local cache. It's alright to let a core collect its data in this struct but the
    same struct must not be considered a valid mechanism to report the information to
    another core. Moving the struct to uncached memory would be one of the options to
    overcome this. */
typedef struct cdr_canDeviceData_t
{
#ifdef MCU_MPC5748G
    /** Bus off/on status.
          @remark The status flag is maintained by the core, which serves the group of
        error interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupErrorTargetCore) and can be read by other
        contexts on the same core. It can't be accessed at all from other cores.
          @remark This flag is not supported on the MPC5775B/E, which doesn't offer an IRQ
        on bus off state done. We don't get a notice when bus off is cleared and can't
        therefore maintain such a flag. */
    bool isBusOff;
#endif

    /** Global counter for bus-off events. Each count means once entering the bus-off
        state. The counter is saturated at its implementation maximum. 
          @remark The counter is maintained by the core, which serves the group of bus off
        interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupBusOff.idxTargetCore) and can be read by other
        contexts on the same core. It can't be accessed at all from other cores. */
    unsigned int noBusOffEvents;
    
    /** Global counter of error interrupts (ESR1[ERRINT], RM 43.4.9, p. 1727ff) since
        software startup. The counter is saturated at its implementation maximum.
          @remark The counter is maintained by the core, which serves the group of error
        interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupError) and can be read by other contexts on
        the same core. It can't be accessed at all from other cores. */
    unsigned int noErrEvents;
    
#if defined(MCU_MPC5775B) || defined(MCU_MPC5775E)
    /** Global counter of error interrupts because of ECC errors in the CAN device RAM.
        (ERRSR[xCEIF], RM75 37.4.27 Error Status Register (CAN_ERRSR), p. 1716f) since
        software startup. The counter is saturated at its implementation maximum.
          @remark The counter is maintained by the core, which serves the group of error
        interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupError) and can be read by other contexts on
        the same core. It can't be accessed at all from other cores.
          @remark This flag is not supported on the MPC5748G, which doesn't offer an IRQ
        on ECC errors. */
    unsigned int noEccErrEvents;
#endif

    /** Last recently seen error in lower halfword of ESR1. */
    uint16_t lastErrEvent;

    /** Global counter for Rx FIFO overflow events. Each count means a lost Rx message. The
        counter is saturated at its implementation maximum.
          @remark The counter is maintained by the core, which serves the group of FIFO
        interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupFIFO.idxTargetCore) and can be read by other
        contexts on the same core. It can't be accessed at all from other cores. */
    unsigned int noRxFIFOOverflowEvents;

    /** Counter for Rx FIFO warning events. Each count means a temporary high load of the
        FIFO with the involved risk of loosing a message. The counter is saturated at its
        implementation maximum.
          @remark The counter is maintained by the core, which serves the group of FIFO
        interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupFIFO.idxTargetCore) and can be read by other
        contexts on the same core. It can't be accessed at all from other cores. */
    unsigned int noRxFIFOWarningEvents;

    /** Global counter of messages successfully received via the FIFO since software
        startup.
          @remark The counter wrapps around when the implementation maximum is
        reached.
          @remark The counter is maintained by the core, which serves the group of FIFO
        interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupFIFO.idxTargetCore) and can be read by other
        contexts on the same core. It can't be accessed at all from other cores. */
    unsigned int noRxMsgsFIFO;

} cdr_canDeviceData_t;


/** The run-time data of the CAN driver.\n
      The principal structure of the object is an array of objects of class \a
    cdr_canDeviceData_t, which hold the run-time data for a single CAN device (the
    devices are operated widely independent from one another). */
typedef cdr_canDeviceData_t cdr_canDriverData_t[CDR_NO_CAN_DEVICES_ENABLED];


/*
 * Global data declarations
 */

/** This is a lookup table, which maps a zero based CAN device index (enumeration
    cdr_enumCanDevice_t) to a CAN peripheral (according to MPC5748G.h) */
extern cdr_idCanDevice_t const RODATA(cdr_mapIdxToCanDevice)[CDR_NO_CAN_DEVICES_ENABLED];

/** The run-time data of the CAN driver. */
extern cdr_canDriverData_t cdr_canDriverData;


/*
 * Global prototypes
 */

/** Internally used Tx variant of cdr_osSendMessage(). */
enum cdr_errorAPI_t cdr_osSendMessage_idMB( const cdr_idMailbox_t * const pIdMB
                                          , const uint8_t payload[]
                                          );
                                     
/** Internally used Rx variant of cdr_osReadMessage(). */
enum cdr_errorAPI_t cdr_osReadMessage_idMB( const cdr_idMailbox_t * const pIdMB
                                          , uint8_t * const pDLC
                                          , uint8_t payload[]
                                          , uint16_t * const pTimeStamp
                                          );

/*
 * Global inline functions
 */

/**
 * Get the number of FIFO CAN ID filter entries in the filter table.
 *   @return
 * Get the number in the range 0..128. 0 is returned if the FIFO is not enabled.
 *   @param pDeviceConfig
 * The result depends on the CAN device configuration. It is passed in by reference.
 */
static inline unsigned int cdr_getNoFIFOFilterEntries
                                        (const cdr_canDeviceConfig_t *pDeviceConfig)
{
    /* Initialize the FIFO filter table. See RM 43.4.43, p. 1785ff, for the binary
       structure.
         See RM 43.4.14, table on p. 1740, for the number of table entries depending on
       CTRL2[RFFN]. */
    return pDeviceConfig->isFIFOEnabled
           ? 8u*(pDeviceConfig->CTRL2_RFFN+1u)
           : 0;

} /* End of cdr_getNoFIFOFilterEntries */





/**
 * Get the additional number of CAN messages, which can processed due to an enabled FIFO.
 * The FIFO filter table utilizes the driver RAM more efficiently than the normal mailboxes
 * and in our configuration both can be applied for one CAN ID. Therefore, the larger the
 * FIFO filter table is configured the more different CAN IDs can be processed.
 *   @return
 * Get the number of additionally processable CAN IDs. The result is zero if the FIFO is
 * switched off.
 *   @param pDeviceConfig
 * The result depends on the device configuration. It is passed in by reference.
 */
static inline unsigned int cdr_getAdditionalCapacityDueToFIFO
                                        (const cdr_canDeviceConfig_t *pDeviceConfig)
{
    /* Initialize the FIFO filter table. See RM 43.4.43, p. 1785ff, for the binary
       structure.
         See RM 43.4.14, table on p. 1740, for the number of table entries depending on
       CTRL2[RFFN].
         Note, we don't need to have confitional code whether FIFO is on; if off than RFFN
       is surely zero. */
    return 6u*pDeviceConfig->CTRL2_RFFN;

} /* End of cdr_getAdditionalCapacityDueToFIFO */





/**
 * Get the index of the first normal mailbox in the CAN device's RAM. The index is zero if
 * the FIFO is disabled by depends on the FIFO configuration otherwise.
 *   @return
 * The index of the first normal mailbox.
 *   @param pDeviceConfig
 * The configuration data set of the given CAN device by reference.
 */
static inline unsigned int cdr_getIdxOfFirstNormalMailbox
                                        (const cdr_canDeviceConfig_t * const pDeviceConfig)
{
    /* See RM, table on p.1740. */
    return pDeviceConfig->isFIFOEnabled
           ? 8u + 2u*pDeviceConfig->CTRL2_RFFN
           : 0u;

} /* End of cdr_getIdxOfFirstNormalMailbox */



/**
 * At the API of the driver, the client code addresses to a particular mailbox in the
 * device by enumerated device and mailbox handle. Internally, we identify a mailbox in
 * terms of device and HW index of mailbox. This helper function maps the former onto the
 * latter and implements a validation of the input at the same time.\n
 *   Note, the operation is not defined for FIFO mailbox handles. FIFO entries don't have
 * a one-by-one related HW mailbox.
 *   @return
 * The function returns \a true if it succeeds. It returns \a false if the arguments are
 * out of range. In this case * \a pIdMB has not been touched.
 *   @param pIdMB
 * The internally used identification of the mailbox is returned as * \a pIdMB if the
 * function succeeds.
 *   @param idxCanDevice
 * The administration of messages and mailboxes is made independently for all enabled CAN
 * devices. This parameter chooses the affected CAN device.\n
 *   See enumeration \a cdr_enumCanDevice_t (actually a zero based index) for the set of
 * possible devices.
 *   @param hMB
 * The handle of the mailbox. The handle to use here is the same as used when having done
 * the call of cdr_osMakeMailboxReservation() for the given mailbox.
 */
static inline bool cdr_mapMailboxHandleToId( cdr_idMailbox_t * const pIdMB
                                           , unsigned int idxCanDevice
                                           , unsigned int hMB
                                           )
{
    if(idxCanDevice >= sizeOfAry(cdr_canDriverConfig))
        return false;

    /* A pointer to the configuration of the device in operation is basis of the next
       steps. */
    const cdr_canDeviceConfig_t * const pDeviceConfig = &cdr_canDriverConfig[idxCanDevice];
    const unsigned int noFIFOMsgs = cdr_getNoFIFOFilterEntries(pDeviceConfig)
                     , additionalCapaFIFO = cdr_getAdditionalCapacityDueToFIFO(pDeviceConfig)
                     , idxMB = hMB - additionalCapaFIFO;
    
    /* hMB needs a simple transformation to become the index of the mailbox in the
       device. */
    if(hMB >= noFIFOMsgs  &&  idxMB < pDeviceConfig->noMailboxes)
    {
        pIdMB->pDevice = cdr_mapIdxToCanDevice[idxCanDevice].pCanDevice;
        pIdMB->pDeviceConfig = &cdr_canDriverConfig[idxCanDevice];
        pIdMB->idxMailbox = idxMB;
        return true;
    }
    else
        return false;
        
} /* End of cdr_mapMailboxHandleToId */




/**
 * Get a mailbox in the CAN device's RAM by index.
 *   @return
 * The pointer to the mailbox is returned.
 *   @param pCanDevice
 * The CAN device in use is passed by reference. It'll be one entry out of #CAN_BASE_PTRS
 * (see MPC5748G.h); this is however not checked.
 *   @param idxMB
 * The index of the mailbox. The index relates to the non-FD CAN situation, where all MBs
 * have the same size, according to RM, Table 43-13, p 1779ff.\n
 *   The range is 0..95, which is checked by assertion.
 *   @remark
 * The current configuration of the device, e.g. FD or not or FIFO filter table size, is
 * not considered by the function. It just provides the simple address calculation.
 */
static inline volatile cdr_mailbox_t *cdr_getMailboxByIdx( const CAN_Type * const pCanDevice
                                                         , unsigned int idxMB
                                                         )
{
    assert(idxMB < CDR_NO_HW_MAILBOXES_PER_CAN_DEVICE);
    return ((volatile cdr_mailbox_t*)&pCanDevice->RAMn[0]) + idxMB;

} /* End of cdr_getMailboxByIdx */



#endif  /* CDR_CANDRIVER_INCLUDED */

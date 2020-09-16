#ifndef CDR_CANDRIVER_INCLUDED
#define CDR_CANDRIVER_INCLUDED
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
#include "cdr_canDriver.config.h"
#include "cdr_canDriverAPI.h"


/*
 * Defines
 */


/*
 * Global type definitions
 */

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
    another core. Moving the struct to uncached memory Mayould be one of the options to
    overcome this. */
typedef struct cdr_canDeviceData_t
{
    /** Bus off/on status.
          @remark The status flag is maintained by the core, which serves the group of
        error interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupErrorTargetCore) and can be read by other
        contexts on the same core. It can't be accessed at all from other cores. */
    bool isBusOff;

    /** Global counter for Rx FIFO overflow events. Each count means a lost Rx message. The
        counter is saturated at its implementation maximum.
          @remark The counter is maintained by the core, which serves the group of FIFO
        interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupFIFOTargetCore) and can be read by other
        contexts on the same core. It can't be accessed at all from other cores. */
    unsigned int noRxFIFOOverflowEvents;

    /** Counter for Rx FIFO warning events. Each count means a temporary high load of the
        FIFO with the involved risk of loosing a message. The counter is saturated at its
        implementation maximum.
          @remark The counter is maintained by the core, which serves the group of FIFO
        interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupFIFOTargetCore) and can be read by other
        contexts on the same core. It can't be accessed at all from other cores. */
    unsigned int noRxFIFOWarningEvents;

    /** Global counter of messages successfully received via the FIFO since software
        startup.
          @remark The counter wrapps around when the implementation maximum is
        reached.
          @remark The counter is maintained by the core, which serves the group of FIFO
        interrupts from the given CAN device (see configuration item
        cdr_canDriverConfig[idxCanDev].irqGroupFIFOTargetCore) and can be read by other
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
    cdr_canDevice_t) to a CAN peripheral (according to MPC5748G.h) */
extern CAN_Type * const cdr_mapIdxToCanDevice[CDR_NO_CAN_DEVICES_ENABLED];

/** The run-time data of the CAN driver. */
extern cdr_canDriverData_t cdr_canDriverData;


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */

/**
 * Get the index of the first normal mailbox in the CAN device's RAM. The index is zero if
 * the FIFO is disabled by depends on the FIFO configuration otherwise.
 *   @return
 * The index of the first normal mailbox.
 *   @param pDeviceConfig
 * The configuration data set of the given CAN device by reference.
 */
static inline unsigned int cdr_osGetIdxOfFirstMailbox
                                        (const cdr_canDeviceConfig_t * const pDeviceConfig)
{
    /* See RM, table on p.1740. */
    return pDeviceConfig->isFIFOEnabled
           ? 8u + 2u*pDeviceConfig->CTRL2_RFFN
           : 0u;

} /* End of cdr_osGetIdxOfFirstMailbox */




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
static inline volatile cdr_mailbox_t *cdr_osGetMailbox( const CAN_Type * const pCanDevice
                                                      , unsigned int idxMB
                                                      )
{
    assert(idxMB < 96);
    return ((volatile cdr_mailbox_t*)&pCanDevice->RAMn[0]) + idxMB;

} /* End of cdr_osGetMailbox */





#endif  /* CDR_CANDRIVER_INCLUDED */

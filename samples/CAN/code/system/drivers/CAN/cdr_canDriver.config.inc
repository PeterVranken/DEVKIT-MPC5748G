#ifdef CDR_IS_INCLUDED_FROM_DRIVER_IMPLEMENTATION
/**
 *   @file cdr_canDriver.config.h
 * Application dependent configuration of CAN I/O driver.
 *   @remark
 * This file actually is a C source file. It is not named as such as it should not be
 * compiled as an independent compilation unit. Instead, we include it from the driver
 * implementation file. Reason is the possibility, to have a default configuration here in
 * the driver implementation folder but to overload it with the true, application dependent
 * file by setting the compiler include search path accordingly or by renaming the file
 * here or -- less convenient but safer -- by renaming it here.
 *   @todo
 * We should investigate if a weak implementation wouldn't be the better way to implement
 * the overloading.
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

#include "typ_types.h"
#include "cdr_canDriver.config.h"


/*
 * Defines
 */

/** @todo Revise this text block and integrate it
Concept: We have a configuration file with the settings as initialized const struct. The
designated initializer expressions keep this well-maintainable. The driver implementation
offeres a default or standard configuration. This is part of the driver implementation. Any
application will copy this to a local folder, where it can be modified to match the
application needs. Inclusion of the right file can be an issue. It can be handled via the
order of entries in the compiler include search path (risk of hard to find mistakes) or the
default configuration file in the driver implementation file is renamed.

Rational is the re-use ofthe same source code in different scenarios. Mainly, this
addresses having several test applications, which can all be build in the same environment
and which may all use different driver configurations.

The configuration starts with a set of principal macros, which enable or disable each of
the physical available CAN devices. These macros don't enable runtime activities but they
control the compilation of code and data elements from the driver. Code elements like ISRs,
configuration and data objects will only be compiled (and consume resources) if the related
CAN device is enabled.

At runtime, the reference to a device is made by zero based index. The mapping to a CAN
device is possible by a const lookup table, which is generated by preprocessor switches.
The indexes can be made available via an accordingly generated enumeration.

The index based addressing to the device makes associated configuration and run-time data
objects accessible in O(1).

Interrupt services don't need the lookup table, they know implicitly to which device (and
thus configuration and data object) they belong.

User services, like polling a mailbox, will require the index and the loop-up.

Interrupts: On any core but in groups. Polling for simplicity core-wise in same groups: No
limitation for any realistic use-case.
*/



/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/// @todo Preliminary solution. Will later be handled by application owned copy of this file
extern void mza_osCbOnCANRx( unsigned int hMB
                           , bool isExtId
                           , unsigned int canId
                           , unsigned int DLC
                           , const uint8_t payload[8]
                           , unsigned int timeStamp
                           );
void mza_osCbOnCanError(bool isCanFD, uint32_t ESR1);
void mza_osCbOnCanBusOff(bool enteringBusOff, uint32_t ESR1);


/*
 * Local data definitions
 */

/** This is the configuration data set of the CAN driver.\n
      The principal structure of the object is an array of objects of class \a
    cdr_canDeviceConfig_t, which hold the configuration for a single CAN device (the
    devices are operated widely independent from one another). You will edit the initializer
    expressions for those CAN devices, which are enabled by macros
    #CDR_ENABLE_USE_OF_CAN_0, #CDR_ENABLE_USE_OF_CAN_1, etc. The rest doesn't care. */
const cdr_canDriverConfig_t cdr_canDriverConfig =
{
#if 0 /* Don't enable this code block: This is our template for the configuration of one
         actual CAN device. Copy it to the code blocks related to the CAN device you're
         going to use and modify it there. */
    [cdr_canDev_CAN_n] =
    {
    }
#endif
#if CDR_ENABLE_USE_OF_CAN_0 == 1
    [cdr_canDev_CAN_0] =
    {
        /** Select the Baud rate. Supported are 250 kBd, 500 kBd and 1 MBd. The unit is
            10000 Bd. */
        .baudRate = 50 /* *10^4 Bd */,
        
        /** Enable the FIFO for Rx messages. This will normally increase the number of
            different processable CAN IDs with the need for a SW queue concept. */
        .isFIFOEnabled = true,

        /** The number of active mailboxes. Range is 0..96 if \a isFIFOEnabled is \a false
            and 6 .. 96 otherwise. */
        .noMailboxes = 96,

        /** This setting controls the partitioning of the mailbox RAM space of the CAN
            device between FIFO (plus CAN ID filter table) and normal mailboxes.\n
              CTRL2[RFFN] is the amount of RAM, which is occupied by the FIFO. It means
            that we have an Rx FIFO with up to 8*(RFFN+1) explicitly configurable Rx CAN
            IDs and another 90-2*(RFFN+1) mailboxes for either Rx or Tx messages. So we can
            process a maximum of N_max=90+6*(RFFN+1) different CAN messages, whereof at
            minimum N_rx_min=8*(RFFN+1) and at maximum N_tx_max=90-2*(RFFN+1) Tx messages.
            See RM 43.4.14, p.1740, for additional information. Examples:\n
              RFFN= 0, N_max= 96, N_rx_min=  8, N_tx_max=88 (widely useless, no MB extension)\n
              RFFN= 3, N_max=114, N_rx_min= 32, N_tx_max=82\n
              RFFN= 8, N_max=144, N_rx_min= 72, N_tx_max=72 (pretty balanced)\n
              RFFN=15, N_max=186, N_rx_min=128, N_tx_max=58\n
              Another important aspect is polling. N_tx_max is the number of normal
            mailboxes, which can be used for either Rx or Tx. If they are used for Rx then
            the SW can use polling to receive the messages. The N_rx_min Rx messages can be
            received by interrupt only.\n
              Note, all mentioned maximum numbers are yielded only with a maximum number of
            active mailboxes, i.e. noMailboxes=96.\a
              This setting doesn't care if \a isFIFOEnabled is \a false. */
        .CTRL2_RFFN = 8,

        /** This is an element of the CAN timing but it depends on the chosen number of
            mailboxes in use. Don't change it without adjustment of the dependent settings.
            See RM 43.5.9.9, Tx Arbitration start delay, for details. */
        .CTRL2_TASD = 22,
        
        /** The interrupts from the CAN device can be handled on any core; the HW is widely
            paralel and different mailboxes can be accessed without conflicts or race
            conditions from different cores. For the same reason, it is possible to have
            preempting ISRs -- serving a mailbox can be preempted by serving another
            mailbox of higher priority. Therefore we allow to configure individually for
            each interrupt, which core is is served on and at which priority.\n
              If message Rx and Tx events produce an interrupt then the information is
            forwarded to the driver's client code by notification callback. Where
            applicable, these callbacks are configured, too. Otherwise, they need to be set
            to NULL.\n
              Mailbox group interrupts support Rx and Tx notifications. The FIFO interrupt
            group supports only an Rx notification.\n
              The error and bus off interrrupt groups have their internal handlers plus an
            optional notification handler. They may be enabled (priority > 0) without
            configuring a notifcation (i.e. callback is NULL).\n
              Here, we have the interrupt configuration for error interrupts, ERRINT,
            ERRINT_FAST. */
        .irqGroupError =
        {
            .idxTargetCore     = RTOS_CORE_Z4A,
            .irqPrio           = 6,
            .osCallbackOnError = mza_osCbOnCanError,
            .osCallbackOnTx    = NULL,   /* Not applicable, needs to be NULL. */
        },   
        
        /** IRQ configuration for bus off etc. IRQs */
        .irqGroupBusOff =
        {
            .idxTargetCore      = RTOS_CORE_Z4A,
            .irqPrio            = 7,
            .osCallbackOnBusOff = mza_osCbOnCanBusOff,
            .osCallbackOnTx     = NULL,   /* Not applicable, needs to be NULL. */
        },   
        
        /** Here, we have the interrupt configuration for the group of FIFO interrupts. */
        .irqGroupFIFO =
        {
            .idxTargetCore  = RTOS_CORE_Z4A,
            .irqPrio        = 5,
            .osCallbackOnRx = mza_osCbOnCANRx,
            .osCallbackOnTx = NULL,   /* Not applicable, needs to be NULL. */
        },
        
        /** IRQ configuration, IRQs of mailboxes 0..3. This interrupt group is not
            available for our configuration: FIFO on, with 72 entries in the filter table
            (CTRL2_RFFN = 8). */
        .irqGroupMB0_3 =
        {
            .idxTargetCore  = RTOS_CORE_Z4A,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        },   
        
        /** IRQ configuration, IRQs of mailboxes 0..3. This interrupt group is not
            available for our configuration: FIFO on, with 72 entries in the filter table
            (CTRL2_RFFN = 8). */
        .irqGroupMB4_7 =
        {
            .idxTargetCore  = RTOS_CORE_Z4A,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        },   
        
        /** IRQ configuration, IRQs of mailboxes 0..3. This interrupt group is not
            available for our configuration: FIFO on, with 72 entries in the filter table
            (CTRL2_RFFN = 8). */
        .irqGroupMB8_11 =
        {
            .idxTargetCore  = RTOS_CORE_Z4A,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        },  
        
        /** IRQ configuration, IRQs of mailboxes 0..3. This interrupt group is not
            available for our configuration: FIFO on, with 72 entries in the filter table
            (CTRL2_RFFN = 8). */
        .irqGroupMB12_15 =
        {
            .idxTargetCore  = RTOS_CORE_Z4A,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQs of mailboxes 16..31. */
        .irqGroupMB16_31 =
        {
            .idxTargetCore  = RTOS_CORE_Z4A,
            .irqPrio        = 1,
            .osCallbackOnRx = mza_osCbOnCANRx,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQs of mailboxes 32..63. */
        .irqGroupMB32_63 =
        {
            .idxTargetCore  = RTOS_CORE_Z4A,
            .irqPrio        = 2,
            .osCallbackOnRx = mza_osCbOnCANRx,
            .osCallbackOnTx = NULL,
        },
        
        /** IRQ configuration, IRQs of mailboxes 64..95. */
        .irqGroupMB64_95 =
        {
            .idxTargetCore  = RTOS_CORE_Z4A,
            .irqPrio        = 3,
            .osCallbackOnRx = mza_osCbOnCANRx,
            .osCallbackOnTx = NULL,
        },
        
        /** Privileges for mailboxes: By default code in user processes can't access the
            mailboxes. */
        .userAccessMailboxAry = 
        {
            [24 ... 95] = {.minPIDToAccess = 2},
        },
    },
#endif
#if CDR_ENABLE_USE_OF_CAN_1 == 1
    [cdr_canDev_CAN_1] =
    {},
#endif
#if CDR_ENABLE_USE_OF_CAN_2 == 1
    [cdr_canDev_CAN_2] =
    {},
#endif
#if CDR_ENABLE_USE_OF_CAN_3 == 1
    [cdr_canDev_CAN_3] =
    {},
#endif
#if CDR_ENABLE_USE_OF_CAN_4 == 1
    [cdr_canDev_CAN_4] =
    {},
#endif
#if CDR_ENABLE_USE_OF_CAN_5 == 1
    [cdr_canDev_CAN_5] =
    {},
#endif
#if CDR_ENABLE_USE_OF_CAN_6 == 1
    [cdr_canDev_CAN_6] =
    {},
#endif
#if CDR_ENABLE_USE_OF_CAN_7 == 1
    [cdr_canDev_CAN_7] =
    {},
#endif
};


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


# undef CDR_IS_INCLUDED_FROM_DRIVER_IMPLEMENTATION
#endif /* CDR_IS_INCLUDED_FROM_DRIVER_IMPLEMENTATION */
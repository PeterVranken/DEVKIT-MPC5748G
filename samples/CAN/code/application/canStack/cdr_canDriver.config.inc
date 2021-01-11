/**
 *   @file cdr_canDriver.config.inc
 * Application dependent configuration of CAN I/O driver.
 *   @remark
 * This file actually is a hybrid from C header and source file. Therefore, it's is neither
 * named as those and got the extension *.inc. A copy of this template is what you will
 * edit in order to configure the CAN driver according to your application's needs. Please
 * find more details in cdr_canDriverAPI.h.\n
 *   @remark
 * Never include this file or your copy directly from your application and never try to
 * compile it.
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
#include "rtos.config.h"
#include "bsw_basicSoftware.h"


#ifndef CDR_CANDRIVER_CONFIG_INC_INCLUDED
#define CDR_CANDRIVER_CONFIG_INC_INCLUDED
/*
 * Defines
 */

/** The MCU MPC5748G has eight CAN devices, MPC5775B/E has four. Each of them can be
    enabled/disabled at compile-time. Here, enabling doesn't mean any execution of
    initialization code, it just relates to enabling the compilation of the code and data
    structures needed to support the given device.\n
      Here for CAN device 0: Compile the code to support CAN device CAN_0? */
#define CDR_ENABLE_USE_OF_CAN_0     1
#define CDR_ENABLE_USE_OF_CAN_1     0 /** Compile the code to support CAN device CAN_1? */
#define CDR_ENABLE_USE_OF_CAN_2     0 /** Compile the code to support CAN device CAN_2? */
#define CDR_ENABLE_USE_OF_CAN_3     0 /** Compile the code to support CAN device CAN_3? */
#define CDR_ENABLE_USE_OF_CAN_4     0 /** MPC5748G only: Compile code for CAN device CAN_4? */
#define CDR_ENABLE_USE_OF_CAN_5     0 /** MPC5748G only: Compile code for CAN device CAN_5? */
#define CDR_ENABLE_USE_OF_CAN_6     0 /** MPC5748G only: Compile code for CAN device CAN_6? */
#define CDR_ENABLE_USE_OF_CAN_7     0 /** MPC5748G only: Compile code for CAN device CAN_7? */

/** The core, which serves the CAN interrupts. In this particular sample, all interrupts in
    use are served by one core. It can be selected here. */
#define CDR_CAN_IRQ_SERVICING_CORE  RTOS_CORE_Z4A

/** The Rx polling API for user code requires some attention drawn to memory allocation.
    The API implementation wants to allocate memory for all Rx mailboxes, which are enabled
    for polling. (It's an assumption that most applications will process most messages on
    event base and that the number of polled messages is rather little.)\n
      The usual paradigm for a data fetching function is taking the address of some caller
    provided memory as argument and to place the result data via this pointer. If our user
    task API would follow this concept then it had to validate the pointer before use in
    order to avoid a memory protection issue from within operating system code.
    Unfortunately, pointer validation is an expensive operation and should be avoided for
    frequently called functions (see rtos_checkUserCodeWritePtr()).\n
      The pointer validation can be avoided by holding memory buffers for the API in the
    operating system data segment. It is readable by the requesting user process and
    in-corruptible. Static allocation is desired for performance reasons and to avoid
    generally undesired dynamic memory allocation.\n
      The static allocation discards reentrance of the related API function - which is not
    an issue as the function is by principle anyway not reentrant for one and the same
    message/mailbox.\n
      The only remaining complexity is the data declaration. Although the required size is
    a compile-time constant, it can't be figured out by a constant expression. Therefore,
    you need to (redundantly) specify the number of polling-enabled mailboxes in this
    define. Redundantly, as the same number is implicit to the privileges configuration of
    the mailboxes. The way out is a run-time check in the startup code of the driver, which
    proves the value specified here with respect to the configuration of the mailboxes.\n
      Note, the number specified here is the total number for all of the enabled CAN
    devices. */
#define CDR_NO_RX_USER_CODE_POLLING_MAILBOXES   6


/** For the evaluation boards DEVKIT-MPC5748G and MPC5775BE-416DS, the driver can configure
    the MCU pins, which are routed to the CAN connector mounted on these boards. This is an
    option only and it must not be used if the CAN I/O driver is run on another board.\n
      On either board, the CAN connector can only be used with CAN device 0. This device
    needs to be enabled. */
#define CDR_ENABLE_MCU_PINS_FOR_EVAL_BOARD      1    

/** In this application of the CAN driver, we serve all mailboxes with same interrupt
    priority. This is essential since the API of our CAN interface, which takes newly
    received CAN messages as input is not reentrant. There must be no race conditions in
    reporting new messages.
      The chosen priority should stay below the kernel tick in order to have this for time
    budget supervision. Timing supervision is essential for the safety concept since the
    CAN driver needs to make callbacks into untrusted user processes. */
#define CDR_IRQ_PRIO_CAN_RX                     1

_Static_assert( CDR_IRQ_PRIO_CAN_RX < RTOS_KERNEL_IRQ_PRIORITY_CORE_0
              , "Bad IRQ priority assignment can break the safety concept"
              );
              
/*
 * Global type definitions
 */

/* Only now, load the definition of the configuration data set: To avoid waste of ROM
   space, several elements are defined conditionally depending on the previously made
   selection of enabled CAN devices. */
#include "cdr_canDriver.config.h"


/*
 * Global data declarations
 */


#endif /* CDR_CANDRIVER_CONFIG_INC_INCLUDED */

/*
 * Local data definitions
 */

#ifdef CDR_IS_INCLUDED_FROM_DRIVER_IMPLEMENTATION
/** This is the configuration data set of the CAN driver.\n
      The principal structure of the object is an array of objects of class \a
    cdr_canDeviceConfig_t, which hold the configuration for a single CAN device (the
    devices are operated widely independent from one another). You will edit the initializer
    expressions for those CAN devices, which are enabled by macros
    #CDR_ENABLE_USE_OF_CAN_0, #CDR_ENABLE_USE_OF_CAN_1, etc. The rest doesn't care. */
const cdr_canDriverConfig_t RODATA(cdr_canDriverConfig) =
{
#if CDR_ENABLE_USE_OF_CAN_0 == 1
    [cdr_canDev_CAN_0] =
    {
        /** Select the Baud rate. Supported are 250 kBd, 500 kBd and 1 MBd. The unit is
            10000 Bd. */
        .baudRate = 50 /* *10^4 Bd */,
        
        /** Enable the FIFO for Rx messages. This will normally increase the number of
            different processable CAN IDs with the need for a SW queue concept. */
        .isFIFOEnabled = true,

        /** The number of active mailboxes. Range is 0 ..
            #CDR_NO_HW_MAILBOXES_PER_CAN_DEVICE if \a isFIFOEnabled is \a false and 6 ..
            #CDR_NO_HW_MAILBOXES_PER_CAN_DEVICE otherwise. */
        .noMailboxes = CDR_NO_HW_MAILBOXES_PER_CAN_DEVICE,

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
            .idxTargetCore     = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio           = 0,
            .osCallbackOnError = NULL,
            .osCallbackOnTx    = NULL,   /* Not applicable, needs to be NULL. */
        },   
        
        /** IRQ configuration for bus off etc. IRQs */
        .irqGroupBusOff =
        {
            .idxTargetCore      = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio            = 0,
            .osCallbackOnBusOff = NULL,
            .osCallbackOnTx     = NULL,   /* Not applicable, needs to be NULL. */
        },   
        
        /** Here, we have the interrupt configuration for the group of FIFO interrupts. */
        .irqGroupFIFO =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = CDR_IRQ_PRIO_CAN_RX,
            .osCallbackOnRx = &bsw_osCbOnCANRx,
            .osCallbackOnTx = NULL,   /* Not applicable, needs to be NULL. */
        },
        
#if defined(MCU_MPC5748G)
        /** IRQ configuration, IRQs of mailboxes 0..3. This interrupt group is not
            available for our configuration: FIFO on, with 72 entries in the filter table
            (CTRL2_RFFN = 8). */
        .irqGroupMB0_3 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        },   
        
        /** IRQ configuration, IRQs of mailboxes 0..3. This interrupt group is not
            available for our configuration: FIFO on, with 72 entries in the filter table
            (CTRL2_RFFN = 8). */
        .irqGroupMB4_7 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        },   
        
        /** IRQ configuration, IRQs of mailboxes 0..3. This interrupt group is not
            available for our configuration: FIFO on, with 72 entries in the filter table
            (CTRL2_RFFN = 8). */
        .irqGroupMB8_11 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        },  
        
        /** IRQ configuration, IRQs of mailboxes 0..3. This interrupt group is not
            available for our configuration: FIFO on, with 72 entries in the filter table
            (CTRL2_RFFN = 8). */
        .irqGroupMB12_15 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
#elif defined(MCU_MPC5775B)  ||  defined(MCU_MPC5775E)
        
        /** IRQ configuration, IRQ of mailbox 0. */
        .irqMB0 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 1. */
        .irqMB1 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 2. */
        .irqMB2 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 3. */
        .irqMB3 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 4. */
        .irqMB4 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 5. */
        .irqMB5 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 6. */
        .irqMB6 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 7. */
        .irqMB7 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 8. */
        .irqMB8 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 9. */
        .irqMB9 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 10. */
        .irqMB10 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 11. */
        .irqMB11 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 12. */
        .irqMB12 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 13. */
        .irqMB13 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 14. */
        .irqMB14 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQ of mailbox 15. */
        .irqMB15 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
#endif
        
        /** IRQ configuration, IRQs of mailboxes 16..31. */
        .irqGroupMB16_31 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        }, 
        
        /** IRQ configuration, IRQs of mailboxes 32..63. */
        .irqGroupMB32_63 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        },
        
#if defined(MCU_MPC5748G)
        /** IRQ configuration, IRQs of mailboxes 64..95. */
        .irqGroupMB64_95 =
        {
            .idxTargetCore  = CDR_CAN_IRQ_SERVICING_CORE,
            .irqPrio        = 0,
            .osCallbackOnRx = NULL,
            .osCallbackOnTx = NULL,
        },
#endif
        
        /** Permission to make mailbox reservations is given only one particular user
            process, or it can be generally prohibitted for user code and left to the
            operating system.\n
              Configure the PID of the process, which may do or configure 0 if only the
            operating system may. */
        .pidMakeMailboxReservation = 1,
        
        /** Privileges for mailboxes: By default, code in user processes can't access the
            mailboxes (i.e. minPIDToAccess=0). You need to specify just those mailboxes,
            which need to be accessed by polling from user tasks.\n
              Note, the index used here is the HW mailbox index not the user visible
            mailbox handle.\n
              Note, the total number of enabled Rx mailboxes in all enabled devices needs
            to match #CDR_NO_RX_USER_CODE_POLLING_MAILBOXES.
              Note, the sort order of API buffers doesn't matter. Particularly, no run-time
            penalty is involved with having a zig-zag-pattern. */
        .userAccessMailboxAry = 
        {
            [/*hMB=72*/ 24] = {.minPIDToAccess = 2, .useAsRxMailbox = true, .idxAPIBuffer = 0},
            [/*hMB=73*/ 25] = {.minPIDToAccess = 2, .useAsRxMailbox = true, .idxAPIBuffer = 1},
            [/*hMB=74*/ 26] = {.minPIDToAccess = 2, .useAsRxMailbox = true, .idxAPIBuffer = 2},
            [/*hMB=75*/ 27] = {.minPIDToAccess = 2, .useAsRxMailbox = true, .idxAPIBuffer = 3},
            [/*hMB=76*/ 28] = {.minPIDToAccess = 2, .useAsRxMailbox = true, .idxAPIBuffer = 4},
            [/*hMB=77*/ 29] = {.minPIDToAccess = 2, .useAsRxMailbox = true, .idxAPIBuffer = 5},
            [/*hMB=78*/ 30] = {.minPIDToAccess = 2, .useAsRxMailbox = false},
            [/*hMB=79*/ 31] = {.minPIDToAccess = 2, .useAsRxMailbox = false},
            [/*hMB=80*/ 32] = {.minPIDToAccess = 2, .useAsRxMailbox = false},
            [/*hMB=81*/ 33] = {.minPIDToAccess = 2, .useAsRxMailbox = false},
            [/*hMB=82*/ 34] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=83*/ 35] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=84*/ 36] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=85*/ 37] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=86*/ 38] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=87*/ 39] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=88*/ 40] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=89*/ 41] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=90*/ 42] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=91*/ 43] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=92*/ 44] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=93*/ 45] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=94*/ 46] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=95*/ 47] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=96*/ 48] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=97*/ 49] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=98*/ 50] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=99*/ 51] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=100*/ 52] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=101*/ 53] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=102*/ 54] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=103*/ 55] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=104*/ 56] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=105*/ 57] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=106*/ 58] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=107*/ 59] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=108*/ 60] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=109*/ 61] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=110*/ 62] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=111*/ 63] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
#if defined(MCU_MPC5748G)
            [/*hMB=112*/ 64] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=113*/ 65] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=114*/ 66] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=115*/ 67] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=116*/ 68] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=117*/ 69] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=118*/ 70] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=119*/ 71] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=120*/ 72] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=121*/ 73] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=122*/ 74] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=123*/ 75] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=124*/ 76] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=125*/ 77] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=126*/ 78] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=127*/ 79] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=128*/ 80] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=129*/ 81] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=130*/ 82] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=131*/ 83] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=132*/ 84] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=133*/ 85] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=134*/ 86] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=135*/ 87] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=136*/ 88] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=137*/ 89] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=138*/ 90] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=139*/ 91] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=140*/ 92] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=141*/ 93] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=142*/ 94] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
            [/*hMB=143*/ 95] = {.minPIDToAccess = 1, .useAsRxMailbox = false},
#endif
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

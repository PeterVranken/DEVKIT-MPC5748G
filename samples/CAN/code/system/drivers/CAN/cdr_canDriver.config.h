#ifndef CDR_CANDRIVER_CONFIG_INCLUDED
#define CDR_CANDRIVER_CONFIG_INCLUDED
/**
 * @file cdr_canDriver.config.h
 * Type definition for application dependent configuration data objects of CAN I/O driver.
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


/*
 * Defines
 */

/** The MCU has 8 CAN devices. Each of them can be enabled/disabled at compile-time. Here,
    enabling dosn't mean any execution of initialization code, it just relates to enabling
    the compilation of the code and data structures needed to support the given device.\n
      Here for CAN device 0: Compile the code to support CAN device CAN_0? */
#define CDR_ENABLE_USE_OF_CAN_0     1
#define CDR_ENABLE_USE_OF_CAN_1     0 /** Compile the code to support CAN device CAN_1? */
#define CDR_ENABLE_USE_OF_CAN_2     0 /** Compile the code to support CAN device CAN_2? */
#define CDR_ENABLE_USE_OF_CAN_3     0 /** Compile the code to support CAN device CAN_3? */
#define CDR_ENABLE_USE_OF_CAN_4     0 /** Compile the code to support CAN device CAN_4? */
#define CDR_ENABLE_USE_OF_CAN_5     0 /** Compile the code to support CAN device CAN_5? */
#define CDR_ENABLE_USE_OF_CAN_6     0 /** Compile the code to support CAN device CAN_6? */
#define CDR_ENABLE_USE_OF_CAN_7     0 /** Compile the code to support CAN device CAN_7? */


/** The number of enabled CAN devices. Many data objects will have just this size. */
#define CDR_NO_CAN_DEVICES_ENABLED ((CDR_ENABLE_USE_OF_CAN_0 == 1)     \
                                    +(CDR_ENABLE_USE_OF_CAN_1 == 1)    \
                                    +(CDR_ENABLE_USE_OF_CAN_2 == 1)    \
                                    +(CDR_ENABLE_USE_OF_CAN_3 == 1)    \
                                    +(CDR_ENABLE_USE_OF_CAN_4 == 1)    \
                                    +(CDR_ENABLE_USE_OF_CAN_5 == 1)    \
                                    +(CDR_ENABLE_USE_OF_CAN_6 == 1)    \
                                    +(CDR_ENABLE_USE_OF_CAN_7 == 1)    \
                                   )

/*
 * Global type definitions
 */

/** An instance of this type collects all constant cnfiguration data for one CAN device. */
typedef struct cdr_canDeviceConfig_t
{
    /** Enable or not the FIFO mechanism of the CAN device for Rx messages. This will
        normally increase the number of different processable CAN IDs with the need for a SW
        queue concept.\n
          The use of the FIFO is not possible with CAN FD. */
    bool isFIFOEnabled;

    /** The number of mailboxes in use including those, whose space is occupied by FIFO and
        its filters. Range is 0..96 if \a isFIFOEnabled is \a false and 6 .. 96
        otherwise.\n
           This setting must be changed with care - there are other dependent settings,
        like \a CTRL2_TASD. */
    uint8_t noMailboxes;

    /** This setting controls the partitioning of the mailbox RAM space of the CAN device
        between FIFO (plus CAN ID filter table) and normal mailboxes.\n
          CTRL2[RFFN] is the amount of RAM, which is occupied by the FIFO. It means that we
        have an Rx FIFO with up to 8*(RFFN+1) explicitly configurable Rx CAN IDs and
        another 90-2*(RFFN+1) mailboxes for either Rx or Tx messages. So we can process a
        maximum of N_max=90+6*(RFFN+1) different CAN messages, whereof at minimum
        N_rx_min=8*(RFFN+1) and at maximum N_tx_max=90-2*(RFFN+1) Tx messages. See RM
        43.4.14, p.1740, for additional information. Examples:\n
          RFFN= 0, N_max= 96, N_rx_min=  8, N_tx_max=88 (widely useless, no MB extension)\n
          RFFN= 3, N_max=114, N_rx_min= 32, N_tx_max=82\n
          RFFN= 8, N_max=144, N_rx_min= 72, N_tx_max=72 (pretty balanced)\n
          RFFN=15, N_max=186, N_rx_min=128, N_tx_max=58\n
          Another important aspect is polling. N_tx_max is the number of normal mailboxes,
        which can be used for either Rx or Tx. If they are used for Rx then the SW can use
        polling to receive the messages. The N_rx_min Rx messages can be received by
        interrupt only.
          This value doesn't care if \a isFIFOEnabled is \a false. */
    uint8_t CTRL2_RFFN;

    /** This is an element of the CAN timing but it depends on the chosen number of mailboxes
        in use. Don't change it without adjustment of the dependent settings. See RM 43.5.9.9,
        Tx Arbitration start delay, for details. */
    uint8_t CTRL2_TASD;

    /** The interrupts from the CAN device can be handled on any core; the HW is widely
        paralel and different mailboxes can be accessed without conflicts or race
        conditions from different cores. For the same reason, it is possible to have
        preempting ISRs -- serving a mailbox can be preempted by serving another mailbox
        of higher priority. Therefore we allow to configure individually for each
        interrupt, which core is is served on and at which priority.\n
          Note, if the FIFO is enabled then the settings for mailboxes 0..3 have not
        effect.\n
          Here, the target core for the FIFO interrupts of this device. Range is
        0..#RTOS_NO_CORES: Any core can handle the IRQ, even a bare-metal core. */
    uint8_t irqGroupFIFOTargetCore;
    uint8_t irqGroupFIFOIrqPrio;        /** IRQ prio in INTC for the Rx FIFO Interrupts */
    uint8_t irqGroupErrorTargetCore;    /** Target core for bus off etc. IRQs */
    uint8_t irqGroupErrorIrqPrio;       /** Prio for error/warning IRQs */
    uint8_t irqGroupMB0_3TargetCore;    /** Target core, IRQs of mailboxes 0..3 */
    uint8_t irqGroupMB0_3IrqPrio;       /** Prio for IRQS mailboxes 0..3 */
    uint8_t irqGroupMB4_7TargetCore;    /** Target core, IRQs of mailboxes 4..7 */
    uint8_t irqGroupMB4_7IrqPrio;       /** Prio for IRQS mailboxes 4..7 */
    uint8_t irqGroupMB8_11TargetCore;   /** Target core, IRQs of mailboxes 8..11 */
    uint8_t irqGroupMB8_11IrqPrio;      /** Prio for IRQS mailboxes 8..11 */
    uint8_t irqGroupMB12_15TargetCore;  /** Target core, IRQs of mailboxes 12_15 */
    uint8_t irqGroupMB12_15IrqPrio;     /** Prio for IRQS mailboxes 12_15 */
    uint8_t irqGroupMB16_31TargetCore;  /** Target core IRQs of mailboxes 16..31 */
    uint8_t irqGroupMB16_31IrqPrio;     /** Prio for IRQS mailboxes 16..31 */
    uint8_t irqGroupMB32_63TargetCore;  /** Target core IRQs of mailboxes 32..63 */
    uint8_t irqGroupMB32_63IrqPrio;     /** Prio for IRQS mailboxes 32..63 */
    uint8_t irqGroupMB64_95TargetCore;  /** Target core IRQs of mailboxes 64..95 */
    uint8_t irqGroupMB64_95IrqPrio;     /** Prio for IRQS mailboxes 64..95 */

    /** Callback for Rx events. This callback into external client code is invoked on
        message reception. The callback is used for normal mailboxes and when a message is
        received via the FIFO.\n
          While the FIFO will always notify Rx events by interrupt, it depends for normal
        mailboxes. Each mailbox can decide individually if or if not an interrupt is raised
        on reception. (If not, a polling API allows to still make use of the mailbox.) The
        decision is made with the mailbox registration API.\n
          The function pointer must not be NULL if at least one Rx interrupt is enabled, be
        it the FIFO enabled or any mailbox configured to generate an interrupt.\n
          Note that the FIFO and all the different mailbox groups can be configured to have
        different interrupt priorities, although served by the same core. If so, then the
        callback needs to be implemented re-entrant: It won't be preempted by Rx events
        from the same mailbox group or from a subsequent FIFO Rx event but another mailbox
        can preempt in this case. See configuration of interrupt priorities (configuration
        items \a irqGroup*IrqPrio and -- related -- \a irqGroup*TargetCore). */
    void (*callbackOnRx)( bool isExtId
                        , unsigned int canId
                        , unsigned int DLC
                        , const uint8_t payload[8]
                        , unsigned int timeStamp
                        );
   
    /** Callback for Tx events. This callback into external client code is invoked on
        completion of message sending. Completion means that the message has been successfully
        serialized on the bus or that sending had to be aborted for some error condition.
        (The most relevant error condition is the client code overwriting a mailbox, which
        had not yet signalled completion.)\n
          Each Tx mailbox can decide individually if or if not an interrupt is raised
        on reception. The decision is made with the mailbox registration API.\n
          The function pointer must not be NULL if at least one Tx mailbox interrupt is
        enabled.\n
          Note that all the different mailbox groups can be configured to have different
        interrupt priorities, although served by the same core. If so, then the callback
        needs to be implemented re-entrant: It won't be preempted by Tx events from the
        same mailbox group but another Tx mailbox can preempt in this case. See
        configuration of interrupt priorities (configuration items \a irqGroup*IrqPrio and
        -- related -- \a irqGroup*TargetCore). */
    void (*callbackOnTx)( bool isExtId
                        , unsigned int canId
                        , unsigned int DLC
                        , bool isAborted
                        , unsigned int timeStamp
                        );

} cdr_canDeviceConfig_t;


/** The configuration data of the CAN driver.\n
      The principal structure of the object is an array of objects of class \a
    cdr_canDeviceConfig_t, which hold the configuration data for a single CAN device (the
    devices are operated widely independent from one another). */
typedef cdr_canDeviceConfig_t cdr_canDriverConfig_t[CDR_NO_CAN_DEVICES_ENABLED];


/*
 * Global data declarations
 */


/*
 * Local data definitions
 */

/** This is the configuration data set of the CAN driver. The object is defined in file
    cdr_canDriver.config.inc. Your application will have its own, dedicated copy of that
    file and there, you will make the configuration of the driver appropriate for your
    specific application. */
extern const cdr_canDriverConfig_t cdr_canDriverConfig;


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


#endif  /* CDR_CANDRIVER_CONFIG_INCLUDED */

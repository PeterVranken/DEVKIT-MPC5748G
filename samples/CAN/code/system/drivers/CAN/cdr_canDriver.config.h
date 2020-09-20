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

/**
 *   @func callbackOnRx_t
 * The type of a callback for Rx events, defined in the client code of this driver. This
 * callback into external client code is invoked on message reception. The callback is used
 * for normal mailboxes and when a message is received via the FIFO.\n
 *   While the FIFO will always notify Rx events by interrupt, it depends for normal
 * mailboxes. Each mailbox can decide individually if or if not an interrupt is raised on
 * reception. (If not, a polling API allows to still make use of the mailbox.) The decision
 * is made with the mailbox registration API.\n
 *   Note that the FIFO and all the different mailbox groups can be configured to have
 * different interrupt priorities, although served by the same core. If so, then the
 * callback needs to be implemented re-entrant: It won't be preempted by Rx events from the
 * same mailbox group or -- for the FIFO ISR -- from a subsequent FIFO Rx event but another
 * mailbox can preempt in this case. See configuration of interrupt priorities
 * (configuration items \a irqGroup*IrqPrio and -- related -- \a irqGroup*TargetCore in
 * struct \a cdr_canDeviceConfig_t).
 *   @param hMB
 * The handle of the notifying mailbox as agreed on at messge registration time is returned
 * to support a simple association of the Rx event with the data content.
 *   @param isExtId
 * Standard and extended CAN IDs partly share the same space of numbers. Hence, we need the
 * additional Boolean information, which of the two the ID \a canId belongs to.
 *   @param canId
 * The standard or extended ID of the received CAN message.
 *   @param DLC
 * Data length code, the number of received content bytes.
 *   @param payload
 * The received payload data. The first \a DLC bytes in the array contain the received
 * data. The remaining 8 - \a DLC bytes may be read but they are undefined.\n
 *   Note, the array is guaranteed to be uint32_t aligned. This can be exploited for a
 * faster copy operation.
 *   @param timeStamp
 * The time of reception of the message is recorded by hardware and the value is forwarded
 * to the callback. The absolute value has not meaning, time-base is a free running 16 Bit
 * counter. The frequency of the timer is the CAN bit rate; having a bus with 500 kBd the
 * unit of the timer would be 2µs. The timer wraps around at 2^16-1.
 *   @remark
 * The callback is invoked from one of the CAN device's interrupt contexts. It is executed
 * in supervisor mode. All Rx interrupts share this callback, so it needs to be reentrant
 * if two of them should be configured not to have the same interrupt priority.
 */
typedef void (*cdr_osCallbackOnRx_t)( unsigned int hMB
                                    , bool isExtId
                                    , unsigned int canId
                                    , unsigned int DLC
                                    , const uint8_t payload[8]
                                    , unsigned int timeStamp
                                    );


/**
 * Callback for Tx events. This callback into external client code is invoked on
 * completion of message sending. Completion means that the message has been successfully
 * serialized on the bus or that sending had to be aborted for some error condition.
 * (The most relevant error condition is the client code overwriting a mailbox, which
 * had not yet signalled completion.)\n
 *   Each Tx mailbox can decide individually if or if not an interrupt is raised
 * on reception. The decision is made with the mailbox registration API.\n
 *   The function pointer must not be NULL if at least one Tx mailbox interrupt is
 * enabled.\n
 *   Note that all the different mailbox groups can be configured to have different
 * interrupt priorities, although served by the same core. If so, then the callback
 * needs to be implemented re-entrant: It won't be preempted by Tx events from the
 * same mailbox group but another Tx mailbox can preempt in this case. See
 * configuration of interrupt priorities (configuration items \a irqGroup*IrqPrio and
 * -- related -- \a irqGroup*TargetCore).
 *   @param hMB
 * The handle of the notifying mailbox as agreed on at messge registration time is returned
 * to support a simple association of the Tx event with the transmitted data content.
 *   @param isExtId
 * Standard and extended CAN IDs partly share the same space of numbers. Hence, we need the
 * additional Boolean information, which of the two the ID \a canId belongs to.
 *   @param canId
 * The standard or extended ID of the transmitted CAN message.
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
 * The callback is invoked from one of the CAN device's interrupt contexts. It is executed
 * in supervisor mode. All Tx interrupts share this callback, so it needs to be reentrant
 * if two of them should be configured not to have the same interrupt priority.
 */
typedef void (*cdr_osCallbackOnTx_t)( unsigned int hMB
                                    , bool isExtId
                                    , unsigned int canId
                                    , unsigned int DLC
                                    , bool isAborted
                                    , unsigned int timeStamp
                                    );

/** This structure bundles the configuration items that are needed for a mailbox group
    interrupt. For simplicity, the same structures is applied to the FIFO interrupt,
    although it can't produce a Tx notification, so that one field of the struct is
    superfluous in this case. */
typedef struct cdr_mailboxIrqConfig_t
{
    /** The interrupts from the CAN device can be handled on any core; the HW is widely
        parallel and different mailboxes can be accessed without conflicts or race
        conditions from different cores. For the same reason, it is possible to have
        preempting ISRs -- serving a mailbox can be preempted by serving another mailbox
        of higher priority. Therefore we allow to configure individually for each
        interrupt, which core is is served on and at which priority.\n
          Here, we have the target core by index for the interrupt of the given mailbox
        group (or the FIFO). Range is 0..#RTOS_NO_CORES: Any core can handle the IRQ, even
        a bare-metal core. */
    uint8_t idxTargetCore;
    
    /** Here, we have the interrupt priority in INTC for the the interrupt of the given
        mailbox group (or the FIFO). Range is 1..15 if the interrupt is enabled for at
        least one mailbox in the group; otherwise it needs to be zero.\n
          Note, the FIFO can only be used with interrupt notification, so here we have a
        range of 1..15 if the FIFO is enabled and zero otherwise. */
    uint8_t irqPrio;

    /** Callback for Rx events. This callback into external client code is invoked on
        message reception in any of the mailboxes belonging to the given group.\n
          While the FIFO will always notify Rx events by interrupt, it depends for normal
        mailboxes. Each mailbox can decide individually if or if not an interrupt is raised
        on reception. (If not, a polling API allows to still make use of the mailbox.) The
        decision is made with the mailbox registration API.\n
          The function pointer must not be NULL if at least one Rx interrupt is enabled, be
        it the FIFO enabled or any mailbox in the gropu configured to generate an
        interrupt. Otherwise it needs to be NULL.\n
          Note that the FIFO and all the different mailbox groups can be configured to have
        different interrupt priorities, although served by the same core. Regardless, they
        may share the same callback. If so, then the callback needs to be implemented
        re-entrant: It won't be preempted by Rx events from the same mailbox group or --
        for the FIFO ISR -- from a subsequent FIFO Rx event but a mailbox from another
        group can preempt in this case. See configuration of interrupt priorities
        (configuration items \a irqPrio and -- related -- \a idxTargetCore). */
    cdr_osCallbackOnRx_t osCallbackOnRx;
   
    /** Callback for Tx events. This callback into external client code is invoked on
        completion of message sending. Completion means that the message has been
        successfully serialized on the bus or that sending had to be aborted for some error
        condition.\n
          Each mailbox group can decide individually if or if not an interrupt is raised on
        transmission complete. The decision is made with the mailbox registration API.\n
          The function pointer must not be NULL if at least one mailbox in the group has
        enabled a Tx interrupt. Otherwise it needs to be NULL.\n
          There is no Tx notifictaion from the FIFO. For the group of FIFO IRQ, this item
        need to be set to NULL.\n
          Note that all the different mailbox groups can be configured to have different
        interrupt priorities, although served by the same core. Regardless, they may share
        the same callback. If so, then the callback needs to be implemented re-entrant: It
        won't be preempted by Tx events from the same mailbox group but a mailbox from
        another group can preempt in this case. See configuration of interrupt priorities
        (configuration items \a irqPrio and -- related -- \a idxTargetCore). */
    cdr_osCallbackOnTx_t osCallbackOnTx;

} cdr_mailboxIrqConfig_t;




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
          If message Rx and Tx events produce an interrupt then the information is
        forwarded to the driver's client code by notification callback. Where applicable,
        these callbacks are configured, too. Otherwise, they need to be set to NULL.\n
          Mailbox group interrupts support Rx and Tx notifications. The FIFO interrupt
        group supports only an Rx notification and the error interrrupt group doesn't
        support any of the notifications.\n
          Here, we have the interrupt configuration for the group of FIFO interrupts. */
    cdr_mailboxIrqConfig_t irqGroupFIFO;
    cdr_mailboxIrqConfig_t irqGroupError;  /** IRQ configuration for bus off etc. IRQs */
    cdr_mailboxIrqConfig_t irqGroupMB0_3;  /** IRQ configuration, IRQs of mailboxes 0..3 */
    cdr_mailboxIrqConfig_t irqGroupMB4_7;  /** IRQ configuration, IRQs of mailboxes 4..7 */
    cdr_mailboxIrqConfig_t irqGroupMB8_11; /** IRQ configuration, IRQs of mailboxes 8..11 */
    cdr_mailboxIrqConfig_t irqGroupMB12_15;/** IRQ configuration, IRQs of mailboxes 12_15 */
    cdr_mailboxIrqConfig_t irqGroupMB16_31;/** IRQ configuration, IRQs of mailboxes 16..31 */
    cdr_mailboxIrqConfig_t irqGroupMB32_63;/** IRQ configuration, IRQs of mailboxes 32..63 */
    cdr_mailboxIrqConfig_t irqGroupMB64_95;/** IRQ configuration, IRQs of mailboxes 64..95 */

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

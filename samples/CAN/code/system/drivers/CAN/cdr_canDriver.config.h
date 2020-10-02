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
 *   @func cdr_osCallbackOnBusOff_t
 * The type of a callback for bus off events, defined in the client code of this driver. This
 * callback into external client code is invoked on bus off interrupts, BOFFINT and
 * BOFFDONEINT, see RM 43.4.9, p. 1727ff.
 *   @param enteringBusOff
 * This flag makes the distinction, whether the notification reports the beginning of a
 * bus-off phase or its end, i.e. successful recovery from the bus-off situation.
 *   @param ESR1
 * The read value of device regsiter ESR1 on entry into the ISR, which makes the
 * notification call. The error bits can be inspected. See RM 43.4.9, p. 1727ff for the
 * meaning of the bits.
 */
typedef void (*cdr_osCallbackOnBusOff_t)(bool enteringBusOff, uint32_t ESR1);


/**
 *   @func cdr_osCallbackOnError_t
 * The type of a callback for error events, defined in the client code of this driver. This
 * callback into external client code is invoked on error interrupts, ERRINT and
 * ERRINT_FAST, see RM 43.4.9, p. 1727ff. (Actually, since we don't support CAN FD, we will
 * just see ERRINT interrupts.)
 *   @param isCanFD
 * This flag makes the distinction, whether the notification reports a standard CAN error
 * or an error during transmission of a CAN FD frame.
 *   @param ESR1
 * The read value of device regsiter ESR1 on entry into the ISR, which makes the
 * notification call. The error bits can be inspected. See RM 43.4.9, p. 1727ff for the
 * meaning of the bits.
 */
typedef void (*cdr_osCallbackOnError_t)(bool isCanFD, uint32_t ESR1);


/**
 *   @func cdr_osCallbackOnRx_t
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
 *   @func cdr_osCallbackOnTx_t
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

/** This structure bundles the configuration items that are needed for an interrupt group. */
typedef struct cdr_irqConfig_t
{
    /** The interrupts from the CAN device can be handled on any core; the HW is widely
        parallel and different mailboxes can be accessed without conflicts or race
        conditions from different cores. For the same reason, it is possible to have
        preempting ISRs -- serving a mailbox, for example, can be preempted by serving
        another mailbox of higher priority. Therefore we allow to configure individually
        for each interrupt group, which core is is served on and at which priority.\n
          Here, we have the target core by index for any of the the interrupts of the given
        group (or the FIFO). Range is 0..#RTOS_NO_CORES: Any core can handle the IRQ, even
        a bare-metal core. */
    uint8_t idxTargetCore;
    
    /** Here, we have the interrupt priority in INTC for the the interrupt of the given
        interrupt group.\n
          For mailbox interrupts, the range is 1..15 if the interrupt is enabled for at
        least one mailbox in the group; otherwise it needs to be zero.\n
          Note, the FIFO can only be used with interrupt notification, so here we have a
        range of 1..15 if the FIFO is enabled and zero otherwise.\n
          For other interrupt groups (error or bus off), the priority is a switch to enable
        or disable the interrupt. Set prio to zero to disable it, otherwise the range is
        1..15. */
    uint8_t irqPrio;

    /** Some of the interrupts require just one callback. Different interrupts require
        notification callbacks with different signature. We group these different types of
        callbacks in an anonymous union - which effectively implements just aliases for one
        and the same field in the struct. */
    union
    {
        /** Callback for error events. This callback into external client code is invoked
            on CAN frame transmission errors.\n
              The function pointer can be NULL if no notification is required. The ISR in
            the CAN driver will then just count the occurances and save the last recent
            error condition. It needs to be NULL if the entire interrupt group is disabled
            by configuring a priority of zero. */
        cdr_osCallbackOnError_t osCallbackOnError;
        
        /** Callback for bus off events. This callback into external client code is invoked
            on entry into a bus-off state or after successful recovery fom a bus-off
            state.\n
              The function pointer can be NULL if no notification is required. The ISR in
            the CAN driver will then just count the occurances of bus-off phases and
            maintain the current bus-off state for the device. The pointer needs to be NULL
            if the entire interrupt group is disabled by configuring a priority of zero. */
        cdr_osCallbackOnBusOff_t osCallbackOnBusOff;
        
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
    };


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
        (configuration items \a irqPrio and -- related -- \a idxTargetCore).\n
           This configuration item doesn't matter for interrupt groups other than mailbox
        interrupt groups. */
    cdr_osCallbackOnTx_t osCallbackOnTx;

} cdr_irqConfig_t;



/** The user process API provides access to Tx mailboxes and Rx mailboxes by polling.
    (Primarily, IRQ based Rx and Tx notifications go only into OS code. The OS needs to
    decide whether/how to propagte these events to the user processes. safe-RTOS offers
    several services to do so but this is no longer in the responsibility of the CAN
    driver.)\n
      Here we have the privileges configuration for normal mailboxes.\n
      The Rx FIFO can be operated by IRQ only and hence it doesn't matter with
    respect to user process privilege management.
      @remark The designated initializers are defined such that non-mentioned array
    elements are implicitly configure the according mailboxes as not accessible by any
    user process. You just need to configure the mailboxes, which are enabled for user
    code access. */
typedef struct cdr_mailboxAccessConfig_t
{
    /** Access to the mailbox is allowed to code running in a user process with process
        ID greater or equal as this value. (Either Rx or Tx is allowed, depending on the
        initialization of the mailbox using cdr_osMakeMailboxReservation().) A value of
        0 or greater than #RTOS_NO_PROCESSES make the mailbox unavailable to all user
        code. */
    uint8_t minPIDToAccess;

    /** Use of the mailboxes is allowed either for Rx or for Tx. */
    bool useAsRxMailbox;
    
    /** The index of the API buffer to be used for Rx messages. All
        user-polling-enabled Rx mailboxes need to specify a unique API buffer and the
        indexes in use must not skip possible values. Note, the index space is shared
        between all enabled CAN devices.\n
          In other words, the ordered set of all indexes specified for all
        user-polling-enabled mailboxes of all enbaled CAN devices needs to form a
        contiguous series of integers, starting with zero. Moreover, the highest
        specified index needs to be #CDR_NO_RX_USER_CODE_POLLING_MAILBOXES - 1.\n
          User code access enabled Tx mailboxes doesn't require an API buffer. Instead
        of a valid index, the special value #CDR_API_BUF_IDX_INVALID needs to be
        configured.\n
          These strict consistency constraints are double-checked at driver startup
        time by cdr_checkDriverConfiguration(), so that configuration errors can't do
        any harm. */
    uint16_t idxAPIBuffer;
    
} cdr_mailboxAccessConfig_t;



/** An instance of this type collects all constant cnfiguration data for one CAN device. */
typedef struct cdr_canDeviceConfig_t
{
    /** Select the Baud rate. Supported are 250 kBd, 500 kBd and 1 MBd. The unit is 
        10000 Bd. */
    uint8_t baudRate;

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
    cdr_irqConfig_t irqGroupError;
    cdr_irqConfig_t irqGroupBusOff; /** IRQ config for bus off and related warning IRQs */
    cdr_irqConfig_t irqGroupFIFO;   /** IRQ configuration for Rx FIFO IRQs */
    cdr_irqConfig_t irqGroupMB0_3;  /** IRQ configuration, IRQs of mailboxes 0..3 */
    cdr_irqConfig_t irqGroupMB4_7;  /** IRQ configuration, IRQs of mailboxes 4..7 */
    cdr_irqConfig_t irqGroupMB8_11; /** IRQ configuration, IRQs of mailboxes 8..11 */
    cdr_irqConfig_t irqGroupMB12_15;/** IRQ configuration, IRQs of mailboxes 12_15 */
    cdr_irqConfig_t irqGroupMB16_31;/** IRQ configuration, IRQs of mailboxes 16..31 */
    cdr_irqConfig_t irqGroupMB32_63;/** IRQ configuration, IRQs of mailboxes 32..63 */
    cdr_irqConfig_t irqGroupMB64_95;/** IRQ configuration, IRQs of mailboxes 64..95 */

    /** Permission to make mailbox reservations is given only one particular user process,
        or it can be generally prohibitted for user code and left to the operating system.\n
          Configure the PID of the process, which may do or configure 0 if only the
        operating system may. */
    uint8_t pidMakeMailboxReservation;
    
    /** The user process API provides access to Tx mailboxes and Rx mailboxes by polling.
        (Primarily, IRQ based Rx and Tx notifications go only into OS code. The OS needs to
        decide whether/how to propagte these events to the user processes. safe-RTOS offers
        several services to do so but this is no longer in the responsibility of the CAN
        driver.)\n
          Here we have the privileges configuration for normal mailboxes.\n
          The Rx FIFO can be operated by IRQ only and hence it doesn't matter with
        respect to user process privilege management.
          @remark The designated initializers are defined such that non-mentioned array
        elements are implicitly configure the according mailboxes as not accessible by any
        user process. You just need to configure the mailboxes, which are enabled for user
        code access. */
/// @todo Find a solution to avoid the literal number here
    cdr_mailboxAccessConfig_t userAccessMailboxAry[96];

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

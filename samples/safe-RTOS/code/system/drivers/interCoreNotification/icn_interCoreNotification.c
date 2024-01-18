/**
 * @file icn_interCoreNotification.c
 * Implementation of a driver for interrupt based core-to-core notifications. The hardware
 * (INTC) based service to generate interrupts an a core of choice is wrapped into a
 * driver, that offers a notification service as a further core-to-core communication
 * channel.\n
 *   The concept is simple. A core has an API to assert a SW settable interrupt. The
 * interrupt is configured to be handled by another core. This other core will preempt the
 * running task and it executes the ISR, which is part of this driver too. The ISR can be
 * configured for two basic actions:\n
 *   - It may trigger an RTOS event (on the notified core)\n
 *   - It may run a handler on the notified core\n
 *   In particular the first action is beneficial: A task of sufficiently high priority
 * will execute the operation, which is deemed suitable for the kind of notification.\n
 *   However, the second action, effectively an ISR on the notified core, has its own
 * charme: The notifier receives a receipt when it is done. Memory mapped data flow without
 * additional synchronization means and still without race conditions can be easily
 * implemented.
 *   @remark
 * The service is not considered an element of the kernel itself. safe-RTOS implements a
 * simple BCC scheduling, which doesn't support voluntary suspension of threads. An
 * beneficial integration of the service with the kernel is therefore not possible. It
 * would, e.g., be possible to let the notifier wait until the notified acknowledges -- but
 * not without busy wait and the busy wait -- if considered appropriate -- can be
 * implemented as easy in the application code using the API of this driver.\n
 *   Consequently, the implementation of this driver could be used even without the RTOS,
 * e.g., on a core with bare-metal application code. Only the notification by triggering an
 * RTOS event must of course not be configured in that case.
 *   @remark
 * This driver uses a different configuration concept than the others. The RTOS itself and
 * most of our simple drivers so far use a run-time API for configuration. This is
 * transparent, elegant and user-friendly but means putting some constant data into
 * expensive RAM. In this driver, we use a C implementation file for configuration. Each
 * application needs to have its individual implementation file.
 *
 * Copyright (C) 2020-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   icn_osInitInterCoreNotificationDriver
 *   icn_osSendNotification
 *   icn_osIsNotificationPending
 * Local functions
 *   swIrqAction
 *   swIrq0 .. swIrq23 (depending on configuration)
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "MPC5748G.h"
#include "rtos.h"
#include "std_decoratedStorage.h"
#include "icn_interCoreNotification.h"

/* To include the configuration file, we must not use the quotes. This would make the
   compiler load the template file (located in the same directory as this source file)
   rather than the (optional) true file, located somewhere in a folder of the driver's
   client code. */
#include <icn_interCoreNotification.config.h>


#if ICN_NO_NOTIFICATIONS > 0

/*
 * Defines
 */


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */

/** The configuration of an event to be notified on the destination core. It is a
    combination of the addressed event processor and the characteristics of the event
    (ordinary vs. countable). */
struct icn_configurationEvent_t
{
    /** The addressed event processor by zero based index. This ID is also returned by the
        constructor of the event processor, see rtos_osCreateEventProcessor(). */
    unsigned int eventProcessorId;

    /** The distinction between sending an ordinary or a countable event. */
    bool isCountableEvent;
};

/** The configuration of a single notification. */
typedef struct icn_notification_t
{
    /** The notification addresses a particular core. The intention is to address to
        another core but the driver works still fine if the addressed core is the notifying
        core at the same time.\n
          The range is 0..2 for the MPC5748G. The upper bounds is the number of cores in
        the MCU. It is dependent on the derivative. */
    unsigned int idxNotifiedCore;

    /** The notification happens by interrupt on the notified core. The INTC interrupt
        priority can be chosen individually for each notification. The range is 1..15.\n
          Note, the safety concept can be broken if the chosen priority is greater or equal
        to the kernel priority, #RTOS_KERNEL_IRQ_PRIORITY_CORE_0 (_1, _2).*/
    unsigned int priorityNotificationIrq;

    /** The notification can be the invocation of a callback on the notified core. If
        desired, put the pointer to a function void (*)(uintptr_t) and otherwise NULL.\n
          The passed function argument is the notification parameter, see
        icn_osSendNotification().\n
          Note, the execution of a callback on the other core can easily break the safety
        concept. The callback fully belongs into the sphere of trusted code. However, its
        implementation can safely call untrusted code by applying the according services of
        safe-RTOS. */
    void (*osNotificationHandler)(uintptr_t notificationParam);

    /** The notification can be the triggering of one or more safe-RTOS events in order to
        activate associated tasks. Here, we have the number of events to trigger. The range
        is 0 .. #ICN_MAX_NO_SENT_EVENTS. */
    unsigned int noSentEvents;

    /** Here, we have an array of configuration items for sent events. The first
        \a noSentEvents elements of the array refer to actually sent events. The other
        elements of the array don't care. */
    struct icn_configurationEvent_t evNotificationAry[ICN_MAX_NO_SENT_EVENTS];

} icn_notification_t;


/** The ROM resident configuration data set of the driver. */
typedef struct icn_configuration_t
{
    /** The list of actually configured notifications. */
    icn_notification_t notificationAry[ICN_NO_NOTIFICATIONS];

} icn_configuration_t;


/*
 * Data definitions
 */

/* Read the user-editted, application dependent configuration data set definition. */
#undef ICN_INTERCORENOTIFICATION_CONFIG_INCLUDED
#define ICN_IS_INCLUDED_FROM_DRIVER_IMPLEMENTATION
# include <icn_interCoreNotification.config.h>
#undef ICN_IS_INCLUDED_FROM_DRIVER_IMPLEMENTATION

/** This is the temporary storage of notification parameter values. The storage is used
    from sending the notification on one core (icn_osSendNotification()) till acknowledge of
    the notification in the ISR for the related SW settable interrupt on the other core. */
static volatile uint32_t UNCACHED_OS(_notificationParamAry)[ICN_NO_NOTIFICATIONS];

/*
 * Function implementation
 */

/**
 * This function implements the common part of of all ISR for the SW settable interrupts.
 * The configured notification action is implemented. On the notified core, we can either
 * trigger an RTOS event and activate the associated tasks or we can invoke a callback.
 *   @param idxNotification
 * The index of the notification to do. The index is identical to the index in the
 * configuration array.
 */
static void swIrqAction(unsigned int idxNotification)
{
    const icn_notification_t * const pN = &icn_configuration.notificationAry[idxNotification];

    const uint32_t notificationParam = _notificationParamAry[idxNotification];

    /* Before we actually notify anyone we need to ensure that the store of the parameter
       has reached the shared RAM. */
    std_fullMemoryBarrier();

    /* Invoke the optional callback. This option is handled first. Here, and in contrast to
       sending an RTOS event, the latency time may matter. (The consequences of a sent RTOS
       event will happen anyway at earliest after ending the ISR.) */
    if(pN->osNotificationHandler != NULL)
        pN->osNotificationHandler(notificationParam);

    /* Send all configured events. */
    unsigned int u = pN->noSentEvents;
    const struct icn_configurationEvent_t *pEvCfg = &pN->evNotificationAry[0];
    while(u-- > 0)
    {
        if(pEvCfg->isCountableEvent)
        {
            assert(notificationParam > 0u);
            rtos_osSendEventCountable(pEvCfg->eventProcessorId, /*evMask*/ notificationParam);
        }
        else
            rtos_osSendEvent(pEvCfg->eventProcessorId, /* taskParam */ notificationParam);
        
        ++ pEvCfg;
    }
} /* End of swIrqAction */





/**
 * The SW settable interrupt service routines are implemented by macro and created multiple
 * times. Each function implements one notification. The configurable actions are
 * implemented in a shared sub-routine.
 *   @param idxN
 * The index of the notification as used in the API of the driver and in the configuration
 * data set. This is not the index of the SW settable interrupt that implements the
 * notification!
 */
#define swInt(idxN)                                                                         \
    static void swInt##idxN(void)                                                           \
    {                                                                                       \
        /* Take the configured actions for the given notification. */                       \
        swIrqAction(idxN);                                                                  \
                                                                                            \
        /* Acknowledge the interrupt bit of the software interrupt. */                      \
        _Static_assert( idxN+ICN_FIRST_SW_IRQ_TO_APPLY >= SS0_IRQn                          \
                        &&  idxN+ICN_FIRST_SW_IRQ_TO_APPLY <= SS23_IRQn                     \
                      , "Index of interrupt out of range"                                   \
                      );                                                                    \
        /* See RM, 23.6.12 INTC Software Set/Clear Interrupt Register (INTC_SSCIRn) */      \
        INTC->SSCIR[idxN+ICN_FIRST_SW_IRQ_TO_APPLY] = 0x01;                                 \
    }

#if ICN_NO_NOTIFICATIONS > 0
swInt(0)
# define FCT_PTR_SW_INT_0   [0]=&swInt0,
#else
# define FCT_PTR_SW_INT_0
#endif
#if ICN_NO_NOTIFICATIONS > 1
swInt(1)
# define FCT_PTR_SW_INT_1   [1]=&swInt1,
#else
# define FCT_PTR_SW_INT_1
#endif
#if ICN_NO_NOTIFICATIONS > 2
swInt(2)
# define FCT_PTR_SW_INT_2   [2]=&swInt2,
#else
# define FCT_PTR_SW_INT_2
#endif
#if ICN_NO_NOTIFICATIONS > 3
swInt(3)
# define FCT_PTR_SW_INT_3   [3]=&swInt3,
#else
# define FCT_PTR_SW_INT_3
#endif
#if ICN_NO_NOTIFICATIONS > 4
swInt(4)
# define FCT_PTR_SW_INT_4   [4]=&swInt4,
#else
# define FCT_PTR_SW_INT_4
#endif
#if ICN_NO_NOTIFICATIONS > 5
swInt(5)
# define FCT_PTR_SW_INT_5   [5]=&swInt5,
#else
# define FCT_PTR_SW_INT_5
#endif
#if ICN_NO_NOTIFICATIONS > 6
swInt(6)
# define FCT_PTR_SW_INT_6   [6]=&swInt6,
#else
# define FCT_PTR_SW_INT_6
#endif
#if ICN_NO_NOTIFICATIONS > 7
swInt(7)
# define FCT_PTR_SW_INT_7   [7]=&swInt7,
#else
# define FCT_PTR_SW_INT_7
#endif
#if ICN_NO_NOTIFICATIONS > 8
swInt(8)
# define FCT_PTR_SW_INT_8   [8]=&swInt8,
#else
# define FCT_PTR_SW_INT_8
#endif
#if ICN_NO_NOTIFICATIONS > 9
swInt(9)
# define FCT_PTR_SW_INT_9   [9]=&swInt9,
#else
# define FCT_PTR_SW_INT_9
#endif
#if ICN_NO_NOTIFICATIONS > 10
swInt(10)
# define FCT_PTR_SW_INT_10   [10]=&swInt10,
#else
# define FCT_PTR_SW_INT_10
#endif
#if ICN_NO_NOTIFICATIONS > 11
swInt(11)
# define FCT_PTR_SW_INT_11   [11]=&swInt11,
#else
# define FCT_PTR_SW_INT_11
#endif
#if ICN_NO_NOTIFICATIONS > 12
swInt(12)
# define FCT_PTR_SW_INT_12   [12]=&swInt12,
#else
# define FCT_PTR_SW_INT_12
#endif
#if ICN_NO_NOTIFICATIONS > 13
swInt(13)
# define FCT_PTR_SW_INT_13   [13]=&swInt13,
#else
# define FCT_PTR_SW_INT_13
#endif
#if ICN_NO_NOTIFICATIONS > 14
swInt(14)
# define FCT_PTR_SW_INT_14   [14]=&swInt14,
#else
# define FCT_PTR_SW_INT_14
#endif
#if ICN_NO_NOTIFICATIONS > 15
swInt(15)
# define FCT_PTR_SW_INT_15   [15]=&swInt15,
#else
# define FCT_PTR_SW_INT_15
#endif
#if ICN_NO_NOTIFICATIONS > 16
swInt(16)
# define FCT_PTR_SW_INT_16   [16]=&swInt16,
#else
# define FCT_PTR_SW_INT_16
#endif
#if ICN_NO_NOTIFICATIONS > 17
swInt(17)
# define FCT_PTR_SW_INT_17   [17]=&swInt17,
#else
# define FCT_PTR_SW_INT_17
#endif
#if ICN_NO_NOTIFICATIONS > 18
swInt(18)
# define FCT_PTR_SW_INT_18   [18]=&swInt18,
#else
# define FCT_PTR_SW_INT_18
#endif
#if ICN_NO_NOTIFICATIONS > 19
swInt(19)
# define FCT_PTR_SW_INT_19   [19]=&swInt19,
#else
# define FCT_PTR_SW_INT_19
#endif
#if ICN_NO_NOTIFICATIONS > 20
swInt(20)
# define FCT_PTR_SW_INT_20   [20]=&swInt20,
#else
# define FCT_PTR_SW_INT_20
#endif
#if ICN_NO_NOTIFICATIONS > 21
swInt(21)
# define FCT_PTR_SW_INT_21   [21]=&swInt21,
#else
# define FCT_PTR_SW_INT_21
#endif
#if ICN_NO_NOTIFICATIONS > 22
swInt(22)
# define FCT_PTR_SW_INT_22   [22]=&swInt22,
#else
# define FCT_PTR_SW_INT_22
#endif
#if ICN_NO_NOTIFICATIONS > 23
swInt(23)
# define FCT_PTR_SW_INT_23   [23]=&swInt23,
#else
# define FCT_PTR_SW_INT_23
#endif
#if ICN_NO_NOTIFICATIONS > 24
# error Number of available SW settable interrupts exceeded
#endif


/**
 * Initialize the driver for inter-core notifications on the basis of SW settable
 * interrupts.\n
 *   The function checks the configuration data set and registers the needed interrupts.
 *   @return
 * icn_err_noError, if function succeeded. All notificationa are configured and can be
 * used. Any other return value means a configuration error and the notification service
 * is not available. The SW must not start up.\n
 *   All error conditions are fully static and in no way run-time o data dependent.
 * Consequently, an assertion in DEBUG compilation suffices to catch the errors: If the
 * DEBUG compilation succeeds then the PRODUCTION compilation can't have a problem neither.
 *   @remark
 * This function must be called from the OS context only. Any attempt to use it in user
 * code will lead to a privileged exception.
 *   @remark
 * The function doesn't alter or even take care, whether the global interrupt handling on
 * the calling core or the others is enables. The notifications won't be served as long as
 * interrupt processing is disabled.
 *   @remark
 * In a multi-core implementation, this function is called only once from the boot core and
 * before any other core may make use of the other driver API.
 *   @remark
 * In a multi-core environment, if a core doesn't run safe-RTOS, it may still use this
 * driver in restricted way:\n
 *   - Only the notification by callback must be used if the non-RTOS core is the notified
 *     one
 */
icn_errorCode_t icn_osInitInterCoreNotificationDriver(void)
{
    _Static_assert( SS23_IRQn == SS0_IRQn+23
                  , "Expect all SW settable IRQs to form a gapless sequence"
                  );
    _Static_assert( ICN_FIRST_SW_IRQ_TO_APPLY + ICN_NO_NOTIFICATIONS <= 24
                  , "Bad SW settable interrupts configured"
                  );

    /* An array of function pointers to all SW settable interrupt handlers, which we
       require to implement the notifications. Note, the elements of the initializer
       expression are conditionally defined. Many of them will expand to nothing, resulting
       in a NULL element. */
    void (* const pIsrAry[ICN_NO_NOTIFICATIONS])(void) =
    {
        FCT_PTR_SW_INT_0  FCT_PTR_SW_INT_1  FCT_PTR_SW_INT_2  FCT_PTR_SW_INT_3
        FCT_PTR_SW_INT_4  FCT_PTR_SW_INT_5  FCT_PTR_SW_INT_6  FCT_PTR_SW_INT_7
        FCT_PTR_SW_INT_8  FCT_PTR_SW_INT_9  FCT_PTR_SW_INT_10 FCT_PTR_SW_INT_11
        FCT_PTR_SW_INT_12 FCT_PTR_SW_INT_13 FCT_PTR_SW_INT_14 FCT_PTR_SW_INT_15
        FCT_PTR_SW_INT_16 FCT_PTR_SW_INT_17 FCT_PTR_SW_INT_18 FCT_PTR_SW_INT_19
        FCT_PTR_SW_INT_20 FCT_PTR_SW_INT_21 FCT_PTR_SW_INT_22 FCT_PTR_SW_INT_23
    };

    icn_errorCode_t result = icn_err_noError;

    unsigned int idxN;
    for(idxN=0; idxN<ICN_NO_NOTIFICATIONS; ++idxN)
    {
        const icn_notification_t * const pN = &icn_configuration.notificationAry[idxN];

        /* Check the configuration of the notification. */
        if(pN->osNotificationHandler == NULL  &&  pN->noSentEvents == 0)
        {
            result = icn_err_noActionSpecified;
            continue;
        }
        if(pN->idxNotifiedCore >= RTOS_NO_CORES)
        {
            result = icn_err_badIdxCore;
            continue;
        }
        if(pN->priorityNotificationIrq < 1  ||  pN->priorityNotificationIrq > 15)
        {
            result = icn_err_badPrioIrq;
            continue;
        }
        if(RTOS_RUN_SAFE_RTOS_ON_CORE_0 != 1  &&  pN->idxNotifiedCore == 0
           &&  pN->noSentEvents != 0
           ||  RTOS_RUN_SAFE_RTOS_ON_CORE_1 != 1  &&  pN->idxNotifiedCore == 1
               &&  pN->noSentEvents != 0
           ||  RTOS_RUN_SAFE_RTOS_ON_CORE_2 != 1  &&  pN->idxNotifiedCore == 2
               &&  pN->noSentEvents != 0
          )
        {
            result = icn_err_actionRequiresRTOS;
            continue;
        }

        _notificationParamAry[idxN] = 0u;

        /* The vector number is validated by compile-time expressions, see above. */
        const unsigned int vectorNum = SS0_IRQn + ICN_FIRST_SW_IRQ_TO_APPLY + idxN;
        rtos_osRegisterInterruptHandler( pIsrAry[idxN]
                                       , /* processorId */ pN->idxNotifiedCore
                                       , vectorNum
                                       , pN->priorityNotificationIrq
                                       , /* isPreemptable */ true
                                       );
    }

    return result;

} /* End of icn_osInitInterCoreNotificationDriver */



/**
 * Send a notification to (another) core. The notification is a callback execution on that
 * other core or a sent RTOS event. Moreover, a single 32 Bit value may be passed to
 * the other core without coherency issues.
 *   @return
 * \a true, if function succeeded, else \a false. The operation can fail if the same
 * notification had been sent before and if it had not been received yet by the addressed
 * core (i.e. the notified core has not processed the related SW settable interrupt yet).\n
 *   The acknowledge of a former notification can be polled using
 * icn_osIsNotificationPending(). If that function returns \a false (and if there are no
 * concurrent contexts which make use of this function) then this function will succeed.\n
 *   Caution, the feedback provided by the function relates to the acknowledge of the
 * interrupt on the notified core. \a true means that any earlier asserted interrupt has
 * been serviced on entry into this function so that it can be asserted again. \a false
 * means that an earlier asserted interrupt is still pending. However, even if the
 * interrupt could be processed on the notified core then it is still not guaranteed that
 * the configured action was fully successful: If the action is sending one or more RTOS
 * events then we don't receive any feedback about. Sending an ordinary event can fail on
 * the notified core if one of the tasks associated with the event should not have
 * completed yet (see rtos_osSendEvent()). Sending a countable event can fail on the
 * notified core if the counter variable for the event multiplicity overflows (see
 * rtos_osSendEventCountable()). This failure is reported on the notified core but not seen
 * here on the notifying core.
 *   @param idxNotification
 * The notification to send is chosen by index. It is the same index as used in the
 * configuration of the driver. The permitted range is 0 .. (ICN_NO_NOTIFICATIONS-1).
 *   @param notificationParam
 * Parameter of the notifications:
 * - The notified core will receive this value as function argument of the
 *   callback if a callback is configured.
 * - The notified core will receive this value as parameter of the task function(s) if an
 *   ordinary event is applied to activate one or more tasks.
 * - The event mask if a countable event is applied to activate one or more tasks. (The
 *   notified multiplicity is one per (successful) call of this funtion.) Note, \a
 *   notificationParam must not be zero if this option is configured for the given
 *   notification.
 *   @remark
 * The function barely has parameters. Most of the needed information, like which core to
 * notify or which action to take on the notified core, is static configuration and
 * unchangeably connected with the given notification. See configuration data set \a
 * icn_configuration.
 *   @remark
 * The function implementation has unavoidable race conditions. If one and the same
 * notification is sent from more than one core then the function can't safely decide,
 * whether the notification collides with another one from the other core and sent
 * coincidentally. Neither the function result is reliable in this case nor the propagation
 * of the parameter \a notificationParam.\n
 *   If sending one and the same notification from different cores is a requirement then
 * the caller is in charge to implement the required serialization.
 *   @remark
 * This function can be safely called from all OS contexts. Any attempt to call it from a
 * user task will lead to a privileged exception in the task's process.
 *   @remark
 * If a core doesn't run safe-RTOS it may still make use of this function.
 */
bool icn_osSendNotification(unsigned int idxNotification, uint32_t notificationParam)
{
    assert(idxNotification < ICN_NO_NOTIFICATIONS);

    /* Read notification related software interrupt bit. If it is still set then the
       previous notification has not been received yet and we reject this notification
       demand from the caller. */
    __IO uint8_t *pINTC_SSCIR = (__IO uint8_t*)&INTC->SSCIR[ICN_FIRST_SW_IRQ_TO_APPLY
                                                            + idxNotification
                                                           ];

    /* If another context invokes this function coincidentally then we have a race
       condition from reading the register till having it written. */
    bool success;
    if(*pINTC_SSCIR == 0)
    {
        /* Put the notification argument in the temporary storage. Propagation of the
           parameter value is consistent as long as the documented race conditions
           don't take effect. */
        _notificationParamAry[idxNotification] = notificationParam;

        /* Before we actually notify anyone we need to ensure that the store of the
           parameter has reached the shared RAM. */
        std_fullMemoryBarrier();

        /* Assert the SW settable interrupt, which implements the notification. */
        *pINTC_SSCIR = 2;

        /* Operation successful. */
        success = true;
    }
    else
    {
        /* CLRi is still set, interrupt has not completed yet on other core. We can't
           deliver the new notification yet. */
        success = false;
    }

    return success;

} /* End of icn_osSendNotification */



/**
 * The core, which has sent a notification can poll the information, whether the notified
 * core has already consumed the notification. If this function returns \a false then the
 * same notification can be safely re-sent.\n
 *   If several concurrent contexts want to send one and the same notification then there
 * are race conditions and the result \a false of this function is no longer a guarantee
 * for successful sending of the same notification. See icn_osSendNotification() for more
 * details.
 *   @return
 * \a false, if the addressed core can currently receive the given notification. \a true if
 * a previously sent notification has not yet been consumed by the receiving core.
 *   @param idxNotification
 * The notification the request relates to is chosen by index. It is the same index as used
 * in the configuration of the driver. The permitted range is 0 .. (ICN_NO_NOTIFICATIONS-1).
 *   @remark
 * This function can be safely called from all OS contexts. Any attempt to call it from a
 * user task will lead to a privileged exception in the task's process.
 *   @remark
 * If a core doesn't run safe-RTOS it may still make use of this function.
 */
bool icn_osIsNotificationPending(unsigned int idxNotification)
{
    assert(idxNotification < ICN_NO_NOTIFICATIONS);

    /* Read notification related software interrupt bit. If it is still set then the previous
       notification has not been received yet.
         See RM, 23.6.12 INTC Software Set/Clear Interrupt Register (INTC_SSCIRn) */
    return INTC->SSCIR[ICN_FIRST_SW_IRQ_TO_APPLY+idxNotification] != 0;

} /* End of icn_osIsNotificationPending */

#endif /* ICN_NO_NOTIFICATIONS > 0 */

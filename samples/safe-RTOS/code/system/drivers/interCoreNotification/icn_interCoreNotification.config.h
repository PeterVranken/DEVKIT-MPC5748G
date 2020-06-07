#ifndef ICN_INTERCORENOTIFICATION_CONFIG_INCLUDED
#define ICN_INTERCORENOTIFICATION_CONFIG_INCLUDED
/**
 * @file icn_interCoreNotification.config.h
 * Configuration of driver icn_interCoreNotification.c
 *   @remark
 * The driver configuration strongly depends on the application. Therefore, each
 * application of safe-RTOS will have its own file. This file here is both, a default
 * configuration and a template for a true application dependent configuration. Copy this
 * file, put it into your application and modify it according to your application's needs.
 * Either remove the file here or ensure by include path settings of your compiler that
 * your modified version of the file is used for compilation.
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

//#include "icn_interCoreNotification.h"


/*
 * Defines
 */

/** The number of different kinds of notification. The range is 0 ..
    (24-#ICN_FIRST_SW_IRQ_TO_APPLY) for the MPC5748G. Note, the mechanism is based on the
    INTC's SW settable interrupts. Their number is specific to the derivative of the MCU
    and hence the range depends on the MCU derivative.\n
      Moreover, this driver is not aware of possible other use of SW settable interrupts
    by other driver code. */
#define ICN_NO_NOTIFICATIONS        0

/** The #ICN_NO_NOTIFICATIONS notifications are implemented by the INTC's SW settable
    interrupts #ICN_FIRST_SW_IRQ_TO_APPLY ..
    (#ICN_FIRST_SW_IRQ_TO_APPLY+#ICN_NO_NOTIFICATIONS -1).\n
      This macro is not only meant for avoiding possible conflicts with other I/O drivers
    making use of the SW settable interrupts but can be used to select interrupts of
    suitable priority, too. The higher the index of the SW settable interrupt the lower
    its priority. */
#define ICN_FIRST_SW_IRQ_TO_APPLY   0

/** A notification can mean to trigger a number of RTOS events on the notified core. The
    maximum number of triggered events per notification is specified here. The range is 0
    .. #RTOS_MAX_NO_EVENTS. */
#define ICN_MAX_NO_TRIGGERED_EVENTS 1


/*
 * Local type definitions
 */


/*
 * Global data declarations
 */


/*
 * Local data definitions
 */

#ifdef ICN_IS_INCLUDED_FROM_DRIVER_IMPLEMENTATION
static const icn_configuration_t icn_configuration =
{
    /* The list of actually configured notifications. */
    .notificationAry =
    {
#if 0 /* This is meant sample code only. */

        /* Notification with index 0. */
        [0] =
        {
            /* The notification addresses a particular core. The intention is to address to
               another core but the driver works still fine if the addressed core is the
               notifying core at the same time.
                 The range is 0..2 for the MPC5748G. The upper bounds is the number of
               cores in the MCU. It is dependent on the derivative. */
            .idxNotifiedCore = 0,

            /* The notification happens by interrupt on the notified core. The INTC
               interrupt priority can be chosen individually for each notification. The
               range is 1..15.
                 Note, the safety concept can be broken if the chosen priority is greater
               or equal to the kernel priority, #RTOS_KERNEL_IRQ_PRIORITY_CORE_0 (_1,
               _2).*/
            .priorityNotificationIrq = 1,

            /* The notification can be the invocation of a callback on the notified core.
               If desired, put the pointer to a function void (*)(uintptr_t) and otherwise
               NULL.
                 The passed function argument is the notification parameter, see
               icn_osSendNotification().
                 Note, the execution of a callback on the other core can easily break the
               safety concept. The callback fully belongs into the sphere of trusted code.
               However, its implementation can safely call untrusted code by applying the
               according services of safe-RTOS. */
            .osNotificationHandler = NULL,
            

            /* The notification can be the triggering of one or more safe-RTOS events in
               order to activate associated tasks. Here, we have the number of events to
               trigger. The range is 0 .. #ICN_MAX_NO_TRIGGERED_EVENTS. */
            .noTriggeredEvents = 0,

            /* Here, we have an array of #ICN_MAX_NO_TRIGGERED_EVENTS possibly triggered
               events. The first #ICN_MAX_NO_TRIGGERED_EVENTS elements of the array refer
               to actually triggered events and they hold an event ID each (see
               rtos_osCreateEvent()). The other elements of the array don't care.
                 All tasks, which are activated because of one of the triggered events,
               will receive the notification parameter (see icn_osSendNotification()) as task
               parameter. */
            .eventIdAry = 
            {
                [/* Event */ 0] = 0,
                [/* Event */ 1] = 2,

            }, /* End of list of triggered events. */

        }, /* End of notification with index 0. */
        
#endif /* End of sample configuration code. */

    }, /* End of .notificationAry */
};
#endif


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


#endif  /* ICN_INTERCORENOTIFICATION_CONFIG_INCLUDED */

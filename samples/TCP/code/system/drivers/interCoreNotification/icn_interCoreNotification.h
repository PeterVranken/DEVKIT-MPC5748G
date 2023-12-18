#ifndef ICN_INTERCORENOTIFICATION_INCLUDED
#define ICN_INTERCORENOTIFICATION_INCLUDED
/**
 * @file icn_interCoreNotification.h
 * Definition of global interface of module icn_interCoreNotification.c
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


/*
 * Defines
 */


/*
 * Global type definitions
 */

/** The enumeration of possible configuration error, which can be reported by the
    initialization routine of the driver. */
typedef enum icn_errorCode_t
{
    icn_err_noError = 0,        /** Success, no error. */
    icn_err_noActionSpecified,  /** No action to be taken when notified. */
    icn_err_badActionSpecified, /** RTOS event specified for non RTOS core. */
    icn_err_badIdxCore,         /** Notification of non existing core.*/
    icn_err_badPrioIrq,         /** Priority of IRQ out of range of INTC. */
    
} icn_errorCode_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialize the driver for inter-core notifictaions. */
icn_errorCode_t icn_osInitInterCoreNotificationDriver(void);

/** Send a notification to (another) core. */
bool icn_osSendNotification(unsigned int idxNotification, uintptr_t notificationParam);

/** Poll, whether the notified core has already consumed the notification. */
bool icn_osIsNotificationPending(unsigned int idxNotification);


/*
 * Global inline functions
 */


#endif  /* ICN_INTERCORENOTIFICATION_INCLUDED */

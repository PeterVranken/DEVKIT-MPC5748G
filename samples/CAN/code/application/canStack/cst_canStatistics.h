#ifndef CST_CANSTATISTICS_DEFINED
#define CST_CANSTATISTICS_DEFINED
/**
 * @file cst_canStatistics.h
 * Some useful statistics about the CAN messages of cluster DEVKIT-MPC5775G.
 *
 * This file has been created with comFramework - codeGenerator version 1.11.3,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/** The number of CAN buses in the cluster. */
#define CST_NO_CAN_BUSES 2

/** The total number of affected CAN messages in the cluster, i.e. either sent or received. */
#define CST_NO_CAN_MSGS (CST_NO_CAN_MSGS_PWM + CST_NO_CAN_MSGS_PT)

/** The number of sent CAN messages in the cluster. */
#define CST_NO_CAN_MSGS_SENT (CST_NO_CAN_MSGS_SENT_PWM + CST_NO_CAN_MSGS_SENT_PT)

/** The number of received CAN messages in the cluster. */
#define CST_NO_CAN_MSGS_RECEIVED (CST_NO_CAN_MSGS_RECEIVED_PWM + CST_NO_CAN_MSGS_RECEIVED_PT)

/** The number of received regular CAN messages in the cluster. */
#define CST_NO_CAN_MSGS_RECEIVED_REGULAR (CST_NO_CAN_MSGS_RECEIVED_REGULAR_PWM + \
    CST_NO_CAN_MSGS_RECEIVED_REGULAR_PT)

/** The number of received event CAN messages in the cluster. */
#define CST_NO_CAN_MSGS_RECEIVED_EVENT (CST_NO_CAN_MSGS_RECEIVED_EVENT_PWM + \
    CST_NO_CAN_MSGS_RECEIVED_EVENT_PT)

/** The number of received mixed mode CAN messages in the cluster. */
#define CST_NO_CAN_MSGS_RECEIVED_MIXED (CST_NO_CAN_MSGS_RECEIVED_MIXED_PWM + \
    CST_NO_CAN_MSGS_RECEIVED_MIXED_PT)

/** The number of sent regular CAN messages in the cluster. */
#define CST_NO_CAN_MSGS_SENT_REGULAR (CST_NO_CAN_MSGS_SENT_REGULAR_PWM + \
    CST_NO_CAN_MSGS_SENT_REGULAR_PT)

/** The number of sent event CAN messages in the cluster. */
#define CST_NO_CAN_MSGS_SENT_EVENT (CST_NO_CAN_MSGS_SENT_EVENT_PWM + CST_NO_CAN_MSGS_SENT_EVENT_PT)

/** The number of sent mixed mode CAN messages in the cluster. */
#define CST_NO_CAN_MSGS_SENT_MIXED (CST_NO_CAN_MSGS_SENT_MIXED_PWM + CST_NO_CAN_MSGS_SENT_MIXED_PT)


/** The total number of affected CAN messages in bus PWM, i.e. either sent or received. */
#define CST_NO_CAN_MSGS_PWM 2u

/** The number of sent CAN messages in bus PWM. */
#define CST_NO_CAN_MSGS_SENT_PWM 1u

/** The number of received CAN messages in bus PWM. */
#define CST_NO_CAN_MSGS_RECEIVED_PWM 1u

/** The number of received regular CAN messages in bus PWM. */
#define CST_NO_CAN_MSGS_RECEIVED_REGULAR_PWM 0u

/** The number of received event CAN messages in bus PWM. */
#define CST_NO_CAN_MSGS_RECEIVED_EVENT_PWM 1u

/** The number of received mixed mode CAN messages in bus PWM. */
#define CST_NO_CAN_MSGS_RECEIVED_MIXED_PWM 0u

/** The number of sent regular CAN messages in bus PWM. */
#define CST_NO_CAN_MSGS_SENT_REGULAR_PWM 1u

/** The number of sent event CAN messages in bus PWM. */
#define CST_NO_CAN_MSGS_SENT_EVENT_PWM 0u

/** The number of sent mixed mode CAN messages in bus PWM. */
#define CST_NO_CAN_MSGS_SENT_MIXED_PWM 0u


/** The total number of affected CAN messages in bus PT, i.e. either sent or received. */
#define CST_NO_CAN_MSGS_PT 6u

/** The number of sent CAN messages in bus PT. */
#define CST_NO_CAN_MSGS_SENT_PT 3u

/** The number of received CAN messages in bus PT. */
#define CST_NO_CAN_MSGS_RECEIVED_PT 3u

/** The number of received regular CAN messages in bus PT. */
#define CST_NO_CAN_MSGS_RECEIVED_REGULAR_PT 2u

/** The number of received event CAN messages in bus PT. */
#define CST_NO_CAN_MSGS_RECEIVED_EVENT_PT 1u

/** The number of received mixed mode CAN messages in bus PT. */
#define CST_NO_CAN_MSGS_RECEIVED_MIXED_PT 0u

/** The number of sent regular CAN messages in bus PT. */
#define CST_NO_CAN_MSGS_SENT_REGULAR_PT 1u

/** The number of sent event CAN messages in bus PT. */
#define CST_NO_CAN_MSGS_SENT_EVENT_PT 1u

/** The number of sent mixed mode CAN messages in bus PT. */
#define CST_NO_CAN_MSGS_SENT_MIXED_PT 1u


/** We have a global array of all sent and received signals, cde_canSignalAry, which is not
    structured according to buses and messages. Here's the count of all contained signals. */
#define CST_NO_SENT_AND_RECEIVED_CAN_SIGNALS 43u


/*
 * Type definitions
 */


/*
 * Data declarations
 */


/*
 * Function declarations
 */


/*
 * Inline function definitions
 */

#endif // !defined(CST_CANSTATISTICS_DEFINED)
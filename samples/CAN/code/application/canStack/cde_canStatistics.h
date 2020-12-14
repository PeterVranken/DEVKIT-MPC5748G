#ifndef CDE_CANSTATISTICS_DEFINED
#define CDE_CANSTATISTICS_DEFINED
/**
 * @file cde_canStatistics.h
 * Some useful statistics about the CAN frames of cluster DEVKIT-MPC5775G.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.4,
 * see http://sourceforge.net/projects/comframe/
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

/** The number of CAN buses in the cluster. */
#define CDE_NO_CAN_BUSES 1

/** The total number of affected CAN frames in the cluster, i.e. either sent or received. */
#define CDE_NO_CAN_FRAMES (CDE_NO_CAN_FRAMES_PT)

/** The number of sent CAN frames in the cluster. */
#define CDE_NO_CAN_FRAMES_SENT (CDE_NO_CAN_FRAMES_SENT_PT)

/** The number of received CAN frames in the cluster. */
#define CDE_NO_CAN_FRAMES_RECEIVED (CDE_NO_CAN_FRAMES_RECEIVED_PT)

/** The number of received regular CAN frames in the cluster. */
#define CDE_NO_CAN_FRAMES_RECEIVED_REGULAR (CDE_NO_CAN_FRAMES_RECEIVED_REGULAR_PT)

/** The number of received event CAN frames in the cluster. */
#define CDE_NO_CAN_FRAMES_RECEIVED_EVENT (CDE_NO_CAN_FRAMES_RECEIVED_EVENT_PT)

/** The number of received mixed mode CAN frames in the cluster. */
#define CDE_NO_CAN_FRAMES_RECEIVED_MIXED (CDE_NO_CAN_FRAMES_RECEIVED_MIXED_PT)

/** The number of sent regular CAN frames in the cluster. */
#define CDE_NO_CAN_FRAMES_SENT_REGULAR (CDE_NO_CAN_FRAMES_SENT_REGULAR_PT)

/** The number of sent event CAN frames in the cluster. */
#define CDE_NO_CAN_FRAMES_SENT_EVENT (CDE_NO_CAN_FRAMES_SENT_EVENT_PT)

/** The number of sent mixed mode CAN frames in the cluster. */
#define CDE_NO_CAN_FRAMES_SENT_MIXED (CDE_NO_CAN_FRAMES_SENT_MIXED_PT)


/** The total number of affected CAN frames in bus PT, i.e. either sent or received. */
#define CDE_NO_CAN_FRAMES_PT 6u

/** The number of sent CAN frames in bus PT. */
#define CDE_NO_CAN_FRAMES_SENT_PT 3u

/** The number of received CAN frames in bus PT. */
#define CDE_NO_CAN_FRAMES_RECEIVED_PT 3u

/** The number of received regular CAN frames in bus PT. */
#define CDE_NO_CAN_FRAMES_RECEIVED_REGULAR_PT 2u

/** The number of received event CAN frames in bus PT. */
#define CDE_NO_CAN_FRAMES_RECEIVED_EVENT_PT 1u

/** The number of received mixed mode CAN frames in bus PT. */
#define CDE_NO_CAN_FRAMES_RECEIVED_MIXED_PT 0u

/** The number of sent regular CAN frames in bus PT. */
#define CDE_NO_CAN_FRAMES_SENT_REGULAR_PT 1u

/** The number of sent event CAN frames in bus PT. */
#define CDE_NO_CAN_FRAMES_SENT_EVENT_PT 1u

/** The number of sent mixed mode CAN frames in bus PT. */
#define CDE_NO_CAN_FRAMES_SENT_MIXED_PT 1u




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

#endif // !defined(CDE_CANSTATISTICS_DEFINED)
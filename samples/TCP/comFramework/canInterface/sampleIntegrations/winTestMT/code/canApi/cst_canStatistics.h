#ifndef CST_CANSTATISTICS_DEFINED
#define CST_CANSTATISTICS_DEFINED
/**
 * @file cst_canStatistics.h
 * Some useful statistics about the CAN frames of cluster canInterfaceMTTest.
 *
 * This file has been created with comFramework - codeGenerator version 1.11.2,
 * see http://sourceforge.net/projects/comframe/
 *
 * Copyright (C) 2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "types.h"


/*
 * Defines
 */

/** The number of CAN buses in the cluster. */
#define CST_NO_CAN_BUSES 10

/** The total number of affected CAN frames in the cluster, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES (CST_NO_CAN_FRAMES_B1 + CST_NO_CAN_FRAMES_B2 + \
    CST_NO_CAN_FRAMES_B3 + CST_NO_CAN_FRAMES_B4 + CST_NO_CAN_FRAMES_B5 + \
    CST_NO_CAN_FRAMES_B6 + CST_NO_CAN_FRAMES_B7 + CST_NO_CAN_FRAMES_B8 + \
    CST_NO_CAN_FRAMES_B9 + CST_NO_CAN_FRAMES_B10)

/** The number of sent CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_SENT (CST_NO_CAN_FRAMES_SENT_B1 + CST_NO_CAN_FRAMES_SENT_B2 + \
    CST_NO_CAN_FRAMES_SENT_B3 + CST_NO_CAN_FRAMES_SENT_B4 + CST_NO_CAN_FRAMES_SENT_B5 + \
    CST_NO_CAN_FRAMES_SENT_B6 + CST_NO_CAN_FRAMES_SENT_B7 + CST_NO_CAN_FRAMES_SENT_B8 + \
    CST_NO_CAN_FRAMES_SENT_B9 + CST_NO_CAN_FRAMES_SENT_B10)

/** The number of received CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_RECEIVED (CST_NO_CAN_FRAMES_RECEIVED_B1 + CST_NO_CAN_FRAMES_RECEIVED_B2 + \
    CST_NO_CAN_FRAMES_RECEIVED_B3 + CST_NO_CAN_FRAMES_RECEIVED_B4 + CST_NO_CAN_FRAMES_RECEIVED_B5 + \
    CST_NO_CAN_FRAMES_RECEIVED_B6 + CST_NO_CAN_FRAMES_RECEIVED_B7 + CST_NO_CAN_FRAMES_RECEIVED_B8 + \
    CST_NO_CAN_FRAMES_RECEIVED_B9 + CST_NO_CAN_FRAMES_RECEIVED_B10)

/** The number of received regular CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR (CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B1 + \
    CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B2 + CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B3 + \
    CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B4 + CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B5 + \
    CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B6 + CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B7 + \
    CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B8 + CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B9 + \
    CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B10)

/** The number of received event CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT (CST_NO_CAN_FRAMES_RECEIVED_EVENT_B1 + \
    CST_NO_CAN_FRAMES_RECEIVED_EVENT_B2 + CST_NO_CAN_FRAMES_RECEIVED_EVENT_B3 + \
    CST_NO_CAN_FRAMES_RECEIVED_EVENT_B4 + CST_NO_CAN_FRAMES_RECEIVED_EVENT_B5 + \
    CST_NO_CAN_FRAMES_RECEIVED_EVENT_B6 + CST_NO_CAN_FRAMES_RECEIVED_EVENT_B7 + \
    CST_NO_CAN_FRAMES_RECEIVED_EVENT_B8 + CST_NO_CAN_FRAMES_RECEIVED_EVENT_B9 + \
    CST_NO_CAN_FRAMES_RECEIVED_EVENT_B10)

/** The number of received mixed mode CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED (CST_NO_CAN_FRAMES_RECEIVED_MIXED_B1 + \
    CST_NO_CAN_FRAMES_RECEIVED_MIXED_B2 + CST_NO_CAN_FRAMES_RECEIVED_MIXED_B3 + \
    CST_NO_CAN_FRAMES_RECEIVED_MIXED_B4 + CST_NO_CAN_FRAMES_RECEIVED_MIXED_B5 + \
    CST_NO_CAN_FRAMES_RECEIVED_MIXED_B6 + CST_NO_CAN_FRAMES_RECEIVED_MIXED_B7 + \
    CST_NO_CAN_FRAMES_RECEIVED_MIXED_B8 + CST_NO_CAN_FRAMES_RECEIVED_MIXED_B9 + \
    CST_NO_CAN_FRAMES_RECEIVED_MIXED_B10)

/** The number of sent regular CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR (CST_NO_CAN_FRAMES_SENT_REGULAR_B1 + \
    CST_NO_CAN_FRAMES_SENT_REGULAR_B2 + CST_NO_CAN_FRAMES_SENT_REGULAR_B3 + \
    CST_NO_CAN_FRAMES_SENT_REGULAR_B4 + CST_NO_CAN_FRAMES_SENT_REGULAR_B5 + \
    CST_NO_CAN_FRAMES_SENT_REGULAR_B6 + CST_NO_CAN_FRAMES_SENT_REGULAR_B7 + \
    CST_NO_CAN_FRAMES_SENT_REGULAR_B8 + CST_NO_CAN_FRAMES_SENT_REGULAR_B9 + \
    CST_NO_CAN_FRAMES_SENT_REGULAR_B10)

/** The number of sent event CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_SENT_EVENT (CST_NO_CAN_FRAMES_SENT_EVENT_B1 + \
    CST_NO_CAN_FRAMES_SENT_EVENT_B2 + CST_NO_CAN_FRAMES_SENT_EVENT_B3 + \
    CST_NO_CAN_FRAMES_SENT_EVENT_B4 + CST_NO_CAN_FRAMES_SENT_EVENT_B5 + \
    CST_NO_CAN_FRAMES_SENT_EVENT_B6 + CST_NO_CAN_FRAMES_SENT_EVENT_B7 + \
    CST_NO_CAN_FRAMES_SENT_EVENT_B8 + CST_NO_CAN_FRAMES_SENT_EVENT_B9 + \
    CST_NO_CAN_FRAMES_SENT_EVENT_B10)

/** The number of sent mixed mode CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_SENT_MIXED (CST_NO_CAN_FRAMES_SENT_MIXED_B1 + \
    CST_NO_CAN_FRAMES_SENT_MIXED_B2 + CST_NO_CAN_FRAMES_SENT_MIXED_B3 + \
    CST_NO_CAN_FRAMES_SENT_MIXED_B4 + CST_NO_CAN_FRAMES_SENT_MIXED_B5 + \
    CST_NO_CAN_FRAMES_SENT_MIXED_B6 + CST_NO_CAN_FRAMES_SENT_MIXED_B7 + \
    CST_NO_CAN_FRAMES_SENT_MIXED_B8 + CST_NO_CAN_FRAMES_SENT_MIXED_B9 + \
    CST_NO_CAN_FRAMES_SENT_MIXED_B10)


/** The total number of affected CAN frames in bus B1, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B1 80u

/** The number of sent CAN frames in bus B1. */
#define CST_NO_CAN_FRAMES_SENT_B1 33u

/** The number of received CAN frames in bus B1. */
#define CST_NO_CAN_FRAMES_RECEIVED_B1 47u

/** The number of received regular CAN frames in bus B1. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B1 34u

/** The number of received event CAN frames in bus B1. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B1 1u

/** The number of received mixed mode CAN frames in bus B1. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B1 12u

/** The number of sent regular CAN frames in bus B1. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B1 25u

/** The number of sent event CAN frames in bus B1. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B1 0u

/** The number of sent mixed mode CAN frames in bus B1. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B1 8u


/** The total number of affected CAN frames in bus B2, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B2 77u

/** The number of sent CAN frames in bus B2. */
#define CST_NO_CAN_FRAMES_SENT_B2 24u

/** The number of received CAN frames in bus B2. */
#define CST_NO_CAN_FRAMES_RECEIVED_B2 53u

/** The number of received regular CAN frames in bus B2. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B2 37u

/** The number of received event CAN frames in bus B2. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B2 0u

/** The number of received mixed mode CAN frames in bus B2. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B2 16u

/** The number of sent regular CAN frames in bus B2. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B2 18u

/** The number of sent event CAN frames in bus B2. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B2 0u

/** The number of sent mixed mode CAN frames in bus B2. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B2 6u


/** The total number of affected CAN frames in bus B3, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B3 64u

/** The number of sent CAN frames in bus B3. */
#define CST_NO_CAN_FRAMES_SENT_B3 19u

/** The number of received CAN frames in bus B3. */
#define CST_NO_CAN_FRAMES_RECEIVED_B3 45u

/** The number of received regular CAN frames in bus B3. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B3 30u

/** The number of received event CAN frames in bus B3. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B3 2u

/** The number of received mixed mode CAN frames in bus B3. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B3 13u

/** The number of sent regular CAN frames in bus B3. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B3 15u

/** The number of sent event CAN frames in bus B3. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B3 0u

/** The number of sent mixed mode CAN frames in bus B3. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B3 4u


/** The total number of affected CAN frames in bus B4, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B4 56u

/** The number of sent CAN frames in bus B4. */
#define CST_NO_CAN_FRAMES_SENT_B4 18u

/** The number of received CAN frames in bus B4. */
#define CST_NO_CAN_FRAMES_RECEIVED_B4 38u

/** The number of received regular CAN frames in bus B4. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B4 28u

/** The number of received event CAN frames in bus B4. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B4 0u

/** The number of received mixed mode CAN frames in bus B4. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B4 10u

/** The number of sent regular CAN frames in bus B4. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B4 16u

/** The number of sent event CAN frames in bus B4. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B4 0u

/** The number of sent mixed mode CAN frames in bus B4. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B4 2u


/** The total number of affected CAN frames in bus B5, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B5 57u

/** The number of sent CAN frames in bus B5. */
#define CST_NO_CAN_FRAMES_SENT_B5 14u

/** The number of received CAN frames in bus B5. */
#define CST_NO_CAN_FRAMES_RECEIVED_B5 43u

/** The number of received regular CAN frames in bus B5. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B5 27u

/** The number of received event CAN frames in bus B5. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B5 2u

/** The number of received mixed mode CAN frames in bus B5. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B5 14u

/** The number of sent regular CAN frames in bus B5. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B5 10u

/** The number of sent event CAN frames in bus B5. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B5 0u

/** The number of sent mixed mode CAN frames in bus B5. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B5 4u


/** The total number of affected CAN frames in bus B6, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B6 95u

/** The number of sent CAN frames in bus B6. */
#define CST_NO_CAN_FRAMES_SENT_B6 31u

/** The number of received CAN frames in bus B6. */
#define CST_NO_CAN_FRAMES_RECEIVED_B6 64u

/** The number of received regular CAN frames in bus B6. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B6 45u

/** The number of received event CAN frames in bus B6. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B6 3u

/** The number of received mixed mode CAN frames in bus B6. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B6 16u

/** The number of sent regular CAN frames in bus B6. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B6 25u

/** The number of sent event CAN frames in bus B6. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B6 0u

/** The number of sent mixed mode CAN frames in bus B6. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B6 6u


/** The total number of affected CAN frames in bus B7, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B7 96u

/** The number of sent CAN frames in bus B7. */
#define CST_NO_CAN_FRAMES_SENT_B7 26u

/** The number of received CAN frames in bus B7. */
#define CST_NO_CAN_FRAMES_RECEIVED_B7 70u

/** The number of received regular CAN frames in bus B7. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B7 45u

/** The number of received event CAN frames in bus B7. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B7 0u

/** The number of received mixed mode CAN frames in bus B7. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B7 25u

/** The number of sent regular CAN frames in bus B7. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B7 11u

/** The number of sent event CAN frames in bus B7. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B7 1u

/** The number of sent mixed mode CAN frames in bus B7. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B7 14u


/** The total number of affected CAN frames in bus B8, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B8 79u

/** The number of sent CAN frames in bus B8. */
#define CST_NO_CAN_FRAMES_SENT_B8 25u

/** The number of received CAN frames in bus B8. */
#define CST_NO_CAN_FRAMES_RECEIVED_B8 54u

/** The number of received regular CAN frames in bus B8. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B8 36u

/** The number of received event CAN frames in bus B8. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B8 2u

/** The number of received mixed mode CAN frames in bus B8. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B8 16u

/** The number of sent regular CAN frames in bus B8. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B8 20u

/** The number of sent event CAN frames in bus B8. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B8 2u

/** The number of sent mixed mode CAN frames in bus B8. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B8 3u


/** The total number of affected CAN frames in bus B9, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B9 75u

/** The number of sent CAN frames in bus B9. */
#define CST_NO_CAN_FRAMES_SENT_B9 34u

/** The number of received CAN frames in bus B9. */
#define CST_NO_CAN_FRAMES_RECEIVED_B9 41u

/** The number of received regular CAN frames in bus B9. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B9 30u

/** The number of received event CAN frames in bus B9. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B9 0u

/** The number of received mixed mode CAN frames in bus B9. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B9 11u

/** The number of sent regular CAN frames in bus B9. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B9 21u

/** The number of sent event CAN frames in bus B9. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B9 0u

/** The number of sent mixed mode CAN frames in bus B9. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B9 13u


/** The total number of affected CAN frames in bus B10, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_B10 58u

/** The number of sent CAN frames in bus B10. */
#define CST_NO_CAN_FRAMES_SENT_B10 18u

/** The number of received CAN frames in bus B10. */
#define CST_NO_CAN_FRAMES_RECEIVED_B10 40u

/** The number of received regular CAN frames in bus B10. */
#define CST_NO_CAN_FRAMES_RECEIVED_REGULAR_B10 29u

/** The number of received event CAN frames in bus B10. */
#define CST_NO_CAN_FRAMES_RECEIVED_EVENT_B10 1u

/** The number of received mixed mode CAN frames in bus B10. */
#define CST_NO_CAN_FRAMES_RECEIVED_MIXED_B10 10u

/** The number of sent regular CAN frames in bus B10. */
#define CST_NO_CAN_FRAMES_SENT_REGULAR_B10 17u

/** The number of sent event CAN frames in bus B10. */
#define CST_NO_CAN_FRAMES_SENT_EVENT_B10 0u

/** The number of sent mixed mode CAN frames in bus B10. */
#define CST_NO_CAN_FRAMES_SENT_MIXED_B10 1u




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
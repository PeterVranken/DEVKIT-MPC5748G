#ifndef CST_CANSTATISTICS_DEFINED
#define CST_CANSTATISTICS_DEFINED
/**
 * @file cst_canStatistics.h
 * Some useful statistics about the CAN frames of cluster arduinoSampleIntegrationEC.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.6,
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

/** The total number of affected CAN frames in the cluster, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES (CST_NO_CAN_FRAMES_PT)

/** The number of sent CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_SENT (CST_NO_CAN_FRAMES_SENT_PT)

/** The number of received CAN frames in the cluster. */
#define CST_NO_CAN_FRAMES_RECEIVED (CST_NO_CAN_FRAMES_RECEIVED_PT)

/** The total number of affected CAN frames in bus PT, i.e. either sent or received. */
#define CST_NO_CAN_FRAMES_PT 6

/** The number of sent CAN frames in bus PT. */
#define CST_NO_CAN_FRAMES_SENT_PT 3

/** The number of received CAN frames in bus PT. */
#define CST_NO_CAN_FRAMES_RECEIVED_PT 3

 

/*
 * Type definitions
 */

 

/*
 * Data declarations
 */

 

/*
 * Function declarations
 */

#endif // !defined(CST_CANSTATISTICS_DEFINED)
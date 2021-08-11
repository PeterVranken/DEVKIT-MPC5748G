#ifndef CDE_CANDRIVER_CONFIG_MCUDERIVATIVE_INCLUDED
#define CDE_CANDRIVER_CONFIG_MCUDERIVATIVE_INCLUDED
/**
 * @file cde_canDriver.config.MCUDerivative.h
 * The CAN driver can be compiled for different derivatives from the NXP MPC57xx family.\n
 *   This file aims at selecting one of the supported MCUs. An according define is set and
 * the related NXP device haeder is included based on the made setting. All other files
 * from the driver implementation will include this header rather than directly an
 * original NXP header.
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



/*
 * Defines
 */

/** Select the MCU derivative, the CAN driver is compiled for. Supported are:\n
      - MCU_MPC5748G\n
      - MCU_MPC5775B\n
      - MCU_MPC5775E */
#define MCU_MPC5748G


/** All supported MCUs specify the size of the mailbox RAM as 384 32 Bit words in the
    specific derivative header files (see CAN_RAMn_COUNT), although this size fits only
    to the 96 mailboxes of the MPC5748G. (RM75, 37.1.1 FlexCAN RAM, p.1667, even says it
    were 6 kByte.) Actually, the MPC5775B/E have only 256 words of
    RAM and an attempt to access RAM beyond the 1 kByte is punished with a machine check
    exception.\n
      We provide an additional macro rather than fixing the wrong header. It despigantes
    the number of physically available 32 Bit RAM words. */
#if defined(MCU_MPC5748G)
# define CAN_PHYSICAL_RAMn_COUNT    (CAN_RAMn_COUNT)
#elif defined(MCU_MPC5775B) || defined(MCU_MPC5775E)
# define CAN_PHYSICAL_RAMn_COUNT    (256u)
#endif    


/*
 * Include NXP derivative headers
 */

#if defined(MCU_MPC5748G)
# include "MPC5748G.h"
#elif defined(MCU_MPC5775B)
# include "MPC5775B.h"
#elif defined(MCU_MPC5775E)
# include "MPC5775E.h"
#else
# error Bad choice of MCU derivative. Selected device is not supported by the implementation
#endif

#include "cdr_MPC5748G_CAN.h" /* Despite of the name, this file fits for all supported MCUs. */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


#endif  /* CDE_CANDRIVER_CONFIG_MCUDERIVATIVE_INCLUDED */

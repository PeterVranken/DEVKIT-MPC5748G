#ifndef BSW_TASKETHERNET_INCLUDED
#define BSW_TASKETHERNET_INCLUDED
/**
 * @file bsw_taskEthernet.h
 * Definition of global interface of module bsw_taskEthernet.c
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

/** This is an RTOS event, which can be used to activate the Internet protocol, e.g., task
    after reception or transmission of a an IP frame. */
#define BSW_ID_EV_TRIG_INTERNET_PROTOCOL_TASK   (4u)



/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Ethernet frame Rx notification. */
void bsw_ethFrameRxCallback(uint32_t EIR);

/** Ethernet buffer Tx notification. */
void bsw_ethFrameTxCallback(uint32_t EIR);

/** Task function of the Ethernet task. */
int32_t bsw_taskEthernetInternal(uint32_t, uint32_t taskParam);

/*
 * Global inline functions
 */

/**
 * Get the current system time of the lwIP stack. It is the time, which has elapsed for the
 * IP protocol task since system startup. Note, the time wraps at its implementation
 * maximum, which is after 2^32 ms (about 50 days) of continuous operation.
 *   @return 
 * Get the system time in Milliseconds.
 *   @remark 
 * This API may be called at any time from any context running on the core, which executes
 * the IP protocol task.
 */
static inline uint32_t bsw_getLwIPTime(void)
{
    extern volatile uint32_t bsw_tiLwIP;
    return bsw_tiLwIP;
}


#endif  /* BSW_TASKETHERNET_INCLUDED */

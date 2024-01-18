#ifndef M4B_MAINZ4B_INCLUDED
#define M4B_MAINZ4B_INCLUDED
/**
 * @file m4b_mainZ4B.h
 * Definition of global interface of module m4b_mainZ4B.c
 *
 * Copyright (C) 2018-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/** This is the RTOS event processor on core Z4B that is triggered from the other core Z2
    using the inter-core notification driver. The notification task on the Z4B, which is
    associated with this event processor is activated by the Z2 core. */
#define M4B_ID_EV_PROC_NOTIFICATION_FROM_Z2     1u

/** This is the RTOS event on core Z4B that is triggered from the other core Z2 using the
    inter-core notification driver. The notification task on the Z4B, which is associated
    with this event processor is activated by the Z2A core. */
#define M4B_ID_EV_PROC_NOTIFICATION_FROM_Z4A    2u

/** This is the bit mask for the occurrence counter of the countable event, which is sent
    from core Z4A to core Z4B. We can afford to use all bits, as we have only a single
    countable event going this path. It is for sure that we will never ever see a counter
    overflow and thus an activation loss. */
#define M2B_EV_MASK_NOTIFICATION_FROM_Z4A       0xFFFFFFFFu

/** This is the position of the bits of the occurrence counter of the countable event in bit
    mask #M2B_EV_MASK_NOTIFICATION_FROM_Z4A. */
#define M2B_EV_SHFT_NOTIFICATION_FROM_Z4A       0u

/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** Counter of notificastion task, activated by other core Z2 using the inter-core
    notification driver. */
extern volatile unsigned long m4b_cntTaskNotificationFromZ2;
   
/** Counter of notification task activations, triggered by other core Z4A using the
    inter-core notification driver. */
extern volatile unsigned long m4b_cntTaskNotificationFromZ4A;

/** Counter of notifications received from other core Z4A using the inter-core notification
    driver. Note that this is not necessarily identical to the number of task activations. */
extern volatile unsigned long m4b_cntNotificationsFromZ4A;

/** Counter of cyclic 1ms user task. */
extern volatile unsigned long m4b_cntTask1ms;  

/** Counter of cyclic 1ms OS task. */
extern volatile unsigned long m4b_cntTaskOs1ms;

/** Counter of cycles of infinite main loop. */
extern volatile unsigned long m4b_cntTaskIdle;

/** Total counter of task failures in P1 on second core. */
extern volatile unsigned int m4b_cntTaskFailuresP1;

/** Activation loss counter for process 1 on the second core. */
extern volatile unsigned int m4b_cntActivationLossFailures;

/** Stack reserve of process p1 on the second core. */
extern volatile unsigned int m4b_stackReserveP1;

/** Stack reserve of kernel process on the second core. */
extern volatile unsigned int m4b_stackReserveOS;

/** The average CPU load produced by all tasks and interrupts on core Z4B in tens of
    percent. */ 
extern volatile unsigned int m4b_cpuLoadZ4B;


/*
 * Global prototypes
 */

/** Test function: error injection. */
void m4b_injectError(unsigned int * const pIdxErr);

/** Callback for LED and button I/O driver. */
int32_t m4b_onButtonChangeCallback(uint32_t PID ATTRIB_UNUSED, uint8_t buttonState);

/** Main entry point of code execution for core Z4B. */
void /* _Noreturn */ m4b_mainZ4B(int noArgs, const char *argAry[]);

#endif  /* M4B_MAINZ4B_INCLUDED */

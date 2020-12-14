#ifndef BSW_BASICSOFTWARE_INCLUDED
#define BSW_BASICSOFTWARE_INCLUDED
/**
 * @file bsw_basicSoftware.h
 * Definition of global interface of module bsw_basicSoftware.c
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

/** The process initialization tasks, which are provided by the application code, must not
    execute longer than this time budget. Otherwise the system won't start up. */
#define BSW_TI_INIT_TASK_MAX_IN_US          5000

/** CAN interface: The BSW uses index spaces for the mailboxes, which are offered to
    user the processes. Rx and Tx messages each have an own solid index space, which is not
    zero based. The first and last available index are provided. */
#define BSW_IDX_FIRST_RX_MAILBOX            0u
#define BSW_IDX_LAST_RX_MAILBOX             71u
#define BSW_IDX_FIRST_TX_MAILBOX            82u
#define BSW_IDX_LAST_TX_MAILBOX             143u

/** A few mailboxes are reserverd for use by the safety supervision process. The Rx
    mailboxes can be used by polling only (which is a typical safety requirement). */
#define BSW_IDX_FIRST_RX_MAILBOX_SAFETY     72u
#define BSW_IDX_LAST_RX_MAILBOX_SAFETY      77u
#define BSW_IDX_FIRST_TX_MAILBOX_SAFETY     78u
#define BSW_IDX_LAST_TX_MAILBOX_SAFETY      81u

/*
 * Global type definitions
 */

/** The IDs of the processes, which can be used by the application. */
typedef enum bsw_pid_t
{
    bsw_pidUser = 1,    /** Intented for user code and C libraries. */
    bsw_pidSafety = 2,  /** Intented for safety assured supervisory code. */

} bsw_pid_t;


/** CAN interface: The notification of a received message as used in bsw_onRxCan(). */
typedef struct bsw_rxCanMessage_t
{
    /** The index of the mailbox, which had received the message. It is in the range
        #BSW_IDX_FIRST_RX_MAILBOX till and including #BSW_IDX_LAST_RX_MAILBOX. */
    unsigned int idxMailbox;

    /** The up to eight received message payload bytes by reference. The exposed data is
        valid only during the runtime of the callback. */
    const unsigned char *payload;

    /** The number of bytes, which can be read via \a payload. */
    unsigned int sizeOfPayload;

} bsw_rxCanMessage_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** CAN RX callback internal to the OS.
      Note, this prototype doesn't belong to the public interface of the BSW. It has been
    placed here to enable type checking in the most simple way. */
void bsw_osCbOnCANRx( unsigned int hMB
                    , bool isExtId
                    , unsigned int canId
                    , unsigned int sizeOfPayload
                    , const uint8_t payload[8]
                    , unsigned int timeStamp
                    );

/** Application provided initialization function for user process bsw_pidUser. */
extern int32_t bsw_taskUserInit(uint32_t PID);

/** Application provided regular 1ms task function, running in user process bsw_pidUser. */
extern int32_t bsw_taskUser1ms(uint32_t PID, uintptr_t taskParam);

/** Application provided regular 1ms task function, running in user process bsw_pidUser. */
extern int32_t bsw_taskUser10ms(uint32_t PID, uintptr_t taskParam);

/** Application provided regular 1ms task function, running in user process bsw_pidUser. */
extern int32_t bsw_taskUser100ms(uint32_t PID, uintptr_t taskParam);

/** Application provided regular 1ms task function, running in user process bsw_pidUser. */
extern int32_t bsw_taskUser1000ms(uint32_t PID, uintptr_t taskParam);


/** Application provided initialization function for safety process bsw_pidSafety. */
extern int32_t bsw_taskSafetyInit(uint32_t PID);

/** Application provided regular 1ms task function, running in safety process bsw_pidSafety. */
extern int32_t bsw_taskSafety1ms(uint32_t PID, uintptr_t taskParam);

/** Application provided regular 10ms task function, running in safety process
    bsw_pidSafety. */
extern int32_t bsw_taskSafety10ms(uint32_t PID, uintptr_t taskParam);

/** CAN interface: This is the notification callback for received messages. It is run in
    user process \a bsw_pidUser and must execute very fast. The budget is 200us. */
int32_t bsw_onRxCan(uint32_t PID, const bsw_rxCanMessage_t *pRxCanMsg);

/*
 * Global inline functions
 */


#endif  /* BSW_BASICSOFTWARE_INCLUDED */

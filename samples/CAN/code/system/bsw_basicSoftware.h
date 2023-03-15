#ifndef BSW_BASICSOFTWARE_INCLUDED
#define BSW_BASICSOFTWARE_INCLUDED
/**
 * @file bsw_basicSoftware.h
 * Definition of global interface of module bsw_basicSoftware.c
 *
 * Copyright (C) 2020-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/** The MCU core, which most of the BSW is executed on. The I/O drivers are executed on
    this core and many of the APIs, which they offer, are only available to code running on
    this core. In the API documentation, this core is often referred toas the "main core".
    Note, this is a reporting macro, not a configuration item. It is not possible to choose
    the core just by changing the macro. */
#define BSW_MAIN_CORE   0u  /* Z7_0 or Z7A */


/** The process initialization tasks, which are provided by the application code, must not
    execute longer than this time budget. Otherwise the system won't start up. */
#define BSW_TI_INIT_TASK_MAX_IN_US          5000

/** CAN interface: The enumeration of configured, usable CAN devices (i.e. CAN buses). The
    defined value has the perspective of the application code and this perspective is
    mapped on the enumeration implemented in MCU HW and CAN driver. */
#define BSW_CAN_BUS_0                (/*cdr_canDev_CAN_*/0u)
//#define BSW_CAN_BUS_1                (/*cdr_canDev_CAN_*/3u)
//#define BSW_CAN_BUS_2                (/*cdr_canDev_CAN_*/2u)
//#define BSW_CAN_BUS_3                (/*cdr_canDev_CAN_*/1u)

/** CAN interface: The BSW uses index spaces for the mailboxes, which are offered to
    the user processes. Rx and Tx messages each have an own solid index space, which is not
    zero based. The first and last available index are provided.\n
      Note, all CAN buses use the same configuration and therefore, the macro relates to
    each of them. */
#define BSW_IDX_FIRST_RX_MAILBOX            0u
#define BSW_IDX_LAST_RX_MAILBOX             71u
#define BSW_IDX_FIRST_TX_MAILBOX            82u
#define BSW_IDX_LAST_TX_MAILBOX             111u

/** A few mailboxes are reserverd for use by the safety supervision process. The Rx
    mailboxes can be used by polling only (which is a typical safety requirement).
      Note, all CAN buses use the same configuration and therefore, the macro relates to
    each of them. */
#define BSW_IDX_FIRST_RX_MAILBOX_SAFETY     72u
#define BSW_IDX_LAST_RX_MAILBOX_SAFETY      77u
#define BSW_IDX_FIRST_TX_MAILBOX_SAFETY     78u
#define BSW_IDX_LAST_TX_MAILBOX_SAFETY      81u

/** This is an argument to function rtos_suspendAllTasksByPriority(). It would then shape a
    critical section between all user tasks 10 ms and slower. */
#define BSW_PRIO_USER_TASK_10MS     2u

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
    /** The zero based index of the CAN bus. The value is always #BSW_CAN_BUS_0, since only
        a single CAN bus is configured in this sample BSW. */
    unsigned int idxCanBus;

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
    placed here to enable type checking in the most simple way.
      @todo Find a better location for this prototype. */
#define bsw_osCbOnCANRxCanN(dev)                        \
void bsw_osCbOnCANRx_##dev( unsigned int hMB            \
                          , bool isExtId                \
                          , unsigned int canId          \
                          , unsigned int sizeOfPayload  \
                          , const uint8_t payload[8]    \
                          , unsigned int timeStamp      \
                          );
bsw_osCbOnCANRxCanN(CAN_0)
bsw_osCbOnCANRxCanN(CAN_1)
bsw_osCbOnCANRxCanN(CAN_2)
bsw_osCbOnCANRxCanN(CAN_3)
#undef bsw_osCbOnCANRxCanN

/** Application provided initialization function for user process bsw_pidUser. */
extern int32_t bsw_taskUserInit(uint32_t PID);

/** Application provided regular 1ms task function, running in user process bsw_pidUser. */
extern int32_t bsw_taskUser1ms(uint32_t PID, uintptr_t taskParam);

/** Application provided regular 10ms task function, running in user process bsw_pidUser. */
extern int32_t bsw_taskUser10ms(uint32_t PID, uintptr_t taskParam);

/** Application provided regular 100ms task function, running in user process bsw_pidUser. */
extern int32_t bsw_taskUser100ms(uint32_t PID, uintptr_t taskParam);

/** Application provided regular 1s task function, running in user process bsw_pidUser. */
extern int32_t bsw_taskUser1000ms(uint32_t PID, uintptr_t taskParam);


/** Application provided initialization function for safety process bsw_pidSafety. */
extern int32_t bsw_taskSafetyInit(uint32_t PID);

/** Application provided regular 1ms task function, running in safety process bsw_pidSafety. */
extern int32_t bsw_taskSafety1ms(uint32_t PID, uintptr_t taskParam);

/** Application provided regular 10ms task function, running in safety process
    bsw_pidSafety. */
extern int32_t bsw_taskSafety10ms(uint32_t PID, uintptr_t taskParam);

/*
 * Global inline functions
 */


#endif  /* BSW_BASICSOFTWARE_INCLUDED */

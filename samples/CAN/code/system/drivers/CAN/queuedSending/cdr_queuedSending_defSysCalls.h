#ifndef CDR_QUEUED_SENDING_DEFSYSCALLS_INCLUDED
#define CDR_QUEUED_SENDING_DEFSYSCALLS_INCLUDED
/**
 * @file cdr_queuedSending_defSysCalls.h
 * Definition of system call interface of extended service "queued sending" of CAN I/O
 * driver. The implementation of the * system calls is found in file cdr_queuedSending.c.
 *
 * Copyright (C) 2020-2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "cdr_canDriverAPI.h"


/*
 * Defines
 */


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0044)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0044) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0044)
    
# if CDR_SYSCALL_SEND_MESSAGE_QUEUED != 44
#  error Inconsistent definition of system call
# endif

/** This system call is available only on the core, which runs the CAN driver. The
    implementation doesn't support servicing different CAN devices on different cores.
    Therefore, one a single core may be configured to provide the system call. Which one
    this is, depends on the configuration of the CAN driver. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0044 \
                                RTOS_SC_TABLE_ENTRY(cdr_scSmplHdlr_sendMessageQueued, SIMPLE)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0044   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0044   RTOS_SYSCALL_DUMMY_TABLE_ENTRY

#else
# error System call 0044 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0044   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0044   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0044   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/* System call implementation to send a message. */
uint32_t cdr_scSmplHdlr_sendMessageQueued( uint32_t PID
                                         , unsigned int idxCanDevice
                                         , bool isExtId
                                         , unsigned int canId
                                         , unsigned int DLC
                                         , const uint8_t payload[]
                                         );

/*
 * Global inline functions
 */


#endif  /* CDR_QUEUED_SENDING_DEFSYSCALLS_INCLUDED */

#ifndef CDR_CANDRIVER_DEFSYSCALLS_INCLUDED
#define CDR_CANDRIVER_DEFSYSCALLS_INCLUDED
/**
 * @file cdr_canDriver_defSysCalls.h
 * Definition of system call interface of CAN I/O driver. Mostly, the implementation of the
 * system calls is found in file cdr_userCodeAPI.c.
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

#include <stdint.h>
#include <stdbool.h>

#include "cdr_canDriverAPI.h"


/*
 * Defines
 */


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0040)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0040) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0040)
    
# if CDR_SYSCALL_MAKE_MB_RESERVATION != 40
#  error Inconsistent definition of system call
# endif

/** This system call implementation is not specific to a core; basically, all of them may
    use the same function. Whether this is useful, may be strongly doubted. Most likely, one
    core will run the one-time initialization of the CAN stack and there's no need to grant
    additional access to the other cores. Just uncomment the definition for the very core
    doing the initialization. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0040 \
                               RTOS_SC_TABLE_ENTRY( cdr_scFullHdlr_makeMailboxReservation   \
                                                  , FULL                                    \
                                                  )                                         \
//# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0040 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0040
//# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0040 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0040

#else
# error System call 0040 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0040   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0040   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0040   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0041)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0041) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0041)
    
# if CDR_SYSCALL_SEND_MSG != 41
#  error Inconsistent definition of system call
# endif

/* This system call is not specific to a core; all of them may use the same function.
   Uncomment the definition for cores, which should not get access to the CAN stack. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0041 \
                                        RTOS_SC_TABLE_ENTRY(cdr_scSmplHdlr_sendMessage, SIMPLE)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0041 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0041
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0041 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0041

#else
# error System call 0041 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0041   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0041   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0041   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


#if CDR_NO_RX_USER_CODE_POLLING_MAILBOXES > 0
# if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0042)    \
     && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0042) \
     && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0042)
     
#  if CDR_SYSCALL_READ_MSG != 42
#   error Inconsistent definition of system call
#  endif

/* This system call is not specific to a core; all of them may use the same function.
   Uncomment the definition for cores, which should not get access to the CAN stack. */
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0042 \
                                        RTOS_SC_TABLE_ENTRY(cdr_scSmplHdlr_readMessage, SIMPLE)
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0042 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0042
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0042 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0042
  
# else
#  error System call 0042 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0042   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0042   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0042   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# endif
#endif /* CDR_NO_RX_USER_CODE_POLLING_MAILBOXES > 0 */

/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/* System call implementation for making a mailbox with CAN ID association. */
uint32_t cdr_scFullHdlr_makeMailboxReservation( uint32_t PID
                                              , unsigned int idxCanDevice
                                              , unsigned int hMB
                                              , bool isExtId
                                              , unsigned int canId
                                              , bool isReceived
                                              , unsigned int TxDLC
                                              , bool doNotify
                                              );
                                              
/* System call implementation to send a message. */
uint32_t cdr_scSmplHdlr_sendMessage( uint32_t PID
                                   , unsigned int idxCanDevice
                                   , unsigned int hMB
                                   , uint8_t payload[8]
                                   );
                                   
#if CDR_NO_RX_USER_CODE_POLLING_MAILBOXES > 0
/* System call implementation to read a message mailbox (polling). */
uint32_t cdr_scSmplHdlr_readMessage( uint32_t PID
                                   , unsigned int idxCanDevice
                                   , unsigned int hMB
                                   );
#endif /* CDR_NO_RX_USER_CODE_POLLING_MAILBOXES > 0 */

/*
 * Global inline functions
 */


#endif  /* CDR_CANDRIVER_DEFSYSCALLS_INCLUDED */

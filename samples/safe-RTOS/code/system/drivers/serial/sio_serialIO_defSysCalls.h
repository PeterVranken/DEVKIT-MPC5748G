#ifndef SIO_SERIALIO_DEFSYSCALLS_INCLUDED
#define SIO_SERIALIO_DEFSYSCALLS_INCLUDED
/**
 * @file sio_serialIO_defSysCalls.h
 * Declaration of system calls offered by and implemented in module sio_serialIO.c. This
 * header file has to be included by source file rtos_systemCall.c, which collects all system
 * call declarations and assembles the const table of system call descriptors.
 *
 * Copyright (C) 2019-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "rtos.h"
#include "sio_serialIO.h"


/*
 * Defines
 */

#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0020)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0020) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0020)
    
# if SIO_SYSCALL_WRITE_SERIAL != 20
#  error Inconsistent definition of system call
# endif

/* This system call is not specific to a core; all of them may use the same function. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0020 \
                                        RTOS_SC_TABLE_ENTRY(sio_scFlHdlr_writeSerial, FULL)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0020 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0020
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0020 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0020

#else
# error System call 0020 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0020   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0020   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0020   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
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

/* Preemptable system call implementation to write to the serial interface. */
unsigned int sio_scFlHdlr_writeSerial( uint32_t pidOfCallingTask
                                     , const char *msg
                                     , unsigned int noBytes
                                     );

#endif  /* SIO_SERIALIO_DEFSYSCALLS_INCLUDED */

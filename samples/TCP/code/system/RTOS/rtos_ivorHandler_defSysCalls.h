#ifndef RTOS_IVORHANDLER_DEFSYSCALLS_INCLUDED
#define RTOS_IVORHANDLER_DEFSYSCALLS_INCLUDED
/**
 * @file rtos_ivorHandler_defSysCalls.h
 * Declaration of system calls offered by and implemented in module rtos_ivorHandler.S.
 * This header file has to be included by source file rtos_systemCall.c, which collects all
 * system call declarations and assembles the const table of system call descriptors.
 *
 * Copyright (C) 2019 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "rtos.h"
#include "rtos_ivorHandler.h"


/*
 * Defines
 */

#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0000)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0000) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0000)

# if RTOS_SYSCALL_SUSPEND_TERMINATE_TASK != 0
#  error Inconsistent definition of system call
# endif

/* The basic system call handler is assembler implemented in rtos_ivorHandler.S. Note,
   despite of the C style prototype, this is not a C callable function. The calling
   convention is different to C. This is the reason, why we declare it here instead of
   publishing it globally in rtos_ivorHandler.h. */
extern void rtos_scBscHdlr_terminateUserTask(int32_t result);

/* This system call is not specific to a core; all of them may use the same function. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0000  \
                                RTOS_SC_TABLE_ENTRY(rtos_scBscHdlr_terminateUserTask, BASIC)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0000  RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0000
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0000  RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0000

#else
# error System call 0000 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0000    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0000    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0000    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
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


/*
 * Global inline functions
 */

#endif  /* RTOS_IVORHANDLER_DEFSYSCALLS_INCLUDED */

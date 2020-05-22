#ifndef STM_SYSTEMTIMER_DEFSYSCALLS_INCLUDED
#define STM_SYSTEMTIMER_DEFSYSCALLS_INCLUDED
/**
 * @file stm_systemTimer_defSysCalls.h
 * Definition of system call interface of module stm_systemTimer.c /
 * stm_systemTimer_sysCalls.S.
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
#include "rtos.h"
#include "stm_systemTimer.h"


/*
 * Defines
 */

#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0030)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0030) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0030)
    
# if STM_SYSCALL_GET_SYSTEM_TIME != 30
#  error Inconsistent definition of system call
# endif

/* This system call is not specific to a core; all of them may use the same function. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0030 \
                                        RTOS_SC_TABLE_ENTRY(stm_scBscHdlr_getSystemTime, BASIC)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0030 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0030
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0030 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0030

#else
# error System call 0030 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0030   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0030   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0030   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
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

/** System call implementation for stm_getSystemTime(). Caution: This is the prototype of
    the assembler code implementation of a system call of basic conformance class. Despite
    of the prototype, the function must not be called directly as a C function. */
uint32_t stm_scBscHdlr_getSystemTime(uint32_t PID, uint32_t idxStmTimer);

#endif  /* STM_SYSTEMTIMER_DEFSYSCALLS_INCLUDED */

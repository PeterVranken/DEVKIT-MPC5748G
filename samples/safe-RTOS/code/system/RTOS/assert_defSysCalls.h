#ifndef ASSERT_DEFSYSCALLS_INCLUDED
#define ASSERT_DEFSYSCALLS_INCLUDED
/**
 * @file assert_defSysCalls.h
 * Definition of global interface of module assert_defSysCalls.c
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

/* The entire contents of this file are not required in PRODUCTION compilation. */
#ifdef DEBUG

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include "rtos.h"


/*
 * Defines
 */

#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0006)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0006) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0006)
# define ASSERT_SYSCALL_ASSERT_FUNC 6

/* Assembler implemented code in assert_sysCall.S. Note, despite of the C style prototype,
   this is not a C callable function. The calling convention is different to C. */
extern void _Noreturn assert_scBscHdlr_assert_func( const char *fileName
                                                  , int line
                                                  , const char *funcName
                                                  , const char *expression
                                                  );
# if RTOS_NO_CORES >= 1
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0006 \
                                    RTOS_SC_TABLE_ENTRY(assert_scBscHdlr_assert_func, BASIC)
# endif
# if RTOS_NO_CORES >= 2
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0006 \
                                    RTOS_SC_TABLE_ENTRY(assert_scBscHdlr_assert_func, BASIC)
# endif
# if RTOS_NO_CORES >= 3
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0006 \
                                    RTOS_SC_TABLE_ENTRY(assert_scBscHdlr_assert_func, BASIC)
# endif
# if RTOS_NO_CORES >= 4
#  error System call definition requires extension for more than three cores
# endif
#else
# error System call 0006 is ambiguously defined
/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0006    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0006    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0006    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
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



#endif /* DEBUG */
#endif  /* ASSERT_DEFSYSCALLS_INCLUDED */

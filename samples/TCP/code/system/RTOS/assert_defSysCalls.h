#ifndef ASSERT_DEFSYSCALLS_INCLUDED
#define ASSERT_DEFSYSCALLS_INCLUDED
/**
 * @file assert_defSysCalls.h
 * Definition of global interface of module assert_defSysCalls.c
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

/* The entire contents of this file are not required in PRODUCTION compilation. */
#ifdef DEBUG

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include "rtos.config.h"
#include "rtos.h"


/*
 * Defines
 */

#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0006)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0006) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0006)
# define ASSERT_SYSCALL_ASSERT_FUNC 6


# if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 1
/* Assembler implemented code in assert_sysCall.S. Note, despite of the C style prototype,
   this is not a C callable function. The calling convention is different to C.
     Each core has its own copy of the routine in order to store the failure information in
   core-related variables. Here for core 0, Z4A. */
extern void _Noreturn assert_scBscHdlr_assert_func_core0( const char *fileName
                                                        , int line
                                                        , const char *funcName
                                                        , const char *expression
                                                        );

#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0006 \
                                RTOS_SC_TABLE_ENTRY(assert_scBscHdlr_assert_func_core0, BASIC)
# endif


# if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
/* Assembler implemented code in assert_sysCall.S. Note, despite of the C style prototype,
   this is not a C callable function. The calling convention is different to C.
     Each core has its own copy of the routine in order to store the failure information in
   core-related variables. Here for core 1, Z4B. */
extern void _Noreturn assert_scBscHdlr_assert_func_core1( const char *fileName
                                                        , int line
                                                        , const char *funcName
                                                        , const char *expression
                                                        );

#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0006 \
                                RTOS_SC_TABLE_ENTRY(assert_scBscHdlr_assert_func_core1, BASIC)
# endif


# if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
/* Assembler implemented code in assert_sysCall.S. Note, despite of the C style prototype,
   this is not a C callable function. The calling convention is different to C.
     Each core has its own copy of the routine in order to store the failure information in
   core-related variables. Here for core 2, Z2. */
extern void _Noreturn assert_scBscHdlr_assert_func_core2( const char *fileName
                                                        , int line
                                                        , const char *funcName
                                                        , const char *expression
                                                        );
                                                        
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0006 \
                                RTOS_SC_TABLE_ENTRY(assert_scBscHdlr_assert_func_core2, BASIC)
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

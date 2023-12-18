#ifndef ASSERT_SYSCALL_INCLUDED
#define ASSERT_SYSCALL_INCLUDED
/**
 * @file assert_sysCall.h
 * Definition of global interface of module assert_sysCall.S
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

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

#ifdef DEBUG
/**
 *   @func assert_os_assert_func
 * This function is the entry point into the assembly implementation of the assert
 * function, which can be used from non safe-RTOS code. The function will never be called
 * directly but it is invoked from the implementation of the C assert function
 * (__assert_func) if the conditions are fulfilled:\n
 *   - Code which runs under controle of safe-RTOS will use the system call and never get
 *     here.
 *   - Bare metal applications and safe-RTOS initialization code (i.e. prior to kernel startzup
 *     and installation of system call interrupt like I/O driver initializtation) will get
 *     into this function.
 *   - Code running in user mode but not under control of safe-RTOS (e.g. a bare-metal
 *     application, which has switched to user mode autonomously) cannot use the assertion
 *     mechanism. Such code would get here an cause an immediate privileged exception. It
 *     depends on the given application what that actually means.
 *   @return
 * After rcording the fault cause information, the function halts the further SW execution.
 * It'll never return.
 *   @param fileName
 * \a fileName holds a pointer to the constant string with the name of source, which the
 * failing assertion is located in.
 *   @param line
 * \a line holds a pointer to the constant string with the line number, which the failing
 * assertion is located at.
 *   @param funcName
 * \a funcName holds a pointer to the constant string with the name of C function, which
 * the failing assertion is located in.
 *   @param expression
 * \a expression holds a pointer to the constant string with the failing expression in the
 * assertion.
 */
void _Noreturn assert_os_assert_func( const char *fileName
                                    , int line
                                    , const char *funcName
                                    , const char *expression
                                    );
#endif

/*
 * Global inline functions
 */


#endif  /* ASSERT_SYSCALL_INCLUDED */

/**
 * @file assert.c
 * The C standard macro assert is in case of GCC for PowerPC implemented by an external
 * function. This leaves it open, how the target platform should behave when an assertion
 * fires. This module implements the wanted behavior as a system call for the RTOS.
 *
 * Copyright (C) 2017-2019 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
/* Module interface
 *   __assert_func
 * Local functions
 */

/* The entire contents of this file are not required in PRODUCTION compilation. */
#ifdef DEBUG

/*
 * Include files
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "typ_types.h"
#include "rtos_ivorHandler.h"
#include "assert_defSysCalls.h"


/*
 * Defines
 */
 
/* The assembler code of the kernel needs to know the index of the assert system call. It
   re-defines it since it can't read the definition made here. To avoid inconsistencies
   it's inivitable to compare both definitions from C code, which is capable of reading
   both definitions. */
#if ASSERT_SYSCALL_ASSERT_FUNC != RTOS_SYSCALL_ASSERT_FUNC
# error Assert system call index: Inconsistent data definition in interface between C and \
        assembly code
#endif

 
/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
/** The number of passed assert macros with \a false condition. If the assert function is
    configured to halt the SW in case (see #ASSERT_FAILURE_BEHAVIOR) then it becomes a
    Boolean flag, which indicates, whether an assertion has fired since reset. */
volatile uint32_t assert_noOccurances SECTION(.data.OS.assert_noOccurances) = 0;

/** If an assertion has fired: The name of the causing source file. Otherwise NULL. */
volatile const char *assert_fileName SECTION(.data.OS.assert_fileName) = NULL;

/** If an assertion has fired: The name of the causing function. Otherwise NULL. */
volatile const char *assert_funcName SECTION(.data.OS.assert_funcName) = NULL;

/** If an assertion has fired: The causing source line in the source file. Otherwise NULL. */
volatile signed int assert_line SECTION(.data.OS.assert_line) = -1;
 
/** If an assertion has fired: The failing condition. Otherwise NULL. */
volatile const char *assert_expression SECTION(.data.OS.assert_expression) = NULL;

/** If at least one assertion has fired: The maximum PID of all failing processes so far.
    With other words, the ID of the process with highest privileges, which had failed so
    far. The value is -1 as long as no assertion had fired at all. */
volatile int8_t assert_PID SECTION(.data.OS.assert_PID) = -1;


/*
 * Function implementation
 */

/**
 *   @fn __assert_func
 * This is the function, which is invoked by the assert macro if the condition is false. We
 * write the information about the location of the problem into global variables, where
 * they can be inspected with the debugger, disable all external interrupts and go into an
 * infinite loop.
 */
void _EXFUN(__assert_func, (const char *fileName, int line, const char *funcName, const char *expression))
{
    /* The actual implementation of the assert function is a system call. This makes the
       assert macro usable in OS and user contexts. Whether the next function returns or
       not depends on the chosen behavior of the assert function. See
       #ASSERT_FAILURE_BEHAVIOR for details. */
    rtos_systemCall(ASSERT_SYSCALL_ASSERT_FUNC, fileName, line, funcName, expression);
    
    /* The assert system call will return if the assertion is in user mode code and if the
       compiled behavior is either #ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_FIRST or
       #ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_LAST. Unfortunately, we can't return
       from this function to the C code, which placed the assertion because this function
       is declared _Noreturn and we can't rely on the compiler to implement the right
       instructions for continuing the calling function. Instead, we place an infinite loop
       here. The promise to continue the SW execution is held in this way:
         The user task spins in the loop either forever or until a specified time budget is
       exhausted. In either case, the problem is reported by the kernel. Forever spinning
       is reported as activation losses of the according event, time budget exhausted as
       process error #RTOS_ERR_PRC_DEADLINE. Anyway, kernel and the tasks of higher
       priority are not impacted. */
    while(true)
        ;
        
} /* End of __assert_func */

#endif /* DEBUG */
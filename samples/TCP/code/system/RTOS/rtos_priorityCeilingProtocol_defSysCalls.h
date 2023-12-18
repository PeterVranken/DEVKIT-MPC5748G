#ifndef RTOS_PRIORITY_CEILING_PROTOCOL_DEFSYSCALLS_INCLUDED
#define RTOS_PRIORITY_CEILING_PROTOCOL_DEFSYSCALLS_INCLUDED
/**
 * @file rtos_priorityCeilingProtocol_defSysCalls.h
 * Declaration of system calls offered by and implemented in module
 * rtos_priorityCeilingProtocol.S. This header file has to be included by source file
 * rtos_systemCall.c, which collects all system call declarations and assembles the const
 * table of system call descriptors.
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

#include <stdint.h>
#include <stdbool.h>

#include "rtos.h"
#include "rtos_priorityCeilingProtocol.h"


/*
 * Defines
 */

#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0001)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0001) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0001)
    
# if RTOS_SYSCALL_SUSPEND_ALL_TASKS_BY_PRIORITY != 1
#  error Inconsistent definition of system call
# endif

/* Assembler implemented code in rtos_priorityCeilingProtocol.S. Note, despite of the C
   style prototype, this is not a C callable function. The calling convention is different
   to C. This is the reason, why we declare it here instead of publishing it globally in
   rtos_priorityCeilingProtocol.h. */
extern uint32_t rtos_scBscHdlr_suspendAllTasksByPriority(uint32_t suspendUpToThisPrio);

/* This system call is not specific to a core; all of them may use the same function. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0001  \
                        RTOS_SC_TABLE_ENTRY(rtos_scBscHdlr_suspendAllTasksByPriority, BASIC)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0001  RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0001
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0001  RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0001

#else
# error System call 0001 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0001    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0001    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0001    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0002)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0002) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0002)
    
# if RTOS_SYSCALL_RESUME_ALL_TASKS_BY_PRIORITY != 2
#  error Inconsistent definition of system call
# endif

/* Assembler implemented code in rtos_priorityCeilingProtocol.S. Note, despite of the C
   style prototype, this is not a C callable function. The calling convention is different
   to C. This is the reason, why we declare it here instead of publishing it globally in
   rtos_priorityCeilingProtocol.h. */
extern uint32_t rtos_scBscHdlr_resumeAllTasksByPriority(uint32_t resumeDownToThisPrio);

/* This system call is not specific to a core; all of them may use the same function. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0002  \
                        RTOS_SC_TABLE_ENTRY(rtos_scBscHdlr_resumeAllTasksByPriority, BASIC)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0002  RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0002
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0002  RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0002

#else
# error System call 0002 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0002    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0002    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0002    RTOS_SYSCALL_DUMMY_TABLE_ENTRY
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


#endif  /* RTOS_PRIORITY_CEILING_PROTOCOL_DEFSYSCALLS_INCLUDED */

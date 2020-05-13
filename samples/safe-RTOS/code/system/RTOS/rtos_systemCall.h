#ifndef RTOS_SYSTEMCALL_INCLUDED
#define RTOS_SYSTEMCALL_INCLUDED
/**
 * @file rtos_systemCall.h
 * Definition of global interface of module rtos_systemCall.c\n
 *   Note, this header file shares information between assembler and C code.
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

#ifdef __STDC_VERSION__
# include <stdint.h>
# include <stdbool.h>
#endif


/*
 * Defines
 */

/** The number of supported system calls.
      @remark If this define is increased than the initializer expression of \a
    rtos_systemCallDescAry and the list of conditional defines
    #RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0000, #RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0001, and so
    on, found in file rtos_systemCall.c, need to be extended, too. */
#define RTOS_NO_SYSTEM_CALLS        64

/** Definition of the enumeration of the supported conformance classes for system call
    handlers. We have:\n\n
      Basic conformance class: The handler is a raw assembler implementation. The system
    call exception branches to the assembler code and it has full responsibility for stack
    switching, memory protection, return from interrupt, etc. This class is not usable with
    C code.\n\n
      Simple handler class: Such a handler can be implemented as C function. The system
    call arguments are accessible as arguments 2, 3, ... of this C function. (The first
    argument of the C function provides the ID of the calling process to support the
    implementation of privileges management.) The function is executed with all interrupt
    processing suspended and therefore it needs to be short. This handler type must be used
    for fast, immediate actions only, like a set or get function.\n\n
      Full handler class: Such a handler can be implemented as C function. The system call
    arguments are accessible as arguments 2, 3, ... of this C function. (The first argument
    of the C function provides the ID of the calling process to support the implementation
    of privileges management.) The function is executed under normal conditions, it is for
    example preemptable by tasks and interrupts of higher priority. This handler type should
    be used longer lasting operations.\n\n
      Note, we need to use a define for this enumeration as the definition is shared with
    the implementing assembler code.\n
      Here, we have the enumeration value to declare a basic handler. */
#define RTOS_HDLR_CONF_CLASS_BASIC  0

/** Declaration of a simple handler. See #RTOS_HDLR_CONF_CLASS_BASIC for details. */
#define RTOS_HDLR_CONF_CLASS_SIMPLE 1   

/** Declaration of a full handler. See #RTOS_HDLR_CONF_CLASS_BASIC for details. */
#define RTOS_HDLR_CONF_CLASS_FULL   2   


#ifdef __STDC_VERSION__
/*
 * Global type definitions
 */

/** An entry in the table of system call service descriptors. */
typedef struct rtos_systemCallDesc_t
{
    /** The pointer to the service implementation.\n
          This field is address at offset O_SCDESC_sr from the assembler code. */
    uint32_t addressOfFct;

    /** Conformance class of service handler. The values are according to enum
        #RTOS_HDLR_CONF_CLASS_BASIC and following. */
    uint32_t conformanceClass;

} rtos_systemCallDesc_t;


/*
 * Global data declarations
 */


/*
 * Global static inline functions
 */


/*
 * Global prototypes
 */

/** Initialization function of the system call service implementation. */
void rtos_osInitSystemCalls(void);

#endif  /* C code parts of the file */
#endif  /* RTOS_SYSTEMCALL_INCLUDED */

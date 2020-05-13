#ifndef LBD_LEDANDBUTTONDRIVER_DEFSYSCALLS_INCLUDED
#define LBD_LEDANDBUTTONDRIVER_DEFSYSCALLS_INCLUDED
/**
 * @file lbd_ledAndButtonDriver_defSysCalls.h
 * Definition of system call interface of module lbd_ledAndButtonDriver.
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
#include "lbd_ledAndButtonDriver.h"


/*
 * Defines
 */

#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0025)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0025) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0025)
    
# if LBD_SYSCALL_SET_LED != 25
#  error Inconsistent definition of system call
# endif

# if RTOS_NO_CORES >= 1
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0025 \
                                        RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_setLED, SIMPLE)
# endif
# if RTOS_NO_CORES >= 2
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0025 \
                                        RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_setLED, SIMPLE)
# endif
# if RTOS_NO_CORES >= 3
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0025 \
                                        RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_setLED, SIMPLE)
# endif
# if RTOS_NO_CORES >= 4
#  error System call definition requires extension for more than three cores
# endif

#else

# error System call 0025 is ambiguously defined
/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0025   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0025   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0025   RTOS_SYSCALL_DUMMY_TABLE_ENTRY

#endif


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0026)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0026) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0026)
    
# if LBD_SYSCALL_GET_BUTTON != 26
#  error Inconsistent definition of system call
# endif

# if RTOS_NO_CORES >= 1
#  define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0026 \
                                        RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_getButton, SIMPLE)
# endif
# if RTOS_NO_CORES >= 2
#  define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0026 \
                                        RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_getButton, SIMPLE)
# endif
# if RTOS_NO_CORES >= 3
#  define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0026 \
                                        RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_getButton, SIMPLE)
# endif
# if RTOS_NO_CORES >= 4
#  error System call definition requires extension for more than three cores
# endif

#else

# error System call 0026 is ambiguously defined
/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0026   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0026   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0026   RTOS_SYSCALL_DUMMY_TABLE_ENTRY

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

/* System call implementation to make the LED driver available to user mode tasks. */
uint32_t lbd_scSmplHdlr_setLED(uint32_t callingPid ATTRIB_UNUSED, lbd_led_t led, bool isOn);

/* System call implementation to read the button states of SW2 and SW3 on the eval board. */
uint32_t lbd_scSmplHdlr_getButton(uint32_t callingPid ATTRIB_UNUSED, lbd_button_t button);

#endif  /* LBD_LEDANDBUTTONDRIVER_DEFSYSCALLS_INCLUDED */

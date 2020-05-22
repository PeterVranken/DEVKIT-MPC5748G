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

/* This system call is not specific to a core; all of them may use the same function. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0025 \
                                       RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_setLED, SIMPLE)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0025 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0025
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0025 RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0025

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

# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0026 \
                                   RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_getButton_core0, SIMPLE)
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0026 \
                                   RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_getButton_core1, SIMPLE)
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0026 \
                                   RTOS_SC_TABLE_ENTRY(lbd_scSmplHdlr_getButton_core2, SIMPLE)

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
uint32_t lbd_scSmplHdlr_setLED(uint32_t callingPid, lbd_led_t led, bool isOn);

#if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 1
/* System call implementation to read the button states of SW2 and SW3 from core 0. */
uint32_t lbd_scSmplHdlr_getButton_core0( uint32_t callingPid, lbd_button_t button);
#endif

#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 1
/* System call implementation to read the button states of SW2 and SW3 from core 1. */
uint32_t lbd_scSmplHdlr_getButton_core1(uint32_t callingPid, lbd_button_t button);
#endif

#if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 1
/* System call implementation to read the button states of SW2 and SW3 from core 2. */
uint32_t lbd_scSmplHdlr_getButton_core2(uint32_t callingPid, lbd_button_t button);
#endif

#endif  /* LBD_LEDANDBUTTONDRIVER_DEFSYSCALLS_INCLUDED */

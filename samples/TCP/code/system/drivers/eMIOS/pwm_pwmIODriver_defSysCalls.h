#ifndef PWM_PWMIODRIVER_DEFSYSCALLS_INCLUDED
#define PWM_PWMIODRIVER_DEFSYSCALLS_INCLUDED
/**
 * @file pwm_pwmIODriver_defSysCalls.h
 * Definition of system call interface of module pwm_pwmIODriver.
 *
 * Copyright (C) 2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "pwm_pwmIODriver.h"

/*
 * Defines
 */

#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0035)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0035) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0035)
    
# if PWM_SYSCALL_SET_PWM_OUT_F_AND_DC != 35
#  error Inconsistent definition of system call
# endif

/* This system call is not fully multi-core capable. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0035 \
                                RTOS_SC_TABLE_ENTRY(pwm_scSmplHdlr_setPwmOutFAndDc, SIMPLE)

/* This sample implementation only uses core 0. To make the system call available on other
   cores, too, we would need to make pwm_osSetChnFrequencyAndDutyCycle() fully multicore
   capable. A core-local mutex needs replacement by a cross-core mutex. */
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0035 RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0035 RTOS_SYSCALL_DUMMY_TABLE_ENTRY

#else
# error System call 0035 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0035   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0035   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0035   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
#endif


#if !defined(RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0036)    \
    && !defined(RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0036) \
    && !defined(RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0036)
    
# if PWM_SYSCALL_GET_PWM_IN_TIME != 36
#  error Inconsistent definition of system call
# endif

/* This system call is not specific to a core; all of them may use the same function. */
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0036 \
                                RTOS_SC_TABLE_ENTRY(pwm_scSmplHdlr_getPwmInTime, SIMPLE)

/* This sample implementation only uses core 0, although this system could be used on the
   other cores, too. */
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0036 RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0036 RTOS_SYSCALL_DUMMY_TABLE_ENTRY

#else
# error System call 0036 is ambiguously defined

/* We purposely redefine the table entry and despite of the already reported error; this
   makes the compiler emit a message with the location of the conflicting previous
   definition.*/
# define RTOS_CORE_0_SYSCALL_TABLE_ENTRY_0036   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_1_SYSCALL_TABLE_ENTRY_0036   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
# define RTOS_CORE_2_SYSCALL_TABLE_ENTRY_0036   RTOS_SYSCALL_DUMMY_TABLE_ENTRY
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

/** System call function to set frequency and duty cycle of PWM output. */
uint32_t pwm_scSmplHdlr_setPwmOutFAndDc( uint32_t pidOfCallingTask ATTRIB_UNUSED
                                       , pwm_pwmOutChannel_t pwmOutputChn
                                       , float f
                                       , float dutyCycle
                                       );

/** System call function to read period or duty time at PWM input. */
uint32_t pwm_scSmplHdlr_getPwmInTime( uint32_t pidOfCallingTask ATTRIB_UNUSED
                                    , pwm_pwmInChannel_t pwmInputChn
                                    );

/*
 * Global inline functions
 */


#endif  /* PWM_PWMIODRIVER_DEFSYSCALLS_INCLUDED */

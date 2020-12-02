/**
 * @file stm_systemTimer_sysCall.c
 * System call to access the current system time from user mode code.
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
/* Module interface
 *   stm_getSystemTime
 *   stm_scBscHdlr_getSystemTime
 * Local functions
 */

#ifndef __VLE__
# error This file is intended for compilation for VLE instruction set only
#endif

/*
 * Include files
 */

#include "stm_systemTimer.h"


/*
 * Defines
 */

/** Peripheral STM_0 base address */
#define STM_0_BASE      0xfc068000

/** Peripheral STM_1 base address */
#define STM_1_BASE      0xfc06c000

/** Peripheral STM_2 base address */
#define STM_2_BASE      0xfc070000


/*
 * External function declarations
 */


/*
 * Data declarations
 */



/*
 * Function implementation
 */

/**
 *   @func stm_getSystemTime
 * Get the counter value from one of the three free running system timers.
 *   @return
 * On return, r3 contains the current counter value, which represents the system time. See
 * #STM_TIMER_0_PERIOD_IN_NS, #STM_TIMER_1_PERIOD_IN_NS and #STM_TIMER_2_PERIOD_IN_NS for
 * the units.
 *   @param r3
 * On entry, r3 holds the index of the counter to read. The value is in the range 0..2.
 *   @remark
 * The function must be called from user code only. Supervisor code (OS tasks and ISRs)
 * will instead call the equivalent function stm_osGetSystemTime().
 */
    .section    .text.ivor.stm_getSystemTime
    .global     stm_getSystemTime, stm_scBscHdlr_getSystemTime
    .extern     rtos_osSystemCallBadArgument
    .p2align    1

stm_getSystemTime:
    se_mr       r4, r3  /* r4: 1st system call argument is index of timer. */
    se_li       r3, STM_SYSCALL_GET_SYSTEM_TIME
    se_sc       /* Continue in SV mode at stm_scBscHdlr_getSystemTime... */
    se_blr      /* ... return here with rfi and return from C function call. */

stm_scBscHdlr_getSystemTime:
    se_cmpli    r4, 2
    e_bgt       rtos_osSystemCallBadArgument
    se_addi     r4, 2   /* +2: First part of STM address, will become 2*2^14 = 0x8000 */
    se_slwi     r4, 14  /* r4: Array offset. Distance between STM n and n+1 is 2^14 Byte */
    e_add2is    r4, 0xfc06  /* r4: Base address of aimed STM device. */
    e_lwz       r3, 4(r4)   /* r3: Register contents of STM->CNT */
    se_rfi

/* End of stm_getSystemTime */


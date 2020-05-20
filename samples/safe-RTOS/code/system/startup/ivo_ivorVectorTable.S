/**
 * @file ivo_ivorVectorTable.S
 * Part of startup code for MPC5748G: The table of IVOR exception handlers for cores not
 * running the RTOS.\n
 *   The default handlers implemented here implement an infinite loop, a branch in itself.
 * This reports an unexpected exception to the debugger.\n
 *   Implemented exceptions are hard-coded in this file: The handler implementation jumps
 * unconditionally to the intended true function. If a new handler is installed or if an
 * existing handler is replaced then the code here has to be changed by hard-coding the name
 * of the new intended handler.
 *
 * Copyright (C) 2018-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   ivo_IVOR0trapCoreN .. ivo_IVOR15trapCoreN (thereof in use 0..11), N = 0 and/or 1 and/or 2
 * Local functions
 */

#ifndef __VLE__
# error This file is intended for compilation for VLE instruction set only
#endif

/*
 * Include files
 */

#include "rtos.config.h"


/*
 * Defines
 */


/*
 * External function declarations
 */


/*
 * Data declarations
 */


/*
 * Function implementation
 */


    .macro      macroIVORVectorTable Core
/*
 * MPC5748G: Different to other z4/z7 cores, it doesn't have distinct pointers to
 * distinct exceptions but it makes use a solid table of handlers, where an entry has a
 * size of 16 Byte. The IVOR table has an alignment of 8 Bit.
 */
    .section    .text.ivorTable.\Core\()
    .global     rtos_ivorVectorTable\Core\()
    .p2align    8
rtos_ivorVectorTable\Core\():


/**
 *   @func ivo_IVOR0trap\Core\()
 * Exception handler IVOR0 for the Critical Input interrupt. See RM, section 62.8.5.1
 * on page 3130.
 */
    .global     ivo_IVOR0trap\Core\()   /* Note, it is not required to make this symbol
                                           global. However it is handy to see the traps in
                                           the application map file and this is why we do
                                           so for all traps. */
ivo_IVOR0trap\Core\():
    se_b    ivo_IVOR0trap\Core\()  /* Critical Input interrupt handler */ 


/**
 *   @func ivo_IVOR1trap\Core\()
 * Exception handler IVOR1 for the Machine check / (NMI) interrupt.
 */
    .global     ivo_IVOR1trap\Core\()
    .p2align    4
ivo_IVOR1trap\Core\():
    se_b        ivo_IVOR1trap\Core\()  /* Machine check / (NMI) interrupt handler */


/**
 *   @func ivo_IVOR2trap\Core\()
 * Exception handler IVOR2 for the Data Storage interrupt. This trap is taken if the MMU
 * signals an unpermitted data access.
 */
    .global     ivo_IVOR2trap\Core\()
    .p2align    4
ivo_IVOR2trap\Core\():
    se_b        ivo_IVOR2trap\Core\()  /* Data Storage interrupt handler */


/**
 *   @func ivo_IVOR3trap\Core\()
 * Exception handler IVOR3 for the Instruction Storage interrupt. This trap is taken if
 * the MMU signals an unpermitted instruction fetch.
 */
    .global     ivo_IVOR3trap\Core\()
    .p2align    4
ivo_IVOR3trap\Core\():
    se_b        ivo_IVOR3trap\Core\()  /* Instruction Storage interrupt handler */


/**
 *   @func ivo_IVOR4trap\Core\()
 * Exception handler IVOR4 for the External Input interrupt. See RM, section
 * 62.8.5.5 on page 3133.
 */
    .global     ivo_IVOR4trap\Core\()
    .p2align    4
ivo_IVOR4trap\Core\():
    e_b     int_INTCInterruptHandler\Core\()   /* External Input interrupt handler */



/**
 *   @func ivo_IVOR5trap\Core\()
 * Exception handler IVOR5 for the Alignment interrupt.
 */
    .global     ivo_IVOR5trap\Core\()
    .p2align    4
ivo_IVOR5trap\Core\():
    se_b        ivo_IVOR5trap\Core\()  /* Alignment interrupt handler */


/**
 *   @func ivo_IVOR6trap\Core\()
 * Exception handler IVOR6 for the Program interrupt.
 */
    .global     ivo_IVOR6trap\Core\()
    .p2align    4
ivo_IVOR6trap\Core\():
    se_b        ivo_IVOR6trap\Core\()  /* Program interrupt handler */


/**
 *   @func ivo_IVOR7trap\Core\()
 * Exception handler IVOR7 for the Performance Monitor interrupt. See RM, section
 * 62.8.5.8.
 */
    .global     ivo_IVOR7trap\Core\()
    .p2align    4
ivo_IVOR7trap\Core\():
    se_b        ivo_IVOR7trap\Core\()  /* Performance Monitor interrupt handler */


/**
 *   @func ivo_IVOR8trap\Core\()
 * Exception handler IVOR8 for the System Call interrupt.
 */
    .global     ivo_IVOR8trap\Core\()
    .p2align    4
ivo_IVOR8trap\Core\():
    se_b        ivo_IVOR8trap\Core\()  /* System Call interrupt handler */


/**
 *   @func ivo_IVOR9trap\Core\()
 * Exception handler IVOR9 for the Debug interrupt.
 */
    .global     ivo_IVOR9trap\Core\()
    .p2align    4
ivo_IVOR9trap\Core\():
    se_b        ivo_IVOR9trap\Core\()  /* Debug interrupt handler */


/**
 *   @func ivo_IVOR10trap\Core\()
 * Exception handler IVOR10 for the Embedded Floating-point Data interrupt. See RM
 * section 62.8.5.11.
 */
    .global     ivo_IVOR10trap\Core\()
    .p2align    4
ivo_IVOR10trap\Core\():
    se_b        ivo_IVOR10trap\Core\() /* Embedded Floating-point Data handler */


/**
 *   @func ivo_IVOR11trap\Core\()
 * Exception handler IVOR11 for the Embedded Floating-point Round interrupt. See RM
 * section 62.8.5.12.
 */
    .global     ivo_IVOR11trap\Core\()
    .p2align    4
ivo_IVOR11trap\Core\():
    se_b        ivo_IVOR11trap\Core\() /* Embedded Floating-point Round interrupt handler */


/**
 *   @func ivo_IVOR12trap\Core\()
 * Unused exception handler IVOR12.
 */
    .global     ivo_IVOR12trap\Core\()
    .p2align    4
ivo_IVOR12trap\Core\():
    se_b        ivo_IVOR12trap\Core\()


/**
 *   @func ivo_IVOR13trap\Core\()
 * Unused exception handler IVOR13.
 */
    .global     ivo_IVOR13trap\Core\()
    .p2align    4
ivo_IVOR13trap\Core\():
    se_b        ivo_IVOR13trap\Core\()


/**
 *   @func ivo_IVOR14trap\Core\()
 * Unused exception handler IVOR14.
 */
    .global     ivo_IVOR14trap\Core\()
    .p2align    4
ivo_IVOR14trap\Core\():
    se_b        ivo_IVOR14trap\Core\()


/**
 *   @func ivo_IVOR15trap\Core\()
 * Unused exception handler IVOR15.
 */
    .global     ivo_IVOR15trap\Core\()
    .p2align    4
ivo_IVOR15trap\Core\():
    se_b        ivo_IVOR15trap\Core\()

/* End of IVOR exception handlers 0..15 (thereof in use 0..11) for core N, if it is not
   running the RTOS */
    .endm
    
    /* Instantiate the macro up to three times to have an individual implementation for
       each core, which is not running safe-RTOS (safe-RTOS has its own IVOR #4 handler). */
#if RTOS_RUN_SAFE_RTOS_ON_CORE_0 == 0
    macroIVORVectorTable Core0
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_1 == 0
    macroIVORVectorTable Core1
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_2 == 0
    macroIVORVectorTable Core2
#endif

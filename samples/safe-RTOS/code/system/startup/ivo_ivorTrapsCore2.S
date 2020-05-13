/**
 * @file ivo_ivorTrapsCore2.S
 * Part of startup code for MPC5748G: The table of IVOR exception handlers for core 2, Z2.
 * The default handlers implemented here implement an infinite loop, a branch in itself.
 * This reports an unexpected exception to the debugger.\n
 *   Implemented exceptions are hard-coded in this file: The handler implementation jumps
 * unconditionally to the intended true function. If a new handler is installed or if an
 * existing handler is replaced then the code here has to be changed by hard-coding the name
 * of the new intended handler.
 *
 * Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   ivo_IVOR0trapCore2 .. ivo_IVOR15trapCore2 (thereof in use 0..13)
 * Local functions
 */

#ifndef __VLE__
# error This file is intended for compilation for VLE instruction set only
#endif

/*
 * Include files
 */


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


/**
 *   @func ivo_IVOR0trapCore2
 * Exception handler IVOR0 for the Critical Input interrupt. See RM, section 62.8.5.1
 * on page 3130.
 */
    .section .text.ivorTable.Core2, "ax"
    .global ivo_IVOR0trapCore2  /* Note, it is not required to make this symbol global. However
                                   it is handy to see the traps in the application map file
                                   and this is why we do so for all traps. */
    .type   ivo_IVOR0trapCore2, @function
    .align  8
ivo_IVOR0trapCore2:
    se_b    ivo_IVOR0trapCore2  /* Critical Input interrupt handler */ 
    .size   ivo_IVOR0trapCore2, .-ivo_IVOR0trapCore2


/**
 *   @func ivo_IVOR1trapCore2
 * Exception handler IVOR1 for the Machine check / (NMI) interrupt.
 */
    .global ivo_IVOR1trapCore2
    .type   ivo_IVOR1trapCore2, @function
    .align  4
ivo_IVOR1trapCore2:
    se_b    ivo_IVOR1trapCore2  /* Machine check / (NMI) interrupt handler */
    .size   ivo_IVOR1trapCore2, .-ivo_IVOR1trapCore2


/**
 *   @func ivo_IVOR2trapCore2
 * Exception handler IVOR2 for the Data Storage interrupt. This trap is taken if the MMU
 * signals an unpermitted data access.
 */
    .global ivo_IVOR2trapCore2
    .type   ivo_IVOR2trapCore2, @function
    .align  4
ivo_IVOR2trapCore2:
    se_b    ivo_IVOR2trapCore2  /* Data Storage interrupt handler */
    .size   ivo_IVOR2trapCore2, .-ivo_IVOR2trapCore2


/**
 *   @func ivo_IVOR3trapCore2
 * Exception handler IVOR3 for the Instruction Storage interrupt. This trap is taken if
 * the MMU signals an unpermitted instruction fetch.
 */
    .global ivo_IVOR3trapCore2
    .type   ivo_IVOR3trapCore2, @function
    .align  4
ivo_IVOR3trapCore2:
    se_b    ivo_IVOR3trapCore2  /* Instruction Storage interrupt handler */
    .size   ivo_IVOR3trapCore2, .-ivo_IVOR3trapCore2


/**
 *   @func ivo_IVOR4trapCore2
 * Exception handler IVOR4 for the External Input interrupt. See RM, section
 * 62.8.5.5 on page 3133.
 */
    .global ivo_IVOR4trapCore2
    .type   ivo_IVOR4trapCore2, @function
    .align  4
ivo_IVOR4trapCore2:
    e_b     int_INTCInterruptHandlerCore2   /* External Input interrupt handler */
    .size   ivo_IVOR4trapCore2, .-ivo_IVOR4trapCore2



/**
 *   @func ivo_IVOR5trapCore2
 * Exception handler IVOR5 for the Alignment interrupt.
 */
    .global ivo_IVOR5trapCore2
    .type   ivo_IVOR5trapCore2, @function
    .align  4
ivo_IVOR5trapCore2:
    se_b    ivo_IVOR5trapCore2  /* Alignment interrupt handler */
    .size   ivo_IVOR5trapCore2, .-ivo_IVOR5trapCore2


/**
 *   @func ivo_IVOR6trapCore2
 * Exception handler IVOR6 for the Program interrupt.
 */
    .global ivo_IVOR6trapCore2
    .type   ivo_IVOR6trapCore2, @function
    .align  4
ivo_IVOR6trapCore2:
    se_b    ivo_IVOR6trapCore2  /* Program interrupt handler */
    .size   ivo_IVOR6trapCore2, .-ivo_IVOR6trapCore2


/**
 *   @func ivo_IVOR7trapCore2
 * Exception handler IVOR7 for the Performance Monitor interrupt. See RM, section
 * 62.8.5.8.
 */
    .global ivo_IVOR7trapCore2
    .type   ivo_IVOR7trapCore2, @function
    .align  4
ivo_IVOR7trapCore2:
    se_b    ivo_IVOR7trapCore2  /* Performance Monitor interrupt handler */
    .size   ivo_IVOR7trapCore2, .-ivo_IVOR7trapCore2


/**
 *   @func ivo_IVOR8trapCore2
 * Exception handler IVOR8 for the System Call interrupt.
 */
    .global ivo_IVOR8trapCore2
    .type   ivo_IVOR8trapCore2, @function
    .align  4
ivo_IVOR8trapCore2:
    se_b    ivo_IVOR8trapCore2  /* System Call interrupt handler */
    .size   ivo_IVOR8trapCore2, .-ivo_IVOR8trapCore2


/**
 *   @func ivo_IVOR9trapCore2
 * Exception handler IVOR9 for the Debug interrupt.
 */
    .global ivo_IVOR9trapCore2
    .type   ivo_IVOR9trapCore2, @function
    .align  4
ivo_IVOR9trapCore2:
    se_b    ivo_IVOR9trapCore2  /* Debug interrupt handler */
    .size   ivo_IVOR9trapCore2, .-ivo_IVOR9trapCore2


/**
 *   @func ivo_IVOR10trapCore2
 * Exception handler IVOR10 for the Embedded Floating-point Data interrupt. See RM
 * section 62.8.5.11.
 */
    .global ivo_IVOR10trapCore2
    .type   ivo_IVOR10trapCore2, @function
    .align  4
ivo_IVOR10trapCore2:
    se_b    ivo_IVOR10trapCore2 /* Embedded Floating-point Data handler */
    .size   ivo_IVOR10trapCore2, .-ivo_IVOR10trapCore2


/**
 *   @func ivo_IVOR11trapCore2
 * Exception handler IVOR11 for the Embedded Floating-point Round interrupt. See RM
 * section 62.8.5.12.
 */
    .global ivo_IVOR11trapCore2
    .type   ivo_IVOR11trapCore2, @function
    .align  4
ivo_IVOR11trapCore2:
    se_b    ivo_IVOR11trapCore2 /* Embedded Floating-point Round interrupt handler */
    .size   ivo_IVOR11trapCore2, .-ivo_IVOR11trapCore2


/**
 *   @func ivo_IVOR12trapCore2
 * Unused exception handler IVOR12.
 */
    .global ivo_IVOR12trapCore2
    .type   ivo_IVOR12trapCore2, @function
    .align  4
ivo_IVOR12trapCore2:
    se_b    ivo_IVOR12trapCore2
    .size   ivo_IVOR12trapCore2, .-ivo_IVOR12trapCore2


/**
 *   @func ivo_IVOR13trapCore2
 * Unused exception handler IVOR13.
 */
    .global ivo_IVOR13trapCore2
    .type   ivo_IVOR13trapCore2, @function
    .align  4
ivo_IVOR13trapCore2:
    se_b    ivo_IVOR13trapCore2
    .size   ivo_IVOR13trapCore2, .-ivo_IVOR13trapCore2


/**
 *   @func ivo_IVOR14trapCore2
 * Unused exception handler IVOR14.
 */
    .global ivo_IVOR14trapCore2
    .type   ivo_IVOR14trapCore2, @function
    .align  4
ivo_IVOR14trapCore2:
    se_b    ivo_IVOR14trapCore2
    .size   ivo_IVOR14trapCore2, .-ivo_IVOR14trapCore2


/**
 *   @func ivo_IVOR15trapCore2
 * Unused exception handler IVOR15.
 */
    .global ivo_IVOR15trapCore2
    .type   ivo_IVOR15trapCore2, @function
    .align  4
ivo_IVOR15trapCore2:
    se_b    ivo_IVOR15trapCore2
    .size   ivo_IVOR15trapCore2, .-ivo_IVOR15trapCore2

/* End of IVOR exception handlers 0..15 (thereof in use 0..13) for core 2, Z2 */

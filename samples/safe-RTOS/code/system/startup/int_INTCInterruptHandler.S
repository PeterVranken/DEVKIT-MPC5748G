/**
 * @file int_INTCInterruptHandler.S
 * VLE assembler implementation of interrupt handler for external interrupts handled by the
 * INTC. Used for MPC5748G. The code has been designed for use with GCC for PowerPC EABI.\n
 *   The interrut handler defined here is used on a core, which doesn't run the RTOS. It is
 * simpler and a bit faster as it doesn't need to consider context switches and safety
 * requirements.
 *
 * Copyright (C) 2017-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   int_INTCInterruptHandlerCore0
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

/** Address of interrupt controller INTC in memory map. */
#define INTC            0xfc040000

/** Address of INTC interrupt acknowledge register in memory map, for processor 0. */
#define INTC_IACKR0     (INTC+0x20)

/** Address of INTC interrupt acknowledge register in memory map, for processor 1. */
#define INTC_IACKR1     (INTC+0x24)

/** Address of INTC interrupt acknowledge register in memory map, for processor 2. */
#define INTC_IACKR2     (INTC+0x28)

/** Address of INTC end of interrupt register in memory map, for processor 0. */
#define INTC_EOIR0      (INTC+0x30)

/** Address of INTC end of interrupt register in memory map, for processor 1. */
#define INTC_EOIR1      (INTC+0x34)

/** Address of INTC end of interrupt register in memory map, for processor 2. */
#define INTC_EOIR2      (INTC+0x38)


/*
 * External function declarations
 */


/*
 * Data declarations
 */



/*
 * Function implementation
 */



    .macro      macroINTCInterruptHandler core, INTC_IACKR, INTC_EOIR
/**
 *   @func int_INTCInterruptHandlerCoreN
 * This is the interrupt handler for the MCU trap #4, External Interrupts. This trap
 * relates to interrupts controlled by the INTC. The INTC provides the vector to the
 * appropriate service function and handles the preemption or mutual exclusion of
 * interrupts by providing an effective priority scheme.\n
 *   The handler implementation here will save the CPU context onto the stack, read the
 * service function pointer and call this function. It'll then acknowledge the interrupt
 * (thereby triggering the priority handling of the INTC) restore the context and return
 * from interrupt.
 */
    .section    .text.ivor4Handler.\core\() /* Load this section close to IVOR handler
                                               table of same core; se_b becomes possible to
                                               jump here. */
    .globl      int_INTCInterruptHandler\core\()
    .align      2
int_INTCInterruptHandler\core\():

    /// @todo Adopt #defines for offsets from kernelbuilder
    e_stwu  sp, -80(sp)         /* Create stack frame */
    
    /* Store all GPRegisters and SPR, which are volatile according to the EABI. */
    e_stmvgprw  8(sp)           /* r0, r3-r12: 11*4 Byte */
    e_stmvsprw  52(sp)          /* CR, LR, CTR, XER: 4*4 Byte */
    e_stmvsrrw  68(sp)          /* SRR0/SRR1: 2*4 Byte */

    /* Clear request to processor; r3 contains the address of the ISR */
    e_lis       r3, \INTC_IACKR\()@ha      /* Read pointer into ISR Vector Table
                                              int_INTCInterruptHandlerAry */
    e_lwz       r3, \INTC_IACKR\()@l(r3)   /* Load INTC_IACKR, which clears request to
                                              processor */
    se_lwz      r3, 0x0(r3)     /* Read ISR address from ISR Vector Table using pointer  */

    /* For preemptable interrupt handlers set the EE bit in the MSR. The property
       preemptability of a handler is encoded as MSBit of the vector in the table. */
    se_btsti    r3, 0
    se_beq      int_endIfPreemptable\core\()

    /* Clear the flag bit to get the proper address back. */
    se_bclri    r3, 0
    wrteei      1               /* Set MSR[EE]=1 to enable External Interrupts */
int_endIfPreemptable\core\():

    /* Branch to ISR handler address from SW vector table */
    mtlr        r3              /* Store ISR address to LR */
    se_blrl                     /* Branch to ISR, but return here */

    /* Prepare writing zero to interrupt acknowledge register. */
    se_li       r3, 0
    e_lis       r4, \INTC_EOIR\()@ha   /* Load upper half of INTC_EOIR address */
    
    /* Disable processor recognition of interrupts. This should be done prior to
       acknowledging the IRQ. Otherwise an interrupt of same priority (which can easily be
       already pending) would be served before we remove our stack frame. Since this could
       happen repeatedly we would no longer have an upper bounds for the stack usage. A
       system normally running well could crash to due stack overflow in case of high
       interrupt load. */
    wrteei      0

    /* Write 0 to INTC_EOIR, informing INTC to restore priority as it was on entry to this
       handler. Note, writing a zero (while any value would succeed) used to be demanded
       for future for the MPC5643L and is still recommended for the MPC5748G - although
       much weaker than before. We follow the recommendation even if this means an
       additional instruction. */
    e_stw       r3, \INTC_EOIR\()@l(r4)    /* Write 0 to INTC_EOIR */

    /* Restore all GPRegisters and SPR, which are volatile according to the EABI. */
    e_lmvgprw   8(sp)       /* r0, r3-r12: 11*4 Byte */
    e_lmvsprw   52(sp)      /* CR, LR, CTR, XER: 4*4 Byte. Could be done earlier, when
                               still EE=1 */
    e_lmvsrrw   68(sp)      /* SRR0/SRR1: 2*4 Byte */

    /* Remove the no longer needed stack frame. */
    e_la        sp, 80(sp)

    /* End of interrupt, restore MSR and PC from the SRR0/1. */
    se_rfi
    
/* End of int_INTCInterruptHandlerCoreN */
    .endm
    
    /* Instantiate the macro up to three times to have an individual implementation for
       each core, which is not running safe-RTOS (safe-RTOS has its own IVOR #4 handler). */
#if RTOS_RUN_SAFE_RTOS_ON_CORE_0_Z4A == 0
    macroINTCInterruptHandler Core0, INTC_IACKR0, INTC_EOIR0
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_1_Z4B == 0
    macroINTCInterruptHandler Core1, INTC_IACKR1, INTC_EOIR1
#endif
#if RTOS_RUN_SAFE_RTOS_ON_CORE_2_Z2 == 0
    macroINTCInterruptHandler Core2, INTC_IACKR2, INTC_EOIR2
#endif

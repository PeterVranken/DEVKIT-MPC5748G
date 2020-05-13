/**
 * @file cfl_configureFlash.S
 * VLE assembler implementation of flash controller initialization.
 *
 * Copyright (C) 2017-2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   cfl_configureFlash
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


/**
 *   @func cfl_configureFlash
 * Access the flash memory controller and select the optimal strategy. This affects the
 * number of wait states, port usage (data versus instruction fetches) and pre-fetch
 * strategies.\n
 *   The optimal settings depend on the chosen clock rate. The recommended settings can be
 * found in the MPC5748G Microcontroller Data Sheet, section 6.3.6, Flash read wait state
 * and address pipeline control settings, Table 34.\n
 *   At reset the flash controller initializes with a conservative, safe setting for wait
 * states and pipelining, which works stable even at highest clock rates. Therefore, this
 * routine can be safely called after configuring the system clock.
 *   @param r3 
 * r3 contains the value \a RWSC_waitStates, which is written into filed RWSC of register
 * PFLASH_PFCR1.
 *   @param r4
 * r4 contains the value of APC_pipelining, which is written into filed APC of register
 * PFLASH_PFCR1.
 *   @remark
 * MCU ref. manual, 73.5, p. 3591: The code to access the registers of the flash memory
 * controller PFLASH must reside in RAM - the flash configuration must not be done from
 * code, which itself resides in ROM. Consequently, only the first core must be running -
 * otherwise the others would still continue reading the flash during the changes. This
 * function copies a tiny machine code fragment onto the stack and branches there to
 * fulfill this requirement.
 *   @todo
 * The settings ofthe prefetch mechanism are still in reset state and should be revised.
 * Likely, we can still improve system performance by enabling it. Compare with MPC5643L
 * settings.
 */
    .global     cfl_configureFlash
cfl_configureFlash:
    e_stwu      sp, -24(sp) /* We need 20 Byte but stack frame must be multiple of 8 (EABI) */
    mflr        r0
    e_stw       r0, 28(sp)
    
    /* Load the required four movable instructions into r8..r10. */
    e_lis       r10, cfl_movalbeMachineCode@ha
    e_add16i    r10, r10, cfl_movalbeMachineCode@l
    e_lwz       r8, 0(r10)
    e_lwz       r9, 4(r10)
    e_lwz       r10, 8(r10)
    
    /* Store moveable sub-routine in the stack area. */
    e_stw       r8, 8(sp)
    e_stw       r9, 12(sp)
    e_stw       r10, 16(sp)
    
    /* mbar: We need a memory barrier here to have everything in RAM before we branch
       there and before we read any code from there.
         isync: Force re-reading instructions after changeing code. Required because
       look-ahead instruction fetching may have picked other bytes. */
    mbar
    se_isync
    
    /* Load pointer to function on the stack into the counter register. */
    e_la        r9, 8(sp)
    mtctr       r9
    
    /* Combine the function arguments to the complete register content. See RM, section
       73.5.1, Platform Flash Configuration Register 1 (PFLASH_PFCR1), p. 3595. The bits
       for RWSC and APC can be set in a read-modify-write access, but here we simply write
       the aimed value; nobody else has changed the register since reset yet.
         @todo This code needs revision to consider the prefetching, too. */
    e_rlwinm    r3, r3, 8, 19, 23  /* r3=RWSC: Mask with 0x1f, shift 8 Bits left */
    e_rlwimi    r3, r4, 13, 16, 18 /* r4=APC: Mask with 0x7, shift 13 Bits left, insert */
    se_addi     r3, 0x15           /* +10101b: P0_BFEN=1 (line buffer enable), P0_PFLIM=10b,
                                      prefetch on miss or hit, P0_IPFEN=1 (prefetch on
                                      instruction fetch) P0_DPFEN=0 (no prefetch on data
                                      fetch) */
    e_or2is     r3, 0x0001         /* P0_M0PFE=1 (Master 0=Z4A triggers prefetch), all other
                                      P0_MnPFE=0 (no other masters trigger prefetch) */

    /* Load register address */
    e_lis       r4, 0xfc03          /* PFLASH_BASE: 0xFC030000, PFCR1: Offset 0 */

    /* Call sub-routine, which is in the stack area. */
    se_bctrl
    
    /** @todo Weakness of implementation: After writing of each register we return to the
        flash ROM for reading next instructions. This makes it impossible to specify a
        register configuration, where several registers need to be set consistantly in a
        certain way to make it run. We are restricted to configurations, why are still
        runnable after each register change. We could first load all register contents in
        as may GPRs and then have a routine in RAM, which writes all of them into the
        controller. */

    /* Write 0x00020015 to register PFCR2 in order to enable prefetch on second port, too.
       Here, we allow instruction prefetch by Z4B, whose address bus is connected to port
       2. */
    e_lis       r3, 0x00020015@h    
    e_or2i      r3, 0x00020015@l    /* P1_M1PFE=1 (Master 0=Z4B triggers prefetch), all other
                                       P1_MnPFE=0 (no other masters trigger prefetch),
                                       P1_IPFEN=1 (prefetch on instruction fetch) P1_DPFEN=0
                                       (no prefetch on data fetch), P1_PFLIM=10b, prefetch on
                                       miss or hit, P1_BFEN=1 (line buffer enable) */
    se_addi     r4, 4               /* PFLASH_BASE: 0xFC030000, PFCR2: Offset 4 */
    
    /* Call sub-routine, which is in the stack area. */
    se_bctrl
    
    e_lwz       r0, 28(sp)
    mtlr        r0
    e_la        sp, 24(sp)
    se_blr

    .p2align    2
cfl_movalbeMachineCode:
    e_stw       r3, 0(r4)
    msync                   /* Accomplish transaction before return to flash. */
    se_isync                /* Force re-reading instructions after changeing flash
                               controller settings. Read next instuctions using new
                               settings. */
    se_blr

/* End of cfl_configureFlash */




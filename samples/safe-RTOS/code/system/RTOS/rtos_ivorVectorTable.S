/**
 * @file rtos_ivorVectorTable.S
 * Part of startup code for MPC5748G: The table of IVOR exception handlers for all cores
 * running the RTOS. The table entries implement a branch into the implementation of the
 * kernel.
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
 *   rtos_ivorVectorTableEntry0 .. rtos_ivorVectorTableEntry15 (thereof in use 0..11)
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


/*
 * MPC5748G: Different to other z4/z7 cores, it doesn't have distinct pointers to
 * distinct exceptions but it makes use a solid table of handlers, where an entry has a
 * size of 16 Byte. The IVOR table has an alignment of 8 Bit.
 */
    .section    .text.ivorTable.rtos
    .global     rtos_ivorVectorTableRTOS
    .p2align    8
rtos_ivorVectorTableRTOS:


/**
 *   @func rtos_ivor0Handler
 * IVOR table entry and exception handler IVOR #0 for the Critical Input interrupt.\n
 *   An IVOR #0 handler is not required. This exception cannot be caused by user mode code;
 * it's a hardware asserted interrupt or may be used by the debug engine, which is not
 * enabled in HID0 (CRM, 2.4.11, p. 48ff). See CRM, 7.7.1, p. 489 and 7.1, Table 7-2, p.
 * 478ff.
/// @todo CRM references still go into MPC5775 docs
 * See RM, section 62.8.5.1 on page 3130.
 */
    .global     rtos_ivorVectorTableEntry0  /* Note, it is not required to make this symbol
                                               global. However it is handy to see the traps
                                               in the application map file and this is why
                                               we do so for all traps. */
    .p2align    4
rtos_ivorVectorTableEntry0:
    se_b        rtos_ivorVectorTableEntry0  /* Critical Input interrupt handler */ 


/**
 *   @func rtos_ivorVectorTableEntry1
 * Exception handler IVOR1 for the Machine check / (NMI) interrupt.
 */
    .global     rtos_ivorVectorTableEntry1
    .extern     rtos_ivor1Handler
    .p2align    4
rtos_ivorVectorTableEntry1:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions. */
    mbar
    e_b         rtos_ivor1Handler   /* Machine check / (NMI) interrupt handler */
    .global     rtos_illegalInstruction
rtos_illegalInstruction:
    se_illegal  /* We place an illegal instuction here at an anyway unused code location. */
    se_illegal  /* The instruction is used for testing and doesn't care otherwise. */
    se_blr

/**
 *   @func rtos_ivorVectorTableEntry2
 * Exception handler IVOR2 for the Data Storage interrupt. This trap is taken if the MMU
 * signals an unpermitted data access.
 */
    .global     rtos_ivorVectorTableEntry2
    .extern     rtos_ivor2Handler
    .p2align    4
rtos_ivorVectorTableEntry2:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         Most important: If there were pending MPU exceptions then the MC handler, IVOR #1,
       will surely preempt us here at this particular instruction. This is the way it'll
       recognize the double-exception situation. */
    mbar
    e_b         rtos_ivor2Handler   /* Data Storage interrupt handler */


/**
 *   @func rtos_ivorVectorTableEntry3
 * Exception handler IVOR3 for the Instruction Storage interrupt. This trap is taken if
 * the MMU signals an unpermitted instruction fetch.
 */
    .global     rtos_ivorVectorTableEntry3
    .extern     rtos_ivor3Handler
    .p2align    4
rtos_ivorVectorTableEntry3:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         Most important: If there were pending MPU exceptions then the MC handler, IVOR #1,
       will surely preempt us here at this particular instruction. This is the way it'll
       recognize the double-exception situation. */
    mbar
    e_b         rtos_ivor3Handler   /* Instruction Storage interrupt handler */


/**
 *   @func rtos_ivorVectorTableEntry4
 * Exception handler IVOR4 for the External Input interrupt. See RM, section
 * 62.8.5.5 on page 3133.
 */
    .global     rtos_ivorVectorTableEntry4
    .extern     rtos_ivor4Handler
    .p2align    4
rtos_ivorVectorTableEntry4:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         If there were pending MPU exceptions then the MC handler, IVOR #1, will surely
       preempt us here at this particular instruction. This is the way it'll recognize the
       double-exception situation.
         The memory barrier is required for a second reason. If the IVOR #4 handler
       preempts a user process then it will soon change the process ID in the CPU to the
       kernel process. At the time of a store, the store buffers of the z4 core record the
       CPU problem state but not the PID (see CRM z7, section 11.9, p. 613). We need to flush
       all of the store buffers prior to altering PID0 so that all stores seen by the MPU
       still happen with the old process ID. Without the mbar instruction, we would face
       MPU exceptions from the last recent, valid user process stores here in the kernel,
       because the MPU would false relate the stores to problem state "user" but process ID
       "kernel" - which is a forbidden combination. */
    mbar
    e_b         rtos_ivor4Handler       /* External Input interrupt handler */



/**
 *   @func rtos_ivorVectorTableEntry5
 * Exception handler IVOR5 for the Alignment interrupt.
 */
    .global     rtos_ivorVectorTableEntry5
    .extern     rtos_ivor5Handler
    .p2align    4
rtos_ivorVectorTableEntry5:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         Most important: If there were pending MPU exceptions then the MC handler, IVOR #1,
       will surely preempt us here at this particular instruction. This is the way it'll
       recognize the double-exception situation. */
    mbar
    e_b         rtos_ivor5Handler   /* Alignment interrupt handler */


/**
 *   @func rtos_ivorVectorTableEntry6
 * Exception handler IVOR6 for the Program interrupt.
 */
    .global     rtos_ivorVectorTableEntry6
    .extern     rtos_ivor6Handler
    .p2align    4
rtos_ivorVectorTableEntry6:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         Most important: If there were pending MPU exceptions then the MC handler, IVOR #1,
       will surely preempt us here at this particular instruction. This is the way it'll
       recognize the double-exception situation. */
    mbar
    e_b         rtos_ivor6Handler   /* Program interrupt handler */


/**
 *   @func rtos_ivorVectorTableEntry7
 * Exception handler IVOR7 for the Performance Monitor interrupt. See RM, section
 * 62.8.5.8.
 */
    .global     rtos_ivorVectorTableEntry7
    .p2align    4
rtos_ivorVectorTableEntry7:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         Most important: If there were pending MPU exceptions then the MC handler, IVOR #1,
       will surely preempt us here at this particular instruction. This is the way it'll
       recognize the double-exception situation. */
    mbar
    se_b        rtos_ivorVectorTableEntry7  /* Performance Monitor interrupt handler */


/**
 *   @func rtos_ivorVectorTableEntry8
 * Exception handler IVOR8 for the System Call interrupt.
 */
    .global     rtos_ivorVectorTableEntry8
    .extern     rtos_ivor8Handler
    .p2align    4
rtos_ivorVectorTableEntry8:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         If there were pending MPU exceptions then the MC handler, IVOR #1, will surely
       preempt us here at this particular instruction. This is the way it'll recognize the
       double-exception situation.
         The memory barrier is required for a second reason. Depending on the kind of
       system call, the IVOR #8 handler may soon change the process ID in the CPU to the
       kernel process. At the time of a store, the store buffers of the z4 core record the
       CPU problem state but not the PID (see CRM z7, section 11.9, p. 613). We need to flush
       all of the store buffers prior to altering PID0 so that all stores seen by the MPU
       still happen with the old process ID. Without the mbar instruction, we would face
       MPU exceptions from the last recent, valid user process stores here in the kernel,
       because the MPU would false relate the stores to problem state "user" but process ID
       "kernel" - which is a forbidden combination. */
    mbar
    e_b         rtos_ivor8Handler   /* System Call interrupt handler */


/// @todo Consider making this implementation dependent on HID0 settings as done for MPC5775
/**
 *   @func rtos_ivorVectorTableEntry9
 * Exception handler IVOR9 for the Debug interrupt.
 */
    .global     rtos_ivorVectorTableEntry9
    .extern     rtos_ivor9Handler
    .p2align    4
rtos_ivorVectorTableEntry9:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         Most important: If there were pending MPU exceptions then the MC handler, IVOR #1,
       will surely preempt us here at this particular instruction. This is the way it'll
       recognize the double-exception situation. */
    mbar
    e_b         rtos_ivor9Handler  /* Debug interrupt handler */


/**
 *   @func rtos_ivorVectorTableEntry10
 * Exception handler IVOR10 for the Embedded Floating-point Data interrupt. See RM
 * section 62.8.5.11.
 */
    .global     rtos_ivorVectorTableEntry10
    .extern     rtos_ivor10And11Handler
    .p2align    4
rtos_ivorVectorTableEntry10:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         Most important: If there were pending MPU exceptions then the MC handler, IVOR #1,
       will surely preempt us here at this particular instruction. This is the way it'll
       recognize the double-exception situation. */
    mbar
    e_b         rtos_ivor10And11Handler /* Embedded Floating-point Data interrupt handler */


/**
 *   @func rtos_ivorVectorTableEntry11
 * Exception handler IVOR11 for the Embedded Floating-point Round interrupt. See RM
 * section 62.8.5.12.
 */
    .global     rtos_ivorVectorTableEntry11
    .p2align    4
rtos_ivorVectorTableEntry11:
    /* We place a memory barrier here to flush all store buffers. All possible MPU
       exceptions, which are related to the buffer stores will have been raised after the
       instruction and the code inside the handler remains free of further delayed MPU
       exceptions.
         Most important: If there were pending MPU exceptions then the MC handler, IVOR #1,
       will surely preempt us here at this particular instruction. This is the way it'll
       recognize the double-exception situation. */
    mbar
    e_b         rtos_ivor10And11Handler /* Embedded Floating-point Round interrupt handler */


/**
 *   @func rtos_ivorVectorTableEntry12
 * Unused exception handler IVOR12.
 */
    .global     rtos_ivorVectorTableEntry12
    .p2align    4
rtos_ivorVectorTableEntry12:
    mbar
    se_b        rtos_ivorVectorTableEntry12


/**
 *   @func rtos_ivorVectorTableEntry13
 * Unused exception handler IVOR13.
 */
    .global     rtos_ivorVectorTableEntry13
    .p2align    4
rtos_ivorVectorTableEntry13:
    mbar
    se_b        rtos_ivorVectorTableEntry13


/**
 *   @func rtos_ivorVectorTableEntry14
 * Unused exception handler IVOR14.
 */
    .global     rtos_ivorVectorTableEntry14
    .p2align    4
rtos_ivorVectorTableEntry14:
    mbar
    se_b        rtos_ivorVectorTableEntry14


/**
 *   @func rtos_ivorVectorTableEntry15
 * Unused exception handler IVOR15.
 */
    .global     rtos_ivorVectorTableEntry15
    .p2align    4
rtos_ivorVectorTableEntry15:
    mbar
    se_b        rtos_ivorVectorTableEntry15

/* End of IVOR exception handlers 0..15 (thereof in use 0..11) for cores running the RTOS */

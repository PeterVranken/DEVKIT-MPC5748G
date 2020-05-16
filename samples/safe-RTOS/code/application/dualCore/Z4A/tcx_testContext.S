/**
 * @file tcx_testContext.S
 * Test file: A task that sets most of the CPU user registers and later checks the contents
 * to see if they are still okay after a context switch.
 *
 * Copyright (C) 2018-2019 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   tcx_testContext
 * Local functions
 *   fillRegisters
 *   testRegisters
 */

#ifndef __VLE__
# error This file is intended for compilation for VLE instruction set only
#endif

/*
 * Include files
 */

#include "rtos_ivorHandler.h"


/*
 * Defines
 */


/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
    .section    .sdata.P1.tcx_cntTestLoops
    .global     tcx_cntTestLoops
txt_startValue:
    .dc.l       0xffff0000  /* Because of upper XER bits we don't start with test pattern 0 */
tcx_cntTestLoops:
    .dc.l       0
tcx_cntLoopsPerTask: 
    .dc.l       0
tcx_waitTimePerCycleInUS:    
    .dc.l       0


/*
 * Function implementation
 */


/**
 *   @func fillRegisters
 * Fill all accessible registers with the value in r3.
 */
    .section .text
    .balign  2

#define SIZE_OF_STACKFRAME  0

fillRegisters:
    se_mr       r0, r3
    se_addi     r3, 1
    mtxer       r3
    se_addi     r3, 1
    mtctr       r3
    se_addi     r3, 1
    se_mr       r5, r3
    se_addi     r3, 1
    se_mr       r6, r3
    se_addi     r3, 1
    se_mr       r7, r3
    se_addi     r3, 1
    se_mtar     r8, r3
    se_addi     r3, 1
    se_mtar     r9, r3
    se_addi     r3, 1
    se_mtar     r10, r3
    se_addi     r3, 1
    se_mtar     r11, r3
    se_addi     r3, 1
    se_mtar     r12, r3
    se_addi     r3, 1
    se_mtar     r14, r3
    se_addi     r3, 1
    se_mtar     r15, r3
    se_addi     r3, 1
    se_mtar     r16, r3
    se_addi     r3, 1
    se_mtar     r17, r3
    se_addi     r3, 1
    se_mtar     r18, r3
    se_addi     r3, 1
    se_mtar     r19, r3
    se_addi     r3, 1
    se_mtar     r20, r3
    se_addi     r3, 1
    se_mtar     r21, r3
    se_addi     r3, 1
    se_mtar     r22, r3
    se_addi     r3, 1
    se_mtar     r23, r3
    se_addi     r3, 1
    se_mr       r24, r3
    se_addi     r3, 1
    se_mr       r25, r3
    se_addi     r3, 1
    se_mr       r26, r3
    se_addi     r3, 1
    se_mr       r27, r3
    se_addi     r3, 1
    se_mr       r28, r3
    se_addi     r3, 1
    se_mr       r29, r3
    se_addi     r3, 1
    se_mr       r30, r3
    se_addi     r3, 1
    se_mr       r31, r3
    se_addi     r3, 1
    
    se_blr

/* End of fillRegisters */




/**
 *   @func testRegisters
 * Compare all accessible registers with the value in r3. Any deviation is reported as an
 * error. Error reporting is done by entering an infinite loop.
 */
    .section    .text
    .globl      tcx_testFailed
    .extern     rtos_systemCall
    .balign     2
#define SIZE_OF_STACKFRAME  0

testRegisters:
    cmplw       cr0, r0, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
    
    mfxer       r0
    xor         r0, r0, r3
    e_rlwinm    r0, r0, 0, 25, 2 /* Mask all bits in use (0xe000007f) and compare with zero */
    e_cmplwi    cr0, r0, 0
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    mfctr       r0
    cmplw       cr0, r0, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r5, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r6, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r7, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r8, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r9, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r10, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r11, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r12, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r14, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r15, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r16, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r17, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r18, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r19, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r20, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r21, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r22, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r23, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r24, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r25, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r26, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r27, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r28, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r29, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r30, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
                
    cmplw       cr0, r31, r3
    se_bne      tcx_testFailed
    se_addi     r3, 1
    
    se_blr

tcx_testFailed:
    /* We use the implementation of the assert macro to report the problem. This doesn't
       work in PRODUCTION compilation: The code is not compiled, the system call index is
       invalid and the kernel will abort the task execution and count a process error
       rather than halting the system. It's effectively not possible to halt the software
       in PRODUCTION compilation. Even an infinite loop would just block this task, and
       thus any of same of lower priority, and only if no deadline monitoring is
       configured.
         However, even in PRODUCTION compilation, we have some kind of error reporting
       through the process error counts. */
    se_li       r3, RTOS_SYSCALL_ASSERT_FUNC
    e_lis       r4, tr_fileName@ha
    e_add16i    r4, r4, tr_fileName@l
    e_li        r5, __LINE__
    e_lis       r6, tr_funcName@ha
    e_add16i    r6, r6, tr_funcName@l
    e_lis       r7, tr_expression@ha
    e_add16i    r7, r7, tr_expression@l
    se_sc
    se_b        .       /* The system call won't actually return. */

    .section    .rodata
tr_fileName:
    .string     __FILE__
tr_funcName:
    .string     "testRegisters"
tr_expression:
    .string     "Register comparison failed"

#undef SIZE_OF_STACKFRAME
/* End of testRegisters */




/**
 *   @func tcx_testContext
 * This function writes specific values to most accessible registers of the CPU, does busy
 * wait for a while - to let the scheduler make a context switch - and checks the register
 * contents. This is done the given number of times, the function returns after \a noCycles
 * times \a waitTimePerCycleInUS Microseconds consumption of CPU. (It produces full CPU
 * load during operation.) The time till return depends on the time it is preempted by
 * other tasks.
 *   @param noCycles
 * r3 contains the number of test cycles to run.
 *   @param waitTimePerCycleInUS
 * r4 contains the busy wait time applied in each of the cycles in Microseconds.
 */
    .section    .text
    .globl      tcx_testContext
    .balign     2
#define SIZE_OF_STACKFRAME  16
#define O_R3                8
tcx_testContext:
    e_stwu      sp, -SIZE_OF_STACKFRAME(sp)
    se_mflr     r0
    se_stw      r0, (SIZE_OF_STACKFRAME+4)(sp)
    
    /* Initialize cycle counter and wait time per cycle for this task invocation. */
    e_stw       r3, tcx_cntLoopsPerTask@sda21(%r0)
    e_stw       r4, tcx_waitTimePerCycleInUS@sda21(%r0)

    /* To give time for a context switch we use del_delayMicroseconds as an external
       funtion. It clobbers the volatile GPR 3,4, the LR and CR0. These registers must
       therefore not be tested. We can use them as work registers, too. */
    e_lwz       r3, txt_startValue@sda21(%r0)
    se_stw      r3, O_R3(sp)
    
tc_mainLoop:
    se_lwz      r3, O_R3(sp)
    e_bl        fillRegisters
                
    e_lwz       r3, tcx_waitTimePerCycleInUS@sda21(%r0)
    e_bl        del_delayMicroseconds
                
    se_lwz      r3, O_R3(sp)
    e_bl        testRegisters
    se_stw      r3, O_R3(sp)
    
#if 0
    /* Do a system call. We use a quite useless one which always returns without demanding
       a context switch. */
    se_li       r3, RTOS_IDX_SYS_CALL_TEST_AND_DECREMENT  /* idxSysCall */
    se_li       r4, 1   /* idxSemaphore. Don't use 0, which is in use for LED access control */
    e_bl        int_systemCall
    
    /* Now do a system call, which doesn't return immediately, but which demands a context
       switch. */
    se_li       r3, RTOS_IDX_SYS_CALL_SWITCH_CONTEXT  /* idxSysCall: cxs_switchContext */
    e_lis       r4, -2@h    /* signalToResumedContext */
    e_or2i      r4, -2@l    /* signalToResumedContext */
    e_bl        int_systemCall
#endif

    /* Cycle completed, ok, count it as success report. */
    e_lwz       r3, tcx_cntTestLoops@sda21(%r0)
    se_addi     r3, 1
    e_stw       r3, tcx_cntTestLoops@sda21(%r0)
    
    /* Count cycles in this call of the task function. */
    e_lwz       r3, tcx_cntLoopsPerTask@sda21(%r0)
    se_cmpli    r3, 1
    se_subi     r3, 1 
    e_stw       r3, tcx_cntLoopsPerTask@sda21(%r0)
    se_bgt      tc_mainLoop
    
    /* Continue in next invocation with subsequent test patterns. */
    se_lwz      r3, O_R3(sp)
    e_stw       r3, txt_startValue@sda21(%r0)

    /* Total number of cycles since startup is function result. */
    e_lwz       r3, tcx_cntTestLoops@sda21(%r0)
    
    /* Destroy stack frame and return. */
    se_lwz      r0, (SIZE_OF_STACKFRAME+4)(sp)
    se_mtlr     r0
    e_la        sp, SIZE_OF_STACKFRAME(sp)
    se_blr

#undef O_R3
#undef SIZE_OF_STACKFRAME
/* End of tcx_testContext */


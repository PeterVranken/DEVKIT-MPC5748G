/**
 * @file assert_sysCall.S
 * Assert function: Implementation as basic system call handler. The basic type is required
 * in order to make the system call work well in all contexts, the OS contexts in
 * supervisor mode or the normal user tasks.
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
/* Module interface
 * Local functions
 */

#ifndef __VLE__
# error This file is intended for compilation for VLE instruction set only
#endif

/* The entire contents of this file are not required in PRODUCTION compilation. */
#ifdef DEBUG

/*
 * Include files
 */

#include "assert_config.h"


/*
 * Defines
 */



/** SPR index of process ID. */
#define SPR_PID0    48


#if !(ASSERT_FAILURE_BEHAVIOR == ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_FIRST \
      ||  ASSERT_FAILURE_BEHAVIOR == ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_LAST \
      ||  ASSERT_FAILURE_BEHAVIOR == ASSERT_FAILURE_BEHAVIOR_HALT_SW \
     )
# error Invalid behavior chosen for assert function
#endif


/*
 * External function declarations
 */


/*
 * Data declarations
 */

    .extern     assert_assertionFired, assert_fileName, assert_funcName
    .extern     assert_line, assert_expression

/*
 * Function implementation
 */

/**
 *   @func assert_scBscHdlr_assert_func
 * Implementation of the assert function, which is called by the C assert macro if the
 * condition fails. The implementation here is made as basic system call handler. This
 * permits offering the service to user and operating system code.\n
 *   For kernel code it's soon decided how to proceed: A violated invariant condition will
 * halt the SW execution as traditionally the case for the assert macro.\n
 *   For user code we could halt the SW but this impacts the SW behavior such that DEBUG
 * compiled SW is no longer testable with respect to fault handling. It's unavoidable that
 * failing, straying code (e.g. due to failure injection) could enter the system call by
 * accident. It will halt the SW execution (and report wrong fault information through the
 * stored assert information, filename, line number, etc.) rather then running through the
 * fault handling procedures established in the operating system. Fault handling would
 * become untestable by principle.\n
 *   On the other hand is halting the SW still very useful for all early, "normal" testing,
 * when the basic SW functionality is put to operation and initially tested. A logical
 * fault halts execution and the stored assert information points directly to the violated
 * invariant.\n
 *   We offer two behaviors of the assert function. User code, which enters the assert
 * function may halt the user code execution or it just stores the assert information,
 * counts the occurance and returns (to the failing user task). The choice needs to be made
 * at compile time, see macro #ASSERT_FAILURE_BEHAVIOR. Note, that an failing assertion in
 * the supervisor code will always halt the code execution.
 *   @param fileName
 * On entry, r4 holds a pointer to the constant string with the name of source, which the
 * failing assertion is located in.
 *   @param line
 * On entry, r5 holds a pointer to the constant string with the line number, which the
 * failing assertion is located at.
 *   @param funcName
 * On entry, r6 holds a pointer to the constant string with the name of C function, which
 * the failing assertion is located in.
 *   @param expression
 * On entry, r7 holds a pointer to the constant string with the failing expression in the
 * assertion.
 *   @remark
 * This is the implementation of a system call handler. The code must not be invoked
 * directly. The system call handler is compliant with the basic conformance class. It is
 * executed with EE=0 and must not rely on sp, r2 and r13
 */
    .section    .text.ivor
    .globl      assert_scBscHdlr_assert_func
    .align      2

assert_scBscHdlr_assert_func:
    /* Globaly store fault location related information, file name, line number, etc.,
       provided by the C assert macro. The information is passed in as function arguments
       in r4, r5, etc. */
    e_lis       r3, assert_noOccurances@ha
    e_lwz       r0, assert_noOccurances@l(r3)
    se_addi     r0, 1
    se_cmpli    r0, 1
    se_blt      ass_saturateOcc     /* Don't store increment if we wrap around */
    e_stw       r0, assert_noOccurances@l(r3)
ass_saturateOcc:

#if ASSERT_FAILURE_BEHAVIOR == ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_FIRST
    se_bne      ass_noUpdErrInfo
#endif
    e_lis       r3, assert_fileName@ha
    e_stw       r4, assert_fileName@l(r3)
    e_lis       r3, assert_line@ha
    e_stw       r5, assert_line@l(r3)
    e_lis       r3, assert_funcName@ha
    e_stw       r6, assert_funcName@l(r3)
    e_lis       r3, assert_expression@ha
    e_stw       r7, assert_expression@l(r3)
ass_noUpdErrInfo:
    mfspr       r0, SPR_PID0    /* PID is not changed prior to entry in basic handler */
    e_lis       r3, assert_PID@ha
    e_lbz       r4, assert_PID@l(r3)    /* r4: PID stored so far, can initially be 0xff */
    se_extsb    r4                      /* r4: PID so far as int32_t, range [-1 .. 4] */
    se_cmp      r0, r4                  /* Signed compare with PID from this assertion */
    se_ble      ass_noUpdPID            /* Don't store if not greater */
    e_stb       r0, assert_PID@l(r3)    /* Store new greatest seen PID. */
ass_noUpdPID:

    /* For testability of failure handling of SW, we must not halt a user task. We inspect
       the machine status of the calling context if testability is requested. */
#if ASSERT_FAILURE_BEHAVIOR == ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_FIRST \
    ||  ASSERT_FAILURE_BEHAVIOR == ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_LAST

    mfsrr1      r0                  /* Load MSR of system calling process */
    se_btsti    r0, 17              /* Test bit "problem state" */
    se_bne      ass_contUserTask    /* if(Problem state == user) return; */

#endif

    /* MSR[EE] = 0 is always granted on entry into a basic system call handler and all
       which remains is entering an infinite loop. */
    .extern     assert_infiniteLoopAfterCaughtError /* Just to have it in the map file. */
assert_infiniteLoopAfterCaughtError:
    se_b        assert_infiniteLoopAfterCaughtError

    /* Return to the user task, which had made the system call. */
ass_contUserTask:
    se_li       r3, 0
    se_rfi

/* End of assert_scBscHdlr_assert_func */


#endif /* DEBUG */

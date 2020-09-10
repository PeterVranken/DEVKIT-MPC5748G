#ifndef ASSERT_CONFIG_INCLUDED
#define ASSERT_CONFIG_INCLUDED
/**
 * @file assert_config.h
 * Compile time configuration of behavior of the C assert macro.
 *
 * Copyright (C) 2019 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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


/*
 * Defines
 */

#ifndef ASSERT_FAILURE_BEHAVIOR
/** The code that implements the function called from the C assert macro, if its
    condition is \a false, can be compiled in different ways. It can halt the SW execution
    immediately or only count the occurances of \a false conditions and continue. The
    decision has a major impact on the testability of failure handling.\n
      One out of #ASSERT_FAILURE_BEHAVIOR_HALT_SW,
    #ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_FIRST or
    #ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_LAST is assigned to this define. See
    these other macros for more details. */
# define ASSERT_FAILURE_BEHAVIOR     ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_FIRST
#endif


/** Traditional behavior of assert: The SW execution is halted at the first occurrence of an
    assert macro with \a false condition.\n
      This behavior can be chosen when software is functionally tested, which is expected to
    be error free.\n
      This behavior must not be used if the software's failure handling is tested, e.g. by
    purposely injected errors. If this behavior is chosen then the fault handling system of
    the RTOS is by principle non-trustable. There's a significant chance that the software
    halts because of an accidental, unintended entry of a straying task into the assert
    system call.\n
      See #ASSERT_FAILURE_BEHAVIOR, too. */
#define ASSERT_FAILURE_BEHAVIOR_HALT_SW                             1

/** "Safe" behavior of assert: The occurrence of assert macros with \a false condition is
    counted. The assert information is stored only for the very first occurrence of an
    assert macro with \a false condition. The SW execution is halted if the assert macro is
    placed in operating system code but continues if it is placed in user task code.
      @remark This behavior can be used with SW compilations, which are to be used for
    testing of the software's failure handling capabilities, if failure exceptions are
    expected and proper catching and processing them is subject of the test.
      @remark The C assert function is declared _Noreturn and we cannot continue the user
    code after the C assert macro by just returning from the assert function. Instead, the
    assert function enters an infinite loop. The promise to continue the SW execution is
    held in this way:\n
      The user task spins in the loop either forever or until a specified time budget is
    exhausted. In either case, the problem is reported by the kernel. Forever spinning
    is reported as activation losses of the according event, time budget exhausted as
    process error #RTOS_ERR_PRC_DEADLINE. Anyway, kernel and the tasks of higher
    priority are not impacted. */
#define ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_FIRST         2

/** "Safe" behavior of assert: The occurrence of assert macros with \a false condition is
    counted. The assert information is stored for the last recent occurrence of an assert
    macro with \a false condition. The SW execution is halted if the assert macro is placed
    in operating system code but continued behind the assert macro if it is placed in user
    task code.\n
      Note, the remarks concerning use case and continuation of code execution, made above
    for behavior #ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_FIRST, do hold for this
    behavior, too. */
#define ASSERT_FAILURE_BEHAVIOR_CONTINUE_SW_AND_STORE_LAST          3


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



#endif  /* ASSERT_CONFIG_INCLUDED */

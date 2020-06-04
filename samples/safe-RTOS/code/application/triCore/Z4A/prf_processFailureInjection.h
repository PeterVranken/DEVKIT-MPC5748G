#ifndef PRF_PROCESSFAILUREINJECTION_INCLUDED
#define PRF_PROCESSFAILUREINJECTION_INCLUDED
/**
 * @file prf_processFailureInjection.h
 * Definition of global interface of module prf_processFailureInjection.c
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

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */

/** Some test cases hinder the code from debugging. The likelihood of hitting an se_illegal
    instruction is high when executing code at arbitrary locations. This instruction makes
    the debugger unconditionally break, when the debugger is connected, and program flow is
    impossible.
      This switch enables code debugging. If the switch is set to 1 then all those test
    cases are switched off, which disable debugging. This switch overrides the otherwise
    made selection of test cases. */
#ifdef DEBUG
# define PRF_DISABLE_ALL_TEST_CASES_THAT_DISABLE_DEBUGGING       1
#else
# define PRF_DISABLE_ALL_TEST_CASES_THAT_DISABLE_DEBUGGING       0
#endif
  

/* All test cases can be enabled or disabled. The debugger cannot be used anymore if some
   of the test cases are enabled and due to the frequent appearance of illegal instructions
   in the code flow. Therefore it is important to have the possibility to selectively
   disable those test cases during development. */
#define PRF_ENA_TC_PRF_KOF_NO_FAILURE                           1
#define PRF_ENA_TC_PRF_KOF_JUMP_TO_RESET_VECTOR                 1
#define PRF_ENA_TC_PRF_KOF_JUMP_TO_ILLEGAL_INSTR                1
#define PRF_ENA_TC_PRF_KOF_USER_TASK_ERROR                      1
#define PRF_ENA_TC_PRF_KOF_PRIVILEGED_INSTR                     1
#define PRF_ENA_TC_PRF_KOF_CALL_OS_API                          1
#define PRF_ENA_TC_PRF_KOF_TRIGGER_UNAVAILABLE_EVENT            1
#define PRF_ENA_TC_PRF_KOF_WRITE_OS_DATA                        1
#define PRF_ENA_TC_PRF_KOF_WRITE_OTHER_PROC_DATA                1
#define PRF_ENA_TC_PRF_KOF_WRITE_ROM                            1
#define PRF_ENA_TC_PRF_KOF_WRITE_PERIPHERAL                     1
#define PRF_ENA_TC_PRF_KOF_READ_PERIPHERAL                      1
#define PRF_ENA_TC_PRF_KOF_INFINITE_LOOP                        1
#define PRF_ENA_TC_PRF_KOF_MISALIGNED_WRITE                     1
#define PRF_ENA_TC_PRF_KOF_MISALIGNED_READ                      1
#define PRF_ENA_TC_PRF_KOF_STACK_OVERFLOW                       1
#define PRF_ENA_TC_PRF_KOF_STACK_CLEAR_BOTTOM                   1
#define PRF_ENA_TC_PRF_KOF_SP_CORRUPT                           1
#define PRF_ENA_TC_PRF_KOF_SP_CORRUPT_AND_WAIT                  1
#define PRF_ENA_TC_PRF_KOF_PRIVILEGED_AND_MPU                   1
#define PRF_ENA_TC_PRF_KOF_READ_SPR                             1
#define PRF_ENA_TC_PRF_KOF_WRITE_SPR                            1
#define PRF_ENA_TC_PRF_KOF_WRITE_SVSP                           1
#define PRF_ENA_TC_PRF_KOF_CLEAR_SDA_PTRS                       1
#define PRF_ENA_TC_PRF_KOF_CLEAR_SDA_PTRS_AND_WAIT              1
#define PRF_ENA_TC_PRF_KOF_MMU_WRITE                            1
#define PRF_ENA_TC_PRF_KOF_MMU_READ                             1
#define PRF_ENA_TC_PRF_KOF_MMU_EXECUTE                          1
#define PRF_ENA_TC_PRF_KOF_MMU_EXECUTE_2                        1
#define PRF_ENA_TC_PRF_KOF_MMU_EXECUTE_PERIPHERAL               1
#define PRF_ENA_TC_PRF_KOF_TRAP                                 1
#define PRF_ENA_TC_PRF_KOF_TLB_INSTR                            1
#define PRF_ENA_TC_PRF_KOF_SPE_INSTR                            1
#define PRF_ENA_TC_PRF_KOF_BOOKE_FPU_INSTR                      1
#define PRF_ENA_TC_PRF_KOF_DCACHE_INSTR                         1
#define PRF_ENA_TC_PRF_KOF_UNDEF_SYS_CALL                       1
#define PRF_ENA_TC_PRF_KOF_RANDOM_WRITE                         1
#define PRF_ENA_TC_PRF_KOF_RANDOM_READ                          1
#define PRF_ENA_TC_PRF_KOF_RANDOM_JUMP                          1
#define PRF_ENA_TC_PRF_KOF_MPU_EXC_BEFORE_SC                    1
#define PRF_ENA_TC_PRF_KOF_INVALID_CRIT_SEC                     1
#define PRF_ENA_TC_PRF_KOF_LEAVE_CRIT_SEC                       1
#define PRF_ENA_TC_PRF_KOF_INVOKE_RTOS_OS_RUN_TASK              1
#define PRF_ENA_TC_PRF_KOF_INVOKE_RTOS_RUN_TASK_NO_PERMIT       1
#define PRF_ENA_TC_PRF_KOF_INVOKE_IVR_SYSTEM_CALL_BAD_ARGUMENT  1
#define PRF_ENA_TC_PRF_KOF_SYSTEM_CALL_ALL_ARGUMENTS_OKAY       0 /* No failure, are all
                                                                     possible 7 args okay? */
#define PRF_ENA_TC_PRF_KOF_WAIT_INSTR                           1
#define PRF_ENA_TC_PRF_KOF_ENA_FPU_EXC                          1

/// @todo Check debug instructions and potentially add a test case

#if PRF_DISABLE_ALL_TEST_CASES_THAT_DISABLE_DEBUGGING == 1
# undef PRF_ENA_TC_PRF_KOF_JUMP_TO_ILLEGAL_INSTR
# define PRF_ENA_TC_PRF_KOF_JUMP_TO_ILLEGAL_INSTR               0
# undef PRF_ENA_TC_PRF_KOF_STACK_OVERFLOW
# define PRF_ENA_TC_PRF_KOF_STACK_OVERFLOW                      0
# undef PRF_ENA_TC_PRF_KOF_STACK_CLEAR_BOTTOM
# define PRF_ENA_TC_PRF_KOF_STACK_CLEAR_BOTTOM                  0
# undef PRF_ENA_TC_PRF_KOF_SP_CORRUPT
# define PRF_ENA_TC_PRF_KOF_SP_CORRUPT                          0
# undef PRF_ENA_TC_PRF_KOF_SP_CORRUPT_AND_WAIT
# define PRF_ENA_TC_PRF_KOF_SP_CORRUPT_AND_WAIT                 0
# undef PRF_ENA_TC_PRF_KOF_RANDOM_JUMP
# define PRF_ENA_TC_PRF_KOF_RANDOM_JUMP                         0
#endif


/*
 * Global type definitions
 */

/** The type of the command to inject the next error. Used in communication between the
    tasks prs_taskCommandError and prf_taskInjectError. */
typedef struct prf_cmdFailure_t
{
    /** Which error? */
    enum prf_kindOfFailure_t
    {
#if PRF_ENA_TC_PRF_KOF_JUMP_TO_RESET_VECTOR == 1
        prf_kof_jumpToResetVector,                      /* 0 */
#endif
#if PRF_ENA_TC_PRF_KOF_JUMP_TO_ILLEGAL_INSTR == 1
        prf_kof_jumpToIllegalInstr,
#endif
#if PRF_ENA_TC_PRF_KOF_NO_FAILURE == 1
        prf_kof_noFailure,
#else
# error Test case "no failure" needs to be always enabled
#endif
#if PRF_ENA_TC_PRF_KOF_USER_TASK_ERROR == 1
        prf_kof_userTaskError,
#endif
#if PRF_ENA_TC_PRF_KOF_PRIVILEGED_INSTR == 1
        prf_kof_privilegedInstr,
#endif
#if PRF_ENA_TC_PRF_KOF_CALL_OS_API == 1
        prf_kof_callOsAPI,
#endif
#if PRF_ENA_TC_PRF_KOF_TRIGGER_UNAVAILABLE_EVENT == 1
        prf_kof_triggerUnavailableEvent,
#endif
#if PRF_ENA_TC_PRF_KOF_WRITE_OS_DATA == 1
        prf_kof_writeOsData,
#endif
#if PRF_ENA_TC_PRF_KOF_WRITE_OTHER_PROC_DATA == 1
        prf_kof_writeOtherProcData,
#endif
#if PRF_ENA_TC_PRF_KOF_WRITE_ROM == 1
        prf_kof_writeROM,
#endif
#if PRF_ENA_TC_PRF_KOF_WRITE_PERIPHERAL == 1
        prf_kof_writePeripheral,
#endif
#if PRF_ENA_TC_PRF_KOF_READ_PERIPHERAL == 1
        prf_kof_readPeripheral,
#endif
#if PRF_ENA_TC_PRF_KOF_INFINITE_LOOP == 1
        prf_kof_infiniteLoop,
#endif
#if PRF_ENA_TC_PRF_KOF_MISALIGNED_WRITE == 1
        prf_kof_misalignedWrite,
#endif
#if PRF_ENA_TC_PRF_KOF_MISALIGNED_READ == 1
        prf_kof_misalignedRead,
#endif
#if PRF_ENA_TC_PRF_KOF_STACK_OVERFLOW == 1
        prf_kof_stackOverflow,
#endif
#if PRF_ENA_TC_PRF_KOF_STACK_CLEAR_BOTTOM == 1
        prf_kof_stackClearBottom,
#endif
#if PRF_ENA_TC_PRF_KOF_SP_CORRUPT == 1
        prf_kof_spCorrupt,
#endif
#if PRF_ENA_TC_PRF_KOF_SP_CORRUPT_AND_WAIT == 1
        prf_kof_spCorruptAndWait,
#endif
#if PRF_ENA_TC_PRF_KOF_PRIVILEGED_AND_MPU == 1
        prf_kof_privilegedAndMPU,
#endif
#if PRF_ENA_TC_PRF_KOF_READ_SPR == 1
        prf_kof_readSPR,
#endif
#if PRF_ENA_TC_PRF_KOF_WRITE_SPR == 1
        prf_kof_writeSPR,
#endif
#if PRF_ENA_TC_PRF_KOF_WRITE_SVSP == 1
        prf_kof_writeSVSP,
#endif
#if PRF_ENA_TC_PRF_KOF_CLEAR_SDA_PTRS == 1
        prf_kof_clearSDAPtrs,
#endif
#if PRF_ENA_TC_PRF_KOF_CLEAR_SDA_PTRS_AND_WAIT == 1
        prf_kof_clearSDAPtrsAndWait,
#endif
#if PRF_ENA_TC_PRF_KOF_MMU_WRITE == 1
        prf_kof_MMUWrite,
#endif
#if PRF_ENA_TC_PRF_KOF_MMU_READ == 1
        prf_kof_MMURead,
#endif
#if PRF_ENA_TC_PRF_KOF_MMU_EXECUTE == 1
        prf_kof_MMUExecute,
#endif
#if PRF_ENA_TC_PRF_KOF_MMU_EXECUTE_2 == 1
        prf_kof_MMUExecute2,
#endif
#if PRF_ENA_TC_PRF_KOF_MMU_EXECUTE_PERIPHERAL == 1
        prf_kof_MMUExecutePeripheral,
#endif
#if PRF_ENA_TC_PRF_KOF_TRAP == 1
        prf_kof_trap,
#endif
#if PRF_ENA_TC_PRF_KOF_TLB_INSTR == 1
        prf_kof_tlbInstr,
#endif
#if PRF_ENA_TC_PRF_KOF_SPE_INSTR == 1
        prf_kof_SPEInstr,
#endif
#if PRF_ENA_TC_PRF_KOF_BOOKE_FPU_INSTR == 1
        prf_kof_BookEFPUInstr,
#endif
#if PRF_ENA_TC_PRF_KOF_DCACHE_INSTR == 1
        prf_kof_dCacheInstr,
#endif
#if PRF_ENA_TC_PRF_KOF_UNDEF_SYS_CALL == 1
        prf_kof_undefSysCall,
#endif
#if PRF_ENA_TC_PRF_KOF_RANDOM_WRITE == 1
        prf_kof_randomWrite,        /** 500 times at once, to raise likelihood of bad hit */
#endif
#if PRF_ENA_TC_PRF_KOF_RANDOM_READ == 1
        prf_kof_randomRead,         /** 500 times at once, to raise likelihood of bad hit */
#endif
#if PRF_ENA_TC_PRF_KOF_RANDOM_JUMP == 1
        prf_kof_randomJump,
#endif
#if PRF_ENA_TC_PRF_KOF_MPU_EXC_BEFORE_SC == 1
        prf_kof_mpuExcBeforeSc,
#endif
#if PRF_ENA_TC_PRF_KOF_INVALID_CRIT_SEC == 1
        prf_kof_invalidCritSec,
#endif
#if PRF_ENA_TC_PRF_KOF_LEAVE_CRIT_SEC == 1
        prf_kof_leaveCritSec,
#endif
#if PRF_ENA_TC_PRF_KOF_INVOKE_RTOS_OS_RUN_TASK == 1
        prf_kof_invokeRtosOsRunTask,
#endif
#if PRF_ENA_TC_PRF_KOF_INVOKE_RTOS_RUN_TASK_NO_PERMIT == 1
        prf_kof_invokeRtosRunTaskWithoutPermission,
#endif
#if PRF_ENA_TC_PRF_KOF_INVOKE_IVR_SYSTEM_CALL_BAD_ARGUMENT == 1
        prf_kof_invokeIvrSystemCallBadArgument,
#endif
#if PRF_ENA_TC_PRF_KOF_SYSTEM_CALL_ALL_ARGUMENTS_OKAY == 1
        prf_kof_systemCallAllArgumentsOkay,
#endif
#if PRF_ENA_TC_PRF_KOF_WAIT_INSTR == 1
        prf_kof_waitInstr,
#endif
#if PRF_ENA_TC_PRF_KOF_ENA_FPU_EXC == 1
        prf_kof_enableFpuExceptions,
#endif

        prf_kof_noFailureTypes    /** Total number of defined failure kinds */

    } kindOfFailure;

    /** This error to injected in which stack depth? */
    unsigned int noRecursionsBeforeFailure;

    /** General purpose argument for test case. */
    uint32_t value;

    /** General purpose pointer argument for test cases. */
    uint32_t address;

} prf_cmdFailure_t;



/*
 * Global data declarations
 */

/** The next error to inject. This object is written by task prs_taskCommandError and read
    by prf_taskInjectError. There are no race conditions between these two tasks. */
extern prf_cmdFailure_t SHARED(prf_cmdFailure);


/*
 * Global prototypes
 */

/** User task intenionally producing severe errors, which would crash an unprotected RTOS. */
int32_t prf_taskInjectError(uint32_t PID, uintptr_t taskParam);

/** User task in same process, running at lower priority. */
int32_t prf_task17ms(uint32_t PID, uintptr_t taskParam);

/** User task in same process, running at higher priority. */
int32_t prf_task1ms(uint32_t PID, uintptr_t taskParam);

#endif  /* PRF_PROCESSFAILUREINJECTION_INCLUDED */

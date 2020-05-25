/**
 * @file prs_processSupervisor.c
 * Implementation of task functions. The tasks and their implementation belong into the
 * sphere of the protected user code. They are are defined in the sphere of unprotected
 * operating system code and anything which relates to their configuration cannot be
 * changed anymore by user code.
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
 *   prs_taskCommandError
 *   prs_taskEvaluateError
 *   prs_taskWatchdog
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "typ_types.h"
#include "rtos.h"
#include "gsl_systemLoad.h"
#include "lbd_ledAndButtonDriver.h"
#include "rtos_ivorHandler.h"
#include "syc_systemConfiguration.h"
#include "prf_processFailureInjection.h"
#include "prr_processReporting.h"
#include "prs_processSupervisor.h"


/*
 * Defines
 */


/*
 * Local type definitions
 */

/** The type of the prediction of the consequence of a command to inject the next error. */
typedef struct failureExpectation
{
    /** Which error has been injected? */
    enum prf_kindOfFailure_t kindOfFailure;

    /** Address of operation failure causing operation. */
    uint32_t address;
    
    /** Expected value for test case result. */
    uint32_t expectedValue;

    /** Expected number of process errors resulting from the failure. */
    unsigned int expectedNoProcessFailures;

    /** The injected error can cause subsequent errors due to the other tasks belonging to
        the process - they can be harmed, too. Therefore we don't look at an exact
        increment by one of reported errors but tolerante a few more. */
    unsigned int expectedNoProcessFailuresTolerance;

} failureExpectation_t;


/** Information, which is frozen in the instance of a failing test case. */
typedef struct failureStatus_t
{
    /** The specification of the injected failure which didn't match the expectations. */
    prf_cmdFailure_t cmdFailure;
    
    /** Expected but likely unmatched results of failing test case. */
    failureExpectation_t expectation; 
    
    /** Status of failing test case. */
    prr_failureStatus_t status;
    
    /** Total number of process errors in process syc_pidFailingTasks at the time of the
        "failing failure". */
    uint32_t noTotalTaskFailures;

} failureStatus_t;


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** Counter for test cycles. */
volatile long unsigned int SDATA_PRC_SV(prs_cntTestCycles) = 0;

/** Expected test result. Set by prs_taskCommandError and tested by prs_taskEvaluateError
    after run of failure injection task prf_taskInjectError. */
static failureExpectation_t DATA_PRC_SV(_failureExpectation);

/** Last recent result of system status check. If the failing process has been suspendend
    then it is the status check result, which let to this decision. */
static failureStatus_t BSS_PRC_SV(prs_status);


/*
 * Function implementation
 */

/**
 * Task function, cyclically activated every 10ms.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
int32_t prs_taskCommandError(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    /* Don't inject more errors if an error had already been detected and the process had
       been halted. Return zero, do not count the same situation repeatedly. */
    if(rtos_getNoTotalTaskFailure(syc_pidSupervisor) > 0)
        return 0;

    /* First cycles without any special action to prove basic operation of the software. */
    if(prs_cntTestCycles < 100)
    {
        /* At the beginning we should be error free. */
        if(prs_cntTestCycles == 0)
        {
            prf_cmdFailure = (prf_cmdFailure_t){ .kindOfFailure = prf_kof_noFailure
                                                 , .noRecursionsBeforeFailure = 0
                                                 , .value = 0
                                                 , .address = 0
                                               };
        }

        return 0;
    }

    const unsigned int kindOfFailure = prs_cntTestCycles % (unsigned)prf_kof_noFailureTypes;
    unsigned int stackDepth = prs_cntTestCycles & 64
               , minNoExpectedFailures = 1 /* Default: Immediate failure of injecting task */ 
               , maxNoExpectedFailures = 3 /* Tolerance: The two other tasks of the process
                                              may easily fail, too. */
               , expectedValue = 0;
    uint32_t value = 0
           , address = 0;

    switch(kindOfFailure)
    {
#if PRF_ENA_TC_PRF_KOF_NO_FAILURE == 1
    case prf_kof_noFailure:
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 0;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_USER_TASK_ERROR == 1
    case prf_kof_userTaskError:
        /* Voluntary task termination with error code must be reported as error but it
           still needs to be clean termination without a possibly harmfully affected
           other task. Tolerance is zero. */
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_PRIVILEGED_INSTR == 1
    case prf_kof_privilegedInstr:
        /* Test cases which cause an exception without any danger of destroying some still
           accessible properties like process owned data don't need a tolerance in the
           potential number of process failures. */
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_TRIGGER_UNAVAILABLE_EVENT == 1
    case prf_kof_triggerUnavailableEvent:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_WRITE_OS_DATA == 1
    case prf_kof_writeOsData:
        /* We need to take an address, where we can be sure that no change from other side
           will happen so that we can later double check that the write attempt really
           didn't alter the value. */
        expectedValue = rtos_getNoTotalTaskFailure(syc_pidSupervisor);
        value = ~expectedValue;
        
        /* This is, what we would do in C:
             address = (uint32_t)rtos_getInstancePtr()
                                 ->processAry[syc_pidSupervisor-1].cntTotalTaskFailure;
             Unfortunately, rtos_processAry and its type are not public. The data is
           however shared with the assembly code and we can use the same interfacing size
           and field offset macros to compute the required address exactly as the assembler
           code does. */
        address = (uint32_t)rtos_getInstancePtr()
                  + O_ID_PROC_ARY
                  + SIZE_OF_PROCESS_DESC*(syc_pidSupervisor-1)
                  + O_PDESC_CNTTOT;
        assert(*(uint32_t*)address == expectedValue);
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_WRITE_OTHER_PROC_DATA == 1
    case prf_kof_writeOtherProcData:
        expectedValue = prs_cntTestCycles;
        value = ~expectedValue;
        address = (uint32_t)&prs_cntTestCycles;
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_WRITE_ROM == 1
    case prf_kof_writeROM:
        {
            extern uint8_t ld_romStart[0], ld_romEnd[0];
            address = (uint32_t)ld_romStart + 0x00000100;
            assert(address < (uint32_t)ld_romEnd);
            expectedValue = *(const uint32_t*)address;
            value = ~expectedValue;
            maxNoExpectedFailures = 1;
        }
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_WRITE_PERIPHERAL == 1
    case prf_kof_writePeripheral:
# define INTC_CPR_PRC0      (0xfff48000u+0x8)
        address = INTC_CPR_PRC0;
        value = 15;
        maxNoExpectedFailures = 1;
        break;
# undef INTC_CPR_PRC0
#endif

#if PRF_ENA_TC_PRF_KOF_READ_PERIPHERAL == 1
# define INTC_CPR_PRC0      (0xfff48000u+0x8)
    case prf_kof_readPeripheral:
        address = INTC_CPR_PRC0;
        maxNoExpectedFailures = 1;
        break;
# undef INTC_CPR_PRC0
#endif

#if PRF_ENA_TC_PRF_KOF_INFINITE_LOOP == 1
    case prf_kof_infiniteLoop:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_MISALIGNED_WRITE == 1
    case prf_kof_misalignedWrite:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_MISALIGNED_READ == 1
    case prf_kof_misalignedRead:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_STACK_OVERFLOW == 1
    case prf_kof_stackOverflow:
        /* This test case should not flood the entire RAM. We try to keep the overflow
           little. This makes the literal here a maintenance issue. The recursion consumes
           24 Byte per stack frame (look for "nestStackInjectError:" in compiler artifact
           prf_processFailureInjection.s) and the stack is configured to have 2048 Byte. */
        stackDepth = 100;
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 3;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_STACK_CLEAR_BOTTOM == 1
    case prf_kof_stackClearBottom:
        stackDepth = 63;
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 3;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_SP_CORRUPT == 1
    case prf_kof_spCorrupt:
        if(stackDepth < 10)
            stackDepth = 10;
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 3;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_SP_CORRUPT_AND_WAIT == 1
    case prf_kof_spCorruptAndWait:
        if(stackDepth < 10)
            stackDepth = 10;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_PRIVILEGED_AND_MPU == 1
    case prf_kof_privilegedAndMPU:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_READ_SPR == 1
    case prf_kof_readSPR:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_WRITE_SPR == 1
    case prf_kof_writeSPR:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_WRITE_SVSP == 1
    case prf_kof_writeSVSP:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_CLEAR_SDA_PTRS == 1
    case prf_kof_clearSDAPtrs:
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 3;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_CLEAR_SDA_PTRS_AND_WAIT == 1
    case prf_kof_clearSDAPtrsAndWait:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_MMU_WRITE == 1
    case prf_kof_MMUWrite:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_MMU_READ == 1
    case prf_kof_MMURead:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_MMU_EXECUTE == 1
    case prf_kof_MMUExecute:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_MMU_EXECUTE_2 == 1
    case prf_kof_MMUExecute2:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_MMU_EXECUTE_PERIPHERAL == 1
    case prf_kof_MMUExecutePeripheral:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_TRAP == 1
    case prf_kof_trap:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_TLB_INSTR == 1
    case prf_kof_tlbInstr:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_SPE_INSTR == 1
    case prf_kof_SPEInstr:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_BOOKE_FPU_INSTR == 1
    case prf_kof_BookEFPUInstr:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_DCACHE_INSTR == 1
    case prf_kof_dCacheInstr:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_UNDEF_SYS_CALL == 1
    case prf_kof_undefSysCall:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_RANDOM_WRITE == 1
    case prf_kof_randomWrite:
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 3;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_RANDOM_READ == 1
    case prf_kof_randomRead:
        minNoExpectedFailures = 1;
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_RANDOM_JUMP == 1
    case prf_kof_randomJump:
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 3;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_MPU_EXC_BEFORE_SC == 1
    case prf_kof_mpuExcBeforeSc:
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_INVALID_CRIT_SEC == 1
    case prf_kof_invalidCritSec:
        minNoExpectedFailures = 1;
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_LEAVE_CRIT_SEC == 1
    case prf_kof_leaveCritSec:
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 0;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_INVOKE_RTOS_OS_RUN_TASK == 1
    case prf_kof_invokeRtosOsRunTask:
        /* Zero error counts would occur if the process were stopped. */
        minNoExpectedFailures = 1;
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_INVOKE_IVR_SYSTEM_CALL_BAD_ARGUMENT == 1
    case prf_kof_invokeIvrSystemCallBadArgument:
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_SYSTEM_CALL_ALL_ARGUMENTS_OKAY == 1
    case prf_kof_systemCallAllArgumentsOkay:
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 0;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_WAIT_INSTR == 1
    case prf_kof_waitInstr:
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 1;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_ENA_FPU_EXC == 1
    case prf_kof_enableFpuExceptions:
        minNoExpectedFailures = 0;
        maxNoExpectedFailures = 0;
        break;
#endif

    default:
        /* Many test cases have the standard expectation: 1..3 reported process failures
           but no particular result to check. They go all here. */
        break;

    } /* End switch(Which test case yields which failure?) */

    prf_cmdFailure = (prf_cmdFailure_t){ .kindOfFailure = kindOfFailure
                                         , .noRecursionsBeforeFailure = stackDepth
                                         , .value = value
                                         , .address = address
                                       };
    _failureExpectation = (failureExpectation_t)
                          { .kindOfFailure = kindOfFailure
                            , .address = address
                            , .expectedValue = expectedValue
                            , .expectedNoProcessFailures =
                                            rtos_getNoTotalTaskFailure(syc_pidFailingTasks)
                                            + minNoExpectedFailures
                            , .expectedNoProcessFailuresTolerance = maxNoExpectedFailures
                                                                    - minNoExpectedFailures
                          };
    return 0;

} /* End of prs_taskCommandError */



/**
 * Task function, cyclically activated every 10ms.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
int32_t prs_taskEvaluateError(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    /* Don't repeat the error evaluation if an error had already been detected and the
       process had been halted. Return zero, do not count the same situation repeatedly. */
    if(rtos_getNoTotalTaskFailure(syc_pidSupervisor) > 0)
        return 0;

    /** A long lasting test could theoretically run into the saturation of the failure
        counter. We must not report this as an error. On the other hand it doesn't make
        much sense to continue. There's no true solution for this dilemma but taking the given
        timing of the application we would reach this point after more than 200 days - and
        ignore it. */ 
    const unsigned int noFailures = rtos_getNoTotalTaskFailure(syc_pidFailingTasks);

    bool testOkThisTime =
            noFailures != 0xffffffff
            &&  noFailures >= _failureExpectation.expectedNoProcessFailures
            &&  noFailures <= _failureExpectation.expectedNoProcessFailures
                              + _failureExpectation.expectedNoProcessFailuresTolerance;

    switch(_failureExpectation.kindOfFailure)
    {
#if PRF_ENA_TC_PRF_KOF_WRITE_OS_DATA == 1
    case prf_kof_writeOsData:
        if(_failureExpectation.expectedValue != *(const uint32_t*)_failureExpectation.address)
            testOkThisTime = false;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_WRITE_OTHER_PROC_DATA == 1
    case prf_kof_writeOtherProcData:
        if(_failureExpectation.expectedValue != *(const uint32_t*)_failureExpectation.address)
            testOkThisTime = false;
        break;
#endif

#if PRF_ENA_TC_PRF_KOF_WRITE_ROM == 1
    case prf_kof_writeROM:
        if(_failureExpectation.expectedValue != *(const uint32_t*)_failureExpectation.address)
            testOkThisTime = false;
        break;
#endif

    default:
        /* Many test cases don't require additional attention. No action. */
        break;
    }

    /* Make the problem visible even if no debugger or terminal is connected. */
    if(!testOkThisTime)
    {
        lbd_setLED(lbd_led_0_DS11, /* isOn */ false);
        lbd_setLED(lbd_led_7_DS4, /* isOn */ true);
    }

    ++ prs_cntTestCycles;

    /* PRODUCTION compilation: If we return a task error here then we will see a process
       error and the watchdog task will halt the further SW execution. */
    return testOkThisTime? 0: -1;

} /* End of prs_taskEvaluateError */



/**
 * The watchdog task. It is running at highest intended RTOS user task priority. This
 * priority level is protected against locks by user code (user code cannot implement a
 * critical section with such a task). The watchdog checks whether the supervisor task is
 * running as expected. (Alive counter, number of errors.)\n
 *   This is a non cyclic task, which is activated by software trigger. The trigger
 * is regular but asynchronous to the normal RTOS scheduler. (This has no particular
 * advantage besides more intensive testing of context switches.)
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here just used for testing, we expect a linear counter
 * starting at zero.
 */
int32_t prs_taskWatchdog(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam)
{
    const bool isPrcFailingTasksSuspended = rtos_isProcessSuspended(syc_pidFailingTasks);
    
#define TI_BLINK_IN_MS  750u
#define CNT_STEP    ((int16_t)((float)(UINT16_MAX)/(TI_BLINK_IN_MS) + 0.5f))
    static int16_t SDATA_PRC_SV(cnt_) = 0;

    if(!isPrcFailingTasksSuspended)
    {
        /// @todo Add SW alive counters in all processes/tasks and add a need-to-change
        // condition here

        /* The status variables don't need to be checked any more after suspending the
           failure injection process after the first failure. However, we continue to do so
           for sake of easier debugging in case of a problem.
             Note, the stack reserve computation every Millisecond costs about 15% CPU
           load. */ 
        prs_status.status.noTestCycles = prs_cntTestCycles;
        prs_status.status.noActLossEvTest = rtos_getNoActivationLoss(syc_idEvTest);
        prs_status.status.noActLossEvPIT2 = rtos_getNoActivationLoss(syc_idEvPIT2);
        prs_status.status.noTaskFailSV = rtos_getNoTotalTaskFailure(syc_pidSupervisor);
        prs_status.status.noTaskFailRep = rtos_getNoTotalTaskFailure(syc_pidReporting);
        prs_status.status.stackResSV = rtos_getStackReserve( /* idxCore */ 0
                                                           , syc_pidSupervisor
                                                           );
        prs_status.status.stackResRep = rtos_getStackReserve( /* idxCore */ 0
                                                            , syc_pidReporting
                                                            );
        prs_status.status.stackResOS = rtos_getStackReserve( /* idxCore */ 0
                                                           , /* PID */ 0 /* OS */
                                                           );
        
        /* The first term in the failure condition is equivalent to a check of activation
           losses for the supervisory process (event syc_idEvPIT2). The event triggering
           ISR sends consecutive number 0, 1, 2... but we would see here a missing number
           if the triggering the event should have failed. */
        static uintptr_t SBSS_PRC_SV(expectedTaskParam_) = 0;
        bool isOk = taskParam == expectedTaskParam_++
                    &&  prs_status.status.noActLossEvTest == 0
                    &&  prs_status.status.noActLossEvPIT2 == 0
                    &&  prs_status.status.noTaskFailSV == 0
                    &&  prs_status.status.noTaskFailRep == 0
                    &&  prs_status.status.stackResSV >= 512
                    &&  prs_status.status.stackResRep >= 512
                    &&  prs_status.status.stackResOS >= 3096;

        if(isOk)
        {
            if((uint16_t)cnt_ < (uint16_t)CNT_STEP)
            {
                /* Run a task in the reporting process to let it print some regular
                   progress and status information. */
                const prr_testStatus_t testStatus = { .noTestCycles = prs_cntTestCycles };
                const rtos_taskDesc_t userTaskConfig =  
                                    { .addrTaskFct = (uintptr_t)prr_taskReportWatchdogStatus
                                      , .PID = syc_pidReporting
                                      , .tiTaskMax = RTOS_TI_MS2TICKS(3)
                                    };
                int32_t result ATTRIB_DBG_ONLY =
                                    rtos_runTask( &userTaskConfig
                                                , /* taskParam */ (uint32_t)&testStatus
                                                );
                assert(result >= 0);
            }
        }
        else
        {
            /* Keep a persistent copy of the information about the injected error for
               inspection in the debugger. */
            prs_status.cmdFailure = prf_cmdFailure;
            prs_status.expectation = _failureExpectation;
            prs_status.noTotalTaskFailures = rtos_getNoTotalTaskFailure(syc_pidFailingTasks);

            /* Run a task once in the reporting process to let it print the conditions,
               which caused the software halt. */
            const rtos_taskDesc_t userTaskConfig =  
                                    { .addrTaskFct = (uintptr_t)prr_taskReportFailure
                                      , .PID = syc_pidReporting
                                      , .tiTaskMax = RTOS_TI_MS2TICKS(5)
                                    };
            int32_t result ATTRIB_DBG_ONLY =
                            rtos_runTask( &userTaskConfig
                                        , /* taskParam */ (uint32_t)&prs_status.status
                                        );
            assert(result >= 0);

            /* Suspend our failure injection process. The RTOS and the rest of the
               application software continue running. */
            rtos_suspendProcess(syc_pidFailingTasks);
        }
    } /* End if(Failure injection process suspended or still alive?) */

    /* Let the LED blink, which indicates the health of the failure injection process. To
       make the effect event better visible, we change the dutc cycle. */
    const bool isLedOn = cnt_ >= (isPrcFailingTasksSuspended? INT16_MAX-UINT16_MAX/5: 0);
    lbd_setLED(isPrcFailingTasksSuspended? lbd_led_7_DS4: lbd_led_0_DS11, isLedOn);

    /* The LED driver is not protected in the sense that it grants different privileges
       to different processes. This makes it available to a failing, straying task. We
       indeed see occasional LED switch commands due to arbitrary code execution in the
       failing failure injection task. We correct the LED status regularly to maintain
       the signaling effect of the LED. */
    lbd_setLED( isPrcFailingTasksSuspended? lbd_led_0_DS11: lbd_led_7_DS4
              , /* isOn */ false
              );

    /* Advance counter such that it wrapps around in the wanted time span. */
    cnt_ += CNT_STEP;

#undef TI_BLINK_IN_MS
#undef CNT_STEP

    return 0;

} /* End of prs_taskWatchdog */




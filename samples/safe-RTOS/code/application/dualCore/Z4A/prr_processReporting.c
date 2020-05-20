/**
 * @file prr_processReporting.c
 * Implementation of task functions of process \a syc_pidReporting. This process has the
 * special ID 1, which makes the C libry accessible. The principal task from this process
 * uses printf from the library to regularly print status messages to the serial output.
 * The tasks of this process are not involved into the testing and we expect them to
 * continuously run, not being harmed by the failures produced by the other processes.\n
 *   The tasks and their implementation belong into the sphere of the protected user code.
 * They are are defined in the sphere of unprotected operating system code and anything
 * which relates to their configuration cannot be changed anymore by user code.
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
 *   prr_taskReportWatchdogStatus
 *   prr_taskReportFailure
 *   prr_taskReporting
 *   prr_taskTestContextSwitches
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
#include "stm_systemTimer.h"
#include "tcx_testContext.h"
#include "syc_systemConfiguration.h"
#include "prs_processSupervisor.h"
#include "mzb_main_Z4B.h"
#include "prr_processReporting.h"


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
 
/** For debugging only: Exceution time of untrusted C lib function iprintf. Unit is
    #STM_TIMER_1_PERIOD_IN_NS. */
uint32_t SDATA_PRC_REPORT(prr_tiMaxDurationPrintf) = 0;


/*
 * Function implementation
 */


/**
 * Task function, which is regularly activated by the watchdog task. Used to print the
 * current status.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param pStatusInfo
 * An object with status information to print by reference. The reporting task has only
 * read access to the data.
 */
int32_t prr_taskReportWatchdogStatus( uint32_t PID ATTRIB_UNUSED
                                    , const prr_testStatus_t *pStatusInfo
                                    )
{
    printf( "prr_taskReportWatchdogStatus: %lu test cases successfully run\r\n"
          , pStatusInfo->noTestCycles
          );
    return 0;
    
} /* End of prr_taskReportWatchdogStatus */



/**
 * Task function, which is activated once by the watchdog task on entry into the halted
 * state. Used to print the error information as last action.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param pFailureInfo
 * An object with error information to print by reference. The reporting task has only
 * read access to the data.
 *   @remark
 * In this sample application, the watchdog task enters an infinite loop in case of a
 * recognized error. Therefore, the serial output will not safely be able to print the
 * information if its interrupt level is not higher than the priority of the watchdog task.
 */
int32_t prr_taskReportFailure( uint32_t PID ATTRIB_UNUSED
                             , const prr_failureStatus_t *pFailureInfo
                             )
{
    printf( "prr_taskReportFailure: Watchdog is about to halt the software after %lu"
            " test cases!\r\n"
            "  noActLossEvTest: %lu\r\n"
            "  noActLossEvPIT2: %lu\r\n"
            "  noTaskFailSV: %lu\r\n"
            "  noTaskFailRep: %lu\r\n"
            "  stackResSV: %lu\r\n"
            "  stackResRep: %lu\r\n"
            "  stackResOS: %lu\r\n"
          , pFailureInfo->noTestCycles
          , pFailureInfo->noActLossEvTest
          , pFailureInfo->noActLossEvPIT2
          , pFailureInfo->noTaskFailSV
          , pFailureInfo->noTaskFailRep
          , pFailureInfo->stackResSV
          , pFailureInfo->stackResRep
          , pFailureInfo->stackResOS
          );

    return 0;
    
} /* End of prr_taskReportFailure */



/**
 * Task function, cyclically activated every about 1000 ms. Used to print status
 * information to the serial output.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
int32_t prr_taskReporting(uint32_t PID ATTRIB_UNUSED, uintptr_t taskParam ATTRIB_UNUSED)
{
    const unsigned int cpuLoadZ4A = syc_cpuLoad
                     , cpuLoadZ4B = mzb_cpuLoad;
    
    const uint32_t tiStart = stm_getSystemTime(1);
    iprintf( "CPU load on core Z4A is %u.%u%%. Stack reserve:\r\n"
             "  OS: %u Byte\r\n"
             "  PID 1: %u Byte\r\n"
             "  PID 2: %u Byte\r\n"
             "  PID 3: %u Byte\r\n"
             "Event triggers (lost):\r\n"
             "  idEvTest: %lu (%u)\r\n"
             "  isrPit3: %llu (N/A)\r\n"
             "Process errors:\r\n"
             "  Total PID 1: %u\r\n"
             "  thereof Deadline missed: %u\r\n"
             "  Total PID 2: %u\r\n"
             "  thereof Deadline missed: %u\r\n"
             "  thereof User task abort: %u\r\n"
             "  Total PID 3: %u\r\n"
             "  thereof Deadline missed: %u\r\n"
           , cpuLoadZ4A/10, cpuLoadZ4A%10
           , rtos_getStackReserve(/* idxCore */ 0, 0)
           , rtos_getStackReserve(/* idxCore */ 0, 1)
           , rtos_getStackReserve(/* idxCore */ 0, 2)
           , rtos_getStackReserve(/* idxCore */ 0, 3)
           , prs_cntTestCycles, rtos_getNoActivationLoss(syc_idEvTest)
           , syc_cntISRPit3
           , rtos_getNoTotalTaskFailure(/* PID */ 1)
           , rtos_getNoTaskFailure(/* PID */ 1, RTOS_ERR_PRC_DEADLINE)
           , rtos_getNoTotalTaskFailure(/* PID */ 2)
           , rtos_getNoTaskFailure(/* PID */ 2, RTOS_ERR_PRC_DEADLINE)
           , rtos_getNoTaskFailure(/* PID */ 2, RTOS_ERR_PRC_USER_ABORT)
           , rtos_getNoTotalTaskFailure(/* PID */ 3)
           , rtos_getNoTaskFailure(/* PID */ 3, RTOS_ERR_PRC_DEADLINE)
           );

    /* Report some results, we received through uncached memory from other core. */
    iprintf( "CPU load on core Z4B is %u.%u%%\r\n"
             "Task counts on core Z4B:\r\n"
             "  OS, 1ms: %lu\n\r"
             "  user, 1ms: %lu\n\r"
             "  idle: %lu\n\r"
           , cpuLoadZ4B/10, cpuLoadZ4B%10
           , mzb_cntTaskOs1ms
           , mzb_cntTask1ms
           , mzb_cntTaskIdle
           );
    const uint64_t tiDuration = stm_getSystemTime(1) - tiStart;
    
    if(tiDuration > prr_tiMaxDurationPrintf)
        prr_tiMaxDurationPrintf = tiDuration;
        
/// @todo remove test code
    const uint32_t tiEndTest = stm_getSystemTime(1)
                               + (1.5e-3f * 1e9f / STM_TIMER_1_PERIOD_IN_NS);
    bool didChange = false;
    uint32_t tiChangedAfter;
    const unsigned long mzb_cntTaskOs1ms_1st = mzb_cntTaskOs1ms;
    while((signed int)(tiEndTest - stm_getSystemTime(1)) > 0)
    {
        if(mzb_cntTaskOs1ms != mzb_cntTaskOs1ms_1st)
        {
            tiChangedAfter = stm_getSystemTime(1)
                             - (uint32_t)(tiEndTest - (1.5e-3f * 1e9f / STM_TIMER_1_PERIOD_IN_NS));
            didChange = true;
            break;
        }
    }
    static unsigned int SDATA_PRC_REPORT(cntDidntChange_) = 0;
    cntDidntChange_ += (didChange? 0: 1);
    iprintf( "Task counts on core Z4B, %lu us later:\r\n"
             "  OS, 1ms: %lu\n\r"
             "  user, 1ms: %lu\n\r"
             "  idle: %lu\n\r"
             "  (didn't change %u times)\r\n"
           , (stm_getSystemTime(1)-(uint32_t)(tiEndTest - (1.5e-3f * 1e9f / STM_TIMER_1_PERIOD_IN_NS)))/5
           , mzb_cntTaskOs1ms
           , mzb_cntTask1ms
           , mzb_cntTaskIdle
           , cntDidntChange_
           );
    if(didChange)
    {
        iprintf( "Task counts changed after %lu us\r\n"
               , tiChangedAfter*STM_TIMER_1_PERIOD_IN_NS/1000
               );
    }
    else
        iprintf("Task counts didn't change\r\n");

    return 0;
    
} /* End of prr_taskReporting */



/**
 * Task function, cyclically activated every 11ms. It executes an assembler function, which
 * aims at testing correct context save/restore for most user registers and across context
 * switches.\n
 *   The function is blocking for a relative long while to provoke a lot of context
 * switches during testing. This produces significant CPU load.\n
 *   In DEBUG compilation any error will run into an assertion and halt the software. In
 * PRODUCTION compilation a process error is accounted. This is a clear problem report
 * because the process is designed to be at all error free.
 *   @return
 * If the task function returns a negative value then the task execution is counted as
 * error in the process.
 *   @param PID
 * A user task function gets the process ID as first argument.
 *   @param taskParam
 * A variable task parameter. Here not used.
 */
int32_t prr_taskTestContextSwitches( uint32_t PID ATTRIB_UNUSED
                                   , uintptr_t taskParam ATTRIB_UNUSED
                                   )
{
    /* The next call produces 100 * noCycles*(waitTimePerCycleInUS/1000) / 11 percent of
       CPU load. */
    tcx_testContext(/* noCycles */ 2, /* waitTimePerCycleInUS */ 2000);

    return 0;
    
} /* End of prr_taskTestContextSwitches */




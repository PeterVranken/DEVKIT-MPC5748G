#ifndef PRR_PROCESSREPORTING_INCLUDED
#define PRR_PROCESSREPORTING_INCLUDED
/**
 * @file prr_processReporting.h
 * Definition of global interface of module prr_processReporting.c
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


/*
 * Global type definitions
 */

/** Status information object as printed by prr_taskReportWatchdogStatus(). */
typedef struct prr_testStatus_t
{
    /** No test cycles so far. */
    long unsigned int noTestCycles;
    
} prr_testStatus_t;


/** Failure information object as printed by prr_taskReportFailure(). */
typedef struct prr_failureStatus_t
{
    /** No test cycles so far. */
    long unsigned int noTestCycles;
    
    /** No lost activations of syc_idEvTest. */
    uint32_t noActLossEvTest;
    
    /** No lost activations of syc_idEvPIT2. */
    uint32_t noActLossEvPIT2;
    
    /** No task failures reported for process syc_pidSupervisor. */
    uint32_t noTaskFailSV;
    
    /** No task failures reported for process syc_pidReporting. */
    uint32_t noTaskFailRep;
    
    /** Stack reserve of process syc_pidSupervisor in Byte. */
    uint32_t stackResSV;
    
    /** Stack reserve of process syc_pidReporting in Byte. */
    uint32_t stackResRep;
    
    /** Stack reserve of kernel process in Byte. */
    uint32_t stackResOS;
    
} prr_failureStatus_t;



/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Task function, which is regularly activated to print the current status. */
int32_t prr_taskReportWatchdogStatus(uint32_t PID, const prr_testStatus_t *pStatusInfo);

/** Task function, which is activated on entry into the halted state to print error info. */
int32_t prr_taskReportFailure( uint32_t PID ATTRIB_UNUSED
                             , const prr_failureStatus_t *pFailureInfo
                             );

/** User task doing some regular status reporting via serial output. */
int32_t prr_taskReporting(uint32_t PID, uint32_t taskParam);

/** User task doing some invisible background testing of context switches. */
int32_t prr_taskTestContextSwitches(uint32_t PID, uint32_t taskParam);


#endif  /* PRR_PROCESSREPORTING_INCLUDED */

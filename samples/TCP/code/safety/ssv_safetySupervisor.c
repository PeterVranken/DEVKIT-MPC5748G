/**
 * @file ssv_safetySupervisor.c
 * Implementation of the safety supervisor task.
 *
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   bsw_taskSafetyInit
 *   bsw_taskSafety1ms
 *   bsw_taskSafety10ms
 * Local functions
 */

/*
 * Include files
 */

#include <assert.h>

#include "typ_types.h"
#include "lbd_ledAndButtonDriver.h"
#include "bsw_basicSoftware.h"
#include "ssv_safetySupervisor.h"


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
 
 
/*
 * Function implementation
 */

/**
 * The initialization task of process bsw_pidSafety, the safety supervision process. The
 * task is called at a time when no parallel thread execution is done yet, so no race
 * conditions exist with other parts of the code and safe build-up of all required data
 * structure can be done prior to the start of the real task scheduling.\n
 *   The initialization function of safety process bsw_pidSafety is invoked after the
 * according initialization function of the QM process -- so it has the power to
 * double-check the QM initialization and can inhibit system startup in case.\n
 *   @return
 * The function may return a negative value to indicate a severe problem. The system won't
 * start up in this case. Normally, we will return zero.
 *   @param PID
 * The process ID of the initialized process, always bsw_pidSafety in our case.
 */
int32_t bsw_taskSafetyInit(uint32_t PID ATTRIB_DBG_ONLY)
{
    assert(PID == bsw_pidSafety);

    boolean_t success = true;

    return success? 0: -1;

} /* End of bsw_taskSafetyInit */




/**
 * Demo code of the regularly executed 1ms task from the safety supervision.
 *   @return
 * The function will always return zero. Indicating a severe problem by returning a
 * negative value to the system would be useless -- nobody would take notice of the
 * reported problem.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidSafety in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskSafety1ms(uint32_t PID ATTRIB_DBG_ONLY, uint32_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidSafety);

    /* Call the 1ms step function of the safety supervisor. */
    //...

    return 0;

} /* End of bsw_taskSafety1ms */




/**
 * Demo code of the regularly executed 10ms task from the safety supervision.
 *   @return
 * The function will always return zero. Indicating a severe problem by returning a
 * negative value to the system would be useless -- nobody would take notice of the
 * reported problem.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidSafety in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskSafety10ms(uint32_t PID ATTRIB_DBG_ONLY, uint32_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidSafety);

    /* Call the 10ms step function of the safety supervisor. */
    //...
    static uint8_t SDATA_P2(cnt_) = 0;
    lbd_setLED(lbd_led_5_DS6, /* isOn */ (cnt_+=3) < 50);

    return 0;

} /* End of bsw_taskSafety10ms */





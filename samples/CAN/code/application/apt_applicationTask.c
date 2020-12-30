/**
 * @file apt_applicationTask.c
 * This file links the APSW to the operating system. It contains the
 * entry points into all the application task functions. A set of (regular) tasks is
 * created by the operating system and may or may not be implemented by the APSW. (If
 * not, an empty default implementation is used.)\n
 *   The init task is for example used to initialize all data structures of the CAN
 * interface.\n
 *   The regularly executed run-time tasks run the CAN interface engine and call the APSW.
 * The CAN interface engine updates all signal values and status in the global CAN API and
 * sends due frames, filled with information read from this API.
 *
 * Copyright (C) 2015-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   bsw_onRxCan
 *   bsw_taskUserInit
 *   bsw_taskUser1ms
 *   bsw_taskUser10ms
 *   bsw_taskUser100ms
 *   bsw_taskUser1000ms
 * Local functions
 */


/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "cap_canApi.h"
#include "lbd_ledAndButtonDriver.h"
#include "bsw_basicSoftware.h"
#include "cdr_canDriverAPI.h"
#include "mem_malloc.h"
#include "cde_canDispatcherEngine.h"
#include "cde_canStatistics.h"
#include "cde_canDataTables.h"
#include "f2d_float2Double.h"
#include "can_canRuntime.h"
#include "apt_applicationTask.h"


/*
 * Defines
 */

/** Floating point random number with more than 15 Bit resolution; taken fron
    http://www.azillionmonkeys.com/qed/random.html on Jan 23, 2017.
      @remark Caution, the definition make use of a GNU extension and is not portable. */
#define DRAND() ({                                                                  \
    double d;                                                                       \
    do {                                                                            \
       d = (((rand() * RS_SCALE) + rand()) * RS_SCALE + rand()) * RS_SCALE;         \
    } while(d >= 1); /* Round off */                                                \
    d;                                                                              \
})

/** Helper for #DRAND. */
#define RS_SCALE (1.0 / (1.0 + RAND_MAX))

/** A scaled floating point random number in the range [a, b). */
#define RAND(a,b) ((double)((b)-(a))*DRAND()+(double)(a))

/** A Boolean random number with given probability p of getting a true. */
#define BOOL_RAND(p) ((DRAND()<(p))? true: false)


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
 * The initialization task of process bsw_pidUser, the QM aaplication code process. The task is
 * called at a time when no parallel thread execution is done yet, so no race conditions
 * exist with other parts of the code and safe build-up of all required data structure can
 * be done prior to the start of the real task scheduling.\n
 *   The initialization function of QM process bsw_pidUser is invoked prior to the
 * according initialization function of the safety process.\n
 *   We use this function to initialize the CAN interface.
 *   @return
 * The function may return a negative value to indicate a severe problem. The system won't
 * start up in this case. Normally, we will return zero.
 *   @param PID
 * The process ID of the initialized process, always bsw_pidUser in our case.
 */
int32_t bsw_taskUserInit(uint32_t PID ATTRIB_DBG_ONLY)
{
    assert(PID == bsw_pidUser);

    bool success = true;
    
    /* Run the initialization of the CAN stack. */
    if(!can_initCanStack())
        success = false;

    return success? 0: -1;

} /* End of bsw_taskUserInit */




/**
 * Demo code of the regularly executed 1ms task of the APSW.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervior task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser1ms(uint32_t PID ATTRIB_DBG_ONLY, uintptr_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the 1ms step function of the APSW. */
    //asw_taskApsw_1ms();

    return 0;

} /* End of bsw_taskUser1ms */




/**
 * Demo code of the regularly executed 10ms task of the APSW. The engine of the CAN
 * interface is clocked and the decoded and pre-processed CAN information can be consumed
 * by the APSW. Vice versa, the APSW provided functional results are encoded and timely
 * sent by the engine. All data access can be done easy and directly since no race
 * conditions occur.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervior task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser10ms(uint32_t PID ATTRIB_DBG_ONLY, uintptr_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the step function of the CAN interface engine for this task. */
    cde_dispatcherMain(CAN_IDX_DISPATCHER_10MS);

    /* Call the step function of the APSW, which computes new CAN output values. */
    //asw_taskApsw_10ms();

    return 0;

} /* End of bsw_taskUser10ms */




/**
 * Demo code of the regularly executed 100ms task of the APSW.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervior task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser100ms(uint32_t PID ATTRIB_DBG_ONLY, uintptr_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the 100ms step function of the APSW. */
    //asw_taskApsw_100ms();

    return 0;

} /* End of bsw_taskUser100ms */




/**
 * Demo code of the regularly executed 1s task of the APSW.
 *   @return
 * Normally, the function will return zero. However, it may return a negative value to
 * indicate a severe problem. The system would count a process error and a safety
 * supervior task could take an action.
 *   @param PID
 * The process ID of the process, the task belongs to; always bsw_pidUser in our case.
 *   @param taskParam
 * A task receives an argument. It is always zero in our case.
 */
int32_t bsw_taskUser1000ms(uint32_t PID ATTRIB_DBG_ONLY, uintptr_t taskParam ATTRIB_UNUSED)
{
    assert(PID == bsw_pidUser);

    /* Call the 1s step function of the APSW. */
    //asw_taskApsw_1000ms();
    static bool SDATA_P1(isOn_) = false;
    lbd_setLED(lbd_led_1_DS10, isOn_=!isOn_);

    /* Some test code of the uniform floating point signal API shaped for this sample. */
    
    /* CAN ID 1024, Rx signal "speedOfRotation": Print current value. */
    const cde_canSignal_t *pSpeedOfRotation = &cde_canSignalAry[1];
    assert(pSpeedOfRotation->isReceived
           &&  pSpeedOfRotation->idxFrame < sizeOfAry(cde_canRxFrameAry)
          );
    printf( "Frame %d, signal %s: %f %s\r\n"
          , cde_canRxFrameAry[pSpeedOfRotation->idxFrame].canId
          , pSpeedOfRotation->name
          , f2d(pSpeedOfRotation->getter())
          , pSpeedOfRotation->unit
          );

    /* CAN ID 1536, Tx signal "power": Change value visibly. */
    const cde_canSignal_t *pPower = &cde_canSignalAry[14];
    assert(!pPower->isReceived
           &&  pPower->idxFrame < sizeOfAry(cde_canTxFrameAry)
          );
    const float range = pPower->max - pPower->min
              , delta = range/15.0f;
    float newValue;
    newValue = pPower->getter() + delta;
    if(newValue > pPower->max)
        newValue -= range;
    assert(newValue >= pPower->min  &&  newValue <= pPower->max);
    pPower->setter(newValue);

    return 0;

} /* End of bsw_taskUser1000ms */





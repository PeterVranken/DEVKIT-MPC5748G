/**
 * @file asw_APSW.c
 * This is a handwritten source file, which imitates the implementation of the application
 * software in a real project - but only with respect to the usage of the CAN API.\n
 *   For outbound frames, it basically fills the CAN API regularly with new data and E2E
 * protects it. For event triggered frame this is not done regularly but on a random
 * base.\n
 *   For inbound frames, it regularly consumes the data from the CAN API by doing the E2E
 * validation. Any error is reported by assertion - this is meant a software test only.\n
 *   Note, the implementation of the module is strongly supported by an auto-coded data
 * structure, which provides access to the frame's individual E2E protection and validation
 * functions in a generic way (by function pointers). Instead, a real APSW, which knows all
 * the different frames, would likely use individual calls of these frame related code.
 *
 * Copyright (C) 2017-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   asw_taskApsw_10ms
 *   asw_taskApsw_100ms
 * Local functions
 *   readCanInput
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "typ_types.h"
#include "cde_canStatistics.h"
#include "cap_canApi.h"
#include "cde_canDataTables.h"
#include "apt_applicationTask.h"
#include "asw_APSW.h"


/*
 * Defines
 */
 
/** A Boolean random number with given probability p of getting a true. */
#define BOOL_RAND(p) (RND()<(p)? true: false)

/** A floating point random number in the range [0;1). */
#define RND() ((double)rand()/(double)RAND_MAX)


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
 * Provide all required the CAN input data to the calling task.
 *   @param tiCycle
 * The same function is used for the CAN frames of all the regular APSW tasks. Which task
 * is currently calling the function is identified by the task's cycle time in ms.
 */
static void readCanInput(unsigned int tiCycle ATTRIB_UNUSED)
{
    /* Nothing to do here: The CAN interface engine has updated the global CAN interface
       with the last recently received CAN information. It has done the E2E validation and
       has put the result into the transmission status. The APSW can directly access the
       signal values and the transmission status in the global API. */

    /* Note, the concept of this implementation is a separation of the CAN messages into
       groups, which are individually processed by different tasks. The idea is to process
       fast regular and event triggered messages by the regular 10ms APSW task, while
       slowly repeated, regular messages are handled by the regular 100ms APSW task. The
       rational is to save computation overhead in the CAN communication.
         A real APSW could adopt this concept but it would likely need some information
       interchange between the tasks. Thread-safe copying CAN data from the other task(s)
       into some local storage of the calling task could be implemented here. */

} /* End of readCanInput */




/**
 * This function imitates the operation of the APSW in that it produces some new output
 * data for all the outbound CAN frames, which are owned or processed by a given task.
 *   @param tiCycle
 * The same function is used for the CAN frames of all the regular APSW tasks. Which task
 * is currently calling the function is identified by the task's cycle time in ms.
 */
static void computeApswResults(unsigned int tiCycle)
{
} /* End of computeApswResults */




/**
 * This function imitates the behavior of a regular task in a possible RTOS project with
 * CAN communication.\n
 *   The behavior is imitated only with respect to the CAN communication. There's no
 * functional code operating on the transmitted CAN information. Inbound frames are E2E
 * validated and random data is used to fill outbound frames. These are E2E protected and
 * submitted.\n
 *   This function is supposed to be called once every 10 ms.
 */

void asw_taskApsw_10ms()
{
    /* Process all CAN input signals, which are required by this task. */
    readCanInput(/* tiCycle */ 10);
    
    /* The natural job of the APSW is to produce new output data. We imitate the APSW
       functionality by producing random data. */
    computeApswResults(/* tiCycle */ 10);
    
    /* Nothing else to do for the ASPW to send a frame. This is handled by the CAN
       interface engine. */

} /* End of asw_taskApsw_10ms */




/**
 * This function imitates the behavior of a regular task in a possible RTOS project with
 * CAN communication.\n
 *   The behavior is imitated only with respect to the CAN communication. There's no
 * functional code operating on the transmitted CAN information. Inbound frames are E2E
 * validated and random data is used to fill outbound frames. These are E2E protected and
 * submitted.\n
 *   This function is supposed to be called once every 100 ms.
 */

void asw_taskApsw_100ms()
{
    /* Process all CAN input signals, which are required by this task. */
    readCanInput(/* tiCycle */ 100);
    
    /* The natural job of the APSW is to produce new output data. We imitate the APSW
       functionality by producing random data. */
    computeApswResults(/* tiCycle */ 100);
    
    /* Nothing else to do for the ASPW to send a frame. This is handled by the CAN
       interface engine. */
    
} /* End of asw_taskApsw_100ms */





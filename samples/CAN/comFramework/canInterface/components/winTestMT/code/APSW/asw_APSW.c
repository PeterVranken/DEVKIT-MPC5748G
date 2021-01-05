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
 * Copyright (C) 2017 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   computeApswResults
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "types.h"
#include "cde_canStatistics.h"
#include "cap_canApi.h"
#include "cde_canDataTables.h"
#include "sup_startup.h"
#include "ose_operatingSystemEmulation.h"
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
 
/** Counters for frame validation failure events.
      @remark These variables are updated by the APSW but not used beyond this. They are
    kept only becasue it's a kind of sample code how a real APSW could be implemented. */
static _Atomic unsigned long long _noRxFrames = 0
                                , _noEvRxTimeout = 0
                                , _noEvRxE2eFailure = 0
                                , _noTxFrames = 0
                                , _noEvTxSendBufFull = 0;
 
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
    /* The natural job of the APSW is to produce new output data. We imitate the APSW
       functionality by producing random data.
         We iterate all registered CAN frames and handle only those, which are outbound and
       owned by the given task. For inbound frames we just observe the status information
       and do some most simple reporting. */
    unsigned int idxFrCde;
    for(idxFrCde=0; idxFrCde<CDE_NO_CAN_FRAMES; ++idxFrCde)
    {
        assert(idxFrCde < sizeof(cde_canFrameAry)/sizeof(cde_canFrameAry[0]));
        const cde_canFrame_t *const pFrDescCde = &cde_canFrameAry[idxFrCde];

        /* Filter the frames to be processed. Continue for frames, which are handled by
           another thread. */
        if(asw_getAssociatedTaskOfFrame(pFrDescCde) != tiCycle)
            continue;

        /* Count events reported through the CAN interface.
             The mechanism is kept as simple as possible. We count the visibility
           of the events to the APSW not the number of occurances. If there is a timeout
           for a frame, we would count all the task invocations of the APSW, which suffer
           from the missing CAN frame, until it has been received again.
             We update global counters, there's no frame related display.
             We ignore the implementation limits and let the counters cycle around. */
        assert(pFrDescCde->pInfoTransmission != NULL);
        if(pFrDescCde->isReceived)
        {
            /* We accumulate the number of successfully received frames. This can be done
               straight forward by adding and resetting the API variable, there are no race
               conditions between the CAN interface engine and the APSW. */
            _noRxFrames += pFrDescCde->pInfoTransmission->noTransmittedFrames;
            pFrDescCde->pInfoTransmission->noTransmittedFrames = 0;

            /* Sequence counter and DLC errors are not supported by this sample
               application. */
            if((pFrDescCde->pInfoTransmission->stsTransmission & cap_stsTransm_errTimeout)
               != 0
              )
            {
                ++ _noEvRxTimeout;
            }
            if((pFrDescCde->pInfoTransmission->stsTransmission & cap_stsTransm_errChecksum)
               != 0
              )
            {
                ++ _noEvRxE2eFailure;
            }
        }            
        else
        {
            /* We accumulate the number of successfully sent frames. This can be done
               straight forward by adding and resetting the API variable, there are no race
               conditions between the CAN interface engine and the APSW. */
            _noTxFrames += pFrDescCde->pInfoTransmission->noTransmittedFrames;
            pFrDescCde->pInfoTransmission->noTransmittedFrames = 0;
            
            if((pFrDescCde->pInfoTransmission->stsTransmission
                & cap_stsTransm_errSendBufferFull
               ) != 0
              )
            {
                ++ _noEvTxSendBufFull;
            }
        }
        
        /* The rest, filling signal values randomly, is useful only for outbound frames. */
        if(pFrDescCde->isReceived)
            continue;
            
        /* Event triggered frames are updated irregularly. We simulate an event by a random
           process. Regular frames updated in every tick. */
        if(pFrDescCde->sendMode == cap_enumSendMode_regular ||  BOOL_RAND(tiCycle*0.002))
        {
            /* Randomly fill the signals of the frame. */
            pFrDescCde->fctRandomFillApiFrame();

            /* Notify the occuring event if it is an event triggered frame. */
            if(pFrDescCde->sendMode != cap_enumSendMode_regular)
            {
                assert(pFrDescCde->pInfoTransmission != NULL);

                /* Normally, the event is checked by the CAN interface engine in every
                   tick, so that any event can be processed. However, most event frames
                   define a minimum delay time after which a subsequent event may lead at
                   earliest to the next frame on the bus (burst avoidance). This can lead
                   to non sent event frames. The situation can be detected by checking the
                   event flag; it is reset by the CAN interface engine as acknowledgment
                   of submitting the event frame. */
                if(pFrDescCde->pInfoTransmission->isEvent)
                {
                    LOG_DEBUG( sup_hGlobalLogger    
                             , "%lu ms: "
                               "%s: Lost event detected for frame %lu on bus %u"
                             , ose_tiSim, __func__
                             , pFrDescCde->canId
                             , pFrDescCde->idxCanBus
                             );
                }

                pFrDescCde->pInfoTransmission->isEvent = true;
            }
        } /* End if(Is there an update of the frame data by the APSW in this tick?) */
    } /* for(All registered frames) */
} /* End of computeApswResults */




/**
 * In this sample, the ASPW separates the CAN frames in two groups, those processed fast
 * and frequently and those with higher latency time. The decision is taken based on some
 * timing characteristics of the frames. This function decides, which of the groups a given
 * frame belong to.
 *   @param pFrDescCde
 * The frame in progress is identified by a reference to its descriptor in the CAN
 * interface.
 */
unsigned int asw_getAssociatedTaskOfFrame(const cde_canFrame_t *pFrDescCde)
{
    /* The slowest clocked reasonably possible task should be used to minimize
       computation overhead. We have a 10ms and a 100ms clocked task. The frames are
       separated by their timing. Regular frames are rated by cycle time. Event
       triggered frames are rated by their minimum distance time, which is a measure
       for the expected latency of processing. */
    return pFrDescCde->sendMode == cap_enumSendMode_regular &&  pFrDescCde->tiCycle < 100
           ||  pFrDescCde->sendMode != cap_enumSendMode_regular
               &&  pFrDescCde->tiMinDistance < 100
           ? /* task with */ 10  /* ms cycle time */
           : /* task with */ 100 /* ms cycle time */
           ;
} /* End of asw_getAssociatedTaskOfFrame */




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
    
    /* Some simple reporting. */
    static unsigned int cnt = 50;
    if(++cnt >= 100)
    {
        cnt = 0;
        LOG_RESULT( sup_hGlobalLogger    
                  , "%lu ms: "
                    "%s: Successfully transmitted frames:\n"
                    "  Rx: %8llu\n"
                    "  Tx: %8llu"
                  , ose_tiSim, __func__
                  , _noRxFrames
                  , _noTxFrames
                  );
        LOG_RESULT( sup_hGlobalLogger    
                  , "%lu ms: "
                    "%s: Global failure counts:\n"
                    "  Rx queue full:       %6llu %4.0f ppm\n"
                    "  Rx timeout:          %6llu %4.0f ppm\n"
                    "  Rx E2E:              %6llu %4.0f ppm\n"
                    "  Tx send buffer full: %6llu %4.0f ppm"
                  , ose_tiSim, __func__
                  , apt_noEvRxQueueFull
                  , 1e6*((double)apt_noEvRxQueueFull/(double)apt_noRxFrames)
                  , apt_noEvRxTimeout
                  , 1e6*((double)apt_noEvRxTimeout/(double)apt_noRxFrames)
                  , apt_noEvRxE2eFailure
                  , 1e6*((double)apt_noEvRxE2eFailure/(double)apt_noRxFrames)
                  , apt_noEvTxSendBufFull
                  , 1e6*((double)apt_noEvTxSendBufFull/(double)apt_noTxFrames)
                  );
    }    
} /* End of asw_taskApsw_100ms */





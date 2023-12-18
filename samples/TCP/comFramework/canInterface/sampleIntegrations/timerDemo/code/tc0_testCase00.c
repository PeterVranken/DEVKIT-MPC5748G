/**
 * @file tc0_testCase00.c
 * Test case 0 for CAN interface.
 *
 * Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   tc0_initTest
 * Local functions
 *   onTestEnd
 *   onTimeoutSyncTimers
 */

/*
 * Include files
 */

#include "tc0_testCase00.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "main.h"


/*
 * Defines
 */
 
/** The test is terminated if this simulation time has been reached. */
#define TEST_DURATION   10000u


/*
 * Local type definitions
 */
 
/* Information for the callbacks: handle and who they are. */
typedef struct userContextSyncTimers_t
{
    /** The handles of all synchronized timers of this test by reference. */
    ede_handleTimer_t *hTimerAry;

    /** The index of the specific timer into the handle array. */
    unsigned int idxTimer;
    
} userContextSyncTimers_t;


/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
/** Signal to the main scheuler loop to end this test. */
bool tc0_endOfTest = false;
 
 
/*
 * Function implementation
 */


/**
 * The once invoked on-elapse timeout for the single-shot timer that terminates the test
 * application.
 *   @param ctx
 * The callback context, which has to be passed back to all accessible API functions.
 */
static void onTestEnd(const ede_callbackContext_t *ctx __attribute__ ((unused)))
{
    /* >=: The requested termination time can already be in the past since the dispatcher
       is not clocked in every simulation time tick. */
    assert(main_tiSim >= TEST_DURATION);

    printf("onTestEnd: " "End of test requested\n");
    tc0_endOfTest = true;    

} /* End of onTestEnd */
 
 
 
/**
 * On-elapse timeout for a group of different timers, which are expected and validated to
 * be always in snyc.
 *   @param ctx
 * The callback context, which has to be passed back to all accessible API functions.
 */

static void onTimeoutSyncTimers(const ede_callbackContext_t *ctx)
{
    /* Get the handle of the timer from the user context data and compare with API function
       result. */
    unsigned int sizeOfUserContextData;
    const userContextSyncTimers_t * const * const pUserData = 
        (const userContextSyncTimers_t * const *)ede_getEventData(ctx, &sizeOfUserContextData);
    assert(sizeOfUserContextData == sizeof(userContextSyncTimers_t *));
    const userContextSyncTimers_t * const pUserContext = *pUserData;
    const unsigned int idxTimer = pUserContext->idxTimer;
    assert(idxTimer < 5);
    const ede_handleTimer_t hTimer = pUserContext->hTimerAry[idxTimer];
    assert(hTimer == ede_getHandleTimer(ctx));
    
    /* Count the callbacks of this timer. */
    static unsigned long cntCallbackAry_[5] = {[4] = 0};
    
    /* Test of synchronism: All timers need to see a callback in the same simulation time
       tick. The first timer, which sees a new simulation timer value will be the first in
       the series of next callbacks. It can validate that the number of calls of all timers
       is identical.
         The last timer is an auto-kill timer. Here we always want to see a single count of
       callbacks. */
    static unsigned long tiSimLast_ = ULONG_MAX;
    if(tiSimLast_ == ULONG_MAX) tiSimLast_ = main_tiSim;
    if(tiSimLast_ != main_tiSim)
    {
        /* Validate simulation time step. */
        assert(main_tiSim == tiSimLast_ + MAIN_TI_TICK_DISPATCHER_0*23);
        
        /* Validate absolute number of callbacks. */
        assert((1+cntCallbackAry_[0])*MAIN_TI_TICK_DISPATCHER_0*23 == main_tiSim);
        
        /* Validate synchronism of first four timers. */
        assert(cntCallbackAry_[0] == cntCallbackAry_[1]
               && cntCallbackAry_[0] == cntCallbackAry_[2]
               && cntCallbackAry_[0] == cntCallbackAry_[3]
              );
        
        /* Validate auto-kill of last timer. */
        assert(cntCallbackAry_[4] == 1);
        
        /* Hinder test repetition for sub-sequent timers' callbacks. */
        tiSimLast_ = main_tiSim;
    }
    
    /* Count the callbacks of this timer. */
    ++ cntCallbackAry_[idxTimer];

    /* The single shot timers are retriggered. This is even done for the auto-kill timer,
       but here it must have no effect. */
    if(idxTimer != 0  &&  idxTimer != 2)
    {
        if(idxTimer == 3)
        {
            /* Test that one timer can re-trigger another one. This must be done by the
               timer, which has the later callback in a cycle; using the other order the
               already due callback of the later timer would be suppressed by re-triggering
               this timer from the earlier callback of the other timer. This fact
               implicitly tests the right order of callback execution for timers being due
               at the same time: It should be the order of timer creation.
                 Passing NULL as handle tests the feature of referring to the implicit
               timer handle. */
            ede_retriggerSingleShotTimer( ctx
                                        , pUserContext->hTimerAry[1]
                                        , 23*MAIN_TI_TICK_DISPATCHER_0
                                        );
            ede_retriggerSingleShotTimer(ctx, NULL, 23*MAIN_TI_TICK_DISPATCHER_0);
        }
        else if(idxTimer == 4)
            ede_retriggerSingleShotTimer(ctx, hTimer, 23*MAIN_TI_TICK_DISPATCHER_0);
        else
            assert(idxTimer == 1);
    }
} /* End of onTimeoutSyncTimers */



/**
 * Initialization callback from dispatcher engine. It initializes the test.
 *   @param ctx
 * The callback context, which has to be passed back to all accessible API functions.
 */

void tc0_initTest(const ede_callbackContext_t *ctx)
{
    assert(ede_getKindOfEvent(ctx) == EDE_EV_EVENT_SOURCE_INT_INIT);
    
    /* A single shot timer is created to terminate the test. */
    ede_createSingleShotTimer( ctx
                             , /* tiPeriod */ TEST_DURATION
                             , onTestEnd
                             , /* refUserContextData */ 0u
                             , /* autoKill */ true
                             );
    
    /* A number of timers is created. All have the same elapse time but only some are
       regular. The single-shot timers are retriggered in their callback, so all timers
       should stay strictly in sync.
         Please note: Retriggered timers and periodic timers will stay in sync only if the
       period is a multiple of the dispatchers time tick. */
    unsigned int idxTi = 0;
    static ede_handleTimer_t hTimerAry_[5];
    static userContextSyncTimers_t userCtxAry_[5];
    hTimerAry_[idxTi] = ede_createPeriodicTimer
                                   ( ctx
                                   , /* tiPeriod */ 23*MAIN_TI_TICK_DISPATCHER_0
                                   , onTimeoutSyncTimers
                                   , /* refUserContextData */ (uintptr_t)&userCtxAry_[idxTi]
                                   );
    assert(hTimerAry_[idxTi] != EDE_INVALID_TIMER_HANDLE);
    userCtxAry_[idxTi].hTimerAry = hTimerAry_;
    userCtxAry_[idxTi].idxTimer = idxTi;
    ++ idxTi;

    hTimerAry_[idxTi] = ede_createSingleShotTimer
                                   ( ctx
                                   , /* tiPeriod */ 23*MAIN_TI_TICK_DISPATCHER_0
                                   , onTimeoutSyncTimers
                                   , /* refUserContextData */ (uintptr_t)&userCtxAry_[idxTi]
                                   , /* autoKill */ false
                                   );
    assert(hTimerAry_[idxTi] != EDE_INVALID_TIMER_HANDLE);
    userCtxAry_[idxTi].hTimerAry = hTimerAry_;
    userCtxAry_[idxTi].idxTimer = idxTi;
    ++ idxTi;
    
    hTimerAry_[idxTi] = ede_createPeriodicTimer
                                   ( ctx
                                   , /* tiPeriod */ 23*MAIN_TI_TICK_DISPATCHER_0
                                   , onTimeoutSyncTimers
                                   , /* refUserContextData */ (uintptr_t)&userCtxAry_[idxTi]
                                   );
    assert(hTimerAry_[idxTi] != EDE_INVALID_TIMER_HANDLE);
    userCtxAry_[idxTi].hTimerAry = hTimerAry_;
    userCtxAry_[idxTi].idxTimer = idxTi;
    ++ idxTi;

    hTimerAry_[idxTi] = ede_createSingleShotTimer
                                   ( ctx
                                   , /* tiPeriod */ 23*MAIN_TI_TICK_DISPATCHER_0
                                   , onTimeoutSyncTimers
                                   , /* refUserContextData */ (uintptr_t)&userCtxAry_[idxTi]
                                   , /* autoKill */ false
                                   );
    assert(hTimerAry_[idxTi] != EDE_INVALID_TIMER_HANDLE);
    userCtxAry_[idxTi].hTimerAry = hTimerAry_;
    userCtxAry_[idxTi].idxTimer = idxTi;
    ++ idxTi;
    
    hTimerAry_[idxTi] = ede_createSingleShotTimer
                                   ( ctx
                                   , /* tiPeriod */ 23*MAIN_TI_TICK_DISPATCHER_0
                                   , onTimeoutSyncTimers
                                   , /* refUserContextData */ (uintptr_t)&userCtxAry_[idxTi]
                                   , /* autoKill */ true
                                   );
    assert(hTimerAry_[idxTi] != EDE_INVALID_TIMER_HANDLE);
    userCtxAry_[idxTi].hTimerAry = hTimerAry_;
    userCtxAry_[idxTi].idxTimer = idxTi;
    ++idxTi;
    assert(idxTi == sizeof(hTimerAry_)/sizeof(hTimerAry_[0]));
    assert(idxTi == sizeof(userCtxAry_)/sizeof(userCtxAry_[0]));

/* Ideas: Several timers created at once, some have same period, kill and restart them in
   callback. Test permanent looping and accurate period time although always recreated. Do
   similar with single shot timer, which are both auto-kill and not. Do same with suspended
   single-shot timers. Suspend or kill timers for a regular callback before they fire, then
   restart them. Assert that their callback is never reached. Put timer handle into timer
   client data and check by assertion. May same with other data. */
   
} /* End of tc0_initTest */





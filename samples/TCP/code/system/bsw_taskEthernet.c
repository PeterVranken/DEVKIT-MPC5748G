/**
 * @file bsw_taskEthernet.c
 * Implementation of the task, which serves the Ethernet driver. The task implements the
 * concept of deferred interrupt handling. It is triggered by the frame Rx and Tx
 * interrupts. Basically, the driver's frame Rx and Tx completed notifications are
 * forwarded to the application's Ethernet task.
 *
 * Copyright (C) 2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   bsw_ethFrameRxCallback
 *   bsw_ethFrameTxCallback
 *   bsw_taskEthernetInternal
 * Local functions
 */

/*
 * Include files
 */

#include "bsw_taskEthernet.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "typ_types.h"
#include "rtos.h"
#include "MPC5748G.h"
#include "bsw_basicSoftware.h"

/*
 * Defines
 */
 
/** This module supports simple progress reporting by console output. The output can be
    turned off by setting the switch to zero. */
#ifdef DEBUG
# define LOGGING 1u
#else
# define LOGGING 0u
#endif

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


/*
 * Defines
 */


/** Mask to define the countable event for triggering the IP protocol task in case it is
    triggered because of a frame Rx event. */
#define EV_RX_ETH_FRAME     0x0000FF00u


/** Mask to define the countable event for triggering the IP protocol task in case it is
    triggered because of completion of a buffer's transmission and in order to trigger
    submission of another (queued) buffer. */
#define EV_TX_ETH_BUFFER    0x00FF0000u

/** Helper for the implementation of a task: The actual count of a countable event is
    extracted from the task parameter. */
#define GET_COUNT_OF_EVENT(taskParam, evMask, shift) (((taskParam)&(evMask))>>(shift))

/** Helper: Get the count from countable event #EV_RX_ETH_FRAME. The task parameter is
    input to the operation. */
#define GET_COUNT_OF_EV_RX_ETH_FRAME(taskParam) \
                            GET_COUNT_OF_EVENT((taskParam), EV_RX_ETH_FRAME, 8u)

/** Helper: Get the count from countable event #EV_TX_ETH_BUFFER. The task parameter is
    input to the operation. */
#define GET_COUNT_OF_EV_TX_ETH_BUFFER(taskParam) \
                            GET_COUNT_OF_EVENT((taskParam), EV_TX_ETH_BUFFER, 16u)

_Static_assert( GET_COUNT_OF_EV_RX_ETH_FRAME(EV_RX_ETH_FRAME) == 0xFFu
                &&  GET_COUNT_OF_EV_TX_ETH_BUFFER(EV_TX_ETH_BUFFER) == 0xFFu
              , "Bad extraction of event counts"
              );

/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** A status counter. Just for progress feedback. Total number of Eth frame Rx IRSs so far. */
volatile unsigned int SBSS_OS(bsw_noRxNotifications) = 0u;

/** A status counter. Just for progress feedback. Total number of Eth Tx buffer-sent IRSs
    so far. */
volatile unsigned int SBSS_OS(bsw_noTxNotifications) = 0u;

/** The RTOS doesn't queue task triggers. Such an event is lost if a task can't be
    triggered in the instance of trying to do so. However, this situation is clearly
    indicated and registered in this counter. Here for Rx events. */
volatile unsigned int SBSS_OS(bsw_noLostTaskTriggersRx) = 0u;

/** The RTOS doesn't queue task triggers. Such an event is lost if a task can't be
    triggered in the instance of trying to do so. However, this situation is clearly
    indicated and registered in this counter. Here for Tx events. */
volatile unsigned int SBSS_OS(bsw_noLostTaskTriggersTx) = 0u;

/** The current time for the lwIP stack, required mainly for timeouts. It is a SW
    maintained time, which is in sync with the regular 10ms task tick of the IP protocol
    task. This task tick drives most of the IP applications, so there is no jitter between
    this SW maintained time and the time, which elapses for these applications.\n
      Unit is Millisecond, resolution is 10ms. The value wraps at the implementation
    maximum, which is after about 50 days of continuous operation. */
volatile uint32_t UNCACHED_P1(bsw_tiLwIP) = 0u;


/*
 * Function implementation
 */

/**
 * Ethernet frame Rx callback. Invoked on "new frame has been received".
 *   @param EIR
 * The interrupt mask register, as it appeared on entry into the interrupt handling and
 * masked for the IRQ bits/sources, which belong into the group, that is served by this
 * function.
 *   @note
 * The reported IRQ bits must not be reset by this function, this has already been done
 * prior to entry into this function.
 */
void bsw_ethFrameRxCallback(uint32_t EIR ATTRIB_DBG_ONLY)
{
    assert(EIR == ENET_EIR_RXF_MASK);
    ++ bsw_noRxNotifications;

    /* We received an Ethernet frame, which needs handling by our protocol state
       machine. So we trigger the task implementing the state machine. */
    if(!rtos_osSendEventCountable( BSW_ID_EV_TRIG_INTERNET_PROTOCOL_TASK
                                 , /*evMask*/ EV_RX_ETH_FRAME
                                 )
      )
    {
        ++ bsw_noLostTaskTriggersRx;
    }
} /* bsw_ethFrameRxCallback */



/**
 * Ethernet buffer Tx callback. Invoked on "transmission complete of next Tx buffer".
 *   @param EIR
 * The interrupt mask register, as it appeared on entry into the interrupt handling and
 * masked for the IRQ bits/sources, which belong into the group, that is served by this
 * function.
 *   @note
 * The reported IRQ bits must not be reset by this function, this has already been done
 * prior to entry into this function.
 */
void bsw_ethFrameTxCallback(uint32_t EIR ATTRIB_DBG_ONLY)
{
    assert(EIR == (ENET_EIR_TXB_MASK|ENET_EIR_TXF_MASK));
    ++ bsw_noTxNotifications;

    /* A Tx buffer has been transmitted, the driver has got room to take another for
       sending. We trigger the task implementing the state machine. It may check if it
       has another buffer to submit for transmission. */
    if(!rtos_osSendEventCountable( BSW_ID_EV_TRIG_INTERNET_PROTOCOL_TASK
                                 , /*evMask*/ EV_TX_ETH_BUFFER
                                 )
      )
    {
        ++ bsw_noLostTaskTriggersTx;
    }
} /* bsw_ethFrameTxCallback */



/**
 * The Ethernet frame interrupt handling is delegated to this task. It doesn't do much but
 * forwarding the notifications from the Ethernet driver to the dedicated Ethernet task in
 * the user code space. The application is supposed to evaluate the Rx frame contents or to
 * submit a Tx frame.\n
 *   The task is activated either regularly by timer for clocking the timeout logic of an
 * IP stack or on frame reception or when an outbound frame has completed transmission.\n
 *   Combining the three events into a single thread ensures that all interaction with the
 * Ethernet driver and the upper layers of an IP protocol stack can be done from one and
 * the same context. This is important as neither the aimed IP stack lwIP nor the driver
 * are implemented thread-safe. Likely (but not certainly analyzed and proven), we could do
 * Rx and Tx with the Ethernet driver from competing contexts but it doesn't bring a true
 * advantage as Rx and Tx are anyway logically connected via the single-threaded
 * implementation of lwIP.\n
 *   Note, this task belongs to user code process P1.
 *   @param taskParam
 * The task parameter is 0 if the task has been activated by the regular 10ms timer event.
 * It is EV_RX_ETH_BUFFER in case of task activation by an Ethernet driver frame Rx event
 * and EV_TX_ETH_BUFFER in case of task activation by an Ethernet driver frame or fragment
 * Tx complete event.\n
 */
int32_t bsw_taskEthernetInternal(uint32_t PID ATTRIB_DBG_ONLY, uint32_t taskParam)
{
    assert(PID == bsw_pidUser);

#if 0
    if((taskParam & ~0x010101u) != 0u)
        iprintf("bsw_taskEthernetInternal: 0x%06lX\r\n", taskParam);
#endif

    /* We can send up to 255 without risking a task activation loss. Theoretically,
       this assertion is wrong but practically the condition almost is an invariant.
      (It's only meant a demonstrative software.) */
    assert(bsw_noLostTaskTriggersRx == 0u  &&  bsw_noLostTaskTriggersTx == 0u);
  
    const unsigned int noNotificationsRx = GET_COUNT_OF_EV_RX_ETH_FRAME(taskParam)
                     , noNotificationsTx = GET_COUNT_OF_EV_TX_ETH_BUFFER(taskParam)
                     , noNotificationsTimer = taskParam & 1u;

    static unsigned int SDATA_P1(totalNoDoubleNotifications_) = 0u;
    static unsigned int SDATA_P1(totalNoTrippleNotifications_) = 0u;
    static unsigned int SDATA_P1(totalNoMultipleNotifications_) = 0u;
    switch(noNotificationsRx + noNotificationsTx + noNotificationsTimer)
    {
    case 0u:
        assert(false);
    case 1u:
        break;
    case 2u:
        ++ totalNoDoubleNotifications_;
        break;
    case 3u:
        ++ totalNoTrippleNotifications_;
        break;
    default:
        ++ totalNoMultipleNotifications_;
        break;
    }

    if(noNotificationsTimer > 0u)
    {
#if LOGGING > 0u
        /* Occasionally print a status message. */
        static unsigned int cnt_ = 0u;
        if(++cnt_ >= 6000u)
        {
            iprintf( "bsw_taskEthernetInternal: %u/%u Rx/Tx frames\r\n"
                   , bsw_noRxNotifications
                   , bsw_noTxNotifications
                   );
            iprintf( "2/3/n-fold task triggers: %u/%u/%u\r\n"
                   , totalNoDoubleNotifications_ 
                   , totalNoTrippleNotifications_
                   , totalNoMultipleNotifications_
                   );
            cnt_ = 0u;
        }
#endif
    }
    
    /* The number of sent events can be higher than the number received so far but there
       must not be a drift. The cyclic difference needs to stay very little. The limit
       in the assertion is chosen arbitrarily. Theoretically, it is wrong but this is just
       meant a demonstrative software. */
    static uint32_t SDATA_P1(totalNoNotificationsRx_) = 0u;
    static uint32_t SDATA_P1(totalNoNotificationsTx_) = 0u;
    totalNoNotificationsRx_ += noNotificationsRx;
    totalNoNotificationsTx_ += noNotificationsTx;
    const uint32_t deltaNoEv ATTRIB_DBG_ONLY = 
                               (bsw_noRxNotifications + bsw_noTxNotifications)
                               - (bsw_noLostTaskTriggersRx + bsw_noLostTaskTriggersTx)
                               - (totalNoNotificationsRx_ + totalNoNotificationsTx_);
    assert(deltaNoEv < 10u);

    /* Call the actual Ethernet evaluation code in the application code space. */
    bsw_taskEthernet(noNotificationsRx, noNotificationsTx, noNotificationsTimer);

    /* Update the current lwIP time. */
    bsw_tiLwIP += 10u * noNotificationsTimer;
    
    /* This task will never end with error. */
    return 0;
    
} /* bsw_taskEthernetInternal */

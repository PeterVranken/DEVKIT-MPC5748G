/**
 * @file lwd_lwIpDemo.c
 * This file contains some demo code for the use of lwIP. It initializes some of the lwIP
 * standard applications, so the evaluation board DEVKIT_MPC5748G will respond to some IP
 * requests from the Windows machine, it is connected to via Ethernet:\n
 *   To run the application from a Windows machine, open a serial connection to the board, 115.2 kBd, 8 Bit, 1
 * stop bit, and connect the board via Ethernet.\n
 *   Normally, the Windows applications can address to the board by name or by IP address.
 * This requires some IP servives like ARP or MDNS, which need to be enabled in the lwIP
 * demo. If this is not the case then an explicit binding of the board's IP address to its
 * MAC address at the Windows side can help. In a Windows shell window, to create this
 * binding, type the preparatory commands:\n
 *   netsh interface ipv4 add neighbors "Ethernet" 192.168.1.200 22-33-44-55-66-77\n
 *   netsh interface ipv4 show neighbors interface="Ethernet"\n
 *   These commands bind the IP address of the evaluation board DEVKIT_MPC5748G to its MAC
 * address. From now on, IP connections opened from the Windows machine to node
 * 192.168.1.200 will address the correct MAC in the emitted Ethernet frames. Note,
 * "Ethernet" stands for the actual name of the Ethernet port of your Windows machine. Use
 * the quotes if the name contains blanks.\n
 *   From a shell window, submit the command:\n
 *   ping 192.168.1.200 or\n
 *   ping DEVKIT_MPC5748G\n
 * The console window should show the processing of the ping request from the Windows
 * machine. Note, that it may take a couple of seconds after startup of the board until the
 * name resolution is working. IP address should work immediately.\n
 *   The Trivial File Transfer Protocol (TFTP) is supported to. File names up to 20
 * characters are allowed. The returned file contents are some repetitions of the chosen
 * file name, which proves that the requested path is evaluated by the application and could
 * be used to select whatever response data. For example, from the shell window, submit the
 * command:\n
 *   tftp 192.168.1.200 GET test/2345/7890123456 test.txt or\n
 *   tftp DEVKIT-MPC5748G GET test/2345/7890123456 test.txt\n
 * The shell command should terminate with a message like this one:\n
 *   Transfer successful: 1750 bytes in 1 second(s), 1750 bytes/s\n
 * and you could inspect the contents of the received "file" test.txt in your text editor.
 *   The application integrates a basic HTTP server. From a shell window, submit the
 * command:\n
 *   curl http://192.168.1.200/get -o - or\n
 *   curl http://DEVKIT-MPC5748G/get -o -\n
 * to fetch the HTML code of the "web page". You can also use this address from an Internet
 * browser.
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
 *   lwd_frameRxCallback
 *   lwd_frameTxCallback
 *   lwd_lwIpDemo_init
 *   lwd_lwIpDemo_main
 * Local functions
 */

/*
 * Include files
 */

#include "lwd_lwIpDemo.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "typ_types.h"
#include "rtos.h"
#include "MPC5748G.h"
#include "bsw_basicSoftware.h"
#include "lwip_lwIPMainFunction.h"
#include "clg_canLoggerOnTCP.h"

/*
 * Defines
 */


/** Task parameter of protocol task in case it is triggered because of a frame Rx event. */
#define EV_RX_ETH_FRAME     1u


/** Task parameter of protocol task in case it is triggered because of completion of a
    buffer's transmission and in order to trigger submission of another (queued) buffer. */
#define EV_TX_ETH_BUFFER    2u

/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** It is assumed that the board is known to the host at IP address 192.168.1.200. The
    inbound ping request is answered using this address as source address. */
static const uint8_t RODATA(_myIPAddr)[4] = {192u, 168u, 1u, 200u};


/*
 * Function implementation
 */

/**
 * Initialize the IP demo; lwIP is started up, the connection with the Ethernet driver is
 * initialized and the application, which do IP communication with lwIP are started up.\n
 *   Note, the Ethernet driver itself is not initialized as part of this function call. It
 * is under control of the operating system.
 *   This function needs to be called before the lwIP demo task is activated the first
 * time.
 */
void lwd_lwIpDemo_init(void)
{
    lwip_initIPStack();
    
    /* The initialization function of the CAN logger application. */
    if(clg_initCanLoggerTcp())
    {    
        iprintf("CAN logger service successfully started. Try: telnet DEVKIT-MPC5748G"
                " 1234\r\n"
               );
    }
    else
    {
        iprintf("CAN logger service can't be started. A Telnet connection won't be"
                " possible. Out of memory?\r\n"
               );
    }
} /* lwd_lwIpDemo_init */



/**
 * The "protocol handling" is delegated to this function. It is invoked from the Ethernet
 * task either regularly for clocking the timeout logic of lwIP or on frame reception or
 * when an outbound frame has completed transmission. (Note, even sending of TCP packets is
 * frequently clocked by frame reception; a packet is sent on demand by the peer, e.g., by
 * ACKnowledge of the preceding packet.)\n
 *   @param taskParam
 * The task parameter is 0 if the task has been activated by the regular 10ms timer event.
 * It is EV_RX_ETH_BUFFER in case of task activation by an Ethernet driver frame Rx event
 * and EV_TX_ETH_BUFFER in case of task activation by an Ethernet driver frame or fragment
 * Tx complete event.
 * The APSW task, which is dedicated to handling notifications from the Ethernet driver.
 * The task is activated by Ethernet frame reception or transmission complete and by
 * regular timer events.
 *   @param noNotificationsRx
 * The number of Ethernet frame Rx events since last activation of the task. This number of
 * Ethernet frames is currently buffered in the driver, waits for fetching and needs
 * processing.
 *   @param noNotificationsTx
 * The number of Ethernet frame Tx events since last activation of the task. The driver has
 * buffer space available to submitted at least this number of Ethernet frames for
 * transmission. (Note, even sending of TCP packets is frequently clocked by frame
 * reception; a packet is sent on demand by the peer, e.g., by ACKnowledge of the preceding
 * packet.)
 *   @param noNotificationsTimer
 * This number of timer events has been occurred since last activation of the task. 
 */
void lwd_lwIpDemo_main( unsigned int noNotificationsRx
                      , unsigned int noNotificationsTx
                      , unsigned int noNotificationsTimer
                      )
{
    /* Activity: The Ethernet driver has completed the transmission of one or more buffers
       so that it got space in its ring buffer for submission of the next ones. We need to
       give the net interface the chance to submit the next (queued) buffers. */
    if(noNotificationsTx > 0u)
        lwip_onEthBufferTxComplete();

    /* Activity: The Ethernet driver has one or more new Rx frames, which we fetch and hand
       over to lwIP for evaluation and response. */
    if(noNotificationsRx > 0u)
        lwip_ethIfPollAllInterfaces();

    if(noNotificationsTimer > 0u)
    {
        /* The step function of the CAN logger application. */
        clg_mainFunction();

        static uint8_t SBSS_P1(cnt100ms_) = 0u;
        if(cnt100ms_ == 0u)
        {
            /* Handle TCP and other LwIP timers. */
            lwip_onTimerTick();

            /* Reload timer. */
            cnt100ms_ = 10u - 1u;
        }
        else
            -- cnt100ms_;
    }
} /* lwd_lwIpDemo_main */

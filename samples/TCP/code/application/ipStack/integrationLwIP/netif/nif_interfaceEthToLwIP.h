#ifndef NIF_INTERFACEETHTOLWIP_INCLUDED
#define NIF_INTERFACEETHTOLWIP_INCLUDED
/**
 * @file nif_interfaceEthToLwIP.h
 * Definition of global interface of module nif_interfaceEthToLwIP.c
 *
 * Copyright (C) 2023-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "typ_types.h"
#include "eth_ethernet.h"
#include "lwip/err.h"
#include "lwip/netif.h"

/*
 * Defines
 */

/** The name of the board. This name is broadcasted to other network nodes with specific IP
    protocols (TBC). */
#define NIF_ETHERNET_HOST_NAME              "DEVKIT-MPC5748G"

/** The MAC address if Ethernet device ENET0 is in use. The value to define is the
    initializer expression for an array of six integers.\n
      Note, we refer to a macro publish by the underlaying Ethernet driver: The driver has
    set the filter for the MAC address of frames to receive and lwIP needs to use the same
    MAC address, e.g., for name or IP address resolution. */
#define NIF_MAC_ADDR_ENET0                  ETH_ENET0_MAC_ADDR

/** The MAC address if Ethernet device ENET1 is in use. The value to define is the
    initializer expression for an array of six integers. */
#define NIF_MAC_ADDR_ENET1                  {0x11,0x22,0x33,0x44,0x55,0x66}

/* IP addresses, etc., for Ethernet interface ENET0.
     APIPA or AUTO_IP: Requires NIF_NET_IF_HAS_AUTO_IP_ENET0=true (below) and LWIP_AUTOIP=1
   (lwipopts.h). Should be used together with DHCP, but this is not a must. If enabled then
   the network, which the DEVKIT-MPC5748G is connected to, needs to have the network ID
   mask 255.255.0.0 and the network ID always is 169.254. See, e.g.,
   https://manuals.konicaminolta.eu/ineo-4000P-4700P/EN/ntwk_guide/what-is-auto-ip-topic.html
   (visited 25.1.2023). On a Windows machine, the needed network settings can be achieved
   by checking radio button "Obtain an IP address automatically" in the property dialog of
   the IP4 protocol settings for the given Ethernet adapter.
     DHCP: Requires NIF_NET_IF_HAS_DHCP_ENET0=true (below) and LWIP_DHCP=1 (lwipopts.h). */
#define NIF_NET_IF_HAS_DHCP_ENET0           true
#define NIF_NET_IF_HAS_AUTO_IP_ENET0        true
#define NIF_NET_IF_IP_ADDR_ENET0            {169,254,1,200}
#define NIF_NET_IF_ADDR_MASK_ENET0          {255,255,0,0}
#define NIF_NET_IF_IP_ADDR_GATEWAY_ENET0    {192,168,1,1}

/* IP addresses, etc., for Ethernet interface ENET1. */
#define NIF_NET_IF_HAS_DHCP_ENET1           false
#define NIF_NET_IF_HAS_AUTO_IP_ENET1        false
#define NIF_NET_IF_IP_ADDR_ENET1            {192,168,2,200}
#define NIF_NET_IF_ADDR_MASK_ENET1          {255,255,255,0}
#define NIF_NET_IF_IP_ADDR_GATEWAY_ENET1    {192,168,2,1}


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialization callback for the specific Ethernet interface ENET0. Called from generic,
    platform independent lwIP initialization function. */
err_t nif_initNetIfForENETDriver(struct netif *pNetIf);

/** Poll ETH driver for Rx frames and feed lwIP in case. */
err_t nif_processPendingEthRxFrame(struct netif *netif, bool *pNoRxFrameAnymore);

/** Signal: Ethernet driver has completed the transmission of a buffer. */
void nif_onEthBufferTxComplete(void);

/*
 * Global inline functions
 */


#endif  /* NIF_INTERFACEETHTOLWIP_INCLUDED */

/**
 * @file lwip_lwIPMainFunction.c
 * "Main function" of lwIP: Here are the APIs implemented, which need to be (regularly)
 * called in order to keep the lwIP stack alive and running. Also the lwIP initialization
 * at startup time is found here.\n
 *   Most of the code here is taken from the original lwIP file
 * contrib/examples/example_app/test.c.
 *
 * Copyright (c) 2001,2002 Florian Schulze.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the authors nor the names of the contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/* Module interface
 *   lwip_initIPStack
 *   lwip_ethIfPollAllInterfaces
 *   lwip_onEthBufferTxComplete
 *   lwip_onTimerTick
 * Local functions
 *   status_callback
 *   link_callback
 *   initNetIf
 *   dns_found
 *   dns_dorequest
 *   lwiperf_report
 *   srv_txt
 *   initLwIPStandardApps
 *   initNetIfsAndApps
 */

/*
 * Include files
 */

#include "lwip_lwIPMainFunction.h"

/* C runtime includes */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "typ_types.h"

/* include the port-dependent configuration */
#include "nif_interfaceEthToLwIP.h"
#include "nif_queueTxPBuf.h"
#include "lwipcfg.h"
#include "mdns_example.h"
#include "tftp_example.h"

#ifdef LWIP_APP_INIT
#include "ipa_ipApplications.h"
#endif

/* C runtime includes */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* lwIP core includes */
#include "lwip/opt.h"

#include "lwip/sys.h"
#include "lwip/timeouts.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/init.h"
#include "lwip/tcpip.h"
#include "lwip/netif.h"
#include "lwip/api.h"

#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/dns.h"
#include "lwip/dhcp.h"
#include "lwip/autoip.h"

/* lwIP netif includes */
#include "lwip/etharp.h"
#include "netif/ethernet.h"

/* applications includes */
#include "lwip/apps/netbiosns.h"
#include "lwip/apps/httpd.h"
#include "apps/httpserver/httpserver-netconn.h"
#include "apps/netio/netio.h"
#include "apps/ping/ping.h"
#include "apps/rtp/rtp.h"
#include "apps/chargen/chargen.h"
#include "apps/shell/shell.h"
#include "apps/tcpecho/tcpecho.h"
#include "apps/tcpecho_raw/tcpecho_raw.h"
#include "apps/udpecho/udpecho.h"
#include "apps/udpecho_raw/udpecho_raw.h"
#include "apps/socket_examples/socket_examples.h"

#include "examples/lwiperf/lwiperf_example.h"
#include "examples/snmp/snmp_example.h"
#include "examples/sntp/sntp_example.h"
#include "examples/mqtt/mqtt_example.h"

#include "examples/httpd/cgi_example/cgi_example.h"
#include "examples/httpd/fs_example/fs_example.h"
#include "examples/httpd/https_example/https_example.h"
#include "examples/httpd/ssi_example/ssi_example.h"

#if NO_SYS
/* ... then we need information about the timer intervals: */
#include "lwip/ip4_frag.h"
#include "lwip/igmp.h"
#endif /* NO_SYS */

#include "netif/ppp/ppp_opts.h"
#if PPP_SUPPORT
# error Sorry, our integration does not support PPP.
#endif /* PPP_SUPPORT */

/* include the port-dependent configuration */
#include "lwipcfg.h"


/*
 * Defines
 */
 
/** Enable some local console output, which is useful for debugging. Set to either 0 or 1. */
#define PRINTF_SUPPORT  1

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

/** An array of all lwIP network interface objects in use. */
static struct netif BSS_P1(_netIfAry)[1];

/* dhcp struct for the ethernet netif */
#if LWIP_DHCP
static struct dhcp BSS_P1(netif_dhcp);
#endif /* LWIP_DHCP */

/* autoip struct for the ethernet netif */
#if LWIP_AUTOIP
static struct autoip BSS_P1(_hasNetIfAutoIP);
#endif /* LWIP_AUTOIP */

/*-----------------------------------------------------------*/

#if LWIP_NETIF_STATUS_CALLBACK
static void status_callback(struct netif *state_netif)
{
    if(netif_is_up(state_netif))
    {
        /* Status callback UP */
#if PRINTF_SUPPORT
# if LWIP_IPV4
        iprintf( "status_callback==UP, local interface IP is %s\r\n"
               , ip4addr_ntoa(netif_ip4_addr(state_netif))
               );
# else   
        iprintf("status_callback==UP\r\n");
# endif
#endif
    }
    else
    {
        /* Status callback DOWN */
#if PRINTF_SUPPORT
        iprintf("status_callback==DOWN\r\n");
#endif
    }
} /* status_callback */
#endif /* LWIP_NETIF_STATUS_CALLBACK */



#if LWIP_NETIF_LINK_CALLBACK
static void link_callback(struct netif *state_netif)
{
#if PRINTF_SUPPORT
    if (netif_is_link_up(state_netif))
    {
        /* Link callback UP */
        iprintf("link_callback==UP\r\n");
    }
    else
    {
        /* Link callback DOWN */
        iprintf("link_callback==DOWN\r\n");
    }
#endif
} /* link_callback */
#endif /* LWIP_NETIF_LINK_CALLBACK */


/**
 * Creation of a lwIP network interface. The netif object is initialized and registered for
 * use in the lwIP stack.\n
 *   This function implements the lwIP initialization steps netif_add(),
 * netif_set_default() and netif_set_up(), according to
 * https://www.nongnu.org/lwip/2_0_x/raw_api.html (Oct 2023). netif_add() invokes the
 * callback nif_initNetIfForENETDriver(), which implements those aspects of the
 * initialization, which depent on the specific, underlying hardware used by the interface.
 * Which are the MCU's ENET devices, in conjunction with the Ethernet driver.\n
 *   The further steps dhcp_start() and autoip_start() are taken, too, if these protocols
 * are enabled by lwIP configuration macros #LWIP_DHCP and #LWIP_AUTOIP, respectively.
 *   @param idxNetIf
 * The net interface to create by zero based index. Range is 0..1, which relates to the two
 * supported MACs of the MPC5748G, ENET0 and ENET1, respectively.
 *   @param ip4Addr
 * The interface will have this IP4 address.
 *   @param ip4AddrMask
 * IP4 address mask. Used to decide, which other IP address can be directly communicated
 * to.
 *   @param ip4AddrGateway
 * IP4 address of a gateway node. A node with this address will be destination for IP
 * packets, which can't directly delivered to the aimed IP address. It is assumed that the
 * node with this address will properly forward those packets.
 *   @param hasIfDHCP
 * Property of underlaying interface: Does it support DHCP?
 *   @param hasIfAutoIP
 * Property of underlaying interface: Does it support Auto IP?
 */
static err_t initNetIf( unsigned int idxNetIf
                      , const uint8_t ip4Addr[4]
                      , const uint8_t ip4AddrMask[4]
                      , const uint8_t ip4AddrGateway[4]
                      , bool hasIfDHCP
                      , bool hasIfAutoIP
                      )
{
#if LWIP_IPV4
    ip4_addr_t ipAddr, ipAddrMask, ipAddrGW;
    ip4_addr_set_zero(&ipAddr);
    ip4_addr_set_zero(&ipAddrMask);
    ip4_addr_set_zero(&ipAddrGW);
    
    /* If not provided by a protocol, the network interface takes the IPv4 addresses from
       static configuration. */
    if(!hasIfDHCP  &&  !hasIfAutoIP)
    {   
        /* Generate other representation of IP addresses as compact 32 Bit integer. */
        IP4_ADDR(&ipAddr, ip4Addr[0], ip4Addr[1], ip4Addr[2], ip4Addr[3]);
        IP4_ADDR(&ipAddrMask, ip4AddrMask[0], ip4AddrMask[1], ip4AddrMask[2], ip4AddrMask[3]);
        IP4_ADDR( &ipAddrGW
                , ip4AddrGateway[0]
                , ip4AddrGateway[1]
                , ip4AddrGateway[2]
                , ip4AddrGateway[3]
                );
    }
#endif /* LWIP_IPV4 */

    /* Create the netIf object. Memory allocation is static, we have an array of all
       objects. */
    struct netif * const pNetIf = netif_add( &_netIfAry[idxNetIf]
#if LWIP_IPV4
                                           , &ipAddr
                                           , &ipAddrMask
                                           , &ipAddrGW
#endif /* LWIP_IPV4 */
                                           , NULL
                                           , nif_initNetIfForENETDriver
                                           , netif_input
                                           );
    assert(pNetIf == &_netIfAry[idxNetIf]);
    netif_set_default(pNetIf);

#if LWIP_IPV6
    netif_create_ip6_linklocal_address(&_netIfAry[idxNetIf], 1);

# if PRINTF_SUPPORT && defined(LWIP_DEBUG)
    iprintf("ip6 linklocal address: ");
    ip6_addr_debug_print(0xFFFFFFFFU & ~LWIP_DBG_HALT, netif_ip6_addr(&_netIfAry[idxNetIf],0));
# endif
#endif /* LWIP_IPV6 */

#if LWIP_NETIF_STATUS_CALLBACK
    netif_set_status_callback(&_netIfAry[idxNetIf], status_callback);
#endif /* LWIP_NETIF_STATUS_CALLBACK */

#if LWIP_NETIF_LINK_CALLBACK
    netif_set_link_callback(&_netIfAry[idxNetIf], link_callback);
#endif /* LWIP_NETIF_LINK_CALLBACK */

#if LWIP_AUTOIP
    if(hasIfAutoIP)
        autoip_set_struct(&_netIfAry[idxNetIf], &_hasNetIfAutoIP);
#endif /* LWIP_AUTOIP */

#if LWIP_DHCP
    if(hasIfDHCP)
        dhcp_set_struct(&_netIfAry[idxNetIf], &netif_dhcp);
#endif /* LWIP_DHCP */

    /* Indicate available Ethernet link to the lwIP stack. */
    netif_set_link_up(pNetIf);

    netif_set_up(&_netIfAry[idxNetIf]);

    err_t status = ERR_OK;
#if LWIP_DHCP
    if(hasIfDHCP)
    {
        const err_t stsDHCP = dhcp_start((struct netif *)&_netIfAry[idxNetIf]);
        if(stsDHCP != ERR_OK)
        {
            assert(false);
            status = stsDHCP;
        }
    }
#endif /* LWIP_DHCP */
#if LWIP_AUTOIP
    else if(hasIfAutoIP)
    {
        const err_t stsAutoIP = autoip_start(&_netIfAry[idxNetIf]);
        if(stsAutoIP != ERR_OK)
        {
            assert(false);
            status = stsAutoIP;
        }
    }
#endif /* LWIP_AUTOIP */

    return status;

} /* initNetIf */


#if LWIP_DNS_APP && LWIP_DNS
static void dns_found(const char *name, const ip_addr_t *addr, void *arg)
{
    LWIP_UNUSED_ARG(arg);
#if PRINTF_SUPPORT
    iprintf("%s: %s\r\n", name, addr? ipaddr_ntoa(addr): "<not found>");
#else
    LWIP_UNUSED_ARG(name);
    LWIP_UNUSED_ARG(addr);
#endif
} /* dns_found */



static void dns_dorequest(void *arg)
{
    //const char * const dnsname = "3com.com";
    const char * const dnsname = "D2Tnet.fr";
    ip_addr_t dnsresp;
    LWIP_UNUSED_ARG(arg);
  
    if(dns_gethostbyname(dnsname, &dnsresp, dns_found, 0) == ERR_OK) {
        dns_found(dnsname, &dnsresp, 0);
    }
} /* dns_dorequest */
#endif /* LWIP_DNS_APP && LWIP_DNS */



/**
 * This function initializes the applications from the lwIP distribution, which have been
 * enabled with compile-time configuration switches in lwipcfg.h.
 */
static void initLwIPStandardApps(void)
{
#if LWIP_DNS_APP && LWIP_DNS
    /* wait until the netif is up (for dhcp, autoip or ppp) */
    sys_timeout(5000, dns_dorequest, NULL);
#endif /* LWIP_DNS_APP && LWIP_DNS */

#if LWIP_CHARGEN_APP
# if LWIP_SOCKET
    chargen_init();
# else
#  error lwIP application chargen requires compilation of sockets.
# endif
#endif /* LWIP_CHARGEN_APP && LWIP_SOCKET */

#if LWIP_PING_APP && LWIP_RAW && LWIP_ICMP
  ping_init(&netif_default->gw);
#endif /* LWIP_PING_APP && LWIP_RAW && LWIP_ICMP */

#if LWIP_NETBIOS_APP && LWIP_UDP
    netbiosns_init();
# ifndef NETBIOS_LWIP_NAME
#  if LWIP_NETIF_HOSTNAME
    netbiosns_set_name(netif_default->hostname);
#  else
    netbiosns_set_name("NETBIOSLWIPDEV");
#  endif
# endif
#endif /* LWIP_NETBIOS_APP && LWIP_UDP */

#if LWIP_HTTPD_APP && LWIP_TCP
# if LWIP_HTTPD_APP_NETCONN
    http_server_netconn_init();
# else /* LWIP_HTTPD_APP_NETCONN */
#  if defined(LWIP_HTTPD_EXAMPLE_CUSTOMFILES)               \
      && LWIP_HTTPD_EXAMPLE_CUSTOMFILES                     \
      && defined(LWIP_HTTPD_EXAMPLE_CUSTOMFILES_ROOTDIR)
  fs_ex_init(LWIP_HTTPD_EXAMPLE_CUSTOMFILES_ROOTDIR);
#  endif
    httpd_init();
#  if defined(LWIP_HTTPD_EXAMPLE_SSI_SIMPLE) && LWIP_HTTPD_EXAMPLE_SSI_SIMPLE
    ssi_ex_init();
#  endif
#  if defined(LWIP_HTTPD_EXAMPLE_CGI_SIMPLE) && LWIP_HTTPD_EXAMPLE_CGI_SIMPLE
    cgi_ex_init();
#  endif
#  if defined(LWIP_HTTPD_EXAMPLE_HTTPS) && LWIP_HTTPD_EXAMPLE_HTTPS
    https_ex_init();
#  endif
# endif /* LWIP_HTTPD_APP_NETCONN */
#endif /* LWIP_HTTPD_APP && LWIP_TCP */

#if LWIP_NETIO_APP && LWIP_TCP
    netio_init();
#endif /* LWIP_NETIO_APP && LWIP_TCP */

#if LWIP_RTP_APP && LWIP_SOCKET && LWIP_IGMP
    rtp_init();
#endif /* LWIP_RTP_APP && LWIP_SOCKET && LWIP_IGMP */

#if LWIP_SHELL_APP && LWIP_NETCONN
    shell_init();
#endif /* LWIP_SHELL_APP && LWIP_NETCONN */

#if LWIP_TCPECHO_APP
# if LWIP_NETCONN && LWIP_TCPECHO_APP_NETCONN
    tcpecho_init();
# else /* LWIP_NETCONN && LWIP_TCPECHO_APP_NETCONN */
    tcpecho_raw_init();
# endif
#endif /* LWIP_TCPECHO_APP && LWIP_NETCONN */

#if LWIP_UDPECHO_APP
# if LWIP_NETCONN && LWIP_UDPECHO_APP_NETCONN
    for(unsigned int idxIf=0u; idxIf<sizeOfAry(_netIfAry); ++idxIf)
        udpecho_init(&_netIfAry[idxIf]);
# else /* LWIP_NETCONN && LWIP_UDPECHO_APP_NETCONN */
    udpecho_raw_init();
# endif /* LWIP_NETCONN && LWIP_UDPECHO_APP_NETCONN */
#endif /* LWIP_UDPECHO_APP */

#if LWIP_SOCKET_EXAMPLES_APP && LWIP_SOCKET
    socket_examples_init();
#endif /* LWIP_SOCKET_EXAMPLES_APP && LWIP_SOCKET */

#if LWIP_MDNS_APP
    mdns_example_init();
#endif

#if LWIP_SNMP_APP
    snmp_example_init();
#endif
#if LWIP_SNTP_APP
    sntp_example_init();
#endif

#if LWIP_TFTP_APP
    tftp_example_init_server();
#endif

#if LWIP_TFTP_CLIENT_APP
    tftp_example_init_client();
#endif

#if LWIP_MQTT_APP
    mqtt_example_init();
#endif

#if LWIP_LWIPERF_APP
    lwiperf_example_init();
#endif

#ifdef LWIP_APP_INIT
    LWIP_APP_INIT();
#endif
} /* initLwIPStandardApps */


/**
 * This function initializes the lwIP stack and the configured applications.
 */
static void initNetIfsAndApps(void)
{
    /* Init network interfaces. In particular the lwIP initialization steps netif_add() and
       netif_set_default(), see https://www.nongnu.org/lwip/2_0_x/raw_api.html (Oct 2023).
         The next mentioned step, netif_set_link_up(), is done
       from nif_interfaceEthToLwIP.c, nif_initNetIfForENETDriver(). This function is the
       callback function of netif_add().
         The next steps, netif_set_up(), dhcp_start() and autoip_start() are done from
       interface_init(), too. The first one unconditionally, the others depending on the
       configuration macros. */
    err_t sts ATTRIB_DBG_ONLY = ERR_OK;
    for(unsigned int idxIf=0u; idxIf<sizeOfAry(_netIfAry); ++idxIf)
    {
        /* This particular project has configuration data only for a single network
           interface. */
        assert(idxIf == 0u);
        
        const uint8_t ip4Addr[4] = NIF_NET_IF_IP_ADDR_ENET0
                    , ip4AddrMask[4] = NIF_NET_IF_ADDR_MASK_ENET0
                    , ip4AddrGateway[4] = NIF_NET_IF_IP_ADDR_GATEWAY_ENET0; 

        const err_t stsIf = initNetIf( idxIf
                                     , ip4Addr
                                     , ip4AddrMask
                                     , ip4AddrGateway
                                     , NIF_NET_IF_HAS_DHCP_ENET0           
                                     , NIF_NET_IF_HAS_AUTO_IP_ENET0      
                                     );
        if(sts == ERR_OK  &&  stsIf != ERR_OK)
            sts = stsIf;

    } /* for(All network interface to create and initialize) */
    
    assert(sts == ERR_OK);
    
    /* Now inititalize the apps running on lwIP. */
    initLwIPStandardApps();

} /* initNetIfsAndApps */



/**
 * This is the main initialization call for lwIP. The core functionality, the connection to
 * the Ethernet interface and the applications doing communication over IP are intialized.
 */
void lwip_initIPStack(void)
{   
    /* Initialize the function from sys_arch, the wrapper around the OS, which provides
       some OS dependent functionality to lwIP, time information in the first place. */
    sys_init();
    
    /* Initialize the netif implementation for the given target platform. */
    nif_queueTxPBuf_initModule();

    /* Initialize the lwIP core functions. */
    lwip_init();
    
    /* Initialize the netif network interfaces and the applications, which will make use of
       lwIP for network communication. The netif objects connect the genric lwIP core
       implementation with a particular, platform dependent Ehernet driver implementation. */
    initNetIfsAndApps();

} /* lwip_initIPStack */


/**
 * This function polls the Ethernet driver on all configured devices for all meanwhile
 * received frame and forwards them to lwIP in case.\n
 *   This is the major API of the lwIP stack to keep it running. The function shall be
 * called from the integrating code either regularly or when the Ethernet driver notifies
 * the reception of a new frame. The latter option is preferred. The former option actually
 * means polling and requires the Ethernet driver to have enough buffer space for storing
 * all frames potentially arriving within the polling cycle time.
 *   @return
 * The number of Rx frames, which were fetched from the driver and passed to lwIP is
 * returned.
 *   @todo
 * The function signature may be inappropriate if several Ethernet devices are in use. They
 * will typically have independent Rx notifications and it is not required to poll all
 * devices if a particular one notifies a new frame. The index of the channel should become
 * an argument of this function. The caller can decide to call it for all devices.
 */
unsigned int lwip_ethIfPollAllInterfaces(void)
{
    unsigned int noRxFrames = 0u;
    for(unsigned int idxIf=0u; idxIf<sizeOfAry(_netIfAry); ++idxIf)
    {
        /* Poll the device for all meanwhile received Rx frames. */
        while(true)
        {
            bool noRxFrameAnymore;
            nif_processPendingEthRxFrame(&_netIfAry[idxIf], &noRxFrameAnymore);
            if(noRxFrameAnymore)
                break;
            else
                ++ noRxFrames;
        }
    }
    
    return noRxFrames;

} /* lwip_ethIfPollAllInterfaces */


/**
 * This function checks the Tx queue for frames (or fragments of such), which have been
 * submitted for transmission on the Ethernet bus but which have not been handed over to
 * the Ethernet driver yet - likely due to a temporary lack of buffer space in the
 * driver.\n
 *   This function is the second API of the lwIP stack to keep it running. The function
 * shall be called from the integrating code either regularly or when the Ethernet driver
 * notifies the transmission of a frame so that it'll have some buffer space freed and can
 * accept a new frame for transmission. The latter option is preferred.\n
 *   The former option actually means polling and has two disadvantages. The maximum Ethernet
 * throughput is reduced. Most likely, an Ethernet driver will submit a frame faster then the
 * polling cycle time. Instead of using the again ready driver for the next frame, the
 * application waits for the next polling cycle to submit the next frame. Secondary, during
 * this time span, the lwIP stack may continue to submit frame fragments (pbufs) and the
 * pbuf queue may overflow and Tx frames were lost.
 *   @note
 * The lwIP core stack implementation is single-threaded. For this API,
 * lwip_ethIfPollAllInterfaces() and lwip_onTimerTick() it means that they must not be used
 * from concurrent context. If lwip_ethIfPollAllInterfaces() and
 * lwip_onEthBufferTxComplete() are connected to the Ethernet drivers interrupts then these
 * need to implement mutual exclusion, e.g., by being served by the same core and having
 * same priority, while lwip_onTimerTick() could be called under interrupt lock.
 */
void lwip_onEthBufferTxComplete(void)
{
    /* Actually, this function is just an alias for nif_onEthBufferTxComplete(), with the
       intention of having all the APIs needed to drive the lwIP stack in a single
       namespace. */
    nif_onEthBufferTxComplete();
    
} /* lwip_onEthBufferTxComplete */


/**
 * This function checks the timeout conditions in the lwIP stack.\n
 *   This function is the third API of the lwIP stack to keep it running. The function
 * shall be called regularly from the integrating code. On every call, lwIP will
 * check the timeouts against an accurate time service. Therefore, neither the period of
 * calling nor the accuracy matter much. Only the maximum time span should be lesser than
 * shortest timeout designation, which is in the magnitude of 500ms. 
 */
void lwip_onTimerTick(void)
{
    /* Actually, this function is just an alias for lwIP's core function
       sys_check_timeouts(), with the intention of having all the APIs needed to drive the
       lwIP stack in a single namespace. */

    /* Handle TCP and other LwIP timers. */
    sys_check_timeouts();
}
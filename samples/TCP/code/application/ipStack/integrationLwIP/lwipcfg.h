#ifndef LWIPCFG_INCLUDED
#define LWIPCFG_INCLUDED
/**
 * @file lwipcfg.h
 * Configuration of lwIP stack suitable for the integration of lwIP with safe-RTOS.\n
 *   The cntents of this file are directly based on lwIP sample file
 * lwip-STABLE-2_2_0_RELEASE/contrib/examples/example_app/lwipcfg.h.ci.
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

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */

/* Configuration for applications. */
#define LWIP_CHARGEN_APP              0
#define LWIP_DNS_APP                  1

/* Set LWIP_HTTPD_APP_NETCONN to 1 to use the netconn http server, otherwise the raw api
   server will be used. */
#define LWIP_HTTPD_APP                0
#define LWIP_HTTPD_APP_NETCONN        0

/* NXP: NetBIOS name server. It responds to name queries for a configurable name. Name
   resolving is not supported. Note that the device doesn't broadcast its own name so can't
   detect duplicate names! */
#define LWIP_NETBIOS_APP              1

#define LWIP_NETIO_APP                0

#define LWIP_MDNS_APP                 1
#define LWIP_MQTT_APP                 0
#define LWIP_PING_APP                 1
#define LWIP_RTP_APP                  0
#define LWIP_SHELL_APP                0
#define LWIP_SNMP_APP                 0
#define LWIP_SNTP_APP                 0
#define LWIP_SOCKET_EXAMPLES_APP      0

/* Set LWIP_TCPECHO_APP_NETCONN to 1 to use the netconn tcpecho server, otherwise the raw
   api server will be used. */
#define LWIP_TCPECHO_APP              1
#define LWIP_TCPECHO_APP_NETCONN      0

#define LWIP_TFTP_APP                 0
#define LWIP_TFTP_CLIENT_APP          0

/* Set LWIP_UDPECHO_APP_NETCONN to 1 to use the netconn tcpecho server, otherwise the raw
   api server will be used. */
#define LWIP_UDPECHO_APP              1
#define LWIP_UDPECHO_APP_NETCONN      0

/* NXP: lwIP iPerf server implementation to measure performance [support only TCP over IPv4] */
#define LWIP_LWIPERF_APP              1

/* Define this to your custom application-init function. */
#define LWIP_APP_INIT                 ipa_initLwIPApplications

/* Our integration doesn't support the netconn or socket API. Several of the standard
   applications must not be enabled. */
_Static_assert( LWIP_CHARGEN_APP == 0
                &&  LWIP_HTTPD_APP_NETCONN == 0
                &&  LWIP_SOCKET_EXAMPLES_APP == 0
                &&  LWIP_TCPECHO_APP_NETCONN == 0
                &&  LWIP_UDPECHO_APP_NETCONN == 0
              , "Netconn and socked API based applications are not supported"
              );

/* Our demo code overloads some of the lwIP standard applications. To avoid clashes with
   function names or IP ports, the same once from the lwIP distribution must not be
   enabled. */
_Static_assert( LWIP_HTTPD_APP == 0
                &&  LWIP_TFTP_APP == 0
                &&  LWIP_TFTP_CLIENT_APP == 0
              , "The HTTP and TFTP applications must not be taken from the lwIP distribution"
              );

/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


#endif  /* LWIPCFG_INCLUDED */

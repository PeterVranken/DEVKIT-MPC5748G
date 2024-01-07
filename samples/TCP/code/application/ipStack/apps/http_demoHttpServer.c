/**
 * @file http_demoHttpServer.c
 * This is the simple HTTP server example from the lwIP manual. However, the manual is not
 * up-to-date any more and the API of lwIP has changed meanwhile. In this file, the code
 * from the manual has been migrated to the up-to--date API of lwIP 2.2.\n
 *   Try: curl http://192.168.1.200/get --output -\n
 * or directly use your browser.\n
 *   Please note that the implementation is for demonstration purposes only. In particular,
 * the error handling has not been elaborated; assertions have been used for unlikely yet
 * possible errors, where runtime error handling would be required. See comments below.
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
 * Local functions
 */

/*
 * Include files
 */

#include "http_demoHttpServer.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "typ_types.h"
#include "lwip/tcp.h"
#include "stm_systemTimer.h"

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

/* This is the data for the actual web page. */
static const char RODATA(htmlPage0)[] =
    "HTTP/1.0 200 OK\r\n"
    "Content-type: text/html\r\n"
    "\r\n"
    "<html>"
      "<head><title>Hello from DEVKIT-MPC5748G</title></head>"
      "<body>"
        "This is a small test page brought to you by DEVKIT-MPC5748G. ";
static const char RODATA(htmlPage1)[] =
        "%u";
static const char RODATA(htmlPage2)[] =
      "</body>"
    "</html>";

static void http_err(void *arg ATTRIB_UNUSED, err_t err)
{
    iprintf( "http_err: Connection %p: Error %i received\r\n"
           , arg
           , (signed)err
           );
} /* http_err */


/* This is the callback function that is called when a TCP segment has arrived in the
   connection. */
static err_t http_recv( void *arg ATTRIB_UNUSED
                      , struct tcp_pcb *pcb
                      , struct pbuf *p
                      , err_t err ATTRIB_UNUSED
                      )
{
    assert(arg == (const void*)pcb);

    /* If we got a NULL pbuf in p, the remote end has closed the connection. */
    if(p != NULL)
    {
        /* For acknowledge: Indicate to protocol stack that all received characters have
           been consumed. */
        tcp_recved(pcb, p->tot_len);

        /* The payload pointer in the pbuf contains the data in the TCP segment. */
        const char * const rq = p->payload;

        /* Check if the request was an HTTP "GET /\r\n". */
        if(rq[0] == 'G'  &&  rq[1] == 'E'  &&  rq[2] == 'T'
           && rq[3] == ' '  &&  rq[4] == '/'
          )
        {
            char cmdBuf[128];
            const uint16_t noCharsCopied = pbuf_copy_partial( p
                                                            , cmdBuf
                                                            , sizeof(cmdBuf)-1u
                                                            , /*offsetInPBuf*/ 5u
                                                            );
            assert(noCharsCopied < sizeof(cmdBuf));
            cmdBuf[noCharsCopied] = '\0';
            iprintf("http_recv: HTTP request: %s\r\n", cmdBuf);

            /* Send the web page to the remote host. A zero in the last argument of
               tcp_write means that the data should not be copied into internal buffers.
                 Note, placing the assertion "tcp_sndbuf(pcb) >= noChars" is wrong and just
               meant for demonstrative purpose. If we can't currently send then we would
               need to wait for a while and continue when some pbuf have been released.
               This requires a more sophisticated state machine as we want to show here. */
            iprintf("http_recv: Max sendable characters: %u\r\n", (unsigned)tcp_sndbuf(pcb));
            uint16_t noChars = sizeof(htmlPage0);
            assert(tcp_sndbuf(pcb) >= noChars);
            err_t rc ATTRIB_DBG_ONLY = tcp_write( pcb
                                                , htmlPage0
                                                , noChars
                                                , /*apiFlags*/ 0
                                                );
            assert(rc == ERR_OK);
            unsigned int noTotalChars = noChars;

            char response[20];
            static unsigned int SBSS_P1(cnt_) = 0u;
            snprintf(response, sizeof(response), htmlPage1, ++cnt_);
            noChars = strlen(response);
            assert(tcp_sndbuf(pcb) >= noChars);
            rc = tcp_write( pcb
                          , response
                          , noChars
                          , /*apiFlags*/ TCP_WRITE_FLAG_COPY
                          );
            assert(rc == ERR_OK);
            noTotalChars += noChars;

            noChars = sizeof(htmlPage2);
            assert(tcp_sndbuf(pcb) >= noChars);
            tcp_write( pcb
                     , htmlPage2
                     , noChars
                     , /*apiFlags*/ 0
                     );
            assert(rc == ERR_OK);
            noTotalChars += noChars;

            iprintf("http_recv: Sent %u Byte\r\n", noTotalChars);
        }

        /* Free the pbuf. */
        pbuf_free(p);
    }

    return ERR_OK;

} /* http_recv */


/* This is the callback function that is called when no data has been transmitted in a
   connection for a significant while. */
static err_t http_idle(void *arg ATTRIB_UNUSED, struct tcp_pcb *pcb)
{
    assert(arg == (const void*)pcb);

    iprintf( "http_idle: Connection %p:%hu: Is idle and will be closed now\r\n"
           , pcb
           , pcb->remote_port
           );

    /* Close the connection. */
    const err_t rc ATTRIB_DBG_ONLY = tcp_close(pcb);
    assert(rc == ERR_OK);

    return ERR_OK;

} /* http_idle */


/* This is the callback function that is called when some response bytes have been
   transmitted. */
static err_t http_sent(void *arg ATTRIB_UNUSED, struct tcp_pcb *pcb, u16_t len)
{
    assert(arg == (const void*)pcb);
    iprintf( "http_sent: Connection %p:%hu: %u Byte of response have been sent\r\n"
           , pcb
           , pcb->remote_port
           , len
           );

    /* Close the connection. */
    const err_t rc ATTRIB_DBG_ONLY = tcp_close(pcb);
    assert(rc == ERR_OK);

    return ERR_OK;

} /* http_sent */


/* This is the callback function that is called when a connection has been accepted. */
static err_t http_accept(void *arg ATTRIB_UNUSED, struct tcp_pcb *pcb, err_t err ATTRIB_UNUSED)
{
    /* We set the callback argument for this connection to the connection pointer itself;
       this is useful to identify the connection even in the error callback. (Knowing well
       that the pointer must not be used in that callback.) */
    tcp_arg(pcb, /*arg*/ (void*)pcb);

    /* Set up the function http_err() to be called upon a connection error. */
    tcp_err(pcb, http_err);

    /* Set up the function http_recv() to be called when data arrives. */
    tcp_recv(pcb, http_recv);

    /* Set up the function http_sent() to be called when response data has been transmitted. */
    tcp_sent(pcb, http_sent);

    /* Set up the function http_idle() to be called while connection is idle. */
    tcp_poll(pcb, http_idle, /*interval*/ 10u /*unit 500ms*/);

    static unsigned int SBSS_P1(noConn_) = 0u;
    iprintf("http_accept: Connection %u: %p:%hu\r\n", ++noConn_, pcb, pcb->remote_port);

    return ERR_OK;

} /* http_accept */


/* The initialization function. */
void http_init(void)
{
    /* Create a new TCP PCB. */
    struct tcp_pcb *pcb = tcp_new();

    /* Bind the PCB to TCP port 80. */
    tcp_bind(pcb, IP_ADDR_ANY, 80);

    /* Change TCP state to LISTEN. */
    struct tcp_pcb * const pcb_listen = tcp_listen(pcb);
    if(pcb_listen != NULL)
        pcb = pcb_listen;

    /* Set up http_accept() function to be called when a new connection arrives. */
    tcp_accept(pcb, http_accept);

} /* http_init */
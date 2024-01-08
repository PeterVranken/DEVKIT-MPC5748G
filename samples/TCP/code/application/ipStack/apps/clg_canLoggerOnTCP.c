/**
 * @file clg_canLoggerOnTCP.c
 * This is the sample implementation of a TCP/IP based service, which is not simply an
 * example from the lwIP distribution but specific to and integrated into the application.
 * It can be used as starting point for your specific service.\n
 *   Note, many copies of this code can live aside to one another inside the same
 * application if only the TCP port number differs.
 *   Try: telnet 192.168.1.200 1234\n
 *   You can try several shell windows all using the telnet command. Up to
 * #CLG_MAX_NO_TCP_CONNECTIONS clients can be served at a time.
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
/* Module interface
 *   clg_initCanLoggerTcp
 *   clg_mainFunction
 * Local functions
 *   findUnusedConnection
 *   getIdxOfConnection
 *   closeConnection
 *   write
 *   onLwIPError
 *   onLwIPSegmentReceived
 *   onLwIPConnectionIdle
 *   onLwIPSent
 *   onLwIPAcceptConnection
 *   reportCANRxSignals
 */

/*
 * Include files
 */

#include "clg_canLoggerOnTCP.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "typ_types.h"
#include "lwip/tcp.h"
#include "stm_systemTimer.h"
#include "cmd_canCommand.h"
#include "cap_canApi.h"
#include "f2d_float2Double.h"
#include "cdt_canDataTables.h"
#include "del_delay.h"

/*
 * Defines
 */

/** The CAN logger service is listening on this TCP port for a connection request from
    telnet. */
#define CLG_TCP_PORT_CAN_LOGGER     1234u

/** The maximum number of TCP/IP connections, which can be established with this service in
    parallel. */
#define CLG_MAX_NO_TCP_CONNECTIONS  3u

/* Note, in this application, the lwIP callback tcp_sent is applied just to give some debug
   level feedback about transmitted data. Normally, we don't need it. It can be enabled by
   setting #DBG_FEEDBACK_ONSENT_DATA to 1. */
#define DBG_FEEDBACK_ON_SENT_DATA   0

/*
 * Local type definitions
 */

/** The data object keeping all runtime information needed to handle a single connection
    with the CAN logger service. */
struct tcpConn_t
{
/// @todo Check: Pointer likely used as Boolean state only, isOpened. Change to state if
// so. We need mote states to distinguish, e.g., the phase after tcp_close() and until
// tcp_recved() acknowledges the actually connection close: All write operations need to be
// suppressed during this phase.
    /** The lwIP connection handle. */
    struct tcp_pcb *pTcpPcb;

#if DBG_FEEDBACK_ON_SENT_DATA == 1
    /** The total number of characters sent via this connection. The counter is not
        saturated and wraps at its implmentation maximum. */
    unsigned int noBytesSent;
#endif

    /** The total number of characters received via this connection. The counter is not
        saturated and wraps at its implmentation maximum. */
    unsigned int noBytesReceived;

    unsigned int someLocalData;
};


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** An array of all currently served TCP connections. */
static struct tcpConn_t DATA_P1(_tcpConnAry)[CLG_MAX_NO_TCP_CONNECTIONS];

/** The number of currently open TCP connections. */
static unsigned int SBSS_P1(_noTcpConn) = 0u;

/*
 * Function implementation
 */

/**
 * Helper: Find a free connection slot in \a _tcpConnAry. Note, the function applies a
 * simple linear search, which is jeutified because the operation is required only once per
 * connection and we anyway don't allow many of those in parallel (mainly due to memory
 * constraints).
 *   @return
 * Get NULL or a slot in \a _tcpConnAry, which is currently unused and can be used for a
 * new connection.
 */
static struct tcpConn_t *findUnusedConnection(void)
{
    struct tcpConn_t *pConn = &_tcpConnAry[0];
    for(unsigned int idxConn=0; idxConn<sizeOfAry(_tcpConnAry); ++idxConn)
    {
        if(pConn->pTcpPcb == NULL)
        {
            assert(_noTcpConn < CLG_MAX_NO_TCP_CONNECTIONS);
#if DBG_FEEDBACK_ON_SENT_DATA == 1
            pConn->noBytesSent = 0u;
#endif
            pConn->noBytesReceived = 0u;
            pConn->someLocalData = 0u;
            return pConn;
        }

        ++ pConn;
    }
    assert(_noTcpConn == CLG_MAX_NO_TCP_CONNECTIONS);
    return NULL;

} /* findUnusedConnection */


/**
 * Helper: Get the zero based index of a connection among all connections. Used only for
 * console feedback.
 *   @return
 * Get the index in the range 0..(#CLG_MAX_NO_TCP_CONNECTIONS-1).
 *   @param pConn
 * The connection object by reference. The pointer is not validated. If a bad pointer is
 * passed in then the result is undefined.
 */
static inline unsigned int getIdxOfConnection(const struct tcpConn_t * const pConn)
{
    return (unsigned int)(pConn - &_tcpConnAry[0]);
}


/**
 * When a TCP connection is closed, update our connection object accordingly, so that
 * memory can be reused for a new TCP connection.
 *   @param pConn
 * The connection object by reference. After return, the pointer must no longer be used.
 */
static void closeConnection(struct tcpConn_t * const pConn)
{
    /// @todo The problem sketched in the lwIP error callback could be tackled by
    // re-defining the "arg" of the lwIP callback to NULL for the connection about to
    // close. Then all callbacks would know, whether or not they belong to a connection,
    // which is still open in our management. The error callback could close our connection
    // object afterwards in case it received a NULL. Rework is required, we should then
    // ensure that this function is always called prior to tcp_abort(); at the moment we do
    // it afterwards.
    assert(pConn->pTcpPcb != NULL);
    pConn->pTcpPcb = NULL;
    -- _noTcpConn;
    assert(_noTcpConn < CLG_MAX_NO_TCP_CONNECTIONS);

} /* closeConnection */


/**
 * Write some data to an established connection. This function is a wrapper around
 * tcp_write() and tcp_output(). It checks the return code of these functions and initiates a
 * connection abort in case of errors.
 *   @return
 * The function normally returns \a true if the data can be written into the TCP stream. In
 * case of errors reported by the lwIP stack, the connection is aborted and the function
 * returns \a false to indicate this.\n
 *   Caution, most lwIP callback require to return ERR_ABRT if a connection abort has been
 * initiated by the callback code. This needs to be obeyed by all client code of this
 * function!
 *   @param noChars
 * The number of characters to write. May be zero; in this case the operation reduces to a
 * flush operation, all characters written before are actully transmitted on the Ethernet.
 */
static bool write( struct tcpConn_t * const pConn
                 , const char * const msg
                 , unsigned int noChars
                 , bool isMsgConst
                 , bool flush
                 )
{
    assert(pConn->pTcpPcb != NULL);

    err_t err = ERR_OK;
    
    if(noChars > 0u)
    {
        err = tcp_write( pConn->pTcpPcb
                       , msg
                       , noChars
                       , /*apiFlags*/ isMsgConst? 0u: TCP_WRITE_FLAG_COPY
                       );
    }

    if(err == ERR_OK)
    {
        /* Data could be written. Shall we initiate a flusha nd send a TCP segment or shall
           we wait for more output data in order to better utilize the TCP frame? */
        if(flush)
            err = tcp_output(pConn->pTcpPcb);
    }

    if(err != ERR_OK)
    {
        iprintf( "Error %i when writing %u characters into TCP connection %i. Connection"
                 " is aborted\r\n"
               , (int)err
               , noChars
               , (int)getIdxOfConnection(pConn)
               );
        tcp_abort(pConn->pTcpPcb);
        closeConnection(pConn);
    }

    return err == ERR_OK;

} /* write */


/**
 * lwIP error callback. Is called after a connection reset and likely in other errornous
 * situations. If it is called then the connection is broken.
 *   @param arg
 * The callback argument; for our particular application the connection object by reference.
 *   @param err
 * The error code, which made the connection fail.
 */
static void onLwIPError(void *arg, err_t err)
{
    /* We don't get an lwIP connection pointer here, the connection is implicitely closed
       when getting this notification. */

    struct tcpConn_t * const pConn = (struct tcpConn_t *)arg;

    /* It is not transparent, when exactly the internal life cycle of the conncetion
       information inside lwIP ends. Partly, it has already ended (this is why lwIP doesn't
       provide the usual PCB to this callback any more) but evidently not completely,
       otherwise we wouldn't get here. */
    /// @todo A serious problem is that we can't safely relate the error to any connection,
    // we know. Normally, it'll be the connection identified by pConn->pTcpPcb but the fact
    // that lwIP reports the error without PCB makes clear that this can be a connection,
    // which had already been closed or aborted before so that pConn->pTcpPcb may be either
    // NULL or even another unrelated, newly established connection. If an error is
    // spontaneously reported, i.e., not as a consequence of or in conjunction with a
    // problem or state change before then we can't react on the error in terms of closing
    // the connection in our managment. A forever blocked connection object could result
    // or, with other words, a memory leak. If this could ever happen then it would be a
    // design flaw of lwIP, which is unlikely. Therefore, we assume that it'll never happen
    // and we put just an assertion to catch it in the unexpected case.
    //   The only way out would be using a unambiguous value for the "arg" of every new
    // connection, e.g., an incremented 32 Bit counter. This would however require an
    // expensive mapping of this value to an existing connection object.
    //   See closeConnection() for another, simpler idea.
    iprintf( "onLwIPError: Connection %i, pConn->pTcpPcb %p: Error %i received\r\n"
           , (int)getIdxOfConnection(pConn)
           , pConn->pTcpPcb
           , (int)err
           );
    if(pConn->pTcpPcb == NULL)
    {
        /* Block for some time to give the DMA the time to send the debug text to the
           serial interface. */
        del_delayMicroseconds(100000u);

        /* Only now halt in the debugger (which would halt the DMA also). */
        assert(false);
    }
} /* onLwIPError */


/**
 * This is the lwIP callback function that is called when a TCP segment has arrived in the
 * connection.
 *   @param arg
 * The callback argument; for our particular application the connection object by reference.
 *   @param pPcb
 * The protocol control block by reference. Effecitively, lwIP's representation of the
 * TCP connection.
 *   @param pPBuf
 * The pbuf by reference, which contains the received data.
 *   @param err
 * An error code. It's not so clear, which errors can occur under which circumstances. We
 * reset to aknown, valid state by TCP reset if an error is reported. This will surely
 * termminate the connection inside lwIP and free the memories.
 */
static err_t onLwIPSegmentReceived( void *arg
                                  , struct tcp_pcb *pPcb
                                  , struct pbuf *pPBuf
                                  , err_t err ATTRIB_UNUSED
                                  )
{
    /// @todo This function is much too complicated and needs cleanup. A concept could be
    // to establish the model of a standard TCP server application. A possible sketch:
    //   Basically, the server application has a callback for a received segment of data,
    // an idle and a timer callback and a write function.
    //   Listening, connection setup and error handling is put into the base class below
    // such an app. The write function can be used from within the receive callback (for
    // immediate responses) and from the idle and the regular timer callback (to
    // autonomously push some information).
    //   Write errors are observed, ERR_MEM will be tolerated for a while, other errors not
    // at all. Not tolerated errors will lead to an abort of the connection.
    //   Receive, idle and timer callback may return with the demand to close the
    // connection (gracefully).
    //   The base class would allow to instantiate different listeners at different ports
    // and each of these has its own limit of parallel connections and its own set of
    // receive, idle, timer callbacks.

    struct tcpConn_t * const pConn = (struct tcpConn_t *)arg;
    const unsigned int idxConn = getIdxOfConnection(pConn);
    assert(idxConn < sizeOfAry(_tcpConnAry)  &&  pConn->pTcpPcb == pPcb  &&  pPcb != NULL);

    /* If we got a NULL pbuf in p, the remote end has closed the connection. */
    if(err == ERR_OK  &&  pPBuf != NULL)
    {
        /* For acknowledge: Indicate to protocol stack that all received characters have
           been consumed. */
        tcp_recved(pPcb, pPBuf->tot_len);

        /* The payload pointer in the pbuf contains the data in the TCP segment. */
        const char *payload = pPBuf->payload;

        pConn->noBytesReceived += (unsigned)pPBuf->tot_len;
        iprintf( "onLwIPSegmentReceived: Connection %u:%hu: %hu Byte have been received\r\n"
               , idxConn
               , pPcb->remote_port
               , pPBuf->tot_len
               );

        /* We check the received data for a hint to quit the connection. Basically, this
           requires a stream implementation as we must not make any assumption in which
           portions the text input typed in telnet will arrive here. By experience, telnet
           will send out as soon as possible -- particularly, it doesn't wait for typing
           Enter -- and this means at latest with the next acknowledge frame for the data
           we send to telnet.
             We use Ctrl-C, a single character to quit the connection. The likelihood to
           see the character at the beginning of the frame is significant but it is still
           not for granted. Maybe, the user sometimes needs to type Ctrl-C more than once.
             We could search the entire payload for Ctrl-C but this is still not easy in
           general as we need to consider possibly chained pbufs.
             Here, we have an incorrect but sufficient solution. 3: Ctrl-C, 4: Ctrl-D, 26:
           Ctrl-Z. */
        const char *pEnd = payload + pPBuf->len;
        bool doClose = false;
        while(payload < pEnd  && !doClose)
        {
            doClose = *payload == '\003'  ||  *payload == '\004'  ||  *payload == '\032';
            ++ payload;
        }

        if(doClose)
        {
            /* We received the demand from the peer to stop sending data. */
            iprintf( "onLwIPSegmentReceived: Connection %u:%hu: Connection is closed"
                     " on demand of peer\r\n"
                   , idxConn
                   , pPcb->remote_port
                   );
            #define MSG "Connection is closed\n\r"
            if(write(pConn, MSG, sizeof MSG - 1u, /* isMsgConst */ true, /* flush */ true))
            {
                const err_t rc ATTRIB_DBG_ONLY = tcp_close(pPcb);
                assert(rc == ERR_OK);
                
                /* We don't call the close function of our own management yet; lwIP will
                   come back with another invocation of the receive callback to indicate
                   the finally closed connection. */
                //closeConnection(pConn);
            }
            else
            {
                /* Nothing to close, write() has already aborted the connection because of
                   an error. */
                err = ERR_ABRT;
            }
            #undef MSG
        }
        else
        {
            #define MSG \
                "Caution, this application doesn't evaluate your input, with the exception" \
                " of Ctrl-C to quit the connection. You typed:\n\r"
            bool success = write( pConn
                                , MSG
                                , /* noChars */ sizeof MSG - 1u
                                , /* isMsgConst */ true
                                , /* flush */ false
                                );
            #undef MSG

            /* This sample aims to provide information to the TCP client. It doesn't take
               input. However, we implement a bit of echoing the input as a sketch how a
               TCP connection can be used for input true. An application could for example
               place a command interpreter here, which allows controlling the application
               to the desired degree. Note that this simple code doesn't consider chained
               pbufs. */
            #define MAX_NO_ECHOED_CHARS 50u
            char msg[MAX_NO_ECHOED_CHARS+2u];
            char *pWr = &msg[0];
            unsigned int noChars = pPBuf->len;
            if(noChars > MAX_NO_ECHOED_CHARS)
                noChars = MAX_NO_ECHOED_CHARS;
            payload = pPBuf->payload;
            pEnd = payload + noChars;
            while(payload < pEnd)
            {
                if(isprint((int)*payload))
                    *pWr = *payload;
                else
                    *pWr = '.';

                ++ pWr;
                ++ payload;
            }
            * pWr++ = '\r';
            * pWr++ = '\n';
            noChars += 2u;
            #undef MAX_NO_ECHOED_CHARS

            if(success && !write(pConn, msg, noChars, /*isMsgConst*/ false, /*flush*/ true))
                success = false;

            if(!success)
                err = ERR_ABRT;
        }

        /* Free the pbuf. */
        pbuf_free(pPBuf);
    }
    else if(pPBuf == NULL)
    {
        iprintf( "onLwIPSegmentReceived: Connection %u:%hu: has been closed by remote"
                 " peer, error %i\r\n"
               , idxConn
               , pPcb->remote_port
               , (int)err
               );
        closeConnection(pConn);

        err = ERR_OK;
    }
    else
    {
        iprintf( "onLwIPSegmentReceived: Connection %u:%hu: Error %i received. Connection"
                 " is aborted\r\n"
               , idxConn
               , pPcb->remote_port
               , (int)err
               );
        tcp_abort(pPcb);
        closeConnection(pConn);

        /* Free the pbuf. */
        pbuf_free(pPBuf);

        err = ERR_ABRT;
    }

    return err;

} /* onLwIPSegmentReceived */


/**
 * This is the callback function that is called when no data has been transmitted in a
 * connection for a significant while, neither Tx nor Rx.
 *   @param arg
 * The callback argument; for our particular application the connection object by reference.
 *   @param pPcb
 * The protocol control block by reference. Effectively, lwIP's representation of the
 * TCP connection.
 */
static err_t onLwIPConnectionIdle(void *arg, struct tcp_pcb *pPcb)
{
    struct tcpConn_t * const pConn = (struct tcpConn_t *)arg;
    const unsigned int idxConn = getIdxOfConnection(pConn);
    assert(idxConn < sizeOfAry(_tcpConnAry));

    /* Close the connection. */
    if(pConn->pTcpPcb == pPcb)
    {
        assert(pPcb != NULL);
        iprintf( "onLwIPConnectionIdle: Connection %u:%hu: Is idle and will be aborted now\r\n"
               , idxConn
               , pPcb->remote_port
               );
        tcp_abort(pPcb);
        closeConnection(pConn);

        /* The use of tcp_abort() requires return value ERR_ABRT. This ensures memory
           freeing of the PCB. Abort causes an error callback and this is where we will do
           our own cleanup. */
        return ERR_ABRT;
    }
    else
    {
        iprintf( "Unexpected state: onIdle, idxConn=%u, pPcb=%p, pConn->pTcpPcb=%p,"
                 " pConn->someLocalData: %u, _noTcpConn=%u\r\n"
               , idxConn
               , pPcb
               , pConn->pTcpPcb
               , pConn->someLocalData
               , _noTcpConn
               );
        del_delayMicroseconds(100000u);
        assert(false);
        return ERR_OK;
    }

} /* onLwIPConnectionIdle */


#if DBG_FEEDBACK_ON_SENT_DATA == 1
/**
 * This is the callback function that is called when some response bytes have been
 * transmitted.
 *   @param arg
 * The callback argument; for our particular application the connection object by reference.
 *   @param pPcb
 * The protocol control block by reference. Effecitively, lwIP's representation of the
 * TCP connection.
 *   @param len
 * The number of bytes, which are acknowledged.
 */
static err_t onLwIPSent(void *arg, struct tcp_pcb *pPcb, u16_t len)
{
    struct tcpConn_t * const pConn = (struct tcpConn_t *)arg;
    const unsigned int idxConn = getIdxOfConnection(pConn);
    assert(idxConn < sizeOfAry(_tcpConnAry)  &&  pConn->pTcpPcb == pPcb  &&  pPcb != NULL);

    if(pConn->pTcpPcb == pPcb)
    {
        pConn->noBytesSent += (unsigned)len;
        iprintf( "onLwIPSent: Connection %u:%hu: %hu Byte of data have been sent\r\n"
               , idxConn
               , pPcb->remote_port
               , len
               );
    }
    else
    {
        iprintf( "onLwIPSent: Connection %u: %hu Byte of sent data have notified after"
                 " closure\r\n"
               , idxConn
               , len
               );
        del_delayMicroseconds(100000u);
        assert(false);
    }

    return ERR_OK;

} /* onLwIPSent */
#endif /* DBG_FEEDBACK_ON_SENT_DATA == 1 */


/**
 * This is the callback function that is called when a connection has been accepted.
 *   @param arg
 * The argument of the callbacks of the listen connection. Not used.
 *   @param pPcb
 * The protocol control block by reference. Effecitively, lwIP's representation of the
 * TCP connection.
 *   @param err
 * An error report. It is unclear, which errors are possible under which conditions and
 * what to do.
 */
static err_t onLwIPAcceptConnection( void *arg ATTRIB_DBG_ONLY
                                   , struct tcp_pcb *pPcb
                                   , err_t err
                                   )
{
    /* For testing purpose only, we had defined an argument for the listen connection,
       which is now reporting a new connection. */
    assert((unsigned)arg == 999u);

    if(err == ERR_OK)
    {
        struct tcpConn_t *pConn = findUnusedConnection();
        if(pConn != NULL)
        {
            /* We accept the new connection. */
            assert(pConn->pTcpPcb == NULL);
            pConn->pTcpPcb = pPcb;
#if DBG_FEEDBACK_ON_SENT_DATA == 1
            pConn->noBytesSent     = 0u;
#endif
            pConn->noBytesReceived = 0u;
            pConn->someLocalData = 0u;

            /* The new connection object will be the callback argument for this connection */
            tcp_arg(pPcb, /*arg*/ pConn);

            /* Set up the function onLwIPError() to be called upon a connection error. */
            tcp_err(pPcb, onLwIPError);

            /* Set up the function onLwIPSegmentReceived() to be called when data arrives. */
            tcp_recv(pPcb, onLwIPSegmentReceived);

            #if DBG_FEEDBACK_ON_SENT_DATA == 1
            /* Set up the function onLwIPSent() to be called when response data has been
               transmitted. */
            tcp_sent(pPcb, onLwIPSent);
            #endif

            /* Set up the function onLwIPConnectionIdle() to be called while connection is
               idle. */
            tcp_poll(pPcb, onLwIPConnectionIdle, /*interval*/ 20u /*unit 500ms*/);

            ++ _noTcpConn;

            iprintf( "onLwIPAcceptConnection: Connection %i: %p:%hu\r\n"
                     "Type Ctrl-C to quit the connection.\r\n"
                   , (int)getIdxOfConnection(pConn)
                   , pPcb
                   , pPcb->remote_port
                   );

            #define MSG "Type Ctrl-C to quit the connection\r\n"
            return write( pConn
                        , MSG
                        , /* noChars */ sizeof MSG - 1u
                        , /* isMsgConst */ true
                        , /* flush */ true
                        )
                   ? ERR_OK
                   : ERR_ABRT;
            #undef MSG
        }
        else
        {
            /* We set the callback argument such that it would indicate that this connection is
               rejected. */
            tcp_arg(pPcb, /*arg*/ NULL);

            iprintf( "onLwIPAcceptConnection: Connection %p:%hu is rejected. No free"
                     " handle any more\r\n"
                   , pPcb
                   , pPcb->remote_port
                   );
            return ERR_RST;
        }
    }
    else
    {
        /* We have received an error. The new connection is rejected. */

        /* We set the callback argument such that it would indicate that this connection is
           rejected. */
        tcp_arg(pPcb, /*arg*/ NULL);

        iprintf( "onLwIPAcceptConnection: Connection %p:%hu has been notified with"
                 " error %i. The new connection is rejected\r\n"
               , pPcb
               , pPcb->remote_port
               , (int)err
               );
        return ERR_RST;
    }
} /* onLwIPAcceptConnection */



/**
 * Core operation of CAN listener: Display the signals, which we are currently listening to.
 *   @param pConn
 * The TCP connection by reference, which the information about received signals is written
 * into.
 */
static void reportCANRxSignals(struct tcpConn_t * const pConn)
{
    /* This function, executed in the lwIP task, shares information with the 10 ms
       application task. This is the synchronization concept:
         The lwIP task has a higher priority than the application task and can preempt it.
       However, this will normally not happen for timer events and this particular function
       is run only when the lwIP task has been awoken by a timer event. The timer events of
       both competing tasks always become due at the same point in time and, due to its
       higher priority, the lwIP task will always execute before the application task.
       Preemption by timer event can occur only if the application task would execute too
       long, beyond the next due time. This function reads information, which is written
       solely by the application task. So even in the exceptional case of a preemption, no
       harm could arise. */

    unsigned int noSigsReported = 0u;
    unsigned int noListenSigs = 0u;
    for( unsigned int idxSigInList=0
       ; idxSigInList<sizeOfAry(cmd_listenerSignalAry)
       ; ++idxSigInList
       )
    {
        const cmd_listenerSigDesc_t const *pSigInList = &cmd_listenerSignalAry[idxSigInList];
        if(pSigInList->idxSignal < sizeOfAry(cdt_canSignalAry))
        {
            /* Access the descriptor of the currently checked signal. */
            const cdt_canSignal_t * const pSig = &cdt_canSignalAry[pSigInList->idxSignal];

            /* Access the descriptor of the received message. */
            assert(pSig->idxMsg < sizeOfAry(cdt_canRxMsgAry));
            const cdt_canMessage_t * const pMsg = &cdt_canRxMsgAry[pSig->idxMsg];

            /* Access the transmission status of the message the signal belongs to. */
            const cap_stsTransmission_t stsRx = pMsg->pInfoTransmission->stsTransmission;

            /* Check if this signal belongs to a just received message. */
            if(pSig->isReceived &&  (stsRx & cap_stTransm_newDataAvailable) != 0u)
            {
                /* Signal belongs to just received message, report new signal value. */
                static char DATA_P1(msg_)[100];
                const int noCharsMsg = snprintf( msg_
                                               , sizeof msg_
                                               , "Message %s (%lu), signal %s: %f %s\r\n"
                                               , pMsg->name
                                               , pMsg->canId
                                               , pSig->name
                                               , f2d(pSig->getter())
                                               , pSig->unit
                                               );
                if(noCharsMsg > 0)
                {
                    uint16_t noChars = sizeof msg_ - 1u;
                    if(noCharsMsg < (int)noChars)
                        noChars = (uint16_t)noCharsMsg;
                    else
                        assert(false);

                    /* Writing the information into the stream can have closing the
                       connection as side effect. This is not reported here but inside the
                       wrapper functon write. */
                    write(pConn, msg_, noChars, /* isMsgConst */ false, /* flush */ false);
                }
                else
                    assert(false);
                
                ++ noSigsReported;
            }

            ++ noListenSigs;
            
        } /* if(List entry contains a signal?) */
        
    } /* for(Check all entries in listener's internal list) */

    static uint16_t SBSS_P1(tiHint_) = 0;
    if(noSigsReported > 0u)
    {
        /* Reload timeout counter. */
        tiHint_ = 0u;

        /* Separate received groups of signals. */
        if(noSigsReported > 1u)
        {
            #define MSG "\r\n"
            write(pConn, MSG, sizeof MSG - 1u, /* isMsgConst */ true, /* flush */ false);
            #undef MSG
        }        
        
        /* Flush buffers. */
        /// @todo TBC: lwIP's tcp_write() doesn't seem to send a frame even if it has got more characters as fit into a frame. We need an explicit tcp_output()
        write(pConn, "", 0u, /* isMsgConst */ true, /* flush */ true);
    }
    else if(++tiHint_ >= 500u)
    {
        if(noListenSigs > 0u)
        {
            #define MSG "No CAN message has been received, which contains a signal to" \
                        " listen to.\r\n"
            write( pConn
                 , MSG
                 , /* noChars */ sizeof MSG - 1u
                 , /* isMsgConst */ true
                 , /* flush */ true
                 );
            #undef MSG
        }
        else
        {
            #define MSG "No CAN signal has been specified for listening. Use command" \
                        " `listen'. Type `help' in the terminal window to find out.\r\n"
            write( pConn
                 , MSG
                 , /* noChars */ sizeof MSG - 1u
                 , /* isMsgConst */ true
                 , /* flush */ true
                 );
            #undef MSG
        }

        tiHint_ = 0u;
    }
} /* reportCANRxSignals */





/**
 * The initialization function of the CAN logger service.
 *   @return
 * Get \a true if the service could be started. \a false will mostly be returned becasue of
 * a lack of memory in the lwIP heap.
 */
bool clg_initCanLoggerTcp(void)
{
    _noTcpConn = 0u;

    /* Create a new TCP PCB. The listen object lives forever in the heap. */
    struct tcp_pcb *pPcb = tcp_new();
    if(pPcb != NULL)
    {
        /* Bind the PCB to TCP port specified port. */
        tcp_bind(pPcb, IP_ADDR_ANY, CLG_TCP_PORT_CAN_LOGGER);

        /* Change TCP state to LISTEN. */
        struct tcp_pcb * const pPcbListen =
                                    tcp_listen_with_backlog(pPcb, CLG_MAX_NO_TCP_CONNECTIONS);
        if(pPcbListen != NULL)
            pPcb = pPcbListen;

#ifdef DEBUG
        /* We set the callback argument for the listen connection. This is just a test to
           demonstrate the way the API works. We don't actually need this argument. */
        tcp_arg(pPcb, /*arg*/ (void*)999);
#endif

        /* Set up onLwIPAcceptConnection() function to be called when a new connection
           arrives. */
        tcp_accept(pPcb, onLwIPAcceptConnection);

        return true;
    }
    else
        return false;

} /* clg_initCanLoggerTcp */


/**
 * The step functions of the state machine handling all TCP connections. It'll be regularly
 * called from the lwIP task. It'll check the connections states and decide whether and
 * which data to send.
 */
void clg_mainFunction(void)
{
    struct tcpConn_t *pConn = &_tcpConnAry[0];
    const struct tcpConn_t * const pEnd = &_tcpConnAry[CLG_MAX_NO_TCP_CONNECTIONS];
    while(pConn != pEnd)
    {
        if(pConn->pTcpPcb != NULL)
        {
            /* Inspect, which signals of interest have been received in the meantime and
               write new signal values into the TCP stream. */
            reportCANRxSignals(pConn);

        } /* if(Visited connection is open?) */

        ++ pConn;
    }
} /* clg_mainFunction */
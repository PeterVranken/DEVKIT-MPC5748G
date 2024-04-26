/**
 * @file ats_accessTimeService.c
 * This is an example of a TCP/IP based service, which is not simply a sample application
 * from the lwIP distribution but specific to and integrated into the DEVKIT-MPC5748G
 * sample. It can be used as starting point for your specific service.\n
 *   This TCP/IP application implements a TCP client, which reads time information from a
 * server. The client addresses to an always available public service in the Internet.
 * (Consequently, it'll normally succeed only if the DEVKIT-MPC57548G is configured for
 * Internet connection.) The operation can fail or succeed and a state machine controls the
 * needed repetitions in case of access problems. When valid time information is received
 * than the SW maintained clock in the application is adjusted to the current time.\n
 *   Please note that locale and time zones are not considered.
 *
 * Copyright (C) 2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   ats_initAccessTimeService
 *   ats_mainFunction
 * Local functions
 *   getMatchOfCaptureGrpAsNum
 *   extractTimeInfo
 *   getIdxOfConnection
 *   closeConnection
 *   write
 *   onLwIPError
 *   onLwIPConnected
 *   onLwIPSegmentReceived
 *   onLwIPConnectionIdle
 *   onLwIPSent
 *   openConnection
 */

/*
 * Include files
 */

#include "ats_accessTimeServer.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "typ_types.h"
#include "lwip/tcp.h"
#include "lwip/priv/tcp_priv.h"
#include "stm_systemTimer.h"
#include "apt_applicationTask.h"

#include "re_regExpMatcher.h"
#include "ats_regExpWorldClockAPI.inc"

_Static_assert( RE_REQUIRE_COMPILER == 0  &&  RE_REQUIRE_MATCHER == 1
              , "Bad configuration of regular expression matcher"
              );


/*
 * Defines
 */

/* Note, in this application, the lwIP callback tcp_sent is applied just to give some debug
   level feedback about transmitted data. Normally, we don't need it. It can be enabled by
   setting #DBG_FEEDBACK_ONSENT_DATA to 1. */
#define DBG_FEEDBACK_ON_SENT_DATA   1

/** The fragment of the HTTP query URL, that is sent to service worldclockapi, which
    specifies the time zone to get the current time for. */
#define WORLDCLOCKAPI_TIME_ZONE     "cet"

/** The time delta in hours between GMT and the requested time zone. */
#define DELTA_T_GMT_TO_TIME_ZONE    2

/*
 * Local type definitions
 */

/** The data object keeping all runtime information needed to handle a single connection
    with the CAN logger service. */
struct tcpConn_t
{
    /** The lwIP connection state. */
    enum stConn_t {stConn_closed, stConn_connecting, stConn_established, stConn_closing} stConn;

    /** A copy of the pointer to the lwIP connection object. This field is actually
        redundant but allows a nicer API of the main method write. */
    struct tcp_pcb *pPcb;

#if DBG_FEEDBACK_ON_SENT_DATA == 1
    /** The total number of characters sent via this connection. The counter is not
        saturated and wraps at its implementation maximum. */
    unsigned int noCharsTx;
#endif

    /** The total number of characters received via this connection. The counter is not
        saturated and wraps at its implementation maximum. */
    unsigned int noCharsRx;
};


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** A particular connection object is used for communication with global time server. */
static struct tcpConn_t DATA_P1(_tcpConn);

/** Number of fully successful synchronization events with time server. A positive HTTP
    response was received and could be evaluated. */
unsigned int DATA_P1(ats_noSyncWithTimeServer) = 0u;

/** Number of time synchronization events with time information picked from the HTTP header
    of the time server response. A negative HTTP response was received and only the header
    could be evaluated. */
unsigned int DATA_P1(ats_noSyncWithHTTPHeader) = 0u;

/*
 * Function implementation
 */

/**
 * Get the first and only match of a capture group and interpret the captured text as
 * unsigned decimal integer number with 1..9 digits. (These constraints are checked by
 * assertion, which makes successful use of this function depend on the regular expression.)
 *   @return
 * Get the result as a signed integer. (Signed has been decided despite of the result never
 * being negative since this data type fits better to the further data flow.)
 *   @param pMatcher
 * The regular expression matcher, which has successfully matched the input, is
 * passed in by reference. It contains the capture group results.
 *   @param inputStream
 * The capture group result has been stored as reference into the original input character
 * string, so we need this string to fetch the data.
 *   @param idxCGrp
 * The capture group by zero based index.
 */
static signed int getMatchOfCaptureGrpAsNum( struct re_matcher_t *pMatcher
                                           , const char * const inputStream
                                           , unsigned int idxCGrp
                                           )
{
    unsigned int idx1stChar, idxEnd;
    const bool success ATTRIB_DBG_ONLY =
            re_getMatchOfCaptureGrp(pMatcher, &idx1stChar, &idxEnd, idxCGrp, /*idxMatch*/ 0u);
    assert(success);

    /* We must not use atoi as we don't have a zero terminated C string. */
    const char *pC = &inputStream[idx1stChar];
    const char * const pEnd = &inputStream[idxEnd];
    assert(pC < pEnd  &&  pEnd - pC <= 9);
    signed int i = 0;
    while(pC < pEnd)
    {
        assert(isdigit((int)*pC));
        i = i*10 + (int)(*pC) - '0';
        ++ pC;
    }

    return i;

} /* getMatchOfCaptureGrpAsNum */


/**
 * Pick time information from the time server HTTP response.
 *   @return
 * The function returns \a true if it found the expected information in the HTTP response
 * and \a false otherwise.
 *   @param pHour
 * If the function returns \a true then the current hours are returned by reference.
 *   @param pMin
 * If the function returns \a true then the current minutes are returned by reference.
 *   @param pSec
 * If the function returns \a true then the current seconds are returned by reference.
 *   @param httpResponse
 * The character string with the HTTP response from the time server.
 *   @param lenHttpResponse
 * \a httpResponse is not a zero terminated C string. Instead, the length of the input is
 * provided as number of characters.
 */
static bool extractTimeInfo( signed int * const pHour
                           , signed int * const pMin
                           , signed int * const pSec
                           , const char * const httpResponse
                           , unsigned int lenHttpResponse
                           )
{
    /* For simplicity, we use a regular expression for picking the time info. This is most
       simple but not really a professional way of doing:
         The regular expression needs to see all text. For fragmented IP data, it means
       that a reliable solution would require a buffering concept, which concatenates all
       received segments until the regular expression matcher is satisfied. Such
       concatenation code may require much expensive RAM and a significant portion of
       code. Particularly the first drawback is normally not acceptable for embedded
       programming.
         Moreover, we query the time at a time server but our regular expression evaluates
       the time information of the HTTP header. This could likely be done with any HTTP
       service. Of course, it is not difficult to extend the regular expression to pick the
       true time information from the response but, by experience, only the HTTP header is
       always in the first received segment. If we want to see the entire response then we
       would have to solve the first issue...
         Using a "normal" parser, which checks the input character by character and which
       can release all seen data, would not suffer from these problems and would be the
       better solution for a tiny embedded system. */

    /* The caller of the regular expression matcher needs to pre-configure the matcher
       object with respect to the memory configuration. The other fields don't care.
         The memory configuration for the matcher depends significantly on the actual
       regular expression. We can tailor it rather tightly as we use the matcher only for a
       single, pre-defined, known expression. */
    struct re_matcherStackElement_t matcherPathElementAry[30];
    struct re_matcherCGrpStackElement_t matcherCGrpStack[20];
    struct re_matcher_t matcher =
    {
        /* The needed size of the memory for path alternatives depends on both, the
           regular expression and the input stream to match against it. It is hard to
           predict and the value, we see here is arbitrarily chosen. On an embedded
           target, this can become a critical optimization. */
        .matcherPathStack = matcherPathElementAry,
        .maxNoPathElements = sizeOfAry(matcherPathElementAry),

        /* The needed size of the memory for capture groups is most often predictable
           for a given regular expression. For most use-cases (if not used inside the
           body of unbounded loops), it barely depends on the input stream. The memory
           should suffice for the number of groups used in the regular expression. */
        .cGrpStack = matcherCGrpStack,
        .maxNoCapturedGrps = sizeOfAry(matcherCGrpStack),
    };
    const bool patternMatches = re_match( &matcher
                                        , &ats_reHttpHdrTime
                                        , httpResponse
                                        , lenHttpResponse
                                        );
    assert(patternMatches == (matcher.err == re_errMatch_success));
    if(patternMatches)
    {
        const bool isHttp200Ok = re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 12) == 1u;

        /* We know our regular expression, so if it matches, then the match result
           structure is an invariant. If this assertion fires then, most likely, the regular
           expression has changed and the evaluating code down here needs according
           maintenance. */
        assert(re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 0) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 1) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 2) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 3) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 4) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 5) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 6) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 7) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 8) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 9) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 10) == 1u
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 11) == 1u

               /* The following groups do match for a positive HTTP response only. */
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 12) == (isHttp200Ok? 1u: 0u)
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 13) == (isHttp200Ok? 1u: 0u)
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 14) == (isHttp200Ok? 1u: 0u)
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 15) == (isHttp200Ok? 1u: 0u)
               &&  re_getNoMatchesCaptureGrp(&matcher, /*idxCGrp*/ 16) == (isHttp200Ok? 1u: 0u)
              );

        if(isHttp200Ok)
        {
            /* Request succeeded, we can extract the time from the time service response. */
            *pHour = getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 15u);
            *pMin  = getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 16u);

            /* There's no explicit second information in the positive response but we can
               take it from the HTTP header. */
            *pSec  = getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 11u);

            ++ ats_noSyncWithTimeServer;

            iprintf( "Got time info: %02u:%02u, %u.%u.%u\r\n"
                   , *pHour
                   , *pMin
                   , getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 14u)
                   , getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 13u)
                   , getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 12u)
                   );
        }
        else
        {
            /* Request failed, but we can extract the time from the HTTP header.
               Unfortunately, this always is the GMT. */
            *pHour = getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 9u);
            *pMin  = getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 10u);
            *pSec  = getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 11u);

            ++ ats_noSyncWithHTTPHeader;

            /* The month is returned as name. */
            unsigned int idx1st, idxEnd;
            const bool success ATTRIB_DBG_ONLY = re_getMatchOfCaptureGrp( &matcher
                                                                        , &idx1st
                                                                        , &idxEnd
                                                                        , /*idxCGrp*/ 6u
                                                                        , /*idxMatch*/ 0u
                                                                        );
            assert(success &&  idxEnd == idx1st+3u);

            iprintf( "Got time info: %02u:%02u:%02u GMT, %u. %c%c%c %u\r\n"
                   , *pHour
                   , *pMin
                   , *pSec
                   , getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 5u)
                   , httpResponse[idx1st], httpResponse[idx1st+1u], httpResponse[idx1st+2u]
                   , getMatchOfCaptureGrpAsNum(&matcher, httpResponse, /*idxCGrp*/ 7u)
                   );

            /* The time information is GMT. We can correct it but all the code to correct
               the date also is too complex for this simple sample. */
            _Static_assert( DELTA_T_GMT_TO_TIME_ZONE >= -12
                            &&  DELTA_T_GMT_TO_TIME_ZONE <= 12
                          , "Bad time zone time shift configured"
                          );
            const signed int dH = DELTA_T_GMT_TO_TIME_ZONE >= 0? DELTA_T_GMT_TO_TIME_ZONE
                                                               : 24+DELTA_T_GMT_TO_TIME_ZONE;
            *pHour += dH;
            if(*pHour > 23)
                *pHour -= 24;

        } /* if(Did HTTP request return 200 OK?) */

    } /* if(Did HTTP response match our expectation, i.e., reg exp?) */

    return patternMatches;

} /* extractTimeInfo */


/**
 * When a TCP connection is closed, update our connection object accordingly, so that
 * memory can be reused for a new TCP connection.
 *   @param pConn
 * The connection object by reference. After return, the pointer must no longer be used.
 */
static void closeConnection(struct tcpConn_t * const pConn)
{
    assert(pConn->stConn != stConn_closed);
    pConn->stConn = stConn_closed;
    pConn->pPcb = NULL;

} /* closeConnection */


/**
 * Write some data to an established connection. This function is a wrapper around
 * tcp_write() and tcp_output(). It checks the return code of these functions and initiates a
 * connection abort in case of errors.
 *   @return
 * The function normally returns \a true if the data can be written into the TCP stream. In
 * case of errors reported by the lwIP stack, the connection is aborted and the function
 * returns \a false to indicate this.\n
 *   The most likely reason for a \a false is the current receive capability of the remote
 * end. No more data then told by tcp_sndbuf() can be sent.\n
 *   Caution, most lwIP callbacks require to return ERR_ABRT if a connection abort has been
 * initiated by the callback code. This needs to be obeyed by all client code of this
 * function!
 *   @param noChars
 * The number of characters to write. May be zero; in this case the operation reduces to a
 * flush operation, all characters written before are actually transmitted on the Ethernet.
 *   @remark
 * The function should no longer be called for a given connection once it has returned \a
 * false, i.e., after the connection has been aborted due to an error. However, this is
 * tolerated; if it is called again after having got \a false then it has no effect and
 * it'll return \a true in order to avoid that the caller assumes a connected reset
 * repeatedly.
 */
static bool write( struct tcpConn_t * const pConn
                 , const char * const msg
                 , unsigned int noChars
                 , bool isMsgConst
                 , bool flush
                 )
{
    if(pConn->stConn == stConn_established)
    {
        err_t err = ERR_OK;

        if(noChars > 0u)
        {
            uint8_t apiFlags = 0u;
            if(!isMsgConst)
                apiFlags |= TCP_WRITE_FLAG_COPY;
            if(!flush)
                apiFlags |= TCP_WRITE_FLAG_MORE;
            err = tcp_write(pConn->pPcb, msg, noChars, apiFlags);
        }

        if(err == ERR_OK)
        {
            /* Data could be written. Shall we initiate a flush and send a TCP segment or
               shall we wait for more output data in order to better utilize the TCP frame? */
            if(flush)
                err = tcp_output(pConn->pPcb);
        }

        if(err != ERR_OK)
        {
            iprintf( "Error %i when writing %u characters into TCP connection %p. Connection"
                     " is aborted\r\n"
                   , (int)err
                   , noChars
                   , pConn->pPcb
                   );
            tcp_abort(pConn->pPcb);
        }

        return err == ERR_OK;
    }
    else
    {
        /* Even if we couldn't write: Do not return \a false. This indicates a connection
           reset to the caller and would guide him to forward this information to lwIP by
           sending error code ERR_ABRT. */
        return true;
    }
} /* write */


/**
 * lwIP error callback. It is called after a received connection reset or connection close
 * or after a connection abort from our side. If it is called then the connection is broken
 * and lwIP has deleted the connection object PCB. We need to close the connection in our
 * management, too.
 *   @param arg
 * The callback argument; for our particular application the connection object by reference.
 *   @param err
 * The error code, which made the connection end. ERR_RST or ERR_CLSD if the connection has
 * been ended from the remote end or ERR_ABRT if either we called tcp_abort() or tcp_abandon()
 * has been called internally
 */
static void onLwIPError(void *arg, err_t err)
{
    /* We don't get an lwIP PCB here, the connection is implicitly closed
       when getting this notification. */

    struct tcpConn_t * const pConn = (struct tcpConn_t *)arg;
    if(pConn->stConn == stConn_connecting)
    {
        iprintf( "onLwIPError: Connection %p: Error %i received. The remote end has rejected"
                 " the new connection\r\n"
               , pConn->pPcb
               , (int)err
               );
    }
    else
    {
        iprintf( "onLwIPError: Connection %p: Error %i received. Connection is closed\r\n"
               , pConn->pPcb
               , (int)err
               );
    }

    closeConnection(pConn);

} /* onLwIPError */


/**
 * lwIP callback for a successfully established connection. (A connection failure would be
 * reported by the other callback onLwIPError.)
 */
static err_t onLwIPConnected(void *arg, struct tcp_pcb *pPcb, err_t err)
{
    struct tcpConn_t * const pConn ATTRIB_DBG_ONLY = (struct tcpConn_t *)arg;

    /* For a TCP client, the established connection should be identical to the one
       having attempted to connect. */
    assert(pPcb == pConn->pPcb);

    if(err == ERR_OK)
    {
        pConn->stConn = stConn_established;
        iprintf( "onLwIPConnected: Connection %p: Connection established with port %hu of"
                 " global time server\r\n"
               , pPcb
               , pPcb->remote_port
               );
        #define WORLDCLOCKAPI_TIME_ZONE "cet"
        #define MSG                                                     \
          "GET /api/json/" WORLDCLOCKAPI_TIME_ZONE "/now HTTP/1.1\r\n"  \
              "Host: worldclockapi.com\r\n"                             \
              "User-Agent: DEVKIT-MPC5748G\r\n"                         \
              "Accept: */*\r\n"                                         \
              "\r\n"
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
        iprintf( "onLwIPConnected: Connection %p: Error %i received when trying to"
                 " connect. New connection is aborted\r\n"
               , pPcb
               , (int)err
               );
        tcp_abort(pPcb);
        return ERR_ABRT;
    }
} /* onLwIPConnected */


/**
 * This is the lwIP callback function that is called when a TCP segment has arrived in the
 * connection.
 *   @param arg
 * The callback argument; for our particular application the connection object by reference.
 *   @param pPcb
 * The protocol control block by reference. Effectively, lwIP's representation of the
 * TCP connection.
 *   @param pPBuf
 * The pbuf by reference, which contains the received data.
 *   @param err
 * An error code. It's not so clear, which errors can occur under which circumstances. We
 * reset to a known, valid state by TCP reset if an error is reported. This will surely
 * terminate the connection inside lwIP and free the memories.
 */
static err_t onLwIPSegmentReceived( void *arg
                                  , struct tcp_pcb *pPcb
                                  , struct pbuf *pPBuf
                                  , err_t err ATTRIB_UNUSED
                                  )
{
    struct tcpConn_t * const pConn = (struct tcpConn_t *)arg;
    assert(pPcb == pConn->pPcb);

    /* If we got a NULL pbuf, the remote end has closed the connection. */
    if(err == ERR_OK  &&  pPBuf != NULL)
    {
        pConn->noCharsRx += (unsigned)pPBuf->tot_len;
        iprintf( "onLwIPSegmentReceived: Connection %p:%hu: %hu Byte have been received\r\n"
               , pPcb
               , pPcb->remote_port
               , pPBuf->tot_len
               );

#if 0
        #define MAX_NO_ECHOED_CHARS 1000u
        char msg[MAX_NO_ECHOED_CHARS+3u];
        char *pWr = &msg[0];
        unsigned int noChars = pPBuf->len;
        if(noChars > MAX_NO_ECHOED_CHARS)
            noChars = MAX_NO_ECHOED_CHARS;
        const char *payload = pPBuf->payload;
        const char * const pEnd = payload + noChars;
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
        * pWr++ = '\0';
        noChars += 3u;
        #undef MAX_NO_ECHOED_CHARS
        fputs(msg, stdout);
#endif

        /* For acknowledge: Indicate to protocol stack that all received characters have
           been consumed. */
        tcp_recved(pPcb, pPBuf->tot_len);

        /* Free the pbuf. */
        pbuf_free(pPBuf);

        /* Close the connection as soon as parsing of data indicates that all expected
           content has been got. */
        uint32_t ti = stm_getSystemTime(/*idxStmTimer*/ 0u);
        signed int h, m, s;
        const bool parsingDone = extractTimeInfo(&h, &m, &s, pPBuf->payload, pPBuf->len);
        ti = stm_getSystemTime(/*idxStmTimer*/ 0u) - ti;
        if(parsingDone)
        {
            apt_setCurrentTime(h, m, s);

            /* If this is the first success the we initiate regular time display to make
               the success apparent. However, don't persist on it; if the user has switched
               the display off again, then we shuld not annoy him. */
            static bool DATA_P1(isFirstSuccess_) = true;
            if(isFirstSuccess_ && !apt_isEnabledRegularTimeDisplay())
                apt_enableRegularTimeDisplay(/*enable*/ true, /*tiCycleInS*/ 10u);
            isFirstSuccess_ = false;
        }
        else
        {
            iprintf("CAUTION: Failed to parse HTTP response from time server."
                    " This can point to a maintenance problem of the sample code:"
                    " Does the regular expression still suits for the HTTP response?\r\n"
                   );
        }
        _Static_assert(STM_TIMER_0_CLK == 80000000u, "Bad scaling of time designation");
        iprintf("Decoding the HTTP response took %lu ns\r\n", (ti*25u)/2u);

        /* See extractTimeInfo(): Our simple way to pick the time from the HTTP
           response would benefit from getting more received segments. If they first
           segment doesn't help then others would help any more, neither. We can close
           the connection regardless whether or not we got the desired information. */
        iprintf( "onLwIPSegmentReceived: Connection %p: GET response consumed."
                 " Connection is closed\r\n"
               , pPcb
               );
        tcp_close(pPcb);

        /* err remains ERR_OK. */
    }
    else if(pPBuf == NULL)
    {
        iprintf( "onLwIPSegmentReceived: Connection %p has been closed by remote"
                 " peer, error %i\r\n"
               , pPcb
               , (int)err
               );
        closeConnection(pConn);

        err = ERR_OK;
    }
    else
    {
        iprintf( "onLwIPSegmentReceived: Connection %p: Error %i received. Connection"
                 " is aborted\r\n"
               , pPcb
               , (int)err
               );
        tcp_abort(pPcb);

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
 *   @remark
 * For this particular application, idle is normalle never entered. We continuously write
 * data into the stream, which avoids to ever become idle.
 */
static err_t onLwIPConnectionIdle(void *arg, struct tcp_pcb *pPcb)
{
    struct tcpConn_t * const pConn = (struct tcpConn_t *)arg;
    assert(pConn->pPcb == pPcb);

    /* Close the connection. */
    if(pConn->stConn == stConn_established)
    {
        assert(pPcb != NULL);
        iprintf( "onLwIPConnectionIdle: Connection %p: Is idle and will be closed now\r\n"
               , pPcb
               );
        tcp_close(pPcb);
        pConn->stConn = stConn_closing;

        return ERR_OK;
    }
    else
    {
        assert(pConn->stConn == stConn_closing);
        iprintf( "onLwIPConnectionIdle: Connection %p: Is idle and has been closed. Waiting"
                 " for remote acknowledge took too long, connection is aborted now\r\n"
               , pPcb
               );
        tcp_abort(pPcb);

        return ERR_ABRT;
    }
} /* onLwIPConnectionIdle */


#if DBG_FEEDBACK_ON_SENT_DATA == 1
/**
 * This is the callback function that is called when some bytes have been transmitted and
 * acknowledged by the remote peer.
 *   @param arg
 * The callback argument; for our particular application the connection object by reference.
 *   @param pPcb
 * The protocol control block by reference. Effectively, lwIP's representation of the
 * TCP connection.
 *   @param len
 * The number of bytes, which are acknowledged.
 */
static err_t onLwIPSent(void *arg, struct tcp_pcb *pPcb, u16_t len)
{
    struct tcpConn_t * const pConn = (struct tcpConn_t *)arg;
    assert(pConn->pPcb == pPcb  &&  pPcb != NULL);

    if(pConn->stConn != stConn_closed)
    {
        pConn->noCharsTx += (unsigned)len;
        iprintf( "onLwIPSent: Connection %p: %hu Byte of data have been sent\r\n"
               , pPcb
               , len
               );
    }
    else
        assert(false);

    return ERR_OK;

} /* onLwIPSent */
#endif /* DBG_FEEDBACK_ON_SENT_DATA == 1 */


/**
 * Open a connection to the time server.
 */
static bool openConnection(void)
{
    struct tcpConn_t * const pConn = &_tcpConn;
#if DBG_FEEDBACK_ON_SENT_DATA == 1
    pConn->noCharsTx = 0u;
#endif
    pConn->noCharsRx = 0u;

    /* Create a new TCP PCB. The listen object lives forever in the heap. */
    struct tcp_pcb *pPcb = tcp_new();
    bool success = pPcb != NULL;

    if(success)
    {
        pConn->stConn = stConn_connecting;
        pConn->pPcb = pPcb;

        /* The needed callbacks are installed for the intended connection. */

        /* The new connection object will be the callback argument for this connection. */
        tcp_arg(pPcb, /*arg*/ pConn);

        /* Set up the function onLwIPError() to be called upon a failing connection or an
           unexpected termination of the connection. */
        tcp_err(pPcb, onLwIPError);

        /* Set up the function onLwIPSegmentReceived() to be called when data arrives. */
        tcp_recv(pPcb, onLwIPSegmentReceived);

        #if DBG_FEEDBACK_ON_SENT_DATA == 1
        /* Set up the function onLwIPSent() to be called when data has been transmitted. */
        tcp_sent(pPcb, onLwIPSent);
        #endif

        /* Set up the function onLwIPConnectionIdle() to be called while connection is
           idle. */
        tcp_poll(pPcb, onLwIPConnectionIdle, /*interval*/ 240u /*unit 500ms*/);

        /* Try a connect to the given IP address and port of the time server. On returned,
           we don't know yet, whether the connection could be established or not. Success
           is signalled via the specified callback, while a rejected connection would be
           reported via the error callback. */
        const ip_addr_t ipAddrTimeServer = IPADDR4_INIT_BYTES(20u, 49u, 104u, 6u);
        const u16_t port = 80u;
        success = tcp_connect(pPcb, &ipAddrTimeServer, port, onLwIPConnected) == ERR_OK;

        /* Connection is not possible due to a lack of memory. Nothing has been transmitted
           and the remote end has not even seen the attempt to connect. */
        if(!success)
        {
            pConn->stConn = stConn_closed;
            pConn->pPcb = NULL;
            tcp_free(pPcb);
        }
    }

    return success;

} /* openConnection */


/**
 * The initialization function of the time service.
 */
void ats_initAccessTimeService(void)
{
    struct tcpConn_t * const pConn = &_tcpConn;
#if DBG_FEEDBACK_ON_SENT_DATA == 1
    pConn->noCharsTx = 0u;
#endif
    pConn->noCharsRx = 0u;
    pConn->stConn = stConn_closed;
    pConn->pPcb = NULL;

} /* ats_initAccessTimeService */


/**
 * The step function of the state machine handling all TCP connections. It'll be regularly
 * called from the lwIP task. It'll check the connections states and decide whether and
 * which data to send.
 */
void ats_mainFunction(void)
{
    #define TI_FIRST_ACCESS_IN_S                        20u
    #define TI_NEXT_ACCESS_IN_S                         60u
    #define TI_REPEAT_ACCESS_AFTER_HTTP_HDR_SYNC_IN_S   300u
    #define TI_REPEAT_ACCESS_AFTER_FULL_SYNC_IN_S       86400u

    static unsigned int SDATA_P1(tiIn10Ms_) = TI_FIRST_ACCESS_IN_S * 100u;
    static unsigned int BSS_P1(noSyncWithTimeServer_last_) = 0u;
    static bool DATA_P1(noSyncSincePwrUp_) = true;
    static bool SDATA_P1(stConnIsClosed_last_) = true;

    if(_tcpConn.stConn == stConn_closed)
    {
        if(!stConnIsClosed_last_)
        {
            assert(tiIn10Ms_ == 0u);

            /* This is the very first clock tick after completing an attempt to
               synchronize the time. We can evaluate the result and decide, when to try
               next time. */

            /* Set time span until next attempt to connect to the time server: Shortly if
               it didn't succeed yet at all, on short notice if we had contact but with
               negative resposne and only after along while to resynchronize the internal
               SW maintained clock if everything had succeeded. */
            noSyncSincePwrUp_ = noSyncSincePwrUp_
                                && ats_noSyncWithTimeServer == 0u
                                && ats_noSyncWithHTTPHeader == 0u;
            if(noSyncSincePwrUp_)
            {
                /* No synchronization at all in this cycle. */
                tiIn10Ms_ = TI_NEXT_ACCESS_IN_S * 100u;
            }
            else if(ats_noSyncWithTimeServer != noSyncWithTimeServer_last_)
            {
                /* Full, correct synchronization of SW clock */
                tiIn10Ms_ = TI_REPEAT_ACCESS_AFTER_FULL_SYNC_IN_S * 100u;
                noSyncWithTimeServer_last_ = ats_noSyncWithTimeServer;
            }
            else
            {
                /* Outermost a simple synchronization with time information in HTTP header
                   has succeeded, while time service itself was not available. Or a re-sync
                   after long while failed entirely. */
                tiIn10Ms_ = TI_REPEAT_ACCESS_AFTER_HTTP_HDR_SYNC_IN_S * 100u;
            }
        }
        else if(tiIn10Ms_ > 0u)
            -- tiIn10Ms_;

        if(tiIn10Ms_ == 0u)
        {
            /* It's time to open a connection for fetching time information and
               synchronization of the own, SW maintained clock. If opening the connection
               succeeds, then we don't need to do anything else from here, the main
               function; the lwIP state machine with its callbacks will directly drive all
               further activities like reception of response segments from the time server
               and their evaluation - till closure of now opened connection. */
            iprintf("ats_mainFunction: Try to open a connection with global time service\r\n");
            const bool success = openConnection();
            if(success)
            {
                assert(_tcpConn.stConn != stConn_closed);
            }
            else
            {
                assert(_tcpConn.stConn == stConn_closed);

                /* This points to an out-of-memory problem of lwIP, not to communication
                   problem with the time server. We shouldn't immediately re-try. */
                tiIn10Ms_ = TI_NEXT_ACCESS_IN_S * 100u;
            }
        }

        stConnIsClosed_last_ = _tcpConn.stConn == stConn_closed;
    }
    else
    {
        /* Time is not measured while we have a working synchronization attempt. Timing only
           relates to the time spans in between two attempts. */
    }
} /* ats_mainFunction */

/*
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Dirk Ziegelmeier <dziegel@gmx.de>
 *
 */

#include "tftp_example.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "lwip/apps/tftp_client.h"
#include "lwip/apps/tftp_server.h"

#include "typ_types.h"

#if LWIP_UDP

/* Define a base directory for TFTP access
 * ATTENTION: This code does NOT check for sandboxing,
 * i.e. '..' in paths is not checked! */
#ifndef LWIP_TFTP_EXAMPLE_BASE_DIR
#define LWIP_TFTP_EXAMPLE_BASE_DIR ""
#endif

/* Define this to a file to get via tftp client */
#ifndef LWIP_TFTP_EXAMPLE_CLIENT_FILENAME
#define LWIP_TFTP_EXAMPLE_CLIENT_FILENAME "test.bin"
#endif

/* Define this to a server IP string */
#ifndef LWIP_TFTP_EXAMPLE_CLIENT_REMOTEIP
#define LWIP_TFTP_EXAMPLE_CLIENT_REMOTEIP "192.168.0.1"
#endif

/** Reading a file is emulated for the TFTP operation GET by returning the file name a
    number of times. This is the repetition factor. */
#define NO_REPETITIONS_PER_GET  50

struct file_t
{
    char name[TFTP_MAX_FILENAME_LEN+1];
    signed int noCharsLeft;
    signed int readPos;
};

#define MAX_NO_FILES    10u
static struct file_t _fileAry[MAX_NO_FILES];

static void *
tftp_open_file(const char* fname, u8_t is_write)
{
    if (is_write)
        return (void*)0;
    else
    {
        /* Look for available file handle. */
        for(unsigned int u=0u; u<sizeOfAry(_fileAry); ++u)
        {
            if(_fileAry[u].name[0] == (char)0)
            {
                snprintf(_fileAry[u].name, sizeof(_fileAry[u].name), "%s", fname);
                _fileAry[u].noCharsLeft = 0;
                _fileAry[u].readPos = -1;
                return (void*)(u+1);
            }
        }
        return (void*)0;
    }
}


static void*
tftp_open(const char* fname, const char* mode, u8_t is_write)
{
  LWIP_UNUSED_ARG(mode);
  return tftp_open_file(fname, is_write);
}

static void tftp_close(void* handle)
{
    const unsigned int idxFile = (unsigned int)handle - 1u;
    if(idxFile < sizeOfAry(_fileAry))
    {
        _fileAry[idxFile].name[0] = (char)0;
        _fileAry[idxFile].noCharsLeft = 0;
        _fileAry[idxFile].readPos = -1;
    }
}

static int tftp_read(void* handle, void* buf, int bytes)
{
    /* Check restriction of given implementation. */
    assert(bytes >= 2);

    unsigned int noCharsRead = 0u;
    const unsigned int idxFile = (unsigned int)handle - 1u;
    if(idxFile < sizeOfAry(_fileAry))
    {
        /* The n times repeated response text, its length and its size in memory. */
        char msg[100];
        signed int lenOfMsg = snprintf( msg
                                      , sizeof(msg)
                                      , "This is file %s. "
                                      , _fileAry[idxFile].name
                                      );
        assert(lenOfMsg >= 0);
        if((unsigned)lenOfMsg >= sizeof(msg))
            lenOfMsg = (int)sizeof(msg) - 1;

        if(_fileAry[idxFile].readPos < 0)
        {
            _fileAry[idxFile].noCharsLeft = NO_REPETITIONS_PER_GET * lenOfMsg;
            _fileAry[idxFile].readPos = 0;
        }

        char *pWr = (char*)buf;
        const char *pWrEnd = (char*)buf + bytes;
        while(pWr < pWrEnd  &&  _fileAry[idxFile].noCharsLeft > 0)
        {
            assert(_fileAry[idxFile].readPos >= 0  &&  _fileAry[idxFile].readPos < lenOfMsg);
            * pWr++ = msg[_fileAry[idxFile].readPos];
            ++ noCharsRead;
            -- _fileAry[idxFile].noCharsLeft;
            if(++_fileAry[idxFile].readPos >= lenOfMsg)
                _fileAry[idxFile].readPos = 0u;
        }
    }
    return noCharsRead > 0u? (int)noCharsRead: -1;
}


static int
tftp_write(void* handle, struct pbuf* p)
{
#if 1
    LWIP_UNUSED_ARG(handle);
    LWIP_UNUSED_ARG(p);
    
    /// @todo Parse data p->len (and chain) as input command, to demonstrate usage of the
    /// tftp service for controlling the application. We could, e.g., modify the number of
    /// repetitions, NO_REPETITIONS_PER_GET, which currently is a compile-time constant.
    return -1;
#else
    while (p != NULL)
    {
        if (fwrite(p->payload, 1, p->len, (FILE*)handle) != (size_t)p->len)
            return -1;

        p = p->next;
    }
    return 0;
#endif
}

/* For TFTP client only */
static void
tftp_error(void* handle, int err, const char* msg, int size)
{
    char message[100];

    LWIP_UNUSED_ARG(handle);

    memset(message, 0, sizeof(message));
    MEMCPY(message, msg, LWIP_MIN(sizeof(message)-1, (size_t)size));

    iprintf("TFTP error: %d (%s)", err, message);
}

static const struct tftp_context tftp = {
    .open  = tftp_open,
    .close = tftp_close,
    .read  = tftp_read,
    .write = tftp_write,
    .error = tftp_error,
};

void
tftp_example_init_server(void)
{
    tftp_init_server(&tftp);
}

void
tftp_example_init_client(void)
{
    void *f;
    err_t err;
    ip_addr_t srv;
    int ret = ipaddr_aton(LWIP_TFTP_EXAMPLE_CLIENT_REMOTEIP, &srv);
    LWIP_ASSERT("ipaddr_aton failed", ret == 1);

    err = tftp_init_client(&tftp);
    LWIP_ASSERT("tftp_init_client failed", err == ERR_OK);

    f = tftp_open_file(LWIP_TFTP_EXAMPLE_CLIENT_FILENAME, 1);
    LWIP_ASSERT("failed to create file", f != NULL);

    err = tftp_get(f, &srv, TFTP_PORT, LWIP_TFTP_EXAMPLE_CLIENT_FILENAME, TFTP_MODE_OCTET);
    LWIP_ASSERT("tftp_get failed", err == ERR_OK);
}

#endif /* LWIP_UDP */

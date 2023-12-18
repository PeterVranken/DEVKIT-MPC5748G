#ifndef NIF_QUEUETXPBUF_INCLUDED
#define NIF_QUEUETXPBUF_INCLUDED
/**
 * @file nif_queueTxPBuf.h
 * Definition of global interface of module nif_queueTxPBuf.c
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

#include "typ_types.h"
#include "eth_ethernet.h"
#include "lwip/pbuf.h"


/*
 * Defines
 */

/** Configure the compilation of some simple buffer statistics, which may help to find the
    right queue size. */
#ifndef NIF_SUPPORT_BUFFER_USAGE_STATISTICS
# ifdef DEBUG
#  define NIF_SUPPORT_BUFFER_USAGE_STATISTICS   1
#else
#  define NIF_SUPPORT_BUFFER_USAGE_STATISTICS   0
# endif
#endif

/*
 * Global type definitions
 */

/* A queue element. A queued pbuf is associated with the ENET device and the ring buffer
   element in the ENET device, which is used to actually transmit it. */
struct nif_queueElemTxPBuf_t
{
    /** The ENET device by zero based index, which the pbuf is transmitted on. */
    uint8_t idxEthDev;
    
    /** The pbuf in prgress by reference. */
    struct pbuf *pPBuf;

    /** The handle of the submitted, pending frame as got from the Ethernet driver, when
        initiating the transmission of the pbuf. This field is valid only in phase 2, when
        a queued pbuf was handed over to the Ethernet driver. */
    uintptr_t hTxFrame;
};

/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialize the module. An empty queue is created. */
void nif_queueTxPBuf_initModule(void);

/** A buf is put into the queue, when lwIP calls the output function for the pbuf. */
err_t nif_queueTxPBuf_enqueue(unsigned int idxEthDev, struct pbuf * const pPBuf);

/** After the ETH driver has signalled transmission-complete for the eldest pbuf, this pbuf
    - the head of the queue - can be removed from the queue. */
void nif_queueTxPBuf_dequeue(void);

/** Query the queue for the eldest pbuf, which is still in phase one. */
struct nif_queueElemTxPBuf_t * nif_queueTxPBuf_getPBufWaitingForSubmission(void);

/** Query the queue for the eldest pbuf, which is waiting for transmission complete. */
const struct nif_queueElemTxPBuf_t * 
                                nif_queueTxPBuf_getPBufWaitingForTransmissionComplete(void);

/** Signal for the eldest pbuf still in phase one that it has entered phase two. */
void nif_queueTxPBuf_advancePBufWaitingForSubmission(void);



/*
 * Global inline functions
 */


#endif  /* NIF_QUEUETXPBUF_INCLUDED */

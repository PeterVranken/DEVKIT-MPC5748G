/**
 * @file nif_queueTxPBuf.c
 * The Tx part of the lwIP-to-ETH-driver interface requires a queue to keep track of those
 * pbufs, which have been handed over to the ETH driver and which may or may not have
 * completed transmission yet. We support the zero copy concept, we provide the driver the
 * frame payload data by reference only and the referenced data, a pbuf, needs to persist
 * until the driver has sent the frame. (At least till its DMA has transferred the date
 * into the HW's shift register.) Only when the driver signals sent buffers, then we can
 * release the pbuf holding the frame contents. This is solved by a queue of pbufs, which
 * is kept in sync with the ring buffer operation of the ETH driver.\n
 *   The queue distinguishes two phases in the life cycle of a Tx pbuf. In the first pahse,
 * it has been output by lwIP but not yet handed over to the ETH driver. When the driver is
 * ready to take a new pbuf, it enters the second phase. In the second phase, the pbuf
 * waits in the queue for the driver signalling its transmission complete. Now it can be
 * removed from the queue and deleted.\n
 *   The first phase allows queueing more pbufs as there is space in the ring buffer of the
 * ETH driver. This is advantageous as the queue elements in the pbuf queue are
 * significantly smaller than the ring buffer elements of the ETH driver. With same amount
 * of RAM, many more pbufs can be buffered. This is particularly useful if a frame in the
 * ETH driver is constituted from several if not many pbufs (see
 * #LWIP_NETIF_TX_SINGLE_PBUF), i.e., if every tcp_write() by the application code sends a
 * pbuf to the ETH driver. In this mode, which minimize data copy operations, the driver
 * will process many, little pbufs and this requires a significantly longer queue for the
 * same buffer capacity.
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
 *   nif_queueTxPBuf_initModule
 *   nif_queueTxPBuf_enqueue
 *   nif_queueTxPBuf_dequeue
 *   nif_queueTxPBuf_getPBufWaitingForSubmission
 *   nif_queueTxPBuf_getPBufWaitingForTransmissionComplete
 *   nif_queueTxPBuf_advancePBufWaitingForSubmission
 * Local functions
 *   inc
 *   diff
 *   isEmpty
 *   isFull
 *   hasPhase1
 *   hasPhase2
 *   noElems
 *   noElemsPhase1
 */

/*
 * Include files
 */

#include "nif_queueTxPBuf.h"

#include <assert.h>
#include <stdio.h>
#include "typ_types.h"


/*
 * Defines
 */
 
/** The maximum number of queueable Tx pbufs. */
#define CAPACITY_QUEUE_TX_PBUF  20u

/*
 * Local type definitions
 */
 
/** The type of the Tx pbuf queue. */
struct queueTxPBuf_t
{
    /** The data storage of the tx pbuf queue, which is implemented as an array. */
    struct nif_queueElemTxPBuf_t data[CAPACITY_QUEUE_TX_PBUF+1u];

    /** The index of the element to store the next pbuf. */
    unsigned int idxTail;
    
    /** The index of the element to remove from the queue at the end of the pbuf's life
        cycle. */
    unsigned int idxHead;
    
    /** The index of the eldest element, which is still in phase one, i.e., the index of
        the eldest queued pbuf, which has not been handed over to the ETH driver, yet. */
    unsigned int idxHeadPhaseOne;

#if NIF_SUPPORT_BUFFER_USAGE_STATISTICS == 1
    /* The number of pbufs, which are lost so far because of queue full events. */
    unsigned int noElemsLost;
    
    /** The maximum ever seen usage of the queue in number of stored elements. */
    unsigned int maxNoElems;
    
    /** The maximum ever seen number of stored elements, which were in phase one. */
    unsigned int maxNoElemsPhaseOne;
#endif
};
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
/** The Tx pbuf queue. */
struct queueTxPBuf_t BSS_P1(_q);

/*
 * Function implementation
 */

/** Cyclic increment of an index into the queue's array. */
static inline unsigned int inc(unsigned int idx)
{
    return idx < CAPACITY_QUEUE_TX_PBUF? idx+1u: 0u;
}

#if NIF_SUPPORT_BUFFER_USAGE_STATISTICS == 1
/** The cyclic difference of two indexes into the queue's array. */
static inline unsigned int diff(unsigned int idxA, unsigned int idxB)
{
    signed int d = (int)(idxA - idxB);
    if(d < 0)
        d += (int)CAPACITY_QUEUE_TX_PBUF + 1;
    const unsigned int du = (unsigned)d;
    assert(du <= CAPACITY_QUEUE_TX_PBUF);
    return du;
    
} /* diff */
#endif

/** Query: Is the queue currently empty? */
static inline bool isEmpty(void)
{
    return _q.idxTail == _q.idxHead;
}

/** Query: Is the queue currently full? */
static inline bool isFull(void)
{
    return inc(_q.idxTail) == _q.idxHead;
}

/** Query: Does the queue currently contain at least one pbuf in phase one? */
static inline bool hasPhase1(void)
{
    return _q.idxHeadPhaseOne != _q.idxTail;
}

/** Query: Does the queue currently contain at least one pbuf in phase two? */
static inline bool hasPhase2(void)
{
    return _q.idxHead != _q.idxHeadPhaseOne;
}

#if NIF_SUPPORT_BUFFER_USAGE_STATISTICS == 1
/** Query: How many pbufs does the queue currently contain? */
static inline unsigned int noElems(void)
{
    return diff(_q.idxTail, _q.idxHead);
}

/** Query: How many pbufs does the queue currently contain, which are in phase one? */
static inline unsigned int noElemsPhase1(void)
{
    return diff(_q.idxTail, _q.idxHeadPhaseOne);
}
#endif


/**
 * Initialize the module. An empty queue is created.
 */
void nif_queueTxPBuf_initModule(void)
{
    /* The pointers to the end of an area point one element behind it. (In a cyclic
       manner.) Two implications: Identical pointers mean an empty area and it is not
       possible to fill all array elements. */
    _q.idxTail            = 0u;
    _q.idxHead            = 0u;
    _q.idxHeadPhaseOne    = 0u;
#if NIF_SUPPORT_BUFFER_USAGE_STATISTICS == 1
    _q.noElemsLost        = 0u;
    _q.maxNoElems         = 0u;
    _q.maxNoElemsPhaseOne = 0u;
#endif
} /* nif_queueTxPBuf_initModule */



/**
 * A pbuf is put into the queue. This function is used, when lwIP calls the output function
 * for the pbuf. The pbuf is associated with the ENET device, it'll be transmitted on.
 *   @return
 * Queuing can fail due to a lack of memory space. (The queue as a fixed size.) Now, the
 * function returns ERR_MEM. Otherwise ERR_OK.
 *   @param idxEthDev
 * The ENET device by zero based index, which the pbuf should be transmitted with.
 *   @param pPBuf
 * The pbuf to send by reference. The function request (partial) ownership of the pbuf by
 * incrementing its reference counter. (The queue will decrement the reference counter and
 * potentially delete the pbuf on dequeuing.)
 */
err_t nif_queueTxPBuf_enqueue(unsigned int idxEthDev, struct pbuf * const pPBuf)
{
    if(!isFull())
    {
        struct nif_queueElemTxPBuf_t * const pElem = &_q.data[_q.idxTail];
        pElem->idxEthDev = idxEthDev;

        /* To ensure that the pbuf is existent during both phases we increment the
           reference counter. */
        pbuf_ref(pPBuf);
        pElem->pPBuf = pPBuf;
#ifdef DEBUG
        /* In DEBUG compilation we have a self-test, checking for consistent status, which
           requires hTxFrame to be zero for newly enqueued pbufs. */
        pElem->hTxFrame = 0u;
#endif
        _q.idxTail = inc(_q.idxTail);
        assert(hasPhase1());

#if NIF_SUPPORT_BUFFER_USAGE_STATISTICS == 1
        const unsigned int noPBufs = noElems()
                         , noPBufsPhase1 = noElemsPhase1();
        if(noPBufs > _q.maxNoElems)
            _q.maxNoElems = noPBufs;
        if(noPBufsPhase1 > _q.maxNoElemsPhaseOne)
            _q.maxNoElemsPhaseOne = noPBufsPhase1;
#endif
        return ERR_OK;
    }
    else
    {
#if NIF_SUPPORT_BUFFER_USAGE_STATISTICS == 1
        ++ _q.noElemsLost;
#endif
        return ERR_MEM;
    }
} /* nif_queueTxPBuf_enqueue */


/**
 * Query the queue for the eldest contained pbuf, which is still in phase one. This is the
 * very one, which needs to be handed over to the Ethernet driver as next.\n
 *   The function can be used, too, to query if the queue contains at least one pbuf in
 * phase one.
 *   @return
 * If a pbuf in phase one is contained then get the eldest of those by reference. The
 * reference grants write access; normal use case it using it to associate the pbuf with
 * the handle to the ring buffer element, which is applied by the Ethernet driver for
 * transmitting the pbuf.\n
 *   The function returns NULL if the queue doesn't contain any such pbuf.
 */
struct nif_queueElemTxPBuf_t * nif_queueTxPBuf_getPBufWaitingForSubmission(void)
{
    if(hasPhase1())
        return &_q.data[_q.idxHeadPhaseOne];
    else
        return NULL;
        
} /* nif_queueTxPBuf_getPBufWaitingForSubmission */


/**
 * Query the queue for the eldest pbuf, which is waiting for transmission complete. This is
 * the very one, which should be acknowledged by the Ethernet driver as next.\n
 *   The function can be used, too, to query if the queue contains at least one pbuf in
 * phase two.
 *   @return
 * If a pbuf in phase two is contained then get the eldest of those by reference. The
 * reference grants read access only.\n
 *   The function returns NULL if the queue doesn't contain any such pbuf.
 */
const struct nif_queueElemTxPBuf_t *
                            nif_queueTxPBuf_getPBufWaitingForTransmissionComplete(void)
{
    if(hasPhase2())
        return &_q.data[_q.idxHead];
    else
        return NULL;

} /* nif_queueTxPBuf_getPBufWaitingForTransmissionComplete */


/**
 * Signal for the eldest pbuf still in phase one that it has entered phase two.
 * This function is used, when a queued pbuf has been accepted by the ETH driver for
 * transmission.
 */
void nif_queueTxPBuf_advancePBufWaitingForSubmission(void)
{
    /* Only pbufs in phase one can be advanced (to phase two). */
    assert(hasPhase1());
    _q.idxHeadPhaseOne = inc(_q.idxHeadPhaseOne);
    assert(hasPhase2());

} /* nif_queueTxPBuf_advancePBufWaitingForSubmission */


/**
 * Pop the eldest pbuf from the queue and decrement its reference counter. (In most typical
 * situations, this will also delete the pbuf.) Use case is to call this function, when the
 * Ethernet driver has signalled completion of transmission for its next ring buffer
 * element.
 */
void nif_queueTxPBuf_dequeue(void)
{
    /* Only pbufs in phase two can be dequeued. */
    assert(hasPhase2());
    struct nif_queueElemTxPBuf_t * const pElem = &_q.data[_q.idxHead];
    
    /* The next pbuf in the chain has been entirely processed by the ETH driver and
       we can free the source memory, i.e., the pbuf... */
    pbuf_free(pElem->pPBuf);
    
    _q.idxHead = inc(_q.idxHead);

} /* nif_queueTxPBuf_dequeue */

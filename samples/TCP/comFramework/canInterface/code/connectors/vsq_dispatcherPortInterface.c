/**
 * @file vsq_dispatcherPortInterface.c
 * This module supports the use of the thread-safe queue as connection element between
 * sender and dispatcher in the event dispatcher mechanism. The event dispatcher mechanism
 * specifies the interfaces of the ports of sender and dispatcher and this module provides
 * the queue API in the form of instances of those ports.\n
 *   This module does not belong to the generic queue implementation and won't be usable
 * outside the context of the event dispatcher mechanism.
 *
 * Copyright (C) 2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   vsq_createEventQueueHead
 *   vsq_createEventQueueTail
 *   vsq_linkEventQueueTailWithHead
 *   vsq_linkEventQueueHeadWithTail
 *   vsq_createEventQueue
 * Local functions
 *   edePortSdr_allocBuffer
 *   edePortSdr_submitBuffer
 *   edePortDisp_readBuffer
 *   edePortDisp_freeBuffer
 */

/*
 * Include files
 */

#include "vsq_dispatcherPortInterface.h"

#include <assert.h>

#include "ede_basicDefinitions.h"
#include "vsq_threadSafeQueueVariableSize.h"

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

/**
 * Implementation of sender port interface: Allocate buffer space for the event to post.
 * The process of sending an event means to first allocate a buffer, then fill it and
 * finally submit it. Sending several events leads to an alternating use of this method and
 * submitBuffer(). The implementation doesn't support more complex use cases, in
 * particular, it doesn't implement the allocation of several buffers before submission of
 * the first one. It assumes strictly alternating use of both methods.
 *   @return
 * The returned pointer points to some memory space, capable of holding an event with
 * \a sizeOfPayload Byte of payload, i.e. at least (sizeof(ede_externalEvent_t) + \a
 * sizeOfPayload) Byte of space.\n
 *   @param hInstance
 * This handle is the identification of the port instance to use.
 *   @param sizeOfPayload
 * The minimum capacity in Byte of the payload area, field \a dataAry[], the returned
 * event needs to have.
 */
static ede_externalEvent_t *edePortSdr_allocBuffer( uintptr_t hInstance
                                                  , unsigned int sizeOfPayload
                                                  )
{
    vsq_queueTail_t * const pQueueTail = (vsq_queueTail_t*)hInstance;
    return vsq_allocTailElement(pQueueTail, sizeof(ede_externalEvent_t) + sizeOfPayload);
}



/**
 * Implementation of sender port interface: Submit the eldest buffer, which had been
 * reserved with edePortSdr_allocBuffer() and for same port instance and which had not been
 * submitted yet.
 *   @param hInstance
 * This handle is the identification of the port instance to use.
 */
static void edePortSdr_submitBuffer(uintptr_t hInstance)
{
    vsq_queueTail_t * const pQueueTail = (vsq_queueTail_t*)hInstance;
    vsq_postTailElement(pQueueTail);
}


/**
 * Implementation of dispatcher port interface: Try to read an event from the port, i.e.,
 * from the thread-safe queue that feeds the port.
 *   @return
 * The function returns a pointer to the head element in the queue, i.e., to the eldest
 * previously sent and not yet fetched event.\n
 *   The data, the returned pointer points to shall is valid for reading until the other
 * method edePortDisp_freeBuffer() is invoked for the same port instance. The implementation
 * assumes, that edePortDisp_readBuffer and edePortDisp_freeBuffer() are called strictly
 * alternatingly.\n
 *   The method returns NULL if the queue is currently empty, i.e., if there's no event to
 * deliver. In this case freeBuffer() must not be used later.
 *   @param hInstance
 * This handle is the identification of the port instance to use.
 *   @param pSizeOfPayload
 * The method will put the size of the payload of the returned event into * \a
 * pSizeOfPayload. The size is the number of bytes, which can be accessed through the
 * event's field \a dataAry[].
 */
static const ede_externalEvent_t * edePortDisp_readBuffer( uintptr_t hInstance
                                                         , unsigned int *pSizeOfPayload
                                                         )
{
    vsq_queueHead_t * const pQueueHead = (vsq_queueHead_t*)hInstance;
    unsigned int sizeOfElem;
    const ede_externalEvent_t * const pEvent = vsq_readFromHead(pQueueHead, &sizeOfElem);
    if(pEvent != NULL)
    {
        EDE_ASSERT(sizeOfElem >= sizeof(ede_externalEvent_t));
        *pSizeOfPayload = sizeOfElem - sizeof(ede_externalEvent_t);
    }

    return pEvent;

} /* edePortDisp_readBuffer */



/**
 * Implementation of sender port interface: Return the eldest buffer, which had been
 * fetched with edePortDisp_readBuffer() and for the same port instance, and which had not
 * been returned yet.
 *   @param hInstance
 * Each receiver port has its own, dedicated connection element instance. This handle is
 * the identification of the port instance to use.
 */
static void edePortDisp_freeBuffer(uintptr_t hInstance EDE_UNUSED)
{
    /* This operation is not applicable for the thread-safe queue. The buffer remains
       allocated until the next element is read from the queue. */
}


/**
 * Create the head object of a thread-safe queue with variable element size for external
 * dispatcher events and return it as a port, which provide access to the head of the
 * queue. The port is compliant with the port interface of the dispatcher from the event
 * dipatcher mechanism.
 *   @return
 * The function returns \a true in case of success, \a false otherwise.
 *   @param pPortHead
 * If the function returns \a true, then a port object, which provides access to the head
 * of the queue for fetching queued elements, has been placed into * \a pPortHead.
 *   @param pMemPoolHead
 * All elements of the queue are allocated in a memory pool. This is the pool (by
 * reference), which is used for those elements, which are required for accessing the head
 * of the queue, i.e., for fetching queued elements.\n
 *   Note, the shared-memory concept of the queue implementation requires that the
 * execution context (ISR, task, process), which makes use of the queue tail to queue
 * elements, needs to have at least read access to the memory from this pool, too.
 *   @remark
 * If memory access restrictions don't play a role, then function vsq_createEventQueue()
 * will be the better alternative, it creates the complete quene, including both ports -
 * all in one call.
 */
bool vsq_createEventQueueHead( ede_eventReceiverPort_t *pPortHead
                             , ede_memoryPool_t * const pMemPoolHead
                             )
{
    /* The queue implementation module doesn't do any memory allocation. We need to
       first reserve a chunk of required size and then let the constructor fill it. */
    const unsigned int sizeOfEvQueueHead = vsq_getSizeOfQueueHead();
    if(sizeOfEvQueueHead == 0u)
        return false;

    void * const pMemChunkHead = pMemPoolHead->malloc( pMemPoolHead->hInstance
                                                     , sizeOfEvQueueHead
                                                     );
    if(pMemChunkHead == NULL)
        return false;

    /* Create a new queue head object. */
    vsq_queueHead_t * const pQHead = vsq_createQueueHead(pMemChunkHead);

    /* Create a port object for the queue's head. */
    pPortHead->providesDataByReference = false;
    pPortHead->readBuffer              = edePortDisp_readBuffer;
    pPortHead->freeBuffer              = edePortDisp_freeBuffer;
    pPortHead->hInstance               = (uintptr_t)pQHead;

    return true;

} /* vsq_createEventQueueHead */



/**
 * Create a thread-safe queue with variable element size for external dispatcher events and
 * return it as a port, which provides access to the tail of the queue. The port is
 * compliant with the port interfaces of the sender from the event dipatcher mechanism.
 *   @return
 * The function returns \a true in case of success, \a false otherwise.
 *   @param pPortTail
 * If the function returns \a true, then a port object, which provides access to the tail
 * of the queue for adding elements, has been placed into * \a pPortTail.
 *   @param maxQueueLength
 * The queue implementation imposes a fixed maximum size of the queue. The size is
 * specified in terms of how many events with a payload of \a sizeOfPayload would fit into
 * the queue. At run-time, stored elements can have arbitrary sizes so that no statement is
 * possible about the actually storable number.\n
 *   A queue length of zero is considered an error in the client code. This is caught by
 * assertion and \a false is returned.
 *   @param maxPayloadSize
 * The size of the payload of a queued standard event, which should be storable \a
 * maxQueueLength times in the queue. This size is just used for specification of the
 * queue's capacity but has no meaning at run-time any more.
 *   @param pMemPoolTail
 * All elements of the queue are allocated in a memory pool. This is the pool (by
 * reference), which is used for those elements, which are required for accessing the tail
 * of the queue, i.e., for queueing elements.\n
 *   Note, the shared-memory concept of the queue implementation requires that the
 * execution context (ISR, task, process), which makes use of the queue head to fetch
 * queued elements, needs to have at least read access to the memory from this pool, too.
 *   @remark
 * If memory access restrictions don't play a role, then function vsq_createEventQueue()
 * will be the better alternative, it creates the complete quene, including both ports -
 * all in one call.
 */
bool vsq_createEventQueueTail( ede_eventSenderPort_t *pPortTail
                             , unsigned int maxQueueLength
                             , unsigned int maxPayloadSize
                             , ede_memoryPool_t * const pMemPoolTail
                             )
{
    const unsigned int maxEventObjSize = sizeof(ede_externalEvent_t) + maxPayloadSize;

    /* The queue implementation module doesn't do any memory allocation. We need to
       first reserve a chunk of required size and then let the constructor fill it. */
    const unsigned int sizeOfEvQueueTail = vsq_getSizeOfQueueTail
                                                ( /* maxNoStdElements */ maxQueueLength
                                                , /* sizeOfStdElement */ maxEventObjSize
                                                );
    if(sizeOfEvQueueTail == 0u)
        return false;

    void * const pMemChunkTail = pMemPoolTail->malloc( pMemPoolTail->hInstance
                                                     , sizeOfEvQueueTail
                                                     );
    if(pMemChunkTail == NULL)
        return false;

    /* Create a new queue tail object. */
    vsq_queueTail_t * const pQTail = vsq_createQueueTail
                                          ( pMemChunkTail
                                          , /* maxNoStdElements */ maxQueueLength
                                          , /* sizeOfStdElement */ maxEventObjSize
                                          );

    /* Create a port objects for the queue's tail. */
    pPortTail->allocBuffer             = edePortSdr_allocBuffer;
    pPortTail->submitBuffer            = edePortSdr_submitBuffer;
    pPortTail->hInstance               = (uintptr_t)pQTail;
    pPortTail->requiresDataByReference = false;

    return true;

} /* vsq_createEventQueueTail */


/**
 * A new event queue's tail and head objects are created independently. Because of the
 * separation of memories of producer and consumer of the queued data, this will typically
 * be done independently and by distinct processes and the two objects don't know yet about
 * one another. They can cooperate only after being mutually linked with one another. The
 * linkage is done in two steps and after creation of both queue ends: This API allows to
 * update the link in the head object and can thus be used by the same process that created
 * the head object and the counterpart vsq_linkQueueTailWithHead() will do the same for the
 * tail object and from another process.\n
 *   Note, this function is just the same as vsq_linkQueueHeadWithTail() but for port
 * objects as used in the dispatcher engine.
 *   @param portHead
 * The newly created queue head port object, which is now linked to its tail.
 *   @param portTail
 * This is the tail port object, * \a portHead is going to cooperate with.
 *   @remark
 * If memory access restrictions don't play a role, then function vsq_createEventQueue()
 * will be the better alternative, it creates both ports, head and tail, and links them - all
 * in one call.
 */
void vsq_linkEventQueueHeadWithTail( const ede_eventReceiverPort_t portHead
                                   , const ede_eventSenderPort_t portTail
                                   )
{
    vsq_queueHead_t * const pQHead = (vsq_queueHead_t*)portHead.hInstance;
    vsq_queueTail_t * const pQTail = (vsq_queueTail_t*)portTail.hInstance;
    vsq_linkQueueHeadWithTail(pQHead, pQTail);

} /* vsq_linkEventQueueHeadWithTail */



/**
 * A new event queue's head and tail objects are created independently. Because of the
 * separation of memories of producer and consumer of the queued data, this will typically
 * be done independently and by distinct processes and the two objects don't know yet about
 * one another. They can cooperate only after being mutually linked with one another. The
 * linkage is done in two steps and after creation of both queue ends: This API allows to
 * update the link in the tail object and can thus be used by the same process that created
 * the tail object and the counterpart vsq_linkQueueHeadWithTail() will do the same for the
 * head object and from another process.\n
 *   Note, this function is just the same as vsq_linkQueueTailWithHead() but for port
 * objects as used in the dispatcher engine.
 *   @param portTail
 * The newly created queue tail port object, which is now linked to its head.
 *   @param portHead
 * This is the head port object, * \a portTail is going to cooperate with.
 *   @remark
 * If memory access restrictions don't play a role, then function vsq_createEventQueue()
 * will be the better alternative, it creates both ports, head and tail, and links them - all
 * in one call.
 */
void vsq_linkEventQueueTailWithHead( const ede_eventSenderPort_t portTail
                                   , const ede_eventReceiverPort_t portHead
                                   )
{
    vsq_queueHead_t * const pQHead = (vsq_queueHead_t*)portHead.hInstance;
    vsq_queueTail_t * const pQTail = (vsq_queueTail_t*)portTail.hInstance;
    vsq_linkQueueTailWithHead(pQTail, pQHead);

} /* vsq_linkEventQueueTailWithHead */


/**
 * Create a thread-safe queue with variable element size for external dispatcher events and
 * return it as pair of ports, which provide access to head and tail of the queue. The
 * ports are compliant with the port interfaces of sender and dispatcher from the event
 * dipatcher mechanism.
 *   @return
 * The function returns \a true in case of success, \a false otherwise.
 *   @param pPortHead
 * If the function returns \a true, then a port object, which provides access to the head
 * of the queue for fetching queued elements, has been placed into * \a pPortHead.
 *   @param pPortTail
 * If the function returns \a true, then a port object, which provides access to the tail
 * of the queue for adding elements, has been placed into * \a pPortTail.
 *   @param maxQueueLength
 * The queue implementation imposes a fixed maximum size of the queue. The size is
 * specified in terms of how many events with a payload of \a sizeOfPayload would fit into
 * the queue. At run-time, stored elements can have arbitrary sizes so that no statement is
 * possible about the actually storable number.\n
 *   A queue length of zero is considered an error in the client code. This is caught by
 * assertion and \a false is returned.
 *   @param maxPayloadSize
 * The size of the payload of a queued standard event, which should be storable \a
 * maxQueueLength times in the queue. This size is just used for specification of the
 * queue's capacity but has no meaning at run-time any more.
 *   @param pMemPoolHead
 * All elements of the queue are allocated in a memory pool. This is the pool (by
 * reference), which is used for those elements, which are required for accessing the head
 * of the queue, i.e., for fetching queued elements.\n
 *   Note, the shared-memory concept of the queue implementation requires that the
 * execution context (ISR, task, process), which makes use of the queue tail to queue
 * elements, needs to have at least read access to the memory from this pool.
 *   @param pMemPoolTail
 * All elements of the queue are allocated in a memory pool. This is the pool (by
 * reference), which is used for those elements, which are required for accessing the tail
 * of the queue, i.e., for queueing elements.\n
 *   Note, the shared-memory concept of the queue implementation requires that the
 * execution context (ISR, task, process), which makes use of the queue head to fetch
 * queued elements, needs to have at least read access to the memory from this pool.
 *   @warning
 * The creation of a complete, ready-to-use queue object requires initialization of both,
 * head and tail object. Therefore, the caller of this routine needs to have write access
 * to the memory from both memory pools. In memory protected environments, this will
 * normally be only a supervisor context!
 */
bool vsq_createEventQueue( ede_eventReceiverPort_t *pPortHead
                         , ede_eventSenderPort_t *pPortTail
                         , unsigned int maxQueueLength
                         , unsigned int maxPayloadSize
                         , ede_memoryPool_t * const pMemPoolHead
                         , ede_memoryPool_t * const pMemPoolTail
                         )
{
    if(!vsq_createEventQueueHead(pPortHead, pMemPoolHead)
       || !vsq_createEventQueueTail(pPortTail, maxQueueLength, maxPayloadSize, pMemPoolTail)
      )
    {
        return false;
    }

    /* Mutually link head and tail object in order to get a queue. */
    vsq_linkEventQueueHeadWithTail(*pPortHead, *pPortTail);
    vsq_linkEventQueueTailWithHead(*pPortTail, *pPortHead);

    return true;

} /* vsq_createEventQueue */



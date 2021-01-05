/**
 * @file tsq_threadSafeQueue.c
 * Thread-safe implementation of a queue. Filling and reading the queue may be done from
 * different threads. It doesn't matter whether these threads have same or different
 * priorities and whether they are running on the same or on different cores. The
 * implementation is lock-free.
 *
 * Copyright (C) 2016 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   tsq_getSizeOfQueue
 *   tsq_createQueue
 *   tsq_getMaxSizeOfElement
 *   tsq_writeToTail
 *   tsq_allocTailElement
 *   tsq_postTailElement
 *   tsq_readFromHead
 *   tsq_getNoQueuedElements
 *   tsq_getMaximumQueueUsage
 * Local functions
 *   allocTailElement
 *   postTailElement
 *   byteOffsetOfRingBuffer
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#if defined(__STDC_VERSION__) &&  (__STDC_VERSION__)/100 >= 2011
# include <stdatomic.h>
#endif

#include "tsq_threadSafeQueue.h"


/*
 * Defines
 */


/** The thread-safe implementation of the dispatcher queue builds on defined memory
    ordering; machine operations are expected to happen in the order of C code statements.
    This is not easy to achieve in C as the language semantics doesn't have awareness of
    concurrency (before C11). The solution will always be target and compiler dependent.
    Here, we offer a macro, which is meant to implement a full memory barrier on the
    target.\n
      Fortunately, when using GCC there is a platform independent solution. See
    http://gcc.gnu.org/onlinedocs/gcc-4.4.3/gcc/Atomic-Builtins.html for details. */
#define MEMORY_BARRIER_FULL() CDE_MEMORY_BARRIER_FULL()


/*
 * Local type definitions
 */


/** The thread-safe implementation of the queue builds on atomic read and write
    of a numeric type. Basically any atomic unsigned integer available on the target
    platform can be typedef'ed here; however, the maximum length of the queue is given by
    the range of this type - thus don't use a too short integer type if you have the
    choice. unsigned int will be appropriate on most 32 and 16 Bit platforms and unsigned
    char on a typical 8 Bit platform.\n
      Negligible problems arise on platforms like AVR, where the atomic integer type is
    shorter than unsigned int. Due to the typedef made here, two integer types are mixed in
    the implementation without making this transparent by explicit type casts. The implicit
    type casts still ensure code correctness with one documented exception: the optional
    diagnostic API functions are now restricted to be used solely in the producer context.
    However, these functions are not essential and will be switched off in most
    integrations. We decided to not clean this up by using typedef'ed integers throughout
    the complete implementation -- this would degrade the readability and maintainability
    of the code and such systems are anyway not the targeted platforms. */
typedef cde_atomicUnsignedInt_t atomicUnsignedInt_t;


/** The queue. A ring buffer implementation has been chosen. */
struct tsq_queue_t
{
    /** The ring buffer elements of the queue.\n
          This member is written by producer and consumer but both will never touch it at
        the array entry at a time. This mutual exclusion is controlled by the other members
        \a idxRead and \a idxWrite. */
    void *ringBuffer;

    /** The number of elements in the ring buffer.\n
          This member is constant and read-only (after initialization) and out of scope of
        race conditions between producer and consumer. */
    unsigned int lengthOfRingBuffer;

    /** The number of currently free elements in the ring buffer.\n
          This member is updated and read solely by the producer. There are no race
        conditions. */
    unsigned int noFreeElements;

#ifdef TSQ_ENABLE_API_QUEUE_DIAGNOSTICS
    /** The maximum number of elements, which has been queued so far. This number can be
        used at application validation time for optimization of the required queue size.\n
          This member updated only by the producer code and is not subject to race
        conditions. */
    unsigned int maxUsage;
#endif

    /** The maximum number of data bytes in the ring buffer elements.\n
          This member is constant and read-only (after initialization) and out of scope of
        race conditions between producer and consumer. */
    unsigned int maxElementSize;

    /** The position of the current head of the list of data elements currently in the ring
        buffer. The name of this member results for the idea of using the ring buffer to
        implement a queue; new elements are appended to the tail of the queue and elder,
        consumed ones are removed from the (stale) head.\n
          This member is read and updated solely by the producer. There are no race
        conditions with the consumer code. */
    unsigned int idxHead;

    /** The read position into the ring buffer of the queue. The element this index refers
        to is owned by the consumer for race condition free data processing.\n
          This member is read-only to the data provider and updated by the consumer. It is
        important that this member can be read or written in a single atomic operation;
        this explains the type, which has to be configured platform dependent. */
    volatile atomicUnsignedInt_t idxRead;

    /** The position of the current tail of the list of data elements currently in the ring
        buffer. The name of this member results for the idea of using the ring buffer to
        implement a queue; new elements are appended to the tail of the queue and elder,
        consumed ones are removed from the (stale) head.\n
          This member is read-only to the data consumer and updated by the producer. It is
        essential that this member can be read or written in a single atomic operation;
        this explains the type, which has to be configured platform dependent. */
    volatile atomicUnsignedInt_t idxTail;
};



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
 * Check if the queue has currently room to append another element to the tail. Return the
 * available element in case.
 *   @return
 * Get either the next available ring buffer element by reference or NULL if the queue is
 * currently full.
 *   @param pQueue
 * The queue object by reference.
 *   @param pNewIdxTail
 * Part of processing is the computation of the index of the element in the linear array,
 * which implements the ring buffer. This index is returned by reference.
 *   @remark
 * The function is an inline implementation of the common part of both APIs to the tail of
 * the queue.
 */

static inline void *allocTailElement(tsq_queue_t *pQueue, unsigned int *pNewIdxTail)
{
    /* Free the elements of the ring buffer, which hold already read queue elements. */
    const unsigned int idxRead = pQueue->idxRead;
    while(pQueue->idxHead != idxRead)
    {
        ++ pQueue->noFreeElements;
        if(++pQueue->idxHead >= pQueue->lengthOfRingBuffer)
            pQueue->idxHead = 0;
        TSQ_ASSERT(pQueue->noFreeElements < pQueue->lengthOfRingBuffer);
    }

    if(pQueue->noFreeElements > 0)
    {
        unsigned int newIdxTail = pQueue->idxTail+1;
        if(newIdxTail >= pQueue->lengthOfRingBuffer)
            newIdxTail = 0;

        *pNewIdxTail = newIdxTail;
        return (void*)((char*)pQueue->ringBuffer + newIdxTail*pQueue->maxElementSize);
    }
    else
        return NULL;

} /* End of allocTailElement */


/**
 * Counterpart to void *allocTailElement(tsq_queue_t *, unsigned int *): Append the
 * previously allocated element to the queue, i.e. notify a consumer the availability of
 * this element. The ownership of the reserved element, which was gained with
 * allocTailElement(), ends with entry into this method; the producer must not touch the
 * element any more.
 *   @param pQueue
 * The queue object by reference.
 *   @param newIdxTail
 * The index of the element in the linear array, which implements the ring buffer. This
 * index is entirely meaningless to the caller but had been returned by the preceding,
 * corresponding call of \a allocTailElement. The producer code is responsible of storing
 * and returning this value.
 *   @remark
 * The function is an inline implementation of the common part of both APIs to the tail of
 * the queue.
 */

static inline void postTailElement(tsq_queue_t *pQueue, unsigned int newIdxTail)
{
    /* We put a full memory barrier between filling the new element and notifying its
       availablity to the consumer. All operations for element filling will be
       completed before the index change of the tail gets visible to the consumer. */
    MEMORY_BARRIER_FULL();

    /* Notify the new element by updating the shared tail index in an atomic write. */
    TSQ_ASSERT(newIdxTail != pQueue->idxHead);
    pQueue->idxTail = newIdxTail;

    /* Update the count of the free elements. */
    -- pQueue->noFreeElements;
    TSQ_ASSERT(pQueue->noFreeElements < pQueue->lengthOfRingBuffer);

#ifdef TSQ_ENABLE_API_QUEUE_DIAGNOSTICS
    const unsigned int noQueuedElems = pQueue->lengthOfRingBuffer - 1
                                       - pQueue->noFreeElements;
    if(noQueuedElems > pQueue->maxUsage)
        pQueue->maxUsage = noQueuedElems;
#endif

} /* End of postTailElement */




/**
 * We are creating an array of elements. The array as a whole must be correct aligned (using
 * method byteOffsetOfRingBuffer()) but the element size must be a multiple of the element
 * alignment, too - otherwise would latest the second element in the array be misaligned.
 * This method computes the element size to be reserved in the array based on the user
 * demanded element size.
 *   @return
 * Get the number of Bytes, which need to be reserved for each element in the ring buffer
 * array that implements the queue.
 *   @param sizeOfElement
 * The suer specified size of an element in the queue.
 *   @param alignOfElement
 * The alignment required for an element in the queue.
 */

static inline unsigned int alignedSizeOfElement( unsigned int sizeOfElement
                                               , unsigned int alignOfElement
                                               )
{
    return ((sizeOfElement + alignOfElement-1) / alignOfElement) * alignOfElement;
    
} /* End of alignedSizeOfElement */




/**
 * Compute the byte offset of the memory for the ringbuffer if putting both, the object and
 * the ringbuffer into a single memory chunk. The two elements can't simply be concatenated,
 * we need to consider a gap to fulfill all alignment requirements.\n
 *   @return
 * \a true, if function succeeded, else \a false.
 *   @param alignOfElement
 * The alignment required for an element in the queue.
 *   @remark
 * This simple function holds the common code of object creation and object size query.
 */

static inline unsigned int byteOffsetOfRingBuffer(unsigned int alignOfElement)
{
    /* Consider the maybe different alignment of the queue element when computing the
       beginning of the ring buffer memory inside the chunk. */
    return alignedSizeOfElement(sizeof(tsq_queue_t), alignOfElement);

} /* End of byteOffsetOfRingBuffer */



/**
 * Query the size of a queue object.\n
 *   This function is meant to be called prior to creation of a queue object. The caller of
 * the constructor is in charge of allocating the memory for the object - the intended use
 * case of the queue implementation is the embedded environment, which doesn't permit to
 * allocate memory dynamically using \a malloc.\n
 *   This function needs to be called with the same parameters as later the constructor. The
 * constructor will silently assume that the memory chunk it receives from the caller will
 * have the size computed by this method. The typical use case avoids the use of \a malloc:
 * @code
 *  struct qElement_t;
 *  #define MAX_Q_LEN 10
 *  const unsigned int sizeOfQ = tsq_getSizeOfQueue( MAX_Q_LEN
 *                                                 , sizeof(struct qElement_t)
 *                                                 , _Alignof(struct qElement_t)
 *                                                 );
 *  // In this example be _Alignof(struct qElement_t) <= _Alignof(unsigned int)
 *  TSQ_ASSERT(_Alignof(struct qElement_t) <= _Alignof(unsigned int));
 *  _Alignas(unsigned int) char memoryChunk[sizeOfQ];
 *  tsq_queue_t myNewQ = tsq_createQueue( memoryChunk
 *                                      , MAX_Q_LEN
 *                                      , sizeof(struct qElement_t)
 *                                      , _Alignof(struct qElement_t)
 *                                      );
 * @endcode
 *   Alternatively, the embedded environment may offer a simple, uncritical memory
 * allocation or partitioning API, most likely without a free function to avoid
 * fragmentation and indeterministic timing behavior.
 *   @return
 * The number of bytes required to construct a queue object with the passed parameters.
 * Only this number is computed, nothing else happens, in particular no queue object is
 * constructed.
 *   @param maxQueueLength
 * The queue implementation imposes a fixed maximum size of the queue. Any attempt to queue
 * more than this number of elements (and without reading any meanwhile) will return an
 * error at run-time.
 *   @param maxElementSize
 * The maximum size of each element to be stored in the queue. In most situations the queue
 * will hold elements of same size, then this size is meant. However, the write API
 * permits to write a variable number of bytes into the queue, too. If variably sized
 * elements are used then the maximum size needs to be specified here.\n
 *   Note, variable size handling doesn't target saving of memory but saving of data
 * copying effort. The constructor will allocate the maximum element size for all possible
 * queue elements.
 *   @param alignOfElement
 * The function operates without type information but needs to form an array of the
 * elements. To safely do so it needs to anticipate the alignment required for such an
 * element.\n
 *   Usually this is the alignment of the element if it has a primitive type or the
 * alignment of the largest field of the element if it is a struct.\n
 *   If the caller's code is compiled as C11 then the best way to do is passing
 * _Alignof(<elementType>).\n
 *   \a alignOfElement is expected to be a power of two.
 *   @remark
 * The memory chunk required by the constructor does not only need to have the right
 * minimum size but, secondary, it needs to have the right alignment, which is the greater
 * one of the alignment of an unsigned int and \a alignOfElement.
 *   @see tsq_createQueue()
 */

unsigned int tsq_getSizeOfQueue( unsigned int maxQueueLength
                               , unsigned int maxElementSize
                               , unsigned int alignOfElement
                               )
{
    /* A valid alignment is a power of two. */
    TSQ_ASSERT((alignOfElement | (alignOfElement-1))+1 == 2*alignOfElement);

    /* (maxQueueLength+1): One element of the ring buffer is owned by the consumer for
       reading and not available to the queue. We need to allocate one element more than
       the demanded maximum length of the queue.
         Alignment requirement on memory chunk at creation time: The consideration of the
       alignment of the ring buffer elements as it is implemented here requires that the
       memory chunk already has the worst case alignment (the worse of queue struct and
       queue element). Alternatively, we could decide to anticipate additional memory for
       an adjustment of an arbitrary memory chunk address; there is a trade off between a
       waste of memory and the convenience of avoiding the alignment requirement. */
    return byteOffsetOfRingBuffer(alignOfElement)
           + (maxQueueLength+1) * alignedSizeOfElement(maxElementSize, alignOfElement);

} /* End of tsq_getSizeOfQueue */




/**
 * Create a new queue object.
 *   @return
 * Get the pointer to the ready-to-use queue object. Effectively, this is the same pointer
 * as \a pMemoryChunk but type casted for use as queue. If the caller uses dynamic memory
 * management then he may free either his memory chunk or the returned pointer after use of
 * the queue.
 *   @param pMemoryChunk
 * The caller is in charge of allocating memory for the new queue object. A memory chunk of
 * required size or bigger is passed in by reference. The required size needs to queried
 * with the other method tsq_getSizeOfQueue() prior to the call of this constructor.\n
 *    Besides the right size, the memory chunk needs to have the right alignment, which is
 * the greater one of the alignment of an unsigned int and \a alignOfElement. If you use
 * \a malloc to allocate the memory chunk than this should always be granted.
 *   @param maxQueueLength
 * The queue implementation imposes a fixed maximum size of the queue. Any attempt to queue
 * more than this number of elements (and without reading any meanwhile) will return an
 * error at run-time.
 *   @param maxElementSize
 * The maximum size of each element to be stored in the queue. In most situations the queue
 * will hold elements of same size, then this size is meant. However, the write API
 * permits to write a variable number of bytes into the queue, too. If variably sized
 * elements are used then the maximum size needs to be specified here.\n
 *   Note, variable size handling doesn't target saving of memory but saving of data
 * copying effort. The constructor will allocate the maximum element size for all possible
 * queue elements.
 *   @param alignOfElement
 * The function operates without type information but needs to form an array of the
 * elements. To safely do so it needs to anticipate the alignment required for such an
 * element.\n
 *   Usually this is the alignment of the element if it has a primitive type or the
 * alignment of the largest field of the element if it is a struct.\n
 *   If the caller's code is compiled as C11 then the best way to do is passing
 * _Alignof(<elementType>).
 *   @remark
 * There's no destructor for a queue object. The caller is responsible for providing the
 * memory for the object and freeing this memory -- if applicable -- would be the only
 * operation to delete a queue object after use.
 *   @see tsq_getSizeOfQueue()
 */

struct tsq_queue_t *tsq_createQueue( void *pMemoryChunk
                                   , unsigned int maxQueueLength
                                   , unsigned int maxElementSize
                                   , unsigned int alignOfElement
                                   )
{
    /* A valid alignment is a power of two. */
    TSQ_ASSERT((alignOfElement | (alignOfElement-1))+1 == 2*alignOfElement);

    tsq_queue_t * const pQueue = (tsq_queue_t*)pMemoryChunk;

    /* Check the alignment of the memory chunk for the queue object. */
    #ifdef _STDC_VERSION_C11
    # define ALIGN_OF_QUEUE_T _Alignof(tsq_queue_t)
    #elif defined(__GNUC__) && defined(__WIN64__)
    # define ALIGN_OF_QUEUE_T 8
    #elif defined(__GNUC__) && defined(__WIN32__)
    # define ALIGN_OF_QUEUE_T 4
    #elif defined(__AVR__)
    # define ALIGN_OF_QUEUE_T 1
    #else
    # error Define the alignment of struct queue_t for your compiler/target
    #endif
    TSQ_ASSERT(((uintptr_t)pQueue & (ALIGN_OF_QUEUE_T-1)) == 0);
    #undef ALIGN_OF_QUEUE_T

    pQueue->lengthOfRingBuffer = maxQueueLength + 1;
    pQueue->ringBuffer = (void*)((char*)pMemoryChunk + byteOffsetOfRingBuffer(alignOfElement));
    TSQ_ASSERT(((uintptr_t)pQueue->ringBuffer & (alignOfElement-1)) == 0);

    /* The number of initially free queue elements in the ring buffer is one less than the
       buffer's size. */
    pQueue->noFreeElements = maxQueueLength;
#ifdef TSQ_ENABLE_API_QUEUE_DIAGNOSTICS
    pQueue->maxUsage = 0;
#endif

    /* The maximum number of data bytes in each of the ring buffer elements is required
       by the later write or post operation. We need to store the uprounded value
       (uprounded due to alignment constraints) because the value is also used for later
       address offset computation from one queue element to the next one. */
    pQueue->maxElementSize = alignedSizeOfElement(maxElementSize, alignOfElement);

    /* The head and tail of the queue and the read position into it all point initially to
       the same element. Which one doesn't matter. */
    pQueue->idxHead = 0;
    pQueue->idxRead = 0;
    pQueue->idxTail = 0;

    return pQueue;

} /* End of tsq_createQueue */




/**
 * Query the maximum permitted size of a queueable element.\n
 *   Please note, the returned value can differ from the element size, which had been
 * demanded as parameter \a maxElementSize in the call of tsq_createQueue(). Due to
 * alignment constraints the value returned by this method can be greater or equal to the
 * value stated at queue creation time.
 *   @return
 * Get the number of bytes, which can be queued at once using either tsq_writeToTail() or
 * which can be written to the memory chunk returned by tsq_allocTailElement().
 *   @param pQueue
 * The query relates to any object processed by this queue.
 */

unsigned int tsq_getMaxSizeOfElement(tsq_queue_t *pQueue)
{
    return pQueue->maxElementSize;
    
} /* End of tsq_getMaxSizeOfElement */




/**
 * Append a new element to the tail of the queue.
 *   @return
 * The operation can fail; the queue is implemented with a pre-determined maximum size and
 * it can be currently full. Get \a true if the operation succeeds and \a false in case of
 * a currently full queue.
 *   The elements themselves have a fixed maximum size. If the caller tries to write more
 * bytes than this maximum the function will also return \a false.
 *   @param pQueue
 * The queue object to write to by reference.
 *   @param pData
 * The pointer to the payload data of the appended element. This is an anonymous byte
 * sequence to this method. memcpy is used to copy the data into the queue, which imposes
 * no alignment requirements on the data.
 *   @param noBytes
 * The number of bytes to write. If variable data sizes don't matter then you will pass the
 * same value as specified as \a maxElementSize at queue creation time.\n
 *   Note, the queue implementation doesn't record how many bytes are written into the
 * appended elements. Most applications will anyway use a fixed size. If an application
 * makes use of variable element sizes it should define the element such that the size
 * information is part of this element.\n
 *   Note, it's impossible to save memory by variable element sizes. The memory allocation
 * at queue creation time will always assume the maximum size for each element.\n
 *   If the number of bytes to write exceeds the fixed maximum size than the operation is
 * rejected. No data will be copied to the queue.
 *   @see void *tsq_allocTailElement(tsq_queue_t *)
 *   @see void *tsq_readFromHead(tsq_queue_t *)
 */

bool tsq_writeToTail(tsq_queue_t *pQueue, const void *pData, unsigned int noBytes)
{
    /* No action (no partial data copying) if the written junk doesn't fit. */
    if(noBytes > pQueue->maxElementSize)
        return false;

    unsigned int newIdxTail;
    void *pFreeElem = allocTailElement(pQueue, &newIdxTail);

    if(pFreeElem != NULL)
    {
        memcpy(pFreeElem, pData, noBytes);

        /* Notify the new element to the consumer and update the statistics of free
           elements. */
        postTailElement(pQueue, newIdxTail);

        return true;
    }
    else
        return false;

} /* End of tsq_writeToTail */




/**
 * Check if the queue has currently room to append another element to the tail and return the
 * available element in case.\n
 *   This method, together with the other method tsq_postTailElement(), is an alternative
 * API to write to the end of the queue. If tsq_allocTailElement() returns a non NULL
 * pointer then the caller can take any time to fill the queue element the return value
 * points to without fearing any race conditions. After having the element filled he will
 * use \a tsq_postTailElement to submit the element. From now on the element will be
 * visible to the consumer at the end of the queue.\n
 *   Using this API in contrast to tsq_writeToTail() can save a local copy of the produced
 * data in the producers implementation.\n
 *   The producer APIs to access the tail of the queue are not race condition free. A call
 * of \a tsq_writeToTail must either\n
 *   - return before the next call of the same method or\n
 *   - return before the invocation of \a tsq_allocTailElement or\n
 *   - be initiated after return from \a tsq_postTailElement.
 *
 * This means for a single producer context, that it can alternatingly use \a
 * tsq_writeToTail and the pair of \a tsq_allocTailElement and \a tsq_postTailElement. For
 * concurrent producer contexts it imposes the need for the implementation of mutual
 * exclusion code at the caller's side.
 *   @return
 * Get either the next available ring buffer element by reference or NULL if the queue is
 * currently full.\n
 *   The returned pointer is aligned as had been specified through \a alignOfElement at
 * queue creation time. The returned pointer can be safely casted to the element type and
 * access to the element (or its fields in case of a struct) can be done through this
 * pointer. There is no time limit in keeping the pointer (i.e. until data submission with
 * \a tsq_postTailElement) and using the pointer can avoid the need for an additional local
 * copy of the data during data production time.
 *   @param pQueue
 * The queue object by reference.
 *   @remark
 * The calls of \a tsq_allocTailElement and \a tsq_postTailElement need to be done strictly
 * alternatingly. It is not possible to reserve several elements by multiple calls of the
 * former method and to submit them later by the same number of calls of the latter method.
 *   @remark
 * It is possible to use this method prior to \a tsq_writeToTail to query if the queue is
 * currently full and to avoid a negative return value of that function. It's however
 * disencouraged to do so. There is a little useless computation overhead in doing so and,
 * more important, the pair of \a tsq_allocTailElement and \a tsq_writeToTail is not race
 * condition free; a queue element could become free between the two calls -- the strategy
 * would be too conservative.
 */

void *tsq_allocTailElement(tsq_queue_t *pQueue)
{
    unsigned int newIdxTailDummy;
    return allocTailElement(pQueue, &newIdxTailDummy);

} /* End of tsq_allocTailElement */




/**
 * Submit a queue element, which had been allocated with tsq_allocTailElement().\n
 *   From now on, the element is in the queue and visible to the consumer. The pointer,
 * which had been got from \a tsq_allocTailElement is invalid and must no longer be used.\n
 *   Please, find more details of using this API in the decription of the counterpart
 * method \a tsq_allocTailElement.
 *   @param pQueue
 * The queue object, where the submitted element had been allocated.
 *   @see void *tsq_allocTailElement(tsq_queue_t *)
 */

void tsq_postTailElement(tsq_queue_t *pQueue)
{
    TSQ_ASSERT(pQueue->noFreeElements > 0);
    unsigned int newIdxTail = pQueue->idxTail+1;
    if(newIdxTail >= pQueue->lengthOfRingBuffer)
        newIdxTail = 0;

    postTailElement(pQueue, newIdxTail);

} /* End of tsq_postTailElement */




/**
 * Read a meanwhile receivced new element from the head of the queue.\n
 *   @return
 * Get the pointer to the newly received element if a new element has arrived. \a NULL is
 * returned if no new element has been received since the previous invocation of this
 * method.\n
 *   The element, which is returned by reference is from now on owned by the data consumer,
 * i.e. the caller of this method. It may use the pointer to read the data. The ownership
 * only ends by getting another pointer to another element with a future invocation of this
 * method. In particular, it does not end when a future call of this method returns \a
 * NULL. The access of the owned element is race condition free for the owner of the
 * pointer.\n
 *   The returned pointer is aligned as had been specified through \a alignOfElement at
 * queue creation time. The returned pointer can be safely casted to the element type and
 * access to the element (or its fields in case of a struct) can be done through this
 * pointer without the need for first copying the data.
 *   @param pQueue
 * The queue object to be read from by reference.
 *   @remark
 * The consumer API is not reentrant. It is not possible to let concurrent consumer
 * contexts read from the head of the queue. This holds even if the consumer code
 * implements synchronization code, which ensures mutual exclusion from this method. This
 * is because the method's effect persists after return from the method; the returned
 * element is reserved to the caller until the next method invocation.
 *   @see bool tsq_writeToTail(tsq_queue_t *, const void *, unsigned int)
 */

void *tsq_readFromHead(tsq_queue_t *pQueue)
{
    void *pReceivedElement;
    unsigned int newIdxRead = pQueue->idxRead;
    if(newIdxRead != pQueue->idxTail)
    {
        /* Here we are between the code that used the data from the element owned by the
           consumer so far and the notification that it is no longer used by the consumer.
           We put a full memory barrier to ensure that the execution of the data consuming
           code is surely completed before the notification can become visible to the
           producer. */
        MEMORY_BARRIER_FULL();

        /* By incrementing the read pointer the last recently read element is released. The
           producer will see that that element is no longer owned by the consumer and may
           free it occasionally. */
        if(++newIdxRead >= pQueue->lengthOfRingBuffer)
            newIdxRead = 0;
        pQueue->idxRead = newIdxRead;

        pReceivedElement = (void*)((char*)pQueue->ringBuffer
                                   + newIdxRead*pQueue->maxElementSize
                                  );
    }
    else
        pReceivedElement = NULL;

    return pReceivedElement;

} /* End of tsq_readFromHead */




#ifdef TSQ_ENABLE_API_QUEUE_DIAGNOSTICS
/**
 * Get the number of currently queued elements.\n
 *   The use of this method is not race condition free, producer and consumer can
 * concurrently change the true value. The method should solely be used to get a picture of
 * the use profile of the queue. No essential decision must be based on the result (like
 * rising a warning at high watermark). The most meaningful result is gained if the method
 * is called from the producer context and immediately after appending an element to the
 * queue.
 *   @return
 * Get the number of currently queued elements.
 *   @param pQueue
 * The queue object by reference.
 *   @remark
 * In far the most environments the type \ref atomicUnsignedInt_t is an unsigned int. On
 * exceptional platforms, where the atomic integer type is shorter than unsigned int the
 * method must not be called from a context other than the producer's. The result would be
 * undefined and an assertion can even fire.
 *   @remark
 * The compilation of this API can be turned on/off by configuration switch
 * #TSQ_ENABLE_API_QUEUE_DIAGNOSTICS.
 */

unsigned int tsq_getNoQueuedElements(tsq_queue_t *pQueue)
{
    /* If atomicUnsignedInt_t is shorter than unsigned int then pQueue->noFreeElements can
       be read safely only from the producer thread. */
    unsigned int noQueuedElems = pQueue->lengthOfRingBuffer - pQueue->noFreeElements - 1;
    TSQ_ASSERT(noQueuedElems < pQueue->lengthOfRingBuffer);
    return noQueuedElems;

} /* End of tsq_getNoQueuedElements */
#endif




#ifdef TSQ_ENABLE_API_QUEUE_DIAGNOSTICS
/**
 * Get the maximum number of queued elements, which has been seen since creation of the
 * queue object.
 *   @return
 * Get the number.
 *   @param pQueue
 * The queue object by reference, to which the query relates.
 *   @remark
 * In far the most environments the type \ref atomicUnsignedInt_t is an unsigned int. On
 * exceptional platforms, where the atomic integer type is shorter than unsigned int the
 * method must not be called from a context other than the producer's. The result would be
 * undefined and even an assertion can fire.
 *   @remark
 * The compilation of this API can be turned on/off by configuration switch
 * #TSQ_ENABLE_API_QUEUE_DIAGNOSTICS.
 */

unsigned int tsq_getMaximumQueueUsage(tsq_queue_t *pQueue)
{
    /* If atomicUnsignedInt_t is shorter than unsigned int then pQueue->maxUsage can
       be read safely only from the producer thread. */
    unsigned int maxNoQueued = pQueue->maxUsage;
    TSQ_ASSERT(maxNoQueued < pQueue->lengthOfRingBuffer);
    return maxNoQueued;
    
} /* End of tsq_getMaximumQueueUsage */
#endif




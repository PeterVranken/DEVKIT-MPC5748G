#ifndef VSQ_THREADSAFEQUEUEVARIABLESIZE_INCLUDED
#define VSQ_THREADSAFEQUEUEVARIABLESIZE_INCLUDED
/**
 * @file vsq_threadSafeQueueVariableSize.h
 * Definition of global interface of module vsq_threadSafeQueueVariableSize.c
 *
 * Copyright (C) 2016-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "ede_basicDefinitions.h"
#include "ede_eventDispatcherEngine.config.h"


/*
 * Defines
 */

/** A diagnostic API reporting the usage of the queue can be useful for supporting the
    development of an application (dimensioning the queue sizes) but won't normally be
    required by the ready application. Therefore the compilation of this API can be
    configured using this switch. */
#ifndef VSQ_ENABLE_API_QUEUE_DIAGNOSTICS
# ifdef DEBUG
#  define VSQ_ENABLE_API_QUEUE_DIAGNOSTICS  1
# else
#  define VSQ_ENABLE_API_QUEUE_DIAGNOSTICS  0
# endif
#endif


/** In a memory protected system, i.e., a system with different processes, where a process
    A can't violate the memory contents owned by another process B, the queue can be used
    to safely cross the process boundaries. The data sender, normally residing in the
    operating system process, can send data to some other client process of lower
    confidence level. In such an environment, the following switch should normally be
    enabled:\n
      If set to 1 then the sender will always double-check the feedback from the receiver
    process such that it will never be blocked or harmed by whatever fault at the receiver
    side. Instead, it'll with very high likelihood recognize a corruption of the receiver's
    side of the queue and offer a mechanism to re-enable/re-synchronize the receiver. Even
    in the very rare case if data corruption at the receiver side is not recognized, the
    sender's operation will stay stable and consistent - only the awareness about data
    loss at the receiver side would be lacking in this situation.\n
      The mechanims is not very expensive but still produces some overhead. At the same
    time is it entirely useless if no memory protection is configured between sender and
    receiver - which will be the case in the majority of integration scenarios. Set the
    switch to 0 in unprotected systems. */
#define VSQ_SUPPORT_MEMORY_PROTECTION       1

/** Many error conditions, which are static in the sense that they can only appear due to
    errors in the implementation code are checked by assertions. This relates to the
    implementation of the queue itself, but to the implementation of the client code, too.
    The most typical errors will be caught the first time the code is executed. This
    concept of static error checks makes it inevitable to have an assertion mechanism. Most
    platforms will offer an assertion. #VSQ_ASSERT(bool) needs to expand to the assertion
    on your platform. */
#define VSQ_ASSERT(booleanInvariant)        EDE_ASSERT(booleanInvariant)


/*
 * Global type definitions
 */

/** The head of the queue object as an unknown struct. */
struct vsq_queueHead_t;

/** The head of the queue as an object of unknown type. The API operates with pointers to
    such objects. */
typedef struct vsq_queueHead_t vsq_queueHead_t;

/** The tail of the queue object as an unknown struct. */
struct vsq_queueTail_t;

/** The tail of the queue as an object of unknown type. The API operates with pointers to
    such objects. */
typedef struct vsq_queueTail_t vsq_queueTail_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Prior to queue creation: Query the size of a queue head object. */
unsigned int vsq_getSizeOfQueueHead(void);

/** Prior to queue creation: Query the size of a queue tail object. */
unsigned int vsq_getSizeOfQueueTail(unsigned int maxQueueLength, unsigned int maxElementSize);

/** Create a new, still unlinked, still unusable queue head object. */
vsq_queueHead_t *vsq_createQueueHead(void *pMemoryChunk);

/** Create a new, still unlinked, still unusable queue tail object. */
vsq_queueTail_t *vsq_createQueueTail( void *pMemoryChunk
                                    , unsigned int maxQueueLength
                                    , unsigned int maxElementSize
                                    );

/** After creation of head and tail, connect a queue's tail object to its head object. */
void vsq_linkQueueHeadWithTail( vsq_queueHead_t *pTheQueuesHead
                              , const vsq_queueTail_t *pTheQueuesTail
                              );

/** After creation of head and tail, connect a queue's head object to its tail object. */
void vsq_linkQueueTailWithHead( vsq_queueTail_t *pTheQueuesTail
                              , const vsq_queueHead_t *pTheQueuesHead
                              );

/** Append a new element to the tail of the queue. */
bool vsq_writeToTail(vsq_queueTail_t *pQueueTail, const void *pData, unsigned int noBytes);

/** Check if the queue has currently room to append another element to the tail and return
    the available element in case. */
void *vsq_allocTailElement(vsq_queueTail_t *pQueueTail, unsigned int sizeOfPayload);

/** Submit a queue element, which had been allocated with \a vsq_allocTailElement. */
void vsq_postTailElement(vsq_queueTail_t *pQueueTail);

/** Read a meanwhile receivced new element from the head of the queue. */
const void *vsq_readFromHead(vsq_queueHead_t *pQueueHead, unsigned int *pSizeOfPayload);

#if VSQ_SUPPORT_MEMORY_PROTECTION == 1
/** Query the communication state in a memory protected environment. */
bool vsq_getIsCommunicationBroken(const vsq_queueTail_t * const pQueueTail);
#endif

#if VSQ_SUPPORT_MEMORY_PROTECTION == 1
/** Complete the re-synchronization of a corrupted receiver process. */
void vsq_acknReSyncHead(vsq_queueTail_t *pQueueTail);
#endif

#if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
/** Get the maximum number of queued elements, which has ever been seen. */
unsigned int vsq_getMaximumQueueUsage(const vsq_queueTail_t *pQueueTail);
#endif

#if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
/** Get the maximum number of queued elements, which has ever been seen. */
unsigned int vsq_getMaximumQueueUsageInByte(const vsq_queueTail_t *pQueueTail);
#endif

#endif  /* VSQ_THREADSAFEQUEUEVARIABLESIZE_INCLUDED */

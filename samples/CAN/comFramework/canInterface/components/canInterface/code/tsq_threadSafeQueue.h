#ifndef TSQ_THREADSAFEQUEUE_INCLUDED
#define TSQ_THREADSAFEQUEUE_INCLUDED
/**
 * @file tsq_threadSafeQueue.h
 * Definition of global interface of module tsq_threadSafeQueue.c
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

/*
 * Include files
 */

#include <stdbool.h>
#include "cde_canDispatcherEngine.config.h"


/*
 * Defines
 */

/** A diagnostic API reporting the usage of the queue can be useful for supporting the
    development of an application (dimensioning the queue sizes) but won't normally be
    required by the ready application. Therefore the compilation of this API can be
    configured using this switch. */
#ifndef TSQ_ENABLE_API_QUEUE_DIAGNOSTICS
# define TSQ_ENABLE_API_QUEUE_DIAGNOSTICS 1
#endif


/** Many error conditions, which are static in the sense that they can only appear due to
    errors in the implementation code are checked by assertions. This relates to the
    implementation of the queue itself, but to the implementation of the client code, too.
    The most typical errors will be caught the first time the code is executed. This
    concept of static error checks makes it inevitable to have an assertion mechanism. Most
    platforms will offer an assertion. #TSQ_ASSERT(boolean_t) needs to expand to the
    assertion on your platform. */
#define TSQ_ASSERT(booleanInvariant)    CDE_ASSERT(booleanInvariant)


/* The software is written as portable as possible. This requires the awareness of the C
   language standard it is compiled with - particularly the new stuff from the C11 standard
   strongly supports portability. (Effectively, not using C11 means that GCC will be
   required for a lower degree of portability.)
     If your environment supports C11 then you should use it and make this #define on the
   compiler's command line. */
#if defined(__STDC_VERSION__)
# if (__STDC_VERSION__)/100 == 2011
#  define _STDC_VERSION_C11
# elif (__STDC_VERSION__)/100 == 1999
#  define _STDC_VERSION_C99
# endif
#endif


/*
 * Global type definitions
 */

/** The queue object as an unknown struct. */
struct tsq_queue_t;

/** The queue object as an unknown type. The API operates with pointers to such objects. */
typedef struct tsq_queue_t tsq_queue_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Prior to queue creation: Query the size of a queue object. */
unsigned int tsq_getSizeOfQueue( unsigned int maxQueueLength
                               , unsigned int maxElementSize
                               , unsigned int alignOfElement
                               );

/** Create a new queue object. */
struct tsq_queue_t *tsq_createQueue( void *pMemoryChunk
                                   , unsigned int maxQueueLength
                                   , unsigned int maxElementSize
                                   , unsigned int alignOfElement 
                                   );

/** Query the maximum permitted size of a queueable element. */
unsigned int tsq_getMaxSizeOfElement(tsq_queue_t *pQueue);

/** Append a new element to the tail of the queue. */
bool tsq_writeToTail(tsq_queue_t *pQueue, const void *pData, unsigned int noBytes);

/** Check if the queue has currently room to append another element to the tail and return
    the available element in case. */
void *tsq_allocTailElement(tsq_queue_t *pQueue);

/** Submit a queue element, which had been allocated with \a tsq_allocTailElement. */
void tsq_postTailElement(tsq_queue_t *pQueue);

/** Read a meanwhile receivced new element from the head of the queue. */
void *tsq_readFromHead(tsq_queue_t *pQueue);

#ifdef TSQ_ENABLE_API_QUEUE_DIAGNOSTICS
/** Get the number of currently queued elements. */
unsigned int tsq_getNoQueuedElements(tsq_queue_t *pQueue);
#endif

#ifdef TSQ_ENABLE_API_QUEUE_DIAGNOSTICS
/** Get the maximum number of queued elements, which has ever been seen. */
unsigned int tsq_getMaximumQueueUsage(tsq_queue_t *pQueue);
#endif

#endif  /* TSQ_THREADSAFEQUEUE_INCLUDED */

/**
 * @file vsq_threadSafeQueueVariableSize.c
 * Thread-safe implementation of a queue. Filling and reading the queue may be done from
 * different threads. It doesn't matter whether these threads have same or different
 * priorities and whether they are running on the same or on different cores.\n
 *   The implementation is lock-free. Mutual exclusion of threads is based on spatial
 * separation rather then on serialization (ordering in time). No two threads will ever
 * read or write to the same address space. The implementation is based on shared memory,
 * which can be read and written by both affected threads. In practice, for a multi-core
 * environment, this will almost always mean some uncached memory area.\n
 *   If the queue connects two processes with enabled memory protection, then the sender of
 * data (tail process) needs to belong to the trusted sphere of code in order not to
 * endanger the stability of the receiver process: If the queue data is potentially
 * damaged then the receiver will not only get damaged data but also wrong pointers to
 * data, which may cause potential access violations and resulting exceptions in the
 * receiving process.\n
 *   It doesn't matter if the receiver doesn't belong to the sphere of trusted code. If the
 * receiver data is damaged then the stability of the sender is not harmed. It may of
 * course lead to loss of data (data not read from the queue, still unread data overwritten
 * by the sender), but the sender will not operate with damaged data, it'll not run a risk
 * of access violation or exception.\n
 *   For the principal use case of a CAN interface, this asymmetry is just fine. The sender
 * will always be the (trusted) OS code, which sends Rx messages or Tx send-acknowledges to
 * the receiver, which may then be some untrusted QM code.
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
/* Module interface
 *   vsq_getSizeOfQueueHead
 *   vsq_getSizeOfQueueTail
 *   vsq_createQueueHead
 *   vsq_createQueueTail
 *   vsq_linkQueueHeadWithTail
 *   vsq_linkQueueTailWithHead
 *   vsq_getMaxSizeOfElement
 *   vsq_writeToTail
 *   vsq_allocTailElement
 *   vsq_postTailElement
 *   vsq_readFromHead
 *   vsq_getIsCommunicationBroken
 *   vsq_acknReSyncHead
 *   vsq_getMaximumQueueUsage
 *   vsq_getMaximumQueueUsageInByte
 * Local functions
 *   alignedSizeOfObject
 *   isaligned
 *   calculateSizeOfRingBuffer
 *   getElementAt
 *   getLinkPtrOfElementAt
 *   setLinkPtrOfElementAt
 *   setHdrOfElementAt
 *   allocTailElement
 *   postTailElement
 *   byteOffsetOfRingBuffer
 */

/* The software is written as portable as possible. This requires the awareness of the C
   language standard it is compiled with - particularly the new stuff from the C11 standard
   strongly supports portability. (Effectively, not using C11 means that GCC will be
   required for a lower degree of portability.)
     If your environment supports C11 then you should use it and make this #define on the
   compiler's command line.
     With respect to the language feature C11 and C17 are identical. We combine the in one
   switch. */
#if defined(__STDC_VERSION__)
# if (__STDC_VERSION__)/100 == 2017
#  define _STDC_VERSION_C17
#  define _STDC_VERSION_C17_C11
# elif (__STDC_VERSION__)/100 == 2011
#  define _STDC_VERSION_C11
#  define _STDC_VERSION_C17_C11
# elif (__STDC_VERSION__)/100 == 1999
#  define _STDC_VERSION_C99
# endif
#endif

/*
 * Include files
 */

#include "vsq_threadSafeQueueVariableSize.h"

#include <string.h>
#include <limits.h>

#if defined(_STDC_VERSION_C17_C11)
# include <stdatomic.h>
#endif



/*
 * Defines
 */

/* Anonymous unions are a means to improve readability of the code. */
#if defined(__GNUC__)
#elif defined(__arm__)
# pragma anon_unions
#endif

/** The thread-safe implementation of the dispatcher queue builds on defined memory
    ordering; machine operations are expected to happen in the order of C code statements.
    This is not easy to achieve in C as the language semantics doesn't have awareness of
    concurrency (before C11). The solution will always be target and compiler dependent.
    Here, we offer a macro, which is meant to implement a full memory barrier on the
    target.\n
      Fortunately, when using GCC there is a platform independent solution. See
    http://gcc.gnu.org/onlinedocs/gcc-4.4.3/gcc/Atomic-Builtins.html for details. */
#if defined(_STDC_VERSION_C17_C11)
# define MEMORY_BARRIER_FULL()  {atomic_thread_fence(memory_order_seq_cst);}
#elif __GNUC__
# define MEMORY_BARRIER_FULL()  __sync_synchronize()
#elif __arm__
# define MEMORY_BARRIER_FULL()  __sync_synchronize()
#else  
# error Macro MEMORY_BARRIER_FULL() needs to be defined for your target
#endif



/** The alignment of type queueElement_t. The queue element can make use of a configurable
    integer size for storage of indexes. We need to know the alignment for this type and
    compilers not supporting C11 can't figure it out. You need to configure the alignment
    in accordance with the chosen index type, see uintidx_t.\n
      TriCore: The alignment of an unsigned int is not identical to its size. The alignment
    can be reduced to 2 Byte even if unsigned int is configured as index type. */
#if defined(_STDC_VERSION_C17_C11)
# define ALIGN_OF_HDR      (_Alignof(queueElement_t))
#elif defined(__AVR__)
# define ALIGN_OF_HDR      (1u)
#else
# define ALIGN_OF_HDR      (sizeof(((const queueElement_t*)NULL)->idxNext))
#endif


/** The alignment of the payload of the queued elements in Byte. The payload of an element
    read from the queue is returned by reference. The got address will have at least this
    alignment.\n
      The value will normally be the largest natural alignment for the given architecture,
    i.e., 4 Byte for 32 Bit systems and 8 Byte on 64 Bit systems. However, special
    architectures like TriCore can deviate. A 32 Bit TriCore could use 2 Byte if the payload
    doesn't contain double values.\n
      The specified value must not be less than #ALIGN_OF_HDR. This is checked by
    assertion. */
#if defined(_STDC_VERSION_C17_C11)
# define ALIGN_OF_PAYLOAD   (_Alignof(uintptr_t))
#elif defined(__AVR__)
# define ALIGN_OF_PAYLOAD   (1u)
#else
# define ALIGN_OF_PAYLOAD   (sizeof(uintptr_t))
#endif

_Static_assert( ALIGN_OF_PAYLOAD >= EDE_COMMON_MACHINE_ALIGNMENT
              , "Suspicious specification of machine alignment"
              );


/** The alignment of the chosen atomic integer type. Mostly, it'll be sizeof(uintatomic_t),
    but because of some specialities on particular platforms, we make this explicit.\n
      TriCore: The alignment of an unsigned int is not identical to the alignment, we
    require, which is the alignment that ensures atomic read and write operations. Taking
    the maximum of alignment and size should be alright in nearly all environments. */
#if defined(_STDC_VERSION_C17_C11)
# define ALIGN_OF_UINTATOMIC (MAX(_Alignof(uintatomic_t), sizeof(uintatomic_t)))
#else
# define ALIGN_OF_UINTATOMIC (sizeof(uintatomic_t))
#endif


/** The maximum of two numbers as a preprocessor expression. */
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/** The minimum of two numbers as a preprocessor expression. */
#define MIN(a,b) (((a) < (b)) ? (a) : (b))


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
    type casts still ensure code correctness with one documented exception: The optional
    diagnostic API functions are now restricted to be used solely in the producer context.
    However, these functions are not essential and will be switched off in most
    integrations. We decided to not clean this up by using typedef'ed integers throughout
    the complete implementation -- this would degrade the readability and maintainability
    of the code and such systems are anyway not the targeted platforms. */
typedef ede_atomicUnsignedInt_t uintatomic_t;


/** This type is used to store index and size information for queue elements. 16, 32 and
    even 64 Bit types can be specified. (Where 64 Bit should have no practical relevance.)
    The appropriate choice is not a really a matter of having a 16 or 32 Bit architecture.
    Even on 32 Bit embedded platforms, the RAM consumption is an important aspect and the
    choice can save a significant amount of RAM: The size of header information for each
    queued element is 4 Byte if a 16 Bit type is configured and 8 Byte for a 32 Bit type.
    If the alignment for the payload is no more than 4 Byte (almost certain for 32 Bit
    systems) then this means a RAM reduction of 4 Byte per queued element. This can sum up
    to several hundreds of Byte for a typical embedded application.}\n
      Caution, the chosen type must not be larger than unsigned int on the given platform. */
typedef unsigned short int uintidx_t;

/** The head of the queue. This is, where previously queued elements are read from. The
    producer requires read access to this element, the consumer needs to have full access
    rights. (Whether memory access restrictions actually apply, depends on how the code is
    integrated into a given environment; this implementation just guarantees, that read
    access to the head element suffices for the producer.) */
struct vsq_queueHead_t
{
    /** Read access to the other end of the queue is granted by this reference. This member
        is constant after queue creation. */
    const vsq_queueTail_t *pTail;

    /** The read position into the ring buffer of the queue. The element, this index refers
        to, is owned by the consumer for race condition free data processing.\n
          The name of this member results from the idea of using the ring buffer to
        implement a queue; new elements are appended to the tail of the queue and elder,
        consumed ones are removed from the (stale) head.\n
          This member is read-only to the data producer and updated by the consumer. It is
        important that this member can be read or written in a single atomic operation;
        this explains the type, which has to be configured platform dependent. */
    volatile
        #ifdef _STDC_VERSION_C17_C11
        _Alignas(ALIGN_OF_UINTATOMIC) /* Required for TriCore */
        #endif
        uintatomic_t idxHead;
};



/** The tail of the queue. This is, where new elements are appended to. A ring buffer
    implementation has been chosen. Note, the buffer space is considered to belong to the
    tail element; The queue contents belong into the memory access sphere of the producer
    and they are exposed to the consumer only with read access. (Whether access
    restrictions actually apply, depends on how the code is integrated into a given
    environment; this implementation just guarantees, that read access to the tail element
    suffices for the consumer.) */
struct vsq_queueTail_t
{
    /** Read access to the other end of the queue is granted by this reference. This member
        is constant after queue creation. */
    const vsq_queueHead_t *pHead;

    /** The ring buffer elements of the queue.\n
          This member is written by producer and consumer but both will never touch it at
        the same array entry at a time. This spatial mutual exclusion is controlled by the
        other members \a idxHead and \a idxTail. */
    void *ringBuffer;

    /** The size in Byte of the ring buffer.\n
          This member is constant and read-only (after initialization) and out of scope of
        race conditions between producer and consumer. */
    unsigned int sizeOfRingBuffer;

#if VSQ_SUPPORT_MEMORY_PROTECTION == 1  ||  VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
    /** The position of the current head of the list of data elements currently in the ring
        buffer. The index denotes the perspective of the producer. The consumer has his own
        index \a idxRead. The distinction between producer and consumer index avoids
        forbidden read-modify-write operations.\n
          This member is read and updated solely by the producer. There are no race
        conditions with the consumer code. */
    unsigned int idxHeadCopy;
#endif

    /** The position of the current tail of the list of data elements currently in the ring
        buffer. The tail element always exists. Strictly spoken, we never have an empty
        queue. The consumer always has the ownership of one element and after creation of
        the queue this is the (empty) tail element. (Although the consumer doesn't have
        awareness of this initial ownership.)\n
          This member is read-only to the data consumer and updated by the producer. It is
        essential that this member can be read or written in a single atomic operation;
        this explains the type, which has to be configured platform dependent. */
    volatile
        #ifdef _STDC_VERSION_C17_C11
        _Alignas(ALIGN_OF_UINTATOMIC) /* Required for TriCore */
        #endif
        uintatomic_t idxTail;

    /** The use of the API vsq_allocTailElement/vsq_postTailElement requires temporary
        storage of some intermediate data. Since the reentrance of this function pair is
        anyway not given by principle, we can use the queue object itself to store this
        data. idxNewAllocatedTail is set by vsq_allocTailElement() for later use by
        vsq_postTailElement().\n
          This member is accessed only by the producer code and is not subject to race
        conditions. */
    unsigned int idxNewAllocatedTail;

#if VSQ_SUPPORT_MEMORY_PROTECTION == 1
    /** For memory protected systema only: The sender checks for correct behavior of
        receiver. Corrupted receiver data will break the communication. This is indicated
        by this flag. As long as no memories are crrupted, it'll always be \a false. */
    bool isHeadCorrupted;
#endif

#if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
    /** The current number of elements in the ring buffer.\n
          This member is updated and read solely by the producer. There are no race
        conditions. */
    unsigned int usage;

    /** The maximum number of elements, which had ever been stored in the ring buffer.\n
          This member is read-only to the data consumer and updated by the producer. It is
        essential that this member can be read or written in a single atomic operation;
        this explains the type, which has to be configured platform dependent. */
    volatile
        #ifdef _STDC_VERSION_C17_C11
        _Alignas(ALIGN_OF_UINTATOMIC) /* Required for TriCore */
        #endif
        uintatomic_t maxUsage;

    /** The maximum number of bytes so far, which had been used for queuing elements. The
        number of bytes includes all overhead for data organization and can be related to
        the size of the ring buffer.\n
          This number can be used at application validation time for optimization of the
        required queue size.\n
          This member is read-only to the data consumer and updated by the producer. It is
        essential that this member can be read or written in a single atomic operation;
        this explains the type, which has to be configured platform dependent. */
    volatile
        #ifdef _STDC_VERSION_C17_C11
        _Alignas(ALIGN_OF_UINTATOMIC) /* Required for TriCore */
        #endif
        uintatomic_t maxUsageInByte;
#endif
};



/** Formally, this is the type of a queued element. We use a flexible array member to model
    the payload data. Effectively, this is the heaer of the element, since the payload data
    is not really inside the struct. The combination of both characteristics is
    advantageous, we can access the payload by the normal dot operator. */
typedef struct queueElement_t
{
    /** A union is applied just to force a certain size of the struct. The size needs to be
        an integral multiple of the alignment, which is specified for the payload data. The
        fulfillment of the specification is double-checked by several depending assertions.
        If such an assertion fires then it may easily be that this type definition is
        wrong.
          The union is implemented anonymously, as the alternatives are meaningless to the
        functional code and effectively not used in the source code. */
    union
    {
        /** The use of an union to ensure the object size requires an anonymous struct to
            bundle all true struct members. */
        struct
        {
            /** The link to the successor element in the queue. It is the Byte index into
                the ring buffer at which the first byte of the header of the successor is
                found. */
            uintidx_t idxNext;

            /** The size of the payload of the queued element in Byte. */
            uintidx_t sizeOfPayload;
        };

        /** A member of the union, which is not used but which enforces the required size
            of the queue element header. The size needs to be an integral multiple of
            #ALIGN_OF_PAYLOAD. */
        uint8_t dummyToForceAlignment[ALIGN_OF_PAYLOAD];
    };

#if (defined(_STDC_VERSION_C17_C11) || defined(_STDC_VERSION_C99))  \
    && (!defined(__GNUC__) ||  __GNUC__ >= 5)
    uint8_t payload[];
#elif defined(__GNUC__)
    uint8_t payload[0];
#else
# error Flexible array members are not supported by your compiler
#endif
} queueElement_t;


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
 * We are creating an array of elements. The array as a whole must be correctly aligned
 * (using method byteOffsetOfRingBuffer()) but the element size must be a multiple of the
 * element alignment, too - otherwise would latest the second element in the array be
 * misaligned. This method computes the element size to be reserved in the array based on
 * the user demanded element size.
 *   @return
 * Get the number of bytes, which need to be reserved for each element in the ring buffer
 * array that implements the queue.
 *   @param sizeOfElement
 * The user specified size of an element in the queue.
 *   @param alignOfElement
 * The alignment required for an element in the queue.
 */
static inline unsigned int alignedSizeOfObject( unsigned int sizeOfElement
                                              , unsigned int alignOfElement
                                              )
{
    const unsigned int mask = alignOfElement-1;
    return ((sizeOfElement + mask) & ~mask);

} /* End of alignedSizeOfObject */




#ifdef DEBUG
/**
 * Test function, mainly intended for code self-tests in assertions: Check proper alignment
 * of an address or Byte index.
 *   @return
 * \a true, if address/index has required alignment, else \a false.
 *   @param addressOrIndex
 * The address or Byte index to check.
 *   @param alignment
 * The required alignment. Is a power of two, most likely 1, 2, 4 or 8.
 */
static inline bool isaligned(uintptr_t address, unsigned int alignment)
{
    return (address & ~(alignment-1)) == address;

} /* End of isaligned */
#endif


/**
 * Figure out, how many ring buffer space we need at minimum to store a given number of
 * elements of given size.
 *   @return
 * Get the number of bytes required for the ring buffer.
 *   @param maxNoStdElements
 * This number of elements, each having a size of \a sizeOfStdElement Byte, needs to fit
 * into the queue.
 *   @param sizeOfStdElement
 * See \a maxNoStdElements.
 */
static unsigned int calculateSizeOfRingBuffer( unsigned int maxNoStdElements
                                             , unsigned int sizeOfStdElement
                                             )
{
    /* (maxQueueLength+1): One element of the ring buffer is always owned by the consumer
       for reading and not available to filling the queue. To fulfill the user
       expectations, we need to allocate one element more than the demanded maximum length
       of the queue.
         sizeof(queueElement_t) is guaranteed to be a multiple of ALIGN_OF_PAYLOAD, so that
       the payload beginns at the correct aligned address. This is a constraint from
       applying a flexible array member for the payload. */
    VSQ_ASSERT(alignedSizeOfObject(sizeof(queueElement_t), ALIGN_OF_PAYLOAD) % ALIGN_OF_PAYLOAD
               == 0
               &&  offsetof(queueElement_t, payload) == sizeof(queueElement_t)
              );
    return (maxNoStdElements+1)
           * (sizeof(queueElement_t)                                    /* Element header */
              + alignedSizeOfObject(sizeOfStdElement, ALIGN_OF_PAYLOAD) /* Payload */
             );
} /* End of calculateSizeOfRingBuffer */






/**
 * Retrieve a queued element from the ring buffer, which is identified by its index in that
 * linear array.
 *   @return
 * Get the element by reference. The returned pointer permits read and write access.
 *   @param pQueueTail
 * The tail object of the affected queue by reference.
 *   @param idxStartOfElement
 * The Byte offset into the ring buffer. The first byte of an element will be assumed at
 * this position.
 */
static inline queueElement_t *getElementAt( const vsq_queueTail_t * const pQueueTail
                                          , unsigned int idxStartOfElement
                                          )
{
    VSQ_ASSERT(isaligned(idxStartOfElement, ALIGN_OF_PAYLOAD)
               &&  idxStartOfElement < pQueueTail->sizeOfRingBuffer
              );
    return (queueElement_t*)((char*)pQueueTail->ringBuffer + idxStartOfElement);

} /* End of getElementAt */



/**
 * Get the link index of the element in the ring buffer, which \a idxStartOfElement points
 * to. The link index is the index in the linear ring buffer of the first byte of the
 * header of the successor element in the queue.
 *   @return
 * The link is implemented as the Byte index into the ring buffer of the first header byte
 * of the next element. Get this index.
 *   @param pQueueTail
 * The tail object of the iterated queue by reference.
 *   @param idxStartOfElement
 * The Byte offset into the ring buffer. The first byte of an element will be assumed at
 * this position.
 */
static inline unsigned int getLinkPtrOfElementAt( const vsq_queueTail_t * const pQueueTail
                                                , unsigned int idxStartOfElement
                                                )
{
    const queueElement_t * const pElem = getElementAt(pQueueTail, idxStartOfElement);
    const unsigned int idxStartOfNextElement = pElem->idxNext;
    VSQ_ASSERT(idxStartOfNextElement < pQueueTail->sizeOfRingBuffer);
    return idxStartOfNextElement;

} /* End of getLinkPtrOfElementAt */



/**
 * Set the link index of the element in the ring buffer, which \a idxStartOfElement points
 * to. The link index is the index in the linear ring buffer of the first byte of the
 * header of the successor element in the queue.
 *   @param pQueueTail
 * The tail object of the affected queue by reference.
 *   @param idxStartOfElement
 * The Byte offset into the ring buffer. The first byte of an element will be assumed at
 * this position.
 *   @param idxStartOfSuccessor
 * The Byte offset into the ring buffer. The first byte of the successor element will be
 * assumed at this position.
 */
static inline void setLinkPtrOfElementAt( vsq_queueTail_t * const pQueueTail
                                        , unsigned int idxStartOfElement
                                        , unsigned int idxStartOfSuccessor
                                        )
{
    queueElement_t * const pElem = getElementAt(pQueueTail, idxStartOfElement);

    VSQ_ASSERT(isaligned(idxStartOfSuccessor, ALIGN_OF_PAYLOAD)
               &&  idxStartOfSuccessor < pQueueTail->sizeOfRingBuffer
              );
    pElem->idxNext = idxStartOfSuccessor;

} /* End of setLinkPtrOfElementAt */



/**
 * Set the complete header information of the element in the ring buffer, which \a
 * idxStartOfElement points to. The header consists of the payload size and the link index,
 * which is the index in the linear ring buffer of the first byte of the header of the
 * successor element in the queue.
 *   @param pQueueTail
 * The tail object of the affected queue by reference.
 *   @param idxStartOfElement
 * The Byte offset into the ring buffer. The first byte of an element will be assumed at
 * this position.
 *   @param idxStartOfSuccessor
 * The Byte offset into the ring buffer. The first byte of the successor element will be
 * assumed at this position.
 *   @param sizeOfPayload
 * The size of the payload of the element addressed by idxStartOfElement.
 */
static inline void setHdrOfElementAt( vsq_queueTail_t * const pQueueTail
                                    , unsigned int idxStartOfElement
                                    , unsigned int idxStartOfSuccessor
                                    , unsigned int sizeOfPayload
                                    )
{
    queueElement_t * const pElem = getElementAt(pQueueTail, idxStartOfElement);

    VSQ_ASSERT(isaligned(idxStartOfSuccessor, ALIGN_OF_PAYLOAD)
               &&  idxStartOfSuccessor < pQueueTail->sizeOfRingBuffer
               &&  idxStartOfSuccessor == 0
                   ||  idxStartOfElement + sizeof(queueElement_t) + sizeOfPayload
                       <= idxStartOfSuccessor
              );
    pElem->idxNext = idxStartOfSuccessor;
    pElem->sizeOfPayload = sizeOfPayload;

} /* End of setHdrOfElementAt */



/**
 * Check if the queue has currently room to append a new element to the tail. Return the
 * available element in case.
 *   @return
 * Either get the pointer to the location where the payload of the new element can be
 * copied to or NULL if the queue is currently too full to store the new element.
 *   @param pQueueTail
 * The queue object by reference.
 *   @param pIdxNewTail
 * Part of processing is the computation of the index of the element in the linear array,
 * which implements the ring buffer. This index is returned by reference if the function
 * doesn't return NULL. It points to the header of the returned element.
 *   @param sizeOfPayload
 * The payload of the new element will have a size of this number of bytes.
 *   @remark
 * The function is an inline implementation of the common part of both APIs to access the
 * tail of the queue.
 */
static inline void *allocTailElement( vsq_queueTail_t * const pQueueTail
                                    , unsigned int *pIdxNewTail
                                    , unsigned int sizeOfPayload
                                    )
{
#if VSQ_SUPPORT_MEMORY_PROTECTION == 1
    if(pQueueTail->isHeadCorrupted)
    {
        /* The communication is broken. No further elements can be queued until the
           receiver has re-synchronized. */
        return NULL;
    }
#endif
    const unsigned int idxHead = pQueueTail->pHead->idxHead
                     , idxTail = pQueueTail->idxTail
                     , sizeOfRingBuffer = pQueueTail->sizeOfRingBuffer;
#if VSQ_SUPPORT_MEMORY_PROTECTION == 1  ||  VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
    unsigned int idxHeadCopy = pQueueTail->idxHeadCopy;
# if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
    unsigned int noElements = pQueueTail->usage;
# endif
    /* Keep track with the movement of the read index by the consumer. This way, we can
       check for corruption of the receiver's read pointer and maintain the number of
       currently stored elements without the need of read-modify-write operations (which we
       don't have). */
    while(idxHeadCopy != idxHead)
    {
#if VSQ_SUPPORT_MEMORY_PROTECTION == 1
        if(idxHeadCopy == idxTail)
        {
            /* Inconsistency: We reached the tail of the queue without encountering the
               current head. idxHead is corrupted at the client side of the queue.
               Communication is broken. */
            pQueueTail->isHeadCorrupted = true;
            pQueueTail->idxHeadCopy = idxTail;
            return NULL;
        }
#endif
# if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
        /* Acknowledge the considered element and check for underflow. */
        -- noElements;
# endif
        /* Advance to successor of visited element. */
        idxHeadCopy = getLinkPtrOfElementAt(pQueueTail, idxHeadCopy);
    }
# if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
    VSQ_ASSERT(noElements * sizeof(queueElement_t) <= pQueueTail->sizeOfRingBuffer);
# endif

    /* Write back the updated read-acknowledge pointer. */
    pQueueTail->idxHeadCopy = idxHeadCopy;
#endif

    /* We use a ring buffer but don't want to offer a kind of wrapped memory space to the
       caller. Either the rest of ring buffer space behind the tail suffices or the
       beginning of the ring buffer up to the head. Otherwise we reject the new element.
         Before writing, the tail index points to the last queued element (at the very
       beginning and later potentially the one, which is currently owned by the consumer
       for reading). */

    /* Initial candidate for placing the new element is just behind the current tail. */
    const unsigned int idxNew = getLinkPtrOfElementAt(pQueueTail, idxTail);

    const unsigned int sizeOfElem = sizeof(queueElement_t)
                                    + alignedSizeOfObject(sizeOfPayload, ALIGN_OF_PAYLOAD);
    unsigned int idxNewTail = UINT_MAX;
    if(idxNew > idxHead)
    {
        /* We can place the new element behind the tail or - if this doesn't fit - we skip
           the rest of the buffer and start over at the beginning. */
        if(sizeOfRingBuffer >= idxNew + sizeOfElem)
        {
            /* The rest of the ring buffer has still enough space. idxNew is confirmed. */
            idxNewTail = idxNew;
        }
        else if(idxHead >= sizeOfElem)
        {
            /* The end of the ring buffer was too small, but our second choice, the
               beginning of the ring buffer, is large enough. Index 0 is confirmed. */
            idxNewTail = 0;
        }
    }
    else if(idxNew < idxHead  &&  idxHead >= idxNew + sizeOfElem)
    {
        /* The ring buffer has enough space between tail and head. idxNew is confirmed. */
        idxNewTail = idxNew;
    }

    if(idxNewTail != UINT_MAX)
    {
        /* The link to the found new element needs to be written into the tail element so
           far.\n
             We can safely touch the tail so far although it may already be owned by the
           consumer: The link won't ever be evaluated by the consumer before it decides to
           advance to the next element and this decision is triggered only by statements
           down below the memory barrier in postTailElement(). */
        setLinkPtrOfElementAt( pQueueTail
                             , /* idxStartOfElement */ idxTail
                             , /* idxStartOfSuccessor */ idxNewTail
                             );

        /* The link to the successor of our new element can't be made yet - we can't
           anticipate its size, which would be needed for its placement. However, we set a
           preliminary link, which points directly behind the new element. This preliminary
           value is evaluated by allocTailElement(), when it is called for the successor.
           The position directly behind will be the initial candidate for placing the
           successor. */
        unsigned int idxStartOfSuccessor = idxNewTail + sizeOfElem;
        if(idxStartOfSuccessor >= sizeOfRingBuffer)
        {
            /* "Directly behind" is meant in a cyclic manner. It is the beginning of the buffer
               if we reach its end. */
            VSQ_ASSERT(idxStartOfSuccessor == sizeOfRingBuffer);
            idxStartOfSuccessor = 0;
        }
        setHdrOfElementAt( pQueueTail
                         , /* idxStartOfElement */ idxNewTail
                         , idxStartOfSuccessor
                         , sizeOfPayload
                         );

#if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
        /* Write back the updated element count. +1: This function actually means adding a
           new element. */
        pQueueTail->usage = noElements + 1;
        if(noElements >= pQueueTail->maxUsage)
            pQueueTail->maxUsage = noElements + 1;

        /* Compute the currently allocated number of bytes. It is the cyclic difference
           from head to the end of the upcoming element, which begins at the new tail.
             Note, at storage of the first element, the calculation incorporates the empty
           dummy element. This is not a fault, as it belongs to the overhead, which is
           documented to belong into the reported usage value. */
        unsigned int usageInByte = idxStartOfSuccessor - idxHead;
        if((int)usageInByte < 0)
            usageInByte += pQueueTail->sizeOfRingBuffer;
        if(usageInByte > pQueueTail->maxUsageInByte)
            pQueueTail->maxUsageInByte = usageInByte;
#endif
        /* The function returns the position of the new element in the ring buffer (needed
           in postTailElement() for announcing the new element to the consumer) and the
           pointer to where to put the payload data. */
        *pIdxNewTail = idxNewTail;
        return &getElementAt(pQueueTail, idxNewTail)->payload[0];
    }
    else
    {
#if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
        /* Write back the updated element count. */
        pQueueTail->usage = noElements;
#endif
        /* The function returns NULL - no space. */
        return NULL;
    }
} /* End of allocTailElement */



/**
 * Counterpart to void *allocTailElement(vsq_queue_t *, unsigned int *): Finalize appending
 * the previously allocated element to the queue, i.e., notify a consumer the availability
 * of this element. The ownership of the reserved element, which was gained with
 * allocTailElement(), ends with entry into this method; the producer must not touch the
 * element any more.
 *   @param pQueueTail
 * The queue object by reference.
 *   @param idxNewTail
 * The index of the first header byte of the appended element in the linear array, which
 * implements the ring buffer. This index is entirely meaningless to the caller but had
 * been returned by the preceding, corresponding call of \a allocTailElement. The producer
 * code is responsible of storing and returning this value.
 *   @remark
 * The function is an inline implementation of the common part of both APIs to access the
 * tail of the queue.
 */
static inline void postTailElement( vsq_queueTail_t * const pQueueTail
                                  , unsigned int idxNewTail
                                  )
{
    /* We put a full memory barrier between filling the new element and updating the link
       in the tail so far on the one hand and notifying the availablity of the new element
       to the consumer. All instructions for element filling will have completed before the
       index change of the tail gets visible to the consumer. */
    MEMORY_BARRIER_FULL();

    /* Notify the new element by updating the shared tail index in an atomic write. */
    pQueueTail->idxTail = idxNewTail;

} /* End of postTailElement */




/**
 * Compute the byte offset of the memory for the ringbuffer if putting both, the object and
 * the ringbuffer into a single memory chunk. The two elements can't simply be concatenated,
 * we need to consider a gap to fulfill all alignment requirements.
 *   @return
 * Get the offset from the beginning of the queue object to the beginning of the ring
 * buffer in Byte.
 *   @remark
 * This simple function holds the common code of object creation and object size query.
 */
static inline unsigned int byteOffsetOfRingBuffer(void)
{
    /* Consider the maybe different alignment of the queue element when computing the
       beginning of the ring buffer memory inside the chunk. */
    return alignedSizeOfObject(sizeof(vsq_queueTail_t), ALIGN_OF_PAYLOAD);

} /* End of byteOffsetOfRingBuffer */



/**
 * Calculate the size of a queue head object.\n
 *   This function is meant to be called prior to creation of a queue head object. The
 * caller of the constructor is in charge of allocating the memory for the object - the
 * intended use case of the queue implementation is the embedded environment, which doesn't
 * permit to allocate memory dynamically using \a malloc. The typical use case avoids the
 * use of \a malloc:
 * @code
 *  const unsigned int sizeOfQHead = vsq_getSizeOfQueueHead();
 *  _Alignas(vsq_queueHead_t) char memoryChunk[sizeOfQHead];
 *  vsq_queueHead_t *pMyNewQueuesHead = vsq_createQueueHead(memoryChunk);
 *  vsq_queueTail_t *pMyNewQueuesTail = ...
 *  vsq_linkQueueHeadWithTail(pMyNewQueuesHead, pMyNewQueuesTail);
 *  vsq_linkQueueTailWithHead(pMyNewQueuesTail, pMyNewQueuesHead);
 * @endcode
 *   Alternatively, the embedded environment may offer a simple, uncritical memory
 * allocation or partitioning API, most likely without a free function to avoid
 * fragmentation and indeterministic timing behavior.
 *   @return
 * The number of bytes required to construct a queue object with the passed parameters.
 * Only this number is computed, nothing else happens, in particular no queue head object
 * is constructed.
 *   @remark
 * The memory chunk required by the constructor does not only need to have the right
 * minimum size but, secondary, it needs to have the right alignment, which is specified at
 * compile-time using macro #ALIGN_OF_PAYLOAD.
 *   @see vsq_createQueueHead()
 */
unsigned int vsq_getSizeOfQueueHead(void)
{
    return sizeof(vsq_queueHead_t);

} /* End of vsq_getSizeOfQueueHead */




/**
 * Calculate the size of a queue tail object.\n
 *   This function is meant to be called prior to creation of a queue tail object. The
 * caller of the constructor is in charge of allocating the memory for the object - the
 * intended use case of the queue implementation is the embedded environment, which doesn't
 * permit to allocate memory dynamically using \a malloc.\n
 *   This function needs to be called with the same parameters as later the constructor. The
 * constructor will silently assume that the memory chunk it receives from the caller will
 * have the size computed by this method. The typical use case avoids the use of \a malloc:
 * @code
 *  struct qElement_t;
 *  #define MAX_Q_LEN 10
 *  const unsigned int sizeOfQTail = vsq_getSizeOfQueueTail( MAX_Q_LEN
 *                                                         , sizeof(struct qElement_t)
 *                                                         );
 *  VSQ_ASSERT(_Alignof(struct qElement_t) <= _Alignof(uintptr_t));
 *  _Alignas(vsq_queueHead_t) char memoryChunk[sizeOfQTail];
 *  vsq_queueHead_t *pMyNewQueuesHead = ...
 *  vsq_queueTail_t *pMyNewQueuesTail = vsq_createQueueTail( memoryChunk
 *                                                         , MAX_Q_LEN
 *                                                         , sizeof(struct qElement_t)
 *                                                         );
 *  vsq_linkQueueHeadWithTail(pMyNewQueuesHead, pMyNewQueuesTail);
 *  vsq_linkQueueTailWithHead(pMyNewQueuesTail, pMyNewQueuesHead);
 * @endcode
 *   Alternatively, the embedded environment may offer a simple, uncritical memory
 * allocation or partitioning API, most likely without a free function to avoid
 * fragmentation and indeterministic timing behavior.
 *   @return
 * The number of Byte required to construct a queue tail object with the passed parameters.
 * Only this number is computed, nothing else happens, in particular no queue tail object is
 * constructed.\n
 *   If a 16 Bit integer type is used to implement the link indexes for the queue elements,
 * it can happen that the specified capacity of the queue is not realizable. The function
 * returns zero in this case.
 *   @param maxNoStdElements
 * The queue implementation imposes a fixed maximum size of the queue. The size is
 * specified in terms of how many elements of given \a size would fit into the queue. At
 * run-time, stored elements can have arbitrary sizes so that no statement is possible
 * about the storable number.\n
 *   Rationale: Using a typical standard element size plus a number of those elements as
 * size specification supports the still most relevant use cases with elements of identical
 * size.\n
 *   A queue size of zero is considered an error in the client code. This is caught by
 * assertion and zero is returned. \a maxNoStdElements * \a sizeOfStdElement needs to be
 * greater than zero.
 *   @param sizeOfStdElement
 * The size of a standard element, which should be storable \a maxNoStdElements times in
 * the queue. This size is just used for specification of the queue's capacity but has no
 * meaning at run-time any more.
 *   @remark
 * Caution, the implementation is not made safe against overflows on systems, where type
 * unsigned int is less than 32 Bit. On such systems, you must not rely on the function
 * return value but carefully double-check that the size of the ring buffer doesn't exceed
 * the 64 kByte limit. Actually, this is a bit theoretic as such systems won't ever have so
 * much RAM that this constraint would be relevant.
 *   @remark
 * The function operates without type information but needs to form a list of
 * elements. To safely do so it needs to anticipate the alignment required for such an
 * element. This alignment will later be applied to all contained elements, regardless of
 * their individual size.\n
 *   Usually this is the alignment of the largest element type if it are primitive types or
 * the alignment of the largest field in any of the elements if it are structs.\n
 *   The required alignment usually is a platform dependent constant and not an application
 * dependent run-time argument. Therefore, it is supplied as macro #ALIGN_OF_PAYLOAD, which
 * is part of the compile-time configuration data of this module. You should double-check
 * the setting for your particular platform.
 *   @remark
 * The memory chunk required by the constructor does not only need to have the right
 * minimum size but, secondary, it needs to have the right alignment, which is specified at
 * compile-time using macro #ALIGN_OF_PAYLOAD.
 *   @see vsq_createQueueTail()
 */
unsigned int vsq_getSizeOfQueueTail( unsigned int maxNoStdElements
                                   , unsigned int sizeOfStdElement
                                   )
{
    unsigned int size = 0;
    if(maxNoStdElements > 0u  &&  sizeOfStdElement > 0u)
    {
        size = byteOffsetOfRingBuffer()
               + calculateSizeOfRingBuffer(maxNoStdElements, sizeOfStdElement);

        /* For 16 Bit index values: Check if the ring buffer fits into an array of maximum
           64 kByte.
             Note, we need to disable the warning "type-limits" for the next statement.
           Justification: If we configure with our special integer types (atomic and for
           array indexes) as unsigned int then the condition reduce to an always true
           expression, which the compiler warns about. However, the true is what we want to
           see, so no worries about the warning. */
#if __GNUC__ >= 5
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif
        const unsigned int noBitsPerChar = 8u;
        if(sizeof(((const queueElement_t*)NULL)->idxNext) < sizeof(unsigned int)
           &&  size >= (1u << sizeof(((const queueElement_t*)NULL)->idxNext)*noBitsPerChar)
           ||  sizeof(uintatomic_t) < sizeof(unsigned int)
               &&  size >= (1u << sizeof(uintatomic_t)*noBitsPerChar)
          )
        {
            size = 0u;
        }
#if __GNUC__ >= 5
#pragma GCC diagnostic pop
#endif
    }
    VSQ_ASSERT(size > 0u);
    return size;

} /* End of vsq_getSizeOfQueueTail */




/**
 * Create a new, still unlinked, still unusable, queue head object. Prior to first use, the
 * head needs to be doubly linked with its communication peer, a queue tail object. See
 * vsq_linkQueueHeadWithTail() and vsq_linkQueueTailWithHead().
 *   @return
 * Get the pointer to the queue head object. Effectively, this is the same pointer as \a
 * pMemoryChunk but type casted for use as queue head. If the caller uses dynamic memory
 * management then he may free either his memory chunk or the returned pointer after use of
 * the queue.
 *   @param pMemoryChunk
 * The caller is in charge of allocating memory for the new queue head object. A memory
 * chunk of required size or bigger is passed in by reference. The required size needs to
 * queried with the other method vsq_getSizeOfQueueHead() prior to the call of this
 * constructor.\n
 *   Besides the right size, the memory chunk needs to have the right alignment, which is
 * specified at compile-time unsing macro #ALIGN_OF_PAYLOAD. If you use \a malloc to
 * allocate the memory chunk than this should normally be granted.\n
 *   The correct alignment is double-checked by assertion.
 *   @remark
 * For alignment considerations and constraints, please refer to vsq_getSizeOfQueueHead().
 *   @remark
 * There's no destructor for a queue head object. The caller is responsible for providing
 * the memory for the object and freeing this memory -- if applicable -- would be the only
 * operation to delete a queue head object after use.
 *   @see vsq_getSizeOfQueueHead()
 */
vsq_queueHead_t *vsq_createQueueHead(void * const pMemoryChunk)
{
#define CHECK_THIS                                                                          \
            ((ALIGN_OF_UINTATOMIC | (ALIGN_OF_UINTATOMIC-1))+1 == 2*ALIGN_OF_UINTATOMIC     \
             &&  (ALIGN_OF_HDR | (ALIGN_OF_HDR-1))+1 == 2*ALIGN_OF_HDR                      \
             &&  (ALIGN_OF_PAYLOAD | (ALIGN_OF_PAYLOAD-1))+1 == 2*ALIGN_OF_PAYLOAD          \
             &&  ALIGN_OF_PAYLOAD >= ALIGN_OF_HDR                                           \
             &&  sizeof(queueElement_t) % ALIGN_OF_PAYLOAD == 0                             \
             &&  offsetof(queueElement_t, payload) % ALIGN_OF_PAYLOAD == 0                  \
             &&  sizeof(unsigned int) >= sizeof(uintidx_t)                                  \
            )
#if defined(_STDC_VERSION_C17_C11)
    _Static_assert(CHECK_THIS, "Check configuration of module");
    _Static_assert(_Alignof(queueElement_t) == ALIGN_OF_HDR, "Check configuration of module");
#else
    VSQ_ASSERT(CHECK_THIS);
#endif
#undef CHECK_THIS

    vsq_queueHead_t * const pQueueHead = (vsq_queueHead_t*)pMemoryChunk;

    /* Check the alignment of the memory chunk for the queue head object. */
    #ifdef _STDC_VERSION_C17_C11
    # define ALIGN_OF_QUEUE_T _Alignof(vsq_queueHead_t)
    #elif defined(__GNUC__) && defined(__WIN64__)
    # define ALIGN_OF_QUEUE_T 8
    #elif defined(__GNUC__) && defined(__WIN32__)
    # define ALIGN_OF_QUEUE_T 4
    #elif defined(__AVR__)
    # define ALIGN_OF_QUEUE_T 1
    #elif defined(__arm__)
    # define ALIGN_OF_QUEUE_T 4
    #else
    # error Define the alignment of struct queue_t for your compiler/target
    #endif
    VSQ_ASSERT(isaligned((uintptr_t)pQueueHead, ALIGN_OF_QUEUE_T));
    #undef ALIGN_OF_QUEUE_T

    /* This queue head has no cooperating tail object yet. */
    pQueueHead->pTail = NULL;
    
    /* The tail and head of the queue and the read position into it all point initially to
       the same element. Which element it is is decided in the cooperating tail object. For
       now, we set the value preliminarily. The proper value will be set when linking head
       and tail. */
    pQueueHead->idxHead = 0u;

    return pQueueHead;

} /* End of vsq_createQueueHead */



/**
 * Create a new, still unlinked, still unusable, queue tail object. Prior to first use, the
 * tail needs to be doubly linked with its communication peer, a queue head object. See
 * vsq_linkQueueHeadWithTail() and vsq_linkQueueTailWithHead().
 *   @return
 * Get the pointer to the queue tail object. Effectively, this is the same pointer as \a
 * pMemoryChunk but type casted for use as queue. If the caller uses dynamic memory
 * management then he may free either his memory chunk or the returned pointer after use of
 * the queue.
 *   @param pMemoryChunk
 * The caller is in charge of allocating memory for the new queue object. A memory chunk of
 * required size or bigger is passed in by reference. The required size needs to queried
 * with the other method vsq_getSizeOfQueueTail() prior to the call of this constructor.\n
 *   Besides the right size, the memory chunk needs to have the right alignment, which is
 * specified at compile-time unsing macro #ALIGN_OF_PAYLOAD. If you use \a malloc to
 * allocate the memory chunk than this should normally be granted.\n
 *   The correct alignment is double-checked by assertion.
 *   @param maxNoStdElements
 * The queue implementation imposes a fixed maximum size of the queue. The size is
 * specified in terms of how many elements of given size \a would fit into the queue. At
 * run-time, stored elements can have arbitrary sizes so that no statement is possible
 * about the storable number.\n
 *   Rationale: Using a typical standard element size plus a number of those elements as
 * size specification supports the still most relevant use cases with elements of identical
 * size.\n
 *   A queue size of zero is considered an error in the client code. This is caught by
 * assertion and NULL is returned. \a maxNoStdElements * \a sizeOfStdElement needs to be
 * greater than zero.
 *   @param sizeOfStdElement
 * The size of a standard element, which should be storable \a maxNoStdElements times in
 * the queue. This size is just used for specification of the queue's capacity but has no
 * meaning at run-time any more.
 *   @remark
 * For alignment considerations and constraints, please refer to vsq_getSizeOfQueueTail().
 *   @remark
 * There's no destructor for a queue object. The caller is responsible for providing the
 * memory for the object and freeing this memory -- if applicable -- would be the only
 * operation to delete a queue tail object after use.
 *   @see vsq_getSizeOfQueueTail()
 */
vsq_queueTail_t *vsq_createQueueTail( void *pMemoryChunk
                                    , unsigned int maxNoStdElements
                                    , unsigned int sizeOfStdElement
                                    )
{
#define CHECK_THIS                                                                          \
            ((ALIGN_OF_UINTATOMIC | (ALIGN_OF_UINTATOMIC-1))+1 == 2*ALIGN_OF_UINTATOMIC     \
             &&  (ALIGN_OF_HDR | (ALIGN_OF_HDR-1))+1 == 2*ALIGN_OF_HDR                      \
             &&  (ALIGN_OF_PAYLOAD | (ALIGN_OF_PAYLOAD-1))+1 == 2*ALIGN_OF_PAYLOAD          \
             &&  ALIGN_OF_PAYLOAD >= ALIGN_OF_HDR                                           \
             &&  sizeof(queueElement_t) % ALIGN_OF_PAYLOAD == 0                             \
             &&  offsetof(queueElement_t, payload) % ALIGN_OF_PAYLOAD == 0                  \
             &&  sizeof(unsigned int) >= sizeof(uintidx_t)                                  \
            )
#if defined(_STDC_VERSION_C17_C11)
    _Static_assert(CHECK_THIS, "Check configuration of module");
    _Static_assert(_Alignof(queueElement_t) == ALIGN_OF_HDR, "Check configuration of module");
#else
    VSQ_ASSERT(CHECK_THIS);
#endif
#undef CHECK_THIS

    /* A queue with zero capacity is useless and surely a mistake in the client code. */
    if(maxNoStdElements == 0  ||  sizeOfStdElement == 0)
    {
        VSQ_ASSERT(false);
        return NULL;
    }

    vsq_queueTail_t * const pQueueTail = (vsq_queueTail_t*)pMemoryChunk;

    /* Check the alignment of the memory chunk for the queue object. */
    #ifdef _STDC_VERSION_C17_C11
    # define ALIGN_OF_QUEUE_T _Alignof(vsq_queueTail_t)
    #elif defined(__GNUC__) && defined(__WIN64__)
    # define ALIGN_OF_QUEUE_T 8
    #elif defined(__GNUC__) && defined(__WIN32__)
    # define ALIGN_OF_QUEUE_T 4
    #elif defined(__AVR__)
    # define ALIGN_OF_QUEUE_T 1
    #elif defined(__arm__)
    # define ALIGN_OF_QUEUE_T 4
    #else
    # error Define the alignment of struct queue_t for your compiler/target
    #endif
    VSQ_ASSERT(isaligned((uintptr_t)pQueueTail, ALIGN_OF_QUEUE_T));
    #undef ALIGN_OF_QUEUE_T

    /* This queue tail has no cooperating head object yet. */
    pQueueTail->pHead = NULL;
    
    /* An element consists of a header, which makes the link to the next element, and the
       user provided payload. */
    pQueueTail->sizeOfRingBuffer = calculateSizeOfRingBuffer( maxNoStdElements
                                                            , sizeOfStdElement
                                                            );
    pQueueTail->ringBuffer = (void*)((char*)pMemoryChunk + byteOffsetOfRingBuffer());
    VSQ_ASSERT(isaligned((uintptr_t)pQueueTail->ringBuffer, ALIGN_OF_PAYLOAD));
    VSQ_ASSERT((uintptr_t)pQueueTail
               + vsq_getSizeOfQueueTail(maxNoStdElements, sizeOfStdElement)
               == (uintptr_t)pQueueTail->ringBuffer + pQueueTail->sizeOfRingBuffer
              );
    //memset(pQueueTail->ringBuffer, /* char */ 0, /* len */ pQueueTail->sizeOfRingBuffer);

    /* The head and tail of the queue and the read position into it all point initially to
       the same element.
         Where to place it matters with respect to a common use case of queues. If the
       queues is solely used with elements of always same size (and this size had been
       specified at queue creation time) then the initial element should be put at the very
       end of the ring buffer space; only then it will be possible to fill the buffer
       entirely without fragmentation and as many elements will fit as had been specified
       at creation time. */
    pQueueTail->idxTail = pQueueTail->sizeOfRingBuffer - sizeof(queueElement_t);

    /* The element, which is initially owned by the consumer, is empty. Its link points to
       first element behind the one, which will be written by the first producer activity. */
    const unsigned int idxStartOfSuccessor = (pQueueTail->idxTail + sizeof(queueElement_t))
                                             % pQueueTail->sizeOfRingBuffer;
    setLinkPtrOfElementAt( pQueueTail
                         , /* idxStartOfElement */ pQueueTail->idxTail
                         , idxStartOfSuccessor
                         );

    pQueueTail->idxNewAllocatedTail = UINT_MAX;
#if VSQ_SUPPORT_MEMORY_PROTECTION == 1
    pQueueTail->isHeadCorrupted = false;
#endif
#if VSQ_SUPPORT_MEMORY_PROTECTION == 1  ||  VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
    pQueueTail->idxHeadCopy = pQueueTail->idxTail;
#endif
#if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
    pQueueTail->usage = 0;
    pQueueTail->maxUsage = 0;
    pQueueTail->maxUsageInByte = 0;
#endif

    return pQueueTail;

} /* End of vsq_createQueueTail */



/**
 * The intended queue's head and tail objects are created independently. Because of the
 * separation of memories of producer and consumer of the queued data, this will typically
 * be done independently and by distinct processes and the two objects don't know yet about
 * one another. They can cooperate only after being mutually linked with one another. The
 * linkage is done in two steps and after creation of both queue ends: This API allows to
 * update the link in the head object and can thus be used by the same process that
 * created the head object and the counterpart vsq_linkQueueTailWithHead() will do the same
 * for the tail object and from another process.
 *   @param pTheQueuesHead
 * The newly created queue head object, which is now linked to its tail.
 *   @param pTheQueuesTail
 * This is the tail object, * \a pTheQueuesHead is going to cooperate with.
 */
void vsq_linkQueueHeadWithTail( vsq_queueHead_t * const pTheQueuesHead
                              , const vsq_queueTail_t * const pTheQueuesTail
                              )
{
#if VSQ_SUPPORT_MEMORY_PROTECTION == 0
    VSQ_ASSERT(pTheQueuesHead->pTail == NULL);
#endif
    pTheQueuesHead->pTail = pTheQueuesTail;
    
    /* The tail and head of the queue and the read position into it all point initially to
       the same element. Which element it is has been decided in the cooperating tail
       object. We adopt that value. */
    pTheQueuesHead->idxHead = pTheQueuesTail->idxTail;

/// @todo Do we need a memory barrier somewhere here? And in the counterpart?

} /* vsq_linkQueueHeadWithTail */
                              


/**
 * The intended queue's head and tail objects are created independently. Because of the
 * separation of memories of producer and consumer of the queued data, this will typically
 * be done independently and by distinct processes and the two objects don't know yet about
 * one another. They can cooperate only after being mutually linked with one another. The
 * linkage is done in two steps and after creation of both queue ends: This API allows to
 * update the link in the tail object and can thus be used by the same process that
 * created the tail object and the counterpart vsq_linkQueueHeadWithTail() will do the same
 * for the head object and from another process.
 *   @param pTheQueuesTail
 * The newly created queue tail object, which is now linked to its head.
 *   @param pTheQueuesHead
 * This is the head object, * \a pTheQueuesTail is going to cooperate with.
 */
void vsq_linkQueueTailWithHead( vsq_queueTail_t * const pTheQueuesTail
                              , const vsq_queueHead_t * const pTheQueuesHead
                              )
{
    VSQ_ASSERT(pTheQueuesTail->pHead == NULL);
    pTheQueuesTail->pHead = pTheQueuesHead;

} /* vsq_linkQueueTailWithHead */
                              


/**
 * Append a new element to the tail of the queue.
 *   @return
 * The operation can fail; the queue is implemented with a pre-determined maximum size and
 * it can be currently full. Get \a true if the operation succeeds and \a false in case of
 * a currently full queue.\n
 *   The elements themselves have a flexible size. The function will return \a false if the
 * caller tries to write more bytes than currently fit into the queue.
 *   @param pQueueTail
 * The queue object to write to by reference.
 *   @param pData
 * The pointer to the payload data of the appended element. This is an anonymous byte
 * sequence to this method. memcpy is used to copy the data into the queue, which imposes
 * no alignment requirements on the data.
 *   @param noBytes
 * The number of bytes to write.\n
 *   No data will be copied to the queue if the function returns \a false.\n
 *   Note, it is valid to append an empty element. The related later call of
 * vsq_readFromHead() will return a non-NULL data pointer in combination with a number of
 * zero bytes.
 *   @see vsq_allocTailElement()
 *   @see vsq_readFromHead()
 */
bool vsq_writeToTail(vsq_queueTail_t * const pQueueTail, const void *pData, unsigned int noBytes)
{
    unsigned int idxNewTail;
    void *pFreeElem = allocTailElement(pQueueTail, &idxNewTail, noBytes);

    if(pFreeElem != NULL)
    {
        memcpy(pFreeElem, pData, noBytes);

        /* Notify the new element to the consumer and update the statistics of used
           elements. */
        postTailElement(pQueueTail, idxNewTail);

        return true;
    }
    else
        return false;

} /* End of vsq_writeToTail */



/**
 * Check if the queue has currently room to append another element to the tail and return the
 * available element in case.\n
 *   This method, together with the other method vsq_postTailElement(), is an alternative
 * API to write to the end of the queue. If vsq_allocTailElement() returns a non NULL
 * pointer then the caller can take any time to fill the queue element the return value
 * points to without fearing any race conditions. After having the element filled he will
 * use \a vsq_postTailElement to submit the element. From now on the element will be
 * visible to the consumer at the end of the queue.\n
 *   Using this API in contrast to vsq_writeToTail() can save a local copy of the produced
 * data in the producers implementation.\n
 *   The producer APIs to access the tail of the queue are not race condition free. A call
 * of \a vsq_writeToTail must either\n
 *   - return before the next call of the same method or\n
 *   - return before the invocation of \a vsq_allocTailElement or\n
 *   - be initiated after return from \a vsq_postTailElement.
 *
 * This means for a single producer context, that it can alternatingly use \a
 * vsq_writeToTail and the pair of \a vsq_allocTailElement and \a vsq_postTailElement. For
 * concurrent producer contexts it imposes the need for the implementation of mutual
 * exclusion code at the caller's side.
 *   @return
 * Get either the next available ring buffer element by reference or NULL if the queue is
 * currently full.\n
 *   The returned pointer is aligned as had been specified at compile-time using macro
 * #ALIGN_OF_PAYLOAD. The returned pointer can be safely casted to the element type and
 * access to the element (or its fields in case of a struct) can be done through this
 * pointer. There is no time limit in keeping the pointer (i.e., until data submission with
 * \a vsq_postTailElement) and using the pointer can avoid the need for an additional local
 * copy of the data during data production time.
 *   @param pQueueTail
 * The queue object by reference.
 *   @param sizeOfPayload
 * The size of the payload of the appended element in Byte.
 *   @remark
 * The calls of \a vsq_allocTailElement and \a vsq_postTailElement need to be done strictly
 * alternatingly. It is not possible to reserve several elements by multiple calls of the
 * former method and to submit them later by the same number of calls of the latter method.
 *   @remark
 * It is possible to use this method prior to \a vsq_writeToTail to query if the queue is
 * currently full and to avoid a negative return value of that function. It's however
 * disencouraged to do so. There is a little useless computation overhead in doing so and,
 * more important, the pair of \a vsq_allocTailElement and \a vsq_writeToTail is not race
 * condition free; a queue element could become free between the two calls -- the strategy
 * would be too conservative.
 */
void *vsq_allocTailElement(vsq_queueTail_t * const pQueueTail, unsigned int sizeOfPayload)
{
    VSQ_ASSERT(pQueueTail->idxNewAllocatedTail == UINT_MAX);
    return allocTailElement(pQueueTail, &pQueueTail->idxNewAllocatedTail, sizeOfPayload);

} /* End of vsq_allocTailElement */




/**
 * Submit a queue element, which had been allocated with vsq_allocTailElement().\n
 *   From now on, the element is in the queue and visible to the consumer. The pointer,
 * which had been got from \a vsq_allocTailElement is invalid and must no longer be used.\n
 *   Please, find more details of using this API in the description of the counterpart
 * method \a vsq_allocTailElement.
 *   @param pQueueTail
 * The queue object, where the submitted element had been allocated.
 *   @see void *vsq_allocTailElement()
 */
void vsq_postTailElement(vsq_queueTail_t * const pQueueTail)
{
    VSQ_ASSERT(pQueueTail->idxNewAllocatedTail != UINT_MAX);
    postTailElement(pQueueTail, pQueueTail->idxNewAllocatedTail);
#ifdef DEBUG
    pQueueTail->idxNewAllocatedTail = UINT_MAX;
#endif
} /* End of vsq_postTailElement */




/**
 * Read a meanwhile receivced new element from the head of the queue.
 *   @return
 * Get the pointer to the newly received element if a new element has arrived. \a NULL is
 * returned if no new element has been received since the previous invocation of this
 * method.\n
 *   The element, which is returned by reference is from now on owned by the data consumer,
 * i.e., the caller of this method. It may use the pointer to read the data. The ownership
 * only ends by getting another pointer to another element with a future invocation of this
 * method. In particular, it does not end when a future call of this method returns \a
 * NULL. The access to the owned element is race condition free for the owner of the
 * pointer.\n
 *   The returned pointer is aligned as had been specified at compile-time using macro
 * #ALIGN_OF_PAYLOAD. The returned pointer can be safely casted to the element type and
 * access to the element (or its fields in case of a struct) can be done through this
 * pointer without the need for first copying the data.
 *   @param pQueueHead
 * The queue object to be read from by reference.
 *   @param pSizeOfPayload
 * The number of bytes, which are conveyed with the received element, is returned by
 * reference. It is the same value as had been provided to the related call of either
 * vsq_writeToTail() or vsq_allocTailElement().\n
 *   The value is set to zero if the function returns NULL.\n
 *   Note, queued elements of size zero are allowed and possible. In which case, the
 * value is set to zero, too; howeber, now the function won't return NULL.\n 
 *   @remark
 * The consumer API is not reentrant. It is not possible to let concurrent consumer
 * contexts read from the head of the queue. This holds even if the consumer code
 * implements synchronization code, which ensures mutual exclusion from this method. This
 * is because the method's effect persists after return from the method; the returned
 * element is reserved to the caller until the next method invocation.
 *   @see bool vsq_writeToTail()
 */
const void *vsq_readFromHead( vsq_queueHead_t * const pQueueHead
                            , unsigned int * const pSizeOfPayload
                            )
{
    const void *pReceivedElementsPayload;
    const unsigned int idxRead = pQueueHead->idxHead;
    const vsq_queueTail_t * const pMyTail = pQueueHead->pTail;
    if(idxRead != pMyTail->idxTail)
    {
        const unsigned int newIdxRead = getLinkPtrOfElementAt(pMyTail, idxRead);

        /* Here we are between the code that used the data from the element owned by the
           consumer so far and the notification that it is no longer used by the consumer.
           We put a full memory barrier to ensure that the execution of the data consuming
           code is surely completed before the notification can become visible to the
           producer. */
        MEMORY_BARRIER_FULL();
        pQueueHead->idxHead = newIdxRead;

        const queueElement_t * const pElem = getElementAt(pMyTail, newIdxRead);
        pReceivedElementsPayload = &pElem->payload[0];
        *pSizeOfPayload = pElem->sizeOfPayload;
    }
    else
    {
        pReceivedElementsPayload = NULL;
        *pSizeOfPayload = 0;
    }
    return pReceivedElementsPayload;

} /* End of vsq_readFromHead */




#if VSQ_SUPPORT_MEMORY_PROTECTION == 1
/**
 * On each queueing of an element, the sender process double-checks if the memories of the
 * receiver process are still valid (as far as the communication via this queue is
 * concerned). It sets a flag in case of not valid. Then the communication is broken until
 * the receiver is re-synchronized (see vsq_acknReSyncHead()). This method queries the
 * communication state.
 *   @return
 * Get \a false if communication is alright. If \a true is returned then no more elements
 * can be queued until the receiver has been re-synchronized.
 *   @param pQueueTail
 * The tail object of the queue by reference, to which the query relates.
 */
bool vsq_getIsCommunicationBroken(const vsq_queueTail_t * const pQueueTail)
{
    return pQueueTail->isHeadCorrupted;
    
} /* End of vsq_getIsCommunicationBroken */



/**
 * If the sender had detected and reported a broken communication situation due to
 * corrupted receiver memories then the queue operation is blocked also for the sender
 * until the receiver has been re-synchronized. This is done -- after general recover of
 * the receiver process -- by again calling method vsq_linkQueueHeadWithTail() from the
 * receiver process and acknowledging success to the sender.\n
 *   The complexity of re-synchronization is the asynchronity of sender and receiver and
 * their memory access rights. The entire mechanism is useful only in environments, where
 * the receiver process' memories cannot be written from the sender process. It'll always
 * be a matter of inter-process communication to complete the re-synchronization. This can
 * be implemented only in some platform specific external code:
 *   1. Receiver process needs to generally recover from its problems
 *   2. Receiver process needs to invoke method vsq_linkQueueHeadWithTail(). This requires
 * the address of the tail object - if it is lost due to the data corruption then the
 * sender process will have to provide it again
 *   3. Receiver process needs to notify completion of invocation of
 * vsq_linkQueueHeadWithTail() to the sender process. From this point in time on, it may
 * again check its queue head for newly received elements. Initially, there won't be any
 *   4. The sender process needs to call method vsq_acknReSyncHead() in order to
 * acknowledge the re-synchonization to the queue logic. From now on, the queue operation
 * is re-enabled for the sender. The next call of alloc/post or vsq_writeToTail() will
 * succeed again and it'll queue the first element the receiver will get again after
 * re-synchronization.
 *   @param pQueueTail
 * The tail object of the queue by reference, which is re-sychronized.
 */
void vsq_acknReSyncHead(vsq_queueTail_t * const pQueueTail)
{
    MEMORY_BARRIER_FULL();
    VSQ_ASSERT(pQueueTail->isHeadCorrupted
               &&  pQueueTail->idxHeadCopy == pQueueTail->idxTail
               &&  pQueueTail->pHead->idxHead == pQueueTail->idxTail
              );
    pQueueTail->isHeadCorrupted = false;
    
} /* End of vsq_reSyncHead */
#endif


#if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
/**
 * Get the maximum number of queued elements, which has been seen since creation of the
 * queue object.
 *   @return
 * Get the number of elements.
 *   @param pQueueTail
 * The tail object of the queue by reference, to which the query relates.
 *   @remark
 * The compilation of this API can be turned on/off by configuration switch
 * #VSQ_ENABLE_API_QUEUE_DIAGNOSTICS.
 *   @remark
 * This method my be called at any time from producer or conumer context.
 */
unsigned int vsq_getMaximumQueueUsage(const vsq_queueTail_t * const pQueueTail)
{
    const unsigned int maxNoQueued = pQueueTail->maxUsage;
    VSQ_ASSERT(maxNoQueued*sizeof(queueElement_t) <= pQueueTail->sizeOfRingBuffer);
    return maxNoQueued;

} /* End of vsq_getMaximumQueueUsage */
#endif



#if VSQ_ENABLE_API_QUEUE_DIAGNOSTICS == 1
/**
 * Get the maximum use of buffer memory, which has been seen since creation of the
 * queue object.\n
 *   Note, the variable element size implies, that the queue potentially can't make use of
 * all memory. This is even normal and not an extraordinary situation. Consequently, if the
 * reported memory consumption is less than the configured memory, it doesn't necessarily
 * mean the the queue was never full.
 *   @return
 * Get the number in Byte.
 *   @param pQueueTail
 * The queue object by reference, to which the query relates.
 *   @remark
 * The compilation of this API can be turned on/off by configuration switch
 * #VSQ_ENABLE_API_QUEUE_DIAGNOSTICS.
 *   @remark
 * This method my be called at any time from producer or conumer context.
 */
unsigned int vsq_getMaximumQueueUsageInByte(const vsq_queueTail_t * const pQueueTail)
{
    const unsigned int maxUsageInByte = pQueueTail->maxUsageInByte;
    VSQ_ASSERT(maxUsageInByte <= pQueueTail->sizeOfRingBuffer);
    return maxUsageInByte;

} /* End of vsq_getMaximumQueueUsageInByte */
#endif

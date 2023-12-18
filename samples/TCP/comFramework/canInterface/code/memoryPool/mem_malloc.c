/**
 * @file mem_malloc.c
 * The memory allocation unit, which is the basis of the concept of static, deterministic
 * memory allocation: A given chunk of memory of limited, known size is partitioned and
 * distributed on demand. The idea is most simple. Each caller gets the demanded piece of
 * memory until the initial chunk of memory is exhausted. There's no method to free
 * allocated memory again and therefore all typical heap problems with fragmentation and
 * undeterministic timing are strictly avoided. A deterministic run-time behavior of the
 * client code is ensured. The application, which uses this allocation needs of course be
 * aware of the concept. It must e.g. not permit to destroy objects or to re-initialize
 * some data structures. Instead it needs to implement concepts like one-time
 * initialization and object pools for reuse.
 *
 * Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   mem_createMemoryPool
 * Local functions
 *   mallocChunk
 *   getNbrOfAvailableBytes
 *   getNbrOfAllocatedChunks
 *   getNbrOfAllocatedBytes
 */

/*
 * Include files
 */

#include "mem_malloc.h"

#include <stdlib.h>
#include <stdio.h>

#include "ede_basicDefinitions.h"
#include "ede_eventDispatcherEngine.config.h"
#include "ede_externalInterfaces.h"


/*
 * Defines
 */

/* Filter none numeric and obviously wrong settings. */
#if (EDE_COMMON_MACHINE_ALIGNMENT) != 1u        \
    &&  (EDE_COMMON_MACHINE_ALIGNMENT) != 2u    \
    &&  (EDE_COMMON_MACHINE_ALIGNMENT) != 4u    \
    &&  (EDE_COMMON_MACHINE_ALIGNMENT) != 8u
# error EDE_COMMON_MACHINE_ALIGNMENT needs to be a power of two
#endif

/** Move a pointer upwards until it points to an address, which has the common machine
    alignment.
      @return The modified pointer is returned as char pointer.
      @param p The pointer to become aligned. */
#define ALIGN_PTR(p)    (char*)((uintptr_t)((char*)(p)+(EDE_COMMON_MACHINE_ALIGNMENT)-1u)   \
                                & ~((EDE_COMMON_MACHINE_ALIGNMENT)-1u)                      \
                               )

/*
 * Local type definitions
 */

/** A memory pool consists of a few pointers and counts, which describe the memory
    partitioning of the pool. */
typedef struct mem_memoryPool_t
{
    /** The pointer behind the end of the complete chunk of memory. */
    const char *pEndOfAllMemory;

    /** The pointer to the free upper part of the complete chunk of memory. */
    char *pNextChunk;

    /** A critical section object to apply if atomicity of method malloc() needs to be
        ensured. The object's methods enter() and leave() will be NULL if this doesn't
        matter. */
    mem_criticalSection_t mutualExclusionGuard;

#if MEM_DIAGNOSTIC_INTERFACE == 1
    /** The number of exhausted bytes of memory. */
    unsigned int noBytesAllocated;

    /** The number of chunks requested so far. */
    unsigned int noChunksAllocated;
#endif
} mem_memoryPool_t;


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
 * A chunk of memory is allocated in a given memory pool.
 *   @return
 * Get the pointer to the reserved chunk of memory of requested size. The address will
 * surely be aligned according to the common machine alignment, see configuration setting
 * #EDE_COMMON_MACHINE_ALIGNMENT.\n
 *   The function returns NULL if the complete available memory is exhausted.
 *   @param hInstance
 * The handle of the memory pool, which should deliver the requested memory.
 *   @param sizeOfChunk
 * The number of requested bytes.
 */
static void *mallocChunk( uintptr_t hInstance
                        , unsigned int sizeOfChunk
                        )
{
    /* Just an alias: Resolve the instance handle back into a pointer. */
    mem_memoryPool_t * const pMemPool = (mem_memoryPool_t*)hInstance;

    void (* const enter)(uintptr_t*) = pMemPool->mutualExclusionGuard.enter;
    if(enter != NULL)
        enter(&pMemPool->mutualExclusionGuard.hInstance);

    /* Simply return the subsequent block of bytes. */
    char *pChunk = pMemPool->pNextChunk;

    /* Move the next-pointer to see where the new chunk would end. */
    const char * const pEndChunkUnaligned = &pChunk[sizeOfChunk];

    if(pEndChunkUnaligned <= pMemPool->pEndOfAllMemory)
    {
        /* pChunk is valid to fulfill the request.
             Now re-align the next-pointer, which may make it point behind the available
           memory space - but this will matter only in the next call of this method. */
        pMemPool->pNextChunk = ALIGN_PTR(pEndChunkUnaligned);
#if MEM_DIAGNOSTIC_INTERFACE == 1
        ++ pMemPool->noChunksAllocated;
        pMemPool->noBytesAllocated += (unsigned int)(pMemPool->pNextChunk - pChunk);
#endif
    }
    else
    {
        /* The remaining memory is not sufficient for the requested chunk. Return NULL. */
        pChunk = NULL;
    }

    if(enter != NULL)
        pMemPool->mutualExclusionGuard.leave(&pMemPool->mutualExclusionGuard.hInstance);

    EDE_ASSERT(pChunk == ALIGN_PTR(pChunk));
    return (void*)pChunk;

} /* End of mallocChunk */



/**
 * Get the number of memory bytes left for allocation. A chunk successfully requested with
 * mem_malloc cannot exceed this size.
 *   @return
 * Get the number of bytes.
 *   @param hInstance
 * The handle of the memory pool, which the request relates to.
 */
static unsigned int getNbrOfAvailableBytes(uintptr_t hInstance)
{
    /* Just an alias: Resolve the instance handle back into a pointer. */
    const mem_memoryPool_t * const pMemPool = (const mem_memoryPool_t*)hInstance;

    /* Due to rounding for alignment the next pointer may point beyond the heap end. This
       is not a fault but just means zero bytes left. */
    if(pMemPool->pEndOfAllMemory >= pMemPool->pNextChunk)
        return (unsigned int)(pMemPool->pEndOfAllMemory - pMemPool->pNextChunk);
    else
        return 0u;

} /* End of getNbrOfAvailableBytes */



#if MEM_DIAGNOSTIC_INTERFACE == 1
#if 0
/**
 * Diagnostic interface: Get the number of memory chunks allocated so far.
 *   @return
 * Get the number.
 *   @param hInstance
 * The handle of the memory pool, which the request relates to.
 */
static unsigned int getNbrOfAllocatedChunks(uintptr_t hInstance)
{
    /* Just an alias: Resolve the instance handle back into a pointer. */
    const mem_memoryPool_t * const pMemPool = (const mem_memoryPool_t*)hInstance;

    return pMemPool->noChunksAllocated;

} /* End of getNbrOfAllocatedChunks */
#endif



/**
 * Diagnostic interface: Get the number of memory bytes allocated so far. Due to alignment
 * operations this can be more than the sum of all requested chunk sizes.
 *   @return
 * Get the number of bytes.
 *   @param hInstance
 * The handle of the memory pool, which the request relates to.
 */
static unsigned int getNbrOfAllocatedBytes(uintptr_t hInstance)
{
    /* Just an alias: Resolve the instance handle back into a pointer. */
    const mem_memoryPool_t * const pMemPool = (const mem_memoryPool_t*)hInstance;

    return pMemPool->noBytesAllocated;

} /* End of getNbrOfAllocatedBytes */

#endif /* MEM_DIAGNOSTIC_INTERFACE == 1 */



/**
 * Create a new memory pool from some given memory.
 *   @return
 * Get \a true if operation succeeded. If the function returns \a false then * \a
 * pNewMemPool will be unusable.\n
 *   A memory pool requires a minimum number of Bytes to host the administrative data. In
 * pathologic situations, where \a sizeOfPoolMemory promises only a few Byte, the function
 * may fail.\n
 *   The function will fail only in case of lack of memory or if a bad critical section
 * object \a mutualExclusionGuard is specified. Since all memory allocation is static and
 * deterministic an appropriate and recommended failure handling concept is to check the
 * return value by assertion only.
 *   @param pNewMemPool
 * The newly created object by reference. The caller has to provide the space for the new
 * object.
 *   @param pPoolMemory
 * The pointer to a chunk of memory, which is statically allocated, available and reserved
 * for the given memory pool during the entire application run-time. This chunk of memory
 * will be partitioned and made available to those data structures of the CAN interface,
 * which are associated with the given pool. The properties of this memory area will become
 * the properties of all the chunks of memory dealt out later by the new pool.
 *   @param sizeOfPoolMemory
 * The number of bytes of \a pPoolMemory.
 *   @param mutualExclusionGuard
 * If the same memory is partitioned and distributed to clients running in different task
 * (or interrupt) contexts then the entry into method mem_malloc() needs to be
 * serialized.\n
 *   If optional method enter() of \a mutualExclusionGuard is not \a NULL then it is
 * invoked before the actual operation of memory allocation to ensure atomicity of the
 * operation.\n
 *   Accordingly, if optional method leave() of \a mutualExclusionGuard is not \a NULL then
 * it is invoked after the actual operation of memory allocation. Note, it is not allowed
 * to pass an object, where enter() is \a NULL but leave() isn't \a NULL or vice versa.\n
 *   The specified guard object needs to be suitable to mutually exclude all contexts
 * competing for the given memory pool.\n
 *   In a single threaded environment or if the newly created memory pool object won't ever
 * be used in concurrent contexts one should pass an object with methods enter() and leave()
 * both being \a NULL.\n
 *   Note, the critical section object is copied by value into the newly created memory
 * pool. All of its memory is therefore owned by the owner of the pool. If the methods
 * write to or read from field \a hInstance then they need to be aware that they access
 * some memory owned by owner of the pool, which normally is the caller of the methods.
 *   @remark
 * The function writes (only) to the specified new pool memory. Therefore, it needs to be
 * called from the context, which owns the new pool or from a super-ordinated context,
 * which has write access to the pool-memory, too, e.g. the operating system.
 */
bool mem_createMemoryPool( ede_memoryPool_t * const pNewMemPool
                         , void *pPoolMemory
                         , unsigned int sizeOfPoolMemory
                         , mem_criticalSection_t mutualExclusionGuard
                         )
{
    void * const pEndOfAllMemory = &((char*)pPoolMemory)[sizeOfPoolMemory];
    void * const pAllMemory = ALIGN_PTR(pPoolMemory);
    void * const pNextChunk = ALIGN_PTR((char*)pAllMemory + sizeof(mem_memoryPool_t));
    if(pNextChunk >= pEndOfAllMemory)
        return false;

    mem_memoryPool_t * const pMemPool = (mem_memoryPool_t*)pAllMemory;
    pMemPool->pNextChunk = pNextChunk;
    pMemPool->pEndOfAllMemory = pEndOfAllMemory;
    
    if(mutualExclusionGuard.enter != NULL  &&  mutualExclusionGuard.leave == NULL
       ||  mutualExclusionGuard.enter == NULL  &&  mutualExclusionGuard.leave != NULL
      )
    {
        return false;
    }
    
    pMemPool->mutualExclusionGuard = mutualExclusionGuard;

#if MEM_DIAGNOSTIC_INTERFACE == 1
    /* The number of exhausted bytes of memory needs to consider the loss due to alignment
       and administrative data. */
    pMemPool->noBytesAllocated = (unsigned int)((char*)pNextChunk - (char*)pPoolMemory);
    pMemPool->noChunksAllocated = 0;
#endif

    pNewMemPool->malloc = mallocChunk;
    pNewMemPool->getNbrOfAvailableBytes = getNbrOfAvailableBytes;
#if MEM_DIAGNOSTIC_INTERFACE == 1
    pNewMemPool->getNbrOfAllocatedBytes = getNbrOfAllocatedBytes;
#else
    pNewMemPool->getNbrOfAllocatedBytes = NULL;
#endif
    pNewMemPool->hInstance = (uintptr_t)pMemPool;

    return true;

} /* End of mem_createMemoryPool */




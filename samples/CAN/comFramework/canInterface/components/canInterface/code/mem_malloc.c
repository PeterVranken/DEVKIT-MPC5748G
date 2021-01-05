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
 * some data structures. Instead in needs to implement concpets like one-time
 * initialization and object pools for reuse.
 *
 * Copyright (C) 2015-2017 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   mem_malloc
 *   mem_getNbrOfAllocatedChunks
 * Local functions
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "cde_canDispatcherEngine.config.h"
#include "mem_malloc.h"


/*
 * Defines
 */

/* Filter none numeric and obviously wrong settings. */
#if (CDE_COMMON_MACHINE_ALIGNMENT) != 1     \
    &&  (CDE_COMMON_MACHINE_ALIGNMENT) != 2 \
    &&  (CDE_COMMON_MACHINE_ALIGNMENT) != 4 \
    &&  (CDE_COMMON_MACHINE_ALIGNMENT) != 8
# error CDE_COMMON_MACHINE_ALIGNMENT needs to be a power of two
#endif

/** Move a pointer upwards until it points to an address, which has the common machine
    alignment.
      @return The modified pointer is returned as char pointer.
      @param p The pointer to become aligned. */
#define ALIGN_PTR(p)    (char*)((uintptr_t)((char*)(p)+(CDE_COMMON_MACHINE_ALIGNMENT)-1u)   \
                                & ~((CDE_COMMON_MACHINE_ALIGNMENT)-1u)                      \
                               )

/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** The pointer to the reserved chunk of memory. */
static char *_pAllMemory = NULL;

/** The pointer behind the end of the complete chunk of memory. */
static char *_pEndOfAllMemory = NULL;

/** The pointer to the free upper part of the complete chunk of memory. */
static char *_pNextChunk = NULL;

#if MEM_DIAGNOSTIC_INTERFACE == 1
/** The number of exhausted bytes of memory. */
static unsigned int _noBytesAllocated = 0;

/** The number of chunks requested so far. */
static unsigned int _noChunksAllocated = 0;
#endif


/*
 * Function implementation
 */

/**
 * Initialize the module at application startup. The internal data structures are set up.\n
 *   This function must be called once and only once. Re-initialization is forbidden due to
 * the static, deterministic memory allocation concept.
 *   @return
 * \a true, if function succeeded, else \a false.\n
 *   The function will fail only in case of lack of memory. Since all memory allocation is
 * static and deterministic an appropriate and recommended failure handling concept is to
 * check the return value by assertion only. Anyhow, the system is not operational if this
 * function returns \a false.
 *   @param pAppMemory
 * The pointer to a chunk of memory, which is statically allocated, available and reserved
 * for the CAN interface during the entire application run-time. This chunk of memory will
 * be partitioned and made available to the data structures of the CAN interface.
 *   @param sizeOfAppMemory
 * The number of bytes of \a pAppMemory.
 *   @remark The call of this function has to be done in a race condition free environment,
 * prior to entering the multi-tasking phase of the application. Most platform will offer
 * an initialization task for this purpose.
 */

void mem_initModule(void *pAppMemory, unsigned int sizeOfAppMemory)
{
    _pAllMemory = ALIGN_PTR(pAppMemory);
    _pEndOfAllMemory = &((char*)pAppMemory)[sizeOfAppMemory];
    _pNextChunk = _pAllMemory;
    CDE_ASSERT((uintptr_t)_pAllMemory >= (uintptr_t)pAppMemory);

#if MEM_DIAGNOSTIC_INTERFACE == 1
    /* The number of exhausted bytes of memory needs to consider the loss due to alignment. */
    _noBytesAllocated = (unsigned int)(_pAllMemory - (char*)pAppMemory);
    _noChunksAllocated = 0;
#endif
} /* End of mem_initModule */



/**
 * A chunk of memory is allocated.
 *   @return
 * Get the pointer to the reserved chunk of memory of requested size. The address will
 * surely be aligned according to the common machine alignment, see configuration setting
 * #CDE_COMMON_MACHINE_ALIGNMENT.\n
 *   The function returns NULL if the complete available memory is exhausted.
 *   @param sizeOfChunk
 * The number of requested bytes.
 *   @param mutualExclusionOfClients
 * If the same memory is partitioned and distributed to clients running in different task
 * (or interrupt) contexts the entry into this method needs to be serialized. If \a
 * mutualExclusionOfClients is \a true then macros #cde_enterCriticalSection and
 * #cde_leaveCriticalSection are called to do this. One should pass \a false in a single
 * threaded environment.
 */

void *mem_malloc(unsigned int sizeOfChunk, boolean_t mutualExclusionOfClients)
{
    if(mutualExclusionOfClients)
    {
        cde_enterCriticalSection();
    }

    /* Simply return the subsequent block of bytes. */
    char *pChunk = _pNextChunk;

    /* Move and align the next-pointer but don't change it if the requested chunk reaches
       beyond the available memory. */
    _pNextChunk = &_pNextChunk[sizeOfChunk];
    if(_pNextChunk <= _pEndOfAllMemory)
    {
        /* pChunk is valid, now re-align the next-pointer. It may now point behind the
           available memory space but this will matter only in the next call of this
           method. */
        _pNextChunk = ALIGN_PTR(_pNextChunk);
#if MEM_DIAGNOSTIC_INTERFACE == 1
        ++ _noChunksAllocated;
        _noBytesAllocated += (unsigned int)(_pNextChunk - pChunk);
#endif
    }
    else
    {
        /* The remaining memory is not sufficient for the requested chunk. Undo the
           operation and return NULL. */
        _pNextChunk = pChunk;
        pChunk = NULL;
    }

    if(mutualExclusionOfClients)
    {
        cde_leaveCriticalSection();
    }

    CDE_ASSERT(pChunk == ALIGN_PTR(pChunk));
    return (void*)pChunk;

} /* End of mem_malloc */



/**
 * Get the number of memory bytes left for allocation. A chunk successfully requested with
 * mem_malloc cannot exceed this size.
 *   @return
 * Get the number of bytes.
 */

unsigned int mem_getNbrOfAvailableBytes(void)
{
    /* Due to rounding for alignment the next pointer may point beyond the heap end. This
       is not a fault but just means null bytes left. */
    if(_pEndOfAllMemory >= _pNextChunk)
        return (unsigned int)(_pEndOfAllMemory - _pNextChunk);
    else
        return 0;

} /* End of mem_getNbrOfAvailableBytes */



#if MEM_DIAGNOSTIC_INTERFACE == 1
/**
 * Diagnostic interface: Get the number of memory chunks allocated so far.
 *   @return
 * Get the number.
 */

unsigned int mem_getNbrOfAllocatedChunks(void)
{
    return _noChunksAllocated;

} /* End of mem_getNbrOfAllocatedChunks */




/**
 * Diagnostic interface: Get the number of memory bytes allocated so far. Due to alignment
 * operations this can be more than the sum of all requested chunk sizes.
 *   @return
 * Get the number of bytes.
 */

unsigned int mem_getNbrOfAllocatedBytes(void)
{
    return _noBytesAllocated;

} /* End of mem_getNbrOfAllocatedBytes */
#endif /* MEM_DIAGNOSTIC_INTERFACE == 1 */
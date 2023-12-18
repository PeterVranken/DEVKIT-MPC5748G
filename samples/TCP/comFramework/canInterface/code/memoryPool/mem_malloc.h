#ifndef MEM_MALLOC_INCLUDED
#define MEM_MALLOC_INCLUDED
/**
 * @file mem_malloc.h
 * Definition of global interface of module mem_malloc.c
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

/*
 * Include files
 */

#include "ede_basicDefinitions.h"
#include "ede_eventDispatcherEngine.config.h"
#include "ede_externalInterfaces.h"


/*
 * Defines
 */

/** A tiny API to get some information about memory usage can be conditionally compiled.
    Use this API during development phase to reduce the heap space to the minimum
    possible. */
#ifndef MEM_DIAGNOSTIC_INTERFACE
# ifdef DEBUG
#  define MEM_DIAGNOSTIC_INTERFACE  1
# else
#  define MEM_DIAGNOSTIC_INTERFACE  0
# endif
#endif

/**
 * A wrapper for the call of method malloc from the memory pool interface. Using this
 * wrapper lets the method invocation look much like a normal function call. In particular,
 * the explicit use of the instance handle is hidden.
 *   @return
 * Get the void * to the allocated memory.
 *   @param memPoolObj
 * The memory pool to use. A memory pool interface instance, which has been created and
 * returned by mem_createMemoryPool().
 *   @param sizeOfChunk
 * The number of bytes to be allocated in the memory pool.
 */
#define MEM_MALLOC(memPoolObj, sizeOfChunk) \
                                EDE_CALL_INTERFACE_VA_ARGS(memPoolObj, malloc, sizeOfChunk)


/**
 * A wrapper for the call of method getNbrOfAvailableBytes from the memory pool interface.
 * Using this wrapper lets the method invocation look much like a normal function call. In
 * particular, the explicit use of the instance handle is hidden.
 *   @return
 * Get the amount of still unused pool memory in Byte.
 *   @param memPoolObj
 * The memory pool to use. A memory pool interface instance, which has been created and
 * returned by mem_createMemoryPool().
 */
#define MEM_GET_NBR_OF_AVAILABLE_BYTES(memPoolObj) \
                                EDE_CALL_INTERFACE_NO_ARGS(memPoolObj, getNbrOfAvailableBytes)


#if MEM_DIAGNOSTIC_INTERFACE == 1
/**
 * A wrapper for the call of method getNbrOfAllocatedBytes from the memory pool interface.
 * Using this wrapper lets the method invocation look much like a normal function call. In
 * particular, the explicit use of the instance handle is hidden.
 *   @return
 * Get the number of already allocated bytes.
 *   @param memPoolObj
 * The memory pool to use. A memory pool interface instance, which has been created and
 * returned by mem_createMemoryPool().
 */
#define MEM_GET_NBR_OF_ALLOCATED_BYTES(memPoolObj) \
                                EDE_CALL_INTERFACE_NO_ARGS(memPoolObj, getNbrOfAllocatedBytes)
#endif

/** A critical section object without functionality. Does nothing. Can be applied to memory
    pools, which are not going to be used from competing contexts. */
#define MEM_VOID_CRITICAL_SECTION_OBJECT \
            (const mem_criticalSection_t){.enter = NULL, .leave = NULL, .hInstance = 0u}


/*
 * Global type definitions
 */

/** The interface of a critical section implementation. The instance of an implementation
    of such a CS provides mutual exclusion from the portion of code, which is enclosed in
    two calls of methods enter() and leave().
      @note The interface specification leaves it undecided what "mutual exclusion" means,
    or to whom it relates. Whether all contexts on a single core is meant or only a sub-set
    or if it relates to contexts on different cores depends on the use case of the CS and
    will be answered by the given implementation. */
typedef struct mem_criticalSection_t
{
    /**
     * Enter the critical section.\n
     *   If a context A returns from this method, it may be sure that no other competing
     * context B will be able to execute the same portion of code at the same time. (More
     * concrete: No other competing context B will be able to return from method enter()
     * before context A will have completed its call of other method leave().)
     *   @param hInstance
     * The handle of the critical section instance.\n
     *   The value of field \a hInstance from the same interface object will be passed in.
     */
    void (*enter)(uintptr_t *pHInstance);

    /**
     * Leave the critical section.\n
     *   After a context A returns from this method, the protected portion of code is
     * available again to all competing contexts B.
     *   @param hInstance
     * The handle of the critical section instance.\n
     *   The value of field \a hInstance from the same interface object will be passed in.
     */
    void (*leave)(uintptr_t *pHInstance);

    /** An actual implementation of the critical section may require some specific data.
        This field provides access to this data.\n
          This value is passed as first argument to the methods specified in this
        interface.\n
          The meaning of \a hInstance is transparent to the interface definition but it'll
        likely by either an index into an array of instances or a pointer to an instance or
        just a state variable if this suffices. The chosen type plus the fact that it is
        passed in to the methods by reference allows all of this. The method implementation
        will do the appropriate type cast. */
    uintptr_t hInstance;

} mem_criticalSection_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Create a new memory pool from some given memory. */
bool mem_createMemoryPool( ede_memoryPool_t * const pNewMemPool
                         , void *pPoolMemory
                         , unsigned int sizeOfPoolMemory
                         , mem_criticalSection_t mutualExclusionGuard
                         );

#endif  /* MEM_MALLOC_INCLUDED */

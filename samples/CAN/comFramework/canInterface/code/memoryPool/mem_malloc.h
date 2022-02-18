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
                                    EDE_CALL_INTERFACE(memPoolObj, malloc, sizeOfChunk)


/*
 * Global type definitions
 */

/** The argument type of any implementation of a mutual exclusion function: Do we enter or
    leave the critical section? */
typedef enum mem_criticalSectionDir_t
{
    /** Enter critical section. */
    mem_critSecDir_entry,

    /** Leave critical section. */
    mem_critSecDir_exit,

} mem_criticalSectionDir_t;

/** If memory allocation is done from competing contexts but from one and the same pool
    then some mutual exclusion is required to safely do the operation. This requires some
    external code, an implementation that is unknow to the memory pool implementation. Here
    is the interface definition. */
typedef void (*mem_fctCriticalSection_t)(mem_criticalSectionDir_t dir);

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
                         , mem_fctCriticalSection_t const mutualExclusionGuard
                         );

#endif  /* MEM_MALLOC_INCLUDED */

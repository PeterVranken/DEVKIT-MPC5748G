#ifndef MEM_MALLOC_INCLUDED
#define MEM_MALLOC_INCLUDED
/**
 * @file mem_malloc.h
 * Definition of global interface of module mem_malloc.c
 *
 * Copyright (C) 2015 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "stdlib.h"
#include "cde_canDispatcherEngine.config.h"

/*
 * Defines
 */

/** A tiny API to get some information about memory usage can be conditionally compiled.
    Use this API during development phase to reduce the heap space to the minimum
    possible. */ 
#ifndef MEM_DIAGNOSTIC_INTERFACE
# ifdef DEBUG
#  define MEM_DIAGNOSTIC_INTERFACE   1
# else
#  define MEM_DIAGNOSTIC_INTERFACE   0
# endif
#endif


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialize the module at application startup. The internal data structures are set up. */
void mem_initModule(void *pAppMemory, unsigned int sizeOfAppMemory);

/** A chunk of memory is allocated. */
void *mem_malloc(unsigned int sizeOfChunk, boolean_t mutualExclusionOfClients);

/** Get the number of memory bytes left for allocation. */
unsigned int mem_getNbrOfAvailableBytes(void);

#if MEM_DIAGNOSTIC_INTERFACE == 1
/** Diagnostic interface: Get the number of memory chunks allocated so far. */
unsigned int mem_getNbrOfAllocatedChunks(void);

/** Diagnostic interface: Get the number of memory bytes allocated so far. */
unsigned int mem_getNbrOfAllocatedBytes(void);
#endif /* MEM_DIAGNOSTIC_INTERFACE == 1 */

#endif  /* MEM_MALLOC_INCLUDED */

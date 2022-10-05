/**
 * @file main.c
 * Main function of the Windows demo application of the timer facilities of the event
 * dispatcher engine.
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
 *   main
 * Local functions
 *   addOsToEdeHandlePair
 *   mapOsFrameHandleToEdeIdx
 *   dispatcherDummyPort_readBuffer
 *   dispatcherDummyPort_freeBuffer
 */

/*
 * Include files
 */

#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "ede_eventDispatcherEngine.h"
#include "mem_malloc.h"
#include "tc0_testCase00.h"
#include "vsq_dispatcherPortInterface.h"


/*
 * Defines
 */

/** The size of the heap memory, which is statically allocated for the CAN interface. The
    value should be set as little as possible; if set too little then the application will
    abort with an assertion. This is safe due to the static, deterministic memory
    allocation concept: If no assertion fires in DEBUG compilation during development then
    it is for sure that the production code compilation won't see a lack of memory
    neither.
      @remark Consider to begin with a large value and then use the function \a
    mem_getNbrOfAllocatedChunks in DEBUG compilation in order to get the optimal setting
    for this define. */
#define SIZE_OF_HEAP_FOR_CAN_INTERFACE  8096u /* Byte */



/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** The simulation time. */
unsigned long main_tiSim = 0u;


/*
 * Function implementation
 */

/**
 * Add a new entry to the map of handle mappings: In this simple sample we don't have any
 * external event processing and the map won't ever be used. Adding an element to it is a
 * pure dummy, which returns success although it totally ignores all its input.
 *   @return
 * Get \a true, indication of no fault.
 *   @param hInstance
 * The handle of the map to use. (Each dispatcher has its own index space and uses a
 * dedicated map instance.)
 *   @param kindOfEvent
 * Kind of external event.
 *   @param senderHandleEvent
 * The identification of an external event.
 *   @param edeIdxEventSrc
 * The handle of the event as used in the dispatcher engine.
 *   @remark
 * This function is called during initialization of the dispatcher, which is done in a
 * race condition free, single threaded context. This function is called repeatedly for
 * each registered event source.
 */
static bool addOsToEdeHandlePair( uintptr_t hInstance ATTRIB_UNUSED
                                , ede_kindOfEvent_t kindOfEvent ATTRIB_UNUSED
                                , ede_senderHandleEvent_t senderHandleEvent ATTRIB_UNUSED
                                , unsigned int edeIdxEventSrc ATTRIB_UNUSED
                                )
{
    return true;
    
} /* addOsToEdeHandlePair */



/**
 * This function implements a map, which associates the externally defined handles of
 * external events to the indexes of the event source as used by the event dispatcher
 * engine (which span a linear, null based index). The map is required for the use of the
 * engine and during initialization time the engine provides the map entries.\n
 *   In this simple sample we don't have any external event processing and the map won't
 * ever be used. The function implementation is a dummy and all its input is ignored.
 *   @return
 * \a false. No mapping is implemented, so we never have a hit.
 *   @param hInstance
 * The handle of the map to use.
 *   @param pValue
 * The index of the event source as required by the event dispatcher engine is returned by
 * reference if the function returns \a true.
 *   @param kindOfEvent
 * Kind of external event. 
 *   @param senderHandleEvent
 * The external handle of the event.
 *   @param hDispatcher
 * The dispatcher engine using the given map instance.
 */
static bool mapOsFrameHandleToEdeIdx( uintptr_t hInstance ATTRIB_UNUSED
                                    , unsigned int * const pValue ATTRIB_UNUSED
                                    , ede_kindOfEvent_t kindOfEvent ATTRIB_UNUSED
                                    , ede_senderHandleEvent_t senderHandleEvent ATTRIB_UNUSED
                                    )
{
    /* In this particular sample, the map lookup is never used: We don't have any external
       event. */
    assert(false);
    return false;
    
} /* mapOsFrameHandleToEdeIdx */



/**
 * Try to read an event from the connection element.\n
 *   In this sample, we won't ever provide any received input event and consequently, the
 * function will never return any event.
 *   @return
 * The method returns NULL as there are no events to deliver in this dummy port
 * implementation.
 *   @param hInstance
 * Each receiver port has its own, dedicated connection element instance. This handle is
 * the identification of the port instance to use.
 *   @param pSizeOfPayload
 * The method will put the size of the payload of the returned event into * \a
 * pSizeOfPayload. The size is the number of bytes, which can be accessed through the
 * event's field \a dataAry[].
 */
static const ede_externalEvent_t *dispatcherDummyPort_readBuffer
                                            ( uintptr_t hInstance ATTRIB_UNUSED
                                            , unsigned int *pSizeOfPayload ATTRIB_UNUSED
                                            )
{
    return NULL;
}


/**
 * Return the eldest buffer, which had been fetched with dispatcherDummyPort_readBuffer()
 * and which had not been returned yet.\n
 *   In this sample, we won't ever provide any received input event and consequently, the
 * function does nothing.
 *   @param hInstance
 * Each receiver port has its own, dedicated connection element instance. This handle is
 * the identification of the port instance to use.
 */
static void dispatcherDummyPort_freeBuffer(uintptr_t hInstance ATTRIB_UNUSED)
{
}



/**
 * The main function of this C project.
 *   @return
 * \a 0 if application succeeded or -1 if it reported an error.
 *   @param argc
 * The number of program arguments.
 *   @param argv
 * An array of \a argc constant strings, each a program argument. An additional array entry
 * NULL indicates the end of the list.
 */

signed int main( signed int argc ATTRIB_UNUSED
               , char *argv[] ATTRIB_UNUSED
               )
{
    const char * const greeting =
           "-----------------------------------------------------------------------------\n"
           " " MAIN_APP_GREETING "\n"
           " Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)\n"
           " This is free software; see the source for copying conditions. There is NO\n"
           " warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
           "-----------------------------------------------------------------------------";

    /* Print the greeting. */
    printf("%s\n", greeting);

    /* Test: Create dispatcher engine and register a few events in order to get the first
       root callbacks, which initiate and perform the tests. */

    /* Create our only memory pool. */
    static char heapMemoryForCanInterface[SIZE_OF_HEAP_FOR_CAN_INTERFACE];
    const mem_criticalSection_t mutualExclusionGuard = { .enter = NULL
                                                       , .leave = NULL
                                                       , .hInstance = 0u
                                                       };
    ede_memoryPool_t memPool = EDE_INVALID_MEMORY_POOL;
    bool success ATTRIB_DBG_ONLY = mem_createMemoryPool( &memPool
                                                       , &heapMemoryForCanInterface[0u]
                                                       , sizeof(heapMemoryForCanInterface)
                                                       , mutualExclusionGuard
                                                       );
    assert(success);
    
    /* Create a dummy input port for the dispatcher. It'll never return any (external)
       event. */
    ede_eventReceiverPort_t portDispatcher = 
    {
        .readBuffer = dispatcherDummyPort_readBuffer,
        .freeBuffer = dispatcherDummyPort_freeBuffer,
        .hInstance = 0u,
        .providesDataByReference = false,
    };

    /* Create the required dispatcher systems. */
    ede_handleDispatcherSystem_t hDispatcherSystem = EDE_INVALID_DISPATCHER_SYSTEM_HANDLE;
    success = ede_createDispatcherSystem( &hDispatcherSystem
                                        , /* noEventDispatcherEngines */ 1u
                                        , /* maxNoEventSourcesExt */ 0u
                                        , /* maxNoEventSourcesInt */ 1u
                                        , &memPool
                                        );
    assert(!success  || hDispatcherSystem != EDE_INVALID_DISPATCHER_SYSTEM_HANDLE);
    

    /* Create the required dispatchers. */
    ede_mapSenderEvHandleToIdx_t const handleMap =
    {
        .addKeyValuePair = addOsToEdeHandlePair,
        .getValue = mapOsFrameHandleToEdeIdx,
        .hInstance = 0u,
    };
    success = ede_createDispatcher( hDispatcherSystem
                                  , /* idxDispatcher */ 0u
                                  , MAIN_TI_TICK_DISPATCHER_0
                                  , /* portAry */ &portDispatcher
                                  , /* noPorts */ 1u
                                  , /* mapSdrEvHdlToEdeEvSrcIdx */ handleMap
                                  );
    assert(success);
    
    /* Register a dummy event source - just to start the test procedure. */
    unsigned int idxEvSrc ATTRIB_UNUSED =
                            ede_registerInternalEventSource( hDispatcherSystem
                                                           , /* idxDispatcher */ 0u
                                                           , /* callback */ tc0_initTest
                                                           , /* refEventSourceData */ 0u
                                                           );
    assert(idxEvSrc == 0u);

    /* Call the step function of the dispatcher engine. */
    while(tc0_endOfTest == false)
    {
        ede_dispatcherMain(hDispatcherSystem, /* idxDispatcher */ 0u);
        main_tiSim += MAIN_TI_TICK_DISPATCHER_0;
    }

    /* Give feedback about memory consumption. */
    if(memPool.getNbrOfAllocatedBytes != NULL  &&  memPool.getNbrOfAvailableBytes != NULL)
    {
        printf( "main: "
                "Consumed memory of heap: %u Byte, remaining heap memory:"
                " %u Byte\n"
              , memPool.getNbrOfAllocatedBytes(memPool.hInstance)
              , memPool.getNbrOfAvailableBytes(memPool.hInstance) 
              );
        if(memPool.getNbrOfAllocatedBytes(memPool.hInstance) < SIZE_OF_HEAP_FOR_CAN_INTERFACE)
        {
            printf( "main: "
                    "Size of heap could be decreased by %u Byte\n"
                  , SIZE_OF_HEAP_FOR_CAN_INTERFACE
                    - memPool.getNbrOfAllocatedBytes(memPool.hInstance)
                  );
        }
    }

    return 0;

} /* End of main */

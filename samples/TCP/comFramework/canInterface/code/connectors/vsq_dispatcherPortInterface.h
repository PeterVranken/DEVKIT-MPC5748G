#ifndef VSQ_DISPATCHERPORTINTERFACE_INCLUDED
#define VSQ_DISPATCHERPORTINTERFACE_INCLUDED
/**
 * @file vsq_dispatcherPortInterface.h
 * Definition of global interface of module vsq_dispatcherPortInterface.c
 *
 * Copyright (C) 2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "ede_externalInterfaces.h"

/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Create a thread-safe event queue and return it as pair of dispatcher engine ports. */
bool vsq_createEventQueue( ede_eventReceiverPort_t *pPortHead
                         , ede_eventSenderPort_t *pPortTail
                         , unsigned int maxQueueLength
                         , unsigned int maxElementSize
                         , ede_memoryPool_t *pMemPoolHead
                         , ede_memoryPool_t *pMemPoolTail
                         );


/** Create the head of a thread-safe event queue and return it as dispatcher input port. */
bool vsq_createEventQueueHead( ede_eventReceiverPort_t *pPortHead
                             , ede_memoryPool_t * const pMemPoolHead
                             );
                             
/** Create the tail of a thread-safe event queue and return it as sender output port. */
bool vsq_createEventQueueTail( ede_eventSenderPort_t *pPortTail
                             , unsigned int maxQueueLength
                             , unsigned int maxPayloadSize
                             , ede_memoryPool_t * const pMemPoolTail
                             );

/** Connect the tail of a queue with its head. */
void vsq_linkEventQueueTailWithHead( const ede_eventSenderPort_t portTail
                                   , const ede_eventReceiverPort_t portHead
                                   );
                                   
/** Connect the head of a queue with its tail. */
void vsq_linkEventQueueHeadWithTail( const ede_eventReceiverPort_t portHead
                                   , const ede_eventSenderPort_t portTail
                                   );

/*
 * Global inline functions
 */


#endif  /* VSQ_DISPATCHERPORTINTERFACE_INCLUDED */

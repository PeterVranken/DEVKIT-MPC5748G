#ifndef EDE_EVENTSENDER_INCLUDED
#define EDE_EVENTSENDER_INCLUDED
/**
 * @file ede_eventSender.h
 * Definition of global interface of module ede_eventSender.c
 *
 * Copyright (C) 2021-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "ede_eventDispatcherEngine.h"
#include "ede_externalInterfaces.h"

/*
 * Defines
 */

/** The invalid event sender handle. */
#define EDE_INVALID_SENDER_HANDLE   NULL


/*
 * Global type definitions
 */

/** The handle or identification of a sender object. */
typedef struct ede_eventSender_t *ede_handleSender_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Create an event sender object. */
bool ede_createSender( ede_handleSender_t * const pHandleSender
                     , ede_eventSenderPort_t portAry[]
                     , unsigned int noPorts
                     , const ede_mapSenderEvHandleToIdx_t *pMapSenderEvHandleToPortIndex
                     , ede_memoryPool_t * const pMemPoolSender
                     );

/** An event is posted. It is put into the associated dispatcher's event queue. */
bool ede_postEvent( ede_handleSender_t hSender
                  , ede_kindOfEvent_t kindOfEvent
                  , ede_senderHandleEvent_t senderHandleEvent
                  , const void *pData
                  , unsigned int sizeOfData
                  );

/** Send an event via a specific port. */
bool ede_postEventToPort( ede_handleSender_t hSender
                        , unsigned int idxPort
                        , ede_kindOfEvent_t kindOfEvent
                        , ede_senderHandleEvent_t senderHandleEvent
                        , const void *pData
                        , unsigned int sizeOfData
                        );
                        
/** Get the number of recorded port-is-blocked events. For use from any context. */
ede_atomicUnsignedInt_t ede_getNoSenderPortBlockedEvents( ede_handleSender_t hSender
                                                        , unsigned int idxPort
                                                        );

/*
 * Global inline functions
 */


#endif  /* EDE_EVENTSENDER_INCLUDED */

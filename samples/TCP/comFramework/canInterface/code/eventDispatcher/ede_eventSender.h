#ifndef EDE_EVENTSENDER_INCLUDED
#define EDE_EVENTSENDER_INCLUDED
/**
 * @file ede_eventSender.h
 * Definition of global interface of module ede_eventSender.c
 *
 * Copyright (C) 2021-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
                     , const ede_eventSenderPort_t portAry[]
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
                        
/** Find the port of a sender object, which is associated with an event to post. */
unsigned int ede_getPortIndex( ede_handleSender_t hSender
                             , ede_kindOfEvent_t kindOfEvent
                             , ede_senderHandleEvent_t senderHandleEvent
                             );
                             
/** Posting an event using the two-step approach: Request empty event object of needed size. */
void * ede_allocEventAtPort( ede_externalEvent_t ** ppEvent
                           , ede_handleSender_t hSender
                           , unsigned int idxPort
                           , unsigned int sizeOfData
                           );

/** Posting an event using the two-step approach: Submit the finalized event. */
void ede_submitEventToPort(ede_handleSender_t hSender, unsigned int idxPort);

/** Get the number of recorded port-is-blocked events. For use from any context. */
ede_atomicUnsignedInt_t ede_getNoSenderPortBlockedEvents( ede_handleSender_t hSender
                                                        , unsigned int idxPort
                                                        );

/*
 * Global inline functions
 */

/**
 * Helper for the two-step approach of posting an event: An event object as got from
 * ede_allocEventAtPort() has all undefined fields. After getting an event object with
 * ede_allocEventAtPort(), this function can be used to fill in the principal event
 * properties: kind and handle, which both together identify the event.\n
 *   Note, the remaining contents of the event, the event's payload data, is filled in via
 * the pointer returned by ede_allocEventAtPort(), too.
 *   @param pEvent
 * The event object, which had been got before from ede_allocEventAtPort(), is passed in by
 * reference.
 *   @param[in] kindOfEvent
 * The kind of event, which is writen into * \a pEvent. It is an enumeration, which is
 * meaningless to connector element and dispatcher engine.
 *   @param[in] senderHandleEvent
 * The event's handle as used (and issued) by the external integration code system. In the
 * case of CAN communication, this will , e.g., be the operating system's handle of a
 * registered CAN message.
 */
static inline void ede_setKindOfEvent( ede_externalEvent_t * const pEvent
                                     , ede_kindOfEvent_t kindOfEvent
                                     , ede_senderHandleEvent_t senderHandleEvent
                                     )
{
    pEvent->kindOfEvent = kindOfEvent;
    pEvent->senderHandleEvent = senderHandleEvent;

} /* ede_setKindOfEvent */

#endif  /* EDE_EVENTSENDER_INCLUDED */

#ifndef MHN_MAPOSFRAMEHANDLETOENGINEHANDLE_INCLUDED
#define MHN_MAPOSFRAMEHANDLETOENGINEHANDLE_INCLUDED
/**
 * @file mhn_mapOsFrameHandleToEngineHandle.h
 * Definition of global interface of module mhn_mapOsFrameHandleToEngineHandle.c
 *
 * Copyright (C) 2015-2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "types.h"
#include "ede_eventDispatcherEngine.h"
#include "cev_canEvents.h"

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

/** Initialze the module. All map instances are created initially empty. */
void mhn_initModule(void);

/** Assign a frame to the appropriate dispatcher. */
unsigned int mhn_assignFrameToDispatcher( cev_canId_t canId
                                        , uint16_t osHandleBus
                                        , ede_senderHandleEvent_t osHandleFrame
                                        , bool isInbound
                                        , signed int latencyTime
                                        );
                                        
/** Add another key, value pair to the handle map. */
bool mhn_addOsToEdeHandlePair( uintptr_t hInstance
                             , ede_kindOfEvent_t kindOfEvent
                             , ede_senderHandleEvent_t senderHandleEvent
                             , unsigned int idxEdeEventSrc
                             );
                                    
/** Map an operating system frame handle to the handle used in the CAN interface. */
bool mhn_mapOsFrameHandleToEdeIdx( uintptr_t hInstance
                                 , unsigned int * pIdxEdeEventSrc
                                 , ede_kindOfEvent_t kindOfEvent
                                 , ede_senderHandleEvent_t senderHandleEvent
                                 );

/** Add a key, value pair to the sender-side map, which directs CAN events to a dispatcher. */
bool mhn_addMapEntrySenderEvHandleToSenderPortIndex
                                        ( uintptr_t hInstance
                                        , unsigned int kindOfEvent
                                        , ede_senderHandleEvent_t senderHandleEvent
                                        , unsigned int idxPort
                                        );

/** Quere the map to see, which dispatcher to post an event to. */
bool mhn_mapSenderEvHandleToSenderPortIndex( uintptr_t hInstance
                                           , unsigned int * const pIdxPort
                                           , unsigned int kindOfEvent
                                           , ede_senderHandleEvent_t senderHandleEvent
                                           );

#endif  /* MHN_MAPOSFRAMEHANDLETOENGINEHANDLE_INCLUDED */

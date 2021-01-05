#ifndef MHN_MAPOSFRAMEHANDLETOENGINEHANDLE_INCLUDED
#define MHN_MAPOSFRAMEHANDLETOENGINEHANDLE_INCLUDED
/**
 * @file mhn_mapOsFrameHandleToEngineHandle.h
 * Definition of global interface of module mhn_mapOsFrameHandleToEngineHandle.c
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

#include "types.h"
#include "cde_canDispatcherEngine.h"


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

/** Assign a frame to the appropriate dispatcher. */
unsigned int mhn_assignFrameToDispatcher( uint32_t canId
                                        , uint16_t osHandleBus
                                        , cde_osHandleFrame_t osHandleFrame
                                        , boolean_t isInbound
                                        , signed int latencyTime
                                        );
                                        
/** Add a key, value pair to the map of handles. */
boolean_t mhn_addOsToCdeHandlePair( unsigned long canId
                                  , unsigned int idxBus
                                  , cde_osHandleFrame_t osHandleFrame
                                  , unsigned int cdeIdxFrame
                                  , boolean_t isInbound
                                  );
                                    
/** Map an operating system frame handle to the handle used in the CAN interface. */
boolean_t mhn_mapOsFrameHandleToCdeIdx( unsigned int *pCdeIdxFrame
                                      , unsigned int idxBus
                                      , cde_osHandleFrame_t osHandle
                                      );


#endif  /* MHN_MAPOSFRAMEHANDLETOENGINEHANDLE_INCLUDED */

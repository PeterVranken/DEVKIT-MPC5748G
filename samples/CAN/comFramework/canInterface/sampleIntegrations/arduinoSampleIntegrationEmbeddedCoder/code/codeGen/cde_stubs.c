/**
 * @file cde_stubs.c
 * This module contains a few functions, which where formerly available in the dispatcher
 * engine. Starting with revision 1.6, the dispatcher is a dispatcher of abstract events
 * and has no longer any CAN related APIs. However, it has the same data propagation
 * mechanisms and these can be applied to easily emulate the elder set of API functions. We
 * stick to the naming of the dispatcher engibne from the CAN interface <= 1.5.
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
/* Module interface
 *   cde_getCanId
 *   cde_getIdxFrame
 * Local functions
 */

/*
 * Include files
 */

#include "cde_stubs.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
 
/*
 * Function implementation
 */

/**
 * Get the CAN ID of a frame from a callback invoked by frame or timer event. If it is a
 * timer event then the operation relates to the parent frame of the timer.
 *   @return
 * The CAN ID.
 *   @param pContext
 * The dispatcher context this callback is invoked from.
 *   @remark
 * This function may be called from frame or timer callback. An assertion fires if this
 * function is invoked from a bus event's callback or from a timer's callback and the
 * timer's parent is not a frame.
 */
cde_canId_t cde_getCanId(const ede_callbackContext_t *pContext)
{
    /* Note, on Arduino, uintptr_t is a 16 Bit integer, so we can't use this implementation
       for extended CAN IDs. */
    const uintptr_t canId = ede_getEventSourceData(pContext);
    EDE_ASSERT((canId & ~0x7FFu) == 0u);
    return CDE_STD_CAN_ID(canId);

} /* End of cde_getCanId */

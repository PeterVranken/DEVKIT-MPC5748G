#ifndef CBK_CALLBACKS_DEFINED
#define CBK_CALLBACKS_DEFINED
/**
 * @file cbk_callbacks.h
 * Declaration of callbacks for the CAN interface engine for cluster arduinoSampleIntegrationEC.
 *
 * This file has been created with comFramework - codeGenerator version 1.10.6,
 * see http://sourceforge.net/projects/comframe/
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

#include "types.h"
#include "ede_eventDispatcherEngine.h"


/*
 * Defines
 */

 

/*
 * Type definitions
 */

 

/*
 * Data declarations
 */

 

/*
 * Function declarations
 */

/** Initialization of the interface: Register all affected frames. */
void cbk_initInterface();

#endif // !defined(CBK_CALLBACKS_DEFINED)
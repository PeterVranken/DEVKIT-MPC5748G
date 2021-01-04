#ifndef CMD_CANCOMMAND_INCLUDED
#define CMD_CANCOMMAND_INCLUDED
/**
 * @file cmd_canCommand.h
 * Definition of global interface of module cmd_canCommand.c
 *
 * Copyright (C) 2020-2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "typ_types.h"


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

/** Process a possible CAN related user command. */
bool cmd_parseCanCommand(unsigned int argC, const char *argV[]);


/** Callback for CAN stack: Display the signals, which we are currently listening to. */
void cmd_onReceiveMessage(unsigned int idxRxFr);

/*
 * Global inline functions
 */


#endif  /* CMD_CANCOMMAND_INCLUDED */

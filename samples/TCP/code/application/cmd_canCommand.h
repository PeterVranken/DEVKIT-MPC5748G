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

/** Size of listener: This is the maximum number of signals to listen to. The number should
    be kept little in order to not flood the console with output about received signals. */
#define CMD_MAX_NO_SIGNALS_TO_LISTEN_TO 10u


/*
 * Global type definitions
 */

/** Table entry of listener. It describes one signal to listen to. */
typedef struct cmd_listenerSigDesc_t
{
    /** Signal by reference into the global table \a cdt_canSignalAry of all signals in the
        CAN database. A value of UINT_MAX means table entry not in use. */
    unsigned int idxSignal;

    /** Time of adding signal to the listener. (The age of the signal is used to identify,
        which one to drop in advantage of a newly added if the list is full.) */
    unsigned int tiAdded;
    
} cmd_listenerSigDesc_t;

/*
 * Global data declarations
 */

/** Listener: Table of signals to report reception events for. */
extern cmd_listenerSigDesc_t cmd_listenerSignalAry[CMD_MAX_NO_SIGNALS_TO_LISTEN_TO];

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

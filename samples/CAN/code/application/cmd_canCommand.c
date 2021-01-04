/**
 * @file cmd_canCommand.c
 * This module implements a simple command interpreter for the CAN realted commands, the
 * application understands.
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
/* Module interface
 *   cmd_parseCanCommand
 * Local functions
 *   checkNoArgs
 *   searchSignalToListenTo
 *   addSignalToListener
 */

/*
 * Include files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>

#include "typ_types.h"
#include "f2d_float2Double.h"
#include "cde_canDataTables.h"
#include "cmd_canCommand.h"


/*
 * Defines
 */
 
/** Size of listener: This is the maximum number of signals to listen to. The number should
    be kept little in order to flood the console with output about received signals. */
#define MAX_NO_SIGNALS_TO_LISTEN_TO 10u

/** Unfortunately, our C library doesn't support case insenistive string compare. Here's a
    preliminary work around. */
#define stricmp(a,b)    (strcmp(a,b))
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
/** Table entry of listener. It describes one signal to listen to. */
typedef struct listenerSigDesc_t
{
    /** Signal by reference into the global table \a cde_canSignalAry of all signals in the
        CAN database. A value of UINT_MAX means table entry not in use. */
    unsigned int idxSignal;

    /** Time of adding signal to the listener. (The age of the signal is used to identify,
        which one to drop in advantage of a newly added if the list is full.) */
    unsigned int tiAdded;
    
} listenerSigDesc_t;


/*
 * Data definitions
 */
 
/** Listener: Table of signals to report reception events for. */
static listenerSigDesc_t SDATA_P1(_listenerSignalAry)[MAX_NO_SIGNALS_TO_LISTEN_TO] =
    { [0 ... ((MAX_NO_SIGNALS_TO_LISTEN_TO)-1)] =
        { .idxSignal = UINT_MAX,
          .tiAdded = 0,
        },
    };

/** Listener: Time at which an element is added to its list of signals to listen to. */
static unsigned int DATA_P1(_tiListenerAdd) = 0;


/*
 * Function implementation
 */


/**
 * Core operation of listener: Display the signals, which we are currently listening to.
 * This function is intended to become a callback for the CAN stack. It should be called on
 * each CAN reception event.
 *   @param idxRxFr
 * Index of the received message. The index relates to the global array of message
 * descriptors, \a cde_canRxFrameAry.
 */
void cmd_onReceiveMessage(unsigned int idxRxFr)
{
    unsigned int idxSigInList;
    for(idxSigInList=0; idxSigInList<sizeOfAry(_listenerSignalAry); ++idxSigInList)
    {
        const listenerSigDesc_t const *pSigInList = &_listenerSignalAry[idxSigInList];
        if(pSigInList->idxSignal < sizeOfAry(cde_canSignalAry))
        {
            /* Access the descriptor of the currently checked signal. */
            const cde_canSignal_t * const pSig = &cde_canSignalAry[pSigInList->idxSignal];

            /* Check if this signal belongs to the just received message. */
            if(pSig->isReceived &&  pSig->idxFrame == idxRxFr)
            {
                /* Signal belongs to received frame, report new signal value. */
                
                /* Access the descriptor of the received frame. */
                assert(idxRxFr < sizeOfAry(cde_canRxFrameAry));
                const cde_canFrame_t * const pFrame = &cde_canRxFrameAry[idxRxFr];

                printf( "Frame %s (%d), signal %s: %f %s\r\n"
                      , pFrame->name
                      , pFrame->canId
                      , pSig->name
                      , f2d(pSig->getter())
                      , pSig->unit
                      );
            }

        } /* End if(List entry contains a signal?) */
        
    } /* End for(Check all entries in listener's internal list) */

} /* End of cmd_onReceiveMessage */



/**
 * Check the number of received arguments. Print a helpful warning in case of a mismatch.
 *   @return
 * \a true, if number of arguments is in range, else \a false.
 *   @param cmd
 * The name of the related command is needed for the help message.
 *   @param noArguments
 * The actual, checked number of arguments, which had been passed with the command.
 *   @param min
 * The minimum allowed number of arguments.
 *   @param max
 * The minimum allowed number of arguments.
 */
static bool checkNoArgs( const char *cmd
                       , unsigned int noArguments
                       , unsigned int min
                       , unsigned int max
                       )
{
    const bool success = noArguments >= min  &&  noArguments <= max;
    if(!success)
    {
        if(min != max)
        {
            iprintf( "Bad number of arguments for command %s; expect %u to %u arguments"
                     " but received %u."
                   , cmd, noArguments, min, max
                   );
        }
        else
        {
            iprintf( "Bad number of arguments for command %s; expect %u arguments"
                     " but received %u."
                   , cmd, noArguments, min
                   );
        }
        iprintf(" Type `help' to get more information about command %s\r\n", cmd);
    }
    
    return success;
    
} /* End of checkNoArgs */




/**
 * Check if a given signal is already in the list of signals to listen to. If not, find out
 * where to possibly put it.
 *   @return
 * \a true If the signal is found, or \a false if it is not currently in the list.
 *   @param pIdxInList
 * If the signal is found, get its index in local table \a _listenerSignalAry of signals
 * to listen to. The value is placed in * \a pIdxInList.\n
 *   If the signal is not found, get the index in the same table, where to place a new
 * signal to listen to. This index points to an empty entry if still available or to the
 * eldest, now dropped signal if the table is full.
 *   @param idxSignalInGlobalTable
 * The signal to look for is identified by the index into the global table \a
 * cde_canSignalAry of all signals in the CAN database.\n
 *   If UINT_MAX is passed then the function will return the index of the first empty entry
 * in the local table or UINT_MAX if the table is full.
 */
static bool searchSignalToListenTo( unsigned int *pIdxInList
                                  , unsigned int idxSignalInGlobalTable
                                  )
{
    *pIdxInList = UINT_MAX;
    unsigned int tiAddedMin = UINT_MAX
               , idxEldest = UINT_MAX;
    
    unsigned int idxSig;
    for(idxSig=0; idxSig<sizeOfAry(_listenerSignalAry); ++idxSig)
    {
        const listenerSigDesc_t const *pSig = &_listenerSignalAry[idxSig];
        if(pSig->idxSignal == idxSignalInGlobalTable)
        {
            /* Signal of interest is identified. */
            *pIdxInList = idxSig;
            assert(*pIdxInList < sizeOfAry(_listenerSignalAry));
            return true;
        }
        else if(pSig->idxSignal == UINT_MAX)
        {
            /* At least, we have found an empty place in the list. */
            if(*pIdxInList == UINT_MAX)
                *pIdxInList = idxSig;
        }
        else if(pSig->tiAdded < tiAddedMin)
        {
            /* Update the reference to the eldest signal in the list. */
            tiAddedMin = pSig->tiAdded;
            idxEldest = idxSig;
        }
    } /* End for(All entries in the list) */
    
    /* If we get here, then the signal is not in the list. */
    
    if(*pIdxInList == UINT_MAX)
    {
        /* No empty space has been found in the (full) list, we return the indes to the
           eldest entry, which should be overwritten. */
        *pIdxInList = idxEldest;
    }
    
    assert(*pIdxInList < sizeOfAry(_listenerSignalAry));
    return false;
    
} /* End of searchSignalToListenTo */




/**
 * Add or remove a signal to/freom the list of those, the application is listening to. The
 * totla number of such signals is tightly restricted (the console would otherwise be
 * flooded with output) and if it is full then the new signal will replace to most recently
 * added.
 *   @return
 * \a true, if the referenced signal was identified in the CAN database and could be added
 * or removed, else \a false. Appropriate user feedback has written to the serial output in
 * case of \a false.
 *   @param canId
 * The CAN ID of the message, \a signalName belongs to. May be UINT_MAX if the signal
 * shopuld be searched across all messages in the database.
 *   @param isExtId
 * \a true, if \a canId designates an extended CAN ID, \a false for a standard 11 Bit ID.
 *   @param signalName
 * The CAN database is serached for this signal. The name matching is done case
 * insensitive.
 *   @param add
 * \a true if the signal should be added to the listener and \a false if it should be
 * removed.
 */
static bool addSignalToListener( unsigned int canId
                               , bool isExtId
                               , const char *signalName
                               , bool add
                               )
{
    const bool doCompareCanId = canId != UINT_MAX;
    
    /* This is just sample code. We don't spent effort on optimized search/hash algorithms.
       Just iterate all signals and compare. */
    unsigned int noMatches = 0
               , idxSignalInGlobalTable = 0
               , idxSig;
    for(idxSig=0; idxSig<CDE_NO_SENT_AND_RECEIVED_CAN_SIGNALS; ++idxSig)
    {
        const cde_canSignal_t *pSig = &cde_canSignalAry[idxSig];
        
        if(pSig->isReceived
           && (!doCompareCanId
               ||  cde_canRxFrameAry[pSig->idxFrame].canId == canId
                   &&  cde_canRxFrameAry[pSig->idxFrame].isExtId == isExtId
              )
           &&  stricmp(signalName, pSig->name) == 0
          )
        {
            /* Match! */
            ++ noMatches;
            idxSignalInGlobalTable = idxSig;
        }
    } /* End for(All known signals) */
                
    bool signalIsInList = false;
    if(noMatches == 1)
    {
        assert(idxSignalInGlobalTable < sizeOfAry(cde_canSignalAry));
        const cde_canSignal_t * const pSig = &cde_canSignalAry[idxSignalInGlobalTable];
        assert(pSig->idxFrame < sizeOfAry(cde_canRxFrameAry));
        const cde_canFrame_t * const pFrame = &cde_canRxFrameAry[pSig->idxFrame];
        
        /* Look for an existing entry of the same signal first to avoid double entries.
             idxInList: Index if found signal or index to use for next added signal
           otherwise. */
        unsigned int idxInList;
        signalIsInList = searchSignalToListenTo(&idxInList, idxSignalInGlobalTable);
        
        if(add)
        {
            /* Add signal to listener. */

            if(signalIsInList)
            {
                iprintf( "Signal %s (%s, %lu) had already been added to the listener. No is"
                         " action taken\r\n"
                       , signalName
                       , pFrame->name
                       , pFrame->canId
                       );
            }
            else
            {
                assert(idxInList < sizeOfAry(_listenerSignalAry));
                const unsigned int idxSignalBefore = _listenerSignalAry[idxInList].idxSignal;
                _listenerSignalAry[idxInList] = (listenerSigDesc_t)      
                                                { .idxSignal = idxSignalInGlobalTable,
                                                  .tiAdded = _tiListenerAdd++,
                                                };
                if(idxSignalBefore < sizeOfAry(cde_canSignalAry))
                {
                    const cde_canSignal_t * const pSig = &cde_canSignalAry[idxSignalBefore];
                    assert(pSig->idxFrame < sizeOfAry(cde_canRxFrameAry));
                    const cde_canFrame_t * const pFrame = &cde_canRxFrameAry[pSig->idxFrame];
                    iprintf( "Signal %s (%s, %lu) has been removed from the listener\r\n"
                           , pSig->name
                           , pFrame->name
                           , pFrame->canId
                           );
                }
                iprintf( "Signal %s (%s, %lu) is added to the listener\r\n"
                       , signalName
                       , pFrame->name
                       , pFrame->canId
                       );
            }
        }
        else
        {
            /* Remove signal from listener. */
            
            if(signalIsInList)
            {
                assert(idxInList < sizeOfAry(_listenerSignalAry));
                _listenerSignalAry[idxInList].idxSignal = UINT_MAX;
                iprintf( "Signal %s (%s, %lu) has been removed from the listener\r\n"
                       , signalName
                       , pFrame->name
                       , pFrame->canId
                       );
            }
            else
            {
                iprintf( "Signal %s (%s, %lu) had not been added to the listener before."
                         " No is action taken\r\n"
                       , signalName
                       , pFrame->name
                       , pFrame->canId
                       );
            }
        }
    }
    else if(noMatches == 0)
    {
        iprintf( "No signal %s found in the CAN database. No such signal is %s"
                 " the listener\r\n"
               , signalName
               , add? "added to": "removed from"
               );
    }
    else
    {
        iprintf( "Signal name %s is ambiguous in the CAN database. Got %u matches. No such"
                 " signal is %s the listener.\r\n"
                 "Consider using the CAN ID for disambiguation."
                 " Type `help' to get more information about command %s\r\n"
               , signalName
               , noMatches
               , add? "added to": "removed from"
               , add? "listen": "unlisten"
               );
    }
   
    return signalIsInList;

} /* End of addSignalToListener */




/**
 * The function receives some user input and decides, whether it forms one of the
 * understood CAN related commands. If so, the user demanded actions are performed.
 *   @return
 * \a true, if the user input could be consumed, else \a false. \a true doesn't necessarily
 * mean that the comand was correct and could be executed. (If not, appropriate user
 * feedback has been written to serial output.)
 *   @param argC
 * The number of white space separated words of received user input.
 *   @param argV
 * The \a argC received words of user input, which form the user issued command.
 */
bool cmd_parseCanCommand(unsigned int argC, const char *argV[])
{
    if(argC == 0)    
        return false;

    const char *pCmd = argV[0];
    bool cmdListen;
    if((cmdListen=stricmp(pCmd, "listen") == 0)  ||  stricmp(pCmd, "unlisten") == 0)
    {
        /* (Un)Listen requires at least 1 argument, the name of a signal. */
        if(checkNoArgs(pCmd, argC-1, 1, 2))
        {
            bool cmdOk = false;
            
            /* A CAN ID 0xffffffff, which doesn't exist, indicates that the user has not
               specified a particular ID. */
            unsigned int canId = UINT_MAX;
            bool isExtId = false;
            
            const char *signalName = NULL;
            
            if(argC == 3)
            {
                /* The first argument is the decimal CAN ID for disambiguation of the
                   signal name. A leading x indicates an extended ID. */
                const char *canIdStr = argV[1];
                unsigned int noChars = strlen(canIdStr);
                assert(noChars > 0);
                
                isExtId = (toupper((int)*canIdStr) == 'X');
                if(isExtId)
                {
                    ++ canIdStr;
                    -- noChars;
                }
                
                if(noChars > 0  && isdigit((int)*canIdStr))
                    canId = (unsigned)atoi(canIdStr);
                    
                /* Check range of received CAN ID. If we didn't get any then the check
                   fails, too, due to the chosen default value for canId. */
                if((canId & ~0x1fffffffu) != 0
                   ||  !isExtId &&  (canId & ~0x7ffu) != 0
                  )
                {
                    iprintf( "Bad 1st argument received for command %s; is not a valid CAN"
                             " ID."
                             " Type `help' to get more information about command %s\r\n"
                           , pCmd
                           , pCmd
                           );
                }
                else
                    cmdOk = true;
                    
                /* The second argument is the name of the signal to listen to. */
                signalName =  argV[2];   
            }
            else
            {
                /* The first and only argument is the name of the signal to listen to. */
                signalName =  argV[1];   
                cmdOk = true;
            }
            
            /* Command line has been parsed, trigger the action if no error had been
               found. */ 
            if(cmdOk)
            {
                addSignalToListener(canId, isExtId, signalName, cmdListen);
            }
            
        } /* End if(Correct number of arguments received?) */
        
        /* Command "listen" or "unlisten" has been consumed. */
        return true;
    }
    else if(stricmp(pCmd, "clearlisten") == 0)
    {
        /* "clearlisten" has no arguments. */
        if(checkNoArgs(pCmd, argC-1, 0, 0))
        {
            unsigned int idxInList;
            for(idxInList=0; idxInList<sizeOfAry(_listenerSignalAry); ++idxInList)
                _listenerSignalAry[idxInList].idxSignal = UINT_MAX;

            iprintf("All signals have been removed from the listener.\r\n");
        }                 

        /* Command "clearlisten" has been consumed. */
        return true;
    }
    else if(stricmp(pCmd, "set") == 0)
    {
        /* Command "set" has been consumed. */
        return true;
    }
    else
        return false;
        
} /* End of cmd_parseCanCommand */





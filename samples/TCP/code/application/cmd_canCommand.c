/**
 * @file cmd_canCommand.c
 * This module implements a simple command interpreter for the CAN related commands, the
 * application understands.
 *
 * Copyright (C) 2020-2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   cmd_onReceiveMessage
 *   cmd_parseCanCommand
 * Local functions
 *   checkNoArgs
 *   parseCanId
 *   searchSignalToListenTo
 *   parseCanSignal
 *   compareCanId
 *   identifySignalInDb
 *   parseCanSignalInDb
 *   addSignalToListener
 *   setSignalValue
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
#include "cdt_canDataTables.h"
#include "cmd_canCommand.h"
#include "cdr_canDriverAPI.h"
#include "clg_canLoggerOnTCP.h"

/*
 * Defines
 */
 
/** Unfortunately, our C library doesn't support case insensitive string compare. Here's a
    preliminary work around. */
#define stricmp(a,b)    (strcmp(a,b))
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
/*
 * Data definitions
 */
 
/** Listener: Table of signals to report reception events for. */
cmd_listenerSigDesc_t DATA_P1(cmd_listenerSignalAry)[CMD_MAX_NO_SIGNALS_TO_LISTEN_TO] =
    { [0 ... ((CMD_MAX_NO_SIGNALS_TO_LISTEN_TO)-1)] =
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
 * descriptors, \a cdt_canRxMsgAry.
 */
void cmd_onReceiveMessage(unsigned int idxRxFr)
{
    /* The console has a rather limited use for CAN logging. If enabled, the console is
       flooded with information. Other information is obscured and the bandwidth is soon
       exceeded, leading to truncated output. As a kind of work around, we say to suppress
       this output if there's anyway another open dedicated TCP channel for the same
       information. */
    const bool tcpInUse = clg_getNoConnections() > 0u;
    static bool SBSS_P1(tcpInUse_last_) = false;
    if(tcpInUse)
    {
        if(!tcpInUse_last_)
        {
            tcpInUse_last_ = true;
            fputs( "A TCP connection with the CAN logger has been established. CAN"
                   " logging via serial terminal is stopped as long as TCP is in use\r\n"
                 , stdout
                 );
        }
        return;        
    }
    else if(tcpInUse_last_)
    {
        tcpInUse_last_ = false;
        fputs( "All TCP connections with the CAN logger have been closed. CAN logging via"
               " serial terminal is enabled again\r\n"
             , stdout
             );
    }
    
    
    unsigned int idxSigInList;
    for(idxSigInList=0; idxSigInList<sizeOfAry(cmd_listenerSignalAry); ++idxSigInList)
    {
        const cmd_listenerSigDesc_t const *pSigInList = &cmd_listenerSignalAry[idxSigInList];
        if(pSigInList->idxSignal < sizeOfAry(cdt_canSignalAry))
        {
            /* Access the descriptor of the currently checked signal. */
            const cdt_canSignal_t * const pSig = &cdt_canSignalAry[pSigInList->idxSignal];

            /* Check if this signal belongs to the just received message. */
            if(pSig->isReceived &&  pSig->idxMsg == idxRxFr)
            {
                /* Signal belongs to received message, report new signal value. */
                
                /* Access the descriptor of the received message. */
                assert(idxRxFr < sizeOfAry(cdt_canRxMsgAry));
                const cdt_canMessage_t * const pMsg = &cdt_canRxMsgAry[idxRxFr];

                printf( "Message %s (%lu), signal %s: %f %s\r\n"
                      , pMsg->name
                      , pMsg->canId
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
 * The maximum allowed number of arguments.
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
                   , cmd, min, max, noArguments
                   );
        }
        else
        {
            iprintf( "Bad number of arguments for command %s; expect %u arguments"
                     " but received %u."
                   , cmd, min, noArguments
                   );
        }
        iprintf(" Type `help' to get more information about command %s\r\n", cmd);
    }
    
    return success;
    
} /* End of checkNoArgs */




/**
 * Interpret a command line argument as CAN ID.
 *   @return
 * \a true, if function succeeded, else \a false. The parse results, i.e., the CAN ID and
 * flag isExtId, are valid only if the function returns \a true.
 *   @param pCanId
 * If the function succeeds, and if the user specified it, the CAN ID is returned by
 * reference. Otherwise UINT_MAX is returned.
 *   @param pExtId
 * If the function succeeds, and if the user specified a CAN ID, then the Boolean
 * information whether * \a pCanId designates an extended ID is returned by reference.
 * Otherwise \a false is returned.
 *   @param arg
 * The command line argument, which is expected to be a CAN ID.
 */
static bool parseCanId( unsigned int * const pCanId
                      , bool * const pIsExtId
                      , const char arg[]
                      )
{
    /* A CAN ID 0xffffffff, which doesn't exist, indicates that the user has not
       specified a particular ID. */
    unsigned int canId = UINT_MAX;
    bool isExtId = false;


    /* A leading x indicates an extended ID. */
    const char *canIdStr = arg;
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

    /* Trailing characters in the CAN ID argument are silently ignored. */

    /* Check range of received CAN ID. If we didn't get any then the check
       fails, too, due to the chosen default value for canId. */
    const bool canIdOk = (canId & ~0x1fffffffu) == 0  &&  (isExtId ||  (canId & ~0x7ffu) == 0);

    *pCanId = canId;
    *pIsExtId = isExtId;
    return canIdOk;

} /* parseCanId */



/**
 * Interpret some command line arguments as designation of a signal from the CAN database.
 *   @return
 * \a true, if function succeeded, else \a false. Parse results, signal name and CAN ID are
 * valid only if the function returns \a true. In case of \a false, all appropriate
 * feedback has written to serial out.
 *   @param pSignalName
 * If function succeeds then the pointer to the signal name is returned by reference. The
 * pointer points to one of the command line arguments and it is valid only as long as \a
 * argV is alive.
 *   @param pCanId
 * If function succeeds, and if the user specified it, the CAN ID is returned by reference.
 * Otherwise UINT_MAX is returned.
 *   @param pExtId
 * If function succeeds, and if the user specified a CAN ID, then the Boolean information
 * whether \a CAN ID designates an extended ID is returned by reference. Otherwise \a false
 * is returned.
 *   @param argC
 * The number of white space separated words of received user input. Needs to be 2 or 3.
 *   @param argV
 * The command line as \a argC received words of user input. This function expects two or
 * three words. The first one is the name of the command (needed only for feedback),
 * followed by an optional CAN ID (required if signal name should be ambiguous) and ending
 * with the name of the signal.
 */
static bool parseCanSignal( const char * * const pSignalName
                          , unsigned int * const pCanId
                          , bool * const pIsExtId
                          , unsigned int argC
                          , const char *argV[]
                          )
{
    assert(argC >= 1);
    const char * const cmd = argV[0];
    
    *pSignalName = NULL;
    *pCanId = UINT_MAX;
    *pIsExtId = false;

    bool cmdOk = false;
    if(checkNoArgs(cmd, argC-1, 1, 2))
    {
        if(argC == 3)
        {
            /* The first argument is the decimal CAN ID for disambiguation of the
               signal name. */
            cmdOk = parseCanId(pCanId, pIsExtId, argV[1]);

            /* The second argument is the name of the signal to listen to. */
            *pSignalName =  argV[2];
            
            if(!cmdOk)
            {
                iprintf( "Bad 1st argument received for command %s; %s is not a valid CAN"
                         " ID."
                         " Type `help' to get more information about command %s\r\n"
                       , cmd
                       , argV[1]
                       , cmd
                       );
            }
        }
        else
        {
            /* The first and only argument is the name of the signal to listen to. */
            *pSignalName = argV[1];
            cmdOk = true;
        }
    }
    
    return cmdOk;
    
} /* End of parseCanSignal */
            
            
            
/**
 * Helper of identifySignalInDb(): Compare if the CAN ID of a signal in the CAN DB matches
 * the user specification.
 *   @return
 * Get \a true if it matches.
 *   @param canId
 * The CAN ID of the message, * \a pSignalInDb belongs to.
 *   @param isExtId
 * \a true, if \a canId designates an extended CAN ID, \a false for a standard 11 Bit ID.
 *   @param pSignalInDb
 * The signal to compare to by reference.
 *   @param isReceived
 * \a true if the signal is expected to be an Rx signal and \a false if it should be
 * a Tx signal.
 */
static bool compareCanId( unsigned int canId
                        , bool isExtId
                        , const cdt_canSignal_t * const pSignalInDb
                        , bool isReceived
                        )
{
    if(isReceived)
    {
        return cdt_canRxMsgAry[pSignalInDb->idxMsg].canId == canId
               &&  cdt_canRxMsgAry[pSignalInDb->idxMsg].isExtId == isExtId;
    }
    else
    {
        return cdt_canTxMsgAry[pSignalInDb->idxMsg].canId == canId
               &&  cdt_canTxMsgAry[pSignalInDb->idxMsg].isExtId == isExtId;
    }
} /* End of compareCanId */




/**
 * Look for a particular signal in the global database, which is a representation of the
 * CAN *.dbc file.
 *   @return
 * If the referenced signal was identified in the CAN database then the function returns
 * the found signal as index into the global table \a cdt_canSignalAry. Otherwise it
 * returns UINT_MAX. Appropriate user feedback has been written to the serial output in
 * case of \a UINT_MAX.
 *   @param canId
 * The CAN ID of the message, \a signalName belongs to. May be UINT_MAX if the signal
 * should be searched across all messages in the database.
 *   @param isExtId
 * \a true, if \a canId designates an extended CAN ID, \a false for a standard 11 Bit ID.
 *   @param signalName
 * The CAN database is searched for this signal. The name matching is done case
 * insensitive.
 *   @param isReceived
 * \a true if the signal is expected to be an Rx signal and \a false if it should be
 * a Tx signal.
 */
static unsigned int identifySignalInDb( unsigned int canId
                                      , bool isExtId
                                      , const char *signalName
                                      , bool isReceived
                                      )
{
    const bool doCompareCanId = canId != UINT_MAX;
    
    /* This is just sample code. We don't spent effort on optimized search/hash algorithms.
       Just iterate all signals in the global database and compare. */
    unsigned int noMatches = 0
               , idxSignalInGlobalTable = UINT_MAX
               , idxSig;
    for(idxSig=0; idxSig<CST_NO_SENT_AND_RECEIVED_CAN_SIGNALS; ++idxSig)
    {
        const cdt_canSignal_t *pSig = &cdt_canSignalAry[idxSig];
        
        if(pSig->isReceived == isReceived
           && (!doCompareCanId || compareCanId(canId, isExtId, pSig, isReceived))
           &&  stricmp(signalName, pSig->name) == 0
          )
        {
            /* Match! */
            ++ noMatches;
            idxSignalInGlobalTable = idxSig;
        }
    } /* End for(All known signals) */
                
    if(noMatches == 1)
    {
        /* Success, signal unambiguously identified. */
    }
    else if(noMatches == 0)
    {
        assert(idxSignalInGlobalTable == UINT_MAX);
        iprintf( "No %s signal %s found in the CAN database\r\n"
               , isReceived? "Rx": "Tx"
               , signalName
               );
    }
    else
    {
        idxSignalInGlobalTable = UINT_MAX;
        iprintf( "%s signal name %s is ambiguous in the CAN database. Got %u matches\r\n"
                 "Consider using the CAN ID in the issued command for disambiguation."
                 " Type `help' to get more information\r\n"
               , isReceived? "Rx": "Tx"
               , signalName
               , noMatches
               );
    }
   
    return idxSignalInGlobalTable;

} /* End of identifySignalInDb */




/**
 * Interpret some command line arguments as designation of a signal from the CAN database.
 * This function is a variant of parseCanSignal(): It filters the raw parse result from the
 * latter with the actual contents of the CAN DB.
 *   @return
 * If the referenced signal was identified in the CAN database then the function returns
 * the found signal as index into the global table \a cdt_canSignalAry. Otherwise it
 * returns UINT_MAX. Appropriate user feedback has been written to the serial output in
 * case of \a UINT_MAX.
 *   @param argC
 * The number of white space separated words of received user input. Needs to be 2 or 3.
 *   @param argV
 * The command line as \a argC received words of user input. This function expects two or
 * three words. The first one is the name of the command (needed only for feedback),
 * followed by an optional CAN ID (required if signal name should be ambiguous) and ending
 * with the name of the signal.
 *   @param isReceived
 * \a true if the signal is expected to be an Rx signal and \a false if it should be
 * a Tx signal.
 */
static unsigned int parseCanSignalInDb( unsigned int argC
                                      , const char *argV[]
                                      , bool isReceived
                                      )
{
    const char *signalName;
    unsigned int canId;
    bool isExtId;
    if(parseCanSignal(&signalName, &canId, &isExtId, argC, argV))
        return identifySignalInDb(canId, isExtId, signalName, isReceived);
    else
        return UINT_MAX;

} /* End of parseCanSignalInDb */
                          
                          
                          
/**
 * Check if a given signal is already in the list of signals to listen to. If not, find out
 * where to possibly put it.
 *   @return
 * \a true If the signal is found, or \a false if it is not currently in the list.
 *   @param pIdxInList
 * If the signal is found, get its index in local table \a cmd_listenerSignalAry of signals
 * to listen to. The value is placed in * \a pIdxInList.\n
 *   If the signal is not found, get the index in the same table, where to place a new
 * signal to listen to. This index points to an empty entry if still available or to the
 * eldest, now dropped signal if the table is full.
 *   @param idxSignalInGlobalTable
 * The signal to look for is identified by the index into the global table \a
 * cdt_canSignalAry of all signals in the CAN database.\n
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
    for(idxSig=0; idxSig<sizeOfAry(cmd_listenerSignalAry); ++idxSig)
    {
        const cmd_listenerSigDesc_t const *pSig = &cmd_listenerSignalAry[idxSig];
        if(pSig->idxSignal == idxSignalInGlobalTable)
        {
            /* Signal of interest is identified. */
            *pIdxInList = idxSig;
            assert(*pIdxInList < sizeOfAry(cmd_listenerSignalAry));
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
        /* No empty space has been found in the (full) list, we return the index to the
           eldest entry, which should be overwritten. */
        *pIdxInList = idxEldest;
    }
    
    assert(*pIdxInList < sizeOfAry(cmd_listenerSignalAry));
    return false;
    
} /* End of searchSignalToListenTo */




/**
 * Add or remove a signal to/from the list of those, the application is listening to. The
 * totla number of such signals is tightly restricted (the console would otherwise be
 * flooded with output) and if it is full then the new signal will replace to most recently
 * added.
 *   @param idxSignalInCanDb
 * The affected CAN signal, represented by the index into the global table \a cdt_canSignalAry.
 *   @param add
 * \a true if the signal should be added to the listener and \a false if it should be
 * removed.
 */
static void addSignalToListener(unsigned int idxSignalInCanDb, bool add)
{
    assert(idxSignalInCanDb < sizeOfAry(cdt_canSignalAry));
    const cdt_canSignal_t * const pSignal = &cdt_canSignalAry[idxSignalInCanDb];
    assert(pSignal->idxMsg < sizeOfAry(cdt_canRxMsgAry));
    const cdt_canMessage_t * const pMsg = &cdt_canRxMsgAry[pSignal->idxMsg];
    
    /* Look for an existing entry of the same signal first to avoid double entries.
         idxInList: Index of found signal or index to use for next added signal
       if not found. */
    unsigned int idxInList;
    const bool signalIsInList = searchSignalToListenTo(&idxInList, idxSignalInCanDb);

    if(add)
    {
        /* Add signal to listener. */

        if(signalIsInList)
        {
            iprintf( "Signal %s (%s, %lu) had already been added to the listener. No"
                     " action is taken\r\n"
                   , pSignal->name
                   , pMsg->name
                   , pMsg->canId
                   );
        }
        else
        {
            assert(idxInList < sizeOfAry(cmd_listenerSignalAry));
            const unsigned int idxSignalInCanDbBefore = cmd_listenerSignalAry[idxInList]
                                                        .idxSignal;
            cmd_listenerSignalAry[idxInList] = (cmd_listenerSigDesc_t)      
                                               { .idxSignal = idxSignalInCanDb,
                                                 .tiAdded = _tiListenerAdd++,
                                               };
            if(idxSignalInCanDbBefore < sizeOfAry(cdt_canSignalAry))
            {
                const cdt_canSignal_t * const pSigBefore =
                                                    &cdt_canSignalAry[idxSignalInCanDbBefore];
                assert(pSigBefore->idxMsg < sizeOfAry(cdt_canRxMsgAry));
                const cdt_canMessage_t * const pMsg = &cdt_canRxMsgAry[pSigBefore->idxMsg];
                iprintf( "Signal %s (%s, %lu) has been removed from the listener\r\n"
                       , pSigBefore->name
                       , pMsg->name
                       , pMsg->canId
                       );
            }
            iprintf( "Signal %s (%s, %lu) is added to the listener\r\n"
                   , pSignal->name
                   , pMsg->name
                   , pMsg->canId
                   );
        }
    }
    else
    {
        /* Remove signal from listener. */
        
        if(signalIsInList)
        {
            assert(idxInList < sizeOfAry(cmd_listenerSignalAry));
            cmd_listenerSignalAry[idxInList].idxSignal = UINT_MAX;
            iprintf( "Signal %s (%s, %lu) has been removed from the listener\r\n"
                   , pSignal->name
                   , pMsg->name
                   , pMsg->canId
                   );
        }
        else
        {
            iprintf( "Signal %s (%s, %lu) had not been added to the listener before."
                     " No action is taken\r\n"
                   , pSignal->name
                   , pMsg->name
                   , pMsg->canId
                   );
        }
    } /* End if(Signal to add or to remove?) */

} /* End of addSignalToListener */




/**
 * Set the value of a signal in the CAN API. If the signal belongs to an event based
 * message then the trigger is set so that it is transmitted immediately.\n
 *   The action is combined with appropriate user feedback via serial out.
 *   @return
 * \a true, if function succeeded, else \a false.
 *   @param idxSignalInCanDb
 * The affected CAN signal, represented by the index into the global table \a cdt_canSignalAry.
 */
static void setSignalValue(unsigned int idxSignalInCanDb, float value)
{
    assert(idxSignalInCanDb < sizeOfAry(cdt_canSignalAry));
    const cdt_canSignal_t * const pSignal = &cdt_canSignalAry[idxSignalInCanDb];
    assert(pSignal->idxMsg < sizeOfAry(cdt_canTxMsgAry));
    const cdt_canMessage_t * const pMsg = &cdt_canTxMsgAry[pSignal->idxMsg];
    
    /* Use range information to properly saturate the set value. */
    bool needSaturation = false;
    if(value > pSignal->max)
    {
        value = pSignal->max;
        needSaturation = true;
    }
    else if(value < pSignal->min)
    {
        value = pSignal->min;
        needSaturation = true;
    }

    float oldValue = pSignal->getter();
    pSignal->setter(value);
    printf( "Signal %s (%s, %lu) has been changed from %f %s to new %svalue %f %s\r\n"
          , pSignal->name
          , pMsg->name
          , pMsg->canId
          , f2d(oldValue)
          , pSignal->unit
          , needSaturation? "(saturated) ": ""
          , f2d(value)
          , pSignal->unit
          );
    
    /* Trigger sending of event messages. For ordinary regular messages, the statement is
       harm- and useless. */
    pMsg->pInfoTransmission->isEvent = true;
    
} /* End of setSignalValue */




/**
 * The function receives some user input and decides, whether it forms one of the
 * understood CAN related commands. If so, the user demanded actions are performed.
 *   @return
 * \a true, if the user input could be consumed, else \a false. \a true doesn't necessarily
 * mean that the command was correct and could be executed. (If not, appropriate user
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

    const char *cmd = argV[0];
    bool isCmdListen;
    if((isCmdListen=stricmp(cmd, "listen") == 0)  ||  stricmp(cmd, "unlisten") == 0)
    {
        unsigned int idxSignalInCanDb = parseCanSignalInDb(argC, argV, /* isReceived */ true);
        if(idxSignalInCanDb < sizeOfAry(cdt_canSignalAry))
        {
            /* Command line has been parsed, signal has been identified in the CAN DB,
               now trigger the action. */
            addSignalToListener(idxSignalInCanDb, /* add */ isCmdListen);
            
        } /* End if(Correct number of arguments received?) */
        
        /* Command "listen" or "unlisten" has been consumed. */
        return true;
    }
    else if(stricmp(cmd, "clearlisten") == 0)
    {
        /* "clearlisten" has no arguments. */
        if(checkNoArgs(cmd, argC-1, 0, 0))
        {
            unsigned int idxInList;
            for(idxInList=0; idxInList<sizeOfAry(cmd_listenerSignalAry); ++idxInList)
                cmd_listenerSignalAry[idxInList].idxSignal = UINT_MAX;

            iprintf("All signals have been removed from the listener.\r\n");
        }                 

        /* Command "clearlisten" has been consumed. */
        return true;
    }
    else if(stricmp(cmd, "set") == 0)
    {
        /* "set" has 2..3 arguments to specify a signal and the value of it. */
        if(checkNoArgs(cmd, argC-1, 2, 3))
        {
            unsigned int idxSignalInCanDb = parseCanSignalInDb( argC-1
                                                              , argV
                                                              , /* isReceived */ false
                                                              );
            if(idxSignalInCanDb < sizeOfAry(cdt_canSignalAry))
            {
                /* Command line has been parsed, signal has been identified in the CAN DB,
                   now trigger the action. */
                float sigVal = atoff(argV[argC-1]);
                setSignalValue(idxSignalInCanDb, sigVal);
            }
        }
        
        /* Command "set" has been consumed. */
        return true;
    }
    else if(stricmp(cmd, "tx") == 0)
    {
        /* "tx" has 1..9 arguments to specify a CAN ID and up to eight payload bytes. */
        if(checkNoArgs(cmd, argC-1, 1, 9))
        {
            unsigned int canId;
            bool isExtId;
            if(parseCanId(&canId, &isExtId, argV[1]))
            {
                unsigned int DLC = argC - 2u;
                assert(DLC <= 8u);
                
                uint8_t payloadAry[DLC];
                for(unsigned int u=0u; u<DLC; ++u)
                    payloadAry[u] = (uint8_t)atoi(argV[u+2u]);
                
                const cdr_errorAPI_t errCode = cdr_sendMessageQueued( BSW_CAN_BUS_0
                                                                    , isExtId
                                                                    , canId
                                                                    , DLC
                                                                    , payloadAry
                                                                    );
                if(errCode == cdr_errApi_noError)
                {
                    iprintf( "CAN message %u%s successfully queued for transmission\r\n"
                           , canId
                           , isExtId? "x": ""
                           );
                }
                else
                {
                    iprintf( "Failed to send CAN message %u%s: Error %u\r\n"
                           , canId
                           , isExtId? "x": ""
                           , (unsigned)errCode
                           );
                }
            }
            else
                iprintf("Bad CAN ID stated: %s\r\n", argV[1]);
        }

        /* Command "tx" has been consumed. */
        return true;
    }
    else
        return false;
        
} /* End of cmd_parseCanCommand */





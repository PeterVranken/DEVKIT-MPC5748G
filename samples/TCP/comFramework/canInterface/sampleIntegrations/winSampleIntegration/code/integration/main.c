/**
 * @file main.c
 * Main function of this application. This file shows how to integrate
 * the CAN interface with an under Windows simulated operating system.
 *
 * Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   main
 * Local functions
 *   getTimeStr
 *   getLogFileName
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "smalloc.h"
#include "log_logger.h"
#include "opt_getOpt.h"
#include "fil_file.h"
#include "oss_operatingSystemSimulation.h"
#include "apt_applicationTask.h"
#include "main.h"


/*
 * Defines
 */

/** The path separator character as a string constant. */
#ifdef __WINNT__
# define SL "\\"
#else
# define SL "/"
#endif


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** A global logger object, which can be referenced from anywhere for writing progress
    messages. */
log_hLogger_t main_hGlobalLogger = LOG_HANDLE_TO_EMPTY_LOGGER_OBJECT;


/*
 * Function implementation
 */

/**
 * Get the current system time as printable string.
 *   @return
 * The time string is returned. The returned pointer is valid until next entry into this
 * function.
 *   @remark
 * The function is not reentrant but uses static memory to store the time information.
 */

static const char *getTimeStr()
{
    /* Get current time as string of fixed length. */
    time_t t;
    time(&t);
    const char * const timeStrLF = ctime(&t);

    /* Copy the time string only partial, we don't need the line feed at the end. */
    assert(strlen(timeStrLF) == 25);
    static char timeStr[25];
    timeStr[0] = '\0';
    strncat(timeStr, timeStrLF, sizeof(timeStr)-1);

    return timeStr;

} /* End of getTimeStr */




/**
 * Figure out the name of the log file. It is either user-specified or derived from an input
 * file or the application name.\n
 *   If a single input file is processed then log file is named as this file.\n
 *   If several input files are processed then the log file's name is derived from the
 * application name.
 *   @return
 * Get the file name as malloc allocated string. Or NULL if the user had specified: "don't
 * use a log file at all."
 *   @param pCmdLine
 * The result of the command line parsing is passed by reference.
 *   @param inputFileName
 * The name of the only or the first input file name or NULL if there's no input file at all.
 */

static const char *getLogFileName( const opt_cmdLineOptions_t * const pCmdLine
                                 , const char * const inputFileName
                                 )
{
    if(pCmdLine->logFileName == NULL)
        return NULL;
    else if(*pCmdLine->logFileName != '\0')
        return stralloccpy(pCmdLine->logFileName);
    else
    {
        /* None trivial case: Determine the default name. */

        /* If the user demands a specific output path then place the log file into that
           path. Otherwise use the current working directory. */
        const char *path;
        if(pCmdLine->outputPath != NULL)
            path = pCmdLine->outputPath;
        else
            path = ".";

        if(pCmdLine->noInputFiles != 1)
        {
            /* If there are several input files, then we use the application name for the
               log file. */
            char logFileName[strlen(path) + sizeof(SL) + sizeof(MAIN_LOG_FILE_NAME)];
            snprintf(logFileName, sizeof(logFileName), "%s" SL MAIN_LOG_FILE_NAME, path);
            return stralloccpy(logFileName);
        }
        else
        {
            /* We have a single input file. Its name is re-used for the log file. */
            assert(pCmdLine->noInputFiles == 1);
            char *pureFileName;
            fil_splitPath( /* pPath */ NULL
                         , &pureFileName
                         , /* pExt */ NULL
                         , inputFileName
                         );

            char logFileName[strlen(path) + sizeof(SL) + strlen(pureFileName)
                             + sizeof(MAIN_LOG_FILE_NAME_EXT)
                            ];
            snprintf( logFileName
                    , sizeof(logFileName)
                    , "%s" SL "%s%s"
                    , path
                    , pureFileName
                    , MAIN_LOG_FILE_NAME_EXT
                    );
            free((char*)pureFileName);
            return stralloccpy(logFileName);

        } /* End if(One or multiple input files?) */

    } /* End if(Trivial situation or do we have to figure out the name?) */

} /* End of getLogFileName */




/**
 * The main function of this C project. It implements the scheduler of the operating system
 * with a simple, single tasked loop.
 *   @return
 * \a 0 if application succeeded or -1 if it reported an error.
 *   @param argc
 * The number of program arguments.
 *   @param argv
 * An array of \a argc constant strings, each a program argument. An additional array entry
 * NULL indicates the end of the list.
 */

signed int main(signed int argc, char *argv[])
{
    const char * const greeting =
           "-----------------------------------------------------------------------------\n"
           " " MAIN_APP_GREETING "\n"
           " Copyright (C) 2015-2022 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)\n"
           " This is free software; see the source for copying conditions. There is NO\n"
           " warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
           "-----------------------------------------------------------------------------";

    /* Print the greeting, which may disregard the switch -s, "be silent". Doing command
       line parsing first (to have the knowledge whether -s is given) would however mean,
       that all feedback to the command line interface (including output of the help text)
       would appear before the greeting - which is worse. */
    printf("%s\n", greeting);

    /* Parse the command line. Errors and problems are reported to both stdout and stderr. */
    opt_cmdLineOptions_t cmdLine;
    bool success = opt_parseCmdLine(&cmdLine, argc, argv);

#ifdef DEBUG
//    opt_echoUserInput(stdout, &cmdLine);
#endif
    if(!success)
    {
        /* Don't consider it an error if the user explicitly demands some information only. */
        return (cmdLine.help || cmdLine.showVersion)? 0: -1;
    }

    /* Some command line options have optional arguments. If the arguments have been
       omitted then find approriate default values now. */
    const char *logFileName = getLogFileName( &cmdLine
                                            , cmdLine.idxFirstInputFile < (unsigned)argc
                                              ? argv[cmdLine.idxFirstInputFile]
                                              : NULL
                                            );
    log_initModule();

    /* Create the logger object. */
    bool cantOpenLogFile = false;
    main_hGlobalLogger = LOG_HANDLE_TO_EMPTY_LOGGER_OBJECT;
    if(!log_createLogger( &main_hGlobalLogger
                        , logFileName
                        , log_result
                        , log_fmtLong
                        , cmdLine.echoToConsole
                        , cmdLine.doAppend
                        )
      )
    {
        /* The constructor of log can fail only if a log file had tried to be opened. */
        assert(logFileName != NULL);

        /* The logger object can still be used if it at least logs to stdout. */
        if(cmdLine.echoToConsole)
        {
            /* Print the error message later, when we have completed the configuration of
               the logger object. */
            cantOpenLogFile = true;
        }
        else
        {
            fprintf( stderr
                   , "Can't open log file %s. Application is terminated as no results"
                     " could be reported\n"
                   , logFileName
                   );
            return -1;
        }
    } /* End if(Could the log file be opened?) */

    /* If we get here: The logger object can be used even if it failed to open the log file
       since it echos everything to stdout. We proceed. */

    /* Configure the logger with the demands of the command line. */
    if(cmdLine.lineFormat != NULL)
        log_parseLineFormat(main_hGlobalLogger, cmdLine.lineFormat);
    if(cmdLine.logLevel != NULL)
        log_parseLogLevel(main_hGlobalLogger, cmdLine.logLevel);

    /* Log the greeting but don't do this a second time on the normal console. */
    log_setEchoToConsole(main_hGlobalLogger, /* echoToConsole */ false);
    LOG_RESULT(main_hGlobalLogger, "\n%s", greeting)
    log_setEchoToConsole(main_hGlobalLogger, cmdLine.echoToConsole);

    if(logFileName != NULL)
        LOG_INFO(main_hGlobalLogger, "Log file name is %s", logFileName)
    if(cantOpenLogFile)
        LOG_ERROR(main_hGlobalLogger, "Can't open log file %s", logFileName)

    /* The log file name is not used down here. */
    if(logFileName != NULL)
    {
        free((char*)logFileName);
        logFileName = NULL;
    }

    /* If the logger object doesn't write a line header with full time information we make
       a time notice now so that the sub-sequent lines of the log can be related to the
       absolute time. */
    if(log_getLineFormat(main_hGlobalLogger) != log_fmtLong)
        LOG_RESULT(main_hGlobalLogger, "Beginning of processing at %s", getTimeStr())

    /* Initialize the modules of the Windows application environment. This part of the code
       is due to the Windows implementation onyl and won't have a counterpart in an
       integration on a true RTOS driven platform. */
    
    
    /* Install the task functions and interrupt handlers.
         This part of the initialization is part of the integration demonstration: A real
       RTOS environment will need a similar piece of code. Some will do it like here with a
       functional API, some will have appropriate macros, which resemble a functional API
       and some will have a configurator application, which the required initialization
       code is generated with. */
    oss_installIrqHandlerCanRx(apt_irqHandlerRxCan);
    oss_installIrqHandlerCanBusOff(apt_irqHandlerBusOff);
    oss_installTask(oss_taskType_init, apt_taskInit);
    oss_installTask(oss_taskType_regular10ms, apt_task10ms);
    oss_installTask(oss_taskType_regular100ms, apt_task100ms);
    oss_installTask(oss_taskType_shutdown, apt_taskShutdown);

    /* Start the operating system. In most real RTOS environment this will be a call like
       startOS and the major difference to our simulation code it that it would never
       return. The simulation however has a end time condition. Via the started OS
       scheduler we actually run the application code. */
    oss_kernel( /* tickInUs */ 100
              , /* tiSimEndInUs */ (unsigned long long)(cmdLine.tiSimEnd*1e6 + 0.5)
              );

    /* Final cleanup by the modules. */

    /* If the logger object doesn't write a line header with full time information we make
       a final time notice now. */
    if(log_getLineFormat(main_hGlobalLogger) != log_fmtLong)
        LOG_RESULT(main_hGlobalLogger, "End of processing at %s", getTimeStr());

    /* Delete global application log and shutdown module log. */
    log_deleteLogger(main_hGlobalLogger);
    log_shutdownModule();

    return success? 0: -1;

} /* End of main */





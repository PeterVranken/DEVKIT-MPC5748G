#ifndef LOG_LOGGER_INCLUDED
#define LOG_LOGGER_INCLUDED
/**
 * @file log_logger.h
 * Definition of global interface of module log_logger.c
 *
 * Copyright (C) 2013 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Include files
 */

#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>

#include "types.h"


/*
 * Defines
 */

/** Log a debug message. Pass the logger object by reference, followed by a printf style
    format string and its variable argument list. */
#define LOG_DEBUG(pObj, ...) LOG_LOG(pObj, log_debug, __VA_ARGS__)

/** Log an informative message. Pass the logger object by reference, followed by a printf
    style format string and its variable argument list. */
#define LOG_INFO(pObj, ...) LOG_LOG(pObj, log_info, __VA_ARGS__)

/** Log an application result. Pass the logger object by reference, followed by a printf
    style format string and its variable argument list. */
#define LOG_RESULT(pObj, ...) LOG_LOG(pObj, log_result, __VA_ARGS__)

/** Log a warning. Pass the logger object by reference, followed by a printf style format
    string and its variable argument list. */
#define LOG_WARN(pObj, ...) LOG_LOG(pObj, log_warn, __VA_ARGS__)

/** Log an error. Pass the logger object by reference, followed by a printf style format
    string and its variable argument list. */
#define LOG_ERROR(pObj, ...) LOG_LOG(pObj, log_error, __VA_ARGS__)

/** Log a fatal error. Pass the logger object by reference, followed by a printf style
    format string and its variable argument list. */
#define LOG_FATAL(pObj, ...) LOG_LOG(pObj, log_fatal, __VA_ARGS__)


/** Log a message if it has the minimum log level. Pass the logger object by reference,
    followed by the log level of this message, followed by a printf style format string and
    its variable argument list. */
#define LOG_LOG(pObj, logLevel, ...)                                                        \
        {                                                                                   \
            if((logLevel) >= log_getLogLevel(pObj))                                         \
                log_logLine((pObj), (logLevel), __VA_ARGS__);                               \
        } /* End macro LOG_LOG */




/** A constant initializer expression, that may be used as RHS of the definition of a
    logger object. It's an invlaid NULL handle, which must not be used at all. */
#define LOG_HANDLE_TO_EMPTY_LOGGER_OBJECT   NULL


/*
 * Global type definitions
 */

/** The verbosity level as used by all logger objects.
      @remark Please note, that any change of the enumeration requires according
    maintenance of the implementation of this module, see C source file for hints. */
typedef enum { log_debug = 0    // For internal developing purpose only
             , log_info         // Verbose, informative output; progress information
             , log_result       // Output of computation results and problem reports
             , log_warn         // Output of warnings and errors
             , log_error        // Output of errors
             , log_fatal        // Output of fatal errors, which make the application abort
             
             , log_noLogLevels  // No log level. Number of known levels. For internal use only
             , log_continueLine // No log level. Flag to suppress output of line header
             
             } log_logLevel_t;


/** The format of each line output by the logger. */
typedef enum { log_fmtRaw = 0     // No header, only application output
             , log_fmtShort       // Condensed header, no absolute time stamp
             , log_fmtLong        // Full line header with absolute time stamp
             
             , log_noLineFormats  // No format. Number of known formats. For internal use only
             
             } log_lineFormat_t;


/** The logger object is implemented by a struct definition. Basically, the structure would
    be obscured by placing the typedef into the implementation file. This would however
    disable the use of inline functions for functional access to the members. Therefore, it
    has been decided to make the typedef public, although it's still forbidden to make any
    use of the information. Never touch the members directly but only use pointers to such
    structs as handles to the logger objects. */
typedef struct log_logger_t
{
    /** A counter of references to this object. Used to control deletion of object. */
    unsigned int noReferencesToThis;

    /** Pointer to the actual file object. Maybe NULL. */
    FILE *pLogFile;

    /** A mutex to serialize possibly concurrent accesses to the log file \a pLogFile. */
    pthread_mutex_t mutexFileStream;
    
    /** Log level. See enum log_logLevel_t. */
    log_logLevel_t logLevel;

    /** Line header format. */
    log_lineFormat_t lineFormat;

    /** True if all output should be written to stdout also. */
    boolean_t echoToConsole;

    /** The return code from the last file operation. */
    int lastFileSystemErr;

} log_logger_t;


/** The logger object is implemented by an obscure struct definition. Use pointers to such
    structs as handles to the logger objects. */
typedef log_logger_t *log_hLogger_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialize the module prior to first use of any of its methods or global data objects. */
void log_initModule(void);

/** Shutdown of module after use. Release of memory, closing files, etc. */
void log_shutdownModule(void);

/** Create a new logger. */
boolean_t log_createLogger( log_hLogger_t * const phNewLogger
                          , const char * const fileName
                          , log_logLevel_t logLevel
                          , log_lineFormat_t lineFormat
                          , boolean_t initialEchoToConsole
                          , boolean_t doAppend
                          );

/** Get another reference or handle to the same object. */
log_hLogger_t log_cloneByReference(log_hLogger_t hObj);

/** Close file and destroy object after usage. */
void log_deleteLogger(log_hLogger_t hObj);

/** Define a logger object to become the global logger. */
log_hLogger_t log_setGlobalLogger(log_hLogger_t hObj);

/** Access the global logger. */
log_hLogger_t log_getGlobalLogger();

/** Enable/disable writing all output to the console (stdout) also. */
void log_setEchoToConsole(log_hLogger_t hObj, boolean_t echoToConsole);

/** Set or change the level of verbosity. */
void log_setLogLevel(log_hLogger_t hObj, log_logLevel_t logLevel);

/** Set or change the level of verbosity, which is specified by string. */
void log_parseLogLevel(log_hLogger_t hObj, const char *logLevelName);

/** Get the level of verbosity. */
static inline log_logLevel_t log_getLogLevel(log_hLogger_t hObj)
    { return hObj->logLevel; }

/** Set or change the line header format. */
void log_setLineFormat(log_hLogger_t hObj, log_lineFormat_t lineHeaderFormat);

/** Set or change the line header format, which is specified by string. */
void log_parseLineFormat(log_hLogger_t hObj, const char *lineHeaderFormatName);

/** Get the line header format. */
static inline log_lineFormat_t log_getLineFormat(log_hLogger_t hObj)
    { return hObj->lineFormat; }

/** The line format dependent length of the header of each line. */
unsigned int log_getLengthOfLineHeader(log_hLogger_t hObj);

/** Get the eror status of the last recent output operation.
      @return The error information is the return value of the stdio function; see e.g. for
    fputs. */
static inline int log_ferror(log_hLogger_t hObj)
    { return hObj->lastFileSystemErr; }

/** Close a log file. */
boolean_t log_close(log_hLogger_t hObj);

/** Request access to the output streams for for direct writing using the C stdio library
    functions. */
void log_getStreams(log_logger_t * const hObj, FILE **phConsole, FILE **phLogFile);
                   
/** Flush contents of log file buffers. */
void log_flush(log_hLogger_t hObj);

/** Write a single logging message without an appended newline character. */
unsigned int log_log( log_hLogger_t hObj
                    , log_logLevel_t logLevel
                    , const char * const formatString
                    , ...
                    );

/** Write a single logging message and terminate output with an additional newline. */
unsigned int log_logLine( log_logger_t * const hObj
                        , log_logLevel_t logLevel
                        , const char * const formatString
                        , ...
                        );

/** Check log level of a logger object.
      @return true if and only if a message of given level should be logged.
      @param hObj The logger object.
      @param logLevel The log level of the message to be (possibly) logged. */
static inline boolean_t log_checkLogLevel(log_logger_t * const hObj, log_logLevel_t logLevel)
    { return (unsigned int)logLevel >= (unsigned int)hObj->logLevel; }
      
#endif  /* LOG_LOGGER_INCLUDED */

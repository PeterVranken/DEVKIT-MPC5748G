/**
 * @file log_logger.c
 *   A simple logging class to write formatted status messages to stdout and into a file.
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
/* Module interface
 *   log_initModule
 *   log_shutdownModule
 *   log_createLogger
 *   log_cloneByReference
 *   log_deleteLogger
 *   log_setEchoToConsole
 *   log_setLogLevel
 *   log_parseLogLevel
 *   log_setLineFormat
 *   log_parseLineFormat
 *   log_getLengthOfLineHeader
 *   log_close
 *   log_getStreams
 *   log_flush
 *   log_log
 *   log_logLine
 * Local functions
 *   logInternal
 */

/*
 * Include files
 */

#include "log_logger.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "types.h"
#include "smalloc.h"
#include "stricmp.h"
#include "snprintf.h"


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

#ifdef DEBUG
/** A global counter of all refernces to any created objects. Used to detect memory leaks. */
static unsigned int _noRefsToObjects = 0;
#endif


/*
 * Function implementation
 */


/**
 * Initialize the module at application startup.
 *   @remark
 * Do not forget to call the counterpart at application end.
 *   @see void log_shutdownModule()
 */

void log_initModule()
{
#ifdef  DEBUG
    /* The DEBUG compilation counts all references to all created objects. */
    _noRefsToObjects = 0;
#endif

#ifdef  DEBUG
    /* Check if patch of snprintf is either not required or properly installed. */
    char buf[3] = {[2] = '\0'};
    snprintf(buf, 2, "%s World", "Hello");
    assert(strlen(buf) == 1);
#endif
} /* End of log_initModule */




/**
 * Do all cleanup after use of the module, which is required to avoid memory leaks, orphaned
 * handles, etc.
 */

void log_shutdownModule()
{
#ifdef  DEBUG
    /* The DEBUG compilation looks for still allocated objects in order to detect memory
       leaks. */
    if(_noRefsToObjects != 0)
    {
        fprintf( stderr
               , "log_shutdownModule: %u references to objects of type log_hLogger_t"
                 " have not been discarded at application shutdown. There are probable"
                 " memory leaks\n"
               , _noRefsToObjects
               );
    }
#endif
} /* End of log_shutdownModule */




/**
 * Create a file logger.
 *   @return
 * The Boolean success is returned. You get false if the file couldn't be opened. Logging
 * can be tried even in case of false: Echoing to the console might still work well.
 *   @param phNewLogger
 * Logger object are used by handles. The handle of the newly created object is returned by
 * reference.
 *   @param fileName
 * The name of the file to write to. Or NULL if no file should be opened.
 *   @param logLevel
 * The amount of status information to actually log.
 *   @param lineFormat
 * The desired format of the header of each logged line. See enumeration log_lineFormat_t
 * for available values.
 *   @param initialEchoToConsole
 * All logged information is written into stdout also if this is set to true.
 *   @param doAppend
 * If true an existing log file is reused and the new status information is appended. The
 * file is deleted and reopened if set to false.
 */

bool log_createLogger( log_hLogger_t * const phNewLogger
                     , const char * const fileName
                     , log_logLevel_t logLevel
                     , log_lineFormat_t lineFormat
                     , bool initialEchoToConsole
                     , bool doAppend
                     )
{
    log_logger_t * const pNewLogger = smalloc(sizeof(log_logger_t), __FILE__, __LINE__);

    pNewLogger->noReferencesToThis = 1;
    pNewLogger->logLevel = logLevel;
    pNewLogger->lineFormat = lineFormat;
    pNewLogger->echoToConsole = initialEchoToConsole;
    pNewLogger->lastFileSystemErr = 0;

    if(fileName != NULL)
    {
        pNewLogger->pLogFile = fopen(fileName, doAppend? "a": "w");
        if(pNewLogger->pLogFile == NULL)
            pNewLogger->lastFileSystemErr = -1; // errno
    }
    else
        pNewLogger->pLogFile = NULL;

#ifdef DEBUG
    ++ _noRefsToObjects;
#endif

    *phNewLogger = pNewLogger;
    return pNewLogger->lastFileSystemErr == 0;

} /* End of log_createLogger */




/**
 * Request a new reference to an existing logger object. The new reference is counted
 * internally for later and safe control of the delete operation.\n
 *   Any requested reference needs to be freed with log_deleteLogger after use.
 *   @return
 * A copy of the passed handle \a hObj is returned.
 *   @param hObj
 * Pointer to the object to be cloned by reference.
 *   @see bool log_createLogger(log_hLogger_t *, const char *const, log_logLevel_t, bool, bool)
 *   @see void log_deleteLOgger(log_hLogger_t)
 */

log_hLogger_t log_cloneByReference(log_hLogger_t hObj)
{
    if(hObj != LOG_HANDLE_TO_EMPTY_LOGGER_OBJECT)
    {
        assert(hObj->noReferencesToThis > 0);

        /* Increment reference counter. */
        ++ hObj->noReferencesToThis;

#ifdef DEBUG
        ++ _noRefsToObjects;
#endif
    }

    return hObj;

} /* End of log_cloneByReference */





/**
 * Delete a reference to a logger object after use. If there are no references left then
 * the object itself is deleted, a potentially open log file is closed and all memory is
 * freed.
 *   @param hObj
 * The handle to the logger object to destroy. No action if this is the null object
 * LOG_HANDLE_TO_EMPTY_LOGGER_OBJECT.
 */

void log_deleteLogger(log_hLogger_t hObj)
{
    if(hObj == LOG_HANDLE_TO_EMPTY_LOGGER_OBJECT)
        return;

    assert(hObj->noReferencesToThis > 0);
    if(--hObj->noReferencesToThis == 0)
    {
        log_close(hObj);
        free(hObj);
    }

#ifdef DEBUG
    -- _noRefsToObjects;
#endif
} /* End of log_deleteLogger */




/**
 * Enable or disable writing all output to the console (stdout) also.
 *   @param hObj
 * The handle to the logger object to operate on.
 *   @param echoToConsole
 * The new value of the flag. True enables echoing.
 */

void log_setEchoToConsole(log_hLogger_t hObj, bool echoToConsole)
{
    hObj->echoToConsole = echoToConsole;

} /* End of log_setEchoToConsole */




/**
 * Set or change the level of verbosity of an existing logger.
 *   @param hObj
 * The handle to the logger object to operate on.
 *   @param logLevel
 * The new value of logLevel. See enumeration log_logLevel_t for available values.
 *   @see void log_parseLogLevel(log_hLogger_t, const char * const)
 */

void log_setLogLevel(log_hLogger_t hObj, log_logLevel_t logLevel)
{
    assert((unsigned int)logLevel <  (unsigned int)log_noLogLevels);
    hObj->logLevel = logLevel;

} /* End of log_setLogLevel */




/**
 * Set or change the level of verbosity of an existing logger. Here, the level is provided
 * as a string. If parsing of this string fails, then the function writes a warning to the
 * log.
 *   @param hObj
 * The handle to the logger object to operate on.
 *   @param logLevelName
 * The new value of logLevel. See enumeration log_logLevel_t for available values. The
 * recognized strings are defined accordingly (without the module suffix log_) and
 * comparison is done case insensitive.
 *   @see void log_setLogLevel(log_hLogger_t, log_logLevel_t)
 */

void log_parseLogLevel(log_hLogger_t hObj, const char * const logLevelName)
{
    assert(logLevelName != NULL);
    
    /* Caution: This table needs to be maintained in close accordance with the enumeration
       of log levels. */
    const char *logLevelAry[] = { [0] = "debug"
                                , [1] = "info"
                                , [2] = "result"
                                , [3] = "warn"
                                , [4] = "error"
                                , [5] = "fatal"
                                };
    const unsigned int noLogLevels = sizeof(logLevelAry)/sizeof(logLevelAry[0]);
    assert(noLogLevels == log_noLogLevels);
    unsigned int logLevel;
    for(logLevel=0; logLevel<noLogLevels; ++logLevel)
    {
        if(stricmp(logLevelName, logLevelAry[logLevel]) == 0)
        {
            log_setLogLevel(hObj, logLevel);
            return;
        }
    }
    
    LOG_WARN( hObj
            , "\"%s\" is not a known logging verbosity level. Verbosity level is not changed"
            , logLevelName
            );

} /* End of log_parseLogLevel */




/**
 * Set or change the line header format of an existing logger.
 *   @param hObj
 * The handle to the logger object to operate on.
 *   @param lineFormat
 * The new value of lineFormat. See enumeration log_lineFormat_t for available values.
 */

void log_setLineFormat(log_hLogger_t hObj, log_lineFormat_t lineFormat)
{
    assert((unsigned int)lineFormat <  (unsigned int)log_noLineFormats);
    hObj->lineFormat = lineFormat;

} /* End of log_setLineFormat */




/**
 * Set or change the line header format of an existing logger. Here, the format is provided
 * as a string. If parsing of this string fails, then the function writes a warning to the
 * log.
 *   @param hObj
 * The handle to the logger object to operate on.
 *   @param lineFormatName
 * The new value of line the header format as a string. See enumeration log_lineFormat_t
 * for available values of the format; the recognized strings are defined accordingly
 * (without the module suffix log_) and comparison is done case insensitive.
 */

void log_parseLineFormat(log_hLogger_t hObj, const char *lineFormatName)
{
    assert(lineFormatName != NULL);
    
    /* Caution: This table needs to be maintained in close accordance with the enumeration
       of line header formats. */
    const char *lineFormatAry[] = { [0] = "raw"
                                  , [1] = "short"
                                  , [2] = "long"
                                  };
    assert(sizeof(lineFormatAry)/sizeof(lineFormatAry[0]) == log_noLineFormats);
             
    unsigned int lineFormat;
    for(lineFormat=0; lineFormat<log_noLineFormats; ++lineFormat)
    {
        if(stricmp(lineFormatName, lineFormatAry[lineFormat]) == 0)
        {
            log_setLineFormat(hObj, lineFormat);
            return;
        }
    }
    
    LOG_WARN( hObj
            , "\"%s\" is not a known line header format. The line header format is not"
              " changed"
            , lineFormatName
            );

} /* End of log_parseLineFormat */




/**
 * The format of the line can be chosen, which means that every line of output is preceeded
 * by a certain header, containing e.g. a time stamp. This function returns the number of
 * characters of the chosen line header.
 *   @return
 * Get the length of the current selected header of the logger.
 *   @param hObj
 * The handle to the logger object to operate on.
 */

unsigned int log_getLengthOfLineHeader(log_logger_t * const hObj)
{
    const unsigned int lenHdrAry[] = { [0] = 0
                                     , [1] = 18
                                     , [2] = 44
                                     };
    assert(sizeof(lenHdrAry)/sizeof(lenHdrAry[0]) == log_noLineFormats
           &&  (unsigned int)hObj->lineFormat < log_noLineFormats
          );
    return lenHdrAry[(unsigned int)hObj->lineFormat];
    
} /* End of log_getLengthOfLineHeader */




/**
 * Close possibly open log file. Use this call before destroying a logger object. (Freeing
 * memory is done by the caller afterwards.)
 *   @param hObj
 * The handle to the logger object to operate on.
 */

bool log_close(log_logger_t * const hObj)
{
    if(hObj->pLogFile != NULL)
    {
        hObj->lastFileSystemErr = fclose(hObj->pLogFile);
        hObj->pLogFile = NULL;
    }
    else
        hObj->lastFileSystemErr = 0;

    return hObj->lastFileSystemErr == 0;

} /* End of log_close */




/**
 * Complex formatted ouput might be easier using the output streams directly. This function
 * reurns the handles of up to two streams: the opened log file and/or the console output.
 * The calling function may use the C stdio functions to write into these streams.\n
 *   The usage of the streams needs to be finished before the class' own output operations
 * are again used (see ).
 *   @param hObj
 * The handle to the logger object to operate on.
 *   @param phConsole
 * The handle of the console output stream is placed in * \a phConsole. Or NULL if no console
 * output takes place. No action if \a phConsole is NULL.
 *   @param phLogFile
 * The handle of the log file stream is placed in * \a phLogFile. Or NULL if no log file
 * has been opened. No action if \a phLogFile is NULL.
 *   @see unsigned int log_log(log_logger_t * const, log_logLevel_t, const
 * char * const, ...)
 *   @see unsigned int log_logLine(log_logger_t * const, log_logLevel_t, const char *
 * const, ...)
 */

void log_getStreams( log_logger_t * const hObj
                   , FILE **phConsole
                   , FILE **phLogFile
                   )
{
    log_flush(hObj);

    if(phConsole != NULL)
    {
        if(hObj->echoToConsole)
            *phConsole = stdout;
        else
            *phConsole = NULL;
    }

    if(phLogFile != NULL)
    {
        if(hObj->pLogFile != NULL)
            *phLogFile = hObj->pLogFile;
        else
            *phLogFile = NULL;
    }
} /* End of log_getStreams */




/**
 * Flush contents of log file buffers.
 *   @param hObj
 * The handle to the logger object to operate on.
 */

void log_flush(log_logger_t * const hObj)
{
    if(hObj->echoToConsole)
        fflush(stdout);
    if(hObj->pLogFile != NULL)
    {
        if(fflush(hObj->pLogFile) != 0)
            hObj->lastFileSystemErr = ferror(hObj->pLogFile);
    }
} /* End of log_flush */





/**
 * Write some logging information to the log file and maybe to stdout also.
 *   @return
 * The number of written characters. If the stdio function return an error this number is
 * not available and this method returns null regardless of possibly written characters.
 *   @param hObj
 * The handle to the logger object to operate on.
 *   @param logLevel
 * The log level (i.e. importance level) of this message.
 *   @param formatString
 * A printf-style format string, which is followed by an argument list of appropriate,
 * variable length.
 *   @param argptr
 * The pointer to the argument list, which may be located in a deeper nested stack frame.
 *   @remark
 * The log level is use only for reporting it does not control whether to write the logging
 * information or not. This is done by a the function call enclosing conditional phrase,
 * which is hidden in a macro.
 */

static unsigned int logInternal( log_logger_t * const hObj
                               , log_logLevel_t logLevel
                               , const char * const formatString
                               , va_list argptr
                               )
{
    assert(hObj != LOG_HANDLE_TO_EMPTY_LOGGER_OBJECT);

    /* Checking the log level and skipping the actual print operation is done outside in a
       preprocessor macro because of speed consideration in conjunction with log level
       DEBUG. */

    /* This array needs to be maintained in accordance with the enumeration
       log_logLevel_t. */
    static const char *logLevelStringAry_[log_noLogLevels] =
    { "DEBUG"
    , "INFO"
    , "RESULT"
    , "WARN"
    , "ERROR"
    , "FATAL"
    };

#define MAX_SIZE_LINE_HDR 128
    bool printHeader = hObj->lineFormat != log_fmtRaw  &&  logLevel != log_continueLine;
    char lineHeader[MAX_SIZE_LINE_HDR+1];
    if(printHeader)
    {
        size_t idxWhere = 0;

        if(hObj->lineFormat == log_fmtLong)
        {
            /* Get current time as string of fixed length. */
            time_t t;
            time(&t);
            const char * const timeStr = ctime(&t);

            /* Copy the time string only partial, we don't need the line feed at the end.
                 +4: Omit day of week. */
            assert(strlen(timeStr) == 25);
            strcpy(lineHeader, timeStr+4);
            /* -1: Overwrite the newline ctime had returned. */
            idxWhere = 25-4-1;
            strcpy(lineHeader+idxWhere, " - ");
            idxWhere += 3;
        }

        /* Convert the CPU time to milli seconds. Normally, it is stated in micro 
           seconds but under Windows MinGW it is returned in milli seconds (and
           actually is the world time not the CPU consumption). More units are not
           supported as POSIX demands micro seconds as only unit. */
        uintmax_t cpuTimeInMs = (uintmax_t)clock()
#if defined(__WINNT__) && (defined(__MINGW32__) || defined(__MINGW64__))
                                ;
        assert(CLOCKS_PER_SEC == (clock_t)1000);
# ifdef __MINGW32__
#  if UINT64_MAX == UINTMAX_MAX
#   define F_MAXU_T "I64u"
#  else
#   error Invalid usage of longest available integer type
#  endif
# else // defined(__MINGW64__)
#  define F_MAXU_T "ju"
# endif
#else // LINUX and other POSIX compliant systems
                                / 1000
                                ;
        assert(CLOCKS_PER_SEC == (clock_t)1000000);
# define F_MAXU_T "ju"
#endif
        assert((int)logLevel >= 0 && (int)logLevel <= (int)log_noLogLevels);
        const char *unitClock = hObj->lineFormat == log_fmtLong? " ms": "";
        snprintf( lineHeader + idxWhere
                , sizeof(lineHeader) - idxWhere
                , "%06" F_MAXU_T "%s - %6s - "
                , cpuTimeInMs
                , unitClock
                , logLevelStringAry_[logLevel]
                );
    } /* End if(Do we need to print a line header?) */
#undef MAX_SIZE_LINE_HDR

    unsigned int noChars = 0;
    bool charsCounted = false;

    if(hObj->echoToConsole)
    {
        if(printHeader)
            fputs(lineHeader, stdout);
        signed int retVFPrintf = vfprintf(stdout, formatString, argptr);

        /* Count the printed characters. Make the distinction between true numbers and
           (negative) error information. */
        if(retVFPrintf >= 0)
        {
            noChars = (unsigned)retVFPrintf;
            if(printHeader)
                noChars += strlen(lineHeader);
        }
        else
            noChars = 0;

        charsCounted = true;

    } /* End if(Logging into stream stdout (console) is active?) */

    hObj->lastFileSystemErr = 0;
    if(hObj->pLogFile != NULL)
    {
        /* Rather than using sprintf once and only the streaming twice, we let printf do
           all the formating once again in order to circumvent to problematic buffer size
           handling of sprintf. Speed is anyway not the most important thing when doing
           formatted logging. */
        if(printHeader &&  fputs(lineHeader, hObj->pLogFile) < 0)
            hObj->lastFileSystemErr = ferror(hObj->pLogFile);
        signed int retVFPrintf = vfprintf(hObj->pLogFile, formatString, argptr);
        if(retVFPrintf < 0)
            hObj->lastFileSystemErr = ferror(hObj->pLogFile);

        /* If we have console outpout the printed characters have already been counted. We
           don't need to repeat this. */
        if(!charsCounted)
        {
            /* Count the printed characters. Make the distinction between true numbers and
               (negative) error information. */
            if(retVFPrintf >= 0)
            {
                noChars = (unsigned)retVFPrintf;
                if(printHeader)
                    noChars += strlen(lineHeader);
            }
            /* else: noChars remains 0 */
        }
    } /* End if(Logging into file stream is active?) */

    return noChars;

} /* End of logInternal */





/**
 * Write some logging information to the log file and maybe to stdout also.\n
 *   Normally you won't call this function directly, but only use the macros offered in the
 * header file. These macros make logging conditional by checking the desired level of
 * verbosity.
 *   @return
 * The number of written characters. If the stdio function return an error this number is
 * not available and this method returns null regardless of possibly written characters.
 *   @param hObj
 * The handle to the logger object to operate on.
 *   @param logLevel
 * The log level (i.e. importance level) of this message.
 *   @param formatString
 * A printf-style format string, which is followed by an argument list of appropriate,
 * variable length.
 *   @remark
 * The log level is used only for reporting it does not control whether to write the logging
 * information or not. This is done by a the function call enclosing conditional phrase,
 * which is hidden in a macro.
 *   @remark
 * This function does not append a newline character to the output as bool log_logLine
 * does.
 *   @see bool log_logLine(log_logger_t * const, log_logLevel_t, const char * const, ...)
 */

unsigned int log_log( log_logger_t * const hObj
                    , log_logLevel_t logLevel
                    , const char * const formatString
                    , ...
                    )
{
    /* Checking the log level and skipping the actual print operation is done outside in a
       preprocessor macro because of speed consideration in conjunction with log level
       DEBUG. */

    va_list argptr;

    va_start(argptr, formatString);

    assert(hObj != LOG_HANDLE_TO_EMPTY_LOGGER_OBJECT);

    unsigned int noChars = logInternal(hObj, logLevel, formatString, argptr);

    va_end(argptr);
    return noChars;

} /* End of log_log */





/**
 * Write some logging information to the log file and maybe to stdout also and terminate
 * output with an appended newline character.\n
 *   Do not call this function directly, only use the macros offered in the header file.
 *   @return
 * The number of written characters. If the stdio function return an error this number is
 * not available and this method returns null regardless of possibly written characters.
 *   @param hObj
 * The handle to the logger object to operate on.
 *   @param logLevel
 * The log level (i.e. importance level) of this message.
 *   @param formatString
 * A printf-style format string, which is followed by an argument list of appropriate,
 * variable length.
 *   @remark
 * The log level is use only for reporting it does not control whether to write the logging
 * information or not. This is done by a the function call enclosing conditional phrase,
 * which is hidden in a macro.
 *   @remark
 * This function will append a newline character to the output. A blank line will appear if
 * \a formatString should end with a newline also.
 *   @see bool log_log(log_logger_t * const, log_logLevel_t, const char * const, ...)
 */

unsigned int log_logLine( log_logger_t * const hObj
                        , log_logLevel_t logLevel
                        , const char * const formatString
                        , ...
                        )
{
    /* Checking the log level and skipping the actual print operation is done outside in a
       preprocessor macro because of speed consideration in conjunction with log level
       DEBUG. */

    va_list argptr;

    va_start(argptr, formatString);

    assert(hObj != LOG_HANDLE_TO_EMPTY_LOGGER_OBJECT);

    unsigned int noChars = logInternal(hObj, logLevel, formatString, argptr);

    /* After actual text output write a line feed character. */
    if(hObj->echoToConsole)
        fputc('\n', stdout);
    if(hObj->pLogFile != NULL  &&  fputc('\n', hObj->pLogFile) == EOF)
            hObj->lastFileSystemErr = ferror(hObj->pLogFile);

    /* Count the added newline character. */
    if(hObj->echoToConsole ||  hObj->pLogFile != NULL)
        ++ noChars;

    va_end(argptr);
    return noChars;

} /* End of log_logLine */

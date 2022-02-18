#ifndef OPT_GETOPT_INCLUDED
#define OPT_GETOPT_INCLUDED
/**
 * @file opt_getOpt.h
 * Definition of global interface of module opt_getOpt.c
 *
 * Copyright (C) 2014 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include "types.h"


/*
 * Defines
 */

/** We can either use the POSIX command line parser \a getopt, which can be used in most C
    environments or the more powerful GNU extension, which will be compilable only with
    GCC. */
#define OPT_USE_POSIX_GETOPT    0


/*
 * Global type definitions
 */

/** The collection of command line options. */
typedef struct opt_cmdLineOptions_t
{
    /** Either help has been demanded or a command line usage error let to the ouput of the
        program help text. */
    bool help;

    /** The revision information has been requested. */
    bool showVersion;

    /** The verbosity level of logging. */
    const char *logLevel;

    /** The name of the log file. */
    const char *logFileName;

    /** The line header format of a log file entry. */
    const char *lineFormat;

    /** Logging is done to the log file and to the console. */
    bool echoToConsole;

    /** Logging output is appended to the (existing) log file. */
    bool doAppend;

    /** The name and path of the output folder. */
    const char *outputPath;

    /** The duration of the simulated time in s. */
    double tiSimEnd;
    
    /** The number of input files. */
    unsigned int noInputFiles;

    /** The index of the first program argument, which designates an input file. Only valid
        if noInputFiles > 0. */
    unsigned int idxFirstInputFile;

} opt_cmdLineOptions_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Parse the command line using the POSIX function getopt with only one character options. */
bool opt_parseCmdLine( opt_cmdLineOptions_t * const pCmdLineOptions
                     , signed int argc
                     , char *argv[]
                     );

#ifdef DEBUG
/** Print the parsed user input in a formatted way. */
void opt_echoUserInput(FILE *stream, const opt_cmdLineOptions_t * const pCmdLineOptions);
#endif /* DEBUG */

#endif  /* OPT_GETOPT_INCLUDED */

#ifndef MAIN_INCLUDED
#define MAIN_INCLUDED
/**
 * @file main.h
 * Definition of global interface of module main.c
 *
 * Copyright (C) 2015 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
#include "log_logger.h"


/*
 * Defines
 */

/** The application name. */
#define MAIN_APP_NAME        "canInterfaceDemo"

/** The printable long name of the application. */
#define MAIN_APP_GREETING    "comFramework - canInterface Demonstration"

/** The revision. */
#define MAIN_SW_REV      "0.1.0"

/** The name of the application's executable file. */
#ifdef __WINNT__
# define MAIN_APP_FILE_NAME  MAIN_APP_NAME ".exe"
#else
# define MAIN_APP_FILE_NAME  MAIN_APP_NAME
#endif

/** The extension for names of log files. */
#define MAIN_LOG_FILE_NAME_EXT   ".log"

/** The name of the application's default log file name. */
#define MAIN_LOG_FILE_NAME       MAIN_APP_NAME MAIN_LOG_FILE_NAME_EXT


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** A global logger object, which can be referenced from anywhere for writing progress
    messages. */
extern log_hLogger_t main_hGlobalLogger;


/*
 * Global prototypes
 */

/** Main function of application. */
signed int main(signed int argc, char *argv[]);


#endif  /* MAIN_INCLUDED */

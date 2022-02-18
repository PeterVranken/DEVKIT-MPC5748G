#ifndef SUP_INCLUDED
#define SUP_INCLUDED
/**
 * @file main.h
 * Definition of global interface of module main.c
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

/*
 * Include files
 */

#include "types.h"
#include "log_logger.h"
#include "rtos_rtosEmulation.h"


/*
 * Defines
 */

/** The application name. */
#define SUP_APP_NAME        "canInterfaceMTTest"

/** The printable long name of the application. */
#define SUP_APP_GREETING    "comFramework - canInterface Multithreaded Test"

/** The revision. */
#define SUP_SW_REV          "0.2.0"

/** The name of the application's executable file. */
#ifdef __WINNT__
# define SUP_APP_FILE_NAME  SUP_APP_NAME ".exe"
#else
# define SUP_APP_FILE_NAME  SUP_APP_NAME
#endif

/** The extension for names of log files. */
#define SUP_LOG_FILE_NAME_EXT   ".log"

/** The name of the application's default log file name. */
#define SUP_LOG_FILE_NAME       SUP_APP_NAME SUP_LOG_FILE_NAME_EXT


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** The fundamental entry point into the APSW is defined by this function pointer. It is
    external to the operating system emulation and needs to be instantiated in the APSW
    code. The designated function will be executed as part of the system startup. The
    invokation happens in a race-condition free, single-threaded context. The
    implementation of the executed function gives the APSW the chance to do all further
    initialization, which is - with respect to the operating system - the definition of the
    required threads and task functions.
      @remark No APSW code is executed prior to the function specified here. This means
    that the only chance of the APSW to assign a value to the function pointer is a
    constant initializer expression. This is supported by making the pointer variable a
    constant. */
extern rtos_taskFctResult_t (* const sup_initAPSW)();

/** A global logger object, which can be referenced from anywhere for writing progress
    messages. */
extern log_hLogger_t sup_hGlobalLogger;


/*
 * Global prototypes
 */

/** Main function of application. */
signed int main(signed int argc, char *argv[]);


#endif  /* SUP_INCLUDED */

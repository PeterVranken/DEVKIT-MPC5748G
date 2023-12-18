/**
 * @file ipa_ipApplications.c
 * This is the entry point into the IP applications, based on the lwIP, which are provided
 * by this DEVKIT-MPC5748G sample application.\n
 *   Note, since the lwIP API is based on callbacks, the entry into those application is
 * barely more than their initialization. During initialization, all required callbacks are
 * specified and this will keep the applications running without further, visible API
 * calls.
 *
 * Copyright (C) 2023 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   ipa_initLwIPApplications
 * Local functions
 */

/*
 * Include files
 */

#include "ipa_ipApplications.h"

#include "tftp_example.h"
#include "http_demoHttpServer.h"

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
 
 
/*
 * Function implementation
 */


/**
 * This function initializes all lwIP applications provided by our sample.
 */
void ipa_initLwIPApplications(void)
{
    /* Initialize the TFTP server. */
    tftp_example_init_server();

    /* Initialize the most simple HTTP server example from the lwIP manual. */
    http_init();

} /* ipa_initLwIPApplications */

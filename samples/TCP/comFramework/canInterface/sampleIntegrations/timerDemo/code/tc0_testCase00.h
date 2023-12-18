#ifndef TC0_TESTCASE00_INCLUDED
#define TC0_TESTCASE00_INCLUDED
/**
 * @file tc0_testCase00.h
 * Definition of global interface of module tc0_testCase00.c
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
#include "ede_eventDispatcherEngine.h"


/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */

/** Signal to the main scheduler loop to end this test. */
extern bool tc0_endOfTest;
 

/*
 * Global prototypes
 */

/** Initialization of test. */
void tc0_initTest(const ede_callbackContext_t *ctx);


#endif  /* TC0_TESTCASE00_INCLUDED */

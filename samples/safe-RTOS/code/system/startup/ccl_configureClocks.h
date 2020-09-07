#ifndef CCL_CONFIGURECLOCKS_INCLUDED
#define CCL_CONFIGURECLOCKS_INCLUDED
/**
 * @file ccl_configureClocks.h
 * Definition of global interface of module ccl_configureClocks.c
 *
 * Copyright (C) 2018-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */

/** The clock frequency of the external crystal oscillator. */
#define CCL_XTAL_CLK    40000000u

/** The core clock rate PHI_0 in Hz. See MCU reference manual, section 9.9.1, Figure
    9-16, p. 223f, and 9.9.1.2. */
#define CCL_PHI_0_CLK   160000000u

/** The system or CPU core clock. */
#define CCL_CORE_CLK    CCL_PHI_0_CLK

/** The core clock rate PHI_1 in Hz. See MCU reference manual, section 9.9.1, Figure
    9-16, p. 223f, and 9.9.1.2. */
#define CCL_PHI_1_CLK   (CCL_PHI_0_CLK/2u)

/// @todo Complete the clock rate definitions


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Perform a mode transition of the micro controller towards DRUN. */
void ccl_triggerTransitionToModeDRUN(void);

/** Configure all clocks as appropriate for the DEVKIT-MPC5748G. */
void ccl_configureClocks(void);

#endif  /* CCL_CONFIGURECLOCKS_INCLUDED */

/**
 * @file stm_systemTimer.c
 * Configuration of the System Timer module for high resolution, short time measurements
 * and initialization of the timers. A little API permits reading the three core related
 * timers.
 *
 * Copyright (C) 2019 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   stm_initSystemTimers
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "stm_systemTimer.h"


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
 * Configuration and initialization of the three system timers. The three timers are
 * intended for use by the three cores but there's no restriction in reading the timers
 * from another core. The configuration lets the timers count at highest possible speed to
 * support high resolution, short time measurements. The maximum duration of measurable time
 * spans is about 53s.
 */
void stm_initSystemTimers(void)
{
    /* The configuration of all three timers is identical and we use a macro to avoid code
       duplication.
         RM, 54.4.1, p. 2778: STM Control Register (STM_CR) to define divider and enable
       the timer.
         Flag FRZ, stop-timer-on-debug, is difficult to decide. In some situations it's
       useful, in others it's hindering. For FRZ=1 and if the debugger halts only one of
       the three cores then all the timers are immediately stopped. The code of the still
       running other cores will likely fail if it depends on a timer, too. */
#define INIT_SYS_TIMER(idxTimer)                                                            \
    STM_##idxTimer->CR = STM_CR_CPS(0u)     /* Divide clock by n+1 */                       \
                        | STM_CR_CSL(0u)    /* 0: System clock, 1: FXOSC */                 \
                        | STM_CR_FRZ(0u)    /* 0: Count while debugger active, 1: Stop */   \
                                            /* when debugging */                            \
                        | STM_CR_TEN(1u);   /* 1: Enable the timer. */

    INIT_SYS_TIMER(0)
    INIT_SYS_TIMER(1)
    INIT_SYS_TIMER(2)
#undef INIT_SYS_TIMER

    /* The timers are now running at 80 MHz. (See RM, 9.4.4.3, STM clocking, p. 213.) */

} /* End of stm_initSystemTimers */





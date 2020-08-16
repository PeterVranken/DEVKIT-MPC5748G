/**
 * @file stm_systemTimer.c
 * Configuration of the System Timer module for high resolution, short time measurements
 * and initialization of the timers. A little API permits reading the three core related
 * timers.
 *
 * Copyright (C) 2019-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   stm_osInitSystemTimers
 * Local functions
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "rtos.h"
#include "ccl_configureClocks.h"
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
 * from another core. Our configuration lets the timers count at different speeds to
 * support high resolution for short time measurements and low resolution measurements of
 * longer time spans.\n
 *   The maximum duration of time spans measurable with highest resolution is about 53s
 * (timer index 0).\n
 *   The longest measurable time span is 3.8h with lowest resolution (timer index 2).\n
 *   The medium timer (index 1) has a resolution of 200ns, which is best suited for
 * rescaling measured times into human readable representation.
 *   @remark
 * CAUTION: On the MPC5748G, the configuration of the STM device is not a user changeable
 * option but an essential prerequisite for running safe-RTOS. The MPC5748G has a
 * simplified Z4 core without the timebase feature. The system timer STM_0 is used as
 * substitute. This I/O driver needs to be started and it must be neither changed nor
 * re-configured without carefully double-checking the side-effects on the kernel!
 */
void stm_osInitSystemTimers(void)
{
    /* Some compile time checks will help to keep the static definitions in the header file
       consistent with the actual configuration made here. */
    _Static_assert( 2*STM_TIMER_0_CLK == CCL_PHI_0_CLK
                    &&  ((double)STM_TIMER_0_CLK * STM_TIMER_0_PERIOD_IN_NS * 1e-9) == 1.0
                    &&  ((double)STM_TIMER_1_CLK * STM_TIMER_1_PERIOD_IN_NS * 1e-9) == 1.0
                    &&  ((double)STM_TIMER_2_CLK * STM_TIMER_2_PERIOD_IN_NS * 1e-9) == 1.0
                  , "Inconsistencies found between public header file and actual clock"
                    " configuration"
                  );

    /* The configuration of all three timers is identical and we use macros to avoid code
       duplication. The strategy is to configure all three timers with diable interrupts so
       that all registers are written nearly coincidental. By spitting the configuration
       into different stepy we can achieve that timer enabling is done as close in time as
       possible for all three timers. Which still dosen't guarantee synchronous counting.
         RM, 54.4.1, p. 2778: STM Control Register (STM_CR) to define divider and enable
       the timer.
         Flag FRZ, stop-timer-on-debug, is difficult to decide. In some situations it's
       useful, in others it's hindering. For FRZ=1 and if the debugger halts only one of
       the three cores then all the timers are immediately stopped. The code of the still
       running other cores will likely fail if it depends on a timer, too. */
    /// @todo To further improve the synchronicity of the three timers, we could offer not
    // to reset the counter register as a function argument. When coming out of a power-on
    // reset we would then not make use of the reset but rely on the power-on HW reset
    // value zeros
#define DISABLE_SYS_TIMER(idxTimer)                                                         \
    STM_##idxTimer->CR &= ~STM_CR_TEN_MASK; /* Disable the timer. */

#define CONFIG_AND_ENABLE_SYS_TIMER(idxTimer, divideSysClkBy)                               \
    STM_##idxTimer->CR = STM_CR_CPS((divideSysClkBy)-1)     /* Divide clock by n+1 */       \
                        | STM_CR_CSL(0u)    /* 0: System clock, 1: FXOSC */                 \
                        | STM_CR_FRZ(1u)    /* 0: Count while debugger active, 1: Stop */   \
                                            /* when debugging */                            \
                        | STM_CR_TEN(1u);   /* 1: Enable the timer. */

#define RESET_COUNTER(idxTimer)                                                             \
    STM_##idxTimer->CNT = STM_CNT_CNT(0u);  /* Counter value reset to zero. */

    uint32_t msr = rtos_osEnterCriticalSection();

    DISABLE_SYS_TIMER(/* idxTimer */ 0)
    DISABLE_SYS_TIMER(/* idxTimer */ 1)
    DISABLE_SYS_TIMER(/* idxTimer */ 2)
    RESET_COUNTER(0)
    RESET_COUNTER(1)
    RESET_COUNTER(2)
    CONFIG_AND_ENABLE_SYS_TIMER(0, /* divideSysClkBy */ 1 /* 80 Mhz, 12.5 ns, 53.7 s */)
    CONFIG_AND_ENABLE_SYS_TIMER(1, /* divideSysClkBy */ 16 /* 5 Mhz, 200 ns, 14.3 min */)
    CONFIG_AND_ENABLE_SYS_TIMER(2, /* divideSysClkBy */ 256 /* 312500 Hz, 3.2us, 3.8 h */)

    rtos_osLeaveCriticalSection(msr);

#undef DISABLE_SYS_TIMER
#undef CONFIG_AND_ENABLE_SYS_TIMER
#undef RESET_COUNTER

    /* The timers are now running at 80 MHz. (See RM, 9.4.4.3, STM clocking, p. 213.) */

} /* End of stm_osInitSystemTimers */





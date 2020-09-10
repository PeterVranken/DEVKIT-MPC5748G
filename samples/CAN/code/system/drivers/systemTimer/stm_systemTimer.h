#ifndef STM_SYSTEMTIMER_INCLUDED
#define STM_SYSTEMTIMER_INCLUDED
/**
 * @file stm_systemTimer.h
 * Definition of global interface of module stm_systemTimer.c
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

/*
 * Include files
 */

#ifdef __STDC_VERSION__
# include <stdint.h>
# include <stdbool.h>

# include "MPC5748G.h"
#endif

/*
 * Defines
 */

/** The frequency at which the STM0 timer counts. */
#define STM_TIMER_0_CLK             80000000

#ifdef __STDC_VERSION__
/** The unit of a counter tick of system timer STM0. The value is meant in ns. */
#define STM_TIMER_0_PERIOD_IN_NS    12.5f
#endif

/** The frequency at which the ST01 timer counts. */
#define STM_TIMER_1_CLK             5000000

/** The unit of a counter tick of system timer STM1. The value is meant in ns. */
#define STM_TIMER_1_PERIOD_IN_NS    200

/** The frequency at which the STM2 timer counts. */
#define STM_TIMER_2_CLK             312500

/** The unit of a counter tick of system timer STM2. The value is meant in ns. */
#define STM_TIMER_2_PERIOD_IN_NS    3200

/** Index of implemented system call for reading the current system time. */
#define STM_SYSCALL_GET_SYSTEM_TIME 30


#ifdef __STDC_VERSION__
/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global inline functions
 */

/**
 * Read one of the three system timers. The function can be called at any time from any
 * context on any core. It must not be called before stm_initSystemTimers() has completed.
 *   @return
 * The timers are running at #STM_TIMER_0_CLK, #STM_TIMER_1_CLK and #STM_TIMER_2_CLK Hz (80
 * MHz each). The unit of one step of the counter value is the reciprocal, i.e. 12.5 ns.
 * The timers wrap at 2^32-1. This limits measurable time spans to 2^32 * 12.5ns = 53.6s.
 *   @param idxTimer
 * The index of the timer in the range 0..2. Our configuration lets the timers count at
 * different speeds to support high resolution for short time measurements and low
 * resolution measurements of longer time spans.\n
 *   The maximum duration of time spans measurable with highest resolution is about 53s
 * (timer index 0).\n
 *   The longest measurable time span is 3.8h with lowest resolution (timer index 2).\n
 *   The medium timer (index 1) has a resolution of 200ns, which is best suited for
 * rescaling measured times into human readable representation.
 *   @remark
 * This function is available solely to OS tasks and ISRs. User code would cause a memory
 * protection exception. User mode code uses stm_getSytemTime() instead.
 *   @remark
 * This function is available to code running on any core, regardless whether safe-RTOS is
 * configured and running on that core or not.
 */
static inline uint32_t stm_osGetSystemTime(unsigned int idxTimer)
{
    /* This function is typically used for measurement of short execution times. Therefore
       the parameter range check is not done. */
    //assert(idxTimer <= 2);
    
    /* RM, 54.4.2, p. 2779: STM Count Register (STM_CNT): Read current timer value as SW
       independent world time. */
    const static STM_Type *pTimerAry[3] = STM_BASE_PTRS;
    return pTimerAry[idxTimer]->CNT;
    
} /* End of stm_osGetSystemTime */


/*
 * Global prototypes
 */

/** Configuration and initialization of the three system timers. */
void stm_osInitSystemTimers(void);

/**
 *   @func stm_getSystemTime
 * Get the counter value from one of the three free running, cyclically counting system
 * timers.
 *   @return
 * Get the current counter value, which represents the system time. See
 * #STM_TIMER_0_PERIOD_IN_NS, #STM_TIMER_1_PERIOD_IN_NS and #STM_TIMER_2_PERIOD_IN_NS for
 * the units.
 *   @param idxStmTimer
 * The index of the STM system timer counter to read. The value is in the range 0..2.
 *   @remark
 * The function must be called from user tasks only. Supervisor code (OS tasks and ISRs)
 * will instead call the equivalent function stm_osGetSystemTime().
 */
uint32_t stm_getSystemTime(unsigned int idxStmTimer);

#endif /* End of C only part of file */
#endif /* STM_SYSTEMTIMER_INCLUDED */

#ifndef STM_SYSTEMTIMER_INCLUDED
#define STM_SYSTEMTIMER_INCLUDED
/**
 * @file stm_systemTimer.h
 * Definition of global interface of module stm_systemTimer.c
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

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>


/*
 * Defines
 */


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
 * The timers are running at 80 MHz. The unit of one step of the counter value is the
 * reciprocal, i.e. 12.5 ns. The timers wrap at 2^32-1. This limits measurable time spans to
 * 2^32 * 12.5ns = 53.6s.
 *   @param idxTimer
 * The index of the timer in the range 0..2. By intention, core i should make use of timer
 * i, but there's no technical restriction in calling timer i from core j, i!=j.
 */
static inline uint32_t stm_getTimerValue(unsigned int idxTimer)
{
    /* This function is typically used for measurement of short execution times. Therefore
       the parameter range check is not done. */
    //assert(idxTimer <= 2);
    
    /* RM, 54.4.2, p. 2779: STM Count Register (STM_CNT): Read current timer value as SW
       independent world time. */
    const static STM_Type *pTimerAry[3] = STM_BASE_PTRS;
    return pTimerAry[idxTimer]->CNT;
    
} /* End of stm_getTimerValue */


/*
 * Global prototypes
 */

/** Configuration and initialization of the three system timers. */
void stm_initSystemTimers(void);


#endif  /* STM_SYSTEMTIMER_INCLUDED */

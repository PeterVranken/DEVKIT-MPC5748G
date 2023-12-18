/**
 * @file sys_arch.c
 * Some basic timing functions, which are platform dependently implemented but need to be
 * provided to lwIP.
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
 * Local functions
 */

/*
 * Include files
 */

#include "arch/sys_arch.h"

#include "typ_types.h"

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/stats.h"
#include "lwip/debug.h"
#include "lwip/sys.h"

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
 * Initialize sys arch layer. To be called when lwIP is started up.
 */
void sys_init(void)
{}


/**
 * Ticks/jiffies since power up.
 *   @return
 * Get the number of counter ticks since system startup, without a specific unit.
 * However, the returned numbers are strictly monotonic -- until they wrap at the
 * implementation maximum.
 */
u32_t sys_jiffies(void)
{
    return stm_getSystemTime(2u);
}


/**
 * Returns the current time in Milliseconds.
 *   @return
 * Get the number of Milliseconds elapsed since system startup.
 *   @remark
 * The implementation is not thread-safe and must never be used from competing contexts. The
 * intended context is the lwIP task, running the IP stack. Other contexts may use it, too,
 * but only if they guarantee mutual exclusion with the lwIP task.
 */
u32_t sys_now(void)
{
    const uint32_t tiNowIn3200ns = stm_getSystemTime(2u);
    static uint32_t SBSS_P1(tiConsumedIn3200ns_) = 0u;
    static uint32_t SBSS_P1(tiReportedInMs_last_) = 0u;

    /* Scaling make use of 1000*3200ns = 2/625, which is valid only for a particular
       counter clock frequency. */
    _Static_assert(STM_TIMER_2_PERIOD_IN_NS == 3200u, "Bad timer scaling");

    const uint32_t tiDeltaIn3200ns = tiNowIn3200ns - tiConsumedIn3200ns_;
    const uint32_t tiDeltaIn2ms = tiDeltaIn3200ns / 625u;
    tiConsumedIn3200ns_ += tiDeltaIn2ms * 625u;

    assert(tiDeltaIn2ms < 0x80000000u);
    const uint32_t tiReportedInMs = tiReportedInMs_last_ + 2u * tiDeltaIn2ms;
    tiReportedInMs_last_ = tiReportedInMs;

    return tiReportedInMs;

} /* sys_now */

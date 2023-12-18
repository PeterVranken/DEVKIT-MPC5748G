#ifndef RCF_RTMCONFIG_INCLUDED
#define RCF_RTMCONFIG_INCLUDED
/**
 * @file rcf_rtmConfig.h
 * Global configuration settings for the compilation of the NXP RTM code and some
 * interfacing code to connect the RTM implementation of the Ethernet driver to our
 * environment.
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

/*
 * Include files
 */
/** The RTM code can be compiled for many derivatives from the MCU families by NXP. This
    defines selects the MCU to build for in this project. The definition controls, which
    elements to pick from the included headers, so it must precede the include
    directives. */
#define CPU_MPC5748G

#include "typ_types.h"
#include "stm_systemTimer.h"

/*
 * Defines
 */
 
/** The RTM code is prepared to run on architectures with either endianess. We need to
    specify, which one we have in our environment. Define to either #CORE_BIG_ENDIAN or
    #CORE_LITTLE_ENDIAN. */
#define CORE_BIG_ENDIAN

/** The left hand side of an include directive. If defined then the header is included and
    expected to define DEV_ASSERT(invariant), when invariant is a Boolean condition,
    expected to be always true. */
#define CUSTOM_DEVASSERT    <assert.h>

/** The assert macro to use for the compilation of the RTM code. */
#define DEV_ASSERT(invariant)   (assert(invariant))

/** The timeout designations in the ETH driver are defined in clock ticks of some hardware
    counter. This macro calculates the number of counter increments, which yields a time
    span given in Milliseconds. 
      @note On the DEVKIT-MPC5748G, we use the STM counter 2, which increments a 32 Bit
    value every 3200ns. 3200ns = 1 ms / (625/2); this enables a simple rescaling. */
#if STM_TIMER_2_PERIOD_IN_NS == 3200
# define RCF_MS_TO_TICKS(tiInMs) \
            (DEV_ASSERT((unsigned)(tiInMs)<=6871947u), ((unsigned)(tiInMs)*625u+1u)/2u)
#else
# error Define hardware timer clock tick for your platform
#endif

/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */

/**
 * Get the time since system startup in counter ticks.
 *   @return
 * The system time is returned in units of 3.2us. The time is linear until the
 * implementation limit is reached, then it'll wrap to zero.
 */
static inline uint32_t rcf_getSystemTime(void)
{
    return stm_osGetSystemTime(2u);
}    


#endif  /* RCF_RTMCONFIG_INCLUDED */

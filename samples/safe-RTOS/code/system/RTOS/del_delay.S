/**
 * @file del_delay.S
 * The CPU load measurement requires a defined delay time in terms of CPU execution clock
 * ticks (as opposed to elapsing world time under control of an independent clock). This
 * unit implements function void del_delayMicroseconds(unsigned int tiCpuInUs) which
 * implements busy wait of a defined duration.
 *
 * Copyright (C) 2017-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   del_delayMicroseconds
 * Local functions
 */

/*
 * Include files
 */

#include "hwc_hardwareConfiguration.h"


/*
 * Defines
 */


/*
 * External function declarations
 */



/*
 * Data declarations
 */


/*
 * Function implementation
 */


/**
 *   @func del_delayMicroseconds
 * This function does nothing but consumes an exactely determined amount of CPU execution
 * time before it returns. "Consumption of CPU time" means that not the elapsed world time
 * counts; all interrupts etc. which interrupt the execution of this function won't be
 * accounted. The blocking time of this function until return therefore is greater or
 * equal to \a tiCpuInUs Microseconds.
 *   @param r3
 * r3, 32 Bit, "tiCpuInUs": The CPU executes further useless code this number of
 * Microseconds.
 *   @remark
 * Note, if the I-cache is enabled then we get a dependency of the execution time on the
 * number of preemptions. Each preemption involves the risk of re-filling the cache with
 * the loop code after return from the preemption. This makes the actual delay rise with
 * higher system load: We will see many more interrupts and/or context switches of an RTOS
 * until all cycles are done. As a consequence, the other module gsl_systemLoad.c, which
 * builds on function del_delayMicroseconds(), will tend to indicate a too high CPU load,
 * the more the higher the load becomes. We've no experience how strong this effect
 * actually is.\n
 *   A solution would be loading this unit into an uncached memory section. However, the
 * price for shaping such an area is much too high (one or more table entries in the MMU,
 * waste of cached space due to minimum area size and the area's block size alignment
 * constraints).
 *   @remark The implementation is done in assembler in order to keep the execution time
 * independent of the compiler's optimization settings; particularly the compile
 * configuration DEBUG/PRODUCTION. Furthermore, the execution time needs to be kept clear
 * of load address caused variances, which can be controlled only in an assembly module.
 *   @remark
 * This function can be called from user and supervisor mode.
 */
    .section    .text.del_delayMicroseconds
    .global     del_delayMicroseconds, del_loopDelayMicroseconds
    
    /* The alignment of the function code is an important element of the
       implementation. The loop code must be inside a 64 Bit word because of the 64 Bit
       address bus for fetching instructions. Otherwise the execution time rises and the
       timing calibration fails.
         The alignment is ensured by the .balignw in combination with the nop instructions
       and can be double checked in the map file; therefore, we've made
       del_loopDelayMicroseconds a global symbol. */

del_delayMicroseconds:

#ifdef __VLE__
# if defined(LINK_IN_RAM)
#  if HWC_ENABLE_ICACHE && HWC_ENABLE_BRANCH_PREDICTION
#   define NO_CYCLES_PER_US     80.0    /* Code in RAM, I-cache and branch prediction on. */
#   define NO_CYCLES_OFFSET     18
#  elif !HWC_ENABLE_ICACHE && HWC_ENABLE_BRANCH_PREDICTION
/// @todo This case is suspicious, needs review
#   define NO_CYCLES_PER_US     22.857  /* Code in RAM, I-cache off, branch prediction on. */
#   define NO_CYCLES_OFFSET     21
#  endif
# else /* Code in flash ROM */
#  if HWC_ENABLE_ICACHE && HWC_ENABLE_BRANCH_PREDICTION
#   define NO_CYCLES_PER_US     80.0   /* Code in ROM, I-cache and branch prediction on. */
#   define NO_CYCLES_OFFSET     18
#  elif !HWC_ENABLE_ICACHE && HWC_ENABLE_BRANCH_PREDICTION
/// @todo This case is still bad, needs calibration
#   define NO_CYCLES_PER_US     22.857 /* Code in ROM, I-cache off, branch prediction on. */
#   define NO_CYCLES_OFFSET     21
#  endif
# endif
# ifndef NO_CYCLES_PER_US
#  error Module del_delay.S needs calibration for chosen configuration
# endif

    /* Rescale us to number of busy wait loops (see below). */
    efscfui     r3, r3      /* r3: noMicroSec as float32_t */
    e_lis       r4, facNoCyclesPerMicroSec@ha       /* GNU as doesn't know floating point */
    e_lwz       r4, facNoCyclesPerMicroSec@l(r4)    /* literals, we need to load a const */
    efsmul      r3, r3, r4  /* r3: noMicroSec*facNoCyclesPerMicroSec as float32_t */
    efsctui     r3, r3      /* r3: noCycles as uint32, rounded to nearest, saturated */

    /* Compensate for overhead, like this code and function call. */
    e_cmpl16i   r3, NO_CYCLES_OFFSET    /* Overhead compensation possible? */
    se_ble      exitDelayMicroseconds   /* Wanted busy wait less than overhead: done */
# if NO_CYCLES_OFFSET >= 1
    e_add16i    r3, r3, -NO_CYCLES_OFFSET /* Consider overhead. Range NO_CYCLES_OFFSET: >= 1 */
#elif NO_CYCLES_OFFSET != 0
#   error NO_CYCLES_OFFSET is out of range
#endif

    /* The code for the busy wait loop must be inside a 64 Bit word because of the 64 Bit
       address bus for fetching instructions and inside a 32 Byte block because this is the
       size of an instruction cache block. Otherwise the execution time rises and the
       timing calibration fails depending on the load address of the unit.
         The loop code has only 6 Byte so the first condition ensures already the second
       one.
         The alignment is ensured by the .balignw in combination with nop instructions
       and can be double checked in the map file; therefore, we've made
       del_loopDelayMicroseconds a global symbol. */
    .balignw    8, 0x4400   /* Ensure alignment of loop code on 8 Byte address using fill
                               pattern "se_nop" */
del_loopDelayMicroseconds:
    e_add2i.    r3, -1
    se_bne      del_loopDelayMicroseconds

exitDelayMicroseconds:
    se_blr

    .section    .rodata.facNoCyclesPerMicroSec
    .balign     4
facNoCyclesPerMicroSec:
    .float      NO_CYCLES_PER_US
    
# undef NO_CYCLES_PER_US
#else
# error Book E instruction set is no longer supported!
#endif

/* End of del_delayMicroseconds */

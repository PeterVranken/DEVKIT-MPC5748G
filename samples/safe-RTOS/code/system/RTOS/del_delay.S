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

#ifndef __VLE__
# error Book E instruction set is not supported by this module!
#endif

/*
 * Include files
 */

#include "hwc_hardwareConfiguration.h"
#include "rtos_ivorHandler.h"


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


    /* Calibration of delay cycles for Z4. The Z4 cores have I- and D-cache and branch
       prediction as speed affecting configuration items. We need a set of calibration
       values for each relevant combination of configuration items. */
#if defined(LINK_IN_RAM)
# if HWC_ENABLE_ICACHE && HWC_ENABLE_BRANCH_PREDICTION
#  define NO_CYCLES_PER_US_Z4   80.0   /* Z4 code in RAM, I-cache and branch prediction on. */
#  define NO_CYCLES_OFFSET_Z4   27
# elif !HWC_ENABLE_ICACHE && HWC_ENABLE_BRANCH_PREDICTION
#  define NO_CYCLES_PER_US_Z4   22.857 /* Z4 code in RAM, I-cache off, branch prediction on. */
#  define NO_CYCLES_OFFSET_Z4   7 
# endif
#else /* Code in flash ROM */
# if HWC_ENABLE_ICACHE && HWC_ENABLE_BRANCH_PREDICTION
#  define NO_CYCLES_PER_US_Z4   80.0   /* Z4 Code in ROM, I-cache and branch prediction on. */
#  define NO_CYCLES_OFFSET_Z4   27
# elif !HWC_ENABLE_ICACHE && HWC_ENABLE_BRANCH_PREDICTION
#  define NO_CYCLES_PER_US_Z4   40.0   /* Z4 Code in ROM, I-cache off, branch prediction on. */
#  define NO_CYCLES_OFFSET_Z4   24
# endif
#endif

    /* Calibration of delay cycles for Z2. The Z2 core runs at half the clock speed and it
       doesn't have I- and D-cache. This reduces the number of cases. ROM and RAM access
       are as fast. The branch prediction unit is available and would make a difference. */
#if HWC_ENABLE_BRANCH_PREDICTION
# define NO_CYCLES_PER_US_Z2    20
# define NO_CYCLES_OFFSET_Z2    18
#endif

#if !defined(NO_CYCLES_PER_US_Z4) || !defined(NO_CYCLES_PER_US_Z2) \
    ||  NO_CYCLES_PER_US_Z2 >= 0x8000  ||  NO_CYCLES_OFFSET_Z4 < 0  ||  NO_CYCLES_OFFSET_Z2 < 0
# error Module del_delay.S needs calibration for chosen configuration
#endif

    /* Define the stack frame contents as offsets of data objects. Note the minimum offset
       of 8 due to the storage of stack pointer and link register. */
    #define O_TI_DEL        (8+0)
    #define SIZE_OF_PAYLOAD 4  /* Size of user data in stack frame */

    /* Size of stack frame: Room for SP and LR and uprounding to multiple of 8. */
    #define SIZE_OF_SF  ((((SIZE_OF_PAYLOAD)+15)/8)*8)
    #define O_LR        (SIZE_OF_SF+4)

    /* Create stack frame and save stack pointer and return address. */
    e_stwu      sp, -SIZE_OF_SF(sp)
    se_mflr     r0
    #if O_LR <= 60
    se_stw      r0, O_LR(sp)
    #else
    e_stw       r0, O_LR(sp)
    #endif

    /* On the MPC5748G, the implementation needs to be core specific: The clock rates and
       the instruction sets differ (no EFPU on Z2). */
    .extern     rtos_getIdxCore
    se_stw      r3, O_TI_DEL(sp)
    e_bl        rtos_getIdxCore     /* r3: Contents of PIR */
    se_cmpli    r3, 2
    se_lwz      r3, O_TI_DEL(sp)
#ifdef DEBUG
    se_bgt      .           /* assert(idxCore <= 2); */
#endif
    se_beq      del_entryZ2

    /* Rescale us to number of busy wait loops on a Z4 core. */
    efscfui     r0, r3      /* r0: noMicroSec as float32_t */
    e_lis       r3, facNoCyclesPerMicroSec@ha       /* GNU as doesn't know floating point */
    e_lwz       r3, facNoCyclesPerMicroSec@l(r3)    /* literals, we need to load a const */
    efsmul      r3, r0, r3  /* r3: noMicroSec*facNoCyclesPerMicroSec as float32_t */
    efsctui     r3, r3      /* r3: noCycles as uint32, rounded to nearest, saturated */
    /* Compensate for overhead, like this code and function call. */
    e_cmpl16i   r3, NO_CYCLES_OFFSET_Z4 /* Overhead compensation possible? */
    se_ble      exitDelayMicroseconds   /* Wanted busy wait less than overhead: done */
#if NO_CYCLES_OFFSET_Z4 >= 1
    e_add16i    r3, r3, -NO_CYCLES_OFFSET_Z4    /* Consider overhead. Range
                                                   NO_CYCLES_OFFSET_Z4: >= 1 */
#endif
    se_b        del_delay

del_entryZ2:
    /* Rescale us to number of busy wait loops on the Z2 core. */
    e_mull2i    r3, NO_CYCLES_PER_US_Z2
    e_cmpl16i   r3, NO_CYCLES_OFFSET_Z2 /* Overhead compensation possible? */
    se_ble      exitDelayMicroseconds   /* Wanted busy wait less than overhead: done */
#if NO_CYCLES_OFFSET_Z2 >= 1
    e_add16i    r3, r3, -NO_CYCLES_OFFSET_Z2 /* Consider overhead. NO_CYCLES_OFFSET_Z2 >= 1 */
#endif
    
    /* Both cores starts here with the delay, having the number of delay cycles in r3. */
del_delay:

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
    /* Remove the no longer needed stack frame and return. */
    #if O_LR <= 60
    se_lwz      r0, O_LR(sp)
    #else
    e_lwz       r0, O_LR(sp)
    #endif
    se_mtlr     r0
    #if SIZE_OF_SF <= 32
    se_addi     sp, SIZE_OF_SF
    #else
    e_add16i    sp, sp, SIZE_OF_SF
    #endif
    se_blr

    .section    .rodata.facNoCyclesPerMicroSec
    .balign     4
facNoCyclesPerMicroSec:
    .float      NO_CYCLES_PER_US_Z4
    
    #undef O_TI_DEL
    #undef SIZE_OF_PAYLOAD
    #undef SIZE_OF_SF
    #undef O_LR

#undef NO_CYCLES_PER_US_Z4
#undef NO_CYCLES_OFFSET_Z4
#undef NO_CYCLES_PER_US_Z2
#undef NO_CYCLES_OFFSET_Z2
/* End of del_delayMicroseconds */

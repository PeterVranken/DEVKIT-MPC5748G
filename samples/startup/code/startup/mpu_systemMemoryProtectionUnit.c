/**
 * @file mpu_systemMemoryProtectionUnit.c
 * Configuration and initialization of the System Memory Protection Unit (SMPU). The
 * configuration is chosen static in this sample. The initially chosen configuration is
 * never changed during run-time. Furthermore, the configuration is most simple; the only
 * requirement to fulfill is to make initial SW development as easy as possible and to
 * support inter-core communication.\n
 *   To simplify development, all cores get unrestricted access to all address space,
 * memory and I/O.\n
 *   To support inter core communication there is an uncached memory area. Many inter-core
 * communication patterns are based on shared memory and while all memory is basically
 * shared in this sample is only the uncached memory easily and safely usable. (Otherwise
 * special techniques need to be applied to let a core look behind its cache into the main
 * memory.) The only - minor- specialty of the configuration is the use of a memory
 * section for the uncached area. There's no need to consider particular address spaces or
 * obey size boundaries, just declare your data as uncached where appropriate and the
 * linker will put it together.\n
 *   In particular and despite of the module name, there is no memory protection implemented
 * here. If an application needs to have protected memory areas then it will need to change
 * the chosen configuration.
 *
 * Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/* Module interface
 *   mpu_initSMPU
 * Local functions
 */

/*
 * Include files
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"

#include "mpu_systemMemoryProtectionUnit.h"


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
 * Configure and initialize the two memory protection units, SMPU0 and SMPU1.\n
 *   The configuration is static, a set of regions suitable for this sample is defined and
 * then the units are enabled. All cores and the DMA get access to the entire meaningful
 * address space. The RAM is partitioned in two chunks, normal, cached RAM and
 * cache-inhibited RAM.
 */
void mpu_initSMPU(void)
{
    /* RM, 21.1, table 21-1, p. 475: SMPU0 handles PFLASH, PBRIDGE_A, PBRIDGE_B accessed
       by XBAR0 masters plus debug interfaces. The connected masters are:
         Z4a (M0), Z4b (M1), Z2 (M2), HSM (M3), DMA (M4), Z4a debug (M8), Z4b debug (M9),
       Z2 debug (M10)
         SMPU1 handles all 3 SRAM blocks accessed by XBAR1 masters plus debug interfaces.
       The connected masters are:
         Z4a (M0), Z4b (M1), Z2 (M2), HSM (M3), DMA (M4), Ethernet (M5), FlexRay(M6), MLB
       (M7), Z4a debug (M8), Z4b debug (M9), Z2 debug (M10), USB0 (M11), USB1 (M12), uSDHC
       (M13) */

    /* All regions grant the same, unrestricted access to all bus masters. The access word
       (we use format 0) has two bits for each master in the order rw (read-write). Master
       0 .. 15 are ordered from left to right, i.e. from most to least significant.
         Full read-write access to all relevant masters, the three cores and DMA: M0, M1,
       M2, M4, M8, M9, M10. In this sample, we don't use the other bus masters (security
       core and certain I/O devices) and for now, they don't get access. */
    const uint32_t commonAccess = 0xfcc0fc00;
    
    /* We consider the entire flash ROM, as far as used in this sample, as one memory
       region. We use linker defined symbols to find the boundaries. They need to be
       aligned compatible with the constraints of the SMPU. This is checked by assertion. */
    extern uint8_t ld_romStart[0], ld_romEnd[0];
    assert(((uintptr_t)ld_romStart & 0x1f) == 0  &&  ((uintptr_t)ld_romEnd & 0x1f) == 0);
    
    /* All used flash ROM */
    SMPU_0->RGD[0].WORD0 = (uintptr_t)ld_romStart;  /* Start address of region. */
    SMPU_0->RGD[0].WORD1 = (uintptr_t)ld_romEnd-1;  /* End address of region, including. */
    SMPU_0->RGD[0].WORD2 = commonAccess;
    /// @todo Here and several other lines of code: Why do we use OR without initial value?
    SMPU_0->RGD[0].WORD5 |= SMPU_WORD5_VLD(1);      /* Enable region descriptor. */

    /* All peripheral address space (256MB). */
    SMPU_0->RGD[1].WORD0 = 0xf0000000u;        /* Start address of region. */
    SMPU_0->RGD[1].WORD1 = 0xffffffffu;        /* End address of region, including. */
    SMPU_0->RGD[1].WORD2 = commonAccess;
    SMPU_0->RGD[1].WORD3 |= SMPU_WORD3_CI(1);  /* Set cache-inhibit bit. */
    SMPU_0->RGD[1].WORD5 |= SMPU_WORD5_VLD(1); /* Enable region descriptor. */

    /* In this sample, the linker control file organizes the RAM in two chunks, normal,
       cached RAM followed by uncached RAM. We use linker defined symbols to find the
       boundaries. They need to be aligned compatible with the constraints of the SMPU.
       This is checked by assertion. */
    extern uint8_t ld_memRamStart[0], ld_uncachedRamStart[0], ld_uncachedRamEnd[0];
    assert(((uintptr_t)ld_memRamStart & 0x1f) == 0
           &&  ((uintptr_t)ld_uncachedRamStart & 0x1f) == 0
           &&  ((uintptr_t)ld_uncachedRamEnd & 0x1f) == 0
          );
    
    /* Normal, cached RAM. The region boundaries are provided by linker defined symbols. */
    SMPU_1->RGD[0].WORD0 = (uintptr_t)ld_memRamStart;       /* Start address of region. */
    SMPU_1->RGD[0].WORD1 = (uintptr_t)ld_uncachedRamStart-1;/* End address, including. */
    SMPU_1->RGD[0].WORD2 = commonAccess;
    SMPU_1->RGD[0].WORD5 |= SMPU_WORD5_VLD(1);           /* Enable region descriptor. */

    /* Uncached SRAM used by all cores. The region boundaries are provided by linker
       defined symbols.
         RM, 21.4.2, p. 506: A cache-enabled region declaration will overrule a
       cache-inhibited region. We must therefore avoid an overlap with a cache-enabled
       region. */
    SMPU_1->RGD[1].WORD0 = (uintptr_t)ld_uncachedRamStart;  /* Start address of region. */
    SMPU_1->RGD[1].WORD1 = (uintptr_t)ld_uncachedRamEnd-1;  /* End address of region. */
    SMPU_1->RGD[1].WORD2 = commonAccess;
    SMPU_1->RGD[1].WORD3 |= SMPU_WORD3_CI(1);               /* Set cache-inhibit bit. */
    SMPU_1->RGD[1].WORD5 |= SMPU_WORD5_VLD(1);				/* Enable region descriptor. */

    /* RM 21.3.1, p. 491: After configuring all region descriptors, we can globally enable
       both MPUs. */
    SMPU_0->CES0 = SMPU_CES0_MERR(0xffff)   /* Reset all possibly pending errors. */
                   | SMPU_CES0_GVLD(1);     /* Globally enable the MPU. */
    SMPU_1->CES0 = SMPU_CES0_MERR(0xffff)   /* Reset all possibly pending errors. */
                   | SMPU_CES0_GVLD(1);     /* Globally enable the MPU. */

} /* End of mpu_initSMPU */

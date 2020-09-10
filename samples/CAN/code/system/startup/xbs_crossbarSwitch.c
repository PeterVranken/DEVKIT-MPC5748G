/**
 * @file xbs_crossbarSwitch.c
 * Configuration of the crossbar switches (AXBS_0 and AXBS_1). The three cores and the DMA
 * are connected to the RAM and ROM memories through two crossbar switches that synchronize
 * the accesses. The default configuration runs out of the box but is not fully optimal.
 * The reference manual suggest a standard setting and this configuration module widely
 * implement this suggestion.
 *
 * Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   xbs_configCrossbarSwitch
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
#include "xbs_crossbarSwitch.h"


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
 * Configuration of the crossbar switches (AXBS_0 and AXBS_1).\n
 *   The three cores and the DMA are connected to the RAM and ROM memories through two
 * crossbar switches that synchronize the accesses. The default configuration runs out of
 * the box but is not fully optimal. The reference manual suggest a standard setting and
 * this function implements this suggestion with little deviations.\n
 *   @param isZ2IOCore
 * NXP proposes to apply the less powerful Z2 core for I/O operations. If this is the
 * intended SW design then \a isZ2IOCore should be \a true. Now, the Z2 has the highest
 * priority in accesses to the two peripheral bridges.
 */
void xbs_configCrossbarSwitch(bool isZ2IOCore)
{
    /* Master priorities: The 8 hex digits in the LHS literals correspond with the masters
       in this order:
         HSM, DMA, Z2-D-Bus, Z2-I-Bus, Z4A-D, Z4B-I, Z4A-D, Z4B-I
         The values are invers with respect to priority. The default value after reset is
       0x76543210, meaning that HSM has lowest priority, followed by DMA, follwed by Z2,
       Z4A and Z4B. For the three cores, a data access has lower priority as an
       instruction read.
         The tables 16-1 and 16-2 in the RM, section 16.1.1, propose a priority scheme.
       This is widely adopted by the code here. The concept is to have higher priority for
       the I bus for ROM access and higher priority for D bus for RAM access. Furthermore,
       each core should ideally have one path, were it has the highest priority. This cannot
       be achieved for the Z2 D bus: It shares the path with the Z4B D bus. Here we grant
       the Z4 the higher priority. */
    AXBS_0->PORT[0].PRS = 0x76541320;
    AXBS_0->PORT[1].PRS = 0x76543012;
    AXBS_0->PORT[2].PRS = 0x32107654;
    AXBS_0->PORT[3].PRS = 0x76150432;
    AXBS_0->PORT[4].PRS = 0x41736205;
    if(isZ2IOCore)
    {
        /// @todo Check difference of both peripheral bridges. Do they work in parallel or
        // do they share the I/O address space? In the former case it would be better to
        // grant each of the Z4 core highest priority in one bridge in the latter case it
        // would depend on the intended driver design.
        AXBS_0->PORT[5].PRS = 0x73062514;
        AXBS_0->PORT[6].PRS = 0x73062514;
    }   
    else
    {
        AXBS_0->PORT[5].PRS = 0x73261504;
        AXBS_0->PORT[6].PRS = 0x73261504;
    }

    /* AXBS_1: The reset settings grant the priorities as proposed in RM, 16.1.2, table
       16-2.
         @todo It's not clear, why table 16-2 proposes giving AXBS_1M0_slave3 precedence
       over AXBS_1M1_slave4: The latter is the path for the D bus of core Z4A and normally
       this core has highest priority. */
    

    /* Port configuration: Most of the reset settings are as desired. RM, 16.1.4:
         The AXBS0_CRSn and AXBS1_CRSn registers reset to 0x00FF_0010. This means:
       High-priority elevation is enabled for all masters (HPEn), arbitration (ARB) is set
       to "fixed priority" for all slave ports, park control is set to "park on last recent
       master" (PCTL) and park-on-master (PARK) is M0 but irrelevent because of the PCTL
       setting.
         Only a single change is useful: The D buses of cores Z4B and Z2 are both routed
       through slave port 3 of AXBS_0, which can significantly slow down the Z2. We alter
       the arbitration of this port to Round Robin in advantage of the Z2 core. */
    AXBS_0->PORT[3].CRS = AXBS_0->PORT[3].CRS
                          & ~AXBS_CRS_ARB_MASK
                          | AXBS_CRS_ARB(1 /* 0: priority based, 1: Round-Robin */);
    
} /* End of xbs_configCrossbarSwitch */





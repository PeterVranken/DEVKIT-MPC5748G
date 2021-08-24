#ifndef SIU_SIUPORTDRIVER_INCLUDED
#define SIU_SIUPORTDRIVER_INCLUDED
/**
 * @file siu_siuPortDriver.h
 * Definition of global interface of module siu_siuPortDriver.c
 *
 * @note References "RM48" (reference manual) in this module refer to "MPC5748G Reference
 * Manual", document number: MPC5748GRM, Rev. 6, 10/2017.
 *
 * @note References "RM75" in this module refer to "MPC5775E/MPC5775B Reference Manual",
 * document number: MPC5775E, Rev. 1, 05/2018.
 * Copyright (C) 2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/** @todo Uncomment the very device header, which relates to the MCU in your project. */
//#include "MPC5775B.h"
#include "MPC5748G.h"

#include "typ_types.h"

/* Double-check that the MCU selection has been properly done and read the related
   definition of port settings. */
#if defined(MCU_MPC5748G)  &&  !defined(MCU_MPC5775B)
# include "siu_siul2PortConfiguration.h"
#elif defined(MCU_MPC5775B)  &&  !defined(MCU_MPC5748G)
# include "siu_siuPortConfiguration.h"
#else
# error Bad configuration of supported MCU derivative. Double-check your include \
        statements above!
#endif


/*
 * Defines
 */

/** The number of available, arbitrated, accessible ports.
      @remark for the MPC5775B/E we have a discrepancy between RM75 and the device header.
    The latter defines #SIU_PCR_COUNT as 512, while the former says 416 as maximum number
    of ports.
      @remark The actual maximum is MCU housing specific and could be reduced in many
    cases. The defined number has a direct impact on the memory consumption for the port
    allocation bit vector and it could pay off to make a project specfic setting with a
    lower upper boundary for the maximally available port index. */
#if defined(MCU_MPC5748G)
# define SIU_NO_MCU_PORTS   SIUL2_MSCR_COUNT
#elif defined(MCU_MPC5775B)
# define SIU_NO_MCU_PORTS   /* SIU_PCR_COUNT (see above) */ (416u)
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

/** Initialization of port driver at system startup. */
void siu_osInitPortDriver(void);

/** Request a port for exclusive use. */
bool siu_osAcquirePort(unsigned int idxPort);

/** Query availability of a port. */
bool siu_osIsPortAvailable(unsigned int idxPort);

/** Return a port after use. */
void siu_osReleasePort(unsigned int idxPort);

/** Configure a port as output. */
void siu_osConfigureOutput(unsigned int idxPort, const siu_portOutCfg_t *pPortCfg);

/** Configure a port as input. */
void siu_osConfigureInput(unsigned int idxPort, const siu_portInCfg_t *pPortCfg);


/*
 * Global inline functions
 */

/**
 * Read a single port, which had been configured either as input or as output with
 * read-back function.
 *   @return
 * Get \a true if a high voltage level is detected at the pin or \a false for a low voltage
 * level.
 *   @param idxPort
 * All port related activities identify the port by it's index. This is the index into
 * register array MSCR (MPC5748G) or PCR (MPC5775B/E). Pass the index of the returned port.
 * The range is 0..#SIU_NO_MCU_PORTS. Violations are caught by assertion.
 */
static inline bool siu_osGetGPIO(unsigned int idxPort)
{
    assert(idxPort < SIU_NO_MCU_PORTS);
    
#if defined(MCU_MPC5748G)
    /* Unfortunately the MCU header only models the 32 Bit access to the GPIO data
       registers, which involves four port bits at once, although the original intention is
       supporting byte acceess to impact a single port only. We need to recompute the
       register address so that we can use byte access. See RM48, 15.2.14 SIUL2 GPIO Pad
       Data Input Register (SIUL2_GPDIn), pp.394f. */
    return *(((__IO uint8_t*)&SIUL2->GPDI[0])+idxPort) != 0;
#elif defined(MCU_MPC5775B)
    /* See RM75, 8.2.65 GPIO Pin Data Input Register (SIU_GPDIn), pp.372f. */
    return SIU->GPDI[idxPort] != 0;
#endif
} /* siu_osGetGPIO */



/**
 * Set the output level of a single port, which had been configured as output.
 *   @param idxPort
 * All port related activities identify the port by it's index. This is the index into
 * register array MSCR (MPC5748G) or PCR (MPC5775B/E). Pass the index of the returned port.
 * The range is 0..#SIU_NO_MCU_PORTS. Violations are caught by assertion.
 *   @param highLevel
 * Pass \a true if the port should output a high voltage level. Pass \a false for output of
 * a low voltage level.
 */
static inline void siu_osSetGPIO(unsigned int idxPort, bool highLevel)
{
    assert(idxPort < SIU_NO_MCU_PORTS);
    
#if defined(MCU_MPC5748G)
    /* Unfortunately the MCU header only models the 32 Bit access to the GPIO data
       registers, which involves four port bits at once, although the original intention is
       supporting byte acceess to impact a single port only. We need to recompute the
       register address so that we can use byte access. See RM48, 15.2.13 SIUL2 GPIO Pad
       Data Output Register (SIUL2_GPDOn), pp.392f. */
    *(((__IO uint8_t*)&SIUL2->GPDO[0])+idxPort) = highLevel? 1u: 0u;
#elif defined(MCU_MPC5775B)
    /** See RM75, 8.2.14 GPIO Pin Data Output Register (SIU_GPDOn), pp.244f. */
    SIU->GPDO[idxPort] = highLevel? 1u: 0u;
#endif
} /* siu_osSetGPIO */

#endif  /* SIU_SIUPORTDRIVER_INCLUDED */

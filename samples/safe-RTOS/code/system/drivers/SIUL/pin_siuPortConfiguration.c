/**
 * @file pin_siuPortConfiguration.c
 * Port configuration for MPC5775B/E and MPC5748G.\n
 *   See header of pin_siul2PortConfiguration.h for how the port configuration works on
 * MCU MPC5748G.
 *   See header of pin_siuPortConfiguration.h for how the port configuration works on
 * MCU MPC5775B/E.
 *
 * @note References "RM48" (reference manual) in this module refer to "MPC5748G Reference
 * Manual", document number: MPC5748GRM, Rev. 6, 10/2017.
 *
 * @note References "PM48" (pin mapping) in this module refer to file
 * "IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx", which is an attachment of
 * RM48.
 *
 * @note References "RM75" in this module refer to "MPC5775E/MPC5775B Reference Manual",
 * document number: MPC5775E, Rev. 1, 05/2018.
 *
 * @note References "PM75" in this module refer to file
 * "MPC5775B_E-ReferenceManual.System_IO_Definition.xlsx", which is an attachment of RM75.
 *
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
/* Module interface
 *   pin_siuConfigureOutput
 *   pin_siuConfigureInput
 * Local functions
 */

/*
 * Include files
 */

#include <assert.h>

/** @todo Uncomment the very device header, which relates to the MCU in your project. */
//#include "MPC5775B.h"
#include "MPC5748G.h"

#include "typ_types.h"


/* Double-check that the MCU selection has been properly done and read the related
   definition of port settings. */
#if defined(MCU_MPC5748G)  &&  !defined(MCU_MPC5775B)
# include "pin_siul2PortConfiguration.h"
#elif defined(MCU_MPC5775B)  &&  !defined(MCU_MPC5748G)
# include "pin_siuPortConfiguration.h"
#else
# error Bad configuration of supported MCU derivative. Double-check your include \
        statements above!
#endif


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
 * Configure an output port.
 *   @param pPortCfg
 * The desired port configuration by reference.
 */
void pin_siuConfigureOutput(const pin_portOutCfg_t *pPortCfg)
{
#if defined(MCU_MPC5748G)
    SIUL2->MSCR[pPortCfg->idxPort_MSCR] =
        SIUL2_MSCR_SSS(pPortCfg->idxPortSource_SSS) /* Source signal of port for output */
        | SIUL2_MSCR_SRC(pPortCfg->maxSlewRate_SRC) /* 0..3: Slew rate */
        | SIUL2_MSCR_OBE(1u) /* Enable output buffer */
        | SIUL2_MSCR_ODE(pPortCfg->enableOpenDrain_ODE? 1u: 0u) /* Open drain or to drive both
                                                                   levels? */ 
        | SIUL2_MSCR_SMC(1u) /* Safe mode as after reset */
        | SIUL2_MSCR_APC(0u) /* No analog I/O */
        | SIUL2_MSCR_IBE(0u) /* Disable input buffer */
        | SIUL2_MSCR_HYS(1u) /* Hysteresis as after reset, doesn't care for output. */
/// @todo Pull-up is useful if open drain is enabled!
        | SIUL2_MSCR_PUE(0u) /* Pull up/down is disabled for outputs. */
        | SIUL2_MSCR_PUS(0u) /* Pull up/down doesn't care, is disabled */
        ;
#elif defined(MCU_MPC5775B)
    assert(pPortCfg->idxPort_PCR <= 416);
    SIU->PCR[pPortCfg->idxPort_PCR] =
        SIU_PCR_PA(pPortCfg->idxPortSource_PA) /* Source signal of port for output. */
        | SIU_PCR_OBE(1u) /* Enable output buffer */
        | SIU_PCR_ODE(pPortCfg->enableOpenDrain_ODE? 1u: 0u) /* Open drain or to drive both
                                                                levels? */ 
        | SIU_PCR_DSC(pPortCfg->driveStrength_DSC) /* 0..3: Drive strength from min to max */
        | SIU_PCR_SRC(pPortCfg->maxSlewRate_SRC) /* 0..3: Slew rate */
        | SIU_PCR_IBE(0u) /* Disable input buffer */
        | SIU_PCR_HYS(0u) /* Hysteresis as after reset, doesn't care for output. */
        | SIU_PCR_WPE(0u) /* Pull up/down is disabled for outputs. */
        | SIU_PCR_WPS(0u) /* Pull up/down doesn't care, is disabled */
        ;
#endif
} /* pin_siuConfigureOutput */



/**
 * Configure an input port.
 *   @param pPortCfg
 * The desired port configuration by reference.
 */
void pin_siuConfigureInput(const pin_portInCfg_t *pPortCfg)
{
#if defined(MCU_MPC5748G)
    assert(pPortCfg->idxPort_MSCR <= 263u); 
    SIUL2->MSCR[pPortCfg->idxPort_MSCR] =
        SIUL2_MSCR_SSS(0u)   /* Source signal for (disabled) ouput is default */
        | SIUL2_MSCR_SRC(0u) /* Slew rate: Irrelevant for input */
        | SIUL2_MSCR_OBE(0u) /* Disable output buffer */
        | SIUL2_MSCR_ODE(0u) /* Disable open drain, drive both edges */
        | SIUL2_MSCR_SMC(1u) /* Safe mode as after reset */
        | SIUL2_MSCR_APC(0u) /* No analog I/O */
        | SIUL2_MSCR_IBE(1u) /* Enable input buffer */
        | SIUL2_MSCR_HYS(pPortCfg->enableHysteresis_HYS? 1u: 0u) /* Hysteresis? */
        | SIUL2_MSCR_PUE(pPortCfg->pullUpDownCfg != pin_pullRes_none? 1u: 0u)/* Pull res on? */
        | SIUL2_MSCR_PUS(pPortCfg->pullUpDownCfg == pin_pullRes_pullUp? 1u: 0u) /* Up/down */
        ;
   /* Connect the input buffer of the port via a multiplxer with an actual I/O device. */
   assert(pPortCfg->idxMultiplexerRegister <= 511u  
          &&  pPortCfg->idxInputSource_MUXSELVALUE <= 15
         );
   SIUL2->IMCR[pPortCfg->idxMultiplexerRegister] = 
                                    SIUL2_IMCR_SSS(pPortCfg->idxInputSource_MUXSELVALUE);

#elif defined(MCU_MPC5775B)

    /* Port configuration. */
    assert(pPortCfg->idxPort_PCR <= 416);
    SIU->PCR[pPortCfg->idxPort_PCR] =
        SIU_PCR_PA(pPortCfg->idxPortSource_PA) /* Port signal for input. */
        | SIU_PCR_OBE(0u) /* Disable output buffer */
        | SIU_PCR_ODE(0u) /* Open drain driver or drive both edges doesn't care. */
        | SIU_PCR_DSC(0u) /* Drive strength from min to max doesn't care for input. */
        | SIU_PCR_SRC(0u) /* Slew rate doesn't care for input. */
        | SIU_PCR_IBE(1u) /* Enable input buffer */
        | SIU_PCR_HYS(pPortCfg->enableHysteresis_HYS? 1u: 0u) /* Hysteresis? */
        | SIU_PCR_WPE(pPortCfg->pullUpDownCfg != pin_pullRes_none? 1u: 0u) /* Pull res on? */
        | SIU_PCR_WPS(pPortCfg->pullUpDownCfg == pin_pullRes_pullUp? 1u: 0u) /* Up or down? */
        ;

    /* Configuration of multiplexer, which connects the input of a device with the required
       port.
         All IMUX form a regular array of 32 Bit registers with gapless 4 Byte distance.
       (With the exception that some IMUX don't exist in this array.) The bitmasks of all
       IMUX registers are identical (only the presence of the muxes in the IMUX differs).
       Moreover, all muxes in an IMUX have same bit pattern and they form a regular array
       of 2 Bit each in normal counting. Therefore, we can make the access generic, by zero
       based indexes. */
    if(pPortCfg->idxMultiplexerRegister != UINT_T_MAX(uint8_t))
    {
        #define SIU_IMUX_MUXSELn_MASK(n)       (0x3u<<(n))
        #define SIU_IMUX_MUXSELn_SHIFT(n)      (2u*(n))
        #define SIU_IMUX_MUXSELn_WIDTH(n)      2u
        #define SIU_IMUX_MUXSELn(n, x)         (((uint32_t)(((uint32_t)(x))<<SIU_IMUX_MUXSELn_SHIFT(n)))&SIU_IMUX_MUXSELn_MASK(n))

        __IO uint32_t * const imuxAry = &SIU->IMUX0;
        assert(pPortCfg->idxMultiplexerRegister <= 5
               ||  pPortCfg->idxMultiplexerRegister == 7
               ||  pPortCfg->idxMultiplexerRegister == 10
               ||  pPortCfg->idxMultiplexerRegister == 12
              );
        assert(pPortCfg->idxMultiplexer <= 15
               &&  pPortCfg->idxInputSource_MUXSELVALUE <= 3
              );
        imuxAry[pPortCfg->idxMultiplexerRegister] =
            imuxAry[pPortCfg->idxMultiplexerRegister]
            & ~SIU_IMUX_MUXSELn_MASK(pPortCfg->idxMultiplexer)
            | SIU_IMUX_MUXSELn(pPortCfg->idxMultiplexer, pPortCfg->idxInputSource_MUXSELVALUE)
            ;

        #undef SIU_IMUX_MUXSELn_MASK
        #undef SIU_IMUX_MUXSELn_SHIFT
        #undef SIU_IMUX_MUXSELn_WIDTH
        #undef SIU_IMUX_MUXSELn
    }
    else
    {
        /* Some device inputs are hardwire with a particular port, without a multiplexer in
           between. This is the case if the signal is not mentioned in PM75, "Input
           Muxing". */
    }
#endif
} /* pin_siuConfigureInput */


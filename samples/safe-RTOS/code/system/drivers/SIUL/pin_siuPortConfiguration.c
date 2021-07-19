/**
 * @file pin_siuPortConfiguration.c
 * Port configuration for MPC5775B/E.\n
 *   See header of pin_siuPortConfiguration.h for how the port configuration works on this
 * MCU.
 *
 * @note References "RM" (reference manual) in this module refer to "MPC5775E/MPC5775B
 * Reference Manual", document number: MPC5775E, Rev. 1, 05/2018.
 *
 * @note References "PM" (pin mapping) in this module refer to file
 * "MPC5775B_E-ReferenceManual.System_IO_Definition.xlsx", which is an attachment of RM.
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

#include "MPC5775B.h"
#include "typ_types.h"
#include "pin_siuPortConfiguration.h"


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
    SIU->PCR[pPortCfg->idxPort_PCR] =
        SIU_PCR_PA(pPortCfg->idxPortSource_PA) /* Source signal of port for output. */
        | SIU_PCR_OBE(1u) /* Enable output buffer */
        | SIU_PCR_ODE(pPortCfg->enableOpenDrain_ODE) /* Open drain or to drive both levels? */
        | SIU_PCR_DSC(pPortCfg->driveStrength_DSC) /* 0..3: Drive strength from min to max */
        | SIU_PCR_SRC(pPortCfg->maxSlewRate_SRC) /* 0..3: Slew rate */
        | SIU_PCR_IBE(0u) /* Disable input buffer */
        | SIU_PCR_HYS(0u) /* Hysteresis as after reset, doesn't care for output. */
        | SIU_PCR_WPE(0u) /* Pull up/down is disabled for outputs. */
        | SIU_PCR_WPS(0u) /* Pull up/down doesn't care, is disabled */
        ;

} /* pin_siuConfigureOutput */



/**
 * Configure an input port.
 *   @param pPortCfg
 * The desired port configuration by reference.
 */
void pin_siuConfigureInput(const pin_portInCfg_t *pPortCfg)
{
    /* Port configuration. */
    SIU->PCR[pPortCfg->idxPort_PCR] =
        SIU_PCR_PA(pPortCfg->idxPortSource_PA) /* Port signal for input. */
        | SIU_PCR_OBE(0u) /* Disable output buffer */
        | SIU_PCR_ODE(0u) /* Open drain driver or drive both edges doesn't care. */
        | SIU_PCR_DSC(0u) /* Drive strength from min to max doesn't care for input. */
        | SIU_PCR_SRC(0u) /* Slew rate doesn't care for input. */
        | SIU_PCR_IBE(1u) /* Enable input buffer */
        | SIU_PCR_HYS(pPortCfg->enableHysteresis_HYS) /* Hysteresis */
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
           between. This is the case if the signal is not mentioned in PM, "Input Muxing". */ 
    }
} /* pin_siuConfigureInput */


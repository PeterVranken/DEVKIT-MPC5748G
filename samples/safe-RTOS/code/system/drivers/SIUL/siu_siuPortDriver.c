/**
 * @file siu_siuPortConfiguration.c
 * Port configuration for MPC5775B/E and MPC5748G.\n
 *   See header of siu_siul2PortConfiguration.h for how the port configuration works on
 * MCU MPC5748G.
 *   See header of siu_siuPortConfiguration.h for how the port configuration works on
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
 *   siu_osInitPortDriver
 *   siu_osAcquirePort
 *   siu_osReleasePort
 *   siu_siuConfigureOutput
 *   siu_siuConfigureInput
 *   siu_getGPIO (inline)
 * Local functions
 */

/*
 * Include files
 */

#include <assert.h>

#include "siu_siuPortDriver.h"
#include "typ_types.h"
#include "mtx_mutex.h"


/*
 * Defines
 */

/** The number of 32 Bit words, which are required to spend one bit for each available
    port. */ 
#define SIZE_OF_PORT_ALLOCATION_ARY     (((SIU_NO_MCU_PORTS) + 3u) / 4u)


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** A bit vector with one bit per DMA channel. A set bit means that the channel is
    allocated by some (unknown, unidentified) client code.
      Note, the availability of the port acquistion and release API to all cores requires
    the use of unchached RAM for the data object. */
static uint32_t UNCACHED_OS(_portAllocationAry)[SIZE_OF_PORT_ALLOCATION_ARY] =
                                                {[0 ... (SIZE_OF_PORT_ALLOCATION_ARY-1u)] = 0};


/*
 * Function implementation
 */

/**
 * Initialization of port driver at system startup. This initialization needs to happen
 * before any client device can request a port using siu_acquirePort() or make
 * use of it.
 */
void siu_osInitPortDriver(void)
{
    /* Mark all ports as currently unused. */
    unsigned int u;
    for(u=0u; u<sizeOfAry(_portAllocationAry); ++u)
        _portAllocationAry[0u] = 0u;

} /* End of siu_osInitPortDriver */



/**
 * Request a port for exclusive use.\n
 *   The client code of the port driver, typically some I/O device drivers, which need to
 * connect the I/O device to a specific MCU port, will call this function to gain access to
 * one particular MCU port. It may use this port until it calls the counterpart function
 * siu_osReleasePort().\n
 *   No code, system wide, must ever touch an MCU port without requesting access to that
 * port using this API!
 *   @return
 * \a true, if function succeeded, else \a false. The port may be used only if the function
 * returned \a true!
 *   @param idxPort
 * All port related activities identify the port by it's index. This is the index into
 * register array MSCR (MPC5748G) or PCR (MPC5775B/E). This is the index of the requested
 * port. The range is 0..#SIU_NO_MCU_PORTS. Violations are caught by assertion and the
 * function returns \a false in PRODUCTION compilation.
 *   @remark
 * On the MPC5748G, the function can be called from any OS context on any core at any time.
 *   @warning
 * On the MPC5775B/E, the function must be called from the boot core only, i.e.
 * rtos_osGetIdxCore() == 0. Any OS context on the boot core may call this function at any
 * time.
 *   @see siu_osReleasePort()
 */
bool siu_osAcquirePort(unsigned int idxPort)
{
    if(idxPort > SIU_NO_MCU_PORTS)
    {
        assert(false);
        return false;
    }
     
    /* This function needs to be thread-safe, even if it'll likely be called only during
       system start up, when there aren't competing contexts. Unfortunately, this is not
       guaranteed. */
#if defined(MCU_MPC5748G)
    static mtx_intercoreCriticalSection_t DATA_OS(critSec) = MTX_INTERCORE_CRITICAL_SECTION;
    mtx_osEnterIntercoreCriticalSection(&critSec);
#elif defined(MCU_MPC5775B)
    /* On MCU_MPC5775B, we don't have a multi-core concept for this driver yet. For now, we
       restrict the use of this function to the boot core. */
    assert(rtos_osGetIdxCore() == 0);
    const uint32_t stateOnEntry = rtos_osEnterCriticalSection();
#endif
    
    #define WORD_SIZE   (sizeof(_portAllocationAry[0])*8u)
    const unsigned int idxWord = idxPort/WORD_SIZE
                     , maskForBit = 1u << (idxPort - idxWord*WORD_SIZE);
    assert(idxWord < sizeOfAry(_portAllocationAry));
    const uint32_t allocVec = _portAllocationAry[idxWord];
    bool success;
    if((allocVec & maskForBit) == 0)
    {
        /* Port is currently not reserved (by someone else). Put the reservation bit
           now. */
        _portAllocationAry[idxWord] = allocVec | maskForBit;
        success = true;
    }
    else
    {
        /* Channel is occupied. Just return error. */
        success = false;
    }
    #undef WORD_SIZE
    
#if defined(MCU_MPC5748G)
    mtx_osLeaveIntercoreCriticalSection(&critSec);
#elif defined(MCU_MPC5775B)
    rtos_osLeaveCriticalSection(stateOnEntry);
#endif
    
    return success;
    
} /* End of siu_osAcquirePort */




/**
 * Query availability of a port. A port is available if it had not been acquired using
 * siu_osAcquirePort(), yet, or after if it had been released again using
 * siu_osReleasePort().
 *   @return
 * \a true, if the port is currently available, \a false if it had been acquired by someone.
 *   @param idxPort
 * All port related activities identify the port by it's index. This is the index into
 * register array MSCR (MPC5748G) or PCR (MPC5775B/E). This is the index of the port in
 * question. The range is 0..#SIU_NO_MCU_PORTS. Violations are caught by assertion and the
 * function returns \a false in PRODUCTION compilation.
 *   @remark
 * The function can be called from any OS context on any core at any time. Note, that it
 * makes no sense to use this function to ensure a successful call of siu_osAcquirePort()
 * if there are indeed competing contexts.
 */
bool siu_osIsPortAvailable(unsigned int idxPort)
{
    if(idxPort > SIU_NO_MCU_PORTS)
    {
        assert(false);
        return false;
    }
     
    /* This function is implicitly thread-safe as it only reads the status information. */
    #define WORD_SIZE   (sizeof(_portAllocationAry[0])*8u)
    const unsigned int idxWord = idxPort/WORD_SIZE
                     , maskForBit = 1u << (idxPort - idxWord*WORD_SIZE);
    const uint32_t allocVec = _portAllocationAry[idxWord];
    const bool success = (allocVec & maskForBit) == 0;
    #undef WORD_SIZE
    
    return success;
    
} /* End of siu_osIsPortAvailable */




/**
 * Return a port after use so that it can be acquired and used by other clients. The port
 * configuration register is restored to the power-on default value, i.e. the port is
 * inactivated.\n
 *   Counterpart of siu_osAcquirePort().
 *   @param idxPort
 * All port related activities identify the port by it's index. This is the index into
 * register array MSCR (MPC5748G) or PCR (MPC5775B/E). Pass the index of the returned port.
 * The range is 0..#SIU_NO_MCU_PORTS. Violations are caught by assertion.
 *   @remark
 * The function doesn't keep track who had allocated a port and who returns it. Proper use
 * of the function is a prerequisite of conflict free operation of ports but this can't be
 * checked by the function! Careful use is a must. As a minimal cross-check, an assertion
 * fires if a port is released, which had not been acquired before.
 *   @remark
 * On the MPC5748G, the function can be called from any OS context on any core at any time.
 *   @warning
 * On the MPC5775B/E, the function must be called from the boot core only, i.e.
 * rtos_osGetIdxCore() == 0. Any OS context on the boot core may call this function at any
 * time.
 *   @see siu_osAcquirePort()
 */
void siu_osReleasePort(unsigned int idxPort)
{
    assert(idxPort < SIU_NO_MCU_PORTS);
     
    /* De-configure the port: We retsore the default settings of the port configururation
       register. */
#if defined(MCU_MPC5748G)
    /* See RM48, 15.2.11, pp.388f for default out of POR: Output buffer off, no pull-up,
       only hystheresis and Safe Mode Control are on. */
    SIUL2->MSCR[idxPort] = 0x00840000u;
#elif defined(MCU_MPC5775B)
    /* See RM75, 8.2.13, pp.241f for default out of POR: Output buffer off, no pull-up,
       hystheresis off. */
    SIU->PCR[idxPort] = 0x00000000u;
#endif    

    /* This function needs to be thread-safe, even if it'll likely be called only during
       system start up, when there aren't competing contexts. Unfortunately, this is not
       guaranteed. */
#if defined(MCU_MPC5748G)
    static mtx_intercoreCriticalSection_t DATA_OS(critSec) = MTX_INTERCORE_CRITICAL_SECTION;
    mtx_osEnterIntercoreCriticalSection(&critSec);
#elif defined(MCU_MPC5775B)
    /* On MCU_MPC5775B, we don't have a multi-core concept for this driver yet. For now, we
       restrict the use of this function to the boot core. */
    assert(rtos_osGetIdxCore() == 0);
    const uint32_t stateOnEntry = rtos_osEnterCriticalSection();
#endif
    
    #define WORD_SIZE   (sizeof(_portAllocationAry[0])*8u)
    const unsigned int idxWord = idxPort/WORD_SIZE
                     , maskForBit = 1u << (idxPort - idxWord*WORD_SIZE);
    const uint32_t allocVec = _portAllocationAry[idxWord];
    
    /* Just reset the reservation bit. */
    assert((allocVec & maskForBit) != 0);
    _portAllocationAry[idxWord] = allocVec & ~maskForBit;
    #undef WORD_SIZE

#if defined(MCU_MPC5748G)
    mtx_osLeaveIntercoreCriticalSection(&critSec);
#elif defined(MCU_MPC5775B)
    rtos_osLeaveCriticalSection(stateOnEntry);
#endif
    
} /* End of siu_osReleasePort */




/**
 * Configure a port as output.
 *   @param idxPort
 * All port related activities identify the port by it's index. This is the index into
 * register array MSCR (MPC5748G) or PCR (MPC5775B/E). Pass the index of the returned port.
 * The range is 0..#SIU_NO_MCU_PORTS. Violations are caught by assertion.
 *   @param pPortCfg
 * The desired port configuration by reference.
 */
void siu_siuConfigureOutput(unsigned int idxPort, const siu_portOutCfg_t *pPortCfg)
{
    /* The next assertion incorporates an index check for idxPort. */
    assert(!siu_osIsPortAvailable(idxPort));

    /* Filter suspicious configurations. */
    assert(pPortCfg->enableOpenDrain_ODE ||  pPortCfg->pullUpDownCfg == siu_pullRes_none);
    
#if defined(MCU_MPC5748G)
    SIUL2->MSCR[idxPort] =
        SIUL2_MSCR_SSS(pPortCfg->idxPortSource_SSS) /* Source signal of port for output */
        | SIUL2_MSCR_SRC(pPortCfg->maxSlewRate_SRC) /* 0..3: Slew rate */
        | SIUL2_MSCR_OBE(1u) /* Enable output buffer */
        | SIUL2_MSCR_ODE(pPortCfg->enableOpenDrain_ODE? 1u: 0u) /* Open drain or to drive both
                                                                   levels? */ 
        | SIUL2_MSCR_SMC(1u) /* Safe mode as after reset */
        | SIUL2_MSCR_APC(0u) /* No analog I/O */
        | SIUL2_MSCR_IBE(pPortCfg->enableReadBack? 1u: 0u) /* Enable input buffer if
                                                              read-back is required. */
        | SIUL2_MSCR_HYS(pPortCfg->enableReadBack? 1u: 0u) /* Hysteresis is useful if the port
                                                              has input characteristics,
                                                              too. */
        | SIUL2_MSCR_PUE(pPortCfg->pullUpDownCfg != siu_pullRes_none? 1u: 0u)/* Pull res on? */
        | SIUL2_MSCR_PUS(pPortCfg->pullUpDownCfg == siu_pullRes_pullUp? 1u: 0u) /* Up/down */
        ;
#elif defined(MCU_MPC5775B)
    SIU->PCR[idxPort] =
        SIU_PCR_PA(pPortCfg->idxPortSource_PA) /* Source signal of port for output. */
        | SIU_PCR_OBE(1u) /* Enable output buffer */
        | SIU_PCR_ODE(pPortCfg->enableOpenDrain_ODE? 1u: 0u) /* Open drain or to drive both
                                                                levels? */ 
        | SIU_PCR_DSC(pPortCfg->driveStrength_DSC) /* 0..3: Drive strength from min to max */
        | SIU_PCR_SRC(pPortCfg->maxSlewRate_SRC) /* 0..3: Slew rate */
        | SIU_PCR_IBE(pPortCfg->enableReadBack? 1u: 0u) /* Enable input buffer if read-back
                                                           is required. */
        | SIU_PCR_HYS(pPortCfg->enableReadBack? 1u: 0u) /* Hysteresis is useful if the port
                                                           has input characteristics, too. */
        | SIU_PCR_WPE(pPortCfg->pullUpDownCfg != siu_pullRes_none? 1u: 0u) /* Pull res on? */
        | SIU_PCR_WPS(pPortCfg->pullUpDownCfg == siu_pullRes_pullUp? 1u: 0u) /* Up or down? */
        ;
#endif
} /* siu_siuConfigureOutput */



/**
 * Configure a port as input.
 *   @param idxPort
 * All port related activities identify the port by it's index. This is the index into
 * register array MSCR (MPC5748G) or PCR (MPC5775B/E). Pass the index of the returned port.
 * The range is 0..#SIU_NO_MCU_PORTS. Violations are caught by assertion.
 *   @param pPortCfg
 * The desired port configuration by reference.
 */
void siu_siuConfigureInput(unsigned int idxPort, const siu_portInCfg_t *pPortCfg)
{
    /* The next assertion incorporates an index check for idxPort. */
    assert(!siu_osIsPortAvailable(idxPort));

#if defined(MCU_MPC5748G)
    SIUL2->MSCR[idxPort] =
        SIUL2_MSCR_SSS(0u)   /* Source signal for (disabled) ouput is default */
        | SIUL2_MSCR_SRC(0u) /* Slew rate: Irrelevant for input */
        | SIUL2_MSCR_OBE(0u) /* Disable output buffer */
        | SIUL2_MSCR_ODE(0u) /* Disable open drain, drive both edges */
        | SIUL2_MSCR_SMC(1u) /* Safe mode as after reset */
        | SIUL2_MSCR_APC(0u) /* No analog I/O */
        | SIUL2_MSCR_IBE(1u) /* Enable input buffer */
        | SIUL2_MSCR_HYS(pPortCfg->enableHysteresis_HYS? 1u: 0u) /* Hysteresis? */
        | SIUL2_MSCR_PUE(pPortCfg->pullUpDownCfg != siu_pullRes_none? 1u: 0u)/* Pull res on? */
        | SIUL2_MSCR_PUS(pPortCfg->pullUpDownCfg == siu_pullRes_pullUp? 1u: 0u) /* Up/down */
        ;
    
    /* If the port is used as input of an I/O device (but not as simple GPIO) then route the
       input buffer of the port via a multiplxer to the actual I/O device. */
    if(pPortCfg->idxMultiplexerRegister != UINT_T_MAX(uint16_t))
    {
        assert(pPortCfg->idxMultiplexerRegister < SIUL2_IMCR_COUNT
               &&  pPortCfg->idxInputSource_MUXSELVALUE <= 15u
              );
        SIUL2->IMCR[pPortCfg->idxMultiplexerRegister] = 
                                        SIUL2_IMCR_SSS(pPortCfg->idxInputSource_MUXSELVALUE);
    }
#elif defined(MCU_MPC5775B)

    /* Port configuration. */
    SIU->PCR[idxPort] =
/// @todo TBC: Does SIU_PCR_PA take any effect if output buffer is disabled? Or like for 5748G?
        SIU_PCR_PA(pPortCfg->idxPortSource_PA) /* Port signal for input. */
        | SIU_PCR_OBE(0u) /* Disable output buffer */
        | SIU_PCR_ODE(0u) /* Open drain driver or drive both edges doesn't care. */
        | SIU_PCR_DSC(0u) /* Drive strength from min to max doesn't care for input. */
        | SIU_PCR_SRC(0u) /* Slew rate doesn't care for input. */
        | SIU_PCR_IBE(1u) /* Enable input buffer */
        | SIU_PCR_HYS(pPortCfg->enableHysteresis_HYS? 1u: 0u) /* Hysteresis? */
        | SIU_PCR_WPE(pPortCfg->pullUpDownCfg != siu_pullRes_none? 1u: 0u) /* Pull res on? */
        | SIU_PCR_WPS(pPortCfg->pullUpDownCfg == siu_pullRes_pullUp? 1u: 0u) /* Up or down? */
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
} /* siu_siuConfigureInput */


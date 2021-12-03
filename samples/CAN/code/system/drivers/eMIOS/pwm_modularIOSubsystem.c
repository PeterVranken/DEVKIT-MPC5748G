/**
 * @file pwm_modularIOSubsystem.c
 * Simple driver for basic operation of the eMIOS devices in an MPC5748G or MPC5775B/E. It
 * supports the use case PWM output with settable duty cycle and frequency, frequency
 * input and duty time input.\n
 *   The driver supports the mode "Output Pulse Width and Frequency Modulation Buffered"
 * (OPWFMB) for PWM output, which means for the MPC5748G that only the channels of groups G
 * and X can be used for output. (The other channels, which don't have an own time base,
 * would require some extension code for sharing the clock with a master channel.)\n
 *   The driver supports the modes "Input Period Measuremen" (IPM) and "Input Pulse Width
 * Measurement" (IPWM) for PWM input, which means for the MPC5748G that only the channels
 * of groups G can be used for output. (The other channels, which don't have an own time
 * base, would require some extension code for sharing the clock with a master channel.)\n
 *   The driver is independent from a specific board and it doesn't configure MCU pins.
 * Some related calls of the SIU/SIUL2 driver will be needed in the calling code to make
 * the operations work. Moreover, for the MPC5775B/E, the Input Glitch Filter, IGF, needs
 * to be configured. It sits in the connection between MCU port and eMIOS device and out of
 * reset it doesn't pass the input signal on.
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
 * "MPC5775B_E-ReferenceManual.System_IO_Definition.xlsx", V1.14, which is an attachment of
 * RM75.
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
 *   pwm_osInitEMIOSDevice
 *   pwm_osInitEMIOSChannelForPeriodTimeMeasurement
 *   pwm_osGetChnInputPeriodTime
 *   pwm_osInitEMIOSChannelForDutyTimeMeasurement
 *   pwm_osInitEMIOSChannelForPWMGeneration
 *   pwm_osSetChnFrequencyAndDutyCycle
 *   pwm_osSetChnDutyCycle
 * Local functions
 *   isChn
 *   isChnGroupX
 *   isChnGroupG
 *   isPossibleOutputChn
 *   isPossibleInputChn
 *   isValidDeviceHandle
 *   isValidInputChnHandle
 *   selectBaseModeGPIO
 *   calcBAForPWM
 *   initChannelAsPWMInput
 *   getInputChnDeltaTime
 */

/*
 * Include files
 */

#include "pwm_modularIOSubsystem.h"

#include <assert.h>

#include "typ_types.h"
#include "rtos.h"
#include "ccl_configureClocks.h"


/*
 * Defines
 */

#ifdef MCU_MPC5748G
/** The appicable clock rate for peripheral eMIOS. See RM48 9.7, Table9-6, pp.220f to find
    out, which I/O device is connected to which peripheral clock. */
# define CCL_PER_CLOCK  CCL_PER_CLK_FS80
#endif


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
 * Check for presence of a given channel index.
 *   @return 
 * Get \a true if a channel with index \a idxChn is present in the eMIOS device.
 *   @param idxChn
 * The index of the channel in the range 0..31.
 */
static inline bool isChn(unsigned int idxChn)
{
#ifdef MCU_MPC5748G
    return idxChn < 32u;
#else
    return idxChn <= 7u  ||  idxChn >= 16u  && idxChn <= 23u;
#endif
} /* isChn */


#ifdef MCU_MPC5748G
/**
 * Check for a given MPC7548G channel, if it belongs into group X. See RM48, Table 35-2 and
 * 35-3, pp.979ff, for details.
 *   @return 
 * Get \a true if the channel is a group X channel.
 *   @param pEMIOS
 * The eMIOS device, the tested given channel belongs to.
 *   @param idxChn
 * The index of the channel in the range 0..31.
 */
static inline bool isChnGroupX(unsigned int idxChn)
{
    return (idxChn & ~0x0180u) == 0u  ||  idxChn == 22u  ||  idxChn == 23u;
    
} /* isChnGroupX */


/**
 * Check for a given MPC7548G channel, if it belongs into group G. See RM48, Table 35-2 and
 * 35-3, pp.979ff, for details.
 *   @return 
 * Get \a true if the channel is a group G channel.
 *   @param pEMIOS
 * The eMIOS device, the tested given channel belongs to.
 *   @param idxChn
 * The index of the channel in the range 0..31.
 */
static inline bool isChnGroupG(const eMIOS_Type * const pEMIOS, unsigned int idxChn)
{
    return pEMIOS == eMIOS_0  &&  idxChn >= 1u  &&  idxChn <= 7u;
    
} /* isChnGroupG */

#endif /* MPC5748G only */


#ifdef DEBUG
/**
 * Check for a given channel, if it can be used for the input modes applied by the driver
 * (IPWM and IPM).
 *   @return 
 * Get \a true if the selected channel is suitable, \a false otherwise.
 *   @param pEMIOS
 * The eMIOS device, the given channel belongs to.
 *   @param idxChn
 * The index of the channel in the range 0..31.
 */
static inline bool isPossibleInputChn(const eMIOS_Type * const pEMIOS, unsigned int idxChn)
{
#ifdef MCU_MPC5748G
    /* Note, RM48, Table 35-3, pp.979ff, says that group H is also capable of running modes
       IP(W)M but this doesn't hold if using the internal time base - what this driver
       implementation does do. */
    return isChnGroupG(pEMIOS, idxChn);
#else
    (void)pEMIOS;

    /* MPC5775B/E: All channels have same capabilities. */
    return isChn(idxChn);
#endif
} /* isPossibleInputChn */



/**
 * Check for a given channel, if it can be used for the output mode applied by the driver
 * (OPWFMB).
 *   @return 
 * Get \a true if the selected channel is suitable, \a false otherwise.
 *   @param pEMIOS
 * The eMIOS device, the given channel belongs to.
 *   @param idxChn
 * The index of the channel in the range 0..31.
 */
static inline bool isPossibleOutputChn(const eMIOS_Type * const pEMIOS, unsigned int idxChn)
{
#ifdef MCU_MPC5748G
    return isChnGroupX(idxChn) || isChnGroupG(pEMIOS, idxChn);
#else
    /* MPC5775B/E: All channels have same capabilities. */
    return isChn(idxChn);
#endif
} /* isPossibleOutputChn */


/**
 * Self-test: Check the validity of a device handle.
 *   @return 
 * Get \a true if handle is alright, if it belongs to a properly initialized eMIOS device.
 *   @param pHDevice
 * The handle to check.
 */
static inline bool isValidDeviceHandle(const pwm_hEMIOSDevice_t * const pHDevice)
{
    const eMIOS_Type * const pEMIOS = pHDevice->pEMIOS;
    return ( pEMIOS == eMIOS_0
             ||  pEMIOS == eMIOS_1
#ifdef MCU_MPC5748G
             ||  pEMIOS == eMIOS_2
#endif
           );
} /* isValidDeviceHandle */



/**
 * Self-test: Check the validity of a channel handle for input operations.
 *   @return 
 * Get \a true if handle is alright, if it belongs to a properly initialized eMIOS input
 * channel.
 *   @param pHChannel
 * The handle to check.
 */
static inline bool isValidInputChnHandle(const pwm_hEMIOSChannel_t * const pHChannel)
{
    const eMIOS_Type * const pEMIOS = pHChannel->pEMIOS;
    const unsigned int idxChn = pHChannel->idxChn;
    return ( pEMIOS == eMIOS_0
             ||  pEMIOS == eMIOS_1
#ifdef MCU_MPC5748G
             ||  pEMIOS == eMIOS_2
#endif
           )
           && isPossibleInputChn(pEMIOS, idxChn);

} /* isValidInputChnHandle */


/**
 * Self-test: Check the validity of a channel handle for output operations.
 *   @return 
 * Get \a true if handle is alright, if it belongs to a properly initialized eMIOS output
 * channel.
 *   @param pHChannel
 * The handle to check.
 */
static inline bool isValidOutputChnHandle(const pwm_hEMIOSChannel_t * const pHChannel)
{
    const eMIOS_Type * const pEMIOS = pHChannel->pEMIOS;
    const unsigned int idxChn = pHChannel->idxChn;
    return ( pEMIOS == eMIOS_0
             ||  pEMIOS == eMIOS_1
#ifdef MCU_MPC5748G
             ||  pEMIOS == eMIOS_2
#endif
           )
           && isPossibleInputChn(pEMIOS, idxChn);

} /* isValidOutputChnHandle */

#endif /* DEBUG only */


/**
 * The channels need to be in GPIO mode before they can be brought into any other mode.
 * This function brings the channel into GPIO. Its call allows changing the mode of a
 * channel.
 */
static void selectBaseModeGPIO( const pwm_hEMIOSChannel_t * const pHChannel
                              , unsigned int counterInitialValue
                              )
{
    eMIOS_UC_Type * const pUC = pHChannel->pUC;
    pUC->C = eMIOS_C_FREN(1u)     /* This channel's freeze when in debug mode. */
             | eMIOS_C_ODIS(0u)   /* 1: Channel output can be disabled by input signal,0: on */
             | eMIOS_C_ODISSL(0u) /* Input selection for output disable, doesn't care. */
             | eMIOS_C_UCPRE(0u)  /* Channel prescaler, divide by n+1 */
             | eMIOS_C_UCPREN(0u) /* Enable prescaler? */
             | eMIOS_C_DMA(0u)    /* 0: Flag raises IRQ, 1: requests DMA */
             | eMIOS_C_IF(8u)     /* Glitch filter strength, need 2*n identical samples */    
             | eMIOS_C_FCK(0u)    /* Filter: 0: Use channel prescaler clock, 1: Module clock */
             | eMIOS_C_FEN(0u)    /* IRQ/DMA enable bit */
             | eMIOS_C_BSL(3u)    /* 3: Internal counter is running and take as time base */
             | eMIOS_C_EDSEL(0u)  /* 0: no flag, 1: flag asserted on input edge */
             | eMIOS_C_EDPOL(0u)  /* Edge select, 0: falling, 1: rising */
             | eMIOS_C_MODE(0x0u);/* Mode is GPIO input. */
          
    /* Input value could be read via status bit UCIN, RM75, 34.5.5, pp.1214ff. */
    
    /* Only in mode GPIO, we can preset the channel counter. RM75, 34.5.3, pp.1207f. */
    assert((pUC->C & eMIOS_C_MODE_MASK) == (0u << eMIOS_C_MODE_SHIFT));
#if defined(MCU_MPC5748G)
    /* MPC5748G: All devices have channels at indexes 0..31 but they differ. Only groups
       X and G have the counter. */
    const unsigned int idxChn = pHChannel->idxChn;
    const eMIOS_Type * const pEMIOS = pHChannel->pEMIOS;
    if(isChnGroupX(idxChn) || isChnGroupG(pEMIOS, idxChn))
#endif
    {
        pUC->CNT = counterInitialValue;
    }
} /* selectBaseModeGPIO */



/**
 * Calculate channel register settings to achieve a given PWM frequency and duty cycle.
 *   @param pB
 * Get the optimal value for register B by reference.
 *   @param pA
 * Get the optimal value for register A by reference.
 *   @param f
 * The desired frequency in Hz. The value is saturated to the technically possible range;
 * see pwm_osInitEMIOSChannelForPWMGeneration() for details.
 *   @param dutyCycle
 * The desired duty cycle in the range [0..1]. The value is saturated to the technically
 * possible range; see pwm_osInitEMIOSChannelForPWMGeneration() for details.
 *   @param totalPrescale
 * The combined prescale value from both, device and given channel. Meant is the factor,
 * i.e. an * integer 1..4*256.
 */
static inline void calcBAForPWM( uint32_t * const pB
                               , uint32_t * const pA
                               , float f
                               , float dutyCycle
                               , unsigned int totalPrescale
                               )
{
#ifdef MCU_MPC5748G
    const unsigned int maskTimerWrap = 0x0000FFFFu;
#else
    const unsigned int maskTimerWrap = 0x00FFFFFFu;
#endif
    /* Note, for f=0.0f, we get a float result of inf, which saturated to B=0xffffffff. */
    unsigned int B = (unsigned int)((float)CCL_PER_CLOCK / ((float)totalPrescale * f));
    if((B & ~maskTimerWrap) != 0u)
        B = maskTimerWrap;
    if(B <= 1u)
        B = 2u;
    *pB = B;
    const unsigned int A = (float)B * dutyCycle;
    if(A <= B)
        *pA = A;
    else
        *pA = B;
        
} /* calcBAForPWM */



/**
 * Basic initialization of a eMIOS device. The global settings are made; most important is
 * the global count rate, which is set to 10 MHz by means of the global prescaler. This
 * frequency is input to all channels and determines their timing resolution and ranges.
 *   @param pHDevice
 * A device handle object by reference. On return from the function, the handle has been
 * initialized. It is required for subsequent operations, like channel initialization.
 *   @param pEMIOS
 * The MCU has two or three eMIOS devices. They can be initialized inpedendently of each
 * other. Call the function twice if both devices are required. Specify either \a eMIOS_0,
 * \a eMIOS_1 or \a eMIOS_2 (only MPC5748G). Checked by assertion.
 *   @param devicePrescale
 * The peripheral clock, which is input to the device, is devided by this factor, before it
 * is routed to any channel. The channel have an input clock which is (#CCL_PER_CLOCK /
 * devicePrescale). Range 1..256, checked by assertion.
 *   @note
 * The driver doesn't allow re-initialization of the device. This is checked by assertion
 * in order to detect the situation, if different dependent drivers try to do the
 * initialization.
 */
void pwm_osInitEMIOSDevice( pwm_hEMIOSDevice_t * const pHDevice
                          , eMIOS_Type *pEMIOS
                          , unsigned int devicePrescale
                          )
{
#ifndef MCU_MPC5748G
    assert(pEMIOS == eMIOS_0  ||  pEMIOS == eMIOS_1);
#else    
    assert(pEMIOS == eMIOS_0  ||  pEMIOS == eMIOS_1  ||  pEMIOS == eMIOS_2);
#endif
    assert(devicePrescale <= 256u  &&  devicePrescale-1u <= eMIOS_MCR_GPRE_MASK);
    
#ifdef DEBUG
    /* We need an assertion to avoid double init; we may easily have different dependent
       client drivers of eMIOS, which may try to call this function. */
    static uint8_t SBSS_OS(isInitBitVec_) = 0x00u;
    const unsigned int maskThisEMIOS = pEMIOS == eMIOS_0? 0x01u: 0x02u;
    assert(((unsigned)isInitBitVec_ & maskThisEMIOS) == 0u);
    isInitBitVec_ |= maskThisEMIOS;
#endif

    pEMIOS->MCR =
          eMIOS_MCR_GPRE(0u)    /* Divide peripheral clock by n+1. */
          | eMIOS_MCR_ETB(0u)   /* STAC time base is disabled; Ch 23 drives ctr bus A */
#ifndef MCU_MPC5748G
          | eMIOS_MCR_SRV(0u)   /* STAC time base selection, doesn't care. */
#endif
          | eMIOS_MCR_GPREN(0u) /* Enable EMIOS_n clock? */
          | eMIOS_MCR_GTBE(0u)  /* Enable global time base? */
          | eMIOS_MCR_FRZ(0u);  /* Globally disable channel freeze when in debug mode.
                                   Freeze can be enabled only if all cores are normally
                                   running. */
    
    /* Bring all channels into passive base state, which is GPIO input.
         MPC5775B/E: The numbering of channels is not linear; see RM75 34.1.1, pp.1191f.
       Each device provides channels 0..7 and 16..23 only. The MCU pins are numbered/named
       EMIOS0..EMIOS31; EMIOS8..EMIOS15 means channels 0..7 of the second device and
       EMIOS24..EMIOS31 means channels 16..23 of the second device. In this module, all
       channel indexes need to be in range [0..7, 16..23].
         MPC5748G: All devices have channels at indexes 0..31 but they differ. The
       initialization depends. */
    unsigned int idxChn = 0u;
    for(idxChn=0u; idxChn<eMIOS_UC_COUNT; ++idxChn)
    {
        /* The indexes don't form a gapless range. Check each before use. */
        if(isChn(idxChn))
        {
            const pwm_hEMIOSChannel_t channel = { .pEMIOS = pEMIOS,
                                                  .pUC = &pEMIOS->UC[idxChn],
                                                  .idxChn = (uint8_t)idxChn,
                                                };
            selectBaseModeGPIO(&channel, /* counterInitialValue */ 0u);
        }
    }

    /* Eventually enable the clocks. */
    pEMIOS->MCR =
          eMIOS_MCR_GPRE(devicePrescale - 1u)  /* Divide peripheral clock by n+1. */
          | eMIOS_MCR_ETB(0u)   /* STAC time base is disabled; Ch 23 drives ctr bus A */
#ifndef MCU_MPC5748G
          | eMIOS_MCR_SRV(0u)   /* STAC time base selection, doesn't care. */
#endif
          | eMIOS_MCR_GPREN(1u) /* Enable EMIOS_n clock? */
          | eMIOS_MCR_GTBE(1u)  /* Enable global time base? */
          | eMIOS_MCR_FRZ(0u);  /* Globally disable channel freeze when in debug mode.
                                   Freeze can be enabled only if all cores are normally
                                   running. */
    pHDevice->pEMIOS = pEMIOS;
    
} /* pwm_osInitEMIOSDevice */




/**
 * Common code for initializing a channel as either frequency or duty cycle input. The
 * only difference between the two is the selection of another mode.\n
 *   See pwm_osInitEMIOSChannelForPeriodTimeMeasurement() for the meaning of the
 * parameters.
 */
static void initChannelAsPWMInput( pwm_hEMIOSChannel_t * const pHChannel
                                 , const pwm_hEMIOSDevice_t * const pHDevice
                                 , unsigned int idxChn
                                 , unsigned int channelPrescale
                                 , unsigned int glitchFilterStrength
                                 , bool isFreqInput
                                 )
{
    assert(isValidDeviceHandle(pHDevice));
    assert(channelPrescale >= 1u  &&  channelPrescale <= 4u
           &&  glitchFilterStrength <= 4u
           &&  isPossibleInputChn(pHDevice->pEMIOS, idxChn)
          );
    const eMIOS_Type * const pEMIOS = pHDevice->pEMIOS;
    eMIOS_UC_Type * const pUC = &pEMIOS->UC[idxChn];
    
    const unsigned int devicePrescale = ((pEMIOS->MCR & eMIOS_MCR_GPRE_MASK)
                                         >> eMIOS_MCR_GPRE_SHIFT
                                        ) + 1u;
    pHChannel->pEMIOS = pEMIOS;
    pHChannel->pUC = pUC;
    pHChannel->idxChn = (uint8_t)idxChn;
    pHChannel->prescale = devicePrescale*channelPrescale;
    pHChannel->tiClkChn = (float)pHChannel->prescale/(float)CCL_PER_CLOCK;
 
    /* Input filter setting IF: Allowed values are only 1, 2, 4, 8 (need 2*n values) or 0
       meaning off. */
    if(glitchFilterStrength > 0u)
        glitchFilterStrength = 1u << (glitchFilterStrength-1u);

    /* Bring channel into mode GPIO input first and write eMIOS_cnt to zero. */
    selectBaseModeGPIO(pHChannel, /* counterInitialValue */ 0u);

    /* We use the input period measurement mode (IPM), see RM75, 34.6.1.1.5, pp.1236f, to
       measure the period time of the input signal and mode input pulse width measurement
       (IPWM), RM75, 34.6.1.1.4, pp.1234f, for measureing the duty cycle. The configuration
       is identical except for the mode word.
         Note, the polarity matters for duty time (defined as time of high phase) but not
       for the period time. We configure it as needed for IPWM.
         The channel's own counter can be used. It wraps at its full range. The count
       frequency can be varied in four steps by the channel's own (additional) prescaler.
       This yields four measurement ranges. */
    const unsigned int  mode = isFreqInput? 0x5u: 0x4u;
    pUC->C =
          eMIOS_C_FREN(1u)      /* This channel's freeze when in debug mode. */
          | eMIOS_C_ODIS(0u)    /* 1: Channel output can be disabled by input signal, 0: on */
          | eMIOS_C_ODISSL(0u)  /* Input selection for output disable, doesn't care. */
          | eMIOS_C_UCPRE(channelPrescale - 1u) /* Channel prescaler, divide by n+1 */
          | eMIOS_C_UCPREN(1u)  /* Enable prescaler? */
          | eMIOS_C_DMA(0u)     /* 0: Flag raises IRQ, 1: requests DMA */
          | eMIOS_C_IF(glitchFilterStrength)    
          | eMIOS_C_FCK(0u)     /* Filter: 0: Use channel prescaler clock, 1: Module clock */
          | eMIOS_C_FEN(0u)     /* IRQ/DMA enable bit */
          | eMIOS_C_BSL(3u)     /* 3: Internal counter is running and take as time base */
          | eMIOS_C_EDSEL(0u)   /* Edge select, according to EDPOL */
          | eMIOS_C_EDPOL(1u)   /* IPWM: 1: Raising till falling edge, 0: vice versa */
          | eMIOS_C_MODE(mode); /* Mode is IPM or IPWM, both measure the distance of two
                                   edges. */
} /* initChannelAsPWMInput */



/**
 * Common code of result evaluation of either period time or duty cycle measurement. In
 * either case, the channel captures the time of two edges so that the difference can be
 * calculated - which is the final result for period or duty time measurement.
 *   @param pIsNewResult
 * Get \a true in * \a pIsNewResult if a time capture has for sure been seen the first time.
 * If a subsequent call of the function reads the still same register values then the
 * function returns \a false. Note, there's no way to consistently read the according falg
 * together with the result. Therefore, there's a very little chance to get a \a false
 * although the result is actually new.
 *   @param pHChannel
 * The handle of the channel by reference. Needs to be the valid handle of a channel, which
 * had been initialized using either pwm_osInitEMIOSChannelForPeriodTimeMeasurement() or
 * pwm_osInitEMIOSChannelForDutyTimeMeasurement().
 */
static inline unsigned int getInputChnDeltaTime( bool * const pIsNewResult
                                               , const pwm_hEMIOSChannel_t * const pHChannel
                                               )
{
    assert(isValidInputChnHandle(pHChannel));
    eMIOS_UC_Type * const pUC = pHChannel->pUC;
    assert((pUC->C & eMIOS_C_MODE_MASK & (~1u << eMIOS_C_MODE_SHIFT))
           == (4u << eMIOS_C_MODE_SHIFT)
          );

    /* Read flag first to see if the later read result is surely new. This order of doing
       means that we will rarely return a new result, which is still tagged as old but
       actually new. Which is harmless in comparison to the other way around. */
    const uint32_t S = pUC->S;

    /* It is most important to read A prior to B, only this way around it is guaranteed
       that the pair of values results from two consecutive edges and in known order. See
       RM75, 34.6.1.1.5, pp.1236ff. */
    const uint32_t A = pUC->A;
    const uint32_t B = pUC->B;
    
    /* We reset the flag unconditionally after reading A and B. It may have been set
       between reading it at the beginning and reading A and B. If we wouldn't negate it
       then a subsequent (soon) call of this function could return the same value A-B
       tagged as new result.
         The downside of unconditionally negating the flag is a subsequent result, tagged
       as not new but actually new. This is considered less harmful. */
    pUC->S = eMIOS_S_FLAG_MASK;
    
    /* The delta time is the 16 or 24 Bit difference A-B of the two captured times. (Length
       of timer registers needs to be considered.)
         Caution, there seems to be no possibility to recognize the situation that very
       low input frequencies lead to capture events not in same and not in consecutive
       counter cycles - which would mean that the low frequency is seen as a much higher,
       wrong one. The problem is irrelevant for applications, which regularly call this
       method and implement a timeout; the latter is anyway a must in order to not get
       stuck in case of a not at all fluctuating input. */
#ifdef MCU_MPC5748G
    const unsigned int maskTimerWrap = 0x0000FFFFu;
#else
    const unsigned int maskTimerWrap = 0x00FFFFFFu;
#endif
    const unsigned int tiDelta = (A - B) & maskTimerWrap;
    
    *pIsNewResult = (S & eMIOS_S_FLAG_MASK) != 0u;
    return tiDelta;

} /* getInputChnDeltaTime */




/** 
 * Initialization of a channel for the standard use case "Measure input period time".
 *   @param pHChannel
 * A channel handle object by reference. On return from the function, the handle has been
 * initialized. It is required for subsequent operations, like fetching measurement results.
 *   @param pHDevice
 * The handle by reference of the eMIOS device, which the initialized channel belongs to.
 * Result of an earlier call of pwm_osInitEMIOSDevice().
 *   @param idxChn
 * The channel to use for the operation. On the MPC5775B/E, the range is [0..7, 16..23]. On
 * the MPC5748G only channels of type G may be used (see RM48, Table 35-3, pp.980f). The
 * range is checked by assertion).\n
 *   Note, there's not so much flexiblity in the mapping MCU to eMIOS channel. So choosing
 * a channel effectively means choosing an MCU pin - even if this function won't touch the
 * MCU pin/port configuration.
 *   @param channelPrescale
 * The period time of the input is measured with a resolution of (#CCL_PER_CLOCK / (\a
 * devicePrescale * \a channelPrescale)), where \a devicePrescale relates to the argument
 * of the earlier call of pwm_osInitEMIOSDevice(). The channel's local prescaler has a
 * range of 1..4, checked by assertion.
 *   @param glitchFilterStrength
 * The input can be filtered from glitches, i.e., very short high or low phases, which are
 * considered not to belong into the true signal. An input level changes is taken as such
 * only if it is stable for N times the basic time resolution (see \a channelPrescale). Five
 * strengths are supported, values s=0..4 means N=2^s. (Effectively, s=0 means filer off.)
 * The range is check by assertion.
 */
void pwm_osInitEMIOSChannelForPeriodTimeMeasurement( pwm_hEMIOSChannel_t * const pHChannel
                                                   , const pwm_hEMIOSDevice_t * const pHDevice
                                                   , unsigned int idxChn
                                                   , unsigned int channelPrescale
                                                   , unsigned int glitchFilterStrength
                                                   )
{
    initChannelAsPWMInput( pHChannel
                         , pHDevice
                         , idxChn
                         , channelPrescale
                         , glitchFilterStrength
                         , /* isFreqInp */ true
                         );
} /* pwm_osInitEMIOSChannelForPeriodTimeMeasurement */



/**
 * Query a period time measuring input channel for the last recently captured result.
 *   @return
 * The channel measures the duration between two consecutive rising edges. The measurement
 * from the last recently seen pair of rising edges is returned. Unit is the period time of
 * the channel counter, i.e., ((\a devicePrescale * \a channelPrescale) / #CCL_PER_CLOCK),
 * where \a devicePrescale and \a channelPrescale mean the arguments of eMIOS device
 * initialization and channel initialization, respectively.
 *   @param pIsNewResult
 * Get \a true in * \a pIsNewResult if a time capture has for sure been seen the first
 * time. If a subsequent call of the function reads the still same register values then the
 * function returns \a false. Note, there's no way to consistently read the according flag
 * together with the result. Therefore, there's a very little chance to get a \a false
 * although the result is actually new.
 *   @param pHChannel
 * The handle of the channel by reference. Needs to be the valid handle of a channel, which
 * had been initialized using pwm_osInitEMIOSChannelForPeriodTimeMeasurement().
 *   @remark
 * An implementation of a timeout is needed in the client code: It may take arbitrarily
 * long to receice a new result (but of course not to return from this function). A timeout
 * must however not be defined to tight: If the input has an actual period time T then it
 * may take 2*T after getting a result, which is tagged "new" and until a subsequent call
 * of this function will get the next such result. This is due to the impossibility of
 * reading the flag and the result registers coherently. Therefore, and if the client code
 * wants to process inputfrequencies down to f_min, it must implement a timeout value,
 * which is not lesser than 2/f_min.
 */
unsigned int pwm_osGetChnInputPeriodTime( bool * const pIsNewResult
                                        , const pwm_hEMIOSChannel_t * const pHChannel
                                        )
{
    return getInputChnDeltaTime(pIsNewResult, pHChannel);

} /* pwm_osGetChnInputPeriodTime */



/** 
 * Initialization of a channel for the standard use case "Measure input pulse duration".
 * Which is equivalent to the duty cycle of an input PWM if the frequency of the same is
 * known. (The frequency can't be measured by the same channel at the same time.)
 *   @param pHChannel
 * A channel handle object by reference. On return from the function, the handle has been
 * initialized. It is required for subsequent operations, like fetching measurement results.
 *   @param pHDevice
 * The handle by reference of the eMIOS device, which the initialized channel belongs to.
 * Result of an earlier call of pwm_osInitEMIOSDevice().
 *   @param idxChn
 * The channel to use for the operation. On the MPC5775B/E, the range is [0..7, 16..23]. On
 * the MPC5748G only channels of type G may be used (see RM48, Table 35-3, pp.980f). The
 * range is checked by assertion).\n
 *   Note, there's not so much flexiblity in the mapping MCU to eMIOS channel. So choosing
 * a channel effectively means choosing an MCU pin - even if this function won't touch the
 * MCU pin/port configuration.
 *   @param channelPrescale
 * The duty time of the input is measured with a resolution of (#CCL_PER_CLOCK / (\a
 * devicePrescale * \a channelPrescale), where \a devicePrescale relates to the argument of
 * the earlier call of pwm_osInitEMIOSDevice(). The channel's local prescaler has a range
 * of 1..4, checked by assertion.
 *   @param glitchFilterStrength
 * The input can be filtered from glitches, i.e., very short high or low phases, which are
 * considered not to belong into the true signal. An input level changes is taken as such
 * only if it is stable for N times the basic time resolution (see \a channelPrescale). Five
 * strengths are supported, values s=0..4 means N=2^s. (Effectively, s=0 means filer off.)
 * The range is check by assertion.
 *   @note
 * The channel can't at the same time measure the pulse duration and period time so that
 * only the client code, which may have additional knowledge, can (possibly) calculate the
 * duty cycle as a a number 0..1 or 0..100%. This channel will jsut return the duration of
 * the high phases of the input signal.
 */
void pwm_osInitEMIOSChannelForDutyTimeMeasurement( pwm_hEMIOSChannel_t * const pHChannel
                                                 , const pwm_hEMIOSDevice_t * const pHDevice
                                                 , unsigned int idxChn
                                                 , unsigned int channelPrescale
                                                 , unsigned int glitchFilterStrength
                                                 )
{
    initChannelAsPWMInput( pHChannel
                         , pHDevice
                         , idxChn
                         , channelPrescale
                         , glitchFilterStrength
                         , /* isFreqInp */ false
                         );
} /* pwm_osInitEMIOSChannelForDutyTimeMeasurement */



/**
 * Query a PWM input channel for the last recently captured pulse duration time
 * measurement. 
 *   @return
 * The channel measures the duration between a rising edge and the immediately following
 * falling edge. The measurement from the last recently seen pair of rising edges is
 * returned. Unit is the period time of the channel counter, i.e., ((\a devicePrescale * \a
 * channelPrescale) / #CCL_PER_CLOCK), where \a devicePrescale and \a channelPrescale mean
 * the arguments of eMIOS device initialization and channel initialization, respectively.
 *   @param pIsNewResult
 * Get \a true in * \a pIsNewResult if a time capture has for sure been seen the first
 * time. If a subsequent call of the function reads the still same register values then the
 * function returns \a false. Note, there's no way to consistently read the according flag
 * together with the result. Therefore, there's a very little chance to get a \a false
 * although the result is actually new.
 *   @param pHChannel
 * The handle of the channel by reference. Needs to be the valid handle of a channel, which
 * had been initialized using pwm_osInitEMIOSChannelForDutyTimeMeasurement().
 *   @remark
 * An implementation of a timeout is needed in the client code: It may take arbitrarily
 * long to receice a new result (but of course not to return from this function). A timeout
 * must however not be defined to tight: If the input has an actual period time T then it
 * may take 2*T after getting a result, which is tagged "new" and until a subsequent call
 * of this function will get the next such result. This is due to the impossibility of
 * reading the flag and the result registers coherently. Therefore, and if the client code
 * wants to process input frequencies down to f_min, it must implement a timeout value,
 * which is not lesser than 2/f_min.
 */
unsigned int pwm_osGetChnInputDutyTime( bool * const pIsNewResult
                                      , const pwm_hEMIOSChannel_t * const pHChannel
                                      )
{
    return getInputChnDeltaTime(pIsNewResult, pHChannel);

} /* pwm_osGetChnInputDutyTime */



/** 
 * Initialization of a channel for the standard use case "Produce PWM with changeable
 * frequency and duty cycle".
 *   @param pHChannel
 * A channel handle object by reference. On return from the function, the handle has been
 * initialized. It is required for subsequent operations, like fetching measurement results.
 *   @param pHDevice
 * The handle by reference of the eMIOS device, which the initialized channel belongs to.
 * Result of an earlier call of pwm_osInitEMIOSDevice().
 *   @param idxChn
 * The channel to use for the operation.\n
 *   On the MPC5775B/E the Range is [0..7, 16..23] (checked by assertion).\n
 *   On the MPC5748G, the selected channel needs to be of type either "G" or "X". RM48,
 * 35.1.1, Table 35-2, pp.979ff tells about which channels are of appropriate type. This
 * is checked by assertion.\n
 *   Note, there's not so much flexiblity in the mapping MCU to eMIOS channel. So choosing
 * a channel effectively means choosing an MCU pin - even if this function won't touch the
 * MCU pin/port configuration.
 *   @param channelPrescale
 * The edges of the PWM are generated with a resolution of (#CCL_PER_CLOCK
 * / (\a devicePrescale * \a channelPrescale), where \a devicePrescale relates to the
 * argument of the earlier call of pwm_osInitEMIOSDevice(). The channel's local prescaler
 * has a range of 1..4, checked by assertion.
 *   @param isInverted
 * \a isInverted relates to the meaning of the specified duty cycles. If \a false is given,
 * then a DC of 0% would mean output always low and 100% would mean output always high. If
 * \a true is given, then it's vice versa.
 *   @param initialFrequency
 * The initial frequency in Hz.\n
 *   The minimum frequency is the reciprocal of (2^N-1) times the configured resolution,
 * where N is 24 for the MPC5775B/E and 16 for the MPC5748G.\n
 *   The maximum frequency is the reciprocal of two times the configured resolution.\n
 *   The specified floating point value is silently limited to this range.
 *   @param initialDutyCycle
 * The initial duty cycle in the range 0..1. The specified floating point value is silently
 * limited to this range.
 */
void pwm_osInitEMIOSChannelForPWMGeneration( pwm_hEMIOSChannel_t * const pHChannel
                                           , const pwm_hEMIOSDevice_t * const pHDevice
                                           , unsigned int idxChn
                                           , unsigned int channelPrescale
                                           , bool isInverted
                                           , float initialFrequency
                                           , float initalDutyCycle
                                           )
{
    assert( isValidDeviceHandle(pHDevice)
            &&  channelPrescale >= 1u  &&  channelPrescale <= 4u
            &&  initialFrequency > 0.0f
            &&  isPossibleOutputChn(pHDevice->pEMIOS, idxChn)
          );

    const eMIOS_Type * const pEMIOS = pHDevice->pEMIOS;
    eMIOS_UC_Type * const pUC = &pEMIOS->UC[idxChn];
    const unsigned int devicePrescale = ((pEMIOS->MCR & eMIOS_MCR_GPRE_MASK)
                                         >> eMIOS_MCR_GPRE_SHIFT
                                        ) + 1u;
    pHChannel->pEMIOS = pEMIOS;
    pHChannel->pUC = pUC;
    pHChannel->idxChn = (uint8_t)idxChn;
    pHChannel->prescale = devicePrescale*channelPrescale;
    pHChannel->tiClkChn = (float)pHChannel->prescale/(float)CCL_PER_CLOCK;

    /* Ensure that channel is in mode GPIO and write eMIOS_cnt to 1: Counter needs to be in
       the range of register B as set below. Otherwise the first PWM period is wrong. */
    selectBaseModeGPIO(pHChannel, /* counterInitialValue */ 1u);

    /* We use the buffered output pulse width and frequency modulation mode (OPWFMB), see
       RM75, 34.6.1.1.14, pp.1253ff. "Buffered" relates to the possibility of setting
       period and duty cycle synchronized with the beginning of a new period.
         Caution, the manual, RM75, 34.6.1.1.14, pp.1253ff, is ambiguous in saying which
       mode bit is variable to specify the behavior of the output disable function. The
       text say bit 6, whereas all tables indicate bit 5 (counted in PPC manner from the
       left). We trust the tables. */
    const unsigned int mode = 0x58u;

    uint32_t B;
    uint32_t A;
    calcBAForPWM(&B, &A, initialFrequency, initalDutyCycle, pHChannel->prescale);

    pUC->B = B;   /* Period of output is B counter clock ticks. */
    pUC->A = A;   /* Active phase of period is A counter clock ticks. */
    pUC->C =
        eMIOS_C_FREN(1u)      /* This channel's freeze when in debug mode. */
        | eMIOS_C_ODIS(0u)    /* 1: Channel output can be disabled by input signal, 0: on */
        | eMIOS_C_ODISSL(0u)  /* Input selection for output disable, doesn't care. */
        | eMIOS_C_UCPRE(channelPrescale - 1u) /* Channel prescaler, divide by n+1 */
        | eMIOS_C_UCPREN(1u)  /* Channel prescaler needs to be enabled in this mode */
        | eMIOS_C_DMA(0u)     /* 0: Flag raises IRQ, 1: requests DMA */
        | eMIOS_C_IF(0u)      /* Input filter setting, doesn't care. */
        | eMIOS_C_FCK(0u)     /* Filter: 0: Use channel prescaler clock, 1: Module clock */
        | eMIOS_C_FEN(0u)     /* IRQ/DMA enable bit */
        | eMIOS_C_BSL(3u)     /* Doesn't care, always use internal counter in this mode. */
        | eMIOS_C_EDSEL(0u)   /* Edge select, irrelevant in mode OPWFMB */
        | eMIOS_C_EDPOL(isInverted? 1u: 0u)   /* Polarity of generated waveform */
        | eMIOS_C_MODE(mode); /* Mode is OPWFMB, i.e. normal PWM generation. */

} /* pwm_osInitEMIOSChannelForPWMGeneration */



/**
 * Set new values for frequency and dutyCycle of a running PWM output channel. The new
 * settings are synchronized with the PWM periods; they take effect with the next PWM
 * period only.
 *   @param pHChannel
 * The handle of the channel by reference. Needs to be the valid handle of a channel, which
 * had been initialized using pwm_osInitEMIOSChannelForPWMGeneration().
 *   @param f
 * The new frequency in Hz.\n
 *   The minimum frequency is the reciprocal of (2^N-1) times the configured resolution,
 * where N is 24 for the MPC5775B/E and 16 for the MPC5748G.\n
 *   The maximum frequency is the reciprocal of two times the configured resolution.\n
 *   The specified floating point value is silently limited to this range.
 *   @param dutyCycle
 * The new duty cycle in the range 0..1. The specified floating point value is silently
 * limited to this range.
 *   @remark
 * The function can be used at any time from any context on any core. However, if more than
 * a single PWM channel is in use than all possibly competing calls need to be done from
 * one and the same core.
 *   @remark
 * The function has race conditions with pwm_osSetChnDutyCycle(). Both of them
 * mustn't be called at a time.
 */
void pwm_osSetChnFrequencyAndDutyCycle( const pwm_hEMIOSChannel_t * const pHChannel
                                      , float f
                                      , float dutyCycle
                                      )
{
    assert(isValidOutputChnHandle(pHChannel));
    eMIOS_Type * const pEMIOS = pHChannel->pEMIOS;
    eMIOS_UC_Type * const pUC = pHChannel->pUC;
    assert((pUC->C & eMIOS_C_MODE_MASK) == (0x58u << eMIOS_C_MODE_SHIFT));

    uint32_t B;
    uint32_t A;
    calcBAForPWM(&B, &A, f, dutyCycle, pHChannel->prescale);

    /* To ensure that both register A and B are modified in the very same clock tick, we
       need to first lock the update, then write both registers and eventually re-enable
       the update. A and B will be coincidentally transferred to the shadow registers A2
       and B2 in then next system clock tick and coincidentally transferred to the actual
       registers A1 and B1, when the next PWM period starts.
         It is not possible to access the bits without possible race conditions. We need a
       critical section. */
    const unsigned int mask = 1u << (unsigned)pHChannel->idxChn;
    uint32_t state = rtos_osEnterCriticalSection();
    pEMIOS->OUDIS |= mask;
    pUC->B = B;   /* New period of output is B counter clock ticks. */
    pUC->A = A;   /* New active phase of period is A counter clock ticks. */
    pEMIOS->OUDIS &= ~mask;
    rtos_osLeaveCriticalSection(state);

} /* pwm_osSetChnFrequencyAndDutyCycle */



/**
 * Set a new value for the duty cycle for a channel, which has been configured for PWM
 * output. The duty cycle is changed for the running PWM output, synchronized with the next
 * starting PWM period.\n
 *   This API is also intended for (temporarily) stopping and re-starting a PWM output
 * channel. Set the duty cycle to either 0.0 or 1.0 to stop PWM output: The output will
 * remain at constant low or high level, respectively.
 *   @param pHChannel
 * The handle of the channel by reference. Needs to be the valid handle of a channel, which
 * had been initialized using pwm_osInitEMIOSChannelForPWMGeneration().
 *   @param dutyCycle
 * The new duty cycle in the range is 0..1. The specified floating point value is
 * silently limited to this range.
 *   @remark
 * The function can be used at any time from any context on any core.
 *   @remark
 * The function has race conditions with pwm_osSetChnFrequencyAndDutyCycle(). Both of them
 * mustn't be called at a time.
 */
void pwm_osSetChnDutyCycle(const pwm_hEMIOSChannel_t * const pHChannel, float dutyCycle)
{
    assert(isValidOutputChnHandle(pHChannel));
    eMIOS_UC_Type * const pUC = pHChannel->pUC;
    assert((pUC->C & eMIOS_C_MODE_MASK) == (0x58u << eMIOS_C_MODE_SHIFT));
    
    /* Use register B to read the current value of B1, i.e. the current period time. */
    const unsigned int T = pUC->B;
    
    /* For sake of performance, we use the most simple saturation code in case of bad duty
       cycle values. The float-to-int conversion saturates implicitly to the implementation
       range of the integer and we need to further limit to the value of register B1. */
    unsigned int dcNew = (unsigned int)((float)T * dutyCycle);
    if(dcNew > T)
        dcNew = T;

    /* Use register A to write to A2, i.e. the shadow register for the period time,
       which is loaded into A1, when the next PWM period starts. */
    pUC->A = dcNew;
    
} /* pwm_osSetChnDutyCycle */


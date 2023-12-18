#ifndef PWM_MODULARIOSUBSYSTEM_INCLUDED
#define PWM_MODULARIOSUBSYSTEM_INCLUDED
/**
 * @file pwm_modularIOSubsystem.h
 * Definition of global interface of module pwm_modularIOSubsystem.c
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

/*
 * Include files
 */

/** @todo Define either MCU_MPC5748G, MCU_MPC5775B or MCU_MPC5775E to select the MCU, which
    this module is compiled for. */
#define MCU_MPC5748G

#include <stdlib.h>
#include "typ_types.h"

/* Include the appropriate MCU header. */
#if defined(MCU_MPC5748G)
# include "MPC5748G.h"
#elif defined(MCU_MPC5775B)
# include "MPC5775B.h"
#elif defined(MCU_MPC5775E)
# include "MPC5775E.h"
#else
# error Unsupported MCU configured
#endif

/*
 * Defines
 */


/*
 * Global type definitions
 */

/** The handle for an eMIOS device. Such a handle is got from the device initialization
    call and it is required to configure a channel of that device. */
typedef struct pwm_hEMIOSDevice_t
{
    /** The MCU's eMIOS device by reference. */
    eMIOS_Type *pEMIOS;

} pwm_hEMIOSDevice_t;


/** The device header doesn't name the type of the eMIOS Unified Channel. Here we do. */
typedef typeof(((eMIOS_Type*)NULL)->UC[0]) eMIOS_UC_Type;

/** The handle for an eMIOS channel. Such a handle is got from the channel initialization
    call and it is required to access channel parameters or measurement results. */
typedef struct pwm_hEMIOSChannel_t
{
    /** The MCU's eMIOS device by reference, which the channel belongs to. */
    eMIOS_Type *pEMIOS;

    /** The MCU's eMIOS channel by reference. */
    eMIOS_UC_Type * pUC;
    
    /** The zero based index of the channel in the device. */
    uint8_t idxChn;
    
    /** Factor between peripheral clock rate and count rate of channel. */
    uint16_t prescale;
    
    /** Time resolution of channel in s. */
    float tiClkChn;

} pwm_hEMIOSChannel_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialize one of the eMIOS devices. */
void pwm_osInitEMIOSDevice( pwm_hEMIOSDevice_t * const pHDevice
                          , eMIOS_Type *pEMIOS
                          , unsigned int devicePrescale
                          );

/** Configure a channel for period time measurement. */
void pwm_osInitEMIOSChannelForPeriodTimeMeasurement( pwm_hEMIOSChannel_t * const pHChannel
                                                   , const pwm_hEMIOSDevice_t * const pHDevice
                                                   , unsigned int idxChn
                                                   , unsigned int channelPrescale
                                                   , unsigned int glitchFilterStrength
                                                   );

/** Query a PWM input channel for the last recently captured period time result. */
unsigned int pwm_osGetChnInputPeriodTime( bool * const pIsNewResult
                                        , const pwm_hEMIOSChannel_t * const pHChannel
                                        );

/** Configure a channel for duty time measurement. */
void pwm_osInitEMIOSChannelForDutyTimeMeasurement( pwm_hEMIOSChannel_t * const pHChannel
                                                 , const pwm_hEMIOSDevice_t * const pHDevice
                                                 , unsigned int idxChn
                                                 , unsigned int channelPrescale
                                                 , unsigned int glitchFilterStrength
                                                 );

/** Query a PWM input channel for the last recently captured duty time result. */
unsigned int pwm_osGetChnInputDutyTime( bool * const pIsNewResult
                                      , const pwm_hEMIOSChannel_t * const pHChannel
                                      );

/** Configure a channel for PWM generation. */
void pwm_osInitEMIOSChannelForPWMGeneration( pwm_hEMIOSChannel_t * const pHChannel
                                           , const pwm_hEMIOSDevice_t * const pHDevice
                                           , unsigned int idxChn
                                           , unsigned int channelPrescale
                                           , bool isInverted
                                           , float initialFrequency
                                           , float initalDutyCycle
                                           );

/** Coincidentally set frequency and duty cyle of running PWM. */
void pwm_osSetChnFrequencyAndDutyCycle( const pwm_hEMIOSChannel_t * const pHChannel
                                      , float f
                                      , float dutyCycle
                                      );

/** Set duty cycle of running PWM without modifying the frequency. */
void pwm_osSetChnDutyCycle(const pwm_hEMIOSChannel_t * const pHChannel, float dutyCycle);


/*
 * Global inline functions
 */

/**
 * All measured timings are scaled in clock ticks of the affected channel. This unit of
 * measurement results can be queried using this function.
 *   @return
 * Get the unit of time measurement results in s.
 *   @param pHChannel
 * The affected channel. Before invoking this function, it had been initialiazed as input
 * of either the period time or the duty time.
 *   @remark
 * The function can be called at any time (after channel initialization) by any context
 * (even user), which has read access to the channel handle.
 */
static inline float pwm_osGetChnClockPeriod(const pwm_hEMIOSChannel_t * const pHChannel)
{
    return pHChannel->tiClkChn;
}


/**
 * A channel, which had been configured for PWM output can vary its frequency only to a
 * limited extend, depending on the width of the timers, the system clock configuration and
 * the configured prescalers. This function returns the lowest frequency, which can be set
 * for a given output channel and using pwm_osSetChnFrequencyAndDutyCycle().
 *   @return
 * Get the lowest possible frequency in Hz.
 *   @param pHChannel
 * The affected channel. Before invoking this function, it had been initialiazed as PWM
 * output.
 *   @remark
 * The function can be called at any time (after channel initialization) by any context
 * (even user), which has read access to the channel handle.
 */
static inline float pwm_osGetChnMinPWMFrequency(const pwm_hEMIOSChannel_t * const pHChannel)
{
#ifdef MCU_MPC5748G
    const unsigned int timerCntMax = 0x00010000u;
#else
    const unsigned int timerCntMax = 0x01000000u;
#endif
    return 1.0f / ((float)timerCntMax * pHChannel->tiClkChn);
}


/**
 * A channel, which had been configured for PWM output can vary its frequency only to a
 * limited extend, depending on the width of the timers, the system clock configuration and
 * the configured prescalers. This function returns the highest frequency, which can be set
 * for a given output channel and using pwm_osSetChnFrequencyAndDutyCycle().
 *   @return
 * Get the highest possible frequency in Hz and such that the remaining resolution for the
 * duty cycle is still 0.01 (1%). (Higher frequencies could be commanded but the duty cycle
 * can then be set only in coarse steps.)
 *   @param pHChannel
 * The affected channel. Before invoking this function, it had been initialiazed as PWM
 * output.
 *   @remark
 * The function can be called at any time (after channel initialization) by any context
 * (even user), which has read access to the channel handle.
 */
static inline float pwm_osGetChnMaxPWMFrequency(const pwm_hEMIOSChannel_t * const pHChannel)
{
    return 0.01f / pHChannel->tiClkChn;
}


#endif  /* PWM_MODULARIOSUBSYSTEM_INCLUDED */

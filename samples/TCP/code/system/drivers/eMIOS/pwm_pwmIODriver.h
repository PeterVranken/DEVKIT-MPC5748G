#ifndef PWM_PWMIODRIVER_INCLUDED
#define PWM_PWMIODRIVER_INCLUDED
/**
 * @file pwm_pwmIODriver.h
 * Definition of global interface of module pwm_pwmIODriver.c
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

#include "typ_types.h"
#include "rtos.h"
#include "ccl_configureClocks.h"


/*
 * Defines
 */

/** Index of system call for setting PWM frequency and duty cycle. */
#define PWM_SYSCALL_SET_PWM_OUT_F_AND_DC    35u

/** Index of system call for getting period or duty time of a PWM input. */
#define PWM_SYSCALL_GET_PWM_IN_TIME         36u


/*
 * Global type definitions
 */

/** The list of supported, available PWM outputs. */
typedef enum pwm_pwmOutChannel_t
{
    pwm_pwmOChn_LED_2_DS10 = 0u,/// PWM output driving user LED 2, DS10
    pwm_pwmOChn_LED_4_DS11,     /// PWM output driving user LED 4, DS11
    pwm_pwmOChn_LED_5_DS5,      /// PWM output driving user LED 5, DS5
    pwm_pwmOChn_PA1_J3_pin1,    /// PWM output on pin 1 of extension port J3
    
    pwm_pwmOChn_noPwmOutputs,   /// The total number of supported PWM outputs.
    
} pwm_pwmOutChannel_t;


/** The list of supported, available PWM duty time inputs and period time inputs. */
typedef enum pwm_pwmInChannel_t
{
    /** PWM input reading the period time at PA2, pin 3 of extension port J3. */
    pwm_pwmIChn_PA2_J3_pin3_periodTime = 0u,
    
    /** PWM input reading the duty time at PA6, pin 1 of extension port J2. */
    pwm_pwmIChn_PA6_J2_pin1_dutyTime,
    
    /** The total number of supported PWM inputs. */
    pwm_pwmIChn_noPwmDutyTimeInputs,
    
} pwm_pwmInChannel_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Initialize the simple PWM test and demonstration driver. */ 
void pwm_osInitIODriver(void);


/*
 * Global inline functions
 */

/**
 * Set frequency and duty cycle of a PWM output.\n
 * Some of the supported channels are connected to the user LEDs on the DEVKIT-MPC5748G so
 * that the effect can be visibly observed.
 *   @param pwmOutputChn
 * The affected PWM output.
 *   @param f
 * The desired frequency in Hz. The specified floating point value is silently limited to
 * the technically available range.
 *   @param dutyCycle
 * The new duty cycle in the range 0..1. The specified floating point value is silently
 * limited to this range.
 *   @note
 * This function must be called solely from user tasks. Any attempt to call it from
 * supervisor mode will halt software execution. Consider using
 * pwm_osSetChnFrequencyAndDutyCycle() instead.
 */
static inline void pwm_setChnFrequencyAndDutyCycle( pwm_pwmOutChannel_t pwmOutputChn
                                                  , float f
                                                  , float dutyCycle
                                                  )
{
    rtos_systemCall(PWM_SYSCALL_SET_PWM_OUT_F_AND_DC, pwmOutputChn, f, dutyCycle);

} /* pwm_setChnFrequencyAndDutyCycle */


/**
 * Get the period time of a PWM period time input.\n
 *   Some of the supported channels are configured for period time input. Only those can be
 * used with this API.
 *   @return
 * Get the period time in Seconds.
 *   @param pIsNewResult
 * For low input frequencies, or even not at all fluctuating input, it may happen that no
 * two edges have been seen since the previous call of this function for the given channel.
 * In this case * \a pIsNewResult is set to \a false. Normally, it'll be \a true and the
 * returned time designation is reliable.
 *   @param pwmInputChn
 * The addressed PWM input.
 *   @note
 * This function must be called solely from user tasks. Any attempt to call it from
 * supervisor mode will halt software execution. Consider using
 * pwm_osGetChnInputPeriodTime() instead.
 */
static inline float pwm_getChnInputPeriodTime( bool *pIsNewResult
                                             , pwm_pwmInChannel_t pwmInputChn
                                             )
{
    /// @todo Properly export these constants and connect them to the true code
    const float tiUnit = 256.0f / (float)CCL_PER_CLK_FS80;
    uint32_t sysCallResult = rtos_systemCall(PWM_SYSCALL_GET_PWM_IN_TIME, pwmInputChn);

    /* The system call returns the information "is a repeated, old result" in the otherwise
       unused MSB. */
    if((sysCallResult & 0x80000000u) != 0)
    {         
        *pIsNewResult = false;
        sysCallResult &= ~0x80000000u;
    }
    else
        *pIsNewResult = true;

    return tiUnit * (float)sysCallResult;

} /* pwm_getChnInputPeriodTime */



/**
 * Get the duty time of a PWM period time input, i.e. the duration of the last recent high
 * phase of the input signal.\n
 *   Some of the supported channels are configured for duty time input. Only those can be
 * used with this API.
 *   @return
 * Get the duty time in Seconds.
 *   @param pIsNewResult
 * For low input frequencies, or even not at all fluctuating input, it may happen that no
 * two edges have been seen since the previous call of this function for the given channel.
 * In this case * \a pIsNewResult is set to \a false. Normally, it'll be \a true and the
 * returned time designation is reliable.
 *   @param pwmInputChn
 * The addressed PWM input.
 *   @note
 * This function must be called solely from user tasks. Any attempt to call it from
 * supervisor mode will halt software execution. Consider using
 * pwm_osGetChnInputDutyTime() instead.
 */
static inline float pwm_getChnInputDutyTime(bool *pIsNewResult, pwm_pwmInChannel_t pwmInputChn)
{
    /* Actually, this function is just a better named alias of just the same system call to
       return a measured time. */
    return pwm_getChnInputPeriodTime(pIsNewResult, pwmInputChn);

} /* pwm_getChnInputDutyTime */

#endif  /* PWM_PWMIODRIVER_INCLUDED */

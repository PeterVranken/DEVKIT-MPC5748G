/**
 * @file pwm_test.c
 * Some simple test or demonstration code for the eMIOS operation. We configure those channel
 * as PWM output, which support the mode "Output Pulse Width and Frequency Modulation
 * Buffered" (OPWFMB) and which are connected to a user LED. The LEDs 2 (DS10), 5 (DS5) and
 * 4 (DS11) can be controlled by PWM.\n
 *   The actual PWM driver is found as file pwm_modularIOSubsystem.c. It supports the
 * channels of group G and X. (The other channels, which don't have an own time base, would
 * require some extension code for sharing the clock with a master channel.)
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
 *   pwm_osInitIODriver
 *   pwm_setChnFrequencyAndDutyCycle (inline)
 *   pwm_getChnInputPeriodTime (inline)
 *   pwm_getChnInputDutyTime (inline)
 * Local functions
 *   pwm_scSmplHdlr_setPwmOutFAndDc
 */

/*
 * Include files
 */

#include "pwm_pwmIODriver.h"

#include <stdio.h>
#include <assert.h>
#include "typ_types.h"
#include "siu_siuPortDriver.h"
#include "pwm_modularIOSubsystem.h"
#include "f2d_float2Double.h"
#include "pwm_pwmIODriver_defSysCalls.h"

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

static pwm_hEMIOSChannel_t SBSS_OS(_hChn6_PWM_IN_PA6_J2_pin1);
static pwm_hEMIOSChannel_t SBSS_OS(_hChn2_PWM_IN_PA2_J3_pin3);
static pwm_hEMIOSChannel_t SBSS_OS(_hChn1_PWM_OUT_PA1_J3_pin1);
static pwm_hEMIOSChannel_t SBSS_OS(_hChn0_LED_2_DS10);
static pwm_hEMIOSChannel_t SBSS_OS(_hChn4_LED_4_DS11);
static pwm_hEMIOSChannel_t SBSS_OS(_hChn7_LED_5_DS5);


/*
 * Function implementation
 */

/**
 * Initialize the simple PWM test driver.
 */
void pwm_osInitIODriver(void)
{
    /* Initialize the eMIOS PWM driver. We just need EMIOS_0 to drive an LED. */
    pwm_hEMIOSDevice_t hEMIOS0;
    pwm_osInitEMIOSDevice(&hEMIOS0, eMIOS_0, /* globalPrescale */ 256u);

    /* Initialize eMIOS0 channels, 0, 4, 7 as PWM output. They are connected to LEDs DS10,
       DS11, DS5 at ports PA0, PA4, PA7, respectively. (These LEDs need to be disabled in
       our standard LED driver, see lbd_ledAndButtonDriver.h.) */
    pwm_osInitEMIOSChannelForPWMGeneration( &_hChn0_LED_2_DS10
                                          , &hEMIOS0
                                          , /* idxChn */ 0u
                                          , /* prescale */ 4u
                                          , /* isInverted */ true
                                          , /* initialFrequency */ 3.0f
                                          , /* initalDutyCycle */ 0.7f
                                          );
    pwm_osInitEMIOSChannelForPWMGeneration( &_hChn4_LED_4_DS11
                                          , &hEMIOS0
                                          , /* idxChn */ 4u
                                          , /* prescale */ 4u
                                          , /* isInverted */ true
                                          , /* initialFrequency */ 5.0f
                                          , /* initalDutyCycle */ 0.1f
                                          );
    pwm_osInitEMIOSChannelForPWMGeneration( &_hChn7_LED_5_DS5
                                          , &hEMIOS0
                                          , /* idxChn */ 7u
                                          , /* prescale */ 4u
                                          , /* isInverted */ true
                                          , /* initialFrequency */ 10.0f
                                          , /* initalDutyCycle */ 0.3f
                                          );

    /* Common output configuration. */
    siu_portOutCfg_t outputCfg =
    {
      .idxPortSource_SSS = 0u,
      .enableReadBack = false,
      .enableOpenDrain_ODE = true, /* Enable open drain, LED connected to Vcc. */
      .maxSlewRate_SRC = 3u, /* Slew rate: Full drive without SR control. RM48, 15.2.11,
                                pp.388ff. */
    };

    /* We configure port PA0 as open drain output. */
    unsigned int SIUL_idxP = 0u
               , SIUL_P_SSS = 1u;

    /* Acquire port for exclusive use with this driver. */
    bool gotIt ATTRIB_DBG_ONLY = siu_osAcquirePort(SIUL_idxP);
    assert(gotIt);

    /* Configure port for LED. */
    outputCfg.idxPortSource_SSS = SIUL_P_SSS;
    siu_osConfigureOutput(SIUL_idxP, &outputCfg);

    /* We configure port PA4 as open drain output. */
    SIUL_idxP = 4u;
    SIUL_P_SSS = 1u;

    /* Acquire port for exclusive use with this driver. */
    gotIt = siu_osAcquirePort(SIUL_idxP);
    assert(gotIt);

    /* Configure port. */
    outputCfg.idxPortSource_SSS = SIUL_P_SSS;
    siu_osConfigureOutput(SIUL_idxP, &outputCfg);

    /* We configure port PA7 as open drain output. */
    SIUL_idxP = 7u;
    SIUL_P_SSS = 1u;

    /* Acquire port for exclusive use with this driver. */
    gotIt = siu_osAcquirePort(SIUL_idxP);
    assert(gotIt);

    /* Configure port. */
    outputCfg.idxPortSource_SSS = SIUL_P_SSS;
    siu_osConfigureOutput(SIUL_idxP, &outputCfg);

    printf( "PWM frequency range for LED DS11: %.3f .. %.3f Hz\r\n"
          , f2d(pwm_osGetChnMinPWMFrequency(&_hChn0_LED_2_DS10))
          , f2d(pwm_osGetChnMaxPWMFrequency(&_hChn0_LED_2_DS10))
          );


    /* Initialize channel 1 as (faster, prescale=1) PWM output and channels 2 and 6 and
       inputs. For this sample, the intention is to connect the MCU pin PA1 with PA2
       and PA6, to generate a PWM at PA1 and to measure its period time with PA2 and to
       measure its pulse-high time (duty time) with PA6. On the extension ports, this means
       two wires from J3, pin1, to J2, pin1, and to J3, pin3. */
    pwm_osInitEMIOSChannelForPWMGeneration( &_hChn1_PWM_OUT_PA1_J3_pin1
                                          , &hEMIOS0
                                          , /* idxChn */ 1u
                                          , /* prescale */ 1u
                                          , /* isInverted */ false
                                          , /* initialFrequency */ 500.0f
                                          , /* initalDutyCycle */ 0.5f
                                          );
    pwm_osInitEMIOSChannelForPeriodTimeMeasurement( &_hChn2_PWM_IN_PA2_J3_pin3
                                                  , &hEMIOS0
                                                  , /* idxChn */ 2u
                                                  , /* prescale */ 1u
                                                  , /* glitchFilterStrength */ 4u
                                                  );
    pwm_osInitEMIOSChannelForDutyTimeMeasurement( &_hChn6_PWM_IN_PA6_J2_pin1
                                                , &hEMIOS0
                                                , /* idxChn */ 6u
                                                , /* prescale */ 1u
                                                , /* glitchFilterStrength */ 4u
                                                );

    /* Acquire and configure port PA1 as output, which should be connected to PA2 and PA6,
       which are configured as PWM inputs. */
    SIUL_idxP = 1u;
    SIUL_P_SSS = 1u;
    gotIt = siu_osAcquirePort(SIUL_idxP);
    assert(gotIt);
    outputCfg.idxPortSource_SSS = SIUL_P_SSS;
    outputCfg.enableOpenDrain_ODE = false;
    siu_osConfigureOutput(SIUL_idxP, &outputCfg);

    printf( "PWM frequency range for output PA1: %.3f .. %.3f Hz\r\n"
          , f2d(pwm_osGetChnMinPWMFrequency(&_hChn1_PWM_OUT_PA1_J3_pin1))
          , f2d(pwm_osGetChnMaxPWMFrequency(&_hChn1_PWM_OUT_PA1_J3_pin1))
          );

    /* Acquire and configure port PA2, our PWM period time input in this sample application. */
    siu_portInCfg_t inputCfg =
    {
        .enableHysteresis_HYS = true,
        .pullUpDownCfg = siu_pullRes_pullUp,
        .idxMultiplexerRegister = 2u,
        .idxInputSource_MUXSELVALUE = 2u,
    };
    SIUL_idxP = 2u;
    gotIt = siu_osAcquirePort(SIUL_idxP);
    assert(gotIt);
    siu_osConfigureInput(SIUL_idxP, &inputCfg);
    
    /* Acquire and configure port PA6, our PWM duty time input in this sample application. */
    SIUL_idxP = 6u;
    inputCfg.idxMultiplexerRegister = 6u;
    inputCfg.idxInputSource_MUXSELVALUE = 2u;
    gotIt = siu_osAcquirePort(SIUL_idxP);
    assert(gotIt);
    siu_osConfigureInput(SIUL_idxP, &inputCfg);

} /* End of pwm_osInitIODriver */




/**
 * Sample implementation of a system call of conformance class "simple". Such a
 * system call can be implemented in C but it needs to be run with all interrupts
 * suspended. It cannot be preempted. Suitable for short running services only.\n
 *   Here we use the concept to implement an I/O driver for a few supported PWM outputs of
 * the DEVKIT-MPC5748G. Frequency and duty cycle can be set or changed. Some of the outputs
 * are connected to the user LEDs so that the effect can be visibly observed.
 *   @return
 * The function has no result an returns always zero.
 *   @param pidOfCallingTask
 * Process ID of calling user task.
 *   @param pwmOutputChn
 * The affected PWM output.
 *   @param f
 * The desired frequency in Hz. The specified floating point value is silently limited to
 * the technically available range.
 *   @param dutyCycle
 * The new duty cycle in the range 0..1. The specified floating point value is silently
 * limited to this range.
 *   @remark
 * Never call this function directly.
 */
uint32_t pwm_scSmplHdlr_setPwmOutFAndDc( uint32_t pidOfCallingTask ATTRIB_UNUSED
                                       , pwm_pwmOutChannel_t pwmOutputChn
                                       , float f
                                       , float dutyCycle
                                       )
{
    /* A safe, "trusted" implementation needs to double check the range of all arguments,
       so that the later execution of the underlaying I/O driver routine will surely not
       fail, which means primarily that it won't go into an assertion in DEBUG
       compilation. For this function, this relates only to the channel designation. */
    switch(pwmOutputChn)
    {
    case pwm_pwmOChn_LED_2_DS10:
        pwm_osSetChnFrequencyAndDutyCycle(&_hChn0_LED_2_DS10, f, dutyCycle);
        break;

    case pwm_pwmOChn_LED_4_DS11:
        pwm_osSetChnFrequencyAndDutyCycle(&_hChn4_LED_4_DS11, f, dutyCycle);
        break;

    case pwm_pwmOChn_LED_5_DS5:
        pwm_osSetChnFrequencyAndDutyCycle(&_hChn7_LED_5_DS5, f, dutyCycle);
        break;

    case pwm_pwmOChn_PA1_J3_pin1:
        pwm_osSetChnFrequencyAndDutyCycle(&_hChn1_PWM_OUT_PA1_J3_pin1, f, dutyCycle);
        break;

    default:
        /* Abort this system call and the calling user task and count this event as an
           error in the process the failing task belongs to. */
        rtos_osSystemCallBadArgument();

        /* rtos_osSystemCallBadArgument() doesn't return. We never get here. */
    }

    /* This function doesn't have a result but a system call still demands a result value. */
    return 0u;

} /* pwm_scSmplHdlr_setPwmOutFAndDc */




/**
 * Sample implementation of a system call of conformance class "simple". Such a
 * system call can be implemented in C but it needs to be run with all interrupts
 * suspended. It cannot be preempted. Suitable for short running services only.\n
 *   Here we use the concept to implement an I/O driver for a few supported PWM inputs of
 * the DEVKIT-MPC5748G. Period or duty cycle can be read via the low level driver.
 *   @return
 * The time designation is returned in bits 0..15. See pwm_osGetChnInputPeriodTime() and
 * pwm_osGetChnInputDutyTime() for scaling and range. It depends on the selected channel,
 * which of the two time designations, period or duty time, applies.\n
 *   MSB, bit 31, is set if no new result has been received since the last call of this API
 * for the given channel. In which result the function will just return the same old, stale
 * time designation as in the previous call. Bit 31 will typically be set in case of low
 * input frequencies or if there are even not fluctuations of the input at all. The time
 * designation must not be trusted in this case.
 *   @param pidOfCallingTask
 * Process ID of calling user task.
 *   @param pwmInputChn
 * The addressed PWM input.
 *   @remark
 * Never call this function directly.
 */
uint32_t pwm_scSmplHdlr_getPwmInTime( uint32_t pidOfCallingTask ATTRIB_UNUSED
                                    , pwm_pwmInChannel_t pwmInputChn
                                    )
{
    /* A safe, "trusted" implementation needs to double check the range of all arguments,
       so that the later execution of the underlaying I/O driver routine will surely not
       fail, which means primarily that it won't go into an assertion in DEBUG
       compilation. For this function, this relates only to the channel designation. */
    uint32_t ti;
    bool isNewResult;
    switch(pwmInputChn)
    {
    case pwm_pwmIChn_PA2_J3_pin3_periodTime:
        ti = pwm_osGetChnInputPeriodTime(&isNewResult, &_hChn2_PWM_IN_PA2_J3_pin3);
        break;

    case pwm_pwmIChn_PA6_J2_pin1_dutyTime:
        ti = pwm_osGetChnInputDutyTime(&isNewResult, &_hChn6_PWM_IN_PA6_J2_pin1);
        break;

    default:
        /* Abort this system call and the calling user task and count this event as an
           error in the process the failing task belongs to. */
        rtos_osSystemCallBadArgument();

        /* rtos_osSystemCallBadArgument() doesn't return. We never get here. */
    }

    if(!isNewResult)
    {
        assert((ti & 0x80000000u) == 0u);
        ti |= 0x80000000u;
    }
    return ti;

} /* pwm_scSmplHdlr_getPwmInTime */





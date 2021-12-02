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
 * Local functions
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

pwm_hEMIOSChannel_t SBSS_OS(pwm_hChn6_PWM_IN_PA6_J2_pin1);
pwm_hEMIOSChannel_t SBSS_OS(pwm_hChn1_PWM_OUT_PA1_J3_pin1);

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

    /* Initialize channel 4 as PWM output. It is connected to LED DS11 at port PA4. (This
       LED needs to be disabled in our standard LED driver, see lbd_ledAndButtonDriver.h.) */
    pwm_hEMIOSChannel_t hChn0_LED_2_DS10
                      , hChn4_LED_4_DS11
                      , hChn7_LED_5_DS5;
    pwm_osInitEMIOSChannelForPWMGeneration( &hChn0_LED_2_DS10
                                          , &hEMIOS0
                                          , /* idxChn */ 0u
                                          , /* prescale */ 4u
                                          , /* isInverted */ true
                                          , /* initialFrequency */ 3.0f
                                          , /* initalDutyCycle */ 0.7f
                                          );
    pwm_osInitEMIOSChannelForPWMGeneration( &hChn4_LED_4_DS11
                                          , &hEMIOS0
                                          , /* idxChn */ 4u
                                          , /* prescale */ 4u
                                          , /* isInverted */ true
                                          , /* initialFrequency */ 5.0f
                                          , /* initalDutyCycle */ 0.1f
                                          );
    pwm_osInitEMIOSChannelForPWMGeneration( &hChn7_LED_5_DS5
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
          , f2d(pwm_osGetChnMinPWMFrequency(&hChn0_LED_2_DS10))
          , f2d(pwm_osGetChnMaxPWMFrequency(&hChn0_LED_2_DS10))
          );


    /* Initialize channel 1 and 6 as PWM output and input, respectively. For this sample,
       the intention is to connect the two MCU pins PA1 and PA6 and to generate a PWM at
       PA1 and to measure it with PA6. On the extension ports, this means a wire between
       J3, pin1, and J2, pin1. */
    pwm_osInitEMIOSChannelForPWMGeneration( &pwm_hChn1_PWM_OUT_PA1_J3_pin1
                                          , &hEMIOS0
                                          , /* idxChn */ 1u
                                          , /* prescale */ 1u
                                          , /* isInverted */ false
                                          , /* initialFrequency */ 500.0f
                                          , /* initalDutyCycle */ 0.5f
                                          );
    pwm_osInitEMIOSChannelForPeriodTimeMeasurement( &pwm_hChn6_PWM_IN_PA6_J2_pin1
                                                  , &hEMIOS0
                                                  , /* idxChn */ 6u
                                                  , /* prescale */ 1u
                                                  , /* glitchFilterStrength */ 4u
                                                  );

    /* Acquire and configure port PA1 as output, which should be connected to PA6, which is
       configured as PWM input. */
    SIUL_idxP = 1u;
    SIUL_P_SSS = 1u;
    gotIt = siu_osAcquirePort(SIUL_idxP);
    assert(gotIt);
    outputCfg.idxPortSource_SSS = SIUL_P_SSS;
    outputCfg.enableOpenDrain_ODE = false;
    siu_osConfigureOutput(SIUL_idxP, &outputCfg);

    /* Acquire and configure port PA6, our PWM input in this sample application. */
    siu_portInCfg_t inputCfg =
    {
        .enableHysteresis_HYS = true,
        .pullUpDownCfg = siu_pullRes_none,
        .idxMultiplexerRegister = 6u,
        .idxInputSource_MUXSELVALUE = 2u,
    };
    SIUL_idxP = 6u;
    gotIt = siu_osAcquirePort(SIUL_idxP);
    assert(gotIt);
    siu_osConfigureInput(SIUL_idxP, &inputCfg);

    printf( "PWM frequency range for output PA1: %.3f .. %.3f Hz\r\n"
          , f2d(pwm_osGetChnMinPWMFrequency(&pwm_hChn1_PWM_OUT_PA1_J3_pin1))
          , f2d(pwm_osGetChnMaxPWMFrequency(&pwm_hChn1_PWM_OUT_PA1_J3_pin1))
          );

} /* End of pwm_osInitIODriver */





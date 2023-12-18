/**
 * @file c2p_canToPWM.c
 * Interface between CAN stack and PWM driver. Particular CAN messages are defined to
 * either control a PWM ouput or to report the measurement results captured at a PWM input.
 * These CAN message are coupled with the PWM I/O driver in this module.
 *   
 * @remark The use of this feature requires that the DBC file PWM.dbc or its contents are
 * element of the set of implemented CAN messages.
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
 *   c2p_mainFunction100ms
 * Local functions
 */

/*
 * Include files
 */

#include "c2p_canToPWM.h"

#include <assert.h>
#include "typ_types.h"
#include "cap_canApi.h"
#include "rtos.h"
#include "bsw_basicSoftware.h"
#include "pwm_pwmIODriver.h"

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
 * Regularly called step function of module. To be invoked from the 100 ms user task.
 */
void c2p_mainFunction100ms(void)
{
#if defined(CAP_MSG_PWM_PWM_IN_1000)
    bool isNewPeriodTime;
    const float tiP = pwm_getChnInputPeriodTime( &isNewPeriodTime
                                               , pwm_pwmIChn_PA2_J3_pin3_periodTime
                                               )
              , f = 1.0f / tiP;
    bool isNewDutyTime;
    const float tiDuty = pwm_getChnInputDutyTime( &isNewDutyTime
                                                , pwm_pwmIChn_PA6_J2_pin1_dutyTime
                                                )
              
              , dutyCycle = tiDuty * f;

    /* Re-scale the values to the particular scaling defined in the DBC file for the CAN
       signals. This is done using the convenience macros offered by the CAN stack. */
/// @todo We need saturation code here
    const unsigned int PA2_J3_pin3_periodTime =
                            CAP_PWM_1000_PA2_J3_pin3_periodTime_DBL_TO_BIN(1000.0f*tiP)
                     , PA6_J2_pin1_dutyTime =
                            CAP_PWM_1000_PA6_J2_pin1_dutyTime_DBL_TO_BIN(1000.0f*tiDuty)
                     , PA2_J3_pin3_frequency =
                            CAP_PWM_1000_PA2_J3_pin3_frequency_DBL_TO_BIN(f)
                     , PA2_PA6_dutyCycle = 
                            dutyCycle <= 1.0f
                            ? CAP_PWM_1000_PA2_PA6_dutyCycle_DBL_TO_BIN(100.0f*dutyCycle)
                            : 0u;
#else
# warning Message catalog does not contain the outbound message PWM_IN. No PWM results \
          are broadcasted
#endif

    /* For reading and updating the global CAN API, we need a critical section with the CAN
       stack task, that packs the messages and sends them out. This is the task, which runs
       the main function of the (only) CAN dispatcher, cde_dispatcherMain(). */
#if defined(CAP_MSG_PWM_PWM_IN_1000) || defined(CAP_MSG_PWM_PWM_OUT_1001)
    uint32_t oldStateTx = rtos_suspendAllTasksByPriority(BSW_PRIO_USER_TASK_10MS);
#endif

#ifdef CAP_MSG_PWM_PWM_IN_1000
    cap_getSignal_PWM_PWM_in_1000(PA2_J3_pin3_isNew)      = isNewPeriodTime;
    cap_getSignal_PWM_PWM_in_1000(PA2_J3_pin3_periodTime) = PA2_J3_pin3_periodTime;
    cap_getSignal_PWM_PWM_in_1000(PA6_J2_pin1_isNew)      = isNewDutyTime;
    cap_getSignal_PWM_PWM_in_1000(PA6_J2_pin1_dutyTime)   = PA6_J2_pin1_dutyTime;
    cap_getSignal_PWM_PWM_in_1000(PA2_J3_pin3_frequency)  = PA2_J3_pin3_frequency;
    cap_getSignal_PWM_PWM_in_1000(PA2_PA6_dutyCycle)      = PA2_PA6_dutyCycle;
#endif
#ifdef CAP_MSG_PWM_PWM_OUT_1001
# define GET_PWM_CAN_CMD(chn)                                                               \
    const bool doCtrl_##chn = !cap_getSignal_PWM_PWM_out_1001(chn##_inhibit);               \
    cap_getSignal_PWM_PWM_out_1001(chn##_inhibit) = true; /* Acknowlegde input */           \
    const uint16_t chn##_frequency = cap_getSignal_PWM_PWM_out_1001(chn##_frequency);       \
    const uint16_t chn##_dutyCycle = cap_getSignal_PWM_PWM_out_1001(chn##_dutyCycle);

    GET_PWM_CAN_CMD(LED_2_DS10)
    GET_PWM_CAN_CMD(LED_4_DS11)
    GET_PWM_CAN_CMD(LED_5_DS5)
    GET_PWM_CAN_CMD(PA1_J3_pin1)
    
#undef GET_PWM_CAN_CMD
#endif
    
#if defined(CAP_MSG_PWM_PWM_IN_1000) || defined(CAP_MSG_PWM_PWM_OUT_1001)
    rtos_resumeAllTasksByPriority(oldStateTx);
#endif

#if defined(CAP_MSG_PWM_PWM_OUT_1001)
# define UPDATE_PWM_CHN(chn)                                                                \
    if(doCtrl_##chn)                                                                        \
    {                                                                                       \
        const float f = CAP_PWM_1001_##chn##_frequency_BIN_TO_DBL(chn##_frequency);         \
        const float dc = CAP_PWM_1001_##chn##_dutyCycle_BIN_TO_DBL(chn##_dutyCycle)/100.0f; \
        pwm_setChnFrequencyAndDutyCycle(pwm_pwmOChn_##chn, f, dc);                          \
    }
    
    UPDATE_PWM_CHN(LED_2_DS10)
    UPDATE_PWM_CHN(LED_4_DS11)
    UPDATE_PWM_CHN(LED_5_DS5)
    UPDATE_PWM_CHN(PA1_J3_pin1)

# undef UPDATE_PWM_CHN
#else
# warning Message catalog does not contain the inbound message PWM_OUT. PWM cannot be \
          controlled via CAN
#endif
} /* c2p_mainFunction100ms */
/*
 * File: pwr_computeEnginePower.c
 *
 * Real-Time Workshop code generated for Simulink model pwr_computeEnginePower.
 *
 * Model version                        : 1.126
 * Real-Time Workshop file version      : 7.3  (R2009a)  15-Jan-2009
 * Real-Time Workshop file generated on : Mon Oct 17 21:28:15 2016
 * TLC version                          : 7.3 (Jan 18 2009)
 * C/C++ source code generated on       : Mon Oct 17 21:28:15 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86/Pentium
 * Code generation objective: Efficiency
 * Validation result: Not run
 */

#include "pwr_computeEnginePower.h"
#include "pwr_computeEnginePower_private.h"

/* Block signals (auto storage) */
pwr_BlockIO_pwr_computeEnginePower_t pwr_pwr_computeEnginePower_B;

/* Output and update for atomic system:
 *   '<Root>/countCheckSumErrors'
 *   '<Root>/countDlcErrors'
 *   '<Root>/countSqcErrors'
 */
void pwr_detectAndCountError(uint8_T rtu_stsTransm_speedOfRotation, uint8_T
  rtu_bitMaskError, uint8_T rtu_stsTransm_torque, uint16_T rtu_noErrBefore,
  pwr_rtB_pwr_detectAndCountError_t *localB)
{
  /* If: '<S2>/ifBothStsAreOkay' incorporates:
   *  ActionPort: '<S6>/Action Port'
   *  S-Function (sfix_bitop): '<S2>/Bitwise Operator'
   *  S-Function (sfix_bitop): '<S2>/Bitwise Operator1'
   *  SubSystem: '<S2>/countCcksumErr'
   */
  if ((rtu_stsTransm_speedOfRotation & rtu_bitMaskError) != 0 ||
      (rtu_stsTransm_torque & rtu_bitMaskError) != 0) {
    /* Sum: '<S6>/Sum' incorporates:
     *  Constant: '<S6>/increment'
     */
    localB->noErrors = (uint16_T)(uint32_T)(rtu_noErrBefore + 1);
  }
}

/* Model step function */
void pwr_computeEnginePower_step(void)
{
  /* local block i/o variables */
  uint16_T rtb_noDlcErrors;
  uint16_T rtb_noCheckSumErrors;
  uint16_T rtb_noSqcErrors;
  uint8_T rtb_stsTransmission;
  uint8_T rtb_stsTransmission_d;

  {
    uint8_T rtb_state;
    boolean_T rtb_pwrIsOutOfRange;
    uint16_T rtb_powerTimesScale_0;
    int32_T tmp;
    int32_T tmp_0;

    /* BusSelector: '<Root>/Bus Selector' incorporates:
     *  Inport: '<Root>/canBus_PT'
     */
    rtb_stsTransmission = cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission;
    rtb_stsTransmission_d = cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission;
    rtb_noDlcErrors =
      cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors;
    rtb_noCheckSumErrors =
      cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors;
    rtb_noSqcErrors =
      cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors;

    /* If: '<S5>/ifBothStsAreOkay' incorporates:
     *  ActionPort: '<S10>/Action Port'
     *  ActionPort: '<S9>/Action Port'
     *  SubSystem: '<S5>/normalOperation'
     *  SubSystem: '<S5>/nullPower'
     */
    if (rtb_stsTransmission == 0 && rtb_stsTransmission_d == 0) {
      /* Product: '<S9>/torqueTimesSOR' incorporates:
       *  Inport: '<Root>/canBus_PT'
       */
      pwr_pwr_computeEnginePower_B.tqTimesSOR = mul_s32_s32_s32_sr25_sat
        (cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation *
         cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque, 858993459);

      /* Logic: '<S11>/Logical Operator3' incorporates:
       *  Constant: '<S11>/constant'
       *  Constant: '<S11>/constant1'
       *  Logic: '<S11>/Logical Operator1'
       *  Logic: '<S11>/Logical Operator2'
       *  RelationalOperator: '<S13>/Compare'
       *  RelationalOperator: '<S14>/Compare'
       *  RelationalOperator: '<S15>/Compare'
       *  RelationalOperator: '<S16>/Compare'
       *  Sum: '<S11>/Add'
       *  Sum: '<S11>/Add1'
       */
      pwr_pwr_computeEnginePower_B.tqTimSORIsSaturated =
        pwr_pwr_computeEnginePower_B.tqTimesSOR > 0 &&
        pwr_pwr_computeEnginePower_B.tqTimesSOR + 1 < 0 ||
        pwr_pwr_computeEnginePower_B.tqTimesSOR < 0 &&
        pwr_pwr_computeEnginePower_B.tqTimesSOR - 1 > 0;

      /* Product: '<S9>/powerTimesScale' incorporates:
       *  Constant: '<S9>/Constant'
       */
      tmp = mul_s32_s32_u32_sr33(pwr_pwr_computeEnginePower_B.tqTimesSOR,
        (uint32_T)54903U);
      tmp_0 = tmp + 15625;
      if (tmp > 0 && tmp_0 <= 0) {
        tmp_0 = MAX_int32_T;
      }

      if (tmp_0 <= 0) {
        rtb_powerTimesScale_0 = 0U;
      } else if (tmp_0 > 65535) {
        rtb_powerTimesScale_0 = MAX_uint16_T;
      } else {
        rtb_powerTimesScale_0 = (uint16_T)tmp_0;
      }

      /* Logic: '<S9>/Logical Operator' incorporates:
       *  Constant: '<S12>/constant'
       *  Logic: '<S12>/Logical Operator1'
       *  RelationalOperator: '<S18>/Compare'
       *  RelationalOperator: '<S19>/Compare'
       *  Sum: '<S12>/Add'
       */
      rtb_pwrIsOutOfRange = pwr_pwr_computeEnginePower_B.tqTimSORIsSaturated ||
        (rtb_powerTimesScale_0 == 0 || (uint16_T)(uint32_T)
         (rtb_powerTimesScale_0 + 1) == 0);

      /* Switch: '<S9>/Switch' incorporates:
       *  Constant: '<S9>/nullPwr'
       */
      if (rtb_pwrIsOutOfRange) {
        rtb_powerTimesScale_0 = 15625U;
      }

      /* Switch: '<S9>/Switch1' incorporates:
       *  Constant: '<S9>/stateOverflow'
       *  Constant: '<S9>/stateValid'
       */
      if (rtb_pwrIsOutOfRange) {
        rtb_state = 2U;
      } else {
        rtb_state = 0U;
      }
    } else {
      /* Constant: '<S10>/Constant' */
      rtb_powerTimesScale_0 = 15625U;

      /* Constant: '<S10>/stateInvalidInput' */
      rtb_state = 1U;
    }

    /* BusCreator: '<Root>/Bus Creator' */
    (*cap_pPT_InfoPowerDisplay_1536).checksum = 0U;
    (*cap_pPT_InfoPowerDisplay_1536).sequenceCounter = 0U;
    (*cap_pPT_InfoPowerDisplay_1536).power = rtb_powerTimesScale_0;
    (*cap_pPT_InfoPowerDisplay_1536).state = rtb_state;

    /* Outputs for atomic SubSystem: '<Root>/countDlcErrors' */
    pwr_detectAndCountError(rtb_stsTransmission, ((uint8_T)16U),
      rtb_stsTransmission_d, rtb_noDlcErrors,
      &pwr_pwr_computeEnginePower_B.countDlcErrors);

    /* end of Outputs for SubSystem: '<Root>/countDlcErrors' */

    /* Outputs for atomic SubSystem: '<Root>/countCheckSumErrors' */
    pwr_detectAndCountError(rtb_stsTransmission, ((uint8_T)4U),
      rtb_stsTransmission_d, rtb_noCheckSumErrors,
      &pwr_pwr_computeEnginePower_B.countCheckSumErrors);

    /* end of Outputs for SubSystem: '<Root>/countCheckSumErrors' */

    /* Outputs for atomic SubSystem: '<Root>/countSqcErrors' */
    pwr_detectAndCountError(rtb_stsTransmission, ((uint8_T)8U),
      rtb_stsTransmission_d, rtb_noSqcErrors,
      &pwr_pwr_computeEnginePower_B.countSqcErrors);

    /* end of Outputs for SubSystem: '<Root>/countSqcErrors' */

    /* BusCreator: '<Root>/Bus Creator1' */
    (*cap_pPT_StatusPowerDisplay_1537).noDlcErrors =
      pwr_pwr_computeEnginePower_B.countDlcErrors.noErrors;
    (*cap_pPT_StatusPowerDisplay_1537).noCheckSumErrors =
      pwr_pwr_computeEnginePower_B.countCheckSumErrors.noErrors;
    (*cap_pPT_StatusPowerDisplay_1537).noSqcErrors =
      pwr_pwr_computeEnginePower_B.countSqcErrors.noErrors;
    (*cap_pPT_StatusPowerDisplay_1537).sequenceCounter = 0U;
    (*cap_pPT_StatusPowerDisplay_1537).checksum = 0U;

    /* If: '<Root>/ifInputIsOkay' incorporates:
     *  ActionPort: '<S1>/Action Port'
     *  SubSystem: '<Root>/checkUserLimits'
     */
    if (rtb_state == 0) {
      /* RelationalOperator: '<S1>/Relational Operator' incorporates:
       *  Inport: '<Root>/canBus_PT'
       */
      pwr_pwr_computeEnginePower_B.belowMinSpeedOfRotation = (uint32_T)
        cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation < (uint32_T)
        (cap_canBus_PT.PT_UserLimits_2032_sts.signals.minSpeedOfRotation << 4);

      /* RelationalOperator: '<S1>/Relational Operator1' incorporates:
       *  Inport: '<Root>/canBus_PT'
       */
      pwr_pwr_computeEnginePower_B.aboveMaxSpeedOfRotation = (uint32_T)
        cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation > (uint32_T)
        (cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxSpeedOfRotation << 4);

      /* Gain: '<S1>/wattTokW' */
      rtb_powerTimesScale_0 = (uint16_T)(mul_s32_s32_u32_sr18
        (rtb_powerTimesScale_0 + -15625, (uint32_T)16777U) + 20);

      /* RelationalOperator: '<S1>/Relational Operator2' incorporates:
       *  Inport: '<Root>/canBus_PT'
       */
      pwr_pwr_computeEnginePower_B.belowMinPower = rtb_powerTimesScale_0 <
        cap_canBus_PT.PT_UserLimits_2032_sts.signals.minPower;

      /* RelationalOperator: '<S1>/Relational Operator3' incorporates:
       *  Inport: '<Root>/canBus_PT'
       */
      pwr_pwr_computeEnginePower_B.aboveMaxPower = rtb_powerTimesScale_0 >
        cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxPower;
    }

    /* BusCreator: '<Root>/Bus Creator2' */
    (*cap_pPT_LimitsPowerDisplay_1538).sequenceCounter = 0U;
    (*cap_pPT_LimitsPowerDisplay_1538).belowMinSpeedOfRotation =
      pwr_pwr_computeEnginePower_B.belowMinSpeedOfRotation;
    (*cap_pPT_LimitsPowerDisplay_1538).aboveMaxSpeedOfRotation =
      pwr_pwr_computeEnginePower_B.aboveMaxSpeedOfRotation;
    (*cap_pPT_LimitsPowerDisplay_1538).belowMinPower =
      pwr_pwr_computeEnginePower_B.belowMinPower;
    (*cap_pPT_LimitsPowerDisplay_1538).aboveMaxPower =
      pwr_pwr_computeEnginePower_B.aboveMaxPower;
  }
}

/* Model initialize function */
void pwr_computeEnginePower_initialize(void)
{
  /* (no initialization code required) */
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */

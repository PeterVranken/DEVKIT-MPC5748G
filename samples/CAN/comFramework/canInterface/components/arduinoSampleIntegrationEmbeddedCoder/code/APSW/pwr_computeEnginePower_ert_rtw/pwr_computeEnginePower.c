/*
 * File: pwr_computeEnginePower.c
 *
 * Real-Time Workshop code generated for Simulink model pwr_computeEnginePower.
 *
 * Model version                        : 1.158
 * Real-Time Workshop file version      : 7.3  (R2009a)  15-Jan-2009
 * Real-Time Workshop file generated on : Mon Oct 17 22:33:42 2016
 * TLC version                          : 7.3 (Jan 18 2009)
 * C/C++ source code generated on       : Mon Oct 17 22:33:42 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objective: Efficiency
 * Validation result: Not run
 */

#include "pwr_computeEnginePower.h"
#include "pwr_computeEnginePower_private.h"

/* Exported block signals */
boolean_T pwr_transmissionErrAry[4];   /* '<S35>/Compare' */

/* Block signals (auto storage) */
pwr_BlockIO_pwr_computeEnginePower_t pwr_pwr_computeEnginePower_B;

/* Block states (auto storage) */
pwr_D_Work_pwr_computeEnginePower_t pwr_pwr_computeEnginePower_DWork;

/* Output and update for atomic system:
 *   '<S2>/countChecksumErrors'
 *   '<S2>/countDlcErrors'
 *   '<S2>/countSqcErrors'
 */
void pwr_detectAndCountError(uint8_T rtu_stsTransm_speedOfRotation, uint8_T
  rtu_bitMaskError, uint8_T rtu_stsTransm_torque, uint16_T rtu_noErrBefore,
  pwr_rtB_pwr_detectAndCountError_t *localB)
{
  /* If: '<S5>/ifBothStsAreOkay' incorporates:
   *  ActionPort: '<S8>/Action Port'
   *  S-Function (sfix_bitop): '<S5>/Bitwise Operator'
   *  S-Function (sfix_bitop): '<S5>/Bitwise Operator1'
   *  SubSystem: '<S5>/countCcksumErr'
   */
  if ((rtu_stsTransm_speedOfRotation & rtu_bitMaskError) != 0 ||
      (rtu_stsTransm_torque & rtu_bitMaskError) != 0) {
    /* Sum: '<S8>/Sum' incorporates:
     *  Constant: '<S8>/increment'
     */
    localB->noErrors = rtu_noErrBefore + 1U;
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
    uint8_T rtb_cntHold_idx;
    uint8_T rtb_cntHold_idx_0;
    uint8_T rtb_cntHold_idx_1;
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

    /* If: '<S3>/ifBothStsAreOkay' incorporates:
     *  ActionPort: '<S11>/Action Port'
     *  ActionPort: '<S12>/Action Port'
     *  SubSystem: '<S3>/normalOperation'
     *  SubSystem: '<S3>/nullPower'
     */
    if (rtb_stsTransmission == 0 && rtb_stsTransmission_d == 0) {
      /* Product: '<S11>/torqueTimesSOR' incorporates:
       *  Inport: '<Root>/canBus_PT'
       */
      pwr_pwr_computeEnginePower_B.tqTimesSOR = mul_s32_s32_s32_sr25_sat
        ((int32_T)cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation *
         (int32_T)cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque,
         858993459L);

      /* Logic: '<S13>/Logical Operator3' incorporates:
       *  Constant: '<S13>/constant'
       *  Constant: '<S13>/constant1'
       *  Logic: '<S13>/Logical Operator1'
       *  Logic: '<S13>/Logical Operator2'
       *  RelationalOperator: '<S15>/Compare'
       *  RelationalOperator: '<S16>/Compare'
       *  RelationalOperator: '<S17>/Compare'
       *  RelationalOperator: '<S18>/Compare'
       *  Sum: '<S13>/Add'
       *  Sum: '<S13>/Add1'
       */
      pwr_pwr_computeEnginePower_B.tqTimSORIsSaturated =
        pwr_pwr_computeEnginePower_B.tqTimesSOR > 0L &&
        pwr_pwr_computeEnginePower_B.tqTimesSOR + 1L < 0L ||
        pwr_pwr_computeEnginePower_B.tqTimesSOR < 0L &&
        pwr_pwr_computeEnginePower_B.tqTimesSOR - 1L > 0L;

      /* Product: '<S11>/powerTimesScale' incorporates:
       *  Constant: '<S11>/Constant'
       */
      tmp = mul_s32_s32_u32_sr33(pwr_pwr_computeEnginePower_B.tqTimesSOR,
        (uint32_T)54903U);
      tmp_0 = tmp + 15625L;
      if (tmp > 0L && tmp_0 <= 0L) {
        tmp_0 = MAX_int32_T;
      }

      if (tmp_0 <= 0L) {
        rtb_powerTimesScale_0 = 0U;
      } else if ((uint32_T)tmp_0 > 65535UL) {
        rtb_powerTimesScale_0 = MAX_uint16_T;
      } else {
        rtb_powerTimesScale_0 = (uint16_T)tmp_0;
      }

      /* Logic: '<S11>/Logical Operator' incorporates:
       *  Constant: '<S14>/constant'
       *  Logic: '<S14>/Logical Operator1'
       *  RelationalOperator: '<S20>/Compare'
       *  RelationalOperator: '<S21>/Compare'
       *  Sum: '<S14>/Add'
       */
      rtb_pwrIsOutOfRange = pwr_pwr_computeEnginePower_B.tqTimSORIsSaturated ||
        (rtb_powerTimesScale_0 == 0U || rtb_powerTimesScale_0 + 1U == 0U);

      /* Switch: '<S11>/Switch' incorporates:
       *  Constant: '<S11>/nullPwr'
       */
      if (rtb_pwrIsOutOfRange) {
        rtb_powerTimesScale_0 = 15625U;
      }

      /* Switch: '<S11>/Switch1' incorporates:
       *  Constant: '<S11>/stateOverflow'
       *  Constant: '<S11>/stateValid'
       */
      if (rtb_pwrIsOutOfRange) {
        rtb_state = 2U;
      } else {
        rtb_state = 0U;
      }
    } else {
      /* Constant: '<S12>/Constant' */
      rtb_powerTimesScale_0 = 15625U;

      /* Constant: '<S12>/stateInvalidInput' */
      rtb_state = 1U;
    }

    /* BusCreator: '<Root>/Bus Creator' */
    (*cap_pPT_InfoPowerDisplay_1536).checksum = 0U;
    (*cap_pPT_InfoPowerDisplay_1536).sequenceCounter = 0U;
    (*cap_pPT_InfoPowerDisplay_1536).power = rtb_powerTimesScale_0;
    (*cap_pPT_InfoPowerDisplay_1536).state = rtb_state;

    /* Outputs for atomic SubSystem: '<S2>/countDlcErrors' */
    pwr_detectAndCountError(rtb_stsTransmission, ((uint8_T)16U),
      rtb_stsTransmission_d, rtb_noDlcErrors,
      &pwr_pwr_computeEnginePower_B.countDlcErrors);

    /* end of Outputs for SubSystem: '<S2>/countDlcErrors' */

    /* Outputs for atomic SubSystem: '<S2>/countChecksumErrors' */
    pwr_detectAndCountError(rtb_stsTransmission, ((uint8_T)4U),
      rtb_stsTransmission_d, rtb_noCheckSumErrors,
      &pwr_pwr_computeEnginePower_B.countChecksumErrors);

    /* end of Outputs for SubSystem: '<S2>/countChecksumErrors' */

    /* Outputs for atomic SubSystem: '<S2>/countSqcErrors' */
    pwr_detectAndCountError(rtb_stsTransmission, ((uint8_T)8U),
      rtb_stsTransmission_d, rtb_noSqcErrors,
      &pwr_pwr_computeEnginePower_B.countSqcErrors);

    /* end of Outputs for SubSystem: '<S2>/countSqcErrors' */

    /* BusCreator: '<Root>/Bus Creator1' */
    (*cap_pPT_StatusPowerDisplay_1537).noDlcErrors =
      pwr_pwr_computeEnginePower_B.countDlcErrors.noErrors;
    (*cap_pPT_StatusPowerDisplay_1537).noCheckSumErrors =
      pwr_pwr_computeEnginePower_B.countChecksumErrors.noErrors;
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
      pwr_pwr_computeEnginePower_B.belowMinSpeedOfRotation = (int32_T)
        cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation < (int32_T)
        cap_canBus_PT.PT_UserLimits_2032_sts.signals.minSpeedOfRotation << 4;

      /* RelationalOperator: '<S1>/Relational Operator1' incorporates:
       *  Inport: '<Root>/canBus_PT'
       */
      pwr_pwr_computeEnginePower_B.aboveMaxSpeedOfRotation = (int32_T)
        cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation > (int32_T)
        cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxSpeedOfRotation << 4;

      /* Gain: '<S1>/wattTokW' */
      rtb_powerTimesScale_0 = (uint16_T)(mul_s32_s32_u32_sr18((int32_T)
        rtb_powerTimesScale_0 + -15625L, (uint32_T)16777U) + 20L);

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

    /* S-Function (sfix_bitop): '<S4>/Bitwise Operator' */
    rtb_state = (uint8_T)(rtb_stsTransmission | rtb_stsTransmission_d);

    /* Switch: '<S29>/ifRestart' incorporates:
     *  Constant: '<S29>/decrement'
     *  Constant: '<S29>/elapsed'
     *  Constant: '<S4>/noTicsHold'
     *  RelationalOperator: '<S30>/Compare'
     *  RelationalOperator: '<S31>/Compare'
     *  RelationalOperator: '<S32>/Compare'
     *  RelationalOperator: '<S33>/Compare'
     *  RelationalOperator: '<S34>/Compare'
     *  S-Function (sfix_bitop): '<S25>/andBitChksumErr'
     *  S-Function (sfix_bitop): '<S26>/andBitDlcErr'
     *  S-Function (sfix_bitop): '<S27>/andBitSqcErr'
     *  S-Function (sfix_bitop): '<S28>/andBitTimeout'
     *  Sum: '<S29>/Sum'
     *  Switch: '<S29>/elseIfCounting'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    if ((rtb_state & 2) != 0) {
      rtb_cntHold_idx = 200U;
    } else if (pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[0] > 0) {
      rtb_cntHold_idx = (uint8_T)
        (pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[0] - 1);
    } else {
      rtb_cntHold_idx = 0U;
    }

    if ((rtb_state & 4) != 0) {
      rtb_cntHold_idx_0 = 200U;
    } else if (pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[1] > 0) {
      rtb_cntHold_idx_0 = (uint8_T)
        (pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[1] - 1);
    } else {
      rtb_cntHold_idx_0 = 0U;
    }

    if ((rtb_state & 8) != 0) {
      rtb_cntHold_idx_1 = 200U;
    } else if (pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[2] > 0) {
      rtb_cntHold_idx_1 = (uint8_T)
        (pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[2] - 1);
    } else {
      rtb_cntHold_idx_1 = 0U;
    }

    if ((rtb_state & 16) != 0) {
      rtb_state = 200U;
    } else if (pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[3] > 0) {
      rtb_state = (uint8_T)(pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[3]
                            - 1);
    } else {
      rtb_state = 0U;
    }

    /* RelationalOperator: '<S35>/Compare' */
    pwr_transmissionErrAry[0] = rtb_cntHold_idx > 0;

    /* Update for UnitDelay: '<S29>/Unit Delay' */
    pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[0] = rtb_cntHold_idx;

    /* RelationalOperator: '<S35>/Compare' */
    pwr_transmissionErrAry[1] = rtb_cntHold_idx_0 > 0;

    /* Update for UnitDelay: '<S29>/Unit Delay' */
    pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[1] = rtb_cntHold_idx_0;

    /* RelationalOperator: '<S35>/Compare' */
    pwr_transmissionErrAry[2] = rtb_cntHold_idx_1 > 0;

    /* Update for UnitDelay: '<S29>/Unit Delay' */
    pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[2] = rtb_cntHold_idx_1;

    /* RelationalOperator: '<S35>/Compare' */
    pwr_transmissionErrAry[3] = rtb_state > 0;

    /* Update for UnitDelay: '<S29>/Unit Delay' */
    pwr_pwr_computeEnginePower_DWork.UnitDelay_DSTATE[3] = rtb_state;
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

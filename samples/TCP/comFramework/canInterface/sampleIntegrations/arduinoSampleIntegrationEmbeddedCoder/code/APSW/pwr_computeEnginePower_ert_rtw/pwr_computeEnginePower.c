/*
 * File: pwr_computeEnginePower.c
 *
 * Code generated for Simulink model 'pwr_computeEnginePower'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Wed Apr  7 15:59:20 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pwr_computeEnginePower.h"
#include "pwr_computeEnginePower_private.h"

/* Exported block signals */
boolean_T pwr_transmissionErrAry[4];   /* '<S35>/Compare' */

/* Block signals (default storage) */
B_pwr_computeEnginePower_T pwr_computeEnginePower_B;

/* Block states (default storage) */
DW_pwr_computeEnginePower_T pwr_computeEnginePower_DW;

/* Real-time model */
RT_MODEL_pwr_computeEnginePow_T pwr_computeEnginePower_M_;
RT_MODEL_pwr_computeEnginePow_T *const pwr_computeEnginePower_M =
    &pwr_computeEnginePower_M_;
void mul_wide_su32(int32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                   *ptrOutBitsLo)
{
    uint32_T outBitsLo;
    uint32_T absIn0;
    uint32_T in0Hi;
    uint32_T in1Lo;
    uint32_T in1Hi;
    uint32_T productHiLo;
    uint32_T productLoHi;
    absIn0 = in0 < 0L ? ~(uint32_T)in0 + 1UL : (uint32_T)in0;
    in0Hi = absIn0 >> 16UL;
    absIn0 &= 65535UL;
    in1Hi = in1 >> 16UL;
    in1Lo = in1 & 65535UL;
    productHiLo = in0Hi * in1Lo;
    productLoHi = absIn0 * in1Hi;
    absIn0 *= in1Lo;
    in1Lo = 0UL;
    outBitsLo = (productLoHi << /*MW:OvBitwiseOk*/ 16UL) + /*MW:OvCarryOk*/
        absIn0;
    if (outBitsLo < absIn0)
    {
        in1Lo = 1UL;
    }

    absIn0 = outBitsLo;
    outBitsLo += /*MW:OvCarryOk*/ productHiLo << /*MW:OvBitwiseOk*/ 16UL;
    if (outBitsLo < absIn0)
    {
        in1Lo++;
    }

    absIn0 = (((productLoHi >> 16UL) + (productHiLo >> 16UL)) + in0Hi * in1Hi) +
        in1Lo;
    if ((in1 != 0UL) && (in0 < 0L))
    {
        absIn0 = ~absIn0;
        outBitsLo = ~outBitsLo;
        outBitsLo++;
        if (outBitsLo == 0UL)
        {
            absIn0++;
        }
    }

    *ptrOutBitsHi = absIn0;
    *ptrOutBitsLo = outBitsLo;
}

int32_T mul_ssu32_hiSR(int32_T a, uint32_T b, uint32_T aShift)
{
    uint32_T u32_chi;
    uint32_T u32_clo;
    mul_wide_su32(a, b, &u32_chi, &u32_clo);
    return (int32_T)u32_chi >> aShift;
}

void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
    uint32_T absIn0;
    uint32_T absIn1;
    uint32_T in0Lo;
    uint32_T in0Hi;
    uint32_T in1Hi;
    uint32_T productHiLo;
    uint32_T productLoHi;
    absIn0 = in0 < 0L ? ~(uint32_T)in0 + 1UL : (uint32_T)in0;
    absIn1 = in1 < 0L ? ~(uint32_T)in1 + 1UL : (uint32_T)in1;
    in0Hi = absIn0 >> 16UL;
    in0Lo = absIn0 & 65535UL;
    in1Hi = absIn1 >> 16UL;
    absIn0 = absIn1 & 65535UL;
    productHiLo = in0Hi * absIn0;
    productLoHi = in0Lo * in1Hi;
    absIn0 *= in0Lo;
    absIn1 = 0UL;
    in0Lo = (productLoHi << /*MW:OvBitwiseOk*/ 16UL) + /*MW:OvCarryOk*/ absIn0;
    if (in0Lo < absIn0)
    {
        absIn1 = 1UL;
    }

    absIn0 = in0Lo;
    in0Lo += /*MW:OvCarryOk*/ productHiLo << /*MW:OvBitwiseOk*/ 16UL;
    if (in0Lo < absIn0)
    {
        absIn1++;
    }

    absIn0 = (((productLoHi >> 16UL) + (productHiLo >> 16UL)) + in0Hi * in1Hi) +
        absIn1;
    if ((in0 != 0L) && ((in1 != 0L) && ((in0 > 0L) != (in1 > 0L))))
    {
        absIn0 = ~absIn0;
        in0Lo = ~in0Lo;
        in0Lo++;
        if (in0Lo == 0UL)
        {
            absIn0++;
        }
    }

    *ptrOutBitsHi = absIn0;
    *ptrOutBitsLo = in0Lo;
}

int32_T mul_s32_loSR_sat(int32_T a, int32_T b, uint32_T aShift)
{
    int32_T result;
    uint32_T u32_chi;
    uint32_T u32_clo;
    mul_wide_s32(a, b, &u32_chi, &u32_clo);
    u32_clo = u32_chi << /*MW:OvBitwiseOk*/ (32UL - aShift) | u32_clo >> aShift;
    u32_chi = (uint32_T)((int32_T)u32_chi >> aShift);
    if (((int32_T)u32_chi > 0L) || ((u32_chi == 0UL) && (u32_clo >= 2147483648UL)))
    {
        result = MAX_int32_T;
    }
    else if (((int32_T)u32_chi < -1L) || (((int32_T)u32_chi == -1L) && (u32_clo <
               2147483648UL)))
    {
        result = MIN_int32_T;
    }
    else
    {
        result = (int32_T)u32_clo;
    }

    return result;
}

/*
 * Output and update for atomic system:
 *    '<S2>/countChecksumErrors'
 *    '<S2>/countDlcErrors'
 *    '<S2>/countSqcErrors'
 */
void pwr_detectAndCountError(uint8_T rtu_stsTransm_speedOfRotation, uint8_T
    rtu_stsTransm_torque, uint8_T rtu_bitMaskError, uint16_T rtu_noErrBefore,
    uint16_T *rty_noErr)
{
    /* If: '<S5>/ifBothStsAreOkay' incorporates:
     *  S-Function (sfix_bitop): '<S5>/Bitwise Operator'
     *  S-Function (sfix_bitop): '<S5>/Bitwise Operator1'
     */
    if (((rtu_stsTransm_speedOfRotation & rtu_bitMaskError) != 0) ||
            ((rtu_stsTransm_torque & rtu_bitMaskError) != 0))
    {
        /* Outputs for IfAction SubSystem: '<S5>/countCcksumErr' incorporates:
         *  ActionPort: '<S8>/Action Port'
         */
        /* Sum: '<S8>/Sum' incorporates:
         *  Constant: '<S8>/increment'
         */
        *rty_noErr = rtu_noErrBefore + 1U;

        /* End of Outputs for SubSystem: '<S5>/countCcksumErr' */
    }

    /* End of If: '<S5>/ifBothStsAreOkay' */
}

/* Model step function */
void pwr_computeEnginePower_step(void)
{
    uint8_T rtb_Merge1;
    uint8_T rtb_BitwiseOperator;
    uint16_T rtb_Merge;
    int32_T q0;

    /* If: '<S3>/ifBothStsAreOkay' incorporates:
     *  Inport: '<Root>/canBus_PT'
     */
    if ((cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission == 0) &&
            (cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission == 0))
    {
        /* Outputs for IfAction SubSystem: '<S3>/normalOperation' incorporates:
         *  ActionPort: '<S11>/Action Port'
         */
        /* Product: '<S11>/torqueTimesSOR' */
        pwr_computeEnginePower_B.tqTimesSOR = mul_s32_loSR_sat((int32_T)
            cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation *
            cap_canBus_PT.PT_StateEcu02_1040_sts.signals.torque, 858993459L,
            25UL);

        /* Logic: '<S13>/Logical Operator3' incorporates:
         *  Constant: '<S13>/constant'
         *  Constant: '<S13>/constant1'
         *  Constant: '<S15>/Constant'
         *  Constant: '<S16>/Constant'
         *  Constant: '<S17>/Constant'
         *  Constant: '<S18>/Constant'
         *  Logic: '<S13>/Logical Operator1'
         *  Logic: '<S13>/Logical Operator2'
         *  RelationalOperator: '<S15>/Compare'
         *  RelationalOperator: '<S16>/Compare'
         *  RelationalOperator: '<S17>/Compare'
         *  RelationalOperator: '<S18>/Compare'
         *  Sum: '<S13>/Add'
         *  Sum: '<S13>/Add1'
         */
        pwr_computeEnginePower_B.tqTimSORIsSaturated =
            (((pwr_computeEnginePower_B.tqTimesSOR > 0L) &&
              (pwr_computeEnginePower_B.tqTimesSOR + 1L < 0L)) ||
             ((pwr_computeEnginePower_B.tqTimesSOR < 0L) &&
              (pwr_computeEnginePower_B.tqTimesSOR - 1L > 0L)));

        /* Product: '<S11>/powerTimesScale' */
        q0 = mul_ssu32_hiSR(pwr_computeEnginePower_B.tqTimesSOR, 54903UL, 1UL);
        if (q0 > 2147468022L)
        {
            q0 = MAX_int32_T;
        }
        else
        {
            q0 += 15625L;
        }

        if (q0 < 0L)
        {
            q0 = 0L;
        }
        else
        {
            if ((uint32_T)q0 > 65535UL)
            {
                q0 = 65535L;
            }
        }

        /* Switch: '<S11>/Switch' incorporates:
         *  Constant: '<S11>/nullPwr'
         *  Constant: '<S11>/stateOverflow'
         *  Constant: '<S11>/stateValid'
         *  Constant: '<S14>/constant'
         *  Constant: '<S20>/Constant'
         *  Constant: '<S21>/Constant'
         *  Logic: '<S11>/Logical Operator'
         *  Logic: '<S14>/Logical Operator1'
         *  Product: '<S11>/powerTimesScale'
         *  RelationalOperator: '<S20>/Compare'
         *  RelationalOperator: '<S21>/Compare'
         *  Sum: '<S14>/Add'
         *  Switch: '<S11>/Switch1'
         */
        if (pwr_computeEnginePower_B.tqTimSORIsSaturated || (((uint16_T)q0 == 0U)
             || ((uint16_T)q0 + 1U == 0U)))
        {
            rtb_Merge = 15625U;
            rtb_Merge1 = 2U;
        }
        else
        {
            rtb_Merge = (uint16_T)q0;
            rtb_Merge1 = 0U;
        }

        /* End of Switch: '<S11>/Switch' */
        /* End of Outputs for SubSystem: '<S3>/normalOperation' */
    }
    else
    {
        /* Outputs for IfAction SubSystem: '<S3>/nullPower' incorporates:
         *  ActionPort: '<S12>/Action Port'
         */
        /* SignalConversion generated from: '<S12>/power' incorporates:
         *  Constant: '<S12>/Constant'
         */
        rtb_Merge = 15625U;

        /* SignalConversion generated from: '<S12>/state' incorporates:
         *  Constant: '<S12>/stateInvalidInput'
         */
        rtb_Merge1 = 1U;

        /* End of Outputs for SubSystem: '<S3>/nullPower' */
    }

    /* End of If: '<S3>/ifBothStsAreOkay' */

    /* Outputs for Atomic SubSystem: '<S2>/countDlcErrors' */
    /* Inport: '<Root>/canBus_PT' incorporates:
     *  Constant: '<S2>/bitCheckSumErr'
     *  Constant: '<S2>/bitDlcErr'
     *  Constant: '<S2>/bitSqcErr'
     */
    pwr_detectAndCountError(cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission,
                            cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission,
                            16,
                            cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noDlcErrors,
                            &pwr_computeEnginePower_B.noDlcErrors);

    /* End of Outputs for SubSystem: '<S2>/countDlcErrors' */

    /* Outputs for Atomic SubSystem: '<S2>/countChecksumErrors' */
    pwr_detectAndCountError(cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission,
                            cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission,
                            4,
                            cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noCheckSumErrors,
                            &pwr_computeEnginePower_B.noChecksumErrors);

    /* End of Outputs for SubSystem: '<S2>/countChecksumErrors' */

    /* Outputs for Atomic SubSystem: '<S2>/countSqcErrors' */
    pwr_detectAndCountError(cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission,
                            cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission,
                            8,
                            cap_canBus_PT.PT_StatusPowerDisplay_1537_sts.signals.noSqcErrors,
                            &pwr_computeEnginePower_B.noSqcErrors);

    /* End of Outputs for SubSystem: '<S2>/countSqcErrors' */

    /* S-Function (sfix_bitop): '<S4>/Bitwise Operator' incorporates:
     *  Inport: '<Root>/canBus_PT'
     */
    rtb_BitwiseOperator = (uint8_T)
        (cap_canBus_PT.PT_StateEcu01_1024_sts.stsTransmission |
         cap_canBus_PT.PT_StateEcu02_1040_sts.stsTransmission);

    /* Switch: '<S29>/ifRestart' incorporates:
     *  Constant: '<S29>/elapsed'
     *  Constant: '<S33>/Constant'
     *  Constant: '<S34>/Constant'
     *  Constant: '<S4>/noTicsHold'
     *  RelationalOperator: '<S33>/Compare'
     *  RelationalOperator: '<S34>/Compare'
     *  S-Function (sfix_bitop): '<S28>/andBitTimeout'
     *  Switch: '<S29>/elseIfCounting'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    if ((rtb_BitwiseOperator & 2U) != 0U)
    {
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[0] = 200U;
    }
    else if (pwr_computeEnginePower_DW.UnitDelay_DSTATE[0] > 0)
    {
        /* Switch: '<S29>/elseIfCounting' incorporates:
         *  Constant: '<S29>/decrement'
         *  Sum: '<S29>/Sum'
         *  UnitDelay: '<S29>/Unit Delay'
         */
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[0]--;
    }
    else
    {
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[0] = 0U;
    }

    /* RelationalOperator: '<S35>/Compare' incorporates:
     *  Constant: '<S35>/Constant'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    pwr_transmissionErrAry[0] = (pwr_computeEnginePower_DW.UnitDelay_DSTATE[0] >
        0);

    /* Switch: '<S29>/ifRestart' incorporates:
     *  Constant: '<S29>/elapsed'
     *  Constant: '<S30>/Constant'
     *  Constant: '<S34>/Constant'
     *  Constant: '<S4>/noTicsHold'
     *  RelationalOperator: '<S30>/Compare'
     *  RelationalOperator: '<S34>/Compare'
     *  S-Function (sfix_bitop): '<S25>/andBitChksumErr'
     *  Switch: '<S29>/elseIfCounting'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    if ((rtb_BitwiseOperator & 4U) != 0U)
    {
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[1] = 200U;
    }
    else if (pwr_computeEnginePower_DW.UnitDelay_DSTATE[1] > 0)
    {
        /* Switch: '<S29>/elseIfCounting' incorporates:
         *  Constant: '<S29>/decrement'
         *  Sum: '<S29>/Sum'
         *  UnitDelay: '<S29>/Unit Delay'
         */
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[1]--;
    }
    else
    {
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[1] = 0U;
    }

    /* RelationalOperator: '<S35>/Compare' incorporates:
     *  Constant: '<S35>/Constant'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    pwr_transmissionErrAry[1] = (pwr_computeEnginePower_DW.UnitDelay_DSTATE[1] >
        0);

    /* Switch: '<S29>/ifRestart' incorporates:
     *  Constant: '<S29>/elapsed'
     *  Constant: '<S32>/Constant'
     *  Constant: '<S34>/Constant'
     *  Constant: '<S4>/noTicsHold'
     *  RelationalOperator: '<S32>/Compare'
     *  RelationalOperator: '<S34>/Compare'
     *  S-Function (sfix_bitop): '<S27>/andBitSqcErr'
     *  Switch: '<S29>/elseIfCounting'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    if ((rtb_BitwiseOperator & 8U) != 0U)
    {
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[2] = 200U;
    }
    else if (pwr_computeEnginePower_DW.UnitDelay_DSTATE[2] > 0)
    {
        /* Switch: '<S29>/elseIfCounting' incorporates:
         *  Constant: '<S29>/decrement'
         *  Sum: '<S29>/Sum'
         *  UnitDelay: '<S29>/Unit Delay'
         */
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[2]--;
    }
    else
    {
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[2] = 0U;
    }

    /* RelationalOperator: '<S35>/Compare' incorporates:
     *  Constant: '<S35>/Constant'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    pwr_transmissionErrAry[2] = (pwr_computeEnginePower_DW.UnitDelay_DSTATE[2] >
        0);

    /* Switch: '<S29>/ifRestart' incorporates:
     *  Constant: '<S29>/elapsed'
     *  Constant: '<S31>/Constant'
     *  Constant: '<S34>/Constant'
     *  Constant: '<S4>/noTicsHold'
     *  RelationalOperator: '<S31>/Compare'
     *  RelationalOperator: '<S34>/Compare'
     *  S-Function (sfix_bitop): '<S26>/andBitDlcErr'
     *  Switch: '<S29>/elseIfCounting'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    if ((rtb_BitwiseOperator & 16U) != 0U)
    {
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[3] = 200U;
    }
    else if (pwr_computeEnginePower_DW.UnitDelay_DSTATE[3] > 0)
    {
        /* Switch: '<S29>/elseIfCounting' incorporates:
         *  Constant: '<S29>/decrement'
         *  Sum: '<S29>/Sum'
         *  UnitDelay: '<S29>/Unit Delay'
         */
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[3]--;
    }
    else
    {
        pwr_computeEnginePower_DW.UnitDelay_DSTATE[3] = 0U;
    }

    /* RelationalOperator: '<S35>/Compare' incorporates:
     *  Constant: '<S35>/Constant'
     *  UnitDelay: '<S29>/Unit Delay'
     */
    pwr_transmissionErrAry[3] = (pwr_computeEnginePower_DW.UnitDelay_DSTATE[3] >
        0);

    /* BusCreator: '<Root>/Bus Creator1' */
    cap_pPT_StatusPowerDisplay_1537->noDlcErrors =
        pwr_computeEnginePower_B.noDlcErrors;
    cap_pPT_StatusPowerDisplay_1537->noCheckSumErrors =
        pwr_computeEnginePower_B.noChecksumErrors;
    cap_pPT_StatusPowerDisplay_1537->noSqcErrors =
        pwr_computeEnginePower_B.noSqcErrors;
    cap_pPT_StatusPowerDisplay_1537->sequenceCounter = 0U;
    cap_pPT_StatusPowerDisplay_1537->checksum = 0U;

    /* BusCreator: '<Root>/Bus Creator' */
    cap_pPT_InfoPowerDisplay_1536->checksum = 0U;
    cap_pPT_InfoPowerDisplay_1536->sequenceCounter = 0U;
    cap_pPT_InfoPowerDisplay_1536->power = rtb_Merge;
    cap_pPT_InfoPowerDisplay_1536->state = rtb_Merge1;

    /* If: '<Root>/ifInputIsOkay' */
    if (rtb_Merge1 == 0)
    {
        /* Outputs for IfAction SubSystem: '<Root>/checkUserLimits' incorporates:
         *  ActionPort: '<S1>/Action Port'
         */
        /* RelationalOperator: '<S1>/Relational Operator' incorporates:
         *  Inport: '<Root>/canBus_PT'
         */
        cap_pPT_LimitsPowerDisplay_1538->belowMinSpeedOfRotation =
            (cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation <
             (int32_T)((uint32_T)
                       cap_canBus_PT.PT_UserLimits_2032_sts.signals.minSpeedOfRotation
                       << 4));

        /* RelationalOperator: '<S1>/Relational Operator1' incorporates:
         *  Inport: '<Root>/canBus_PT'
         */
        cap_pPT_LimitsPowerDisplay_1538->aboveMaxSpeedOfRotation =
            (cap_canBus_PT.PT_StateEcu01_1024_sts.signals.speedOfRotation >
             (int32_T)((uint32_T)
                       cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxSpeedOfRotation
                       << 4));

        /* Gain: '<S1>/wattTokW' */
        rtb_Merge = (uint16_T)((int16_T)(((rtb_Merge + -15625L) * 16777L) >> 18)
                               + 20);

        /* RelationalOperator: '<S1>/Relational Operator2' incorporates:
         *  Inport: '<Root>/canBus_PT'
         */
        cap_pPT_LimitsPowerDisplay_1538->belowMinPower = (rtb_Merge <
            cap_canBus_PT.PT_UserLimits_2032_sts.signals.minPower);

        /* RelationalOperator: '<S1>/Relational Operator3' incorporates:
         *  Inport: '<Root>/canBus_PT'
         */
        cap_pPT_LimitsPowerDisplay_1538->aboveMaxPower = (rtb_Merge >
            cap_canBus_PT.PT_UserLimits_2032_sts.signals.maxPower);

        /* End of Outputs for SubSystem: '<Root>/checkUserLimits' */
    }

    /* End of If: '<Root>/ifInputIsOkay' */

    /* BusCreator: '<Root>/Bus Creator2' */
    cap_pPT_LimitsPowerDisplay_1538->sequenceCounter = 0U;
}

/* Model initialize function */
void pwr_computeEnginePower_initialize(void)
{
    /* (no initialization code required) */
}

/* Model terminate function */
void pwr_computeEnginePower_terminate(void)
{
    /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

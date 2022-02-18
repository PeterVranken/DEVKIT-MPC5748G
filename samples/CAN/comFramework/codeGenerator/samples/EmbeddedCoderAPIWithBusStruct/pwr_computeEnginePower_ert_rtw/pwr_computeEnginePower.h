/*
 * File: pwr_computeEnginePower.h
 *
 * Code generated for Simulink model 'pwr_computeEnginePower'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Fri Apr  9 10:31:36 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_pwr_computeEnginePower_h_
#define RTW_HEADER_pwr_computeEnginePower_h_
#ifndef pwr_computeEnginePower_COMMON_INCLUDES_
# define pwr_computeEnginePower_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                             /* pwr_computeEnginePower_COMMON_INCLUDES_ */

#include "pwr_computeEnginePower_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct
{
    int32_T tqTimesSOR;                /* '<S11>/torqueTimesSOR' */
    uint16_T noSqcErrors;              /* '<S10>/Sum' */
    uint16_T noDlcErrors;              /* '<S9>/Sum' */
    uint16_T noChecksumErrors;         /* '<S8>/Sum' */
    boolean_T tqTimSORIsSaturated;     /* '<S13>/Logical Operator3' */
}
B_pwr_computeEnginePower_T;

/* Block states (default storage) for system '<Root>' */
typedef struct
{
    uint8_T UnitDelay_DSTATE[4];       /* '<S29>/Unit Delay' */
}
DW_pwr_computeEnginePower_T;

/* Real-time Model Data Structure */
struct tag_RTM_pwr_computeEnginePowe_T
{
    const char_T *errorStatus;
};

/* Block signals (default storage) */
extern B_pwr_computeEnginePower_T pwr_computeEnginePower_B;

/* Block states (default storage) */
extern DW_pwr_computeEnginePower_T pwr_computeEnginePower_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern boolean_T pwr_transmissionErrAry[4];/* '<S35>/Compare' */

/* Model entry point functions */
extern void pwr_computeEnginePower_initialize(void);
extern void pwr_computeEnginePower_step(void);
extern void pwr_computeEnginePower_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pwr_computeEnginePow_T *const pwr_computeEnginePower_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S19>/FixPt Data Type Propagation' : Unused code path elimination
 * Block '<S22>/FixPt Data Type Propagation' : Unused code path elimination
 * Block '<S23>/FixPt Data Type Propagation' : Unused code path elimination
 * Block '<S24>/FixPt Data Type Propagation' : Unused code path elimination
 * Block '<S19>/FixPt Gateway Out' : Eliminate redundant data type conversion
 * Block '<S22>/FixPt Gateway Out' : Eliminate redundant data type conversion
 * Block '<S23>/FixPt Gateway Out' : Eliminate redundant data type conversion
 * Block '<S24>/FixPt Gateway Out' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pwr_computeEnginePower'
 * '<S1>'   : 'pwr_computeEnginePower/checkUserLimits'
 * '<S2>'   : 'pwr_computeEnginePower/cntTransmissionErrs'
 * '<S3>'   : 'pwr_computeEnginePower/powerComputation'
 * '<S4>'   : 'pwr_computeEnginePower/transmissionErrs'
 * '<S5>'   : 'pwr_computeEnginePower/cntTransmissionErrs/countChecksumErrors'
 * '<S6>'   : 'pwr_computeEnginePower/cntTransmissionErrs/countDlcErrors'
 * '<S7>'   : 'pwr_computeEnginePower/cntTransmissionErrs/countSqcErrors'
 * '<S8>'   : 'pwr_computeEnginePower/cntTransmissionErrs/countChecksumErrors/countCcksumErr'
 * '<S9>'   : 'pwr_computeEnginePower/cntTransmissionErrs/countDlcErrors/countCcksumErr'
 * '<S10>'  : 'pwr_computeEnginePower/cntTransmissionErrs/countSqcErrors/countCcksumErr'
 * '<S11>'  : 'pwr_computeEnginePower/powerComputation/normalOperation'
 * '<S12>'  : 'pwr_computeEnginePower/powerComputation/nullPower'
 * '<S13>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated'
 * '<S14>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1'
 * '<S15>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero'
 * '<S16>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero1'
 * '<S17>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero2'
 * '<S18>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero3'
 * '<S19>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/makeRawInteger'
 * '<S20>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1/Compare To Zero'
 * '<S21>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1/Compare To Zero3'
 * '<S22>'  : 'pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1/makeRawInteger'
 * '<S23>'  : 'pwr_computeEnginePower/transmissionErrs/Data Type Scaling Strip'
 * '<S24>'  : 'pwr_computeEnginePower/transmissionErrs/Data Type Scaling Strip1'
 * '<S25>'  : 'pwr_computeEnginePower/transmissionErrs/filterBitChksumErr'
 * '<S26>'  : 'pwr_computeEnginePower/transmissionErrs/filterBitDlcErr'
 * '<S27>'  : 'pwr_computeEnginePower/transmissionErrs/filterBitSqcErr'
 * '<S28>'  : 'pwr_computeEnginePower/transmissionErrs/filterBitTimeout'
 * '<S29>'  : 'pwr_computeEnginePower/transmissionErrs/hold'
 * '<S30>'  : 'pwr_computeEnginePower/transmissionErrs/filterBitChksumErr/Compare To Zero'
 * '<S31>'  : 'pwr_computeEnginePower/transmissionErrs/filterBitDlcErr/Compare To Zero'
 * '<S32>'  : 'pwr_computeEnginePower/transmissionErrs/filterBitSqcErr/Compare To Zero'
 * '<S33>'  : 'pwr_computeEnginePower/transmissionErrs/filterBitTimeout/Compare To Zero'
 * '<S34>'  : 'pwr_computeEnginePower/transmissionErrs/hold/Compare To Zero'
 * '<S35>'  : 'pwr_computeEnginePower/transmissionErrs/hold/Compare To Zero1'
 */
#endif                                /* RTW_HEADER_pwr_computeEnginePower_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

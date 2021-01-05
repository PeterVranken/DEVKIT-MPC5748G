/*
 * File: pwr_computeEnginePower.h
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

#ifndef RTW_HEADER_pwr_computeEnginePower_h_
#define RTW_HEADER_pwr_computeEnginePower_h_
#ifndef pwr_computeEnginePower_COMMON_INCLUDES_
# define pwr_computeEnginePower_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_shared_utils.h"
#endif                                 /* pwr_computeEnginePower_COMMON_INCLUDES_ */

#include "pwr_computeEnginePower_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((void*) 0)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((void) 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

#define pwr_computeEnginePower_M       pwr_pwr_computeEnginePower_M

/* Block signals for system '<S2>/countChecksumErrors' */
typedef struct {
  uint16_T noErrors;                   /* '<S8>/Sum' */
} pwr_rtB_pwr_detectAndCountError_t;

/* Block signals (auto storage) */
typedef struct {
  int32_T tqTimesSOR;                  /* '<S11>/torqueTimesSOR' */
  boolean_T tqTimSORIsSaturated;       /* '<S13>/Logical Operator3' */
  boolean_T belowMinSpeedOfRotation;   /* '<S1>/Relational Operator' */
  boolean_T aboveMaxSpeedOfRotation;   /* '<S1>/Relational Operator1' */
  boolean_T belowMinPower;             /* '<S1>/Relational Operator2' */
  boolean_T aboveMaxPower;             /* '<S1>/Relational Operator3' */
  pwr_rtB_pwr_detectAndCountError_t countSqcErrors;/* '<S2>/countSqcErrors' */
  pwr_rtB_pwr_detectAndCountError_t countDlcErrors;/* '<S2>/countDlcErrors' */
  pwr_rtB_pwr_detectAndCountError_t countChecksumErrors;/* '<S2>/countChecksumErrors' */
} pwr_BlockIO_pwr_computeEnginePower_t;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T UnitDelay_DSTATE[4];         /* '<S29>/Unit Delay' */
} pwr_D_Work_pwr_computeEnginePower_t;

/* Block signals (auto storage) */
extern pwr_BlockIO_pwr_computeEnginePower_t pwr_pwr_computeEnginePower_B;

/* Block states (auto storage) */
extern pwr_D_Work_pwr_computeEnginePower_t pwr_pwr_computeEnginePower_DWork;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  RTW declares the memory for these signals
 * and exports their symbols.
 *
 */
extern boolean_T pwr_transmissionErrAry[4];/* '<S35>/Compare' */

/* Model entry point functions */
extern void pwr_computeEnginePower_initialize(void);
extern void pwr_computeEnginePower_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S19>/FixPt Data Type Propagation' : Eliminated upon user request
 * Block '<S19>/FixPt Gateway Out' : Eliminate redundant data type conversion
 * Block '<S22>/FixPt Data Type Propagation' : Eliminated upon user request
 * Block '<S22>/FixPt Gateway Out' : Eliminate redundant data type conversion
 * Block '<S23>/FixPt Data Type Propagation' : Eliminated upon user request
 * Block '<S23>/FixPt Gateway Out' : Eliminate redundant data type conversion
 * Block '<S24>/FixPt Data Type Propagation' : Eliminated upon user request
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
 * '<Root>' : pwr_computeEnginePower
 * '<S1>'   : pwr_computeEnginePower/checkUserLimits
 * '<S2>'   : pwr_computeEnginePower/cntTransmissionErrs
 * '<S3>'   : pwr_computeEnginePower/powerComputation
 * '<S4>'   : pwr_computeEnginePower/transmissionErrs
 * '<S5>'   : pwr_computeEnginePower/cntTransmissionErrs/countChecksumErrors
 * '<S6>'   : pwr_computeEnginePower/cntTransmissionErrs/countDlcErrors
 * '<S7>'   : pwr_computeEnginePower/cntTransmissionErrs/countSqcErrors
 * '<S8>'   : pwr_computeEnginePower/cntTransmissionErrs/countChecksumErrors/countCcksumErr
 * '<S9>'   : pwr_computeEnginePower/cntTransmissionErrs/countDlcErrors/countCcksumErr
 * '<S10>'  : pwr_computeEnginePower/cntTransmissionErrs/countSqcErrors/countCcksumErr
 * '<S11>'  : pwr_computeEnginePower/powerComputation/normalOperation
 * '<S12>'  : pwr_computeEnginePower/powerComputation/nullPower
 * '<S13>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated
 * '<S14>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1
 * '<S15>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero
 * '<S16>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero1
 * '<S17>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero2
 * '<S18>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero3
 * '<S19>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/makeRawInteger
 * '<S20>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1/Compare To Zero
 * '<S21>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1/Compare To Zero3
 * '<S22>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1/makeRawInteger
 * '<S23>'  : pwr_computeEnginePower/transmissionErrs/Data Type Scaling Strip
 * '<S24>'  : pwr_computeEnginePower/transmissionErrs/Data Type Scaling Strip1
 * '<S25>'  : pwr_computeEnginePower/transmissionErrs/filterBitChksumErr
 * '<S26>'  : pwr_computeEnginePower/transmissionErrs/filterBitDlcErr
 * '<S27>'  : pwr_computeEnginePower/transmissionErrs/filterBitSqcErr
 * '<S28>'  : pwr_computeEnginePower/transmissionErrs/filterBitTimeout
 * '<S29>'  : pwr_computeEnginePower/transmissionErrs/hold
 * '<S30>'  : pwr_computeEnginePower/transmissionErrs/filterBitChksumErr/Compare To Zero
 * '<S31>'  : pwr_computeEnginePower/transmissionErrs/filterBitDlcErr/Compare To Zero
 * '<S32>'  : pwr_computeEnginePower/transmissionErrs/filterBitSqcErr/Compare To Zero
 * '<S33>'  : pwr_computeEnginePower/transmissionErrs/filterBitTimeout/Compare To Zero
 * '<S34>'  : pwr_computeEnginePower/transmissionErrs/hold/Compare To Zero
 * '<S35>'  : pwr_computeEnginePower/transmissionErrs/hold/Compare To Zero1
 */
#endif                                 /* RTW_HEADER_pwr_computeEnginePower_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */

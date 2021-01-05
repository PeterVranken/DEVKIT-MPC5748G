/*
 * File: pwr_computeEnginePower.h
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

/* Block signals for system '<Root>/countCheckSumErrors' */
typedef struct {
  uint16_T noErrors;                   /* '<S6>/Sum' */
} pwr_rtB_pwr_detectAndCountError_t;

/* Block signals (auto storage) */
typedef struct {
  int32_T tqTimesSOR;                  /* '<S9>/torqueTimesSOR' */
  boolean_T tqTimSORIsSaturated;       /* '<S11>/Logical Operator3' */
  boolean_T belowMinSpeedOfRotation;   /* '<S1>/Relational Operator' */
  boolean_T aboveMaxSpeedOfRotation;   /* '<S1>/Relational Operator1' */
  boolean_T belowMinPower;             /* '<S1>/Relational Operator2' */
  boolean_T aboveMaxPower;             /* '<S1>/Relational Operator3' */
  pwr_rtB_pwr_detectAndCountError_t countSqcErrors;/* '<Root>/countSqcErrors' */
  pwr_rtB_pwr_detectAndCountError_t countDlcErrors;/* '<Root>/countDlcErrors' */
  pwr_rtB_pwr_detectAndCountError_t countCheckSumErrors;/* '<Root>/countCheckSumErrors' */
} pwr_BlockIO_pwr_computeEnginePower_t;

/* Block signals (auto storage) */
extern pwr_BlockIO_pwr_computeEnginePower_t pwr_pwr_computeEnginePower_B;

/* Model entry point functions */
extern void pwr_computeEnginePower_initialize(void);
extern void pwr_computeEnginePower_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S17>/FixPt Data Type Propagation' : Eliminated upon user request
 * Block '<S17>/FixPt Gateway Out' : Eliminate redundant data type conversion
 * Block '<S20>/FixPt Data Type Propagation' : Eliminated upon user request
 * Block '<S20>/FixPt Gateway Out' : Eliminate redundant data type conversion
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
 * '<S2>'   : pwr_computeEnginePower/countCheckSumErrors
 * '<S3>'   : pwr_computeEnginePower/countDlcErrors
 * '<S4>'   : pwr_computeEnginePower/countSqcErrors
 * '<S5>'   : pwr_computeEnginePower/powerComputation
 * '<S6>'   : pwr_computeEnginePower/countCheckSumErrors/countCcksumErr
 * '<S7>'   : pwr_computeEnginePower/countDlcErrors/countCcksumErr
 * '<S8>'   : pwr_computeEnginePower/countSqcErrors/countCcksumErr
 * '<S9>'   : pwr_computeEnginePower/powerComputation/normalOperation
 * '<S10>'  : pwr_computeEnginePower/powerComputation/nullPower
 * '<S11>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated
 * '<S12>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1
 * '<S13>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero
 * '<S14>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero1
 * '<S15>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero2
 * '<S16>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/Compare To Zero3
 * '<S17>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated/makeRawInteger
 * '<S18>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1/Compare To Zero
 * '<S19>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1/Compare To Zero3
 * '<S20>'  : pwr_computeEnginePower/powerComputation/normalOperation/isSaturated1/makeRawInteger
 */
#endif                                 /* RTW_HEADER_pwr_computeEnginePower_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */

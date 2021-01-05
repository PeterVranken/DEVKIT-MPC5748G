/*
 * File: pwr_computeEnginePower_private.h
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

#ifndef RTW_HEADER_pwr_computeEnginePower_private_h_
#define RTW_HEADER_pwr_computeEnginePower_private_h_
#include "rtwtypes.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error "Code was generated for compiler with different sized uchar/char. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compiler's limits.h header file. Alternatively, you can select 'None' for Emulation Hardware and select the 'Enable portable word sizes' option for ERT based targets, which will disable the preprocessor word size checks."
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error "Code was generated for compiler with different sized ushort/short. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file. Alternatively, you can select 'None' for Emulation Hardware and select the 'Enable portable word sizes' option for ERT based targets, this will disable the preprocessor word size checks."
#endif

#if ( UINT_MAX != (0xFFFFU) ) || ( INT_MAX != (0x7FFF) )
#error "Code was generated for compiler with different sized uint/int. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file. Alternatively, you can select 'None' for Emulation Hardware and select the 'Enable portable word sizes' option for ERT based targets, this will disable the preprocessor word size checks."
#endif

#if ( ULONG_MAX != (0xFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFL) )
#error "Code was generated for compiler with different sized ulong/long. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file. Alternatively, you can select 'None' for Emulation Hardware and select the 'Enable portable word sizes' option for ERT based targets, this will disable the preprocessor word size checks."
#endif

#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I16L32N08F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I16L32N08F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

/* Imported (extern) block signals */
extern cap_canBus_PT_t cap_canBus_PT;  /* '<Root>/canBus_PT' */

/* Imported (extern) pointer block signals */
extern cap_PT_InfoPowerDisplay_1536_t *cap_pPT_InfoPowerDisplay_1536;/* '<Root>/Bus Creator' */
extern cap_PT_StatusPowerDisplay_1537_t *cap_pPT_StatusPowerDisplay_1537;/* '<Root>/Bus Creator1' */
extern cap_PT_LimitsPowerDisplay_1538_t *cap_pPT_LimitsPowerDisplay_1538;/* '<Root>/Bus Creator2' */
void mul_wide_su32(int32_T in0, uint32_T in2, uint32_T *ptrOutBitsHi, uint32_T
                   *ptrOutBitsLo);
int32_T mul_s32_s32_u32_sr33(int32_T a, uint32_T b);
int32_T mul_s32_s32_u32_sr18(int32_T a, uint32_T b);
void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo);
int32_T mul_s32_s32_s32_sr25_sat(int32_T a, int32_T b);
void pwr_detectAndCountError(uint8_T rtu_stsTransm_speedOfRotation, uint8_T
  rtu_bitMaskError, uint8_T rtu_stsTransm_torque, uint16_T rtu_noErrBefore,
  pwr_rtB_pwr_detectAndCountError_t *localB);

#endif                                 /* RTW_HEADER_pwr_computeEnginePower_private_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */

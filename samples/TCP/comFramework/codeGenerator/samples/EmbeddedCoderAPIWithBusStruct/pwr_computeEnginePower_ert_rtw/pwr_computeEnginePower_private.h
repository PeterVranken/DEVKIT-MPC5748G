/*
 * File: pwr_computeEnginePower_private.h
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

#ifndef RTW_HEADER_pwr_computeEnginePower_private_h_
#define RTW_HEADER_pwr_computeEnginePower_private_h_
#include "rtwtypes.h"
#include "pwr_computeEnginePower.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Imported (extern) block signals */
extern cap_canBus_PT_t cap_canBus_PT;  /* '<Root>/canBus_PT'
                                        * The externally initialized nested struct, which specifies all elements of CAN bus PT
                                        */

/* Imported (extern) pointer block signals */
extern cap_PT_StatusPowerDisplay_1537_t *cap_pPT_StatusPowerDisplay_1537;/* '<Root>/Bus Creator1'
                                                                      * An externally initialized, constant pointer to the external struct describing the outbound frame StatusPowerDisplay (1537, 0x601). Via this pointer the frame's signals can be accessed
                                                                      */
extern cap_PT_LimitsPowerDisplay_1538_t *cap_pPT_LimitsPowerDisplay_1538;/* '<Root>/Bus Creator2'
                                                                      * An externally initialized, constant pointer to the external struct describing the outbound frame LimitsPowerDisplay (1538, 0x602). Via this pointer the frame's signals can be accessed
                                                                      */
extern cap_PT_InfoPowerDisplay_1536_t *cap_pPT_InfoPowerDisplay_1536;/* '<Root>/Bus Creator'
                                                                      * An externally initialized, constant pointer to the external struct describing the outbound frame InfoPowerDisplay (1536, 0x600). Via this pointer the frame's signals can be accessed
                                                                      */
extern void mul_wide_su32(int32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi,
    uint32_T *ptrOutBitsLo);
extern int32_T mul_ssu32_hiSR(int32_T a, uint32_T b, uint32_T aShift);
extern void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi,
    uint32_T *ptrOutBitsLo);
extern int32_T mul_s32_loSR_sat(int32_T a, int32_T b, uint32_T aShift);
extern void pwr_detectAndCountError(uint8_T rtu_stsTransm_speedOfRotation,
    uint8_T rtu_stsTransm_torque, uint8_T rtu_bitMaskError, uint16_T
    rtu_noErrBefore, uint16_T *rty_noErr);

#endif                        /* RTW_HEADER_pwr_computeEnginePower_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * File: C:\user\vranken\projects\comFrameworkAtSourceforge\canInterface\trunk\components\arduinoSampleIntegrationEmbeddedCoder\code\APSW\slprj\ert\_sharedutils\mul_s32_s32_u32_sr33.c
 *
 * Real-Time Workshop code generated for Simulink model pwr_computeEnginePower.
 *
 * Model version                        : 1.129
 * Real-Time Workshop file version      : 7.3  (R2009a)  15-Jan-2009
 * Real-Time Workshop file generated on : Sat May 28 20:34:33 2016
 * TLC version                          : 7.3 (Jan 18 2009)
 * C/C++ source code generated on       : Sat May 28 20:34:34 2016
 */

#include "rtwtypes.h"
#include "rtw_shared_utils.h"

int32_T mul_s32_s32_u32_sr33(int32_T a, uint32_T b)
{
  int32_T result;
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_su32(a, b, &u32_chi, &u32_clo);
  u32_clo = (uint32_T)((int32_T)u32_chi >> 1);
  result = (int32_T)u32_clo;
  return result;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */

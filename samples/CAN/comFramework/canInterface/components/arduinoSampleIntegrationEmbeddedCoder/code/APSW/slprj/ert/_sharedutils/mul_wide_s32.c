/*
 * File: C:\user\vranken\projects\comFrameworkAtSourceforge\canInterface\trunk\components\arduinoSampleIntegrationEmbeddedCoder\code\APSW\slprj\ert\_sharedutils\mul_wide_s32.c
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

void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
  uint32_T outBitsHi;
  uint32_T outBitsLo;
  uint32_T absIn0;
  uint32_T absIn1;
  uint32_T in0Lo;
  uint32_T in0Hi;
  uint32_T in1Hi;
  uint32_T productLoHi;
  uint32_T carry;
  absIn0 = (uint32_T)(in0 < (int32_T)0 ? -in0 : in0);
  absIn1 = (uint32_T)(in1 < (int32_T)0 ? -in1 : in1);
  in0Hi = absIn0 >> 16;
  in0Lo = absIn0 & 65535UL;
  in1Hi = absIn1 >> 16;
  absIn0 = absIn1 & 65535UL;
  absIn1 = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 = in0Lo * absIn0;
  carry = (uint32_T)0;
  outBitsLo = (productLoHi << 16) + absIn0;
  if (outBitsLo < absIn0) {
    carry++;
  }

  absIn0 = outBitsLo;
  outBitsLo = (uint32_T)((absIn1 << 16) + outBitsLo);
  if (outBitsLo < absIn0) {
    carry++;
  }

  outBitsHi = in0Hi * in1Hi + carry + (productLoHi >> 16) + (absIn1 >> 16);
  if (!(in0 == (int32_T)0 || in1 == (int32_T)0 || in0 > (int32_T)0 == in1 >
        (int32_T)0)) {
    outBitsHi = ~outBitsHi;
    outBitsLo = ~outBitsLo;
    outBitsLo++;
    if (outBitsLo == (uint32_T)0) {
      outBitsHi++;
    }
  }

  *ptrOutBitsHi = outBitsHi;
  *ptrOutBitsLo = outBitsLo;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */

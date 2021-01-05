/*
 * File: C:\user\vranken\projects\comFrameworkAtSourceforge\canInterface\trunk\components\arduinoSampleIntegrationEmbeddedCoder\code\APSW\slprj\ert\_sharedutils\mul_wide_su32.c
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

void mul_wide_su32(int32_T in0, uint32_T in2, uint32_T *ptrOutBitsHi, uint32_T
                   *ptrOutBitsLo)
{
  uint32_T outBitsHi;
  uint32_T outBitsLo;
  uint32_T absIn0;
  uint32_T in0Hi;
  uint32_T in1Lo;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  uint32_T carry;
  absIn0 = (uint32_T)(in0 < (int32_T)0 ? -in0 : in0);
  in0Hi = absIn0 >> 16;
  absIn0 = absIn0 & 65535UL;
  in1Hi = in2 >> 16;
  in1Lo = in2 & 65535UL;
  productHiLo = in0Hi * in1Lo;
  productLoHi = absIn0 * in1Hi;
  absIn0 = absIn0 * in1Lo;
  carry = (uint32_T)0;
  outBitsLo = (productLoHi << 16) + absIn0;
  if (outBitsLo < absIn0) {
    carry++;
  }

  absIn0 = outBitsLo;
  outBitsLo = (uint32_T)((productHiLo << 16) + outBitsLo);
  if (outBitsLo < absIn0) {
    carry++;
  }

  outBitsHi = in0Hi * in1Hi + carry + (productLoHi >> 16) + (productHiLo >> 16);
  if (!(in2 == (uint32_T)0 || in0 >= (int32_T)0)) {
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

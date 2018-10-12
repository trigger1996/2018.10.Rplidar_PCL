/*
 * File: detrend.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:12:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "detrend.h"
#include "mldivide.h"

/* Function Definitions */

/*
 * Arguments    : double x[512]
 * Return Type  : void
 */
void detrend(double x[512])
{
  int i;
  double a[1024];
  double b[2];
  double d2;
  int i2;
  for (i = 0; i < 512; i++) {
    a[i] = ((double)i + 1.0) / 512.0;
    a[512 + i] = 1.0;
  }

  mldivide(a, x, b);
  for (i = 0; i < 512; i++) {
    d2 = 0.0;
    for (i2 = 0; i2 < 2; i2++) {
      d2 += a[i + (i2 << 9)] * b[i2];
    }

    x[i] -= d2;
  }
}

/*
 * File trailer for detrend.c
 *
 * [EOF]
 */

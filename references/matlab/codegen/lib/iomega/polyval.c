/*
 * File: polyval.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 15:40:47
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "polyval.h"

/* Function Definitions */

/*
 * Arguments    : const double p[3]
 *                const double x[512]
 *                double y[512]
 * Return Type  : void
 */
void polyval(const double p[3], const double x[512], double y[512])
{
  int i2;
  int k;
  for (i2 = 0; i2 < 512; i2++) {
    y[i2] = p[0];
  }

  for (k = 0; k < 2; k++) {
    for (i2 = 0; i2 < 512; i2++) {
      y[i2] = x[i2] * y[i2] + p[k + 1];
    }
  }
}

/*
 * File trailer for polyval.c
 *
 * [EOF]
 */

/*
 * File: polyval.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:10:50
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
  int i1;
  int k;
  for (i1 = 0; i1 < 512; i1++) {
    y[i1] = p[0];
  }

  for (k = 0; k < 2; k++) {
    for (i1 = 0; i1 < 512; i1++) {
      y[i1] = x[i1] * y[i1] + p[k + 1];
    }
  }
}

/*
 * File trailer for polyval.c
 *
 * [EOF]
 */

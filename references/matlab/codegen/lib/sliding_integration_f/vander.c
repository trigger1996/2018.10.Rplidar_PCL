/*
 * File: vander.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:12:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "vander.h"

/* Function Definitions */

/*
 * Arguments    : const double v[512]
 *                double A[1536]
 * Return Type  : void
 */
void vander(const double v[512], double A[1536])
{
  int k;
  for (k = 0; k < 512; k++) {
    A[1024 + k] = 1.0;
    A[512 + k] = v[k];
    A[k] = v[k] * A[512 + k];
  }
}

/*
 * File trailer for vander.c
 *
 * [EOF]
 */

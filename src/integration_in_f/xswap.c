/*
 * File: xswap.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 15:40:47
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "xswap.h"

/* Function Definitions */

/*
 * Arguments    : double x[1536]
 *                int ix0
 *                int iy0
 * Return Type  : void
 */
void b_xswap(double x[1536], int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 512; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

/*
 * Arguments    : double x[1024]
 *                int ix0
 *                int iy0
 * Return Type  : void
 */
void xswap(double x[1024], int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 512; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

/*
 * File trailer for xswap.c
 *
 * [EOF]
 */

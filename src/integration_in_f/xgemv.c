/*
 * File: xgemv.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 15:40:47
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "xgemv.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                const double A[1536]
 *                int ia0
 *                const double x[1536]
 *                int ix0
 *                double y[3]
 * Return Type  : void
 */
void b_xgemv(int m, int n, const double A[1536], int ia0, const double x[1536],
             int ix0, double y[3])
{
  int iy;
  int i9;
  int iac;
  int ix;
  double c;
  int i10;
  int ia;
  if (n != 0) {
    for (iy = 1; iy <= n; iy++) {
      y[iy - 1] = 0.0;
    }

    iy = 0;
    i9 = ia0 + ((n - 1) << 9);
    for (iac = ia0; iac <= i9; iac += 512) {
      ix = ix0;
      c = 0.0;
      i10 = (iac + m) - 1;
      for (ia = iac; ia <= i10; ia++) {
        c += A[ia - 1] * x[ix - 1];
        ix++;
      }

      y[iy] += c;
      iy++;
    }
  }
}

/*
 * Arguments    : int m
 *                int n
 *                const double A[1024]
 *                int ia0
 *                const double x[1024]
 *                int ix0
 *                double y[2]
 * Return Type  : void
 */
void xgemv(int m, int n, const double A[1024], int ia0, const double x[1024],
           int ix0, double y[2])
{
  int iy;
  int i5;
  int iac;
  int ix;
  double c;
  int i6;
  int ia;
  if (n != 0) {
    for (iy = 1; iy <= n; iy++) {
      y[iy - 1] = 0.0;
    }

    iy = 0;
    i5 = ia0 + ((n - 1) << 9);
    for (iac = ia0; iac <= i5; iac += 512) {
      ix = ix0;
      c = 0.0;
      i6 = (iac + m) - 1;
      for (ia = iac; ia <= i6; ia++) {
        c += A[ia - 1] * x[ix - 1];
        ix++;
      }

      y[iy] += c;
      iy++;
    }
  }
}

/*
 * File trailer for xgemv.c
 *
 * [EOF]
 */

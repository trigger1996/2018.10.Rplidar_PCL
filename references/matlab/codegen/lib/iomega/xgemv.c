/*
 * File: xgemv.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:10:50
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
  int i8;
  int iac;
  int ix;
  double c;
  int i9;
  int ia;
  if (n != 0) {
    for (iy = 1; iy <= n; iy++) {
      y[iy - 1] = 0.0;
    }

    iy = 0;
    i8 = ia0 + ((n - 1) << 9);
    for (iac = ia0; iac <= i8; iac += 512) {
      ix = ix0;
      c = 0.0;
      i9 = (iac + m) - 1;
      for (ia = iac; ia <= i9; ia++) {
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
  int i4;
  int iac;
  int ix;
  double c;
  int i5;
  int ia;
  if (n != 0) {
    for (iy = 1; iy <= n; iy++) {
      y[iy - 1] = 0.0;
    }

    iy = 0;
    i4 = ia0 + ((n - 1) << 9);
    for (iac = ia0; iac <= i4; iac += 512) {
      ix = ix0;
      c = 0.0;
      i5 = (iac + m) - 1;
      for (ia = iac; ia <= i5; ia++) {
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

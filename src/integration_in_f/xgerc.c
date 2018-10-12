/*
 * File: xgerc.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 13:32:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "xgerc.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                double alpha1
 *                int ix0
 *                const double y[3]
 *                double A[1536]
 *                int ia0
 * Return Type  : void
 */
void b_xgerc(int m, int n, double alpha1, int ix0, const double y[3], double A
             [1536], int ia0)
{
  int jA;
  int jy;
  int j;
  double temp;
  int ix;
  int i10;
  int ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if (y[jy] != 0.0) {
        temp = y[jy] * alpha1;
        ix = ix0;
        i10 = m + jA;
        for (ijA = jA; ijA + 1 <= i10; ijA++) {
          A[ijA] += A[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += 512;
    }
  }
}

/*
 * Arguments    : int m
 *                int n
 *                double alpha1
 *                int ix0
 *                const double y[2]
 *                double A[1024]
 *                int ia0
 * Return Type  : void
 */
void xgerc(int m, int n, double alpha1, int ix0, const double y[2], double A
           [1024], int ia0)
{
  int jA;
  int jy;
  int j;
  double temp;
  int ix;
  int i6;
  int ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if (y[jy] != 0.0) {
        temp = y[jy] * alpha1;
        ix = ix0;
        i6 = m + jA;
        for (ijA = jA; ijA + 1 <= i6; ijA++) {
          A[ijA] += A[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += 512;
    }
  }
}

/*
 * File trailer for xgerc.c
 *
 * [EOF]
 */

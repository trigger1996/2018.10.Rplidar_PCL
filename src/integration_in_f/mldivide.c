/*
 * File: mldivide.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 13:32:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "mldivide.h"
#include "qrsolve.h"
#include "xgeqp3.h"

/* Function Definitions */

/*
 * Arguments    : const double A[1024]
 *                const double B[512]
 *                double Y[2]
 * Return Type  : void
 */
void mldivide(const double A[1024], const double B[512], double Y[2])
{
  double b_A[1024];
  double tau[2];
  int jpvt[2];
  int rankA;
  double b_B[512];
  int j;
  int i;
  double wj;
  memcpy(&b_A[0], &A[0], sizeof(double) << 10);
  xgeqp3(b_A, tau, jpvt);
  rankA = rankFromQR(b_A);
  memcpy(&b_B[0], &B[0], sizeof(double) << 9);
  for (j = 0; j < 2; j++) {
    Y[j] = 0.0;
    if (tau[j] != 0.0) {
      wj = b_B[j];
      for (i = j + 1; i + 1 < 513; i++) {
        wj += b_A[i + (j << 9)] * b_B[i];
      }

      wj *= tau[j];
      if (wj != 0.0) {
        b_B[j] -= wj;
        for (i = j + 1; i + 1 < 513; i++) {
          b_B[i] -= b_A[i + (j << 9)] * wj;
        }
      }
    }
  }

  for (i = 0; i + 1 <= rankA; i++) {
    Y[jpvt[i] - 1] = b_B[i];
  }

  for (j = rankA - 1; j + 1 > 0; j--) {
    Y[jpvt[j] - 1] /= b_A[j + (j << 9)];
    i = 1;
    while (i <= j) {
      Y[jpvt[0] - 1] -= Y[jpvt[j] - 1] * b_A[j << 9];
      i = 2;
    }
  }
}

/*
 * File trailer for mldivide.c
 *
 * [EOF]
 */

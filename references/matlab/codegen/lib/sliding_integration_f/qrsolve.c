/*
 * File: qrsolve.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:12:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "qrsolve.h"
#include "xgeqp3.h"

/* Function Declarations */
static int b_rankFromQR(const double A[1536]);

/* Function Definitions */

/*
 * Arguments    : const double A[1536]
 * Return Type  : int
 */
static int b_rankFromQR(const double A[1536])
{
  int r;
  double tol;
  r = 0;
  tol = 512.0 * fabs(A[0]) * 2.2204460492503131E-16;
  while ((r < 3) && (!(fabs(A[r + (r << 9)]) <= tol))) {
    r++;
  }

  return r;
}

/*
 * Arguments    : const double A[1536]
 *                const double B[512]
 *                double Y[3]
 *                int *rankR
 * Return Type  : void
 */
void qrsolve(const double A[1536], const double B[512], double Y[3], int *rankR)
{
  double b_A[1536];
  double tau[3];
  int jpvt[3];
  double b_B[512];
  int j;
  int i;
  double wj;
  memcpy(&b_A[0], &A[0], 1536U * sizeof(double));
  b_xgeqp3(b_A, tau, jpvt);
  *rankR = b_rankFromQR(b_A);
  memcpy(&b_B[0], &B[0], sizeof(double) << 9);
  for (j = 0; j < 3; j++) {
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

  for (i = 0; i < 3; i++) {
    Y[jpvt[i] - 1] = b_B[i];
  }

  for (j = 2; j >= 0; j--) {
    Y[jpvt[j] - 1] /= b_A[j + (j << 9)];
    for (i = 0; i + 1 <= j; i++) {
      Y[jpvt[i] - 1] -= Y[jpvt[j] - 1] * b_A[i + (j << 9)];
    }
  }
}

/*
 * Arguments    : const double A[1024]
 * Return Type  : int
 */
int rankFromQR(const double A[1024])
{
  int r;
  double tol;
  r = 0;
  tol = 512.0 * fabs(A[0]) * 2.2204460492503131E-16;
  while ((r < 2) && (!(fabs(A[r + (r << 9)]) <= tol))) {
    r++;
  }

  return r;
}

/*
 * File trailer for qrsolve.c
 *
 * [EOF]
 */

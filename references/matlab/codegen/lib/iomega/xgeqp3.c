/*
 * File: xgeqp3.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:10:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "xgeqp3.h"
#include "xnrm2.h"
#include "sqrt.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "xswap.h"
#include "ixamax.h"

/* Function Definitions */

/*
 * Arguments    : double A[1536]
 *                double tau[3]
 *                int jpvt[3]
 * Return Type  : void
 */
void b_xgeqp3(double A[1536], double tau[3], int jpvt[3])
{
  int i;
  double TOL3Z;
  double work[3];
  int k;
  int pvt;
  double temp1;
  double vn2[3];
  double vn1[3];
  int itemp;
  double temp2;
  for (i = 0; i < 3; i++) {
    jpvt[i] = 1 + i;
    work[i] = 0.0;
  }

  TOL3Z = 2.2204460492503131E-16;
  c_sqrt(&TOL3Z);
  k = 1;
  for (pvt = 0; pvt < 3; pvt++) {
    temp1 = c_xnrm2(A, k);
    vn2[pvt] = temp1;
    k += 512;
    vn1[pvt] = temp1;
  }

  for (i = 0; i < 3; i++) {
    k = i + (i << 9);
    pvt = (i + b_ixamax(3 - i, vn1, i + 1)) - 1;
    if (pvt + 1 != i + 1) {
      b_xswap(A, 1 + (pvt << 9), 1 + (i << 9));
      itemp = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = itemp;
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }

    temp1 = A[k];
    tau[i] = b_xzlarfg(512 - i, &temp1, A, k + 2);
    A[k] = temp1;
    if (i + 1 < 3) {
      temp1 = A[k];
      A[k] = 1.0;
      b_xzlarf(512 - i, 2 - i, k + 1, tau[i], A, (i + ((i + 1) << 9)) + 1, work);
      A[k] = temp1;
    }

    for (pvt = i + 1; pvt + 1 < 4; pvt++) {
      if (vn1[pvt] != 0.0) {
        temp1 = fabs(A[i + (pvt << 9)]) / vn1[pvt];
        temp1 = 1.0 - temp1 * temp1;
        if (temp1 < 0.0) {
          temp1 = 0.0;
        }

        temp2 = vn1[pvt] / vn2[pvt];
        temp2 = temp1 * (temp2 * temp2);
        if (temp2 <= TOL3Z) {
          vn1[pvt] = d_xnrm2(511 - i, A, (i + (pvt << 9)) + 2);
          vn2[pvt] = vn1[pvt];
        } else {
          c_sqrt(&temp1);
          vn1[pvt] *= temp1;
        }
      }
    }
  }
}

/*
 * Arguments    : double A[1024]
 *                double tau[2]
 *                int jpvt[2]
 * Return Type  : void
 */
void xgeqp3(double A[1024], double tau[2], int jpvt[2])
{
  int i;
  int k;
  double work[2];
  int pvt;
  double temp1;
  double vn2[2];
  double vn1[2];
  int itemp;
  double temp2;
  for (i = 0; i < 2; i++) {
    jpvt[i] = 1 + i;
    work[i] = 0.0;
  }

  b_sqrt(2.2204460492503131E-16);
  k = 1;
  for (pvt = 0; pvt < 2; pvt++) {
    temp1 = xnrm2(A, k);
    vn2[pvt] = temp1;
    k += 512;
    vn1[pvt] = temp1;
  }

  for (i = 0; i < 2; i++) {
    k = i + (i << 9);
    pvt = (i + ixamax(2 - i, vn1, i + 1)) - 1;
    if (pvt + 1 != i + 1) {
      xswap(A, 1 + (pvt << 9), 1 + (i << 9));
      itemp = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = itemp;
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }

    temp1 = A[k];
    tau[i] = xzlarfg(512 - i, &temp1, A, k + 2);
    A[k] = temp1;
    if (i + 1 < 2) {
      temp1 = A[k];
      A[k] = 1.0;
      xzlarf(512, 1, k + 1, tau[0], A, 513, work);
      A[k] = temp1;
    }

    pvt = i + 2;
    while (pvt < 3) {
      if (vn1[1] != 0.0) {
        temp1 = fabs(A[512 + i]) / vn1[1];
        temp1 = 1.0 - temp1 * temp1;
        if (temp1 < 0.0) {
          temp1 = 0.0;
        }

        temp2 = vn1[1] / vn2[1];
        temp2 = temp1 * (temp2 * temp2);
        if (temp2 <= 1.4901161193847656E-8) {
          vn1[1] = b_xnrm2(511 - i, A, i + 514);
          vn2[1] = vn1[1];
        } else {
          c_sqrt(&temp1);
          vn1[1] *= temp1;
        }
      }

      pvt = 3;
    }
  }
}

/*
 * File trailer for xgeqp3.c
 *
 * [EOF]
 */

/* Include Files */
#include "include/x.h"
#include "include/matlab_math.h"
#include "include/inte_util.h"

/* Function Definitions */
static int b_rankFromQR(const double A[1536]);

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
 * Arguments    : int n
 *                const double x[1024]
 *                int ix0
 * Return Type  : double
 */
double b_xnrm2(int n, const double x[1024], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double b_t;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          b_t = scale / absxk;
          y = 1.0 + y * b_t * b_t;
          scale = absxk;
        } else {
          b_t = absxk / scale;
          y += b_t * b_t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/*
 * Arguments    : const double x[1536]
 *                int ix0
 * Return Type  : double
 */
double c_xnrm2(const double x[1536], int ix0)
{
  double y;
  double scale;
  int k;
  double absxk;
  double b_t;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = ix0; k <= ix0 + 511; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      b_t = scale / absxk;
      y = 1.0 + y * b_t * b_t;
      scale = absxk;
    } else {
      b_t = absxk / scale;
      y += b_t * b_t;
    }
  }

  return scale * sqrt(y);
}

/*
 * Arguments    : int n
 *                const double x[1536]
 *                int ix0
 * Return Type  : double
 */
double d_xnrm2(int n, const double x[1536], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double b_t;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          b_t = scale / absxk;
          y = 1.0 + y * b_t * b_t;
          scale = absxk;
        } else {
          b_t = absxk / scale;
          y += b_t * b_t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/*
 * Arguments    : const double x[1024]
 *                int ix0
 * Return Type  : double
 */
double xnrm2(const double x[1024], int ix0)
{
  double y;
  double scale;
  int k;
  double absxk;
  double b_t;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = ix0; k <= ix0 + 511; k++) {
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      b_t = scale / absxk;
      y = 1.0 + y * b_t * b_t;
      scale = absxk;
    } else {
      b_t = absxk / scale;
      y += b_t * b_t;
    }
  }

  return scale * sqrt(y);
}

/*
 * Arguments    : int n
 *                const double x[3]
 *                int ix0
 * Return Type  : int
 */
int b_ixamax(int n, const double x[3], int ix0)
{
  int idxmax;
  int ix;
  double smax;
  int k;
  double s;
  if (n < 1) {
    idxmax = 0;
  } else {
    idxmax = 1;
    if (n > 1) {
      ix = ix0 - 1;
      smax = fabs(x[ix0 - 1]);
      for (k = 2; k <= n; k++) {
        ix++;
        s = fabs(x[ix]);
        if (s > smax) {
          idxmax = k;
          smax = s;
        }
      }
    }
  }

  return idxmax;
}

/*
 * Arguments    : int n
 *                const double x[2]
 *                int ix0
 * Return Type  : int
 */
int ixamax(int n, const double x[2], int ix0)
{
  int idxmax;
  int ix;
  double smax;
  int k;
  double s;
  if (n < 1) {
    idxmax = 0;
  } else {
    idxmax = 1;
    if (n > 1) {
      ix = ix0 - 1;
      smax = fabs(x[ix0 - 1]);
      for (k = 2; k <= n; k++) {
        ix++;
        s = fabs(x[ix]);
        if (s > smax) {
          idxmax = k;
          smax = s;
        }
      }
    }
  }

  return idxmax;
}

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
 * Arguments    : int m
 *                int n
 *                const double A[1536]
 *                int ia0
 * Return Type  : int
 */
static int b_ilazlc(int m, int n, const double A[1536], int ia0)
{
  int j;
  boolean_T exitg2;
  int coltop;
  int ia;
  int exitg1;
  j = n;
  exitg2 = false;
  while ((!exitg2) && (j > 0)) {
    coltop = ia0 + ((j - 1) << 9);
    ia = coltop;
    do {
      exitg1 = 0;
      if (ia <= (coltop + m) - 1) {
        if (A[ia - 1] != 0.0) {
          exitg1 = 1;
        } else {
          ia++;
        }
      } else {
        j--;
        exitg1 = 2;
      }
    } while (exitg1 == 0);

    if (exitg1 == 1) {
      exitg2 = true;
    }
  }

  return j;
}

/*
 * Arguments    : int m
 *                int n
 *                const double A[1024]
 *                int ia0
 * Return Type  : int
 */
static int ilazlc(int m, int n, const double A[1024], int ia0)
{
  int j;
  boolean_T exitg2;
  int coltop;
  int ia;
  int exitg1;
  j = n;
  exitg2 = false;
  while ((!exitg2) && (j > 0)) {
    coltop = ia0 + ((j - 1) << 9);
    ia = coltop;
    do {
      exitg1 = 0;
      if (ia <= (coltop + m) - 1) {
        if (A[ia - 1] != 0.0) {
          exitg1 = 1;
        } else {
          ia++;
        }
      } else {
        j--;
        exitg1 = 2;
      }
    } while (exitg1 == 0);

    if (exitg1 == 1) {
      exitg2 = true;
    }
  }

  return j;
}

/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                double tau
 *                double C[1536]
 *                int ic0
 *                double work[3]
 * Return Type  : void
 */
void b_xzlarf(int m, int n, int iv0, double tau, double C[1536], int ic0, double
              work[3])
{
  int lastv;
  int lastc;
  if (tau != 0.0) {
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && (C[lastc - 2] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = b_ilazlc(lastv, n, C, ic0);
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    b_xgemv(lastv, lastc, C, ic0, C, iv0, work);
    b_xgerc(lastv, lastc, -tau, iv0, work, C, ic0);
  }
}

/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                double tau
 *                double C[1024]
 *                int ic0
 *                double work[2]
 * Return Type  : void
 */
void xzlarf(int m, int n, int iv0, double tau, double C[1024], int ic0, double
            work[2])
{
  int lastv;
  int lastc;
  if (tau != 0.0) {
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && (C[lastc - 2] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = ilazlc(lastv, n, C, ic0);
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    xgemv(lastv, lastc, C, ic0, C, iv0, work);
    xgerc(lastv, lastc, -tau, iv0, work, C, ic0);
  }
}

/*
 * Arguments    : int n
 *                double *alpha1
 *                double x[1536]
 *                int ix0
 * Return Type  : double
 */
double b_xzlarfg(int n, double *alpha1, double x[1536], int ix0)
{
  double tau;
  double xnorm;
  int knt;
  int i8;
  int k;
  tau = 0.0;
  if (!(n <= 0)) {
    xnorm = d_xnrm2(n - 1, x, ix0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        i8 = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i8; k++) {
            x[k - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

        xnorm = rt_hypotd_snf(*alpha1, d_xnrm2(n - 1, x, ix0));
        if (*alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i8 = (ix0 + n) - 2;
        for (k = ix0; k <= i8; k++) {
          x[k - 1] *= *alpha1;
        }

        for (k = 1; k <= knt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i8 = (ix0 + n) - 2;
        for (k = ix0; k <= i8; k++) {
          x[k - 1] *= *alpha1;
        }

        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

/*
 * Arguments    : int n
 *                double *alpha1
 *                double x[1024]
 *                int ix0
 * Return Type  : double
 */
double xzlarfg(int n, double *alpha1, double x[1024], int ix0)
{
  double tau;
  double xnorm;
  int knt;
  int i4;
  int k;
  tau = 0.0;
  if (!(n <= 0)) {
    xnorm = b_xnrm2(n - 1, x, ix0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        i4 = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i4; k++) {
            x[k - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

        xnorm = rt_hypotd_snf(*alpha1, b_xnrm2(n - 1, x, ix0));
        if (*alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i4 = (ix0 + n) - 2;
        for (k = ix0; k <= i4; k++) {
          x[k - 1] *= *alpha1;
        }

        for (k = 1; k <= knt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i4 = (ix0 + n) - 2;
        for (k = ix0; k <= i4; k++) {
          x[k - 1] *= *alpha1;
        }

        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

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
  int i11;
  int ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if (y[jy] != 0.0) {
        temp = y[jy] * alpha1;
        ix = ix0;
        i11 = m + jA;
        for (ijA = jA; ijA + 1 <= i11; ijA++) {
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
  int i7;
  int ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if (y[jy] != 0.0) {
        temp = y[jy] * alpha1;
        ix = ix0;
        i7 = m + jA;
        for (ijA = jA; ijA + 1 <= i7; ijA++) {
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
 * File trailer for xgemv.c
 *
 * [EOF]
 */


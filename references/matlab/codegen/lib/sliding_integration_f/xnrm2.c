/*
 * File: xnrm2.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:12:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "xnrm2.h"

/* Function Definitions */

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
 * File trailer for xnrm2.c
 *
 * [EOF]
 */

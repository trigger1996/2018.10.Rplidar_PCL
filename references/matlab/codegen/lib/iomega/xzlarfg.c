/*
 * File: xzlarfg.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:10:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "xzlarfg.h"
#include "xnrm2.h"
#include "iomega_rtwutil.h"

/* Function Definitions */

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
  int i7;
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
        i7 = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i7; k++) {
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
        i7 = (ix0 + n) - 2;
        for (k = ix0; k <= i7; k++) {
          x[k - 1] *= *alpha1;
        }

        for (k = 1; k <= knt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i7 = (ix0 + n) - 2;
        for (k = ix0; k <= i7; k++) {
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
  int i3;
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
        i3 = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i3; k++) {
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
        i3 = (ix0 + n) - 2;
        for (k = ix0; k <= i3; k++) {
          x[k - 1] *= *alpha1;
        }

        for (k = 1; k <= knt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i3 = (ix0 + n) - 2;
        for (k = ix0; k <= i3; k++) {
          x[k - 1] *= *alpha1;
        }

        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

/*
 * File trailer for xzlarfg.c
 *
 * [EOF]
 */

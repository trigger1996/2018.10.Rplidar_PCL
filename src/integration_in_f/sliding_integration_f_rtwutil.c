/*
 * File: sliding_integration_f_rtwutil.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 13:32:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "sliding_integration_f_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/*
 * File trailer for sliding_integration_f_rtwutil.c
 *
 * [EOF]
 */

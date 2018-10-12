/*
 * File: polyfit.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 15:40:47
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "polyfit.h"
#include "qrsolve.h"
#include "vander.h"

/* Function Definitions */

/*
 * Arguments    : const double x[512]
 *                const double y[512]
 *                double p[3]
 * Return Type  : void
 */
void polyfit(const double x[512], const double y[512], double p[3])
{
  double dv8[1536];
  int rr;
  vander(x, dv8);
  qrsolve(dv8, y, p, &rr);
}

/*
 * File trailer for polyfit.c
 *
 * [EOF]
 */

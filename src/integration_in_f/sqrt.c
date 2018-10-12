/*
 * File: sqrt.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 13:32:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : double x
 * Return Type  : double
 */
double b_sqrt(double x)
{
  double b_x;
  b_x = x;
  c_sqrt(&b_x);
  return b_x;
}

/*
 * Arguments    : double *x
 * Return Type  : void
 */
void c_sqrt(double *x)
{
  *x = sqrt(*x);
}

/*
 * File trailer for sqrt.c
 *
 * [EOF]
 */

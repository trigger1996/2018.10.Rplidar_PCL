/*
 * File: xnrm2.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 15:40:47
 */

#ifndef XNRM2_H
#define XNRM2_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "iomega_types.h"

/* Function Declarations */
extern double b_xnrm2(int n, const double x[1024], int ix0);
extern double c_xnrm2(const double x[1536], int ix0);
extern double d_xnrm2(int n, const double x[1536], int ix0);
extern double xnrm2(const double x[1024], int ix0);

#endif

/*
 * File trailer for xnrm2.h
 *
 * [EOF]
 */

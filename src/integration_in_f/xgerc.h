/*
 * File: xgerc.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 13:32:32
 */

#ifndef XGERC_H
#define XGERC_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "sliding_integration_f_types.h"

/* Function Declarations */
extern void b_xgerc(int m, int n, double alpha1, int ix0, const double y[3],
                    double A[1536], int ia0);
extern void xgerc(int m, int n, double alpha1, int ix0, const double y[2],
                  double A[1024], int ia0);

#endif

/*
 * File trailer for xgerc.h
 *
 * [EOF]
 */

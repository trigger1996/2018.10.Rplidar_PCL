/*
 * File: xgemv.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 13:32:32
 */

#ifndef XGEMV_H
#define XGEMV_H

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
extern void b_xgemv(int m, int n, const double A[1536], int ia0, const double x
                    [1536], int ix0, double y[3]);
extern void xgemv(int m, int n, const double A[1024], int ia0, const double x
                  [1024], int ix0, double y[2]);

#endif

/*
 * File trailer for xgemv.h
 *
 * [EOF]
 */

/*
 * File: xzlarf.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 13:32:32
 */

#ifndef XZLARF_H
#define XZLARF_H

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
extern void b_xzlarf(int m, int n, int iv0, double tau, double C[1536], int ic0,
                     double work[3]);
extern void xzlarf(int m, int n, int iv0, double tau, double C[1024], int ic0,
                   double work[2]);

#endif

/*
 * File trailer for xzlarf.h
 *
 * [EOF]
 */

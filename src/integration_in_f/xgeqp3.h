/*
 * File: xgeqp3.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 13:32:32
 */

#ifndef XGEQP3_H
#define XGEQP3_H

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
extern void b_xgeqp3(double A[1536], double tau[3], int jpvt[3]);
extern void xgeqp3(double A[1024], double tau[2], int jpvt[2]);

#endif

/*
 * File trailer for xgeqp3.h
 *
 * [EOF]
 */

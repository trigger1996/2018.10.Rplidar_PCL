/*
 * File: qrsolve.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 15:40:47
 */

#ifndef QRSOLVE_H
#define QRSOLVE_H

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
extern void qrsolve(const double A[1536], const double B[512], double Y[3], int *
                    rankR);
extern int rankFromQR(const double A[1024]);

#endif

/*
 * File trailer for qrsolve.h
 *
 * [EOF]
 */

/*
 * File: iomega.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:12:01
 */

#ifndef IOMEGA_H
#define IOMEGA_H

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
extern void b_iomega(const double datain[512], double dt, double dataout[512]);
extern void iomega(const double datain[512], double dt, double datain_type,
                   double dataout_type, double dataout[512]);

#endif

/*
 * File trailer for iomega.h
 *
 * [EOF]
 */

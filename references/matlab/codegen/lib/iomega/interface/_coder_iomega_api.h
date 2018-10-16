/*
 * File: _coder_iomega_api.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 15:40:47
 */

#ifndef _CODER_IOMEGA_API_H
#define _CODER_IOMEGA_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_iomega_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void iomega(real_T datain[512], real_T dt, real_T datain_type, real_T
                   dataout_type, real_T dataout[512]);
extern void iomega_api(const mxArray * const prhs[4], const mxArray *plhs[1]);
extern void iomega_atexit(void);
extern void iomega_initialize(void);
extern void iomega_terminate(void);
extern void iomega_xil_terminate(void);
extern void sliding_integrate_f(real_T ax_in, real_T ay_in, real_T ts, real_T
  arr_len_in, real_T *dst_x, real_T *dst_y, real_T *vel_x, real_T *vel_y);
extern void sliding_integrate_f_api(const mxArray * const prhs[4], const mxArray
  *plhs[4]);

#endif

/*
 * File trailer for _coder_iomega_api.h
 *
 * [EOF]
 */
/*
 * File: _coder_sliding_integration_f_api.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:12:01
 */

#ifndef _CODER_SLIDING_INTEGRATION_F_API_H
#define _CODER_SLIDING_INTEGRATION_F_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_sliding_integration_f_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void iomega(real_T datain[512], real_T dt, real_T datain_type, real_T
                   dataout_type, real_T dataout[512]);
extern void iomega_api(const mxArray * const prhs[4], const mxArray *plhs[1]);
extern void sliding_integrate_f(real_T data_in, real_T ts, real_T arr_len_in,
  real_T *dst, real_T *vel);
extern void sliding_integrate_f_api(const mxArray * const prhs[3], const mxArray
  *plhs[2]);
extern void sliding_integration_f_atexit(void);
extern void sliding_integration_f_initialize(void);
extern void sliding_integration_f_terminate(void);
extern void sliding_integration_f_xil_terminate(void);

#endif

/*
 * File trailer for _coder_sliding_integration_f_api.h
 *
 * [EOF]
 */

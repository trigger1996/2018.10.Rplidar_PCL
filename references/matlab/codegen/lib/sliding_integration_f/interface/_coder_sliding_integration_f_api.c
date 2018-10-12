/*
 * File: _coder_sliding_integration_f_api.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:12:01
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_sliding_integration_f_api.h"
#include "_coder_sliding_integration_f_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131451U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "sliding_integration_f",             /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[512];
static const mxArray *b_emlrt_marshallOut(const real_T u[512]);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *dt, const
  char_T *identifier);
static const mxArray *c_emlrt_marshallOut(const real_T u[512]);
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *acc_arr,
  const char_T *identifier, real_T y[512]);
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *datain,
  const char_T *identifier))[512];
static const mxArray *emlrt_marshallOut(const real_T u);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[512]);
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[512];
static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[512]);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[512]
 */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[512]
{
  real_T (*y)[512];
  y = g_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const real_T u[512]
 * Return Type  : const mxArray *
 */
  static const mxArray *b_emlrt_marshallOut(const real_T u[512])
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv0[1] = { 512 };

  real_T *pData;
  int32_T i;
  y = NULL;
  m1 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)emlrtMxGetPr(m1);
  for (i = 0; i < 512; i++) {
    pData[i] = u[i];
  }

  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *dt
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *dt, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(dt), &thisId);
  emlrtDestroyArray(&dt);
  return y;
}

/*
 * Arguments    : const real_T u[512]
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrt_marshallOut(const real_T u[512])
{
  const mxArray *y;
  const mxArray *m2;
  static const int32_T iv1[1] = { 0 };

  static const int32_T iv2[1] = { 512 };

  y = NULL;
  m2 = emlrtCreateNumericArray(1, iv1, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m2, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m2, iv2, 1);
  emlrtAssign(&y, m2);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *acc_arr
 *                const char_T *identifier
 *                real_T y[512]
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *acc_arr,
  const char_T *identifier, real_T y[512])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(sp, emlrtAlias(acc_arr), &thisId, y);
  emlrtDestroyArray(&acc_arr);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *datain
 *                const char_T *identifier
 * Return Type  : real_T (*)[512]
 */
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *datain,
  const char_T *identifier))[512]
{
  real_T (*y)[512];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(datain), &thisId);
  emlrtDestroyArray(&datain);
  return y;
}
/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
  static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[512]
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[512])
{
  i_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[512]
 */
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[512]
{
  real_T (*ret)[512];
  static const int32_T dims[1] = { 512 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[512])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
  static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[512]
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[512])
{
  static const int32_T dims[1] = { 512 };

  int32_T i0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  for (i0 = 0; i0 < 512; i0++) {
    ret[i0] = (*(real_T (*)[512])emlrtMxGetData(src))[i0];
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray * const prhs[4]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void iomega_api(const mxArray * const prhs[4], const mxArray *plhs[1])
{
  real_T (*dataout)[512];
  real_T (*datain)[512];
  real_T dt;
  real_T datain_type;
  real_T dataout_type;
  const mxArray *tmp;
  real_T arr_len;
  real_T acc_arr[512];
  real_T vel_arr[512];
  real_T t[512];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  dataout = (real_T (*)[512])mxMalloc(sizeof(real_T [512]));

  /* Marshall function inputs */
  datain = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "datain");
  dt = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "dt");
  datain_type = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "datain_type");
  dataout_type = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "dataout_type");

  /* Marshall in global variables */
  tmp = emlrtGetGlobalVariable("arr_len");
  if (tmp != NULL) {
    arr_len = c_emlrt_marshallIn(&st, tmp, "arr_len");
  }

  tmp = emlrtGetGlobalVariable("acc_arr");
  if (tmp != NULL) {
    e_emlrt_marshallIn(&st, tmp, "acc_arr", acc_arr);
  }

  tmp = emlrtGetGlobalVariable("vel_arr");
  if (tmp != NULL) {
    e_emlrt_marshallIn(&st, tmp, "vel_arr", vel_arr);
  }

  tmp = emlrtGetGlobalVariable("t");
  if (tmp != NULL) {
    e_emlrt_marshallIn(&st, tmp, "t", t);
  }

  /* Invoke the target function */
  iomega(*datain, dt, datain_type, dataout_type, *dataout);

  /* Marshall out global variables */
  emlrtPutGlobalVariable("arr_len", emlrt_marshallOut(arr_len));
  emlrtPutGlobalVariable("acc_arr", b_emlrt_marshallOut(acc_arr));
  emlrtPutGlobalVariable("vel_arr", b_emlrt_marshallOut(vel_arr));
  emlrtPutGlobalVariable("t", b_emlrt_marshallOut(t));

  /* Marshall function outputs */
  plhs[0] = c_emlrt_marshallOut(*dataout);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void sliding_integrate_f_api(const mxArray * const prhs[3], const mxArray *plhs
  [2])
{
  real_T data_in;
  real_T ts;
  real_T arr_len_in;
  const mxArray *tmp;
  real_T arr_len;
  real_T acc_arr[512];
  real_T vel_arr[512];
  real_T t[512];
  real_T dst;
  real_T vel;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  data_in = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "data_in");
  ts = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "ts");
  arr_len_in = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "arr_len_in");

  /* Marshall in global variables */
  tmp = emlrtGetGlobalVariable("arr_len");
  if (tmp != NULL) {
    arr_len = c_emlrt_marshallIn(&st, tmp, "arr_len");
  }

  tmp = emlrtGetGlobalVariable("acc_arr");
  if (tmp != NULL) {
    e_emlrt_marshallIn(&st, tmp, "acc_arr", acc_arr);
  }

  tmp = emlrtGetGlobalVariable("vel_arr");
  if (tmp != NULL) {
    e_emlrt_marshallIn(&st, tmp, "vel_arr", vel_arr);
  }

  tmp = emlrtGetGlobalVariable("t");
  if (tmp != NULL) {
    e_emlrt_marshallIn(&st, tmp, "t", t);
  }

  /* Invoke the target function */
  sliding_integrate_f(data_in, ts, arr_len_in, &dst, &vel);

  /* Marshall out global variables */
  emlrtPutGlobalVariable("arr_len", emlrt_marshallOut(arr_len));
  emlrtPutGlobalVariable("acc_arr", b_emlrt_marshallOut(acc_arr));
  emlrtPutGlobalVariable("vel_arr", b_emlrt_marshallOut(vel_arr));
  emlrtPutGlobalVariable("t", b_emlrt_marshallOut(t));

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(dst);
  plhs[1] = emlrt_marshallOut(vel);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void sliding_integration_f_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  sliding_integration_f_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void sliding_integration_f_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void sliding_integration_f_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_sliding_integration_f_api.c
 *
 * [EOF]
 */

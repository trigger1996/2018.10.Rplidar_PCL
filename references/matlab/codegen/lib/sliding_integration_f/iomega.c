/*
 * File: iomega.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:12:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "ifft.h"
#include "ifftshift.h"
#include "sliding_integration_f_emxutil.h"
#include "fft.h"
#include "sliding_integration_f_rtwutil.h"

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);
static double rt_powd_snf(double u0, double u1);
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = 1.0;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *
 *    IOMEGA is a MATLAB script for converting displacement, velocity, or
 *    acceleration time-series to either displacement, velocity, or
 *    acceleration times-series. The script takes an array of waveform data
 *    (datain), transforms into the frequency-domain in order to more easily
 *    convert into desired output form, and then converts back into the time
 *    domain resulting in output (dataout) that is converted into the desired
 *    form.
 *
 *    Variables:
 *    ----------
 *
 *    datain       =   input waveform data of type datain_type
 *
 *    dataout      =   output waveform data of type dataout_type
 *
 *    dt           =   time increment (units of seconds per sample)
 *
 *                     1 - Displacement
 *    datain_type  =   2 - Velocity
 *                     3 - Acceleration
 *
 *                     1 - Displacement
 *    dataout_type =   2 - Velocity
 *                     3 - Acceleration
 *
 *
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *    Make sure that datain_type and dataout_type are either 1, 2 or 3
 * Arguments    : const double datain[512]
 *                double dt
 *                double dataout[512]
 * Return Type  : void
 */
void b_iomega(const double datain[512], double dt, double dataout[512])
{
  emxArray_real_T *y;
  double df;
  double Nyq;
  double kd;
  int k;
  double ndbl;
  double apnd;
  emxArray_creal_T *iomega_array;
  double cdiff;
  int nm1d2;
  double absa;
  double absb;
  int n;
  creal_T A[512];
  boolean_T b_iomega_array;
  creal_T dcv1[512];
  emxInit_real_T(&y, 2);

  /*    Determine Number of points (next power of 2), frequency increment */
  /*    and Nyquist frequency */
  df = 1.0 / (512.0 * dt);
  Nyq = 1.0 / (2.0 * dt);

  /*    Save frequency array */
  kd = Nyq - df;
  if (rtIsNaN(-Nyq) || rtIsNaN(df) || rtIsNaN(kd)) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, k);
    y->data[0] = rtNaN;
  } else if ((df == 0.0) || ((-Nyq < kd) && (df < 0.0)) || ((kd < -Nyq) && (df >
    0.0))) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 0;
    emxEnsureCapacity_real_T(y, k);
  } else if ((rtIsInf(-Nyq) || rtIsInf(kd)) && (rtIsInf(df) || (-Nyq == kd))) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, k);
    y->data[0] = rtNaN;
  } else if (rtIsInf(df)) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, k);
    y->data[0] = -Nyq;
  } else if ((floor(-Nyq) == -Nyq) && (floor(df) == df)) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)floor((kd - (-Nyq)) / df) + 1;
    emxEnsureCapacity_real_T(y, k);
    nm1d2 = (int)floor((kd - (-Nyq)) / df);
    for (k = 0; k <= nm1d2; k++) {
      y->data[y->size[0] * k] = -Nyq + df * (double)k;
    }
  } else {
    ndbl = floor((kd - (-Nyq)) / df + 0.5);
    apnd = -Nyq + ndbl * df;
    if (df > 0.0) {
      cdiff = apnd - kd;
    } else {
      cdiff = kd - apnd;
    }

    absa = fabs(-Nyq);
    absb = fabs(kd);
    if ((absa > absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = kd;
    } else if (cdiff > 0.0) {
      apnd = -Nyq + (ndbl - 1.0) * df;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }

    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity_real_T(y, k);
    if (n > 0) {
      y->data[0] = -Nyq;
      if (n > 1) {
        y->data[n - 1] = apnd;
        nm1d2 = (n - 1) / 2;
        for (k = 1; k < nm1d2; k++) {
          kd = (double)k * df;
          y->data[k] = -Nyq + kd;
          y->data[(n - k) - 1] = apnd - kd;
        }

        if (nm1d2 << 1 == n - 1) {
          y->data[nm1d2] = (-Nyq + apnd) / 2.0;
        } else {
          kd = (double)nm1d2 * df;
          y->data[nm1d2] = -Nyq + kd;
          y->data[nm1d2 + 1] = apnd - kd;
        }
      }
    }
  }

  emxInit_creal_T(&iomega_array, 2);
  k = iomega_array->size[0] * iomega_array->size[1];
  iomega_array->size[0] = 1;
  iomega_array->size[1] = y->size[1];
  emxEnsureCapacity_creal_T(iomega_array, k);
  nm1d2 = y->size[0] * y->size[1];
  for (k = 0; k < nm1d2; k++) {
    iomega_array->data[k].re = y->data[k] * 0.0;
    iomega_array->data[k].im = y->data[k] * 6.2831853071795862;
  }

  emxFree_real_T(&y);

  /*    Pad datain array with zeros (if needed) */
  /*    Transform datain into frequency domain via FFT and shift output (A) */
  /*    so that zero-frequency amplitude is in the middle of the array */
  /*    (instead of the beginning) */
  fft(datain, A);
  for (nm1d2 = 0; nm1d2 < 2; nm1d2++) {
    eml_fftshift(A, nm1d2 + 1);
  }

  /*    Convert datain of type datain_type to type dataout_type */
  for (nm1d2 = 0; nm1d2 < 512; nm1d2++) {
    b_iomega_array = ((iomega_array->data[nm1d2].re != 0.0) ||
                      (iomega_array->data[nm1d2].im != 0.0));
    if (b_iomega_array) {
      cdiff = iomega_array->data[nm1d2].re;
      absb = iomega_array->data[nm1d2].im;
      absa = fabs(cdiff);
      ndbl = fabs(absb);
      if (absb == 0.0) {
        cdiff = 1.0 / cdiff;
        kd = 0.0;
      } else if (cdiff == 0.0) {
        cdiff = 0.0;
        kd = -1.0 / absb;
      } else if (absa > ndbl) {
        ndbl = absb / cdiff;
        kd = cdiff + ndbl * absb;
        cdiff = 1.0 / kd;
        kd = -ndbl / kd;
      } else if (absa == ndbl) {
        kd = 0.5;
        if (cdiff < 0.0) {
          kd = -0.5;
        }

        ndbl = 0.5;
        if (absb < 0.0) {
          ndbl = -0.5;
        }

        cdiff = kd / absa;
        kd = -ndbl / absa;
      } else {
        ndbl = cdiff / absb;
        kd = absb + ndbl * cdiff;
        cdiff = ndbl / kd;
        kd = -1.0 / kd;
      }

      ndbl = A[nm1d2].re;
      A[nm1d2].re = A[nm1d2].re * cdiff - A[nm1d2].im * kd;
      A[nm1d2].im = ndbl * kd + A[nm1d2].im * cdiff;
    } else {
      A[nm1d2].re = 0.0;
      A[nm1d2].im = 0.0;
    }
  }

  emxFree_creal_T(&iomega_array);

  /*    Shift new frequency-amplitude array back to MATLAB format and */
  /*    transform back into the time domain via the inverse FFT. */
  ifftshift(A);

  /*    Remove zeros that were added to datain in order to pad to next */
  /*    biggerst power of 2 and return dataout. */
  ifft(A, dcv1);
  for (nm1d2 = 0; nm1d2 < 512; nm1d2++) {
    dataout[nm1d2] = dcv1[nm1d2].re;
  }
}

/*
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *
 *    IOMEGA is a MATLAB script for converting displacement, velocity, or
 *    acceleration time-series to either displacement, velocity, or
 *    acceleration times-series. The script takes an array of waveform data
 *    (datain), transforms into the frequency-domain in order to more easily
 *    convert into desired output form, and then converts back into the time
 *    domain resulting in output (dataout) that is converted into the desired
 *    form.
 *
 *    Variables:
 *    ----------
 *
 *    datain       =   input waveform data of type datain_type
 *
 *    dataout      =   output waveform data of type dataout_type
 *
 *    dt           =   time increment (units of seconds per sample)
 *
 *                     1 - Displacement
 *    datain_type  =   2 - Velocity
 *                     3 - Acceleration
 *
 *                     1 - Displacement
 *    dataout_type =   2 - Velocity
 *                     3 - Acceleration
 *
 *
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *    Make sure that datain_type and dataout_type are either 1, 2 or 3
 * Arguments    : const double datain[512]
 *                double dt
 *                double datain_type
 *                double dataout_type
 *                double dataout[512]
 * Return Type  : void
 */
void iomega(const double datain[512], double dt, double datain_type, double
            dataout_type, double dataout[512])
{
  emxArray_real_T *y;
  double df;
  double Nyq;
  double ai;
  int k;
  double ndbl;
  double apnd;
  emxArray_creal_T *iomega_array;
  double cdiff;
  int nm1d2;
  double absa;
  double absb;
  int n;
  creal_T A[512];
  boolean_T b_iomega_array;
  creal_T dcv0[512];
  signed char r;
  emxInit_real_T(&y, 2);

  /*    Determine Number of points (next power of 2), frequency increment */
  /*    and Nyquist frequency */
  df = 1.0 / (512.0 * dt);
  Nyq = 1.0 / (2.0 * dt);

  /*    Save frequency array */
  ai = Nyq - df;
  if (rtIsNaN(-Nyq) || rtIsNaN(df) || rtIsNaN(ai)) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, k);
    y->data[0] = rtNaN;
  } else if ((df == 0.0) || ((-Nyq < ai) && (df < 0.0)) || ((ai < -Nyq) && (df >
    0.0))) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 0;
    emxEnsureCapacity_real_T(y, k);
  } else if ((rtIsInf(-Nyq) || rtIsInf(ai)) && (rtIsInf(df) || (-Nyq == ai))) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, k);
    y->data[0] = rtNaN;
  } else if (rtIsInf(df)) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, k);
    y->data[0] = -Nyq;
  } else if ((floor(-Nyq) == -Nyq) && (floor(df) == df)) {
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)floor((ai - (-Nyq)) / df) + 1;
    emxEnsureCapacity_real_T(y, k);
    nm1d2 = (int)floor((ai - (-Nyq)) / df);
    for (k = 0; k <= nm1d2; k++) {
      y->data[y->size[0] * k] = -Nyq + df * (double)k;
    }
  } else {
    ndbl = floor((ai - (-Nyq)) / df + 0.5);
    apnd = -Nyq + ndbl * df;
    if (df > 0.0) {
      cdiff = apnd - ai;
    } else {
      cdiff = ai - apnd;
    }

    absa = fabs(-Nyq);
    absb = fabs(ai);
    if ((absa > absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = ai;
    } else if (cdiff > 0.0) {
      apnd = -Nyq + (ndbl - 1.0) * df;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }

    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity_real_T(y, k);
    if (n > 0) {
      y->data[0] = -Nyq;
      if (n > 1) {
        y->data[n - 1] = apnd;
        nm1d2 = (n - 1) / 2;
        for (k = 1; k < nm1d2; k++) {
          ndbl = (double)k * df;
          y->data[k] = -Nyq + ndbl;
          y->data[(n - k) - 1] = apnd - ndbl;
        }

        if (nm1d2 << 1 == n - 1) {
          y->data[nm1d2] = (-Nyq + apnd) / 2.0;
        } else {
          ndbl = (double)nm1d2 * df;
          y->data[nm1d2] = -Nyq + ndbl;
          y->data[nm1d2 + 1] = apnd - ndbl;
        }
      }
    }
  }

  emxInit_creal_T(&iomega_array, 2);
  k = iomega_array->size[0] * iomega_array->size[1];
  iomega_array->size[0] = 1;
  iomega_array->size[1] = y->size[1];
  emxEnsureCapacity_creal_T(iomega_array, k);
  nm1d2 = y->size[0] * y->size[1];
  for (k = 0; k < nm1d2; k++) {
    iomega_array->data[k].re = y->data[k] * 0.0;
    iomega_array->data[k].im = y->data[k] * 6.2831853071795862;
  }

  emxFree_real_T(&y);
  absa = dataout_type - datain_type;

  /*    Pad datain array with zeros (if needed) */
  /*    Transform datain into frequency domain via FFT and shift output (A) */
  /*    so that zero-frequency amplitude is in the middle of the array */
  /*    (instead of the beginning) */
  fft(datain, A);
  for (nm1d2 = 0; nm1d2 < 2; nm1d2++) {
    eml_fftshift(A, nm1d2 + 1);
  }

  /*    Convert datain of type datain_type to type dataout_type */
  for (nm1d2 = 0; nm1d2 < 512; nm1d2++) {
    b_iomega_array = ((iomega_array->data[nm1d2].re != 0.0) ||
                      (iomega_array->data[nm1d2].im != 0.0));
    if (b_iomega_array) {
      ndbl = iomega_array->data[nm1d2].re;
      ai = iomega_array->data[nm1d2].im;
      if ((ai == 0.0) && (ndbl >= 0.0)) {
        ndbl = rt_powd_snf(ndbl, absa);
        cdiff = 0.0;
      } else if ((ndbl == 0.0) && (floor(absa) == absa)) {
        cdiff = rt_powd_snf(ai, absa);
        if ((!rtIsInf(absa)) && (!rtIsNaN(absa))) {
          if (absa == 0.0) {
            ai = 0.0;
          } else {
            ai = fmod(absa, 4.0);
            if (ai == 0.0) {
              ai = 0.0;
            } else {
              if (absa < 0.0) {
                ai += 4.0;
              }
            }
          }
        } else {
          ai = rtNaN;
        }

        ndbl = rt_roundd_snf(ai);
        if (ndbl < 128.0) {
          r = (signed char)ndbl;
        } else {
          r = 0;
        }

        if (r == 3) {
          ndbl = 0.0;
          cdiff = -cdiff;
        } else if (r == 2) {
          ndbl = -cdiff;
          cdiff = 0.0;
        } else if (r == 1) {
          ndbl = 0.0;
        } else {
          ndbl = cdiff;
          cdiff = 0.0;
        }
      } else if ((ai == 0.0) && rtIsInf(absa) && (fabs(ndbl) == 1.0)) {
        ndbl = 1.0;
        cdiff = 0.0;
      } else {
        if (iomega_array->data[nm1d2].im == 0.0) {
          if (iomega_array->data[nm1d2].re < 0.0) {
            ndbl = log(fabs(iomega_array->data[nm1d2].re));
            cdiff = 3.1415926535897931;
          } else {
            ndbl = log(fabs(iomega_array->data[nm1d2].re));
            cdiff = 0.0;
          }
        } else if ((fabs(iomega_array->data[nm1d2].re) > 8.9884656743115785E+307)
                   || (fabs(iomega_array->data[nm1d2].im) >
                       8.9884656743115785E+307)) {
          ndbl = log(rt_hypotd_snf(iomega_array->data[nm1d2].re / 2.0,
                      iomega_array->data[nm1d2].im / 2.0)) + 0.69314718055994529;
          cdiff = rt_atan2d_snf(iomega_array->data[nm1d2].im, iomega_array->
                                data[nm1d2].re);
        } else {
          ndbl = log(rt_hypotd_snf(iomega_array->data[nm1d2].re,
                      iomega_array->data[nm1d2].im));
          cdiff = rt_atan2d_snf(iomega_array->data[nm1d2].im, iomega_array->
                                data[nm1d2].re);
        }

        ndbl *= absa;
        cdiff *= absa;
        if (cdiff == 0.0) {
          ndbl = exp(ndbl);
          cdiff = 0.0;
        } else if (rtIsInf(cdiff) && rtIsInf(ndbl) && (ndbl < 0.0)) {
          ndbl = 0.0;
          cdiff = 0.0;
        } else {
          ai = exp(ndbl / 2.0);
          ndbl = ai * (ai * cos(cdiff));
          cdiff = ai * (ai * sin(cdiff));
        }
      }

      ai = A[nm1d2].re;
      A[nm1d2].re = A[nm1d2].re * ndbl - A[nm1d2].im * cdiff;
      A[nm1d2].im = ai * cdiff + A[nm1d2].im * ndbl;
    } else {
      A[nm1d2].re = 0.0;
      A[nm1d2].im = 0.0;
    }
  }

  emxFree_creal_T(&iomega_array);

  /*    Shift new frequency-amplitude array back to MATLAB format and */
  /*    transform back into the time domain via the inverse FFT. */
  ifftshift(A);

  /*    Remove zeros that were added to datain in order to pad to next */
  /*    biggerst power of 2 and return dataout. */
  ifft(A, dcv0);
  for (nm1d2 = 0; nm1d2 < 512; nm1d2++) {
    dataout[nm1d2] = dcv0[nm1d2].re;
  }
}

/*
 * File trailer for iomega.c
 *
 * [EOF]
 */

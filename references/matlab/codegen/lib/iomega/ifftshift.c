/*
 * File: ifftshift.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:10:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "ifftshift.h"

/* Function Definitions */

/*
 * Arguments    : creal_T x[512]
 *                int dim
 * Return Type  : void
 */
void eml_fftshift(creal_T x[512], int dim)
{
  int i1;
  int vlend2;
  int vstride;
  int k;
  int midoffset;
  int j;
  int ia;
  int ib;
  double xtmp_re;
  double xtmp_im;
  int ic;
  if (dim <= 1) {
    i1 = 512;
  } else {
    i1 = 1;
  }

  if (!(i1 <= 1)) {
    vlend2 = i1 / 2;
    vstride = 1;
    k = 1;
    while (k <= dim - 1) {
      vstride <<= 9;
      k = 2;
    }

    midoffset = vlend2 * vstride;
    if (vlend2 << 1 == i1) {
      i1 = -1;
      for (j = 1; j <= vstride; j++) {
        i1++;
        ia = i1;
        ib = i1 + midoffset;
        for (k = 1; k <= vlend2; k++) {
          xtmp_re = x[ia].re;
          xtmp_im = x[ia].im;
          x[ia] = x[ib];
          x[ib].re = xtmp_re;
          x[ib].im = xtmp_im;
          ia += vstride;
          ib += vstride;
        }
      }
    } else {
      i1 = -1;
      for (j = 1; j <= vstride; j++) {
        i1++;
        ia = i1;
        ib = (i1 + midoffset) + 1;
        xtmp_re = x[ib - 1].re;
        xtmp_im = x[ib - 1].im;
        for (k = 1; k <= vlend2; k++) {
          ic = ib + vstride;
          x[ib - 1] = x[ia];
          x[ia] = x[ic - 1];
          ia += vstride;
          ib = ic;
        }

        x[ib - 1].re = xtmp_re;
        x[ib - 1].im = xtmp_im;
      }
    }
  }
}

/*
 * Arguments    : creal_T x[512]
 * Return Type  : void
 */
void ifftshift(creal_T x[512])
{
  int dim;
  int i2;
  int vlend2;
  int vstride;
  int k;
  int midoffset;
  int i1;
  int j;
  int ia;
  int ib;
  double xtmp_re;
  double xtmp_im;
  int ic;
  for (dim = 0; dim < 2; dim++) {
    if (dim + 1 <= 1) {
      i2 = 512;
    } else {
      i2 = 1;
    }

    if (!(i2 <= 1)) {
      vlend2 = i2 / 2;
      if (vlend2 << 1 == i2) {
        eml_fftshift(x, dim + 1);
      } else {
        vstride = 1;
        k = 1;
        while (k <= dim) {
          vstride <<= 9;
          k = 2;
        }

        midoffset = vlend2 * vstride;
        i1 = -1;
        i2 = (i2 - 1) * vstride - 1;
        for (j = 1; j <= vstride; j++) {
          i1++;
          i2++;
          ia = i1 + midoffset;
          ib = i2;
          xtmp_re = x[i2].re;
          xtmp_im = x[i2].im;
          for (k = 1; k <= vlend2; k++) {
            ia -= vstride;
            ic = ib;
            ib -= vstride;
            x[ic] = x[ia];
            x[ia] = x[ib];
          }

          x[ib].re = xtmp_re;
          x[ib].im = xtmp_im;
        }
      }
    }
  }
}

/*
 * File trailer for ifftshift.c
 *
 * [EOF]
 */

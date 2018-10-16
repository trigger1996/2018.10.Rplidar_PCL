#ifndef MATLAB_MATH_H
#define MATLAB_MATH_H

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#include <float.h>
#endif

#include <stddef.h>

#include "matlab_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
extern void rt_InitInfAndNaN(size_t realSize);
extern boolean_T rtIsInf(real_T value);
extern boolean_T rtIsInfF(real32_T value);
extern boolean_T rtIsNaN(real_T value);
extern boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtGetInf(void);
real32_T rtGetInfF(void);
real_T rtGetMinusInf(void);
real32_T rtGetMinusInfF(void);

real_T rtGetNaN(void);
real32_T rtGetNaNF(void);

void eml_fftshift(creal_T x[512], int dim);
void ifftshift(creal_T x[512]);

void detrend(double x[512]);
void mldivide(const double A[1024], const double B[512], double Y[2]);

double b_sqrt(double x);
void c_sqrt(double *x);

void fft(const double x[512], creal_T y[512]);
void ifft(const creal_T x[512], creal_T y[512]);

void polyfit(const double x[512], const double y[512], double p[3]);
void polyval(const double p[3], const double x[512], double y[512]);

void vander(const double v[512], double A[1536]);


#endif // MATLAB_MATH_H


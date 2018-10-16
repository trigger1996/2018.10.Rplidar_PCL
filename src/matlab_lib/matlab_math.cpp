#include "include/matlab_math.h"
#include "include/x.h"

//
extern double dv0[257];

#define NumBitsPerChar                 8U

/* Function: rtGetInf ==================================================
 * Abstract:
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetInf(void)
{
  real_T inf = 0.0;
  uint16_T one = 1U;
  enum {
    LittleEndian,
    BigEndian
  } machByteOrder = (*((uint8_T *) &one) == 1U) ? LittleEndian : BigEndian;
  switch (machByteOrder) {
   case LittleEndian:
    {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
      break;
    }

   case BigEndian:
    {
      union {
        BigEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
      break;
    }
  }

  return inf;
}

/* Function: rtGetInfF ==================================================
 * Abstract:
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/* Function: rtGetMinusInf ==================================================
 * Abstract:
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetMinusInf(void)
{
  real_T minf = 0.0;
  uint16_T one = 1U;
  enum {
    LittleEndian,
    BigEndian
  } machByteOrder = (*((uint8_T *) &one) == 1U) ? LittleEndian : BigEndian;
  switch (machByteOrder) {
   case LittleEndian:
    {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
      break;
    }

   case BigEndian:
    {
      union {
        BigEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
      break;
    }
  }

  return minf;
}

/* Function: rtGetMinusInfF ==================================================
 * Abstract:
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

/* Function: rt_InitInfAndNaN ==================================================
 * Abstract:
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Function: rtIsInf ==================================================
 * Abstract:
 * Test if value is infinite
 */
boolean_T rtIsInf(real_T value)
{
  return ((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Function: rtIsInfF =================================================
 * Abstract:
 * Test if single-precision value is infinite
 */
boolean_T rtIsInfF(real32_T value)
{
  return(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Function: rtIsNaN ==================================================
 * Abstract:
 * Test if value is not a number
 */
boolean_T rtIsNaN(real_T value)
{

#if defined(_MSC_VER) && (_MSC_VER <= 1200)

  return _isnan(value)? TRUE:FALSE;

#else

  return (value!=value)? 1U:0U;

#endif

}

/* Function: rtIsNaNF =================================================
 * Abstract:
 * Test if single-precision value is not a number
 */
boolean_T rtIsNaNF(real32_T value)
{

#if defined(_MSC_VER) && (_MSC_VER <= 1200)

  return _isnan((real_T)value)? true:false;

#else

  return (value!=value)? 1U:0U;

#endif

}

/* Function: rtGetNaN ==================================================
 * Abstract:
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetNaN(void)
{
  real_T nan = 0.0;
  uint16_T one = 1U;
  enum {
    LittleEndian,
    BigEndian
  } machByteOrder = (*((uint8_T *) &one) == 1U) ? LittleEndian : BigEndian;
  switch (machByteOrder) {
   case LittleEndian:
    {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      nan = tmpVal.fltVal;
      break;
    }

   case BigEndian:
    {
      union {
        BigEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FFFFFFFU;
      tmpVal.bitVal.words.wordL = 0xFFFFFFFFU;
      nan = tmpVal.fltVal;
      break;
    }
  }

  return nan;
}

/* Function: rtGetNaNF ==================================================
 * Abstract:
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0 } };

  uint16_T one = 1U;
  enum {
    LittleEndian,
    BigEndian
  } machByteOrder = (*((uint8_T *) &one) == 1U) ? LittleEndian : BigEndian;
  switch (machByteOrder) {
   case LittleEndian:
    {
      nanF.wordL.wordLuint = 0xFFC00000U;
      break;
    }

   case BigEndian:
    {
      nanF.wordL.wordLuint = 0x7FFFFFFFU;
      break;
    }
  }

  return nanF.wordL.wordLreal;
}


double b_sqrt(double x)
{
  double b_x;
  b_x = x;
  c_sqrt(&b_x);
  return b_x;
}

/*
 * Arguments    : double *x
 * Return Type  : void
 */
void c_sqrt(double *x)
{
  *x = sqrt(*x);
}

/*
 * Arguments    : double x[512]
 * Return Type  : void
 */
void detrend(double x[512])
{
  int i;
  double a[1024];
  double b[2];
  double d2;
  int i3;
  for (i = 0; i < 512; i++) {
    a[i] = ((double)i + 1.0) / 512.0;
    a[512 + i] = 1.0;
  }

  mldivide(a, x, b);
  for (i = 0; i < 512; i++) {
    d2 = 0.0;
    for (i3 = 0; i3 < 2; i3++) {
      d2 += a[i + (i3 << 9)] * b[i3];
    }

    x[i] -= d2;
  }
}

/*
 * Arguments    : const double A[1024]
 *                const double B[512]
 *                double Y[2]
 * Return Type  : void
 */
void mldivide(const double A[1024], const double B[512], double Y[2])
{
  double b_A[1024];
  double tau[2];
  int jpvt[2];
  int rankA;
  double b_B[512];
  int j;
  int i;
  double wj;
  memcpy(&b_A[0], &A[0], sizeof(double) << 10);
  xgeqp3(b_A, tau, jpvt);
  rankA = rankFromQR(b_A);
  memcpy(&b_B[0], &B[0], sizeof(double) << 9);
  for (j = 0; j < 2; j++) {
    Y[j] = 0.0;
    if (tau[j] != 0.0) {
      wj = b_B[j];
      for (i = j + 1; i + 1 < 513; i++) {
        wj += b_A[i + (j << 9)] * b_B[i];
      }

      wj *= tau[j];
      if (wj != 0.0) {
        b_B[j] -= wj;
        for (i = j + 1; i + 1 < 513; i++) {
          b_B[i] -= b_A[i + (j << 9)] * wj;
        }
      }
    }
  }

  for (i = 0; i + 1 <= rankA; i++) {
    Y[jpvt[i] - 1] = b_B[i];
  }

  for (j = rankA - 1; j + 1 > 0; j--) {
    Y[jpvt[j] - 1] /= b_A[j + (j << 9)];
    i = 1;
    while (i <= j) {
      Y[jpvt[0] - 1] -= Y[jpvt[j] - 1] * b_A[j << 9];
      i = 2;
    }
  }
}

/*
 * Arguments    : const double x[512]
 *                creal_T y[512]
 * Return Type  : void
 */
void fft(const double x[512], creal_T y[512])
{
  int ix;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  int iheight;
  int istart;
  int j;
  double twid_re;
  double twid_im;
  static const double dv6[257] = { 0.0, -0.012271538285719925,
    -0.024541228522912288, -0.036807222941358832, -0.049067674327418015,
    -0.061320736302208578, -0.073564563599667426, -0.0857973123444399,
    -0.0980171403295606, -0.11022220729388306, -0.1224106751992162,
    -0.13458070850712617, -0.14673047445536175, -0.15885814333386145,
    -0.17096188876030122, -0.18303988795514095, -0.19509032201612825,
    -0.20711137619221856, -0.2191012401568698, -0.23105810828067111,
    -0.24298017990326387, -0.25486565960451457, -0.26671275747489837,
    -0.27851968938505306, -0.29028467725446233, -0.30200594931922808,
    -0.31368174039889152, -0.32531029216226293, -0.33688985339222005,
    -0.34841868024943456, -0.35989503653498811, -0.37131719395183749,
    -0.38268343236508978, -0.3939920400610481, -0.40524131400498986,
    -0.41642956009763715, -0.42755509343028208, -0.43861623853852766,
    -0.44961132965460654, -0.46053871095824, -0.47139673682599764,
    -0.48218377207912272, -0.49289819222978404, -0.50353838372571758,
    -0.51410274419322166, -0.524589682678469, -0.53499761988709715,
    -0.54532498842204646, -0.55557023301960218, -0.56573181078361312,
    -0.57580819141784534, -0.58579785745643886, -0.59569930449243336,
    -0.60551104140432555, -0.61523159058062682, -0.62485948814238634,
    -0.63439328416364549, -0.64383154288979139, -0.65317284295377676,
    -0.66241577759017178, -0.67155895484701833, -0.680600997795453,
    -0.68954054473706683, -0.69837624940897292, -0.70710678118654757,
    -0.71573082528381859, -0.724247082951467, -0.73265427167241282,
    -0.74095112535495922, -0.74913639452345937, -0.75720884650648457,
    -0.765167265622459, -0.773010453362737, -0.78073722857209449,
    -0.78834642762660634, -0.79583690460888357, -0.80320753148064494,
    -0.81045719825259477, -0.81758481315158371, -0.82458930278502529,
    -0.83146961230254524, -0.83822470555483808, -0.84485356524970712,
    -0.8513551931052652, -0.85772861000027212, -0.8639728561215867,
    -0.87008699110871146, -0.8760700941954066, -0.881921264348355,
    -0.88763962040285393, -0.89322430119551532, -0.89867446569395382,
    -0.90398929312344334, -0.90916798309052238, -0.91420975570353069,
    -0.91911385169005777, -0.92387953251128674, -0.92850608047321559,
    -0.932992798834739, -0.937339011912575, -0.94154406518302081,
    -0.94560732538052128, -0.94952818059303667, -0.95330604035419386,
    -0.95694033573220882, -0.96043051941556579, -0.96377606579543984,
    -0.96697647104485207, -0.970031253194544, -0.97293995220556018,
    -0.97570213003852857, -0.97831737071962765, -0.98078528040323043,
    -0.98310548743121629, -0.98527764238894122, -0.98730141815785843,
    -0.989176509964781, -0.99090263542778, -0.99247953459871,
    -0.99390697000235606, -0.99518472667219693, -0.996312612182778,
    -0.99729045667869021, -0.99811811290014918, -0.99879545620517241,
    -0.99932238458834954, -0.99969881869620425, -0.9999247018391445, -1.0,
    -0.9999247018391445, -0.99969881869620425, -0.99932238458834954,
    -0.99879545620517241, -0.99811811290014918, -0.99729045667869021,
    -0.996312612182778, -0.99518472667219693, -0.99390697000235606,
    -0.99247953459871, -0.99090263542778, -0.989176509964781,
    -0.98730141815785843, -0.98527764238894122, -0.98310548743121629,
    -0.98078528040323043, -0.97831737071962765, -0.97570213003852857,
    -0.97293995220556018, -0.970031253194544, -0.96697647104485207,
    -0.96377606579543984, -0.96043051941556579, -0.95694033573220882,
    -0.95330604035419386, -0.94952818059303667, -0.94560732538052128,
    -0.94154406518302081, -0.937339011912575, -0.932992798834739,
    -0.92850608047321559, -0.92387953251128674, -0.91911385169005777,
    -0.91420975570353069, -0.90916798309052238, -0.90398929312344334,
    -0.89867446569395382, -0.89322430119551532, -0.88763962040285393,
    -0.881921264348355, -0.8760700941954066, -0.87008699110871146,
    -0.8639728561215867, -0.85772861000027212, -0.8513551931052652,
    -0.84485356524970712, -0.83822470555483808, -0.83146961230254524,
    -0.82458930278502529, -0.81758481315158371, -0.81045719825259477,
    -0.80320753148064494, -0.79583690460888357, -0.78834642762660634,
    -0.78073722857209449, -0.773010453362737, -0.765167265622459,
    -0.75720884650648457, -0.74913639452345937, -0.74095112535495922,
    -0.73265427167241282, -0.724247082951467, -0.71573082528381859,
    -0.70710678118654757, -0.69837624940897292, -0.68954054473706683,
    -0.680600997795453, -0.67155895484701833, -0.66241577759017178,
    -0.65317284295377676, -0.64383154288979139, -0.63439328416364549,
    -0.62485948814238634, -0.61523159058062682, -0.60551104140432555,
    -0.59569930449243336, -0.58579785745643886, -0.57580819141784534,
    -0.56573181078361312, -0.55557023301960218, -0.54532498842204646,
    -0.53499761988709715, -0.524589682678469, -0.51410274419322166,
    -0.50353838372571758, -0.49289819222978404, -0.48218377207912272,
    -0.47139673682599764, -0.46053871095824, -0.44961132965460654,
    -0.43861623853852766, -0.42755509343028208, -0.41642956009763715,
    -0.40524131400498986, -0.3939920400610481, -0.38268343236508978,
    -0.37131719395183749, -0.35989503653498811, -0.34841868024943456,
    -0.33688985339222005, -0.32531029216226293, -0.31368174039889152,
    -0.30200594931922808, -0.29028467725446233, -0.27851968938505306,
    -0.26671275747489837, -0.25486565960451457, -0.24298017990326387,
    -0.23105810828067111, -0.2191012401568698, -0.20711137619221856,
    -0.19509032201612825, -0.18303988795514095, -0.17096188876030122,
    -0.15885814333386145, -0.14673047445536175, -0.13458070850712617,
    -0.1224106751992162, -0.11022220729388306, -0.0980171403295606,
    -0.0857973123444399, -0.073564563599667426, -0.061320736302208578,
    -0.049067674327418015, -0.036807222941358832, -0.024541228522912288,
    -0.012271538285719925, -0.0 };

  int ihi;
  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 511; i++) {
    y[iy].re = x[ix];
    y[iy].im = 0.0;
    iy = 512;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy].re = x[ix];
  y[iy].im = 0.0;
  for (i = 0; i <= 511; i += 2) {
    temp_re = y[i + 1].re;
    temp_im = y[i + 1].im;
    y[i + 1].re = y[i].re - y[i + 1].re;
    y[i + 1].im = y[i].im - y[i + 1].im;
    y[i].re += temp_re;
    y[i].im += temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 128;
  iheight = 509;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re = y[i + iy].re;
      temp_im = y[i + iy].im;
      y[i + iy].re = y[i].re - temp_re;
      y[i + iy].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 256; j += ju) {
      twid_re = dv0[j];
      twid_im = dv6[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re = twid_re * y[i + iy].re - twid_im * y[i + iy].im;
        temp_im = twid_re * y[i + iy].im + twid_im * y[i + iy].re;
        y[i + iy].re = y[i].re - temp_re;
        y[i + iy].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }
}

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
 * Arguments    : const creal_T x[512]
 *                creal_T y[512]
 * Return Type  : void
 */
void ifft(const creal_T x[512], creal_T y[512])
{
  int ix;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  int iheight;
  int istart;
  int j;
  double twid_re;
  double twid_im;
  static const double dv7[257] = { 0.0, 0.012271538285719925,
    0.024541228522912288, 0.036807222941358832, 0.049067674327418015,
    0.061320736302208578, 0.073564563599667426, 0.0857973123444399,
    0.0980171403295606, 0.11022220729388306, 0.1224106751992162,
    0.13458070850712617, 0.14673047445536175, 0.15885814333386145,
    0.17096188876030122, 0.18303988795514095, 0.19509032201612825,
    0.20711137619221856, 0.2191012401568698, 0.23105810828067111,
    0.24298017990326387, 0.25486565960451457, 0.26671275747489837,
    0.27851968938505306, 0.29028467725446233, 0.30200594931922808,
    0.31368174039889152, 0.32531029216226293, 0.33688985339222005,
    0.34841868024943456, 0.35989503653498811, 0.37131719395183749,
    0.38268343236508978, 0.3939920400610481, 0.40524131400498986,
    0.41642956009763715, 0.42755509343028208, 0.43861623853852766,
    0.44961132965460654, 0.46053871095824, 0.47139673682599764,
    0.48218377207912272, 0.49289819222978404, 0.50353838372571758,
    0.51410274419322166, 0.524589682678469, 0.53499761988709715,
    0.54532498842204646, 0.55557023301960218, 0.56573181078361312,
    0.57580819141784534, 0.58579785745643886, 0.59569930449243336,
    0.60551104140432555, 0.61523159058062682, 0.62485948814238634,
    0.63439328416364549, 0.64383154288979139, 0.65317284295377676,
    0.66241577759017178, 0.67155895484701833, 0.680600997795453,
    0.68954054473706683, 0.69837624940897292, 0.70710678118654757,
    0.71573082528381859, 0.724247082951467, 0.73265427167241282,
    0.74095112535495922, 0.74913639452345937, 0.75720884650648457,
    0.765167265622459, 0.773010453362737, 0.78073722857209449,
    0.78834642762660634, 0.79583690460888357, 0.80320753148064494,
    0.81045719825259477, 0.81758481315158371, 0.82458930278502529,
    0.83146961230254524, 0.83822470555483808, 0.84485356524970712,
    0.8513551931052652, 0.85772861000027212, 0.8639728561215867,
    0.87008699110871146, 0.8760700941954066, 0.881921264348355,
    0.88763962040285393, 0.89322430119551532, 0.89867446569395382,
    0.90398929312344334, 0.90916798309052238, 0.91420975570353069,
    0.91911385169005777, 0.92387953251128674, 0.92850608047321559,
    0.932992798834739, 0.937339011912575, 0.94154406518302081,
    0.94560732538052128, 0.94952818059303667, 0.95330604035419386,
    0.95694033573220882, 0.96043051941556579, 0.96377606579543984,
    0.96697647104485207, 0.970031253194544, 0.97293995220556018,
    0.97570213003852857, 0.97831737071962765, 0.98078528040323043,
    0.98310548743121629, 0.98527764238894122, 0.98730141815785843,
    0.989176509964781, 0.99090263542778, 0.99247953459871, 0.99390697000235606,
    0.99518472667219693, 0.996312612182778, 0.99729045667869021,
    0.99811811290014918, 0.99879545620517241, 0.99932238458834954,
    0.99969881869620425, 0.9999247018391445, 1.0, 0.9999247018391445,
    0.99969881869620425, 0.99932238458834954, 0.99879545620517241,
    0.99811811290014918, 0.99729045667869021, 0.996312612182778,
    0.99518472667219693, 0.99390697000235606, 0.99247953459871, 0.99090263542778,
    0.989176509964781, 0.98730141815785843, 0.98527764238894122,
    0.98310548743121629, 0.98078528040323043, 0.97831737071962765,
    0.97570213003852857, 0.97293995220556018, 0.970031253194544,
    0.96697647104485207, 0.96377606579543984, 0.96043051941556579,
    0.95694033573220882, 0.95330604035419386, 0.94952818059303667,
    0.94560732538052128, 0.94154406518302081, 0.937339011912575,
    0.932992798834739, 0.92850608047321559, 0.92387953251128674,
    0.91911385169005777, 0.91420975570353069, 0.90916798309052238,
    0.90398929312344334, 0.89867446569395382, 0.89322430119551532,
    0.88763962040285393, 0.881921264348355, 0.8760700941954066,
    0.87008699110871146, 0.8639728561215867, 0.85772861000027212,
    0.8513551931052652, 0.84485356524970712, 0.83822470555483808,
    0.83146961230254524, 0.82458930278502529, 0.81758481315158371,
    0.81045719825259477, 0.80320753148064494, 0.79583690460888357,
    0.78834642762660634, 0.78073722857209449, 0.773010453362737,
    0.765167265622459, 0.75720884650648457, 0.74913639452345937,
    0.74095112535495922, 0.73265427167241282, 0.724247082951467,
    0.71573082528381859, 0.70710678118654757, 0.69837624940897292,
    0.68954054473706683, 0.680600997795453, 0.67155895484701833,
    0.66241577759017178, 0.65317284295377676, 0.64383154288979139,
    0.63439328416364549, 0.62485948814238634, 0.61523159058062682,
    0.60551104140432555, 0.59569930449243336, 0.58579785745643886,
    0.57580819141784534, 0.56573181078361312, 0.55557023301960218,
    0.54532498842204646, 0.53499761988709715, 0.524589682678469,
    0.51410274419322166, 0.50353838372571758, 0.49289819222978404,
    0.48218377207912272, 0.47139673682599764, 0.46053871095824,
    0.44961132965460654, 0.43861623853852766, 0.42755509343028208,
    0.41642956009763715, 0.40524131400498986, 0.3939920400610481,
    0.38268343236508978, 0.37131719395183749, 0.35989503653498811,
    0.34841868024943456, 0.33688985339222005, 0.32531029216226293,
    0.31368174039889152, 0.30200594931922808, 0.29028467725446233,
    0.27851968938505306, 0.26671275747489837, 0.25486565960451457,
    0.24298017990326387, 0.23105810828067111, 0.2191012401568698,
    0.20711137619221856, 0.19509032201612825, 0.18303988795514095,
    0.17096188876030122, 0.15885814333386145, 0.14673047445536175,
    0.13458070850712617, 0.1224106751992162, 0.11022220729388306,
    0.0980171403295606, 0.0857973123444399, 0.073564563599667426,
    0.061320736302208578, 0.049067674327418015, 0.036807222941358832,
    0.024541228522912288, 0.012271538285719925, 0.0 };

  int ihi;
  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 511; i++) {
    y[iy] = x[ix];
    iy = 512;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  for (i = 0; i <= 511; i += 2) {
    temp_re = y[i + 1].re;
    temp_im = y[i + 1].im;
    y[i + 1].re = y[i].re - y[i + 1].re;
    y[i + 1].im = y[i].im - y[i + 1].im;
    y[i].re += temp_re;
    y[i].im += temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 128;
  iheight = 509;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re = y[i + iy].re;
      temp_im = y[i + iy].im;
      y[i + iy].re = y[i].re - temp_re;
      y[i + iy].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 256; j += ju) {
      twid_re = dv0[j];
      twid_im = dv7[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re = twid_re * y[i + iy].re - twid_im * y[i + iy].im;
        temp_im = twid_re * y[i + iy].im + twid_im * y[i + iy].re;
        y[i + iy].re = y[i].re - temp_re;
        y[i + iy].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }

  for (iy = 0; iy < 512; iy++) {
    y[iy].re *= 0.001953125;
    y[iy].im *= 0.001953125;
  }
}

/*
 * Arguments    : const double x[512]
 *                const double y[512]
 *                double p[3]
 * Return Type  : void
 */
void polyfit(const double x[512], const double y[512], double p[3])
{
  double dv8[1536];
  int rr;
  vander(x, dv8);
  qrsolve(dv8, y, p, &rr);
}

/*
 * Arguments    : const double p[3]
 *                const double x[512]
 *                double y[512]
 * Return Type  : void
 */
void polyval(const double p[3], const double x[512], double y[512])
{
  int i2;
  int k;
  for (i2 = 0; i2 < 512; i2++) {
    y[i2] = p[0];
  }

  for (k = 0; k < 2; k++) {
    for (i2 = 0; i2 < 512; i2++) {
      y[i2] = x[i2] * y[i2] + p[k + 1];
    }
  }
}

/*
 * Arguments    : const double v[512]
 *                double A[1536]
 * Return Type  : void
 */
void vander(const double v[512], double A[1536])
{
  int k;
  for (k = 0; k < 512; k++) {
    A[1024 + k] = 1.0;
    A[512 + k] = v[k];
    A[k] = v[k] * A[512 + k];
  }
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */

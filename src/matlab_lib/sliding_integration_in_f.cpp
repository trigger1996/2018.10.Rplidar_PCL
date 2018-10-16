/*
 * File: sliding_integrate_f.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 15:40:47
 */

/* Include Files */
#include "include/sliding_integration_in_f.h"
#include "include/inte_util.h"

double arr_len;
double acc_x_arr[512];
double acc_y_arr[512];
double vel_x_arr[512];
double vel_y_arr[512];
double t[512];
const double dv0[257] = { 1.0, 0.9999247018391445, 0.99969881869620425,
  0.99932238458834954, 0.99879545620517241, 0.99811811290014918,
  0.99729045667869021, 0.996312612182778, 0.99518472667219693,
  0.99390697000235606, 0.99247953459871, 0.99090263542778, 0.989176509964781,
  0.98730141815785843, 0.98527764238894122, 0.98310548743121629,
  0.98078528040323043, 0.97831737071962765, 0.97570213003852857,
  0.97293995220556018, 0.970031253194544, 0.96697647104485207,
  0.96377606579543984, 0.96043051941556579, 0.95694033573220882,
  0.95330604035419386, 0.94952818059303667, 0.94560732538052128,
  0.94154406518302081, 0.937339011912575, 0.932992798834739, 0.92850608047321559,
  0.92387953251128674, 0.91911385169005777, 0.91420975570353069,
  0.90916798309052238, 0.90398929312344334, 0.89867446569395382,
  0.89322430119551532, 0.88763962040285393, 0.881921264348355,
  0.8760700941954066, 0.87008699110871146, 0.8639728561215867,
  0.85772861000027212, 0.8513551931052652, 0.84485356524970712,
  0.83822470555483808, 0.83146961230254524, 0.82458930278502529,
  0.81758481315158371, 0.81045719825259477, 0.80320753148064494,
  0.79583690460888357, 0.78834642762660634, 0.78073722857209449,
  0.773010453362737, 0.765167265622459, 0.75720884650648457, 0.74913639452345937,
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
  0.024541228522912288, 0.012271538285719925, 0.0, -0.012271538285719925,
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
  -0.989176509964781, -0.99090263542778, -0.99247953459871, -0.99390697000235606,
  -0.99518472667219693, -0.996312612182778, -0.99729045667869021,
  -0.99811811290014918, -0.99879545620517241, -0.99932238458834954,
  -0.99969881869620425, -0.9999247018391445, -1.0 };


void b_iomega(const double datain[512], double dt, double dataout[512]);
void iomega(const double datain[512], double dt, double datain_type,
                   double dataout_type, double dataout[512]);


static double rt_atan2d_snf(double u0, double u1);
static double rt_powd_snf(double u0, double u1);
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * 核心思想：
 *  记录加速度序列，每次以滑动的方式添加一个加速度进来，积分得到速度，这样就可以利用频域，又能单数据更新
 *  但是这样速度和位移的积分结果就只和加速度序列有关，而与全局状态无关，这显然是错的——比如如果停止运动，过一段时间加速度会很小，然后速度和位移也会趋于0
 *  所以需要让这些参数都和全局有关起来
 *  所以同样地记录速度即可
 * Arguments    : double ax_in
 *                double ay_in
 *                double ts
 *                double arr_len_in
 *                double *dst_x
 *                double *dst_y
 *                double *vel_x
 *                double *vel_y
 * Return Type  : void
 */
void sliding_integrate_f(double ax_in, double ay_in, double ts, double
  arr_len_in, double *dst_x, double *dst_y, double *vel_x, double *vel_y)
{
  int idx;
  int i;
  boolean_T exitg1;
  int loop_ub;
  int ii_data[512];
  int i_data[512];
  int mtmp;
  int i0;
  double vel_x_int[512];
  double vel_y_int[512];
  double px[3];
  int i1;
  double dis_y_int[512];
  (void)arr_len_in;

  /*  persistent */
  /*  if size(arr_len_in, 1) == 0 */
  /*      arr_len = [];                                       % 预留用来复位的，只要arr_len_in输入等于[]，就复位 */
  /*      vel_x_arr = []; vel_y_arr = [];                     % 编译的时候记得注释掉这个，用不上，还会造成编译错误 */
  /*      acc_x_arr = []; acc_y_arr = []; */
  /*      t         = []; */
  /*      dst_x = 0;      dst_y = 0; */
  /*      vel_x = 0;      vel_y = 0; */
  /*      return; */
  /*  end */
  /*  如果数据不满，则不进行运算 */
  if ((acc_x_arr[511] == 0.0) || (acc_y_arr[511] == 0.0)) {
    idx = 0;
    i = 1;
    exitg1 = false;
    while ((!exitg1) && (i < 513)) {
      if (acc_x_arr[i - 1] == 0.0) {
        idx++;
        ii_data[idx - 1] = i;
        if (idx >= 512) {
          exitg1 = true;
        } else {
          i++;
        }
      } else {
        i++;
      }
    }

    if (1 > idx) {
      loop_ub = 0;
    } else {
      loop_ub = idx;
    }

    if (0 <= loop_ub - 1) {
      memcpy(&i_data[0], &ii_data[0], (unsigned int)(loop_ub * (int)sizeof(int)));
    }

    mtmp = i_data[0];
    if (1 > idx) {
      i0 = 0;
    } else {
      i0 = idx;
    }

    if (i0 > 1) {
      for (i = 1; i + 1 <= loop_ub; i++) {
        if (i_data[i] < mtmp) {
          mtmp = i_data[i];
        }
      }
    }

    acc_x_arr[mtmp - 1] = ax_in;

    /*  找到最后一个0（未填满）的位置插入数据 */
    idx = 0;
    i = 1;
    exitg1 = false;
    while ((!exitg1) && (i < 513)) {
      if (acc_y_arr[i - 1] == 0.0) {
        idx++;
        ii_data[idx - 1] = i;
        if (idx >= 512) {
          exitg1 = true;
        } else {
          i++;
        }
      } else {
        i++;
      }
    }

    if (1 > idx) {
      loop_ub = 0;
    } else {
      loop_ub = idx;
    }

    if (0 <= loop_ub - 1) {
      memcpy(&i_data[0], &ii_data[0], (unsigned int)(loop_ub * (int)sizeof(int)));
    }

    mtmp = i_data[0];
    if (1 > idx) {
      i1 = 0;
    } else {
      i1 = idx;
    }

    if (i1 > 1) {
      for (i = 1; i + 1 <= loop_ub; i++) {
        if (i_data[i] < mtmp) {
          mtmp = i_data[i];
        }
      }
    }

    acc_y_arr[mtmp - 1] = ay_in;
    *dst_x = 0.0;
    *dst_y = 0.0;
    *vel_x = 0.0;
    *vel_y = 0.0;
  } else {
    /*  正常计算 */
    /*  将数据滑动前移一位 */
    for (i = 0; i < (int)(arr_len - 1.0); i++) {
      acc_x_arr[i] = acc_x_arr[(int)((1.0 + (double)i) + 1.0) - 1];
      acc_y_arr[i] = acc_y_arr[(int)((1.0 + (double)i) + 1.0) - 1];
    }

    /*  最后一位插入新的数据 */
    acc_x_arr[(int)arr_len - 1] = ax_in;
    acc_y_arr[(int)arr_len - 1] = ay_in;

    /*  如果vel序列没有填满则记录vel序列后退出 */
    /*  此时加速度已经能计算，那么先根据加速度序列算出速度序列，然后推出 */
    if ((vel_x_arr[511] == 0.0) || (vel_y_arr[511] == 0.0)) {
      b_iomega(acc_x_arr, ts, vel_x_arr);
      b_iomega(acc_y_arr, ts, vel_y_arr);
      *dst_x = 0.0;
      *dst_y = 0.0;
      *vel_x = 0.0;
      *vel_y = 0.0;
    } else {
      /*  积分 */
      /*  频域积分 */
      /*  速度 */
      b_iomega(acc_x_arr, ts, vel_x_int);
      detrend(vel_x_int);
      b_iomega(acc_y_arr, ts, vel_y_int);
      detrend(vel_y_int);

      /*  将数据滑动前移一位 */
      for (i = 0; i < (int)(arr_len - 1.0); i++) {
        vel_x_arr[i] = vel_x_arr[(int)((1.0 + (double)i) + 1.0) - 1];
        vel_y_arr[i] = vel_y_arr[(int)((1.0 + (double)i) + 1.0) - 1];
      }

      /*  最后一位插入新的数据 */
      vel_x_arr[(int)arr_len - 1] = vel_x_int[511];
      vel_y_arr[(int)arr_len - 1] = vel_y_int[511];

      /* disint =  iomega(acc_arr, ts, 3, 1); */
      b_iomega(vel_x_arr, ts, vel_x_int);

      /*  去除位移中的二次项 */
      polyfit(t, vel_x_int, px);
      polyval(px, t, vel_y_int);
      for (i = 0; i < 512; i++) {
        vel_x_int[i] -= vel_y_int[i];
      }

      /* disint =  iomega(acc_arr, ts, 3, 1); */
      b_iomega(vel_y_arr, ts, dis_y_int);

      /*  去除位移中的二次项 */
      polyfit(t, dis_y_int, px);
      polyval(px, t, vel_y_int);
      for (i = 0; i < 512; i++) {
        dis_y_int[i] -= vel_y_int[i];
      }

      *dst_x = vel_x_int[(int)arr_len - 1];
      *dst_y = dis_y_int[(int)arr_len - 1];
      *vel_x = vel_x_arr[(int)arr_len - 1];
      *vel_y = vel_y_arr[(int)arr_len - 1];
    }
  }
}


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
 * File trailer for sliding_integrate_f.c
 *
 * [EOF]
 */

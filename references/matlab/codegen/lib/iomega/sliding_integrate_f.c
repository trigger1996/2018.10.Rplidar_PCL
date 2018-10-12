/*
 * File: sliding_integrate_f.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 14:10:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "polyval.h"
#include "polyfit.h"
#include "detrend.h"
#include "iomega_data.h"

/* Function Definitions */

/*
 * 核心思想：
 *  记录加速度序列，每次以滑动的方式添加一个加速度进来，积分得到速度，这样就可以利用频域，又能单数据更新
 *  但是这样速度和位移的积分结果就只和加速度序列有关，而与全局状态无关，这显然是错的——比如如果停止运动，过一段时间加速度会很小，然后速度和位移也会趋于0
 *  所以需要让这些参数都和全局有关起来
 *  所以同样地记录速度即可
 * Arguments    : double data_in
 *                double ts
 *                double arr_len_in
 *                double *dst
 *                double *vel
 * Return Type  : void
 */
void sliding_integrate_f(double data_in, double ts, double arr_len_in, double
  *dst, double *vel)
{
  int idx;
  int i;
  boolean_T exitg1;
  int loop_ub;
  int ii_data[512];
  int i_data[512];
  int mtmp;
  int i0;
  double velint[512];
  double p[3];
  double dv6[512];
  (void)arr_len_in;

  /*  persistent */
  /*  if size(arr_len_in, 1) == 0 */
  /*      arr_len = [];                   % 预留用来复位的，只要arr_len_in输入等于[]，就复位 */
  /*      vel_arr = []; */
  /*      acc_arr = []; */
  /*      t       = []; */
  /*      dst = 0; */
  /*      vel = 0; */
  /*      return; */
  /*  end */
  /*  如果数据不满，则不进行运算 */
  if (acc_arr[511] == 0.0) {
    idx = 0;
    i = 1;
    exitg1 = false;
    while ((!exitg1) && (i < 513)) {
      if (acc_arr[i - 1] == 0.0) {
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

    acc_arr[mtmp - 1] = data_in;

    /*  找到最后一个0（未填满）的位置插入数据 */
    *dst = 0.0;
    *vel = 0.0;
  } else {
    /*  正常计算 */
    /*  将数据滑动前移一位 */
    for (i = 0; i < (int)(arr_len - 1.0); i++) {
      acc_arr[i] = acc_arr[(int)((1.0 + (double)i) + 1.0) - 1];
    }

    /*  最后一位插入新的数据 */
    acc_arr[(int)arr_len - 1] = data_in;

    /*  如果vel序列没有填满则记录vel序列后退出 */
    /*  此时加速度已经能计算，那么先根据加速度序列算出速度序列，然后推出 */
    if (vel_arr[511] == 0.0) {
      b_iomega(acc_arr, ts, vel_arr);
      *dst = 0.0;
      *vel = 0.0;
    } else {
      /*  积分 */
      /*  频域积分 */
      /*  速度 */
      b_iomega(acc_arr, ts, velint);
      detrend(velint);

      /*  将数据滑动前移一位 */
      for (i = 0; i < (int)(arr_len - 1.0); i++) {
        vel_arr[i] = vel_arr[(int)((1.0 + (double)i) + 1.0) - 1];
      }

      /*  最后一位插入新的数据 */
      vel_arr[(int)arr_len - 1] = velint[511];

      /* disint =  iomega(acc_arr, ts, 3, 1); */
      b_iomega(vel_arr, ts, velint);

      /*  去除位移中的二次项 */
      polyfit(t, velint, p);
      polyval(p, t, dv6);
      for (i = 0; i < 512; i++) {
        velint[i] -= dv6[i];
      }

      *vel = vel_arr[(int)arr_len - 1];
      *dst = velint[(int)arr_len - 1];
    }
  }
}

/*
 * File trailer for sliding_integrate_f.c
 *
 * [EOF]
 */

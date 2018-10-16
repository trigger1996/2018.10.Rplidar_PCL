/*
 * File: main.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Oct-2018 15:40:47
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "iomega.h"
#include "sliding_integrate_f.h"
#include "main.h"
#include "iomega_terminate.h"
#include "iomega_initialize.h"

/* Function Declarations */
static void argInit_512x1_real_T(double result[512]);
static double argInit_real_T(void);
static void main_iomega(void);
static void main_sliding_integrate_f(void);

/* Function Definitions */

/*
 * Arguments    : double result[512]
 * Return Type  : void
 */
static void argInit_512x1_real_T(double result[512])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 512; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_iomega(void)
{
  double dv9[512];
  double dataout[512];

  /* Initialize function 'iomega' input arguments. */
  /* Initialize function input argument 'datain'. */
  /* Call the entry-point 'iomega'. */
  argInit_512x1_real_T(dv9);
  iomega(dv9, argInit_real_T(), argInit_real_T(), argInit_real_T(), dataout);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_sliding_integrate_f(void)
{
  double dst_x;
  double dst_y;
  double vel_x;
  double vel_y;

  /* Initialize function 'sliding_integrate_f' input arguments. */
  /* Call the entry-point 'sliding_integrate_f'. */
  sliding_integrate_f(argInit_real_T(), argInit_real_T(), argInit_real_T(),
                      argInit_real_T(), &dst_x, &dst_y, &vel_x, &vel_y);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  iomega_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_iomega();
  main_sliding_integrate_f();

  /* Terminate the application.
     You do not need to do this more than one time. */
  iomega_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
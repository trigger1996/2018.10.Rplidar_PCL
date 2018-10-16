#ifndef EMXUTIL_H
#define EMXUTIL_H

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_creal_T
#define struct_emxArray_creal_T

struct emxArray_creal_T
{
  creal_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_creal_T*/

#ifndef typedef_emxArray_creal_T
#define typedef_emxArray_creal_T

typedef struct emxArray_creal_T emxArray_creal_T;

#endif                                 /*typedef_emxArray_creal_T*/

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

void emxEnsureCapacity_creal_T(emxArray_creal_T *emxArray, int oldNumel);
void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
void emxFree_creal_T(emxArray_creal_T **pEmxArray);
void emxFree_real_T(emxArray_real_T **pEmxArray);
void emxInit_creal_T(emxArray_creal_T **pEmxArray, int b_numDimensions);
void emxInit_real_T(emxArray_real_T **pEmxArray, int b_numDimensions);

double rt_hypotd_snf(double u0, double u1);

#endif // EMXUTIL_H


/*
 * matlab_cubic_spline_emxAPI.h
 *
 * Code generation for function 'matlab_cubic_spline_emxAPI'
 *
 */

#ifndef MATLAB_CUBIC_SPLINE_EMXAPI_H
#define MATLAB_CUBIC_SPLINE_EMXAPI_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "matlab_cubic_spline_types.h"

/* Function Declarations */
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
  numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (matlab_cubic_spline_emxAPI.h) */

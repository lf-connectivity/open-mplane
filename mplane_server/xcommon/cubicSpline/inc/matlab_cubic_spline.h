/*
 * matlab_cubic_spline.h
 *
 * Code generation for function 'matlab_cubic_spline'
 *
 */

#ifndef MATLAB_CUBIC_SPLINE_H
#define MATLAB_CUBIC_SPLINE_H

/* Include files */
#include "matlab_cubic_spline_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

/* Function Declarations */
extern void matlab_cubic_spline(
    const emxArray_real_T* x,
    const emxArray_real_T* y,
    const emxArray_real_T* xx,
    emxArray_real_T* yy);

#endif

/* End of code generation (matlab_cubic_spline.h) */

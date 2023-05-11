/*
 * spline.h
 *
 * Code generation for function 'spline'
 *
 */

#ifndef SPLINE_H
#define SPLINE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "matlab_cubic_spline_types.h"

/* Function Declarations */
extern void splinepp(const emxArray_real_T *x, const emxArray_real_T *y,
                     emxArray_real_T *pp_breaks, emxArray_real_T *pp_coefs);

#endif

/* End of code generation (spline.h) */

/*
 * rt_nonfinite.h
 *
 * Code generation for function 'matlab_cubic_spline'
 *
 */

#ifndef RT_NONFINITE_H
#define RT_NONFINITE_H
#include "rtwtypes.h"
#include <stddef.h>

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

#endif

/* End of code generation (rt_nonfinite.h) */

/*
 * matlab_cubic_spline.cpp
 *
 * Code generation for function 'matlab_cubic_spline'
 *
 */

/* Include files */
#include "matlab_cubic_spline.h"
#include "matlab_cubic_spline_emxutil.h"
#include "rt_nonfinite.h"
#include "spline.h"

/* Function Definitions */
void
matlab_cubic_spline(
    const emxArray_real_T* x,
    const emxArray_real_T* y,
    const emxArray_real_T* xx,
    emxArray_real_T* yy) {
  emxArray_real_T* pp_breaks;
  emxArray_real_T* pp_coefs;
  int numTerms;
  int high_i;
  int nx;
  int ix;
  double v;
  int low_i;
  int low_ip1;
  double xloc;
  int mid_i;
  emxInit_real_T(&pp_breaks, 2);
  emxInit_real_T(&pp_coefs, 2);

  /*  This function is simply a wrapper for the Matlab built-in cubic spline
   * function. It has been written */
  /*  in order that we can transcode this function to C++, using the Matlab
   * Coder toolbox */
  /*  Written by DDNB, January 2019 */
  /*  */
  splinepp(x, y, pp_breaks, pp_coefs);
  numTerms = pp_coefs->size[1];
  high_i = yy->size[0] * yy->size[1];
  yy->size[0] = xx->size[0];
  yy->size[1] = xx->size[1];
  emxEnsureCapacity_real_T(yy, high_i);
  nx = xx->size[1];
  for (ix = 0; ix < nx; ix++) {
    if (rtIsNaN(xx->data[ix])) {
      v = xx->data[ix];
    } else {
      high_i = pp_breaks->size[1];
      low_i = 1;
      low_ip1 = 2;
      while (high_i > low_ip1) {
        mid_i = (low_i >> 1) + (high_i >> 1);
        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }

        if (xx->data[ix] >= pp_breaks->data[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }

      xloc = xx->data[ix] - pp_breaks->data[low_i - 1];
      v = pp_coefs->data[low_i - 1];
      for (high_i = 2; high_i <= numTerms; high_i++) {
        v = xloc * v +
            pp_coefs
                ->data[(low_i + (high_i - 1) * (pp_breaks->size[1] - 1)) - 1];
      }
    }

    yy->data[ix] = v;
  }

  emxFree_real_T(&pp_coefs);
  emxFree_real_T(&pp_breaks);
}

/* End of code generation (matlab_cubic_spline.cpp) */

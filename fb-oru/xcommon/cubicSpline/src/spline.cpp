/*
 * spline.cpp
 *
 * Code generation for function 'spline'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "matlab_cubic_spline.h"
#include "spline.h"
#include "matlab_cubic_spline_emxutil.h"

/* Function Definitions */
void splinepp(const emxArray_real_T *x, const emxArray_real_T *y,
              emxArray_real_T *pp_breaks, emxArray_real_T *pp_coefs)
{
  bool has_endslopes;
  emxArray_real_T *s;
  emxArray_real_T *dvdf;
  emxArray_real_T *dx;
  emxArray_real_T *md;
  emxArray_real_T *t1_coefs;
  int nxm1;
  double szdvdf_idx_1;
  int yoffset;
  int szs_idx_1;
  double d31;
  double c_data[4];
  int j;
  double szdvdf_idx_0;
  double pp1_coefs[4];
  double dxj;
  double r;
  has_endslopes = (y->size[1] == x->size[1] + 2);
  emxInit_real_T(&s, 2);
  emxInit_real_T(&dvdf, 2);
  emxInit_real_T(&dx, 2);
  emxInit_real_T(&md, 2);
  emxInit_real_T(&t1_coefs, 2);
  if ((x->size[1] <= 2) || ((x->size[1] <= 3) && (!has_endslopes))) {
    has_endslopes = (y->size[1] == x->size[1] + 2);
    if (x->size[1] <= 2) {
      if (has_endslopes) {
        yoffset = 4;
      } else {
        yoffset = 2;
      }

      if (has_endslopes) {
        szdvdf_idx_0 = y->data[0];
        szdvdf_idx_1 = y->data[y->size[1] - 1];
        nxm1 = x->size[1];
        for (j = 0; j <= nxm1 - 2; j++) {
          dxj = x->data[1] - x->data[0];
          d31 = (y->data[2] - y->data[1]) / dxj;
          r = (d31 - szdvdf_idx_0) / dxj;
          d31 = (szdvdf_idx_1 - d31) / dxj;
          pp1_coefs[0] = (d31 - r) / dxj;
          pp1_coefs[1] = 2.0 * r - d31;
          pp1_coefs[2] = szdvdf_idx_0;
          pp1_coefs[3] = y->data[1];
        }

        memcpy(&c_data[0], &pp1_coefs[0], (unsigned int)(yoffset * (int)sizeof
                (double)));
      } else {
        c_data[0] = (y->data[1] - y->data[0]) / (x->data[1] - x->data[0]);
        c_data[1] = y->data[0];
      }

      szs_idx_1 = x->size[1];
      j = pp_breaks->size[0] * pp_breaks->size[1];
      pp_breaks->size[0] = 1;
      pp_breaks->size[1] = szs_idx_1;
      emxEnsureCapacity_real_T(pp_breaks, j);
      for (j = 0; j < szs_idx_1; j++) {
        pp_breaks->data[j] = x->data[j];
      }
    } else {
      yoffset = 3;
      d31 = x->data[1] - x->data[0];
      szdvdf_idx_1 = (y->data[1] - y->data[0]) / d31;
      c_data[0] = ((y->data[2] - y->data[1]) / (x->data[2] - x->data[1]) -
                   szdvdf_idx_1) / (x->data[2] - x->data[0]);
      c_data[1] = szdvdf_idx_1 - c_data[0] * d31;
      c_data[2] = y->data[0];
      szdvdf_idx_0 = x->data[0];
      szdvdf_idx_1 = x->data[2];
      j = pp_breaks->size[0] * pp_breaks->size[1];
      pp_breaks->size[0] = 1;
      pp_breaks->size[1] = 2;
      emxEnsureCapacity_real_T(pp_breaks, j);
      pp_breaks->data[0] = szdvdf_idx_0;
      pp_breaks->data[1] = szdvdf_idx_1;
    }

    j = pp_coefs->size[0] * pp_coefs->size[1];
    pp_coefs->size[0] = 1;
    pp_coefs->size[1] = yoffset;
    emxEnsureCapacity_real_T(pp_coefs, j);
    for (j = 0; j < yoffset; j++) {
      pp_coefs->data[j] = c_data[j];
    }
  } else {
    nxm1 = x->size[1] - 1;
    if (has_endslopes) {
      szdvdf_idx_1 = (double)y->size[1] - 3.0;
      szs_idx_1 = y->size[1] - 2;
      yoffset = 1;
    } else {
      szdvdf_idx_1 = (double)y->size[1] - 1.0;
      szs_idx_1 = y->size[1];
      yoffset = 0;
    }

    j = s->size[0] * s->size[1];
    s->size[0] = 1;
    s->size[1] = szs_idx_1;
    emxEnsureCapacity_real_T(s, j);
    j = dvdf->size[0] * dvdf->size[1];
    dvdf->size[0] = 1;
    dvdf->size[1] = (int)szdvdf_idx_1;
    emxEnsureCapacity_real_T(dvdf, j);
    j = x->size[1] - 1;
    szs_idx_1 = dx->size[0] * dx->size[1];
    dx->size[0] = 1;
    dx->size[1] = j;
    emxEnsureCapacity_real_T(dx, szs_idx_1);
    for (szs_idx_1 = 0; szs_idx_1 < nxm1; szs_idx_1++) {
      dx->data[szs_idx_1] = x->data[szs_idx_1 + 1] - x->data[szs_idx_1];
      j = yoffset + szs_idx_1;
      dvdf->data[szs_idx_1] = (y->data[j + 1] - y->data[j]) / dx->data[szs_idx_1];
    }

    for (szs_idx_1 = 2; szs_idx_1 <= nxm1; szs_idx_1++) {
      s->data[szs_idx_1 - 1] = 3.0 * (dx->data[szs_idx_1 - 1] * dvdf->
        data[szs_idx_1 - 2] + dx->data[szs_idx_1 - 2] * dvdf->data[szs_idx_1 - 1]);
    }

    if (has_endslopes) {
      d31 = 0.0;
      szdvdf_idx_1 = 0.0;
      s->data[0] = dx->data[1] * y->data[0];
      s->data[x->size[1] - 1] = dx->data[x->size[1] - 3] * y->data[x->size[1] +
        1];
    } else {
      d31 = x->data[2] - x->data[0];
      szdvdf_idx_1 = x->data[x->size[1] - 1] - x->data[x->size[1] - 3];
      s->data[0] = ((dx->data[0] + 2.0 * d31) * dx->data[1] * dvdf->data[0] +
                    dx->data[0] * dx->data[0] * dvdf->data[1]) / d31;
      s->data[x->size[1] - 1] = ((dx->data[x->size[1] - 2] + 2.0 * szdvdf_idx_1)
        * dx->data[x->size[1] - 3] * dvdf->data[x->size[1] - 2] + dx->data
        [x->size[1] - 2] * dx->data[x->size[1] - 2] * dvdf->data[x->size[1] - 3])
        / szdvdf_idx_1;
    }

    j = md->size[0] * md->size[1];
    md->size[0] = x->size[0];
    md->size[1] = x->size[1];
    emxEnsureCapacity_real_T(md, j);
    md->data[0] = dx->data[1];
    md->data[x->size[1] - 1] = dx->data[x->size[1] - 3];
    for (szs_idx_1 = 2; szs_idx_1 <= nxm1; szs_idx_1++) {
      md->data[szs_idx_1 - 1] = 2.0 * (dx->data[szs_idx_1 - 1] + dx->
        data[szs_idx_1 - 2]);
    }

    r = dx->data[1] / md->data[0];
    md->data[1] -= r * d31;
    s->data[1] -= r * s->data[0];
    for (szs_idx_1 = 3; szs_idx_1 <= nxm1; szs_idx_1++) {
      r = dx->data[szs_idx_1 - 1] / md->data[szs_idx_1 - 2];
      md->data[szs_idx_1 - 1] -= r * dx->data[szs_idx_1 - 3];
      s->data[szs_idx_1 - 1] -= r * s->data[szs_idx_1 - 2];
    }

    r = szdvdf_idx_1 / md->data[x->size[1] - 2];
    md->data[x->size[1] - 1] -= r * dx->data[x->size[1] - 3];
    s->data[x->size[1] - 1] -= r * s->data[x->size[1] - 2];
    s->data[x->size[1] - 1] /= md->data[x->size[1] - 1];
    for (szs_idx_1 = nxm1; szs_idx_1 >= 2; szs_idx_1--) {
      s->data[szs_idx_1 - 1] = (s->data[szs_idx_1 - 1] - dx->data[szs_idx_1 - 2]
        * s->data[szs_idx_1]) / md->data[szs_idx_1 - 1];
    }

    s->data[0] = (s->data[0] - d31 * s->data[1]) / md->data[0];
    nxm1 = x->size[1];
    szs_idx_1 = x->size[1];
    j = pp_breaks->size[0] * pp_breaks->size[1];
    pp_breaks->size[0] = 1;
    pp_breaks->size[1] = szs_idx_1;
    emxEnsureCapacity_real_T(pp_breaks, j);
    for (j = 0; j < szs_idx_1; j++) {
      pp_breaks->data[j] = x->data[j];
    }

    szs_idx_1 = s->size[1] - 1;
    j = t1_coefs->size[0] * t1_coefs->size[1];
    t1_coefs->size[0] = s->size[1] - 1;
    t1_coefs->size[1] = 4;
    emxEnsureCapacity_real_T(t1_coefs, j);
    for (j = 0; j <= nxm1 - 2; j++) {
      r = (dvdf->data[j] - s->data[j]) / dx->data[j];
      d31 = (s->data[j + 1] - dvdf->data[j]) / dx->data[j];
      t1_coefs->data[j] = (d31 - r) / dx->data[j];
      t1_coefs->data[szs_idx_1 + j] = 2.0 * r - d31;
      t1_coefs->data[(szs_idx_1 << 1) + j] = s->data[j];
      t1_coefs->data[3 * szs_idx_1 + j] = y->data[yoffset + j];
    }

    j = pp_coefs->size[0] * pp_coefs->size[1];
    pp_coefs->size[0] = t1_coefs->size[0];
    pp_coefs->size[1] = 4;
    emxEnsureCapacity_real_T(pp_coefs, j);
    szs_idx_1 = t1_coefs->size[0] * t1_coefs->size[1];
    for (j = 0; j < szs_idx_1; j++) {
      pp_coefs->data[j] = t1_coefs->data[j];
    }
  }

  emxFree_real_T(&t1_coefs);
  emxFree_real_T(&md);
  emxFree_real_T(&dx);
  emxFree_real_T(&dvdf);
  emxFree_real_T(&s);
}

/* End of code generation (spline.cpp) */

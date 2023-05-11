/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      cubicSpline.cpp
 * \brief     Implements the cubic spline algorithm
 *
 *
 * \details   Implements the cubic spline algorithm
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "cubicSpline.h"
#include "matlab_cubic_spline.h"
#include "matlab_cubic_spline_emxAPI.h"
#include "matlab_cubic_spline_initialize.h"
#include "matlab_cubic_spline_terminate.h"
#include "rt_nonfinite.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::cubicSpline::cubicSpline(void) {
  // Initialize the cubicSpline.
  matlab_cubic_spline_initialize();
}

//-------------------------------------------------------------------------------------------------------------
Mplane::cubicSpline::~cubicSpline(void) {
  // Initialize the cubicSpline.
  matlab_cubic_spline_terminate();
}

/**************************************************************************************************************
 * Function:    calculate
 *
 * Description: Calculates the values at the query points using the cubic spline
 *algorithm
 *
 * Returns:     The crc value (uint16)
 ************************************************************************************************************/
bool
Mplane::cubicSpline::calculate(
    std::vector<double> xValues,
    std::vector<double> yValues,
    std::vector<double> queryPoints,
    std::vector<double>& interpolatedValues) {
  emxArray_real_T* yy;
  emxArray_real_T* x;
  emxArray_real_T* y;
  emxArray_real_T* xx;
  emxInitArray_real_T(&yy, 2);

  // Initial checks
  if (xValues.size() == yValues.size()) {
    // For each query point an interpolated value will be calculated
    interpolatedValues.resize(queryPoints.size());

    // Copy input data into the format required by the Matlab code
    x = emxCreate_real_T(1, xValues.size());
    y = emxCreate_real_T(1, yValues.size());
    for (unsigned int i = 0; i < xValues.size(); i++) {
      x->data[i] = xValues[i];
      y->data[i] = yValues[i];
    }

    // Copy the query points into the format required by Matlab code
    xx = emxCreate_real_T(1, queryPoints.size());
    for (unsigned int i = 0; i < queryPoints.size(); i++) {
      xx->data[i] = queryPoints[i];
    }

    // Call the entry-point 'matlab_cubic_spline'
    matlab_cubic_spline(x, y, xx, yy);

    // Copy the result into the interpolatedValues parameter
    for (unsigned int i = 0; i < queryPoints.size(); i++) {
      interpolatedValues[i] = yy->data[i];
    }

    emxDestroyArray_real_T(yy);
    emxDestroyArray_real_T(xx);
    emxDestroyArray_real_T(y);
    emxDestroyArray_real_T(x);

    return true;
  }

  return false;
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      cubicSpline.h
 * \brief     Implements the cubic spline algorithm
 *
 *
 * \details   Implements the cubic spline algorithm
 *
 */

#ifndef CUBIC_SPLINE_H_
#define CUBIC_SPLINE_H_

#include <vector>

namespace Mplane {

/* This class is a wrapper around the Matlab generated code for cubic spline.
 */
class cubicSpline {
 public:
  cubicSpline();

  ~cubicSpline();

  /**
   * Calculate the values at the query points using the cubic spline algorithm
   */
  bool calculate(
      std::vector<double> x,
      std::vector<double> y,
      std::vector<double> queryPoints,
      std::vector<double>& interpolatedValues);
};

} // namespace Mplane

#endif /* CUBIC_SPLINE_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      cubicSplineTestCase.cpp
 * \brief     Google Test of cubicSpline
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the cubicSpline class.
 *
 */

#include <gtest/gtest.h>
#include <cmath>
#include <vector>

#include "cubicSpline.h"

using namespace Mplane ;

//-------------------------------------------------------------------------------------------------------------
TEST(cubicSpline, Test1)
{
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> queryPoints;
	std::vector<double> interpolatedValues;

	//Write the x and y vectors
	x.resize(8);
	y.resize(8);

	x[0] = 0;
	x[1] = 1;
	x[2] = 2.5;
	x[3] = 3.6;
	x[4] = 5;
	x[5] = 7;
	x[6] = 8.1;
	x[7] = 10;

	//y vector is sin of x
	for (int i = 0; i < 8; i++)
	{
		y[i] = sin(x[i]);
	}

	//Write some query points
	queryPoints.resize(10);

	queryPoints[0] = 0.5;
	queryPoints[1] = 3.1;
	queryPoints[2] = 4.2;
	queryPoints[3] = 6.25;
	queryPoints[4] = 8.5;
	queryPoints[5] = 1.7;
	queryPoints[6] = 9.15;
	queryPoints[7] = 5.3;
	queryPoints[8] = 2.75;
	queryPoints[9] = 9.6;

	cubicSpline spline;

	//Calculate cubic spline
	spline.calculate(x,y,queryPoints, interpolatedValues);

	//The interpolated values should be sin function of query points
	EXPECT_NEAR(interpolatedValues[0], sin(queryPoints[0]), 0.2);
	EXPECT_NEAR(interpolatedValues[1], sin(queryPoints[1]), 0.2);
	EXPECT_NEAR(interpolatedValues[2], sin(queryPoints[2]), 0.2);
	EXPECT_NEAR(interpolatedValues[3], sin(queryPoints[3]), 0.2);
	EXPECT_NEAR(interpolatedValues[4], sin(queryPoints[4]), 0.2);
	EXPECT_NEAR(interpolatedValues[5], sin(queryPoints[5]), 0.2);
	EXPECT_NEAR(interpolatedValues[6], sin(queryPoints[6]), 0.2);
	EXPECT_NEAR(interpolatedValues[7], sin(queryPoints[7]), 0.2);
	EXPECT_NEAR(interpolatedValues[8], sin(queryPoints[8]), 0.2);
	EXPECT_NEAR(interpolatedValues[9], sin(queryPoints[9]), 0.2);

}

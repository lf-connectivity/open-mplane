/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Maths.h
 * \brief     Collection of useful maths functions
 *
 *
 * \details   Set of maths functions that should be in the std library (and possibly are in C++11 onwards!)
 *
 */


#ifndef MATHS_H_
#define MATHS_H_

#include <cmath>
#include <string>
#include "GlobalTypeDefs.h"

namespace Mplane {

//-------------------------------------------------------------------------------------------------------------
/**
 * Round float toward nearest int
 * @param fval	+ve or -ve value to round
 * @return value rounded to nearest integer
 */
inline long long fround(double fval)
{
    // round half up - short version
	if (fval < 0.0)
		fval -= 0.5 ;
	else
		fval += 0.5 ;

	return static_cast<long long>(fval) ;
}

/**
 * \class Maths
 */
class Maths {
public:
	/**
	 * Jason's optimised char pointer to float
	 * @param str
	 * @param end	(Optional) when provided with a pointer, method returns the end of the string
	 * @return float
	 */
	static float char2float(const char* str, char** end = nullptr) ;

	/**
	 * Jason's optimised char pointer to float
	 * @param str
	 * @return float
	 */
	static float str2float(const std::string& str) ;

	/**
	 * Convert 32 bit representation of single precision floating point into a float
	 * @param ieee754
	 * @return float
	 */
	static float ieee754toFloat(UINT32 ieee754) ;

	/**
	 * Convert float to 32 bit representation of single precision floating point
	 * @param float
	 * @return ieee754
	 */
	static UINT32 floatToIeee754(float fval) ;

	/**
	 * Compare 2 floats for equality within a certain accuracy
	 */
	static bool floatEqual(float lhs, float rhs, float accuracy = 0.001) ;
};

}

#endif /* MATHS_H_ */

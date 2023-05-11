#ifndef _MPLANE_CPPUNIT_H_
#define _MPLANE_CPPUNIT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AxisCppunit
 * \brief     Wrapper macros for CPPUNIT
 *
 *
 * \details   Mplane extensions to the CPPUNIT assertion macros. Most of the
 * macros just output extra debug info if the variable
 * 'debug' is true. This variable may be declared as a member variable or global.
 *
 */

// Include all the useful CPPUNIT stuff
#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

/**
 * Wrap the standard assert macros with some extra debug output
 */

#define AXIS_CPPUNIT_ASSERT_EQUAL(expected, actual)	\
	if (debug) std::cout << "CPPUNIT_ASSERT_EQUAL(expected=" << (expected) << ", actual = " << (actual) << ")" << endl ; \
	CPPUNIT_ASSERT_EQUAL(expected, actual)

#define AXIS_CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta)	\
	if (debug) std::cout << "CPPUNIT_ASSERT_DOUBLES_EQUAL(expected=" << (expected) << ", actual = " << (actual) << " within " << delta << ")" << endl ; \
	CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta)



#endif /* _MPLANE_CPPUNIT_H_ */

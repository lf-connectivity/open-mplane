/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FailString.cpp
 * \brief     Implementation of Fail String class
 *
 *
 * \details   Implements the failure string capture methods
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdexcept>
#include <iostream>

#include "FailString.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FailString::FailString(void):
	mFailureReason("")
{
}

//-------------------------------------------------------------------------------------------------------------
FailString::~FailString()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string FailString::failReason(void)
{
	// Return current reason and clear it
	std::string reason("") ;
	swap(mFailureReason, reason) ;

#ifdef OFF_TARGET
	// Make a bang for test purposes!
	std::cerr << "FAIL - reason: " << reason << std::endl ;
#endif

	return reason ;
}

//-------------------------------------------------------------------------------------------------------------
void FailString::setFailReason(const std::string& reason)
{
	mFailureReason.assign(reason) ;
}

//-------------------------------------------------------------------------------------------------------------
void FailString::clearFailReason()
{
	mFailureReason.clear() ;
}

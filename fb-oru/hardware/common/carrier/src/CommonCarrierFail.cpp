
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierFail.cpp
 * \brief     Implementation of Common Carrier Fail class
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

#include "CommonCarrierFail.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonCarrierFail::CommonCarrierFail(void):
	mFailureReason("")
{
}

//-------------------------------------------------------------------------------------------------------------
CommonCarrierFail::~CommonCarrierFail()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string CommonCarrierFail::failReason(void)
{
	// Return current reason and clear it
	std::string reason("") ;
	swap(mFailureReason, reason) ;

#ifdef OFF_TARGET
	// Make a bang for test purposes!
	std::cerr << "Carrier FAIL - reason: " << reason << std::endl ;
#endif

	return reason ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierFail::setFailReason(const std::string& reason)
{
	mFailureReason.assign(reason) ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierFail::clearFailReason()
{
	mFailureReason.clear() ;
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgcCal.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RxAgcCal.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxAgcCal::RxAgcCal(const std::string& version, const std::string& country, const std::string& facility, const std::string& theoperator) :
	RxCal(version, country, facility, theoperator)
{
}

//-------------------------------------------------------------------------------------------------------------
RxAgcCal::~RxAgcCal()
{
}

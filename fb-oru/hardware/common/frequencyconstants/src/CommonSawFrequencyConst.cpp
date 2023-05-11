/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonSawFrequencyConst.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommonSawFrequencyConst.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonSawFrequencyConst::~CommonSawFrequencyConst()
{
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonSawFrequencyConst::getCentre() const
{
	return mCentre ;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonSawFrequencyConst::getBandwidth() const
{
	return mBandwidth ;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency CommonSawFrequencyConst::getDigitalCentre() const
{
	return mDigCentre ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonSawFrequencyConst::CommonSawFrequencyConst() :
	mCentre(0.0),
	mBandwidth(0.0),
	mDigCentre(0.0)
{
}

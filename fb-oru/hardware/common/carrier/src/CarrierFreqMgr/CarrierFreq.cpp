/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFreq.cpp
 * \brief     Stores the range of frequencies used by a carrier
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CarrierUtils.hpp"
#include "CarrierFreq.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CarrierFreq::CarrierFreq() :
	mCentre(0.0),
	mType(ICarrier::CARRTYPE_NONE),
	mMin(0.0),
	mMax(0.0)
{
}

//-------------------------------------------------------------------------------------------------------------
CarrierFreq::CarrierFreq(const Frequency& centre, ICarrier::Type carrierType) :
	mCentre(centre),
	mType(carrierType),
	mMin(0.0),
	mMax(0.0)
{
	Frequency bandwidth(CarrierUtils::typeBandwidth(mType)) ;
	Frequency halfBw(bandwidth / 2.0) ;
	mMin = mCentre - halfBw ;
	mMax = mCentre + halfBw ;
}

//-------------------------------------------------------------------------------------------------------------
CarrierFreq::~CarrierFreq()
{
}

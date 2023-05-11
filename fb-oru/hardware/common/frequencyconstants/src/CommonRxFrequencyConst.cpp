/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxGrequencyConstant.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "Frequency.h"
#include "CommonRxFrequencyConst.h"

using namespace Mplane;

const Frequency CommonRxFrequencyConst::getMinimum() const
{
    return mMinimum;
}

const Frequency CommonRxFrequencyConst::getMaximum() const
{
    return mMaximum;
}

const Frequency CommonRxFrequencyConst::getCentre() const
{
    return mCentre;
}

const Frequency CommonRxFrequencyConst::getFilterMinimum() const
{
    return mFilterMinimum;
}

const Frequency CommonRxFrequencyConst::getFilterMaximum() const
{
    return mFilterMaximum;
}

const Frequency CommonRxFrequencyConst::get3GMinimum() const
{
    return m3GMinimum;
}

const Frequency CommonRxFrequencyConst::get3GMaximum() const
{
    return m3GMaximum;
}

const Frequency CommonRxFrequencyConst::getBandwidth() const
{
    return mBandwidth;
}

const Frequency CommonRxFrequencyConst::getRaster() const
{
    return mRaster;
}

const Injection_t CommonRxFrequencyConst::getCarrierFlip() const
{
    return mCarrierFlip;
}

const Injection_t CommonRxFrequencyConst::getLOInjection() const
{
    return mLOInjection;
}

const unsigned int CommonRxFrequencyConst::getNumberOfRFLO() const
{
    return mNumberOfRFLO;
}

void CommonRxFrequencyConst::show()
{
}

CommonRxFrequencyConst::CommonRxFrequencyConst():
	mFilterMinimum(0.0),
	mFilterMaximum(0.0),
	m3GMinimum(0.0),
	m3GMaximum(0.0),
	mMinimum(0.0),
	mMaximum(0.0),
	mCentre(0.0),
	mRaster(1000.0),
	mCarrierFlip( LOWSIDE ),
	mLOInjection( LOWSIDE ),
	mNumberOfRFLO( 1 )
{
}

CommonRxFrequencyConst::~CommonRxFrequencyConst()
{
}

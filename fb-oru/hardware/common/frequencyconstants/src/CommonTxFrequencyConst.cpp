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
#include "CommonTxFrequencyConst.h"

using namespace Mplane;

const Frequency CommonTxFrequencyConst::getMinimum() const
{
    return mMinimum;
}

const Frequency CommonTxFrequencyConst::getMaximum() const
{
    return mMaximum;
}

const Frequency CommonTxFrequencyConst::getCentre() const
{
    return mCentre;
}

const Frequency CommonTxFrequencyConst::getFilterMinimum() const
{
    return mFilterMinimum;
}

const Frequency CommonTxFrequencyConst::getFilterMaximum() const
{
    return mFilterMaximum;
}

const Frequency CommonTxFrequencyConst::get3GMinimum() const
{
    return m3GMinimum;
}

const Frequency CommonTxFrequencyConst::get3GMaximum() const
{
    return m3GMaximum;
}

const Frequency CommonTxFrequencyConst::getBandwidth() const
{
    return mBandwidth;
}

const Frequency CommonTxFrequencyConst::getRaster() const
{
    return mRaster;
}

const Injection_t CommonTxFrequencyConst::getCarrierFlip() const
{
    return mCarrierFlip;
}

const unsigned int CommonTxFrequencyConst::getNumberOfRFLO() const
{
    return mNumberOfRFLO;
}

const Injection_t CommonTxFrequencyConst::getLOInjection() const
{
    return mLOInjection;
}

void CommonTxFrequencyConst::show()
{
}

CommonTxFrequencyConst::CommonTxFrequencyConst():
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

CommonTxFrequencyConst::~CommonTxFrequencyConst()
{
}

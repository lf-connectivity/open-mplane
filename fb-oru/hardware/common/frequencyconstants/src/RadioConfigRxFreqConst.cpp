/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfigRxFreqConst.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <memory>
#include "IRadioConfig.h"

#include "RadioConfigRxFreqConst.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigRxFreqConst::getMinimum() const
{
    return mMinimum;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigRxFreqConst::getMaximum() const
{
    return mMaximum;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigRxFreqConst::getCentre() const
{
    return mCentre;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigRxFreqConst::getFilterMinimum() const
{
    return mFilterMinimum;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigRxFreqConst::getFilterMaximum() const
{
    return mFilterMaximum;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigRxFreqConst::get3GMinimum() const
{
    return m3GMinimum;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigRxFreqConst::get3GMaximum() const
{
    return m3GMaximum;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigRxFreqConst::getBandwidth() const
{
    return mBandwidth;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigRxFreqConst::getRaster() const
{
    return mRaster;
}

//-------------------------------------------------------------------------------------------------------------
const Injection_t RadioConfigRxFreqConst::getCarrierFlip() const
{
    return mCarrierFlip;
}

//-------------------------------------------------------------------------------------------------------------
const Injection_t RadioConfigRxFreqConst::getLOInjection() const
{
    return mLOInjection;
}

//-------------------------------------------------------------------------------------------------------------
const unsigned int RadioConfigRxFreqConst::getNumberOfRFLO() const
{
    return mNumberOfRFLO;
}

//-------------------------------------------------------------------------------------------------------------
void RadioConfigRxFreqConst::show()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RadioConfigRxFreqConst::RadioConfigRxFreqConst():
	mFilterMinimum(0.0),
	mFilterMaximum(0.0),
	m3GMinimum(0.0),
	m3GMaximum(0.0),
	mMinimum(0.0),
	mMaximum(0.0),
	mCentre(0.0),
	mBandwidth(0.0),
	mRaster(1000.0),
	mCarrierFlip( LOWSIDE ),
	mLOInjection( LOWSIDE ),
	mNumberOfRFLO( 1 )
{

    std::shared_ptr<IRadioConfig> radioConfig(IRadioConfig::singleton()) ;

    if (radioConfig->isVariable(IRadioConfig::RX_CENTRE_FREQ))
    	mCentre = Frequency(radioConfig->doubleValue(IRadioConfig::RX_CENTRE_FREQ), Frequency::KHz) ;

    if (radioConfig->isVariable(IRadioConfig::RX_BANDWIDTH))
    	mBandwidth = Frequency(radioConfig->doubleValue(IRadioConfig::RX_BANDWIDTH), Frequency::KHz) ;

    if (radioConfig->isVariable(IRadioConfig::RX_MIN_FILTER_FREQ))
    	mFilterMinimum = Frequency(radioConfig->doubleValue(IRadioConfig::RX_MIN_FILTER_FREQ), Frequency::KHz) ;

    if (radioConfig->isVariable(IRadioConfig::RX_MAX_FILTER_FREQ))
    	mFilterMaximum = Frequency(radioConfig->doubleValue(IRadioConfig::RX_MAX_FILTER_FREQ), Frequency::KHz) ;

    if (radioConfig->isVariable(IRadioConfig::RX_MIN_AIR_FREQ))
    	m3GMinimum = Frequency(radioConfig->doubleValue(IRadioConfig::RX_MIN_AIR_FREQ), Frequency::KHz) ;

    if (radioConfig->isVariable(IRadioConfig::RX_MAX_AIR_FREQ))
    	m3GMaximum = Frequency(radioConfig->doubleValue(IRadioConfig::RX_MAX_AIR_FREQ), Frequency::KHz) ;

    if (radioConfig->isVariable(IRadioConfig::RX_MIN_FREQ))
    	mMinimum = Frequency(radioConfig->doubleValue(IRadioConfig::RX_MIN_FREQ), Frequency::KHz) ;

    if (radioConfig->isVariable(IRadioConfig::RX_MAX_FREQ))
    	mMaximum = Frequency(radioConfig->doubleValue(IRadioConfig::RX_MAX_FREQ), Frequency::KHz) ;


}


//-------------------------------------------------------------------------------------------------------------
RadioConfigRxFreqConst::~RadioConfigRxFreqConst()
{
}

//-------------------------------------------------------------------------------------------------------------
void RadioConfigRxFreqConst::setRadioSpecific(const Frequency &raster,
		Injection_t carrierFlip, Injection_t loInjection,
		unsigned int numberOfRFLO)
{
	mRaster = raster ;
	mCarrierFlip = carrierFlip ;
	mLOInjection = loInjection ;
	mNumberOfRFLO = numberOfRFLO ;
}

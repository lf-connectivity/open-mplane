/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfigSawFreqConst.cpp
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

#include "RadioConfigSawFreqConst.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const std::string SECTION("saw") ;

const std::string CENTRE_FREQ("centre-khz") ;
const std::string BANDWIDTH("bandwidth-khz") ;
const std::string DIG_CENTRE_FREQ("digcentre-khz") ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RadioConfigSawFreqConst::~RadioConfigSawFreqConst()
{
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigSawFreqConst::getCentre() const
{
	return mCentre ;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigSawFreqConst::getBandwidth() const
{
	return mBandwidth ;
}

//-------------------------------------------------------------------------------------------------------------
const Frequency RadioConfigSawFreqConst::getDigitalCentre() const
{
	return mDigCentre ;
}

//-------------------------------------------------------------------------------------------------------------
RadioConfigSawFreqConst::RadioConfigSawFreqConst() :
	mCentre(0.0),
	mBandwidth(0.0),
	mDigCentre(0.0)

{
    std::shared_ptr<IRadioConfig> radioConfig(IRadioConfig::singleton()) ;

    if (radioConfig->isVariable(IRadioConfig::SAW_CENTRE_FREQ))
    	mCentre = Frequency(radioConfig->doubleValue(IRadioConfig::SAW_CENTRE_FREQ), Frequency::KHz) ;

    if (radioConfig->isVariable(IRadioConfig::SAW_BANDWIDTH))
    	mBandwidth = Frequency(radioConfig->doubleValue(IRadioConfig::SAW_BANDWIDTH), Frequency::KHz) ;

    if (radioConfig->isVariable(IRadioConfig::SAW_DIG_CENTRE_FREQ))
    	mDigCentre = Frequency(radioConfig->doubleValue(IRadioConfig::SAW_DIG_CENTRE_FREQ), Frequency::KHz) ;

}

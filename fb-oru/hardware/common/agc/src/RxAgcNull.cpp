/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxAgcNull.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RxAgcNull.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<IRxAgc> > Mplane::RxAgcNullFactory::createAgcs()
{
    return RxAgcNullFactory::getAgcs() ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<IRxAgc> > Mplane::RxAgcNullFactory::getAgcs()
{
	static std::vector< std::shared_ptr<IRxAgc> > rxAgcList;

	// set the number of RX ports for the host radio test implementation
    if( rxAgcList.empty())
    {
        rxAgcList.push_back (  std::make_shared<RxAgcNull>(0, "RxAgcNull"));
    }
    return rxAgcList;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRxAgc> Mplane::RxAgcNullFactory::getAgc(unsigned index)
{
	std::vector< std::shared_ptr<IRxAgc> > agcList(IRxAgcFactory::getAgcs()) ;
	return agcList[0] ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::RxAgcNull::RxAgcNull(unsigned index,
		const std::string& name, unsigned numAdcBits, const Power& dBbelowFS,
		const Power& thresholdHysteresis,
		const Temperature& temperatureHysteresis) {
}

//-------------------------------------------------------------------------------------------------------------
Mplane::RxAgcNull::~RxAgcNull() {
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RxAgcNull::setAttenFrames(unsigned numFrames) {
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RxAgcNull::setDigitalGain(Power digitalGain) {
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RxAgcNull::setDigitalGain(Power digitalGain,
		Power rxPointAdjust) {
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RxAgcNull::setRxPointAdjust(Power rxPointAdjust) {
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RxAgcNull::show(std::ostream& os) const {
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RxAgcNull::showDetail(std::ostream& os) const {
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::RxAgcNull::getFeAdjustment(unsigned feLevel) const {
	return Power(0.0) ;
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::RxAgcNull::getFeAtten(unsigned feLevel) const {
	return Power(0.0) ;
}

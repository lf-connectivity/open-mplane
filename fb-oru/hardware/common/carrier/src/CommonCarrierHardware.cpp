
/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierHardware.cpp
 * \brief     Implementation of Common Carrier Hardware base class
 *
 *
 * \details   Implementation of Common Carrier Hardware base class. Just implements the generic methods
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CommonCarrierFail.h"
#include "CommonCarrierHardware.h"

// debug
#include "CommonCarrier.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonCarrierHardware::CommonCarrierHardware(void):
	mCarrier(NULL),
	mFail(new CommonCarrierFail() ),
	mSettingsChanged(false)
{
}

//-------------------------------------------------------------------------------------------------------------
CommonCarrierHardware::CommonCarrierHardware(const ICarrier *carrier):
	mCarrier(carrier),
	mFail(new CommonCarrierFail() ),
	mSettingsChanged(false)
{
}

//-------------------------------------------------------------------------------------------------------------
CommonCarrierHardware::~CommonCarrierHardware()
{
}

//-------------------------------------------------------------------------------------------------------------
const ICarrier& CommonCarrierHardware::getCarrier() const
{
	return *mCarrier ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::validateChange(const ICarrier &carrier)
{
	mFail->clearFailReason() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::carrierChange(const ICarrier &carrier)
{
	mFail->clearFailReason() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
const bool CommonCarrierHardware::isChanged() const
{
	// return flag
	return mSettingsChanged ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::preUpdate()
{
	mFail->clearFailReason() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::updateHardware()
{
	mFail->clearFailReason() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::postUpdate()
{
	mFail->clearFailReason() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierHardware::changeComplete()
{
	// clear flag
	mSettingsChanged = false ;
}

//-------------------------------------------------------------------------------------------------------------
std::string CommonCarrierHardware::failReason(void)
{
	return mFail->failReason() ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierHardware::settingsChanged()
{
	// set flag
	mSettingsChanged = true ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierHardware::showCarrier(std::ostream& os) const
{

}

//-------------------------------------------------------------------------------------------------------------
Power CommonCarrierHardware::getPower(unsigned txpath) const
{
	return Power(0.0) ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CommonCarrierHardware::getMinTxFreq() const
{
	return Frequency(0.0) ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CommonCarrierHardware::getMaxTxFreq() const
{
	return Frequency(0.0) ;
}

unsigned CommonCarrierHardware::getDlDelay( unsigned antenna ) const
{
	return 0;
}

unsigned CommonCarrierHardware::getUlDelay( unsigned antenna ) const
{
	return 0;
}

unsigned CommonCarrierHardware::getUlAdditionalDelay( unsigned antenna ) const
{
	return 0;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::resyncUlStream(unsigned path)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::resyncDlStream(unsigned path)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::txFrequencyChange(unsigned antenna, const Frequency& newTxFrequency)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::rxFrequencyChange(unsigned antenna, const Frequency& newRxFrequency)
{
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonCarrierHardware::getRssi(unsigned antenna, Power& rssi) const
{
	rssi = Power(0.0);
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonCarrierHardware::showDiag(std::ostream& os) const
{
}

//-------------------------------------------------------------------------------------------------------------
Frequency CommonCarrierHardware::getTxFreq() const
{
	return Frequency(0.0) ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CommonCarrierHardware::getChbwFreq() const
{
	return Frequency(0.0) ;
}

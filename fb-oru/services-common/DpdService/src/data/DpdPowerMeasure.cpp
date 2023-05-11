/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdPowerMeasure.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IDevices.h"
#include "IRadio.h"
#include "IAttenuator.h"

#include "DpdPowerMeasure.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdPowerMeasure::DpdPowerMeasure(const std::string& gerrName) :
	mGerrName(gerrName),
	mTxPort(0),
	mXrmsRef(0.0),
	mYrmsRef(0.0),
	mGerr(0.0),
	mSrxAtten(0.0)
{
}

//-------------------------------------------------------------------------------------------------------------
DpdPowerMeasure::DpdPowerMeasure(const IDpdPowerMeasure& rhs) :
	mGerrName(rhs.getGerrName()),
	mTxPort(rhs.getTxPort()),
	mXrmsRef(rhs.getXrmsRef()),
	mYrmsRef(rhs.getYrmsRef()),
	mGerr(rhs.getGerr()),
	mSrxAtten(rhs.getSrxAtten())
{
}

//-------------------------------------------------------------------------------------------------------------
DpdPowerMeasure::~DpdPowerMeasure()
{
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::DpdPowerMeasure::predicate(const std::map<std::string, DataVariant>& attributes)
{
	// Require the following variable to be present:
	//   tx
	//   srxAtten
	//   XrmsRef
	//   YrmsRef
	//   fwdGerr [trigger]
	//
	return checkVariables(std::vector<std::string>{
		"tx",
		"srxAtten",
		"XrmsRef",
		"YrmsRef",
		mGerrName
	}, attributes) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdPowerMeasure::setData(const std::map<std::string, DataVariant>& attributes)
{
	unsigned port( static_cast<unsigned>(attributes.at("tx").toInt()) ) ;
	mTxPort = port + 1 ;
	mXrmsRef = rmsToPower(attributes.at("XrmsRef").toInt()) ;
	mYrmsRef = rmsToPower(attributes.at("YrmsRef").toInt()) ;
	mGerr = Power(attributes.at(mGerrName).toFloat()) ;

	// convert srxAtten
	std::shared_ptr<IAttenuator> atten(IRadioFactory::getInterface()->getDevices().getDpdAttenuator(port)) ;
	mSrxAtten = atten->calcAttenuation( static_cast<unsigned>(attributes.at("srxAtten").toInt())) ;
	return true ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Power DpdPowerMeasure::rmsToPower(int rms) const
{
	// RMS value is referenced to 32768
    float power = (float)(20 * log10( (float)rms / 32768.0 ));
	return Power(power) ;
}

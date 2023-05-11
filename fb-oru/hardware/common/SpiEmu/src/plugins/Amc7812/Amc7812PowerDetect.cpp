/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Amc7812PowerDetect.cpp
 * \brief     TX power detector
 *
 *
 * \details   An Amc7812 ADC used for TX power detection in the system. Emulates the required TX power to drive a PCL
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cmath>
#include <iostream>

#include "ISpiPlugin.h"
#include "ISpiEmu.h"

#include "OffTargetFPGA.h"
#include "Amc7812PowerDetect.h"
#include "SpiPluginAttnPE4302.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
static constexpr float PDET_FACTOR{-41.0} ;
static constexpr float PDET_OFFSET{1238.0 + 41.0*48.0} ;
static constexpr float PDET_DELTA{80.3} ; // this is the difference between the CW generated output and the target

// RF Atten
const float MAX_ATTENUATION(31.0f); // maximum attenuation for the device
const float MIN_ATTENUATION(0.0f); // minimum attenuation for the device
const float SWEET_SPOT(6.0f); // attenuation sweet spot for the device
const UINT16 RAW_SWEET_SPOT(7200); //raw attenuator value for the sweet spot
const float LOW_COEFF(1530.5f);          //!> the conversion coefficient for 0 to 6dB
const float HI_COEFF(288.0f);           //!> the conversion coefficient for 6dB t0 30dB

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAmc7812Handler> Amc7812PowerDetect::factory(const std::string& name, unsigned txPort)
{
	std::shared_ptr<IAmc7812Handler> instance(std::make_shared<Amc7812PowerDetect>(name, txPort)) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Amc7812PowerDetect::Amc7812PowerDetect(const std::string& name, unsigned txPort) :
	Amc7812Handler(name, PDET_OFFSET, PDET_FACTOR),
	mTxPort(txPort),
	mTargetPower(33.85)
{
}

//-------------------------------------------------------------------------------------------------------------
Amc7812PowerDetect::~Amc7812PowerDetect()
{
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float Amc7812PowerDetect::getValue(unsigned address)
{
//	std::shared_ptr<IPcl> pcl(getInstance(mTxPort)) ;

	Power cw(getCwPower()) ;
	Power ifAtten(getIfAtten()) ;
	Power rfAtten(getRfAtten()) ;
	Power digScaling(getDigScaling()) ;

	Power output = cw + digScaling - ifAtten - rfAtten ;
	Power targetPower = output + Power(PDET_DELTA) ;

	logDebugNormal("Amc7812[%s] TX%u: CW %fdB + Scaling %fdB - IF Atten %fdB - RF Atten %fdB = %fdB + %fdB => Target %fdB",
		getInstanceName().c_str(),
		mTxPort,
		cw.get(),
		digScaling.get(),
		ifAtten.get(),
		rfAtten.get(),
		output.get(),
		PDET_DELTA,
		targetPower.get()
	) ;

	mTargetPower = targetPower ;

	return mTargetPower.get() ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Power Mplane::Amc7812PowerDetect::getCwPower()
{
    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    UINT16 word(fpgaEmu->internalReadField("antDacSedQ0[" + std::to_string(mTxPort) + "]")) ;
    float dv( (float)word / (32767.0 * 0.707106781187)) ;
    float power( 20.0 * log10(dv) ) ;

//std::cerr << " * getCwPower: word=" << word << " power=" << power << std::endl ;
    return power ;
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::Amc7812PowerDetect::getIfAtten()
{
	// Get the top-level SPI emulator model
	std::shared_ptr<ISpiEmu> spiEmu(ISpiEmu::getInstance()) ;

	// Get the plugin for the PE4302 attenuator
	std::shared_ptr<ISpiPlugin> ifAttnPlugin(spiEmu->getPlugin("AttnPE4302-" + std::to_string(mTxPort))) ;
	if (!ifAttnPlugin)
		return Power(0.0) ;

	// Cast it to the specific instance so we can access it's additional methods
	std::shared_ptr<SpiPluginAttnPE4302> attnPE4302(std::dynamic_pointer_cast<SpiPluginAttnPE4302>(ifAttnPlugin)) ;
	if (!attnPE4302)
		return Power(0.0) ;

	// read out the attenuation setting
	return attnPE4302->getAtten() ;
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::Amc7812PowerDetect::getRfAtten()
{
    // get the fpga emulator
    std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

    UINT16 pwm(fpgaEmu->internalReadField("txVattenRaw[" + std::to_string(mTxPort) + "]")) ;


	float attn(0.0) ;
	if (pwm >= RAW_SWEET_SPOT)
	{
		attn = SWEET_SPOT - ( ( (float)pwm - RAW_SWEET_SPOT) / LOW_COEFF) ;
	}
	else
	{
		attn = SWEET_SPOT + ( (RAW_SWEET_SPOT - (float)pwm ) / HI_COEFF) ;
	}

//	std::cerr << " * getRfAtten: pwm=" << pwm << " attn=" << attn << std::endl ;

	if (attn > MAX_ATTENUATION)
		attn = MAX_ATTENUATION ;
	if (attn < MIN_ATTENUATION)
		attn = MIN_ATTENUATION ;

    return attn ;
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::Amc7812PowerDetect::getDigScaling()
{
	// get the fpga emulator
	std::shared_ptr<OffTargetFPGA> fpgaEmu = OffTargetFPGA::getInstance() ;

	UINT16 scaler(fpgaEmu->internalReadField("antDacIqSwap[" + std::to_string(mTxPort) + "]")) ;

	float multiplier( (float)scaler / 16384.0) ;
	float power( 20.0 * log10(multiplier) ) ;

//	std::cerr << " * getDigScaling: scaler=" << scaler <<
//		" multiplier=" << multiplier <<
//		" power=" << power << std::endl ;
	return power ;
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiPluginAttnPE4302.cpp
 * \brief     Attenuator plugin for SPI emulation
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SpiPluginAttnPE4302.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISpiPlugin> SpiPluginAttnPE4302::factory(unsigned bus, unsigned devId, unsigned devNum, unsigned shift)
{
	std::shared_ptr<ISpiPlugin> instance(std::make_shared<SpiPluginAttnPE4302>(bus, devId, devNum, shift)) ;
	return instance ;
}

//-------------------------------------------------------------------------------------------------------------
SpiPluginAttnPE4302::SpiPluginAttnPE4302(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) :
	SpiPluginBase("AttnPE4302-" + std::to_string((devNum-3)/2), bus, devId, devNum, shift),
	mAtten(0.0)
{
}

//-------------------------------------------------------------------------------------------------------------
SpiPluginAttnPE4302::~SpiPluginAttnPE4302()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SpiPluginAttnPE4302::handleData(unsigned select,
		unsigned writeData, unsigned writeNumBits, unsigned & readData,
		unsigned readNumBits)
{
	if (writeNumBits == 6)
	{
		mAtten = Power((float)writeData * 0.5) ;
		logDebugNormal("[%s] : Atten %fdB", getName().c_str(), mAtten.get()) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
Power SpiPluginAttnPE4302::getAtten() const
{
	return mAtten ;
}

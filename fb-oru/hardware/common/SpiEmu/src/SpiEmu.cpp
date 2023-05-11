/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiEmu.cpp
 * \brief     SPI emulator of all devices on all buses
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "plugins/SpiPluginAttnPE4302.h"
#include "plugins/SpiPluginAmc7812.h"
#include "plugins/SpiPluginAd9122.h"

#include "SpiBusEmu.h"
#include "SpiEmu.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISpiEmu> ISpiEmu::getInstance()
{
	static std::shared_ptr<ISpiEmu> instance(std::make_shared<SpiEmu>(2)) ;
	return instance ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SpiEmu::SpiEmu(unsigned numSpiBuses) :
	Loggable("SpiEmu", "SpiEmu"),
	mSpiBus()
{
//	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "SpiEmu") ;

	// Create buses
	for (unsigned bus=0; bus < numSpiBuses; ++bus)
	{
		mSpiBus.push_back(std::make_shared<SpiBusEmu>(bus)) ;
	}

	// Add devices
	registerDevice(SpiPluginAmc7812::factory(0, 8, 0, 3)) ;
	registerDevice(SpiPluginAmc7812::factory(0, 8, 1, 3)) ;
	registerDevice(SpiPluginAttnPE4302::factory(0, 7, 3, 3)) ;
	registerDevice(SpiPluginAttnPE4302::factory(0, 7, 5, 3)) ;
	registerDevice(SpiPluginAd9122::factory(0, 4, 0, 3)) ;
	registerDevice(SpiPluginAd9122::factory(0, 4, 1, 3)) ;

}

//-------------------------------------------------------------------------------------------------------------
SpiEmu::~SpiEmu()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SpiEmu::registerDevice(std::shared_ptr<ISpiPlugin> plugin)
{
	unsigned bus(plugin->getBus()) ;
	if (bus >= mSpiBus.size())
		return false ;

	return mSpiBus[bus]->registerDevice(plugin) ;
}

//-------------------------------------------------------------------------------------------------------------
bool SpiEmu::unregisterDevice(unsigned bus, unsigned devId, unsigned devNum, unsigned shift)
{
	if (bus >= mSpiBus.size())
		return false ;

	return mSpiBus[bus]->unregisterDevice(devId, devNum, shift) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISpiPlugin> SpiEmu::getPlugin(const std::string& name) const
{
	for (auto entry : mSpiBus)
	{
		std::shared_ptr<ISpiPlugin> plugin(entry->getPlugin(name)) ;
		if (plugin)
			return plugin ;
	}
	return std::shared_ptr<ISpiPlugin>() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISpiPlugin> SpiEmu::getPlugin(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) const
{
	if (bus >= mSpiBus.size())
		return std::shared_ptr<ISpiPlugin>() ;

	return mSpiBus[bus]->getPlugin(devId, devNum, shift) ;
}

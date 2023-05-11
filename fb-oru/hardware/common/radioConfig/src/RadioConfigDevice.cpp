/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfigDevice.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "IRadioConfig.h"

#include "RadioConfigFpgaHelper.h"
#include "RadioConfigDevice.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRadioConfigDevice> IRadioConfigDevice::singleton()
{
	static std::shared_ptr<IRadioConfigDevice> instance(std::make_shared<RadioConfigDevice>()) ;
	return instance ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RadioConfigDevice::RadioConfigDevice() :
	Device( IDevice::CONFIG, 0, "RadioConfig" )
{
	std::cerr << "NEW RadioConfigDevice" << std::endl ;

	// Create the IRadioConfigSetter to ensure the RadioConfig is initialised before the app starts using the values
	(void)IRadioConfigSetter::singleton() ;

	// FPGA should be available now, so apply the limits from the FPGA registers
	RadioConfigFpgaHelper::applyFpgaLimits() ;
}

//-------------------------------------------------------------------------------------------------------------
RadioConfigDevice::~RadioConfigDevice()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RadioConfigDevice::doInit()
{
	return ReturnType::RT_OK ;
}

//-------------------------------------------------------------------------------------------------------------
void RadioConfigDevice::show()
{
}

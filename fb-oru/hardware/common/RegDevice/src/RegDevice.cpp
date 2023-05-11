/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegDevice.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RegModel.h"
#include "RegDevice.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RegDevice::~RegDevice()
{
	mBus->unregisterMonitor( std::dynamic_pointer_cast<IBusMonitor>(mRegModel) ) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RegDevice::RegDevice(Device::Type type, int index, const std::string &name,
		std::shared_ptr<IBus> bus,
		unsigned addrWidth, unsigned dataWidth, unsigned addrLSB) :
	Device(type, index, name),
	mBus(bus),
	mRegModel( )
{
	std::shared_ptr<RegModel> regModel( std::make_shared<RegModel>(name, addrWidth, dataWidth, addrLSB) ) ;
	mRegModel = regModel ;
	mBus->registerMonitor(regModel) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRegModel> RegDevice::regModel()
{
	return mRegModel ;
}

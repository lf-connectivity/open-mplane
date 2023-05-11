/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegDriver.cpp
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
#include "RegDriver.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RegDriver::RegDriver(const std::string &name, std::shared_ptr<IBus> bus, std::shared_ptr<IRegModel> regModel) :
	Driver(name),
	mBus(bus),
	mRegModel(regModel)
{
	mBus->registerMonitor( std::dynamic_pointer_cast<IBusMonitor>(mRegModel)) ;
}

//-------------------------------------------------------------------------------------------------------------
RegDriver::~RegDriver()
{
	mBus->unregisterMonitor( std::dynamic_pointer_cast<IBusMonitor>(mRegModel) ) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRegModel> RegDriver::regModel()
{
	return mRegModel ;
}

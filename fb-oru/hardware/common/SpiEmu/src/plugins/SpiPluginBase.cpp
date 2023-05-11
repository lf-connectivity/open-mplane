/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiPluginBase.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SpiPluginBase.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SpiPluginBase::SpiPluginBase(const std::string& name, unsigned bus,
		unsigned devId, unsigned devNum, unsigned shift) :
	Loggable(name, "SpiEmu"),
	mBus(bus),
	mDevId(devId),
	mDevNum(devNum),
	mShift(shift)
{
}

//-------------------------------------------------------------------------------------------------------------
SpiPluginBase::~SpiPluginBase()
{
}

//-------------------------------------------------------------------------------------------------------------
bool SpiPluginBase::isPlugin(const std::string& name) const
{
	return getName() == name ;
}

//-------------------------------------------------------------------------------------------------------------
bool SpiPluginBase::isPlugin(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) const
{
	if (mBus != bus)
		return false ;
	if (mDevId != devId)
		return false ;
	if (mDevNum != devNum)
		return false ;
	if (mShift != shift)
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string SpiPluginBase::getName() const
{
	return getInstanceName() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SpiPluginBase::getBus() const
{
	return mBus ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SpiPluginBase::getDevId() const
{
	return mDevId ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SpiPluginBase::getDevNum() const
{
	return mDevNum ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned SpiPluginBase::getShift() const
{
	return mShift ;
}

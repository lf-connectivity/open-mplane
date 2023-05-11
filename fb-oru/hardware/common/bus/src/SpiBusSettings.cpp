/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiBusSettings.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SpiBusSettings.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SpiBusSettings::SpiBusSettings() :
	BusSettings(),
	mSpeedHz(0),
	mMode(ISpiBusSettings::SPI_MODE0)
{
}

//-------------------------------------------------------------------------------------------------------------
SpiBusSettings::~SpiBusSettings()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned SpiBusSettings::speedHz() const
{
	return mSpeedHz ;
}

//-------------------------------------------------------------------------------------------------------------
ISpiBusSettings::SpiMode SpiBusSettings::mode() const
{
	return mMode ;
}

//-------------------------------------------------------------------------------------------------------------
bool SpiBusSettings::setSpeedHz(unsigned speedHz)
{
	mSpeedHz = speedHz ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SpiBusSettings::setMode(ISpiBusSettings::SpiMode mode)
{
	mMode = mode ;
	return true ;
}

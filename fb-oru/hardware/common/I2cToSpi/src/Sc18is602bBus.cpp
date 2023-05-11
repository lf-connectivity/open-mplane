/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Sc18is602bBus.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Sc18is602bBus.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Sc18is602bBus::Sc18is602bBus(std::shared_ptr<II2cBus> i2c, std::shared_ptr<IBusReadonlySettings> busSettings, unsigned spiSelect) :
	I2cToSpiBus(i2c, busSettings, spiSelect)
{
}

//-------------------------------------------------------------------------------------------------------------
Sc18is602bBus::~Sc18is602bBus()
{
}

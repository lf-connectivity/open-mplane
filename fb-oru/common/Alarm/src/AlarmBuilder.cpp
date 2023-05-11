/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AlarmBuilder.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "AlarmBuilder.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::AlarmBuilder::AlarmBuilder()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::AlarmBuilder::~AlarmBuilder()
{
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::AlarmBuilder::addAlarmPackage(std::shared_ptr<IAlarmPackage> package)
{
	// actually does nothing because the alarms will be stored in the IAlarmsList
}

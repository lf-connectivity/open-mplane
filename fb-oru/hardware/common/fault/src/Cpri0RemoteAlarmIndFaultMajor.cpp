/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri0RemoteAlarmIndFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Cpri0RemoteAlarmIndFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Cpri0RemoteAlarmIndicationFaultMajor::NAME="Cpri0RemoteAlarmIndMajorFault";
//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri0RemoteAlarmIndicationFaultMajor::Cpri0RemoteAlarmIndicationFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri0RemoteAlarmIndicationFaultMajor::~Cpri0RemoteAlarmIndicationFaultMajor()
{
}

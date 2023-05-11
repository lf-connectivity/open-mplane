/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri1RemoteAlarmIndFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Cpri1RemoteAlarmIndFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Cpri1RemoteAlarmIndicationFaultMajor::NAME="Cpri1RemoteAlarmIndMajorFault";
//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri1RemoteAlarmIndicationFaultMajor::Cpri1RemoteAlarmIndicationFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri1RemoteAlarmIndicationFaultMajor::~Cpri1RemoteAlarmIndicationFaultMajor()
{
}

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

#include "Cpri0SapDefectIndFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Cpri0SapDefectIndFaultMajor::NAME="Cpri0SapDefectIndMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri0SapDefectIndFaultMajor::Cpri0SapDefectIndFaultMajor() :
	Fault(3, 3, NAME )
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri0SapDefectIndFaultMajor::~Cpri0SapDefectIndFaultMajor()
{
}

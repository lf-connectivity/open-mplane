/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri0LossOfSignalFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Cpri0LossOfSignalFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Cpri0LossOfSignalFaultMajor::NAME="Cpri0LossOfSignalMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri0LossOfSignalFaultMajor::Cpri0LossOfSignalFaultMajor() :
	Fault(6, 6, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri0LossOfSignalFaultMajor::~Cpri0LossOfSignalFaultMajor()
{
}

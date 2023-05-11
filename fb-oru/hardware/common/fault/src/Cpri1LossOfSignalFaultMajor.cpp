/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri1LossOfSignalFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Cpri1LossOfSignalFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Cpri1LossOfSignalFaultMajor::NAME="Cpri1LossOfSignalMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri1LossOfSignalFaultMajor::Cpri1LossOfSignalFaultMajor() :
	Fault(6, 6, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri1LossOfSignalFaultMajor::~Cpri1LossOfSignalFaultMajor()
{
}

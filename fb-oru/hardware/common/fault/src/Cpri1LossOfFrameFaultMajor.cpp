/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri1LossOfFrameFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Cpri1LossOfFrameFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Cpri1LossOfFrameFaultMajor::NAME="Cpri1LossOfFrameMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri1LossOfFrameFaultMajor::Cpri1LossOfFrameFaultMajor() :
	Fault(6, 6, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri1LossOfFrameFaultMajor::~Cpri1LossOfFrameFaultMajor()
{
}

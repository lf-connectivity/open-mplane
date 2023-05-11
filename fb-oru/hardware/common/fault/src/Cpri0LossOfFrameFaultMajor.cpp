/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri0LossOfFrameFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Cpri0LossOfFrameFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Cpri0LossOfFrameFaultMajor::NAME="Cpri0LossOfFrameMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri0LossOfFrameFaultMajor::Cpri0LossOfFrameFaultMajor() :
	Fault(6, 6, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Cpri0LossOfFrameFaultMajor::~Cpri0LossOfFrameFaultMajor()
{
}

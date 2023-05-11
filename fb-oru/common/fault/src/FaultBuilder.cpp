/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultBuilder.cpp
 * \brief     Creates and stores IFaultPackage objects (creating the faults for the application)
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FaultBuilder.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::FaultBuilder::FaultBuilder()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::FaultBuilder::~FaultBuilder()
{
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::FaultBuilder::addFaultPackage(std::shared_ptr<IFaultPackage> package)
{
	mPackages.push_back(package) ;
}

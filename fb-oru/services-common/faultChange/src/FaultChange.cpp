/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FaultChange.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FaultChange.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FaultChange::FaultChange() : mFaultName("")
{
}

//-------------------------------------------------------------------------------------------------------------
FaultChange::~FaultChange()
{
	// Base class destructor, that actually does something will automatically be called.
}


//-------------------------------------------------------------------------------------------------------------
const std::string& FaultChange::getFaultName( void )
{
	Mutex::Lock lock(mMutex) ;

	return mFaultName;
}

//-------------------------------------------------------------------------------------------------------------
void FaultChange::setFaultName( const std::string& faultName )
{
	Mutex::Lock lock(mMutex) ;

	mFaultName = faultName;
}

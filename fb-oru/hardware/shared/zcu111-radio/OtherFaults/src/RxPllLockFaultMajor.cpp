/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxPllLockFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RxPllLockFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::RxPllLockFaultMajor::NAME="RxPllLockMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::RxPllLockFaultMajor::RxPllLockFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::RxPllLockFaultMajor::~RxPllLockFaultMajor()
{
}

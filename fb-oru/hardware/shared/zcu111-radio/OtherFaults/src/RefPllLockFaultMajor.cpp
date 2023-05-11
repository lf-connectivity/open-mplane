/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RefPllLockFaultMajor.cpp
 * \brief     Reference clock PLL Lock fault major
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "RefPllLockFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::RefPllLockFaultMajor::NAME="RefPllLockMajorFault";
//-------------------------------------------------------------------------------------------------------------
Mplane::RefPllLockFaultMajor::RefPllLockFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::RefPllLockFaultMajor::~RefPllLockFaultMajor()
{
}

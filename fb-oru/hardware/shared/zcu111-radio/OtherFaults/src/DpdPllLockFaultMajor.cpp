/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdPllLockFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DpdPllLockFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::DpdPllLockFaultMajor::NAME="DpdPllLockMajorFault";
//-------------------------------------------------------------------------------------------------------------
Mplane::DpdPllLockFaultMajor::DpdPllLockFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdPllLockFaultMajor::~DpdPllLockFaultMajor()
{
}

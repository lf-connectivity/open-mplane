/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxPllLockFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxPllLockFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::TxPllLockFaultMajor::NAME="TxPllLockMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::TxPllLockFaultMajor::TxPllLockFaultMajor() :
	Fault(3, 3, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::TxPllLockFaultMajor::~TxPllLockFaultMajor()
{
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SrlTxFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "SrlTxFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::SrlTx1FaultMajor::NAME="SrlTx1MajorFault";

const char* Mplane::SrlTx2FaultMajor::NAME="SrlTx2MajorFault";

const char* Mplane::SrlTx3FaultMajor::NAME="SrlTx3MajorFault";

const char* Mplane::SrlTx4FaultMajor::NAME="SrlTx4MajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::SrlTx1FaultMajor::SrlTx1FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SrlTx1FaultMajor::~SrlTx1FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SrlTx2FaultMajor::SrlTx2FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SrlTx2FaultMajor::~SrlTx2FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SrlTx3FaultMajor::SrlTx3FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SrlTx3FaultMajor::~SrlTx3FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SrlTx4FaultMajor::SrlTx4FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::SrlTx4FaultMajor::~SrlTx4FaultMajor()
{
}

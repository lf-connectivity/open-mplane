/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      VswrTxFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "VswrTxFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::VswrTx1FaultMajor::NAME="VswrTx1MajorFault";

const char* Mplane::VswrTx2FaultMajor::NAME="VswrTx2MajorFault";

const char* Mplane::VswrTx3FaultMajor::NAME="VswrTx3MajorFault";

const char* Mplane::VswrTx4FaultMajor::NAME="VswrTx4MajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::VswrTx1FaultMajor::VswrTx1FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::VswrTx1FaultMajor::~VswrTx1FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::VswrTx2FaultMajor::VswrTx2FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::VswrTx2FaultMajor::~VswrTx2FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::VswrTx3FaultMajor::VswrTx3FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::VswrTx3FaultMajor::~VswrTx3FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::VswrTx4FaultMajor::VswrTx4FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::VswrTx4FaultMajor::~VswrTx4FaultMajor()
{
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PopTripTxFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PopTripTxFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::PopTripTx1FaultMajor::NAME="PopTripTx1MajorFault";

const char* Mplane::PopTripTx2FaultMajor::NAME="PopTripTx2MajorFault";

const char* Mplane::PopTripTx3FaultMajor::NAME="PopTripTx3MajorFault";

const char* Mplane::PopTripTx4FaultMajor::NAME="PopTripTx4MajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::PopTripTx1FaultMajor::PopTripTx1FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PopTripTx1FaultMajor::~PopTripTx1FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PopTripTx2FaultMajor::PopTripTx2FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PopTripTx2FaultMajor::~PopTripTx2FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PopTripTx3FaultMajor::PopTripTx3FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PopTripTx3FaultMajor::~PopTripTx3FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PopTripTx4FaultMajor::PopTripTx4FaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PopTripTx4FaultMajor::~PopTripTx4FaultMajor()
{
}

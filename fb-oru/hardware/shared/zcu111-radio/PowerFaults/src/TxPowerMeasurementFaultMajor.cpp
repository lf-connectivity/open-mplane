/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxOverpowerFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxPowerMeasurementFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::Tx1PowerMeasurementFaultMajor::NAME="Tx1PowerMeasurementMajorFault";

const char* Mplane::Tx2PowerMeasurementFaultMajor::NAME="Tx2PowerMeasurementMajorFault";

const char* Mplane::Tx3PowerMeasurementFaultMajor::NAME="Tx3PowerMeasurementMajorFault";

const char* Mplane::Tx4PowerMeasurementFaultMajor::NAME="Tx4PowerMeasurementMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx1PowerMeasurementFaultMajor::Tx1PowerMeasurementFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx1PowerMeasurementFaultMajor::~Tx1PowerMeasurementFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx2PowerMeasurementFaultMajor::Tx2PowerMeasurementFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx2PowerMeasurementFaultMajor::~Tx2PowerMeasurementFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx3PowerMeasurementFaultMajor::Tx3PowerMeasurementFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx3PowerMeasurementFaultMajor::~Tx3PowerMeasurementFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx4PowerMeasurementFaultMajor::Tx4PowerMeasurementFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::Tx4PowerMeasurementFaultMajor::~Tx4PowerMeasurementFaultMajor()
{
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PclTxConvergenceFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "PclTxConvergenceFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::PclTx1ConvergenceFaultMajor::NAME="PclTx1ConvergenceMajorFault";

const char* Mplane::PclTx2ConvergenceFaultMajor::NAME="PclTx2ConvergenceMajorFault";

const char* Mplane::PclTx3ConvergenceFaultMajor::NAME="PclTx3ConvergenceMajorFault";

const char* Mplane::PclTx4ConvergenceFaultMajor::NAME="PclTx4ConvergenceMajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx1ConvergenceFaultMajor::PclTx1ConvergenceFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx1ConvergenceFaultMajor::~PclTx1ConvergenceFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx2ConvergenceFaultMajor::PclTx2ConvergenceFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx2ConvergenceFaultMajor::~PclTx2ConvergenceFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx3ConvergenceFaultMajor::PclTx3ConvergenceFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx3ConvergenceFaultMajor::~PclTx3ConvergenceFaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx4ConvergenceFaultMajor::PclTx4ConvergenceFaultMajor() :
	Fault(1, 1, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::PclTx4ConvergenceFaultMajor::~PclTx4ConvergenceFaultMajor()
{
}

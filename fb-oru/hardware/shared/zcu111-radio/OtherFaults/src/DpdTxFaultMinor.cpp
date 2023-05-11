/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdTxFaultMinor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DpdTxFaultMinor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::DpdTx1FaultMinor::NAME="DpdTx1MinorFault";

const char* Mplane::DpdTx2FaultMinor::NAME="DpdTx2MinorFault";

const char* Mplane::DpdTx3FaultMinor::NAME="DpdTx3MinorFault";

const char* Mplane::DpdTx4FaultMinor::NAME="DpdTx4MinorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx1FaultMinor::DpdTx1FaultMinor() :
	Fault(6, 6, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx1FaultMinor::~DpdTx1FaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx2FaultMinor::DpdTx2FaultMinor() :
	Fault(6, 6, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx2FaultMinor::~DpdTx2FaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx3FaultMinor::DpdTx3FaultMinor() :
	Fault(6, 6, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx3FaultMinor::~DpdTx3FaultMinor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx4FaultMinor::DpdTx4FaultMinor() :
	Fault(6, 6, NAME)
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx4FaultMinor::~DpdTx4FaultMinor()
{
}

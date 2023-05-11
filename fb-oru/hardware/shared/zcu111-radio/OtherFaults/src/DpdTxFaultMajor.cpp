/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdTxFaultMajor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "DpdTxFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* Mplane::DpdTx1FaultMajor::NAME="DpdTx1MajorFault";

const char* Mplane::DpdTx2FaultMajor::NAME="DpdTx2MajorFault";

const char* Mplane::DpdTx3FaultMajor::NAME="DpdTx3MajorFault";

const char* Mplane::DpdTx4FaultMajor::NAME="DpdTx4MajorFault";

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx1FaultMajor::DpdTx1FaultMajor() :
	Fault(6, 6, NAME )
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx1FaultMajor::~DpdTx1FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx2FaultMajor::DpdTx2FaultMajor() :
	Fault(6, 6, NAME )
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx2FaultMajor::~DpdTx2FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx3FaultMajor::DpdTx3FaultMajor() :
	Fault(6, 6, NAME )
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx3FaultMajor::~DpdTx3FaultMajor()
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx4FaultMajor::DpdTx4FaultMajor() :
	Fault(6, 6, NAME )
{
}

//-------------------------------------------------------------------------------------------------------------
Mplane::DpdTx4FaultMajor::~DpdTx4FaultMajor()
{
}

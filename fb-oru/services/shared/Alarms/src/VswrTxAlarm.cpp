/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      VswrTxAlarm.cpp
 * \brief     VswrTx alarms
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "VswrTxFaultMajor.h"
#include "VswrTxAlarm.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

const char* VswrTx1Alarm::NAME="VswrTx1Alarm";

const char* VswrTx2Alarm::NAME="VswrTx2Alarm";

const char* VswrTx3Alarm::NAME="VswrTx3Alarm";

const char* VswrTx4Alarm::NAME="VswrTx4Alarm";

//-------------------------------------------------------------------------------------------------------------
VswrTx1Alarm::VswrTx1Alarm() :
		Alarm(VswrTx1Alarm::NAME, "VSWR exceeded permitted value on path TX 1")
{
    registerFault(VswrTx1FaultMajor::NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
VswrTx1Alarm::~VswrTx1Alarm()
{
}

//-------------------------------------------------------------------------------------------------------------
VswrTx2Alarm::VswrTx2Alarm() :
		Alarm(VswrTx2Alarm::NAME, "VSWR exceeded permitted value on path TX 2")
{
    registerFault(VswrTx2FaultMajor::NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
VswrTx2Alarm::~VswrTx2Alarm()
{
}

//-------------------------------------------------------------------------------------------------------------
VswrTx3Alarm::VswrTx3Alarm() :
		Alarm(VswrTx3Alarm::NAME, "VSWR exceeded permitted value on path TX 3")
{
    registerFault(VswrTx3FaultMajor::NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
VswrTx3Alarm::~VswrTx3Alarm()
{
}

//-------------------------------------------------------------------------------------------------------------
VswrTx4Alarm::VswrTx4Alarm() :
		Alarm(VswrTx4Alarm::NAME, "VSWR exceeded permitted value on path TX 4")
{
    registerFault(VswrTx4FaultMajor::NAME) ;
}

//-------------------------------------------------------------------------------------------------------------
VswrTx4Alarm::~VswrTx4Alarm()
{
}

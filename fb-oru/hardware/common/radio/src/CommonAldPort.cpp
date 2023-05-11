/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAldPort.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "CommonAldPort.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonAldPort::CommonAldPort(int index, const char* name, std::shared_ptr<Hdlc> hdlc):
    CommonPort( index, name),
	mDcPowerStatus(false),
	mOverCurrentCb(),
    mHdlc( hdlc )
{
}

//-------------------------------------------------------------------------------------------------------------
CommonAldPort::~CommonAldPort()
{
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<Hdlc> CommonAldPort::getHdlc(void)
{
	return mHdlc ;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonAldPort::isDCPowerControlSupported(void)
{
	// By default the power control is available
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonAldPort::isDCPowerOn(void)
{
	return mDcPowerStatus;
}

//-------------------------------------------------------------------------------------------------------------
void CommonAldPort::setDCPower(bool status)
{
	mDcPowerStatus = status;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonAldPort::isOvercurrentDetectionSupported(void)
{
	// By default overcurrent detection is supported
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void CommonAldPort::registerOvercurrentCb(OverCurrentFuncCb cb)
{
	mOverCurrentCb.push_back(cb);
}

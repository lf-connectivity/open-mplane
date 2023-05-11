/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CUPlaneConnectService.cpp
 * \brief     ORAN C/U-Plane Connectivity Service
 *
 *
 * \details   Responsible for monitoring each logical C/U-plane connection associated
 *            with a processing element using a watchdog timer.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>

#include "CUPlaneConnectService.h"

using namespace Mplane;

//=============================================================================================================
// DEFINITIONS
//=============================================================================================================

//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// STATIC
//=============================================================================================================
std::map<CUPlaneConnectService::ServiceState_T, std::string> CUPlaneConnectService::mStateStr =
{
	{ ServiceState_T::DISABLED, "DISABLED" },
	{ ServiceState_T::RUNNING,  "RUNNING"  },
	{ ServiceState_T::FAULT,    "FAULT"    },
};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CUPlaneConnectService::CUPlaneConnectService()
	: Service(SERVICE_LOW_PRIORITY,
	          SMALL_STACK,
	          1, // update stuff every 1 msec
	          "CUPlaneConnectService",
	          "YANG")
	, mState(ServiceState_T::DISABLED)
{
}

//-------------------------------------------------------------------------------------------------------------
CUPlaneConnectService::~CUPlaneConnectService()
{
}

//-------------------------------------------------------------------------------------------------------------
// Called by mgr when o-ran-supervision a RPC is received
ReturnType::State CUPlaneConnectService::addConnection(uint16_t id, uint16_t monitoringInterval)
{
	ReturnType::State returnValue = ReturnType::RT_ERROR;

	// Service is now running
	setState(ServiceState_T::RUNNING);
	returnValue = ReturnType::RT_OK;

	return returnValue;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CUPlaneConnectService::removeConnection(uint16_t id)
{
	ReturnType::State returnValue = ReturnType::RT_ERROR;

	returnValue = ReturnType::RT_OK;

	return returnValue;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CUPlaneConnectService::setState(ServiceState_T state)
{
	if (state != mState)
	{
		eventInfo("%s[%s]: Previous [%s]", getName(), mStateStr[state].c_str(), mStateStr[mState].c_str());
	}
	state = mState;
}

//-------------------------------------------------------------------------------------------------------------
void CUPlaneConnectService::show()
{
	eventInfo("%s[%s]: Show", getName(), mStateStr[mState].c_str());
}

//-------------------------------------------------------------------------------------------------------------
int CUPlaneConnectService::service()
{
	eventInfo("%s[%s]: Servicing", getName(), mStateStr[mState].c_str());

	if(mState == ServiceState_T::RUNNING)
	{
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
void CUPlaneConnectService::doReset()
{
	eventInfo("%s[%s]: Reset", getName(), mStateStr[mState].c_str());
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

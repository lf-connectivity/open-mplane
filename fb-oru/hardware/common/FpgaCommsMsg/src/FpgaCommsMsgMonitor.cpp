/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgMonitor.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FpgaCommsMsgMonitor.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgMonitor::FpgaCommsMsgMonitor(const std::string& monitorVariableName, MsgMonitorCallback callback) :
	TaskEvent(Task::PRIORITY_MEDIUM, Task::SMALL_STACK,
		"MsgMonitor" + monitorVariableName, "MsgMon"),
	mMonitorVariable(monitorVariableName),
	mCallback(callback),
	mMutex(),
	mMessages()
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgMonitor::~FpgaCommsMsgMonitor()
{
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsMsgMonitor::handleMsg(std::shared_ptr<IFpgaMsg> msg)
{
	Mutex::Lock lock(mMutex) ;
	mMessages.push(msg) ;
	event() ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsMsgMonitor::runEvent()
{
	std::shared_ptr<IFpgaMsg> msg ;
	do
	{
		// get data
		msg.reset() ;
		{
			Mutex::Lock lock(mMutex) ;
			if (!mMessages.empty())
			{
				msg = mMessages.front() ;
				mMessages.pop() ;
			}
		}

		// Handle data
		if (!msg)
			continue ;

		std::map<std::string, DataVariant> attributes(msg->getAttributes()) ;
		auto entry(attributes.find(mMonitorVariable)) ;
		if (entry == attributes.end())
			continue ;

		// got variable entry so run callback
		mCallback(attributes) ;

	} while(msg) ;

	return true ;
}

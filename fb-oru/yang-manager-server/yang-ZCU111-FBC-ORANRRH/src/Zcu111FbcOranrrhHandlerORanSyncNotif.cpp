 /*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanSyncNotif.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <algorithm>
#include <string>

#include "stringfunc.hpp"
#include "YangParamUtils.h"

#include "RadioDatastoreSysrepo.h"
#include "Zcu111FbcOranrrhHandlerORanSyncNotif.h"

using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanSyncNotif::Zcu111FbcOranrrhHandlerORanSyncNotif(ISendNotification* notifier, std::string path)
	: TaskEvent(Task::PRIORITY_DEFAULT, Task::StackSize::SMALL_STACK, "OranSyncNotification", "SyncNotif"),
	  mLinuxPtp(ILinuxPtp::singleton()),
	  mNotifier(notifier),
	  mPath(path)
{
	mPtpLockStatus = ILinuxPtp::LockStatus_T::NOT_LOCKED;
	mPrevPtpLockStatus = mPtpLockStatus;
	mAirframeLockStatus = ILinuxPtp::LockStatus_T::NOT_LOCKED;
	mPrevAirframeLockStatus = mAirframeLockStatus;
	mSynceLockStatus = ILinuxPtp::LockStatus_T::NOT_LOCKED;
	mPrevSynceLockStatus = mSynceLockStatus;

	// Send notifications if PTP status changes
	mLinuxPtp->registerPtpStatusFunc([this](ILinuxPtp::LockStatus_T lockStatus)
	{
		mPtpLockStatus = lockStatus;
		event();
	}) ;

	// Send notifications if sync status changes
	mLinuxPtp->registerAirframeStatusFunc([this](ILinuxPtp::LockStatus_T lockStatus)
	{
		mAirframeLockStatus = lockStatus;
		event();
	}) ;

	// Send notifications if synce status changes
	mLinuxPtp->registerSynceStatusFunc([this](ILinuxPtp::LockStatus_T lockStatus)
	{
		mSynceLockStatus = lockStatus;
		event();
	}) ;

}

//-------------------------------------------------------------------------------------------------------------
Zcu111FbcOranrrhHandlerORanSyncNotif::~Zcu111FbcOranrrhHandlerORanSyncNotif()
{
}
//=============================================================================================================
// PROTECTED
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerORanSyncNotif::runEvent()
{
	// Send notification if PTP status has changed
	if (mPtpLockStatus != mPrevPtpLockStatus)
	{
		mPrevPtpLockStatus = mPtpLockStatus;

		std::string notifPath( mPath + "ptp-state-change" ) ;
		std::string ptpStatePath( notifPath + "/ptp-state" ) ;

		std::string value = (mPtpLockStatus == ILinuxPtp::LockStatus_T::LOCKED) ? "LOCKED" : "UNLOCKED";
		std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;
		params->addParam(value, ptpStatePath) ;

		eventInfo("Sending notification for ptp-state = %s", value.c_str());
		mNotifier->sendNotification(notifPath, params) ;
	}

	// Send notification if airframe status has changed
	if (mAirframeLockStatus != mPrevAirframeLockStatus)
	{
		mPrevAirframeLockStatus = mAirframeLockStatus;

		std::string notifPath( mPath + "synchronization-state-change" ) ;
		std::string syncStatePath( notifPath + "/sync-state" ) ;

		std::string value = (mAirframeLockStatus == ILinuxPtp::LockStatus_T::LOCKED) ? "LOCKED" : "FREERUN";
		std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;
		params->addParam(value,	syncStatePath) ;

		eventInfo("Sending notification for sync-state = %s", value.c_str());
		mNotifier->sendNotification(notifPath, params) ;
	}

	// Send notification if synce status has changed
	if (mSynceLockStatus != mPrevSynceLockStatus)
	{
		mPrevSynceLockStatus = mSynceLockStatus;

		std::string notifPath( mPath + "synce-state-change" ) ;
		std::string synceStatePath( notifPath + "/synce-state" ) ;

		std::string value = (mSynceLockStatus == ILinuxPtp::LockStatus_T::LOCKED) ? "LOCKED" : "UNLOCKED";
		std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;
		params->addParam(value,	synceStatePath) ;

		eventInfo("Sending notification for synce-state = %s", value.c_str());
		mNotifier->sendNotification(notifPath, params) ;
	}

	return true;
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhHandlerORanSyncNotif.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANSYNCNOTIF_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANSYNCNOTIF_H_

#include "ILinuxPtpService.h"
#include "TaskEvent.h"
#include "ISendNotification.h"

namespace Mplane
{

/*!
 * \class  Zcu111FbcOranrrhHandlerORanSyncNotif
 * \brief
 * \details
 *
 */
class Zcu111FbcOranrrhHandlerORanSyncNotif : public TaskEvent
{
public:
	//using LockStatusChangeFunc = std::function< void(ILinuxPtp::LockStatus_T) > ;

	Zcu111FbcOranrrhHandlerORanSyncNotif(ISendNotification* notifier, std::string path);
	virtual ~Zcu111FbcOranrrhHandlerORanSyncNotif();

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:

	std::shared_ptr<ILinuxPtp> mLinuxPtp;
	ISendNotification* mNotifier;
	std::string mPath;
	ILinuxPtp::LockStatus_T mPtpLockStatus;
	ILinuxPtp::LockStatus_T mPrevPtpLockStatus;
	ILinuxPtp::LockStatus_T mAirframeLockStatus;
	ILinuxPtp::LockStatus_T mPrevAirframeLockStatus;
	ILinuxPtp::LockStatus_T mSynceLockStatus;
	ILinuxPtp::LockStatus_T mPrevSynceLockStatus;
};

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_ZCU111FBCORANRRHHANDLERORANSYNCNOTIF_H_ */

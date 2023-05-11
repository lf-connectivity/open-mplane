/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgMonitor.h
 * \brief     Monitor messages for specific data
 *
 *
 * \details   Monitors all messages for the presence of a specific variable. Calls a user callback with the
 * 				message if the variable is present
 *
 */


#ifndef FPGACOMMSMSGMONITOR_H_
#define FPGACOMMSMSGMONITOR_H_

#include <map>
#include <string>
#include <memory>
#include <queue>
#include <functional>

#include "DataVariant.h"
#include "Mutex.h"
#include "TaskEvent.h"

#include "IFpgaMsg.h"

namespace Mplane {

class FpgaCommsMsgMonitor : public TaskEvent {
public:
	using MsgMonitorCallback = std::function<void(std::map<std::string, DataVariant>)> ;


	FpgaCommsMsgMonitor(const std::string& monitorVariableName, MsgMonitorCallback callback) ;
	virtual ~FpgaCommsMsgMonitor() ;

	/**
	 * Handle a new message
	 * @param msg
	 */
	void handleMsg(std::shared_ptr<IFpgaMsg> msg) ;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
	std::string			mMonitorVariable ;
	MsgMonitorCallback 	mCallback ;
	Mutex				mMutex ;

	std::queue< std::shared_ptr<IFpgaMsg> >	mMessages ;
} ;

}

#endif /* FPGACOMMSMSGMONITOR_H_ */

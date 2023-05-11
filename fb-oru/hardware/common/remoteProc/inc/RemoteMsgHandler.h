/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteMsgHandler.h
 * \brief     Remote processor message handler
 *
 *
 * \details   Handles the messages to/from remote processor
 *
 */


#ifndef _REMOTEMSGHANDLER_H_
#define _REMOTEMSGHANDLER_H_

#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "RemoteMsgHandlerBase.h"
#include "RemoteMsg.h"

namespace Mplane {

class RemoteProc ;
class RpmsgMgr ;

/*!
 * \class  RemoteMsgHandler
 * \brief
 * \details
 *
 */
class RemoteMsgHandler : public RemoteMsgHandlerBase {
public:
	RemoteMsgHandler(unsigned index, std::shared_ptr<IFpgaMsgTokens> tokens) ;
	virtual ~RemoteMsgHandler() ;

	/**
	 * Load the remote processor with the specified firmware, start it up, and connect up the channel
	 */
	virtual bool connect(const std::string& firmware) override ;

	/**
	 * Shutdown the remote processor
	 */
	virtual bool disconnect() override ;

	/**
	 * Send a command string to the remote processor
	 */
	virtual bool sendCommand(const std::string& cmd,
			const std::vector<DataVariant>& attributes,
			const std::set<std::string>& varNames,
			std::vector<DataVariant>& replyAttributes,
			unsigned timeoutMs) override ;

	/**
	 * Either start or stop the processor
	 */
	virtual bool procSetState(bool start) override ;

	/**
	 * get the current processor state
	 */
	virtual int procState() override ;



protected:
	/**
	 * Derived classes override this function. Returns non-zero on error
	 */
	virtual int eventLoopFunc() override ;


private:
	bool processRpc() ;
	bool handleOpen() ;
	bool handleClose() ;
	bool handleWrite() ;
	bool handleRead() ;
protected:
	bool read(unsigned timeoutMs, bool& timedOut) ;
	int fd() ;

private:
	std::shared_ptr<RpmsgMgr> mRpmsgMgr ;
	std::shared_ptr<RemoteProc> mProc ;
	int mFd ;
	int mPipeWrFd ;
	int mPipeRdFd ;

	std::mutex mMsgMutex ;

	// Buffering for commands from remote proc and replies back
	RemoteMsg mRpc ;
	RemoteMsg mRpcResponse ;

	// Buffering for commands from this host and replies
	RemoteMsg mCmd ;
	RemoteMsg mCmdReply ;
	std::atomic<bool> mGotReply ;
	std::condition_variable mReplyCv ;
} ;

}

#endif /* _REMOTEMSGHANDLER_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteMsgHandlerBase.h
 * \brief     Common base class for any IRemoteMsgHandler classes
 *
 *
 * \details   Common base class for any IRemoteMsgHandler classes
 *
 */


#ifndef COMMON_REMOTEPROC_INC_REMOTEMSGHANDLERBASE_H_
#define COMMON_REMOTEPROC_INC_REMOTEMSGHANDLERBASE_H_

#include <functional>
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "Task.h"
#include "IRemoteMsgHandler.h"
#include "IFpgaMsgTokens.h"
#include "IHostFileMgr.h"

namespace Mplane {

/*!
 * \class  RemoteMsgHandlerBase
 * \brief
 * \details
 *
 */
class RemoteMsgHandlerBase : public virtual IRemoteMsgHandler, public Task {
public:
	RemoteMsgHandlerBase(unsigned index, std::shared_ptr<IFpgaMsgTokens> tokens) ;
	virtual ~RemoteMsgHandlerBase() ;

	/**
	 * Is the handler running?
	 */
	virtual bool isActive() const override ;

	/**
	 * Is the event loop running?
	 */
	virtual bool isEventLoop() const override ;

	/**
	 * Get any error string
	 */
	virtual std::string error() override ;


	/**
	 * Start/stop the event loop handling messages from the processor
	 */
	virtual bool eventLoop(bool start) override ;

	/**
	 * Either start or stop the processor
	 */
	virtual bool procSetState(bool start) override ;

	/**
	 * get the current processor state
	 */
	virtual int procState() override ;

	/**
	 * Get the file manager for this handler
	 */
	virtual std::shared_ptr<IHostFileMgr> fileMgr() override ;


	/**
	 * Register a callback for when a command is received
	 */
	virtual void registerCmdReceivedFunc(CommandReceivedFunc func) override ;

	/**
	 * Register a callback for when an event PDU is received
	 */
	virtual void registerEventFunc(EventFunc func) override ;

	/**
	 * Register a callback for when an alarm PDU is received
	 */
	virtual void registerAlarmFunc(AlarmFunc func) override ;


protected:
	unsigned index() const ;
	void setActive(bool active) ;
	std::vector<uint8_t> cmdBytes(const std::string &cmd,
			const std::vector<DataVariant> &attributes,
			const std::set<std::string> &varNames) ;
	void reply(const uint8_t* replyBytes, unsigned replyLen,
			std::vector<DataVariant> &replyAttributes) ;

	bool setError(const std::string& error) ;
	void setCmd(const std::string& cmd) ;

	// call the event callback - input is whole PDU
	void callEventCallback(uint8_t *pdu, unsigned pdu_len) ;

	// call the alarm callback - input is whole pdu
	void callAlarmCallback(uint8_t *pdu, unsigned pdu_len) ;

protected:
    /**
     * This is the method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     * @return the exit status of task process
     */
    virtual int run() override ;

	/**
	 * Derived classes override this function. Returns non-zero on error
	 */
	virtual int eventLoopFunc() ;



private:
	unsigned mIndex ;
	std::string mError ;
	bool mActive ;
	std::shared_ptr<IHostFileMgr> mFileMgr ;
	std::shared_ptr<IFpgaMsgTokens> mTokens ;

	std::mutex mMutex ;
	std::atomic<bool> mStartEventLoop ;
	std::atomic<bool> mEventLoopActive ;
	std::atomic<bool> mExit ;
	std::condition_variable mEventLoopCv ;

	CommandReceivedFunc mCommandReceivedFunc ;
	EventFunc mEventFunc ;
	AlarmFunc mAlarmFunc ;

} ;

}

#endif /* COMMON_REMOTEPROC_INC_REMOTEMSGHANDLERBASE_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteMsgHandlerBase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>
#include "ByteTransfer.hpp"

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "HostFileMgr.h"
#include "FpgaPdu.h"
#include "RemoteCommsMsgCmd.h"
#include "RemoteCommsMsgReply.h"
#include "RemoteMsgHandlerShim.h"

#include "RemoteMsgHandlerBase.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RemoteMsgHandlerBase::RemoteMsgHandlerBase(unsigned index, std::shared_ptr<IFpgaMsgTokens> tokens) :
	Task(Task::PRIORITY_DEFAULT, Task::DEFAULT_STACK, std::string("RemoteMsgHandler" + std::to_string(index)).c_str(), "RemoteProc"),
	mIndex(index),
	mError(""),
	mActive(false),
	mFileMgr( std::make_shared<HostFileMgr>() ),
	mTokens(tokens),
	mMutex(),
	mStartEventLoop(false),
	mEventLoopActive(false),
	mExit(false),
	mEventLoopCv(),
	mCommandReceivedFunc(),
	mEventFunc(),
	mAlarmFunc()


{
//	std::cerr << "NEW RemoteMsgHandlerBase @ " << (void*)this << " file mgr use=" << mFileMgr.use_count() << " @ " << mFileMgr.get() << std::endl ;
	this->Task::start() ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteMsgHandlerBase::~RemoteMsgHandlerBase()
{
//	std::cerr << "DEL RemoteMsgHandlerBase @ " << (void*)this << " file mgr use=" << mFileMgr.use_count() << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerBase::isActive() const
{
	return mActive ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerBase::isEventLoop() const
{
	return mEventLoopActive ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerBase::eventLoop(bool start)
{
//std::cerr << "RemoteMsgHandlerBase::eventLoop() @ " << (void*)this << " start=" << start << " (mActive=" << mActive << ")" << std::endl ;

	if (!mActive)
		return setError("Not active") ;

	// skip if already at this state
	if (mStartEventLoop == start)
		return true ;

	// change state
	{
	std::unique_lock<std::mutex> lock(mMutex) ;
	mStartEventLoop = start;
	mEventLoopCv.notify_all() ;
	}

	// wait until state changed (or timed out)
	for (unsigned timer=0; timer < 10; ++timer)
	{
		if (start == mEventLoopActive)
			break ;

		Task::msSleep(100) ;
	}

//std::cerr << "RemoteMsgHandlerBase::eventLoop() start=" << start << " mEventLoopActive=" << mEventLoopActive << std::endl ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RemoteMsgHandlerBase::error()
{
	std::string err ;
	using std::swap ;
	swap(err, mError) ;
	return err ;
}


//-------------------------------------------------------------------------------------------------------------
void RemoteMsgHandlerBase::registerCmdReceivedFunc(CommandReceivedFunc func)
{
	mCommandReceivedFunc = func ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteMsgHandlerBase::registerEventFunc(EventFunc func)
{
	mEventFunc = func ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteMsgHandlerBase::registerAlarmFunc(AlarmFunc func)
{
	mAlarmFunc = func ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
unsigned RemoteMsgHandlerBase::index() const
{
	return mIndex ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteMsgHandlerBase::setActive(bool active)
{
//std::cerr << "RemoteMsgHandlerBase::setActive() @ " << (void*)this << " active=" << active << " (mActive=" << mActive << ")" << std::endl ;
	mActive = active ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IHostFileMgr> RemoteMsgHandlerBase::fileMgr()
{
//	std::cerr << "RemoteMsgHandlerBase::fileMgr() @ " << (void*)this << " use=" << mFileMgr.use_count() << " @ " << mFileMgr.get() << std::endl ;
	return mFileMgr ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<uint8_t> RemoteMsgHandlerBase::cmdBytes(
		const std::string &cmd, const std::vector<DataVariant> &attributes,
		const std::set<std::string> &varNames)
{
	RemoteCommsMsgCmd msg(mTokens, cmd, attributes, varNames) ;
	std::shared_ptr<IFpgaPdu> pdu(msg.getPdu()) ;
	std::vector<uint8_t> pduBytes(pdu->getBytes()) ;

//std::cerr << "RemoteMsgHandlerBase::cmdBytes bytes:" << std::endl ;
//ByteTransfer::dump(pduBytes) ;
//std::cerr << "RemoteMsgHandlerBase::cmdBytes:" << msg.toString() << std::endl ;

	return pduBytes ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteMsgHandlerBase::reply(const uint8_t *replyBytes,
		unsigned replyLen, std::vector<DataVariant> &replyAttributes)
{
	replyAttributes.clear() ;

	std::vector<UINT8> bytes(replyBytes, replyBytes+replyLen) ;
	std::shared_ptr<IFpgaPdu> replyPdu(std::make_shared<FpgaPdu>(bytes)) ;

	RemoteCommsMsgReply replyMsg(mTokens, replyPdu) ;
	std::map<std::string, DataVariant> attrs(replyMsg.getAttributes()) ;
	for (auto& entry : attrs)
		replyAttributes.push_back(entry.second) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerBase::setError(const std::string &error)
{
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerBase::procSetState(bool start)
{
	// NO-OP
	(void)start;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandlerBase::procState()
{
	// NO-OP
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteMsgHandlerBase::setCmd(const std::string &cmd)
{
	if (mCommandReceivedFunc)
		mCommandReceivedFunc(cmd) ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteMsgHandlerBase::callEventCallback(uint8_t *pdu, unsigned pdu_len)
{
	if (!mEventFunc)
		return ;

	std::vector<UINT8> bytes(pdu, pdu+pdu_len) ;
	std::shared_ptr<IFpgaPdu> replyPdu(std::make_shared<FpgaPdu>(bytes)) ;

	RemoteCommsMsgReply replyMsg(mTokens, replyPdu) ;
	mEventFunc(replyMsg.toString(), replyMsg.getAttributes()) ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteMsgHandlerBase::callAlarmCallback(uint8_t *pdu, unsigned pdu_len)
{
	if (!mAlarmFunc)
		return ;

	std::vector<UINT8> bytes(pdu, pdu+pdu_len) ;
	std::shared_ptr<IFpgaPdu> replyPdu(std::make_shared<FpgaPdu>(bytes)) ;

	RemoteCommsMsgReply replyMsg(mTokens, replyPdu) ;
	mAlarmFunc(replyMsg.toString(), replyMsg.getAttributes()) ;
}

//=============================================================================================================
// PROTECTED THREAD
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandlerBase::run()
{
	//std::cerr << "RemoteMsgHandlerBase::run() @ " << (void*)this << " - START" << std::endl ;

	while(!mExit)
	{
		if (!mStartEventLoop)
		{
			mEventLoopActive = false ;

			std::unique_lock<std::mutex> lock(mMutex) ;
			while (!mExit && !mStartEventLoop)
				mEventLoopCv.wait(lock) ;
		}

		if (mExit)
			break ;

		// started event loop
		mEventLoopActive = true ;

		// Execute the loop method
		eventLoopFunc() ;
	}

	mEventLoopActive = false ;

	//std::cerr << "RemoteMsgHandlerBase::run() @ " << (void*)this << " - EXIT" << std::endl ;
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandlerBase::eventLoopFunc()
{
	// NO-OP
	return 0 ;
}

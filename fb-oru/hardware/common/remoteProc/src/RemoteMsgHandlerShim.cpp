/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteMsgHandlerShim.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "ByteTransfer.hpp"
#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string.h>

#include "FpgaPdu.h"
#include "Task.h"
#include "RemoteMsgHandlerShim.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned TICK_MS(100) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RemoteMsgHandlerShim::RemoteMsgHandlerShim(unsigned index, std::shared_ptr<IFpgaMsgTokens> tokens) :
	RemoteMsgHandlerBase(index, tokens),
	mMsgMutex(),
	mCmd(""),
	mCmdReply(""),
	mGotReply(false),
	mReplyCv()
{
//	std::cerr << "NEW RemoteMsgHandlerShim @ " << (void*)this << " " << index << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteMsgHandlerShim::~RemoteMsgHandlerShim()
{
//	std::cerr << "DEL RemoteMsgHandlerShim @ " << (void*)this << std::endl ;
	disconnect() ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerShim::connect(const std::string &firmware)
{
	setActive(true) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerShim::disconnect()
{
	setActive(false) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerShim::sendCommand(const std::string &cmd,
		const std::vector<DataVariant> &attributes,
		const std::set<std::string> &varNames,
		std::vector<DataVariant> &replyAttributes,
		unsigned timeoutMs)
{
	replyAttributes.clear() ;

	std::vector<uint8_t> pduBytes( cmdBytes(cmd, attributes, varNames) ) ;

	{
	std::unique_lock<std::mutex> lock(mMsgMutex) ;
	mGotReply = false ;
	mCmd = std::string(pduBytes.begin(), pduBytes.end()) ;
	mCmdReply.clear() ;
	pduBytes.clear() ;
	}

	// pass command down to base class (which will initiate any registered callback)
	setCmd(std::string(pduBytes.begin(), pduBytes.end())) ;

//std::cerr << "RemoteMsgHandlerShim::sendCommand - wait reply..." << std::endl ;

	while (!mGotReply)
	{
		std::unique_lock<std::mutex> lock(mMsgMutex) ;
		if (mReplyCv.wait_for(lock, std::chrono::milliseconds(timeoutMs)) == std::cv_status::timeout)
		{
//std::cerr << "Timed out " << timeoutMs << " ms" << std::endl ;
			return setError("Timed out waiting for reply") ;
		}
	}

//std::cerr << "RemoteMsgHandlerShim::sendCommand - got reply=" << mGotReply << std::endl ;

	// convert command reply
	{
	std::unique_lock<std::mutex> lock(mMsgMutex) ;
	reply((uint8_t*)mCmdReply.c_str(), mCmdReply.size(), replyAttributes) ;
	mCmdReply.clear() ;
	mGotReply = false ;
	}
//std::cerr << "RemoteMsgHandlerShim::sendCommand - got reply" << std::endl ;
//std::cerr << "RemoteMsgHandlerShim::sendCommand - DONE" << std::endl ;
	return true ;
}






//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandlerShim::hostOpen(const char *filename, int flags, int mode)
{
//	std::cerr << "RemoteMsgHandlerShim::hostOpen @ " << (void*)this << std::endl ;
	std::shared_ptr<IHostFileMgr> mgr(fileMgr()) ;
	return mgr->open(filename, flags, mode) ;
}

//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandlerShim::hostRead(int fd, uint8_t *buffer, int buflen)
{
	std::shared_ptr<IHostFileMgr> mgr(fileMgr()) ;
	return mgr->read(fd, buffer, buflen) ;
}

//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandlerShim::hostWrite(int fd, const uint8_t *buffer, int buflen)
{
	std::shared_ptr<IHostFileMgr> mgr(fileMgr()) ;
	return mgr->write(fd, buffer, buflen) ;
}

//-------------------------------------------------------------------------------------------------------------
int RemoteMsgHandlerShim::hostClose(int fd)
{
	std::shared_ptr<IHostFileMgr> mgr(fileMgr()) ;
	return mgr->close(fd) ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerShim::hostCommandReceived()
{
	std::unique_lock<std::mutex> lock(mMsgMutex) ;
	return !mCmd.empty() ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerShim::hostGetCommand(uint8_t *command, unsigned max_command_len)
{
	std::unique_lock<std::mutex> lock(mMsgMutex) ;
	if (mCmd.empty())
		return false ;

	unsigned len(max_command_len) ;
	if (len >= mCmd.size())
		len = mCmd.size() ;
	memcpy(command, mCmd.c_str(), max_command_len) ;
	mCmd.clear() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteMsgHandlerShim::hostCommandReply(uint8_t *replyBytes, unsigned replyLen)
{
	if (replyLen <= 1)
		return false ;

	std::unique_lock<std::mutex> lock(mMsgMutex) ;

//std::cerr << "RemoteMsgHandlerShim::host_command_reply [" << *replyBytes << "]" << std::endl ;
//ByteTransfer::dump(std::vector<uint8_t>(replyBytes, replyBytes+replyLen)) ;
//
//std::vector<DataVariant> replyAttributes ;
//reply(replyBytes, replyLen, replyAttributes) ;
//for (auto dv : replyAttributes)
//	std::cerr << "REPLY DV: " << dv.getTypeStr() << " " << dv.getName() << " = " << dv.toString() << std::endl ;

	// route the reply PDU
	switch(*replyBytes)
	{
	case IFpgaPdu::PDU_TYPE_REPLY:
		break ;

	case IFpgaPdu::PDU_TYPE_ALARM:
		callAlarmCallback(replyBytes, replyLen) ;
		return true ;

	case IFpgaPdu::PDU_TYPE_EVENT:
		callEventCallback(replyBytes, replyLen) ;
		return true ;

	case IFpgaPdu::PDU_TYPE_NONE:
	case IFpgaPdu::PDU_TYPE_CMD:
	case IFpgaPdu::PDU_TYPE_LOG:
	case IFpgaPdu::PDU_TYPE_MATLAB:
	case IFpgaPdu::PDU_TYPE_TEXT:
	default:
		return false ;
	}

	mCmdReply = std::string(replyBytes, replyBytes+replyLen) ;
	mGotReply = true ;
//std::cerr << "RemoteMsgHandlerShim::host_command_reply - DONE (len=" << replyLen << ")" << std::endl ;
	mReplyCv.notify_all() ;

	return true ;
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaComms.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "stringfunc.hpp"

#include "FpgaCommsFromPpc.h"
#include "FpgaCommsToPpc.h"

//#include "IFpga.h"

#include "FpgaComms.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
const unsigned RESPONSE_TIMEOUT_MS = 4000 ;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaComms::FpgaComms(const std::string& name, const std::string& cmdqName, const std::string& replyqName,
		std::shared_ptr<IFpgaMsgTokens> tokens) :
	Loggable(name, "FpgaCom"),
	mTokens(tokens),
	mFromPpc(std::make_shared<FpgaCommsFromPpc>(cmdqName)),
	mToPpc(std::make_shared<FpgaCommsToPpc>(replyqName)),
	mLogEnable{
		{PduDataType::PDU_TYPE_NONE, 		false},
		{PduDataType::PDU_TYPE_CMD, 		false},
		{PduDataType::PDU_TYPE_REPLY, 		false},
		{PduDataType::PDU_TYPE_EVENT, 		false},
		{PduDataType::PDU_TYPE_LOG, 		false},
		{PduDataType::PDU_TYPE_MATLAB,		false},
		{PduDataType::PDU_TYPE_TEXT, 		false},
	},

	mQueueCallback([this](std::shared_ptr<IFpgaMsg> msg){ queueCallback(msg); }),
	mLogQueue{
		{PduDataType::PDU_TYPE_NONE, 		std::make_shared<MsgQueueBuff>("QueueNone", 	"FpgaCom", mQueueCallback) },
		{PduDataType::PDU_TYPE_CMD, 		std::make_shared<MsgQueueBuff>("QueueCmd", 		"FpgaCom", mQueueCallback) },
		{PduDataType::PDU_TYPE_REPLY, 		std::make_shared<MsgQueueBuff>("QueueReply", 	"FpgaCom", mQueueCallback) },
		{PduDataType::PDU_TYPE_EVENT, 		std::make_shared<MsgQueueBuff>("QueueEvent", 	"FpgaCom", mQueueCallback) },
		{PduDataType::PDU_TYPE_LOG, 		std::make_shared<MsgQueueBuff>("QueueLog", 		"FpgaCom", mQueueCallback) },
		{PduDataType::PDU_TYPE_MATLAB, 		std::make_shared<MsgQueueBuff>("QueueMatlab", 	"FpgaCom", mQueueCallback) },
		{PduDataType::PDU_TYPE_TEXT, 		std::make_shared<MsgQueueBuff>("QueueText", 	"FpgaCom", mQueueCallback) },
	},
	mCmdMutex(),
	mGotRx(),
	mReplyMutex(),
	mReply( std::shared_ptr<IFpgaMsg>() )

{
	// DEBUG: While I'm debugging the comms, enable everything
	//	ILoggable::setGroupLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "FpgaCom") ;

	// Register handler
	std::string failReason ;
	registerMsgHandler(IFpgaPdu::PDU_TYPE_REPLY, this,
		[this](std::shared_ptr<IFpgaMsg> msg) {handleMsg(msg);},
		[this](const IFpgaPdu& pdu)->std::shared_ptr<IFpgaMsg> {return IFpgaMsg::factory(pdu);},
		failReason) ;

	// enable logging
	setLogging(PduDataType::PDU_TYPE_LOG, true) ;
	// console (TEXT) output should not go to syslog by default
	//setLogging(PduDataType::PDU_TYPE_TEXT, true) ;

	// Auto start
	start() ;

}

//-------------------------------------------------------------------------------------------------------------
FpgaComms::~FpgaComms()
{
	mFromPpc->shutdown() ;
	mToPpc->shutdown() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsgTokens> FpgaComms::getTokens() const
{
	return mTokens ;
}

//-------------------------------------------------------------------------------------------------------------
int FpgaComms::start()
{
	int rc ;
	rc = mFromPpc->start() ;
	if (rc != 0)
		return rc ;
	rc = mToPpc->start() ;
	return rc ;
}

//-------------------------------------------------------------------------------------------------------------
int FpgaComms::stop()
{
	int rc ;
	rc = mFromPpc->stop() ;
	if (rc != 0)
		return rc ;
	rc = mToPpc->stop() ;
	return rc ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaComms::isRunning()
{
	return mFromPpc->isRunning() && mToPpc->isRunning() ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaComms::show()
{
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::pair<std::string, UINT16> > FpgaComms::statusValues()
{
	std::vector<std::pair<std::string, UINT16> > values ;

	// @TODO
//	std::shared_ptr<IFpga> fpga(IFpga::getInstance()) ;
//
//	for (unsigned idx=0; idx < PIMSTATUS_LEN/2; ++idx)
//	{
//		UINT16 mem = fpga->readRegister(PIMSTATUS_OFFSET_PPC + idx*2) ;
//
//		std::stringstream ss ;
//		ss << "PIMSTATUS(" << idx << ")" ;
//		values.push_back(make_pair(ss.str(), mem)) ;
//	}
	return values ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaComms::checkApiVersion(std::shared_ptr<IFpgaMsg> msg)
{
	std::map<std::string, DataVariant> attributes(msg->getAttributes()) ;
	if (attributes.find("apiVersion") == attributes.end())
		return false ;

	return static_cast<unsigned>(attributes["apiVerson"].toInt()) == getApiVersion() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned FpgaComms::getApiVersion()
{
	return mTokens->getApiVersion() ;
}


//-------------------------------------------------------------------------------------------------------------
bool FpgaComms::command(const IFpgaMsg& msg, std::string& failReason)
{
	bool ok = mFromPpc->sendPdu(msg.getPdu()) ;
	if (!ok)
		failReason = "Unable to send message" ;
	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaComms::command(std::shared_ptr<IFpgaMsg> msg, std::string& failReason)
{
	bool ok = mFromPpc->sendPdu(msg->getPdu()) ;
	if (!ok)
		failReason = "Unable to send message" ;
	return ok ;
}


//-------------------------------------------------------------------------------------------------------------
bool FpgaComms::registerMsgHandler(IFpgaPdu::PduDataType dataType, void* const object,
		MsgHandler handler, MsgCreator creator,
		std::string& failReason)
{
	// Handle commands from PPC
	if (dataType == IFpgaPdu::PduDataType::PDU_TYPE_CMD)
		return mFromPpc->registerMsgHandler(object, handler, creator, failReason) ;

	// Responses back to PPC
	return mToPpc->registerMsgHandler(dataType, object, handler, creator, failReason) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaComms::unRegisterMsgHandler(IFpgaPdu::PduDataType dataType, void* const object)
{
	// Handle commands from PPC
	if (dataType == IFpgaPdu::PduDataType::PDU_TYPE_CMD)
		return mFromPpc->unRegisterMsgHandler(object) ;

	// Responses back to PPC
	mToPpc->unRegisterMsgHandler(dataType, object) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaComms::setLogging(IFpgaPdu::PduDataType dataType, bool logEnable)
{
	// check for change
	if (logEnable != mLogEnable.at(dataType))
	{
		// enabling
		if (logEnable)
		{
			std::string failReason ;
			registerMsgHandler(dataType, mLogQueue[dataType].get(),
				[this, dataType](std::shared_ptr<IFpgaMsg> msg){ mLogQueue[dataType]->add(msg); },
				[this](const IFpgaPdu& pdu)->std::shared_ptr<IFpgaMsg>{ return IFpgaMsg::factory(pdu); },
				failReason
			) ;
		}

		// disabling
		else
		{
			unRegisterMsgHandler(dataType, mLogQueue[dataType].get()) ;
		}
	}

	// save setting
	mLogEnable[dataType] = logEnable ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaComms::getLogging(IFpgaPdu::PduDataType dataType) const
{
	return mLogEnable.at(dataType) ;
}


//-------------------------------------------------------------------------------------------------------------
int FpgaComms::enumToInt(const std::string& name) const
{
	return mTokens->getToken(name) ;
}


//-------------------------------------------------------------------------------------------------------------
bool FpgaComms::commandWaitResponse(std::shared_ptr<IFpgaMsg> msg, std::shared_ptr<IFpgaMsg>& response, std::string& failReason)
{
//	std::cerr << "FpgaComms::commandWaitResponse CMD: '" << msg->toString() << "'" << std::endl ;

	response = std::shared_ptr<IFpgaMsg>() ;

	// This lock prevents any other commands being sent
	Mutex::Lock lock(mCmdMutex) ;

	// Clear out reply and send new command
	{
		Mutex::Lock lock(mReplyMutex) ;
//		std::cerr << "FpgaComms::commandWaitResponse clear reply" << std::endl ;

		mReply = std::shared_ptr<IFpgaMsg>() ;

		// Clear out conditional (removes any previous replies)
		mGotRx.clear() ;

		// Send command
		if (!command(msg, failReason))
		{
			return false ;
		}
	}

//std::cerr << "FpgaComms::commandWaitResponse wait for mGotRx" << std::endl ;

	// wait for response or timeout
	if (mGotRx.wait(RESPONSE_TIMEOUT_MS) == false)
	{
		eventWarning("FpgaComms::commandWaitResponse : Timed out waiting for reply to ID %u", msg->getId()) ;
//std::cerr << "FpgaComms::commandWaitResponse (mGotRx is FALSE)" << std::endl ;
		failReason = "Timed out waiting for reply" ;
		return false ;
	}
//std::cerr << "FpgaComms::commandWaitResponse (mGotRx is true)" << std::endl ;


	// get response (clears local copy)
	{
		Mutex::Lock lock(mReplyMutex) ;
		using std::swap ;
		swap(response, mReply) ;

//		std::cerr << "FpgaComms::commandWaitResponse swap reply" << std::endl ;
	}

	// Check IDs
	if (!response->isIdMatch(msg))
	{
		eventError("FpgaComms::commandWaitResponse : message ID mismatch with reply - sent ID %u, Reply ID %u", msg->getId(), response->getId()) ;
//std::cerr << "FpgaComms::commandWaitResponse ** MsgIds MISMATCH ** Cmd=" << msg->getId() << " Reply=" << pimMsg->getId() << std::endl ;
	}

	// Check response
	if (!response->getAck())
	{
		logDebugVerbose("NACK received: reply '%s'", response->toString().c_str()) ;
		logDebugVerbose("NACK received: PDU '%s'", response->getPdu()->toString().c_str()) ;
		failReason = "NACK received" ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaComms::commandDontWaitResponse(std::shared_ptr<IFpgaMsg> msg, std::string& failReason)
{
	// This lock prevents any other commands being sent
	Mutex::Lock lock(mCmdMutex) ;

	// Send command
	if (!command(msg, failReason))
	{
		return false;
	}
	return true;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void FpgaComms::queueCallback(std::shared_ptr<IFpgaMsg> msg)
{
	std::string info("[" + IFpgaPdu::typeToStr(msg->getType()) + "] " + msg->toString()) ;
	eventInfo(info) ;
//std::cerr << "FpgaComms::queueCallback - '" << info << "' END" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaComms::handleMsg(std::shared_ptr<IFpgaMsg> msg)
{
	{
	Mutex::Lock lock(mReplyMutex) ;
	mReply = msg ;
	}
//std::cerr << "FpgaComms::handleMsg got reply (mGotRx=true) " << mReply->toString() << std::endl ;

	// send signal
	{
	Conditional::Lock condLock(mGotRx) ;
	mGotRx.signal() ;
	}
}

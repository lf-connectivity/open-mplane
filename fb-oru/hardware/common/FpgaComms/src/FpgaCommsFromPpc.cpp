/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsFromPpc.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdexcept>
#include <sstream>

#include "IFpgaCommsConstants.h"
#include "FpgaPdu.h"

#include "FpgaCommsFromPpc.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsFromPpc::FpgaCommsFromPpc(const std::string& messageQueueName)  :
	Task(Task::PRIORITY_MEDIUM, Task::SMALL_STACK, "FpgaCommsFromPpc", "FpgaCom"),

	mCmdQ(IMsgQ::factory(messageQueueName)),
	mPduLen(0),
    mTaskRun(true),
    mTaskRunning(false),
    mPduAvailable(),

    mPduMutex(),
    mPdus(),

    mHandlerMutex(),
    mHandlers{}

{
	if (!mCmdQ->connectWrite())
		throw std::runtime_error("Cannot connect (write) to message queue " + messageQueueName) ;
	mPduLen = mCmdQ->getMaxMsgSize() ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsFromPpc::~FpgaCommsFromPpc()
{
	if (mTaskRunning)
		shutdown() ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsFromPpc::sendPdu(std::shared_ptr<IFpgaPdu> pdu)
{
	logDebugVerbose("FpgaCommsFromPpc: sendPdu") ;

	// check for valid message size
	if (pdu->getData().empty())
		return false ;
	if (pdu->getData().size() >= mPduLen)
		return false ;

	// For debug, dump data
	if (isDebug(ILoggable::LOG_DEBUG_VERBOSE))
	{
		std::vector<UINT8> data(pdu->getBytes()) ;
		logDebugVerbose("FpgaCommsFromPpc PDU: 0x%02x (total len=%u)",
				pdu->getTypeByte(), (unsigned)data.size()) ;

		const unsigned ENTRIES_PER_LINE(8) ;

		std::stringstream hex ;
		std::stringstream ascii ;
		hex << std::hex ;

		unsigned offset(0) ;
		unsigned idx(0) ;
		for(idx=0; idx < data.size(); ++idx)
		{
			char buff[8] ;
			snprintf(buff, sizeof(buff), "0x%02x ", (unsigned)data[idx]) ;
			hex << buff ;
			if ( (data[idx] >= 0x20) && (data[idx] <= 0x7f) )
				ascii << (char)data[idx] ;
			else
				ascii << "." ;

			if ( (idx+1) % ENTRIES_PER_LINE == 0)
			{
				logDebugVerbose("FpgaCommsFromPpc PDU [0x%04x]: %s : %s", offset, hex.str().c_str(), ascii.str().c_str()) ;
				hex.str("") ;
				ascii.str("") ;
				offset += 2*ENTRIES_PER_LINE ;
			}
		}

		if (!hex.str().empty())
		{
			for (unsigned pad=1; pad <= ENTRIES_PER_LINE-(idx % ENTRIES_PER_LINE); pad++)
				hex << "     " ;
			logDebugVerbose("FpgaCommsFromPpcShim PDU [0x%04x]: %s : %s", offset, hex.str().c_str(), ascii.str().c_str()) ;
		}
	}



	// add the message to the queue
	{
		Mutex::Lock lock(mPduMutex) ;
		mPdus.push(pdu) ;
	}

	logDebugVerbose("FpgaCommsFromPpc: sendPdu - signal to task") ;

	// If a handler is defined, then we can use it
	{
		Mutex::Lock lock(mHandlerMutex) ;
		for (auto entry : mHandlers)
		{
			entry.second.handler( entry.second.creator(*pdu) ) ;
		}
	}

	// signal to task to send msg
	Conditional::Lock condLock(mPduAvailable) ;
	mPduAvailable.signal() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::FpgaCommsFromPpc::shutdown()
{
	if (!mTaskRunning)
		return ;

	mTaskRun = false ;
	while(mTaskRunning)
	{
		{
		Conditional::Lock condLock(mPduAvailable) ;
		mPduAvailable.signal() ;
		}
		msSleep(10) ;
	}
}


//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsFromPpc::registerMsgHandler(void* const object,
		MsgHandler handler, MsgCreator creator, std::string& failReason)
{
	Mutex::Lock lock(mHandlerMutex) ;

	if (!handler || !creator)
	{
		throw std::invalid_argument("Must specify valid handler/creator functions") ;
		return false ;
	}

	auto entry(mHandlers.find(object)) ;
	if (entry != mHandlers.end())
	{
		entry->second = CmdHandlerStruct(handler, creator) ;
	}
	else
	{
		mHandlers[object] = CmdHandlerStruct(handler, creator) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsFromPpc::unRegisterMsgHandler(void* const object)
{
	Mutex::Lock lock(mHandlerMutex) ;
	auto entry(mHandlers.find(object)) ;
	if (entry != mHandlers.end())
		mHandlers.erase(entry) ;
}

//=============================================================================================================
// PROTECTED (TASK)
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int FpgaCommsFromPpc::run()
{
	mTaskRunning = true ;

    /*
     * Now our thread is running we just enter an infinite loop so we never end.
     * ALl image management is triggered by invocation of class methods, which are explicit action requests.
     */
    while (mTaskRun)
    {
		logDebugVerbose("FpgaCommsFromPpc: wait for data...") ;

    	// wait for messages to become available
    	mPduAvailable.wait() ;

		// check for task stop
		if (!mTaskRun)
			break ;

		logDebugVerbose("FpgaCommsFromPpc: process messages") ;

		// process all messages
		Mutex::Lock lock(mPduMutex) ;
		while (!mPdus.empty() && mTaskRun)
		{
			logDebugVerbose("PPC->DPD: SEND") ;

			// send data
//			mCmdQ->sendData( mPdus.front()->getDataBytes() ) ; <---- BUG! - Need to sort out the SHIM end now...
			mCmdQ->sendData( mPdus.front()->getBytes() ) ;

			logDebugVerbose("PPC->DPD: SEND done") ;

			// finished with data
			mPdus.pop() ;

		} // while still got messages
    }

	mTaskRunning = false ;
    return 0;
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsToPpc.cpp
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
#include "FpgaCommsToPpc.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsToPpc::FpgaCommsToPpc(const std::string& messageQueueName) :
	Task(Task::PRIORITY_MEDIUM, Task::SMALL_STACK, "FpgaCommsToPpc", "FpgaCom"),

	mMsgQ(IMsgQ::factory(messageQueueName)),
    mTaskRun(true),
    mTaskRunning(false),

    mHandlerMutex(),
    mHandlers({
    	{PduDataType::PDU_TYPE_NONE, {}},
    	{PduDataType::PDU_TYPE_CMD, {}},
    	{PduDataType::PDU_TYPE_REPLY, {}},
    	{PduDataType::PDU_TYPE_EVENT, {}},
    	{PduDataType::PDU_TYPE_LOG, {}},
    	{PduDataType::PDU_TYPE_MATLAB, {}},
    	{PduDataType::PDU_TYPE_TEXT, {}},
    })
{
	logDebugVerbose("FpgaCommsToPpc new") ;
	if (!mMsgQ->connectRead())
		throw std::runtime_error("Cannot connect (read) to message queue " + messageQueueName) ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsToPpc::~FpgaCommsToPpc()
{
	logDebugVerbose("FpgaCommsToPpc destroy") ;
	if (mTaskRunning)
		shutdown() ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsToPpc::shutdown()
{
	if (!mTaskRunning)
		return ;

	mTaskRun = false ;

	// send a message to ensure task wakes up
	std::shared_ptr<IMsgQ> msgq(IMsgQ::factory(mMsgQ->getName())) ;
	msgq->connectWrite() ;

	std::vector<unsigned char> msg{'e', 'x', 'i', 't'} ;
	msgq->sendData(msg) ;

	// wait until task finishes
	while(mTaskRunning)
	{
		msSleep(10) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsToPpc::registerMsgHandler(FpgaPdu::PduDataType dataType, void* const object,
		MsgHandler handler, MsgCreator creator,
		std::string& failReason)
{
//std::cerr << "FpgaCommsToPpc::registerMsgHandler type=" << dataType << " " << object << std::endl ;
	Mutex::Lock lock(mHandlerMutex) ;

	if (!handler || !creator)
	{
		throw std::invalid_argument("Must specify valid handler/creator functions") ;
		return false ;
	}

	auto entry(mHandlers[dataType].find(object)) ;
	if (entry != mHandlers[dataType].end())
	{
		entry->second = HandlerStruct(handler, creator) ;
	}
	else
	{
		mHandlers[dataType][object] = HandlerStruct(handler, creator) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsToPpc::unRegisterMsgHandler(FpgaPdu::PduDataType dataType, void* const object)
{
//std::cerr << "FpgaCommsToPpc::unRegisterMsgHandler " << object << std::endl ;
	Mutex::Lock lock(mHandlerMutex) ;
	auto entry(mHandlers[dataType].find(object)) ;
	if (entry != mHandlers[dataType].end())
		mHandlers[dataType].erase(entry) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int FpgaCommsToPpc::run()
{
	mTaskRunning = true ;
	logDebugVerbose("FpgaCommsToPpc task run") ;

    /*
     * Now our thread is running we just enter an infinite loop so we never end.
     * ALl image management is triggered by invocation of class methods, which are explicit action requests.
     */
    while (mTaskRun)
    {
    	// wait for message
    	std::vector<unsigned char> rx ;
    	mMsgQ->getData(rx) ;

    	logDebugVerbose("FpgaCommsToPpc task got data") ;

		// check for task stop
		if (!mTaskRun)
			break ;

		// handle the message
		std::shared_ptr<IFpgaPdu> pdu(std::make_shared<FpgaPdu>(rx)) ;
		handlePdu(*pdu) ;
    }

	logDebugVerbose("FpgaCommsToPpc task end") ;
	mTaskRunning = false ;
    return 0;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
void FpgaCommsToPpc::handlePdu(const FpgaPdu& pdu)
{
	FpgaPdu::PduDataType dataType( pdu.getType() ) ;

	// If a handler is defined, then we can use it
	Mutex::Lock lock(mHandlerMutex) ;
	logDebugVerbose("FpgaCommsToPpc::handlePdu type=%u %u handlers",
			(unsigned)dataType, (unsigned)mHandlers[dataType].size()) ;
//std::cerr << "handlePdu: " << pdu.toString() << std::endl ;
	for (auto entry : mHandlers[dataType])
	{
		entry.second.handler( entry.second.creator(pdu) ) ;
	}
}

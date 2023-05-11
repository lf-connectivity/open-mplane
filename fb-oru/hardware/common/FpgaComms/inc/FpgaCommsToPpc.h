/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsToPpc.h
 * \brief     FPGA comms from uBlaze to PPC
 *
 *
 * \details
 *
 */


#ifndef FPGACOMMSTOPPC_H_
#define FPGACOMMSTOPPC_H_

#include <queue>
#include <map>

#include "GlobalTypeDefs.h"
#include "Conditional.h"
#include "Mutex.h"
#include "Task.h"
#include "IMsgQ.h"

#include "IFpgaMsg.h"
#include "FpgaPdu.h"

namespace Mplane {

class FpgaCommsToPpc : public Task
{
public:
	using MsgHandler = IFpgaMsg::MsgHandler ;
	using MsgCreator = IFpgaMsg::MsgCreator ;
	using PduDataType = FpgaPdu::PduDataType ;

	explicit FpgaCommsToPpc(const std::string& messageQueueName) ;
	virtual ~FpgaCommsToPpc() ;

	/**
	 * Register a message handler with a particular type of message
	 * @param PduDataType	Message type to register handler with
	 * @param object	Pointer to object registering the calls
	 * @param handler	The function to call with this type of message
	 * @param creator	Function to call to create a message from the PDU
	 * @param failReason	Set to failure string on error
	 * @return true if registered ok
	 */
	virtual bool registerMsgHandler(FpgaPdu::PduDataType PduDataType, void* const object,
			MsgHandler handler, MsgCreator creator,
			std::string& failReason) ;

	/**
	 * Un-Register a message handler from a particular type of message
	 * @param PduDataType	Message type to un-register handler from
	 * @param object	Pointer to object un-registering the calls
	 */
	virtual void unRegisterMsgHandler(FpgaPdu::PduDataType PduDataType, void* const object) ;

	/**
	 * Shutdown any running process
	 */
	void shutdown() ;


protected:
    /**
     * This is the Task method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     *
     * \return the exit status of task process
     */
    virtual int run() override ;

private:
	void handlePdu(const FpgaPdu& pdu) ;

private:
	std::shared_ptr<IMsgQ> mMsgQ ;
	bool mTaskRun ;
    bool mTaskRunning ;

    // Message handlers
    struct HandlerStruct {
    	HandlerStruct(MsgHandler _handler, MsgCreator _creator) :
    		handler(_handler), creator(_creator)
    	{}
    	HandlerStruct() :
    		handler(), creator()
    	{}
    	MsgHandler handler ;
    	MsgCreator creator ;
    };
    Mutex mHandlerMutex ;
    std::map<PduDataType, std::map<void* const, HandlerStruct>> mHandlers ;
} ;

}

#endif /* FPGACOMMSTOPPC_H_ */

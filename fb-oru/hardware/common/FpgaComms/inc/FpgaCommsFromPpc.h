/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsFromPpc.h
 * \brief     FPGA comms from PPC to uBlaze
 *
 *
 * \details
 *
 */


#ifndef FPGACOMMSFROMPPC_H_
#define FPGACOMMSFROMPPC_H_

#include <memory>
#include <vector>
#include <queue>

#include "IMsgQ.h"
#include "Conditional.h"
#include "Mutex.h"
#include "Task.h"
#include "IFpgaPdu.h"
#include "IFpgaMsg.h"

namespace Mplane {

class FpgaCommsFromPpc : public Task
{
public:
	using MsgHandler = IFpgaMsg::MsgHandler ;
	using MsgCreator = IFpgaMsg::MsgCreator ;

	explicit FpgaCommsFromPpc(const std::string& messageQueueName) ;
	virtual ~FpgaCommsFromPpc() ;

	/**
	 * Send a new PDU
	 */
	bool sendPdu(std::shared_ptr<IFpgaPdu> pdu) ;

	/**
	 * Shutdown any running process
	 */
	void shutdown() ;

	/**
	 * Register a message handler for command messages
	 * @param object	Pointer to object registering the calls
	 * @param handler	The function to call with this type of message
	 * @param creator	Function to call to create a message from the PDU
	 * @param failReason	Set to failure string on error
	 * @return true if registered ok
	 */
	virtual bool registerMsgHandler(void* const object,
			MsgHandler handler, MsgCreator creator,
			std::string& failReason) ;

	/**
	 * Un-Register a message handler for command messages
	 * @param object	Pointer to object un-registering the calls
	 */
	virtual void unRegisterMsgHandler(void* const object) ;


protected:
    /**
     * This is the Task method that is run by the start() method. As it is pure virtual
     * it must be implemented by the inheriting task.
     *
     * \return the exit status of task process
     */
    virtual int run() override ;

private:
    std::shared_ptr<IMsgQ> mCmdQ ;
    unsigned mPduLen ;
    bool mTaskRun ;
    bool mTaskRunning ;
    Conditional mPduAvailable ;

    Mutex mPduMutex ;
    std::queue<std::shared_ptr<IFpgaPdu>> mPdus ;

    // Message handlers
    struct CmdHandlerStruct {
    	CmdHandlerStruct(MsgHandler _handler, MsgCreator _creator) :
    		handler(_handler), creator(_creator)
    	{}
    	CmdHandlerStruct() :
    		handler(), creator()
    	{}
    	MsgHandler handler ;
    	MsgCreator creator ;
    };
    Mutex mHandlerMutex ;
    std::map<void* const, CmdHandlerStruct> mHandlers ;
} ;

}

#endif /* FPGACOMMSFROMPPC_H_ */

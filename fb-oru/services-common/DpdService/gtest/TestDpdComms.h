/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDpdComms.h
 * \brief     Communications with FPGA
 *
 *
 * \details
 *
 */


#ifndef TestDpdComms_H_
#define TestDpdComms_H_

#include <memory>
#include <string>

#include "Loggable.h"
#include "QueueBuffer.hpp"

#include "IFpgaComms.h"
#include "IFpgaMsg.h"
#include "IFpgaPdu.h"
#include "IFpgaMsgTokens.h"

namespace Mplane {

class TestDpdComms : public virtual IFpgaComms
{
public:
	using PduDataType = IFpgaPdu::PduDataType ;

	TestDpdComms() ;
	virtual ~TestDpdComms() ;

	/////////////////////////////////////////////////////////////////
	// TEST INTERFACE

	/**
	 * Sends the message to all registered clients
	 * @param msg
	 */
	void emulateRxMsg(std::shared_ptr<IFpgaMsg> msg) ;

	/**
	 * Create a message of the specified type. The 'args' parameter is a DataVariantList-compatible string which defines variable/value pairs
	 * @param type
	 * @param args
	 * @return message
	 */
	std::shared_ptr<IFpgaMsg> createMsg(IFpgaPdu::PduDataType type, const std::string& args) ;

	/////////////////////////////////////////////////////////////////


	/**
	 * Get the tokens interface for this comms channel
	 */
	virtual std::shared_ptr<IFpgaMsgTokens> getTokens() const override ;

	// Command interface

	/**
	 * Convert enumeration name into a value
	 * @param name
	 * @return integer
	 */
	virtual int enumToInt(const std::string& name) const override ;

	/**
	 * Sends the command IFpgaMsg to the PIM. Waits for a response and checks the response for an ACK.
	 *
	 * @param msg			Command message to send
	 * @param response		Response from PIM
	 * @param failReason	String set with failure reason if call fails
	 * @return true if able to send and response is valid
	 */
	virtual bool commandWaitResponse(std::shared_ptr<IFpgaMsg> msg, std::shared_ptr<IFpgaMsg>& response, std::string& failReason) override ;

	/**
	 * Sends the command IFpgaMsg to the PIM. Does not waits for a response.
	 *
	 * @param msg			Command message to send
	 * @param failReason	String set with failure reason if call fails
	 * @return true if able to send
	 */
	virtual bool commandDontWaitResponse(std::shared_ptr<IFpgaMsg> msg,
			std::string& failReason) override ;

	/**
	 * Communicates with the FPGA and ensures that the FPGA's API version matches this interface's API version
	 * @param msg			Response from 'get api' command
	 * @return true if versions match
	 */
	virtual bool checkApiVersion(std::shared_ptr<IFpgaMsg> msg) override ;

	/**
	 * Get the application's API version  (mainly used for testing)
	 * @return API version
	 */
	virtual unsigned getApiVersion() override ;

	/**
	 * Sends the command IFpgaMsg to the PIM
	 * @param msg
	 * @param failReason	String set with failure reason if call fails
	 * @return true if able to send
	 */
	virtual bool command(const IFpgaMsg& msg, std::string& failReason) override ;

	/**
	 * Sends the command IFpgaMsg to the PIM
	 * @param msg
	 * @param failReason	String set with failure reason if call fails
	 * @return true if able to send
	 */
	virtual bool command(std::shared_ptr<IFpgaMsg> msg, std::string& failReason) override ;

    /**
     * Returns a set of internal status registers used to debug the state of the microblaze code
     * @return vector of register values paired with a register name
     */
    virtual std::vector< std::pair<std::string, UINT16> > statusValues() override ;

	/**
	 * Register a message handler with a particular type of message
	 * @param PduDataType	Message type to register handler with
	 * @param handler	The function to call with this type of message
	 * @param creator	Function to call to create a message from the PDU
	 * @param failReason	Set to failure string on error
	 * @return true if registered ok
	 */
	virtual bool registerMsgHandler(IFpgaPdu::PduDataType PduDataType, void* const object,
			MsgHandler handler, MsgCreator creator,
			std::string& failReason) override ;

	/**
	 * Un-Register a message handler from a particular type of message
	 * @param PduDataType	Message type to un-register handler from
	 */
	virtual void unRegisterMsgHandler(IFpgaPdu::PduDataType PduDataType, void* const object) override ;

	/**
	 * Enable/disable logging of this type of message
	 * @param PduDataType	Message type to register handler with
	 * @param logEnable	Logging enable
	 */
	virtual void setLogging(IFpgaPdu::PduDataType PduDataType, bool logEnable) override ;

	/**
	 * Enable/disable logging of this type of message
	 * @param PduDataType	Message type to register handler with
	 * @return true if logging enabled
	 */
	virtual bool getLogging(IFpgaPdu::PduDataType PduDataType) const override ;



	// Task interface

	/**
	 * Method called to start run the tasks run() method.
	 */
	virtual int start() override ;

	/**
	 * Method used to cancel the running task, the calling thread will
	 * block until the task cancellation is complete.
	 */
	virtual int stop() override ;

    /**
     * Method return true, if the task is running.
     */
	virtual bool isRunning() override ;

    /**
     * Method defined by the Loggable interface must be implemented by all
     * object to force the display of the objects current status.
     */
    virtual void show() override ;

public:
    struct HandlerStruct {
    	HandlerStruct(MsgHandler handler, MsgCreator creator) :
    		mHandler(handler), mCreator(creator)
    	{}
    	HandlerStruct() :
    		mHandler(), mCreator()
    	{}
    	MsgHandler mHandler;
    	MsgCreator mCreator ;
    };
    std::map<IFpgaPdu::PduDataType, std::map<void* const, HandlerStruct>> mHandlers ;

    // save last sent command
    std::shared_ptr<IFpgaMsg> mLastCommand ;
} ;

}

#endif /* FPGACOMMS_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaComms.h
 * \brief     FPGA comms interface
 *
 *
 * \details
 *
 */


#ifndef IFPGACOMMS_H_
#define IFPGACOMMS_H_

#include <utility>
#include <vector>
#include <memory>

#include "IFpgaMsg.h"
#include "IFpgaMsgTokens.h"
#include "IFpgaPdu.h"

namespace Mplane {

class IFpgaComms {
public:
	using MsgHandler = IFpgaMsg::MsgHandler ;
	using MsgCreator = IFpgaMsg::MsgCreator ;

	/**
	 * Singleton
	 */
	static std::shared_ptr<IFpgaComms> getInterface() ;

	virtual ~IFpgaComms() {}


	/**
	 * Get the tokens interface for this comms channel
	 */
	virtual std::shared_ptr<IFpgaMsgTokens> getTokens() const =0 ;


	// Command interface

	/**
	 * Convert enumeration name into a value
	 * @param name
	 * @return integer
	 */
	virtual int enumToInt(const std::string& name) const =0 ;

	/**
	 * Sends the command IFpgaMsg to the PIM. Waits for a response and checks the response for an ACK.
	 *
	 * @param msg			Command message to send
	 * @param response		Response from PIM
	 * @param failReason	String set with failure reason if call fails
	 * @return true if able to send and response is valid
	 */
	virtual bool commandWaitResponse(std::shared_ptr<IFpgaMsg> msg, std::shared_ptr<IFpgaMsg>& response,
			std::string& failReason) =0 ;

	/**
	 * Sends the command IFpgaMsg to the PIM. Does not waits for a response.
	 *
	 * @param msg			Command message to send
	 * @param failReason	String set with failure reason if call fails
	 * @return true if able to send
	 */
	virtual bool commandDontWaitResponse(std::shared_ptr<IFpgaMsg> msg,
			std::string& failReason) =0 ;

	/**
	 * Communicates with the FPGA and ensures that the FPGA's API version matches this interface's API version
	 * @param msg			Response from 'get api' command
	 * @return true if versions match
	 */
	virtual bool checkApiVersion(std::shared_ptr<IFpgaMsg> msg) =0 ;

	/**
	 * Get the application's API version (mainly used for testing)
	 * @return API version
	 */
	virtual unsigned getApiVersion() =0 ;

	/**
	 * Sends the command IFpgaMsg to the FPGA
	 * @param msg			Command message to send
	 * @param failReason	String set with failure reason if call fails
	 * @return true if able to send
	 */
	virtual bool command(const IFpgaMsg& msg, std::string& failReason) =0 ;

	/**
	 * Sends the command IFpgaMsg to the DPD
	 * @param msg			Command message to send
	 * @param failReason	String set with failure reason if call fails
	 * @return true if able to send
	 */
	virtual bool command(std::shared_ptr<IFpgaMsg> msg, std::string& failReason) =0 ;

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
			std::string& failReason) =0 ;

	/**
	 * Un-Register a message handler from a particular type of message
	 * @param PduDataType	Message type to un-register handler from
	 */
	virtual void unRegisterMsgHandler(IFpgaPdu::PduDataType PduDataType, void* const object) =0 ;


	/**
	 * Enable/disable logging of this type of message
	 * @param PduDataType	Message type to register handler with
	 * @param logEnable	Logging enable
	 */
	virtual void setLogging(IFpgaPdu::PduDataType PduDataType, bool logEnable) =0 ;

	/**
	 * Enable/disable logging of this type of message
	 * @param PduDataType	Message type to register handler with
	 * @return true if logging enabled
	 */
	virtual bool getLogging(IFpgaPdu::PduDataType PduDataType) const =0 ;



	// Task interface

	/**
	 * Method called to start run the tasks run() method.
	 */
	virtual int start() =0 ;

	/**
	 * Method used to cancel the running task, the calling thread will
	 * block until the task cancellation is complete.
	 */
	virtual int stop() =0 ;

    /**
     * Method return true, if the task is running.
     */
	virtual bool isRunning() =0 ;

    /**
     * Method defined by the Loggable interface must be implemented by all
     * object to force the display of the objects current status.
     */
    virtual void show() =0 ;

    /**
     * Returns a set of internal status registers used to debug the state of the microblaze code
     * @return vector of register values paired with a register name
     */
    virtual std::vector< std::pair<std::string, UINT16> > statusValues() =0 ;

protected:
    IFpgaComms() {}

} ;

}

#endif /* IFPGACOMMS_H_ */

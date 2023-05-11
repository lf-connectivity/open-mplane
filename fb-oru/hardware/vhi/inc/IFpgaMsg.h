/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaMsg.h
 * \brief     FPGA message interface
 *
 *
 * \details   Defines the low-level access methods (used by FpgaComms) to manipulate the message without needing to
 * 			 know anything about the higher-layer details of the message. This means that the same low-level can
 * 			 be given DPD messages, PIM messages etc.
 *
 */


#ifndef IFPGAMSG_H_
#define IFPGAMSG_H_

#include <map>
#include <set>
#include <string>
#include <memory>
#include <ostream>
#include <functional>

#include "DataVariant.h"
#include "IFpgaPdu.h"

namespace Mplane {

class IFpgaMsg {
public:
	/** Handler function that takes an IFpgaMsg and uses it
	 */
	using MsgHandler = std::function< void(std::shared_ptr<IFpgaMsg>) > ;

	/**
	 * Function for creating an IFpgaMsg instance from a PDU
	 */
	using MsgCreator = std::function< std::shared_ptr<IFpgaMsg>(const IFpgaPdu&) > ;


	virtual ~IFpgaMsg() {}
	IFpgaMsg() {}

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	IFpgaMsg(const IFpgaPdu& pdu) {}

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	IFpgaMsg(std::shared_ptr<IFpgaPdu> pdu) {}


	/**
	 * Factory from creating new instances
	 *
	 * @param pdu
	 */
	static std::shared_ptr<IFpgaMsg> factory(std::shared_ptr<IFpgaPdu> pdu) ;

	/**
	 * Factory from creating new instances
	 *
	 * @param pdu
	 */
	static std::shared_ptr<IFpgaMsg> factory(const IFpgaPdu& pdu) ;

	/**
	 * Factory from creating new command instances
	 *
	 * @param cmd	Command type to create
	 * @param attributes	map of key/value pairs to use with the command
	 * @param varNames	[optional] set of variable names to use with command (used with 'get' command etc)
	 *
	 */
	static std::shared_ptr<IFpgaMsg> factory(const std::string& cmd,
			const std::vector<DataVariant>& attributes = std::vector<DataVariant>{},
			const std::set<std::string>& varNames = std::set<std::string>{}) ;

	/**
	 * Factory from creating new reply instances
	 *
	 * @param msgId		Message ID of the command we're replying to
	 * @param attributes	map of key/value pairs to use with the reply
	 *
	 */
	static std::shared_ptr<IFpgaMsg> factory(unsigned msgId,
			const std::vector<DataVariant>& attributes = std::vector<DataVariant>{}) ;


	/**
	 * Get the message type
	 * @return type of message
	 */
	virtual IFpgaPdu::PduDataType getType() const =0 ;

	/**
	 * Get the underlying PDU from this message
	 * @return PDU
	 */
	virtual std::shared_ptr<IFpgaPdu> getPdu() const =0 ;

	/**
	 * Get PDU data as a string (with any leading/trailing spaces trimmed)
	 * @return PDU string
	 */
	virtual std::string getPduData() const =0 ;

	/**
	 * Output the message to the specified stream
	 */
	virtual void show(std::ostream& os) const =0 ;

	/**
	 * Every message will be tagged with a monotonic ID number to assist with tracking. Internally
	 * will be stored in a suitably sized type compatible with the fpga hardware)
	 */
	virtual unsigned getId() const =0 ;

	/**
	 * Was there an error during message construction?
	 * @return true if error
	 */
	virtual bool isError() const =0 ;

	/**
	 * If there has been an error, this returns an error message
	 * @return error message if error; empty otherwise
	 */
	virtual std::string errorReason() const =0 ;

	/**
	 * Converts the message data into a string. For response types this converts any token values into strings
	 * and any enumerated type values into enumerations.
	 *
	 * @return string representation of message
	 */
	virtual std::string toString() const =0 ;

	/**
	 * Does this message ID match that in the specified message? If one or other of the messages does not have an ID set then assumes they
	 * match (had to have a relaxed approach because the of inconsistency in replies!)
	 * @param msg	Message to compare this message with
	 * @return true if IDs match
	 */
	virtual bool isIdMatch(std::shared_ptr<IFpgaMsg>& msg) const =0 ;


	/**
	 * Get the low-level message as a string (mainly for debug)
	 * @return message string
	 */
	virtual std::string getStr() const =0 ;

	/**
	 * Every reply will have a token 'response' set to 'ACK' or 'NACK'. This returns TRUE for 'ACK', FALSE for 'NACK'.
	 * Replies with true if no response token is found (e.g. for commands)
	 */
	virtual bool getAck() const =0 ;

	/**
	 * Extract the var=value pairs from the message
	 * @return map of var=value pairs
	 */
	virtual std::map<std::string, DataVariant> getAttributes() const =0 ;

} ;

}

#endif /* IFPGAMSG_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestFpgaCommsMsg.h
 * \brief     FpgaComms message base class
 *
 *
 * \details    FpgaComms messaging class that can take a command string and convert it into a PDU (with converted tokens).
 *
 * 				Class can also handle the other direction, take a PDU (log/event/response) and convert it into a string.
 *
 * 				Provides a "show" string interface that the TIF can use to output the message, along with message logging.
 *
 *
 */


#ifndef TestFpgaCommsMsg_H_
#define TestFpgaCommsMsg_H_

#include <iostream>
#include <string>
#include <map>
#include <set>

#include "Loggable.h"
#include "Mutex.h"

#include "Tokeniser.h"

#include "IFpgaMsg.h"
#include "IFpgaMsgTokens.h"


namespace Mplane {

class TestFpgaCommsMsg : public IFpgaMsg
{
public:
	// IFpgaMsg Interface

	TestFpgaCommsMsg() ;


	/**
	 * Destructor
	 */
	virtual ~TestFpgaCommsMsg() ;

	/**
	 * Get the message type
	 * @return type of message
	 */
	virtual IFpgaPdu::PduDataType getType() const override ;

	/**
	 * Get the underlying PDU from this message
	 * @return PDU
	 */
	virtual std::shared_ptr<IFpgaPdu> getPdu() const override ;

	/**
	 * Get PDU data as a string (with any leading/trailing spaces trimmed)
	 * @return PDU string
	 */
	virtual std::string getPduData() const override ;

	/**
	 * Output the message to the specified stream
	 */
	virtual void show(std::ostream& os = std::cout) const override ;

	/**
	 * Every message will be tagged with a monotonic ID number to assist with tracking. Internally
	 * will be stored in a suitably sized type compatible with the fpga hardware)
	 */
	virtual unsigned getId() const override ;

	/**
	 * Was there an error during message construction?
	 * @return true if error
	 */
	virtual bool isError() const override ;

	/**
	 * If there has been an error, this returns an error message
	 * @return error message if error; empty otherwise
	 */
	virtual std::string errorReason() const override ;

	/**
	 * Converts the message data into a string. For response types this converts any token values into strings
	 * and any enumerated type values into enumerations.
	 *
	 * @return string representation of message
	 */
	virtual std::string toString() const override ;

	/**
	 * Does this message ID match that in the specified message? If one or other of the messages does not have an ID set then assumes they
	 * match (had to have a relaxed approach because the of inconsistency in replies!)
	 * @param msg	Message to compare this message with
	 * @return true if IDs match
	 */
	virtual bool isIdMatch(std::shared_ptr<IFpgaMsg>& msg) const override ;

	/**
	 * Get the message as a string
	 * @return message string
	 */
	virtual std::string getStr() const override ;


	/**
	 * Every reply will have a token 'response' set to 'ACK' or 'NACK'. This returns TRUE for 'ACK', FALSE for 'NACK'.
	 * Replies with true if no response token is found (e.g. for commands)
	 */
	virtual bool getAck() const override ;

	/**
	 * Extract the var=value pairs from the message
	 * @return map of var=value pairs
	 */
	virtual std::map<std::string, DataVariant> getAttributes() const override ;


	// Test interface
	TestFpgaCommsMsg(const std::string& cmd,
			const std::vector<DataVariant>& attributes,
			const std::set<std::string>& varNames) ;


private:
	std::string mCmd ;
	std::vector<DataVariant> mAttributes ;
	std::set<std::string> mVarNames ;

} ;

}

#endif /* TestFpgaCommsMsg_H_ */

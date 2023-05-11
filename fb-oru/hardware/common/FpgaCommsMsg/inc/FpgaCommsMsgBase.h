/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgBase.h
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


#ifndef FpgaCommsMSGBASE_H_
#define FpgaCommsMSGBASE_H_

#include <iostream>
#include <string>
#include <map>
#include <set>

#include "Mutex.h"

#include "Tokeniser.h"

#include "IFpgaMsg.h"
#include "IFpgaMsgTokens.h"


namespace Mplane {

class FpgaCommsMsgBase : public IFpgaMsg
{
public:
	/**
	 * Construct a message from a text only PDU. The param textMsg is a dummy used to select this constructor
	 *
	 * @param pdu
	 */
	FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu, bool textMsg) ;

	/**
	 * Construct a message from a text only PDU. The param textMsg is a dummy used to select this constructor
	 *
	 * @param pdu
	 */
	FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu, bool textMsg) ;



	// IFpgaMsg Interface

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) ;

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) ;

	/**
	 * Construct a message from a command and a map of attribute key/value pairs
	 *
	 * @param cmd	Command type to create
	 * @param attributes	map of key/value pairs to use with the command
	 * @param varNames	[optional] set of variable names to use with command (used with 'get' command etc)
	 *
	 */
	FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens,
			const std::string& cmd,
			const std::vector<DataVariant>& attributes = std::vector<DataVariant>{},
			const std::set<std::string>& varNames = std::set<std::string>{}) ;

	/**
	 * Construct a new reply message
	 *
	 * @param msgId		Message ID of the command we're replying to
	 * @param attributes	map of key/value pairs to use with the reply
	 *
	 */
	FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens,
			unsigned msgId,
			const std::vector<DataVariant>& attributes = std::vector<DataVariant>{}) ;


	/**
	 * Destructor
	 */
	virtual ~FpgaCommsMsgBase() ;

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

protected:
	void setAck(bool ack) ;
	std::string toTokenString(const std::string& data, unsigned& dataPos) const ;
	std::map<std::string, DataVariant> getTokenAttributes(const std::string& data, unsigned& dataPos) const ;

	std::shared_ptr<IFpgaMsgTokens> getMsgTokens() const ;

	bool readByte(const std::string& data, unsigned& dataPos, unsigned char& value) const ;
	bool readShort(const std::string& data, unsigned& dataPos, unsigned short& value) const ;
	bool readWord(const std::string& data, unsigned & dataPos, unsigned int& value) const ;

	bool readInt(const std::string& data, unsigned& dataPos, int& value) const ;
	bool readFloat(const std::string& data, unsigned& dataPos, float& value) const ;
	bool readEnum(const std::string& data, unsigned & dataPos, std::string& value) const ;

	static int nextId() ;

private:
	void addByte(std::vector<UINT8>& vec, UINT8 value) const;
	void addShort(std::vector<UINT8>& vec, unsigned short value) const ;
	void addWord(std::vector<UINT8>& vec, unsigned value) const ;

	void addVariableInt(std::vector<UINT8>& vec, unsigned short id, int value) const ;
	void addVariableFloat(std::vector<UINT8>& vec, unsigned short id, float value) const ;
	void addVariableEnum(std::vector<UINT8>& vec, unsigned short id, const std::string& value) const ;

	std::shared_ptr<IFpgaPdu> pduFromCommand(const std::string& cmd,
			const std::vector<DataVariant>& attributes,
			const std::set<std::string>& varNames) ;
	void idFromPdu(const IFpgaPdu& pdu) ;

	std::shared_ptr<IFpgaPdu> pduFromDataVariants(const std::vector<DataVariant>& attributes) ;


private:
	// Static message ID counter
	static Mutex mIdMutex ;
	static short unsigned mUniqueId ;

	std::shared_ptr<IFpgaMsgTokens> mMsgTokens ;

	// Error during construction
	bool mError ;

	// Error string on error
	std::string mErrorString ;

	// Unique ID
	bool mIdSet ;
	int mId ;

	// The PDU
	std::shared_ptr<IFpgaPdu>	mPdu ;

	// Reply ACK/NACK
	bool mAck ;

	// String representation of message
	std::string	mMessageStr ;

	// Map of the attributes used in this message (cache)
	mutable bool mAttributesSet ;
	mutable std::map<std::string, DataVariant> mAttributes ;
} ;

}

#endif /* FpgaCommsMSGBASE_H_ */

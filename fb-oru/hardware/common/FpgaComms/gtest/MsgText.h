/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MsgText.h
 * \brief     Test message
 *
 *
 * \details
 *
 */


#ifndef MSGTEXT_H_
#define MSGTEXT_H_

#include <memory>
#include <vector>
#include <string>

#include "stringfunc.hpp"
#include "IFpgaMsg.h"
#include "IFpgaPdu.h"
#include "FpgaPdu.h"

namespace Mplane {

class MsgText : public IFpgaMsg
{
public:
	MsgText() : mId(101), mPdu(), mAck(true) {}
	virtual ~MsgText() {}

/////////////
	virtual std::string getStr() const override {
		return "" ;
	}
	virtual bool getAck() const override {
		return true ;
	}
	virtual std::map<std::string, DataVariant> getAttributes() const override {
		return std::map<std::string, DataVariant>() ;
	}
/////////////

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	MsgText(const IFpgaPdu& pdu) : mId(102), mPdu(new FpgaPdu(pdu)), mAck(true) {}

	/**
	 * Construct a message from a log/event/response PDU. Converts all token values into token strings
	 *
	 * @param pdu
	 */
	MsgText(std::shared_ptr<IFpgaPdu> pdu) : mId(103), mPdu(pdu), mAck(true) {}

	/**
	 * Get the message type
	 * @return type of message
	 */
	virtual IFpgaPdu::PduDataType getType() const  override { return mPdu->getType(); }

	/**
	 * Get the underlying PDU from this message
	 * @return PDU
	 */
	virtual std::shared_ptr<IFpgaPdu> getPdu() const  override { return mPdu; }

	/**
	 * Get PDU data as a string (with any leading/trailing spaces trimmed)
	 * @return PDU string
	 */
	virtual std::string getPduData() const  override {
		std::string spaces(" \t\n\r") ;
		spaces.push_back('\0') ;
		std::string pduData(trim(mPdu->getData(), spaces)) ;

		return pduData ;
	}

	/**
	 * Output the message to the specified stream
	 */
	virtual void show(std::ostream& os) const  override {  }

	/**
	 * Every message will be tagged with a monotonic ID number to assist with tracking. Internally
	 * will be stored in a suitably sized type compatible with the fpga hardware)
	 */
	virtual unsigned getId() const  override { return mId; }

	/**
	 * Was there an error during message construction?
	 * @return true if error
	 */
	virtual bool isError() const  override { return false; }

	/**
	 * If there has been an error, this returns an error message
	 * @return error message if error; empty otherwise
	 */
	virtual std::string errorReason() const  override { return ""; }

	/**
	 * Converts the message data into a string. For response types this converts any token values into strings
	 * and any enumerated type values into enumerations.
	 *
	 * @return string representation of message
	 */
	virtual std::string toString() const  override { return ""; }

	/**
	 * Does this message ID match that in the specified message? If one or other of the messages does not have an ID set then assumes they
	 * match (had to have a relaxed approach because the of inconsistency in replies!)
	 * @param msg	Message to compare this message with
	 * @return true if IDs match
	 */
	virtual bool isIdMatch(std::shared_ptr<IFpgaMsg>& msg) const  override { return true; }

private:
	// Unique ID
	int mId ;

	// The PDU
	std::shared_ptr<IFpgaPdu>	mPdu ;

	// Reply ACK/NACK
	bool mAck ;

} ;

}

#endif /* MSGTEXT_H_ */

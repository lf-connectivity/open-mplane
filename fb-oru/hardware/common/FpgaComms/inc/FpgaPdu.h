/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaPdu.h
 * \brief     A single PDU to/from FPGA
 *
 *
 * \details
 *
 */


#ifndef FPGAPDU_H_
#define FPGAPDU_H_

#include <memory>
#include "IFpgaPdu.h"

namespace Mplane {

class FpgaPdu : public IFpgaPdu
{
public:
	using PduDataType = IFpgaPdu::PduDataType ;

	/**
	 * Create a message using the type and a message string
	 * @param type
	 * @param data
	 */
	FpgaPdu(PduDataType type, const std::string& data) ;

	/**
	 * Create a message using the type byte code and a vector of bytes
	 * @param typeByte
	 * @param data
	 */
	FpgaPdu(UINT8 typeByte, const std::vector<UINT8>& data) ;

	/**
	 * Create a message using the type byte code and a vector of bytes
	 * @param type
	 * @param data
	 */
	FpgaPdu(PduDataType type, const std::vector<UINT8>& data) ;

	/**
	 * Create a message using the vector of bytes. First byte in vector is the type
	 * @param data
	 */
	explicit FpgaPdu(const std::vector<UINT8>& data) ;

	// Destructor
	virtual ~FpgaPdu() ;

	// Create from an IFpgaPdu ref
	// cppcheck-suppress noExplicitConstructor
	FpgaPdu(const IFpgaPdu& pdu) ;

	// Create from an IFpgaPdu shared pointer
	// cppcheck-suppress noExplicitConstructor
	FpgaPdu(std::shared_ptr<IFpgaPdu> pdu) ;


	/**
	 * Get the type of the message
	 * @return type
	 */
	virtual PduDataType getType() const override ;

	/**
	 * Get the message as a string
	 * @return message string
	 */
	virtual std::string getData() const override ;

	/**
	 * Get the type of the message as a byte code used for sending/receiving messages
	 * @return type
	 */
	virtual UINT8 getTypeByte() const override ;

	/**
	 * Get the message part as a vector of bytes (excludes header)
	 * @return message bytes
	 */
	virtual std::vector<UINT8> getDataBytes() const override ;

	/**
	 * Get the PDU as a vector of bytes (header and message)
	 * @return PDU bytes
	 */
	virtual std::vector<UINT8> getBytes() const override ;

	/**
	 * Convert PDU to a printable string of hex bytes
	 */
	virtual std::string toString() const override ;


private:
	void dataToBytes() ;
	void dataFromBytes() ;

	static UINT8 typeByteFromBytes(const std::vector<UINT8>& bytes) ;
	static std::vector<UINT8> dataBytesFromBytes(const std::vector<UINT8>& bytes) ;

private:
	// message stored as string
	bool mDataValid ;
	PduDataType	mType ;
	std::string mData ;

	// message stored as bytes
	bool mDataBytesValid ;
	UINT8 mTypeByte ;
	std::vector<UINT8> mDataBytes ;
} ;

}

#endif /* FPGAPDU_H_ */

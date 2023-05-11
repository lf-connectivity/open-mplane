/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFpgaPdu.h
 * \brief     A single PDU to/from FPGA
 *
 *
 * \details
 *
 */


#ifndef IFPGAPDU_H_
#define IFPGAPDU_H_

#include "GlobalTypeDefs.h"
#include <string>
#include <vector>

namespace Mplane {

class IFpgaPdu {
public:
	/**
	 * Data types
	 */
	enum PduDataType {
		PDU_TYPE_NONE	= '\0',
		PDU_TYPE_CMD	= 'C',
		PDU_TYPE_REPLY	= 'R',
		PDU_TYPE_EVENT	= 'E',
		PDU_TYPE_ALARM	= 'A',
		PDU_TYPE_LOG	= 'L',
		PDU_TYPE_MATLAB	= 'M',
		PDU_TYPE_TEXT	= 'T',
	};

	//-------------------------------------------------------------------------------------------------------------
	//
	// Format is:
	//
	//    0       1        2       3       4
	// +-------+-------+-------+-------+-------+-------+--...-----+
	// | TYPE  |///////|   LENGTH      |  DATA                    |
	// +-------+-------+-------+-------+-------+-------+--...-----+
	//
	//
	static const unsigned PDU_OFFSET_TYPE{0} ;
	static const unsigned PDU_OFFSET_LENGTH{2} ;
	static const unsigned PDU_OFFSET_DATA{4} ;

	static const unsigned PDU_HEAD_LEN{PDU_OFFSET_DATA} ;

	/**
	 * Convert the PduDataType into a string
	 * @param type
	 * @return string (empty for type PDU_TYPE_NONE)
	 */
	static std::string typeToStr(PduDataType type) ;

	/**
	 * Convert the string into a PduDataType
	 * @param str
	 * @return type or PDU_TYPE_NONE if unable to convert
	 */
	static PduDataType strToType(const std::string& str) ;

	IFpgaPdu() {}


	// Descructor
	virtual ~IFpgaPdu() {}

	/**
	 * Get the type of the message
	 * @return type
	 */
	virtual PduDataType getType() const =0 ;

	/**
	 * Get the message as a string
	 * @return message string
	 */
	virtual std::string getData() const =0 ;

	/**
	 * Get the type of the message as a byte code used for sending/receiving messages
	 * @return type
	 */
	virtual UINT8 getTypeByte() const =0 ;

	/**
	 * Get the message part as a vector of bytes (excludes header)
	 * @return message bytes
	 */
	virtual std::vector<UINT8> getDataBytes() const =0 ;

	/**
	 * Get the PDU as a vector of bytes (header and message)
	 * @return PDU bytes
	 */
	virtual std::vector<UINT8> getBytes() const =0 ;

	/**
	 * Convert PDU to a printable string of hex bytes
	 */
	virtual std::string toString() const =0 ;

} ;

}

#endif /* IFPGAPDU_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaPdu.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>

#include "stringfunc.hpp"
#include "IFpgaCommsConstants.h"
#include "FpgaPdu.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
//
// Format is:
//
//    0       1        2       3       4
// +-------+-------+-------+-------+-------+-------+--...-----+
// | TYPE  | ~TYPE |   LENGTH      |  DATA                    |
// +-------+-------+-------+-------+-------+-------+--...-----+
//
//
static const unsigned PDU_OFFSET_TYPE{0} ;
static const unsigned PDU_OFFSET_INV_TYPE{1} ;
static const unsigned PDU_OFFSET_LENGTH{2} ;
static const unsigned PDU_OFFSET_DATA{4} ;

static const unsigned PDU_HEAD_LEN{PDU_OFFSET_DATA} ;

//-------------------------------------------------------------------------------------------------------------
const std::map<FpgaPdu::PduDataType, UINT8> typeMap{
	{FpgaPdu::PDU_TYPE_NONE, 		(UINT8)0},
	{FpgaPdu::PDU_TYPE_CMD, 		(UINT8)TYPE_BYTE_COMMAND},
	{FpgaPdu::PDU_TYPE_REPLY, 		(UINT8)TYPE_BYTE_RESPONSE},
	{FpgaPdu::PDU_TYPE_EVENT, 		(UINT8)TYPE_BYTE_EVENT},
	{FpgaPdu::PDU_TYPE_LOG, 		(UINT8)TYPE_BYTE_LOG},
	{FpgaPdu::PDU_TYPE_MATLAB,		(UINT8)TYPE_BYTE_MATLAB},
	{FpgaPdu::PDU_TYPE_TEXT, 		(UINT8)TYPE_BYTE_TEXT},
} ;

//-------------------------------------------------------------------------------------------------------------
const std::map<IFpgaPdu::PduDataType, std::string> typeStrMap{
	{IFpgaPdu::PDU_TYPE_NONE, 		""},
	{IFpgaPdu::PDU_TYPE_CMD, 		"CMD"},
	{IFpgaPdu::PDU_TYPE_REPLY, 		"REPLY"},
	{IFpgaPdu::PDU_TYPE_EVENT, 		"EVENT"},
	{IFpgaPdu::PDU_TYPE_LOG, 		"LOG"},
	{IFpgaPdu::PDU_TYPE_MATLAB, 	"MATLAB"},
	{IFpgaPdu::PDU_TYPE_TEXT, 		"TEXT"},
} ;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::string IFpgaPdu::typeToStr(IFpgaPdu::PduDataType type)
{
	return typeStrMap.at(type) ;
}

//-------------------------------------------------------------------------------------------------------------
IFpgaPdu::PduDataType IFpgaPdu::strToType(const std::string& str)
{
	std::string STR(toUpper(str)) ;
	for (auto entry : typeStrMap)
	{
		if (entry.second == STR)
			return entry.first ;
	}
	return FpgaPdu::PDU_TYPE_NONE ;
}



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::FpgaPdu(const IFpgaPdu& pdu) :
	mDataValid(false),
	mType(PDU_TYPE_NONE),
	mData(),

	mDataBytesValid(true),
	mTypeByte(pdu.getTypeByte()),
	mDataBytes(pdu.getDataBytes())
{
	dataFromBytes() ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::FpgaPdu(std::shared_ptr<IFpgaPdu> pdu) :
	mDataValid(false),
	mType(PDU_TYPE_NONE),
	mData(),

	mDataBytesValid(true),
	mTypeByte(pdu->getTypeByte()),
	mDataBytes(pdu->getDataBytes())
{
	dataFromBytes() ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::FpgaPdu(PduDataType type, const std::string& data) :
	mDataValid(true),
	mType(type),
	mData(data),

	mDataBytesValid(false),
	mTypeByte(0),
	mDataBytes()
{
	dataToBytes() ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::FpgaPdu(UINT8 typeByte, const std::vector<UINT8>& data) :
	mDataValid(false),
	mType(PDU_TYPE_NONE),
	mData(),

	mDataBytesValid(true),
	mTypeByte(typeByte),
	mDataBytes(data)
{
	dataFromBytes() ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::FpgaPdu(PduDataType type, const std::vector<UINT8>& data) :
	mDataValid(false),
	mType(type),
	mData(),

	mDataBytesValid(true),
	mTypeByte(typeMap.at(mType)),
	mDataBytes(data)
{
	dataFromBytes() ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::FpgaPdu(const std::vector<UINT8>& data) :
	mDataValid(false),
	mType(PDU_TYPE_NONE),
	mData(),

	mDataBytesValid(true),
	mTypeByte(typeByteFromBytes(data)),
	mDataBytes(dataBytesFromBytes(data))

{
	dataFromBytes() ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::~FpgaPdu()
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::PduDataType FpgaPdu::getType() const
{
	return mType ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaPdu::getData() const
{
	return mData ;
}

//-------------------------------------------------------------------------------------------------------------
UINT8 FpgaPdu::getTypeByte() const
{
	return mTypeByte ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<UINT8> FpgaPdu::getDataBytes() const
{
	return mDataBytes ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<UINT8> Mplane::FpgaPdu::getBytes() const
{
	std::vector<UINT8> bytes(mDataBytes) ;

	// length
	unsigned short length(mDataBytes.size()) ;
	bytes.insert(bytes.begin(), length&0xff) ;
	bytes.insert(bytes.begin(), (length>>8)&0xff) ;
	bytes.insert(bytes.begin(), ~mTypeByte) ;
	bytes.insert(bytes.begin(), mTypeByte) ;
	return bytes ;
}


//-------------------------------------------------------------------------------------------------------------
std::string Mplane::FpgaPdu::toString() const
{
	std::stringstream ss ;
	unsigned size(mDataBytes.size()) ;

//	ss << std::hex << std::setw(4) << std::setfill(0) ;
	ss << std::hex ;
	ss << "HEAD[ " ;
	ss << "0x" << (static_cast<unsigned>(mTypeByte) & 0xff) << " 0xXX " ;
	ss << "0x" << ((size >> 8) & 0xff) << " 0x" << (size & 0xff) ;
	ss << " ] DATA[" ;
	for (auto byte : mDataBytes)
		ss << " 0x" << (static_cast<unsigned>(byte) & 0xff) ;
	ss << " ]" ;
	return ss.str() ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void FpgaPdu::dataToBytes()
{
	if (mDataBytesValid)
		return ;

	mTypeByte = typeMap.at(mType) ;

	mDataBytes.resize(mData.size(), ' ') ;
	unsigned idx = 0 ;
	for (auto cc : mData)
		mDataBytes[idx++] = static_cast<UINT8>(cc) ;

	mDataBytesValid = true ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaPdu::dataFromBytes()
{
	if (mDataValid)
		return ;

	// convert byte value into a type enum
	auto entry( std::find_if(typeMap.begin(), typeMap.end(),
		[this](std::map<FpgaPdu::PduDataType, UINT8>::value_type const& it)->bool{
			return mTypeByte == it.second ;
		}) );
	if (entry != typeMap.end())
		mType = entry->first ;

	mData.clear() ;
	mData.insert(mData.begin(), mDataBytes.begin(), mDataBytes.end()) ;
	mDataValid = true ;
}

//-------------------------------------------------------------------------------------------------------------
UINT8 FpgaPdu::typeByteFromBytes(const std::vector<UINT8>& bytes)
{
	if (bytes.empty())
		return 0 ;

	return bytes.front() ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<UINT8> FpgaPdu::dataBytesFromBytes(const std::vector<UINT8>& bytes)
{
	if (bytes.size() <= PDU_HEAD_LEN)
		return std::vector<UINT8>() ;

	return std::vector<UINT8>(bytes.begin()+PDU_OFFSET_DATA, bytes.end()) ;
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RemoteCommsMsgBase.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>

#include "stringfunc.hpp"

#include "FpgaPdu.h"
#include "RemoteCommsMsgBase.h"

using namespace Mplane;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RemoteCommsMsgBase::RemoteCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mPdu(new FpgaPdu(pdu) ),
	mAck(true),
	mMessageStr(mPdu->getData()),
	mAttributesSet(false),
	mAttributes()
{
//	std::cerr << "RemoteCommsMsgBase(pdu&)" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteCommsMsgBase::RemoteCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mPdu(new FpgaPdu(pdu) ),
	mAck(true),
	mMessageStr(mPdu->getData()),
	mAttributesSet(false),
	mAttributes()
{
//	std::cerr << "RemoteCommsMsgBase(pdu*)" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteCommsMsgBase::RemoteCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens,
		const std::string& cmd,
		const std::vector<DataVariant>& attributes,
		const std::set<std::string>& varNames) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mPdu(pduFromCommand(cmd, attributes, varNames)),
	mAck(true),
	mMessageStr(""),
	mAttributesSet(false),
	mAttributes()
{
//	std::cerr << "RemoteCommsMsgBase(cmd)" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
RemoteCommsMsgBase::RemoteCommsMsgBase(
		std::shared_ptr<IFpgaMsgTokens> tokens, unsigned msgId,
		const std::vector<DataVariant>& attributes) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mPdu(pduFromDataVariants(attributes)),
	mAck(true),
	mMessageStr(""),
	mAttributesSet(false),
	mAttributes()
{
	(void)msgId;
}



//-------------------------------------------------------------------------------------------------------------
RemoteCommsMsgBase::~RemoteCommsMsgBase()
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::PduDataType RemoteCommsMsgBase::getType() const
{
	return mPdu->getType() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaPdu> RemoteCommsMsgBase::getPdu() const
{
	return mPdu ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RemoteCommsMsgBase::getPduData() const
{
	std::string pduData(mPdu->getData()) ;
	return pduData ;
}


//-------------------------------------------------------------------------------------------------------------
std::string RemoteCommsMsgBase::getStr() const
{
	return mMessageStr ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteCommsMsgBase::show(std::ostream& os) const
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned RemoteCommsMsgBase::getId() const
{
	return 0 ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::getAck() const
{
	return mAck ;
}


//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::isError() const
{
	return mError ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RemoteCommsMsgBase::errorReason() const
{
	return mErrorString ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RemoteCommsMsgBase::toString() const
{
	// Default is to return the PDU data
	std::string str( getPduData() ) ;

	// strip any NUL (from C code)
	while (!str.empty() && (str.back() == '\0'))
	{
		str.resize(str.length()-1) ;
	}
	return str ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::isIdMatch(std::shared_ptr<IFpgaMsg>& msg) const
{
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
std::map<std::string, DataVariant> RemoteCommsMsgBase::getAttributes() const
{
	// Default is no attributes
	return std::map<std::string, DataVariant>() ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, DataVariant> RemoteCommsMsgBase::getTokenAttributes(const std::string& pduData, unsigned& dataPos) const
{
	// use cache
	if (mAttributesSet)
		return mAttributes ;

	// Process the attributes
	unsigned short attrib ;
	while ( readShort(pduData, dataPos, attrib) )
	{
		// skip any non-state tokens (e.g. command tokens)
		if (!mMsgTokens->isStateToken(attrib))
			continue ;

		// get name of attribute
		std::string var(mMsgTokens->getStateTokenStr(attrib)) ;
		if (var.empty())
			return std::map<std::string, DataVariant>() ;

		// lookup type
		DataVariantType::Type type(mMsgTokens->getStateType(attrib)) ;
		std::string typeStr(mMsgTokens->getStateTypeStr(attrib)) ;

		// Create variant
		DataVariant dv(var, typeStr) ;

		// handle each type
		switch (type)
		{
			case DataVariantType::Int:
			{
				int value ;
				if (!readInt(pduData, dataPos, value))
					return std::map<std::string, DataVariant>() ;

				dv.set(value) ;
			}
			break ;

			case DataVariantType::Enum:
			{
				std::string value ;
				if (!readEnum(pduData, dataPos, value))
					return std::map<std::string, DataVariant>() ;

				dv.set(value) ;
			}
			break ;

			case DataVariantType::Float:
			{
				float value ;
				if (!readFloat(pduData, dataPos, value))
					return std::map<std::string, DataVariant>() ;

				dv.set(value) ;
			}
			break ;

			case DataVariantType::String:
			{
				std::string value;
				if (!readString(pduData, dataPos, value))
					return std::map<std::string, DataVariant>() ;

				dv.set(value) ;
			}
			break;

			case DataVariantType::None:
			default:
			break ;

		}

		// set attribute
		mAttributes[var] = dv ;

	} // while

	mAttributesSet = true ;
	return mAttributes ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RemoteCommsMsgBase::toTokenString(const std::string& pduData, unsigned& dataPos) const
{
	// Need to convert tokens
	std::stringstream ss ;

	std::map<std::string, DataVariant> attributes( getTokenAttributes(pduData, dataPos) ) ;
	for (auto attr : attributes)
	{
		if (!ss.str().empty())
			ss << " " ;
		ss << attr.first << "=" << attr.second.toString() ;
	}

	return ss.str() ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteCommsMsgBase::setAck(bool ack)
{
	mAck = ack ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsgTokens> RemoteCommsMsgBase::getMsgTokens() const
{
	return mMsgTokens ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::readByte(const std::string& data, unsigned & dataPos, unsigned char& value) const
{
	if (dataPos+1 > data.size())
		return false ;

	value = static_cast<unsigned char>(data[dataPos]) ;
	dataPos++ ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::readShort(const std::string& data, unsigned & dataPos, unsigned short & value) const
{
	if (dataPos+2 > data.size())
		return false ;

	value = ((static_cast<unsigned short>(data[dataPos]) & 0xff) << 8) +
			(static_cast<unsigned short>(data[dataPos+1]) & 0xff) ;
	dataPos += 2 ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::readWord(const std::string& data, unsigned & dataPos, unsigned int& value) const
{
	if (dataPos+4 > data.size())
		return false ;

	value = ((static_cast<int>(data[dataPos]) & 0xff) << 24) +
			((static_cast<int>(data[dataPos+1]) & 0xff) << 16) +
			((static_cast<int>(data[dataPos+2]) & 0xff) << 8) +
			(static_cast<int>(data[dataPos+3]) & 0xff) ;
	dataPos += 4 ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::readInt(const std::string& data, unsigned & dataPos, int& value) const
{
	unsigned int word ;
	if (!readWord(data, dataPos, word))
		return false ;

	value = static_cast<int>(word) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::readFloat(const std::string& data, unsigned & dataPos, float& value) const
{
	unsigned int word ;
	if (!readWord(data, dataPos, word))
		return false ;

	// cppcheck-suppress invalidPointerCast
	float* fptr = (float*)(&word) ;

	value = *fptr ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::readEnum(const std::string& data, unsigned & dataPos, std::string& value) const
{
	unsigned char enumId ;
	if (!readByte(data, dataPos, enumId))
		return false ;

	// convert to enumeration value
	value = mMsgTokens->getTokenStr(enumId) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool RemoteCommsMsgBase::readString(const std::string& data, unsigned & dataPos, std::string& value) const
{

	if (dataPos+2 > data.size())	// expect at least two quotes to delimit string characters
		return false ;

	if (data[dataPos++] != '"')
		return false;

	while (dataPos < data.size())
	{
		char c = data[dataPos++];
		if (c == '"')
			return true;
		value.push_back(c);
	}
	return false ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void RemoteCommsMsgBase::addByte(std::vector<UINT8>& vec, UINT8 value) const
{
	vec.push_back(value) ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteCommsMsgBase::addShort(std::vector<UINT8>& vec, unsigned short value) const
{
	vec.push_back(static_cast<UINT8>((value >> 8) & 0xff)) ;
	vec.push_back(static_cast<UINT8>(value & 0xff)) ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteCommsMsgBase::addWord(std::vector<UINT8>& vec, unsigned value) const
{
	vec.push_back(static_cast<UINT8>((value >> 24) & 0xff)) ;
	vec.push_back(static_cast<UINT8>((value >> 16) & 0xff)) ;
	vec.push_back(static_cast<UINT8>((value >> 8) & 0xff)) ;
	vec.push_back(static_cast<UINT8>(value & 0xff)) ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteCommsMsgBase::addVariableInt(std::vector<UINT8>& vec, unsigned short id, int value) const
{
	addShort(vec, id) ;
	addWord(vec, static_cast<unsigned>(value)) ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteCommsMsgBase::addVariableFloat(std::vector<UINT8>& vec, unsigned short id, float value) const
{
	addShort(vec, id) ;

	// cppcheck-suppress invalidPointerCast
	unsigned* uiptr = (unsigned *)(&value) ;

	addWord(vec, *uiptr) ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteCommsMsgBase::addVariableEnum(std::vector<UINT8>& vec, unsigned short id, const std::string& value) const
{
	// convert from enum
	int eval = mMsgTokens->getToken(value) ;
	addShort(vec, id) ;
	addByte(vec, static_cast<UINT8>(eval)) ;
}

//-------------------------------------------------------------------------------------------------------------
void RemoteCommsMsgBase::addVariableString(std::vector<UINT8>& vec, unsigned short id, const std::string& value) const
{
	addShort(vec, id) ;
	addByte(vec, '\"') ;
	for (auto c : value)
		addByte(vec, c) ;
	addByte(vec, '\"') ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaPdu> RemoteCommsMsgBase::pduFromCommand(const std::string& cmd,
		const std::vector<DataVariant>& attributes,
		const std::set<std::string>& varNames)
{

	// Convert command, attributes, and variables into token values
	std::vector<UINT8> pduData ;

	// command
	addShort(pduData, mMsgTokens->getCmdToken(cmd)) ;

//	// msgid
//	addVariableInt(pduData, mMsgTokens->getStateToken("msgId"), mId) ;

	// Add attributes
	for (auto attr : attributes)
	{
		// skip if not set
		if (!attr.isSet())
			continue ;

		int token( mMsgTokens->getStateToken(attr.getName()) ) ;
		if (token < 0)
		{
			// Error
			mError = true ;
			mErrorString = "Invalid attribute: " + attr.getName() ;

			return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_NONE, "") ) ;
		}

		// process all types
		switch (attr.getType())
		{
		case DataVariantType::Int:
			addVariableInt(pduData, token, attr.toInt()) ;
			break ;

		case DataVariantType::Enum:
			addVariableEnum(pduData, token, attr.toString()) ;
			break ;

		case DataVariantType::Float:
			addVariableFloat(pduData, token, attr.toFloat()) ;
			break ;

		case DataVariantType::String:
			addVariableString(pduData, token, attr.toString()) ;
			break;

		case DataVariantType::None:
		default:
			return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_NONE, "") ) ;
			break ;
		}
	}

	// Add any variables
	for (auto var : varNames)
	{
		int token( mMsgTokens->getStateToken(var) ) ;
		if (token < 0)
		{
			// Error
			mError = true ;
			mErrorString = "Invalid variable: " + var ;

			return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_NONE, "") ) ;
		}


		// lookup type
		DataVariantType::Type type(mMsgTokens->getStateType(var)) ;

		// handle each type
		switch (type)
		{
			case DataVariantType::Int:
				addVariableInt(pduData, token, 0) ;
			break ;

			case DataVariantType::Enum:
				addVariableEnum(pduData, token, mMsgTokens->getStateDefault(var)) ;
			break ;

			case DataVariantType::Float:
				addVariableFloat(pduData, token, 0.0) ;
			break ;

			case DataVariantType::String:
				addVariableString(pduData, token, "") ;
				break;

			case DataVariantType::None:
			default:
			break ;
		}
	}

	// done
	return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_CMD, pduData) ) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaPdu> RemoteCommsMsgBase::pduFromDataVariants(const std::vector<DataVariant>& attributes)
{
	// Convert command, attributes, and variables into token values
	std::vector<UINT8> pduData ;

//	// msgid
//	addVariableInt(pduData, mMsgTokens->getStateToken("msgId"), mId) ;

	// Add attributes
	for (auto attr : attributes)
	{
		// skip if not set
		if (!attr.isSet())
			continue ;

		int token( mMsgTokens->getStateToken(attr.getName()) ) ;
		if (token < 0)
		{
			// Error
			mError = true ;
			mErrorString = "Invalid attribute: " + attr.getName() ;

			return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_NONE, "") ) ;
		}

		// process all types
		switch (attr.getType())
		{
		case DataVariantType::Int:
			addVariableInt(pduData, token, attr.toInt()) ;
			break ;

		case DataVariantType::Enum:
			addVariableEnum(pduData, token, attr.toString()) ;
			break ;

		case DataVariantType::Float:
			addVariableFloat(pduData, token, attr.toFloat()) ;
			break ;

		case DataVariantType::String:
			addVariableString(pduData, token, attr.toString()) ;
			break ;

		case DataVariantType::None:
		default:
			return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_NONE, "") ) ;
			break ;
		}
	}

	// done
	return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_CMD, pduData) ) ;
}

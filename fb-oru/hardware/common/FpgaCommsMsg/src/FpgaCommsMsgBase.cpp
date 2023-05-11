/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgBase.cpp
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
#include "FpgaCommsMsgBase.h"

using namespace Mplane;


//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mutex FpgaCommsMsgBase::mIdMutex ;
short unsigned FpgaCommsMsgBase::mUniqueId = 0 ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgBase::FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu,
		bool textMsg) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mIdSet(false),
	mId(0),
	mPdu(new FpgaPdu(pdu) ),
	mAck(true),
	mMessageStr(mPdu->getData()),
	mAttributesSet(false),
	mAttributes()
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgBase::FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu,
		bool textMsg) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mIdSet(false),
	mId(0),
	mPdu(new FpgaPdu(pdu) ),
	mAck(true),
	mMessageStr(mPdu->getData()),
	mAttributesSet(false),
	mAttributes()
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgBase::FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mIdSet(false),
	mId(0),
	mPdu(new FpgaPdu(pdu) ),
	mAck(true),
	mMessageStr(mPdu->getData()),
	mAttributesSet(false),
	mAttributes()
{
//	std::cerr << "FpgaCommsMsgBase(pdu&)" << std::endl ;
	idFromPdu(pdu) ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgBase::FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mIdSet(false),
	mId(0),
	mPdu(new FpgaPdu(pdu) ),
	mAck(true),
	mMessageStr(mPdu->getData()),
	mAttributesSet(false),
	mAttributes()
{
//	std::cerr << "FpgaCommsMsgBase(pdu*)" << std::endl ;
	idFromPdu(*pdu) ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgBase::FpgaCommsMsgBase(std::shared_ptr<IFpgaMsgTokens> tokens,
		const std::string& cmd,
		const std::vector<DataVariant>& attributes,
		const std::set<std::string>& varNames) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mIdSet(true),
	mId(nextId()),
	mPdu(pduFromCommand(cmd, attributes, varNames)),
	mAck(true),
	mMessageStr(""),
	mAttributesSet(false),
	mAttributes()
{
//	std::cerr << "FpgaCommsMsgBase(cmd)" << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgBase::FpgaCommsMsgBase(
		std::shared_ptr<IFpgaMsgTokens> tokens, unsigned msgId,
		const std::vector<DataVariant>& attributes) :

	mMsgTokens(tokens),
	mError(false),
	mErrorString(""),

	mIdSet(true),
	mId(msgId),
	mPdu(pduFromDataVariants(attributes)),
	mAck(true),
	mMessageStr(""),
	mAttributesSet(false),
	mAttributes()
{
}



//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgBase::~FpgaCommsMsgBase()
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu::PduDataType FpgaCommsMsgBase::getType() const
{
	return mPdu->getType() ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaPdu> FpgaCommsMsgBase::getPdu() const
{
	return mPdu ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaCommsMsgBase::getPduData() const
{
	std::string pduData(mPdu->getData()) ;
	return pduData ;
}


//-------------------------------------------------------------------------------------------------------------
std::string FpgaCommsMsgBase::getStr() const
{
	return mMessageStr ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsMsgBase::show(std::ostream& os) const
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned FpgaCommsMsgBase::getId() const
{
	return mId ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsMsgBase::getAck() const
{
	return mAck ;
}


//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsMsgBase::isError() const
{
	return mError ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaCommsMsgBase::errorReason() const
{
	return mErrorString ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaCommsMsgBase::toString() const
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
bool FpgaCommsMsgBase::isIdMatch(std::shared_ptr<IFpgaMsg>& msg) const
{
	std::shared_ptr<FpgaCommsMsgBase> FpgaCommsMsg(std::dynamic_pointer_cast<FpgaCommsMsgBase>(msg)) ;

	if (!mIdSet || !FpgaCommsMsg->mIdSet)
		return true ;

	return mId == FpgaCommsMsg->mId ;
}


//-------------------------------------------------------------------------------------------------------------
std::map<std::string, DataVariant> FpgaCommsMsgBase::getAttributes() const
{
	// Default is no attributes
	return std::map<std::string, DataVariant>() ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, DataVariant> FpgaCommsMsgBase::getTokenAttributes(const std::string& pduData, unsigned& dataPos) const
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
				//TODO
				std::cerr << "FpgaCommsMsgBase::getTokenAttribute " << var << typeStr << std::endl;
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
std::string FpgaCommsMsgBase::toTokenString(const std::string& pduData, unsigned& dataPos) const
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
void FpgaCommsMsgBase::setAck(bool ack)
{
	mAck = ack ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaMsgTokens> FpgaCommsMsgBase::getMsgTokens() const
{
	return mMsgTokens ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsMsgBase::readByte(const std::string& data, unsigned & dataPos, unsigned char& value) const
{
	if (dataPos+1 > data.size())
		return false ;

	value = static_cast<unsigned char>(data[dataPos]) ;
	dataPos++ ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsMsgBase::readShort(const std::string& data, unsigned & dataPos, unsigned short & value) const
{
	if (dataPos+2 > data.size())
		return false ;

	value = ((static_cast<unsigned short>(data[dataPos]) & 0xff) << 8) +
			(static_cast<unsigned short>(data[dataPos+1]) & 0xff) ;
	dataPos += 2 ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsMsgBase::readWord(const std::string& data, unsigned & dataPos, unsigned int& value) const
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
bool FpgaCommsMsgBase::readInt(const std::string& data, unsigned & dataPos, int& value) const
{
	unsigned int word ;
	if (!readWord(data, dataPos, word))
		return false ;

	value = static_cast<int>(word) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaCommsMsgBase::readFloat(const std::string& data, unsigned & dataPos, float& value) const
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
bool FpgaCommsMsgBase::readEnum(const std::string& data, unsigned & dataPos, std::string& value) const
{
	unsigned char enumId ;
	if (!readByte(data, dataPos, enumId))
		return false ;

	// convert to enumeration value
	value = mMsgTokens->getTokenStr(enumId) ;

	return true ;
}


//=============================================================================================================
// PROTECTED STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int FpgaCommsMsgBase::nextId()
{
	Mutex::Lock lock(FpgaCommsMsgBase::mIdMutex) ;
	if (++FpgaCommsMsgBase::mUniqueId == 0)
		++FpgaCommsMsgBase::mUniqueId ;
	return FpgaCommsMsgBase::mUniqueId ;
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsMsgBase::addByte(std::vector<UINT8>& vec, UINT8 value) const
{
	vec.push_back(value) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsMsgBase::addShort(std::vector<UINT8>& vec, unsigned short value) const
{
	vec.push_back(static_cast<UINT8>((value >> 8) & 0xff)) ;
	vec.push_back(static_cast<UINT8>(value & 0xff)) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsMsgBase::addWord(std::vector<UINT8>& vec, unsigned value) const
{
	vec.push_back(static_cast<UINT8>((value >> 24) & 0xff)) ;
	vec.push_back(static_cast<UINT8>((value >> 16) & 0xff)) ;
	vec.push_back(static_cast<UINT8>((value >> 8) & 0xff)) ;
	vec.push_back(static_cast<UINT8>(value & 0xff)) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsMsgBase::addVariableInt(std::vector<UINT8>& vec, unsigned short id, int value) const
{
	addShort(vec, id) ;
	addWord(vec, static_cast<unsigned>(value)) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsMsgBase::addVariableFloat(std::vector<UINT8>& vec, unsigned short id, float value) const
{
	addShort(vec, id) ;

	// cppcheck-suppress invalidPointerCast
	unsigned* uiptr = (unsigned *)(&value) ;

	addWord(vec, *uiptr) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsMsgBase::addVariableEnum(std::vector<UINT8>& vec, unsigned short id, const std::string& value) const
{
	// convert from enum
	int eval = mMsgTokens->getToken(value) ;
	addShort(vec, id) ;
	addByte(vec, static_cast<UINT8>(eval)) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaPdu> FpgaCommsMsgBase::pduFromCommand(const std::string& cmd,
		const std::vector<DataVariant>& attributes,
		const std::set<std::string>& varNames)
{

	// Convert command, attributes, and variables into token values
	std::vector<UINT8> pduData ;

	// command
	addShort(pduData, mMsgTokens->getCmdToken(cmd)) ;

	// msgid
	addVariableInt(pduData, mMsgTokens->getStateToken("msgId"), mId) ;

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

			case DataVariantType::None:
			default:
			break ;
		}
	}

	// done
	return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_CMD, pduData) ) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaPdu> FpgaCommsMsgBase::pduFromDataVariants(const std::vector<DataVariant>& attributes)
{
	// Convert command, attributes, and variables into token values
	std::vector<UINT8> pduData ;

	// msgid
	addVariableInt(pduData, mMsgTokens->getStateToken("msgId"), mId) ;

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

		case DataVariantType::None:
		default:
			return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_NONE, "") ) ;
			break ;
		}
	}

	// done
	return std::shared_ptr<IFpgaPdu>(new FpgaPdu(FpgaPdu::PDU_TYPE_CMD, pduData) ) ;
}

//-------------------------------------------------------------------------------------------------------------
void FpgaCommsMsgBase::idFromPdu(const IFpgaPdu& pdu)
{
	// Assume this won't be a command and just process the data as if it's a reply etc
	std::string pduData(getPduData()) ;
	try {
		unsigned dataPos{0} ;
		std::map<std::string, DataVariant> attributes(getTokenAttributes(pduData, dataPos)) ;
		if (attributes.find("msgId") == attributes.end())
			return ;

		mIdSet = true ;
		mId = attributes["msgId"].toInt() ;

	} catch(...) {
		return ;
	}

}

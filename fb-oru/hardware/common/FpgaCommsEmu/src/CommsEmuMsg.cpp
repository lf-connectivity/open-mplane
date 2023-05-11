/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommsEmuMsg.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommsEmuMsg.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg::CommsEmuMsg(UINT8 type, const std::vector<UINT8>& data, bool valid) :
	mValid(valid),
	mPdu(type, data)
{
	// check the type
	if ( mPdu.getType() == FpgaPdu::PDU_TYPE_NONE )
		mValid = false ;

}

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg::CommsEmuMsg(FpgaPdu::PduDataType type, const std::vector<UINT8>& data) :
	mValid(true),
	mPdu(type, data)
{
	// check the type
	if ( mPdu.getType() == FpgaPdu::PDU_TYPE_NONE )
		mValid = false ;

}

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg::CommsEmuMsg(FpgaPdu::PduDataType type, const std::string& str) :
	mValid(true),
	mPdu(type, str)
{
	// check the type
	if ( mPdu.getType() == FpgaPdu::PDU_TYPE_NONE )
		mValid = false ;

}

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg::~CommsEmuMsg()
{
}

//-------------------------------------------------------------------------------------------------------------
bool CommsEmuMsg::isValid() const
{
	return mValid ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<UINT8> CommsEmuMsg::getData() const
{
	return mPdu.getDataBytes() ;
}

//-------------------------------------------------------------------------------------------------------------
UINT8 CommsEmuMsg::getType() const
{
	return mPdu.getTypeByte() ;
}

//-------------------------------------------------------------------------------------------------------------
FpgaPdu CommsEmuMsg::getPdu() const
{
	return mPdu ;
}

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg CommsEmuMsg::createCommand(const std::vector<UINT8>& data)
{
	return CommsEmuMsg(FpgaPdu::PDU_TYPE_CMD, data) ;
}

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg CommsEmuMsg::createResponse(const std::vector<UINT8>& data)
{
	return CommsEmuMsg(FpgaPdu::PDU_TYPE_REPLY, data) ;
}

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg CommsEmuMsg::createEvent(const std::vector<UINT8>& data)
{
	return CommsEmuMsg(FpgaPdu::PDU_TYPE_EVENT, data) ;
}

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg CommsEmuMsg::createLog(const std::string& msg)
{
	return CommsEmuMsg(FpgaPdu::PDU_TYPE_LOG, msg) ;
}

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg CommsEmuMsg::createMatlab(const std::string& msg)
{
	return CommsEmuMsg(FpgaPdu::PDU_TYPE_MATLAB, msg) ;
}

//-------------------------------------------------------------------------------------------------------------
CommsEmuMsg CommsEmuMsg::createText(const std::string& msg)
{
	return CommsEmuMsg(FpgaPdu::PDU_TYPE_TEXT, msg) ;
}

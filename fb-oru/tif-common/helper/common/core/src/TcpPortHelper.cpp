/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TcpPortHelper.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cstdarg>

#include "RtiKeyword.h"
#include "TcpPortHelper.h"

using namespace Mplane;

//=============================================================================================================
// PROTOTYPES
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static unsigned getPort(IRtiMsgParser& msgParser, const std::string& portVarName,
		DataVariantList* callList, DataVariantList* returnList) ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TcpPortHelper::TcpPortHelper(IRtiMsgParser& msgParser,
		const std::string& portVarName, DataVariantList* callList) :
	mMsgParser(msgParser),
	mPort( getPort(mMsgParser, portVarName, callList, NULL) )
{
}

//-------------------------------------------------------------------------------------------------------------
TcpPortHelper::~TcpPortHelper()
{
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortHelper::send(const std::string& msg)
{
	mMsgParser.tcpPortSend(mPort, msg) ;
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortHelper::send(const std::vector<uint8_t>& msg)
{
	mMsgParser.tcpPortSend(mPort, msg) ;
}

//-------------------------------------------------------------------------------------------------------------
void TcpPortHelper::send(const char* fmt, ... )
{
	va_list args;
	va_start (args, fmt);

	char buffer[1024];
	vsnprintf (buffer, sizeof(buffer), fmt, args);
	va_end (args);

	mMsgParser.tcpPortSend(mPort, buffer) ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortHelper::receive(std::vector<uint8_t>& data, unsigned expectedSize, unsigned timeoutSecs)
{
	return mMsgParser.tcpPortReceive(mPort, data, expectedSize, timeoutSecs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool TcpPortHelper::receive(ITcpPortIoTypes::ReceiveCallback callback, unsigned expectedSize, unsigned timeoutSecs)
{
	return mMsgParser.tcpPortReceive(mPort, callback, expectedSize, timeoutSecs) ;
}

//=============================================================================================================
// STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool TcpPortHelper::portValid(IRtiMsgParser& msgParser, const std::string& portVarName,
		DataVariantList* callList, DataVariantList* returnList)
{
	return getPort(msgParser, portVarName, callList, returnList) != 0 ;
}

//=============================================================================================================
// LOCAL STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
static unsigned getPort(IRtiMsgParser& msgParser, const std::string& portVarName,
		DataVariantList* callList, DataVariantList* returnList)
{
	unsigned port( static_cast<unsigned>(callList->find(portVarName)->toInt()) ) ;
	if ( (port < 1024) || (port > 65535) )
	{
		if (!returnList)
			return 0 ;

		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Port number must be between 1024..65535") ;
		return 0 ;
	}

	// Error if port is not open yet
	if (!msgParser.tcpIsPortOpen(port))
	{
		if (!returnList)
			return 0 ;

		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("TCP port has not been opened yet (use tcp command)") ;
		return 0 ;
	}

	return port ;
}

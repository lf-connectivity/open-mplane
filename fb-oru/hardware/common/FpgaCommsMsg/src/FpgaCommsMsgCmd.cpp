/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsgCmd.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FpgaCommsMsgCmd.h"

using namespace Mplane;



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgCmd::FpgaCommsMsgCmd(std::shared_ptr<IFpgaMsgTokens> tokens, std::shared_ptr<IFpgaPdu> pdu) :
	FpgaCommsMsgBase(tokens, pdu)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgCmd::FpgaCommsMsgCmd(std::shared_ptr<IFpgaMsgTokens> tokens, const IFpgaPdu& pdu) :
	FpgaCommsMsgBase(tokens, pdu)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgCmd::FpgaCommsMsgCmd(std::shared_ptr<IFpgaMsgTokens> tokens,
		const std::string& cmd,
		const std::vector<DataVariant>& attributes,
		const std::set<std::string>& varNames) :
	FpgaCommsMsgBase(tokens, cmd, attributes, varNames)
{
}


//-------------------------------------------------------------------------------------------------------------
FpgaCommsMsgCmd::~FpgaCommsMsgCmd()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string FpgaCommsMsgCmd::toString() const
{
	std::shared_ptr<IFpgaPdu> pdu(getPdu()) ;

	// Need to convert tokens
	std::shared_ptr<IFpgaMsgTokens> msgTokens(getMsgTokens()) ;

	std::string pduData(getPduData()) ;
	unsigned dataPos{0} ;

	// cmd
	unsigned short cmdCode ;
	if (!readShort(pduData, dataPos, cmdCode))
		// just use the PDU data
		return pduData ;

	// convert command into a string
	std::string cmd(msgTokens->getCmdTokenStr(cmdCode)) ;

	// convert the rest of the data into a string
	std::string str(toTokenString(pduData, dataPos)) ;

	return cmd + " " + str ;
}

//-------------------------------------------------------------------------------------------------------------
std::map<std::string, DataVariant> FpgaCommsMsgCmd::getAttributes() const
{
	std::string pduData(getPduData()) ;
	unsigned dataPos{0} ;

	// remove command
	unsigned short cmdCode ;
	if (!readShort(pduData, dataPos, cmdCode))
		return std::map<std::string, DataVariant>() ;

	return getTokenAttributes(pduData, dataPos) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------

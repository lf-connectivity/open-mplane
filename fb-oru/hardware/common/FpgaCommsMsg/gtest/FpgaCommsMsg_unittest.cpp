/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaCommsMsg_unittest.cpp
 * \brief     Google Test of FpgaCommsMsg
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaCommsMsg class.
 *
 */

#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <memory>

#include "Tokeniser.h"
#include "test_fixture.h"

#include "FpgaPdu.h"

// use to get the PIM view of the token numbers
#include "IFpgaCommsConstants.h"
#include "test_tok.h"

#include "TestTokens.h"
#include "FpgaCommsMsgFactory.h"
#include "IFpgaMsg.h"
#include "FpgaCommsMsgMonitor.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class FpgaCommsMsgTest : public TestFixture
{
public:

	/**
	 * Create a message of the specified type using the specified tokens and the string of arguments formatted as if to
	 * build a DataVariantList
	 * @param type
	 * @param tokens
	 * @param args
	 * @return message
	 */
	std::shared_ptr<IFpgaMsg> createMsg(IFpgaPdu::PduDataType type, std::shared_ptr<IFpgaMsgTokens> tokens, const std::string& args)
	{
		// create a dummy command message using the tokens and args
		DataVariantList dvl(args.c_str()) ;
		std::shared_ptr<IFpgaMsg> cmdMsg( FpgaCommsMsgFactory::factory(tokens, "set", dvl.getList()) ) ;

		// get the message PDU bytes and drop the command word (first 2 bytes)
		std::vector<UINT8> bytes(cmdMsg->getPdu()->getDataBytes()) ;
		std::vector<UINT8> bytesData(bytes.begin()+2, bytes.end()) ;

		// create a PDU of the specified type using the bytes
		FpgaPdu pdu(type, bytesData) ;

		// Now create the messsage
		std::shared_ptr<IFpgaMsg> msg(FpgaCommsMsgFactory::factory(tokens, pdu)) ;

		return msg ;
	}

	void pimGainMonitor(std::map<std::string, DataVariant> attributes)
	{
		++mPimGainCount ;
		mPimGain = 0 ;

		auto entry(attributes.find("pimGain")) ;
		if (entry == attributes.end())
			return ;

		mPimGain = attributes["pimGain"].toInt() ;
	}

public:
	int mPimGain=-1 ;
	unsigned mPimGainCount=0;

};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, CmdToMsg)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	// Should fail
//	bool ok(true) ;
//	try {
	DataVariantList dvl2("INT dummy1=0") ;
	std::shared_ptr<IFpgaMsg> msg1(
		FpgaCommsMsgFactory::factory(testTokens, "apiVersion", dvl2.getList())
	) ;
//	} catch (...) {
//		ok = false ;
//	}
	EXPECT_TRUE(msg1->isError()) ;
	EXPECT_EQ(std::string("Invalid attribute: dummy1"), msg1->errorReason()) ;
	std::cerr << "EXPECTED: " << msg1->errorReason() << std::endl ;
//	EXPECT_FALSE(ok) ;

	DataVariantList dvl("INT stimRe=1,INT stimIm=288,INT pimGain=13398,INT period=1,INT branches=1") ;
	std::shared_ptr<IFpgaMsg> msg2( FpgaCommsMsgFactory::factory(testTokens, "set", dvl.getList()) ) ;

	EXPECT_FALSE(msg2->isError()) ;
	EXPECT_EQ(std::string(""), msg2->errorReason()) ;
	std::shared_ptr<IFpgaPdu> pdu2(msg2->getPdu()) ;
	std::string pdu2Str(pdu2->toString()) ;
	std::cerr << "PDU2: " << pdu2Str << std::endl ;

//	EXPECT_EQ(CMD_set, pdu2Tokens.cmd) ;
//	EXPECT_EQ(0u, pdu2Tokens.vars.size()) ;
//	EXPECT_NE(0u, pdu2Tokens.attributes.size()) ;
//
//	EXPECT_EQ(1, pdu2Tokens.attributes[STATEVAR_stimRe]) ;
//	EXPECT_EQ(288, pdu2Tokens.attributes[STATEVAR_stimIm]) ;
//	EXPECT_EQ(13398, pdu2Tokens.attributes[STATEVAR_pimGain]) ;
//	EXPECT_EQ(1, pdu2Tokens.attributes[STATEVAR_period]) ;
//	EXPECT_EQ(1, pdu2Tokens.attributes[STATEVAR_branches]) ;

	std::string msg2Str(msg2->toString()) ;
	std::cerr << "MSG2: " << msg2Str << std::endl ;
	EXPECT_TRUE(msg2Str.find("set ") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("branches=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("period=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("pimGain=13398") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimIm=288") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimRe=1") != std::string::npos) ;

	//  get channel=1 channel pimStatus
	std::shared_ptr<IFpgaMsg> msg3( FpgaCommsMsgFactory::factory(testTokens, "get", std::vector<DataVariant>(),
		std::set<std::string>{
			"stimRe", "stimIm"
		}
	) ) ;
	EXPECT_FALSE(msg3->isError()) ;
	EXPECT_EQ(std::string(""), msg3->errorReason()) ;
	std::shared_ptr<IFpgaPdu> pdu3(msg3->getPdu()) ;
	std::string pdu3Str(pdu3->getData()) ;
//	std::cerr << "PDU3: " << pdu3Str << std::endl ;
//	PduTokens pdu3Tokens( splitPduStr(pdu3Str) ) ;
//
//	EXPECT_EQ(CMD_get, pdu3Tokens.cmd) ;
//	EXPECT_EQ(2u, pdu3Tokens.vars.size()) ;
//	EXPECT_NE(0u, pdu3Tokens.attributes.size()) ;

	// MsgId
//	EXPECT_EQ(1, pdu3Tokens.attributes.size()) ;
//
//	EXPECT_TRUE(pdu3Tokens.vars.find(STATEVAR_stimRe) != pdu3Tokens.vars.end()) ;
//	EXPECT_TRUE(pdu3Tokens.vars.find(STATEVAR_stimIm) != pdu3Tokens.vars.end()) ;

	std::string msg3Str(msg3->toString()) ;
	std::cerr << "MSG3: " << msg3Str << std::endl ;
	EXPECT_TRUE(msg3Str.find("get ") != std::string::npos) ;
	EXPECT_TRUE(msg3Str.find("stimIm=0 stimRe=0") != std::string::npos) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, PduToMsg)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	DataVariantList dvl("INT stimRe=1,INT stimIm=288,INT pimGain=13398,INT period=1,INT branches=1") ;
	std::shared_ptr<IFpgaMsg> msg2a( FpgaCommsMsgFactory::factory(testTokens, "set", dvl.getList()) ) ;

	// Use this created PDU to build a new FpgaCommsMsg
	std::shared_ptr<IFpgaMsg> msg2( FpgaCommsMsgFactory::factory(testTokens, msg2a->getPdu()) ) ;

	EXPECT_FALSE(msg2->isError()) ;
	EXPECT_EQ(std::string(""), msg2->errorReason()) ;
	std::shared_ptr<IFpgaPdu> pdu2(msg2->getPdu()) ;
//	std::string pdu2Str(pdu2->getData()) ;
//	std::cerr << "PDU2: " << pdu2Str << std::endl ;
//	PduTokens pdu2Tokens( splitPduStr(pdu2Str) ) ;
//
//	EXPECT_EQ(CMD_set, pdu2Tokens.cmd) ;
//	EXPECT_EQ(0u, pdu2Tokens.vars.size()) ;
//	EXPECT_NE(0u, pdu2Tokens.attributes.size()) ;
//
//	EXPECT_EQ(1, pdu2Tokens.attributes[STATEVAR_stimRe]) ;
//	EXPECT_EQ(288, pdu2Tokens.attributes[STATEVAR_stimIm]) ;
//	EXPECT_EQ(13398, pdu2Tokens.attributes[STATEVAR_pimGain]) ;
//	EXPECT_EQ(1, pdu2Tokens.attributes[STATEVAR_period]) ;
//	EXPECT_EQ(1, pdu2Tokens.attributes[STATEVAR_branches]) ;

	std::string msg2aStr(msg2a->toString()) ;
	std::cerr << "MSG2a: " << msg2aStr << std::endl ;

	std::string msg2Str(msg2->toString()) ;
	std::cerr << "MSG2: " << msg2Str << std::endl ;
	EXPECT_TRUE(msg2Str.find("set ") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("branches=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("period=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("pimGain=13398") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimIm=288") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimRe=1") != std::string::npos) ;

	// Copy should be identical (including msgId)
	EXPECT_EQ(msg2aStr, msg2Str) ;



	//  get channel=1 channel pimStatus
	std::shared_ptr<IFpgaMsg> msg3a( FpgaCommsMsgFactory::factory(testTokens, "get", std::vector<DataVariant>(),
		std::set<std::string>{
			"stimRe", "stimIm"
		}
	)) ;

	// Use this created PDU to build a new FpgaCommsMsg
	std::shared_ptr<IFpgaMsg> msg3( FpgaCommsMsgFactory::factory(testTokens, msg3a->getPdu()) ) ;


	EXPECT_FALSE(msg3->isError()) ;
	EXPECT_EQ(std::string(""), msg3->errorReason()) ;
//	std::shared_ptr<IFpgaPdu> pdu3(msg3->getPdu()) ;
//	std::string pdu3Str(pdu3->getData()) ;
//	std::cerr << "PDU3: " << pdu3Str << std::endl ;
//	PduTokens pdu3Tokens( splitPduStr(pdu3Str) ) ;
//
//	EXPECT_EQ(CMD_get, pdu3Tokens.cmd) ;
//	EXPECT_EQ(2u, pdu3Tokens.vars.size()) ;
//	EXPECT_NE(0u, pdu3Tokens.attributes.size()) ;
//
//	// MsgId
//	EXPECT_EQ(1, pdu3Tokens.attributes.size()) ;
//
//	EXPECT_TRUE(pdu3Tokens.vars.find(STATEVAR_stimRe) != pdu3Tokens.vars.end()) ;
//	EXPECT_TRUE(pdu3Tokens.vars.find(STATEVAR_stimIm) != pdu3Tokens.vars.end()) ;

	std::string msg3aStr(msg3a->toString()) ;
	std::cerr << "MSG3a: " << msg3aStr << std::endl ;

	std::string msg3Str(msg3->toString()) ;
	std::cerr << "MSG3: " << msg3Str << std::endl ;
	EXPECT_TRUE(msg3Str.find("get ") != std::string::npos) ;
	EXPECT_TRUE(msg3Str.find("stimIm=0") != std::string::npos) ;
	EXPECT_TRUE(msg3Str.find("stimRe=0") != std::string::npos) ;

	// Copy should be identical (including msgId)
	EXPECT_EQ(msg3aStr, msg3Str) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, Factory)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	DataVariantList dvl("INT stimRe=1,INT stimIm=288,INT pimGain=13398,INT period=1,INT branches=1") ;
	std::shared_ptr<IFpgaMsg> msg2a( FpgaCommsMsgFactory::factory(testTokens, "set", dvl.getList()) ) ;

	// Use this created PDU to build a new FpgaCommsMsg
	std::shared_ptr<IFpgaMsg> msg2( FpgaCommsMsgFactory::factory(testTokens, msg2a->getPdu()) ) ;

	EXPECT_FALSE(msg2->isError()) ;
	EXPECT_EQ(std::string(""), msg2->errorReason()) ;
//	std::shared_ptr<IFpgaPdu> pdu2(msg2->getPdu()) ;
//	std::string pdu2Str(pdu2->getData()) ;
//	std::cerr << "PDU2: " << pdu2Str << std::endl ;
//	PduTokens pdu2Tokens( splitPduStr(pdu2Str) ) ;
//
//	EXPECT_EQ(CMD_set, pdu2Tokens.cmd) ;
//	EXPECT_EQ(0u, pdu2Tokens.vars.size()) ;
//	EXPECT_NE(0u, pdu2Tokens.attributes.size()) ;
//
//	EXPECT_EQ(1, pdu2Tokens.attributes[STATEVAR_stimRe]) ;
//	EXPECT_EQ(288, pdu2Tokens.attributes[STATEVAR_stimIm]) ;
//	EXPECT_EQ(13398, pdu2Tokens.attributes[STATEVAR_pimGain]) ;
//	EXPECT_EQ(1, pdu2Tokens.attributes[STATEVAR_period]) ;
//	EXPECT_EQ(1, pdu2Tokens.attributes[STATEVAR_branches]) ;

	std::string msg2aStr(msg2a->toString()) ;
	std::cerr << "MSG2a: " << msg2aStr << std::endl ;

	std::string msg2Str(msg2->toString()) ;
	std::cerr << "MSG2: " << msg2Str << std::endl ;
	EXPECT_TRUE(msg2Str.find("set ") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("branches=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("period=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("pimGain=13398") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimIm=288") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimRe=1") != std::string::npos) ;

	// Copy should be identical (including msgId)
	EXPECT_EQ(msg2aStr, msg2Str) ;

	//-------------------------------------------------------------------------------------
	// factory(std::shared_ptr<IFpgaPdu> pdu)
	std::shared_ptr<IFpgaMsg> msg3a( FpgaCommsMsgFactory::factory(testTokens, msg2a->getPdu()) ) ;

	EXPECT_FALSE(msg3a->isError()) ;
	EXPECT_EQ(std::string(""), msg3a->errorReason()) ;
//	std::shared_ptr<IFpgaPdu> pdu3a(msg3a->getPdu()) ;
//	std::string pdu3aStr(pdu3a->getData()) ;
//	std::cerr << "PDU2: " << pdu3aStr << std::endl ;
//	PduTokens pdu3aTokens( splitPduStr(pdu3aStr) ) ;
//
//	EXPECT_EQ(CMD_set, pdu3aTokens.cmd) ;
//	EXPECT_EQ(0u, pdu3aTokens.vars.size()) ;
//	EXPECT_NE(0u, pdu3aTokens.attributes.size()) ;
//
//	EXPECT_EQ(1, pdu3aTokens.attributes[STATEVAR_stimRe]) ;
//	EXPECT_EQ(288, pdu3aTokens.attributes[STATEVAR_stimIm]) ;
//	EXPECT_EQ(13398, pdu3aTokens.attributes[STATEVAR_pimGain]) ;
//	EXPECT_EQ(1, pdu3aTokens.attributes[STATEVAR_period]) ;
//	EXPECT_EQ(1, pdu3aTokens.attributes[STATEVAR_branches]) ;

	std::string msg3aStr(msg3a->toString()) ;
	std::cerr << "MSG3a: " << msg3aStr << std::endl ;
	EXPECT_TRUE(msg3aStr.find("set ") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("branches=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("period=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("pimGain=13398") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimIm=288") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimRe=1") != std::string::npos) ;

	// Copy should be identical (including msgId)
	EXPECT_EQ(msg3aStr, msg2Str) ;


	//-------------------------------------------------------------------------------------
	// factory(const IFpgaPdu& pdu)
	std::shared_ptr<IFpgaMsg> msg4a( FpgaCommsMsgFactory::factory( testTokens, *(msg2a->getPdu()) ) ) ;

	EXPECT_FALSE(msg4a->isError()) ;
	EXPECT_EQ(std::string(""), msg4a->errorReason()) ;
//	std::shared_ptr<IFpgaPdu> pdu4a(msg4a->getPdu()) ;
//	std::string pdu4aStr(pdu4a->getData()) ;
//	std::cerr << "PDU2: " << pdu4aStr << std::endl ;
//	PduTokens pdu4aTokens( splitPduStr(pdu4aStr) ) ;
//
//	EXPECT_EQ(CMD_set, pdu4aTokens.cmd) ;
//	EXPECT_EQ(0u, pdu4aTokens.vars.size()) ;
//	EXPECT_NE(0u, pdu4aTokens.attributes.size()) ;
//
//	EXPECT_EQ(1, pdu4aTokens.attributes[STATEVAR_stimRe]) ;
//	EXPECT_EQ(288, pdu4aTokens.attributes[STATEVAR_stimIm]) ;
//	EXPECT_EQ(13398, pdu4aTokens.attributes[STATEVAR_pimGain]) ;
//	EXPECT_EQ(1, pdu4aTokens.attributes[STATEVAR_period]) ;
//	EXPECT_EQ(1, pdu4aTokens.attributes[STATEVAR_branches]) ;

	std::string msg4aStr(msg4a->toString()) ;
	std::cerr << "MSG4a: " << msg4aStr << std::endl ;
	EXPECT_TRUE(msg4aStr.find("set ") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("branches=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("period=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("pimGain=13398") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimIm=288") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimRe=1") != std::string::npos) ;

	// Copy should be identical (including msgId)
	EXPECT_EQ(msg4aStr, msg2Str) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, ToString)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	DataVariantList dvl("INT stimRe=1,INT stimIm=288,INT pimGain=13398,INT period=1,INT branches=1") ;
	std::shared_ptr<IFpgaMsg> msg2a( FpgaCommsMsgFactory::factory(testTokens, "set", dvl.getList()) ) ;

	// Use this created PDU to build a new FpgaCommsMsg
	std::vector<UINT8> bytes2a(msg2a->getPdu()->getDataBytes()) ;	// drop command word
	std::vector<UINT8> bytes2aData(bytes2a.begin()+2, bytes2a.end()) ;
	FpgaPdu pdu2a(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, bytes2aData) ;
	std::shared_ptr<IFpgaMsg> msg2(FpgaCommsMsgFactory::factory(testTokens, pdu2a)) ;

	EXPECT_FALSE(msg2->isError()) ;
	EXPECT_EQ(std::string(""), msg2->errorReason()) ;

//	std::shared_ptr<IFpgaPdu> pdu2(msg2->getPdu()) ;
//	std::string pdu2Str(pdu2->getData()) ;
	std::string msg2Str(msg2->toString()) ;
	std::cerr << "MSG2: " << msg2Str << std::endl ;

	EXPECT_TRUE(msg2Str.find("set ") == std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("branches=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("period=1") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("pimGain=13398") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimIm=288") != std::string::npos) ;
	EXPECT_TRUE(msg2Str.find("stimRe=1") != std::string::npos) ;

	std::map<std::string, std::string> tokens ;
	tokens["get"] = std::to_string(testTokens->getCmdToken("get")) ;
	tokens["dFOM"] = std::to_string(testTokens->getStateToken("dFOM")) ;
	tokens["logTrace"] = std::to_string(testTokens->getStateToken("logTrace")) ;
	tokens["response"] = std::to_string(testTokens->getStateToken("response")) ;
	tokens["logConsole"] = std::to_string(testTokens->getStateToken("logConsole")) ;
	tokens["ulBbDst"] = std::to_string(testTokens->getStateToken("ulBbDst")) ;
	tokens["uptime"] = std::to_string(testTokens->getStateToken("uptime")) ;

	tokens["YES"] = std::to_string(testTokens->getToken("YES")) ;
	tokens["ACK"] = std::to_string(testTokens->getToken("ACK")) ;

#if 0
	FpgaPdu pduA(IFpgaPdu::PduDataType::PDU_TYPE_REPLY,
			tokens["uptime"] + "=123 " +
			tokens["dFOM"] + "=1 " +
			tokens["logTrace"] + "=" + tokens["YES"]) ;
	std::shared_ptr<IFpgaMsg> msgA( FpgaCommsMsgFactory::factory(testTokens, pduA) ) ;
	std::string msgAStr(msgA->toString()) ;
	std::cerr << "MSGA: " << msgAStr << std::endl ;
	EXPECT_EQ("uptime=123 dFOM=1 logTrace=YES", msgAStr) ;

	FpgaPdu pduB(IFpgaPdu::PduDataType::PDU_TYPE_REPLY,
			tokens["uptime"] + "=123 " +
			tokens["dFOM"] + "=2 " +
			tokens["uptime"] + "=10 " +
			tokens["response"] + "=" + tokens["ACK"]) ;
	std::shared_ptr<IFpgaMsg> msgB( FpgaCommsMsgFactory::factory(testTokens, pduB) ) ;
	std::string msgBStr(msgB->toString()) ;
	std::cerr << "MSGB: " << msgBStr << std::endl ;
	EXPECT_EQ("uptime=123 dFOM=2 uptime=10 response=ACK", msgBStr) ;

	FpgaPdu pduC(IFpgaPdu::PduDataType::PDU_TYPE_REPLY,
			tokens["uptime"] + "=345 " +
			tokens["dFOM"] + "=2 " +
			tokens["logConsole"] + "=" + tokens["YES"]+ " " +
			tokens["ulBbDst"] + "=288") ;
	std::shared_ptr<IFpgaMsg> msgC( FpgaCommsMsgFactory::factory(testTokens, pduC) ) ;
	std::string msgCStr(msgC->toString()) ;
	std::cerr << "MSGC: " << msgCStr << std::endl ;
	EXPECT_EQ("uptime=345 dFOM=2 logConsole=YES ulBbDst=288", msgCStr) ;
#endif


	FpgaPdu pduD(IFpgaPdu::PduDataType::PDU_TYPE_MATLAB, "10 28=1 6=101") ;
	std::shared_ptr<IFpgaMsg> msgD( FpgaCommsMsgFactory::factory(testTokens, pduD) ) ;
	std::string msgDStr(msgD->toString()) ;
	std::cerr << "MSGD: " << msgDStr << std::endl ;
	EXPECT_EQ("10 28=1 6=101", msgDStr) ;

	FpgaPdu pduE(IFpgaPdu::PduDataType::PDU_TYPE_TEXT, "10 28=2 10=10 0=108") ;
	std::shared_ptr<IFpgaMsg> msgE( FpgaCommsMsgFactory::factory(testTokens, pduE) ) ;
	std::string msgEStr(msgE->toString()) ;
	std::cerr << "MSGE: " << msgEStr << std::endl ;
	EXPECT_EQ("10 28=2 10=10 0=108", msgEStr) ;

	FpgaPdu pduF(IFpgaPdu::PduDataType::PDU_TYPE_LOG, "10 28=2 10=10 0=108") ;
	std::shared_ptr<IFpgaMsg> msgF( FpgaCommsMsgFactory::factory(testTokens, pduF) ) ;
	std::string msgFStr(msgF->toString()) ;
	std::cerr << "MSGF: " << msgFStr << std::endl ;
	EXPECT_EQ("10 28=2 10=10 0=108", msgFStr) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, Ack)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	DataVariantList dvl("INT stimRe=1,INT stimIm=288,INT pimGain=13398,INT period=1,INT branches=1") ;
	std::shared_ptr<IFpgaMsg> msg1( FpgaCommsMsgFactory::factory(testTokens, "set", dvl.getList()) ) ;

	// commands default to ack set
	EXPECT_TRUE(msg1->getAck()) ;

	std::shared_ptr<IFpgaMsg> msg2a( FpgaCommsMsgFactory::factory(testTokens, "set", dvl.getList()) ) ;
	std::vector<UINT8> bytes2a(msg2a->getPdu()->getDataBytes()) ;	// drop command word
	std::vector<UINT8> bytes2aData(bytes2a.begin()+2, bytes2a.end()) ;
	FpgaPdu pdu2a(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, bytes2aData) ;
	std::shared_ptr<IFpgaMsg> msg2b(FpgaCommsMsgFactory::factory(testTokens, pdu2a)) ;

	// reply with no response, defaults to NACK
	EXPECT_FALSE(msg2b->getAck()) ;


	DataVariantList dvl3a("INT stimRe=1,INT stimIm=288,INT pimGain=13398,INT period=1,INT branches=1,ENUM(NACK:ACK) response=ACK") ;
	std::shared_ptr<IFpgaMsg> msg3a( FpgaCommsMsgFactory::factory(testTokens, "set", dvl3a.getList()) ) ;

	std::vector<UINT8> bytes3a(msg3a->getPdu()->getDataBytes()) ;	// drop command word
//std::cout << "MSG3a bytes:" << std::endl ;
//for (auto byte : bytes3a)
//{
//	printf("  0x%02x (%u)\n", byte, byte) ;
//}

	std::vector<UINT8> bytes3aData(bytes3a.begin()+2, bytes3a.end()) ;
	FpgaPdu pdu3a(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, bytes3aData) ;
	std::shared_ptr<IFpgaMsg> msg3b(FpgaCommsMsgFactory::factory(testTokens, pdu3a)) ;
	EXPECT_TRUE(msg3b->getAck()) ;
std::cerr << "MSG3b '" << msg3b->toString() << "'" << std::endl ;

	DataVariantList dvl4a("INT stimRe=1,INT stimIm=288,INT pimGain=13398,INT period=1,INT branches=1,ENUM(NACK:ACK) response=NACK") ;
	std::shared_ptr<IFpgaMsg> msg4a( FpgaCommsMsgFactory::factory(testTokens, "set", dvl4a.getList()) ) ;
std::cerr << "MSG4a '" << msg4a->toString() << "'" << std::endl ;

	std::vector<UINT8> bytes4a(msg4a->getPdu()->getDataBytes()) ;	// drop command word
	std::vector<UINT8> bytes4aData(bytes4a.begin()+2, bytes4a.end()) ;
	FpgaPdu pdu4a(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, bytes4aData) ;
	std::shared_ptr<IFpgaMsg> msg4b(FpgaCommsMsgFactory::factory(testTokens, pdu4a)) ;
	EXPECT_FALSE(msg4b->getAck()) ;
std::cerr << "MSG4b '" << msg4b->toString() << "'" << std::endl ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, Monitor)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	std::shared_ptr<IFpgaMsg> msg1 = createMsg(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, testTokens,
			"INT stimRe=1,INT stimIm=288,INT pimGain=13398,INT period=1,INT branches=1") ;

	std::shared_ptr<IFpgaMsg> msg2 = createMsg(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, testTokens,
			"INT stimRe=1,INT stimIm=288,INT pimGain=222,INT period=1,INT branches=1") ;

	std::shared_ptr<IFpgaMsg> msg3 = createMsg(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, testTokens,
			"INT stimRe=1,INT stimIm=288,INT period=1,INT branches=1") ;

	// Create a monitor
	std::shared_ptr<FpgaCommsMsgMonitor> msgMonitor = std::make_shared<FpgaCommsMsgMonitor>(
			"pimGain", [this](std::map<std::string, DataVariant> attributes){pimGainMonitor(attributes);}
	) ;

	mPimGain=-1 ;
	mPimGainCount=0 ;

	msgMonitor->handleMsg(msg1) ;
	Task::msSleep(200) ; // allow task time to process
	EXPECT_EQ(13398, mPimGain) ;
	EXPECT_EQ(1u, mPimGainCount) ;

	msgMonitor->handleMsg(msg2) ;
	Task::msSleep(200) ; // allow task time to process
	EXPECT_EQ(222, mPimGain) ;
	EXPECT_EQ(2u, mPimGainCount) ;

	// shouldn't get called here
	msgMonitor->handleMsg(msg3) ;
	Task::msSleep(200) ; // allow task time to process
	EXPECT_EQ(222, mPimGain) ;
	EXPECT_EQ(2u, mPimGainCount) ;

	msgMonitor->handleMsg(msg1) ;
	Task::msSleep(200) ; // allow task time to process
	EXPECT_EQ(13398, mPimGain) ;
	EXPECT_EQ(3u, mPimGainCount) ;

	Task::msSleep(200) ;
}


#ifdef TODO

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, FromPDU_CMD)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	std::stringstream data ;

	std::shared_ptr<IFpgaMsg> msg1( FpgaCommsMsgFactory::factory(testTokens, "set", std::map<std::string, DataVariant>{
		{"stimRe", 1},
		{"stimIm", 288},
		{"pimGain", 13398},
	}) ) ;
	std::shared_ptr<IFpgaMsg> msg( FpgaCommsMsgFactory::factory(testTokens, msg1->getPdu()) ) ;

	std::shared_ptr<IFpgaPdu> pdu2( new FpgaPdu(msg1->getPdu()) ) ;
	std::shared_ptr<IFpgaMsg> msg2( FpgaCommsMsgFactory::factory(testTokens, pdu2) ) ;

//	std::cout << "PDU: '" << pdu.getData() << "'" << std::endl ;
//	std::cout << "PDU2: '" << pdu2->getData() << "'" << std::endl ;

	std::cout << "MSG: '" << msg->toString() << "'" << std::endl ;
	std::cout << "MSG2: '" << msg2->toString() << "'" << std::endl ;

	EXPECT_EQ(IFpgaPdu::PduDataType::PDU_TYPE_CMD, msg->getPdu()->getType()) ;
	EXPECT_EQ(IFpgaPdu::PduDataType::PDU_TYPE_CMD, msg2->getPdu()->getType()) ;

	EXPECT_TRUE(msg->toString().find("pimGain=13398 stimIm=288 stimRe=1") != std::string::npos) ;
	EXPECT_TRUE(msg2->toString().find("pimGain=13398 stimIm=288 stimRe=1") != std::string::npos) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, FromPDU_REPLY)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	std::stringstream data ;

	std::shared_ptr<IFpgaMsg> msg3a( FpgaCommsMsgFactory::factory(testTokens, "set", std::map<std::string, DataVariant>{
		{"stimRe", 1},
		{"stimIm", 288},
		{"pimGain", 13398},
		{"response", testTokens->getToken("ACK")}
	}) ) ;
	std::vector<UINT8> bytes3a(msg3a->getPdu()->getDataBytes()) ;	// drop command word
	std::vector<UINT8> bytes3aData(bytes3a.begin()+2, bytes3a.end()) ;
	FpgaPdu pdu3a(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, bytes3aData) ;
	std::shared_ptr<IFpgaMsg> msg(FpgaCommsMsgFactory::factory(testTokens, pdu3a)) ;

	std::shared_ptr<IFpgaPdu> pdu2( new FpgaPdu(msg->getPdu()) ) ;
	std::shared_ptr<IFpgaMsg> msg2( FpgaCommsMsgFactory::factory(testTokens, pdu2) ) ;

	std::cout << "MSG: '" << msg->toString() << "'" << std::endl ;
	std::cout << "MSG2: '" << msg2->toString() << "'" << std::endl ;

	EXPECT_TRUE(msg->toString().find("pimGain=13398 response=ACK stimIm=288 stimRe=1") != std::string::npos) ;
	EXPECT_TRUE(msg2->toString().find("pimGain=13398 response=ACK stimIm=288 stimRe=1") != std::string::npos) ;

	EXPECT_EQ(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, msg->getPdu()->getType()) ;
	EXPECT_EQ(IFpgaPdu::PduDataType::PDU_TYPE_REPLY, msg2->getPdu()->getType()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, FromPDU_EVENT)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	std::stringstream data ;

	std::shared_ptr<IFpgaMsg> msg3a( FpgaCommsMsgFactory::factory(testTokens, "set", std::map<std::string, DataVariant>{
		{"stimRe", 1},
		{"stimIm", 288},
		{"pimGain", 13398},
		{"response", testTokens->getToken("ACK")}
	}) ) ;
	std::vector<UINT8> bytes3a(msg3a->getPdu()->getDataBytes()) ;	// drop command word
	std::vector<UINT8> bytes3aData(bytes3a.begin()+2, bytes3a.end()) ;
	FpgaPdu pdu3a(IFpgaPdu::PduDataType::PDU_TYPE_EVENT, bytes3aData) ;
	std::shared_ptr<IFpgaMsg> msg(FpgaCommsMsgFactory::factory(testTokens, pdu3a)) ;

	std::shared_ptr<IFpgaPdu> pdu2( new FpgaPdu(msg->getPdu()) ) ;
	std::shared_ptr<IFpgaMsg> msg2( FpgaCommsMsgFactory::factory(testTokens, pdu2) ) ;

	std::cout << "MSG: '" << msg->toString() << "'" << std::endl ;
	std::cout << "MSG2: '" << msg2->toString() << "'" << std::endl ;

	EXPECT_TRUE(msg->toString().find("pimGain=13398 response=ACK stimIm=288 stimRe=1") != std::string::npos) ;
	EXPECT_TRUE(msg2->toString().find("pimGain=13398 response=ACK stimIm=288 stimRe=1") != std::string::npos) ;

	EXPECT_EQ(IFpgaPdu::PduDataType::PDU_TYPE_EVENT, msg->getPdu()->getType()) ;
	EXPECT_EQ(IFpgaPdu::PduDataType::PDU_TYPE_EVENT, msg2->getPdu()->getType()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, FromPDU_MATLAB)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	std::stringstream data ;

	data.str("") ;
    data <<
    	testTokens->getStateToken("response") << "=" << testTokens->getToken("ACK") << " " <<
    	testTokens->getStateToken("stimRe") << "=" << std::to_string(1) << " " <<
    	testTokens->getStateToken("stimIm") << "=" << std::to_string(288) << " " <<
    	testTokens->getStateToken("pimGain") << "=" << std::to_string(13398) ;
	FpgaPdu pdu(IFpgaPdu::PDU_TYPE_MATLAB, data.str()) ;
	std::shared_ptr<IFpgaMsg> msg( FpgaCommsMsgFactory::factory(testTokens, pdu) ) ;

	std::shared_ptr<IFpgaPdu> pdu2( new FpgaPdu(pdu) ) ;
	std::shared_ptr<IFpgaMsg> msg2( FpgaCommsMsgFactory::factory(testTokens, pdu2) ) ;

	std::cout << "PDU: '" << pdu.getData() << "'" << std::endl ;
	std::cout << "PDU2: '" << pdu2->getData() << "'" << std::endl ;

	std::cout << "MSG: '" << msg->toString() << "'" << std::endl ;
	std::cout << "MSG2: '" << msg2->toString() << "'" << std::endl ;

	EXPECT_EQ("100=208 129=1 130=288 131=13398", msg->toString()) ;
	EXPECT_EQ("100=208 129=1 130=288 131=13398", msg2->toString()) ;

	EXPECT_EQ(IFpgaPdu::PduDataType::PDU_TYPE_MATLAB, msg->getPdu()->getType()) ;
	EXPECT_EQ(IFpgaPdu::PduDataType::PDU_TYPE_MATLAB, msg2->getPdu()->getType()) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaCommsMsgTest, PduToMsgErr)
{
	std::shared_ptr<IFpgaMsgTokens> testTokens(TestTokens::getInterface()) ;

	DataVariantList dvl("INT stimRe=1,INT stimIm=288,INT pimGain=13398,INT period=1,INT branches=1") ;
	std::shared_ptr<IFpgaMsg> msg2a( FpgaCommsMsgFactory::factory(testTokens, "set", dvl.getList()) ) ;

	// Create corrupted version
	std::shared_ptr<IFpgaPdu> pdu2a(msg2a->getPdu()) ;
	std::vector<UINT8> pdu2aBytes(pdu2a->getBytes()) ;
	for (unsigned idx=pdu2aBytes.size()/2; idx < pdu2aBytes.size(); ++idx)
	{
		pdu2aBytes[idx] = 0 ;
	}


for (unsigned idx=0; idx < pdu2aBytes.size(); ++idx)
{
	printf("0x%02x ", (unsigned)pdu2aBytes[idx]) ;
	if (idx % 15 == 0)
		std::cout << std::endl ;
}
std::cout << std::endl ;

	std::shared_ptr<IFpgaPdu> pdu2aErr(new FpgaPdu(pdu2aBytes)) ;

	// Use this created PDU to build a new FpgaCommsMsg
	std::shared_ptr<IFpgaMsg> msg2( FpgaCommsMsgFactory::factory(testTokens, pdu2aErr) ) ;

	EXPECT_FALSE(msg2->isError()) ;
	EXPECT_EQ(std::string(""), msg2->errorReason()) ;

	std::string msgStr(msg2->toString()) ;
	std::cerr << "MSG: " << msgStr << std::endl ;
	EXPECT_TRUE(msg2->isError()) ;
	EXPECT_NE(std::string(""), msg2->errorReason()) ;
}
#endif

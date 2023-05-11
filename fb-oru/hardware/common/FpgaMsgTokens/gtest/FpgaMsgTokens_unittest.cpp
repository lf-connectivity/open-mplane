/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaMsgTokens_unittest.cpp
 * \brief     Google Test of FpgaMsgTokens
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaMsgTokens class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "test_fixture.h"
#include "IFpgaCommsConstants.h"

// use to get the PIM view of the token numbers
#include "test_tok.h"

#include "TestTokens.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class FpgaMsgTokensTest : public TestFixture
{
public:
	void checkCmd(const std::string& tokenStr, int token)
	{
		std::shared_ptr<IFpgaMsgTokens> pimTok(TestTokens::getInterface()) ;
		EXPECT_EQ(token, pimTok->getCmdToken(tokenStr)) ;
		EXPECT_EQ(tokenStr, pimTok->getCmdTokenStr(token)) ;
	}

	void checkState(const std::string& tokenStr, int token)
	{
		std::shared_ptr<IFpgaMsgTokens> pimTok(TestTokens::getInterface()) ;
		EXPECT_EQ(token, pimTok->getStateToken(tokenStr)) ;
		EXPECT_EQ(tokenStr, pimTok->getStateTokenStr(token)) ;
	}

	void checkToken(const std::string& tokenStr, int token)
	{
		std::shared_ptr<IFpgaMsgTokens> pimTok(TestTokens::getInterface()) ;
		EXPECT_EQ(token, pimTok->getToken(tokenStr)) ;
		EXPECT_EQ(tokenStr, pimTok->getTokenStr(token)) ;
	}

};

#define CHECK_CMD(nm)	checkCmd(#nm, CMD_##nm)
#define CHECK_TOKEN(nm)	checkToken(#nm, TOK_##nm)
#define CHECK_STATE(nm)	checkState(#nm, STATEVAR_##nm)

//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaMsgTokensTest, Basic)
{
	std::shared_ptr<IFpgaMsgTokens> pimTok(TestTokens::getInterface()) ;

	CHECK_CMD(apiVersion) ;	// first
	CHECK_CMD(set) ;
	CHECK_CMD(get) ;
	CHECK_CMD(restart) ;
	CHECK_CMD(orthogonalise) ;
	CHECK_CMD(xcorr) ;	// last

	CHECK_STATE(response);	// first
	CHECK_STATE(msgId);
	CHECK_STATE(command);
	CHECK_STATE(succeeded );
	CHECK_STATE(buildNo );
	CHECK_STATE(logTrace );
	CHECK_STATE(data ); // last


	CHECK_TOKEN(NO ); // first
	CHECK_TOKEN(YES );
	CHECK_TOKEN(OFF );
	CHECK_TOKEN(ON);
	CHECK_TOKEN(disabled);
	CHECK_TOKEN(enabled );
	CHECK_TOKEN(none );
	CHECK_TOKEN(NACK );
	CHECK_TOKEN(ACK );
	CHECK_TOKEN(error ); // last


	EXPECT_EQ(API_VERSION, pimTok->getApiVersion()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaMsgTokensTest, Type)
{
	std::shared_ptr<IFpgaMsgTokens> pimTok(TestTokens::getInterface()) ;

	EXPECT_EQ("INT", pimTok->getStateTypeStr("msgId")) ;
	EXPECT_EQ("INT", pimTok->getStateTypeStr(STATEVAR_msgId)) ;
	EXPECT_EQ(DataVariantType::Int, pimTok->getStateType("msgId")) ;
	EXPECT_EQ(DataVariantType::Int, pimTok->getStateType(STATEVAR_msgId)) ;

	EXPECT_EQ("ENUM(NACK:ACK)", pimTok->getStateTypeStr("response")) ;
	EXPECT_EQ("ENUM(NACK:ACK)", pimTok->getStateTypeStr(STATEVAR_response)) ;
	EXPECT_EQ(DataVariantType::Enum, pimTok->getStateType("response")) ;
	EXPECT_EQ(DataVariantType::Enum, pimTok->getStateType(STATEVAR_response)) ;
	EXPECT_EQ("NACK", pimTok->getStateDefault("response")) ;
	EXPECT_EQ("NACK", pimTok->getStateDefault(STATEVAR_response)) ;
}

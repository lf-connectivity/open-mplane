/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaPdu_unittest.cpp
 * \brief     Google Test of FpgaPdu
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the FpgaPdu class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>
#include <memory>

#include "Path.h"
#include "dpd_fixture.h"
#include "IFpgaCommsConstants.h"
#include "FpgaPdu.h"

using namespace Mplane;

using namespace std;

//===========================================================================================================
// CLASSES

//-------------------------------------------------------------------------------------------------------------
class FpgaPduTest : public DpdTestFixture
{
};


//===========================================================================================================
// TESTS

//-------------------------------------------------------------------------------------------------------------
TEST_F(FpgaPduTest, Basic)
{
	// Command
    std::shared_ptr<FpgaPdu> msgC1(new FpgaPdu(FpgaPdu::PDU_TYPE_CMD, "this is a test")) ;

    EXPECT_EQ(FpgaPdu::PDU_TYPE_CMD, msgC1->getType()) ;
    EXPECT_EQ(std::string("this is a test"), msgC1->getData()) ;

    EXPECT_EQ(TYPE_BYTE_COMMAND, msgC1->getTypeByte()) ;

    std::vector<UINT8> bytes(msgC1->getDataBytes()) ;
    std::vector<UINT8> expectedBytes{
    	0x74, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x61, 0x20, 0x74, 0x65, 0x73, 0x74
    } ;
    EXPECT_EQ(expectedBytes.size(), bytes.size()) ;
    if (expectedBytes.size() == bytes.size())
    {
    	unsigned idx=0 ;
    	for (auto cc : expectedBytes)
    	{
//    		std::cerr << "BYTE " << idx <<
//    			std::hex <<
//    			" : Expect 0x" << (unsigned)cc << " '" << (char)cc << "' " <<
//    			" : Got 0x" << (unsigned)bytes[idx] << " '" << (char)bytes[idx] << "' " <<
//    			std::dec << std::endl ;
    		EXPECT_EQ(cc, bytes[idx]) ;
    		++idx ;
    	}
    }

    // Command
    std::shared_ptr<FpgaPdu> msgC2(new FpgaPdu(TYPE_BYTE_COMMAND, expectedBytes)) ;
    EXPECT_EQ(FpgaPdu::PDU_TYPE_CMD, msgC2->getType()) ;
    EXPECT_EQ(TYPE_BYTE_COMMAND, msgC2->getTypeByte()) ;

    // Event
    std::shared_ptr<FpgaPdu> msgE1(new FpgaPdu(TYPE_BYTE_EVENT, expectedBytes)) ;

    EXPECT_EQ(FpgaPdu::PDU_TYPE_EVENT, msgE1->getType()) ;
    EXPECT_EQ(std::string("this is a test"), msgE1->getData()) ;

    EXPECT_EQ(TYPE_BYTE_EVENT, msgE1->getTypeByte()) ;

    std::vector<UINT8> bytes2(msgE1->getDataBytes()) ;
    EXPECT_EQ(expectedBytes.size(), bytes2.size()) ;
    if (expectedBytes.size() == bytes2.size())
    {
    	unsigned idx=0 ;
    	for (auto cc : expectedBytes)
    	{
//    		std::cerr << "BYTE " << idx <<
//    			std::hex <<
//    			" : Expect 0x" << (unsigned)cc << " '" << (char)cc << "' " <<
//    			" : Got 0x" << (unsigned)bytes2[idx] << " '" << (char)bytes2[idx] << "' " <<
//    			std::dec << std::endl ;
    		EXPECT_EQ(cc, bytes2[idx]) ;
    		++idx ;
    	}
    }


    // Event
    std::shared_ptr<FpgaPdu> msgE2(new FpgaPdu(FpgaPdu::PDU_TYPE_EVENT, "this is a test")) ;
    EXPECT_EQ(FpgaPdu::PDU_TYPE_EVENT, msgE2->getType()) ;
    EXPECT_EQ(TYPE_BYTE_EVENT, msgE2->getTypeByte()) ;


    // Response
    std::shared_ptr<FpgaPdu> msgR1(new FpgaPdu(TYPE_BYTE_RESPONSE, expectedBytes)) ;
    EXPECT_EQ(FpgaPdu::PDU_TYPE_REPLY, msgR1->getType()) ;
    EXPECT_EQ(TYPE_BYTE_RESPONSE, msgR1->getTypeByte()) ;

    // Response
    std::shared_ptr<FpgaPdu> msgR2(new FpgaPdu(FpgaPdu::PDU_TYPE_REPLY, "this is a test")) ;
    EXPECT_EQ(FpgaPdu::PDU_TYPE_REPLY, msgR2->getType()) ;
    EXPECT_EQ(TYPE_BYTE_RESPONSE, msgR2->getTypeByte()) ;



    // Log
    std::shared_ptr<FpgaPdu> msgL1(new FpgaPdu(TYPE_BYTE_LOG, expectedBytes)) ;
    EXPECT_EQ(FpgaPdu::PDU_TYPE_LOG, msgL1->getType()) ;
    EXPECT_EQ(TYPE_BYTE_LOG, msgL1->getTypeByte()) ;

    // Log
    std::shared_ptr<FpgaPdu> msgL2(new FpgaPdu(FpgaPdu::PDU_TYPE_LOG, "this is a test")) ;
    EXPECT_EQ(FpgaPdu::PDU_TYPE_LOG, msgL2->getType()) ;
    EXPECT_EQ(TYPE_BYTE_LOG, msgL2->getTypeByte()) ;


}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OffTargetFPGATestCase.cpp
 * \brief     Implementation of the CppUnit test harness for OffTargetFPGA
 *
 *
 * \details   This file contains the implementation of the CppUnit test cases
 *            for the hardware fpga OffTargetFPGA class.
 *
 */
#include <sys/ioctl.h>

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>

#include "OffTargetFPGA.h"
#include "OffTargetFPGATestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( OffTargetFPGATestCase );

using namespace std;

/****** Area for unit test specifics  ******/

/****** End of Area for unit test specifics  ******/

struct FieldSequenceCheck {

	std::string mField ;
	UINT16 mValue ;
};

static const FieldSequenceCheck c0FieldData[] = {
	{ "ResyncUL[4]", 0x0001 },
	{ "ResyncDL[4]", 0x0000 }
};
#define NUM_C0_FIELD_DATA	(sizeof(c0FieldData) / sizeof(FieldSequenceCheck))


/*
 * Unit tests
 */
void OffTargetFPGATestCase::testCreation()
{
    cout << endl << "*** OffTargetFPGATestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    std::shared_ptr<OffTargetFPGA> OffTargetFPGA = OffTargetFPGA::getInstance();
    (void)OffTargetFPGA; // keep compiler happy

    cout << __func__ << " - END" <<  endl;
}

void OffTargetFPGATestCase::testRegisterWriteRead()
{
    cout << __func__ << " - START" <<  endl;

    UINT32 regOffset = 0x10000;
    UINT16 writeValue = 0xc0fe;
    UINT16 readValue = 0x0000;

    std::shared_ptr<OffTargetFPGA> OffTargetFPGA = OffTargetFPGA::getInstance();
    OffTargetFPGA->reset() ;

    // confirm the register value starts at default value
    UINT16 defaultValue = OffTargetFPGA->defaultValue() ;
    bool valid = OffTargetFPGA->readReg(regOffset, &readValue);
    CPPUNIT_ASSERT(!valid);
    CPPUNIT_ASSERT(readValue == defaultValue);

    // confirm the FPGA register write was successful
    CPPUNIT_ASSERT(OffTargetFPGA->writeReg(regOffset, writeValue));
    OffTargetFPGA->readReg(regOffset, &readValue);
    CPPUNIT_ASSERT(readValue == writeValue);


    cout << __func__ << " - END" <<  endl;
}

void OffTargetFPGATestCase::testFields()
{
    cout << __func__ << " - START" <<  endl;

    std::shared_ptr<OffTargetFPGA> OffTargetFPGA = OffTargetFPGA::getInstance();
    UINT16 readValue = 0x0000;

    CPPUNIT_ASSERT( OffTargetFPGA->writeReg(0x00004, 0x0000, 0xFFFF) ) ;

    OffTargetFPGA->writeField("alarmStatusSpi0Done", 1) ;
    OffTargetFPGA->writeField("alarmStatusDynAdcAlm", 0) ;

    CPPUNIT_ASSERT_EQUAL((UINT16)1, OffTargetFPGA->readField("alarmStatusSpi0Done"));

    CPPUNIT_ASSERT( OffTargetFPGA->readReg(0x00004, &readValue) ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x0080, readValue) ;

//    name=alarmStatusSynthStatus position=0x00004 mask=0x0001 shift=0
//    name=alarmStatusDynAdcAlm position=0x00004 mask=0x0001 shift=2
//    name=alarmStatusFpgaTempAlm position=0x00004 mask=0x0001 shift=3
//    name=alarmStatusFpgaTempAlert position=0x00004 mask=0x0001 shift=4
//    name=alarmStatusPsuAlm position=0x00004 mask=0x0001 shift=5
//    name=alarmStatusAuroraChannelUp position=0x00004 mask=0x0001 shift=6
//    name=alarmStatusSpi0Done position=0x00004 mask=0x0001 shift=7
//    name=alarmStatusSpi1Done position=0x00004 mask=0x0001 shift=8
//    name=alarmStatusPsuFail position=0x00004 mask=0x0001 shift=9

    OffTargetFPGA->writeReg(0x00004, 0x0555) ;

    CPPUNIT_ASSERT_EQUAL( (UINT16)1, OffTargetFPGA->readField("alarmStatusSynthStatus") ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)1, OffTargetFPGA->readField("alarmStatusDynAdcAlm") ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)1, OffTargetFPGA->readField("alarmStatusFpgaTempAlert") ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)1, OffTargetFPGA->readField("alarmStatusAuroraChannelUp") ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)1, OffTargetFPGA->readField("alarmStatusSpi1Done") ) ;

    CPPUNIT_ASSERT_EQUAL( (UINT16)0, OffTargetFPGA->readField("alarmStatusFpgaTempAlm") ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0, OffTargetFPGA->readField("alarmStatusPsuAlm") ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0, OffTargetFPGA->readField("alarmStatusSpi0Done") ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0, OffTargetFPGA->readField("alarmStatusPsuFail") ) ;

    OffTargetFPGA->writeField("alarmStatusDynAdcAlm", (UINT16)0) ;
    OffTargetFPGA->writeField("alarmStatusFpgaTempAlert", (UINT16)0) ;
    OffTargetFPGA->writeField("alarmStatusAuroraChannelUp", (UINT16)0) ;
    OffTargetFPGA->writeField("alarmStatusSpi1Done", (UINT16)0) ;
    OffTargetFPGA->writeField("alarmStatusPsuFail", (UINT16)0) ;

    CPPUNIT_ASSERT( OffTargetFPGA->readReg(0x00004, &readValue) ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x401, readValue) ;

    OffTargetFPGA->writeField("alarmStatusSynthStatus", (UINT16)1) ;
    OffTargetFPGA->writeField("alarmStatusFpgaTempAlm", (UINT16)1) ;
    OffTargetFPGA->writeField("alarmStatusPsuAlm", (UINT16)1) ;
    OffTargetFPGA->writeField("alarmStatusSpi0Done", (UINT16)1) ;
    OffTargetFPGA->writeField("alarmStatusPsuFail", (UINT16)1) ;
    OffTargetFPGA->writeField("alarmStatusSynthStatus", (UINT16)1) ;

    CPPUNIT_ASSERT( OffTargetFPGA->readReg(0x00004, &readValue) ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x6a9, readValue) ;

    //== INDEXED ==
    CPPUNIT_ASSERT( OffTargetFPGA->writeReg(0x4020c, 0x2345) ) ;
    CPPUNIT_ASSERT( OffTargetFPGA->readReg(0x4020c, &readValue) ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x2345, readValue) ;

    CPPUNIT_ASSERT( OffTargetFPGA->writeReg(0x4120c, 0x6789) ) ;
    CPPUNIT_ASSERT( OffTargetFPGA->readReg(0x4120c, &readValue) ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x6789, readValue) ;

    CPPUNIT_ASSERT_EQUAL( (UINT16)0x5, OffTargetFPGA->readField("StatCode[0]") ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x9, OffTargetFPGA->readField("StatCode[1]") ) ;

    OffTargetFPGA->writeField("StatCode[0]", (UINT16)0xA) ;
    OffTargetFPGA->writeField("StatCode[1]", (UINT16)0x0) ;

    CPPUNIT_ASSERT_EQUAL( (UINT16)0xA, OffTargetFPGA->readField("StatCode[0]") ) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x0, OffTargetFPGA->readField("StatCode[1]") ) ;

}


void OffTargetFPGATestCase::testData()
{
    cout << __func__ << " - START" <<  endl;

    std::shared_ptr<OffTargetFPGA> OffTargetFPGA = OffTargetFPGA::getInstance();

    // field SPI0_READ_DATA_LO at 0x00208 bits [15..0]
    // field SPI0_READ_DATA_HI at 0x0020a bits [15..0]

    OffTargetFPGA->writeReg(0x00208, 0x5555) ;
    OffTargetFPGA->writeReg(0x0020a, 0xAAAA) ;

    UINT16 rdVal ;

    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x5555, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xAAAA, rdVal ) ;

    // Add some data sources
    std::vector<UINT16> data ;
    data.push_back( 0x1111 );
    data.push_back( 0x2222 );
    data.push_back( 0x3333 );
    data.push_back( 0x4444 );
    OffTargetFPGA->registerDataValues(0x00208, data) ;

    data.clear() ;
    data.push_back( 0x00AA );
    data.push_back( 0x00BB );
    data.push_back( 0x00CC );
    OffTargetFPGA->registerDataValues(0x0020a, data) ;

    // 0
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1111, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x00AA, rdVal ) ;

    // 1
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x2222, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x00BB, rdVal ) ;

    // 2
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x3333, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x00CC, rdVal ) ;

    // 3
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x4444, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xAAAA, rdVal ) ;

    // 4
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x5555, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xAAAA, rdVal ) ;


    // == Do it again but using field names ==

    // Add some data sources
    data.clear() ;
    data.push_back( 0x1111 );
    data.push_back( 0x2222 );
    data.push_back( 0x3333 );
    data.push_back( 0x4444 );
    OffTargetFPGA->registerDataValues("spi0ReadDataLo", data) ;

    data.clear() ;
    data.push_back( 0x00AA );
    data.push_back( 0x00BB );
    data.push_back( 0x00CC );
    OffTargetFPGA->registerDataValues("spi0ReadDataHi", data) ;

    // 0
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1111, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x00AA, rdVal ) ;

    // 1
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x2222, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x00BB, rdVal ) ;

    // 2
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x3333, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x00CC, rdVal ) ;

    // 3
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x4444, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xAAAA, rdVal ) ;

    // 4
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x5555, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xAAAA, rdVal ) ;

    // == Check repeat ==
    data.clear() ;
    data.push_back( 0x1111 );
    data.push_back( 0x2222 );
    OffTargetFPGA->registerDataValues("spi0ReadDataLo", data, OffTargetFPGA::DATAVALUES_REPEAT) ;

    // 0
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1111, rdVal ) ;

    // 1
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x2222, rdVal ) ;

    // 0
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1111, rdVal ) ;

    // 1
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x2222, rdVal ) ;

    // 0
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1111, rdVal ) ;

    // 1
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x2222, rdVal ) ;

    // 0
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1111, rdVal ) ;

    // 1
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x2222, rdVal ) ;


    // == Clear repeat ==
    data.clear() ;
    data.push_back( 0x1111 );
    data.push_back( 0x2222 );
    OffTargetFPGA->registerDataValues("spi0ReadDataLo", data) ;

    // 0
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1111, rdVal ) ;

    // 1
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x2222, rdVal ) ;

    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x5555, rdVal ) ;
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x5555, rdVal ) ;
}

void OffTargetFPGATestCase::testReset()
{
    cout << __func__ << " - START" <<  endl;

    std::shared_ptr<OffTargetFPGA> OffTargetFPGA = OffTargetFPGA::getInstance();

    OffTargetFPGA->writeReg(0x00000, 0x1010) ;
    OffTargetFPGA->writeReg(0x00002, 0x1210) ;
    OffTargetFPGA->writeReg(0x00004, 0x1410) ;
    OffTargetFPGA->writeReg(0x00006, 0x1610) ;
    OffTargetFPGA->writeReg(0x00008, 0x1810) ;
    OffTargetFPGA->writeReg(0x00208, 0x5555) ;
    OffTargetFPGA->writeReg(0x0020a, 0xAAAA) ;


    UINT16 rdVal ;

    OffTargetFPGA->readReg(0x00000, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1010, rdVal ) ;
    OffTargetFPGA->readReg(0x00002, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1210, rdVal ) ;
    OffTargetFPGA->readReg(0x00004, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1410, rdVal ) ;
    OffTargetFPGA->readReg(0x00006, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1610, rdVal ) ;
    OffTargetFPGA->readReg(0x00008, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x1810, rdVal ) ;
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x5555, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xAAAA, rdVal ) ;

    // Add some data sources
    std::vector<UINT16> data ;
    data.push_back( 0x1111 );
    data.push_back( 0x2222 );
    data.push_back( 0x3333 );
    data.push_back( 0x4444 );
    OffTargetFPGA->registerDataValues(0x00208, data) ;

    data.clear() ;
    data.push_back( 0x00AA );
    data.push_back( 0x00BB );
    data.push_back( 0x00CC );
    OffTargetFPGA->registerDataValues(0x0020a, data) ;


    // Do reset
    OffTargetFPGA->reset() ;

    // should be back to default value
    OffTargetFPGA->readReg(0x00000, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xDEAD, rdVal ) ;
    OffTargetFPGA->readReg(0x00002, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x0180, rdVal ) ;
    OffTargetFPGA->readReg(0x00004, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0x0180, rdVal ) ;
    OffTargetFPGA->readReg(0x00006, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xDEAD, rdVal ) ;
    OffTargetFPGA->readReg(0x00008, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xDEAD, rdVal ) ;
    OffTargetFPGA->readReg(0x00208, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xDEAD, rdVal ) ;
    OffTargetFPGA->readReg(0x0020a, &rdVal) ;
    CPPUNIT_ASSERT_EQUAL( (UINT16)0xDEAD, rdVal ) ;
}



void OffTargetFPGATestCase::testSequenceCheck()
{
    cout << __func__ << " - START" <<  endl;

    std::shared_ptr<OffTargetFPGA> OffTargetFPGA = OffTargetFPGA::getInstance();


    // Make a sequence
    std::vector<OffTargetFPGA::SequenceCheck> seq1 ;
    seq1.push_back(OffTargetFPGA::SequenceCheck(0x00208, 0x1111)) ;
    seq1.push_back(OffTargetFPGA::SequenceCheck(0x0020A, 0x2222, 0x00ff)) ;
    seq1.push_back(OffTargetFPGA::SequenceCheck(0x0020C, 0x3333, 0xff00)) ;
    seq1.push_back(OffTargetFPGA::SequenceCheck(0x00208, 0x4444)) ;
    seq1.push_back(OffTargetFPGA::SequenceCheck(0x0020A, 0x5555, 0x00ff)) ;
    seq1.push_back(OffTargetFPGA::SequenceCheck(0x0020C, 0x6666, 0xff00)) ;
    OffTargetFPGA->addSequenceCheck("seqTest1", seq1) ;

    OffTargetFPGA->showSequenceCheck("seqTest1") ;
    CPPUNIT_ASSERT(!OffTargetFPGA->isSequenceCheckComplete("seqTest1")) ;

    OffTargetFPGA->writeReg(0x00208, 0x1111) ;
    OffTargetFPGA->writeReg(0x0020a, 0x2222) ;

    // should have stepped forward 2 elements in the sequence
    OffTargetFPGA->showSequenceCheck("seqTest1") ;

    // cause a mismatch
    OffTargetFPGA->writeReg(0x0020c, 0x5555) ;

    // should be back to start
    OffTargetFPGA->showSequenceCheck("seqTest1") ;

    // Start again
    OffTargetFPGA->writeReg(0x00208, 0x1111) ;
    CPPUNIT_ASSERT(!OffTargetFPGA->isSequenceCheckComplete("seqTest1")) ;
    OffTargetFPGA->writeReg(0x0020a, 0x0022) ;
    CPPUNIT_ASSERT(!OffTargetFPGA->isSequenceCheckComplete("seqTest1")) ;
    OffTargetFPGA->writeReg(0x0020c, 0x3300) ;
    CPPUNIT_ASSERT(!OffTargetFPGA->isSequenceCheckComplete("seqTest1")) ;
    OffTargetFPGA->writeReg(0x00208, 0x4444) ;
    CPPUNIT_ASSERT(!OffTargetFPGA->isSequenceCheckComplete("seqTest1")) ;
    OffTargetFPGA->writeReg(0x0020a, 0x0055) ;
    CPPUNIT_ASSERT(!OffTargetFPGA->isSequenceCheckComplete("seqTest1")) ;
    OffTargetFPGA->writeReg(0x0020c, 0x6600) ;
    CPPUNIT_ASSERT(OffTargetFPGA->isSequenceCheckComplete("seqTest1")) ;

    OffTargetFPGA->showSequenceCheck("seqTest1") ;


    std::vector<FieldSequenceCheck> fieldSeq(c0FieldData, c0FieldData+NUM_C0_FIELD_DATA) ;

}

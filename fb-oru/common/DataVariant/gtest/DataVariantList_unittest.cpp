/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariant_unittest.cpp
 * \brief     Google Test of DataVariant
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the DataVariant class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "IDataVariantSettings.h"
#include "DataVariant.h"

using namespace Mplane;

using namespace std;


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("INT ival,FLOAT fval,ENUM(AA:BB:CC) eval,BOOL bval") ;
	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("ival= fval= eval= bval=", dlist.toString()) ;
	EXPECT_FALSE(dlist.allSet()) ;

	DataVariantList dlist2("INT ival=123,FLOAT fval=45.6,ENUM(AA:BB:CC) eval=cc,BOOL bval=true") ;
	cout << "LIST=" << dlist2.toString() << endl ;
	EXPECT_EQ("ival=123 fval=45.6 eval=CC bval=true", dlist2.toString()) ;
	EXPECT_TRUE(dlist2.allSet()) ;

	DataVariantList dlist3("INT ival=123,FLOAT fval,ENUM(AA:BB:CC) eval=cc,BOOL bval=true") ;
	cout << "LIST=" << dlist3.toString() << endl ;
	EXPECT_EQ("ival=123 fval= eval=CC bval=true", dlist3.toString()) ;
	EXPECT_FALSE(dlist3.allSet()) ;

	DataVariantList dlist4("INT ival=123,FLOAT fval,ENUM(AA:BB:CC) eval=cc,BOOL bval=true,COMPLEX cval=12.3-i45.6") ;
	cout << "LIST=" << dlist4.toString() << endl ;
	EXPECT_EQ("ival=123 fval= eval=CC bval=true cval=12.3-i45.6", dlist4.toString()) ;
	EXPECT_FALSE(dlist4.allSet()) ;
	DataVariant* dv(dlist4.find("cval")) ;
	EXPECT_EQ(DataVariantType::Complex, dv->getType()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Optional)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist1("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT fval],ENUM(AA:BB:CC) eval=cc,BOOL bval=true") ;
	cout << "LIST=" << dlist1.toStringFull() << endl ;
	EXPECT_EQ("Status=OK Message=\"\" Info=\"\" fval= eval=CC bval=true", dlist1.toStringFull()) ;
	EXPECT_EQ("Status=OK fval= eval=CC bval=true", dlist1.toString()) ;
	EXPECT_TRUE(dlist1.allSet()) ;

	DataVariantList dlist3("INT ival=123,[FLOAT fval],ENUM(AA:BB:CC) eval=cc,BOOL bval=true") ;
	cout << "LIST=" << dlist3.toString() << endl ;
	EXPECT_EQ("ival=123 fval= eval=CC bval=true", dlist3.toString()) ;
	EXPECT_TRUE(dlist3.allSet()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Multiple)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist3("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],INT ival=123,INT Status") ;
	cout << "LIST=" << dlist3.toString() << endl ;
	EXPECT_EQ("Status=OK Message=\"\" Info=\"\" ival=123", dlist3.toStringFull()) ;
	EXPECT_EQ("Status=OK ival=123", dlist3.toString()) ;
	EXPECT_TRUE(dlist3.allSet()) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Vector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// NOTE: ival has default value of 123
	DataVariantList dlist("INT ival=123,INT[] ivec") ;
	cout << "LIST=" << dlist.toString() << endl ;

	bool ok = dlist.set("ival=1 ivec[1]=111 ivec[2]=222") ;
	EXPECT_TRUE( ok ) << dlist.getError() ;

	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("ival=1 ivec[0]= ivec[1]=111 ivec[2]=222", dlist.toString()) ;

	DataVariant* dv(dlist.find("ivec")) ;
	dv->setName(0, "firstVec") ;
	dv->setName(2, "thirdVec") ;

	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("ival=1 firstVec= ivec[1]=111 thirdVec=222", dlist.toString()) ;

	dv->setName(1, "secondVec") ;

	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("ival=1 firstVec= secondVec=111 thirdVec=222", dlist.toString()) ;

	dv->set(3, 333, "another") ;

	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("ival=1 firstVec= secondVec=111 thirdVec=222 another=333", dlist.toString()) ;

	// Test value clear
	dlist.clearValues() ;

	// ival reset to default
	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("ival=123", dlist.toString()) ;
	dlist.find("ival")->set(1) ;
	dv->set(0, 444) ;

	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("ival=1 ivec[0]=444", dlist.toString()) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, VectorHex)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("HEXINT[] ivec") ;
	cout << "LIST=" << dlist.toString() << endl ;

	DataVariant* dv(dlist.find("ivec")) ;
	dv->set(1, 111) ;
	dv->set(2, 222) ;

std::cerr << "-- get list --" << std::endl ;
	std::vector< std::pair<std::string, DataVariant> > vecList( dv->getList() ) ;
std::cerr << "--------------" << std::endl ;
	std::vector< std::pair<std::string, DataVariant> >::const_iterator iter ;
	for (iter=vecList.begin(); iter != vecList.end(); ++iter)
	{
		std::cout << iter->first << " : " << iter->second.getTypeStr() << " " << iter->second.isHex() << " " << std::endl ;
	}

	dv->setName(0, "firstVec") ;
	dv->setName(2, "thirdVec") ;

	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("firstVec= ivec[1]=0x6F thirdVec=0xDE", dlist.toString()) ;

	dv->setName(1, "secondVec") ;

	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("firstVec= secondVec=0x6F thirdVec=0xDE", dlist.toString()) ;

	dv->set(3, 333, "another") ;

	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("firstVec= secondVec=0x6F thirdVec=0xDE another=0x14D", dlist.toString()) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Units)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("INT freq (kHz),FLOAT power (dB),ENUM(AA:BB:CC) eval,BOOL bval") ;
	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("freq= power= eval= bval=", dlist.toString()) ;
	EXPECT_FALSE(dlist.allSet()) ;

	DataVariant* dvf( dlist.find("freq") ) ;
	EXPECT_EQ("kHz", dvf->getUnits()) ;
	dvf->set(123) ;
	EXPECT_EQ("freq=123kHz power= eval= bval=", dlist.toString()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, SuperSet)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("INT freq (kHz),FLOAT power (dB),ENUM(AA:BB:CC) eval,BOOL bval") ;
	EXPECT_TRUE( dlist.superset( std::string("INT freq (kHz),FLOAT power (dB),ENUM(AA:BB:CC) eval,BOOL bval") ) ) ;
	EXPECT_TRUE( dlist.superset( std::string("INT freq,FLOAT power,ENUM(AA:BB:CC) eval,BOOL bval") ) ) ;
	EXPECT_TRUE( dlist.superset( std::string("ENUM(AA:BB:CC) eval,INT freq") ) ) ;
	EXPECT_TRUE( dlist.superset( std::string("FLOAT power,ENUM(AA:BB:CC) eval,BOOL bval,INT freq") ) ) ;

	EXPECT_FALSE( dlist.superset( std::string("INT afreq") ) ) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, SubSet)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	// This with a list
	DataVariantList dlist("INT freq (kHz),FLOAT power (dB),ENUM(AA:BB:CC) eval,BOOL bval") ;

	EXPECT_TRUE( dlist.subset( std::string("INT freq (kHz),FLOAT power (dB),ENUM(AA:BB:CC) eval,BOOL bval") ) ) ;
	EXPECT_TRUE( dlist.subset( std::string("INT freq,FLOAT power,ENUM(AA:BB:CC) eval,BOOL bval") ) ) ;
	EXPECT_FALSE( dlist.subset( std::string("ENUM(AA:BB:CC) eval,INT freq") ) ) ;
	EXPECT_TRUE( dlist.subset( std::string("FLOAT power,ENUM(AA:BB:CC) eval,BOOL bval,INT freq") ) ) ;

	EXPECT_FALSE( dlist.subset( std::string("INT afreq") ) ) ;
	EXPECT_FALSE( dlist.subset( std::string("") ) ) ;

	EXPECT_TRUE( dlist.subset( std::string("INT newVal,FLOAT power,ENUM(AA:BB:CC) eval,BOOL bval,INT freq") ) ) ;
	EXPECT_TRUE( dlist.subset( std::string("FLOAT power,ENUM(AA:BB:CC) eval,BOOL bval,INT freq,INT newVal") ) ) ;

	EXPECT_FALSE( dlist.subset( std::string("INT newVal,FLOAT XXpower,ENUM(AA:BB:CC) eval,BOOL bval,INT freq") ) ) ;


	// This with a zero length list
	DataVariantList dlist2("") ;
	EXPECT_TRUE( dlist2.subset( std::string("INT afreq") ) ) ;
	EXPECT_TRUE( dlist2.subset( std::string("") ) ) ;

	// --
	std::string cmdRet("STRING[] ulSync,STRING[] dlSync") ;

	// ignore value with default
	DataVariantList dlist3("STRING[] ulSync,STRING[] dlSync,ENUM(OK:FAIL) Status=OK") ;
	EXPECT_TRUE( dlist3.subset( cmdRet ) ) ;

	// ignore value optional
	DataVariantList dlist4("STRING[] ulSync,STRING[] dlSync,[STRING Info]") ;
	EXPECT_TRUE( dlist4.subset( cmdRet ) ) ;

	// ignore value with both
	DataVariantList dlist5("STRING[] ulSync,STRING[] dlSync,ENUM(OK:FAIL) Status=OK,[STRING Info]") ;
	EXPECT_TRUE( dlist5.subset( cmdRet ) ) ;

	// ignore value with both
	DataVariantList dlist6("BOOL extra,STRING[] ulSync,STRING[] dlSync,ENUM(OK:FAIL) Status=OK,[STRING Info]") ;
	EXPECT_FALSE( dlist6.subset( cmdRet ) ) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Expand)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::string requiredArgs = "INT freq (kHz),FLOAT power (dB),ENUM(AA:BB:CC) eval,BOOL bval" ;
	DataVariantList dlist("INT freq") ;
	EXPECT_TRUE( dlist.subset( requiredArgs ) ) ;
	EXPECT_FALSE( dlist.superset( requiredArgs ) ) ;

	dlist.addFields( requiredArgs.c_str() ) ;
	EXPECT_TRUE( dlist.subset( requiredArgs ) ) ;
	EXPECT_TRUE( dlist.superset( requiredArgs ) ) ;
}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, VectorString)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

//	DataVariantList dlist("STRING[] arg") ;
	DataVariantList dlist("[STRING a1],[STRING a2],[STRING a3],[STRING a4],[STRING a5],[STRING a6]") ;

//	EXPECT_TRUE(dlist.set("a1 b2 c3 d4 e5")) ;
	EXPECT_TRUE(dlist.set("1 2 3 4 5")) ;
	cout << "LIST=" << dlist.toString() << endl ;

	EXPECT_EQ(std::string("a1=\"1\" a2=\"2\" a3=\"3\" a4=\"4\" a5=\"5\""), dlist.toString()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Default)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist1("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT fval=1.2],[FLOAT fval2],ENUM(AA:BB:CC) eval=cc,[BOOL bval=true]") ;
	cout << "LIST=" << dlist1.toStringFull() << endl ;
	EXPECT_EQ("Status=OK Message=\"\" Info=\"\" fval=1.2 fval2= eval=CC bval=true", dlist1.toStringFull()) ;
	EXPECT_EQ("Status=OK fval=1.2 fval2= eval=CC bval=true", dlist1.toString()) ;
	EXPECT_TRUE(dlist1.allSet()) ;

	cout << "VARLIST=" << dlist1.varlist(",", true) << std::endl ;
	EXPECT_EQ("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT fval=1.2],[FLOAT fval2],ENUM(AA:BB:CC) eval=CC,[BOOL bval=true]", dlist1.varlist(",", true)) ;
	DataVariant* dv = dlist1.find("status") ;
	EXPECT_EQ("OK", dv->getDefault()) ;
	dv->set("ERROR") ;

	dv = dlist1.find("fval") ;
	EXPECT_EQ("1.2", dv->getDefault()) ;
	dv->set("3.4") ;

	dv = dlist1.find("fval2") ;
	EXPECT_EQ("", dv->getDefault()) ;
	dv->set("5.6") ;

	cout << "VARLIST=" << dlist1.varlist(",", true) << std::endl ;
	EXPECT_EQ("ENUM(OK:ERROR) Status=ERROR,[STRING Message],[STRING Info],[FLOAT fval=3.4],[FLOAT fval2=5.6],ENUM(AA:BB:CC) eval=CC,[BOOL bval=true]", dlist1.varlist(",", true)) ;


	// clear out all values, reset any with defaults to that default value
	dlist1.clearValues() ;
	cout << "VARLIST=" << dlist1.varlist(",", true) << std::endl ;
	EXPECT_EQ("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT fval=1.2],[FLOAT fval2],ENUM(AA:BB:CC) eval=CC,[BOOL bval=true]", dlist1.varlist(",", true)) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Limits)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist1("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT{1.1..2.5} fval=1.2],[FLOAT{0.0..20.1} fval2],ENUM(AA:BB:CC) eval=cc,[BOOL bval=true]") ;
	cout << "LIST=" << dlist1.toStringFull() << endl ;
	EXPECT_EQ("Status=OK Message=\"\" Info=\"\" fval=1.2 fval2= eval=CC bval=true", dlist1.toStringFull()) ;
	EXPECT_EQ("Status=OK fval=1.2 fval2= eval=CC bval=true", dlist1.toString()) ;
	EXPECT_EQ("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT{1.1..2.5} fval=1.2],[FLOAT{0.0..20.1} fval2],ENUM(AA:BB:CC) eval=CC,[BOOL bval=true]", dlist1.varlist(",", true)) ;
	EXPECT_TRUE(dlist1.allSet()) ;

	cout << "VARS=" << dlist1.varlist(",", true) << endl ;

	std::string error ;

	DataVariant* dv = dlist1.find("fval") ;
	EXPECT_EQ("1.2", dv->getDefault()) ;
	EXPECT_TRUE(dv->checkLimits()) ;
	dv->set("3.4") ;
	EXPECT_FALSE(dv->checkLimits()) ;
	EXPECT_FALSE(dv->checkLimits(error)) ;
	EXPECT_EQ("fval greater than maximum 2.5", error) ;

	error = "" ;
	EXPECT_FALSE(dlist1.checkLimits(error)) ;
	EXPECT_EQ("fval greater than maximum 2.5", error) ;
	std::cout << "EXPECT: " << error << std::endl ;
	EXPECT_FALSE(dlist1.checkLimits()) ;
	EXPECT_EQ("fval greater than maximum 2.5", dlist1.getError()) ;

	dv = dlist1.find("fval2") ;
	EXPECT_EQ("", dv->getDefault()) ;
	EXPECT_TRUE(dv->checkLimits()) ;
	dv->set("5.6") ;
	EXPECT_TRUE(dv->checkLimits()) ;
	dv->set("51.6") ;
	EXPECT_FALSE(dv->checkLimits()) ;
	EXPECT_FALSE(dv->checkLimits(error)) ;
	EXPECT_EQ("fval2 greater than maximum 20.1", error) ;
	EXPECT_FALSE(dlist1.checkLimits()) ;
	EXPECT_EQ("fval greater than maximum 2.5, fval2 greater than maximum 20.1", dlist1.getError()) ;

	dv->set("-51.6") ;
	EXPECT_FALSE(dv->checkLimits()) ;
	EXPECT_FALSE(dv->checkLimits(error)) ;
	EXPECT_EQ("fval2 less than minimum 0", error) ;
	EXPECT_FALSE(dlist1.checkLimits()) ;
	EXPECT_EQ("fval greater than maximum 2.5, fval2 less than minimum 0", dlist1.getError()) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, OptionalBug)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist1(
		"INT path (None),[FLOAT maxPower (dBm)],[FLOAT minPower (dBm)],[FLOAT paPeakGain (dB)],"
		"[FLOAT rfDsaAcqAtten (dB)],[FLOAT acq1PowerTol (dBm)],[FLOAT acq1PowerMargin (dB)],"
		"[INT acq2SettlingTime (ticks)],[FLOAT acq2PowerTol (dBm)],[FLOAT muSeek (None)],"
		"[INT trackUpdateInterval (ticks)],[FLOAT muTrack (None)],[FLOAT panicPowerTol (dB)],"
		"[FLOAT trackInPowerTol (dB)],[FLOAT trackOutPowerTol (dB)],[INT numAvg (None)],"
		"[INT detMaxPos (LSB)],[FLOAT detCoeff (LSB/dBm)],[INT detCalOffset (LSB)],[FLOAT detCalPower (dBm)]"
	) ;

	dlist1.find("maxPower")->set(47.0f) ;
	dlist1.find("minPower")->set(27.0f) ;

	EXPECT_NEAR(47.0, dlist1.find("maxPower")->toFloat(), 0.1) ;
	EXPECT_NEAR(27.0, dlist1.find("minPower")->toFloat(), 0.1) ;

	std::string cmd("1 minPowers=25") ;
	EXPECT_FALSE(dlist1.set(cmd.c_str())) ;
	EXPECT_EQ("Invalid argument 'minPowers'", dlist1.getError()) ;

	EXPECT_TRUE(dlist1.find("path")->isSet()) ;
	EXPECT_FALSE(dlist1.find("maxPower")->isSet()) ;
	EXPECT_FALSE(dlist1.find("minPower")->isSet()) ;
	EXPECT_FALSE(dlist1.find("paPeakGain")->isSet()) ;
	EXPECT_FALSE(dlist1.find("rfDsaAcqAtten")->isSet()) ;
	EXPECT_FALSE(dlist1.find("acq1PowerTol")->isSet()) ;
	EXPECT_FALSE(dlist1.find("muSeek")->isSet()) ;
	EXPECT_FALSE(dlist1.find("trackUpdateInterval")->isSet()) ;
	EXPECT_FALSE(dlist1.find("muTrack")->isSet()) ;
	EXPECT_FALSE(dlist1.find("panicPowerTol")->isSet()) ;
	EXPECT_FALSE(dlist1.find("trackInPowerTol")->isSet()) ;
	EXPECT_FALSE(dlist1.find("trackOutPowerTol")->isSet()) ;
	EXPECT_FALSE(dlist1.find("numAvg")->isSet()) ;
	EXPECT_FALSE(dlist1.find("detMaxPos")->isSet()) ;
	EXPECT_FALSE(dlist1.find("detCoeff")->isSet()) ;
	EXPECT_FALSE(dlist1.find("detCalOffset")->isSet()) ;
	EXPECT_FALSE(dlist1.find("detCalPower")->isSet()) ;

	std::string cmd2("2 minPower=") ;
	EXPECT_FALSE(dlist1.set(cmd2.c_str())) ;
	EXPECT_EQ("Invalid argument 'minPower='", dlist1.getError()) ;

	std::string cmd3("2 =25") ;
	EXPECT_FALSE(dlist1.set(cmd3.c_str())) ;
	EXPECT_EQ("Invalid argument '=25'", dlist1.getError()) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, VectorComplex)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("COMPLEX[] cvec") ;
	cout << "LIST=" << dlist.toString() << endl ;

	DataVariant* dv(dlist.find("cvec")) ;
	dv->set(0, std::complex<float>(0, -111)) ;
	dv->set(1, std::complex<float>(-11100, 222.0500)) ;
	dv->set(2, std::complex<float>(222, -3330)) ;

	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("cvec[0]=0-j111 cvec[1]=-11100+j222.050003 cvec[2]=222-j3330", dlist.toString()) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, VarLimits)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IDataVariantSettings> settings(IDataVariantSettings::getInstance()) ;
	settings->registerSettings(std::map<std::string, std::string>{
		{ "NUM_PORTS",		"2" },
		{ "FVAL1_MIN",		"0.0" },
		{ "FVAL2_MAX",		"0.0" },
	}) ;
	EXPECT_TRUE(settings->setSetting("NUM_PORTS", "4")) ;
	EXPECT_TRUE(settings->setSetting("FVAL1_MIN", "1.1")) ;
	EXPECT_TRUE(settings->setSetting("FVAL2_MAX", "20.1")) ;


//	DataVariantList dlist1("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT{1.1..2.5} fval=1.2],[FLOAT{0.0..20.1} fval2],ENUM(AA:BB:CC) eval=cc,[BOOL bval=true]") ;
	DataVariantList dlist1("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT{${FVAL1_MIN}..2.5} fval=1.2],[FLOAT{0.0..${FVAL2_MAX}} fval2],INT{1..${NUM_PORTS}} index=2,[BOOL bval=true]") ;
	cout << "LIST=" << dlist1.toStringFull() << endl ;
	EXPECT_EQ("Status=OK Message=\"\" Info=\"\" fval=1.2 fval2= index=2 bval=true", dlist1.toStringFull()) ;
	EXPECT_EQ("Status=OK fval=1.2 fval2= index=2 bval=true", dlist1.toString()) ;
	EXPECT_EQ("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT{1.1..2.5} fval=1.2],[FLOAT{0.0..20.1} fval2],INT{1..4} index=2,[BOOL bval=true]", dlist1.varlist(",", true)) ;
	EXPECT_TRUE(dlist1.allSet()) ;

	cout << "VARS=" << dlist1.varlist(",", true) << endl ;

	std::string error ;

	DataVariant* dv = dlist1.find("fval") ;
	EXPECT_EQ("1.2", dv->getDefault()) ;
	EXPECT_TRUE(dv->checkLimits()) ;
	dv->set("3.4") ;
	EXPECT_FALSE(dv->checkLimits()) ;
	EXPECT_FALSE(dv->checkLimits(error)) ;
	EXPECT_EQ("fval greater than maximum 2.5", error) ;

	error = "" ;
	EXPECT_FALSE(dlist1.checkLimits(error)) ;
	EXPECT_EQ("fval greater than maximum 2.5", error) ;
	std::cout << "EXPECT: " << error << std::endl ;
	EXPECT_FALSE(dlist1.checkLimits()) ;
	EXPECT_EQ("fval greater than maximum 2.5", dlist1.getError()) ;

	dv = dlist1.find("fval2") ;
	EXPECT_EQ("", dv->getDefault()) ;
	EXPECT_TRUE(dv->checkLimits()) ;
	dv->set("5.6") ;
	EXPECT_TRUE(dv->checkLimits()) ;
	dv->set("51.6") ;
	EXPECT_FALSE(dv->checkLimits()) ;
	EXPECT_FALSE(dv->checkLimits(error)) ;
	EXPECT_EQ("fval2 greater than maximum 20.1", error) ;
	EXPECT_FALSE(dlist1.checkLimits()) ;
	EXPECT_EQ("fval greater than maximum 2.5, fval2 greater than maximum 20.1", dlist1.getError()) ;

	dv->set("-51.6") ;
	EXPECT_FALSE(dv->checkLimits()) ;
	EXPECT_FALSE(dv->checkLimits(error)) ;
	EXPECT_EQ("fval2 less than minimum 0", error) ;
	EXPECT_FALSE(dlist1.checkLimits()) ;
	EXPECT_EQ("fval greater than maximum 2.5, fval2 less than minimum 0", dlist1.getError()) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, CommaBug)
{
	// Found that you could specify string "1,3" as an INT parameter and it would be accepted
	// Turns out that the ",3" was being treated as a units string

	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist1(
		"INT index=1,[INT sensor=1]"
	) ;

	DataVariant* dv(dlist1.find("index")) ;

	dv->set("3") ;
	EXPECT_TRUE(dv->isSet()) ;
	dv->set("1,3") ;
	EXPECT_FALSE(dv->isSet()) ;

	dv->set("3") ;
	EXPECT_TRUE(dv->isSet()) ;
	dv->set("1.3") ;
	EXPECT_FALSE(dv->isSet()) ;

	dv->set("3") ;
	EXPECT_TRUE(dv->isSet()) ;
	dv->set("1x3") ;
	EXPECT_FALSE(dv->isSet()) ;


//	std::cerr << "EXPECT ERROR:" << dlist1.getError() << std::endl ;
//	EXPECT_FALSE(dlist1.getError().empty()) ;
//	EXPECT_EQ("Invalid argument '=25'", dlist1.getError()) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, ExpandEnum)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<IDataVariantSettings> settings(IDataVariantSettings::getInstance()) ;
	settings->registerSettings(std::map<std::string, std::string>{
		{ "NUM_PORTS",		"2" },
		{ "FVAL1_MIN",		"0.0" },
		{ "FVAL2_MAX",		"0.0" },
		{ "ENUM_TYPES",		"Tx:Rx" },
	}) ;
	EXPECT_TRUE(settings->setSetting("NUM_PORTS", "4")) ;
	EXPECT_TRUE(settings->setSetting("FVAL1_MIN", "1.1")) ;
	EXPECT_TRUE(settings->setSetting("FVAL2_MAX", "20.1")) ;
	EXPECT_TRUE(settings->setSetting("ENUM_TYPES", "Rx:Tx:RxAgc:PaDet")) ;


//	DataVariantList dlist1("ENUM(OK:ERROR) Status=OK,[STRING Message],[STRING Info],[FLOAT{1.1..2.5} fval=1.2],[FLOAT{0.0..20.1} fval2],ENUM(AA:BB:CC) eval=cc,[BOOL bval=true]") ;
	DataVariantList dlist1("ENUM(OK:ERROR) Status=OK,ENUM(${ENUM_TYPES}) type,[STRING Message],[STRING Info],[FLOAT{${FVAL1_MIN}..2.5} fval=1.2],[FLOAT{0.0..${FVAL2_MAX}} fval2],INT{1..${NUM_PORTS}} index=2,[BOOL bval=true]") ;
	cout << "LIST=" << dlist1.toStringFull() << endl ;
	EXPECT_EQ("Status=OK type= Message=\"\" Info=\"\" fval=1.2 fval2= index=2 bval=true", dlist1.toStringFull()) ;
	EXPECT_EQ("Status=OK type= fval=1.2 fval2= index=2 bval=true", dlist1.toString()) ;
	EXPECT_EQ("ENUM(OK:ERROR) Status=OK,ENUM(Rx:Tx:RxAgc:PaDet) type,[STRING Message],[STRING Info],[FLOAT{1.1..2.5} fval=1.2],[FLOAT{0.0..20.1} fval2],INT{1..4} index=2,[BOOL bval=true]", dlist1.varlist(",", true)) ;
	EXPECT_FALSE(dlist1.allSet()) ;

	DataVariant* dv ;
	dv = dlist1.find("type") ;
	dv->set("Tx") ;
	EXPECT_TRUE(dlist1.allSet()) ;

	cout << "VARS=" << dlist1.varlist(",", true) << endl ;

	std::string error ;

	dv = dlist1.find("fval") ;
	EXPECT_EQ("1.2", dv->getDefault()) ;
	EXPECT_TRUE(dv->checkLimits()) ;
	dv->set("3.4") ;
	EXPECT_FALSE(dv->checkLimits()) ;
	EXPECT_FALSE(dv->checkLimits(error)) ;
	EXPECT_EQ("fval greater than maximum 2.5", error) ;



	error = "" ;
	EXPECT_FALSE(dlist1.checkLimits(error)) ;
	EXPECT_EQ("fval greater than maximum 2.5", error) ;
	std::cout << "EXPECT: " << error << std::endl ;
	EXPECT_FALSE(dlist1.checkLimits()) ;
	EXPECT_EQ("fval greater than maximum 2.5", dlist1.getError()) ;

	dv = dlist1.find("fval2") ;
	EXPECT_EQ("", dv->getDefault()) ;
	EXPECT_TRUE(dv->checkLimits()) ;
	dv->set("5.6") ;
	EXPECT_TRUE(dv->checkLimits()) ;
	dv->set("51.6") ;
	EXPECT_FALSE(dv->checkLimits()) ;
	EXPECT_FALSE(dv->checkLimits(error)) ;
	EXPECT_EQ("fval2 greater than maximum 20.1", error) ;
	EXPECT_FALSE(dlist1.checkLimits()) ;
	EXPECT_EQ("fval greater than maximum 2.5, fval2 greater than maximum 20.1", dlist1.getError()) ;

	dv->set("-51.6") ;
	EXPECT_FALSE(dv->checkLimits()) ;
	EXPECT_FALSE(dv->checkLimits(error)) ;
	EXPECT_EQ("fval2 less than minimum 0", error) ;
	EXPECT_FALSE(dlist1.checkLimits()) ;
	EXPECT_EQ("fval greater than maximum 2.5, fval2 less than minimum 0", dlist1.getError()) ;


}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, VecLimits)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist1("FLOAT[]{1.1..2.5} fvals,INT[]{10..20} ivals,COMPLEX[]{-10.0..20.0} cvals") ;
	cout << "LIST=" << dlist1.toStringFull() << endl ;
	cout << "VARS=" << dlist1.varlist(",", true) << endl ;

	std::string error ;

	{
		DataVariant* dv = dlist1.find("fvals") ;
		dv->set(0, "3.4") ;
		EXPECT_FALSE(dv->checkLimits()) ;
		EXPECT_FALSE(dv->checkLimits(error)) ;
		EXPECT_EQ("fvals greater than maximum 2.5", error) ;
		error = "" ;
		EXPECT_FALSE(dlist1.checkLimits(error)) ;
		EXPECT_EQ("fvals greater than maximum 2.5", error) ;
		std::cout << "EXPECT: " << error << std::endl ;
		EXPECT_FALSE(dlist1.checkLimits()) ;
		EXPECT_EQ("fvals greater than maximum 2.5", dlist1.getError()) ;
		dv->set(0, "1.4") ;
	}

	{
		DataVariant* dv = dlist1.find("cvals") ;
		dv->set(0, "3.4+i4.5") ;
		EXPECT_TRUE(dv->checkLimits()) ;
		EXPECT_TRUE(dv->checkLimits(error)) ;
		error = "" ;
		cout << "LIST=" << dlist1.toStringFull() << endl ;
		cout << "VARS=" << dlist1.varlist(",", true) << endl ;

		dv->set(0, "-30+i4.5") ;
		EXPECT_FALSE(dv->checkLimits()) ;
		EXPECT_FALSE(dv->checkLimits(error)) ;
		cout << "LIST=" << dlist1.toStringFull() << endl ;
		cout << "VARS=" << dlist1.varlist(",", true) << endl ;
		EXPECT_EQ("cvals less than minimum -10", error) ;
		error = "" ;
		EXPECT_FALSE(dlist1.checkLimits(error)) ;
		EXPECT_EQ("cvals less than minimum -10", error) ;
		std::cout << "EXPECT: " << error << std::endl ;
		EXPECT_FALSE(dlist1.checkLimits()) ;
		EXPECT_EQ("cvals less than minimum -10", dlist1.getError()) ;

		dv->set(0, "6+i24.5") ;
		EXPECT_FALSE(dv->checkLimits()) ;
		EXPECT_FALSE(dv->checkLimits(error)) ;
		cout << "LIST=" << dlist1.toStringFull() << endl ;
		cout << "VARS=" << dlist1.varlist(",", true) << endl ;
		EXPECT_EQ("cvals greater than maximum 20", error) ;
		error = "" ;
		EXPECT_FALSE(dlist1.checkLimits(error)) ;
		EXPECT_EQ("cvals greater than maximum 20", error) ;
		std::cout << "EXPECT: " << error << std::endl ;
		EXPECT_FALSE(dlist1.checkLimits()) ;
		EXPECT_EQ("cvals greater than maximum 20", dlist1.getError()) ;

		dv->set(0, "3.4+i4.5") ;
	}


}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Bool)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("BOOL(no:yes)  console") ;
	cout << "LIST=" << dlist.toString() << endl ;

	DataVariant* db(dlist.find("console")) ;
	db->set("yes") ;
	EXPECT_TRUE(db->toBool());
	cout << "LIST=" << dlist.toStringFull() << endl ;

	db->set("no") ;
	EXPECT_FALSE(db->toBool());
	cout << "LIST=" << dlist.toStringFull() << endl ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Freq)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("FREQ freq (kHz),FLOAT power (dB),ENUM(AA:BB:CC) eval,BOOL bval") ;
	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("freq= power= eval= bval=", dlist.toString()) ;
	EXPECT_FALSE(dlist.allSet()) ;

    // Freq with units - value is always relative to the current units
	DataVariant* dvf( dlist.find("freq") ) ;
	EXPECT_EQ("kHz", dvf->getUnits()) ;
	EXPECT_EQ(DataVariantType::Freq, dvf->getType()) ;
	dvf->set(123) ;
	EXPECT_EQ("freq=123kHz power= eval= bval=", dlist.toString()) ;
	EXPECT_EQ(Frequency(123.0, Frequency::KHz), dvf->toFreq()) ;
	EXPECT_FLOAT_EQ(123.0, dvf->toFloat()) ;
	EXPECT_FLOAT_EQ(dvf->toFreq().getDbl( Frequency::str2unit(dvf->getUnits())), dvf->toFloat()) ;

	dvf->setFreq( Frequency(751000.0, Frequency::KHz) ) ;
	EXPECT_EQ("freq=751000kHz power= eval= bval=", dlist.toString()) ;
	EXPECT_EQ(Frequency(751000.0, Frequency::KHz), dvf->toFreq()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantList, Power)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("POWER{0.0..3.0} power (dB)") ;
	cout << "LIST=" << dlist.toString() << endl ;
	EXPECT_EQ("power=", dlist.toString()) ;
	EXPECT_FALSE(dlist.allSet()) ;

	DataVariant* dv( dlist.find("power") ) ;
	EXPECT_EQ("dB", dv->getUnits()) ;
	EXPECT_EQ(DataVariantType::Power, dv->getType()) ;
	dv->setFloat(1.0) ;
	EXPECT_EQ("power=1dB", dlist.toString()) ;
	EXPECT_EQ("POWER{0.0..3.0} power=1dB (dB)", dlist.varlist(",", true)) ;
	std::cerr << dlist.varlist(",", true) << std::endl ;
	EXPECT_FLOAT_EQ(1.0, dv->toFloat()) ;
	EXPECT_TRUE(dv->checkLimits()) ;

	dv->setFloat(4.0) ;
	EXPECT_FALSE(dv->checkLimits()) ;

}

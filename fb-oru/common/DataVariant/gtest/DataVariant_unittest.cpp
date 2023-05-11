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
#include "DataVariant.h"

using namespace Mplane;

using namespace std;

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    DataVariant* vi = new DataVariant("vi");
    DataVariant* viA = new DataVariant("viA=12");
    DataVariant* viB = new DataVariant("viB=this");
    DataVariant* viC = new DataVariant("viC=16384");
    DataVariant* viD = new DataVariant("viD=16.384");
    DataVariant* viE = new DataVariant("viE=20.6");
    DataVariant* viF = new DataVariant("viF=99.998");
    DataVariant* viX = new DataVariant("viX=0xFF");
    auto viY( std::unique_ptr<DataVariant>(new DataVariant("viY=12.3+j45.6")) );


    EXPECT_TRUE( vi != 0 );
    EXPECT_TRUE( viA != 0 );
    EXPECT_TRUE( viB != 0 );
    EXPECT_TRUE( viC != 0 );
    EXPECT_TRUE( viD != 0 );
    EXPECT_TRUE( viE != 0 );
    EXPECT_TRUE( viX != 0 );
    EXPECT_TRUE( viY ? true : false );

    EXPECT_EQ( vi->getType(), Mplane::DataVariantType::None );
    EXPECT_EQ( viA->getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( viB->getType(), Mplane::DataVariantType::String );
    EXPECT_EQ( viC->getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( viD->getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( viE->getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( viX->getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( viF->getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( viY->getType(), Mplane::DataVariantType::Complex );

    EXPECT_EQ( vi->getName(), "vi" );
    EXPECT_EQ( viA->getName(), "viA" );
    EXPECT_EQ( viB->getName(), "viB" );
    EXPECT_EQ( viC->getName(), "viC" );
    EXPECT_EQ( viD->getName(), "viD" );
    EXPECT_EQ( viE->getName(), "viE" );
    EXPECT_EQ( viF->getName(), "viF" );
    EXPECT_EQ( viX->getName(), "viX" );
    EXPECT_EQ( viY->getName(), "viY" );

    EXPECT_FALSE( viA->isHex() );
    EXPECT_FALSE( viB->isHex() );
    EXPECT_FALSE( viC->isHex() );
    EXPECT_FALSE( viD->isHex() );
    EXPECT_FALSE( viE->isHex() );
    EXPECT_FALSE( viF->isHex() );
    EXPECT_TRUE( viX->isHex() );
    EXPECT_FALSE( viY->isHex() );

    EXPECT_EQ( viA->toInt(), 12);
    EXPECT_EQ( viB->toInt(), 0);
    EXPECT_EQ( viC->toInt(), 16384);
    EXPECT_EQ( viD->toInt(), 16);
    EXPECT_EQ( viE->toInt(), 20);
    EXPECT_EQ( viF->toInt(), 99);
    EXPECT_EQ( viX->toInt(), 255);
    EXPECT_EQ( viY->toInt(), 12);

//    cout <<  viX->getName() << ": " << viX->toInt() << endl;

    EXPECT_EQ( viA->toFloat(), 12.0);
    EXPECT_EQ( viB->toFloat(), 0.0);
    EXPECT_EQ( viC->toFloat(), 16384.0);
    EXPECT_EQ( viD->toFloat(), 16.384f);
    EXPECT_EQ( viE->toFloat(), 20.6f);
    EXPECT_EQ( viF->toFloat(), 99.998f);
    EXPECT_EQ( viX->toFloat(), 255.0f);
    EXPECT_EQ( viY->toFloat(), 12.3f);


    EXPECT_EQ( viA->toString(), "12");
    EXPECT_EQ( viB->toString(), "this");
    EXPECT_EQ( viC->toString(), "16384");
    EXPECT_EQ( viD->toString(), "16.384");
    EXPECT_EQ( viE->toString(), "20.6");
    EXPECT_EQ( viF->toString(), "99.998");
    EXPECT_EQ( viX->toString(), "0xFF");
    EXPECT_EQ( viY->toString(), "12.3+j45.6");

//    cout <<  viE->getName() << ": " << viE->toString() << endl;

    DataVariant cpviA = DataVariant( *viA );
    EXPECT_EQ( cpviA.getName(), "viA" );
    EXPECT_EQ( cpviA.toInt(), 12);
    EXPECT_EQ( cpviA.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( cpviA.toFloat(), 12.0);
    EXPECT_EQ( cpviA.toString(), "12");

    DataVariant cpviB = DataVariant( *viB );
    EXPECT_EQ( cpviB.getName(), "viB" );
    EXPECT_EQ( cpviB.toInt(), 0);
    EXPECT_EQ( cpviB.getType(), Mplane::DataVariantType::String );
    EXPECT_EQ( cpviB.toFloat(), 0.0);
    EXPECT_EQ( cpviB.toString(), "this");

    DataVariant cpviD = DataVariant( *viD );
    EXPECT_EQ( cpviD.getName(), "viD" );
    EXPECT_EQ( cpviD.toInt(), 16);
    EXPECT_EQ( cpviD.getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( cpviD.toFloat(), 16.384f);
    EXPECT_EQ( cpviD.toString(), "16.384");

    DataVariant cpvi;
    EXPECT_EQ( cpvi.getType(), Mplane::DataVariantType::None );
    EXPECT_EQ( cpvi.getName(), "" );
    EXPECT_EQ( cpvi.toString(), "" );
    EXPECT_EQ( cpvi.toInt(), 0 );
    EXPECT_EQ( cpvi.toFloat(), 0.0 );

    cpvi = cpviA;
    EXPECT_NE( &cpvi, &cpviA);
    EXPECT_EQ( cpvi.getName(), "viA" );
    EXPECT_EQ( cpvi.toInt(), 12);
    EXPECT_EQ( cpvi.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( cpvi.toFloat(), 12.0);
    EXPECT_EQ( cpvi.toString(), "12");

    cpvi = cpviB;
    EXPECT_NE( &cpvi, &cpviA);
    EXPECT_NE( &cpvi, &cpviB);
    EXPECT_EQ( cpvi.getName(), "viB" );
    EXPECT_EQ( cpvi.toInt(), 0);
    EXPECT_EQ( cpvi.getType(), Mplane::DataVariantType::String );
    EXPECT_EQ( cpvi.toFloat(), 0.0);
    EXPECT_EQ( cpvi.toString(), "this");

    cpvi = cpviD;
    EXPECT_NE( &cpvi, &cpviA);
    EXPECT_NE( &cpvi, &cpviB);
    EXPECT_NE( &cpvi, &cpviD);
    EXPECT_EQ( cpvi.getName(), "viD" );
    EXPECT_EQ( cpvi.toInt(), 16);
    EXPECT_EQ( cpvi.getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( cpvi.toFloat(), 16.384f);
    EXPECT_EQ( cpvi.toString(), "16.384");

    std::string strvalue = "43770";

    viA->set( strvalue );
    EXPECT_EQ( viA->toInt(), 43770);

    vi->set(56);
    EXPECT_EQ( vi->toInt(), 56);
    EXPECT_EQ( vi->getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( vi->toString(), "56");
    vi->set( 19.99f );
    EXPECT_EQ( vi->toString(), "19");

    DataVariant fvi( "float" ) ;
    fvi.set(888.888f);
    EXPECT_EQ( fvi.getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( fvi.toString(), "888.888");
    fvi.set( 22 );
    EXPECT_EQ( fvi.getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( fvi.toString(), "22");

    viB->set(69);
    EXPECT_EQ( viB->getType(), Mplane::DataVariantType::String );
    EXPECT_EQ( viB->toString(), "69");
    viB->set( 123.4f );
    EXPECT_EQ( viB->getType(), Mplane::DataVariantType::String );
//    EXPECT_EQ( viB->toString(), "123.4");
    EXPECT_EQ( viB->toString(), "123.400002");

    EXPECT_EQ( viA->getNameValuePair(), "viA=43770" );
//    EXPECT_EQ( viB->getNameValuePair(), "viB=\"123.4\"" );
    EXPECT_EQ( viB->getNameValuePair(), "viB=\"123.400002\"" );
    EXPECT_EQ( viC->getNameValuePair(), "viC=16384" );
    EXPECT_EQ( viD->getNameValuePair(), "viD=16.384" );
    EXPECT_EQ( viE->getNameValuePair(), "viE=20.6" );
    EXPECT_EQ( viF->getNameValuePair(), "viF=99.998" );
    EXPECT_EQ( viX->getNameValuePair(), "viX=0xFF" );

    delete( viA );
    delete( viB );
    delete( viC );
    delete( viD );
    delete( viE );
    delete( viF );
    delete( viX );

    //test variants that are created with value pair values
    DataVariant dvs = DataVariant("string=test it");
    EXPECT_EQ( dvs.getName(), "string" );
    EXPECT_EQ( dvs.getType(), Mplane::DataVariantType::String );
    EXPECT_EQ( dvs.toString(), "test it");
    EXPECT_EQ( dvs.getNameValuePair(), "string=\"test it\"" );

    DataVariant dvi = DataVariant("integer=12");
    EXPECT_EQ( dvi.getName(), "integer" );
    EXPECT_EQ( dvi.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( dvi.toString(), "12");
    EXPECT_EQ( dvi.getNameValuePair(), "integer=12" );

    DataVariant dvf = DataVariant("float=32.0");
    EXPECT_EQ( dvf.getName(), "float" );
    EXPECT_EQ( dvf.getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( dvf.toString(), "32.0");
    EXPECT_EQ( dvf.getNameValuePair(), "float=32.0" );

    std::string vp = "hex=0xC0DE";
    DataVariant *dvh = new DataVariant(vp);
    EXPECT_EQ( dvh->getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( dvh->toString(), "0xC0DE");
    EXPECT_EQ( dvh->getNameValuePair(), "hex=0xC0DE" );

    vp = "empty";
    DataVariant ve = DataVariant(vp);
    EXPECT_EQ( ve.getName(), "empty" );
    EXPECT_EQ( ve.getType(), Mplane::DataVariantType::None );

    delete vi;
    delete dvh;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Int)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariant dvi("integer=-12");
    EXPECT_EQ( dvi.getName(), "integer" );
    EXPECT_EQ( dvi.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( dvi.toString(), "-12");
    EXPECT_EQ( dvi.toInt(), -12);
    EXPECT_EQ( dvi.getNameValuePair(), "integer=-12" );

    DataVariant i2("i2") ;
    i2.set("0x1234") ;
    EXPECT_EQ( i2.getName(), "i2" );
    EXPECT_EQ( i2.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( i2.toString(), "0x1234");
    EXPECT_EQ( i2.toInt(), 4660);
    EXPECT_EQ( i2.getNameValuePair(), "i2=0x1234" );
    EXPECT_TRUE( i2.isHex() );
    EXPECT_TRUE( i2.isSet() );

    i2.set("1234") ;
    EXPECT_EQ( i2.getName(), "i2" );
    EXPECT_EQ( i2.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( i2.toString(), "1234");
    EXPECT_EQ( i2.toInt(), 1234);
    EXPECT_EQ( i2.getNameValuePair(), "i2=1234" );
    EXPECT_FALSE( i2.isHex() );
    EXPECT_TRUE( i2.isSet() );

    DataVariant i3("i3=0x1234") ;
    EXPECT_EQ( i3.getName(), "i3" );
    EXPECT_EQ( i3.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( i3.toString(), "0x1234");
    EXPECT_EQ( i3.toInt(), 4660);
    EXPECT_EQ( i3.getNameValuePair(), "i3=0x1234" );
    EXPECT_TRUE( i3.isHex() );
    EXPECT_TRUE( i3.isSet() );

    DataVariant i4("i4=0xffff") ;
    EXPECT_EQ( i4.getName(), "i4" );
    EXPECT_EQ( i4.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( i4.toString(), "0xffff");
    EXPECT_EQ( i4.toInt(), 65535);
    EXPECT_EQ( i4.getNameValuePair(), "i4=0xffff" );
    EXPECT_TRUE( i4.isHex() );
    EXPECT_TRUE( i4.isSet() );

    // error checking
    i2.set("fred") ;
    EXPECT_EQ( i2.getName(), "i2" );
    EXPECT_EQ( i2.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( i2.toString(), "");
    EXPECT_EQ( i2.toInt(), 0);
    EXPECT_EQ( i2.getNameValuePair(), "i2=" );
    EXPECT_FALSE( i2.isHex() );
    EXPECT_FALSE( i2.isSet() );

    i2.set("123.0") ;
    EXPECT_EQ( i2.getName(), "i2" );
    EXPECT_EQ( i2.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( i2.toString(), "");
    EXPECT_EQ( i2.toInt(), 0);
    EXPECT_EQ( i2.getNameValuePair(), "i2=" );
    EXPECT_FALSE( i2.isHex() );
    EXPECT_FALSE( i2.isSet() );

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Float)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariant dvf("fval=-12.0");
    EXPECT_EQ( dvf.getName(), "fval" );
    EXPECT_EQ( dvf.getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( dvf.toString(), "-12.0");
    EXPECT_EQ( dvf.toFloat(), -12.0);
    EXPECT_EQ( dvf.getNameValuePair(), "fval=-12.0" );

    // error checking
    dvf.set("fred") ;
    EXPECT_EQ( dvf.getName(), "fval" );
    EXPECT_EQ( dvf.getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( dvf.toString(), "");
    EXPECT_EQ( dvf.toFloat(), 0.0);
    EXPECT_EQ( dvf.getNameValuePair(), "fval=" );
    EXPECT_FALSE( dvf.isHex() );
    EXPECT_FALSE( dvf.isSet() );

    dvf.set("123") ;
    EXPECT_EQ( dvf.getName(), "fval" );
    EXPECT_EQ( dvf.getType(), Mplane::DataVariantType::Float );
    EXPECT_EQ( dvf.toString(), "123");
    EXPECT_EQ( dvf.toFloat(), 123.0);
    EXPECT_EQ( dvf.getNameValuePair(), "fval=123" );
    EXPECT_FALSE( dvf.isHex() );
    EXPECT_TRUE( dvf.isSet() );

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Bool)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant b1("b1") ;
    EXPECT_EQ( b1.getName(), "b1" );
    EXPECT_EQ( b1.getType(), Mplane::DataVariantType::None );
    EXPECT_EQ( b1.toString(), "");
    EXPECT_EQ( b1.toInt(), 0);
    EXPECT_FALSE( b1.isHex() );
    EXPECT_FALSE( b1.isSet() );

	b1.set("true") ;
    EXPECT_EQ( b1.getType(), Mplane::DataVariantType::Bool );
    EXPECT_EQ( b1.toString(), "true");
    EXPECT_EQ( b1.toInt(), 1);
    EXPECT_EQ( b1.getNameValuePair(), "b1=true" );
    EXPECT_FALSE( b1.isHex() );
    EXPECT_TRUE( b1.isSet() );

	DataVariant b2("b2=true") ;
    EXPECT_EQ( b2.getType(), Mplane::DataVariantType::Bool );
    EXPECT_EQ( b2.toString(), "true");
    EXPECT_EQ( b2.toInt(), 1);
    EXPECT_EQ( b2.getNameValuePair(), "b2=true" );
    EXPECT_FALSE( b2.isHex() );
    EXPECT_TRUE( b2.isSet() );

	DataVariant b3("b3=TRUE") ;
    EXPECT_EQ( b3.getType(), Mplane::DataVariantType::Bool );
    EXPECT_EQ( b3.toString(), "true");
    EXPECT_EQ( b3.toInt(), 1);
    EXPECT_EQ( b3.getNameValuePair(), "b3=true" );
    EXPECT_FALSE( b3.isHex() );
    EXPECT_TRUE( b3.isSet() );

	DataVariant b4("b4=false") ;
    EXPECT_EQ( b4.getType(), Mplane::DataVariantType::Bool );
    EXPECT_EQ( b4.toString(), "false");
    EXPECT_EQ( b4.toInt(), 0);
    EXPECT_EQ( b4.getNameValuePair(), "b4=false" );
    EXPECT_FALSE( b4.isHex() );
    EXPECT_TRUE( b4.isSet() );

	DataVariant b5("b5=FALSE") ;
    EXPECT_EQ( b5.getType(), Mplane::DataVariantType::Bool );
    EXPECT_EQ( b5.toString(), "false");
    EXPECT_EQ( b5.toInt(), 0);
    EXPECT_EQ( b5.getNameValuePair(), "b5=false" );
    EXPECT_FALSE( b5.isHex() );
    EXPECT_TRUE( b5.isSet() );

	DataVariant b6(std::string("b6"), std::string("BOOL")) ;
    EXPECT_EQ( b6.getName(), "b6" );
    EXPECT_EQ( b6.getType(), Mplane::DataVariantType::Bool );
    EXPECT_EQ( b6.getTypeStr(), "BOOL" );
    EXPECT_EQ( b6.toString(), "");
    EXPECT_EQ( b6.toInt(), 0);
    EXPECT_FALSE( b6.isHex() );
    EXPECT_FALSE( b6.isSet() );

    b6.set("false") ;
    EXPECT_EQ( b6.toString(), "false");
    EXPECT_EQ( b6.toInt(), 0);
    EXPECT_EQ( b6.toBool(), false);
    EXPECT_EQ( b6.getNameValuePair(), "b6=false" );
    EXPECT_FALSE( b6.isHex() );
    EXPECT_TRUE( b6.isSet() );

    b6.set("true") ;
    EXPECT_EQ( b6.toString(), "true");
    EXPECT_EQ( b6.toInt(), 1);
    EXPECT_EQ( b6.toBool(), true);
    EXPECT_EQ( b6.getNameValuePair(), "b6=true" );


	DataVariant b7(std::string("b7"), std::string("BOOL(off:on)")) ;
    EXPECT_EQ( b7.getName(), "b7" );
    EXPECT_EQ( b7.getType(), Mplane::DataVariantType::Bool );
    EXPECT_EQ( b7.getTypeStr(), "BOOL(off:on)" );
    EXPECT_EQ( b7.toString(), "");
    EXPECT_EQ( b7.toInt(), 0);
    EXPECT_EQ( b7.toBool(), false);
    EXPECT_FALSE( b7.isHex() );
    EXPECT_FALSE( b7.isSet() );

    b7.set("false") ;
    EXPECT_EQ( b7.toString(), "off");
    EXPECT_EQ( b7.toInt(), 0);
    EXPECT_EQ( b7.toBool(), false);
    EXPECT_EQ( b7.getNameValuePair(), "b7=off" );
    EXPECT_FALSE( b7.isHex() );
    EXPECT_TRUE( b7.isSet() );

    b7.set("true") ;
    EXPECT_EQ( b7.toString(), "on");
    EXPECT_EQ( b7.toInt(), 1);
    EXPECT_EQ( b7.toBool(), true);
    EXPECT_EQ( b7.getNameValuePair(), "b7=on" );

    b7.set("OFF") ;
    EXPECT_EQ( b7.toString(), "off");
    EXPECT_EQ( b7.toInt(), 0);
    EXPECT_EQ( b7.toBool(), false);
    EXPECT_EQ( b7.getNameValuePair(), "b7=off" );

    b7.set("ON") ;
    EXPECT_EQ( b7.toString(), "on");
    EXPECT_EQ( b7.toInt(), 1);
    EXPECT_EQ( b7.toBool(), true);
    EXPECT_EQ( b7.getNameValuePair(), "b7=on" );

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Enum)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant e1(std::string("e1"), std::string("ENUM(LTE5:LTE10:LTE15:LTE20)")) ;
    EXPECT_EQ( e1.getName(), "e1" );
    EXPECT_EQ( e1.getType(), Mplane::DataVariantType::Enum );
    EXPECT_EQ( e1.toString(), "");
    EXPECT_EQ( e1.toInt(), 0);
    EXPECT_FALSE( e1.isHex() );
    EXPECT_FALSE( e1.isSet() );

    e1.set("LTE15") ;
    EXPECT_EQ( e1.toString(), "LTE15");
    EXPECT_EQ( e1.toInt(), 2);
    EXPECT_FALSE( e1.isHex() );
    EXPECT_TRUE( e1.isSet() );

    e1.set("lte20") ;
    EXPECT_EQ( e1.toString(), "LTE20");
    EXPECT_EQ( e1.toInt(), 3);
    EXPECT_FALSE( e1.isHex() );
    EXPECT_TRUE( e1.isSet() );

    e1.set("lte200") ;
    EXPECT_EQ( e1.toString(), "");
    EXPECT_EQ( e1.toInt(), 0);
    EXPECT_FALSE( e1.isHex() );
    EXPECT_FALSE( e1.isSet() );


}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Constructor)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant dv1(DataVariantType::String, "dv1", "astring") ;
	EXPECT_TRUE(dv1.isSet());
	DataVariant dv2(DataVariantType::Int, "dv2", "12") ;
	EXPECT_TRUE(dv2.isSet());
	DataVariant dv3(DataVariantType::Float, "dv3", "12.3") ;
	EXPECT_TRUE(dv3.isSet());
	DataVariant dv4(DataVariantType::Bool, "dv4", "true") ;
	EXPECT_TRUE(dv4.isSet());

	bool exception = false ;
	try {
		DataVariant dv5(DataVariantType::Enum, "dv5", "??") ;
	}
	catch(...)
	{
		std::cout << "Expected exception due to creating ENUM" << std::endl ;
		exception = true ;
	}
	EXPECT_TRUE(exception);
}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Vector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant vec1(std::string("vec1"), std::string("INT[]")) ;
    EXPECT_EQ( vec1.getName(), "vec1" );
    EXPECT_EQ( vec1.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( vec1.toString(), "");
    EXPECT_EQ( vec1.toInt(), 0);
    EXPECT_FALSE( vec1.isHex() );
    EXPECT_FALSE( vec1.isSet() );
    EXPECT_TRUE( vec1.isVector() );
    EXPECT_EQ( 1u, vec1.size() );

    // set element 0
    vec1.set(0u, 100) ;

    // wrapper matches [0]
    EXPECT_EQ( vec1.getName(), "vec1" );
    EXPECT_EQ( vec1.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( vec1.toString(), "100");
    EXPECT_EQ( vec1.toInt(), 100);
    EXPECT_FALSE( vec1.isHex() );
    EXPECT_TRUE( vec1.isSet() );
    EXPECT_TRUE( vec1.isVector() );
    EXPECT_EQ( 1u, vec1.size() );

    std::vector< std::pair<std::string, DataVariant> > list(vec1.getList()) ;
    EXPECT_TRUE( list.size() == 1u) ;
    EXPECT_EQ(std::string("vec1[0]"), list[0].first) ;
    DataVariant dv(list[0].second) ;
    EXPECT_EQ( dv.getName(), "vec1" );
    EXPECT_EQ( dv.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( dv.toString(), "100");
    EXPECT_EQ( dv.toInt(), 100);
    EXPECT_FALSE( dv.isHex() );
    EXPECT_TRUE( dv.isSet() );
    EXPECT_FALSE( dv.isVector() );


    // set element 2
    vec1.set(2u, 300) ;

    // wrapper matches [0]
    EXPECT_EQ( vec1.getName(), "vec1" );
    EXPECT_EQ( vec1.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( vec1.toString(), "100");
    EXPECT_EQ( vec1.toInt(), 100);
    EXPECT_FALSE( vec1.isHex() );
    EXPECT_TRUE( vec1.isSet() );
    EXPECT_TRUE( vec1.isVector() );
    EXPECT_EQ( 3u, vec1.size() );

    list = vec1.getList() ;
    EXPECT_TRUE( list.size() == 3u) ;

    dv = list[0].second ;
    EXPECT_EQ(std::string("vec1[0]"), list[0].first) ;
    EXPECT_EQ( dv.getName(), "vec1" );
    EXPECT_EQ( dv.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( dv.toString(), "100");
    EXPECT_EQ( dv.toInt(), 100);
    EXPECT_FALSE( dv.isHex() );
    EXPECT_TRUE( dv.isSet() );
    EXPECT_FALSE( dv.isVector() );

    // this will be an empty DataVariant of the same type
    dv = list[1].second ;
    EXPECT_EQ(std::string("vec1[1]"), list[1].first) ;
    EXPECT_EQ( "vec1", dv.getName() );
    EXPECT_EQ( Mplane::DataVariantType::Int, dv.getType() );
    EXPECT_EQ( dv.toString(), "");
    EXPECT_EQ( dv.toInt(), 0);
    EXPECT_FALSE( dv.isHex() );
    EXPECT_FALSE( dv.isSet() );
    EXPECT_FALSE( dv.isVector() );

    dv = list[2].second ;
    EXPECT_EQ(std::string("vec1[2]"), list[2].first) ;
    EXPECT_EQ( dv.getName(), "vec1" );
    EXPECT_EQ( dv.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( dv.toString(), "300");
    EXPECT_EQ( dv.toInt(), 300);
    EXPECT_FALSE( dv.isHex() );
    EXPECT_TRUE( dv.isSet() );
    EXPECT_FALSE( dv.isVector() );


    // get string
    EXPECT_EQ(std::string("vec1[0]=100 vec1[1]= vec1[2]=300"), vec1.getNameValuePair()) ;

    // change names
    vec1.setName(0u, "first") ;
    vec1.setName(1u, "second") ;
    vec1.setName(2u, "third") ;
    EXPECT_EQ(std::string("first=100 second= third=300"), vec1.getNameValuePair()) ;

    // Units
	DataVariantList dlist("FLOAT[] vec2 (kHz)") ;
	DataVariant* vec2(dlist.find("vec2")) ;
	EXPECT_EQ("kHz", vec2->getUnits()) ;
	vec2->set(0u, 1234.5f) ;
	vec2->set(2u, 567.8f) ;

	list = vec2->getList() ;
	dv = list[0].second ;
	EXPECT_EQ("kHz", dv.getUnits()) ;
	dv = list[2].second ;
	EXPECT_EQ("kHz", dv.getUnits()) ;


}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, VectorCopy)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant vec1(std::string("vec1"), std::string("INT[]")) ;
    vec1.set(0u, 100) ;
    vec1.set(2u, 300) ;
    vec1.setName(0u, "first") ;
    vec1.setName(1u, "second") ;
    vec1.setName(2u, "third") ;
    EXPECT_EQ(std::string("first=100 second= third=300"), vec1.getNameValuePair()) ;
    EXPECT_TRUE( vec1.isVector() );

    DataVariant vec2 ;
    vec2 = vec1 ;
    EXPECT_EQ(std::string("first=100 second= third=300"), vec2.getNameValuePair()) ;
    EXPECT_TRUE( vec2.isVector() );

    DataVariant vec3 ;
    vec3.set(vec1) ;
    EXPECT_EQ(std::string("first=100 second= third=300"), vec3.getNameValuePair()) ;
    EXPECT_TRUE( vec3.isVector() );

    DataVariant* vecp = &vec1 ;
    DataVariant vec4 ;
    vec4.set(vecp) ;
    EXPECT_EQ(std::string("first=100 second= third=300"), vec4.getNameValuePair()) ;
    EXPECT_TRUE( vec4.isVector() );

    std::shared_ptr<DataVariant> vecsp( new DataVariant(std::string("vec1"), std::string("INT[]")) ) ;
    vecsp->set(0u, 10) ;
    vecsp->set(1u, 20) ;
    vecsp->setName(0u, "aa") ;
    vecsp->setName(1u, "bb") ;
    EXPECT_EQ(std::string("aa=10 bb=20"), vecsp->getNameValuePair()) ;

    DataVariant vec5 ;
    vec5.set(vecsp) ;
    EXPECT_EQ(std::string("aa=10 bb=20"), vec5.getNameValuePair()) ;
    EXPECT_TRUE( vec5.isVector() );

    // change value
    vec5 = vec1 ;
    EXPECT_EQ(std::string("first=100 second= third=300"), vec5.getNameValuePair()) ;
    EXPECT_TRUE( vec5.isVector() );

    // change from an array to a single value
    DataVariant dv(std::string("b6"), std::string("BOOL")) ;
    dv.set("true");
    vec5 = dv ;
    EXPECT_FALSE( vec5.isVector() );
    EXPECT_EQ(std::string("b6=true"), vec5.getNameValuePair()) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, BaseCopy)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantBase base1(std::string("base1"), std::string("INT")) ;
    base1.setInt(100) ;
    EXPECT_EQ(std::string("base1=100"), base1.getNameValuePair()) ;

    DataVariantBase base2 ;
    base2 = base1 ;
    EXPECT_EQ(std::string("base1=100"), base1.getNameValuePair()) ;

    DataVariantBase base3 ;
    base3.set(base1) ;
    EXPECT_EQ(std::string("base1=100"), base1.getNameValuePair()) ;

    DataVariantBase* basep = &base1 ;
    DataVariantBase base4 ;
    base4.set(basep) ;
    EXPECT_EQ(std::string("base1=100"), base1.getNameValuePair()) ;

    std::shared_ptr<DataVariantBase> basesp( new DataVariantBase(std::string("basep"), std::string("INT")) ) ;
    basesp->setInt(10) ;
    EXPECT_EQ(std::string("basep=10"), basesp->getNameValuePair()) ;

    DataVariantBase base5 ;
    base5.set(basesp) ;
    EXPECT_EQ(std::string("basep=10"), base5.getNameValuePair()) ;

    // change value
    base5 = base1 ;
    EXPECT_EQ(std::string("base1=100"), base5.getNameValuePair()) ;

    // change type/name
    DataVariantBase dv(std::string("b6"), std::string("BOOL")) ;
    dv.set("true");
    base5 = dv ;
    EXPECT_EQ(std::string("b6=true"), base5.getNameValuePair()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Units)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant dv1(std::string("dv1"), std::string("INT")) ;
	EXPECT_EQ("dv1=", dv1.getNameValuePair()) ;

	dv1.setInt(123) ;
	EXPECT_EQ("dv1=123", dv1.getNameValuePair()) ;

	dv1.setUnits("kHz") ;
	EXPECT_EQ(123, dv1.toInt()) ;
	EXPECT_EQ("kHz", dv1.getUnits()) ;
	EXPECT_EQ("123", dv1.toString()) ;
	EXPECT_EQ("dv1=123kHz", dv1.getNameValuePair()) ;

	// set value with new units
	dv1.set("345Hz") ;
	EXPECT_EQ("dv1=345Hz", dv1.getNameValuePair()) ;
	EXPECT_EQ(345, dv1.toInt()) ;
	EXPECT_EQ("345", dv1.toString()) ;
	EXPECT_EQ("Hz", dv1.getUnits()) ;

	DataVariant dvf(std::string("dvf"), std::string("INT kHz")) ;
    EXPECT_EQ( dvf.getName(), "dvf" );
    EXPECT_EQ( dvf.getType(), Mplane::DataVariantType::Int );
    EXPECT_EQ( dvf.toString(), "");
    EXPECT_EQ( dvf.toInt(), 0);
    EXPECT_FALSE( dvf.isHex() );
    EXPECT_FALSE( dvf.isSet() );
	EXPECT_EQ("kHz", dvf.getUnits()) ;
	dvf.setInt(123) ;
	EXPECT_EQ("dvf=123kHz", dvf.getNameValuePair()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Limits)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    DataVariant vi(DataVariantType::Float, "vi", "1.0");
    EXPECT_EQ( vi.getName(), "vi" );
    EXPECT_TRUE(vi.setLimits("0.0..10.0")) ;
    EXPECT_TRUE(vi.checkLimits()) ;
    vi.set("20.0") ;
    EXPECT_FALSE(vi.checkLimits()) ;
    vi.set("-1.0") ;
    EXPECT_FALSE(vi.checkLimits()) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Complex)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariant dvc("complex=-12+j1e3");
    EXPECT_EQ( dvc.getName(), "complex" );
    EXPECT_EQ( dvc.getType(), Mplane::DataVariantType::Complex );
    EXPECT_EQ( dvc.toString(), "-12+j1e3");
    EXPECT_EQ( -12, dvc.toInt() );
    EXPECT_EQ( "complex=-12+j1e3", dvc.getNameValuePair() );
    EXPECT_FLOAT_EQ(-12.0, dvc.toComplex().real()) ;
    EXPECT_FLOAT_EQ(1000.0, dvc.toComplex().imag()) ;

    DataVariant c2("c2") ;
    c2.set("1.2-j3.4") ;
    EXPECT_EQ( c2.getName(), "c2" );
    EXPECT_EQ( c2.getType(), Mplane::DataVariantType::Complex );
    EXPECT_EQ( c2.toString(), "1.2-j3.4");
    EXPECT_EQ( c2.toInt(), 1);
    EXPECT_EQ( c2.getNameValuePair(), "c2=1.2-j3.4" );
    EXPECT_FALSE( c2.isHex() );
    EXPECT_TRUE( c2.isSet() );

    c2.set(std::complex<float>(5.6,-7.8)) ;
    EXPECT_EQ( c2.getName(), "c2" );
    EXPECT_EQ( c2.getType(), Mplane::DataVariantType::Complex );
    EXPECT_EQ( c2.toString(), "5.6-j7.8");
    EXPECT_EQ( c2.toInt(), 5);
    EXPECT_EQ( c2.getNameValuePair(), "c2=5.6-j7.8" );
    EXPECT_FALSE( c2.isHex() );
    EXPECT_TRUE( c2.isSet() );

//    i2.set("1234") ;
//    EXPECT_EQ( i2.getName(), "i2" );
//    EXPECT_EQ( i2.getType(), Mplane::DataVariantType::Int );
//    EXPECT_EQ( i2.toString(), "1234");
//    EXPECT_EQ( i2.toInt(), 1234);
//    EXPECT_EQ( i2.getNameValuePair(), "i2=1234" );
//    EXPECT_FALSE( i2.isHex() );
//    EXPECT_TRUE( i2.isSet() );
//
//    DataVariant i3("i3=0x1234") ;
//    EXPECT_EQ( i3.getName(), "i3" );
//    EXPECT_EQ( i3.getType(), Mplane::DataVariantType::Int );
//    EXPECT_EQ( i3.toString(), "0x1234");
//    EXPECT_EQ( i3.toInt(), 4660);
//    EXPECT_EQ( i3.getNameValuePair(), "i3=0x1234" );
//    EXPECT_TRUE( i3.isHex() );
//    EXPECT_TRUE( i3.isSet() );
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Long)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    DataVariant vf(DataVariantType::Float, "vf", "6307200010.0");
    DataVariant vi(DataVariantType::Int, "vi", "6307200000");

    std::cerr << "Float=" << std::fixed << vf.toFloat() << std::endl ;
    std::cerr << "Int=" << vi.toInt() << std::endl ;

}

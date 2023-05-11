/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantBase_unittest.cpp
 * \brief     Google Test of DataVariantBase
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the DataVariantBase class.
 *
 */

#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "DataVariantBase.h"

using namespace Mplane;

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Basic)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

    DataVariantBase vi("vi");
    DataVariantBase viA("viA","12");
    DataVariantBase* viB = new DataVariantBase("viB","this");
    std::shared_ptr<DataVariantBase> viC(new DataVariantBase(DataVariantType::Int, "viC", "16384"));

    EXPECT_EQ( vi.getName(), "vi" );

    vi.set(viA) ;
    EXPECT_EQ( vi.getName(), "viA" );

    vi.set(viB) ;
    EXPECT_EQ( vi.getName(), "viB" );

    vi.set(viC) ;
    EXPECT_EQ( vi.getName(), "viC" );



    delete( viB );
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Int)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dvi("integer=-12");
    EXPECT_EQ( dvi.getName(), "integer" );
    EXPECT_EQ( dvi.getType(), DataVariantType::Int );
    EXPECT_EQ( dvi.toString(), "-12");
    EXPECT_EQ( dvi.toInt(), -12);
    EXPECT_EQ( dvi.getNameValuePair(), "integer=-12" );

    DataVariantBase i2("i2") ;
    i2.set("0x1234") ;
    EXPECT_EQ( i2.getName(), "i2" );
    EXPECT_EQ( i2.getType(), DataVariantType::Int );
    EXPECT_EQ( i2.toString(), "0x1234");
    EXPECT_EQ( i2.toInt(), 4660);
    EXPECT_EQ( i2.getNameValuePair(), "i2=0x1234" );
    EXPECT_TRUE( i2.isHex() );
    EXPECT_TRUE( i2.isSet() );

    i2.set("1234") ;
    EXPECT_EQ( i2.getName(), "i2" );
    EXPECT_EQ( i2.getType(), DataVariantType::Int );
    EXPECT_EQ( i2.toString(), "1234");
    EXPECT_EQ( i2.toInt(), 1234);
    EXPECT_EQ( i2.getNameValuePair(), "i2=1234" );
    EXPECT_FALSE( i2.isHex() );
    EXPECT_TRUE( i2.isSet() );

    DataVariantBase i3("i3=0x1234") ;
    EXPECT_EQ( i3.getName(), "i3" );
    EXPECT_EQ( i3.getType(), DataVariantType::Int );
    EXPECT_EQ( i3.toString(), "0x1234");
    EXPECT_EQ( i3.toInt(), 4660);
    EXPECT_EQ( i3.getNameValuePair(), "i3=0x1234" );
    EXPECT_TRUE( i3.isHex() );
    EXPECT_TRUE( i3.isSet() );

    DataVariantBase i4("i4=0xffff") ;
    EXPECT_EQ( i4.getName(), "i4" );
    EXPECT_EQ( i4.getType(), DataVariantType::Int );
    EXPECT_EQ( i4.toString(), "0xffff");
    EXPECT_EQ( i4.toInt(), 65535);
    EXPECT_EQ( i4.getNameValuePair(), "i4=0xffff" );
    EXPECT_TRUE( i4.isHex() );
    EXPECT_TRUE( i4.isSet() );

    // error checking
    i2.set("fred") ;
    EXPECT_EQ( i2.getName(), "i2" );
    EXPECT_EQ( i2.getType(), DataVariantType::Int );
    EXPECT_EQ( i2.toString(), "");
    EXPECT_EQ( i2.toInt(), 0);
    EXPECT_EQ( i2.getNameValuePair(), "i2=" );
    EXPECT_FALSE( i2.isHex() );
    EXPECT_FALSE( i2.isSet() );

    i2.set("123.0") ;
    EXPECT_EQ( i2.getName(), "i2" );
    EXPECT_EQ( i2.getType(), DataVariantType::Int );
    EXPECT_EQ( i2.toString(), "");
    EXPECT_EQ( i2.toInt(), 0);
    EXPECT_EQ( i2.getNameValuePair(), "i2=" );
    EXPECT_FALSE( i2.isHex() );
    EXPECT_FALSE( i2.isSet() );

    // units
    DataVariantBase i5("i5") ;
    i5.setInt(1234) ;
	i5.setUnits("kHz") ;
    EXPECT_EQ( i5.toString(), "1234");
    EXPECT_EQ( i5.toInt(), 1234);
    EXPECT_EQ( i5.getNameValuePair(), "i5=1234kHz" );
    i5.set("5678Hz") ;
    EXPECT_EQ( i5.toString(), "5678");
    EXPECT_EQ( i5.toInt(), 5678);
    EXPECT_EQ( i5.getNameValuePair(), "i5=5678Hz" );


}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Float)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dvf("fval=-12.0");
    EXPECT_EQ( dvf.getName(), "fval" );
    EXPECT_EQ( dvf.getType(), DataVariantType::Float );
    EXPECT_EQ( dvf.toString(), "-12.0");
    EXPECT_EQ( dvf.toFloat(), -12.0);
    EXPECT_EQ( dvf.getNameValuePair(), "fval=-12.0" );

    // error checking
    dvf.set("fred") ;
    EXPECT_EQ( dvf.getName(), "fval" );
    EXPECT_EQ( dvf.getType(), DataVariantType::Float );
    EXPECT_EQ( dvf.toString(), "");
    EXPECT_FLOAT_EQ( dvf.toFloat(), 0.0);
    EXPECT_EQ( dvf.getNameValuePair(), "fval=" );
    EXPECT_FALSE( dvf.isHex() );
    EXPECT_FALSE( dvf.isSet() );

    dvf.set("123") ;
    EXPECT_EQ( dvf.getName(), "fval" );
    EXPECT_EQ( dvf.getType(), DataVariantType::Float );
    EXPECT_EQ( dvf.toString(), "123");
    EXPECT_FLOAT_EQ( dvf.toFloat(), 123.0);
    EXPECT_EQ( dvf.getNameValuePair(), "fval=123" );
    EXPECT_FALSE( dvf.isHex() );
    EXPECT_TRUE( dvf.isSet() );

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, String)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dvs(DataVariantType::String, "dvs", "1234");
    EXPECT_EQ( dvs.getName(), "dvs" );
    EXPECT_EQ( dvs.getType(), DataVariantType::String );
    EXPECT_EQ( dvs.toString(), "1234");
    EXPECT_EQ( 1234, dvs.toInt() );
    EXPECT_EQ( "dvs=\"1234\"", dvs.getNameValuePair() );
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Complex)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dvc("complex=-12+j1e3");
    EXPECT_EQ( dvc.getName(), "complex" );
    EXPECT_EQ( dvc.getType(), DataVariantType::Complex );
    EXPECT_EQ( dvc.toString(), "-12+j1e3");
    EXPECT_EQ( -12, dvc.toInt() );
    EXPECT_EQ( "complex=-12+j1e3", dvc.getNameValuePair() );
    EXPECT_FLOAT_EQ(-12.0, dvc.toComplex().real()) ;
    EXPECT_FLOAT_EQ(1000.0, dvc.toComplex().imag()) ;

    DataVariantBase c2("c2") ;
    c2.set("1.2-j3.4") ;
    EXPECT_EQ( c2.getName(), "c2" );
    EXPECT_EQ( c2.getType(), DataVariantType::Complex );
    EXPECT_EQ( c2.toString(), "1.2-j3.4");
    EXPECT_EQ( c2.toInt(), 1);
    EXPECT_EQ( c2.getNameValuePair(), "c2=1.2-j3.4" );
    EXPECT_FALSE( c2.isHex() );
    EXPECT_TRUE( c2.isSet() );

    c2.setComplex(std::complex<float>(5.6,-7.8)) ;
    EXPECT_EQ( c2.getName(), "c2" );
    EXPECT_EQ( c2.getType(), DataVariantType::Complex );
    EXPECT_EQ( c2.toString(), "5.6-j7.8");
    EXPECT_EQ( c2.toInt(), 5);
    EXPECT_EQ( c2.getNameValuePair(), "c2=5.6-j7.8" );
    EXPECT_FALSE( c2.isHex() );
    EXPECT_TRUE( c2.isSet() );
}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Convert)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dvf("fval=-12.3");
    EXPECT_EQ( dvf.getType(), DataVariantType::Float );
    EXPECT_EQ( dvf.toString(), "-12.3");
    EXPECT_FLOAT_EQ( -12.3, dvf.toFloat());
    EXPECT_EQ( dvf.toInt(), -12);

    DataVariantBase dvi("integer=25");
    EXPECT_EQ( dvi.getType(), DataVariantType::Int );
    EXPECT_EQ( dvi.toString(), "25");
    EXPECT_EQ( dvi.toFloat(), 25.0);

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Freq)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dvf(DataVariantType::Freq, "fval", "5123456789");
    EXPECT_EQ( "fval", dvf.getName() );
    EXPECT_EQ( DataVariantType::Freq, dvf.getType() );
    EXPECT_EQ( "5123456789", dvf.toString() );
//    EXPECT_FLOAT_EQ( 5123456789.0, dvf.toFloat() );
    EXPECT_EQ( Frequency(5123456789.0), dvf.toFreq() );
    EXPECT_EQ( "fval=5123456789", dvf.getNameValuePair() );

    // Freq with units - value is always relative to the current units
	dvf.setUnits("Hz") ;
    dvf.set("200KHz") ;
    EXPECT_EQ( "fval", dvf.getName() );
    EXPECT_EQ( DataVariantType::Freq, dvf.getType() );
    EXPECT_EQ( "200", dvf.toString() );
    EXPECT_FLOAT_EQ( 200.0, dvf.toFloat() );
    EXPECT_EQ( Frequency(200.0, Frequency::KHz), dvf.toFreq() );
    EXPECT_FLOAT_EQ( dvf.toFloat(), dvf.toFreq().getDbl(Frequency::str2unit(dvf.getUnits())) );
    EXPECT_EQ( "fval=200KHz", dvf.getNameValuePair() );

	dvf.setUnits("Hz") ;
    EXPECT_EQ( "200000", dvf.toString() );
    EXPECT_FLOAT_EQ( 200000.0, dvf.toFloat() );
    dvf.setInt(123000) ;
    EXPECT_EQ( "123000", dvf.toString() );
    EXPECT_FLOAT_EQ( 123000.0, dvf.toFloat() );

	dvf.setUnits("KHz") ;
    EXPECT_EQ( "123", dvf.toString() );
    EXPECT_FLOAT_EQ( 123.0, dvf.toFloat() );
    EXPECT_EQ( Frequency(123.0, Frequency::KHz), dvf.toFreq() );
    dvf.set("456") ;
    EXPECT_EQ( Frequency(456.0, Frequency::KHz), dvf.toFreq() );

    dvf.setFloat(345.0) ;
    EXPECT_EQ( "345", dvf.toString() );
    EXPECT_FLOAT_EQ( 345.0, dvf.toFloat() );
    EXPECT_EQ( "fval=345KHz", dvf.getNameValuePair() );

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Uint)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dv(DataVariantType::Uint, "val", "4294967295");
    EXPECT_EQ( "val", dv.getName() );
    EXPECT_EQ( DataVariantType::Uint, dv.getType() );
    EXPECT_EQ( "4294967295", dv.toString() );
    EXPECT_EQ( "val=4294967295", dv.getNameValuePair() );
    EXPECT_EQ( 4294967295U, dv.toUint() ) ;
    EXPECT_TRUE(dv.isSet()) ;

    dv.set("-1") ;
    EXPECT_FALSE(dv.isSet()) ;
    EXPECT_EQ( "val=", dv.getNameValuePair() );

    dv.setUint(3294967295) ;
    EXPECT_TRUE(dv.isSet()) ;
    EXPECT_EQ( "val=3294967295", dv.getNameValuePair() );
    EXPECT_EQ( 3294967295U, dv.toUint() ) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Long)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dv(DataVariantType::Long, "val", "4294967295");
    EXPECT_EQ( "val", dv.getName() );
    EXPECT_EQ( DataVariantType::Long, dv.getType() );
    EXPECT_EQ( "4294967295", dv.toString() );
    EXPECT_EQ( "val=4294967295", dv.getNameValuePair() );
    EXPECT_EQ( 4294967295LL, dv.toLong() ) ;
    EXPECT_TRUE(dv.isSet()) ;

    dv.set("-1") ;
    EXPECT_TRUE(dv.isSet()) ;
    EXPECT_EQ( "val=-1", dv.getNameValuePair() );

    dv.set("5123456789") ;
    EXPECT_TRUE(dv.isSet()) ;
    EXPECT_EQ( "val=5123456789", dv.getNameValuePair() );
    EXPECT_EQ( 5123456789LL, dv.toLong() ) ;

    dv.setLong(15123456789LL) ;
    EXPECT_TRUE(dv.isSet()) ;
    EXPECT_EQ( "val=15123456789", dv.getNameValuePair() );
    EXPECT_EQ( 15123456789LL, dv.toLong() ) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Double)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dv(DataVariantType::Double, "val", "5123456789.0123");
    EXPECT_EQ( "val", dv.getName() );
    EXPECT_EQ( DataVariantType::Double, dv.getType() );
    EXPECT_EQ( "5123456789.0123", dv.toString() );
    EXPECT_EQ( "val=5123456789.0123", dv.getNameValuePair() );
    EXPECT_DOUBLE_EQ( 5123456789.0123, dv.toDouble() ) ;
    EXPECT_TRUE(dv.isSet()) ;

    dv.set("-1") ;
    EXPECT_TRUE(dv.isSet()) ;
    EXPECT_EQ( "val=-1", dv.getNameValuePair() );

    dv.set("5123456789") ;
    EXPECT_TRUE(dv.isSet()) ;
    EXPECT_EQ( "val=5123456789", dv.getNameValuePair() );

    dv.setDouble(15123456789.0123) ;
    EXPECT_TRUE(dv.isSet()) ;
    EXPECT_EQ( "val=15123456789.0123", dv.getNameValuePair() );
    EXPECT_DOUBLE_EQ( 15123456789.0123, dv.toDouble() ) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantBase, Power)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;


    DataVariantBase dv(DataVariantType::Power, "val", "33.5");
    EXPECT_EQ( "val", dv.getName() );
    EXPECT_EQ( DataVariantType::Power, dv.getType() );
    EXPECT_EQ( "33.5", dv.toString() );
    EXPECT_FLOAT_EQ( 33.5, dv.toFloat() );
    EXPECT_EQ( Power(33.5), dv.toPower() );

//    std::cerr << "Power = " << dv.toPower() << std::endl ;

    // Power with units - value is always relative to the current units
	dv.setUnits("dB") ;
    EXPECT_EQ( "val", dv.getName() );
    EXPECT_EQ( DataVariantType::Power, dv.getType() );
    EXPECT_EQ( "33.5", dv.toString() );
    EXPECT_FLOAT_EQ( 33.5, dv.toFloat() );
    EXPECT_EQ( Power(33.5, Power::dBm), dv.toPower() );
    EXPECT_FLOAT_EQ( dv.toFloat(), dv.toPower().get(Power::str2unit(dv.getUnits())) );
    EXPECT_EQ( "val=33.5dB", dv.getNameValuePair() );

    dv.setUnits("W") ;
    EXPECT_EQ( "2.238721", dv.toString() );
    EXPECT_FLOAT_EQ( 2.2387207, dv.toFloat() );
//    std::cerr << "Power (W) = " << dv.toPower() << std::endl ;

    dv.setUnits("TdBm") ;
    EXPECT_EQ( "335", dv.toString() );
    EXPECT_FLOAT_EQ( 335.0, dv.toFloat() );
    EXPECT_FLOAT_EQ( dv.toFloat(), dv.toPower().get(Power::str2unit(dv.getUnits())) );

    dv.setUnits("mW") ;
    EXPECT_EQ( "2238.720703", dv.toString() );
    EXPECT_FLOAT_EQ( 2238.720703, dv.toFloat() );
    EXPECT_EQ( Power(33.5, Power::dB), dv.toPower() );

    dv.setUnits("dB") ;
    EXPECT_EQ( "33.5", dv.toString() );
    EXPECT_FLOAT_EQ( 33.5, dv.toFloat() );
    EXPECT_FLOAT_EQ( dv.toFloat(), dv.toPower().get(Power::str2unit(dv.getUnits())) );
    EXPECT_EQ( Power(33.5, Power::dB), dv.toPower() );

    dv.setUnits("dBFS") ;
    EXPECT_EQ( "33.5", dv.toString() );
    EXPECT_FLOAT_EQ( 33.5, dv.toFloat() );
    EXPECT_FLOAT_EQ( dv.toFloat(), dv.toPower().get(Power::str2unit(dv.getUnits())) );
    EXPECT_EQ( Power(33.5, Power::dB), dv.toPower() );

}

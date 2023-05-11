/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantVector_unittest.cpp
 * \brief     Google Test of DataVariantVector
 *
 *
 * \details   This file contains the implementation of the Google Test test cases
 *            for the DataVariantVector class.
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
TEST(DataVariantVector, IntVector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant vec1(std::string("vec1"), std::string("INT[]")) ;
    vec1.set(0u, 100) ;
    vec1.set(2u, 300) ;
    EXPECT_EQ(std::string("vec1[0]=100 vec1[1]= vec1[2]=300"), vec1.getNameValuePair()) ;

    std::string error ;
    EXPECT_FALSE(DataVariantVector::isVectorComplete(vec1, error)) ;
    EXPECT_EQ("Value vec1[1] is unset", error) ;

    error="" ;
    std::vector<int> intList1(DataVariantVector::toIntVector(vec1, error)) ;
    EXPECT_EQ(0u, intList1.size()) ;

    vec1.set(1u, 200) ;
    EXPECT_TRUE(DataVariantVector::isVectorComplete(vec1, error)) ;
    EXPECT_EQ("", error) ;

    std::vector<int> intList2(DataVariantVector::toIntVector(vec1, error)) ;
    EXPECT_EQ(3u, intList2.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(100, intList2[0]) ;
    EXPECT_EQ(200, intList2[1]) ;
    EXPECT_EQ(300, intList2[2]) ;

    // change names
    vec1.setName(0u, "first") ;
    vec1.setName(1u, "second") ;
    vec1.setName(2u, "third") ;

    std::vector<int> intList3(DataVariantVector::toIntVector(vec1, error)) ;
    EXPECT_EQ(3u, intList3.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(100, intList3[0]) ;
    EXPECT_EQ(200, intList3[1]) ;
    EXPECT_EQ(300, intList3[2]) ;

    // Set DV from vector
    std::vector<int> intList4{-1, -2, -3, -4} ;
    EXPECT_TRUE(DataVariantVector::fromIntVector(intList4, vec1, error)) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(std::string("first=-1 second=-2 third=-3 vec1[3]=-4"), vec1.getNameValuePair()) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantVector, UnsignedVector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant vec1(std::string("vec1"), std::string("INT[]")) ;
    vec1.set(0u, 100) ;
    vec1.set(2u, 300) ;
    EXPECT_EQ(std::string("vec1[0]=100 vec1[1]= vec1[2]=300"), vec1.getNameValuePair()) ;

    std::string error ;
    EXPECT_FALSE(DataVariantVector::isVectorComplete(vec1, error)) ;
    EXPECT_EQ("Value vec1[1] is unset", error) ;

    error="" ;
    std::vector<unsigned> unsignedList1(DataVariantVector::toUnsignedVector(vec1, error)) ;
    EXPECT_EQ(0u, unsignedList1.size()) ;

    vec1.set(1u, 200) ;
    EXPECT_TRUE(DataVariantVector::isVectorComplete(vec1, error)) ;
    EXPECT_EQ("", error) ;

    std::vector<unsigned> unsignedList2(DataVariantVector::toUnsignedVector(vec1, error)) ;
    EXPECT_EQ(3u, unsignedList2.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(100u, unsignedList2[0]) ;
    EXPECT_EQ(200u, unsignedList2[1]) ;
    EXPECT_EQ(300u, unsignedList2[2]) ;

    // change names
    vec1.setName(0u, "first") ;
    vec1.setName(1u, "second") ;
    vec1.setName(2u, "third") ;

    std::vector<unsigned> unsignedList3(DataVariantVector::toUnsignedVector(vec1, error)) ;
    EXPECT_EQ(3u, unsignedList3.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(100u, unsignedList3[0]) ;
    EXPECT_EQ(200u, unsignedList3[1]) ;
    EXPECT_EQ(300u, unsignedList3[2]) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantVector, FloatVector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("FLOAT[] vec1") ;
	DataVariant* vec1(dlist.find("vec1")) ;
    vec1->set(0u, 100.0f) ;
    vec1->set(2u, 300.0f) ;

    std::string error ;
    EXPECT_FALSE(DataVariantVector::isVectorComplete(*vec1, error)) ;
    EXPECT_EQ("Value vec1[1] is unset", error) ;

    error="" ;
    std::vector<float> floatList1(DataVariantVector::toFloatVector(*vec1, error)) ;
    EXPECT_EQ(0u, floatList1.size()) ;

    vec1->set(1u, 200.0f) ;
    EXPECT_TRUE(DataVariantVector::isVectorComplete(*vec1, error)) ;
    EXPECT_EQ("", error) ;

    std::vector<float> floatList2(DataVariantVector::toFloatVector(*vec1, error)) ;
    EXPECT_EQ(3u, floatList2.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_FLOAT_EQ(100.0f, floatList2[0]) ;
    EXPECT_FLOAT_EQ(200.0f, floatList2[1]) ;
    EXPECT_FLOAT_EQ(300.0f, floatList2[2]) ;

    // change names
    vec1->setName(0u, "first") ;
    vec1->setName(1u, "second") ;
    vec1->setName(2u, "third") ;

    std::vector<float> floatList3(DataVariantVector::toFloatVector(*vec1, error)) ;
    EXPECT_EQ(3u, floatList3.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_FLOAT_EQ(100.0f, floatList3[0]) ;
    EXPECT_FLOAT_EQ(200.0f, floatList3[1]) ;
    EXPECT_FLOAT_EQ(300.0f, floatList3[2]) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantVector, FreqVector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("FLOAT[] vec1 (kHz)") ;
	DataVariant* vec1(dlist.find("vec1")) ;
	EXPECT_EQ("kHz", vec1->getUnits()) ;
    vec1->set(0u, 700000.0f) ;
    vec1->set(2u, 2355000.0f) ;

    std::string error ;
    EXPECT_FALSE(DataVariantVector::isVectorComplete(*vec1, error)) ;
    EXPECT_EQ("Value vec1[1] is unset", error) ;

    error="" ;
    std::vector<Frequency> freqList1(DataVariantVector::toFrequencyVector(*vec1, error)) ;
    EXPECT_EQ(0u, freqList1.size()) ;

    vec1->set(1u, 2345000.0f) ;
    EXPECT_TRUE(DataVariantVector::isVectorComplete(*vec1, error)) ;
    EXPECT_EQ("", error) ;

    std::vector<Frequency> freqList2(DataVariantVector::toFrequencyVector(*vec1, error)) ;
    EXPECT_EQ(3u, freqList2.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(700000u, freqList2[0].getUint(Frequency::KHz)) ;
    EXPECT_EQ(2345000u, freqList2[1].getUint(Frequency::KHz)) ;
    EXPECT_EQ(2355000u, freqList2[2].getUint(Frequency::KHz)) ;

    // change names
    vec1->setName(0u, "first") ;
    vec1->setName(1u, "second") ;
    vec1->setName(2u, "third") ;

    std::vector<Frequency> freqList3(DataVariantVector::toFrequencyVector(*vec1, error)) ;
    EXPECT_EQ(3u, freqList3.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(700000u, freqList3[0].getUint(Frequency::KHz)) ;
    EXPECT_EQ(2345000u, freqList3[1].getUint(Frequency::KHz)) ;
    EXPECT_EQ(2355000u, freqList3[2].getUint(Frequency::KHz)) ;

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantVector, PowerVector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariantList dlist("FLOAT[] vec1 (dB)") ;
	DataVariant* vec1(dlist.find("vec1")) ;
	EXPECT_EQ("dB", vec1->getUnits()) ;
    vec1->set(0u, 35.0f) ;
    vec1->set(2u, 40.0f) ;

    std::string error ;
    EXPECT_FALSE(DataVariantVector::isVectorComplete(*vec1, error)) ;
    EXPECT_EQ("Value vec1[1] is unset", error) ;

    error="" ;
    std::vector<Power> powerList1(DataVariantVector::toPowerVector(*vec1, error)) ;
    EXPECT_EQ(0u, powerList1.size()) ;

    vec1->set(1u, 37.0f) ;
    EXPECT_TRUE(DataVariantVector::isVectorComplete(*vec1, error)) ;
    EXPECT_EQ("", error) ;

    std::vector<Power> powerList2(DataVariantVector::toPowerVector(*vec1, error)) ;
    EXPECT_EQ(3u, powerList2.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(35, powerList2[0].getInt()) ;
    EXPECT_EQ(37, powerList2[1].getInt()) ;
    EXPECT_EQ(40, powerList2[2].getInt()) ;

    // change names
    vec1->setName(0u, "first") ;
    vec1->setName(1u, "second") ;
    vec1->setName(2u, "third") ;

    std::vector<Power> powerList3(DataVariantVector::toPowerVector(*vec1, error)) ;
    EXPECT_EQ(3u, powerList3.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(35, powerList3[0].getInt()) ;
    EXPECT_EQ(37, powerList3[1].getInt()) ;
    EXPECT_EQ(40, powerList3[2].getInt()) ;

}



//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantVector, BoolVector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant vec1(std::string("vec1"), std::string("BOOL[]")) ;
    vec1.set(0u, true) ;
    vec1.set(2u, true) ;
    EXPECT_EQ(std::string("vec1[0]=true vec1[1]= vec1[2]=true"), vec1.getNameValuePair()) ;

    std::string error ;
    EXPECT_FALSE(DataVariantVector::isVectorComplete(vec1, error)) ;
    EXPECT_EQ("Value vec1[1] is unset", error) ;

    error="" ;
    std::vector<bool> boolList1(DataVariantVector::toBoolVector(vec1, error)) ;
    EXPECT_EQ(0u, boolList1.size()) ;

    vec1.set(1u, false) ;
    EXPECT_TRUE(DataVariantVector::isVectorComplete(vec1, error)) ;
    EXPECT_EQ("", error) ;

    std::vector<bool> boolList2(DataVariantVector::toBoolVector(vec1, error)) ;
    EXPECT_EQ(3u, boolList2.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(true, boolList2[0]) ;
    EXPECT_EQ(false, boolList2[1]) ;
    EXPECT_EQ(true, boolList2[2]) ;

    // change names
    vec1.setName(0u, "first") ;
    vec1.setName(1u, "second") ;
    vec1.setName(2u, "third") ;

    std::vector<bool> boolList3(DataVariantVector::toBoolVector(vec1, error)) ;
    EXPECT_EQ(3u, boolList3.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ(true, boolList3[0]) ;
    EXPECT_EQ(false, boolList3[1]) ;
    EXPECT_EQ(true, boolList3[2]) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariantVector, StringVector)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	DataVariant vec1(std::string("vec1"), std::string("STRING[]")) ;
    vec1.set(0u, "aaa") ;
    vec1.set(2u, "ccc") ;

    std::string error ;
    EXPECT_FALSE(DataVariantVector::isVectorComplete(vec1, error)) ;
    EXPECT_EQ("Value vec1[1] is unset", error) ;

    error="" ;
    std::vector<std::string> stringList1(DataVariantVector::toStringVector(vec1, error)) ;
    EXPECT_EQ(0u, stringList1.size()) ;

    vec1.set(1u, "bbb") ;
    EXPECT_TRUE(DataVariantVector::isVectorComplete(vec1, error)) ;
    EXPECT_EQ("", error) ;

    std::vector<std::string> stringList2(DataVariantVector::toStringVector(vec1, error)) ;
    EXPECT_EQ(3u, stringList2.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ("aaa", stringList2[0]) ;
    EXPECT_EQ("bbb", stringList2[1]) ;
    EXPECT_EQ("ccc", stringList2[2]) ;

    // change names
    vec1.setName(0u, "first") ;
    vec1.setName(1u, "second") ;
    vec1.setName(2u, "third") ;

    std::vector<std::string> stringList3(DataVariantVector::toStringVector(vec1, error)) ;
    EXPECT_EQ(3u, stringList3.size()) ;
    EXPECT_EQ("", error) ;
    EXPECT_EQ("aaa", stringList3[0]) ;
    EXPECT_EQ("bbb", stringList3[1]) ;
    EXPECT_EQ("ccc", stringList3[2]) ;

}

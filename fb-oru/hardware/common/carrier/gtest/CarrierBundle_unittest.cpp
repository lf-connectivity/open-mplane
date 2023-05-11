/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierBundle_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "ICarrierBundleList.h"
#include "CarrierBundle.h"

using namespace Mplane;

//static bool debug = true ;

/*
 * Unit tests
 */
TEST(CarrierBundle, Basic)
{
    const ::testing::TestInfo* const test_info =
      ::testing::UnitTest::GetInstance()->current_test_info();

    std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
    std::cout << test_info->name() << " - START" <<  std::endl;

    // CarrierBundle(const Frequency& totalBw, const Frequency& maxGap) ;
    Frequency f0(0.0) ;
    Frequency f1_4(1.4, Frequency::MHz) ;
    Frequency f3(3.0, Frequency::MHz) ;
    Frequency f5(5.0, Frequency::MHz) ;
    Frequency f10(10.0, Frequency::MHz) ;
    Frequency f15(15.0, Frequency::MHz) ;
    Frequency f20(20.0, Frequency::MHz) ;
    CarrierBundle cb_0_0(2, f0, f0, f0, f0) ;

    // This test uses internal knowledge of the thresholds table and will be invalid if/when the table changes!
	std::vector<Power> thresholds ;

    //		    [CB_GAP_0]  =
//	{ /* thresholds */ {6.70, 6.70, 6.80} },    // default
    thresholds = cb_0_0.getThresholds() ;
    EXPECT_NEAR(6.70, thresholds[0].get(), 0.01) ;
    EXPECT_NEAR(6.70, thresholds[1].get(), 0.01) ;
    EXPECT_NEAR(6.80, thresholds[2].get(), 0.01) ;

//    //		[CB_BW_5] =
//    		{
//    //		    [CB_GAP_0]  =
//    				{ /* thresholds */ {7.50, 7.50, 7.60}, /* clip */ 7.70 },    // 5
//    //			[CB_GAP_10] =
//    				{ /* thresholds */ {7.50, 7.50, 7.60}, /* clip */ 7.70 },    // N/A
    CarrierBundle cb_1M4_10(2, f1_4, f10, f0, f0) ;
    CarrierBundle cb_3_10(2, f3, f10, f0, f0) ;
    CarrierBundle cb_5_0(2, f5, f0, f0, f0) ;

    thresholds = cb_5_0.getThresholds() ;
    EXPECT_NEAR(6.50, thresholds[0].get(), 0.01) ;
    EXPECT_NEAR(6.50, thresholds[1].get(), 0.01) ;
    EXPECT_NEAR(6.60, thresholds[2].get(), 0.01) ;

    CarrierBundle cb_5_10(2, f5, f10, f0, f0) ;

    thresholds = cb_5_10.getThresholds() ;
    EXPECT_NEAR(6.50, thresholds[0].get(), 0.01) ;
    EXPECT_NEAR(6.50, thresholds[1].get(), 0.01) ;
    EXPECT_NEAR(6.60, thresholds[2].get(), 0.01) ;

//    //		[CB_BW_10] =
//    		{
//    //		    [CB_GAP_0]  =
//    				{ /* thresholds */ {7.20, 7.20, 7.30}, /* clip */ 7.40 },    // 10 5+5
//    //			[CB_GAP_10] =
//    				{ /* thresholds */ {7.20, 7.20, 7.80}, /* clip */ 7.90 },    // N/A
//    //			[CB_GAP_20] =
//    				{ /* thresholds */ {7.20, 7.20, 7.80}, /* clip */ 7.90 },    // N/A
    CarrierBundle cb_10_0(2, f10, f0, f0, f0) ;

    thresholds = cb_10_0.getThresholds() ;
    EXPECT_NEAR(6.20, thresholds[0].get(), 0.01) ;
    EXPECT_NEAR(6.20, thresholds[1].get(), 0.01) ;
    EXPECT_NEAR(6.30, thresholds[2].get(), 0.01) ;

    CarrierBundle cb_10_20(2, f10, f20, f0, f0) ;

    thresholds = cb_10_20.getThresholds() ;
    EXPECT_NEAR(6.20, thresholds[0].get(), 0.01) ;
    EXPECT_NEAR(6.20, thresholds[1].get(), 0.01) ;
    EXPECT_NEAR(6.80, thresholds[2].get(), 0.01) ;



    //-------------------------------------------------
    // Compare bundles
    EXPECT_NE(cb_0_0, cb_5_0) ;

    // BW 10MHz GAP 0
    CarrierBundle cb_7_2(2, Frequency(7.0, Frequency::MHz), Frequency(2.0, Frequency::MHz), f0, f0) ;
    EXPECT_NE(cb_5_0, cb_7_2) ;
    EXPECT_EQ(cb_10_0, cb_7_2) ;

    // BW 1.4MHz GAP 10
    CarrierBundle cb_2_7(2, Frequency(2.0, Frequency::MHz), Frequency(7.0, Frequency::MHz), f0, f0) ;
    EXPECT_EQ(cb_1M4_10, cb_2_7) ;

    // BW 20MHz GAP 20
    CarrierBundle cb_17_17(2, Frequency(17.0, Frequency::MHz), Frequency(17.0, Frequency::MHz), f0, f0) ;
    CarrierBundle cb_20_20(2, Frequency(20.0, Frequency::MHz), Frequency(20.0, Frequency::MHz), f0, f0) ;
    EXPECT_EQ(cb_20_20, cb_17_17) ;

    // BW 50MHz GAP 30
    CarrierBundle cb_47_27(2, Frequency(47.0, Frequency::MHz), Frequency(27.0, Frequency::MHz), f0, f0) ;
    CarrierBundle cb_50_30(2, Frequency(50.0, Frequency::MHz), Frequency(30.0, Frequency::MHz), f0, f0) ;
    EXPECT_EQ(cb_50_30, cb_47_27) ;

    // BW 40MHz GAP 40
    CarrierBundle cb_37_36(2, Frequency(37.0, Frequency::MHz), Frequency(36.0, Frequency::MHz), f0, f0) ;
    CarrierBundle cb_40_40(2, Frequency(40.0, Frequency::MHz), Frequency(40.0, Frequency::MHz), f0, f0) ;
    EXPECT_EQ(cb_40_40, cb_37_36) ;


    //--------------------------------------------
    // Bundle list
    std::shared_ptr<ICarrierBundleList> list(ICarrierBundleList::getInstance()) ;
    std::shared_ptr<ICarrierBundleListSetter> listSetter(ICarrierBundleListSetter::getInstance()) ;

    EXPECT_TRUE(list->getCarrierBundle(10).get() == nullptr) ;
    EXPECT_TRUE(list->getMultiCarrierBundle(10).get() == nullptr) ;

    listSetter->setCarrierBundle(10, cb_37_36) ;
    listSetter->setMultiCarrierBundle(10, cb_37_36) ;

    EXPECT_TRUE(list->getCarrierBundle(10).get() == nullptr) ;
    EXPECT_TRUE(list->getMultiCarrierBundle(10).get() == nullptr) ;

    listSetter->setMultiCarrierBundle(10, cb_37_36) ;


    // BW 10MHz GAP 0
    listSetter->setCarrierBundle(0, cb_7_2) ;
    EXPECT_NE(cb_5_0, *(list->getCarrierBundle(0)) ) ;
    EXPECT_EQ(cb_10_0, *(list->getCarrierBundle(0)) ) ;

    // BW 1.4MHz GAP 10
    listSetter->setCarrierBundle(1, cb_2_7) ;
    EXPECT_EQ(cb_1M4_10, *(list->getCarrierBundle(1)) ) ;

    // BW 20MHz GAP 20
    listSetter->setMultiCarrierBundle(0, cb_17_17) ;
    EXPECT_EQ(cb_20_20, *(list->getMultiCarrierBundle(0)) ) ;

    // BW 50MHz GAP 30
    listSetter->setMultiCarrierBundle(1, cb_47_27) ;
    EXPECT_EQ(cb_50_30, *(list->getMultiCarrierBundle(1)) ) ;


    // Random checks
    CarrierBundle cb_misc(3,
    	Frequency(37.0, Frequency::MHz), // total BW
    	Frequency(36.0, Frequency::MHz), // gap
    	Frequency(38.0, Frequency::MHz), // sum BW
    	Frequency(39.0, Frequency::MHz)  // ave centre
    ) ;
    EXPECT_EQ(3, cb_misc.getNumCarriers()) ;
    EXPECT_EQ(Frequency(38.0, Frequency::MHz), cb_misc.getSumBw()) ;
    EXPECT_EQ(Frequency(39.0, Frequency::MHz), cb_misc.getAveCentre()) ;
}



//===================================================================================================================

class AppSettings {
public:
	enum Tfdd {TDD, FDD} ;

	AppSettings(Tfdd tfdd) : mTfdd(tfdd) {}
	~AppSettings() {}

	Tfdd getType() { return mTfdd; }

private:
	Tfdd mTfdd ;
};

class ObjBase {
public:
	ObjBase() {}
	virtual ~ObjBase() {}
	virtual void show() { std::cerr << "ObjBase" << std::endl; }
};

class ObjTdd : public ObjBase {
public:
	ObjTdd() {}
	virtual ~ObjTdd() {}
	virtual void show() { std::cerr << "ObjTdd" << std::endl; }
};

class ObjFdd : public ObjBase {
public:
	ObjFdd() {}
	virtual ~ObjFdd() {}
	virtual void show() { std::cerr << "ObjFdd" << std::endl; }
};

//static

TEST(CarrierBundle, ObjectSelect)
{
	AppSettings appSettings(AppSettings::TDD) ;

//	ObjBase* obj( appSettings.getType() == AppSettings::FDD ? new ObjFdd : new ObjTdd) ;
//	ObjBase* obj(new ObjTdd) ;
	ObjBase* obj ;
	if (appSettings.getType() == AppSettings::FDD)
		obj = new ObjFdd ;
	else
		obj = new ObjTdd ;
	obj->show() ;
	delete obj ;

}

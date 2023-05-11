/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFunctionalTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <typeinfo>
#include <string>
#include <iostream>
#include <vector>

#include <numeric>
#include <functional>
#include <algorithm>

#include "ICarrier.h"
#include "ICarrierHardware.h"
#include "CarrierUtils.hpp"
#include "CommonCarrier.h"
#include "CommonCarrierHardwareList.hpp"
#include "CommonCarrierHardwareFunctional.h"



using namespace std;
using namespace Mplane;

//========================================================================================================================
// TYPES
//========================================================================================================================

//------------------------------------------------------------------------------------------------------------------------
// CarrierHardware test class
class FunctionalCarrierHardware : public ICarrierHardware
{
public:
    /**
     *
     */
	FunctionalCarrierHardware(const ICarrier *carrier = 0) :
		mCarrier(carrier),
		mIndex(0)
    {
		if (carrier)
			mIndex = carrier->getIndex() ;
    }

	FunctionalCarrierHardware(const ICarrier *carrier, unsigned index) :
		mCarrier(carrier),
		mIndex(index)
    {
    }

	virtual ~FunctionalCarrierHardware() {}

    virtual const ICarrier& getCarrier() const { return *mCarrier ; }
    virtual bool validateChange(const ICarrier &carrier) { return true; }
    virtual bool carrierChange(const ICarrier &carrier) { return true; }
    virtual const bool isChanged() const { return true; }
    virtual bool preUpdate() { return true; }
    virtual bool updateHardware() { return true; }
    virtual bool postUpdate() { return true; }
    virtual void changeComplete() { }
    virtual void settingsChanged() {}
    virtual std::string failReason(void) { return std::string(""); }
    virtual void setFailReason(std::string reason) {}
    virtual void clearFailReason() {}
    void showCarrier(std::ostream& os = std::cout) const {
    	os << "Show carrier hardware" << std::endl ;
    }
    void showDiag(std::ostream& os = std::cout) const {
    }

    virtual Power getPower(unsigned txpath) const { return Power(10.0); }
    virtual Frequency getMinTxFreq() const { return Frequency(1000.0); }
    virtual Frequency getMaxTxFreq() const { return Frequency(1000.0); }
    virtual unsigned getDlDelay( unsigned antenna ) const { return 0; }
    virtual unsigned getUlDelay( unsigned antenna ) const { return 0; }
    virtual unsigned getUlAdditionalDelay( unsigned antenna ) const { return 0; }

    virtual bool resyncUlStream( unsigned path ) { return true; }
    virtual bool resyncDlStream( unsigned path ) { return true; }
    virtual bool getRssi(unsigned antenna, Power& rssi) const { rssi=Power(0.0); return true; }
    virtual Frequency getChbwFreq() const {return Frequency(1000.0);}
    virtual Frequency getTxFreq() const {return Frequency(1000.0);}

    void incLoop() {
    	++loopCount;
    	indexCount += mIndex ;
    }

    void incLoopArg(const unsigned& arg) {
    	++loopCount;
    	indexCount += mIndex + arg ;
    }

    void incLoopArg2(const unsigned& arg, const unsigned& arg2) {
    	++loopCount;
    	indexCount += mIndex + arg + arg2 ;
    }


	const FunctionalCarrierHardware transArg(const unsigned arg) const
	{
    	++loopCount;

    	FunctionalCarrierHardware ch(*this) ;
		ch.mIndex += arg ;
		std::cerr << "transArg arg=" << arg << " this : " << mIndex << " ch : " << ch.mIndex << std::endl ;
		indexCount += ch.mIndex ;
		return ch ;
	}

	const FunctionalCarrierHardware trans() const
	{
    	++loopCount;

    	FunctionalCarrierHardware ch(*this) ;
		ch.mIndex += 10 ;
		std::cerr << "trans this : " << mIndex << " ch : " << ch.mIndex << std::endl ;
		indexCount += ch.mIndex ;
		return ch ;
	}

    const bool pred() const
    {
    	// allow evens
    	if (mIndex % 2 == 0)
    		return true ;
    	return false ;
    }

    const bool predArg(unsigned int arg) const
    {
    	if (mIndex % arg == 0)
    		return true ;
    	return false ;
    }

	const FunctionalCarrierHardware summariseArg(const FunctionalCarrierHardware& b, const unsigned arg) const
	{
    	++loopCount;

    	FunctionalCarrierHardware ch ;
		ch.mIndex += mIndex + b.mIndex + arg ;
		std::cerr << "summariseArg arg=" << arg << " this : " << mIndex <<
				" b : " << b.mIndex <<
				" ch : " << ch.mIndex << std::endl ;
		indexCount += ch.mIndex ;
		return ch ;
	}

	const FunctionalCarrierHardware summarise(const FunctionalCarrierHardware& b) const
	{
    	++loopCount;

    	FunctionalCarrierHardware ch ;
		ch.mIndex += mIndex + b.mIndex ;
		std::cerr << "summarise this : " << mIndex <<
				" b : " << b.mIndex <<
				" ch : " << ch.mIndex << std::endl ;
		indexCount += ch.mIndex ;
		return ch ;
	}

	bool txFrequencyChange(unsigned antenna,
			const Frequency& newTxFrequency) {
		return true ;
	}

	bool rxFrequencyChange(unsigned antenna,
			const Frequency& newRxFrequency) {
		return true ;
	}


public:
	const ICarrier *mCarrier ;
	static unsigned loopCount ;
	static unsigned indexCount ;
	unsigned mIndex ;
};

unsigned FunctionalCarrierHardware::loopCount = 0 ;
unsigned FunctionalCarrierHardware::indexCount = 0 ;



//------------------------------------------------------------------------------------------------------------------------
class FunctionalCarrierHardwareList : public CommonCarrierHardwareList<FunctionalCarrierHardware>
{
public:
	typedef CommonCarrierHardwareList<FunctionalCarrierHardware>::iterator iterator ;
	typedef CommonCarrierHardwareList<FunctionalCarrierHardware>::const_iterator const_iterator ;

	FunctionalCarrierHardwareList() : CommonCarrierHardwareList<FunctionalCarrierHardware>() {}
	virtual ~FunctionalCarrierHardwareList() {}

};

//------------------------------------------------------------------------------------------------------------------------
// Test fixture
class CarrierFunctionalTests : public ::testing::Test
{
public:

    /*! @brief Setup the test
     */
    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
          ::testing::UnitTest::GetInstance()->current_test_info();

        cout << endl << "*** " << test_info->test_case_name() << " Tests ***" <<  endl;
        cout << test_info->name() << " - START" <<  endl;

        unsigned txPorts = 2 ;
        unsigned rxPorts = 2 ;
        unsigned carrierIndex = 0 ;
        hwlist.addCarrier( CommonCarrier(carrierIndex++, txPorts, rxPorts) ) ;
        hwlist.addCarrier( CommonCarrier(carrierIndex++, txPorts, rxPorts) ) ;
        hwlist.addCarrier( CommonCarrier(carrierIndex++, txPorts, rxPorts) ) ;
        hwlist.addCarrier( CommonCarrier(carrierIndex++, txPorts, rxPorts) ) ;
        hwlist.addCarrier( CommonCarrier(carrierIndex++, txPorts, rxPorts) ) ;


        for (FunctionalCarrierHardwareList::iterator it = hwlist.begin(); it != hwlist.end(); ++it)
        {
        	list.push_back(*it) ;
        }

        FunctionalCarrierHardware::loopCount = 0 ;
        FunctionalCarrierHardware::indexCount = 0 ;
    }

    /*! @brief Tear down the test
     */
    virtual void TearDown()
    {

    }

protected:
    FunctionalCarrierHardwareList hwlist ;
    std::vector<FunctionalCarrierHardware> list ;
};



//========================================================================================================================
// TESTS
//========================================================================================================================


//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, foreachTest)
{
    // 	carrier_hardware_foreach_bind(_TFunRet (_TCarrierHardware::*fn)())
    std::for_each(list.begin(), list.end(), carrier_hardware_foreach_bind(&FunctionalCarrierHardware::incLoop)) ;
    EXPECT_EQ(5u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(10u, FunctionalCarrierHardware::indexCount) ;
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, foreach2Test)
{
    std::for_each(hwlist.begin(), hwlist.end(), carrier_hardware_foreach_bind(&FunctionalCarrierHardware::incLoop)) ;
    EXPECT_EQ(5u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(10u, FunctionalCarrierHardware::indexCount) ;
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, foreachPredTest)
{
    // 	carrier_hardware_foreach_bind(_TFunRet (_TCarrierHardware::*fn)(), const bool (_TCarrierHardware::*pred)() const)
    std::for_each(list.begin(), list.end(), carrier_hardware_foreach_bind(&FunctionalCarrierHardware::incLoop, &FunctionalCarrierHardware::pred)) ;
    EXPECT_EQ(3u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(6u, FunctionalCarrierHardware::indexCount) ;

}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, foreachArg1Test)
{
    // carrier_hardware_foreach_bind1(_TFunRet (_TCarrierHardware::*fn)(const _TArg1& arg1), const _TArg1& arg1)
    const unsigned arg = 100u ;
    std::for_each(list.begin(), list.end(), carrier_hardware_foreach_bind1(&FunctionalCarrierHardware::incLoopArg, arg)) ;
    EXPECT_EQ(5u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(510u, FunctionalCarrierHardware::indexCount) ;


}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, foreachArg2Test)
{
    // carrier_hardware_foreach_bind2(_TFunRet (_TCarrierHardware::*fn)(const _TArg1& arg1, const _TArg2& arg2)
    const unsigned arg = 100u ;
    const unsigned arg2 = 100u ;
    std::for_each(list.begin(), list.end(), carrier_hardware_foreach_bind2(&FunctionalCarrierHardware::incLoopArg2, arg, arg2)) ;
    EXPECT_EQ(5u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(1010u, FunctionalCarrierHardware::indexCount) ;

}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, transformTest)
{
    // carrier_hardware_transform_bind(const _TCarrierHardware (_TCarrierHardware::*fn)(const _Arg) const, const _Arg arg)
    const unsigned arg = 100u ;
    std::transform(hwlist.begin(), hwlist.end(), hwlist.begin(), carrier_hardware_transform_bind(&FunctionalCarrierHardware::transArg, arg)) ;
    EXPECT_EQ(5u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(510u, FunctionalCarrierHardware::indexCount) ;

    unsigned idx = 0 ;
    for (FunctionalCarrierHardwareList::iterator it = hwlist.begin(); it != hwlist.end(); ++it)
    {
        EXPECT_EQ(100u + idx, it->mIndex) ;
        ++idx ;
    }
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, transformArg1Test)
{
    // carrier_hardware_transform_bind(const _TCarrierHardware (_TCarrierHardware::*fn)() const, const bool (_TCarrierHardware::*pred)() const)
    const unsigned arg = 100u ;
    std::transform(hwlist.begin(), hwlist.end(), hwlist.begin(), carrier_hardware_transform_bind(&FunctionalCarrierHardware::transArg, arg)) ;
    EXPECT_EQ(5u, FunctionalCarrierHardware::loopCount) ;

    unsigned idx = 0 ;
    for (FunctionalCarrierHardwareList::iterator it = hwlist.begin(); it != hwlist.end(); ++it)
    {
        EXPECT_EQ(100u + idx, it->mIndex) ;
        ++idx ;
    }
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, transformPredTest)
{
    // carrier_hardware_transform_bind(const _TCarrierHardware (_TCarrierHardware::*fn)() const, const bool (_TCarrierHardware::*pred)() const)
    std::transform(hwlist.begin(), hwlist.end(), hwlist.begin(), carrier_hardware_transform_bind(&FunctionalCarrierHardware::trans, &FunctionalCarrierHardware::pred)) ;
    EXPECT_EQ(3u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(36u, FunctionalCarrierHardware::indexCount) ;

    unsigned idx = 0 ;
    for (FunctionalCarrierHardwareList::iterator it = hwlist.begin(); it != hwlist.end(); ++it)
    {
    	if (idx % 2 == 0)
    		EXPECT_EQ(10u + idx, it->mIndex) ;
    	else
    		EXPECT_EQ(idx, it->mIndex) ;
        ++idx ;
    }
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, transformPredArgTest)
{
	//	carrier_hardware_transform_bind(const _TCarrierHardware (_TCarrierHardware::*fn)() const, const bool (_TCarrierHardware::*pred)(const _Arg) const, const _Arg arg)
	unsigned arg = 3u ;
	std::transform(hwlist.begin(), hwlist.end(), hwlist.begin(), carrier_hardware_transform_bind(&FunctionalCarrierHardware::trans, &FunctionalCarrierHardware::predArg, arg)) ;
    EXPECT_EQ(2u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(23u, FunctionalCarrierHardware::indexCount) ;

    unsigned idx = 0 ;
    for (FunctionalCarrierHardwareList::iterator it = hwlist.begin(); it != hwlist.end(); ++it)
    {
    	if (idx % 3 == 0)
    		EXPECT_EQ(10u + idx, it->mIndex) ;
    	else
    		EXPECT_EQ(idx, it->mIndex) ;
        ++idx ;
    }
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, transformArgPredArgTest)
{
	//	carrier_hardware_transform_bind(
	//				const _TCarrierHardware (_TCarrierHardware::*fn)(const _Fn_arg) const,
	//				const _Fn_arg fn_arg,
	//				const bool (_TCarrierHardware::*pred)(const _Pred_arg) const,
	//				const _Pred_arg pred_arg)
	unsigned arg = 100u ;
	unsigned predArg = 2u ;
	std::transform(hwlist.begin(), hwlist.end(), hwlist.begin(), carrier_hardware_transform_bind(&FunctionalCarrierHardware::transArg, arg, &FunctionalCarrierHardware::predArg, predArg)) ;
    EXPECT_EQ(3u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(306u, FunctionalCarrierHardware::indexCount) ;

    unsigned idx = 0 ;
    for (FunctionalCarrierHardwareList::iterator it = hwlist.begin(); it != hwlist.end(); ++it)
    {
    	if (idx % 2 == 0)
    		EXPECT_EQ(100u + idx, it->mIndex) ;
    	else
    		EXPECT_EQ(idx, it->mIndex) ;
        ++idx ;
    }
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, summariseArgTest)
{
	//carrier_hardware_summarise_bind(const _TCarrierHardware (_TCarrierHardware::*fn)(const _TCarrierHardware&, const _Arg) const, const _Arg arg)
    const unsigned arg = 100u ;
    FunctionalCarrierHardware summary = std::accumulate(hwlist.begin(), hwlist.end(), FunctionalCarrierHardware(),
    		carrier_hardware_summarise_bind(&FunctionalCarrierHardware::summariseArg, arg)) ;

    EXPECT_EQ(5u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(510u, summary.mIndex) ;
    EXPECT_EQ(1520u, FunctionalCarrierHardware::indexCount) ;	// sum of the individual summary totals

    unsigned idx = 0 ;
    for (FunctionalCarrierHardwareList::iterator it = hwlist.begin(); it != hwlist.end(); ++it)
    {
        EXPECT_EQ(idx, it->mIndex) ;
        ++idx ;
    }
}

//------------------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFunctionalTests, summarisePredArgTest)
{
	//carrier_hardware_summarise_bind(const _TCarrierHardware (_TCarrierHardware::*fn)(const _TCarrierHardware&) const, const bool (_TCarrierHardware::*pred)(const _Arg) const, const _Arg arg)
	unsigned arg = 3u ;
    FunctionalCarrierHardware summary = std::accumulate(hwlist.begin(), hwlist.end(), FunctionalCarrierHardware(),
    		carrier_hardware_summarise_bind(&FunctionalCarrierHardware::summarise,
    				&FunctionalCarrierHardware::predArg, arg)) ;
    EXPECT_EQ(2u, FunctionalCarrierHardware::loopCount) ;
    EXPECT_EQ(3u, FunctionalCarrierHardware::indexCount) ;
    EXPECT_EQ(3u, summary.mIndex) ;

    unsigned idx = 0 ;
    for (FunctionalCarrierHardwareList::iterator it = hwlist.begin(); it != hwlist.end(); ++it)
    {
        EXPECT_EQ(idx, it->mIndex) ;
        ++idx ;
    }
}

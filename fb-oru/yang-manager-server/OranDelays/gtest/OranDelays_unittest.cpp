/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranDelays_unittest.cpp
 * \brief     Oran Delays unit tests
 *
 *
 * \details   ORAN Delays unit tests.
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "IOranDelays.h"
#include "OranDelays.h"

using namespace Mplane;

class TestBandwidthProcessingDelays10G : public ::testing::Test
{
public:

    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name()
                << " Tests ***" << std::endl;
        std::cout << test_info->name() << " - SETUP" << std::endl;

        // Do the setup here
        Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_NORMAL, "YANG") ;

        mOranDelays = new OranDelays(IOranDelays::DelayClock_T::_10G_CLOCK);

        std::cout << test_info->name() << " - SETUP complete" << std::endl;
    }

    virtual void TearDown()
	{
	  const ::testing::TestInfo* const test_info =
			  ::testing::UnitTest::GetInstance()->current_test_info();

	  std::cout << test_info->name() << " - TEARDOWN" << std::endl;

	  // Do the tear down here
	  delete mOranDelays;

	  std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;
	}

    OranDelays * mOranDelays;

    virtual ~TestBandwidthProcessingDelays10G(){}

protected:

private:

};

TEST_F(TestBandwidthProcessingDelays10G, getTOranDlMin)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranDlMin(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 51007.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranDlMin(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 11347;

	EXPECT_TRUE(delay == expectedResult);

}

TEST_F(TestBandwidthProcessingDelays10G, getTOranDlMax)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranDlMax(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 116193.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranDlMax(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 81119;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, getTOranUlMin)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlMin(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 126792.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlMin(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 84180.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, getTOranUlMax)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlMax(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 197836.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlMax(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 154581.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, getTOranUlProc)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlProc(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 120524.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlProc(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 80879.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, getSlotLength)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(120.00, Frequency::KHz);

	delay = mOranDelays->getSlotLength(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 125000.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(15.00, Frequency::KHz);

	delay = mOranDelays->getSlotLength(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 1000000.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, getChBwTypeFromBandwidth)
{
	mOranDelays->initDelayData();

	ICarrierHardwareTypes::ChbwType chBwType;

	Frequency bwFreq(200.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	ICarrierHardwareTypes::ChbwType expectedResult = ICarrierHardwareTypes::CHBW_200;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(5000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_5000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(10000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_10000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(15000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_15000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(20000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_20000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(100000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_100000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(200000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_UNSET;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(400000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_UNSET;

	EXPECT_TRUE(chBwType == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, getTduc)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->getTduc(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 18941.20;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, getTddc)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->getTddc(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 18990.10;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, getCalcT2aMinUpTddc)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMinUp(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 31724.50;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, CalcT2aMaxUp)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMaxUp(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 100345;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, CalcTcpAdvDl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcTcpAdvDl(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 0.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, CalcT2aMinCpDl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMinCpDl(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 31724.50;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, CalcT2aMaxCpDl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMaxCpDl(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 100345;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, CalcT3aMin)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcTa3Min(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 103332;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, CalcT3aMax)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcTa3Max(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 261180;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, CalcT2aMinCpUl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMinCpUl(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 0.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays10G, CalcT2aMaxCpUl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);
	Frequency slot(15.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMaxCpUl(freq, slot);

	std::cout << "Actual delay = " << delay.getInt() << std::endl;

	Zcu111Delay expectedResult = 900131;

	EXPECT_TRUE(delay == expectedResult);
}

// ======================================================================================================
class TestBandwidthProcessingDelays25G : public ::testing::Test
{
public:

    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name()
                << " Tests ***" << std::endl;
        std::cout << test_info->name() << " - SETUP" << std::endl;

        // Do the setup here
        Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_NORMAL, "YANG") ;

        mOranDelays = new OranDelays(IOranDelays::DelayClock_T::_25G_CLOCK);

        std::cout << test_info->name() << " - SETUP complete" << std::endl;
    }

    virtual void TearDown()
	{
	  const ::testing::TestInfo* const test_info =
			  ::testing::UnitTest::GetInstance()->current_test_info();

	  std::cout << test_info->name() << " - TEARDOWN" << std::endl;

	  // Do the tear down here
	  delete mOranDelays;

	  std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;
	}

    OranDelays * mOranDelays;

    virtual ~TestBandwidthProcessingDelays25G(){}

protected:

private:

};

TEST_F(TestBandwidthProcessingDelays25G, getTOranDlMin)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranDlMin(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 51007.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranDlMin(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 11347;

	EXPECT_TRUE(delay == expectedResult);

}

TEST_F(TestBandwidthProcessingDelays25G, getTOranDlMax)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranDlMax(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 116193.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranDlMax(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 81119;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, getTOranUlMin)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlMin(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 126792.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlMin(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 84180.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, getTOranUlMax)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlMax(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 197836.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlMax(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 154581.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, getTOranUlProc)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(20000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlProc(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 120524.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(5000.00, Frequency::KHz);

	delay = mOranDelays->getTOranUlProc(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 80879.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, getSlotLength)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(120.00, Frequency::KHz);

	delay = mOranDelays->getSlotLength(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 125000.00;

	EXPECT_TRUE(delay == expectedResult);

	freq.set(15.00, Frequency::KHz);

	delay = mOranDelays->getSlotLength(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	expectedResult = 1000000.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, getChBwTypeFromBandwidth)
{
	mOranDelays->initDelayData();

	ICarrierHardwareTypes::ChbwType chBwType;

	Frequency bwFreq(200.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	ICarrierHardwareTypes::ChbwType expectedResult = ICarrierHardwareTypes::CHBW_200;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(5000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_5000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(10000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_10000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(15000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_15000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(20000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_20000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(100000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_100000;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(200000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_UNSET;

	EXPECT_TRUE(chBwType == expectedResult);

	//-----------------------------------------------------------------------------------------------------
	bwFreq.set(400000.00, Frequency::KHz);

	chBwType = mOranDelays->getChBwTypeFromBandwidth(bwFreq);

	std::cout << "chBwType = " << ICarrierHardwareTypes::chbwToStr(chBwType) << std::endl;

	expectedResult = ICarrierHardwareTypes::CHBW_UNSET;

	EXPECT_TRUE(chBwType == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, getTduc)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->getTduc(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 18941.20;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, getTddc)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->getTddc(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 18990.10;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, getCalcT2aMinUpTddc)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMinUp(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 30875.90;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, CalcT2aMaxUp)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMaxUp(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 100187;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, CalcTcpAdvDl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcTcpAdvDl(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 0.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, CalcT2aMinCpDl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMinCpDl(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 30875.90;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, CalcT2aMaxCpDl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMaxCpDl(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 100187;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, CalcT3aMin)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcTa3Min(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 103255;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, CalcT3aMax)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcTa3Max(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 261104;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, CalcT2aMinCpUl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMinCpUl(freq);

	std::cout << "delay = " << delay.get() << std::endl;

	Zcu111Delay expectedResult = 0.00;

	EXPECT_TRUE(delay == expectedResult);
}

TEST_F(TestBandwidthProcessingDelays25G, CalcT2aMaxCpUl)
{
	mOranDelays->initDelayData();

	Zcu111Delay delay;

	Frequency freq(5000.00, Frequency::KHz);
	Frequency slot(15.00, Frequency::KHz);

	delay = mOranDelays->CalcT2aMaxCpUl(freq, slot);

	std::cout << "Actual delay = " << delay.getInt() << std::endl;

	Zcu111Delay expectedResult = 900131;

	EXPECT_TRUE(delay == expectedResult);
}

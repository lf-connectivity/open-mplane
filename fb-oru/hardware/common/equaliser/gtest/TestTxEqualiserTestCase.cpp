/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxEqualiserTestCase.cpp
 * \brief     Test case file for the Tx equaliser
 *
 *
 * \details   Test case file for the Tx Equaliser
 *
 */

#include <stdexcept>
#include <memory>
#include <string.h>
#include <iostream>

#include "gtest/gtest.h"

#include "GlobalTypeDefs.h"
#include "Loggable.h"
#include "OffTargetFPGA.h"

#include "TestTxEqualiserTestCase.h"
#include "TxEqualiser.h"
#include "CommonEqualiser.h"
#include "TestCalData.h"
#include "IFrequencyConst.h"

namespace Mplane
{
    // Test objects

    Mplane::TestTxEq::TestTxEq() :
    		CommonTxEqualiser( 0, "TestTxEq", -122880000, 122880000, 32)
    {
    }

    Mplane::TestTxEq::~TestTxEq()
    {
        std::cout << "Mplane::TestTxEq destructor" << std::endl;
    }

    /*
     * Unit tests
     */
    void TestTxEqTestCases::SetUp()
    {
    }

    void TestTxEqTestCases::TearDown()
    {
    }

    void TestTxEqTestCases::setFreq(std::shared_ptr<CommonEqualiser> cEq, Frequency freq)
    {
    	cEq->mFrequencyChangeValue = freq;
    	cEq->mCurrentFrequency = freq;
    }

    void TestTxEqTestCases::extractResp(std::shared_ptr<TxEqualiser> eq, std::vector<EqPoint> &freqResp, bool ifResp)
    {
    	if (ifResp)
    	{
    		eq->extractIfFreqResp(freqResp);
    	}
    	else
    	{
    		eq->extractRfFreqResp(freqResp);
    	}
    }

    void TestTxEqTestCases::interpolate(std::shared_ptr<TxEqualiser> eq, std::vector<EqPoint> freqResp,
    		std::vector<EqPoint> &freqGainTable)
    {
    	eq->interpolateFreqResp(freqResp, freqGainTable);
    }

    void TestTxEqTestCases::combineResp(std::shared_ptr<TxEqualiser> eq,
    		std::vector<EqPoint> &freqGainTable1, std::vector<EqPoint> &freqGainTable2)
    {
    	eq->combineFreqResp(freqGainTable1, freqGainTable2);
    }

    void TestTxEqTestCases::calculateIfft(std::shared_ptr<TxEqualiser> eq,
    		std::vector<EqPoint> freqGainTable,
    		std::complex<float> input[])
    {
    	eq->performIfft(freqGainTable, input);
    }

    void TestTxEqTestCases::tukeyWindow(std::shared_ptr<TxEqualiser> eq,
    		std::vector<float> &factor)
    {
    	eq->calculateTukeyWindow(factor);
    }

    TEST_F(TestTxEqTestCases, basic)
    {
        // Check the basics work first.
        TestTxEq TestTemp;
        ASSERT_TRUE(TestTemp.getIndex()     == 0 ); // index 0
        ASSERT_EQ(TestTemp.getName().compare("TestTxEq"), 0 ); // name
    }

    TEST_F(TestTxEqTestCases, combinedResp)
	{
    	std::vector<EqPoint> freqResp;
    	std::vector<EqPoint> freqGainTable1;
    	std::vector<EqPoint> freqGainTable2;

    	std::vector< std::shared_ptr<IEqualiser> > txEqualisers;
        for( unsigned index = 0; index < 4; index++)
        {
        	txEqualisers.push_back (  std::shared_ptr<IEqualiser>(new TxEqualiser( index,"TX_EQ")) );
        }

    	//Change current frequency
    	Frequency freq(3000.0, Frequency::MHz);
    	setFreq(std::dynamic_pointer_cast<CommonEqualiser>(txEqualisers[0]), freq);

    	//calculate IF response
    	extractResp(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[0]), freqResp, true);

    	EXPECT_NEAR(freqResp[0].gain.get(), 0, 0.005);
    	EXPECT_NEAR(freqResp[1].gain.get(), -0.7, 0.005);
    	EXPECT_NEAR(freqResp[2].gain.get(), 0.8, 0.005);
    	EXPECT_NEAR(freqResp[3].gain.get(), 0.7, 0.005);
    	if (ITxFrequencyConstFactory::getInterface()->getLOInjection() == Injection_t::HIGHSIDE)
    	{
			EXPECT_NEAR(freqResp[4].gain.get(), 0.5, 0.005);
    	}
    	else
    	{
			EXPECT_NEAR(freqResp[4].gain.get(), 0.6, 0.005);
    	}
    	EXPECT_NEAR(freqResp[5].gain.get(), 0.4, 0.005);
    	EXPECT_NEAR(freqResp[6].gain.get(), 0.2, 0.005);
    	EXPECT_NEAR(freqResp[7].gain.get(), 0, 0.005);
    	EXPECT_NEAR(freqResp[8].gain.get(), 0.2, 0.005);
    	EXPECT_NEAR(freqResp[9].gain.get(), 0.4, 0.005);
    	if (ITxFrequencyConstFactory::getInterface()->getLOInjection() == Injection_t::HIGHSIDE)
		{
			EXPECT_NEAR(freqResp[10].gain.get(), 0.6, 0.005);
		}
    	else
    	{
			EXPECT_NEAR(freqResp[10].gain.get(), 0.5, 0.005);
    	}
    	EXPECT_NEAR(freqResp[11].gain.get(), 0.7, 0.005);
    	EXPECT_NEAR(freqResp[12].gain.get(), 0.8, 0.005);
    	EXPECT_NEAR(freqResp[13].gain.get(), -0.7, 0.005);
    	EXPECT_NEAR(freqResp[14].gain.get(), 0, 0.005);

		freqResp.clear();

    	//calculate RF response
    	extractResp(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[0]), freqResp, false);

    	EXPECT_NEAR(freqResp[0].gain.get(), 0, 0.005);
		EXPECT_NEAR(freqResp[1].gain.get(), 1.8214, 0.005);
		EXPECT_NEAR(freqResp[2].gain.get(), -2.2729, 0.005);
		EXPECT_NEAR(freqResp[3].gain.get(), -1.8214, 0.005);
		EXPECT_NEAR(freqResp[4].gain.get(), -1.3684, 0.005);
		EXPECT_NEAR(freqResp[5].gain.get(), -0.914, 0.005);
		EXPECT_NEAR(freqResp[6].gain.get(), -0.458, 0.005);
		EXPECT_NEAR(freqResp[7].gain.get(), 0, 0.005);
		EXPECT_NEAR(freqResp[8].gain.get(), 0.459, 0.005);
		EXPECT_NEAR(freqResp[9].gain.get(), 0.9198, 0.005);
		EXPECT_NEAR(freqResp[10].gain.get(), 1.382, 0.005);
		EXPECT_NEAR(freqResp[11].gain.get(), 1.845, 0.005);
		EXPECT_NEAR(freqResp[12].gain.get(), 2.3111, 0.005);
		EXPECT_NEAR(freqResp[13].gain.get(), -1.845, 0.005);
		EXPECT_NEAR(freqResp[14].gain.get(), 0, 0.005);

    	//Change current frequency
    	freqResp.clear();
		freq.set(2000.0, Frequency::MHz);
		setFreq(std::dynamic_pointer_cast<CommonEqualiser>(txEqualisers[0]), freq);

	   	//calculate IF response
		extractResp(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[0]), freqResp, true);

    	EXPECT_NEAR(freqResp[0].gain.get(), 0, 0.005);
    	EXPECT_NEAR(freqResp[1].gain.get(), -0.7, 0.005);
    	EXPECT_NEAR(freqResp[2].gain.get(), 0.8, 0.005);
    	EXPECT_NEAR(freqResp[3].gain.get(), 0.7, 0.005);
    	if (ITxFrequencyConstFactory::getInterface()->getLOInjection() == Injection_t::HIGHSIDE)
    	{
			EXPECT_NEAR(freqResp[4].gain.get(), 0.5, 0.005);
    	}
    	else
    	{
			EXPECT_NEAR(freqResp[4].gain.get(), 0.6, 0.005);
    	}
    	EXPECT_NEAR(freqResp[5].gain.get(), 0.4, 0.005);
    	EXPECT_NEAR(freqResp[6].gain.get(), 0.2, 0.005);
    	EXPECT_NEAR(freqResp[7].gain.get(), 0, 0.005);
    	EXPECT_NEAR(freqResp[8].gain.get(), 0.2, 0.005);
    	EXPECT_NEAR(freqResp[9].gain.get(), 0.4, 0.005);
    	if (ITxFrequencyConstFactory::getInterface()->getLOInjection() == Injection_t::HIGHSIDE)
		{
			EXPECT_NEAR(freqResp[10].gain.get(), 0.6, 0.005);
		}
    	else
    	{
			EXPECT_NEAR(freqResp[10].gain.get(), 0.5, 0.005);
    	}
    	EXPECT_NEAR(freqResp[11].gain.get(), 0.7, 0.005);
    	EXPECT_NEAR(freqResp[12].gain.get(), 0.8, 0.005);
    	EXPECT_NEAR(freqResp[13].gain.get(), -0.7, 0.005);
    	EXPECT_NEAR(freqResp[14].gain.get(), 0, 0.005);

		freqResp.clear();

		//calculate RF response
		extractResp(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[0]), freqResp, false);

		EXPECT_NEAR(freqResp[0].gain.get(), 0, 0.005);
		EXPECT_NEAR(freqResp[1].gain.get(), 1.2102, 0.005);
		EXPECT_NEAR(freqResp[2].gain.get(), -1.5089, 0.005);
		EXPECT_NEAR(freqResp[3].gain.get(), -1.2102, 0.005);
		EXPECT_NEAR(freqResp[4].gain.get(), -0.91, 0.005);
		EXPECT_NEAR(freqResp[5].gain.get(), -0.6082, 0.005);
		EXPECT_NEAR(freqResp[6].gain.get(), -0.3049, 0.005);
		EXPECT_NEAR(freqResp[7].gain.get(), 0, 0.005);
		EXPECT_NEAR(freqResp[8].gain.get(), 0.306, 0.005);
		EXPECT_NEAR(freqResp[9].gain.get(), 0.614, 0.005);
		EXPECT_NEAR(freqResp[10].gain.get(), 0.923, 0.005);
		EXPECT_NEAR(freqResp[11].gain.get(), 1.2346, 0.005);
		EXPECT_NEAR(freqResp[12].gain.get(), 1.5471, 0.005);
		EXPECT_NEAR(freqResp[13].gain.get(), -1.2346, 0.005);
		EXPECT_NEAR(freqResp[14].gain.get(), 0, 0.005);

    	//Change current frequency and calculate with equaliser 1
    	freqResp.clear();
		freq.set(4500.0, Frequency::MHz);
		setFreq(std::dynamic_pointer_cast<CommonEqualiser>(txEqualisers[1]), freq);

	   	//calculate IF response
		extractResp(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[1]), freqResp, true);

    	EXPECT_NEAR(freqResp[0].gain.get(), 0, 0.005);
    	EXPECT_NEAR(freqResp[1].gain.get(), -0.7, 0.005);
    	EXPECT_NEAR(freqResp[2].gain.get(), 0.8, 0.005);
    	EXPECT_NEAR(freqResp[3].gain.get(), 0.7, 0.005);
    	if (ITxFrequencyConstFactory::getInterface()->getLOInjection() == Injection_t::HIGHSIDE)
    	{
			EXPECT_NEAR(freqResp[4].gain.get(), 0.5, 0.005);
    	}
    	else
    	{
			EXPECT_NEAR(freqResp[4].gain.get(), 0.6, 0.005);
    	}
    	EXPECT_NEAR(freqResp[5].gain.get(), 0.4, 0.005);
    	EXPECT_NEAR(freqResp[6].gain.get(), 0.2, 0.005);
    	EXPECT_NEAR(freqResp[7].gain.get(), 0, 0.005);
    	EXPECT_NEAR(freqResp[8].gain.get(), 0.2, 0.005);
    	EXPECT_NEAR(freqResp[9].gain.get(), 0.4, 0.005);
    	if (ITxFrequencyConstFactory::getInterface()->getLOInjection() == Injection_t::HIGHSIDE)
		{
			EXPECT_NEAR(freqResp[10].gain.get(), 0.6, 0.005);
		}
    	else
    	{
			EXPECT_NEAR(freqResp[10].gain.get(), 0.5, 0.005);
    	}
    	EXPECT_NEAR(freqResp[11].gain.get(), 0.7, 0.005);
    	EXPECT_NEAR(freqResp[12].gain.get(), 0.8, 0.005);
    	EXPECT_NEAR(freqResp[13].gain.get(), -0.7, 0.005);
    	EXPECT_NEAR(freqResp[14].gain.get(), 0, 0.005);

		freqResp.clear();

		//calculate RF response
		extractResp(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[1]), freqResp, false);

		EXPECT_NEAR(freqResp[0].gain.get(), 0, 0.005);
		EXPECT_NEAR(freqResp[1].gain.get(), 2.73818, 0.005);
		EXPECT_NEAR(freqResp[2].gain.get(), -3.4189, 0.005);
		EXPECT_NEAR(freqResp[3].gain.get(), -2.73818, 0.005);
		EXPECT_NEAR(freqResp[4].gain.get(), -2.056, 0.005);
		EXPECT_NEAR(freqResp[5].gain.get(), -1.3722, 0.005);
		EXPECT_NEAR(freqResp[6].gain.get(), -0.687, 0.005);
		EXPECT_NEAR(freqResp[7].gain.get(), 0, 0.005);
		EXPECT_NEAR(freqResp[8].gain.get(), 0.688, 0.005);
		EXPECT_NEAR(freqResp[9].gain.get(), 1.378, 0.005);
		EXPECT_NEAR(freqResp[10].gain.get(), 2.0698, 0.005);
		EXPECT_NEAR(freqResp[11].gain.get(), 2.7626, 0.005);
		EXPECT_NEAR(freqResp[12].gain.get(), 3.457, 0.005);
		EXPECT_NEAR(freqResp[13].gain.get(), -2.7626, 0.005);
		EXPECT_NEAR(freqResp[14].gain.get(), 0, 0.005);

		//calculate combined response
		freqGainTable1.resize(1024);
		freqGainTable2.resize(1024);
		for (UINT16 index = 0; index < 1024; index++)
		{
			freqGainTable1[index].gain.set(index * 0.2);
			freqGainTable2[index].gain.set(index * 0.4);
		}
		combineResp(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[0]), freqGainTable1, freqGainTable2);

		for (UINT16 index = 0; index < 1024; index++)
		{
			EXPECT_NEAR(freqGainTable1[index].gain.get(), (index * 0.6),0.01);
		}
	}

    TEST_F(TestTxEqTestCases, interpolate)
    {
    	//The interpolated values are calculated using: http://www.akiti.ca/CubicSpline.html

    	std::vector<EqPoint> freqResp;
    	std::vector<EqPoint> freqGainTable;
    	std::vector< std::shared_ptr<IEqualiser> > txEqualisers;
        for( unsigned index = 0; index < 4; index++)
        {
        	txEqualisers.push_back (  std::shared_ptr<IEqualiser>(new TxEqualiser( index,"TX_EQ")) );
        }

    	freqResp.resize(15);
    	freqResp[0].freq.set(-122880, Frequency::KHz);
    	freqResp[1].freq.set(-92160, Frequency::KHz);
    	for (int index = 2; index < 13; index++)
    	{
    		freqResp[index].freq.set(-50000 + ((index - 2) * 10000), Frequency::KHz);
    	}
    	freqResp[13].freq.set(92160, Frequency::KHz);
    	freqResp[14].freq.set(122880, Frequency::KHz);

    	for (int index = 0; index < 15; index++)
    	{
    		freqResp[index].gain.set(index);
    	}

    	freqGainTable.resize(1024);


    	interpolate(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[0]), freqResp, freqGainTable);

    	EXPECT_NEAR(freqGainTable[0].gain.get(), 0.0, 0.005);
    	EXPECT_NEAR(freqGainTable[1].gain.get(), 0.0203, 0.005);
    	EXPECT_NEAR(freqGainTable[50].gain.get(), 0.7182, 0.005);;
    	EXPECT_NEAR(freqGainTable[400].gain.get(), 4.3103, 0.005);
    	EXPECT_NEAR(freqGainTable[1022].gain.get(), 13.959, 0.005);
    	EXPECT_NEAR(freqGainTable[1023].gain.get(), 13.979, 0.005);

    }

    TEST_F(TestTxEqTestCases, calculateIfft)
    {
    	//The IFFT values are calculated using: http://scistatcalc.blogspot.com/2013/12/fft-calculator.html

    	std::complex<float> input[1024] = {0};
    	std::vector<EqPoint> freqGainTable;
    	std::vector< std::shared_ptr<IEqualiser> > txEqualisers;
        for( unsigned index = 0; index < 4; index++)
        {
        	txEqualisers.push_back (  std::shared_ptr<IEqualiser>(new TxEqualiser( index,"TX_EQ")) );
        }

    	freqGainTable.resize(1024);

    	for (int index = 0; index < 1024; index++)
    	{
    		freqGainTable[index].freq.set(-122880 + (index * 240), Frequency::KHz);
    		freqGainTable[index].gain.set(index/10.0);
    	}

		calculateIfft(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[0]), freqGainTable, input);

		EXPECT_NEAR(input[0].real(), 11117.53, 0.05);
		EXPECT_NEAR(input[0].imag(), 0, 0.05);

		EXPECT_NEAR(input[10].real(), 316.029, 5);
		EXPECT_NEAR(input[10].imag(), -2026.04, 5);

		EXPECT_NEAR(input[1022].real(), 5170.223, 5);
		EXPECT_NEAR(input[1022].imag(), 5579.38, 5);
    }

    TEST_F(TestTxEqTestCases, calculateTukey)
    {
    	std::vector<float> input;
    	std::vector< std::shared_ptr<IEqualiser> > txEqualisers;
        for( unsigned index = 0; index < 4; index++)
        {
        	txEqualisers.push_back (  std::shared_ptr<IEqualiser>(new TxEqualiser( index,"TX_EQ")) );
        }

    	tukeyWindow(std::dynamic_pointer_cast<TxEqualiser>(txEqualisers[1]), input);

    	EXPECT_NEAR(input[0], 0, 0.01);
    	EXPECT_NEAR(input[15], 0.006048, 0.01);
    	EXPECT_NEAR(input[106], 0.2733, 0.01);
    	EXPECT_NEAR(input[247], 0.9188, 0.01);
    	EXPECT_NEAR(input[302], 0.9999, 0.01);

    	for (int index = 303; index < 721; index++)
    	{
    		EXPECT_EQ(input[index], 1.0);
    	}

    	EXPECT_NEAR(input[1023], 0, 0.01);
    	EXPECT_NEAR(input[850], 0.6115, 0.01);
    	EXPECT_NEAR(input[788], 0.8816, 0.01);
    	EXPECT_NEAR(input[721], 0.9999, 0.01);
    }
} // Namespace

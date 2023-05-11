/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxRFBandTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "CommonTxRfBandConfig.h"
#include "IRfBandConfig.h"
#include "CommonTxRFBandTestCase.h"

using namespace std;

using namespace Mplane;


TestTxRfBandConfig::TestTxRfBandConfig()
{
	addTxRfBand(Frequency(250.0, Frequency::MHz),
				Frequency(1650.0, Frequency::MHz),
				Frequency(200.0, Frequency::MHz),
				Frequency(1800.0, Frequency::MHz),
				Frequency(3932.16, Frequency::MHz),
				1, 8,
				std::make_pair(10, 5),
				std::make_pair(2, 2));

	addTxRfBand(Frequency(1650.0, Frequency::MHz),
				Frequency(2500.0, Frequency::MHz),
				Frequency(1500.0, Frequency::MHz),
				Frequency(2700.0, Frequency::MHz),
				Frequency(2949.12, Frequency::MHz),
				2, 4,
				std::make_pair(13, 8),
				std::make_pair(4, 5));

}

TestTxRfBandConfig::~TestTxRfBandConfig()
{
}

std::shared_ptr<IRfBandConfig> IRfBandConfig::getTxSingleton()
{
    static std::shared_ptr<IRfBandConfig> rxRfBand( new TestTxRfBandConfig() );
    return rxRfBand;
}


/*
 * Unit test fixtures
 */
TEST_F(CommonTxRFBandTestCase, band1)
{
	cout << "CommonTxRFBandTestCase band 250 to 1650 MHz" << endl;

	std::shared_ptr<IRfBandConfig> tx ( IRfBandConfig::getTxSingleton() );

	//Frequency at lower limit for 250 to 1650 band
	ASSERT_TRUE(tx->getRfBandCenterMinFreq(Frequency(250.0, Frequency::MHz)) == Frequency(250.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandCenterMaxFreq(Frequency(250.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMinFreq(Frequency(250.0, Frequency::MHz)) == Frequency(200.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMaxFreq(Frequency(250.0, Frequency::MHz)) == Frequency(1800.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandSamplingFreq(Frequency(250.0, Frequency::MHz)) == Frequency(3932.16, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandNyquistZone(Frequency(250.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(tx->getRfBandDecimationFactor(Frequency(250.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(tx->getRfBandInterpolationFactor(Frequency(250.0, Frequency::MHz)) == 8);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(250.0, Frequency::MHz)).first == 10);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(250.0, Frequency::MHz)).second == 5);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(250.0, Frequency::MHz)).first == 2);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(250.0, Frequency::MHz)).second == 2);

	//Frequency between lower and upper limit for 250 to 1650 band
	ASSERT_TRUE(tx->getRfBandCenterMinFreq(Frequency(800.0, Frequency::MHz)) == Frequency(250.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandCenterMaxFreq(Frequency(800.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMinFreq(Frequency(800.0, Frequency::MHz)) == Frequency(200.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMaxFreq(Frequency(800.0, Frequency::MHz)) == Frequency(1800.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandSamplingFreq(Frequency(800.0, Frequency::MHz)) == Frequency(3932.16, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandNyquistZone(Frequency(800.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(tx->getRfBandDecimationFactor(Frequency(800.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(tx->getRfBandInterpolationFactor(Frequency(800.0, Frequency::MHz)) == 8);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(800.0, Frequency::MHz)).first == 10);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(800.0, Frequency::MHz)).second == 5);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(800.0, Frequency::MHz)).first == 2);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(800.0, Frequency::MHz)).second == 2);

	//Frequency at upper limit for 250 to 1650 band
	ASSERT_TRUE(tx->getRfBandCenterMinFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(250.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandCenterMaxFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMinFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(200.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMaxFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(1800.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandSamplingFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(3932.16, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandNyquistZone(Frequency(1650.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(tx->getRfBandDecimationFactor(Frequency(1650.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(tx->getRfBandInterpolationFactor(Frequency(1650.0, Frequency::MHz)) == 8);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(1650.0, Frequency::MHz)).first == 10);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(1650.0, Frequency::MHz)).second == 5);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(1650.0, Frequency::MHz)).first == 2);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(1650.0, Frequency::MHz)).second == 2);
}

TEST_F(CommonTxRFBandTestCase, band2)
{
	cout << "CommonTxRFBandTestCase band 1650 to 2500 MHz" << endl;

	std::shared_ptr<IRfBandConfig> tx ( IRfBandConfig::getTxSingleton() );

	//Frequency at lower limit for 1650 to 2500 band
	ASSERT_TRUE(tx->getRfBandCenterMinFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandCenterMaxFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(2500.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMinFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(1500.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMaxFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(2700.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandSamplingFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(2949.12, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandNyquistZone(Frequency(1650.1, Frequency::MHz)) == 2);
	ASSERT_TRUE(tx->getRfBandDecimationFactor(Frequency(1650.1, Frequency::MHz)) == 1);
	ASSERT_TRUE(tx->getRfBandInterpolationFactor(Frequency(1650.1, Frequency::MHz)) == 4);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(1650.1, Frequency::MHz)).first == 13);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(1650.1, Frequency::MHz)).second == 8);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(1650.1, Frequency::MHz)).first == 4);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(1650.1, Frequency::MHz)).second == 5);

	//Frequency between lower and upper limit for 1650 to 2500 band
	ASSERT_TRUE(tx->getRfBandCenterMinFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandCenterMaxFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(2500.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMinFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(1500.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMaxFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(2700.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandSamplingFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(2949.12, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandNyquistZone(Frequency(1800.0, Frequency::MHz)) == 2);
	ASSERT_TRUE(tx->getRfBandDecimationFactor(Frequency(1800.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(tx->getRfBandInterpolationFactor(Frequency(1800.0, Frequency::MHz)) == 4);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(1800.0, Frequency::MHz)).first == 13);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(1800.0, Frequency::MHz)).second == 8);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(1800.0, Frequency::MHz)).first == 4);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(1800.0, Frequency::MHz)).second == 5);

	//Frequency at upper limit for 1650 to 2500 band
	ASSERT_TRUE(tx->getRfBandCenterMinFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandCenterMaxFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(2500.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMinFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(1500.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandEdgeMaxFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(2700.0, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandSamplingFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(2949.12, Frequency::MHz));
	ASSERT_TRUE(tx->getRfBandNyquistZone(Frequency(2500.0, Frequency::MHz)) == 2);
	ASSERT_TRUE(tx->getRfBandDecimationFactor(Frequency(2500.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(tx->getRfBandInterpolationFactor(Frequency(2500.0, Frequency::MHz)) == 4);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(2500.0, Frequency::MHz)).first == 13);
	ASSERT_TRUE(tx->getRfBandMmcmRatio(Frequency(2500.0, Frequency::MHz)).second == 8);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(2500.0, Frequency::MHz)).first == 4);
	ASSERT_TRUE(tx->getRfBandResamplerRatio(Frequency(2500.0, Frequency::MHz)).second == 5);
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxRFBandTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "CommonRxRfBandConfig.h"
#include "IRfBandConfig.h"
#include "CommonRxRFBandTestCase.h"

using namespace std;

using namespace Mplane;


TestRxRfBandConfig::TestRxRfBandConfig()
{
	addRxRfBand(Frequency(250.0, Frequency::MHz),
				Frequency(1650.0, Frequency::MHz),
				Frequency(200.0, Frequency::MHz),
				Frequency(1800.0, Frequency::MHz),
				Frequency(3932.16, Frequency::MHz),
				1, 8,
				std::make_pair(10, 5),
				std::make_pair(2, 2));

	addRxRfBand(Frequency(1650.0, Frequency::MHz),
				Frequency(2500.0, Frequency::MHz),
				Frequency(1500.0, Frequency::MHz),
				Frequency(2700.0, Frequency::MHz),
				Frequency(2949.12, Frequency::MHz),
				2, 4,
				std::make_pair(13, 8),
				std::make_pair(4, 5));

}

TestRxRfBandConfig::~TestRxRfBandConfig()
{
}

std::shared_ptr<IRfBandConfig> IRfBandConfig::getRxSingleton()
{
    static std::shared_ptr<IRfBandConfig> rxRfBand( new TestRxRfBandConfig() );
    return rxRfBand;
}


/*
 * Unit test fixtures
 */
TEST_F(CommonRxRFBandTestCase, band1)
{
	cout << "CommonRxRFBandTestCase band 250 to 1650 MHz" << endl;

	std::shared_ptr<IRfBandConfig> rx ( IRfBandConfig::getRxSingleton() );

	//Frequency at lower limit for 250 to 1650 band
	ASSERT_TRUE(rx->getRfBandCenterMinFreq(Frequency(250.0, Frequency::MHz)) == Frequency(250.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandCenterMaxFreq(Frequency(250.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMinFreq(Frequency(250.0, Frequency::MHz)) == Frequency(200.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMaxFreq(Frequency(250.0, Frequency::MHz)) == Frequency(1800.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandSamplingFreq(Frequency(250.0, Frequency::MHz)) == Frequency(3932.16, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandNyquistZone(Frequency(250.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(rx->getRfBandDecimationFactor(Frequency(250.0, Frequency::MHz)) == 8);
	ASSERT_TRUE(rx->getRfBandInterpolationFactor(Frequency(250.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(250.0, Frequency::MHz)).first == 10);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(250.0, Frequency::MHz)).second == 5);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(250.0, Frequency::MHz)).first == 2);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(250.0, Frequency::MHz)).second == 2);

	//Frequency between lower and upper limit for 250 to 1650 band
	ASSERT_TRUE(rx->getRfBandCenterMinFreq(Frequency(800.0, Frequency::MHz)) == Frequency(250.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandCenterMaxFreq(Frequency(800.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMinFreq(Frequency(800.0, Frequency::MHz)) == Frequency(200.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMaxFreq(Frequency(800.0, Frequency::MHz)) == Frequency(1800.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandSamplingFreq(Frequency(800.0, Frequency::MHz)) == Frequency(3932.16, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandNyquistZone(Frequency(800.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(rx->getRfBandDecimationFactor(Frequency(800.0, Frequency::MHz)) == 8);
	ASSERT_TRUE(rx->getRfBandInterpolationFactor(Frequency(800.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(800.0, Frequency::MHz)).first == 10);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(800.0, Frequency::MHz)).second == 5);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(800.0, Frequency::MHz)).first == 2);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(800.0, Frequency::MHz)).second == 2);

	//Frequency at upper limit for 250 to 1650 band
	ASSERT_TRUE(rx->getRfBandCenterMinFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(250.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandCenterMaxFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMinFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(200.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMaxFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(1800.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandSamplingFreq(Frequency(1650.0, Frequency::MHz)) == Frequency(3932.16, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandNyquistZone(Frequency(1650.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(rx->getRfBandDecimationFactor(Frequency(1650.0, Frequency::MHz)) == 8);
	ASSERT_TRUE(rx->getRfBandInterpolationFactor(Frequency(1650.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(1650.0, Frequency::MHz)).first == 10);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(1650.0, Frequency::MHz)).second == 5);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(1650.0, Frequency::MHz)).first == 2);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(1650.0, Frequency::MHz)).second == 2);
}

TEST_F(CommonRxRFBandTestCase, band2)
{
	cout << "CommonRxRFBandTestCase band 1650 to 2500 MHz" << endl;

	std::shared_ptr<IRfBandConfig> rx ( IRfBandConfig::getRxSingleton() );

	//Frequency at lower limit for 1650 to 2500 band
	ASSERT_TRUE(rx->getRfBandCenterMinFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandCenterMaxFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(2500.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMinFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(1500.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMaxFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(2700.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandSamplingFreq(Frequency(1650.1, Frequency::MHz)) == Frequency(2949.12, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandNyquistZone(Frequency(1650.1, Frequency::MHz)) == 2);
	ASSERT_TRUE(rx->getRfBandDecimationFactor(Frequency(1650.1, Frequency::MHz)) == 4);
	ASSERT_TRUE(rx->getRfBandInterpolationFactor(Frequency(1650.1, Frequency::MHz)) == 1);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(1650.1, Frequency::MHz)).first == 13);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(1650.1, Frequency::MHz)).second == 8);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(1650.1, Frequency::MHz)).first == 4);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(1650.1, Frequency::MHz)).second == 5);

	//Frequency between lower and upper limit for 1650 to 2500 band
	ASSERT_TRUE(rx->getRfBandCenterMinFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandCenterMaxFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(2500.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMinFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(1500.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMaxFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(2700.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandSamplingFreq(Frequency(1800.0, Frequency::MHz)) == Frequency(2949.12, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandNyquistZone(Frequency(1800.0, Frequency::MHz)) == 2);
	ASSERT_TRUE(rx->getRfBandDecimationFactor(Frequency(1800.0, Frequency::MHz)) == 4);
	ASSERT_TRUE(rx->getRfBandInterpolationFactor(Frequency(1800.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(1800.0, Frequency::MHz)).first == 13);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(1800.0, Frequency::MHz)).second == 8);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(1800.0, Frequency::MHz)).first == 4);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(1800.0, Frequency::MHz)).second == 5);

	//Frequency at upper limit for 1650 to 2500 band
	ASSERT_TRUE(rx->getRfBandCenterMinFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(1650.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandCenterMaxFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(2500.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMinFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(1500.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandEdgeMaxFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(2700.0, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandSamplingFreq(Frequency(2500.0, Frequency::MHz)) == Frequency(2949.12, Frequency::MHz));
	ASSERT_TRUE(rx->getRfBandNyquistZone(Frequency(2500.0, Frequency::MHz)) == 2);
	ASSERT_TRUE(rx->getRfBandDecimationFactor(Frequency(2500.0, Frequency::MHz)) == 4);
	ASSERT_TRUE(rx->getRfBandInterpolationFactor(Frequency(2500.0, Frequency::MHz)) == 1);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(2500.0, Frequency::MHz)).first == 13);
	ASSERT_TRUE(rx->getRfBandMmcmRatio(Frequency(2500.0, Frequency::MHz)).second == 8);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(2500.0, Frequency::MHz)).first == 4);
	ASSERT_TRUE(rx->getRfBandResamplerRatio(Frequency(2500.0, Frequency::MHz)).second == 5);
}

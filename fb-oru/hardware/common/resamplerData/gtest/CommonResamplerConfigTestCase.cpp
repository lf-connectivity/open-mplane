/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonResamplerConfigTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "CommonResamplerConfigTestCase.h"

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "CommonResamplerConfig.h"
#include "IResamplerConfig.h"

using namespace std;

using namespace Mplane;


TestResamplerConfig::TestResamplerConfig()
{
	//Resampler 2,2
	createResampler(std::make_pair(2,2));
	addIbwData(std::make_pair(2,2), Frequency(100.0,Frequency::MHz), 6, {1.2, 2.3, 3.4});
	addIbwData(std::make_pair(2,2), Frequency(200.0,Frequency::MHz), 12, {11.2, 12.3, 13.4});
	addIbwData(std::make_pair(2,2), Frequency(400.0,Frequency::MHz), 20, {21.2, 22.3, 23.4});

	//Resampler 5,4
	createResampler(std::make_pair(5,4));
	addIbwData(std::make_pair(5,4), Frequency(100.0,Frequency::MHz), 5, {4,5,6,7});
	addIbwData(std::make_pair(5,4), Frequency(200.0,Frequency::MHz), 14, {8,9,10,11});
	addIbwData(std::make_pair(5,4), Frequency(400.0,Frequency::MHz), 8, {12,13,14,15});

}

TestResamplerConfig::~TestResamplerConfig()
{
}

std::shared_ptr<IResamplerConfig> IResamplerConfig::getTxSingleton()
{
    static std::shared_ptr<IResamplerConfig> resampler( new TestResamplerConfig() );
    return resampler;
}

std::shared_ptr<IResamplerConfig> IResamplerConfig::getRxSingleton()
{
    static std::shared_ptr<IResamplerConfig> resampler( new TestResamplerConfig() );
    return resampler;
}

/*
 * Unit test fixtures
 */
TEST_F(CommonResamplerConfigTestCase, resampler1)
{
	cout << "CommonResamplerConfigTestCase resampler 2,2" << endl;

	std::shared_ptr<IResamplerConfig> resampler ( IResamplerConfig::getTxSingleton() );

	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(2,2), Frequency(100.0, Frequency::MHz)) == 6);
	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(2,2), Frequency(200.0, Frequency::MHz)) == 12);
	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(2,2), Frequency(400.0, Frequency::MHz)) == 20);
	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(2,2), Frequency(300.0, Frequency::MHz)) == 0);

	std::vector<float> coeff = resampler->getResamplingCoefficients(std::make_pair(2,2), Frequency(100.0, Frequency::MHz));
	ASSERT_TRUE(coeff.size() == 3);
	EXPECT_NEAR(coeff[0], 1.2, 0.01);
	EXPECT_NEAR(coeff[1], 2.3, 0.01);
	EXPECT_NEAR(coeff[2], 3.4, 0.01);

	coeff = resampler->getResamplingCoefficients(std::make_pair(2,2), Frequency(200.0, Frequency::MHz));
	ASSERT_TRUE(coeff.size() == 3);
	EXPECT_NEAR(coeff[0], 11.2, 0.01);
	EXPECT_NEAR(coeff[1], 12.3, 0.01);
	EXPECT_NEAR(coeff[2], 13.4, 0.01);

	coeff = resampler->getResamplingCoefficients(std::make_pair(2,2), Frequency(400.0, Frequency::MHz));
	ASSERT_TRUE(coeff.size() == 3);
	EXPECT_NEAR(coeff[0], 21.2, 0.01);
	EXPECT_NEAR(coeff[1], 22.3, 0.01);
	EXPECT_NEAR(coeff[2], 23.4, 0.01);

	coeff = resampler->getResamplingCoefficients(std::make_pair(2,2), Frequency(300.0, Frequency::MHz));
	ASSERT_TRUE(coeff.size() == 0);

}

TEST_F(CommonResamplerConfigTestCase, resampler2)
{
	cout << "CommonResamplerConfigTestCase resampler 5,4" << endl;

	std::shared_ptr<IResamplerConfig> resampler ( IResamplerConfig::getTxSingleton() );

	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(5,4), Frequency(100.0, Frequency::MHz)) == 5);
	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(5,4), Frequency(200.0, Frequency::MHz)) == 14);
	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(5,4), Frequency(400.0, Frequency::MHz)) == 8);
	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(5,4), Frequency(300.0, Frequency::MHz)) == 0);

	std::vector<float> coeff = resampler->getResamplingCoefficients(std::make_pair(5,4), Frequency(100.0, Frequency::MHz));
	ASSERT_TRUE(coeff.size() == 4);
	EXPECT_NEAR(coeff[0], 4, 0.01);
	EXPECT_NEAR(coeff[1], 5, 0.01);
	EXPECT_NEAR(coeff[2], 6, 0.01);
	EXPECT_NEAR(coeff[3], 7, 0.01);

	coeff = resampler->getResamplingCoefficients(std::make_pair(5,4), Frequency(200.0, Frequency::MHz));
	ASSERT_TRUE(coeff.size() == 4);
	EXPECT_NEAR(coeff[0], 8, 0.01);
	EXPECT_NEAR(coeff[1], 9, 0.01);
	EXPECT_NEAR(coeff[2], 10, 0.01);
	EXPECT_NEAR(coeff[3], 11, 0.01);

	coeff = resampler->getResamplingCoefficients(std::make_pair(5,4), Frequency(400.0, Frequency::MHz));
	ASSERT_TRUE(coeff.size() == 4);
	EXPECT_NEAR(coeff[0], 12, 0.01);
	EXPECT_NEAR(coeff[1], 13, 0.01);
	EXPECT_NEAR(coeff[2], 14, 0.01);
	EXPECT_NEAR(coeff[3], 15, 0.01);

	coeff = resampler->getResamplingCoefficients(std::make_pair(5,4), Frequency(300.0, Frequency::MHz));
	ASSERT_TRUE(coeff.size() == 0);
}

TEST_F(CommonResamplerConfigTestCase, resamplerNotFound)
{
	cout << "CommonResamplerConfigTestCase resampler not found" << endl;

	std::shared_ptr<IResamplerConfig> resampler ( IResamplerConfig::getTxSingleton() );

	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(9,8), Frequency(100.0, Frequency::MHz)) == 0);
	ASSERT_TRUE(resampler->getClockPerSample(std::make_pair(4,5), Frequency(200.0, Frequency::MHz)) == 0);
}

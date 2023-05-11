/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxFrequencyConstantTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "CommonRxFrequencyConst.h"
#include "CommonRxFrequencyConstTestCase.h"

#include "IFrequencyConst.h"

using namespace std;

using namespace Mplane;


TestRxFreqConst::TestRxFreqConst()
{
    mFilterMinimum = 1710000000ULL;
    mFilterMaximum = 1770000000ULL;
    m3GMinimum = 1710000000ULL;
    m3GMaximum = 1770000000ULL;
    mMinimum = m3GMinimum;
    mMaximum = m3GMaximum;
//    mIFCentre = 168960000U;
//    mLOMinimum = mMinimum - mIFCentre;
//    mLOMaximum = mMaximum + mIFCentre;
//    mRFLOResolution = 50000U;
//    mNCOAdjustment = 0U;
    mBandwidth = 4480000ULL;
//    mNarrowBandIFFilterBandwidth = 5000000U;
    mRaster = 10000ULL;
//    mIFBandwidth = 15000000U;
//    mLOSeparation = 1000000U;
    mCarrierFlip = HIGHSIDE;
    mLOInjection = HIGHSIDE;
    mNumberOfRFLO = 2;

}

TestRxFreqConst::~TestRxFreqConst()
{
}

std::shared_ptr<IRxFrequencyConst> IRxFrequencyConstFactory::getInterface()
{
    static std::shared_ptr<IRxFrequencyConst> rxfreq( new TestRxFreqConst() );
    return rxfreq;
}

/*
 * Unit tests
 */
void CommonRxFrequencyConstTestCase::unittest()
{
    cout << "CommonRxFrequencyConstantsTestCase unit test" << endl;

    std::shared_ptr<IRxFrequencyConst> rx ( IRxFrequencyConstFactory::getInterface() );

     ASSERT_TRUE(rx->getFilterMinimum() == 1710000000U);
     ASSERT_TRUE(rx->getFilterMaximum() == 1770000000U);
     ASSERT_TRUE(rx->get3GMinimum() == 1710000000U);
     ASSERT_TRUE(rx->get3GMaximum() == 1770000000U);
     ASSERT_TRUE(rx->getMinimum() == 1710000000U);
     ASSERT_TRUE(rx->getMaximum() == 1770000000U);
//     ASSERT_TRUE(rx->getIFCentre() == 168960000U);
//     ASSERT_TRUE(rx->getLOMinimum() == 1541040000U);
//     ASSERT_TRUE(rx->getLOMaximum() == 1938960000U);
//     ASSERT_TRUE(rx->getRFLOResolution() == 50000U);
//     ASSERT_TRUE(rx->getNCOAdjustment() == 0U);
     ASSERT_TRUE(rx->getBandwidth() == 4480000U);
//     ASSERT_TRUE(rx->getNarrowBandIFFilterBandwidth() == 5000000U);
     ASSERT_TRUE(rx->getRaster() == 10000U);
//     ASSERT_TRUE(rx->getIFBandwidth() == 15000000U);
//     ASSERT_TRUE(rx->getLOSeparation() == 1000000U);
     ASSERT_TRUE(rx->getCarrierFlip() == 1);
     ASSERT_TRUE(rx->getLOInjection() == 1);
     ASSERT_TRUE(rx->getNumberOfRFLO() == 2);

     TestRxFreqConst* test = new TestRxFreqConst();

     delete test;

}

/*
 * Unit test fixtures
 */
TEST_F(CommonRxFrequencyConstTestCase, unittest)
{
    unittest();
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxFrequencyXonstantTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "CommonTxFrequencyConst.h"
#include "CommonTxFrequencyConstTestCase.h"

#include "IFrequencyConst.h"

using namespace std;

using namespace Mplane;

TestTxFreqConst::TestTxFreqConst()
{
    m3GMinimum = 2110000000ULL;
    m3GMaximum = 2170000000ULL;
    mFilterMinimum = 2110000000ULL;
    mFilterMaximum = 2170000000ULL;
    mMinimum = m3GMinimum;
    mMaximum = m3GMaximum;
//    mIFCentre = 263520000U;
//    mLOMinimum = mMinimum - mIFCentre;
//    mLOMaximum = mMaximum - mIFCentre;
//    mIFBandwidth = 15000000U;
//    mRFLOResolution = 200000U;
    mBandwidth = 4480000ULL;
//    mIFResolution = 720000U;
    mRaster = 10000ULL;
    mCarrierFlip = HIGHSIDE;
    mLOInjection = LOWSIDE;
}

TestTxFreqConst::~TestTxFreqConst()
{

}




std::shared_ptr<ITxFrequencyConst> ITxFrequencyConstFactory::getInterface()
{
    static std::shared_ptr<ITxFrequencyConst> txfreq( new TestTxFreqConst() );
    return txfreq;

}



/*
 * Unit tests
 */
void CommonTxFrequencyConstTestCase::unittest()
{
    cout << "CommonTxFrequencyConstantsTestCase unit test" << endl;

    std::shared_ptr<ITxFrequencyConst> tx( ITxFrequencyConstFactory::getInterface() );

    ASSERT_TRUE(tx->get3GMinimum() == 2110000000U);
    ASSERT_TRUE(tx->get3GMaximum() == 2170000000U);
    ASSERT_TRUE(tx->getFilterMinimum() == 2110000000U);
    ASSERT_TRUE(tx->getFilterMaximum() == 2170000000U);
    ASSERT_TRUE(tx->getMinimum() == 2110000000U);
    ASSERT_TRUE(tx->getMaximum() == 2170000000U);
//    ASSERT_TRUE(tx->getIFCentre() == 263520000U);
//    ASSERT_TRUE(tx->getLOMinimum() == 1846480000U);
//    ASSERT_TRUE(tx->getLOMaximum() == 1906480000U);
//    ASSERT_TRUE(tx->getIFBandwidth() == 15000000U);
//    ASSERT_TRUE(tx->getRFLOResolution() == 200000U);
    ASSERT_TRUE(tx->getBandwidth() == 4480000U);
//    ASSERT_TRUE(tx->getDigitalIFResolution() == 720000U);
    ASSERT_TRUE(tx->getRaster() == 10000U);
    ASSERT_TRUE(tx->getCarrierFlip() == 1);
    ASSERT_TRUE(tx->getLOInjection() == -1);


    TestTxFreqConst* test = new TestTxFreqConst();
    delete test;

}

/*
 * Unit test fixtures
 */
TEST_F(CommonTxFrequencyConstTestCase, unittest)
{
    unittest();
}

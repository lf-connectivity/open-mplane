/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierModelTestCase.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string>
#include <iostream>
#include <vector>

#include <numeric>
#include <functional>
#include <algorithm>

#include "ICarrier.h"
#include "ICarrierHardware.h"
#include "CommonCarrier.h"
#include "CommonCarrierHardware.h"
#include "CommonCarrierModel.h"
#include "CommonCarrierHardwareTestCase.h"


using namespace std;
using namespace Mplane;

//------------------------------------------------------------------------------------------------------------------------

class CarrierHardwareTest : public CommonCarrierHardware
{
public:
	CarrierHardwareTest(const ICarrier *carrier = 0) :
		mCarrier(carrier),
    	mTarget_pwr_mW(0)
    {
//		unsigned power = mCarrier->getTxPower() ;
    }

    virtual bool validateChange(const ICarrier &carrier) { return true; }
    virtual bool carrierChange(const ICarrier &carrier) { return true; }
    virtual const bool isChanged() const { return true; }
    virtual bool preUpdate() { return true; }
    virtual bool updateHardware() { return true; }
    virtual bool postUpdate() { return true; }
    virtual void changeComplete() { }
    virtual void settingsChanged() {  }
    void showCarrier(void) const {}
    Power getPower(unsigned txpath) const { return Power(0.0); }
    Frequency getMinTxFreq() const { return Frequency(0.0); }
    Frequency getMaxTxFreq() const { return Frequency(0.0); }
    unsigned getDlDelay( unsigned antenna ) const { return 0; }
    unsigned getUlDelay( unsigned antenna ) const { return 0; }
    unsigned getUlAdditionalDelay( unsigned antenna ) const { return 0; }
    virtual bool resyncUlStream( unsigned path ) { return true; }
    virtual bool resyncDlStream( unsigned path ) { return true; }


    virtual ~CarrierHardwareTest() {} ;

	const CarrierHardwareTest sum_target(const CarrierHardwareTest &a)
	{
//		cout << "this=" << mTarget_pwr_mW << ", a=" << a.mTarget_pwr_mW << endl;
		CarrierHardwareTest c = CarrierHardwareTest() ;
		c.mTarget_pwr_mW = mTarget_pwr_mW + a.mTarget_pwr_mW ;
		return c ;
	}

    std::string mFailureReason ;
    virtual std::string failReason(void)
    {
    	std::string reason("") ;
    	swap(mFailureReason, reason) ;
    	return reason ;
    }
    virtual void setFailReason(std::string reason)
    {
    	mFailureReason = reason ;
    }
    virtual void clearFailReason()
    {
    	mFailureReason = "" ;
    }

	bool txFrequencyChange(unsigned antenna,
			const Frequency& newTxFrequency) {
		return true ;
	}

	bool rxFrequencyChange(unsigned antenna,
			const Frequency& newRxFrequency) {
		return true ;
	}

//private:
	const ICarrier *mCarrier ;
	unsigned mTarget_pwr_mW ;

};


//------------------------------------------------------------------------------------------------------------------------
/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonCarrierHardwareTestCase );


//------------------------------------------------------------------------------------------------------------------------
/*
 * Unit tests
 */
void CommonCarrierHardwareTestCase::unittest()
{
    cout << "CommonCarrierHardwareTestCase unit test" << endl;

    std::vector<CarrierHardwareTest> hw ;

    CarrierHardwareTest a ;
    a.mTarget_pwr_mW = 10 ;
    hw.push_back(a) ;

    CarrierHardwareTest b ;
    b.mTarget_pwr_mW = 15 ;
    hw.push_back(b) ;

    CarrierHardwareTest c ;
    c.mTarget_pwr_mW = 20 ;
    hw.push_back(c) ;

    CarrierHardwareTest e = accumulate(hw.begin(), hw.end(), CarrierHardwareTest(), mem_fun_ref(&CarrierHardwareTest::sum_target)) ;
    CPPUNIT_ASSERT_EQUAL(45u, e.mTarget_pwr_mW) ;

}

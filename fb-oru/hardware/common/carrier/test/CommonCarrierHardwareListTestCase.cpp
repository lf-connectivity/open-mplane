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

#include "CommonCarrierHardwareListTestCase.h"


using namespace std;
using namespace Mplane;

//------------------------------------------------------------------------------------------------------------------------
static bool gDebug = false ;

//------------------------------------------------------------------------------------------------------------------------

class CarrierHardware2 : public ICarrierHardware
{
public:
    /**
     *
     */
	CarrierHardware2(const ICarrier *carrier = 0) :
		mCarrier(carrier),
    	mTarget_pwr_mW(0),

    	mName(""),
    	mOk(true),
    	mPreCount(0),
    	mCompleteCount(0)
    {
		if (gDebug) cerr << __func__ << endl ;
//		cout << "Created CarrierHardware2 - carrier = " << carrier << endl ;
    }

    virtual const ICarrier& getCarrier() const {
    	return *mCarrier ;
    }

    virtual bool validateChange(const ICarrier &carrier) {
    	if (gDebug) cerr << __func__ << endl ;
    	return mOk;
    }
    virtual bool carrierChange(const ICarrier &carrier) {
    	if (gDebug) cerr << __func__ << endl ;
    	return mOk;
    }
    virtual const bool isChanged() const {
    	if (gDebug) cerr << __func__ << endl ;
    	return true;
    }
    virtual bool preUpdate() {
		++mPreCount ;
		if (gDebug) cerr << "preUpdate(" << mName << ") " << this << " target=" << mTarget_pwr_mW << " carrier=" << mCarrier << " count=" << mPreCount << endl ;
    	return mOk;
    }
    virtual bool updateHardware() {
    	if (gDebug) cerr << __func__ << endl ;
    	return mOk;
    }
    virtual bool postUpdate() {
    	if (gDebug) cerr << __func__ << endl ;
    	return mOk;
    }
    virtual void changeComplete() {
    	if (gDebug) cerr << __func__ << endl ;
    	++mCompleteCount ;
    }
    virtual void settingsChanged() {
    	if (gDebug) cerr << __func__ << endl ;
    }


    void setTarget(const unsigned target) {
    	if (gDebug) cerr << __func__ << endl ;
    	mTarget_pwr_mW = target;
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

    void showCarrier(std::ostream& os = std::cout) const {
    	os << "Show carrier hardware" << std::endl ;
    }
    void showDiag(std::ostream& os = std::cout) const {
    }

    Power getPower(unsigned txpath) const { return Power(0.0); }
    Frequency getMinTxFreq() const { return Frequency(0.0); }
    Frequency getMaxTxFreq() const { return Frequency(0.0); }

    unsigned getDlDelay( unsigned antenna ) const { return 0; }
    unsigned getUlDelay( unsigned antenna ) const { return 0; }
    unsigned getUlAdditionalDelay( unsigned antenna ) const { return 0; }

    virtual bool resyncUlStream( unsigned path ) { return true; }
    virtual bool resyncDlStream( unsigned path ) { return true; }

    virtual bool getRssi(unsigned antenna, Power& rssi) const override { rssi=Power(0.0); return true; }

    virtual Frequency getChbwFreq() const override { return Frequency(0.0); }
    virtual Frequency getTxFreq() const override { return Frequency(0.0); }


    /*! @brief  Destructor
     *
     *  Allow destruction through the interface
     */
    virtual ~CarrierHardware2()
    {
//    	cout << "destroy() this=" << this << " target=" << mTarget_pwr_mW << ", carrier=" << mCarrier << endl;
    }


	const CarrierHardware2 summariseEnabledOnTx(const CarrierHardware2& b, const unsigned txpath) const
	{
		if (gDebug)
		{
		cerr << "summariseEnabledOnTx() " << this << " target=" << mTarget_pwr_mW << " carrier=" << mCarrier <<
				" txpath=" << txpath <<
				", b=" << &b << " b carrier=" << b.mCarrier << endl ;
		cerr <<	" b enabled=" << (b.mCarrier ? CarrierUtils::isEnabled(b.mCarrier) : false) <<
				" b tx=" << (b.mCarrier ? b.mCarrier->isTx(txpath) : false) <<
				endl;
		}

		if (!b.mCarrier || !CarrierUtils::isEnabled(b.mCarrier))
			return *this ;

		// check tx path
		if (!b.mCarrier->isTx(txpath))
			return *this ;

		CarrierHardware2 c = CarrierHardware2() ;
		c.mTarget_pwr_mW = mTarget_pwr_mW + b.mTarget_pwr_mW ;

//		cerr << "summariseEnabledOnTx() " << " target=" << mTarget_pwr_mW << ", b=" << b.mTarget_pwr_mW << endl;
		return c ;
	}

	const CarrierHardware2 summarise(const CarrierHardware2& b) const
	{
		if (gDebug)
		{
		cerr << "summarise() " << this << " target=" << mTarget_pwr_mW << " carrier=" << mCarrier <<
				", b=" << &b << " b carrier=" << b.mCarrier << endl ;
		cerr <<	" b enabled=" << (b.mCarrier ? CarrierUtils::isEnabled(b.mCarrier) : false) <<
				endl;
		}

		CarrierHardware2 c = CarrierHardware2() ;
		c.mTarget_pwr_mW = mTarget_pwr_mW + b.mTarget_pwr_mW ;

//		cerr << "summarise() " << " target=" << mTarget_pwr_mW << ", b=" << b.mTarget_pwr_mW << endl;
		return c ;
	}


	const CarrierHardware2 offsetTarget(const unsigned offset) const
	{
		if (gDebug)
			cerr << "offsetTarget() " << this << " target=" << mTarget_pwr_mW << " carrier=" << mCarrier << endl;
		CarrierHardware2 ch(*this) ;
		ch.mTarget_pwr_mW += offset ;
		return ch ;
	}



	const bool isEnabledOnTx(const unsigned txpath) const
	{
		if (gDebug)
		{
		cerr << "isEnabledOnTx() " << this << " target=" << mTarget_pwr_mW << " carrier=" << mCarrier << endl ;
		}

		// check enabled
		if (!mCarrier || !CarrierUtils::isEnabled(mCarrier))
			return false ;

		// check tx path
		if (!mCarrier->isTx(txpath))
			return false ;

		return true ;
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

	std::string mName ;
	bool mOk ;

	unsigned mPreCount ;
	unsigned mCompleteCount ;

};

//------------------------------------------------------------------------------------------------------------------------
class CarrierHardwareList : public CommonCarrierHardwareList<CarrierHardware2>
{
public:
	CarrierHardwareList() : CommonCarrierHardwareList<CarrierHardware2>() {}
	virtual ~CarrierHardwareList() {}

};

// Provide factory method to be able to get singleton instance of this model
std::shared_ptr<ICarrierHardwareList> ICarrierHardwareList::getInstance()
{
	static std::shared_ptr<ICarrierHardwareList> hwlist( new CarrierHardwareList() );
	return hwlist ;
}




//------------------------------------------------------------------------------------------------------------------------
/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonCarrierHardwareListTestCase );


//------------------------------------------------------------------------------------------------------------------------
/*
 * Unit tests
 */
void CommonCarrierHardwareListTestCase::unittest()
{
    cout << "CommonCarrierHardwareListTestCase" << endl;
    cout << __func__ << endl;

    CarrierHardwareList cl ;
    CarrierHardware2* ch ;

    CommonCarrier ca(1, 2, 2) ;
    cl.addCarrier(ca) ;
    ch = cl.getCarrierHardware(1) ;
    ch->setTarget(10) ;

    CommonCarrier cb(2, 2, 2) ;
    cl.addCarrier(cb) ;
    ch = cl.getCarrierHardware(2) ;
    ch->setTarget(15) ;

    CommonCarrier cc(3, 2, 2) ;
    cl.addCarrier(cc) ;
    ch = cl.getCarrierHardware(3) ;
    ch->setTarget(20) ;

    CommonCarrier cd(4, 2, 2) ;
    cl.addCarrier(cd) ;
    ch = cl.getCarrierHardware(4) ;
    ch->setTarget(30) ;

    if (gDebug)
    {
		ch = cl.getCarrierHardware(1) ;
		cout << "CarrierHardware2[1] = " << ch << " target=" << ch->mTarget_pwr_mW << " carrier=" << ch->mCarrier << endl ;
		ch = cl.getCarrierHardware(2) ;
		cout << "CarrierHardware2[2] = " << ch << " target=" << ch->mTarget_pwr_mW << " carrier=" << ch->mCarrier <<  endl ;
		ch = cl.getCarrierHardware(3) ;
		cout << "CarrierHardware2[3] = " << ch << " target=" << ch->mTarget_pwr_mW << " carrier=" << ch->mCarrier <<  endl ;
		ch = cl.getCarrierHardware(4) ;
		cout << "CarrierHardware2[4] = " << ch << " target=" << ch->mTarget_pwr_mW << " carrier=" << ch->mCarrier <<  endl ;

		cout << "-------------------\n" ;
    }


    CarrierHardware2 summary ;

    // None enabled

    // Test an all-in-one call
    summary = cl.summariseList(carrier_hardware_summarise_bind(&CarrierHardware2::summariseEnabledOnTx, 1u)) ;
    CPPUNIT_ASSERT_EQUAL(0u, summary.mTarget_pwr_mW) ;

    // test separate predicate with arg
    summary = cl.summariseList(carrier_hardware_summarise_bind(&CarrierHardware2::summarise, &CarrierHardware2::isEnabledOnTx, 1u)) ;
    CPPUNIT_ASSERT_EQUAL(0u, summary.mTarget_pwr_mW) ;


//    cout << "-------------------\n" ;
    ca.setState(ICarrier::STATE_ENABLE) ;
    cb.setState(ICarrier::STATE_ENABLE) ;
    cc.setState(ICarrier::STATE_ENABLE) ;
    cd.setState(ICarrier::STATE_ENABLE) ;

    ca.setTxContainer(1, 2) ;
    cb.setTxContainer(1, 2) ;
    cc.setTxContainer(1, 2) ;
    cd.setTxContainer(0, 2) ;

    ca.setTxFrequency(5000ULL) ;
    cb.setTxFrequency(5000ULL) ;
    cc.setTxFrequency(5000ULL) ;
    cd.setTxFrequency(5000ULL) ;
//    cout << "ca " << &ca << " enabled=" << ca.isEnabled() << endl ;

    summary = cl.summariseList(carrier_hardware_summarise_bind(&CarrierHardware2::summariseEnabledOnTx, 1u)) ;
    CPPUNIT_ASSERT_EQUAL(45u, summary.mTarget_pwr_mW) ;

    // test separate predicate with arg
	summary = cl.summariseList(carrier_hardware_summarise_bind(&CarrierHardware2::summarise, &CarrierHardware2::isEnabledOnTx, 1u)) ;
    CPPUNIT_ASSERT_EQUAL(45u, summary.mTarget_pwr_mW) ;
//	cout << "Sum =" << summary.mTarget_pwr_mW << endl ;


	//-------------------------------
    std::vector<CarrierHardware2> hl ;
	ch = cl.getCarrierHardware(1) ;
	hl.push_back(*ch) ;
	ch = cl.getCarrierHardware(2) ;
	hl.push_back(*ch) ;
	ch = cl.getCarrierHardware(3) ;
	hl.push_back(*ch) ;
	ch = cl.getCarrierHardware(4) ;
	hl.push_back(*ch) ;

	CPPUNIT_ASSERT_EQUAL(10u, hl[0].mTarget_pwr_mW) ;
	CPPUNIT_ASSERT_EQUAL(15u, hl[1].mTarget_pwr_mW) ;
	CPPUNIT_ASSERT_EQUAL(20u, hl[2].mTarget_pwr_mW) ;
	CPPUNIT_ASSERT_EQUAL(30u, hl[3].mTarget_pwr_mW) ;


//	std::transform(hl.begin(), hl.end(), hl.begin(), mem_fun_ref(&CarrierHardware2::offsetTarget)) ;
	std::transform(hl.begin(), hl.end(), hl.begin(), carrier_hardware_transform_bind(&CarrierHardware2::offsetTarget, 10u)) ;

	CPPUNIT_ASSERT_EQUAL(20u, hl[0].mTarget_pwr_mW) ;
	CPPUNIT_ASSERT_EQUAL(25u, hl[1].mTarget_pwr_mW) ;
	CPPUNIT_ASSERT_EQUAL(30u, hl[2].mTarget_pwr_mW) ;
	CPPUNIT_ASSERT_EQUAL(40u, hl[3].mTarget_pwr_mW) ;

//	std::for_each(hl.begin(), hl.end(), myclass() ) ;
	std::for_each(hl.begin(), hl.end(), carrier_hardware_foreach_bind(&CarrierHardware2::preUpdate)) ;


	//-------------------------------
	ch = cl.getCarrierHardware(1) ;
	CPPUNIT_ASSERT_EQUAL(10u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(2) ;
	CPPUNIT_ASSERT_EQUAL(15u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(3) ;
	CPPUNIT_ASSERT_EQUAL(20u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(4) ;
	CPPUNIT_ASSERT_EQUAL(30u, ch->mTarget_pwr_mW) ;

    cl.transformList(carrier_hardware_transform_bind(&CarrierHardware2::offsetTarget, 10u)) ;

	ch = cl.getCarrierHardware(1) ;
	CPPUNIT_ASSERT_EQUAL(20u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(2) ;
	CPPUNIT_ASSERT_EQUAL(25u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(3) ;
	CPPUNIT_ASSERT_EQUAL(30u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(4) ;
	CPPUNIT_ASSERT_EQUAL(40u, ch->mTarget_pwr_mW) ;

	//-------------------------------
	// do it again but only offset TX 1
	ch = cl.getCarrierHardware(1) ;
	CPPUNIT_ASSERT_EQUAL(20u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(2) ;
	CPPUNIT_ASSERT_EQUAL(25u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(3) ;
	CPPUNIT_ASSERT_EQUAL(30u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(4) ;
	CPPUNIT_ASSERT_EQUAL(40u, ch->mTarget_pwr_mW) ;

    cl.transformList(carrier_hardware_transform_bind(&CarrierHardware2::offsetTarget, 5u, &CarrierHardware2::isEnabledOnTx, 1u)) ;

	ch = cl.getCarrierHardware(1) ;
	CPPUNIT_ASSERT_EQUAL(25u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(2) ;
	CPPUNIT_ASSERT_EQUAL(30u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(3) ;
	CPPUNIT_ASSERT_EQUAL(35u, ch->mTarget_pwr_mW) ;
	ch = cl.getCarrierHardware(4) ;
	CPPUNIT_ASSERT_EQUAL(40u, ch->mTarget_pwr_mW) ;

//    cl.foreachList(carrier_hardware_transform_bind(&CarrierHardware2::preUpdate, &CarrierHardware2::isChanged)) ;
}



//////////////////////////////////////////////////////////////////////////////////////////////////

////------------------------------------------------------------------------------------------------------------------------------
///**
// * @brief Bind a carrier hardware object member function with 1 argument
// *
// * Converts an ICarrierHardware member function into a function suitable for running in std::for_each, binding
// * a single argument
// *
// * @param fn The member function
// * @param arg1 the argument
// * @return a unary operation usable in STL algorithms
// */
//template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
//class XXX_ch_foreach_bind1_t : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
//{
//public:
//  explicit XXX_ch_foreach_bind1_t(_TFunRet (_TCarrierHardware::*fn)(const _TArg1& arg1), const _TArg1& arg1)
//  : mFn(fn),
//    mArg1(arg1)
//  {
//  }
//
//  _TCarrierHardware& operator()(_TCarrierHardware& a)
//  {
//	  (a.*mFn)(mArg1);
//	  return a ;
//  }
//
//private:
//  _TFunRet (_TCarrierHardware::*mFn)(const _TArg1& arg1) ;
//  const _TArg1& mArg1 ;
//};
//
//template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
//	inline XXX_ch_foreach_bind1_t<_TCarrierHardware, _TArg1, _TFunRet>
//XXX_carrier_hardware_foreach_bind1(_TFunRet (_TCarrierHardware::*fn)(const _TArg1& arg1), const _TArg1& arg1)
//	{
//		return XXX_ch_foreach_bind1_t<_TCarrierHardware, _TArg1, _TFunRet>(fn, arg1);
//	}
//
//
//template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
//class XXX_ch_foreach_bind1_nonconst_t : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
//{
//public:
//  explicit XXX_ch_foreach_bind1_nonconst_t(_TFunRet (_TCarrierHardware::*fn)(_TArg1& arg1), _TArg1& arg1)
//  : mFn(fn),
//    mArg1(arg1)
//  {
//  }
//
//  _TCarrierHardware& operator()(_TCarrierHardware& a)
//  {
//	  (a.*mFn)(mArg1);
//	  return a ;
//  }
//
//private:
//  _TFunRet (_TCarrierHardware::*mFn)(_TArg1& arg1) ;
//  _TArg1& mArg1 ;
//};
//
//template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
//	inline XXX_ch_foreach_bind1_nonconst_t<_TCarrierHardware, _TArg1, _TFunRet>
//XXX_carrier_hardware_foreach_bind1(_TFunRet (_TCarrierHardware::*fn)(_TArg1& arg1), _TArg1& arg1)
//	{
//		return XXX_ch_foreach_bind1_nonconst_t<_TCarrierHardware, _TArg1, _TFunRet>(fn, arg1);
//	}


// unary_function<Arg, Result>
template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
class XXX_ch_foreach_const_bind1_nonconst_t : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
{
public:
  explicit XXX_ch_foreach_const_bind1_nonconst_t(_TFunRet (_TCarrierHardware::*fn)(_TArg1& arg1) const, _TArg1& arg1)
  : mFn(fn),
    mArg1(arg1)
  {
  }

  _TCarrierHardware& operator()(_TCarrierHardware& a)
  {
	  (a.*mFn)(mArg1);
	  return a ;
  }

private:
  _TFunRet (_TCarrierHardware::*mFn)(_TArg1& arg1) const ;
  _TArg1& mArg1 ;
};

template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
	inline XXX_ch_foreach_const_bind1_nonconst_t<_TCarrierHardware, _TArg1, _TFunRet>
XXX_carrier_hardware_foreach_bind1(_TFunRet (_TCarrierHardware::*fn)(_TArg1& arg1) const, _TArg1& arg1)
	{
		return XXX_ch_foreach_const_bind1_nonconst_t<_TCarrierHardware, _TArg1, _TFunRet>(fn, arg1);
	}



//template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
//	bool XXX_carrier_hardware_foreach_bind1(_TFunRet (_TCarrierHardware::*fn)(_TArg1& arg1), _TArg1& arg1)
//	{
//		return true ;
//	}
//
//template <typename _TCarrierHardware, typename _TFunRet>
//	bool XXX_carrier_hardware_foreach_bind0(_TFunRet (_TCarrierHardware::*fn)(void) const)
//	{
//		return true ;
//	}
//
//template <typename _TCarrierHardware, typename _TFunRet>
//	bool XXX_carrier_hardware_foreach_bind0(_TFunRet (_TCarrierHardware::*fn)(void) )
//	{
//		return true ;
//	}



//------------------------------------------------------------------------------------------------------------------------
/*
 * Unit tests
 */
void CommonCarrierHardwareListTestCase::foreach_test()
{
    cout << "CommonCarrierHardwareListTestCase" << endl;
    cout << __func__ << endl;

    CarrierHardwareList cl ;
    CarrierHardware2* ch ;

    std::vector<CarrierHardware2*> chvec ;
    std::vector<CarrierHardware2> chvec2 ;

    CommonCarrier ca(1, 2, 2) ;
    cl.addCarrier(ca) ;
    ch = cl.getCarrierHardware(1) ;
    ch->mName = std::string("ch-a") ;
    chvec.push_back(ch) ;
    chvec2.push_back(*ch) ;

    CommonCarrier cb(2, 2, 2) ;
    cl.addCarrier(cb) ;
    ch = cl.getCarrierHardware(2) ;
    ch->mName = std::string("ch-b") ;
    chvec.push_back(ch) ;
    chvec2.push_back(*ch) ;

    CommonCarrier cc(3, 2, 2) ;
    cl.addCarrier(cc) ;
    ch = cl.getCarrierHardware(3) ;
    ch->mName = std::string("ch-c") ;
    chvec.push_back(ch) ;
    chvec2.push_back(*ch) ;

    CommonCarrier cd(4, 2, 2) ;
    cl.addCarrier(cd) ;
    ch = cl.getCarrierHardware(4) ;
    ch->mName = std::string("ch-d") ;
    chvec.push_back(ch) ;
    chvec2.push_back(*ch) ;

    if (gDebug)
    {
		ch = cl.getCarrierHardware(1) ;
		cout << "CarrierHardware2[1] = " << ch << " target=" << ch->mTarget_pwr_mW << " carrier=" << ch->mCarrier << endl ;
		ch = cl.getCarrierHardware(2) ;
		cout << "CarrierHardware2[2] = " << ch << " target=" << ch->mTarget_pwr_mW << " carrier=" << ch->mCarrier <<  endl ;
		ch = cl.getCarrierHardware(3) ;
		cout << "CarrierHardware2[3] = " << ch << " target=" << ch->mTarget_pwr_mW << " carrier=" << ch->mCarrier <<  endl ;
		ch = cl.getCarrierHardware(4) ;
		cout << "CarrierHardware2[4] = " << ch << " target=" << ch->mTarget_pwr_mW << " carrier=" << ch->mCarrier <<  endl ;

		cout << "-------------------\n" ;

		for(std::vector<CarrierHardware2*>::iterator chp = chvec.begin(); chp != chvec.end(); ++chp)
		{
			cerr << "Prior to preUpdate(): " << (*chp) << " name=" << (*chp)->mName << " count=" << (*chp)->mPreCount << endl ;
		}
		cout << "-------------------\n" ;
    }



    // Run pre update on all
    bool status ;
    status = cl.preUpdate() ;
	CPPUNIT_ASSERT_EQUAL(true, status) ;

    if (gDebug)
    {
		for(std::vector<CarrierHardware2*>::iterator chp = chvec.begin(); chp != chvec.end(); ++chp)
		{
			cerr << "After preUpdate(): " << (*chp) << " name=" << (*chp)->mName << " count=" << (*chp)->mPreCount << endl ;
		}
		cout << "-------------------\n" ;
    }




	// All CarrierHardware2 should have run preUpdate()
	unsigned expected = 1u ;
	ch = cl.getCarrierHardware(1) ;
	CPPUNIT_ASSERT_EQUAL(expected, ch->mPreCount) ;
	ch = cl.getCarrierHardware(2) ;
	CPPUNIT_ASSERT_EQUAL(expected, ch->mPreCount) ;
	ch = cl.getCarrierHardware(3) ;
	CPPUNIT_ASSERT_EQUAL(expected, ch->mPreCount) ;
	ch = cl.getCarrierHardware(4) ;
	CPPUNIT_ASSERT_EQUAL(expected, ch->mPreCount) ;

	// Set 'ch-c' to failed
	ch = cl.getCarrierHardware(3) ;
	ch->mOk = false ;
	ch->mFailureReason = std::string("ch-c failed") ;

    status = cl.preUpdate() ;
	CPPUNIT_ASSERT_EQUAL(false, status) ;
	CPPUNIT_ASSERT_EQUAL(std::string("ch-c failed"), cl.failReason()) ;

	// All CarrierHardware2 should have run preUpdate()
	ch = cl.getCarrierHardware(1) ;
	CPPUNIT_ASSERT_EQUAL(2u, ch->mPreCount) ;
	ch = cl.getCarrierHardware(2) ;
	CPPUNIT_ASSERT_EQUAL(2u, ch->mPreCount) ;
	ch = cl.getCarrierHardware(3) ;
	CPPUNIT_ASSERT_EQUAL(2u, ch->mPreCount) ;	// pre-update gets called but returns failure
	ch = cl.getCarrierHardware(4) ;
	CPPUNIT_ASSERT_EQUAL(1u, ch->mPreCount) ;	// pre-update does not get called

//	bool test = XXX_carrier_hardware_foreach_bind1(&CarrierHardware2::showCarrier2, std::cout) ;
//	bool test = XXX_carrier_hardware_foreach_bind0(&CarrierHardware2::showCarrier0) ;
//	CPPUNIT_ASSERT(test) ;

    	std::for_each(chvec2.begin(), chvec2.end(),
//    		std::bind2nd(std::mem_fun_ref(&CarrierHardware2::showCarrier), std::cout)
    		XXX_carrier_hardware_foreach_bind1(&CarrierHardware2::showCarrier, std::cout)
    	) ;

}

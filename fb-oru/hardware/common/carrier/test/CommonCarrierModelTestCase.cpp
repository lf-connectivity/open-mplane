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

#include <string.h>
#include <iostream>


#include "ICarrierModel.h"
#include "CommonCarrier.h"
#include "CommonCarrierModel.h"
#include "CommonCarrierModelTestCase.h"


using namespace std;
using namespace Mplane;

std::shared_ptr<ICarrierModel> ICarrierModel::createInstance(unsigned maxCarriers)
{
	static std::shared_ptr<ICarrierModel> model( new CommonCarrierModel(maxCarriers) );
	return model ;
}

//------------------------------------------------------------------------------------------------------------------------

static unsigned access_count = 0 ;

// A simple, well behaved worker
class SimpleWorker : public ICarrierModelWorker
{
public:
	SimpleWorker() :
		mFailureReason(""),
		mInitCount(0),
		mAddCount(0),
		mValidateCount(0),
		mPostUpdateCount(0),
		mPreUpdateCount(0),
		mChangeCount(0),
		mHardwareCount(0),
		mCompleteCount(0),
		ok(true),
		mAccess(0)
	{} ;
	~SimpleWorker() {} ;

    bool initialise(void) { ++mInitCount; return checkFail();}

    bool addCarrier( const ICarrier& carrier ) { ++mAddCount; return checkFail();}

    bool validateChange(const ICarrier& carrier) { mAccess = ++access_count ; ++mValidateCount; return checkFail();}

    bool carrierChange(const ICarrier& carrier) { ++mChangeCount; return checkFail();}

    bool preUpdate() { ++mPreUpdateCount ; return checkFail();}

    bool updateHardware() { ++mHardwareCount; return checkFail();}

    bool postUpdate() { ++mPostUpdateCount; return checkFail();}

    void changeComplete() { ++mCompleteCount;}

    std::string failReason(void)
    {
    	std::string reason("");
    	using std::swap ;
    	swap(reason, mFailureReason);
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

    bool checkFail()
    {
    	if (!ok)
    	{
    		mFailureReason = "Failed for some reason" ;
    	}
    	return ok ;
    }

    virtual void show() {}

    virtual void show(std::ostream& os) {}


    std::string mFailureReason ;
    unsigned mInitCount ;
    unsigned mAddCount ;
    unsigned mValidateCount ;
    unsigned mPostUpdateCount ;
    unsigned mPreUpdateCount ;
    unsigned mChangeCount ;
    unsigned mHardwareCount ;
    unsigned mCompleteCount ;
    bool ok ;
    unsigned mAccess ;
};

class SimpleListWorker : public ICarrierModelWorker
{
public:
	SimpleListWorker() :
		mFailureReason(""),
		mAccess(0)
	{} ;
	~SimpleListWorker() {} ;

    bool initialise(void) { return true;}

    bool addCarrier( const ICarrier& carrier ) { return true;}

    bool validateChange(const ICarrier& carrier) { mAccess = ++access_count ; return true;}

    bool carrierChange(const ICarrier& carrier) { return true;}

    bool preUpdate() { return true;}

    bool updateHardware() { return true;}

    bool postUpdate() { return true;}

    void changeComplete() { }

    std::string failReason(void)
    {
    	std::string reason("");
    	using std::swap ;
    	swap(reason, mFailureReason);
    	return reason ;
    }

    virtual void show() {}

    virtual void show(std::ostream& os) {}

    virtual void setFailReason(std::string reason)
    {
    	mFailureReason = reason ;
    }

    virtual void clearFailReason()
    {
    	mFailureReason = "" ;
    }

    std::string mFailureReason ;

    unsigned mAccess ;
};


//------------------------------------------------------------------------------------------------------------------------
/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonCarrierModelTestCase );

static const unsigned MAX_CARRIERS = 4 ;

//------------------------------------------------------------------------------------------------------------------------
/*
 * Unit tests
 */
void CommonCarrierModelTestCase::unittest()
{
    cout << "CommonCarrierModelTestCase unit test" << endl;


    std::shared_ptr<ICarrierModel> model( ICarrierModel::createInstance(MAX_CARRIERS) );

    // add some workers
    vector< std::shared_ptr<SimpleWorker> > workers ;
    for (unsigned i=0; i < 3; ++i)
    {
    	std::shared_ptr<SimpleWorker> w( new SimpleWorker() ) ;
        model->addWorker( std::static_pointer_cast<ICarrierModelWorker>(w) ) ;
        workers.push_back( w ) ;
    }

    std::shared_ptr<SimpleListWorker> listWorker(new SimpleListWorker() ) ;
    model->addListWorker( std::static_pointer_cast<ICarrierModelWorker>(listWorker) ) ;

    for (unsigned i=0; i < workers.size(); ++i)
    {
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mInitCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mAddCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mValidateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mPostUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mPreUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mChangeCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mHardwareCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mCompleteCount);
    }

    CPPUNIT_ASSERT_EQUAL(true, model->initialise() );

    for (unsigned i=0; i < workers.size(); ++i)
    {
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mInitCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mAddCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mValidateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mPostUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mPreUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mChangeCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mHardwareCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mCompleteCount);
    }

    CommonCarrier carrier(1, 2, 4) ;
    CPPUNIT_ASSERT_EQUAL(true, model->addCarrier(carrier) );

    for (unsigned i=0; i < workers.size(); ++i)
    {
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mInitCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mAddCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mValidateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mPostUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mPreUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mChangeCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mHardwareCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mCompleteCount);
    }

    CPPUNIT_ASSERT_EQUAL(true, model->validateChange(carrier) );

    for (unsigned i=0; i < workers.size(); ++i)
    {
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mInitCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mAddCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mValidateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mPostUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mPreUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mChangeCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mHardwareCount);
    	CPPUNIT_ASSERT_EQUAL(0u, workers[i]->mCompleteCount);
    }

    // check order of calls
	CPPUNIT_ASSERT_EQUAL(1u, listWorker->mAccess);
    for (unsigned i=0; i < workers.size(); ++i)
    {
    	CPPUNIT_ASSERT_EQUAL(i+2, workers[i]->mAccess);
    }

    // Enabling
    carrier.setState(ICarrier::STATE_ENABLE) ;
    CPPUNIT_ASSERT_EQUAL(true, model->carrierChange(carrier) );

    for (unsigned i=0; i < workers.size(); ++i)
    {
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mInitCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mAddCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mValidateCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mPostUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mPreUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mChangeCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mHardwareCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mCompleteCount);
    }
    carrier.applyChanges() ;

    // Disabling
    carrier.setState(ICarrier::STATE_DISABLE) ;
    CPPUNIT_ASSERT_EQUAL(true, model->carrierChange(carrier) );

    for (unsigned i=0; i < workers.size(); ++i)
    {
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mInitCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mAddCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mValidateCount);

    	CPPUNIT_ASSERT_EQUAL(2u, workers[i]->mPostUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(2u, workers[i]->mPreUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(2u, workers[i]->mChangeCount);
    	CPPUNIT_ASSERT_EQUAL(2u, workers[i]->mHardwareCount);
    	CPPUNIT_ASSERT_EQUAL(2u, workers[i]->mCompleteCount);
    }
    carrier.applyChanges() ;

    // Check for fail
    workers[1]->ok = false ;	// worker [1] will fail, so carrierChange() will not update
    CPPUNIT_ASSERT_EQUAL(false, model->carrierChange(carrier) );
//    CPPUNIT_ASSERT_EQUAL(std::string("Failed for some reason"), model->failReason() );
    for (unsigned i=0; i < workers.size(); ++i)
    {
    	std::cout << "Worker[" << i << "] mInitCount=" << workers[i]->mInitCount << std::endl ;
    	std::cout << "Worker[" << i << "] mAddCount=" << workers[i]->mAddCount << std::endl ;
    	std::cout << "Worker[" << i << "] mValidateCount=" << workers[i]->mValidateCount << std::endl ;
    	std::cout << "Worker[" << i << "] mChangeCount=" << workers[i]->mChangeCount << std::endl ;
    	std::cout << "Worker[" << i << "] mPreUpdateCount=" << workers[i]->mPreUpdateCount << std::endl ;
    	std::cout << "Worker[" << i << "] mHardwareCount=" << workers[i]->mHardwareCount << std::endl ;
    	std::cout << "Worker[" << i << "] mPostUpdateCount=" << workers[i]->mPostUpdateCount << std::endl ;
    	std::cout << "Worker[" << i << "] mCompleteCount=" << workers[i]->mCompleteCount << std::endl ;


    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mInitCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mAddCount);
    	CPPUNIT_ASSERT_EQUAL(1u, workers[i]->mValidateCount);

    	// Model performs carrierChange() on all workers first. When it fails for worker [1] is will stop
    	unsigned expected = 2 ;
    	if (i <= 1)
    		expected = 3 ;
    	CPPUNIT_ASSERT_EQUAL(expected, workers[i]->mChangeCount);

    	// Since the carrierChange() failed at worker [1], *no* calls will be made to updateHardware()
    	CPPUNIT_ASSERT_EQUAL(2u, workers[i]->mPreUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(2u, workers[i]->mHardwareCount);
    	CPPUNIT_ASSERT_EQUAL(2u, workers[i]->mPostUpdateCount);
    	CPPUNIT_ASSERT_EQUAL(2u, workers[i]->mCompleteCount);
    }

    CPPUNIT_ASSERT_EQUAL(std::string("Failed for some reason"), model->failReason() ) ;

    // clear failure for subsequent tests
    workers[1]->ok = true ;
}

#ifndef _MPLANE_COMMONTXPORTTESTCASE_H_
#define _MPLANE_COMMONTXPORTTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonTxPortTestCase.h
 * \brief     Define the unit tests for the CommonTxPort class
 *
 *
 * \details   This CPPUNIT test class will test all the functionality of the
 * CommonTxPort implementation of the ITxPort interface.
 *
 */


#include <cppunit/extensions/HelperMacros.h>
#include "ITxPort.h"

namespace Mplane
{

class CommonTxPortObserver: public Observer<ITxPort>
{
public:
    const char* mName;
    ITxPort& mTxPort;
    bool mTxState;
    bool mObsCalled;
    CommonTxPortObserver(ITxPort *txPort ):
        mName("TxPortObs"),
        mTxPort(*txPort),
        mTxState( false ),
        mObsCalled( false )
    {
        static_cast<Subject<ITxPort>&>(mTxPort).attach( *this );
    }
    virtual ~CommonTxPortObserver()
    {
    	static_cast<Subject<ITxPort>&>(mTxPort).detach( *this );
    }
    virtual void update(ITxPort& subject)
    {
        mObsCalled = true;
        mTxState = subject.isTxOn();
    }
    virtual const char* name() const
    {
        return mName;
    }

};

/*! @brief Unit test harness for the common Tx port implementation.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonTxPort class.
 */
class CommonTxPortTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( Mplane::CommonTxPortTestCase );
    CPPUNIT_TEST( unittest );
    CPPUNIT_TEST_SUITE_END();

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the Frequency object constructor options
     */
    void unittest();

};


} /* namespace Mplane */



#endif /* _MPLANE_COMMONTXPORTTESTCASE_H_ */

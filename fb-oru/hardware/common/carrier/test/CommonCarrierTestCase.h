#ifndef _MPLANE_COMMONCARRIERTESTCASE_H_
#define _MPLANE_COMMONCARRIERTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <cppunit/extensions/HelperMacros.h>

#include "CommonCarrier.h"

namespace Mplane
{

class TestCarrier: public CommonCarrier
{
public:
    TestCarrier( int index, int maxTxPaths, int maxRxPaths );

    ~TestCarrier();
};



/*! @brief Unit test harness for the common Tx port implementation.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonTxPort class.
 */
class CommonCarrierTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonCarrierTestCase );
    CPPUNIT_TEST( unittest );
    CPPUNIT_TEST( change_test );
    CPPUNIT_TEST( path_change_test );
    CPPUNIT_TEST_SUITE_END();

public:


    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the Carrier object constructor options
     */
    void unittest();

    /**
     * @test Test the change tracking
     */
    void change_test();

    /**
     * @test Test the change tracking due to changing the tx or rx paths
     */
    void path_change_test();

private:

};


} /* namespace Mplane */





#endif /* _MPLANE_COMMONCARRIERTESTCASE_H_ */

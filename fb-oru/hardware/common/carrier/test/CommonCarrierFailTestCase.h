#ifndef _MPLANE_COMMONCARRIERFAILTESTCASE_H_
#define _MPLANE_COMMONCARRIERFAILTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierFailTestCase.h
 * \brief     Tests the CommonCarrierFail
 *
 *
 * \details   Tests the common carrier model instance of ICarrierFail
 *
 */

#include <cppunit/extensions/HelperMacros.h>

#include "CommonCarrierFail.h"

namespace Mplane
{

/*! @brief Unit test harness for the common carrier fail implementation.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonCarrierFail class.
 */
class CommonCarrierFailTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonCarrierFailTestCase );
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
     * @test Test the Carrier object constructor options
     */
    void unittest();

private:

};


} /* namespace Mplane */





#endif /* _MPLANE_COMMONCARRIERFAILTESTCASE_H_ */

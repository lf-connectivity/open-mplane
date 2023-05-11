#ifndef _MPLANE_COMMONCARRIERHWTESTCASE_H_
#define _MPLANE_COMMONCARRIERHWTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierModelTestCase.h
 * \brief     Tests the CommonCarrierModel
 *
 *
 * \details   Tests the common carrier model instance of ICarrierModel using simple carrier model workers
 *
 */

#include <cppunit/extensions/HelperMacros.h>

namespace Mplane
{

/*! @brief Unit test harness for the common carrier model implementation.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the CommonCarrierModel class.
 */
class CommonCarrierHardwareTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( CommonCarrierHardwareTestCase );
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





#endif /* _MPLANE_COMMONCARRIERHWTESTCASE_H_ */

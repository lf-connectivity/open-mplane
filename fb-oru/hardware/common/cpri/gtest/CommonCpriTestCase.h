#ifndef _COMM_COMMONCPRITESTCASE_H_
#define _COMM_COMMONCPRITESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCpriTestCase.h
 * \brief     The CppUnit test harness for CommonCpriCore
 *
 *
 * \details   This file defines the CppUnit test cases that will unit test
 *            the CommonCpriCore class.
 *
 */
#include "gtest/gtest.h"
#include "ICpriCore.h"

namespace Mplane
{

/* Our test classes used for the unit tests */

/*! \brief Unit test harness for the CommonCpri classes.
 *
 *  This class uses the google test facilities to perform unit testing
 *  of the CommonCpri classes.
 */
class CommonCpriTestCase : public ::testing::Test
{

public:

    /*! @brief Setup the test harness
     */
    void setUp() {};

    /*! @brief Tear down the test harness
     */
    void tearDown() {};

    /**
     * @test Test the Faults object constructor options
     */
    void testCreation();

    /**
     * @test Test the CPRI Core Slave mode access operations
     */
    void testCpriCoreSlaveAccess();

    /**
     * @test Test the CPRI Core Master mode access operations
     */
    void testCpriCoreMasterAccess();

    /**
     * @test Test the CPRI system startup, creation of the CPRI ports
     */
    void testCpriStartup();

    /**
     * @test Test the CPRI mode change, when CPRI config changes
     */
    void testCpriModeChange();
};

} /* namespace Mplane */

#endif /* _COMM_COMMONCPRITESTCASE_H_ */

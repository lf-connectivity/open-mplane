#ifndef _RADIOSVC_FIBRECONTROLSERVICE_TESTS_H_
#define _RADIOSVC_FIBRECONTROLSERVICE_TESTS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FibreControlServiceTests.h
 * \brief     The Google Unit test harness for FibreControlService
 *
 *
 * \details   This file defines the Google Unit test cases that will unit test
 *            the FibreControlService classes.
 *
 */

// Includes go here, before the namespace
#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "OffTargetFPGA.h"
#include "CommonFpgaKernel.h"
#include "CommonCpriCore.h"
#include "CpriController.h"
#include "FibreControlService.h"
#include "CpriPortHandling.h"
#include <memory>

namespace Mplane
{

// simulate a CPRI observer, to be notified of CPRI link state changes
class TestCpriObserver : public Observer<ICpriPortHandler>,
                         public Loggable
{
public:

    // allow off target test access
    friend class FibreControlServiceTestCases;
    friend class FibreControlServiceTestCase;

    TestCpriObserver();

    ~TestCpriObserver();

    // Implement the Loggable pure virtual methods
    virtual void show();

    // Implement the Observer pure virtual methods
    virtual void update(ICpriPortHandler& subject);
    virtual const char* name() const
    {
        return mName;
    }

    virtual bool doAttach(bool all, UINT32 portAttach);
    virtual bool getUpdateDone();
    virtual void setUpdateDone(bool setting);

    ICpriCore::LineRate mLineRate;
    const char* mName;
    bool mUpdateDone;
};


class FibreControlServiceTestCases: public ::testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual void testCreation();
    virtual void testCpriController();
    virtual void testCpriSlavePort();
    virtual void testCpriMasterPort();
    virtual void testCpriCfgChange();
    virtual void testErrorPaths();
    virtual void testResetScenarios();
    virtual void testAlarmScenarios();
    virtual void testMultiplePorts();
    virtual void testTidyUp();

    virtual bool waitState(std::shared_ptr<CpriPortHandler> ph, CpriPortHandler::CpriSMStates state, unsigned timeoutMs) ;
};


} /* namespace Mplane */

#endif /* _RADIOSVC_FIBRECONTROLSERVICE_TESTS_H_ */

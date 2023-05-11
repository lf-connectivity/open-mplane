/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestFilterTestCase.cpp
 * \brief     Define the unit tests for the TestFilter class
 *
 *
 * \details   Define the unit tests for the TestFilter class
 *
 */

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <iostream>


#include "IFilter.h"
#include "CommonFilter.h"
#include "CommonFilterTestCase.h"

using namespace Mplane;

/* Registers the fixture into the 'registry'
 */
CPPUNIT_TEST_SUITE_REGISTRATION( CommonFilterTestCase );

using namespace std;

/****** Area for unit test specifics  ******/

namespace Mplane
{

// The Filter test class
class TestFilter : public CommonFilter
{
public:

    TestFilter( int index, int number, const char* name);

    virtual ~TestFilter() { };

    virtual ReturnType::State doInit();

    virtual IFilter::IPortData * getData( int port )  /* throw (std::invalid_argument) */;

    CommonFilterPortData mData;

};

} /* namespace Mplane */

TestFilter::TestFilter( int index, int number, const char* name):
        CommonFilter::CommonFilter(index, number, name)
{

}



IFilter::IPortData* TestFilter::getData(int port)
        /* throw (std::invalid_argument) */
{
    return dynamic_cast<IFilter::IPortData*>(&mData);
}

ReturnType::State TestFilter::doInit()
{
    ReturnType::State result = ReturnType::RT_OK;
    std::string resultString = "TESTFILTER INITIALISED OK";

    setInitResultString(resultString);

    // waste a bit of time
    int timedelay = 1000000;
    while (timedelay != 0) timedelay--;


    return result;
}

/****** End of Area for unit test specifics  ******/

/*
 * Unit tests
 */
void CommonFilterTestCase::testCreation()
{
    cout << endl << "*** TestFilterTestCase Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    TestFilter* testFilter = new TestFilter( 0, 1, "TheFILTER");
    CPPUNIT_ASSERT(testFilter != 0);

    CPPUNIT_ASSERT(testFilter->getIndex() == 0);
    CPPUNIT_ASSERT(testFilter->getNumber() == 1);
    CPPUNIT_ASSERT(strcmp(testFilter->getName(), "TheFILTER") == 0 );

    delete( testFilter );

    cout << __func__ << " - END" <<  endl;
}

void CommonFilterTestCase::testInitialisation()
{
    cout << __func__ << " - START" <<  endl;

    TestFilter* testFilter = new TestFilter( 0, 1, "TheFILTER");
    CPPUNIT_ASSERT(testFilter != 0);

    // then initialise and confirm it completed ok
    CPPUNIT_ASSERT(testFilter->initialise() == ReturnType::RT_OK);

    CPPUNIT_ASSERT(testFilter->getInitResult() == ReturnType::RT_OK);
    CPPUNIT_ASSERT( testFilter->getInitResultString() == "TESTFILTER INITIALISED OK");
    CPPUNIT_ASSERT(testFilter->getInitStartTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testFilter->getInitEndTime()->tv_sec != 0);
    CPPUNIT_ASSERT(testFilter->getInitDurationTime() != 0);
    CPPUNIT_ASSERT(testFilter->isInitComplete() == true);

    IFilter *iFilter = testFilter;

//    CPPUNIT_ASSERT( iFilter->update() == ReturnType::RT_OK );

    CPPUNIT_ASSERT( iFilter->shutdown() == true );

    testFilter->show();

    cout << "The Filter Initialise execution duration was " << testFilter->getInitDurationTime() << " usecs" << endl;

    delete( testFilter );

    cout << __func__ << " - END" <<  endl;
}

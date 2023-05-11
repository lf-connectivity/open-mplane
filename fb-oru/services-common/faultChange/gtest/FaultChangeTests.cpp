/*
 * FaultChangeTestCase.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: rcooper
 */

#include "gtest/gtest.h"

#include <string.h>
#include <iostream>

#include "IFaultChange.h"
#include "FaultChange.h"

using namespace Mplane;
using namespace std;


namespace Mplane
{

class FaultChangeTestCases: public ::testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();
    virtual void testCreation();

};

void Mplane::FaultChangeTestCases::SetUp()
{
}

void Mplane::FaultChangeTestCases::TearDown()
{
}

void Mplane::FaultChangeTestCases::testCreation()
{
    cout << "testCreation" << endl;

    std::shared_ptr<IFaultChange> testFaultChange = IFaultChange::getInstance();

    ASSERT_TRUE(testFaultChange != 0);

    testFaultChange->setFaultName("TestFault1");

    ASSERT_TRUE("TestFault1" == testFaultChange->getFaultName() );

    testFaultChange->setFaultName("TestFault2");

    ASSERT_TRUE("TestFault2" == testFaultChange->getFaultName() );
}


/*
 * Unit tests
 */
TEST_F(FaultChangeTestCases, TestCreation)
{
    cout << endl << "*** FaultChangeTestCases Tests ***" <<  endl;
    cout << __func__ << " - START" <<  endl;

    testCreation();


    cout << __func__ << " - END" <<  endl;
}

int main( int argc, char* argv[] )
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

} // end namespace

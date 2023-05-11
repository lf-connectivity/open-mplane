#ifndef _SERVICETESTCASE_H_
#define _SERVICETESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ServiceTestCase.h
 * \brief     Define CPPUNIT unit test class for Service base class.
 *
 *
 * \details   Define CPPUNIT unit test class for Service base class.
 *
 */

#include <cppunit/extensions/HelperMacros.h>

#include "Service.h"

namespace Mplane
{

class AService : public Service
{
public:
    AService();

    virtual ~AService(){std::cerr << "~AService" << std::endl ;};

    int count;

    virtual void show();

protected:
    virtual int service();

};


class BService : public Service
{
public:
    BService();

    virtual ~BService(){std::cerr << "~BService" << std::endl ;};

    int getCount();

    void notifytest();

    int count;

    bool doneRegObs;

    virtual void show();

protected:
    virtual int service();
    virtual void doReset();
    virtual bool registerObservers();

};

class CService : public Service
{
public:
    CService();

    virtual ~CService(){ std::cerr << "~CService" << std::endl ;};

    int count;

    virtual void show();

    // used to force error return in service
    bool bForceError;
protected:
    virtual int service();

};


/*! @brief Unit test harness for the Frequency class.
 *
 *  This class uses the CPPUnit test facilities to perform unit testing
 *  of the common task Task class.
 */
class ServiceTestCase : public CPPUNIT_NS::TestFixture
{
    /*!
     * Macro definitions used to add the test definitions to the base test fixture
     */
    CPPUNIT_TEST_SUITE( ServiceTestCase );
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
     * @test Test the Service base class, through test services AService and BService
     */
    void unittest();

private:

    AService* svc_a;

    BService* svc_b;

    CService* svc_c;

};


} /* namespace Mplane */






#endif /* _SERVICETESTCASE_H_ */

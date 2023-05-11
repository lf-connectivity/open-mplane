#ifndef _TESTRADIOAPPLICATION_H_
#define _TESTRADIOAPPLICATION_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestRadioApplication.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#include "IServicesCtl.h"
#include "Service.h"

namespace Mplane
{

class ATestApp : public Service
{
public:
    ATestApp(const char* name, const char* suId );

    virtual ~ATestApp(){};

    int getCount();

    void notifytest();

    int count;

    bool doneRegObs;

protected:
    virtual void show();
    virtual int service();
    virtual void doReset();
    virtual bool registerObservers();

};


class TestApplicationServices: public IServicesCtl
{
    friend class CommonServicesTestCase;
public:

    /**
     *
     */
    TestApplicationServices();

    /**
     * Method called by the controlling radio process to start all services
     *
     */
    virtual void start();

    /**
     * Method called by the controlling radio process to reset all services.
     *
     * @return
     */
    virtual void reset();

    /**
     * Method called by the controlling radio process to temporarily suspend
     * all services.
     *
     */
    virtual void suspend();

    /**
     * Method called by the controlling radio process to resume a currently
     * suspended services.
     */
    virtual void resume();

    /**
     * Method used to shutdown all services after which the service may be deleted
     * or restarted using the start() method.
     */
    virtual void shutdown();

    virtual bool registerService(std::shared_ptr<Service> service) override {return true;}

    virtual bool registerTaskService(std::shared_ptr<Task> service) override {return true;}

    virtual bool registerMiscService(IServicesCtl::MiscServiceSingletonCreate create) override {return true;}


    virtual ~TestApplicationServices();

protected:
    ATestApp& mAapp;
    ATestApp& mBapp;
    ATestApp& mCapp;

};

}

#endif /* _TESTRADIOAPPLICATION_H_ */

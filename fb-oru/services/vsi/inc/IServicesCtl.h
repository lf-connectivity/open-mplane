#ifndef _IRADIOSERVICES_H_
#define _IRADIOSERVICES_H_

#include <memory>
#include <functional>

#include "Service.h"
#include "Task.h"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRadioServices.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

namespace Mplane
{

/**
 * Virtual class of miscellaneous services. A miscellaneous service is basically anything not Task or Service
 * based, but needs to be created at Service::start() time.
 *
 * This definition is only created so that all miscellaneous services can be derived from this base class and the
 * pointer to the actual instance stored in the service object.
 */
class IServiceMisc
{
public:
	IServiceMisc() {}
	virtual ~IServiceMisc() {}
};

/**
 * This is a common interface that must be implemented by the owner of the
 * all radio services either in the common services or in the specific
 * application.
 */
class IServicesCtl
{
public:
    /**
     * Method called by the controlling radio process to start all services
     *
     */
    virtual void start() = 0;

    /**
     * Method called by the controlling radio process to reset all services.
     *
     * @return
     */
    virtual void reset() = 0;

    /**
     * Method called by the controlling radio process to temporarily suspend
     * all services.
     *
     */
    virtual void suspend() = 0;

    /**
     * Method called by the controlling radio process to resume a currently
     * suspended services.
     */
    virtual void resume() = 0;

    /**
     * Method used to shutdown all services after which the service may be deleted
     * or restarted using the start() method.
     */
    virtual void shutdown() = 0;


    /**
     * Register a new service. Adds this service to the list so that it can be controlled like the others
     * @param service
     * @return true if registered ok
     */
    virtual bool registerService(std::shared_ptr<Service> service) =0 ;

    /**
     * Register a new task-based service. Adds this service to the list so that it can be controlled like the others
     * @param service
     * @return true if registered ok
     */
    virtual bool registerTaskService(std::shared_ptr<Task> service) =0 ;

    /**
     * Callback function which is guaranteed to create one and only one instance of the misc service
     */
    using MiscServiceSingletonCreate = std::function<std::shared_ptr<IServiceMisc>()> ;

    /**
     * Register a miscellaneous service. In this case it registers the service creation function. This is called
     * once at start up.
     * @param create	Singleton creation callback function
     * @return true if registered ok
     */
    virtual bool registerMiscService(MiscServiceSingletonCreate create) =0 ;


    /**
     * Register a new service. Adds this service to the list *before* the last entry in the list. This is used for
     * "plugin" services so they can add their services to the list in front of the final radio service (or whatever the final
     * control service is)
     * @param service
     * @return true if registered ok
     */
    virtual bool registerServiceInsert(std::shared_ptr<Service> service) =0 ;


    /**
     * Default virtual destructor
     */
    virtual ~IServicesCtl() {};
};

/**
 * Factory interface that must be implemented by the owning container of
 * all radio services. Allows a radio control process to create the
 * common radio services without knowing their details.
 */
class IRadioServicesFactory
{
public:
    /**
     * Method used to create all the common radio services and return an
     * interface to an implementation of common radio services control object.
     * @return
     */
    static std::shared_ptr<IServicesCtl> create();
};


/**
 * Factory interface that must be implemented by the owning container of
 * all radio application services. Allows a common radio control process
 * to create the application services without knowing their details.
 *
 */
class IServicesFactory
{
public:
    /**
     * Method used to create all the common radio services and return an
     * interface to an implementation of common radio services control object.
     * @return
     */
    static std::shared_ptr<IServicesCtl> create();

    /**
     * Get the created singleton
     */
    static std::shared_ptr<IServicesCtl> singleton();
};


}


#endif /* _IRADIOSERVICES_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppServices.h
 * \brief     Base class for application services
 *
 *
 * \details   Manages the services that run for any particular application. Application specific code just needs
 * 			to register it's own services, all common behaviour is handled by this common class
 *
 */


#ifndef APPSERVICES_H_
#define APPSERVICES_H_

#include <string>
#include <memory>
#include <vector>

#include "IServicesCtl.h"
#include "Loggable.h"
#include "Task.h"
#include "Service.h"

namespace Mplane {

/*!
 * \class AppServices
 */
class AppServices: public IServicesCtl, public Loggable
{
public:
	explicit AppServices(const std::string& name) ;
	virtual ~AppServices() ;

    /**
     * Method called by the controlling radio process to start all services
     *
     */
    virtual void start() override;

    /**
     * Method called by the controlling radio process to reset all services.
     *
     * @return
     */
    virtual void reset() override;

    /**
     * Method called by the controlling radio process to temporarily suspend
     * all services.
     *
     */
    virtual void suspend() override;

    /**
     * Method called by the controlling radio process to resume a currently
     * suspended services.
     */
    virtual void resume() override;

    /**
     * Method used to shutdown all services after which the service may be deleted
     * or restarted using the start() method.
     */
    virtual void shutdown() override;


    /**
     * Register a new service. ADds this service to the list so that it can be controlled like the others
     * @param service
     * @return true if registered ok
     */
    virtual bool registerService(std::shared_ptr<Service> service) override ;

    /**
     * Register a new task-based service. ADds this service to the list so that it can be controlled like the others
     * @param service
     * @return true if registered ok
     */
    virtual bool registerTaskService(std::shared_ptr<Task> service) override ;

    /**
     * Register a miscellaneous service. In this case it registers the service creation function. This is called
     * once at start up.
     * @param create	Singleton creation callback function
     * @return true if registered ok
     */
    virtual bool registerMiscService(IServicesCtl::MiscServiceSingletonCreate create) override ;

    /**
     * Register a new service. Adds this service to the list *before* the last entry in the list. This is used for
     * "plugin" services so they can add their services to the list in front of the final radio service (or whatever the final
     * control service is)
     * @param service
     * @return true if registered ok
     */
    virtual bool registerServiceInsert(std::shared_ptr<Service> service) override ;



    /**
     * For ILoggable
     */
    virtual void show();


protected:
    // add a service
    void addService(std::shared_ptr<Service> service) ;
    void addTaskService(std::shared_ptr<Task> task) ;
    void addMiscService(IServicesCtl::MiscServiceSingletonCreate create) ;

    // get the list of all services
    std::vector< std::shared_ptr<Service> > getServices() const ;

    // get the list of all task based services
    std::vector< std::shared_ptr<Task> > getTasks() const ;

protected:
    std::vector< std::shared_ptr<Service> > mServices ;
    std::vector< std::shared_ptr<Task> > mTasks;	//<! Task based services
    std::vector< std::shared_ptr<IServiceMisc> > mMiscServices ;

    // list of services to create
    std::vector< IServicesCtl::MiscServiceSingletonCreate > mCreateList ;

private:
    bool mStarted ;
} ;

}

#endif /* APPSERVICES_H_ */

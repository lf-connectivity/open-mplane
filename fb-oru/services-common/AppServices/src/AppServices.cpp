/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppServices.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "AppServices.h"

using namespace Mplane;


//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IServicesCtl> IServicesFactory::singleton()
{
	return IServicesFactory::create() ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AppServices::AppServices(const std::string& name) :
	Loggable(name, "AP"),
    mServices(),
    mTasks(),
    mMiscServices(),
    mCreateList(),
    mStarted(false)
{
    eventInfo("Application being created");
}

//-------------------------------------------------------------------------------------------------------------
AppServices::~AppServices()
{
}

//-------------------------------------------------------------------------------------------------------------
void AppServices::start()
{

    // Done if already started
    if (mStarted)
    {
        eventInfo("Application start being called more than one!");
        return ;
    }

    eventInfo("Application being started");
    for (auto service : mServices)
    {
    	service->start() ;
    }

    for (auto task : mTasks)
    {
    	task->start() ;
    }


	// Create all misc services
	for (auto create : mCreateList)
	{
		mMiscServices.push_back( create() ) ;
	}

	mStarted = true ;
}

//-------------------------------------------------------------------------------------------------------------
void AppServices::reset()
{
    for (auto service : mServices)
    {
    	service->reset() ;
    }
}

//-------------------------------------------------------------------------------------------------------------
void AppServices::suspend()
{
    for (auto service : mServices)
    {
    	service->suspend() ;
    }
}

//-------------------------------------------------------------------------------------------------------------
void AppServices::resume()
{
    for (auto service : mServices)
    {
    	service->resume() ;
    }
}

//-------------------------------------------------------------------------------------------------------------
void AppServices::shutdown()
{
    for (auto service : mServices)
    {
    	service->shutdown() ;
    }
}

//-------------------------------------------------------------------------------------------------------------
void AppServices::show()
{
    for (auto service : mServices)
    {
    	service->show() ;
    }

    for (auto task : mTasks)
    {
    	task->show() ;
    }
}

//-------------------------------------------------------------------------------------------------------------
bool AppServices::registerService(std::shared_ptr<Service> service)
{
	addService(service) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool AppServices::registerTaskService(std::shared_ptr<Task> service)
{
	addTaskService(service) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool AppServices::registerMiscService(IServicesCtl::MiscServiceSingletonCreate create)
{
	addMiscService(create) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool AppServices::registerServiceInsert(std::shared_ptr<Service> service)
{
	if (mServices.empty())
	{
		addService(service) ;
		return true ;
	}

	mServices.insert(mServices.begin()+mServices.size()-1, service) ;

	return true ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void AppServices::addService(std::shared_ptr<Service> service)
{
	mServices.push_back(service) ;
}

//-------------------------------------------------------------------------------------------------------------
void AppServices::addTaskService(std::shared_ptr<Task> task)
{
	mTasks.push_back(task) ;
}

//-------------------------------------------------------------------------------------------------------------
void AppServices::addMiscService(IServicesCtl::MiscServiceSingletonCreate create)
{
	mCreateList.push_back(create) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<Service> > AppServices::getServices() const
{
	return mServices ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<Task> > AppServices::getTasks() const
{
	return mTasks ;
}

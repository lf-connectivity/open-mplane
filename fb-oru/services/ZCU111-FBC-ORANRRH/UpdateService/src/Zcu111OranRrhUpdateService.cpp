/*
 * Zcu111OranRrhUpdateService.cpp
 *
 *  Created on: 28 May 2020
 *      Author: rcooper
 */

#include "Zcu111OranRrhUpdateService.h"

using namespace Mplane;

std::shared_ptr<OranRrhUpdateService> OranRrhUpdateService::singleton()
{
	static std::shared_ptr<OranRrhUpdateService> instance(std::make_shared<Zcu111OranRrhUpdateService>()) ;
	return instance ;
}

Mplane::Zcu111OranRrhUpdateService::Zcu111OranRrhUpdateService() :
		OranRrhUpdateService()
{
}

void Mplane::Zcu111OranRrhUpdateService::show()
{
    eventInfo("*** Zcu111OranRrhUpdateService has no specific data at this time ***");
}

int Mplane::Zcu111OranRrhUpdateService::service()
{
	OranRrhUpdateService::service();

    logDebugVerbose("Zcu111OranRrhUpdateService");
    return 0;   // no errors
}

void Mplane::Zcu111OranRrhUpdateService::doReset()
{
}

Mplane::Zcu111OranRrhUpdateService::~Zcu111OranRrhUpdateService()
{
}

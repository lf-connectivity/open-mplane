/*
 * FaultService.cpp
 *
 *  Created on: 12 Jun 2013
 *      Author: gdurban
 */

#include "IFaultBuilder.h"
#include "IFaultsList.h"
#include "FaultService.h"

using namespace Mplane;

Mplane::FaultService::FaultService():
	Service( SERVICE_MEDIUM_PRIORITY,
			SMALL_STACK,
			800,
			"FaultService", "FS" )
{
	// Ensure all the faults and owners are created first
    std::shared_ptr<IFaultBuilder> faultBuilder(IFaultBuilder::getInstance()) ;

	eventInfo("FaultService created");
}

Mplane::FaultService::~FaultService()
{
}

void Mplane::FaultService::show()
{
}

int Mplane::FaultService::service()
{
	std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;
	faultsList->updateFaults() ;

    return 0;
}

void Mplane::FaultService::doReset()
{
}

bool Mplane::FaultService::registerObservers()
{
	return true ;
}

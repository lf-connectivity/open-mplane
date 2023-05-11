/*
 * CommonFPGA.cpp
 *
 *  Created on: 12 Jun 2013
 *      Author: gdurban
 */

#include "RxService.h"

using namespace Mplane;

Mplane::RxService::RxService():
                        Service( SERVICE_MEDIUM_PRIORITY,
                                SMALL_STACK,
                                1500,
                                "RxService", "RS" )
{
    eventInfo("RxService created");
}

void Mplane::RxService::show()
{
    eventInfo("*** RxService Show ***");
}

int Mplane::RxService::service()
{
    logDebugNormal("RxService - executing service");
    return 0;
}

bool Mplane::RxService::registerObservers()
{
    return true;
}

void Mplane::RxService::doReset()
{
}

Mplane::RxService::~RxService()
{
}

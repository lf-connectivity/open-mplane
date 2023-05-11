/*
 * CommonFPGA.cpp
 *
 *  Created on: 12 Jun 2013
 *      Author: gdurban
 */

#include "DigitalPowerService.h"
#include "IRadio.h"
#include "ITxPort.h"
#include "Power.h"

using namespace Mplane;

Mplane::DigitalPowerService::DigitalPowerService():
        Service( SERVICE_MEDIUM_PRIORITY,
                SMALL_STACK,
                100,
                "PowerService", "PS" ),
                radio( IRadioFactory::getInterface() )
{
    eventInfo("PowerService created");
}

void Mplane::DigitalPowerService::show()
{
    eventInfo("*** PowerService Show ***");
}

int Mplane::DigitalPowerService::service()
{
    logDebugNormal(
            "DigitalPowerService - executing service calling radio->updatePowerData()");

    for( int index = 0; index < 2; index++ )
    {
//        ITxPort &txPort = radio->getTxPort( index );
        logDebugNormal(
                 ">>Power TSSI: %f  RSSI %f",
                0.0, 0.0 );
    }
    return 0;   // no errors
}

bool Mplane::DigitalPowerService::registerObservers()
{
    return true;
}

void Mplane::DigitalPowerService::doReset()
{
}

Mplane::DigitalPowerService::~DigitalPowerService()
{
}

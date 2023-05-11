/*
 * CommonFPGA.cpp
 *
 *  Created on: 12 Jun 2013
 *      Author: gdurban
 */

#include "TxService.h"
#include "ITxPcl.h"
#include "IRadio.h"
#include "VswrMon.h"

using namespace Mplane;

const unsigned int TxService::TXSERVICE_TIMER_PERIOD_MSEC = 200;  // 200 msec timer period for TxService

Mplane::TxService::TxService():
           Service( SERVICE_MEDIUM__HIGH_PRIORITY,
                    SMALL_STACK,
					TxService::TXSERVICE_TIMER_PERIOD_MSEC,
                    "TxService", "TX" ),
				    mRadio(IRadioFactory::getInterface()),
                    updateCount( ONE_SEC_UPDATE )

{
    for( int index = 0; index < mRadio->getNumberOfTxPorts(); index++ )
    {
        std::shared_ptr<ITxPcl> pcl = ITxPcl::getInstance(index);
        mPcls.push_back( pcl );
        pcl->timerUpdate();
        std::shared_ptr<IVswr> vswr = IVswr::getInstance( index );
        mVswrs.push_back( vswr );
    }

    eventInfo("TxService created");
}

void Mplane::TxService::show()
{
    eventInfo("*** TxService Show ***");
}

int Mplane::TxService::service()
{
    logDebugNormal("TxService - executing service");

    // update both PCL loops on every service update
    for( int index = 0; index < mRadio->getNumberOfTxPorts(); index++ )
    {
        mPcls[index]->timerUpdate();
    }

    if( !mRadio->getCalMode() )     // only do VSWR measurements when we are not in cal mode.
    {
        // only update the VSWR monitor every second.
        if( ++updateCount ==  VswrMon::UPDATE_RATE)
        {
            updateCount = 0;
            for( int index = 0; index < mRadio->getNumberOfTxPorts(); index++ )
            {
                mVswrs[index]->processMeasurements();
            }
        }
    }
    return 0;
}

bool Mplane::TxService::registerObservers()
{
    return true;
}

void Mplane::TxService::doReset()
{
}

Mplane::TxService::~TxService()
{
}

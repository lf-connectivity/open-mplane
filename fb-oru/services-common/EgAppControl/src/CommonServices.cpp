/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonServices.cpp
 * \brief     Implementation of common radio services interface to create and controls all radio services
 *
 *
 * \details   Implementation of common radio services interface to create and controls all radio services
 *
 */


#include "CommonServices.h"

#include "TxService.h"
#include "RxService.h"
#include "FaultService.h"
#include "DigitalPowerService.h"
#include "FibreControlService.h"
#include "DpdService.h"

using namespace Mplane;

Mplane::CommonServices::CommonServices():
        mTxService( std::shared_ptr<TxService>(new TxService()) ),
        mRxService( std::shared_ptr<RxService>(new RxService()) ),
//        mFaultService( std::shared_ptr<FaultService>(new FaultService()) ),
        mPowerService( std::shared_ptr<DigitalPowerService>(new DigitalPowerService()) ),
        mFibreControlService( std::shared_ptr<FibreControlService>(new FibreControlService()) )
//		mDpdService( std::shared_ptr<DpdService>(new DpdService()) )
{
}

void Mplane::CommonServices::start()
{
    mTxService->start();
    mRxService->start();
//    mFaultService->start();
    mPowerService->start();
//    mDpdService->start();
    mFibreControlService->start();
}

void Mplane::CommonServices::reset()
{
    mTxService->reset();
    mRxService->reset();
//    mFaultService->reset();
    mPowerService->reset();
//    mDpdService->reset();
    mFibreControlService->reset();
}

void Mplane::CommonServices::suspend()
{
    mTxService->suspend();
    mRxService->suspend();
//    mFaultService->suspend();
    mPowerService->suspend();
//    mDpdService->suspend();
    mFibreControlService->suspend();
}

void Mplane::CommonServices::resume()
{
    mTxService->resume();
    mRxService->resume();
//    mFaultService->resume();
    mPowerService->resume();
//    mDpdService->resume();
    mFibreControlService->resume();
}

void Mplane::CommonServices::shutdown()
{
    mTxService->shutdown();
    mRxService->shutdown();
//    mFaultService->shutdown();
    mPowerService->shutdown();
//    mDpdService->shutdown();
    mFibreControlService->shutdown();
}

Mplane::CommonServices::~CommonServices()
{
}

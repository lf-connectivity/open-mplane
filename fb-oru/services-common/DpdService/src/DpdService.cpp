/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdService.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "ITxPort.h"
#include "IFpgaMsg.h"
#include "IFpgaComms.h"

#include "FpgaCommsMsgMonitor.h"
#include "DpdControlTx.h"

#include "DpdService.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdService::DpdService() :
	TaskEvent(Task::PRIORITY_MEDIUM, Task::SMALL_STACK, "DpdService", "TX"),
	mFpgaComms(IFpgaComms::getInterface())
{
	// Create DPD TX  controllers for each TX path
    std::vector< std::shared_ptr<ITxPort> > txPorts( ITxPortFactory::getPorts() ) ;
	for (unsigned tx=0; tx < txPorts.size(); ++tx)
	{
		mDpdControl.push_back( std::make_shared<DpdControlTx>(tx) ) ;
	}

	// Register EVENT message handling
	std::string failReason ;
	bool registered = mFpgaComms->registerMsgHandler(IFpgaPdu::PduDataType::PDU_TYPE_EVENT, this,
		[this](std::shared_ptr<IFpgaMsg> msg) {msgDispatcher(msg);},
		[](const IFpgaPdu& pdu)->std::shared_ptr<IFpgaMsg> {return IFpgaMsg::factory(pdu);},
		failReason) ;

	if (!registered)
		eventError("Failed to register DPD service with DPD comms : %s", failReason.c_str()) ;
}

//-------------------------------------------------------------------------------------------------------------
DpdService::~DpdService()
{
	mFpgaComms->unRegisterMsgHandler(IFpgaPdu::PduDataType::PDU_TYPE_EVENT, this) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdService::resetDpd(unsigned tx)
{
	// forward call
	return mDpdControl[tx]->resetDpd() ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdService::startDpd(unsigned tx)
{
	// forward call
	return mDpdControl[tx]->startDpd() ;
}


//-------------------------------------------------------------------------------------------------------------
bool DpdService::startDpd(unsigned tx, unsigned timeoutMs)
{
	// forward call
	return mDpdControl[tx]->startDpd(timeoutMs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdService::stopDpd(unsigned tx)
{
	// forward call
	return mDpdControl[tx]->stopDpd() ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdService::setPapr(unsigned tx, const Power& papr)
{
	// forward call
	return mDpdControl[tx]->setPapr(papr) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdService::setSRxAtten(unsigned tx, const Power& atten)
{
	// forward call
	return mDpdControl[tx]->setSRxAtten(atten) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdService::setParams(unsigned tx, const std::vector<DataVariant> &params)
{
	// TBD
	return false ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool DpdService::addMonitor(std::shared_ptr<FpgaCommsMsgMonitor> monitor)
{
	mMonitors.push_back(monitor) ;
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<DpdControlTx> DpdService::getDpdControl(unsigned txPort)
{
	if (txPort >= mDpdControl.size())
		return std::shared_ptr<DpdControlTx>() ;

	return mDpdControl[txPort] ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void DpdService::msgDispatcher(std::shared_ptr<IFpgaMsg> msg)
{
	Mutex::Lock lock(mMutex) ;
	mMessages.push(msg) ;
	event() ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdService::runEvent()
{
	// process message(s)
	std::shared_ptr<IFpgaMsg> msg ;
	do
	{
		// get data
		msg.reset() ;
		{
			Mutex::Lock lock(mMutex) ;
			if (!mMessages.empty())
			{
				msg = mMessages.front() ;
				mMessages.pop() ;
			}
		}

		// Handle data
		if (!msg)
			continue ;

		// Forward this message on to all monitors
		for (auto monitor : mMonitors)
		{
			monitor->handleMsg(msg) ;
		}

	} while(msg) ;

	return true ;
}

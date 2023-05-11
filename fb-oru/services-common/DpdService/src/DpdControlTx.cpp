/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdControlTx.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string>

#include "IFpgaComms.h"
#include "FpgaCommsMsgMonitor.h"

#include "DpdControlTx.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DpdControlTx::DpdControlTx(unsigned txPort) :
	DpdControlBase("DpdTx" + std::to_string(txPort)),

	mMonitor(),
	mTxPort(txPort),

	mMutex(),
	mCond(),
	mSuccessCount(0)

{
	// create an EVENT monitor looking for the success count
	mMonitor = 	std::make_shared<FpgaCommsMsgMonitor>("success",
		[this](std::map<std::string, DataVariant> attributes){
			handleEvent(attributes);
	}) ;


	// Register EVENT message handling
	std::string failReason ;
	bool registered = getFpgaComms()->registerMsgHandler(IFpgaPdu::PduDataType::PDU_TYPE_EVENT, this,
		[this](std::shared_ptr<IFpgaMsg> msg) {msgDispatcher(msg);},
		[](const IFpgaPdu& pdu)->std::shared_ptr<IFpgaMsg> {return IFpgaMsg::factory(pdu);},
		failReason) ;

	if (!registered)
		eventError("Failed to register DPD service with DPD comms : %s", failReason.c_str()) ;
}

//-------------------------------------------------------------------------------------------------------------
DpdControlTx::~DpdControlTx()
{
	getFpgaComms()->unRegisterMsgHandler(IFpgaPdu::PduDataType::PDU_TYPE_EVENT, this) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdControlTx::setPapr(const Power& papr)
{
	std::vector<DataVariant> args ;
	pushInt(args, "tx", mTxPort) ;
	pushFloat(args, "XcfrRef", papr.get()) ;
	return dpdSet(args) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdControlTx::setSRxAtten(const Power& atten)
{
	std::vector<DataVariant> args ;
	pushInt(args, "tx", mTxPort) ;
	pushFloat(args, "srxAtten", atten.get()) ;
	return dpdSet(args) ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdControlTx::resetDpd()
{
	std::vector<DataVariant> args ;
	pushInt(args, "tx", mTxPort) ;
	if (!dpdCmd("reset", args))
		return false ;

	// Ensure carrier streams have actually started before starting dpd
	Task::msSleep(50);

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdControlTx::startDpd()
{
	// Send start command
	std::vector<DataVariant> args ;
	pushInt(args, "tx", mTxPort) ;
	if (!dpdCmd("start", args))
		return false ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool DpdControlTx::startDpd(unsigned timeoutMs)
{
	// Send start command
	if (!startDpd())
		return false ;

	// Wait for at least 1 successful iteration

	// wait for registers to become available
	unsigned successCount(getSuccessCount()) ;
	while (successCount < 1)
	{
		// wait for success count change - abort on timeout
		if (!mCond.wait(timeoutMs))
			return false ;

		successCount = getSuccessCount() ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool DpdControlTx::stopDpd()
{
	std::vector<DataVariant> args ;
	pushInt(args, "tx", mTxPort) ;
	if (!dpdCmd("stop", args))
		return false ;

	// TODO: Use new DPD feature which should show stop status
	// For now just add a 100ms delay
	Task::msSleep(100) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::DpdControlTx::setQmc(QmcMode mode)
{
	std::vector<DataVariant> args ;
	pushInt(args, "tx", mTxPort) ;

	std::string modeStr("OFF") ;
	switch (mode)
	{
	case QmcMode::ON:
		modeStr = "ON" ;
		break ;

	case QmcMode::DCONLY:
		modeStr = "DCONLY" ;
		break ;

	case QmcMode::FREEZE:
		modeStr = "FREEZE" ;
		break ;

	case QmcMode::OFF:
	default:
		modeStr = "OFF" ;
		break ;
	}
	pushEnum(args, "qmc", "OFF:ON:DCONLY:FREEZE", modeStr) ;
	return dpdSet(args) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned DpdControlTx::getSuccessCount() const
{
	Mutex::Lock lock(mMutex) ;
	return mSuccessCount ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void DpdControlTx::msgDispatcher(std::shared_ptr<IFpgaMsg> msg)
{
	// Dispatch this EVENT message to the monitor
	mMonitor->handleMsg(msg) ;
}

//-------------------------------------------------------------------------------------------------------------
void DpdControlTx::handleEvent(const std::map<std::string, DataVariant>& attributes)
{
	// Callback for EVENT monitor - message must contain the variable 'success' in order to reach here

	// Get the latest value
	unsigned success(static_cast<unsigned>( attributes.at("success").toInt()) ) ;

	// Ensure the message is for this port
	auto txEntry(attributes.find("tx")) ;
	if (txEntry == attributes.end())
		return ;

	unsigned tx(static_cast<unsigned>( attributes.at("tx").toInt()) ) ;
	if (tx != mTxPort)
		return ;


	Mutex::Lock lock(mMutex) ;
	if (mSuccessCount != success)
	{
		mSuccessCount = success ;

		// signal that event has occurred (success count has changed)
		Conditional::Lock condLock(mCond) ;
		mCond.signal() ;
	}
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HeartBeatFaultOwner.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "HeartBeatMajorFaultOwner.h"
#include "HeartBeatFaultMajor.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IHeartbeat> IHeartbeat::getInstance()
{
	static std::shared_ptr<IHeartbeat> instance(std::make_shared<HeartBeatFaultOwner>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HeartBeatFaultOwner::HeartBeatFaultOwner() :
	FaultOwner("HeartBeatFaultOwner", {Mplane::HeartBeatFaultMajor::NAME}),
	Heartbeat()
{
}

//-------------------------------------------------------------------------------------------------------------
HeartBeatFaultOwner::~HeartBeatFaultOwner()
{
}

//-------------------------------------------------------------------------------------------------------------
void HeartBeatFaultOwner::updateFaults()
{
	// Does nothing - Fault updating done by the heartbeat event callback
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::HeartBeatFaultOwner::heartbeatEvent(bool expired)
{
	// Update the Fault
    std::shared_ptr<IFaultsList> faultsList(IFaultsList::getInstance()) ;

    std::shared_ptr<IFault> fault(faultsList->getFault(Mplane::HeartBeatFaultMajor::NAME)) ;
    fault->setStatus( expired );
}

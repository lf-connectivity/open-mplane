/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HeartBeatFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef HEART_BEAT_FAULTOWNER_H_
#define HEART_BEAT_FAULTOWNER_H_

#include "Heartbeat.h"
#include "FaultOwner.h"

namespace Mplane {

class HeartBeatFaultOwner : public FaultOwner, public Heartbeat
{
public:
	HeartBeatFaultOwner() ;
	virtual ~HeartBeatFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults.
	 * For the heartbeat monitor this does nothing since it used the heartbeatEvent() method to update
	 * it's fault
	 */
	virtual void updateFaults() override ;

protected:
	/**
	 * Event created by heartbeat monitor - used by derived classes (to raise faults etc)
	 * Event is generated on change of timer expiration
	 * @param expired
	 */
	virtual void heartbeatEvent(bool expired) ;


} ;

}

#endif /* HEART_BEAT_FAULTOWNER_H_ */

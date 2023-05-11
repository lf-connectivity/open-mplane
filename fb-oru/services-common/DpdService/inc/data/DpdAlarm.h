/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdAlarm.h
 * \brief     Implements the DPD alarm data class
 *
 *
 * \details   IDpdData class sent to clients registered for DPD alarm updates
 *
 */


#ifndef DPDALARM_H_
#define DPDALARM_H_

#include "data/IDpdAlarm.h"
#include "data/IDpdData.h"
#include "data/DpdData.h"

namespace Mplane {

class DpdAlarm : public DpdData, public virtual IDpdAlarm, public virtual IDpdDataSetter {
public:
	using DpdAlarmType = IDpdAlarm::DpdAlarmType ;

	DpdAlarm() ;
	virtual ~DpdAlarm() ;

	/**
	 * Return the trigger variable name for this data
	 * @return
	 */
	static std::string getTriggerVariable() ;

	/**
	 * Construct from a virtual reference (used mainly for testing)
	 */
	explicit DpdAlarm(const IDpdAlarm& rhs) ;

	/**
	 * Predicate used to determine whether this data will be used
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if data is to be used
	 */
	virtual bool predicate(const std::map<std::string, DataVariant>& attributes) override ;

	// Get the failure count
	virtual unsigned getFailCount() const override { return mFailCount; }

	// Get the alarm type
	virtual DpdAlarmType getAlarmType() const override { return mAlarmType; }

	// Get the tx port
	virtual unsigned getTxPort() const override { return mTxPort; }


	// Data set interface

	/**
	 * Data setter. Each derived class must provide this method to set it's member data
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if set ok; false on failure
	 */
	virtual bool setData(const std::map<std::string, DataVariant>& attributes) override ;

private:
	unsigned mFailCount ;
	DpdAlarmType mAlarmType ;
	unsigned mTxPort ;
} ;

}

#endif /* DPDALARM_H_ */

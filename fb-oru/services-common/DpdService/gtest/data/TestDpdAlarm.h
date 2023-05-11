/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDpdAlarm.h
 * \brief     Implements the TESTDPD alarm data class
 *
 *
 * \details
 *
 */


#ifndef TESTDPDALARM_H_
#define TESTDPDALARM_H_

#include "data/ITestDpdAlarm.h"
#include "data/IDpdData.h"

namespace Mplane {

class TestDpdAlarm : public virtual ITestDpdAlarm, public virtual IDpdDataSetter {
public:
	TestDpdAlarm() ;
	virtual ~TestDpdAlarm() ;

	// Data set interface

	/**
	 * Data setter. Each derived class must provide this method to set it's member data
	 * @param attributes	Map of variable/value pairs contained in the TESTDPD message
	 * @return true if set ok; false on failure
	 */
	virtual bool setData(const std::map<std::string, DataVariant>& attributes) override ;

	/**
	 * Predicate used to determine whether this data will be used
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if data is to be used
	 */
	virtual bool predicate(const std::map<std::string, DataVariant>& attributes) override
	{
		return true ;
	}

} ;

}

#endif /* TESTDPDALARM_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDpdVswr.h
 * \brief     Implements the TESTDPD VSWR measurement data class
 *
 *
 * \details
 *
 */


#ifndef TESTDPDVSWR_H_
#define TESTDPDVSWR_H_

#include "data/ITestDpdVswr.h"
#include "data/IDpdData.h"

namespace Mplane {

class TestDpdVswr : public virtual ITestDpdVswr, public virtual IDpdDataSetter {
public:
	TestDpdVswr() ;
	virtual ~TestDpdVswr() ;

	/**
	 * Predicate used to determine whether this data will be used
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if data is to be used
	 */
	virtual bool predicate(const std::map<std::string, DataVariant>& attributes) override
	{
		return true ;
	}

	/**
	 * Get the VSWR power measurement for a TX port
	 * @param port 0-based index
	 * @return measurement
	 */
	virtual Power getMeasurement(unsigned port) const override ;

	// Data set interface

	/**
	 * Data setter. Each derived class must provide this method to set it's member data
	 * @param attributes	Map of variable/value pairs contained in the TESTDPD message
	 * @return true if set ok; false on failure
	 */
	virtual bool setData(const std::map<std::string, DataVariant>& attributes) override ;

private:
	unsigned mNumTxPorts ;
	std::vector<Power>	mPowers ;
} ;

}

#endif /* TESTDPDVSWR_H_ */

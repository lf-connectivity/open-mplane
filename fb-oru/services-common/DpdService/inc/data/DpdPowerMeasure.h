/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdPowerMeasure.h
 * \brief     Base IDpdData class for forward and reverse power measurements
 *
 *
 * \details
 *
 */


#ifndef DPDPOWERMEASUREMENT_H_
#define DPDPOWERMEASUREMENT_H_

#include "data/IDpdPowerMeasure.h"
#include "data/IDpdData.h"
#include "data/DpdData.h"

namespace Mplane {

class DpdPowerMeasure : public DpdData, public virtual IDpdPowerMeasure, public virtual IDpdDataSetter {
public:
	explicit DpdPowerMeasure(const std::string& gerrName) ;
	virtual ~DpdPowerMeasure() ;

	/**
	 * Construct from a virtual reference (used mainly for testing)
	 */
	explicit DpdPowerMeasure(const IDpdPowerMeasure& rhs) ;


	/**
	 * Predicate used to determine whether this data will be used
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if data is to be used
	 */
	virtual bool predicate(const std::map<std::string, DataVariant>& attributes) override ;

	// Get the name of the variable which provides the forward/reverse power
	virtual std::string getGerrName() const override { return mGerrName; }

	// Get tx path [1..NUM_TX_PORTS]
	virtual unsigned getTxPort() const override { return mTxPort; }

	// Get XrmsRef in dB
	virtual Power getXrmsRef() const override { return mXrmsRef; }

	// Get YrmsRef in dB
	virtual Power getYrmsRef() const override { return mYrmsRef; }

	// Get Gerr in dB
	virtual Power getGerr() const override { return mGerr; }

	// Get SRX atten in dB
	virtual Power getSrxAtten() const override { return mSrxAtten; }

	// Data set interface

	/**
	 * Data setter. Each derived class must provide this method to set it's member data
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if set ok; false on failure
	 */
	virtual bool setData(const std::map<std::string, DataVariant>& attributes) override ;

private:
	// convert the rms integer into a Power
	Power rmsToPower(int rms) const ;

private:
	std::string mGerrName ;
	unsigned mTxPort ;
	Power mXrmsRef ;
	Power mYrmsRef ;
	Power mGerr ;
	Power mSrxAtten ;
} ;

}

#endif /* DPDPOWERMEASUREMENT_H_ */

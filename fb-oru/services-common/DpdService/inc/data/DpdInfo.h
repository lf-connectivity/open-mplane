/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdInfo.h
 * \brief     Implements the DPD alarm data class
 *
 *
 * \details   IDpdData class sent to clients registered for DPD alarm updates
 *
 */


#ifndef DPDINFO_H_
#define DPDINFO_H_

#include "data/IDpdInfo.h"
#include "data/IDpdData.h"
#include "data/DpdData.h"

namespace Mplane {

class DpdInfo : public DpdData, public virtual IDpdInfo, public virtual IDpdDataSetter {
public:

	DpdInfo() ;
	virtual ~DpdInfo() ;

	/**
	 * Return the trigger variable name for this data
	 * @return
	 */
	static std::string getTriggerVariable() ;

	/**
	 * Construct from a virtual reference (used mainly for testing)
	 */
	explicit DpdInfo(const IDpdInfo& rhs) ;

	/**
	 * Predicate used to determine whether this data will be used
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if data is to be used
	 */
	virtual bool predicate(const std::map<std::string, DataVariant>& attributes) override ;

	// Clear out the settings
	virtual void clear() override ;

	// Get the failure count
	virtual unsigned getFailCount() const override { return mFailCount; }

	// Get the success count
	virtual unsigned getSuccessCount() const override { return mSuccessCount; }

	// Get the iteration count
	virtual unsigned getIteration() const override { return mIteration; }

	// Get B, N, Q
	virtual unsigned getB() const override { return mB; }
	virtual unsigned getN() const override { return mN; }
	virtual unsigned getQ() const override { return mQ; }

	// Get G, Gexp, eff, evm
	virtual float getG() const override { return mG; }
	virtual float getGexp() const override { return mGexp; }
	virtual float getEff() const override { return mEff; }
	virtual float getEvm() const override { return mEvm; }

	// Get the Tx Port
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
	unsigned mSuccessCount ;
	unsigned mIteration ;
	unsigned mB ;
	unsigned mN ;
	unsigned mQ ;
	float mG ;
	float mGexp ;
	float mEff ;
	float mEvm ;
	unsigned mTxPort ;
} ;

}

#endif /* DPDINFO_H_ */

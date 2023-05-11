/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdTxpower.h
 * \brief     Implements the DPD power data class
 *
 *
 * \details   IDpdData class sent to clients registered for TX power measurement updates
 *
 */


#ifndef DPDTXPOWER_H_
#define DPDTXPOWER_H_

#include "data/IDpdTxpower.h"
#include "data/DpdPowerMeasure.h"

namespace Mplane {

class DpdTxpower : public DpdPowerMeasure, public virtual IDpdTxpower {
public:
	using super = DpdPowerMeasure ;

	DpdTxpower() ;
	virtual ~DpdTxpower() ;

	/**
	 * Return the trigger variable name for this data
	 * @return
	 */
	static std::string getTriggerVariable() ;

	/**
	 * Construct from a virtual reference (used mainly for testing)
	 */
	DpdTxpower(const IDpdTxpower& rhs) ;

	// Get tx path [1..NUM_TX_PORTS]
	virtual unsigned getTxPort() const override { return this->super::getTxPort(); }

	// Get XrmsRef in dB
	virtual Power getXrmsRef() const override { return this->super::getXrmsRef(); }

	// Get YrmsRef in dB
	virtual Power getYrmsRef() const override { return this->super::getYrmsRef(); }

	// Get SRX atten in dB
	virtual Power getSrxAtten() const override { return this->super::getSrxAtten(); }

	// Get fwdGerr in dB
	virtual Power getFwdGerr() const override { return getGerr(); }

} ;

}

#endif /* DPDTXPOWER_H_ */

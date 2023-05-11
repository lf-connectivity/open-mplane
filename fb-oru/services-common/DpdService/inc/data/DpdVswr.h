/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdVswr.h
 * \brief     Implements the DPD VSWR measurement data class
 *
 *
 * \details   IDpdData class sent to clients registered for VSWR measurement updates
 *
 */


#ifndef DPDVSWR_H_
#define DPDVSWR_H_

#include "data/IDpdVswr.h"
#include "data/DpdPowerMeasure.h"

namespace Mplane {

class DpdVswr : public DpdPowerMeasure, public virtual IDpdVswr {
public:
	using super = DpdPowerMeasure ;

	DpdVswr() ;
	virtual ~DpdVswr() ;

	/**
	 * Return the trigger variable name for this data
	 * @return
	 */
	static std::string getTriggerVariable() ;

	/**
	 * Construct from a virtual reference (used mainly for testing)
	 */
	explicit DpdVswr(const IDpdVswr& rhs) ;

	// Get tx path [1..NUM_TX_PORTS]
	virtual unsigned getTxPort() const override { return this->super::getTxPort(); }

	// Get XrmsRef in dB
	virtual Power getXrmsRef() const override { return this->super::getXrmsRef(); }

	// Get YrmsRef in dB
	virtual Power getYrmsRef() const override { return this->super::getYrmsRef(); }

	// Get SRX atten in dB
	virtual Power getSrxAtten() const override { return this->super::getSrxAtten(); }

	// Get revGerr in dB
	virtual Power getRevGerr() const override { return getGerr(); }

} ;

}

#endif /* DPDVSWR_H_ */

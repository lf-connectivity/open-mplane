/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdVswr.h
 * \brief     Interface object for data passed to DPD client interested in VSWR measurements
 *
 *
 * \details
 *
 */


#ifndef IDPDVSWR_H_
#define IDPDVSWR_H_

#include "data/IDpdData.h"
#include "Power.h"

namespace Mplane {

class IDpdVswr : public virtual IDpdData {
public:
	IDpdVswr() {}
	virtual ~IDpdVswr() {}

	// Get tx path [1..NUM_TX_PORTS]
	virtual unsigned getTxPort() const =0;

	// Get XrmsRef in dB
	virtual Power getXrmsRef() const =0;

	// Get YrmsRef in dB
	virtual Power getYrmsRef() const =0;

	// Get revGerr in dB
	virtual Power getRevGerr() const =0;

	// Get SRX atten in dB
	virtual Power getSrxAtten() const =0;
} ;

}

#endif /* IDPDVSWR_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdPowerMeasure.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef IDPDPOWERMEASURE_H_
#define IDPDPOWERMEASURE_H_

#include "data/IDpdData.h"
#include "Power.h"

namespace Mplane {

class IDpdPowerMeasure : public virtual IDpdData {
public:
	IDpdPowerMeasure() {}
	virtual ~IDpdPowerMeasure() {}

	// Get the name of the variable which provides the forward/reverse power
	virtual std::string getGerrName() const =0;

	// Get tx path [1..NUM_TX_PORTS]
	virtual unsigned getTxPort() const =0;

	// Get XrmsRef in dB
	virtual Power getXrmsRef() const =0;

	// Get YrmsRef in dB
	virtual Power getYrmsRef() const =0;

	// Get Gerr in dB
	virtual Power getGerr() const =0;

	// Get SRX atten in dB
	virtual Power getSrxAtten() const =0;
} ;

}

#endif /* IDPDPOWERMEASURE_H_ */

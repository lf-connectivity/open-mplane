/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdInfo.h
 * \brief     Interface object for data passed to DPD client interested in DPD information
 *
 *
 * \details
 *
 */


#ifndef IDPDINFO_H_
#define IDPDINFO_H_

#include "data/IDpdData.h"

namespace Mplane {

class IDpdInfo : public virtual IDpdData {
public:
	IDpdInfo() {}
	virtual ~IDpdInfo() {}

	// Clear out the settings
	virtual void clear() =0 ;

	// B=12 G=0.33 Gexp=-2.16314 N=1 Q=1 eff=-22.5937 err=OK evm=-22.8926 fail=0 i=1 success=1 tx=0

	// Get the failure count
	virtual unsigned getFailCount() const =0;

	// Get the success count
	virtual unsigned getSuccessCount() const =0;

	// Get the iteration count
	virtual unsigned getIteration() const =0;

	// Get B, N, Q
	virtual unsigned getB() const =0;
	virtual unsigned getN() const =0;
	virtual unsigned getQ() const =0;

	// Get G, Gexp, eff, evm
	virtual float getG() const =0 ;
	virtual float getGexp() const =0 ;
	virtual float getEff() const =0 ;
	virtual float getEvm() const =0 ;

	// Get the Tx Port
	virtual unsigned getTxPort() const =0;

} ;

}

#endif /* IDPDINFO_H_ */

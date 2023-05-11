/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PopTripMajorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef POP_TRIP_MAJOR_FAULTOWNER_H_
#define POP_TRIP_MAJOR_FAULTOWNER_H_

#include "FaultOwner.h"

namespace Mplane {

class PopTripMajorFaultOwner : public FaultOwner
{
public:
	PopTripMajorFaultOwner() ;
	virtual ~PopTripMajorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

private:
	void updatePopTripTx1MajorFaults( void ); //!> update method
	void updatePopTripTx2MajorFaults( void ); //!> update method

	const UINT16 POP_BIT_MASK = 0x8000;

} ;

}

#endif /* POP_TRIP_MAJOR_FAULTOWNER_H_ */

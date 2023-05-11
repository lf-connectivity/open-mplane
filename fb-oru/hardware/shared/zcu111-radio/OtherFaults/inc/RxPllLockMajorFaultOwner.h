/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxPllLockMajorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef RX_PLL_LOCK_MAJOR_FAULTOWNER_H_
#define RX_PLL_LOCK_MAJOR_FAULTOWNER_H_

#include "FaultOwner.h"

namespace Mplane {

class RxPllLockMajorFaultOwner : public FaultOwner
{
public:
	RxPllLockMajorFaultOwner() ;
	virtual ~RxPllLockMajorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

private:
	void updateRxPllLockMajorFaults( void ); //!> Under temperature Major fault update method

} ;

}

#endif /* RX_PLL_LOCK_MAJOR_FAULTOWNER_H_ */

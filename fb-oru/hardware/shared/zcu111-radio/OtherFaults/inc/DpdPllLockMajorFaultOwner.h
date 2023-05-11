/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdPllLockMajorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef DPD_PLL_LOCK_MAJOR_FAULTOWNER_H_
#define DPD_PLL_LOCK_MAJOR_FAULTOWNER_H_

#include "FaultOwner.h"

namespace Mplane {

class DpdPllLockMajorFaultOwner : public FaultOwner
{
public:
	DpdPllLockMajorFaultOwner() ;
	virtual ~DpdPllLockMajorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

private:
	void updateDpdPllLockMajorFaults( void ); //!> Under temperature Major fault update method

} ;

}

#endif /* DPD_PLL_LOCK_MAJOR_FAULTOWNER_H_ */

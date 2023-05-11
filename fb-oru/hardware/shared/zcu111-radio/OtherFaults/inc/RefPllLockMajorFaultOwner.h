/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RefPllLockMajorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef REF_PLL_LOCK_MAJOR_FAULTOWNER_H_
#define REF_PLL_LOCK_MAJOR_FAULTOWNER_H_

#include "FaultOwner.h"

namespace Mplane {

class RefPllLockMajorFaultOwner : public FaultOwner
{
public:
	RefPllLockMajorFaultOwner() ;
	virtual ~RefPllLockMajorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

private:
	void updateRefPllLockMajorFaults( void ); //!> Ref PLL Major fault update method

} ;

}

#endif /* REF_PLL_LOCK_MAJOR_FAULTOWNER_H_ */

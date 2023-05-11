/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxPllLockMajorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TX_PLL_LOCK_MAJOR_FAULTOWNER_H_
#define TX_PLL_LOCK_MAJOR_FAULTOWNER_H_

#include "FaultOwner.h"

namespace Mplane {

class TxPllLockMajorFaultOwner : public FaultOwner
{
public:
	TxPllLockMajorFaultOwner() ;
	virtual ~TxPllLockMajorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

private:
	void updateTxPllLockMajorFaults( void ); //!> Under temperature Major fault update method

} ;

}

#endif /* TX_PLL_LOCK_MAJOR_FAULTOWNER_H_ */

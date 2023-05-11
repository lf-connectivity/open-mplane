/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PclTxMajorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef PCL_TX_MAJOR_FAULTOWNER_H_
#define PCL_TX_MAJOR_FAULTOWNER_H_

#include "FaultOwner.h"

namespace Mplane {

class PclTxMajorFaultOwner : public FaultOwner
{
public:
	PclTxMajorFaultOwner() ;
	virtual ~PclTxMajorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

private:
} ;

}

#endif /* PCL_TX_MAJOR_FAULTOWNER_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SrlMajorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef SRL_MAJOR_FAULTOWNER_H_
#define SRL_MAJOR_FAULTOWNER_H_

#include "FaultOwner.h"

namespace Mplane {

class SrlMajorFaultOwner : public FaultOwner
{
public:
	SrlMajorFaultOwner() ;
	virtual ~SrlMajorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

private:
	void updateSrlTx1MajorFaults( void ); //!> update method
	void updateSrlTx2MajorFaults( void ); //!> update method

} ;

}

#endif /* SRL_MAJOR_FAULTOWNER_H_ */

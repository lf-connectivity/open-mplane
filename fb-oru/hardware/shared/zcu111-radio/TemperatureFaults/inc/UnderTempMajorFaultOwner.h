/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      UnderTempMajorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef UNDER_TEMP_MAJOR_FAULTOWNER_H_
#define UNDER_TEMP_MAJOR_FAULTOWNER_H_

#include "FaultOwner.h"
#include "Loggable.h"

namespace Mplane {

class UnderTempMajorFaultOwner : public FaultOwner, public Loggable
{
public:
	UnderTempMajorFaultOwner() ;
	virtual ~UnderTempMajorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

private:
	const float FPGA_ALARM_UNDER_TEMP_MAJOR 	  = -12.0; //!> FPGA under temperature major alarm
	const float BOARD_TX1_ALARM_UNDER_TEMP_MAJOR  = -12.0; //!> Board Tx1 under temperature major alarm
	const float BOARD_TX2_ALARM_UNDER_TEMP_MAJOR  = -12.0; //!> Board Tx2 under temperature major alarm
	const float BOARD_TX3_ALARM_UNDER_TEMP_MAJOR  = -12.0; //!> Board Tx3 under temperature major alarm
	const float BOARD_TX4_ALARM_UNDER_TEMP_MAJOR  = -12.0; //!> Board Tx4 under temperature major alarm
	const float PA1_ALARM_UNDER_TEMP_MAJOR   	  = -12.0; //!> PA 1 under temperature major
	const float PA2_ALARM_UNDER_TEMP_MAJOR   	  = -12.0; //!> PA 2 under temperature major
	const float PA3_ALARM_UNDER_TEMP_MAJOR   	  = -12.0; //!> PA 3 under temperature major
	const float PA4_ALARM_UNDER_TEMP_MAJOR   	  = -12.0; //!> PA 4 under temperature major

	void updateUnderTempMajorFaults( void ); //!> Under temperature Major fault update method

} ;

}

#endif /* UNDER_TEMP_MAJOR_FAULTOWNER_H_ */

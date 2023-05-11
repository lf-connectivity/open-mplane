/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OverTempMinorFaultOwner.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef OVER_TEMP_MINOR_FAULTOWNER_H_
#define OVER_TEMP_MINOR_FAULTOWNER_H_

#include "FaultOwner.h"

namespace Mplane {

class OverTempMinorFaultOwner : public FaultOwner
{
public:
	OverTempMinorFaultOwner() ;
	virtual ~OverTempMinorFaultOwner() ;

	/**
	 * Called by a service or any other regular task. Causes the IFaultOwner to update it's owned faults
	 */
	virtual void updateFaults() override ;

private:
	const float FPGA_ALARM_OVER_TEMP_MINOR        =  90.0; //!> FPGA over temperature minor
	const float BOARD_TX1_ALARM_OVER_TEMP_MINOR   =  82.0; //!> Board Tx1 over temperature minor
	const float BOARD_TX2_ALARM_OVER_TEMP_MINOR   =  82.0; //!> Board Tx2 over temperature minor
	const float BOARD_TX3_ALARM_OVER_TEMP_MINOR   =  82.0; //!> Board Tx3 over temperature minor
	const float BOARD_TX4_ALARM_OVER_TEMP_MINOR   =  82.0; //!> Board Tx4 over temperature minor
	const float PA1_ALARM_OVER_TEMP_MINOR   	  =  115.0; //!> PA 1 over temperature major
	const float PA2_ALARM_OVER_TEMP_MINOR   	  =  115.0; //!> PA 2 over temperature major
	const float PA3_ALARM_OVER_TEMP_MINOR   	  =  115.0; //!> PA 3 over temperature major
	const float PA4_ALARM_OVER_TEMP_MINOR   	  =  115.0; //!> PA 4 over temperature major

	void updateOverTempMinorFaults( void ); //!> Over temperature Minor fault update method

} ;

}

#endif /* OVER_TEMP_MINOR_FAULTOWNER_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PclTxOverPowerFaultMajor.h
 * \brief     Power control loop Tx over power fault major
 *
 *
 * \details
 *
 */


#ifndef PCL_TX_OVER_POWER_FAULT_MAJOR_H_
#define PCL_TX_OVER_POWER_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class PclTx1OverPowerFaultMajor : public Fault
{
public:
	PclTx1OverPowerFaultMajor() ;
	virtual ~PclTx1OverPowerFaultMajor() ;
    static const char* NAME;

} ;

class PclTx2OverPowerFaultMajor : public Fault
{
public:
	PclTx2OverPowerFaultMajor() ;
	virtual ~PclTx2OverPowerFaultMajor() ;
    static const char* NAME;

} ;

class PclTx3OverPowerFaultMajor : public Fault
{
public:
	PclTx3OverPowerFaultMajor() ;
	virtual ~PclTx3OverPowerFaultMajor() ;
    static const char* NAME;

} ;

class PclTx4OverPowerFaultMajor : public Fault
{
public:
	PclTx4OverPowerFaultMajor() ;
	virtual ~PclTx4OverPowerFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* PCL_TX_OVER_POWER_FAULT_MAJOR_H_ */

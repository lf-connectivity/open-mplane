/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PopTripTxFaultMajor.h
 * \brief     POP trip Tx fault major
 *
 *
 * \details
 *
 */


#ifndef POP_TRIP_TX_FAULT_MAJOR_H_
#define POP_TRIP_TX_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class PopTripTx1FaultMajor : public Fault
{
public:
	PopTripTx1FaultMajor() ;
	virtual ~PopTripTx1FaultMajor() ;
    static const char* NAME;

} ;

class PopTripTx2FaultMajor : public Fault
{
public:
	PopTripTx2FaultMajor() ;
	virtual ~PopTripTx2FaultMajor() ;
    static const char* NAME;

} ;

class PopTripTx3FaultMajor : public Fault
{
public:
	PopTripTx3FaultMajor() ;
	virtual ~PopTripTx3FaultMajor() ;
    static const char* NAME;

} ;

class PopTripTx4FaultMajor : public Fault
{
public:
	PopTripTx4FaultMajor() ;
	virtual ~PopTripTx4FaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* POP_TRIP_TX_FAULT_MAJOR_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PclTxConvergenceFaultMajor.h
 * \brief     Power control loop Tx convergence fault major
 *
 *
 * \details
 *
 */


#ifndef PCL_TX_CONVERGENCE_FAULT_MAJOR_H_
#define PCL_TX_CONVERGENCE_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class PclTx1ConvergenceFaultMajor : public Fault
{
public:
	PclTx1ConvergenceFaultMajor() ;
	virtual ~PclTx1ConvergenceFaultMajor() ;
    static const char* NAME;

} ;

class PclTx2ConvergenceFaultMajor : public Fault
{
public:
	PclTx2ConvergenceFaultMajor() ;
	virtual ~PclTx2ConvergenceFaultMajor() ;
    static const char* NAME;

} ;

class PclTx3ConvergenceFaultMajor : public Fault
{
public:
	PclTx3ConvergenceFaultMajor() ;
	virtual ~PclTx3ConvergenceFaultMajor() ;
    static const char* NAME;

} ;

class PclTx4ConvergenceFaultMajor : public Fault
{
public:
	PclTx4ConvergenceFaultMajor() ;
	virtual ~PclTx4ConvergenceFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* PCL_TX_CONVERGENCE_FAULT_MAJOR_H_ */

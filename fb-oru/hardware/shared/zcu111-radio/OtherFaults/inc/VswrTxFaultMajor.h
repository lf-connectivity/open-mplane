/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      VswrTxFaultMajor.h
 * \brief     VSWR Tx fault major
 *
 *
 * \details
 *
 */


#ifndef VSWR_TX_FAULT_MAJOR_H_
#define VSWR_TX_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class VswrTx1FaultMajor : public Fault
{
public:
	VswrTx1FaultMajor() ;
	virtual ~VswrTx1FaultMajor() ;
    static const char* NAME;

} ;

class VswrTx2FaultMajor : public Fault
{
public:
	VswrTx2FaultMajor() ;
	virtual ~VswrTx2FaultMajor() ;
    static const char* NAME;

} ;

class VswrTx3FaultMajor : public Fault
{
public:
	VswrTx3FaultMajor() ;
	virtual ~VswrTx3FaultMajor() ;
    static const char* NAME;

} ;

class VswrTx4FaultMajor : public Fault
{
public:
	VswrTx4FaultMajor() ;
	virtual ~VswrTx4FaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* VSWR_TX_FAULT_MAJOR_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SrlTxFaultMajor.h
 * \brief     SRL Tx fault major
 *
 *
 * \details
 *
 */


#ifndef SRL_TX_FAULT_MAJOR_H_
#define SRL_TX_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class SrlTx1FaultMajor : public Fault
{
public:
	SrlTx1FaultMajor() ;
	virtual ~SrlTx1FaultMajor() ;
    static const char* NAME;

} ;

class SrlTx2FaultMajor : public Fault
{
public:
	SrlTx2FaultMajor() ;
	virtual ~SrlTx2FaultMajor() ;
    static const char* NAME;

} ;

class SrlTx3FaultMajor : public Fault
{
public:
	SrlTx3FaultMajor() ;
	virtual ~SrlTx3FaultMajor() ;
    static const char* NAME;

} ;

class SrlTx4FaultMajor : public Fault
{
public:
	SrlTx4FaultMajor() ;
	virtual ~SrlTx4FaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* SRL_TX_FAULT_MAJOR_H_ */

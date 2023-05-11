/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdTxFaultMajor.h
 * \brief     DPD Tx fault major
 *
 *
 * \details
 *
 */


#ifndef DPD_TX_FAULT_MAJOR_H_
#define DPD_TX_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class DpdTx1FaultMajor : public Fault
{
public:
	DpdTx1FaultMajor() ;
	virtual ~DpdTx1FaultMajor() ;
    static const char* NAME;

} ;

class DpdTx2FaultMajor : public Fault
{
public:
	DpdTx2FaultMajor() ;
	virtual ~DpdTx2FaultMajor() ;
    static const char* NAME;

} ;

class DpdTx3FaultMajor : public Fault
{
public:
	DpdTx3FaultMajor() ;
	virtual ~DpdTx3FaultMajor() ;
    static const char* NAME;

} ;

class DpdTx4FaultMajor : public Fault
{
public:
	DpdTx4FaultMajor() ;
	virtual ~DpdTx4FaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* DPD_TX_FAULT_MAJOR_H_ */

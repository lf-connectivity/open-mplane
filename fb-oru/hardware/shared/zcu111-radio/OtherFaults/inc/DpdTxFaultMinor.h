/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdTxFaultMinor.h
 * \brief     DPD Tx fault minor
 *
 *
 * \details
 *
 */


#ifndef DPD_TX_FAULT_MINOR_H_
#define DPD_TX_FAULT_MINOR_H_

#include "Fault.h"

namespace Mplane {

class DpdTx1FaultMinor : public Fault
{
public:
	DpdTx1FaultMinor() ;
	virtual ~DpdTx1FaultMinor() ;
    static const char* NAME;

} ;

class DpdTx2FaultMinor : public Fault
{
public:
	DpdTx2FaultMinor() ;
	virtual ~DpdTx2FaultMinor() ;
    static const char* NAME;

} ;

class DpdTx3FaultMinor : public Fault
{
public:
	DpdTx3FaultMinor() ;
	virtual ~DpdTx3FaultMinor() ;
    static const char* NAME;

} ;

class DpdTx4FaultMinor : public Fault
{
public:
	DpdTx4FaultMinor() ;
	virtual ~DpdTx4FaultMinor() ;
    static const char* NAME;

} ;

}

#endif /* DPD_TX_FAULT_MINOR_H_ */

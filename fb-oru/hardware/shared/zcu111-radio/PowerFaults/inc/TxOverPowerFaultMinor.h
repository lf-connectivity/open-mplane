/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxOverpowerFaultMinor.h
 * \brief     Tx over power fault minor
 *
 *
 * \details
 *
 */


#ifndef TX_OVERPOWER_FAULT_MINOR_H_
#define TX_OVERPOWER_FAULT_MINOR_H_

#include "Fault.h"

namespace Mplane {

class Tx1OverPowerFaultMinor : public Fault
{
public:
	Tx1OverPowerFaultMinor() ;
	virtual ~Tx1OverPowerFaultMinor() ;
    static const char* NAME;

} ;

class Tx2OverPowerFaultMinor : public Fault
{
public:
	Tx2OverPowerFaultMinor() ;
	virtual ~Tx2OverPowerFaultMinor() ;
    static const char* NAME;

} ;

class Tx3OverPowerFaultMinor : public Fault
{
public:
	Tx3OverPowerFaultMinor() ;
	virtual ~Tx3OverPowerFaultMinor() ;
    static const char* NAME;

} ;

class Tx4OverPowerFaultMinor : public Fault
{
public:
	Tx4OverPowerFaultMinor() ;
	virtual ~Tx4OverPowerFaultMinor() ;
    static const char* NAME;

} ;

}

#endif /* TX_OVERPOWER_FAULT_MINOR_H_ */

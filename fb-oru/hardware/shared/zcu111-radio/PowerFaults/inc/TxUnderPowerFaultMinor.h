/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxUnderpowerFaultMinor.h
 * \brief     Tx over power fault minor
 *
 *
 * \details
 *
 */


#ifndef TX_UNDERPOWER_FAULT_MINOR_H_
#define TX_UNDERPOWER_FAULT_MINOR_H_

#include "Fault.h"

namespace Mplane {

class Tx1UnderPowerFaultMinor : public Fault
{
public:
	Tx1UnderPowerFaultMinor() ;
	virtual ~Tx1UnderPowerFaultMinor() ;
    static const char* NAME;

} ;

class Tx2UnderPowerFaultMinor : public Fault
{
public:
	Tx2UnderPowerFaultMinor() ;
	virtual ~Tx2UnderPowerFaultMinor() ;
    static const char* NAME;

} ;

class Tx3UnderPowerFaultMinor : public Fault
{
public:
	Tx3UnderPowerFaultMinor() ;
	virtual ~Tx3UnderPowerFaultMinor() ;
    static const char* NAME;

} ;

class Tx4UnderPowerFaultMinor : public Fault
{
public:
	Tx4UnderPowerFaultMinor() ;
	virtual ~Tx4UnderPowerFaultMinor() ;
    static const char* NAME;

} ;

}

#endif /* TX_UNDERPOWER_FAULT_MINOR_H_ */

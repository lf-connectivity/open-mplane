/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxOverpowerFaultMajor.h
 * \brief     Tx over power fault major
 *
 *
 * \details
 *
 */


#ifndef TX_OVERPOWER_FAULT_MAJOR_H_
#define TX_OVERPOWER_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Tx1OverPowerFaultMajor : public Fault
{
public:
	Tx1OverPowerFaultMajor() ;
	virtual ~Tx1OverPowerFaultMajor() ;
    static const char* NAME;

} ;

class Tx2OverPowerFaultMajor : public Fault
{
public:
	Tx2OverPowerFaultMajor() ;
	virtual ~Tx2OverPowerFaultMajor() ;
    static const char* NAME;

} ;

class Tx3OverPowerFaultMajor : public Fault
{
public:
	Tx3OverPowerFaultMajor() ;
	virtual ~Tx3OverPowerFaultMajor() ;
    static const char* NAME;

} ;

class Tx4OverPowerFaultMajor : public Fault
{
public:
	Tx4OverPowerFaultMajor() ;
	virtual ~Tx4OverPowerFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* TX_OVERPOWER_FAULT_MAJOR_H_ */

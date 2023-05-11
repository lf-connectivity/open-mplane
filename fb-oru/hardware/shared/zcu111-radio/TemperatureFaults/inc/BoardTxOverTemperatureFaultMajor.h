/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BoardTxOverTemperatureFaultMajor.h
 * \brief     Board Tx over temperature fault major
 *
 *
 * \details
 *
 */


#ifndef BOARD_TX_OVER_TEMPERATURE_FAULT_MAJOR_H_
#define BOARD_TX_OVER_TEMPERATURE_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class BoardTx1OverTemperatureFaultMajor : public Fault
{
public:
	BoardTx1OverTemperatureFaultMajor() ;
	virtual ~BoardTx1OverTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class BoardTx2OverTemperatureFaultMajor : public Fault
{
public:
	BoardTx2OverTemperatureFaultMajor() ;
	virtual ~BoardTx2OverTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class BoardTx3OverTemperatureFaultMajor : public Fault
{
public:
	BoardTx3OverTemperatureFaultMajor() ;
	virtual ~BoardTx3OverTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class BoardTx4OverTemperatureFaultMajor : public Fault
{
public:
	BoardTx4OverTemperatureFaultMajor() ;
	virtual ~BoardTx4OverTemperatureFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* BOARD_TX_OVER_TEMPERATURE_FAULT_MAJOR_H_ */

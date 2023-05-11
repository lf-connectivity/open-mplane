/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BoardTxOverTemperatureFaultMinor.h
 * \brief     Board Tx over temperature fault minor
 *
 *
 * \details
 *
 */


#ifndef BOARD_TX_OVER_TEMPERATURE_FAULT_MINOR_H_
#define BOARD_TX_OVER_TEMPERATURE_FAULT_MINOR_H_

#include "Fault.h"

namespace Mplane {

class BoardTx1OverTemperatureFaultMinor : public Fault
{
public:
	BoardTx1OverTemperatureFaultMinor() ;
	virtual ~BoardTx1OverTemperatureFaultMinor() ;
    static const char* NAME;

} ;

class BoardTx2OverTemperatureFaultMinor : public Fault
{
public:
	BoardTx2OverTemperatureFaultMinor() ;
	virtual ~BoardTx2OverTemperatureFaultMinor() ;
    static const char* NAME;

} ;

class BoardTx3OverTemperatureFaultMinor : public Fault
{
public:
	BoardTx3OverTemperatureFaultMinor() ;
	virtual ~BoardTx3OverTemperatureFaultMinor() ;
    static const char* NAME;

} ;

class BoardTx4OverTemperatureFaultMinor : public Fault
{
public:
	BoardTx4OverTemperatureFaultMinor() ;
	virtual ~BoardTx4OverTemperatureFaultMinor() ;
    static const char* NAME;

} ;

}

#endif /* BOARD_TX_OVER_TEMPERATURE_FAULT_MINOR_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BoardTx1UnderTemperatureFaultMajor.h
 * \brief     Board Tx under temperature fault major
 *
 *
 * \details
 *
 */


#ifndef BOARD_TX_UNDER_TEMPERATURE_FAULT_MAJOR_H_
#define BOARD_TX_UNDER_TEMPERATURE_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class BoardTx1UnderTemperatureFaultMajor : public Fault
{
public:
	BoardTx1UnderTemperatureFaultMajor() ;
	virtual ~BoardTx1UnderTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class BoardTx2UnderTemperatureFaultMajor : public Fault
{
public:
	BoardTx2UnderTemperatureFaultMajor() ;
	virtual ~BoardTx2UnderTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class BoardTx3UnderTemperatureFaultMajor : public Fault
{
public:
	BoardTx3UnderTemperatureFaultMajor() ;
	virtual ~BoardTx3UnderTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class BoardTx4UnderTemperatureFaultMajor : public Fault
{
public:
	BoardTx4UnderTemperatureFaultMajor() ;
	virtual ~BoardTx4UnderTemperatureFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* BOARD_TX_UNDER_TEMPERATURE_FAULT_MAJOR_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaUnderTemperatureFaultMajor.h
 * \brief     PA  under temperature fault major
 *
 *
 * \details
 *
 */


#ifndef PA_UNDER_TEMPERATURE_FAULT_MAJOR_H_
#define PA_UNDER_TEMPERATURE_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Pa1UnderTemperatureFaultMajor : public Fault
{
public:
	Pa1UnderTemperatureFaultMajor() ;
	virtual ~Pa1UnderTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class Pa2UnderTemperatureFaultMajor : public Fault
{
public:
	Pa2UnderTemperatureFaultMajor() ;
	virtual ~Pa2UnderTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class Pa3UnderTemperatureFaultMajor : public Fault
{
public:
	Pa3UnderTemperatureFaultMajor() ;
	virtual ~Pa3UnderTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class Pa4UnderTemperatureFaultMajor : public Fault
{
public:
	Pa4UnderTemperatureFaultMajor() ;
	virtual ~Pa4UnderTemperatureFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* PA_UNDER_TEMPERATURE_FAULT_MAJOR_H_ */

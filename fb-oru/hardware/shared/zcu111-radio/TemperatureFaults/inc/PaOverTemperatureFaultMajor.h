/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaOverTemperatureFaultMajor.h
 * \brief     PA over temperature fault major
 *
 *
 * \details
 *
 */


#ifndef PA_OVER_TEMPERATURE_FAULT_MAJOR_H_
#define PA_OVER_TEMPERATURE_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Pa1OverTemperatureFaultMajor : public Fault
{
public:
	Pa1OverTemperatureFaultMajor() ;
	virtual ~Pa1OverTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class Pa2OverTemperatureFaultMajor : public Fault
{
public:
	Pa2OverTemperatureFaultMajor() ;
	virtual ~Pa2OverTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class Pa3OverTemperatureFaultMajor : public Fault
{
public:
	Pa3OverTemperatureFaultMajor() ;
	virtual ~Pa3OverTemperatureFaultMajor() ;
    static const char* NAME;

} ;

class Pa4OverTemperatureFaultMajor : public Fault
{
public:
	Pa4OverTemperatureFaultMajor() ;
	virtual ~Pa4OverTemperatureFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* PA_OVER_TEMPERATURE_FAULT_MAJOR_H_ */

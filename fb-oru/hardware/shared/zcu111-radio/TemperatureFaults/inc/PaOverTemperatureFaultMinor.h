/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaOverTemperatureFaultMinor.h
 * \brief     PA over temperature fault minor
 *
 *
 * \details
 *
 */


#ifndef PA_OVER_TEMPERATURE_FAULT_MINOR_H_
#define PA_OVER_TEMPERATURE_FAULT_MINOR_H_

#include "Fault.h"

namespace Mplane {

class Pa1OverTemperatureFaultMinor : public Fault
{
public:
	Pa1OverTemperatureFaultMinor() ;
	virtual ~Pa1OverTemperatureFaultMinor() ;
    static const char* NAME;

} ;

class Pa2OverTemperatureFaultMinor : public Fault
{
public:
	Pa2OverTemperatureFaultMinor() ;
	virtual ~Pa2OverTemperatureFaultMinor() ;
    static const char* NAME;

} ;

class Pa3OverTemperatureFaultMinor : public Fault
{
public:
	Pa3OverTemperatureFaultMinor() ;
	virtual ~Pa3OverTemperatureFaultMinor() ;
    static const char* NAME;

} ;

class Pa4OverTemperatureFaultMinor : public Fault
{
public:
	Pa4OverTemperatureFaultMinor() ;
	virtual ~Pa4OverTemperatureFaultMinor() ;
    static const char* NAME;

} ;

}

#endif /* PA_OVER_TEMPERATURE_FAULT_MINOR_H_ */

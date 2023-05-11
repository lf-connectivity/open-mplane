/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxPowerMeasurementFaultMajor.h
 * \brief     Tx power measurement fault major
 *
 *
 * \details
 *
 */


#ifndef TX_POWER_MEASUREMENT_FAULT_MAJOR_H_
#define TX_POWER_MEASUREMENT_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

/**
 * This class defines a major fault used to indicate that the PCL power
 * measurement system has failed to measure RF power.
 */
class Tx1PowerMeasurementFaultMajor : public Fault
{
public:
    Tx1PowerMeasurementFaultMajor() ;
	virtual ~Tx1PowerMeasurementFaultMajor() ;
    static const char* NAME;

} ;

/**
 * This class defines a major fault used to indicate that the PCL power
 * measurement system has failed to measure RF power.
 */
class Tx2PowerMeasurementFaultMajor : public Fault
{
public:
    Tx2PowerMeasurementFaultMajor() ;
	virtual ~Tx2PowerMeasurementFaultMajor() ;
    static const char* NAME;

} ;

/**
 * This class defines a major fault used to indicate that the PCL power
 * measurement system has failed to measure RF power.
 */
class Tx3PowerMeasurementFaultMajor : public Fault
{
public:
    Tx3PowerMeasurementFaultMajor() ;
	virtual ~Tx3PowerMeasurementFaultMajor() ;
    static const char* NAME;

} ;

/**
 * This class defines a major fault used to indicate that the PCL power
 * measurement system has failed to measure RF power.
 */
class Tx4PowerMeasurementFaultMajor : public Fault
{
public:
    Tx4PowerMeasurementFaultMajor() ;
	virtual ~Tx4PowerMeasurementFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* TX_POWER_MEASUREMENT_FAULT_MAJOR_H_ */

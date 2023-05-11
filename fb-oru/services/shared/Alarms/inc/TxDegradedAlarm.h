/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxDegradedAlarm.h
 * \brief     Tx degraded alarm
 *
 *
 * \details
 *
 */


#ifndef TX_DEGRADED_ALARM_H_
#define TX_DEGRADED_ALARM_H_

#include "Alarm.h"

namespace Mplane {

class Tx1DegradedAlarm : public Alarm
{
public:
	Tx1DegradedAlarm() ;

	virtual ~Tx1DegradedAlarm() ;

    static const char* NAME;

} ;

class Tx2DegradedAlarm : public Alarm
{
public:
	Tx2DegradedAlarm() ;

	virtual ~Tx2DegradedAlarm() ;

    static const char* NAME;

} ;

class Tx3DegradedAlarm : public Alarm
{
public:
	Tx3DegradedAlarm() ;

	virtual ~Tx3DegradedAlarm() ;

    static const char* NAME;

} ;

class Tx4DegradedAlarm : public Alarm
{
public:
	Tx4DegradedAlarm() ;

	virtual ~Tx4DegradedAlarm() ;

    static const char* NAME;

} ;

}

#endif /* TX_DEGRADED_ALARM_H_ */

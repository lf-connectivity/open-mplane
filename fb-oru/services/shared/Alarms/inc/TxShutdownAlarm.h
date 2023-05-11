/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxShutdownAlarm.h
 * \brief     Tx shutdown alarm
 *
 *
 * \details
 *
 */


#ifndef TX_SHUTDOWN_ALARM_H_
#define TX_SHUTDOWN_ALARM_H_

#include "AlarmLatched.h"

namespace Mplane {

class Tx1ShutdownAlarm : public AlarmLatched
{
public:
	Tx1ShutdownAlarm() ;

	virtual ~Tx1ShutdownAlarm() ;

    static const char* NAME;

} ;

class Tx2ShutdownAlarm : public AlarmLatched
{
public:
	Tx2ShutdownAlarm() ;

	virtual ~Tx2ShutdownAlarm() ;

    static const char* NAME;

} ;

class Tx3ShutdownAlarm : public AlarmLatched
{
public:
	Tx3ShutdownAlarm() ;

	virtual ~Tx3ShutdownAlarm() ;

    static const char* NAME;

} ;

class Tx4ShutdownAlarm : public AlarmLatched
{
public:
	Tx4ShutdownAlarm() ;

	virtual ~Tx4ShutdownAlarm() ;

    static const char* NAME;

} ;

}

#endif /* TX_SHUTDOWN_ALARM_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxBbIqAlarm.h
 * \brief     Tx BB IQ alarm
 *
 *
 * \details
 *
 */


#ifndef TX_BB_IQ_ALARM_H_
#define TX_BB_IQ_ALARM_H_

#include "Alarm.h"

namespace Mplane {

class Tx1BbIqAlarm : public Alarm
{
public:
	Tx1BbIqAlarm() ;

	virtual ~Tx1BbIqAlarm() ;

    static const char* NAME;

} ;

class Tx2BbIqAlarm : public Alarm
{
public:
	Tx2BbIqAlarm() ;

	virtual ~Tx2BbIqAlarm() ;

    static const char* NAME;

} ;

class Tx3BbIqAlarm : public Alarm
{
public:
	Tx3BbIqAlarm() ;

	virtual ~Tx3BbIqAlarm() ;

    static const char* NAME;

} ;

class Tx4BbIqAlarm : public Alarm
{
public:
	Tx4BbIqAlarm() ;

	virtual ~Tx4BbIqAlarm() ;

    static const char* NAME;

} ;

}

#endif /* TX_BB_IQ_ALARM_H_ */

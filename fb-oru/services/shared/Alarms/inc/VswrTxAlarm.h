/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      VswrTxAlarm.h
 * \brief     Alarm for VSWR Tx fault
 *
 *
 * \details
 *
 */


#ifndef VSWR_TX_ALARM_H_
#define VSWR_TX_ALARM_H_

#include "Alarm.h"

namespace Mplane {

class VswrTx1Alarm : public Alarm
{
public:
	VswrTx1Alarm() ;

	virtual ~VswrTx1Alarm() ;

    static const char* NAME;

} ;

class VswrTx2Alarm : public Alarm
{
public:
	VswrTx2Alarm() ;

	virtual ~VswrTx2Alarm() ;

    static const char* NAME;

} ;

class VswrTx3Alarm : public Alarm
{
public:
	VswrTx3Alarm() ;

	virtual ~VswrTx3Alarm() ;

    static const char* NAME;

} ;

class VswrTx4Alarm : public Alarm
{
public:
	VswrTx4Alarm() ;

	virtual ~VswrTx4Alarm() ;

    static const char* NAME;

} ;

}

#endif /* VSWR_TX_ALARM_H_ */

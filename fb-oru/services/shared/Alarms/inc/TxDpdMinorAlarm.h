/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxDpdMinorAlarm.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TXDPDMINORALARM_H_
#define TXDPDMINORALARM_H_

#include "Alarm.h"

namespace Mplane {

/*!
 * \class Tx1DpdMinorAlarm
 */
class Tx1DpdMinorAlarm  : public Alarm {
public:
	Tx1DpdMinorAlarm() ;
	virtual ~Tx1DpdMinorAlarm() ;

    static const char* NAME;
} ;

class Tx2DpdMinorAlarm  : public Alarm {
public:
	Tx2DpdMinorAlarm() ;
	virtual ~Tx2DpdMinorAlarm() ;

    static const char* NAME;
} ;

class Tx3DpdMinorAlarm  : public Alarm {
public:
	Tx3DpdMinorAlarm() ;
	virtual ~Tx3DpdMinorAlarm() ;

    static const char* NAME;
} ;

class Tx4DpdMinorAlarm  : public Alarm {
public:
	Tx4DpdMinorAlarm() ;
	virtual ~Tx4DpdMinorAlarm() ;

    static const char* NAME;
} ;

}

#endif /* TXDPDMINORALARM_H_ */

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LatchedAlarmEmu.h
 * \brief     Latched alarm register (at 0x24)
 *
 *
 * \details
 *
 */


#ifndef LATCHEDALARM_H_
#define LATCHEDALARM_H_

#include "W1Clear.h"

namespace Mplane {

class LatchedAlarmEmu : public W1Clear {
public:
	LatchedAlarmEmu() ;
	virtual ~LatchedAlarmEmu() ;

} ;

}

#endif /* LATCHEDALARM_H_ */

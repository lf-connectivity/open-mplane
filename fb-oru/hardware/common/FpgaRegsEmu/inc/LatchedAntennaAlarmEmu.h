/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LatchedAntennaAlarmEmu.h
 * \brief     Latched antenna alarm register (at 0x5y250)
 *
 *
 * \details
 *
 */


#ifndef LATCHEDANTALARM_H_
#define LATCHEDANTALARM_H_

#include "W1Clear.h"

namespace Mplane {

class LatchedAntennaAlarmEmu : public W1Clear {
public:
	explicit LatchedAntennaAlarmEmu(unsigned antenna) ;
	virtual ~LatchedAntennaAlarmEmu() ;

} ;

}

#endif /* LATCHEDANTALARM_H_ */

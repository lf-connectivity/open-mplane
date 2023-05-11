/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITestDpdAlarm.h
 * \brief     Interface object for data passed to TESTDPD client interested in TESTDPD alarms
 *
 *
 * \details
 *
 */


#ifndef ITESTDPDALARM_H_
#define ITESTDPDALARM_H_

#include "data/IDpdData.h"

namespace Mplane {

class ITestDpdAlarm : public virtual IDpdData {
public:
	ITestDpdAlarm() {}
	virtual ~ITestDpdAlarm() {}

	// TBD ......

} ;

}

#endif /* ITESTDPDALARM_H_ */

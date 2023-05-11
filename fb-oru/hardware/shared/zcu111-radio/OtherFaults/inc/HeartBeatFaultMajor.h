/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HeartBeatFaultMajor.h
 * \brief     Heart beat fault major
 *
 *
 * \details
 *
 */


#ifndef HEART_BEAT_FAULT_MAJOR_H_
#define HEART_BEAT_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class HeartBeatFaultMajor : public Fault
{
public:
	HeartBeatFaultMajor() ;
	virtual ~HeartBeatFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* HEART_BEAT_FAULT_MAJOR_H_ */

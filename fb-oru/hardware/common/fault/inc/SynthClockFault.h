/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SynthClockFault.h
 * \brief     System synth clock lock fault
 *
 *
 * \details
 *
 */


#ifndef SYNTHCLOCKFAULT_H_
#define SYNTHCLOCKFAULT_H_

#include "Fault.h"

namespace Mplane {

class SynthClockFault : public Fault
{
public:
	SynthClockFault() ;
	virtual ~SynthClockFault() ;
	static const char* NAME;
} ;

}

#endif /* SYNTHCLOCKFAULT_H_ */

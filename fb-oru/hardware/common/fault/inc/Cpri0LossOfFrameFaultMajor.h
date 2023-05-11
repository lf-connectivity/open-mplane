/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri0LossOfFrameFaultMajor.h
 * \brief     CPRI0 loss of frame fault major
 *
 *
 * \details
 *
 */


#ifndef CPRI0_LOSS_OF_FRAME_FAULT_MAJOR_H_
#define CPRI0_LOSS_OF_FRAME_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Cpri0LossOfFrameFaultMajor : public Fault
{
public:
	Cpri0LossOfFrameFaultMajor() ;
	virtual ~Cpri0LossOfFrameFaultMajor() ;

	static const char* NAME;

} ;

}

#endif /* CPRI0_LOSS_OF_FRAME_FAULT_MAJOR_H_ */

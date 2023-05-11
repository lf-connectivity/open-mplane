/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri1LossOfFrameFaultMajor.h
 * \brief     Cpri 1 loss of frame fault major
 *
 *
 * \details
 *
 */


#ifndef CPRI1_LOSS_OF_FRAME_FAULT_MAJOR_H_
#define CPRI1_LOSS_OF_FRAME_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Cpri1LossOfFrameFaultMajor : public Fault
{
public:
	Cpri1LossOfFrameFaultMajor() ;
	virtual ~Cpri1LossOfFrameFaultMajor() ;

	static const char* NAME;

} ;

}

#endif /* CPRI1_LOSS_OF_FRAME_FAULT_MAJOR_H_ */

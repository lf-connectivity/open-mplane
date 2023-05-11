/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri0LossOfSignalFaultMajor.h
 * \brief     CPRI0 loss of signal fault major
 *
 *
 * \details
 *
 */


#ifndef CPRI0_LOSS_OF_SIGNAL_FAULT_MAJOR_H_
#define CPRI0_LOSS_OF_SIGNAL_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Cpri0LossOfSignalFaultMajor : public Fault
{
public:
	Cpri0LossOfSignalFaultMajor() ;
	virtual ~Cpri0LossOfSignalFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* CPRI0_LOSS_OF_SIGNAL_FAULT_MAJOR_H_ */

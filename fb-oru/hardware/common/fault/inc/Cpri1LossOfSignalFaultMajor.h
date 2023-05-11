/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Cpri1LossOfSignalFaultMajor.h
 * \brief     CPRI0 loss of signal fault major
 *
 *
 * \details
 *
 */


#ifndef CPRI1_LOSS_OF_SIGNAL_FAULT_MAJOR_H_
#define CPRI1_LOSS_OF_SIGNAL_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class Cpri1LossOfSignalFaultMajor : public Fault
{
public:
	Cpri1LossOfSignalFaultMajor() ;
	virtual ~Cpri1LossOfSignalFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* CPRI1_LOSS_OF_SIGNAL_FAULT_MAJOR_H_ */

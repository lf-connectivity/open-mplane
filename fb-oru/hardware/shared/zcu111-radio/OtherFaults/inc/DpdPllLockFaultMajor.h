/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdPllLockFaultMajor.h
 * \brief     Dpd PLL Lock fault major
 *
 *
 * \details
 *
 */


#ifndef DPD_PLL_LOCK_FAULT_MAJOR_H_
#define DPD_PLL_LOCK_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class DpdPllLockFaultMajor : public Fault
{
public:
	DpdPllLockFaultMajor() ;
	virtual ~DpdPllLockFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* DPD_PLL_LOCK_FAULT_MAJOR_H_ */

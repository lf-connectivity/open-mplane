/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RefPllLockFaultMajor.h
 * \brief     Reference clock PLL Lock fault major
 *
 *
 * \details
 *
 */


#ifndef REF_PLL_LOCK_FAULT_MAJOR_H_
#define REF_PLL_LOCK_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class RefPllLockFaultMajor : public Fault
{
public:
	RefPllLockFaultMajor() ;
	virtual ~RefPllLockFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* REF_PLL_LOCK_FAULT_MAJOR_H_ */

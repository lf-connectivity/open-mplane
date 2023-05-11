/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxPllLockFaultMajor.h
 * \brief     Board Tx1 over temperature fault major
 *
 *
 * \details
 *
 */


#ifndef RX_PLL_LOCK_FAULT_MAJOR_H_
#define RX_PLL_LOCK_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class RxPllLockFaultMajor : public Fault
{
public:
	RxPllLockFaultMajor() ;
	virtual ~RxPllLockFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* RX_PLL_LOCK_FAULT_MAJOR_H_ */

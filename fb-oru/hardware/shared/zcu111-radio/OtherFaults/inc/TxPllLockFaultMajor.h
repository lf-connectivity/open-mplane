/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxPllLockFaultMajor.h
 * \brief     Tx PLL Lock fault major
 *
 *
 * \details
 *
 */


#ifndef TX_PLL_LOCK_FAULT_MAJOR_H_
#define TX_PLL_LOCK_FAULT_MAJOR_H_

#include "Fault.h"

namespace Mplane {

class TxPllLockFaultMajor : public Fault
{
public:
	TxPllLockFaultMajor() ;
	virtual ~TxPllLockFaultMajor() ;
    static const char* NAME;

} ;

}

#endif /* TX_PLL_LOCK_FAULT_MAJOR_H_ */

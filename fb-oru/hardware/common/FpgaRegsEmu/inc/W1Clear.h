/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      W1Clear.h
 * \brief     Write '1' to clear latched bit
 *
 *
 * \details   Generic model of a register bit that needs to be written with a '1' to clear it's bit.
 *
 */


#ifndef W1CLEAR_H_
#define W1CLEAR_H_

#include "GlobalTypeDefs.h"
#include "OffTargetFPGA.h"

namespace Mplane {

class W1Clear {
public:
	W1Clear(unsigned address, unsigned startBit, unsigned numBits) ;
	virtual ~W1Clear() ;

	/**
	 * Allows testbench to set any bits
	 */
	virtual void set(UINT16 value) ;

private:
	UINT16 writeHandler(const UINT32 address, const UINT16 value, const UINT16 mask) ;
	UINT16 readHandler(const UINT32 address, const UINT16 mask) ;

private:
	Mutex mEmuMutex ;
	std::shared_ptr<OffTargetFPGA> mFpga ;
	unsigned mAddress;
	unsigned mStartBit;
	unsigned mNumBits;
	UINT16 mMask ;
	UINT16 mValue ;

} ;

}

#endif /* W1CLEAR_H_ */

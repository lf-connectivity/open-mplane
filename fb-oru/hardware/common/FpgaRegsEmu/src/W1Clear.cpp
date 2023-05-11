/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      W1Clear.cpp
 * \brief     Write '1' to clear latched bit
 *
 *
 * \details   Generic model of a register bit that needs to be written with a '1' to clear it's bit.
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "W1Clear.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
W1Clear::W1Clear(unsigned address, unsigned startBit, unsigned numBits) :
	mEmuMutex(),
	mFpga(OffTargetFPGA::getInstance()),
	mAddress(address),
	mStartBit(startBit),
	mNumBits(numBits),
	mMask(0),
	mValue(0)
{
	mMask = ((1<<mNumBits)-1) << mStartBit ;

	// register ourself to handle the memory locations
	mFpga->registerHandler(mAddress, mAddress,
		[this](const UINT32 address, const UINT16 value, const UINT16 mask)->UINT16{
			return writeHandler(address, value, mask) ;
		},
		[this](const UINT32 address, const UINT16 mask)->UINT16{
			return readHandler(address, mask) ;
		}
	) ;
}

//-------------------------------------------------------------------------------------------------------------
W1Clear::~W1Clear()
{
	mFpga->unRegisterHandler(mAddress) ;
}

//-------------------------------------------------------------------------------------------------------------
void W1Clear::set(UINT16 value)
{
	Mutex::Lock lock(mEmuMutex) ;
	mValue = value & mMask ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
UINT16 W1Clear::writeHandler(const UINT32 address, const UINT16 value, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	UINT16 clear = (value & mask) & mMask ;

	// Can only clear if bit is a 1, otherwise ignore
	UINT16 maskBit(1<<mStartBit) ;
	for (unsigned bit=0; bit < mNumBits; ++bit)
	{
		if (clear & maskBit)
			mValue &= ~maskBit ;
	}

	return mValue ;
}

//-------------------------------------------------------------------------------------------------------------
UINT16 W1Clear::readHandler(const UINT32 address, const UINT16 mask)
{
	Mutex::Lock lock(mEmuMutex) ;
	return mValue & mask ;
}

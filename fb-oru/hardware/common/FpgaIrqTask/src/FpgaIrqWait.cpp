/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FpgaIrqWait.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "FpgaIrqWait.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FpgaIrqWait::FpgaIrqWait(unsigned irqBit) :
	FpgaIrqTask(irqBit, [this](char*){ irqCallback(); }),
	mIrq(false),
	mMutex(),
	mCond(),
	mWaiting(false)
{
}

//-------------------------------------------------------------------------------------------------------------
FpgaIrqWait::~FpgaIrqWait()
{
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaIrqWait::wait()
{
	return wait(0) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FpgaIrqWait::wait(unsigned timeoutMs)
{
	{
		Mutex::Lock lock(mMutex) ;

		// catch early IRQ
		if (mIrq)
		{
			mIrq = false ;
			return true ;
		}

		// need to wait
		mCond.clear() ;
		mWaiting = true ;
	}

	if (timeoutMs == 0)
	{
		mCond.wait() ;
	}
	else
	{
		if (!mCond.wait(timeoutMs))
			return false ;
	}

	if (mIrq)
	{
		mIrq = false ;
		return true ;
	}

	return false ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void FpgaIrqWait::irqCallback()
{
	// signal that IRQ triggered
	Mutex::Lock lock(mMutex) ;
	mIrq = true ;
	if (!mWaiting)
		return ;

	// only set flags when we are waiting - otherwise we can end up with false positives
	mCond.signal() ;
	mWaiting = false ;
}

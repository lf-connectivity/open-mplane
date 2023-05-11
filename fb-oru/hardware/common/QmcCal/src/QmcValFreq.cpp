/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcValFreq.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "QmcValFreq.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
QmcValFreq::QmcValFreq(FreqSaveFunc saveFunc, FreqRestoreFunc restoreFunc) :
	QmcVal(),
	mValue(),
	mSaveFunc(saveFunc),
	mRestoreFunc(restoreFunc)
{
}

//-------------------------------------------------------------------------------------------------------------
QmcValFreq::~QmcValFreq()
{
}

//-------------------------------------------------------------------------------------------------------------
bool QmcValFreq::save()
{
	mValue = mSaveFunc() ;
	setSaved() ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcValFreq::restore()
{
	if (!isSaved())
		return false ;

	mRestoreFunc(mValue) ;
	return true ;
}

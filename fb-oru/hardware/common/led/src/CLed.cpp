/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CLed.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CLed.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CLed::CLed(int index, CLedControl &controller):
	mController( controller ),
	mIndex(index),
	mSettings(),
	mPendingSettings()
{
}

//-------------------------------------------------------------------------------------------------------------
CLed::CLed(int index, CLedControl &controller, LedState state, LedColour colour, unsigned rate):
	mController( controller ),
	mIndex(index),
	mSettings(),
	mPendingSettings()
{
}

//-------------------------------------------------------------------------------------------------------------
CLed::~CLed()
{
}


//-------------------------------------------------------------------------------------------------------------
const int CLed::getIndex()
{
	return mIndex;
}


//-------------------------------------------------------------------------------------------------------------
ILed::LedColour CLed::getColour()
{
	return mSettings.getColour();
}

//-------------------------------------------------------------------------------------------------------------
ILed::LedState CLed::getState()
{
	return mSettings.getState();
}

//-------------------------------------------------------------------------------------------------------------
unsigned CLed::getRate()
{
	return mSettings.getRate();
}


//-------------------------------------------------------------------------------------------------------------
ReturnType::State CLed::setColour(LedColour colour)
{
	ReturnType::State rc = verifyColour( colour );
	if( rc != ReturnType::RT_OK)
		return rc ;

	rc = changeColour(colour) ;
	if( rc != ReturnType::RT_OK )
		return rc ;

	return applyChanges() ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CLed::setState(LedState state)
{
	ReturnType::State rc = changeState(state) ;
	if( rc != ReturnType::RT_OK )
		return rc ;

	return applyChanges() ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CLed::setRate(unsigned rate)
{
	ReturnType::State rc = changeRate(rate) ;
	if( rc != ReturnType::RT_OK )
		return rc ;

	return applyChanges() ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CLed::changeColour(LedColour colour)
{
	mPendingSettings.setColour(colour) ;
	return ReturnType::RT_OK ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CLed::changeState(LedState state)
{
	mPendingSettings.setState(state) ;
	return ReturnType::RT_OK ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CLed::changeRate(unsigned rate)
{
	mPendingSettings.setRate(rate) ;
	return ReturnType::RT_OK ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CLed::applyChanges()
{
	// save settings
	LedSettings currentSettings(mSettings) ;
	mSettings.copyChanged(mPendingSettings) ;
	mPendingSettings.clearChange() ;

	// apply
	ReturnType::State state = mController.setLed( *this );
	if( state != ReturnType::RT_OK )
	{
		// failed to set, so restore previous settings
		mSettings = currentSettings ;
		return state ;
	}

	mSettings.clearChange() ;
	return state ;
}

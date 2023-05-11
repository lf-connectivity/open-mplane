/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CLedControl.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

#include "CLedControl.h"
#include "ILed.h"

using namespace Mplane;

CLedControl::CLedControl( int deviceIndex, int numLeds ):
	Device( Device::LED, deviceIndex, "LedControl" ),
	mNumLeds( numLeds )
{
    mLeds.reserve( numLeds );
}

int CLedControl::getNumberOfLeds()
{
    return mNumLeds;
}

std::shared_ptr<ILed> CLedControl::getLed(int index)
{
    if( index >= mNumLeds )
    {
        char buffer[100];
        sprintf(buffer, "Led index %d out of range - max is %d",index, mNumLeds);
        std::out_of_range e( buffer );
        throw( e );
    }
    return mLeds[ index ];
}

ReturnType::State CLedControl::add(std::shared_ptr<ILed> led)
{
    if( led->getIndex() < mNumLeds )
    {
        mLeds.push_back( led );
        return ReturnType::RT_OK;
    }
    return ReturnType::RT_OUT_OF_RANGE;
}

CLedControl::~CLedControl()
{
}

bool CLedControl::isInitComplete() const
{
	return true ;
}

ReturnType::State CLedControl::setColour(unsigned index, ILed::LedColour setLedColour)
{
	return getLed(index)->setColour(setLedColour) ;
}

ReturnType::State CLedControl::setState(unsigned index, ILed::LedState setLedState)
{
	return getLed(index)->setState(setLedState) ;
}

ReturnType::State CLedControl::setRate(unsigned index, unsigned transitionRate)
{
	return getLed(index)->setRate(transitionRate) ;
}

ReturnType::State CLedControl::groupIndicate(unsigned timeMs)
{
	// does nothing
	return ReturnType::RT_OK ;
}

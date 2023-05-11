/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonSynth.cpp
 * \brief     Implementation of the CommonSynth class
 *
 *
 * \details   This file contains the implementation of the hardware radio
 *            CommonSynth class.
 *
 */

// Includes go here, before the namespace
#include "CommonSynth.h"

using namespace Mplane;

//////// CommonSynth implementation //////////

//---------------------------------------------------------------------------------------------------------------------------------------------------
Mplane::CommonSynth::CommonSynth(std::shared_ptr<ISynthDriver> driver, int index, const std::string& name, Frequency frequency):
	Device( Device::SYNTH, index, name ),
	mFrequency( frequency ),
	mDriver( driver )
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
Mplane::CommonSynth::~CommonSynth()
{

}

//---------------------------------------------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonSynth::doInit()
{
	ReturnType::State rc = mDriver->initialise();

	program();
    setInitResult(rc);
    std::string str = getName() + " Init" + ReturnType::getState(rc);
    setInitResultString(str);
    return rc;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
ReturnType::State Mplane::CommonSynth::program()
{
	return mDriver->program(mFrequency);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Mplane::CommonSynth::postProgram(void)
{
	return mDriver->postProgram();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Mplane::CommonSynth::setFrequency(Frequency frequency)
{
    mFrequency = frequency;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
Frequency Mplane::CommonSynth::getFrequency(void)
{
    return mFrequency;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
Frequency Mplane::CommonSynth::getSynthFrequency()
{
    return mFrequency;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Mplane::CommonSynth::isBadIbsFreq( Frequency frequency )
{
	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Mplane::CommonSynth::isPllLocked(void)
{
    return mDriver->isPllLocked();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Mplane::CommonSynth::isOutOfLock(void)
{
    return mDriver->isOutOfLock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Mplane::CommonSynth::forceOutOfLock(void)
{
	mDriver->forceOutOfLock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
FrequencyOffset Mplane::CommonSynth::checkFrequency( int port, Frequency frequency )
{
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void CommonSynth::show(std::ostream& os)
{
	os << "Synth device : " << getName() << std::endl;
	mDriver->show(os);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void Mplane::CommonSynth::show(void)
{
	show(std::cout);
}

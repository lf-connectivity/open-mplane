/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AttnBase.cpp
 * \brief     Common shared attenuator methods
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "AttnBase.h"
#include <ostream>
#include <sstream>

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
AttnBase::AttnBase(std::shared_ptr<IAttenuatorDriver> driver, int index, const char* name) :
	Device( Device::ATTENUATOR, index, name ),
	Loggable(name, index, "DV"),

	mDriver( driver ),
	mAttenuation(0),
	mAttenuationResidual(0.0),
	mAttenControl(0)
{
	mAttenuation = getMaxAttenuation();
}

//-------------------------------------------------------------------------------------------------------------
AttnBase::~AttnBase()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AttnBase::doInit(void)
{
	ReturnType::State rc = mDriver->initialise();

    setInitResult(rc);
    std::string str = getName() + " Init" + ReturnType::getState(rc);
    setInitResultString(str);
    return rc;
}


//-------------------------------------------------------------------------------------------------------------
void AttnBase::show(void)
{
    eventInfo("----------------------------------------");
    eventInfo("Device:");
    eventInfo("  Name         : %s",getName().c_str());
    eventInfo("  Device Index : %d",getIndex());

    std::ostringstream ss;
    mDriver->show(ss);
    //eventInfo(ss.str().c_str());
    eventInfo("----------------------------------------");
}

//-------------------------------------------------------------------------------------------------------------
Power AttnBase::getAttenuation(void)
{
    return mAttenuation;
}

//-------------------------------------------------------------------------------------------------------------
Power Mplane::AttnBase::getAttenuationResidual(void)
{
    return mAttenuationResidual;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AttnBase::setAttenuation(Power attenuation)
{
    if (!isValidAttenuation(attenuation))
    {
        return ReturnType::RT_OUT_OF_RANGE;
    }

	mAttenControl = calcControl(attenuation) ;
	mAttenuation = calcAttenuation(mAttenControl);

	// calculate residual
	mAttenuationResidual = attenuation - mAttenuation ;

	return mDriver->applyAttenuation(mAttenControl);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AttnBase::setAttenuation(Power attenuation, Temperature temperature)
{
    if (!isValidAttenuation(attenuation))
    {
        return ReturnType::RT_OUT_OF_RANGE;
    }

    mAttenControl = calcControl(attenuation) ;
    mAttenuation = calcAttenuation(mAttenControl);

    // calculate residual
    mAttenuationResidual = attenuation - mAttenuation ;

    return mDriver->applyAttenuation(mAttenControl);
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State AttnBase::setMaxAttenuation()
{
    return setAttenuation( getMaxAttenuation() );
}

//-------------------------------------------------------------------------------------------------------------
Power AttnBase::getMaxAttenuation(void)
{
    return mDriver->getMaxAttenuation();
}

//-------------------------------------------------------------------------------------------------------------
Power AttnBase::getMinAttenuation(void)
{
    return mDriver->getMinAttenuation();
}

//-------------------------------------------------------------------------------------------------------------
unsigned int AttnBase::calcControl(Power attenuation, Temperature temperature)
{
	return mDriver->calcControl(attenuation, temperature) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned int AttnBase::calcControl(Power attenuation)
{
	return mDriver->calcControl(attenuation) ;
}

//-------------------------------------------------------------------------------------------------------------
Power AttnBase::calcAttenuation(unsigned int control)
{
	return mDriver->calcAttenuation(control) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Power AttnBase::limitAttenuation(const Power& attenuation) const
{
	Power limitedAtten(attenuation) ;

	Power max = mDriver->getMaxAttenuation();
	Power min = mDriver->getMinAttenuation();

	if (limitedAtten > max)
		limitedAtten = max ;
	if (limitedAtten < min)
		limitedAtten = min ;

	return limitedAtten ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::AttnBase::isValidAttenuation(const Power& attenuation) const
{
	Power max = mDriver->getMaxAttenuation();
	Power min = mDriver->getMinAttenuation();

	if (attenuation > max)
		return false ;
	if (attenuation < min)
		return false ;

	return true ;
}

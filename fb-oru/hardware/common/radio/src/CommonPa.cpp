/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonPa.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "CommonPa.h"

using namespace Mplane;

CommonPa::CommonPa( int index, const char* name):
	Loggable(name, index, "PA"),
	mIndex(index), mName(name)
{
}

std::shared_ptr<IIdEeprom> CommonPa::getIdEeprom( void )
{
	std::shared_ptr<IIdEeprom> idEeprom(0);
	return idEeprom;
}

float CommonPa::getTemperature(paTempSensor_T temperatureSensorToRead)
{
    return 0.0f;
}

UINT16 CommonPa::getID( void )
{
	return 0x0000;
}

const Power CommonPa::getDesignGain()
{
    Power power (0.0);
    return power;
}

const Power CommonPa::getMaxDesignGain()
{
    Power power (0.0);
    return power;
}

 void CommonPa::updateAvgTemp( void )
{

}

bool CommonPa::isConnected( void )
{
	 return false;
}

UINT16 CommonPa::numberTempSensorsPerPa( void )
{
	return 0;
}

const ReturnType::State CommonPa::setPaEnable( void )
{
	return ReturnType::RT_ERROR;
}

const ReturnType::State CommonPa::setPaDisable( void )
{
	return ReturnType::RT_ERROR;
}

const ReturnType::State CommonPa::getPaState( paState_T& paState )
{
	return ReturnType::RT_ERROR;
}

bool Mplane::CommonPa::getPaGainManualCtrl(UINT16& ctrlRawValue)
{
    return false;
}

bool Mplane::CommonPa::setPaGainManualCtrl(UINT16 ctrlStatus)
{
    return false;
}

bool Mplane::CommonPa::getPaGainOverride(UINT16& overrideRawValue)
{
    return false;
}

bool Mplane::CommonPa::setPaGainOverride(UINT16 overrideStatus)
{
    return false;
}

int CommonPa::getIndex() const {
	return mIndex ;
}

std::string CommonPa::getName() const {
	return mName ;
}

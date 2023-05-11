/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonDevices.cpp
 * \brief     Base class implementation for CommonDevices class.
 *
 *
 * \details   Base class implementation for CommonDevices class.
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "ILoggable.h"

#include "IAdc.h"
#include "IDac.h"
#include "IAttenuator.h"
#include "ILed.h"
#include "ISynth.h"
#include "ICam.h"
#include "IFpgaDev.h"
#include "IGpioExp.h"
#include "ITemperatureSensor.h"

#include "CommonDevices.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CommonDevices::CommonDevices() :
	mDevices(),
	mDeviceTypes()
{
}

//-------------------------------------------------------------------------------------------------------------
CommonDevices::~CommonDevices()
{
}


//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonDevices::initialise()
{
    bool initFail = false;

    ILoggable::logEventInfo("Devices: initialising");

    for (auto dev : mDevices)
    {
        if (dev->initialise() == ReturnType::RT_OK)
        	continue ;

        ILoggable::logEventError("Failed to initialise '%s' device: %s", dev->getName().c_str(), dev->initResultString().c_str());
#ifdef OFF_TARGET
        dev->show();
#endif

		initFail = true;
    }

    if (initFail)
    {
        return ReturnType::RT_OPERATION_FAILED;
    }

    ILoggable::logEventInfo("Devices: initialised ok");

    return ReturnType::RT_OK;
}

//-------------------------------------------------------------------------------------------------------------
bool CommonDevices::shutdown(void)
{
    return true;
}

//-------------------------------------------------------------------------------------------------------------
void CommonDevices::show()
{
    ILoggable::logEventInfo("Device list status:");
    for (auto dev : mDevices)
    {
        dev->show();
    }
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDevice> Mplane::CommonDevices::getDevice(IDevice::Type type, DeviceCollection collection, int index) const
{
	if (mDeviceTypes.find(type) == mDeviceTypes.end())
		return std::shared_ptr<IDevice>() ;

	if (mDeviceTypes.at(type).find(collection) == mDeviceTypes.at(type).end())
		return std::shared_ptr<IDevice>() ;

	if (index >= (int)mDeviceTypes.at(type).at(collection).size())
		return std::shared_ptr<IDevice>() ;

	return mDeviceTypes.at(type).at(collection).at(index) ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDevice> CommonDevices::getDevice(IDevice::Type type, int index) const
{
	return getDevice(type, DeviceCollection::NONE, index) ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAdc> CommonDevices::getRxAdc(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::ADC, DeviceCollection::RX, index)) ;
	if (!device)
		return std::shared_ptr<IAdc>() ;
    return std::dynamic_pointer_cast<IAdc>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAdc> CommonDevices::getDpdAdc(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::ADC, DeviceCollection::DPD, index)) ;
	if (!device)
		return std::shared_ptr<IAdc>() ;
    return std::dynamic_pointer_cast<IAdc>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IDac> CommonDevices::getTxDac(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::DAC, DeviceCollection::TX, index)) ;
	if (!device)
		device = getDevice(IDevice::DAC, index) ;
	if (!device)
		return std::shared_ptr<IDac>() ;
    return std::dynamic_pointer_cast<IDac>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IGpioExp> CommonDevices::getFemGpioExp(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::EXP, DeviceCollection::FEM, index)) ;
	if (!device)
		return std::shared_ptr<IGpioExp>() ;
    return std::dynamic_pointer_cast<IGpioExp>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILedControl> CommonDevices::getLed(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::LED, index)) ;
	if (!device)
		return std::shared_ptr<ILedControl>() ;
    return std::dynamic_pointer_cast<ILedControl>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAttenuator> CommonDevices::getRxIFAttenuator(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::ATTENUATOR, DeviceCollection::RXIF, index)) ;
	if (!device)
		return std::shared_ptr<IAttenuator>() ;
    return std::dynamic_pointer_cast<IAttenuator>(device);

}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAttenuator> CommonDevices::getRxRFAttenuator(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::ATTENUATOR, DeviceCollection::RXRF, index)) ;
	if (!device)
		return std::shared_ptr<IAttenuator>() ;
    return std::dynamic_pointer_cast<IAttenuator>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAttenuator> CommonDevices::getTxIFAttenuator(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::ATTENUATOR, DeviceCollection::TXIF, index)) ;
	if (!device)
		return std::shared_ptr<IAttenuator>() ;
    return std::dynamic_pointer_cast<IAttenuator>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAttenuator> CommonDevices::getTxRFAttenuator(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::ATTENUATOR, DeviceCollection::TXRF, index)) ;
	if (!device)
		return std::shared_ptr<IAttenuator>() ;
    return std::dynamic_pointer_cast<IAttenuator>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAttenuator> CommonDevices::getDpdAttenuator(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::ATTENUATOR, DeviceCollection::DPD, index)) ;
	if (!device)
		return std::shared_ptr<IAttenuator>() ;
    return std::dynamic_pointer_cast<IAttenuator>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISynth> CommonDevices::getTxSynth(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::SYNTH, DeviceCollection::TX, index)) ;
	if (!device)
		return std::shared_ptr<ISynth>() ;
    return std::dynamic_pointer_cast<ISynth>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISynth> CommonDevices::getRxSynth(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::SYNTH, DeviceCollection::RX, index)) ;
	if (!device)
		return std::shared_ptr<ISynth>() ;
    return std::dynamic_pointer_cast<ISynth>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISynth> CommonDevices::getDpdSynth(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::SYNTH, DeviceCollection::DPD, index)) ;
	if (!device)
		return std::shared_ptr<ISynth>() ;
    return std::dynamic_pointer_cast<ISynth>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ISynth> CommonDevices::getSystemSynth(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::SYNTH, DeviceCollection::SYSTEM, index)) ;
	if (!device)
		device = getDevice(IDevice::SYNTH, index) ;
	if (!device)
		return std::shared_ptr<ISynth>() ;
    return std::dynamic_pointer_cast<ISynth>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFpgaDev> CommonDevices::getSystemFpga(int index)
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::FPGA, DeviceCollection::SYSTEM, index)) ;
	if (!device)
		device = getDevice(IDevice::FPGA, index) ;
	if (!device)
		return std::shared_ptr<IFpgaDev>() ;
    return std::dynamic_pointer_cast<IFpgaDev>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ICam> CommonDevices::getCam(int index)
{
    throw std::invalid_argument("getCam() must be implemented by a radio specific base class, if supported.");
    return std::shared_ptr<ICam>();

	std::shared_ptr<IDevice> device(getDevice(IDevice::CAM, index)) ;
	if (!device)
		return std::shared_ptr<ICam>() ;
    return std::dynamic_pointer_cast<ICam>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITemperatureSensor> CommonDevices::getRxTemperatureSensor( int index )
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::TEMPERATURE_SENSOR, DeviceCollection::RX, index)) ;
	if (!device)
	{
		return std::shared_ptr<ITemperatureSensor>() ;
	}

    return std::dynamic_pointer_cast<ITemperatureSensor>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITemperatureSensor> CommonDevices::getTxTemperatureSensor( int index )
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::TEMPERATURE_SENSOR, DeviceCollection::TX, index)) ;
	if (!device)
	{
		return std::shared_ptr<ITemperatureSensor>() ;
	}

    return std::dynamic_pointer_cast<ITemperatureSensor>(device);
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITemperatureSensor> CommonDevices::getSRxTemperatureSensor( int index )
{
	std::shared_ptr<IDevice> device(getDevice(IDevice::TEMPERATURE_SENSOR, DeviceCollection::DPD, index)) ;
	if (!device)
	{
		return std::shared_ptr<ITemperatureSensor>() ;
	}

    return std::dynamic_pointer_cast<ITemperatureSensor>(device);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::CommonDevices::addDevice(std::shared_ptr<IDevice> device, DeviceCollection collection)
{
	// add to initialisation list
	mDevices.push_back(device) ;

	// add to the map
	int index(device->getIndex()) ;
	if (index < 0)
		return ;

	IDevice::Type type(device->getType()) ;
	if (mDeviceTypes.find(type) == mDeviceTypes.end())
		mDeviceTypes[type] = std::map<DeviceCollection, std::vector<std::shared_ptr<IDevice>>>() ;

	if (mDeviceTypes[type].find(collection) == mDeviceTypes[type].end())
		mDeviceTypes[type][collection] = std::vector<std::shared_ptr<IDevice>>() ;

	while (index >= (int)mDeviceTypes[type][collection].size())
		mDeviceTypes[type][collection].push_back(std::shared_ptr<IDevice>()) ;
	mDeviceTypes[type][collection][index] = device ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonDevices::addDevice(std::shared_ptr<IDevice> device)
{
	addDevice(device, DeviceCollection::NONE) ;
}

#ifndef _VRH_IDEVICES_H_
#define _VRH_IDEVICES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDevices.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <stdexcept>
#include <memory>

#include "GlobalTypeDefs.h"
#include "IDevice.h"

namespace Mplane
{

// Forward declare IDevice sub classes
class ITemperatureSensor;
class II2c;
class IAdc;
class IAttenuator;
class IDac;
class ISynth;
class ISpi;
class ICam;
class IGpioExp;
class IFpgaDev;
class ILedControl;

class IDevices
{
public:
    IDevices(){}
    virtual ~IDevices(){}

    /**
     * Some devices are stored in collections. For example, an ADC type may be collected as TX ADCs and RX ADCS
     * This list of enumerations defines the collections supported
     */
    enum class DeviceCollection {
    	NONE,
		TX,
		RX,
		DPD,
		SYSTEM,
		RXIF,
		RXRF,
		TXIF,
		TXRF,
		FEM,
    } ;

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() = 0;

    /**
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible. The primary purpose is to protect the
     * FEM stages.
     * @return true if successful
     */
    virtual bool shutdown(void) = 0;

    /**
     * Generic device access. Given a device type (and an optional index) retrieves the device pointer
     * if available; returns null pointer otherwise
     */
    virtual std::shared_ptr<IDevice> getDevice( IDevice::Type type, DeviceCollection collection, int index=0 ) const =0 ;
    virtual std::shared_ptr<IDevice> getDevice( IDevice::Type type, int index=0 ) const =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a receiver ADC device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to maximum receiver ADCs.
     *
     * @return a reference to the ADC for the given index.
     *
     * @throws invalid_argument exception if the index is invalid, or the device is not supported.
     */
    virtual std::shared_ptr<IAdc> getRxAdc( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a DPD ADC device virtual interface.
     *
     * @param portIndex zero-based index from 0 to maximum receiver ADCs.
     *
     * @return a reference to the DPD ADC for the given index.
     *
     * @throws invalid_argument exception if the device is not supported.
     */
    virtual std::shared_ptr<IAdc> getDpdAdc( int portIndex ) =0 ;


    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a transmit DAC device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to number of TX DACs
     *
     * @return a reference to the DAC for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or device is not supported.
     */
    virtual std::shared_ptr<IDac> getTxDac( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a LED device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to number of Leds
     *
     * @return a reference to the LED for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or device is not supported.
     */
    virtual std::shared_ptr<ILedControl> getLed( int index ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a receiver IF attenuator device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to number of port attenuators
     *
     * @return a reference to the IAttenuator device interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<IAttenuator> getRxIFAttenuator( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a receiver RF attenuator device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to max port index
     *
     * @return a reference to the IAttenuator interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<IAttenuator> getRxRFAttenuator( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a transmit IF attenuator device interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to maximum devices
     *
     * @return a reference to the IAttenuator interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<IAttenuator> getTxIFAttenuator( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a transmit RF Attenuator device interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to 'MAX Attenuators - 1'
     *
     * @return a reference to the IAttenuator interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<IAttenuator> getTxRFAttenuator( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a DPD RF Attenuator device interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to 'MAX Attenuators - 1'
     *
     * @return a reference to the IAttenuator interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<IAttenuator> getDpdAttenuator( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a transmit synthesiser device interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to number of devices
     *
     * @return a reference to the ISynth interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<ISynth> getTxSynth( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a receive synthesiser device interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to number of devices
     *
     * @return a reference to the ISynth interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<ISynth> getRxSynth( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a sample path synthesiser device interface.
     *
     * @param portIndex zero-based index from 0 to number of devices
     *
     * @return a reference to the ISynth interface for the device.
     *
     * @throws invalid_argument exception if the device is not supported
     */
    virtual std::shared_ptr<ISynth> getDpdSynth( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a system clock synthesiser device interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to number of devices
     *
     * @return a reference to the ISynth interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<ISynth> getSystemSynth( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a system FPGA device interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to number of devices
     *
     * @return a reference to the IFpgaDev interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<IFpgaDev> getSystemFpga( int portIndex ) =0 ;


    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a general purpose control and measurement device virtual interface.
     * The port index must be between zero and the number of devices supported
     * by the hardware.
     *
     * @param portIndex zero-based index from 0 to maximum devices.
     *
     * @return a reference to the ICam interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid, or the device is not supported.
     */
    virtual std::shared_ptr<ICam> getCam( int portIndex ) =0 ;


    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a gpio expander device virtual interface.
     * The port index must be between zero and the number of devices supported
     * by the hardware.
     *
     * @param portIndex zero-based index from 0 to maximum devices.
     *
     * @return a reference to the IGpioExp interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid, or the device is not supported.
     */
    virtual std::shared_ptr<IGpioExp> getFemGpioExp( int portIndex ) =0 ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a receiver temperature sensor device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to maximum receiver ports.
     *
     * @return a reference to the temperature sensor for the given index.
     *
     * @throws invalid_argument exception if the index is invalid, or the device is not supported.
     */
    virtual std::shared_ptr<ITemperatureSensor> getRxTemperatureSensor( int portIndex ) =0;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a transmitter temperature sensor device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to maximum transmitter ports.
     *
     * @return a reference to the temperature sensor for the given index.
     *
     * @throws invalid_argument exception if the index is invalid, or the device is not supported.
     */
    virtual std::shared_ptr<ITemperatureSensor> getTxTemperatureSensor( int portIndex ) =0;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a observation receiver temperature sensor device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to maximum receiver ports.
     *
     * @return a reference to the temperature sensor for the given index.
     *
     * @throws invalid_argument exception if the index is invalid, or the device is not supported.
     */
    virtual std::shared_ptr<ITemperatureSensor> getSRxTemperatureSensor( int portIndex ) =0;


    /**
     * Method used to show the status of all the devices in the device list.
     */
    virtual void show() = 0;


};

/**
 * Defines a factory class that is called by the common radio during initialisation
 * to create all the physical devices fitted to the radio and initialise them.
 */
class IDevicesFactory
{
public:
    /**
     * Factory method created by a radio specific implementation
     * @return a reference to the radio device interface.
     */
    static std::shared_ptr<IDevices> create();
};


}

#endif /* _VRH_IDEVICES_H_ */

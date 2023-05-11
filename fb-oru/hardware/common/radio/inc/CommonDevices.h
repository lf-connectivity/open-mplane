#ifndef _COMMONDEVICES_H_
#define _COMMONDEVICES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonDevices.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <memory>
#include <vector>
#include <map>

#include "IDevices.h"
#include "IDevice.h"

namespace Mplane
{


class CommonDevices: public IDevices
{
public:
    CommonDevices();
    virtual ~CommonDevices();

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise();

    /**
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible. The primary purpose is to protect the
     * FEM stages.
     * @return true if successful
     */
    virtual bool shutdown(void);

    /**
     * Generic device access. Given a device type (and an optional index) retrieves the device pointer
     * if available; returns null pointer otherwise
     */
    virtual std::shared_ptr<IDevice> getDevice( IDevice::Type type, DeviceCollection collection, int index=0 ) const override ;
    virtual std::shared_ptr<IDevice> getDevice( IDevice::Type type, int index=0 ) const override ;




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
    virtual std::shared_ptr<IAdc> getRxAdc( int portIndex ) ;

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
    virtual std::shared_ptr<IAdc> getDpdAdc( int portIndex ) ;


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
    virtual std::shared_ptr<IDac> getTxDac( int index ) ;


    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to number of devices
     *
     * @return a reference to the device for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or device is not supported.
     */
    virtual std::shared_ptr<IGpioExp> getFemGpioExp( int index ) ;


    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a LED device virtual interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to number of LEDs
     *
     * @return a reference to the LED for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or device is not supported.
     */
    virtual std::shared_ptr<ILedControl> getLed( int index ) ;

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
    virtual std::shared_ptr<IAttenuator> getRxIFAttenuator( int portIndex ) ;

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
    virtual std::shared_ptr<IAttenuator> getRxRFAttenuator( int index ) ;

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
    virtual std::shared_ptr<IAttenuator> getTxIFAttenuator( int index ) ;

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
    virtual std::shared_ptr<IAttenuator> getTxRFAttenuator( int portIndex ) ;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a DPD Attenuator device interface. The port index must be between zero and the number
     * of devices supported by the hardware.
     *
     * @param portIndex zero-based index from 0 to 'MAX Attenuators - 1'
     *
     * @return a reference to the IAttenuator interface for the given index.
     *
     * @throws invalid_argument exception if the index is invalid or the device is not supported.
     */
    virtual std::shared_ptr<IAttenuator> getDpdAttenuator( int portIndex ) ;

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
    virtual std::shared_ptr<ISynth> getTxSynth( int portIndex ) ;

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
    virtual std::shared_ptr<ISynth> getRxSynth( int index ) ;

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
    virtual std::shared_ptr<ISynth> getDpdSynth( int index ) ;

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
    virtual std::shared_ptr<ISynth> getSystemSynth( int index ) ;

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
    virtual std::shared_ptr<IFpgaDev> getSystemFpga( int index ) ;


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
    virtual std::shared_ptr<ICam> getCam( int portIndex ) ;

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
    virtual std::shared_ptr<ITemperatureSensor> getRxTemperatureSensor( int portIndex ) ;

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
    virtual std::shared_ptr<ITemperatureSensor> getTxTemperatureSensor( int portIndex ) ;

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
    virtual std::shared_ptr<ITemperatureSensor> getSRxTemperatureSensor( int portIndex ) ;


    /**
     * Method used to show the status of all the devices in the device list.
     */
    virtual void show();

protected:
    /**
     * Add the device to the list
     */
    void addDevice(std::shared_ptr<IDevice> device, DeviceCollection collection) ;
    void addDevice(std::shared_ptr<IDevice> device) ;

private:
    /**
     * A vector of physical radio devices on this radio, a collection
     * of ADCs, DACs, Synths, attenuators etc. Used during initialisation
     * to setup all devices.
     */
    std::vector< std::shared_ptr<IDevice> > mDevices;

    /**
     * Map from device type to a vector of devices added for that type. Device pointers are all the same
     * stored in mDevices.
     */
    std::map<IDevice::Type, std::map<DeviceCollection, std::vector<std::shared_ptr<IDevice>>>> mDeviceTypes ;

};

} /* namespace Mplane */

#endif /* _COMMONDEVICES_H_ */

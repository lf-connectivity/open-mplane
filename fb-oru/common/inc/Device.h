#ifndef _COMMON_DEVICE_H_
#define _COMMON_DEVICE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Device.h
 * \brief     A file to define generic interface to all radio physical devices
 *
 *
 * \details   A file to define generic interface to all radio physical devices
 *
 */

// Includes go here, before the namespace
#include <vector>
#include <string>

#include "IDevice.h"
#include "Initialise.h"

namespace Mplane
{

/*! \brief  Generic Device interface
 *
 *  A virtual interface base class defining an interface
 *  that must be implemented by all physical radio devices
 *  such as Dacs, Adcs, attenuators and synthesisers.
 *
 *  The interface allows all actual devices to be held in a
 *  device list that is used during start up to
 *  ensure all device are initialised to their correct state.
 *
 *  All IDevices must support the Initialise interface
 *
 */
class Device: public virtual IDevice, public Initialise
{
public:

    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class DeviceTestCase;

    using Type = IDevice::Type ;

    /**
     * This method is implemented by the final device implementation
     * to indicate its type.
     *
     * @return enumerated device type.
     */
    virtual Device::Type getType() override;

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() override;

    /**
     * Get the results from initialisation (useful for debugging failure)
     */
    virtual std::string initResultString() override ;


    /*! \brief Get the devices index
     *
     * Get the zero based index that can be used to reference the device from
     * a list of radio devices.
     *
     * \return zero-based index of the device
     */
    virtual int getIndex() override;

    /*! \brief Get the device name string
     *
     * A string name associated with the device used in logging and debugging.
     *
     * \return Device name string
     */
    virtual std::string getName() override;

    /*! \brief  Display the device data and information related to its general
     * status.
     *
     *  Display the state of the device registers on the console or log file
     */
    virtual void show(void) =0;

    /*! \brief Destructor
     *
     */
    virtual ~Device();

protected:

    Device(Device::Type type, int index, const std::string& name);

private:
    /**
     * the sub class device type.
     */
    Device::Type mType;
    /*!
     * zero-based index of the device, set by constructor
     */
    int mIndex;
    /*!
     * name string for the device, set by constructor
     */
    std::string mName;

};


} /* namespace Mplane */

#endif /* _COMMON_DEVICE_H_ */

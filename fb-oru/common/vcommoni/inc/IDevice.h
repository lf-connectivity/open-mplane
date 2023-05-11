/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDevice.h
 * \brief     Virtual interface to Device
 *
 *
 * \details   This is a "proper" virtual interface and doesn't have any concrete class data!
 *
 */


#ifndef INC_IDEVICE_H_
#define INC_IDEVICE_H_

#include <vector>
#include <string>

#include "GlobalTypeDefs.h"

namespace Mplane {

/*!
 * \class  IDevice
 * \brief
 * \details
 *
 */
class IDevice {
public:
	IDevice() {}
	virtual ~IDevice() {}

    enum Type
    {
        DAC,                    //!> Digital to Analogue Converter device type
        ADC,                    //!> Analogue to Digital Converter device type
        SYNTH,                  //!> Synthesiser device type
        ATTENUATOR,             //!> Attenuator device type
        CAM,                    //!> Control And Measurement device type
        FPGA,                   //!> Field Programmable Gate Array device type
        LED,                    //!> Light Emitting Diode device type
        REF,                    //!> 10MHz Reference device type
        MDIO,                   //!> Management Data Input/Output (Ethernet) device type
		BNC,                    //!> BNC routing device type (located, if fitted, on the 10MHz Reference module)
		LNA,                    //!> Low Noise Amplifier device type
		EXP,                    //!> GPIO Expander device typer
		MUX,                    //!> Multiplexer device type
		REFCLOCK,               //!> Reference clock
		TEMPERATURE_SENSOR,     //!> Temperature sensor device type
		CONFIG,                 //!> Configuration
		SENSOR,					//!> Other (non-temperature) sensor
    };

    /**
     * This method is implemented by the final device implementation
     * to indicate its type.
     *
     * @return enumerated device type.
     */
    virtual Type getType() =0 ;

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() =0 ;

    /**
     * Get the results from initialisation (useful for debugging failure)
     */
    virtual std::string initResultString() =0 ;

    /*! \brief Get the devices index
     *
     * Get the zero based index that can be used to reference the device from
     * a list of radio devices.
     *
     * \return zero-based index of the device
     */
    virtual int getIndex() =0 ;

    /*! \brief Get the device name string
     *
     * A string name associated with the device used in logging and debugging.
     *
     * \return Device name string
     */
    virtual std::string getName() =0 ;

    /*! \brief  Display the device data and information related to its general
     * status.
     *
     *  Display the state of the device registers on the console or log file
     */
    virtual void show(void) =0;

} ;

}

#endif /* INC_IDEVICE_H_ */

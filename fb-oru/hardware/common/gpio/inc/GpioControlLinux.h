/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      GpioControlLinux.h
 * \brief     GPIO control using Linux devices
 *
 *
 * \details   Implements the GPIO control. Actual implementation is via Linux I2c device
 * 				drivers which map to physical devices on the board connected to the processor
 *
 */


#ifndef COMMON_GPIO_INC_GPIOCONTROLLINUX_H_
#define COMMON_GPIO_INC_GPIOCONTROLLINUX_H_

#include "IGpioControl.h"
#include <mutex>
#include <map>
#include <string>

namespace Mplane {

/*!
 * \class  I2cBusLinux
 * \brief
 * \details
 *
 */
class GpioControlLinux : public IGpioControl {
public:
	/**
	 * The Linux object instance needs a path for an gpio device (e.g. something like "/dev/gpiochipN")
	 */
	explicit GpioControlLinux(const std::string& classPath, const std::string& devPath,
			const std::string& label, unsigned base, unsigned ngpio) ;

	virtual ~GpioControlLinux() ;

    /*! \brief  Set direction of GPIO line
     *
     *  Method used to set the direction of a GPIO line at a specified index.
     *
     *  \return  bool - Whether method is successful
     */
    virtual bool setDirection(unsigned index, GpioDirection dir) override;

    /*! \brief  Get direction of GPIO line
     *
     *  Method used to get the direction of a GPIO line at a specified index.
     *
     *  \return  bool - Whether method is successful
     */
    virtual bool getDirection(unsigned index, GpioDirection& dir) override;

    /*! \brief  Set value of GPIO line
     *
     *  Method used to set the value of a GPIO line at a specified index.
     *
     *  \return  bool - Whether method is successful
     */
    virtual bool setValue(unsigned index, int value) override;

    /*! \brief  Get value of GPIO line
     *
     *  Method used to get the value of a GPIO line at a specified index.
     *
     *  \return  bool - Whether method is successful
     */
    virtual bool getValue(unsigned index, int& value) override;

	/**
	 * Error string set whenever any method fails. Reading the error string clears the internal error string
	 */
	virtual std::string error() override ;

	/**
	 * DEBUG: Enable/disable debug
	 */
	virtual void setDebug(bool debug) override ;


protected:

	/**
	 * Utility for updating the error string
	 * Always returns false, so can be used to both set the error and return from the calling method
	 */
	bool setError(const std::string& error) ;

	/**
	 * Get the debug flag
	 */
	bool debug() const ;

	/**
	 * Check if the pin index is valid
	 */
	bool isPinIndexValid(unsigned pinIndex) ;

    /*
     *  Method used to check if the pin is exported
     */
    bool isExported(unsigned pinIndex);

    /*
     *  Method used to export a GPIO pin
     */
    bool doExport(unsigned pinIndex);

    /*
     *  Method used to unexport a GPIO pin
     */
	bool doUnexport(unsigned pinIndex);

    /*
     *  Method used to set direction for a pin
     */
	bool doSetDirection(unsigned pinIndex, GpioDirection dir);

    /*
     *  Method used to get direction for a pin
     */
	bool doGetDirection(unsigned pinIndex, GpioDirection& dir);

    /*
     *  Method used to write data to a GPIO pin
     */
	bool doSetValue(unsigned pinIndex, int value);

    /*
     *  Method used to read a GPIO pin
     */
	bool doGetValue(unsigned pinIndex, int& value);

private:
	std::string mDevicePath ;
	std::string mGpioPath;
	std::string mError ;
	std::string mLabel;
	std::mutex mMutex;                    //!> Mutex to protect the read and write operations
	std::map<int,bool> mExportedPins;     //!> Map of pin index and export status
	unsigned mBaseIndex;                  //!> Start index of the GPIO for this device
	unsigned mNumGpios;                   //!> Number of GPIOs available for this device
	bool mDebug ;
#ifdef OFF_TARGET
	std::map<int,int> mPinValue;          //!> Map of pin index and pin value
	std::map<int,GpioDirection> mPinDir;  //!> Map of pin index and pin direction
#endif
} ;

}

#endif /* COMMON_GPIO_INC_GPIOCONTROLLINUX_H_ */

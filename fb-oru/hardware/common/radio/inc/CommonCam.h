#ifndef _RADIO_HARDWARE_COMMONCAM_H_
#define _RADIO_HARDWARE_COMMONCAM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCam.h
 * \brief     Defines an interface for a general purpose control and measurement device
 *
 *
 * \details   Defines an interface for a general purpose control and measurement device
 *
 */


#include <string>
#include "ICam.h"
#include "Device.h"


namespace Mplane
{

/**
 * This class defines a base class for general purpose control and measurement
 * devices that include multiple channel ADCs, DACs, CPIO etc.
 */
class CommonCam:  public virtual ICam, public Device
{
public:

    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method in Initialise.
     *  This is pure virtual and MUST be implemented by inheritors.
     *
     *  Means that this CommonAdc class does not provide any ADC-type specific
     *  initialisation. That is left to the inheritors who know what
     *  device they are.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "ADC INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit() = 0;


    /*! \brief  Dump the ADC registers
     *
     *  Dump the state of the ADC registers to the console or log file
     */
    virtual void show(void) override;


    /**
      * This virtual method is used to request that an A/D channel, selected through the index,
      * start conversion and on completion the data is return to the called in an integer. An out of range exception
      * is thrown if the channel index is invalid.
      *
      * @note this method may be overloaded by any real CAM device implementations to provide the functionality.
      *
      * @note the if out of range exception is thrown, these are programming errors and must be corrected.
      *
      * @param channleIndex 0 based channel selector
      * @return the converted value for the given channel index
      */
     virtual ReturnType::State readAdc( int channelIndex, int &value ) override ; /* throw (std::out_of_range) */

     /**
      * This virtual method is used to write a value to the selected D/A channel.
      * An out of range exception is thrown if the channel index is invalid, or the value to
      * be written exceeds the range of the device.
      *
      * @note this method may be overloaded by any real CAM device implementations to provide the functionality.
      *
      * @note the if out of range exception is thrown, these are programming errors and must be corrected.
      *
      * @param channelIndex 0 base channel selector
      * @param value raw value to be written
      * @return true if write successful
      */
     virtual bool writeDac( int channelIndex, int value ) override ; /* throw (std::out_of_range) */

     /**
      * This virtual method is used to request the of an A/D channel through the index for a
      * free running conversion, i.e. the method will return the result of the last converted value.
      * An out of rage exception is thrown if the channel index is invalid or the device is not set
      * to free run.
      *
      * @note this method may be overloaded by any real CAM device implementations to provide the functionality.
      *
      * @note the if out of range exception is thrown, these are programming errors and must be corrected.
      *
      * @param channleIndex 0 based channel selector
      * @return the converted value for the given channel index
      */
     virtual int getValue( int channelIndex ) override ; /* throw (std::out_of_range) */

     /**
      * Pure virtual method used to set the GPIO output of the selected bit to the given value.
      * An out of range exception is thrown if the bit select exceeds the number of GPIO output lines
      * available on the device.
      *
      * @note this method may be overloaded by any real CAM device implementations to provide the functionality.
      *
      * @note the if out of range exception is thrown, these are programming errors and must be corrected.
      *
      * @param bitSelect 0 based bit number used to determine the output line to set
      * @param value true turns the output line on, false turns it off
      * @return true if set OK, otherwise false
      */
     virtual bool setOutput( unsigned bitSelect, unsigned value ) override ; /* throw (std::out_of_range) */

     /**
      * Virtual method used to get the value of a GPIO output line corresponding to the selected bit value.
      * An out of range exception is thrown if the bit select exceeds the number of GPIO output lines
      * available on the device.
      *
      * @note this method may be overloaded by any real CAM device implementations to provide the functionality.
      *
      * @note the if out of range exception is thrown, these are programming errors and must be corrected.
      *
      * @param bitSelect 0 based bit number used to determine the output line to get
      * @return true if the output is on or false if it's off.
      */
     virtual bool getOutput( unsigned bitSelect ) override ; /* throw (std::out_of_range) */

     /**
      * Virtual method used to get the value of a GPIO input line corresponding to the selected bit value.
      * An out of range exception is thrown if the bit select exceeds the number of GPIO input lines
      * available on the device.
      *
      * @note this method may be overloaded by any real CAM device implementations to provide the functionality.
      *
      * @note the if out of range exception is thrown, these are programming errors and must be corrected.
      *
      * @param bitSelect 0 based bit number used to determine the input line to get
      * @return true if the input is on or false if it's off.
      */
     virtual bool getInput( int bitSelect ) override ; /* throw (std::out_of_range) */

     /**
      * Virtual method used to set the a multi-channel A/D converter to free run, periodically converting
      * all channels. Setting value true, starts free running conversion, false stops it.
      * Throws the out of range exception if free running mode not supported by the device.
      *
      * @note this method may be overloaded by any real CAM device implementations to provide the functionality.
      *
      * @note the if out of range exception is thrown, these are programming errors and must be corrected.
      *
      * @param value true starts free running conversion, false stops it.
      * @return the value set.
      */
     virtual bool setFreeRun( bool value ) override ; /* throw (std::out_of_range) */

     /**
      * Virtual method used to get the a multi-channel A/D converter to free run mode.
      * Throws the out of range exception if free running mode not supported by the device.
      *
      * @note this method may be overloaded by any real CAM device implementations to provide the functionality.
      *
      * @note the if out of range exception is thrown, these are programming errors and must be corrected.
      *
      * @return true if free running otherwise false.
      */
     virtual bool getFreeRun( ) override ; /* throw (std::out_of_range) */

     /**
      * Virtual method used to get the a temperature from one of three
      * sensors inputs on the CAM AMC7812
      *
      * \param sensor 0 based sensor selection.
      * \return floating point number in ˚C.
      */
     virtual float  getTemperature(short int readTempSensor) = 0;

     /**
      * Pure virtual method used to set the ADC gain of the selected channel.
      * An out of range exception is thrown if the channel select is exceeded
      *
      * @param The channel to select
      * @param The ADC range to apply
      * @return true if set OK, otherwise false
      */
     virtual bool setAdcGain( unsigned int channel, adcGain_T adcGain) override ; /* throw (std::out_of_range) */

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     *
     *  \param index  zero-based index of the CAM
     *  \param name   name string for the CAM
     */
    CommonCam( int index, const char* name);

    /*! \brief Destructor
     *
     */
    virtual ~CommonCam();


protected:



private:

};

}


#endif /* _COMMONCAM_H_ */

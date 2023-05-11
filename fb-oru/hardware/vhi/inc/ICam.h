#ifndef _VRH_ICAM_H_
#define _VRH_ICAM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICam.h
 * \brief     Pure virtual interface that defines methods need to access the functionality of most control and measurement devices.
 *
 *
 * \details   Pure virtual interface that defines methods need to access the functionality of most control and measurement devices.
 *
 */

#include <stdexcept>
#include <memory>

#include "IDevice.h"

namespace Mplane
{

class ICam: public virtual IDevice
{
public:

    /** \brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the generic CAM
     *  object. This must be implemented using the singleton pattern by the
     *  specific radio implementation.
     *
     *  Must be define in: hardware/<BOARD>/radio/src/<Board>CamFactory.cpp
     *
     *  Test mock defined in: vrh/test/src/TestICam.cpp //TODO
     *
     *
     */
    static std::shared_ptr<ICam> getInstance(int deviceIndex);

    /**
     * This pure virtual method is used to request that an A/D channel, selected through the index,
     * start conversion and on completion the data is return to the called in an integer. An out of range exception
     * is thrown if the channel index is invalid.
     *
     * @note the if out of range exception is thrown, these are programming errors and must be corrected.
     *
     * @param channleIndex 0 based channel selector
     * @return the converted value for the given channel index
     */
    virtual ReturnType::State readAdc( int channelIndex, int &value ) =0 ; /* throw (std::out_of_range) */

    /**
     * This pure virtual method is used to write a value to the selected D/A channel.
     * An out of range exception is thrown if the channel index is invalid, or the value to
     * be written exceeds the range of the device.
     *
     * @note the if out of range exception is thrown, these are programming errors and must be corrected.
     *
     * @param channelIndex 0 base channel selector
     * @param value raw value to be written
     * @return true if write successful
     */
    virtual bool writeDac( int channelIndex, int value ) =0 ; /* throw (std::out_of_range) */

    /**
     * This pure virtual method is used to request the of an A/D channel through the index for a
     * free running conversion, i.e. the method will return the result of the last converted value.
     * An out of rage exception is thrown if the channel index is invalid or the device is not set
     * to free run.
     *
     * @note the if out of range exception is thrown, these are programming errors and must be corrected.
     *
     * @param channleIndex 0 based channel selector
     * @return the converted value for the given channel index
     */
    virtual int getValue( int channelIndex ) =0 ; /* throw (std::out_of_range) */

    /**
     * Pure virtual method used to set the GPIO output of the selected bit to the given value.
     * An out of range exception is thrown if the bit select exceeds the number of GPIO output lines
     * available on the device.
     * @param bitSelect 0 based bit number used to determine the output line to set
     * @param value true turns the output line on, false turns it off
     * @return true if set OK, otherwise false
     */
    virtual bool setOutput( unsigned bitSelect, unsigned value ) =0 ; /* throw (std::out_of_range) */

    /**
     * Pure virtual method used to get the value of a GPIO output line corresponding to the selected bit value.
     * An out of range exception is thrown if the bit select exceeds the number of GPIO output lines
     * available on the device.
     * @param bitSelect 0 based bit number used to determine the output line to get
     * @return true if the output is on or false if it's off.
     */
    virtual bool getOutput( unsigned bitSelect ) =0 ; /* throw (std::out_of_range) */

    /**
     * Pure virtual method used to get the value of a GPIO input line corresponding to the selected bit value.
     * An out of range exception is thrown if the bit select exceeds the number of GPIO input lines
     * available on the device.
     * @param bitSelect 0 based bit number used to determine the input line to get
     * @return true if the input is on or false if it's off.
     */
    virtual bool getInput( int bitSelect ) =0 ; /* throw (std::out_of_range) */

    /**
     * Pure virtual method used to set the a multi-channel A/D converter to free run, periodically converting
     * all channels. Setting value true, starts free running conversion, false stops it.
     * Throws the out of range exception if free running mode not supported by the device.
     *
     * @param value true starts free running conversion, false stops it.
     * @return the value set.
     */
    virtual bool setFreeRun( bool value ) =0 ; /* throw (std::out_of_range) */

    /**
     * Pure virtual method used to get the a multi-channel A/D converter to free run mode.
     * Throws the out of range exception if free running mode not supported by the device.
     *
     * @return true if free running otherwise false.
     */
    virtual bool getFreeRun( ) =0 ; /* throw (std::out_of_range) */

    /**
     * Pure virtual method used to get the temperature from one of three
     * sensors inputs on the CAM AMC7812
     *
     * @param channleIndex 0 based channel selector
     * @return Temperature value in DegC
     */
    virtual float getTemperature( short int readTempSensor ) = 0;

    /**
     * Pure virtual method used to get the board number from CAM AMC7812
     *
     * @return Enumerated type of the board connected to the VSWR port.
     */
    virtual int readExternalBoardNumber() = 0;

    /*
     * The board version - although index is from 0 to 15, board revisions start at 1.
     */
    enum boardRevision
    {
        REV_1,
        REV_2,
        REV_3,
        REV_4,
        REV_5,
        REV_6,
        REV_7,
        REV_8,
        REV_9,
        REV_10,
        REV_11,
        REV_12,
        REV_13,
        REV_14,
        REV_15,
        REV_16,
        REV_UNKNOWN
    };

    /**
     * Pure virtual method used to get the board revision from CAM AMC7812
     *
     * @return Enumerated type of the board revision we are running on.
     */
    virtual boardRevision readBoardRevision() = 0;

    typedef enum
    {
        TWO_X_REF = 0x0,
        REF       = 0x1
    } adcGain_T; // !> Adc gain on a per channel basis

    /**
     * Pure virtual method used to set the ADC gain of the selected channel.
     * An out of range exception is thrown if the channel select is exceeded
     *
     * @param The channel to select
     * @param The ADC range to apply
     * @return true if set OK, otherwise false
     */
    virtual bool setAdcGain( unsigned int channel, adcGain_T adcGain) =0 ; /* throw (std::out_of_range) */

protected:
    // Must be defined in hardware/<BOARD>/radio/src/<Board>Cam.cpp
    static const char* mDevName;

    ICam() {};

    virtual ~ICam(){};
};

}

#endif /* _VRH_ICAM_H_ */

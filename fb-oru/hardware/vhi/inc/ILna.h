#ifndef _VHI_ILNA_H_
#define _VHI_ILNA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILna.h
 * \brief     A file to define generic interface to an ILna (LNA functions on the 10MHz Reference) Module
 *
 *
 * \details   A file to define generic interface to an ILna (LNA functions on the 10MHz Reference) Module
 *
 */

#include <vector>
#include <stdexcept>
#include <memory>

#include "GlobalTypeDefs.h"
#include "II2c.h"
#include "Frequency.h"

namespace Mplane
{

/*! \brief  Generic ILna interface
 *
 *  A virtual interface base class defining an interface to a ILna bus.
 *  The interface contains configuration and control aspects.
 */
class ILna
{
public:

    /*! \brief LNA input path enumeration.
     *
     */
    typedef enum
    {
        LNA_INPUT_PATH_1A = 0,
        LNA_INPUT_PATH_1B,
        LNA_INPUT_PATH_1OFF,    //!> Used to 'park' path 1A/1B in to a protection mode.
        LNA_INPUT_PATH_2A,
        LNA_INPUT_PATH_2B,
        LNA_INPUT_PATH_UNSET    //!> Used if unable to retrieve a value
    } lnaInputPath_T;

    /*! \brief LNA output path enumeration.
     *
     */
    typedef enum
    {
        LNA_OUTPUT_PATH_1 = 0,
        LNA_OUTPUT_PATH_2,
        LNA_OUTPUT_PATH_UNSET    //!> Used if unable to retrieve a value
    } lnaOutputPath_T;

    /*! \brief LNA Band enable enumeration. These relate to specific frequency bands
     *
     */
    typedef enum
    {
        LNA_BAND_A = 0,
        LNA_BAND_B,
        LNA_BAND_C,
        LNA_BAND_OFF,        //!> Used to turn off when input path=1B output path=1
        LNA_BAND_NOT_IN_USE, //!> LNA band is only used for in path=1A/1B output path=1
        LNA_BAND_UNSET       //!> Used if unable to retrieve a value
    } lnaBandEnable_T;

    /*! \brief LNA Temperature alarm enumeration
     *
     */
    typedef enum
    {
        LNA_TEMP_ALARM_NONE = 0,
        LNA_TEMP_ALARM_PRIMARY,
        LNA_TEMP_ALARM_SECONDARY,
        LNA_TEMP_ALARM_BOTH,
        LNA_TEMP_ALARM_UNSET    //!> Used if unable to retrieve a value
    } lnaTempAlarm_T;

    /*!
     *
     * \brief Primary/secondary temperature sensor.
     *
     */
    typedef enum
    {
        LNA_PRIMARY_TEMP_SENSOR = 0,
        LNA_SECONDARY_TEMP_SENSOR
    } lnaTempSensor_T;

    /*! \brief Destructor
     *
     */
    virtual ~ILna() { };

    /*! \brief Pure virtual method to select the path
     *
     * \param  lnaOutputPath Output path to select
     * \param  lnaInputPath  Input path to select
     * \return Return state of the set command if successful or not
     */
    virtual ReturnType::State selectPath( lnaOutputPath_T lnaOutputPath,
                                          lnaInputPath_T  lnaInputPath ) = 0;

    /*! \brief Pure virtual method to get the Input path configuration
     *
     * \param lnaOutputPath Output path to select
     * \return Input path configuration for the selected input path
     */
    virtual lnaInputPath_T getPath( lnaOutputPath_T lnaOutputPath ) = 0;

    /*! \brief Pure virtual method to get the LNA path configuration
     *
     * \param none
     * \return LNA Band configuration
     */
    virtual lnaBandEnable_T getLna( void ) = 0;

    /*! \brief Pure virtual method to get the LNA path configuration frequency band
     *
     * \param bandLow	Lower frequency limit of selected band
     * \param bandHigh	Upper frequency limit of selected band
     * \return LNA Band configuration
     */
    virtual void getFreqBand(Frequency& bandLow, Frequency& bandHigh ) = 0;

    /*! \brief Pure virtual method to check that the supplied frequency
     *         is with in the currently selected LNA band.
     *
     * \param The frequency to check
     * \return True or False.
     */
    virtual bool isFreqInLnaBand( Frequency suppliedFrequency ) = 0;

    /*! \brief Pure virtual method to get the temperature alarm status
     *
     * \param  None
     * \return LNA temperature alarm status
     */
    virtual lnaTempAlarm_T getTempAlarm( void ) = 0;

    /*!
     *
     * \brief Pure virtual method to get the temperature value
     *
     * \param  None
     * \return The temperature reading
     */
    virtual float getTemperature( lnaTempSensor_T temperatureSensorToRead ) = 0;

    /*!
     *
     * \brief Pure virtual method to get the low threshold temperature value
     *
     * \param  None
     * \return The low threshold temperature
     */
    virtual float getLowThresholdTemp( lnaTempSensor_T temperatureSensorToSet ) = 0;

    /*!
     *
     * \brief Pure virtual method to get the high threshold temperature value
     *
     * \param  None
     * \return The high threshold temperature
     */
    virtual float getHighThresholdTemp( lnaTempSensor_T temperatureSensorToSet ) = 0;

    /*!
     *
     * \brief Pure virtual method to set the low threshold temperature value
     *
     * \param  None
     * \return The low threshold temperature
     */
    virtual ReturnType::State setLowThresholdTemp( float lowThresholdTemperature,
                                                   lnaTempSensor_T temperatureSensorToSet) = 0;

    /*!
     *
     * \brief Pure virtual method to set the high threshold temperature value
     *
     * \param  None
     * \return The high threshold temperature
     */
    virtual ReturnType::State setHighThresholdTemp( float highThresholdTemperature,
                                                    lnaTempSensor_T temperatureSensorToSet) = 0;

    /**
     * \brief   Get an instance of the LNA interface
     * \return  return a reference to the interface
     */
    static std::shared_ptr<ILna> getInterface();

protected:
    ILna() {};
};

} /* namespace Mplane */

#endif /* _VHI_ILNA_H_ */

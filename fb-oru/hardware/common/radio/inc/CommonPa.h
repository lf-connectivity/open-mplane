#ifndef _COMMONPA_H_
#define _COMMONPA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonPA.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IPa.h"
#include "Loggable.h"

namespace Mplane
{


class CommonPa: public IPa, public Loggable
{
public:

    /**
     *
     * @param index
     * @param number
     * @param name
     */
    CommonPa( int index, const char* name);

    /*!
     *
     * \brief Method to get the ID eeprom associated with the PA
     *
     * \param  None
     * \return The IdEeprom object if any, else NULL
     */
    virtual std::shared_ptr<IIdEeprom> getIdEeprom( void ) override;

    /**
     * Get the 0-based index
     */
    virtual int getIndex() const override ;

    /**
     * Get the name
     */
    virtual std::string getName() const override ;

    /*!
     *
     * \brief Pure virtual method to get the temperature value
     *
     * \param  Temperature sensor to read, each PA has two.
     * \return The temperature reading of the selected sensor.
     */
    virtual float getTemperature( paTempSensor_T temperatureSensorToRead ) override;

    /*!
     *
     * \brief Pure virtual method to get PA id
     *
     * \param  array to store the two ID values.
     * \return The integer value of the PA id that has been read.
     */
    virtual UINT16 getID( void ) override;

    /*!
     *
     * \brief Pure virtual method to retrieve if a PA is connected.
     *
     * \param  None
     * \return Is a PA connected true/false
     */
    virtual bool isConnected( void ) override;

    /*!
     *
     * \brief Virtual method to retrieve the number of sensors per PA.
     *
     * \param  None
     * \return Number of sensors per PA
     */
    virtual UINT16 numberTempSensorsPerPa( void ) override;

    /**
     * Method used to return the nominal design gain associated with the PA attached to
     * the TX path.
     * @return
     */
    virtual const Power getDesignGain() override;

    /**
     * Method used to return the possible operational band for the PA, ie the maximum
     * power - the minimum power, taking into account all thermal and aging effects.
     * @return
     */
    virtual const Power getMaxDesignGain() override;

    /*!
     *
     * \brief Pure virtual method to update the average temperature value
     *
     * \param  None
     * \return None
     */
    virtual void updateAvgTemp( void ) override;

    /**
     * Method used to enable a PA connected to the radio
     *
     * @param PA to enable
     * @return Return state of the operation
     */
    virtual const ReturnType::State setPaEnable( void ) override;

    /**
     * Method used to disable a PA connected to the radio
     *
     * @param PA to disable
     * @return Return state of the operation
     */
    virtual const ReturnType::State setPaDisable( void ) override;

    /**
     * Method used to query the enable/disable of a PA connected to the radio
     *
     * @param PA to query
     * @param Reference to the PA current state
     * @return Return state of the operation
     */
    virtual const ReturnType::State getPaState( paState_T &paState ) override;

    /**
     * Method used to return the status for the PA Gain Manual Control.
     *
     * @param UINT16 ctrlRawValue the raw value of the PA Gain Manual control register
     *
     * @return true if successful, false otherwise
     */
    virtual bool getPaGainManualCtrl(UINT16& ctrlRawValue) override;

    /**
     * Method used to set the status for the PA Gain Manual Control.
     *
     * @param UINT16 ctrlStatus the raw value of the PA Gain Manual Control register to set
     *
     * @return true if successful, false otherwise
     */
    virtual bool setPaGainManualCtrl(UINT16 ctrlStatus) override;

    /**
     * Method used to return the status for the PA Gain Override.
     *
     * @param UINT16 overrideRawValue the raw value of the PA Gain Override register
     *
     * @return true if successful, false otherwise
     */
    virtual bool getPaGainOverride(UINT16& overrideRawValue) override;

    /**
     * Method used to set the status for the PA Gain Override.
     *
     * @param UINT16 overrideStatus the raw value of the PA Gain Override register to set
     *
     * @return true if successful, false otherwise
     */
    virtual bool setPaGainOverride(UINT16 overrideStatus) override;

private:
     int mIndex;
     std::string mName;
};

}

#endif /* _COMMONPA_H_ */

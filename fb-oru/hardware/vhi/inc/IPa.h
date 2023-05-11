#ifndef _VHI_IPA_H_
#define _VHI_IPA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPa.h
 * \brief     A file to define generic interface to an IPa (Power Amplifier) Module
 *
 *
 * \details   A file to define generic interface to an IPa (Power Amplifier) Module
 *
 */

// Includes go here, before the namespace
#include <vector>
#include <memory>

#include "IIdEeprom.h"
#include "GlobalTypeDefs.h"
#include "Power.h"

namespace Mplane
{

/*! \brief  Generic IPa interface
 *
 *  A virtual interface base class defining an interface to a PA.
 *  The interface contains configuration and control aspects.
 */
class IPa
{
public:

	/*!
	 *
	 * \brief PA selector.
	 *
	 */
	typedef enum
	{
		PA_TEMP_1 = 1,
		PA_TEMP_2 = 2
	} paTempSensor_T;

	typedef enum
	{
		PA_ENABLED  = 1,
		PA_DISABLED = 2
	} paState_T;

    /*! \brief Destructor
     *
     */
    virtual ~IPa() { };

    /**
     * Get the 0-based index
     */
    virtual int getIndex() const =0 ;

    /**
     * Get the name
     */
    virtual std::string getName() const =0 ;

    /*!
     *
     * \brief Pure virtual method to get the ID eeprom associated with the PA
     *
     * \param  None
     * \return The IdEeprom object if any, else NULL
     */
    virtual std::shared_ptr<IIdEeprom> getIdEeprom( void ) = 0;

    /*!
     *
     * \brief Pure virtual method to get the temperature value
     *
     * \param  Temperature sensor to read, each PA has two.
     * \return The temperature reading of the selected sensor.
     */
    virtual float getTemperature( paTempSensor_T temperatureSensorToRead ) = 0;

    /*!
     *
     * \brief Pure virtual method to update the average temperature value
     *
     * \param  None
     * \return None
     */
    virtual void updateAvgTemp( void ) = 0;

    /*!
     *
     * \brief Pure virtual method to get PA idea
     *
     * \param  None
     * \return Integer of the id in two byte chunks 0x'id1''id0'
     */
    virtual UINT16 getID( void ) = 0;

    /*!
     *
     * \brief Pure virtual method to retrieve if a PA is connected.
     *
     * \param  None
     * \return Is a PA connected true/false
     */
    virtual bool isConnected( void ) = 0;

    /*!
     *
     * \brief Pure virtual method to retrieve the number of sensors per PA.
     *
     * \param  None
     * \return Number of sensors per PA
     */
    virtual UINT16 numberTempSensorsPerPa( void ) = 0;

    /**
     * Method used to return the nominal design gain associated with the PA attached to
     * the TX path.
     * @return
     */
    virtual const Power getDesignGain() = 0;

    /**
     * Method used to return the possible operational band for the PA, ie the maximum
     * power - the minimum power, taking into account all thermal and aging effects.
     * @return
     */
    virtual const Power getMaxDesignGain() = 0;

    /**
     * Method used to enable a PA connected to the radio
     *
     * @return Return state of the operation
     */
    virtual const ReturnType::State setPaEnable( void ) = 0;

    /**
     * Method used to disable a PA connected to the radio
     *
     * @return Return state of the operation
     */
    virtual const ReturnType::State setPaDisable( void ) = 0;

    /**
     * Method used to query the enable/disable of a PA connected to the radio
     *
     * @param Reference to the PA current state
     * @return Return state of the operation
     */
    virtual const ReturnType::State getPaState( paState_T &paState ) = 0;

    /**
     * Method used to return the status for the PA Gain Manual Control.
     *
     * @param UINT16 ctrlRawValue the raw value of the PA Gain Manual control register
     *
     * @return true if successful, false otherwise
     */
    virtual bool getPaGainManualCtrl(UINT16& ctrlRawValue) = 0;

    /**
     * Method used to set the status for the PA Gain Manual Control.
     *
     * @param UINT16 ctrlStatus the raw value of the PA Gain Manual Control register to set
     *
     * @return true if successful, false otherwise
     */
    virtual bool setPaGainManualCtrl(UINT16 ctrlStatus) = 0;

    /**
     * Method used to return the status for the PA Gain Override.
     *
     * @param UINT16 overrideRawValue the raw value of the PA Gain Override register
     *
     * @return true if successful, false otherwise
     */
    virtual bool getPaGainOverride(UINT16& overrideRawValue) = 0;

    /**
     * Method used to set the status for the PA Gain Override.
     *
     * @param UINT16 overrideStatus the raw value of the PA Gain Override register to set
     *
     * @return true if successful, false otherwise
     */
    virtual bool setPaGainOverride(UINT16 overrideStatus) = 0;

protected:
    IPa() {};
};

/**
 * The IPaFactory is a polymorphic Pa port interface factory that allows a
 * specific radio implementation to set the number of PA ports supported by
 * that particular hardware implementation, create the actual PA port, again
 * specific to the radio implementation and return them as a vector that is
 * stored in the common radio implementation.
 *
 * @note This factory must be implemented by each radio type where its physical
 * characteristics have nothing in common with any existing implementation.
 */
class IPaFactory
{
public:
    /**
     * This interface must be implemented by each radio implementation
     * type. The caller passes in a variable by reference that will be used to
     * return the number of ports created. The return value, is a vector of
     * pointers to the common IPa interface.
     *
     * Any radio specific implementation code that is aware of the actual PA port
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * \param maxPorts a reference to a variable that is used to return the number of PA's
     * \return a vector containing maxPorts PA interface pointers.
     */
    static std::vector< std::shared_ptr<IPa> > createPAs( int &maxPAs );

    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a previous created list of ports. The return value, is a vector of
     * pointers to the common PA interface.
     *
     * Any radio specific implementation code that is aware of the actual PA
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * \return a vector containing maxPorts PA interface pointers.
     */
    static std::vector< std::shared_ptr<IPa> > getPAs( );

    /**
     * Pure virtual interface method used return the number of PA ports that
     * are supported by this radio implementation.
     *
     * @return Number of supported PA ports.
     */
    static int getNumberOfPAs();
};

} /* namespace Mplane */

#endif /* _VHI_IPA_H_ */

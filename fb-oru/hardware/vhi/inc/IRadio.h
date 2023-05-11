/*
 * Radio.h
 *
 *  Created on: 26 Mar 2013
 *      Author: gdurban
 */

#ifndef _VRH_RADIO_H_
#define _VRH_RADIO_H_


/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRadio.h
 * \brief     A file to contain a generic interface to the radio hardware
 *
 *
 * \details   This file defines a generic interface to a radio implementation
 *
 */


#include <memory>
#include "GlobalTypeDefs.h"
#include <stdexcept>
#include "Observer.hpp"
#include "ICalModeChange.h"
#include "IRxAgc.h"
#include "IRxAgcModeChange.h"

namespace Mplane
{

/*
 * Forward class declarations
 */

class IRadioInfo;
class ITxPort;
class IRxPort;
class ISRxPort;
class IDevices;
class IModules;
class ICalData;
class ICarrierServer;
class IRxAgc;
class IAldPort;

/** @brief  Virtual Radio Hardware Interface
 *
 *  This class defines the root interface to the radio hardware.
 *  It exposes instances of many objects that map the functionality
 *  of the radio hardware physical devices, such as FPGAs, DACs ADCs, PLLs
 *  etc.  into collections of method call interfaces.
 *
 *  The purpose of the interface is to attempt expose the majority of the underlying
 *  radio hardware to the upper level radio control software through a collection
 *  of pure virtual abstract classes (interfaces) that are implemented at runtime
 *  by either common functionality or by a radio hardware specific implementation.
 *
 *  The Radio hardware interface is implemented as a singleton pattern, so
 *  that only one global reference to the radio can be established. Higher
 *  level control and application software must get an instance of the virtual radio
 *  in order to access the radio hardware.
 *
 *  @note - upper level control and application software must never access hardware directly
 *  in order to maintain the common implementation provided by the interface. If a specific radio
 *  needs to add functionality it must do so by extending the common interface and producing
 *  a radio specific implementation of that extended interface.
 *
 */
class IRadio: public ICalModeChange, public Subject<ICalModeChange>,
public IRxAgcModeChange, public Subject<IRxAgcModeChange, IRxAgc::RxAgcMode>
{
public:

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() = 0;

    /**
     * This method is called at the end of the radio initialise() method.
     * For the ART product the radio has two external devices associated with it, the 8 port LED
     * board fitted to the front panel, and the 10Mhz reference and trigger part mounted on the rear
     * panel. The ART radio implementation therefore creates and initialises these devices here,
     * immediately after the base board initialisation is complete.
     *
     * @return RT_OK if successful or some other RT_* value on failure.
     */
    virtual ReturnType::State systemDeviceInitialise() = 0;



    /**
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible. The primary purpose is to protect the
     * FEM stages.
     * @return true if successful
     */
    virtual bool shutdown(void) = 0;


    /** @brief  Get radio board information
     *
     *  Get access to the board information object that holds
     *  details of the physical radio hardware
     *
     *  @return a reference to the boards information
     */
    static std::shared_ptr<IRadioInfo> getInfo(void) ;


    /**
     * Pure virtual interface method used return the number of Tx ports that
     * are supported by this radio implementation.
     *
     * @return Number of supported radio transmit ports.
     */
    virtual int getNumberOfTxPorts() const = 0;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a Tx Port implementation. The index must be between zero and the number
     * returned by the getNumberOfTxPorts() method.
     * @param index zero based index from 0 to 'MAX Tx Ports - 1'
     * @return a reference to the Tx port for the given index.
     * @throws invalid_argument exception if the index is invalid
     */
    virtual ITxPort& getTxPort( int index ) =0 ; /* throw ( std::invalid_argument) */

    /**
     * Pure virtual interface method used return the number of Rx ports that
     * are supported by this radio implementation.
     *
     * @return Number of supported radio receive ports.
     */
    virtual int getNumberOfRxPorts() const = 0;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a Rx Port implementation. The index must be between zero and the number
     * returned by the getNumberOfRxPorts() method.
     * @param index zero based index from 0 to 'MAX Rx Ports - 1'
     * @return a reference to the Rx port for the given index.
     * @throws invalid_argument exception if the index is invalid
     */
    virtual IRxPort& getRxPort( int index ) =0 ; /* throw ( std::invalid_argument) */

    /**
     * Pure virtual interface method used to return the number of sampling receiver
     * ports that are supported by this radio implementation.
     *
     * @return Number of supported radio sampling receive ports.
     */
    virtual int getNumberOfSRxPorts() const = 0;

    /**
     * Pure virtual method is used to return a reference to a particular instance
     * of a sampling receive port implementation. The index must be between zero
     * and the number returned by the getNumberOfRxPorts() method.
     * @param index zero based index from 0 to 'MAX SRx Ports - 1'
     * @return a reference to the SRx port for the given index.
     * @throws invalid_argument exception if the index is invalid
     */
    virtual ISRxPort& getSRxPort( int index ) =0 ; /* throw ( std::invalid_argument) */

    /**
     * Pure virtual interface method used return the number of Ald ports that
     * are supported by this radio implementation.
     *
     * @return Number of supported radio transmit ports.
     */
    virtual int getNumberOfAldPorts() const = 0;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a Ald Port implementation. The index must be between zero and the number
     * returned by the getNumberOfAldPorts() method.
     * @param index zero based index from 0 to 'MAX Ald Ports - 1'
     * @return a reference to the Ald port for the given index.
     */
    virtual IAldPort& getAldPort( int index ) =0 ;

    /**
     * Method used to return a reference to the physical devices of the radio,
     * ie ADCs, DACs etc. The base implementation uses this method to
     * initialise the devices during radio bring up.
     * @return a reference to the radio devices for this implementation
     */
    virtual IDevices& getDevices() = 0;

    /**
     * Method used to return a reference to the physical modules of the radio,
     * ie Filters, FEMs etc. The base implementation uses this method to
     * initialise the modules during radio bring up.
     *
     * @return a reference to the radio modules for this implementation
     */
    virtual IModules& getModules() = 0;


    /**
     * This method is used to return a reference to the calibration data supported
     * by this radio instance. See ICalData for details.
     * @return a reference to the radios calibration data implementation
     */
    virtual ICalData& getCalData() = 0;

    /**
     * This method is called periodically by the higher level application
     * to update the temperature data associated with various parts of the radio.
     *
     * On return from the call, the implementation will have performed all the
     * necessary temperature measurements and updated the temperature data associated with
     * FPGAs, transmit and receive paths and the average radio temperature.
     *
     * Subsequent calls to methods suck as Mplane::ITxPort::getTemperature will return
     * the last temperature update.
     *
     * @return RT_OK if temperature data updated successfully.
     */
    virtual ReturnType::State updateTemperatureData() = 0;

    /**
     * This method is called periodically by the higher level application
     * to update the power supply data associated radio.
     *
     * On return from the call, the implementation will have performed all the
     * necessary voltage measurements and updated the power supply data.
     *
     *
     * @return RT_OK if temperature data updated successfully.
     */
    virtual ReturnType::State updatePowerSupplyData() = 0;

    /**
     * This method is called periodically by the higher level application
     * to update the system synth state of the radio.
     *
     * On return from the call, the implementation will have performed all the
     * necessary steps to read the system synth state.
     *
     * If a fault is found then a fault will be raise
     *
     * @return RT_OK if system synth is updated successfully.
     */
    virtual ReturnType::State updateSystemSynthState() = 0;


    /** @brief  Get radio carrier server
     *
     *  Get access to the carrier server that manages carriers on this radio
     *
     *  @return a shared pointer to the carrier server (pointer may be null if carrier server not set)
     */
    virtual std::shared_ptr<ICarrierServer> getCarrierServer(void) = 0 ;

    /*! \brief  Get the FPGA core Temperature
     *
     *  Method used to read the FPGA core temperature.
     *
     */
    virtual float getFpgaTemperature( void ) = 0;


    /**
     * Method used to enable and disable calibration mode of operation
     */
    virtual void setCalMode( bool mode ) = 0;

    /**
     * Method used to return the current calibration mode setting.
     * When enabled services that autonomously change any hardware settings are
     * disabled. When calibration mode is disabled the software returns to normal operation.
     * @return
     */
    virtual bool getCalMode() = 0;

    virtual ~IRadio(){};

    IRadio(){};

    /**
     * Method used to get the current radio power supply voltage.
     *
     * @return the supply voltage
     */
    virtual float getSupplyVoltage() = 0;

    /*! \brief Pure virtual method to get the agc mode
	 *
	 * \return The agc mode
	 */
	virtual IRxAgc::RxAgcMode getRxAttenMode( void ) = 0;

    /*! \brief Pure virtual method to set the agc mode
	 *
	 * \param The agc mode
	 * \return None
	 */
	virtual void setRxAttenMode( IRxAgc::RxAgcMode mode ) = 0;

};


class IRadioFactory
{
public:
    /** @brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of the base radio hardware
     *  access object. This must be implemented using the singleton pattern by the
     *  specific radio implementation.
     *
     *  Must be define in: hardware/<BOARD>/radio/src/<Board>RadioFactory.cpp
     *
     *  Test mock defined in: vrh/test/src/TestIRadio.cpp
     *
     *
     */
    static std::shared_ptr<IRadio> getInterface(void);

};

/**
 * This class provides a hook for applications to add/run post radio initialisation objects (for example the radio
 * test interface can be started up in an instance of this class) that are in the application space (appServices) rather
 * than in hardware.
 */
class IRadioPostInit
{
public:
    /** @brief  Get the singleton instance
     *
     *  Used to get a reference to the single instance of this class.
     *  This must be implemented using the singleton pattern by the
     *  specific radio implementation.
     *
     *  Must be define in: appServices/<BOARD>/RadioControl/src/<Board>RadioPostInit.cpp
     *
     *  Test mock defined in: vrh/test/src/TestIRadioPostInit.cpp
     *
     */
    static std::shared_ptr<IRadioPostInit> getInterface(void);

    /**
     * This method will be called by the IRadio once the initialisation has successfully completed. NOTE: The
     * method is NOT called if initialisation fails.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State operator()() = 0 ;

    IRadioPostInit() {}
    virtual ~IRadioPostInit() {}

};


} /* namespace Mplane */

#endif /* _VRH_RADIO_H_ */

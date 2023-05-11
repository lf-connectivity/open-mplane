/*
 * CommonRadio.h
 *
 *  Created on: 15 Jun 2013
 *      Author: gdurban
 */

#ifndef _RADIO_HARDWARE_COMMONRADIO_H_
#define _RADIO_HARDWARE_COMMONRADIO_H_

#include "IRadio.h"
#include "ITxPort.h"
#include "IRxPort.h"
#include "ISRxPort.h"
#include "IAldPort.h"
#include "IDevices.h"
#include "IModules.h"
#include "IRadioInfo.h"
#include "Initialise.h"
#include "MovingAvg.hpp"

#include <vector>
#include <stdexcept>

namespace Mplane
{

/**
 * The Mplane::CommonRadio base class implements the base functionality used by all radios.
 * It's interface is defined by the Mplane::IRadio interface. The radio initialisation
 * is implemented through inheritance of the Mplane::Initialise class.
 *
 * The CommonRadio class is implemented as a singleton, as defined by the IRadio interface.
 * When the constructor is called, it uses various factories to create the boards devices,
 * RX paths, Tx paths and modules.
 *
 * The common radio isn't aware of the actual implementation of these items, just that
 * that can be created and initialised.
 *
 * @note It is important that the AxeAxis::Devices are created before the creation of
 * other items, like the TX and RX paths, as they will be referenced by these higher level
 * objects.
 *
 */
class CommonRadio: public virtual IRadio, public Initialise
{
	friend class CommonRadioTestCase;

public:

	/**
	 * Construct a base common radio class, that  supports a common
	 * hardware configuration, by calling factories implemented by higher
	 * level board specific factories.
	 */
	CommonRadio();

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise();

    /**
     * This method is called at the end of the radio initialise() method.
     * For the ART product the radio has two external devices associated with it, the 8 port LED
     * board fitted to the front panel, and the 10Mhz reference and trigger part mounted on the rear
     * panel. The ART radio implementation therefore creates and initialises these devices here,
     * immediately after the base board initialisation is complete.
     *
     * @return RT_OK if successful or some other RT_* value on failure.
     */
    virtual ReturnType::State systemDeviceInitialise();


    /**
     * This method is called at the end of the common radio initialisation
     * process to allow for higher level radio implementations to provide
     * application specific initialisation of the radio hardware.
     *
     * As this is is a pure virtual method in the common radio it must be
     * implemented by the final implementation.
     */
    virtual ReturnType::State appSpecificInitialise() = 0;

    /*! \brief  The doInit method
     *
     *  Included due to inheritance from Initialise.
     *
     *  Method called by the _initialise() method in Initialise.
     *
     *  Called at radio start up to initialise the radio hardware to a known
     *  good state.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResultString - eg. to "RADIO INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit();

    /**
     * This method is called during a shutdown request to set the radio hardware to
     * a safe state as soon as possible. The primary purpose is to protect the
     * FEM stages.
     * @return true if successful
     */
    virtual bool shutdown(void);

    /** @brief  Get radio board information
     *
     *  Get access to the board information object that holds
     *  details of the physical radio hardware
     *
     *  @return a reference to the boards information
     */
    virtual IRadioInfo& getInfo(void) const;

    /**
     * Pure virtual interface method used return the number of Tx ports that
     * are supported by this radio implementation.
     *
     * @return Number of supported radio transmit ports.
     */
    virtual int getNumberOfTxPorts() const;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a Tx Port implementation. The index must between zero and the number
     * returned by the getNumberOfTxPorts() method.
     * @param index zero based index from 0 to 'MAX Tx Ports - 1'
     * @return a reference to the Tx port for the given index.
     * @throws invalid_argument exception if the index is invalid
     */
    virtual ITxPort& getTxPort( int index ) ; /* throw (std::invalid_argument) */

    /**
     * Pure virtual interface method used return the number of Rx ports that
     * are supported by this radio implementation.
     *
     * @return Number of supported radio receive ports.
     */
    virtual int getNumberOfRxPorts() const;

    /**
     * Pure virtual interface method used return the number of sampling receiver
     * ports that are supported by this radio implementation.
     *
     * @return Number of supported radio sample receive ports.
     */
    virtual int getNumberOfSRxPorts() const;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a Rx Port implementation. The index must between zero and the number
     * returned by the getNumberOfRxPorts() method.
     * @param index zero based index from 0 to 'MAX Rx Ports - 1'
     * @return a reference to the Rx port for the given index.
     * @throws invalid_argument exception if the index is invalid
     */
    virtual IRxPort& getRxPort( int index ) ; /* throw (std::invalid_argument) */

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a sampling receiver port implementation. The index must between zero and the number
     * returned by the getNumberOfSRxPorts() method.
     * @param index zero based index from 0 to 'MAX SRx Ports - 1'
     * @return a reference to the SRx port for the given index.
     * @throws invalid_argument exception if the index is invalid
     */
    virtual ISRxPort& getSRxPort( int index ) ; /* throw (std::invalid_argument) */

    /**
     * Pure virtual interface method used return the number of Ald ports that
     * are supported by this radio implementation.
     *
     * @return Number of supported radio transmit ports.
     */
    virtual int getNumberOfAldPorts() const;

    /**
     * Pure virtual method used to return a reference to a particular instance
     * of a Ald Port implementation. The index must be between zero and the number
     * returned by the getNumberOfAldPorts() method.
     * @param index zero based index from 0 to 'MAX Ald Ports - 1'
     * @return a reference to the Ald port for the given index.
     */
    virtual IAldPort& getAldPort( int index );

    /**
     * Method used to return a reference to the physical devices of the radio,
     * ie ADCs, DACs etc. The base implementation uses this method to
     * initialise the devices during radio bring up.
     * @return
     */
    virtual IDevices& getDevices();

    /**
     * Method used to return a reference to the physical modules of the radio,
     * ie Filters, FEMs etc. The base implementation uses this method to
     * initialise the modules during radio bring up.
     *
     * @return a reference to the radio modules for this implementation
     */
    virtual IModules& getModules();

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
     * @return RT_OK if power data updated successfully.
     */
    virtual ReturnType::State updateTemperatureData();

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
    virtual ReturnType::State updatePowerSupplyData();

    /** @brief  Get radio carrier server
     *
     *  Get access to the carrier server that manages carriers on this radio
     *
     *  @return a shared pointer to the carrier server (pointer may be null if carrier server not set)
     */
    virtual std::shared_ptr<ICarrierServer> getCarrierServer(void) ;

    /**
     * Method used to enable and disable calibration mode of operation
     */
    virtual void setCalMode( bool mode ) override;

    /**
     * Method used to return the current calibration mode setting.
     * When enabled services that autonomously change any hardware settings are
     * disabled. When calibration mode is disabled the software returns to normal operation.
     * @return
     */
    virtual bool getCalMode() override;


    /**
     * Method used to get the current radio power supply voltage.
     *
     * @return the supply voltage
     */
    virtual float getSupplyVoltage() override;

    /*! \brief Method to get the agc mode
	 *
	 * \return The agc mode
	 */
	virtual IRxAgc::RxAgcMode getRxAttenMode( void ) override;

    /*! \brief Method to set the agc mode
	 *
	 * \param The agc mode
	 * \return None
	 */
	virtual void setRxAttenMode( IRxAgc::RxAgcMode mode ) override;


    virtual ~CommonRadio();

protected:


    std::shared_ptr<IRadioInfo> mRadioInfo;
    int m_MaxTxPorts;
    int m_MaxRxPorts;
    int m_MaxSRxPorts;
    int m_MaxAldPorts;
    std::shared_ptr<IDevices> mDevices;                   //!> pointer to the boards devices
    std::vector< std::shared_ptr<ITxPort> > m_TxPorts;
    std::vector< std::shared_ptr<IRxPort> > m_RxPorts;
    std::vector< std::shared_ptr<ISRxPort> > m_SRxPorts;
    std::vector< std::shared_ptr<IAldPort> > m_AldPorts;
    std::shared_ptr<IModules> mModules;
    std::shared_ptr<ICarrierServer> mCarrierServer;

    MovingAvg<float> mSupplyVoltage;

    bool mCalMode;
    bool mPreviousCalMode;

    IRxAgc::RxAgcMode mRxAgcMode;
};


} /* namespace Mplane */

#endif /* RADIO_HARDWARE_COMMONRADIO_H_ */

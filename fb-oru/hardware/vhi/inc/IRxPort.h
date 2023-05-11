#ifndef _MPLANE_IRXPORT_H_
#define _MPLANE_IRXPORT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRxPort.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <memory>
#include <vector>

#include "IPort.h"
#include "IFrequencyChange.h"
#include "ITemperatureChange.h"
#include "IRxAgc.h"

#include "GlobalTypeDefs.h"
#include "Frequency.h"
#include "Power.h"

#include "Observer.hpp"

namespace Mplane
{

/**
 * The IRxPort interface provides access to all the functionality related
 * to the receive path of the radio.
 */
class IRxPort : public virtual IPort,
	public ITemperatureChange, public Subject<ITemperatureChange>,
	public IFrequencyChange, public Subject<IFrequencyChange>
{
public:

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() = 0;

    /*! \brief  Set the port NCO frequency
     *
     *  Used to set the NCO frequency
     *
     *  \param frequency  the frequency to set
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setFrequency(const Frequency& frequency) = 0;

    /*! \brief  Set the port synthesiser frequency (does no other calibrations)
     *
     *  Used to set the NCO frequency
     *
     *  \param frequency  the frequency to set
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setSynth(const Frequency& frequency) = 0;

    /*! \brief  Get the port NCO frequency
     *
     *  Used to read the set NCO frequency
     *
     *  \return the set frequency
     */
    virtual const Frequency getFrequency(void)  = 0;

    /**
     * \brief Get the temperature in Deg C associated with this port
     *
     * Used to read the temperature associated with the port.
     *
     * \return Temperature value in degrees Celcius
     */
    virtual const Temperature getTemperature() = 0;


    /*! \brief  Set the RxIF attenuator value
     *
     *  Used to set the RxIF attenuator value
     *
     *  \return RT_OK if successful, RT_ERROR if not
     */
    virtual ReturnType::State setIfAttenuation( Power attenuation ) = 0;

    /*! \brief  Set the Rx RF attenuator value
     *
     *  Used to set the Rx RF attenuator value
     *
     *  \return RT_OK if successful, RT_ERROR if not
     */
     virtual ReturnType::State setRfAttenuation( Power attenuation) = 0;


    /*! \brief  Get the RxIF attenuator value
     *
     *  Used to read the RxIF attenuator value
     *
     *  \return float dBm value between 0 and 31.5
     */
    virtual Power getIfAttenuation() = 0;

    /*! \brief  Get the RxRF attenuator value
     *
     *  Used to read the RxRF attenuator value
     *
     *  \return RT_OK if successful, RT_ERROR if not
     */
    virtual Power getRfAttenuation( ) = 0;

    /*! \brief  Get the wide band RSSI
     *
     *  Used to read the RSSI value
     *
     *  \return RT_OK if successful, RT_ERROR if not
     */
    virtual Power getRssi(void) = 0;

    /**
     * This method is used to scale the digital power,
     *
     * @param power the dBFS value for the output
     * @return RT_OK is power set successfully.
     */
    virtual ReturnType::State setDigitalPowerScaler( float power ) = 0;

    /**
     * Method returns the the last set power level in DbFS
     *
     * @return last set  power adjustment..
     */
    virtual const Power getDigitalPowerScaler() = 0;

    /*! \brief  Retrieves the RX RF path state
    *
    *  Used to get the RX RF path state
    *
    *  \return bool
    */
    virtual bool isRxOn(void) = 0;

    /*! \brief  Set the RX Rf path on
    *
    *  Used to set the Rx Rf path on
    *
    *  \return State
    */
    virtual ReturnType::State setRxOn(void) =0 ;

    /*! \brief  Set the RX RF path off
    *
    *  Used to set the RX RF path off
    *
    *  \return State
    */
    virtual ReturnType::State setRxOff(void) =0 ;

    /*! \brief  Get the cal corrected adjustment
    *
    *  Used to get the cal corrected adjustment
    *
    *  \return Power
    */
    virtual Power getAdjustment() =0;


    /**
     * @brief Return the external filter loss for this RX path
     *
     * Method returns the current external filter loss that is added to the
     * receive power measurements in the receive path
     *
     * @return the receive port filter loss - defaults to 0.0 dB
     */
    virtual Power getExtFilterLoss() = 0;

    /**
     * @brief Set the external filter loss for this RX path
     *
     * Method used to set the external filter/duplexer losses
     * for this receive port.
     *
     * @param filterLoss
     * @return state RT_OK is successful, some other RT_ return code if failed.
     */
    virtual ReturnType::State setExtFilterLoss(Power filterLoss ) = 0;

    /**
     * Method used to manually set the external path connected to
     * the receive port
     *
     * @param path 0 to N-1 supported external receive paths
     * @return RT_OK if index is valid else RT_OUT_OF_RANGE
     */
    virtual ReturnType::State setPath( int path )  = 0;

    /**
     * Return the currently selected external receive path.
     * @return 0 to N-1 path index values.
     */
    virtual int getPath() = 0;



    virtual ~IRxPort() {};
};

/**
 * The IRxPortFactory is a polymorphic Rx port interface factory that allows a
 * specific radio implementation to set the number of Rx ports supported by
 * that particular hardware implementation, create the actual Rx port, again
 * specific to the radio implementation and return them as a vector that is
 * stored in the common radio implementation.
 *
 * @note This factory must be implemented by each radio type where its physical
 * characteristics have nothing in common with any existing implementation.
 */
class IRxPortFactory
{
public:

    /**
     * This interface must be implemented by each radio implementation
     * type. The caller passes in a variable by reference that will be used to
     * return the number of ports created. The return value, is a vector of
     * pointers to the common IRxPort interface.
     *
     * Any radio specific implementation code that is aware of the actual Rx port
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * @param maxPorts a reference to a variable that is used to return the number of ports
     * @return a vector containing maxPorts Rx ports interface pointers.
     */
    static std::vector< std::shared_ptr<IRxPort> > createPorts( int &maxPorts );


    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a previous created list of ports. The return value, is a vector of
     * pointers to the common ITxPort interface.
     *
     * Any radio specific implementation code that is aware of the actual Tx port
     * implementation class can use a static cast to return the interface pointer
     * to its original top level type.
     *
     * \return a vector containing maxPorts Rx ports interface pointers.
     */
    static std::vector< std::shared_ptr<IRxPort> > getPorts( );
};

}


#endif /* _MPLANE_IRXPORT_H_ */

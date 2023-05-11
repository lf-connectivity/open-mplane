#ifndef _ISRXPORT_H_
#define _ISRXPORT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ISRxPort.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <memory>
#include <vector>
#include <complex>

#include "IPort.h"
#include "GlobalTypeDefs.h"
#include "Frequency.h"
#include "Power.h"

namespace Mplane
{

/**
 * The ISRxPort interface provides access to all the functionality related
 * to the sampling receive path of the radio.
 */
class ISRxPort : public virtual IPort
{
public:

	enum class Direction
	{
		SRX_DIR_FORWARD,
		SRX_DIR_REVERSE
	};

    /*! \brief  The initialise method
     *
     *  Method called during system startup to setup the devices associated
     *  with the sample receiver path.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise() = 0;

    /*! \brief  Set the port NCO frequency
     *
     *  Used to set the frequency of the sampling receiver path
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
     *  Used to read back the current sampling receiver path frequency
     *
     *  \return the set frequency
     */
    virtual const Frequency getFrequency(void)  = 0;

    /*! \brief  Set the sampling receiver attenuator value
     *
     *  Used to set the sampling receiver attenuation value
     *
     *  \return RT_OK if successful, RT_ERROR if not
     */
    virtual ReturnType::State setAttenuation( Power attenuation ) = 0;


    /*! \brief  Get the sampling receiver path attenuator value
     *
     *  Used to read the current sampling receiver path attenuation value
     *
     *  \return float dBm value between 0 and 31.5
     */
    virtual Power getAttenuation( void ) = 0;

    /*! \brief  Get the sampling receiver path attenuator value
     *
     *  Used to read the current sampling receiver path attenuation value
     *
     *  \param path 0 to N-1 supported sample paths
     *  \return float dBm value between 0 and 31.5
     */
    virtual ReturnType::State getPathAtten( int path, Power &attenuation ) = 0;

    /**
     * \brief Get the temperature in Deg C associated with this port
     *
     * Used to read the temperature associated with the port.
     *
     * \return Temperature value in degrees Celcius
     */
    virtual float getTemperature() = 0;


    /*! \brief  Get the wide band RSSI
     *
     *  Used to read the Raw ADC RMS value in dBfs.
     *
     *  \return srx input power in dBfs
     */
    virtual Power getRawAdcRms(void) = 0;

    /*! \brief  Get the wide band RSSI peak
     *
     *  Used to read the ADC Peak value in dBfs.
     *
     *  \return srx peak power in dBfs
     */
    virtual Power getRawAdcPeak(void) = 0;

    /*! \brief  Get the SRX DC measurement
     *
     *  Used to read the DC value in dBfs.
     *
     *  \return srx DC measurement in dBfs
     */
    virtual Power getDC(void) =0 ;

    /*! \brief  Get the SRX DC measurement
     *
     *  Used to read the DC value in dBfs.
     *
     *  \param dc Ref to complex value set by this method to the complex value used to calculate the DC dBfs
     *
     *  \return srx DC measurement in dBfs
     */
    virtual Power getDC(std::complex<double>& dc) =0 ;



    /**
     * \brief get calibrated power correction for the current temperature and attenuation
     *
     * Used to get the correction factor used in the sample receive path power conversion
     * from dBfs to dBm
     *
     * This method will use the current attenuation value and path frequency
     * to determine the correction factor.
     *
     * @NOTE this value is not usually required by the application as it is used
     * in the getPower() method, it is however useful when converting capture power
     * data in an exrternal application
     *
     * @param path 0 to N-1 selects the input path associated power measurement
     * @return power correction factor
     */
    virtual Power getCorrection( void ) = 0;

    /**
     * \brief get wide band sample receiver power dBm
     *
     * Used to get the actual corrected sample receive path power in dbBm for
     * the selected path.
     *
     * This method will use the attenuation value associated with the path
     * to convert to convert the dBfs value to dBm.
     *
     * @param path 0 to N-1 selects the input path associated power measurement
     * @return sample power in dBm
     */
    virtual Power getPower( void ) = 0;

    /**
     * Method used where the SRX path is used to measure forward power
     * @param path
     * @param rf return the measured RF power
     * @param digital return the measured digital power
     * @return RT_OK if measurement OK, of RT_NOT_SUPPORTED
     */
    virtual ReturnType::State getFwdPower( int path, Power &rf, Power &digital ) = 0;

    /**
     * Method used where the SRX path is used to measure reverse power
     * @param path
     * @param rf return the measured reverse RF power
     * @param digital return the measured digital power
     * @return RT_OK if measurement OK, of RT_NOT_SUPPORTED
     */
    virtual ReturnType::State getRevPower( int path, Power &rf, Power &digital ) = 0;

    /**
     * Method used to manually set the external feedback path connected to
     * the sample receive path
     *
     * @param path 0 to N-1 supported sample paths
     * @return RT_OK if index is valid else RT_OUT_OF_RANGE
     */
    virtual ReturnType::State setPath( int path )  = 0;


    /**
     * Method used to set the target power associated with a measurement path,
     * this can be used to optimise the path attenuation for the expected
     * power measurement.
     *
     * @param path 0 to N-1 supported sample paths
     * @param target target power measurement
     * @return RT_OK or RT_NOT_SUPPORTED.
     */
    virtual ReturnType::State setTargetPower( int path, Power target ) = 0;

    /**
     * Return the currently selected external sample path.
     * @return 0 to N-1 path index values.
     */
    virtual int getPath() = 0;

    /**
     * Method used to manually set the direction of the measurement
     *
     * @param direction - Forward/Reverse
     * @return RT_OK if direction is valid else RT_OUT_OF_RANGE
     */
    virtual ReturnType::State setDirection( Direction dir )  = 0;

    /**
     * Return the currently selected direction.
     * @return direction
     */
    virtual Direction getDirection() = 0;

    /**
     * Method used to find out if an rf power measurement is in progress
     * @return true if rf power measurement in progress
     */
    virtual bool getMeasurementInProgress() = 0;

    /**
     * Basic virtual descructor.
     */
    virtual ~ISRxPort() {};

};

/**
 * The ISRxPortFactory is a polymorphic SRx port interface factory that allows a
 * specific radio implementation to set the number of SRx ports supported by
 * that particular hardware implementation, create the actual SRx port, again
 * specific to the radio implementation and return them as a vector that is
 * stored in the common radio implementation.
 *
 * @note This factory must be implemented by each radio type where its physical
 * characteristics are different from the common implementation.
 */
class ISRxPortFactory
{
public:

    /**
     * This interface must be implemented by each radio implementation
     * type. The caller passes in a variable by reference that will be used to
     * return the number of ports created. The return value, is a vector of
     * pointers to the common ISRxPort interface.
     *
     * Any radio specific implementation code that is aware of the actual SRx port
     * implementation class can cast to the returned interface pointer
     * to its original top level type.
     *
     * @param maxPorts a reference to a variable that is used to return the number of ports
     * @return a vector containing maxPorts SRx ports interface pointers.
     */
    static std::vector< std::shared_ptr<ISRxPort> > createPorts( int &maxPorts );


    /**
     * This interface must be implemented by each radio implementation
     * type. Returns a previous created list of ports. The return value, is a vector of
     * pointers to the ISRxPort interface.
     *
     * Any radio specific implementation code that is aware of the actual Rx port
     * implementation class can cast the returned interface pointer
     * to its original top level type.
     *
     * \return a vector containing maxPorts SRx ports interface pointers.
     */
    static std::vector< std::shared_ptr<ISRxPort> > getPorts( );

    /**
     * This interface must be implemented by each radio implementation
     * type. Returns the number of Tx ports associated with the SRX port
     *
     *
     * \return the number of Tx ports associated with the Srx port.
     */
    static unsigned int getNumAssociatedTxPorts( );
};



}


#endif /* _ISRXPORT_H_ */

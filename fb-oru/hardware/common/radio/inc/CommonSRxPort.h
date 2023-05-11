#ifndef _COMMON_SRXPATH_H_
#define _COMMON_SRXPATH_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonSRxPath.h
 * \brief     Common sampling receiver path implementation
 *
 *
 * \details   Common sampling receiver path implementation
 *
 */

#include "IFpgaMgr.h"
#include "ISRxPort.h"
#include "IAttenuator.h"
#include "Task.h"
#include "CommonPort.h"
#include "MovingAvg.hpp"


namespace Mplane
{


class CommonSRxPort:  public ISRxPort, public CommonPort
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class CommonSRxPortTestCases; // gtest

public:
    /*! \brief  The initialise method
     *
     *  Method called during system startup to setup the devices associated
     *  with the sample receiver path.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise();

    /*! \brief  Set the port NCO frequency
     *
     *  Used to set the frequency of the sampling receiver path
     *
     *  \param frequency  the frequency to set
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setFrequency(const Frequency& frequency);

    /*! \brief  Set the port synthesiser frequency (does no other calibrations)
     *
     *  Used to set the NCO frequency
     *
     *  \param frequency  the frequency to set
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State setSynth(const Frequency& frequency) override ;

    /*! \brief  Get the port NCO frequency
     *
     *  Used to read back the current sampling receiver path frequency
     *
     *  \return the set frequency
     */
    virtual const Frequency getFrequency(void);

    /*! \brief  Set the sampling receiver attenuator value
     *
     *  Used to set the sampling receiver attenuation value
     *
     *  \return RT_OK if successful, RT_ERROR if not
     */
    virtual ReturnType::State setAttenuation( Power attenuation );


    /*! \brief  Get the sampling receiver path attenuator value
     *
     *  Used to read the current sampling receiver path attenuation value
     *
     *  \return float dBm value between 0 and 31.5
     */
    virtual Power getAttenuation();

    /*! \brief  Get the sampling receiver path attenuator value
     *
     *  Used to read the current sampling receiver path attenuation value
     *
     *  \param path 0 to N-1 supported sample paths
     *  \return float dBm value between 0 and 31.5
     */
    virtual ReturnType::State getPathAtten( int path, Power &attenuation );

    /**
     * \brief Get the temperature in Deg C associated with this port
     *
     * Used to read the temperature associated with the port.
     *
     * \return Temperature value in degrees Celcius
     */
    virtual float getTemperature();


    /*! \brief  Get the wide band RSSI
     *
     *  Used to read the Raw ADC RMS value in dBfs.
     *
     *  \return srx input power in dBfs
     */
    virtual Power getRawAdcRms(void);

    /*! \brief  Get the wide band RSSI peak
     *
     *  Used to read the ADC Peak value in dBfs.
     *
     *  \return srx peak power in dBfs
     */
    virtual Power getRawAdcPeak(void) override;

    /*! \brief  Get the SRX DC measurement
     *
     *  Used to read the DC value in dBfs.
     *
     *  \return srx DC measurement in dBfs
     */
    virtual Power getDC(void) override ;

    /*! \brief  Get the SRX DC measurement
     *
     *  Used to read the DC value in dBfs.
     *
     *  \param dc Ref to complex value set by this method to the complex value used to calculate the DC dBfs
     *
     *  \return srx DC measurement in dBfs
     */
    virtual Power getDC(std::complex<double>& dc) override ;

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
    virtual Power getCorrection( void);


    /**
     * \brief get wide band sample receiver power dBm
     *
     * Used to get the actual corrected sample receive path power in dbBm
     *
     * @return sample power in dBm
     */
    virtual Power getPower(void);

    /**
     * Method used where the SRX path is used to measure forward power
     * @param path
     * @param rf return the measured RF power
     * @param digital return the measured digital power
     * @return RT_OK if measurement OK, of RT_NOT_SUPPORTED
     */
    virtual ReturnType::State getFwdPower( int path, Power &rf, Power &digital );

    /**
     * Method used where the SRX path is used to measure reverse power
     * @param path
     * @param rf return the measured reverse RF power
     * @param digital return the measured digital power
     * @return RT_OK if measurement OK, of RT_NOT_SUPPORTED
     */
    virtual ReturnType::State getRevPower( int path, Power &rf, Power &digital );

    /**
     * Method used to set the external feedback path connected to the sample receive path
     * @param path 0 to N-1 supported sample paths
     * @return RT_OK if index is valid else RT_OUT_OF_RANGE
     */
    virtual ReturnType::State setPath( int path );

    /**
     * Method used to set the target power associated with a measurement path,
     * this can be used to optimise the path attenuation for the expected
     * power measurement.
     *
     * @param path 0 to N-1 supported sample paths
     * @param target target power measurement
     * @return RT_OK or RT_NOT_SUPPORTED.
     */
    virtual ReturnType::State setTargetPower( int path, Power target );


    /**
     * Return the currently selected external sample path.
     * @return 0 to N-1 path index values.
     */
    virtual int getPath();

    /**
     * Method used to find out if an rf power measurement is in progress
     * @return true if rf power measurement in progress
     */
    virtual bool getMeasurementInProgress();

    /**
     * Method used to manually set the direction of the measurement
     *
     * @param direction - Forward/Reverse
     * @return RT_OK if direction is valid else RT_OUT_OF_RANGE
     */
    virtual ReturnType::State setDirection( Direction dir ) ;

    /**
     * Return the currently selected direction.
     * @return direction
     */
    virtual Direction getDirection() ;

    /**
     * The radio updateTemperature method calls this method to update the
     * average temperature for this port.
     */
    virtual void updateAvgTemp();

    /**
     * Common sampling receiver port constructor, stores the port index
     * it port number and name through the base common port class.
     */
    CommonSRxPort( int index, char const* name);

    /**
     * Default constructor
     */
    virtual ~CommonSRxPort();

protected:

    /**
     * Performs the TSSI measurement returning the raw TSSI as the digital power and convertng this
     * into the rf power (without any correction)
     * @param forward
     * @param rf
     * @param digital
     * @return RT_OK if converts ok
     */
    ReturnType::State getTssi(bool forward, unsigned path, Power& rf, Power& digital) ;

    /**
     * Perform the RSSI measurement. Returns false if fails to measure
     */
    virtual bool measureRssi(const std::string& fnName) ;

protected:
    Mutex mMutex;

    /**
     * Used to store the currently selected
     */
    int mSamplePathIndex;

    /**
     * Used to store the currently selected direction
     */
    Direction mDir;

    /**
     * Used to access common FPGA functionality
     */
    std::shared_ptr<IFpgaSystemRegs> mSystemFpga;

    /**
     * Used to access system FPGA functionality
     */
    std::shared_ptr<IFpgaAntennaRegs> mAntennaFpga;

    /**
     * Attenuator associated with the sample receiver port.
     */
    std::shared_ptr<IAttenuator> mAtten;

    bool mTempUpdated;
    MovingAvg<float>  mTemperature;

    bool mMeasInProg;
};


}



#endif /* _COMMONRXPATH_H_ */

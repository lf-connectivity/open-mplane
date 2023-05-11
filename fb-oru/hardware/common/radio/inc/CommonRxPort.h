#ifndef _COMMONRXPATH_H_
#define _COMMONRXPATH_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonRxPath.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */
#include "Mutex.h"
#include "Temperature.h"

#include "IRadio.h"
#include "IRxAttenuators.h"
#include "IRxPort.h"
#include "MovingAvg.hpp"

#include "CommonPort.h"

namespace Mplane
{

class CommonRxPort:  public virtual IRxPort, public virtual IRxAttenuators, public CommonPort
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class CommonRxPortTestCase;  // cppunit
    friend class CommonRxPortTestCases; // gtest

public:

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise();

    /*! \brief  Set the port NCO frequency
     *
     *  Used to set the NCO frequency
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
     *  Used to read the set NCO frequency
     *
     *  \return the set frequency
     */
    virtual const Frequency getFrequency() ;

    /**
     * \brief Get the temperature in Deg C associated with this port
     *
     * Used to read the temperature associated with the port.
     *
     * \return Temperature value in degrees Celcius
     */
    virtual const Temperature getTemperature();


    CommonRxPort( int index, char const* name);

    virtual ~CommonRxPort();


    /*! \brief  Set the RxIF attenuator value
     *
     *  Used to set the RxIF attenuator value
     *
     *  \return RT_OK if successful, RT_ERROR if not
     */
     virtual ReturnType::State setIfAttenuation( Power attenuation);

     /*! \brief  Set the Rx RF attenuator value
      *
      *  Used to set the Rx RF attenuator value
      *
      *  \return RT_OK if successful, RT_ERROR if not
      */
      virtual ReturnType::State setRfAttenuation( Power setVal);



     /*! \brief  Get the RxIF attenuator value
     *
     *  Used to read the RxIF attenuator value
     *
     *  \return float dBm value between 0 and 31.5
     */
     virtual Power getIfAttenuation();

     /*! \brief  Get the RxRF attenuator value
     *
     *  Used to read the RxRF attenuator value
     *
     *  \return float dBm value between 0 and 31.5
     */
     virtual Power getRfAttenuation();

     /*! \brief  Get the RSSI value
     *
     *  Used to read the RSSI value
     *
     *  \return float dBm value
     */
     virtual Power getRssi(void);

     /**
      * This method is used to scale the digital power,
      *
      * @param power the dBFS value for the output
      * @return RT_OK is power set successfully.
      */
     virtual ReturnType::State setDigitalPowerScaler( float power ) override ;


     /**
      * Method returns the the last set power level in DbFS
      *
      * @return last set  power adjustment..
      */
     virtual const Power getDigitalPowerScaler() override ;

     /*! \brief  Set the RX Rf path on
     *
     *  Used to set the Rx Rf path on
     *
     *  \return State
     */
     virtual ReturnType::State setRxOn(void);

     /*! \brief  Set the RX RF path off
     *
     *  Used to set the RX RF path off
     *
     *  \return State
     */
     virtual ReturnType::State setRxOff(void);

     /*! \brief  Retrieves the RX RF path state
     *
     *  Used to get the RX RF path state
     *
     *  \return bool
     */
     virtual bool isRxOn(void);

     /*! \brief mutes or unmutes the data to the ADC
      *
      * This method controls the muting and unmuting of the data to the ADC.
      *
      * \param muteState  true = data to the ADC is muted, otherwise unmute
      */
     virtual void muteAdc(bool muteState);

     /*! \brief ADC muting current state
      *
      * ADC muting current state
      *
      * \return true if ADC is muted
      */
     virtual bool isAdcMuted();

     /**
      * The radio updateTemperature method calls this method to update the
      * average temperature for this port.
      */
     virtual void updateAvgTemp();


     // IRxAttenuators interface

     /*! \brief  Get the Rx IF attenuator
      *
      *  Used to access the Rx IF attenuator object
      *
      *  \return IF attenuator object
      */
     virtual std::shared_ptr<IAttenuator> getIfAttenuator() override ;

     /*! \brief  Get the Rx RF attenuator
      *
      *  Used to access the Rx RF attenuator object
      *
      *  \return IF attenuator object
      */
     virtual std::shared_ptr<IAttenuator> getRfAttenuator() override ;

     /*! \brief  Get the cal corrected adjustment
     *
     *  Used to get the cal corrected adjustment
     *
     *  \return Power
     */
     virtual Power getAdjustment() override;

     /**
      * @brief Return the external filter loss for this RX path
      *
      * Method returns the current external filter loss that is added to the
      * receive power measurements in the receive path
      *
      * @return the receive port filter loss - defaults to 0.0 dB
      */
     virtual Power getExtFilterLoss() override;

     /**
      * @brief Set the external filter loss for this RX path
      *
      * Method used to set the external filter/duplexer losses
      * for this receive port.
      *
      * @param filterLoss
      * @return state RT_OK is successful, some other RT_ return code if failed.
      */
     virtual ReturnType::State setExtFilterLoss(Power filterLoss ) override;

     /**
      * Method used to manually set the external path connected to
      * the receive port
      *
      * @param path 0 to N-1 supported external receive paths
      * @return RT_OK if index is valid else RT_OUT_OF_RANGE
      */
     virtual ReturnType::State setPath( int path )  override;

     /**
      * Return the currently selected external receive path.
      * @return 0 to N-1 path index values.
      */
     virtual int getPath() override;


protected:
     /*! \brief  Low-level method to turn the receiver on. Must be implemented by derived object
      *
      *  Method used to turn on the receiver for this port.
      *
      *  \return state of RT_OK if successful, RT_other if not.
      */
     virtual ReturnType::State setRxOnLowLevel(void)=0;

     /*! \brief  Low-level method to turn the receiver off. Must be implemented by derived object
      *
      *  Method used to turn off the receiver for this port.
      *
      *  \return state of RT_OK if successful, RT_other if not.
      */
     virtual ReturnType::State setRxOffLowLevel(void)=0;

protected:
     Mutex mMutex ;
     int mExternalPathIndex;
     bool mRxOnState;
     bool mAdcMuteState;

     bool mTempUpdated;
     MovingAvg<float>  mTemperature;
     Temperature       mCurrentTemperature;    //!> The temperature value associated with this port
     Temperature       mPreviousTemperature;   //!> The temperature value associated with this port
     Power             mDigitalPowerScaler;
     Power             mExtLoss;               //!> Optional external loss for the receive path

     std::shared_ptr<IRadio> mRadio;

};


}




#endif /* _COMMONRXPATH_H_ */

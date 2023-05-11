/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IPcl.h
 * \brief     Interface for PCL
 *
 *
 * \details   Defines the expected interface for power control loop (PCL)
 *
 */


#ifndef IPCL_H_
#define IPCL_H_

#include <memory>
#include "Observer.hpp"
#include "Power.h"
#include "Frequency.h"

namespace Mplane {

/*! @brief  Power Control Loop
 *
 * The purpose of the IPcl class is to provide a generic
 * interface to the power control loop in the application.
 *
 * The PCL implements the singleton pattern so that only one power control loop
 * can exist with the system, and any object in the application can register observers with
 * the singleton without knowing what actually implements it.
 *
 * An implementation of the IPcl needs to provide the getState() method so that the subject can get the current PCL state
 * and it also needs to call Subject notify() method on state changes.
 *
 */
class IPcl : public Subject<IPcl>
{
public:
	virtual ~IPcl() {}

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the PCL within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IPcl> getInstance(int index);

	/**
	 * PCL states
	 */
	enum PclStateType {
		PCL_STATE_MANUAL_ENABLED,
		PCL_STATE_MANUAL_DISABLED,
		PCL_STATE_AUTO_DISABLED,
		PCL_STATE_ACQUISITION1,
		PCL_STATE_ACQUISITION2,
		PCL_STATE_SEEK,
		PCL_STATE_TRACK,
		PCL_STATE_PA_ENABLE
	};

    /* Assign strings to the PclStateType ENUM above. Ensure that the
     * ordering is the same */

	std::vector<std::string> mStateNames =
        { "MANUAL/ENABLED",
          "MANUAL/DISABLED",
          "AUTO/DISABLED",
          "ACQUISITION1",
          "ACQUISITION2",
          "SEEK",
          "TRACK",
          "PA_ENABLE"};

	/* PCL mode types*/
	enum PclModeType {
	    PCL_MODE_MANUAL,
	    PCL_MODE_AUTO
	};

	/* PCL Enable types */
	enum PclEnableType {
	    PCL_ENABLE_OFF,
	    PCL_ENABLE_ON
	};

    /* Power detector ADC range */
    enum PclDetAdcRange {
        PCL_DET_ADC_2_5V = 0x0,
        PCL_DET_ADC_5_0V = 0x1
    };

	/* PCL service update rate - may become configurable at some point */
	static const unsigned PCL_SERVICE_UPDATE_RATE = 50;



     /**
      * Returns the current PCL state
      * @return PCL state
      */
     virtual PclStateType getState() const =0 ;

     /**
      * Method that is called periodically, to run the PCL
      */
     virtual void servicePcl() = 0;

     /**
      * This method is to show the PCL status.
      */
     virtual void showPcl() = 0;

//     /**
//      * This method is the entry point to the PCL controlling application.
//      */
//     virtual void startPcl() = 0;
//
//
//     /**
//      * This method will reset the PCL
//      */
//     virtual void resetPcl() = 0;

     virtual void setMode(IPcl::PclModeType newMode) = 0;
     virtual IPcl::PclModeType getMode(void) = 0;

     virtual void setEnable(IPcl::PclEnableType enable) = 0;
     virtual IPcl::PclEnableType getEnable(void) = 0;

     virtual ReturnType::State setTargetPower(Power power) = 0;
     virtual Power getTargetPower(void) = 0;

     /* Get the current tick value */
     virtual unsigned getTicks(void) = 0;

     /* Get the index into the TxPort to which this instance of PCL is attached */
     virtual int getIndex() const = 0;

     /* Set the frequency of the Tx Port to which the this instance of PCL is attached. */
     virtual ReturnType::State setFrequency(Frequency frequency) = 0;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMaxPower */

     virtual Power getParameterMaxPower(void) const = 0 ;
     virtual void setParameterMaxPower(Power maxPower) = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mDetCoeff */

     virtual float getParameterDetCoeff(void) const = 0 ;
     virtual void setParameterDetCoeff(float detCoeff) = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMinPower */

     virtual Power getParameterMinPower(void) const  = 0 ;
     virtual void setParameterMinPower(Power minPower)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPaPeakGain */

     virtual float getParameterPaPeakGain(void) const  = 0 ;
     virtual void setParameterPaPeakGain(float paPeakGain)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTestPower */

     virtual Power getParameterTestPower(void) const  = 0 ;
     virtual void setParameterTestPower(Power testPower)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTestPowerTol */

     virtual float getParameterTestPowerTol(void) const  = 0 ;
     virtual void setParameterTestPowerTol(float testPowerTol)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mRetLossMin */

     virtual float getParameterRetLossMin(void) const  = 0 ;
     virtual void setParameterRetLossMin(float retLossMin)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mIsoPortCheckPower */

     virtual Power getParameterIsoPortCheckPower(void) const  = 0 ;
     virtual void setParameterIsoPortCheckPower(Power isoPortCheckPower)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mIsoPortMaxPower */

     virtual Power getParameterIsoPortMaxPower(void) const  = 0 ;
     virtual void setParameterIsoPortMaxPower(Power isoPortMaxPower)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPclCwPower */

     virtual float getParameterPclCwPower(void) const  = 0 ;
     virtual void setParameterPclCwPower(float pclCwPower)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mRfDsaAcqAttn */

     virtual float getParameterRfDsaAcqAttn(void) const  = 0 ;
     virtual void setParameterRfDsaAcqAttn(float rfDsaAcqAttn)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mOlRefLookupLevel */

     virtual Power getParameterOlRefLookupLevel(void) const  = 0 ;
     virtual void setParameterOlRefLookupLevel(Power olRefLookupLevel)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq1SettlingTime */

     virtual unsigned getParameterAcq1SettlingTime(void) const  = 0 ;
     virtual void setParameterAcq1SettlingTime(unsigned acq1SettlingTime)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq1PowerTol */

     virtual Power getParameterAcq1PowerTol(void) const  = 0 ;
     virtual void setParameterAcq1PowerTol(Power acq1PowerTol)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq1PowerMargin */

     virtual float getParameterAcq1PowerMargin(void) const  = 0 ;
     virtual void setParameterAcq1PowerMargin(float acq1PowerMargin)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq2SettlingTime */

     virtual unsigned getParameterAcq2SettlingTime(void) const  = 0 ;
     virtual void setParameterAcq2SettlingTime(unsigned acq2SettlingTime)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq2PowerTol */

     virtual Power getParameterAcq2PowerTol(void) const  = 0 ;
     virtual void setParameterAcq2PowerTol(Power acq2PowerTol)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mSeekUpdateInterval */

     virtual unsigned getParameterSeekUpdateInterval(void) const  = 0 ;
     virtual void setParameterSeekUpdateInterval(unsigned seekUpdateInterval)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMuSeek */

     virtual float getParameterMuSeek(void) const  = 0 ;
     virtual void setParameterMuSeek(float muSeek)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTrackUpdateInterval */

     virtual unsigned getParameterTrackUpdateInterval(void) const  = 0 ;
     virtual void setParameterTrackUpdateInterval(unsigned trackUpdateInterval)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMuTrack */

     virtual float getParameterMuTrack(void) const  = 0 ;
     virtual void setParameterMuTrack(float muTrack)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPanicPowerTol */

     virtual float getParameterPanicPowerTol(void) const  = 0 ;
     virtual void setParameterPanicPowerTol(float panicPowerTol)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTrackInPowerTol */

     virtual float getParameterTrackInPowerTol(void) const  = 0 ;
     virtual void setParameterTrackInPowerTol(float trackInPowerTol)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTrackOutPowerTol */

     virtual float getParameterTrackOutPowerTol(void) const  = 0 ;
     virtual void setParameterTrackOutPowerTol(float trackOutPowerTol)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mParameterNumAvg */

     virtual unsigned getParameterNumAvg(void) const  = 0 ;
     virtual void setParameterNumAvg(unsigned numAvg)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mDetMaxPos */

     virtual unsigned getParameterDetMaxPos(void) const  = 0 ;
     virtual void setParameterDetMaxPos(unsigned detMaxPos)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMaxFreqChange */

     virtual Frequency getParameterMaxFreqChange(void) const  = 0 ;
     virtual void setParameterMaxFreqChange(Frequency maxFreqChange)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mDetCalOffset */

     virtual unsigned getParameterDetCalOffset(void) const  = 0 ;
     virtual void setParameterDetCalOffset(unsigned detCalOffset)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mDetCalPower */

     virtual Power getParameterDetCalPower(void) const  = 0 ;
     virtual void setParameterDetCalPower(Power detCalPower)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPowerDetAdcRange */

     virtual PclDetAdcRange getParameterDetAdcRange(void) const  = 0 ;
     virtual void setParameterDetAdcRange(PclDetAdcRange detAdcRange)  = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPaEnableTime */

     virtual unsigned getParameterPaEnableTime(void) const = 0 ;
     virtual void setParameterPaEnableTime(unsigned paEnableTime) = 0 ;

     /* ---------------------------------------------------------------------*/

     /* Get Tx Failure status */

     virtual bool getTxFailureStatus(void) const  = 0 ;
} ;


/**
 * This class defines an observer interface that must be implemented by objects
 * that need to process PCL state changes.
 *
 * Any object implementing this interface must register themselves with the
 * IPcl using the registerObserver(IPclObserver &observer )
 * function in order to receive any notification.
 *
 */
class IPclObserver : public Observer<IPcl>
{
public:
    virtual ~IPclObserver() {}
};


}

#endif /* IPCL_H_ */

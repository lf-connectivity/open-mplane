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


#ifndef _VRS_TESTIPCL_H_
#define _VRS_TESTIPCL_H_

#include "IPcl.h"
#include <memory>
#include "Observer.hpp"


namespace Mplane {

/*! \brief  Stub of the IPcl Interface
 *
 * This class provides an implementation of the IPcl interface, for use
 * by unit tests.
 * Users/coders of the unit tests that use an IPcl interface must ensure
 * that they code the TestIPcl implementation that meets their unit test
 * cases.
 */

class TestIPcl : public IPcl
{
public:
	virtual ~TestIPcl() {}

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the PCL within the system.
     *
     *  @return the singleton instance
     */
     static std::shared_ptr<IPcl> getInstance(int index);


     /**
      * Returns the current PCL state
      * @return PCL state
      */
     virtual PclStateType getState() const ;

     /**
      * Method that is called periodically, to run the PCL
      */
     virtual void servicePcl();

     /**
      * This method is to show the PCL status.
      */
     virtual void showPcl();

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


     virtual void setMode(IPcl::PclModeType newMode) ;
     virtual IPcl::PclModeType getMode(void);

     virtual void setEnable(IPcl::PclEnableType enable);
     virtual IPcl::PclEnableType getEnable(void);

     virtual ReturnType::State setTargetPower(Power power);
     virtual Power getTargetPower(void);

     virtual unsigned getTicks(void);
     virtual int getIndex() const ;

     virtual ReturnType::State setFrequency(Frequency frequency);

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMaxPower */

     virtual Power getParameterMaxPower(void) const;
     virtual void setParameterMaxPower(Power maxPower);

     /* ---------------------------------------------------------------------*/

     /* Get/Set mDetCoeff */

     virtual float getParameterDetCoeff(void) const;
     virtual void setParameterDetCoeff(float detCoeff);

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMinPower */

     virtual Power getParameterMinPower(void) const ;
     virtual void setParameterMinPower(Power minPower) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPaPeakGain */

     virtual float getParameterPaPeakGain(void) const ;
     virtual void setParameterPaPeakGain(float paPeakGain) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTestPower */

     virtual Power getParameterTestPower(void) const ;
     virtual void setParameterTestPower(Power testPower) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTestPowerTol */

     virtual float getParameterTestPowerTol(void) const ;
     virtual void setParameterTestPowerTol(float testPowerTol) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mRetLossMin */

     virtual float getParameterRetLossMin(void) const ;
     virtual void setParameterRetLossMin(float retLossMin) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mIsoPortCheckPower */

     virtual Power getParameterIsoPortCheckPower(void) const ;
     virtual void setParameterIsoPortCheckPower(Power isoPortCheckPower) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mIsoPortMaxPower */

     virtual Power getParameterIsoPortMaxPower(void) const ;
     virtual void setParameterIsoPortMaxPower(Power isoPortMaxPower) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPclCwPower */

     virtual float getParameterPclCwPower(void) const ;
     virtual void setParameterPclCwPower(float pclCwPower) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mRfDsaAcqAttn */

     virtual float getParameterRfDsaAcqAttn(void) const ;
     virtual void setParameterRfDsaAcqAttn(float rfDsaAcqAttn) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mOlRefLookupLevel */

     virtual Power getParameterOlRefLookupLevel(void) const ;
     virtual void setParameterOlRefLookupLevel(Power olRefLookupLevel) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq1SettlingTime */

     virtual unsigned getParameterAcq1SettlingTime(void) const ;
     virtual void setParameterAcq1SettlingTime(unsigned acq1SettlingTime) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq1PowerTol */

     virtual Power getParameterAcq1PowerTol(void) const ;
     virtual void setParameterAcq1PowerTol(Power acq1PowerTol) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq1PowerMargin */

     virtual float getParameterAcq1PowerMargin(void) const ;
     virtual void setParameterAcq1PowerMargin(float acq1PowerMargin) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq2SettlingTime */

     virtual unsigned getParameterAcq2SettlingTime(void) const ;
     virtual void setParameterAcq2SettlingTime(unsigned acq2SettlingTime) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mAcq2PowerTol */

     virtual Power getParameterAcq2PowerTol(void) const ;
     virtual void setParameterAcq2PowerTol(Power acq2PowerTol) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mSeekUpdateInterval */

     virtual unsigned getParameterSeekUpdateInterval(void) const ;
     virtual void setParameterSeekUpdateInterval(unsigned seekUpdateInterval) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMuSeek */

     virtual float getParameterMuSeek(void) const ;
     virtual void setParameterMuSeek(float muSeek) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTrackUpdateInterval */

     virtual unsigned getParameterTrackUpdateInterval(void) const ;
     virtual void setParameterTrackUpdateInterval(unsigned trackUpdateInterval) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMuTrack */

     virtual float getParameterMuTrack(void) const ;
     virtual void setParameterMuTrack(float muTrack) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPanicPowerTol */

     virtual float getParameterPanicPowerTol(void) const ;
     virtual void setParameterPanicPowerTol(float panicPowerTol) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTrackInPowerTol */

     virtual float getParameterTrackInPowerTol(void) const ;
     virtual void setParameterTrackInPowerTol(float trackInPowerTol) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mTrackOutPowerTol */

     virtual float getParameterTrackOutPowerTol(void) const ;
     virtual void setParameterTrackOutPowerTol(float trackOutPowerTol) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mParameterNumAvg */

     virtual unsigned getParameterNumAvg(void) const ;
     virtual void setParameterNumAvg(unsigned numAvg) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mDetMaxPos */

     virtual unsigned getParameterDetMaxPos(void) const ;
     virtual void setParameterDetMaxPos(unsigned detMaxPos) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mMaxFreqChange */

     virtual Frequency getParameterMaxFreqChange(void) const ;
     virtual void setParameterMaxFreqChange(Frequency maxFreqChange) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mDetCalOffset */

     virtual unsigned getParameterDetCalOffset(void) const ;
     virtual void setParameterDetCalOffset(unsigned detCalOffset) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mDetCalPower */

     virtual Power getParameterDetCalPower(void) const ;
     virtual void setParameterDetCalPower(Power detCalPower) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPowerDetAdcRange */

     virtual PclDetAdcRange getParameterDetAdcRange(void) const ;
     virtual void setParameterDetAdcRange(PclDetAdcRange detAdcRange) ;

     /* ---------------------------------------------------------------------*/

     /* Get/Set mPaEnableTime */

     virtual unsigned getParameterPaEnableTime(void) const;
     virtual void setParameterPaEnableTime(unsigned paEnableTime);

     /* ---------------------------------------------------------------------*/

     /* Get/Set Tx Failure status */

     virtual bool getTxFailureStatus(void) const;
     virtual void setTxFailureStatus(bool txFailureStatus);

protected:

     IPcl::PclStateType mPclState;

     bool mPclTxFailure;


} ;




}

#endif /* _VRS_TESTIPCL_H_ */

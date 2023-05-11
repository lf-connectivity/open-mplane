/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestIPcl.h
 * \brief     Test Interface for PCL
 *
 *
 * \details   Defines the expected interface for power control loop (PCL)
 *
 */

#include "TestIPcl.h"
#include "Power.h"


using namespace Mplane;

/*! \brief  Stub of the IPcl Interface
 *
 * This class provides an implementation of the IPcl interface, for use
 * by unit tests.
 * Users/coders of the unit tests that use an IPcl interface must ensure
 * that they code the TestIPcl implementation that meets their unit test
 * cases.
 */


  /* Implement getState() as defined in IPcl */
  IPcl::PclStateType Mplane::TestIPcl::getState() const
  {
       return(mPclState);
  }


  void Mplane::TestIPcl::servicePcl(void)
  {
  }

  void Mplane::TestIPcl::showPcl(void)
  {
  }

  void Mplane::TestIPcl::setMode(IPcl::PclModeType newMode)
  {
  }



  IPcl::PclModeType Mplane::TestIPcl::getMode(void)
  {
      return(PCL_MODE_MANUAL);
  }


  void Mplane::TestIPcl::setEnable(IPcl::PclEnableType enable)
  {
  }

  IPcl::PclEnableType Mplane::TestIPcl::getEnable(void)
  {
      return(PCL_ENABLE_OFF);
  }

  ReturnType::State Mplane::TestIPcl::setTargetPower(Power power)
  {
      return ReturnType::RT_OK;
  }

  ReturnType::State Mplane::TestIPcl::setFrequency(Frequency frequency)
  {
	  return ReturnType::RT_OK;
  }

  unsigned Mplane::TestIPcl::getTicks(void)
  {
      return (0);
  }

  Power Mplane::TestIPcl::getTargetPower(void)
  {
      return(0);
  }

  int Mplane::TestIPcl::getIndex(void) const
  {
      return (0);
  }

  Power Mplane::TestIPcl::getParameterMaxPower(void) const
  {
      return (0.0f);
  }

  void Mplane::TestIPcl::setParameterMaxPower(Power maxPower)
  {
  }

  /* ---------------------------------------------------------------------*/

  Power Mplane::TestIPcl::getParameterMinPower(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterMinPower(Power minPower)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterPaPeakGain(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterPaPeakGain(float paPeakGain)
  {
  }

  /* ---------------------------------------------------------------------*/

  Power Mplane::TestIPcl::getParameterTestPower(void) const
  {

      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterTestPower(Power testPower)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterTestPowerTol(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterTestPowerTol(float testPowerTol)
  {
  }


  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterRetLossMin(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterRetLossMin(float retLossMin)
  {
  }

  /* ---------------------------------------------------------------------*/

  Power Mplane::TestIPcl::getParameterIsoPortCheckPower(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterIsoPortCheckPower(Power isoPortCheckPower)
  {
  }

  /* ---------------------------------------------------------------------*/

  Power Mplane::TestIPcl::getParameterIsoPortMaxPower(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterIsoPortMaxPower(Power isoPortMaxPower)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterPclCwPower(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterPclCwPower(float pclCwPower)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterRfDsaAcqAttn(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterRfDsaAcqAttn(float rfDsaAcqAttn)
  {
  }

  /* ---------------------------------------------------------------------*/


  Power Mplane::TestIPcl::getParameterOlRefLookupLevel(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterOlRefLookupLevel(Power olRefLookupLevel)
  {
  }

  /* ---------------------------------------------------------------------*/

  unsigned Mplane::TestIPcl::getParameterAcq1SettlingTime(void) const
  {
      return (0);
  }


  void Mplane::TestIPcl::setParameterAcq1SettlingTime(unsigned acq1SettlingTime)
  {
  }

  /* ---------------------------------------------------------------------*/

  Power Mplane::TestIPcl::getParameterAcq1PowerTol(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterAcq1PowerTol(Power acq1PowerTol)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterAcq1PowerMargin(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterAcq1PowerMargin(float acq1PowerMargin)
  {
  }

  /* ---------------------------------------------------------------------*/

  unsigned Mplane::TestIPcl::getParameterAcq2SettlingTime(void) const
  {
      return (0);
  }


  void Mplane::TestIPcl::setParameterAcq2SettlingTime(unsigned acq2SettlingTime)
  {
  }

  /* ---------------------------------------------------------------------*/

  Power Mplane::TestIPcl::getParameterAcq2PowerTol(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterAcq2PowerTol(Power acq2PowerTol)
  {
  }

  /* ---------------------------------------------------------------------*/

  unsigned Mplane::TestIPcl::getParameterSeekUpdateInterval(void) const
  {
      return (0);
  }


  void Mplane::TestIPcl::setParameterSeekUpdateInterval(unsigned seekUpdateInterval)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterMuSeek(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterMuSeek(float muSeek)
  {
  }

  /* ---------------------------------------------------------------------*/

  unsigned Mplane::TestIPcl::getParameterTrackUpdateInterval(void) const
  {
      return (0);
  }


  void Mplane::TestIPcl::setParameterTrackUpdateInterval(unsigned trackUpdateInterval)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterMuTrack(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterMuTrack(float muTrack)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterPanicPowerTol(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterPanicPowerTol(float panicPowerTol)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterTrackInPowerTol(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterTrackInPowerTol(float trackInPowerTol)
  {
  }

  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterTrackOutPowerTol(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterTrackOutPowerTol(float trackOutPowerTol)
  {
  }


  /* ---------------------------------------------------------------------*/

  unsigned Mplane::TestIPcl::getParameterNumAvg(void) const
  {
      return (0);
  }


  void Mplane::TestIPcl::setParameterNumAvg(unsigned numAvg)
  {
  }

  /* ---------------------------------------------------------------------*/

  unsigned Mplane::TestIPcl::getParameterDetMaxPos(void) const
  {
      return (0);
  }


  void Mplane::TestIPcl::setParameterDetMaxPos(unsigned detMaxPos)
  {
  }

  /* ---------------------------------------------------------------------*/

  Frequency Mplane::TestIPcl::getParameterMaxFreqChange(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterMaxFreqChange(Frequency maxFreqChange)
  {
  }


  /* ---------------------------------------------------------------------*/

  float Mplane::TestIPcl::getParameterDetCoeff(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterDetCoeff(float detCoeff)
  {
  }



  /* ---------------------------------------------------------------------*/

  unsigned Mplane::TestIPcl::getParameterDetCalOffset(void) const
  {
      return (0);
  }


  void Mplane::TestIPcl::setParameterDetCalOffset(unsigned detCalOffset)
  {
  }

  /* ---------------------------------------------------------------------*/

  Power Mplane::TestIPcl::getParameterDetCalPower(void) const
  {
      return (0.0f);
  }


  void Mplane::TestIPcl::setParameterDetCalPower(Power detCalPower)
  {
  }

  /* ---------------------------------------------------------------------*/

  /* Get/Set mPowerDetAdcRange */

  IPcl::PclDetAdcRange Mplane::TestIPcl::getParameterDetAdcRange(void) const
  {
      return PclDetAdcRange::PCL_DET_ADC_2_5V;
  }

  void Mplane::TestIPcl::setParameterDetAdcRange(PclDetAdcRange detAdcRange)
  {

  }

  /* ---------------------------------------------------------------------*/

  /* Get/Set mPaEnableTime */

  unsigned Mplane::TestIPcl::getParameterPaEnableTime(void) const
  {
      return (0);
  }
  void Mplane::TestIPcl::setParameterPaEnableTime(unsigned paEnableTime)
  {

  }

  /* ---------------------------------------------------------------------*/

  bool Mplane::TestIPcl::getTxFailureStatus(void) const
  {
      return mPclTxFailure;
  }


  void Mplane::TestIPcl::setTxFailureStatus(bool txFailureStatus)
  {
      mPclTxFailure = txFailureStatus;
  }

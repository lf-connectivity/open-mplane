/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcCal.h
 * \brief     Implements the QMC spot calibration
 *
 *
 * \details
 *
 */


#ifndef QMCCAL_H_
#define QMCCAL_H_

#include <string>
#include <complex>

#include "ITxPort.h"
#include "ISRxPort.h"
#include "Frequency.h"
#include "Loggable.h"
#include "Mutex.h"

#include "IQmcCal.h"

namespace Mplane {

class QmcCal : public virtual IQmcCal, public Loggable {
public:
	explicit QmcCal(unsigned index) ;
	virtual ~QmcCal() ;

	/**
	 * Get the 0-based TX port index
	 */
	virtual unsigned getIndex() const override ;

	/**
	 * Perform the calibration
	 * @return true on success
	 */
	virtual bool performCal() override ;

	/**
	 * Get the error string (if any)
	 * @return error string on error; empty string if no error
	 */
	virtual std::string error() override ;

	/**
	 * Get the carrier suppression figure from the last calibration
	 * @return
	 */
	virtual Power getCarrierSuppression() const override ;

	/**
	 * Get the image suppression figure from the last calibration
	 * @return
	 */
	virtual Power getImageSuppression() const override ;

	/**
	 * Either set the attenuators to minimum or leave at current setting during QMC
	 */
	virtual bool setAttenuatorMode(IQmcCal::AttenMode attenMode) override ;


private:
	// reset all variables ready for a new calibration
	void restart() ;
	void measureNoiseFloor() ;

	// Run the cal loops
	bool doCal() ;

	// Inner loops
	bool calImageSuppression() ;
	bool calCarrierSuppression() ;

	// final check on the results
	bool checkResults() ;

	// set error string
	void setError(const std::string& error) ;

	// Set the DAC settings with limits checking
	bool setDacDC(int i, int q) ;
	bool setDacMag(int i, int q) ;
	bool setDacPhase(int phase) ;
	bool checkLimits(int val, int min, int max) ;

	// Debug - show the DAC settings
	void showDacSettings() ;

private:
	unsigned mIndex ;
	std::string mError ;
	std::shared_ptr<ITxPort> mTxPort ;
	std::shared_ptr<ISRxPort> mSrxPort ;
	mutable Mutex mMutex ;

	IQmcCal::AttenMode mAttenMode ;

	// == algorithm parameters

	Frequency mTxFreq ;

	// The starting point can either be 0, or the static calibration values read from the cal file for faster convergence for the freq we are on
	//If reading from the cal file, note that any number of phase larger that 511 gets added to Q so intLastPhase = calPhaseI + calPhaseQ
	//TODO: read these from the cal file for the current Frequency
	int mLastDCI ;
	int mLastDCQ ;
	int mLastPhase ;
	int mLastMag ;

	// Target ADCRMS for the main tone. This needs to be set to ensure we achieve good dynamic range to see the component we wish to null
	double mTartgetSRxADC ;

	// Image and carrier suppression targets
	double mTargetIS ;
	double mTargetCS ;

	// Image and carrier suppression final limits
	double mMinFinalIS ;
	double mMinFinalCS ;

	// Known Adjuster Values
	int mMAGKnownAdjuster ;
	int mDCKnownAdjusterAddition ;
	double mDCKnownAdjusterMultiplier ;

	// Shift Per LSB Values - These numbers are derived from measurements as it changes with frequency and temperature and power etc.
	//They can vary on a hardware basis, so may need to have these stored in a base class that can be overridden on a per product basis
	double mDCIShiftPerMagLSB ;
	double mDCQShiftPerPhaseLSB ;

	// Setup the radio to be in CW mode with a DAC induced NCO tone for our QMC measurement
	double mStartSRX ;

	double mSRxRMS ;
	double mSRxDC;
	double mSRxDSA;
	double mSRxDCLevelReference ;

	// Results
	double mCarrierPower ;
	double mImagePower ;

	int mPhase ;
	int mMag ;
	int mDCI ;
	int mDCQ ;

	std::complex<double> mIQref;
	std::complex<double> mIQrot;

	bool mSetPhaseMags ;
	bool mSetDCs ;

	double mSRxDSAErrorToTarget ;
	double mPwrDiff ;

	std::complex<double> mIQCarrierNoise ;

} ;

}

#endif /* QMCCAL_H_ */

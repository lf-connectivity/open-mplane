/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      QmcCal.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Maths.h"
#include "Task.h"

#include "IRadio.h"
#include "IDevices.h"
#include "ISynth.h"
#include "Frequency.h"
#include "stringfunc.hpp"

#include "IFpgaMgr.h"
#include "QmcState.h"
#include "QmcDacState.h"
#include "QmcCal.h"

using namespace Mplane;

//=============================================================================================================
// MACROS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
#define roundtoint(fval)	static_cast<int>(fround(fval))

#define CHECK_RETURN(cmd)	if ( (cmd) != ReturnType::RT_OK ) return false

//=============================================================================================================
// CONST
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Limits for the calibration parameters
const int LIMIT_PHASE_MIN = -1024;
const int LIMIT_PHASE_MAX = 1022;

const int LIMIT_MAG_MIN = -64;
const int LIMIT_MAG_MAX = 64;

const int LIMIT_DC_MIN = -8192;
const int LIMIT_DC_MAX = 8192;

//Max number of times to try iterating the suppression
const unsigned MAX_LOOPS = 4;

//Max number of IS or CS passes
const unsigned MAX_INNER_LOOPS = 6;

const Frequency FREQ_OFFSET(4500.0, Frequency::KHz) ;

// Modes
const IQmcCal::AttenMode DEFAULT_ATTEN_MODE{IQmcCal::ATTEN_MIN} ;
const std::map<std::string, IQmcCal::AttenMode> ATTEN_MODES {
	{ "MIN", IQmcCal::ATTEN_MIN },
	{ "CURRENT", IQmcCal::ATTEN_CURRENT },
} ;

//=============================================================================================================
// PUBLIC STATIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
IQmcCal::AttenMode IQmcCal::strToAttenMode(const std::string& modestr)
{
	std::string str(toUpper(modestr)) ;
	auto entry(ATTEN_MODES.find(str)) ;
	if (entry == ATTEN_MODES.end())
		return DEFAULT_ATTEN_MODE ;

	return entry->second ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
QmcCal::QmcCal(unsigned index) :
	Loggable("QmcCal" + std::to_string(index), "QMC"),
	mIndex(index),
	mError(""),
	mTxPort(),
	mSrxPort(),
	mMutex(),
	mAttenMode(DEFAULT_ATTEN_MODE),
	mLastDCI(0),
	mLastDCQ(0),
	mLastPhase(0),
	mLastMag(0),
	mTartgetSRxADC(0.0f),
	mTargetIS(0.0),
	mTargetCS(0.0),
	mMinFinalIS(0.0),
	mMinFinalCS(0.0),
	mMAGKnownAdjuster(0),
	mDCKnownAdjusterAddition(0),
	mDCKnownAdjusterMultiplier(0.0),
	mDCIShiftPerMagLSB(0.0f),
	mDCQShiftPerPhaseLSB(0.0f),
	mStartSRX(0.0f),
	mSRxRMS(0.0f),
	mSRxDC(0.0f),
	mSRxDSA(0.0f),
	mSRxDCLevelReference(0.0f),
	mCarrierPower(0.0f),
	mImagePower(0.0f),
	mPhase(0),
	mMag(0),
	mDCI(0),
	mDCQ(0),
	mSetPhaseMags(false),
	mSetDCs(false),
    mSRxDSAErrorToTarget(0.0f),
    mPwrDiff(0.0f),
    mIQCarrierNoise(0.0, 0.0)
{
}

//-------------------------------------------------------------------------------------------------------------
QmcCal::~QmcCal()
{
}

//-------------------------------------------------------------------------------------------------------------
unsigned QmcCal::getIndex() const
{
	return mIndex ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcCal::performCal()
{
	// Hold off any other attempt to cal this port
	Mutex::Lock lock(mMutex) ;

	// Save the state of all the settings we're about to change
	QmcState savedState(mIndex) ;

	logDebugVerbose("QMC: Cal started on TX%u", mIndex) ;

	// reset all the vars
	restart() ;

	// Create RAII object to store the DAC settings (i.e. set to CAL file values)
	QmcDacState dacState(mIndex) ;

	// run the cal
	if (!doCal())
	{
		// ensure error message says something
		if (mError.empty())
			setError("Calibration error") ;

		return false ;
	}

#ifndef OFF_TARGET
	// check results
	if (!checkResults())
		return false ;
#endif

	// show last DAC settings
	showDacSettings() ;

	// calibration worked, so don't restore DAC start state
	dacState.noRestore() ;

	logDebugVerbose("QMC: Cal completed TX%u", mIndex) ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::string QmcCal::error()
{
	Mutex::Lock lock(mMutex) ;
	using std::swap ;
	std::string error("") ;
	swap(mError, error) ;
	return error ;
}

//-------------------------------------------------------------------------------------------------------------
Power QmcCal::getCarrierSuppression() const
{
	Mutex::Lock lock(mMutex) ;
	return Power(mCarrierPower) ;
}

//-------------------------------------------------------------------------------------------------------------
Power QmcCal::getImageSuppression() const
{
	Mutex::Lock lock(mMutex) ;
	return Power(mImagePower) ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcCal::setAttenuatorMode(IQmcCal::AttenMode attenMode)
{
	Mutex::Lock lock(mMutex) ;
	mAttenMode = attenMode ;
	return true ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void QmcCal::restart()
{
	std::vector<std::shared_ptr<ITxPort>> txPorts(ITxPortFactory::getPorts()) ;
	mTxPort = txPorts[mIndex] ;
    std::vector< std::shared_ptr<ISRxPort> > mSrxPorts(ISRxPortFactory::getPorts()) ;
	mSrxPort = mSrxPorts[0] ;

	// Ensure TX is enabled
	if (!mTxPort->isTxOn())
		mTxPort->setTxOn() ;

	// Get the current TX freq
	mTxFreq = mTxPort->getFrequency() ;
	logDebugVerbose("QMC: Tx frequency %llu KHz", mTxFreq.getUint(Frequency::KHz)) ;

	// Adjust to actual synth frequency
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());
    IDevices& devices( radio->getDevices() ) ;
    std::shared_ptr<ISynth> txSynth(devices.getTxSynth( mIndex ) ) ;
	FrequencyOffset adjust = txSynth->checkFrequency( mIndex, mTxFreq );
	mTxFreq = Frequency(mTxFreq.getDbl() - adjust.getDbl()) ;
	logDebugVerbose("QMC: Tx synth frequency %llu KHz", mTxFreq.getUint(Frequency::KHz)) ;


	// The starting point can either be 0, or the static calibration values read from the cal file for faster convergence for the freq we are on
	//If reading from the cal file, note that any number of phase larger that 511 gets added to Q so intLastPhase = calPhaseI + calPhaseQ

	// Set to the current values (which will be from the cal file)
	mTxPort->getDacDCOffset(mLastDCI, mLastDCQ) ;

	int phaseI, phaseQ ;
	mTxPort->getDacPhaseOffset(phaseI, phaseQ) ;
	mLastPhase = phaseI + phaseQ ;

	int magI, magQ ;
	mTxPort->getDacMagOffset(magI, magQ) ;
	mLastMag = magI - magQ ;

	// Target ADCRMS for the main tone. This needs to be set to ensure we achieve good dynamic range to see the component we wish to null
	mTartgetSRxADC = -6;

	// Image and carrier suppression targets
	mTargetIS = -65;
	mTargetCS = -75;

	// Final Image and carrier suppression limits
	mMinFinalIS = -55;
	mMinFinalCS = -60;

	// Known Adjuster Values
	mMAGKnownAdjuster = 10;
	mDCKnownAdjusterAddition = 200;
	mDCKnownAdjusterMultiplier = 1.2;

	// Shift Per LSB Values - These numbers are derived from measurements as it changes with frequency and temperature and power etc.
	//They can vary on a hardware basis, so may need to have these stored in a base class that can be overridden on a per product basis
	mDCIShiftPerMagLSB = 6.7;
	mDCQShiftPerPhaseLSB = 0.352;

	mStartSRX = 12.0;

	mSRxDCLevelReference = -999;

	mCarrierPower = -999;
	mImagePower = -999;

}

//-------------------------------------------------------------------------------------------------------------
void QmcCal::measureNoiseFloor()
{
//	// save current attenuator settings
//	std::shared_ptr<QmcAttenState> attenState( std::make_shared<QmcAttenState>(mIndex) ) ;
//
//	// set to maximum attenuation
//	attenState->maxAtten() ;

	// disable TX

	std::shared_ptr<IFpgaAntennaRegs> fpga( IFpgaMgr::getIFpgaAntennaRegs() ) ;

	// TODO Check if the master Tx needs to be disabled or only the specific Tx port?
#if 0
	fpga->write_paTxEnable(mIndex, 0) ;
#endif
	fpga->write_tx_enable(0);

	// Pause of 1 frame
	Task::msSleep(11);

	// Read the noise floor
	mSrxPort->getDC(mIQCarrierNoise) ;

	logDebugVerbose("QMC: Noise floor (%.2lf, %.2lf)", mIQCarrierNoise.real(), mIQCarrierNoise.imag()) ;

	// re-enable TX
#if 0
	fpga->write_paTxEnable(mIndex, 1) ;
#endif
	fpga->write_tx_enable(1);

	// Pause of 1 frame - to let TX re-settle
	Task::msSleep(11);

}


//-------------------------------------------------------------------------------------------------------------
bool QmcCal::doCal()
{
	// Setup the radio to be in CW mode with a DAC induced NCO tone for our QMC measurement
	CHECK_RETURN(mTxPort->setDacIfOffset(FREQ_OFFSET.getDbl(Frequency::MHz)));
	CHECK_RETURN(mTxPort->setMode(ITxPort::Mode::CW_TEST)) ;
	CHECK_RETURN(mTxPort->setCWPower(-13.0));
	CHECK_RETURN(mTxPort->setOpAttenPad(ITxPort::PAD_ON));
	CHECK_RETURN(mSrxPort->setPath(mIndex));
	CHECK_RETURN(mSrxPort->setAttenuation(mStartSRX));
	CHECK_RETURN(mSrxPort->setFrequency(mTxFreq + FREQ_OFFSET));
	CHECK_RETURN(mTxPort->setDigitalPowerScaler(0.0));

//	double diffMax = 3.0 ;
	double referenceMin = -60.0 ;
	if (mAttenMode == IQmcCal::ATTEN_MIN)
	{
		CHECK_RETURN(mTxPort->setIFAttenuation(0.0));
		CHECK_RETURN(mTxPort->setRFAttenuation(0.0));
//		diffMax = 2.0 ;
		referenceMin = -30.0 ;
	}

	// Initialise the values in the DAC - Mag/phase gets set as part of the first adjustment
	if (!setDacDC(mLastDCI, mLastDCQ))
	{
		setError("Failed to set DAC DC") ;
		return false ;
	}

	// Pause of 1 frame to ensure the RSSI measurement isn't one that has the DAC adjustment mid way through.
	Task::msSleep(11);


	// Get the RMS and DC values from the SRx receiver
	mSRxRMS = mSrxPort->getRawAdcRms().get();
	mSRxDC = mSrxPort->getDC().get();

#if 0
	// Conditionaly compiled OUT as Jason says algorithm is for high powers and this test craps out at the low powers we are specifically using
	//	|
	//	|
	//	V

	// Sanity Check with the SRX tuned to the same Freq as the TX - it should see same power - the issue is that at high frequency the CS is so poor (~-7dBc), that it breaks a 1dB limit...
	mPwrDiff = (mSRxDC - 3.02) - mSRxRMS;

	// TODO: This actually passes erronously if the FPGA doesn't support the feature
	if (::fabs(mPwrDiff) > diffMax)
	{
		char buff[512] ;
		snprintf(buff, sizeof(buff), "SRx DC Power measurement error: Ensure the FPGA supports this feature. SRx DC = %.2lf, SRx RMS = %.2lf", mSRxDC, mSRxRMS) ;
		setError(buff) ;
		return false ;
	}
#endif

	// Work out what the SRx DSA value should be to get the set point in the correct place
	mSRxDSAErrorToTarget = mSRxRMS - mTartgetSRxADC;
	mSRxDSA = mStartSRX + mSRxDSAErrorToTarget;

	// Round the DSA value to the closest 0.5dB
	mSRxDSA = double(roundtoint(mSRxDSA * 2)) / 2.0;

	// Limit the SRx DSA to Zero - this will give us maximum dynamic range, even in the case where the Tx signal is low.
	if (mSRxDSA < 0)
		mSRxDSA = 0;

	// Make sure that the DSA isn't at too high a value, as this limits our dynamic range
	if (mSRxDSA > 16.0)
	{
		char buff[512] ;
		snprintf(buff, sizeof(buff), "Tx output seems too high - risk of overdriving SRx. UnKnown error: SRx DSA = %.1lf, SRx DC = %.2lf, SRx RMS = %.2lf",
				mSRxDSA, mSRxDC, mSRxRMS) ;
		setError(buff) ;
		return false ;
	}

	// Set the SRx to the new atten value
	CHECK_RETURN(mSrxPort->setAttenuation(mSRxDSA));

	// Pause of 1 frame to ensure the RSSI measurement isn't one that has the previous adjustement mid way through.
	Task::msSleep(11);

	// Get the reference level for measurement
	mSRxDCLevelReference = mSrxPort->getDC().get();

	// Make sure the SRx input level isn't too low
	if (mSRxDCLevelReference < referenceMin)
	{
		char buff[512] ;
		snprintf(buff, sizeof(buff), "Reference power too low at %.2lf. SRx RF DSA value = %.1lf", mSRxDCLevelReference, mSRxDSA) ;
		setError(buff) ;
		return false ;
	}

	// Initialise the values to the values from the last loop
	mPhase = mLastPhase;
	mMag = mLastMag;
	mDCI = mLastDCI;
	mDCQ = mLastDCQ;

	// Number of loops to home in on the best cal point
	for (unsigned loop = 0; loop < MAX_LOOPS; ++loop)
	{
		logDebugVerbose("QMC: Outer loop iteration %u / %u", (loop+1), MAX_LOOPS) ;

		// Set the SRx to the image frequency
		CHECK_RETURN(mSrxPort->setFrequency(mTxFreq - FREQ_OFFSET));
		logDebugVerbose("QMC: SRx frequency %llu KHz", mSrxPort->getFrequency().getUint(Frequency::KHz)) ;

		// Execute an image suppression calibration
		mSetPhaseMags = true;

		// IS cal
		if (!calImageSuppression())
			return false ;

		// Send the best values to the DAC if we need to
		if (mSetPhaseMags)
		{
			// Set the current phase settings noting that it is split over I & Q if over 511
			if (!setDacPhase(mPhase))
			{
				setError("Failed to set DAC Phase") ;
				return false ;
			}

			// Now update the Mags
			if (!setDacMag(mMag, 0))
			{
				setError("Failed to set DAC Mag") ;
				return false ;
			}
		}

		// Execute the carrier supression calibration
		mSetDCs = true;

		// Set the SRx to the Carrier Leakage frequency
		CHECK_RETURN(mSrxPort->setFrequency(mTxFreq));
		logDebugVerbose("QMC: SRx frequency %llu KHz", mSrxPort->getFrequency().getUint(Frequency::KHz)) ;

		// CS cal
		if (!calCarrierSuppression())
			return false ;

		// Set DACs back following our known adjustement if it was required
		if (mSetDCs)
		{
			if (!setDacDC(mDCI, mDCQ))
			{
				setError("Failed to set DAC DC") ;
				return false ;
			}
		}
		logDebugVerbose("QMC: Outer loop %u end: Carrier %.2lfdBc, Image %.2lfdBc", (loop+1), mCarrierPower, mImagePower) ;

		// show latest DAC settings
		showDacSettings() ;

		// If we meet the breakout criteria, exit the loop
		if ((mCarrierPower < mTargetCS) && (mImagePower < mTargetIS))
			break;

	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcCal::calImageSuppression()
{
	for (unsigned innerLoop = 0; innerLoop < MAX_INNER_LOOPS; ++innerLoop)
	{
		logDebugVerbose("QMC: Image suppression iteration %u / %u", (innerLoop+1), MAX_INNER_LOOPS) ;

		// Set the Mag Offset
		if (!setDacMag(mMag, 0))
		{
			setError("Failed to set DAC Mag") ;
			return false ;
		}

		// Set the current phase settings noting that it is split over I & Q if over 511
		if (!setDacPhase(mPhase))
		{
			setError("Failed to set DAC Phase") ;
			return false ;
		}

		// Pause of 1 frame to ensure the RSSI measurement isn't one that has the DAC adjustement mid way through.
		Task::msSleep(11);

		// Measure the carrier suppression
		mImagePower = mSrxPort->getDC(mIQref).get() - mSRxDCLevelReference;

		// If we have reached the target, exit the loop and don't bother updating the registers
		if (mImagePower < mTargetIS)
		{
			mSetPhaseMags = false;
			break;
		}

		// Move the mag by a known trajectory and derive the correction vector
		if (!setDacMag(mMag + mMAGKnownAdjuster, 0))
		{
			setError("Failed to set DAC Mag") ;
			return false ;
		}

		// Pause of 1 frame to ensure the RSSI measurement isn't one that has the DAC adjustement mid way through.
		Task::msSleep(11);
		mSrxPort->getDC(mIQrot);

		std::complex<double> iqIdeal(mDCIShiftPerMagLSB * mMAGKnownAdjuster, 0);
		std::complex<double> iqMeas = ((mIQrot - mIQref) / iqIdeal);
		std::complex<double> iqCor = mIQref / iqMeas;
		int magAddition = roundtoint(-iqCor.real() / mDCIShiftPerMagLSB);
		int phaAddition = roundtoint(-iqCor.imag() / mDCQShiftPerPhaseLSB);

		// Reached optimal value so break out
		if ((phaAddition == 0) && (magAddition == 0))
			break;

		// Add the updates to the mag and phase
		if (innerLoop < MAX_INNER_LOOPS)
		{
			mMag += magAddition;
			mPhase += phaAddition;
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcCal::calCarrierSuppression()
{
	// Get noise floor
	measureNoiseFloor() ;

	// iterate
	for (unsigned innerLoop = 0; innerLoop < MAX_INNER_LOOPS; ++innerLoop)
	{
		logDebugVerbose("QMC: Carrier suppression iteration %u / %u", (innerLoop+1), MAX_INNER_LOOPS) ;

		// Set the new best guess of the compensation values
		if (!setDacDC(mDCI, mDCQ))
		{
			setError("Failed to set DAC DC") ;
			return false ;
		}

		// Pause of 1 frame to ensure the RSSI measurement isn't one that has the DAC adjustement mid way through.
		Task::msSleep(11);

		// Measure the carrier suppression
//		mCarrierPower = mSrxPort->getDC(mIQref).get() - mSRxDCLevelReference;
		mSrxPort->getDC(mIQref) ;
		mIQref -= mIQCarrierNoise ; // remove noise floor
		double noiseCorrectedPower = 10.0 * log10(
			(mIQref.real()*mIQref.real() + mIQref.imag()*mIQref.imag()) /
			(32768.0 * 32768.0)
		) ;
		mCarrierPower = noiseCorrectedPower	- mSRxDCLevelReference;

		// If we have reached the target, exit the loop and don't bother updating the registers
		if (mCarrierPower < mTargetCS)
		{
			mSetDCs = false;
			break;
		}

		// Move the DC by a known trajectory and derive the correction vector to compensate for synthesiser impairments
		int dcKnownAdjuster = roundtoint(mDCI * mDCKnownAdjusterMultiplier); //Add known multiplier
		//To avoid small deviations, make minimum adjustment by adding LSBs
		if (dcKnownAdjuster >= 0)
			dcKnownAdjuster += mDCKnownAdjusterAddition ;
		else
			dcKnownAdjuster -= mDCKnownAdjusterAddition;

		if (!setDacDC((mDCI + dcKnownAdjuster), mDCQ))
		{
			setError("Failed to set DAC DC") ;
			return false ;
		}

		// Pause of 1 frame to ensure the RSSI measurement isn't one that has the DAC adjustement mid way through.
		Task::msSleep(11);
		(void)mSrxPort->getDC(mIQrot);
		mIQrot -= mIQCarrierNoise ; // remove noise floor

		// Refine our compensation values
		std::complex<double> mIQAdj(dcKnownAdjuster, 0);
		std::complex<double> iqMeas = ((mIQrot - mIQref) / mIQAdj);
		std::complex<double> iqCor = mIQref / iqMeas;
		int dciAddition = roundtoint(-iqCor.real());
		int dcqAddition = roundtoint(-iqCor.imag());

		// Reached optimal value so break out
		if ((0 == dciAddition) && (0 == dcqAddition))
			break;

		// Add the compensation values on the DC values with some damping
		if (innerLoop < MAX_INNER_LOOPS)
		{
			mDCI += roundtoint(dciAddition * 0.8);
			mDCQ += roundtoint(dcqAddition * 0.8);
		}
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcCal::checkResults()
{
	bool ok(true) ;

	// Check if the image suppression is within limits
	if (mImagePower > mMinFinalIS)
	{
		char buff[512] ;
		snprintf(buff, sizeof(buff), "Quadrature calibration only achieved %.2lfdBc image suppression", mImagePower) ;
		setError(buff) ;
		ok = false ;
	}

	// Check if the carrier suppression is within limits
	if (mCarrierPower > mMinFinalCS)
	{
		char buff[512] ;
		snprintf(buff, sizeof(buff), "DC offset calibration only achieved %.2lfdBc carrier suppression", mCarrierPower) ;
		setError(buff) ;
		ok = false ;
	}

	return ok ;
}

//-------------------------------------------------------------------------------------------------------------
void QmcCal::setError(const std::string& error)
{
	if (!mError.empty())
		mError += "\n" ;
	mError += error ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcCal::setDacDC(int i, int q)
{
	if (!checkLimits(i, LIMIT_DC_MIN, LIMIT_DC_MAX))
	{
		logDebugNormal("QMC: DAC DC I outside limits: DC I %d, limits %d..%d", i, LIMIT_DC_MIN, LIMIT_DC_MAX) ;
		return false ;
	}
	if (!checkLimits(q, LIMIT_DC_MIN, LIMIT_DC_MAX))
	{
		logDebugNormal("QMC: DAC DC Q outside limits: DC Q %d, limits %d..%d", q, LIMIT_DC_MIN, LIMIT_DC_MAX) ;
		return false ;
	}
	CHECK_RETURN(mTxPort->setDacDCOffset(i, q));
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcCal::setDacMag(int i, int q)
{
	if (!checkLimits(i, LIMIT_MAG_MIN, LIMIT_MAG_MAX))
	{
		logDebugNormal("QMC: DAC Mag I outside limits: Mag I %d, limits %d..%d", i, LIMIT_MAG_MIN, LIMIT_MAG_MAX) ;
		return false ;
	}
	if (!checkLimits(q, LIMIT_MAG_MIN, LIMIT_MAG_MAX))
	{
		logDebugNormal("QMC: DAC Mag Q outside limits: Mag Q %d, limits %d..%d", q, LIMIT_MAG_MIN, LIMIT_MAG_MAX) ;
		return false ;
	}

	CHECK_RETURN(mTxPort->setDacMagOffset(i, q));
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcCal::setDacPhase(int phase)
{
	int phaseI = phase;
	int phaseQ = 0;
	if (phaseI > 511)
	{
		phaseI = 511;
		phaseQ = phase - phaseI;
	}
	else if (phaseI < -511)
	{
		phaseI = -511;
		phaseQ = phase + phaseI;
	}

	if (!checkLimits(phaseI, LIMIT_PHASE_MIN, LIMIT_PHASE_MAX))
	{
		logDebugNormal("QMC: DAC Phase I outside limits: phase I %d, limits %d..%d", phaseI, LIMIT_PHASE_MIN, LIMIT_PHASE_MAX) ;
		return false ;
	}
	if (!checkLimits(phaseQ, LIMIT_PHASE_MIN, LIMIT_PHASE_MAX))
	{
		logDebugNormal("QMC: DAC Phase Q outside limits: phase Q %d, limits %d..%d", phaseQ, LIMIT_PHASE_MIN, LIMIT_PHASE_MAX) ;
		return false ;
	}

	CHECK_RETURN(mTxPort->setDacPhaseOffset(phaseI, phaseQ));
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool QmcCal::checkLimits(int val, int min, int max)
{
	if (val < min)
		return false ;
	if (val > max)
		return false ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void QmcCal::showDacSettings()
{
	int magI, magQ ;
	mTxPort->getDacMagOffset(magI, magQ) ;
	int phaseI, phaseQ ;
	mTxPort->getDacPhaseOffset(phaseI, phaseQ) ;
	int dcI, dcQ ;
	mTxPort->getDacDCOffset(dcI, dcQ) ;
	logDebugNormal("QMC: DAC settings - DC (%d, %d) Mag (%d, %d) Phase (%d, %d)", dcI, dcQ, magI, magQ, phaseI, phaseQ) ;
}

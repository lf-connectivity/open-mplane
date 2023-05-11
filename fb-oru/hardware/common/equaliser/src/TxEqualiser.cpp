/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxEqualiser.cpp
 * \brief     A file to define the interface to the tx equaliser for 100MHz
 *
 *
 * \details   A file to define the interface to the tx equaliser for 100MHz
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <cmath>
#include <vector>
#include <map>

#include "Loggable.h"

#include "ICalData.h"
#include "ITxIfCalData.h"
#include "ITxIfCal.h"
#include "ITxCal.h"
#include "ITxCalData.h"
#include "ITxPort.h"
#include "IFrequencyConst.h"

#include "TxEqualiser.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//All the frequency constants are in KHz
const float TxEqualiser::TX_IF_MIN_FREQ(-50000.0);
const float TxEqualiser::TX_IF_MAX_FREQ(50000.0);
const float TxEqualiser::TX_RF_FREQ_STEP(10000.0);
const float TxEqualiser::TX_IF_FREQ_STEP(10000.0);
const float TxEqualiser::INTERPOLATION_MIN_FREQ(-122880.0);
const float TxEqualiser::INTERPOLATION_MAX_FREQ(122880.0);
const float TxEqualiser::INTERPOLATION_SECOND_FREQ(-92160.0);
const float TxEqualiser::INTERPOLATION_SECOND_LAST_FREQ(92160.0);
const float TxEqualiser::INTERPOLATION_STEP(240.0);
const unsigned int TxEqualiser::INTERPOLATION_SIZE(1024);

//=============================================================================================================
// TxEqualiser
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxEqualiser::TxEqualiser(int index, const char* name) :
	CommonTxEqualiser(index, name, TxEqualiser::INTERPOLATION_MIN_FREQ * Frequency::KHz,
			TxEqualiser::INTERPOLATION_MAX_FREQ * Frequency::KHz, TxEqualiser::INTERPOLATION_SIZE),
			mFpga( IFpgaMgr::getIFpgaAntennaRegs() ),
			mRfdsa(),
			mBaseband()
{
}

//-------------------------------------------------------------------------------------------------------------
TxEqualiser::~TxEqualiser()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State TxEqualiser::calculateEqualiser(void)
{
	ReturnType::State status = ReturnType::RT_OK;
	std::vector<EqPoint> freqGainTable1;
	std::vector<EqPoint> freqGainTable2;
	std::vector<float> window;
	std::complex<float> input[TxEqualiser::INTERPOLATION_SIZE] = {0};

	//If equaliser needs to be put into passthrough mode, then do not perform further calculations
	if (mPassThroughMode || mCalMode)
	{
		//Put the equaliser in pass through mode
		writeEqualiserCoeff(input, true);
		return status;
	}

	FrequencyOffset freq(0.0);
	Power gain(0.0);

	//Create frequency gain tables for IF, RF and combined frequency response
	std::vector<EqPoint> ifFreqResponse;
	std::vector<EqPoint> rfFreqResponse;

	//Extract frequency response from Tx IF cal file
	status = extractIfFreqResp(ifFreqResponse);
	if (status != ReturnType::RT_OK)
	{
		ILoggable::logEventInfo("Tx Equaliser - Entering passthrough mode as IF cal data cannot be loaded");
		//Put the equaliser in pass through mode
		writeEqualiserCoeff(input, true);
		return status;
	}

	//Interpolate the IF frequency response to get 1024 equally spaces points
	if (interpolateFreqResp(ifFreqResponse, freqGainTable1) == false)
	{
		ILoggable::logEventInfo("Tx Equaliser - Entering passthrough mode due to internal error");
		//Put the equaliser in pass through mode
		writeEqualiserCoeff(input, true);
		return ReturnType::RT_ERROR;
	}

	//Extract frequency response from Tx RF cal file
	status = extractRfFreqResp(rfFreqResponse);
	if (status != ReturnType::RT_OK)
	{
		ILoggable::logEventInfo("Tx Equaliser - Entering passthrough mode as RF cal data cannot be loaded");
		//Put the equaliser in pass through mode
		writeEqualiserCoeff(input, true);
		return status;
	}

	//Interpolate the RF frequency response to get 1024 equally spaces points
	if (interpolateFreqResp(rfFreqResponse, freqGainTable2) == false)
	{
		ILoggable::logEventInfo("Tx Equaliser - Entering passthrough mode due to internal error");
		//Put the equaliser in pass through mode
		writeEqualiserCoeff(input, true);
		return ReturnType::RT_ERROR;
	}

	//Combine the interpolated IF and RF frequency response
	combineFreqResp(freqGainTable1, freqGainTable2);

	//Multiply gain points with tukey window
	calculateTukeyWindow(window);

	for (unsigned int index = 0; index < freqGainTable1.size(); index++)
	{
		freqGainTable1[index].gain = freqGainTable1[index].gain * window[index];
	}

	//Convert gain points to time domain using IFFT
	performIfft(freqGainTable1, input);

	//Write coefficients to FPGA registers
	writeEqualiserCoeff(input, false);

	return status;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State TxEqualiser::extractIfFreqResp(std::vector<EqPoint> &freqGainTable)
{
	ReturnType::State status = ReturnType::RT_OK;

	FrequencyOffset freq(0.0);
	Power gain(0.0);
	Power rfCentreGain(0.0);
	EqPoint point;

	// Get TX IF cal
	std::shared_ptr<ITxIfCalDataContainer> calData(
			std::dynamic_pointer_cast<ITxIfCalDataContainer>(ICalDataFactory::getInterface())
		);
	if (!calData)
		return ReturnType::RT_NOT_FOUND;

	std::shared_ptr<ITxIfCalData> txIfCal(calData->getTxIfCal());
	if (!txIfCal)
		return ReturnType::RT_NOT_FOUND ;

	// skip if not loaded
	if (!txIfCal->isLoaded())
		return ReturnType::RT_NOT_INITIALISED ;

	// skip if no valid TX IF response
	std::shared_ptr<ITxIfResponse> ifResp(txIfCal->getTxIfResponse(getIndex() + 1)) ;
	if (!ifResp)
		return ReturnType::RT_NOT_FOUND ;

	Injection_t loInjection = ITxFrequencyConstFactory::getInterface()->getLOInjection();

	//Add the first point at -122.88MHz with a gain of 0 dBm
	freq.set(INTERPOLATION_MIN_FREQ, Frequency::KHz);
	gain.set(0.0, Power::dBm);
	point.freq = freq;
	point.gain = gain;
	freqGainTable.push_back(point);

	//Add a dummy point for frequency -92.16MHz
	point.freq.set(0.0);
	point.gain.set(0.0);
	freqGainTable.push_back(point);

	//Get the Tx IF gain corresponding to the centre frequency
	rfCentreGain = getIfCentreFreqGain();

	/* Get the Rx IF gain corresponding to frequencies -50 to +50 MHz in steps of 5MHz
	 */
	int loopLen = ((TxEqualiser::TX_IF_MAX_FREQ - TxEqualiser::TX_IF_MIN_FREQ)/TxEqualiser::TX_IF_FREQ_STEP) + 1;
	for (UINT16 index = 0; index < loopLen; index++)
	{
		//Set frequency offset from centre frequency
		freq.set(TxEqualiser::TX_IF_MIN_FREQ + (index * TxEqualiser::TX_IF_FREQ_STEP), Frequency::KHz);

		//Get the Tx IF gain value corresponding to the frequency offset from the centre frequency
		if( loInjection ==  Injection_t::HIGHSIDE )
		{
			ifResp->getGain((freq.get() * -1), gain);
		}
		else
		{
			ifResp->getGain(freq.get(), gain);
		}

		//Add the point in the table
		point.freq = freq;
		point.gain = rfCentreGain - gain;
		freqGainTable.push_back(point);
	}

	//Add a point at frequency -92.16 MHz that has the same gain value as -40MHz with the sign inverted
	point.freq.set(TxEqualiser::INTERPOLATION_SECOND_FREQ, Frequency::KHz);
	point.gain = freqGainTable[3].gain.get() * -1;
	freqGainTable[1] = point;

	//Add a point at frequency 92.16 MHz that has the same gain value as 40MHz with the sign inverted
	point.freq.set(TxEqualiser::INTERPOLATION_SECOND_LAST_FREQ, Frequency::KHz);
	point.gain = freqGainTable[loopLen].gain.get() * -1;
	freqGainTable.push_back(point);

	//Add the last point at 122.88MHz with a gain of 0 dBm
	freq.set(TxEqualiser::INTERPOLATION_MAX_FREQ, Frequency::KHz);
	gain.set(0.0, Power::dBm);
	point.freq = freq;
	point.gain = gain;
	freqGainTable.push_back(point);

	return status;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State TxEqualiser::extractRfFreqResp(std::vector<EqPoint> &freqGainTable)
{
	ReturnType::State status = ReturnType::RT_OK;

	FrequencyOffset freq(0.0);
	Power gain(0.0);
	Power rfCentreGain(0.0);
	EqPoint point;

	//Get Tx RF cal
	std::shared_ptr<ITxCalDataContainer> calRfData(
			std::dynamic_pointer_cast<ITxCalDataContainer>(ICalDataFactory::getInterface())
		);
	if (!calRfData)
		return ReturnType::RT_NOT_FOUND;

	std::shared_ptr<ITxCalData> txRfCal(calRfData->getTxCal());
	if (!txRfCal)
		return ReturnType::RT_NOT_FOUND ;

	// skip if not loaded
	if (!txRfCal->isLoaded())
		return ReturnType::RT_NOT_INITIALISED ;

	// skip if no valid TX RF response
	std::shared_ptr<ITxOpenLoop> rfResp(txRfCal->getTxOpenLoop(getIndex() + 1)) ;
	if (!rfResp)
		return ReturnType::RT_NOT_FOUND ;

	//TODO: The rfdsa, ifdsa values for the first power band for the centre frequency is used for extraction of cal data.
	rfResp->getData(mCurrentFrequency, mBaseband, mRfdsa);

	//Get the Tx RF gain corresponding to the centre frequency
	rfCentreGain = getRfCentreFreqGain();

	//Add the first point at -122.88MHz with a gain of 0 dBm
	freq.set(INTERPOLATION_MIN_FREQ, Frequency::KHz);
	gain.set(0.0, Power::dBm);
	point.freq = freq;
	point.gain = gain;
	freqGainTable.push_back(point);

	//Add a dummy point for frequency -92.16MHz
	point.freq.set(0.0);
	point.gain.set(0.0);
	freqGainTable.push_back(point);

	/* Get the Rx RF gain corresponding to frequencies in 100MHz bandwidth around the centre frequency in steps of 10MHz
	 */
	int loopLen = ((TxEqualiser::TX_IF_MAX_FREQ - TxEqualiser::TX_IF_MIN_FREQ)/TxEqualiser::TX_RF_FREQ_STEP) + 1;
	for (UINT16 index = 0; index < loopLen; index++)
	{
		Frequency txCalFreq;

		//Set the frequency from the 100MHz range
		txCalFreq.set(mCurrentFrequency.get(Frequency::KHz) + TxEqualiser::TX_IF_MIN_FREQ + (index * TxEqualiser::TX_RF_FREQ_STEP), Frequency::KHz);

		Power rfGain(0.0);

		rfResp->getPower(txCalFreq, mBaseband, mRfdsa, rfGain);

		//Set frequency offset from centre frequency
		freq.set(txCalFreq.getInt() - mCurrentFrequency.getInt());

		//Record the Rx RF gain value and normalise it
		gain = rfCentreGain - rfGain;

		//Add the point in the table
		point.freq = freq;
		point.gain = gain;
		freqGainTable.push_back(point);
	}

	//Add a point at frequency -92.16 MHz that has the same gain value as -40MHz with the sign inverted
	point.freq.set(TxEqualiser::INTERPOLATION_SECOND_FREQ, Frequency::KHz);
	point.gain = freqGainTable[3].gain.get() * -1;
	freqGainTable[1] = point;

	//Add a point at frequency 92.16 MHz that has the same gain value as 40MHz with the sign inverted
	point.freq.set(TxEqualiser::INTERPOLATION_SECOND_LAST_FREQ, Frequency::KHz);
	point.gain = freqGainTable[loopLen].gain.get() * -1;
	freqGainTable.push_back(point);

	//Add the last point at -122.88MHz with a gain of 0 dBm
	freq.set(TxEqualiser::INTERPOLATION_MAX_FREQ, Frequency::KHz);
	gain.set(0.0, Power::dBm);
	point.freq = freq;
	point.gain = gain;
	freqGainTable.push_back(point);

	return status;
}

//-------------------------------------------------------------------------------------------------------------
Power TxEqualiser::getIfCentreFreqGain(void)
{
	FrequencyOffset freq(0.0);
	Power gain(0.0);

	// Get TX IF cal
	std::shared_ptr<ITxIfCalDataContainer> calData(
			std::dynamic_pointer_cast<ITxIfCalDataContainer>(ICalDataFactory::getInterface())
		);
	if (!calData)
		return 0.0;

	std::shared_ptr<ITxIfCalData> txIfCal(calData->getTxIfCal());
	if (!txIfCal)
		return 0.0;

	// skip if not loaded
	if (!txIfCal->isLoaded())
		return 0.0;

	// skip if no valid TX IF response for port 1
	std::shared_ptr<ITxIfResponse> ifResp(txIfCal->getTxIfResponse(getIndex() + 1)) ;
	if (!ifResp)
		return 0.0;

	//Get the Rx IF gain value corresponding to the centre frequency
	ifResp->getGain(0.0, gain);

	return gain;
}

//-------------------------------------------------------------------------------------------------------------
Power TxEqualiser::getRfCentreFreqGain(void)
{
	FrequencyOffset freq(0.0);
	Power gain(0.0);

	//Get Tx RF cal
	std::shared_ptr<ITxCalDataContainer> calRfData(
			std::dynamic_pointer_cast<ITxCalDataContainer>(ICalDataFactory::getInterface())
		);
	if (!calRfData)
		return 0.0;

	std::shared_ptr<ITxCalData> txRfCal(calRfData->getTxCal());
	if (!txRfCal)
		return 0.0;

	// skip if not loaded
	if (!txRfCal->isLoaded())
		return 0.0;

	// skip if no valid TX RF response
	std::shared_ptr<ITxOpenLoop> rfResp(txRfCal->getTxOpenLoop(1)) ;
	if (!rfResp)
		return 0.0;

	//Get the Tx RF gain corresponding to the centre frequency
	rfResp->getPower(mCurrentFrequency, mBaseband, mRfdsa, gain);

	return gain;
}

//-------------------------------------------------------------------------------------------------------------
void TxEqualiser::writeEqualiserCoeff(std::complex<float> input[], bool bypass)
{
	//Get number of taps used for the equaliser
	unsigned int numTaps = mFpga->read_txNumTaps(getIndex());
	//Get the number of bits used in the equaliser coefficient
	unsigned int equaliserUnity = 1u << (mFpga->read_txNumCoeffBits(getIndex()) - 1);
	std::complex<float> coeffSum(0.0, 0.0);
	float absCoeffSum;
	float scalingFactor;
	unsigned int index;

	if (numTaps > CommonTxEqualiser::MAX_NUM_TAPS)
	{
		ILoggable::logEventInfo("Tx Equaliser - Number of taps invalid");
		numTaps = CommonTxEqualiser::MAX_NUM_TAPS;
	}

	if (bypass)
	{
		//In passthrough mode, write the first real coefficient with equaliserUnity
		//and write all others with 0
		mFpga->write_txEqRealCoeff(getIndex(), 0, equaliserUnity);
		mFpga->write_txEqImagCoeff(getIndex(), 0, 0);

		for (index = 1; index < numTaps; index++)
		{
			mFpga->write_txEqRealCoeff(getIndex(), index, 0);
			mFpga->write_txEqImagCoeff(getIndex(), index, 0);
		}
		return;
	}

	//Calculate the complex sum of the inputs
	for (index = 0; index < numTaps; index++)
	{
		coeffSum += input[index];
	}

	//Calculate the absolute value of the complex sum
	absCoeffSum = sqrt((coeffSum.real() * coeffSum.real()) + (coeffSum.imag() * coeffSum.imag()));

	//Calculate the scaling factor to quantise the time domain values
	scalingFactor = equaliserUnity/absCoeffSum;

	//Write the quantised time domain values as the equaliser coefficients
	for (index = 0; index < numTaps; index++)
	{
		input[index] *= scalingFactor;
		mFpga->write_txEqRealCoeff(getIndex(), index, round(input[index].real()));
		mFpga->write_txEqImagCoeff(getIndex(), index, round(input[index].imag()));
	}
}

//-------------------------------------------------------------------------------------------------------------
void TxEqualiser::show(std::ostream& os) const
{
	unsigned int index;
	//Get number of taps used for the equaliser
	unsigned int numTaps = mFpga->read_txNumTaps(getIndex());

	os << "Tx Equaliser " << "[" << getIndex() << "] " << std::endl ;

	CommonEqualiser::show(os);

	os << " * Num Taps................: " << numTaps << std::endl ;

	if (numTaps > TxEqualiser::INTERPOLATION_SIZE)
	{
		numTaps = TxEqualiser::INTERPOLATION_SIZE;
	}
	for (index = 0; index < numTaps; index++)
	{
		os << "* [" << index << "] " << mFpga->read_txEqRealCoeff(getIndex(), index) << "+" <<
				mFpga->read_txEqImagCoeff(getIndex(), index) << "i" << std::endl ;
	}
}

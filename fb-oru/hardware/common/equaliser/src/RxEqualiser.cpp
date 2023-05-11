/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxEqualiser.cpp
 * \brief     A file to define the interface to the rx equaliser for 100MHz
 *
 *
 * \details   A file to define the interface to the rx equaliser for 100MHz
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <vector>
#include <map>
#include <cmath>

#include "Loggable.h"

#include "ICalData.h"
#include "IRxIfCalData.h"
#include "IRxIfCal.h"
#include "IRxCal.h"
#include "IRxCalData.h"
#include "IRxPort.h"
#include "IFrequencyConst.h"

#include "RxEqualiser.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

//All the frequency constants are in KHz
const float RxEqualiser::RX_IF_MIN_FREQ(-50000.0);
const float RxEqualiser::RX_IF_MAX_FREQ(50000.0);
const float RxEqualiser::RX_RF_FREQ_STEP(10000.0);
const float RxEqualiser::RX_IF_FREQ_STEP(10000.0);
const float RxEqualiser::INTERPOLATION_MIN_FREQ(-122880.0);
const float RxEqualiser::INTERPOLATION_MAX_FREQ(122880.0);
const float RxEqualiser::INTERPOLATION_SECOND_FREQ(-92160.0);
const float RxEqualiser::INTERPOLATION_SECOND_LAST_FREQ(92160.0);
const unsigned int RxEqualiser::INTERPOLATION_SIZE(1024);


//=============================================================================================================
// RxEqualiser
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxEqualiser::RxEqualiser(int index, const char* name) :
	CommonRxEqualiser(index, name, RxEqualiser::INTERPOLATION_MIN_FREQ * Frequency::KHz,
			RxEqualiser::INTERPOLATION_MAX_FREQ * Frequency::KHz, RxEqualiser::INTERPOLATION_SIZE),
	mFpga( IFpgaMgr::getIFpgaAntennaRegs() ),
	mRfdsa()
{
}

//-------------------------------------------------------------------------------------------------------------
RxEqualiser::~RxEqualiser()
{
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RxEqualiser::calculateEqualiser(void)
{
	ReturnType::State status = ReturnType::RT_OK;
	std::vector<float> window;
	std::vector<EqPoint> freqGainTable1;
	std::vector<EqPoint> freqGainTable2;
	std::complex<float> input[RxEqualiser::INTERPOLATION_SIZE] = {0};

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

	//Extract frequency response from Rx IF cal file
	status = extractIfFreqResp(ifFreqResponse);
	if (status != ReturnType::RT_OK)
	{
		ILoggable::logEventInfo("Rx Equaliser - Entering passthrough mode as IF cal data cannot be loaded");
		//Put the equaliser in pass through mode
		writeEqualiserCoeff(input, true);
		return status;
	}

	//Interpolate the IF frequency response to get 1024 equally spaced points
	if (interpolateFreqResp(ifFreqResponse, freqGainTable1) == false)
	{
		ILoggable::logEventInfo("Rx Equaliser - Entering passthrough mode due to internal error");
		//Put the equaliser in pass through mode
		writeEqualiserCoeff(input, true);
		return ReturnType::RT_ERROR;
	}

	//Extract frequency response from Rx RF cal file
	status = extractRfFreqResp(rfFreqResponse);
	if (status != ReturnType::RT_OK)
	{
		ILoggable::logEventInfo("Rx Equaliser - Entering passthrough mode as RF cal data cannot be loaded");
		//Put the equaliser in pass through mode
		writeEqualiserCoeff(input, true);
		return status;
	}

	//Interpolate the RF frequency response to get 1024 equally spaced points
	if (interpolateFreqResp(rfFreqResponse, freqGainTable2) == false)
	{
		ILoggable::logEventInfo("Rx Equaliser - Entering passthrough mode due to internal error");
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
ReturnType::State RxEqualiser::extractIfFreqResp(std::vector<EqPoint> &freqGainTable)
{
	ReturnType::State status = ReturnType::RT_OK;

	FrequencyOffset freq(0.0);
	Power gain(0.0);
	Power rfCentreGain(0.0);
	EqPoint point;

	// Get RX IF cal
	std::shared_ptr<IRxIfCalDataContainer> calData(
			std::dynamic_pointer_cast<IRxIfCalDataContainer>(ICalDataFactory::getInterface())
		);
	if (!calData)
		return ReturnType::RT_NOT_FOUND;

	std::shared_ptr<IRxIfCalData> rxIfCal(calData->getRxIfCal());
	if (!rxIfCal)
		return ReturnType::RT_NOT_FOUND ;

	// skip if not loaded
	if (!rxIfCal->isLoaded())
		return ReturnType::RT_NOT_INITIALISED ;

	// skip if no valid RX IF response
	std::shared_ptr<IRxIfResponse> ifResp(rxIfCal->getRxIfResponse(getIndex() + 1)) ;
	if (!ifResp)
		return ReturnType::RT_NOT_FOUND ;

	Injection_t loInjection = IRxFrequencyConstFactory::getInterface()->getLOInjection();

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

	//Get the Rx IF gain corresponding to the centre frequency
	rfCentreGain = getIfCentreFreqGain();

	/* Get the Rx IF gain corresponding to frequencies -50 to +50 MHz in steps of 5MHz
	 */
	int loopLen = ((RxEqualiser::RX_IF_MAX_FREQ - RxEqualiser::RX_IF_MIN_FREQ)/RxEqualiser::RX_IF_FREQ_STEP) + 1;
	for (UINT16 index = 0; index < loopLen; index++)
	{
		//Set frequency offset from centre frequency
		freq.set(RxEqualiser::RX_IF_MIN_FREQ + (index * RxEqualiser::RX_IF_FREQ_STEP), Frequency::KHz);

		//Get the Rx IF gain value corresponding to the frequency offset from the centre frequency
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
	point.freq.set(RxEqualiser::INTERPOLATION_SECOND_FREQ, Frequency::KHz);
	point.gain = freqGainTable[3].gain.get() * -1;
	freqGainTable[1] = point;

	//Add a point at frequency 92.16 MHz that has the same gain value as 40MHz with the sign inverted
	point.freq.set(RxEqualiser::INTERPOLATION_SECOND_LAST_FREQ, Frequency::KHz);
	point.gain = freqGainTable[loopLen].gain.get() * -1;
	freqGainTable.push_back(point);

	//Add the last point at 122.88MHz with a gain of 0 dBm
	freq.set(RxEqualiser::INTERPOLATION_MAX_FREQ, Frequency::KHz);
	gain.set(0.0, Power::dBm);
	point.freq = freq;
	point.gain = gain;
	freqGainTable.push_back(point);

	return status;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State RxEqualiser::extractRfFreqResp(std::vector<EqPoint> &freqGainTable)
{
	ReturnType::State status = ReturnType::RT_OK;

	FrequencyOffset freq(0.0);
	Power gain(0.0);
	Power rfCentreGain(0.0);
	EqPoint point;

	//Get Rx RF cal
	std::shared_ptr<IRxCalDataContainer> calRfData(
			std::dynamic_pointer_cast<IRxCalDataContainer>(ICalDataFactory::getInterface())
		);
	if (!calRfData)
		return ReturnType::RT_NOT_FOUND;

	std::shared_ptr<IRxCalData> rxRfCal(calRfData->getRxCal());
	if (!rxRfCal)
		return ReturnType::RT_NOT_FOUND ;

	// skip if not loaded
	if (!rxRfCal->isLoaded())
		return ReturnType::RT_NOT_INITIALISED ;

	// skip if no valid RX RF response
	std::shared_ptr<IRxOpenLoop> rfResp(rxRfCal->getRxOpenLoop(getIndex() + 1)) ;
	if (!rfResp)
		return ReturnType::RT_NOT_FOUND ;

	//TODO: The first dsa value for the centre frequency is used for extraction of cal data. Do we need to get the dsa value from tif command?
	mRfdsa = rfResp->getRfdsaForFrequency(mCurrentFrequency);

	//Get the Rx RF gain corresponding to the centre frequency
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
	int loopLen = ((RxEqualiser::RX_IF_MAX_FREQ - RxEqualiser::RX_IF_MIN_FREQ)/RxEqualiser::RX_RF_FREQ_STEP) + 1;
	for (UINT16 index = 0; index < loopLen; index++)
	{
		Frequency rxCalFreq;

		//Set the frequency from the 100MHz range
		rxCalFreq.set(mCurrentFrequency.get(Frequency::KHz) + RxEqualiser::RX_IF_MIN_FREQ + (index * RxEqualiser::RX_RF_FREQ_STEP), Frequency::KHz);

		Power rfGain = rfResp->dBfsTodBm(rxCalFreq, mRfdsa);

		//Set frequency offset from centre frequency
		freq.set(rxCalFreq.getInt() - mCurrentFrequency.getInt());

		//Record the Rx RF gain value and normalise it
		gain = rfCentreGain - rfGain;

		//Add the point in the table
		point.freq = freq;
		point.gain = gain;
		freqGainTable.push_back(point);
	}

	//Add a point at frequency -92.16 MHz that has the same gain value as -40MHz with the sign inverted
	point.freq.set(RxEqualiser::INTERPOLATION_SECOND_FREQ, Frequency::KHz);
	point.gain = freqGainTable[3].gain.get() * -1;
	freqGainTable[1] = point;

	//Add a point at frequency 92.16 MHz that has the same gain value as 40MHz with the sign inverted
	point.freq.set(RxEqualiser::INTERPOLATION_SECOND_LAST_FREQ, Frequency::KHz);
	point.gain = freqGainTable[loopLen].gain.get() * -1;
	freqGainTable.push_back(point);

	//Add the last point at -122.88MHz with a gain of 0 dBm
	freq.set(RxEqualiser::INTERPOLATION_MAX_FREQ, Frequency::KHz);
	gain.set(0.0, Power::dBm);
	point.freq = freq;
	point.gain = gain;
	freqGainTable.push_back(point);

	return status;
}

//-------------------------------------------------------------------------------------------------------------
Power RxEqualiser::getIfCentreFreqGain(void)
{
	FrequencyOffset freq(0.0);
	Power gain(0.0);

	// Get RX IF cal
	std::shared_ptr<IRxIfCalDataContainer> calData(
			std::dynamic_pointer_cast<IRxIfCalDataContainer>(ICalDataFactory::getInterface())
		);
	if (!calData)
		return 0.0;

	std::shared_ptr<IRxIfCalData> rxIfCal(calData->getRxIfCal());
	if (!rxIfCal)
		return 0.0;

	// skip if not loaded
	if (!rxIfCal->isLoaded())
		return 0.0;

	// skip if no valid RX IF response for port 1
	std::shared_ptr<IRxIfResponse> ifResp(rxIfCal->getRxIfResponse(1)) ;
	if (!ifResp)
		return 0.0;

	//Get the Rx IF gain value corresponding to the centre frequency
	ifResp->getGain(0.0, gain);

	return gain;
}

//-------------------------------------------------------------------------------------------------------------
Power RxEqualiser::getRfCentreFreqGain(void)
{
	FrequencyOffset freq(0.0);
	Power gain(0.0);

	//Get Rx RF cal
	std::shared_ptr<IRxCalDataContainer> calRfData(
			std::dynamic_pointer_cast<IRxCalDataContainer>(ICalDataFactory::getInterface())
		);
	if (!calRfData)
		return 0.0;

	std::shared_ptr<IRxCalData> rxRfCal(calRfData->getRxCal());
	if (!rxRfCal)
		return 0.0;

	// skip if not loaded
	if (!rxRfCal->isLoaded())
		return 0.0;

	// skip if no valid RX RF response for port 1
	std::shared_ptr<IRxOpenLoop> rfResp(rxRfCal->getRxOpenLoop(1)) ;
	if (!rfResp)
		return 0.0;

	//Get the aggregate gain for port 1 at centre frequency
	gain = rfResp->dBfsTodBm(mCurrentFrequency, mRfdsa);

	return gain;
}

//-------------------------------------------------------------------------------------------------------------
void RxEqualiser::writeEqualiserCoeff(std::complex<float> input[], bool bypass)
{
	//Get number of taps used for the equaliser
	unsigned int numTaps = mFpga->read_rxNumTaps(getIndex());
	//Get the number of bits used in the equaliser coefficient
	unsigned int equaliserUnity = 1u << (mFpga->read_rxNumCoeffBits(getIndex()) - 1);
	std::complex<float> coeffSum(0.0, 0.0);
	float absCoeffSum;
	float scalingFactor;
	unsigned int index;

	if (numTaps > CommonRxEqualiser::MAX_NUM_TAPS)
	{
		ILoggable::logEventInfo("Rx Equaliser - Number of taps invalid");
		numTaps = CommonRxEqualiser::MAX_NUM_TAPS;
	}

	if (bypass)
	{
		//In passthrough mode, write the first real coefficient with equaliserUnity
		//and write all others with 0
		mFpga->write_rxEqRealCoeff(getIndex(), 0, equaliserUnity);
		mFpga->write_rxEqImagCoeff(getIndex(), 0, 0);

		for (index = 1; index < numTaps; index++)
		{
			mFpga->write_rxEqRealCoeff(getIndex(), index, 0);
			mFpga->write_rxEqImagCoeff(getIndex(), index, 0);
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
		mFpga->write_rxEqRealCoeff(getIndex(), index, round(input[index].real()));
		mFpga->write_rxEqImagCoeff(getIndex(), index, round(input[index].imag()));
	}
}

//-------------------------------------------------------------------------------------------------------------
void RxEqualiser::show(std::ostream& os) const
{
	unsigned int index;
	//Get number of taps used for the equaliser
	unsigned int numTaps = mFpga->read_rxNumTaps(getIndex());

	os << "Rx Equaliser " << "[" << getIndex() << "] " << std::endl ;

	CommonEqualiser::show(os);

	os << " * Num Taps................: " << numTaps << std::endl ;

	if (numTaps > RxEqualiser::INTERPOLATION_SIZE)
	{
		numTaps = RxEqualiser::INTERPOLATION_SIZE;
	}
	for (index = 0; index < numTaps; index++)
	{
		os << "* [" << index << "] " << mFpga->read_rxEqRealCoeff(getIndex(), index) << "+" <<
				mFpga->read_rxEqImagCoeff(getIndex(), index) << "i" << std::endl ;
	}
}

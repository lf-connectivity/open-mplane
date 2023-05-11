/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonEqualiser.cpp
 * \brief     A file to define the interface to a common equaliser
 *
 *
 * \details   A file to define the interface to a common equaliser
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "CommonEqualiser.h"
#include "IRadio.h"
#include "cubicSpline.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const float CommonEqualiser::SAMPLE_RATE_MHZ(245.76);

//=============================================================================================================
// CommonEqualiser
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int CommonEqualiser::getIndex() const
{
    return mIndex;
}

//-------------------------------------------------------------------------------------------------------------
std::string CommonEqualiser::getName() const
{
    return mName;
}

//-------------------------------------------------------------------------------------------------------------
CommonEqualiser::CommonEqualiser(int index, const char* name,
		FrequencyOffset minFreq, FrequencyOffset maxFreq, unsigned int numPoints) :
	mIndex( index ), mName( name ),
	mInterpolationMinFreq(minFreq), mInterpolationMaxFreq(maxFreq), mInterpolationPoints(numPoints),
	mPassThroughMode(false),
	mCalMode(false)
{
    mFrequencyChangeValue = 0.0;
    std::shared_ptr<IRadio> radio(IRadioFactory::getInterface());

    // Attach to radio instance
    std::dynamic_pointer_cast<Subject<ICalModeChange>>(radio)->attach(*this);
}

//-------------------------------------------------------------------------------------------------------------
CommonEqualiser::~CommonEqualiser()
{
}

//-------------------------------------------------------------------------------------------------------------
bool CommonEqualiser::getPassthroughMode( void )
{
	return mPassThroughMode;
}

//-------------------------------------------------------------------------------------------------------------
void CommonEqualiser::setPassthroughMode( bool enable )
{
	if (mPassThroughMode != enable)
	{
		mPassThroughMode = enable;
		calculateEqualiser();
	}
}

//-------------------------------------------------------------------------------------------------------------
void CommonEqualiser::show(std::ostream& os) const
{
	os << " * Frequency...............: " << mCurrentFrequency << std::endl ;
	os << " * Passthough mode.........: " << mPassThroughMode << std::endl ;
	os << " * Min Interpolation Freq..: " << mInterpolationMinFreq << std::endl ;
	os << " * Max Interpolation Freq..: " << mInterpolationMaxFreq << std::endl ;
	os << " * Num Interpolation Pts...: " << mInterpolationPoints << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
void CommonEqualiser::attachToFreqChange()
{
}

//-------------------------------------------------------------------------------------------------------------
void CommonEqualiser::update(IFrequencyChange& subject)
{
    mFrequencyChangeValue = subject.getFrequency();
    if (mCurrentFrequency != mFrequencyChangeValue)
    {
    	mCurrentFrequency = mFrequencyChangeValue;
    	calculateEqualiser();
    }
}

//-------------------------------------------------------------------------------------------------------------
void CommonEqualiser::update(ICalModeChange& subject)
{
	bool calMode = subject.getCalMode();

	if (mCalMode != calMode)
	{
		mCalMode = calMode;
		calculateEqualiser();
	}
}

const char* CommonEqualiser::name() const
{
	return mName.c_str();
}

//-------------------------------------------------------------------------------------------------------------
bool CommonEqualiser::interpolateFreqResp(std::vector<EqPoint> ipFreqGainTable, std::vector<EqPoint> &opFreqGainTable)
{
	std::vector<double> freqPoints;
	std::vector<double> gainPoints;
	std::vector<double> queryPoints;
	std::vector<double> interpolatedValues;

	opFreqGainTable.clear();

	//Write the frequency and gain vectors
	for (unsigned int i = 0; i < ipFreqGainTable.size(); i++)
	{
		freqPoints.push_back(ipFreqGainTable[i].freq.getDbl());
		gainPoints.push_back(ipFreqGainTable[i].gain.get());
	}

	//Prepare the query vector
	FrequencyOffset freq = mInterpolationMinFreq;
	double step = (mInterpolationMaxFreq.getDbl() - mInterpolationMinFreq.getDbl())/mInterpolationPoints;
	for (unsigned int i = 0; i < mInterpolationPoints; i++)
	{
		queryPoints.push_back(freq.getDbl());
		freq += step;
	}

	//Interpolate the values using the cubic spline algorithm
	cubicSpline spline;

	if (spline.calculate(freqPoints, gainPoints, queryPoints, interpolatedValues))
	{
		//Copy the interpolated values in the required format
		for (unsigned int i = 0; i < mInterpolationPoints; i++)
		{
			EqPoint point;
			point.freq.set(queryPoints[i]);
			point.gain.set(interpolatedValues[i]);
			opFreqGainTable.push_back(point);
		}

		return true;
	}

	return false;

}

//-------------------------------------------------------------------------------------------------------------
void CommonEqualiser::combineFreqResp(std::vector<EqPoint> &freqGainTable1, std::vector<EqPoint> &freqGainTable2)
{
	//Add the gains from the 2 frequency responses and store in freqGainTable1
	for (UINT16 index = 0; index < freqGainTable1.size() && index < freqGainTable2.size(); index++)
	{
		freqGainTable1[index].gain = freqGainTable1[index].gain + freqGainTable2[index].gain;
	}
}

//-------------------------------------------------------------------------------------------------------------
void CommonEqualiser::calculateTukeyWindow(std::vector<float> &window_function)
{
	//Refer equation from wiki page:https://en.wikipedia.org/wiki/Window_function#Tukey_window

	unsigned int tukeyCentrePoints = 2 * ceil(mInterpolationPoints * 50.0/CommonEqualiser::SAMPLE_RATE_MHZ);
	unsigned int tukeyCosinePoints = (mInterpolationPoints - tukeyCentrePoints)/2;
	float tukeyAlpha = 2 * (static_cast<float>(tukeyCosinePoints)/mInterpolationPoints);

	unsigned int index;
	unsigned int srcIndex;

	window_function.clear();
	window_function.resize(mInterpolationPoints);

	//Calculate the first part of the cosine lobe
	for (index = 0; index < tukeyCosinePoints; index++)
	{
		window_function[index] = (0.5 * (1 + cos(M_PI * ((2 * index/(tukeyAlpha * (mInterpolationPoints - 1))) - 1))));
	}

	//The central part of the tukey window
	for (index = tukeyCosinePoints;
			index < (tukeyCosinePoints + tukeyCentrePoints);
			index++)
	{
		window_function[index] = 1;
	}

	//The second cosine lobe is calculated by reversing the first cosine lobe
	for (index = tukeyCosinePoints + tukeyCentrePoints,
			srcIndex = (tukeyCosinePoints - 1);
			index < mInterpolationPoints;
			index++, srcIndex--)
	{
		window_function[index] = window_function[srcIndex];
	}
}

//-------------------------------------------------------------------------------------------------------------
void CommonEqualiser::performIfft(std::vector<EqPoint> freqGainTable, std::complex<float> timeDomainValues[])
{
	UINT16 destIndex;
	UINT16 srcIndex;
	UINT16 numPoints = freqGainTable.size();

	//Construct the input vector of IFFT so that the positive values are added from 0 to max
	//and then the negative values are added from the min to 0
	for (destIndex = 0, srcIndex = numPoints/2 ;
			destIndex < numPoints/2; destIndex++, srcIndex++)
	{
		//Convert the db values to linear
		//(This converting from db to voltage and not watts. Hence the equation uses divide by 20 instead of 10)
		timeDomainValues[destIndex] = exp10(freqGainTable[srcIndex].gain.get()/20.0);
	}

	for (destIndex = numPoints/2, srcIndex = 0 ;
			destIndex < numPoints; destIndex++, srcIndex++)
	{
		//Convert the db values to linear
		//(This converting from db to voltage and not watts. Hence the equation uses divide by 20 instead of 10)
		timeDomainValues[destIndex] = exp10(freqGainTable[srcIndex].gain.get()/20.0);
	}

	//Calculate IFFT
	std::shared_ptr<IFftCalc<std::complex<float>> > ifft(InverseFftCalcBuilder<std::complex<float>>::factory(numPoints)) ;

	// inverse fft
	ifft->fft(timeDomainValues) ;
}

//-------------------------------------------------------------------------------------------------------------
ReturnType::State CommonEqualiser::calculateEqualiser(void)
{
	return ReturnType::RT_OK;
}

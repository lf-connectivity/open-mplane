/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxIfCal.cpp
 * \brief     RX IF calibration classes for storing the cal data
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "IRxAttenuators.h"

#include "RxIfCal.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const std::string RxIfCal::name = "FTUCalibrationRxIF";

const std::string RxIfResponse::name("RxIfResponse");
const std::string RxIfResponse::PathStr("Path") ;
const std::string RxIfResponse::DateStr("Date") ;
const std::string RxIfResponse::LinearTemperatureCompensation("LinearTemperatureCompensation") ;
const std::string RxIfResponse::CoefficientStr("Coefficient");
const std::string RxIfResponse::TemperatureStr("Temperature");

const std::string RxIfOffsetFrequency::name("OffsetFrequency");
const std::string RxIfOffsetFrequency::UpperStr("Upper");
const std::string RxIfOffsetFrequency::LowerStr("Lower");

const std::string RxIfFrequencyOffsetTable::name("FrequencyTable");
const std::string RxIfFrequencyOffsetTable::PointStr("Point");
const std::string RxIfFrequencyOffsetTable::offsetStr("Frequency");
const std::string RxIfFrequencyOffsetTable::gainStr("Gain");


//=============================================================================================================
// RxIfFrequencyOffsetTable
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxIfFrequencyOffsetTable::RxIfFrequencyOffsetTable() :
	mCalPoints()
{
}

//-------------------------------------------------------------------------------------------------------------
RxIfFrequencyOffsetTable::~RxIfFrequencyOffsetTable()
{
}

//-------------------------------------------------------------------------------------------------------------
void RxIfFrequencyOffsetTable::addRxIfPoint(const RxIfPoint& point)
{
	mCalPoints.push_back( point );
}

//-------------------------------------------------------------------------------------------------------------
const RxIfPoint RxIfFrequencyOffsetTable::getPoint(const FrequencyOffset& freqOffset) const
{
	if (mCalPoints.empty())
		return RxIfPoint() ;

	RxIfPoint prevPoint(mCalPoints[0]) ;
	for (auto point : mCalPoints)
	{
		// if we've gone past the freq offset we're looking for then stop
		if (point.freqOffset > freqOffset)
		{
			// choose closest point to this frequency
			if (freqOffset - prevPoint.freqOffset > point.freqOffset - freqOffset)
				return point ;

			return prevPoint ;
		}

		// have we found it
		if (point.freqOffset == freqOffset)
			return point ;

		prevPoint = point ;
	}
	return prevPoint ;
}


//=============================================================================================================
// RxIfOffsetFrequency
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxIfOffsetFrequency::RxIfOffsetFrequency(FrequencyOffset upper, FrequencyOffset lower) :
	mUpper(upper),
	mLower(lower),
	mFrequencyOffsetTables()
{
}

//-------------------------------------------------------------------------------------------------------------
RxIfOffsetFrequency::~RxIfOffsetFrequency()
{
}

//-------------------------------------------------------------------------------------------------------------
void RxIfOffsetFrequency::addFrequencyOffsetTable(std::shared_ptr<RxIfFrequencyOffsetTable> frequencyTable)
{
	mFrequencyOffsetTables.push_back( frequencyTable );
}

//-------------------------------------------------------------------------------------------------------------
const FrequencyOffset RxIfOffsetFrequency::getLower() const
{
	return mLower;
}

//-------------------------------------------------------------------------------------------------------------
const FrequencyOffset RxIfOffsetFrequency::getUpper() const
{
	return mUpper;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<RxIfFrequencyOffsetTable> RxIfOffsetFrequency::findFreqTable( FrequencyOffset frequency )
{
	if (mFrequencyOffsetTables.empty())
		return std::shared_ptr<RxIfFrequencyOffsetTable>() ;

	return mFrequencyOffsetTables.front() ;
}

////-------------------------------------------------------------------------------------------------------------
//const std::list<std::shared_ptr<RxIfFrequencyOffsetTable> >& RxIfOffsetFrequency::getFrequencyOffsetTables() const
//{
//	return mFrequencyOffsetTables ;
//}

//=============================================================================================================
// RxIfResponse
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxIfResponse::RxIfResponse(int path, float tempCoeff,
		float temperature, const std::string& date) :
	mPath(path),
	mTempCoeff(tempCoeff),
	mTemp(temperature),
	mDate(date),
	mOffsetFrequencies()
{
}

//-------------------------------------------------------------------------------------------------------------
RxIfResponse::~RxIfResponse()
{
}

//-------------------------------------------------------------------------------------------------------------
int RxIfResponse::getPath()
{
	return mPath;
}

//-------------------------------------------------------------------------------------------------------------
float RxIfResponse::getCoefficient()
{
	return mTempCoeff;
}

//-------------------------------------------------------------------------------------------------------------
float RxIfResponse::getTemperature()
{
	return mTemp ;
}

//-------------------------------------------------------------------------------------------------------------
std::string RxIfResponse::getDate()
{
	return mDate;
}

////-------------------------------------------------------------------------------------------------------------
//const std::list<std::shared_ptr<RxIfOffsetFrequency> >& RxIfResponse::getOffsetFrequencies() const
//{
//	return mOffsetFrequencies ;
//}


//-------------------------------------------------------------------------------------------------------------
bool RxIfResponse::getGain(FrequencyOffset frequencyOffset, Power& gain)
{
	std::shared_ptr<RxIfOffsetFrequency> freqOffset(findOffsetFreq(frequencyOffset)) ;
	if( !freqOffset )
		return false ;

	std::shared_ptr<RxIfFrequencyOffsetTable> freqTable(freqOffset->findFreqTable(frequencyOffset)) ;
	if( !freqTable )
		return false ;

	RxIfPoint point(freqTable->getPoint(frequencyOffset));
	gain = point.gain ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void RxIfResponse::addOffsetFrequency(std::shared_ptr<RxIfOffsetFrequency> offsetFrequencyOffset)
{
	mOffsetFrequencies.push_back(offsetFrequencyOffset) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<RxIfOffsetFrequency> RxIfResponse::findOffsetFreq(FrequencyOffset frequency)
{
	if (mOffsetFrequencies.empty())
		return std::shared_ptr<RxIfOffsetFrequency>() ;

	for (auto offsetFreq : mOffsetFrequencies)
	{
		if ( (frequency >= offsetFreq->getLower()) && (frequency <= offsetFreq->getUpper()) )
			return offsetFreq ;
	}

	return std::shared_ptr<RxIfOffsetFrequency>() ;
}


//=============================================================================================================
// RxIfCal
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxIfCal::RxIfCal(const std::string& version, const std::string& country,
		const std::string& facility, const std::string& theoperator):
				mVersion( version ), mCountry( country ),
				mFacility( facility ), mOperator( theoperator)
{
}

//-------------------------------------------------------------------------------------------------------------
RxIfCal::~RxIfCal()
{
	mRxIfResponseData.clear();
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRxIfResponse> RxIfCal::getRxIfResponse(int path)
{
	return mRxIfResponseData[ path ];
}

//-------------------------------------------------------------------------------------------------------------
void RxIfCal::addRxIfResponse(int path, std::shared_ptr<RxIfResponse> rxIfResponse)
{
	mRxIfResponseData[path] = rxIfResponse;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::RxIfCal::getVersion() const
{
	return mVersion ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::RxIfCal::getCountry() const
{
	return mCountry ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::RxIfCal::getFacility() const
{
	return mFacility ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::RxIfCal::getOperator() const
{
	return mOperator ;
}

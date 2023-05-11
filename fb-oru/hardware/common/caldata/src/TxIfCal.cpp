/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxIfCal.cpp
 * \brief     TX IF calibration classes for storing the cal data
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "TxIfCal.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================

const std::string TxIfCal::name = "FTUCalibrationTxIF";

const std::string TxIfResponse::name("TxIfResponse");
const std::string TxIfResponse::PathStr("Path") ;
const std::string TxIfResponse::DateStr("Date") ;
const std::string TxIfResponse::TemperatureStr("Temperature");

const std::string TxIfOffsetFrequency::name("OffsetFrequency");
const std::string TxIfOffsetFrequency::UpperStr("Upper");
const std::string TxIfOffsetFrequency::LowerStr("Lower");

const std::string TxIfFrequencyOffsetTable::name("FrequencyTable");
const std::string TxIfFrequencyOffsetTable::PointStr("Point");
const std::string TxIfFrequencyOffsetTable::offsetStr("Frequency");
const std::string TxIfFrequencyOffsetTable::gainStr("Gain");


//=============================================================================================================
// TxIfFrequencyOffsetTable
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxIfFrequencyOffsetTable::TxIfFrequencyOffsetTable() :
	mCalPoints()
{
}

//-------------------------------------------------------------------------------------------------------------
TxIfFrequencyOffsetTable::~TxIfFrequencyOffsetTable()
{
}

//-------------------------------------------------------------------------------------------------------------
void TxIfFrequencyOffsetTable::addTxIfPoint(const TxIfPoint& point)
{
	mCalPoints.push_back( point );
}

//-------------------------------------------------------------------------------------------------------------
const TxIfPoint TxIfFrequencyOffsetTable::getPoint(const FrequencyOffset& freqOffset) const
{
	if (mCalPoints.empty())
		return TxIfPoint() ;

	TxIfPoint prevPoint(mCalPoints[0]) ;
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
// TxIfOffsetFrequency
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxIfOffsetFrequency::TxIfOffsetFrequency(FrequencyOffset upper, FrequencyOffset lower) :
	mUpper(upper),
	mLower(lower),
	mFrequencyOffsetTables()
{
}

//-------------------------------------------------------------------------------------------------------------
TxIfOffsetFrequency::~TxIfOffsetFrequency()
{
}

//-------------------------------------------------------------------------------------------------------------
void TxIfOffsetFrequency::addFrequencyOffsetTable(std::shared_ptr<TxIfFrequencyOffsetTable> frequencyTable)
{
	mFrequencyOffsetTables.push_back( frequencyTable );
}

//-------------------------------------------------------------------------------------------------------------
const FrequencyOffset TxIfOffsetFrequency::getLower() const
{
	return mLower;
}

//-------------------------------------------------------------------------------------------------------------
const FrequencyOffset TxIfOffsetFrequency::getUpper() const
{
	return mUpper;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TxIfFrequencyOffsetTable> TxIfOffsetFrequency::findFreqTable( FrequencyOffset frequency )
{
	if (mFrequencyOffsetTables.empty())
		return std::shared_ptr<TxIfFrequencyOffsetTable>() ;

	return mFrequencyOffsetTables.front() ;
}

//=============================================================================================================
// TxIfResponse
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxIfResponse::TxIfResponse(int path, float temperature, const std::string& date) :
	mPath(path),
	mTemp(temperature),
	mDate(date),
	mOffsetFrequencies()
{
}

//-------------------------------------------------------------------------------------------------------------
TxIfResponse::~TxIfResponse()
{
}

//-------------------------------------------------------------------------------------------------------------
int TxIfResponse::getPath()
{
	return mPath;
}

//-------------------------------------------------------------------------------------------------------------
float TxIfResponse::getTemperature()
{
	return mTemp ;
}

//-------------------------------------------------------------------------------------------------------------
std::string TxIfResponse::getDate()
{
	return mDate;
}

////-------------------------------------------------------------------------------------------------------------
//const std::list<std::shared_ptr<TxIfOffsetFrequency> >& TxIfResponse::getOffsetFrequencies() const
//{
//	return mOffsetFrequencies ;
//}


//-------------------------------------------------------------------------------------------------------------
bool TxIfResponse::getGain(FrequencyOffset frequencyOffset, Power& gain)
{
	std::shared_ptr<TxIfOffsetFrequency> freqOffset(findOffsetFreq(frequencyOffset)) ;
	if( !freqOffset )
		return false ;

	std::shared_ptr<TxIfFrequencyOffsetTable> freqTable(freqOffset->findFreqTable(frequencyOffset)) ;
	if( !freqTable )
		return false ;

	TxIfPoint point(freqTable->getPoint(frequencyOffset));
	gain = point.gain ;
	return true;
}

//-------------------------------------------------------------------------------------------------------------
void TxIfResponse::addOffsetFrequency(std::shared_ptr<TxIfOffsetFrequency> offsetFrequencyOffset)
{
	mOffsetFrequencies.push_back(offsetFrequencyOffset) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TxIfOffsetFrequency> TxIfResponse::findOffsetFreq(FrequencyOffset frequency)
{
	if (mOffsetFrequencies.empty())
		return std::shared_ptr<TxIfOffsetFrequency>() ;

	for (auto offsetFreq : mOffsetFrequencies)
	{
		if ( (frequency >= offsetFreq->getLower()) && (frequency <= offsetFreq->getUpper()) )
			return offsetFreq ;
	}

	return std::shared_ptr<TxIfOffsetFrequency>() ;
}


//=============================================================================================================
// TxIfCal
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxIfCal::TxIfCal(const std::string& version, const std::string& country,
		const std::string& facility, const std::string& theoperator):
				mVersion( version ), mCountry( country ),
				mFacility( facility ), mOperator( theoperator)
{
}

//-------------------------------------------------------------------------------------------------------------
TxIfCal::~TxIfCal()
{
	mTxIfResponseData.clear();
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITxIfResponse> TxIfCal::getTxIfResponse(int path)
{
	return mTxIfResponseData[ path ];
}

//-------------------------------------------------------------------------------------------------------------
void TxIfCal::addTxIfResponse(int path, std::shared_ptr<TxIfResponse> rxIfResponse)
{
	mTxIfResponseData[path] = rxIfResponse;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::TxIfCal::getVersion() const
{
	return mVersion ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::TxIfCal::getCountry() const
{
	return mCountry ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::TxIfCal::getFacility() const
{
	return mFacility ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::TxIfCal::getOperator() const
{
	return mOperator ;
}

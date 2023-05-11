/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxIfCalData.cpp
 * \brief     <one-line description of file>
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// Use the ICalDownloadManagement class to get the installed file path
#include "ICalDownloadManagement.h"

#include "RxIfCalData.h"
#include "GlobalTypeDefs.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
RxIfCalData::RxIfCalData( std::shared_ptr<ICalDownload> calDownload ):
	CommonCalBase("RxIfCal", "HW"),
	mCalDownload( calDownload ),
	mCalFilePath( calDownload->getInstallFilePath() ),
	mRxIfCal()
{
}

//-------------------------------------------------------------------------------------------------------------
RxIfCalData::~RxIfCalData()
{
}

//-------------------------------------------------------------------------------------------------------------
void RxIfCalData::show()
{
}


//-------------------------------------------------------------------------------------------------------------
ReturnType::State RxIfCalData::load()
{
	ReturnType::State status = ReturnType::RT_OK;

	if( isLoaded() )
	{
		mRxIfCal.reset();  // deference the caldata shared pointer so that it gets deleted
		setLoaded( false );
	}

	// Parse the final expanded file
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(mCalFilePath.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		eventError("Could not parse file %s", mCalFilePath.c_str() );
		return ReturnType::RT_NOT_FOUND;
	}

	tinyxml2::XMLElement *root_element = doc.RootElement();
	if (root_element == NULL)
	{
		eventError("Invalid xml format in file %s ", mCalFilePath.c_str());
		return ReturnType::RT_NOT_FOUND;
	}

	if (!parseRxIfCal(root_element))
	{
		eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
		return ReturnType::RT_SYNTAX_ERROR;
	}
	setLoaded(true);
	return status;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRxIfResponse> RxIfCalData::getRxIfResponse(int path)
{
    return mRxIfCal->getRxIfResponse(path);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void RxIfCalData::getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const
{
	for (auto& entry : attrMap)
	{
		const char* attr(node->Attribute(entry.first.c_str()));
		if (attr)
			entry.second = std::string(attr);
	}
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<RxIfCal> RxIfCalData::createRxIfCal(
		const std::string& version, const std::string& country,
		const std::string& facility, const std::string& theoperator)
{
	return std::make_shared<RxIfCal>(version, country, facility, theoperator) ;
}


//-------------------------------------------------------------------------------------------------------------
bool RxIfCalData::parseRxIfCal(tinyxml2::XMLElement* node)
{

	if (node->Name() != RxIfCal::name) // is the first element the correct element?
		return false ;

	AttrMap attributes;
	attributes["version"] = "";
	attributes["country"] = "";
	attributes["facility"] = "";
	attributes["operator"] = "";
	getAttributeMap(node, attributes);

	mRxIfCal = createRxIfCal(attributes["version"], attributes["country"],
					attributes["facility"], attributes["operator"]);

	for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
			cur_node; cur_node = cur_node->NextSiblingElement())
	{
		// Get the device definition inside board
		if (!extractRxIfResponse(mRxIfCal, cur_node))
			return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool RxIfCalData::extractRxIfResponse(std::shared_ptr<RxIfCal> mRxIfCal, tinyxml2::XMLElement* node)
{
	if (node->Name() != RxIfResponse::name)    // is the The TxOpenLoop element?
		return false ;

	tinyxml2::XMLElement* ele = node->FirstChildElement();

	if (ele->Name() != RxIfResponse::PathStr)
		return false ;

	int path = atoi(ele->GetText());
	ele = ele->NextSiblingElement();
	std::string date = "";
	if (ele->Name() != RxIfResponse::DateStr)
		return false ;
	date = ele->GetText();

	mCalDownload->addPath(path, date) ;

	ele = ele->NextSiblingElement();
	if (ele->Name() != RxIfResponse::LinearTemperatureCompensation)
		return false ;

	tinyxml2::XMLElement* tempEle = ele->FirstChildElement();
	if (tempEle->Name() != RxIfResponse::CoefficientStr)
		return false ;
	float tempCoeff = atof(tempEle->GetText());

	ele = ele->NextSiblingElement();
	if (ele->Name() != RxIfResponse::TemperatureStr)
		return false ;
	Temperature temperature;
	temperature.set(ele->GetText());

	std::shared_ptr<RxIfResponse> rxIfResponse(std::make_shared<RxIfResponse>(path, tempCoeff, temperature.get(), date));
	mRxIfCal->addRxIfResponse(path, rxIfResponse);

	// now we have a list (of one?) offset frequency objects to create
	for (tinyxml2::XMLElement* cur_node =
			ele->NextSiblingElement(); cur_node; cur_node =
			cur_node->NextSiblingElement())
	{
		// Get the device definition inside board
		if (!extractOffsetFrequency(rxIfResponse, cur_node))
			return false;
	}
	// OK we have everything we need for the FrequencyOffset Table
	return true; // we have completed the TxOpenLoop data table
}


//-------------------------------------------------------------------------------------------------------------
bool RxIfCalData::extractOffsetFrequency(std::shared_ptr<RxIfResponse> rxIfResponse, tinyxml2::XMLElement* node)
{
	if (node->Name() != RxIfOffsetFrequency::name)   // is this a PowerBand element?
		return false ;

	tinyxml2::XMLElement* ele = node->FirstChildElement();
	if (ele->Name() != RxIfOffsetFrequency::UpperStr)
		return false ;
	FrequencyOffset upper;
	upper.set(ele->GetText(), FrequencyOffset::KHz);

	ele = ele->NextSiblingElement();
	if (ele->Name() != RxIfOffsetFrequency::LowerStr)
		return false ;
	FrequencyOffset lower;
	lower.set(ele->GetText(), FrequencyOffset::KHz);

	std::shared_ptr<RxIfOffsetFrequency> offsetFreq(std::make_shared<RxIfOffsetFrequency>(upper, lower));
	rxIfResponse->addOffsetFrequency(offsetFreq);

	// now we have to add our frequency table
	for (tinyxml2::XMLElement* cur_node =
			ele->NextSiblingElement(); cur_node; cur_node =
			cur_node->NextSiblingElement())
	{
		if (!extractFrequencyOffsetTable(offsetFreq, cur_node))
			return false;
	}

	return true;    // we have completed the power band table OK
}


//-------------------------------------------------------------------------------------------------------------
bool RxIfCalData::extractFrequencyOffsetTable(std::shared_ptr<RxIfOffsetFrequency> offsetFrequencyOffset,
		tinyxml2::XMLElement* node)
{
	if (node->Name() != RxIfFrequencyOffsetTable::name) // is this a FrequencyOffsetTable element?
		return false ;

	std::shared_ptr<RxIfFrequencyOffsetTable> frequencyTable(std::make_shared<RxIfFrequencyOffsetTable>());
	offsetFrequencyOffset->addFrequencyOffsetTable(frequencyTable);

	// now we have to add our power tables to the frequency table.
	for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
			cur_node; cur_node = cur_node->NextSiblingElement())
	{
		// Get the device definition inside board
		if (!extractCalPoints(frequencyTable, cur_node))
			return false;
	}
	return true; // we have completed FrequencyOffset Table OK
}

//-------------------------------------------------------------------------------------------------------------
bool RxIfCalData::extractCalPoints(
        std::shared_ptr<RxIfFrequencyOffsetTable> frequencyTable,
        tinyxml2::XMLElement* node)
{
	if (node->Name() != RxIfFrequencyOffsetTable::PointStr) // is this a Points element?
		return false ;

	tinyxml2::XMLElement* ele = node->FirstChildElement();
	if (ele->Name() != RxIfFrequencyOffsetTable::offsetStr)
		return false ;
	FrequencyOffset freq;
	freq.set(ele->GetText(), FrequencyOffset::KHz);

	ele = ele->NextSiblingElement();
	if (ele->Name() != RxIfFrequencyOffsetTable::gainStr)
		return false ;
	Power gain;
	gain.set(ele->GetText());

	frequencyTable->addRxIfPoint( RxIfPoint(freq, gain) );
	return true;
}

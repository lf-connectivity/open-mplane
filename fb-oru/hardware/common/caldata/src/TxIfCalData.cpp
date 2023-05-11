/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxIfCalData.cpp
 * \brief     <one-line description of file>
 *
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

// Use the ICalDownloadManagement class to get the installed file path
#include "ICalDownloadManagement.h"

#include "TxIfCalData.h"
#include "GlobalTypeDefs.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TxIfCalData::TxIfCalData( std::shared_ptr<ICalDownload> calDownload ):
	CommonCalBase("TxIfCal", "HW"),
	mCalDownload( calDownload ),
	mCalFilePath( calDownload->getInstallFilePath() ),
	mTxIfCal()
{
}

//-------------------------------------------------------------------------------------------------------------
TxIfCalData::~TxIfCalData()
{
}

//-------------------------------------------------------------------------------------------------------------
void TxIfCalData::show()
{
}


//-------------------------------------------------------------------------------------------------------------
ReturnType::State TxIfCalData::load()
{
	ReturnType::State status = ReturnType::RT_OK;

	if( isLoaded() )
	{
		mTxIfCal.reset();  // deference the caldata shared pointer so that it gets deleted
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

	if (!parseTxIfCal(root_element))
	{
		eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
		return ReturnType::RT_SYNTAX_ERROR;
	}
	setLoaded(true);
	return status;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITxIfResponse> TxIfCalData::getTxIfResponse(int path)
{
	return mTxIfCal->getTxIfResponse(path);
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void TxIfCalData::getAttributeMap(tinyxml2::XMLElement* node, AttrMap& attrMap) const
{
	for (auto& entry : attrMap)
	{
		const char* attr(node->Attribute(entry.first.c_str()));
		if (attr)
			entry.second = std::string(attr);
	}
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<TxIfCal> TxIfCalData::createTxIfCal(
		const std::string& version, const std::string& country,
		const std::string& facility, const std::string& theoperator)
{
	return std::make_shared<TxIfCal>(version, country, facility, theoperator) ;
}


//-------------------------------------------------------------------------------------------------------------
bool TxIfCalData::parseTxIfCal(tinyxml2::XMLElement* node)
{

	if (node->Name() != TxIfCal::name) // is the first element the correct element?
		return false ;

	AttrMap attributes;
	attributes["version"] = "";
	attributes["country"] = "";
	attributes["facility"] = "";
	attributes["operator"] = "";
	getAttributeMap(node, attributes);

	mTxIfCal = createTxIfCal(attributes["version"], attributes["country"],
					attributes["facility"], attributes["operator"]);

	for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
			cur_node; cur_node = cur_node->NextSiblingElement())
	{
		// Get the device definition inside board
		if (!extractTxIfResponse(mTxIfCal, cur_node))
			return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool TxIfCalData::extractTxIfResponse(std::shared_ptr<TxIfCal> mTxIfCal, tinyxml2::XMLElement* node)
{
	if (node->Name() != TxIfResponse::name)    // is the The TxOpenLoop element?
		return false ;

	tinyxml2::XMLElement* ele = node->FirstChildElement();

	if (ele->Name() != TxIfResponse::PathStr)
		return false ;

	int path = atoi(ele->GetText());
	ele = ele->NextSiblingElement();
	std::string date = "";
	if (ele->Name() != TxIfResponse::DateStr)
		return false ;
	date = ele->GetText();

	mCalDownload->addPath(path, date) ;

	ele = ele->NextSiblingElement();
	if (ele->Name() != TxIfResponse::TemperatureStr)
		return false ;
	Temperature temperature;
	temperature.set(ele->GetText());

	std::shared_ptr<TxIfResponse> txIfResponse(std::make_shared<TxIfResponse>(path, temperature.get(), date));
	mTxIfCal->addTxIfResponse(path, txIfResponse);

	// now we have a list (of one?) offset frequency objects to create
	for (tinyxml2::XMLElement* cur_node =
			ele->NextSiblingElement(); cur_node; cur_node =
			cur_node->NextSiblingElement())
	{
		// Get the device definition inside board
		if (!extractOffsetFrequency(txIfResponse, cur_node))
			return false;
	}
	// OK we have everything we need for the FrequencyOffset Table
	return true; // we have completed the TxOpenLoop data table
}


//-------------------------------------------------------------------------------------------------------------
bool TxIfCalData::extractOffsetFrequency(std::shared_ptr<TxIfResponse> txIfResponse, tinyxml2::XMLElement* node)
{
	if (node->Name() != TxIfOffsetFrequency::name)   // is this a PowerBand element?
		return false ;

	tinyxml2::XMLElement* ele = node->FirstChildElement();
	if (ele->Name() != TxIfOffsetFrequency::UpperStr)
		return false ;
	FrequencyOffset upper;
	upper.set(ele->GetText(), FrequencyOffset::KHz);

	ele = ele->NextSiblingElement();
	if (ele->Name() != TxIfOffsetFrequency::LowerStr)
		return false ;
	FrequencyOffset lower;
	lower.set(ele->GetText(), FrequencyOffset::KHz);

	std::shared_ptr<TxIfOffsetFrequency> offsetFreq(std::make_shared<TxIfOffsetFrequency>(upper, lower));
	txIfResponse->addOffsetFrequency(offsetFreq);

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
bool TxIfCalData::extractFrequencyOffsetTable(std::shared_ptr<TxIfOffsetFrequency> offsetFrequencyOffset,
		tinyxml2::XMLElement* node)
{
	if (node->Name() != TxIfFrequencyOffsetTable::name) // is this a FrequencyOffsetTable element?
		return false ;

	std::shared_ptr<TxIfFrequencyOffsetTable> frequencyTable(std::make_shared<TxIfFrequencyOffsetTable>());
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
bool TxIfCalData::extractCalPoints(
		std::shared_ptr<TxIfFrequencyOffsetTable> frequencyTable,
		tinyxml2::XMLElement* node)
{
	if (node->Name() != TxIfFrequencyOffsetTable::PointStr) // is this a Points element?
		return false ;

	tinyxml2::XMLElement* ele = node->FirstChildElement();
	if (ele->Name() != TxIfFrequencyOffsetTable::offsetStr)
		return false ;
	FrequencyOffset freq;
	freq.set(ele->GetText(), FrequencyOffset::KHz);

	ele = ele->NextSiblingElement();
	if (ele->Name() != TxIfFrequencyOffsetTable::gainStr)
		return false ;
	Power gain;
	gain.set(ele->GetText());

	frequencyTable->addTxIfPoint( TxIfPoint(freq, gain) );
	return true;
}

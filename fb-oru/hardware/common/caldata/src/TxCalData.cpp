/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxCalData.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Maths.h"

// Use the ICalDownloadManagement class to get the installed file path
#include "ICalDownloadManagement.h"

#include "ICalDownload.h"
#include "TxCalData.h"
#include "GlobalTypeDefs.h"
#include "TxCal.h"
#include "Frequency.h"
#include "Power.h"
#include <memory>

using namespace Mplane;

Mplane::TxCalData::TxCalData(  std::shared_ptr<ICalDownload> calDownload ) :
	CommonCalBase("TxCal", "HW"),
	mCalDownload( calDownload ),
	mCalFilePath( calDownload->getInstallFilePath() ),
	mTxCal(0)
{

}

Mplane::TxCalData::~TxCalData()
{
}

void Mplane::TxCalData::show()
{
}

ReturnType::State Mplane::TxCalData::load()
{
    ReturnType::State status = ReturnType::RT_OK;

    mCalFilePath = mCalDownload->getInstallFilePath();  // need this here to allow unit tests to modify dir to a test dir

    if( isLoaded() )
    {
        mTxCal = 0; // dereference the shared pointer so that the cal data is cleared.
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

    if( !parseTxCal(root_element) )
    {
        eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
        return ReturnType::RT_SYNTAX_ERROR;
    }

    setLoaded( true );
    return status;
}

bool Mplane::TxCalData::parseTxCal(tinyxml2::XMLElement* node)
{
    if (node->Name() == TxCal::name) // is the first element the correct element?
    {
        AttrMap attributes;
        attributes["version"] = "";
        attributes["country"] = "";
        attributes["facility"] = "";
        attributes["operator"] = "";
        getAttributeMap(node, attributes);

        std::shared_ptr<TxCal> ftuTxCal(
                new TxCal(attributes["version"], attributes["country"],
                        attributes["facility"], attributes["operator"]));

        mTxCal = ftuTxCal;

        for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
                cur_node; cur_node = cur_node->NextSiblingElement())
        {
            // Get the device definition inside board
            if (!extractTxOpenLoop(mTxCal, cur_node))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Mplane::TxCalData::extractTxOpenLoop(std::shared_ptr<TxCal> mTxCal, tinyxml2::XMLElement* node)
{
    if (node->Name() == TxOpenLoop::name)    // is the The TxOpenLoop element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();

        if (ele->Name() == TxOpenLoop::PathStr)
        {
            int path = atoi(ele->GetText());
            ele = ele->NextSiblingElement();
            std::string date = "";
            if (ele->Name() == TxOpenLoop::DateStr)
            {
                date = ele->GetText();
                ele = ele->NextSiblingElement();

                mCalDownload->addPath(path, date) ;

                if (ele->Name() == TxOpenLoop::LinearTemperatureCompensation)
                {
                    tinyxml2::XMLElement* tempEle = ele->FirstChildElement();
                    if (tempEle->Name() == TxOpenLoop::CoefficientStr)
                    {
                        float tempCoeff = Maths::char2float(tempEle->GetText());
                        std::shared_ptr<TxOpenLoop> txOpenLoop(
                                new TxOpenLoop(path, tempCoeff, date ));

                        mTxCal->addTxOpenLoop( path, txOpenLoop );

                        // now we have a list of Frequency Table elements to create.
                        for (tinyxml2::XMLElement* cur_node =
                                ele->NextSiblingElement(); cur_node; cur_node =
                                cur_node->NextSiblingElement())
                        {
                            // Get the device definition inside board
                            if (!extractFrequecnyTable(txOpenLoop, cur_node))
                            {
                                return false;
                            }
                        }
                        // OK we have everything we need for the Frequency Table
                        return true; // we have completed the TxOpenLoop data table
                    }
                }
            }
        }
    }
    return false;
}

bool Mplane::TxCalData::extractFrequecnyTable(
        std::shared_ptr<TxOpenLoop> txOpenLoop, tinyxml2::XMLElement* node)
{
    if (node->Name() == FrequencyTable::name) // is this a FrequencyTable element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        Frequency frequency(0.0);
        if (ele->Name() == FrequencyTable::FrequencyStr)
        {
            bool haveCoefficient = false;
            frequency.set(ele->GetText(), Frequency::KHz);
            float coefficient = 0.0f;
            tinyxml2::XMLElement* coeff =  ele->NextSiblingElement( FrequencyTable::CoefficientStr.c_str() );
            if( coeff )
            {
                haveCoefficient = true;
                coefficient = Maths::char2float(coeff->GetText());
                ele = coeff;
            }

            std::shared_ptr<FrequencyTable> frequencyTable(
                    new FrequencyTable(frequency,haveCoefficient, coefficient));

            txOpenLoop->addFrequencyTable( frequencyTable );

            // now we have to add our power tables to the frequency table.
            for (tinyxml2::XMLElement* cur_node = ele->NextSiblingElement();
                    cur_node; cur_node = cur_node->NextSiblingElement())
            {
                // Get the device definition inside board
                if (!extractPowerBand(frequencyTable, cur_node))
                {
                    return false;
                }
            }
            return true; // we have completed Frequency Table OK
        }

    }
    return false;
}

bool Mplane::TxCalData::extractPowerBand(
        std::shared_ptr<FrequencyTable> frequencyTable,
        tinyxml2::XMLElement* node)
{
    if (node->Name() == PowerBand::name)    // is this a PowerBand element?
    {

        tinyxml2::XMLElement* ele = node->FirstChildElement();
        if (ele->Name() == PowerBand::UpperStr )
        {
            Power upper;
            upper.set( ele->GetText() );
            ele = ele->NextSiblingElement();
            if (ele->Name() == PowerBand::LowerStr)
            {
                Power lower;
                lower.set( ele->GetText() );
                ele = ele->NextSiblingElement();
                if (ele->Name() == PowerBand::BBStr)
                {
                    Power baseBand;
                    baseBand.set( ele->GetText() );
                    ele = ele->NextSiblingElement();
					if (ele->Name() == PowerBand::TemperatureStr)
					{
						Temperature temperature;
						temperature.set( ele->GetText() );

						std::shared_ptr<PowerBand> powerBand( new PowerBand( upper, lower,
								baseBand, temperature.get() ));
						frequencyTable->addPowerBand( powerBand );
						// now we have to add our power tables to the frequency table.
						for (tinyxml2::XMLElement* cur_node = ele->NextSiblingElement();
								cur_node; cur_node = cur_node->NextSiblingElement())
						{
							// now we extract the variable attenuation value and add them
							// as cal points, they may be IF or RF attenuation values.
							if (!extractCalPoints(powerBand, cur_node))
							{
								return false;
							}
						}
						return true;    // we have completed the power band table OK
					}
                }
            }
        }
    }

    return false;
}

bool Mplane::TxCalData::extractCalPoints( std::shared_ptr<PowerBand> powerBand, tinyxml2::XMLElement* node)
{
	if (node->Name() != PowerBand::PointStr)    // is this a Points element?
		return false;

	tinyxml2::XMLElement* ele = node->FirstChildElement();
	if (ele->Name() != PowerBand::PowerStr )
		return false;

	const char* powerVal(ele->GetText()) ;
	ele = ele->NextSiblingElement();

	//
	// If we are loading an old style cal file, the variable DSA value is the
	// IF attenuator but the new style cal can support fixed RF and variable IF or
	// fixed IF and variable IF. That's why we are checking for both string names in the
	// element.
	//
	const char* name(ele->Name()) ;
	if ( name != PowerBand::RFAttenStr )
		return false;

	const char* dsaVal(ele->GetText()) ;

	Point point;

	if (powerVal)
		point.power.set(powerVal);

	if (dsaVal)
		point.varDsa.set(dsaVal);

	powerBand->addPointPower( point );   // the the cal point pair to the map table

	return true;
}


void Mplane::TxCalData::getAttributeMap(tinyxml2::XMLElement* node,
        AttrMap& attrMap) const
{

    for (AttrMapIterator iter(attrMap.begin()); iter != attrMap.end(); ++iter)
    {
        const char* attr(node->Attribute(iter->first.c_str()));
        if (attr)
        {
            iter->second = std::string(attr);
        }
    }

}

std::shared_ptr<ITxOpenLoop> Mplane::TxCalData::getTxOpenLoop(int path)
{
    return mTxCal->getTxOpenLoop( path );
}

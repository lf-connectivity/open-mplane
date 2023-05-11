/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PamCalData.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

// Use the ICalDownloadManagement class to get the installed file path
#include "PamCalData.h"

#include "ICalDownloadManagement.h"

#include "ICalDownload.h"
#include "GlobalTypeDefs.h"
#include "Frequency.h"
#include "Power.h"
#include <memory>
#include "PamCal.h"

using namespace Mplane;

Mplane::PamCalData::PamCalData( std::shared_ptr<ICalDownload> calDownload ) :
	CommonCalBase("PamCal", "HW"),
    mCalDownload( calDownload ),
	mCalFilePath( calDownload->getInstallFilePath() ),
	mPamCal(0)
{

}

Mplane::PamCalData::~PamCalData()
{
}

void Mplane::PamCalData::show()
{
}

ReturnType::State Mplane::PamCalData::load()
{
    ReturnType::State status = ReturnType::RT_OK;

    mCalFilePath = mCalDownload->getInstallFilePath();  // need this here to allow unit tests to modify dir to a test dir

    if( isLoaded() )
    {
        mPamCal = 0; // dereference the shared pointer so that the cal data is cleared.
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

    if( !parsePamCal(root_element) )
    {
        eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
        return ReturnType::RT_SYNTAX_ERROR;
    }
    setLoaded( true );
    return status;
}

bool Mplane::PamCalData::parsePamCal(tinyxml2::XMLElement* node)
{
    if (node->Name() == PamCal::name) // is the first element the correct element?
    {
        AttrMap attributes;
        attributes["version"] = "";
        attributes["country"] = "";
        attributes["facility"] = "";
        attributes["operator"] = "";
        getAttributeMap(node, attributes);

        std::shared_ptr<PamCal> atgPamCal(
                new PamCal(attributes["version"], attributes["country"],
                        attributes["facility"], attributes["operator"]));

        mPamCal = atgPamCal;

        for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
                cur_node; cur_node = cur_node->NextSiblingElement())
        {
            // Get the device definition inside board
            if (!extractPaGainStep(mPamCal, cur_node))
            {
                return false;
            }
        }
        return true;
    }
    return false;  // the wrong node name, do nothing
}

bool Mplane::PamCalData::extractPaGainStep(std::shared_ptr<PamCal> pamCal,
		                                    tinyxml2::XMLElement* node)
{
    if (node->Name() == PaGainStep::name)    // check this is the PaGainStep element
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();

        if (ele->Name() == PaGainStep::PathStr)
        {
            int path = atoi(ele->GetText());
            ele = ele->NextSiblingElement();
            std::string date = "";
            if (ele->Name() == PaGainStep::DateStr)
            {
                date = ele->GetText();
                ele = ele->NextSiblingElement();

                mCalDownload->addPath(path, date) ;

                if (ele->Name() == PaGainStep::LinearTemperatureCompensationStr)
                {
                    tinyxml2::XMLElement* tempEle = ele->FirstChildElement();
                    if (tempEle->Name() == PaGainStep::StepCoefficientStr)
                    {
                        float tempStepCoeff = atof(tempEle->GetText());
                        tempEle = tempEle->NextSiblingElement();

                        if (tempEle->Name() == PaGainStep::CoefficientStr)
                        {
                            float tempCoeff = atof(tempEle->GetText());
                            std::shared_ptr<PaGainStep> paGainStep(
                            		new PaGainStep(path, tempStepCoeff, tempCoeff, date ));

                            pamCal->addPaGainStep( path, paGainStep );

                            // now we have a list of Frequency Table elements to create.
                            for (tinyxml2::XMLElement* cur_node =
                            		ele->NextSiblingElement(); cur_node; cur_node =
                            				cur_node->NextSiblingElement())
                            {
                            	// Get the device definition inside board
                            	if (!extractFrequencyTable(paGainStep, cur_node))
                            	{
                            		return false;
                            	}
                            }
                            // OK we have everything we need for the Frequency Table
                            return true; // we have completed the PaGainStep data table
                        }
                    }
                }
            }
        }
    }
    return false;  // the wrong node name, do nothing
}

bool Mplane::PamCalData::extractFrequencyTable(
		std::shared_ptr<PaGainStep> paGainStep, tinyxml2::XMLElement* node)
{
    if (node->Name() == PgsFrequencyTable::name)
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        Frequency frequency(0.0);
        if (ele->Name() == PgsFrequencyTable::FrequencyStr)
        {
            frequency.set(ele->GetText(), Frequency::KHz);
        	std::shared_ptr<PgsFrequencyTable> frequencyTable(
        			new PgsFrequencyTable(frequency) );

        	paGainStep->addFrequencyTable( frequencyTable );

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

        }  // not frequency name, do nothing
    }  // the wrong table name, do nothing
    return false;
}

bool Mplane::PamCalData::extractPowerBand(
        std::shared_ptr<PgsFrequencyTable> frequencyTable,
		tinyxml2::XMLElement* node)
{
    if (node->Name() == PgsPowerBand::name)    // is this a PowerBand element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        if (ele->Name() == PgsPowerBand::RadioTemperatureStr)
        {
        	Temperature radioTemperature;
        	radioTemperature.set( ele->GetText() );
        	ele = ele->NextSiblingElement();
        	if (ele->Name() == PgsPowerBand::PamTemperatureStr)
        	{
        		Temperature pamTemperature;
        		pamTemperature.set( ele->GetText() );
        		ele = ele->NextSiblingElement();
        		if (ele->Name() == PgsPowerBand::VvaPwmStr)
        		{
        			unsigned int vvaPwm;
        			vvaPwm = atoi( ele->GetText() );
        			ele = ele->NextSiblingElement();
        			if (ele->Name() == PgsPowerBand::LowGainOutputPowerStr)
        			{
        				Power lowGainOutputPower;
        				lowGainOutputPower.set( ele->GetText() );
        				ele = ele->NextSiblingElement();
        				if (ele->Name() == PgsPowerBand::HighGainOutputPowerStr)
        				{
        					Power highGainOutputPower;
        					highGainOutputPower.set( ele->GetText() );

                            std::shared_ptr<PgsPowerBand> powerBand( new PgsPowerBand( radioTemperature.get(), pamTemperature.get(),
        									vvaPwm, lowGainOutputPower, highGainOutputPower) );

                            frequencyTable->addPgsPowerBand( powerBand );

        					return true; // we have completed a PowerBand Table OK
        				}  // not high gain output power name, do nothing
        			}  // not low gain output power name, do nothing
        		}  // not vva pwm name, do nothing
        	}  // not pam temperature name, do nothing
        }  // not radio temperature name, do nothing
    }  // the wrong table name, do nothing
    return false;
}

void Mplane::PamCalData::getAttributeMap(tinyxml2::XMLElement* node,
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

std::shared_ptr<IPaGainStep> Mplane::PamCalData::getPaGainStep(int path)
{
    return mPamCal->getPaGainStep( path );
}

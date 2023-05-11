/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SwrCalData.cpp
 * \brief     Load reverse path power cal data from file
 *
 *
 * \details   Load reverse path power cal data from file
 *
 */

// Use the ICalDownloadManagement class to get the installed file path
#include "ICalDownloadManagement.h"

#include "SwrCalData.h"
#include "GlobalTypeDefs.h"

using namespace Mplane;

Mplane::SwrCalData::SwrCalData( std::shared_ptr<ICalDownload> calDownload ):
	CommonCalBase("SRxCal", "HW"),
    mCalDownload( calDownload ),
	mCalFilePath( calDownload->getInstallFilePath() )
{
}

Mplane::SwrCalData::~SwrCalData()
{
}

void Mplane::SwrCalData::show()
{
}


ReturnType::State Mplane::SwrCalData::load()
{
    ReturnType::State status = ReturnType::RT_OK;

    mCalFilePath = mCalDownload->getInstallFilePath();  // need this here to allow unit tests to modify dir to a test dir

    if( isLoaded() )
    {
        mSwrCal = 0;  // deference the caldata shared pointer so that it gets deleted
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

    if (!parseSwrCal(root_element))
    {
        eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
        return ReturnType::RT_SYNTAX_ERROR;
    }
    setLoaded(true);
    return status;
}

std::shared_ptr<ISwrOpenLoop> Mplane::SwrCalData::getSwrOpenLoop(int path)
{
    return mSwrCal->getSwrOpenLoop(path);
}

bool Mplane::SwrCalData::parseSwrCal(tinyxml2::XMLElement* node)
{

    if (node->Name() == SwrCal::name) // is the first element the correct element?
    {
        AttrMap attributes;
        attributes["version"] = "";
        attributes["country"] = "";
        attributes["facility"] = "";
        attributes["operator"] = "";
        getAttributeMap(node, attributes);

        std::shared_ptr<SwrCal> sWrCal(
                new SwrCal(attributes["version"], attributes["country"],
                        attributes["facility"], attributes["operator"]));

        mSwrCal = sWrCal;

        for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
                cur_node; cur_node = cur_node->NextSiblingElement())
        {
            // Get the device definition inside board
            if (!extractSwrOpenLoop(mSwrCal, cur_node))
            {
                return false;
            }
        }
        return true;
    }
    return false;

}

bool Mplane::SwrCalData::extractSwrOpenLoop(
        std::shared_ptr<SwrCal> mSwrCal, tinyxml2::XMLElement* node)
{
    if (node->Name() == SwrOpenLoop::name)    // is the The TxOpenLoop element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();

        if (ele->Name() == SwrOpenLoop::PathStr)
        {
            int path = atoi(ele->GetText());
            ele = ele->NextSiblingElement();
            std::string date = "";
            if (ele->Name() == SwrOpenLoop::DateStr)
            {
                date = ele->GetText();
                ele = ele->NextSiblingElement();

                mCalDownload->addPath(path, date) ;

                if (ele->Name() == SwrOpenLoop::LinearTemperatureCompensation)
                {
                    tinyxml2::XMLElement* tempEle = ele->FirstChildElement();
                    if (tempEle->Name() == SwrOpenLoop::CoefficientStr)
                    {
                        float tempCoeff = atof(tempEle->GetText());
                        std::shared_ptr<SwrOpenLoop> swrOpenLoop(
                                new SwrOpenLoop(path, tempCoeff, date));

                        mSwrCal->addSwrOpenLoop(path, swrOpenLoop);

                        // now we have a list of Frequency Table elements to create.
                        for (tinyxml2::XMLElement* cur_node =
                                ele->NextSiblingElement(); cur_node; cur_node =
                                cur_node->NextSiblingElement())
                        {
                            // Get the device definition inside board
                            if (!extractFrequencyBand(swrOpenLoop, cur_node))
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

bool Mplane::SwrCalData::extractFrequencyBand(
        std::shared_ptr<SwrOpenLoop> swrOpenLoop, tinyxml2::XMLElement* node)
{
    if (node->Name() == SwrFrequencyBand::name)   // is this a PowerBand element?
    {

        tinyxml2::XMLElement* ele = node->FirstChildElement();
        if (ele->Name() == SwrFrequencyBand::UpperStr)
        {
            Frequency upper;
            upper.set(ele->GetText(), Frequency::KHz);
            ele = ele->NextSiblingElement();
            if (ele->Name() == SwrFrequencyBand::LowerStr)
            {
                Frequency lower;
                lower.set(ele->GetText(), Frequency::KHz);

                std::shared_ptr<SwrFrequencyBand> freqBand(
                        new SwrFrequencyBand(upper, lower));
                swrOpenLoop->addFrequencyBand(freqBand);
                // now we have to add our power tables to the frequency table.
                for (tinyxml2::XMLElement* cur_node =
                        ele->NextSiblingElement(); cur_node; cur_node =
                                cur_node->NextSiblingElement())
                {
                    // Get the device definition inside board
                    if (!extractFrequencyTable(freqBand, cur_node))
                    {
                        return false;
                    }
                }
                return true;    // we have completed the power band table OK
            }
        }
    }

    return false;

}

bool Mplane::SwrCalData::extractFrequencyTable(
        std::shared_ptr<SwrFrequencyBand> frequencyBand,
        tinyxml2::XMLElement* node)
{
    if (node->Name() == SwrFrequencyTable::name) // is this a FrequencyTable element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        Frequency frequency(0.0);
        if (ele->Name() == SwrFrequencyTable::FrequencyStr)
        {
            frequency.set(ele->GetText(), Frequency::KHz);

            ele = ele->NextSiblingElement();
            if (ele->Name() == SwrFrequencyTable::TemperatureStr)
            {
                Temperature temperature;
                temperature.set(ele->GetText());

                std::shared_ptr<SwrFrequencyTable> frequencyTable(
                        new SwrFrequencyTable(frequency, temperature.get()));

                frequencyBand->addFrequencyTable(frequencyTable);

                // now we have to add our power tables to the frequency table.
                for (tinyxml2::XMLElement* cur_node = ele->NextSiblingElement();
                        cur_node; cur_node = cur_node->NextSiblingElement())
                {
                    // Get the device definition inside board
                    if (!extractCalPoints(frequencyTable, cur_node))
                    {
                        return false;
                    }
                }
                return true; // we have completed Frequency Table OK
            }
        }

    }
    return false;

}

bool Mplane::SwrCalData::extractCalPoints(
        std::shared_ptr<SwrFrequencyTable> frequencyTable,
        tinyxml2::XMLElement* node)
{
    if (node->Name() == SwrFrequencyTable::PointStr) // is this a Points element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        if (ele->Name() == SwrFrequencyTable::rfDSAStr)
        {
            Power rfDsa;
            if( ele->GetText() != nullptr )
            {
                rfDsa.set(ele->GetText());
            }
            ele = ele->NextSiblingElement();
            if (ele->Name() == SwrFrequencyTable::dBFS2dBmStr)
            {
                Power dBfs2dBm;
                if( ele->GetText() != nullptr )
                {
                    dBfs2dBm.set(ele->GetText());
                }
                SwrPoint point;
                point.rfDSA = rfDsa;
                point.dBFS2dBm = dBfs2dBm;
                frequencyTable->addPoint(point);
                return true;
            }
        }
    }
    return false;

}

void Mplane::SwrCalData::getAttributeMap(tinyxml2::XMLElement* node,
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

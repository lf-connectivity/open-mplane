/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SRxCalData.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

// Use the ICalDownloadManagement class to get the installed file path
#include "ICalDownloadManagement.h"

#include "SRxCalData.h"
#include "GlobalTypeDefs.h"
#include "Maths.h"

using namespace Mplane;

Mplane::SRxCalData::SRxCalData( std::shared_ptr<ICalDownload> calDownload ):
	CommonCalBase("SRxCal", "HW"),
	mCalDownload( calDownload ),
	mCalFilePath( calDownload->getInstallFilePath() )
{
}

Mplane::SRxCalData::~SRxCalData()
{
}

void Mplane::SRxCalData::show()
{
}


ReturnType::State Mplane::SRxCalData::load()
{
    ReturnType::State status = ReturnType::RT_OK;

    mCalFilePath = mCalDownload->getInstallFilePath();  // need this here to allow unit tests to modify dir to a test dir

    if( isLoaded() )
    {
        mSRxCal = 0;  // deference the caldata shared pointer so that it gets deleted

        mFirstTempPath.clear();

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

    if (!parseSRxCal(root_element))
    {
        eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
        return ReturnType::RT_SYNTAX_ERROR;
    }
    setLoaded(true);
    return status;
}

std::shared_ptr<ISRxOpenLoop> Mplane::SRxCalData::getSRxOpenLoop(int path)
{
    return mSRxCal->getSRxOpenLoop(path);
}

bool Mplane::SRxCalData::parseSRxCal(tinyxml2::XMLElement* node)
{

    if (node->Name() == SRxCal::name) // is the first element the correct element?
    {
        AttrMap attributes;
        attributes["version"] = "";
        attributes["country"] = "";
        attributes["facility"] = "";
        attributes["operator"] = "";
        getAttributeMap(node, attributes);

        std::shared_ptr<SRxCal> sRxCal(
                new SRxCal(attributes["version"], attributes["country"],
                        attributes["facility"], attributes["operator"]));

        mSRxCal = sRxCal;

        for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
                cur_node; cur_node = cur_node->NextSiblingElement())
        {
            // Get the device definition inside board
            if (!extractSRxOpenLoop(mSRxCal, cur_node))
            {
                return false;
            }
        }
        return true;
    }
    return false;

}

bool Mplane::SRxCalData::extractSRxOpenLoop(
        std::shared_ptr<SRxCal> mSRxCal, tinyxml2::XMLElement* node)
{
    if (node->Name() == SRxOpenLoop::name)    // is the The TxOpenLoop element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();

        if (ele->Name() == SRxOpenLoop::PathStr)
        {
        	mCalPath = atoi(ele->GetText());
            ele = ele->NextSiblingElement();
            std::string date = "";
            if (ele->Name() == SRxOpenLoop::DateStr)
            {
                date = ele->GetText();
                ele = ele->NextSiblingElement();

                mCalDownload->addPath(mCalPath, date) ;

                // We need to extract the first temperature for each path
                mFirstTempPath.push_back(true);

                if (ele->Name() == SRxOpenLoop::LinearTemperatureCompensation)
                {
                    tinyxml2::XMLElement* tempEle = ele->FirstChildElement();
                    if (tempEle->Name() == SRxOpenLoop::CoefficientStr)
                    {
                        float tempCoeff = Maths::char2float(tempEle->GetText());
                        std::shared_ptr<SRxOpenLoop> srxOpenLoop(
                                new SRxOpenLoop(mCalPath, tempCoeff, date));

                        mSRxCal->addSRxOpenLoop(mCalPath, srxOpenLoop);

                        // now we have a list of Frequency Table elements to create.
                        for (tinyxml2::XMLElement* cur_node =
                                ele->NextSiblingElement(); cur_node; cur_node =
                                cur_node->NextSiblingElement())
                        {
                            // Get the device definition inside board
                            if (!extractFrequencyBand(srxOpenLoop, cur_node))
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

bool Mplane::SRxCalData::extractFrequencyBand(
        std::shared_ptr<SRxOpenLoop> rxOpenLoop, tinyxml2::XMLElement* node)
{
    if (node->Name() == SRxFrequencyBand::name)   // is this a PowerBand element?
    {

        tinyxml2::XMLElement* ele = node->FirstChildElement();
        if (ele->Name() == SRxFrequencyBand::UpperStr)
        {
            Frequency upper;
            upper.set(ele->GetText(), Frequency::KHz);
            ele = ele->NextSiblingElement();
            if (ele->Name() == SRxFrequencyBand::LowerStr)
            {
                Frequency lower;
                lower.set(ele->GetText(), Frequency::KHz);

                std::shared_ptr<SRxFrequencyBand> freqBand(
                        new SRxFrequencyBand(upper, lower));
                rxOpenLoop->addFrequencyBand(freqBand);
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

bool Mplane::SRxCalData::extractFrequencyTable(
        std::shared_ptr<SRxFrequencyBand> frequencyBand,
        tinyxml2::XMLElement* node)
{
    if (node->Name() == SRxFrequencyTable::name) // is this a FrequencyTable element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        Frequency frequency(0.0);
        if (ele->Name() == SRxFrequencyTable::FrequencyStr)
        {
            frequency.set(ele->GetText(), Frequency::KHz);

            ele = ele->NextSiblingElement();
            if (ele->Name() == SRxFrequencyTable::TemperatureStr)
            {
                Temperature temperature;
                temperature.set(ele->GetText());

                if(true == mFirstTempPath[mCalPath-1])
                {
                	mCalDownload->addTemperature(mCalPath, temperature.get());

                	mFirstTempPath[mCalPath-1] = false;
                }

                std::shared_ptr<SRxFrequencyTable> frequencyTable(
                        new SRxFrequencyTable(frequency, temperature.get()));

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

bool Mplane::SRxCalData::extractCalPoints(
        std::shared_ptr<SRxFrequencyTable> frequencyTable,
        tinyxml2::XMLElement* node)
{
	if (node->Name() != SRxFrequencyTable::PointStr) // is this a Points element?
		return false;

	tinyxml2::XMLElement* ele = node->FirstChildElement();
	if (ele->Name() != SRxFrequencyTable::rfDSAStr)
		return false;

	const char* dsaVal(ele->GetText()) ;
	ele = ele->NextSiblingElement();

	if (ele->Name() != SRxFrequencyTable::dBFS2dBmStr)
		return false;

	const char* dbfsVal(ele->GetText()) ;

	SRxPoint point;

	if (dsaVal)
		point.rfDSA.set(dsaVal);

	if (dbfsVal)
		point.dBFS2dBm.set(dbfsVal) ;

	frequencyTable->addPoint(point);
	return true;
}

void Mplane::SRxCalData::getAttributeMap(tinyxml2::XMLElement* node,
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

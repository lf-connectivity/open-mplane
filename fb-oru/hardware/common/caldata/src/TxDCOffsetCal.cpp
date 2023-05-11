/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxDCOffsetCal.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "ICalDownloadManagement.h"


#include "TxDCOffsetCal.h"
#include <map>
#include <memory>


using namespace Mplane;

const std::string TxDCOffsetFrequency::name = "FrequencyTable";
const std::string TxDCOffsetFrequency::FrequencyStr = "Frequency";
const std::string TxDCOffsetFrequency::TemperatureStr = "Temperature";
const std::string TxDCOffsetFrequency::IDCOffsetStr = "DCI";
const std::string TxDCOffsetFrequency::QDCOffsetStr = "DCQ";



const std::string Mplane::TxDCOffset::name = "TxDcOffset";
const std::string Mplane::TxDCOffset::PathStr = "Path";
const std::string Mplane::TxDCOffset::DateStr = "Date" ;


void Mplane::TxDCOffset::addFrequencyTable(   std::shared_ptr<TxDCOffsetFrequency> frequencyTable)
{
    mFrequencyTables.push_back( frequencyTable );
}


bool Mplane::TxDCOffset::getIQOffsets(Frequency frequency, float &temperature,
        int& iDCOffset, int& qDCOffset)
{
    std::shared_ptr<TxDCOffsetFrequency> freqTable;

     if ( findFrequency( frequency , freqTable ))    // is the frequency in the cal data
     {
         iDCOffset = freqTable->getIDCOffset();
         qDCOffset = freqTable->getQDCOffset();
         temperature = freqTable->getTemperature();
         return true;
     }
     return  false;

}

bool Mplane::TxDCOffset::findFrequency(Frequency freq,   std::shared_ptr<TxDCOffsetFrequency>& frequencyTable)
{
    int count = 0;
    std::shared_ptr<TxDCOffsetFrequency> previous  = *(mFrequencyTables.begin());
    for( std::list<std::shared_ptr<TxDCOffsetFrequency>>::iterator it = mFrequencyTables.begin();
            it != mFrequencyTables.end(); ++it, ++count )
    {
        if( (*it)->getFrequency() == freq )
        {
            frequencyTable = (*it);
            return true;
        }
        if( count )
        {
            if( freq > previous->getFrequency() && freq < (*it)->getFrequency() )
            {
                if( freq < (previous->getFrequency()+
                        (((*it)->getFrequency() - previous->getFrequency() ) /2)  ))
                {
                    frequencyTable = previous;
                }
                else
                {
                    frequencyTable = (*it);
                }
                return true;
            }
        }
        else if( freq < (*it)->getFrequency() )
        {
            frequencyTable = (*it);
            return true;
        }
        previous = (*it);
    }
    frequencyTable = previous;
    return true;
}

const std::string Mplane::TxDCOffsetCal::name = "TxDcOffsetCalibration";

std::shared_ptr<TxDCOffset> Mplane::TxDCOffsetCal::getTxDCOffset(int path)
{
    return mTxDCOffsetData[ path ];
}

void Mplane::TxDCOffsetCal::addTxDCOffset(int path,  std::shared_ptr<TxDCOffset> txDCOffset)
{
    mTxDCOffsetData[path] = txDCOffset;

}

Mplane::TxDCOffsetCalData::TxDCOffsetCalData( std::shared_ptr<ICalDownload> calDownload ):
            CommonCalBase("TxDCOffsetCal", "HW"),
            mCalDownload( calDownload ),
            mCalFilePath( calDownload->getInstallFilePath() ),
            mTxDCOffsetCal(0)
{
}

Mplane::TxDCOffsetCalData::~TxDCOffsetCalData()
{
}

void Mplane::TxDCOffsetCalData::show()
{
}

ReturnType::State Mplane::TxDCOffsetCalData::load()
{
    ReturnType::State status = ReturnType::RT_OK;

    if( isLoaded() )
    {
        mTxDCOffsetCal = 0; // dereference the shared pointer so that the cal data is cleared.
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

    if( !parseTxDCOffsetCal(root_element) )
    {
        eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
        return ReturnType::RT_SYNTAX_ERROR;
    }
    setLoaded( true );
    return status;

}

std::shared_ptr<TxDCOffset> Mplane::TxDCOffsetCalData::getTxDCOffset(int path)
{
    return mTxDCOffsetCal->getTxDCOffset( path );
}

bool Mplane::TxDCOffsetCalData::parseTxDCOffsetCal(tinyxml2::XMLElement* node)
{
    if (node->Name() == TxDCOffsetCal::name) // is the first element the correct element?
    {
        AttrMap attributes;
        attributes["version"] = "";
        attributes["country"] = "";
        attributes["facility"] = "";
        attributes["operator"] = "";
        getAttributeMap(node, attributes);

        std::shared_ptr<TxDCOffsetCal> txDCOffsetCal( new TxDCOffsetCal(attributes["version"], attributes["country"],
                        attributes["facility"], attributes["operator"]));

        mTxDCOffsetCal = txDCOffsetCal;

        for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
                cur_node; cur_node = cur_node->NextSiblingElement())
        {
            // Get the device definition inside board
            if (!extractTxDCOffset(mTxDCOffsetCal, cur_node))
            {
                return false;
            }
        }
        return true;
    }
    return false;

}

bool Mplane::TxDCOffsetCalData::extractTxDCOffset( std::shared_ptr<TxDCOffsetCal> txDCOffsetCal,
                                                                tinyxml2::XMLElement* node)
{
    if (node->Name() == TxDCOffset::name)    // is the The TxOpenLoop element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();

        if (ele->Name() == TxDCOffset::PathStr)
        {
            int path = atoi(ele->GetText());
            ele = ele->NextSiblingElement();
            std::string date = "";
            if (ele->Name() == TxDCOffset::DateStr)
            {
                date = ele->GetText();
//                ele = ele->NextSiblingElement();
//                if (ele->Name() == TxOpenLoop::LinearTemperatureCompensation)
//                {
//                    tinyxml2::XMLElement* tempEle = ele->FirstChildElement();
//                    if (tempEle->Name() == TxOpenLoop::CoefficientStr)
//                    {
//                        float tempCoeff = atof(tempEle->GetText());
                        float tempCoeff = 0.0f;
                        std::shared_ptr<TxDCOffset> txDCOffset( new TxDCOffset(path, tempCoeff, date ));

                        mTxDCOffsetCal->addTxDCOffset( path, txDCOffset );
                        mCalDownload->addPath(path, date) ;

                        // now we have a list of Frequency Table elements to create.
                        for (tinyxml2::XMLElement* cur_node =
                                ele->NextSiblingElement(); cur_node; cur_node =
                                cur_node->NextSiblingElement())
                        {
                            // Get the device definition inside board
                            if (!extractFrequecnyTable(txDCOffset, cur_node))
                            {
                                return false;
                            }
                        }
                        // OK we have everything we need for the Frequency Table
                        return true; // we have completed the TxOpenLoop data table
//                    }
//                }
            }
        }
    }
    return false;


}

bool Mplane::TxDCOffsetCalData::extractFrequecnyTable( std::shared_ptr<TxDCOffset> txDCOffset, tinyxml2::XMLElement* node)
{
    if (node->Name() == TxDCOffsetFrequency::name) // is this a FrequencyTable element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        Frequency frequency(0.0);
        if (ele->Name() == TxDCOffsetFrequency::FrequencyStr)
        {
            frequency.set(ele->GetText(), Frequency::KHz);

            ele = ele->NextSiblingElement();

            if( ele->Name() == TxDCOffsetFrequency::TemperatureStr )
            {
                Temperature temperature;
                temperature.set( ele->GetText() );
                ele = ele->NextSiblingElement();

                if( ele->Name() == TxDCOffsetFrequency::IDCOffsetStr )
                {
                    int iDCOffset = atoi( ele->GetText() );
                    ele = ele->NextSiblingElement();

                    if( ele->Name() == TxDCOffsetFrequency::QDCOffsetStr )
                    {
                        int qDCOffset = atoi( ele->GetText() );

                        std::shared_ptr<TxDCOffsetFrequency> frequencyTable(
                                new TxDCOffsetFrequency(frequency, temperature.get(), iDCOffset, qDCOffset ));

                        txDCOffset->addFrequencyTable( frequencyTable );

                        return true; // we have completed Frequency Table OK
                    }
                }
            }

        }

    }
    return false;

}


void Mplane::TxDCOffsetCalData::getAttributeMap(tinyxml2::XMLElement* node,  AttrMap& attrMap) const
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

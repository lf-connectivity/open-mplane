/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxVVACal.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "ICalDownloadManagement.h"


#include "TxVVACal.h"
#include <map>
#include <memory>

#include <iostream>

using namespace Mplane;

const std::string TxVVAFrequency::name = "FrequencyTable";
const std::string TxVVAFrequency::FrequencyStr = "Frequency";
const std::string TxVVAFrequency::TemperatureStr = "Temperature";
const std::string TxVVAFrequency::PointStr = "Point";
const std::string TxVVAFrequency::PWMStr = "PWM";
const std::string TxVVAFrequency::DBStr = "dB";



const std::string Mplane::TxVVA::name = "TxVVA";
const std::string Mplane::TxVVA::PathStr = "Path";
const std::string Mplane::TxVVA::DateStr = "Date" ;


void Mplane::TxVVA::addFrequencyTable(   std::shared_ptr<TxVVAFrequency> frequencyTable)
{
    mFrequencyTables.push_back( frequencyTable );
}

bool Mplane::TxVVA::getPWM(Frequency frequency, float dB, int& pwm )
{
    std::shared_ptr<TxVVAFrequency> freqTable;

     if ( findFrequency( frequency , freqTable ))    // is the frequency in the cal data
     {
         pwm = freqTable->getPWM( dB );
         return true;
     }
     return  false;
}

bool Mplane::TxVVA::getDBM( Frequency frequency, int pwm,  float& dbm )
{
    std::shared_ptr<TxVVAFrequency> freqTable;

     if ( findFrequency( frequency , freqTable ))    // is the frequency in the cal data
     {
         dbm = freqTable->getDBM( pwm );
         return true;
     }
     return  false;
}

bool Mplane::TxVVA::findFrequency(Frequency freq,   std::shared_ptr<TxVVAFrequency>& frequencyTable)
{
    int count = 0;
    std::shared_ptr<TxVVAFrequency> previous  = *(mFrequencyTables.begin());
    for( std::list<std::shared_ptr<TxVVAFrequency>>::iterator it = mFrequencyTables.begin();
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
        previous = (*it);
    }
    return false;
}

const std::string Mplane::TxVVACal::name = "VVACalibrationTx";


std::shared_ptr<TxVVA>Mplane::TxVVACal::getTxVVA(int path)
{
    return mTxVVAData[ path ];
}

void Mplane::TxVVACal::addTxVVA(int path,  std::shared_ptr<TxVVA> txVVA )
{
    mTxVVAData[path] = txVVA;
}

Mplane::TxVVACalData::TxVVACalData( std::shared_ptr<ICalDownload> calDownload ):
            CommonCalBase("TxVVACal", "HW"),
            mCalDownload( calDownload ),
            mCalFilePath( calDownload->getInstallFilePath() )
{
}

Mplane::TxVVACalData::~TxVVACalData()
{
}

void Mplane::TxVVACalData::show()
{
}

ReturnType::State Mplane::TxVVACalData::load()
{
    ReturnType::State status = ReturnType::RT_OK;

    mCalFilePath = mCalDownload->getInstallFilePath();  // need this here to allow unit tests to modify dir to a test dir

    if( isLoaded() )
    {
        mTxVVACal = 0; // dereference the shared pointer so that the cal data is cleared.
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

    if( !parseTxVVACal(root_element) )
    {
        eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
        return ReturnType::RT_SYNTAX_ERROR;
    }
    setLoaded( true );
    return status;

}

std::shared_ptr<TxVVA> Mplane::TxVVACalData::getTxVVA(int path)
{
    return mTxVVACal->getTxVVA( path );
}

bool Mplane::TxVVACalData::parseTxVVACal(tinyxml2::XMLElement* node)
{
    if (node->Name() == TxVVACal::name) // is the first element the correct element?
    {
        AttrMap attributes;
        attributes["version"] = "";
        attributes["country"] = "";
        attributes["facility"] = "";
        attributes["operator"] = "";
        getAttributeMap(node, attributes);

        std::shared_ptr<TxVVACal> txVVACal( new TxVVACal(attributes["version"], attributes["country"],
                        attributes["facility"], attributes["operator"]));

        mTxVVACal = txVVACal;

        for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
                cur_node; cur_node = cur_node->NextSiblingElement())
        {
            // Get the device definition inside board
            if (!extractTxVVA(mTxVVACal, cur_node))
            {
                return false;
            }
        }
        return true;
    }
    return false;

}

bool Mplane::TxVVACalData::extractTxVVA( std::shared_ptr<TxVVACal> txVVACal,
        tinyxml2::XMLElement* node)
{
    if (node->Name() == TxVVA::name)    // is the The TxOpenLoop element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();

        if (ele->Name() == TxVVA::PathStr)
        {
            int path = atoi(ele->GetText());
            ele = ele->NextSiblingElement();
            std::string date = "";
            if (ele->Name() == TxVVA::DateStr)
            {
                date = ele->GetText();
                std::shared_ptr<TxVVA> txVVA( new TxVVA(path, date ));

                mTxVVACal->addTxVVA( path, txVVA );
                mCalDownload->addPath(path, date) ;

                // now we have a list of Frequency Table elements to create.
                for (tinyxml2::XMLElement* cur_node =
                        ele->NextSiblingElement(); cur_node; cur_node =
                                cur_node->NextSiblingElement())
                {
                    // Get the device definition inside board
                    if (!extractFrequecnyTable(txVVA, cur_node))
                    {
                        return false;
                    }
                }
                // OK we have everything we need for the Frequency Table
                return true; // we have completed the TxOpenLoop data table
            }
        }
    }
    return false;
}

bool Mplane::TxVVACalData::extractFrequecnyTable( std::shared_ptr<TxVVA> txVVA, tinyxml2::XMLElement* node)
{
    if (node->Name() == TxVVAFrequency::name) // is this a FrequencyTable element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        Frequency frequency(0.0);
        if (ele->Name() == TxVVAFrequency::FrequencyStr)
        {
            frequency.set(ele->GetText(), Frequency::KHz);

            ele = ele->NextSiblingElement();

            if( ele->Name() == TxVVAFrequency::TemperatureStr )
            {
                Temperature temperature;
                temperature.set( ele->GetText() );

                std::shared_ptr<TxVVAFrequency> frequencyTable(
                        new TxVVAFrequency(frequency, temperature.get()));

                txVVA->addFrequencyTable( frequencyTable );


                // now we have to add our power tables to the frequency table.
                for (tinyxml2::XMLElement* node = ele->NextSiblingElement();
                        node; node = node->NextSiblingElement())
                {
                    if (node->Name() == TxVVAFrequency::PointStr) // is this a Points element?
                    {
                        tinyxml2::XMLElement* ele = node->FirstChildElement();
                        if (ele->Name() == TxVVAFrequency::PWMStr)
                        {
                            if( ele->GetText() != nullptr )
                            {
                                float pwm = atof( ele->GetText() );
                                ele = ele->NextSiblingElement();

                                if (ele->Name() == TxVVAFrequency::DBStr)
                                {
                                    Power dBfs;
                                    if( ele->GetText() != nullptr )
                                    {
                                        dBfs.set(ele->GetText());
                                        // miss of the nasty step at the end as it brakes the spline interpolator
                                        if( dBfs <= 28.0f )
                                        {
                                            frequencyTable->addPoint(dBfs.get(), pwm);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;

}


void Mplane::TxVVACalData::getAttributeMap(tinyxml2::XMLElement* node,  AttrMap& attrMap) const
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

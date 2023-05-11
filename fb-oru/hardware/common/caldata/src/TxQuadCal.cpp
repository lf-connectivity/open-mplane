/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxQuadCal.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "ICalDownloadManagement.h"


#include "TxQuadCal.h"
#include <map>
#include <memory>


using namespace Mplane;

const std::string TxQuadOffsetFrequency::name = "FrequencyTable";
const std::string TxQuadOffsetFrequency::FrequencyStr = "Frequency";
const std::string TxQuadOffsetFrequency::TemperatureStr = "Temperature";
const std::string TxQuadOffsetFrequency::IPhaseOffsetStr = "PhaseI";
const std::string TxQuadOffsetFrequency::QPhaseOffsetStr = "PhaseQ";
const std::string TxQuadOffsetFrequency::IMagStr = "MagI";
const std::string TxQuadOffsetFrequency::QMagStr = "MagQ";



const std::string Mplane::TxQuadOffset::name = "TxQuadPhaseOffset";
const std::string Mplane::TxQuadOffset::PathStr = "Path";
const std::string Mplane::TxQuadOffset::DateStr = "Date" ;


void Mplane::TxQuadOffset::addFrequencyTable(   std::shared_ptr<TxQuadOffsetFrequency> frequencyTable)
{
    mFrequencyTables.push_back( frequencyTable );
}


bool Mplane::TxQuadOffset::getData(Frequency frequency, float &temperature,
        int& iOffset, int& qOffset, int &iMag, int &qMag)
{
    std::shared_ptr<TxQuadOffsetFrequency> freqTable;

     if ( findFrequency( frequency , freqTable ))    // is the frequency in the cal data
     {
         iOffset = freqTable->getIPhaseOffset();
         qOffset = freqTable->getQPhaseOffset();
         iMag = freqTable->getIMag();
         qMag = freqTable->getQMag();
         temperature = freqTable->getTemperature();
         return true;
     }
     return  false;

}

bool Mplane::TxQuadOffset::findFrequency(Frequency freq,   std::shared_ptr<TxQuadOffsetFrequency>& frequencyTable)
{
    int count = 0;
    std::shared_ptr<TxQuadOffsetFrequency> previous  = *(mFrequencyTables.begin());
    for( std::list<std::shared_ptr<TxQuadOffsetFrequency>>::iterator it = mFrequencyTables.begin();
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

const std::string Mplane::TxQuadOffsetCal::name = "TxQuadPhaseOffsetCalibration";

std::shared_ptr<TxQuadOffset> Mplane::TxQuadOffsetCal::getTxQuadOffset(int path)
{
    return mTxQuadOffsetData[ path ];
}

void Mplane::TxQuadOffsetCal::addTxQuadOffset(int path,  std::shared_ptr<TxQuadOffset> txQuadOffset)
{
    mTxQuadOffsetData[path] = txQuadOffset;

}

Mplane::TxQuadOffsetCalData::TxQuadOffsetCalData( std::shared_ptr<ICalDownload> calDownload ):
            CommonCalBase("TxQuadOffsetCal", "HW"),
            mCalDownload( calDownload ),
            mCalFilePath( calDownload->getInstallFilePath() ),
            mTxQuadOffsetCal(0),
			mCalPath(0)
{
}

Mplane::TxQuadOffsetCalData::~TxQuadOffsetCalData()
{
}

void Mplane::TxQuadOffsetCalData::show()
{
}

ReturnType::State Mplane::TxQuadOffsetCalData::load()
{
    ReturnType::State status = ReturnType::RT_OK;

    if( isLoaded() )
    {
        mTxQuadOffsetCal = 0; // dereference the shared pointer so that the cal data is cleared.

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

    if( !parseTxQuadOffsetCal(root_element) )
    {
        eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
        return ReturnType::RT_SYNTAX_ERROR;
    }
    setLoaded( true );
    return status;

}

std::shared_ptr<TxQuadOffset> Mplane::TxQuadOffsetCalData::getTxQuadOffset(int path)
{
    return mTxQuadOffsetCal->getTxQuadOffset( path );
}

bool Mplane::TxQuadOffsetCalData::parseTxQuadOffsetCal(tinyxml2::XMLElement* node)
{
    if (node->Name() == TxQuadOffsetCal::name) // is the first element the correct element?
    {
        AttrMap attributes;
        attributes["version"] = "";
        attributes["country"] = "";
        attributes["facility"] = "";
        attributes["operator"] = "";
        getAttributeMap(node, attributes);

        std::shared_ptr<TxQuadOffsetCal> txQuadOffsetCal( new TxQuadOffsetCal(attributes["version"], attributes["country"],
                        attributes["facility"], attributes["operator"]));

        mTxQuadOffsetCal = txQuadOffsetCal;

        for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
                cur_node; cur_node = cur_node->NextSiblingElement())
        {
            // Get the device definition inside board
            if (!extractTxQuadOffset( mTxQuadOffsetCal, cur_node))
            {
                return false;
            }
        }
        return true;
    }
    return false;

}

bool Mplane::TxQuadOffsetCalData::extractTxQuadOffset( std::shared_ptr<TxQuadOffsetCal> txQuadOffsetCal,
                                                                tinyxml2::XMLElement* node)
{
    if (node->Name() == TxQuadOffset::name)    // is the The TxOpenLoop element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();

        if (ele->Name() == TxQuadOffset::PathStr)
        {
        	mCalPath = atoi(ele->GetText());
            ele = ele->NextSiblingElement();
            std::string date = "";
            if (ele->Name() == TxQuadOffset::DateStr)
            {
                date = ele->GetText();

				float tempCoeff = 0.0f;
				std::shared_ptr<TxQuadOffset> txQuadOffset( new TxQuadOffset(mCalPath, tempCoeff, date ));

				mTxQuadOffsetCal->addTxQuadOffset( mCalPath, txQuadOffset );
				mCalDownload->addPath(mCalPath, date) ;

                // We need to extract the first temperature for each path
                mFirstTempPath.push_back(true);

				// now we have a list of Frequency Table elements to create.
				for (tinyxml2::XMLElement* cur_node =  ele->NextSiblingElement();
						cur_node;
						cur_node = cur_node->NextSiblingElement())
				{
					// Get the device definition inside board
					if (!extractFrequencyTable(txQuadOffset, cur_node))
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

bool Mplane::TxQuadOffsetCalData::extractFrequencyTable( std::shared_ptr<TxQuadOffset> txQuadOffset, tinyxml2::XMLElement* node)
{
    if (node->Name() == TxQuadOffsetFrequency::name) // is this a FrequencyTable element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        Frequency frequency(0.0);
        if (ele->Name() == TxQuadOffsetFrequency::FrequencyStr)
        {
            frequency.set(ele->GetText(), Frequency::KHz);

            ele = ele->NextSiblingElement();

            if( ele->Name() == TxQuadOffsetFrequency::TemperatureStr )
            {
                Temperature temperature;
                temperature.set( ele->GetText() );
                ele = ele->NextSiblingElement();

                // Capture the first temperature in the table for each path.
                if(true == mFirstTempPath[mCalPath-1])
                {
                	mCalDownload->addTemperature(mCalPath, temperature.get());

                	mFirstTempPath[mCalPath-1] = false;
                }

                if( ele->Name() == TxQuadOffsetFrequency::IPhaseOffsetStr )
                {
                    int iOffset = atoi( ele->GetText() );
                    ele = ele->NextSiblingElement();

                    if( ele->Name() == TxQuadOffsetFrequency::QPhaseOffsetStr )
                    {
                        int qOffset = atoi( ele->GetText() );
                        ele = ele->NextSiblingElement();

                        if( ele->Name() == TxQuadOffsetFrequency::IMagStr )
                        {
                            int iMag = atoi( ele->GetText() );

                            ele = ele->NextSiblingElement();

                            if( ele->Name() == TxQuadOffsetFrequency::QMagStr )
                            {
                                int qMag = atoi( ele->GetText() );

                                std::shared_ptr<TxQuadOffsetFrequency> frequencyTable(
                                        new TxQuadOffsetFrequency(frequency, temperature.get(), iOffset, qOffset, iMag, qMag ));

                                txQuadOffset->addFrequencyTable( frequencyTable );

                                return true; // we have completed Frequency Table OK
                            }
                        }
                    }
                }
            }

        }

    }
    return false;
}


void Mplane::TxQuadOffsetCalData::getAttributeMap(tinyxml2::XMLElement* node,  AttrMap& attrMap) const
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

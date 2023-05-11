/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PaDetCal.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "PaDetCal.h"

#include "ICalDownloadManagement.h"


#include <map>
#include <memory>

#include <iostream>

#include "Maths.h"

using namespace Mplane;


const std::string PaDetFrequency::name = "FrequencyTable";
const std::string PaDetFrequency::FrequencyStr = "Frequency";
const std::string PaDetFrequency::TemperatureStr = "Temperature";
const std::string PaDetFrequency::PointStr = "Point";


const std::string PaDetFrequency::PowerStr  = "Power";
const std::string PaDetFrequency::DetAdcStr = "DetADC";
const std::string PaDetFrequency::PwrInStr  = "PwrIn";



const std::string Mplane::PaDet::name = "TxPaCal";
const std::string Mplane::PaDet::PathStr = "Path";
const std::string Mplane::PaDet::DateStr = "Date" ;


void Mplane::PaDet::addFrequencyTable(   std::shared_ptr<PaDetFrequency> frequencyTable)
{
    mFrequencyTables.push_back( frequencyTable );
}

bool Mplane::PaDet::getdBm(Frequency frequency, float pwrdet, float& dBm )
{

    Frequency minFreq, maxFreq;
    findMinMaxFrequencies(minFreq, maxFreq);

    if ((frequency < minFreq) || (frequency > maxFreq))
    {
        return false;
    }

    std::shared_ptr<PaDetFrequency> freqTable1, freqTable2 ;

     if ( findFrequencyTables( frequency , freqTable1, freqTable2 ))    // is the frequency in the cal data
     {
         // linearly interpolate between the nearest two frequency tables

         float dBm1 = freqTable1->getdBm( pwrdet );
         float dBm2 = freqTable2->getdBm( pwrdet );
         Frequency f1 = freqTable1->getFrequency();
         Frequency f2 = freqTable2->getFrequency();

         /* if the two frequency tables are identical then no need to
          interpolate as the Tx frequency must of matched one frequencies at
          which the calibation was performed. */

         if ( f1.get() == f2.get() )
         {
             dBm = dBm1;
         }
         else
         {
             /* interpolate between the frequency tables immediately below and above the Tx frequency */
             dBm = ( frequency.get() - f1.get() ) * ( dBm2 - dBm1 ) / ( f2.get() - f1.get() ) + dBm1 ;
         }

         return true;
     }
     return  false;

}

bool Mplane::PaDet::getPwrIn(Frequency frequency, float pwrOut, float& pwrIn )
{

    Frequency minFreq, maxFreq;
    findMinMaxFrequencies(minFreq, maxFreq);

    if ((frequency < minFreq) || (frequency > maxFreq))
    {
        return false;
    }

    std::shared_ptr<PaDetFrequency> freqTable1, freqTable2 ;

     if ( findFrequencyTables( frequency , freqTable1, freqTable2 ))    // is the frequency in the cal data
     {
         // linearly interpolate between the nearest two frequency tables

         float pwrIn1 = freqTable1->getPwrIn( pwrOut );
         float pwrIn2 = freqTable2->getPwrIn( pwrOut );
         Frequency f1 = freqTable1->getFrequency();
         Frequency f2 = freqTable2->getFrequency();

         /* if the two frequency tables are identical then no need to
          interpolate as the Tx frequency must of matched one frequencies at
          which the calibation was performed. */

         if ( f1.get() == f2.get() )
         {
             pwrIn = pwrIn1;
         }
         else
         {
             /* interpolate between the frequency tables immediately below and above the Tx frequency */
             pwrIn = ( frequency.get() - f1.get() ) * ( pwrIn2 - pwrIn1 ) / ( f2.get() - f1.get() ) + pwrIn1 ;
         }

         return true;
     }
     return  false;

}

bool Mplane::PaDet::findFrequencyTables( Frequency freq,
                                    std::shared_ptr<PaDetFrequency>& frequencyTable1,
                                    std::shared_ptr<PaDetFrequency>& frequencyTable2 )

{
    int count = 0;
    std::shared_ptr<PaDetFrequency> previous  = *(mFrequencyTables.begin());

    for( std::list<std::shared_ptr<PaDetFrequency>>::iterator it = mFrequencyTables.begin();
            it != mFrequencyTables.end(); ++it, ++count )
    {

        if( (*it)->getFrequency() == freq )
        {
            // the Tx frequency is exactly equal to one of the frequency tables.
            frequencyTable1 = (*it);
            frequencyTable2 = (*it);

            return true;
        }
        if( count )
        {
            if( freq > previous->getFrequency() && freq < (*it)->getFrequency() )
            {
                // Use the frequency tables either side of the requested frequency
                frequencyTable1 = previous ;
                frequencyTable2 = (*it) ;
                return true;
            }
        }
        previous = (*it);
    }
    return false;
}


void Mplane::PaDet::findMinMaxFrequencies( Frequency& minFreq, Frequency& maxFreq)
{
    /* Initialise the min/max frequencies */
    minFreq.set(5000000, Frequency::KHz);
    maxFreq.set(0, Frequency::KHz);

    /* we can probably assume the table list is in numerical order, but just in case...*/
    for( std::list<std::shared_ptr<PaDetFrequency>>::iterator it = mFrequencyTables.begin();
            it != mFrequencyTables.end(); ++it  )
    {

        Frequency thisTableFrequency = (*it)->getFrequency();

        //std::cout << "Min/Max: freq= " << thisTableFrequency << std::endl;

        if( thisTableFrequency < minFreq )
            minFreq = thisTableFrequency;

        if (thisTableFrequency > maxFreq)
        {
            maxFreq = thisTableFrequency;
        }
    }

}



const std::string Mplane::PaDetCal::name = "ECBCalibrationTx";


std::shared_ptr<PaDet>Mplane::PaDetCal::getPaDet(int path)
{
    return mPaDetData[ path ];
}

void Mplane::PaDetCal::addPaDet(int path,  std::shared_ptr<PaDet> paDet )
{
    mPaDetData[path] = paDet;
}

Mplane::PaDetCalData::PaDetCalData( std::shared_ptr<ICalDownload> calDownload ):
            CommonCalBase("PaDetCal", "HW"),
            mCalDownload( calDownload ),
            mCalFilePath( calDownload->getInstallFilePath() )
{
}

Mplane::PaDetCalData::~PaDetCalData()
{
}

void Mplane::PaDetCalData::show()
{
}

ReturnType::State Mplane::PaDetCalData::load()
{
    ReturnType::State status = ReturnType::RT_OK;

    if( isLoaded() )
    {
        mPaDetCal = 0; // dereference the shared pointer so that the cal data is cleared.
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

    if( !parsePaDetCal(root_element) )
    {
        eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
        return ReturnType::RT_SYNTAX_ERROR;
    }
    setLoaded( true );
    return status;

}

std::shared_ptr<PaDet> Mplane::PaDetCalData::getPaDet(int path)
{
    return mPaDetCal->getPaDet( path );
}

bool Mplane::PaDetCalData::parsePaDetCal(tinyxml2::XMLElement* node)
{
    if (node->Name() == PaDetCal::name) // is the first element the correct element?
    {
        AttrMap attributes;
        attributes["version"] = "";
        attributes["country"] = "";
        attributes["facility"] = "";
        attributes["operator"] = "";
        getAttributeMap(node, attributes);

        std::shared_ptr<PaDetCal> paDetCal( new PaDetCal(attributes["version"], attributes["country"],
                        attributes["facility"], attributes["operator"]));

        mPaDetCal = paDetCal;

        for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
                cur_node; cur_node = cur_node->NextSiblingElement())
        {
            // Get the device definition inside board
            if (!extractPaDet(mPaDetCal, cur_node))
            {
                return false;
            }
        }
        return true;
    }
    return false;

}


bool Mplane::PaDetCalData::extractPaDet( std::shared_ptr<PaDetCal> paDetCal,
        tinyxml2::XMLElement* node)
{

    if (node->Name() == PaDet::name)
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();

        if (ele->Name() == PaDet::PathStr)
        {
            int path = atoi(ele->GetText());
            ele = ele->NextSiblingElement();
            std::string date = "";
            if (ele->Name() == PaDet::DateStr)
            {
                date = ele->GetText();
                std::shared_ptr<PaDet> paDet( new PaDet(path, date ));

                mPaDetCal->addPaDet( path, paDet );
                mCalDownload->addPath(path, date) ;

                ele = ele->NextSiblingElement();

                // now we have a list of Frequency Table elements to create.
                for (tinyxml2::XMLElement* cur_node =
                        ele->NextSiblingElement(); cur_node; cur_node =
                                cur_node->NextSiblingElement())
                {
                    // Get the device definition inside board
                    if (!extractFrequencyTable(paDet, cur_node))
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

bool Mplane::PaDetCalData::extractFrequencyTable( std::shared_ptr<PaDet> paDet, tinyxml2::XMLElement* node)
{

    if (node->Name() == PaDetFrequency::name) // is this a FrequencyTable element?
    {
        tinyxml2::XMLElement* ele = node->FirstChildElement();
        Frequency frequency(0.0);
        if (ele->Name() == PaDetFrequency::FrequencyStr)
        {
            frequency.set(ele->GetText(), Frequency::KHz);

            // the cal file doesn't currently contain temperature data but
            // the frequency table expects a temperature parameter - for now
            // just set it to an arbitrary (valid) value
            Temperature temperature = 0.0;

            std::shared_ptr<PaDetFrequency> frequencyTable(
                    new PaDetFrequency(frequency, temperature.get()));

            paDet->addFrequencyTable( frequencyTable );

            // now we have to add our power tables to the frequency table.
            for (tinyxml2::XMLElement* node = ele->NextSiblingElement();
                    node; node = node->NextSiblingElement())
            {
                if (node->Name() == PaDetFrequency::PointStr) // is this a Points element?
                {
                    tinyxml2::XMLElement* ele = node->FirstChildElement();
                    if (ele->Name() == PaDetFrequency::PowerStr)
                    {
                        if( ele->GetText() != nullptr )
                        {
                            Power dBm;
                            dBm.set(ele->GetText());

                            ele = ele->NextSiblingElement();

                            if (ele->Name() == PaDetFrequency::PwrInStr)
                            {
                                if( ele->GetText() != nullptr )
                                {
                                    Power pwrIn;
                                    pwrIn.set(ele->GetText());

                                    ele = ele->NextSiblingElement();

                                    if (ele->Name() == PaDetFrequency::DetAdcStr)
                                    {
                                        if( ele->GetText() != nullptr )
                                        {
                                            float pwrDet = Maths::char2float(ele->GetText());
                                            frequencyTable->dBmAddPoint(dBm.get(), pwrDet);
                                            frequencyTable->pwrInAddPoint(dBm.get(), pwrIn.get());
                                        }
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
    return false;

}


void Mplane::PaDetCalData::getAttributeMap(tinyxml2::XMLElement* node,  AttrMap& attrMap) const
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

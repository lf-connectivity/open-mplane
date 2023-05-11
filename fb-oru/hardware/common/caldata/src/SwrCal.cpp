/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SwrCal.cpp
 * \brief     Implementation of reverse power measurement calibration data
 *
 *
 * \details   Implementation of reverse power measurement calibration data
 *
 */

#include "SwrCal.h"

using namespace Mplane;

const std::string Mplane::SwrOpenLoop::name("RevSRXOpenLoop");
const std::string Mplane::SwrOpenLoop::PathStr("Path") ;
const std::string Mplane::SwrOpenLoop::DateStr("Date") ;
const std::string Mplane::SwrOpenLoop::LinearTemperatureCompensation("LinearTemperatureCompensation") ;
const std::string Mplane::SwrOpenLoop::CoefficientStr("Coefficient");
const std::string Mplane::SwrFrequencyBand::name("FrequencyBand");
const std::string Mplane::SwrFrequencyBand::UpperStr = ("Upper");
const std::string Mplane::SwrFrequencyBand::LowerStr = ("Lower");
const std::string Mplane::SwrFrequencyTable::name("FrequencyTable");
const std::string Mplane::SwrFrequencyTable::FrequencyStr("Frequency");
const std::string Mplane::SwrFrequencyTable::TemperatureStr = ("Temperature");
const std::string Mplane::SwrFrequencyTable::PointStr = ("Point");
const std::string Mplane::SwrFrequencyTable::rfDSAStr = ("RFDSA");
const std::string Mplane::SwrFrequencyTable::dBFS2dBmStr = ("dBFS2dBm");

const std::string Mplane::SwrCal::name = "ALCalibrationSWR";


Mplane::SwrFrequencyTable::SwrFrequencyTable(Frequency frequency,
        float temperature):
                mFrequency( frequency ),
                mTemperature( temperature )
{
}

Mplane::SwrFrequencyTable::~SwrFrequencyTable()
{
    mCalPoints.clear();
}


Frequency& Mplane::SwrFrequencyTable::getFrequency()
{
    return mFrequency;
}

float Mplane::SwrFrequencyTable::getTemperature()
{
    return mTemperature;
}

void Mplane::SwrFrequencyTable::addPoint(SwrPoint& point)
{
    mCalPoints.push_back( point );
}

const std::vector<SwrPoint>& Mplane::SwrFrequencyTable::getCalPoints() const
{
    return mCalPoints;
}

SwrPoint Mplane::SwrFrequencyTable::findNearestPower(Power power)
{
    int index = 0;
    Power previous  = mCalPoints[0].dBFS2dBm;
    for( index = 0 ; index < (int) mCalPoints.size() ; index++)
    {
        // if power is greater than or equal to the first element that's as close as we get
        if( index == 0 )
        {
            if( power <= mCalPoints[0].dBFS2dBm )
            {
                break;
            }
        }
        else
        {
            // is the power spot on the table value?
            if( power == mCalPoints[index].dBFS2dBm)
            {
                break;
            }
            else
            {
                // are we between values?
                if( power < mCalPoints[index].dBFS2dBm )
                {
                    // find the closest
                    Power diff = ((mCalPoints[index].dBFS2dBm - previous)/2.0f);
                    if( power < ( previous + diff ))
                    {
                        index--;        // closer to previous, so use it.
                    }
                    break;
                }
            }
        }
        previous = mCalPoints[index].dBFS2dBm;
    }
    if( index == (int) mCalPoints.size())
    {
        index--;    // use the last entry if we are off the end
    }
    return mCalPoints[index];   // return a reference to the nearset cal point

}

Mplane::SwrFrequencyBand::SwrFrequencyBand(Frequency upper, Frequency lower):
                mUpper( upper), mLower( lower )
{
}

Mplane::SwrFrequencyBand::~SwrFrequencyBand()
{
    mFrequencyTables.clear();
}

void Mplane::SwrFrequencyBand::addFrequencyTable( std::shared_ptr<SwrFrequencyTable> frequencyTable)
{
    mFrequencyTables.push_back( frequencyTable );
}

const Frequency& Mplane::SwrFrequencyBand::getLower() const
{
    return mLower;
}

const Frequency& Mplane::SwrFrequencyBand::getUpper() const
{
    return mUpper;
}


Mplane::SwrOpenLoop::SwrOpenLoop(int path, float tempCoeef, const std::string& date):
    mPath( path ), mTempCoeff( tempCoeef ), mDate( date ), mFrequencyBands()
{
}

Mplane::SwrOpenLoop::~SwrOpenLoop()
{
    mFrequencyBands.clear();
}

int Mplane::SwrOpenLoop::getPath()
{
    return mPath;
}

float Mplane::SwrOpenLoop::getCoefficient()
{
    return mTempCoeff;
}

void Mplane::SwrOpenLoop::addFrequencyBand( std::shared_ptr<SwrFrequencyBand> frequencyBand)
{
    mFrequencyBands.push_back( frequencyBand );
}

std::string Mplane::SwrOpenLoop::getDate()
{
    return mDate;
}


Mplane::SwrCal::SwrCal(const std::string& version, const std::string& country,
        const std::string& facility, const std::string& theoperator):
                mVersion( version ), mCountry( country ),
                mFacility( facility ), mOperator( theoperator)
{
}

Mplane::SwrCal::~SwrCal()
{
    mSwrOpenLoopData.clear();
}

std::shared_ptr<ISwrOpenLoop> Mplane::SwrCal::getSwrOpenLoop(int path)
{
    return mSwrOpenLoopData[ path ];
}

void Mplane::SwrCal::addSwrOpenLoop(int path,
        std::shared_ptr<SwrOpenLoop> rxOpenLoop)
{
    mSwrOpenLoopData[path] = rxOpenLoop;
}


Power Mplane::SwrOpenLoop::dBfsTodBm(Frequency frequency, Power rfDsa,
        float temperature)
{
    Power offset(0.0f);

    std::shared_ptr<SwrFrequencyBand> freqBand;
    if( this->findFreqBand( frequency, freqBand ))
    {
        std::shared_ptr<SwrFrequencyTable> freqTable;
        if( freqBand->findFreqTable( frequency, freqTable) )
        {
            float calTemp = freqTable->getTemperature();
            float tempCorr = ( temperature - calTemp ) * this->getCoefficient();
            SwrPoint callPoint = freqTable->findPowerForDSASetting( rfDsa );
            offset = callPoint.dBFS2dBm + tempCorr;
        }
    }
    return offset;
}

Power Mplane::SwrOpenLoop::findNearestAttenuation(Frequency frequency, Power target)
{
    Power atten(-1.0f);

    std::shared_ptr<SwrFrequencyBand> freqBand;
    if( this->findFreqBand( frequency, freqBand ))
    {
        std::shared_ptr<SwrFrequencyTable> freqTable;
        if( freqBand->findFreqTable( frequency, freqTable) )
        {
            atten = freqTable->findNearestPower( target ).rfDSA;
        }
    }
    return atten;
}

bool Mplane::SwrOpenLoop::findFreqBand(Frequency frequency,
        std::shared_ptr<SwrFrequencyBand>& freqBand)
{
    for( std::list<std::shared_ptr<SwrFrequencyBand>>::iterator it = mFrequencyBands.begin();
            it != mFrequencyBands.end(); ++it )
    {
        if( frequency >= (*it)->getLower() &&
                frequency <= (*it)->getUpper())
        {
            freqBand = (*it);
            return true;
        }
    }
    return false;
}

bool Mplane::SwrFrequencyBand::findFreqTable(Frequency frequency,
        std::shared_ptr<SwrFrequencyTable>& freqTable)
{

    int count = 0;
    std::shared_ptr<SwrFrequencyTable> previous = *(mFrequencyTables.begin());

    for( std::list<std::shared_ptr<SwrFrequencyTable>>::iterator it = mFrequencyTables.begin();
            it != mFrequencyTables.end(); ++it, ++count )
    {
        if( (*it)->getFrequency() == frequency )
        {
            freqTable = (*it);
            return true;
        }
        if( count )
        {
            if( frequency > previous->getFrequency() && frequency < (*it)->getFrequency() )
            {
                if( frequency < (previous->getFrequency()+
                        (((*it)->getFrequency() - previous->getFrequency() ) /2)  ))
                {
                    freqTable = previous;
                }
                else
                {
                    freqTable = (*it);
                }
                return true;
            }
        }
        previous = (*it);
    }
    return false;
}

SwrPoint Mplane::SwrFrequencyTable::findPowerForDSASetting(Power rfDsa)
{
    int index = 0;
    Power previous  = mCalPoints[0].rfDSA;
    for( index = 0 ; index < (int) mCalPoints.size() ; index++)
    {
        // if power is greater than or equal to the first element that's as close as we get
        if( index == 0 )
        {
            if( rfDsa <= mCalPoints[0].rfDSA )
            {
                break;
            }
        }
        else
        {
            // is the power spot on the table value?
            if( rfDsa == mCalPoints[index].rfDSA)
            {
                break;
            }
            else
            {
                // are we between values?
                if( rfDsa < mCalPoints[index].rfDSA )
                {
                    // find the closest
                    Power diff = ((mCalPoints[index].rfDSA - previous )/2.0f);
                    if( rfDsa < ( previous + diff ))
                    {
                        index--;        // closer to previous, so use it.
                    }
                    break;
                }
            }
        }
        previous = mCalPoints[index].rfDSA;
    }
    if( index == (int) mCalPoints.size())
    {
        index--;    // use the last entry if we are off the end
    }
    return mCalPoints[index];   // return a reference to the nearset cal point


}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SRxCal.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "SRxCal.h"

using namespace Mplane;

const std::string Mplane::SRxOpenLoop::name("SrxOpenLoop");
const std::string Mplane::SRxOpenLoop::PathStr("Path") ;
const std::string Mplane::SRxOpenLoop::DateStr("Date") ;
const std::string Mplane::SRxOpenLoop::LinearTemperatureCompensation("LinearTemperatureCompensation") ;
const std::string Mplane::SRxOpenLoop::CoefficientStr("Coefficient");
const std::string Mplane::SRxFrequencyBand::name("FrequencyBand");
const std::string Mplane::SRxFrequencyBand::UpperStr = ("Upper");
const std::string Mplane::SRxFrequencyBand::LowerStr = ("Lower");
const std::string Mplane::SRxFrequencyTable::name("FrequencyTable");
const std::string Mplane::SRxFrequencyTable::FrequencyStr("Frequency");
const std::string Mplane::SRxFrequencyTable::TemperatureStr = ("Temperature");
const std::string Mplane::SRxFrequencyTable::PointStr = ("Point");
const std::string Mplane::SRxFrequencyTable::rfDSAStr = ("RFDSA");
const std::string Mplane::SRxFrequencyTable::dBFS2dBmStr = ("dBFS2dBm");

const std::string Mplane::SRxCal::name = "PATCalibrationSRx";


Mplane::SRxFrequencyTable::SRxFrequencyTable(Frequency frequency,
        float temperature):
                mFrequency( frequency ),
                mTemperature( temperature )
{
	// Should only reach ~32
    mCalPoints.reserve(128);
}

Mplane::SRxFrequencyTable::~SRxFrequencyTable()
{
    mCalPoints.clear();
}


Frequency& Mplane::SRxFrequencyTable::getFrequency()
{
    return mFrequency;
}

float Mplane::SRxFrequencyTable::getTemperature()
{
    return mTemperature;
}

void Mplane::SRxFrequencyTable::addPoint(SRxPoint& point)
{
    mCalPoints.push_back( point );
}

const std::vector<SRxPoint>& Mplane::SRxFrequencyTable::getCalPoints() const
{
    return mCalPoints;
}

SRxPoint Mplane::SRxFrequencyTable::findNearestPower(Power power)
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

Mplane::SRxFrequencyBand::SRxFrequencyBand(Frequency upper, Frequency lower):
                mUpper( upper), mLower( lower )
{
}

Mplane::SRxFrequencyBand::~SRxFrequencyBand()
{
    mFrequencyTables.clear();
}

void Mplane::SRxFrequencyBand::addFrequencyTable( std::shared_ptr<SRxFrequencyTable> frequencyTable)
{
    mFrequencyTables.push_back( frequencyTable );
}

const Frequency& Mplane::SRxFrequencyBand::getLower() const
{
    return mLower;
}

const Frequency& Mplane::SRxFrequencyBand::getUpper() const
{
    return mUpper;
}


Mplane::SRxOpenLoop::SRxOpenLoop(int path, float tempCoeef, const std::string& date):
    mPath( path ), mTempCoeff( tempCoeef ), mDate( date ), mFrequencyBands()
{
}

Mplane::SRxOpenLoop::~SRxOpenLoop()
{
    mFrequencyBands.clear();
}

int Mplane::SRxOpenLoop::getPath()
{
    return mPath;
}

float Mplane::SRxOpenLoop::getCoefficient()
{
    return mTempCoeff;
}

void Mplane::SRxOpenLoop::addFrequencyBand( std::shared_ptr<SRxFrequencyBand> frequencyBand)
{
    mFrequencyBands.push_back( frequencyBand );
}

std::string Mplane::SRxOpenLoop::getDate()
{
    return mDate;
}


Mplane::SRxCal::SRxCal(const std::string& version, const std::string& country,
        const std::string& facility, const std::string& theoperator):
                mVersion( version ), mCountry( country ),
                mFacility( facility ), mOperator( theoperator)
{
}

Mplane::SRxCal::~SRxCal()
{
    mSRxOpenLoopData.clear();
}

std::shared_ptr<ISRxOpenLoop> Mplane::SRxCal::getSRxOpenLoop(int path)
{
    return mSRxOpenLoopData[ path ];
}

void Mplane::SRxCal::addSRxOpenLoop(int path,
        std::shared_ptr<SRxOpenLoop> rxOpenLoop)
{
    mSRxOpenLoopData[path] = rxOpenLoop;
}


Power Mplane::SRxOpenLoop::dBfsTodBm(Frequency frequency, Power rfDsa,
        float temperature)
{
    Power offset(0.0f);

    std::shared_ptr<SRxFrequencyBand> freqBand;
    if( this->findFreqBand( frequency, freqBand ))
    {
        std::shared_ptr<SRxFrequencyTable> freqTable;
        if( freqBand->findFreqTable( frequency, freqTable) )
        {
            float calTemp = freqTable->getTemperature();
            float tempCorr = ( temperature - calTemp ) * this->getCoefficient();
            SRxPoint callPoint = freqTable->findPowerForDSASetting( rfDsa );
            offset = callPoint.dBFS2dBm + tempCorr;
        }
    }
    return offset;
}

Power Mplane::SRxOpenLoop::findNearestAttenuation(Frequency frequency, Power target)
{
    Power atten(-1.0f);

    std::shared_ptr<SRxFrequencyBand> freqBand;
    if( this->findFreqBand( frequency, freqBand ))
    {
        std::shared_ptr<SRxFrequencyTable> freqTable;
        if( freqBand->findFreqTable( frequency, freqTable) )
        {
            atten = freqTable->findNearestPower( target ).rfDSA;
        }
    }
    return atten;
}

bool Mplane::SRxOpenLoop::findFreqBand(Frequency frequency,
        std::shared_ptr<SRxFrequencyBand>& freqBand)
{
    for( std::list<std::shared_ptr<SRxFrequencyBand>>::iterator it = mFrequencyBands.begin();
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

bool Mplane::SRxFrequencyBand::findFreqTable(Frequency frequency,
        std::shared_ptr<SRxFrequencyTable>& freqTable)
{

    int count = 0;
    std::shared_ptr<SRxFrequencyTable> previous = *(mFrequencyTables.begin());

    for( std::list<std::shared_ptr<SRxFrequencyTable>>::iterator it = mFrequencyTables.begin();
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

SRxPoint Mplane::SRxFrequencyTable::findPowerForDSASetting(Power rfDsa)
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

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxCal.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>
#include "TxCal.h"
#include <memory>

using namespace Mplane;

const std::string Mplane::TxOpenLoop::name("TxOpenLoop");
const std::string Mplane::TxOpenLoop::PathStr("Path") ;
const std::string Mplane::TxOpenLoop::DateStr("Date") ;
const std::string Mplane::TxOpenLoop::LinearTemperatureCompensation("LinearTemperatureCompensation") ;
const std::string Mplane::TxOpenLoop::CoefficientStr("Coefficient");
const std::string Mplane::FrequencyTable::name("FrequencyTable");
const std::string Mplane::FrequencyTable::FrequencyStr("Frequency");
const std::string Mplane::FrequencyTable::CoefficientStr("Coefficient");
const std::string Mplane::PowerBand::name("PowerBand");
const std::string Mplane::PowerBand::UpperStr = ("Upper");
const std::string Mplane::PowerBand::LowerStr = ("Lower");
const std::string Mplane::PowerBand::BBStr = ("BB");
const std::string Mplane::PowerBand::RFAttenStr = ("RFAtten");
const std::string Mplane::PowerBand::TemperatureStr = ("Temperature");
const std::string Mplane::PowerBand::PointStr = ("Point");
const std::string Mplane::PowerBand::PowerStr = ("Power");


Mplane::TxOpenLoop::TxOpenLoop(int path, float tempCoeff, const std::string& date):
        mPath( path ),
        mTempCoeff( tempCoeff ),
        mDate( date )
{
}

Mplane::TxOpenLoop::~TxOpenLoop()
{
    mFrequencyTables.clear();
}


float Mplane::TxOpenLoop::getCoefficient()
{
    return mTempCoeff;
}

Mplane::TxCal::TxCal(const std::string& version, const std::string& country, const std::string& facility,
        const std::string& theoperator):
    mVersion( version ),
    mCountry( country ),
    mFacility( facility ),
    mOperator( theoperator )
{
}

const std::string Mplane::TxCal::name = "FTUCalibrationTx";

Mplane::TxCal::~TxCal()
{
    mTxOpenLoopData.clear();
}

std::shared_ptr<ITxOpenLoop> Mplane::TxCal::getTxOpenLoop(int path)
{

    return mTxOpenLoopData[ path ];
}

void Mplane::TxCal::addTxOpenLoop(int path, std::shared_ptr<TxOpenLoop> txOpenLoop)
{
    mTxOpenLoopData[path] = txOpenLoop;
}

int Mplane::TxOpenLoop::getPath()
{
    return mPath;
}

void Mplane::TxOpenLoop::addFrequencyTable( std::shared_ptr<FrequencyTable> frequencyTable)
{
    mFrequencyTables.push_back( frequencyTable );
}

std::string Mplane::TxOpenLoop::getDate()
{
    return mDate;
}


bool Mplane::TxOpenLoop::findFrequency(Frequency freq, std::shared_ptr<FrequencyTable> &lwrFrequencyTable,
        std::shared_ptr<FrequencyTable> &uprFrequencyTable)
{

    int count = 0;
    std::shared_ptr<FrequencyTable> previous  = *(mFrequencyTables.begin());
    for( std::list<std::shared_ptr<FrequencyTable>>::iterator it = mFrequencyTables.begin();
            it != mFrequencyTables.end(); ++it, ++count )
    {
        if( (*it)->getFrequency() == freq )
        {
            lwrFrequencyTable = (*it);
            uprFrequencyTable = (*it);
            return true;
        }
        if( count )
        {
            if( freq > previous->getFrequency() && freq < (*it)->getFrequency() )
            {
                lwrFrequencyTable = previous;
                uprFrequencyTable = (*it);
                return true;
            }
        }
        previous = (*it);
    }
    return false;
}


Mplane::FrequencyTable::FrequencyTable(Frequency frequency, bool haveCoefficient, float temperatureCoefficient ):
    mFrequency( frequency ),
    mHasTemperatureCoefficient(haveCoefficient),
    mTemperatureCoefficient(temperatureCoefficient),
    mPrevPowerBand(0)
{
}

Mplane::FrequencyTable::~FrequencyTable()
{
    mPowerBands.clear();
}


Frequency& Mplane::FrequencyTable::getFrequency()
{
    return mFrequency;
}

bool Mplane::FrequencyTable::hasTemperatureCoefficient()
{
    return mHasTemperatureCoefficient;
}

float Mplane::FrequencyTable::getTemperatureCoefficient()
{
    return mTemperatureCoefficient;
}


void Mplane::FrequencyTable::addPowerBand(std::shared_ptr<PowerBand> powerBand)
{
    if( mPrevPowerBand == nullptr )
    {
        mPrevPowerBand = powerBand;
    }
    else
    {
        mPrevPowerBand->setNext( powerBand );
        powerBand->setPrevious( mPrevPowerBand );
        mPrevPowerBand = powerBand;
    }
    mPowerBands.push_back( powerBand );
}

Mplane::PowerBand::PowerBand(Power upper, Power lower, Power baseband, float temperature):
    mUpper(upper),
    mLower(lower),
    mBaseBand(baseband),
    mTemperature(temperature),
    mPrevious(0),
    mNext(0)
{
	// small optimisation - otherwise appending all the cal points adds a noticeable delay
	mCalPoints.reserve(64) ;
}

Mplane::PowerBand::~PowerBand()
{
    mCalPoints.clear();
}

void Mplane::PowerBand::addPointPower(Point &point)
{
    mCalPoints.push_back( point );
}

Power& Mplane::PowerBand::getBaseBand()
{
    return mBaseBand;
}

const std::vector<Point>& Mplane::PowerBand::getCalPoints() const
{
    return mCalPoints;
}

const Power& Mplane::PowerBand::getLower() const
{
    return mLower;
}

float Mplane::PowerBand::getTemperature()
{
    return mTemperature;
}

const Power& Mplane::PowerBand::getUpper() const
{
    return mUpper;
}


bool Mplane::FrequencyTable::isPowerInBand(Power power,
        std::shared_ptr<PowerBand>& powerBand)
{
    int count = 0;
    for( std::list<std::shared_ptr<PowerBand>>::iterator it = mPowerBands.begin();
            it != mPowerBands.end(); ++it )
    {
        if( count++ == 0 && power > (*it)->getUpper())
        {
            return false;
        }
        if( power >= (*it)->getLower() )
        {
            powerBand = (*it);
            return true;
        }
    }
    return false;
}


bool Mplane::FrequencyTable::findPowerBandWithDsa( Power rfAtten,
                                    std::shared_ptr<PowerBand> &powerBand, Point &calPoint )
{
    for( std::list<std::shared_ptr<PowerBand>>::iterator it = mPowerBands.begin();
            it != mPowerBands.end(); ++it )
    {
        if( powerBand->findAtten(rfAtten, calPoint ))
        {
            return true;
        }
    }

    return false;
}

bool Mplane::FrequencyTable::getNextBand(Power power, std::shared_ptr<PowerBand>& powerBand)
{
    int count = 0;
    for( std::list<std::shared_ptr<PowerBand>>::iterator it = mPowerBands.begin();
            it != mPowerBands.end(); ++it )
    {
        if( count++ == 0 && power > (*it)->getUpper())
        {
            return false;
        }
        if( power >= (*it)->getLower() )
        {
        	// cppcheck-suppress postfixOperator
        	it++; // Increment the pointer on by one as we need the next band
        	powerBand = (*it);
        	return true;
        }
    }
    return false;
}

bool Mplane::FrequencyTable::getDataAtFirstPowerBand( Power &rfAtten, Power &baseBand)
{
	//Get the first power powerband
	std::list<std::shared_ptr<PowerBand>>::iterator it = mPowerBands.begin();

	//Get the fixed and var dsa setting for the power band
	std::vector<Point> calPoints = (*it)->getCalPoints();
	rfAtten = calPoints[0].varDsa;

	return true;
}

ReturnType::State Mplane::PowerBand::findNearestPower(Power power, Point &calPoint)
{
	ReturnType::State returnState;

    if( 0 == mCalPoints.size())
    {
    	returnState = ReturnType::RT_ERROR;
    }
    else
    {
		Power previous  = mCalPoints[0].power;

	    int index;

		for( index = 0 ; index < (int) mCalPoints.size() ; index++)
		{
			// if power is greater than or equal to the first element that's as close as we get
			if( index == 0 )
			{
				if( power >= mCalPoints[0].power )
				{
					break;
				}
			}
			else
			{
				// is the power spot on the table value?
				if( power == mCalPoints[index].power)
				{
					break;
				}
				else
				{
					// are we between values?
					if( power > mCalPoints[index].power )
					{
						// find the closest
						Power diff = ((previous - mCalPoints[index].power)/2.0f);
						if( power > ( previous - diff ))
						{
							index--;        // closer to previous, so use it.
						}
						break;
					}
				}
			}
			previous = mCalPoints[index].power;
		}
		if( index == (int) mCalPoints.size())
		{
			index--;    // use the last entry if we are off the end
		}
		calPoint = mCalPoints[index];   // return a reference to the nearest cal point

		returnState = ReturnType::RT_OK;
    }
    return returnState;
}

bool Mplane::PowerBand::findAtten(Power atten, Point &point)
{
    int index = 0;
    for (index = 0; index < (int) mCalPoints.size(); index++)
    {
        if (atten == mCalPoints[index].varDsa)
        {
            point = mCalPoints[index];
            return true;
        }
    }
    return false;
}




bool Mplane::TxOpenLoop::getData(Frequency frequency, Power requiredPower,
        float temperature, Power& baseBand, Power& correction, Power& rfAtten,
        float &calTemperature)
{
    std::shared_ptr<FrequencyTable> lwrFreqTable;
    std::shared_ptr<FrequencyTable> uprFreqTable;

    if ( findFrequency( frequency , lwrFreqTable, uprFreqTable ))    // is the frequency in the cal data
    {
        if( lwrFreqTable == uprFreqTable)  // is frequency on a cal frequency point?
        {
            std::shared_ptr<PowerBand> powerBand;
            // find the power band initially with the required power
            if( lwrFreqTable->isPowerInBand( requiredPower, powerBand )) // do we have a power band for the required power
            {
	            Point calPoint;

                float coefficient = getCoefficient();
                if( lwrFreqTable->hasTemperatureCoefficient())
                {
                    coefficient = lwrFreqTable->getTemperatureCoefficient();
                }

                // now we find the temperature corrected required power (that can vary by a few dB)
                Power tempCorrRequiredPower = requiredPower +
                        (( temperature - powerBand->getTemperature() ) * coefficient);

                // find the power band again using the temperature corrected required
                // power just in case it has pushed us into another power band
                if( lwrFreqTable->isPowerInBand( tempCorrRequiredPower, powerBand )) // do we have a power band for the required power
                {
                    // now find the calibration point for the temperature corrected required power
                    if( powerBand->findNearestPower( tempCorrRequiredPower, calPoint )
                            == ReturnType::RT_OK)
                    {
                        // tell the caller what the calibration temperature was
                        calTemperature = powerBand->getTemperature();

                        // work out the base band power correction by adding the error between the measured
                        // calibration power and the temperature corrected required power
                        correction = tempCorrRequiredPower - calPoint.power;
                        baseBand = powerBand->getBaseBand();

                        rfAtten = calPoint.varDsa;
                        return true;
                    }
                }
            }
        }
        else    // we are in between frequency tables, so go for the lower attenuation
        {
            std::shared_ptr<PowerBand> lwrFreqPowerBand;
            std::shared_ptr<PowerBand> uprFreqPowerBand;
            // start by getting the power band table of the lower frequency using the required power
            if( lwrFreqTable->isPowerInBand( requiredPower, lwrFreqPowerBand ) )
            {

                // work out the ratio of how far we are between the lower and upper frequency table
                // values and our frequency setpoint. This allows us to choose the closest temperature
                // compensated setpoint for the corner cases where we run the risk of being between
                // power tables.
                float ratio =  (double)(frequency.getDbl() - lwrFreqTable->getFrequency().getDbl()) /
                         (double)(uprFreqTable->getFrequency().getDbl() - lwrFreqTable->getFrequency().getDbl());



                // get the temperature coefficient, either from the TX cal table or the frequency table
                float coefficient = getCoefficient();
                if( lwrFreqTable->hasTemperatureCoefficient() && uprFreqTable->hasTemperatureCoefficient())
                {
                    coefficient = (lwrFreqTable->getTemperatureCoefficient() + uprFreqTable->getTemperatureCoefficient()) / 2.0;
                }


                // Calculate the temperature correction using the current power band
                float tempCorr = (( temperature - lwrFreqPowerBand->getTemperature() ) * coefficient);
                // get the new temperature corrected required power
                float tempCorrReqPower = requiredPower.get() + tempCorr;


                // now look for the power band again with the temperature corrected required power, in case its changed
                if( lwrFreqTable->isPowerInBand( tempCorrReqPower, lwrFreqPowerBand ) )
                {
                    // now find the cal point that is nearest to our temperature compensated required power
                    Point lwrFreqCalPoint;
                    if( ReturnType::RT_OK == lwrFreqPowerBand->findNearestPower( tempCorrReqPower, lwrFreqCalPoint ) )
                    {
                        // now go through the same process for the upper frequency table.
                        if( uprFreqTable->isPowerInBand( requiredPower, uprFreqPowerBand ))
                        {
                            // work out the temperature correction factor
                            float uprTempCorr = (( temperature - uprFreqPowerBand->getTemperature() ) * coefficient);
                            float tempCorrUprFreqReqPower = requiredPower.get() + uprTempCorr;

                            // check for the power band again, with the temperature corrected required power
                            if( uprFreqTable->isPowerInBand( tempCorrUprFreqReqPower, uprFreqPowerBand ))
                            {
                                Point uprFreqCalPoint;
                                // find the cal data point for the temperature corrected required power
                                if( ReturnType::RT_OK == uprFreqPowerBand->findNearestPower( tempCorrUprFreqReqPower,
                                        uprFreqCalPoint ) )
                                {
                                    std::shared_ptr<PowerBand> selectedPowerBand;
                                    Point selectedCalPoint;

                                    // Find the power power and calibration point with the lowest combined attenuation
                                    // value. Use this value to find a matching power band and frequency point
                                    // from the other frequency table.
                                    if(  uprFreqCalPoint.varDsa <  lwrFreqCalPoint.varDsa )
                                    {
                                    	if( lwrFreqTable->findPowerBandWithDsa(uprFreqCalPoint.varDsa, lwrFreqPowerBand, lwrFreqCalPoint )
												== false  )
										{
											return false;
										}
                                        // we have selected the upper frequency band
                                        selectedPowerBand = uprFreqPowerBand;
                                        selectedCalPoint = uprFreqCalPoint;
                                    }
                                    else
                                    {
                                        if( uprFreqTable->findPowerBandWithDsa(lwrFreqCalPoint.varDsa, uprFreqPowerBand, uprFreqCalPoint )
                                                == false  )
                                        {
                                            return false;
                                        }
                                        selectedPowerBand = lwrFreqPowerBand;
                                        selectedCalPoint = lwrFreqCalPoint;
                                    }


                                    // our requiredPower band cal point is now based upon the lowest attenuation
                                    // from either the upper or lower frequency table.
                                    float fcorrPower = lwrFreqCalPoint.power.get() +
                                            (((uprFreqCalPoint.power - lwrFreqCalPoint.power).get()) * ratio);

                                    correction = tempCorrReqPower - fcorrPower;   // calculate the digital correction
                                    baseBand = selectedPowerBand->getBaseBand();

                                    rfAtten = selectedCalPoint.varDsa;

                                    // tell the caller what the cal temperature is
                                    calTemperature = selectedPowerBand->getTemperature();

                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return  false;
}

bool Mplane::TxOpenLoop::getData( Frequency frequency, Power &baseBand, Power &rfAtten)
{
    std::shared_ptr<FrequencyTable> lwrFreqTable;
    std::shared_ptr<FrequencyTable> uprFreqTable;

    if ( findFrequency( frequency , lwrFreqTable, uprFreqTable ))    // is the frequency in the cal data
    {
    	//Get settings from the frequency table that is closest to the input frequency
    	if ((frequency.getDbl() - lwrFreqTable->getFrequency().getDbl()) <=
    	    (uprFreqTable->getFrequency().getDbl() - frequency.getDbl()))
    	{
			if (lwrFreqTable->getDataAtFirstPowerBand(rfAtten, baseBand))
			{
				return true;
			}
    	}
    	else
    	{
    		if (uprFreqTable->getDataAtFirstPowerBand(rfAtten, baseBand))
			{
				return true;
			}
    	}
    }
	return false;
}

bool Mplane::TxOpenLoop::getPower( Frequency frequency, Power baseBand, Power rfAtten, Power &power)
{
    std::shared_ptr<FrequencyTable> lwrFreqTable;
    std::shared_ptr<FrequencyTable> uprFreqTable;

    if ( findFrequency( frequency , lwrFreqTable, uprFreqTable ))    // is the frequency in the cal data
    {
		std::shared_ptr<PowerBand> powerBand;
		Point calPoint;

        if( lwrFreqTable == uprFreqTable)  // is frequency on a cal frequency point?
        {
			if (lwrFreqTable->findPowerBandWithDsa(rfAtten, powerBand, calPoint))
			{
				power = calPoint.power;
				return true;
			}
        }
        else
        {
        	//As the frequency lies between the 2 tables, we need to linearly interpolate the power value

        	Point lwrCalPoint;
        	Point uprCalPoint;

        	//Calculate how far the input frequency is from the upper and lower frequencies
            float ratio =  (double)(frequency.getDbl() - lwrFreqTable->getFrequency().getDbl()) /
                     (double)(uprFreqTable->getFrequency().getDbl() - lwrFreqTable->getFrequency().getDbl());

            //Get the power at the lower frequency
			if (lwrFreqTable->findPowerBandWithDsa(rfAtten, powerBand, lwrCalPoint))
			{
				//Get power at the upper frequency
				if (uprFreqTable->findPowerBandWithDsa(rfAtten, powerBand, uprCalPoint))
				{
					//Calculate interpolated power using the factor calculated above
                    float fcorrPower = lwrCalPoint.power.get() +
                            (((uprCalPoint.power - lwrCalPoint.power).get()) * ratio);

                    power.set(fcorrPower);

                    return true;
				}
			}
        }
    }
	return false;
}

std::shared_ptr<PowerBand> Mplane::PowerBand::getPrevious()
{
    return mPrevious;
}

std::shared_ptr<PowerBand> Mplane::PowerBand::getNext()
{
    return mNext;
}

void Mplane::PowerBand::setPrevious(std::shared_ptr<PowerBand> previous)
{
    mPrevious = previous;
}

void Mplane::PowerBand::setNext(std::shared_ptr<PowerBand> next)
{
    mNext = next;
}

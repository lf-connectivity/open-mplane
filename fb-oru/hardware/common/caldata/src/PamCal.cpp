/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      PamCal.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "PamCal.h"

#include <memory>

using namespace Mplane;

const std::string Mplane::PaGainStep::name("PaGainStep");
const std::string Mplane::PaGainStep::PathStr("Path") ;
const std::string Mplane::PaGainStep::DateStr("Date") ;
const std::string Mplane::PaGainStep::LinearTemperatureCompensationStr("LinearTemperatureCompensation") ;
const std::string Mplane::PaGainStep::CoefficientStr("Coefficient");
const std::string Mplane::PaGainStep::StepCoefficientStr("Step_Coefficient");
const std::string Mplane::PgsFrequencyTable::name("FrequencyTable");
const std::string Mplane::PgsFrequencyTable::FrequencyStr("Frequency");
const std::string Mplane::PgsPowerBand::name("PowerBand");
const std::string Mplane::PgsPowerBand::RadioTemperatureStr("RadioTemperature");
const std::string Mplane::PgsPowerBand::PamTemperatureStr("PamTemperature");
const std::string Mplane::PgsPowerBand::VvaPwmStr("VVA_PWM");
const std::string Mplane::PgsPowerBand::LowGainOutputPowerStr("LowGainOutputPower");
const std::string Mplane::PgsPowerBand::HighGainOutputPowerStr("HighGainOutputPower");

////  PaGainStep class implementation ////

Mplane::PaGainStep::PaGainStep(int path, float tempStepCoeff, float tempCoeff, const std::string& date):
        mPath( path ),
        mTempStepCoeff( tempStepCoeff ),
        mTempCoeff( tempCoeff ),
        mDate( date )
{
}

Mplane::PaGainStep::~PaGainStep()
{
    mFrequencyTables.clear();
}


int Mplane::PaGainStep::getPath()
{
    return mPath;
}

float Mplane::PaGainStep::getCoefficient()
{
    return mTempCoeff;
}

float Mplane::PaGainStep::getStepCoefficient()
{
    return mTempStepCoeff;
}

void Mplane::PaGainStep::addFrequencyTable( std::shared_ptr<PgsFrequencyTable> frequencyTable)
{
    mFrequencyTables.push_back( frequencyTable );
}

std::string Mplane::PaGainStep::getDate()
{
    return mDate;
}

bool Mplane::PaGainStep::getData(Frequency frequency, Power power, float& radioCalTemperature, float& pamCalTemperature,
		unsigned int& vvaPwm, Power& lowGainOutputPower, Power& highGainOutputPower )
{
    std::shared_ptr<PgsFrequencyTable> lwrFreqTable;
    std::shared_ptr<PgsFrequencyTable> uprFreqTable;
    float powerRatio = 1;

    if ( findFrequency(frequency, lwrFreqTable, uprFreqTable) )    // is the frequency in the cal data
    {
    	// found an exact frequency or a frequency range
        if ( lwrFreqTable == uprFreqTable )
        {
        	// found the exact frequency in the table, now get the data
            std::shared_ptr<PgsPowerBand> powerBand;
            if ( lwrFreqTable->isLowGainPowerInBand( power, powerBand ) ||
                 lwrFreqTable->isHighGainPowerInBand( power, powerBand ) )
            {
            	// an exact match of power in low or high gain mode
	            radioCalTemperature = powerBand->getRadioTemperature();
	            pamCalTemperature = powerBand->getPamTemperature();
	            vvaPwm = powerBand->getVvaPwm();
	            lowGainOutputPower = powerBand->getLowGainOutputPower();
	            highGainOutputPower = powerBand->getHighGainOutputPower();

                return true;
            }
            else
            {
            	// no exact match, so find a match between power bands
                std::shared_ptr<PgsPowerBand> lwrPowerBand;
                std::shared_ptr<PgsPowerBand> uprPowerBand;
                if ( lwrFreqTable->findPowerBandWithPower(power, lwrPowerBand, uprPowerBand, powerRatio) )
                {
                    float lwrRadioCalTemperature = lwrPowerBand->getRadioTemperature();
                    float lwrRadioPamTemperature = lwrPowerBand->getPamTemperature();
                    int   lwrVvaPpm              = (signed int)lwrPowerBand->getVvaPwm();
                    Power lwrLowGainOutputPower  = lwrPowerBand->getLowGainOutputPower();
                    Power lwrHighGainOutputPower = lwrPowerBand->getHighGainOutputPower();

                    float uprRadioCalTemperature = uprPowerBand->getRadioTemperature();
                    float uprRadioPamTemperature = uprPowerBand->getPamTemperature();
                    int   uprVvaPpm              = (signed int)uprPowerBand->getVvaPwm();
                    Power uprLowGainOutputPower  = uprPowerBand->getLowGainOutputPower();
                    Power uprHighGainOutputPower = uprPowerBand->getHighGainOutputPower();

                    float tmpVva = 0;

                    // now get the final data by interpolation
                    radioCalTemperature = lwrRadioCalTemperature + ((uprRadioCalTemperature - lwrRadioCalTemperature) * powerRatio);
                    pamCalTemperature = lwrRadioPamTemperature + ((uprRadioPamTemperature - lwrRadioPamTemperature) * powerRatio);
                    tmpVva = lwrVvaPpm + ((uprVvaPpm - lwrVvaPpm) * powerRatio);
                    vvaPwm = (unsigned int)tmpVva;
                    lowGainOutputPower = lwrLowGainOutputPower + ((uprLowGainOutputPower - lwrLowGainOutputPower) * powerRatio);
                    highGainOutputPower = lwrHighGainOutputPower + ((uprHighGainOutputPower - lwrHighGainOutputPower) * powerRatio);
#if 0
                    std::cout << "powerRatio is " << powerRatio << std::endl;
                    std::cout << "radioCalTemperature is " << radioCalTemperature << std::endl;
                    std::cout << "pamCalTemperature is " << pamCalTemperature << std::endl;
                    std::cout << "lwrVvaPpm is " << lwrVvaPpm << std::endl;
                    std::cout << "uprVvaPpm is " << uprVvaPpm << std::endl;
                    std::cout << "uprVvaPpm-lwrVvaPpm is " << (uprVvaPpm-lwrVvaPpm) << std::endl;
                    std::cout << "tmpVva is " << tmpVva << std::endl;
                    std::cout << "vvaPwm is " << vvaPwm << std::endl;
                    std::cout << "lowGainOutputPower is " << lowGainOutputPower.get() << std::endl;
                    std::cout << "highGainOutputPower is " << highGainOutputPower.get() << std::endl;
#endif
                    return true;

                }
            }
        }
        else
        {
        	// didn't find the exact frequency in the table, do a bit of interpolation

        	// first, get the ratio between the frequencies, and then do the powers
            float freqRatio =  (double)(frequency.getDbl() - lwrFreqTable->getFrequency().getDbl()) /
                     (double)(uprFreqTable->getFrequency().getDbl() - lwrFreqTable->getFrequency().getDbl());

#if 0
            std::cout << "freqRatio is " << freqRatio << std::endl;
#endif
            // now get the data from the low and upper frequency tables
            // and then perform the interpolation on that data
            std::shared_ptr<PgsPowerBand> powerBand;
            std::shared_ptr<PgsPowerBand> lwrPowerBand;
            std::shared_ptr<PgsPowerBand> uprPowerBand;

            float lwrFreqRadioCalTemperature;
            float lwrFreqRadioPamTemperature;
            int   lwrFreqVvaPpm;
            Power lwrFreqLowGainOutputPower;
            Power lwrFreqHighGainOutputPower;

            float uprFreqRadioCalTemperature;
            float uprFreqRadioPamTemperature;
            int   uprFreqVvaPpm;
            Power uprFreqLowGainOutputPower;
            Power uprFreqHighGainOutputPower;

            if ( lwrFreqTable->isLowGainPowerInBand( power, powerBand ) ||
                 lwrFreqTable->isHighGainPowerInBand( power, powerBand ) )
            {
            	// an exact match of power in low or high gain mode
            	lwrFreqRadioCalTemperature = powerBand->getRadioTemperature();
            	lwrFreqRadioPamTemperature = powerBand->getPamTemperature();
            	lwrFreqVvaPpm = powerBand->getVvaPwm();
            	lwrFreqLowGainOutputPower = powerBand->getLowGainOutputPower();
            	lwrFreqHighGainOutputPower = powerBand->getHighGainOutputPower();
            }
            else
            {
            	// no exact match, so find a match between power bands
                if ( lwrFreqTable->findPowerBandWithPower(power, lwrPowerBand, uprPowerBand, powerRatio) )
                {
                    float lwrRadioCalTemperature = lwrPowerBand->getRadioTemperature();
                    float lwrRadioPamTemperature = lwrPowerBand->getPamTemperature();
                    int   lwrVvaPpm              = (signed int)lwrPowerBand->getVvaPwm();
                    Power lwrLowGainOutputPower  = lwrPowerBand->getLowGainOutputPower();
                    Power lwrHighGainOutputPower = lwrPowerBand->getHighGainOutputPower();

                    float uprRadioCalTemperature = uprPowerBand->getRadioTemperature();
                    float uprRadioPamTemperature = uprPowerBand->getPamTemperature();
                    int   uprVvaPpm              = (signed int)uprPowerBand->getVvaPwm();
                    Power uprLowGainOutputPower  = uprPowerBand->getLowGainOutputPower();
                    Power uprHighGainOutputPower = uprPowerBand->getHighGainOutputPower();

                    float tmpVva = 0;

                    // now get the final data by interpolation, for the lower freq table
                    lwrFreqRadioCalTemperature = lwrRadioCalTemperature + ((uprRadioCalTemperature - lwrRadioCalTemperature) * powerRatio);
                    lwrFreqRadioPamTemperature = lwrRadioPamTemperature + ((uprRadioPamTemperature - lwrRadioPamTemperature) * powerRatio);
                    tmpVva = lwrVvaPpm + ((uprVvaPpm - lwrVvaPpm) * powerRatio);
                    lwrFreqVvaPpm = (unsigned int)tmpVva;
                    lwrFreqLowGainOutputPower = lwrLowGainOutputPower + ((uprLowGainOutputPower - lwrLowGainOutputPower) * powerRatio);
                    lwrFreqHighGainOutputPower = lwrHighGainOutputPower + ((uprHighGainOutputPower - lwrHighGainOutputPower) * powerRatio);
                }
                else
                {
                	return false;
                }
            }

            // now repeat for the upper freq table
            if ( uprFreqTable->isLowGainPowerInBand( power, powerBand ) ||
            		uprFreqTable->isHighGainPowerInBand( power, powerBand ) )
            {
            	// an exact match of power in low or high gain mode
            	uprFreqRadioCalTemperature = powerBand->getRadioTemperature();
            	uprFreqRadioPamTemperature = powerBand->getPamTemperature();
            	uprFreqVvaPpm = powerBand->getVvaPwm();
            	uprFreqLowGainOutputPower = powerBand->getLowGainOutputPower();
            	uprFreqHighGainOutputPower = powerBand->getHighGainOutputPower();
            }
            else
            {
            	// no exact match, so find a match between power bands
            	if ( uprFreqTable->findPowerBandWithPower(power, lwrPowerBand, uprPowerBand, powerRatio) )
            	{
            		float lwrRadioCalTemperature = lwrPowerBand->getRadioTemperature();
            		float lwrRadioPamTemperature = lwrPowerBand->getPamTemperature();
            		int lwrVvaPpm              = (signed int)lwrPowerBand->getVvaPwm();
            		Power lwrLowGainOutputPower  = lwrPowerBand->getLowGainOutputPower();
            		Power lwrHighGainOutputPower = lwrPowerBand->getHighGainOutputPower();

            		float uprRadioCalTemperature = uprPowerBand->getRadioTemperature();
            		float uprRadioPamTemperature = uprPowerBand->getPamTemperature();
            		int uprVvaPpm              = (signed int)uprPowerBand->getVvaPwm();
            		Power uprLowGainOutputPower  = uprPowerBand->getLowGainOutputPower();
            		Power uprHighGainOutputPower = uprPowerBand->getHighGainOutputPower();

                    float tmpVva = 0;

            		// now get the final data by interpolation, for the upper freq table
					uprFreqRadioCalTemperature = lwrRadioCalTemperature + ((uprRadioCalTemperature - lwrRadioCalTemperature) * powerRatio);
					uprFreqRadioPamTemperature = lwrRadioPamTemperature + ((uprRadioPamTemperature - lwrRadioPamTemperature) * powerRatio);
					tmpVva = lwrVvaPpm + ((uprVvaPpm - lwrVvaPpm) * powerRatio);
					uprFreqVvaPpm = (unsigned int)tmpVva;
					uprFreqLowGainOutputPower = lwrLowGainOutputPower + ((uprLowGainOutputPower - lwrLowGainOutputPower) * powerRatio);
					uprFreqHighGainOutputPower = lwrHighGainOutputPower + ((uprHighGainOutputPower - lwrHighGainOutputPower) * powerRatio);
            	}
                else
                {
                	return false;
                }
            }

    		// now get the final data by interpolation, usng the ratio between the lower and upper freq table data
            radioCalTemperature = lwrFreqRadioCalTemperature + ((uprFreqRadioCalTemperature - lwrFreqRadioCalTemperature) * freqRatio);
            pamCalTemperature = lwrFreqRadioPamTemperature + ((uprFreqRadioPamTemperature - lwrFreqRadioPamTemperature) * freqRatio);
            float tmpVva = lwrFreqVvaPpm + ((uprFreqVvaPpm - lwrFreqVvaPpm) * freqRatio);
            vvaPwm = (unsigned int)tmpVva;
            lowGainOutputPower = lwrFreqLowGainOutputPower + ((uprFreqLowGainOutputPower - lwrFreqLowGainOutputPower) * freqRatio);
            highGainOutputPower = lwrFreqHighGainOutputPower + ((uprFreqHighGainOutputPower - lwrFreqHighGainOutputPower) * freqRatio);
#if 0
			std::cout << "lwrFreqLowGainOutputPower is " << lwrFreqLowGainOutputPower.get() << std::endl;
			std::cout << "uprFreqLowGainOutputPower is " << uprFreqLowGainOutputPower.get() << std::endl;

			std::cout << "freqRatio is " << freqRatio << std::endl;
			std::cout << "powerRatio is " << powerRatio << std::endl;
            std::cout << "radioCalTemperature is " << radioCalTemperature << std::endl;
            std::cout << "pamCalTemperature is " << pamCalTemperature << std::endl;
            std::cout << "lwrFreqVvaPpm is " << lwrFreqVvaPpm << std::endl;
            std::cout << "uprFreqVvaPpm is " << uprFreqVvaPpm << std::endl;
            std::cout << "tmpVva is " << tmpVva << std::endl;
            std::cout << "vvaPwm is " << vvaPwm << std::endl;
            std::cout << "lowGainOutputPower is " << lowGainOutputPower.get() << std::endl;
            std::cout << "highGainOutputPower is " << highGainOutputPower.get() << std::endl;
#endif
            return true;

        }
    }

    return  false;
}

bool Mplane::PaGainStep::findFrequency(Frequency freq, std::shared_ptr<PgsFrequencyTable> &lwrFrequencyTable,
        std::shared_ptr<PgsFrequencyTable> &uprFrequencyTable)
{
    int count = 0;
    std::shared_ptr<PgsFrequencyTable> previous  = *(mFrequencyTables.begin());
    for( std::list<std::shared_ptr<PgsFrequencyTable>>::iterator it = mFrequencyTables.begin();
            it != mFrequencyTables.end(); ++it, ++count )
    {
        if ( (*it)->getFrequency() == freq )
        {
            lwrFrequencyTable = (*it);
            uprFrequencyTable = (*it);
            return true;
        }

        if ( count )
        {
            if ( freq > previous->getFrequency() && freq < (*it)->getFrequency() )
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

////  PamCal class implementation ////

Mplane::PamCal::PamCal(const std::string& version, const std::string& country, const std::string& facility,
        const std::string& theoperator):
    mVersion( version ),
    mCountry( country ),
    mFacility( facility ),
    mOperator( theoperator )
{
}

const std::string Mplane::PamCal::name = "PaGainStepCalibration";

Mplane::PamCal::~PamCal()
{
    mPaGainStepData.clear();
}

std::shared_ptr<IPaGainStep> Mplane::PamCal::getPaGainStep(int path)
{
    return mPaGainStepData[ path ];
}

void Mplane::PamCal::addPaGainStep(int path, std::shared_ptr<PaGainStep> paGainStep)
{
    mPaGainStepData[path] = paGainStep;
}


////  PgsPowerBand class implementation ////

Mplane::PgsPowerBand::PgsPowerBand( float radioTemperature, float pamTemperature,
		unsigned int vvaPwm, Power lowGainOutputPower, Power highGainOutputPower):
    mRadioTemperature( radioTemperature ),
	mPamTemperature( pamTemperature ),
	mVvaPwm( vvaPwm ),
	mLowGainOutputPower( lowGainOutputPower),
	mHighGainOutputPower( highGainOutputPower)
{
}

Mplane::PgsPowerBand::~PgsPowerBand()
{
}

float& Mplane::PgsPowerBand::getRadioTemperature()
{
    return mRadioTemperature;
}

float& Mplane::PgsPowerBand::getPamTemperature()
{
    return mPamTemperature;
}

unsigned int& Mplane::PgsPowerBand::getVvaPwm()
{
    return mVvaPwm;
}

Power& Mplane::PgsPowerBand::getLowGainOutputPower()
{
    return mLowGainOutputPower;
}

Power& Mplane::PgsPowerBand::getHighGainOutputPower()
{
    return mHighGainOutputPower;
}


////  PgsFrequencyTable class implementation ////

Mplane::PgsFrequencyTable::PgsFrequencyTable(Frequency frequency):
    mFrequency( frequency )
{
}

Mplane::PgsFrequencyTable::~PgsFrequencyTable()
{
    mPowerBands.clear();
}


Frequency& Mplane::PgsFrequencyTable::getFrequency()
{
    return mFrequency;
}

void Mplane::PgsFrequencyTable::addPgsPowerBand( std::shared_ptr<PgsPowerBand> powerBand )
{
    mPowerBands.push_back( powerBand );
}

bool Mplane::PgsFrequencyTable::isLowGainPowerInBand( Power power, std::shared_ptr<PgsPowerBand> &powerBand )
{
    for( std::list<std::shared_ptr<PgsPowerBand>>::iterator it = mPowerBands.begin();
            it != mPowerBands.end(); ++it )
    {
        if ( power == (*it)->getLowGainOutputPower() )
        {
            powerBand = (*it);
            return true;
        }
    }

    return false;
}

bool Mplane::PgsFrequencyTable::isHighGainPowerInBand( Power power, std::shared_ptr<PgsPowerBand> &powerBand )
{
    for( std::list<std::shared_ptr<PgsPowerBand>>::iterator it = mPowerBands.begin();
            it != mPowerBands.end(); ++it )
    {
        if ( power == (*it)->getHighGainOutputPower() )
        {
            powerBand = (*it);
            return true;
        }
    }

    return false;
}

bool Mplane::PgsFrequencyTable::findPowerBandWithPower( Power power,
		std::shared_ptr<PgsPowerBand> &lwrPowerBand,
		std::shared_ptr<PgsPowerBand> &uprPowerBand,
		float &ratio)
{
    int count = 0;
    std::shared_ptr<PgsPowerBand> previous  = *(mPowerBands.begin());

    for ( std::list<std::shared_ptr<PgsPowerBand>>::iterator it = mPowerBands.begin();
            it != mPowerBands.end(); ++it, ++count )
    {
        if ( power == (*it)->getLowGainOutputPower() ||
             power == (*it)->getHighGainOutputPower() )
        {
            lwrPowerBand = (*it);
            uprPowerBand = (*it);
            ratio = 1;
            return true;
        }

        if ( count )
        {
            if ( power < previous->getLowGainOutputPower() && power > (*it)->getLowGainOutputPower() )
            {
            	lwrPowerBand = previous;
                uprPowerBand = (*it);

                ratio = (double)(lwrPowerBand->getLowGainOutputPower().get() - power.get()) /
                		(double)(lwrPowerBand->getLowGainOutputPower().get() - uprPowerBand->getLowGainOutputPower().get());

                return true;
            }

            if ( power < previous->getHighGainOutputPower() && power > (*it)->getHighGainOutputPower() )
            {
            	lwrPowerBand = previous;
                uprPowerBand = (*it);

                ratio = (double)(lwrPowerBand->getHighGainOutputPower().get() - power.get()) /
                		(double)(lwrPowerBand->getHighGainOutputPower().get() - uprPowerBand->getHighGainOutputPower().get());

                return true;
            }
        }
        previous = (*it);
    }

    // If the high power is more than what is in the table
    std::shared_ptr<PgsPowerBand> begin  = *(mPowerBands.begin());
    if ( power > begin->getHighGainOutputPower() )
    {
        lwrPowerBand = begin;
        uprPowerBand = begin;
        ratio = 1;
        return true;
    }

    // If the high/low power less more than what is in the table
    if ( (power < previous->getHighGainOutputPower()) ||
         (power < previous->getLowGainOutputPower()) )
    {
        lwrPowerBand = previous;
        uprPowerBand = previous;
        ratio = 1;
        return true;
    }

    // If we have a gap between the last high power and the first low power
    if ( (power > begin->getLowGainOutputPower()) &&
         (power < previous->getHighGainOutputPower())   )
    {
        lwrPowerBand = previous;
        uprPowerBand = previous;
        ratio = 1;
        return true;
    }

    return false;
}

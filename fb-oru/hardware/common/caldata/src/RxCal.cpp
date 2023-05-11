/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxCal.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IRxAttenuators.h"

#include "RxCal.h"

using namespace Mplane;

const std::string Mplane::RxOpenLoop::name("RxOpenLoop");
const std::string Mplane::RxOpenLoop::PathStr("Path") ;
const std::string Mplane::RxOpenLoop::DateStr("Date") ;
const std::string Mplane::RxOpenLoop::LinearTemperatureCompensation("LinearTemperatureCompensation") ;
const std::string Mplane::RxOpenLoop::CoefficientStr("Coefficient");
const std::string Mplane::RxOpenLoop::GainTargetStr("GainTarget");
const std::string Mplane::RxFrequencyBand::name("FrequencyBand");
const std::string Mplane::RxFrequencyBand::UpperStr = ("Upper");
const std::string Mplane::RxFrequencyBand::LowerStr = ("Lower");
const std::string Mplane::RxFrequencyBand::IFDSAStr = ("IFDSA");
const std::string Mplane::IFAttenTable::name("IFAttenTable");
const std::string Mplane::IFAttenTable::StepStr = ("Step");
const std::string Mplane::IFAttenTable::GainRedStr = ("GainReduct");
const std::string Mplane::IFAttenTable::IFDSARedStr = ("IFDSAReduct");
const std::string Mplane::RxFrequencyTable::name("FrequencyTable");
const std::string Mplane::RxFrequencyTable::FrequencyStr("Frequency");
const std::string Mplane::RxFrequencyTable::TemperatureStr = ("Temperature");
const std::string Mplane::RxFrequencyTable::ifDSAStr = ("IFDSA");
const std::string Mplane::RxFrequencyTable::PointStr = ("Point");
const std::string Mplane::RxFrequencyTable::rfDSAStr = ("RFDSA");
const std::string Mplane::RxFrequencyTable::dBFS2dBmStr = ("dBFS2dBm");

const std::string Mplane::RxCal::name = "FTUCalibrationRx";

//=============================================================================================================
// IFAttenTable
//=============================================================================================================

Mplane::IFAttenTable::IFAttenTable()
{
	// Should only reach ~12
	mCalSteps.reserve(32);
}

Mplane::IFAttenTable::~IFAttenTable()
{
	mCalSteps.clear();
}

void Mplane::IFAttenTable::addRxStep(RxStep &step)
{
	mCalSteps.push_back( step );
}

const std::vector<RxStep>& Mplane::IFAttenTable::getCalSteps() const
{
	return mCalSteps;
}

RxStep Mplane::IFAttenTable::findNearestGainRed(Power gainRed)
{
	int index = 0;
	Power previous  = mCalSteps[0].GainRed;
	for( index = 0 ; index < (int) mCalSteps.size() ; index++)
	{
		// if reduction is less than or equal to the first element that's as close as we get
		if( index == 0 )
		{
			if( gainRed <= mCalSteps[0].GainRed )
			{
				break;
			}
		}
		else
		{
			// is the power spot on the table value?
			if( gainRed == mCalSteps[index].GainRed)
			{
				break;
			}
			else
			{
				// are we between values?
				if( gainRed < mCalSteps[index].GainRed )
				{
					// find the closest
					Power diff = ((previous - mCalSteps[index].GainRed)/2.0f);
					if( gainRed < ( previous - diff ))
					{
						index--;        // closer to previous, so use it.
					}
					break;
				}
			}
		}
		previous = mCalSteps[index].GainRed;
	}
	if( index == (int) mCalSteps.size())
	{
		index--;    // use the last entry if we are off the end
	}
	return mCalSteps[index];   // return a reference to the nearset cal point

}


//=============================================================================================================
// RxFrequencyTable
//=============================================================================================================

Mplane::RxFrequencyTable::RxFrequencyTable(Frequency frequency,
		float temperature):
				mFrequency( frequency ),
				mTemperature( temperature ),
				mIfDsa(0.0)
{
	// Should only reach ~32
	mCalPoints.reserve(128);
}

Mplane::RxFrequencyTable::RxFrequencyTable(Frequency frequency,
		float temperature, Power IfDsa):
				mFrequency( frequency ),
				mTemperature( temperature ),
				mIfDsa (IfDsa)
{
	// Should only reach ~32
	mCalPoints.reserve(128);
}

Mplane::RxFrequencyTable::~RxFrequencyTable()
{
	mCalPoints.clear();
}


Frequency& Mplane::RxFrequencyTable::getFrequency()
{
	return mFrequency;
}

float Mplane::RxFrequencyTable::getTemperature()
{
	return mTemperature;
}

Power& Mplane::RxFrequencyTable::getIfDsa()
{
	return mIfDsa;
}

void Mplane::RxFrequencyTable::addRxPoint(RxPoint& point)
{
	mCalPoints.push_back( point );
}

const std::vector<RxPoint>& Mplane::RxFrequencyTable::getCalPoints() const
{
	return mCalPoints;
}

RxPoint Mplane::RxFrequencyTable::findNearestPower(Power power)
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
					Power diff = ((previous - mCalPoints[index].dBFS2dBm)/2.0f);
					if( power < ( previous - diff ))
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

RxPoint Mplane::RxFrequencyTable::findPowerForDSASetting(Power rfDsa)
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
					Power diff = ((previous - mCalPoints[index].rfDSA)/2.0f);
					if( rfDsa < ( previous - diff ))
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


//=============================================================================================================
// RxFrequencyBand
//=============================================================================================================

Mplane::RxFrequencyBand::RxFrequencyBand(Frequency upper, Frequency lower,   Power IfDsa):
				mUpper( upper), mLower( lower ), mIfDsa( IfDsa ), mIfDsaLoc(IfDsaLoc::PerFreqBand)
{
}

Mplane::RxFrequencyBand::RxFrequencyBand(Frequency upper, Frequency lower):
				mUpper( upper), mLower( lower ), mIfDsa( 0.0 ), mIfDsaLoc(IfDsaLoc::PerFreqTable)
{
}

Mplane::RxFrequencyBand::~RxFrequencyBand()
{
	mFrequencyTables.clear();
}

void Mplane::RxFrequencyBand::addIFAttenTable( std::shared_ptr<IFAttenTable> iFAttenTable )
{
	mIFAttenTable = iFAttenTable;
}

void Mplane::RxFrequencyBand::addFrequencyTable(
		std::shared_ptr<RxFrequencyTable> frequencyTable)
{
	mFrequencyTables.push_back( frequencyTable );
}

const Frequency& Mplane::RxFrequencyBand::getLower() const
{
	return mLower;
}

const Frequency& Mplane::RxFrequencyBand::getUpper() const
{
	return mUpper;
}

Power& Mplane::RxFrequencyBand::getIfDsa(Frequency frequency)
{
	if (mIfDsaLoc == IfDsaLoc::PerFreqBand)
	{
		return mIfDsa;
	}
	else
	{
		std::shared_ptr<RxFrequencyTable> freqTable;
		if ( !this->findFreqTable( frequency, freqTable) )
		{
			return mIfDsa;
		}
		else
		{
			return freqTable->getIfDsa();
		}
	}
}

RxFrequencyBand::IfDsaLoc Mplane::RxFrequencyBand::getIfDsaLoc()
{
	return mIfDsaLoc;
}

const std::shared_ptr<IFAttenTable>& Mplane::RxFrequencyBand::getIFAttenTable() const
{
	return mIFAttenTable;
}

bool Mplane::RxFrequencyBand::findFreqTable(Frequency frequency, std::shared_ptr<RxFrequencyTable>& freqTable)
{
	std::list<std::shared_ptr<RxFrequencyTable>>::iterator it = mFrequencyTables.begin() ;
	if (it == mFrequencyTables.end())
		return false ;

	// For RX we may be applying "Howard's cunning scheme" which will push the LO centre beyond the calibrated data, so choose
	// the closest band we can

	// Check for freq below minimum in cal
	if (frequency < (*it)->getFrequency())
	{
		// use this
		freqTable = (*it);
		return true;
	}

	// search list
	std::shared_ptr<RxFrequencyTable> previous ;
	for( ; it != mFrequencyTables.end(); ++it )
	{
		freqTable = (*it);
		if( frequency == freqTable->getFrequency())
		{
			return true;
		}

		// Not in this band, is it between the previous band and this one?
		if (previous)
		{
			if( frequency > previous->getFrequency() && frequency < freqTable->getFrequency())
			{
				// use the closest band
				int distLower(frequency.getInt() - previous->getFrequency().getInt()) ;
				int distUpper(freqTable->getFrequency().getInt() - frequency.getInt()) ;
				if (distUpper > distLower)
					freqTable = previous ;
				return true;
			}
		}
		previous = (*it) ;
	}

	// frequency must be above the bands, just return the maximum
	return true;
}

const std::list<std::shared_ptr<RxFrequencyTable> >& Mplane::RxFrequencyBand::getFrequencyTables() const
{
	return mFrequencyTables ;
}



//=============================================================================================================
// RxOpenLoop
//=============================================================================================================

Mplane::RxOpenLoop::RxOpenLoop(int path, float tempCoeef, const std::string& date, float gainTarget):
//	Loggable("RxOpenLoop","HW"),
	mPath( path ), mTempCoeff( tempCoeef ), mDate( date ), mGainTarget( gainTarget ), mFrequencyBands()
{
}

Mplane::RxOpenLoop::~RxOpenLoop()
{
	mFrequencyBands.clear();
}

int Mplane::RxOpenLoop::getPath()
{
	return mPath;
}

float Mplane::RxOpenLoop::getCoefficient()
{
	return mTempCoeff;
}

float Mplane::RxOpenLoop::getGainTarget()
{
	return mGainTarget;
}

void Mplane::RxOpenLoop::addFrequencyBand(
		std::shared_ptr<RxFrequencyBand> frequencyBand)
{
	mFrequencyBands.push_back( frequencyBand );
}

std::string Mplane::RxOpenLoop::getDate()
{
	return mDate;
}

bool RxOpenLoop::getIfAtten(Frequency frequency, Power& ifAtten, Temperature& calTemperature)
{
	std::shared_ptr<RxFrequencyBand> freqBand;
	if( !this->findFreqBand( frequency, freqBand ))
		return false ;

	std::shared_ptr<RxFrequencyTable> freqTable;
	if( !freqBand->findFreqTable( frequency, freqTable) )
		return false ;

	calTemperature = Temperature(freqTable->getTemperature());
	ifAtten = freqBand->getIfDsa(frequency);

	return true;
}

bool Mplane::RxOpenLoop::getIfAtten(Frequency frequency, Power& ifAtten)
{
	Temperature calTemperature ;
	return getIfAtten(frequency, ifAtten, calTemperature) ;
}

bool Mplane::RxOpenLoop::getRfAtten(Frequency frequency, Power amplitude,  Power &rfAtten)
{
	std::shared_ptr<RxFrequencyBand> freqBand;
	if( this->findFreqBand( frequency, freqBand ))
	{
		std::shared_ptr<RxFrequencyTable> freqTable;
		if( freqBand->findFreqTable( frequency, freqTable) )
		{
			RxPoint calPoint = freqTable->findNearestPower( amplitude );
			rfAtten = calPoint.rfDSA;
			return true;
		}
	}
	return false;
}

bool Mplane::RxOpenLoop::getRfAttenAndScaler(Power amplitude, Frequency frequency, Power tempCompIdeal,  Power &rfAtten, Power &scaler)
{
	std::shared_ptr<RxFrequencyBand> freqBand;
	if( this->findFreqBand( frequency, freqBand ))
	{
		std::shared_ptr<RxFrequencyTable> freqTable;
		if( freqBand->findFreqTable( frequency, freqTable) )
		{
			if ( amplitude == 0 )
			{
				RxPoint calPoint = freqTable->findPowerForDSASetting( 0.0f );
				rfAtten = 0;
				scaler = calPoint.dBFS2dBm - tempCompIdeal;

			}
			else
			{
				RxPoint calPoint = freqTable->findNearestPower( tempCompIdeal );
				rfAtten = calPoint.rfDSA;
				scaler = calPoint.dBFS2dBm - tempCompIdeal;
			}
			return true;
		}
	}
	return false;
}

Power Mplane::RxOpenLoop::getTempCompTarget(Frequency frequency, Power target, float temperature)
{
	Power result(0.0f);

	std::shared_ptr<RxFrequencyBand> freqBand;
	if( !this->findFreqBand( frequency, freqBand ))
		return result;

	std::shared_ptr<RxFrequencyTable> freqTable;
	if( !freqBand->findFreqTable( frequency, freqTable) )
		return result;

	// Temperature correct
	float calTemp = freqTable->getTemperature();
	float tempCorr = ( temperature - calTemp ) * this->getCoefficient();
	result = target - tempCorr;
	return result;
}

Power Mplane::RxOpenLoop::getRfdsaForFrequency(Frequency frequency)
{
	Power dsa(0.0f);

	std::shared_ptr<RxFrequencyBand> freqBand;
	if( !this->findFreqBand( frequency, freqBand ))
		return dsa ;

	std::shared_ptr<RxFrequencyTable> freqTable;
	if( !freqBand->findFreqTable( frequency, freqTable) )
		return dsa ;

	std::vector<RxPoint> calPoints = freqTable->getCalPoints();

	return calPoints[0].rfDSA;
}

Power Mplane::RxOpenLoop::dBfsTodBm(Frequency frequency, Power rfDsa)
{
	Power offset(0.0f);

	std::shared_ptr<RxFrequencyBand> freqBand;
	if( !this->findFreqBand( frequency, freqBand ))
		return offset ;

	std::shared_ptr<RxFrequencyTable> freqTable;
	if( !freqBand->findFreqTable( frequency, freqTable) )
		return offset ;

	// Temperature correct
	RxPoint calPoint = freqTable->findPowerForDSASetting( rfDsa );
	offset = calPoint.dBFS2dBm;

	return offset;
}

Power Mplane::RxOpenLoop::dBfsTodBm(Frequency frequency, Power rfDsa,
		float temperature)
{
	Power offset(0.0f);

	std::shared_ptr<RxFrequencyBand> freqBand;
	if( !this->findFreqBand( frequency, freqBand ))
		return offset ;

	std::shared_ptr<RxFrequencyTable> freqTable;
	if( !freqBand->findFreqTable( frequency, freqTable) )
		return offset ;

	// Temperature correct
	float calTemp = freqTable->getTemperature();
	float tempCorr = ( temperature - calTemp ) * this->getCoefficient();
	RxPoint calPoint = freqTable->findPowerForDSASetting( rfDsa );
	offset = calPoint.dBFS2dBm + tempCorr;

	// Convert path (which may be of the form 11, 22 as well as the usual 1,2) into a port index
	unsigned path(getPath()) ;

	unsigned port = 0;
	//for paths where the port is encoded as the port * 10
	if( path > 10)
	{
		port = (path / 10) -1;  // integer divide gets the path index, -1 to convert to zero based port
	}
	else
	{
		port = path - 1;    // otherwise the port is the path (1 or 2 ) -1
	}

	std::shared_ptr<IRxAttenuators> rxAttenuators(IRxAttenuators::getInstance(port)) ;
	if (!rxAttenuators)
		return offset ;

	// output information for RSSI debug
//	eventInfo("RSSI: dBfsTodBm cal=%.2f dBm Temp correction=%.2f dB : Final dBFS2dBm %.2f dBm",
//			calPoint.dBFS2dBm.get(), tempCorr, offset.get());

	return offset;
}

const std::list<std::shared_ptr<RxFrequencyBand> >& Mplane::RxOpenLoop::getFrequencyBands() const
{
	return mFrequencyBands ;
}

bool Mplane::RxOpenLoop::findFreqBand(Frequency frequency, std::shared_ptr<RxFrequencyBand>& freqBand)
{
	std::list<std::shared_ptr<RxFrequencyBand>>::iterator it = mFrequencyBands.begin() ;
	if (it == mFrequencyBands.end())
		return false ;

	// For RX we may be applying "Howard's cunning scheme" which will push the LO centre beyond the calibrated data, so choose
	// the closest band we can

	// Check for freq below minimum in cal
	if (frequency < (*it)->getLower())
	{
		// use this
		freqBand = (*it);
		return true;
	}

	// search list
	std::shared_ptr<RxFrequencyBand> previous ;
	for( ; it != mFrequencyBands.end(); ++it )
	{
		freqBand = (*it);
		if( frequency >= freqBand->getLower() && frequency <= freqBand->getUpper())
		{
			return true;
		}

		// Not in this band, is it between the previous band and this one?
		if (previous)
		{
			if( frequency >= previous->getUpper() && frequency <= freqBand->getLower())
			{
				// use the closest band
				int distLower(frequency.getInt() - previous->getUpper().getInt()) ;
				int distUpper(freqBand->getLower().getInt() - frequency.getInt()) ;
				if (distUpper > distLower)
					freqBand = previous ;
				return true;
			}
		}
		previous = (*it) ;
	}

	// frequency must be above the bands, just return the maximum
	return true;
}

bool Mplane::RxOpenLoop::getNearestGainReduction(Power reduction, Frequency frequency, Power &nearestIFDSARed, Power &nearestGainRed)
{
	std::shared_ptr<RxFrequencyBand> freqBand;
	if( this->findFreqBand( frequency, freqBand ))
	{
		std::shared_ptr<IFAttenTable> attenTable = freqBand->getIFAttenTable();
		if (attenTable == NULL)
		{
			return false;
		}
		else
		{
			RxStep step = attenTable->findNearestGainRed( reduction );
			nearestIFDSARed = step.IFDSARed;
			nearestGainRed = step.GainRed;
			return true;
		}
	}
	else
	{
		return false;
	}
}


//=============================================================================================================
// RxCal
//=============================================================================================================

Mplane::RxCal::RxCal(const std::string& version, const std::string& country,
		const std::string& facility, const std::string& theoperator):
				mVersion( version ), mCountry( country ),
				mFacility( facility ), mOperator( theoperator)
{
}

Mplane::RxCal::~RxCal()
{
	mRxOpenLoopData.clear();
}

std::shared_ptr<IRxOpenLoop> Mplane::RxCal::getRxOpenLoop(int path)
{
	return mRxOpenLoopData[ path ];
}

void Mplane::RxCal::addRxOpenLoop(int path,
		std::shared_ptr<RxOpenLoop> rxOpenLoop)
{
	mRxOpenLoopData[path] = rxOpenLoop;
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RxCalData.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

// Use the ICalDownloadManagement class to get the installed file path
#include "ICalDownloadManagement.h"

#include "RxCalData.h"
#include "GlobalTypeDefs.h"
#include "Maths.h"

using namespace Mplane;

Mplane::RxCalData::RxCalData( std::shared_ptr<ICalDownload> calDownload ):
	CommonCalBase("RxCal", "HW"),
	mCalDownload( calDownload ),
	mCalFilePath( calDownload->getInstallFilePath() ),
	mCalPath(0)
{
}

Mplane::RxCalData::~RxCalData()
{
}

void Mplane::RxCalData::show()
{
}


ReturnType::State Mplane::RxCalData::load()
{
	ReturnType::State status = ReturnType::RT_OK;

	if( isLoaded() )
	{
		mRxCal = 0;  // deference the caldata shared pointer so that it gets deleted

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

	if (!parseRxCal(root_element))
	{
		eventError("Syntax error in cal file %s ", mCalFilePath.c_str());
		return ReturnType::RT_SYNTAX_ERROR;
	}
	setLoaded(true);
	return status;
}

std::shared_ptr<IRxOpenLoop> Mplane::RxCalData::getRxOpenLoop(int path)
{
	return mRxCal->getRxOpenLoop(path);
}

bool Mplane::RxCalData::parseRxCal(tinyxml2::XMLElement* node)
{

	if (node->Name() == RxCal::name) // is the first element the correct element?
	{
		AttrMap attributes;
		attributes["version"] = "";
		attributes["country"] = "";
		attributes["facility"] = "";
		attributes["operator"] = "";
		getAttributeMap(node, attributes);

		mRxCal = createRxCal(attributes["version"], attributes["country"],
						attributes["facility"], attributes["operator"]);

		for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
				cur_node; cur_node = cur_node->NextSiblingElement())
		{
			// Get the device definition inside board
			if (!extractRxOpenLoop(mRxCal, cur_node))
			{
				return false;
			}
		}
		return true;
	}
	return false;

}

bool Mplane::RxCalData::extractRxOpenLoop(
		std::shared_ptr<RxCal> mRxCal, tinyxml2::XMLElement* node)
{
	if (node->Name() == RxOpenLoop::name)    // is the The TxOpenLoop element?
	{
		tinyxml2::XMLElement* ele = node->FirstChildElement();

		if (ele->Name() == RxOpenLoop::PathStr)
		{
			mCalPath = atoi(ele->GetText());
			ele = ele->NextSiblingElement();
			std::string date = "";
			if (ele->Name() == RxOpenLoop::DateStr)
			{
				date = ele->GetText();
				ele = ele->NextSiblingElement();

				mCalDownload->addPath(mCalPath, date) ;

				// We need to extract the first temperature for each path
				mFirstTempPath.push_back(true);

				if (ele->Name() == RxOpenLoop::LinearTemperatureCompensation)
				{
					tinyxml2::XMLElement* tempEle = ele->FirstChildElement();
					if (tempEle->Name() == RxOpenLoop::CoefficientStr)
					{
						float tempCoeff = Maths::char2float(tempEle->GetText());
						ele = ele->NextSiblingElement();

						if (ele->Name() == RxOpenLoop::GainTargetStr)
						{
							float gainTarget = Maths::char2float(ele->GetText());
							std::shared_ptr<RxOpenLoop> rxOpenLoop(
								new RxOpenLoop(mCalPath, tempCoeff, date, gainTarget));
							mRxCal->addRxOpenLoop(mCalPath, rxOpenLoop);

							// now we have a list of Frequency Table elements to create.
							for (tinyxml2::XMLElement* cur_node =
									ele->NextSiblingElement(); cur_node; cur_node =
									cur_node->NextSiblingElement())
							{
								// Get the device definition inside board
								if (!extractFrequencyBand(rxOpenLoop, cur_node))
								{
									return false;
								}
							}
						}
						else
						{
							std::shared_ptr<RxOpenLoop> rxOpenLoop(
								new RxOpenLoop(mCalPath, tempCoeff, date));
							mRxCal->addRxOpenLoop(mCalPath, rxOpenLoop);

							// now we have a list of Frequency Table elements to create.
							// Go back one
							ele = ele->PreviousSiblingElement();
							for (tinyxml2::XMLElement* cur_node =
									ele->NextSiblingElement(); cur_node; cur_node =
									cur_node->NextSiblingElement())
							{
								// Get the device definition inside board
								if (!extractFrequencyBand(rxOpenLoop, cur_node))
								{
									return false;
								}
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

bool Mplane::RxCalData::extractFrequencyBand(
		std::shared_ptr<RxOpenLoop> rxOpenLoop, tinyxml2::XMLElement* node)
{
	if (node->Name() == RxFrequencyBand::name)   // is this a PowerBand element?
	{

		tinyxml2::XMLElement* ele = node->FirstChildElement();
		if (ele->Name() == RxFrequencyBand::UpperStr)
		{
			Frequency upper;
			upper.set(ele->GetText(), Frequency::KHz);
			ele = ele->NextSiblingElement();
			if (ele->Name() == RxFrequencyBand::LowerStr)
			{
				Frequency lower;
				lower.set(ele->GetText(), Frequency::KHz);
				ele = ele->NextSiblingElement();
				//Parse the IFDSA value and IF attenuation table if available for the frequency band
				if (ele->Name() == RxFrequencyBand::IFDSAStr)
				{
					Power ifDsa;
					ifDsa.set(ele->GetText());

					std::shared_ptr<RxFrequencyBand> freqBand(
							 new RxFrequencyBand(upper, lower, ifDsa));
					rxOpenLoop->addFrequencyBand(freqBand);

					ele = ele->NextSiblingElement();

					if (ele->Name() == IFAttenTable::name)
					{
						tinyxml2::XMLElement* cur_node = ele;

						// Get the device definition inside board
						if (!extractIFAttenTable(freqBand, cur_node))
						{
							return false;
						}
					}
					else
					{
						// Just go back one after sneaking look
						ele = ele->PreviousSiblingElement();
					}

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
				}
				//If IFDSA setting is not available here, then it is assumed that it is specific to frequency table
				else
				{
					// Just go back one after sneaking look
					ele = ele->PreviousSiblingElement();

					std::shared_ptr<RxFrequencyBand> freqBand(
							 new RxFrequencyBand(upper, lower));
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

				}

				return true;    // we have completed the power band table OK
			}
		}
	}

	return false;

}

bool Mplane::RxCalData::extractIFAttenTable(
		std::shared_ptr<RxFrequencyBand> frequencyBand,
		tinyxml2::XMLElement* node)
{
	if (node->Name() == IFAttenTable::name) // is this a IFAttenTable element?
	{

		std::shared_ptr<IFAttenTable> iFAttenTable(
				new IFAttenTable());

		frequencyBand->addIFAttenTable(iFAttenTable);

		// now we have to add our power tables to the frequency table.
		for (tinyxml2::XMLElement* cur_node = node->FirstChildElement();
				cur_node; cur_node = cur_node->NextSiblingElement())
		{
			// Get the device definition inside board
			if (!extractCalSteps(iFAttenTable, cur_node))
			{
				return false;
			}
		}
		return true; // we have completed Frequency Table OK
	}
	return false;
}

bool Mplane::RxCalData::extractFrequencyTable(
		std::shared_ptr<RxFrequencyBand> frequencyBand,
		tinyxml2::XMLElement* node)
{
	if (node->Name() == RxFrequencyTable::name) // is this a FrequencyTable element?
	{
		tinyxml2::XMLElement* ele = node->FirstChildElement();
		Frequency frequency(0.0);
		if (ele->Name() == RxFrequencyTable::FrequencyStr)
		{
			frequency.set(ele->GetText(), Frequency::KHz);

			ele = ele->NextSiblingElement();
			if (ele->Name() == RxFrequencyTable::TemperatureStr)
			{
				Temperature temperature;
				temperature.set(ele->GetText());

				// Capture the first temperature in the table for each path.
				int path = 0;

				if(mCalPath > 10)
				{
					path = mCalPath - 11;
				}
				else
				{
					path = mCalPath;
				}

				if(true == mFirstTempPath[path])
				{
					mCalDownload->addTemperature(mCalPath, temperature.get());

					mFirstTempPath[path] = false;
				}

				//If IFDSA setting is specific to each frequency table, then check if that is available in the cal file
				if (frequencyBand->getIfDsaLoc() == RxFrequencyBand::IfDsaLoc::PerFreqTable)
				{
					ele = ele->NextSiblingElement();
					if (ele->Name() == RxFrequencyTable::ifDSAStr)
					{
						Power ifDsa;
						ifDsa.set(ele->GetText());

						std::shared_ptr<RxFrequencyTable> frequencyTable(
								new RxFrequencyTable(frequency, temperature.get(), ifDsa));

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
					}
					else
					{
						return false;
					}
				}
				else
				{
					std::shared_ptr<RxFrequencyTable> frequencyTable(
							new RxFrequencyTable(frequency, temperature.get()));

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
				}

				return true; // we have completed Frequency Table OK
			}
		}
	}
	return false;
}

bool Mplane::RxCalData::extractCalSteps(
		std::shared_ptr<IFAttenTable> iFAttenTable,
		tinyxml2::XMLElement* node)
{
	if (node->Name() != IFAttenTable::StepStr) // is this a Step element?
		return false ;

	tinyxml2::XMLElement* ele = node->FirstChildElement();
	if (ele->Name() != IFAttenTable::GainRedStr)
		return false ;

	const char* gainVal(ele->GetText()) ;
	ele = ele->NextSiblingElement();

	if (ele->Name() != IFAttenTable::IFDSARedStr)
		return false ;

	const char* dsaVal(ele->GetText()) ;

	RxStep step;

	if (gainVal)
		step.GainRed.set(gainVal);

	if (dsaVal)
		step.IFDSARed.set(dsaVal);

	iFAttenTable->addRxStep(step);
	return true;
}

bool Mplane::RxCalData::extractCalPoints(
		std::shared_ptr<RxFrequencyTable> frequencyTable,
		tinyxml2::XMLElement* node)
{
	if (node->Name() != RxFrequencyTable::PointStr) // is this a Points element?
		return false ;

	tinyxml2::XMLElement* ele = node->FirstChildElement();
	if (ele->Name() != RxFrequencyTable::rfDSAStr)
		return false ;

	const char* dsaVal(ele->GetText()) ;
	ele = ele->NextSiblingElement();

	if (ele->Name() != RxFrequencyTable::dBFS2dBmStr)
		return false ;

	const char* dfsVal(ele->GetText()) ;

	RxPoint point;

	if (dsaVal)
		point.rfDSA.set(dsaVal);

	if (dfsVal)
		point.dBFS2dBm.set(dfsVal);

	frequencyTable->addRxPoint(point);
	return true;
}

void Mplane::RxCalData::getAttributeMap(tinyxml2::XMLElement* node,
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

std::shared_ptr<RxCal> Mplane::RxCalData::createRxCal(
		const std::string& version, const std::string& country,
		const std::string& facility, const std::string& theoperator)
{
	return std::make_shared<RxCal>(version, country, facility, theoperator) ;
}

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierFreqBand_unittest.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <string>
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>


#include "CarrierFreqMgr/CarrierFreq.h"
#include "CarrierFreqMgr/CarrierFreqBand.h"

#include "CommonCarrierServer_fixture.h"


namespace Mplane {

class SimpleFrequencyPolicy : public virtual ICarrierFreqPolicy {
public:
	SimpleFrequencyPolicy() {}
	virtual ~SimpleFrequencyPolicy() {}

	/**
	 * "function" call which calculates the centre frequency based on the provided data
	 */
	virtual Frequency calcCentre(unsigned port, const Frequency& centre, const Frequency& bundleMin, const Frequency& bundleMax) override
	{
		// calc centre of bundle
		Frequency bandwidth(bundleMax - bundleMin) ;
		return bundleMin + (bandwidth/2.0) ;
	}

	virtual bool checkBundle(unsigned port,
			const Frequency& bandMin, const Frequency& bandMax,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override
	{
		// Check against end stops
		if (bundleMax > bandMax)
		{
			std::stringstream ss ;
			ss << "Maximum frequency " << bundleMax << " greater than limit " << bandMax ;
			errorString = ss.str() ;
			return false ;
		}
		if (bundleMin < bandMin)
		{
			std::stringstream ss ;
			ss << "Minimum frequency " << bundleMin << " less than limit " << bandMin ;
			errorString = ss.str() ;
			return false ;
		}

		return true ;

	}

	/**
	 * Check the LO centre covers the carrier bundle. If centre is outside bounds sets the errorString
	 * @param port
	 * @param centre
	 * @param halfBandwidth
	 * @param bundleMin
	 * @param bundleMax
	 * @param errorString
	 * @return true if centre within bounds
	 */
	virtual bool checkCentre(unsigned port, const Frequency& centre,
			const Frequency& halfBandwidth,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override
	{
		// Now check against the centre
		Frequency loMax(centre + halfBandwidth) ;
		if (bundleMax > loMax)
		{
			std::stringstream ss ;
			ss << "Maximum frequency " << bundleMax << " outside LO bandwidth. Max " << loMax ;
			errorString = ss.str() ;
			return false ;
		}

		Frequency loMin(centre - halfBandwidth) ;
		if (bundleMin < loMin)
		{
			std::stringstream ss ;
			ss << "Minimum frequency " << bundleMin << " outside LO bandwidth. Min " << loMin ;
			errorString = ss.str() ;
			return false ;
		}

		return true ;

	}

};

class NoMoveFrequencyPolicy : public virtual ICarrierFreqPolicy {
public:
	NoMoveFrequencyPolicy() {}
	virtual ~NoMoveFrequencyPolicy() {}

	/**
	 * "function" call which calculates the centre frequency based on the provided data
	 */
	virtual Frequency calcCentre(unsigned port, const Frequency& centre, const Frequency& bundleMin, const Frequency& bundleMax) override
	{
		return centre ;
	}

	virtual bool checkBundle(unsigned port,
			const Frequency& bandMin, const Frequency& bandMax,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override
	{
		// Check against end stops
		if (bundleMax > bandMax)
		{
			std::stringstream ss ;
			ss << "Maximum frequency " << bundleMax << " greater than limit " << bandMax ;
			errorString = ss.str() ;
			return false ;
		}
		if (bundleMin < bandMin)
		{
			std::stringstream ss ;
			ss << "Minimum frequency " << bundleMin << " less than limit " << bandMin ;
			errorString = ss.str() ;
			return false ;
		}

		return true ;

	}

	/**
	 * Check the LO centre covers the carrier bundle. If centre is outside bounds sets the errorString
	 * @param port
	 * @param centre
	 * @param halfBandwidth
	 * @param bundleMin
	 * @param bundleMax
	 * @param errorString
	 * @return true if centre within bounds
	 */
	virtual bool checkCentre(unsigned port, const Frequency& centre,
			const Frequency& halfBandwidth,
			const Frequency& bundleMin, const Frequency& bundleMax,
			std::string& errorString) override
	{
		// Now check against the centre
		Frequency loMax(centre + halfBandwidth) ;
		if (bundleMax > loMax)
		{
			std::stringstream ss ;
			ss << "Maximum frequency " << bundleMax << " outside LO bandwidth. Max " << loMax ;
			errorString = ss.str() ;
			return false ;
		}

		Frequency loMin(centre - halfBandwidth) ;
		if (bundleMin < loMin)
		{
			std::stringstream ss ;
			ss << "Minimum frequency " << bundleMin << " outside LO bandwidth. Min " << loMin ;
			errorString = ss.str() ;
			return false ;
		}

		return true ;

	}
};

}


using namespace std;

using namespace Mplane;

//=============================================================================================================
// TEST FIXTURE
//=============================================================================================================
class CarrierFreqBandTestFixture : public CommonCarrierServerTestFixture {
public:
	void testCarrierFreq(const CarrierFreq& carrierFreq, const Frequency& centre, const Frequency& bandwidth)
	{
		Frequency min(centre - bandwidth/2.0) ;
		Frequency max(centre + bandwidth/2.0) ;
		EXPECT_EQ(centre, carrierFreq.getCentre()) ;
		EXPECT_EQ(min, carrierFreq.getMin()) ;
		EXPECT_EQ(max, carrierFreq.getMax()) ;

	}

	void testCarrierFreqBand(const CarrierFreqBand& freqBand, const Frequency& centre, const Frequency& min, const Frequency& max)
	{
		EXPECT_EQ(centre, freqBand.getCentre()) ;
		EXPECT_EQ(min, freqBand.getMinFrequency()) ;
		EXPECT_EQ(max, freqBand.getMaxFrequency()) ;
	}

	void testAddBase(CarrierFreqBand& freqBand, unsigned index, const CarrierFreq& carrierFreq, bool autoCentre = false, bool expectPass = true)
	{
		std::string failReason ;

		std::shared_ptr<ICarrierFreqPolicy> policy ;
		if (autoCentre)
		{
			policy = std::make_shared<SimpleFrequencyPolicy>() ;
		}
		else
		{
			policy = std::make_shared<NoMoveFrequencyPolicy>() ;
		}

		Frequency newCentre ;
		if (expectPass)
		{
			EXPECT_TRUE(freqBand.canFit(index, carrierFreq, policy, newCentre, failReason)) ;
			EXPECT_TRUE(failReason.empty()) ;
			if (!failReason.empty())
				std::cerr << "ADD: Unexpected error in canFit(): " << failReason << std::endl ;
			EXPECT_TRUE(freqBand.add(index, carrierFreq, policy, failReason)) ;
			EXPECT_TRUE(failReason.empty()) ;
			if (!failReason.empty())
				std::cerr << "ADD: Unexpected error in add(): " << failReason << std::endl ;
		}
		else
		{

			EXPECT_FALSE(freqBand.canFit(index, carrierFreq, policy, newCentre, failReason)) ;
			EXPECT_FALSE(failReason.empty()) ;
			EXPECT_FALSE(freqBand.add(index, carrierFreq, policy, failReason)) ;
			EXPECT_FALSE(failReason.empty()) ;
		}
	}

	void testDelBase(CarrierFreqBand& freqBand, unsigned index, bool autoCentre = false, bool expectPass = true)
	{
		std::string failReason ;

		std::shared_ptr<ICarrierFreqPolicy> policy ;
		if (autoCentre)
		{
			policy = std::make_shared<SimpleFrequencyPolicy>() ;
		}
		else
		{
			policy = std::make_shared<NoMoveFrequencyPolicy>() ;
		}

		if (expectPass)
		{
			EXPECT_TRUE(freqBand.del(index, policy, failReason)) ;
			EXPECT_TRUE(failReason.empty()) ;
			if (!failReason.empty())
				std::cerr << "DEL: Unexpected error in del(): " << failReason << std::endl ;
		}
		else
		{

			EXPECT_FALSE(freqBand.del(index, policy, failReason)) ;
			EXPECT_FALSE(failReason.empty()) ;
		}
	}

	void testAddNoMove(CarrierFreqBand& freqBand, unsigned index, const CarrierFreq& carrierFreq, bool expectPass = true)
	{
		return testAddBase(freqBand, index, carrierFreq, false, expectPass) ;
	}

	void testDelNoMove(CarrierFreqBand& freqBand, unsigned index, bool expectPass = true)
	{
		return testDelBase(freqBand, index, false, expectPass) ;
	}

	void testAdd(CarrierFreqBand& freqBand, unsigned index, const CarrierFreq& carrierFreq, bool expectPass = true)
	{
		return testAddBase(freqBand, index, carrierFreq, true, expectPass) ;
	}

	void testDel(CarrierFreqBand& freqBand, unsigned index, bool expectPass = true)
	{
		return testDelBase(freqBand, index, true, expectPass) ;
	}


};

//=============================================================================================================
// TESTS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFreqBandTestFixture, Basic)
{
	Frequency loBandwidth(50.0, Frequency::MHz) ;
	Frequency bandMin(1800.0, Frequency::KHz) ;
	Frequency bandMax(2200.0, Frequency::KHz) ;
	Frequency centre(2000.0, Frequency::KHz) ;
	CarrierFreqBand freqBand("test", 0, loBandwidth, bandMin, bandMax, centre) ;

	Frequency loMin(centre - loBandwidth/2.0) ;
	Frequency loMax(centre + loBandwidth/2.0) ;

	EXPECT_EQ(centre, freqBand.getCentre()) ;
	EXPECT_EQ(Frequency(0.0), freqBand.getMinFrequency()) ;
	EXPECT_EQ(Frequency(0.0), freqBand.getMaxFrequency()) ;

	// Can't delete from empty list
	std::string failReason ;
	EXPECT_FALSE(freqBand.del(0, std::make_shared<SimpleFrequencyPolicy>(), failReason)) ;
	EXPECT_FALSE(failReason.empty()) ;
}

//-------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFreqBandTestFixture, StationaryCentre)
{
	// Start with an LO bandwidth of:
	//
	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                |                                                |
	//   +------------------------------------------------+------------------------------------------------+
	//
	Frequency loBandwidth(50.0, Frequency::MHz) ;
	Frequency bandMin(1800.0, Frequency::MHz) ;
	Frequency bandMax(2200.0, Frequency::MHz) ;
	Frequency centre(2000.0, Frequency::MHz) ;
	CarrierFreqBand freqBand("test", 0, loBandwidth, bandMin, bandMax, centre) ;

	// With Frequencies added it will be:
	//
	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |   1980        1990                                           2010                               |
	//   |-----+-----| |---+---|                            |-------------+-------------|                  |
	//   |1975    1985                                      2002.5     15M [0]     2017.5                  |
	//   |    10M         5M                                                                               |
	//   |    [3]         [1]                                                      2015                    |
	//   |                                                     |---------------------+---------------------|
	//   |                                                     2005              20M [2]              2025 |
	//   |                                                                                                 |
	//

	CarrierFreq cf5MHz(Frequency(1990000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE5) ;
	CarrierFreq cf10MHz(Frequency(1980000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE10) ;
	CarrierFreq cf15MHz(Frequency(2010000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE15) ;
	CarrierFreq cf20MHz(Frequency(2015000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE20) ;
	CarrierFreq cfMin(Frequency(1974000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE20) ;
	CarrierFreq cfMax(Frequency(2026000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE20) ;

	std::string failReason ;

	// Can't add frequencies below/above endstops
	std::cerr << "Try adding carrier below min" << std::endl ;
	testAddNoMove(freqBand, 0, cfMin, false) ;
	std::cerr << "Try adding carrier above max" << std::endl ;
	testAddNoMove(freqBand, 0, cfMax, false) ;

	// Add frequencies
	unsigned index{0};


	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |                                                              2010                               |
	//   |                                                  |-------------+-------------|                  |
	//   |                                                  2002.5     15M [0]     2017.5                  |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//
	std::cerr << "Add 15MHz carrier" << std::endl ;
	testAddNoMove(freqBand, index, cf15MHz) ;
	++index ;
	testCarrierFreqBand(freqBand, centre, Frequency(2002500.0, Frequency::KHz), Frequency(2017500.0, Frequency::KHz)) ;

//	EXPECT_FALSE(freqBand.add(0, cf15MHz, std::make_shared<NoMoveFrequencyPolicy>(), failReason)) ; // can't add with same index
//	EXPECT_FALSE(failReason.empty()) ;

	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |               1990                                           2010                               |
	//   |             |---+---|                            |-------------+-------------|                  |
	//   |          1987.5   1992.5                         2002.5     15M [0]     2017.5                  |
	//   |                5M [1]                                                                           |
	//   |                                                                                                 |
	//
	std::cerr << "Add 5MHz carrier" << std::endl ;
	testAddNoMove(freqBand, index, cf5MHz) ;
	++index ;
	testCarrierFreqBand(freqBand, centre, Frequency(1987500.0, Frequency::KHz), Frequency(2017500.0, Frequency::KHz)) ;

	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |               1990                                           2010                               |
	//   |             |---+---|                            |-------------+-------------|                  |
	//   |                                                  2002.5     15M [0]     2017.5                  |
	//   |                5M [1]                                                                           |
	//   |                                                                         2015                    |
	//   |                                                     |---------------------+---------------------|
	//   |                                                     2005              20M [2]              2025 |
	//   |                                                                                                 |
	//
	std::cerr << "Add 20MHz carrier" << std::endl ;
	testAddNoMove(freqBand, index, cf20MHz) ;
	++index ;
	testCarrierFreqBand(freqBand, centre, Frequency(1987500.0, Frequency::KHz), Frequency(2025000.0, Frequency::KHz)) ;

	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |   1980        1990                                           2010                               |
	//   |-----+-----| |---+---|                            |-------------+-------------|                  |
	//   |1975    1985                                      2002.5     15M [0]     2017.5                  |
	//   |    10M [3]     5M [1]                                                                           |
	//   |                                                                         2015                    |
	//   |                                                     |---------------------+---------------------|
	//   |                                                     2005              20M [2]              2025 |
	//   |                                                                                                 |
	//
	std::cerr << "Add 10MHz carrier" << std::endl ;
	testAddNoMove(freqBand, index, cf10MHz) ;
	++index ;
	testCarrierFreqBand(freqBand, centre, Frequency(1975000.0, Frequency::KHz), Frequency(2025000.0, Frequency::KHz)) ;


	// Delete frequencies

	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |   1980        1990                                           2010                               |
	//   |-----+-----| |---+---|                            |-------------+-------------|                  |
	//   |1975    1985                                      2002.5     15M [0]     2017.5                  |
	//   |    10M         5M                                                                               |
	//   |    [3]         [1]                                                                              |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//
	std::cerr << "Del 20MHz carrier" << std::endl ;
	testDelNoMove(freqBand, 2) ;
	testCarrierFreqBand(freqBand, centre, Frequency(1975000.0, Frequency::KHz), Frequency(2017500.0, Frequency::KHz)) ;

	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |   1980        1990                                                                              |
	//   |-----+-----| |---+---|                                                                           |
	//   |1975    1985                                                                                     |
	//   |    10M [3]     5M [1]                                                                           |
	//   |                                                                                                 |
	//
	std::cerr << "Del 15MHz carrier" << std::endl ;
	testDelNoMove(freqBand, 0) ;
	testCarrierFreqBand(freqBand, centre, Frequency(1975000.0, Frequency::KHz), Frequency(1992500.0, Frequency::KHz)) ;

	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |               1990                                                                              |
	//   |             |---+---|                                                                           |
	//   |                                                                                                 |
	//   |                5M [1]                                                                           |
	//   |                                                                                                 |
	//
	std::cerr << "Del 10MHz carrier" << std::endl ;
	testDelNoMove(freqBand, 3) ;
	testCarrierFreqBand(freqBand, centre, Frequency(1987500.0, Frequency::KHz), Frequency(1992500.0, Frequency::KHz)) ;

	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//
	std::cerr << "Del 5MHz carrier" << std::endl ;
	testDelNoMove(freqBand, 1) ;
	testCarrierFreqBand(freqBand, centre, Frequency(0.0, Frequency::KHz), Frequency(0.0, Frequency::KHz)) ;

}


//-------------------------------------------------------------------------------------------------------------
TEST_F(CarrierFreqBandTestFixture, AutoCentre)
{
	// Start with an LO bandwidth of:
	//
	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                |                                                |
	//   +------------------------------------------------+------------------------------------------------+
	//
	Frequency loBandwidth(50.0, Frequency::MHz) ;
	Frequency bandMin(1800.0, Frequency::MHz) ;
	Frequency bandMax(2025.0, Frequency::MHz) ;
	Frequency centre(2000.0, Frequency::MHz) ;
	CarrierFreqBand freqBand("test", 0, loBandwidth, bandMin, bandMax, centre) ;

	// With Frequencies added it will be:
	//
	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |   1980        1990                                           2010                               |
	//   |-----+-----| |---+---|                            |-------------+-------------|                  |
	//   |1975    1985                                      2002.5     15M [0]     2017.5                  |
	//   |    10M         5M                                                                               |
	//   |    [3]         [1]                                                      2015                    |
	//   |                                                     |---------------------+---------------------|
	//   |                                                     2005              20M [2]              2025 |
	//   |                                                                                                 |
	//

	CarrierFreq cf5MHz(Frequency(1990000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE5) ;
	CarrierFreq cf10MHz(Frequency(1980000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE10) ;
	CarrierFreq cf15MHz(Frequency(2010000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE15) ;
	CarrierFreq cf20MHz(Frequency(2015000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE20) ;
	CarrierFreq cfMin(Frequency(1979000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE20) ;
	CarrierFreq cfMax(Frequency(2016000.0, Frequency::KHz), ICarrier::CARRTYPE_LTE20) ;

	std::string failReason ;

	// Can't add frequencies below/above endstops
	std::cerr << "Try adding carrier below min" << std::endl ;
	testAddNoMove(freqBand, 0, cfMin, false) ;
	std::cerr << "Try adding carrier above max" << std::endl ;
	testAddNoMove(freqBand, 0, cfMax, false) ;

	// Add frequencies
	unsigned index{0};


	// 1975                                                             2010                             2025
	//   |                                                                ^                                |
	//   |                                                                                                 |
	//   |                                                              2010                               |
	//   |                                                  |-------------+-------------|                  |
	//   |                                                  2002.5     15M [0]     2017.5                  |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//
	std::cerr << "Add 15MHz carrier" << std::endl ;
	testAdd(freqBand, index, cf15MHz) ;
	++index ;
	testCarrierFreqBand(freqBand,  Frequency(2010000.0, Frequency::KHz), Frequency(2002500.0, Frequency::KHz), Frequency(2017500.0, Frequency::KHz)) ;

//	EXPECT_FALSE(freqBand.add(0, cf15MHz, std::make_shared<NoMoveFrequencyPolicy>(), failReason)) ; // can't add with same index
//	EXPECT_FALSE(failReason.empty()) ;

	// 1975                                             2002.5                                           2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |               1990                                           2010                               |
	//   |             |---+---|                            |-------------+-------------|                  |
	//   |          1987.5   1992.5                         2002.5     15M [0]     2017.5                  |
	//   |                5M [1]                                                                           |
	//   |                                                                                                 |
	//
	std::cerr << "Add 5MHz carrier" << std::endl ;
	testAdd(freqBand, index, cf5MHz) ;
	++index ;
	testCarrierFreqBand(freqBand, Frequency(2002500.0, Frequency::KHz), Frequency(1987500.0, Frequency::KHz), Frequency(2017500.0, Frequency::KHz)) ;

	// 1975                                                    2006.25                                   2025
	//   |                                                       ^                                         |
	//   |                                                                                                 |
	//   |               1990                                           2010                               |
	//   |             |---+---|                            |-------------+-------------|                  |
	//   |                                                  2002.5     15M [0]     2017.5                  |
	//   |                5M [1]                                                                           |
	//   |                                                                         2015                    |
	//   |                                                     |---------------------+---------------------|
	//   |                                                     2005              20M [2]              2025 |
	//   |                                                                                                 |
	//
	std::cerr << "Add 20MHz carrier" << std::endl ;
	testAdd(freqBand, index, cf20MHz) ;
	++index ;
	testCarrierFreqBand(freqBand, Frequency(2006250.0, Frequency::KHz), Frequency(1987500.0, Frequency::KHz), Frequency(2025000.0, Frequency::KHz)) ;

	// 1975                                             2000                                             2025
	//   |                                                ^                                                |
	//   |                                                                                                 |
	//   |   1980        1990                                           2010                               |
	//   |-----+-----| |---+---|                            |-------------+-------------|                  |
	//   |1975    1985                                      2002.5     15M [0]     2017.5                  |
	//   |    10M [3]     5M [1]                                                                           |
	//   |                                                                         2015                    |
	//   |                                                     |---------------------+---------------------|
	//   |                                                     2005              20M [2]              2025 |
	//   |                                                                                                 |
	//
	std::cerr << "Add 10MHz carrier" << std::endl ;
	testAdd(freqBand, index, cf10MHz) ;
	++index ;
	testCarrierFreqBand(freqBand, centre, Frequency(1975000.0, Frequency::KHz), Frequency(2025000.0, Frequency::KHz)) ;


	// Delete frequencies

	// 1975                               1996.25                                                        2025
	//   |                                   ^                                                             |
	//   |                                                                                                 |
	//   |   1980        1990                                           2010                               |
	//   |-----+-----| |---+---|                            |-------------+-------------|                  |
	//   |1975    1985                                      2002.5     15M [0]     2017.5                  |
	//   |    10M         5M                                                                               |
	//   |    [3]         [1]                                                                              |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//
	std::cerr << "Del 20MHz carrier" << std::endl ;
	testDel(freqBand, 2) ;
	testCarrierFreqBand(freqBand, Frequency(1996250.0, Frequency::KHz), Frequency(1975000.0, Frequency::KHz), Frequency(2017500.0, Frequency::KHz)) ;

	// 1975       1983.75                                                                                2025
	//   |          ^                                                                                      |
	//   |                                                                                                 |
	//   |   1980        1990                                                                              |
	//   |-----+-----| |---+---|                                                                           |
	//   |1975    1985        1992.5                                                                       |
	//   |    10M [3]     5M [1]                                                                           |
	//   |                                                                                                 |
	//
	std::cerr << "Del 15MHz carrier" << std::endl ;
	testDel(freqBand, 0) ;
	testCarrierFreqBand(freqBand, Frequency(1983750.0, Frequency::KHz), Frequency(1975000.0, Frequency::KHz), Frequency(1992500.0, Frequency::KHz)) ;

	// 1975              1990                                                                            2025
	//   |                 ^                                                                               |
	//   |                                                                                                 |
	//   |               1990                                                                              |
	//   |             |---+---|                                                                           |
	//   |                                                                                                 |
	//   |                5M [1]                                                                           |
	//   |                                                                                                 |
	//
	std::cerr << "Del 10MHz carrier" << std::endl ;
	testDel(freqBand, 3) ;
	testCarrierFreqBand(freqBand, Frequency(1990000.0, Frequency::KHz), Frequency(1987500.0, Frequency::KHz), Frequency(1992500.0, Frequency::KHz)) ;

	// 1975               1990                                                                           2025
	//   |                  ^                                                                              |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//   |                                                                                                 |
	//
	std::cerr << "Del 5MHz carrier" << std::endl ;
	testDel(freqBand, 1) ;
	testCarrierFreqBand(freqBand, Frequency(1990000.0, Frequency::KHz), Frequency(0.0, Frequency::KHz), Frequency(0.0, Frequency::KHz)) ;

}

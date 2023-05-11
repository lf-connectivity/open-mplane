/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierBundle.cpp
 * \brief     Model fibres
 *
 *
 * \details   Manage carriers enabled on an antenna
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <map>

#include "CarrierBundle.h"

using namespace Mplane;


//=================================================================================================
// DEBUG
#ifdef OFF_TARGET
const bool debug = true ;
#else
const bool debug = false ;
#endif


//=================================================================================================
// TYPES

// TODO: Sort out the CPG table (which is Xilinx-specific!) into something more generic
const unsigned HW_CFR_STAGES = 3 ;

// Entry in the carrier bundle CFR update table
struct carrier_bundle_update_struct {
	float thresholds[HW_CFR_STAGES] ;
};

//=================================================================================================
// CONSTANTS
const std::map<ICarrierBundle::BundleBw, std::string> BW_NAMES{
	{ICarrierBundle::CB_BW_0,		"0M"},
	{ICarrierBundle::CB_BW_1M4,		"1.4M"},
	{ICarrierBundle::CB_BW_3,		"3M"},
	{ICarrierBundle::CB_BW_5,		"5M"},
	{ICarrierBundle::CB_BW_10,		"10M"},
	{ICarrierBundle::CB_BW_20,		"20M"},
	{ICarrierBundle::CB_BW_30,		"30M"},
	{ICarrierBundle::CB_BW_40,		"40M"},
	{ICarrierBundle::CB_BW_50,		"50M"},
	{ICarrierBundle::CB_BW_60,		"60M"},
	{ICarrierBundle::CB_BW_70,		"70M"},
	{ICarrierBundle::CB_BW_80,		"80M"},
	{ICarrierBundle::CB_BW_90,		"90M"},
	{ICarrierBundle::CB_BW_100,		"100M"},
} ;

const std::map<ICarrierBundle::BundleGap, std::string> GAP_NAMES{
	{ICarrierBundle::CB_GAP_0,		"0M"},
	{ICarrierBundle::CB_GAP_10,		"10M"},
	{ICarrierBundle::CB_GAP_20,		"20M"},
	{ICarrierBundle::CB_GAP_30,		"30M"},
	{ICarrierBundle::CB_GAP_40,		"40M"},
	{ICarrierBundle::CB_GAP_50,		"50M"},
	{ICarrierBundle::CB_GAP_60,		"60M"},
	{ICarrierBundle::CB_GAP_70,		"70M"},
	{ICarrierBundle::CB_GAP_80,		"80M"},
	{ICarrierBundle::CB_GAP_90,		"90M"},
} ;

const float DEFAULT_THRESHOLD(7.5) ;

//=================================================================================================
// DATA

// Table of carrier bundle adjustments based on total BW and max gap
static struct carrier_bundle_update_struct bundleTable[ICarrierBundle::CB_BW_MAX+1][ICarrierBundle::CB_GAP_MAX+1] = {
#if 0
//  [CB_BW_0] =
  {
//      [CB_GAP_0]  =
    { /* thresholds */ {6.70, 6.70, 6.80} },    // default
//   [CB_GAP_10] =
    { /* thresholds */ {6.70, 6.70, 6.80} },    // N/A
//   [CB_GAP_20] =
    { /* thresholds */ {6.70, 6.70, 6.80} },    // N/A
//   [CB_GAP_30] =
    { /* thresholds */ {6.70, 6.70, 6.80} },    // N/A
//   [CB_GAP_40] =
    { /* thresholds */ {6.70, 6.70, 6.80} },    // N/A
  },

//  [CB_BW_1M4] =
  {
//      [CB_GAP_0]  =
    { /* thresholds */ {6.50, 6.50, 6.60} },    // 1.4
//   [CB_GAP_10] =
    { /* thresholds */ {6.50, 6.50, 6.60} },    // N/A
//   [CB_GAP_20] =
    { /* thresholds */ {6.50, 6.50, 6.60} },    // N/A
//   [CB_GAP_30] =
    { /* thresholds */ {6.50, 6.50, 6.60} },    // N/A
//   [CB_GAP_40] =
    { /* thresholds */ {6.50, 6.50, 6.60} },
  },

//  [CB_BW_3] =
{
//      [CB_GAP_0]  =
  { /* thresholds */ {6.50, 6.50, 6.60} },    // 3
//   [CB_GAP_10] =
  { /* thresholds */ {6.50, 6.50, 6.60} },    // N/A
//   [CB_GAP_20] =
  { /* thresholds */ {6.50, 6.50, 6.60} },    // N/A
//   [CB_GAP_30] =
  { /* thresholds */ {6.50, 6.50, 6.60} },    // N/A
//   [CB_GAP_40] =
  { /* thresholds */ {6.50, 6.50, 6.60} },
},

//  [CB_BW_5] =
  {
//      [CB_GAP_0]  =
	{ /* thresholds */ {6.50, 6.50, 6.60} },    // 5
//   [CB_GAP_10] =
	{ /* thresholds */ {6.50, 6.50, 6.60} },    // N/A
//   [CB_GAP_20] =
	{ /* thresholds */ {6.50, 6.50, 6.60} },    // N/A
//   [CB_GAP_30] =
	{ /* thresholds */ {6.50, 6.50, 6.60} },    // N/A
//   [CB_GAP_40] =
	{ /* thresholds */ {6.50, 6.50, 6.60} },
  },

//  [CB_BW_10] =
  {
//      [CB_GAP_0]  =
    { /* thresholds */ {6.20, 6.20, 6.30} },    // 10 5+5
//   [CB_GAP_10] =
    { /* thresholds */ {6.20, 6.20, 6.80} },    // N/A
//   [CB_GAP_20] =
    { /* thresholds */ {6.20, 6.20, 6.80} },    // N/A
//   [CB_GAP_30] =
    { /* thresholds */ {6.20, 6.20, 6.80} },    // N/A
//   [CB_GAP_40] =
    { /* thresholds */ {6.20, 6.20, 6.80} },    // N/A
  },

//  [CB_BW_20] =
  {
//      [CB_GAP_0]  =
    { /* thresholds */ {6.20, 6.20, 6.30} },    // 20 5+5+5 ##### Raised 0.2 dB from Felix 1.5.9
//   [CB_GAP_10] =
    { /* thresholds */ {6.40, 6.40, 6.50} },    // 5GG5 #### N/A
//   [CB_GAP_20] =
    { /* thresholds */ {6.40, 6.40, 6.50} },    // N/A
//   [CB_GAP_30] =
    { /* thresholds */ {6.40, 6.40, 6.50} },    // N/A
//   [CB_GAP_40] =
    { /* thresholds */ {6.40, 6.40, 6.50} },    // N/A
  },

//  [CB_BW_30] =
  {
//      [CB_GAP_0]  =
    { /* thresholds */ {6.20, 6.20, 6.30} },    // 10+10+10 #### N/A
//   [CB_GAP_10] =
    { /* thresholds */ {6.50, 6.50, 6.60} },    // 10G10 #### N/A
//   [CB_GAP_20] =
    { /* thresholds */ {6.40, 6.40, 6.50} },    // 5GGGG5 #### N/A
//   [CB_GAP_30] =
    { /* thresholds */ {6.60, 6.60, 6.70} },    // N/A
//   [CB_GAP_40] =
    { /* thresholds */ {6.60, 6.60, 6.70} },    // N/A
  },

//  [CB_BW_40] =
  {
//      [CB_GAP_0]  =
    { /* thresholds */ {6.20, 6.20, 6.30} },    // 20+20 #### N/A
//   [CB_GAP_10] =
    { /* thresholds */ {6.60, 6.60, 6.70} },    // 10+10G10 #### N/A
//   [CB_GAP_20] =
    { /* thresholds */ {6.80, 6.80, 6.90} },    // 10GG10 #### N/A
//   [CB_GAP_30] =
    { /* thresholds */ {6.60, 6.60, 6.70} },    // N/A
//   [CB_GAP_40] =
    { /* thresholds */ {6.60, 6.60, 6.70} },    // N/A
  },

//  [CB_BW_50] =
  {
//      [CB_GAP_0]  =
    { /* thresholds */ {6.20, 6.20, 6.30} },    // 20+20+10 #### N/A
//   [CB_GAP_10] =
    { /* thresholds */ {6.20, 6.20, 6.30} },    // 20G20 #### N/A
//   [CB_GAP_20] =
    { /* thresholds */ {6.60, 6.60, 6.70} },    // 10GG10+10 #### N/A
//   [CB_GAP_30] =
    { /* thresholds */ {6.60, 6.60, 6.70} },    // N/A
//   [CB_GAP_40] =
    { /* thresholds */ {6.60, 6.60, 6.70} },    // N/A
  },
#endif
} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
CarrierBundle::CarrierBundle(unsigned numCarriers,const Frequency& totalBw, const Frequency& maxGap,
		const Frequency& sumBw, const Frequency& aveCentre) :
	mNumCarriers(numCarriers),
	mBw( quantiseBw(totalBw) ),
	mGap( quantiseGap(maxGap) ),
	mSumBw(sumBw),
	mMaxGap(maxGap),
	mAveCentre(aveCentre)
{
//#ifdef OFF_TARGET
//std::cerr << "CarrierBundle(totalBw="<<totalBw<<", maxGap="<< maxGap<<"): " << *this << std::endl ;
//#endif
}

//-------------------------------------------------------------------------------------------------------------
CarrierBundle::CarrierBundle() :
	mNumCarriers(0),
	mBw(CB_BW_0),
	mGap(CB_GAP_0),
	mSumBw(0.0),
	mMaxGap(0.0),
	mAveCentre(0.0)
{
}

//-------------------------------------------------------------------------------------------------------------
void CarrierBundle::set(const ICarrierBundle& rhs)
{
	mNumCarriers = rhs.getNumCarriers() ;
	mBw = rhs.getBw() ;
	mGap = rhs.getGap() ;
	mSumBw = rhs.getSumBw() ;
	mMaxGap = rhs.getMaxGap() ;
	mAveCentre = rhs.getAveCentre() ;
}

//-------------------------------------------------------------------------------------------------------------
void CarrierBundle::set(std::shared_ptr<ICarrierBundle> rhs)
{
	set(*rhs) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<Power> CarrierBundle::getThresholds() const
{
	std::vector<Power> thresholds ;
	for (unsigned idx=0; idx < HW_CFR_STAGES; ++idx)
	{
		float threshold(bundleTable[mBw][mGap].thresholds[idx]) ;
		if (threshold == 0)
			thresholds.push_back( Power(DEFAULT_THRESHOLD, Power::dBm) ) ;
		else
			thresholds.push_back( Power(threshold, Power::dBm) ) ;
	}
	return thresholds ;
}

//-------------------------------------------------------------------------------------------------------------
void CarrierBundle::show(std::ostream& os) const
{
	os << "CarrierBundle[ carriers=" << mNumCarriers <<
		" BW=" << BW_NAMES.at(mBw) <<
		" Gap=" << GAP_NAMES.at(mGap) <<
		" Sum BW=" << mSumBw <<
		" Max Gap=" << mMaxGap <<
		" Ave Centre=" << mAveCentre <<
		"]" ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierBundle::operator==(const ICarrierBundle& rhs) const
{
	const CarrierBundle& other = dynamic_cast<const CarrierBundle&>(rhs) ;
	if (mBw != other.mBw)
		return false ;
	if (mGap != other.mGap)
		return false ;
	if (mNumCarriers != other.mNumCarriers)
		return false ;
	if (mSumBw != other.mSumBw)
		return false ;
	if (mMaxGap != other.mMaxGap)
		return false ;
	if (mAveCentre != other.mAveCentre)
		return false ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierBundle::operator!=(const ICarrierBundle& rhs) const
{
	return !operator==(rhs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierBundle::operator ==(std::shared_ptr<ICarrierBundle> rhs) const
{
	return operator==(*rhs) ;
}

//-------------------------------------------------------------------------------------------------------------
bool CarrierBundle::operator !=(std::shared_ptr<ICarrierBundle> rhs) const
{
	return operator!=(*rhs) ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned Mplane::CarrierBundle::getNumCarriers() const
{
	return mNumCarriers ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrierBundle::BundleBw CarrierBundle::getBw() const
{
	return mBw ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrierBundle::BundleGap CarrierBundle::getGap() const
{
	return mGap ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CarrierBundle::getSumBw() const
{
	return mSumBw ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CarrierBundle::getMaxGap() const
{
	return mMaxGap ;
}

//-------------------------------------------------------------------------------------------------------------
Frequency CarrierBundle::getAveCentre() const
{
	return mAveCentre ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ICarrierBundle::BundleBw CarrierBundle::quantiseBw(const Frequency& totalBw) const
{
enum BundleBw bw( CB_BW_0 ) ;

	unsigned total_occupied_bw( totalBw.getUint(Frequency::MHz) ) ;
	if (total_occupied_bw > 95)
	{
		bw = CB_BW_100;
	}
	else if (total_occupied_bw > 85)
	{
		bw = CB_BW_90;
	}
	else if (total_occupied_bw > 75)
	{
		bw = CB_BW_80;
	}
	else if (total_occupied_bw > 65)
	{
		bw = CB_BW_70;
	}
	else if (total_occupied_bw > 55)
	{
		bw = CB_BW_60;
	}
	else if (total_occupied_bw > 45)
	{
		bw = CB_BW_50;
	}
	else if (total_occupied_bw > 35)
	{
		bw = CB_BW_40;
	}
	else if (total_occupied_bw > 25)
	{
		bw = CB_BW_30;
	}
	else if (total_occupied_bw > 15)
	{
		bw = CB_BW_20;
	}
	else if (total_occupied_bw > 5)
	{
		bw = CB_BW_10;
	}
	else if (total_occupied_bw > 3)
	{
		bw = CB_BW_5;
	}
	else if (total_occupied_bw > 2)
	{
		bw = CB_BW_3;
	}
	else if (total_occupied_bw > 0 )
	{
		bw = CB_BW_1M4;
	}

	return bw ;
}

//-------------------------------------------------------------------------------------------------------------
ICarrierBundle::BundleGap CarrierBundle::quantiseGap(const Frequency& maxGap) const
{
BundleGap gap( CB_GAP_0 ) ;

	unsigned max_gap( maxGap.getUint(Frequency::MHz) ) ;
	if (max_gap > 85)
	{
		gap = CB_GAP_90;
	}
	else if (max_gap > 75)
	{
		gap = CB_GAP_80;
	}
	else if (max_gap > 65)
	{
		gap = CB_GAP_70;
	}
	else if (max_gap > 55)
	{
		gap = CB_GAP_60;
	}
	else if (max_gap > 45)
	{
		gap = CB_GAP_50;
	}
	else if (max_gap > 35)
	{
		gap = CB_GAP_40;
	}
	else if (max_gap > 25)
	{
		gap = CB_GAP_30;
	}
	else if (max_gap > 15)
	{
		gap = CB_GAP_20;
	}
	else if (max_gap > 5)
	{
		gap = CB_GAP_10;
	}

	return gap ;
}

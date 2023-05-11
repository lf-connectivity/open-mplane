/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranDelays.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>
#include <string>
#include <cmath>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <set>
#include <string>

#include "OranDelays.h"

using namespace Mplane;


//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
OranDelays::OranDelays(DelayClock_T delayClock) :
	Loggable("OranDelays", "YANG"),
	mClock(delayClock == _10G_CLOCK ? 6.4 : 2.56),		// If this is a 10G clock then the clock value is 6.4.
														// Else for a 25G clock then the clock value is 2.56
	mT_Eth_Tx((7.0 * mClock), Zcu111Delay::NS), 		// The delay class does not convert correctly.
	mT_Eth_Rx_Min((31.0  * mClock), Zcu111Delay::NS),	// This should be at a 'lineRate' of 156.25MHz which is a clock tick of 6.4ns. (1/156250000)
	mT_Eth_Rx_Max((211.0  * mClock), Zcu111Delay::NS),
	mT_MacPcs_Tx((13.0  * mClock), Zcu111Delay::NS),
	mT_MacPcs_Rx((10.0  * mClock), Zcu111Delay::NS),
	mGty_Tx(34.133, Zcu111Delay::NS),
	mGty_Rx(21.867, Zcu111Delay::NS),
	mInitialised(false),
	mBandwidth(),
	mSubCarrierSpacing(),
	mSystemFpga(IFpgaMgr::getIFpgaSystemRegs()),
	mOranFpga(IFpgaMgr::getIFpgaOranRegs()),
	mNumSupportedAirStdBw(4),
	mNumSupportedScsBw(4)
{
	// Initialise the date right here, right now.
	initDelayData();
}

//-------------------------------------------------------------------------------------------------------------
OranDelays::~OranDelays()
{
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Mplane::OranDelays::initDelayData(void)
{
	{
		UINT32 airStd = getNumSupportedAirStdBw();	// 4 Air standards supported - LTE20/15/10/5
		UINT32 param = 6;		// 6 parameters; listed below

		double delays[airStd][param] =
				//	  Bandwidth, T_ORAN_DL_min, T_ORAN_DL_max, T_ORAN_UL_min, T_ORAN_UL_max, T_ORAN_UL_proc;
					{{20000,	 51007, 		116193, 	   126792, 		  197836,		 120524},	//LTE20
					 {15000,	 51007, 		116193, 	   126792, 		  197836,		 120524},	//LTE15
					 {10000,	 23876, 		92123,  	   97678,  		  168803,		 93410},	//LTE10
					 {5000,		 11347, 		81119,  	   84180,  		  154581,		 80879}};	//LTE5

		for( UINT32 airStdLoop = 0; airStdLoop < airStd; airStdLoop ++ )
		{
			ProcessingDelays instance;

			instance.bandwidth.set(delays[airStdLoop][0], Frequency::KHz);

			instance.T_ORAN_DL_min = delays[airStdLoop][1];
			instance.T_ORAN_DL_max = delays[airStdLoop][2];
			instance.T_ORAN_UL_min = delays[airStdLoop][3];
			instance.T_ORAN_UL_max = delays[airStdLoop][4];
			instance.T_ORAN_UL_proc = delays[airStdLoop][5];

			mBandwidthProcessingDelays.push_back(instance);
		}
	}

	// Initialise the SubCarrier Spacing data
	{
		UINT32 scs = getNumSupportedScsSpacing();	// 4 SubCarrier Spacing supported - 120/60/30/15KHz
		UINT32 param = 2;	// 2 parameters; listed below

		double slotLength[scs][param] =
				// 	  SCS, T_slot_length (us)
					{{120, 125},
					 { 60, 250},
					 { 30, 500},
					 { 15,1000}};

		for( UINT32 scsLoop = 0; scsLoop < scs; scsLoop ++ )
		{
			SlotLength instance;

			instance.SubCarrier_Spacing.set(slotLength[scsLoop][0], Frequency::KHz);
			instance.T_slot_length = slotLength[scsLoop][1] * 1000; // Default unit is 'us'. we need 'ns'

			mScsSlotLength.push_back(instance);
		}
	}

	mChannelBandwidthMap[200]    = ICarrierHardwareTypes::CHBW_200;
	mChannelBandwidthMap[1400]   = ICarrierHardwareTypes::CHBW_1400;
	mChannelBandwidthMap[3000]   = ICarrierHardwareTypes::CHBW_3000;
	mChannelBandwidthMap[5000]   = ICarrierHardwareTypes::CHBW_5000;
	mChannelBandwidthMap[10000]  = ICarrierHardwareTypes::CHBW_10000;
	mChannelBandwidthMap[15000]  = ICarrierHardwareTypes::CHBW_15000;
	mChannelBandwidthMap[20000]  = ICarrierHardwareTypes::CHBW_20000;
	mChannelBandwidthMap[25000]  = ICarrierHardwareTypes::CHBW_25000;
	mChannelBandwidthMap[30000]  = ICarrierHardwareTypes::CHBW_30000;
	mChannelBandwidthMap[40000]  = ICarrierHardwareTypes::CHBW_40000;
	mChannelBandwidthMap[50000]  = ICarrierHardwareTypes::CHBW_50000;
	mChannelBandwidthMap[60000]  = ICarrierHardwareTypes::CHBW_60000;
	mChannelBandwidthMap[70000]  = ICarrierHardwareTypes::CHBW_70000;
	mChannelBandwidthMap[80000]  = ICarrierHardwareTypes::CHBW_80000;
	mChannelBandwidthMap[90000]  = ICarrierHardwareTypes::CHBW_90000;
	mChannelBandwidthMap[100000] = ICarrierHardwareTypes::CHBW_100000;
	mChannelBandwidthMap[200000] = ICarrierHardwareTypes::CHBW_UNSET;
	mChannelBandwidthMap[400000] = ICarrierHardwareTypes::CHBW_UNSET;

}

// The following calculations are from the FPGA wiki - http://twiki/cgi-bin/twiki/view/Engineering/OranMPlaneDelayManagement?rev=5
// The 2nd symbol length is from revision 6 of this document, but in the majority this is all derived from revision 5
// This is because revision 6 uses FPGA registers that relate to particular streams. There is some suggestion that these won't be
// setup at the time that this data is collated and the current Yang mode does not anticipate complex mixed
// carrier setups that the wiki page supports.

//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::CalcT2aMinUp(Frequency bandwidth)
{
	// T2a min up = TDUC + TORAN DL min + TEth Rx max + TMAC/PCS Rx + TGTY Rx
	Zcu111Delay T2aMinUp;

	T2aMinUp = getTduc(bandwidth) +
			   getTOranDlMin(bandwidth) +
			   mT_Eth_Rx_Max.get(Zcu111Delay::NS) +
			   mT_MacPcs_Rx.get(Zcu111Delay::NS) +
			   mGty_Rx.get(Zcu111Delay::NS);

	logDebugVerbose("CalcT2aMinUp( %s ) = ", std::to_string(bandwidth.getInt(Frequency::KHz)).c_str());
	logDebugVerbose("        TDUC = %s +", std::to_string(getTduc(bandwidth).getInt()).c_str());
	logDebugVerbose("  TOranDlMin = %s +", std::to_string(getTOranDlMin(bandwidth).getInt()).c_str());
	logDebugVerbose("T_Eth_Rx_Max = %s +", std::to_string(mT_Eth_Rx_Max.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose(" T_MacPcs_Rx = %s +", std::to_string(mT_MacPcs_Rx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("      Gty_Rx = %s", std::to_string(mGty_Rx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("             = %s", std::to_string(T2aMinUp.get()).c_str());

	return T2aMinUp;

}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::CalcT2aMaxUp(Frequency bandwidth)
{
	// T2a max up = TDUC + TORAN DL max + TEth Rx min + TMAC/PCS Rx + TGTY Rx
	Zcu111Delay T2aMaxUp;

	T2aMaxUp = getTduc(bandwidth) +
			   getTOranDlMax(bandwidth) +
			   mT_Eth_Rx_Min.get(Zcu111Delay::NS) +
			   mT_MacPcs_Rx.get(Zcu111Delay::NS) +
			   mGty_Rx.get(Zcu111Delay::NS);

	logDebugVerbose("CalcT2aMaxUp( %s )", std::to_string(bandwidth.getInt(Frequency::KHz)).c_str());
	logDebugVerbose("        TDUC = %s +", std::to_string(getTduc(bandwidth).getInt()).c_str());
	logDebugVerbose("  TOranDlMax = %s +", std::to_string(getTOranDlMax(bandwidth).getInt()).c_str());
	logDebugVerbose("T_Eth_Rx_Min = %s +", std::to_string(mT_Eth_Rx_Min.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose(" T_MacPcs_Rx = %s +", std::to_string(mT_MacPcs_Rx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("      Gty_Rx = %s", std::to_string(mGty_Rx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("             = %s", std::to_string(T2aMaxUp.get()).c_str());



	return T2aMaxUp;

}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::CalcTcpAdvDl(Frequency bandwidth)
{
	// Tcp adv dl = 0
	return 0;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::CalcT2aMinCpDl(Frequency bandwidth)
{
	//	T2a min cp dl = T2a min up + Tcp adv dl
	Zcu111Delay T2aMinCpDl;

	T2aMinCpDl = CalcT2aMinUp(bandwidth) + CalcTcpAdvDl(bandwidth);

	logDebugVerbose("CalcT2aMinCpDl( %s ) = ", std::to_string(bandwidth.getInt(Frequency::KHz)).c_str());
	logDebugVerbose("T2aMinUp = %s +", std::to_string(CalcT2aMinUp(bandwidth).get()).c_str());
	logDebugVerbose("TcpAdvDl = %s", std::to_string(CalcTcpAdvDl(bandwidth).get()).c_str());
	logDebugVerbose("         = %s", std::to_string(T2aMinCpDl.get()).c_str());

	return T2aMinCpDl;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::CalcT2aMaxCpDl(Frequency bandwidth)
{
	// T2a max cp dl = T2a max up + Tcp adv dl
	Zcu111Delay T2aMaxCpDl;

	T2aMaxCpDl = CalcT2aMaxUp(bandwidth) + CalcTcpAdvDl(bandwidth);

	logDebugVerbose("CalcT2aMaxCpDl( %s ) = ", std::to_string(bandwidth.getInt(Frequency::KHz)).c_str());
	logDebugVerbose("T2aMaxCpDl = %s +", std::to_string(CalcT2aMaxUp(bandwidth).get()).c_str());
	logDebugVerbose("  TcpAdvDl = %s", std::to_string(CalcTcpAdvDl(bandwidth).get()).c_str());
	logDebugVerbose("           = %s ", std::to_string(T2aMaxCpDl.get()).c_str());

	return T2aMaxCpDl;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::CalcTa3Min(Frequency bandwidth)
{
	// Ta3 min = TDDC + TORAN UL min + TEth Tx + TMAC/PCS Tx + TGTY Tx
	Zcu111Delay T3aMin;

	T3aMin = getTddc(bandwidth) +
			 getTOranUlMin(bandwidth) +
			 mT_Eth_Tx.get(Zcu111Delay::NS) +
			 mT_MacPcs_Tx.get(Zcu111Delay::NS) +
			 mGty_Tx.get(Zcu111Delay::NS);

	logDebugVerbose("CalcTa3Min( %s ) =", std::to_string(bandwidth.getInt(Frequency::KHz)).c_str());
	logDebugVerbose("       TDDC = %s +", std::to_string(getTddc(bandwidth).getInt()).c_str());
	logDebugVerbose(" TOranUlMin = %s +", std::to_string(getTOranUlMin(bandwidth).getInt()).c_str());
	logDebugVerbose("   T_Eth_Tx = %s +", std::to_string(mT_Eth_Tx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("T_MacPcs_Tx = %s +", std::to_string(mT_MacPcs_Tx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("     Gty_Tx = %s", std::to_string(mGty_Tx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("            = %s", std::to_string(T3aMin.get()).c_str());

	return T3aMin;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::CalcTa3Max(Frequency bandwidth)
{
	// Ta3 max = TDDC + TORAN UL proc + TEth Tx + TMAC/PCS Tx + TGTY Tx
	Zcu111Delay T3aMax;

	T3aMax = getTddc(bandwidth) +
			 getTOranUlProc(bandwidth) +
			 get2ndSymbolLength() +
			 mT_Eth_Tx.get(Zcu111Delay::NS) +
			 mT_MacPcs_Tx.get(Zcu111Delay::NS) +
			 mGty_Tx.get(Zcu111Delay::NS);

	logDebugVerbose("CalcTa3Max( %s ) =", std::to_string(bandwidth.getInt(Frequency::KHz)).c_str());
	logDebugVerbose("            TDDC = %s +", std::to_string(getTddc(bandwidth).getInt()).c_str());
	logDebugVerbose("     TOranUlProc = %s +", std::to_string(getTOranUlProc(bandwidth).getInt()).c_str());
	logDebugVerbose("T2ndSymbolLength = %s +", std::to_string(get2ndSymbolLength().get()).c_str());
	logDebugVerbose("        T_Eth_Tx = %s +", std::to_string(mT_Eth_Tx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("     T_MacPcs_Tx = %s +", std::to_string(mT_MacPcs_Tx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("          Gty_Tx = %s", std::to_string(mGty_Tx.get(Zcu111Delay::NS)).c_str());
	logDebugVerbose("                 = %s", std::to_string(T3aMax.get()).c_str());

	return T3aMax;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::CalcT2aMinCpUl(Frequency bandwidth)
{
	// T2a min cp ul = 0
	return 0;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::CalcT2aMaxCpUl(Frequency bandwidth, Frequency subCarrierSpacing)
{
	//	T2a max cp ul = Tslot length - TORAN UL proc - TDDC
	Zcu111Delay T2aMaxCpUl = 0;

	T2aMaxCpUl = getSlotLength(subCarrierSpacing) - getTOranUlProc(bandwidth) - getTddc(bandwidth);

	logDebugVerbose("CalcT2aMaxCpUl( %s ) =", std::to_string(bandwidth.getInt(Frequency::KHz)).c_str());
	logDebugVerbose(" Tslot length = %s -", std::to_string(getSlotLength(subCarrierSpacing).get()).c_str());
	logDebugVerbose("  TOranUlProc = %s -", std::to_string(getTOranUlProc(bandwidth).getInt()).c_str());
	logDebugVerbose("         TDDC = %s", std::to_string(getTddc(bandwidth).getInt()).c_str());
	logDebugVerbose("              = %s", std::to_string(T2aMaxCpUl.get()).c_str());

	return T2aMaxCpUl;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::getTOranDlMin(Frequency bandwidth)
{
	Zcu111Delay returnValue(0);

	for( std::vector<ProcessingDelays>::iterator itr = mBandwidthProcessingDelays.begin();
		 itr < mBandwidthProcessingDelays.end();
		 itr ++)
	{
		if(itr->bandwidth == bandwidth)
		{
			returnValue = itr->T_ORAN_DL_min.get(Zcu111Delay::NS);
		}
	}
	return returnValue;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::getTOranDlMax(Frequency bandwidth)
{
	Zcu111Delay returnValue(0);

	for( std::vector<ProcessingDelays>::iterator itr = mBandwidthProcessingDelays.begin();
		 itr < mBandwidthProcessingDelays.end();
		 itr ++)
	{
		if(itr->bandwidth == bandwidth)
		{
			returnValue = itr->T_ORAN_DL_max.get(Zcu111Delay::NS);;
		}
	}
	return returnValue;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::getTOranUlMin(Frequency bandwidth)
{
	Zcu111Delay returnValue(0);

	for( std::vector<ProcessingDelays>::iterator itr = mBandwidthProcessingDelays.begin();
		 itr < mBandwidthProcessingDelays.end();
		 itr ++)
	{
		if(itr->bandwidth == bandwidth)
		{
			returnValue = itr->T_ORAN_UL_min.get(Zcu111Delay::NS);;
		}
	}
	return returnValue;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::getTOranUlMax(Frequency bandwidth)
{
	Zcu111Delay returnValue(0);

	for( std::vector<ProcessingDelays>::iterator itr = mBandwidthProcessingDelays.begin();
		 itr < mBandwidthProcessingDelays.end();
		 itr ++)
	{
		if(itr->bandwidth == bandwidth)
		{
			returnValue = itr->T_ORAN_UL_max.get(Zcu111Delay::NS);;
		}
	}
	return returnValue;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::getTOranUlProc(Frequency bandwidth)
{
	Zcu111Delay returnValue(0);

	for( std::vector<ProcessingDelays>::iterator itr = mBandwidthProcessingDelays.begin();
		 itr < mBandwidthProcessingDelays.end();
		 itr ++)
	{
		if(itr->bandwidth == bandwidth)
		{
			returnValue = itr->T_ORAN_UL_proc.get(Zcu111Delay::NS);;
		}
	}
	return returnValue;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::getSlotLength(Frequency subCarrierSpacing)
{
	Zcu111Delay returnValue(0);

	for( std::vector<SlotLength>::iterator itr = mScsSlotLength.begin();
		 itr < mScsSlotLength.end();
		 itr ++)
	{
		if(itr->SubCarrier_Spacing == subCarrierSpacing)
		{
			returnValue = itr->T_slot_length.get(Zcu111Delay::NS);;
		}
	}
	return returnValue;
}
//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::getTduc(Frequency bandwidth)
{
	UINT32 ulProcDelay = 0;

	mSystemFpga->write_desiredAirStd((unsigned)0, ICarrierHardwareTypes::AIRSTD_LTE) ;
	mSystemFpga->write_desiredChBw((unsigned)0, getChBwTypeFromBandwidth(bandwidth)) ;

	// Read the processing delays now
	ulProcDelay = mSystemFpga->read_resultingUlProcessing(0) ;

	logDebugVerbose("OranDelays::getTduc() - Raw TDUC %s", std::to_string(ulProcDelay).c_str());

	Zcu111Delay procDelay(ulProcDelay, Zcu111Delay::FPGA);

	return procDelay.get(Zcu111Delay::NS);
}

//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::getTddc(Frequency bandwidth)
{
	UINT32 dlProcDelay = 0;

	mSystemFpga->write_desiredAirStd((unsigned)0, ICarrierHardwareTypes::AIRSTD_LTE) ;
	mSystemFpga->write_desiredChBw((unsigned)0, getChBwTypeFromBandwidth(bandwidth)) ;

	// Read the processing delays now
	dlProcDelay = mSystemFpga->read_resultingDlProcessing(0) ;

	logDebugVerbose("OranDelays::getTduc() - Raw TDDC %s", std::to_string(dlProcDelay).c_str());

	Zcu111Delay procDelay(dlProcDelay, Zcu111Delay::FPGA);

	return procDelay.get(Zcu111Delay::NS);
}

//-------------------------------------------------------------------------------------------------------------
ICarrierHardwareTypes::ChbwType Mplane::OranDelays::getChBwTypeFromBandwidth(Frequency bandwidth)
{
	std::map<double, ICarrierHardwareTypes::ChbwType>::iterator itr;

	itr = mChannelBandwidthMap.find(bandwidth.get(Frequency::KHz));

	if(itr != mChannelBandwidthMap.end())
	{
		if(itr->second == ICarrierHardwareTypes::CHBW_UNSET)
		{
			eventError("OranDelays::getChBwTypeFromBandwidth() - Bandwidth %llu not supported, returning CHBW_UNSET", bandwidth.get());
		}
	}
	else
	{
		eventError("OranDelays::getChBwTypeFromBandwidth() - Bandwidth %llu not found, returning CHBW_UNSET", bandwidth.get());
	}

	return itr->second;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 Mplane::OranDelays::getNumSupportedAirStdBw(void)
{
	return mNumSupportedAirStdBw;
}

//-------------------------------------------------------------------------------------------------------------
UINT32 Mplane::OranDelays::getNumSupportedScsSpacing(void)
{
	return mNumSupportedScsBw;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::OranDelays::getSupportedAirStdBw(std::vector<Frequency> &supportedAirStdBw)
{
	for( std::vector<ProcessingDelays>::iterator itr = mBandwidthProcessingDelays.begin();
		 itr < mBandwidthProcessingDelays.end();
		 itr ++)
	{
		supportedAirStdBw.push_back(itr->bandwidth);
	}
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::OranDelays::getSupportedScsSpacing(std::vector<Frequency> &supportedScsSpacing)
{
	for( std::vector <SlotLength>::iterator itr = mScsSlotLength.begin();
		 itr < mScsSlotLength.end();
		 itr ++)
	{
		supportedScsSpacing.push_back(itr->SubCarrier_Spacing);
	}
}

//-------------------------------------------------------------------------------------------------------------
Zcu111Delay Mplane::OranDelays::get2ndSymbolLength(void)
{

	// FFTsize + CP1
	UINT32 FFTsize = 0;
	UINT32 cp1Length = 0;

	FFTsize = mOranFpga->read_fftSize((unsigned)0);
	cp1Length = mOranFpga->read_cp1Length((unsigned)0);

	logDebugVerbose("OranDelays::get2ndSymbolLength() - Raw FFTsize %s", std::to_string(FFTsize).c_str());
	logDebugVerbose("OranDelays::get2ndSymbolLength() - Raw cp1Length %s", std::to_string(cp1Length).c_str());

//	UINT32 power = std::pow(2, FFTsize);
//
//	logDebugVerbose("OranDelays::get2ndSymbolLength() - power = %s", std::to_string(power).c_str());
//
//	UINT32 calc = ((std::pow(2, FFTsize) + cp1Length)/2);
//
//	logDebugVerbose("OranDelays::get2ndSymbolLength() - calc = %s", std::to_string(calc).c_str());

	// The 2nd symbol length = ((2^FFTsize + cp1 length) / 2) * 1/30.72MHz) in seconds. We need this in 'ns' so multiply by 1x10exp9
	Zcu111Delay SymbolLength((double)((std::pow(2.0, (double)FFTsize) + (double)cp1Length) / 2.0) * (double)(1.0/30720000.0) * 1000000000, Zcu111Delay::NS);

	logDebugVerbose("OranDelays::get2ndSymbolLength() - result = %s", std::to_string(SymbolLength.get()).c_str());

	return SymbolLength.get(Zcu111Delay::NS);
}

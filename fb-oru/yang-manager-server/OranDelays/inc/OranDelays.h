/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranDelays.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef _INC_ORAN_DELAYS_H_
#define _INC_ORAN_DELAYS_H_

#include <set>
#include <map>
#include <string>
#include <utility>

#include "Loggable.h"
#include "Frequency.h"

#include "IFpgaMgr.h"
#include "IOranDelays.h"
#include "ICarrierScheduler.h"

#include "Zcu111Delay.h"


namespace Mplane
{

/*!
 * \class  OranDelays
 * \brief
 * \details
 *
 */
class OranDelays : public IOranDelays, public Loggable
{
	friend class TestBandwidthProcessingDelays_getTOranDlMin_Test;

public:

	OranDelays(DelayClock_T delayClock) ;
	virtual ~OranDelays() ;

	virtual Zcu111Delay CalcT2aMinUp(Frequency bandwidth);		//!> Calculate T2a Min Uplink (ns)
	virtual Zcu111Delay CalcT2aMaxUp(Frequency bandwidth);		//!> Calculate T2a Max Uplink (ns)
	virtual Zcu111Delay CalcTcpAdvDl(Frequency bandwidth);		//!> Calculate TCP advance Downlink (ns)
	virtual Zcu111Delay CalcT2aMinCpDl(Frequency bandwidth);	//!> Calculate T2a Min CP Downlink (ns)
	virtual Zcu111Delay CalcT2aMaxCpDl(Frequency bandwidth);	//!> Calculate T2a Max CP Downlink (ns)
	virtual Zcu111Delay CalcTa3Min(Frequency bandwidth);		//!> Calculate Ta3 Min (ns)
	virtual Zcu111Delay CalcTa3Max(Frequency bandwidth);		//!> Calculate Ta3 Max (ns)
	virtual Zcu111Delay CalcT2aMinCpUl(Frequency bandwidth);	//!> Calculate T2a Min CP Uplink (ns)
	virtual Zcu111Delay CalcT2aMaxCpUl(Frequency bandwidth,		//!> Calculate T2a Min CP Uplink (ns)
	                                   Frequency subCarrierSpacing);

	virtual ICarrierHardwareTypes::ChbwType getChBwTypeFromBandwidth(Frequency bandwidth);

	virtual UINT32 getNumSupportedAirStdBw(void);
	virtual UINT32 getNumSupportedScsSpacing(void);

	virtual void getSupportedAirStdBw(std::vector<Frequency> & supportedAirStdBw);
	virtual void getSupportedScsSpacing(std::vector<Frequency> & supportedScsSpacing);

	class ProcessingDelays
	{
	public:
		ProcessingDelays(){};
		~ProcessingDelays(){};

		Frequency bandwidth;

		Zcu111Delay T_ORAN_DL_min;	// Downlink minimum delay in ns
		Zcu111Delay T_ORAN_DL_max;	// Downlink maximum delay in ns
		Zcu111Delay T_ORAN_UL_min;	// Uplink minimum delay in ns
		Zcu111Delay T_ORAN_UL_max;	// Uplink minimum delay in ns
		Zcu111Delay T_ORAN_UL_proc;	// Uplink processing delay in ns
	};

	std::vector <ProcessingDelays> mBandwidthProcessingDelays;

	class SlotLength
	{
	public:
		SlotLength(){};
		~SlotLength(){};

		Frequency SubCarrier_Spacing;	// Slot spacing 120, 60, 30, 15 KHz
		Zcu111Delay T_slot_length;		// Slot length in ms
	};

	std::vector <SlotLength> mScsSlotLength;

	const float mClock;

	const Zcu111Delay mT_Eth_Tx;
	const Zcu111Delay mT_Eth_Rx_Min;
	const Zcu111Delay mT_Eth_Rx_Max;
	const Zcu111Delay mT_MacPcs_Tx;
	const Zcu111Delay mT_MacPcs_Rx;

	const Zcu111Delay mGty_Tx;
	const Zcu111Delay mGty_Rx;

	bool mInitialised ;

	Frequency mBandwidth;
	Frequency mSubCarrierSpacing;

	std::shared_ptr<IFpgaSystemRegs> mSystemFpga;
	std::shared_ptr<IFpgaOranRegs> mOranFpga;

	std::map<double, ICarrierHardwareTypes::ChbwType> mChannelBandwidthMap;

	UINT32 mNumSupportedAirStdBw;
	UINT32 mNumSupportedScsBw;

	void initDelayData(void);

	Zcu111Delay getTOranDlMin(Frequency bandwidth);
	Zcu111Delay getTOranDlMax(Frequency bandwidth);
	Zcu111Delay getTOranUlMin(Frequency bandwidth);
	Zcu111Delay getTOranUlMax(Frequency bandwidth);
	Zcu111Delay getTOranUlProc(Frequency bandwidth);

	Zcu111Delay getSlotLength(Frequency subCarrierSpacing);

	Zcu111Delay getTduc(Frequency bandwidth);
	Zcu111Delay getTddc(Frequency bandwidth);

	Zcu111Delay get2ndSymbolLength(void);
} ;

}

#endif /* _INC_ORAN_DELAYS_H_ */

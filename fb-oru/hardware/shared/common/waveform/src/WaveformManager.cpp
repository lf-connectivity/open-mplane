/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      WaveformManager.cpp
 * \brief
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <sstream>
#include <string>
#include <iostream>
#include "WaveformHardwareDpdAdc.h"
#include "WaveformHardwareRxAdc.h"
#include "WaveformHardwareFullrate.h"
#include "WaveformHardwareRxFixedRate.h"
#include "WaveformHardwareFastVss.h"
#include "WaveformHardware153M6.h"
#include "WaveformHardware122M88.h"
#include "Waveform.h"
#include "WaveformControl.h"
#include "WaveformManager.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// The SDRAM interface has a maximum rate - if we try to exceed it with too many simultaneous captures
// then we'll need to reschedule captures
static const unsigned MAX_INTERFACE_KSPS{245760} ;

// High rate capture
static const unsigned HIGH_RATE_KSPS{61440} ;

// A frame's worth of trigger delay
static const unsigned TRIGGER_FRAME{307200} ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
WaveformManager::WaveformManager(unsigned waveMemSize, unsigned waveMemStart, unsigned waveMemAlignment) :
	mMutex(),
	mWaveformResources(),
	mWaveformPortMap(),
	mWaveformMap(),
	mError("")
{
	// Get the waveform memory manager instance - getting first instance will set it's size
	std::shared_ptr<WaveMemMgr> waveMemMgr( WaveMemMgr::getInstance(waveMemSize, waveMemStart, waveMemAlignment) ) ;

	std::string error ;

	// Initialise master hardware
	WaveformHardware::initMaster(error) ;
}

//-------------------------------------------------------------------------------------------------------------
WaveformManager::~WaveformManager()
{
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::init()
{
	std::string error ;

	// FPGA now uses a fixed table. For full details see: http://twiki/cgi-bin/twiki/view/Engineering/FpgaSwifWaveformMemorySystem
	//
	// The index sets the waveform type:
	//  0 = CAPTURE RX1 Fixed rate 61440Ksps
	//  1 = CAPTURE RX2 Fixed rate 61440Ksps
	//  2 = PLAYBACK CPRI multicast RF chain indexes 0 and 2 (carrier rate)
	//  3 = PLAYBACK CPRI multicast RF chain indexes 0 and 2 (carrier rate)
	//  4 = CAPTURE CPRI RF chain index 0 (carrier rate)
	//  5 = CAPTURE CPRI RF chain index 1 (carrier rate)
	//  6 = PLAYBACK TX1 (carrier rate)
	//  7 = PLAYBACK TX2 (carrier rate)
	//  8 = CAPTURE CPRI RF chain index 2 (carrier rate)
	//  9 = CAPTURE CPRI RF chain index 3 (carrier rate)
	// 10 = PLAYBACK TX1 DAC
	// 11 = PLAYBACK TX2 DAC
	// 12 = CAPTURE CPRI RF chain index 4 (carrier rate)
	// 13 = CAPTURE CPRI RF chain index 5 (carrier rate)
	// 14 = Fast VSS Playback
	// 15 = (PLAYBACK reserved)
	// 16 = CAPTURE RX1 (carrier rate)
	// 17 = CAPTURE RX2 (carrier rate)
	// 18 = (PLAYBACK reserved)
	// 19 = (PLAYBACK reserved)
	// 20 = CAPTURE first PIM block UL input (carrier rate)
	// 21 = CAPTURE first PIM block UL output (carrier rate)
	//
	//	Waveform Module 22 	CPRI Playback on RF Chain index 0 at 153.6 MSPS, Sample Rate Generator: N=0, A=3, B=5
	//	Waveform Module 23 	CPRI Playback on RF Chain index 1 at 153.6 MSPS, Sample Rate Generator: N=0, A=3, B=5
	//	Waveform Module 24 	CPRI Capture on RF Chain index 0 at 153.6 MSPS, Sample Rate Generator: N=0, A=3, B=5
	//	Waveform Module 25 	CPRI Capture on RF Chain index 1 at 153.6 MSPS, Sample Rate Generator: N=0, A=3, B=5
	//
	//	Waveform Module 26 	CPRI Playback on RF Chain index 0 at 122.88 MSPS, Sample Rate Generator: N=2, A=0, B=1
	//	Waveform Module 27 	CPRI Playback on RF Chain index 1 at 122.88 MSPS, Sample Rate Generator: N=2, A=0, B=1
	//	Waveform Module 28 	CPRI Capture on RF Chain index 0 at 122.88 MSPS, Sample Rate Generator: N=2, A=0, B=1
	//	Waveform Module 29 	CPRI Capture on RF Chain index 1 at 122.00 MSPS, Sample Rate Generator: N=2, A=0, B=1


	// Totally separate wave modules are used to capture the DPD ADC, Rx1 ADC and Rx2 ADC:
	// wrxcal = CAPTURE DPD ADC
	// wrxcal1 = CAPTURE RX1 ADC
	// wrxcal2 = CAPTURE RX2 ADC

	unsigned idx(0) ;
	std::string name("");

	// 0-1:  RX1/2 capture at 61.44Msps
	for (; idx <= 1; ++idx)
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "w" + std::to_string(idx);
		unsigned port = (idx % 2);
		mWaveformPortMap[name] = port;

		std::shared_ptr<WaveformHardwareRxFixedRate> waveformHardware(new WaveformHardwareRxFixedRate(idx, port)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	// 2-9: normal
	for (; idx <= 9; ++idx)
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "w" + std::to_string(idx);
		unsigned port = (idx % 2);
		mWaveformPortMap[name] = port;

		std::shared_ptr<WaveformHardware> waveformHardware(new WaveformHardware(idx, port)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	// 10-11: Tx1/2 playback direct to DAC
	for (; idx <= 11; ++idx)
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "w" + std::to_string(idx);
		unsigned port = (idx % 2);
		mWaveformPortMap[name] = port;

		std::shared_ptr<WaveformHardwareFullrate> waveformHardware(new WaveformHardwareFullrate(idx, port)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	// 12-13: normal
	for (; idx <= 13; ++idx)
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "w" + std::to_string(idx);
		unsigned port = (idx % 2);
		mWaveformPortMap[name] = port;

		std::shared_ptr<WaveformHardware> waveformHardware(new WaveformHardware(idx, port)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	// 14-15: Fast VSS
	for (; idx <= 15; ++idx)
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "w" + std::to_string(idx);
		unsigned port = (idx % 2);
		mWaveformPortMap[name] = port;

		std::shared_ptr<WaveformHardware> waveformHardware(new WaveformHardwareFastVss(idx, port)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	// 16-21: normal
	for (; idx <= 21; ++idx)
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "w" + std::to_string(idx);
		unsigned port = (idx % 2);
		mWaveformPortMap[name] = port;

		std::shared_ptr<WaveformHardware> waveformHardware(new WaveformHardware(idx, port)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	// 22-25: 153.6MSPS
	for (; idx <= 25; ++idx)
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "w" + std::to_string(idx);
		unsigned port = (idx % 2);
		mWaveformPortMap[name] = port;

		std::shared_ptr<WaveformHardware153M6> waveformHardware(new WaveformHardware153M6(idx, port)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	// 26-29: 122.88MSPS
	for (; idx <= 25; ++idx)
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "w" + std::to_string(idx);
		unsigned port = (idx % 2);
		mWaveformPortMap[name] = port;

		std::shared_ptr<WaveformHardware122M88> waveformHardware(new WaveformHardware122M88(idx, port)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}




	// Append a DPD ADC capture waveform
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "wrxcal";
		mWaveformPortMap[name] = 0;

		std::shared_ptr<WaveformHardware> waveformHardware(new WaveformHardwareDpdAdc(idx++, 0)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	// Append Rx1 ADC capture waveform
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "wrxcal1";
		mWaveformPortMap[name] = 0;

		std::shared_ptr<WaveformHardware> waveformHardware(new WaveformHardwareRxAdc(idx++, 0)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	// Append Rx2 ADC capture waveform
	{
		//Add antenna port for the waveform in a map
		//Nailed for now
		name = "wrxcal2";
		mWaveformPortMap[name] = 1;

		std::shared_ptr<WaveformHardware> waveformHardware(new WaveformHardwareRxAdc(idx++, 1)) ;
		addResource(waveformHardware);

		// do any initialisation
		waveformHardware->init(error) ;
	}

	if (!error.empty())
	{
		setError(error) ;
		return false ;
	}

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::createWave(const std::string& name, Waveform::WaveType type)
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	// have we any more space?
	if (mWaveformMap.size() == mWaveformResources.size())
	{
		mError = "Already using all available waveform resources" ;
		return false ;
	}

	// Ok to add a new one

	// Can only support name wN where N = 0 .. max resources
	if (!validWaveName(name))
		return false ;

	// Check name not already used
	std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(name) ) ;
	if (waveformControl)
	{
		mError = "Waveform already exists" ;
		return false ;
	}

	// create new entry
	waveformControl = createWaveControl() ;
	waveformControl->getWaveform()->setName(name) ;
	waveformControl->getWaveform()->setType(type) ;
	//Get the antenna port. Currently uses the wave name to derive port
	unsigned port = getPortFromWaveName(name) ;
	waveformControl->getWaveform()->setAntennaPort(port) ;
	mWaveformMap[name] = waveformControl ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::hasWave(const std::string& name) const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	// See if waveform exists
	std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(name) ) ;
	if (waveformControl)
		return true ;

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IWaveform> WaveformManager::getWave(const std::string& name) const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	// See if waveform exists
	std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(name) ) ;
	if (waveformControl)
		return waveformControl->getWaveform() ;

	return std::shared_ptr<IWaveform>() ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::deleteWave(const std::string& name)
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(name) ) ;
	if (!waveformControl)
	{
		// silently ignore name error so that a test can start by deleting waveforms even if they haven't been
		// created yet
		return true ;
	}

	// clear down this waveform
	std::string error ;
	waveformControl->shutdown( error ) ;
	waveformControl->setWaveformHardware( std::shared_ptr<WaveformHardware>(), error ) ;

	mWaveformMap.erase(name) ;
	return true ;
}


#define WAVEFORM_SET(method, type) \
bool WaveformManager::method(const std::string& waveName, type value) \
{ \
	Mutex::Lock lock(mMutex) ; \
\
	std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(waveName) ) ; \
	if (!waveformControl) \
	{ \
		mError = "Waveform not found" ; \
		return false ; \
	} \
\
	waveformControl->getWaveform()->method(value) ; \
	return true ; \
}


//-------------------------------------------------------------------------------------------------------------
WAVEFORM_SET(setAntennaPort, unsigned)
WAVEFORM_SET(setCarrierIdx, unsigned)
WAVEFORM_SET(setDirection, Waveform::WaveDirection)
WAVEFORM_SET(setDepth, unsigned)
WAVEFORM_SET(setTrigger, unsigned)
WAVEFORM_SET(setGain, float)
WAVEFORM_SET(setGainFilename, const std::string&)
WAVEFORM_SET(setCaptureCallback, IWaveform::CaptureCallback)

//WAVEFORM_SET(setStreaming, bool)
WAVEFORM_SET(setAveraging, unsigned)
WAVEFORM_SET(setNco, double)
WAVEFORM_SET(setDecimation, IWaveform::WrxcalDecimation)


//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::setScalingGain(const std::string& waveName, float scalingValue)
{
    // Need to mutex protect from test interfaces
    Mutex::Lock lock(mMutex) ;

    std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(waveName) ) ;
    if (!waveformControl)
    {
        mError = "Waveform not found" ;
        return false ;
    }

    if (!waveformControl->setScalingGain(scalingValue))
    {
        mError = "Unable to set scaling gain" ;
        return false ;
    }

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::setStreaming(const std::string& waveName, bool streaming)
{
    // Need to mutex protect from test interfaces
    Mutex::Lock lock(mMutex) ;

    std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(waveName) ) ;
    if (!waveformControl)
    {
        mError = "Waveform not found" ;
        return false ;
    }

    if (!waveformControl->setStreaming(streaming))
    {
        mError = "Unable to set streaming" ;
        return false ;
    }

    return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::setFilename(const std::string& waveName, const std::string& filename)
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(waveName) ) ;
	if (!waveformControl)
	{
		mError = "Waveform not found" ;
		return false ;
	}

	waveformControl->getWaveform()->setFilename(filename) ;

	// Pass change to waveform control
	if (!waveformControl->filenameHasChanged(mError))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::setEnable(const std::string& waveName, bool enable)
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(waveName) ) ;
	if (!waveformControl)
	{
		mError = "Waveform not found" ;
		return false ;
	}

	// Set enable
	waveformControl->getWaveform()->setEnable(enable) ;

	// Get WaveformController to check settings and allocate resources
	if (!allocateCapture())
		return false ;

	if (!validateCapture())
		return false ;

	if (!allocatePlayback())
		return false ;

	if (!validatePlayback())
		return false ;

	if (!scheduleCapture())
		return false ;

	// Pass change to waveform control
	waveformControl->enableHasChanged(enable) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
unsigned WaveformManager::getFileDepth(const std::string& waveName) const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	std::shared_ptr<IWaveformControl> waveformControl( getWaveformControl(waveName) ) ;
	if (!waveformControl)
	{
		return 0 ;
	}

	return waveformControl->getFileDepth() ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::isResourcePresent(unsigned index) const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	if (index >= mWaveformResources.size())
		return false ;

	return mWaveformResources[index]->isPresent() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformManager::calcSampleRateKsps(ICarrier::Type type) const
{
	// Calculate the sample rate
	return WaveformHardware::calcCarrierSampleRateKsps(type) ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::setCapturePlayback(bool captureEnable, bool playbackEnable)
{
	// get the current settings - playback is different from capture because capture is an implied one-shot,
	// whereas playback continues until turned off
	bool currentPlaybackEnable = isPlaybackEnabled() ;

	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	// == Set up hardware if enabling ==

	// enabling capture?
	if (captureEnable)
	{
		// Capture enable

		if (!allocateCapture())
			return false ;

		if (!validateCapture())
			return false ;
	}

	// enabling playback?
	if (playbackEnable && !currentPlaybackEnable)
	{
		// Playback enable

		if (!allocatePlayback())
			return false ;

		if (!validatePlayback())
			return false ;
	}

	// Run scheduler
	if (!scheduleCapture())
		return false ;


	// enabling capture?
	if (captureEnable)
	{
		if (!updateHardwareCapture())
			return false ;
	}

	// enabling playback?
	if (playbackEnable && !currentPlaybackEnable)
	{
		if (!updateHardwarePlayback())
			return false ;
	}


	// == Create a list of enabled waveforms ==
	std::vector< std::shared_ptr<IWaveformControl> > enabledWaves ;
	for (WaveformMapIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		// if it's enabled
		if ( !iter->second->getWaveform()->isEnable() )
			continue ;

		// Add to list
		enabledWaves.push_back(iter->second) ;
	}

	// == Now run the capture playback as necessary ==
	if (captureEnable)
	{
		// capture with/without playback
		if (!WaveformControl::startCapturePlayback(playbackEnable, enabledWaves, mError))
			return false ;
	}
	else
	{
		if (!WaveformControl::stopCapture(enabledWaves, mError))
			return false ;

		// Playback enabling?
		if (playbackEnable && !currentPlaybackEnable)
		{
			// Playback enable
			if (!WaveformControl::startPlayback(enabledWaves, mError))
				return false ;
		}

		// Playback disabling?
		if (!playbackEnable && currentPlaybackEnable)
		{
			// Playback disable
			if (!WaveformControl::stopPlayback(enabledWaves, mError))
				return false ;
		}
	}

	// Finish off
	WaveformControl::completeStartStop(enabledWaves, mError) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
std::string WaveformManager::getErrorReason()
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	using std::swap ;
	std::string reason("") ;
	swap(mError, reason) ;
	return reason ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformManager::supportedWaveforms() const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	return mWaveformResources.size() ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformManager::numWaveforms() const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	return mWaveformMap.size() ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::isPlaybackEnabled() const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	return WaveformHardware::isMasterPlaybackEnabled() ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::isCaptureEnabled() const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	return WaveformHardware::isMasterCaptureEnabled() ;
}


//-------------------------------------------------------------------------------------------------------------
std::string WaveformManager::getPlaybackDirectory() const
{
	return WaveformControl::getPlaybackDirectory() ;
}


//-------------------------------------------------------------------------------------------------------------
std::string WaveformManager::getCaptureDirectory() const
{
	return WaveformControl::getCaptureDirectory() ;
}




//-------------------------------------------------------------------------------------------------------------
void WaveformManager::show(std::ostream& os) const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	os << "Waveforms" << std::endl ;
	for (WaveformMapConstIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		os << (*iter->second) ;
	}
	os << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformManager::show(const std::string& waveName, std::ostream& os) const
{
	// Need to mutex protect from test interfaces
	Mutex::Lock lock(mMutex) ;

	std::shared_ptr<IWaveformControl> waveControl(getWaveformControl(waveName)) ;

	if (waveControl.get() == 0)
	{
		os << "Wave " << waveName << " not found" << std::endl ;
	}
	else
	{
		os << *waveControl << std::endl ;
	}
}


//-------------------------------------------------------------------------------------------------------------
void WaveformManager::showWaveformReg(const std::string& waveName, std::ostream& os)
{
	// Can only support name wN where N = 0 .. max resources
	if (!validWaveName(waveName))
		return ;

	unsigned waveIdx = waveNameToIndex(waveName) ;
	mWaveformResources[waveIdx]->showWaveformReg(os) ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformManager::showWaveformMasterReg(std::ostream& os)
{
	mWaveformResources[0]->showWaveformMasterReg(os) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IFileMgr> WaveformManager::getPlaybackFileMgr()
{
	return IFileMgr::factory(WaveformControl::getPlaybackDirectory()) ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IWaveformControl> WaveformManager::getWaveformControl(const std::string& name) const
{
	WaveformMapConstIter iter(mWaveformMap.find(name)) ;
	if (iter == mWaveformMap.end())
		return std::shared_ptr<IWaveformControl>() ;

	return iter->second ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::allocateCapture()
{
	for (WaveformMapIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		// if it's enabled for capture
		if ( iter->second->getWaveform()->getType() != Waveform::WAVEFORM_CAPTURE )
			continue ;
		if ( !iter->second->getWaveform()->isEnable() )
			continue ;

		// if already allocated AND no changes then skip
		if ( iter->second->getWaveformHardware() &&
			 iter->second->getWaveform() &&
			 !iter->second->getWaveform()->isValueChanged() )
			continue ;

		//Get wave index
		unsigned waveIdx = waveNameToIndex(iter->first);

		// Allocate resources - nailed for now
		std::string error ;
		if (!iter->second->setWaveformHardware( mWaveformResources[waveIdx], error ) )
		{
			std::stringstream ss ;
			ss << "Failed to allocate hardware for " << iter->first << " " << error ;
			mError = ss.str() ;
			return false ;
		}

	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::scheduleCapture()
{
	// Iterate through the enabled waves - create a list which sums up the total interface data rate
	struct WaveRate {
		WaveRate(std::shared_ptr<IWaveformControl> _waveControl, unsigned _sampleRateKsps) :
			waveControl(_waveControl),
			sampleRateKsps(_sampleRateKsps)
		{}
		std::shared_ptr<IWaveformControl> waveControl ;
		unsigned sampleRateKsps ;
	};

//std::cerr << "[scheduleCapture] START" << std::endl ;

	std::vector<WaveRate> waveList ;
	unsigned totalRateKsps{0} ;
	for (auto entry : mWaveformMap)
	{
		// skip non-enabled
		if ( !entry.second->getWaveform()->isEnable() )
			continue ;

		// skip if wave module doesn't use the fpga bus
		if ( !entry.second->getWaveformHardware() || !entry.second->getWaveformHardware()->usesFpgaBus() )
			continue ;

		// clear out the trigger delay
		entry.second->getWaveform()->setDelayFrames(0) ;

		// get current settings
		unsigned rateKsps(entry.second->getWaveform()->getSampleRateKsps()) ;
		waveList.push_back(WaveRate(entry.second, rateKsps)) ;
		totalRateKsps += rateKsps ;
//std::cerr << "[scheduleCapture] * " << entry.first << " rate=" << rateKsps << " (total=" << totalRateKsps << ")" << std::endl ;

	}

//std::cerr << "[scheduleCapture] Total Rate: " << totalRateKsps << std::endl ;

	// If total rate is lower than the max then we're ok
	if (totalRateKsps <= MAX_INTERFACE_KSPS)
		return true ;

//std::cerr << "[scheduleCapture] ** Delay RF Capture **" << std::endl ;

	// Need to try delaying any high rate (RF) captures then see if the 2 new sets are within the limit
	std::vector<WaveRate> delayedList ;
	totalRateKsps = 0 ;
	unsigned totalDelayedRateKsps{0} ;
	unsigned maxCapture{0} ;
	unsigned earliestTrigger{0} ;
	for (auto entry : waveList)
	{
		// if it's enabled for capture
		if ( entry.waveControl->getWaveform()->getType() != Waveform::WAVEFORM_CAPTURE )
			continue ;

		// For all high-rate captures, move to the delayed list
		if (entry.sampleRateKsps >= HIGH_RATE_KSPS)
		{
			// Work out the earliest trigger
			unsigned trigger(entry.waveControl->getWaveform()->getTrigger()) ;
			if (delayedList.empty())
				earliestTrigger = trigger ;
			else if (earliestTrigger > trigger)
				earliestTrigger = trigger ;

//std::cerr << "[scheduleCapture] * * High rate : trigger=" << trigger << " earliest=" << earliestTrigger << std::endl ;

			delayedList.push_back(entry) ;
			totalDelayedRateKsps += entry.sampleRateKsps ;
		}
		else
		{
			// Lower rate capture
			totalRateKsps += entry.sampleRateKsps ;

			// keep track of when all captures in this list will end
			unsigned captureEnd(entry.waveControl->getWaveform()->getCaptureEnd()) ;
//std::cerr << "[scheduleCapture] * * Low rate : capture end=" << captureEnd << " max end=" << maxCapture <<
//		" trigger=" << entry.waveControl->getWaveform()->getTrigger() <<
//		" depth=" << entry.waveControl->getWaveform()->getDepth() <<
//		" rate=" << entry.waveControl->getWaveform()->getSampleRateKsps() <<
//		std::endl ;

			if (maxCapture < captureEnd)
				maxCapture = captureEnd ;
		}
	}

//std::cerr << "[scheduleCapture] maxCapture=" << maxCapture << " earliestTrigger=" << earliestTrigger << std::endl ;
//std::cerr << "[scheduleCapture] Now Total Rate: " << totalRateKsps << std::endl ;
//std::cerr << "[scheduleCapture] Delayed Rate: " << totalDelayedRateKsps << std::endl ;

	// Check both sets can be accommodated in the interface
	if (totalRateKsps > MAX_INTERFACE_KSPS)
	{
		mError = "Total rate of all captures exceeds maximum, unable to schedule captures" ;
		return false ;
	}
	if (totalDelayedRateKsps > MAX_INTERFACE_KSPS)
	{
		mError = "Total rate of delayed captures exceeds maximum, unable to schedule captures" ;
		return false ;
	}

	// If earliest trigger is after any existing captures end then we should be ok
	if (maxCapture <= earliestTrigger)
		return true ;

	// Now we need to adjust the delayed captures such that they start after the last normal capture finishes
	unsigned numFrames( ((maxCapture - earliestTrigger) + TRIGGER_FRAME-1) / TRIGGER_FRAME ) ;
//std::cerr << "[scheduleCapture] numFrames=" << numFrames << std::endl ;
	for (auto entry : delayedList)
	{
		// Adjust the trigger by this many air frames
		entry.waveControl->getWaveform()->setDelayFrames(numFrames) ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::validateCapture()
{
	for (WaveformMapIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		// if it's enabled for capture
		if ( iter->second->getWaveform()->getType() != Waveform::WAVEFORM_CAPTURE )
			continue ;
		if ( !iter->second->getWaveform()->isEnable() )
			continue ;

		// Validate
		std::string error ;
		if ( !iter->second->validate(error) )
		{
			// clear enable so we don't keep reporting this
			iter->second->getWaveform()->setEnable(false) ;

			// return error
			std::stringstream ss ;
			ss << "Failed to validate hardware for " << iter->first << " " << error ;
			mError = ss.str() ;
			return false ;
		}
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::updateHardwareCapture()
{
	for (WaveformMapIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		// if it's enabled for capture
		if ( iter->second->getWaveform()->getType() != Waveform::WAVEFORM_CAPTURE )
			continue ;
		if ( !iter->second->getWaveform()->isEnable() )
			continue ;

		// Do update
		std::string error ;
		if ( !iter->second->updateHardware(error) )
		{
			std::stringstream ss ;
			ss << "Failed to update hardware for " << iter->first << " " << error ;
			mError = ss.str() ;
			return false ;
		}
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::deallocateCapture()
{
	for (WaveformMapIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		// if it's enabled for capture
		if ( iter->second->getWaveform()->getType() != Waveform::WAVEFORM_CAPTURE )
			continue ;
		if ( !iter->second->getWaveform()->isEnable() )
			continue ;

		// Deallocate
		std::string error ;
		iter->second->setWaveformHardware( std::shared_ptr<WaveformHardware>(), error ) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::allocatePlayback()
{
	for (WaveformMapIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		// if it's enabled for playback
		if ( iter->second->getWaveform()->getType() != Waveform::WAVEFORM_PLAYBACK )
			continue ;
		if ( !iter->second->getWaveform()->isEnable() )
			continue ;

		// if already allocated AND no changes then skip
		if ( iter->second->getWaveformHardware() &&
				iter->second->getWaveform() && ! iter->second->getWaveform()->isValueChanged() )
			continue ;

		//Get wave index
		unsigned waveIdx = waveNameToIndex(iter->first);

		// Allocate resources - nailed for now
		std::string error ;
		if (!iter->second->setWaveformHardware( mWaveformResources[waveIdx], error ) )
		{
			std::stringstream ss ;
			ss << "Failed to allocate hardware for " << iter->first << " " << error ;
			mError = ss.str() ;
			return false ;
		}


	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::validatePlayback()
{
	for (WaveformMapIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		// if it's enabled for playback
		if ( iter->second->getWaveform()->getType() != Waveform::WAVEFORM_PLAYBACK )
			continue ;
		if ( !iter->second->getWaveform()->isEnable() )
			continue ;

		// Validate
		std::string error ;
		if ( !iter->second->validate(error) )
		{
			// clear enable so we don't keep reporting this
			iter->second->getWaveform()->setEnable(false) ;

			std::stringstream ss ;
			ss << "Failed to validate hardware for " << iter->first << " : " << error ;
			mError = ss.str() ;
			return false ;
		}
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::updateHardwarePlayback()
{
	for (WaveformMapIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		// if it's enabled for capture
		if ( iter->second->getWaveform()->getType() != Waveform::WAVEFORM_PLAYBACK )
			continue ;
		if ( !iter->second->getWaveform()->isEnable() )
			continue ;

		// Do update
		std::string error ;
		if ( !iter->second->updateHardware(error) )
		{
			std::stringstream ss ;
			ss << "Failed to update hardware for " << iter->first << " : " << error ;
			mError = ss.str() ;
			return false ;
		}
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::deallocatePlayback()
{
	for (WaveformMapIter iter(mWaveformMap.begin()); iter != mWaveformMap.end(); ++iter)
	{
		// if it's enabled for capture
		if ( iter->second->getWaveform()->getType() != Waveform::WAVEFORM_PLAYBACK )
			continue ;
		if ( !iter->second->getWaveform()->isEnable() )
			continue ;

		// Deallocate
		std::string error ;
		iter->second->setWaveformHardware( std::shared_ptr<WaveformHardware>(), error ) ;
	}
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformManager::getPortFromWaveName(const std::string& name) const
{
	std::map<std::string, unsigned>::const_iterator iter;

	iter = mWaveformPortMap.find(name) ;
	if (iter == mWaveformPortMap.end())
		return 0 ;

	return iter->second ;
}

//-------------------------------------------------------------------------------------------------------------
unsigned WaveformManager::waveNameToIndex(const std::string& name) const
{
	if (name == "wrxcal")
		return numResources() - 3 ;
	else if (name == "wrxcal1")
		return numResources() - 2;
	else if (name == "wrxcal2")
		return numResources() - 1;

	unsigned waveIdx = 0 ;
	try {
		waveIdx = static_cast<unsigned>(std::stoul(name.substr(1))) ;
	}
	catch (...)
	{
		waveIdx = 0 ;
	}
	return waveIdx ;
}

//-------------------------------------------------------------------------------------------------------------
bool WaveformManager::validWaveName(const std::string& name)
{
	std::stringstream ss ;
	ss << "Must use names w0 to w" << (numResources()-4) << ", or wrxcal or wrxcal1 or wrxcal2" ;

	// must of form wYYYY
	if (name[0] != 'w')
	{
		mError = ss.str() ;
		return false ;
	}

	// special case name
	if (name == "wrxcal" || name == "wrxcal1" || name == "wrxcal2")
		return true ;


	// must be of the form wX or wXX
	std::size_t size(name.size()) ;
	if (size != 2 && size != 3)
	{
		mError = ss.str() ;
		return false ;
	}

	if (!isdigit(name[1]))
	{
		mError = ss.str() ;
		return false ;
	}

	if (size == 3 && !isdigit(name[2]))
	{
		mError = ss.str() ;
		return false ;
	}

	if (waveNameToIndex(name) >= numResources())
	{
		mError = ss.str() ;
		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IWaveformControl> Mplane::WaveformManager::createWaveControl() const
{
	return std::make_shared<WaveformControl>() ;
}

//-------------------------------------------------------------------------------------------------------------
void WaveformManager::setError(const std::string& error)
{
	mError = error ;
}

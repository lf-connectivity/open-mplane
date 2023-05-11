/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SharedArbTestHelper.cpp
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
#include <memory>

#include "Path.h"
#include "IWaveformManager.h"
#include "ICarrierServer.h"
#include "IRadio.h"

#include "RtiKeyword.h"
#include "SharedArbTestHelper.h"

using namespace Mplane;


//=============================================================================================================
// CONSTANTS
//=============================================================================================================

// with the hard coded fpga
const unsigned NUM_PORTS = 2 ;

// Carrier used for normal data
const unsigned CARRIER_NO_INDEX = 99 ;
const unsigned CARRIER_INDEX = 1 ;
const unsigned CARRIER_MULTICAST_INDEX = 0 ;
const unsigned NUM_CARRIERS = 2 ;

#define DEBUG_ARB
#ifdef DEBUG_ARB
#define LOG_DEBUG_ARB(fmt, args...) logDebugVerbose(fmt, ## args)
#else
#define LOG_DEBUG_ARB(fmt, args...)
#endif

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<SharedArbTestHelper> SharedArbTestHelper::getInstance()
{
	static std::shared_ptr<SharedArbTestHelper> instance(new SharedArbTestHelper) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SharedArbTestHelper::~SharedArbTestHelper()
{
}

//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::set(DataVariantList* callList, DataVariantList* returnList)
{
	Mutex::Lock lock(mMutex) ;

	mAirStd = "" ;
	mBw = "" ;

	// Disable all carriers
	if (mCarriersRequired)
	{
		if (!setAllCarriersState(false, returnList))
			return ;
	}

	// ensure all waveform playback/capture is disabled
	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	waveformMgr->setCapturePlayback(false, false) ;

	logDebugNormal("arb: PLAYBACK OFF");
	logDebugNormal("arb: CAPTURE OFF");

	LOG_DEBUG_ARB("[ARB] .waveform.start playback=off capture=off") ;

	// Set centre freq using current frequency
	std::shared_ptr<ITxPort> txPort = getTxPort( 0, returnList );
	Frequency centreFreq( txPort->getFrequency() );


	// Set up the carriers here
	std::string airstd(callList->find("airstd")->toString()) ;
	std::string bw(callList->find("bw")->toString()) ;

	unsigned groupSize(1) ;
	if (bw == "1_4")
		groupSize = 1 ;
	else if (bw == "3")
		groupSize = 1 ;
	else if (bw == "5")
		groupSize = 2 ;
	if (bw == "10")
		groupSize = 4 ;
	else if (bw == "15")
		groupSize = 6 ;
	else if (bw == "20")
		groupSize = 8 ;

	std::string carrierType(airstd + bw) ;

	if (mCarriersRequired)
	{
		if (!setCarrier(CARRIER_INDEX, carrierType, centreFreq, groupSize, returnList))
			return ;

		if (!setCarrier(CARRIER_MULTICAST_INDEX, carrierType, centreFreq, groupSize, returnList))
			return ;
	}

	// Now ok to save settings
	mAirStd = airstd ;
	mBw = bw ;

}

//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::show(DataVariantList* callList, DataVariantList* returnList)
{
	Mutex::Lock lock(mMutex) ;

	std::stringstream ss ;
	ss << std::endl ;

	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;

	ss << "Air Std......: " << mAirStd << std::endl ;
	ss << "BW...........: " << mBw << (mBw.empty() ? "" : "MHz") << std::endl ;
	ss << "Playback.....: " << (waveformMgr->isPlaybackEnabled() ? "Enabled" : "Disabled") << std::endl ;
	ss << "Capture......: " << (waveformMgr->isCaptureEnabled() ? "Enabled" : "Disabled") << std::endl ;
	ss << "Multicast....: " << (mPlaybackMulticast ? "Enabled" : "Disabled") << std::endl ;

	unsigned port = 1 ;
	for (auto entry : mRfPlayback)
	{
		ss << "RF Playback Port " << port << std::endl ;
		ss << " * File.........: " << entry.getFilename() << std::endl ;
		ss << " * Depth........: " << entry.getDepth() << std::endl ;
		ss << " * Enable.......: " << (entry.isEnable() ? "on" : "off") << std::endl ;
		ss << " * Hw Present...: " << (entry.isResourcePresent() ? "yes" : "no") << std::endl ;
		ss << " * Trigger......: " << entry.getTrigger() << std::endl ;
		ss << " * Wave.........: " << entry.getWavename() << std::endl ;

		++port ;
	}

	port = 1 ;
	for (auto entry : mCpriPlayback)
	{
		ss << "CPRI Playback Port " << port << std::endl ;
		ss << " * File.........: " << entry.getFilename() << std::endl ;
		ss << " * Depth........: " << entry.getDepth() << std::endl ;
		ss << " * Enable.......: " << (entry.isEnable() ? "on" : "off") << std::endl ;
		ss << " * Hw Present...: " << (entry.isResourcePresent() ? "yes" : "no") << std::endl ;
		ss << " * Trigger......: " << entry.getTrigger() << std::endl ;
		ss << " * Wave.........: " << entry.getWavename() << std::endl ;

		++port ;
	}

	port = 1 ;
	for (auto entry : mRfCapture)
	{
		ss << "RF Capture Port " << port << std::endl ;
		ss << " * File.........: " << entry.getFilename() << std::endl ;
		ss << " * Depth........: " << entry.getDepth() << std::endl ;
		ss << " * Enable.......: " << (entry.isEnable() ? "on" : "off") << std::endl ;
		ss << " * Hw Present...: " << (entry.isResourcePresent() ? "yes" : "no") << std::endl ;
		ss << " * Trigger......: " << entry.getTrigger() << std::endl ;
		ss << " * Wave.........: " << entry.getWavename() << std::endl ;

		++port ;
	}

	port = 1 ;
	for (auto entry : mCpriCapture)
	{
		ss << "CPRI Capture Port " << port << std::endl ;
		ss << " * File.........: " << entry.getFilename() << std::endl ;
		ss << " * Depth........: " << entry.getDepth() << std::endl ;
		ss << " * Enable.......: " << (entry.isEnable() ? "on" : "off") << std::endl ;
		ss << " * Hw Present...: " << (entry.isResourcePresent() ? "yes" : "no") << std::endl ;
		ss << " * Trigger......: " << entry.getTrigger() << std::endl ;
		ss << " * Wave.........: " << entry.getWavename() << std::endl ;

		++port ;
	}

	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;
}

//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::cpriCapture(DataVariantList* callList, DataVariantList* returnList)
{
	Mutex::Lock lock(mMutex) ;

	if (!checkSettings(returnList))
		return ;

	unsigned port ;
	if (!getPortNum(port, callList, returnList) )
		return ;

	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	std::string wavename(mCpriCapture[port].getWavename()) ;

#ifdef DEBUG_ARB
	std::string waveStr("[ARB] .waveform.set " + wavename + " capture ") ;
#endif

	if (!mCpriCapture[port].isResourcePresent())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Hardware resource not present") ;
		return ;
	}

	// filename
	if (callList->find("waveform")->isSet())
	{
		mCpriCapture[port].setFilename(callList->find("waveform")->toString()) ;
		waveformMgr->setFilename(wavename, mCpriCapture[port].getFilename() ) ;

#ifdef DEBUG_ARB
		waveStr.append("filename=" + mCpriCapture[port].getFilename() + " ") ;
#endif
	}

	// trigger
	if (callList->find("trigger")->isSet())
	{
		mCpriCapture[port].setTrigger(callList->find("trigger")->toInt()) ;
		waveformMgr->setTrigger(wavename, mCpriCapture[port].getTrigger()) ;

#ifdef DEBUG_ARB
		waveStr.append("trigger=" + std::to_string(mCpriCapture[port].getTrigger()) + " ") ;
#endif
	}

	// depth
	if (callList->find("depth")->isSet())
	{
		mCpriCapture[port].setDepth(callList->find("depth")->toInt()) ;
		waveformMgr->setDepth(wavename, mCpriCapture[port].getDepth()) ;

#ifdef DEBUG_ARB
		waveStr.append("depth=" + std::to_string(mCpriCapture[port].getDepth()) + " ") ;
#endif
	}

	// ** Must set enable last - this causes the waveform settings to get applied **
	// enable
	if (callList->find("enable")->isSet())
	{
		mCpriCapture[port].setEnable(callList->find("enable")->toBool()) ;
		waveformMgr->setEnable(wavename, mCpriCapture[port].isEnable()) ;

#ifdef DEBUG_ARB
		waveStr.append(std::string("enable=") + (mCpriCapture[port].isEnable() ? "on" : "off") + " ") ;
#endif
	}

#ifdef DEBUG_ARB
	LOG_DEBUG_ARB(waveStr) ;
#endif

	// Check for errors
	std::string error(waveformMgr->getErrorReason()) ;
	if (!error.empty())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(error) ;
		return ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::cpriPlayback(DataVariantList* callList, DataVariantList* returnList)
{
	Mutex::Lock lock(mMutex) ;

	if (!checkSettings(returnList))
		return ;

	unsigned port ;
	if (!getPortNum(port, callList, returnList) )
		return ;

	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	std::string wavename(mCpriPlayback[port].getWavename()) ;

#ifdef DEBUG_ARB
	std::string waveStr("[ARB] .waveform.set " + wavename + " playback ") ;
#endif

	if (!mCpriPlayback[port].isResourcePresent())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Hardware resource not present") ;
		return ;
	}

	// filename
	if (callList->find("waveform")->isSet())
	{
		mCpriPlayback[port].setFilename(callList->find("waveform")->toString()) ;

		// get waveform depth from file size
		waveformMgr->setFilename(wavename, mCpriPlayback[port].getFilename() ) ;
		mCpriPlayback[port].setDepth( waveformMgr->getFileDepth(wavename) ) ;
		if ( mCpriPlayback[port].getDepth() == 0 )
		{
			// disable waveform
			mCpriPlayback[port].setEnable(false) ;
			waveformMgr->setEnable(wavename, mCpriPlayback[port].isEnable()) ;

			// error
			returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
			returnList->find(RtiKeyword::MESSAGE_VAR)->set("Unable to determine file size (does file exist?)") ;
			return ;
		}
		waveformMgr->setDepth(wavename, mCpriPlayback[port].getDepth() ) ;

#ifdef DEBUG_ARB
		waveStr.append("filename=" + mCpriPlayback[port].getFilename() +
				" depth=" + std::to_string(mCpriPlayback[port].getDepth()) + " ") ;
#endif
	}

	// trigger
	if (callList->find("trigger")->isSet())
	{
		mCpriPlayback[port].setTrigger(callList->find("trigger")->toInt()) ;
		waveformMgr->setTrigger(wavename, mCpriPlayback[port].getTrigger()) ;

#ifdef DEBUG_ARB
		waveStr.append("trigger=" + std::to_string(mCpriPlayback[port].getTrigger()) + " ") ;
#endif
	}


	// ** Must set enable last - this causes the waveform settings to get applied **
	// enable
	if (callList->find("enable")->isSet())
	{
		mCpriPlayback[port].setEnable(callList->find("enable")->toBool()) ;
		waveformMgr->setEnable(wavename, mCpriPlayback[port].isEnable()) ;

#ifdef DEBUG_ARB
		waveStr.append(std::string("enable=") + (mCpriPlayback[port].isEnable() ? "on" : "off") + " ") ;
#endif
	}

#ifdef DEBUG_ARB
	waveStr.append("carrier=" + std::to_string(mCpriPlayback[port].getCarrier())) ;
	LOG_DEBUG_ARB(waveStr) ;
#endif

	// Check for errors
	std::string error(waveformMgr->getErrorReason()) ;
	if (!error.empty())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(error) ;
		return ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::rfCapture(DataVariantList* callList, DataVariantList* returnList)
{
	Mutex::Lock lock(mMutex) ;

	if (!checkSettings(returnList))
		return ;

	unsigned port ;
	if (!getPortNum(port, callList, returnList) )
		return ;

	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	std::string wavename(mRfCapture[port].getWavename()) ;

#ifdef DEBUG_ARB
	std::string waveStr("[ARB] .waveform.set " + wavename + " capture ") ;
#endif

	if (!mRfCapture[port].isResourcePresent())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Hardware resource not present") ;
		return ;
	}

	// filename
	if (callList->find("waveform")->isSet())
	{
		mRfCapture[port].setFilename(callList->find("waveform")->toString()) ;
		waveformMgr->setFilename(wavename, mRfCapture[port].getFilename() ) ;

#ifdef DEBUG_ARB
		waveStr.append("filename=" + mRfCapture[port].getFilename() + " ") ;
#endif
	}

	// trigger
	if (callList->find("trigger")->isSet())
	{
		mRfCapture[port].setTrigger(callList->find("trigger")->toInt()) ;
		waveformMgr->setTrigger(wavename, mRfCapture[port].getTrigger()) ;

#ifdef DEBUG_ARB
		waveStr.append("trigger=" + std::to_string(mRfCapture[port].getTrigger()) + " ") ;
#endif
	}

	// depth
	if (callList->find("depth")->isSet())
	{
		mRfCapture[port].setDepth(callList->find("depth")->toInt()) ;
		waveformMgr->setDepth(wavename, mRfCapture[port].getDepth()) ;

#ifdef DEBUG_ARB
		waveStr.append("depth=" + std::to_string(mRfCapture[port].getDepth()) + " ") ;
#endif
	}

	// ** Must set enable last - this causes the waveform settings to get applied **
	// enable
	if (callList->find("enable")->isSet())
	{
		mRfCapture[port].setEnable(callList->find("enable")->toBool()) ;
		waveformMgr->setEnable(wavename, mRfCapture[port].isEnable()) ;

#ifdef DEBUG_ARB
		waveStr.append(std::string("enable=") + (mRfCapture[port].isEnable() ? "on" : "off") + " ") ;
#endif
	}

#ifdef DEBUG_ARB
	LOG_DEBUG_ARB(waveStr) ;
#endif

	// Check for errors
	std::string error(waveformMgr->getErrorReason()) ;
	if (!error.empty())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(error) ;
		return ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::rfPlayback(DataVariantList* callList, DataVariantList* returnList)
{
	Mutex::Lock lock(mMutex) ;

	if (!checkSettings(returnList))
		return ;

	unsigned port ;
	if (!getPortNum(port, callList, returnList) )
		return ;

	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	std::string wavename(mRfPlayback[port].getWavename()) ;

#ifdef DEBUG_ARB
	std::string waveStr("[ARB] .waveform.set " + wavename + " playback ") ;
#endif

	if (!mRfPlayback[port].isResourcePresent())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Hardware resource not present") ;
		return ;
	}

	// filename
	if (callList->find("waveform")->isSet())
	{
		mRfPlayback[port].setFilename(callList->find("waveform")->toString()) ;

		// get waveform depth from file size
		waveformMgr->setFilename(wavename, mRfPlayback[port].getFilename() ) ;
		mRfPlayback[port].setDepth( waveformMgr->getFileDepth(wavename) ) ;
		if ( mRfPlayback[port].getDepth() == 0 )
		{
			// disable waveform
			mRfPlayback[port].setEnable(false) ;
			waveformMgr->setEnable(wavename, mRfPlayback[port].isEnable()) ;

			// error
			returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
			returnList->find(RtiKeyword::MESSAGE_VAR)->set("Unable to determine file size (does file exist?)") ;
			return ;
		}
		waveformMgr->setDepth(wavename, mRfPlayback[port].getDepth() ) ;

#ifdef DEBUG_ARB
		waveStr.append("filename=" + mRfPlayback[port].getFilename() +
				" depth=" + std::to_string(mRfPlayback[port].getDepth()) + " ") ;
#endif
	}

	// trigger
	if (callList->find("trigger")->isSet())
	{
		mRfPlayback[port].setTrigger(callList->find("trigger")->toInt()) ;
		waveformMgr->setTrigger(wavename, mRfPlayback[port].getTrigger()) ;

#ifdef DEBUG_ARB
		waveStr.append("trigger=" + std::to_string(mRfPlayback[port].getTrigger()) + " ") ;
#endif
	}


	// ** Must set enable last - this causes the waveform settings to get applied **
	// enable
	if (callList->find("enable")->isSet())
	{
		mRfPlayback[port].setEnable(callList->find("enable")->toBool()) ;
		waveformMgr->setEnable(wavename, mRfPlayback[port].isEnable()) ;

#ifdef DEBUG_ARB
		waveStr.append(std::string("enable=") + (mRfPlayback[port].isEnable() ? "on" : "off") + " ") ;
#endif
	}

#ifdef DEBUG_ARB
	waveStr.append("carrier=" + std::to_string(mRfPlayback[port].getCarrier())) ;
	LOG_DEBUG_ARB(waveStr) ;
#endif

	// Check for errors
	std::string error(waveformMgr->getErrorReason()) ;
	if (!error.empty())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(error) ;
		return ;
	}
}


//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::playbackStart(DataVariantList* callList, DataVariantList* returnList)
{
	logDebugNormal("arb: Playback start");

	Mutex::Lock lock(mMutex) ;

	if (!checkSettings(returnList))
		return ;

	// Disable all carriers
	if (mCarriersRequired)
	{
		if (!setAllCarriersState(false, returnList))
			return ;
	}

	// playback enable
	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	if (!waveformMgr->isPlaybackEnabled())
	{
		LOG_DEBUG_ARB("[ARB] .waveform.start playback=on capture=on") ;

		if (!waveformMgr->setCapturePlayback(waveformMgr->isCaptureEnabled(), true))
		{
			returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
			returnList->find(RtiKeyword::MESSAGE_VAR)->set(waveformMgr->getErrorReason()) ;
			return ;
		}

		logDebugNormal("arb: PLAYBACK ON");
		logDebugNormal("arb: CAPTURE %s", (waveformMgr->isCaptureEnabled() ? "ON" : "OFF"));
	}

	// skip carrier setup if not required
	if (!mCarriersRequired)
		return ;

	// Enable carriers
	if (mPlaybackMulticast)
	{
		if (!setAllCarriersState(true, returnList))
			return ;
	}
	else
	{
		if (!setCarrierState(CARRIER_INDEX, true, returnList))
			return ;
	}

}

//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::playbackStop(DataVariantList* callList, DataVariantList* returnList)
{
	logDebugNormal("arb: Playback stop");

	Mutex::Lock lock(mMutex) ;

	if (!checkSettings(returnList))
		return ;

	// Disable all carriers
	if (mCarriersRequired)
	{
		if (!setAllCarriersState(false, returnList))
			return ;
	}

	LOG_DEBUG_ARB("[ARB] .waveform.start playback=off capture=off") ;

	// stop playback
	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	if (!waveformMgr->setCapturePlayback(false, false))
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(waveformMgr->getErrorReason()) ;
		return ;
	}

	logDebugNormal("arb: PLAYBACK OFF");
	logDebugNormal("arb: CAPTURE OFF");
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::SharedArbTestHelper::playbackFiles(DataVariantList* callList, DataVariantList* returnList) const
{
	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	std::string path(waveformMgr->getPlaybackDirectory()) ;
	if (callList->find("path")->isSet())
	{
		path = callList->find("path")->toString() ;
	}

	showFiles(path, returnList) ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::SharedArbTestHelper::playbackMulticast(DataVariantList* callList, DataVariantList* returnList)
{
	Mutex::Lock lock(mMutex) ;

	bool enable(callList->find("enable")->toBool()) ;
	if (enable == mPlaybackMulticast)
		return ;

	if (mCarriersRequired)
	{
		if (!setCarrierState(CARRIER_MULTICAST_INDEX, enable, returnList))
			return ;
	}

	mPlaybackMulticast = enable ;
}



//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::captureStart(DataVariantList* callList, DataVariantList* returnList)
{
	logDebugNormal("arb: Capture start");

	Mutex::Lock lock(mMutex) ;

	if (!checkSettings(returnList))
		return ;

	// check that carriers are enabled and playback is on
	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	if (mCarriersRequired)
	{
		bool ok(true) ;
		ICarrierSetter& carrierMainSetter( getCarrierSetter(ok, CARRIER_INDEX, returnList) ) ;
		if (!ok)
			return ;

		if (
			(carrierMainSetter.getState() != ICarrier::STATE_ENABLE) ||
			!waveformMgr->isPlaybackEnabled()
		)
		{
			// set an error
			returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
			returnList->find(RtiKeyword::MESSAGE_VAR)->set("Cannot start capture until playback is started") ;
			return ;
		}
	}
	LOG_DEBUG_ARB("[ARB] .waveform.start playback=on capture=on") ;

	// start capture
	if (!waveformMgr->setCapturePlayback(true, true))
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(waveformMgr->getErrorReason()) ;
		return ;
	}

	logDebugNormal("arb: PLAYBACK ON");
	logDebugNormal("arb: CAPTURE ON");
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::SharedArbTestHelper::captureFiles(DataVariantList* callList, DataVariantList* returnList) const
{
	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;
	std::string path(waveformMgr->getCaptureDirectory()) ;
	if (callList->find("path")->isSet())
	{
		path = callList->find("path")->toString() ;
	}

	showFiles(path, returnList) ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SharedArbTestHelper::SharedArbTestHelper() :
	Loggable("ARB", "TIF"),
	mAirStd(""),
	mBw(""),
	mCarriersRequired(false),
	mPlaybackMulticast(false)
{
	// DEBUG: While I'm debugging the measurements, enable everything
//	ILoggable::setInstanceLogDebugLevel(ILoggable::LOG_DEBUG_VERBOSE, "ARB") ;

	init() ;
}

//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::init()
{
	std::shared_ptr<IWaveformManager> waveformMgr(IWaveformManager::getInstance()) ;

	// Create the waveforms used - currently the FPGA is hard coded
	waveformMgr->createWave("w0", IWaveform::WAVEFORM_CAPTURE) ;
	waveformMgr->createWave("w1", IWaveform::WAVEFORM_CAPTURE) ;
	waveformMgr->createWave("w2", IWaveform::WAVEFORM_PLAYBACK) ;
	waveformMgr->createWave("w3", IWaveform::WAVEFORM_PLAYBACK) ;
	waveformMgr->createWave("w4", IWaveform::WAVEFORM_CAPTURE) ;
	waveformMgr->createWave("w5", IWaveform::WAVEFORM_CAPTURE) ;
	waveformMgr->createWave("w6", IWaveform::WAVEFORM_PLAYBACK) ;
	waveformMgr->createWave("w7", IWaveform::WAVEFORM_PLAYBACK) ;

	waveformMgr->setCarrierIdx("w2", CARRIER_INDEX) ;
	waveformMgr->setCarrierIdx("w3", CARRIER_INDEX) ;
	waveformMgr->setCarrierIdx("w4", CARRIER_INDEX) ;
	waveformMgr->setCarrierIdx("w5", CARRIER_INDEX) ;
	waveformMgr->setCarrierIdx("w6", CARRIER_INDEX) ;
	waveformMgr->setCarrierIdx("w7", CARRIER_INDEX) ;


	// Set up playback settings
	mCpriPlayback.push_back(ArbPlayback("w2", waveformMgr->isResourcePresent(2), CARRIER_INDEX)) ;
	mCpriPlayback.push_back(ArbPlayback("w3", waveformMgr->isResourcePresent(3), CARRIER_INDEX)) ;
	mRfPlayback.push_back(ArbPlayback("w6", waveformMgr->isResourcePresent(6), CARRIER_INDEX)) ;
	mRfPlayback.push_back(ArbPlayback("w7", waveformMgr->isResourcePresent(7), CARRIER_INDEX)) ;

	// Set up capture settings
	mCpriCapture.push_back(ArbCapture("w4", waveformMgr->isResourcePresent(4), CARRIER_INDEX)) ;
	mCpriCapture.push_back(ArbCapture("w5", waveformMgr->isResourcePresent(5), CARRIER_INDEX)) ;
	mRfCapture.push_back(ArbCapture("w0", waveformMgr->isResourcePresent(0), CARRIER_NO_INDEX)) ;
	mRfCapture.push_back(ArbCapture("w1", waveformMgr->isResourcePresent(1), CARRIER_NO_INDEX)) ;


	// determine whether carrier setup is required
	mCarriersRequired = false ;
	for (auto entry : mCpriPlayback)
	{
		if (entry.isResourcePresent())
			mCarriersRequired = true ;
	}
	for (auto entry : mRfPlayback)
	{
		if (entry.isResourcePresent())
			mCarriersRequired = true ;
	}

	logDebugNormal("arb: Init waveforms (carrier setup required?=%u", (unsigned)mCarriersRequired);

}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ICarrierSetter& SharedArbTestHelper::getCarrierSetter(bool& ok, unsigned index, DataVariantList *returnList) const
{
	ok = true ;
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance()) ;
	if (index >= carrierServer->getMaxCarriers())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );

		std::stringstream ss ;
		ss << "Index " << index << " outside valid range (Number of carrier " << carrierServer->getMaxCarriers() << ")" ;
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(ss.str()) ;

		ok = false ;
		return carrierServer->getCarrierSetter(0) ;
	}

	return carrierServer->getCarrierSetter(index) ;
}

//-------------------------------------------------------------------------------------------------------------
const ICarrier& SharedArbTestHelper::getCarrier(bool& ok, unsigned index, DataVariantList *returnList) const
{
	ok = true ;
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance()) ;
	if (index >= carrierServer->getMaxCarriers())
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );

		std::stringstream ss ;
		ss << "Index " << index << " outside valid range (Number of carrier " << carrierServer->getMaxCarriers() << ")" ;
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(ss.str()) ;

		ok = false ;
		return carrierServer->getCarrier(0) ;
	}

	return carrierServer->getCarrier(index) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ITxPort> SharedArbTestHelper::getTxPort(unsigned index, DataVariantList *returnList) const
{
    std::vector< std::shared_ptr<ITxPort> > txPorts = ITxPortFactory::getPorts( ) ;

    if( index >= static_cast<unsigned>(IRadioFactory::getInterface()->getNumberOfTxPorts() ))
    {
        returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );

        std::stringstream ss ;
        ss << "index " << index+1 << " outside valid range (Number of ports "
                << IRadioFactory::getInterface()->getNumberOfTxPorts() << ")" ;
        returnList->find(RtiKeyword::MESSAGE_VAR)->set(ss.str()) ;

        return std::shared_ptr<ITxPort>() ;
    }
    return txPorts[index];
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IRxPort> SharedArbTestHelper::getRxPort(unsigned index, DataVariantList *returnList) const
{
    std::vector< std::shared_ptr<IRxPort> > rxPorts = IRxPortFactory::getPorts( ) ;

    if( index >= static_cast<unsigned>(IRadioFactory::getInterface()->getNumberOfTxPorts() ))
    {
        returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );

        std::stringstream ss ;
        ss << "index " << index+1 << " outside valid range (Number of ports "
                << IRadioFactory::getInterface()->getNumberOfRxPorts() << ")" ;
        returnList->find(RtiKeyword::MESSAGE_VAR)->set(ss.str()) ;

        return std::shared_ptr<IRxPort>() ;
    }
    return rxPorts[index];
}


//-------------------------------------------------------------------------------------------------------------
bool SharedArbTestHelper::setCarrier(
	unsigned index,
	const std::string& typeStr,
	const Frequency& centreFreq,
	unsigned groupSize,
	DataVariantList *returnList) const
{
	bool ok ;
	ICarrierSetter& carrierSetter( getCarrierSetter(ok, index, returnList) ) ;
	if (!ok)
		return false ;

#ifdef DEBUG_ARB
	std::string carrierSetStr("[ARB] .carrier.set " + std::to_string(index) + " " + typeStr + " ") ;
#endif

	ok = carrierSetter.setType(ICarrier::strToType(typeStr)) ;
	if (!checkState(ok, "Type", returnList))
		return false ;

	ok = carrierSetter.setState(ICarrier::STATE_DISABLE) ;
	if (!checkState(ok, "State", returnList))
		return false ;


	ok = carrierSetter.setSigType(ICarrier::SIGTYPE_TX) ;
	if (!checkState(ok, "SigType", returnList))
		return false ;


	ok = carrierSetter.setTxPower( Power(37.0) ) ;
	if (!checkState(ok, "TxPower", returnList))
		return false ;

	ok = carrierSetter.setTxFrequency(centreFreq) ;
	if (!checkState(ok, "TxFreq", returnList))
		return false ;

	ok = carrierSetter.setRxFrequency(centreFreq) ;
	if (!checkState(ok, "RxFreq", returnList))
		return false ;

	ok = carrierSetter.setGroupSizeUp( groupSize ) ;
	if (!checkState(ok, "GroupUp", returnList))
		return false ;

	ok = carrierSetter.setGroupSizeDown( groupSize ) ;
	if (!checkState(ok, "GroupDown", returnList))
		return false ;

	// The playback wave is scaled for -18dB such that cpri playback will be correct. But for RF we need to increase the levels by 0.9dB hence the TX scaling of -18.9
	ok = carrierSetter.setTxScaling( Power(-18.9) ) ;
	if (!checkState(ok, "TxScaling", returnList))
		return false ;

#ifdef DEBUG_ARB
	carrierSetStr.append("state=DISABLE sigtype=TX TxPower=37 TxScaling=-18.9 ") ;
	carrierSetStr.append("TxFreq=" + std::to_string(centreFreq.getUint(Frequency::KHz)) +
			" RxFreq=" + std::to_string(centreFreq.getUint(Frequency::KHz)) + " ") ;
	carrierSetStr.append("GroupUp=" + std::to_string(groupSize) + " GroupDown=" + std::to_string(groupSize) + " ") ;
#endif

	unsigned startAxC(1) ;
	if (index == CARRIER_MULTICAST_INDEX)
		startAxC += 2 * groupSize ;

	for (unsigned idx=0; idx < NUM_PORTS; ++idx)
	{
		ok = carrierSetter.setTxContainer( idx, startAxC ) ;
		if (!checkState(ok, "TxContainer", returnList))
			return false ;

		ok = carrierSetter.setRxContainer( idx, startAxC ) ;
		if (!checkState(ok, "RxContainer", returnList))
			return false ;

#ifdef DEBUG_ARB
	carrierSetStr.append("TxContainer[" + std::to_string(idx) + "]=" + std::to_string(startAxC) + " ") ;
	carrierSetStr.append("RxContainer[" + std::to_string(idx) + "]=" + std::to_string(startAxC) + " ") ;
#endif

		startAxC += groupSize ;
	}

	logDebugNormal("arb: Set up carrier %u", index) ;

	// Apply changes - carrier enabled to apply all changes
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance()) ;
	if (!carrierServer->setCarrier( carrierSetter ))
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );

		std::stringstream ss ;
		ss << "Unable to set carrier " << index << " : " << carrierServer->getSetCarrierFailureStr() ;
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(ss.str()) ;
		return false ;
	}

#ifdef DEBUG_ARB
	LOG_DEBUG_ARB(carrierSetStr) ;
#endif


	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SharedArbTestHelper::checkState(bool ok, const std::string& param, DataVariantList *returnList) const
{
	if (!ok)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );

		std::stringstream ss ;
		ss << "Unable to set " << param ;
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(ss.str()) ;

		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SharedArbTestHelper::checkSettings(DataVariantList *returnList) const
{
	// Need to ensure both air standard and bandwidth are configured
	if (mAirStd.empty() || mBw.empty())
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Cannot run arb unless Air standard and Bandwidth have been set") ;

		return false ;
	}

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SharedArbTestHelper::getPortNum(unsigned& port, DataVariantList *callList, DataVariantList *returnList) const
{
	int portVal(callList->find("port")->toInt()) ;
	if (portVal <= 0 || portVal > (int)NUM_PORTS)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("Invalid port number") ;

		return false ;
	}

	// User interface uses ports starting at 1, internally we start at 0
	port = static_cast<unsigned>(portVal-1) ;
	return true ;
}

//-------------------------------------------------------------------------------------------------------------
bool SharedArbTestHelper::setCarrierState(unsigned index, bool enable, DataVariantList *returnList) const
{
	bool ok ;
	ICarrierSetter& carrierSetter( getCarrierSetter(ok, index, returnList) ) ;
	if (!ok)
		return false ;

	ICarrier::State state(ICarrier::STATE_DISABLE) ;
	if (enable)
		state = ICarrier::STATE_ENABLE ;

	carrierSetter.setState(state) ;

	// Apply changes
	std::shared_ptr<ICarrierServer> carrierServer(ICarrierServer::getInstance()) ;
	if (!carrierServer->setCarrier( carrierSetter ))
	{
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );

		std::stringstream ss ;
		ss << "Unable to set carrier " << index << " : " << carrierServer->getSetCarrierFailureStr() ;
		returnList->find(RtiKeyword::MESSAGE_VAR)->set(ss.str()) ;
		return false ;
	}

	logDebugNormal("arb: Carrier %u %s", index, (enable ? "ENABLED" : "DISABLED")) ;

	LOG_DEBUG_ARB("[ARB] .carrier.set %u state=%s", index, (enable ? "ENABLE" : "DISABLE")) ;

	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool SharedArbTestHelper::setAllCarriersState(bool enable, DataVariantList *returnList) const
{
	if (!setCarrierState(CARRIER_INDEX, enable, returnList))
		return false ;

	if (!setCarrierState(CARRIER_MULTICAST_INDEX, enable, returnList))
		return false ;

	return true ;
}

//-------------------------------------------------------------------------------------------------------------
void SharedArbTestHelper::showFiles(const std::string& path, DataVariantList *returnList) const
{
	std::vector<std::string> contents(Path::dirContents(path)) ;
	std::stringstream ss ;
	ss << std::endl ;

	for (auto entry : contents)
	{
		if (Path::isFile(entry))
			ss << entry << std::endl ;
	}

	returnList->find(RtiKeyword::INFO_VAR)->set(ss.str()) ;
}
